#include "mbaa_recomp/rollback_hooks.h"

#include <cstring>

namespace mbaa_recomp {

namespace {

// Exact 24 deterministic .data state regions verified in mbaacc-src/evidence/companion_binaries.json
// (hook_dll.rollback_state_ranges, total = 252 bytes).
constexpr std::array<RollbackRegion, RollbackStateSnapshot::kRegionCount> kRollbackRegions = {{
    {0x0074D598u,  4u,   0u},
    {0x0074D99Cu,  4u,   4u},
    {0x0074D9D0u,  4u,   8u},
    {0x0074E4E4u,  8u,  12u},
    {0x0074E5B0u,  4u,  20u},
    {0x0074E768u,  4u,  24u},
    {0x0074E770u, 20u,  28u},
    {0x0074E78Cu, 12u,  48u},
    {0x0074E79Cu, 12u,  60u},
    {0x0074E7ACu, 20u,  72u},
    {0x0074E7C8u, 16u,  92u},
    {0x0074E7DCu,  4u, 108u},
    {0x0074E7E4u, 16u, 112u},
    {0x0074E7F8u, 16u, 128u},
    {0x0074E80Cu,  4u, 144u},
    {0x0074E814u, 20u, 148u},
    {0x0074E82Cu,  8u, 168u},
    {0x0074E838u, 20u, 176u},
    {0x0074E850u,  8u, 196u},
    {0x0074E85Cu, 16u, 204u},
    {0x0076E6F4u, 12u, 220u},
    {0x0076E780u, 12u, 232u},
    {0x007717D8u,  4u, 244u}, // Battle frame / tick counter
    {0x007B1D2Cu,  4u, 248u},
}};

static_assert(kRollbackRegions[23].snapshot_offset + kRollbackRegions[23].byte_size ==
              RollbackStateSnapshot::kTotalStateBytes,
              "24 rollback regions must total exactly 252 bytes");

// Exact CCCaster v3.1 (hook.dll PatchGroup 0x6673cce0) stage unlock .data/.bss layout.
constexpr uint32_t kStageUnlockSentinel       = 0x000000FFu;
constexpr uint32_t kStageIdExcludedDummy      = 0x00000063u; // Stage 99 (preserved)
constexpr uint32_t kStageListTerminator       = 0xFFFFFFFFu; // -1 sentinel (preserved)

// Training-mode disabled stage list (sub_00488760 when [0x00562A74] == 0x1010, and sub_004b49d0).
// Vanilla: [55, 57, 58, 99, -1]. Unlocks 55 (...and nothing heart) and 57/58 (G TABLE).
constexpr uint32_t kTrainingBlacklistBaseVa   = 0x0054CEBCu;
constexpr uint32_t kTrainingBlacklistPatchCnt = 3u;
constexpr uint32_t kTrainingBlacklistDummyVa  = 0x0054CEC8u;
constexpr uint32_t kTrainingBlacklistTermVa   = 0x0054CECCu;

// Versus/Normal/Random disabled stage list (sub_00488760, sub_004b4a10, sub_00428d20, sub_0042f140,
// sub_00490ef0). Vanilla: [3, 4, 18, 20, 21, 23, 31, 32, 43, 44, 47, 49, 50, 51, 52, 54, 55, 57, 58, 99, -1].
constexpr uint32_t kVersusBlacklistBaseVa     = 0x0054CF68u;
constexpr uint32_t kVersusBlacklistPatchCnt   = 19u;
constexpr uint32_t kVersusBlacklistDummyVa    = 0x0054CFB4u;
constexpr uint32_t kVersusBlacklistTermVa     = 0x0054CFB8u;

// BGM table entry 55 (base 0x00768B90 + 55 * 0x30 = 0x007695E0), populated from .\bgm\bgm.txt
// by sub_004dd5d0. Vanilla bgm.txt assigns "bgmme56\0" (19.125s loop) even though bgmme55.ogg exists in 0001.p.
constexpr uint32_t kBgm55EntryBaseVa          = 0x007695E0u; // valid flag dword
constexpr uint32_t kBgm55LoopPosHiVa          = 0x007695ECu; // upper 32 bits of IEEE-754 double at 0x007695E8
constexpr uint32_t kBgm55FilenameVa           = 0x007695F0u; // char[32] filename without extension
constexpr uint32_t kBgm55FilenamePatchVa      = 0x007695F6u; // byte +6 ('6' -> '5') + trailing NULs
constexpr uint32_t kBgm55PrefixBgmm           = 0x6D6D6762u; // "bgmm" little-endian
constexpr uint32_t kBgm55SuffixE56            = 0x00363565u; // "e56\0" little-endian
constexpr uint32_t kBgm55PatchedTail          = 0x00000035u; // "5\0\0\0" little-endian
constexpr uint32_t kBgm55LoopPosHiPatched     = 0x401ECCAAu; // ~7.70s loop point (CCCaster exact value)

} // namespace

const std::array<RollbackRegion, RollbackStateSnapshot::kRegionCount>&
get_rollback_regions() noexcept {
    return kRollbackRegions;
}

uint32_t compute_snapshot_checksum(const uint8_t* bytes, size_t len) noexcept {
    uint32_t hash = 2166136261u;
    for (size_t i = 0; i < len; ++i) {
        hash ^= static_cast<uint32_t>(bytes[i]);
        hash *= 16777619u;
    }
    return hash;
}

uint32_t apply_cccaster_stage_unlocks(GuestMemory& mem) noexcept {
    uint32_t patched = 0u;

    if (mem.in_bounds(kTrainingBlacklistBaseVa, (kTrainingBlacklistPatchCnt + 2u) * 4u) &&
        mem.r32(kTrainingBlacklistDummyVa) == kStageIdExcludedDummy &&
        mem.r32(kTrainingBlacklistTermVa) == kStageListTerminator) {
        for (uint32_t i = 0u; i < kTrainingBlacklistPatchCnt; ++i) {
            const uint32_t va = kTrainingBlacklistBaseVa + i * 4u;
            if (mem.r32(va) != kStageUnlockSentinel) {
                mem.w32(va, kStageUnlockSentinel);
                ++patched;
            }
        }
    }

    if (mem.in_bounds(kVersusBlacklistBaseVa, (kVersusBlacklistPatchCnt + 2u) * 4u) &&
        mem.r32(kVersusBlacklistDummyVa) == kStageIdExcludedDummy &&
        mem.r32(kVersusBlacklistTermVa) == kStageListTerminator) {
        for (uint32_t i = 0u; i < kVersusBlacklistPatchCnt; ++i) {
            const uint32_t va = kVersusBlacklistBaseVa + i * 4u;
            if (mem.r32(va) != kStageUnlockSentinel) {
                mem.w32(va, kStageUnlockSentinel);
                ++patched;
            }
        }
    }

    if (mem.in_bounds(kBgm55EntryBaseVa, 0x20u) &&
        mem.r32(kBgm55EntryBaseVa) != 0u &&
        mem.r32(kBgm55FilenameVa) == kBgm55PrefixBgmm &&
        mem.r32(kBgm55FilenameVa + 4u) == kBgm55SuffixE56) {
        mem.w32(kBgm55FilenamePatchVa, kBgm55PatchedTail);
        mem.w32(kBgm55LoopPosHiVa, kBgm55LoopPosHiPatched);
        patched += 2u;
    }

    return patched;
}

RollbackManager::RollbackManager(size_t max_ring_frames)
    : max_ring_frames_(max_ring_frames > 0 ? max_ring_frames : 1) {
    ring_.reserve(max_ring_frames_);
}

bool RollbackManager::save_state(const GuestMemory& mem, RollbackStateSnapshot& out) const noexcept {
    for (const auto& reg : kRollbackRegions) {
        if (!mem.read_bytes(reg.mbaa_data_va, out.data.data() + reg.snapshot_offset, reg.byte_size)) {
            return false;
        }
    }
    out.battle_tick = mem.r32(kBattleTickVa);
    out.checksum    = compute_snapshot_checksum(out.data.data(), out.data.size());
    return true;
}

bool RollbackManager::load_state(GuestMemory& mem, const RollbackStateSnapshot& snapshot) const noexcept {
    for (const auto& reg : kRollbackRegions) {
        if (!mem.write_bytes(reg.mbaa_data_va, snapshot.data.data() + reg.snapshot_offset, reg.byte_size)) {
            return false;
        }
    }
    return true;
}

bool RollbackManager::push_frame_snapshot(const GuestMemory& mem, uint32_t frame) {
    RollbackStateSnapshot snap;
    snap.frame = frame;
    if (!save_state(mem, snap)) {
        return false;
    }

    for (auto& existing : ring_) {
        if (existing.frame == frame) {
            existing = snap;
            return true;
        }
    }
    if (ring_.size() >= max_ring_frames_) {
        ring_.erase(ring_.begin());
    }
    ring_.push_back(snap);
    return true;
}

bool RollbackManager::rollback_to_frame(GuestMemory& mem, uint32_t frame) const noexcept {
    for (const auto& snap : ring_) {
        if (snap.frame == frame) {
            return load_state(mem, snap);
        }
    }
    return false;
}

uint32_t RollbackManager::live_checksum(const GuestMemory& mem) const noexcept {
    RollbackStateSnapshot snap;
    if (!save_state(mem, snap)) return 0;
    return snap.checksum;
}

uint32_t RollbackManager::battle_tick(const GuestMemory& mem) const noexcept {
    return mem.r32(kBattleTickVa);
}

void RollbackManager::clear_history() noexcept {
    ring_.clear();
}

bool RollbackManager::ggpo_save_game_state(
    const GuestMemory& mem, uint8_t** buffer, int* len, int* checksum, int frame) const {
    if (!buffer || !len) return false;
    RollbackStateSnapshot snap;
    snap.frame = static_cast<uint32_t>(frame);
    if (!save_state(mem, snap)) return false;

    auto* raw = new uint8_t[RollbackStateSnapshot::kTotalStateBytes];
    std::memcpy(raw, snap.data.data(), RollbackStateSnapshot::kTotalStateBytes);
    *buffer = raw;
    *len    = static_cast<int>(RollbackStateSnapshot::kTotalStateBytes);
    if (checksum) {
        *checksum = static_cast<int>(snap.checksum);
    }
    return true;
}

bool RollbackManager::ggpo_load_game_state(GuestMemory& mem, const uint8_t* buffer, int len) const {
    if (!buffer || len != static_cast<int>(RollbackStateSnapshot::kTotalStateBytes)) {
        return false;
    }
    RollbackStateSnapshot snap;
    std::memcpy(snap.data.data(), buffer, RollbackStateSnapshot::kTotalStateBytes);
    return load_state(mem, snap);
}

void RollbackManager::ggpo_free_buffer(uint8_t* buffer) const noexcept {
    delete[] buffer;
}

} // namespace mbaa_recomp
