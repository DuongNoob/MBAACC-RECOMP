#include "mbaa_recomp/hle_crt.h"
#include "mbaa_recomp/dispatch.h"
#include "mbaa_recomp/hle_win32.h"

#include <algorithm>
#include <array>
#include <atomic>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

namespace mbaa_recomp {

namespace {

// ---------------------------------------------------------------------------
// Guest heap / string / ctype helpers
// ---------------------------------------------------------------------------
std::vector<uint32_t> g_atexit_funcs;
std::mutex g_crt_mutex;
uint32_t g_localtime_buf_va = 0u;

// ---------------------------------------------------------------------------
// Guest printf / vsnprintf engine (reads 32-bit stack va_list from GuestMemory)
// ---------------------------------------------------------------------------
std::string format_guest_printf(const GuestMemory& mem, const std::string& fmt, uint32_t ap_va) {
    std::string out;
    out.reserve(fmt.size() + 32u);
    uint32_t arg_cursor = ap_va;

    auto next_u32 = [&]() -> uint32_t {
        const uint32_t v = mem.r32(arg_cursor);
        arg_cursor += 4u;
        return v;
    };
    auto next_u64 = [&]() -> uint64_t {
        const uint64_t lo = mem.r32(arg_cursor);
        const uint64_t hi = mem.r32(arg_cursor + 4u);
        arg_cursor += 8u;
        return lo | (hi << 32);
    };

    for (size_t i = 0; i < fmt.size(); ++i) {
        if (fmt[i] != '%' || i + 1 >= fmt.size()) {
            out.push_back(fmt[i]);
            continue;
        }
        size_t j = i + 1;
        std::string spec = "%";
        while (j < fmt.size() && (fmt[j] == '-' || fmt[j] == '+' || fmt[j] == '0' ||
                                  fmt[j] == ' ' || fmt[j] == '#')) {
            spec.push_back(fmt[j++]);
        }
        if (j < fmt.size() && fmt[j] == '*') {
            spec += std::to_string(static_cast<int32_t>(next_u32()));
            ++j;
        } else {
            while (j < fmt.size() && std::isdigit(static_cast<unsigned char>(fmt[j]))) {
                spec.push_back(fmt[j++]);
            }
        }
        if (j < fmt.size() && fmt[j] == '.') {
            spec.push_back('.');
            ++j;
            if (j < fmt.size() && fmt[j] == '*') {
                spec += std::to_string(static_cast<int32_t>(next_u32()));
                ++j;
            } else {
                while (j < fmt.size() && std::isdigit(static_cast<unsigned char>(fmt[j]))) {
                    spec.push_back(fmt[j++]);
                }
            }
        }

        bool is_ll = false;
        if (j + 2 < fmt.size() && fmt[j] == 'I' && fmt[j + 1] == '6' && fmt[j + 2] == '4') {
            is_ll = true;
            spec += "ll";
            j += 3;
        } else if (j + 1 < fmt.size() && fmt[j] == 'l' && fmt[j + 1] == 'l') {
            is_ll = true;
            spec += "ll";
            j += 2;
        } else if (j < fmt.size() && (fmt[j] == 'l' || fmt[j] == 'h')) {
            if (fmt[j] == 'h') spec.push_back(fmt[j]);
            ++j;
        }

        if (j >= fmt.size()) break;
        const char conv = fmt[j];
        i = j;

        if (conv == '%') {
            out.push_back('%');
            continue;
        }
        spec.push_back(conv);

        char buf[512] = {};
        if (conv == 's') {
            const uint32_t s_va = next_u32();
            std::string s = (s_va != 0u) ? mem.read_cstring(s_va, 8192u) : "(null)";
            std::snprintf(buf, sizeof(buf), spec.c_str(), s.c_str());
            out += buf;
        } else if (conv == 'c') {
            std::snprintf(buf, sizeof(buf), spec.c_str(), static_cast<int>(next_u32() & 0xFFu));
            out += buf;
        } else if (conv == 'd' || conv == 'i') {
            if (is_ll) {
                std::snprintf(buf, sizeof(buf), spec.c_str(), static_cast<long long>(next_u64()));
            } else {
                std::snprintf(buf, sizeof(buf), spec.c_str(), static_cast<int32_t>(next_u32()));
            }
            out += buf;
        } else if (conv == 'u' || conv == 'x' || conv == 'X' || conv == 'o' || conv == 'p') {
            if (is_ll) {
                std::snprintf(buf, sizeof(buf), spec.c_str(), static_cast<unsigned long long>(next_u64()));
            } else if (conv == 'p') {
                std::snprintf(buf, sizeof(buf), "%08x", next_u32());
            } else {
                std::snprintf(buf, sizeof(buf), spec.c_str(), next_u32());
            }
            out += buf;
        } else if (conv == 'f' || conv == 'F' || conv == 'e' || conv == 'E' ||
                   conv == 'g' || conv == 'G') {
            const uint64_t raw = next_u64();
            double d = 0.0;
            std::memcpy(&d, &raw, sizeof(d));
            std::snprintf(buf, sizeof(buf), spec.c_str(), d);
            out += buf;
        } else {
            out += spec;
        }
    }
    return out;
}

int write_formatted_cstr(GuestMemory& mem, uint32_t dst_va, size_t max_count, bool bounded, const std::string& formatted) {
    if (dst_va == 0u) return -1;
    if (!bounded) {
        mem.write_bytes(dst_va, formatted.data(), formatted.size());
        mem.w8(dst_va + static_cast<uint32_t>(formatted.size()), 0u);
        return static_cast<int>(formatted.size());
    }
    if (max_count == 0u) return -1;
    const size_t n = std::min(formatted.size(), max_count);
    mem.write_bytes(dst_va, formatted.data(), n);
    if (formatted.size() < max_count) {
        mem.w8(dst_va + static_cast<uint32_t>(formatted.size()), 0u);
        return static_cast<int>(formatted.size());
    }
    return (formatted.size() == max_count) ? static_cast<int>(max_count) : -1;
}

// ---------------------------------------------------------------------------
// Guest sscanf implementation (reads args from [esp+12..])
// ---------------------------------------------------------------------------
int run_guest_sscanf(GuestMemory& mem, uint32_t str_va, uint32_t fmt_va, uint32_t ap_va) {
    if (str_va == 0u || fmt_va == 0u) return -1;
    const std::string input = mem.read_cstring(str_va, 8192u);
    const std::string fmt   = mem.read_cstring(fmt_va, 1024u);

    size_t si = 0;
    size_t fi = 0;
    uint32_t arg_cursor = ap_va;
    int assigned = 0;

    auto next_ptr = [&]() -> uint32_t {
        const uint32_t p = mem.r32(arg_cursor);
        arg_cursor += 4u;
        return p;
    };

    while (fi < fmt.size()) {
        if (std::isspace(static_cast<unsigned char>(fmt[fi]))) {
            while (fi < fmt.size() && std::isspace(static_cast<unsigned char>(fmt[fi]))) ++fi;
            while (si < input.size() && std::isspace(static_cast<unsigned char>(input[si]))) ++si;
            continue;
        }
        if (fmt[fi] != '%') {
            if (si >= input.size() || input[si] != fmt[fi]) break;
            ++si;
            ++fi;
            continue;
        }

        ++fi;
        if (fi < fmt.size() && fmt[fi] == '%') {
            if (si >= input.size() || input[si] != '%') break;
            ++si;
            ++fi;
            continue;
        }

        bool suppress = false;
        if (fi < fmt.size() && fmt[fi] == '*') {
            suppress = true;
            ++fi;
        }
        int width = 0;
        while (fi < fmt.size() && std::isdigit(static_cast<unsigned char>(fmt[fi]))) {
            width = width * 10 + (fmt[fi++] - '0');
        }
        bool is_long = false;
        bool is_short = false;
        if (fi < fmt.size() && fmt[fi] == 'l') {
            is_long = true;
            ++fi;
        } else if (fi < fmt.size() && fmt[fi] == 'h') {
            is_short = true;
            ++fi;
        }
        if (fi >= fmt.size()) break;

        const char conv = fmt[fi++];
        if (conv == 'n') {
            if (!suppress) {
                const uint32_t dst = next_ptr();
                if (dst) mem.w32(dst, static_cast<uint32_t>(si));
            }
            continue;
        }

        if (conv != 'c' && conv != '[') {
            while (si < input.size() && std::isspace(static_cast<unsigned char>(input[si]))) ++si;
        }
        if (si >= input.size()) break;

        if (conv == 'd' || conv == 'i' || conv == 'u' || conv == 'x' || conv == 'X') {
            const int base = (conv == 'x' || conv == 'X') ? 16 : ((conv == 'i') ? 0 : 10);
            std::string tok = (width > 0) ? input.substr(si, static_cast<size_t>(width)) : input.substr(si);
            char* endp = nullptr;
            if (conv == 'u' || conv == 'x' || conv == 'X') {
                const unsigned long val = std::strtoul(tok.c_str(), &endp, base);
                if (endp == tok.c_str()) break;
                si += static_cast<size_t>(endp - tok.c_str());
                if (!suppress) {
                    const uint32_t dst = next_ptr();
                    if (dst) {
                        if (is_short) mem.w16(dst, static_cast<uint16_t>(val));
                        else mem.w32(dst, static_cast<uint32_t>(val));
                    }
                    ++assigned;
                }
            } else {
                const long val = std::strtol(tok.c_str(), &endp, base);
                if (endp == tok.c_str()) break;
                si += static_cast<size_t>(endp - tok.c_str());
                if (!suppress) {
                    const uint32_t dst = next_ptr();
                    if (dst) {
                        if (is_short) mem.w16(dst, static_cast<uint16_t>(val));
                        else mem.w32(dst, static_cast<uint32_t>(static_cast<int32_t>(val)));
                    }
                    ++assigned;
                }
            }
        } else if (conv == 'f' || conv == 'F' || conv == 'e' || conv == 'E' || conv == 'g' || conv == 'G') {
            std::string tok = (width > 0) ? input.substr(si, static_cast<size_t>(width)) : input.substr(si);
            char* endp = nullptr;
            const double val = std::strtod(tok.c_str(), &endp);
            if (endp == tok.c_str()) break;
            si += static_cast<size_t>(endp - tok.c_str());
            if (!suppress) {
                const uint32_t dst = next_ptr();
                if (dst) {
                    if (is_long) mem.wf64(dst, val);
                    else mem.wf32(dst, static_cast<float>(val));
                }
                ++assigned;
            }
        } else if (conv == 's') {
            const size_t start = si;
            int rem = (width > 0) ? width : 4096;
            while (si < input.size() && rem > 0 && !std::isspace(static_cast<unsigned char>(input[si]))) {
                ++si;
                --rem;
            }
            if (si == start) break;
            if (!suppress) {
                const uint32_t dst = next_ptr();
                if (dst) mem.write_cstring(dst, input.substr(start, si - start));
                ++assigned;
            }
        } else if (conv == 'c') {
            const size_t cnt = (width > 0) ? static_cast<size_t>(width) : 1u;
            if (si + cnt > input.size()) break;
            if (!suppress) {
                const uint32_t dst = next_ptr();
                if (dst) mem.write_bytes(dst, input.data() + si, cnt);
                ++assigned;
            }
            si += cnt;
        } else if (conv == '[') {
            bool negate = false;
            if (fi < fmt.size() && fmt[fi] == '^') {
                negate = true;
                ++fi;
            }
            std::array<bool, 256> set{};
            if (fi < fmt.size() && fmt[fi] == ']') {
                set[static_cast<unsigned char>(']')] = true;
                ++fi;
            }
            while (fi < fmt.size() && fmt[fi] != ']') {
                set[static_cast<unsigned char>(fmt[fi++])] = true;
            }
            if (fi < fmt.size() && fmt[fi] == ']') ++fi;

            const size_t start = si;
            int rem = (width > 0) ? width : 4096;
            while (si < input.size() && rem > 0) {
                const bool in_set = set[static_cast<unsigned char>(input[si])];
                if (negate ? in_set : !in_set) break;
                ++si;
                --rem;
            }
            if (si == start) break;
            if (!suppress) {
                const uint32_t dst = next_ptr();
                if (dst) mem.write_cstring(dst, input.substr(start, si - start));
                ++assigned;
            }
        } else {
            break;
        }
    }

    return (assigned == 0 && si == 0 && !input.empty()) ? -1 : assigned;
}

// ---------------------------------------------------------------------------
// Self-contained Xiph Ogg Vorbis I Decoder (for libvorbisfile ov_* HLE)
// Tested against MBAACC .ogg streams (mono 22050 Hz SE & stereo 44100 Hz BGM).
// ---------------------------------------------------------------------------
constexpr std::array<float, 256> kFloor1InvDb = {{
    1.0649863e-07f, 1.1341951e-07f, 1.2079015e-07f, 1.2863978e-07f, 1.3699951e-07f, 1.4590251e-07f, 1.5538408e-07f, 1.6548181e-07f,
    1.7623575e-07f, 1.8768855e-07f, 1.9988561e-07f, 2.1287530e-07f, 2.2670913e-07f, 2.4144197e-07f, 2.5713223e-07f, 2.7384213e-07f,
    2.9163793e-07f, 3.1059021e-07f, 3.3077411e-07f, 3.5226968e-07f, 3.7516214e-07f, 3.9954229e-07f, 4.2550680e-07f, 4.5315863e-07f,
    4.8260743e-07f, 5.1396998e-07f, 5.4737065e-07f, 5.8294187e-07f, 6.2082472e-07f, 6.6116941e-07f, 7.0413592e-07f, 7.4989464e-07f,
    7.9862701e-07f, 8.5052630e-07f, 9.0579828e-07f, 9.6466216e-07f, 1.0273513e-06f, 1.0941144e-06f, 1.1652161e-06f, 1.2409384e-06f,
    1.3215816e-06f, 1.4074654e-06f, 1.4989305e-06f, 1.5963394e-06f, 1.7000785e-06f, 1.8105592e-06f, 1.9282195e-06f, 2.0535261e-06f,
    2.1869758e-06f, 2.3290978e-06f, 2.4804557e-06f, 2.6416497e-06f, 2.8133190e-06f, 2.9961443e-06f, 3.1908506e-06f, 3.3982101e-06f,
    3.6190449e-06f, 3.8542308e-06f, 4.1047004e-06f, 4.3714470e-06f, 4.6555282e-06f, 4.9580707e-06f, 5.2802740e-06f, 5.6234160e-06f,
    5.9888572e-06f, 6.3780469e-06f, 6.7925283e-06f, 7.2339451e-06f, 7.7040476e-06f, 8.2047000e-06f, 8.7378876e-06f, 9.3057248e-06f,
    9.9104632e-06f, 1.0554501e-05f, 1.1240392e-05f, 1.1970856e-05f, 1.2748789e-05f, 1.3577278e-05f, 1.4459606e-05f, 1.5399272e-05f,
    1.6400004e-05f, 1.7465768e-05f, 1.8600792e-05f, 1.9809576e-05f, 2.1096914e-05f, 2.2467911e-05f, 2.3928002e-05f, 2.5482978e-05f,
    2.7139006e-05f, 2.8902651e-05f, 3.0780908e-05f, 3.2781225e-05f, 3.4911534e-05f, 3.7180282e-05f, 3.9596466e-05f, 4.2169667e-05f,
    4.4910090e-05f, 4.7828601e-05f, 5.0936773e-05f, 5.4246931e-05f, 5.7772202e-05f, 6.1526565e-05f, 6.5524908e-05f, 6.9783085e-05f,
    7.4317983e-05f, 7.9147585e-05f, 8.4291040e-05f, 8.9768747e-05f, 9.5602426e-05f, 0.00010181521f, 0.00010843174f, 0.00011547824f,
    0.00012298267f, 0.00013097477f, 0.00013948625f, 0.00014855085f, 0.00015820453f, 0.00016848555f, 0.00017943469f, 0.00019109536f,
    0.00020351382f, 0.00021673929f, 0.00023082423f, 0.00024582449f, 0.00026179955f, 0.00027881276f, 0.00029693158f, 0.00031622787f,
    0.00033677814f, 0.00035866388f, 0.00038197188f, 0.00040679456f, 0.00043323036f, 0.00046138411f, 0.00049136745f, 0.00052329927f,
    0.00055730621f, 0.00059352311f, 0.00063209358f, 0.00067317058f, 0.00071691700f, 0.00076350630f, 0.00081312324f, 0.00086596457f,
    0.00092223983f, 0.00098217216f, 0.0010459992f,  0.0011139742f,  0.0011863665f,  0.0012634633f,  0.0013455702f,  0.0014330129f,
    0.0015261382f,  0.0016253153f,  0.0017309374f,  0.0018434235f,  0.0019632195f,  0.0020908006f,  0.0022266726f,  0.0023713743f,
    0.0025254795f,  0.0026895994f,  0.0028643847f,  0.0030505286f,  0.0032487691f,  0.0034598925f,  0.0036847358f,  0.0039241906f,
    0.0041792066f,  0.0044507950f,  0.0047400328f,  0.0050480668f,  0.0053761186f,  0.0057254891f,  0.0060975636f,  0.0064938176f,
    0.0069158225f,  0.0073652516f,  0.0078438871f,  0.0083536271f,  0.0088964928f,  0.009474637f,   0.010090352f,   0.010746080f,
    0.011444421f,   0.012188144f,   0.012980198f,   0.013823725f,   0.014722068f,   0.015678791f,   0.016697687f,   0.017782797f,
    0.018938423f,   0.020169149f,   0.021479854f,   0.022875735f,   0.024362330f,   0.025945531f,   0.027631618f,   0.029427276f,
    0.031339626f,   0.033376252f,   0.035545228f,   0.037855157f,   0.040315199f,   0.042935108f,   0.045725273f,   0.048696758f,
    0.051861348f,   0.055231591f,   0.058820850f,   0.062643361f,   0.066714279f,   0.071049749f,   0.075666962f,   0.080584227f,
    0.085821044f,   0.091398179f,   0.097337747f,   0.10366330f,    0.11039993f,    0.11757434f,    0.12521498f,    0.13335215f,
    0.14201813f,    0.15124727f,    0.16107617f,    0.17154380f,    0.18269168f,    0.19456402f,    0.20720788f,    0.22067342f,
    0.23501402f,    0.25028656f,    0.26655159f,    0.28387361f,    0.30232132f,    0.32196786f,    0.34289114f,    0.36517414f,
    0.38890521f,    0.41417847f,    0.44109412f,    0.46975890f,    0.50028648f,    0.53279791f,    0.56742212f,    0.60429640f,
    0.64356699f,    0.68538959f,    0.72993007f,    0.77736504f,    0.82788260f,    0.88168307f,    0.9389798f,     1.0f,
}};

int ilog_u32(uint32_t v) noexcept {
    int r = 0;
    while (v > 0u) {
        ++r;
        v >>= 1;
    }
    return r;
}

double vorbis_float32_unpack(uint32_t val) noexcept {
    int32_t mant = static_cast<int32_t>(val & 0x1FFFFFu);
    const int32_t exp = static_cast<int32_t>((val & 0x7FE00000u) >> 21);
    if (val & 0x80000000u) mant = -mant;
    return std::ldexp(static_cast<double>(mant), exp - 788);
}

struct VorbisBitReader {
    const uint8_t* data = nullptr;
    size_t bitpos = 0;
    size_t total_bits = 0;

    bool read_bit(uint32_t& out) noexcept {
        if (bitpos >= total_bits) return false;
        out = (data[bitpos >> 3] >> (bitpos & 7u)) & 1u;
        ++bitpos;
        return true;
    }

    bool read(int n, uint32_t& out) noexcept {
        if (n == 0) {
            out = 0u;
            return true;
        }
        if (bitpos + static_cast<size_t>(n) > total_bits) return false;
        uint32_t val = 0u;
        for (int i = 0; i < n; ++i) {
            const size_t bp = bitpos + static_cast<size_t>(i);
            if ((data[bp >> 3] >> (bp & 7u)) & 1u) {
                val |= (1u << i);
            }
        }
        bitpos += static_cast<size_t>(n);
        out = val;
        return true;
    }
};

struct VorbisCodebook {
    struct Node {
        int32_t ch[2] = {-1, -1}; // leaf encoded as sym + 0x40000000
    };
    uint32_t dims = 0;
    uint32_t entries = 0;
    std::vector<Node> nodes;
    std::vector<float> values; // entries * dims

    bool build_huffman(const std::vector<int>& lengths) {
        nodes.assign(1u, Node{});
        std::vector<bool> used(1u, false);
        std::vector<std::pair<uint32_t, int>> active;
        for (uint32_t s = 0; s < lengths.size(); ++s) {
            if (lengths[s] > 0) active.emplace_back(s, lengths[s]);
        }
        if (active.size() == 1u) {
            nodes[0].ch[0] = static_cast<int32_t>(active[0].first) + 0x40000000;
            return true;
        }

        auto place = [&](auto& self, uint32_t ni, int depth, uint32_t sym) -> bool {
            if (used[ni]) return false;
            if (depth == 0) {
                if (nodes[ni].ch[0] != -1 || nodes[ni].ch[1] != -1) return false;
                used[ni] = true;
                nodes[ni].ch[0] = static_cast<int32_t>(sym) + 0x40000000;
                return true;
            }
            for (int b = 0; b < 2; ++b) {
                int32_t nxt = nodes[ni].ch[b];
                if (nxt == -1) {
                    nxt = static_cast<int32_t>(nodes.size());
                    nodes[ni].ch[b] = nxt;
                    nodes.push_back(Node{});
                    used.push_back(false);
                }
                if (self(self, static_cast<uint32_t>(nxt), depth - 1, sym)) {
                    if (nodes[ni].ch[0] >= 0 && used[static_cast<size_t>(nodes[ni].ch[0])] &&
                        nodes[ni].ch[1] >= 0 && used[static_cast<size_t>(nodes[ni].ch[1])]) {
                        used[ni] = true;
                    }
                    return true;
                }
            }
            return false;
        };

        for (const auto& [sym, len] : active) {
            if (!place(place, 0u, len, sym)) return false;
        }
        return true;
    }

    bool parse(VorbisBitReader& br) {
        uint32_t sync = 0;
        if (!br.read(24, sync) || sync != 0x564342u) return false;
        uint32_t d = 0, e = 0, ordered = 0;
        if (!br.read(16, d) || !br.read(24, e) || !br.read_bit(ordered)) return false;
        dims = d;
        entries = e;
        if (entries > 65536u || dims > 256u) return false;

        std::vector<int> lengths(entries, 0);
        if (!ordered) {
            uint32_t sparse = 0;
            if (!br.read_bit(sparse)) return false;
            for (uint32_t i = 0; i < entries; ++i) {
                uint32_t v = 0;
                if (sparse) {
                    uint32_t flag = 0;
                    if (!br.read_bit(flag)) return false;
                    if (flag) {
                        if (!br.read(5, v)) return false;
                        lengths[i] = static_cast<int>(v) + 1;
                    }
                } else {
                    if (!br.read(5, v)) return false;
                    lengths[i] = static_cast<int>(v) + 1;
                }
            }
        } else {
            uint32_t cur_len_raw = 0;
            if (!br.read(5, cur_len_raw)) return false;
            int cur_len = static_cast<int>(cur_len_raw) + 1;
            uint32_t cur_entry = 0;
            while (cur_entry < entries) {
                uint32_t num = 0;
                if (!br.read(ilog_u32(entries - cur_entry), num)) return false;
                for (uint32_t k = 0; k < num && cur_entry < entries; ++k) {
                    lengths[cur_entry++] = cur_len;
                }
                ++cur_len;
            }
        }
        if (!build_huffman(lengths)) return false;

        uint32_t ltype = 0;
        if (!br.read(4, ltype)) return false;
        if (ltype == 1u || ltype == 2u) {
            uint32_t min_raw = 0, delta_raw = 0, vbits_raw = 0, seq_p = 0;
            if (!br.read(32, min_raw) || !br.read(32, delta_raw) ||
                !br.read(4, vbits_raw) || !br.read_bit(seq_p)) return false;
            const double min_v = vorbis_float32_unpack(min_raw);
            const double delta_v = vorbis_float32_unpack(delta_raw);
            const int vbits = static_cast<int>(vbits_raw) + 1;
            uint32_t lv = 1;
            if (ltype == 1u) {
                while (std::pow(static_cast<double>(lv + 1u), static_cast<double>(dims)) <=
                       static_cast<double>(entries) + 0.5) {
                    ++lv;
                }
            } else {
                lv = entries * dims;
            }
            std::vector<uint32_t> mults(lv, 0u);
            for (uint32_t i = 0; i < lv; ++i) {
                if (!br.read(vbits, mults[i])) return false;
            }
            values.resize(entries * dims, 0.0f);
            for (uint32_t i = 0; i < entries; ++i) {
                double last = 0.0;
                if (ltype == 1u) {
                    uint32_t idx_div = 1;
                    for (uint32_t k = 0; k < dims; ++k) {
                        const uint32_t off = (i / idx_div) % lv;
                        const double v = static_cast<double>(mults[off]) * delta_v + min_v + last;
                        if (seq_p) last = v;
                        values[i * dims + k] = static_cast<float>(v);
                        idx_div *= lv;
                    }
                } else {
                    const uint32_t base = i * dims;
                    for (uint32_t k = 0; k < dims; ++k) {
                        const double v = static_cast<double>(mults[base + k]) * delta_v + min_v + last;
                        if (seq_p) last = v;
                        values[base + k] = static_cast<float>(v);
                    }
                }
            }
        }
        return true;
    }

    bool decode_scalar(VorbisBitReader& br, uint32_t& out_sym) const noexcept {
        if (nodes.empty()) return false;
        uint32_t cur = 0u;
        for (;;) {
            if (nodes[cur].ch[0] >= 0x40000000) {
                out_sym = static_cast<uint32_t>(nodes[cur].ch[0] - 0x40000000);
                return true;
            }
            uint32_t b = 0;
            if (!br.read_bit(b)) return false;
            const int32_t nxt = nodes[cur].ch[b];
            if (nxt < 0) return false;
            if (nxt >= 0x40000000) {
                out_sym = static_cast<uint32_t>(nxt - 0x40000000);
                return true;
            }
            cur = static_cast<uint32_t>(nxt);
        }
    }
};

struct VorbisFloor1 {
    struct ClassInfo {
        uint8_t dims = 0;
        uint8_t subs = 0;
        uint8_t mbook = 0;
        std::vector<int16_t> subbooks;
    };
    std::vector<uint8_t> part_cls;
    std::vector<ClassInfo> classes;
    uint8_t mult = 1;
    std::vector<int> x_list;
};

struct VorbisResidue {
    uint16_t type = 0;
    uint32_t begin = 0;
    uint32_t end = 0;
    uint32_t psize = 1;
    uint8_t classifications = 1;
    uint8_t classbook = 0;
    std::array<std::array<int16_t, 8>, 64> rbooks{};
};

struct VorbisMapping {
    std::vector<std::pair<uint8_t, uint8_t>> couplings;
    std::vector<uint8_t> ch_mux;
    std::vector<std::pair<uint8_t, uint8_t>> submap_fr;
};

struct VorbisMode {
    uint8_t blockflag = 0;
    uint8_t mapping = 0;
};

void render_floor1_line(int x0, int y0, int x1, int y1, std::vector<int>& v) noexcept {
    if (x1 <= x0) return;
    const int dy = y1 - y0;
    const int adx = x1 - x0;
    int ady = std::abs(dy);
    const int base = dy / adx;
    const int sy = (dy < 0) ? (base - 1) : (base + 1);
    ady -= std::abs(base) * adx;
    int y = y0;
    int err = 0;
    if (x0 >= 0 && static_cast<size_t>(x0) < v.size()) v[static_cast<size_t>(x0)] = y;
    for (int x = x0 + 1; x < x1; ++x) {
        err += ady;
        if (err >= adx) {
            err -= adx;
            y += sy;
        } else {
            y += base;
        }
        if (x >= 0 && static_cast<size_t>(x) < v.size()) v[static_cast<size_t>(x)] = y;
    }
}

void fft_inplace(std::vector<std::complex<double>>& buf) {
    const size_t n = buf.size();
    for (size_t i = 1, j = 0; i < n; ++i) {
        size_t bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) std::swap(buf[i], buf[j]);
    }
    constexpr double kPi = 3.14159265358979323846;
    for (size_t len = 2; len <= n; len <<= 1) {
        const double ang = 2.0 * kPi / static_cast<double>(len);
        const std::complex<double> wlen(std::cos(ang), std::sin(ang));
        const size_t half = len >> 1;
        for (size_t i = 0; i < n; i += len) {
            std::complex<double> w(1.0, 0.0);
            for (size_t k = 0; k < half; ++k) {
                const auto u = buf[i + k];
                const auto v = buf[i + k + half] * w;
                buf[i + k]        = u + v;
                buf[i + k + half] = u - v;
                w *= wlen;
            }
        }
    }
}

void imdct_fft(const std::vector<float>& spec, uint32_t n, std::vector<float>& out) {
    constexpr double kPi = 3.14159265358979323846;
    const uint32_t n2 = n >> 1;
    std::vector<std::complex<double>> buf(n, std::complex<double>(0.0, 0.0));
    const double c_off = (2.0 * kPi / static_cast<double>(n)) * (static_cast<double>(n) * 0.25 + 0.5);
    for (uint32_t k = 0; k < n2; ++k) {
        const double ang = c_off * (static_cast<double>(k) + 0.5);
        buf[k] = std::complex<double>(spec[k] * std::cos(ang), spec[k] * std::sin(ang));
    }
    fft_inplace(buf);
    out.resize(n);
    const double step_ang = kPi / static_cast<double>(n);
    for (uint32_t i = 0; i < n; ++i) {
        const double a = step_ang * static_cast<double>(i);
        out[i] = static_cast<float>(buf[i].real() * std::cos(a) - buf[i].imag() * std::sin(a));
    }
}

struct VorbisStreamState {
    uint32_t datasource_va = 0;
    uint32_t cb_close_va   = 0;
    uint32_t info_guest_va = 0;
    uint32_t channels      = 2;
    uint32_t sample_rate   = 44100;
    double   duration_sec  = 0.0;
    std::vector<int16_t> pcm_interleaved;
    size_t   read_cursor_bytes = 0;
    bool     valid = false;
};

bool decode_ogg_vorbis_to_pcm(const std::vector<uint8_t>& raw, VorbisStreamState& st) {
    if (raw.size() < 32u) return false;

    // 1. Parse OggS pages -> packets & total granule position
    std::vector<std::vector<uint8_t>> packets;
    std::vector<uint8_t> cur_pkt;
    int64_t last_granule = 0;
    size_t pos = 0;
    while (pos + 27u <= raw.size()) {
        if (std::memcmp(raw.data() + pos, "OggS", 4) != 0) break;
        int64_t gran = 0;
        std::memcpy(&gran, raw.data() + pos + 6, sizeof(gran));
        if (gran > 0) last_granule = gran;
        const uint8_t nseg = raw[pos + 26];
        if (pos + 27u + nseg > raw.size()) break;
        const uint8_t* lacing = raw.data() + pos + 27u;
        size_t bpos = pos + 27u + nseg;
        for (uint8_t s = 0; s < nseg; ++s) {
            const uint8_t lv = lacing[s];
            if (bpos + lv > raw.size()) break;
            cur_pkt.insert(cur_pkt.end(), raw.data() + bpos, raw.data() + bpos + lv);
            bpos += lv;
            if (lv < 255u) {
                packets.push_back(std::move(cur_pkt));
                cur_pkt.clear();
            }
        }
        pos = bpos;
    }
    if (packets.size() < 3u) return false;

    // 2. Packet 0: Identification header
    const auto& p0 = packets[0];
    if (p0.size() < 30u || p0[0] != 1u || std::memcmp(p0.data() + 1, "vorbis", 6) != 0) return false;
    const uint8_t ch = p0[11];
    uint32_t rate = 0;
    std::memcpy(&rate, p0.data() + 12, 4);
    const uint8_t bsz = p0[28];
    const uint32_t bs0 = 1u << (bsz & 0x0Fu);
    const uint32_t bs1 = 1u << ((bsz >> 4) & 0x0Fu);
    if (ch == 0u || rate == 0u || bs0 < 64u || bs1 < bs0 || bs1 > 8192u) return false;

    st.channels    = ch;
    st.sample_rate = rate;
    st.duration_sec = (last_granule > 0) ? (static_cast<double>(last_granule) / static_cast<double>(rate)) : 0.0;

    // 3. Packet 2: Setup header
    const auto& p2 = packets[2];
    if (p2.size() < 8u || p2[0] != 5u || std::memcmp(p2.data() + 1, "vorbis", 6) != 0) return false;
    VorbisBitReader br{p2.data(), 7u * 8u, p2.size() * 8u};

    uint32_t tmp = 0;
    if (!br.read(8, tmp)) return false;
    const uint32_t num_books = tmp + 1u;
    std::vector<VorbisCodebook> books(num_books);
    for (uint32_t i = 0; i < num_books; ++i) {
        if (!books[i].parse(br)) return false;
    }

    if (!br.read(6, tmp)) return false;
    const uint32_t time_cnt = tmp + 1u;
    for (uint32_t i = 0; i < time_cnt; ++i) {
        if (!br.read(16, tmp)) return false;
    }

    if (!br.read(6, tmp)) return false;
    const uint32_t floor_cnt = tmp + 1u;
    std::vector<VorbisFloor1> floors(floor_cnt);
    for (uint32_t f = 0; f < floor_cnt; ++f) {
        if (!br.read(16, tmp) || tmp != 1u) return false;
        uint32_t parts = 0;
        if (!br.read(5, parts)) return false;
        floors[f].part_cls.resize(parts);
        int max_cls = -1;
        for (uint32_t i = 0; i < parts; ++i) {
            if (!br.read(4, tmp)) return false;
            floors[f].part_cls[i] = static_cast<uint8_t>(tmp);
            max_cls = std::max(max_cls, static_cast<int>(tmp));
        }
        floors[f].classes.resize(static_cast<size_t>(max_cls + 1));
        for (int c = 0; c <= max_cls; ++c) {
            uint32_t d = 0, s = 0, mb = 0;
            if (!br.read(3, d) || !br.read(2, s)) return false;
            if (s > 0u && !br.read(8, mb)) return false;
            auto& ci = floors[f].classes[static_cast<size_t>(c)];
            ci.dims = static_cast<uint8_t>(d + 1u);
            ci.subs = static_cast<uint8_t>(s);
            ci.mbook = static_cast<uint8_t>(mb);
            ci.subbooks.resize(1u << s);
            for (size_t k = 0; k < ci.subbooks.size(); ++k) {
                uint32_t sb = 0;
                if (!br.read(8, sb)) return false;
                ci.subbooks[k] = static_cast<int16_t>(static_cast<int>(sb) - 1);
            }
        }
        uint32_t mult_raw = 0, rangebits = 0;
        if (!br.read(2, mult_raw) || !br.read(4, rangebits)) return false;
        floors[f].mult = static_cast<uint8_t>(mult_raw + 1u);
        floors[f].x_list = {0, static_cast<int>(1u << rangebits)};
        for (uint8_t pc : floors[f].part_cls) {
            for (uint8_t k = 0; k < floors[f].classes[pc].dims; ++k) {
                if (!br.read(static_cast<int>(rangebits), tmp)) return false;
                floors[f].x_list.push_back(static_cast<int>(tmp));
            }
        }
    }

    if (!br.read(6, tmp)) return false;
    const uint32_t res_cnt = tmp + 1u;
    std::vector<VorbisResidue> residues(res_cnt);
    for (uint32_t r = 0; r < res_cnt; ++r) {
        auto& res = residues[r];
        uint32_t rt = 0, psize = 0, clsn = 0, cb = 0;
        if (!br.read(16, rt) || !br.read(24, res.begin) || !br.read(24, res.end) ||
            !br.read(24, psize) || !br.read(6, clsn) || !br.read(8, cb)) return false;
        res.type = static_cast<uint16_t>(rt);
        res.psize = psize + 1u;
        res.classifications = static_cast<uint8_t>(clsn + 1u);
        res.classbook = static_cast<uint8_t>(cb);
        std::array<uint8_t, 64> casc{};
        for (uint8_t i = 0; i < res.classifications; ++i) {
            uint32_t lo = 0, flag = 0, hi = 0;
            if (!br.read(3, lo) || !br.read_bit(flag)) return false;
            if (flag && !br.read(5, hi)) return false;
            casc[i] = static_cast<uint8_t>((hi << 3) | lo);
        }
        for (uint8_t i = 0; i < res.classifications; ++i) {
            for (int b = 0; b < 8; ++b) {
                if (casc[i] & (1u << b)) {
                    if (!br.read(8, tmp)) return false;
                    res.rbooks[i][b] = static_cast<int16_t>(tmp);
                } else {
                    res.rbooks[i][b] = -1;
                }
            }
        }
    }

    if (!br.read(6, tmp)) return false;
    const uint32_t map_cnt = tmp + 1u;
    std::vector<VorbisMapping> mappings(map_cnt);
    for (uint32_t m = 0; m < map_cnt; ++m) {
        if (!br.read(16, tmp) || tmp != 0u) return false;
        uint32_t has_sub = 0, submaps = 1u, has_coup = 0;
        if (!br.read_bit(has_sub)) return false;
        if (has_sub) {
            if (!br.read(4, submaps)) return false;
            submaps += 1u;
        }
        if (!br.read_bit(has_coup)) return false;
        if (has_coup) {
            uint32_t cs = 0;
            if (!br.read(8, cs)) return false;
            cs += 1u;
            const int cbits = ilog_u32(ch - 1u);
            for (uint32_t i = 0; i < cs; ++i) {
                uint32_t mc = 0, ac = 0;
                if (!br.read(cbits, mc) || !br.read(cbits, ac)) return false;
                mappings[m].couplings.emplace_back(static_cast<uint8_t>(mc), static_cast<uint8_t>(ac));
            }
        }
        if (!br.read(2, tmp) || tmp != 0u) return false;
        mappings[m].ch_mux.assign(ch, 0u);
        if (submaps > 1u) {
            for (uint8_t c = 0; c < ch; ++c) {
                if (!br.read(4, tmp)) return false;
                mappings[m].ch_mux[c] = static_cast<uint8_t>(tmp);
            }
        }
        for (uint32_t s = 0; s < submaps; ++s) {
            uint32_t t0 = 0, fl = 0, rs = 0;
            if (!br.read(8, t0) || !br.read(8, fl) || !br.read(8, rs)) return false;
            mappings[m].submap_fr.emplace_back(static_cast<uint8_t>(fl), static_cast<uint8_t>(rs));
        }
    }

    if (!br.read(6, tmp)) return false;
    const uint32_t mode_cnt = tmp + 1u;
    std::vector<VorbisMode> modes(mode_cnt);
    for (uint32_t m = 0; m < mode_cnt; ++m) {
        uint32_t bf = 0, wt = 0, tt = 0, mp = 0;
        if (!br.read_bit(bf) || !br.read(16, wt) || !br.read(16, tt) || !br.read(8, mp)) return false;
        modes[m] = {static_cast<uint8_t>(bf), static_cast<uint8_t>(mp)};
    }
    if (!br.read_bit(tmp) || tmp != 1u) return false;

    // 4. Precompute Vorbis windows & decode audio packets
    constexpr double kPi = 3.14159265358979323846;
    auto make_win = [&](uint32_t n) {
        const uint32_t half = n >> 1;
        std::vector<float> w(half);
        for (uint32_t i = 0; i < half; ++i) {
            const double s = std::sin(0.5 * kPi * (static_cast<double>(i) + 0.5) / static_cast<double>(half));
            w[i] = static_cast<float>(std::sin(0.5 * kPi * s * s));
        }
        return w;
    };
    const auto win0 = make_win(bs0);
    const auto win1 = make_win(bs1);
    const int mode_bits = ilog_u32(mode_cnt - 1u);
    static constexpr int kRangeLim[5] = {256, 256, 128, 86, 64};

    std::vector<std::vector<float>> prev_right;
    uint32_t prev_n = 0;
    st.pcm_interleaved.clear();

    for (size_t pi = 3u; pi < packets.size(); ++pi) {
        const auto& pkt = packets[pi];
        if (pkt.empty()) continue;
        VorbisBitReader pbr{pkt.data(), 0u, pkt.size() * 8u};
        uint32_t pkt_type = 0, mode_idx = 0;
        if (!pbr.read_bit(pkt_type) || pkt_type != 0u) continue;
        if (!pbr.read(mode_bits, mode_idx) || mode_idx >= mode_cnt) continue;

        const auto& mode = modes[mode_idx];
        const bool bf = mode.blockflag != 0u;
        const uint32_t n = bf ? bs1 : bs0;
        const uint32_t n2 = n >> 1;
        uint32_t prev_w = 0, next_w = 0;
        if (bf) {
            if (!pbr.read_bit(prev_w) || !pbr.read_bit(next_w)) continue;
        }
        const auto& mp = mappings[mode.mapping];

        std::vector<bool> no_res(ch, false);
        std::vector<bool> fl_nz(ch, false);
        std::vector<std::vector<float>> fl_vals(ch);

        for (uint8_t c = 0; c < ch; ++c) {
            const auto& fl = floors[mp.submap_fr[mp.ch_mux[c]].first];
            uint32_t nz = 0;
            if (!pbr.read_bit(nz) || nz == 0u) {
                no_res[c] = true;
                continue;
            }
            fl_nz[c] = true;
            const int rng = kRangeLim[std::min<uint8_t>(fl.mult, 4u)];
            const int rbits = ilog_u32(static_cast<uint32_t>(rng - 1));
            std::vector<int> Y(fl.x_list.size(), 0);
            uint32_t y0 = 0, y1 = 0;
            if (!pbr.read(rbits, y0) || !pbr.read(rbits, y1)) {
                no_res[c] = true;
                continue;
            }
            Y[0] = static_cast<int>(y0);
            Y[1] = static_cast<int>(y1);
            size_t yi = 2;
            bool fl_ok = true;
            for (uint8_t pc : fl.part_cls) {
                const auto& ci = fl.classes[pc];
                const uint32_t csub = (1u << ci.subs) - 1u;
                uint32_t cval = 0;
                if (ci.subs > 0u && !books[ci.mbook].decode_scalar(pbr, cval)) {
                    fl_ok = false;
                    break;
                }
                for (uint8_t k = 0; k < ci.dims; ++k) {
                    const int16_t sb = ci.subbooks[cval & csub];
                    cval >>= ci.subs;
                    uint32_t sym = 0;
                    if (sb >= 0 && !books[static_cast<size_t>(sb)].decode_scalar(pbr, sym)) {
                        fl_ok = false;
                        break;
                    }
                    Y[yi++] = (sb >= 0) ? static_cast<int>(sym) : 0;
                }
                if (!fl_ok) break;
            }
            if (!fl_ok) {
                no_res[c] = true;
                fl_nz[c] = false;
                continue;
            }

            std::vector<bool> step2(fl.x_list.size(), false);
            step2[0] = step2[1] = true;
            std::vector<int> final_Y = Y;
            for (size_t i = 2; i < fl.x_list.size(); ++i) {
                size_t lo_i = 0, hi_i = 1;
                int lo_x = -1, hi_x = 1 << 30;
                for (size_t j = 0; j < i; ++j) {
                    const int xj = fl.x_list[j];
                    if (xj < fl.x_list[i] && xj > lo_x) { lo_x = xj; lo_i = j; }
                    if (xj > fl.x_list[i] && xj < hi_x) { hi_x = xj; hi_i = j; }
                }
                const int predicted = final_Y[lo_i] +
                    ((final_Y[hi_i] - final_Y[lo_i]) * (fl.x_list[i] - fl.x_list[lo_i])) /
                    std::max(1, fl.x_list[hi_i] - fl.x_list[lo_i]);
                const int val = Y[i];
                const int highroom = rng - predicted;
                const int lowroom  = predicted;
                const int room = (highroom > lowroom) ? (lowroom * 2) : (highroom * 2);
                if (val != 0) {
                    step2[lo_i] = step2[hi_i] = step2[i] = true;
                    if (val >= room) {
                        final_Y[i] = (highroom > lowroom) ? (val - lowroom + predicted) : (predicted - val + highroom - 1);
                    } else {
                        final_Y[i] = (val & 1) ? (predicted - ((val + 1) >> 1)) : (predicted + (val >> 1));
                    }
                } else {
                    final_Y[i] = predicted;
                }
            }

            std::vector<size_t> order(fl.x_list.size());
            for (size_t i = 0; i < order.size(); ++i) order[i] = i;
            std::sort(order.begin(), order.end(), [&](size_t a, size_t b) { return fl.x_list[a] < fl.x_list[b]; });
            std::vector<int> curve(n2, 0);
            int lx = fl.x_list[order[0]];
            int ly = final_Y[order[0]] * fl.mult;
            for (size_t k = 1; k < order.size(); ++k) {
                const size_t oi = order[k];
                if (step2[oi]) {
                    const int hx = fl.x_list[oi];
                    const int hy = final_Y[oi] * fl.mult;
                    render_floor1_line(lx, ly, hx, hy, curve);
                    lx = hx;
                    ly = hy;
                }
            }
            for (uint32_t k = static_cast<uint32_t>(std::max(0, lx)); k < n2; ++k) curve[k] = ly;
            fl_vals[c].resize(n2);
            for (uint32_t k = 0; k < n2; ++k) {
                fl_vals[c][k] = kFloor1InvDb[static_cast<size_t>(std::clamp(curve[k], 0, 255))];
            }
        }

        for (const auto& [mc, ac] : mp.couplings) {
            if (!no_res[mc] || !no_res[ac]) {
                no_res[mc] = no_res[ac] = false;
            }
        }

        std::vector<std::vector<float>> res_vecs(ch, std::vector<float>(n2, 0.0f));
        for (size_t sm = 0; sm < mp.submap_fr.size(); ++sm) {
            std::vector<uint8_t> sm_chans;
            for (uint8_t c = 0; c < ch; ++c) {
                if (mp.ch_mux[c] == sm) sm_chans.push_back(c);
            }
            if (sm_chans.empty()) continue;
            const auto& res = residues[mp.submap_fr[sm].second];
            const uint32_t limit_end = std::min<uint32_t>(
                res.end, (res.type == 2u) ? (n2 * static_cast<uint32_t>(sm_chans.size())) : n2);
            const uint32_t n_to_read = (limit_end > res.begin) ? (limit_end - res.begin) : 0u;
            const uint32_t part_read = n_to_read / res.psize;
            const auto& cbook = books[res.classbook];
            const uint32_t cw = std::max<uint32_t>(1u, cbook.dims);
            const uint32_t class_words = (part_read + cw - 1u) / cw;

            if (res.type == 2u) {
                bool all_skip = true;
                for (uint8_t c : sm_chans) {
                    if (!no_res[c]) all_skip = false;
                }
                if (all_skip) continue;
                std::vector<uint8_t> cls_grid(class_words * cw, 0u);
                std::vector<float> flat_out(n2 * sm_chans.size(), 0.0f);
                bool eop = false;
                for (int pass = 0; pass < 8 && !eop; ++pass) {
                    uint32_t pcount = 0;
                    while (pcount < part_read && !eop) {
                        if (pass == 0) {
                            uint32_t temp = 0;
                            if (!cbook.decode_scalar(pbr, temp)) { eop = true; break; }
                            for (int k = static_cast<int>(cw) - 1; k >= 0; --k) {
                                cls_grid[pcount + static_cast<uint32_t>(k)] =
                                    static_cast<uint8_t>(temp % res.classifications);
                                temp /= res.classifications;
                            }
                        }
                        for (uint32_t k = 0; k < cw && pcount < part_read && !eop; ++k, ++pcount) {
                            const int16_t vb_idx = res.rbooks[cls_grid[pcount]][pass];
                            if (vb_idx >= 0) {
                                const auto& vb = books[static_cast<size_t>(vb_idx)];
                                const uint32_t off = res.begin + pcount * res.psize;
                                for (uint32_t i = 0; i < res.psize; i += vb.dims) {
                                    uint32_t sc = 0;
                                    if (!vb.decode_scalar(pbr, sc)) { eop = true; break; }
                                    const float* vv = vb.values.data() + sc * vb.dims;
                                    for (uint32_t d = 0; d < vb.dims; ++d) {
                                        if (off + i + d < flat_out.size()) {
                                            flat_out[off + i + d] += vv[d];
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                for (uint32_t i = 0; i < n2; ++i) {
                    for (size_t ci = 0; ci < sm_chans.size(); ++ci) {
                        res_vecs[sm_chans[ci]][i] = flat_out[i * sm_chans.size() + ci];
                    }
                }
            } else {
                const size_t cc = sm_chans.size();
                std::vector<std::vector<uint8_t>> cls_grid(cc, std::vector<uint8_t>(class_words * cw, 0u));
                bool eop = false;
                for (int pass = 0; pass < 8 && !eop; ++pass) {
                    uint32_t pcount = 0;
                    while (pcount < part_read && !eop) {
                        if (pass == 0) {
                            for (size_t ci = 0; ci < cc; ++ci) {
                                if (no_res[sm_chans[ci]]) continue;
                                uint32_t temp = 0;
                                if (!cbook.decode_scalar(pbr, temp)) { eop = true; break; }
                                for (int k = static_cast<int>(cw) - 1; k >= 0; --k) {
                                    cls_grid[ci][pcount + static_cast<uint32_t>(k)] =
                                        static_cast<uint8_t>(temp % res.classifications);
                                    temp /= res.classifications;
                                }
                            }
                        }
                        for (uint32_t k = 0; k < cw && pcount < part_read && !eop; ++k, ++pcount) {
                            for (size_t ci = 0; ci < cc && !eop; ++ci) {
                                const uint8_t c = sm_chans[ci];
                                if (no_res[c]) continue;
                                const int16_t vb_idx = res.rbooks[cls_grid[ci][pcount]][pass];
                                if (vb_idx >= 0) {
                                    const auto& vb = books[static_cast<size_t>(vb_idx)];
                                    const uint32_t off = res.begin + pcount * res.psize;
                                    if (res.type == 0u) {
                                        const uint32_t step = res.psize / std::max<uint32_t>(1u, vb.dims);
                                        for (uint32_t i = 0; i < step; ++i) {
                                            uint32_t sc = 0;
                                            if (!vb.decode_scalar(pbr, sc)) { eop = true; break; }
                                            const float* vv = vb.values.data() + sc * vb.dims;
                                            for (uint32_t d = 0; d < vb.dims; ++d) {
                                                if (off + i + d * step < n2) res_vecs[c][off + i + d * step] += vv[d];
                                            }
                                        }
                                    } else {
                                        for (uint32_t i = 0; i < res.psize; i += vb.dims) {
                                            uint32_t sc = 0;
                                            if (!vb.decode_scalar(pbr, sc)) { eop = true; break; }
                                            const float* vv = vb.values.data() + sc * vb.dims;
                                            for (uint32_t d = 0; d < vb.dims; ++d) {
                                                if (off + i + d < n2) res_vecs[c][off + i + d] += vv[d];
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        for (auto it = mp.couplings.rbegin(); it != mp.couplings.rend(); ++it) {
            const uint8_t mc = it->first;
            const uint8_t ac = it->second;
            for (uint32_t i = 0; i < n2; ++i) {
                const float M = res_vecs[mc][i];
                const float A = res_vecs[ac][i];
                if (M > 0.0f) {
                    res_vecs[ac][i] = (A > 0.0f) ? (M - A) : M;
                    res_vecs[mc][i] = (A > 0.0f) ? M : (M + A);
                } else {
                    res_vecs[ac][i] = (A > 0.0f) ? (M + A) : M;
                    res_vecs[mc][i] = (A > 0.0f) ? M : (M - A);
                }
            }
        }

        std::vector<std::vector<float>> td_ch(ch, std::vector<float>(n, 0.0f));
        const auto& w_left  = (bf && prev_w) ? win1 : win0;
        const auto& w_right = (bf && next_w) ? win1 : win0;
        for (uint8_t c = 0; c < ch; ++c) {
            std::vector<float> spec(n2, 0.0f);
            if (fl_nz[c]) {
                for (uint32_t k = 0; k < n2; ++k) spec[k] = res_vecs[c][k] * fl_vals[c][k];
            }
            imdct_fft(spec, n, td_ch[c]);
            auto& td = td_ch[c];
            if (bf) {
                const uint32_t ls = (n >> 2) - static_cast<uint32_t>(w_left.size() >> 1);
                for (uint32_t i = 0; i < ls; ++i) td[i] = 0.0f;
                for (size_t i = 0; i < w_left.size(); ++i) td[ls + i] *= w_left[i];
                const uint32_t rs = ((3u * n) >> 2) - static_cast<uint32_t>(w_right.size() >> 1);
                for (size_t i = 0; i < w_right.size(); ++i) td[rs + i] *= w_right[w_right.size() - 1u - i];
                for (size_t i = rs + w_right.size(); i < n; ++i) td[i] = 0.0f;
            } else {
                for (uint32_t i = 0; i < n2; ++i) {
                    td[i] *= w_left[i];
                    td[n2 + i] *= w_right[n2 - 1u - i];
                }
            }
        }

        if (!prev_right.empty()) {
            auto push_frame = [&](uint32_t c_idx, float sample) {
                const int32_t q = static_cast<int32_t>(std::lround(sample * 32767.0f));
                return static_cast<int16_t>(std::clamp(q, -32768, 32767));
            };
            if (prev_n == n) {
                for (uint32_t i = 0; i < n2; ++i) {
                    for (uint8_t c = 0; c < ch; ++c) {
                        st.pcm_interleaved.push_back(push_frame(c, prev_right[c][i] + td_ch[c][i]));
                    }
                }
            } else if (prev_n < n) {
                const uint32_t off = (n - prev_n) >> 2;
                const uint32_t p2  = prev_n >> 1;
                for (uint32_t i = off; i < off + p2; ++i) {
                    for (uint8_t c = 0; c < ch; ++c) {
                        st.pcm_interleaved.push_back(push_frame(c, prev_right[c][i - off] + td_ch[c][i]));
                    }
                }
                for (uint32_t i = off + p2; i < n2; ++i) {
                    for (uint8_t c = 0; c < ch; ++c) {
                        st.pcm_interleaved.push_back(push_frame(c, td_ch[c][i]));
                    }
                }
            } else {
                const uint32_t off = (prev_n - n) >> 2;
                for (uint32_t i = 0; i < off; ++i) {
                    for (uint8_t c = 0; c < ch; ++c) {
                        st.pcm_interleaved.push_back(push_frame(c, prev_right[c][i]));
                    }
                }
                for (uint32_t i = 0; i < n2; ++i) {
                    for (uint8_t c = 0; c < ch; ++c) {
                        st.pcm_interleaved.push_back(push_frame(c, prev_right[c][off + i] + td_ch[c][i]));
                    }
                }
            }
        }

        prev_right.resize(ch);
        for (uint8_t c = 0; c < ch; ++c) {
            prev_right[c].assign(td_ch[c].begin() + n2, td_ch[c].end());
        }
        prev_n = n;
    }

    if (last_granule > 0) {
        const size_t max_samples = static_cast<size_t>(last_granule) * ch;
        if (st.pcm_interleaved.size() > max_samples) {
            st.pcm_interleaved.resize(max_samples);
        }
    }
    st.valid = !st.pcm_interleaved.empty();
    return st.valid;
}

std::mutex g_vorbis_mutex;
std::unordered_map<uint32_t, std::shared_ptr<VorbisStreamState>> g_vorbis_streams;

} // namespace

// ---------------------------------------------------------------------------
// All 76 CRT HLE implementations (matching recompiler/crt_signatures.json)
// ---------------------------------------------------------------------------

// 0x004e00d0: free(ptr) [cdecl]
void hle_crt_004e00d0(CpuContext& ctx, GuestMemory& mem) {
    mem.guest_free(ctx.arg32(mem, 0));
    ctx.ret_cdecl(mem);
}

// 0x004e0177: operator new(size) [cdecl]
void hle_crt_004e0177(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t sz = std::max<uint32_t>(1u, ctx.arg32(mem, 0));
    ctx.eax = mem.guest_alloc(sz, 16u);
    ctx.ret_cdecl(mem);
}

// 0x004e0230: malloc(size) [cdecl]
void hle_crt_004e0230(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t sz = std::max<uint32_t>(1u, ctx.arg32(mem, 0));
    ctx.eax = mem.guest_alloc(sz, 16u);
    ctx.ret_cdecl(mem);
}

// 0x004e02f3: operator delete(ptr) [cdecl]
void hle_crt_004e02f3(CpuContext& ctx, GuestMemory& mem) {
    hle_crt_004e00d0(ctx, mem);
}

// 0x004e02f8: __security_check_cookie(ecx) [fastcall_ecx]
void hle_crt_004e02f8(CpuContext& ctx, GuestMemory& mem) {
    ctx.ret_cdecl(mem);
}

// 0x004e0307: operator delete[](ptr) [cdecl]
void hle_crt_004e0307(CpuContext& ctx, GuestMemory& mem) {
    hle_crt_004e00d0(ctx, mem);
}

// 0x004e0675: operator new[](size) [cdecl]
void hle_crt_004e0675(CpuContext& ctx, GuestMemory& mem) {
    hle_crt_004e0177(ctx, mem);
}

// 0x004e0680: operator new[](size) variant [cdecl]
void hle_crt_004e0680(CpuContext& ctx, GuestMemory& mem) {
    hle_crt_004e0177(ctx, mem);
}

// 0x004e068b: sprintf(buf, fmt, ...) [cdecl]
void hle_crt_004e068b(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t buf_va = ctx.arg32(mem, 0);
    const std::string fmt = mem.read_cstring(ctx.arg32(mem, 1));
    const std::string out = format_guest_printf(mem, fmt, ctx.esp + 12u);
    ctx.eax = static_cast<uint32_t>(write_formatted_cstr(mem, buf_va, 0u, false, out));
    ctx.ret_cdecl(mem);
}

// 0x004e0706: strncmp(s1, s2, count) [cdecl]
void hle_crt_004e0706(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t s1_va = ctx.arg32(mem, 0);
    const uint32_t s2_va = ctx.arg32(mem, 1);
    const uint32_t cnt   = ctx.arg32(mem, 2);
    int res = 0;
    if (cnt > 0u) {
        for (uint32_t i = 0; i < cnt; ++i) {
            const uint8_t a = mem.r8(s1_va + i);
            const uint8_t b = mem.r8(s2_va + i);
            if (a != b) { res = (a < b) ? -1 : 1; break; }
            if (a == 0u) break;
        }
    }
    ctx.eax = static_cast<uint32_t>(res);
    ctx.ret_cdecl(mem);
}

// 0x004e07c4: std::exception::exception() [thiscall]
void hle_crt_004e07c4(CpuContext& ctx, GuestMemory& mem) {
    if (ctx.ecx != 0u) {
        mem.w32(ctx.ecx + 0u, 0x0051BD40u);
        mem.w32(ctx.ecx + 4u, 0u);
        mem.w32(ctx.ecx + 8u, 0u);
    }
    ctx.eax = ctx.ecx;
    ctx.ret_cdecl(mem);
}

// 0x004e07d5: std::exception::exception(const char* const&) [thiscall, clean=4]
void hle_crt_004e07d5(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pwhat_va = ctx.arg32(mem, 0);
    if (ctx.ecx != 0u) {
        mem.w32(ctx.ecx + 0u, 0x0051BD40u);
        const uint32_t str_va = pwhat_va ? mem.r32(pwhat_va) : 0u;
        if (str_va != 0u) {
            const std::string s = mem.read_cstring(str_va);
            const uint32_t buf = mem.guest_alloc(static_cast<uint32_t>(s.size() + 1u));
            mem.write_cstring(buf, s);
            mem.w32(ctx.ecx + 4u, buf);
            mem.w32(ctx.ecx + 8u, 1u);
        } else {
            mem.w32(ctx.ecx + 4u, 0u);
            mem.w32(ctx.ecx + 8u, 0u);
        }
    }
    ctx.eax = ctx.ecx;
    ctx.ret_stdcall(mem, 4u);
}

// 0x004e083b: std::exception::exception(const std::exception&) [thiscall, clean=4]
void hle_crt_004e083b(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t rhs_va = ctx.arg32(mem, 0);
    if (ctx.ecx != 0u) {
        mem.w32(ctx.ecx + 0u, 0x0051BD40u);
        const uint32_t own = rhs_va ? mem.r32(rhs_va + 8u) : 0u;
        const uint32_t src = rhs_va ? mem.r32(rhs_va + 4u) : 0u;
        if (own != 0u && src != 0u) {
            const std::string s = mem.read_cstring(src);
            const uint32_t buf = mem.guest_alloc(static_cast<uint32_t>(s.size() + 1u));
            mem.write_cstring(buf, s);
            mem.w32(ctx.ecx + 4u, buf);
            mem.w32(ctx.ecx + 8u, 1u);
        } else {
            mem.w32(ctx.ecx + 4u, src);
            mem.w32(ctx.ecx + 8u, 0u);
        }
    }
    ctx.eax = ctx.ecx;
    ctx.ret_stdcall(mem, 4u);
}

// 0x004e0893: std::exception::~exception() [thiscall]
void hle_crt_004e0893(CpuContext& ctx, GuestMemory& mem) {
    if (ctx.ecx != 0u) {
        mem.w32(ctx.ecx + 0u, 0x0051BD40u);
        if (mem.r32(ctx.ecx + 8u) != 0u) {
            mem.guest_free(mem.r32(ctx.ecx + 4u));
        }
    }
    ctx.ret_cdecl(mem);
}

// 0x004e0917: memcpy_s(dest, destsz, src, count) [cdecl]
void hle_crt_004e0917(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t dst   = ctx.arg32(mem, 0);
    const uint32_t dstsz = ctx.arg32(mem, 1);
    const uint32_t src   = ctx.arg32(mem, 2);
    const uint32_t cnt   = ctx.arg32(mem, 3);
    if (cnt == 0u) {
        ctx.eax = 0u;
    } else if (dst == 0u || src == 0u) {
        if (dst != 0u && dstsz > 0u) mem.zero_bytes(dst, dstsz);
        ctx.eax = 22u; // EINVAL
    } else if (cnt > dstsz) {
        mem.zero_bytes(dst, dstsz);
        ctx.eax = 34u; // ERANGE
    } else {
        std::memmove(mem.ptr(dst), mem.cptr(src), cnt);
        ctx.eax = 0u;
    }
    ctx.ret_cdecl(mem);
}

// 0x004e0ab6: atexit(func) [cdecl]
void hle_crt_004e0ab6(CpuContext& ctx, GuestMemory& mem) {
    {
        std::lock_guard<std::mutex> lock(g_crt_mutex);
        g_atexit_funcs.push_back(ctx.arg32(mem, 0));
    }
    ctx.eax = 0u;
    ctx.ret_cdecl(mem);
}

// 0x004e0bf2: _invalid_parameter_noinfo() [cdecl]
void hle_crt_004e0bf2(CpuContext& ctx, GuestMemory& mem) {
    ctx.ret_cdecl(mem);
}

// 0x004e0c02: memmove_s(dest, destsz, src, count) [cdecl]
void hle_crt_004e0c02(CpuContext& ctx, GuestMemory& mem) {
    hle_crt_004e0917(ctx, mem);
}

// 0x004e0cc5: sscanf(str, fmt, ...) [cdecl]
void hle_crt_004e0cc5(CpuContext& ctx, GuestMemory& mem) {
    const int n = run_guest_sscanf(mem, ctx.arg32(mem, 0), ctx.arg32(mem, 1), ctx.esp + 12u);
    ctx.eax = static_cast<uint32_t>(n);
    ctx.ret_cdecl(mem);
}

// 0x004e0cf0: strncpy(dest, src, count) [cdecl]
void hle_crt_004e0cf0(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t dst = ctx.arg32(mem, 0);
    const uint32_t src = ctx.arg32(mem, 1);
    const uint32_t cnt = ctx.arg32(mem, 2);
    if (dst && src && cnt > 0u) {
        uint32_t i = 0;
        for (; i < cnt; ++i) {
            const uint8_t ch = mem.r8(src + i);
            mem.w8(dst + i, ch);
            if (ch == 0u) { ++i; break; }
        }
        for (; i < cnt; ++i) mem.w8(dst + i, 0u);
    }
    ctx.eax = dst;
    ctx.ret_cdecl(mem);
}

// 0x004e0e20: strstr(haystack, needle) [cdecl]
void hle_crt_004e0e20(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t hay_va = ctx.arg32(mem, 0);
    const uint32_t ndl_va = ctx.arg32(mem, 1);
    const std::string hay = mem.read_cstring(hay_va, 65536u);
    const std::string ndl = mem.read_cstring(ndl_va, 4096u);
    if (ndl.empty()) {
        ctx.eax = hay_va;
    } else {
        const size_t pos = hay.find(ndl);
        ctx.eax = (pos == std::string::npos) ? 0u : (hay_va + static_cast<uint32_t>(pos));
    }
    ctx.ret_cdecl(mem);
}

// 0x004e0eb7: atoi(str) [cdecl]
void hle_crt_004e0eb7(CpuContext& ctx, GuestMemory& mem) {
    const std::string s = mem.read_cstring(ctx.arg32(mem, 0));
    ctx.eax = static_cast<uint32_t>(static_cast<int32_t>(std::strtol(s.c_str(), nullptr, 10)));
    ctx.ret_cdecl(mem);
}

// 0x004e0fe7: atof(str) [cdecl, returns st(0)]
void hle_crt_004e0fe7(CpuContext& ctx, GuestMemory& mem) {
    const std::string s = mem.read_cstring(ctx.arg32(mem, 0));
    ctx.fpu_push(std::strtod(s.c_str(), nullptr));
    ctx.ret_cdecl(mem);
}

// 0x004e10aa: _get_crtheap() [cdecl]
void hle_crt_004e10aa(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = 0x10000008u;
    ctx.ret_cdecl(mem);
}

// 0x004e1340: exit(status) [cdecl]
void hle_crt_004e1340(CpuContext& ctx, GuestMemory& mem) {
    hle_win32_post_quit(static_cast<int>(ctx.arg32(mem, 0)));
    ctx.ret_cdecl(mem);
}

// 0x004e13cc: realloc(ptr, new_size) [cdecl]
void hle_crt_004e13cc(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = mem.guest_realloc(ctx.arg32(mem, 0), ctx.arg32(mem, 1));
    ctx.ret_cdecl(mem);
}

// 0x004e1660: strrchr(str, c) [cdecl]
void hle_crt_004e1660(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t s_va = ctx.arg32(mem, 0);
    const uint8_t  ch   = static_cast<uint8_t>(ctx.arg32(mem, 1) & 0xFFu);
    const std::string s = mem.read_cstring(s_va, 65536u);
    if (ch == 0u) {
        ctx.eax = s_va + static_cast<uint32_t>(s.size());
    } else {
        const size_t pos = s.rfind(static_cast<char>(ch));
        ctx.eax = (pos == std::string::npos) ? 0u : (s_va + static_cast<uint32_t>(pos));
    }
    ctx.ret_cdecl(mem);
}

// 0x004e18d3: wcstombs(mbstr, wcstr, count) [cdecl]
void hle_crt_004e18d3(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t mb_va  = ctx.arg32(mem, 0);
    const uint32_t wc_va  = ctx.arg32(mem, 1);
    const uint32_t count  = ctx.arg32(mem, 2);
    const auto wstr = mem.read_wstring_utf16(wc_va);
    std::string narrow;
    narrow.reserve(wstr.size());
    for (char16_t c : wstr) narrow.push_back(static_cast<char>(c & 0x7Fu));
    if (mb_va != 0u && count > 0u) {
        const uint32_t n = std::min<uint32_t>(count, static_cast<uint32_t>(narrow.size()));
        mem.write_bytes(mb_va, narrow.data(), n);
        if (n < count) mem.w8(mb_va + n, 0u);
        ctx.eax = n;
    } else {
        ctx.eax = static_cast<uint32_t>(narrow.size());
    }
    ctx.ret_cdecl(mem);
}

// 0x004e1900: strchr(str, c) [cdecl]
void hle_crt_004e1900(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t s_va = ctx.arg32(mem, 0);
    const uint8_t  ch   = static_cast<uint8_t>(ctx.arg32(mem, 1) & 0xFFu);
    const std::string s = mem.read_cstring(s_va, 65536u);
    if (ch == 0u) {
        ctx.eax = s_va + static_cast<uint32_t>(s.size());
    } else {
        const size_t pos = s.find(static_cast<char>(ch));
        ctx.eax = (pos == std::string::npos) ? 0u : (s_va + static_cast<uint32_t>(pos));
    }
    ctx.ret_cdecl(mem);
}

// 0x004e1a12: isalnum(c) [cdecl]
void hle_crt_004e1a12(CpuContext& ctx, GuestMemory& mem) {
    const int c = static_cast<int>(ctx.arg32(mem, 0) & 0xFFu);
    ctx.eax = std::isalnum(c) ? 1u : 0u;
    ctx.ret_cdecl(mem);
}

// 0x004e1a8c: isdigit(c) [cdecl]
void hle_crt_004e1a8c(CpuContext& ctx, GuestMemory& mem) {
    const int c = static_cast<int>(ctx.arg32(mem, 0) & 0xFFu);
    ctx.eax = std::isdigit(c) ? 4u : 0u;
    ctx.ret_cdecl(mem);
}

// 0x004e1b09: isprint(c) [cdecl]
void hle_crt_004e1b09(CpuContext& ctx, GuestMemory& mem) {
    const int c = static_cast<int>(ctx.arg32(mem, 0) & 0xFFu);
    ctx.eax = (c >= 0x20 && c <= 0x7E) ? 0x80u : 0u;
    ctx.ret_cdecl(mem);
}

// 0x004e1c34: __ehvec_dtor(ptr, size, count, dtor) [stdcall, clean=16]
void hle_crt_004e1c34(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t ptr   = ctx.arg32(mem, 0);
    const uint32_t size  = ctx.arg32(mem, 1);
    const int32_t  count = static_cast<int32_t>(ctx.arg32(mem, 2));
    const uint32_t dtor  = ctx.arg32(mem, 3);
    if (dtor != 0u && ptr != 0u && count > 0) {
        for (int32_t i = count - 1; i >= 0; --i) {
            ctx.ecx = ptr + static_cast<uint32_t>(i) * size;
            ctx.push32(mem, 0x00FFFFF4u);
            call_indirect(ctx, mem, dtor);
        }
    }
    ctx.ret_stdcall(mem, 16u);
}

// 0x004e1c97: __ehvec_ctor(ptr, size, count, ctor, dtor) [stdcall, clean=20]
void hle_crt_004e1c97(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t ptr   = ctx.arg32(mem, 0);
    const uint32_t size  = ctx.arg32(mem, 1);
    const int32_t  count = static_cast<int32_t>(ctx.arg32(mem, 2));
    const uint32_t ctor  = ctx.arg32(mem, 3);
    if (ctor != 0u && ptr != 0u && count > 0) {
        for (int32_t i = 0; i < count; ++i) {
            ctx.ecx = ptr + static_cast<uint32_t>(i) * size;
            ctx.push32(mem, 0x00FFFFF5u);
            call_indirect(ctx, mem, ctor);
        }
    }
    ctx.ret_stdcall(mem, 20u);
}

// 0x004e1cfc: _time64(timer) [cdecl]
void hle_crt_004e1cfc(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t timer_va = ctx.arg32(mem, 0);
    const int64_t t = static_cast<int64_t>(std::time(nullptr));
    if (timer_va != 0u) mem.w64(timer_va, static_cast<uint64_t>(t));
    ctx.eax = static_cast<uint32_t>(static_cast<uint64_t>(t) & 0xFFFFFFFFu);
    ctx.edx = static_cast<uint32_t>(static_cast<uint64_t>(t) >> 32);
    ctx.ret_cdecl(mem);
}

// 0x004e1d40: memchr(buf, c, count) [cdecl]
void hle_crt_004e1d40(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t buf = ctx.arg32(mem, 0);
    const uint8_t  c   = static_cast<uint8_t>(ctx.arg32(mem, 1) & 0xFFu);
    const uint32_t cnt = ctx.arg32(mem, 2);
    const uint8_t* p = mem.cptr(buf);
    if (p && mem.in_bounds(buf, cnt)) {
        const void* found = std::memchr(p, c, cnt);
        ctx.eax = found ? (buf + static_cast<uint32_t>(static_cast<const uint8_t*>(found) - p)) : 0u;
    } else {
        ctx.eax = 0u;
    }
    ctx.ret_cdecl(mem);
}

// 0x004e1ded: _difftime64(time1, time0) [cdecl, returns st(0)]
void hle_crt_004e1ded(CpuContext& ctx, GuestMemory& mem) {
    const int64_t t1 = static_cast<int64_t>(mem.r64(ctx.esp + 4u));
    const int64_t t0 = static_cast<int64_t>(mem.r64(ctx.esp + 12u));
    ctx.fpu_push(std::difftime(static_cast<std::time_t>(t1), static_cast<std::time_t>(t0)));
    ctx.ret_cdecl(mem);
}

// 0x004e1e2e: _endthreadex(retval) [cdecl]
void hle_crt_004e1e2e(CpuContext& ctx, GuestMemory& mem) {
    ctx.ret_cdecl(mem);
}

// 0x004e1f28: _beginthreadex(security, stack_size, start_addr, arglist, initflag, thrdaddr) [cdecl]
void hle_crt_004e1f28(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t start_va  = ctx.arg32(mem, 2);
    const uint32_t arglist   = ctx.arg32(mem, 3);
    const uint32_t thrd_addr = ctx.arg32(mem, 5);
    if (start_va == 0u) {
        ctx.eax = 0u;
        ctx.ret_cdecl(mem);
        return;
    }
    const uint32_t child_esp = mem.alloc_thread_stack();
    if (child_esp == 0u) {
        ctx.eax = 0u;
        ctx.ret_cdecl(mem);
        return;
    }
    if (thrd_addr != 0u) mem.w32(thrd_addr, 0x3000u);
    GuestMemory* mptr = &mem;
    try {
        std::thread([mptr, start_va, arglist, child_esp]() {
            struct ThreadStackGuard {
                GuestMemory* mem_ptr;
                uint32_t esp;
                ~ThreadStackGuard() {
                    if (mem_ptr != nullptr && esp != 0u) {
                        mem_ptr->free_thread_stack(esp);
                    }
                }
            } stack_guard{mptr, child_esp};

            CpuContext tctx;
            tctx.reset(child_esp, GuestMemory::kTebBase);
            tctx.push32(*mptr, arglist);
            tctx.push32(*mptr, 0x00FFFFF6u);
            call_indirect(tctx, *mptr, start_va);
        }).detach();
    } catch (...) {
        mem.free_thread_stack(child_esp);
        ctx.eax = 0u;
        ctx.ret_cdecl(mem);
        return;
    }
    ctx.eax = 0x20009001u;
    ctx.ret_cdecl(mem);
}

// 0x004e20de: _stricmp(s1, s2) [cdecl]
void hle_crt_004e20de(CpuContext& ctx, GuestMemory& mem) {
    const std::string a = mem.read_cstring(ctx.arg32(mem, 0));
    const std::string b = mem.read_cstring(ctx.arg32(mem, 1));
    int res = 0;
    const size_t n = std::max(a.size(), b.size());
    for (size_t i = 0; i <= n; ++i) {
        const int ca = (i < a.size()) ? std::tolower(static_cast<unsigned char>(a[i])) : 0;
        const int cb = (i < b.size()) ? std::tolower(static_cast<unsigned char>(b[i])) : 0;
        if (ca != cb) { res = (ca < cb) ? -1 : 1; break; }
        if (ca == 0) break;
    }
    ctx.eax = static_cast<uint32_t>(res);
    ctx.ret_cdecl(mem);
}

// 0x004e21df: _vsnprintf(buf, count, fmt, ap) [cdecl]
void hle_crt_004e21df(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t buf_va = ctx.arg32(mem, 0);
    const uint32_t count  = ctx.arg32(mem, 1);
    const std::string fmt = mem.read_cstring(ctx.arg32(mem, 2));
    const uint32_t ap_va  = ctx.arg32(mem, 3);
    const std::string out = format_guest_printf(mem, fmt, ap_va);
    ctx.eax = static_cast<uint32_t>(write_formatted_cstr(mem, buf_va, count, true, out));
    ctx.ret_cdecl(mem);
}

// 0x004e2ca0: strftime(str, maxsize, fmt, timeptr) [cdecl]
void hle_crt_004e2ca0(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t dst_va  = ctx.arg32(mem, 0);
    const uint32_t maxsz   = ctx.arg32(mem, 1);
    const std::string fmt  = mem.read_cstring(ctx.arg32(mem, 2));
    const uint32_t tm_va   = ctx.arg32(mem, 3);
    std::tm tm_val{};
    if (tm_va != 0u) {
        tm_val.tm_sec   = static_cast<int>(mem.r32(tm_va + 0u));
        tm_val.tm_min   = static_cast<int>(mem.r32(tm_va + 4u));
        tm_val.tm_hour  = static_cast<int>(mem.r32(tm_va + 8u));
        tm_val.tm_mday  = static_cast<int>(mem.r32(tm_va + 12u));
        tm_val.tm_mon   = static_cast<int>(mem.r32(tm_va + 16u));
        tm_val.tm_year  = static_cast<int>(mem.r32(tm_va + 20u));
        tm_val.tm_wday  = static_cast<int>(mem.r32(tm_va + 24u));
        tm_val.tm_yday  = static_cast<int>(mem.r32(tm_va + 28u));
        tm_val.tm_isdst = static_cast<int>(mem.r32(tm_va + 32u));
    }
    std::vector<char> buf(std::max<size_t>(maxsz, 64u), '\0');
    const size_t n = std::strftime(buf.data(), maxsz, fmt.c_str(), &tm_val);
    if (dst_va != 0u && maxsz > 0u) mem.write_bytes(dst_va, buf.data(), std::min<size_t>(n + 1u, maxsz));
    ctx.eax = static_cast<uint32_t>(n);
    ctx.ret_cdecl(mem);
}

// 0x004e2cbd: remove(path) [cdecl]
void hle_crt_004e2cbd(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t path_va = ctx.arg32(mem, 0);
    const std::string raw = mem.read_cstring(path_va);
    const std::string resolved = raw.empty() ? std::string() : hle_win32_resolve_path(raw, true);
    std::error_code ec;
    const bool ok = !resolved.empty() && std::filesystem::remove(resolved, ec);
    ctx.eax = ok ? 0u : 0xFFFFFFFFu;
    ctx.ret_cdecl(mem);
}

// 0x004e2d59: fclose(stream) [cdecl]
void hle_crt_004e2d59(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = 0u;
    ctx.ret_cdecl(mem);
}

// 0x004e309a: _localtime32(timep) [cdecl]
void hle_crt_004e309a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t tp = ctx.arg32(mem, 0);
    const std::time_t t = tp ? static_cast<std::time_t>(static_cast<int32_t>(mem.r32(tp))) : std::time(nullptr);
    std::tm tm_val{};
#if !defined(_WIN32)
    ::localtime_r(&t, &tm_val);
#else
    ::localtime_s(&tm_val, &t);
#endif
    {
        std::lock_guard<std::mutex> lock(g_crt_mutex);
        if (g_localtime_buf_va == 0u) g_localtime_buf_va = mem.alloc_thunk_block(64u, 4u);
    }
    mem.w32(g_localtime_buf_va + 0u,  static_cast<uint32_t>(tm_val.tm_sec));
    mem.w32(g_localtime_buf_va + 4u,  static_cast<uint32_t>(tm_val.tm_min));
    mem.w32(g_localtime_buf_va + 8u,  static_cast<uint32_t>(tm_val.tm_hour));
    mem.w32(g_localtime_buf_va + 12u, static_cast<uint32_t>(tm_val.tm_mday));
    mem.w32(g_localtime_buf_va + 16u, static_cast<uint32_t>(tm_val.tm_mon));
    mem.w32(g_localtime_buf_va + 20u, static_cast<uint32_t>(tm_val.tm_year));
    mem.w32(g_localtime_buf_va + 24u, static_cast<uint32_t>(tm_val.tm_wday));
    mem.w32(g_localtime_buf_va + 28u, static_cast<uint32_t>(tm_val.tm_yday));
    mem.w32(g_localtime_buf_va + 32u, static_cast<uint32_t>(tm_val.tm_isdst));
    ctx.eax = g_localtime_buf_va;
    ctx.ret_cdecl(mem);
}

// 0x004e30be: _snprintf(buf, count, fmt, ...) [cdecl]
void hle_crt_004e30be(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t buf_va = ctx.arg32(mem, 0);
    const uint32_t count  = ctx.arg32(mem, 1);
    const std::string fmt = mem.read_cstring(ctx.arg32(mem, 2));
    const std::string out = format_guest_printf(mem, fmt, ctx.esp + 16u);
    ctx.eax = static_cast<uint32_t>(write_formatted_cstr(mem, buf_va, count, true, out));
    ctx.ret_cdecl(mem);
}

// 0x004e325b: _strnicmp(s1, s2, count) [cdecl]
void hle_crt_004e325b(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t s1_va = ctx.arg32(mem, 0);
    const uint32_t s2_va = ctx.arg32(mem, 1);
    const uint32_t cnt   = ctx.arg32(mem, 2);
    int res = 0;
    for (uint32_t i = 0; i < cnt; ++i) {
        const int ca = std::tolower(mem.r8(s1_va + i));
        const int cb = std::tolower(mem.r8(s2_va + i));
        if (ca != cb) { res = (ca < cb) ? -1 : 1; break; }
        if (ca == 0) break;
    }
    ctx.eax = static_cast<uint32_t>(res);
    ctx.ret_cdecl(mem);
}

// 0x004e3333: vsprintf(buf, fmt, ap) [cdecl]
void hle_crt_004e3333(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t buf_va = ctx.arg32(mem, 0);
    const std::string fmt = mem.read_cstring(ctx.arg32(mem, 1));
    const std::string out = format_guest_printf(mem, fmt, ctx.arg32(mem, 2));
    ctx.eax = static_cast<uint32_t>(write_formatted_cstr(mem, buf_va, 0u, false, out));
    ctx.ret_cdecl(mem);
}

// 0x004e334a: _controlfp_s(currentControl, newControl, mask) [cdecl]
void hle_crt_004e334a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t cur_va  = ctx.arg32(mem, 0);
    const uint32_t new_ctl = ctx.arg32(mem, 1);
    const uint32_t mask    = ctx.arg32(mem, 2);
    if (mask != 0u) {
        const uint16_t rc_pc_bits = static_cast<uint16_t>((new_ctl & mask) & 0x0F00u);
        ctx.fpu_cw = static_cast<uint16_t>((ctx.fpu_cw & ~0x0F00u) | rc_pc_bits);
    }
    if (cur_va != 0u) mem.w32(cur_va, ctx.fpu_cw);
    ctx.eax = 0u;
    ctx.ret_cdecl(mem);
}

// 0x004e34e2: _clearfp() [cdecl]
void hle_crt_004e34e2(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t prev = ctx.fpu_sw & 0x00BFu;
    ctx.fpu_sw &= static_cast<uint16_t>(~0x00BFu);
    ctx.eax = prev;
    ctx.ret_cdecl(mem);
}

// 0x004e3b12: toupper(c) [cdecl]
void hle_crt_004e3b12(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t c = ctx.arg32(mem, 0);
    ctx.eax = (c >= 'a' && c <= 'z') ? (c - 0x20u) : c;
    ctx.ret_cdecl(mem);
}

// 0x004e3e1b: _CxxThrowException(pExceptionObject, pThrowInfo) [stdcall, clean=8]
void hle_crt_004e3e1b(CpuContext& ctx, GuestMemory& mem) {
    std::fprintf(stderr, "[hle_crt] _CxxThrowException(obj=0x%08x, info=0x%08x)\n",
                 ctx.arg32(mem, 0), ctx.arg32(mem, 1));
    ctx.ret_stdcall(mem, 8u);
}

// 0x004e422c: __EH_prolog3 [custom_stack]
void hle_crt_004e422c(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t ret_addr   = mem.r32(ctx.esp);
    const uint32_t frame_size = mem.r32(ctx.esp + 4u);
    const uint32_t handler    = ctx.eax;
    const uint32_t new_ebp    = ctx.esp + 4u;
    const uint32_t old_fs0    = mem.r32(ctx.fs_0);

    mem.w32(new_ebp - 8u, handler);
    mem.w32(new_ebp - 12u, old_fs0);
    ctx.esp = (new_ebp - 12u) - frame_size;
    ctx.push32(mem, ctx.ebx);
    ctx.push32(mem, ctx.esi);
    ctx.push32(mem, ctx.edi);
    mem.w32(new_ebp, ctx.ebp);
    ctx.ebp = new_ebp;
    ctx.push32(mem, mem.r32(0x0054B458u) ^ ctx.ebp);
    mem.w32(ctx.ebp - 4u, 0xFFFFFFFFu);
    mem.w32(ctx.fs_0, ctx.ebp - 12u);
    ctx.eip = ret_addr;
}

// 0x004e6340: memset(dest, c, count) [cdecl]
void hle_crt_004e6340(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t dst = ctx.arg32(mem, 0);
    const uint8_t  c   = static_cast<uint8_t>(ctx.arg32(mem, 1) & 0xFFu);
    const uint32_t cnt = ctx.arg32(mem, 2);
    if (dst && cnt > 0u && mem.in_bounds(dst, cnt)) {
        std::memset(mem.ptr(dst), c, cnt);
    }
    ctx.eax = dst;
    ctx.ret_cdecl(mem);
}

// 0x004e63c0: memcpy(dest, src, count) [cdecl]
void hle_crt_004e63c0(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t dst = ctx.arg32(mem, 0);
    const uint32_t src = ctx.arg32(mem, 1);
    const uint32_t cnt = ctx.arg32(mem, 2);
    if (dst && src && cnt > 0u && mem.in_bounds(dst, cnt) && mem.in_bounds(src, cnt)) {
        std::memmove(mem.ptr(dst), mem.cptr(src), cnt);
    }
    ctx.eax = dst;
    ctx.ret_cdecl(mem);
}

// 0x004eae60: _alldiv(a, b) [stdcall, clean=16]
void hle_crt_004eae60(CpuContext& ctx, GuestMemory& mem) {
    const int64_t a = static_cast<int64_t>(mem.r64(ctx.esp + 4u));
    const int64_t b = static_cast<int64_t>(mem.r64(ctx.esp + 12u));
    const int64_t q = (b != 0) ? (a / b) : 0;
    ctx.eax = static_cast<uint32_t>(static_cast<uint64_t>(q) & 0xFFFFFFFFu);
    ctx.edx = static_cast<uint32_t>(static_cast<uint64_t>(q) >> 32);
    ctx.ret_stdcall(mem, 16u);
}

// 0x004eaf10: _allrem(a, b) [stdcall, clean=16]
void hle_crt_004eaf10(CpuContext& ctx, GuestMemory& mem) {
    const int64_t a = static_cast<int64_t>(mem.r64(ctx.esp + 4u));
    const int64_t b = static_cast<int64_t>(mem.r64(ctx.esp + 12u));
    const int64_t r = (b != 0) ? (a % b) : 0;
    ctx.eax = static_cast<uint32_t>(static_cast<uint64_t>(r) & 0xFFFFFFFFu);
    ctx.edx = static_cast<uint32_t>(static_cast<uint64_t>(r) >> 32);
    ctx.ret_stdcall(mem, 16u);
}

// 0x004edba0: _allmul(a, b) [stdcall, clean=16]
void hle_crt_004edba0(CpuContext& ctx, GuestMemory& mem) {
    const int64_t a = static_cast<int64_t>(mem.r64(ctx.esp + 4u));
    const int64_t b = static_cast<int64_t>(mem.r64(ctx.esp + 12u));
    const uint64_t p = static_cast<uint64_t>(a) * static_cast<uint64_t>(b);
    ctx.eax = static_cast<uint32_t>(p & 0xFFFFFFFFu);
    ctx.edx = static_cast<uint32_t>(p >> 32);
    ctx.ret_stdcall(mem, 16u);
}

// 0x004efab0: __alloca_probe (__chkstk) [custom_stack]
void hle_crt_004efab0(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t ret_addr = mem.r32(ctx.esp);
    const uint32_t sz       = ctx.eax;
    const uint32_t new_esp  = (ctx.esp >= sz) ? (ctx.esp - sz) : 0u;
    ctx.esp = new_esp + 4u;
    ctx.eax = ret_addr;
    ctx.eip = ret_addr;
}

// 0x004f0a50: _alldvrm(a, b) [stdcall, clean=16]
void hle_crt_004f0a50(CpuContext& ctx, GuestMemory& mem) {
    const int64_t a = static_cast<int64_t>(mem.r64(ctx.esp + 4u));
    const int64_t b = static_cast<int64_t>(mem.r64(ctx.esp + 12u));
    const int64_t q = (b != 0) ? (a / b) : 0;
    const int64_t r = (b != 0) ? (a % b) : 0;
    ctx.eax = static_cast<uint32_t>(static_cast<uint64_t>(q) & 0xFFFFFFFFu);
    ctx.edx = static_cast<uint32_t>(static_cast<uint64_t>(q) >> 32);
    ctx.ecx = static_cast<uint32_t>(static_cast<uint64_t>(r) & 0xFFFFFFFFu);
    ctx.ebx = static_cast<uint32_t>(static_cast<uint64_t>(r) >> 32);
    ctx.ret_stdcall(mem, 16u);
}

// 0x004f1ece: DirectSoundCreate8 thunk [stdcall, clean=12]
void hle_crt_004f1ece(CpuContext& ctx, GuestMemory& mem) {
    hle_iat_call(ctx, mem, 0x0051B008u);
}

// 0x004f49a0: ov_open_callbacks(datasource, vf, initial, ibytes, cb_read, cb_seek, cb_close, cb_tell) [cdecl]
void hle_crt_004f49a0(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t ds_va    = ctx.arg32(mem, 0);
    const uint32_t vf_va    = ctx.arg32(mem, 1);
    const uint32_t init_va  = ctx.arg32(mem, 2);
    const int32_t  ibytes   = static_cast<int32_t>(ctx.arg32(mem, 3));
    const uint32_t cb_read  = ctx.arg32(mem, 4);
    const uint32_t cb_close = ctx.arg32(mem, 6);

    if (vf_va == 0u || cb_read == 0u) {
        ctx.eax = static_cast<uint32_t>(-131); // OV_EINVAL
        ctx.ret_cdecl(mem);
        return;
    }

    std::vector<uint8_t> raw;
    if (init_va != 0u && ibytes > 0) {
        raw.resize(static_cast<size_t>(ibytes));
        mem.read_bytes(init_va, raw.data(), static_cast<size_t>(ibytes));
    }

    const uint32_t scratch = mem.guest_alloc(16384u, 16u);
    if (scratch != 0u) {
        for (;;) {
            // size_t cb_read(void* ptr, size_t size, size_t nmemb, void* datasource) [cdecl]
            ctx.push32(mem, ds_va);
            ctx.push32(mem, 16384u);
            ctx.push32(mem, 1u);
            ctx.push32(mem, scratch);
            ctx.push32(mem, 0x00FFFFF7u);
            call_indirect(ctx, mem, cb_read);
            ctx.esp += 16u; // clean cdecl args
            const uint32_t n = std::min<uint32_t>(ctx.eax, 16384u);
            if (n == 0u) break;
            const size_t old_sz = raw.size();
            raw.resize(old_sz + n);
            mem.read_bytes(scratch, raw.data() + old_sz, n);
        }
        mem.guest_free(scratch);
    }

    auto st = std::make_shared<VorbisStreamState>();
    st->datasource_va = ds_va;
    st->cb_close_va   = cb_close;
    if (!decode_ogg_vorbis_to_pcm(raw, *st)) {
        ctx.eax = static_cast<uint32_t>(-132); // OV_ENOTVORBIS
        ctx.ret_cdecl(mem);
        return;
    }

    // Allocate guest vorbis_info struct (32 bytes): [0]=version(0), [4]=channels, [8]=rate
    st->info_guest_va = mem.guest_calloc(1u, 32u);
    if (st->info_guest_va != 0u) {
        mem.w32(st->info_guest_va + 0u, 0u);
        mem.w32(st->info_guest_va + 4u, st->channels);
        mem.w32(st->info_guest_va + 8u, st->sample_rate);
    }
    mem.w32(vf_va + 4u, 1u); // seekable flag expected by MBAA.exe

    uint32_t old_info_va = 0u;
    {
        std::lock_guard<std::mutex> lock(g_vorbis_mutex);
        auto prev_it = g_vorbis_streams.find(vf_va);
        if (prev_it != g_vorbis_streams.end() && prev_it->second) {
            old_info_va = prev_it->second->info_guest_va;
        }
        g_vorbis_streams[vf_va] = st;
    }
    if (old_info_va != 0u) {
        mem.guest_free(old_info_va);
    }

    ctx.eax = 0u;
    ctx.ret_cdecl(mem);
}

// 0x004f3170: ov_clear(vf) [cdecl]
void hle_crt_004f3170(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t vf_va = ctx.arg32(mem, 0);
    std::shared_ptr<VorbisStreamState> st;
    {
        std::lock_guard<std::mutex> lock(g_vorbis_mutex);
        auto it = g_vorbis_streams.find(vf_va);
        if (it != g_vorbis_streams.end()) {
            st = it->second;
            g_vorbis_streams.erase(it);
        }
    }
    if (st) {
        if (st->cb_close_va != 0u) {
            ctx.push32(mem, st->datasource_va);
            ctx.push32(mem, 0x00FFFFF8u);
            call_indirect(ctx, mem, st->cb_close_va);
            ctx.esp += 4u;
        }
        if (st->info_guest_va != 0u) {
            mem.guest_free(st->info_guest_va);
        }
    }
    ctx.eax = 0u;
    ctx.ret_cdecl(mem);
}

// 0x004f32f0: ov_time_total(vf, i) [cdecl, returns st(0)]
void hle_crt_004f32f0(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t vf_va = ctx.arg32(mem, 0);
    double dur = -131.0;
    {
        std::lock_guard<std::mutex> lock(g_vorbis_mutex);
        auto it = g_vorbis_streams.find(vf_va);
        if (it != g_vorbis_streams.end() && it->second->valid) {
            dur = it->second->duration_sec;
        }
    }
    ctx.fpu_push(dur);
    ctx.ret_cdecl(mem);
}

// 0x004f41a0: ov_time_seek(vf, double pos) [cdecl]
void hle_crt_004f41a0(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t vf_va = ctx.arg32(mem, 0);
    const double   pos   = mem.rf64(ctx.esp + 8u);
    int32_t rc = -131;
    {
        std::lock_guard<std::mutex> lock(g_vorbis_mutex);
        auto it = g_vorbis_streams.find(vf_va);
        if (it != g_vorbis_streams.end() && it->second->valid) {
            auto& st = *it->second;
            const size_t total_bytes = st.pcm_interleaved.size() * sizeof(int16_t);
            const size_t byte_align = std::max<size_t>(1u, st.channels * sizeof(int16_t));
            const size_t frame = static_cast<size_t>(std::max(0.0, pos) * static_cast<double>(st.sample_rate));
            st.read_cursor_bytes = std::min(frame * byte_align, total_bytes);
            rc = 0;
        }
    }
    ctx.eax = static_cast<uint32_t>(rc);
    ctx.ret_cdecl(mem);
}

// 0x004f4290: ov_info(vf, link) [cdecl]
void hle_crt_004f4290(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t vf_va = ctx.arg32(mem, 0);
    uint32_t info_va = 0u;
    {
        std::lock_guard<std::mutex> lock(g_vorbis_mutex);
        auto it = g_vorbis_streams.find(vf_va);
        if (it != g_vorbis_streams.end() && it->second->valid) {
            info_va = it->second->info_guest_va;
        }
    }
    ctx.eax = info_va;
    ctx.ret_cdecl(mem);
}

// 0x004f4620: ov_read(vf, buffer, length, bigendianp, word, sgned, bitstream) [cdecl]
void hle_crt_004f4620(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t vf_va    = ctx.arg32(mem, 0);
    const uint32_t buf_va   = ctx.arg32(mem, 1);
    const int32_t  length   = static_cast<int32_t>(ctx.arg32(mem, 2));
    const uint32_t bs_va    = ctx.arg32(mem, 6);

    int32_t copied = 0;
    {
        std::lock_guard<std::mutex> lock(g_vorbis_mutex);
        auto it = g_vorbis_streams.find(vf_va);
        if (it == g_vorbis_streams.end() || !it->second->valid) {
            ctx.eax = static_cast<uint32_t>(-131);
            ctx.ret_cdecl(mem);
            return;
        }
        auto& st = *it->second;
        const size_t total_bytes = st.pcm_interleaved.size() * sizeof(int16_t);
        if (st.read_cursor_bytes < total_bytes && length > 0 && buf_va != 0u) {
            const size_t avail = total_bytes - st.read_cursor_bytes;
            const size_t byte_align = std::max<size_t>(1u, st.channels * sizeof(int16_t));
            size_t n = std::min(avail, static_cast<size_t>(length));
            n = (n / byte_align) * byte_align;
            if (n > 0u) {
                mem.write_bytes(
                    buf_va,
                    reinterpret_cast<const uint8_t*>(st.pcm_interleaved.data()) + st.read_cursor_bytes,
                    n);
                st.read_cursor_bytes += n;
                copied = static_cast<int32_t>(n);
            }
        }
    }
    if (bs_va != 0u) mem.w32(bs_va, 0u);
    ctx.eax = static_cast<uint32_t>(copied);
    ctx.ret_cdecl(mem);
}

// 0x004f49f0: _ftol2_sse() [custom_x87]
void hle_crt_004f49f0(CpuContext& ctx, GuestMemory& mem) {
    const double v = ctx.fpu_pop();
    int64_t r = 0;
    if (std::isnan(v) || v >= 9223372036854775808.0 || v < -9223372036854775808.0) {
        r = static_cast<int64_t>(0x8000000000000000ull);
    } else {
        r = static_cast<int64_t>(v);
    }
    ctx.eax = static_cast<uint32_t>(static_cast<uint64_t>(r) & 0xFFFFFFFFu);
    ctx.edx = static_cast<uint32_t>(static_cast<uint64_t>(r) >> 32);
    ctx.ret_cdecl(mem);
}

// 0x004f4a26: _ftol2() [custom_x87]
void hle_crt_004f4a26(CpuContext& ctx, GuestMemory& mem) {
    hle_crt_004f49f0(ctx, mem);
}

// 0x0050e1d0: _CIatan() [custom_x87]
void hle_crt_0050e1d0(CpuContext& ctx, GuestMemory& mem) {
    ctx.fpu_st(0) = std::atan(ctx.fpu_st(0));
    ctx.ret_cdecl(mem);
}

// 0x0050e2b0: _CIsqrt() [custom_x87]
void hle_crt_0050e2b0(CpuContext& ctx, GuestMemory& mem) {
    ctx.fpu_st(0) = std::sqrt(ctx.fpu_st(0));
    ctx.ret_cdecl(mem);
}

// 0x0050e8d0: _CIpow() [custom_x87: pops exponent st(0), replaces new st(0) with pow(base, exp)]
void hle_crt_0050e8d0(CpuContext& ctx, GuestMemory& mem) {
    const double exp_v = ctx.fpu_pop();
    ctx.fpu_st(0) = std::pow(ctx.fpu_st(0), exp_v);
    ctx.ret_cdecl(mem);
}

// 0x0050eb60: _CIsin() [custom_x87]
void hle_crt_0050eb60(CpuContext& ctx, GuestMemory& mem) {
    ctx.fpu_st(0) = std::sin(ctx.fpu_st(0));
    ctx.ret_cdecl(mem);
}

// 0x0050ec90: _CIcos() [custom_x87]
void hle_crt_0050ec90(CpuContext& ctx, GuestMemory& mem) {
    ctx.fpu_st(0) = std::cos(ctx.fpu_st(0));
    ctx.ret_cdecl(mem);
}

// 0x0050edc0: _CIacos() [custom_x87]
void hle_crt_0050edc0(CpuContext& ctx, GuestMemory& mem) {
    ctx.fpu_st(0) = std::acos(ctx.fpu_st(0));
    ctx.ret_cdecl(mem);
}

// 0x00513030: _CItan() [custom_x87]
void hle_crt_00513030(CpuContext& ctx, GuestMemory& mem) {
    ctx.fpu_st(0) = std::tan(ctx.fpu_st(0));
    ctx.ret_cdecl(mem);
}

// ---------------------------------------------------------------------------
// Dynamic CRT VA dispatcher
// ---------------------------------------------------------------------------
void hle_crt_dispatch(CpuContext& ctx, GuestMemory& mem, uint32_t va) {
    switch (va) {
        case 0x004E00D0u: hle_crt_004e00d0(ctx, mem); return;
        case 0x004E0177u: hle_crt_004e0177(ctx, mem); return;
        case 0x004E0230u: hle_crt_004e0230(ctx, mem); return;
        case 0x004E02F3u: hle_crt_004e02f3(ctx, mem); return;
        case 0x004E02F8u: hle_crt_004e02f8(ctx, mem); return;
        case 0x004E0307u: hle_crt_004e0307(ctx, mem); return;
        case 0x004E0675u: hle_crt_004e0675(ctx, mem); return;
        case 0x004E0680u: hle_crt_004e0680(ctx, mem); return;
        case 0x004E068Bu: hle_crt_004e068b(ctx, mem); return;
        case 0x004E0706u: hle_crt_004e0706(ctx, mem); return;
        case 0x004E07C4u: hle_crt_004e07c4(ctx, mem); return;
        case 0x004E07D5u: hle_crt_004e07d5(ctx, mem); return;
        case 0x004E083Bu: hle_crt_004e083b(ctx, mem); return;
        case 0x004E0893u: hle_crt_004e0893(ctx, mem); return;
        case 0x004E0917u: hle_crt_004e0917(ctx, mem); return;
        case 0x004E0AB6u: hle_crt_004e0ab6(ctx, mem); return;
        case 0x004E0BF2u: hle_crt_004e0bf2(ctx, mem); return;
        case 0x004E0C02u: hle_crt_004e0c02(ctx, mem); return;
        case 0x004E0CC5u: hle_crt_004e0cc5(ctx, mem); return;
        case 0x004E0CF0u: hle_crt_004e0cf0(ctx, mem); return;
        case 0x004E0E20u: hle_crt_004e0e20(ctx, mem); return;
        case 0x004E0EB7u: hle_crt_004e0eb7(ctx, mem); return;
        case 0x004E0FE7u: hle_crt_004e0fe7(ctx, mem); return;
        case 0x004E10AAu: hle_crt_004e10aa(ctx, mem); return;
        case 0x004E1340u: hle_crt_004e1340(ctx, mem); return;
        case 0x004E13CCu: hle_crt_004e13cc(ctx, mem); return;
        case 0x004E1660u: hle_crt_004e1660(ctx, mem); return;
        case 0x004E18D3u: hle_crt_004e18d3(ctx, mem); return;
        case 0x004E1900u: hle_crt_004e1900(ctx, mem); return;
        case 0x004E1A12u: hle_crt_004e1a12(ctx, mem); return;
        case 0x004E1A8Cu: hle_crt_004e1a8c(ctx, mem); return;
        case 0x004E1B09u: hle_crt_004e1b09(ctx, mem); return;
        case 0x004E1C34u: hle_crt_004e1c34(ctx, mem); return;
        case 0x004E1C97u: hle_crt_004e1c97(ctx, mem); return;
        case 0x004E1CFCu: hle_crt_004e1cfc(ctx, mem); return;
        case 0x004E1D40u: hle_crt_004e1d40(ctx, mem); return;
        case 0x004E1DEDu: hle_crt_004e1ded(ctx, mem); return;
        case 0x004E1E2Eu: hle_crt_004e1e2e(ctx, mem); return;
        case 0x004E1F28u: hle_crt_004e1f28(ctx, mem); return;
        case 0x004E20DEu: hle_crt_004e20de(ctx, mem); return;
        case 0x004E21DFu: hle_crt_004e21df(ctx, mem); return;
        case 0x004E2CA0u: hle_crt_004e2ca0(ctx, mem); return;
        case 0x004E2CBDu: hle_crt_004e2cbd(ctx, mem); return;
        case 0x004E2D59u: hle_crt_004e2d59(ctx, mem); return;
        case 0x004E309Au: hle_crt_004e309a(ctx, mem); return;
        case 0x004E30BEu: hle_crt_004e30be(ctx, mem); return;
        case 0x004E325Bu: hle_crt_004e325b(ctx, mem); return;
        case 0x004E3333u: hle_crt_004e3333(ctx, mem); return;
        case 0x004E334Au: hle_crt_004e334a(ctx, mem); return;
        case 0x004E34E2u: hle_crt_004e34e2(ctx, mem); return;
        case 0x004E3B12u: hle_crt_004e3b12(ctx, mem); return;
        case 0x004E3E1Bu: hle_crt_004e3e1b(ctx, mem); return;
        case 0x004E422Cu: hle_crt_004e422c(ctx, mem); return;
        case 0x004E6340u: hle_crt_004e6340(ctx, mem); return;
        case 0x004E63C0u: hle_crt_004e63c0(ctx, mem); return;
        case 0x004EAE60u: hle_crt_004eae60(ctx, mem); return;
        case 0x004EAF10u: hle_crt_004eaf10(ctx, mem); return;
        case 0x004EDBA0u: hle_crt_004edba0(ctx, mem); return;
        case 0x004EFAB0u: hle_crt_004efab0(ctx, mem); return;
        case 0x004F0A50u: hle_crt_004f0a50(ctx, mem); return;
        case 0x004F1ECEu: hle_crt_004f1ece(ctx, mem); return;
        case 0x004F3170u: hle_crt_004f3170(ctx, mem); return;
        case 0x004F32F0u: hle_crt_004f32f0(ctx, mem); return;
        case 0x004F41A0u: hle_crt_004f41a0(ctx, mem); return;
        case 0x004F4290u: hle_crt_004f4290(ctx, mem); return;
        case 0x004F4620u: hle_crt_004f4620(ctx, mem); return;
        case 0x004F49A0u: hle_crt_004f49a0(ctx, mem); return;
        case 0x004F49F0u: hle_crt_004f49f0(ctx, mem); return;
        case 0x004F4A26u: hle_crt_004f4a26(ctx, mem); return;
        case 0x0050E1D0u: hle_crt_0050e1d0(ctx, mem); return;
        case 0x0050E2B0u: hle_crt_0050e2b0(ctx, mem); return;
        case 0x0050E8D0u: hle_crt_0050e8d0(ctx, mem); return;
        case 0x0050EB60u: hle_crt_0050eb60(ctx, mem); return;
        case 0x0050EC90u: hle_crt_0050ec90(ctx, mem); return;
        case 0x0050EDC0u: hle_crt_0050edc0(ctx, mem); return;
        case 0x00513030u: hle_crt_00513030(ctx, mem); return;
        default:
            std::fprintf(stderr, "[hle_crt] Unhandled CRT VA 0x%08x\n", va);
            ctx.eax = 0u;
            ctx.ret_cdecl(mem);
            return;
    }
}

} // namespace mbaa_recomp
