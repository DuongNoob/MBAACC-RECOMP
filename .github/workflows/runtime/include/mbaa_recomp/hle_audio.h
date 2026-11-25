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

/// HLE entry for DSOUND.dll!ord_11 (DirectSoundCreate8, stdcall, 3 args: 12 bytes).
void hle_direct_sound_create8(CpuContext& ctx, GuestMemory& mem);

} // namespace mbaa_recomp
