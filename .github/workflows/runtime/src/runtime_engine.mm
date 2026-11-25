#import <Foundation/Foundation.h>
#import <QuartzCore/CAMetalLayer.h>

#include "mbaa_recomp/runtime_engine.h"
#include "mbaa_recomp/d3d9_shim.h"
#include "mbaa_recomp/dispatch.h"
#include "mbaa_recomp/hle_audio.h"
#include "mbaa_recomp/hle_crt.h"
#include "mbaa_recomp/hle_input.h"
#include "mbaa_recomp/hle_win32.h"

#include <atomic>
#include <cctype>
#include <condition_variable>
#include <cstdio>
#include <filesystem>
#include <mutex>
#include <string>
#include <thread>

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

void run_static_crt_initializers(CpuContext& ctx, GuestMemory& mem) {
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
    }
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
    bool guest_boot_ok = false;

    D3D9MetalBridge d3d_bridge;
    bool d3d_initialized = false;
};

RuntimeEngine::RuntimeEngine() : impl_(std::make_unique<Impl>()) {}

RuntimeEngine::~RuntimeEngine() {
    shutdown();
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
    input_init();
    audio_init();

    impl_->ctx.reset(GuestMemory::kInitialEsp, GuestMemory::kTebBase);

    Impl* impl_ptr = impl_.get();
    hle_win32_set_frame_yield_callback([impl_ptr]() -> bool {
        std::unique_lock<std::mutex> lock(impl_ptr->sync_mtx);
        impl_ptr->guest_boot_ok = true;
        impl_ptr->phase = Impl::StepPhase::GuestYielded;
        impl_ptr->host_cv.notify_all();

        impl_ptr->guest_cv.wait(lock, [impl_ptr]() {
            return impl_ptr->stop_requested ||
                   impl_ptr->phase == Impl::StepPhase::StepRequested;
        });

        if (impl_ptr->stop_requested || hle_win32_is_quit_requested()) {
            return false;
        }

        impl_ptr->phase = Impl::StepPhase::WaitGuestYield;
        return true;
    });

    {
        std::lock_guard<std::mutex> lock(impl_->sync_mtx);
        impl_->phase = Impl::StepPhase::WaitGuestYield;
        impl_->stop_requested = false;
    }

    impl_->initialized.store(true, std::memory_order_release);
    impl_->running.store(true, std::memory_order_release);

    impl_->guest_thread = std::thread([impl_ptr, win_main_fn]() {
        @autoreleasepool {
            hle_win32_set_guest_main_thread();

            run_static_crt_initializers(impl_ptr->ctx, impl_ptr->mem);

            const uint32_t cmdline_va = impl_ptr->mem.alloc_thunk_block(16u, 4u);
            impl_ptr->mem.write_cstring(cmdline_va, "", 16u);

            // WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
            impl_ptr->ctx.push32(impl_ptr->mem, 10u);                    // nCmdShow = SW_SHOWDEFAULT
            impl_ptr->ctx.push32(impl_ptr->mem, cmdline_va);             // lpCmdLine
            impl_ptr->ctx.push32(impl_ptr->mem, 0u);                     // hPrevInstance
            impl_ptr->ctx.push32(impl_ptr->mem, GuestMemory::kImageBase);// hInstance
            impl_ptr->ctx.push32(impl_ptr->mem, kSentinelReturnVa);      // return address

            win_main_fn(impl_ptr->ctx, impl_ptr->mem);

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

void RuntimeEngine::step_frame() {
    if (!impl_->initialized.load(std::memory_order_acquire) ||
        !impl_->running.load(std::memory_order_acquire)) {
        return;
    }

    input_poll_platform();
    audio_update_streams();

    if (impl_->d3d_initialized) {
        impl_->d3d_bridge.begin_frame();
    }

    Impl* impl_ptr = impl_.get();
    {
        std::unique_lock<std::mutex> lock(impl_->sync_mtx);
        impl_->host_cv.wait(lock, [impl_ptr]() {
            return impl_ptr->phase == Impl::StepPhase::GuestYielded ||
                   impl_ptr->phase == Impl::StepPhase::GuestExited;
        });

        if (impl_->phase == Impl::StepPhase::GuestExited) {
            impl_->running.store(false, std::memory_order_release);
            if (impl_->d3d_initialized) {
                impl_->d3d_bridge.end_frame_and_present();
            }
            return;
        }

        impl_->phase = Impl::StepPhase::StepRequested;
        impl_->guest_cv.notify_one();

        impl_->host_cv.wait(lock, [impl_ptr]() {
            return impl_ptr->phase == Impl::StepPhase::GuestYielded ||
                   impl_ptr->phase == Impl::StepPhase::GuestExited;
        });

        if (impl_->phase == Impl::StepPhase::GuestExited) {
            impl_->running.store(false, std::memory_order_release);
        }
    }

    if (impl_->d3d_initialized) {
        impl_->d3d_bridge.end_frame_and_present();
    }

    impl_->frame_count.fetch_add(1u, std::memory_order_relaxed);
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

void RuntimeEngine::shutdown() {
    if (!impl_) return;

    const bool was_init = impl_->initialized.exchange(false, std::memory_order_acq_rel);
    impl_->running.store(false, std::memory_order_release);

    if (was_init || impl_->guest_thread.joinable()) {
        hle_win32_post_quit(0);
        {
            std::lock_guard<std::mutex> lock(impl_->sync_mtx);
            impl_->stop_requested = true;
            impl_->guest_cv.notify_all();
        }
        if (impl_->guest_thread.joinable()) {
            impl_->guest_thread.join();
        }
        {
            std::lock_guard<std::mutex> lock(impl_->sync_mtx);
            impl_->phase = Impl::StepPhase::Idle;
            impl_->stop_requested = false;
        }

        audio_shutdown();
        input_shutdown();
        hle_win32_register_d3d_handler(nullptr);
        if (D3D9MetalBridge::active() == &impl_->d3d_bridge) {
            D3D9MetalBridge::set_active(nullptr);
        }
        if (impl_->d3d_initialized) {
            impl_->d3d_bridge.shutdown();
            impl_->d3d_initialized = false;
        }
        hle_win32_shutdown();
        clear_dispatch_table();
        impl_->rollback.clear_history();
        impl_->mem.shutdown();
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
