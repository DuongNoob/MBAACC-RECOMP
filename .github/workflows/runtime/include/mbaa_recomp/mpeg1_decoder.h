#pragma once

/**
 * @file mpeg1_decoder.h
 * @brief Zero-dependency, pure-C++20 ISO/IEC 11172-2 MPEG-1 Video Decoder.
 *
 * Supports both raw MPEG-1 Video Elementary Streams (0x000001B3, e.g. dat_m_ttl.d)
 * and MPEG-1 Program Streams (0x000001BA + 0x000001E0..0xEF PES packs, e.g. dat_m_vs.d).
 *
 * Pure BYOC runtime decoder (zero bundled assets, zero external libraries).
 * Designed for low RAM (~1.4 MiB frame buffers + ES) and fast arm64 decode on iOS 15+.
 */

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

namespace mbaa_recomp {

class Mpeg1Decoder {
public:
    Mpeg1Decoder() noexcept {
        non_intra_quant_zz_.fill(16u);
    }
    ~Mpeg1Decoder() = default;

    Mpeg1Decoder(const Mpeg1Decoder&) = delete;
    Mpeg1Decoder& operator=(const Mpeg1Decoder&) = delete;

    bool open_file(const std::string& path) {
        close();
        std::ifstream ifs(path, std::ios::binary | std::ios::ate);
        if (!ifs.is_open()) {
            return false;
        }
        const std::streamoff sz = ifs.tellg();
        if (sz <= 12) {
            return false;
        }
        ifs.seekg(0, std::ios::beg);
        std::vector<uint8_t> raw(static_cast<size_t>(sz));
        if (!ifs.read(reinterpret_cast<char*>(raw.data()), sz)) {
            return false;
        }
        return open_owned_buffer(std::move(raw));
    }

    bool open_memory(const uint8_t* data, size_t size) {
        close();
        if (!data || size <= 12) {
            return false;
        }
        std::vector<uint8_t> raw(data, data + size);
        return open_owned_buffer(std::move(raw));
    }

    void close() {
        is_open_ = false;
        width_ = 0;
        height_ = 0;
        mb_width_ = 0;
        mb_height_ = 0;
        coded_width_ = 0;
        coded_height_ = 0;
        fps_ = 30.0;
        frame_count_ = 0;
        current_display_idx_ = -1;
        fwd_decode_idx_ = -1;
        bwd_decode_idx_ = -1;
        cur_b_decode_idx_ = -1;
        display_buf_ = nullptr;
        last_seq_offset_loaded_ = kInvalidOffset;

        es_data_.clear();
        es_data_.shrink_to_fit();
        pics_.clear();
        pics_.shrink_to_fit();
        display_to_decode_.clear();
        display_to_decode_.shrink_to_fit();
        buf_fwd_.clear();
        buf_bwd_.clear();
        buf_b_.clear();
    }

    [[nodiscard]] bool is_open() const noexcept { return is_open_; }
    [[nodiscard]] uint32_t width() const noexcept { return width_; }
    [[nodiscard]] uint32_t height() const noexcept { return height_; }
    [[nodiscard]] double fps() const noexcept { return fps_; }
    [[nodiscard]] uint32_t frame_count() const noexcept { return frame_count_; }
    [[nodiscard]] double duration_seconds() const noexcept {
        return (fps_ > 0.0) ? (static_cast<double>(frame_count_) / fps_) : 0.0;
    }
    [[nodiscard]] int32_t current_frame_index() const noexcept { return current_display_idx_; }

    /// Decodes (or reuses cached) display-order frame `display_idx` in [0, frame_count - 1].
    bool decode_frame(int32_t display_idx) {
        if (!is_open_ || frame_count_ == 0u) {
            return false;
        }
        if (display_idx < 0) {
            display_idx = 0;
        }
        if (static_cast<uint32_t>(display_idx) >= frame_count_) {
            display_idx = static_cast<int32_t>(frame_count_ - 1u);
        }

        const int32_t d_target = display_to_decode_[static_cast<size_t>(display_idx)];
        if (d_target < 0 || static_cast<size_t>(d_target) >= pics_.size()) {
            return false;
        }

        // Fast cache hit: already decoded in one of our 3 active YUV buffers.
        if (d_target == bwd_decode_idx_) {
            display_buf_ = &buf_bwd_;
            current_display_idx_ = display_idx;
            return true;
        }
        if (d_target == fwd_decode_idx_) {
            display_buf_ = &buf_fwd_;
            current_display_idx_ = display_idx;
            return true;
        }
        if (d_target == cur_b_decode_idx_) {
            display_buf_ = &buf_b_;
            current_display_idx_ = display_idx;
            return true;
        }

        // Find the latest I-frame <= d_target.
        int32_t d_i = d_target;
        while (d_i > 0 && pics_[static_cast<size_t>(d_i)].pic_type != kPicTypeI) {
            --d_i;
        }

        // Check if d_target is an open-GOP leading B-frame immediately following d_i
        // (no P-frame between d_i and d_target). Such B-frames reference the last I/P
        // picture of the previous GOP as forward reference.
        int32_t d_start = d_i;
        bool is_open_gop_leading_b = false;
        int32_t prev_ref_before_i = -1;
        if (pics_[static_cast<size_t>(d_target)].pic_type == kPicTypeB && d_i > 0) {
            bool has_intervening_ref = false;
            for (int32_t k = d_i + 1; k < d_target; ++k) {
                const uint8_t pt = pics_[static_cast<size_t>(k)].pic_type;
                if (pt == kPicTypeI || pt == kPicTypeP) {
                    has_intervening_ref = true;
                    break;
                }
            }
            if (!has_intervening_ref) {
                is_open_gop_leading_b = true;
                for (int32_t k = d_i - 1; k >= 0; --k) {
                    const uint8_t pt = pics_[static_cast<size_t>(k)].pic_type;
                    if (pt == kPicTypeI || pt == kPicTypeP) {
                        prev_ref_before_i = k;
                        break;
                    }
                }
                if (prev_ref_before_i >= 0 && bwd_decode_idx_ != prev_ref_before_i) {
                    int32_t prev_i = prev_ref_before_i;
                    while (prev_i > 0 && pics_[static_cast<size_t>(prev_i)].pic_type != kPicTypeI) {
                        --prev_i;
                    }
                    d_start = prev_i;
                }
            }
        }

        int32_t loop_start = d_start;
        const bool can_continue_seq =
            (bwd_decode_idx_ >= 0 && bwd_decode_idx_ < d_target) &&
            ((d_start <= bwd_decode_idx_) ||
             (is_open_gop_leading_b && bwd_decode_idx_ == prev_ref_before_i));

        if (can_continue_seq) {
            loop_start = bwd_decode_idx_ + 1;
        } else {
            fwd_decode_idx_ = -1;
            bwd_decode_idx_ = -1;
            cur_b_decode_idx_ = -1;
            buf_fwd_.fill_neutral();
            buf_bwd_.fill_neutral();
            loop_start = d_start;
        }

        for (int32_t d = loop_start; d <= d_target; ++d) {
            const uint8_t pt = pics_[static_cast<size_t>(d)].pic_type;
            if (pt == kPicTypeB && d != d_target) {
                continue; // Non-reference B-frames never affect later frames.
            }
            if (!decode_picture_at(d)) {
                // Keep going best-effort if a single slice had trailing garbage.
                if (d == d_target) {
                    break;
                }
            }
        }

        if (d_target == bwd_decode_idx_) {
            display_buf_ = &buf_bwd_;
        } else if (d_target == cur_b_decode_idx_) {
            display_buf_ = &buf_b_;
        } else if (d_target == fwd_decode_idx_) {
            display_buf_ = &buf_fwd_;
        } else {
            return false;
        }
        current_display_idx_ = display_idx;
        return true;
    }

    /// Converts the currently decoded YCbCr 4:2:0 frame into BGRA32 or BGR24 pixels.
    /// When `bottom_up` is true, row `height - 1` is written first (Windows DIB / DirectShow order).
    bool copy_rgb(uint8_t* dst, size_t dst_size, bool rgb32, bool bottom_up) const {
        if (!is_open_ || !display_buf_ || !dst || width_ == 0u || height_ == 0u) {
            return false;
        }
        const size_t bpp = rgb32 ? 4u : 3u;
        const size_t row_bytes = static_cast<size_t>(width_) * bpp;
        const size_t required = row_bytes * static_cast<size_t>(height_);
        if (dst_size < required) {
            return false;
        }

        const uint32_t y_stride = coded_width_;
        const uint32_t c_stride = coded_width_ >> 1;
        const uint8_t* y_plane  = display_buf_->y.data();
        const uint8_t* cb_plane = display_buf_->cb.data();
        const uint8_t* cr_plane = display_buf_->cr.data();

        for (uint32_t y = 0; y < height_; ++y) {
            const uint32_t dst_y = bottom_up ? (height_ - 1u - y) : y;
            uint8_t* out = dst + static_cast<size_t>(dst_y) * row_bytes;
            const uint8_t* yp  = y_plane  + static_cast<size_t>(y) * y_stride;
            const uint8_t* cbp = cb_plane + static_cast<size_t>(y >> 1) * c_stride;
            const uint8_t* crp = cr_plane + static_cast<size_t>(y >> 1) * c_stride;

            if (rgb32) {
                uint32_t x = 0;
                for (; x + 1u < width_; x += 2u) {
                    const int32_t d  = static_cast<int32_t>(cbp[x >> 1]) - 128;
                    const int32_t e  = static_cast<int32_t>(crp[x >> 1]) - 128;
                    const int32_t bc = 516 * d + 128;
                    const int32_t gc = -100 * d - 208 * e + 128;
                    const int32_t rc = 409 * e + 128;

                    const int32_t y0 = 298 * (static_cast<int32_t>(yp[x]) - 16);
                    out[x * 4u + 0u] = clamp_u8((y0 + bc) >> 8);
                    out[x * 4u + 1u] = clamp_u8((y0 + gc) >> 8);
                    out[x * 4u + 2u] = clamp_u8((y0 + rc) >> 8);
                    out[x * 4u + 3u] = 0xFFu;

                    const int32_t y1 = 298 * (static_cast<int32_t>(yp[x + 1u]) - 16);
                    out[x * 4u + 4u] = clamp_u8((y1 + bc) >> 8);
                    out[x * 4u + 5u] = clamp_u8((y1 + gc) >> 8);
                    out[x * 4u + 6u] = clamp_u8((y1 + rc) >> 8);
                    out[x * 4u + 7u] = 0xFFu;
                }
                for (; x < width_; ++x) {
                    const int32_t c = static_cast<int32_t>(yp[x]) - 16;
                    const int32_t d = static_cast<int32_t>(cbp[x >> 1]) - 128;
                    const int32_t e = static_cast<int32_t>(crp[x >> 1]) - 128;
                    const int32_t ys = 298 * c + 128;
                    out[x * 4u + 0u] = clamp_u8((ys + 516 * d) >> 8);
                    out[x * 4u + 1u] = clamp_u8((ys - 100 * d - 208 * e) >> 8);
                    out[x * 4u + 2u] = clamp_u8((ys + 409 * e) >> 8);
                    out[x * 4u + 3u] = 0xFFu;
                }
            } else {
                for (uint32_t x = 0; x < width_; ++x) {
                    const int32_t c = static_cast<int32_t>(yp[x]) - 16;
                    const int32_t d = static_cast<int32_t>(cbp[x >> 1]) - 128;
                    const int32_t e = static_cast<int32_t>(crp[x >> 1]) - 128;
                    const int32_t ys = 298 * c + 128;
                    out[x * 3u + 0u] = clamp_u8((ys + 516 * d) >> 8);
                    out[x * 3u + 1u] = clamp_u8((ys - 100 * d - 208 * e) >> 8);
                    out[x * 3u + 2u] = clamp_u8((ys + 409 * e) >> 8);
                }
            }
        }
        return true;
    }

private:
    static constexpr size_t kInvalidOffset = static_cast<size_t>(-1);

    static constexpr uint8_t kPicTypeI = 1u;
    static constexpr uint8_t kPicTypeP = 2u;
    static constexpr uint8_t kPicTypeB = 3u;
    static constexpr uint8_t kPicTypeD = 4u;

    static constexpr uint8_t kMbQuant   = 0x01u;
    static constexpr uint8_t kMbFwd     = 0x02u;
    static constexpr uint8_t kMbBwd     = 0x04u;
    static constexpr uint8_t kMbPattern = 0x08u;
    static constexpr uint8_t kMbIntra   = 0x10u;

    static constexpr int16_t kMbIncStuffing = -1;
    static constexpr int16_t kMbIncEscape   = -2;

    static constexpr uint8_t kAcFlagEob    = 0x01u;
    static constexpr uint8_t kAcFlagEscape = 0x02u;

    struct YuvPlaneBuffer {
        std::vector<uint8_t> y;
        std::vector<uint8_t> cb;
        std::vector<uint8_t> cr;

        void allocate(uint32_t coded_w, uint32_t coded_h) {
            const size_t y_sz = static_cast<size_t>(coded_w) * coded_h;
            const size_t c_sz = static_cast<size_t>(coded_w >> 1) * (coded_h >> 1);
            y.assign(y_sz, 16u);
            cb.assign(c_sz, 128u);
            cr.assign(c_sz, 128u);
        }

        void fill_neutral() {
            std::fill(y.begin(), y.end(), 16u);
            std::fill(cb.begin(), cb.end(), 128u);
            std::fill(cr.begin(), cr.end(), 128u);
        }

        void clear() {
            y.clear();  y.shrink_to_fit();
            cb.clear(); cb.shrink_to_fit();
            cr.clear(); cr.shrink_to_fit();
        }
    };

    struct PictureEntry {
        size_t   pic_offset    = 0;
        size_t   seq_offset    = 0;
        uint8_t  pic_type      = 0;
        uint16_t temporal_ref  = 0;
        int32_t  display_index = -1;
    };

    struct BitReader {
        const uint8_t* data = nullptr;
        size_t size = 0;
        size_t byte_pos = 0;
        uint64_t bit_buf = 0;
        int32_t bit_count = 0;

        void init(const uint8_t* ptr, size_t len, size_t start_offset) noexcept {
            data = ptr;
            size = len;
            byte_pos = (start_offset <= len) ? start_offset : len;
            bit_buf = 0;
            bit_count = 0;
            refill();
        }

        void refill() noexcept {
            while (bit_count <= 56 && byte_pos < size) {
                bit_buf = (bit_buf << 8) | static_cast<uint64_t>(data[byte_pos++]);
                bit_count += 8;
            }
        }

        [[nodiscard]] bool eof() const noexcept {
            return bit_count == 0 && byte_pos >= size;
        }

        [[nodiscard]] uint32_t peek_bits(int32_t n) noexcept {
            if (n <= 0) return 0u;
            if (bit_count < n) refill();
            if (bit_count >= n) {
                return static_cast<uint32_t>((bit_buf >> (bit_count - n)) & ((1ull << n) - 1ull));
            }
            if (bit_count == 0) return 0u;
            const int32_t pad = n - bit_count;
            return static_cast<uint32_t>((bit_buf << pad) & ((1ull << n) - 1ull));
        }

        void skip_bits(int32_t n) noexcept {
            if (n <= 0) return;
            if (bit_count < n) refill();
            if (bit_count >= n) {
                bit_count -= n;
            } else {
                bit_count = 0;
            }
        }

        [[nodiscard]] uint32_t read_bits(int32_t n) noexcept {
            const uint32_t v = peek_bits(n);
            skip_bits(n);
            return v;
        }

        void align_to_byte() noexcept {
            const int32_t rem = bit_count & 7;
            if (rem != 0) {
                bit_count -= rem;
            }
        }

        [[nodiscard]] size_t current_byte_pos() const noexcept {
            return byte_pos - static_cast<size_t>(bit_count >> 3);
        }

        /// Advances to the next 0x000001XX start code and returns XX, or -1 at EOF.
        int32_t find_next_start_code() noexcept {
            align_to_byte();
            size_t pos = current_byte_pos();
            while (pos + 3u < size) {
                if (data[pos] == 0x00u && data[pos + 1u] == 0x00u && data[pos + 2u] == 0x01u) {
                    const uint8_t code = data[pos + 3u];
                    init(data, size, pos + 4u);
                    return static_cast<int32_t>(code);
                }
                ++pos;
            }
            init(data, size, size);
            return -1;
        }
    };

    // -----------------------------------------------------------------------
    // Canonical ISO/IEC 11172-2 Annex B VLC Tables & O(1) Lookup Tables
    // -----------------------------------------------------------------------
    struct VlcSpec {
        uint32_t code;
        uint8_t  bits;
        int16_t  value;
    };

    struct AcVlcSpec {
        uint32_t code;  // unsigned prefix (without trailing sign bit)
        uint8_t  bits;  // prefix bit length (excluding sign bit)
        uint8_t  run;
        uint8_t  level;
        uint8_t  flags; // kAcFlagEob / kAcFlagEscape / 0
    };

    struct VlcLutEntry {
        int16_t value = 0;
        uint8_t bits  = 0; // 0 = invalid
    };

    struct AcLutEntry {
        uint8_t run   = 0;
        uint8_t level = 0;
        uint8_t bits  = 0; // 0 = invalid
        uint8_t flags = 0;
    };

    struct Tables {
        std::array<VlcLutEntry, 2048> mb_addr_inc{}; // 11-bit direct LUT
        std::array<VlcLutEntry, 4>    mb_type_i{};   // 2-bit direct LUT
        std::array<VlcLutEntry, 64>   mb_type_p{};   // 6-bit direct LUT
        std::array<VlcLutEntry, 64>   mb_type_b{};   // 6-bit direct LUT
        std::array<VlcLutEntry, 512>  cbp{};         // 9-bit direct LUT
        std::array<VlcLutEntry, 2048> motion{};      // 11-bit direct LUT
        std::array<VlcLutEntry, 128>  dc_luma{};     // 7-bit direct LUT
        std::array<VlcLutEntry, 256>  dc_chroma{};   // 8-bit direct LUT
        std::array<AcLutEntry,  1024> ac_hi{};       // 10-bit primary LUT (codes len <= 10, top6 != 0)
        std::array<AcLutEntry,  1024> ac_lo{};       // 10-bit secondary LUT (codes with 6 leading 0s, total len <= 16)

        // ISO/IEC 11172-2 Table B.1 — Macroblock address increment
        static constexpr VlcSpec kMbAddrIncSpecs[] = {
            {0b1u,           1,  1},
            {0b011u,         3,  2},
            {0b010u,         3,  3},
            {0b0011u,        4,  4},
            {0b0010u,        4,  5},
            {0b00011u,       5,  6},
            {0b00010u,       5,  7},
            {0b0000111u,     7,  8},
            {0b0000110u,     7,  9},
            {0b00001011u,    8, 10},
            {0b00001010u,    8, 11},
            {0b00001001u,    8, 12},
            {0b00001000u,    8, 13},
            {0b00000111u,    8, 14},
            {0b00000110u,    8, 15},
            {0b0000010111u, 10, 16},
            {0b0000010110u, 10, 17},
            {0b0000010101u, 10, 18},
            {0b0000010100u, 10, 19},
            {0b0000010011u, 10, 20},
            {0b0000010010u, 10, 21},
            {0b00000100011u, 11, 22},
            {0b00000100010u, 11, 23},
            {0b00000100001u, 11, 24},
            {0b00000100000u, 11, 25},
            {0b00000011111u, 11, 26},
            {0b00000011110u, 11, 27},
            {0b00000011101u, 11, 28},
            {0b00000011100u, 11, 29},
            {0b00000011011u, 11, 30},
            {0b00000011010u, 11, 31},
            {0b00000011001u, 11, 32},
            {0b00000011000u, 11, 33},
            {0b00000001111u, 11, kMbIncStuffing},
            {0b00000001000u, 11, kMbIncEscape},
        };

        // ISO/IEC 11172-2 Table B.2a — I-picture macroblock types
        static constexpr VlcSpec kMbTypeISpecs[] = {
            {0b1u,  1, kMbIntra},
            {0b01u, 2, kMbQuant | kMbIntra},
        };

        // ISO/IEC 11172-2 Table B.2b — P-picture macroblock types
        static constexpr VlcSpec kMbTypePSpecs[] = {
            {0b1u,      1, kMbFwd | kMbPattern},
            {0b01u,     2, kMbPattern},
            {0b001u,    3, kMbFwd},
            {0b00011u,  5, kMbIntra},
            {0b00010u,  5, kMbQuant | kMbFwd | kMbPattern},
            {0b00001u,  5, kMbQuant | kMbPattern},
            {0b000001u, 6, kMbQuant | kMbIntra},
        };

        // ISO/IEC 11172-2 Table B.2c — B-picture macroblock types
        static constexpr VlcSpec kMbTypeBSpecs[] = {
            {0b10u,     2, kMbFwd | kMbBwd},
            {0b11u,     2, kMbFwd | kMbBwd | kMbPattern},
            {0b010u,    3, kMbBwd},
            {0b011u,    3, kMbBwd | kMbPattern},
            {0b0010u,   4, kMbFwd},
            {0b0011u,   4, kMbFwd | kMbPattern},
            {0b00011u,  5, kMbIntra},
            {0b00010u,  5, kMbQuant | kMbFwd | kMbBwd | kMbPattern},
            {0b000011u, 6, kMbQuant | kMbFwd | kMbPattern},
            {0b000010u, 6, kMbQuant | kMbBwd | kMbPattern},
            {0b000001u, 6, kMbQuant | kMbIntra},
        };

        // ISO/IEC 11172-2 Table B.9 — Coded block pattern (CBP, 1..63)
        static constexpr VlcSpec kCbpSpecs[] = {
            {0b111u,       3, 60}, {0b1101u,      4,  4}, {0b1100u,      4,  8},
            {0b1011u,      4, 16}, {0b1010u,      4, 32}, {0b10011u,     5, 12},
            {0b10010u,     5, 48}, {0b10001u,     5, 20}, {0b10000u,     5, 40},
            {0b01111u,     5, 28}, {0b01110u,     5, 44}, {0b01101u,     5, 52},
            {0b01100u,     5, 56}, {0b01011u,     5,  1}, {0b01010u,     5, 61},
            {0b01001u,     5,  2}, {0b01000u,     5, 62}, {0b001111u,    6, 24},
            {0b001110u,    6, 36}, {0b001101u,    6,  3}, {0b001100u,    6, 63},
            {0b0010111u,   7,  5}, {0b0010110u,   7,  9}, {0b0010101u,   7, 17},
            {0b0010100u,   7, 33}, {0b0010011u,   7,  6}, {0b0010010u,   7, 10},
            {0b0010001u,   7, 18}, {0b0010000u,   7, 34}, {0b00011111u,  8,  7},
            {0b00011110u,  8, 11}, {0b00011101u,  8, 19}, {0b00011100u,  8, 35},
            {0b00011011u,  8, 13}, {0b00011010u,  8, 49}, {0b00011001u,  8, 21},
            {0b00011000u,  8, 41}, {0b00010111u,  8, 14}, {0b00010110u,  8, 50},
            {0b00010101u,  8, 22}, {0b00010100u,  8, 42}, {0b00010011u,  8, 15},
            {0b00010010u,  8, 51}, {0b00010001u,  8, 23}, {0b00010000u,  8, 43},
            {0b00001111u,  8, 25}, {0b00001110u,  8, 37}, {0b00001101u,  8, 26},
            {0b00001100u,  8, 38}, {0b00001011u,  8, 29}, {0b00001010u,  8, 45},
            {0b00001001u,  8, 53}, {0b00001000u,  8, 57}, {0b00000111u,  8, 30},
            {0b00000110u,  8, 46}, {0b00000101u,  8, 54}, {0b00000100u,  8, 58},
            {0b000000111u, 9, 31}, {0b000000110u, 9, 47}, {0b000000101u, 9, 55},
            {0b000000100u, 9, 59}, {0b000000011u, 9, 27}, {0b000000010u, 9, 39},
        };

        // ISO/IEC 11172-2 Table B.10 — Motion vectors (-16..+16)
        static constexpr VlcSpec kMotionSpecs[] = {
            {0b1u,            1,   0},
            {0b010u,          3,   1}, {0b011u,          3,  -1},
            {0b0010u,         4,   2}, {0b0011u,         4,  -2},
            {0b00010u,        5,   3}, {0b00011u,        5,  -3},
            {0b0000110u,      7,   4}, {0b0000111u,      7,  -4},
            {0b00001010u,     8,   5}, {0b00001011u,     8,  -5},
            {0b00001000u,     8,   6}, {0b00001001u,     8,  -6},
            {0b00000110u,     8,   7}, {0b00000111u,     8,  -7},
            {0b0000010110u,  10,   8}, {0b0000010111u,  10,  -8},
            {0b0000010100u,  10,   9}, {0b0000010101u,  10,  -9},
            {0b0000010010u,  10,  10}, {0b0000010011u,  10, -10},
            {0b00000100010u, 11,  11}, {0b00000100011u, 11, -11},
            {0b00000100000u, 11,  12}, {0b00000100001u, 11, -12},
            {0b00000011110u, 11,  13}, {0b00000011111u, 11, -13},
            {0b00000011100u, 11,  14}, {0b00000011101u, 11, -14},
            {0b00000011010u, 11,  15}, {0b00000011011u, 11, -15},
            {0b00000011000u, 11,  16}, {0b00000011001u, 11, -16},
        };

        // ISO/IEC 11172-2 Table B.12 — dct_dc_size_luminance
        static constexpr VlcSpec kDcLumaSpecs[] = {
            {0b100u,     3, 0},
            {0b00u,      2, 1},
            {0b01u,      2, 2},
            {0b101u,     3, 3},
            {0b110u,     3, 4},
            {0b1110u,    4, 5},
            {0b11110u,   5, 6},
            {0b111110u,  6, 7},
            {0b1111110u, 7, 8},
        };

        // ISO/IEC 11172-2 Table B.13 — dct_dc_size_chrominance
        static constexpr VlcSpec kDcChromaSpecs[] = {
            {0b00u,       2, 0},
            {0b01u,       2, 1},
            {0b10u,       2, 2},
            {0b110u,      3, 3},
            {0b1110u,     4, 4},
            {0b11110u,    5, 5},
            {0b111110u,   6, 6},
            {0b1111110u,  7, 7},
            {0b11111110u, 8, 8},
        };

        // ISO/IEC 11172-2 Table B.14 — DCT coefficients (next coefficient; first coeff 1s handled explicitly)
        // `code` and `bits` exclude the trailing sign bit `s` for regular entries.
        static constexpr AcVlcSpec kAcSpecs[] = {
            // Special markers (no sign bit)
            {0b10u,                 2,  0,  0, kAcFlagEob},
            {0b000001u,             6,  0,  0, kAcFlagEscape},
            // 2..5 bit prefixes
            {0b11u,                 2,  0,  1, 0},
            {0b011u,                3,  1,  1, 0},
            {0b0100u,               4,  0,  2, 0},
            {0b0101u,               4,  2,  1, 0},
            {0b00101u,              5,  0,  3, 0},
            {0b00111u,              5,  3,  1, 0},
            {0b00110u,              5,  4,  1, 0},
            // 6 bit prefixes
            {0b000110u,             6,  1,  2, 0},
            {0b000111u,             6,  5,  1, 0},
            {0b000101u,             6,  6,  1, 0},
            {0b000100u,             6,  7,  1, 0},
            // 7 bit prefixes
            {0b0000110u,            7,  0,  4, 0},
            {0b0000100u,            7,  2,  2, 0},
            {0b0000111u,            7,  8,  1, 0},
            {0b0000101u,            7,  9,  1, 0},
            // 8 bit prefixes (0010 0xxx)
            {0b00100110u,           8,  0,  5, 0},
            {0b00100001u,           8,  0,  6, 0},
            {0b00100101u,           8,  1,  3, 0},
            {0b00100100u,           8,  3,  2, 0},
            {0b00100111u,           8, 10,  1, 0},
            {0b00100011u,           8, 11,  1, 0},
            {0b00100010u,           8, 12,  1, 0},
            {0b00100000u,           8, 13,  1, 0},
            // 10 bit prefixes (0000 0010 xx / 0000 0011 xx)
            {0b0000001010u,        10,  0,  7, 0},
            {0b0000001100u,        10,  1,  4, 0},
            {0b0000001011u,        10,  2,  3, 0},
            {0b0000001111u,        10,  4,  2, 0},
            {0b0000001001u,        10,  5,  2, 0},
            {0b0000001110u,        10, 14,  1, 0},
            {0b0000001101u,        10, 15,  1, 0},
            {0b0000001000u,        10, 16,  1, 0},
            // 12 bit prefixes (0000 0001 1xxx & 0000 0001 0xxx)
            {0b000000011101u,      12,  0,  8, 0},
            {0b000000011000u,      12,  0,  9, 0},
            {0b000000010011u,      12,  0, 10, 0},
            {0b000000010000u,      12,  0, 11, 0},
            {0b000000011011u,      12,  1,  5, 0},
            {0b000000010100u,      12,  2,  4, 0},
            {0b000000011100u,      12,  3,  3, 0},
            {0b000000010010u,      12,  4,  3, 0},
            {0b000000011110u,      12,  6,  2, 0},
            {0b000000010101u,      12,  7,  2, 0},
            {0b000000010001u,      12,  8,  2, 0},
            {0b000000011111u,      12, 17,  1, 0},
            {0b000000011010u,      12, 18,  1, 0},
            {0b000000011001u,      12, 19,  1, 0},
            {0b000000010111u,      12, 20,  1, 0},
            {0b000000010110u,      12, 21,  1, 0},
            // 13 bit prefixes (0000 0000 1101 0 .. 1111 1)
            {0b0000000011010u,     13,  0, 12, 0},
            {0b0000000011001u,     13,  0, 13, 0},
            {0b0000000011000u,     13,  0, 14, 0},
            {0b0000000010111u,     13,  0, 15, 0},
            {0b0000000010110u,     13,  1,  6, 0},
            {0b0000000010101u,     13,  1,  7, 0},
            {0b0000000010100u,     13,  2,  5, 0},
            {0b0000000010011u,     13,  3,  4, 0},
            {0b0000000010010u,     13,  5,  3, 0},
            {0b0000000010001u,     13,  9,  2, 0},
            {0b0000000010000u,     13, 10,  2, 0},
            {0b0000000011111u,     13, 22,  1, 0},
            {0b0000000011110u,     13, 23,  1, 0},
            {0b0000000011101u,     13, 24,  1, 0},
            {0b0000000011100u,     13, 25,  1, 0},
            {0b0000000011011u,     13, 26,  1, 0},
            // 14 bit prefixes (0000 0000 01xx xx)
            {0b00000000011111u,    14,  0, 16, 0},
            {0b00000000011110u,    14,  0, 17, 0},
            {0b00000000011101u,    14,  0, 18, 0},
            {0b00000000011100u,    14,  0, 19, 0},
            {0b00000000011011u,    14,  0, 20, 0},
            {0b00000000011010u,    14,  0, 21, 0},
            {0b00000000011001u,    14,  0, 22, 0},
            {0b00000000011000u,    14,  0, 23, 0},
            {0b00000000010111u,    14,  0, 24, 0},
            {0b00000000010110u,    14,  0, 25, 0},
            {0b00000000010101u,    14,  0, 26, 0},
            {0b00000000010100u,    14,  0, 27, 0},
            {0b00000000010011u,    14,  0, 28, 0},
            {0b00000000010010u,    14,  0, 29, 0},
            {0b00000000010001u,    14,  0, 30, 0},
            {0b00000000010000u,    14,  0, 31, 0},
            // 15 bit prefixes (0000 0000 001x xxx)
            {0b000000000011000u,   15,  0, 32, 0},
            {0b000000000010111u,   15,  0, 33, 0},
            {0b000000000010110u,   15,  0, 34, 0},
            {0b000000000010101u,   15,  0, 35, 0},
            {0b000000000010100u,   15,  0, 36, 0},
            {0b000000000010011u,   15,  0, 37, 0},
            {0b000000000010010u,   15,  0, 38, 0},
            {0b000000000010001u,   15,  0, 39, 0},
            {0b000000000010000u,   15,  0, 40, 0},
            {0b000000000011111u,   15,  1,  8, 0},
            {0b000000000011110u,   15,  1,  9, 0},
            {0b000000000011101u,   15,  1, 10, 0},
            {0b000000000011100u,   15,  1, 11, 0},
            {0b000000000011011u,   15,  1, 12, 0},
            {0b000000000011010u,   15,  1, 13, 0},
            {0b000000000011001u,   15,  1, 14, 0},
            // 16 bit prefixes (0000 0000 0001 xxxx)
            {0b0000000000010011u,  16,  1, 15, 0},
            {0b0000000000010010u,  16,  1, 16, 0},
            {0b0000000000010001u,  16,  1, 17, 0},
            {0b0000000000010000u,  16,  1, 18, 0},
            {0b0000000000010100u,  16,  6,  3, 0},
            {0b0000000000011010u,  16, 11,  2, 0},
            {0b0000000000011001u,  16, 12,  2, 0},
            {0b0000000000011000u,  16, 13,  2, 0},
            {0b0000000000010111u,  16, 14,  2, 0},
            {0b0000000000010110u,  16, 15,  2, 0},
            {0b0000000000010101u,  16, 16,  2, 0},
            {0b0000000000011111u,  16, 27,  1, 0},
            {0b0000000000011110u,  16, 28,  1, 0},
            {0b0000000000011101u,  16, 29,  1, 0},
            {0b0000000000011100u,  16, 30,  1, 0},
            {0b0000000000011011u,  16, 31,  1, 0},
        };

        static void build_vlc_lut(const VlcSpec* specs, size_t count, VlcLutEntry* lut, int32_t max_bits) noexcept {
            for (size_t i = 0; i < count; ++i) {
                const uint32_t shift = static_cast<uint32_t>(max_bits - specs[i].bits);
                const uint32_t base  = specs[i].code << shift;
                const uint32_t span  = 1u << shift;
                for (uint32_t k = 0; k < span; ++k) {
                    lut[base + k] = VlcLutEntry{specs[i].value, specs[i].bits};
                }
            }
        }

        void build_ac_luts() noexcept {
            for (size_t i = 0; i < std::size(kAcSpecs); ++i) {
                const AcVlcSpec& s = kAcSpecs[i];
                const AcLutEntry entry{s.run, s.level, s.bits, s.flags};
                if (s.bits <= 10u) {
                    const uint32_t shift = 10u - s.bits;
                    const uint32_t base  = s.code << shift;
                    const uint32_t span  = 1u << shift;
                    for (uint32_t k = 0; k < span; ++k) {
                        ac_hi[base + k] = entry;
                    }
                    if (base < 16u) {
                        const uint32_t shift16 = 16u - s.bits;
                        const uint32_t base16  = s.code << shift16;
                        const uint32_t span16  = 1u << shift16;
                        for (uint32_t k = 0; k < span16; ++k) {
                            if (base16 + k < 1024u) {
                                ac_lo[base16 + k] = entry;
                            }
                        }
                    }
                } else {
                    const uint32_t shift16 = 16u - s.bits;
                    const uint32_t base16  = s.code << shift16;
                    const uint32_t span16  = 1u << shift16;
                    for (uint32_t k = 0; k < span16; ++k) {
                        if (base16 + k < 1024u) {
                            ac_lo[base16 + k] = entry;
                        }
                    }
                }
            }
        }

        Tables() noexcept {
            build_vlc_lut(kMbAddrIncSpecs, std::size(kMbAddrIncSpecs), mb_addr_inc.data(), 11);
            build_vlc_lut(kMbTypeISpecs,   std::size(kMbTypeISpecs),   mb_type_i.data(),    2);
            build_vlc_lut(kMbTypePSpecs,   std::size(kMbTypePSpecs),   mb_type_p.data(),    6);
            build_vlc_lut(kMbTypeBSpecs,   std::size(kMbTypeBSpecs),   mb_type_b.data(),    6);
            build_vlc_lut(kCbpSpecs,       std::size(kCbpSpecs),       cbp.data(),          9);
            build_vlc_lut(kMotionSpecs,    std::size(kMotionSpecs),    motion.data(),      11);
            build_vlc_lut(kDcLumaSpecs,    std::size(kDcLumaSpecs),    dc_luma.data(),      7);
            build_vlc_lut(kDcChromaSpecs,  std::size(kDcChromaSpecs),  dc_chroma.data(),    8);
            build_ac_luts();
        }
    };

    static const Tables& tables() {
        static const Tables instance;
        return instance;
    }

    // Zig-zag scan index -> raster index (0..63)
    static constexpr std::array<uint8_t, 64> kZigZag = {
         0,  1,  8, 16,  9,  2,  3, 10,
        17, 24, 32, 25, 18, 11,  4,  5,
        12, 19, 26, 33, 40, 48, 41, 34,
        27, 20, 13,  6,  7, 14, 21, 28,
        35, 42, 49, 56, 57, 50, 43, 36,
        29, 22, 15, 23, 30, 37, 44, 51,
        58, 59, 52, 45, 38, 31, 39, 46,
        53, 60, 61, 54, 47, 55, 62, 63,
    };

    // Default intra quantizer matrix in ZIG-ZAG scan order (ISO/IEC 11172-2 Section 2.4.3.2)
    static constexpr std::array<uint8_t, 64> kDefaultIntraQuantZz = {
         8, 16, 16, 19, 16, 19, 22, 22,
        22, 22, 22, 22, 26, 24, 26, 27,
        27, 27, 26, 26, 26, 26, 27, 27,
        27, 29, 29, 29, 34, 34, 34, 29,
        29, 29, 27, 27, 29, 29, 32, 32,
        34, 34, 37, 38, 37, 35, 35, 34,
        35, 38, 38, 40, 40, 40, 48, 48,
        46, 46, 56, 56, 58, 69, 69, 83,
    };

    // Standard MPEG-1 frame_rate_code table (index 0..15)
    static constexpr std::array<double, 16> kFrameRates = {
        30.0,
        24000.0 / 1001.0,
        24.0,
        25.0,
        30000.0 / 1001.0,
        30.0,
        50.0,
        60000.0 / 1001.0,
        60.0,
        30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 30.0,
    };

    static inline uint8_t clamp_u8(int32_t v) noexcept {
        if (v < 0) return 0u;
        if (v > 255) return 255u;
        return static_cast<uint8_t>(v);
    }

    // -----------------------------------------------------------------------
    // Container Demuxing (PS -> Video ES) & Pre-Scan Indexing
    // -----------------------------------------------------------------------
    bool open_owned_buffer(std::vector<uint8_t>&& raw) {
        // Locate first 0x000001 start code.
        size_t first_sc = 0;
        bool found_sc = false;
        while (first_sc + 4u <= raw.size()) {
            if (raw[first_sc] == 0x00u && raw[first_sc + 1u] == 0x00u && raw[first_sc + 2u] == 0x01u) {
                found_sc = true;
                break;
            }
            ++first_sc;
        }
        if (!found_sc) {
            return false;
        }

        if (raw[first_sc + 3u] == 0xBAu) {
            if (!demux_program_stream(raw.data(), raw.size(), es_data_)) {
                return false;
            }
        } else {
            es_data_ = std::move(raw);
        }

        if (!index_elementary_stream()) {
            close();
            return false;
        }

        buf_fwd_.allocate(coded_width_, coded_height_);
        buf_bwd_.allocate(coded_width_, coded_height_);
        buf_b_.allocate(coded_width_, coded_height_);
        is_open_ = true;
        return true;
    }

    static bool demux_program_stream(const uint8_t* data, size_t size, std::vector<uint8_t>& out_es) {
        out_es.clear();
        out_es.reserve(size);
        size_t pos = 0;
        uint8_t selected_video_stream = 0;

        while (pos + 4u <= size) {
            if (data[pos] != 0x00u || data[pos + 1u] != 0x00u || data[pos + 2u] != 0x01u) {
                ++pos;
                continue;
            }
            const uint8_t code = data[pos + 3u];
            if (code == 0xBAu) {
                // Pack header
                if (pos + 5u > size) break;
                if ((data[pos + 4u] & 0xF0u) == 0x20u) {
                    pos += 12u; // MPEG-1 pack header
                } else if ((data[pos + 4u] & 0xC0u) == 0x40u) {
                    if (pos + 14u > size) break;
                    const size_t stuff = static_cast<size_t>(data[pos + 13u] & 0x07u);
                    pos += 14u + stuff; // MPEG-2 pack header
                } else {
                    pos += 4u;
                }
            } else if (code == 0xB9u) {
                // ISO 11172 end code
                pos += 4u;
            } else if (code == 0xBBu || code >= 0xBCu) {
                if (pos + 6u > size) break;
                const size_t pkt_len =
                    (static_cast<size_t>(data[pos + 4u]) << 8) | static_cast<size_t>(data[pos + 5u]);
                const size_t payload_start = pos + 6u;
                const size_t pkt_end = std::min(size, payload_start + pkt_len);

                if (code >= 0xE0u && code <= 0xEFu) {
                    if (selected_video_stream == 0u) {
                        selected_video_stream = code;
                    }
                    if (code == selected_video_stream) {
                        size_t p = payload_start;
                        // Skip MPEG-1 PES stuffing bytes (0xFF)
                        while (p < pkt_end && data[p] == 0xFFu) {
                            ++p;
                        }
                        if (p < pkt_end) {
                            if ((data[p] & 0xC0u) == 0x80u) {
                                // MPEG-2 PES header
                                if (p + 3u <= pkt_end) {
                                    const size_t hdr_len = data[p + 2u];
                                    p = std::min(pkt_end, p + 3u + hdr_len);
                                } else {
                                    p = pkt_end;
                                }
                            } else {
                                // MPEG-1 PES header
                                if ((data[p] & 0xC0u) == 0x40u) {
                                    p = std::min(pkt_end, p + 2u); // STD buffer scale/size
                                }
                                if (p < pkt_end) {
                                    const uint8_t tag = data[p] & 0xF0u;
                                    if (tag == 0x20u) {
                                        p = std::min(pkt_end, p + 5u); // PTS
                                    } else if (tag == 0x30u) {
                                        p = std::min(pkt_end, p + 10u); // PTS + DTS
                                    } else if (data[p] == 0x0Fu) {
                                        p += 1u; // No PTS/DTS marker
                                    }
                                }
                            }
                        }
                        if (p < pkt_end) {
                            out_es.insert(out_es.end(), data + p, data + pkt_end);
                        }
                    }
                }
                pos = pkt_end;
            } else {
                pos += 4u;
            }
        }
        return !out_es.empty();
    }

    bool index_elementary_stream() {
        pics_.clear();
        display_to_decode_.clear();

        const uint8_t* d = es_data_.data();
        const size_t n = es_data_.size();
        size_t pos = 0;
        size_t last_seq_off = kInvalidOffset;
        bool parsed_first_seq = false;

        while (pos + 4u <= n) {
            if (d[pos] != 0x00u || d[pos + 1u] != 0x00u || d[pos + 2u] != 0x01u) {
                ++pos;
                continue;
            }
            const uint8_t code = d[pos + 3u];
            if (code == 0xB3u && pos + 12u <= n) {
                last_seq_off = pos + 4u;
                if (!parsed_first_seq) {
                    const uint32_t w = (static_cast<uint32_t>(d[pos + 4u]) << 4) |
                                       (static_cast<uint32_t>(d[pos + 5u]) >> 4);
                    const uint32_t h = ((static_cast<uint32_t>(d[pos + 5u]) & 0x0Fu) << 8) |
                                       static_cast<uint32_t>(d[pos + 6u]);
                    const uint8_t fr_code = d[pos + 7u] & 0x0Fu;
                    if (w == 0u || h == 0u || w > 4096u || h > 4096u) {
                        return false;
                    }
                    width_        = w;
                    height_       = h;
                    mb_width_     = (w + 15u) >> 4;
                    mb_height_    = (h + 15u) >> 4;
                    coded_width_  = mb_width_ << 4;
                    coded_height_ = mb_height_ << 4;
                    fps_          = kFrameRates[fr_code];
                    parsed_first_seq = true;
                }
                pos += 12u;
            } else if (code == 0x00u && pos + 8u <= n && parsed_first_seq) {
                const uint16_t tref = static_cast<uint16_t>(
                    (static_cast<uint32_t>(d[pos + 4u]) << 2) | (static_cast<uint32_t>(d[pos + 5u]) >> 6));
                const uint8_t ptype = (d[pos + 5u] >> 3) & 0x07u;
                if (ptype >= kPicTypeI && ptype <= kPicTypeD) {
                    PictureEntry entry{};
                    entry.pic_offset   = pos + 4u;
                    entry.seq_offset   = last_seq_off;
                    entry.pic_type     = ptype;
                    entry.temporal_ref = tref;
                    pics_.push_back(entry);
                }
                pos += 8u;
            } else {
                pos += 4u;
            }
        }

        if (!parsed_first_seq || pics_.empty()) {
            return false;
        }

        // Compute exact display-order mapping using ISO/IEC 11172-2 I/P reorder delay.
        int32_t pending_ref = -1;
        int32_t next_disp = 0;
        for (int32_t i = 0; i < static_cast<int32_t>(pics_.size()); ++i) {
            const uint8_t pt = pics_[static_cast<size_t>(i)].pic_type;
            if (pt == kPicTypeI || pt == kPicTypeP) {
                if (pending_ref >= 0) {
                    pics_[static_cast<size_t>(pending_ref)].display_index = next_disp++;
                }
                pending_ref = i;
            } else {
                pics_[static_cast<size_t>(i)].display_index = next_disp++;
            }
        }
        if (pending_ref >= 0) {
            pics_[static_cast<size_t>(pending_ref)].display_index = next_disp++;
        }

        frame_count_ = static_cast<uint32_t>(next_disp);
        display_to_decode_.assign(frame_count_, -1);
        for (int32_t i = 0; i < static_cast<int32_t>(pics_.size()); ++i) {
            const int32_t di = pics_[static_cast<size_t>(i)].display_index;
            if (di >= 0 && static_cast<uint32_t>(di) < frame_count_) {
                display_to_decode_[static_cast<size_t>(di)] = i;
            }
        }
        return frame_count_ > 0u;
    }

    // -----------------------------------------------------------------------
    // Sequence Header & Picture / Slice / Macroblock Decoding
    // -----------------------------------------------------------------------
    void load_sequence_header(size_t seq_offset) {
        if (seq_offset == kInvalidOffset || seq_offset == last_seq_offset_loaded_) {
            return;
        }
        BitReader br;
        br.init(es_data_.data(), es_data_.size(), seq_offset);
        br.skip_bits(12 + 12 + 4 + 4 + 18 + 1 + 10 + 1); // w, h, ar, fr, bitrate, marker, vbv, cpf

        const uint32_t load_intra = br.read_bits(1);
        if (load_intra != 0u) {
            for (size_t i = 0; i < 64u; ++i) {
                intra_quant_zz_[i] = static_cast<uint8_t>(br.read_bits(8));
            }
        } else {
            intra_quant_zz_ = kDefaultIntraQuantZz;
        }

        const uint32_t load_non_intra = br.read_bits(1);
        if (load_non_intra != 0u) {
            for (size_t i = 0; i < 64u; ++i) {
                non_intra_quant_zz_[i] = static_cast<uint8_t>(br.read_bits(8));
            }
        } else {
            non_intra_quant_zz_.fill(16u);
        }
        last_seq_offset_loaded_ = seq_offset;
    }

    static inline int32_t decode_vlc(BitReader& br, const VlcLutEntry* lut, int32_t max_bits, bool& ok) noexcept {
        const uint32_t idx = br.peek_bits(max_bits);
        const VlcLutEntry e = lut[idx];
        if (e.bits == 0u) {
            ok = false;
            return 0;
        }
        br.skip_bits(e.bits);
        return e.value;
    }

    static inline int32_t decode_dc_diff(BitReader& br, int32_t size) noexcept {
        if (size <= 0) return 0;
        const int32_t val = static_cast<int32_t>(br.read_bits(size));
        const int32_t half = 1 << (size - 1);
        return (val < half) ? (val - ((1 << size) - 1)) : val;
    }

    static inline int32_t decode_motion_component(
        BitReader& br,
        const Tables& tbl,
        int32_t f_code,
        bool full_pel,
        int32_t& prev_recon,
        bool& ok) noexcept
    {
        const int32_t mcode = decode_vlc(br, tbl.motion.data(), 11, ok);
        if (!ok) return prev_recon;

        const int32_t r_size = (f_code > 1) ? (f_code - 1) : 0;
        const int32_t f = 1 << r_size;

        int32_t delta = 0;
        if (f == 1 || mcode == 0) {
            delta = mcode;
        } else {
            const int32_t motion_r = static_cast<int32_t>(br.read_bits(r_size));
            const int32_t abs_m = (mcode < 0) ? -mcode : mcode;
            delta = ((abs_m - 1) * f) + motion_r + 1;
            if (mcode < 0) {
                delta = -delta;
            }
        }

        int32_t recon = prev_recon + delta;
        const int32_t min_v = -16 * f;
        const int32_t max_v = 16 * f - 1;
        const int32_t range = 32 * f;
        if (recon < min_v) {
            recon += range;
        } else if (recon > max_v) {
            recon -= range;
        }
        prev_recon = recon;
        return full_pel ? (recon << 1) : recon;
    }

    bool decode_picture_at(int32_t decode_idx) {
        const PictureEntry& pe = pics_[static_cast<size_t>(decode_idx)];
        load_sequence_header(pe.seq_offset);

        // Determine end of this picture's slice data (next picture start or ES end).
        const size_t pic_end = (static_cast<size_t>(decode_idx + 1) < pics_.size())
            ? (pics_[static_cast<size_t>(decode_idx + 1)].pic_offset - 4u)
            : es_data_.size();

        BitReader br;
        br.init(es_data_.data(), pic_end, pe.pic_offset);

        // Picture header (ISO/IEC 11172-2 Section 2.4.3.5)
        br.skip_bits(10); // temporal_reference
        const uint8_t pic_type = static_cast<uint8_t>(br.read_bits(3));
        br.skip_bits(16); // vbv_delay

        bool full_pel_fwd = false;
        int32_t fwd_f_code = 1;
        bool full_pel_bwd = false;
        int32_t bwd_f_code = 1;

        if (pic_type == kPicTypeP || pic_type == kPicTypeB) {
            full_pel_fwd = (br.read_bits(1) != 0u);
            fwd_f_code   = static_cast<int32_t>(br.read_bits(3));
            if (fwd_f_code < 1) fwd_f_code = 1;
        }
        if (pic_type == kPicTypeB) {
            full_pel_bwd = (br.read_bits(1) != 0u);
            bwd_f_code   = static_cast<int32_t>(br.read_bits(3));
            if (bwd_f_code < 1) bwd_f_code = 1;
        }

        // Skip extra_bit_picture fields
        while (!br.eof() && br.read_bits(1) != 0u) {
            br.skip_bits(8);
        }

        // Rotate reference buffers for I/P pictures; B pictures decode into buf_b_.
        YuvPlaneBuffer* dst = nullptr;
        if (pic_type == kPicTypeI || pic_type == kPicTypeP) {
            std::swap(buf_fwd_, buf_bwd_);
            fwd_decode_idx_ = bwd_decode_idx_;
            bwd_decode_idx_ = decode_idx;
            dst = &buf_bwd_;
        } else {
            cur_b_decode_idx_ = decode_idx;
            dst = &buf_b_;
        }

        const Tables& tbl = tables();
        const int32_t total_mbs = static_cast<int32_t>(mb_width_ * mb_height_);

        // Decode all slices (start codes 0x01..0xAF) until next picture/GOP/sequence/EOF.
        while (true) {
            const int32_t sc = br.find_next_start_code();
            if (sc < 0) break;
            if (sc < 0x01 || sc > 0xAF) {
                if (sc == 0xB2 || sc == 0xB5) {
                    continue; // User data / extension data inside picture
                }
                break;
            }

            const int32_t slice_row = sc - 1;
            if (slice_row < 0 || static_cast<uint32_t>(slice_row) >= mb_height_) {
                continue;
            }

            int32_t quant_scale = static_cast<int32_t>(br.read_bits(5));
            if (quant_scale == 0) quant_scale = 1;
            while (!br.eof() && br.read_bits(1) != 0u) {
                br.skip_bits(8); // extra_information_slice
            }

            // Slice-start resets (ISO/IEC 11172-2)
            int32_t mb_addr = slice_row * static_cast<int32_t>(mb_width_) - 1;
            int32_t dc_pred[3] = {128, 128, 128};
            int32_t recon_fwd_x = 0, recon_fwd_y = 0;
            int32_t recon_bwd_x = 0, recon_bwd_y = 0;
            int32_t mv_fwd_x = 0, mv_fwd_y = 0;
            int32_t mv_bwd_x = 0, mv_bwd_y = 0;
            uint8_t prev_b_dir = 0; // kMbFwd / kMbBwd flags for skipped B-MBs

            bool slice_ok = true;
            while (slice_ok && !br.eof()) {
                // Next start code begins with 23 zero bits.
                if (br.peek_bits(23) == 0u) {
                    break;
                }

                // Decode macroblock_address_increment (with stuffing and +33 escapes)
                int32_t mb_inc = 0;
                while (slice_ok && !br.eof()) {
                    const int32_t v = decode_vlc(br, tbl.mb_addr_inc.data(), 11, slice_ok);
                    if (!slice_ok) break;
                    if (v == kMbIncStuffing) {
                        continue;
                    }
                    if (v == kMbIncEscape) {
                        mb_inc += 33;
                        continue;
                    }
                    mb_inc += v;
                    break;
                }
                if (!slice_ok || mb_inc <= 0) {
                    break;
                }

                // Handle skipped macroblocks (mb_inc > 1)
                if (mb_inc > 1) {
                    dc_pred[0] = dc_pred[1] = dc_pred[2] = 128;
                    if (pic_type == kPicTypeP) {
                        recon_fwd_x = recon_fwd_y = 0;
                        mv_fwd_x = mv_fwd_y = 0;
                    }
                    for (int32_t s = 1; s < mb_inc; ++s) {
                        ++mb_addr;
                        if (mb_addr < 0 || mb_addr >= total_mbs) break;
                        const int32_t mbx = mb_addr % static_cast<int32_t>(mb_width_);
                        const int32_t mby = mb_addr / static_cast<int32_t>(mb_width_);
                        if (pic_type == kPicTypeP) {
                            motion_compensate_mb(*dst, mbx, mby, true, false, 0, 0, 0, 0);
                        } else if (pic_type == kPicTypeB) {
                            const bool use_fwd = (prev_b_dir & kMbFwd) != 0u;
                            const bool use_bwd = (prev_b_dir & kMbBwd) != 0u;
                            motion_compensate_mb(*dst, mbx, mby, use_fwd, use_bwd,
                                                 mv_fwd_x, mv_fwd_y, mv_bwd_x, mv_bwd_y);
                        }
                    }
                }

                ++mb_addr;
                if (mb_addr < 0 || mb_addr >= total_mbs) {
                    break;
                }
                const int32_t mbx = mb_addr % static_cast<int32_t>(mb_width_);
                const int32_t mby = mb_addr / static_cast<int32_t>(mb_width_);

                // Decode macroblock_type
                uint8_t mb_type = 0;
                if (pic_type == kPicTypeI) {
                    mb_type = static_cast<uint8_t>(decode_vlc(br, tbl.mb_type_i.data(), 2, slice_ok));
                } else if (pic_type == kPicTypeP) {
                    mb_type = static_cast<uint8_t>(decode_vlc(br, tbl.mb_type_p.data(), 6, slice_ok));
                } else if (pic_type == kPicTypeB) {
                    mb_type = static_cast<uint8_t>(decode_vlc(br, tbl.mb_type_b.data(), 6, slice_ok));
                } else {
                    // D-picture: 1-bit mb_type = 1
                    br.skip_bits(1);
                    mb_type = kMbIntra;
                }
                if (!slice_ok) break;

                if ((mb_type & kMbQuant) != 0u) {
                    quant_scale = static_cast<int32_t>(br.read_bits(5));
                    if (quant_scale == 0) quant_scale = 1;
                }

                const bool is_intra = (mb_type & kMbIntra) != 0u;
                const bool has_fwd  = (mb_type & kMbFwd) != 0u;
                const bool has_bwd  = (mb_type & kMbBwd) != 0u;

                if (has_fwd) {
                    mv_fwd_x = decode_motion_component(br, tbl, fwd_f_code, full_pel_fwd, recon_fwd_x, slice_ok);
                    mv_fwd_y = decode_motion_component(br, tbl, fwd_f_code, full_pel_fwd, recon_fwd_y, slice_ok);
                    if (!slice_ok) break;
                } else if (pic_type == kPicTypeP) {
                    recon_fwd_x = recon_fwd_y = 0;
                    mv_fwd_x = mv_fwd_y = 0;
                }

                if (has_bwd) {
                    mv_bwd_x = decode_motion_component(br, tbl, bwd_f_code, full_pel_bwd, recon_bwd_x, slice_ok);
                    mv_bwd_y = decode_motion_component(br, tbl, bwd_f_code, full_pel_bwd, recon_bwd_y, slice_ok);
                    if (!slice_ok) break;
                }

                if (is_intra) {
                    recon_fwd_x = recon_fwd_y = 0;
                    recon_bwd_x = recon_bwd_y = 0;
                    mv_fwd_x = mv_fwd_y = 0;
                    mv_bwd_x = mv_bwd_y = 0;
                } else {
                    dc_pred[0] = dc_pred[1] = dc_pred[2] = 128;
                    if (pic_type == kPicTypeB) {
                        prev_b_dir = static_cast<uint8_t>(mb_type & (kMbFwd | kMbBwd));
                    }
                    const bool mc_fwd = (pic_type == kPicTypeP) ? true : has_fwd;
                    const bool mc_bwd = (pic_type == kPicTypeB) ? has_bwd : false;
                    motion_compensate_mb(*dst, mbx, mby, mc_fwd, mc_bwd,
                                         mv_fwd_x, mv_fwd_y, mv_bwd_x, mv_bwd_y);
                }

                uint32_t cbp = is_intra ? 0x3Fu : 0u;
                if ((mb_type & kMbPattern) != 0u) {
                    cbp = static_cast<uint32_t>(decode_vlc(br, tbl.cbp.data(), 9, slice_ok));
                    if (!slice_ok) break;
                }

                // Decode 6 8x8 blocks: 0..3 = Y (TL, TR, BL, BR), 4 = Cb, 5 = Cr
                for (int32_t blk = 0; blk < 6; ++blk) {
                    if ((cbp & (1u << (5 - blk))) == 0u) {
                        continue;
                    }
                    int32_t coeffs[64];
                    if (!decode_block(br, tbl, blk, is_intra, pic_type == kPicTypeD,
                                      quant_scale, dc_pred, coeffs)) {
                        slice_ok = false;
                        break;
                    }
                    idct_8x8(coeffs);

                    uint8_t* plane = nullptr;
                    uint32_t stride = 0;
                    int32_t px = 0;
                    int32_t py = 0;
                    if (blk < 4) {
                        plane  = dst->y.data();
                        stride = coded_width_;
                        px     = (mbx << 4) + ((blk & 1) << 3);
                        py     = (mby << 4) + ((blk & 2) << 2);
                    } else if (blk == 4) {
                        plane  = dst->cb.data();
                        stride = coded_width_ >> 1;
                        px     = mbx << 3;
                        py     = mby << 3;
                    } else {
                        plane  = dst->cr.data();
                        stride = coded_width_ >> 1;
                        px     = mbx << 3;
                        py     = mby << 3;
                    }

                    uint8_t* out = plane + static_cast<size_t>(py) * stride + static_cast<size_t>(px);
                    if (is_intra) {
                        for (int32_t r = 0; r < 8; ++r) {
                            const int32_t* src_row = coeffs + r * 8;
                            for (int32_t c = 0; c < 8; ++c) {
                                out[c] = clamp_u8(src_row[c]);
                            }
                            out += stride;
                        }
                    } else {
                        for (int32_t r = 0; r < 8; ++r) {
                            const int32_t* src_row = coeffs + r * 8;
                            for (int32_t c = 0; c < 8; ++c) {
                                out[c] = clamp_u8(static_cast<int32_t>(out[c]) + src_row[c]);
                            }
                            out += stride;
                        }
                    }
                }

                if (pic_type == kPicTypeD) {
                    br.skip_bits(1); // end_of_macroblock = 1 in D-pictures
                }
            }
        }

        return true;
    }

    bool decode_block(
        BitReader& br,
        const Tables& tbl,
        int32_t blk_idx,
        bool is_intra,
        bool is_d_picture,
        int32_t quant_scale,
        int32_t dc_pred[3],
        int32_t out_coeffs[64]) const noexcept
    {
        std::memset(out_coeffs, 0, sizeof(int32_t) * 64u);
        int32_t n = 0;

        if (is_intra) {
            bool ok = true;
            const int32_t comp = (blk_idx < 4) ? 0 : (blk_idx - 3);
            const int32_t dc_size = (comp == 0)
                ? decode_vlc(br, tbl.dc_luma.data(), 7, ok)
                : decode_vlc(br, tbl.dc_chroma.data(), 8, ok);
            if (!ok) return false;
            dc_pred[comp] += decode_dc_diff(br, dc_size);
            out_coeffs[0] = dc_pred[comp] * 8;
            if (is_d_picture) {
                return true;
            }
            n = 0; // First AC coefficient advances by (run + 1) -> index >= 1
        } else {
            // Non-intra first coefficient: bit pattern `1s` (2 bits) => run=0, level=+/-1
            if (br.peek_bits(1) == 1u) {
                const uint32_t code2 = br.read_bits(2);
                const int32_t level = (code2 & 1u) ? -1 : 1;
                out_coeffs[0] = dequant_non_intra(level, quant_scale, non_intra_quant_zz_[0]);
                n = 0;
            } else {
                n = -1; // So first run=0 lands on index 0
            }
        }

        const uint8_t* qm = is_intra ? intra_quant_zz_.data() : non_intra_quant_zz_.data();
        while (!br.eof()) {
            const uint32_t peek16 = br.peek_bits(16);
            const AcLutEntry e = (peek16 < 1024u)
                ? tbl.ac_lo[peek16]
                : tbl.ac_hi[peek16 >> 6];

            if (e.bits == 0u) {
                return false;
            }
            br.skip_bits(e.bits);

            if ((e.flags & kAcFlagEob) != 0u) {
                return true;
            }

            int32_t run = 0;
            int32_t level = 0;
            if ((e.flags & kAcFlagEscape) != 0u) {
                run = static_cast<int32_t>(br.read_bits(6));
                const uint32_t l8 = br.read_bits(8);
                if (l8 == 0x00u) {
                    level = static_cast<int32_t>(br.read_bits(8));
                } else if (l8 == 0x80u) {
                    level = static_cast<int32_t>(br.read_bits(8)) - 256;
                } else {
                    level = static_cast<int32_t>(static_cast<int8_t>(l8));
                }
            } else {
                run = static_cast<int32_t>(e.run);
                const uint32_t sign = br.read_bits(1);
                level = sign ? -static_cast<int32_t>(e.level) : static_cast<int32_t>(e.level);
            }

            n += run + 1;
            if (n < 0 || n >= 64) {
                return false;
            }

            const int32_t deq = is_intra
                ? dequant_intra_ac(level, quant_scale, qm[n])
                : dequant_non_intra(level, quant_scale, qm[n]);
            out_coeffs[kZigZag[static_cast<size_t>(n)]] = deq;
        }
        return true;
    }

    static inline int32_t dequant_intra_ac(int32_t level, int32_t qscale, uint8_t qm) noexcept {
        int32_t val = (2 * level * qscale * static_cast<int32_t>(qm)) / 16;
        if (val > 0) {
            if ((val & 1) == 0) val -= 1;
            if (val > 2047) val = 2047;
        } else if (val < 0) {
            if ((val & 1) == 0) val += 1;
            if (val < -2048) val = -2048;
        }
        return val;
    }

    static inline int32_t dequant_non_intra(int32_t level, int32_t qscale, uint8_t qm) noexcept {
        if (level == 0) return 0;
        const int32_t sign = (level > 0) ? 1 : -1;
        int32_t val = ((2 * level + sign) * qscale * static_cast<int32_t>(qm)) / 16;
        if (val > 0) {
            if ((val & 1) == 0) val -= 1;
            if (val > 2047) val = 2047;
        } else if (val < 0) {
            if ((val & 1) == 0) val += 1;
            if (val < -2048) val = -2048;
        }
        return val;
    }

    // -----------------------------------------------------------------------
    // Motion Compensation (ISO/IEC 11172-2 half-pel bilinear + bidirectional)
    // -----------------------------------------------------------------------
    void motion_compensate_mb(
        YuvPlaneBuffer& dst,
        int32_t mbx,
        int32_t mby,
        bool use_fwd,
        bool use_bwd,
        int32_t mv_fwd_x,
        int32_t mv_fwd_y,
        int32_t mv_bwd_x,
        int32_t mv_bwd_y) const noexcept
    {
        const int32_t lx = mbx << 4;
        const int32_t ly = mby << 4;
        const int32_t cx = mbx << 3;
        const int32_t cy = mby << 3;
        const int32_t lw = static_cast<int32_t>(coded_width_);
        const int32_t lh = static_cast<int32_t>(coded_height_);
        const int32_t cw = lw >> 1;
        const int32_t ch = lh >> 1;

        // ISO/IEC 11172-2 Section 2.4.4.2: chroma MV = luma MV / 2 (truncated toward zero)
        const int32_t cmv_fx = mv_fwd_x / 2;
        const int32_t cmv_fy = mv_fwd_y / 2;
        const int32_t cmv_bx = mv_bwd_x / 2;
        const int32_t cmv_by = mv_bwd_y / 2;

        if (use_fwd && !use_bwd) {
            mc_plane_uni(dst.y.data(),  buf_fwd_.y.data(),  lw, lh, lx, ly, 16, mv_fwd_x, mv_fwd_y);
            mc_plane_uni(dst.cb.data(), buf_fwd_.cb.data(), cw, ch, cx, cy,  8, cmv_fx,   cmv_fy);
            mc_plane_uni(dst.cr.data(), buf_fwd_.cr.data(), cw, ch, cx, cy,  8, cmv_fx,   cmv_fy);
        } else if (!use_fwd && use_bwd) {
            mc_plane_uni(dst.y.data(),  buf_bwd_.y.data(),  lw, lh, lx, ly, 16, mv_bwd_x, mv_bwd_y);
            mc_plane_uni(dst.cb.data(), buf_bwd_.cb.data(), cw, ch, cx, cy,  8, cmv_bx,   cmv_by);
            mc_plane_uni(dst.cr.data(), buf_bwd_.cr.data(), cw, ch, cx, cy,  8, cmv_bx,   cmv_by);
        } else if (use_fwd && use_bwd) {
            mc_plane_bi(dst.y.data(),  buf_fwd_.y.data(),  buf_bwd_.y.data(),  lw, lh, lx, ly, 16, mv_fwd_x, mv_fwd_y, mv_bwd_x, mv_bwd_y);
            mc_plane_bi(dst.cb.data(), buf_fwd_.cb.data(), buf_bwd_.cb.data(), cw, ch, cx, cy,  8, cmv_fx,   cmv_fy,   cmv_bx,   cmv_by);
            mc_plane_bi(dst.cr.data(), buf_fwd_.cr.data(), buf_bwd_.cr.data(), cw, ch, cx, cy,  8, cmv_fx,   cmv_fy,   cmv_bx,   cmv_by);
        }
    }

    static inline uint8_t sample_halfpel(
        const uint8_t* ref,
        int32_t w,
        int32_t h,
        int32_t sx,
        int32_t sy,
        bool hx,
        bool hy) noexcept
    {
        const int32_t x0 = std::clamp(sx, 0, w - 1);
        const int32_t y0 = std::clamp(sy, 0, h - 1);
        const uint8_t* r0 = ref + static_cast<size_t>(y0) * static_cast<size_t>(w);
        if (!hx && !hy) {
            return r0[x0];
        }
        const int32_t x1 = std::clamp(sx + 1, 0, w - 1);
        if (hx && !hy) {
            return static_cast<uint8_t>((static_cast<int32_t>(r0[x0]) + static_cast<int32_t>(r0[x1]) + 1) >> 1);
        }
        const int32_t y1 = std::clamp(sy + 1, 0, h - 1);
        const uint8_t* r1 = ref + static_cast<size_t>(y1) * static_cast<size_t>(w);
        if (!hx && hy) {
            return static_cast<uint8_t>((static_cast<int32_t>(r0[x0]) + static_cast<int32_t>(r1[x0]) + 1) >> 1);
        }
        return static_cast<uint8_t>((
            static_cast<int32_t>(r0[x0]) + static_cast<int32_t>(r0[x1]) +
            static_cast<int32_t>(r1[x0]) + static_cast<int32_t>(r1[x1]) + 2) >> 2);
    }

    static void mc_plane_uni(
        uint8_t* dst,
        const uint8_t* ref,
        int32_t w,
        int32_t h,
        int32_t dx,
        int32_t dy,
        int32_t blk_sz,
        int32_t mv_x,
        int32_t mv_y) noexcept
    {
        const int32_t ix = mv_x >> 1;
        const int32_t iy = mv_y >> 1;
        const bool hx = (mv_x & 1) != 0;
        const bool hy = (mv_y & 1) != 0;
        const int32_t sx0 = dx + ix;
        const int32_t sy0 = dy + iy;

        const bool in_bounds =
            (sx0 >= 0 && sy0 >= 0 &&
             sx0 + blk_sz + (hx ? 1 : 0) <= w &&
             sy0 + blk_sz + (hy ? 1 : 0) <= h);

        if (in_bounds) {
            uint8_t* dp = dst + static_cast<size_t>(dy) * static_cast<size_t>(w) + static_cast<size_t>(dx);
            const uint8_t* sp = ref + static_cast<size_t>(sy0) * static_cast<size_t>(w) + static_cast<size_t>(sx0);
            if (!hx && !hy) {
                for (int32_t r = 0; r < blk_sz; ++r) {
                    std::memcpy(dp, sp, static_cast<size_t>(blk_sz));
                    dp += w;
                    sp += w;
                }
            } else if (hx && !hy) {
                for (int32_t r = 0; r < blk_sz; ++r) {
                    for (int32_t c = 0; c < blk_sz; ++c) {
                        dp[c] = static_cast<uint8_t>((static_cast<int32_t>(sp[c]) + static_cast<int32_t>(sp[c + 1]) + 1) >> 1);
                    }
                    dp += w;
                    sp += w;
                }
            } else if (!hx && hy) {
                for (int32_t r = 0; r < blk_sz; ++r) {
                    const uint8_t* sp1 = sp + w;
                    for (int32_t c = 0; c < blk_sz; ++c) {
                        dp[c] = static_cast<uint8_t>((static_cast<int32_t>(sp[c]) + static_cast<int32_t>(sp1[c]) + 1) >> 1);
                    }
                    dp += w;
                    sp += w;
                }
            } else {
                for (int32_t r = 0; r < blk_sz; ++r) {
                    const uint8_t* sp1 = sp + w;
                    for (int32_t c = 0; c < blk_sz; ++c) {
                        dp[c] = static_cast<uint8_t>((
                            static_cast<int32_t>(sp[c])  + static_cast<int32_t>(sp[c + 1]) +
                            static_cast<int32_t>(sp1[c]) + static_cast<int32_t>(sp1[c + 1]) + 2) >> 2);
                    }
                    dp += w;
                    sp += w;
                }
            }
            return;
        }

        for (int32_t r = 0; r < blk_sz; ++r) {
            uint8_t* dp = dst + static_cast<size_t>(dy + r) * static_cast<size_t>(w) + static_cast<size_t>(dx);
            for (int32_t c = 0; c < blk_sz; ++c) {
                dp[c] = sample_halfpel(ref, w, h, sx0 + c, sy0 + r, hx, hy);
            }
        }
    }

    static void mc_plane_bi(
        uint8_t* dst,
        const uint8_t* ref_f,
        const uint8_t* ref_b,
        int32_t w,
        int32_t h,
        int32_t dx,
        int32_t dy,
        int32_t blk_sz,
        int32_t mv_fx,
        int32_t mv_fy,
        int32_t mv_bx,
        int32_t mv_by) noexcept
    {
        const int32_t fix = mv_fx >> 1, fiy = mv_fy >> 1;
        const bool fhx = (mv_fx & 1) != 0, fhy = (mv_fy & 1) != 0;
        const int32_t bix = mv_bx >> 1, biy = mv_by >> 1;
        const bool bhx = (mv_bx & 1) != 0, bhy = (mv_by & 1) != 0;

        const int32_t fsx = dx + fix, fsy = dy + fiy;
        const int32_t bsx = dx + bix, bsy = dy + biy;

        for (int32_t r = 0; r < blk_sz; ++r) {
            uint8_t* dp = dst + static_cast<size_t>(dy + r) * static_cast<size_t>(w) + static_cast<size_t>(dx);
            for (int32_t c = 0; c < blk_sz; ++c) {
                const int32_t pf = sample_halfpel(ref_f, w, h, fsx + c, fsy + r, fhx, fhy);
                const int32_t pb = sample_halfpel(ref_b, w, h, bsx + c, bsy + r, bhx, bhy);
                dp[c] = static_cast<uint8_t>((pf + pb + 1) >> 1);
            }
        }
    }

    // -----------------------------------------------------------------------
    // IEEE-1180 Accurate Separable 8x8 Integer IDCT (Chen-Wang butterfly)
    // -----------------------------------------------------------------------
    static void idct_8x8(int32_t block[64]) noexcept {
        static constexpr int32_t kW1 = 2841; // 2048 * sqrt(2) * cos(1*pi/16)
        static constexpr int32_t kW2 = 2676; // 2048 * sqrt(2) * cos(2*pi/16)
        static constexpr int32_t kW3 = 2408; // 2048 * sqrt(2) * cos(3*pi/16)
        static constexpr int32_t kW5 = 1609; // 2048 * sqrt(2) * cos(5*pi/16)
        static constexpr int32_t kW6 = 1108; // 2048 * sqrt(2) * cos(6*pi/16)
        static constexpr int32_t kW7 =  565; // 2048 * sqrt(2) * cos(7*pi/16)

        // Row pass
        for (int32_t r = 0; r < 8; ++r) {
            int32_t* b = block + r * 8;
            int32_t x1 = b[4] << 11;
            int32_t x2 = b[6];
            int32_t x3 = b[2];
            int32_t x4 = b[1];
            int32_t x5 = b[7];
            int32_t x6 = b[5];
            int32_t x7 = b[3];

            if ((x1 | x2 | x3 | x4 | x5 | x6 | x7) == 0) {
                const int32_t dc = b[0] << 3;
                b[0] = b[1] = b[2] = b[3] = b[4] = b[5] = b[6] = b[7] = dc;
                continue;
            }

            int32_t x0 = (b[0] << 11) + 128;

            // Stage 1
            int32_t x8 = kW7 * (x4 + x5);
            x4 = x8 + (kW1 - kW7) * x4;
            x5 = x8 - (kW1 + kW7) * x5;
            x8 = kW3 * (x6 + x7);
            x6 = x8 - (kW3 - kW5) * x6;
            x7 = x8 - (kW3 + kW5) * x7;

            // Stage 2
            x8 = x0 + x1;
            x0 -= x1;
            x1 = kW6 * (x3 + x2);
            x2 = x1 - (kW2 + kW6) * x2;
            x3 = x1 + (kW2 - kW6) * x3;
            x1 = x4 + x6;
            x4 -= x6;
            x6 = x5 + x7;
            x5 -= x7;

            // Stage 3
            x7 = x8 + x3;
            x8 -= x3;
            x3 = x0 + x2;
            x0 -= x2;
            x2 = (181 * (x4 + x5) + 128) >> 8;
            x4 = (181 * (x4 - x5) + 128) >> 8;

            // Stage 4
            b[0] = (x7 + x1) >> 8;
            b[1] = (x3 + x2) >> 8;
            b[2] = (x0 + x4) >> 8;
            b[3] = (x8 + x6) >> 8;
            b[4] = (x8 - x6) >> 8;
            b[5] = (x0 - x4) >> 8;
            b[6] = (x3 - x2) >> 8;
            b[7] = (x7 - x1) >> 8;
        }

        // Column pass
        for (int32_t c = 0; c < 8; ++c) {
            int32_t* b = block + c;
            int32_t x1 = b[8 * 4] << 8;
            int32_t x2 = b[8 * 6];
            int32_t x3 = b[8 * 2];
            int32_t x4 = b[8 * 1];
            int32_t x5 = b[8 * 7];
            int32_t x6 = b[8 * 5];
            int32_t x7 = b[8 * 3];

            if ((x1 | x2 | x3 | x4 | x5 | x6 | x7) == 0) {
                const int32_t dc = (b[0] + 32) >> 6;
                b[8 * 0] = b[8 * 1] = b[8 * 2] = b[8 * 3] = dc;
                b[8 * 4] = b[8 * 5] = b[8 * 6] = b[8 * 7] = dc;
                continue;
            }

            int32_t x0 = (b[8 * 0] << 8) + 8192;

            // Stage 1
            int32_t x8 = kW7 * (x4 + x5) + 4;
            x4 = (x8 + (kW1 - kW7) * x4) >> 3;
            x5 = (x8 - (kW1 + kW7) * x5) >> 3;
            x8 = kW3 * (x6 + x7) + 4;
            x6 = (x8 - (kW3 - kW5) * x6) >> 3;
            x7 = (x8 - (kW3 + kW5) * x7) >> 3;

            // Stage 2
            x8 = x0 + x1;
            x0 -= x1;
            x1 = kW6 * (x3 + x2) + 4;
            x2 = (x1 - (kW2 + kW6) * x2) >> 3;
            x3 = (x1 + (kW2 - kW6) * x3) >> 3;
            x1 = x4 + x6;
            x4 -= x6;
            x6 = x5 + x7;
            x5 -= x7;

            // Stage 3
            x7 = x8 + x3;
            x8 -= x3;
            x3 = x0 + x2;
            x0 -= x2;
            x2 = (181 * (x4 + x5) + 128) >> 8;
            x4 = (181 * (x4 - x5) + 128) >> 8;

            // Stage 4
            b[8 * 0] = (x7 + x1) >> 14;
            b[8 * 1] = (x3 + x2) >> 14;
            b[8 * 2] = (x0 + x4) >> 14;
            b[8 * 3] = (x8 + x6) >> 14;
            b[8 * 4] = (x8 - x6) >> 14;
            b[8 * 5] = (x0 - x4) >> 14;
            b[8 * 6] = (x3 - x2) >> 14;
            b[8 * 7] = (x7 - x1) >> 14;
        }
    }

    // -----------------------------------------------------------------------
    // Decoder Instance State
    // -----------------------------------------------------------------------
    bool     is_open_ = false;
    uint32_t width_ = 0;
    uint32_t height_ = 0;
    uint32_t mb_width_ = 0;
    uint32_t mb_height_ = 0;
    uint32_t coded_width_ = 0;
    uint32_t coded_height_ = 0;
    double   fps_ = 30.0;
    uint32_t frame_count_ = 0;

    std::vector<uint8_t>      es_data_;
    std::vector<PictureEntry> pics_;
    std::vector<int32_t>      display_to_decode_;

    std::array<uint8_t, 64> intra_quant_zz_     = kDefaultIntraQuantZz;
    std::array<uint8_t, 64> non_intra_quant_zz_{};
    size_t last_seq_offset_loaded_ = kInvalidOffset;

    YuvPlaneBuffer buf_fwd_;
    YuvPlaneBuffer buf_bwd_;
    YuvPlaneBuffer buf_b_;
    YuvPlaneBuffer* display_buf_ = nullptr;

    int32_t fwd_decode_idx_      = -1;
    int32_t bwd_decode_idx_      = -1;
    int32_t cur_b_decode_idx_    = -1;
    int32_t current_display_idx_ = -1;
};

} // namespace mbaa_recomp
