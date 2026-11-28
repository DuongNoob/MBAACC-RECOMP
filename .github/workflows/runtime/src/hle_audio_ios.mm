#include "mbaa_recomp/hle_audio.h"
#include "mbaa_recomp/dispatch.h"
#include "mbaa_recomp/hle_win32.h"

#if defined(__APPLE__)
#import <AudioToolbox/AudioToolbox.h>
#import <AVFoundation/AVFoundation.h>
#import <TargetConditionals.h>
#endif

#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

namespace mbaa_recomp {

namespace {

constexpr uint32_t kDS_OK            = 0x00000000u;
constexpr uint32_t kDSERR_INVALID    = 0x80070057u;
constexpr uint32_t kDSERR_OUTOFMEM   = 0x8007000Eu;
constexpr uint32_t kDSBPLAY_LOOPING  = 0x00000001u;
constexpr uint32_t kDSBSTATUS_PLAYING= 0x00000001u;
constexpr uint32_t kDSBSTATUS_LOOPING= 0x00000004u;
constexpr uint32_t kDSBCAPS_PRIMARY  = 0x00000001u;
constexpr uint32_t kDSBLOCK_FROMWRITE= 0x00000001u;
constexpr uint32_t kDSBLOCK_ENTIRE   = 0x00000002u;

constexpr uint32_t kOutputSampleRate = 44100u;
constexpr uint32_t kOutputChannels   = 2u;
constexpr uint32_t kBufferFrames     = 512u;
constexpr uint32_t kNumAudioBuffers  = 3u;

struct NotifyPoint {
    uint32_t offset_bytes = 0;
    uint32_t event_handle = 0;
};

struct SoundVoice {
    uint32_t id              = 0;
    uint32_t obj_va          = 0;
    uint32_t notify_obj_va   = 0;
    uint32_t guest_buf_va    = 0;
    uint32_t buffer_bytes    = 0;
    uint32_t flags           = 0;
    uint32_t sample_rate     = 44100;
    uint16_t channels        = 2;
    uint16_t bits_per_sample = 16;
    uint32_t buf_refcount    = 1;
    uint32_t notify_refcount = 0;
    bool     is_primary      = false;
    bool     playing         = false;
    bool     looping         = false;
    int32_t  volume_mb       = 0;     // DirectSound millibels [-10000..0]
    int32_t  pan_mb          = 0;     // DirectSound pan [-10000..+10000]
    double   frame_cursor    = 0.0;   // Fractional input frame position
    uint32_t last_lock_off   = 0;
    uint32_t last_lock_len   = 0;
    uint32_t prev_byte_pos   = 0;
    std::vector<uint8_t> pcm;
    std::vector<NotifyPoint> notifies;
};

struct AudioState {
    static constexpr uint32_t kSfxTableVa   = 0x0076E008u; // 1,500 SFX trigger bytes
    static constexpr uint32_t kSfxPtrsVa    = 0x0076C6F8u; // 1,500 SFX wrapper pointers
    static constexpr size_t   kSfxSlotCount = 1500u;

    std::mutex mutex;
    std::atomic<bool> initialized{false};
    std::atomic<bool> muted{false};
    std::atomic<bool> rollback_mute{false};
    std::atomic<bool> rollback_tracking{false};
    std::atomic<uint32_t> rollback_frame{0u};
    std::atomic<bool> in_rollback_catchup{false};
    std::atomic<uint32_t> catchup_rollback_target{0u};
    std::array<uint32_t, kSfxSlotCount> sfx_last_played_frame{};
    std::array<uint8_t,  kSfxSlotCount> sfx_has_played{};
    std::array<uint8_t,  kSfxSlotCount> resim_sfx_accum{};
    std::unordered_map<uint32_t, std::shared_ptr<SoundVoice>> voices_by_obj;
    std::vector<std::shared_ptr<SoundVoice>> active_list;

    uint32_t next_voice_id  = 1u;
    uint32_t ds8_vtable     = 0;
    uint32_t buf_vtable     = 0;
    uint32_t notify_vtable  = 0;
    uint32_t ds8_obj_va     = 0;
    uint32_t health_tick    = 0;

#if defined(__APPLE__)
    AudioQueueRef queue = nullptr;
    AudioQueueBufferRef aq_buffers[kNumAudioBuffers] = {};
#endif
};

AudioState g_audio;

int find_triggered_sfx_slot(const GuestMemory& mem, uint32_t obj_va) noexcept {
    if (!mem.in_bounds(AudioState::kSfxTableVa, AudioState::kSfxSlotCount) ||
        !mem.in_bounds(AudioState::kSfxPtrsVa, AudioState::kSfxSlotCount * 4u)) {
        return -1;
    }
    const uint8_t* trig = mem.cptr(AudioState::kSfxTableVa);
    for (size_t i = 0; i < AudioState::kSfxSlotCount; ++i) {
        if (trig[i] != 1u) continue;
        const uint32_t wrapper = mem.r32(AudioState::kSfxPtrsVa + static_cast<uint32_t>(i * 4u));
        if (wrapper == 0u || !mem.in_bounds(wrapper + 4u, 4u)) continue;
        const uint32_t inner = mem.r32(wrapper + 4u);
        if (inner == 0u || !mem.in_bounds(inner, 4u)) continue;
        if (mem.r32(inner) == obj_va) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

float millibels_to_gain(int32_t mb) noexcept {
    if (mb <= -10000) return 0.0f;
    if (mb >= 0) return 1.0f;
    return std::pow(10.0f, static_cast<float>(mb) / 2000.0f);
}

void compute_pan_gains(int32_t pan_mb, float& left_g, float& right_g) noexcept {
    left_g = 1.0f;
    right_g = 1.0f;
    if (pan_mb > 0) {
        left_g = millibels_to_gain(-pan_mb);
    } else if (pan_mb < 0) {
        right_g = millibels_to_gain(pan_mb);
    }
}

void sample_voice_frame(const SoundVoice& v, uint32_t frame_idx, float& out_l, float& out_r) noexcept {
    const uint32_t bytes_per_sample = std::max<uint32_t>(1u, v.bits_per_sample / 8u);
    const uint32_t block_align = std::max<uint32_t>(1u, v.channels * bytes_per_sample);
    const uint32_t total_frames = static_cast<uint32_t>(v.pcm.size() / block_align);
    if (total_frames == 0u || frame_idx >= total_frames) {
        out_l = out_r = 0.0f;
        return;
    }

    const size_t base = static_cast<size_t>(frame_idx) * block_align;
    auto decode_sample = [&](uint32_t ch_off) -> float {
        const size_t p = base + ch_off;
        if (v.bits_per_sample == 8u && p < v.pcm.size()) {
            return (static_cast<int32_t>(v.pcm[p]) - 128) / 128.0f;
        }
        if (v.bits_per_sample == 16u && p + 1u < v.pcm.size()) {
            int16_t s = 0;
            std::memcpy(&s, v.pcm.data() + p, sizeof(s));
            return static_cast<float>(s) / 32768.0f;
        }
        return 0.0f;
    };

    out_l = decode_sample(0u);
    out_r = (v.channels >= 2u) ? decode_sample(bytes_per_sample) : out_l;
}

void mix_output_frames(int16_t* out_interleaved, uint32_t num_frames) {
    if (g_audio.muted.load(std::memory_order_relaxed)) {
        std::memset(out_interleaved, 0, num_frames * kOutputChannels * sizeof(int16_t));
        return;
    }

    static thread_local std::vector<float> accum;
    accum.assign(num_frames * kOutputChannels, 0.0f);

    std::vector<uint32_t> events_to_signal;
    {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        for (auto& v : g_audio.active_list) {
            if (!v || !v->playing || v->is_primary || v->pcm.empty()) continue;

            const uint32_t bytes_per_sample = std::max<uint32_t>(1u, v->bits_per_sample / 8u);
            const uint32_t block_align = std::max<uint32_t>(1u, v->channels * bytes_per_sample);
            const uint32_t total_frames = static_cast<uint32_t>(v->pcm.size() / block_align);
            if (total_frames == 0u) continue;

            const float gain = millibels_to_gain(v->volume_mb);
            float pan_l = 1.0f, pan_r = 1.0f;
            compute_pan_gains(v->pan_mb, pan_l, pan_r);
            const float gl = gain * pan_l;
            const float gr = gain * pan_r;

            const double step = static_cast<double>(v->sample_rate) / static_cast<double>(kOutputSampleRate);
            const uint32_t old_byte_pos = v->prev_byte_pos;
            bool stopped_during_mix = false;

            for (uint32_t i = 0; i < num_frames; ++i) {
                uint32_t idx0 = static_cast<uint32_t>(v->frame_cursor);
                if (idx0 >= total_frames) {
                    if (v->looping) {
                        idx0 %= total_frames;
                        v->frame_cursor = std::fmod(v->frame_cursor, static_cast<double>(total_frames));
                    } else {
                        v->playing = false;
                        v->frame_cursor = 0.0;
                        stopped_during_mix = true;
                        for (const auto& np : v->notifies) {
                            if (np.offset_bytes == 0xFFFFFFFFu && np.event_handle != 0u) {
                                events_to_signal.push_back(np.event_handle);
                            }
                        }
                        break;
                    }
                }

                const uint32_t idx1 = (idx0 + 1u < total_frames) ? (idx0 + 1u) : (v->looping ? 0u : idx0);
                const float frac = static_cast<float>(v->frame_cursor - std::floor(v->frame_cursor));
                float l0 = 0.0f, r0 = 0.0f, l1 = 0.0f, r1 = 0.0f;
                sample_voice_frame(*v, idx0, l0, r0);
                sample_voice_frame(*v, idx1, l1, r1);

                accum[i * 2u + 0u] += (l0 + (l1 - l0) * frac) * gl;
                accum[i * 2u + 1u] += (r0 + (r1 - r0) * frac) * gr;

                v->frame_cursor += step;
            }

            if (stopped_during_mix) {
                for (const auto& np : v->notifies) {
                    if (np.offset_bytes == 0xFFFFFFFFu || np.event_handle == 0u) continue;
                    if (np.offset_bytes > old_byte_pos && np.offset_bytes < v->pcm.size()) {
                        events_to_signal.push_back(np.event_handle);
                    }
                }
                v->prev_byte_pos = 0u;
            } else {
                const uint32_t new_frame = static_cast<uint32_t>(v->frame_cursor) % total_frames;
                const uint32_t new_byte_pos = new_frame * block_align;
                for (const auto& np : v->notifies) {
                    if (np.offset_bytes == 0xFFFFFFFFu || np.event_handle == 0u) continue;
                    const bool crossed = (old_byte_pos <= new_byte_pos)
                        ? (np.offset_bytes > old_byte_pos && np.offset_bytes <= new_byte_pos)
                        : (np.offset_bytes > old_byte_pos || np.offset_bytes <= new_byte_pos);
                    if (crossed) {
                        events_to_signal.push_back(np.event_handle);
                    }
                }
                v->prev_byte_pos = new_byte_pos;
            }
        }
    }

    for (uint32_t ev : events_to_signal) {
        hle_win32_signal_event(ev);
    }

    for (size_t i = 0; i < accum.size(); ++i) {
        const float clamped = std::clamp(accum[i], -1.0f, 1.0f);
        out_interleaved[i] = static_cast<int16_t>(clamped * 32767.0f);
    }
}

#if defined(__APPLE__)
void audio_queue_callback(void* /*user_data*/, AudioQueueRef aq, AudioQueueBufferRef buf) {
    if (!g_audio.initialized.load(std::memory_order_relaxed)) {
        return;
    }
    buf->mAudioDataByteSize = kBufferFrames * kOutputChannels * sizeof(int16_t);
    mix_output_frames(static_cast<int16_t*>(buf->mAudioData), kBufferFrames);
    AudioQueueEnqueueBuffer(aq, buf, 0, nullptr);
}
#endif

// ---------------------------------------------------------------------------
// DirectSound8 / DirectSoundBuffer / DirectSoundNotify COM Methods (stdcall)
// ---------------------------------------------------------------------------
std::shared_ptr<SoundVoice> find_voice(uint32_t obj_va) {
    std::lock_guard<std::mutex> lock(g_audio.mutex);
    auto it = g_audio.voices_by_obj.find(obj_va);
    return (it != g_audio.voices_by_obj.end()) ? it->second : nullptr;
}

void ds_unk_addref(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va = ctx.arg32(mem, 0);
    uint32_t refs = 1u;
    {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        auto it = g_audio.voices_by_obj.find(obj_va);
        if (it != g_audio.voices_by_obj.end() && it->second) {
            if (obj_va == it->second->notify_obj_va) {
                refs = ++it->second->notify_refcount;
            } else {
                refs = ++it->second->buf_refcount;
            }
        }
    }
    ctx.eax = refs;
    ctx.ret_stdcall(mem, 4u);
}

void ds_unk_release(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va = ctx.arg32(mem, 0);
    std::shared_ptr<SoundVoice> removed;
    uint32_t remaining = 0u;
    {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        auto it = g_audio.voices_by_obj.find(obj_va);
        if (it != g_audio.voices_by_obj.end() && it->second) {
            auto v = it->second;
            if (obj_va == v->notify_obj_va) {
                if (v->notify_refcount > 0u) --v->notify_refcount;
                remaining = v->notify_refcount;
            } else {
                if (v->buf_refcount > 0u) --v->buf_refcount;
                remaining = v->buf_refcount;
                if (v->buf_refcount == 0u) {
                    v->playing = false;
                }
            }
            if (v->buf_refcount == 0u && v->notify_refcount == 0u) {
                removed = v;
                g_audio.voices_by_obj.erase(v->obj_va);
                g_audio.voices_by_obj.erase(v->notify_obj_va);
                g_audio.active_list.erase(
                    std::remove(g_audio.active_list.begin(), g_audio.active_list.end(), removed),
                    g_audio.active_list.end());
            }
        }
    }
    if (removed) {
        if (removed->guest_buf_va != 0u) mem.guest_free(removed->guest_buf_va);
        if (removed->obj_va != 0u) mem.guest_free(removed->obj_va);
        if (removed->notify_obj_va != 0u) mem.guest_free(removed->notify_obj_va);
    }
    ctx.eax = remaining;
    ctx.ret_stdcall(mem, 4u);
}

template <uint32_t ArgBytes>
void ds_ret_ok(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, ArgBytes);
}

void ds_query_interface(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va  = ctx.arg32(mem, 0);
    const uint32_t riid_va = ctx.arg32(mem, 1);
    const uint32_t ppv_va  = ctx.arg32(mem, 2);
    if (ppv_va == 0u) {
        ctx.eax = kDSERR_INVALID;
        ctx.ret_stdcall(mem, 12u);
        return;
    }

    uint8_t iid[16] = {};
    if (riid_va) mem.read_bytes(riid_va, iid, 16);

    // IID_IDirectSoundNotify: {B0210783-89CD-11D0-AF08-00A0C925CD16}
    if (iid[0] == 0x83 && iid[1] == 0x07 && iid[2] == 0x21 && iid[3] == 0xB0) {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        auto it = g_audio.voices_by_obj.find(obj_va);
        if (it != g_audio.voices_by_obj.end() && it->second && it->second->notify_obj_va != 0u) {
            ++it->second->notify_refcount;
            mem.w32(ppv_va, it->second->notify_obj_va);
            ctx.eax = kDS_OK;
            ctx.ret_stdcall(mem, 12u);
            return;
        }
    }
    {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        auto it = g_audio.voices_by_obj.find(obj_va);
        if (it != g_audio.voices_by_obj.end() && it->second) {
            if (obj_va == it->second->notify_obj_va) {
                ++it->second->notify_refcount;
            } else {
                ++it->second->buf_refcount;
            }
        }
    }
    mem.w32(ppv_va, obj_va);
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 12u);
}

std::shared_ptr<SoundVoice> create_voice_object(
    GuestMemory& mem, uint32_t buffer_bytes, uint32_t rate, uint16_t ch, uint16_t bits, bool primary, uint32_t flags) {
    auto v = std::make_shared<SoundVoice>();
    v->is_primary      = primary;
    v->flags           = flags;
    v->buffer_bytes    = primary ? 0u : std::max<uint32_t>(buffer_bytes, 4096u);
    v->sample_rate     = (rate != 0u) ? rate : 44100u;
    v->channels        = (ch != 0u) ? ch : 2u;
    v->bits_per_sample = (bits == 8u || bits == 16u) ? bits : 16u;
    v->buf_refcount    = 1u;
    v->notify_refcount = 0u;

    v->obj_va        = mem.guest_alloc(16u, 16u);
    v->notify_obj_va = mem.guest_alloc(16u, 16u);
    if (v->obj_va == 0u || v->notify_obj_va == 0u) {
        if (v->obj_va != 0u) mem.guest_free(v->obj_va);
        if (v->notify_obj_va != 0u) mem.guest_free(v->notify_obj_va);
        return nullptr;
    }

    if (!primary) {
        v->guest_buf_va = mem.guest_calloc(1u, v->buffer_bytes);
        if (v->guest_buf_va == 0u) {
            mem.guest_free(v->obj_va);
            mem.guest_free(v->notify_obj_va);
            return nullptr;
        }
        v->pcm.assign(v->buffer_bytes, 0u);
    }

    mem.w32(v->obj_va, g_audio.buf_vtable);
    mem.w32(v->notify_obj_va, g_audio.notify_vtable);

    std::lock_guard<std::mutex> lock(g_audio.mutex);
    v->id = g_audio.next_voice_id++;
    g_audio.voices_by_obj[v->obj_va] = v;
    g_audio.voices_by_obj[v->notify_obj_va] = v;
    g_audio.active_list.push_back(v);
    return v;
}

// IDirectSound8::GetCaps(this, pDSCaps) -> 8 bytes
void ds8_get_caps(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t caps_va = ctx.arg32(mem, 1);
    if (caps_va == 0u) {
        ctx.eax = kDSERR_INVALID;
        ctx.ret_stdcall(mem, 8u);
        return;
    }
    const uint32_t sz = mem.r32(caps_va + 0u);
    if (sz >= 96u && mem.in_bounds(caps_va, sz)) {
        mem.zero_bytes(caps_va + 4u, sz - 4u);
        mem.w32(caps_va + 4u,  0x00000F10u); // DSCAPS_CONTINUOUSRATE | PRIMARY/SECONDARY STEREO+16BIT
        mem.w32(caps_va + 8u,  100u);        // dwMinSecondarySampleRate
        mem.w32(caps_va + 12u, 192000u);     // dwMaxSecondarySampleRate
        mem.w32(caps_va + 16u, 1u);          // dwPrimaryBuffers
        mem.w32(caps_va + 20u, 64u);         // dwMaxHwMixingAllBuffers
        mem.w32(caps_va + 24u, 64u);         // dwMaxHwMixingStaticBuffers
        mem.w32(caps_va + 28u, 64u);         // dwMaxHwMixingStreamingBuffers
        mem.w32(caps_va + 32u, 64u);         // dwFreeHwMixingAllBuffers
        mem.w32(caps_va + 36u, 64u);         // dwFreeHwMixingStaticBuffers
        mem.w32(caps_va + 40u, 64u);         // dwFreeHwMixingStreamingBuffers
        mem.w32(caps_va + 68u, 16u * 1024u * 1024u); // dwTotalHwMemBytes
        mem.w32(caps_va + 72u, 16u * 1024u * 1024u); // dwFreeHwMemBytes
    }
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IDirectSound8::CreateSoundBuffer(this, pcDSBufferDesc, ppDSBuffer, pUnkOuter) -> 16 bytes
void ds8_create_sound_buffer(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t desc_va = ctx.arg32(mem, 1);
    const uint32_t pp_va   = ctx.arg32(mem, 2);
    if (desc_va == 0u || pp_va == 0u) {
        ctx.eax = kDSERR_INVALID;
        ctx.ret_stdcall(mem, 16u);
        return;
    }

    const uint32_t flags        = mem.r32(desc_va + 4u);
    const uint32_t buffer_bytes = mem.r32(desc_va + 8u);
    const uint32_t wfx_va       = mem.r32(desc_va + 16u);
    const bool is_primary       = (flags & kDSBCAPS_PRIMARY) != 0u;

    uint16_t ch = 2, bits = 16;
    uint32_t rate = 44100;
    if (wfx_va != 0u) {
        ch   = mem.r16(wfx_va + 2u);
        rate = mem.r32(wfx_va + 4u);
        bits = mem.r16(wfx_va + 14u);
    }

    auto v = create_voice_object(mem, buffer_bytes, rate, ch, bits, is_primary, flags);
    if (!v) {
        mem.w32(pp_va, 0u);
        ctx.eax = kDSERR_OUTOFMEM;
        ctx.ret_stdcall(mem, 16u);
        return;
    }
    mem.w32(pp_va, v->obj_va);
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 16u);
}

// IDirectSound8::DuplicateSoundBuffer(this, pOriginal, ppDuplicate) -> 12 bytes
void ds8_duplicate_sound_buffer(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t orig_va = ctx.arg32(mem, 1);
    const uint32_t pp_va   = ctx.arg32(mem, 2);
    auto orig = find_voice(orig_va);
    if (!orig || pp_va == 0u) {
        ctx.eax = kDSERR_INVALID;
        ctx.ret_stdcall(mem, 12u);
        return;
    }
    auto dup = create_voice_object(
        mem, orig->buffer_bytes, orig->sample_rate, orig->channels, orig->bits_per_sample, orig->is_primary, orig->flags);
    if (!dup) {
        mem.w32(pp_va, 0u);
        ctx.eax = kDSERR_OUTOFMEM;
        ctx.ret_stdcall(mem, 12u);
        return;
    }
    {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        dup->pcm = orig->pcm;
        if (dup->guest_buf_va && !dup->pcm.empty()) {
            mem.write_bytes(dup->guest_buf_va, dup->pcm.data(), dup->pcm.size());
        }
    }
    mem.w32(pp_va, dup->obj_va);
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 12u);
}

// IDirectSoundBuffer::GetCaps(this, pDSBufferCaps) -> 8 bytes
void dsb_get_caps(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va  = ctx.arg32(mem, 0);
    const uint32_t caps_va = ctx.arg32(mem, 1);
    auto v = find_voice(obj_va);
    if (!v || caps_va == 0u || !mem.in_bounds(caps_va, 20u)) {
        ctx.eax = kDSERR_INVALID;
        ctx.ret_stdcall(mem, 8u);
        return;
    }
    {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        mem.w32(caps_va + 4u,  v->flags);
        mem.w32(caps_va + 8u,  v->buffer_bytes);
        mem.w32(caps_va + 12u, 0u);
        mem.w32(caps_va + 16u, 0u);
    }
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IDirectSoundBuffer::GetFormat(this, pwfxFormat, dwSizeAllocated, pdwSizeWritten) -> 16 bytes
void dsb_get_format(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va     = ctx.arg32(mem, 0);
    const uint32_t wfx_va     = ctx.arg32(mem, 1);
    const uint32_t alloc_sz   = ctx.arg32(mem, 2);
    const uint32_t written_va = ctx.arg32(mem, 3);
    auto v = find_voice(obj_va);
    if (!v) {
        ctx.eax = kDSERR_INVALID;
        ctx.ret_stdcall(mem, 16u);
        return;
    }
    constexpr uint32_t kWfxSize = 18u;
    if (wfx_va != 0u && alloc_sz >= 16u && mem.in_bounds(wfx_va, std::min(alloc_sz, kWfxSize))) {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        const uint16_t block_align = static_cast<uint16_t>(v->channels * (v->bits_per_sample / 8u));
        const uint32_t avg_bps     = v->sample_rate * block_align;
        mem.w16(wfx_va + 0u,  1u); // WAVE_FORMAT_PCM
        mem.w16(wfx_va + 2u,  v->channels);
        mem.w32(wfx_va + 4u,  v->sample_rate);
        mem.w32(wfx_va + 8u,  avg_bps);
        mem.w16(wfx_va + 12u, block_align);
        mem.w16(wfx_va + 14u, v->bits_per_sample);
        if (alloc_sz >= kWfxSize) {
            mem.w16(wfx_va + 16u, 0u);
        }
    }
    if (written_va != 0u && mem.in_bounds(written_va, 4u)) {
        mem.w32(written_va, kWfxSize);
    }
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 16u);
}

// IDirectSoundBuffer::GetVolume(this, plVolume) -> 8 bytes
void dsb_get_volume(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va = ctx.arg32(mem, 0);
    const uint32_t out_va = ctx.arg32(mem, 1);
    auto v = find_voice(obj_va);
    if (v && out_va != 0u && mem.in_bounds(out_va, 4u)) {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        mem.w32(out_va, static_cast<uint32_t>(v->volume_mb));
    }
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IDirectSoundBuffer::GetPan(this, plPan) -> 8 bytes
void dsb_get_pan(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va = ctx.arg32(mem, 0);
    const uint32_t out_va = ctx.arg32(mem, 1);
    auto v = find_voice(obj_va);
    if (v && out_va != 0u && mem.in_bounds(out_va, 4u)) {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        mem.w32(out_va, static_cast<uint32_t>(v->pan_mb));
    }
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IDirectSoundBuffer::GetFrequency(this, pdwFrequency) -> 8 bytes
void dsb_get_frequency(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va = ctx.arg32(mem, 0);
    const uint32_t out_va = ctx.arg32(mem, 1);
    auto v = find_voice(obj_va);
    if (v && out_va != 0u && mem.in_bounds(out_va, 4u)) {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        mem.w32(out_va, v->sample_rate);
    }
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IDirectSoundBuffer::GetCurrentPosition(this, pdwPlay, pdwWrite) -> 12 bytes
void dsb_get_current_position(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va   = ctx.arg32(mem, 0);
    const uint32_t play_va  = ctx.arg32(mem, 1);
    const uint32_t write_va = ctx.arg32(mem, 2);
    auto v = find_voice(obj_va);
    uint32_t pos = 0u;
    if (v && v->buffer_bytes > 0u) {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        const uint32_t block_align = std::max<uint32_t>(1u, v->channels * (v->bits_per_sample / 8u));
        pos = (static_cast<uint32_t>(v->frame_cursor) * block_align) % v->buffer_bytes;
    }
    if (play_va)  mem.w32(play_va, pos);
    if (write_va) mem.w32(write_va, pos);
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 12u);
}

// IDirectSoundBuffer::GetStatus(this, pdwStatus) -> 8 bytes
void dsb_get_status(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va = ctx.arg32(mem, 0);
    const uint32_t out_va = ctx.arg32(mem, 1);
    auto v = find_voice(obj_va);
    uint32_t status = 0u;
    if (v) {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        if (v->playing) {
            status |= kDSBSTATUS_PLAYING;
            if (v->looping) status |= kDSBSTATUS_LOOPING;
        }
    }
    if (out_va) mem.w32(out_va, status);
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IDirectSoundBuffer::Lock(this, dwOffset, dwBytes, pp1, pcb1, pp2, pcb2, dwFlags) -> 32 bytes
void dsb_lock(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va   = ctx.arg32(mem, 0);
    uint32_t offset         = ctx.arg32(mem, 1);
    uint32_t bytes          = ctx.arg32(mem, 2);
    const uint32_t pp1_va   = ctx.arg32(mem, 3);
    const uint32_t pcb1_va  = ctx.arg32(mem, 4);
    const uint32_t pp2_va   = ctx.arg32(mem, 5);
    const uint32_t pcb2_va  = ctx.arg32(mem, 6);
    const uint32_t flags    = ctx.arg32(mem, 7);

    auto v = find_voice(obj_va);
    if (!v || v->guest_buf_va == 0u || v->buffer_bytes == 0u) {
        ctx.eax = kDSERR_INVALID;
        ctx.ret_stdcall(mem, 32u);
        return;
    }

    if (flags & kDSBLOCK_FROMWRITE) {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        const uint32_t block_align = std::max<uint32_t>(1u, v->channels * (v->bits_per_sample / 8u));
        offset = (static_cast<uint32_t>(v->frame_cursor) * block_align) % v->buffer_bytes;
    }
    if (flags & kDSBLOCK_ENTIRE) {
        offset = 0u;
        bytes = v->buffer_bytes;
    }
    offset %= v->buffer_bytes;
    bytes = std::min(bytes, v->buffer_bytes);

    const uint32_t first_len  = std::min(bytes, v->buffer_bytes - offset);
    const uint32_t second_len = bytes - first_len;

    if (pp1_va)  mem.w32(pp1_va, v->guest_buf_va + offset);
    if (pcb1_va) mem.w32(pcb1_va, first_len);
    if (pp2_va)  mem.w32(pp2_va, (second_len > 0u) ? v->guest_buf_va : 0u);
    if (pcb2_va) mem.w32(pcb2_va, second_len);

    {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        v->last_lock_off = offset;
        v->last_lock_len = bytes;
    }

    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 32u);
}

// IDirectSoundBuffer::Unlock(this, p1, cb1, p2, cb2) -> 20 bytes
void dsb_unlock(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va = ctx.arg32(mem, 0);
    const uint32_t p1_va  = ctx.arg32(mem, 1);
    const uint32_t cb1    = ctx.arg32(mem, 2);
    const uint32_t p2_va  = ctx.arg32(mem, 3);
    const uint32_t cb2    = ctx.arg32(mem, 4);

    auto v = find_voice(obj_va);
    if (v && v->guest_buf_va != 0u) {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        auto sync_span = [&](uint32_t va, uint32_t len) {
            if (va < v->guest_buf_va || len == 0u) return;
            const uint32_t off = va - v->guest_buf_va;
            if (off < v->pcm.size()) {
                const uint32_t copy_len = std::min<uint32_t>(len, static_cast<uint32_t>(v->pcm.size()) - off);
                mem.read_bytes(va, v->pcm.data() + off, copy_len);
            }
        };
        sync_span(p1_va, cb1);
        sync_span(p2_va, cb2);
    }

    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 20u);
}

// IDirectSoundBuffer::Play(this, dwReserved1, dwPriority, dwFlags) -> 16 bytes
void dsb_play(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va = ctx.arg32(mem, 0);
    const uint32_t flags  = ctx.arg32(mem, 3);
    const bool is_looping = (flags & kDSBPLAY_LOOPING) != 0u;
    auto v = find_voice(obj_va);
    if (v) {
        const bool track_rollback = g_audio.rollback_tracking.load(std::memory_order_acquire) &&
                                    !v->is_primary && !is_looping;
        const int sfx_slot = track_rollback ? find_triggered_sfx_slot(mem, obj_va) : -1;

        std::lock_guard<std::mutex> lock(g_audio.mutex);
        if (g_audio.rollback_mute.load(std::memory_order_acquire)) {
            if (sfx_slot >= 0) {
                g_audio.resim_sfx_accum[static_cast<size_t>(sfx_slot)] = 1u;
            }
            ctx.eax = kDS_OK;
            ctx.ret_stdcall(mem, 16u);
            return;
        }
        if (track_rollback && sfx_slot >= 0) {
            const size_t idx = static_cast<size_t>(sfx_slot);
            if (g_audio.in_rollback_catchup.load(std::memory_order_acquire)) {
                const uint32_t target = g_audio.catchup_rollback_target.load(std::memory_order_acquire);
                if (g_audio.sfx_has_played[idx] != 0u && g_audio.sfx_last_played_frame[idx] >= target) {
                    ctx.eax = kDS_OK;
                    ctx.ret_stdcall(mem, 16u);
                    return;
                }
            }
            g_audio.sfx_has_played[idx] = 1u;
            g_audio.sfx_last_played_frame[idx] = g_audio.rollback_frame.load(std::memory_order_acquire);
        }

        if (!v->playing) {
            const uint32_t block_align = std::max<uint32_t>(1u, v->channels * (v->bits_per_sample / 8u));
            v->prev_byte_pos = (v->buffer_bytes > 0u)
                ? ((static_cast<uint32_t>(v->frame_cursor) * block_align) % v->buffer_bytes)
                : 0u;
        }
        v->playing = true;
        v->looping = is_looping;
    }
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 16u);
}

// IDirectSoundBuffer::Stop(this) -> 4 bytes
void dsb_stop(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va = ctx.arg32(mem, 0);
    auto v = find_voice(obj_va);
    if (v) {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        v->playing = false;
    }
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 4u);
}

// IDirectSoundBuffer::SetCurrentPosition(this, dwNewPosition) -> 8 bytes
void dsb_set_current_position(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va  = ctx.arg32(mem, 0);
    const uint32_t new_pos = ctx.arg32(mem, 1);
    auto v = find_voice(obj_va);
    if (v) {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        const uint32_t block_align = std::max<uint32_t>(1u, v->channels * (v->bits_per_sample / 8u));
        v->frame_cursor = static_cast<double>((new_pos % std::max<uint32_t>(1u, v->buffer_bytes)) / block_align);
        v->prev_byte_pos = new_pos;
    }
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IDirectSoundBuffer::SetFormat(this, pcfxFormat) -> 8 bytes
void dsb_set_format(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va = ctx.arg32(mem, 0);
    const uint32_t wfx_va = ctx.arg32(mem, 1);
    auto v = find_voice(obj_va);
    if (v && wfx_va != 0u) {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        const uint16_t ch   = mem.r16(wfx_va + 2u);
        const uint32_t rate = mem.r32(wfx_va + 4u);
        const uint16_t bits = mem.r16(wfx_va + 14u);
        if (ch != 0u) v->channels = ch;
        if (rate >= 100u && rate <= 192000u) v->sample_rate = rate;
        if (bits == 8u || bits == 16u) v->bits_per_sample = bits;
    }
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IDirectSoundBuffer::SetVolume(this, lVolume) -> 8 bytes
void dsb_set_volume(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va = ctx.arg32(mem, 0);
    const int32_t  vol_mb = static_cast<int32_t>(ctx.arg32(mem, 1));
    auto v = find_voice(obj_va);
    if (v) {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        v->volume_mb = std::clamp(vol_mb, -10000, 0);
    }
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IDirectSoundBuffer::SetPan(this, lPan) -> 8 bytes
void dsb_set_pan(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va = ctx.arg32(mem, 0);
    const int32_t  pan_mb = static_cast<int32_t>(ctx.arg32(mem, 1));
    auto v = find_voice(obj_va);
    if (v) {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        v->pan_mb = std::clamp(pan_mb, -10000, 10000);
    }
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IDirectSoundBuffer::SetFrequency(this, dwFrequency) -> 8 bytes
void dsb_set_frequency(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va = ctx.arg32(mem, 0);
    const uint32_t freq   = ctx.arg32(mem, 1);
    auto v = find_voice(obj_va);
    if (v && freq >= 100u && freq <= 192000u) {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        v->sample_rate = freq;
    }
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IDirectSoundNotify::SetNotificationPositions(this, dwPositionNotifies, pcPositionNotifies) -> 12 bytes
void dsn_set_notification_positions(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t obj_va   = ctx.arg32(mem, 0);
    const uint32_t count    = ctx.arg32(mem, 1);
    const uint32_t arr_va   = ctx.arg32(mem, 2);
    auto v = find_voice(obj_va);
    if (v) {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        v->notifies.clear();
        if (arr_va != 0u && count <= 64u) {
            for (uint32_t i = 0; i < count; ++i) {
                NotifyPoint np;
                np.offset_bytes = mem.r32(arr_va + i * 8u + 0u);
                np.event_handle = mem.r32(arr_va + i * 8u + 4u);
                v->notifies.push_back(np);
            }
        }
    }
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 12u);
}

uint32_t build_vtable(GuestMemory& mem, const RecompFn* slots, size_t count) {
    const uint32_t vt = mem.alloc_thunk_block(static_cast<uint32_t>(count * 4u), 4u);
    for (size_t i = 0; i < count; ++i) {
        mem.w32(vt + static_cast<uint32_t>(i * 4u), alloc_com_method_thunk(slots[i]));
    }
    return vt;
}

void ensure_dsound_objects(GuestMemory& mem) {
    if (g_audio.ds8_obj_va != 0u && mem.r32(g_audio.ds8_obj_va) != 0u) {
        return;
    }

    // IDirectSound8: 11 slots (+0x00 .. +0x28)
    RecompFn ds8_slots[11] = {
        &ds_query_interface,
        &ds_unk_addref,
        &ds_unk_release,
        &ds8_create_sound_buffer,    // +0x0C
        &ds8_get_caps,               // +0x10 GetCaps
        &ds8_duplicate_sound_buffer, // +0x14
        &ds_ret_ok<12u>,             // +0x18 SetCooperativeLevel
        &ds_ret_ok<4u>,              // +0x1C Compact
        &ds_ret_ok<8u>,              // +0x20 GetSpeakerConfig
        &ds_ret_ok<8u>,              // +0x24 SetSpeakerConfig
        &ds_ret_ok<8u>,              // +0x28 Initialize
    };
    g_audio.ds8_vtable = build_vtable(mem, ds8_slots, 11);

    // IDirectSoundBuffer: 21 slots (+0x00 .. +0x50)
    RecompFn buf_slots[21] = {
        &ds_query_interface,
        &ds_unk_addref,
        &ds_unk_release,
        &dsb_get_caps,              // +0x0C GetCaps
        &dsb_get_current_position,  // +0x10
        &dsb_get_format,            // +0x14 GetFormat
        &dsb_get_volume,            // +0x18 GetVolume
        &dsb_get_pan,               // +0x1C GetPan
        &dsb_get_frequency,         // +0x20 GetFrequency
        &dsb_get_status,            // +0x24
        &ds_ret_ok<12u>,            // +0x28 Initialize
        &dsb_lock,                  // +0x2C
        &dsb_play,                  // +0x30
        &dsb_set_current_position,  // +0x34
        &dsb_set_format,            // +0x38
        &dsb_set_volume,            // +0x3C
        &dsb_set_pan,               // +0x40
        &dsb_set_frequency,         // +0x44
        &dsb_stop,                  // +0x48
        &dsb_unlock,                // +0x4C
        &ds_ret_ok<4u>,             // +0x50 Restore
    };
    g_audio.buf_vtable = build_vtable(mem, buf_slots, 21);

    // IDirectSoundNotify: 4 slots
    RecompFn notify_slots[4] = {
        &ds_query_interface,
        &ds_unk_addref,
        &ds_unk_release,
        &dsn_set_notification_positions, // +0x0C
    };
    g_audio.notify_vtable = build_vtable(mem, notify_slots, 4);

    g_audio.ds8_obj_va = mem.alloc_thunk_block(16u, 8u);
    mem.w32(g_audio.ds8_obj_va, g_audio.ds8_vtable);
}

} // namespace

void audio_init() {
    if (g_audio.initialized.exchange(true)) return;

#if defined(__APPLE__)
#if TARGET_OS_IPHONE
    @autoreleasepool {
        AVAudioSession* session = [AVAudioSession sharedInstance];
        NSError* err = nil;
        if (![session setCategory:AVAudioSessionCategoryPlayback
                      withOptions:AVAudioSessionCategoryOptionMixWithOthers
                            error:&err]) {
            hle_win32_log("AVAudioSession setCategory failed: %s",
                          err ? err.localizedDescription.UTF8String : "unknown");
        }
        [session setPreferredSampleRate:static_cast<double>(kOutputSampleRate) error:nil];
        [session setPreferredIOBufferDuration:0.0116 error:nil];
        err = nil;
        if (![session setActive:YES error:&err]) {
            hle_win32_log("AVAudioSession setActive failed: %s",
                          err ? err.localizedDescription.UTF8String : "unknown");
        }
    }
#endif

    AudioStreamBasicDescription fmt{};
    fmt.mSampleRate       = static_cast<Float64>(kOutputSampleRate);
    fmt.mFormatID         = kAudioFormatLinearPCM;
    fmt.mFormatFlags      = kLinearPCMFormatFlagIsSignedInteger | kLinearPCMFormatFlagIsPacked;
    fmt.mBitsPerChannel   = 16u;
    fmt.mChannelsPerFrame = kOutputChannels;
    fmt.mBytesPerFrame    = kOutputChannels * sizeof(int16_t);
    fmt.mFramesPerPacket  = 1u;
    fmt.mBytesPerPacket   = fmt.mBytesPerFrame;

    OSStatus st = AudioQueueNewOutput(&fmt, &audio_queue_callback, nullptr, nullptr, nullptr, 0, &g_audio.queue);
    if (st == noErr && g_audio.queue != nullptr) {
        const UInt32 byte_sz = kBufferFrames * fmt.mBytesPerFrame;
        for (uint32_t i = 0; i < kNumAudioBuffers; ++i) {
            if (AudioQueueAllocateBuffer(g_audio.queue, byte_sz, &g_audio.aq_buffers[i]) == noErr) {
                g_audio.aq_buffers[i]->mAudioDataByteSize = byte_sz;
                std::memset(g_audio.aq_buffers[i]->mAudioData, 0, byte_sz);
                AudioQueueEnqueueBuffer(g_audio.queue, g_audio.aq_buffers[i], 0, nullptr);
            }
        }
        const OSStatus start_st = AudioQueueStart(g_audio.queue, nullptr);
        if (start_st != noErr) {
            hle_win32_log("AudioQueueStart failed status=%d", static_cast<int>(start_st));
        }
    } else {
        hle_win32_log("AudioQueueNewOutput failed status=%d", static_cast<int>(st));
    }
#endif
}

void audio_shutdown() {
    if (!g_audio.initialized.exchange(false)) return;

#if defined(__APPLE__)
    if (g_audio.queue != nullptr) {
        AudioQueueStop(g_audio.queue, true);
        AudioQueueDispose(g_audio.queue, true);
        g_audio.queue = nullptr;
    }
    for (uint32_t i = 0; i < kNumAudioBuffers; ++i) {
        g_audio.aq_buffers[i] = nullptr;
    }
#endif

    std::lock_guard<std::mutex> lock(g_audio.mutex);
    g_audio.voices_by_obj.clear();
    g_audio.active_list.clear();
    g_audio.ds8_vtable    = 0u;
    g_audio.buf_vtable    = 0u;
    g_audio.notify_vtable = 0u;
    g_audio.ds8_obj_va    = 0u;
    g_audio.health_tick   = 0u;
    g_audio.rollback_mute.store(false, std::memory_order_relaxed);
    g_audio.rollback_tracking.store(false, std::memory_order_relaxed);
    g_audio.rollback_frame.store(0u, std::memory_order_relaxed);
    g_audio.in_rollback_catchup.store(false, std::memory_order_relaxed);
    g_audio.catchup_rollback_target.store(0u, std::memory_order_relaxed);
    g_audio.sfx_last_played_frame.fill(0u);
    g_audio.sfx_has_played.fill(0u);
    g_audio.resim_sfx_accum.fill(0u);
}

void audio_set_muted(bool muted) {
    g_audio.muted.store(muted, std::memory_order_relaxed);
}

void audio_set_rollback_mute(bool muted) {
    g_audio.rollback_mute.store(muted, std::memory_order_release);
}

bool audio_is_rollback_muted() {
    return g_audio.rollback_mute.load(std::memory_order_acquire);
}

void audio_rollback_set_tracking(bool active, uint32_t current_frame) {
    g_audio.rollback_frame.store(current_frame, std::memory_order_release);
    if (!active) {
        g_audio.rollback_mute.store(false, std::memory_order_release);
        g_audio.rollback_tracking.store(false, std::memory_order_release);
        g_audio.in_rollback_catchup.store(false, std::memory_order_release);
        g_audio.catchup_rollback_target.store(0u, std::memory_order_release);
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        g_audio.sfx_last_played_frame.fill(0u);
        g_audio.sfx_has_played.fill(0u);
        g_audio.resim_sfx_accum.fill(0u);
    } else {
        g_audio.rollback_tracking.store(true, std::memory_order_release);
    }
}

void audio_rollback_begin_catchup(uint32_t rollback_target_frame) {
    {
        std::lock_guard<std::mutex> lock(g_audio.mutex);
        g_audio.resim_sfx_accum.fill(0u);
    }
    g_audio.catchup_rollback_target.store(rollback_target_frame, std::memory_order_release);
    g_audio.in_rollback_catchup.store(true, std::memory_order_release);
    g_audio.rollback_mute.store(true, std::memory_order_release);
}

void audio_rollback_prepare_live_catchup(GuestMemory& mem) {
    g_audio.rollback_mute.store(false, std::memory_order_release);
    std::lock_guard<std::mutex> lock(g_audio.mutex);
    const uint32_t target = g_audio.catchup_rollback_target.load(std::memory_order_acquire);
    if (mem.in_bounds(AudioState::kSfxTableVa, AudioState::kSfxSlotCount)) {
        for (size_t i = 0; i < AudioState::kSfxSlotCount; ++i) {
            if (g_audio.resim_sfx_accum[i] == 0u) continue;
            if (g_audio.sfx_has_played[i] != 0u && g_audio.sfx_last_played_frame[i] >= target) {
                continue;
            }
            mem.w8(AudioState::kSfxTableVa + static_cast<uint32_t>(i), 1u);
        }
    }
    g_audio.resim_sfx_accum.fill(0u);
}

void audio_rollback_end_catchup() {
    g_audio.rollback_mute.store(false, std::memory_order_release);
    g_audio.in_rollback_catchup.store(false, std::memory_order_release);
    std::lock_guard<std::mutex> lock(g_audio.mutex);
    g_audio.resim_sfx_accum.fill(0u);
}

void audio_update_streams() {
    // AudioQueue callback handles live mixing and DirectSoundNotify event dispatch asynchronously.
    // Periodically verify AudioQueue stayed running after iOS interruptions / route changes.
#if defined(__APPLE__) && TARGET_OS_IPHONE
    if (!g_audio.initialized.load(std::memory_order_relaxed) || g_audio.queue == nullptr) {
        return;
    }
    if ((++g_audio.health_tick % 60u) != 0u) {
        return;
    }
    UInt32 is_running = 0u;
    UInt32 prop_size = sizeof(is_running);
    if (AudioQueueGetProperty(g_audio.queue, kAudioQueueProperty_IsRunning, &is_running, &prop_size) == noErr &&
        is_running == 0u) {
        @autoreleasepool {
            AVAudioSession* session = [AVAudioSession sharedInstance];
            [session setActive:YES error:nil];
        }
        AudioQueueStart(g_audio.queue, nullptr);
    }
#endif
}

// DirectSoundCreate8(lpcGuidDevice, ppDS8, pUnkOuter) -> 12 bytes
void hle_direct_sound_create8(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pp_ds8_va = ctx.arg32(mem, 1);
    if (pp_ds8_va == 0u) {
        ctx.eax = kDSERR_INVALID;
        ctx.ret_stdcall(mem, 12u);
        return;
    }
    audio_init();
    ensure_dsound_objects(mem);
    mem.w32(pp_ds8_va, g_audio.ds8_obj_va);
    ctx.eax = kDS_OK;
    ctx.ret_stdcall(mem, 12u);
}

} // namespace mbaa_recomp
