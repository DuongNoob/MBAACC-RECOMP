// Auto-generated C++20 shard: gen_filepac.cpp (40 functions) — DO NOT EDIT

#include "recomp_funcs.h"

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

namespace mbaa_recomp {

// sub_00408180 | subsystem=FilePacFunc | canonical | 5 blocks | 26 insns
void sub_00408180(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00408180: mov ecx, dword ptr [esp + 4]
    uint32_t t0 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint32_t t1 = mem.r32(t0);
    ctx.ecx = static_cast<uint32_t>(t1);
    // 0x00408184: sub esp, 0xc
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x0000000cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x0000000cu, t2);
    ctx.esp = static_cast<uint32_t>(t2);
    // 0x00408187: test ecx, ecx
    uint32_t t3 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t3);
    // 0x00408189: ja 0x40819a
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_0040819a;
    goto bb_0040818b;
}
bb_0040819a: {
    // 0x0040819a: or eax, 0xffffffff
    uint32_t t4 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0040819d: xor edx, edx
    uint32_t t5 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    ctx.edx = static_cast<uint32_t>(t5);
    // 0x0040819f: div ecx
    uint64_t t6 = ((static_cast<uint64_t>(ctx.edx) << 32) | static_cast<uint64_t>(ctx.eax));
    uint32_t t7 = recomp_detail::div64_u(t6, ctx.ecx);
    uint32_t t8 = recomp_detail::mod64_u(t6, ctx.ecx);
    ctx.eax = static_cast<uint32_t>(t7);
    ctx.edx = static_cast<uint32_t>(t8);
    // 0x004081a1: cmp eax, 1
    uint32_t t9 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t9);
    // 0x004081a4: jae 0x40818d
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0040818d;
    goto bb_004081a6;
}
bb_0040818b: {
    // 0x0040818b: xor ecx, ecx
    uint32_t t10 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.ecx = static_cast<uint32_t>(t10);
}
bb_0040818d: {
    // 0x0040818d: push ecx
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.ecx);
    // 0x0040818e: call 0x4e0177
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x00408193u);
    hle_crt_004e0177(ctx, mem);
    // 0x00408193: add esp, 4
    uint32_t t13 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t13);
    ctx.esp = static_cast<uint32_t>(t13);
    // 0x00408196: add esp, 0xc
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t14);
    ctx.esp = static_cast<uint32_t>(t14);
    // 0x00408199: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004081a6: {
    // 0x004081a6: lea eax, [esp + 0x10]
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x004081aa: push eax
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, ctx.eax);
    // 0x004081ab: lea ecx, [esp + 4]
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    ctx.ecx = static_cast<uint32_t>(t17);
    // 0x004081af: mov dword ptr [esp + 0x14], 0
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t18, 0x00000000u);
    // 0x004081b7: call 0x4e07d5
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x004081bcu);
    hle_crt_004e07d5(ctx, mem);
    // 0x004081bc: push 0x543b60
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x00543b60u);
    // 0x004081c1: lea ecx, [esp + 4]
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    ctx.ecx = static_cast<uint32_t>(t21);
    // 0x004081c5: push ecx
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, ctx.ecx);
    // 0x004081c6: mov dword ptr [esp + 8], 0x51b5e0
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    mem.w32(t23, 0x0051b5e0u);
    // 0x004081ce: call 0x4e3e1b
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x004081d3u);
    hle_crt_004e3e1b(ctx, mem);
    // 0x004081d3: int3
    recomp_detail::trap_halt(ctx, 0x004081d3u, "int3");
    return;
}
}

// sub_00413e00 | subsystem=FilePacFunc | canonical | 12 blocks | 44 insns
void sub_00413e00(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00413e00: push ebx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebx);
    // 0x00413e01: mov ebx, dword ptr [esp + 0xc]
    uint32_t t1 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t2 = mem.r32(t1);
    ctx.ebx = static_cast<uint32_t>(t2);
    // 0x00413e05: push ebp
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.ebp);
    // 0x00413e06: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x00413e07: mov eax, ebx
    ctx.eax = static_cast<uint32_t>(ctx.ebx);
    // 0x00413e09: sub eax, 1
    uint32_t t5 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t5);
    ctx.eax = static_cast<uint32_t>(t5);
    // 0x00413e0c: push edi
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.edi);
    // 0x00413e0d: mov edi, ecx
    ctx.edi = static_cast<uint32_t>(ctx.ecx);
    // 0x00413e0f: je 0x413e29
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00413e29;
    goto bb_00413e11;
}
bb_00413e29: {
    // 0x00413e29: cmp dword ptr [edi + 0x1c], 3
    uint32_t t7 = static_cast<uint32_t>(ctx.edi + 0x0000001cu);
    uint32_t t8 = mem.r32(t7);
    uint32_t t9 = static_cast<uint32_t>(t8 - 0x00000003u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t8, 0x00000003u, t9);
    // 0x00413e2d: mov ebp, dword ptr [esp + 0x14]
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t11 = mem.r32(t10);
    ctx.ebp = static_cast<uint32_t>(t11);
    // 0x00413e31: jne 0x413e5a
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00413e5a;
    goto bb_00413e33;
}
bb_00413e11: {
    // 0x00413e11: sub eax, 1
    uint32_t t12 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t12);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x00413e14: je 0x413e1f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00413e1f;
    goto bb_00413e16;
}
bb_00413e5a: {
    // 0x00413e5a: cmp dword ptr [edi], 0
    uint32_t t13 = mem.r32(ctx.edi);
    uint32_t t14 = static_cast<uint32_t>(t13 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t13, 0x00000000u, t14);
    // 0x00413e5d: jne 0x413e4d
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00413e4d;
    goto bb_00413e5f;
}
bb_00413e33: {
    // 0x00413e33: cmp ebx, 2
    uint32_t t15 = static_cast<uint32_t>(ctx.ebx - 0x00000002u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, 0x00000002u, t15);
    // 0x00413e36: jne 0x413e3c
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00413e3c;
    goto bb_00413e38;
}
bb_00413e1f: {
    // 0x00413e1f: mov esi, edi
    ctx.esi = static_cast<uint32_t>(ctx.edi);
    // 0x00413e21: call 0x413db0
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x00413e26u);
    sub_00413db0(ctx, mem);
    // 0x00413e26: mov dword ptr [edi + 0x10], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.edi + 0x00000010u);
    mem.w32(t17, ctx.eax);
    goto bb_00413e29;
}
bb_00413e16: {
    // 0x00413e16: mov dword ptr [edi + 0x10], 0
    uint32_t t18 = static_cast<uint32_t>(ctx.edi + 0x00000010u);
    mem.w32(t18, 0x00000000u);
    // 0x00413e1d: jmp 0x413e29
    goto bb_00413e29;
}
bb_00413e4d: {
    // 0x00413e4d: add dword ptr [edi + 0x10], ebp
    uint32_t t19 = static_cast<uint32_t>(ctx.edi + 0x00000010u);
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t20 + ctx.ebp);
    recomp_detail::update_flags_add<uint32_t>(ctx, t20, ctx.ebp, t21);
    mem.w32(t19, t21);
    // 0x00413e50: mov eax, dword ptr [edi + 0x10]
    uint32_t t22 = static_cast<uint32_t>(ctx.edi + 0x00000010u);
    uint32_t t23 = mem.r32(t22);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x00413e53: pop edi
    uint32_t t24 = ctx.esp;
    uint32_t t25 = mem.r32(t24);
    uint32_t t26 = static_cast<uint32_t>(t24 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    ctx.edi = static_cast<uint32_t>(t25);
    // 0x00413e54: pop esi
    uint32_t t27 = ctx.esp;
    uint32_t t28 = mem.r32(t27);
    uint32_t t29 = static_cast<uint32_t>(t27 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    ctx.esi = static_cast<uint32_t>(t28);
    // 0x00413e55: pop ebp
    uint32_t t30 = ctx.esp;
    uint32_t t31 = mem.r32(t30);
    uint32_t t32 = static_cast<uint32_t>(t30 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    ctx.ebp = static_cast<uint32_t>(t31);
    // 0x00413e56: pop ebx
    uint32_t t33 = ctx.esp;
    uint32_t t34 = mem.r32(t33);
    uint32_t t35 = static_cast<uint32_t>(t33 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    ctx.ebx = static_cast<uint32_t>(t34);
    // 0x00413e57: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
bb_00413e5f: {
    // 0x00413e5f: pop edi
    uint32_t t36 = ctx.esp;
    uint32_t t37 = mem.r32(t36);
    uint32_t t38 = static_cast<uint32_t>(t36 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    ctx.edi = static_cast<uint32_t>(t37);
    // 0x00413e60: pop esi
    uint32_t t39 = ctx.esp;
    uint32_t t40 = mem.r32(t39);
    uint32_t t41 = static_cast<uint32_t>(t39 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    ctx.esi = static_cast<uint32_t>(t40);
    // 0x00413e61: pop ebp
    uint32_t t42 = ctx.esp;
    uint32_t t43 = mem.r32(t42);
    uint32_t t44 = static_cast<uint32_t>(t42 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    ctx.ebp = static_cast<uint32_t>(t43);
    // 0x00413e62: xor eax, eax
    uint32_t t45 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t45);
    ctx.eax = static_cast<uint32_t>(t45);
    // 0x00413e64: pop ebx
    uint32_t t46 = ctx.esp;
    uint32_t t47 = mem.r32(t46);
    uint32_t t48 = static_cast<uint32_t>(t46 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    ctx.ebx = static_cast<uint32_t>(t47);
    // 0x00413e65: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
bb_00413e3c: {
    // 0x00413e3c: xor edx, edx
    uint32_t t49 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t49);
    ctx.edx = static_cast<uint32_t>(t49);
    // 0x00413e3e: test ebx, ebx
    uint32_t t50 = static_cast<uint32_t>(ctx.ebx & ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t50);
    // 0x00413e40: setne dl
    uint8_t t51 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::NE) ? 1u : 0u);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t51));
    goto bb_00413e43;
}
bb_00413e38: {
    // 0x00413e38: mov edx, ebx
    ctx.edx = static_cast<uint32_t>(ctx.ebx);
    // 0x00413e3a: jmp 0x413e43
}
bb_00413e43: {
    // 0x00413e43: mov esi, dword ptr [edi + 0x58]
    uint32_t t52 = static_cast<uint32_t>(ctx.edi + 0x00000058u);
    uint32_t t53 = mem.r32(t52);
    ctx.esi = static_cast<uint32_t>(t53);
    // 0x00413e46: mov eax, ebp
    ctx.eax = static_cast<uint32_t>(ctx.ebp);
    // 0x00413e48: call 0x4dbec0
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, 0x00413e4du);
    sub_004dbec0(ctx, mem);
    goto bb_00413e4d;
}
}

// sub_0041e470 | subsystem=FilePacFunc | canonical | 1 blocks | 39 insns
void sub_0041e470(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041e470: push edi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.edi);
    // 0x0041e471: push 0x535914
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00535914u);
    // 0x0041e476: push 0x76e9c4
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x0076e9c4u);
    // 0x0041e47b: mov edi, 0x535914
    ctx.edi = static_cast<uint32_t>(0x00535914u);
    // 0x0041e480: call 0x4db7f0
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x0041e485u);
    sub_004db7f0(ctx, mem);
    // 0x0041e485: push 0x535920
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x00535920u);
    // 0x0041e48a: push 0x76e9c4
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, 0x0076e9c4u);
    // 0x0041e48f: mov edi, 0x535920
    ctx.edi = static_cast<uint32_t>(0x00535920u);
    // 0x0041e494: call 0x4db7f0
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0041e499u);
    sub_004db7f0(ctx, mem);
    // 0x0041e499: push 0x53592c
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0053592cu);
    // 0x0041e49e: push 0x76e9c4
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x0076e9c4u);
    // 0x0041e4a3: mov edi, 0x53592c
    ctx.edi = static_cast<uint32_t>(0x0053592cu);
    // 0x0041e4a8: call 0x4db7f0
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x0041e4adu);
    sub_004db7f0(ctx, mem);
    // 0x0041e4ad: push 0x535938
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x00535938u);
    // 0x0041e4b2: push 0x76e9c4
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0x0076e9c4u);
    // 0x0041e4b7: mov edi, 0x535938
    ctx.edi = static_cast<uint32_t>(0x00535938u);
    // 0x0041e4bc: call 0x4db7f0
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x0041e4c1u);
    sub_004db7f0(ctx, mem);
    // 0x0041e4c1: push 0x535944
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x00535944u);
    // 0x0041e4c6: push 0x76e9c4
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x0076e9c4u);
    // 0x0041e4cb: mov edi, 0x535944
    ctx.edi = static_cast<uint32_t>(0x00535944u);
    // 0x0041e4d0: call 0x4db7f0
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x0041e4d5u);
    sub_004db7f0(ctx, mem);
    // 0x0041e4d5: push 0x535950
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x00535950u);
    // 0x0041e4da: push 0x76e9c4
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x0076e9c4u);
    // 0x0041e4df: mov edi, 0x535950
    ctx.edi = static_cast<uint32_t>(0x00535950u);
    // 0x0041e4e4: call 0x4db7f0
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x0041e4e9u);
    sub_004db7f0(ctx, mem);
    // 0x0041e4e9: push 0x53595c
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x0053595cu);
    // 0x0041e4ee: push 0x76e9c4
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x0076e9c4u);
    // 0x0041e4f3: mov edi, 0x53595c
    ctx.edi = static_cast<uint32_t>(0x0053595cu);
    // 0x0041e4f8: call 0x4db7f0
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x0041e4fdu);
    sub_004db7f0(ctx, mem);
    // 0x0041e4fd: push 0x535968
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x00535968u);
    // 0x0041e502: push 0x76e9c4
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x0076e9c4u);
    // 0x0041e507: mov edi, 0x535968
    ctx.edi = static_cast<uint32_t>(0x00535968u);
    // 0x0041e50c: call 0x4db7f0
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x0041e511u);
    sub_004db7f0(ctx, mem);
    // 0x0041e511: push 0x535974
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x00535974u);
    // 0x0041e516: push 0x76e9c4
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x0076e9c4u);
    // 0x0041e51b: mov edi, 0x535974
    ctx.edi = static_cast<uint32_t>(0x00535974u);
    // 0x0041e520: call 0x4db7f0
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x0041e525u);
    sub_004db7f0(ctx, mem);
    // 0x0041e525: pop edi
    uint32_t t28 = ctx.esp;
    uint32_t t29 = mem.r32(t28);
    uint32_t t30 = static_cast<uint32_t>(t28 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    ctx.edi = static_cast<uint32_t>(t29);
    // 0x0041e526: jmp 0x41e390
    sub_0041e390(ctx, mem);
    return;
}
}

// sub_0049eac0 | subsystem=FilePacFunc | canonical | 46 blocks | 207 insns
void sub_0049eac0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0049eac0: sub esp, 8
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000008u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000008u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x0049eac3: push ebx
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebx);
    // 0x0049eac4: mov ebx, ecx
    ctx.ebx = static_cast<uint32_t>(ctx.ecx);
    // 0x0049eac6: mov cl, byte ptr [eax]
    uint8_t t2 = mem.r8(ctx.eax);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x0049eac8: mov eax, dword ptr [ebx + 4]
    uint32_t t3 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    uint32_t t4 = mem.r32(t3);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0049eacb: test eax, eax
    uint32_t t5 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    // 0x0049eacd: push ebp
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebp);
    // 0x0049eace: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x0049eacf: push edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edi);
    // 0x0049ead0: mov byte ptr [esp + 0x14], cl
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w8(t9, recomp_detail::r8l(ctx.ecx));
    // 0x0049ead4: jne 0x49eada
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049eada;
    goto bb_0049ead6;
}
bb_0049eada: {
    // 0x0049eada: mov ecx, dword ptr [ebx + 0xc]
    uint32_t t10 = static_cast<uint32_t>(ctx.ebx + 0x0000000cu);
    uint32_t t11 = mem.r32(t10);
    ctx.ecx = static_cast<uint32_t>(t11);
    // 0x0049eadd: sub ecx, eax
    uint32_t t12 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t12);
    ctx.ecx = static_cast<uint32_t>(t12);
    // 0x0049eadf: mov edx, ecx
    ctx.edx = static_cast<uint32_t>(ctx.ecx);
    goto bb_0049eae1;
}
bb_0049ead6: {
    // 0x0049ead6: xor edx, edx
    uint32_t t13 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t13);
    ctx.edx = static_cast<uint32_t>(t13);
    // 0x0049ead8: jmp 0x49eae1
}
bb_0049eae1: {
    // 0x0049eae1: mov edi, dword ptr [esp + 0x1c]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t15 = mem.r32(t14);
    ctx.edi = static_cast<uint32_t>(t15);
    // 0x0049eae5: test edi, edi
    uint32_t t16 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    // 0x0049eae7: je 0x49eca4
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049eca4;
    goto bb_0049eaed;
}
bb_0049eca4: {
    // 0x0049eca4: pop edi
    uint32_t t17 = ctx.esp;
    uint32_t t18 = mem.r32(t17);
    uint32_t t19 = static_cast<uint32_t>(t17 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    ctx.edi = static_cast<uint32_t>(t18);
    // 0x0049eca5: pop esi
    uint32_t t20 = ctx.esp;
    uint32_t t21 = mem.r32(t20);
    uint32_t t22 = static_cast<uint32_t>(t20 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    ctx.esi = static_cast<uint32_t>(t21);
    // 0x0049eca6: pop ebp
    uint32_t t23 = ctx.esp;
    uint32_t t24 = mem.r32(t23);
    uint32_t t25 = static_cast<uint32_t>(t23 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    ctx.ebp = static_cast<uint32_t>(t24);
    // 0x0049eca7: pop ebx
    uint32_t t26 = ctx.esp;
    uint32_t t27 = mem.r32(t26);
    uint32_t t28 = static_cast<uint32_t>(t26 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    ctx.ebx = static_cast<uint32_t>(t27);
    // 0x0049eca8: add esp, 8
    uint32_t t29 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t29);
    ctx.esp = static_cast<uint32_t>(t29);
    // 0x0049ecab: ret 0xc
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 12u;
    return;
}
bb_0049eaed: {
    // 0x0049eaed: test eax, eax
    uint32_t t30 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t30);
    // 0x0049eaef: jne 0x49eaf5
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049eaf5;
    goto bb_0049eaf1;
}
bb_0049eaf5: {
    // 0x0049eaf5: mov ecx, dword ptr [ebx + 8]
    uint32_t t31 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t32 = mem.r32(t31);
    ctx.ecx = static_cast<uint32_t>(t32);
    // 0x0049eaf8: sub ecx, eax
    uint32_t t33 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t33);
    ctx.ecx = static_cast<uint32_t>(t33);
    goto bb_0049eafa;
}
bb_0049eaf1: {
    // 0x0049eaf1: xor ecx, ecx
    uint32_t t34 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t34);
    ctx.ecx = static_cast<uint32_t>(t34);
    // 0x0049eaf3: jmp 0x49eafa
}
bb_0049eafa: {
    // 0x0049eafa: or esi, 0xffffffff
    uint32_t t35 = static_cast<uint32_t>(ctx.esi | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t35);
    ctx.esi = static_cast<uint32_t>(t35);
    // 0x0049eafd: sub esi, ecx
    uint32_t t36 = static_cast<uint32_t>(ctx.esi - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ecx, t36);
    ctx.esi = static_cast<uint32_t>(t36);
    // 0x0049eaff: cmp esi, edi
    uint32_t t37 = static_cast<uint32_t>(ctx.esi - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edi, t37);
    // 0x0049eb01: jae 0x49eb08
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0049eb08;
    goto bb_0049eb03;
}
bb_0049eb08: {
    // 0x0049eb08: test eax, eax
    uint32_t t38 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t38);
    // 0x0049eb0a: jne 0x49eb10
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049eb10;
    goto bb_0049eb0c;
}
bb_0049eb03: {
    // 0x0049eb03: call 0x407b70
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, 0x0049eb08u);
    sub_00407b70(ctx, mem);
    goto bb_0049eb08;
}
bb_0049eb10: {
    // 0x0049eb10: mov ecx, dword ptr [ebx + 8]
    uint32_t t40 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t41 = mem.r32(t40);
    ctx.ecx = static_cast<uint32_t>(t41);
    // 0x0049eb13: sub ecx, eax
    uint32_t t42 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t42);
    ctx.ecx = static_cast<uint32_t>(t42);
    goto bb_0049eb15;
}
bb_0049eb0c: {
    // 0x0049eb0c: xor ecx, ecx
    uint32_t t43 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t43);
    ctx.ecx = static_cast<uint32_t>(t43);
    // 0x0049eb0e: jmp 0x49eb15
}
bb_0049eb15: {
    // 0x0049eb15: add ecx, edi
    uint32_t t44 = static_cast<uint32_t>(ctx.ecx + ctx.edi);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, ctx.edi, t44);
    ctx.ecx = static_cast<uint32_t>(t44);
    // 0x0049eb17: cmp edx, ecx
    uint32_t t45 = static_cast<uint32_t>(ctx.edx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ecx, t45);
    // 0x0049eb19: jae 0x49ebf0
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0049ebf0;
    goto bb_0049eb1f;
}
bb_0049ebf0: {
    // 0x0049ebf0: mov esi, dword ptr [ebx + 8]
    uint32_t t46 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t47 = mem.r32(t46);
    ctx.esi = static_cast<uint32_t>(t47);
    // 0x0049ebf3: mov ebp, dword ptr [esp + 0x24]
    uint32_t t48 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t49 = mem.r32(t48);
    ctx.ebp = static_cast<uint32_t>(t49);
    // 0x0049ebf7: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0049ebf9: sub eax, ebp
    uint32_t t50 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t50);
    ctx.eax = static_cast<uint32_t>(t50);
    // 0x0049ebfb: cmp eax, edi
    uint32_t t51 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t51);
    // 0x0049ebfd: jae 0x49ec50
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0049ec50;
    goto bb_0049ebff;
}
bb_0049eb1f: {
    // 0x0049eb1f: mov ecx, edx
    ctx.ecx = static_cast<uint32_t>(ctx.edx);
    // 0x0049eb21: shr ecx, 1
    uint32_t t52 = static_cast<uint32_t>(0x00000001u & 0x0000001fu);
    uint32_t t53 = recomp_detail::shr<uint32_t>(ctx.ecx, t52);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.ecx, t52, t53);
    ctx.ecx = static_cast<uint32_t>(t53);
    // 0x0049eb23: or esi, 0xffffffff
    uint32_t t54 = static_cast<uint32_t>(ctx.esi | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t54);
    ctx.esi = static_cast<uint32_t>(t54);
    // 0x0049eb26: sub esi, ecx
    uint32_t t55 = static_cast<uint32_t>(ctx.esi - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ecx, t55);
    ctx.esi = static_cast<uint32_t>(t55);
    // 0x0049eb28: cmp esi, edx
    uint32_t t56 = static_cast<uint32_t>(ctx.esi - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edx, t56);
    // 0x0049eb2a: jae 0x49eb3a
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0049eb3a;
    goto bb_0049eb2c;
}
bb_0049ec50: {
    // 0x0049ec50: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x0049ec52: sub ecx, edi
    uint32_t t57 = static_cast<uint32_t>(ctx.ecx - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.edi, t57);
    ctx.ecx = static_cast<uint32_t>(t57);
    // 0x0049ec54: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0049ec56: sub eax, ecx
    uint32_t t58 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t58);
    ctx.eax = static_cast<uint32_t>(t58);
    // 0x0049ec58: lea edx, [eax + esi]
    uint32_t t59 = static_cast<uint32_t>(ctx.eax + ctx.esi);
    ctx.edx = static_cast<uint32_t>(t59);
    // 0x0049ec5b: mov dword ptr [esp + 0x1c], edx
    uint32_t t60 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t60, ctx.edx);
    // 0x0049ec5f: je 0x49ec6d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049ec6d;
    goto bb_0049ec61;
}
bb_0049ebff: {
    // 0x0049ebff: test eax, eax
    uint32_t t61 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t61);
    // 0x0049ec01: jbe 0x49ec12
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0049ec12;
    goto bb_0049ec03;
}
bb_0049eb3a: {
    // 0x0049eb3a: add edx, ecx
    uint32_t t62 = static_cast<uint32_t>(ctx.edx + ctx.ecx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, ctx.ecx, t62);
    ctx.edx = static_cast<uint32_t>(t62);
    // 0x0049eb3c: mov dword ptr [esp + 0x10], edx
    uint32_t t63 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t63, ctx.edx);
    goto bb_0049eb40;
}
bb_0049eb2c: {
    // 0x0049eb2c: mov dword ptr [esp + 0x10], 0
    uint32_t t64 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t64, 0x00000000u);
    // 0x0049eb34: mov edx, dword ptr [esp + 0x10]
    uint32_t t65 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t66 = mem.r32(t65);
    ctx.edx = static_cast<uint32_t>(t66);
    // 0x0049eb38: jmp 0x49eb40
    goto bb_0049eb40;
}
bb_0049ec6d: {
    // 0x0049ec6d: mov eax, dword ptr [esp + 0x1c]
    uint32_t t67 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t68 = mem.r32(t67);
    ctx.eax = static_cast<uint32_t>(t68);
    // 0x0049ec71: mov dword ptr [ebx + 8], eax
    uint32_t t69 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    mem.w32(t69, ctx.eax);
    // 0x0049ec74: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0049ec76: sub eax, ebp
    uint32_t t70 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t70);
    ctx.eax = static_cast<uint32_t>(t70);
    // 0x0049ec78: sub eax, edi
    uint32_t t71 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t71);
    ctx.eax = static_cast<uint32_t>(t71);
    // 0x0049ec7a: test eax, eax
    uint32_t t72 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t72);
    // 0x0049ec7c: jle 0x49ec8c
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0049ec8c;
    goto bb_0049ec7e;
}
bb_0049ec61: {
    // 0x0049ec61: push eax
    uint32_t t73 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    mem.w32(t73, ctx.eax);
    // 0x0049ec62: push ecx
    uint32_t t74 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    mem.w32(t74, ctx.ecx);
    // 0x0049ec63: push eax
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, ctx.eax);
    // 0x0049ec64: push esi
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    mem.w32(t76, ctx.esi);
    // 0x0049ec65: call 0x4e0c02
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, 0x0049ec6au);
    hle_crt_004e0c02(ctx, mem);
    // 0x0049ec6a: add esp, 0x10
    uint32_t t78 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t78);
    ctx.esp = static_cast<uint32_t>(t78);
    goto bb_0049ec6d;
}
bb_0049ec12: {
    // 0x0049ec12: mov eax, dword ptr [ebx + 8]
    uint32_t t79 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t80 = mem.r32(t79);
    ctx.eax = static_cast<uint32_t>(t80);
    // 0x0049ec15: mov esi, ebp
    ctx.esi = static_cast<uint32_t>(ctx.ebp);
    // 0x0049ec17: sub esi, eax
    uint32_t t81 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t81);
    ctx.esi = static_cast<uint32_t>(t81);
    // 0x0049ec19: add esi, edi
    uint32_t t82 = static_cast<uint32_t>(ctx.esi + ctx.edi);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, ctx.edi, t82);
    ctx.esi = static_cast<uint32_t>(t82);
    // 0x0049ec1b: push eax
    uint32_t t83 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t83);
    mem.w32(t83, ctx.eax);
    // 0x0049ec1c: lea edi, [esp + 0x18]
    uint32_t t84 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.edi = static_cast<uint32_t>(t84);
    // 0x0049ec20: call 0x49ecb0
    uint32_t t85 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t85);
    mem.w32(t85, 0x0049ec25u);
    sub_0049ecb0(ctx, mem);
    // 0x0049ec25: mov eax, dword ptr [esp + 0x1c]
    uint32_t t86 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t87 = mem.r32(t86);
    ctx.eax = static_cast<uint32_t>(t87);
    // 0x0049ec29: add dword ptr [ebx + 8], eax
    uint32_t t88 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t89 = mem.r32(t88);
    uint32_t t90 = static_cast<uint32_t>(t89 + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, t89, ctx.eax, t90);
    mem.w32(t88, t90);
    // 0x0049ec2c: mov ebx, dword ptr [ebx + 8]
    uint32_t t91 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t92 = mem.r32(t91);
    ctx.ebx = static_cast<uint32_t>(t92);
    // 0x0049ec2f: sub ebx, eax
    uint32_t t93 = static_cast<uint32_t>(ctx.ebx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.eax, t93);
    ctx.ebx = static_cast<uint32_t>(t93);
    // 0x0049ec31: cmp ebp, ebx
    uint32_t t94 = static_cast<uint32_t>(ctx.ebp - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebp, ctx.ebx, t94);
    // 0x0049ec33: je 0x49eca4
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049eca4;
    goto bb_0049ec35;
}
bb_0049ec03: {
    // 0x0049ec03: push eax
    uint32_t t95 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t95);
    mem.w32(t95, ctx.eax);
    // 0x0049ec04: push ebp
    uint32_t t96 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    mem.w32(t96, ctx.ebp);
    // 0x0049ec05: push eax
    uint32_t t97 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t97);
    mem.w32(t97, ctx.eax);
    // 0x0049ec06: lea edx, [edi + ebp]
    uint32_t t98 = static_cast<uint32_t>(ctx.edi + ctx.ebp);
    ctx.edx = static_cast<uint32_t>(t98);
    // 0x0049ec09: push edx
    uint32_t t99 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t99);
    mem.w32(t99, ctx.edx);
    // 0x0049ec0a: call 0x4e0c02
    uint32_t t100 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t100);
    mem.w32(t100, 0x0049ec0fu);
    hle_crt_004e0c02(ctx, mem);
    // 0x0049ec0f: add esp, 0x10
    uint32_t t101 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t101);
    ctx.esp = static_cast<uint32_t>(t101);
    goto bb_0049ec12;
}
bb_0049eb40: {
    // 0x0049eb40: test eax, eax
    uint32_t t102 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t102);
    // 0x0049eb42: jne 0x49eb48
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049eb48;
    goto bb_0049eb44;
}
bb_0049ec8c: {
    // 0x0049ec8c: lea eax, [edi + ebp]
    uint32_t t103 = static_cast<uint32_t>(ctx.edi + ctx.ebp);
    ctx.eax = static_cast<uint32_t>(t103);
    // 0x0049ec8f: cmp ebp, eax
    uint32_t t104 = static_cast<uint32_t>(ctx.ebp - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebp, ctx.eax, t104);
    // 0x0049ec91: je 0x49eca4
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049eca4;
    goto bb_0049ec93;
}
bb_0049ec7e: {
    // 0x0049ec7e: push eax
    uint32_t t105 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t105);
    mem.w32(t105, ctx.eax);
    // 0x0049ec7f: push ebp
    uint32_t t106 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t106);
    mem.w32(t106, ctx.ebp);
    // 0x0049ec80: push eax
    uint32_t t107 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t107);
    mem.w32(t107, ctx.eax);
    // 0x0049ec81: sub esi, eax
    uint32_t t108 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t108);
    ctx.esi = static_cast<uint32_t>(t108);
    // 0x0049ec83: push esi
    uint32_t t109 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t109);
    mem.w32(t109, ctx.esi);
    // 0x0049ec84: call 0x4e0c02
    uint32_t t110 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t110);
    mem.w32(t110, 0x0049ec89u);
    hle_crt_004e0c02(ctx, mem);
    // 0x0049ec89: add esp, 0x10
    uint32_t t111 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t111);
    ctx.esp = static_cast<uint32_t>(t111);
    goto bb_0049ec8c;
}
bb_0049ec35: {
    // 0x0049ec35: mov eax, dword ptr [esp + 0x14]
    uint32_t t112 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t113 = mem.r32(t112);
    ctx.eax = static_cast<uint32_t>(t113);
    // 0x0049ec39: sub ebx, ebp
    uint32_t t114 = static_cast<uint32_t>(ctx.ebx - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.ebp, t114);
    ctx.ebx = static_cast<uint32_t>(t114);
    // 0x0049ec3b: push ebx
    uint32_t t115 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t115);
    mem.w32(t115, ctx.ebx);
    // 0x0049ec3c: push eax
    uint32_t t116 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t116);
    mem.w32(t116, ctx.eax);
    // 0x0049ec3d: push ebp
    uint32_t t117 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t117);
    mem.w32(t117, ctx.ebp);
    // 0x0049ec3e: call 0x4e6340
    uint32_t t118 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    mem.w32(t118, 0x0049ec43u);
    hle_crt_004e6340(ctx, mem);
    // 0x0049ec43: add esp, 0xc
    uint32_t t119 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t119);
    ctx.esp = static_cast<uint32_t>(t119);
    // 0x0049ec46: pop edi
    uint32_t t120 = ctx.esp;
    uint32_t t121 = mem.r32(t120);
    uint32_t t122 = static_cast<uint32_t>(t120 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t122);
    ctx.edi = static_cast<uint32_t>(t121);
    // 0x0049ec47: pop esi
    uint32_t t123 = ctx.esp;
    uint32_t t124 = mem.r32(t123);
    uint32_t t125 = static_cast<uint32_t>(t123 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t125);
    ctx.esi = static_cast<uint32_t>(t124);
    // 0x0049ec48: pop ebp
    uint32_t t126 = ctx.esp;
    uint32_t t127 = mem.r32(t126);
    uint32_t t128 = static_cast<uint32_t>(t126 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t128);
    ctx.ebp = static_cast<uint32_t>(t127);
    // 0x0049ec49: pop ebx
    uint32_t t129 = ctx.esp;
    uint32_t t130 = mem.r32(t129);
    uint32_t t131 = static_cast<uint32_t>(t129 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t131);
    ctx.ebx = static_cast<uint32_t>(t130);
    // 0x0049ec4a: add esp, 8
    uint32_t t132 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t132);
    ctx.esp = static_cast<uint32_t>(t132);
    // 0x0049ec4d: ret 0xc
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 12u;
    return;
}
bb_0049eb48: {
    // 0x0049eb48: mov ecx, dword ptr [ebx + 8]
    uint32_t t133 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t134 = mem.r32(t133);
    ctx.ecx = static_cast<uint32_t>(t134);
    // 0x0049eb4b: sub ecx, eax
    uint32_t t135 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t135);
    ctx.ecx = static_cast<uint32_t>(t135);
    goto bb_0049eb4d;
}
bb_0049eb44: {
    // 0x0049eb44: xor ecx, ecx
    uint32_t t136 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t136);
    ctx.ecx = static_cast<uint32_t>(t136);
    // 0x0049eb46: jmp 0x49eb4d
    goto bb_0049eb4d;
}
bb_0049ec93: {
    // 0x0049ec93: mov ecx, dword ptr [esp + 0x14]
    uint32_t t137 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t138 = mem.r32(t137);
    ctx.ecx = static_cast<uint32_t>(t138);
    // 0x0049ec97: sub eax, ebp
    uint32_t t139 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t139);
    ctx.eax = static_cast<uint32_t>(t139);
    // 0x0049ec99: push eax
    uint32_t t140 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t140);
    mem.w32(t140, ctx.eax);
    // 0x0049ec9a: push ecx
    uint32_t t141 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t141);
    mem.w32(t141, ctx.ecx);
    // 0x0049ec9b: push ebp
    uint32_t t142 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t142);
    mem.w32(t142, ctx.ebp);
    // 0x0049ec9c: call 0x4e6340
    uint32_t t143 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t143);
    mem.w32(t143, 0x0049eca1u);
    hle_crt_004e6340(ctx, mem);
    // 0x0049eca1: add esp, 0xc
    uint32_t t144 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t144);
    ctx.esp = static_cast<uint32_t>(t144);
    goto bb_0049eca4;
}
bb_0049eb4d: {
    // 0x0049eb4d: add ecx, edi
    uint32_t t145 = static_cast<uint32_t>(ctx.ecx + ctx.edi);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, ctx.edi, t145);
    ctx.ecx = static_cast<uint32_t>(t145);
    // 0x0049eb4f: cmp edx, ecx
    uint32_t t146 = static_cast<uint32_t>(ctx.edx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ecx, t146);
    // 0x0049eb51: jae 0x49eb68
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0049eb68;
    goto bb_0049eb53;
}
bb_0049eb68: {
    // 0x0049eb68: push 0
    uint32_t t147 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t147);
    mem.w32(t147, 0x00000000u);
    // 0x0049eb6a: push edx
    uint32_t t148 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t148);
    mem.w32(t148, ctx.edx);
    // 0x0049eb6b: call 0x408180
    uint32_t t149 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t149);
    mem.w32(t149, 0x0049eb70u);
    sub_00408180(ctx, mem);
    // 0x0049eb70: mov ecx, dword ptr [ebx + 4]
    uint32_t t150 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    uint32_t t151 = mem.r32(t150);
    ctx.ecx = static_cast<uint32_t>(t151);
    // 0x0049eb73: mov ebp, eax
    ctx.ebp = static_cast<uint32_t>(ctx.eax);
    // 0x0049eb75: mov eax, dword ptr [esp + 0x2c]
    uint32_t t152 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    uint32_t t153 = mem.r32(t152);
    ctx.eax = static_cast<uint32_t>(t153);
    // 0x0049eb79: add esp, 8
    uint32_t t154 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t154);
    ctx.esp = static_cast<uint32_t>(t154);
    // 0x0049eb7c: sub eax, ecx
    uint32_t t155 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t155);
    ctx.eax = static_cast<uint32_t>(t155);
    // 0x0049eb7e: lea esi, [eax + ebp]
    uint32_t t156 = static_cast<uint32_t>(ctx.eax + ctx.ebp);
    ctx.esi = static_cast<uint32_t>(t156);
    // 0x0049eb81: je 0x49eb8f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049eb8f;
    goto bb_0049eb83;
}
bb_0049eb53: {
    // 0x0049eb53: test eax, eax
    uint32_t t157 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t157);
    // 0x0049eb55: jne 0x49eb5b
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049eb5b;
    goto bb_0049eb57;
}
bb_0049eb8f: {
    // 0x0049eb8f: push esi
    uint32_t t158 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t158);
    mem.w32(t158, ctx.esi);
    // 0x0049eb90: mov esi, dword ptr [esp + 0x20]
    uint32_t t159 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t160 = mem.r32(t159);
    ctx.esi = static_cast<uint32_t>(t160);
    // 0x0049eb94: lea edi, [esp + 0x18]
    uint32_t t161 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.edi = static_cast<uint32_t>(t161);
    // 0x0049eb98: call 0x49ecb0
    uint32_t t162 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t162);
    mem.w32(t162, 0x0049eb9du);
    sub_0049ecb0(ctx, mem);
    // 0x0049eb9d: mov ecx, dword ptr [ebx + 8]
    uint32_t t163 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t164 = mem.r32(t163);
    ctx.ecx = static_cast<uint32_t>(t164);
    // 0x0049eba0: mov edx, dword ptr [esp + 0x24]
    uint32_t t165 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t166 = mem.r32(t165);
    ctx.edx = static_cast<uint32_t>(t166);
    // 0x0049eba4: sub ecx, edx
    uint32_t t167 = static_cast<uint32_t>(ctx.ecx - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.edx, t167);
    ctx.ecx = static_cast<uint32_t>(t167);
    // 0x0049eba6: je 0x49ebb4
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049ebb4;
    goto bb_0049eba8;
}
bb_0049eb83: {
    // 0x0049eb83: push eax
    uint32_t t168 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t168);
    mem.w32(t168, ctx.eax);
    // 0x0049eb84: push ecx
    uint32_t t169 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t169);
    mem.w32(t169, ctx.ecx);
    // 0x0049eb85: push eax
    uint32_t t170 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t170);
    mem.w32(t170, ctx.eax);
    // 0x0049eb86: push ebp
    uint32_t t171 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t171);
    mem.w32(t171, ctx.ebp);
    // 0x0049eb87: call 0x4e0c02
    uint32_t t172 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t172);
    mem.w32(t172, 0x0049eb8cu);
    hle_crt_004e0c02(ctx, mem);
    // 0x0049eb8c: add esp, 0x10
    uint32_t t173 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t173);
    ctx.esp = static_cast<uint32_t>(t173);
    goto bb_0049eb8f;
}
bb_0049eb5b: {
    // 0x0049eb5b: mov ecx, dword ptr [ebx + 8]
    uint32_t t174 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t175 = mem.r32(t174);
    ctx.ecx = static_cast<uint32_t>(t175);
    // 0x0049eb5e: sub ecx, eax
    uint32_t t176 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t176);
    ctx.ecx = static_cast<uint32_t>(t176);
    goto bb_0049eb60;
}
bb_0049eb57: {
    // 0x0049eb57: xor ecx, ecx
    uint32_t t177 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t177);
    ctx.ecx = static_cast<uint32_t>(t177);
    // 0x0049eb59: jmp 0x49eb60
    goto bb_0049eb60;
}
bb_0049ebb4: {
    // 0x0049ebb4: mov ecx, dword ptr [ebx + 4]
    uint32_t t178 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    uint32_t t179 = mem.r32(t178);
    ctx.ecx = static_cast<uint32_t>(t179);
    // 0x0049ebb7: test ecx, ecx
    uint32_t t180 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t180);
    // 0x0049ebb9: jne 0x49ebbf
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049ebbf;
    goto bb_0049ebbb;
}
bb_0049eba8: {
    // 0x0049eba8: push ecx
    uint32_t t181 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t181);
    mem.w32(t181, ctx.ecx);
    // 0x0049eba9: push edx
    uint32_t t182 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t182);
    mem.w32(t182, ctx.edx);
    // 0x0049ebaa: push ecx
    uint32_t t183 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t183);
    mem.w32(t183, ctx.ecx);
    // 0x0049ebab: push eax
    uint32_t t184 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t184);
    mem.w32(t184, ctx.eax);
    // 0x0049ebac: call 0x4e0c02
    uint32_t t185 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t185);
    mem.w32(t185, 0x0049ebb1u);
    hle_crt_004e0c02(ctx, mem);
    // 0x0049ebb1: add esp, 0x10
    uint32_t t186 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t186);
    ctx.esp = static_cast<uint32_t>(t186);
    goto bb_0049ebb4;
}
bb_0049eb60: {
    // 0x0049eb60: add ecx, edi
    uint32_t t187 = static_cast<uint32_t>(ctx.ecx + ctx.edi);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, ctx.edi, t187);
    ctx.ecx = static_cast<uint32_t>(t187);
    // 0x0049eb62: mov dword ptr [esp + 0x10], ecx
    uint32_t t188 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t188, ctx.ecx);
    // 0x0049eb66: mov edx, ecx
    ctx.edx = static_cast<uint32_t>(ctx.ecx);
    goto bb_0049eb68;
}
bb_0049ebbf: {
    // 0x0049ebbf: mov eax, dword ptr [ebx + 8]
    uint32_t t189 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t190 = mem.r32(t189);
    ctx.eax = static_cast<uint32_t>(t190);
    // 0x0049ebc2: sub eax, ecx
    uint32_t t191 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t191);
    ctx.eax = static_cast<uint32_t>(t191);
    goto bb_0049ebc4;
}
bb_0049ebbb: {
    // 0x0049ebbb: xor eax, eax
    uint32_t t192 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t192);
    ctx.eax = static_cast<uint32_t>(t192);
    // 0x0049ebbd: jmp 0x49ebc4
}
bb_0049ebc4: {
    // 0x0049ebc4: add esi, eax
    uint32_t t193 = static_cast<uint32_t>(ctx.esi + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, ctx.eax, t193);
    ctx.esi = static_cast<uint32_t>(t193);
    // 0x0049ebc6: test ecx, ecx
    uint32_t t194 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t194);
    // 0x0049ebc8: je 0x49ebd3
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049ebd3;
    goto bb_0049ebca;
}
bb_0049ebd3: {
    // 0x0049ebd3: mov edx, dword ptr [esp + 0x10]
    uint32_t t195 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t196 = mem.r32(t195);
    ctx.edx = static_cast<uint32_t>(t196);
    // 0x0049ebd7: lea eax, [edx + ebp]
    uint32_t t197 = static_cast<uint32_t>(ctx.edx + ctx.ebp);
    ctx.eax = static_cast<uint32_t>(t197);
    // 0x0049ebda: lea ecx, [esi + ebp]
    uint32_t t198 = static_cast<uint32_t>(ctx.esi + ctx.ebp);
    ctx.ecx = static_cast<uint32_t>(t198);
    // 0x0049ebdd: mov dword ptr [ebx + 0xc], eax
    uint32_t t199 = static_cast<uint32_t>(ctx.ebx + 0x0000000cu);
    mem.w32(t199, ctx.eax);
    // 0x0049ebe0: mov dword ptr [ebx + 8], ecx
    uint32_t t200 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    mem.w32(t200, ctx.ecx);
    // 0x0049ebe3: mov dword ptr [ebx + 4], ebp
    uint32_t t201 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    mem.w32(t201, ctx.ebp);
    // 0x0049ebe6: pop edi
    uint32_t t202 = ctx.esp;
    uint32_t t203 = mem.r32(t202);
    uint32_t t204 = static_cast<uint32_t>(t202 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t204);
    ctx.edi = static_cast<uint32_t>(t203);
    // 0x0049ebe7: pop esi
    uint32_t t205 = ctx.esp;
    uint32_t t206 = mem.r32(t205);
    uint32_t t207 = static_cast<uint32_t>(t205 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t207);
    ctx.esi = static_cast<uint32_t>(t206);
    // 0x0049ebe8: pop ebp
    uint32_t t208 = ctx.esp;
    uint32_t t209 = mem.r32(t208);
    uint32_t t210 = static_cast<uint32_t>(t208 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t210);
    ctx.ebp = static_cast<uint32_t>(t209);
    // 0x0049ebe9: pop ebx
    uint32_t t211 = ctx.esp;
    uint32_t t212 = mem.r32(t211);
    uint32_t t213 = static_cast<uint32_t>(t211 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t213);
    ctx.ebx = static_cast<uint32_t>(t212);
    // 0x0049ebea: add esp, 8
    uint32_t t214 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t214);
    ctx.esp = static_cast<uint32_t>(t214);
    // 0x0049ebed: ret 0xc
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 12u;
    return;
}
bb_0049ebca: {
    // 0x0049ebca: push ecx
    uint32_t t215 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t215);
    mem.w32(t215, ctx.ecx);
    // 0x0049ebcb: call 0x4e02f3
    uint32_t t216 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t216);
    mem.w32(t216, 0x0049ebd0u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0049ebd0: add esp, 4
    uint32_t t217 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t217);
    ctx.esp = static_cast<uint32_t>(t217);
    goto bb_0049ebd3;
}
}

// sub_0049ecb0 | subsystem=FilePacFunc | canonical | 4 blocks | 16 insns
void sub_0049ecb0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0049ecb0: test esi, esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    // 0x0049ecb2: push ebp
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebp);
    // 0x0049ecb3: mov ebp, dword ptr [esp + 8]
    uint32_t t2 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t3 = mem.r32(t2);
    ctx.ebp = static_cast<uint32_t>(t3);
    // 0x0049ecb7: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0049ecb9: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x0049ecbb: jbe 0x49ecce
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0049ecce;
    goto bb_0049ecbd;
}
bb_0049ecce: {
    // 0x0049ecce: lea eax, [esi + ebp]
    uint32_t t4 = static_cast<uint32_t>(ctx.esi + ctx.ebp);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0049ecd1: pop ebp
    uint32_t t5 = ctx.esp;
    uint32_t t6 = mem.r32(t5);
    uint32_t t7 = static_cast<uint32_t>(t5 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    ctx.ebp = static_cast<uint32_t>(t6);
    // 0x0049ecd2: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0049ecbd: {
    // 0x0049ecbd: lea ecx, [ecx]
    ctx.ecx = static_cast<uint32_t>(ctx.ecx);
}
bb_0049ecc0: {
    // 0x0049ecc0: mov dl, byte ptr [edi]
    uint8_t t8 = mem.r8(ctx.edi);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t8));
    // 0x0049ecc2: mov byte ptr [ecx], dl
    mem.w8(ctx.ecx, recomp_detail::r8l(ctx.edx));
    // 0x0049ecc4: sub eax, 1
    uint32_t t9 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t9);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x0049ecc7: add ecx, 1
    uint32_t t10 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t10);
    ctx.ecx = static_cast<uint32_t>(t10);
    // 0x0049ecca: test eax, eax
    uint32_t t11 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    // 0x0049eccc: ja 0x49ecc0
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_0049ecc0;
    goto bb_0049ecce;
}
}

// sub_004c1d50 | subsystem=FilePacFunc | canonical | 16 blocks | 110 insns
void sub_004c1d50(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004c1d50: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x004c1d52: push 0x514bee
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00514beeu);
    // 0x004c1d57: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004c1d5d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x004c1d5e: sub esp, 0x14
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000014u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000014u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x004c1d61: push ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebx);
    // 0x004c1d62: push ebp
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.ebp);
    // 0x004c1d63: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x004c1d64: push edi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.edi);
    // 0x004c1d65: mov eax, dword ptr [0x54b458]
    uint32_t t10 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x004c1d6a: xor eax, esp
    uint32_t t11 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x004c1d6c: push eax
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.eax);
    // 0x004c1d6d: lea eax, [esp + 0x28]
    uint32_t t13 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x004c1d71: mov dword ptr fs:[0], eax
    uint32_t t14 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t14, ctx.eax);
    // 0x004c1d77: mov eax, dword ptr [esp + 0x3c]
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    uint32_t t16 = mem.r32(t15);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x004c1d7b: mov ebp, dword ptr [esp + 0x38]
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    uint32_t t18 = mem.r32(t17);
    ctx.ebp = static_cast<uint32_t>(t18);
    // 0x004c1d7f: mov dword ptr [esp + 0x20], eax
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t19, ctx.eax);
    // 0x004c1d83: xor ebx, ebx
    uint32_t t20 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t20);
    ctx.ebx = static_cast<uint32_t>(t20);
    // 0x004c1d85: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x004c1d8a: test byte ptr [0x7b0a70], al
    uint8_t t21 = mem.r8(0x007b0a70u);
    uint8_t t22 = static_cast<uint8_t>(static_cast<uint32_t>(t21) & static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t22);
    // 0x004c1d90: mov edi, ecx
    ctx.edi = static_cast<uint32_t>(ctx.ecx);
    // 0x004c1d92: mov dword ptr [esp + 0x1c], edi
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t23, ctx.edi);
    // 0x004c1d96: mov dword ptr [esp + 0x24], ebx
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t24, ctx.ebx);
    // 0x004c1d9a: jne 0x4c1de0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004c1de0;
    goto bb_004c1d9c;
}
bb_004c1de0: {
    // 0x004c1de0: mov ecx, dword ptr [0x7b0a50]
    uint32_t t25 = mem.r32(0x007b0a50u);
    ctx.ecx = static_cast<uint32_t>(t25);
    // 0x004c1de6: cmp ecx, ebx
    uint32_t t26 = static_cast<uint32_t>(ctx.ecx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebx, t26);
    // 0x004c1de8: jne 0x4c1dee
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004c1dee;
    goto bb_004c1dea;
}
bb_004c1d9c: {
    // 0x004c1d9c: or dword ptr [0x7b0a70], eax
    uint32_t t27 = mem.r32(0x007b0a70u);
    uint32_t t28 = static_cast<uint32_t>(t27 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t28);
    mem.w32(0x007b0a70u, t28);
    // 0x004c1da2: mov dword ptr [esp + 0x30], ebx
    uint32_t t29 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    mem.w32(t29, ctx.ebx);
    // 0x004c1da6: mov byte ptr [esp + 0x1b], bl
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x0000001bu);
    mem.w8(t30, recomp_detail::r8l(ctx.ebx));
    // 0x004c1daa: lea ebx, [esp + 0x1b]
    uint32_t t31 = static_cast<uint32_t>(ctx.esp + 0x0000001bu);
    ctx.ebx = static_cast<uint32_t>(t31);
    // 0x004c1dae: mov edi, 0x800
    ctx.edi = static_cast<uint32_t>(0x00000800u);
    // 0x004c1db3: mov esi, 0x7b0a4c
    ctx.esi = static_cast<uint32_t>(0x007b0a4cu);
    // 0x004c1db8: call 0x4c2180
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x004c1dbdu);
    sub_004c2180(ctx, mem);
    // 0x004c1dbd: push 0x519fe0
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x00519fe0u);
    // 0x004c1dc2: call 0x4e0ab6
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x004c1dc7u);
    hle_crt_004e0ab6(ctx, mem);
    // 0x004c1dc7: mov edi, dword ptr [esp + 0x20]
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t36 = mem.r32(t35);
    ctx.edi = static_cast<uint32_t>(t36);
    // 0x004c1dcb: add esp, 4
    uint32_t t37 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t37);
    ctx.esp = static_cast<uint32_t>(t37);
    // 0x004c1dce: mov dword ptr [esp + 0x30], 0xffffffff
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    mem.w32(t38, 0xffffffffu);
    // 0x004c1dd6: xor ebx, ebx
    uint32_t t39 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t39);
    ctx.ebx = static_cast<uint32_t>(t39);
    // 0x004c1dd8: jmp 0x4c1de0
    goto bb_004c1de0;
}
bb_004c1dee: {
    // 0x004c1dee: mov eax, dword ptr [0x7b0a54]
    uint32_t t40 = mem.r32(0x007b0a54u);
    ctx.eax = static_cast<uint32_t>(t40);
    // 0x004c1df3: sub eax, ecx
    uint32_t t41 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t41);
    ctx.eax = static_cast<uint32_t>(t41);
    // 0x004c1df5: cmp eax, ebx
    uint32_t t42 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t42);
    // 0x004c1df7: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004c1df9: ja 0x4c1e06
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_004c1e06;
    goto bb_004c1dfb;
}
bb_004c1dea: {
    // 0x004c1dea: xor esi, esi
    uint32_t t43 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t43);
    ctx.esi = static_cast<uint32_t>(t43);
    // 0x004c1dec: jmp 0x4c1dfb
    goto bb_004c1dfb;
}
bb_004c1e06: {
    // 0x004c1e06: mov edx, dword ptr [esp + 0x20]
    uint32_t t44 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t45 = mem.r32(t44);
    ctx.edx = static_cast<uint32_t>(t45);
    // 0x004c1e0a: push edx
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, ctx.edx);
    // 0x004c1e0b: push edi
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, ctx.edi);
    // 0x004c1e0c: push esi
    uint32_t t48 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    mem.w32(t48, ctx.esi);
    // 0x004c1e0d: push ecx
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, ctx.ecx);
    // 0x004c1e0e: call 0x4e21df
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, 0x004c1e13u);
    hle_crt_004e21df(ctx, mem);
    // 0x004c1e13: add esp, 0x10
    uint32_t t51 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t51);
    ctx.esp = static_cast<uint32_t>(t51);
    // 0x004c1e16: cmp eax, -1
    uint32_t t52 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t52);
    // 0x004c1e19: jne 0x4c1e4a
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004c1e4a;
    goto bb_004c1e1b;
}
bb_004c1dfb: {
    // 0x004c1dfb: call 0x4e0bf2
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, 0x004c1e00u);
    hle_crt_004e0bf2(ctx, mem);
    // 0x004c1e00: mov ecx, dword ptr [0x7b0a50]
    uint32_t t54 = mem.r32(0x007b0a50u);
    ctx.ecx = static_cast<uint32_t>(t54);
    goto bb_004c1e06;
}
bb_004c1e4a: {
    // 0x004c1e4a: mov byte ptr [esp + 0x1b], bl
    uint32_t t55 = static_cast<uint32_t>(ctx.esp + 0x0000001bu);
    mem.w8(t55, recomp_detail::r8l(ctx.ebx));
    // 0x004c1e4e: lea ebx, [esp + 0x1b]
    uint32_t t56 = static_cast<uint32_t>(ctx.esp + 0x0000001bu);
    ctx.ebx = static_cast<uint32_t>(t56);
    // 0x004c1e52: call 0x4c2110
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, 0x004c1e57u);
    sub_004c2110(ctx, mem);
    // 0x004c1e57: mov ecx, dword ptr [0x7b0a50]
    uint32_t t58 = mem.r32(0x007b0a50u);
    ctx.ecx = static_cast<uint32_t>(t58);
    // 0x004c1e5d: xor ebx, ebx
    uint32_t t59 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t59);
    ctx.ebx = static_cast<uint32_t>(t59);
    // 0x004c1e5f: cmp ecx, ebx
    uint32_t t60 = static_cast<uint32_t>(ctx.ecx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebx, t60);
    // 0x004c1e61: je 0x4c1e6c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004c1e6c;
    goto bb_004c1e63;
}
bb_004c1e1b: {
    // 0x004c1e1b: mov ecx, dword ptr [0x7b0a50]
    uint32_t t61 = mem.r32(0x007b0a50u);
    ctx.ecx = static_cast<uint32_t>(t61);
    // 0x004c1e21: cmp ecx, ebx
    uint32_t t62 = static_cast<uint32_t>(ctx.ecx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebx, t62);
    // 0x004c1e23: jne 0x4c1e35
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004c1e35;
    goto bb_004c1e25;
}
bb_004c1e6c: {
    // 0x004c1e6c: call 0x4e0bf2
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, 0x004c1e71u);
    hle_crt_004e0bf2(ctx, mem);
    // 0x004c1e71: mov ecx, dword ptr [0x7b0a50]
    uint32_t t64 = mem.r32(0x007b0a50u);
    ctx.ecx = static_cast<uint32_t>(t64);
    goto bb_004c1e77;
}
bb_004c1e63: {
    // 0x004c1e63: mov eax, dword ptr [0x7b0a54]
    uint32_t t65 = mem.r32(0x007b0a54u);
    ctx.eax = static_cast<uint32_t>(t65);
    // 0x004c1e68: sub eax, ecx
    uint32_t t66 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t66);
    ctx.eax = static_cast<uint32_t>(t66);
    // 0x004c1e6a: jne 0x4c1e77
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004c1e77;
    goto bb_004c1e6c;
}
bb_004c1e35: {
    // 0x004c1e35: mov eax, dword ptr [0x7b0a54]
    uint32_t t67 = mem.r32(0x007b0a54u);
    ctx.eax = static_cast<uint32_t>(t67);
    // 0x004c1e3a: sub eax, ecx
    uint32_t t68 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t68);
    ctx.eax = static_cast<uint32_t>(t68);
    // 0x004c1e3c: add eax, eax
    uint32_t t69 = static_cast<uint32_t>(ctx.eax + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.eax, t69);
    ctx.eax = static_cast<uint32_t>(t69);
    // 0x004c1e3e: mov ecx, 0x7b0a4c
    ctx.ecx = static_cast<uint32_t>(0x007b0a4cu);
    // 0x004c1e43: call 0x49e990
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, 0x004c1e48u);
    sub_0049e990(ctx, mem);
    // 0x004c1e48: jmp 0x4c1de0
    goto bb_004c1de0;
}
bb_004c1e25: {
    // 0x004c1e25: xor eax, eax
    uint32_t t71 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t71);
    ctx.eax = static_cast<uint32_t>(t71);
    // 0x004c1e27: mov eax, eax
    ctx.eax = static_cast<uint32_t>(ctx.eax);
    // 0x004c1e29: mov ecx, 0x7b0a4c
    ctx.ecx = static_cast<uint32_t>(0x007b0a4cu);
    // 0x004c1e2e: call 0x49e990
    uint32_t t72 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    mem.w32(t72, 0x004c1e33u);
    sub_0049e990(ctx, mem);
    // 0x004c1e33: jmp 0x4c1de0
    goto bb_004c1de0;
}
bb_004c1e77: {
    // 0x004c1e77: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x004c1e79: mov dword ptr [ebp + 0x18], 0xf
    uint32_t t73 = static_cast<uint32_t>(ctx.ebp + 0x00000018u);
    mem.w32(t73, 0x0000000fu);
    // 0x004c1e80: mov dword ptr [ebp + 0x14], ebx
    uint32_t t74 = static_cast<uint32_t>(ctx.ebp + 0x00000014u);
    mem.w32(t74, ctx.ebx);
    // 0x004c1e83: mov byte ptr [ebp + 4], bl
    uint32_t t75 = static_cast<uint32_t>(ctx.ebp + 0x00000004u);
    mem.w8(t75, recomp_detail::r8l(ctx.ebx));
    // 0x004c1e86: lea esi, [eax + 1]
    uint32_t t76 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.esi = static_cast<uint32_t>(t76);
    // 0x004c1e89: lea esp, [esp]
    ctx.esp = static_cast<uint32_t>(ctx.esp);
}
bb_004c1e90: {
    // 0x004c1e90: mov dl, byte ptr [eax]
    uint8_t t77 = mem.r8(ctx.eax);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t77));
    // 0x004c1e92: add eax, 1
    uint32_t t78 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t78);
    ctx.eax = static_cast<uint32_t>(t78);
    // 0x004c1e95: cmp dl, bl
    uint8_t t79 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)) - static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.edx), recomp_detail::r8l(ctx.ebx), t79);
    // 0x004c1e97: jne 0x4c1e90
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004c1e90;
}
{
    // 0x004c1e99: sub eax, esi
    uint32_t t80 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t80);
    ctx.eax = static_cast<uint32_t>(t80);
    // 0x004c1e9b: push eax
    uint32_t t81 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    mem.w32(t81, ctx.eax);
    // 0x004c1e9c: push ecx
    uint32_t t82 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t82);
    mem.w32(t82, ctx.ecx);
    // 0x004c1e9d: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x004c1e9f: call 0x407c10
    uint32_t t83 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t83);
    mem.w32(t83, 0x004c1ea4u);
    sub_00407c10(ctx, mem);
    // 0x004c1ea4: mov eax, ebp
    ctx.eax = static_cast<uint32_t>(ctx.ebp);
    // 0x004c1ea6: mov ecx, dword ptr [esp + 0x28]
    uint32_t t84 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t85 = mem.r32(t84);
    ctx.ecx = static_cast<uint32_t>(t85);
    // 0x004c1eaa: mov dword ptr fs:[0], ecx
    uint32_t t86 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t86, ctx.ecx);
    // 0x004c1eb1: pop ecx
    uint32_t t87 = ctx.esp;
    uint32_t t88 = mem.r32(t87);
    uint32_t t89 = static_cast<uint32_t>(t87 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t89);
    ctx.ecx = static_cast<uint32_t>(t88);
    // 0x004c1eb2: pop edi
    uint32_t t90 = ctx.esp;
    uint32_t t91 = mem.r32(t90);
    uint32_t t92 = static_cast<uint32_t>(t90 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    ctx.edi = static_cast<uint32_t>(t91);
    // 0x004c1eb3: pop esi
    uint32_t t93 = ctx.esp;
    uint32_t t94 = mem.r32(t93);
    uint32_t t95 = static_cast<uint32_t>(t93 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t95);
    ctx.esi = static_cast<uint32_t>(t94);
    // 0x004c1eb4: pop ebp
    uint32_t t96 = ctx.esp;
    uint32_t t97 = mem.r32(t96);
    uint32_t t98 = static_cast<uint32_t>(t96 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t98);
    ctx.ebp = static_cast<uint32_t>(t97);
    // 0x004c1eb5: pop ebx
    uint32_t t99 = ctx.esp;
    uint32_t t100 = mem.r32(t99);
    uint32_t t101 = static_cast<uint32_t>(t99 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t101);
    ctx.ebx = static_cast<uint32_t>(t100);
    // 0x004c1eb6: add esp, 0x20
    uint32_t t102 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000020u, t102);
    ctx.esp = static_cast<uint32_t>(t102);
    // 0x004c1eb9: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004c2110 | subsystem=FilePacFunc | canonical | 6 blocks | 42 insns
void sub_004c2110(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004c2110: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x004c2111: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x004c2113: and esp, 0xfffffff8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xfffffff8u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x004c2116: mov edx, dword ptr [0x7b0a54]
    uint32_t t2 = mem.r32(0x007b0a54u);
    ctx.edx = static_cast<uint32_t>(t2);
    // 0x004c211c: sub esp, 8
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000008u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000008u, t3);
    ctx.esp = static_cast<uint32_t>(t3);
    // 0x004c211f: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x004c2120: mov esi, dword ptr [0x7b0a50]
    uint32_t t5 = mem.r32(0x007b0a50u);
    ctx.esi = static_cast<uint32_t>(t5);
    // 0x004c2126: test esi, esi
    uint32_t t6 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t6);
    // 0x004c2128: push edi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.edi);
    // 0x004c2129: je 0x4c214f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004c214f;
    goto bb_004c212b;
}
bb_004c214f: {
    // 0x004c214f: cmp esi, edx
    uint32_t t8 = static_cast<uint32_t>(ctx.esi - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edx, t8);
    // 0x004c2151: mov edi, edx
    ctx.edi = static_cast<uint32_t>(ctx.edx);
    // 0x004c2153: jbe 0x4c215a
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_004c215a;
    goto bb_004c2155;
}
bb_004c212b: {
    // 0x004c212b: mov ecx, dword ptr [0x7b0a58]
    uint32_t t9 = mem.r32(0x007b0a58u);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x004c2131: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004c2133: sub eax, esi
    uint32_t t10 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t10);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x004c2135: sub ecx, esi
    uint32_t t11 = static_cast<uint32_t>(ctx.ecx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.esi, t11);
    ctx.ecx = static_cast<uint32_t>(t11);
    // 0x004c2137: cmp eax, ecx
    uint32_t t12 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t12);
    // 0x004c2139: jae 0x4c214f
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004c214f;
    goto bb_004c213b;
}
bb_004c215a: {
    // 0x004c215a: push edi
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, ctx.edi);
    // 0x004c215b: mov eax, 0x7b0a4c
    ctx.eax = static_cast<uint32_t>(0x007b0a4cu);
    // 0x004c2160: push eax
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, ctx.eax);
    // 0x004c2161: push ebx
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.ebx);
    // 0x004c2162: lea edx, [esp + 0x14]
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.edx = static_cast<uint32_t>(t16);
    // 0x004c2166: push edx
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, ctx.edx);
    // 0x004c2167: call 0x4c21d0
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x004c216cu);
    sub_004c21d0(ctx, mem);
    // 0x004c216c: pop edi
    uint32_t t19 = ctx.esp;
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t19 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    ctx.edi = static_cast<uint32_t>(t20);
    // 0x004c216d: pop esi
    uint32_t t22 = ctx.esp;
    uint32_t t23 = mem.r32(t22);
    uint32_t t24 = static_cast<uint32_t>(t22 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    ctx.esi = static_cast<uint32_t>(t23);
    // 0x004c216e: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x004c2170: pop ebp
    uint32_t t25 = ctx.esp;
    uint32_t t26 = mem.r32(t25);
    uint32_t t27 = static_cast<uint32_t>(t25 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    ctx.ebp = static_cast<uint32_t>(t26);
    // 0x004c2171: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c2155: {
    // 0x004c2155: call 0x4e0bf2
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x004c215au);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004c215a;
}
bb_004c213b: {
    // 0x004c213b: mov cl, byte ptr [ebx]
    uint8_t t29 = mem.r8(ctx.ebx);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t29));
    // 0x004c213d: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004c213f: add eax, 1
    uint32_t t30 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t30);
    ctx.eax = static_cast<uint32_t>(t30);
    // 0x004c2142: mov byte ptr [edx], cl
    mem.w8(ctx.edx, recomp_detail::r8l(ctx.ecx));
    // 0x004c2144: mov dword ptr [0x7b0a54], eax
    mem.w32(0x007b0a54u, ctx.eax);
    // 0x004c2149: pop edi
    uint32_t t31 = ctx.esp;
    uint32_t t32 = mem.r32(t31);
    uint32_t t33 = static_cast<uint32_t>(t31 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    ctx.edi = static_cast<uint32_t>(t32);
    // 0x004c214a: pop esi
    uint32_t t34 = ctx.esp;
    uint32_t t35 = mem.r32(t34);
    uint32_t t36 = static_cast<uint32_t>(t34 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    ctx.esi = static_cast<uint32_t>(t35);
    // 0x004c214b: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x004c214d: pop ebp
    uint32_t t37 = ctx.esp;
    uint32_t t38 = mem.r32(t37);
    uint32_t t39 = static_cast<uint32_t>(t37 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    ctx.ebp = static_cast<uint32_t>(t38);
    // 0x004c214e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004c2180 | subsystem=FilePacFunc | canonical | 7 blocks | 32 insns
void sub_004c2180(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004c2180: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x004c2182: cmp edi, eax
    uint32_t t1 = static_cast<uint32_t>(ctx.edi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.eax, t1);
    // 0x004c2184: push ebp
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebp);
    // 0x004c2185: mov dword ptr [esi + 4], eax
    uint32_t t3 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t3, ctx.eax);
    // 0x004c2188: mov dword ptr [esi + 8], eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t4, ctx.eax);
    // 0x004c218b: mov dword ptr [esi + 0xc], eax
    uint32_t t5 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t5, ctx.eax);
    // 0x004c218e: je 0x4c21cc
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004c21cc;
    goto bb_004c2190;
}
bb_004c21cc: {
    // 0x004c21cc: pop ebp
    uint32_t t6 = ctx.esp;
    uint32_t t7 = mem.r32(t6);
    uint32_t t8 = static_cast<uint32_t>(t6 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    ctx.ebp = static_cast<uint32_t>(t7);
    // 0x004c21cd: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c2190: {
    // 0x004c2190: cmp edi, -1
    uint32_t t9 = static_cast<uint32_t>(ctx.edi - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, 0xffffffffu, t9);
    // 0x004c2193: jbe 0x4c219a
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_004c219a;
    goto bb_004c2195;
}
bb_004c219a: {
    // 0x004c219a: push eax
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.eax);
    // 0x004c219b: push edi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.edi);
    // 0x004c219c: call 0x408180
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x004c21a1u);
    sub_00408180(ctx, mem);
    // 0x004c21a1: lea ecx, [eax + edi]
    uint32_t t13 = static_cast<uint32_t>(ctx.eax + ctx.edi);
    ctx.ecx = static_cast<uint32_t>(t13);
    // 0x004c21a4: add esp, 8
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t14);
    ctx.esp = static_cast<uint32_t>(t14);
    // 0x004c21a7: test edi, edi
    uint32_t t15 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t15);
    // 0x004c21a9: mov dword ptr [esi + 0xc], ecx
    uint32_t t16 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t16, ctx.ecx);
    // 0x004c21ac: mov dword ptr [esi + 4], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t17, ctx.eax);
    // 0x004c21af: mov dword ptr [esi + 8], eax
    uint32_t t18 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t18, ctx.eax);
    // 0x004c21b2: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004c21b4: mov ebp, eax
    ctx.ebp = static_cast<uint32_t>(ctx.eax);
    // 0x004c21b6: jbe 0x4c21c7
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_004c21c7;
    goto bb_004c21b8;
}
bb_004c2195: {
    // 0x004c2195: jmp 0x407b70
    sub_00407b70(ctx, mem);
    return;
}
bb_004c21c7: {
    // 0x004c21c7: add eax, edi
    uint32_t t19 = static_cast<uint32_t>(ctx.eax + ctx.edi);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edi, t19);
    ctx.eax = static_cast<uint32_t>(t19);
    // 0x004c21c9: mov dword ptr [esi + 8], eax
    uint32_t t20 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t20, ctx.eax);
    goto bb_004c21cc;
}
bb_004c21b8: {
    // 0x004c21b8: mov dl, byte ptr [ebx]
    uint8_t t21 = mem.r8(ctx.ebx);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t21));
    // 0x004c21ba: mov byte ptr [ebp], dl
    mem.w8(ctx.ebp, recomp_detail::r8l(ctx.edx));
    // 0x004c21bd: sub ecx, 1
    uint32_t t22 = static_cast<uint32_t>(ctx.ecx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000001u, t22);
    ctx.ecx = static_cast<uint32_t>(t22);
    // 0x004c21c0: add ebp, 1
    uint32_t t23 = static_cast<uint32_t>(ctx.ebp + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebp, 0x00000001u, t23);
    ctx.ebp = static_cast<uint32_t>(t23);
    // 0x004c21c3: test ecx, ecx
    uint32_t t24 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t24);
    // 0x004c21c5: ja 0x4c21b8
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_004c21b8;
    goto bb_004c21c7;
}
}

// sub_004c21d0 | subsystem=FilePacFunc | canonical | 15 blocks | 57 insns
void sub_004c21d0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004c21d0: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x004c21d1: mov eax, dword ptr [0x7b0a50]
    uint32_t t1 = mem.r32(0x007b0a50u);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x004c21d6: test eax, eax
    uint32_t t2 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    // 0x004c21d8: push ebx
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.ebx);
    // 0x004c21d9: mov ebx, dword ptr [esp + 0x18]
    uint32_t t4 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t5 = mem.r32(t4);
    ctx.ebx = static_cast<uint32_t>(t5);
    // 0x004c21dd: push ebp
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebp);
    // 0x004c21de: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x004c21df: mov esi, dword ptr [esp + 0x1c]
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t9 = mem.r32(t8);
    ctx.esi = static_cast<uint32_t>(t9);
    // 0x004c21e3: push edi
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.edi);
    // 0x004c21e4: je 0x4c21f2
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004c21f2;
    goto bb_004c21e6;
}
bb_004c21f2: {
    // 0x004c21f2: xor edi, edi
    uint32_t t11 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    ctx.edi = static_cast<uint32_t>(t11);
    // 0x004c21f4: jmp 0x4c2216
    goto bb_004c2216;
}
bb_004c21e6: {
    // 0x004c21e6: mov ecx, dword ptr [0x7b0a54]
    uint32_t t12 = mem.r32(0x007b0a54u);
    ctx.ecx = static_cast<uint32_t>(t12);
    // 0x004c21ec: mov edx, ecx
    ctx.edx = static_cast<uint32_t>(ctx.ecx);
    // 0x004c21ee: sub edx, eax
    uint32_t t13 = static_cast<uint32_t>(ctx.edx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.eax, t13);
    ctx.edx = static_cast<uint32_t>(t13);
    // 0x004c21f0: jne 0x4c21f6
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004c21f6;
    goto bb_004c21f2;
}
bb_004c2216: {
    // 0x004c2216: mov eax, dword ptr [esp + 0x1c]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t15 = mem.r32(t14);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x004c221a: push ebx
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, ctx.ebx);
    // 0x004c221b: push esi
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, ctx.esi);
    // 0x004c221c: push 1
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x00000001u);
    // 0x004c221e: mov ecx, 0x7b0a4c
    ctx.ecx = static_cast<uint32_t>(0x007b0a4cu);
    // 0x004c2223: call 0x49eac0
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x004c2228u);
    sub_0049eac0(ctx, mem);
    // 0x004c2228: mov ecx, dword ptr [0x7b0a50]
    uint32_t t20 = mem.r32(0x007b0a50u);
    ctx.ecx = static_cast<uint32_t>(t20);
    // 0x004c222e: cmp ecx, dword ptr [0x7b0a54]
    uint32_t t21 = mem.r32(0x007b0a54u);
    uint32_t t22 = static_cast<uint32_t>(ctx.ecx - t21);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, t21, t22);
    // 0x004c2234: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004c2236: jbe 0x4c2243
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_004c2243;
    goto bb_004c2238;
}
bb_004c21f6: {
    // 0x004c21f6: cmp eax, ecx
    uint32_t t23 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t23);
    // 0x004c21f8: mov ebp, eax
    ctx.ebp = static_cast<uint32_t>(ctx.eax);
    // 0x004c21fa: jbe 0x4c2201
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_004c2201;
    goto bb_004c21fc;
}
bb_004c2243: {
    // 0x004c2243: mov dword ptr [esp + 0x24], esi
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t24, ctx.esi);
    // 0x004c2247: add esi, edi
    uint32_t t25 = static_cast<uint32_t>(ctx.esi + ctx.edi);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, ctx.edi, t25);
    ctx.esi = static_cast<uint32_t>(t25);
    // 0x004c2249: cmp esi, dword ptr [0x7b0a54]
    uint32_t t26 = mem.r32(0x007b0a54u);
    uint32_t t27 = static_cast<uint32_t>(ctx.esi - t26);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, t26, t27);
    // 0x004c224f: mov eax, 0x7b0a4c
    ctx.eax = static_cast<uint32_t>(0x007b0a4cu);
    // 0x004c2254: mov ebx, eax
    ctx.ebx = static_cast<uint32_t>(ctx.eax);
    // 0x004c2256: ja 0x4c225c
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_004c225c;
    goto bb_004c2258;
}
bb_004c2238: {
    // 0x004c2238: call 0x4e0bf2
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x004c223du);
    hle_crt_004e0bf2(ctx, mem);
    // 0x004c223d: mov ecx, dword ptr [0x7b0a50]
    uint32_t t29 = mem.r32(0x007b0a50u);
    ctx.ecx = static_cast<uint32_t>(t29);
    goto bb_004c2243;
}
bb_004c2201: {
    // 0x004c2201: test esi, esi
    uint32_t t30 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t30);
    // 0x004c2203: je 0x4c220d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004c220d;
    goto bb_004c2205;
}
bb_004c21fc: {
    // 0x004c21fc: call 0x4e0bf2
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x004c2201u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004c2201;
}
bb_004c225c: {
    // 0x004c225c: call 0x4e0bf2
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x004c2261u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004c2261;
}
bb_004c2258: {
    // 0x004c2258: cmp esi, ecx
    uint32_t t33 = static_cast<uint32_t>(ctx.esi - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ecx, t33);
    // 0x004c225a: jae 0x4c2261
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004c2261;
    goto bb_004c225c;
}
bb_004c220d: {
    // 0x004c220d: call 0x4e0bf2
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x004c2212u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004c2212;
}
bb_004c2205: {
    // 0x004c2205: cmp esi, 0x7b0a4c
    uint32_t t35 = static_cast<uint32_t>(ctx.esi - 0x007b0a4cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x007b0a4cu, t35);
    // 0x004c220b: je 0x4c2212
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004c2212;
    goto bb_004c220d;
}
bb_004c2261: {
    // 0x004c2261: mov eax, dword ptr [esp + 0x18]
    uint32_t t36 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t37 = mem.r32(t36);
    ctx.eax = static_cast<uint32_t>(t37);
    // 0x004c2265: pop edi
    uint32_t t38 = ctx.esp;
    uint32_t t39 = mem.r32(t38);
    uint32_t t40 = static_cast<uint32_t>(t38 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    ctx.edi = static_cast<uint32_t>(t39);
    // 0x004c2266: mov dword ptr [eax + 4], esi
    uint32_t t41 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w32(t41, ctx.esi);
    // 0x004c2269: pop esi
    uint32_t t42 = ctx.esp;
    uint32_t t43 = mem.r32(t42);
    uint32_t t44 = static_cast<uint32_t>(t42 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    ctx.esi = static_cast<uint32_t>(t43);
    // 0x004c226a: pop ebp
    uint32_t t45 = ctx.esp;
    uint32_t t46 = mem.r32(t45);
    uint32_t t47 = static_cast<uint32_t>(t45 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    ctx.ebp = static_cast<uint32_t>(t46);
    // 0x004c226b: mov dword ptr [eax], ebx
    mem.w32(ctx.eax, ctx.ebx);
    // 0x004c226d: pop ebx
    uint32_t t48 = ctx.esp;
    uint32_t t49 = mem.r32(t48);
    uint32_t t50 = static_cast<uint32_t>(t48 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    ctx.ebx = static_cast<uint32_t>(t49);
    // 0x004c226e: pop ecx
    uint32_t t51 = ctx.esp;
    uint32_t t52 = mem.r32(t51);
    uint32_t t53 = static_cast<uint32_t>(t51 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    ctx.ecx = static_cast<uint32_t>(t52);
    // 0x004c226f: ret 0x10
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 16u;
    return;
}
bb_004c2212: {
    // 0x004c2212: mov edi, ebx
    ctx.edi = static_cast<uint32_t>(ctx.ebx);
    // 0x004c2214: sub edi, ebp
    uint32_t t54 = static_cast<uint32_t>(ctx.edi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebp, t54);
    ctx.edi = static_cast<uint32_t>(t54);
    goto bb_004c2216;
}
}

// sub_004db400 | subsystem=FilePacFunc | canonical | 1 blocks | 31 insns
void sub_004db400(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004db400: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x004db402: push 0x514a38
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00514a38u);
    // 0x004db407: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004db40d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x004db40e: push esi
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.esi);
    // 0x004db40f: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x004db414: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x004db416: push eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.eax);
    // 0x004db417: lea eax, [esp + 8]
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x004db41b: mov dword ptr fs:[0], eax
    uint32_t t10 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t10, ctx.eax);
    // 0x004db421: mov esi, dword ptr [esp + 0x18]
    uint32_t t11 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t12 = mem.r32(t11);
    ctx.esi = static_cast<uint32_t>(t12);
    // 0x004db425: xor eax, eax
    uint32_t t13 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t13);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x004db427: mov dword ptr [esi + 0x18], 0xf
    uint32_t t14 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    mem.w32(t14, 0x0000000fu);
    // 0x004db42e: mov dword ptr [esi + 0x14], eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esi + 0x00000014u);
    mem.w32(t15, ctx.eax);
    // 0x004db431: mov byte ptr [esi + 4], al
    uint32_t t16 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w8(t16, recomp_detail::r8l(ctx.eax));
    // 0x004db434: mov dword ptr [esp + 0x10], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t17, ctx.eax);
    // 0x004db438: push eax
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, ctx.eax);
    // 0x004db439: push 0x534f8a
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x00534f8au);
    // 0x004db43e: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004db440: mov dword ptr [esi + 0x20], eax
    uint32_t t20 = static_cast<uint32_t>(ctx.esi + 0x00000020u);
    mem.w32(t20, ctx.eax);
    // 0x004db443: mov dword ptr [esi + 0x24], eax
    uint32_t t21 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    mem.w32(t21, ctx.eax);
    // 0x004db446: mov dword ptr [esi + 0x28], eax
    uint32_t t22 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    mem.w32(t22, ctx.eax);
    // 0x004db449: mov dword ptr [esi + 0x1c], eax
    uint32_t t23 = static_cast<uint32_t>(ctx.esi + 0x0000001cu);
    mem.w32(t23, ctx.eax);
    // 0x004db44c: call 0x407c10
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x004db451u);
    sub_00407c10(ctx, mem);
    // 0x004db451: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004db453: mov ecx, dword ptr [esp + 8]
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t26 = mem.r32(t25);
    ctx.ecx = static_cast<uint32_t>(t26);
    // 0x004db457: mov dword ptr fs:[0], ecx
    uint32_t t27 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t27, ctx.ecx);
    // 0x004db45e: pop ecx
    uint32_t t28 = ctx.esp;
    uint32_t t29 = mem.r32(t28);
    uint32_t t30 = static_cast<uint32_t>(t28 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    ctx.ecx = static_cast<uint32_t>(t29);
    // 0x004db45f: pop esi
    uint32_t t31 = ctx.esp;
    uint32_t t32 = mem.r32(t31);
    uint32_t t33 = static_cast<uint32_t>(t31 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    ctx.esi = static_cast<uint32_t>(t32);
    // 0x004db460: add esp, 0xc
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t34);
    ctx.esp = static_cast<uint32_t>(t34);
    // 0x004db463: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
}

// sub_004db470 | subsystem=FilePacFunc | canonical | 9 blocks | 29 insns
void sub_004db470(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004db470: mov eax, dword ptr [edi + 0x14]
    uint32_t t0 = static_cast<uint32_t>(ctx.edi + 0x00000014u);
    uint32_t t1 = mem.r32(t0);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x004db473: push ebx
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebx);
    // 0x004db474: push esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.esi);
    // 0x004db475: xor ebx, ebx
    uint32_t t4 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    ctx.ebx = static_cast<uint32_t>(t4);
    // 0x004db477: xor esi, esi
    uint32_t t5 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    ctx.esi = static_cast<uint32_t>(t5);
    // 0x004db479: test eax, eax
    uint32_t t6 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t6);
    // 0x004db47b: jbe 0x4db4ab
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_004db4ab;
    goto bb_004db47d;
}
bb_004db4ab: {
    // 0x004db4ab: pop esi
    uint32_t t7 = ctx.esp;
    uint32_t t8 = mem.r32(t7);
    uint32_t t9 = static_cast<uint32_t>(t7 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    ctx.esi = static_cast<uint32_t>(t8);
    // 0x004db4ac: mov eax, ebx
    ctx.eax = static_cast<uint32_t>(ctx.ebx);
    // 0x004db4ae: pop ebx
    uint32_t t10 = ctx.esp;
    uint32_t t11 = mem.r32(t10);
    uint32_t t12 = static_cast<uint32_t>(t10 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    ctx.ebx = static_cast<uint32_t>(t11);
    // 0x004db4af: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004db47d: {
    // 0x004db47d: cmp esi, eax
    uint32_t t13 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t13);
    // 0x004db47f: push ebp
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, ctx.ebp);
    // 0x004db480: lea ebp, [edi + 4]
    uint32_t t15 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    ctx.ebp = static_cast<uint32_t>(t15);
    // 0x004db483: jbe 0x4db48a
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_004db48a;
    goto bb_004db485;
}
bb_004db48a: {
    // 0x004db48a: cmp dword ptr [edi + 0x18], 0x10
    uint32_t t16 = static_cast<uint32_t>(ctx.edi + 0x00000018u);
    uint32_t t17 = mem.r32(t16);
    uint32_t t18 = static_cast<uint32_t>(t17 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t17, 0x00000010u, t18);
    // 0x004db48e: jb 0x4db495
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004db495;
    goto bb_004db490;
}
bb_004db485: {
    // 0x004db485: call 0x4e0bf2
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x004db48au);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004db48a;
}
bb_004db495: {
    // 0x004db495: mov eax, ebp
    ctx.eax = static_cast<uint32_t>(ctx.ebp);
    goto bb_004db497;
}
bb_004db490: {
    // 0x004db490: mov eax, dword ptr [ebp]
    uint32_t t20 = mem.r32(ctx.ebp);
    ctx.eax = static_cast<uint32_t>(t20);
    // 0x004db493: jmp 0x4db497
}
bb_004db497: {
    // 0x004db497: movsx eax, byte ptr [eax + esi]
    uint32_t t21 = static_cast<uint32_t>(ctx.eax + ctx.esi);
    uint8_t t22 = mem.r8(t21);
    uint32_t t23 = recomp_detail::sext8_32(static_cast<uint8_t>(t22));
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x004db49b: imul eax, esi
    uint64_t t24 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.esi)));
    uint32_t t25 = static_cast<uint32_t>(t24);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t24);
    ctx.eax = static_cast<uint32_t>(t25);
    // 0x004db49e: add ebx, eax
    uint32_t t26 = static_cast<uint32_t>(ctx.ebx + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebx, ctx.eax, t26);
    ctx.ebx = static_cast<uint32_t>(t26);
    // 0x004db4a0: mov eax, dword ptr [edi + 0x14]
    uint32_t t27 = static_cast<uint32_t>(ctx.edi + 0x00000014u);
    uint32_t t28 = mem.r32(t27);
    ctx.eax = static_cast<uint32_t>(t28);
    // 0x004db4a3: add esi, 1
    uint32_t t29 = static_cast<uint32_t>(ctx.esi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000001u, t29);
    ctx.esi = static_cast<uint32_t>(t29);
    // 0x004db4a6: cmp esi, eax
    uint32_t t30 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t30);
    // 0x004db4a8: jb 0x4db48a
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004db48a;
}
{
    // 0x004db4aa: pop ebp
    uint32_t t31 = ctx.esp;
    uint32_t t32 = mem.r32(t31);
    uint32_t t33 = static_cast<uint32_t>(t31 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    ctx.ebp = static_cast<uint32_t>(t32);
    goto bb_004db4ab;
}
}

// sub_004db4b0 | subsystem=FilePacFunc | canonical | 1 blocks | 31 insns
void sub_004db4b0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004db4b0: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x004db4b2: mov dword ptr [esi], eax
    mem.w32(ctx.esi, ctx.eax);
    // 0x004db4b4: mov dword ptr [esi + 4], eax
    uint32_t t1 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t1, ctx.eax);
    // 0x004db4b7: mov dword ptr [esi + 8], eax
    uint32_t t2 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t2, ctx.eax);
    // 0x004db4ba: mov dword ptr [esi + 0xc], eax
    uint32_t t3 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t3, ctx.eax);
    // 0x004db4bd: mov eax, dword ptr [0x53d504]
    uint32_t t4 = mem.r32(0x0053d504u);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x004db4c2: mov dword ptr [esi], eax
    mem.w32(ctx.esi, ctx.eax);
    // 0x004db4c4: mov ecx, dword ptr [0x53d508]
    uint32_t t5 = mem.r32(0x0053d508u);
    ctx.ecx = static_cast<uint32_t>(t5);
    // 0x004db4ca: mov dword ptr [esi + 4], ecx
    uint32_t t6 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t6, ctx.ecx);
    // 0x004db4cd: mov edx, dword ptr [0x53d50c]
    uint32_t t7 = mem.r32(0x0053d50cu);
    ctx.edx = static_cast<uint32_t>(t7);
    // 0x004db4d3: mov dword ptr [esi + 8], edx
    uint32_t t8 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t8, ctx.edx);
    // 0x004db4d6: mov ax, word ptr [0x53d510]
    uint16_t t9 = mem.r16(0x0053d510u);
    recomp_detail::w16(ctx.eax, static_cast<uint16_t>(t9));
    // 0x004db4dc: push edi
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.edi);
    // 0x004db4dd: mov word ptr [esi + 0xc], ax
    uint32_t t11 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w16(t11, recomp_detail::r16(ctx.eax));
    // 0x004db4e1: mov cl, byte ptr [0x53d512]
    uint8_t t12 = mem.r8(0x0053d512u);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t12));
    // 0x004db4e7: xor edi, edi
    uint32_t t13 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t13);
    ctx.edi = static_cast<uint32_t>(t13);
    // 0x004db4e9: push edi
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, ctx.edi);
    // 0x004db4ea: mov byte ptr [esi + 0xe], cl
    uint32_t t15 = static_cast<uint32_t>(ctx.esi + 0x0000000eu);
    mem.w8(t15, recomp_detail::r8l(ctx.ecx));
    // 0x004db4ed: mov dword ptr [esi + 0x10], 1
    uint32_t t16 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    mem.w32(t16, 0x00000001u);
    // 0x004db4f4: call 0x4e1cfc
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x004db4f9u);
    hle_crt_004e1cfc(ctx, mem);
    // 0x004db4f9: add esp, 4
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t18);
    ctx.esp = static_cast<uint32_t>(t18);
    // 0x004db4fc: mov dword ptr [esi + 0x18], edi
    uint32_t t19 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    mem.w32(t19, ctx.edi);
    // 0x004db4ff: mov dword ptr [esi + 0x1c], edi
    uint32_t t20 = static_cast<uint32_t>(ctx.esi + 0x0000001cu);
    mem.w32(t20, ctx.edi);
    // 0x004db502: mov dword ptr [esi + 0x20], edi
    uint32_t t21 = static_cast<uint32_t>(ctx.esi + 0x00000020u);
    mem.w32(t21, ctx.edi);
    // 0x004db505: mov dword ptr [esi + 0x24], edi
    uint32_t t22 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    mem.w32(t22, ctx.edi);
    // 0x004db508: mov dword ptr [esi + 0x14], eax
    uint32_t t23 = static_cast<uint32_t>(ctx.esi + 0x00000014u);
    mem.w32(t23, ctx.eax);
    // 0x004db50b: mov dword ptr [esi + 0x28], 1
    uint32_t t24 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    mem.w32(t24, 0x00000001u);
    // 0x004db512: mov dword ptr [esi + 0x2c], 3
    uint32_t t25 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    mem.w32(t25, 0x00000003u);
    // 0x004db519: mov dword ptr [esi + 0x30], 0x1000
    uint32_t t26 = static_cast<uint32_t>(ctx.esi + 0x00000030u);
    mem.w32(t26, 0x00001000u);
    // 0x004db520: pop edi
    uint32_t t27 = ctx.esp;
    uint32_t t28 = mem.r32(t27);
    uint32_t t29 = static_cast<uint32_t>(t27 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    ctx.edi = static_cast<uint32_t>(t28);
    // 0x004db521: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004db530 | subsystem=FilePacFunc | canonical | 5 blocks | 26 insns
void sub_004db530(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004db530: sub esp, 0x18
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000018u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000018u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x004db533: mov eax, dword ptr [0x54b458]
    uint32_t t1 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x004db538: xor eax, esp
    uint32_t t2 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x004db53a: mov dword ptr [esp + 0x14], eax
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t3, ctx.eax);
    // 0x004db53e: mov eax, dword ptr [esp + 0x1c]
    uint32_t t4 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t5 = mem.r32(t4);
    ctx.eax = static_cast<uint32_t>(t5);
    // 0x004db542: mov eax, dword ptr [eax + 0x14]
    uint32_t t6 = static_cast<uint32_t>(ctx.eax + 0x00000014u);
    uint32_t t7 = mem.r32(t6);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x004db545: test eax, eax
    uint32_t t8 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t8);
    // 0x004db547: je 0x4db579
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004db579;
    goto bb_004db549;
}
bb_004db579: {
    // 0x004db579: mov ecx, dword ptr [esp + 0x14]
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t10 = mem.r32(t9);
    ctx.ecx = static_cast<uint32_t>(t10);
    // 0x004db57d: xor ecx, esp
    uint32_t t11 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    ctx.ecx = static_cast<uint32_t>(t11);
    // 0x004db57f: call 0x4e02f8
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x004db584u);
    hle_crt_004e02f8(ctx, mem);
    // 0x004db584: add esp, 0x18
    uint32_t t13 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000018u, t13);
    ctx.esp = static_cast<uint32_t>(t13);
    // 0x004db587: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_004db549: {
    // 0x004db549: test dl, dl
    uint8_t t14 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t14);
    // 0x004db54b: mov dword ptr [esp + 0x10], esi
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t15, ctx.esi);
    // 0x004db54f: mov dword ptr [esp], eax
    mem.w32(ctx.esp, ctx.eax);
    // 0x004db552: mov byte ptr [esp + 4], 1
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    mem.w8(t16, uint8_t{0x01u});
    // 0x004db557: je 0x4db55d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004db55d;
    goto bb_004db559;
}
bb_004db55d: {
    // 0x004db55d: push esi
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, ctx.esi);
    // 0x004db55e: mov dword ptr [esp + 0xa], eax
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x0000000au);
    mem.w32(t18, ctx.eax);
    // 0x004db562: push ecx
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, ctx.ecx);
    // 0x004db563: lea eax, [esp + 8]
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.eax = static_cast<uint32_t>(t20);
    // 0x004db567: mov dword ptr [esp + 0x14], 0
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t21, 0x00000000u);
    // 0x004db56f: mov byte ptr [esp + 0xd], 0
    uint32_t t22 = static_cast<uint32_t>(ctx.esp + 0x0000000du);
    mem.w8(t22, uint8_t{0x00u});
    // 0x004db574: call 0x4db5e0
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x004db579u);
    sub_004db5e0(ctx, mem);
    goto bb_004db579;
}
bb_004db559: {
    // 0x004db559: mov byte ptr [esp + 4], dl
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    mem.w8(t24, recomp_detail::r8l(ctx.edx));
    goto bb_004db55d;
}
}

// sub_004db590 | subsystem=FilePacFunc | canonical | 7 blocks | 25 insns
void sub_004db590(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004db590: xor edx, edx
    uint32_t t0 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.edx = static_cast<uint32_t>(t0);
    // 0x004db592: cmp ecx, edx
    uint32_t t1 = static_cast<uint32_t>(ctx.ecx - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.edx, t1);
    // 0x004db594: push esi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.esi);
    // 0x004db595: mov esi, dword ptr [eax]
    uint32_t t3 = mem.r32(ctx.eax);
    ctx.esi = static_cast<uint32_t>(t3);
    // 0x004db597: mov dword ptr [eax + 0xc], edx
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    mem.w32(t4, ctx.edx);
    // 0x004db59a: mov dword ptr [eax + 6], esi
    uint32_t t5 = static_cast<uint32_t>(ctx.eax + 0x00000006u);
    mem.w32(t5, ctx.esi);
    // 0x004db59d: mov byte ptr [eax + 5], dl
    uint32_t t6 = static_cast<uint32_t>(ctx.eax + 0x00000005u);
    mem.w8(t6, recomp_detail::r8l(ctx.edx));
    // 0x004db5a0: jbe 0x4db5d1
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_004db5d1;
    goto bb_004db5a2;
}
bb_004db5d1: {
    // 0x004db5d1: pop esi
    uint32_t t7 = ctx.esp;
    uint32_t t8 = mem.r32(t7);
    uint32_t t9 = static_cast<uint32_t>(t7 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    ctx.esi = static_cast<uint32_t>(t8);
    // 0x004db5d2: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004db5a2: {
    // 0x004db5a2: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004db5a4: mov edx, 1
    ctx.edx = static_cast<uint32_t>(0x00000001u);
    // 0x004db5a9: push ebx
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.ebx);
    // 0x004db5aa: lea ebx, [ebx]
    ctx.ebx = static_cast<uint32_t>(ctx.ebx);
}
bb_004db5b0: {
    // 0x004db5b0: movzx ecx, byte ptr [eax + 5]
    uint32_t t11 = static_cast<uint32_t>(ctx.eax + 0x00000005u);
    uint8_t t12 = mem.r8(t11);
    uint32_t t13 = static_cast<uint32_t>(static_cast<uint8_t>(t12));
    ctx.ecx = static_cast<uint32_t>(t13);
    // 0x004db5b4: mov bl, byte ptr [eax + 4]
    uint32_t t14 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint8_t t15 = mem.r8(t14);
    recomp_detail::w8l(ctx.ebx, static_cast<uint8_t>(t15));
    // 0x004db5b7: add byte ptr [ecx + eax + 6], bl
    uint32_t t16 = static_cast<uint32_t>(ctx.ecx + ctx.eax);
    uint32_t t17 = static_cast<uint32_t>(t16 + 0x00000006u);
    uint8_t t18 = mem.r8(t17);
    uint8_t t19 = static_cast<uint8_t>(static_cast<uint32_t>(t18) + static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_add<uint8_t>(ctx, t18, recomp_detail::r8l(ctx.ebx), t19);
    mem.w8(t17, t19);
    // 0x004db5bb: add byte ptr [eax + 5], dl
    uint32_t t20 = static_cast<uint32_t>(ctx.eax + 0x00000005u);
    uint8_t t21 = mem.r8(t20);
    uint8_t t22 = static_cast<uint8_t>(static_cast<uint32_t>(t21) + static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_add<uint8_t>(ctx, t21, recomp_detail::r8l(ctx.edx), t22);
    mem.w8(t20, t22);
    // 0x004db5be: cmp byte ptr [eax + 5], 4
    uint32_t t23 = static_cast<uint32_t>(ctx.eax + 0x00000005u);
    uint8_t t24 = mem.r8(t23);
    uint8_t t25 = static_cast<uint8_t>(static_cast<uint32_t>(t24) - static_cast<uint32_t>(uint8_t{0x04u}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, t24, uint8_t{0x04u}, t25);
    // 0x004db5c2: lea ecx, [ecx + eax + 6]
    uint32_t t26 = static_cast<uint32_t>(ctx.ecx + ctx.eax);
    uint32_t t27 = static_cast<uint32_t>(t26 + 0x00000006u);
    ctx.ecx = static_cast<uint32_t>(t27);
    // 0x004db5c6: jb 0x4db5cc
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004db5cc;
    goto bb_004db5c8;
}
bb_004db5cc: {
    // 0x004db5cc: sub esi, edx
    uint32_t t28 = static_cast<uint32_t>(ctx.esi - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edx, t28);
    ctx.esi = static_cast<uint32_t>(t28);
    // 0x004db5ce: jne 0x4db5b0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004db5b0;
    goto bb_004db5d0;
}
bb_004db5c8: {
    // 0x004db5c8: mov byte ptr [eax + 5], 0
    uint32_t t29 = static_cast<uint32_t>(ctx.eax + 0x00000005u);
    mem.w8(t29, uint8_t{0x00u});
    goto bb_004db5cc;
}
bb_004db5d0: {
    // 0x004db5d0: pop ebx
    uint32_t t30 = ctx.esp;
    uint32_t t31 = mem.r32(t30);
    uint32_t t32 = static_cast<uint32_t>(t30 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    ctx.ebx = static_cast<uint32_t>(t31);
    goto bb_004db5d1;
}
}

// sub_004db5e0 | subsystem=FilePacFunc | canonical | 11 blocks | 35 insns
void sub_004db5e0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004db5e0: mov ecx, dword ptr [eax + 0x10]
    uint32_t t0 = static_cast<uint32_t>(ctx.eax + 0x00000010u);
    uint32_t t1 = mem.r32(t0);
    ctx.ecx = static_cast<uint32_t>(t1);
    // 0x004db5e3: mov edx, dword ptr [eax + 0xc]
    uint32_t t2 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    uint32_t t3 = mem.r32(t2);
    ctx.edx = static_cast<uint32_t>(t3);
    // 0x004db5e6: cmp edx, ecx
    uint32_t t4 = static_cast<uint32_t>(ctx.edx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ecx, t4);
    // 0x004db5e8: jae 0x4db639
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004db639;
    goto bb_004db5ea;
}
bb_004db639: {
    // 0x004db639: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
bb_004db5ea: {
    // 0x004db5ea: push esi
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.esi);
    // 0x004db5eb: mov esi, dword ptr [esp + 8]
    uint32_t t6 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t7 = mem.r32(t6);
    ctx.esi = static_cast<uint32_t>(t7);
    // 0x004db5ef: push edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edi);
    // 0x004db5f0: mov edi, dword ptr [esp + 0x10]
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t10 = mem.r32(t9);
    ctx.edi = static_cast<uint32_t>(t10);
    // 0x004db5f4: add edi, edx
    uint32_t t11 = static_cast<uint32_t>(ctx.edi + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, ctx.edx, t11);
    ctx.edi = static_cast<uint32_t>(t11);
    // 0x004db5f6: cmp ecx, edi
    uint32_t t12 = static_cast<uint32_t>(ctx.ecx - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.edi, t12);
    // 0x004db5f8: jae 0x4db5fc
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004db5fc;
    goto bb_004db5fa;
}
bb_004db5fc: {
    // 0x004db5fc: cmp edx, edi
    uint32_t t13 = static_cast<uint32_t>(ctx.edx - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.edi, t13);
    // 0x004db5fe: jae 0x4db637
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004db637;
    goto bb_004db600;
}
bb_004db5fa: {
    // 0x004db5fa: mov edi, ecx
    ctx.edi = static_cast<uint32_t>(ctx.ecx);
    goto bb_004db5fc;
}
bb_004db637: {
    // 0x004db637: pop edi
    uint32_t t14 = ctx.esp;
    uint32_t t15 = mem.r32(t14);
    uint32_t t16 = static_cast<uint32_t>(t14 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    ctx.edi = static_cast<uint32_t>(t15);
    // 0x004db638: pop esi
    uint32_t t17 = ctx.esp;
    uint32_t t18 = mem.r32(t17);
    uint32_t t19 = static_cast<uint32_t>(t17 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    ctx.esi = static_cast<uint32_t>(t18);
    goto bb_004db639;
}
bb_004db600: {
    // 0x004db600: mov edx, 1
    ctx.edx = static_cast<uint32_t>(0x00000001u);
    // 0x004db605: push ebx
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, ctx.ebx);
}
bb_004db606: {
    // 0x004db606: movzx ecx, byte ptr [eax + 5]
    uint32_t t21 = static_cast<uint32_t>(ctx.eax + 0x00000005u);
    uint8_t t22 = mem.r8(t21);
    uint32_t t23 = static_cast<uint32_t>(static_cast<uint8_t>(t22));
    ctx.ecx = static_cast<uint32_t>(t23);
    // 0x004db60a: mov cl, byte ptr [ecx + eax + 6]
    uint32_t t24 = static_cast<uint32_t>(ctx.ecx + ctx.eax);
    uint32_t t25 = static_cast<uint32_t>(t24 + 0x00000006u);
    uint8_t t26 = mem.r8(t25);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t26));
    // 0x004db60e: xor byte ptr [esi], cl
    uint8_t t27 = mem.r8(ctx.esi);
    uint8_t t28 = static_cast<uint8_t>(static_cast<uint32_t>(t27) ^ static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t28);
    mem.w8(ctx.esi, t28);
    // 0x004db610: movzx ecx, byte ptr [eax + 5]
    uint32_t t29 = static_cast<uint32_t>(ctx.eax + 0x00000005u);
    uint8_t t30 = mem.r8(t29);
    uint32_t t31 = static_cast<uint32_t>(static_cast<uint8_t>(t30));
    ctx.ecx = static_cast<uint32_t>(t31);
    // 0x004db614: mov bl, byte ptr [eax + 4]
    uint32_t t32 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint8_t t33 = mem.r8(t32);
    recomp_detail::w8l(ctx.ebx, static_cast<uint8_t>(t33));
    // 0x004db617: add byte ptr [ecx + eax + 6], bl
    uint32_t t34 = static_cast<uint32_t>(ctx.ecx + ctx.eax);
    uint32_t t35 = static_cast<uint32_t>(t34 + 0x00000006u);
    uint8_t t36 = mem.r8(t35);
    uint8_t t37 = static_cast<uint8_t>(static_cast<uint32_t>(t36) + static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_add<uint8_t>(ctx, t36, recomp_detail::r8l(ctx.ebx), t37);
    mem.w8(t35, t37);
    // 0x004db61b: add byte ptr [eax + 5], dl
    uint32_t t38 = static_cast<uint32_t>(ctx.eax + 0x00000005u);
    uint8_t t39 = mem.r8(t38);
    uint8_t t40 = static_cast<uint8_t>(static_cast<uint32_t>(t39) + static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_add<uint8_t>(ctx, t39, recomp_detail::r8l(ctx.edx), t40);
    mem.w8(t38, t40);
    // 0x004db61e: cmp byte ptr [eax + 5], 4
    uint32_t t41 = static_cast<uint32_t>(ctx.eax + 0x00000005u);
    uint8_t t42 = mem.r8(t41);
    uint8_t t43 = static_cast<uint8_t>(static_cast<uint32_t>(t42) - static_cast<uint32_t>(uint8_t{0x04u}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, t42, uint8_t{0x04u}, t43);
    // 0x004db622: lea ecx, [ecx + eax + 6]
    uint32_t t44 = static_cast<uint32_t>(ctx.ecx + ctx.eax);
    uint32_t t45 = static_cast<uint32_t>(t44 + 0x00000006u);
    ctx.ecx = static_cast<uint32_t>(t45);
    // 0x004db626: jb 0x4db62c
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004db62c;
    goto bb_004db628;
}
bb_004db62c: {
    // 0x004db62c: add dword ptr [eax + 0xc], edx
    uint32_t t46 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    uint32_t t47 = mem.r32(t46);
    uint32_t t48 = static_cast<uint32_t>(t47 + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, t47, ctx.edx, t48);
    mem.w32(t46, t48);
    // 0x004db62f: add esi, edx
    uint32_t t49 = static_cast<uint32_t>(ctx.esi + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, ctx.edx, t49);
    ctx.esi = static_cast<uint32_t>(t49);
    // 0x004db631: cmp dword ptr [eax + 0xc], edi
    uint32_t t50 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    uint32_t t51 = mem.r32(t50);
    uint32_t t52 = static_cast<uint32_t>(t51 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t51, ctx.edi, t52);
    // 0x004db634: jb 0x4db606
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004db606;
    goto bb_004db636;
}
bb_004db628: {
    // 0x004db628: mov byte ptr [eax + 5], 0
    uint32_t t53 = static_cast<uint32_t>(ctx.eax + 0x00000005u);
    mem.w8(t53, uint8_t{0x00u});
    goto bb_004db62c;
}
bb_004db636: {
    // 0x004db636: pop ebx
    uint32_t t54 = ctx.esp;
    uint32_t t55 = mem.r32(t54);
    uint32_t t56 = static_cast<uint32_t>(t54 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    ctx.ebx = static_cast<uint32_t>(t55);
    goto bb_004db637;
}
}

// sub_004db640 | subsystem=FilePacFunc | canonical | 7 blocks | 31 insns
void sub_004db640(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004db640: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x004db641: push 0x5c
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0000005cu);
    // 0x004db643: call 0x4e0177
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x004db648u);
    hle_crt_004e0177(ctx, mem);
    // 0x004db648: add esp, 4
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t3);
    ctx.esp = static_cast<uint32_t>(t3);
    // 0x004db64b: test eax, eax
    uint32_t t4 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    // 0x004db64d: je 0x4db65a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004db65a;
    goto bb_004db64f;
}
bb_004db65a: {
    // 0x004db65a: xor esi, esi
    uint32_t t5 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    ctx.esi = static_cast<uint32_t>(t5);
    goto bb_004db65c;
}
bb_004db64f: {
    // 0x004db64f: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004db651: call 0x413c60
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x004db656u);
    sub_00413c60(ctx, mem);
    // 0x004db656: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004db658: jmp 0x4db65c
}
bb_004db65c: {
    // 0x004db65c: mov eax, dword ptr [esp + 8]
    uint32_t t7 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t8 = mem.r32(t7);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x004db660: push 0
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x00000000u);
    // 0x004db662: push eax
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.eax);
    // 0x004db663: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004db665: call 0x413ce0
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0x004db66au);
    sub_00413ce0(ctx, mem);
    // 0x004db66a: test eax, eax
    uint32_t t12 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t12);
    // 0x004db66c: jne 0x4db686
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004db686;
    goto bb_004db66e;
}
bb_004db686: {
    // 0x004db686: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004db688: pop esi
    uint32_t t13 = ctx.esp;
    uint32_t t14 = mem.r32(t13);
    uint32_t t15 = static_cast<uint32_t>(t13 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    ctx.esi = static_cast<uint32_t>(t14);
    // 0x004db689: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004db66e: {
    // 0x004db66e: test esi, esi
    uint32_t t16 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    // 0x004db670: je 0x4db686
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004db686;
}
{
    // 0x004db672: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004db674: call 0x414000
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x004db679u);
    sub_00414000(ctx, mem);
    // 0x004db679: push esi
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, ctx.esi);
    // 0x004db67a: call 0x4e02f3
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x004db67fu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004db67f: add esp, 4
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t20);
    ctx.esp = static_cast<uint32_t>(t20);
    // 0x004db682: xor eax, eax
    uint32_t t21 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t21);
    ctx.eax = static_cast<uint32_t>(t21);
    // 0x004db684: pop esi
    uint32_t t22 = ctx.esp;
    uint32_t t23 = mem.r32(t22);
    uint32_t t24 = static_cast<uint32_t>(t22 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    ctx.esi = static_cast<uint32_t>(t23);
    // 0x004db685: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004db690 | subsystem=FilePacFunc | canonical | 4 blocks | 28 insns
void sub_004db690(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004db690: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x004db691: push 0x5c
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0000005cu);
    // 0x004db693: call 0x4e0177
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x004db698u);
    hle_crt_004e0177(ctx, mem);
    // 0x004db698: add esp, 4
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t3);
    ctx.esp = static_cast<uint32_t>(t3);
    // 0x004db69b: test eax, eax
    uint32_t t4 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    // 0x004db69d: je 0x4db6aa
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004db6aa;
    goto bb_004db69f;
}
bb_004db6aa: {
    // 0x004db6aa: xor esi, esi
    uint32_t t5 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    ctx.esi = static_cast<uint32_t>(t5);
    goto bb_004db6ac;
}
bb_004db69f: {
    // 0x004db69f: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004db6a1: call 0x413c60
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x004db6a6u);
    sub_00413c60(ctx, mem);
    // 0x004db6a6: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004db6a8: jmp 0x4db6ac
}
bb_004db6ac: {
    // 0x004db6ac: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004db6ae: call 0x414000
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x004db6b3u);
    sub_00414000(ctx, mem);
    // 0x004db6b3: mov eax, dword ptr [esp + 8]
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t9 = mem.r32(t8);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x004db6b7: mov ecx, dword ptr [esp + 0xc]
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t11 = mem.r32(t10);
    ctx.ecx = static_cast<uint32_t>(t11);
    // 0x004db6bb: mov dword ptr [esi + 4], eax
    uint32_t t12 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t12, ctx.eax);
    // 0x004db6be: xor eax, eax
    uint32_t t13 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t13);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x004db6c0: mov dword ptr [esi], 0
    mem.w32(ctx.esi, 0x00000000u);
    // 0x004db6c6: mov dword ptr [esi + 0x1c], 2
    uint32_t t14 = static_cast<uint32_t>(ctx.esi + 0x0000001cu);
    mem.w32(t14, 0x00000002u);
    // 0x004db6cd: mov dword ptr [esi + 0x28], ecx
    uint32_t t15 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    mem.w32(t15, ctx.ecx);
    // 0x004db6d0: mov dword ptr [esi + 8], eax
    uint32_t t16 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t16, ctx.eax);
    // 0x004db6d3: mov dword ptr [esi + 0xc], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t17, ctx.eax);
    // 0x004db6d6: mov dword ptr [esi + 0x10], eax
    uint32_t t18 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    mem.w32(t18, ctx.eax);
    // 0x004db6d9: mov dword ptr [esi + 0x14], eax
    uint32_t t19 = static_cast<uint32_t>(ctx.esi + 0x00000014u);
    mem.w32(t19, ctx.eax);
    // 0x004db6dc: mov dword ptr [esi + 0x18], eax
    uint32_t t20 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    mem.w32(t20, ctx.eax);
    // 0x004db6df: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004db6e1: pop esi
    uint32_t t21 = ctx.esp;
    uint32_t t22 = mem.r32(t21);
    uint32_t t23 = static_cast<uint32_t>(t21 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    ctx.esi = static_cast<uint32_t>(t22);
    // 0x004db6e2: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004db7f0 | subsystem=FilePacFunc | canonical | 13 blocks | 82 insns
void sub_004db7f0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004db7f0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x004db7f2: push 0x5135bb
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005135bbu);
    // 0x004db7f7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004db7fd: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x004db7fe: push ecx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ecx);
    // 0x004db7ff: push ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebx);
    // 0x004db800: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x004db801: mov eax, dword ptr [0x54b458]
    uint32_t t8 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x004db806: xor eax, esp
    uint32_t t9 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x004db808: push eax
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.eax);
    // 0x004db809: lea eax, [esp + 0x10]
    uint32_t t11 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x004db80d: mov dword ptr fs:[0], eax
    uint32_t t12 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t12, ctx.eax);
    // 0x004db813: push 0x8c
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x0000008cu);
    // 0x004db818: call 0x4e0177
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x004db81du);
    hle_crt_004e0177(ctx, mem);
    // 0x004db81d: add esp, 4
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t15);
    ctx.esp = static_cast<uint32_t>(t15);
    // 0x004db820: mov dword ptr [esp + 0xc], eax
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t16, ctx.eax);
    // 0x004db824: xor ebx, ebx
    uint32_t t17 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t17);
    ctx.ebx = static_cast<uint32_t>(t17);
    // 0x004db826: cmp eax, ebx
    uint32_t t18 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t18);
    // 0x004db828: mov dword ptr [esp + 0x18], ebx
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t19, ctx.ebx);
    // 0x004db82c: je 0x4db838
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004db838;
    goto bb_004db82e;
}
bb_004db838: {
    // 0x004db838: xor esi, esi
    uint32_t t20 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t20);
    ctx.esi = static_cast<uint32_t>(t20);
    goto bb_004db83a;
}
bb_004db82e: {
    // 0x004db82e: push eax
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, ctx.eax);
    // 0x004db82f: call 0x4dba20
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x004db834u);
    sub_004dba20(ctx, mem);
    // 0x004db834: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004db836: jmp 0x4db83a
}
bb_004db83a: {
    // 0x004db83a: mov dword ptr [esp + 0x18], 0xffffffff
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t23, 0xffffffffu);
    // 0x004db842: mov edx, dword ptr [esp + 0x24]
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t25 = mem.r32(t24);
    ctx.edx = static_cast<uint32_t>(t25);
    // 0x004db846: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004db848: call 0x4dc050
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x004db84du);
    sub_004dc050(ctx, mem);
    // 0x004db84d: test eax, eax
    uint32_t t27 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t27);
    // 0x004db84f: jne 0x4db875
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004db875;
    goto bb_004db851;
}
bb_004db875: {
    // 0x004db875: push 0x20
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x00000020u);
    // 0x004db877: call 0x4e0177
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x004db87cu);
    hle_crt_004e0177(ctx, mem);
    // 0x004db87c: add esp, 4
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t30);
    ctx.esp = static_cast<uint32_t>(t30);
    // 0x004db87f: cmp eax, ebx
    uint32_t t31 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t31);
    // 0x004db881: je 0x4db896
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004db896;
    goto bb_004db883;
}
bb_004db851: {
    // 0x004db851: cmp esi, ebx
    uint32_t t32 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t32);
    // 0x004db853: je 0x4db85f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004db85f;
    goto bb_004db855;
}
bb_004db896: {
    // 0x004db896: xor ecx, ecx
    uint32_t t33 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t33);
    ctx.ecx = static_cast<uint32_t>(t33);
    goto bb_004db898;
}
bb_004db883: {
    // 0x004db883: mov dword ptr [eax + 0x1c], 0xf
    uint32_t t34 = static_cast<uint32_t>(ctx.eax + 0x0000001cu);
    mem.w32(t34, 0x0000000fu);
    // 0x004db88a: mov dword ptr [eax + 0x18], ebx
    uint32_t t35 = static_cast<uint32_t>(ctx.eax + 0x00000018u);
    mem.w32(t35, ctx.ebx);
    // 0x004db88d: mov byte ptr [eax + 8], bl
    uint32_t t36 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    mem.w8(t36, recomp_detail::r8l(ctx.ebx));
    // 0x004db890: mov dword ptr [eax], ebx
    mem.w32(ctx.eax, ctx.ebx);
    // 0x004db892: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x004db894: jmp 0x4db898
    goto bb_004db898;
}
bb_004db85f: {
    // 0x004db85f: xor eax, eax
    uint32_t t37 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t37);
    ctx.eax = static_cast<uint32_t>(t37);
    // 0x004db861: mov ecx, dword ptr [esp + 0x10]
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t39 = mem.r32(t38);
    ctx.ecx = static_cast<uint32_t>(t39);
    // 0x004db865: mov dword ptr fs:[0], ecx
    uint32_t t40 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t40, ctx.ecx);
    // 0x004db86c: pop ecx
    uint32_t t41 = ctx.esp;
    uint32_t t42 = mem.r32(t41);
    uint32_t t43 = static_cast<uint32_t>(t41 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    ctx.ecx = static_cast<uint32_t>(t42);
    // 0x004db86d: pop esi
    uint32_t t44 = ctx.esp;
    uint32_t t45 = mem.r32(t44);
    uint32_t t46 = static_cast<uint32_t>(t44 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    ctx.esi = static_cast<uint32_t>(t45);
    // 0x004db86e: pop ebx
    uint32_t t47 = ctx.esp;
    uint32_t t48 = mem.r32(t47);
    uint32_t t49 = static_cast<uint32_t>(t47 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    ctx.ebx = static_cast<uint32_t>(t48);
    // 0x004db86f: add esp, 0x10
    uint32_t t50 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t50);
    ctx.esp = static_cast<uint32_t>(t50);
    // 0x004db872: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
bb_004db855: {
    // 0x004db855: mov eax, dword ptr [esi]
    uint32_t t51 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t51);
    // 0x004db857: mov edx, dword ptr [eax]
    uint32_t t52 = mem.r32(ctx.eax);
    ctx.edx = static_cast<uint32_t>(t52);
    // 0x004db859: push 1
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, 0x00000001u);
    // 0x004db85b: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004db85d: call edx
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, 0x004db85fu);
    call_indirect(ctx, mem, ctx.edx);
    goto bb_004db85f;
}
bb_004db898: {
    // 0x004db898: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x004db89a: mov dword ptr [ecx], esi
    mem.w32(ctx.ecx, ctx.esi);
    // 0x004db89c: mov dword ptr [esp + 0x24], ecx
    uint32_t t55 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t55, ctx.ecx);
    // 0x004db8a0: lea esi, [eax + 1]
    uint32_t t56 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.esi = static_cast<uint32_t>(t56);
}
bb_004db8a3: {
    // 0x004db8a3: mov dl, byte ptr [eax]
    uint8_t t57 = mem.r8(ctx.eax);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t57));
    // 0x004db8a5: add eax, 1
    uint32_t t58 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t58);
    ctx.eax = static_cast<uint32_t>(t58);
    // 0x004db8a8: cmp dl, bl
    uint8_t t59 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)) - static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.edx), recomp_detail::r8l(ctx.ebx), t59);
    // 0x004db8aa: jne 0x4db8a3
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004db8a3;
}
{
    // 0x004db8ac: sub eax, esi
    uint32_t t60 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t60);
    ctx.eax = static_cast<uint32_t>(t60);
    // 0x004db8ae: push eax
    uint32_t t61 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    mem.w32(t61, ctx.eax);
    // 0x004db8af: push edi
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, ctx.edi);
    // 0x004db8b0: add ecx, 4
    uint32_t t63 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000004u, t63);
    ctx.ecx = static_cast<uint32_t>(t63);
    // 0x004db8b3: call 0x407c10
    uint32_t t64 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    mem.w32(t64, 0x004db8b8u);
    sub_00407c10(ctx, mem);
    // 0x004db8b8: mov esi, dword ptr [esp + 0x20]
    uint32_t t65 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t66 = mem.r32(t65);
    ctx.esi = static_cast<uint32_t>(t66);
    // 0x004db8bc: lea ebx, [esp + 0x24]
    uint32_t t67 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    ctx.ebx = static_cast<uint32_t>(t67);
    // 0x004db8c0: call 0x4dcaf0
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, 0x004db8c5u);
    sub_004dcaf0(ctx, mem);
    // 0x004db8c5: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x004db8ca: mov ecx, dword ptr [esp + 0x10]
    uint32_t t69 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t70 = mem.r32(t69);
    ctx.ecx = static_cast<uint32_t>(t70);
    // 0x004db8ce: mov dword ptr fs:[0], ecx
    uint32_t t71 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t71, ctx.ecx);
    // 0x004db8d5: pop ecx
    uint32_t t72 = ctx.esp;
    uint32_t t73 = mem.r32(t72);
    uint32_t t74 = static_cast<uint32_t>(t72 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    ctx.ecx = static_cast<uint32_t>(t73);
    // 0x004db8d6: pop esi
    uint32_t t75 = ctx.esp;
    uint32_t t76 = mem.r32(t75);
    uint32_t t77 = static_cast<uint32_t>(t75 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    ctx.esi = static_cast<uint32_t>(t76);
    // 0x004db8d7: pop ebx
    uint32_t t78 = ctx.esp;
    uint32_t t79 = mem.r32(t78);
    uint32_t t80 = static_cast<uint32_t>(t78 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    ctx.ebx = static_cast<uint32_t>(t79);
    // 0x004db8d8: add esp, 0x10
    uint32_t t81 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t81);
    ctx.esp = static_cast<uint32_t>(t81);
    // 0x004db8db: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
}

// sub_004dba20 | subsystem=FilePacFunc | canonical | 9 blocks | 63 insns
void sub_004dba20(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dba20: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x004dba22: push 0x513c71
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00513c71u);
    // 0x004dba27: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004dba2d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x004dba2e: push ebx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ebx);
    // 0x004dba2f: push ebp
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebp);
    // 0x004dba30: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x004dba31: push edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edi);
    // 0x004dba32: mov eax, dword ptr [0x54b458]
    uint32_t t9 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x004dba37: xor eax, esp
    uint32_t t10 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x004dba39: push eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.eax);
    // 0x004dba3a: lea eax, [esp + 0x14]
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x004dba3e: mov dword ptr fs:[0], eax
    uint32_t t13 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t13, ctx.eax);
    // 0x004dba44: mov edi, dword ptr [esp + 0x24]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t15 = mem.r32(t14);
    ctx.edi = static_cast<uint32_t>(t15);
    // 0x004dba48: lea ebp, [edi + 8]
    uint32_t t16 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    ctx.ebp = static_cast<uint32_t>(t16);
    // 0x004dba4b: mov dword ptr [edi], 0x53d538
    mem.w32(ctx.edi, 0x0053d538u);
    // 0x004dba51: xor ebx, ebx
    uint32_t t17 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t17);
    ctx.ebx = static_cast<uint32_t>(t17);
    // 0x004dba53: mov dword ptr [ebp + 0x18], 0xf
    uint32_t t18 = static_cast<uint32_t>(ctx.ebp + 0x00000018u);
    mem.w32(t18, 0x0000000fu);
    // 0x004dba5a: mov dword ptr [ebp + 0x14], ebx
    uint32_t t19 = static_cast<uint32_t>(ctx.ebp + 0x00000014u);
    mem.w32(t19, ctx.ebx);
    // 0x004dba5d: mov byte ptr [ebp + 4], bl
    uint32_t t20 = static_cast<uint32_t>(ctx.ebp + 0x00000004u);
    mem.w8(t20, recomp_detail::r8l(ctx.ebx));
    // 0x004dba60: lea esi, [edi + 0x24]
    uint32_t t21 = static_cast<uint32_t>(ctx.edi + 0x00000024u);
    ctx.esi = static_cast<uint32_t>(t21);
    // 0x004dba63: mov dword ptr [esp + 0x1c], ebx
    uint32_t t22 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t22, ctx.ebx);
    // 0x004dba67: call 0x4db4b0
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x004dba6cu);
    sub_004db4b0(ctx, mem);
    // 0x004dba6c: mov dword ptr [edi + 0x5c], ebx
    uint32_t t24 = static_cast<uint32_t>(ctx.edi + 0x0000005cu);
    mem.w32(t24, ctx.ebx);
    // 0x004dba6f: mov dword ptr [edi + 0x60], ebx
    uint32_t t25 = static_cast<uint32_t>(ctx.edi + 0x00000060u);
    mem.w32(t25, ctx.ebx);
    // 0x004dba72: mov dword ptr [edi + 0x64], ebx
    uint32_t t26 = static_cast<uint32_t>(ctx.edi + 0x00000064u);
    mem.w32(t26, ctx.ebx);
    // 0x004dba75: mov dword ptr [edi + 0x6c], ebx
    uint32_t t27 = static_cast<uint32_t>(ctx.edi + 0x0000006cu);
    mem.w32(t27, ctx.ebx);
    // 0x004dba78: mov dword ptr [edi + 0x70], ebx
    uint32_t t28 = static_cast<uint32_t>(ctx.edi + 0x00000070u);
    mem.w32(t28, ctx.ebx);
    // 0x004dba7b: mov dword ptr [edi + 0x74], ebx
    uint32_t t29 = static_cast<uint32_t>(ctx.edi + 0x00000074u);
    mem.w32(t29, ctx.ebx);
    // 0x004dba7e: mov byte ptr [esp + 0x1c], 2
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w8(t30, uint8_t{0x02u});
    // 0x004dba83: mov dword ptr [edi + 4], ebx
    uint32_t t31 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    mem.w32(t31, ctx.ebx);
    // 0x004dba86: mov esi, dword ptr [ebp + 0x14]
    uint32_t t32 = static_cast<uint32_t>(ctx.ebp + 0x00000014u);
    uint32_t t33 = mem.r32(t32);
    ctx.esi = static_cast<uint32_t>(t33);
    // 0x004dba89: cmp esi, 0x100
    uint32_t t34 = static_cast<uint32_t>(ctx.esi - 0x00000100u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00000100u, t34);
    // 0x004dba8f: ja 0x4dbabe
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_004dbabe;
    goto bb_004dba91;
}
bb_004dbabe: {
    // 0x004dbabe: mov dword ptr [edi + 0x78], ebx
    uint32_t t35 = static_cast<uint32_t>(ctx.edi + 0x00000078u);
    mem.w32(t35, ctx.ebx);
    // 0x004dbac1: mov dword ptr [edi + 0x80], ebx
    uint32_t t36 = static_cast<uint32_t>(ctx.edi + 0x00000080u);
    mem.w32(t36, ctx.ebx);
    // 0x004dbac7: mov dword ptr [edi + 0x84], ebx
    uint32_t t37 = static_cast<uint32_t>(ctx.edi + 0x00000084u);
    mem.w32(t37, ctx.ebx);
    // 0x004dbacd: mov dword ptr [edi + 0x88], ebx
    uint32_t t38 = static_cast<uint32_t>(ctx.edi + 0x00000088u);
    mem.w32(t38, ctx.ebx);
    // 0x004dbad3: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x004dbad5: mov ecx, dword ptr [esp + 0x14]
    uint32_t t39 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t40 = mem.r32(t39);
    ctx.ecx = static_cast<uint32_t>(t40);
    // 0x004dbad9: mov dword ptr fs:[0], ecx
    uint32_t t41 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t41, ctx.ecx);
    // 0x004dbae0: pop ecx
    uint32_t t42 = ctx.esp;
    uint32_t t43 = mem.r32(t42);
    uint32_t t44 = static_cast<uint32_t>(t42 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    ctx.ecx = static_cast<uint32_t>(t43);
    // 0x004dbae1: pop edi
    uint32_t t45 = ctx.esp;
    uint32_t t46 = mem.r32(t45);
    uint32_t t47 = static_cast<uint32_t>(t45 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    ctx.edi = static_cast<uint32_t>(t46);
    // 0x004dbae2: pop esi
    uint32_t t48 = ctx.esp;
    uint32_t t49 = mem.r32(t48);
    uint32_t t50 = static_cast<uint32_t>(t48 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    ctx.esi = static_cast<uint32_t>(t49);
    // 0x004dbae3: pop ebp
    uint32_t t51 = ctx.esp;
    uint32_t t52 = mem.r32(t51);
    uint32_t t53 = static_cast<uint32_t>(t51 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    ctx.ebp = static_cast<uint32_t>(t52);
    // 0x004dbae4: pop ebx
    uint32_t t54 = ctx.esp;
    uint32_t t55 = mem.r32(t54);
    uint32_t t56 = static_cast<uint32_t>(t54 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    ctx.ebx = static_cast<uint32_t>(t55);
    // 0x004dbae5: add esp, 0xc
    uint32_t t57 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t57);
    ctx.esp = static_cast<uint32_t>(t57);
    // 0x004dbae8: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_004dba91: {
    // 0x004dba91: mov eax, dword ptr [ebp + 0x18]
    uint32_t t58 = static_cast<uint32_t>(ctx.ebp + 0x00000018u);
    uint32_t t59 = mem.r32(t58);
    ctx.eax = static_cast<uint32_t>(t59);
    // 0x004dba94: cmp eax, 0x100
    uint32_t t60 = static_cast<uint32_t>(ctx.eax - 0x00000100u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000100u, t60);
    // 0x004dba99: je 0x4dbabe
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dbabe;
}
{
    // 0x004dba9b: jae 0x4dbaaa
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004dbaaa;
    goto bb_004dba9d;
}
bb_004dbaaa: {
    // 0x004dbaaa: cmp dword ptr [ebp + 0x18], 0x10
    uint32_t t61 = static_cast<uint32_t>(ctx.ebp + 0x00000018u);
    uint32_t t62 = mem.r32(t61);
    uint32_t t63 = static_cast<uint32_t>(t62 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t62, 0x00000010u, t63);
    // 0x004dbaae: mov dword ptr [ebp + 0x14], esi
    uint32_t t64 = static_cast<uint32_t>(ctx.ebp + 0x00000014u);
    mem.w32(t64, ctx.esi);
    // 0x004dbab1: jb 0x4dbab8
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004dbab8;
    goto bb_004dbab3;
}
bb_004dba9d: {
    // 0x004dba9d: push esi
    uint32_t t65 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t65);
    mem.w32(t65, ctx.esi);
    // 0x004dba9e: push 0x100
    uint32_t t66 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    mem.w32(t66, 0x00000100u);
    // 0x004dbaa3: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x004dbaa5: call 0x408030
    uint32_t t67 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t67);
    mem.w32(t67, 0x004dbaaau);
    sub_00408030(ctx, mem);
    goto bb_004dbaaa;
}
bb_004dbab8: {
    // 0x004dbab8: add ebp, 4
    uint32_t t68 = static_cast<uint32_t>(ctx.ebp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebp, 0x00000004u, t68);
    ctx.ebp = static_cast<uint32_t>(t68);
    goto bb_004dbabb;
}
bb_004dbab3: {
    // 0x004dbab3: mov ebp, dword ptr [ebp + 4]
    uint32_t t69 = static_cast<uint32_t>(ctx.ebp + 0x00000004u);
    uint32_t t70 = mem.r32(t69);
    ctx.ebp = static_cast<uint32_t>(t70);
    // 0x004dbab6: jmp 0x4dbabb
}
bb_004dbabb: {
    // 0x004dbabb: mov byte ptr [esi + ebp], bl
    uint32_t t71 = static_cast<uint32_t>(ctx.esi + ctx.ebp);
    mem.w8(t71, recomp_detail::r8l(ctx.ebx));
    goto bb_004dbabe;
}
}

// sub_004dbaf0 | subsystem=FilePacFunc | canonical | 3 blocks | 11 insns
void sub_004dbaf0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dbaf0: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x004dbaf1: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004dbaf3: call 0x4dbb10
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x004dbaf8u);
    sub_004dbb10(ctx, mem);
    // 0x004dbaf8: test byte ptr [esp + 8], 1
    uint32_t t2 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint8_t t3 = mem.r8(t2);
    uint8_t t4 = static_cast<uint8_t>(static_cast<uint32_t>(t3) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t4);
    // 0x004dbafd: je 0x4dbb08
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dbb08;
    goto bb_004dbaff;
}
bb_004dbb08: {
    // 0x004dbb08: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004dbb0a: pop esi
    uint32_t t5 = ctx.esp;
    uint32_t t6 = mem.r32(t5);
    uint32_t t7 = static_cast<uint32_t>(t5 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x004dbb0b: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_004dbaff: {
    // 0x004dbaff: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x004dbb00: call 0x4e02f3
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x004dbb05u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dbb05: add esp, 4
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t10);
    ctx.esp = static_cast<uint32_t>(t10);
    goto bb_004dbb08;
}
}

// sub_004dbb10 | subsystem=FilePacFunc | canonical | 7 blocks | 65 insns
void sub_004dbb10(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dbb10: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x004dbb12: push 0x515781
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00515781u);
    // 0x004dbb17: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004dbb1d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x004dbb1e: push ecx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ecx);
    // 0x004dbb1f: push ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebx);
    // 0x004dbb20: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x004dbb21: push edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edi);
    // 0x004dbb22: mov eax, dword ptr [0x54b458]
    uint32_t t9 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x004dbb27: xor eax, esp
    uint32_t t10 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x004dbb29: push eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.eax);
    // 0x004dbb2a: lea eax, [esp + 0x14]
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x004dbb2e: mov dword ptr fs:[0], eax
    uint32_t t13 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t13, ctx.eax);
    // 0x004dbb34: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004dbb36: mov dword ptr [esp + 0x10], esi
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t14, ctx.esi);
    // 0x004dbb3a: mov dword ptr [esi], 0x53d538
    mem.w32(ctx.esi, 0x0053d538u);
    // 0x004dbb40: push esi
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.esi);
    // 0x004dbb41: mov dword ptr [esp + 0x20], 2
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t16, 0x00000002u);
    // 0x004dbb49: call 0x4dbbe0
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x004dbb4eu);
    sub_004dbbe0(ctx, mem);
    // 0x004dbb4e: mov eax, dword ptr [esi + 0x6c]
    uint32_t t18 = static_cast<uint32_t>(ctx.esi + 0x0000006cu);
    uint32_t t19 = mem.r32(t18);
    ctx.eax = static_cast<uint32_t>(t19);
    // 0x004dbb51: xor ebx, ebx
    uint32_t t20 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t20);
    ctx.ebx = static_cast<uint32_t>(t20);
    // 0x004dbb53: cmp eax, ebx
    uint32_t t21 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t21);
    // 0x004dbb55: je 0x4dbb70
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dbb70;
    goto bb_004dbb57;
}
bb_004dbb70: {
    // 0x004dbb70: mov dword ptr [esi + 0x6c], ebx
    uint32_t t22 = static_cast<uint32_t>(ctx.esi + 0x0000006cu);
    mem.w32(t22, ctx.ebx);
    // 0x004dbb73: mov dword ptr [esi + 0x70], ebx
    uint32_t t23 = static_cast<uint32_t>(ctx.esi + 0x00000070u);
    mem.w32(t23, ctx.ebx);
    // 0x004dbb76: mov dword ptr [esi + 0x74], ebx
    uint32_t t24 = static_cast<uint32_t>(ctx.esi + 0x00000074u);
    mem.w32(t24, ctx.ebx);
    // 0x004dbb79: mov eax, dword ptr [esi + 0x5c]
    uint32_t t25 = static_cast<uint32_t>(ctx.esi + 0x0000005cu);
    uint32_t t26 = mem.r32(t25);
    ctx.eax = static_cast<uint32_t>(t26);
    // 0x004dbb7c: cmp eax, ebx
    uint32_t t27 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t27);
    // 0x004dbb7e: je 0x4dbb99
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dbb99;
    goto bb_004dbb80;
}
bb_004dbb57: {
    // 0x004dbb57: mov ecx, dword ptr [esp + 0x10]
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t29 = mem.r32(t28);
    ctx.ecx = static_cast<uint32_t>(t29);
    // 0x004dbb5b: mov edi, dword ptr [esi + 0x70]
    uint32_t t30 = static_cast<uint32_t>(ctx.esi + 0x00000070u);
    uint32_t t31 = mem.r32(t30);
    ctx.edi = static_cast<uint32_t>(t31);
    // 0x004dbb5e: push ecx
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, ctx.ecx);
    // 0x004dbb5f: call 0x4dd220
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x004dbb64u);
    sub_004dd220(ctx, mem);
    // 0x004dbb64: mov edx, dword ptr [esi + 0x6c]
    uint32_t t34 = static_cast<uint32_t>(ctx.esi + 0x0000006cu);
    uint32_t t35 = mem.r32(t34);
    ctx.edx = static_cast<uint32_t>(t35);
    // 0x004dbb67: push edx
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, ctx.edx);
    // 0x004dbb68: call 0x4e02f3
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, 0x004dbb6du);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dbb6d: add esp, 8
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t38);
    ctx.esp = static_cast<uint32_t>(t38);
    goto bb_004dbb70;
}
bb_004dbb99: {
    // 0x004dbb99: mov dword ptr [esi + 0x5c], ebx
    uint32_t t39 = static_cast<uint32_t>(ctx.esi + 0x0000005cu);
    mem.w32(t39, ctx.ebx);
    // 0x004dbb9c: mov dword ptr [esi + 0x60], ebx
    uint32_t t40 = static_cast<uint32_t>(ctx.esi + 0x00000060u);
    mem.w32(t40, ctx.ebx);
    // 0x004dbb9f: mov dword ptr [esi + 0x64], ebx
    uint32_t t41 = static_cast<uint32_t>(ctx.esi + 0x00000064u);
    mem.w32(t41, ctx.ebx);
    // 0x004dbba2: cmp dword ptr [esi + 0x20], 0x10
    uint32_t t42 = static_cast<uint32_t>(ctx.esi + 0x00000020u);
    uint32_t t43 = mem.r32(t42);
    uint32_t t44 = static_cast<uint32_t>(t43 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t43, 0x00000010u, t44);
    // 0x004dbba6: jb 0x4dbbb4
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004dbbb4;
    goto bb_004dbba8;
}
bb_004dbb80: {
    // 0x004dbb80: mov ecx, dword ptr [esp + 0x10]
    uint32_t t45 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t46 = mem.r32(t45);
    ctx.ecx = static_cast<uint32_t>(t46);
    // 0x004dbb84: mov edi, dword ptr [esi + 0x60]
    uint32_t t47 = static_cast<uint32_t>(ctx.esi + 0x00000060u);
    uint32_t t48 = mem.r32(t47);
    ctx.edi = static_cast<uint32_t>(t48);
    // 0x004dbb87: push ecx
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, ctx.ecx);
    // 0x004dbb88: call 0x4dd220
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, 0x004dbb8du);
    sub_004dd220(ctx, mem);
    // 0x004dbb8d: mov edx, dword ptr [esi + 0x5c]
    uint32_t t51 = static_cast<uint32_t>(ctx.esi + 0x0000005cu);
    uint32_t t52 = mem.r32(t51);
    ctx.edx = static_cast<uint32_t>(t52);
    // 0x004dbb90: push edx
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, ctx.edx);
    // 0x004dbb91: call 0x4e02f3
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, 0x004dbb96u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dbb96: add esp, 8
    uint32_t t55 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t55);
    ctx.esp = static_cast<uint32_t>(t55);
    goto bb_004dbb99;
}
bb_004dbbb4: {
    // 0x004dbbb4: mov dword ptr [esi + 0x20], 0xf
    uint32_t t56 = static_cast<uint32_t>(ctx.esi + 0x00000020u);
    mem.w32(t56, 0x0000000fu);
    // 0x004dbbbb: mov dword ptr [esi + 0x1c], ebx
    uint32_t t57 = static_cast<uint32_t>(ctx.esi + 0x0000001cu);
    mem.w32(t57, ctx.ebx);
    // 0x004dbbbe: mov byte ptr [esi + 0xc], bl
    uint32_t t58 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w8(t58, recomp_detail::r8l(ctx.ebx));
    // 0x004dbbc1: mov ecx, dword ptr [esp + 0x14]
    uint32_t t59 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t60 = mem.r32(t59);
    ctx.ecx = static_cast<uint32_t>(t60);
    // 0x004dbbc5: mov dword ptr fs:[0], ecx
    uint32_t t61 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t61, ctx.ecx);
    // 0x004dbbcc: pop ecx
    uint32_t t62 = ctx.esp;
    uint32_t t63 = mem.r32(t62);
    uint32_t t64 = static_cast<uint32_t>(t62 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    ctx.ecx = static_cast<uint32_t>(t63);
    // 0x004dbbcd: pop edi
    uint32_t t65 = ctx.esp;
    uint32_t t66 = mem.r32(t65);
    uint32_t t67 = static_cast<uint32_t>(t65 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t67);
    ctx.edi = static_cast<uint32_t>(t66);
    // 0x004dbbce: pop esi
    uint32_t t68 = ctx.esp;
    uint32_t t69 = mem.r32(t68);
    uint32_t t70 = static_cast<uint32_t>(t68 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    ctx.esi = static_cast<uint32_t>(t69);
    // 0x004dbbcf: pop ebx
    uint32_t t71 = ctx.esp;
    uint32_t t72 = mem.r32(t71);
    uint32_t t73 = static_cast<uint32_t>(t71 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    ctx.ebx = static_cast<uint32_t>(t72);
    // 0x004dbbd0: add esp, 0x10
    uint32_t t74 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t74);
    ctx.esp = static_cast<uint32_t>(t74);
    // 0x004dbbd3: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004dbba8: {
    // 0x004dbba8: mov eax, dword ptr [esi + 0xc]
    uint32_t t75 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    uint32_t t76 = mem.r32(t75);
    ctx.eax = static_cast<uint32_t>(t76);
    // 0x004dbbab: push eax
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, ctx.eax);
    // 0x004dbbac: call 0x4e02f3
    uint32_t t78 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    mem.w32(t78, 0x004dbbb1u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dbbb1: add esp, 4
    uint32_t t79 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t79);
    ctx.esp = static_cast<uint32_t>(t79);
    goto bb_004dbbb4;
}
}

// sub_004dbbe0 | subsystem=FilePacFunc | canonical | 17 blocks | 137 insns
void sub_004dbbe0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dbbe0: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x004dbbe1: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x004dbbe3: and esp, 0xfffffff8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xfffffff8u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x004dbbe6: push -1
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0xffffffffu);
    // 0x004dbbe8: push 0x515740
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x00515740u);
    // 0x004dbbed: mov eax, dword ptr fs:[0]
    uint32_t t4 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t5 = mem.r32(t4);
    ctx.eax = static_cast<uint32_t>(t5);
    // 0x004dbbf3: push eax
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.eax);
    // 0x004dbbf4: sub esp, 0x20
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000020u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000020u, t7);
    ctx.esp = static_cast<uint32_t>(t7);
    // 0x004dbbf7: push ebx
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.ebx);
    // 0x004dbbf8: push esi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.esi);
    // 0x004dbbf9: push edi
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.edi);
    // 0x004dbbfa: mov eax, dword ptr [0x54b458]
    uint32_t t11 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x004dbbff: xor eax, esp
    uint32_t t12 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t12);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x004dbc01: push eax
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, ctx.eax);
    // 0x004dbc02: lea eax, [esp + 0x30]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x004dbc06: mov dword ptr fs:[0], eax
    uint32_t t15 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t15, ctx.eax);
    // 0x004dbc0c: mov edi, dword ptr [ebp + 8]
    uint32_t t16 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t17 = mem.r32(t16);
    ctx.edi = static_cast<uint32_t>(t17);
    // 0x004dbc0f: xor ebx, ebx
    uint32_t t18 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    ctx.ebx = static_cast<uint32_t>(t18);
    // 0x004dbc11: cmp dword ptr [edi + 0x78], ebx
    uint32_t t19 = static_cast<uint32_t>(ctx.edi + 0x00000078u);
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t20 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t20, ctx.ebx, t21);
    // 0x004dbc14: je 0x4dbc3c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dbc3c;
    goto bb_004dbc16;
}
bb_004dbc3c: {
    // 0x004dbc3c: lea esi, [edi + 0x24]
    uint32_t t22 = static_cast<uint32_t>(ctx.edi + 0x00000024u);
    ctx.esi = static_cast<uint32_t>(t22);
    // 0x004dbc3f: call 0x4db4b0
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x004dbc44u);
    sub_004db4b0(ctx, mem);
    // 0x004dbc44: mov eax, dword ptr [edi + 0x60]
    uint32_t t24 = static_cast<uint32_t>(ctx.edi + 0x00000060u);
    uint32_t t25 = mem.r32(t24);
    ctx.eax = static_cast<uint32_t>(t25);
    // 0x004dbc47: cmp dword ptr [edi + 0x5c], eax
    uint32_t t26 = static_cast<uint32_t>(ctx.edi + 0x0000005cu);
    uint32_t t27 = mem.r32(t26);
    uint32_t t28 = static_cast<uint32_t>(t27 - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t27, ctx.eax, t28);
    // 0x004dbc4a: lea esi, [edi + 0x58]
    uint32_t t29 = static_cast<uint32_t>(ctx.edi + 0x00000058u);
    ctx.esi = static_cast<uint32_t>(t29);
    // 0x004dbc4d: mov dword ptr [esp + 0x14], eax
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t30, ctx.eax);
    // 0x004dbc51: jbe 0x4dbc58
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_004dbc58;
    goto bb_004dbc53;
}
bb_004dbc16: {
    // 0x004dbc16: mov esi, dword ptr [edi + 0x88]
    uint32_t t31 = static_cast<uint32_t>(ctx.edi + 0x00000088u);
    uint32_t t32 = mem.r32(t31);
    ctx.esi = static_cast<uint32_t>(t32);
    // 0x004dbc1c: cmp esi, ebx
    uint32_t t33 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t33);
    // 0x004dbc1e: je 0x4dbc30
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dbc30;
    goto bb_004dbc20;
}
bb_004dbc58: {
    // 0x004dbc58: mov eax, dword ptr [esi + 4]
    uint32_t t34 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t35 = mem.r32(t34);
    ctx.eax = static_cast<uint32_t>(t35);
    // 0x004dbc5b: cmp eax, dword ptr [esi + 8]
    uint32_t t36 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t37 = mem.r32(t36);
    uint32_t t38 = static_cast<uint32_t>(ctx.eax - t37);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, t37, t38);
    // 0x004dbc5e: mov dword ptr [esp + 0x10], eax
    uint32_t t39 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t39, ctx.eax);
    // 0x004dbc62: jbe 0x4dbc6d
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_004dbc6d;
    goto bb_004dbc64;
}
bb_004dbc53: {
    // 0x004dbc53: call 0x4e0bf2
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, 0x004dbc58u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004dbc58;
}
bb_004dbc30: {
    // 0x004dbc30: mov dword ptr [edi + 0x88], ebx
    uint32_t t41 = static_cast<uint32_t>(ctx.edi + 0x00000088u);
    mem.w32(t41, ctx.ebx);
    // 0x004dbc36: mov dword ptr [edi + 0x78], ebx
    uint32_t t42 = static_cast<uint32_t>(ctx.edi + 0x00000078u);
    mem.w32(t42, ctx.ebx);
    // 0x004dbc39: mov dword ptr [edi + 0x7c], ebx
    uint32_t t43 = static_cast<uint32_t>(ctx.edi + 0x0000007cu);
    mem.w32(t43, ctx.ebx);
    goto bb_004dbc3c;
}
bb_004dbc20: {
    // 0x004dbc20: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004dbc22: call 0x414000
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, 0x004dbc27u);
    sub_00414000(ctx, mem);
    // 0x004dbc27: push esi
    uint32_t t45 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    mem.w32(t45, ctx.esi);
    // 0x004dbc28: call 0x4e02f3
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, 0x004dbc2du);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dbc2d: add esp, 4
    uint32_t t47 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t47);
    ctx.esp = static_cast<uint32_t>(t47);
    goto bb_004dbc30;
}
bb_004dbc6d: {
    // 0x004dbc6d: mov ecx, dword ptr [esp + 0x14]
    uint32_t t48 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t49 = mem.r32(t48);
    ctx.ecx = static_cast<uint32_t>(t49);
    // 0x004dbc71: push ecx
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, ctx.ecx);
    // 0x004dbc72: push esi
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, ctx.esi);
    // 0x004dbc73: push eax
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, ctx.eax);
    // 0x004dbc74: push esi
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, ctx.esi);
    // 0x004dbc75: lea edx, [esp + 0x24]
    uint32_t t54 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    ctx.edx = static_cast<uint32_t>(t54);
    // 0x004dbc79: push edx
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, ctx.edx);
    // 0x004dbc7a: push esi
    uint32_t t56 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    mem.w32(t56, ctx.esi);
    // 0x004dbc7b: call 0x4dcce0
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, 0x004dbc80u);
    sub_004dcce0(ctx, mem);
    // 0x004dbc80: mov eax, dword ptr [esi + 4]
    uint32_t t58 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t59 = mem.r32(t58);
    ctx.eax = static_cast<uint32_t>(t59);
    // 0x004dbc83: cmp eax, ebx
    uint32_t t60 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t60);
    // 0x004dbc85: mov dword ptr [esi + 4], ebx
    uint32_t t61 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t61, ctx.ebx);
    // 0x004dbc88: mov ecx, dword ptr [esi + 8]
    uint32_t t62 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t63 = mem.r32(t62);
    ctx.ecx = static_cast<uint32_t>(t63);
    // 0x004dbc8b: mov dword ptr [esi + 8], ebx
    uint32_t t64 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t64, ctx.ebx);
    // 0x004dbc8e: mov edx, dword ptr [esi + 0xc]
    uint32_t t65 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    uint32_t t66 = mem.r32(t65);
    ctx.edx = static_cast<uint32_t>(t66);
    // 0x004dbc91: mov dword ptr [esp + 0x20], eax
    uint32_t t67 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t67, ctx.eax);
    // 0x004dbc95: mov dword ptr [esp + 0x24], ecx
    uint32_t t68 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t68, ctx.ecx);
    // 0x004dbc99: mov dword ptr [esi + 0xc], ebx
    uint32_t t69 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t69, ctx.ebx);
    // 0x004dbc9c: mov dword ptr [esp + 0x28], edx
    uint32_t t70 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t70, ctx.edx);
    // 0x004dbca0: mov dword ptr [esp + 0x38], 0xffffffff
    uint32_t t71 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    mem.w32(t71, 0xffffffffu);
    // 0x004dbca8: je 0x4dbcc9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dbcc9;
    goto bb_004dbcaa;
}
bb_004dbc64: {
    // 0x004dbc64: call 0x4e0bf2
    uint32_t t72 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    mem.w32(t72, 0x004dbc69u);
    hle_crt_004e0bf2(ctx, mem);
    // 0x004dbc69: mov eax, dword ptr [esp + 0x10]
    uint32_t t73 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t74 = mem.r32(t73);
    ctx.eax = static_cast<uint32_t>(t74);
    goto bb_004dbc6d;
}
bb_004dbcc9: {
    // 0x004dbcc9: mov eax, dword ptr [edi + 0x70]
    uint32_t t75 = static_cast<uint32_t>(ctx.edi + 0x00000070u);
    uint32_t t76 = mem.r32(t75);
    ctx.eax = static_cast<uint32_t>(t76);
    // 0x004dbccc: cmp dword ptr [edi + 0x6c], eax
    uint32_t t77 = static_cast<uint32_t>(ctx.edi + 0x0000006cu);
    uint32_t t78 = mem.r32(t77);
    uint32_t t79 = static_cast<uint32_t>(t78 - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t78, ctx.eax, t79);
    // 0x004dbccf: lea esi, [edi + 0x68]
    uint32_t t80 = static_cast<uint32_t>(ctx.edi + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t80);
    // 0x004dbcd2: mov dword ptr [esp + 0x10], eax
    uint32_t t81 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t81, ctx.eax);
    // 0x004dbcd6: jbe 0x4dbcdd
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_004dbcdd;
    goto bb_004dbcd8;
}
bb_004dbcaa: {
    // 0x004dbcaa: mov edx, dword ptr [esp + 0x14]
    uint32_t t82 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t83 = mem.r32(t82);
    ctx.edx = static_cast<uint32_t>(t83);
    // 0x004dbcae: push edx
    uint32_t t84 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    mem.w32(t84, ctx.edx);
    // 0x004dbcaf: mov edi, ecx
    ctx.edi = static_cast<uint32_t>(ctx.ecx);
    // 0x004dbcb1: call 0x4dd220
    uint32_t t85 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t85);
    mem.w32(t85, 0x004dbcb6u);
    sub_004dd220(ctx, mem);
    // 0x004dbcb6: mov eax, dword ptr [esp + 0x24]
    uint32_t t86 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t87 = mem.r32(t86);
    ctx.eax = static_cast<uint32_t>(t87);
    // 0x004dbcba: add esp, 4
    uint32_t t88 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t88);
    ctx.esp = static_cast<uint32_t>(t88);
    // 0x004dbcbd: push eax
    uint32_t t89 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t89);
    mem.w32(t89, ctx.eax);
    // 0x004dbcbe: call 0x4e02f3
    uint32_t t90 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    mem.w32(t90, 0x004dbcc3u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dbcc3: mov edi, dword ptr [ebp + 8]
    uint32_t t91 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t92 = mem.r32(t91);
    ctx.edi = static_cast<uint32_t>(t92);
    // 0x004dbcc6: add esp, 4
    uint32_t t93 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t93);
    ctx.esp = static_cast<uint32_t>(t93);
    goto bb_004dbcc9;
}
bb_004dbcdd: {
    // 0x004dbcdd: mov eax, dword ptr [esi + 4]
    uint32_t t94 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t95 = mem.r32(t94);
    ctx.eax = static_cast<uint32_t>(t95);
    // 0x004dbce0: cmp eax, dword ptr [esi + 8]
    uint32_t t96 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t97 = mem.r32(t96);
    uint32_t t98 = static_cast<uint32_t>(ctx.eax - t97);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, t97, t98);
    // 0x004dbce3: mov dword ptr [esp + 0x14], eax
    uint32_t t99 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t99, ctx.eax);
    // 0x004dbce7: jbe 0x4dbcf2
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_004dbcf2;
    goto bb_004dbce9;
}
bb_004dbcd8: {
    // 0x004dbcd8: call 0x4e0bf2
    uint32_t t100 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t100);
    mem.w32(t100, 0x004dbcddu);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004dbcdd;
}
bb_004dbcf2: {
    // 0x004dbcf2: mov ecx, dword ptr [esp + 0x10]
    uint32_t t101 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t102 = mem.r32(t101);
    ctx.ecx = static_cast<uint32_t>(t102);
    // 0x004dbcf6: push ecx
    uint32_t t103 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    mem.w32(t103, ctx.ecx);
    // 0x004dbcf7: push esi
    uint32_t t104 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t104);
    mem.w32(t104, ctx.esi);
    // 0x004dbcf8: push eax
    uint32_t t105 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t105);
    mem.w32(t105, ctx.eax);
    // 0x004dbcf9: push esi
    uint32_t t106 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t106);
    mem.w32(t106, ctx.esi);
    // 0x004dbcfa: lea edx, [esp + 0x24]
    uint32_t t107 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    ctx.edx = static_cast<uint32_t>(t107);
    // 0x004dbcfe: push edx
    uint32_t t108 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t108);
    mem.w32(t108, ctx.edx);
    // 0x004dbcff: push esi
    uint32_t t109 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t109);
    mem.w32(t109, ctx.esi);
    // 0x004dbd00: call 0x4dcce0
    uint32_t t110 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t110);
    mem.w32(t110, 0x004dbd05u);
    sub_004dcce0(ctx, mem);
    // 0x004dbd05: mov eax, dword ptr [esi + 4]
    uint32_t t111 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t112 = mem.r32(t111);
    ctx.eax = static_cast<uint32_t>(t112);
    // 0x004dbd08: cmp eax, ebx
    uint32_t t113 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t113);
    // 0x004dbd0a: mov dword ptr [esi + 4], ebx
    uint32_t t114 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t114, ctx.ebx);
    // 0x004dbd0d: mov ecx, dword ptr [esi + 8]
    uint32_t t115 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t116 = mem.r32(t115);
    ctx.ecx = static_cast<uint32_t>(t116);
    // 0x004dbd10: mov dword ptr [esi + 8], ebx
    uint32_t t117 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t117, ctx.ebx);
    // 0x004dbd13: mov edx, dword ptr [esi + 0xc]
    uint32_t t118 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    uint32_t t119 = mem.r32(t118);
    ctx.edx = static_cast<uint32_t>(t119);
    // 0x004dbd16: mov dword ptr [esp + 0x20], eax
    uint32_t t120 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t120, ctx.eax);
    // 0x004dbd1a: mov dword ptr [esp + 0x24], ecx
    uint32_t t121 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t121, ctx.ecx);
    // 0x004dbd1e: mov dword ptr [esi + 0xc], ebx
    uint32_t t122 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t122, ctx.ebx);
    // 0x004dbd21: mov dword ptr [esp + 0x28], edx
    uint32_t t123 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t123, ctx.edx);
    // 0x004dbd25: mov dword ptr [esp + 0x38], 0xffffffff
    uint32_t t124 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    mem.w32(t124, 0xffffffffu);
    // 0x004dbd2d: je 0x4dbd4e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dbd4e;
    goto bb_004dbd2f;
}
bb_004dbce9: {
    // 0x004dbce9: call 0x4e0bf2
    uint32_t t125 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t125);
    mem.w32(t125, 0x004dbceeu);
    hle_crt_004e0bf2(ctx, mem);
    // 0x004dbcee: mov eax, dword ptr [esp + 0x14]
    uint32_t t126 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t127 = mem.r32(t126);
    ctx.eax = static_cast<uint32_t>(t127);
    goto bb_004dbcf2;
}
bb_004dbd4e: {
    // 0x004dbd4e: push ebx
    uint32_t t128 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t128);
    mem.w32(t128, ctx.ebx);
    // 0x004dbd4f: push 0x534f8a
    uint32_t t129 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t129);
    mem.w32(t129, 0x00534f8au);
    // 0x004dbd54: lea ecx, [edi + 8]
    uint32_t t130 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    ctx.ecx = static_cast<uint32_t>(t130);
    // 0x004dbd57: mov dword ptr [esp + 0x28], ebx
    uint32_t t131 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t131, ctx.ebx);
    // 0x004dbd5b: mov dword ptr [esp + 0x2c], ebx
    uint32_t t132 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    mem.w32(t132, ctx.ebx);
    // 0x004dbd5f: mov dword ptr [esp + 0x30], ebx
    uint32_t t133 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    mem.w32(t133, ctx.ebx);
    // 0x004dbd63: call 0x407c10
    uint32_t t134 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t134);
    mem.w32(t134, 0x004dbd68u);
    sub_00407c10(ctx, mem);
    // 0x004dbd68: mov dword ptr [edi + 0x84], ebx
    uint32_t t135 = static_cast<uint32_t>(ctx.edi + 0x00000084u);
    mem.w32(t135, ctx.ebx);
    // 0x004dbd6e: mov dword ptr [edi + 4], ebx
    uint32_t t136 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    mem.w32(t136, ctx.ebx);
    // 0x004dbd71: mov ecx, dword ptr [esp + 0x30]
    uint32_t t137 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    uint32_t t138 = mem.r32(t137);
    ctx.ecx = static_cast<uint32_t>(t138);
    // 0x004dbd75: mov dword ptr fs:[0], ecx
    uint32_t t139 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t139, ctx.ecx);
    // 0x004dbd7c: pop ecx
    uint32_t t140 = ctx.esp;
    uint32_t t141 = mem.r32(t140);
    uint32_t t142 = static_cast<uint32_t>(t140 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t142);
    ctx.ecx = static_cast<uint32_t>(t141);
    // 0x004dbd7d: pop edi
    uint32_t t143 = ctx.esp;
    uint32_t t144 = mem.r32(t143);
    uint32_t t145 = static_cast<uint32_t>(t143 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t145);
    ctx.edi = static_cast<uint32_t>(t144);
    // 0x004dbd7e: pop esi
    uint32_t t146 = ctx.esp;
    uint32_t t147 = mem.r32(t146);
    uint32_t t148 = static_cast<uint32_t>(t146 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t148);
    ctx.esi = static_cast<uint32_t>(t147);
    // 0x004dbd7f: pop ebx
    uint32_t t149 = ctx.esp;
    uint32_t t150 = mem.r32(t149);
    uint32_t t151 = static_cast<uint32_t>(t149 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t151);
    ctx.ebx = static_cast<uint32_t>(t150);
    // 0x004dbd80: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x004dbd82: pop ebp
    uint32_t t152 = ctx.esp;
    uint32_t t153 = mem.r32(t152);
    uint32_t t154 = static_cast<uint32_t>(t152 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t154);
    ctx.ebp = static_cast<uint32_t>(t153);
    // 0x004dbd83: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_004dbd2f: {
    // 0x004dbd2f: mov edx, dword ptr [esp + 0x14]
    uint32_t t155 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t156 = mem.r32(t155);
    ctx.edx = static_cast<uint32_t>(t156);
    // 0x004dbd33: push edx
    uint32_t t157 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t157);
    mem.w32(t157, ctx.edx);
    // 0x004dbd34: mov edi, ecx
    ctx.edi = static_cast<uint32_t>(ctx.ecx);
    // 0x004dbd36: call 0x4dd220
    uint32_t t158 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t158);
    mem.w32(t158, 0x004dbd3bu);
    sub_004dd220(ctx, mem);
    // 0x004dbd3b: mov eax, dword ptr [esp + 0x24]
    uint32_t t159 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t160 = mem.r32(t159);
    ctx.eax = static_cast<uint32_t>(t160);
    // 0x004dbd3f: add esp, 4
    uint32_t t161 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t161);
    ctx.esp = static_cast<uint32_t>(t161);
    // 0x004dbd42: push eax
    uint32_t t162 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t162);
    mem.w32(t162, ctx.eax);
    // 0x004dbd43: call 0x4e02f3
    uint32_t t163 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t163);
    mem.w32(t163, 0x004dbd48u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dbd48: mov edi, dword ptr [ebp + 8]
    uint32_t t164 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t165 = mem.r32(t164);
    ctx.edi = static_cast<uint32_t>(t165);
    // 0x004dbd4b: add esp, 4
    uint32_t t166 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t166);
    ctx.esp = static_cast<uint32_t>(t166);
    goto bb_004dbd4e;
}
}

// sub_004dbd90 | subsystem=FilePacFunc | canonical | 8 blocks | 39 insns
void sub_004dbd90(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dbd90: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x004dbd91: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
    // 0x004dbd92: push edi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.edi);
    // 0x004dbd93: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x004dbd95: cmp dword ptr [edi + 4], 0
    uint32_t t3 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t4 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t4, 0x00000000u, t5);
    // 0x004dbd99: jne 0x4dbda1
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dbda1;
    goto bb_004dbd9b;
}
bb_004dbda1: {
    // 0x004dbda1: call 0x4dbf40
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x004dbda6u);
    sub_004dbf40(ctx, mem);
    // 0x004dbda6: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004dbda8: test esi, esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    // 0x004dbdaa: je 0x4dbd9b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dbd9b;
    goto bb_004dbdac;
}
bb_004dbd9b: {
    // 0x004dbd9b: xor eax, eax
    uint32_t t8 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t8);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x004dbd9d: pop edi
    uint32_t t9 = ctx.esp;
    uint32_t t10 = mem.r32(t9);
    uint32_t t11 = static_cast<uint32_t>(t9 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    ctx.edi = static_cast<uint32_t>(t10);
    // 0x004dbd9e: pop esi
    uint32_t t12 = ctx.esp;
    uint32_t t13 = mem.r32(t12);
    uint32_t t14 = static_cast<uint32_t>(t12 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    ctx.esi = static_cast<uint32_t>(t13);
    // 0x004dbd9f: pop ecx
    uint32_t t15 = ctx.esp;
    uint32_t t16 = mem.r32(t15);
    uint32_t t17 = static_cast<uint32_t>(t15 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    ctx.ecx = static_cast<uint32_t>(t16);
    // 0x004dbda0: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004dbdac: {
    // 0x004dbdac: cmp dword ptr [edi + 0x20], 0x10
    uint32_t t18 = static_cast<uint32_t>(ctx.edi + 0x00000020u);
    uint32_t t19 = mem.r32(t18);
    uint32_t t20 = static_cast<uint32_t>(t19 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t19, 0x00000010u, t20);
    // 0x004dbdb0: jb 0x4dbdb7
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004dbdb7;
    goto bb_004dbdb2;
}
bb_004dbdb7: {
    // 0x004dbdb7: lea eax, [edi + 0xc]
    uint32_t t21 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    ctx.eax = static_cast<uint32_t>(t21);
    goto bb_004dbdba;
}
bb_004dbdb2: {
    // 0x004dbdb2: mov eax, dword ptr [edi + 0xc]
    uint32_t t22 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    uint32_t t23 = mem.r32(t22);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x004dbdb5: jmp 0x4dbdba
}
bb_004dbdba: {
    // 0x004dbdba: push eax
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, ctx.eax);
    // 0x004dbdbb: call 0x4db640
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x004dbdc0u);
    sub_004db640(ctx, mem);
    // 0x004dbdc0: add esp, 4
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t26);
    ctx.esp = static_cast<uint32_t>(t26);
    // 0x004dbdc3: test eax, eax
    uint32_t t27 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t27);
    // 0x004dbdc5: mov dword ptr [edi + 0x88], eax
    uint32_t t28 = static_cast<uint32_t>(ctx.edi + 0x00000088u);
    mem.w32(t28, ctx.eax);
    // 0x004dbdcb: je 0x4dbd9b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dbd9b;
}
{
    // 0x004dbdcd: mov dword ptr [edi + 0x78], esi
    uint32_t t29 = static_cast<uint32_t>(ctx.edi + 0x00000078u);
    mem.w32(t29, ctx.esi);
    // 0x004dbdd0: mov edx, dword ptr [esi + 0x24]
    uint32_t t30 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    uint32_t t31 = mem.r32(t30);
    ctx.edx = static_cast<uint32_t>(t31);
    // 0x004dbdd3: add edx, dword ptr [edi + 0x3c]
    uint32_t t32 = static_cast<uint32_t>(ctx.edi + 0x0000003cu);
    uint32_t t33 = mem.r32(t32);
    uint32_t t34 = static_cast<uint32_t>(ctx.edx + t33);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, t33, t34);
    ctx.edx = static_cast<uint32_t>(t34);
    // 0x004dbdd6: push 0
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, 0x00000000u);
    // 0x004dbdd8: push edx
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, ctx.edx);
    // 0x004dbdd9: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x004dbddb: call 0x413e00
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, 0x004dbde0u);
    sub_00413e00(ctx, mem);
    // 0x004dbde0: mov dword ptr [edi + 0x7c], 0
    uint32_t t38 = static_cast<uint32_t>(ctx.edi + 0x0000007cu);
    mem.w32(t38, 0x00000000u);
    // 0x004dbde7: pop edi
    uint32_t t39 = ctx.esp;
    uint32_t t40 = mem.r32(t39);
    uint32_t t41 = static_cast<uint32_t>(t39 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    ctx.edi = static_cast<uint32_t>(t40);
    // 0x004dbde8: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x004dbded: pop esi
    uint32_t t42 = ctx.esp;
    uint32_t t43 = mem.r32(t42);
    uint32_t t44 = static_cast<uint32_t>(t42 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    ctx.esi = static_cast<uint32_t>(t43);
    // 0x004dbdee: pop ecx
    uint32_t t45 = ctx.esp;
    uint32_t t46 = mem.r32(t45);
    uint32_t t47 = static_cast<uint32_t>(t45 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    ctx.ecx = static_cast<uint32_t>(t46);
    // 0x004dbdef: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004dbdf0 | subsystem=FilePacFunc | canonical | 15 blocks | 66 insns
void sub_004dbdf0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dbdf0: sub esp, 0x1c
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x0000001cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x0000001cu, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x004dbdf3: mov eax, dword ptr [0x54b458]
    uint32_t t1 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x004dbdf8: xor eax, esp
    uint32_t t2 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x004dbdfa: mov dword ptr [esp + 0x18], eax
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t3, ctx.eax);
    // 0x004dbdfe: mov eax, dword ptr [esi + 0x78]
    uint32_t t4 = static_cast<uint32_t>(ctx.esi + 0x00000078u);
    uint32_t t5 = mem.r32(t4);
    ctx.eax = static_cast<uint32_t>(t5);
    // 0x004dbe01: test eax, eax
    uint32_t t6 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t6);
    // 0x004dbe03: push ebp
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.ebp);
    // 0x004dbe04: mov ebp, dword ptr [esp + 0x24]
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t9 = mem.r32(t8);
    ctx.ebp = static_cast<uint32_t>(t9);
    // 0x004dbe08: mov dword ptr [esp + 4], ecx
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    mem.w32(t10, ctx.ecx);
    // 0x004dbe0c: jne 0x4dbe20
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dbe20;
    goto bb_004dbe0e;
}
bb_004dbe20: {
    // 0x004dbe20: test ebp, ebp
    uint32_t t11 = static_cast<uint32_t>(ctx.ebp & ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    // 0x004dbe22: jne 0x4dbe27
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dbe27;
    goto bb_004dbe24;
}
bb_004dbe0e: {
    // 0x004dbe0e: pop ebp
    uint32_t t12 = ctx.esp;
    uint32_t t13 = mem.r32(t12);
    uint32_t t14 = static_cast<uint32_t>(t12 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    ctx.ebp = static_cast<uint32_t>(t13);
    // 0x004dbe0f: mov ecx, dword ptr [esp + 0x18]
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t16 = mem.r32(t15);
    ctx.ecx = static_cast<uint32_t>(t16);
    // 0x004dbe13: xor ecx, esp
    uint32_t t17 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t17);
    ctx.ecx = static_cast<uint32_t>(t17);
    // 0x004dbe15: call 0x4e02f8
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x004dbe1au);
    hle_crt_004e02f8(ctx, mem);
    // 0x004dbe1a: add esp, 0x1c
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000001cu, t19);
    ctx.esp = static_cast<uint32_t>(t19);
    // 0x004dbe1d: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_004dbe27: {
    // 0x004dbe27: push edi
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, ctx.edi);
    // 0x004dbe28: mov edi, dword ptr [esi + 0x88]
    uint32_t t21 = static_cast<uint32_t>(ctx.esi + 0x00000088u);
    uint32_t t22 = mem.r32(t21);
    ctx.edi = static_cast<uint32_t>(t22);
    // 0x004dbe2e: test edi, edi
    uint32_t t23 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t23);
    // 0x004dbe30: je 0x4dbe47
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dbe47;
    goto bb_004dbe32;
}
bb_004dbe24: {
    // 0x004dbe24: mov ebp, dword ptr [eax + 0x28]
    uint32_t t24 = static_cast<uint32_t>(ctx.eax + 0x00000028u);
    uint32_t t25 = mem.r32(t24);
    ctx.ebp = static_cast<uint32_t>(t25);
    goto bb_004dbe27;
}
bb_004dbe47: {
    // 0x004dbe47: cmp dword ptr [esi + 0x4c], 0
    uint32_t t26 = static_cast<uint32_t>(ctx.esi + 0x0000004cu);
    uint32_t t27 = mem.r32(t26);
    uint32_t t28 = static_cast<uint32_t>(t27 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t27, 0x00000000u, t28);
    // 0x004dbe4b: je 0x4dbe9b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dbe9b;
    goto bb_004dbe4d;
}
bb_004dbe32: {
    // 0x004dbe32: push ebp
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, ctx.ebp);
    // 0x004dbe33: push ebp
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, ctx.ebp);
    // 0x004dbe34: push ecx
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, ctx.ecx);
    // 0x004dbe35: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004dbe37: call 0x413fb0
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x004dbe3cu);
    sub_00413fb0(ctx, mem);
    // 0x004dbe3c: test eax, eax
    uint32_t t33 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t33);
    // 0x004dbe3e: jne 0x4dbe44
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dbe44;
    goto bb_004dbe40;
}
bb_004dbe9b: {
    // 0x004dbe9b: add dword ptr [esi + 0x7c], edi
    uint32_t t34 = static_cast<uint32_t>(ctx.esi + 0x0000007cu);
    uint32_t t35 = mem.r32(t34);
    uint32_t t36 = static_cast<uint32_t>(t35 + ctx.edi);
    recomp_detail::update_flags_add<uint32_t>(ctx, t35, ctx.edi, t36);
    mem.w32(t34, t36);
    // 0x004dbe9e: mov ecx, dword ptr [esp + 0x20]
    uint32_t t37 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t38 = mem.r32(t37);
    ctx.ecx = static_cast<uint32_t>(t38);
    // 0x004dbea2: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x004dbea4: pop edi
    uint32_t t39 = ctx.esp;
    uint32_t t40 = mem.r32(t39);
    uint32_t t41 = static_cast<uint32_t>(t39 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    ctx.edi = static_cast<uint32_t>(t40);
    // 0x004dbea5: pop ebp
    uint32_t t42 = ctx.esp;
    uint32_t t43 = mem.r32(t42);
    uint32_t t44 = static_cast<uint32_t>(t42 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    ctx.ebp = static_cast<uint32_t>(t43);
    // 0x004dbea6: xor ecx, esp
    uint32_t t45 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t45);
    ctx.ecx = static_cast<uint32_t>(t45);
    // 0x004dbea8: call 0x4e02f8
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, 0x004dbeadu);
    hle_crt_004e02f8(ctx, mem);
    // 0x004dbead: add esp, 0x1c
    uint32_t t47 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000001cu, t47);
    ctx.esp = static_cast<uint32_t>(t47);
    // 0x004dbeb0: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_004dbe4d: {
    // 0x004dbe4d: mov ecx, dword ptr [esi + 0x54]
    uint32_t t48 = static_cast<uint32_t>(ctx.esi + 0x00000054u);
    uint32_t t49 = mem.r32(t48);
    ctx.ecx = static_cast<uint32_t>(t49);
    // 0x004dbe50: mov al, byte ptr [esi + 0x50]
    uint32_t t50 = static_cast<uint32_t>(ctx.esi + 0x00000050u);
    uint8_t t51 = mem.r8(t50);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t51));
    // 0x004dbe53: test al, al
    uint8_t t52 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t52);
    // 0x004dbe55: mov dword ptr [esp + 0x1c], ecx
    uint32_t t53 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t53, ctx.ecx);
    // 0x004dbe59: mov ecx, dword ptr [esi + 0x38]
    uint32_t t54 = static_cast<uint32_t>(ctx.esi + 0x00000038u);
    uint32_t t55 = mem.r32(t54);
    ctx.ecx = static_cast<uint32_t>(t55);
    // 0x004dbe5c: mov dword ptr [esp + 0xc], ecx
    uint32_t t56 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t56, ctx.ecx);
    // 0x004dbe60: mov byte ptr [esp + 0x10], 1
    uint32_t t57 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w8(t57, uint8_t{0x01u});
    // 0x004dbe65: je 0x4dbe6b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dbe6b;
    goto bb_004dbe67;
}
bb_004dbe44: {
    // 0x004dbe44: mov edi, dword ptr [edi + 0x20]
    uint32_t t58 = static_cast<uint32_t>(ctx.edi + 0x00000020u);
    uint32_t t59 = mem.r32(t58);
    ctx.edi = static_cast<uint32_t>(t59);
    goto bb_004dbe47;
}
bb_004dbe40: {
    // 0x004dbe40: xor edi, edi
    uint32_t t60 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t60);
    ctx.edi = static_cast<uint32_t>(t60);
    // 0x004dbe42: jmp 0x4dbe47
    goto bb_004dbe47;
}
bb_004dbe6b: {
    // 0x004dbe6b: mov dword ptr [esp + 0x12], ecx
    uint32_t t61 = static_cast<uint32_t>(ctx.esp + 0x00000012u);
    mem.w32(t61, ctx.ecx);
    // 0x004dbe6f: mov ecx, dword ptr [esi + 0x7c]
    uint32_t t62 = static_cast<uint32_t>(ctx.esi + 0x0000007cu);
    uint32_t t63 = mem.r32(t62);
    ctx.ecx = static_cast<uint32_t>(t63);
    // 0x004dbe72: test ecx, ecx
    uint32_t t64 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t64);
    // 0x004dbe74: mov dword ptr [esp + 0x18], 0
    uint32_t t65 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t65, 0x00000000u);
    // 0x004dbe7c: mov byte ptr [esp + 0x11], 0
    uint32_t t66 = static_cast<uint32_t>(ctx.esp + 0x00000011u);
    mem.w8(t66, uint8_t{0x00u});
    // 0x004dbe81: je 0x4dbe8c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dbe8c;
    goto bb_004dbe83;
}
bb_004dbe67: {
    // 0x004dbe67: mov byte ptr [esp + 0x10], al
    uint32_t t67 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w8(t67, recomp_detail::r8l(ctx.eax));
    goto bb_004dbe6b;
}
bb_004dbe8c: {
    // 0x004dbe8c: mov edx, dword ptr [esp + 8]
    uint32_t t68 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t69 = mem.r32(t68);
    ctx.edx = static_cast<uint32_t>(t69);
    // 0x004dbe90: push ebp
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, ctx.ebp);
    // 0x004dbe91: push edx
    uint32_t t71 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t71);
    mem.w32(t71, ctx.edx);
    // 0x004dbe92: lea eax, [esp + 0x14]
    uint32_t t72 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.eax = static_cast<uint32_t>(t72);
    // 0x004dbe96: call 0x4db5e0
    uint32_t t73 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    mem.w32(t73, 0x004dbe9bu);
    sub_004db5e0(ctx, mem);
    goto bb_004dbe9b;
}
bb_004dbe83: {
    // 0x004dbe83: lea eax, [esp + 0xc]
    uint32_t t74 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    ctx.eax = static_cast<uint32_t>(t74);
    // 0x004dbe87: call 0x4db590
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, 0x004dbe8cu);
    sub_004db590(ctx, mem);
    goto bb_004dbe8c;
}
}

// sub_004dbf40 | subsystem=FilePacFunc | canonical | 14 blocks | 80 insns
void sub_004dbf40(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dbf40: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x004dbf42: push 0x518be8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00518be8u);
    // 0x004dbf47: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004dbf4d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x004dbf4e: sub esp, 0x24
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000024u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000024u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x004dbf51: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x004dbf56: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x004dbf58: mov dword ptr [esp + 0x20], eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t8, ctx.eax);
    // 0x004dbf5c: push ebp
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ebp);
    // 0x004dbf5d: push esi
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.esi);
    // 0x004dbf5e: mov eax, dword ptr [0x54b458]
    uint32_t t11 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x004dbf63: xor eax, esp
    uint32_t t12 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t12);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x004dbf65: push eax
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, ctx.eax);
    // 0x004dbf66: lea eax, [esp + 0x30]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x004dbf6a: mov dword ptr fs:[0], eax
    uint32_t t15 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t15, ctx.eax);
    // 0x004dbf70: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004dbf72: push esi
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, ctx.esi);
    // 0x004dbf73: call dword ptr [0x51b204]
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x004dbf79u);
    hle_iat_call(ctx, mem, 0x0051b204u);
    // 0x004dbf79: mov dword ptr [esp + 0xc], eax
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t18, ctx.eax);
    // 0x004dbf7d: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004dbf7f: mov dword ptr [esp + 0x28], 0xf
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t19, 0x0000000fu);
    // 0x004dbf87: mov dword ptr [esp + 0x24], 0
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t20, 0x00000000u);
    // 0x004dbf8f: mov byte ptr [esp + 0x14], 0
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w8(t21, uint8_t{0x00u});
    // 0x004dbf94: lea edx, [eax + 1]
    uint32_t t22 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.edx = static_cast<uint32_t>(t22);
}
bb_004dbf97: {
    // 0x004dbf97: mov cl, byte ptr [eax]
    uint8_t t23 = mem.r8(ctx.eax);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t23));
    // 0x004dbf99: add eax, 1
    uint32_t t24 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t24);
    ctx.eax = static_cast<uint32_t>(t24);
    // 0x004dbf9c: test cl, cl
    uint8_t t25 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t25);
    // 0x004dbf9e: jne 0x4dbf97
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dbf97;
}
{
    // 0x004dbfa0: sub eax, edx
    uint32_t t26 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t26);
    ctx.eax = static_cast<uint32_t>(t26);
    // 0x004dbfa2: push eax
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, ctx.eax);
    // 0x004dbfa3: push esi
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, ctx.esi);
    // 0x004dbfa4: lea ecx, [esp + 0x18]
    uint32_t t29 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.ecx = static_cast<uint32_t>(t29);
    // 0x004dbfa8: call 0x407c10
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x004dbfadu);
    sub_00407c10(ctx, mem);
    // 0x004dbfad: mov dword ptr [esp + 0x38], 0
    uint32_t t31 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    mem.w32(t31, 0x00000000u);
    // 0x004dbfb5: mov eax, dword ptr [esp + 0x14]
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t33 = mem.r32(t32);
    ctx.eax = static_cast<uint32_t>(t33);
    // 0x004dbfb9: mov ebp, 0x10
    ctx.ebp = static_cast<uint32_t>(0x00000010u);
    // 0x004dbfbe: cmp dword ptr [esp + 0x28], ebp
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t35 = mem.r32(t34);
    uint32_t t36 = static_cast<uint32_t>(t35 - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t35, ctx.ebp, t36);
    // 0x004dbfc2: jae 0x4dbfc8
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004dbfc8;
    goto bb_004dbfc4;
}
bb_004dbfc8: {
    // 0x004dbfc8: push eax
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, ctx.eax);
    // 0x004dbfc9: call dword ptr [0x51b210]
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, 0x004dbfcfu);
    hle_iat_call(ctx, mem, 0x0051b210u);
    // 0x004dbfcf: cmp dword ptr [esp + 0x28], ebp
    uint32_t t39 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t40 = mem.r32(t39);
    uint32_t t41 = static_cast<uint32_t>(t40 - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t40, ctx.ebp, t41);
    // 0x004dbfd3: mov ecx, dword ptr [esp + 0x14]
    uint32_t t42 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t43 = mem.r32(t42);
    ctx.ecx = static_cast<uint32_t>(t43);
    // 0x004dbfd7: jae 0x4dbfdd
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004dbfdd;
    goto bb_004dbfd9;
}
bb_004dbfc4: {
    // 0x004dbfc4: lea eax, [esp + 0x14]
    uint32_t t44 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.eax = static_cast<uint32_t>(t44);
    goto bb_004dbfc8;
}
bb_004dbfdd: {
    // 0x004dbfdd: push edi
    uint32_t t45 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    mem.w32(t45, ctx.edi);
    // 0x004dbfde: call 0x4dc6a0
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, 0x004dbfe3u);
    sub_004dc6a0(ctx, mem);
    // 0x004dbfe3: test eax, eax
    uint32_t t47 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t47);
    // 0x004dbfe5: jne 0x4dbffe
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dbffe;
    goto bb_004dbfe7;
}
bb_004dbfd9: {
    // 0x004dbfd9: lea ecx, [esp + 0x14]
    uint32_t t48 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.ecx = static_cast<uint32_t>(t48);
    goto bb_004dbfdd;
}
bb_004dbffe: {
    // 0x004dbffe: mov eax, dword ptr [eax + 0x20]
    uint32_t t49 = static_cast<uint32_t>(ctx.eax + 0x00000020u);
    uint32_t t50 = mem.r32(t49);
    ctx.eax = static_cast<uint32_t>(t50);
    // 0x004dc001: mov ecx, dword ptr [esp + 0xc]
    uint32_t t51 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t52 = mem.r32(t51);
    ctx.ecx = static_cast<uint32_t>(t52);
    // 0x004dc005: push edi
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, ctx.edi);
    // 0x004dc006: mov edx, eax
    ctx.edx = static_cast<uint32_t>(ctx.eax);
    // 0x004dc008: call 0x4dc8b0
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, 0x004dc00du);
    sub_004dc8b0(ctx, mem);
    // 0x004dc00d: cmp dword ptr [esp + 0x28], ebp
    uint32_t t55 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t56 = mem.r32(t55);
    uint32_t t57 = static_cast<uint32_t>(t56 - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t56, ctx.ebp, t57);
    // 0x004dc011: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004dc013: jb 0x4dc022
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004dc022;
    goto bb_004dc015;
}
bb_004dbfe7: {
    // 0x004dbfe7: cmp dword ptr [esp + 0x28], ebp
    uint32_t t58 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t59 = mem.r32(t58);
    uint32_t t60 = static_cast<uint32_t>(t59 - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t59, ctx.ebp, t60);
    // 0x004dbfeb: jb 0x4dbffa
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004dbffa;
    goto bb_004dbfed;
}
bb_004dc022: {
    // 0x004dc022: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    goto bb_004dc024;
}
bb_004dc015: {
    // 0x004dc015: mov ecx, dword ptr [esp + 0x14]
    uint32_t t61 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t62 = mem.r32(t61);
    ctx.ecx = static_cast<uint32_t>(t62);
    // 0x004dc019: push ecx
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, ctx.ecx);
    // 0x004dc01a: call 0x4e02f3
    uint32_t t64 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    mem.w32(t64, 0x004dc01fu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dc01f: add esp, 4
    uint32_t t65 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t65);
    ctx.esp = static_cast<uint32_t>(t65);
    goto bb_004dc022;
}
bb_004dbffa: {
    // 0x004dbffa: xor eax, eax
    uint32_t t66 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t66);
    ctx.eax = static_cast<uint32_t>(t66);
    // 0x004dbffc: jmp 0x4dc024
    goto bb_004dc024;
}
bb_004dbfed: {
    // 0x004dbfed: mov eax, dword ptr [esp + 0x14]
    uint32_t t67 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t68 = mem.r32(t67);
    ctx.eax = static_cast<uint32_t>(t68);
    // 0x004dbff1: push eax
    uint32_t t69 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    mem.w32(t69, ctx.eax);
    // 0x004dbff2: call 0x4e02f3
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, 0x004dbff7u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dbff7: add esp, 4
    uint32_t t71 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t71);
    ctx.esp = static_cast<uint32_t>(t71);
    goto bb_004dbffa;
}
bb_004dc024: {
    // 0x004dc024: mov ecx, dword ptr [esp + 0x30]
    uint32_t t72 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    uint32_t t73 = mem.r32(t72);
    ctx.ecx = static_cast<uint32_t>(t73);
    // 0x004dc028: mov dword ptr fs:[0], ecx
    uint32_t t74 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t74, ctx.ecx);
    // 0x004dc02f: pop ecx
    uint32_t t75 = ctx.esp;
    uint32_t t76 = mem.r32(t75);
    uint32_t t77 = static_cast<uint32_t>(t75 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    ctx.ecx = static_cast<uint32_t>(t76);
    // 0x004dc030: pop esi
    uint32_t t78 = ctx.esp;
    uint32_t t79 = mem.r32(t78);
    uint32_t t80 = static_cast<uint32_t>(t78 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    ctx.esi = static_cast<uint32_t>(t79);
    // 0x004dc031: pop ebp
    uint32_t t81 = ctx.esp;
    uint32_t t82 = mem.r32(t81);
    uint32_t t83 = static_cast<uint32_t>(t81 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t83);
    ctx.ebp = static_cast<uint32_t>(t82);
    // 0x004dc032: mov ecx, dword ptr [esp + 0x20]
    uint32_t t84 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t85 = mem.r32(t84);
    ctx.ecx = static_cast<uint32_t>(t85);
    // 0x004dc036: xor ecx, esp
    uint32_t t86 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t86);
    ctx.ecx = static_cast<uint32_t>(t86);
    // 0x004dc038: call 0x4e02f8
    uint32_t t87 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t87);
    mem.w32(t87, 0x004dc03du);
    hle_crt_004e02f8(ctx, mem);
    // 0x004dc03d: add esp, 0x30
    uint32_t t88 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000030u, t88);
    ctx.esp = static_cast<uint32_t>(t88);
    // 0x004dc040: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004dc050 | subsystem=FilePacFunc | canonical | 92 blocks | 510 insns
void sub_004dc050(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dc050: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x004dc052: push 0x516510
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00516510u);
    // 0x004dc057: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004dc05d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x004dc05e: sub esp, 0x6c
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x0000006cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x0000006cu, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x004dc061: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x004dc066: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x004dc068: mov dword ptr [esp + 0x68], eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    mem.w32(t8, ctx.eax);
    // 0x004dc06c: push ebx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ebx);
    // 0x004dc06d: push ebp
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.ebp);
    // 0x004dc06e: push esi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.esi);
    // 0x004dc06f: push edi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.edi);
    // 0x004dc070: mov eax, dword ptr [0x54b458]
    uint32_t t13 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x004dc075: xor eax, esp
    uint32_t t14 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x004dc077: push eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.eax);
    // 0x004dc078: lea eax, [esp + 0x80]
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000080u);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x004dc07f: mov dword ptr fs:[0], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t17, ctx.eax);
    // 0x004dc085: mov ebx, ecx
    ctx.ebx = static_cast<uint32_t>(ctx.ecx);
    // 0x004dc087: mov esi, edx
    ctx.esi = static_cast<uint32_t>(ctx.edx);
    // 0x004dc089: push ebx
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, ctx.ebx);
    // 0x004dc08a: mov dword ptr [esp + 0x2c], ebx
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    mem.w32(t19, ctx.ebx);
    // 0x004dc08e: mov dword ptr [esp + 0x44], esi
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    mem.w32(t20, ctx.esi);
    // 0x004dc092: call 0x4dbbe0
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x004dc097u);
    sub_004dbbe0(ctx, mem);
    // 0x004dc097: push esi
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, ctx.esi);
    // 0x004dc098: call 0x4db640
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x004dc09du);
    sub_004db640(ctx, mem);
    // 0x004dc09d: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x004dc09f: add esp, 4
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t24);
    ctx.esp = static_cast<uint32_t>(t24);
    // 0x004dc0a2: test edi, edi
    uint32_t t25 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t25);
    // 0x004dc0a4: je 0x4dc0cf
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc0cf;
    goto bb_004dc0a6;
}
bb_004dc0cf: {
    // 0x004dc0cf: xor eax, eax
    uint32_t t26 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t26);
    ctx.eax = static_cast<uint32_t>(t26);
    // 0x004dc0d1: jmp 0x4dc678
    goto bb_004dc678;
}
bb_004dc0a6: {
    // 0x004dc0a6: push 0x34
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x00000034u);
    // 0x004dc0a8: lea eax, [ebx + 0x24]
    uint32_t t28 = static_cast<uint32_t>(ctx.ebx + 0x00000024u);
    ctx.eax = static_cast<uint32_t>(t28);
    // 0x004dc0ab: push 0x34
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x00000034u);
    // 0x004dc0ad: push eax
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, ctx.eax);
    // 0x004dc0ae: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004dc0b0: call 0x413fb0
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x004dc0b5u);
    sub_00413fb0(ctx, mem);
    // 0x004dc0b5: test eax, eax
    uint32_t t32 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t32);
    // 0x004dc0b7: je 0x4dc0bf
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc0bf;
    goto bb_004dc0b9;
}
bb_004dc678: {
    // 0x004dc678: mov ecx, dword ptr [esp + 0x80]
    uint32_t t33 = static_cast<uint32_t>(ctx.esp + 0x00000080u);
    uint32_t t34 = mem.r32(t33);
    ctx.ecx = static_cast<uint32_t>(t34);
    // 0x004dc67f: mov dword ptr fs:[0], ecx
    uint32_t t35 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t35, ctx.ecx);
    // 0x004dc686: pop ecx
    uint32_t t36 = ctx.esp;
    uint32_t t37 = mem.r32(t36);
    uint32_t t38 = static_cast<uint32_t>(t36 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    ctx.ecx = static_cast<uint32_t>(t37);
    // 0x004dc687: pop edi
    uint32_t t39 = ctx.esp;
    uint32_t t40 = mem.r32(t39);
    uint32_t t41 = static_cast<uint32_t>(t39 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    ctx.edi = static_cast<uint32_t>(t40);
    // 0x004dc688: pop esi
    uint32_t t42 = ctx.esp;
    uint32_t t43 = mem.r32(t42);
    uint32_t t44 = static_cast<uint32_t>(t42 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    ctx.esi = static_cast<uint32_t>(t43);
    // 0x004dc689: pop ebp
    uint32_t t45 = ctx.esp;
    uint32_t t46 = mem.r32(t45);
    uint32_t t47 = static_cast<uint32_t>(t45 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    ctx.ebp = static_cast<uint32_t>(t46);
    // 0x004dc68a: pop ebx
    uint32_t t48 = ctx.esp;
    uint32_t t49 = mem.r32(t48);
    uint32_t t50 = static_cast<uint32_t>(t48 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    ctx.ebx = static_cast<uint32_t>(t49);
    // 0x004dc68b: mov ecx, dword ptr [esp + 0x68]
    uint32_t t51 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    uint32_t t52 = mem.r32(t51);
    ctx.ecx = static_cast<uint32_t>(t52);
    // 0x004dc68f: xor ecx, esp
    uint32_t t53 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t53);
    ctx.ecx = static_cast<uint32_t>(t53);
    // 0x004dc691: call 0x4e02f8
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, 0x004dc696u);
    hle_crt_004e02f8(ctx, mem);
    // 0x004dc696: add esp, 0x78
    uint32_t t55 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000078u, t55);
    ctx.esp = static_cast<uint32_t>(t55);
    // 0x004dc699: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004dc0bf: {
    // 0x004dc0bf: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004dc0c1: call 0x414000
    uint32_t t56 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    mem.w32(t56, 0x004dc0c6u);
    sub_00414000(ctx, mem);
    // 0x004dc0c6: push edi
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, ctx.edi);
    // 0x004dc0c7: call 0x4e02f3
    uint32_t t58 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    mem.w32(t58, 0x004dc0ccu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dc0cc: add esp, 4
    uint32_t t59 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t59);
    ctx.esp = static_cast<uint32_t>(t59);
    goto bb_004dc0cf;
}
bb_004dc0b9: {
    // 0x004dc0b9: cmp dword ptr [edi + 0x20], 0x34
    uint32_t t60 = static_cast<uint32_t>(ctx.edi + 0x00000020u);
    uint32_t t61 = mem.r32(t60);
    uint32_t t62 = static_cast<uint32_t>(t61 - 0x00000034u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t61, 0x00000034u, t62);
    // 0x004dc0bd: je 0x4dc0d6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc0d6;
    goto bb_004dc0bf;
}
bb_004dc0d6: {
    // 0x004dc0d6: mov esi, dword ptr [ebx + 0x3c]
    uint32_t t63 = static_cast<uint32_t>(ctx.ebx + 0x0000003cu);
    uint32_t t64 = mem.r32(t63);
    ctx.esi = static_cast<uint32_t>(t64);
    // 0x004dc0d9: push 0x1b8
    uint32_t t65 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t65);
    mem.w32(t65, 0x000001b8u);
    // 0x004dc0de: push 0x53d514
    uint32_t t66 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    mem.w32(t66, 0x0053d514u);
    // 0x004dc0e3: sub esi, 0x34
    uint32_t t67 = static_cast<uint32_t>(ctx.esi - 0x00000034u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00000034u, t67);
    ctx.esi = static_cast<uint32_t>(t67);
    // 0x004dc0e6: push 4
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, 0x00000004u);
    // 0x004dc0e8: push esi
    uint32_t t69 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    mem.w32(t69, ctx.esi);
    // 0x004dc0e9: call 0x4e0680
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, 0x004dc0eeu);
    hle_crt_004e0680(ctx, mem);
    // 0x004dc0ee: add esp, 0x10
    uint32_t t71 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t71);
    ctx.esp = static_cast<uint32_t>(t71);
    // 0x004dc0f1: push esi
    uint32_t t72 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    mem.w32(t72, ctx.esi);
    // 0x004dc0f2: mov ebp, eax
    ctx.ebp = static_cast<uint32_t>(ctx.eax);
    // 0x004dc0f4: push esi
    uint32_t t73 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    mem.w32(t73, ctx.esi);
    // 0x004dc0f5: push ebp
    uint32_t t74 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    mem.w32(t74, ctx.ebp);
    // 0x004dc0f6: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004dc0f8: mov dword ptr [esp + 0x48], ebp
    uint32_t t75 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    mem.w32(t75, ctx.ebp);
    // 0x004dc0fc: call 0x413fb0
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    mem.w32(t76, 0x004dc101u);
    sub_00413fb0(ctx, mem);
    // 0x004dc101: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004dc103: call 0x414000
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, 0x004dc108u);
    sub_00414000(ctx, mem);
    // 0x004dc108: push edi
    uint32_t t78 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    mem.w32(t78, ctx.edi);
    // 0x004dc109: call 0x4e02f3
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, 0x004dc10eu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dc10e: add esp, 4
    uint32_t t80 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t80);
    ctx.esp = static_cast<uint32_t>(t80);
    // 0x004dc111: push esi
    uint32_t t81 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    mem.w32(t81, ctx.esi);
    // 0x004dc112: push ebp
    uint32_t t82 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t82);
    mem.w32(t82, ctx.ebp);
    // 0x004dc113: call 0x4db690
    uint32_t t83 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t83);
    mem.w32(t83, 0x004dc118u);
    sub_004db690(ctx, mem);
    // 0x004dc118: mov esi, dword ptr [ebx + 0x44]
    uint32_t t84 = static_cast<uint32_t>(ctx.ebx + 0x00000044u);
    uint32_t t85 = mem.r32(t84);
    ctx.esi = static_cast<uint32_t>(t85);
    // 0x004dc11b: sub esp, 0x24
    uint32_t t86 = static_cast<uint32_t>(ctx.esp - 0x00000024u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000024u, t86);
    ctx.esp = static_cast<uint32_t>(t86);
    // 0x004dc11e: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x004dc120: mov eax, esp
    ctx.eax = static_cast<uint32_t>(ctx.esp);
    // 0x004dc122: mov dword ptr [esp + 0x44], esp
    uint32_t t87 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    mem.w32(t87, ctx.esp);
    // 0x004dc126: push eax
    uint32_t t88 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t88);
    mem.w32(t88, ctx.eax);
    // 0x004dc127: mov dword ptr [esp + 0x4c], edi
    uint32_t t89 = static_cast<uint32_t>(ctx.esp + 0x0000004cu);
    mem.w32(t89, ctx.edi);
    // 0x004dc12b: call 0x4db400
    uint32_t t90 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    mem.w32(t90, 0x004dc130u);
    sub_004db400(ctx, mem);
    // 0x004dc130: lea edx, [ebx + 0x58]
    uint32_t t91 = static_cast<uint32_t>(ctx.ebx + 0x00000058u);
    ctx.edx = static_cast<uint32_t>(t91);
    // 0x004dc133: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004dc135: call 0x4dcbb0
    uint32_t t92 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    mem.w32(t92, 0x004dc13au);
    sub_004dcbb0(ctx, mem);
    // 0x004dc13a: mov esi, dword ptr [ebx + 0x48]
    uint32_t t93 = static_cast<uint32_t>(ctx.ebx + 0x00000048u);
    uint32_t t94 = mem.r32(t93);
    ctx.esi = static_cast<uint32_t>(t94);
    // 0x004dc13d: sub esp, 0x2c
    uint32_t t95 = static_cast<uint32_t>(ctx.esp - 0x0000002cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x0000002cu, t95);
    ctx.esp = static_cast<uint32_t>(t95);
    // 0x004dc140: mov ecx, esp
    ctx.ecx = static_cast<uint32_t>(ctx.esp);
    // 0x004dc142: mov dword ptr [esp + 0x44], esp
    uint32_t t96 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    mem.w32(t96, ctx.esp);
    // 0x004dc146: push ecx
    uint32_t t97 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t97);
    mem.w32(t97, ctx.ecx);
    // 0x004dc147: call 0x4db400
    uint32_t t98 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t98);
    mem.w32(t98, 0x004dc14cu);
    sub_004db400(ctx, mem);
    // 0x004dc14c: lea edx, [ebx + 0x68]
    uint32_t t99 = static_cast<uint32_t>(ctx.ebx + 0x00000068u);
    ctx.edx = static_cast<uint32_t>(t99);
    // 0x004dc14f: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004dc151: call 0x4dcbb0
    uint32_t t100 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t100);
    mem.w32(t100, 0x004dc156u);
    sub_004dcbb0(ctx, mem);
    // 0x004dc156: xor ebp, ebp
    uint32_t t101 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t101);
    ctx.ebp = static_cast<uint32_t>(t101);
    // 0x004dc158: mov dword ptr [esp + 0x18], ebp
    uint32_t t102 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t102, ctx.ebp);
    // 0x004dc15c: mov dword ptr [esp + 0x20], ebp
    uint32_t t103 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t103, ctx.ebp);
}
bb_004dc160: {
    // 0x004dc160: mov eax, dword ptr [ebx + 0x5c]
    uint32_t t104 = static_cast<uint32_t>(ctx.ebx + 0x0000005cu);
    uint32_t t105 = mem.r32(t104);
    ctx.eax = static_cast<uint32_t>(t105);
    // 0x004dc163: test eax, eax
    uint32_t t106 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t106);
    // 0x004dc165: lea esi, [ebx + 0x58]
    uint32_t t107 = static_cast<uint32_t>(ctx.ebx + 0x00000058u);
    ctx.esi = static_cast<uint32_t>(t107);
    // 0x004dc168: je 0x4dc39a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc39a;
    goto bb_004dc16e;
}
bb_004dc39a: {
    // 0x004dc39a: xor ebp, ebp
    uint32_t t108 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t108);
    ctx.ebp = static_cast<uint32_t>(t108);
    // 0x004dc39c: mov dword ptr [esp + 0x20], ebp
    uint32_t t109 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t109, ctx.ebp);
    // 0x004dc3a0: mov dword ptr [esp + 0x18], ebp
    uint32_t t110 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t110, ctx.ebp);
    goto bb_004dc3a4;
}
bb_004dc16e: {
    // 0x004dc16e: mov ecx, dword ptr [esi + 8]
    uint32_t t111 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t112 = mem.r32(t111);
    ctx.ecx = static_cast<uint32_t>(t112);
    // 0x004dc171: sub ecx, eax
    uint32_t t113 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t113);
    ctx.ecx = static_cast<uint32_t>(t113);
    // 0x004dc173: mov eax, 0x2e8ba2e9
    ctx.eax = static_cast<uint32_t>(0x2e8ba2e9u);
    // 0x004dc178: imul ecx
    uint64_t t114 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t115 = static_cast<uint32_t>(t114);
    uint32_t t116 = static_cast<uint32_t>(t114 >> 32);
    ctx.eax = static_cast<uint32_t>(t115);
    ctx.edx = static_cast<uint32_t>(t116);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t114);
    // 0x004dc17a: sar edx, 3
    uint32_t t117 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t118 = recomp_detail::sar<uint32_t>(ctx.edx, t117);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t117, t118);
    ctx.edx = static_cast<uint32_t>(t118);
    // 0x004dc17d: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004dc17f: shr eax, 0x1f
    uint32_t t119 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t120 = recomp_detail::shr<uint32_t>(ctx.eax, t119);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t119, t120);
    ctx.eax = static_cast<uint32_t>(t120);
    // 0x004dc182: add eax, edx
    uint32_t t121 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t121);
    ctx.eax = static_cast<uint32_t>(t121);
    // 0x004dc184: cmp ebp, eax
    uint32_t t122 = static_cast<uint32_t>(ctx.ebp - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebp, ctx.eax, t122);
    // 0x004dc186: jae 0x4dc39a
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004dc39a;
    goto bb_004dc18c;
}
bb_004dc3a4: {
    // 0x004dc3a4: mov eax, dword ptr [ebx + 0x6c]
    uint32_t t123 = static_cast<uint32_t>(ctx.ebx + 0x0000006cu);
    uint32_t t124 = mem.r32(t123);
    ctx.eax = static_cast<uint32_t>(t124);
    // 0x004dc3a7: test eax, eax
    uint32_t t125 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t125);
    // 0x004dc3a9: lea esi, [ebx + 0x68]
    uint32_t t126 = static_cast<uint32_t>(ctx.ebx + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t126);
    // 0x004dc3ac: je 0x4dc628
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc628;
    goto bb_004dc3b2;
}
bb_004dc18c: {
    // 0x004dc18c: mov eax, dword ptr [esi + 4]
    uint32_t t127 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t128 = mem.r32(t127);
    ctx.eax = static_cast<uint32_t>(t128);
    // 0x004dc18f: test eax, eax
    uint32_t t129 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t129);
    // 0x004dc191: je 0x4dc1ad
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc1ad;
    goto bb_004dc193;
}
bb_004dc628: {
    // 0x004dc628: test edi, edi
    uint32_t t130 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t130);
    // 0x004dc62a: je 0x4dc63c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc63c;
    goto bb_004dc62c;
}
bb_004dc3b2: {
    // 0x004dc3b2: mov ecx, dword ptr [esi + 8]
    uint32_t t131 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t132 = mem.r32(t131);
    ctx.ecx = static_cast<uint32_t>(t132);
    // 0x004dc3b5: sub ecx, eax
    uint32_t t133 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t133);
    ctx.ecx = static_cast<uint32_t>(t133);
    // 0x004dc3b7: mov eax, 0x2e8ba2e9
    ctx.eax = static_cast<uint32_t>(0x2e8ba2e9u);
    // 0x004dc3bc: imul ecx
    uint64_t t134 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t135 = static_cast<uint32_t>(t134);
    uint32_t t136 = static_cast<uint32_t>(t134 >> 32);
    ctx.eax = static_cast<uint32_t>(t135);
    ctx.edx = static_cast<uint32_t>(t136);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t134);
    // 0x004dc3be: sar edx, 3
    uint32_t t137 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t138 = recomp_detail::sar<uint32_t>(ctx.edx, t137);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t137, t138);
    ctx.edx = static_cast<uint32_t>(t138);
    // 0x004dc3c1: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004dc3c3: shr eax, 0x1f
    uint32_t t139 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t140 = recomp_detail::shr<uint32_t>(ctx.eax, t139);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t139, t140);
    ctx.eax = static_cast<uint32_t>(t140);
    // 0x004dc3c6: add eax, edx
    uint32_t t141 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t141);
    ctx.eax = static_cast<uint32_t>(t141);
    // 0x004dc3c8: cmp ebp, eax
    uint32_t t142 = static_cast<uint32_t>(ctx.ebp - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebp, ctx.eax, t142);
    // 0x004dc3ca: jae 0x4dc628
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004dc628;
    goto bb_004dc3d0;
}
bb_004dc1ad: {
    // 0x004dc1ad: call 0x4e0bf2
    uint32_t t143 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t143);
    mem.w32(t143, 0x004dc1b2u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004dc1b2;
}
bb_004dc193: {
    // 0x004dc193: mov ecx, dword ptr [esi + 8]
    uint32_t t144 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t145 = mem.r32(t144);
    ctx.ecx = static_cast<uint32_t>(t145);
    // 0x004dc196: sub ecx, eax
    uint32_t t146 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t146);
    ctx.ecx = static_cast<uint32_t>(t146);
    // 0x004dc198: mov eax, 0x2e8ba2e9
    ctx.eax = static_cast<uint32_t>(0x2e8ba2e9u);
    // 0x004dc19d: imul ecx
    uint64_t t147 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t148 = static_cast<uint32_t>(t147);
    uint32_t t149 = static_cast<uint32_t>(t147 >> 32);
    ctx.eax = static_cast<uint32_t>(t148);
    ctx.edx = static_cast<uint32_t>(t149);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t147);
    // 0x004dc19f: sar edx, 3
    uint32_t t150 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t151 = recomp_detail::sar<uint32_t>(ctx.edx, t150);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t150, t151);
    ctx.edx = static_cast<uint32_t>(t151);
    // 0x004dc1a2: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004dc1a4: shr eax, 0x1f
    uint32_t t152 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t153 = recomp_detail::shr<uint32_t>(ctx.eax, t152);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t152, t153);
    ctx.eax = static_cast<uint32_t>(t153);
    // 0x004dc1a7: add eax, edx
    uint32_t t154 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t154);
    ctx.eax = static_cast<uint32_t>(t154);
    // 0x004dc1a9: cmp ebp, eax
    uint32_t t155 = static_cast<uint32_t>(ctx.ebp - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebp, ctx.eax, t155);
    // 0x004dc1ab: jb 0x4dc1b2
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004dc1b2;
    goto bb_004dc1ad;
}
bb_004dc63c: {
    // 0x004dc63c: cmp dword ptr [esp + 0x3c], 0
    uint32_t t156 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    uint32_t t157 = mem.r32(t156);
    uint32_t t158 = static_cast<uint32_t>(t157 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t157, 0x00000000u, t158);
    // 0x004dc641: je 0x4dc650
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc650;
    goto bb_004dc643;
}
bb_004dc62c: {
    // 0x004dc62c: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004dc62e: call 0x414000
    uint32_t t159 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t159);
    mem.w32(t159, 0x004dc633u);
    sub_00414000(ctx, mem);
    // 0x004dc633: push edi
    uint32_t t160 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t160);
    mem.w32(t160, ctx.edi);
    // 0x004dc634: call 0x4e02f3
    uint32_t t161 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t161);
    mem.w32(t161, 0x004dc639u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dc639: add esp, 4
    uint32_t t162 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t162);
    ctx.esp = static_cast<uint32_t>(t162);
    goto bb_004dc63c;
}
bb_004dc3d0: {
    // 0x004dc3d0: mov eax, dword ptr [esi + 4]
    uint32_t t163 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t164 = mem.r32(t163);
    ctx.eax = static_cast<uint32_t>(t164);
    // 0x004dc3d3: test eax, eax
    uint32_t t165 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t165);
    // 0x004dc3d5: je 0x4dc3f1
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc3f1;
    goto bb_004dc3d7;
}
bb_004dc1b2: {
    // 0x004dc1b2: mov ebp, dword ptr [esi + 4]
    uint32_t t166 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t167 = mem.r32(t166);
    ctx.ebp = static_cast<uint32_t>(t167);
    // 0x004dc1b5: add ebp, dword ptr [esp + 0x20]
    uint32_t t168 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t169 = mem.r32(t168);
    uint32_t t170 = static_cast<uint32_t>(ctx.ebp + t169);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebp, t169, t170);
    ctx.ebp = static_cast<uint32_t>(t170);
    // 0x004dc1b9: test edi, edi
    uint32_t t171 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t171);
    // 0x004dc1bb: je 0x4dc22b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc22b;
    goto bb_004dc1bd;
}
bb_004dc650: {
    // 0x004dc650: mov eax, dword ptr [esp + 0x40]
    uint32_t t172 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t173 = mem.r32(t172);
    ctx.eax = static_cast<uint32_t>(t173);
    // 0x004dc654: lea edx, [eax + 1]
    uint32_t t174 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.edx = static_cast<uint32_t>(t174);
    goto bb_004dc657;
}
bb_004dc643: {
    // 0x004dc643: mov ecx, dword ptr [esp + 0x3c]
    uint32_t t175 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    uint32_t t176 = mem.r32(t175);
    ctx.ecx = static_cast<uint32_t>(t176);
    // 0x004dc647: push ecx
    uint32_t t177 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t177);
    mem.w32(t177, ctx.ecx);
    // 0x004dc648: call 0x4e0307
    uint32_t t178 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t178);
    mem.w32(t178, 0x004dc64du);
    hle_crt_004e0307(ctx, mem);
    // 0x004dc64d: add esp, 4
    uint32_t t179 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t179);
    ctx.esp = static_cast<uint32_t>(t179);
    goto bb_004dc650;
}
bb_004dc3f1: {
    // 0x004dc3f1: call 0x4e0bf2
    uint32_t t180 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t180);
    mem.w32(t180, 0x004dc3f6u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004dc3f6;
}
bb_004dc3d7: {
    // 0x004dc3d7: mov ecx, dword ptr [esi + 8]
    uint32_t t181 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t182 = mem.r32(t181);
    ctx.ecx = static_cast<uint32_t>(t182);
    // 0x004dc3da: sub ecx, eax
    uint32_t t183 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t183);
    ctx.ecx = static_cast<uint32_t>(t183);
    // 0x004dc3dc: mov eax, 0x2e8ba2e9
    ctx.eax = static_cast<uint32_t>(0x2e8ba2e9u);
    // 0x004dc3e1: imul ecx
    uint64_t t184 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t185 = static_cast<uint32_t>(t184);
    uint32_t t186 = static_cast<uint32_t>(t184 >> 32);
    ctx.eax = static_cast<uint32_t>(t185);
    ctx.edx = static_cast<uint32_t>(t186);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t184);
    // 0x004dc3e3: sar edx, 3
    uint32_t t187 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t188 = recomp_detail::sar<uint32_t>(ctx.edx, t187);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t187, t188);
    ctx.edx = static_cast<uint32_t>(t188);
    // 0x004dc3e6: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004dc3e8: shr eax, 0x1f
    uint32_t t189 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t190 = recomp_detail::shr<uint32_t>(ctx.eax, t189);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t189, t190);
    ctx.eax = static_cast<uint32_t>(t190);
    // 0x004dc3eb: add eax, edx
    uint32_t t191 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t191);
    ctx.eax = static_cast<uint32_t>(t191);
    // 0x004dc3ed: cmp ebp, eax
    uint32_t t192 = static_cast<uint32_t>(ctx.ebp - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebp, ctx.eax, t192);
    // 0x004dc3ef: jb 0x4dc3f6
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004dc3f6;
    goto bb_004dc3f1;
}
bb_004dc22b: {
    // 0x004dc22b: lea ebx, [esp + 0x17]
    uint32_t t193 = static_cast<uint32_t>(ctx.esp + 0x00000017u);
    ctx.ebx = static_cast<uint32_t>(t193);
    // 0x004dc22f: mov edi, 0x100
    ctx.edi = static_cast<uint32_t>(0x00000100u);
    // 0x004dc234: lea esi, [esp + 0x2c]
    uint32_t t194 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    ctx.esi = static_cast<uint32_t>(t194);
    // 0x004dc238: mov byte ptr [esp + 0x17], 0
    uint32_t t195 = static_cast<uint32_t>(ctx.esp + 0x00000017u);
    mem.w8(t195, uint8_t{0x00u});
    // 0x004dc23d: call 0x4c2180
    uint32_t t196 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t196);
    mem.w32(t196, 0x004dc242u);
    sub_004c2180(ctx, mem);
    // 0x004dc242: mov dword ptr [esp + 0x88], 0
    uint32_t t197 = static_cast<uint32_t>(ctx.esp + 0x00000088u);
    mem.w32(t197, 0x00000000u);
    // 0x004dc24d: mov ebx, dword ptr [esp + 0x30]
    uint32_t t198 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    uint32_t t199 = mem.r32(t198);
    ctx.ebx = static_cast<uint32_t>(t199);
    // 0x004dc251: test ebx, ebx
    uint32_t t200 = static_cast<uint32_t>(ctx.ebx & ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t200);
    // 0x004dc253: mov edi, dword ptr [esp + 0x34]
    uint32_t t201 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    uint32_t t202 = mem.r32(t201);
    ctx.edi = static_cast<uint32_t>(t202);
    // 0x004dc257: je 0x4dc25f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc25f;
    goto bb_004dc259;
}
bb_004dc1bd: {
    // 0x004dc1bd: mov esi, dword ptr [esp + 0x1c]
    uint32_t t203 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t204 = mem.r32(t203);
    ctx.esi = static_cast<uint32_t>(t204);
    // 0x004dc1c1: lea edx, [ebp + 0x24]
    uint32_t t205 = static_cast<uint32_t>(ctx.ebp + 0x00000024u);
    ctx.edx = static_cast<uint32_t>(t205);
    // 0x004dc1c4: mov edi, 4
    ctx.edi = static_cast<uint32_t>(0x00000004u);
    // 0x004dc1c9: push edx
    uint32_t t206 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t206);
    mem.w32(t206, ctx.edx);
    // 0x004dc1ca: mov ebx, edi
    ctx.ebx = static_cast<uint32_t>(ctx.edi);
    // 0x004dc1cc: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004dc1ce: call 0x413e70
    uint32_t t207 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t207);
    mem.w32(t207, 0x004dc1d3u);
    sub_00413e70(ctx, mem);
    // 0x004dc1d3: test eax, eax
    uint32_t t208 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t208);
    // 0x004dc1d5: je 0x4dc1e9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc1e9;
    goto bb_004dc1d7;
}
bb_004dc657: {
    // 0x004dc657: mov cl, byte ptr [eax]
    uint8_t t209 = mem.r8(ctx.eax);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t209));
    // 0x004dc659: add eax, 1
    uint32_t t210 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t210);
    ctx.eax = static_cast<uint32_t>(t210);
    // 0x004dc65c: test cl, cl
    uint8_t t211 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t211);
    // 0x004dc65e: jne 0x4dc657
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dc657;
    goto bb_004dc660;
}
bb_004dc3f6: {
    // 0x004dc3f6: mov ebp, dword ptr [esi + 4]
    uint32_t t212 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t213 = mem.r32(t212);
    ctx.ebp = static_cast<uint32_t>(t213);
    // 0x004dc3f9: add ebp, dword ptr [esp + 0x18]
    uint32_t t214 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t215 = mem.r32(t214);
    uint32_t t216 = static_cast<uint32_t>(ctx.ebp + t215);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebp, t215, t216);
    ctx.ebp = static_cast<uint32_t>(t216);
    // 0x004dc3fd: test edi, edi
    uint32_t t217 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t217);
    // 0x004dc3ff: je 0x4dc46f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc46f;
    goto bb_004dc401;
}
bb_004dc25f: {
    // 0x004dc25f: call 0x4e0bf2
    uint32_t t218 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t218);
    mem.w32(t218, 0x004dc264u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004dc264;
}
bb_004dc259: {
    // 0x004dc259: mov edx, edi
    ctx.edx = static_cast<uint32_t>(ctx.edi);
    // 0x004dc25b: sub edx, ebx
    uint32_t t219 = static_cast<uint32_t>(ctx.edx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ebx, t219);
    ctx.edx = static_cast<uint32_t>(t219);
    // 0x004dc25d: jne 0x4dc264
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dc264;
    goto bb_004dc25f;
}
bb_004dc1e9: {
    // 0x004dc1e9: lea eax, [ebp + 0x20]
    uint32_t t220 = static_cast<uint32_t>(ctx.ebp + 0x00000020u);
    ctx.eax = static_cast<uint32_t>(t220);
    // 0x004dc1ec: push eax
    uint32_t t221 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t221);
    mem.w32(t221, ctx.eax);
    // 0x004dc1ed: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004dc1ef: call 0x413e70
    uint32_t t222 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t222);
    mem.w32(t222, 0x004dc1f4u);
    sub_00413e70(ctx, mem);
    // 0x004dc1f4: test eax, eax
    uint32_t t223 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t223);
    // 0x004dc1f6: je 0x4dc20a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc20a;
    goto bb_004dc1f8;
}
bb_004dc1d7: {
    // 0x004dc1d7: mov eax, dword ptr [esi + 0x3c]
    uint32_t t224 = static_cast<uint32_t>(ctx.esi + 0x0000003cu);
    uint32_t t225 = mem.r32(t224);
    ctx.eax = static_cast<uint32_t>(t225);
    // 0x004dc1da: test eax, eax
    uint32_t t226 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t226);
    // 0x004dc1dc: je 0x4dc1e9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc1e9;
    goto bb_004dc1de;
}
bb_004dc660: {
    // 0x004dc660: sub eax, edx
    uint32_t t227 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t227);
    ctx.eax = static_cast<uint32_t>(t227);
    // 0x004dc662: mov edx, dword ptr [esp + 0x40]
    uint32_t t228 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t229 = mem.r32(t228);
    ctx.edx = static_cast<uint32_t>(t229);
    // 0x004dc666: push eax
    uint32_t t230 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t230);
    mem.w32(t230, ctx.eax);
    // 0x004dc667: push edx
    uint32_t t231 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t231);
    mem.w32(t231, ctx.edx);
    // 0x004dc668: lea ecx, [ebx + 8]
    uint32_t t232 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    ctx.ecx = static_cast<uint32_t>(t232);
    // 0x004dc66b: call 0x407c10
    uint32_t t233 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t233);
    mem.w32(t233, 0x004dc670u);
    sub_00407c10(ctx, mem);
    // 0x004dc670: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x004dc675: mov dword ptr [ebx + 4], eax
    uint32_t t234 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    mem.w32(t234, ctx.eax);
    goto bb_004dc678;
}
bb_004dc46f: {
    // 0x004dc46f: lea ebx, [esp + 0x17]
    uint32_t t235 = static_cast<uint32_t>(ctx.esp + 0x00000017u);
    ctx.ebx = static_cast<uint32_t>(t235);
    // 0x004dc473: mov edi, 0x20
    ctx.edi = static_cast<uint32_t>(0x00000020u);
    // 0x004dc478: lea esi, [esp + 0x2c]
    uint32_t t236 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    ctx.esi = static_cast<uint32_t>(t236);
    // 0x004dc47c: mov byte ptr [esp + 0x17], 0
    uint32_t t237 = static_cast<uint32_t>(ctx.esp + 0x00000017u);
    mem.w8(t237, uint8_t{0x00u});
    // 0x004dc481: call 0x4c2180
    uint32_t t238 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t238);
    mem.w32(t238, 0x004dc486u);
    sub_004c2180(ctx, mem);
    // 0x004dc486: mov dword ptr [esp + 0x88], 3
    uint32_t t239 = static_cast<uint32_t>(ctx.esp + 0x00000088u);
    mem.w32(t239, 0x00000003u);
    // 0x004dc491: mov esi, dword ptr [esp + 0x30]
    uint32_t t240 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    uint32_t t241 = mem.r32(t240);
    ctx.esi = static_cast<uint32_t>(t241);
    // 0x004dc495: xor ebx, ebx
    uint32_t t242 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t242);
    ctx.ebx = static_cast<uint32_t>(t242);
    // 0x004dc497: cmp esi, ebx
    uint32_t t243 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t243);
    // 0x004dc499: je 0x4dc4a3
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc4a3;
    goto bb_004dc49b;
}
bb_004dc401: {
    // 0x004dc401: mov esi, dword ptr [esp + 0x1c]
    uint32_t t244 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t245 = mem.r32(t244);
    ctx.esi = static_cast<uint32_t>(t245);
    // 0x004dc405: lea ecx, [ebp + 0x24]
    uint32_t t246 = static_cast<uint32_t>(ctx.ebp + 0x00000024u);
    ctx.ecx = static_cast<uint32_t>(t246);
    // 0x004dc408: mov edi, 4
    ctx.edi = static_cast<uint32_t>(0x00000004u);
    // 0x004dc40d: push ecx
    uint32_t t247 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t247);
    mem.w32(t247, ctx.ecx);
    // 0x004dc40e: mov ebx, edi
    ctx.ebx = static_cast<uint32_t>(ctx.edi);
    // 0x004dc410: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004dc412: call 0x413e70
    uint32_t t248 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t248);
    mem.w32(t248, 0x004dc417u);
    sub_00413e70(ctx, mem);
    // 0x004dc417: test eax, eax
    uint32_t t249 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t249);
    // 0x004dc419: je 0x4dc42d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc42d;
    goto bb_004dc41b;
}
bb_004dc264: {
    // 0x004dc264: mov ecx, dword ptr [esp + 0x1c]
    uint32_t t250 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t251 = mem.r32(t250);
    ctx.ecx = static_cast<uint32_t>(t251);
    // 0x004dc268: test ecx, ecx
    uint32_t t252 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t252);
    // 0x004dc26a: je 0x4dc27c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc27c;
    goto bb_004dc26c;
}
bb_004dc20a: {
    // 0x004dc20a: lea ecx, [ebp + 0x28]
    uint32_t t253 = static_cast<uint32_t>(ctx.ebp + 0x00000028u);
    ctx.ecx = static_cast<uint32_t>(t253);
    // 0x004dc20d: push ecx
    uint32_t t254 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t254);
    mem.w32(t254, ctx.ecx);
    // 0x004dc20e: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004dc210: call 0x413e70
    uint32_t t255 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t255);
    mem.w32(t255, 0x004dc215u);
    sub_00413e70(ctx, mem);
    // 0x004dc215: test eax, eax
    uint32_t t256 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t256);
    // 0x004dc217: je 0x4dc22b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc22b;
    goto bb_004dc219;
}
bb_004dc1f8: {
    // 0x004dc1f8: mov eax, dword ptr [esi + 0x3c]
    uint32_t t257 = static_cast<uint32_t>(ctx.esi + 0x0000003cu);
    uint32_t t258 = mem.r32(t257);
    ctx.eax = static_cast<uint32_t>(t258);
    // 0x004dc1fb: test eax, eax
    uint32_t t259 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t259);
    // 0x004dc1fd: je 0x4dc20a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc20a;
    goto bb_004dc1ff;
}
bb_004dc1de: {
    // 0x004dc1de: push 0
    uint32_t t260 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t260);
    mem.w32(t260, 0x00000000u);
    // 0x004dc1e0: push -1
    uint32_t t261 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t261);
    mem.w32(t261, 0xffffffffu);
    // 0x004dc1e2: push eax
    uint32_t t262 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t262);
    mem.w32(t262, ctx.eax);
    // 0x004dc1e3: call dword ptr [0x51b1c4]
    uint32_t t263 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t263);
    mem.w32(t263, 0x004dc1e9u);
    hle_iat_call(ctx, mem, 0x0051b1c4u);
    goto bb_004dc1e9;
}
bb_004dc4a3: {
    // 0x004dc4a3: call 0x4e0bf2
    uint32_t t264 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t264);
    mem.w32(t264, 0x004dc4a8u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004dc4a8;
}
bb_004dc49b: {
    // 0x004dc49b: mov ecx, dword ptr [esp + 0x34]
    uint32_t t265 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    uint32_t t266 = mem.r32(t265);
    ctx.ecx = static_cast<uint32_t>(t266);
    // 0x004dc49f: sub ecx, esi
    uint32_t t267 = static_cast<uint32_t>(ctx.ecx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.esi, t267);
    ctx.ecx = static_cast<uint32_t>(t267);
    // 0x004dc4a1: jne 0x4dc4a8
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dc4a8;
    goto bb_004dc4a3;
}
bb_004dc42d: {
    // 0x004dc42d: lea edx, [ebp + 0x20]
    uint32_t t268 = static_cast<uint32_t>(ctx.ebp + 0x00000020u);
    ctx.edx = static_cast<uint32_t>(t268);
    // 0x004dc430: push edx
    uint32_t t269 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t269);
    mem.w32(t269, ctx.edx);
    // 0x004dc431: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004dc433: call 0x413e70
    uint32_t t270 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t270);
    mem.w32(t270, 0x004dc438u);
    sub_00413e70(ctx, mem);
    // 0x004dc438: test eax, eax
    uint32_t t271 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t271);
    // 0x004dc43a: je 0x4dc44e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc44e;
    goto bb_004dc43c;
}
bb_004dc41b: {
    // 0x004dc41b: mov eax, dword ptr [esi + 0x3c]
    uint32_t t272 = static_cast<uint32_t>(ctx.esi + 0x0000003cu);
    uint32_t t273 = mem.r32(t272);
    ctx.eax = static_cast<uint32_t>(t273);
    // 0x004dc41e: test eax, eax
    uint32_t t274 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t274);
    // 0x004dc420: je 0x4dc42d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc42d;
    goto bb_004dc422;
}
bb_004dc27c: {
    // 0x004dc27c: test ebx, ebx
    uint32_t t275 = static_cast<uint32_t>(ctx.ebx & ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t275);
    // 0x004dc27e: je 0x4dc286
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc286;
    goto bb_004dc280;
}
bb_004dc26c: {
    // 0x004dc26c: push 0x100
    uint32_t t276 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t276);
    mem.w32(t276, 0x00000100u);
    // 0x004dc271: push 0x100
    uint32_t t277 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t277);
    mem.w32(t277, 0x00000100u);
    // 0x004dc276: push ebx
    uint32_t t278 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t278);
    mem.w32(t278, ctx.ebx);
    // 0x004dc277: call 0x413fb0
    uint32_t t279 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t279);
    mem.w32(t279, 0x004dc27cu);
    sub_00413fb0(ctx, mem);
    goto bb_004dc27c;
}
bb_004dc219: {
    // 0x004dc219: mov esi, dword ptr [esi + 0x3c]
    uint32_t t280 = static_cast<uint32_t>(ctx.esi + 0x0000003cu);
    uint32_t t281 = mem.r32(t280);
    ctx.esi = static_cast<uint32_t>(t281);
    // 0x004dc21c: test esi, esi
    uint32_t t282 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t282);
    // 0x004dc21e: je 0x4dc22b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc22b;
    goto bb_004dc220;
}
bb_004dc1ff: {
    // 0x004dc1ff: push 0
    uint32_t t283 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t283);
    mem.w32(t283, 0x00000000u);
    // 0x004dc201: push -1
    uint32_t t284 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t284);
    mem.w32(t284, 0xffffffffu);
    // 0x004dc203: push eax
    uint32_t t285 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t285);
    mem.w32(t285, ctx.eax);
    // 0x004dc204: call dword ptr [0x51b1c4]
    uint32_t t286 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t286);
    mem.w32(t286, 0x004dc20au);
    hle_iat_call(ctx, mem, 0x0051b1c4u);
    goto bb_004dc20a;
}
bb_004dc4a8: {
    // 0x004dc4a8: cmp dword ptr [esp + 0x1c], ebx
    uint32_t t287 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t288 = mem.r32(t287);
    uint32_t t289 = static_cast<uint32_t>(t288 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t288, ctx.ebx, t289);
    // 0x004dc4ac: je 0x4dc4db
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc4db;
    goto bb_004dc4ae;
}
bb_004dc44e: {
    // 0x004dc44e: lea eax, [ebp + 0x28]
    uint32_t t290 = static_cast<uint32_t>(ctx.ebp + 0x00000028u);
    ctx.eax = static_cast<uint32_t>(t290);
    // 0x004dc451: push eax
    uint32_t t291 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t291);
    mem.w32(t291, ctx.eax);
    // 0x004dc452: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004dc454: call 0x413e70
    uint32_t t292 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t292);
    mem.w32(t292, 0x004dc459u);
    sub_00413e70(ctx, mem);
    // 0x004dc459: test eax, eax
    uint32_t t293 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t293);
    // 0x004dc45b: je 0x4dc46f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc46f;
    goto bb_004dc45d;
}
bb_004dc43c: {
    // 0x004dc43c: mov eax, dword ptr [esi + 0x3c]
    uint32_t t294 = static_cast<uint32_t>(ctx.esi + 0x0000003cu);
    uint32_t t295 = mem.r32(t294);
    ctx.eax = static_cast<uint32_t>(t295);
    // 0x004dc43f: test eax, eax
    uint32_t t296 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t296);
    // 0x004dc441: je 0x4dc44e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc44e;
    goto bb_004dc443;
}
bb_004dc422: {
    // 0x004dc422: push 0
    uint32_t t297 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t297);
    mem.w32(t297, 0x00000000u);
    // 0x004dc424: push -1
    uint32_t t298 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t298);
    mem.w32(t298, 0xffffffffu);
    // 0x004dc426: push eax
    uint32_t t299 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t299);
    mem.w32(t299, ctx.eax);
    // 0x004dc427: call dword ptr [0x51b1c4]
    uint32_t t300 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t300);
    mem.w32(t300, 0x004dc42du);
    hle_iat_call(ctx, mem, 0x0051b1c4u);
    goto bb_004dc42d;
}
bb_004dc286: {
    // 0x004dc286: call 0x4e0bf2
    uint32_t t301 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t301);
    mem.w32(t301, 0x004dc28bu);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004dc28b;
}
bb_004dc280: {
    // 0x004dc280: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x004dc282: sub eax, ebx
    uint32_t t302 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t302);
    ctx.eax = static_cast<uint32_t>(t302);
    // 0x004dc284: jne 0x4dc28b
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dc28b;
    goto bb_004dc286;
}
bb_004dc220: {
    // 0x004dc220: push 0
    uint32_t t303 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t303);
    mem.w32(t303, 0x00000000u);
    // 0x004dc222: push -1
    uint32_t t304 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t304);
    mem.w32(t304, 0xffffffffu);
    // 0x004dc224: push esi
    uint32_t t305 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t305);
    mem.w32(t305, ctx.esi);
    // 0x004dc225: call dword ptr [0x51b1c4]
    uint32_t t306 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t306);
    mem.w32(t306, 0x004dc22bu);
    hle_iat_call(ctx, mem, 0x0051b1c4u);
    goto bb_004dc22b;
}
bb_004dc4db: {
    // 0x004dc4db: cmp esi, ebx
    uint32_t t307 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t307);
    // 0x004dc4dd: mov edi, dword ptr [esp + 0x34]
    uint32_t t308 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    uint32_t t309 = mem.r32(t308);
    ctx.edi = static_cast<uint32_t>(t309);
    // 0x004dc4e1: je 0x4dc4e9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc4e9;
    goto bb_004dc4e3;
}
bb_004dc4ae: {
    // 0x004dc4ae: mov eax, dword ptr [esp + 0x1c]
    uint32_t t310 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t311 = mem.r32(t310);
    ctx.eax = static_cast<uint32_t>(t311);
    // 0x004dc4b2: mov edi, 0x20
    ctx.edi = static_cast<uint32_t>(0x00000020u);
    // 0x004dc4b7: push esi
    uint32_t t312 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t312);
    mem.w32(t312, ctx.esi);
    // 0x004dc4b8: mov ebx, edi
    ctx.ebx = static_cast<uint32_t>(ctx.edi);
    // 0x004dc4ba: call 0x413e70
    uint32_t t313 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t313);
    mem.w32(t313, 0x004dc4bfu);
    sub_00413e70(ctx, mem);
    // 0x004dc4bf: test eax, eax
    uint32_t t314 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t314);
    // 0x004dc4c1: je 0x4dc4d9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc4d9;
    goto bb_004dc4c3;
}
bb_004dc45d: {
    // 0x004dc45d: mov esi, dword ptr [esi + 0x3c]
    uint32_t t315 = static_cast<uint32_t>(ctx.esi + 0x0000003cu);
    uint32_t t316 = mem.r32(t315);
    ctx.esi = static_cast<uint32_t>(t316);
    // 0x004dc460: test esi, esi
    uint32_t t317 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t317);
    // 0x004dc462: je 0x4dc46f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc46f;
    goto bb_004dc464;
}
bb_004dc443: {
    // 0x004dc443: push 0
    uint32_t t318 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t318);
    mem.w32(t318, 0x00000000u);
    // 0x004dc445: push -1
    uint32_t t319 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t319);
    mem.w32(t319, 0xffffffffu);
    // 0x004dc447: push eax
    uint32_t t320 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t320);
    mem.w32(t320, ctx.eax);
    // 0x004dc448: call dword ptr [0x51b1c4]
    uint32_t t321 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t321);
    mem.w32(t321, 0x004dc44eu);
    hle_iat_call(ctx, mem, 0x0051b1c4u);
    goto bb_004dc44e;
}
bb_004dc28b: {
    // 0x004dc28b: mov eax, dword ptr [esp + 0x28]
    uint32_t t322 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t323 = mem.r32(t322);
    ctx.eax = static_cast<uint32_t>(t323);
    // 0x004dc28f: mov dl, byte ptr [ebp + 0x28]
    uint32_t t324 = static_cast<uint32_t>(ctx.ebp + 0x00000028u);
    uint8_t t325 = mem.r8(t324);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t325));
    // 0x004dc292: add eax, 0x24
    uint32_t t326 = static_cast<uint32_t>(ctx.eax + 0x00000024u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000024u, t326);
    ctx.eax = static_cast<uint32_t>(t326);
    // 0x004dc295: push eax
    uint32_t t327 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t327);
    mem.w32(t327, ctx.eax);
    // 0x004dc296: mov esi, 0x100
    ctx.esi = static_cast<uint32_t>(0x00000100u);
    // 0x004dc29b: mov ecx, ebx
    ctx.ecx = static_cast<uint32_t>(ctx.ebx);
    // 0x004dc29d: call 0x4db530
    uint32_t t328 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t328);
    mem.w32(t328, 0x004dc2a2u);
    sub_004db530(ctx, mem);
    // 0x004dc2a2: test ebx, ebx
    uint32_t t329 = static_cast<uint32_t>(ctx.ebx & ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t329);
    // 0x004dc2a4: je 0x4dc2aa
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc2aa;
    goto bb_004dc2a6;
}
bb_004dc4e9: {
    // 0x004dc4e9: call 0x4e0bf2
    uint32_t t330 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t330);
    mem.w32(t330, 0x004dc4eeu);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004dc4ee;
}
bb_004dc4e3: {
    // 0x004dc4e3: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x004dc4e5: sub eax, esi
    uint32_t t331 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t331);
    ctx.eax = static_cast<uint32_t>(t331);
    // 0x004dc4e7: jne 0x4dc4ee
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dc4ee;
    goto bb_004dc4e9;
}
bb_004dc4d9: {
    // 0x004dc4d9: xor ebx, ebx
    uint32_t t332 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t332);
    ctx.ebx = static_cast<uint32_t>(t332);
    goto bb_004dc4db;
}
bb_004dc4c3: {
    // 0x004dc4c3: mov edx, dword ptr [esp + 0x1c]
    uint32_t t333 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t334 = mem.r32(t333);
    ctx.edx = static_cast<uint32_t>(t334);
    // 0x004dc4c7: mov eax, dword ptr [edx + 0x3c]
    uint32_t t335 = static_cast<uint32_t>(ctx.edx + 0x0000003cu);
    uint32_t t336 = mem.r32(t335);
    ctx.eax = static_cast<uint32_t>(t336);
    // 0x004dc4ca: test eax, eax
    uint32_t t337 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t337);
    // 0x004dc4cc: je 0x4dc4d9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc4d9;
    goto bb_004dc4ce;
}
bb_004dc464: {
    // 0x004dc464: push 0
    uint32_t t338 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t338);
    mem.w32(t338, 0x00000000u);
    // 0x004dc466: push -1
    uint32_t t339 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t339);
    mem.w32(t339, 0xffffffffu);
    // 0x004dc468: push esi
    uint32_t t340 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t340);
    mem.w32(t340, ctx.esi);
    // 0x004dc469: call dword ptr [0x51b1c4]
    uint32_t t341 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t341);
    mem.w32(t341, 0x004dc46fu);
    hle_iat_call(ctx, mem, 0x0051b1c4u);
    goto bb_004dc46f;
}
bb_004dc2aa: {
    // 0x004dc2aa: call 0x4e0bf2
    uint32_t t342 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t342);
    mem.w32(t342, 0x004dc2afu);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004dc2af;
}
bb_004dc2a6: {
    // 0x004dc2a6: sub edi, ebx
    uint32_t t343 = static_cast<uint32_t>(ctx.edi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebx, t343);
    ctx.edi = static_cast<uint32_t>(t343);
    // 0x004dc2a8: jne 0x4dc2af
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dc2af;
    goto bb_004dc2aa;
}
bb_004dc4ee: {
    // 0x004dc4ee: mov eax, dword ptr [esp + 0x28]
    uint32_t t344 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t345 = mem.r32(t344);
    ctx.eax = static_cast<uint32_t>(t345);
    // 0x004dc4f2: mov cl, byte ptr [ebp + 0x28]
    uint32_t t346 = static_cast<uint32_t>(ctx.ebp + 0x00000028u);
    uint8_t t347 = mem.r8(t346);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t347));
    // 0x004dc4f5: add eax, 0x24
    uint32_t t348 = static_cast<uint32_t>(ctx.eax + 0x00000024u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000024u, t348);
    ctx.eax = static_cast<uint32_t>(t348);
    // 0x004dc4f8: mov eax, dword ptr [eax + 0x14]
    uint32_t t349 = static_cast<uint32_t>(ctx.eax + 0x00000014u);
    uint32_t t350 = mem.r32(t349);
    ctx.eax = static_cast<uint32_t>(t350);
    // 0x004dc4fb: cmp eax, ebx
    uint32_t t351 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t351);
    // 0x004dc4fd: je 0x4dc530
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc530;
    goto bb_004dc4ff;
}
bb_004dc4ce: {
    // 0x004dc4ce: push 0
    uint32_t t352 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t352);
    mem.w32(t352, 0x00000000u);
    // 0x004dc4d0: push -1
    uint32_t t353 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t353);
    mem.w32(t353, 0xffffffffu);
    // 0x004dc4d2: push eax
    uint32_t t354 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t354);
    mem.w32(t354, ctx.eax);
    // 0x004dc4d3: call dword ptr [0x51b1c4]
    uint32_t t355 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t355);
    mem.w32(t355, 0x004dc4d9u);
    hle_iat_call(ctx, mem, 0x0051b1c4u);
    goto bb_004dc4d9;
}
bb_004dc2af: {
    // 0x004dc2af: mov edi, 0xf
    ctx.edi = static_cast<uint32_t>(0x0000000fu);
    // 0x004dc2b4: mov eax, ebx
    ctx.eax = static_cast<uint32_t>(ctx.ebx);
    // 0x004dc2b6: mov dword ptr [esp + 0x78], edi
    uint32_t t356 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    mem.w32(t356, ctx.edi);
    // 0x004dc2ba: mov dword ptr [esp + 0x74], 0
    uint32_t t357 = static_cast<uint32_t>(ctx.esp + 0x00000074u);
    mem.w32(t357, 0x00000000u);
    // 0x004dc2c2: mov byte ptr [esp + 0x64], 0
    uint32_t t358 = static_cast<uint32_t>(ctx.esp + 0x00000064u);
    mem.w8(t358, uint8_t{0x00u});
    // 0x004dc2c7: lea esi, [eax + 1]
    uint32_t t359 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.esi = static_cast<uint32_t>(t359);
    // 0x004dc2ca: lea ebx, [ebx]
    ctx.ebx = static_cast<uint32_t>(ctx.ebx);
    goto bb_004dc2d0;
}
bb_004dc530: {
    // 0x004dc530: cmp esi, ebx
    uint32_t t360 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t360);
    // 0x004dc532: je 0x4dc538
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc538;
    goto bb_004dc534;
}
bb_004dc4ff: {
    // 0x004dc4ff: cmp cl, bl
    uint8_t t361 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) - static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.ecx), recomp_detail::r8l(ctx.ebx), t361);
    // 0x004dc501: mov dword ptr [esp + 0x70], 0x20
    uint32_t t362 = static_cast<uint32_t>(ctx.esp + 0x00000070u);
    mem.w32(t362, 0x00000020u);
    // 0x004dc509: mov dword ptr [esp + 0x60], eax
    uint32_t t363 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    mem.w32(t363, ctx.eax);
    // 0x004dc50d: mov byte ptr [esp + 0x64], 1
    uint32_t t364 = static_cast<uint32_t>(ctx.esp + 0x00000064u);
    mem.w8(t364, uint8_t{0x01u});
    // 0x004dc512: je 0x4dc518
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc518;
    goto bb_004dc514;
}
bb_004dc2d0: {
    // 0x004dc2d0: mov cl, byte ptr [eax]
    uint8_t t365 = mem.r8(ctx.eax);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t365));
    // 0x004dc2d2: add eax, 1
    uint32_t t366 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t366);
    ctx.eax = static_cast<uint32_t>(t366);
    // 0x004dc2d5: test cl, cl
    uint8_t t367 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t367);
    // 0x004dc2d7: jne 0x4dc2d0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dc2d0;
    goto bb_004dc2d9;
}
bb_004dc538: {
    // 0x004dc538: call 0x4e0bf2
    uint32_t t368 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t368);
    mem.w32(t368, 0x004dc53du);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004dc53d;
}
bb_004dc534: {
    // 0x004dc534: sub edi, esi
    uint32_t t369 = static_cast<uint32_t>(ctx.edi - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.esi, t369);
    ctx.edi = static_cast<uint32_t>(t369);
    // 0x004dc536: jne 0x4dc53d
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dc53d;
    goto bb_004dc538;
}
bb_004dc518: {
    // 0x004dc518: push 0x20
    uint32_t t370 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t370);
    mem.w32(t370, 0x00000020u);
    // 0x004dc51a: mov dword ptr [esp + 0x6a], eax
    uint32_t t371 = static_cast<uint32_t>(ctx.esp + 0x0000006au);
    mem.w32(t371, ctx.eax);
    // 0x004dc51e: push esi
    uint32_t t372 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t372);
    mem.w32(t372, ctx.esi);
    // 0x004dc51f: lea eax, [esp + 0x68]
    uint32_t t373 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.eax = static_cast<uint32_t>(t373);
    // 0x004dc523: mov dword ptr [esp + 0x74], ebx
    uint32_t t374 = static_cast<uint32_t>(ctx.esp + 0x00000074u);
    mem.w32(t374, ctx.ebx);
    // 0x004dc527: mov byte ptr [esp + 0x6d], bl
    uint32_t t375 = static_cast<uint32_t>(ctx.esp + 0x0000006du);
    mem.w8(t375, recomp_detail::r8l(ctx.ebx));
    // 0x004dc52b: call 0x4db5e0
    uint32_t t376 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t376);
    mem.w32(t376, 0x004dc530u);
    sub_004db5e0(ctx, mem);
    goto bb_004dc530;
}
bb_004dc514: {
    // 0x004dc514: mov byte ptr [esp + 0x64], cl
    uint32_t t377 = static_cast<uint32_t>(ctx.esp + 0x00000064u);
    mem.w8(t377, recomp_detail::r8l(ctx.ecx));
    goto bb_004dc518;
}
bb_004dc2d9: {
    // 0x004dc2d9: sub eax, esi
    uint32_t t378 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t378);
    ctx.eax = static_cast<uint32_t>(t378);
    // 0x004dc2db: push eax
    uint32_t t379 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t379);
    mem.w32(t379, ctx.eax);
    // 0x004dc2dc: push ebx
    uint32_t t380 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t380);
    mem.w32(t380, ctx.ebx);
    // 0x004dc2dd: lea ecx, [esp + 0x68]
    uint32_t t381 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.ecx = static_cast<uint32_t>(t381);
    // 0x004dc2e1: call 0x407c10
    uint32_t t382 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t382);
    mem.w32(t382, 0x004dc2e6u);
    sub_00407c10(ctx, mem);
    // 0x004dc2e6: lea ecx, [esp + 0x60]
    uint32_t t383 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    ctx.ecx = static_cast<uint32_t>(t383);
    // 0x004dc2ea: push ecx
    uint32_t t384 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t384);
    mem.w32(t384, ctx.ecx);
    // 0x004dc2eb: lea ecx, [esp + 0x48]
    uint32_t t385 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    ctx.ecx = static_cast<uint32_t>(t385);
    // 0x004dc2ef: mov byte ptr [esp + 0x8c], 1
    uint32_t t386 = static_cast<uint32_t>(ctx.esp + 0x0000008cu);
    mem.w8(t386, uint8_t{0x01u});
    // 0x004dc2f7: call 0x4c1f60
    uint32_t t387 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t387);
    mem.w32(t387, 0x004dc2fcu);
    sub_004c1f60(ctx, mem);
    // 0x004dc2fc: add esp, 4
    uint32_t t388 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t388);
    ctx.esp = static_cast<uint32_t>(t388);
    // 0x004dc2ff: push -1
    uint32_t t389 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t389);
    mem.w32(t389, 0xffffffffu);
    // 0x004dc301: push 0
    uint32_t t390 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t390);
    mem.w32(t390, 0x00000000u);
    // 0x004dc303: push eax
    uint32_t t391 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t391);
    mem.w32(t391, ctx.eax);
    // 0x004dc304: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x004dc306: mov byte ptr [esp + 0x94], 2
    uint32_t t392 = static_cast<uint32_t>(ctx.esp + 0x00000094u);
    mem.w8(t392, uint8_t{0x02u});
    // 0x004dc30e: call 0x4079d0
    uint32_t t393 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t393);
    mem.w32(t393, 0x004dc313u);
    sub_004079d0(ctx, mem);
    // 0x004dc313: mov esi, 0x10
    ctx.esi = static_cast<uint32_t>(0x00000010u);
    // 0x004dc318: cmp dword ptr [esp + 0x5c], esi
    uint32_t t394 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    uint32_t t395 = mem.r32(t394);
    uint32_t t396 = static_cast<uint32_t>(t395 - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t395, ctx.esi, t396);
    // 0x004dc31c: jb 0x4dc32b
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004dc32b;
    goto bb_004dc31e;
}
bb_004dc53d: {
    // 0x004dc53d: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004dc53f: mov dword ptr [esp + 0x78], 0xf
    uint32_t t397 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    mem.w32(t397, 0x0000000fu);
    // 0x004dc547: mov dword ptr [esp + 0x74], ebx
    uint32_t t398 = static_cast<uint32_t>(ctx.esp + 0x00000074u);
    mem.w32(t398, ctx.ebx);
    // 0x004dc54b: mov byte ptr [esp + 0x64], bl
    uint32_t t399 = static_cast<uint32_t>(ctx.esp + 0x00000064u);
    mem.w8(t399, recomp_detail::r8l(ctx.ebx));
    // 0x004dc54f: lea edi, [eax + 1]
    uint32_t t400 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.edi = static_cast<uint32_t>(t400);
    goto bb_004dc552;
}
bb_004dc32b: {
    // 0x004dc32b: cmp dword ptr [esp + 0x78], esi
    uint32_t t401 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    uint32_t t402 = mem.r32(t401);
    uint32_t t403 = static_cast<uint32_t>(t402 - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t402, ctx.esi, t403);
    // 0x004dc32f: mov dword ptr [esp + 0x5c], edi
    uint32_t t404 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    mem.w32(t404, ctx.edi);
    // 0x004dc333: mov dword ptr [esp + 0x58], 0
    uint32_t t405 = static_cast<uint32_t>(ctx.esp + 0x00000058u);
    mem.w32(t405, 0x00000000u);
    // 0x004dc33b: mov byte ptr [esp + 0x48], 0
    uint32_t t406 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    mem.w8(t406, uint8_t{0x00u});
    // 0x004dc340: jb 0x4dc34f
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004dc34f;
    goto bb_004dc342;
}
bb_004dc31e: {
    // 0x004dc31e: mov edx, dword ptr [esp + 0x48]
    uint32_t t407 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    uint32_t t408 = mem.r32(t407);
    ctx.edx = static_cast<uint32_t>(t408);
    // 0x004dc322: push edx
    uint32_t t409 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t409);
    mem.w32(t409, ctx.edx);
    // 0x004dc323: call 0x4e02f3
    uint32_t t410 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t410);
    mem.w32(t410, 0x004dc328u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dc328: add esp, 4
    uint32_t t411 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t411);
    ctx.esp = static_cast<uint32_t>(t411);
    goto bb_004dc32b;
}
bb_004dc552: {
    // 0x004dc552: mov cl, byte ptr [eax]
    uint8_t t412 = mem.r8(ctx.eax);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t412));
    // 0x004dc554: add eax, 1
    uint32_t t413 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t413);
    ctx.eax = static_cast<uint32_t>(t413);
    // 0x004dc557: cmp cl, bl
    uint8_t t414 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) - static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.ecx), recomp_detail::r8l(ctx.ebx), t414);
    // 0x004dc559: jne 0x4dc552
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dc552;
    goto bb_004dc55b;
}
bb_004dc34f: {
    // 0x004dc34f: mov edi, ebp
    ctx.edi = static_cast<uint32_t>(ctx.ebp);
    // 0x004dc351: call 0x4db470
    uint32_t t415 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t415);
    mem.w32(t415, 0x004dc356u);
    sub_004db470(ctx, mem);
    // 0x004dc356: xor esi, esi
    uint32_t t416 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t416);
    ctx.esi = static_cast<uint32_t>(t416);
    // 0x004dc358: cmp ebx, esi
    uint32_t t417 = static_cast<uint32_t>(ctx.ebx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.esi, t417);
    // 0x004dc35a: mov dword ptr [ebp + 0x1c], eax
    uint32_t t418 = static_cast<uint32_t>(ctx.ebp + 0x0000001cu);
    mem.w32(t418, ctx.eax);
    // 0x004dc35d: mov dword ptr [esp + 0x88], 0xffffffff
    uint32_t t419 = static_cast<uint32_t>(ctx.esp + 0x00000088u);
    mem.w32(t419, 0xffffffffu);
    // 0x004dc368: je 0x4dc373
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc373;
    goto bb_004dc36a;
}
bb_004dc342: {
    // 0x004dc342: mov eax, dword ptr [esp + 0x64]
    uint32_t t420 = static_cast<uint32_t>(ctx.esp + 0x00000064u);
    uint32_t t421 = mem.r32(t420);
    ctx.eax = static_cast<uint32_t>(t421);
    // 0x004dc346: push eax
    uint32_t t422 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t422);
    mem.w32(t422, ctx.eax);
    // 0x004dc347: call 0x4e02f3
    uint32_t t423 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t423);
    mem.w32(t423, 0x004dc34cu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dc34c: add esp, 4
    uint32_t t424 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t424);
    ctx.esp = static_cast<uint32_t>(t424);
    goto bb_004dc34f;
}
bb_004dc55b: {
    // 0x004dc55b: sub eax, edi
    uint32_t t425 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t425);
    ctx.eax = static_cast<uint32_t>(t425);
    // 0x004dc55d: push eax
    uint32_t t426 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t426);
    mem.w32(t426, ctx.eax);
    // 0x004dc55e: push esi
    uint32_t t427 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t427);
    mem.w32(t427, ctx.esi);
    // 0x004dc55f: lea ecx, [esp + 0x68]
    uint32_t t428 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.ecx = static_cast<uint32_t>(t428);
    // 0x004dc563: call 0x407c10
    uint32_t t429 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t429);
    mem.w32(t429, 0x004dc568u);
    sub_00407c10(ctx, mem);
    // 0x004dc568: lea ecx, [esp + 0x60]
    uint32_t t430 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    ctx.ecx = static_cast<uint32_t>(t430);
    // 0x004dc56c: push ecx
    uint32_t t431 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t431);
    mem.w32(t431, ctx.ecx);
    // 0x004dc56d: lea ecx, [esp + 0x48]
    uint32_t t432 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    ctx.ecx = static_cast<uint32_t>(t432);
    // 0x004dc571: mov byte ptr [esp + 0x8c], 4
    uint32_t t433 = static_cast<uint32_t>(ctx.esp + 0x0000008cu);
    mem.w8(t433, uint8_t{0x04u});
    // 0x004dc579: call 0x4c1f60
    uint32_t t434 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t434);
    mem.w32(t434, 0x004dc57eu);
    sub_004c1f60(ctx, mem);
    // 0x004dc57e: add esp, 4
    uint32_t t435 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t435);
    ctx.esp = static_cast<uint32_t>(t435);
    // 0x004dc581: push -1
    uint32_t t436 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t436);
    mem.w32(t436, 0xffffffffu);
    // 0x004dc583: push ebx
    uint32_t t437 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t437);
    mem.w32(t437, ctx.ebx);
    // 0x004dc584: push eax
    uint32_t t438 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t438);
    mem.w32(t438, ctx.eax);
    // 0x004dc585: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x004dc587: mov byte ptr [esp + 0x94], 5
    uint32_t t439 = static_cast<uint32_t>(ctx.esp + 0x00000094u);
    mem.w8(t439, uint8_t{0x05u});
    // 0x004dc58f: call 0x4079d0
    uint32_t t440 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t440);
    mem.w32(t440, 0x004dc594u);
    sub_004079d0(ctx, mem);
    // 0x004dc594: mov edi, 0x10
    ctx.edi = static_cast<uint32_t>(0x00000010u);
    // 0x004dc599: cmp dword ptr [esp + 0x5c], edi
    uint32_t t441 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    uint32_t t442 = mem.r32(t441);
    uint32_t t443 = static_cast<uint32_t>(t442 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t442, ctx.edi, t443);
    // 0x004dc59d: jb 0x4dc5ac
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004dc5ac;
    goto bb_004dc59f;
}
bb_004dc373: {
    // 0x004dc373: add dword ptr [esp + 0x18], 1
    uint32_t t444 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t445 = mem.r32(t444);
    uint32_t t446 = static_cast<uint32_t>(t445 + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t445, 0x00000001u, t446);
    mem.w32(t444, t446);
    // 0x004dc378: add dword ptr [esp + 0x20], 0x2c
    uint32_t t447 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t448 = mem.r32(t447);
    uint32_t t449 = static_cast<uint32_t>(t448 + 0x0000002cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, t448, 0x0000002cu, t449);
    mem.w32(t447, t449);
    // 0x004dc37d: mov edi, dword ptr [esp + 0x1c]
    uint32_t t450 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t451 = mem.r32(t450);
    ctx.edi = static_cast<uint32_t>(t451);
    // 0x004dc381: mov ebp, dword ptr [esp + 0x18]
    uint32_t t452 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t453 = mem.r32(t452);
    ctx.ebp = static_cast<uint32_t>(t453);
    // 0x004dc385: mov ebx, dword ptr [esp + 0x28]
    uint32_t t454 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t455 = mem.r32(t454);
    ctx.ebx = static_cast<uint32_t>(t455);
    // 0x004dc389: mov dword ptr [esp + 0x30], esi
    uint32_t t456 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    mem.w32(t456, ctx.esi);
    // 0x004dc38d: mov dword ptr [esp + 0x34], esi
    uint32_t t457 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    mem.w32(t457, ctx.esi);
    // 0x004dc391: mov dword ptr [esp + 0x38], esi
    uint32_t t458 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    mem.w32(t458, ctx.esi);
    // 0x004dc395: jmp 0x4dc160
    goto bb_004dc160;
}
bb_004dc36a: {
    // 0x004dc36a: push ebx
    uint32_t t459 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t459);
    mem.w32(t459, ctx.ebx);
    // 0x004dc36b: call 0x4e02f3
    uint32_t t460 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t460);
    mem.w32(t460, 0x004dc370u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dc370: add esp, 4
    uint32_t t461 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t461);
    ctx.esp = static_cast<uint32_t>(t461);
    goto bb_004dc373;
}
bb_004dc5ac: {
    // 0x004dc5ac: cmp dword ptr [esp + 0x78], edi
    uint32_t t462 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    uint32_t t463 = mem.r32(t462);
    uint32_t t464 = static_cast<uint32_t>(t463 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t463, ctx.edi, t464);
    // 0x004dc5b0: mov dword ptr [esp + 0x5c], 0xf
    uint32_t t465 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    mem.w32(t465, 0x0000000fu);
    // 0x004dc5b8: mov dword ptr [esp + 0x58], ebx
    uint32_t t466 = static_cast<uint32_t>(ctx.esp + 0x00000058u);
    mem.w32(t466, ctx.ebx);
    // 0x004dc5bc: mov byte ptr [esp + 0x48], bl
    uint32_t t467 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    mem.w8(t467, recomp_detail::r8l(ctx.ebx));
    // 0x004dc5c0: jb 0x4dc5cf
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004dc5cf;
    goto bb_004dc5c2;
}
bb_004dc59f: {
    // 0x004dc59f: mov edx, dword ptr [esp + 0x48]
    uint32_t t468 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    uint32_t t469 = mem.r32(t468);
    ctx.edx = static_cast<uint32_t>(t469);
    // 0x004dc5a3: push edx
    uint32_t t470 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t470);
    mem.w32(t470, ctx.edx);
    // 0x004dc5a4: call 0x4e02f3
    uint32_t t471 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t471);
    mem.w32(t471, 0x004dc5a9u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dc5a9: add esp, 4
    uint32_t t472 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t472);
    ctx.esp = static_cast<uint32_t>(t472);
    goto bb_004dc5ac;
}
bb_004dc5cf: {
    // 0x004dc5cf: mov edi, ebp
    ctx.edi = static_cast<uint32_t>(ctx.ebp);
    // 0x004dc5d1: mov dword ptr [esp + 0x78], 0xf
    uint32_t t473 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    mem.w32(t473, 0x0000000fu);
    // 0x004dc5d9: mov dword ptr [esp + 0x74], ebx
    uint32_t t474 = static_cast<uint32_t>(ctx.esp + 0x00000074u);
    mem.w32(t474, ctx.ebx);
    // 0x004dc5dd: mov byte ptr [esp + 0x64], bl
    uint32_t t475 = static_cast<uint32_t>(ctx.esp + 0x00000064u);
    mem.w8(t475, recomp_detail::r8l(ctx.ebx));
    // 0x004dc5e1: call 0x4db470
    uint32_t t476 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t476);
    mem.w32(t476, 0x004dc5e6u);
    sub_004db470(ctx, mem);
    // 0x004dc5e6: cmp esi, ebx
    uint32_t t477 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t477);
    // 0x004dc5e8: mov dword ptr [ebp + 0x1c], eax
    uint32_t t478 = static_cast<uint32_t>(ctx.ebp + 0x0000001cu);
    mem.w32(t478, ctx.eax);
    // 0x004dc5eb: mov dword ptr [esp + 0x88], 0xffffffff
    uint32_t t479 = static_cast<uint32_t>(ctx.esp + 0x00000088u);
    mem.w32(t479, 0xffffffffu);
    // 0x004dc5f6: je 0x4dc601
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dc601;
    goto bb_004dc5f8;
}
bb_004dc5c2: {
    // 0x004dc5c2: mov eax, dword ptr [esp + 0x64]
    uint32_t t480 = static_cast<uint32_t>(ctx.esp + 0x00000064u);
    uint32_t t481 = mem.r32(t480);
    ctx.eax = static_cast<uint32_t>(t481);
    // 0x004dc5c6: push eax
    uint32_t t482 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t482);
    mem.w32(t482, ctx.eax);
    // 0x004dc5c7: call 0x4e02f3
    uint32_t t483 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t483);
    mem.w32(t483, 0x004dc5ccu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dc5cc: add esp, 4
    uint32_t t484 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t484);
    ctx.esp = static_cast<uint32_t>(t484);
    goto bb_004dc5cf;
}
bb_004dc601: {
    // 0x004dc601: add dword ptr [esp + 0x20], 1
    uint32_t t485 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t486 = mem.r32(t485);
    uint32_t t487 = static_cast<uint32_t>(t486 + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t486, 0x00000001u, t487);
    mem.w32(t485, t487);
    // 0x004dc606: add dword ptr [esp + 0x18], 0x2c
    uint32_t t488 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t489 = mem.r32(t488);
    uint32_t t490 = static_cast<uint32_t>(t489 + 0x0000002cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, t489, 0x0000002cu, t490);
    mem.w32(t488, t490);
    // 0x004dc60b: mov edi, dword ptr [esp + 0x1c]
    uint32_t t491 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t492 = mem.r32(t491);
    ctx.edi = static_cast<uint32_t>(t492);
    // 0x004dc60f: mov ebp, dword ptr [esp + 0x20]
    uint32_t t493 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t494 = mem.r32(t493);
    ctx.ebp = static_cast<uint32_t>(t494);
    // 0x004dc613: mov dword ptr [esp + 0x30], ebx
    uint32_t t495 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    mem.w32(t495, ctx.ebx);
    // 0x004dc617: mov dword ptr [esp + 0x34], ebx
    uint32_t t496 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    mem.w32(t496, ctx.ebx);
    // 0x004dc61b: mov dword ptr [esp + 0x38], ebx
    uint32_t t497 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    mem.w32(t497, ctx.ebx);
    // 0x004dc61f: mov ebx, dword ptr [esp + 0x28]
    uint32_t t498 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t499 = mem.r32(t498);
    ctx.ebx = static_cast<uint32_t>(t499);
    // 0x004dc623: jmp 0x4dc3a4
    goto bb_004dc3a4;
}
bb_004dc5f8: {
    // 0x004dc5f8: push esi
    uint32_t t500 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t500);
    mem.w32(t500, ctx.esi);
    // 0x004dc5f9: call 0x4e02f3
    uint32_t t501 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t501);
    mem.w32(t501, 0x004dc5feu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dc5fe: add esp, 4
    uint32_t t502 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t502);
    ctx.esp = static_cast<uint32_t>(t502);
    goto bb_004dc601;
}
}

// sub_004dcb50 | subsystem=FilePacFunc | canonical | 3 blocks | 19 insns
void sub_004dcb50(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dcb50: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x004dcb51: mov eax, dword ptr [esi + 4]
    uint32_t t1 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t2 = mem.r32(t1);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x004dcb54: test eax, eax
    uint32_t t3 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t3);
    // 0x004dcb56: je 0x4dcb72
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dcb72;
    goto bb_004dcb58;
}
bb_004dcb72: {
    // 0x004dcb72: mov dword ptr [esi + 4], 0
    uint32_t t4 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t4, 0x00000000u);
    // 0x004dcb79: mov dword ptr [esi + 8], 0
    uint32_t t5 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t5, 0x00000000u);
    // 0x004dcb80: mov dword ptr [esi + 0xc], 0
    uint32_t t6 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t6, 0x00000000u);
    // 0x004dcb87: pop ecx
    uint32_t t7 = ctx.esp;
    uint32_t t8 = mem.r32(t7);
    uint32_t t9 = static_cast<uint32_t>(t7 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    ctx.ecx = static_cast<uint32_t>(t8);
    // 0x004dcb88: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004dcb58: {
    // 0x004dcb58: mov ecx, dword ptr [esp]
    uint32_t t10 = mem.r32(ctx.esp);
    ctx.ecx = static_cast<uint32_t>(t10);
    // 0x004dcb5b: push edi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.edi);
    // 0x004dcb5c: mov edi, dword ptr [esi + 8]
    uint32_t t12 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t13 = mem.r32(t12);
    ctx.edi = static_cast<uint32_t>(t13);
    // 0x004dcb5f: push ecx
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, ctx.ecx);
    // 0x004dcb60: call 0x4dd220
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x004dcb65u);
    sub_004dd220(ctx, mem);
    // 0x004dcb65: mov edx, dword ptr [esi + 4]
    uint32_t t16 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t17 = mem.r32(t16);
    ctx.edx = static_cast<uint32_t>(t17);
    // 0x004dcb68: push edx
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, ctx.edx);
    // 0x004dcb69: call 0x4e02f3
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x004dcb6eu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dcb6e: add esp, 8
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t20);
    ctx.esp = static_cast<uint32_t>(t20);
    // 0x004dcb71: pop edi
    uint32_t t21 = ctx.esp;
    uint32_t t22 = mem.r32(t21);
    uint32_t t23 = static_cast<uint32_t>(t21 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    ctx.edi = static_cast<uint32_t>(t22);
    goto bb_004dcb72;
}
}

// sub_004dcb90 | subsystem=FilePacFunc | canonical | 3 blocks | 13 insns
void sub_004dcb90(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dcb90: mov eax, dword ptr [ecx + 4]
    uint32_t t0 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    uint32_t t1 = mem.r32(t0);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x004dcb93: test eax, eax
    uint32_t t2 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    // 0x004dcb95: jne 0x4dcb98
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dcb98;
    goto bb_004dcb97;
}
bb_004dcb98: {
    // 0x004dcb98: mov ecx, dword ptr [ecx + 8]
    uint32_t t3 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t4 = mem.r32(t3);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x004dcb9b: sub ecx, eax
    uint32_t t5 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t5);
    ctx.ecx = static_cast<uint32_t>(t5);
    // 0x004dcb9d: mov eax, 0x2e8ba2e9
    ctx.eax = static_cast<uint32_t>(0x2e8ba2e9u);
    // 0x004dcba2: imul ecx
    uint64_t t6 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t7 = static_cast<uint32_t>(t6);
    uint32_t t8 = static_cast<uint32_t>(t6 >> 32);
    ctx.eax = static_cast<uint32_t>(t7);
    ctx.edx = static_cast<uint32_t>(t8);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t6);
    // 0x004dcba4: sar edx, 3
    uint32_t t9 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t10 = recomp_detail::sar<uint32_t>(ctx.edx, t9);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t9, t10);
    ctx.edx = static_cast<uint32_t>(t10);
    // 0x004dcba7: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004dcba9: shr eax, 0x1f
    uint32_t t11 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t12 = recomp_detail::shr<uint32_t>(ctx.eax, t11);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t11, t12);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x004dcbac: add eax, edx
    uint32_t t13 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t13);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x004dcbae: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004dcb97: {
    // 0x004dcb97: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004dcbb0 | subsystem=FilePacFunc | canonical | 22 blocks | 114 insns
void sub_004dcbb0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dcbb0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x004dcbb2: push 0x5156c8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005156c8u);
    // 0x004dcbb7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004dcbbd: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x004dcbbe: sub esp, 0x10
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000010u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x004dcbc1: push ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebx);
    // 0x004dcbc2: push ebp
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.ebp);
    // 0x004dcbc3: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x004dcbc4: push edi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.edi);
    // 0x004dcbc5: mov eax, dword ptr [0x54b458]
    uint32_t t10 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x004dcbca: xor eax, esp
    uint32_t t11 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x004dcbcc: push eax
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.eax);
    // 0x004dcbcd: lea eax, [esp + 0x24]
    uint32_t t13 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x004dcbd1: mov dword ptr fs:[0], eax
    uint32_t t14 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t14, ctx.eax);
    // 0x004dcbd7: mov ebx, ecx
    ctx.ebx = static_cast<uint32_t>(ctx.ecx);
    // 0x004dcbd9: mov esi, edx
    ctx.esi = static_cast<uint32_t>(ctx.edx);
    // 0x004dcbdb: mov dword ptr [esp + 0x2c], 0
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    mem.w32(t15, 0x00000000u);
    // 0x004dcbe3: mov edi, dword ptr [esi + 4]
    uint32_t t16 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t17 = mem.r32(t16);
    ctx.edi = static_cast<uint32_t>(t17);
    // 0x004dcbe6: test edi, edi
    uint32_t t18 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    // 0x004dcbe8: jne 0x4dcbee
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dcbee;
    goto bb_004dcbea;
}
bb_004dcbee: {
    // 0x004dcbee: mov ecx, dword ptr [esi + 8]
    uint32_t t19 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t20 = mem.r32(t19);
    ctx.ecx = static_cast<uint32_t>(t20);
    // 0x004dcbf1: sub ecx, edi
    uint32_t t21 = static_cast<uint32_t>(ctx.ecx - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.edi, t21);
    ctx.ecx = static_cast<uint32_t>(t21);
    // 0x004dcbf3: mov eax, 0x2e8ba2e9
    ctx.eax = static_cast<uint32_t>(0x2e8ba2e9u);
    // 0x004dcbf8: imul ecx
    uint64_t t22 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t23 = static_cast<uint32_t>(t22);
    uint32_t t24 = static_cast<uint32_t>(t22 >> 32);
    ctx.eax = static_cast<uint32_t>(t23);
    ctx.edx = static_cast<uint32_t>(t24);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t22);
    // 0x004dcbfa: sar edx, 3
    uint32_t t25 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t26 = recomp_detail::sar<uint32_t>(ctx.edx, t25);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t25, t26);
    ctx.edx = static_cast<uint32_t>(t26);
    // 0x004dcbfd: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004dcbff: shr eax, 0x1f
    uint32_t t27 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t28 = recomp_detail::shr<uint32_t>(ctx.eax, t27);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t27, t28);
    ctx.eax = static_cast<uint32_t>(t28);
    // 0x004dcc02: add eax, edx
    uint32_t t29 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t29);
    ctx.eax = static_cast<uint32_t>(t29);
    goto bb_004dcc04;
}
bb_004dcbea: {
    // 0x004dcbea: xor eax, eax
    uint32_t t30 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t30);
    ctx.eax = static_cast<uint32_t>(t30);
    // 0x004dcbec: jmp 0x4dcc04
}
bb_004dcc04: {
    // 0x004dcc04: cmp eax, ebx
    uint32_t t31 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t31);
    // 0x004dcc06: jae 0x4dcc58
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004dcc58;
    goto bb_004dcc08;
}
bb_004dcc58: {
    // 0x004dcc58: test edi, edi
    uint32_t t32 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t32);
    // 0x004dcc5a: je 0x4dccb5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dccb5;
    goto bb_004dcc5c;
}
bb_004dcc08: {
    // 0x004dcc08: mov ebp, dword ptr [esi + 8]
    uint32_t t33 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t34 = mem.r32(t33);
    ctx.ebp = static_cast<uint32_t>(t34);
    // 0x004dcc0b: cmp edi, ebp
    uint32_t t35 = static_cast<uint32_t>(ctx.edi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebp, t35);
    // 0x004dcc0d: jbe 0x4dcc14
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_004dcc14;
    goto bb_004dcc0f;
}
bb_004dccb5: {
    // 0x004dccb5: cmp dword ptr [esp + 0x4c], 0x10
    uint32_t t36 = static_cast<uint32_t>(ctx.esp + 0x0000004cu);
    uint32_t t37 = mem.r32(t36);
    uint32_t t38 = static_cast<uint32_t>(t37 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t37, 0x00000010u, t38);
    // 0x004dccba: jb 0x4dccc9
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004dccc9;
    goto bb_004dccbc;
}
bb_004dcc5c: {
    // 0x004dcc5c: mov ebp, dword ptr [esi + 8]
    uint32_t t39 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t40 = mem.r32(t39);
    ctx.ebp = static_cast<uint32_t>(t40);
    // 0x004dcc5f: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x004dcc61: sub ecx, edi
    uint32_t t41 = static_cast<uint32_t>(ctx.ecx - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.edi, t41);
    ctx.ecx = static_cast<uint32_t>(t41);
    // 0x004dcc63: mov eax, 0x2e8ba2e9
    ctx.eax = static_cast<uint32_t>(0x2e8ba2e9u);
    // 0x004dcc68: imul ecx
    uint64_t t42 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t43 = static_cast<uint32_t>(t42);
    uint32_t t44 = static_cast<uint32_t>(t42 >> 32);
    ctx.eax = static_cast<uint32_t>(t43);
    ctx.edx = static_cast<uint32_t>(t44);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t42);
    // 0x004dcc6a: sar edx, 3
    uint32_t t45 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t46 = recomp_detail::sar<uint32_t>(ctx.edx, t45);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t45, t46);
    ctx.edx = static_cast<uint32_t>(t46);
    // 0x004dcc6d: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004dcc6f: shr eax, 0x1f
    uint32_t t47 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t48 = recomp_detail::shr<uint32_t>(ctx.eax, t47);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t47, t48);
    ctx.eax = static_cast<uint32_t>(t48);
    // 0x004dcc72: add eax, edx
    uint32_t t49 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t49);
    ctx.eax = static_cast<uint32_t>(t49);
    // 0x004dcc74: cmp ebx, eax
    uint32_t t50 = static_cast<uint32_t>(ctx.ebx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.eax, t50);
    // 0x004dcc76: jae 0x4dccb5
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004dccb5;
    goto bb_004dcc78;
}
bb_004dcc14: {
    // 0x004dcc14: mov eax, dword ptr [esi + 4]
    uint32_t t51 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t52 = mem.r32(t51);
    ctx.eax = static_cast<uint32_t>(t52);
    // 0x004dcc17: test eax, eax
    uint32_t t53 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t53);
    // 0x004dcc19: jne 0x4dcc30
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dcc30;
    goto bb_004dcc1b;
}
bb_004dcc0f: {
    // 0x004dcc0f: call 0x4e0bf2
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, 0x004dcc14u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004dcc14;
}
bb_004dccc9: {
    // 0x004dccc9: mov ecx, dword ptr [esp + 0x24]
    uint32_t t55 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t56 = mem.r32(t55);
    ctx.ecx = static_cast<uint32_t>(t56);
    // 0x004dcccd: mov dword ptr fs:[0], ecx
    uint32_t t57 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t57, ctx.ecx);
    // 0x004dccd4: pop ecx
    uint32_t t58 = ctx.esp;
    uint32_t t59 = mem.r32(t58);
    uint32_t t60 = static_cast<uint32_t>(t58 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t60);
    ctx.ecx = static_cast<uint32_t>(t59);
    // 0x004dccd5: pop edi
    uint32_t t61 = ctx.esp;
    uint32_t t62 = mem.r32(t61);
    uint32_t t63 = static_cast<uint32_t>(t61 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    ctx.edi = static_cast<uint32_t>(t62);
    // 0x004dccd6: pop esi
    uint32_t t64 = ctx.esp;
    uint32_t t65 = mem.r32(t64);
    uint32_t t66 = static_cast<uint32_t>(t64 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    ctx.esi = static_cast<uint32_t>(t65);
    // 0x004dccd7: pop ebp
    uint32_t t67 = ctx.esp;
    uint32_t t68 = mem.r32(t67);
    uint32_t t69 = static_cast<uint32_t>(t67 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    ctx.ebp = static_cast<uint32_t>(t68);
    // 0x004dccd8: pop ebx
    uint32_t t70 = ctx.esp;
    uint32_t t71 = mem.r32(t70);
    uint32_t t72 = static_cast<uint32_t>(t70 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    ctx.ebx = static_cast<uint32_t>(t71);
    // 0x004dccd9: add esp, 0x1c
    uint32_t t73 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000001cu, t73);
    ctx.esp = static_cast<uint32_t>(t73);
    // 0x004dccdc: ret 0x2c
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 44u;
    return;
}
bb_004dccbc: {
    // 0x004dccbc: mov ecx, dword ptr [esp + 0x38]
    uint32_t t74 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    uint32_t t75 = mem.r32(t74);
    ctx.ecx = static_cast<uint32_t>(t75);
    // 0x004dccc0: push ecx
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    mem.w32(t76, ctx.ecx);
    // 0x004dccc1: call 0x4e02f3
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, 0x004dccc6u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dccc6: add esp, 4
    uint32_t t78 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t78);
    ctx.esp = static_cast<uint32_t>(t78);
    goto bb_004dccc9;
}
bb_004dcc78: {
    // 0x004dcc78: cmp edi, ebp
    uint32_t t79 = static_cast<uint32_t>(ctx.edi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebp, t79);
    // 0x004dcc7a: jbe 0x4dcc81
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_004dcc81;
    goto bb_004dcc7c;
}
bb_004dcc30: {
    // 0x004dcc30: mov ecx, dword ptr [esi + 8]
    uint32_t t80 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t81 = mem.r32(t80);
    ctx.ecx = static_cast<uint32_t>(t81);
    // 0x004dcc33: sub ecx, eax
    uint32_t t82 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t82);
    ctx.ecx = static_cast<uint32_t>(t82);
    // 0x004dcc35: mov eax, 0x2e8ba2e9
    ctx.eax = static_cast<uint32_t>(0x2e8ba2e9u);
    // 0x004dcc3a: imul ecx
    uint64_t t83 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t84 = static_cast<uint32_t>(t83);
    uint32_t t85 = static_cast<uint32_t>(t83 >> 32);
    ctx.eax = static_cast<uint32_t>(t84);
    ctx.edx = static_cast<uint32_t>(t85);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t83);
    // 0x004dcc3c: sar edx, 3
    uint32_t t86 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t87 = recomp_detail::sar<uint32_t>(ctx.edx, t86);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t86, t87);
    ctx.edx = static_cast<uint32_t>(t87);
    // 0x004dcc3f: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004dcc41: shr eax, 0x1f
    uint32_t t88 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t89 = recomp_detail::shr<uint32_t>(ctx.eax, t88);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t88, t89);
    ctx.eax = static_cast<uint32_t>(t89);
    // 0x004dcc44: add eax, edx
    uint32_t t90 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t90);
    ctx.eax = static_cast<uint32_t>(t90);
    // 0x004dcc46: push ebp
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, ctx.ebp);
    // 0x004dcc47: push esi
    uint32_t t92 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    mem.w32(t92, ctx.esi);
    // 0x004dcc48: sub ebx, eax
    uint32_t t93 = static_cast<uint32_t>(ctx.ebx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.eax, t93);
    ctx.ebx = static_cast<uint32_t>(t93);
    // 0x004dcc4a: push ebx
    uint32_t t94 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t94);
    mem.w32(t94, ctx.ebx);
    // 0x004dcc4b: lea edx, [esp + 0x40]
    uint32_t t95 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    ctx.edx = static_cast<uint32_t>(t95);
    // 0x004dcc4f: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004dcc51: call 0x4dcd40
    uint32_t t96 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    mem.w32(t96, 0x004dcc56u);
    sub_004dcd40(ctx, mem);
    // 0x004dcc56: jmp 0x4dccb5
    goto bb_004dccb5;
}
bb_004dcc1b: {
    // 0x004dcc1b: push ebp
    uint32_t t97 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t97);
    mem.w32(t97, ctx.ebp);
    // 0x004dcc1c: push esi
    uint32_t t98 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t98);
    mem.w32(t98, ctx.esi);
    // 0x004dcc1d: sub ebx, eax
    uint32_t t99 = static_cast<uint32_t>(ctx.ebx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.eax, t99);
    ctx.ebx = static_cast<uint32_t>(t99);
    // 0x004dcc1f: push ebx
    uint32_t t100 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t100);
    mem.w32(t100, ctx.ebx);
    // 0x004dcc20: lea edx, [esp + 0x40]
    uint32_t t101 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    ctx.edx = static_cast<uint32_t>(t101);
    // 0x004dcc24: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004dcc26: call 0x4dcd40
    uint32_t t102 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    mem.w32(t102, 0x004dcc2bu);
    sub_004dcd40(ctx, mem);
    // 0x004dcc2b: jmp 0x4dccb5
    goto bb_004dccb5;
}
bb_004dcc81: {
    // 0x004dcc81: mov edi, dword ptr [esi + 4]
    uint32_t t103 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t104 = mem.r32(t103);
    ctx.edi = static_cast<uint32_t>(t104);
    // 0x004dcc84: cmp edi, dword ptr [esi + 8]
    uint32_t t105 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t106 = mem.r32(t105);
    uint32_t t107 = static_cast<uint32_t>(ctx.edi - t106);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, t106, t107);
    // 0x004dcc87: jbe 0x4dcc8e
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_004dcc8e;
    goto bb_004dcc89;
}
bb_004dcc7c: {
    // 0x004dcc7c: call 0x4e0bf2
    uint32_t t108 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t108);
    mem.w32(t108, 0x004dcc81u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004dcc81;
}
bb_004dcc8e: {
    // 0x004dcc8e: imul ebx, ebx, 0x2c
    uint64_t t109 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.ebx)) * static_cast<int64_t>(static_cast<int32_t>(0x0000002cu)));
    uint32_t t110 = static_cast<uint32_t>(t109);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t109);
    ctx.ebx = static_cast<uint32_t>(t110);
    // 0x004dcc91: mov dword ptr [esp + 0x1c], edi
    uint32_t t111 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t111, ctx.edi);
    // 0x004dcc95: add edi, ebx
    uint32_t t112 = static_cast<uint32_t>(ctx.edi + ctx.ebx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, ctx.ebx, t112);
    ctx.edi = static_cast<uint32_t>(t112);
    // 0x004dcc97: cmp edi, dword ptr [esi + 8]
    uint32_t t113 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t114 = mem.r32(t113);
    uint32_t t115 = static_cast<uint32_t>(ctx.edi - t114);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, t114, t115);
    // 0x004dcc9a: ja 0x4dcca1
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_004dcca1;
    goto bb_004dcc9c;
}
bb_004dcc89: {
    // 0x004dcc89: call 0x4e0bf2
    uint32_t t116 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t116);
    mem.w32(t116, 0x004dcc8eu);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004dcc8e;
}
bb_004dcca1: {
    // 0x004dcca1: call 0x4e0bf2
    uint32_t t117 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t117);
    mem.w32(t117, 0x004dcca6u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004dcca6;
}
bb_004dcc9c: {
    // 0x004dcc9c: cmp edi, dword ptr [esi + 4]
    uint32_t t118 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t119 = mem.r32(t118);
    uint32_t t120 = static_cast<uint32_t>(ctx.edi - t119);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, t119, t120);
    // 0x004dcc9f: jae 0x4dcca6
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004dcca6;
    goto bb_004dcca1;
}
bb_004dcca6: {
    // 0x004dcca6: push ebp
    uint32_t t121 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t121);
    mem.w32(t121, ctx.ebp);
    // 0x004dcca7: push esi
    uint32_t t122 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t122);
    mem.w32(t122, ctx.esi);
    // 0x004dcca8: push edi
    uint32_t t123 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t123);
    mem.w32(t123, ctx.edi);
    // 0x004dcca9: push esi
    uint32_t t124 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t124);
    mem.w32(t124, ctx.esi);
    // 0x004dccaa: lea eax, [esp + 0x28]
    uint32_t t125 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.eax = static_cast<uint32_t>(t125);
    // 0x004dccae: push eax
    uint32_t t126 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t126);
    mem.w32(t126, ctx.eax);
    // 0x004dccaf: push esi
    uint32_t t127 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t127);
    mem.w32(t127, ctx.esi);
    // 0x004dccb0: call 0x4dcce0
    uint32_t t128 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t128);
    mem.w32(t128, 0x004dccb5u);
    sub_004dcce0(ctx, mem);
    goto bb_004dccb5;
}
}

// sub_004dcce0 | subsystem=FilePacFunc | canonical | 6 blocks | 34 insns
void sub_004dcce0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dcce0: push ebx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebx);
    // 0x004dcce1: mov ebx, dword ptr [esp + 0x10]
    uint32_t t1 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t2 = mem.r32(t1);
    ctx.ebx = static_cast<uint32_t>(t2);
    // 0x004dcce5: test ebx, ebx
    uint32_t t3 = static_cast<uint32_t>(ctx.ebx & ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t3);
    // 0x004dcce7: push ebp
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.ebp);
    // 0x004dcce8: mov ebp, dword ptr [esp + 0xc]
    uint32_t t5 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t6 = mem.r32(t5);
    ctx.ebp = static_cast<uint32_t>(t6);
    // 0x004dccec: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x004dcced: push edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edi);
    // 0x004dccee: je 0x4dccf6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dccf6;
    goto bb_004dccf0;
}
bb_004dccf6: {
    // 0x004dccf6: call 0x4e0bf2
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x004dccfbu);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004dccfb;
}
bb_004dccf0: {
    // 0x004dccf0: cmp ebx, dword ptr [esp + 0x24]
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t11 = mem.r32(t10);
    uint32_t t12 = static_cast<uint32_t>(ctx.ebx - t11);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, t11, t12);
    // 0x004dccf4: je 0x4dccfb
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dccfb;
    goto bb_004dccf6;
}
bb_004dccfb: {
    // 0x004dccfb: mov esi, dword ptr [esp + 0x20]
    uint32_t t13 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t14 = mem.r32(t13);
    ctx.esi = static_cast<uint32_t>(t14);
    // 0x004dccff: mov edi, dword ptr [esp + 0x28]
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t16 = mem.r32(t15);
    ctx.edi = static_cast<uint32_t>(t16);
    // 0x004dcd03: cmp esi, edi
    uint32_t t17 = static_cast<uint32_t>(ctx.esi - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edi, t17);
    // 0x004dcd05: je 0x4dcd2a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dcd2a;
    goto bb_004dcd07;
}
bb_004dcd2a: {
    // 0x004dcd2a: mov eax, dword ptr [esp + 0x18]
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t19 = mem.r32(t18);
    ctx.eax = static_cast<uint32_t>(t19);
    // 0x004dcd2e: pop edi
    uint32_t t20 = ctx.esp;
    uint32_t t21 = mem.r32(t20);
    uint32_t t22 = static_cast<uint32_t>(t20 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    ctx.edi = static_cast<uint32_t>(t21);
    // 0x004dcd2f: mov dword ptr [eax + 4], esi
    uint32_t t23 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w32(t23, ctx.esi);
    // 0x004dcd32: pop esi
    uint32_t t24 = ctx.esp;
    uint32_t t25 = mem.r32(t24);
    uint32_t t26 = static_cast<uint32_t>(t24 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    ctx.esi = static_cast<uint32_t>(t25);
    // 0x004dcd33: pop ebp
    uint32_t t27 = ctx.esp;
    uint32_t t28 = mem.r32(t27);
    uint32_t t29 = static_cast<uint32_t>(t27 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    ctx.ebp = static_cast<uint32_t>(t28);
    // 0x004dcd34: mov dword ptr [eax], ebx
    mem.w32(ctx.eax, ctx.ebx);
    // 0x004dcd36: pop ebx
    uint32_t t30 = ctx.esp;
    uint32_t t31 = mem.r32(t30);
    uint32_t t32 = static_cast<uint32_t>(t30 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    ctx.ebx = static_cast<uint32_t>(t31);
    // 0x004dcd37: ret 0x18
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 24u;
    return;
}
bb_004dcd07: {
    // 0x004dcd07: mov eax, dword ptr [ebp + 8]
    uint32_t t33 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t34 = mem.r32(t33);
    ctx.eax = static_cast<uint32_t>(t34);
    // 0x004dcd0a: call 0x4dd0b0
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, 0x004dcd0fu);
    sub_004dd0b0(ctx, mem);
    // 0x004dcd0f: mov edi, dword ptr [ebp + 8]
    uint32_t t36 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t37 = mem.r32(t36);
    ctx.edi = static_cast<uint32_t>(t37);
    // 0x004dcd12: mov ebx, eax
    ctx.ebx = static_cast<uint32_t>(ctx.eax);
    // 0x004dcd14: mov eax, dword ptr [esp + 0x14]
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t39 = mem.r32(t38);
    ctx.eax = static_cast<uint32_t>(t39);
    // 0x004dcd18: push eax
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, ctx.eax);
    // 0x004dcd19: mov eax, ebx
    ctx.eax = static_cast<uint32_t>(ctx.ebx);
    // 0x004dcd1b: call 0x4dd220
    uint32_t t41 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    mem.w32(t41, 0x004dcd20u);
    sub_004dd220(ctx, mem);
    // 0x004dcd20: mov dword ptr [ebp + 8], ebx
    uint32_t t42 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    mem.w32(t42, ctx.ebx);
    // 0x004dcd23: mov ebx, dword ptr [esp + 0x20]
    uint32_t t43 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t44 = mem.r32(t43);
    ctx.ebx = static_cast<uint32_t>(t44);
    // 0x004dcd27: add esp, 4
    uint32_t t45 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t45);
    ctx.esp = static_cast<uint32_t>(t45);
    goto bb_004dcd2a;
}
}

// sub_004dcd40 | subsystem=FilePacFunc | canonical | 36 blocks | 274 insns
void sub_004dcd40(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dcd40: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x004dcd41: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x004dcd43: push -1
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0xffffffffu);
    // 0x004dcd45: push 0x515698
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x00515698u);
    // 0x004dcd4a: mov eax, dword ptr fs:[0]
    uint32_t t3 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t4 = mem.r32(t3);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x004dcd50: push eax
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.eax);
    // 0x004dcd51: sub esp, 0x40
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000040u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000040u, t6);
    ctx.esp = static_cast<uint32_t>(t6);
    // 0x004dcd54: mov eax, dword ptr [0x54b458]
    uint32_t t7 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x004dcd59: xor eax, ebp
    uint32_t t8 = static_cast<uint32_t>(ctx.eax ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t8);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x004dcd5b: mov dword ptr [ebp - 0x14], eax
    uint32_t t9 = static_cast<uint32_t>(ctx.ebp + 0xffffffecu);
    mem.w32(t9, ctx.eax);
    // 0x004dcd5e: push ebx
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.ebx);
    // 0x004dcd5f: push esi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.esi);
    // 0x004dcd60: push edi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.edi);
    // 0x004dcd61: push eax
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, ctx.eax);
    // 0x004dcd62: lea eax, [ebp - 0xc]
    uint32_t t14 = static_cast<uint32_t>(ctx.ebp + 0xfffffff4u);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x004dcd65: mov dword ptr fs:[0], eax
    uint32_t t15 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t15, ctx.eax);
    // 0x004dcd6b: mov dword ptr [ebp - 0x10], esp
    uint32_t t16 = static_cast<uint32_t>(ctx.ebp + 0xfffffff0u);
    mem.w32(t16, ctx.esp);
    // 0x004dcd6e: push -1
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0xffffffffu);
    // 0x004dcd70: xor esi, esi
    uint32_t t18 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    ctx.esi = static_cast<uint32_t>(t18);
    // 0x004dcd72: mov ebx, ecx
    ctx.ebx = static_cast<uint32_t>(ctx.ecx);
    // 0x004dcd74: mov edi, edx
    ctx.edi = static_cast<uint32_t>(ctx.edx);
    // 0x004dcd76: push esi
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, ctx.esi);
    // 0x004dcd77: push edi
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, ctx.edi);
    // 0x004dcd78: lea ecx, [ebp - 0x40]
    uint32_t t21 = static_cast<uint32_t>(ctx.ebp + 0xffffffc0u);
    ctx.ecx = static_cast<uint32_t>(t21);
    // 0x004dcd7b: mov dword ptr [ebp - 0x44], ebx
    uint32_t t22 = static_cast<uint32_t>(ctx.ebp + 0xffffffbcu);
    mem.w32(t22, ctx.ebx);
    // 0x004dcd7e: mov dword ptr [ebp - 0x28], 0xf
    uint32_t t23 = static_cast<uint32_t>(ctx.ebp + 0xffffffd8u);
    mem.w32(t23, 0x0000000fu);
    // 0x004dcd85: mov dword ptr [ebp - 0x2c], esi
    uint32_t t24 = static_cast<uint32_t>(ctx.ebp + 0xffffffd4u);
    mem.w32(t24, ctx.esi);
    // 0x004dcd88: mov byte ptr [ebp - 0x3c], 0
    uint32_t t25 = static_cast<uint32_t>(ctx.ebp + 0xffffffc4u);
    mem.w8(t25, uint8_t{0x00u});
    // 0x004dcd8c: call 0x4079d0
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x004dcd91u);
    sub_004079d0(ctx, mem);
    // 0x004dcd91: mov eax, dword ptr [edi + 0x1c]
    uint32_t t27 = static_cast<uint32_t>(ctx.edi + 0x0000001cu);
    uint32_t t28 = mem.r32(t27);
    ctx.eax = static_cast<uint32_t>(t28);
    // 0x004dcd94: mov ecx, dword ptr [edi + 0x20]
    uint32_t t29 = static_cast<uint32_t>(ctx.edi + 0x00000020u);
    uint32_t t30 = mem.r32(t29);
    ctx.ecx = static_cast<uint32_t>(t30);
    // 0x004dcd97: mov edx, dword ptr [edi + 0x24]
    uint32_t t31 = static_cast<uint32_t>(ctx.edi + 0x00000024u);
    uint32_t t32 = mem.r32(t31);
    ctx.edx = static_cast<uint32_t>(t32);
    // 0x004dcd9a: mov dword ptr [ebp - 0x24], eax
    uint32_t t33 = static_cast<uint32_t>(ctx.ebp + 0xffffffdcu);
    mem.w32(t33, ctx.eax);
    // 0x004dcd9d: mov eax, dword ptr [edi + 0x28]
    uint32_t t34 = static_cast<uint32_t>(ctx.edi + 0x00000028u);
    uint32_t t35 = mem.r32(t34);
    ctx.eax = static_cast<uint32_t>(t35);
    // 0x004dcda0: mov dword ptr [ebp - 0x20], ecx
    uint32_t t36 = static_cast<uint32_t>(ctx.ebp + 0xffffffe0u);
    mem.w32(t36, ctx.ecx);
    // 0x004dcda3: mov dword ptr [ebp - 0x1c], edx
    uint32_t t37 = static_cast<uint32_t>(ctx.ebp + 0xffffffe4u);
    mem.w32(t37, ctx.edx);
    // 0x004dcda6: mov dword ptr [ebp - 0x18], eax
    uint32_t t38 = static_cast<uint32_t>(ctx.ebp + 0xffffffe8u);
    mem.w32(t38, ctx.eax);
    // 0x004dcda9: mov dword ptr [ebp - 4], esi
    uint32_t t39 = static_cast<uint32_t>(ctx.ebp + 0xfffffffcu);
    mem.w32(t39, ctx.esi);
    // 0x004dcdac: mov edi, dword ptr [ebx + 4]
    uint32_t t40 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    uint32_t t41 = mem.r32(t40);
    ctx.edi = static_cast<uint32_t>(t41);
    // 0x004dcdaf: cmp edi, esi
    uint32_t t42 = static_cast<uint32_t>(ctx.edi - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.esi, t42);
    // 0x004dcdb1: je 0x4dcdc9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dcdc9;
    goto bb_004dcdb3;
}
bb_004dcdc9: {
    // 0x004dcdc9: mov ecx, dword ptr [ebp + 8]
    uint32_t t43 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t44 = mem.r32(t43);
    ctx.ecx = static_cast<uint32_t>(t44);
    // 0x004dcdcc: test ecx, ecx
    uint32_t t45 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t45);
    // 0x004dcdce: je 0x4dd04d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dd04d;
    goto bb_004dcdd4;
}
bb_004dcdb3: {
    // 0x004dcdb3: mov ecx, dword ptr [ebx + 0xc]
    uint32_t t46 = static_cast<uint32_t>(ctx.ebx + 0x0000000cu);
    uint32_t t47 = mem.r32(t46);
    ctx.ecx = static_cast<uint32_t>(t47);
    // 0x004dcdb6: sub ecx, edi
    uint32_t t48 = static_cast<uint32_t>(ctx.ecx - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.edi, t48);
    ctx.ecx = static_cast<uint32_t>(t48);
    // 0x004dcdb8: mov eax, 0x2e8ba2e9
    ctx.eax = static_cast<uint32_t>(0x2e8ba2e9u);
    // 0x004dcdbd: imul ecx
    uint64_t t49 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t50 = static_cast<uint32_t>(t49);
    uint32_t t51 = static_cast<uint32_t>(t49 >> 32);
    ctx.eax = static_cast<uint32_t>(t50);
    ctx.edx = static_cast<uint32_t>(t51);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t49);
    // 0x004dcdbf: sar edx, 3
    uint32_t t52 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t53 = recomp_detail::sar<uint32_t>(ctx.edx, t52);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t52, t53);
    ctx.edx = static_cast<uint32_t>(t53);
    // 0x004dcdc2: mov esi, edx
    ctx.esi = static_cast<uint32_t>(ctx.edx);
    // 0x004dcdc4: shr esi, 0x1f
    uint32_t t54 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t55 = recomp_detail::shr<uint32_t>(ctx.esi, t54);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.esi, t54, t55);
    ctx.esi = static_cast<uint32_t>(t55);
    // 0x004dcdc7: add esi, edx
    uint32_t t56 = static_cast<uint32_t>(ctx.esi + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, ctx.edx, t56);
    ctx.esi = static_cast<uint32_t>(t56);
    goto bb_004dcdc9;
}
bb_004dd04d: {
    // 0x004dd04d: cmp dword ptr [ebp - 0x28], 0x10
    uint32_t t57 = static_cast<uint32_t>(ctx.ebp + 0xffffffd8u);
    uint32_t t58 = mem.r32(t57);
    uint32_t t59 = static_cast<uint32_t>(t58 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t58, 0x00000010u, t59);
    // 0x004dd051: jb 0x4dd05f
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004dd05f;
    goto bb_004dd053;
}
bb_004dcdd4: {
    // 0x004dcdd4: test edi, edi
    uint32_t t60 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t60);
    // 0x004dcdd6: jne 0x4dcddc
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dcddc;
    goto bb_004dcdd8;
}
bb_004dd05f: {
    // 0x004dd05f: mov ecx, dword ptr [ebp - 0xc]
    uint32_t t61 = static_cast<uint32_t>(ctx.ebp + 0xfffffff4u);
    uint32_t t62 = mem.r32(t61);
    ctx.ecx = static_cast<uint32_t>(t62);
    // 0x004dd062: mov dword ptr fs:[0], ecx
    uint32_t t63 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t63, ctx.ecx);
    // 0x004dd069: pop ecx
    uint32_t t64 = ctx.esp;
    uint32_t t65 = mem.r32(t64);
    uint32_t t66 = static_cast<uint32_t>(t64 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    ctx.ecx = static_cast<uint32_t>(t65);
    // 0x004dd06a: pop edi
    uint32_t t67 = ctx.esp;
    uint32_t t68 = mem.r32(t67);
    uint32_t t69 = static_cast<uint32_t>(t67 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    ctx.edi = static_cast<uint32_t>(t68);
    // 0x004dd06b: pop esi
    uint32_t t70 = ctx.esp;
    uint32_t t71 = mem.r32(t70);
    uint32_t t72 = static_cast<uint32_t>(t70 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    ctx.esi = static_cast<uint32_t>(t71);
    // 0x004dd06c: pop ebx
    uint32_t t73 = ctx.esp;
    uint32_t t74 = mem.r32(t73);
    uint32_t t75 = static_cast<uint32_t>(t73 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    ctx.ebx = static_cast<uint32_t>(t74);
    // 0x004dd06d: mov ecx, dword ptr [ebp - 0x14]
    uint32_t t76 = static_cast<uint32_t>(ctx.ebp + 0xffffffecu);
    uint32_t t77 = mem.r32(t76);
    ctx.ecx = static_cast<uint32_t>(t77);
    // 0x004dd070: xor ecx, ebp
    uint32_t t78 = static_cast<uint32_t>(ctx.ecx ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t78);
    ctx.ecx = static_cast<uint32_t>(t78);
    // 0x004dd072: call 0x4e02f8
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, 0x004dd077u);
    hle_crt_004e02f8(ctx, mem);
    // 0x004dd077: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x004dd079: pop ebp
    uint32_t t80 = ctx.esp;
    uint32_t t81 = mem.r32(t80);
    uint32_t t82 = static_cast<uint32_t>(t80 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t82);
    ctx.ebp = static_cast<uint32_t>(t81);
    // 0x004dd07a: ret 0xc
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 12u;
    return;
}
bb_004dd053: {
    // 0x004dd053: mov ecx, dword ptr [ebp - 0x3c]
    uint32_t t83 = static_cast<uint32_t>(ctx.ebp + 0xffffffc4u);
    uint32_t t84 = mem.r32(t83);
    ctx.ecx = static_cast<uint32_t>(t84);
    // 0x004dd056: push ecx
    uint32_t t85 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t85);
    mem.w32(t85, ctx.ecx);
    // 0x004dd057: call 0x4e02f3
    uint32_t t86 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t86);
    mem.w32(t86, 0x004dd05cu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dd05c: add esp, 4
    uint32_t t87 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t87);
    ctx.esp = static_cast<uint32_t>(t87);
    goto bb_004dd05f;
}
bb_004dcddc: {
    // 0x004dcddc: mov edx, dword ptr [ebx + 8]
    uint32_t t88 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t89 = mem.r32(t88);
    ctx.edx = static_cast<uint32_t>(t89);
    // 0x004dcddf: sub edx, edi
    uint32_t t90 = static_cast<uint32_t>(ctx.edx - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.edi, t90);
    ctx.edx = static_cast<uint32_t>(t90);
    // 0x004dcde1: mov eax, 0x2e8ba2e9
    ctx.eax = static_cast<uint32_t>(0x2e8ba2e9u);
    // 0x004dcde6: imul edx
    uint64_t t91 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.edx)));
    uint32_t t92 = static_cast<uint32_t>(t91);
    uint32_t t93 = static_cast<uint32_t>(t91 >> 32);
    ctx.eax = static_cast<uint32_t>(t92);
    ctx.edx = static_cast<uint32_t>(t93);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t91);
    // 0x004dcde8: sar edx, 3
    uint32_t t94 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t95 = recomp_detail::sar<uint32_t>(ctx.edx, t94);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t94, t95);
    ctx.edx = static_cast<uint32_t>(t95);
    // 0x004dcdeb: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004dcded: shr eax, 0x1f
    uint32_t t96 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t97 = recomp_detail::shr<uint32_t>(ctx.eax, t96);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t96, t97);
    ctx.eax = static_cast<uint32_t>(t97);
    // 0x004dcdf0: add eax, edx
    uint32_t t98 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t98);
    ctx.eax = static_cast<uint32_t>(t98);
    goto bb_004dcdf2;
}
bb_004dcdd8: {
    // 0x004dcdd8: xor eax, eax
    uint32_t t99 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t99);
    ctx.eax = static_cast<uint32_t>(t99);
    // 0x004dcdda: jmp 0x4dcdf2
}
bb_004dcdf2: {
    // 0x004dcdf2: mov edx, 0x5d1745d
    ctx.edx = static_cast<uint32_t>(0x05d1745du);
    // 0x004dcdf7: sub edx, eax
    uint32_t t100 = static_cast<uint32_t>(ctx.edx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.eax, t100);
    ctx.edx = static_cast<uint32_t>(t100);
    // 0x004dcdf9: cmp edx, ecx
    uint32_t t101 = static_cast<uint32_t>(ctx.edx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ecx, t101);
    // 0x004dcdfb: jae 0x4dce02
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004dce02;
    goto bb_004dcdfd;
}
bb_004dce02: {
    // 0x004dce02: test edi, edi
    uint32_t t102 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t102);
    // 0x004dce04: jne 0x4dce0a
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dce0a;
    goto bb_004dce06;
}
bb_004dcdfd: {
    // 0x004dcdfd: call 0x437280
    uint32_t t103 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    mem.w32(t103, 0x004dce02u);
    sub_00437280(ctx, mem);
    goto bb_004dce02;
}
bb_004dce0a: {
    // 0x004dce0a: mov edx, dword ptr [ebx + 8]
    uint32_t t104 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t105 = mem.r32(t104);
    ctx.edx = static_cast<uint32_t>(t105);
    // 0x004dce0d: sub edx, edi
    uint32_t t106 = static_cast<uint32_t>(ctx.edx - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.edi, t106);
    ctx.edx = static_cast<uint32_t>(t106);
    // 0x004dce0f: mov eax, 0x2e8ba2e9
    ctx.eax = static_cast<uint32_t>(0x2e8ba2e9u);
    // 0x004dce14: imul edx
    uint64_t t107 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.edx)));
    uint32_t t108 = static_cast<uint32_t>(t107);
    uint32_t t109 = static_cast<uint32_t>(t107 >> 32);
    ctx.eax = static_cast<uint32_t>(t108);
    ctx.edx = static_cast<uint32_t>(t109);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t107);
    // 0x004dce16: sar edx, 3
    uint32_t t110 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t111 = recomp_detail::sar<uint32_t>(ctx.edx, t110);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t110, t111);
    ctx.edx = static_cast<uint32_t>(t111);
    // 0x004dce19: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004dce1b: shr eax, 0x1f
    uint32_t t112 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t113 = recomp_detail::shr<uint32_t>(ctx.eax, t112);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t112, t113);
    ctx.eax = static_cast<uint32_t>(t113);
    // 0x004dce1e: add eax, edx
    uint32_t t114 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t114);
    ctx.eax = static_cast<uint32_t>(t114);
    goto bb_004dce20;
}
bb_004dce06: {
    // 0x004dce06: xor eax, eax
    uint32_t t115 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t115);
    ctx.eax = static_cast<uint32_t>(t115);
    // 0x004dce08: jmp 0x4dce20
}
bb_004dce20: {
    // 0x004dce20: add eax, ecx
    uint32_t t116 = static_cast<uint32_t>(ctx.eax + ctx.ecx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.ecx, t116);
    ctx.eax = static_cast<uint32_t>(t116);
    // 0x004dce22: cmp esi, eax
    uint32_t t117 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t117);
    // 0x004dce24: jae 0x4dcf81
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004dcf81;
    goto bb_004dce2a;
}
bb_004dcf81: {
    // 0x004dcf81: mov edi, dword ptr [ebx + 8]
    uint32_t t118 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t119 = mem.r32(t118);
    ctx.edi = static_cast<uint32_t>(t119);
    // 0x004dcf84: mov esi, dword ptr [ebp + 0x10]
    uint32_t t120 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    uint32_t t121 = mem.r32(t120);
    ctx.esi = static_cast<uint32_t>(t121);
    // 0x004dcf87: mov edx, edi
    ctx.edx = static_cast<uint32_t>(ctx.edi);
    // 0x004dcf89: sub edx, esi
    uint32_t t122 = static_cast<uint32_t>(ctx.edx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.esi, t122);
    ctx.edx = static_cast<uint32_t>(t122);
    // 0x004dcf8b: mov eax, 0x2e8ba2e9
    ctx.eax = static_cast<uint32_t>(0x2e8ba2e9u);
    // 0x004dcf90: imul edx
    uint64_t t123 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.edx)));
    uint32_t t124 = static_cast<uint32_t>(t123);
    uint32_t t125 = static_cast<uint32_t>(t123 >> 32);
    ctx.eax = static_cast<uint32_t>(t124);
    ctx.edx = static_cast<uint32_t>(t125);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t123);
    // 0x004dcf92: sar edx, 3
    uint32_t t126 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t127 = recomp_detail::sar<uint32_t>(ctx.edx, t126);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t126, t127);
    ctx.edx = static_cast<uint32_t>(t127);
    // 0x004dcf95: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004dcf97: shr eax, 0x1f
    uint32_t t128 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t129 = recomp_detail::shr<uint32_t>(ctx.eax, t128);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t128, t129);
    ctx.eax = static_cast<uint32_t>(t129);
    // 0x004dcf9a: add eax, edx
    uint32_t t130 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t130);
    ctx.eax = static_cast<uint32_t>(t130);
    // 0x004dcf9c: cmp eax, ecx
    uint32_t t131 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t131);
    // 0x004dcf9e: push edi
    uint32_t t132 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t132);
    mem.w32(t132, ctx.edi);
    // 0x004dcf9f: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x004dcfa1: jae 0x4dd01b
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004dd01b;
    goto bb_004dcfa3;
}
bb_004dce2a: {
    // 0x004dce2a: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004dce2c: shr eax, 1
    uint32_t t133 = static_cast<uint32_t>(0x00000001u & 0x0000001fu);
    uint32_t t134 = recomp_detail::shr<uint32_t>(ctx.eax, t133);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t133, t134);
    ctx.eax = static_cast<uint32_t>(t134);
    // 0x004dce2e: mov edx, 0x5d1745d
    ctx.edx = static_cast<uint32_t>(0x05d1745du);
    // 0x004dce33: sub edx, eax
    uint32_t t135 = static_cast<uint32_t>(ctx.edx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.eax, t135);
    ctx.edx = static_cast<uint32_t>(t135);
    // 0x004dce35: cmp edx, esi
    uint32_t t136 = static_cast<uint32_t>(ctx.edx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.esi, t136);
    // 0x004dce37: jae 0x4dce3d
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004dce3d;
    goto bb_004dce39;
}
bb_004dd01b: {
    // 0x004dd01b: imul eax, eax, 0x2c
    uint64_t t137 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(0x0000002cu)));
    uint32_t t138 = static_cast<uint32_t>(t137);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t137);
    ctx.eax = static_cast<uint32_t>(t138);
    // 0x004dd01e: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004dd020: sub ecx, eax
    uint32_t t139 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t139);
    ctx.ecx = static_cast<uint32_t>(t139);
    // 0x004dd022: push ecx
    uint32_t t140 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t140);
    mem.w32(t140, ctx.ecx);
    // 0x004dd023: mov edx, edi
    ctx.edx = static_cast<uint32_t>(ctx.edi);
    // 0x004dd025: mov dword ptr [ebp - 0x48], eax
    uint32_t t141 = static_cast<uint32_t>(ctx.ebp + 0xffffffb8u);
    mem.w32(t141, ctx.eax);
    // 0x004dd028: mov dword ptr [ebp - 0x44], ecx
    uint32_t t142 = static_cast<uint32_t>(ctx.ebp + 0xffffffbcu);
    mem.w32(t142, ctx.ecx);
    // 0x004dd02b: call 0x4dd150
    uint32_t t143 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t143);
    mem.w32(t143, 0x004dd030u);
    sub_004dd150(ctx, mem);
    // 0x004dd030: mov dword ptr [ebx + 8], eax
    uint32_t t144 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    mem.w32(t144, ctx.eax);
    // 0x004dd033: mov eax, dword ptr [ebp - 0x44]
    uint32_t t145 = static_cast<uint32_t>(ctx.ebp + 0xffffffbcu);
    uint32_t t146 = mem.r32(t145);
    ctx.eax = static_cast<uint32_t>(t146);
    // 0x004dd036: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004dd038: call 0x4dd180
    uint32_t t147 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t147);
    mem.w32(t147, 0x004dd03du);
    sub_004dd180(ctx, mem);
    // 0x004dd03d: mov eax, dword ptr [ebp - 0x48]
    uint32_t t148 = static_cast<uint32_t>(ctx.ebp + 0xffffffb8u);
    uint32_t t149 = mem.r32(t148);
    ctx.eax = static_cast<uint32_t>(t149);
    // 0x004dd040: lea ebx, [eax + esi]
    uint32_t t150 = static_cast<uint32_t>(ctx.eax + ctx.esi);
    ctx.ebx = static_cast<uint32_t>(t150);
    // 0x004dd043: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    goto bb_004dd045;
}
bb_004dcfa3: {
    // 0x004dcfa3: imul eax, eax, 0x2c
    uint64_t t151 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(0x0000002cu)));
    uint32_t t152 = static_cast<uint32_t>(t151);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t151);
    ctx.eax = static_cast<uint32_t>(t152);
    // 0x004dcfa6: lea edx, [eax + esi]
    uint32_t t153 = static_cast<uint32_t>(ctx.eax + ctx.esi);
    ctx.edx = static_cast<uint32_t>(t153);
    // 0x004dcfa9: push esi
    uint32_t t154 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t154);
    mem.w32(t154, ctx.esi);
    // 0x004dcfaa: mov dword ptr [ebp - 0x48], eax
    uint32_t t155 = static_cast<uint32_t>(ctx.ebp + 0xffffffb8u);
    mem.w32(t155, ctx.eax);
    // 0x004dcfad: call 0x4dd150
    uint32_t t156 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t156);
    mem.w32(t156, 0x004dcfb2u);
    sub_004dd150(ctx, mem);
    // 0x004dcfb2: mov byte ptr [ebp - 4], 3
    uint32_t t157 = static_cast<uint32_t>(ctx.ebp + 0xfffffffcu);
    mem.w8(t157, uint8_t{0x03u});
    // 0x004dcfb6: mov edi, dword ptr [ebx + 8]
    uint32_t t158 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t159 = mem.r32(t158);
    ctx.edi = static_cast<uint32_t>(t159);
    // 0x004dcfb9: lea ecx, [ebp - 0x40]
    uint32_t t160 = static_cast<uint32_t>(ctx.ebp + 0xffffffc0u);
    ctx.ecx = static_cast<uint32_t>(t160);
    // 0x004dcfbc: push ecx
    uint32_t t161 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t161);
    mem.w32(t161, ctx.ecx);
    // 0x004dcfbd: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004dcfbf: sub ecx, esi
    uint32_t t162 = static_cast<uint32_t>(ctx.ecx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.esi, t162);
    ctx.ecx = static_cast<uint32_t>(t162);
    // 0x004dcfc1: mov esi, dword ptr [ebp + 8]
    uint32_t t163 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t164 = mem.r32(t163);
    ctx.esi = static_cast<uint32_t>(t164);
    // 0x004dcfc4: mov eax, 0x2e8ba2e9
    ctx.eax = static_cast<uint32_t>(0x2e8ba2e9u);
    // 0x004dcfc9: imul ecx
    uint64_t t165 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t166 = static_cast<uint32_t>(t165);
    uint32_t t167 = static_cast<uint32_t>(t165 >> 32);
    ctx.eax = static_cast<uint32_t>(t166);
    ctx.edx = static_cast<uint32_t>(t167);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t165);
    // 0x004dcfcb: sar edx, 3
    uint32_t t168 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t169 = recomp_detail::sar<uint32_t>(ctx.edx, t168);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t168, t169);
    ctx.edx = static_cast<uint32_t>(t169);
    // 0x004dcfce: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004dcfd0: shr eax, 0x1f
    uint32_t t170 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t171 = recomp_detail::shr<uint32_t>(ctx.eax, t170);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t170, t171);
    ctx.eax = static_cast<uint32_t>(t171);
    // 0x004dcfd3: add eax, edx
    uint32_t t172 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t172);
    ctx.eax = static_cast<uint32_t>(t172);
    // 0x004dcfd5: sub esi, eax
    uint32_t t173 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t173);
    ctx.esi = static_cast<uint32_t>(t173);
    // 0x004dcfd7: call 0x4dd080
    uint32_t t174 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t174);
    mem.w32(t174, 0x004dcfdcu);
    sub_004dd080(ctx, mem);
    // 0x004dcfdc: mov ecx, dword ptr [ebp - 0x48]
    uint32_t t175 = static_cast<uint32_t>(ctx.ebp + 0xffffffb8u);
    uint32_t t176 = mem.r32(t175);
    ctx.ecx = static_cast<uint32_t>(t176);
    // 0x004dcfdf: mov eax, dword ptr [ebp + 0x10]
    uint32_t t177 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    uint32_t t178 = mem.r32(t177);
    ctx.eax = static_cast<uint32_t>(t178);
    // 0x004dcfe2: mov dword ptr [ebp - 4], 0
    uint32_t t179 = static_cast<uint32_t>(ctx.ebp + 0xfffffffcu);
    mem.w32(t179, 0x00000000u);
    // 0x004dcfe9: add dword ptr [ebx + 8], ecx
    uint32_t t180 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t181 = mem.r32(t180);
    uint32_t t182 = static_cast<uint32_t>(t181 + ctx.ecx);
    recomp_detail::update_flags_add<uint32_t>(ctx, t181, ctx.ecx, t182);
    mem.w32(t180, t182);
    // 0x004dcfec: mov ebx, dword ptr [ebx + 8]
    uint32_t t183 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t184 = mem.r32(t183);
    ctx.ebx = static_cast<uint32_t>(t184);
    // 0x004dcfef: sub ebx, ecx
    uint32_t t185 = static_cast<uint32_t>(ctx.ebx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.ecx, t185);
    ctx.ebx = static_cast<uint32_t>(t185);
    // 0x004dcff1: jmp 0x4dd045
    goto bb_004dd045;
}
bb_004dce3d: {
    // 0x004dce3d: add esi, eax
    uint32_t t186 = static_cast<uint32_t>(ctx.esi + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, ctx.eax, t186);
    ctx.esi = static_cast<uint32_t>(t186);
    goto bb_004dce3f;
}
bb_004dce39: {
    // 0x004dce39: xor esi, esi
    uint32_t t187 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t187);
    ctx.esi = static_cast<uint32_t>(t187);
    // 0x004dce3b: jmp 0x4dce3f
    goto bb_004dce3f;
}
bb_004dd045: {
    // 0x004dd045: lea edi, [ebp - 0x40]
    uint32_t t188 = static_cast<uint32_t>(ctx.ebp + 0xffffffc0u);
    ctx.edi = static_cast<uint32_t>(t188);
    // 0x004dd048: call 0x4dd260
    uint32_t t189 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t189);
    mem.w32(t189, 0x004dd04du);
    sub_004dd260(ctx, mem);
    goto bb_004dd04d;
}
bb_004dce3f: {
    // 0x004dce3f: test edi, edi
    uint32_t t190 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t190);
    // 0x004dce41: jne 0x4dce47
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dce47;
    goto bb_004dce43;
}
bb_004dce47: {
    // 0x004dce47: mov edx, dword ptr [ebx + 8]
    uint32_t t191 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t192 = mem.r32(t191);
    ctx.edx = static_cast<uint32_t>(t192);
    // 0x004dce4a: sub edx, edi
    uint32_t t193 = static_cast<uint32_t>(ctx.edx - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.edi, t193);
    ctx.edx = static_cast<uint32_t>(t193);
    // 0x004dce4c: mov eax, 0x2e8ba2e9
    ctx.eax = static_cast<uint32_t>(0x2e8ba2e9u);
    // 0x004dce51: imul edx
    uint64_t t194 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.edx)));
    uint32_t t195 = static_cast<uint32_t>(t194);
    uint32_t t196 = static_cast<uint32_t>(t194 >> 32);
    ctx.eax = static_cast<uint32_t>(t195);
    ctx.edx = static_cast<uint32_t>(t196);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t194);
    // 0x004dce53: sar edx, 3
    uint32_t t197 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t198 = recomp_detail::sar<uint32_t>(ctx.edx, t197);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t197, t198);
    ctx.edx = static_cast<uint32_t>(t198);
    // 0x004dce56: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004dce58: shr eax, 0x1f
    uint32_t t199 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t200 = recomp_detail::shr<uint32_t>(ctx.eax, t199);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t199, t200);
    ctx.eax = static_cast<uint32_t>(t200);
    // 0x004dce5b: add eax, edx
    uint32_t t201 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t201);
    ctx.eax = static_cast<uint32_t>(t201);
    goto bb_004dce5d;
}
bb_004dce43: {
    // 0x004dce43: xor eax, eax
    uint32_t t202 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t202);
    ctx.eax = static_cast<uint32_t>(t202);
    // 0x004dce45: jmp 0x4dce5d
}
bb_004dce5d: {
    // 0x004dce5d: add eax, ecx
    uint32_t t203 = static_cast<uint32_t>(ctx.eax + ctx.ecx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.ecx, t203);
    ctx.eax = static_cast<uint32_t>(t203);
    // 0x004dce5f: cmp esi, eax
    uint32_t t204 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t204);
    // 0x004dce61: jae 0x4dce6f
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004dce6f;
    goto bb_004dce63;
}
bb_004dce6f: {
    // 0x004dce6f: test esi, esi
    uint32_t t205 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t205);
    // 0x004dce71: ja 0x4dce82
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_004dce82;
    goto bb_004dce73;
}
bb_004dce63: {
    // 0x004dce63: mov ecx, ebx
    ctx.ecx = static_cast<uint32_t>(ctx.ebx);
    // 0x004dce65: call 0x4dcb90
    uint32_t t206 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t206);
    mem.w32(t206, 0x004dce6au);
    sub_004dcb90(ctx, mem);
    // 0x004dce6a: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004dce6c: add esi, dword ptr [ebp + 8]
    uint32_t t207 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t208 = mem.r32(t207);
    uint32_t t209 = static_cast<uint32_t>(ctx.esi + t208);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, t208, t209);
    ctx.esi = static_cast<uint32_t>(t209);
    goto bb_004dce6f;
}
bb_004dce82: {
    // 0x004dce82: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004dce84: call 0x4dd1d0
    uint32_t t210 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t210);
    mem.w32(t210, 0x004dce89u);
    sub_004dd1d0(ctx, mem);
    // 0x004dce89: mov dword ptr [ebp - 0x48], eax
    uint32_t t211 = static_cast<uint32_t>(ctx.ebp + 0xffffffb8u);
    mem.w32(t211, ctx.eax);
    goto bb_004dce8c;
}
bb_004dce73: {
    // 0x004dce73: push 0
    uint32_t t212 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t212);
    mem.w32(t212, 0x00000000u);
    // 0x004dce75: call 0x4e0177
    uint32_t t213 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t213);
    mem.w32(t213, 0x004dce7au);
    hle_crt_004e0177(ctx, mem);
    // 0x004dce7a: add esp, 4
    uint32_t t214 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t214);
    ctx.esp = static_cast<uint32_t>(t214);
    // 0x004dce7d: mov dword ptr [ebp - 0x48], eax
    uint32_t t215 = static_cast<uint32_t>(ctx.ebp + 0xffffffb8u);
    mem.w32(t215, ctx.eax);
    // 0x004dce80: jmp 0x4dce8c
}
bb_004dce8c: {
    // 0x004dce8c: mov byte ptr [ebp - 4], 1
    uint32_t t216 = static_cast<uint32_t>(ctx.ebp + 0xfffffffcu);
    mem.w8(t216, uint8_t{0x01u});
    // 0x004dce90: mov edx, dword ptr [ebx + 4]
    uint32_t t217 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    uint32_t t218 = mem.r32(t217);
    ctx.edx = static_cast<uint32_t>(t218);
    // 0x004dce93: mov byte ptr [ebp - 0x44], 0
    uint32_t t219 = static_cast<uint32_t>(ctx.ebp + 0xffffffbcu);
    mem.w8(t219, uint8_t{0x00u});
    // 0x004dce97: mov ecx, dword ptr [ebp - 0x44]
    uint32_t t220 = static_cast<uint32_t>(ctx.ebp + 0xffffffbcu);
    uint32_t t221 = mem.r32(t220);
    ctx.ecx = static_cast<uint32_t>(t221);
    // 0x004dce9a: push ecx
    uint32_t t222 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t222);
    mem.w32(t222, ctx.ecx);
    // 0x004dce9b: mov ecx, dword ptr [ebp - 0x44]
    uint32_t t223 = static_cast<uint32_t>(ctx.ebp + 0xffffffbcu);
    uint32_t t224 = mem.r32(t223);
    ctx.ecx = static_cast<uint32_t>(t224);
    // 0x004dce9e: push ecx
    uint32_t t225 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t225);
    mem.w32(t225, ctx.ecx);
    // 0x004dce9f: mov ecx, dword ptr [ebp + 0x10]
    uint32_t t226 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    uint32_t t227 = mem.r32(t226);
    ctx.ecx = static_cast<uint32_t>(t227);
    // 0x004dcea2: push eax
    uint32_t t228 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t228);
    mem.w32(t228, ctx.eax);
    // 0x004dcea3: mov dword ptr [ebp - 0x4c], eax
    uint32_t t229 = static_cast<uint32_t>(ctx.ebp + 0xffffffb4u);
    mem.w32(t229, ctx.eax);
    // 0x004dcea6: call 0x4dd380
    uint32_t t230 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t230);
    mem.w32(t230, 0x004dceabu);
    sub_004dd380(ctx, mem);
    // 0x004dceab: mov edi, dword ptr [ebp + 8]
    uint32_t t231 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t232 = mem.r32(t231);
    ctx.edi = static_cast<uint32_t>(t232);
    // 0x004dceae: add esp, 0xc
    uint32_t t233 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t233);
    ctx.esp = static_cast<uint32_t>(t233);
    // 0x004dceb1: mov byte ptr [ebp - 0x44], 0
    uint32_t t234 = static_cast<uint32_t>(ctx.ebp + 0xffffffbcu);
    mem.w8(t234, uint8_t{0x00u});
    // 0x004dceb5: mov edx, dword ptr [ebp - 0x44]
    uint32_t t235 = static_cast<uint32_t>(ctx.ebp + 0xffffffbcu);
    uint32_t t236 = mem.r32(t235);
    ctx.edx = static_cast<uint32_t>(t236);
    // 0x004dceb8: mov ecx, dword ptr [ebp - 0x44]
    uint32_t t237 = static_cast<uint32_t>(ctx.ebp + 0xffffffbcu);
    uint32_t t238 = mem.r32(t237);
    ctx.ecx = static_cast<uint32_t>(t238);
    // 0x004dcebb: push edx
    uint32_t t239 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t239);
    mem.w32(t239, ctx.edx);
    // 0x004dcebc: push ecx
    uint32_t t240 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t240);
    mem.w32(t240, ctx.ecx);
    // 0x004dcebd: push eax
    uint32_t t241 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t241);
    mem.w32(t241, ctx.eax);
    // 0x004dcebe: lea ecx, [ebp - 0x40]
    uint32_t t242 = static_cast<uint32_t>(ctx.ebp + 0xffffffc0u);
    ctx.ecx = static_cast<uint32_t>(t242);
    // 0x004dcec1: mov edx, edi
    ctx.edx = static_cast<uint32_t>(ctx.edi);
    // 0x004dcec3: mov dword ptr [ebp - 0x4c], eax
    uint32_t t243 = static_cast<uint32_t>(ctx.ebp + 0xffffffb4u);
    mem.w32(t243, ctx.eax);
    // 0x004dcec6: call 0x4dd2a0
    uint32_t t244 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t244);
    mem.w32(t244, 0x004dcecbu);
    sub_004dd2a0(ctx, mem);
    // 0x004dcecb: mov eax, dword ptr [ebp - 0x4c]
    uint32_t t245 = static_cast<uint32_t>(ctx.ebp + 0xffffffb4u);
    uint32_t t246 = mem.r32(t245);
    ctx.eax = static_cast<uint32_t>(t246);
    // 0x004dcece: mov ecx, dword ptr [ebx + 8]
    uint32_t t247 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t248 = mem.r32(t247);
    ctx.ecx = static_cast<uint32_t>(t248);
    // 0x004dced1: mov edx, edi
    ctx.edx = static_cast<uint32_t>(ctx.edi);
    // 0x004dced3: imul edx, edx, 0x2c
    uint64_t t249 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.edx)) * static_cast<int64_t>(static_cast<int32_t>(0x0000002cu)));
    uint32_t t250 = static_cast<uint32_t>(t249);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t249);
    ctx.edx = static_cast<uint32_t>(t250);
    // 0x004dced6: add eax, edx
    uint32_t t251 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t251);
    ctx.eax = static_cast<uint32_t>(t251);
    // 0x004dced8: add esp, 0xc
    uint32_t t252 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t252);
    ctx.esp = static_cast<uint32_t>(t252);
    // 0x004dcedb: mov byte ptr [ebp - 0x44], 0
    uint32_t t253 = static_cast<uint32_t>(ctx.ebp + 0xffffffbcu);
    mem.w8(t253, uint8_t{0x00u});
    // 0x004dcedf: mov edx, dword ptr [ebp - 0x44]
    uint32_t t254 = static_cast<uint32_t>(ctx.ebp + 0xffffffbcu);
    uint32_t t255 = mem.r32(t254);
    ctx.edx = static_cast<uint32_t>(t255);
    // 0x004dcee2: push edx
    uint32_t t256 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t256);
    mem.w32(t256, ctx.edx);
    // 0x004dcee3: mov edx, dword ptr [ebp - 0x44]
    uint32_t t257 = static_cast<uint32_t>(ctx.ebp + 0xffffffbcu);
    uint32_t t258 = mem.r32(t257);
    ctx.edx = static_cast<uint32_t>(t258);
    // 0x004dcee6: push edx
    uint32_t t259 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t259);
    mem.w32(t259, ctx.edx);
    // 0x004dcee7: mov edx, dword ptr [ebp + 0x10]
    uint32_t t260 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    uint32_t t261 = mem.r32(t260);
    ctx.edx = static_cast<uint32_t>(t261);
    // 0x004dceea: push eax
    uint32_t t262 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t262);
    mem.w32(t262, ctx.eax);
    // 0x004dceeb: mov dword ptr [ebp - 0x4c], eax
    uint32_t t263 = static_cast<uint32_t>(ctx.ebp + 0xffffffb4u);
    mem.w32(t263, ctx.eax);
    // 0x004dceee: call 0x4dd380
    uint32_t t264 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t264);
    mem.w32(t264, 0x004dcef3u);
    sub_004dd380(ctx, mem);
    // 0x004dcef3: mov ecx, dword ptr [ebx + 4]
    uint32_t t265 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    uint32_t t266 = mem.r32(t265);
    ctx.ecx = static_cast<uint32_t>(t266);
    // 0x004dcef6: add esp, 0xc
    uint32_t t267 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t267);
    ctx.esp = static_cast<uint32_t>(t267);
    // 0x004dcef9: test ecx, ecx
    uint32_t t268 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t268);
    // 0x004dcefb: jne 0x4dcf01
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dcf01;
    goto bb_004dcefd;
}
bb_004dcf01: {
    // 0x004dcf01: mov edx, dword ptr [ebx + 8]
    uint32_t t269 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t270 = mem.r32(t269);
    ctx.edx = static_cast<uint32_t>(t270);
    // 0x004dcf04: sub edx, ecx
    uint32_t t271 = static_cast<uint32_t>(ctx.edx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ecx, t271);
    ctx.edx = static_cast<uint32_t>(t271);
    // 0x004dcf06: mov eax, 0x2e8ba2e9
    ctx.eax = static_cast<uint32_t>(0x2e8ba2e9u);
    // 0x004dcf0b: imul edx
    uint64_t t272 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.edx)));
    uint32_t t273 = static_cast<uint32_t>(t272);
    uint32_t t274 = static_cast<uint32_t>(t272 >> 32);
    ctx.eax = static_cast<uint32_t>(t273);
    ctx.edx = static_cast<uint32_t>(t274);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t272);
    // 0x004dcf0d: sar edx, 3
    uint32_t t275 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t276 = recomp_detail::sar<uint32_t>(ctx.edx, t275);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t275, t276);
    ctx.edx = static_cast<uint32_t>(t276);
    // 0x004dcf10: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004dcf12: shr eax, 0x1f
    uint32_t t277 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t278 = recomp_detail::shr<uint32_t>(ctx.eax, t277);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t277, t278);
    ctx.eax = static_cast<uint32_t>(t278);
    // 0x004dcf15: add eax, edx
    uint32_t t279 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t279);
    ctx.eax = static_cast<uint32_t>(t279);
    goto bb_004dcf17;
}
bb_004dcefd: {
    // 0x004dcefd: xor eax, eax
    uint32_t t280 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t280);
    ctx.eax = static_cast<uint32_t>(t280);
    // 0x004dceff: jmp 0x4dcf17
}
bb_004dcf17: {
    // 0x004dcf17: add edi, eax
    uint32_t t281 = static_cast<uint32_t>(ctx.edi + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, ctx.eax, t281);
    ctx.edi = static_cast<uint32_t>(t281);
    // 0x004dcf19: test ecx, ecx
    uint32_t t282 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t282);
    // 0x004dcf1b: mov dword ptr [ebp + 8], edi
    uint32_t t283 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    mem.w32(t283, ctx.edi);
    // 0x004dcf1e: je 0x4dcf40
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dcf40;
    goto bb_004dcf20;
}
bb_004dcf40: {
    // 0x004dcf40: mov eax, dword ptr [ebp - 0x48]
    uint32_t t284 = static_cast<uint32_t>(ctx.ebp + 0xffffffb8u);
    uint32_t t285 = mem.r32(t284);
    ctx.eax = static_cast<uint32_t>(t285);
    // 0x004dcf43: imul esi, esi, 0x2c
    uint64_t t286 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.esi)) * static_cast<int64_t>(static_cast<int32_t>(0x0000002cu)));
    uint32_t t287 = static_cast<uint32_t>(t286);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t286);
    ctx.esi = static_cast<uint32_t>(t287);
    // 0x004dcf46: imul edi, edi, 0x2c
    uint64_t t288 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.edi)) * static_cast<int64_t>(static_cast<int32_t>(0x0000002cu)));
    uint32_t t289 = static_cast<uint32_t>(t288);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t288);
    ctx.edi = static_cast<uint32_t>(t289);
    // 0x004dcf49: add esi, eax
    uint32_t t290 = static_cast<uint32_t>(ctx.esi + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, ctx.eax, t290);
    ctx.esi = static_cast<uint32_t>(t290);
    // 0x004dcf4b: add edi, eax
    uint32_t t291 = static_cast<uint32_t>(ctx.edi + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, ctx.eax, t291);
    ctx.edi = static_cast<uint32_t>(t291);
    // 0x004dcf4d: mov dword ptr [ebx + 0xc], esi
    uint32_t t292 = static_cast<uint32_t>(ctx.ebx + 0x0000000cu);
    mem.w32(t292, ctx.esi);
    // 0x004dcf50: mov dword ptr [ebx + 8], edi
    uint32_t t293 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    mem.w32(t293, ctx.edi);
    // 0x004dcf53: mov dword ptr [ebx + 4], eax
    uint32_t t294 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    mem.w32(t294, ctx.eax);
    // 0x004dcf56: jmp 0x4dd04d
    goto bb_004dd04d;
}
bb_004dcf20: {
    // 0x004dcf20: mov eax, dword ptr [ebp - 0x44]
    uint32_t t295 = static_cast<uint32_t>(ctx.ebp + 0xffffffbcu);
    uint32_t t296 = mem.r32(t295);
    ctx.eax = static_cast<uint32_t>(t296);
    // 0x004dcf23: mov edi, dword ptr [ebx + 8]
    uint32_t t297 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t298 = mem.r32(t297);
    ctx.edi = static_cast<uint32_t>(t298);
    // 0x004dcf26: push eax
    uint32_t t299 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t299);
    mem.w32(t299, ctx.eax);
    // 0x004dcf27: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x004dcf29: call 0x4dd220
    uint32_t t300 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t300);
    mem.w32(t300, 0x004dcf2eu);
    sub_004dd220(ctx, mem);
    // 0x004dcf2e: mov ecx, dword ptr [ebx + 4]
    uint32_t t301 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    uint32_t t302 = mem.r32(t301);
    ctx.ecx = static_cast<uint32_t>(t302);
    // 0x004dcf31: add esp, 4
    uint32_t t303 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t303);
    ctx.esp = static_cast<uint32_t>(t303);
    // 0x004dcf34: push ecx
    uint32_t t304 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t304);
    mem.w32(t304, ctx.ecx);
    // 0x004dcf35: call 0x4e02f3
    uint32_t t305 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t305);
    mem.w32(t305, 0x004dcf3au);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dcf3a: mov edi, dword ptr [ebp + 8]
    uint32_t t306 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t307 = mem.r32(t306);
    ctx.edi = static_cast<uint32_t>(t307);
    // 0x004dcf3d: add esp, 4
    uint32_t t308 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t308);
    ctx.esp = static_cast<uint32_t>(t308);
    goto bb_004dcf40;
}
}

// sub_004dd080 | subsystem=FilePacFunc | canonical | 1 blocks | 15 insns
void sub_004dd080(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dd080: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x004dd081: mov ecx, dword ptr [esp + 8]
    uint32_t t1 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t2 = mem.r32(t1);
    ctx.ecx = static_cast<uint32_t>(t2);
    // 0x004dd085: mov byte ptr [esp], 0
    mem.w8(ctx.esp, uint8_t{0x00u});
    // 0x004dd089: mov eax, dword ptr [esp]
    uint32_t t3 = mem.r32(ctx.esp);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004dd08c: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x004dd08d: push ecx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ecx);
    // 0x004dd08e: mov ecx, dword ptr [esp + 0x10]
    uint32_t t6 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t7 = mem.r32(t6);
    ctx.ecx = static_cast<uint32_t>(t7);
    // 0x004dd092: push edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edi);
    // 0x004dd093: mov edx, esi
    ctx.edx = static_cast<uint32_t>(ctx.esi);
    // 0x004dd095: call 0x4dd2a0
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x004dd09au);
    sub_004dd2a0(ctx, mem);
    // 0x004dd09a: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004dd09c: imul eax, eax, 0x2c
    uint64_t t10 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(0x0000002cu)));
    uint32_t t11 = static_cast<uint32_t>(t10);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t10);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x004dd09f: add eax, edi
    uint32_t t12 = static_cast<uint32_t>(ctx.eax + ctx.edi);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edi, t12);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x004dd0a1: add esp, 0x10
    uint32_t t13 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t13);
    ctx.esp = static_cast<uint32_t>(t13);
    // 0x004dd0a4: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
}

// sub_004dd0b0 | subsystem=FilePacFunc | canonical | 1 blocks | 28 insns
void sub_004dd0b0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dd0b0: sub esp, 8
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000008u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000008u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x004dd0b3: push ebx
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebx);
    // 0x004dd0b4: mov ebx, eax
    ctx.ebx = static_cast<uint32_t>(ctx.eax);
    // 0x004dd0b6: xor al, al
    uint8_t t2 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) ^ static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t2);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t2));
    // 0x004dd0b8: mov byte ptr [esp + 8], al
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    mem.w8(t3, recomp_detail::r8l(ctx.eax));
    // 0x004dd0bc: mov ecx, dword ptr [esp + 8]
    uint32_t t4 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t5 = mem.r32(t4);
    ctx.ecx = static_cast<uint32_t>(t5);
    // 0x004dd0c0: mov edx, dword ptr [esp + 8]
    uint32_t t6 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t7 = mem.r32(t6);
    ctx.edx = static_cast<uint32_t>(t7);
    // 0x004dd0c4: mov byte ptr [esp + 4], al
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    mem.w8(t8, recomp_detail::r8l(ctx.eax));
    // 0x004dd0c8: mov eax, dword ptr [esp + 4]
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint32_t t10 = mem.r32(t9);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x004dd0cc: push eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.eax);
    // 0x004dd0cd: push ecx
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.ecx);
    // 0x004dd0ce: push edx
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, ctx.edx);
    // 0x004dd0cf: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004dd0d1: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004dd0d3: call 0x4dd330
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x004dd0d8u);
    sub_004dd330(ctx, mem);
    // 0x004dd0d8: sub ebx, edi
    uint32_t t15 = static_cast<uint32_t>(ctx.ebx - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.edi, t15);
    ctx.ebx = static_cast<uint32_t>(t15);
    // 0x004dd0da: mov eax, 0x2e8ba2e9
    ctx.eax = static_cast<uint32_t>(0x2e8ba2e9u);
    // 0x004dd0df: imul ebx
    uint64_t t16 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ebx)));
    uint32_t t17 = static_cast<uint32_t>(t16);
    uint32_t t18 = static_cast<uint32_t>(t16 >> 32);
    ctx.eax = static_cast<uint32_t>(t17);
    ctx.edx = static_cast<uint32_t>(t18);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t16);
    // 0x004dd0e1: sar edx, 3
    uint32_t t19 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t20 = recomp_detail::sar<uint32_t>(ctx.edx, t19);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t19, t20);
    ctx.edx = static_cast<uint32_t>(t20);
    // 0x004dd0e4: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004dd0e6: shr eax, 0x1f
    uint32_t t21 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t22 = recomp_detail::shr<uint32_t>(ctx.eax, t21);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t21, t22);
    ctx.eax = static_cast<uint32_t>(t22);
    // 0x004dd0e9: add eax, edx
    uint32_t t23 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t23);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x004dd0eb: imul eax, eax, 0x2c
    uint64_t t24 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(0x0000002cu)));
    uint32_t t25 = static_cast<uint32_t>(t24);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t24);
    ctx.eax = static_cast<uint32_t>(t25);
    // 0x004dd0ee: add esp, 0xc
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t26);
    ctx.esp = static_cast<uint32_t>(t26);
    // 0x004dd0f1: add eax, esi
    uint32_t t27 = static_cast<uint32_t>(ctx.eax + ctx.esi);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.esi, t27);
    ctx.eax = static_cast<uint32_t>(t27);
    // 0x004dd0f3: pop ebx
    uint32_t t28 = ctx.esp;
    uint32_t t29 = mem.r32(t28);
    uint32_t t30 = static_cast<uint32_t>(t28 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    ctx.ebx = static_cast<uint32_t>(t29);
    // 0x004dd0f4: add esp, 8
    uint32_t t31 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t31);
    ctx.esp = static_cast<uint32_t>(t31);
    // 0x004dd0f7: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004dd150 | subsystem=FilePacFunc | canonical | 1 blocks | 12 insns
void sub_004dd150(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dd150: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x004dd151: mov ecx, dword ptr [esp + 0xc]
    uint32_t t1 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t2 = mem.r32(t1);
    ctx.ecx = static_cast<uint32_t>(t2);
    // 0x004dd155: mov byte ptr [esp], 0
    mem.w8(ctx.esp, uint8_t{0x00u});
    // 0x004dd159: mov eax, dword ptr [esp]
    uint32_t t3 = mem.r32(ctx.esp);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004dd15c: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x004dd15d: push ecx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ecx);
    // 0x004dd15e: mov ecx, dword ptr [esp + 0x14]
    uint32_t t6 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t7 = mem.r32(t6);
    ctx.ecx = static_cast<uint32_t>(t7);
    // 0x004dd162: push edx
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edx);
    // 0x004dd163: mov edx, dword ptr [esp + 0x14]
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t10 = mem.r32(t9);
    ctx.edx = static_cast<uint32_t>(t10);
    // 0x004dd167: call 0x4dd380
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0x004dd16cu);
    sub_004dd380(ctx, mem);
    // 0x004dd16c: add esp, 0x10
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t12);
    ctx.esp = static_cast<uint32_t>(t12);
    // 0x004dd16f: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
}

// sub_004dd180 | subsystem=FilePacFunc | canonical | 1 blocks | 33 insns
void sub_004dd180(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dd180: sub esp, 8
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000008u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000008u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x004dd183: push ebx
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebx);
    // 0x004dd184: push esi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.esi);
    // 0x004dd185: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004dd187: xor al, al
    uint8_t t3 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) ^ static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t3);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t3));
    // 0x004dd189: mov byte ptr [esp + 0xc], al
    uint32_t t4 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w8(t4, recomp_detail::r8l(ctx.eax));
    // 0x004dd18d: mov edx, dword ptr [esp + 0xc]
    uint32_t t5 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t6 = mem.r32(t5);
    ctx.edx = static_cast<uint32_t>(t6);
    // 0x004dd191: mov byte ptr [esp + 8], al
    uint32_t t7 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    mem.w8(t7, recomp_detail::r8l(ctx.eax));
    // 0x004dd195: mov eax, dword ptr [esp + 8]
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t9 = mem.r32(t8);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x004dd199: mov ebx, ecx
    ctx.ebx = static_cast<uint32_t>(ctx.ecx);
    // 0x004dd19b: mov ecx, dword ptr [esp + 0xc]
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t11 = mem.r32(t10);
    ctx.ecx = static_cast<uint32_t>(t11);
    // 0x004dd19f: push eax
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.eax);
    // 0x004dd1a0: push ecx
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, ctx.ecx);
    // 0x004dd1a1: push edx
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, ctx.edx);
    // 0x004dd1a2: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x004dd1a4: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004dd1a6: call 0x4dd480
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x004dd1abu);
    sub_004dd480(ctx, mem);
    // 0x004dd1ab: sub esi, ebx
    uint32_t t16 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t16);
    ctx.esi = static_cast<uint32_t>(t16);
    // 0x004dd1ad: mov eax, 0x2e8ba2e9
    ctx.eax = static_cast<uint32_t>(0x2e8ba2e9u);
    // 0x004dd1b2: imul esi
    uint64_t t17 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.esi)));
    uint32_t t18 = static_cast<uint32_t>(t17);
    uint32_t t19 = static_cast<uint32_t>(t17 >> 32);
    ctx.eax = static_cast<uint32_t>(t18);
    ctx.edx = static_cast<uint32_t>(t19);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t17);
    // 0x004dd1b4: sar edx, 3
    uint32_t t20 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t21 = recomp_detail::sar<uint32_t>(ctx.edx, t20);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t20, t21);
    ctx.edx = static_cast<uint32_t>(t21);
    // 0x004dd1b7: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004dd1b9: shr eax, 0x1f
    uint32_t t22 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t23 = recomp_detail::shr<uint32_t>(ctx.eax, t22);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t22, t23);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x004dd1bc: add eax, edx
    uint32_t t24 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t24);
    ctx.eax = static_cast<uint32_t>(t24);
    // 0x004dd1be: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x004dd1c0: imul ecx, ecx, 0x2c
    uint64_t t25 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)) * static_cast<int64_t>(static_cast<int32_t>(0x0000002cu)));
    uint32_t t26 = static_cast<uint32_t>(t25);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t25);
    ctx.ecx = static_cast<uint32_t>(t26);
    // 0x004dd1c3: add esp, 0xc
    uint32_t t27 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t27);
    ctx.esp = static_cast<uint32_t>(t27);
    // 0x004dd1c6: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x004dd1c8: pop esi
    uint32_t t28 = ctx.esp;
    uint32_t t29 = mem.r32(t28);
    uint32_t t30 = static_cast<uint32_t>(t28 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    ctx.esi = static_cast<uint32_t>(t29);
    // 0x004dd1c9: sub eax, ecx
    uint32_t t31 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t31);
    ctx.eax = static_cast<uint32_t>(t31);
    // 0x004dd1cb: pop ebx
    uint32_t t32 = ctx.esp;
    uint32_t t33 = mem.r32(t32);
    uint32_t t34 = static_cast<uint32_t>(t32 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    ctx.ebx = static_cast<uint32_t>(t33);
    // 0x004dd1cc: add esp, 8
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t35);
    ctx.esp = static_cast<uint32_t>(t35);
    // 0x004dd1cf: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004dd1d0 | subsystem=FilePacFunc | canonical | 3 blocks | 22 insns
void sub_004dd1d0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dd1d0: or eax, 0xffffffff
    uint32_t t0 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x004dd1d3: xor edx, edx
    uint32_t t1 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.edx = static_cast<uint32_t>(t1);
    // 0x004dd1d5: div ecx
    uint64_t t2 = ((static_cast<uint64_t>(ctx.edx) << 32) | static_cast<uint64_t>(ctx.eax));
    uint32_t t3 = recomp_detail::div64_u(t2, ctx.ecx);
    uint32_t t4 = recomp_detail::mod64_u(t2, ctx.ecx);
    ctx.eax = static_cast<uint32_t>(t3);
    ctx.edx = static_cast<uint32_t>(t4);
    // 0x004dd1d7: sub esp, 0x10
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000010u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x004dd1da: cmp eax, 0x2c
    uint32_t t6 = static_cast<uint32_t>(ctx.eax - 0x0000002cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x0000002cu, t6);
    // 0x004dd1dd: jae 0x4dd20b
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004dd20b;
    goto bb_004dd1df;
}
bb_004dd20b: {
    // 0x004dd20b: imul ecx, ecx, 0x2c
    uint64_t t7 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)) * static_cast<int64_t>(static_cast<int32_t>(0x0000002cu)));
    uint32_t t8 = static_cast<uint32_t>(t7);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t7);
    ctx.ecx = static_cast<uint32_t>(t8);
    // 0x004dd20e: push ecx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ecx);
    // 0x004dd20f: call 0x4e0177
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x004dd214u);
    hle_crt_004e0177(ctx, mem);
    // 0x004dd214: add esp, 4
    uint32_t t11 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t11);
    ctx.esp = static_cast<uint32_t>(t11);
    // 0x004dd217: add esp, 0x10
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t12);
    ctx.esp = static_cast<uint32_t>(t12);
    // 0x004dd21a: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004dd1df: {
    // 0x004dd1df: lea eax, [esp]
    ctx.eax = static_cast<uint32_t>(ctx.esp);
    // 0x004dd1e2: push eax
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, ctx.eax);
    // 0x004dd1e3: lea ecx, [esp + 8]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.ecx = static_cast<uint32_t>(t14);
    // 0x004dd1e7: mov dword ptr [esp + 4], 0
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    mem.w32(t15, 0x00000000u);
    // 0x004dd1ef: call 0x4e07d5
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x004dd1f4u);
    hle_crt_004e07d5(ctx, mem);
    // 0x004dd1f4: push 0x543b60
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x00543b60u);
    // 0x004dd1f9: lea ecx, [esp + 8]
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.ecx = static_cast<uint32_t>(t18);
    // 0x004dd1fd: push ecx
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, ctx.ecx);
    // 0x004dd1fe: mov dword ptr [esp + 0xc], 0x51b5e0
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t20, 0x0051b5e0u);
    // 0x004dd206: call 0x4e3e1b
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x004dd20bu);
    hle_crt_004e3e1b(ctx, mem);
    goto bb_004dd20b;
}
}

// sub_004dd220 | subsystem=FilePacFunc | canonical | 7 blocks | 22 insns
void sub_004dd220(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dd220: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x004dd221: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004dd223: cmp esi, edi
    uint32_t t1 = static_cast<uint32_t>(ctx.esi - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edi, t1);
    // 0x004dd225: je 0x4dd257
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dd257;
    goto bb_004dd227;
}
bb_004dd257: {
    // 0x004dd257: pop esi
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.esi = static_cast<uint32_t>(t3);
    // 0x004dd258: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004dd227: {
    // 0x004dd227: push ebx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ebx);
    // 0x004dd228: xor ebx, ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t6);
    ctx.ebx = static_cast<uint32_t>(t6);
    // 0x004dd22a: lea ebx, [ebx]
    ctx.ebx = static_cast<uint32_t>(ctx.ebx);
}
bb_004dd230: {
    // 0x004dd230: cmp dword ptr [esi + 0x18], 0x10
    uint32_t t7 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    uint32_t t8 = mem.r32(t7);
    uint32_t t9 = static_cast<uint32_t>(t8 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t8, 0x00000010u, t9);
    // 0x004dd234: jb 0x4dd242
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004dd242;
    goto bb_004dd236;
}
bb_004dd242: {
    // 0x004dd242: mov dword ptr [esi + 0x18], 0xf
    uint32_t t10 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    mem.w32(t10, 0x0000000fu);
    // 0x004dd249: mov dword ptr [esi + 0x14], ebx
    uint32_t t11 = static_cast<uint32_t>(ctx.esi + 0x00000014u);
    mem.w32(t11, ctx.ebx);
    // 0x004dd24c: mov byte ptr [esi + 4], bl
    uint32_t t12 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w8(t12, recomp_detail::r8l(ctx.ebx));
    // 0x004dd24f: add esi, 0x2c
    uint32_t t13 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x0000002cu, t13);
    ctx.esi = static_cast<uint32_t>(t13);
    // 0x004dd252: cmp esi, edi
    uint32_t t14 = static_cast<uint32_t>(ctx.esi - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edi, t14);
    // 0x004dd254: jne 0x4dd230
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dd230;
    goto bb_004dd256;
}
bb_004dd236: {
    // 0x004dd236: mov eax, dword ptr [esi + 4]
    uint32_t t15 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t16 = mem.r32(t15);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x004dd239: push eax
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, ctx.eax);
    // 0x004dd23a: call 0x4e02f3
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x004dd23fu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dd23f: add esp, 4
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t19);
    ctx.esp = static_cast<uint32_t>(t19);
    goto bb_004dd242;
}
bb_004dd256: {
    // 0x004dd256: pop ebx
    uint32_t t20 = ctx.esp;
    uint32_t t21 = mem.r32(t20);
    uint32_t t22 = static_cast<uint32_t>(t20 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    ctx.ebx = static_cast<uint32_t>(t21);
    goto bb_004dd257;
}
}

// sub_004dd260 | subsystem=FilePacFunc | canonical | 3 blocks | 22 insns
void sub_004dd260(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dd260: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x004dd261: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004dd263: cmp esi, ebx
    uint32_t t1 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t1);
    // 0x004dd265: je 0x4dd292
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dd292;
    goto bb_004dd267;
}
bb_004dd292: {
    // 0x004dd292: pop esi
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.esi = static_cast<uint32_t>(t3);
    // 0x004dd293: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004dd267: {
    // 0x004dd267: push -1
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, 0xffffffffu);
    // 0x004dd269: push 0
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x00000000u);
    // 0x004dd26b: push edi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.edi);
    // 0x004dd26c: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004dd26e: call 0x4079d0
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x004dd273u);
    sub_004079d0(ctx, mem);
    // 0x004dd273: mov eax, dword ptr [edi + 0x1c]
    uint32_t t9 = static_cast<uint32_t>(ctx.edi + 0x0000001cu);
    uint32_t t10 = mem.r32(t9);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x004dd276: mov dword ptr [esi + 0x1c], eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esi + 0x0000001cu);
    mem.w32(t11, ctx.eax);
    // 0x004dd279: mov ecx, dword ptr [edi + 0x20]
    uint32_t t12 = static_cast<uint32_t>(ctx.edi + 0x00000020u);
    uint32_t t13 = mem.r32(t12);
    ctx.ecx = static_cast<uint32_t>(t13);
    // 0x004dd27c: mov dword ptr [esi + 0x20], ecx
    uint32_t t14 = static_cast<uint32_t>(ctx.esi + 0x00000020u);
    mem.w32(t14, ctx.ecx);
    // 0x004dd27f: mov edx, dword ptr [edi + 0x24]
    uint32_t t15 = static_cast<uint32_t>(ctx.edi + 0x00000024u);
    uint32_t t16 = mem.r32(t15);
    ctx.edx = static_cast<uint32_t>(t16);
    // 0x004dd282: mov dword ptr [esi + 0x24], edx
    uint32_t t17 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    mem.w32(t17, ctx.edx);
    // 0x004dd285: mov eax, dword ptr [edi + 0x28]
    uint32_t t18 = static_cast<uint32_t>(ctx.edi + 0x00000028u);
    uint32_t t19 = mem.r32(t18);
    ctx.eax = static_cast<uint32_t>(t19);
    // 0x004dd288: mov dword ptr [esi + 0x28], eax
    uint32_t t20 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    mem.w32(t20, ctx.eax);
    // 0x004dd28b: add esi, 0x2c
    uint32_t t21 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x0000002cu, t21);
    ctx.esi = static_cast<uint32_t>(t21);
    // 0x004dd28e: cmp esi, ebx
    uint32_t t22 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t22);
    // 0x004dd290: jne 0x4dd267
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dd267;
    goto bb_004dd292;
}
}

// sub_004dd330 | subsystem=FilePacFunc | canonical | 5 blocks | 28 insns
void sub_004dd330(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dd330: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x004dd331: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004dd333: cmp esi, ebx
    uint32_t t1 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t1);
    // 0x004dd335: push edi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.edi);
    // 0x004dd336: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x004dd338: je 0x4dd370
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dd370;
    goto bb_004dd33a;
}
bb_004dd370: {
    // 0x004dd370: pop edi
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.edi = static_cast<uint32_t>(t4);
    // 0x004dd371: pop esi
    uint32_t t6 = ctx.esp;
    uint32_t t7 = mem.r32(t6);
    uint32_t t8 = static_cast<uint32_t>(t6 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    ctx.esi = static_cast<uint32_t>(t7);
    // 0x004dd372: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004dd33a: {
    // 0x004dd33a: lea ebx, [ebx]
    ctx.ebx = static_cast<uint32_t>(ctx.ebx);
}
bb_004dd340: {
    // 0x004dd340: push -1
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0xffffffffu);
    // 0x004dd342: push 0
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x00000000u);
    // 0x004dd344: push esi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.esi);
    // 0x004dd345: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004dd347: call 0x4079d0
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x004dd34cu);
    sub_004079d0(ctx, mem);
    // 0x004dd34c: mov eax, dword ptr [esi + 0x1c]
    uint32_t t13 = static_cast<uint32_t>(ctx.esi + 0x0000001cu);
    uint32_t t14 = mem.r32(t13);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x004dd34f: mov dword ptr [edi + 0x1c], eax
    uint32_t t15 = static_cast<uint32_t>(ctx.edi + 0x0000001cu);
    mem.w32(t15, ctx.eax);
    // 0x004dd352: mov ecx, dword ptr [esi + 0x20]
    uint32_t t16 = static_cast<uint32_t>(ctx.esi + 0x00000020u);
    uint32_t t17 = mem.r32(t16);
    ctx.ecx = static_cast<uint32_t>(t17);
    // 0x004dd355: mov dword ptr [edi + 0x20], ecx
    uint32_t t18 = static_cast<uint32_t>(ctx.edi + 0x00000020u);
    mem.w32(t18, ctx.ecx);
    // 0x004dd358: mov edx, dword ptr [esi + 0x24]
    uint32_t t19 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    uint32_t t20 = mem.r32(t19);
    ctx.edx = static_cast<uint32_t>(t20);
    // 0x004dd35b: mov dword ptr [edi + 0x24], edx
    uint32_t t21 = static_cast<uint32_t>(ctx.edi + 0x00000024u);
    mem.w32(t21, ctx.edx);
    // 0x004dd35e: mov eax, dword ptr [esi + 0x28]
    uint32_t t22 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    uint32_t t23 = mem.r32(t22);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x004dd361: mov dword ptr [edi + 0x28], eax
    uint32_t t24 = static_cast<uint32_t>(ctx.edi + 0x00000028u);
    mem.w32(t24, ctx.eax);
    // 0x004dd364: add esi, 0x2c
    uint32_t t25 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x0000002cu, t25);
    ctx.esi = static_cast<uint32_t>(t25);
    // 0x004dd367: add edi, 0x2c
    uint32_t t26 = static_cast<uint32_t>(ctx.edi + 0x0000002cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x0000002cu, t26);
    ctx.edi = static_cast<uint32_t>(t26);
    // 0x004dd36a: cmp esi, ebx
    uint32_t t27 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t27);
    // 0x004dd36c: jne 0x4dd340
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dd340;
}
{
    // 0x004dd36e: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    goto bb_004dd370;
}
}

// sub_004dd480 | subsystem=FilePacFunc | canonical | 5 blocks | 28 insns
void sub_004dd480(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dd480: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x004dd481: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004dd483: cmp ebx, esi
    uint32_t t1 = static_cast<uint32_t>(ctx.ebx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.esi, t1);
    // 0x004dd485: push edi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.edi);
    // 0x004dd486: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x004dd488: je 0x4dd4c0
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dd4c0;
    goto bb_004dd48a;
}
bb_004dd4c0: {
    // 0x004dd4c0: pop edi
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.edi = static_cast<uint32_t>(t4);
    // 0x004dd4c1: pop esi
    uint32_t t6 = ctx.esp;
    uint32_t t7 = mem.r32(t6);
    uint32_t t8 = static_cast<uint32_t>(t6 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    ctx.esi = static_cast<uint32_t>(t7);
    // 0x004dd4c2: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004dd48a: {
    // 0x004dd48a: lea ebx, [ebx]
    ctx.ebx = static_cast<uint32_t>(ctx.ebx);
}
bb_004dd490: {
    // 0x004dd490: push -1
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0xffffffffu);
    // 0x004dd492: push 0
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x00000000u);
    // 0x004dd494: sub esi, 0x2c
    uint32_t t11 = static_cast<uint32_t>(ctx.esi - 0x0000002cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x0000002cu, t11);
    ctx.esi = static_cast<uint32_t>(t11);
    // 0x004dd497: sub edi, 0x2c
    uint32_t t12 = static_cast<uint32_t>(ctx.edi - 0x0000002cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, 0x0000002cu, t12);
    ctx.edi = static_cast<uint32_t>(t12);
    // 0x004dd49a: push esi
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, ctx.esi);
    // 0x004dd49b: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004dd49d: call 0x4079d0
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x004dd4a2u);
    sub_004079d0(ctx, mem);
    // 0x004dd4a2: cmp esi, ebx
    uint32_t t15 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t15);
    // 0x004dd4a4: mov eax, dword ptr [esi + 0x1c]
    uint32_t t16 = static_cast<uint32_t>(ctx.esi + 0x0000001cu);
    uint32_t t17 = mem.r32(t16);
    ctx.eax = static_cast<uint32_t>(t17);
    // 0x004dd4a7: mov dword ptr [edi + 0x1c], eax
    uint32_t t18 = static_cast<uint32_t>(ctx.edi + 0x0000001cu);
    mem.w32(t18, ctx.eax);
    // 0x004dd4aa: mov ecx, dword ptr [esi + 0x20]
    uint32_t t19 = static_cast<uint32_t>(ctx.esi + 0x00000020u);
    uint32_t t20 = mem.r32(t19);
    ctx.ecx = static_cast<uint32_t>(t20);
    // 0x004dd4ad: mov dword ptr [edi + 0x20], ecx
    uint32_t t21 = static_cast<uint32_t>(ctx.edi + 0x00000020u);
    mem.w32(t21, ctx.ecx);
    // 0x004dd4b0: mov edx, dword ptr [esi + 0x24]
    uint32_t t22 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    uint32_t t23 = mem.r32(t22);
    ctx.edx = static_cast<uint32_t>(t23);
    // 0x004dd4b3: mov dword ptr [edi + 0x24], edx
    uint32_t t24 = static_cast<uint32_t>(ctx.edi + 0x00000024u);
    mem.w32(t24, ctx.edx);
    // 0x004dd4b6: mov eax, dword ptr [esi + 0x28]
    uint32_t t25 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    uint32_t t26 = mem.r32(t25);
    ctx.eax = static_cast<uint32_t>(t26);
    // 0x004dd4b9: mov dword ptr [edi + 0x28], eax
    uint32_t t27 = static_cast<uint32_t>(ctx.edi + 0x00000028u);
    mem.w32(t27, ctx.eax);
    // 0x004dd4bc: jne 0x4dd490
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dd490;
}
{
    // 0x004dd4be: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    goto bb_004dd4c0;
}
}

} // namespace mbaa_recomp

#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
