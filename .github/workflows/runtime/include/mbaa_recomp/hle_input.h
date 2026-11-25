#pragma once

/**
 * @file hle_input.h
 * @brief DirectInput8 HLE bridge for iOS TouchOverlayView and Apple GCController.
 *
 * Pure C++20 header so both .cpp runtime/recompiled files and .mm UIKit/GameController files
 * can include it directly without Objective-C dependencies.
 */

#include "mbaa_recomp/cpu_context.h"
#include "mbaa_recomp/guest_memory.h"

#include <cstdint>

namespace mbaa_recomp {

/// Touch & virtual controller input bitmask shared with ios/App/TouchOverlayView.mm.
enum TouchButton : uint32_t {
    kTouchNone  = 0u,
    kTouchUp    = 1u << 0,
    kTouchDown  = 1u << 1,
    kTouchLeft  = 1u << 2,
    kTouchRight = 1u << 3,
    kTouchA     = 1u << 4,
    kTouchB     = 1u << 5,
    kTouchC     = 1u << 6,
    kTouchD     = 1u << 7,
    kTouchE     = 1u << 8,
    kTouchStart = 1u << 9,
    kTouchCoin  = 1u << 10,
    kTouchFN1   = 1u << 11,
    kTouchFN2   = 1u << 12,
    kTouchPause = 1u << 13,
    kTouchDash  = 1u << 14, // Convenience macro: A + B
    kTouchHeat  = 1u << 15, // Convenience macro: A + B + C
};

struct TouchInputState {
    uint32_t buttons   = 0;     // Bitmask of TouchButton flags
    float    stick_x   = 0.0f;  // Normalized [-1.0, +1.0] optional D-pad/stick X
    float    stick_y   = 0.0f;  // Normalized [-1.0, +1.0] optional D-pad/stick Y
    bool     any_touch = false; // True when any virtual touch control is active
};

/// Updates live touch input state from TouchOverlayView (thread-safe).
void input_set_touch_state(const TouchInputState& state);

/// Returns the latest touch input state.
[[nodiscard]] TouchInputState input_get_touch_state();

/// Initializes Apple GCController discovery / notification observers.
void input_init();
void input_shutdown();

/// Polls GCController + keyboard/touch state once per frame before guest update.
void input_poll_platform();

/// Returns true if a physical MFi/Bluetooth/USB GCController is currently connected.
[[nodiscard]] bool input_has_gc_controller();

/// Returns Win32 GetKeyState / GetAsyncKeyState compatible 16-bit state for virtual key `vk`.
[[nodiscard]] int16_t input_get_vk_state(int vk_code);

/// HLE entry for DINPUT8.dll!DirectInput8Create (stdcall, 5 args: 20 bytes).
void hle_direct_input8_create(CpuContext& ctx, GuestMemory& mem);

} // namespace mbaa_recomp
