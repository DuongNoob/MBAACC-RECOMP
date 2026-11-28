#import <Foundation/Foundation.h>
#import <QuartzCore/CAMetalLayer.h>

extern "C" void* objc_autoreleasePoolPush(void);
extern "C" void  objc_autoreleasePoolPop(void* pool);

#include "mbaa_recomp/runtime_engine.h"
#include "mbaa_recomp/cccaster_protocol.h"
#include "mbaa_recomp/d3d9_shim.h"
#include "mbaa_recomp/dispatch.h"
#include "mbaa_recomp/hle_audio.h"
#include "mbaa_recomp/hle_crt.h"
#include "mbaa_recomp/hle_input.h"
#include "mbaa_recomp/hle_win32.h"
#include "mbaa_recomp/netplay_rollback.h"

#include <algorithm>
#include <array>
#include <atomic>
#include <cctype>
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

namespace mbaa_recomp {

namespace {

constexpr uint32_t kGuestEntryWinMain   = 0x0040D240u;
constexpr uint32_t kCrtXcaStartVa       = 0x0051B410u; // .CRT$XCA
constexpr uint32_t kCrtXczEndVa         = 0x0051B584u; // .CRT$XCZ
constexpr uint32_t kSentinelReturnVa    = 0x00F00004u;

std::string ascii_lower(std::string s) {
    for (char& ch : s) {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }
    return s;
}

std::string find_exe_case_insensitive(const std::string& assets_dir, const char* filename) {
    std::error_code ec;
    const fs::path direct = fs::path(assets_dir) / filename;
    if (fs::exists(direct, ec) && fs::is_regular_file(direct, ec)) {
        return direct.string();
    }
    const std::string target = ascii_lower(filename);
    if (fs::exists(assets_dir, ec) && fs::is_directory(assets_dir, ec)) {
        for (const auto& entry : fs::directory_iterator(assets_dir, ec)) {
            if (ec) break;
            if (entry.is_regular_file(ec) &&
                ascii_lower(entry.path().filename().string()) == target) {
                return entry.path().string();
            }
        }
    }
    return {};
}

uint32_t run_static_crt_initializers(CpuContext& ctx, GuestMemory& mem) {
    uint32_t count = 0u;
    for (uint32_t ptr_va = kCrtXcaStartVa; ptr_va < kCrtXczEndVa; ptr_va += 4u) {
        const uint32_t fn_va = mem.r32(ptr_va);
        if (fn_va == 0u) continue;
        RecompFn fn = lookup_function(fn_va);
        if (!fn) continue;

        const uint32_t saved_esp = ctx.esp;
        ctx.push32(mem, kSentinelReturnVa);
        fn(ctx, mem);
        // Defensively restore stack pointer if a compiler stub leaves alignment delta.
        ctx.esp = saved_esp;
        ++count;
    }
    return count;
}

constexpr uint32_t kNetBattleFlagVa     = 0x0054EEE8u; // 1 = in active combat
constexpr uint32_t kNetGameModeVa       = 0x0055D1D0u; // 0x14 = VS, 0x1A = Replay
constexpr uint32_t kNetFastForwardVa    = 0x0055D25Cu; // 1 = fast-forward / skip FPS sleep
constexpr uint32_t kNetInputKeyTableVa  = 0x0054D2C0u; // 20B P1 DIK keybind table
constexpr uint32_t kNetFocusEscapeVa    = 0x005544F1u; // Escape key check (sub_004a0070)
constexpr uint32_t kNetChara0AltVa      = 0x0074D8F8u;
constexpr uint32_t kNetChara0Va         = 0x0074D8FCu;
constexpr uint32_t kNetMoon0Va          = 0x0074D900u;
constexpr uint32_t kNetColor0Va         = 0x0074D904u;
constexpr uint32_t kNetChara1AltVa      = 0x0074D91Cu;
constexpr uint32_t kNetChara1Va         = 0x0074D920u;
constexpr uint32_t kNetMoon1Va          = 0x0074D924u;
constexpr uint32_t kNetColor1Va         = 0x0074D928u;
constexpr uint32_t kNetStageVa          = 0x0074FD98u;
constexpr size_t   kNetKeyTableBytes    = 20u;
constexpr size_t   kNetFrameWindow      = 512u;

struct ResimStep {
    uint32_t frame = 0u;
    uint16_t p1_word = 0u;
    uint16_t p2_word = 0u;
    bool save_next_snapshot = false;
    bool save_next_sync_hash = false;
    bool mask_spectator = false;
};

struct NetFrameSlot {
    uint32_t frame = 0xFFFFFFFFu;
    uint16_t local_word = 0u;
    uint16_t remote_word = 0u;
    uint16_t spectate_p1 = 0u;
    uint16_t spectate_p2 = 0u;
    bool local_sent = false;
    bool remote_confirmed = false;
    bool spectate_ready = false;
    bool sync_hash_valid = false;
    bool sync_hash_sent = false;
    SyncHashData local_sync_hash{};
};

WireRngState to_wire_rng(const RngStateBlock& src, uint32_t ctx_val = 0u) noexcept {
    WireRngState out{};
    out.context = ctx_val;
    out.data = src.bytes;
    return out;
}

RngStateBlock from_wire_rng(const WireRngState& src) noexcept {
    RngStateBlock out{};
    out.bytes = src.data;
    return out;
}

WireSyncHash to_wire_sync_hash(const SyncHashData& src) noexcept {
    WireSyncHash out{};
    out.indexed_frame  = src.indexed_frame;
    out.round_or_flags = src.flags;
    out.rng_md5        = src.rng_md5;
    out.globals        = src.globals;
    out.p1_slice       = src.p1_slice;
    out.p2_slice       = src.p2_slice;
    return out;
}

SyncHashData from_wire_sync_hash(const WireSyncHash& src) noexcept {
    SyncHashData out{};
    out.indexed_frame = src.indexed_frame;
    out.flags         = src.round_or_flags;
    out.rng_md5       = src.rng_md5;
    out.globals       = src.globals;
    out.p1_slice      = src.p1_slice;
    out.p2_slice      = src.p2_slice;
    return out;
}

void apply_initial_game_state(GuestMemory& mem, const WireInitialGameState& st) noexcept {
    if (!mem.in_bounds(kNetChara0AltVa, 0x38u) || !mem.in_bounds(kNetStageVa, 4u)) {
        return;
    }
    mem.w32(kNetChara0Va,    st.chara0);
    mem.w32(kNetChara0AltVa, st.chara0);
    mem.w32(kNetMoon0Va,     st.moon0);
    mem.w32(kNetColor0Va,    st.color0);
    mem.w32(kNetChara1Va,    st.chara1);
    mem.w32(kNetChara1AltVa, st.chara1);
    mem.w32(kNetMoon1Va,     st.moon1);
    mem.w32(kNetColor1Va,    st.color1);
    mem.w32(kNetStageVa,     st.stage);
}

WireInitialGameState capture_initial_game_state(const GuestMemory& mem) noexcept {
    WireInitialGameState st{};
    if (!mem.in_bounds(kNetChara0AltVa, 0x38u) || !mem.in_bounds(kNetStageVa, 4u)) {
        return st;
    }
    st.chara0 = static_cast<uint8_t>(mem.r32(kNetChara0Va) & 0xFFu);
    st.moon0  = static_cast<uint8_t>(mem.r32(kNetMoon0Va) & 0xFFu);
    st.color0 = static_cast<uint8_t>(mem.r32(kNetColor0Va) & 0xFFu);
    st.chara1 = static_cast<uint8_t>(mem.r32(kNetChara1Va) & 0xFFu);
    st.moon1  = static_cast<uint8_t>(mem.r32(kNetMoon1Va) & 0xFFu);
    st.color1 = static_cast<uint8_t>(mem.r32(kNetColor1Va) & 0xFFu);
    st.stage  = mem.r32(kNetStageVa);
    return st;
}

} // namespace

struct RuntimeEngine::Impl {
    CpuContext ctx{};
    GuestMemory mem{};
    RollbackManager rollback{16};

    std::string assets_dir;
    std::string last_error;
    void* metal_layer = nullptr;
    int width = 1334;
    int height = 750;

    std::atomic<bool> initialized{false};
    std::atomic<bool> running{false};
    std::atomic<uint64_t> frame_count{0};

    enum class StepPhase {
        Idle,
        WaitGuestYield,
        GuestYielded,
        StepRequested,
        GuestExited,
    };

    std::thread guest_thread;
    std::mutex sync_mtx;
    std::condition_variable host_cv;
    std::condition_variable guest_cv;
    StepPhase phase = StepPhase::Idle;
    bool stop_requested = false;
    bool frame_in_flight = false;
    bool guest_boot_ok = false;
    bool guest_detached = false;
    void* guest_frame_pool = nullptr;

    D3D9MetalBridge d3d_bridge;
    bool d3d_initialized = false;

    // CCCaster v3.1 Netplay & full 61-region rollback engine (0 B allocated offline)
    CccasterNetClient net_client;
    NetplayRollbackEngine net_rollback;

    std::thread net_thread;
    std::mutex net_thread_mtx;
    std::condition_variable net_thread_cv;
    bool net_thread_stop = false;

    std::atomic<bool> netplay_active{false};
    std::atomic<NetplayMode> netplay_mode{NetplayMode::Offline};
    std::atomic<bool> netplay_in_match{false};
    std::atomic<uint32_t> netplay_frame{0u};
    std::atomic<uint32_t> netplay_rollbacks{0u};
    std::atomic<uint32_t> netplay_desyncs{0u};
    std::atomic<int> netplay_cfg_delay{-1};
    std::atomic<int> netplay_cfg_max_rollback{4};
    std::atomic<bool> netplay_training{false};
    std::mutex net_err_mtx;
    std::string net_last_error;

    // Synchronous rollback resimulation burst (owned by step_frame while guest is yielded,
    // and read/updated on guest_thread while resim_active == true).
    std::atomic<bool> resim_active{false};
    std::atomic<bool> resim_abort{false};
    std::vector<ResimStep> resim_steps;
    size_t resim_cursor = 0u;

    // Match session state (simulation thread only)
    bool in_match_prev = false;
    bool keybind_saved = false;
    bool rng_sent_this_match = false;
    bool rng_installed_this_match = false;
    uint32_t last_contig_confirmed = 0xFFFFFFFFu;
    uint32_t last_broadcast_frame = 0xFFFFFFFFu;
    uint16_t last_remote_word = 0u;
    std::array<uint8_t, kNetKeyTableBytes> saved_keybind_table{};
    std::array<NetFrameSlot, kNetFrameWindow> frame_slots{};
    std::unordered_map<uint32_t, SyncHashData> pending_remote_hashes;

    NetFrameSlot* slot_for(uint32_t f) noexcept {
        NetFrameSlot& s = frame_slots[f % kNetFrameWindow];
        return (s.frame == f) ? &s : nullptr;
    }

    NetFrameSlot& alloc_slot(uint32_t f) noexcept {
        NetFrameSlot& s = frame_slots[f % kNetFrameWindow];
        if (s.frame != f) {
            s = NetFrameSlot{};
            s.frame = f;
        }
        return s;
    }

    void reset_match_tracking() noexcept {
        last_contig_confirmed = 0xFFFFFFFFu;
        last_broadcast_frame = 0xFFFFFFFFu;
        last_remote_word = 0u;
        rng_sent_this_match = false;
        rng_installed_this_match = false;
        for (auto& s : frame_slots) {
            s = NetFrameSlot{};
        }
        pending_remote_hashes.clear();
        netplay_frame.store(0u, std::memory_order_release);
        net_rollback.reset_match_state();
    }

    void record_local_sync_hash(uint32_t f, const SyncHashData& sh) noexcept {
        NetFrameSlot& s = alloc_slot(f);
        s.local_sync_hash = sh;
        s.sync_hash_valid = true;
        s.sync_hash_sent  = false;
    }

    void restore_keybinds_if_saved() noexcept {
        if (keybind_saved && mem.in_bounds(kNetInputKeyTableVa, kNetKeyTableBytes)) {
            mem.write_bytes(kNetInputKeyTableVa, saved_keybind_table.data(), kNetKeyTableBytes);
            keybind_saved = false;
        }
    }

    void save_and_zero_keybinds() noexcept {
        if (!mem.in_bounds(kNetInputKeyTableVa, kNetKeyTableBytes)) return;
        if (!keybind_saved) {
            mem.read_bytes(kNetInputKeyTableVa, saved_keybind_table.data(), kNetKeyTableBytes);
            keybind_saved = true;
        }
        mem.zero_bytes(kNetInputKeyTableVa, kNetKeyTableBytes);
    }

    void start_net_poll_thread() {
        stop_net_poll_thread();
        {
            std::lock_guard<std::mutex> lk(net_thread_mtx);
            net_thread_stop = false;
        }
        net_thread = std::thread([this]() {
            std::unique_lock<std::mutex> lk(net_thread_mtx);
            while (!net_thread_stop) {
                lk.unlock();
                net_client.poll();
                lk.lock();
                net_thread_cv.wait_for(lk, std::chrono::milliseconds(5), [this]() {
                    return net_thread_stop;
                });
            }
        });
    }

    void stop_net_poll_thread() {
        {
            std::lock_guard<std::mutex> lk(net_thread_mtx);
            net_thread_stop = true;
        }
        net_thread_cv.notify_all();
        if (net_thread.joinable()) {
            net_thread.join();
        }
    }

    bool start_netplay_role(NetplayMode role, const NetplayConfig& config);
    bool step_netplay_frame();
    bool run_resim_burst(uint32_t first_mispred, uint32_t current_frame);
    bool execute_guest_single_tick(uint32_t wait_ms = 100u);
    void poll_and_apply_match_packets(const CccasterSessionStatus& cs, bool in_match);
    void check_and_exchange_sync_hashes();
};

RuntimeEngine::RuntimeEngine() : impl_(std::make_unique<Impl>()) {}

RuntimeEngine::~RuntimeEngine() {
    shutdown();
    if (impl_ && impl_->guest_detached) {
        // Emergency OS-termination fallback: keep Impl alive until process exit so a
        // detached guest thread cannot dereference destroyed state during teardown.
        (void)impl_.release();
    }
}

bool RuntimeEngine::init(const std::string& assets_dir, void* metal_layer, int width, int height) {
    shutdown();

    impl_->assets_dir = assets_dir;
    impl_->metal_layer = metal_layer;
    impl_->width = (width > 0) ? width : 1334;
    impl_->height = (height > 0) ? height : 750;
    impl_->last_error.clear();
    impl_->frame_count.store(0u, std::memory_order_relaxed);
    impl_->guest_boot_ok = false;

    if (assets_dir.empty()) {
        impl_->last_error = "Assets directory path is empty.";
        return false;
    }

    const std::string exe_path = find_exe_case_insensitive(assets_dir, "MBAA.exe");
    if (exe_path.empty()) {
        impl_->last_error = "Missing MBAA.exe in BYOC directory: " + assets_dir;
        return false;
    }

    if (!impl_->mem.init()) {
        impl_->last_error = "Failed to allocate 256 MiB GuestMemory arena.";
        return false;
    }

    if (!impl_->mem.load_pe_sections(exe_path)) {
        impl_->last_error = "Failed to load PE sections from: " + exe_path;
        impl_->mem.shutdown();
        return false;
    }

    apply_cccaster_stage_unlocks(impl_->mem);

    clear_dispatch_table();
    register_recomp_functions();

    RecompFn win_main_fn = lookup_function(kGuestEntryWinMain);
    if (!win_main_fn) {
        impl_->last_error = "Recompiled entry point sub_0040d240 (WinMain) is not registered.";
        clear_dispatch_table();
        impl_->mem.shutdown();
        return false;
    }

    // Initialize D3D9 -> Metal bridge and wire IAT forwarding before booting WinMain
    impl_->d3d_initialized = impl_->d3d_bridge.init(metal_layer, impl_->width, impl_->height);
    if (!impl_->d3d_initialized && metal_layer != nullptr) {
        impl_->last_error = "Failed to initialize D3D9MetalBridge for Metal layer.";
        clear_dispatch_table();
        impl_->mem.shutdown();
        return false;
    }
    D3D9MetalBridge::set_active(&impl_->d3d_bridge);
    hle_win32_register_d3d_handler([](uint32_t iat_va, const char* api_name, CpuContext& ctx, GuestMemory& mem) {
        if (auto* bridge = D3D9MetalBridge::active(); bridge != nullptr) {
            if (bridge->handle_d3d_iat(iat_va, api_name, ctx, mem)) {
                return;
            }
        }
        ctx.eax = 0u;
        ctx.ret_stdcall(mem, 4u);
    });

    // MBAACC native client coordinate space is 640x480 unless configured otherwise.
    hle_win32_init(assets_dir, 640u, 480u);
    hle_win32_log("RuntimeEngine::init PE loaded (%s), starting guest thread", exe_path.c_str());
    input_init();
    audio_init();

    impl_->ctx.reset(GuestMemory::kInitialEsp, GuestMemory::kTebBase);

    Impl* impl_ptr = impl_.get();
    hle_win32_set_frame_yield_callback([impl_ptr]() -> bool {
        if (!impl_ptr->guest_boot_ok) {
            hle_win32_log(
                "First PeekMessageA yield: active=%u d3d_ctx=0x%08x d3d_dev=0x%08x "
                "dinput8=0x%08x hwnd=0x%08x in_mgr=0x%08x rt0=0x%08x",
                static_cast<unsigned>(impl_ptr->mem.r8(0x0076e650u)),
                impl_ptr->mem.r32(0x00767448u),
                impl_ptr->mem.r32(0x0076e7d4u),
                impl_ptr->mem.r32(0x005544e8u),
                impl_ptr->mem.r32(0x005541c4u),
                impl_ptr->mem.r32(0x0076e6b0u),
                impl_ptr->mem.r32(0x005542d0u));
        }

        // Keep CCCaster extra stages and Stage 55 BGM table patched across runtime bgm.txt loads.
        apply_cccaster_stage_unlocks(impl_ptr->mem);

        // Drain all Obj-C / Metal autoreleased temporaries from the guest frame that just ended.
        if (impl_ptr->guest_frame_pool != nullptr) {
            objc_autoreleasePoolPop(impl_ptr->guest_frame_pool);
            impl_ptr->guest_frame_pool = nullptr;
        }

        // Synchronous rollback catchup fast-path: save resimulated state snapshots and advance
        // immediately into the next catchup tick on guest_thread without waking host_cv.
        if (impl_ptr->resim_active.load(std::memory_order_acquire)) {
            const size_t done_idx = impl_ptr->resim_cursor;
            if (!impl_ptr->resim_abort.load(std::memory_order_acquire) &&
                done_idx < impl_ptr->resim_steps.size()) {
                const auto& finished = impl_ptr->resim_steps[done_idx];
                if (finished.save_next_snapshot) {
                    const uint32_t saved_f = finished.frame + 1u;
                    impl_ptr->net_rollback.save_frame(impl_ptr->mem, saved_f);
                    if (finished.save_next_sync_hash) {
                        SyncHashData sh{};
                        const uint32_t rflags = impl_ptr->mem.in_bounds(kNetGameModeVa, 4u)
                            ? impl_ptr->mem.r32(kNetGameModeVa) : 0u;
                        if (build_sync_hash(impl_ptr->mem, saved_f, rflags, sh)) {
                            impl_ptr->record_local_sync_hash(saved_f, sh);
                        }
                    }
                }
            }
            const size_t next_idx = done_idx + 1u;
            const bool quitting = !impl_ptr->running.load(std::memory_order_acquire) ||
                                  impl_ptr->resim_abort.load(std::memory_order_acquire) ||
                                  hle_win32_is_quit_requested();
            if (!quitting && next_idx < impl_ptr->resim_steps.size()) {
                impl_ptr->resim_cursor = next_idx;
                const auto& nxt = impl_ptr->resim_steps[next_idx];
                input_inject_netplay_pair(impl_ptr->mem, nxt.p1_word, nxt.p2_word, nxt.mask_spectator);
                audio_rollback_set_tracking(true, nxt.frame);
                if (impl_ptr->mem.in_bounds(kNetFastForwardVa, 4u)) {
                    impl_ptr->mem.w32(kNetFastForwardVa, 1u);
                }
                impl_ptr->guest_frame_pool = objc_autoreleasePoolPush();
                return true;
            }
            if (impl_ptr->mem.in_bounds(kNetFastForwardVa, 4u)) {
                impl_ptr->mem.w32(kNetFastForwardVa, 0u);
            }
            impl_ptr->resim_active.store(false, std::memory_order_release);
        }

        bool keep_running = true;
        {
            std::unique_lock<std::mutex> lock(impl_ptr->sync_mtx);
            impl_ptr->guest_boot_ok = true;
            impl_ptr->phase = Impl::StepPhase::GuestYielded;
            impl_ptr->host_cv.notify_all();

            impl_ptr->guest_cv.wait(lock, [impl_ptr]() {
                return impl_ptr->stop_requested ||
                       impl_ptr->phase == Impl::StepPhase::StepRequested;
            });

            if (impl_ptr->stop_requested || hle_win32_is_quit_requested()) {
                keep_running = false;
            } else {
                impl_ptr->phase = Impl::StepPhase::WaitGuestYield;
            }
        }

        // Push a fresh per-frame autorelease pool before returning to guest code (including quit teardown).
        impl_ptr->guest_frame_pool = objc_autoreleasePoolPush();
        return keep_running;
    });

    {
        std::lock_guard<std::mutex> lock(impl_->sync_mtx);
        impl_->phase = Impl::StepPhase::WaitGuestYield;
        impl_->stop_requested = false;
        impl_->frame_in_flight = false;
        impl_->guest_detached = false;
        impl_->guest_frame_pool = nullptr;
    }

    impl_->initialized.store(true, std::memory_order_release);
    impl_->running.store(true, std::memory_order_release);

    impl_->guest_thread = std::thread([impl_ptr, win_main_fn]() {
        @autoreleasepool {
            impl_ptr->guest_frame_pool = objc_autoreleasePoolPush();
            struct GuestFramePoolGuard {
                void*& pool;
                ~GuestFramePoolGuard() {
                    if (pool != nullptr) {
                        objc_autoreleasePoolPop(pool);
                        pool = nullptr;
                    }
                }
            } frame_pool_guard{impl_ptr->guest_frame_pool};

            hle_win32_set_guest_main_thread();

            const uint32_t crt_cnt = run_static_crt_initializers(impl_ptr->ctx, impl_ptr->mem);
            hle_win32_log("CRT initializers completed: %u", crt_cnt);

            const uint32_t cmdline_va = impl_ptr->mem.alloc_thunk_block(16u, 4u);
            impl_ptr->mem.write_cstring(cmdline_va, "", 16u);

            // WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
            impl_ptr->ctx.push32(impl_ptr->mem, 10u);                    // nCmdShow = SW_SHOWDEFAULT
            impl_ptr->ctx.push32(impl_ptr->mem, cmdline_va);             // lpCmdLine
            impl_ptr->ctx.push32(impl_ptr->mem, 0u);                     // hPrevInstance
            impl_ptr->ctx.push32(impl_ptr->mem, GuestMemory::kImageBase);// hInstance
            impl_ptr->ctx.push32(impl_ptr->mem, kSentinelReturnVa);      // return address

            hle_win32_log("Entering WinMain (0x0040d240)");
            win_main_fn(impl_ptr->ctx, impl_ptr->mem);
            hle_win32_log("WinMain exited eax=0x%08x", impl_ptr->ctx.eax);

            std::lock_guard<std::mutex> lock(impl_ptr->sync_mtx);
            impl_ptr->phase = Impl::StepPhase::GuestExited;
            impl_ptr->running.store(false, std::memory_order_release);
            impl_ptr->host_cv.notify_all();
        }
    });

    // Wait for WinMain -> App_BootInitialize -> first PeekMessageA yield.
    {
        std::unique_lock<std::mutex> lock(impl_->sync_mtx);
        impl_->host_cv.wait(lock, [impl_ptr]() {
            return impl_ptr->phase == Impl::StepPhase::GuestYielded ||
                   impl_ptr->phase == Impl::StepPhase::GuestExited;
        });

        if (impl_->phase == Impl::StepPhase::GuestExited && !impl_->guest_boot_ok) {
            impl_->last_error = "MBAA.exe exited during boot initialization (code=" +
                                std::to_string(impl_->ctx.eax) + ").";
            lock.unlock();
            shutdown();
            return false;
        }
    }

    return true;
}

bool RuntimeEngine::Impl::execute_guest_single_tick(uint32_t wait_ms) {
    auto guest_done = [this]() {
        return phase == StepPhase::GuestYielded || phase == StepPhase::GuestExited;
    };
    std::unique_lock<std::mutex> lock(sync_mtx);
    frame_in_flight = true;
    phase = StepPhase::StepRequested;
    guest_cv.notify_one();

    if (!host_cv.wait_for(lock, std::chrono::milliseconds(wait_ms), guest_done)) {
        return false;
    }
    frame_in_flight = false;
    if (phase == StepPhase::GuestExited) {
        running.store(false, std::memory_order_release);
        return false;
    }
    return true;
}

bool RuntimeEngine::Impl::run_resim_burst(uint32_t first_mispred, uint32_t current_frame) {
    if (first_mispred >= current_frame) return true;

    const CccasterSessionStatus cs = net_client.status();
    const bool local_is_p1 = (cs.local_player_index != 1);

    resim_steps.clear();
    resim_steps.reserve(static_cast<size_t>(current_frame - first_mispred));
    for (uint32_t f = first_mispred; f < current_frame; ++f) {
        const NetFrameSlot* sl = slot_for(f);
        const uint16_t loc_w = (sl != nullptr) ? sl->local_word : 0u;
        const uint16_t rem_w = (sl != nullptr) ? sl->remote_word : 0u;
        ResimStep st{};
        st.frame              = f;
        st.p1_word            = local_is_p1 ? loc_w : rem_w;
        st.p2_word            = local_is_p1 ? rem_w : loc_w;
        st.save_next_snapshot = true;
        st.save_next_sync_hash = (((f + 1u) % 30u) == 0u);
        st.mask_spectator     = false;
        resim_steps.push_back(st);
    }

    if (!net_rollback.rollback_to_frame(mem, first_mispred, current_frame)) {
        resim_steps.clear();
        return false;
    }

    d3d_bridge.set_skip_render(true);
    audio_rollback_begin_catchup(first_mispred);
    if (mem.in_bounds(kNetFastForwardVa, 4u)) {
        mem.w32(kNetFastForwardVa, static_cast<uint32_t>(resim_steps.size()));
    }

    resim_cursor = 0u;
    resim_abort.store(false, std::memory_order_release);
    resim_active.store(true, std::memory_order_release);
    input_inject_netplay_pair(mem, resim_steps[0].p1_word, resim_steps[0].p2_word, false);
    audio_rollback_set_tracking(true, resim_steps[0].frame);

    const bool ok = execute_guest_single_tick(300u);

    bool still_in_flight = false;
    {
        std::lock_guard<std::mutex> lock(sync_mtx);
        still_in_flight = frame_in_flight;
    }
    if (!ok || still_in_flight) {
        // Guest timed out or is still mid-tick: signal abort and keep resim_steps alive
        // until frame_in_flight drains on the next step_frame() or stop_netplay().
        resim_abort.store(true, std::memory_order_release);
        return false;
    }

    resim_active.store(false, std::memory_order_release);
    resim_steps.clear();
    if (mem.in_bounds(kNetFastForwardVa, 4u)) {
        mem.w32(kNetFastForwardVa, 0u);
    }
    d3d_bridge.set_skip_render(false);
    return true;
}

void RuntimeEngine::Impl::poll_and_apply_match_packets(const CccasterSessionStatus& cs, bool in_match) {
    WireInitialGameState igs{};
    while (net_client.pop_remote_initial_game_state(igs)) {
        if (!cs.is_host) {
            apply_initial_game_state(mem, igs);
        }
    }

    WireRngState wrng{};
    while (net_client.pop_remote_rng_state(wrng)) {
        if (!cs.is_host && (!in_match || !rng_installed_this_match)) {
            const RngStateBlock rng = from_wire_rng(wrng);
            apply_rng_state(mem, rng);
            if (in_match) {
                rng_installed_this_match = true;
            }
        }
    }
}

void RuntimeEngine::Impl::check_and_exchange_sync_hashes() {
    WireSyncHash wsh{};
    while (net_client.pop_remote_sync_hash(wsh)) {
        const SyncHashData rsh = from_wire_sync_hash(wsh);
        const bool confirmed = (last_contig_confirmed != 0xFFFFFFFFu) &&
                               (rsh.indexed_frame <= last_contig_confirmed);
        const NetFrameSlot* sl = confirmed ? slot_for(rsh.indexed_frame) : nullptr;
        if (sl != nullptr && sl->sync_hash_valid) {
            if (!sl->local_sync_hash.matches_gameplay(rsh)) {
                netplay_desyncs.fetch_add(1u, std::memory_order_relaxed);
                hle_win32_log("[Netplay] SyncHash DESYNC at frame %u", rsh.indexed_frame);
            }
        } else {
            if (pending_remote_hashes.size() >= 64u) {
                pending_remote_hashes.erase(pending_remote_hashes.begin());
            }
            pending_remote_hashes[rsh.indexed_frame] = rsh;
        }
    }

    if (last_contig_confirmed == 0xFFFFFFFFu) {
        return;
    }
    const uint32_t scan_begin = (last_contig_confirmed > 120u) ? (last_contig_confirmed - 120u) : 0u;
    for (uint32_t f = scan_begin; f <= last_contig_confirmed; ++f) {
        if (f == 0u || (f % 30u) != 0u) continue;
        NetFrameSlot* sl = slot_for(f);
        if (sl == nullptr || !sl->sync_hash_valid) continue;

        if (auto it = pending_remote_hashes.find(f); it != pending_remote_hashes.end()) {
            if (!sl->local_sync_hash.matches_gameplay(it->second)) {
                netplay_desyncs.fetch_add(1u, std::memory_order_relaxed);
                hle_win32_log("[Netplay] SyncHash DESYNC (confirmed) at frame %u", f);
            }
            pending_remote_hashes.erase(it);
        }
        if (!sl->sync_hash_sent) {
            net_client.send_sync_hash(to_wire_sync_hash(sl->local_sync_hash));
            sl->sync_hash_sent = true;
        }
    }
}

bool RuntimeEngine::Impl::start_netplay_role(NetplayMode role, const NetplayConfig& config) {
    if (!initialized.load(std::memory_order_acquire) ||
        !running.load(std::memory_order_acquire)) {
        std::lock_guard<std::mutex> lk(net_err_mtx);
        net_last_error = "RuntimeEngine not running";
        return false;
    }

    // Stop any previous Netplay session cleanly before starting a new role.
    stop_net_poll_thread();
    net_client.disconnect();
    netplay_active.store(false, std::memory_order_release);
    netplay_in_match.store(false, std::memory_order_release);
    in_match_prev = false;
    restore_keybinds_if_saved();
    input_set_netplay_override(false);
    audio_rollback_set_tracking(false, 0u);
    d3d_bridge.set_skip_render(false);
    if (mem.in_bounds(kNetFastForwardVa, 4u)) {
        mem.w32(kNetFastForwardVa, 0u);
    }
    register_dispatch_netplay_overrides(false);

    const int clamped_rb = std::clamp(config.max_rollback, 0,
        static_cast<int>(NetplayRollbackEngine::kMaxRingFrames - 1u));
    if (!net_rollback.allocate_session(static_cast<size_t>(clamped_rb))) {
        std::lock_guard<std::mutex> lk(net_err_mtx);
        net_last_error = "Failed to allocate rollback ring buffer";
        return false;
    }

    reset_match_tracking();
    netplay_rollbacks.store(0u, std::memory_order_relaxed);
    netplay_desyncs.store(0u, std::memory_order_relaxed);
    netplay_cfg_delay.store(config.delay_frames, std::memory_order_relaxed);
    netplay_cfg_max_rollback.store(clamped_rb, std::memory_order_relaxed);
    netplay_training.store(config.training_mode, std::memory_order_relaxed);

    CccasterSessionConfig scfg{};
    scfg.peer_ip       = config.peer_ip;
    scfg.port          = config.port;
    scfg.player_name   = config.player_name.empty() ? std::string("iOS") : config.player_name;
    scfg.delay_frames  = (config.delay_frames < 0) ? -1 : std::clamp(config.delay_frames, 0, 254);
    scfg.max_rollback  = clamped_rb;
    scfg.training_mode = config.training_mode;

    bool started = false;
    if (role == NetplayMode::Host) {
        started = net_client.start_host(scfg);
    } else if (role == NetplayMode::Join) {
        started = net_client.start_join(scfg);
    } else if (role == NetplayMode::Spectate) {
        started = net_client.start_spectate(scfg);
    }

    if (!started) {
        const CccasterSessionStatus cs = net_client.status();
        {
            std::lock_guard<std::mutex> lk(net_err_mtx);
            net_last_error = cs.last_error.empty() ? std::string("Failed to start netplay socket") : cs.last_error;
        }
        net_rollback.release_session();
        netplay_mode.store(NetplayMode::Offline, std::memory_order_release);
        return false;
    }

    {
        std::lock_guard<std::mutex> lk(net_err_mtx);
        net_last_error.clear();
    }
    netplay_mode.store(role, std::memory_order_release);
    register_dispatch_netplay_overrides(true);
    netplay_active.store(true, std::memory_order_release);
    start_net_poll_thread();
    return true;
}

bool RuntimeEngine::Impl::step_netplay_frame() {
    net_client.poll();
    const CccasterSessionStatus cs = net_client.status();

    const bool connected_now = cs.connected;
    const bool in_match_now = connected_now &&
        mem.in_bounds(kNetBattleFlagVa, 4u) &&
        (mem.r32(kNetBattleFlagVa) == 1u);

    poll_and_apply_match_packets(cs, in_match_now);
    netplay_in_match.store(in_match_now, std::memory_order_release);

    if (!in_match_now) {
        if (in_match_prev) {
            restore_keybinds_if_saved();
            input_set_netplay_override(false);
            audio_rollback_set_tracking(false, 0u);
            d3d_bridge.set_skip_render(false);
            if (mem.in_bounds(kNetFastForwardVa, 4u)) {
                mem.w32(kNetFastForwardVa, 0u);
            }
            in_match_prev = false;
            reset_match_tracking();
        }
        if (d3d_initialized) {
            d3d_bridge.begin_frame();
        }
        return execute_guest_single_tick(100u);
    }

    // Active combat match under Netplay control
    const int cfg_delay = netplay_cfg_delay.load(std::memory_order_relaxed);
    const uint32_t delay = static_cast<uint32_t>(
        std::clamp((cfg_delay >= 0) ? cfg_delay : cs.delay_frames, 0, 254));
    const uint32_t max_rb = static_cast<uint32_t>(
        std::clamp(cs.max_rollback, 0, static_cast<int>(NetplayRollbackEngine::kMaxRingFrames - 1u)));
    net_rollback.set_max_rollback_frames(max_rb);

    if (!in_match_prev) {
        in_match_prev = true;
        reset_match_tracking();
        save_and_zero_keybinds();
        if (mem.in_bounds(kNetFocusEscapeVa, 1u)) {
            mem.w8(kNetFocusEscapeVa, 0u);
        }
        input_set_netplay_override(true);

        if (cs.is_host) {
            net_client.send_initial_game_state(capture_initial_game_state(mem));
            RngStateBlock rng{};
            if (capture_rng_state(mem, rng)) {
                net_client.send_rng_state(to_wire_rng(rng, 0u));
            }
            rng_sent_this_match = true;
            rng_installed_this_match = true;
        } else {
            // Re-drain in case initial game/RNG packets arrived on transition
            poll_and_apply_match_packets(cs, true);
        }

        // Seed initial delayed local frames with neutral inputs so peer frames 0..delay-1 never stall
        if (cs.mode != CccasterClientMode::SpectateNetplay) {
            for (uint32_t f = 0u; f < delay; ++f) {
                NetFrameSlot& sl = alloc_slot(f);
                sl.local_word = 0u;
                sl.local_sent = true;
                net_client.submit_local_input(f, 0u);
            }
        }
        net_rollback.save_frame(mem, 0u);
    }

    // Keep P1 local raw keybind table zeroed and escape bit clear throughout combat
    if (mem.in_bounds(kNetInputKeyTableVa, kNetKeyTableBytes)) {
        mem.zero_bytes(kNetInputKeyTableVa, kNetKeyTableBytes);
    }
    if (mem.in_bounds(kNetFocusEscapeVa, 1u)) {
        mem.w8(kNetFocusEscapeVa, 0u);
    }

    const uint32_t cur_f = netplay_frame.load(std::memory_order_relaxed);

    // Spectate branch: wait for confirmed BothInputs packet for `cur_f` and step deterministically
    if (cs.mode == CccasterClientMode::SpectateNetplay) {
        uint16_t p1_w = 0u;
        uint16_t p2_w = 0u;
        if (!net_client.get_spectate_inputs(cur_f, p1_w, p2_w)) {
            return false; // Hold display frame until spectator stream catches up
        }
        input_inject_netplay_pair(mem, p1_w, p2_w, true);
        audio_rollback_set_tracking(false, cur_f);
        if (d3d_initialized) {
            d3d_bridge.begin_frame();
        }
        if (!execute_guest_single_tick(100u)) {
            return false;
        }
        netplay_frame.store(cur_f + 1u, std::memory_order_release);
        return true;
    }

    // Host / Join branch: always submit local input for `cur_f + delay`
    const uint16_t local_now = input_encode_local_word();
    const uint32_t send_f = cur_f + delay;
    {
        NetFrameSlot& send_sl = alloc_slot(send_f);
        if (!send_sl.local_sent) {
            send_sl.local_word = local_now;
            send_sl.local_sent = true;
        }
        net_client.submit_local_input(send_f, send_sl.local_word);
    }

    // Check newly confirmed remote inputs over [scan_start .. cur_f) for mispredictions
    const uint32_t scan_start = (cur_f > max_rb) ? (cur_f - max_rb) : 0u;
    uint32_t first_mispred = cur_f;
    uint16_t mispred_actual_word = last_remote_word;

    for (uint32_t f = scan_start; f < cur_f; ++f) {
        NetFrameSlot* sl = slot_for(f);
        if (sl == nullptr) continue;
        if (!sl->remote_confirmed) {
            uint16_t actual = 0u;
            if (net_client.get_remote_input(f, actual)) {
                actual = cccaster_sanitize_input_word(actual, false);
                sl->remote_confirmed = true;
                last_remote_word = actual;
                if (actual != sl->remote_word && first_mispred == cur_f) {
                    first_mispred = f;
                    mispred_actual_word = actual;
                }
                sl->remote_word = actual;
            }
        } else {
            last_remote_word = sl->remote_word;
        }
    }

    // Advance contiguous confirmed watermark cleanly
    while (true) {
        const uint32_t next_c = (last_contig_confirmed == 0xFFFFFFFFu) ? 0u : (last_contig_confirmed + 1u);
        if (next_c >= cur_f) break;
        NetFrameSlot* sl = slot_for(next_c);
        if (sl != nullptr && sl->remote_confirmed) {
            last_contig_confirmed = next_c;
        } else {
            break;
        }
    }

    // Execute rollback + silent resimulation if an earlier predicted frame mispredicted
    bool did_rollback = false;
    if (first_mispred < cur_f) {
        // Propagate updated prediction forward to later unconfirmed frames > first_mispred
        const uint16_t prop_pred = static_cast<uint16_t>(mispred_actual_word & 0x7DFFu);
        for (uint32_t f = first_mispred + 1u; f < cur_f; ++f) {
            NetFrameSlot* sl = slot_for(f);
            if (sl != nullptr && !sl->remote_confirmed) {
                sl->remote_word = prop_pred;
            }
        }
        netplay_rollbacks.fetch_add(1u, std::memory_order_relaxed);
        if (!run_resim_burst(first_mispred, cur_f)) {
            return false;
        }
        did_rollback = true;
    }

    // Check max rollback distance throttle before advancing cur_f
    uint16_t cur_remote = 0u;
    const bool got_cur_remote = net_client.get_remote_input(cur_f, cur_remote);
    if (got_cur_remote) {
        cur_remote = cccaster_sanitize_input_word(cur_remote, false);
        last_remote_word = cur_remote;
    } else {
        const uint32_t first_unconfirmed = (last_contig_confirmed == 0xFFFFFFFFu)
            ? 0u : (last_contig_confirmed + 1u);
        if (max_rb == 0u || cur_f >= first_unconfirmed + max_rb) {
            // Remote peer is at max rollback horizon: stall advancement gracefully and resend inputs
            check_and_exchange_sync_hashes();
            return false;
        }
        cur_remote = static_cast<uint16_t>(last_remote_word & 0x7DFFu);
    }

    // Record resolved/predicted input pair for cur_f
    NetFrameSlot& cur_sl = alloc_slot(cur_f);
    cur_sl.remote_word      = cur_remote;
    cur_sl.remote_confirmed = got_cur_remote;
    if (!cur_sl.local_sent) {
        cur_sl.local_word = local_now;
        cur_sl.local_sent = true;
        net_client.submit_local_input(cur_f, cur_sl.local_word);
    }
    if (got_cur_remote && (last_contig_confirmed == 0xFFFFFFFFu ? cur_f == 0u : cur_f == last_contig_confirmed + 1u)) {
        last_contig_confirmed = cur_f;
    }

    // Broadcast newly confirmed (P1, P2) frames to spectators if hosting
    if (cs.is_host && cs.spectator_count > 0u && last_contig_confirmed != 0xFFFFFFFFu) {
        const uint32_t start_b = (last_broadcast_frame == 0xFFFFFFFFu)
            ? ((last_contig_confirmed > 16u) ? (last_contig_confirmed - 16u) : 0u)
            : (last_broadcast_frame + 1u);
        for (uint32_t bf = start_b; bf <= last_contig_confirmed; ++bf) {
            const NetFrameSlot* bsl = slot_for(bf);
            if (bsl != nullptr && bsl->local_sent && bsl->remote_confirmed) {
                const bool local_p1 = (cs.local_player_index != 1);
                const uint16_t bp1 = local_p1 ? bsl->local_word : bsl->remote_word;
                const uint16_t bp2 = local_p1 ? bsl->remote_word : bsl->local_word;
                net_client.broadcast_both_inputs(bf, bp1, bp2);
                last_broadcast_frame = bf;
            }
        }
    }

    // Save pre-step snapshot at start of cur_f (and SyncHash every 30 frames)
    net_rollback.save_frame(mem, cur_f);
    if (cur_f > 0u && (cur_f % 30u) == 0u) {
        SyncHashData sh{};
        const uint32_t rflags = mem.in_bounds(kNetGameModeVa, 4u) ? mem.r32(kNetGameModeVa) : 0u;
        if (build_sync_hash(mem, cur_f, rflags, sh)) {
            cur_sl.local_sync_hash = sh;
            cur_sl.sync_hash_valid = true;
            cur_sl.sync_hash_sent  = false;
        }
    }
    check_and_exchange_sync_hashes();

    // Inject P1/P2 pair and step one live visual frame (unmuting audio & merging catchup SFX)
    if (did_rollback) {
        audio_rollback_prepare_live_catchup(mem);
    }
    const bool local_is_p1 = (cs.local_player_index != 1);
    const uint16_t p1_w = local_is_p1 ? cur_sl.local_word : cur_sl.remote_word;
    const uint16_t p2_w = local_is_p1 ? cur_sl.remote_word : cur_sl.local_word;
    input_inject_netplay_pair(mem, p1_w, p2_w, false);
    audio_rollback_set_tracking(true, cur_f);

    if (d3d_initialized) {
        d3d_bridge.begin_frame();
    }
    const bool step_ok = execute_guest_single_tick(100u);
    audio_rollback_end_catchup();
    if (!step_ok) {
        return false;
    }

    netplay_frame.store(cur_f + 1u, std::memory_order_release);
    return true;
}

void RuntimeEngine::step_frame() {
    if (!impl_->initialized.load(std::memory_order_acquire) ||
        !impl_->running.load(std::memory_order_acquire)) {
        return;
    }

    @autoreleasepool {
        input_poll_platform();
        audio_update_streams();

        Impl* impl_ptr = impl_.get();
        auto guest_done = [impl_ptr]() {
            return impl_ptr->phase == Impl::StepPhase::GuestYielded ||
                   impl_ptr->phase == Impl::StepPhase::GuestExited;
        };
        auto finish_frame = [this]() {
            if (impl_->d3d_initialized) {
                impl_->d3d_bridge.end_frame_and_present();
            }
            const uint64_t fno = impl_->frame_count.fetch_add(1u, std::memory_order_relaxed) + 1u;
            if (fno == 1u || fno == 60u || fno == 300u) {
                hle_win32_log("Frame %llu | active=%u | %s",
                              static_cast<unsigned long long>(fno),
                              static_cast<unsigned>(impl_->mem.r8(0x0076e650u)),
                              impl_->d3d_bridge.debug_stats().c_str());
            }
        };

        {
            std::unique_lock<std::mutex> lock(impl_->sync_mtx);
            if (impl_->frame_in_flight) {
                if (!impl_->host_cv.wait_for(lock, std::chrono::milliseconds(16), guest_done)) {
                    return;
                }
                impl_->frame_in_flight = false;
                if (impl_->phase == Impl::StepPhase::GuestExited) {
                    impl_->running.store(false, std::memory_order_release);
                }
                const bool was_resim = impl_->resim_active.exchange(false, std::memory_order_acq_rel) ||
                                       impl_->resim_abort.exchange(false, std::memory_order_acq_rel);
                if (was_resim) {
                    impl_->resim_steps.clear();
                }
                lock.unlock();
                if (was_resim) {
                    if (impl_->mem.in_bounds(kNetFastForwardVa, 4u)) {
                        impl_->mem.w32(kNetFastForwardVa, 0u);
                    }
                    impl_->d3d_bridge.set_skip_render(false);
                    if (!impl_->netplay_active.load(std::memory_order_acquire)) {
                        impl_->net_rollback.release_session();
                    }
                    return;
                }
                finish_frame();
                return;
            }

            if (!impl_->host_cv.wait_for(lock, std::chrono::milliseconds(16), guest_done)) {
                return;
            }
            if (impl_->phase == Impl::StepPhase::GuestExited) {
                impl_->running.store(false, std::memory_order_release);
                return;
            }
        }

        if (impl_->netplay_active.load(std::memory_order_acquire)) {
            if (!impl_->step_netplay_frame()) {
                return;
            }
            finish_frame();
            return;
        }

        if (impl_->d3d_initialized) {
            impl_->d3d_bridge.begin_frame();
        }
        if (!impl_->execute_guest_single_tick(100u)) {
            return;
        }
        finish_frame();
    }
}

void RuntimeEngine::set_touch_state(const TouchInputState& state) {
    input_set_touch_state(state);
}

void RuntimeEngine::handle_memory_warning() {
    std::fprintf(stderr, "[RuntimeEngine] iOS memory warning received.\n");
    if (impl_->d3d_initialized) {
        impl_->d3d_bridge.evict_on_memory_warning();
    }
}

void RuntimeEngine::resize_drawable(int width, int height) {
    if (!impl_) return;
    if (width > 0)  impl_->width  = width;
    if (height > 0) impl_->height = height;
    if (impl_->d3d_initialized) {
        impl_->d3d_bridge.resize(impl_->width, impl_->height);
    }
}

bool RuntimeEngine::start_netplay_host(const NetplayConfig& config) {
    return impl_ ? impl_->start_netplay_role(NetplayMode::Host, config) : false;
}

bool RuntimeEngine::start_netplay_join(const NetplayConfig& config) {
    return impl_ ? impl_->start_netplay_role(NetplayMode::Join, config) : false;
}

bool RuntimeEngine::start_netplay_spectate(const NetplayConfig& config) {
    return impl_ ? impl_->start_netplay_role(NetplayMode::Spectate, config) : false;
}

void RuntimeEngine::stop_netplay() {
    if (!impl_) return;

    impl_->stop_net_poll_thread();
    impl_->netplay_active.store(false, std::memory_order_release);
    impl_->netplay_in_match.store(false, std::memory_order_release);
    impl_->netplay_mode.store(NetplayMode::Offline, std::memory_order_release);
    impl_->resim_abort.store(true, std::memory_order_release);
    impl_->net_client.disconnect();

    // Wait for any active or timed-out resimulation tick on guest_thread to yield cleanly
    // before mutating resim_steps or restoring guest memory overrides.
    bool guest_yielded = true;
    if (impl_->initialized.load(std::memory_order_acquire) && impl_->guest_thread.joinable()) {
        std::unique_lock<std::mutex> lock(impl_->sync_mtx);
        guest_yielded = impl_->host_cv.wait_for(lock, std::chrono::milliseconds(500), [this]() {
            return !impl_->frame_in_flight ||
                   impl_->phase == Impl::StepPhase::GuestYielded ||
                   impl_->phase == Impl::StepPhase::GuestExited;
        });
    }

    if (guest_yielded) {
        impl_->resim_active.store(false, std::memory_order_release);
        impl_->resim_abort.store(false, std::memory_order_release);
        impl_->resim_steps.clear();
        impl_->in_match_prev = false;
        impl_->restore_keybinds_if_saved();
        if (impl_->mem.in_bounds(kNetFastForwardVa, 4u)) {
            impl_->mem.w32(kNetFastForwardVa, 0u);
        }
        impl_->net_rollback.release_session(); // Immediately returns ~19.8 MiB to iOS (0 B offline)
    }
    input_set_netplay_override(false);
    audio_rollback_set_tracking(false, 0u);
    impl_->d3d_bridge.set_skip_render(false);
    register_dispatch_netplay_overrides(false);
}

NetplayStatus RuntimeEngine::netplay_status() const {
    NetplayStatus out{};
    if (!impl_) return out;

    const NetplayMode mode = impl_->netplay_mode.load(std::memory_order_acquire);
    const CccasterSessionStatus cs = impl_->net_client.status();

    out.mode           = mode;
    out.state          = static_cast<NetplayConnState>(static_cast<uint8_t>(cs.state));
    out.active         = impl_->netplay_active.load(std::memory_order_acquire) || cs.active;
    out.connected      = cs.connected;
    out.in_match       = impl_->netplay_in_match.load(std::memory_order_acquire);
    out.local_port     = cs.local_port;
    out.local_ipv4     = cs.local_ipv4.empty() ? cccaster_get_local_ipv4() : cs.local_ipv4;
    out.peer_addr      = cs.peer_addr;
    out.peer_name      = cs.peer_name;
    out.ping_ms        = cs.ping_ms;
    out.one_way_ms     = cs.one_way_ms;
    out.delay_frames   = cs.delay_frames;
    out.max_rollback   = cs.max_rollback;
    out.current_frame  = impl_->netplay_frame.load(std::memory_order_relaxed);
    out.rollback_count = impl_->netplay_rollbacks.load(std::memory_order_relaxed);
    out.desync_count   = impl_->netplay_desyncs.load(std::memory_order_relaxed);
    out.state_label    = cs.state_label;

    {
        std::lock_guard<std::mutex> lk(impl_->net_err_mtx);
        out.last_error = !cs.last_error.empty() ? cs.last_error : impl_->net_last_error;
    }
    return out;
}

std::string RuntimeEngine::get_local_ipv4() {
    return cccaster_get_local_ipv4();
}

void RuntimeEngine::shutdown() {
    if (!impl_) return;

    impl_->stop_net_poll_thread();
    impl_->netplay_active.store(false, std::memory_order_release);
    impl_->netplay_in_match.store(false, std::memory_order_release);
    impl_->netplay_mode.store(NetplayMode::Offline, std::memory_order_release);
    impl_->resim_abort.store(true, std::memory_order_release);
    impl_->net_client.disconnect();

    const bool was_init = impl_->initialized.exchange(false, std::memory_order_acq_rel);
    impl_->running.store(false, std::memory_order_release);

    if (was_init || impl_->guest_thread.joinable()) {
        hle_win32_post_quit(0);
        {
            std::lock_guard<std::mutex> lock(impl_->sync_mtx);
            impl_->stop_requested = true;
            impl_->guest_cv.notify_all();
        }

        bool joined_cleanly = true;
        if (impl_->guest_thread.joinable()) {
            bool exited = false;
            {
                std::unique_lock<std::mutex> lock(impl_->sync_mtx);
                exited = impl_->host_cv.wait_for(
                    lock, std::chrono::milliseconds(1500),
                    [this]() { return impl_->phase == Impl::StepPhase::GuestExited; });
            }
            if (exited) {
                impl_->guest_thread.join();
            } else {
                joined_cleanly = false;
                impl_->guest_detached = true;
                hle_win32_log(
                    "RuntimeEngine::shutdown: guest thread did not exit within 1500ms; "
                    "detaching to prevent iOS FrontBoard watchdog 0x8BADF00D");
                impl_->guest_thread.detach();
            }
        }

        {
            std::lock_guard<std::mutex> lock(impl_->sync_mtx);
            if (joined_cleanly) {
                impl_->phase = Impl::StepPhase::Idle;
                impl_->stop_requested = false;
                impl_->frame_in_flight = false;
            }
        }

        if (joined_cleanly) {
            impl_->resim_active.store(false, std::memory_order_release);
            impl_->resim_steps.clear();
            impl_->restore_keybinds_if_saved();
            impl_->net_rollback.release_session();
        }
        input_set_netplay_override(false);
        audio_rollback_set_tracking(false, 0u);
        register_dispatch_netplay_overrides(false);

        audio_shutdown();
        input_shutdown();
        hle_win32_register_d3d_handler(nullptr);
        if (D3D9MetalBridge::active() == &impl_->d3d_bridge) {
            D3D9MetalBridge::set_active(nullptr);
        }
        if (joined_cleanly) {
            if (impl_->d3d_initialized) {
                impl_->d3d_bridge.shutdown();
                impl_->d3d_initialized = false;
            }
            hle_win32_shutdown();
            clear_dispatch_table();
            impl_->rollback.clear_history();
            impl_->mem.shutdown();
        } else {
            hle_win32_set_frame_yield_callback(nullptr);
        }
    }
}

bool RuntimeEngine::is_initialized() const noexcept {
    return impl_->initialized.load(std::memory_order_acquire);
}

bool RuntimeEngine::is_running() const noexcept {
    return impl_->running.load(std::memory_order_acquire);
}

uint64_t RuntimeEngine::frame_count() const noexcept {
    return impl_->frame_count.load(std::memory_order_relaxed);
}

const std::string& RuntimeEngine::last_error() const noexcept {
    return impl_->last_error;
}

std::string RuntimeEngine::debug_summary() const {
    if (!impl_) return "RuntimeEngine uninitialized";
    char hdr[384] = {};
    std::snprintf(
        hdr, sizeof(hdr),
        "frames=%llu running=%d active[0x76e650]=%u\n"
        "d3d_ctx=0x%08x d3d_dev=0x%08x dinput8=0x%08x rt0=0x%08x heap=%.1fMB\n",
        static_cast<unsigned long long>(impl_->frame_count.load(std::memory_order_relaxed)),
        impl_->running.load(std::memory_order_relaxed) ? 1 : 0,
        static_cast<unsigned>(impl_->mem.r8(0x0076e650u)),
        impl_->mem.r32(0x00767448u),
        impl_->mem.r32(0x0076e7d4u),
        impl_->mem.r32(0x005544e8u),
        impl_->mem.r32(0x005542d0u),
        static_cast<double>(impl_->mem.heap_used_bytes()) / (1024.0 * 1024.0));

    std::string out(hdr);
    out += impl_->d3d_bridge.debug_stats();
    out += "\n--- Logs ---\n";
    out += hle_win32_recent_logs(10u);
    return out;
}

CpuContext& RuntimeEngine::cpu_context() noexcept {
    return impl_->ctx;
}

GuestMemory& RuntimeEngine::guest_memory() noexcept {
    return impl_->mem;
}

RollbackManager& RuntimeEngine::rollback_manager() noexcept {
    return impl_->rollback;
}

} // namespace mbaa_recomp
