#pragma once

/**
 * @file runtime_engine.h
 * @brief Top-level lifecycle controller driving MBAA.exe AOT recompiled code on iOS/macOS.
 *
 * Cooperatively bridges WinMain (0x0040D240) / MainMessageLoop (0x0040D310) /
 * MainFrameUpdate (0x0040E390) to MTKView 60 Hz frame callbacks.
 */

#include "mbaa_recomp/cpu_context.h"
#include "mbaa_recomp/guest_memory.h"
#include "mbaa_recomp/hle_input.h"
#include "mbaa_recomp/rollback_hooks.h"

#include <cstdint>
#include <memory>
#include <string>

namespace mbaa_recomp {

enum class NetplayMode : uint8_t {
    Offline  = 0,
    Host     = 1,
    Join     = 2,
    Spectate = 3,
};

enum class NetplayConnState : uint8_t {
    Offline     = 0,
    Listening   = 1,
    Connecting  = 2,
    Handshaking = 3,
    Connected   = 4,
    InGame      = 5,
    Error       = 6,
};

struct NetplayConfig {
    std::string peer_ip;
    uint16_t    port          = 3939u; // 0 = ephemeral OS port when hosting
    std::string player_name   = "iOS";
    int         delay_frames  = -1;    // -1 = Auto from RTT; 0..254 = fixed
    int         max_rollback  = 4;     // 0..15 (CCCaster config.ini defaultRollback=4)
    bool        training_mode = false;
};

struct NetplayStatus {
    NetplayMode      mode           = NetplayMode::Offline;
    NetplayConnState state          = NetplayConnState::Offline;
    bool             active         = false;
    bool             connected      = false;
    bool             in_match       = false;
    uint16_t         local_port     = 0u;
    std::string      local_ipv4;
    std::string      peer_addr;
    std::string      peer_name;
    double           ping_ms        = 0.0; // RTT in ms
    double           one_way_ms     = 0.0; // Mean one-way latency in ms
    int              delay_frames   = 0;
    int              max_rollback   = 4;
    uint32_t         current_frame  = 0u;
    uint32_t         rollback_count = 0u;
    uint32_t         desync_count   = 0u;
    std::string      state_label;
    std::string      last_error;
};

class RuntimeEngine {
public:
    RuntimeEngine();
    ~RuntimeEngine();

    RuntimeEngine(const RuntimeEngine&) = delete;
    RuntimeEngine& operator=(const RuntimeEngine&) = delete;

    /// Initializes guest arena, loads BYOC MBAA.exe sections from `assets_dir/MBAA.exe`,
    /// binds `metal_layer` (CAMetalLayer*) to D3D9MetalBridge, and boots WinMain up to
    /// the cooperative 60 Hz frame loop.
    bool init(const std::string& assets_dir, void* metal_layer, int width, int height);

    /// Runs exactly one 60 Hz frame tick (Touch/GCController poll -> guest MainFrameUpdate
    /// -> Metal EndScene/Present).
    void step_frame();

    /// Updates touch button/stick mask from ios/App/TouchOverlayView.
    void set_touch_state(const TouchInputState& state);

    /// Handles iOS UIApplicationDidReceiveMemoryWarningNotification (evicts LRU Metal textures).
    void handle_memory_warning();

    /// Updates Metal drawable pixel size on view resize / orientation change.
    void resize_drawable(int width, int height);

    /// Cleanly exits the guest message loop, saves config, and frees runtime resources.
    void shutdown();

    /// CCCaster v3.1 Netplay session control (lazy-allocates rollback ring buffer on start,
    /// frees completely on stop_netplay() / disconnect).
    bool start_netplay_host(const NetplayConfig& config);
    bool start_netplay_join(const NetplayConfig& config);
    bool start_netplay_spectate(const NetplayConfig& config);
    void stop_netplay();
    [[nodiscard]] NetplayStatus netplay_status() const;
    [[nodiscard]] static std::string get_local_ipv4();

    [[nodiscard]] bool is_initialized() const noexcept;
    [[nodiscard]] bool is_running() const noexcept;
    [[nodiscard]] uint64_t frame_count() const noexcept;
    [[nodiscard]] const std::string& last_error() const noexcept;
    [[nodiscard]] std::string debug_summary() const;

    [[nodiscard]] CpuContext& cpu_context() noexcept;
    [[nodiscard]] GuestMemory& guest_memory() noexcept;
    [[nodiscard]] RollbackManager& rollback_manager() noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace mbaa_recomp
