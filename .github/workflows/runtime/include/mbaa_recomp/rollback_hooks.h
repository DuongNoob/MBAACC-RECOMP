#pragma once

/**
 * @file rollback_hooks.h
 * @brief Deterministic 24-region (252-byte) .data snapshot/restore hooks for GGPO rollback.
 *
 * Verified from c:\Users\A\Desktop\AI\google\mbaacc-src\evidence\companion_binaries.json
 * (hook_dll.rollback_state_ranges, 0x0074D598..0x007B1D2C including battle tick 0x007717D8).
 */

#include "mbaa_recomp/guest_memory.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace mbaa_recomp {

struct RollbackRegion {
    uint32_t mbaa_data_va;
    uint32_t byte_size;
    uint32_t snapshot_offset;
};

struct RollbackStateSnapshot {
    static constexpr size_t kRegionCount    = 24;
    static constexpr size_t kTotalStateBytes = 252;

    std::array<uint8_t, kTotalStateBytes> data{};
    uint32_t frame       = 0;
    uint32_t battle_tick = 0;
    uint32_t checksum    = 0;
};

/// Returns the canonical 24 deterministic rollback memory regions (252 bytes total).
[[nodiscard]] const std::array<RollbackRegion, RollbackStateSnapshot::kRegionCount>&
get_rollback_regions() noexcept;

/// Computes FNV-1a 32-bit checksum over a 252-byte snapshot buffer.
[[nodiscard]] uint32_t compute_snapshot_checksum(const uint8_t* bytes, size_t len) noexcept;

/// Unlocks all CCCaster extra Training/Versus stages and restores Stage 55 BGM in GuestMemory.
///
/// Mirrors the exact 24 .data/.bss entries from CCCaster v3.1 `hook.dll` (PatchGroup 0x6673cce0):
///   - Training blacklist (`0x0054CEBC..0x0054CEC4`, 3 dwords -> `0xFF`): unlocks stages
///     55 (`...and nothing heart`), 57 (`G TABLE`), and 58 (`G TABLE`), preserving 99 and -1.
///   - Versus/Normal/Random blacklist (`0x0054CF68..0x0054CFB0`, 19 dwords -> `0xFF`): unlocks
///     stages 3, 4, 18, 20, 21, 23, 31, 32, 43, 44, 47, 49, 50, 51, 52, 54, 55, 57, 58,
///     preserving 99 and -1.
///   - Stage 55 BGM table entry (`0x007695E0`, populated from `.\bgm\bgm.txt` by `sub_004dd5d0`):
///     patches `"bgmme56\0"` -> `"bgmme55\0"` (`0x007695F6 = 0x35`) and loop point high dword
///     (`0x007695EC = 0x401ECCAA`) so `bgmme55.ogg` plays with its original loop point.
///
/// Fast and idempotent; safe to call both after PE load and on each frame (to catch runtime
/// `bgm.txt` loads/reloads in `sub_004dd5d0`). Returns the count of 32-bit slots updated.
uint32_t apply_cccaster_stage_unlocks(GuestMemory& mem) noexcept;

class RollbackManager {
public:
    static constexpr uint32_t kBattleTickVa = 0x007717D8u;

    explicit RollbackManager(size_t max_ring_frames = 16);

    /// Captures all 24 regions (252 bytes) from GuestMemory into `out`.
    bool save_state(const GuestMemory& mem, RollbackStateSnapshot& out) const noexcept;

    /// Restores all 24 regions (252 bytes) from `snapshot` back into GuestMemory.
    bool load_state(GuestMemory& mem, const RollbackStateSnapshot& snapshot) const noexcept;

    /// Captures current state into internal ring buffer keyed by frame number.
    bool push_frame_snapshot(const GuestMemory& mem, uint32_t frame);

    /// Restores state for `frame` from internal ring buffer if present.
    bool rollback_to_frame(GuestMemory& mem, uint32_t frame) const noexcept;

    /// Returns checksum of live 24-region state in GuestMemory without modifying state.
    [[nodiscard]] uint32_t live_checksum(const GuestMemory& mem) const noexcept;

    /// Reads current battle frame counter at 0x007717D8.
    [[nodiscard]] uint32_t battle_tick(const GuestMemory& mem) const noexcept;

    void clear_history() noexcept;

    // GGPO-compatible C-style buffer helpers
    bool ggpo_save_game_state(const GuestMemory& mem, uint8_t** buffer, int* len, int* checksum, int frame) const;
    bool ggpo_load_game_state(GuestMemory& mem, const uint8_t* buffer, int len) const;
    void ggpo_free_buffer(uint8_t* buffer) const noexcept;

private:
    size_t max_ring_frames_ = 16;
    std::vector<RollbackStateSnapshot> ring_;
};

} // namespace mbaa_recomp
