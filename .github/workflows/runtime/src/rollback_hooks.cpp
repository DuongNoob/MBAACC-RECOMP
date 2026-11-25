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
