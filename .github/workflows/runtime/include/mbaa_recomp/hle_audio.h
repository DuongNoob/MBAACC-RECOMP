#pragma once

/**
 * @file hle_audio.h
 * @brief DirectSound8 HLE PCM mixer backed by Apple AudioToolbox AudioQueue / AVAudioSession.
 */

#include "mbaa_recomp/cpu_context.h"
#include "mbaa_recomp/guest_memory.h"

#include <cstdint>

namespace mbaa_recomp {

/// Initializes / tears down the iOS AudioQueue PCM mixer.
void audio_init();
void audio_shutdown();
void audio_set_muted(bool muted);

/// Advances streaming notification positions & audio session health once per frame.
void audio_update_streams();

/// Mutes new SFX voice triggers (`dsb_play`) during netplay rollback resimulation
/// while leaving BGM / AudioQueue playback active.
void audio_set_rollback_mute(bool muted);
[[nodiscard]] bool audio_is_rollback_muted();

/// Rollback SFX OR-merge / deduplication tracking around 0x0076e008 (1,500 SFX slots).
void audio_rollback_set_tracking(bool active, uint32_t current_frame);
void audio_rollback_begin_catchup(uint32_t rollback_target_frame);
void audio_rollback_prepare_live_catchup(GuestMemory& mem);
void audio_rollback_end_catchup();

/// HLE entry for DSOUND.dll!ord_11 (DirectSoundCreate8, stdcall, 3 args: 12 bytes).
void hle_direct_sound_create8(CpuContext& ctx, GuestMemory& mem);

} // namespace mbaa_recomp
