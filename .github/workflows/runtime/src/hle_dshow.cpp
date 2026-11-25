#include "mbaa_recomp/hle_win32.h"
#include "mbaa_recomp/dispatch.h"

#include <atomic>
#include <cstdio>
#include <cstring>

namespace mbaa_recomp {

namespace {

// DirectShow / COM error codes & filter states
constexpr uint32_t kS_OK          = 0x00000000u;
constexpr uint32_t kE_POINTER     = 0x80004003u;
constexpr uint32_t kE_NOINTERFACE = 0x80004002u;
constexpr uint32_t kEC_COMPLETE   = 0x00000001u;

constexpr uint32_t kStateStopped  = 0u;
constexpr uint32_t kStatePaused   = 1u;
constexpr uint32_t kStateRunning  = 2u;

// Little-endian GUID byte sequences verified from MBAA.exe (0x0051D710..0x0051D7F0):
// CLSID_FilterGraph: {E436EBB3-524F-11CE-9F53-0020AF0BA770}
constexpr uint8_t kClsidFilterGraph[16] = {
    0xB3, 0xEB, 0x36, 0xE4, 0x4F, 0x52, 0xCE, 0x11,
    0x9F, 0x53, 0x00, 0x20, 0xAF, 0x0B, 0xA7, 0x70
};
// CLSID_SampleGrabber: {C1F400A0-3F08-11D3-9F0B-006008039E37}
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

bool guid_eq(const uint8_t* a, const uint8_t* b) noexcept {
    return std::memcmp(a, b, 16) == 0;
}

struct DShowStubState {
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

    std::atomic<uint32_t> ref_count{1};
    std::atomic<uint32_t> filter_state{kStateStopped};
    bool completed_once         = true;
    DShowVideoHookFn hook_fn    = nullptr;
};

DShowStubState g_dshow;

// Shared COM AddRef/Release/ReturnOK helpers (stdcall)
void com_addref(CpuContext& ctx, GuestMemory& mem) {
    g_dshow.ref_count.fetch_add(1, std::memory_order_relaxed);
    ctx.eax = g_dshow.ref_count.load(std::memory_order_relaxed);
    ctx.ret_stdcall(mem, 4u);
}

void com_release(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t prev = g_dshow.ref_count.load(std::memory_order_relaxed);
    ctx.eax = (prev > 1u) ? (prev - 1u) : 0u;
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
    if (ppv_va == 0u) {
        ctx.eax = kE_POINTER;
        ctx.ret_stdcall(mem, 12u);
        return;
    }

    uint8_t iid[16] = {};
    mem.read_bytes(riid_va, iid, 16);

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
    g_dshow.ref_count.fetch_add(1, std::memory_order_relaxed);
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

// IGraphBuilder::RenderFile(this, lpwstrFile, lpwstrPlayList) -> 12 bytes
void dshow_render_file(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t wpath_va = ctx.arg32(mem, 1);
    const std::u16string wpath = mem.read_wstring_utf16(wpath_va);
    std::string narrow;
    narrow.reserve(wpath.size());
    for (char16_t ch : wpath) {
        narrow.push_back(static_cast<char>(ch & 0x7Fu));
    }
    g_dshow.completed_once = false;
    g_dshow.filter_state.store(kStateStopped, std::memory_order_relaxed);
    if (g_dshow.hook_fn != nullptr) {
        g_dshow.hook_fn(narrow);
    } else {
        hle_win32_log("[hle_dshow] RenderFile('%s') -> clean skip", narrow.c_str());
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

// IMediaControl::Run(this) / Pause(this) / Stop(this) -> 4 bytes
void dshow_media_run(CpuContext& ctx, GuestMemory& mem) {
    g_dshow.filter_state.store(kStateRunning, std::memory_order_relaxed);
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 4u);
}

void dshow_media_pause(CpuContext& ctx, GuestMemory& mem) {
    g_dshow.filter_state.store(kStatePaused, std::memory_order_relaxed);
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 4u);
}

void dshow_media_stop(CpuContext& ctx, GuestMemory& mem) {
    g_dshow.filter_state.store(kStateStopped, std::memory_order_relaxed);
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 4u);
}

// IMediaControl::GetState(this, msTimeout, pfs) -> 12 bytes
void dshow_media_get_state(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pfs_va = ctx.arg32(mem, 2);
    if (pfs_va) mem.w32(pfs_va, g_dshow.filter_state.load(std::memory_order_relaxed));
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

// IMediaEvent::GetEventHandle(this, hEvent) -> 8 bytes
void dshow_event_get_handle(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t hev_va = ctx.arg32(mem, 1);
    if (hev_va) mem.w32(hev_va, 0u);
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IMediaEventEx::GetEvent(this, lEventCode, lParam1, lParam2, msTimeout) -> 20 bytes
void dshow_get_event(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t ev_va = ctx.arg32(mem, 1);
    const uint32_t p1_va = ctx.arg32(mem, 2);
    const uint32_t p2_va = ctx.arg32(mem, 3);
    if (!g_dshow.completed_once) {
        g_dshow.completed_once = true;
        if (ev_va) mem.w32(ev_va, kEC_COMPLETE);
        if (p1_va) mem.w32(p1_va, 0u);
        if (p2_va) mem.w32(p2_va, 0u);
        ctx.eax = kS_OK;
    } else {
        ctx.eax = 0x80004005u; // E_FAIL / no more events in queue
    }
    ctx.ret_stdcall(mem, 20u);
}

// IMediaSeeking::GetDuration / GetStopPosition / GetCurrentPosition(this, pVal) -> 8 bytes
void dshow_seeking_get_zero64(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t out_va = ctx.arg32(mem, 1);
    if (out_va) mem.w64(out_va, 0ull);
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IMediaSeeking::GetPositions / GetAvailable(this, pVal1, pVal2) -> 12 bytes
void dshow_seeking_get_positions(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t p1_va = ctx.arg32(mem, 1);
    const uint32_t p2_va = ctx.arg32(mem, 2);
    if (p1_va) mem.w64(p1_va, 0ull);
    if (p2_va) mem.w64(p2_va, 0ull);
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

// IMediaSeeking::GetRate(this, pdRate) -> 8 bytes
void dshow_seeking_get_rate(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t rate_va = ctx.arg32(mem, 1);
    if (rate_va) mem.wf64(rate_va, 1.0);
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IBasicVideo::get_AvgTimePerFrame(this, pAvgTimePerFrame) -> 8 bytes
void dshow_basic_video_avg_time(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t out_va = ctx.arg32(mem, 1);
    if (out_va) mem.wf64(out_va, 1.0 / 60.0);
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// IBasicAudio::get_Volume / get_Balance(this, plValue) -> 8 bytes
void dshow_basic_audio_get_zero(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t out_va = ctx.arg32(mem, 1);
    if (out_va) mem.w32(out_va, 0u);
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// ISampleGrabber::GetCurrentBuffer(this, pBufferSize, pBuffer) -> 12 bytes
void dshow_grabber_get_buffer(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t sz_va = ctx.arg32(mem, 1);
    if (sz_va) mem.w32(sz_va, 0u);
    ctx.eax = 0x80004005u;
    ctx.ret_stdcall(mem, 12u);
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

void ensure_dshow_objects(GuestMemory& mem) {
    if (g_dshow.graph_obj_va != 0u && mem.r32(g_dshow.graph_obj_va) != 0u) {
        return;
    }

    g_dshow.filter_state.store(kStateStopped, std::memory_order_relaxed);

    // Covers IDispatch + all DirectShow vtable slots including IVideoWindow +0x9c (slot 39)
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
    set_iunknown(graph_slots);
    set_iunknown(control_slots);
    set_iunknown(event_slots);
    set_iunknown(window_slots);
    set_iunknown(grabber_slots);
    set_iunknown(seeking_slots);
    set_iunknown(basic_video_slots);
    set_iunknown(basic_audio_slots);

    // IFilterGraph / IGraphBuilder slots (0..16)
    graph_slots[3]  = &com_ret<12u>; // AddFilter(this, pFilter, pName)
    graph_slots[4]  = &com_ret<8u>;  // RemoveFilter(this, pFilter)
    graph_slots[5]  = &com_ret<8u>;  // EnumFilters(this, ppEnum)
    graph_slots[6]  = &com_ret<12u>; // FindFilterByName(this, pName, ppFilter)
    graph_slots[7]  = &com_ret<12u>; // ConnectDirect(this, ppinOut, ppinIn, pmt)
    graph_slots[8]  = &com_ret<8u>;  // Reconnect(this, ppin)
    graph_slots[9]  = &com_ret<8u>;  // Disconnect(this, ppin)
    graph_slots[10] = &com_ret<4u>;  // SetDefaultSyncSource(this)
    graph_slots[11] = &com_ret<12u>; // Connect(this, ppinOut, ppinIn)
    graph_slots[12] = &com_ret<8u>;  // Render(this, ppinOut)
    graph_slots[13] = &dshow_render_file; // RenderFile(this, lpwstrFile, lpwstrPlayList)
    graph_slots[14] = &com_ret<16u>; // AddSourceFilter(this, lpcwstrFileName, lpcwstrFilterName, ppFilter)
    graph_slots[15] = &com_ret<8u>;  // SetLogFile(this, hFile)
    graph_slots[16] = &com_ret<4u>;  // Abort(this)

    // IMediaControl slots (IDispatch + Run/Pause/Stop/GetState)
    control_slots[7]  = &dshow_media_run;       // Run(this)
    control_slots[8]  = &dshow_media_pause;     // Pause(this)
    control_slots[9]  = &dshow_media_stop;      // Stop(this)
    control_slots[10] = &dshow_media_get_state; // GetState(this, msTimeout, pfs)

    // IMediaEvent / IMediaEventEx slots
    event_slots[7]  = &dshow_event_get_handle; // GetEventHandle(this, hEvent)
    event_slots[8]  = &dshow_get_event;        // GetEvent(this, lEventCode, lParam1, lParam2, msTimeout)
    event_slots[12] = &com_ret<16u>;            // FreeEventParams(this, lEvCode, lParam1, lParam2)
    event_slots[13] = &com_ret<16u>;            // SetNotifyWindow(this, hwnd, lMsg, lInstanceData)
    event_slots[14] = &com_ret<8u>;             // SetNotifyFlags(this, lNoNotifyFlags)

    // IVideoWindow slots (offsets up to +0x9c = slot 39)
    window_slots[9]  = &com_ret<8u>;  // put_Visible
    window_slots[13] = &com_ret<8u>;  // put_WindowStyleEx (+0x34)
    window_slots[15] = &com_ret<8u>;  // put_WindowStyle (+0x3c)
    window_slots[19] = &com_ret<8u>;  // put_AutoShow (+0x4c)
    window_slots[29] = &com_ret<8u>;  // put_Owner (+0x74)
    window_slots[31] = &com_ret<20u>; // legacy SetWindowPosition slot
    window_slots[37] = &com_ret<8u>;  // put_MessageDrain (+0x94)
    window_slots[39] = &com_ret<20u>; // SetWindowPosition (+0x9c)

    // ISampleGrabber slots (0x004128e8..0x00412c00)
    grabber_slots[3] = &com_ret<8u>;  // SetOneShot(this, OneShot)
    grabber_slots[4] = &com_ret<8u>;  // SetMediaType(this, pType)
    grabber_slots[5] = &com_ret<8u>;  // GetConnectedMediaType(this, pType)
    grabber_slots[6] = &com_ret<8u>;  // SetBufferSamples(this, BufferThem)
    grabber_slots[7] = &dshow_grabber_get_buffer; // GetCurrentBuffer(this, pBufferSize, pBuffer)
    grabber_slots[8] = &com_ret<12u>; // SetCallback(this, pCallback, WhichMethodToCallback)

    // IMediaSeeking slots (0x00412d30..0x00413260)
    seeking_slots[10] = &dshow_seeking_get_zero64;    // GetDuration (+0x28)
    seeking_slots[11] = &dshow_seeking_get_zero64;    // GetStopPosition (+0x2c)
    seeking_slots[12] = &dshow_seeking_get_zero64;    // GetCurrentPosition (+0x30)
    seeking_slots[14] = &com_ret<20u>;                // SetPositions (+0x38)
    seeking_slots[15] = &dshow_seeking_get_positions; // GetPositions (+0x3c)
    seeking_slots[16] = &dshow_seeking_get_positions; // GetAvailable (+0x40)
    seeking_slots[17] = &com_ret<12u>;                // SetRate(this, double dRate) (+0x44)
    seeking_slots[18] = &dshow_seeking_get_rate;      // GetRate(this, double* pdRate) (+0x48)

    // IBasicVideo slots (0x00413190..0x004131e0)
    basic_video_slots[7] = &dshow_basic_video_avg_time; // get_AvgTimePerFrame (+0x1c)

    // IBasicAudio slots (0x0048167a)
    basic_audio_slots[7]  = &com_ret<8u>;                 // put_Volume (+0x1c)
    basic_audio_slots[8]  = &dshow_basic_audio_get_zero;  // get_Volume (+0x20)
    basic_audio_slots[9]  = &com_ret<8u>;                 // put_Balance (+0x24)
    basic_audio_slots[10] = &dshow_basic_audio_get_zero;  // get_Balance (+0x28)

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
        ensure_dshow_objects(mem);
        *out_iface_va = g_dshow.graph_obj_va;
        return true;
    }
    if (std::memcmp(clsid_bytes, kClsidSampleGrabber, 16) == 0) {
        ensure_dshow_objects(mem);
        *out_iface_va = g_dshow.grabber_obj_va;
        return true;
    }
    return false;
}

} // namespace mbaa_recomp
