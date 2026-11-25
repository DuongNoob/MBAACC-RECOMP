#include "mbaa_recomp/dispatch.h"
#include "mbaa_recomp/hle_crt.h"
#include "mbaa_recomp/hle_win32.h"

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

} // namespace

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
}

void call_indirect(CpuContext& ctx, GuestMemory& mem, uint32_t target_va) {
    if (target_va == 0u) {
        std::fprintf(stderr, "[mbaa_recomp] call_indirect(0x00000000) from eip=0x%08x\n", ctx.eip);
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

    std::fprintf(stderr, "[mbaa_recomp] unresolved call_indirect(0x%08x) esp=0x%08x\n", target_va, ctx.esp);
    ctx.ret_cdecl(mem);
}

void jump_indirect(CpuContext& ctx, GuestMemory& mem, uint32_t target_va) {
    // Tail-call or function-pointer jump: stack already holds caller's return address.
    call_indirect(ctx, mem, target_va);
}

} // namespace mbaa_recomp
