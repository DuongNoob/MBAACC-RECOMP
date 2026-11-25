#pragma once

/**
 * @file dispatch.h
 * @brief Function registry, indirect call/jump dispatch, and COM/IAT thunk resolution.
 */

#include "mbaa_recomp/cpu_context.h"
#include "mbaa_recomp/guest_memory.h"

#include <cstdint>

namespace mbaa_recomp {

using RecompFn = void (*)(CpuContext&, GuestMemory&);

/// Registers a lifted game function or hook at exact 32-bit guest virtual address `va`.
void register_function(uint32_t va, RecompFn fn);

/// Registers a synthetic COM vtable method thunk inside 0x00F00000..0x00FFFFFF.
void register_com_thunk(uint32_t thunk_va, RecompFn fn);

/// Allocates and registers a synthetic COM method address in 0x00F40000..0x00FDFFFF.
uint32_t alloc_com_method_thunk(RecompFn fn);

/// Returns registered function pointer for `va`, or nullptr if not registered.
[[nodiscard]] RecompFn lookup_function(uint32_t va);

/// Clears all registered functions/thunks (used on shutdown/re-init).
void clear_dispatch_table();

/// Dispatches an indirect x86 `call r32` / `call [mem]` targeting `target_va`.
/// Supports lifted game functions, CRT VAs, synthetic COM method thunks, and IAT thunks.
void call_indirect(CpuContext& ctx, GuestMemory& mem, uint32_t target_va);

/// Dispatches an indirect x86 `jmp r32` / `jmp [mem]` (tail-call / switch jump / thunk).
void jump_indirect(CpuContext& ctx, GuestMemory& mem, uint32_t target_va);

/// Populated by recompiler-generated `build_gen/gen_dispatch.cpp`.
void register_recomp_functions();

} // namespace mbaa_recomp
