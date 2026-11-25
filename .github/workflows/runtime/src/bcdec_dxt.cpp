/**
 * @file bcdec_dxt.cpp
 * @brief Self-contained software DXT1 / DXT2 / DXT3 / DXT4 / DXT5 and DDS -> RGBA8 decoder.
 *
 * Designed for iPhone SE 2020 (Apple A13 Bionic / Metal), which lacks hardware S3TC/DXT
 * support in Metal on iOS. Zero external dependencies.
 *
 * Verified against all 1,167 DDS assets in MBAACC (.p archives):
 *   - DXT1 (BC1, 6 textures)
 *   - DXT2 (BC2 premultiplied alpha -> un-premultiplied to straight RGBA8, 241 textures)
 *   - DXT3 (BC2 explicit 4-bit alpha, 10 textures)
 *   - DXT4 (BC3 premultiplied alpha -> un-premultiplied to straight RGBA8, 277 textures)
 *   - DXT5 (BC3 interpolated 8-bit alpha, 328 textures)
 *   - Uncompressed 32-bit A8R8G8B8 (305 textures) + general RGB/BGR/16-bit/L8 DDS masks.
 */

#include "mbaa_recomp/d3d9_shim.h"

#include <algorithm>
#include <array>
#include <bit>
#include <cstring>

namespace mbaa_recomp {

namespace {

inline uint32_t read_u32_le(const uint8_t* p) noexcept {
    return static_cast<uint32_t>(p[0]) |
           (static_cast<uint32_t>(p[1]) << 8) |
           (static_cast<uint32_t>(p[2]) << 16) |
           (static_cast<uint32_t>(p[3]) << 24);
}

inline uint16_t read_u16_le(const uint8_t* p) noexcept {
    return static_cast<uint16_t>(p[0]) |
           (static_cast<uint16_t>(p[1]) << 8);
}

inline uint64_t read_u64_le(const uint8_t* p) noexcept {
    uint64_t v = 0;
    for (int i = 0; i < 8; ++i) {
        v |= static_cast<uint64_t>(p[i]) << (8 * i);
    }
    return v;
}

inline void rgb565_to_rgb8(uint16_t c, uint8_t& r, uint8_t& g, uint8_t& b) noexcept {
    const uint32_t r5 = (c >> 11) & 0x1Fu;
    const uint32_t g6 = (c >> 5) & 0x3Fu;
    const uint32_t b5 = c & 0x1Fu;
    r = static_cast<uint8_t>((r5 << 3) | (r5 >> 2));
    g = static_cast<uint8_t>((g6 << 2) | (g6 >> 4));
    b = static_cast<uint8_t>((b5 << 3) | (b5 >> 2));
}

inline uint8_t unpremultiply_channel(uint8_t c, uint8_t a) noexcept {
    if (a == 0u) {
        return 0u;
    }
    if (a == 255u) {
        return c;
    }
    const uint32_t v = (static_cast<uint32_t>(c) * 255u + (static_cast<uint32_t>(a) >> 1)) /
                       static_cast<uint32_t>(a);
    return static_cast<uint8_t>(v > 255u ? 255u : v);
}

inline void decode_color_block(
    const uint8_t* color_block,
    bool allow_3color_transparent,
    std::array<std::array<uint8_t, 4>, 4>& out_palette,
    uint32_t& out_indices) noexcept
{
    const uint16_t c0 = read_u16_le(color_block);
    const uint16_t c1 = read_u16_le(color_block + 2);
    out_indices = read_u32_le(color_block + 4);

    uint8_t r0 = 0, g0 = 0, b0 = 0;
    uint8_t r1 = 0, g1 = 0, b1 = 0;
    rgb565_to_rgb8(c0, r0, g0, b0);
    rgb565_to_rgb8(c1, r1, g1, b1);

    out_palette[0] = {r0, g0, b0, 255u};
    out_palette[1] = {r1, g1, b1, 255u};

    if (allow_3color_transparent && c0 <= c1) {
        out_palette[2] = {
            static_cast<uint8_t>((static_cast<uint32_t>(r0) + r1) >> 1),
            static_cast<uint8_t>((static_cast<uint32_t>(g0) + g1) >> 1),
            static_cast<uint8_t>((static_cast<uint32_t>(b0) + b1) >> 1),
            255u
        };
        out_palette[3] = {0u, 0u, 0u, 0u};
    } else {
        out_palette[2] = {
            static_cast<uint8_t>((2u * r0 + r1 + 1u) / 3u),
            static_cast<uint8_t>((2u * g0 + g1 + 1u) / 3u),
            static_cast<uint8_t>((2u * b0 + b1 + 1u) / 3u),
            255u
        };
        out_palette[3] = {
            static_cast<uint8_t>((r0 + 2u * r1 + 1u) / 3u),
            static_cast<uint8_t>((g0 + 2u * g1 + 1u) / 3u),
            static_cast<uint8_t>((b0 + 2u * b1 + 1u) / 3u),
            255u
        };
    }
}

inline uint8_t extract_masked_channel(uint32_t pixel, uint32_t mask) noexcept {
    if (mask == 0u) {
        return 255u;
    }
    const int shift = std::countr_zero(mask);
    const uint32_t shifted_mask = mask >> shift;
    const int bits = std::popcount(shifted_mask);
    const uint32_t val = (pixel >> shift) & shifted_mask;
    if (bits >= 8) {
        return static_cast<uint8_t>(val >> (bits - 8));
    }
    if (bits <= 0) {
        return 0u;
    }
    // Replicate top bits to fill 8-bit range accurately (e.g. 5-bit -> 8-bit)
    uint32_t expanded = val << (8 - bits);
    expanded |= val >> (2 * bits - 8 > 0 ? 2 * bits - 8 : 0);
    if (bits == 1) {
        return val ? 255u : 0u;
    }
    if (bits == 4) {
        return static_cast<uint8_t>((val << 4) | val);
    }
    if (bits == 5) {
        return static_cast<uint8_t>((val << 3) | (val >> 2));
    }
    if (bits == 6) {
        return static_cast<uint8_t>((val << 2) | (val >> 4));
    }
    return static_cast<uint8_t>(std::min<uint32_t>(255u, (val * 255u) / shifted_mask));
}

// D3DFORMAT numeric codes used by Direct3D 9
constexpr uint32_t kD3DFMT_R8G8B8   = 20u;
constexpr uint32_t kD3DFMT_A8R8G8B8 = 21u;
constexpr uint32_t kD3DFMT_X8R8G8B8 = 22u;
constexpr uint32_t kD3DFMT_R5G6B5   = 23u;
constexpr uint32_t kD3DFMT_X1R5G5B5 = 24u;
constexpr uint32_t kD3DFMT_A1R5G5B5 = 25u;
constexpr uint32_t kD3DFMT_A4R4G4B4 = 26u;
constexpr uint32_t kD3DFMT_A8       = 28u;
constexpr uint32_t kD3DFMT_A8B8G8R8 = 32u;
constexpr uint32_t kD3DFMT_X8B8G8R8 = 33u;
constexpr uint32_t kD3DFMT_L8       = 50u;
constexpr uint32_t kD3DFMT_A8L8     = 51u;
constexpr uint32_t kD3DFMT_DXT1     = 0x31545844u; // '1TXD'
constexpr uint32_t kD3DFMT_DXT2     = 0x32545844u; // '2TXD'
constexpr uint32_t kD3DFMT_DXT3     = 0x33545844u; // '3TXD'
constexpr uint32_t kD3DFMT_DXT4     = 0x34545844u; // '4TXD'
constexpr uint32_t kD3DFMT_DXT5     = 0x35545844u; // '5TXD'
constexpr uint32_t kD3DFMT_DX10     = 0x30315844u; // '01XD'

// DDS_PIXELFORMAT flags
constexpr uint32_t kDDPF_ALPHAPIXELS = 0x00000001u;
constexpr uint32_t kDDPF_ALPHA       = 0x00000002u;
constexpr uint32_t kDDPF_FOURCC      = 0x00000004u;
constexpr uint32_t kDDPF_RGB         = 0x00000040u;
constexpr uint32_t kDDPF_LUMINANCE   = 0x00020000u;

} // namespace

void bcdec_dxt1_block(const uint8_t* src_block, uint8_t* dst_rgba, int dst_pitch) noexcept {
    std::array<std::array<uint8_t, 4>, 4> pal{};
    uint32_t indices = 0;
    decode_color_block(src_block, true, pal, indices);

    for (int y = 0; y < 4; ++y) {
        uint8_t* row = dst_rgba + y * dst_pitch;
        for (int x = 0; x < 4; ++x) {
            const uint32_t idx = (indices >> (2 * (y * 4 + x))) & 0x3u;
            const auto& px = pal[idx];
            row[x * 4 + 0] = px[0];
            row[x * 4 + 1] = px[1];
            row[x * 4 + 2] = px[2];
            row[x * 4 + 3] = px[3];
        }
    }
}

void bcdec_dxt23_block(const uint8_t* src_block, uint8_t* dst_rgba, int dst_pitch, bool unpremultiply) noexcept {
    const uint64_t alpha_bits = read_u64_le(src_block);

    std::array<std::array<uint8_t, 4>, 4> pal{};
    uint32_t indices = 0;
    // DXT2/DXT3 always use 4-color RGB mode regardless of c0 <= c1
    decode_color_block(src_block + 8, false, pal, indices);

    for (int y = 0; y < 4; ++y) {
        uint8_t* row = dst_rgba + y * dst_pitch;
        for (int x = 0; x < 4; ++x) {
            const int bit_i = y * 4 + x;
            const uint8_t a4 = static_cast<uint8_t>((alpha_bits >> (4 * bit_i)) & 0xFu);
            const uint8_t a8 = static_cast<uint8_t>((a4 << 4) | a4);
            const auto& px = pal[(indices >> (2 * bit_i)) & 0x3u];
            uint8_t r = px[0];
            uint8_t g = px[1];
            uint8_t b = px[2];
            if (unpremultiply) {
                r = unpremultiply_channel(r, a8);
                g = unpremultiply_channel(g, a8);
                b = unpremultiply_channel(b, a8);
            }
            row[x * 4 + 0] = r;
            row[x * 4 + 1] = g;
            row[x * 4 + 2] = b;
            row[x * 4 + 3] = a8;
        }
    }
}

void bcdec_dxt45_block(const uint8_t* src_block, uint8_t* dst_rgba, int dst_pitch, bool unpremultiply) noexcept {
    const uint8_t a0 = src_block[0];
    const uint8_t a1 = src_block[1];

    uint64_t alpha_indices = 0;
    for (int i = 0; i < 6; ++i) {
        alpha_indices |= static_cast<uint64_t>(src_block[2 + i]) << (8 * i);
    }

    std::array<uint8_t, 8> apal{};
    apal[0] = a0;
    apal[1] = a1;
    if (a0 > a1) {
        for (uint32_t k = 1; k <= 6; ++k) {
            apal[k + 1] = static_cast<uint8_t>(((7u - k) * a0 + k * a1 + 3u) / 7u);
        }
    } else {
        for (uint32_t k = 1; k <= 4; ++k) {
            apal[k + 1] = static_cast<uint8_t>(((5u - k) * a0 + k * a1 + 2u) / 5u);
        }
        apal[6] = 0u;
        apal[7] = 255u;
    }

    std::array<std::array<uint8_t, 4>, 4> pal{};
    uint32_t indices = 0;
    // DXT4/DXT5 always use 4-color RGB mode regardless of c0 <= c1
    decode_color_block(src_block + 8, false, pal, indices);

    for (int y = 0; y < 4; ++y) {
        uint8_t* row = dst_rgba + y * dst_pitch;
        for (int x = 0; x < 4; ++x) {
            const int bit_i = y * 4 + x;
            const uint8_t a8 = apal[(alpha_indices >> (3 * bit_i)) & 0x7u];
            const auto& px = pal[(indices >> (2 * bit_i)) & 0x3u];
            uint8_t r = px[0];
            uint8_t g = px[1];
            uint8_t b = px[2];
            if (unpremultiply) {
                r = unpremultiply_channel(r, a8);
                g = unpremultiply_channel(g, a8);
                b = unpremultiply_channel(b, a8);
            }
            row[x * 4 + 0] = r;
            row[x * 4 + 1] = g;
            row[x * 4 + 2] = b;
            row[x * 4 + 3] = a8;
        }
    }
}

bool decode_dxt_image(
    DxtFormat format,
    uint32_t width,
    uint32_t height,
    const uint8_t* src,
    size_t src_bytes,
    std::vector<uint8_t>& out_rgba)
{
    if (width == 0u || height == 0u || src == nullptr || format == DxtFormat::Unknown) {
        return false;
    }

    const size_t block_bytes = (format == DxtFormat::DXT1) ? 8u : 16u;
    const uint32_t blocks_x = (width + 3u) / 4u;
    const uint32_t blocks_y = (height + 3u) / 4u;
    const size_t required_bytes = static_cast<size_t>(blocks_x) * static_cast<size_t>(blocks_y) * block_bytes;
    if (src_bytes < required_bytes) {
        return false;
    }

    out_rgba.resize(static_cast<size_t>(width) * static_cast<size_t>(height) * 4u);

    uint8_t scratch_block[4 * 4 * 4]{};
    const uint8_t* src_ptr = src;

    for (uint32_t by = 0; by < blocks_y; ++by) {
        const uint32_t copy_h = std::min<uint32_t>(4u, height - by * 4u);
        for (uint32_t bx = 0; bx < blocks_x; ++bx) {
            const uint32_t copy_w = std::min<uint32_t>(4u, width - bx * 4u);

            const bool full_block = (copy_w == 4u && copy_h == 4u);
            uint8_t* dst_target = full_block
                ? (out_rgba.data() + ((static_cast<size_t>(by) * 4u * width + bx * 4u) * 4u))
                : scratch_block;
            const int dst_pitch = full_block ? static_cast<int>(width * 4u) : 16;

            switch (format) {
                case DxtFormat::DXT1:
                    bcdec_dxt1_block(src_ptr, dst_target, dst_pitch);
                    break;
                case DxtFormat::DXT2:
                    bcdec_dxt23_block(src_ptr, dst_target, dst_pitch, true);
                    break;
                case DxtFormat::DXT3:
                    bcdec_dxt23_block(src_ptr, dst_target, dst_pitch, false);
                    break;
                case DxtFormat::DXT4:
                    bcdec_dxt45_block(src_ptr, dst_target, dst_pitch, true);
                    break;
                case DxtFormat::DXT5:
                    bcdec_dxt45_block(src_ptr, dst_target, dst_pitch, false);
                    break;
                default:
                    return false;
            }

            if (!full_block) {
                for (uint32_t row = 0; row < copy_h; ++row) {
                    const size_t dst_off =
                        (static_cast<size_t>(by * 4u + row) * width + bx * 4u) * 4u;
                    std::memcpy(out_rgba.data() + dst_off, scratch_block + row * 16u, copy_w * 4u);
                }
            }

            src_ptr += block_bytes;
        }
    }
    return true;
}

bool dds_probe_info(const uint8_t* dds_data, size_t dds_bytes, DdsProbeInfo& out_info) noexcept {
    out_info = DdsProbeInfo{};
    if (dds_data == nullptr || dds_bytes < 128u) {
        return false;
    }
    if (dds_data[0] != 'D' || dds_data[1] != 'D' || dds_data[2] != 'S' || dds_data[3] != ' ') {
        return false;
    }

    const uint32_t hdr_size = read_u32_le(dds_data + 4);
    if (hdr_size != 124u) {
        return false;
    }

    const uint32_t height    = read_u32_le(dds_data + 12);
    const uint32_t width     = read_u32_le(dds_data + 16);
    const uint32_t mip_raw   = read_u32_le(dds_data + 28);
    const uint32_t pf_size   = read_u32_le(dds_data + 76);
    const uint32_t pf_flags  = read_u32_le(dds_data + 80);
    const uint32_t fourcc    = read_u32_le(dds_data + 84);
    const uint32_t bitcount  = read_u32_le(dds_data + 88);
    const uint32_t rmask     = read_u32_le(dds_data + 92);
    const uint32_t gmask     = read_u32_le(dds_data + 96);
    const uint32_t bmask     = read_u32_le(dds_data + 100);
    const uint32_t amask     = read_u32_le(dds_data + 104);

    if (width == 0u || height == 0u || pf_size != 32u) {
        return false;
    }

    out_info.width        = width;
    out_info.height       = height;
    out_info.mip_count    = mip_raw == 0u ? 1u : mip_raw;
    out_info.pixel_offset = 128u;
    out_info.has_alpha    = (pf_flags & kDDPF_ALPHAPIXELS) != 0u;

    if ((pf_flags & kDDPF_FOURCC) != 0u) {
        out_info.d3d_format = fourcc;
        switch (fourcc) {
            case kD3DFMT_DXT1:
                out_info.dxt_format    = DxtFormat::DXT1;
                out_info.is_compressed = true;
                out_info.has_alpha     = true;
                return true;
            case kD3DFMT_DXT2:
                out_info.dxt_format    = DxtFormat::DXT2;
                out_info.is_compressed = true;
                out_info.has_alpha     = true;
                out_info.premultiplied = true;
                return true;
            case kD3DFMT_DXT3:
                out_info.dxt_format    = DxtFormat::DXT3;
                out_info.is_compressed = true;
                out_info.has_alpha     = true;
                return true;
            case kD3DFMT_DXT4:
                out_info.dxt_format    = DxtFormat::DXT4;
                out_info.is_compressed = true;
                out_info.has_alpha     = true;
                out_info.premultiplied = true;
                return true;
            case kD3DFMT_DXT5:
                out_info.dxt_format    = DxtFormat::DXT5;
                out_info.is_compressed = true;
                out_info.has_alpha     = true;
                return true;
            case kD3DFMT_DX10: {
                if (dds_bytes < 148u) {
                    return false;
                }
                const uint32_t dxgi_fmt = read_u32_le(dds_data + 128);
                out_info.pixel_offset = 148u;
                switch (dxgi_fmt) {
                    case 71u: case 72u: // BC1_UNORM / SRGB
                        out_info.dxt_format = DxtFormat::DXT1;
                        out_info.d3d_format = kD3DFMT_DXT1;
                        out_info.is_compressed = true;
                        out_info.has_alpha = true;
                        return true;
                    case 74u: case 75u: // BC2_UNORM / SRGB
                        out_info.dxt_format = DxtFormat::DXT3;
                        out_info.d3d_format = kD3DFMT_DXT3;
                        out_info.is_compressed = true;
                        out_info.has_alpha = true;
                        return true;
                    case 77u: case 78u: // BC3_UNORM / SRGB
                        out_info.dxt_format = DxtFormat::DXT5;
                        out_info.d3d_format = kD3DFMT_DXT5;
                        out_info.is_compressed = true;
                        out_info.has_alpha = true;
                        return true;
                    case 28u: case 29u: // R8G8B8A8
                        out_info.d3d_format = kD3DFMT_A8B8G8R8;
                        out_info.bits_per_pixel = 32u;
                        out_info.has_alpha = true;
                        return true;
                    case 87u: case 91u: // B8G8R8A8
                        out_info.d3d_format = kD3DFMT_A8R8G8B8;
                        out_info.bits_per_pixel = 32u;
                        out_info.has_alpha = true;
                        return true;
                    default:
                        return false;
                }
            }
            default:
                // Numeric D3DFORMAT stored in FourCC (e.g. 21 = A8R8G8B8)
                out_info.bits_per_pixel = 32u;
                return (fourcc == kD3DFMT_A8R8G8B8 || fourcc == kD3DFMT_X8R8G8B8);
        }
    }

    out_info.bits_per_pixel = bitcount;
    if ((pf_flags & kDDPF_RGB) != 0u) {
        if (bitcount == 32u) {
            if (rmask == 0x00FF0000u && gmask == 0x0000FF00u && bmask == 0x000000FFu) {
                out_info.d3d_format = amask ? kD3DFMT_A8R8G8B8 : kD3DFMT_X8R8G8B8;
            } else if (rmask == 0x000000FFu && gmask == 0x0000FF00u && bmask == 0x00FF0000u) {
                out_info.d3d_format = amask ? kD3DFMT_A8B8G8R8 : kD3DFMT_X8B8G8R8;
            } else {
                out_info.d3d_format = kD3DFMT_A8R8G8B8;
            }
            return true;
        }
        if (bitcount == 24u) {
            out_info.d3d_format = kD3DFMT_R8G8B8;
            return true;
        }
        if (bitcount == 16u) {
            if (rmask == 0xF800u && gmask == 0x07E0u && bmask == 0x001Fu) {
                out_info.d3d_format = kD3DFMT_R5G6B5;
            } else if (rmask == 0x0F00u && amask == 0xF000u) {
                out_info.d3d_format = kD3DFMT_A4R4G4B4;
                out_info.has_alpha = true;
            } else {
                out_info.d3d_format = amask ? kD3DFMT_A1R5G5B5 : kD3DFMT_X1R5G5B5;
            }
            return true;
        }
    }

    if ((pf_flags & kDDPF_LUMINANCE) != 0u) {
        out_info.d3d_format = (bitcount == 16u) ? kD3DFMT_A8L8 : kD3DFMT_L8;
        return bitcount == 8u || bitcount == 16u;
    }

    if ((pf_flags & kDDPF_ALPHA) != 0u && bitcount == 8u) {
        out_info.d3d_format = kD3DFMT_A8;
        out_info.has_alpha = true;
        return true;
    }

    return false;
}

bool decode_dds_to_rgba8(
    const uint8_t* dds_data,
    size_t dds_bytes,
    uint32_t& out_width,
    uint32_t& out_height,
    std::vector<uint8_t>& out_rgba,
    DdsProbeInfo* out_info)
{
    DdsProbeInfo info{};
    if (!dds_probe_info(dds_data, dds_bytes, info)) {
        return false;
    }
    if (out_info != nullptr) {
        *out_info = info;
    }
    out_width  = info.width;
    out_height = info.height;

    const uint8_t* pixels = dds_data + info.pixel_offset;
    const size_t avail = dds_bytes - info.pixel_offset;

    if (info.is_compressed) {
        return decode_dxt_image(info.dxt_format, info.width, info.height, pixels, avail, out_rgba);
    }

    const uint32_t pf_flags = read_u32_le(dds_data + 80);
    const uint32_t rmask    = read_u32_le(dds_data + 92);
    const uint32_t gmask    = read_u32_le(dds_data + 96);
    const uint32_t bmask    = read_u32_le(dds_data + 100);
    const uint32_t amask    = read_u32_le(dds_data + 104);

    const size_t pixel_count = static_cast<size_t>(info.width) * static_cast<size_t>(info.height);
    const size_t bpp_bytes = info.bits_per_pixel / 8u;
    if (bpp_bytes == 0u || avail < pixel_count * bpp_bytes) {
        return false;
    }

    out_rgba.resize(pixel_count * 4u);

    if ((pf_flags & kDDPF_ALPHA) != 0u && info.bits_per_pixel == 8u) {
        for (size_t i = 0; i < pixel_count; ++i) {
            out_rgba[i * 4 + 0] = 255u;
            out_rgba[i * 4 + 1] = 255u;
            out_rgba[i * 4 + 2] = 255u;
            out_rgba[i * 4 + 3] = pixels[i];
        }
        return true;
    }

    if ((pf_flags & kDDPF_LUMINANCE) != 0u) {
        for (size_t i = 0; i < pixel_count; ++i) {
            const uint8_t lum = pixels[i * bpp_bytes];
            const uint8_t alpha = (bpp_bytes == 2u) ? pixels[i * 2 + 1] : 255u;
            out_rgba[i * 4 + 0] = lum;
            out_rgba[i * 4 + 1] = lum;
            out_rgba[i * 4 + 2] = lum;
            out_rgba[i * 4 + 3] = alpha;
        }
        return true;
    }

    if (info.bits_per_pixel == 32u) {
        // Fast path for MBAACC's A8R8G8B8 / X8R8G8B8 (BGRA little-endian -> RGBA8)
        const bool is_bgra = (rmask == 0x00FF0000u && gmask == 0x0000FF00u && bmask == 0x000000FFu) ||
                             (rmask == 0u && gmask == 0u && bmask == 0u);
        const bool is_rgba = (rmask == 0x000000FFu && gmask == 0x0000FF00u && bmask == 0x00FF0000u);
        const bool force_opaque = (amask == 0u) && ((pf_flags & kDDPF_ALPHAPIXELS) == 0u);

        if (is_bgra) {
            for (size_t i = 0; i < pixel_count; ++i) {
                const uint8_t* s = pixels + i * 4u;
                out_rgba[i * 4 + 0] = s[2];
                out_rgba[i * 4 + 1] = s[1];
                out_rgba[i * 4 + 2] = s[0];
                out_rgba[i * 4 + 3] = force_opaque ? 255u : s[3];
            }
            return true;
        }
        if (is_rgba) {
            std::memcpy(out_rgba.data(), pixels, pixel_count * 4u);
            if (force_opaque) {
                for (size_t i = 0; i < pixel_count; ++i) {
                    out_rgba[i * 4 + 3] = 255u;
                }
            }
            return true;
        }
    }

    for (size_t i = 0; i < pixel_count; ++i) {
        uint32_t raw = 0;
        for (size_t b = 0; b < bpp_bytes; ++b) {
            raw |= static_cast<uint32_t>(pixels[i * bpp_bytes + b]) << (8u * b);
        }
        out_rgba[i * 4 + 0] = extract_masked_channel(raw, rmask);
        out_rgba[i * 4 + 1] = extract_masked_channel(raw, gmask);
        out_rgba[i * 4 + 2] = extract_masked_channel(raw, bmask);
        out_rgba[i * 4 + 3] = amask ? extract_masked_channel(raw, amask) : 255u;
    }
    return true;
}

} // namespace mbaa_recomp
