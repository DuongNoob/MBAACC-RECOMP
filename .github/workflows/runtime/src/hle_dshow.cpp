#include "mbaa_recomp/hle_win32.h"
#include "mbaa_recomp/dispatch.h"

#include <atomic>
#include <cstdio>
#include <cstring>

namespace mbaa_recomp {

namespace {

// DirectShow / COM error codes
constexpr uint32_t kS_OK          = 0x00000000u;
constexpr uint32_t kE_NOINTERFACE = 0x80004002u;
constexpr uint32_t kEC_COMPLETE   = 0x00000001u;

// Little-endian GUID byte sequences verified from MBAA.exe (0x0051D720..0x0051D7F0):
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

struct DShowStubState {
    uint32_t graph_vtable      = 0;
    uint32_t control_vtable    = 0;
    uint32_t event_vtable      = 0;
    uint32_t window_vtable     = 0;
    uint32_t grabber_vtable    = 0;
    uint32_t graph_obj_va      = 0;
    uint32_t control_obj_va    = 0;
    uint32_t event_obj_va      = 0;
    uint32_t window_obj_va     = 0;
    uint32_t grabber_obj_va    = 0;
    std::atomic<uint32_t> ref_count{1};
    bool completed_once        = true;
    DShowVideoHookFn hook_fn   = nullptr;
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
    const uint32_t riid_va = ctx.arg32(mem, 1);
    const uint32_t ppv_va  = ctx.arg32(mem, 2);
    if (ppv_va == 0u) {
        ctx.eax = 0x80004003u; // E_POINTER
        ctx.ret_stdcall(mem, 12u);
        return;
    }

    uint8_t iid[16] = {};
    mem.read_bytes(riid_va, iid, 16);

    // Match IID prefixes for IMediaControl / IMediaEventEx / IVideoWindow / IGraphBuilder / ISampleGrabber
    uint32_t target_obj = g_dshow.graph_obj_va;
    if (iid[0] == 0xB1 && iid[1] == 0x68 && iid[2] == 0xA8 && iid[3] == 0x56) {
        target_obj = g_dshow.control_obj_va; // IID_IMediaControl
    } else if (iid[0] == 0xC0 && iid[1] == 0x68 && iid[2] == 0xA8 && iid[3] == 0x56) {
        target_obj = g_dshow.event_obj_va; // IID_IMediaEventEx
    } else if (iid[0] == 0xB4 && iid[1] == 0x68 && iid[2] == 0xA8 && iid[3] == 0x56) {
        target_obj = g_dshow.window_obj_va; // IID_IVideoWindow
    } else if (iid[0] == 0xFF && iid[1] == 0x2F && iid[2] == 0x65 && iid[3] == 0x6B) {
        target_obj = g_dshow.grabber_obj_va; // IID_ISampleGrabber
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
    if (g_dshow.hook_fn != nullptr) {
        g_dshow.hook_fn(narrow);
    } else {
        std::fprintf(stderr, "[hle_dshow] Skipping DirectShow movie '%s' on iOS (clean completion)\n",
                     narrow.c_str());
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
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

// IMediaControl::GetState(this, msTimeout, pfs) -> 12 bytes
void dshow_media_get_state(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pfs_va = ctx.arg32(mem, 2);
    if (pfs_va) mem.w32(pfs_va, 0u); // State_Stopped -> intro/VS transition finishes immediately
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
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

    // Standard DirectShow vtable slot counts (padded generously up to 36 slots with safe 4..20B stubs)
    static constexpr size_t kSlots = 36;
    RecompFn graph_slots[kSlots];
    RecompFn control_slots[kSlots];
    RecompFn event_slots[kSlots];
    RecompFn window_slots[kSlots];
    RecompFn grabber_slots[kSlots];

    for (size_t i = 0; i < kSlots; ++i) {
        graph_slots[i]   = &com_ret<8u>;
        control_slots[i] = &com_ret<4u>;
        event_slots[i]   = &com_ret<8u>;
        window_slots[i]  = &com_ret<8u>;
        grabber_slots[i] = &com_ret<8u>;
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
    control_slots[7] = &com_ret<4u>;           // Run(this)
    control_slots[8] = &com_ret<4u>;           // Pause(this)
    control_slots[9] = &com_ret<4u>;           // Stop(this)
    control_slots[10] = &dshow_media_get_state; // GetState(this, msTimeout, pfs)

    // IMediaEvent / IMediaEventEx slots
    event_slots[8]  = &dshow_get_event; // GetEvent
    event_slots[12] = &com_ret<16u>;    // FreeEventParams(this, lEvCode, lParam1, lParam2)
    event_slots[13] = &com_ret<16u>;    // SetNotifyWindow(this, hwnd, lMsg, lInstanceData)
    event_slots[14] = &com_ret<8u>;     // SetNotifyFlags(this, lNoNotifyFlags)

    // IVideoWindow slots
    window_slots[9]  = &com_ret<8u>;  // put_Visible
    window_slots[15] = &com_ret<8u>;  // put_WindowStyle
    window_slots[29] = &com_ret<8u>;  // put_Owner
    window_slots[31] = &com_ret<20u>; // SetWindowPosition(this, Left, Top, Width, Height)

    // ISampleGrabber slots (0x004128e8..0x00412c00)
    grabber_slots[3] = &com_ret<8u>;  // SetOneShot(this, OneShot)
    grabber_slots[4] = &com_ret<8u>;  // SetMediaType(this, pType)
    grabber_slots[5] = &com_ret<8u>;  // GetConnectedMediaType(this, pType)
    grabber_slots[6] = &com_ret<8u>;  // SetBufferSamples(this, BufferThem)
    grabber_slots[7] = &dshow_grabber_get_buffer; // GetCurrentBuffer(this, pBufferSize, pBuffer)
    grabber_slots[8] = &com_ret<12u>; // SetCallback(this, pCallback, WhichMethodToCallback)

    g_dshow.graph_vtable   = build_vtable(mem, graph_slots, kSlots);
    g_dshow.control_vtable = build_vtable(mem, control_slots, kSlots);
    g_dshow.event_vtable   = build_vtable(mem, event_slots, kSlots);
    g_dshow.window_vtable  = build_vtable(mem, window_slots, kSlots);
    g_dshow.grabber_vtable = build_vtable(mem, grabber_slots, kSlots);

    g_dshow.graph_obj_va   = build_com_object(mem, g_dshow.graph_vtable);
    g_dshow.control_obj_va = build_com_object(mem, g_dshow.control_vtable);
    g_dshow.event_obj_va   = build_com_object(mem, g_dshow.event_vtable);
    g_dshow.window_obj_va  = build_com_object(mem, g_dshow.window_vtable);
    g_dshow.grabber_obj_va = build_com_object(mem, g_dshow.grabber_vtable);
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
