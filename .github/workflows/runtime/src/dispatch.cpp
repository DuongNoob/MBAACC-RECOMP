#include "mbaa_recomp/dispatch.h"
#include "mbaa_recomp/hle_crt.h"
#include "mbaa_recomp/hle_input.h"
#include "mbaa_recomp/hle_win32.h"
#include "mbaa_recomp/netplay_rollback.h"

#include <atomic>
#include <cstdio>
#include <mutex>
#include <shared_mutex>
#include <unordered_map>

namespace mbaa_recomp {

namespace {

std::shared_mutex g_dispatch_mutex;
std::unordered_map<uint32_t, RecompFn> g_fn_table;
std::unordered_map<uint32_t, RecompFn> g_com_thunks;
std::atomic<uint32_t> g_next_com_thunk{GuestMemory::kComThunkBase};
std::atomic<uint32_t> g_unresolved_calls{0};

// Netplay indirect-dispatch hook for PollInputDevice (0x004a00b0, invoked via
// vtable slot +0x14 inside sub_0041f080). Pass-through when offline.
// Direct C++ calls in build_gen/ (sub_004330c0/sub_004bdbc0 frame limiter, etc.)
// are governed via [0x0055D25C] and HLE boundaries without editing build_gen/.
RecompFn g_orig_004a00b0 = nullptr;

void netplay_wrap_004a00b0(CpuContext& ctx, GuestMemory& mem) {
    if (input_handle_poll_input_device(ctx, mem)) {
        return;
    }
    if (g_orig_004a00b0 != nullptr) {
        g_orig_004a00b0(ctx, mem);
    }
}

} // namespace

void register_dispatch_netplay_overrides(bool active) {
    std::unique_lock<std::shared_mutex> lock(g_dispatch_mutex);
    auto it = g_fn_table.find(0x004A00B0u);
    if (it == g_fn_table.end()) return;
    if (active) {
        if (it->second != &netplay_wrap_004a00b0) {
            g_orig_004a00b0 = it->second;
            it->second = &netplay_wrap_004a00b0;
        }
    } else if (g_orig_004a00b0 != nullptr) {
        it->second = g_orig_004a00b0;
    }
}

void register_function(uint32_t va, RecompFn fn) {
    if (fn == nullptr) return;
    std::unique_lock<std::shared_mutex> lock(g_dispatch_mutex);
    g_fn_table[va] = fn;
}

void register_com_thunk(uint32_t thunk_va, RecompFn fn) {
    if (fn == nullptr) return;
    std::unique_lock<std::shared_mutex> lock(g_dispatch_mutex);
    g_com_thunks[thunk_va] = fn;
}

uint32_t alloc_com_method_thunk(RecompFn fn) {
    const uint32_t va = g_next_com_thunk.fetch_add(4u, std::memory_order_relaxed);
    register_com_thunk(va, fn);
    return va;
}

RecompFn lookup_function(uint32_t va) {
    std::shared_lock<std::shared_mutex> lock(g_dispatch_mutex);
    if (auto it = g_fn_table.find(va); it != g_fn_table.end()) {
        return it->second;
    }
    if (auto cit = g_com_thunks.find(va); cit != g_com_thunks.end()) {
        return cit->second;
    }
    return nullptr;
}

void clear_dispatch_table() {
    std::unique_lock<std::shared_mutex> lock(g_dispatch_mutex);
    g_fn_table.clear();
    g_com_thunks.clear();
    g_next_com_thunk.store(GuestMemory::kComThunkBase, std::memory_order_relaxed);
    g_unresolved_calls.store(0u, std::memory_order_relaxed);
    g_orig_004a00b0 = nullptr;
}

void call_indirect(CpuContext& ctx, GuestMemory& mem, uint32_t target_va) {
    if (target_va == 0u) {
        const uint32_t cnt = g_unresolved_calls.fetch_add(1u, std::memory_order_relaxed) + 1u;
        if (cnt <= 30u) {
            hle_win32_log("[dispatch] call_indirect(0x00000000) eip=0x%08x esp=0x%08x (#%u)",
                          ctx.eip, ctx.esp, cnt);
        }
        ctx.ret_cdecl(mem);
        return;
    }

    // Check if target is an IAT slot or synthetic IAT thunk
    const uint32_t iat_va = hle_thunk_to_iat_va(target_va);
    if (iat_va != 0u) {
        hle_iat_call(ctx, mem, iat_va);
        return;
    }
    if (target_va >= GuestMemory::kIatRangeStart && target_va < GuestMemory::kIatRangeEnd) {
        hle_iat_call(ctx, mem, target_va);
        return;
    }

    if (RecompFn fn = lookup_function(target_va); fn != nullptr) {
        fn(ctx, mem);
        return;
    }

    // Fall back to CRT dispatcher if target is a known CRT VA
    if (target_va >= 0x004E00D0u && target_va < 0x0051A18Fu) {
        hle_crt_dispatch(ctx, mem, target_va);
        return;
    }

    const uint32_t cnt = g_unresolved_calls.fetch_add(1u, std::memory_order_relaxed) + 1u;
    if (cnt <= 30u) {
        hle_win32_log("[dispatch] unresolved call_indirect(0x%08x) esp=0x%08x (#%u)",
                      target_va, ctx.esp, cnt);
    }
    ctx.ret_cdecl(mem);
}

void jump_indirect(CpuContext& ctx, GuestMemory& mem, uint32_t target_va) {
    // Tail-call or function-pointer jump: stack already holds caller's return address.
    call_indirect(ctx, mem, target_va);
}

} // namespace mbaa_recomp
