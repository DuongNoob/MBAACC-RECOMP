#pragma once

/**
 * @file hle_win32.h
 * @brief Win32 / POSIX / BSD Socket / COM IAT HLE dispatcher for all 184+ MBAA.exe imports.
 */

#include "mbaa_recomp/cpu_context.h"
#include "mbaa_recomp/guest_memory.h"

#include <cstdint>
#include <functional>
#include <string>

namespace mbaa_recomp {

/// Initializes Win32 HLE state (maps ./ and .\ case-insensitively to `assets_dir`).
void hle_win32_init(const std::string& assets_dir, uint32_t screen_width, uint32_t screen_height);
void hle_win32_shutdown();

/// Dispatches a call to any MBAA.exe IAT slot (0x0051B000..0x0051B40C).
void hle_iat_call(CpuContext& ctx, GuestMemory& mem, uint32_t iat_va);

/// Resolves an IAT VA (or synthetic kIatThunkBase VA) to "DLL!Name" or nullptr if invalid.
[[nodiscard]] const char* hle_iat_name(uint32_t va);

/// Converts synthetic kIatThunkBase VA back to canonical IAT VA (returns 0 if not an IAT thunk).
[[nodiscard]] uint32_t hle_thunk_to_iat_va(uint32_t va) noexcept;

/// Cooperative frame synchronization hooks for iOS MTKView 60 Hz step loop.
void hle_win32_set_guest_main_thread();
void hle_win32_set_frame_yield_callback(std::function<bool()> callback);
void hle_win32_post_quit(int exit_code = 0);
[[nodiscard]] bool hle_win32_is_quit_requested() noexcept;

/// Optional D3D9 / D3DX9 IAT forwarding hook wired by RuntimeEngine to D3D9MetalBridge.
using D3DIatHandlerFn = void (*)(uint32_t iat_va, const char* api_name, CpuContext& ctx, GuestMemory& mem);
void hle_win32_register_d3d_handler(D3DIatHandlerFn fn);

/// Maps a Windows/relative guest path case-insensitively inside assets_dir.
[[nodiscard]] std::string hle_win32_resolve_path(const std::string& guest_path, bool for_write = false);

/// Signals a synthetic Win32 Event handle (used by DirectSoundNotify and thread sync).
void hle_win32_signal_event(uint32_t handle_val);

/// DirectShow COM CoCreateInstance helper (implemented in hle_dshow.cpp).
bool hle_dshow_try_cocreate(
    GuestMemory& mem,
    const uint8_t* clsid_bytes,
    const uint8_t* iid_bytes,
    uint32_t* out_iface_va);

/// Optional hook for future FFmpeg/AVFoundation MPEG playback replacement.
using DShowVideoHookFn = bool (*)(const std::string& file_path);
void hle_dshow_set_video_hook(DShowVideoHookFn fn);

} // namespace mbaa_recomp
