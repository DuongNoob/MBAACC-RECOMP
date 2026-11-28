#include "mbaa_recomp/cccaster_protocol.h"

#include <zlib.h>

#include <algorithm>
#include <array>
#include <cctype>
#include <chrono>
#include <cmath>
#include <cstring>
#include <deque>
#include <mutex>
#include <random>
#include <unordered_map>

#if defined(_WIN32)
#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#  endif
#  ifndef NOMINMAX
#    define NOMINMAX
#  endif
#  include <winsock2.h>
#  include <ws2tcpip.h>
#  pragma comment(lib, "ws2_32.lib")
#else
#  include <arpa/inet.h>
#  include <cerrno>
#  include <fcntl.h>
#  include <ifaddrs.h>
#  include <net/if.h>
#  include <netdb.h>
#  include <netinet/in.h>
#  include <sys/socket.h>
#  include <unistd.h>
#endif

namespace mbaa_recomp {
namespace {

constexpr size_t kMaxStrWireLen       = 4096u;
constexpr size_t kMaxInputCacheFrames = 2048u;
constexpr size_t kMaxEventQueueDepth  = 128u;
constexpr size_t kMaxUdpDatagramBytes = 2048u;
constexpr size_t kMaxPollsPerTick     = 256u;
constexpr uint32_t kFastPingIntervalMs = 50u;
constexpr uint32_t kKeepalivePingMs    = 1000u;

// -----------------------------------------------------------------------------
// Little-Endian Serialization Primitives
// -----------------------------------------------------------------------------

void write_u8(std::vector<uint8_t>& out, uint8_t v) {
    out.push_back(v);
}

void write_u16(std::vector<uint8_t>& out, uint16_t v) {
    out.push_back(static_cast<uint8_t>(v & 0xFFu));
    out.push_back(static_cast<uint8_t>((v >> 8) & 0xFFu));
}

void write_u32(std::vector<uint8_t>& out, uint32_t v) {
    out.push_back(static_cast<uint8_t>(v & 0xFFu));
    out.push_back(static_cast<uint8_t>((v >> 8) & 0xFFu));
    out.push_back(static_cast<uint8_t>((v >> 16) & 0xFFu));
    out.push_back(static_cast<uint8_t>((v >> 24) & 0xFFu));
}

void write_u64(std::vector<uint8_t>& out, uint64_t v) {
    for (int i = 0; i < 8; ++i) {
        out.push_back(static_cast<uint8_t>((v >> (i * 8)) & 0xFFu));
    }
}

void write_f64(std::vector<uint8_t>& out, double v) {
    uint64_t bits = 0u;
    static_assert(sizeof(bits) == sizeof(v));
    std::memcpy(&bits, &v, sizeof(bits));
    write_u64(out, bits);
}

void write_bytes(std::vector<uint8_t>& out, const uint8_t* ptr, size_t n) {
    if (n > 0u) {
        out.insert(out.end(), ptr, ptr + n);
    }
}

void write_len_str(std::vector<uint8_t>& out, const std::string& s) {
    const size_t n = std::min(s.size(), kMaxStrWireLen);
    write_u32(out, static_cast<uint32_t>(n));
    if (n > 0u) {
        const auto* raw = reinterpret_cast<const uint8_t*>(s.data());
        out.insert(out.end(), raw, raw + n);
    }
}

struct ByteReader {
    const uint8_t* data = nullptr;
    size_t         size = 0u;
    size_t         pos  = 0u;

    explicit ByteReader(const std::vector<uint8_t>& buf) noexcept
        : data(buf.data()), size(buf.size()), pos(0u) {}

    ByteReader(const uint8_t* ptr, size_t len) noexcept
        : data(ptr), size(len), pos(0u) {}

    [[nodiscard]] size_t remaining() const noexcept {
        return (pos <= size) ? (size - pos) : 0u;
    }

    bool read_u8(uint8_t& out) noexcept {
        if (remaining() < 1u) return false;
        out = data[pos++];
        return true;
    }

    bool read_i8(int8_t& out) noexcept {
        uint8_t raw = 0u;
        if (!read_u8(raw)) return false;
        out = static_cast<int8_t>(raw);
        return true;
    }

    bool read_u16(uint16_t& out) noexcept {
        if (remaining() < 2u) return false;
        out = static_cast<uint16_t>(data[pos]) |
              (static_cast<uint16_t>(data[pos + 1u]) << 8);
        pos += 2u;
        return true;
    }

    bool read_u32(uint32_t& out) noexcept {
        if (remaining() < 4u) return false;
        out = static_cast<uint32_t>(data[pos]) |
              (static_cast<uint32_t>(data[pos + 1u]) << 8) |
              (static_cast<uint32_t>(data[pos + 2u]) << 16) |
              (static_cast<uint32_t>(data[pos + 3u]) << 24);
        pos += 4u;
        return true;
    }

    bool read_u64(uint64_t& out) noexcept {
        if (remaining() < 8u) return false;
        uint64_t v = 0u;
        for (int i = 0; i < 8; ++i) {
            v |= static_cast<uint64_t>(data[pos + static_cast<size_t>(i)]) << (i * 8);
        }
        pos += 8u;
        out = v;
        return true;
    }

    bool read_f64(double& out) noexcept {
        uint64_t bits = 0u;
        if (!read_u64(bits)) return false;
        double v = 0.0;
        std::memcpy(&v, &bits, sizeof(v));
        if (!std::isfinite(v)) return false;
        out = v;
        return true;
    }

    bool read_bytes(uint8_t* dst, size_t n) noexcept {
        if (remaining() < n) return false;
        if (n > 0u) {
            std::memcpy(dst, data + pos, n);
            pos += n;
        }
        return true;
    }

    bool read_len_str(std::string& out) {
        uint32_t len = 0u;
        if (!read_u32(len)) return false;
        if (len > kMaxStrWireLen || remaining() < len) return false;
        out.assign(reinterpret_cast<const char*>(data + pos), len);
        pos += len;
        return true;
    }

    bool read_len_vec(std::vector<uint8_t>& out, size_t max_len) {
        uint32_t len = 0u;
        if (!read_u32(len)) return false;
        if (len > max_len || remaining() < len) return false;
        out.assign(data + pos, data + pos + len);
        pos += len;
        return true;
    }
};

// -----------------------------------------------------------------------------
// RFC 1321 MD5 Core
// -----------------------------------------------------------------------------

constexpr uint32_t md5_rotl(uint32_t x, uint32_t n) noexcept {
    return (x << n) | (x >> (32u - n));
}

void md5_transform(std::array<uint32_t, 4>& state, const uint8_t block[64]) noexcept {
    static constexpr std::array<uint32_t, 64> kShifts = {
        7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
        5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
        4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
        6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
    };
    static constexpr std::array<uint32_t, 64> kTable = {
        0xd76aa478u, 0xe8c7b756u, 0x242070dbu, 0xc1bdceeeu,
        0xf57c0fafu, 0x4787c62au, 0xa8304613u, 0xfd469501u,
        0x698098d8u, 0x8b44f7afu, 0xffff5bb1u, 0x895cd7beu,
        0x6b901122u, 0xfd987193u, 0xa679438eu, 0x49b40821u,
        0xf61e2562u, 0xc040b340u, 0x265e5a51u, 0xe9b6c7aau,
        0xd62f105du, 0x02441453u, 0xd8a1e681u, 0xe7d3fbc8u,
        0x21e1cde6u, 0xc33707d6u, 0xf4d50d87u, 0x455a14edu,
        0xa9e3e905u, 0xfcefa3f8u, 0x676f02d9u, 0x8d2a4c8au,
        0xfffa3942u, 0x8771f681u, 0x6d9d6122u, 0xfde5380cu,
        0xa4beea44u, 0x4bdecfa9u, 0xf6bb4b60u, 0xbebfbc70u,
        0x289b7ec6u, 0xeaa127fau, 0xd4ef3085u, 0x04881d05u,
        0xd9d4d039u, 0xe6db99e5u, 0x1fa27cf8u, 0xc4ac5665u,
        0xf4292244u, 0x432aff97u, 0xab9423a7u, 0xfc93a039u,
        0x655b59c3u, 0x8f0ccc92u, 0xffeff47du, 0x85845dd1u,
        0x6fa87e4fu, 0xfe2ce6e0u, 0xa3014314u, 0x4e0811a1u,
        0xf7537e82u, 0xbd3af235u, 0x2ad7d2bbu, 0xeb86d391u
    };

    std::array<uint32_t, 16> m{};
    for (size_t i = 0; i < 16; ++i) {
        const size_t j = i * 4u;
        m[i] = static_cast<uint32_t>(block[j]) |
               (static_cast<uint32_t>(block[j + 1u]) << 8) |
               (static_cast<uint32_t>(block[j + 2u]) << 16) |
               (static_cast<uint32_t>(block[j + 3u]) << 24);
    }

    uint32_t a = state[0];
    uint32_t b = state[1];
    uint32_t c = state[2];
    uint32_t d = state[3];

    for (uint32_t i = 0; i < 64u; ++i) {
        uint32_t f = 0u;
        uint32_t g = 0u;
        if (i < 16u) {
            f = (b & c) | ((~b) & d);
            g = i;
        } else if (i < 32u) {
            f = (d & b) | ((~d) & c);
            g = (5u * i + 1u) & 15u;
        } else if (i < 48u) {
            f = b ^ c ^ d;
            g = (3u * i + 5u) & 15u;
        } else {
            f = c ^ (b | (~d));
            g = (7u * i) & 15u;
        }
        const uint32_t tmp = d;
        d = c;
        c = b;
        b = b + md5_rotl(a + f + kTable[i] + m[g], kShifts[i]);
        a = tmp;
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}

// -----------------------------------------------------------------------------
// Wire Serializers for Handshake / Control / State Messages
// -----------------------------------------------------------------------------

std::string make_session_tag() {
    static constexpr const char kAlphabet[] =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<size_t> dist(0u, sizeof(kAlphabet) - 2u);
    std::string tag(10u, '0');
    for (char& ch : tag) {
        ch = kAlphabet[dist(rng)];
    }
    return tag;
}

std::vector<uint8_t> serialize_ack_sequence(uint32_t seq_id) {
    std::vector<uint8_t> out;
    out.reserve(4u);
    write_u32(out, seq_id);
    return out;
}

bool deserialize_ack_sequence(const std::vector<uint8_t>& body, uint32_t& out_seq_id) noexcept {
    ByteReader r(body);
    return r.read_u32(out_seq_id);
}

std::vector<uint8_t> serialize_udp_control(uint32_t seq_id, CccasterUdpControlCode code) {
    std::vector<uint8_t> out;
    out.reserve(5u);
    write_u32(out, seq_id);
    write_u8(out, static_cast<uint8_t>(code));
    return out;
}

bool deserialize_udp_control(const std::vector<uint8_t>& body,
                             uint32_t& out_seq_id,
                             CccasterUdpControlCode& out_code) noexcept {
    ByteReader r(body);
    uint8_t raw_code = 0u;
    if (!r.read_u32(out_seq_id) || !r.read_u8(raw_code)) return false;
    out_code = static_cast<CccasterUdpControlCode>(raw_code);
    return true;
}

std::vector<uint8_t> serialize_ping(uint64_t send_ms) {
    std::vector<uint8_t> out;
    out.reserve(8u);
    write_u64(out, send_ms);
    return out;
}

bool deserialize_ping(const std::vector<uint8_t>& body, uint64_t& out_send_ms) noexcept {
    ByteReader r(body);
    return r.read_u64(out_send_ms);
}

std::vector<uint8_t> serialize_version_config(const WireVersionConfig& msg) {
    std::vector<uint8_t> out;
    out.reserve(64u);
    write_u32(out, msg.seq_id);
    write_u8(out, static_cast<uint8_t>(msg.mode));
    write_u8(out, msg.flags);
    write_len_str(out, msg.version_str);
    write_len_str(out, msg.commit_str);
    write_len_str(out, msg.build_date_str);
    return out;
}

bool deserialize_version_config(const std::vector<uint8_t>& body, WireVersionConfig& out) {
    ByteReader r(body);
    uint8_t raw_mode = 0u;
    if (!r.read_u32(out.seq_id) ||
        !r.read_u8(raw_mode) ||
        !r.read_u8(out.flags) ||
        !r.read_len_str(out.version_str) ||
        !r.read_len_str(out.commit_str) ||
        !r.read_len_str(out.build_date_str)) {
        return false;
    }
    out.mode = static_cast<CccasterClientMode>(raw_mode);
    return true;
}

std::vector<uint8_t> serialize_initial_config(const WireInitialConfig& msg) {
    std::vector<uint8_t> out;
    out.reserve(64u);
    write_u32(out, msg.seq_id);
    write_u8(out, static_cast<uint8_t>(msg.mode));
    write_u8(out, msg.flags);
    write_u16(out, msg.spectate_port);
    write_len_str(out, msg.local_name);
    write_len_str(out, msg.remote_name);
    write_u8(out, msg.extra_flag);
    return out;
}

bool deserialize_initial_config(const std::vector<uint8_t>& body, WireInitialConfig& out) {
    ByteReader r(body);
    uint8_t raw_mode = 0u;
    if (!r.read_u32(out.seq_id) ||
        !r.read_u8(raw_mode) ||
        !r.read_u8(out.flags) ||
        !r.read_u16(out.spectate_port) ||
        !r.read_len_str(out.local_name) ||
        !r.read_len_str(out.remote_name) ||
        !r.read_u8(out.extra_flag)) {
        return false;
    }
    out.mode = static_cast<CccasterClientMode>(raw_mode);
    return true;
}

std::vector<uint8_t> serialize_netplay_config(const WireNetplayConfig& msg) {
    std::vector<uint8_t> out;
    out.reserve(96u);
    write_u32(out, msg.seq_id);
    write_u8(out, static_cast<uint8_t>(msg.mode));
    write_u8(out, msg.flags);
    write_u8(out, msg.delay);
    write_u8(out, msg.rollback);
    write_u8(out, msg.sub_byte_3e);
    write_u8(out, msg.sub_byte_3f);
    write_u8(out, msg.host_side);
    write_u16(out, msg.sub_word_42);
    write_len_str(out, msg.p1_name);
    write_len_str(out, msg.p2_name);
    write_len_str(out, msg.session_tag);
    write_len_str(out, msg.extra_tag);
    write_u32(out, msg.tail_word_a4);
    return out;
}

bool deserialize_netplay_config(const std::vector<uint8_t>& body, WireNetplayConfig& out) {
    ByteReader r(body);
    uint8_t raw_mode = 0u;
    if (!r.read_u32(out.seq_id) ||
        !r.read_u8(raw_mode) ||
        !r.read_u8(out.flags) ||
        !r.read_u8(out.delay) ||
        !r.read_u8(out.rollback) ||
        !r.read_u8(out.sub_byte_3e) ||
        !r.read_u8(out.sub_byte_3f) ||
        !r.read_u8(out.host_side) ||
        !r.read_u16(out.sub_word_42) ||
        !r.read_len_str(out.p1_name) ||
        !r.read_len_str(out.p2_name) ||
        !r.read_len_str(out.session_tag) ||
        !r.read_len_str(out.extra_tag) ||
        !r.read_u32(out.tail_word_a4)) {
        return false;
    }
    out.mode = static_cast<CccasterClientMode>(raw_mode);
    return true;
}

std::vector<uint8_t> serialize_spectate_config(const WireSpectateConfig& msg) {
    std::vector<uint8_t> out;
    out.reserve(96u);
    write_u32(out, msg.seq_id);
    write_u8(out, static_cast<uint8_t>(msg.mode));
    write_u8(out, msg.flags);
    write_u8(out, msg.delay);
    write_u8(out, msg.rollback);
    write_u8(out, msg.sub_byte_3e);
    write_u8(out, msg.sub_byte_3f);
    write_len_str(out, msg.p1_name);
    write_len_str(out, msg.p2_name);
    write_len_str(out, msg.session_tag);
    write_bytes(out, msg.state_header8.data(), msg.state_header8.size());
    write_u32(out, msg.stage);
    write_u8(out, msg.state_u8_b4);
    write_u8(out, msg.state_u8_b5);
    write_u16(out, msg.chara_word);
    write_u16(out, msg.moon_word);
    write_u16(out, msg.color_word);
    return out;
}

bool deserialize_spectate_config(const std::vector<uint8_t>& body, WireSpectateConfig& out) {
    ByteReader r(body);
    uint8_t raw_mode = 0u;
    if (!r.read_u32(out.seq_id) ||
        !r.read_u8(raw_mode) ||
        !r.read_u8(out.flags) ||
        !r.read_u8(out.delay) ||
        !r.read_u8(out.rollback) ||
        !r.read_u8(out.sub_byte_3e) ||
        !r.read_u8(out.sub_byte_3f) ||
        !r.read_len_str(out.p1_name) ||
        !r.read_len_str(out.p2_name) ||
        !r.read_len_str(out.session_tag) ||
        !r.read_bytes(out.state_header8.data(), out.state_header8.size()) ||
        !r.read_u32(out.stage) ||
        !r.read_u8(out.state_u8_b4) ||
        !r.read_u8(out.state_u8_b5) ||
        !r.read_u16(out.chara_word) ||
        !r.read_u16(out.moon_word) ||
        !r.read_u16(out.color_word)) {
        return false;
    }
    out.mode = static_cast<CccasterClientMode>(raw_mode);
    return true;
}

std::vector<uint8_t> serialize_confirm_config(uint32_t seq_id) {
    return serialize_ack_sequence(seq_id);
}

bool deserialize_confirm_config(const std::vector<uint8_t>& body, uint32_t& out_seq_id) noexcept {
    return deserialize_ack_sequence(body, out_seq_id);
}

std::vector<uint8_t> serialize_error_message(uint32_t seq_id, const std::string& message) {
    std::vector<uint8_t> out;
    out.reserve(8u + message.size());
    write_u32(out, seq_id);
    write_len_str(out, message);
    return out;
}

bool deserialize_error_message(const std::vector<uint8_t>& body,
                               uint32_t& out_seq_id,
                               std::string& out_message) {
    ByteReader r(body);
    return r.read_u32(out_seq_id) && r.read_len_str(out_message);
}

std::vector<uint8_t> serialize_change_config(const WireChangeConfig& msg) {
    std::vector<uint8_t> out;
    out.reserve(16u);
    write_u32(out, msg.seq_id);
    write_u8(out, static_cast<uint8_t>(msg.kind));
    write_bytes(out, msg.payload8.data(), msg.payload8.size());
    write_u8(out, msg.delay);
    write_u8(out, msg.p2_delay);
    write_u8(out, msg.rollback);
    return out;
}

bool deserialize_change_config(const std::vector<uint8_t>& body, WireChangeConfig& out) noexcept {
    ByteReader r(body);
    uint8_t raw_kind = 0u;
    if (!r.read_u32(out.seq_id) ||
        !r.read_u8(raw_kind) ||
        !r.read_bytes(out.payload8.data(), out.payload8.size()) ||
        !r.read_u8(out.delay) ||
        !r.read_u8(out.p2_delay) ||
        !r.read_u8(out.rollback)) {
        return false;
    }
    out.kind = static_cast<CccasterChangeKind>(raw_kind);
    return true;
}

std::vector<uint8_t> serialize_initial_game_state(const WireInitialGameState& msg) {
    std::vector<uint8_t> out;
    out.reserve(24u);
    write_u32(out, msg.seq_id);
    write_bytes(out, msg.header8.data(), msg.header8.size());
    write_u32(out, msg.stage);
    write_u8(out, msg.round_flags);
    write_u8(out, msg.unk_2d);
    write_u8(out, msg.chara0);
    write_u8(out, msg.chara1);
    write_u8(out, msg.moon0);
    write_u8(out, msg.moon1);
    write_u8(out, msg.color0);
    write_u8(out, msg.color1);
    return out;
}

bool deserialize_initial_game_state(const std::vector<uint8_t>& body,
                                     WireInitialGameState& out) noexcept {
    ByteReader r(body);
    return r.read_u32(out.seq_id) &&
           r.read_bytes(out.header8.data(), out.header8.size()) &&
           r.read_u32(out.stage) &&
           r.read_u8(out.round_flags) &&
           r.read_u8(out.unk_2d) &&
           r.read_u8(out.chara0) &&
           r.read_u8(out.chara1) &&
           r.read_u8(out.moon0) &&
           r.read_u8(out.moon1) &&
           r.read_u8(out.color0) &&
           r.read_u8(out.color1);
}

std::vector<uint8_t> serialize_menu_index(const WireMenuIndex& msg) {
    std::vector<uint8_t> out;
    out.reserve(9u);
    write_u32(out, msg.seq_id);
    write_u32(out, msg.indexed_frame);
    write_u8(out, static_cast<uint8_t>(msg.menu_choice));
    return out;
}

bool deserialize_menu_index(const std::vector<uint8_t>& body, WireMenuIndex& out) noexcept {
    ByteReader r(body);
    return r.read_u32(out.seq_id) &&
           r.read_u32(out.indexed_frame) &&
           r.read_i8(out.menu_choice);
}

std::vector<uint8_t> serialize_transition_index(uint32_t transition_id) {
    std::vector<uint8_t> out;
    out.reserve(4u);
    write_u32(out, transition_id);
    return out;
}

bool deserialize_transition_index(const std::vector<uint8_t>& body,
                                  uint32_t& out_transition_id) noexcept {
    ByteReader r(body);
    return r.read_u32(out_transition_id);
}

std::vector<uint8_t> serialize_split_message(const WireSplitMessage& msg) {
    std::vector<uint8_t> out;
    out.reserve(17u + msg.chunk.size());
    write_u32(out, msg.seq_id);
    write_u8(out, static_cast<uint8_t>(msg.orig_msg_type));
    write_u32(out, msg.part_idx);
    write_u32(out, msg.total_parts);
    const size_t n = std::min(msg.chunk.size(), static_cast<size_t>(kCccasterMaxChunkBytes));
    write_u32(out, static_cast<uint32_t>(n));
    write_bytes(out, msg.chunk.data(), n);
    return out;
}

bool deserialize_split_message(const std::vector<uint8_t>& body, WireSplitMessage& out) {
    ByteReader r(body);
    uint8_t raw_orig = 0u;
    if (!r.read_u32(out.seq_id) ||
        !r.read_u8(raw_orig) ||
        !r.read_u32(out.part_idx) ||
        !r.read_u32(out.total_parts) ||
        !r.read_len_vec(out.chunk, kCccasterMaxChunkBytes)) {
        return false;
    }
    out.orig_msg_type = static_cast<CccasterMsgType>(raw_orig);
    return out.total_parts > 0u && out.part_idx < out.total_parts;
}

void patch_seq_id(std::vector<uint8_t>& body, uint32_t seq_id) noexcept {
    if (body.size() < 4u) return;
    body[0] = static_cast<uint8_t>(seq_id & 0xFFu);
    body[1] = static_cast<uint8_t>((seq_id >> 8) & 0xFFu);
    body[2] = static_cast<uint8_t>((seq_id >> 16) & 0xFFu);
    body[3] = static_cast<uint8_t>((seq_id >> 24) & 0xFFu);
}

bool is_valid_msg_type(uint8_t v) noexcept {
    return v >= static_cast<uint8_t>(CccasterMsgType::AckSequence) &&
           v <= static_cast<uint8_t>(CccasterMsgType::PaletteManager);
}

std::vector<std::string> split_dots(const std::string& s) {
    std::vector<std::string> parts;
    size_t start = 0u;
    while (start <= s.size()) {
        const size_t dot = s.find('.', start);
        if (dot == std::string::npos) {
            parts.push_back(s.substr(start));
            break;
        }
        parts.push_back(s.substr(start, dot - start));
        start = dot + 1u;
    }
    return parts;
}

// -----------------------------------------------------------------------------
// Cross-Platform Non-Blocking UDP Socket Wrapper
// -----------------------------------------------------------------------------

#if defined(_WIN32)
struct WsaRuntime {
    bool ok = false;
    WsaRuntime() noexcept {
        WSADATA wsa{};
        ok = (WSAStartup(MAKEWORD(2, 2), &wsa) == 0);
    }
    ~WsaRuntime() {
        if (ok) {
            WSACleanup();
        }
    }
};
using NativeSocket = SOCKET;
constexpr NativeSocket kInvalidSocket = INVALID_SOCKET;
#else
using NativeSocket = int;
constexpr NativeSocket kInvalidSocket = -1;
#endif

struct IpEndpoint {
    uint32_t addr_be = 0u; // Network byte order
    uint16_t port_be = 0u; // Network byte order

    [[nodiscard]] bool valid() const noexcept {
        return addr_be != 0u && port_be != 0u;
    }

    bool operator==(const IpEndpoint& rhs) const noexcept {
        return addr_be == rhs.addr_be && port_be == rhs.port_be;
    }

    [[nodiscard]] std::string to_string() const {
        if (!valid()) return "";
        in_addr a{};
        a.s_addr = addr_be;
        char buf[INET_ADDRSTRLEN]{};
        if (!inet_ntop(AF_INET, &a, buf, sizeof(buf))) return "";
        const uint16_t host_port = ntohs(port_be);
        return std::string(buf) + ":" + std::to_string(host_port);
    }

    [[nodiscard]] sockaddr_in to_sockaddr() const noexcept {
        sockaddr_in sa{};
        sa.sin_family = AF_INET;
        sa.sin_addr.s_addr = addr_be;
        sa.sin_port = port_be;
        return sa;
    }

    static IpEndpoint from_sockaddr(const sockaddr_in& sa) noexcept {
        return IpEndpoint{sa.sin_addr.s_addr, sa.sin_port};
    }
};

class UdpSocket {
public:
    UdpSocket() = default;
    ~UdpSocket() { close(); }

    UdpSocket(const UdpSocket&) = delete;
    UdpSocket& operator=(const UdpSocket&) = delete;

    [[nodiscard]] bool is_open() const noexcept { return fd_ != kInvalidSocket; }

    void close() noexcept {
        if (fd_ != kInvalidSocket) {
#if defined(_WIN32)
            closesocket(fd_);
#else
            ::close(fd_);
#endif
            fd_ = kInvalidSocket;
        }
        bound_port_ = 0u;
    }

    bool open_udp(uint16_t bind_port, bool reuse_addr, std::string& err) {
        close();
#if defined(_WIN32)
        static const WsaRuntime wsa_guard;
        if (!wsa_guard.ok) {
            err = "WSAStartup failed";
            return false;
        }
#endif
        const NativeSocket s = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (s == kInvalidSocket) {
            err = "socket(AF_INET, SOCK_DGRAM) failed";
            return false;
        }

        if (reuse_addr) {
            const int yes = 1;
            ::setsockopt(s, SOL_SOCKET, SO_REUSEADDR,
                         reinterpret_cast<const char*>(&yes), sizeof(yes));
        }

#if defined(__APPLE__) && defined(SO_NOSIGPIPE)
        {
            const int yes = 1;
            ::setsockopt(s, SOL_SOCKET, SO_NOSIGPIPE, &yes, sizeof(yes));
        }
#endif

        // Increase socket buffers cleanly when permitted by OS.
        {
            const int rcv_sz = 262144;
            const int snd_sz = 262144;
            ::setsockopt(s, SOL_SOCKET, SO_RCVBUF,
                         reinterpret_cast<const char*>(&rcv_sz), sizeof(rcv_sz));
            ::setsockopt(s, SOL_SOCKET, SO_SNDBUF,
                         reinterpret_cast<const char*>(&snd_sz), sizeof(snd_sz));
        }

#if defined(_WIN32)
        {
            u_long nonblock = 1u;
            if (ioctlsocket(s, FIONBIO, &nonblock) != 0) {
                closesocket(s);
                err = "ioctlsocket(FIONBIO) failed";
                return false;
            }
        }
#else
        {
            const int flags = ::fcntl(s, F_GETFL, 0);
            if (flags < 0 || ::fcntl(s, F_SETFL, flags | O_NONBLOCK) < 0) {
                ::close(s);
                err = "fcntl(O_NONBLOCK) failed";
                return false;
            }
        }
#endif

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(bind_port);

        if (::bind(s, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr)) != 0) {
#if defined(_WIN32)
            closesocket(s);
#else
            ::close(s);
#endif
            err = "bind(UDP :" + std::to_string(bind_port) + ") failed";
            return false;
        }

        sockaddr_in local_sa{};
        socklen_t sa_len = static_cast<socklen_t>(sizeof(local_sa));
        if (::getsockname(s, reinterpret_cast<sockaddr*>(&local_sa), &sa_len) == 0) {
            bound_port_ = ntohs(local_sa.sin_port);
        } else {
            bound_port_ = bind_port;
        }

        fd_ = s;
        return true;
    }

    bool send_to(const IpEndpoint& dst, const uint8_t* data, size_t len) const noexcept {
        if (fd_ == kInvalidSocket || !dst.valid() || !data || len == 0u) return false;
        const sockaddr_in sa = dst.to_sockaddr();
#if defined(_WIN32)
        const int sent = ::sendto(fd_, reinterpret_cast<const char*>(data),
                                  static_cast<int>(len), 0,
                                  reinterpret_cast<const sockaddr*>(&sa),
                                  static_cast<int>(sizeof(sa)));
        return sent == static_cast<int>(len);
#else
        const ssize_t sent = ::sendto(fd_, data, len, 0,
                                      reinterpret_cast<const sockaddr*>(&sa),
                                      static_cast<socklen_t>(sizeof(sa)));
        return sent == static_cast<ssize_t>(len);
#endif
    }

    // Returns > 0 packet length, 0 if would-block / EAGAIN, < 0 on fatal socket error.
    int recv_from(uint8_t* buf, size_t cap, IpEndpoint& out_src) const noexcept {
        if (fd_ == kInvalidSocket || !buf || cap == 0u) return 0;
        sockaddr_in sa{};
        socklen_t sa_len = static_cast<socklen_t>(sizeof(sa));
#if defined(_WIN32)
        const int n = ::recvfrom(fd_, reinterpret_cast<char*>(buf), static_cast<int>(cap), 0,
                                 reinterpret_cast<sockaddr*>(&sa), &sa_len);
        if (n < 0) {
            const int e = WSAGetLastError();
            if (e == WSAEWOULDBLOCK || e == WSAEINTR || e == WSAECONNRESET) return 0;
            return -1;
        }
#else
        const ssize_t n = ::recvfrom(fd_, buf, cap, 0,
                                     reinterpret_cast<sockaddr*>(&sa), &sa_len);
        if (n < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR || errno == ECONNREFUSED) {
                return 0;
            }
            return -1;
        }
#endif
        if (sa.sin_family != AF_INET) return 0;
        out_src = IpEndpoint::from_sockaddr(sa);
        return static_cast<int>(n);
    }

    [[nodiscard]] uint16_t bound_port() const noexcept { return bound_port_; }

private:
    NativeSocket fd_         = kInvalidSocket;
    uint16_t     bound_port_ = 0u;
};

bool resolve_ipv4_endpoint(const std::string& host_or_ip,
                           uint16_t port,
                           IpEndpoint& out,
                           std::string& err) {
    if (host_or_ip.empty() || port == 0u) {
        err = "Invalid peer host or port";
        return false;
    }

#if defined(_WIN32)
    static const WsaRuntime wsa_guard;
    if (!wsa_guard.ok) {
        err = "WSAStartup failed";
        return false;
    }
#endif

    in_addr direct{};
    if (::inet_pton(AF_INET, host_or_ip.c_str(), &direct) == 1) {
        out.addr_be = direct.s_addr;
        out.port_be = htons(port);
        return true;
    }

    addrinfo hints{};
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    addrinfo* res     = nullptr;
    const std::string port_str = std::to_string(port);
    const int gai = ::getaddrinfo(host_or_ip.c_str(), port_str.c_str(), &hints, &res);
    if (gai != 0 || !res) {
        if (res) ::freeaddrinfo(res);
        err = "Failed to resolve IPv4 peer '" + host_or_ip + "'";
        return false;
    }

    bool found = false;
    for (addrinfo* cur = res; cur != nullptr; cur = cur->ai_next) {
        if (cur->ai_family == AF_INET && cur->ai_addr && cur->ai_addrlen >= sizeof(sockaddr_in)) {
            const auto* sa = reinterpret_cast<const sockaddr_in*>(cur->ai_addr);
            out.addr_be = sa->sin_addr.s_addr;
            out.port_be = htons(port);
            found = true;
            break;
        }
    }
    ::freeaddrinfo(res);

    if (!found) {
        err = "No IPv4 address for '" + host_or_ip + "'";
    }
    return found;
}

// -----------------------------------------------------------------------------
// Reusable GoBackN Link State (shared between P2P peer & Spectator streams)
// -----------------------------------------------------------------------------

struct PendingReliablePacket {
    uint32_t             seq_id        = 0u;
    std::vector<uint8_t> wire_bytes;
    uint64_t             first_sent_ms = 0u;
    uint64_t             last_sent_ms  = 0u;
};

class GoBackNLink {
public:
    bool send_reliable(const UdpSocket& sock,
                       const IpEndpoint& dst,
                       CccasterMsgType type,
                       std::vector<uint8_t> body,
                       uint64_t now_ms) {
        return send_reliable_impl(sock, dst, type, std::move(body), now_ms);
    }

    bool send_unreliable(const UdpSocket& sock,
                         const IpEndpoint& dst,
                         CccasterMsgType type,
                         const std::vector<uint8_t>& body) const {
        const std::vector<uint8_t> pkt = cccaster_encode_packet(type, body, 9);
        return sock.send_to(dst, pkt.data(), pkt.size());
    }

    void send_disconnect_3x(const UdpSocket& sock, const IpEndpoint& dst) const {
        const std::vector<uint8_t> body =
            serialize_udp_control(0u, CccasterUdpControlCode::Disconnect);
        const std::vector<uint8_t> pkt =
            cccaster_encode_packet(CccasterMsgType::UdpControl, body, 9);
        for (int i = 0; i < 3; ++i) {
            (void)sock.send_to(dst, pkt.data(), pkt.size());
        }
    }

    void reset(uint64_t now_ms) {
        next_send_seq_        = 0u;
        last_recv_seq_        = 0u;
        last_acked_seq_       = 0u;
        split_expected_parts_ = 0u;
        split_next_part_      = 0u;
        split_orig_type_      = CccasterMsgType::AckSequence;
        split_buf_.clear();
        send_queue_.clear();
        last_activity_ms_     = now_ms;
    }

    // Returns false iff a queued reliable packet exceeded kCccasterTimeoutMs (20000 ms).
    bool tick_resends(const UdpSocket& sock, const IpEndpoint& dst, uint64_t now_ms) {
        if (send_queue_.empty()) return true;
        const PendingReliablePacket& front = send_queue_.front();
        if (now_ms >= front.first_sent_ms &&
            (now_ms - front.first_sent_ms) >= kCccasterTimeoutMs) {
            return false;
        }
        for (PendingReliablePacket& pkt : send_queue_) {
            if (now_ms >= pkt.last_sent_ms &&
                (now_ms - pkt.last_sent_ms) >= kCccasterResendMs) {
                (void)sock.send_to(dst, pkt.wire_bytes.data(), pkt.wire_bytes.size());
                pkt.last_sent_ms = now_ms;
            }
        }
        return true;
    }

    template <typename DispatchFn>
    void handle_packet(const UdpSocket& sock,
                       const IpEndpoint& src,
                       const uint8_t* data,
                       size_t len,
                       uint64_t now_ms,
                       bool allow_initial_seq1_reset,
                       DispatchFn&& dispatch) {
        CccasterMsgType msg_type = CccasterMsgType::AckSequence;
        std::vector<uint8_t> body;
        if (!cccaster_decode_packet(data, len, msg_type, body)) {
            return;
        }
        last_activity_ms_ = now_ms;

        if (!cccaster_is_sequence_msg(msg_type)) {
            dispatch(msg_type, body);
            return;
        }

        // UdpControl::Disconnect bypasses GoBackN sequence gating cleanly.
        if (msg_type == CccasterMsgType::UdpControl) {
            uint32_t seq_id = 0u;
            CccasterUdpControlCode code = CccasterUdpControlCode::Unknown;
            if (deserialize_udp_control(body, seq_id, code) &&
                code == CccasterUdpControlCode::Disconnect) {
                dispatch(msg_type, body);
                return;
            }
        }

        if (body.size() < 4u) return;
        uint32_t seq_id = 0u;
        {
            ByteReader r(body);
            if (!r.read_u32(seq_id)) return;
        }

        if (msg_type == CccasterMsgType::AckSequence) {
            if (seq_id > last_acked_seq_) {
                last_acked_seq_ = seq_id;
            }
            while (!send_queue_.empty() && send_queue_.front().seq_id <= last_acked_seq_) {
                send_queue_.pop_front();
            }
            return;
        }

        // Listening Host accepts fresh ConnectRequest(seqId=1) by resetting receive cursor.
        if (allow_initial_seq1_reset &&
            msg_type == CccasterMsgType::UdpControl &&
            seq_id == 1u) {
            uint32_t tmp_seq = 0u;
            CccasterUdpControlCode code = CccasterUdpControlCode::Unknown;
            if (deserialize_udp_control(body, tmp_seq, code) &&
                code == CccasterUdpControlCode::ConnectRequest) {
                reset(now_ms);
            }
        }

        const uint32_t expected_seq = last_recv_seq_ + 1u;
        if (seq_id != expected_seq) {
            // Re-ACK highest contiguous received sequence so sender recovers fast.
            send_ack(sock, src, last_recv_seq_);
            return;
        }

        last_recv_seq_ = seq_id;
        send_ack(sock, src, last_recv_seq_);

        if (msg_type == CccasterMsgType::SplitMessage) {
            handle_split_chunk(body, dispatch);
            return;
        }

        dispatch(msg_type, body);
    }

    [[nodiscard]] uint64_t last_activity_ms() const noexcept { return last_activity_ms_; }

private:
    bool send_reliable_impl(const UdpSocket& sock,
                            const IpEndpoint& dst,
                            CccasterMsgType type,
                            std::vector<uint8_t> body,
                            uint64_t now_ms) {
        if (body.size() < 4u) return false;

        // CCCaster 0x0045b2b0 assigns (nextSendSeq + 1) to the outer message before encoding,
        // then advances nextSendSeq either once (single packet <= 256B) or once per SplitMessage part.
        patch_seq_id(body, next_send_seq_ + 1u);
        std::vector<uint8_t> encoded = cccaster_encode_packet(type, body, 9);

        if (encoded.size() <= kCccasterMaxChunkBytes) {
            ++next_send_seq_;
            PendingReliablePacket item;
            item.seq_id        = next_send_seq_;
            item.wire_bytes    = std::move(encoded);
            item.first_sent_ms = now_ms;
            item.last_sent_ms  = now_ms;
            const bool sent = sock.send_to(dst, item.wire_bytes.data(), item.wire_bytes.size());
            send_queue_.push_back(std::move(item));
            return sent;
        }

        const uint32_t total_parts = static_cast<uint32_t>(
            (encoded.size() + kCccasterMaxChunkBytes - 1u) / kCccasterMaxChunkBytes);
        bool all_sent = true;
        for (uint32_t idx = 0u; idx < total_parts; ++idx) {
            const size_t offset = static_cast<size_t>(idx) * kCccasterMaxChunkBytes;
            const size_t chunk_len =
                std::min(static_cast<size_t>(kCccasterMaxChunkBytes), encoded.size() - offset);

            ++next_send_seq_;
            WireSplitMessage split;
            split.seq_id        = next_send_seq_;
            split.orig_msg_type = type;
            split.part_idx      = idx;
            split.total_parts   = total_parts;
            split.chunk.assign(encoded.begin() + static_cast<std::ptrdiff_t>(offset),
                               encoded.begin() + static_cast<std::ptrdiff_t>(offset + chunk_len));

            std::vector<uint8_t> split_wire = cccaster_encode_packet(
                CccasterMsgType::SplitMessage, serialize_split_message(split), 9);

            PendingReliablePacket item;
            item.seq_id        = next_send_seq_;
            item.wire_bytes    = std::move(split_wire);
            item.first_sent_ms = now_ms;
            item.last_sent_ms  = now_ms;
            if (!sock.send_to(dst, item.wire_bytes.data(), item.wire_bytes.size())) {
                all_sent = false;
            }
            send_queue_.push_back(std::move(item));
        }
        return all_sent;
    }

    void send_ack(const UdpSocket& sock, const IpEndpoint& dst, uint32_t seq_id) const {
        const std::vector<uint8_t> pkt = cccaster_encode_packet(
            CccasterMsgType::AckSequence, serialize_ack_sequence(seq_id), 9);
        (void)sock.send_to(dst, pkt.data(), pkt.size());
    }

    template <typename DispatchFn>
    void handle_split_chunk(const std::vector<uint8_t>& body, DispatchFn&& dispatch) {
        WireSplitMessage split;
        if (!deserialize_split_message(body, split)) {
            split_buf_.clear();
            split_expected_parts_ = 0u;
            split_next_part_ = 0u;
            return;
        }

        if (split.part_idx == 0u) {
            split_orig_type_      = split.orig_msg_type;
            split_expected_parts_ = split.total_parts;
            split_next_part_      = 0u;
            split_buf_.clear();
        }

        if (split.orig_msg_type != split_orig_type_ ||
            split.total_parts != split_expected_parts_ ||
            split.part_idx != split_next_part_) {
            split_buf_.clear();
            split_expected_parts_ = 0u;
            split_next_part_ = 0u;
            return;
        }

        if (split_buf_.size() + split.chunk.size() > kCccasterMaxWirePacket) {
            split_buf_.clear();
            split_expected_parts_ = 0u;
            split_next_part_ = 0u;
            return;
        }

        split_buf_.insert(split_buf_.end(), split.chunk.begin(), split.chunk.end());
        ++split_next_part_;

        if (split_next_part_ == split_expected_parts_) {
            CccasterMsgType decoded_type = CccasterMsgType::AckSequence;
            std::vector<uint8_t> decoded_body;
            const bool ok = cccaster_decode_packet(
                split_buf_.data(), split_buf_.size(), decoded_type, decoded_body);
            const CccasterMsgType expected_orig = split_orig_type_;
            split_buf_.clear();
            split_expected_parts_ = 0u;
            split_next_part_ = 0u;
            if (ok && decoded_type == expected_orig) {
                dispatch(decoded_type, decoded_body);
            }
        }
    }

    uint32_t                        next_send_seq_        = 0u;
    uint32_t                        last_recv_seq_        = 0u;
    uint32_t                        last_acked_seq_       = 0u;
    CccasterMsgType                 split_orig_type_      = CccasterMsgType::AckSequence;
    uint32_t                        split_expected_parts_ = 0u;
    uint32_t                        split_next_part_      = 0u;
    std::vector<uint8_t>            split_buf_;
    std::deque<PendingReliablePacket> send_queue_;
    uint64_t                        last_activity_ms_     = 0u;
};

template <typename T>
void push_bounded(std::deque<T>& q, T value) {
    if (q.size() >= kMaxEventQueueDepth) {
        q.pop_front();
    }
    q.push_back(std::move(value));
}

template <typename T>
bool pop_front_item(std::deque<T>& q, T& out) {
    if (q.empty()) return false;
    out = std::move(q.front());
    q.pop_front();
    return true;
}

void prune_old_inputs(std::unordered_map<uint32_t, uint16_t>& map, uint32_t latest_frame) {
    if (map.size() <= kMaxInputCacheFrames) return;
    const uint32_t cutoff = (latest_frame > kMaxInputCacheFrames)
                                ? (latest_frame - static_cast<uint32_t>(kMaxInputCacheFrames))
                                : 0u;
    for (auto it = map.begin(); it != map.end();) {
        if (it->first < cutoff) {
            it = map.erase(it);
        } else {
            ++it;
        }
    }
}

void prune_old_spectate(std::unordered_map<uint32_t, std::pair<uint16_t, uint16_t>>& map,
                        uint32_t latest_frame) {
    if (map.size() <= kMaxInputCacheFrames) return;
    const uint32_t cutoff = (latest_frame > kMaxInputCacheFrames)
                                ? (latest_frame - static_cast<uint32_t>(kMaxInputCacheFrames))
                                : 0u;
    for (auto it = map.begin(); it != map.end();) {
        if (it->first < cutoff) {
            it = map.erase(it);
        } else {
            ++it;
        }
    }
}

} // namespace

// -----------------------------------------------------------------------------
// CccasterStatistics Implementation (Welford + oneWayMs = rttMs >> 1)
// -----------------------------------------------------------------------------

void CccasterStatistics::reset() noexcept {
    sample_count    = 0u;
    max_one_way_ms  = 0.0;
    mean_one_way_ms = 0.0;
    welford_m2      = 0.0;
    loss_percent    = 0u;
}

void CccasterStatistics::record_rtt_ms(uint64_t rtt_ms) noexcept {
    // Verified at 0x00479948: 64-bit unsigned right shift by 1 before float conversion.
    const double one_way = static_cast<double>(rtt_ms >> 1u);
    ++sample_count;
    if (sample_count == 1u || one_way > max_one_way_ms) {
        max_one_way_ms = one_way;
    }
    const double delta = one_way - mean_one_way_ms;
    mean_one_way_ms += delta / static_cast<double>(sample_count);
    const double delta2 = one_way - mean_one_way_ms;
    welford_m2 += delta * delta2;
}

double CccasterStatistics::stddev_ms() const noexcept {
    if (sample_count < 2u || welford_m2 <= 0.0) return 0.0;
    return std::sqrt(welford_m2 / static_cast<double>(sample_count - 1u));
}

uint16_t CccasterStatistics::auto_delay(bool is_host_initial) const noexcept {
    return cccaster_compute_auto_delay(mean_one_way_ms, is_host_initial);
}

// -----------------------------------------------------------------------------
// Free Helpers: Local IPv4, MD5, Framing, Version Check, Sanitizer, Auto-Delay
// -----------------------------------------------------------------------------

std::string cccaster_get_local_ipv4() {
#if defined(_WIN32)
    static const WsaRuntime wsa_guard;
    if (!wsa_guard.ok) return "127.0.0.1";
    char hostname[256]{};
    if (::gethostname(hostname, sizeof(hostname)) != 0) return "127.0.0.1";
    addrinfo hints{};
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    addrinfo* res     = nullptr;
    if (::getaddrinfo(hostname, nullptr, &hints, &res) != 0 || !res) {
        if (res) ::freeaddrinfo(res);
        return "127.0.0.1";
    }
    std::string chosen = "127.0.0.1";
    for (addrinfo* cur = res; cur != nullptr; cur = cur->ai_next) {
        if (cur->ai_family == AF_INET && cur->ai_addr) {
            const auto* sa = reinterpret_cast<const sockaddr_in*>(cur->ai_addr);
            const uint32_t host_ip = ntohl(sa->sin_addr.s_addr);
            if ((host_ip >> 24) == 127u) continue;
            char buf[INET_ADDRSTRLEN]{};
            if (::inet_ntop(AF_INET, &sa->sin_addr, buf, sizeof(buf))) {
                chosen = buf;
                break;
            }
        }
    }
    ::freeaddrinfo(res);
    return chosen;
#else
    ifaddrs* ifap = nullptr;
    if (::getifaddrs(&ifap) != 0 || !ifap) {
        return "127.0.0.1";
    }

    std::string preferred_lan;
    std::string fallback_non_loopback;
    std::string fallback_link_local;

    for (ifaddrs* ifa = ifap; ifa != nullptr; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr || ifa->ifa_addr->sa_family != AF_INET) continue;
        if ((ifa->ifa_flags & IFF_UP) == 0u) continue;
        if ((ifa->ifa_flags & IFF_LOOPBACK) != 0u) continue;

        const auto* sa = reinterpret_cast<const sockaddr_in*>(ifa->ifa_addr);
        const uint32_t host_ip = ntohl(sa->sin_addr.s_addr);
        if (host_ip == 0u || (host_ip >> 24) == 127u) continue;

        char buf[INET_ADDRSTRLEN]{};
        if (!::inet_ntop(AF_INET, &sa->sin_addr, buf, sizeof(buf))) continue;

        const bool is_link_local = ((host_ip >> 16) == 0xA9FEu); // 169.254.0.0/16
        if (is_link_local) {
            if (fallback_link_local.empty()) {
                fallback_link_local = buf;
            }
            continue;
        }

        const char* name = ifa->ifa_name ? ifa->ifa_name : "";
        const bool is_primary_nic =
            (std::strncmp(name, "en", 2) == 0) ||
            (std::strncmp(name, "eth", 3) == 0) ||
            (std::strncmp(name, "wlan", 4) == 0);
        if (is_primary_nic && preferred_lan.empty()) {
            preferred_lan = buf;
        } else if (fallback_non_loopback.empty()) {
            fallback_non_loopback = buf;
        }
    }

    ::freeifaddrs(ifap);

    if (!preferred_lan.empty()) return preferred_lan;
    if (!fallback_non_loopback.empty()) return fallback_non_loopback;
    if (!fallback_link_local.empty()) return fallback_link_local;
    return "127.0.0.1";
#endif
}

std::array<uint8_t, 16> cccaster_md5(const uint8_t* data, size_t len) noexcept {
    std::array<uint32_t, 4> state = {
        0x67452301u, 0xefcdab89u, 0x98badcfeu, 0x10325476u
    };

    size_t offset = 0u;
    while (offset + 64u <= len) {
        md5_transform(state, data + offset);
        offset += 64u;
    }

    uint8_t tail[128]{};
    const size_t rem = len - offset;
    if (rem > 0u && data) {
        std::memcpy(tail, data + offset, rem);
    }
    tail[rem] = 0x80u;

    const size_t padded_len = (rem < 56u) ? 64u : 128u;
    const uint64_t bit_len = static_cast<uint64_t>(len) * 8u;
    for (size_t i = 0u; i < 8u; ++i) {
        tail[padded_len - 8u + i] = static_cast<uint8_t>((bit_len >> (i * 8u)) & 0xFFu);
    }

    md5_transform(state, tail);
    if (padded_len == 128u) {
        md5_transform(state, tail + 64u);
    }

    std::array<uint8_t, 16> digest{};
    for (size_t i = 0u; i < 4u; ++i) {
        digest[i * 4u + 0u] = static_cast<uint8_t>(state[i] & 0xFFu);
        digest[i * 4u + 1u] = static_cast<uint8_t>((state[i] >> 8) & 0xFFu);
        digest[i * 4u + 2u] = static_cast<uint8_t>((state[i] >> 16) & 0xFFu);
        digest[i * 4u + 3u] = static_cast<uint8_t>((state[i] >> 24) & 0xFFu);
    }
    return digest;
}

bool cccaster_is_sequence_msg(CccasterMsgType type) noexcept {
    switch (type) {
        case CccasterMsgType::KeyboardEvent:
        case CccasterMsgType::Ping:
        case CccasterMsgType::PlayerInputs:
        case CccasterMsgType::JoysticksChanged:
        case CccasterMsgType::TransitionIndex:
            return false;
        default:
            return true;
    }
}

bool cccaster_version_compatible(const std::string& remote_ver,
                                 const std::string& remote_build_date,
                                 bool strict_version) {
    // Verified at 0x00494f90: explicit legacy blacklist.
    if (remote_ver == "2.1e" || remote_ver == "3.0a.019" || remote_ver.empty()) {
        return false;
    }

    const auto local_parts  = split_dots(kCccasterVersionString);
    const auto remote_parts = split_dots(remote_ver);
    if (local_parts.size() < 2u || remote_parts.size() < 2u) {
        return false;
    }
    if (remote_parts[0] != local_parts[0] || remote_parts[1] != local_parts[1]) {
        return false;
    }
    if (strict_version) {
        if (local_parts.size() < 3u || remote_parts.size() < 3u) {
            return false;
        }
        if (remote_parts[2] != local_parts[2]) {
            return false;
        }
    }
    if (remote_ver.find("-custom") != std::string::npos &&
        remote_build_date != kCccasterBuildDate) {
        return false;
    }
    return true;
}

std::vector<uint8_t> cccaster_encode_packet(CccasterMsgType msg_type,
                                            const std::vector<uint8_t>& body,
                                            int zlib_level) {
    // Step 1: raw = body || MD5(body) (MD5 computed before compression, 0x0047bb40).
    const std::array<uint8_t, 16> digest = cccaster_md5(body.data(), body.size());
    std::vector<uint8_t> raw;
    raw.reserve(body.size() + 16u);
    write_bytes(raw, body.data(), body.size());
    write_bytes(raw, digest.data(), digest.size());

    const uint32_t raw_len = static_cast<uint32_t>(raw.size());

    // Step 2: zlib compression iff level != 0 && (compLen + 8) < rawLen (0x0047af89).
    if (zlib_level != 0) {
        const int clamped_level = std::clamp(zlib_level, 1, 9);
        uLongf comp_cap = ::compressBound(static_cast<uLong>(raw_len));
        std::vector<uint8_t> comp_buf(static_cast<size_t>(comp_cap));
        uLongf comp_len = comp_cap;
        const int zrc = ::compress2(comp_buf.data(), &comp_len,
                                    raw.data(), static_cast<uLong>(raw_len),
                                    clamped_level);
        if (zrc == Z_OK && static_cast<size_t>(comp_len) + 8u < static_cast<size_t>(raw_len)) {
            std::vector<uint8_t> out;
            out.reserve(10u + static_cast<size_t>(comp_len));
            write_u8(out, static_cast<uint8_t>(msg_type));
            write_u8(out, static_cast<uint8_t>(clamped_level));
            write_u32(out, raw_len);
            write_u32(out, static_cast<uint32_t>(comp_len));
            write_bytes(out, comp_buf.data(), static_cast<size_t>(comp_len));
            return out;
        }
    }

    // Uncompressed fallback: [msgType][0][body || MD5(body)]
    std::vector<uint8_t> out;
    out.reserve(2u + raw.size());
    write_u8(out, static_cast<uint8_t>(msg_type));
    write_u8(out, 0u);
    write_bytes(out, raw.data(), raw.size());
    return out;
}

bool cccaster_decode_packet(const uint8_t* data,
                            size_t len,
                            CccasterMsgType& out_type,
                            std::vector<uint8_t>& out_body,
                            bool* out_md5_ok) {
    if (out_md5_ok) *out_md5_ok = false;
    if (!data || len < 2u) return false;

    const uint8_t raw_type = data[0];
    if (!is_valid_msg_type(raw_type)) return false;
    out_type = static_cast<CccasterMsgType>(raw_type);

    const uint8_t comp_level = data[1];
    std::vector<uint8_t> raw;

    if (comp_level == 0u) {
        const size_t raw_len = len - 2u;
        if (raw_len < 16u || raw_len > kCccasterMaxWirePacket) return false;
        raw.assign(data + 2u, data + len);
    } else {
        if (len < 10u) return false;
        ByteReader hdr(data + 2u, len - 2u);
        uint32_t raw_len  = 0u;
        uint32_t comp_len = 0u;
        if (!hdr.read_u32(raw_len) || !hdr.read_u32(comp_len)) return false;
        if (raw_len < 16u || raw_len > kCccasterMaxWirePacket) return false;
        if (comp_len == 0u || static_cast<size_t>(comp_len) > len - 10u) return false;

        raw.resize(raw_len);
        uLongf dest_len = static_cast<uLongf>(raw_len);
        const int zrc = ::uncompress(raw.data(), &dest_len,
                                     data + 10u, static_cast<uLong>(comp_len));
        if (zrc != Z_OK || dest_len != static_cast<uLongf>(raw_len)) {
            return false;
        }
    }

    const size_t body_len = raw.size() - 16u;
    const std::array<uint8_t, 16> expected = cccaster_md5(raw.data(), body_len);
    const bool md5_match = (std::memcmp(expected.data(), raw.data() + body_len, 16u) == 0);
    if (out_md5_ok) *out_md5_ok = md5_match;
    if (!md5_match) return false;

    out_body.assign(raw.begin(), raw.begin() + static_cast<std::ptrdiff_t>(body_len));
    return true;
}

uint16_t cccaster_sanitize_input_word(uint16_t raw_word,
                                      bool mask_spectator_auto_confirm) noexcept {
    uint16_t dir = static_cast<uint16_t>(raw_word & kCccasterDirMask);
    if (dir == 5u || dir > 9u) {
        dir = 0u;
    }
    uint16_t buttons = static_cast<uint16_t>(raw_word & ~kCccasterDirMask);
    if (mask_spectator_auto_confirm) {
        buttons = static_cast<uint16_t>(buttons & ~kCccasterBtnAutoConfirm);
    }
    return static_cast<uint16_t>(dir | buttons);
}

uint16_t cccaster_compute_auto_delay(double mean_one_way_ms, bool is_host_initial) noexcept {
    if (!std::isfinite(mean_one_way_ms) || mean_one_way_ms <= 0.0) {
        return is_host_initial ? 1u : 0u;
    }
    // Constant 0.06 verified in .rdata [0x006d3338]; Host initial adds +1 at 0x005d2a64.
    const double raw = std::ceil(0.06 * mean_one_way_ms) + (is_host_initial ? 1.0 : 0.0);
    if (raw <= 0.0) return 0u;
    if (raw >= static_cast<double>(kCccasterMaxDelay)) return kCccasterMaxDelay;
    return static_cast<uint16_t>(raw);
}

// -----------------------------------------------------------------------------
// Public Wire Body Helpers (PlayerInputs, BothInputs, PingStats, RngState, SyncHash)
// -----------------------------------------------------------------------------

std::vector<uint8_t> serialize_player_inputs(const WirePlayerInputs& msg) {
    // Verified at 0x005df5a8: Message (0B base), u32 frame, u32 index, fixed 60B (30 * u16).
    std::vector<uint8_t> out;
    out.reserve(68u);
    write_u32(out, msg.frame);
    write_u32(out, msg.index);
    for (uint16_t w : msg.inputs) {
        write_u16(out, w);
    }
    return out;
}

bool deserialize_player_inputs(const std::vector<uint8_t>& body, WirePlayerInputs& out) {
    ByteReader r(body);
    if (!r.read_u32(out.frame) || !r.read_u32(out.index)) return false;
    for (uint16_t& w : out.inputs) {
        if (!r.read_u16(w)) return false;
    }
    return true;
}

std::vector<uint8_t> serialize_both_inputs(const WireBothInputs& msg) {
    // Verified at 0x005df8c0: Sequence (u32 seqId), u32 frame, u32 index, 60B p1, 60B p2 (132B).
    std::vector<uint8_t> out;
    out.reserve(132u);
    write_u32(out, msg.seq_id);
    write_u32(out, msg.frame);
    write_u32(out, msg.index);
    for (uint16_t w : msg.p1_inputs) {
        write_u16(out, w);
    }
    for (uint16_t w : msg.p2_inputs) {
        write_u16(out, w);
    }
    return out;
}

bool deserialize_both_inputs(const std::vector<uint8_t>& body, WireBothInputs& out) {
    ByteReader r(body);
    if (!r.read_u32(out.seq_id) || !r.read_u32(out.frame) || !r.read_u32(out.index)) {
        return false;
    }
    for (uint16_t& w : out.p1_inputs) {
        if (!r.read_u16(w)) return false;
    }
    for (uint16_t& w : out.p2_inputs) {
        if (!r.read_u16(w)) return false;
    }
    return true;
}

std::vector<uint8_t> serialize_ping_stats(uint32_t seq_id, const CccasterStatistics& stats) {
    // Verified at 0x005e57a0 / 0x005d95a0: u32 seqId, u32 sampleCount, f64 max, f64 mean, f64 m2, u8 loss.
    std::vector<uint8_t> out;
    out.reserve(33u);
    write_u32(out, seq_id);
    write_u32(out, stats.sample_count);
    write_f64(out, stats.max_one_way_ms);
    write_f64(out, stats.mean_one_way_ms);
    write_f64(out, stats.welford_m2);
    write_u8(out, stats.loss_percent);
    return out;
}

bool deserialize_ping_stats(const std::vector<uint8_t>& body,
                            uint32_t& out_seq_id,
                            CccasterStatistics& out_stats) {
    ByteReader r(body);
    return r.read_u32(out_seq_id) &&
           r.read_u32(out_stats.sample_count) &&
           r.read_f64(out_stats.max_one_way_ms) &&
           r.read_f64(out_stats.mean_one_way_ms) &&
           r.read_f64(out_stats.welford_m2) &&
           r.read_u8(out_stats.loss_percent);
}

std::vector<uint8_t> serialize_rng_state(const WireRngState& msg) {
    // Verified at 0x005e50e0: u32 seqId, u32 context (+0x1c), 232B RNG state (240B inner body).
    std::vector<uint8_t> out;
    out.reserve(240u);
    write_u32(out, msg.seq_id);
    write_u32(out, msg.context);
    write_bytes(out, msg.data.data(), msg.data.size());
    return out;
}

bool deserialize_rng_state(const std::vector<uint8_t>& body, WireRngState& out) {
    ByteReader r(body);
    return r.read_u32(out.seq_id) &&
           r.read_u32(out.context) &&
           r.read_bytes(out.data.data(), out.data.size());
}

std::vector<uint8_t> serialize_sync_hash(const WireSyncHash& msg) {
    // Verified at 0x005e5370: u32 seqId, u32 frame, u32 roundOrFlags, 16B md5, 4*u32, 44B P1, 44B P2 (136B).
    std::vector<uint8_t> out;
    out.reserve(136u);
    write_u32(out, msg.seq_id);
    write_u32(out, msg.indexed_frame);
    write_u32(out, msg.round_or_flags);
    write_bytes(out, msg.rng_md5.data(), msg.rng_md5.size());
    for (uint32_t g : msg.globals) {
        write_u32(out, g);
    }
    write_bytes(out, msg.p1_slice.data(), msg.p1_slice.size());
    write_bytes(out, msg.p2_slice.data(), msg.p2_slice.size());
    return out;
}

bool deserialize_sync_hash(const std::vector<uint8_t>& body, WireSyncHash& out) {
    ByteReader r(body);
    if (!r.read_u32(out.seq_id) ||
        !r.read_u32(out.indexed_frame) ||
        !r.read_u32(out.round_or_flags) ||
        !r.read_bytes(out.rng_md5.data(), out.rng_md5.size())) {
        return false;
    }
    for (uint32_t& g : out.globals) {
        if (!r.read_u32(g)) return false;
    }
    return r.read_bytes(out.p1_slice.data(), out.p1_slice.size()) &&
           r.read_bytes(out.p2_slice.data(), out.p2_slice.size());
}

// -----------------------------------------------------------------------------
// CccasterNetClient::Impl
// -----------------------------------------------------------------------------

struct SpectatorPeer {
    IpEndpoint endpoint;
    GoBackNLink link;
    bool       confirmed = false;
    bool       version_ok = false;
};

struct CccasterNetClient::Impl {
    mutable std::mutex mutex;

    CccasterSessionConfig config;
    CccasterSessionStatus status;

    UdpSocket  main_sock;
    UdpSocket  spectate_sock;
    IpEndpoint peer_ep;
    GoBackNLink main_link;

    CccasterStatistics local_ping_stats;
    CccasterStatistics remote_ping_stats;

    bool peer_version_ok     = false;
    bool peer_initial_rx     = false;
    bool local_initial_sent  = false;
    bool host_config_sent    = false;
    bool config_confirmed    = false;
    uint64_t last_ping_tx_ms = 0u;
    uint64_t ping_clock_bias_ = 0u;

    // Input history (sliding 30-frame redundancy window + received inputs)
    std::unordered_map<uint32_t, uint16_t> local_inputs;
    std::unordered_map<uint32_t, uint16_t> remote_inputs;
    std::unordered_map<uint32_t, std::pair<uint16_t, uint16_t>> spectate_inputs;
    uint32_t last_sent_frame        = 0xFFFFFFFFu;
    uint32_t confirmed_remote_frame = 0xFFFFFFFFu;
    uint32_t latest_spectate_frame  = 0xFFFFFFFFu;

    // Sync / control message queues
    std::deque<WireRngState>         remote_rng_states;
    std::deque<WireSyncHash>         remote_sync_hashes;
    std::deque<WireInitialGameState> remote_initial_states;
    std::deque<WireMenuIndex>        remote_menu_indices;
    std::deque<uint32_t>             remote_transitions;
    std::deque<WireChangeConfig>     remote_change_configs;

    // Optional connected spectators on Host
    std::vector<SpectatorPeer> spectators;

    static int clamp_rollback(int rb) noexcept {
        return std::clamp(rb, 0, static_cast<int>(kCccasterMaxRollback));
    }

    static std::string make_state_label(CccasterSessionState st,
                                        CccasterClientMode mode) {
        switch (st) {
            case CccasterSessionState::Offline:
                return "Offline";
            case CccasterSessionState::Listening:
                return "Listening on UDP";
            case CccasterSessionState::Connecting:
                return (mode == CccasterClientMode::SpectateNetplay)
                           ? "Connecting to spectate..."
                           : "Connecting to host...";
            case CccasterSessionState::Handshaking:
                return "Calibrating RTT & config...";
            case CccasterSessionState::Connected:
                return "Connected";
            case CccasterSessionState::InGame:
                return "In Netplay";
            case CccasterSessionState::Error:
                return "Connection error";
        }
        return "Offline";
    }

    uint8_t build_mode_flags() const noexcept {
        return config.training_mode ? kModeFlagTraining : kModeFlagNone;
    }

    void reset_locked(CccasterClientMode mode, const std::string& local_ip) {
        main_sock.close();
        spectate_sock.close();
        peer_ep = IpEndpoint{};
        const uint64_t now = CccasterNetClient::steady_clock_ms();
        main_link.reset(now);
        local_ping_stats.reset();
        remote_ping_stats.reset();

        peer_version_ok    = false;
        peer_initial_rx    = false;
        local_initial_sent = false;
        host_config_sent   = false;
        config_confirmed   = false;
        last_ping_tx_ms    = 0u;
        {
            std::random_device rd;
            std::mt19937_64 rng(rd());
            ping_clock_bias_ = ((rng() & 0x7FFFFFFFull) + 1ull) << 32;
        }
        outstanding_local_pings_.clear();

        local_inputs.clear();
        remote_inputs.clear();
        spectate_inputs.clear();
        last_sent_frame        = 0xFFFFFFFFu;
        confirmed_remote_frame = 0xFFFFFFFFu;
        latest_spectate_frame  = 0xFFFFFFFFu;

        remote_rng_states.clear();
        remote_sync_hashes.clear();
        remote_initial_states.clear();
        remote_menu_indices.clear();
        remote_transitions.clear();
        remote_change_configs.clear();
        spectators.clear();

        status = CccasterSessionStatus{};
        status.mode               = mode;
        status.state              = CccasterSessionState::Offline;
        status.is_host            = (mode == CccasterClientMode::Host);
        status.local_player_index = (mode == CccasterClientMode::Host)
                                        ? (config.host_plays_p1 ? 0 : 1)
                                        : -1;
        status.local_ipv4         = local_ip;
        status.max_rollback       = clamp_rollback(config.max_rollback);
        status.delay_frames       = (config.delay_frames >= 0)
                                        ? std::min(config.delay_frames, static_cast<int>(kCccasterMaxDelay))
                                        : 0;
        status.state_label        = "Offline";
    }

    void set_error_locked(const std::string& err) {
        status.state       = CccasterSessionState::Error;
        status.active      = false;
        status.connected   = false;
        status.in_match    = false;
        status.last_error  = err;
        status.state_label = err;
    }

    bool start_host_locked(const CccasterSessionConfig& cfg) {
        config = cfg;
        if (config.player_name.empty()) config.player_name = "iOS";
        config.max_rollback = clamp_rollback(cfg.max_rollback);

        const std::string local_ip = cccaster_get_local_ipv4();
        reset_locked(CccasterClientMode::Host, local_ip);

        std::string err;
        if (!main_sock.open_udp(cfg.port, true, err)) {
            set_error_locked(err);
            return false;
        }

        if (cfg.spectate_port > 0u) {
            std::string spec_err;
            (void)spectate_sock.open_udp(cfg.spectate_port, true, spec_err);
        }

        status.state       = CccasterSessionState::Listening;
        status.active      = true;
        status.local_port  = main_sock.bound_port();
        status.p1_name     = config.host_plays_p1 ? config.player_name : std::string{};
        status.p2_name     = config.host_plays_p1 ? std::string{} : config.player_name;
        status.session_tag = make_session_tag();
        status.state_label = "Listening (" + local_ip + ":" + std::to_string(status.local_port) + ")";
        return true;
    }

    bool start_client_common_locked(const CccasterSessionConfig& cfg,
                                    CccasterClientMode mode) {
        config = cfg;
        if (config.player_name.empty()) config.player_name = "iOS";
        config.max_rollback = clamp_rollback(cfg.max_rollback);

        const std::string local_ip = cccaster_get_local_ipv4();
        reset_locked(mode, local_ip);

        const uint16_t target_port = (cfg.port == 0u) ? kCccasterDefaultPort : cfg.port;
        std::string err;
        IpEndpoint target{};
        if (!resolve_ipv4_endpoint(cfg.peer_ip, target_port, target, err)) {
            set_error_locked(err);
            return false;
        }
        if (!main_sock.open_udp(0u, false, err)) {
            set_error_locked(err);
            return false;
        }

        peer_ep            = target;
        status.state       = CccasterSessionState::Connecting;
        status.active      = true;
        status.local_port  = main_sock.bound_port();
        status.peer_addr   = target.to_string();
        status.state_label = make_state_label(status.state, mode);

        const uint64_t now = CccasterNetClient::steady_clock_ms();
        main_link.reset(now);
        (void)main_link.send_reliable(
            main_sock, peer_ep, CccasterMsgType::UdpControl,
            serialize_udp_control(0u, CccasterUdpControlCode::ConnectRequest), now);
        return true;
    }

    void update_ping_metrics_locked() {
        status.ping_samples        = local_ping_stats.sample_count;
        status.one_way_ms          = local_ping_stats.mean_one_way_ms;
        status.max_one_way_ms      = local_ping_stats.max_one_way_ms;
        status.ping_ms             = local_ping_stats.mean_one_way_ms * 2.0;
        status.jitter_ms           = local_ping_stats.stddev_ms();
        status.packet_loss_percent = local_ping_stats.loss_percent;
    }

    void emit_ping_locked(uint64_t now_ms) {
        last_ping_tx_ms = now_ms;
        if (outstanding_local_pings_.size() >= 32u) {
            outstanding_local_pings_.clear();
        }
        const uint64_t stamped_ms = ping_clock_bias_ + now_ms;
        outstanding_local_pings_[stamped_ms] = true;
        (void)main_link.send_unreliable(
            main_sock, peer_ep, CccasterMsgType::Ping, serialize_ping(stamped_ms));
    }

    void send_version_config_locked(uint64_t now_ms) {
        WireVersionConfig vc;
        vc.mode           = status.mode;
        vc.flags          = build_mode_flags();
        vc.version_str    = kCccasterVersionString;
        vc.commit_str     = kCccasterGitRevision;
        vc.build_date_str = kCccasterBuildDate;
        (void)main_link.send_reliable(
            main_sock, peer_ep, CccasterMsgType::VersionConfig,
            serialize_version_config(vc), now_ms);
    }

    void send_initial_config_locked(uint64_t now_ms) {
        if (local_initial_sent) return;
        local_initial_sent = true;

        WireInitialConfig ic;
        ic.mode          = status.mode;
        ic.flags         = build_mode_flags();
        ic.spectate_port = (status.mode == CccasterClientMode::Host && spectate_sock.is_open())
                               ? spectate_sock.bound_port()
                               : 0u;
        ic.local_name    = config.player_name;
        ic.remote_name   = status.peer_name;
        ic.extra_flag    = 0u;
        (void)main_link.send_reliable(
            main_sock, peer_ep, CccasterMsgType::InitialConfig,
            serialize_initial_config(ic), now_ms);
    }

    void maybe_send_host_netplay_config_locked(uint64_t now_ms) {
        if (status.mode != CccasterClientMode::Host) return;
        if (!peer_version_ok || !peer_initial_rx || host_config_sent) return;
        if (local_ping_stats.sample_count < kCccasterPingCalibSamples) return;

        host_config_sent = true;

        const uint16_t chosen_delay = (config.delay_frames >= 0)
                                          ? static_cast<uint16_t>(std::min(
                                                config.delay_frames,
                                                static_cast<int>(kCccasterMaxDelay)))
                                          : local_ping_stats.auto_delay(true);
        const uint8_t chosen_rb = static_cast<uint8_t>(clamp_rollback(config.max_rollback));

        status.delay_frames = static_cast<int>(chosen_delay);
        status.max_rollback = static_cast<int>(chosen_rb);

        (void)main_link.send_reliable(
            main_sock, peer_ep, CccasterMsgType::PingStats,
            serialize_ping_stats(0u, local_ping_stats), now_ms);

        WireNetplayConfig nc;
        nc.mode        = CccasterClientMode::Host;
        nc.flags       = build_mode_flags();
        nc.delay       = static_cast<uint8_t>(chosen_delay);
        nc.rollback    = chosen_rb;
        nc.sub_byte_3e = 0u;
        nc.sub_byte_3f = 0u;
        nc.host_side   = config.host_plays_p1 ? 1u : 2u;
        nc.sub_word_42 = 2u; // versusWinCount default
        nc.p1_name     = config.host_plays_p1 ? config.player_name : status.peer_name;
        nc.p2_name     = config.host_plays_p1 ? status.peer_name : config.player_name;
        nc.session_tag = status.session_tag;
        nc.extra_tag.clear();
        nc.tail_word_a4 = 0u;

        status.p1_name = nc.p1_name;
        status.p2_name = nc.p2_name;

        (void)main_link.send_reliable(
            main_sock, peer_ep, CccasterMsgType::NetplayConfig,
            serialize_netplay_config(nc), now_ms);
    }

    void handle_main_message_locked(CccasterMsgType type,
                                    const std::vector<uint8_t>& body,
                                    const IpEndpoint& src,
                                    uint64_t now_ms) {
        switch (type) {
            case CccasterMsgType::UdpControl: {
                uint32_t seq_id = 0u;
                CccasterUdpControlCode code = CccasterUdpControlCode::Unknown;
                if (!deserialize_udp_control(body, seq_id, code)) return;

                if (code == CccasterUdpControlCode::Disconnect) {
                    status.active      = false;
                    status.connected   = false;
                    status.in_match    = false;
                    status.state       = CccasterSessionState::Offline;
                    status.state_label = "Disconnected by peer";
                    main_sock.close();
                    spectate_sock.close();
                    return;
                }

                if (status.mode == CccasterClientMode::Host &&
                    code == CccasterUdpControlCode::ConnectRequest &&
                    status.state == CccasterSessionState::Listening) {
                    peer_ep          = src;
                    status.peer_addr = src.to_string();
                    status.state     = CccasterSessionState::Handshaking;
                    status.state_label = "Connecting peer...";
                    (void)main_link.send_reliable(
                        main_sock, peer_ep, CccasterMsgType::UdpControl,
                        serialize_udp_control(0u, CccasterUdpControlCode::ConnectReply),
                        now_ms);
                } else if (status.mode != CccasterClientMode::Host &&
                           code == CccasterUdpControlCode::ConnectReply &&
                           status.state == CccasterSessionState::Connecting) {
                    status.state       = CccasterSessionState::Handshaking;
                    status.state_label = make_state_label(status.state, status.mode);
                    (void)main_link.send_reliable(
                        main_sock, peer_ep, CccasterMsgType::UdpControl,
                        serialize_udp_control(0u, CccasterUdpControlCode::ConnectFinal),
                        now_ms);
                    send_version_config_locked(now_ms);
                } else if (status.mode == CccasterClientMode::Host &&
                           code == CccasterUdpControlCode::ConnectFinal &&
                           src == peer_ep) {
                    status.connected   = true;
                    status.state       = CccasterSessionState::Handshaking;
                    status.state_label = "Verifying version...";
                    send_version_config_locked(now_ms);
                }
                break;
            }

            case CccasterMsgType::VersionConfig: {
                WireVersionConfig vc;
                if (!deserialize_version_config(body, vc)) return;

                if (!cccaster_version_compatible(vc.version_str, vc.build_date_str,
                                                 config.strict_version)) {
                    const std::string err_msg =
                        "Incompatible CCCaster version: " + vc.version_str +
                        " (expected " + kCccasterVersionString + ")";
                    (void)main_link.send_reliable(
                        main_sock, peer_ep, CccasterMsgType::ErrorMessage,
                        serialize_error_message(0u, err_msg), now_ms);
                    set_error_locked(err_msg);
                    return;
                }

                peer_version_ok = true;
                if (status.mode == CccasterClientMode::Host) {
                    if (vc.mode == CccasterClientMode::SpectateNetplay ||
                        vc.mode == CccasterClientMode::SpectateBroadcast) {
                        const std::string rej_msg =
                            "Peer requested spectate on host netplay port";
                        (void)main_link.send_reliable(
                            main_sock, peer_ep, CccasterMsgType::ErrorMessage,
                            serialize_error_message(0u, rej_msg), now_ms);
                        peer_ep = IpEndpoint{};
                        peer_version_ok = false;
                        status.peer_addr.clear();
                        status.state = CccasterSessionState::Listening;
                        status.connected = false;
                        status.state_label = "Listening (" + status.local_ipv4 + ":" +
                                             std::to_string(status.local_port) + ")";
                        return;
                    }
                    send_initial_config_locked(now_ms);
                } else {
                    send_initial_config_locked(now_ms);
                    // Probe RTT actively while waiting for Host NetplayConfig / SpectateConfig.
                    emit_ping_locked(now_ms);
                }
                break;
            }

            case CccasterMsgType::InitialConfig: {
                WireInitialConfig ic;
                if (!deserialize_initial_config(body, ic)) return;
                peer_initial_rx = true;
                if (!ic.local_name.empty()) {
                    status.peer_name = ic.local_name;
                } else {
                    status.peer_name = "Anonymous";
                }
                if (status.mode == CccasterClientMode::Host) {
                    status.p1_name = config.host_plays_p1 ? config.player_name : status.peer_name;
                    status.p2_name = config.host_plays_p1 ? status.peer_name : config.player_name;
                    emit_ping_locked(now_ms);
                    maybe_send_host_netplay_config_locked(now_ms);
                }
                break;
            }

            case CccasterMsgType::Ping: {
                uint64_t send_ms = 0u;
                if (!deserialize_ping(body, send_ms)) return;
                const uint64_t biased_now = ping_clock_bias_ + now_ms;
                if (send_ms <= biased_now && (biased_now - send_ms) < 5000u &&
                    outstanding_local_pings_.erase(send_ms) > 0u) {
                    local_ping_stats.record_rtt_ms(biased_now - send_ms);
                    update_ping_metrics_locked();
                    maybe_send_host_netplay_config_locked(now_ms);
                } else {
                    (void)main_link.send_unreliable(
                        main_sock, peer_ep, CccasterMsgType::Ping, serialize_ping(send_ms));
                }
                break;
            }

            case CccasterMsgType::PingStats: {
                uint32_t seq_id = 0u;
                CccasterStatistics stats;
                if (!deserialize_ping_stats(body, seq_id, stats)) return;
                remote_ping_stats = stats;
                if (local_ping_stats.sample_count == 0u && stats.sample_count > 0u) {
                    local_ping_stats = stats;
                    update_ping_metrics_locked();
                }
                break;
            }

            case CccasterMsgType::NetplayConfig: {
                WireNetplayConfig nc;
                if (!deserialize_netplay_config(body, nc)) return;
                if (status.mode != CccasterClientMode::Client) break;

                status.p1_name      = nc.p1_name;
                status.p2_name      = nc.p2_name;
                status.session_tag  = nc.session_tag;
                status.max_rollback = clamp_rollback(nc.rollback);
                status.delay_frames = static_cast<int>(nc.delay);
                status.local_player_index = (nc.host_side == 1u) ? 1 : 0;
                if (status.peer_name.empty()) {
                    status.peer_name = (nc.host_side == 1u) ? nc.p1_name : nc.p2_name;
                }
                config_confirmed   = true;
                status.connected   = true;
                status.in_match    = true;
                status.state       = CccasterSessionState::InGame;
                status.state_label = "In Netplay";

                (void)main_link.send_reliable(
                    main_sock, peer_ep, CccasterMsgType::ConfirmConfig,
                    serialize_confirm_config(0u), now_ms);
                break;
            }

            case CccasterMsgType::SpectateConfig: {
                WireSpectateConfig sc;
                if (!deserialize_spectate_config(body, sc)) return;
                if (status.mode != CccasterClientMode::SpectateNetplay &&
                    status.mode != CccasterClientMode::SpectateBroadcast) {
                    break;
                }

                status.p1_name            = sc.p1_name;
                status.p2_name            = sc.p2_name;
                status.session_tag        = sc.session_tag;
                status.delay_frames       = static_cast<int>(sc.delay);
                status.max_rollback       = clamp_rollback(sc.rollback);
                status.local_player_index = -1;
                if (status.peer_name.empty()) {
                    status.peer_name = sc.p1_name + " vs " + sc.p2_name;
                }

                WireInitialGameState igs;
                igs.header8     = sc.state_header8;
                igs.stage       = sc.stage;
                igs.round_flags = sc.state_u8_b4;
                igs.unk_2d      = sc.state_u8_b5;
                igs.chara0      = static_cast<uint8_t>(sc.chara_word & 0xFFu);
                igs.chara1      = static_cast<uint8_t>((sc.chara_word >> 8) & 0xFFu);
                igs.moon0       = static_cast<uint8_t>(sc.moon_word & 0xFFu);
                igs.moon1       = static_cast<uint8_t>((sc.moon_word >> 8) & 0xFFu);
                igs.color0      = static_cast<uint8_t>(sc.color_word & 0xFFu);
                igs.color1      = static_cast<uint8_t>((sc.color_word >> 8) & 0xFFu);
                push_bounded(remote_initial_states, std::move(igs));

                config_confirmed   = true;
                status.connected   = true;
                status.in_match    = true;
                status.state       = CccasterSessionState::InGame;
                status.state_label = "Spectating";

                (void)main_link.send_reliable(
                    main_sock, peer_ep, CccasterMsgType::ConfirmConfig,
                    serialize_confirm_config(0u), now_ms);
                break;
            }

            case CccasterMsgType::ConfirmConfig: {
                uint32_t seq_id = 0u;
                if (!deserialize_confirm_config(body, seq_id)) return;
                config_confirmed   = true;
                status.connected   = true;
                status.in_match    = true;
                status.state       = CccasterSessionState::InGame;
                status.state_label = "In Netplay";
                break;
            }

            case CccasterMsgType::PlayerInputs: {
                WirePlayerInputs pi;
                if (!deserialize_player_inputs(body, pi)) return;
                if (pi.frame == 0xFFFFFFFFu) return;

                const size_t count =
                    std::min(static_cast<size_t>(pi.frame) + 1u, kCccasterInputWindow);
                const uint32_t start_frame = (pi.frame >= static_cast<uint32_t>(kCccasterInputWindow - 1u))
                                                 ? (pi.frame - static_cast<uint32_t>(kCccasterInputWindow - 1u))
                                                 : 0u;
                for (size_t i = 0u; i < count; ++i) {
                    const uint32_t f = start_frame + static_cast<uint32_t>(i);
                    remote_inputs[f] = cccaster_sanitize_input_word(pi.inputs[i], false);
                }
                if (confirmed_remote_frame == 0xFFFFFFFFu || pi.frame > confirmed_remote_frame) {
                    confirmed_remote_frame        = pi.frame;
                    status.confirmed_remote_frame = pi.frame;
                }
                prune_old_inputs(remote_inputs, pi.frame);
                break;
            }

            case CccasterMsgType::BothInputs: {
                WireBothInputs bi;
                if (!deserialize_both_inputs(body, bi)) return;
                if (bi.frame == 0xFFFFFFFFu) return;

                const size_t count =
                    std::min(static_cast<size_t>(bi.frame) + 1u, kCccasterInputWindow);
                const uint32_t start_frame = (bi.frame >= static_cast<uint32_t>(kCccasterInputWindow - 1u))
                                                 ? (bi.frame - static_cast<uint32_t>(kCccasterInputWindow - 1u))
                                                 : 0u;
                for (size_t i = 0u; i < count; ++i) {
                    const uint32_t f = start_frame + static_cast<uint32_t>(i);
                    // Mask bit 0x0020 (AutoConfirm) for spectators/replays matching 0x6639e6bd.
                    const uint16_t p1 = cccaster_sanitize_input_word(bi.p1_inputs[i], true);
                    const uint16_t p2 = cccaster_sanitize_input_word(bi.p2_inputs[i], true);
                    spectate_inputs[f] = std::make_pair(p1, p2);
                }
                if (latest_spectate_frame == 0xFFFFFFFFu || bi.frame > latest_spectate_frame) {
                    latest_spectate_frame         = bi.frame;
                    confirmed_remote_frame        = bi.frame;
                    status.confirmed_remote_frame = bi.frame;
                }
                prune_old_spectate(spectate_inputs, bi.frame);
                break;
            }

            case CccasterMsgType::RngState: {
                WireRngState rs;
                if (deserialize_rng_state(body, rs)) {
                    push_bounded(remote_rng_states, std::move(rs));
                }
                break;
            }

            case CccasterMsgType::SyncHash: {
                WireSyncHash sh;
                if (deserialize_sync_hash(body, sh)) {
                    push_bounded(remote_sync_hashes, std::move(sh));
                }
                break;
            }

            case CccasterMsgType::InitialGameState: {
                WireInitialGameState igs;
                if (deserialize_initial_game_state(body, igs)) {
                    push_bounded(remote_initial_states, std::move(igs));
                }
                break;
            }

            case CccasterMsgType::MenuIndex: {
                WireMenuIndex mi;
                if (deserialize_menu_index(body, mi)) {
                    push_bounded(remote_menu_indices, mi);
                }
                break;
            }

            case CccasterMsgType::TransitionIndex: {
                uint32_t tid = 0u;
                if (deserialize_transition_index(body, tid)) {
                    push_bounded(remote_transitions, tid);
                }
                break;
            }

            case CccasterMsgType::ChangeConfig: {
                WireChangeConfig cc;
                if (deserialize_change_config(body, cc)) {
                    if (cc.kind == CccasterChangeKind::DelayP1) {
                        status.delay_frames = static_cast<int>(
                            std::min(cc.delay, kCccasterMaxDelay));
                    } else if (cc.kind == CccasterChangeKind::DelayP2) {
                        status.delay_frames = static_cast<int>(
                            std::min(cc.p2_delay, kCccasterMaxDelay));
                    } else if (cc.kind == CccasterChangeKind::Rollback) {
                        status.max_rollback = clamp_rollback(cc.rollback);
                    }
                    push_bounded(remote_change_configs, cc);
                }
                break;
            }

            case CccasterMsgType::ErrorMessage: {
                uint32_t seq_id = 0u;
                std::string msg;
                if (deserialize_error_message(body, seq_id, msg)) {
                    set_error_locked(msg.empty() ? "Peer reported protocol error" : msg);
                }
                break;
            }

            default:
                break;
        }
    }

    SpectatorPeer* find_or_add_spectator_locked(const IpEndpoint& src, uint64_t now_ms) {
        for (SpectatorPeer& sp : spectators) {
            if (sp.endpoint == src) return &sp;
        }
        if (spectators.size() >= 8u) return nullptr;
        SpectatorPeer sp;
        sp.endpoint = src;
        sp.link.reset(now_ms);
        spectators.push_back(std::move(sp));
        return &spectators.back();
    }

    void handle_spectate_socket_locked(uint64_t now_ms) {
        if (!spectate_sock.is_open()) return;
        std::array<uint8_t, kMaxUdpDatagramBytes> buf{};
        for (size_t i = 0u; i < kMaxPollsPerTick; ++i) {
            IpEndpoint src{};
            const int n = spectate_sock.recv_from(buf.data(), buf.size(), src);
            if (n <= 0) break;
            SpectatorPeer* sp = find_or_add_spectator_locked(src, now_ms);
            if (!sp) continue;

            sp->link.handle_packet(
                spectate_sock, src, buf.data(), static_cast<size_t>(n), now_ms, true,
                [this, sp, now_ms](CccasterMsgType type, const std::vector<uint8_t>& body) {
                    if (type == CccasterMsgType::UdpControl) {
                        uint32_t seq_id = 0u;
                        CccasterUdpControlCode code = CccasterUdpControlCode::Unknown;
                        if (!deserialize_udp_control(body, seq_id, code)) return;
                        if (code == CccasterUdpControlCode::ConnectRequest) {
                            (void)sp->link.send_reliable(
                                spectate_sock, sp->endpoint, CccasterMsgType::UdpControl,
                                serialize_udp_control(0u, CccasterUdpControlCode::ConnectReply),
                                now_ms);
                        } else if (code == CccasterUdpControlCode::ConnectFinal) {
                            WireVersionConfig vc;
                            vc.mode           = CccasterClientMode::Host;
                            vc.flags          = build_mode_flags();
                            vc.version_str    = kCccasterVersionString;
                            vc.commit_str     = kCccasterGitRevision;
                            vc.build_date_str = kCccasterBuildDate;
                            (void)sp->link.send_reliable(
                                spectate_sock, sp->endpoint, CccasterMsgType::VersionConfig,
                                serialize_version_config(vc), now_ms);
                        } else if (code == CccasterUdpControlCode::Disconnect) {
                            sp->confirmed = false;
                            sp->endpoint = IpEndpoint{};
                        }
                    } else if (type == CccasterMsgType::VersionConfig) {
                        WireVersionConfig vc;
                        if (deserialize_version_config(body, vc) &&
                            cccaster_version_compatible(vc.version_str, vc.build_date_str,
                                                        config.strict_version)) {
                            sp->version_ok = true;
                        }
                    } else if (type == CccasterMsgType::InitialConfig && sp->version_ok) {
                        WireSpectateConfig sc;
                        sc.mode        = CccasterClientMode::SpectateNetplay;
                        sc.flags       = build_mode_flags();
                        sc.delay       = static_cast<uint8_t>(std::clamp(status.delay_frames, 0, 254));
                        sc.rollback    = static_cast<uint8_t>(clamp_rollback(status.max_rollback));
                        sc.p1_name     = status.p1_name;
                        sc.p2_name     = status.p2_name;
                        sc.session_tag = status.session_tag;
                        (void)sp->link.send_reliable(
                            spectate_sock, sp->endpoint, CccasterMsgType::SpectateConfig,
                            serialize_spectate_config(sc), now_ms);
                    } else if (type == CccasterMsgType::ConfirmConfig) {
                        sp->confirmed = true;
                    } else if (type == CccasterMsgType::Ping) {
                        uint64_t send_ms = 0u;
                        if (deserialize_ping(body, send_ms)) {
                            (void)sp->link.send_unreliable(
                                spectate_sock, sp->endpoint, CccasterMsgType::Ping,
                                serialize_ping(send_ms));
                        }
                    }
                });
        }

        for (auto it = spectators.begin(); it != spectators.end();) {
            if (!it->endpoint.valid() ||
                !it->link.tick_resends(spectate_sock, it->endpoint, now_ms)) {
                it = spectators.erase(it);
            } else {
                ++it;
            }
        }
        status.spectator_count = static_cast<uint32_t>(spectators.size());
    }

    void poll_locked(uint64_t now_ms) {
        if (!status.active || !main_sock.is_open()) return;

        std::array<uint8_t, kMaxUdpDatagramBytes> buf{};
        for (size_t i = 0u; i < kMaxPollsPerTick; ++i) {
            IpEndpoint src{};
            const int n = main_sock.recv_from(buf.data(), buf.size(), src);
            if (n < 0) {
                set_error_locked("UDP recvfrom failed");
                return;
            }
            if (n == 0) break;

            const bool allow_accept =
                (status.mode == CccasterClientMode::Host &&
                 status.state == CccasterSessionState::Listening);
            if (!allow_accept && !(src == peer_ep)) {
                continue;
            }

            main_link.handle_packet(
                main_sock, src, buf.data(), static_cast<size_t>(n), now_ms, allow_accept,
                [this, &src, now_ms](CccasterMsgType type, const std::vector<uint8_t>& body) {
                    handle_main_message_locked(type, body, src, now_ms);
                });

            if (!status.active) return;
        }

        // GoBackN retransmit & 20000 ms timeout check on active peer link.
        if (peer_ep.valid() && !main_link.tick_resends(main_sock, peer_ep, now_ms)) {
            set_error_locked("Connection timed out (20s)");
            return;
        }

        // Connecting state overall timeout before ConnectReply arrives.
        if ((status.state == CccasterSessionState::Connecting ||
             status.state == CccasterSessionState::Handshaking) &&
            main_link.last_activity_ms() > 0u &&
            now_ms >= main_link.last_activity_ms() &&
            (now_ms - main_link.last_activity_ms()) >= kCccasterTimeoutMs) {
            set_error_locked("Handshake timed out (20s)");
            return;
        }

        // Drive Ping probes once InitialConfig has begun (fast burst during calibration, 1 Hz after).
        if (peer_ep.valid() && peer_version_ok && local_initial_sent &&
            status.mode != CccasterClientMode::SpectateNetplay &&
            status.mode != CccasterClientMode::SpectateBroadcast) {
            const uint32_t interval =
                (!host_config_sent && local_ping_stats.sample_count < kCccasterPingCalibSamples)
                    ? kFastPingIntervalMs
                    : kKeepalivePingMs;
            if (last_ping_tx_ms == 0u ||
                (now_ms >= last_ping_tx_ms && (now_ms - last_ping_tx_ms) >= interval)) {
                emit_ping_locked(now_ms);
            }
        }

        if (status.mode == CccasterClientMode::Host) {
            maybe_send_host_netplay_config_locked(now_ms);
            handle_spectate_socket_locked(now_ms);
        }
    }

    std::unordered_map<uint64_t, bool> outstanding_local_pings_;
};

// -----------------------------------------------------------------------------
// CccasterNetClient Public API
// -----------------------------------------------------------------------------

CccasterNetClient::CccasterNetClient()
    : impl_(std::make_unique<Impl>()) {}

CccasterNetClient::~CccasterNetClient() {
    disconnect();
}

uint64_t CccasterNetClient::steady_clock_ms() noexcept {
    const auto now = std::chrono::steady_clock::now().time_since_epoch();
    return static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(now).count());
}

bool CccasterNetClient::start_host(const CccasterSessionConfig& config) {
    std::lock_guard<std::mutex> lock(impl_->mutex);
    return impl_->start_host_locked(config);
}

bool CccasterNetClient::start_join(const CccasterSessionConfig& config) {
    std::lock_guard<std::mutex> lock(impl_->mutex);
    return impl_->start_client_common_locked(config, CccasterClientMode::Client);
}

bool CccasterNetClient::start_spectate(const CccasterSessionConfig& config) {
    std::lock_guard<std::mutex> lock(impl_->mutex);
    return impl_->start_client_common_locked(config, CccasterClientMode::SpectateNetplay);
}

void CccasterNetClient::disconnect() {
    if (!impl_) return;
    std::lock_guard<std::mutex> lock(impl_->mutex);
    if (impl_->main_sock.is_open() && impl_->peer_ep.valid()) {
        impl_->main_link.send_disconnect_3x(impl_->main_sock, impl_->peer_ep);
    }
    if (impl_->spectate_sock.is_open()) {
        for (const SpectatorPeer& sp : impl_->spectators) {
            if (sp.endpoint.valid()) {
                sp.link.send_disconnect_3x(impl_->spectate_sock, sp.endpoint);
            }
        }
    }
    impl_->reset_locked(CccasterClientMode::Offline, impl_->status.local_ipv4);
}

void CccasterNetClient::poll(uint64_t now_ms) {
    const uint64_t ts = (now_ms == 0u) ? steady_clock_ms() : now_ms;
    std::lock_guard<std::mutex> lock(impl_->mutex);
    impl_->poll_locked(ts);
}

void CccasterNetClient::submit_local_input(uint32_t frame,
                                           uint16_t input_word,
                                           uint32_t context_index) {
    if (frame == 0xFFFFFFFFu) return;
    std::lock_guard<std::mutex> lock(impl_->mutex);
    if (!impl_->status.active || !impl_->main_sock.is_open() || !impl_->peer_ep.valid()) {
        return;
    }
    if (impl_->status.mode == CccasterClientMode::SpectateNetplay ||
        impl_->status.mode == CccasterClientMode::SpectateBroadcast) {
        return;
    }

    const uint16_t sanitized = cccaster_sanitize_input_word(input_word, false);
    impl_->local_inputs[frame] = sanitized;
    if (impl_->last_sent_frame == 0xFFFFFFFFu || frame > impl_->last_sent_frame) {
        impl_->last_sent_frame        = frame;
        impl_->status.last_sent_frame = frame;
    }
    prune_old_inputs(impl_->local_inputs, frame);

    WirePlayerInputs pi;
    pi.frame = frame;
    pi.index = context_index;
    const uint32_t start_frame = (frame >= static_cast<uint32_t>(kCccasterInputWindow - 1u))
                                     ? (frame - static_cast<uint32_t>(kCccasterInputWindow - 1u))
                                     : 0u;
    const size_t count = std::min(static_cast<size_t>(frame) + 1u, kCccasterInputWindow);
    for (size_t i = 0u; i < count; ++i) {
        const auto it = impl_->local_inputs.find(start_frame + static_cast<uint32_t>(i));
        pi.inputs[i] = (it != impl_->local_inputs.end()) ? it->second : 0u;
    }

    (void)impl_->main_link.send_unreliable(
        impl_->main_sock, impl_->peer_ep, CccasterMsgType::PlayerInputs,
        serialize_player_inputs(pi));
}

bool CccasterNetClient::get_remote_input(uint32_t frame, uint16_t& out_input_word) const {
    std::lock_guard<std::mutex> lock(impl_->mutex);
    const auto it = impl_->remote_inputs.find(frame);
    if (it == impl_->remote_inputs.end()) return false;
    out_input_word = it->second;
    return true;
}

bool CccasterNetClient::get_spectate_inputs(uint32_t frame,
                                            uint16_t& out_p1_word,
                                            uint16_t& out_p2_word) const {
    std::lock_guard<std::mutex> lock(impl_->mutex);
    const auto it = impl_->spectate_inputs.find(frame);
    if (it == impl_->spectate_inputs.end()) return false;
    out_p1_word = it->second.first;
    out_p2_word = it->second.second;
    return true;
}

void CccasterNetClient::broadcast_both_inputs(uint32_t frame,
                                              uint16_t p1_input_word,
                                              uint16_t p2_input_word,
                                              uint32_t context_index) {
    if (frame == 0xFFFFFFFFu) return;
    const uint64_t now = steady_clock_ms();
    std::lock_guard<std::mutex> lock(impl_->mutex);
    if (impl_->status.mode != CccasterClientMode::Host || !impl_->spectate_sock.is_open()) {
        return;
    }
    const uint16_t p1 = cccaster_sanitize_input_word(p1_input_word, true);
    const uint16_t p2 = cccaster_sanitize_input_word(p2_input_word, true);
    impl_->spectate_inputs[frame] = std::make_pair(p1, p2);
    prune_old_spectate(impl_->spectate_inputs, frame);

    WireBothInputs bi;
    bi.frame = frame;
    bi.index = context_index;
    const uint32_t start_frame = (frame >= static_cast<uint32_t>(kCccasterInputWindow - 1u))
                                     ? (frame - static_cast<uint32_t>(kCccasterInputWindow - 1u))
                                     : 0u;
    const size_t count = std::min(static_cast<size_t>(frame) + 1u, kCccasterInputWindow);
    for (size_t i = 0u; i < count; ++i) {
        const auto it = impl_->spectate_inputs.find(start_frame + static_cast<uint32_t>(i));
        if (it != impl_->spectate_inputs.end()) {
            bi.p1_inputs[i] = it->second.first;
            bi.p2_inputs[i] = it->second.second;
        }
    }

    const std::vector<uint8_t> body = serialize_both_inputs(bi);
    for (SpectatorPeer& sp : impl_->spectators) {
        if (sp.confirmed && sp.endpoint.valid()) {
            (void)sp.link.send_reliable(
                impl_->spectate_sock, sp.endpoint, CccasterMsgType::BothInputs, body, now);
        }
    }
}

bool CccasterNetClient::send_rng_state(const WireRngState& state) {
    const uint64_t now = steady_clock_ms();
    std::lock_guard<std::mutex> lock(impl_->mutex);
    if (!impl_->status.active || !impl_->main_sock.is_open() || !impl_->peer_ep.valid()) {
        return false;
    }
    return impl_->main_link.send_reliable(
        impl_->main_sock, impl_->peer_ep, CccasterMsgType::RngState,
        serialize_rng_state(state), now);
}

bool CccasterNetClient::pop_remote_rng_state(WireRngState& out_state) {
    std::lock_guard<std::mutex> lock(impl_->mutex);
    return pop_front_item(impl_->remote_rng_states, out_state);
}

bool CccasterNetClient::send_sync_hash(const WireSyncHash& hash) {
    const uint64_t now = steady_clock_ms();
    std::lock_guard<std::mutex> lock(impl_->mutex);
    if (!impl_->status.active || !impl_->main_sock.is_open() || !impl_->peer_ep.valid()) {
        return false;
    }
    return impl_->main_link.send_reliable(
        impl_->main_sock, impl_->peer_ep, CccasterMsgType::SyncHash,
        serialize_sync_hash(hash), now);
}

bool CccasterNetClient::pop_remote_sync_hash(WireSyncHash& out_hash) {
    std::lock_guard<std::mutex> lock(impl_->mutex);
    return pop_front_item(impl_->remote_sync_hashes, out_hash);
}

bool CccasterNetClient::send_initial_game_state(const WireInitialGameState& state) {
    const uint64_t now = steady_clock_ms();
    std::lock_guard<std::mutex> lock(impl_->mutex);
    if (!impl_->status.active || !impl_->main_sock.is_open() || !impl_->peer_ep.valid()) {
        return false;
    }
    return impl_->main_link.send_reliable(
        impl_->main_sock, impl_->peer_ep, CccasterMsgType::InitialGameState,
        serialize_initial_game_state(state), now);
}

bool CccasterNetClient::pop_remote_initial_game_state(WireInitialGameState& out_state) {
    std::lock_guard<std::mutex> lock(impl_->mutex);
    return pop_front_item(impl_->remote_initial_states, out_state);
}

bool CccasterNetClient::send_menu_index(uint32_t indexed_frame, int8_t menu_choice) {
    const uint64_t now = steady_clock_ms();
    std::lock_guard<std::mutex> lock(impl_->mutex);
    if (!impl_->status.active || !impl_->main_sock.is_open() || !impl_->peer_ep.valid()) {
        return false;
    }
    WireMenuIndex mi;
    mi.indexed_frame = indexed_frame;
    mi.menu_choice   = menu_choice;
    return impl_->main_link.send_reliable(
        impl_->main_sock, impl_->peer_ep, CccasterMsgType::MenuIndex,
        serialize_menu_index(mi), now);
}

bool CccasterNetClient::pop_remote_menu_index(WireMenuIndex& out_menu) {
    std::lock_guard<std::mutex> lock(impl_->mutex);
    return pop_front_item(impl_->remote_menu_indices, out_menu);
}

bool CccasterNetClient::send_transition_index(uint32_t transition_id) {
    std::lock_guard<std::mutex> lock(impl_->mutex);
    if (!impl_->status.active || !impl_->main_sock.is_open() || !impl_->peer_ep.valid()) {
        return false;
    }
    return impl_->main_link.send_unreliable(
        impl_->main_sock, impl_->peer_ep, CccasterMsgType::TransitionIndex,
        serialize_transition_index(transition_id));
}

bool CccasterNetClient::pop_remote_transition_index(uint32_t& out_transition_id) {
    std::lock_guard<std::mutex> lock(impl_->mutex);
    return pop_front_item(impl_->remote_transitions, out_transition_id);
}

bool CccasterNetClient::send_change_config(const WireChangeConfig& cfg) {
    const uint64_t now = steady_clock_ms();
    std::lock_guard<std::mutex> lock(impl_->mutex);
    if (!impl_->status.active || !impl_->main_sock.is_open() || !impl_->peer_ep.valid()) {
        return false;
    }
    return impl_->main_link.send_reliable(
        impl_->main_sock, impl_->peer_ep, CccasterMsgType::ChangeConfig,
        serialize_change_config(cfg), now);
}

bool CccasterNetClient::pop_remote_change_config(WireChangeConfig& out_cfg) {
    std::lock_guard<std::mutex> lock(impl_->mutex);
    return pop_front_item(impl_->remote_change_configs, out_cfg);
}

CccasterSessionStatus CccasterNetClient::status() const {
    std::lock_guard<std::mutex> lock(impl_->mutex);
    return impl_->status;
}

} // namespace mbaa_recomp
