#include "mbaa_recomp/hle_win32.h"
#include "mbaa_recomp/dispatch.h"
#include "mbaa_recomp/mpeg1_decoder.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <mutex>
#include <string>

namespace mbaa_recomp {

namespace {

// DirectShow / COM HRESULTs & filter states
constexpr uint32_t kS_OK                = 0x00000000u;
constexpr uint32_t kS_FALSE             = 0x00000001u;
constexpr uint32_t kE_NOINTERFACE       = 0x80004002u;
constexpr uint32_t kE_POINTER           = 0x80004003u;
constexpr uint32_t kE_FAIL              = 0x80004005u;
constexpr uint32_t kE_OUTOFMEMORY       = 0x8007000Eu;
constexpr uint32_t kVFW_E_NOT_CONNECTED = 0x80040209u;
constexpr uint32_t kVFW_E_NOT_FOUND     = 0x80040216u;
constexpr uint32_t kVFW_E_WRONG_STATE   = 0x80040227u;
constexpr uint32_t kE_ABORT             = 0x80004004u;

constexpr uint32_t kEC_COMPLETE         = 0x00000001u;

constexpr uint32_t kStateStopped        = 0u;
constexpr uint32_t kStatePaused         = 1u;
constexpr uint32_t kStateRunning        = 2u;

// IMediaSeeking positioning flags & capabilities
constexpr uint32_t kSeekingNoPositioning       = 0x00u;
constexpr uint32_t kSeekingAbsolutePositioning = 0x01u;
constexpr uint32_t kSeekingRelativePositioning = 0x02u;
constexpr uint32_t kSeekingPositioningMask     = 0x03u;
constexpr uint32_t kSeekingReturnTime          = 0x08u;
constexpr uint32_t kSeekingDefaultCaps         = 0x3Fu;

// Little-endian GUID byte sequences verified from MBAA.exe (0x0051D710..0x0051D830):
// CLSID_FilterGraph (0x0051D7F0): {E436EBB3-524F-11CE-9F53-0020AF0BA770}
constexpr uint8_t kClsidFilterGraph[16] = {
    0xB3, 0xEB, 0x36, 0xE4, 0x4F, 0x52, 0xCE, 0x11,
    0x9F, 0x53, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70
};
// CLSID_SampleGrabber (0x0051D760): {C1F400A0-3F08-11D3-9F0B-006008039E37}
constexpr uint8_t kClsidSampleGrabber[16] = {
    0xA0, 0x00, 0xF4, 0xC1, 0x08, 0x3F, 0xD3, 0x11,
    0x9F, 0x0B, 0x00, 0x60, 0x08, 0x03, 0x9E, 0x37
};

// IID_IUnknown: {00000000-0000-0000-C000-000000000046}
constexpr uint8_t kIidIUnknown[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46
};
// IID_IGraphBuilder (0x0051D720): {56A868A9-0AD4-11CE-B03A-0020AF0BA770}
constexpr uint8_t kIidIGraphBuilder[16] = {
    0xA9, 0x68, 0xA8, 0x56, 0xD4, 0x0A, 0xCE, 0x11,
    0xB0, 0x3A, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70
};
// IID_IFilterGraph (0x0051D750): {56A8689F-0AD4-11CE-B03A-0020AF0BA770}
constexpr uint8_t kIidIFilterGraph[16] = {
    0x9F, 0x68, 0xA8, 0x56, 0xD4, 0x0A, 0xCE, 0x11,
    0xB0, 0x3A, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70
};
// IID_IBaseFilter (0x0051D740): {56A86895-0AD4-11CE-B03A-0020AF0BA770}
constexpr uint8_t kIidIBaseFilter[16] = {
    0x95, 0x68, 0xA8, 0x56, 0xD4, 0x0A, 0xCE, 0x11,
    0xB0, 0x3A, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70
};
// IID_ISampleGrabber (0x0051D770): {6B652FFF-11FE-4FCE-92AD-0266B5D7C78F}
constexpr uint8_t kIidISampleGrabber[16] = {
    0xFF, 0x2F, 0x65, 0x6B, 0xFE, 0x11, 0xCE, 0x4F,
    0x92, 0xAD, 0x02, 0x66, 0xB5, 0xD7, 0xC7, 0x8F
};
// IID_IMediaControl (0x0051D7C0): {56A868B1-0AD4-11CE-B03A-0020AF0BA770}
constexpr uint8_t kIidIMediaControl[16] = {
    0xB1, 0x68, 0xA8, 0x56, 0xD4, 0x0A, 0xCE, 0x11,
    0xB0, 0x3A, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70
};
// IID_IMediaEventEx (0x0051D7B0): {56A868C0-0AD4-11CE-B03A-0020AF0BA770}
constexpr uint8_t kIidIMediaEventEx[16] = {
    0xC0, 0x68, 0xA8, 0x56, 0xD4, 0x0A, 0xCE, 0x11,
    0xB0, 0x3A, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70
};
// IID_IMediaEvent: {56A868B6-0AD4-11CE-B03A-0020AF0BA770}
constexpr uint8_t kIidIMediaEvent[16] = {
    0xB6, 0x68, 0xA8, 0x56, 0xD4, 0x0A, 0xCE, 0x11,
    0xB0, 0x3A, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70
};
// IID_IVideoWindow (0x0051D790): {56A868B4-0AD4-11CE-B03A-0020AF0BA770}
constexpr uint8_t kIidIVideoWindow[16] = {
    0xB4, 0x68, 0xA8, 0x56, 0xD4, 0x0A, 0xCE, 0x11,
    0xB0, 0x3A, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70
};
// IID_IMediaSeeking (0x0051D730): {36B73880-C2C8-11CF-8B46-00805F6CEF60}
constexpr uint8_t kIidIMediaSeeking[16] = {
    0x80, 0x38, 0xB7, 0x36, 0xC8, 0xC2, 0xCF, 0x11,
    0x8B, 0x46, 0x00, 0x80, 0x5F, 0x6C, 0xEF, 0x60
};
// IID_IBasicVideo (0x0051D780): {56A868B5-0AD4-11CE-B03A-0020AF0BA770}
constexpr uint8_t kIidIBasicVideo[16] = {
    0xB5, 0x68, 0xA8, 0x56, 0xD4, 0x0A, 0xCE, 0x11,
    0xB0, 0x3A, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70
};
// IID_IBasicAudio (0x0051D7A0): {56A868B3-0AD4-11CE-B03A-0020AF0BA770}
constexpr uint8_t kIidIBasicAudio[16] = {
    0xB3, 0x68, 0xA8, 0x56, 0xD4, 0x0A, 0xCE, 0x11,
    0xB0, 0x3A, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70
};
// IID_IVMRWindowlessControl9 (0x0051D710): {8F537D09-F85E-4414-B23B-502E54C79927}
constexpr uint8_t kIidIVMRWindowlessControl9[16] = {
    0x09, 0x7D, 0x53, 0x8F, 0x5E, 0xF8, 0x14, 0x44,
    0xB2, 0x3B, 0x50, 0x2E, 0x54, 0xC7, 0x99, 0x27
};

// DirectShow Media Type / Format / Time Format GUIDs (0x0051D7D0..0x0051D830):
// TIME_FORMAT_MEDIA_TIME (0x0051D7D0): {7B785574-8C82-11CF-BC0C-00AA00AC74F6}
constexpr uint8_t kGuidTimeFormatMediaTime[16] = {
    0x74, 0x55, 0x78, 0x7B, 0x82, 0x8C, 0xCF, 0x11,
    0xBC, 0x0C, 0x00, 0xAA, 0x00, 0xAC, 0x74, 0xF6
};
// FORMAT_VideoInfo (0x0051D7E0): {05589F80-C356-11CE-BF01-00AA0055595A}
constexpr uint8_t kGuidFormatVideoInfo[16] = {
    0x80, 0x9F, 0x58, 0x05, 0x56, 0xC3, 0xCE, 0x11,
    0xBF, 0x01, 0x00, 0xAA, 0x00, 0x55, 0x59, 0x5A
};
// MEDIASUBTYPE_RGB32 (0x0051D810): {E436EB7E-524F-11CE-9F53-0020AF0BA770}
constexpr uint8_t kGuidSubtypeRGB32[16] = {
    0x7E, 0xEB, 0x36, 0xE4, 0x4F, 0x52, 0xCE, 0x11,
    0x9F, 0x53, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70
};
// MEDIASUBTYPE_RGB24 (0x0051D820): {E436EB7D-524F-11CE-9F53-0020AF0BA770}
constexpr uint8_t kGuidSubtypeRGB24[16] = {
    0x7D, 0xEB, 0x36, 0xE4, 0x4F, 0x52, 0xCE, 0x11,
    0x9F, 0x53, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70
};
// MEDIATYPE_Video (0x0051D830): {73646976-0000-0010-8000-00AA00389B71}
constexpr uint8_t kGuidMediaTypeVideo[16] = {
    0x76, 0x69, 0x64, 0x73, 0x00, 0x00, 0x10, 0x00,
    0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71
};

bool guid_eq(const uint8_t* a, const uint8_t* b) noexcept {
    return std::memcmp(a, b, 16) == 0;
}

std::string utf16_to_utf8(const std::u16string& ws) {
    std::string out;
    out.reserve(ws.size());
    for (size_t i = 0; i < ws.size(); ++i) {
        uint32_t cp = ws[i];
        if (cp >= 0xD800u && cp <= 0xDBFFu && i + 1u < ws.size()) {
            const uint32_t lo = ws[i + 1u];
            if (lo >= 0xDC00u && lo <= 0xDFFFu) {
                cp = 0x10000u + (((cp - 0xD800u) << 10) | (lo - 0xDC00u));
                ++i;
            }
        }
        if (cp < 0x80u) {
            out.push_back(static_cast<char>(cp));
        } else if (cp < 0x800u) {
            out.push_back(static_cast<char>(0xC0u | (cp >> 6)));
            out.push_back(static_cast<char>(0x80u | (cp & 0x3Fu)));
        } else if (cp < 0x10000u) {
            out.push_back(static_cast<char>(0xE0u | (cp >> 12)));
            out.push_back(static_cast<char>(0x80u | ((cp >> 6) & 0x3Fu)));
            out.push_back(static_cast<char>(0x80u | (cp & 0x3Fu)));
        } else {
            out.push_back(static_cast<char>(0xF0u | (cp >> 18)));
            out.push_back(static_cast<char>(0x80u | ((cp >> 12) & 0x3Fu)));
            out.push_back(static_cast<char>(0x80u | ((cp >> 6) & 0x3Fu)));
            out.push_back(static_cast<char>(0x80u | (cp & 0x3Fu)));
        }
    }
    return out;
}

struct DShowState {
    std::mutex mtx;

    uint32_t graph_vtable       = 0;
    uint32_t control_vtable     = 0;
    uint32_t event_vtable       = 0;
    uint32_t window_vtable      = 0;
    uint32_t grabber_vtable     = 0;
    uint32_t seeking_vtable     = 0;
    uint32_t basic_video_vtable = 0;
    uint32_t basic_audio_vtable = 0;

    uint32_t graph_obj_va       = 0;
    uint32_t control_obj_va     = 0;
    uint32_t event_obj_va       = 0;
    uint32_t window_obj_va      = 0;
    uint32_t grabber_obj_va     = 0;
    uint32_t seeking_obj_va     = 0;
    uint32_t basic_video_obj_va = 0;
    uint32_t basic_audio_obj_va = 0;

    uint32_t active_refs        = 0;
    uint32_t filter_state       = kStateStopped;
    bool     connected          = false;
    bool     requested_rgb32    = true;
    bool     buffer_samples     = false;
    bool     eof_notified       = false;

    int64_t  duration_100ns     = 0;
    int64_t  stop_pos_100ns     = 0;
    int64_t  pos_base_100ns     = 0;
    double   rate               = 1.0;
    int32_t  volume             = 0;
    int32_t  balance            = 0;
    std::chrono::steady_clock::time_point run_anchor_time{};

    Mpeg1Decoder decoder;
    DShowVideoHookFn hook_fn = nullptr;

    void reset_session_locked() {
        decoder.close();
        filter_state    = kStateStopped;
        connected       = false;
        requested_rgb32 = true;
        buffer_samples  = false;
        eof_notified    = false;
        duration_100ns  = 0;
        stop_pos_100ns  = 0;
        pos_base_100ns  = 0;
        rate            = 1.0;
        volume          = 0;
        balance         = 0;
        run_anchor_time = std::chrono::steady_clock::now();
    }

    [[nodiscard]] int64_t current_position_locked() const noexcept {
        if (!connected || duration_100ns <= 0) {
            return 0;
        }
        int64_t cur = pos_base_100ns;
        if (filter_state == kStateRunning) {
            const auto now = std::chrono::steady_clock::now();
            const auto ns  = std::chrono::duration_cast<std::chrono::nanoseconds>(now - run_anchor_time).count();
            if (ns > 0) {
                const double scaled_100ns = (static_cast<double>(ns) * rate) / 100.0;
                cur += static_cast<int64_t>(scaled_100ns);
            }
        }
        const int64_t limit = (stop_pos_100ns > 0 && stop_pos_100ns < duration_100ns)
            ? stop_pos_100ns
            : duration_100ns;
        return std::clamp<int64_t>(cur, 0, limit);
    }
};

DShowState g_dshow;

// Shared COM AddRef/Release/ReturnOK helpers (stdcall)
void com_addref(CpuContext& ctx, GuestMemory& mem) {
    uint32_t refs = 1u;
    {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        refs = ++g_dshow.active_refs;
    }
    ctx.eax = refs;
    ctx.ret_stdcall(mem, 4u);
}

void com_release(CpuContext& ctx, GuestMemory& mem) {
    uint32_t refs = 0u;
    {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        if (g_dshow.active_refs > 0u) {
            --g_dshow.active_refs;
        }
        refs = g_dshow.active_refs;
        if (refs == 0u && g_dshow.connected) {
            g_dshow.reset_session_locked();
        }
    }
    ctx.eax = refs;
    ctx.ret_stdcall(mem, 4u);
}

template <uint32_t ArgBytes, uint32_t RetVal = kS_OK>
void com_ret(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = RetVal;
    ctx.ret_stdcall(mem, ArgBytes);
}

// IUnknown::QueryInterface(this, riid, ppvObject) -> 3 args = 12 bytes
void dshow_query_interface(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t this_va = ctx.arg32(mem, 0);
    const uint32_t riid_va = ctx.arg32(mem, 1);
    const uint32_t ppv_va  = ctx.arg32(mem, 2);
    if (ppv_va == 0u || !mem.in_bounds(ppv_va, 4u) || riid_va == 0u || !mem.in_bounds(riid_va, 16u)) {
        ctx.eax = kE_POINTER;
        ctx.ret_stdcall(mem, 12u);
        return;
    }

    uint8_t iid[16] = {};
    mem.read_bytes(riid_va, iid, 16);

    std::lock_guard<std::mutex> lock(g_dshow.mtx);
    uint32_t target_obj = 0u;
    if (guid_eq(iid, kIidIUnknown)) {
        target_obj = (this_va != 0u) ? this_va : g_dshow.graph_obj_va;
    } else if (guid_eq(iid, kIidIGraphBuilder) ||
               guid_eq(iid, kIidIFilterGraph) ||
               guid_eq(iid, kIidIBaseFilter)) {
        target_obj = g_dshow.graph_obj_va;
    } else if (guid_eq(iid, kIidIMediaControl)) {
        target_obj = g_dshow.control_obj_va;
    } else if (guid_eq(iid, kIidIMediaEventEx) || guid_eq(iid, kIidIMediaEvent)) {
        target_obj = g_dshow.event_obj_va;
    } else if (guid_eq(iid, kIidIVideoWindow)) {
        target_obj = g_dshow.window_obj_va;
    } else if (guid_eq(iid, kIidISampleGrabber)) {
        target_obj = g_dshow.grabber_obj_va;
    } else if (guid_eq(iid, kIidIMediaSeeking)) {
        target_obj = g_dshow.seeking_obj_va;
    } else if (guid_eq(iid, kIidIBasicVideo)) {
        target_obj = g_dshow.basic_video_obj_va;
    } else if (guid_eq(iid, kIidIBasicAudio)) {
        target_obj = g_dshow.basic_audio_obj_va;
    } else if (guid_eq(iid, kIidIVMRWindowlessControl9)) {
        mem.w32(ppv_va, 0u);
        ctx.eax = kE_NOINTERFACE;
        ctx.ret_stdcall(mem, 12u);
        return;
    } else {
        mem.w32(ppv_va, 0u);
        hle_win32_log("[hle_dshow] QueryInterface E_NOINTERFACE "
                      "{%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
                      iid[3], iid[2], iid[1], iid[0],
                      iid[5], iid[4], iid[7], iid[6],
                      iid[8], iid[9],
                      iid[10], iid[11], iid[12], iid[13], iid[14], iid[15]);
        ctx.eax = kE_NOINTERFACE;
        ctx.ret_stdcall(mem, 12u);
        return;
    }

    mem.w32(ppv_va, target_obj);
    ++g_dshow.active_refs;
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

// IGraphBuilder::RenderFile(this, lpwstrFile, lpwstrPlayList) -> 12 bytes
void dshow_render_file(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t wpath_va = ctx.arg32(mem, 1);
    if (wpath_va == 0u) {
        ctx.eax = kE_POINTER;
        ctx.ret_stdcall(mem, 12u);
        return;
    }

    const std::u16string wpath = mem.read_wstring_utf16(wpath_va);
    const std::string narrow = utf16_to_utf8(wpath);
    const std::string resolved = hle_win32_resolve_path(narrow, false);

    uint32_t hr = kVFW_E_NOT_FOUND;
    DShowVideoHookFn hook = nullptr;
    {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        const bool keep_rgb32 = g_dshow.requested_rgb32;
        const bool keep_buf   = g_dshow.buffer_samples;
        g_dshow.reset_session_locked();
        g_dshow.requested_rgb32 = keep_rgb32;
        g_dshow.buffer_samples  = keep_buf;
        hook = g_dshow.hook_fn;

        if (g_dshow.decoder.open_file(resolved)) {
            const double fps = (g_dshow.decoder.fps() > 0.0) ? g_dshow.decoder.fps() : 30.0;
            g_dshow.duration_100ns = static_cast<int64_t>(
                std::llround((static_cast<double>(g_dshow.decoder.frame_count()) * 10000000.0) / fps));
            if (g_dshow.duration_100ns <= 0) {
                g_dshow.duration_100ns = 1;
            }
            g_dshow.stop_pos_100ns = g_dshow.duration_100ns;
            g_dshow.pos_base_100ns = 0;
            g_dshow.connected      = true;
            g_dshow.eof_notified   = false;
            (void)g_dshow.decoder.decode_frame(0);

            hle_win32_log("[hle_dshow] RenderFile('%s' -> '%s') OK %ux%u %.2ffps %u frames",
                          narrow.c_str(), resolved.c_str(),
                          g_dshow.decoder.width(), g_dshow.decoder.height(),
                          fps, g_dshow.decoder.frame_count());
            hr = kS_OK;
        } else {
            hle_win32_log("[hle_dshow] RenderFile('%s' -> '%s') open failed",
                          narrow.c_str(), resolved.c_str());
            hr = kVFW_E_NOT_FOUND;
        }
    }

    if (hook != nullptr) {
        (void)hook(resolved);
    }

    ctx.eax = hr;
    ctx.ret_stdcall(mem, 12u);
}

// IMediaControl::Run(this) / Pause(this) / Stop(this) -> 4 bytes
void dshow_media_run(CpuContext& ctx, GuestMemory& mem) {
    {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        if (g_dshow.filter_state != kStateRunning) {
            g_dshow.run_anchor_time = std::chrono::steady_clock::now();
            g_dshow.filter_state    = kStateRunning;
            if (g_dshow.pos_base_100ns < g_dshow.duration_100ns) {
                g_dshow.eof_notified = false;
            }
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 4u);
}

void dshow_media_pause(CpuContext& ctx, GuestMemory& mem) {
    {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        if (g_dshow.filter_state == kStateRunning) {
            g_dshow.pos_base_100ns = g_dshow.current_position_locked();
        }
        g_dshow.filter_state = kStatePaused;
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 4u);
}

void dshow_media_stop(CpuContext& ctx, GuestMemory& mem) {
    {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        if (g_dshow.filter_state == kStateRunning) {
            g_dshow.pos_base_100ns = g_dshow.current_position_locked();
        }
        g_dshow.filter_state = kStateStopped;
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 4u);
}

// IMediaControl::GetState(this, msTimeout, pfs) -> 12 bytes
void dshow_media_get_state(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pfs_va = ctx.arg32(mem, 2);
    if (pfs_va == 0u || !mem.in_bounds(pfs_va, 4u)) {
        ctx.eax = kE_POINTER;
        ctx.ret_stdcall(mem, 12u);
        return;
    }
    uint32_t st = kStateStopped;
    {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        st = g_dshow.filter_state;
    }
    mem.w32(pfs_va, st);
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

// IMediaEvent::GetEventHandle(this, hEvent) -> 8 bytes
void dshow_event_get_handle(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t hev_va = ctx.arg32(mem, 1);
    if (hev_va != 0u && mem.in_bounds(hev_va, 4u)) {
        mem.w32(hev_va, 0u);
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IMediaEventEx::GetEvent(this, lEventCode, lParam1, lParam2, msTimeout) -> 20 bytes
void dshow_get_event(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t ev_va = ctx.arg32(mem, 1);
    const uint32_t p1_va = ctx.arg32(mem, 2);
    const uint32_t p2_va = ctx.arg32(mem, 3);

    bool emit_complete = false;
    {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        if (g_dshow.connected && !g_dshow.eof_notified &&
            g_dshow.duration_100ns > 0 &&
            g_dshow.current_position_locked() >= g_dshow.duration_100ns) {
            g_dshow.eof_notified = true;
            emit_complete = true;
        }
    }

    if (emit_complete) {
        if (ev_va != 0u && mem.in_bounds(ev_va, 4u)) mem.w32(ev_va, kEC_COMPLETE);
        if (p1_va != 0u && mem.in_bounds(p1_va, 4u)) mem.w32(p1_va, kS_OK);
        if (p2_va != 0u && mem.in_bounds(p2_va, 4u)) mem.w32(p2_va, 0u);
        ctx.eax = kS_OK;
    } else {
        ctx.eax = kE_ABORT;
    }
    ctx.ret_stdcall(mem, 20u);
}

// ISampleGrabber::SetMediaType(this, pType) -> 8 bytes
void dshow_grabber_set_media_type(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t mt_va = ctx.arg32(mem, 1);
    if (mt_va != 0u && mem.in_bounds(mt_va, 32u)) {
        uint8_t subtype[16] = {};
        mem.read_bytes(mt_va + 16u, subtype, 16);
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        if (guid_eq(subtype, kGuidSubtypeRGB24)) {
            g_dshow.requested_rgb32 = false;
        } else if (guid_eq(subtype, kGuidSubtypeRGB32)) {
            g_dshow.requested_rgb32 = true;
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// ISampleGrabber::GetConnectedMediaType(this, pType) -> 8 bytes
// Critical: Before RenderFile(), returns VFW_E_NOT_CONNECTED (causing MBAA.exe at 0x0041299c
// to switch from RGB24 to fast 32-bit X8R8G8B8!). After RenderFile(), populates AM_MEDIA_TYPE
// (0x48 bytes) + guest-allocated VIDEOINFOHEADER (0x58 bytes, freed by MBAA.exe via CoTaskMemFree).
void dshow_grabber_get_connected_media_type(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t mt_va = ctx.arg32(mem, 1);
    if (mt_va == 0u || !mem.in_bounds(mt_va, 0x48u)) {
        ctx.eax = kE_POINTER;
        ctx.ret_stdcall(mem, 8u);
        return;
    }

    uint32_t w = 0u, h = 0u;
    double fps = 30.0;
    bool rgb32 = true;
    {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        if (!g_dshow.connected || !g_dshow.decoder.is_open()) {
            ctx.eax = kVFW_E_NOT_CONNECTED;
            ctx.ret_stdcall(mem, 8u);
            return;
        }
        w     = g_dshow.decoder.width();
        h     = g_dshow.decoder.height();
        fps   = (g_dshow.decoder.fps() > 0.0) ? g_dshow.decoder.fps() : 30.0;
        rgb32 = g_dshow.requested_rgb32;
    }

    constexpr uint32_t kVideoInfoHeaderSize = 0x58u; // 88 bytes
    const uint32_t pb_fmt = mem.guest_calloc(1u, kVideoInfoHeaderSize);
    if (pb_fmt == 0u || !mem.in_bounds(pb_fmt, kVideoInfoHeaderSize)) {
        if (pb_fmt != 0u) mem.guest_free(pb_fmt);
        ctx.eax = kE_OUTOFMEMORY;
        ctx.ret_stdcall(mem, 8u);
        return;
    }

    const uint32_t bpp = rgb32 ? 4u : 3u;
    const uint32_t sample_bytes = w * h * bpp;
    const uint64_t avg_time_100ns = static_cast<uint64_t>(std::llround(10000000.0 / fps));

    // Populate VIDEOINFOHEADER (0x58 bytes)
    // +0x00 rcSource (left, top, right, bottom)
    mem.w32(pb_fmt + 0x00u, 0u);
    mem.w32(pb_fmt + 0x04u, 0u);
    mem.w32(pb_fmt + 0x08u, w);
    mem.w32(pb_fmt + 0x0Cu, h);
    // +0x10 rcTarget (left, top, right, bottom)
    mem.w32(pb_fmt + 0x10u, 0u);
    mem.w32(pb_fmt + 0x14u, 0u);
    mem.w32(pb_fmt + 0x18u, w);
    mem.w32(pb_fmt + 0x1Cu, h);
    // +0x20 dwBitRate, +0x24 dwBitErrorRate, +0x28 AvgTimePerFrame
    mem.w32(pb_fmt + 0x20u, 0u);
    mem.w32(pb_fmt + 0x24u, 0u);
    mem.w64(pb_fmt + 0x28u, avg_time_100ns);
    // +0x30 BITMAPINFOHEADER (40 bytes)
    mem.w32(pb_fmt + 0x30u, 40u);                           // biSize
    mem.w32(pb_fmt + 0x34u, w);                             // biWidth
    mem.w32(pb_fmt + 0x38u, h);                             // biHeight (positive = bottom-up DIB)
    mem.w16(pb_fmt + 0x3Cu, 1u);                            // biPlanes
    mem.w16(pb_fmt + 0x3Eu, static_cast<uint16_t>(bpp * 8u)); // biBitCount (32 or 24)
    mem.w32(pb_fmt + 0x40u, 0u);                            // biCompression = BI_RGB
    mem.w32(pb_fmt + 0x44u, sample_bytes);                  // biSizeImage

    // Populate AM_MEDIA_TYPE (0x48 bytes)
    mem.write_bytes(mt_va + 0x00u, kGuidMediaTypeVideo, 16);
    mem.write_bytes(mt_va + 0x10u, rgb32 ? kGuidSubtypeRGB32 : kGuidSubtypeRGB24, 16);
    mem.w32(mt_va + 0x20u, 1u);                   // bFixedSizeSamples = TRUE
    mem.w32(mt_va + 0x24u, 0u);                   // bTemporalCompression = FALSE
    mem.w32(mt_va + 0x28u, sample_bytes);         // lSampleSize
    mem.write_bytes(mt_va + 0x2Cu, kGuidFormatVideoInfo, 16);
    mem.w32(mt_va + 0x3Cu, 0u);                   // pUnk = NULL
    mem.w32(mt_va + 0x40u, kVideoInfoHeaderSize); // cbFormat
    mem.w32(mt_va + 0x44u, pb_fmt);               // pbFormat

    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// ISampleGrabber::SetBufferSamples(this, BufferThem) -> 8 bytes
void dshow_grabber_set_buffer_samples(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t enable = ctx.arg32(mem, 1);
    {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        g_dshow.buffer_samples = (enable != 0u);
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// ISampleGrabber::GetCurrentBuffer(this, pBufferSize, pBuffer) -> 12 bytes
void dshow_grabber_get_buffer(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t sz_va  = ctx.arg32(mem, 1);
    const uint32_t buf_va = ctx.arg32(mem, 2);
    if (sz_va == 0u || !mem.in_bounds(sz_va, 4u)) {
        ctx.eax = kE_POINTER;
        ctx.ret_stdcall(mem, 12u);
        return;
    }

    std::lock_guard<std::mutex> lock(g_dshow.mtx);
    if (!g_dshow.connected || !g_dshow.decoder.is_open()) {
        mem.w32(sz_va, 0u);
        ctx.eax = kVFW_E_WRONG_STATE;
        ctx.ret_stdcall(mem, 12u);
        return;
    }

    const uint32_t bpp = g_dshow.requested_rgb32 ? 4u : 3u;
    const uint32_t frame_bytes = g_dshow.decoder.width() * g_dshow.decoder.height() * bpp;

    // Size query call (pBuffer == NULL)
    if (buf_va == 0u) {
        mem.w32(sz_va, frame_bytes);
        ctx.eax = kS_OK;
        ctx.ret_stdcall(mem, 12u);
        return;
    }

    const uint32_t avail_bytes = mem.r32(sz_va);
    if (avail_bytes < frame_bytes || !mem.in_bounds(buf_va, frame_bytes)) {
        mem.w32(sz_va, frame_bytes);
        ctx.eax = kE_FAIL;
        ctx.ret_stdcall(mem, 12u);
        return;
    }

    const int64_t cur_100ns = g_dshow.current_position_locked();
    const double fps = (g_dshow.decoder.fps() > 0.0) ? g_dshow.decoder.fps() : 30.0;
    int32_t target_frame = static_cast<int32_t>((static_cast<double>(cur_100ns) / 10000000.0) * fps);
    if (target_frame < 0) {
        target_frame = 0;
    }
    const int32_t max_frame = static_cast<int32_t>(g_dshow.decoder.frame_count()) - 1;
    if (target_frame > max_frame) {
        target_frame = max_frame;
    }

    if (!g_dshow.decoder.decode_frame(target_frame) ||
        !g_dshow.decoder.copy_rgb(mem.ptr(buf_va), frame_bytes, g_dshow.requested_rgb32, /*bottom_up=*/true)) {
        ctx.eax = kE_FAIL;
        ctx.ret_stdcall(mem, 12u);
        return;
    }

    mem.w32(sz_va, frame_bytes);
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

// IMediaSeeking capability & time-format methods
void dshow_seeking_get_caps(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t out_va = ctx.arg32(mem, 1);
    if (out_va == 0u || !mem.in_bounds(out_va, 4u)) {
        ctx.eax = kE_POINTER;
    } else {
        mem.w32(out_va, kSeekingDefaultCaps);
        ctx.eax = kS_OK;
    }
    ctx.ret_stdcall(mem, 8u);
}

void dshow_seeking_is_format_supported(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t fmt_va = ctx.arg32(mem, 1);
    if (fmt_va == 0u || !mem.in_bounds(fmt_va, 16u)) {
        ctx.eax = kE_POINTER;
    } else {
        uint8_t g[16] = {};
        mem.read_bytes(fmt_va, g, 16);
        ctx.eax = guid_eq(g, kGuidTimeFormatMediaTime) ? kS_OK : kS_FALSE;
    }
    ctx.ret_stdcall(mem, 8u);
}

void dshow_seeking_get_time_format(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t fmt_va = ctx.arg32(mem, 1);
    if (fmt_va == 0u || !mem.in_bounds(fmt_va, 16u)) {
        ctx.eax = kE_POINTER;
    } else {
        mem.write_bytes(fmt_va, kGuidTimeFormatMediaTime, 16);
        ctx.eax = kS_OK;
    }
    ctx.ret_stdcall(mem, 8u);
}

// IMediaSeeking::GetDuration(this, pDuration) -> 8 bytes
void dshow_seeking_get_duration(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t out_va = ctx.arg32(mem, 1);
    if (out_va == 0u || !mem.in_bounds(out_va, 8u)) {
        ctx.eax = kE_POINTER;
        ctx.ret_stdcall(mem, 8u);
        return;
    }
    int64_t dur = 0;
    {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        dur = g_dshow.duration_100ns;
    }
    mem.w64(out_va, static_cast<uint64_t>(dur));
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IMediaSeeking::GetStopPosition(this, pStop) -> 8 bytes
void dshow_seeking_get_stop_pos(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t out_va = ctx.arg32(mem, 1);
    if (out_va == 0u || !mem.in_bounds(out_va, 8u)) {
        ctx.eax = kE_POINTER;
        ctx.ret_stdcall(mem, 8u);
        return;
    }
    int64_t stop_p = 0;
    {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        stop_p = g_dshow.stop_pos_100ns;
    }
    mem.w64(out_va, static_cast<uint64_t>(stop_p));
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IMediaSeeking::GetCurrentPosition(this, pCurrent) -> 8 bytes
void dshow_seeking_get_current_pos(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t out_va = ctx.arg32(mem, 1);
    if (out_va == 0u || !mem.in_bounds(out_va, 8u)) {
        ctx.eax = kE_POINTER;
        ctx.ret_stdcall(mem, 8u);
        return;
    }
    int64_t cur = 0;
    {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        cur = g_dshow.current_position_locked();
    }
    mem.w64(out_va, static_cast<uint64_t>(cur));
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IMediaSeeking::GetPreroll(this, pllPreroll) -> 8 bytes
void dshow_seeking_get_zero64(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t out_va = ctx.arg32(mem, 1);
    if (out_va != 0u && mem.in_bounds(out_va, 8u)) {
        mem.w64(out_va, 0ull);
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IMediaSeeking::SetPositions(this, pCurrent, dwCurrentFlags, pStop, dwStopFlags) -> 20 bytes
void dshow_seeking_set_positions(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pcur_va   = ctx.arg32(mem, 1);
    const uint32_t cur_flags = ctx.arg32(mem, 2);
    const uint32_t pstop_va  = ctx.arg32(mem, 3);
    const uint32_t stp_flags = ctx.arg32(mem, 4);

    std::lock_guard<std::mutex> lock(g_dshow.mtx);
    const uint32_t cur_mode = cur_flags & kSeekingPositioningMask;
    if (cur_mode != kSeekingNoPositioning && pcur_va != 0u && mem.in_bounds(pcur_va, 8u)) {
        const int64_t req = static_cast<int64_t>(mem.r64(pcur_va));
        int64_t next_pos = req;
        if (cur_mode == kSeekingRelativePositioning) {
            next_pos = g_dshow.current_position_locked() + req;
        }
        next_pos = std::clamp<int64_t>(next_pos, 0, g_dshow.duration_100ns);
        g_dshow.pos_base_100ns  = next_pos;
        g_dshow.run_anchor_time = std::chrono::steady_clock::now();
        if (next_pos < g_dshow.duration_100ns) {
            g_dshow.eof_notified = false;
        }
        if ((cur_flags & kSeekingReturnTime) != 0u) {
            mem.w64(pcur_va, static_cast<uint64_t>(next_pos));
        }
    }

    const uint32_t stp_mode = stp_flags & kSeekingPositioningMask;
    if (stp_mode != kSeekingNoPositioning && pstop_va != 0u && mem.in_bounds(pstop_va, 8u)) {
        const int64_t req = static_cast<int64_t>(mem.r64(pstop_va));
        int64_t next_stop = req;
        if (stp_mode == kSeekingRelativePositioning) {
            next_stop = g_dshow.stop_pos_100ns + req;
        }
        next_stop = std::clamp<int64_t>(next_stop, 0, g_dshow.duration_100ns);
        g_dshow.stop_pos_100ns = next_stop;
        if ((stp_flags & kSeekingReturnTime) != 0u) {
            mem.w64(pstop_va, static_cast<uint64_t>(next_stop));
        }
    }

    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 20u);
}

// IMediaSeeking::GetPositions(this, pCurrent, pStop) -> 12 bytes
void dshow_seeking_get_positions(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pcur_va  = ctx.arg32(mem, 1);
    const uint32_t pstop_va = ctx.arg32(mem, 2);
    int64_t cur = 0;
    int64_t stp = 0;
    {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        cur = g_dshow.current_position_locked();
        stp = g_dshow.stop_pos_100ns;
    }
    if (pcur_va != 0u && mem.in_bounds(pcur_va, 8u)) {
        mem.w64(pcur_va, static_cast<uint64_t>(cur));
    }
    if (pstop_va != 0u && mem.in_bounds(pstop_va, 8u)) {
        mem.w64(pstop_va, static_cast<uint64_t>(stp));
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

// IMediaSeeking::GetAvailable(this, pEarliest, pLatest) -> 12 bytes
void dshow_seeking_get_available(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t p1_va = ctx.arg32(mem, 1);
    const uint32_t p2_va = ctx.arg32(mem, 2);
    int64_t dur = 0;
    {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        dur = g_dshow.duration_100ns;
    }
    if (p1_va != 0u && mem.in_bounds(p1_va, 8u)) mem.w64(p1_va, 0ull);
    if (p2_va != 0u && mem.in_bounds(p2_va, 8u)) mem.w64(p2_va, static_cast<uint64_t>(dur));
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

// IMediaSeeking::SetRate(this, double dRate) -> 12 bytes (this + 8-byte double)
void dshow_seeking_set_rate(CpuContext& ctx, GuestMemory& mem) {
    const double r = mem.rf64(ctx.esp + 8u);
    if (std::isfinite(r) && r > 0.0) {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        if (g_dshow.filter_state == kStateRunning) {
            g_dshow.pos_base_100ns  = g_dshow.current_position_locked();
            g_dshow.run_anchor_time = std::chrono::steady_clock::now();
        }
        g_dshow.rate = r;
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

// IMediaSeeking::GetRate(this, double* pdRate) -> 8 bytes
void dshow_seeking_get_rate(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t rate_va = ctx.arg32(mem, 1);
    if (rate_va == 0u || !mem.in_bounds(rate_va, 8u)) {
        ctx.eax = kE_POINTER;
        ctx.ret_stdcall(mem, 8u);
        return;
    }
    double r = 1.0;
    {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        r = g_dshow.rate;
    }
    mem.wf64(rate_va, r);
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IBasicVideo::get_AvgTimePerFrame(this, pAvgTimePerFrame) -> 8 bytes
void dshow_basic_video_avg_time(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t out_va = ctx.arg32(mem, 1);
    if (out_va == 0u || !mem.in_bounds(out_va, 8u)) {
        ctx.eax = kE_POINTER;
        ctx.ret_stdcall(mem, 8u);
        return;
    }
    double avg_sec = 1.0 / 30.0;
    {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        if (g_dshow.connected && g_dshow.decoder.fps() > 0.0) {
            avg_sec = 1.0 / g_dshow.decoder.fps();
        }
    }
    mem.wf64(out_va, avg_sec);
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void dshow_basic_video_get_width(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t out_va = ctx.arg32(mem, 1);
    if (out_va != 0u && mem.in_bounds(out_va, 4u)) {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        mem.w32(out_va, g_dshow.decoder.width());
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void dshow_basic_video_get_height(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t out_va = ctx.arg32(mem, 1);
    if (out_va != 0u && mem.in_bounds(out_va, 4u)) {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        mem.w32(out_va, g_dshow.decoder.height());
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void dshow_basic_video_get_size(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pw_va = ctx.arg32(mem, 1);
    const uint32_t ph_va = ctx.arg32(mem, 2);
    std::lock_guard<std::mutex> lock(g_dshow.mtx);
    if (pw_va != 0u && mem.in_bounds(pw_va, 4u)) mem.w32(pw_va, g_dshow.decoder.width());
    if (ph_va != 0u && mem.in_bounds(ph_va, 4u)) mem.w32(ph_va, g_dshow.decoder.height());
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

// IBasicAudio::put_Volume / get_Volume / put_Balance / get_Balance -> 8 bytes
void dshow_basic_audio_put_volume(CpuContext& ctx, GuestMemory& mem) {
    const int32_t v = static_cast<int32_t>(ctx.arg32(mem, 1));
    {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        g_dshow.volume = v;
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void dshow_basic_audio_get_volume(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t out_va = ctx.arg32(mem, 1);
    if (out_va != 0u && mem.in_bounds(out_va, 4u)) {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        mem.w32(out_va, static_cast<uint32_t>(g_dshow.volume));
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void dshow_basic_audio_put_balance(CpuContext& ctx, GuestMemory& mem) {
    const int32_t b = static_cast<int32_t>(ctx.arg32(mem, 1));
    {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        g_dshow.balance = b;
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void dshow_basic_audio_get_balance(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t out_va = ctx.arg32(mem, 1);
    if (out_va != 0u && mem.in_bounds(out_va, 4u)) {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        mem.w32(out_va, static_cast<uint32_t>(g_dshow.balance));
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

uint32_t build_vtable(GuestMemory& mem, const RecompFn* slots, size_t count) {
    const uint32_t vt_va = mem.alloc_thunk_block(static_cast<uint32_t>(count * 4u), 4u);
    for (size_t i = 0; i < count; ++i) {
        const uint32_t method_va = alloc_com_method_thunk(slots[i]);
        mem.w32(vt_va + static_cast<uint32_t>(i * 4u), method_va);
    }
    return vt_va;
}

uint32_t build_com_object(GuestMemory& mem, uint32_t vtable_va) {
    const uint32_t obj_va = mem.alloc_thunk_block(16u, 8u);
    mem.w32(obj_va, vtable_va);
    return obj_va;
}

void ensure_dshow_objects_locked(GuestMemory& mem) {
    if (g_dshow.graph_obj_va != 0u &&
        g_dshow.graph_vtable != 0u &&
        mem.r32(g_dshow.graph_obj_va) == g_dshow.graph_vtable &&
        lookup_function(mem.r32(g_dshow.graph_vtable)) != nullptr) {
        return;
    }

    g_dshow.reset_session_locked();

    static constexpr size_t kSlots = 48;
    RecompFn graph_slots[kSlots];
    RecompFn control_slots[kSlots];
    RecompFn event_slots[kSlots];
    RecompFn window_slots[kSlots];
    RecompFn grabber_slots[kSlots];
    RecompFn seeking_slots[kSlots];
    RecompFn basic_video_slots[kSlots];
    RecompFn basic_audio_slots[kSlots];

    for (size_t i = 0; i < kSlots; ++i) {
        graph_slots[i]       = &com_ret<8u>;
        control_slots[i]     = &com_ret<4u>;
        event_slots[i]       = &com_ret<8u>;
        window_slots[i]      = &com_ret<8u>;
        grabber_slots[i]     = &com_ret<8u>;
        seeking_slots[i]     = &com_ret<8u>;
        basic_video_slots[i] = &com_ret<8u>;
        basic_audio_slots[i] = &com_ret<8u>;
    }

    auto set_iunknown = [](RecompFn* s) {
        s[0] = &dshow_query_interface;
        s[1] = &com_addref;
        s[2] = &com_release;
    };
    auto set_idispatch = [](RecompFn* s) {
        s[3] = &com_ret<8u, kE_NOINTERFACE>;  // GetTypeInfoCount(this, pctinfo)
        s[4] = &com_ret<16u, kE_NOINTERFACE>; // GetTypeInfo(this, iTInfo, lcid, ppTInfo)
        s[5] = &com_ret<24u, kE_NOINTERFACE>; // GetIDsOfNames(this, riid, rgszNames, cNames, lcid, rgDispId)
        s[6] = &com_ret<36u, kE_NOINTERFACE>; // Invoke(...)
    };

    set_iunknown(graph_slots);
    set_iunknown(control_slots);     set_idispatch(control_slots);
    set_iunknown(event_slots);       set_idispatch(event_slots);
    set_iunknown(window_slots);      set_idispatch(window_slots);
    set_iunknown(grabber_slots);
    set_iunknown(seeking_slots);
    set_iunknown(basic_video_slots); set_idispatch(basic_video_slots);
    set_iunknown(basic_audio_slots); set_idispatch(basic_audio_slots);

    // IFilterGraph / IGraphBuilder slots (0..17)
    graph_slots[3]  = &com_ret<12u>;      // AddFilter(this, pFilter, pName)
    graph_slots[4]  = &com_ret<8u>;       // RemoveFilter(this, pFilter)
    graph_slots[5]  = &com_ret<8u>;       // EnumFilters(this, ppEnum)
    graph_slots[6]  = &com_ret<12u>;      // FindFilterByName(this, pName, ppFilter)
    graph_slots[7]  = &com_ret<16u>;      // ConnectDirect(this, ppinOut, ppinIn, pmt)
    graph_slots[8]  = &com_ret<8u>;       // Reconnect(this, ppin)
    graph_slots[9]  = &com_ret<8u>;       // Disconnect(this, ppin)
    graph_slots[10] = &com_ret<4u>;       // SetDefaultSyncSource(this)
    graph_slots[11] = &com_ret<12u>;      // Connect(this, ppinOut, ppinIn)
    graph_slots[12] = &com_ret<8u>;       // Render(this, ppinOut)
    graph_slots[13] = &dshow_render_file; // RenderFile(this, lpwstrFile, lpwstrPlayList)
    graph_slots[14] = &com_ret<16u>;      // AddSourceFilter(this, lpcwstrFileName, lpcwstrFilterName, ppFilter)
    graph_slots[15] = &com_ret<8u>;       // SetLogFile(this, hFile)
    graph_slots[16] = &com_ret<4u>;       // Abort(this)
    graph_slots[17] = &com_ret<4u>;       // ShouldOperationContinue(this)

    // IMediaControl slots (IDispatch 3..6 + Run/Pause/Stop/GetState)
    control_slots[7]  = &dshow_media_run;       // Run(this)
    control_slots[8]  = &dshow_media_pause;     // Pause(this)
    control_slots[9]  = &dshow_media_stop;      // Stop(this)
    control_slots[10] = &dshow_media_get_state; // GetState(this, msTimeout, pfs)
    control_slots[11] = &com_ret<8u>;           // RenderFile(this, strFilename)
    control_slots[12] = &com_ret<12u>;          // AddSourceFilter(this, strFilename, ppUnk)
    control_slots[13] = &com_ret<8u>;           // get_FilterCollection(this, ppUnk)
    control_slots[14] = &com_ret<8u>;           // get_RegFilterCollection(this, ppUnk)
    control_slots[15] = &com_ret<4u>;           // StopWhenReady(this)

    // IMediaEvent / IMediaEventEx slots (IDispatch 3..6 + 7..15)
    event_slots[7]  = &dshow_event_get_handle; // GetEventHandle(this, hEvent)
    event_slots[8]  = &dshow_get_event;        // GetEvent(this, lEventCode, lParam1, lParam2, msTimeout)
    event_slots[9]  = &com_ret<12u>;           // WaitForCompletion(this, msTimeout, pEvCode)
    event_slots[10] = &com_ret<8u>;            // CancelDefaultHandling(this, lEvCode)
    event_slots[11] = &com_ret<8u>;            // RestoreDefaultHandling(this, lEvCode)
    event_slots[12] = &com_ret<16u>;           // FreeEventParams(this, lEvCode, lParam1, lParam2)
    event_slots[13] = &com_ret<16u>;           // SetNotifyWindow(this, hwnd, lMsg, lInstanceData)
    event_slots[14] = &com_ret<8u>;            // SetNotifyFlags(this, lNoNotifyFlags)
    event_slots[15] = &com_ret<8u>;            // GetNotifyFlags(this, lplNoNotifyFlags)

    // IVideoWindow slots (IDispatch 3..6, single-arg prop put/get = 8u, multi-arg methods below)
    window_slots[9]  = &com_ret<8u>;  // put_WindowStyle (+0x24)
    window_slots[13] = &com_ret<8u>;  // put_Visible (+0x34)
    window_slots[19] = &com_ret<8u>;  // put_AutoShow (+0x4c)
    window_slots[29] = &com_ret<8u>;  // put_Owner (+0x74)
    window_slots[37] = &com_ret<8u>;  // put_MessageDrain (+0x94)
    window_slots[39] = &com_ret<20u>; // SetWindowPosition(this, Left, Top, Width, Height) (+0x9c)
    window_slots[40] = &com_ret<20u>; // GetWindowPosition(this, pLeft, pTop, pWidth, pHeight) (+0xa0)
    window_slots[41] = &com_ret<12u>; // GetMinIdealImageSize(this, pWidth, pHeight)
    window_slots[42] = &com_ret<12u>; // GetMaxIdealImageSize(this, pWidth, pHeight)
    window_slots[44] = &com_ret<8u>;  // HideCursor(this, HideCursor)
    window_slots[45] = &com_ret<8u>;  // IsCursorHidden(this, CursorHidden)

    // ISampleGrabber slots (0x004128e8..0x00412c74)
    grabber_slots[3] = &com_ret<8u>;                           // SetOneShot(this, OneShot)
    grabber_slots[4] = &dshow_grabber_set_media_type;          // SetMediaType(this, pType)
    grabber_slots[5] = &dshow_grabber_get_connected_media_type;// GetConnectedMediaType(this, pType)
    grabber_slots[6] = &dshow_grabber_set_buffer_samples;      // SetBufferSamples(this, BufferThem)
    grabber_slots[7] = &dshow_grabber_get_buffer;              // GetCurrentBuffer(this, pBufferSize, pBuffer)
    grabber_slots[8] = &com_ret<8u, kE_NOINTERFACE>;           // GetCurrentSample(this, ppSample)
    grabber_slots[9] = &com_ret<12u>;                          // SetCallback(this, pCallback, WhichMethodToCallback)

    // IMediaSeeking slots (0x00412d30..0x00413260, inherits IUnknown directly)
    seeking_slots[3]  = &dshow_seeking_get_caps;            // GetCapabilities (+0x0c)
    seeking_slots[4]  = &dshow_seeking_get_caps;            // CheckCapabilities (+0x10)
    seeking_slots[5]  = &dshow_seeking_is_format_supported; // IsFormatSupported (+0x14)
    seeking_slots[6]  = &dshow_seeking_get_time_format;     // QueryPreferredFormat (+0x18)
    seeking_slots[7]  = &dshow_seeking_get_time_format;     // GetTimeFormat (+0x1c)
    seeking_slots[8]  = &dshow_seeking_is_format_supported; // IsUsingTimeFormat (+0x20)
    seeking_slots[9]  = &com_ret<8u>;                       // SetTimeFormat (+0x24)
    seeking_slots[10] = &dshow_seeking_get_duration;        // GetDuration (+0x28)
    seeking_slots[11] = &dshow_seeking_get_stop_pos;        // GetStopPosition (+0x2c)
    seeking_slots[12] = &dshow_seeking_get_current_pos;     // GetCurrentPosition (+0x30)
    seeking_slots[13] = &com_ret<24u>;                      // ConvertTimeFormat (+0x34)
    seeking_slots[14] = &dshow_seeking_set_positions;       // SetPositions (+0x38)
    seeking_slots[15] = &dshow_seeking_get_positions;       // GetPositions (+0x3c)
    seeking_slots[16] = &dshow_seeking_get_available;       // GetAvailable (+0x40)
    seeking_slots[17] = &dshow_seeking_set_rate;            // SetRate(this, double dRate) (+0x44)
    seeking_slots[18] = &dshow_seeking_get_rate;            // GetRate(this, double* pdRate) (+0x48)
    seeking_slots[19] = &dshow_seeking_get_zero64;          // GetPreroll (+0x4c)

    // IBasicVideo slots (IDispatch 3..6 + 7..38)
    basic_video_slots[7]  = &dshow_basic_video_avg_time;   // get_AvgTimePerFrame (+0x1c)
    basic_video_slots[22] = &dshow_basic_video_get_width;  // get_VideoWidth (+0x58)
    basic_video_slots[23] = &dshow_basic_video_get_height; // get_VideoHeight (+0x5c)
    basic_video_slots[28] = &com_ret<20u>;                 // SetSourcePosition (+0x70)
    basic_video_slots[29] = &com_ret<20u>;                 // GetSourcePosition (+0x74)
    basic_video_slots[30] = &com_ret<20u>;                 // SetDestinationPosition (+0x78)
    basic_video_slots[31] = &com_ret<20u>;                 // GetDestinationPosition (+0x7c)
    basic_video_slots[32] = &dshow_basic_video_get_size;   // GetVideoSize (+0x80)
    basic_video_slots[35] = &com_ret<12u, kE_NOINTERFACE>; // GetCurrentImage (+0x8c)

    // IBasicAudio slots (IDispatch 3..6 + 7..10)
    basic_audio_slots[7]  = &dshow_basic_audio_put_volume;  // put_Volume (+0x1c)
    basic_audio_slots[8]  = &dshow_basic_audio_get_volume;  // get_Volume (+0x20)
    basic_audio_slots[9]  = &dshow_basic_audio_put_balance; // put_Balance (+0x24)
    basic_audio_slots[10] = &dshow_basic_audio_get_balance; // get_Balance (+0x28)

    g_dshow.graph_vtable       = build_vtable(mem, graph_slots, kSlots);
    g_dshow.control_vtable     = build_vtable(mem, control_slots, kSlots);
    g_dshow.event_vtable       = build_vtable(mem, event_slots, kSlots);
    g_dshow.window_vtable      = build_vtable(mem, window_slots, kSlots);
    g_dshow.grabber_vtable     = build_vtable(mem, grabber_slots, kSlots);
    g_dshow.seeking_vtable     = build_vtable(mem, seeking_slots, kSlots);
    g_dshow.basic_video_vtable = build_vtable(mem, basic_video_slots, kSlots);
    g_dshow.basic_audio_vtable = build_vtable(mem, basic_audio_slots, kSlots);

    g_dshow.graph_obj_va       = build_com_object(mem, g_dshow.graph_vtable);
    g_dshow.control_obj_va     = build_com_object(mem, g_dshow.control_vtable);
    g_dshow.event_obj_va       = build_com_object(mem, g_dshow.event_vtable);
    g_dshow.window_obj_va      = build_com_object(mem, g_dshow.window_vtable);
    g_dshow.grabber_obj_va     = build_com_object(mem, g_dshow.grabber_vtable);
    g_dshow.seeking_obj_va     = build_com_object(mem, g_dshow.seeking_vtable);
    g_dshow.basic_video_obj_va = build_com_object(mem, g_dshow.basic_video_vtable);
    g_dshow.basic_audio_obj_va = build_com_object(mem, g_dshow.basic_audio_vtable);
}

} // namespace

void hle_dshow_set_video_hook(DShowVideoHookFn fn) {
    std::lock_guard<std::mutex> lock(g_dshow.mtx);
    g_dshow.hook_fn = fn;
}

bool hle_dshow_try_cocreate(
    GuestMemory& mem,
    const uint8_t* clsid_bytes,
    const uint8_t* iid_bytes,
    uint32_t* out_iface_va) {
    if (!clsid_bytes || !out_iface_va) return false;
    (void)iid_bytes;

    if (std::memcmp(clsid_bytes, kClsidFilterGraph, 16) == 0) {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        ensure_dshow_objects_locked(mem);
        g_dshow.reset_session_locked();
        g_dshow.active_refs = 1u;
        *out_iface_va = g_dshow.graph_obj_va;
        return true;
    }
    if (std::memcmp(clsid_bytes, kClsidSampleGrabber, 16) == 0) {
        std::lock_guard<std::mutex> lock(g_dshow.mtx);
        ensure_dshow_objects_locked(mem);
        ++g_dshow.active_refs;
        *out_iface_va = g_dshow.grabber_obj_va;
        return true;
    }
    return false;
}

} // namespace mbaa_recomp
