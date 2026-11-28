#pragma once

/**
 * @file netplay_rollback.h
 * @brief Full CCCaster v3.1 rollback engine: 61 static regions (1,229,047 B) +
 *        1,000x3 dynamic child pointers (12,000 B) + [0x0077bf9c] TTL cleanup +
 *        232B RngState + 160B MD5 SyncHash + 1,500B SFX OR-merge.
 *
 * Designed for iPhone SE 2020 (3 GB RAM): ring buffer is lazily allocated ONLY
 * while a Netplay session is active (~19.8 MiB for 16 frames) and freed
 * immediately on disconnect (0 B overhead during offline play).
 */

#include "mbaa_recomp/guest_memory.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace mbaa_recomp {

struct NetplayRollbackRegion {
    uint32_t mbaa_data_va;
    uint32_t byte_size;
    uint32_t snapshot_offset;
};

struct RngStateBlock {
    static constexpr size_t kByteSize = 232u; // 0xE8 bytes: [0x563778], [0x56377c], [0x564068], [0x564070..+0xDC)
    std::array<uint8_t, kByteSize> bytes{};
};

struct SyncHashData {
    static constexpr size_t kP1Stride = 0x0AFCu;

    uint32_t indexed_frame = 0u;
    uint32_t flags         = 0u;
    std::array<uint8_t, 16> rng_md5{};
    std::array<uint32_t, 4> globals{}; // 0x562a3c, 0x562a40, 0x564b14, 0x564b18
    std::array<uint8_t, 44> p1_slice{};
    std::array<uint8_t, 44> p2_slice{};

    [[nodiscard]] bool matches_gameplay(const SyncHashData& other) const noexcept;
};

struct FullRollbackSnapshot {
    static constexpr size_t kStaticRegionCount = 61u;
    static constexpr size_t kStaticStateBytes  = 1229047u; // 0x12C0F7 bytes
    static constexpr size_t kDynamicSlotCount  = 1000u;    // 0x0067bde8 array length
    static constexpr size_t kDynamicSlotStride = 0x33Cu;
    static constexpr size_t kDynamicChildCount = kDynamicSlotCount * 3u;
    static constexpr size_t kDynamicChildBytes = kDynamicChildCount * sizeof(uint32_t); // 12,000 B
    static constexpr size_t kTotalTreeBytes    = kStaticStateBytes + kDynamicChildBytes; // 1,241,047 B (0x12EFD7)
    static constexpr size_t kSfxArrayBytes     = 1500u;    // 0x5DC bytes at 0x0076e008 / 0x0076c0b8

    uint32_t frame = 0u;
    bool     valid = false;
    std::vector<uint8_t> static_data;
    std::array<uint32_t, kDynamicChildCount> child_ptrs{};
    std::array<uint8_t, kSfxArrayBytes> sfx_triggers{};
};

/// Returns the canonical 61 top-level static rollback regions (1,229,047 bytes).
[[nodiscard]] const std::array<NetplayRollbackRegion, FullRollbackSnapshot::kStaticRegionCount>&
get_full_rollback_regions() noexcept;

/// Computes RFC 1321 MD5 digest over arbitrary bytes into `out_digest[16]`.
void compute_md5(const uint8_t* data, size_t len, uint8_t out_digest[16]) noexcept;

/// Captures / restores the explicit 232-byte combat PRNG state (CCCaster RngState msg 0x16).
bool capture_rng_state(const GuestMemory& mem, RngStateBlock& out) noexcept;
bool apply_rng_state(GuestMemory& mem, const RngStateBlock& in) noexcept;

/// Builds CCCaster v3.1 SyncHash (0x663973b0) over live GuestMemory.
bool build_sync_hash(const GuestMemory& mem, uint32_t indexed_frame, uint32_t flags, SyncHashData& out) noexcept;

/// Executes `[0x0077bf9c]` container TTL cleanup (`ttl == 1` erased, `ttl > 1` decremented)
/// mirroring `hook.dll` `0x663aa000..0x663aa2ef` across `rollback_frames` steps.
void cleanup_transient_containers(GuestMemory& mem, uint32_t rollback_frames) noexcept;

class NetplayRollbackEngine {
public:
    static constexpr size_t kMaxRingFrames       = 16u;
    static constexpr uint32_t kDynamicBaseVa     = 0x0067BDE8u;
    static constexpr uint32_t kSfxTriggerQueueVa = 0x0076E008u;
    static constexpr uint32_t kSfxPlayedCacheVa  = 0x0076C0B8u;

    NetplayRollbackEngine() = default;
    ~NetplayRollbackEngine();

    NetplayRollbackEngine(const NetplayRollbackEngine&) = delete;
    NetplayRollbackEngine& operator=(const NetplayRollbackEngine&) = delete;

    /// Lazily allocates the 16-frame ring buffer (~19.8 MiB) when Netplay starts.
    bool allocate_session(size_t max_rollback_frames = 4u);

    /// Frees all ring buffer memory immediately on disconnect (0 B offline overhead).
    void release_session() noexcept;

    [[nodiscard]] bool is_allocated() const noexcept { return !ring_.empty(); }
    [[nodiscard]] size_t allocated_bytes() const noexcept;
    [[nodiscard]] size_t max_rollback_frames() const noexcept { return max_rollback_frames_; }
    void set_max_rollback_frames(size_t frames) noexcept;

    /// Captures all 61 static regions + 1,000x3 dynamic child pointers + last-frame SFX cache.
    bool save_frame(const GuestMemory& mem, uint32_t frame) noexcept;

    /// Records the live frame's played SFX mask (`0x0076c0b8`, 1,500 B) after `sub_0040e390`.
    void record_live_frame_sfx(const GuestMemory& mem, uint32_t frame) noexcept;

    /// Restores all 61 static regions + 1,000x3 dynamic child pointers for `frame`,
    /// runs `[0x0077bf9c]` TTL cleanup for `(current_frame - frame)` steps, and seeds
    /// the SFX OR-merge filter from discarded frames `[frame+1 .. current_frame]`.
    bool rollback_to_frame(GuestMemory& mem, uint32_t target_frame, uint32_t current_frame) noexcept;

    /// Captures any SFX triggered during a silent resimulation tick (`0x0076c0b8` / `0x0076e008`).
    void capture_resim_sfx(const GuestMemory& mem) noexcept;

    /// Re-injects missed unmuted SFX into `0x0076e008` right before live catchup frame ticks.
    void commit_resim_sfx(GuestMemory& mem) noexcept;

    /// Clears ring valid flags and SFX accumulators (e.g. on match reset) without freeing pool.
    void reset_match_state() noexcept;

private:
    size_t max_rollback_frames_ = 4u;
    std::vector<FullRollbackSnapshot> ring_;
    std::array<uint8_t, FullRollbackSnapshot::kSfxArrayBytes> sfx_already_played_{};
    std::array<uint8_t, FullRollbackSnapshot::kSfxArrayBytes> sfx_resim_accum_{};
};

/// Installs or restores CCCaster v3.1 indirect-dispatch overrides (`0x004a00b0` PollInputDevice).
/// Offline (`active == false`) is a 100% pass-through to unmodified lifted code.
/// Note: direct C++ calls in build_gen/ (`0x004330c0`/`0x004bdbc0`, etc.) honor [0x0055D25C]
/// and HLE frame boundaries (`hle_win32`, `hle_input`, `hle_d3d9_metal`, `hle_audio`) directly.
void register_dispatch_netplay_overrides(bool active);

} // namespace mbaa_recomp
