#include "mbaa_recomp/netplay_rollback.h"

#include <algorithm>
#include <cstring>

namespace mbaa_recomp {

namespace {

constexpr std::array<NetplayRollbackRegion, FullRollbackSnapshot::kStaticRegionCount>
build_full_rollback_regions() noexcept {
    constexpr std::pair<uint32_t, uint32_t> kSpecs[FullRollbackSnapshot::kStaticRegionCount] = {
        // [0..36]: Top-level combat, player, camera, RNG, particle, and actor pools
        {0x0054EB70u, 12u},
        {0x00555124u, 8u},
        {0x00555130u, 11248u},
        {0x00557D2Bu, 1u},
        {0x00557DACu, 2u},
        {0x00557DB0u, 1056u},
        {0x005585E8u, 12u},
        {0x00558608u, 3900u},
        {0x00559546u, 14u},
        {0x00559580u, 4u},
        {0x005595B4u, 4u},
        {0x0055D1D4u, 4u},
        {0x0055D204u, 6u},
        {0x0055D20Bu, 1u},
        {0x0055DEC4u, 12u},
        {0x0055DEDCu, 16u},
        {0x00562A3Cu, 8u},
        {0x00562A48u, 4u},
        {0x00562A6Cu, 2u},
        {0x00562A6Fu, 1u},
        {0x0056357Cu, 100u},
        {0x005635F4u, 96u},
        {0x00563750u, 4u},
        {0x00563778u, 8u},
        {0x00563864u, 4u},
        {0x00564068u, 4u},
        {0x00564070u, 224u},
        {0x005641A4u, 4u},
        {0x00564200u, 4u},
        {0x00564AF8u, 4u},
        {0x00564B00u, 2u},
        {0x00564B0Cu, 6u},
        {0x00564B14u, 12u},
        {0x00564B24u, 4u},
        {0x0061E170u, 384000u},
        {0x0067BD78u, 4u},
        {0x0067BDE8u, 828000u},
        // [37..60]: Exact 24 tail regions (252 bytes) matching rollback_hooks.cpp
        {0x0074D598u, 4u},
        {0x0074D99Cu, 4u},
        {0x0074D9D0u, 4u},
        {0x0074E4E4u, 8u},
        {0x0074E5B0u, 4u},
        {0x0074E768u, 4u},
        {0x0074E770u, 20u},
        {0x0074E78Cu, 12u},
        {0x0074E79Cu, 12u},
        {0x0074E7ACu, 20u},
        {0x0074E7C8u, 16u},
        {0x0074E7DCu, 4u},
        {0x0074E7E4u, 16u},
        {0x0074E7F8u, 16u},
        {0x0074E80Cu, 4u},
        {0x0074E814u, 20u},
        {0x0074E82Cu, 8u},
        {0x0074E838u, 20u},
        {0x0074E850u, 8u},
        {0x0074E85Cu, 16u},
        {0x0076E6F4u, 12u},
        {0x0076E780u, 12u},
        {0x007717D8u, 4u},
        {0x007B1D2Cu, 4u},
    };

    std::array<NetplayRollbackRegion, FullRollbackSnapshot::kStaticRegionCount> out{};
    uint32_t offset = 0u;
    for (size_t i = 0; i < FullRollbackSnapshot::kStaticRegionCount; ++i) {
        out[i] = NetplayRollbackRegion{kSpecs[i].first, kSpecs[i].second, offset};
        offset += kSpecs[i].second;
    }
    return out;
}

constexpr auto kFullRollbackRegions = build_full_rollback_regions();

static_assert(
    kFullRollbackRegions[60].snapshot_offset + kFullRollbackRegions[60].byte_size ==
        FullRollbackSnapshot::kStaticStateBytes,
    "61 static rollback regions must sum to exactly 1,229,047 bytes");

static_assert(
    FullRollbackSnapshot::kTotalTreeBytes == 0x0012EFD7u,
    "Total static + dynamic child rollback tree must equal 1,241,047 bytes (0x0012EFD7)");

constexpr uint32_t kCombatActiveFlagVa = 0x0054EEE8u;
constexpr uint32_t kHitstopFreezeVa    = 0x0055D20Bu;
constexpr uint32_t kContainerQueueVa   = 0x0077BF9Cu;

inline uint32_t rotl32(uint32_t x, uint32_t n) noexcept {
    return (x << n) | (x >> (32u - n));
}

inline void write_le32(uint8_t* dst, uint32_t v) noexcept {
    dst[0] = static_cast<uint8_t>(v & 0xFFu);
    dst[1] = static_cast<uint8_t>((v >> 8) & 0xFFu);
    dst[2] = static_cast<uint8_t>((v >> 16) & 0xFFu);
    dst[3] = static_cast<uint8_t>((v >> 24) & 0xFFu);
}

inline void write_le16(uint8_t* dst, uint16_t v) noexcept {
    dst[0] = static_cast<uint8_t>(v & 0xFFu);
    dst[1] = static_cast<uint8_t>((v >> 8) & 0xFFu);
}

inline uint32_t read_le32(const uint8_t* src) noexcept {
    return static_cast<uint32_t>(src[0]) |
           (static_cast<uint32_t>(src[1]) << 8) |
           (static_cast<uint32_t>(src[2]) << 16) |
           (static_cast<uint32_t>(src[3]) << 24);
}

void md5_transform(uint32_t state[4], const uint8_t block[64]) noexcept {
    static constexpr uint32_t kS[64] = {
        7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
        5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
        4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
        6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,
    };
    static constexpr uint32_t kK[64] = {
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
        0xf7537e82u, 0xbd3af235u, 0x2ad7d2bbu, 0xeb86d391u,
    };

    uint32_t m[16];
    for (uint32_t i = 0; i < 16u; ++i) {
        m[i] = read_le32(block + i * 4u);
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
            g = (5u * i + 1u) % 16u;
        } else if (i < 48u) {
            f = b ^ c ^ d;
            g = (3u * i + 5u) % 16u;
        } else {
            f = c ^ (b | (~d));
            g = (7u * i) % 16u;
        }

        const uint32_t tmp = d;
        d = c;
        c = b;
        b = b + rotl32(a + f + kK[i] + m[g], kS[i]);
        a = tmp;
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}

void fill_player_sync_slice(
    const GuestMemory& mem,
    uint32_t player_idx,
    bool freeze_active,
    std::array<uint8_t, 44>& out) noexcept {
    const uint32_t p_off = player_idx * static_cast<uint32_t>(SyncHashData::kP1Stride);
    const uint32_t c_off = player_idx * 0x24u; // 0x0074d8fc (P1) -> 0x0074d920 (P2)

    write_le32(out.data() + 0u,  mem.r32(0x00555140u + p_off));
    write_le32(out.data() + 4u,  mem.r32(0x00555144u + p_off));
    write_le32(out.data() + 8u,  mem.r32(0x005551ECu + p_off));
    write_le32(out.data() + 12u, mem.r32(0x005551F0u + p_off));
    write_le32(out.data() + 16u, mem.r32(0x00555210u + p_off));
    write_le32(out.data() + 20u, mem.r32(0x00555214u + p_off));
    write_le32(out.data() + 24u, freeze_active ? 0u : mem.r32(0x005551F4u + p_off));
    write_le32(out.data() + 28u, mem.r32(0x00555208u + p_off));
    write_le32(out.data() + 32u, mem.r32(0x00555238u + p_off));
    write_le32(out.data() + 36u, mem.r32(0x0055523Cu + p_off));
    write_le16(out.data() + 40u, static_cast<uint16_t>(mem.r32(0x0074D8FCu + c_off) & 0xFFFFu));
    write_le16(out.data() + 42u, static_cast<uint16_t>(mem.r32(0x0074D900u + c_off) & 0xFFFFu));
}

} // namespace

bool SyncHashData::matches_gameplay(const SyncHashData& other) const noexcept {
    return rng_md5 == other.rng_md5 &&
           globals == other.globals &&
           p1_slice == other.p1_slice &&
           p2_slice == other.p2_slice;
}

const std::array<NetplayRollbackRegion, FullRollbackSnapshot::kStaticRegionCount>&
get_full_rollback_regions() noexcept {
    return kFullRollbackRegions;
}

void compute_md5(const uint8_t* data, size_t len, uint8_t out_digest[16]) noexcept {
    uint32_t state[4] = {
        0x67452301u, 0xefcdab89u, 0x98badcfeu, 0x10325476u,
    };

    size_t offset = 0u;
    while (offset + 64u <= len) {
        md5_transform(state, data + offset);
        offset += 64u;
    }

    uint8_t tail[128] = {};
    const size_t rem = len - offset;
    if (rem > 0u && data != nullptr) {
        std::memcpy(tail, data + offset, rem);
    }
    tail[rem] = 0x80u;

    const size_t pad_blocks = (rem < 56u) ? 64u : 128u;
    const uint64_t bit_len = static_cast<uint64_t>(len) * 8ull;
    write_le32(tail + pad_blocks - 8u, static_cast<uint32_t>(bit_len & 0xFFFFFFFFull));
    write_le32(tail + pad_blocks - 4u, static_cast<uint32_t>(bit_len >> 32));

    md5_transform(state, tail);
    if (pad_blocks == 128u) {
        md5_transform(state, tail + 64u);
    }

    for (uint32_t i = 0; i < 4u; ++i) {
        write_le32(out_digest + i * 4u, state[i]);
    }
}

bool capture_rng_state(const GuestMemory& mem, RngStateBlock& out) noexcept {
    if (!mem.in_bounds(0x00563778u, 8u) ||
        !mem.in_bounds(0x00564068u, 4u) ||
        !mem.in_bounds(0x00564070u, 220u)) {
        return false;
    }
    if (!mem.read_bytes(0x00563778u, out.bytes.data() + 0u, 4u) ||
        !mem.read_bytes(0x0056377Cu, out.bytes.data() + 4u, 4u) ||
        !mem.read_bytes(0x00564068u, out.bytes.data() + 8u, 4u) ||
        !mem.read_bytes(0x00564070u, out.bytes.data() + 12u, 220u)) {
        return false;
    }
    return true;
}

bool apply_rng_state(GuestMemory& mem, const RngStateBlock& in) noexcept {
    if (!mem.in_bounds(0x00563778u, 8u) ||
        !mem.in_bounds(0x00564068u, 4u) ||
        !mem.in_bounds(0x00564070u, 220u)) {
        return false;
    }
    return mem.write_bytes(0x00563778u, in.bytes.data() + 0u, 4u) &&
           mem.write_bytes(0x0056377Cu, in.bytes.data() + 4u, 4u) &&
           mem.write_bytes(0x00564068u, in.bytes.data() + 8u, 4u) &&
           mem.write_bytes(0x00564070u, in.bytes.data() + 12u, 220u);
}

bool build_sync_hash(const GuestMemory& mem, uint32_t indexed_frame, uint32_t flags, SyncHashData& out) noexcept {
    out = SyncHashData{};
    out.indexed_frame = indexed_frame;
    out.flags = flags;

    RngStateBlock rng{};
    if (!capture_rng_state(mem, rng)) {
        return false;
    }
    compute_md5(rng.bytes.data(), rng.bytes.size(), out.rng_md5.data());

    // SyncHash (`0x663974f8..0x66397697`) always writes P1/P2 uint16 char/moon slots
    // ([40..43]) even when [0x0054eee8] != 1, keeping [0..39] and globals zeroed out of combat.
    if (mem.in_bounds(kCombatActiveFlagVa, 4u) && mem.r32(kCombatActiveFlagVa) == 1u) {
        out.globals[0] = mem.r32(0x00562A3Cu);
        out.globals[1] = mem.r32(0x00562A40u);
        out.globals[2] = mem.r32(0x00564B14u);
        out.globals[3] = mem.r32(0x00564B18u);

        const bool freeze_active = mem.r8(kHitstopFreezeVa) != 0u;
        fill_player_sync_slice(mem, 0u, freeze_active, out.p1_slice);
        fill_player_sync_slice(mem, 1u, freeze_active, out.p2_slice);
    } else {
        write_le16(out.p1_slice.data() + 40u, static_cast<uint16_t>(mem.r32(0x0074D8FCu) & 0xFFFFu));
        write_le16(out.p1_slice.data() + 42u, static_cast<uint16_t>(mem.r32(0x0074D900u) & 0xFFFFu));
        write_le16(out.p2_slice.data() + 40u, static_cast<uint16_t>(mem.r32(0x0074D920u) & 0xFFFFu));
        write_le16(out.p2_slice.data() + 42u, static_cast<uint16_t>(mem.r32(0x0074D924u) & 0xFFFFu));
    }
    return true;
}

void cleanup_transient_containers(GuestMemory& mem, uint32_t rollback_frames) noexcept {
    if (rollback_frames == 0u) {
        return;
    }
    const uint32_t capped_steps = std::min<uint32_t>(rollback_frames, 32u);
    if (!mem.in_bounds(kContainerQueueVa, 4u)) {
        return;
    }

    for (uint32_t step = 0; step < capped_steps; ++step) {
        const uint32_t obj = mem.r32(kContainerQueueVa);
        if (obj < 0x20u || !mem.in_bounds(obj - 0x20u, 4u)) {
            break;
        }
        const uint32_t hdr = mem.r32(obj - 0x20u);
        if (hdr == 0u || !mem.in_bounds(hdr, 0x80u)) {
            break;
        }

        // Exact 4 container slots at +0x00/+0x20/+0x40/+0x60 inside *(obj - 0x20)
        // mirroring hook.dll 0x663aa000..0x663aa2ef.
        for (uint32_t slot = 0u; slot < 4u; ++slot) {
            const uint32_t slot_off = slot * 0x20u;
            const uint32_t base_va  = mem.r32(hdr + 0x04u + slot_off);
            if (base_va == 0u) {
                continue;
            }
            const uint32_t byte_len = mem.r32(hdr + 0x08u + slot_off);
            const uint32_t count    = mem.r32(hdr + 0x18u + slot_off);
            const uint64_t elem_va64 = static_cast<uint64_t>(base_va) + static_cast<uint64_t>(count) * 8ull;
            if (elem_va64 + 8ull > GuestMemory::kArenaSize) {
                continue;
            }
            const uint32_t elem_va = static_cast<uint32_t>(elem_va64);
            const uint8_t ttl = mem.r8(elem_va + 1u);
            if (ttl == 0u) {
                continue;
            }
            if (ttl == 1u) {
                mem.w32(elem_va + 0u, 0u);
                mem.w32(elem_va + 4u, 0u);
                if (byte_len >= 8u) {
                    mem.w32(hdr + 0x08u + slot_off, byte_len - 8u);
                }
                if (count >= 1u) {
                    mem.w32(hdr + 0x18u + slot_off, count - 1u);
                }
            } else {
                mem.w8(elem_va + 1u, static_cast<uint8_t>(ttl - 1u));
            }
        }
    }
}

NetplayRollbackEngine::~NetplayRollbackEngine() {
    release_session();
}

bool NetplayRollbackEngine::allocate_session(size_t max_rollback_frames) {
    set_max_rollback_frames(max_rollback_frames);
    if (ring_.size() == kMaxRingFrames) {
        reset_match_state();
        return true;
    }

    ring_.clear();
    ring_.resize(kMaxRingFrames);
    for (auto& snap : ring_) {
        snap.frame = 0u;
        snap.valid = false;
        snap.static_data.assign(FullRollbackSnapshot::kStaticStateBytes, 0u);
        snap.child_ptrs.fill(0u);
        snap.sfx_triggers.fill(0u);
    }
    sfx_already_played_.fill(0u);
    sfx_resim_accum_.fill(0u);
    return true;
}

void NetplayRollbackEngine::release_session() noexcept {
    for (auto& snap : ring_) {
        snap.static_data.clear();
        snap.static_data.shrink_to_fit();
        snap.child_ptrs.fill(0u);
        snap.sfx_triggers.fill(0u);
        snap.valid = false;
        snap.frame = 0u;
    }
    ring_.clear();
    ring_.shrink_to_fit();
    sfx_already_played_.fill(0u);
    sfx_resim_accum_.fill(0u);
}

size_t NetplayRollbackEngine::allocated_bytes() const noexcept {
    size_t total = ring_.capacity() * sizeof(FullRollbackSnapshot);
    for (const auto& snap : ring_) {
        total += snap.static_data.capacity();
    }
    return total;
}

void NetplayRollbackEngine::set_max_rollback_frames(size_t frames) noexcept {
    max_rollback_frames_ = std::min<size_t>(frames, 15u);
}

void NetplayRollbackEngine::reset_match_state() noexcept {
    for (auto& snap : ring_) {
        snap.valid = false;
        snap.frame = 0u;
        snap.sfx_triggers.fill(0u);
    }
    sfx_already_played_.fill(0u);
    sfx_resim_accum_.fill(0u);
}

bool NetplayRollbackEngine::save_frame(const GuestMemory& mem, uint32_t frame) noexcept {
    if (ring_.empty()) {
        return false;
    }
    auto& snap = ring_[frame % kMaxRingFrames];
    if (snap.static_data.size() != FullRollbackSnapshot::kStaticStateBytes) {
        return false;
    }

    for (const auto& reg : kFullRollbackRegions) {
        if (!mem.read_bytes(reg.mbaa_data_va, snap.static_data.data() + reg.snapshot_offset, reg.byte_size)) {
            return false;
        }
    }

    snap.child_ptrs.fill(0u);
    for (uint32_t i = 0u; i < FullRollbackSnapshot::kDynamicSlotCount; ++i) {
        const uint32_t slot_va = kDynamicBaseVa + i * static_cast<uint32_t>(FullRollbackSnapshot::kDynamicSlotStride);
        const uint32_t ptr1 = mem.r32(slot_va + 0x320u);
        if (ptr1 == 0u) {
            continue;
        }
        const uint32_t addr1 = ptr1 + 0x38u;
        if (addr1 < ptr1 || !mem.in_bounds(addr1, 4u)) {
            continue;
        }
        const uint32_t val1 = mem.r32(addr1);
        snap.child_ptrs[i * 3u + 0u] = val1;
        if (val1 == 0u || !mem.in_bounds(val1, 4u)) {
            continue;
        }
        const uint32_t val2 = mem.r32(val1);
        snap.child_ptrs[i * 3u + 1u] = val2;
        if (val2 == 0u || !mem.in_bounds(val2, 4u)) {
            continue;
        }
        const uint32_t val3 = mem.r32(val2);
        snap.child_ptrs[i * 3u + 2u] = val3;
    }

    snap.sfx_triggers.fill(0u);
    snap.frame = frame;
    snap.valid = true;
    return true;
}

void NetplayRollbackEngine::record_live_frame_sfx(const GuestMemory& mem, uint32_t frame) noexcept {
    if (ring_.empty()) {
        return;
    }
    auto& snap = ring_[frame % kMaxRingFrames];
    if (!snap.valid || snap.frame != frame) {
        return;
    }
    if (mem.in_bounds(kSfxPlayedCacheVa, FullRollbackSnapshot::kSfxArrayBytes)) {
        mem.read_bytes(kSfxPlayedCacheVa, snap.sfx_triggers.data(), FullRollbackSnapshot::kSfxArrayBytes);
    }
}

bool NetplayRollbackEngine::rollback_to_frame(
    GuestMemory& mem, uint32_t target_frame, uint32_t current_frame) noexcept {
    if (ring_.empty() || current_frame < target_frame) {
        return false;
    }
    const auto& snap = ring_[target_frame % kMaxRingFrames];
    if (!snap.valid || snap.frame != target_frame ||
        snap.static_data.size() != FullRollbackSnapshot::kStaticStateBytes) {
        return false;
    }

    // Seed SFX already-played filter across discarded frames [target_frame .. current_frame]
    sfx_already_played_.fill(0u);
    sfx_resim_accum_.fill(0u);
    for (uint32_t f = target_frame; f <= current_frame; ++f) {
        const auto& old_snap = ring_[f % kMaxRingFrames];
        if (old_snap.valid && old_snap.frame == f) {
            for (size_t i = 0; i < FullRollbackSnapshot::kSfxArrayBytes; ++i) {
                if (old_snap.sfx_triggers[i] != 0u) {
                    sfx_already_played_[i] = 1u;
                }
            }
        }
    }

    // Restore all 61 static regions first (includes 0x0067bde8 actor array)
    for (const auto& reg : kFullRollbackRegions) {
        if (!mem.write_bytes(reg.mbaa_data_va, snap.static_data.data() + reg.snapshot_offset, reg.byte_size)) {
            return false;
        }
    }

    // Restore 1,000x3 dynamic child pointers under 0x0067bde8 + 0x320 -> +0x38
    for (uint32_t i = 0u; i < FullRollbackSnapshot::kDynamicSlotCount; ++i) {
        const uint32_t slot_va = kDynamicBaseVa + i * static_cast<uint32_t>(FullRollbackSnapshot::kDynamicSlotStride);
        const uint32_t ptr1 = mem.r32(slot_va + 0x320u);
        if (ptr1 == 0u) {
            continue;
        }
        const uint32_t addr1 = ptr1 + 0x38u;
        if (addr1 < ptr1 || !mem.in_bounds(addr1, 4u)) {
            continue;
        }
        mem.w32(addr1, snap.child_ptrs[i * 3u + 0u]);
        const uint32_t addr2 = mem.r32(addr1);
        if (addr2 == 0u || !mem.in_bounds(addr2, 4u)) {
            continue;
        }
        mem.w32(addr2, snap.child_ptrs[i * 3u + 1u]);
        const uint32_t addr3 = mem.r32(addr2);
        if (addr3 == 0u || !mem.in_bounds(addr3, 4u)) {
            continue;
        }
        mem.w32(addr3, snap.child_ptrs[i * 3u + 2u]);
    }

    cleanup_transient_containers(mem, current_frame - target_frame);
    return true;
}

void NetplayRollbackEngine::capture_resim_sfx(const GuestMemory& mem) noexcept {
    if (!mem.in_bounds(kSfxPlayedCacheVa, FullRollbackSnapshot::kSfxArrayBytes) ||
        !mem.in_bounds(kSfxTriggerQueueVa, FullRollbackSnapshot::kSfxArrayBytes)) {
        return;
    }
    const uint8_t* played = mem.cptr(kSfxPlayedCacheVa);
    const uint8_t* queued = mem.cptr(kSfxTriggerQueueVa);
    if (!played || !queued) {
        return;
    }
    for (size_t i = 0; i < FullRollbackSnapshot::kSfxArrayBytes; ++i) {
        if ((played[i] | queued[i]) != 0u) {
            sfx_resim_accum_[i] = 0x80u;
        }
    }
}

void NetplayRollbackEngine::commit_resim_sfx(GuestMemory& mem) noexcept {
    if (!mem.in_bounds(kSfxTriggerQueueVa, FullRollbackSnapshot::kSfxArrayBytes)) {
        return;
    }
    for (size_t i = 0; i < FullRollbackSnapshot::kSfxArrayBytes; ++i) {
        if (sfx_resim_accum_[i] == 0x80u && sfx_already_played_[i] == 0u) {
            mem.w8(kSfxTriggerQueueVa + static_cast<uint32_t>(i), 1u);
        }
    }
    sfx_resim_accum_.fill(0u);
    sfx_already_played_.fill(0u);
}

} // namespace mbaa_recomp
