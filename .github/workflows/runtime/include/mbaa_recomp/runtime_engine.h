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

    /// Cleanly exits the guest message loop, saves config, and frees runtime resources.
    void shutdown();

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
