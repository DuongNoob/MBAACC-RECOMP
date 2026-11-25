// Auto-generated C++20 shard: gen_replay.cpp (56 functions) — DO NOT EDIT

#include "recomp_funcs.h"

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

namespace mbaa_recomp {

// sub_00407ab0 | subsystem=Replay | canonical | 3 blocks | 6 insns
void sub_00407ab0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00407ab0: cmp dword ptr [ecx + 0x18], 0x10
    uint32_t t0 = static_cast<uint32_t>(ctx.ecx + 0x00000018u);
    uint32_t t1 = mem.r32(t0);
    uint32_t t2 = static_cast<uint32_t>(t1 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t1, 0x00000010u, t2);
    // 0x00407ab4: jb 0x407aba
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_00407aba;
    goto bb_00407ab6;
}
bb_00407aba: {
    // 0x00407aba: lea eax, [ecx + 4]
    uint32_t t3 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x00407abd: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00407ab6: {
    // 0x00407ab6: mov eax, dword ptr [ecx + 4]
    uint32_t t4 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    uint32_t t5 = mem.r32(t4);
    ctx.eax = static_cast<uint32_t>(t5);
    // 0x00407ab9: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004138c0 | subsystem=Replay | canonical | 7 blocks | 26 insns
void sub_004138c0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004138c0: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x004138c1: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004138c3: push edi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.edi);
    // 0x004138c4: mov edi, dword ptr [esi + 0x14]
    uint32_t t2 = static_cast<uint32_t>(ctx.esi + 0x00000014u);
    uint32_t t3 = mem.r32(t2);
    ctx.edi = static_cast<uint32_t>(t3);
    // 0x004138c7: cmp edi, eax
    uint32_t t4 = static_cast<uint32_t>(ctx.edi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.eax, t4);
    // 0x004138c9: ja 0x4138f6
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_004138f6;
    goto bb_004138cb;
}
bb_004138f6: {
    // 0x004138f6: pop edi
    uint32_t t5 = ctx.esp;
    uint32_t t6 = mem.r32(t5);
    uint32_t t7 = static_cast<uint32_t>(t5 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    ctx.edi = static_cast<uint32_t>(t6);
    // 0x004138f7: pop esi
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.esi = static_cast<uint32_t>(t9);
    // 0x004138f8: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004138cb: {
    // 0x004138cb: cmp dword ptr [esi + 0x18], eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    uint32_t t12 = mem.r32(t11);
    uint32_t t13 = static_cast<uint32_t>(t12 - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t12, ctx.eax, t13);
    // 0x004138ce: je 0x4138f6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004138f6;
}
{
    // 0x004138d0: push 1
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x00000001u);
    // 0x004138d2: push eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.eax);
    // 0x004138d3: call 0x407d70
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x004138d8u);
    sub_00407d70(ctx, mem);
    // 0x004138d8: test al, al
    uint8_t t17 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t17);
    // 0x004138da: je 0x4138f6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004138f6;
}
{
    // 0x004138dc: cmp dword ptr [esi + 0x18], 0x10
    uint32_t t18 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    uint32_t t19 = mem.r32(t18);
    uint32_t t20 = static_cast<uint32_t>(t19 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t19, 0x00000010u, t20);
    // 0x004138e0: mov dword ptr [esi + 0x14], edi
    uint32_t t21 = static_cast<uint32_t>(ctx.esi + 0x00000014u);
    mem.w32(t21, ctx.edi);
    // 0x004138e3: jb 0x4138ef
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004138ef;
    goto bb_004138e5;
}
bb_004138ef: {
    // 0x004138ef: add esi, 4
    uint32_t t22 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000004u, t22);
    ctx.esi = static_cast<uint32_t>(t22);
    // 0x004138f2: mov byte ptr [esi + edi], 0
    uint32_t t23 = static_cast<uint32_t>(ctx.esi + ctx.edi);
    mem.w8(t23, uint8_t{0x00u});
    goto bb_004138f6;
}
bb_004138e5: {
    // 0x004138e5: mov esi, dword ptr [esi + 4]
    uint32_t t24 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t25 = mem.r32(t24);
    ctx.esi = static_cast<uint32_t>(t25);
    // 0x004138e8: mov byte ptr [esi + edi], 0
    uint32_t t26 = static_cast<uint32_t>(ctx.esi + ctx.edi);
    mem.w8(t26, uint8_t{0x00u});
    // 0x004138ec: pop edi
    uint32_t t27 = ctx.esp;
    uint32_t t28 = mem.r32(t27);
    uint32_t t29 = static_cast<uint32_t>(t27 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    ctx.edi = static_cast<uint32_t>(t28);
    // 0x004138ed: pop esi
    uint32_t t30 = ctx.esp;
    uint32_t t31 = mem.r32(t30);
    uint32_t t32 = static_cast<uint32_t>(t30 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    ctx.esi = static_cast<uint32_t>(t31);
    // 0x004138ee: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00414340 | subsystem=Replay | canonical | 3 blocks | 14 insns
void sub_00414340(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00414340: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x00414342: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x00414343: lea esi, [eax + 1]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.esi = static_cast<uint32_t>(t1);
}
bb_00414346: {
    // 0x00414346: mov cl, byte ptr [eax]
    uint8_t t2 = mem.r8(ctx.eax);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x00414348: add eax, 1
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t3);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0041434b: test cl, cl
    uint8_t t4 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t4);
    // 0x0041434d: jne 0x414346
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00414346;
}
{
    // 0x0041434f: sub eax, esi
    uint32_t t5 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t5);
    ctx.eax = static_cast<uint32_t>(t5);
    // 0x00414351: push eax
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.eax);
    // 0x00414352: mov eax, dword ptr [esp + 0xc]
    uint32_t t7 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t8 = mem.r32(t7);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x00414356: push edx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.edx);
    // 0x00414357: call 0x414660
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x0041435cu);
    sub_00414660(ctx, mem);
    // 0x0041435c: pop esi
    uint32_t t11 = ctx.esp;
    uint32_t t12 = mem.r32(t11);
    uint32_t t13 = static_cast<uint32_t>(t11 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    ctx.esi = static_cast<uint32_t>(t12);
    // 0x0041435d: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
}

// sub_00437ca0 | subsystem=Replay | canonical | 4 blocks | 40 insns
void sub_00437ca0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00437ca0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x00437ca2: push 0x518abb
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00518abbu);
    // 0x00437ca7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x00437cad: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x00437cae: push ecx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ecx);
    // 0x00437caf: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x00437cb4: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x00437cb6: push eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.eax);
    // 0x00437cb7: lea eax, [esp + 8]
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x00437cbb: mov dword ptr fs:[0], eax
    uint32_t t10 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t10, ctx.eax);
    // 0x00437cc1: call 0x4ddf40
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0x00437cc6u);
    sub_004ddf40(ctx, mem);
    // 0x00437cc6: push 0xdc
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x000000dcu);
    // 0x00437ccb: mov byte ptr [0x76e653], 1
    mem.w8(0x0076e653u, uint8_t{0x01u});
    // 0x00437cd2: call 0x4e0177
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x00437cd7u);
    hle_crt_004e0177(ctx, mem);
    // 0x00437cd7: add esp, 4
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t14);
    ctx.esp = static_cast<uint32_t>(t14);
    // 0x00437cda: mov dword ptr [esp + 4], eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    mem.w32(t15, ctx.eax);
    // 0x00437cde: test eax, eax
    uint32_t t16 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    // 0x00437ce0: mov dword ptr [esp + 0x10], 0
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t17, 0x00000000u);
    // 0x00437ce8: je 0x437cf2
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00437cf2;
    goto bb_00437cea;
}
bb_00437cf2: {
    // 0x00437cf2: xor eax, eax
    uint32_t t18 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    ctx.eax = static_cast<uint32_t>(t18);
    goto bb_00437cf4;
}
bb_00437cea: {
    // 0x00437cea: push eax
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, ctx.eax);
    // 0x00437ceb: call 0x43c830
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x00437cf0u);
    sub_0043c830(ctx, mem);
    // 0x00437cf0: jmp 0x437cf4
}
bb_00437cf4: {
    // 0x00437cf4: mov dword ptr [esp + 0x10], 0xffffffff
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t21, 0xffffffffu);
    // 0x00437cfc: mov dword ptr [0x54f980], eax
    mem.w32(0x0054f980u, ctx.eax);
    // 0x00437d01: mov dword ptr [eax + 4], 1
    uint32_t t22 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w32(t22, 0x00000001u);
    // 0x00437d08: mov eax, dword ptr [0x54f980]
    uint32_t t23 = mem.r32(0x0054f980u);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x00437d0d: mov dword ptr [eax + 8], 0xa
    uint32_t t24 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    mem.w32(t24, 0x0000000au);
    // 0x00437d14: mov ecx, dword ptr [0x54f980]
    uint32_t t25 = mem.r32(0x0054f980u);
    ctx.ecx = static_cast<uint32_t>(t25);
    // 0x00437d1a: push 0xa
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x0000000au);
    // 0x00437d1c: push 0x536970
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x00536970u);
    // 0x00437d21: add ecx, 0x2c
    uint32_t t28 = static_cast<uint32_t>(ctx.ecx + 0x0000002cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x0000002cu, t28);
    ctx.ecx = static_cast<uint32_t>(t28);
    // 0x00437d24: call 0x407c10
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x00437d29u);
    sub_00407c10(ctx, mem);
    // 0x00437d29: mov dword ptr [0x54f974], 0
    mem.w32(0x0054f974u, 0x00000000u);
    // 0x00437d33: mov dword ptr [0x54f97c], 0
    mem.w32(0x0054f97cu, 0x00000000u);
    // 0x00437d3d: mov ecx, dword ptr [esp + 8]
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t31 = mem.r32(t30);
    ctx.ecx = static_cast<uint32_t>(t31);
    // 0x00437d41: mov dword ptr fs:[0], ecx
    uint32_t t32 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t32, ctx.ecx);
    // 0x00437d48: pop ecx
    uint32_t t33 = ctx.esp;
    uint32_t t34 = mem.r32(t33);
    uint32_t t35 = static_cast<uint32_t>(t33 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    ctx.ecx = static_cast<uint32_t>(t34);
    // 0x00437d49: add esp, 0x10
    uint32_t t36 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t36);
    ctx.esp = static_cast<uint32_t>(t36);
    // 0x00437d4c: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0043c280 | subsystem=Replay | canonical | 17 blocks | 72 insns
void sub_0043c280(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043c280: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x0043c281: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
    // 0x0043c282: push edi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.edi);
    // 0x0043c283: mov edi, dword ptr [ebx + 4]
    uint32_t t3 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    uint32_t t4 = mem.r32(t3);
    ctx.edi = static_cast<uint32_t>(t4);
    // 0x0043c286: xor ebp, ebp
    uint32_t t5 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    ctx.ebp = static_cast<uint32_t>(t5);
    // 0x0043c288: cmp edi, ebp
    uint32_t t6 = static_cast<uint32_t>(ctx.edi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebp, t6);
    // 0x0043c28a: je 0x43c2b4
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c2b4;
    goto bb_0043c28c;
}
bb_0043c2b4: {
    // 0x0043c2b4: mov edi, dword ptr [ebx + 8]
    uint32_t t7 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t8 = mem.r32(t7);
    ctx.edi = static_cast<uint32_t>(t8);
    // 0x0043c2b7: cmp edi, ebp
    uint32_t t9 = static_cast<uint32_t>(ctx.edi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebp, t9);
    // 0x0043c2b9: mov dword ptr [ebx + 4], ebp
    uint32_t t10 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    mem.w32(t10, ctx.ebp);
    // 0x0043c2bc: je 0x43c2e6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c2e6;
    goto bb_0043c2be;
}
bb_0043c28c: {
    // 0x0043c28c: push edi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.edi);
    // 0x0043c28d: mov esi, 0x7b0928
    ctx.esi = static_cast<uint32_t>(0x007b0928u);
    // 0x0043c292: call 0x4bc9e0
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x0043c297u);
    sub_004bc9e0(ctx, mem);
    // 0x0043c297: mov eax, dword ptr [edi]
    uint32_t t13 = mem.r32(ctx.edi);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0043c299: cmp eax, ebp
    uint32_t t14 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t14);
    // 0x0043c29b: je 0x43c2a4
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c2a4;
    goto bb_0043c29d;
}
bb_0043c2e6: {
    // 0x0043c2e6: mov edi, dword ptr [ebx + 0xc]
    uint32_t t15 = static_cast<uint32_t>(ctx.ebx + 0x0000000cu);
    uint32_t t16 = mem.r32(t15);
    ctx.edi = static_cast<uint32_t>(t16);
    // 0x0043c2e9: cmp edi, ebp
    uint32_t t17 = static_cast<uint32_t>(ctx.edi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebp, t17);
    // 0x0043c2eb: mov dword ptr [ebx + 8], ebp
    uint32_t t18 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    mem.w32(t18, ctx.ebp);
    // 0x0043c2ee: je 0x43c318
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c318;
    goto bb_0043c2f0;
}
bb_0043c2be: {
    // 0x0043c2be: push edi
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, ctx.edi);
    // 0x0043c2bf: mov esi, 0x7b0928
    ctx.esi = static_cast<uint32_t>(0x007b0928u);
    // 0x0043c2c4: call 0x4bc9e0
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x0043c2c9u);
    sub_004bc9e0(ctx, mem);
    // 0x0043c2c9: mov eax, dword ptr [edi]
    uint32_t t21 = mem.r32(ctx.edi);
    ctx.eax = static_cast<uint32_t>(t21);
    // 0x0043c2cb: cmp eax, ebp
    uint32_t t22 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t22);
    // 0x0043c2cd: je 0x43c2d6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c2d6;
    goto bb_0043c2cf;
}
bb_0043c2a4: {
    // 0x0043c2a4: push edi
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, ctx.edi);
    // 0x0043c2a5: call 0x4e00d0
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x0043c2aau);
    hle_crt_004e00d0(ctx, mem);
    // 0x0043c2aa: add esp, 4
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t25);
    ctx.esp = static_cast<uint32_t>(t25);
    // 0x0043c2ad: sub dword ptr [0x767440], 1
    uint32_t t26 = mem.r32(0x00767440u);
    uint32_t t27 = static_cast<uint32_t>(t26 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t26, 0x00000001u, t27);
    mem.w32(0x00767440u, t27);
    goto bb_0043c2b4;
}
bb_0043c29d: {
    // 0x0043c29d: call 0x4bcfd0
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x0043c2a2u);
    sub_004bcfd0(ctx, mem);
    // 0x0043c2a2: mov dword ptr [edi], ebp
    mem.w32(ctx.edi, ctx.ebp);
    goto bb_0043c2a4;
}
bb_0043c318: {
    // 0x0043c318: mov edi, dword ptr [ebx + 0x10]
    uint32_t t29 = static_cast<uint32_t>(ctx.ebx + 0x00000010u);
    uint32_t t30 = mem.r32(t29);
    ctx.edi = static_cast<uint32_t>(t30);
    // 0x0043c31b: cmp edi, ebp
    uint32_t t31 = static_cast<uint32_t>(ctx.edi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebp, t31);
    // 0x0043c31d: mov dword ptr [ebx + 0xc], ebp
    uint32_t t32 = static_cast<uint32_t>(ctx.ebx + 0x0000000cu);
    mem.w32(t32, ctx.ebp);
    // 0x0043c320: je 0x43c34a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c34a;
    goto bb_0043c322;
}
bb_0043c2f0: {
    // 0x0043c2f0: push edi
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, ctx.edi);
    // 0x0043c2f1: mov esi, 0x7b0928
    ctx.esi = static_cast<uint32_t>(0x007b0928u);
    // 0x0043c2f6: call 0x4bc9e0
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x0043c2fbu);
    sub_004bc9e0(ctx, mem);
    // 0x0043c2fb: mov eax, dword ptr [edi]
    uint32_t t35 = mem.r32(ctx.edi);
    ctx.eax = static_cast<uint32_t>(t35);
    // 0x0043c2fd: cmp eax, ebp
    uint32_t t36 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t36);
    // 0x0043c2ff: je 0x43c308
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c308;
    goto bb_0043c301;
}
bb_0043c2d6: {
    // 0x0043c2d6: push edi
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, ctx.edi);
    // 0x0043c2d7: call 0x4e00d0
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, 0x0043c2dcu);
    hle_crt_004e00d0(ctx, mem);
    // 0x0043c2dc: add esp, 4
    uint32_t t39 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t39);
    ctx.esp = static_cast<uint32_t>(t39);
    // 0x0043c2df: sub dword ptr [0x767440], 1
    uint32_t t40 = mem.r32(0x00767440u);
    uint32_t t41 = static_cast<uint32_t>(t40 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t40, 0x00000001u, t41);
    mem.w32(0x00767440u, t41);
    goto bb_0043c2e6;
}
bb_0043c2cf: {
    // 0x0043c2cf: call 0x4bcfd0
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, 0x0043c2d4u);
    sub_004bcfd0(ctx, mem);
    // 0x0043c2d4: mov dword ptr [edi], ebp
    mem.w32(ctx.edi, ctx.ebp);
    goto bb_0043c2d6;
}
bb_0043c34a: {
    // 0x0043c34a: pop edi
    uint32_t t43 = ctx.esp;
    uint32_t t44 = mem.r32(t43);
    uint32_t t45 = static_cast<uint32_t>(t43 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    ctx.edi = static_cast<uint32_t>(t44);
    // 0x0043c34b: pop esi
    uint32_t t46 = ctx.esp;
    uint32_t t47 = mem.r32(t46);
    uint32_t t48 = static_cast<uint32_t>(t46 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    ctx.esi = static_cast<uint32_t>(t47);
    // 0x0043c34c: mov dword ptr [ebx + 0x10], ebp
    uint32_t t49 = static_cast<uint32_t>(ctx.ebx + 0x00000010u);
    mem.w32(t49, ctx.ebp);
    // 0x0043c34f: pop ebp
    uint32_t t50 = ctx.esp;
    uint32_t t51 = mem.r32(t50);
    uint32_t t52 = static_cast<uint32_t>(t50 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    ctx.ebp = static_cast<uint32_t>(t51);
    // 0x0043c350: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043c322: {
    // 0x0043c322: push edi
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, ctx.edi);
    // 0x0043c323: mov esi, 0x7b0928
    ctx.esi = static_cast<uint32_t>(0x007b0928u);
    // 0x0043c328: call 0x4bc9e0
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, 0x0043c32du);
    sub_004bc9e0(ctx, mem);
    // 0x0043c32d: mov eax, dword ptr [edi]
    uint32_t t55 = mem.r32(ctx.edi);
    ctx.eax = static_cast<uint32_t>(t55);
    // 0x0043c32f: cmp eax, ebp
    uint32_t t56 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t56);
    // 0x0043c331: je 0x43c33a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c33a;
    goto bb_0043c333;
}
bb_0043c308: {
    // 0x0043c308: push edi
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, ctx.edi);
    // 0x0043c309: call 0x4e00d0
    uint32_t t58 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    mem.w32(t58, 0x0043c30eu);
    hle_crt_004e00d0(ctx, mem);
    // 0x0043c30e: add esp, 4
    uint32_t t59 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t59);
    ctx.esp = static_cast<uint32_t>(t59);
    // 0x0043c311: sub dword ptr [0x767440], 1
    uint32_t t60 = mem.r32(0x00767440u);
    uint32_t t61 = static_cast<uint32_t>(t60 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t60, 0x00000001u, t61);
    mem.w32(0x00767440u, t61);
    goto bb_0043c318;
}
bb_0043c301: {
    // 0x0043c301: call 0x4bcfd0
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, 0x0043c306u);
    sub_004bcfd0(ctx, mem);
    // 0x0043c306: mov dword ptr [edi], ebp
    mem.w32(ctx.edi, ctx.ebp);
    goto bb_0043c308;
}
bb_0043c33a: {
    // 0x0043c33a: push edi
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, ctx.edi);
    // 0x0043c33b: call 0x4e00d0
    uint32_t t64 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    mem.w32(t64, 0x0043c340u);
    hle_crt_004e00d0(ctx, mem);
    // 0x0043c340: add esp, 4
    uint32_t t65 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t65);
    ctx.esp = static_cast<uint32_t>(t65);
    // 0x0043c343: sub dword ptr [0x767440], 1
    uint32_t t66 = mem.r32(0x00767440u);
    uint32_t t67 = static_cast<uint32_t>(t66 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t66, 0x00000001u, t67);
    mem.w32(0x00767440u, t67);
    goto bb_0043c34a;
}
bb_0043c333: {
    // 0x0043c333: call 0x4bcfd0
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, 0x0043c338u);
    sub_004bcfd0(ctx, mem);
    // 0x0043c338: mov dword ptr [edi], ebp
    mem.w32(ctx.edi, ctx.ebp);
    goto bb_0043c33a;
}
}

// sub_0043c470 | subsystem=Replay | canonical | 1 blocks | 23 insns
void sub_0043c470(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043c470: sub esp, 8
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000008u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000008u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x0043c473: movzx edx, word ptr [eax + 8]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    uint16_t t2 = mem.r16(t1);
    uint32_t t3 = static_cast<uint32_t>(static_cast<uint16_t>(t2));
    ctx.edx = static_cast<uint32_t>(t3);
    // 0x0043c477: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x0043c478: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x0043c47a: movzx ecx, word ptr [eax + 0xa]
    uint32_t t5 = static_cast<uint32_t>(ctx.eax + 0x0000000au);
    uint16_t t6 = mem.r16(t5);
    uint32_t t7 = static_cast<uint32_t>(static_cast<uint16_t>(t6));
    ctx.ecx = static_cast<uint32_t>(t7);
    // 0x0043c47e: push ecx
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.ecx);
    // 0x0043c47f: movzx ecx, word ptr [eax + 6]
    uint32_t t9 = static_cast<uint32_t>(ctx.eax + 0x00000006u);
    uint16_t t10 = mem.r16(t9);
    uint32_t t11 = static_cast<uint32_t>(static_cast<uint16_t>(t10));
    ctx.ecx = static_cast<uint32_t>(t11);
    // 0x0043c483: push edx
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.edx);
    // 0x0043c484: movzx edx, word ptr [eax + 4]
    uint32_t t13 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint16_t t14 = mem.r16(t13);
    uint32_t t15 = static_cast<uint32_t>(static_cast<uint16_t>(t14));
    ctx.edx = static_cast<uint32_t>(t15);
    // 0x0043c488: push ecx
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, ctx.ecx);
    // 0x0043c489: movzx ecx, word ptr [eax + 2]
    uint32_t t17 = static_cast<uint32_t>(ctx.eax + 0x00000002u);
    uint16_t t18 = mem.r16(t17);
    uint32_t t19 = static_cast<uint32_t>(static_cast<uint16_t>(t18));
    ctx.ecx = static_cast<uint32_t>(t19);
    // 0x0043c48d: push edx
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, ctx.edx);
    // 0x0043c48e: movzx edx, word ptr [eax]
    uint16_t t21 = mem.r16(ctx.eax);
    uint32_t t22 = static_cast<uint32_t>(static_cast<uint16_t>(t21));
    ctx.edx = static_cast<uint32_t>(t22);
    // 0x0043c491: push ecx
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, ctx.ecx);
    // 0x0043c492: push edx
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, ctx.edx);
    // 0x0043c493: push 0x536a8c
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x00536a8cu);
    // 0x0043c498: mov dword ptr [esp + 0x24], 0
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t26, 0x00000000u);
    // 0x0043c4a0: call 0x4c1ec0
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x0043c4a5u);
    sub_004c1ec0(ctx, mem);
    // 0x0043c4a5: add esp, 0x1c
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000001cu, t28);
    ctx.esp = static_cast<uint32_t>(t28);
    // 0x0043c4a8: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0043c4aa: pop esi
    uint32_t t29 = ctx.esp;
    uint32_t t30 = mem.r32(t29);
    uint32_t t31 = static_cast<uint32_t>(t29 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    ctx.esi = static_cast<uint32_t>(t30);
    // 0x0043c4ab: add esp, 8
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t32);
    ctx.esp = static_cast<uint32_t>(t32);
    // 0x0043c4ae: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0043c4b0 | subsystem=Replay | canonical | 1 blocks | 34 insns
void sub_0043c4b0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043c4b0: xor ecx, ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.ecx = static_cast<uint32_t>(t0);
    // 0x0043c4b2: mov word ptr [eax + 0x22], cx
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00000022u);
    mem.w16(t1, recomp_detail::r16(ctx.ecx));
    // 0x0043c4b6: mov word ptr [eax + 0x20], cx
    uint32_t t2 = static_cast<uint32_t>(ctx.eax + 0x00000020u);
    mem.w16(t2, recomp_detail::r16(ctx.ecx));
    // 0x0043c4ba: mov word ptr [eax + 0x1e], cx
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0000001eu);
    mem.w16(t3, recomp_detail::r16(ctx.ecx));
    // 0x0043c4be: mov word ptr [eax + 0x1c], cx
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x0000001cu);
    mem.w16(t4, recomp_detail::r16(ctx.ecx));
    // 0x0043c4c2: mov word ptr [eax + 0x1a], cx
    uint32_t t5 = static_cast<uint32_t>(ctx.eax + 0x0000001au);
    mem.w16(t5, recomp_detail::r16(ctx.ecx));
    // 0x0043c4c6: mov word ptr [eax + 0x18], cx
    uint32_t t6 = static_cast<uint32_t>(ctx.eax + 0x00000018u);
    mem.w16(t6, recomp_detail::r16(ctx.ecx));
    // 0x0043c4ca: mov dword ptr [eax + 0x28], ecx
    uint32_t t7 = static_cast<uint32_t>(ctx.eax + 0x00000028u);
    mem.w32(t7, ctx.ecx);
    // 0x0043c4cd: mov dword ptr [eax + 0x24], ecx
    uint32_t t8 = static_cast<uint32_t>(ctx.eax + 0x00000024u);
    mem.w32(t8, ctx.ecx);
    // 0x0043c4d0: mov edx, 2
    ctx.edx = static_cast<uint32_t>(0x00000002u);
    // 0x0043c4d5: mov dword ptr [eax + 0x2c], edx
    uint32_t t9 = static_cast<uint32_t>(ctx.eax + 0x0000002cu);
    mem.w32(t9, ctx.edx);
    // 0x0043c4d8: mov dword ptr [eax + 0x34], edx
    uint32_t t10 = static_cast<uint32_t>(ctx.eax + 0x00000034u);
    mem.w32(t10, ctx.edx);
    // 0x0043c4db: mov dword ptr [eax + 0x38], edx
    uint32_t t11 = static_cast<uint32_t>(ctx.eax + 0x00000038u);
    mem.w32(t11, ctx.edx);
    // 0x0043c4de: mov dword ptr [eax + 0x3c], ecx
    uint32_t t12 = static_cast<uint32_t>(ctx.eax + 0x0000003cu);
    mem.w32(t12, ctx.ecx);
    // 0x0043c4e1: mov dword ptr [eax + 0x40], ecx
    uint32_t t13 = static_cast<uint32_t>(ctx.eax + 0x00000040u);
    mem.w32(t13, ctx.ecx);
    // 0x0043c4e4: mov dword ptr [eax + 0x44], ecx
    uint32_t t14 = static_cast<uint32_t>(ctx.eax + 0x00000044u);
    mem.w32(t14, ctx.ecx);
    // 0x0043c4e7: mov dword ptr [eax + 0x48], ecx
    uint32_t t15 = static_cast<uint32_t>(ctx.eax + 0x00000048u);
    mem.w32(t15, ctx.ecx);
    // 0x0043c4ea: mov dword ptr [eax + 0x4c], ecx
    uint32_t t16 = static_cast<uint32_t>(ctx.eax + 0x0000004cu);
    mem.w32(t16, ctx.ecx);
    // 0x0043c4ed: mov dword ptr [eax + 0x50], ecx
    uint32_t t17 = static_cast<uint32_t>(ctx.eax + 0x00000050u);
    mem.w32(t17, ctx.ecx);
    // 0x0043c4f0: mov dword ptr [eax + 0x54], ecx
    uint32_t t18 = static_cast<uint32_t>(ctx.eax + 0x00000054u);
    mem.w32(t18, ctx.ecx);
    // 0x0043c4f3: mov dword ptr [eax + 0x58], ecx
    uint32_t t19 = static_cast<uint32_t>(ctx.eax + 0x00000058u);
    mem.w32(t19, ctx.ecx);
    // 0x0043c4f6: mov edx, dword ptr [0x536aa8]
    uint32_t t20 = mem.r32(0x00536aa8u);
    ctx.edx = static_cast<uint32_t>(t20);
    // 0x0043c4fc: mov dword ptr [eax], edx
    mem.w32(ctx.eax, ctx.edx);
    // 0x0043c4fe: mov edx, dword ptr [0x536aac]
    uint32_t t21 = mem.r32(0x00536aacu);
    ctx.edx = static_cast<uint32_t>(t21);
    // 0x0043c504: mov dword ptr [eax + 4], edx
    uint32_t t22 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w32(t22, ctx.edx);
    // 0x0043c507: mov edx, dword ptr [0x536ab0]
    uint32_t t23 = mem.r32(0x00536ab0u);
    ctx.edx = static_cast<uint32_t>(t23);
    // 0x0043c50d: mov dword ptr [eax + 8], edx
    uint32_t t24 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    mem.w32(t24, ctx.edx);
    // 0x0043c510: mov dx, word ptr [0x536ab4]
    uint16_t t25 = mem.r16(0x00536ab4u);
    recomp_detail::w16(ctx.edx, static_cast<uint16_t>(t25));
    // 0x0043c517: mov word ptr [eax + 0xc], dx
    uint32_t t26 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    mem.w16(t26, recomp_detail::r16(ctx.edx));
    // 0x0043c51b: mov dl, byte ptr [0x536ab6]
    uint8_t t27 = mem.r8(0x00536ab6u);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t27));
    // 0x0043c521: mov byte ptr [eax + 0xe], dl
    uint32_t t28 = static_cast<uint32_t>(ctx.eax + 0x0000000eu);
    mem.w8(t28, recomp_detail::r8l(ctx.edx));
    // 0x0043c524: mov dword ptr [eax + 0x10], 0xc0000004
    uint32_t t29 = static_cast<uint32_t>(ctx.eax + 0x00000010u);
    mem.w32(t29, 0xc0000004u);
    // 0x0043c52b: mov dword ptr [eax + 0x14], ecx
    uint32_t t30 = static_cast<uint32_t>(ctx.eax + 0x00000014u);
    mem.w32(t30, ctx.ecx);
    // 0x0043c52e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0043c530 | subsystem=Replay | canonical | 11 blocks | 68 insns
void sub_0043c530(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043c530: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0043c532: push 0x514606
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00514606u);
    // 0x0043c537: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0043c53d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0043c53e: push ebx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ebx);
    // 0x0043c53f: push ebp
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebp);
    // 0x0043c540: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x0043c541: push edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edi);
    // 0x0043c542: mov eax, dword ptr [0x54b458]
    uint32_t t9 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x0043c547: xor eax, esp
    uint32_t t10 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0043c549: push eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.eax);
    // 0x0043c54a: lea eax, [esp + 0x14]
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0043c54e: mov dword ptr fs:[0], eax
    uint32_t t13 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t13, ctx.eax);
    // 0x0043c554: mov edi, dword ptr [esp + 0x24]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t15 = mem.r32(t14);
    ctx.edi = static_cast<uint32_t>(t15);
    // 0x0043c558: mov dword ptr [esp + 0x1c], 1
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t16, 0x00000001u);
    // 0x0043c560: mov ebp, dword ptr [edi + 0x44]
    uint32_t t17 = static_cast<uint32_t>(ctx.edi + 0x00000044u);
    uint32_t t18 = mem.r32(t17);
    ctx.ebp = static_cast<uint32_t>(t18);
    // 0x0043c563: xor ebx, ebx
    uint32_t t19 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t19);
    ctx.ebx = static_cast<uint32_t>(t19);
    // 0x0043c565: cmp ebp, ebx
    uint32_t t20 = static_cast<uint32_t>(ctx.ebp - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebp, ctx.ebx, t20);
    // 0x0043c567: je 0x43c593
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c593;
    goto bb_0043c569;
}
bb_0043c593: {
    // 0x0043c593: mov eax, dword ptr [edi + 0x40]
    uint32_t t21 = static_cast<uint32_t>(ctx.edi + 0x00000040u);
    uint32_t t22 = mem.r32(t21);
    ctx.eax = static_cast<uint32_t>(t22);
    // 0x0043c596: cmp eax, ebx
    uint32_t t23 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t23);
    // 0x0043c598: mov dword ptr [edi + 0x44], ebx
    uint32_t t24 = static_cast<uint32_t>(ctx.edi + 0x00000044u);
    mem.w32(t24, ctx.ebx);
    // 0x0043c59b: je 0x43c5a9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c5a9;
    goto bb_0043c59d;
}
bb_0043c569: {
    // 0x0043c569: push ebp
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, ctx.ebp);
    // 0x0043c56a: mov esi, 0x7b0928
    ctx.esi = static_cast<uint32_t>(0x007b0928u);
    // 0x0043c56f: call 0x4bc9e0
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x0043c574u);
    sub_004bc9e0(ctx, mem);
    // 0x0043c574: mov eax, dword ptr [ebp]
    uint32_t t27 = mem.r32(ctx.ebp);
    ctx.eax = static_cast<uint32_t>(t27);
    // 0x0043c577: cmp eax, ebx
    uint32_t t28 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t28);
    // 0x0043c579: je 0x43c583
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c583;
    goto bb_0043c57b;
}
bb_0043c5a9: {
    // 0x0043c5a9: mov ebp, 0x10
    ctx.ebp = static_cast<uint32_t>(0x00000010u);
    // 0x0043c5ae: cmp dword ptr [edi + 0x3c], ebp
    uint32_t t29 = static_cast<uint32_t>(ctx.edi + 0x0000003cu);
    uint32_t t30 = mem.r32(t29);
    uint32_t t31 = static_cast<uint32_t>(t30 - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t30, ctx.ebp, t31);
    // 0x0043c5b1: jb 0x43c5bf
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043c5bf;
    goto bb_0043c5b3;
}
bb_0043c59d: {
    // 0x0043c59d: push eax
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, ctx.eax);
    // 0x0043c59e: call 0x4e02f3
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x0043c5a3u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043c5a3: add esp, 4
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t34);
    ctx.esp = static_cast<uint32_t>(t34);
    // 0x0043c5a6: mov dword ptr [edi + 0x40], ebx
    uint32_t t35 = static_cast<uint32_t>(ctx.edi + 0x00000040u);
    mem.w32(t35, ctx.ebx);
    goto bb_0043c5a9;
}
bb_0043c583: {
    // 0x0043c583: push ebp
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, ctx.ebp);
    // 0x0043c584: call 0x4e00d0
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, 0x0043c589u);
    hle_crt_004e00d0(ctx, mem);
    // 0x0043c589: add esp, 4
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t38);
    ctx.esp = static_cast<uint32_t>(t38);
    // 0x0043c58c: sub dword ptr [0x767440], 1
    uint32_t t39 = mem.r32(0x00767440u);
    uint32_t t40 = static_cast<uint32_t>(t39 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t39, 0x00000001u, t40);
    mem.w32(0x00767440u, t40);
    goto bb_0043c593;
}
bb_0043c57b: {
    // 0x0043c57b: call 0x4bcfd0
    uint32_t t41 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    mem.w32(t41, 0x0043c580u);
    sub_004bcfd0(ctx, mem);
    // 0x0043c580: mov dword ptr [ebp], ebx
    mem.w32(ctx.ebp, ctx.ebx);
    goto bb_0043c583;
}
bb_0043c5bf: {
    // 0x0043c5bf: mov esi, 0xf
    ctx.esi = static_cast<uint32_t>(0x0000000fu);
    // 0x0043c5c4: mov dword ptr [edi + 0x3c], esi
    uint32_t t42 = static_cast<uint32_t>(ctx.edi + 0x0000003cu);
    mem.w32(t42, ctx.esi);
    // 0x0043c5c7: mov dword ptr [edi + 0x38], ebx
    uint32_t t43 = static_cast<uint32_t>(ctx.edi + 0x00000038u);
    mem.w32(t43, ctx.ebx);
    // 0x0043c5ca: mov byte ptr [edi + 0x28], bl
    uint32_t t44 = static_cast<uint32_t>(ctx.edi + 0x00000028u);
    mem.w8(t44, recomp_detail::r8l(ctx.ebx));
    // 0x0043c5cd: cmp dword ptr [edi + 0x20], ebp
    uint32_t t45 = static_cast<uint32_t>(ctx.edi + 0x00000020u);
    uint32_t t46 = mem.r32(t45);
    uint32_t t47 = static_cast<uint32_t>(t46 - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t46, ctx.ebp, t47);
    // 0x0043c5d0: jb 0x43c5de
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043c5de;
    goto bb_0043c5d2;
}
bb_0043c5b3: {
    // 0x0043c5b3: mov eax, dword ptr [edi + 0x28]
    uint32_t t48 = static_cast<uint32_t>(ctx.edi + 0x00000028u);
    uint32_t t49 = mem.r32(t48);
    ctx.eax = static_cast<uint32_t>(t49);
    // 0x0043c5b6: push eax
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, ctx.eax);
    // 0x0043c5b7: call 0x4e02f3
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, 0x0043c5bcu);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043c5bc: add esp, 4
    uint32_t t52 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t52);
    ctx.esp = static_cast<uint32_t>(t52);
    goto bb_0043c5bf;
}
bb_0043c5de: {
    // 0x0043c5de: mov dword ptr [edi + 0x20], esi
    uint32_t t53 = static_cast<uint32_t>(ctx.edi + 0x00000020u);
    mem.w32(t53, ctx.esi);
    // 0x0043c5e1: mov dword ptr [edi + 0x1c], ebx
    uint32_t t54 = static_cast<uint32_t>(ctx.edi + 0x0000001cu);
    mem.w32(t54, ctx.ebx);
    // 0x0043c5e4: mov byte ptr [edi + 0xc], bl
    uint32_t t55 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    mem.w8(t55, recomp_detail::r8l(ctx.ebx));
    // 0x0043c5e7: mov ecx, dword ptr [esp + 0x14]
    uint32_t t56 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t57 = mem.r32(t56);
    ctx.ecx = static_cast<uint32_t>(t57);
    // 0x0043c5eb: mov dword ptr fs:[0], ecx
    uint32_t t58 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t58, ctx.ecx);
    // 0x0043c5f2: pop ecx
    uint32_t t59 = ctx.esp;
    uint32_t t60 = mem.r32(t59);
    uint32_t t61 = static_cast<uint32_t>(t59 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    ctx.ecx = static_cast<uint32_t>(t60);
    // 0x0043c5f3: pop edi
    uint32_t t62 = ctx.esp;
    uint32_t t63 = mem.r32(t62);
    uint32_t t64 = static_cast<uint32_t>(t62 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    ctx.edi = static_cast<uint32_t>(t63);
    // 0x0043c5f4: pop esi
    uint32_t t65 = ctx.esp;
    uint32_t t66 = mem.r32(t65);
    uint32_t t67 = static_cast<uint32_t>(t65 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t67);
    ctx.esi = static_cast<uint32_t>(t66);
    // 0x0043c5f5: pop ebp
    uint32_t t68 = ctx.esp;
    uint32_t t69 = mem.r32(t68);
    uint32_t t70 = static_cast<uint32_t>(t68 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    ctx.ebp = static_cast<uint32_t>(t69);
    // 0x0043c5f6: pop ebx
    uint32_t t71 = ctx.esp;
    uint32_t t72 = mem.r32(t71);
    uint32_t t73 = static_cast<uint32_t>(t71 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    ctx.ebx = static_cast<uint32_t>(t72);
    // 0x0043c5f7: add esp, 0xc
    uint32_t t74 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t74);
    ctx.esp = static_cast<uint32_t>(t74);
    // 0x0043c5fa: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0043c5d2: {
    // 0x0043c5d2: mov ecx, dword ptr [edi + 0xc]
    uint32_t t75 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    uint32_t t76 = mem.r32(t75);
    ctx.ecx = static_cast<uint32_t>(t76);
    // 0x0043c5d5: push ecx
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, ctx.ecx);
    // 0x0043c5d6: call 0x4e02f3
    uint32_t t78 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    mem.w32(t78, 0x0043c5dbu);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043c5db: add esp, 4
    uint32_t t79 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t79);
    ctx.esp = static_cast<uint32_t>(t79);
    goto bb_0043c5de;
}
}

// sub_0043c600 | subsystem=Replay | canonical | 5 blocks | 23 insns
void sub_0043c600(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043c600: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x0043c601: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
    // 0x0043c602: push edi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.edi);
    // 0x0043c603: mov edi, dword ptr [ebx + 0x44]
    uint32_t t3 = static_cast<uint32_t>(ctx.ebx + 0x00000044u);
    uint32_t t4 = mem.r32(t3);
    ctx.edi = static_cast<uint32_t>(t4);
    // 0x0043c606: test edi, edi
    uint32_t t5 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    // 0x0043c608: je 0x43c636
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c636;
    goto bb_0043c60a;
}
bb_0043c636: {
    // 0x0043c636: pop edi
    uint32_t t6 = ctx.esp;
    uint32_t t7 = mem.r32(t6);
    uint32_t t8 = static_cast<uint32_t>(t6 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    ctx.edi = static_cast<uint32_t>(t7);
    // 0x0043c637: mov dword ptr [ebx + 0x44], 0
    uint32_t t9 = static_cast<uint32_t>(ctx.ebx + 0x00000044u);
    mem.w32(t9, 0x00000000u);
    // 0x0043c63e: pop esi
    uint32_t t10 = ctx.esp;
    uint32_t t11 = mem.r32(t10);
    uint32_t t12 = static_cast<uint32_t>(t10 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    ctx.esi = static_cast<uint32_t>(t11);
    // 0x0043c63f: pop ecx
    uint32_t t13 = ctx.esp;
    uint32_t t14 = mem.r32(t13);
    uint32_t t15 = static_cast<uint32_t>(t13 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    ctx.ecx = static_cast<uint32_t>(t14);
    // 0x0043c640: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043c60a: {
    // 0x0043c60a: push edi
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, ctx.edi);
    // 0x0043c60b: mov esi, 0x7b0928
    ctx.esi = static_cast<uint32_t>(0x007b0928u);
    // 0x0043c610: call 0x4bc9e0
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x0043c615u);
    sub_004bc9e0(ctx, mem);
    // 0x0043c615: mov eax, dword ptr [edi]
    uint32_t t18 = mem.r32(ctx.edi);
    ctx.eax = static_cast<uint32_t>(t18);
    // 0x0043c617: test eax, eax
    uint32_t t19 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t19);
    // 0x0043c619: je 0x43c626
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c626;
    goto bb_0043c61b;
}
bb_0043c626: {
    // 0x0043c626: push edi
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, ctx.edi);
    // 0x0043c627: call 0x4e00d0
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x0043c62cu);
    hle_crt_004e00d0(ctx, mem);
    // 0x0043c62c: add esp, 4
    uint32_t t22 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t22);
    ctx.esp = static_cast<uint32_t>(t22);
    // 0x0043c62f: sub dword ptr [0x767440], 1
    uint32_t t23 = mem.r32(0x00767440u);
    uint32_t t24 = static_cast<uint32_t>(t23 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t23, 0x00000001u, t24);
    mem.w32(0x00767440u, t24);
    goto bb_0043c636;
}
bb_0043c61b: {
    // 0x0043c61b: call 0x4bcfd0
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x0043c620u);
    sub_004bcfd0(ctx, mem);
    // 0x0043c620: mov dword ptr [edi], 0
    mem.w32(ctx.edi, 0x00000000u);
    goto bb_0043c626;
}
}

// sub_0043c650 | subsystem=Replay | canonical | 1 blocks | 5 insns
void sub_0043c650(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043c650: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x0043c651: mov esi, dword ptr [esp + 8]
    uint32_t t1 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t2 = mem.r32(t1);
    ctx.esi = static_cast<uint32_t>(t2);
    // 0x0043c655: call 0x43c690
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x0043c65au);
    sub_0043c690(ctx, mem);
    // 0x0043c65a: pop esi
    uint32_t t4 = ctx.esp;
    uint32_t t5 = mem.r32(t4);
    uint32_t t6 = static_cast<uint32_t>(t4 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    ctx.esi = static_cast<uint32_t>(t5);
    // 0x0043c65b: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
}

// sub_0043c660 | subsystem=Replay | canonical | 4 blocks | 12 insns
void sub_0043c660(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043c660: cmp dword ptr [eax + 0xd4], 0
    uint32_t t0 = static_cast<uint32_t>(ctx.eax + 0x000000d4u);
    uint32_t t1 = mem.r32(t0);
    uint32_t t2 = static_cast<uint32_t>(t1 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t1, 0x00000000u, t2);
    // 0x0043c667: jne 0x43c66f
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043c66f;
    goto bb_0043c669;
}
bb_0043c66f: {
    // 0x0043c66f: mov eax, dword ptr [eax + 0xd8]
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x000000d8u);
    uint32_t t4 = mem.r32(t3);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0043c675: test eax, eax
    uint32_t t5 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    // 0x0043c677: je 0x43c669
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c669;
    goto bb_0043c679;
}
bb_0043c669: {
    // 0x0043c669: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0043c66e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043c679: {
    // 0x0043c679: xor ecx, ecx
    uint32_t t6 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t6);
    ctx.ecx = static_cast<uint32_t>(t6);
    // 0x0043c67b: cmp eax, 1
    uint32_t t7 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t7);
    // 0x0043c67e: sete cl
    uint8_t t8 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::E) ? 1u : 0u);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t8));
    // 0x0043c681: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x0043c683: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0043c690 | subsystem=Replay | canonical | 29 blocks | 116 insns
void sub_0043c690(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043c690: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x0043c691: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x0043c693: and esp, 0xfffffff8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xfffffff8u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x0043c696: sub esp, 8
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000008u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000008u, t2);
    ctx.esp = static_cast<uint32_t>(t2);
    // 0x0043c699: cmp dword ptr [esi + 0xd4], 0
    uint32_t t3 = static_cast<uint32_t>(ctx.esi + 0x000000d4u);
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t4 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t4, 0x00000000u, t5);
    // 0x0043c6a0: push ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebx);
    // 0x0043c6a1: push edi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.edi);
    // 0x0043c6a2: je 0x43c80b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c80b;
    goto bb_0043c6a8;
}
bb_0043c80b: {
    // 0x0043c80b: pop edi
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.edi = static_cast<uint32_t>(t9);
    // 0x0043c80c: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0043c811: pop ebx
    uint32_t t11 = ctx.esp;
    uint32_t t12 = mem.r32(t11);
    uint32_t t13 = static_cast<uint32_t>(t11 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    ctx.ebx = static_cast<uint32_t>(t12);
    // 0x0043c812: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0043c814: pop ebp
    uint32_t t14 = ctx.esp;
    uint32_t t15 = mem.r32(t14);
    uint32_t t16 = static_cast<uint32_t>(t14 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    ctx.ebp = static_cast<uint32_t>(t15);
    // 0x0043c815: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043c6a8: {
    // 0x0043c6a8: push 1
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x00000001u);
    // 0x0043c6aa: call dword ptr [0x51b1d0]
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x0043c6b0u);
    hle_iat_call(ctx, mem, 0x0051b1d0u);
    // 0x0043c6b0: mov eax, dword ptr [esi + 0xd8]
    uint32_t t19 = static_cast<uint32_t>(ctx.esi + 0x000000d8u);
    uint32_t t20 = mem.r32(t19);
    ctx.eax = static_cast<uint32_t>(t20);
    // 0x0043c6b6: cmp eax, 3
    uint32_t t21 = static_cast<uint32_t>(ctx.eax - 0x00000003u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000003u, t21);
    // 0x0043c6b9: ja 0x43c7fe
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_0043c7fe;
    goto bb_0043c6bf;
}
bb_0043c7fe: {
    // 0x0043c7fe: cmp dword ptr [esi + 0xd4], 0
    uint32_t t22 = static_cast<uint32_t>(ctx.esi + 0x000000d4u);
    uint32_t t23 = mem.r32(t22);
    uint32_t t24 = static_cast<uint32_t>(t23 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t23, 0x00000000u, t24);
    // 0x0043c805: jne 0x43c6a8
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043c6a8;
    goto bb_0043c80b;
}
bb_0043c6bf: {
    // 0x0043c6bf: jmp dword ptr [eax*4 + 0x43c818]
    switch (ctx.eax) {
        case 0u: goto bb_0043c6c6;
        case 1u: goto bb_0043c6c6;
        case 2u: goto bb_0043c6dd;
        case 3u: goto bb_0043c706;
        default: recomp_detail::trap_halt(ctx, 0x0043c818u, "switch_oob"); return;
    }
}
bb_0043c6c6: {
    // 0x0043c6c6: test eax, eax
    uint32_t t25 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t25);
    // 0x0043c6c8: jne 0x43c7fe
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043c7fe;
    goto bb_0043c6ce;
}
bb_0043c6dd: {
    // 0x0043c6dd: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x0043c6df: call 0x43cca0
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x0043c6e4u);
    sub_0043cca0(ctx, mem);
    // 0x0043c6e4: push esi
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, ctx.esi);
    // 0x0043c6e5: call 0x43dce0
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x0043c6eau);
    sub_0043dce0(ctx, mem);
    // 0x0043c6ea: cmp dword ptr [esi + 0xd8], 0
    uint32_t t29 = static_cast<uint32_t>(ctx.esi + 0x000000d8u);
    uint32_t t30 = mem.r32(t29);
    uint32_t t31 = static_cast<uint32_t>(t30 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t30, 0x00000000u, t31);
    // 0x0043c6f1: je 0x43c7fe
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c7fe;
    goto bb_0043c6f7;
}
bb_0043c706: {
    // 0x0043c706: push esi
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, ctx.esi);
    // 0x0043c707: call 0x43cfa0
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x0043c70cu);
    sub_0043cfa0(ctx, mem);
    // 0x0043c70c: xor edi, edi
    uint32_t t34 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t34);
    ctx.edi = static_cast<uint32_t>(t34);
    // 0x0043c70e: mov edi, edi
    ctx.edi = static_cast<uint32_t>(ctx.edi);
    goto bb_0043c710;
}
bb_0043c6ce: {
    // 0x0043c6ce: mov dword ptr [esi + 0xd8], 1
    uint32_t t35 = static_cast<uint32_t>(ctx.esi + 0x000000d8u);
    mem.w32(t35, 0x00000001u);
    // 0x0043c6d8: jmp 0x43c7fe
    goto bb_0043c7fe;
}
bb_0043c6f7: {
    // 0x0043c6f7: mov dword ptr [esi + 0xd8], 3
    uint32_t t36 = static_cast<uint32_t>(ctx.esi + 0x000000d8u);
    mem.w32(t36, 0x00000003u);
    // 0x0043c701: jmp 0x43c7fe
    goto bb_0043c7fe;
}
bb_0043c710: {
    // 0x0043c710: mov ecx, dword ptr [esi + 0x6c]
    uint32_t t37 = static_cast<uint32_t>(ctx.esi + 0x0000006cu);
    uint32_t t38 = mem.r32(t37);
    ctx.ecx = static_cast<uint32_t>(t38);
    // 0x0043c713: test ecx, ecx
    uint32_t t39 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t39);
    // 0x0043c715: je 0x43c74c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c74c;
    goto bb_0043c717;
}
bb_0043c74c: {
    // 0x0043c74c: xor edi, edi
    uint32_t t40 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t40);
    ctx.edi = static_cast<uint32_t>(t40);
    // 0x0043c74e: mov dword ptr [esp + 0xc], edi
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t41, ctx.edi);
    goto bb_0043c752;
}
bb_0043c717: {
    // 0x0043c717: mov eax, dword ptr [esi + 0x70]
    uint32_t t42 = static_cast<uint32_t>(ctx.esi + 0x00000070u);
    uint32_t t43 = mem.r32(t42);
    ctx.eax = static_cast<uint32_t>(t43);
    // 0x0043c71a: sub eax, ecx
    uint32_t t44 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t44);
    ctx.eax = static_cast<uint32_t>(t44);
    // 0x0043c71c: sar eax, 2
    uint32_t t45 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t46 = recomp_detail::sar<uint32_t>(ctx.eax, t45);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t45, t46);
    ctx.eax = static_cast<uint32_t>(t46);
    // 0x0043c71f: cmp edi, eax
    uint32_t t47 = static_cast<uint32_t>(ctx.edi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.eax, t47);
    // 0x0043c721: jae 0x43c74c
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0043c74c;
    goto bb_0043c723;
}
bb_0043c752: {
    // 0x0043c752: mov eax, dword ptr [esi + 0xb8]
    uint32_t t48 = static_cast<uint32_t>(ctx.esi + 0x000000b8u);
    uint32_t t49 = mem.r32(t48);
    ctx.eax = static_cast<uint32_t>(t49);
    // 0x0043c758: test eax, eax
    uint32_t t50 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t50);
    // 0x0043c75a: je 0x43c7f8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c7f8;
    goto bb_0043c760;
}
bb_0043c723: {
    // 0x0043c723: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0043c725: call 0x43c660
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, 0x0043c72au);
    sub_0043c660(ctx, mem);
    // 0x0043c72a: test eax, eax
    uint32_t t52 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t52);
    // 0x0043c72c: jne 0x43c74c
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043c74c;
    goto bb_0043c72e;
}
bb_0043c7f8: {
    // 0x0043c7f8: push esi
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, ctx.esi);
    // 0x0043c7f9: call 0x43ecb0
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, 0x0043c7feu);
    sub_0043ecb0(ctx, mem);
    goto bb_0043c7fe;
}
bb_0043c760: {
    // 0x0043c760: mov ecx, dword ptr [esi + 0xbc]
    uint32_t t55 = static_cast<uint32_t>(ctx.esi + 0x000000bcu);
    uint32_t t56 = mem.r32(t55);
    ctx.ecx = static_cast<uint32_t>(t56);
    // 0x0043c766: sub ecx, eax
    uint32_t t57 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t57);
    ctx.ecx = static_cast<uint32_t>(t57);
    // 0x0043c768: mov eax, 0x66666667
    ctx.eax = static_cast<uint32_t>(0x66666667u);
    // 0x0043c76d: imul ecx
    uint64_t t58 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t59 = static_cast<uint32_t>(t58);
    uint32_t t60 = static_cast<uint32_t>(t58 >> 32);
    ctx.eax = static_cast<uint32_t>(t59);
    ctx.edx = static_cast<uint32_t>(t60);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t58);
    // 0x0043c76f: sar edx, 3
    uint32_t t61 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t62 = recomp_detail::sar<uint32_t>(ctx.edx, t61);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t61, t62);
    ctx.edx = static_cast<uint32_t>(t62);
    // 0x0043c772: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x0043c774: shr eax, 0x1f
    uint32_t t63 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t64 = recomp_detail::shr<uint32_t>(ctx.eax, t63);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t63, t64);
    ctx.eax = static_cast<uint32_t>(t64);
    // 0x0043c777: add eax, edx
    uint32_t t65 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t65);
    ctx.eax = static_cast<uint32_t>(t65);
    // 0x0043c779: cmp edi, eax
    uint32_t t66 = static_cast<uint32_t>(ctx.edi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.eax, t66);
    // 0x0043c77b: jae 0x43c7f8
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0043c7f8;
    goto bb_0043c77d;
}
bb_0043c72e: {
    // 0x0043c72e: mov eax, dword ptr [esi + 0x88]
    uint32_t t67 = static_cast<uint32_t>(ctx.esi + 0x00000088u);
    uint32_t t68 = mem.r32(t67);
    ctx.eax = static_cast<uint32_t>(t68);
    // 0x0043c734: cmp edi, eax
    uint32_t t69 = static_cast<uint32_t>(ctx.edi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.eax, t69);
    // 0x0043c736: jl 0x43c747
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0043c747;
    goto bb_0043c738;
}
bb_0043c77d: {
    // 0x0043c77d: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0043c77f: call 0x43c660
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, 0x0043c784u);
    sub_0043c660(ctx, mem);
    // 0x0043c784: test eax, eax
    uint32_t t71 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t71);
    // 0x0043c786: jne 0x43c7f8
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043c7f8;
    goto bb_0043c788;
}
bb_0043c747: {
    // 0x0043c747: add edi, 1
    uint32_t t72 = static_cast<uint32_t>(ctx.edi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000001u, t72);
    ctx.edi = static_cast<uint32_t>(t72);
    // 0x0043c74a: jmp 0x43c710
    goto bb_0043c710;
}
bb_0043c738: {
    // 0x0043c738: add eax, 0xc
    uint32_t t73 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x0000000cu, t73);
    ctx.eax = static_cast<uint32_t>(t73);
    // 0x0043c73b: cmp edi, eax
    uint32_t t74 = static_cast<uint32_t>(ctx.edi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.eax, t74);
    // 0x0043c73d: jge 0x43c747
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0043c747;
    goto bb_0043c73f;
}
bb_0043c788: {
    // 0x0043c788: xor ebx, ebx
    uint32_t t75 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t75);
    ctx.ebx = static_cast<uint32_t>(t75);
    // 0x0043c78a: lea ebx, [ebx]
    ctx.ebx = static_cast<uint32_t>(ctx.ebx);
    goto bb_0043c790;
}
bb_0043c73f: {
    // 0x0043c73f: push esi
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    mem.w32(t76, ctx.esi);
    // 0x0043c740: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x0043c742: call 0x43f8f0
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, 0x0043c747u);
    sub_0043f8f0(ctx, mem);
    goto bb_0043c747;
}
bb_0043c790: {
    // 0x0043c790: push ebx
    uint32_t t78 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    mem.w32(t78, ctx.ebx);
    // 0x0043c791: push esi
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, ctx.esi);
    // 0x0043c792: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x0043c794: call 0x43f710
    uint32_t t80 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    mem.w32(t80, 0x0043c799u);
    sub_0043f710(ctx, mem);
    // 0x0043c799: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0043c79b: call 0x43c660
    uint32_t t81 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    mem.w32(t81, 0x0043c7a0u);
    sub_0043c660(ctx, mem);
    // 0x0043c7a0: test eax, eax
    uint32_t t82 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t82);
    // 0x0043c7a2: jne 0x43c7ac
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043c7ac;
    goto bb_0043c7a4;
}
bb_0043c7ac: {
    // 0x0043c7ac: mov eax, dword ptr [esi + 0xb8]
    uint32_t t83 = static_cast<uint32_t>(ctx.esi + 0x000000b8u);
    uint32_t t84 = mem.r32(t83);
    ctx.eax = static_cast<uint32_t>(t84);
    // 0x0043c7b2: test eax, eax
    uint32_t t85 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t85);
    // 0x0043c7b4: je 0x43c7d3
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c7d3;
    goto bb_0043c7b6;
}
bb_0043c7a4: {
    // 0x0043c7a4: add ebx, 1
    uint32_t t86 = static_cast<uint32_t>(ctx.ebx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebx, 0x00000001u, t86);
    ctx.ebx = static_cast<uint32_t>(t86);
    // 0x0043c7a7: cmp ebx, 2
    uint32_t t87 = static_cast<uint32_t>(ctx.ebx - 0x00000002u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, 0x00000002u, t87);
    // 0x0043c7aa: jl 0x43c790
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0043c790;
    goto bb_0043c7ac;
}
bb_0043c7d3: {
    // 0x0043c7d3: call 0x4e0bf2
    uint32_t t88 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t88);
    mem.w32(t88, 0x0043c7d8u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043c7d8;
}
bb_0043c7b6: {
    // 0x0043c7b6: mov ecx, dword ptr [esi + 0xbc]
    uint32_t t89 = static_cast<uint32_t>(ctx.esi + 0x000000bcu);
    uint32_t t90 = mem.r32(t89);
    ctx.ecx = static_cast<uint32_t>(t90);
    // 0x0043c7bc: sub ecx, eax
    uint32_t t91 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t91);
    ctx.ecx = static_cast<uint32_t>(t91);
    // 0x0043c7be: mov eax, 0x66666667
    ctx.eax = static_cast<uint32_t>(0x66666667u);
    // 0x0043c7c3: imul ecx
    uint64_t t92 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t93 = static_cast<uint32_t>(t92);
    uint32_t t94 = static_cast<uint32_t>(t92 >> 32);
    ctx.eax = static_cast<uint32_t>(t93);
    ctx.edx = static_cast<uint32_t>(t94);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t92);
    // 0x0043c7c5: sar edx, 3
    uint32_t t95 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t96 = recomp_detail::sar<uint32_t>(ctx.edx, t95);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t95, t96);
    ctx.edx = static_cast<uint32_t>(t96);
    // 0x0043c7c8: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x0043c7ca: shr eax, 0x1f
    uint32_t t97 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t98 = recomp_detail::shr<uint32_t>(ctx.eax, t97);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t97, t98);
    ctx.eax = static_cast<uint32_t>(t98);
    // 0x0043c7cd: add eax, edx
    uint32_t t99 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t99);
    ctx.eax = static_cast<uint32_t>(t99);
    // 0x0043c7cf: cmp edi, eax
    uint32_t t100 = static_cast<uint32_t>(ctx.edi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.eax, t100);
    // 0x0043c7d1: jb 0x43c7d8
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043c7d8;
    goto bb_0043c7d3;
}
bb_0043c7d8: {
    // 0x0043c7d8: mov eax, dword ptr [esp + 0xc]
    uint32_t t101 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t102 = mem.r32(t101);
    ctx.eax = static_cast<uint32_t>(t102);
    // 0x0043c7dc: mov ecx, dword ptr [esi + 0xb8]
    uint32_t t103 = static_cast<uint32_t>(ctx.esi + 0x000000b8u);
    uint32_t t104 = mem.r32(t103);
    ctx.ecx = static_cast<uint32_t>(t104);
    // 0x0043c7e2: mov dword ptr [eax + ecx], 0
    uint32_t t105 = static_cast<uint32_t>(ctx.eax + ctx.ecx);
    mem.w32(t105, 0x00000000u);
    // 0x0043c7e9: add edi, 1
    uint32_t t106 = static_cast<uint32_t>(ctx.edi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000001u, t106);
    ctx.edi = static_cast<uint32_t>(t106);
    // 0x0043c7ec: add eax, 0x14
    uint32_t t107 = static_cast<uint32_t>(ctx.eax + 0x00000014u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000014u, t107);
    ctx.eax = static_cast<uint32_t>(t107);
    // 0x0043c7ef: mov dword ptr [esp + 0xc], eax
    uint32_t t108 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t108, ctx.eax);
    // 0x0043c7f3: jmp 0x43c752
    goto bb_0043c752;
}
}

// sub_0043c830 | subsystem=Replay | canonical | 1 blocks | 79 insns
void sub_0043c830(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043c830: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0043c832: push 0x5163a3
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005163a3u);
    // 0x0043c837: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0043c83d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0043c83e: push ebx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ebx);
    // 0x0043c83f: push ebp
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebp);
    // 0x0043c840: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x0043c841: push edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edi);
    // 0x0043c842: mov eax, dword ptr [0x54b458]
    uint32_t t9 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x0043c847: xor eax, esp
    uint32_t t10 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0043c849: push eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.eax);
    // 0x0043c84a: lea eax, [esp + 0x14]
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0043c84e: mov dword ptr fs:[0], eax
    uint32_t t13 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t13, ctx.eax);
    // 0x0043c854: mov esi, dword ptr [esp + 0x24]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t15 = mem.r32(t14);
    ctx.esi = static_cast<uint32_t>(t15);
    // 0x0043c858: lea edi, [esi + 0x10]
    uint32_t t16 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    ctx.edi = static_cast<uint32_t>(t16);
    // 0x0043c85b: mov dword ptr [esi], 0x537020
    mem.w32(ctx.esi, 0x00537020u);
    // 0x0043c861: xor ebx, ebx
    uint32_t t17 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t17);
    ctx.ebx = static_cast<uint32_t>(t17);
    // 0x0043c863: mov eax, 0xf
    ctx.eax = static_cast<uint32_t>(0x0000000fu);
    // 0x0043c868: mov dword ptr [edi + 0x18], eax
    uint32_t t18 = static_cast<uint32_t>(ctx.edi + 0x00000018u);
    mem.w32(t18, ctx.eax);
    // 0x0043c86b: mov dword ptr [edi + 0x14], ebx
    uint32_t t19 = static_cast<uint32_t>(ctx.edi + 0x00000014u);
    mem.w32(t19, ctx.ebx);
    // 0x0043c86e: mov byte ptr [edi + 4], bl
    uint32_t t20 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    mem.w8(t20, recomp_detail::r8l(ctx.ebx));
    // 0x0043c871: lea ebp, [esi + 0x2c]
    uint32_t t21 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    ctx.ebp = static_cast<uint32_t>(t21);
    // 0x0043c874: mov dword ptr [esp + 0x1c], ebx
    uint32_t t22 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t22, ctx.ebx);
    // 0x0043c878: mov dword ptr [ebp + 0x18], eax
    uint32_t t23 = static_cast<uint32_t>(ctx.ebp + 0x00000018u);
    mem.w32(t23, ctx.eax);
    // 0x0043c87b: mov dword ptr [ebp + 0x14], ebx
    uint32_t t24 = static_cast<uint32_t>(ctx.ebp + 0x00000014u);
    mem.w32(t24, ctx.ebx);
    // 0x0043c87e: mov byte ptr [ebp + 4], bl
    uint32_t t25 = static_cast<uint32_t>(ctx.ebp + 0x00000004u);
    mem.w8(t25, recomp_detail::r8l(ctx.ebx));
    // 0x0043c881: mov dword ptr [esi + 0x4c], ebx
    uint32_t t26 = static_cast<uint32_t>(ctx.esi + 0x0000004cu);
    mem.w32(t26, ctx.ebx);
    // 0x0043c884: mov dword ptr [esi + 0x50], ebx
    uint32_t t27 = static_cast<uint32_t>(ctx.esi + 0x00000050u);
    mem.w32(t27, ctx.ebx);
    // 0x0043c887: mov dword ptr [esi + 0x54], ebx
    uint32_t t28 = static_cast<uint32_t>(ctx.esi + 0x00000054u);
    mem.w32(t28, ctx.ebx);
    // 0x0043c88a: mov dword ptr [esi + 0x5c], ebx
    uint32_t t29 = static_cast<uint32_t>(ctx.esi + 0x0000005cu);
    mem.w32(t29, ctx.ebx);
    // 0x0043c88d: mov dword ptr [esi + 0x60], ebx
    uint32_t t30 = static_cast<uint32_t>(ctx.esi + 0x00000060u);
    mem.w32(t30, ctx.ebx);
    // 0x0043c890: mov dword ptr [esi + 0x64], ebx
    uint32_t t31 = static_cast<uint32_t>(ctx.esi + 0x00000064u);
    mem.w32(t31, ctx.ebx);
    // 0x0043c893: mov dword ptr [esi + 0x6c], ebx
    uint32_t t32 = static_cast<uint32_t>(ctx.esi + 0x0000006cu);
    mem.w32(t32, ctx.ebx);
    // 0x0043c896: mov dword ptr [esi + 0x70], ebx
    uint32_t t33 = static_cast<uint32_t>(ctx.esi + 0x00000070u);
    mem.w32(t33, ctx.ebx);
    // 0x0043c899: mov dword ptr [esi + 0x74], ebx
    uint32_t t34 = static_cast<uint32_t>(ctx.esi + 0x00000074u);
    mem.w32(t34, ctx.ebx);
    // 0x0043c89c: mov dword ptr [esi + 0x94], ebx
    uint32_t t35 = static_cast<uint32_t>(ctx.esi + 0x00000094u);
    mem.w32(t35, ctx.ebx);
    // 0x0043c8a2: mov dword ptr [esi + 0x98], ebx
    uint32_t t36 = static_cast<uint32_t>(ctx.esi + 0x00000098u);
    mem.w32(t36, ctx.ebx);
    // 0x0043c8a8: mov dword ptr [esi + 0x9c], ebx
    uint32_t t37 = static_cast<uint32_t>(ctx.esi + 0x0000009cu);
    mem.w32(t37, ctx.ebx);
    // 0x0043c8ae: mov dword ptr [esi + 0xb8], ebx
    uint32_t t38 = static_cast<uint32_t>(ctx.esi + 0x000000b8u);
    mem.w32(t38, ctx.ebx);
    // 0x0043c8b4: mov dword ptr [esi + 0xbc], ebx
    uint32_t t39 = static_cast<uint32_t>(ctx.esi + 0x000000bcu);
    mem.w32(t39, ctx.ebx);
    // 0x0043c8ba: mov dword ptr [esi + 0xc0], ebx
    uint32_t t40 = static_cast<uint32_t>(ctx.esi + 0x000000c0u);
    mem.w32(t40, ctx.ebx);
    // 0x0043c8c0: mov byte ptr [esp + 0x1c], 6
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w8(t41, uint8_t{0x06u});
    // 0x0043c8c5: push 1
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, 0x00000001u);
    // 0x0043c8c7: push 0x535314
    uint32_t t43 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    mem.w32(t43, 0x00535314u);
    // 0x0043c8cc: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x0043c8ce: mov dword ptr [esi + 4], ebx
    uint32_t t44 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t44, ctx.ebx);
    // 0x0043c8d1: mov dword ptr [esi + 8], ebx
    uint32_t t45 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t45, ctx.ebx);
    // 0x0043c8d4: mov dword ptr [esi + 0xc], ebx
    uint32_t t46 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t46, ctx.ebx);
    // 0x0043c8d7: mov dword ptr [esi + 0x8c], ebx
    uint32_t t47 = static_cast<uint32_t>(ctx.esi + 0x0000008cu);
    mem.w32(t47, ctx.ebx);
    // 0x0043c8dd: mov dword ptr [esi + 0x88], ebx
    uint32_t t48 = static_cast<uint32_t>(ctx.esi + 0x00000088u);
    mem.w32(t48, ctx.ebx);
    // 0x0043c8e3: call 0x407c10
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, 0x0043c8e8u);
    sub_00407c10(ctx, mem);
    // 0x0043c8e8: push -1
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, 0xffffffffu);
    // 0x0043c8ea: push ebx
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, ctx.ebx);
    // 0x0043c8eb: push edi
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, ctx.edi);
    // 0x0043c8ec: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x0043c8ee: call 0x4079d0
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, 0x0043c8f3u);
    sub_004079d0(ctx, mem);
    // 0x0043c8f3: lea ecx, [esi + 0xb4]
    uint32_t t54 = static_cast<uint32_t>(ctx.esi + 0x000000b4u);
    ctx.ecx = static_cast<uint32_t>(t54);
    // 0x0043c8f9: mov dword ptr [esi + 0x78], ebx
    uint32_t t55 = static_cast<uint32_t>(ctx.esi + 0x00000078u);
    mem.w32(t55, ctx.ebx);
    // 0x0043c8fc: mov dword ptr [esi + 0x7c], ebx
    uint32_t t56 = static_cast<uint32_t>(ctx.esi + 0x0000007cu);
    mem.w32(t56, ctx.ebx);
    // 0x0043c8ff: mov dword ptr [esi + 0x80], ebx
    uint32_t t57 = static_cast<uint32_t>(ctx.esi + 0x00000080u);
    mem.w32(t57, ctx.ebx);
    // 0x0043c905: mov dword ptr [esi + 0xac], ebx
    uint32_t t58 = static_cast<uint32_t>(ctx.esi + 0x000000acu);
    mem.w32(t58, ctx.ebx);
    // 0x0043c90b: mov dword ptr [esi + 0xb0], ebx
    uint32_t t59 = static_cast<uint32_t>(ctx.esi + 0x000000b0u);
    mem.w32(t59, ctx.ebx);
    // 0x0043c911: mov dword ptr [esi + 0xa8], ebx
    uint32_t t60 = static_cast<uint32_t>(ctx.esi + 0x000000a8u);
    mem.w32(t60, ctx.ebx);
    // 0x0043c917: mov dword ptr [esi + 0x84], 1
    uint32_t t61 = static_cast<uint32_t>(ctx.esi + 0x00000084u);
    mem.w32(t61, 0x00000001u);
    // 0x0043c921: call 0x43fea0
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, 0x0043c926u);
    sub_0043fea0(ctx, mem);
    // 0x0043c926: mov dword ptr [esi + 0xc4], ebx
    uint32_t t63 = static_cast<uint32_t>(ctx.esi + 0x000000c4u);
    mem.w32(t63, ctx.ebx);
    // 0x0043c92c: mov dword ptr [esi + 0xc8], ebx
    uint32_t t64 = static_cast<uint32_t>(ctx.esi + 0x000000c8u);
    mem.w32(t64, ctx.ebx);
    // 0x0043c932: mov dword ptr [esi + 0xcc], ebx
    uint32_t t65 = static_cast<uint32_t>(ctx.esi + 0x000000ccu);
    mem.w32(t65, ctx.ebx);
    // 0x0043c938: mov dword ptr [esi + 0xd0], ebx
    uint32_t t66 = static_cast<uint32_t>(ctx.esi + 0x000000d0u);
    mem.w32(t66, ctx.ebx);
    // 0x0043c93e: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0043c940: mov ecx, dword ptr [esp + 0x14]
    uint32_t t67 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t68 = mem.r32(t67);
    ctx.ecx = static_cast<uint32_t>(t68);
    // 0x0043c944: mov dword ptr fs:[0], ecx
    uint32_t t69 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t69, ctx.ecx);
    // 0x0043c94b: pop ecx
    uint32_t t70 = ctx.esp;
    uint32_t t71 = mem.r32(t70);
    uint32_t t72 = static_cast<uint32_t>(t70 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    ctx.ecx = static_cast<uint32_t>(t71);
    // 0x0043c94c: pop edi
    uint32_t t73 = ctx.esp;
    uint32_t t74 = mem.r32(t73);
    uint32_t t75 = static_cast<uint32_t>(t73 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    ctx.edi = static_cast<uint32_t>(t74);
    // 0x0043c94d: pop esi
    uint32_t t76 = ctx.esp;
    uint32_t t77 = mem.r32(t76);
    uint32_t t78 = static_cast<uint32_t>(t76 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    ctx.esi = static_cast<uint32_t>(t77);
    // 0x0043c94e: pop ebp
    uint32_t t79 = ctx.esp;
    uint32_t t80 = mem.r32(t79);
    uint32_t t81 = static_cast<uint32_t>(t79 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    ctx.ebp = static_cast<uint32_t>(t80);
    // 0x0043c94f: pop ebx
    uint32_t t82 = ctx.esp;
    uint32_t t83 = mem.r32(t82);
    uint32_t t84 = static_cast<uint32_t>(t82 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    ctx.ebx = static_cast<uint32_t>(t83);
    // 0x0043c950: add esp, 0xc
    uint32_t t85 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t85);
    ctx.esp = static_cast<uint32_t>(t85);
    // 0x0043c953: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
}

// sub_0043c960 | subsystem=Replay | canonical | 3 blocks | 11 insns
void sub_0043c960(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043c960: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x0043c961: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x0043c963: call 0x43c980
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0043c968u);
    sub_0043c980(ctx, mem);
    // 0x0043c968: test byte ptr [esp + 8], 1
    uint32_t t2 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint8_t t3 = mem.r8(t2);
    uint8_t t4 = static_cast<uint8_t>(static_cast<uint32_t>(t3) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t4);
    // 0x0043c96d: je 0x43c978
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c978;
    goto bb_0043c96f;
}
bb_0043c978: {
    // 0x0043c978: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0043c97a: pop esi
    uint32_t t5 = ctx.esp;
    uint32_t t6 = mem.r32(t5);
    uint32_t t7 = static_cast<uint32_t>(t5 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x0043c97b: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0043c96f: {
    // 0x0043c96f: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x0043c970: call 0x4e02f3
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x0043c975u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043c975: add esp, 4
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t10);
    ctx.esp = static_cast<uint32_t>(t10);
    goto bb_0043c978;
}
}

// sub_0043c980 | subsystem=Replay | canonical | 13 blocks | 83 insns
void sub_0043c980(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043c980: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0043c982: push 0x516335
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00516335u);
    // 0x0043c987: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0043c98d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0043c98e: push ecx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ecx);
    // 0x0043c98f: push ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebx);
    // 0x0043c990: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x0043c991: push edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edi);
    // 0x0043c992: mov eax, dword ptr [0x54b458]
    uint32_t t9 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x0043c997: xor eax, esp
    uint32_t t10 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0043c999: push eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.eax);
    // 0x0043c99a: lea eax, [esp + 0x14]
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0043c99e: mov dword ptr fs:[0], eax
    uint32_t t13 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t13, ctx.eax);
    // 0x0043c9a4: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x0043c9a6: mov dword ptr [esp + 0x10], esi
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t14, ctx.esi);
    // 0x0043c9aa: mov dword ptr [esi], 0x537020
    mem.w32(ctx.esi, 0x00537020u);
    // 0x0043c9b0: lea edi, [esi + 0xb4]
    uint32_t t15 = static_cast<uint32_t>(ctx.esi + 0x000000b4u);
    ctx.edi = static_cast<uint32_t>(t15);
    // 0x0043c9b6: mov dword ptr [esp + 0x1c], 5
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t16, 0x00000005u);
    // 0x0043c9be: call 0x440330
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x0043c9c3u);
    sub_00440330(ctx, mem);
    // 0x0043c9c3: mov eax, dword ptr [esi + 0x94]
    uint32_t t18 = static_cast<uint32_t>(ctx.esi + 0x00000094u);
    uint32_t t19 = mem.r32(t18);
    ctx.eax = static_cast<uint32_t>(t19);
    // 0x0043c9c9: xor ebx, ebx
    uint32_t t20 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t20);
    ctx.ebx = static_cast<uint32_t>(t20);
    // 0x0043c9cb: cmp eax, ebx
    uint32_t t21 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t21);
    // 0x0043c9cd: je 0x43c9d8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c9d8;
    goto bb_0043c9cf;
}
bb_0043c9d8: {
    // 0x0043c9d8: mov dword ptr [esi + 0x94], ebx
    uint32_t t22 = static_cast<uint32_t>(ctx.esi + 0x00000094u);
    mem.w32(t22, ctx.ebx);
    // 0x0043c9de: mov dword ptr [esi + 0x98], ebx
    uint32_t t23 = static_cast<uint32_t>(ctx.esi + 0x00000098u);
    mem.w32(t23, ctx.ebx);
    // 0x0043c9e4: mov dword ptr [esi + 0x9c], ebx
    uint32_t t24 = static_cast<uint32_t>(ctx.esi + 0x0000009cu);
    mem.w32(t24, ctx.ebx);
    // 0x0043c9ea: mov eax, dword ptr [esi + 0x6c]
    uint32_t t25 = static_cast<uint32_t>(ctx.esi + 0x0000006cu);
    uint32_t t26 = mem.r32(t25);
    ctx.eax = static_cast<uint32_t>(t26);
    // 0x0043c9ed: cmp eax, ebx
    uint32_t t27 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t27);
    // 0x0043c9ef: je 0x43c9fa
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043c9fa;
    goto bb_0043c9f1;
}
bb_0043c9cf: {
    // 0x0043c9cf: push eax
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, ctx.eax);
    // 0x0043c9d0: call 0x4e02f3
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x0043c9d5u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043c9d5: add esp, 4
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t30);
    ctx.esp = static_cast<uint32_t>(t30);
    goto bb_0043c9d8;
}
bb_0043c9fa: {
    // 0x0043c9fa: mov dword ptr [esi + 0x6c], ebx
    uint32_t t31 = static_cast<uint32_t>(ctx.esi + 0x0000006cu);
    mem.w32(t31, ctx.ebx);
    // 0x0043c9fd: mov dword ptr [esi + 0x70], ebx
    uint32_t t32 = static_cast<uint32_t>(ctx.esi + 0x00000070u);
    mem.w32(t32, ctx.ebx);
    // 0x0043ca00: mov dword ptr [esi + 0x74], ebx
    uint32_t t33 = static_cast<uint32_t>(ctx.esi + 0x00000074u);
    mem.w32(t33, ctx.ebx);
    // 0x0043ca03: mov eax, dword ptr [esi + 0x5c]
    uint32_t t34 = static_cast<uint32_t>(ctx.esi + 0x0000005cu);
    uint32_t t35 = mem.r32(t34);
    ctx.eax = static_cast<uint32_t>(t35);
    // 0x0043ca06: cmp eax, ebx
    uint32_t t36 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t36);
    // 0x0043ca08: je 0x43ca13
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043ca13;
    goto bb_0043ca0a;
}
bb_0043c9f1: {
    // 0x0043c9f1: push eax
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, ctx.eax);
    // 0x0043c9f2: call 0x4e02f3
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, 0x0043c9f7u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043c9f7: add esp, 4
    uint32_t t39 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t39);
    ctx.esp = static_cast<uint32_t>(t39);
    goto bb_0043c9fa;
}
bb_0043ca13: {
    // 0x0043ca13: mov dword ptr [esi + 0x5c], ebx
    uint32_t t40 = static_cast<uint32_t>(ctx.esi + 0x0000005cu);
    mem.w32(t40, ctx.ebx);
    // 0x0043ca16: mov dword ptr [esi + 0x60], ebx
    uint32_t t41 = static_cast<uint32_t>(ctx.esi + 0x00000060u);
    mem.w32(t41, ctx.ebx);
    // 0x0043ca19: mov dword ptr [esi + 0x64], ebx
    uint32_t t42 = static_cast<uint32_t>(ctx.esi + 0x00000064u);
    mem.w32(t42, ctx.ebx);
    // 0x0043ca1c: mov eax, dword ptr [esi + 0x4c]
    uint32_t t43 = static_cast<uint32_t>(ctx.esi + 0x0000004cu);
    uint32_t t44 = mem.r32(t43);
    ctx.eax = static_cast<uint32_t>(t44);
    // 0x0043ca1f: cmp eax, ebx
    uint32_t t45 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t45);
    // 0x0043ca21: je 0x43ca2c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043ca2c;
    goto bb_0043ca23;
}
bb_0043ca0a: {
    // 0x0043ca0a: push eax
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, ctx.eax);
    // 0x0043ca0b: call 0x4e02f3
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, 0x0043ca10u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043ca10: add esp, 4
    uint32_t t48 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t48);
    ctx.esp = static_cast<uint32_t>(t48);
    goto bb_0043ca13;
}
bb_0043ca2c: {
    // 0x0043ca2c: mov dword ptr [esi + 0x4c], ebx
    uint32_t t49 = static_cast<uint32_t>(ctx.esi + 0x0000004cu);
    mem.w32(t49, ctx.ebx);
    // 0x0043ca2f: mov dword ptr [esi + 0x50], ebx
    uint32_t t50 = static_cast<uint32_t>(ctx.esi + 0x00000050u);
    mem.w32(t50, ctx.ebx);
    // 0x0043ca32: mov dword ptr [esi + 0x54], ebx
    uint32_t t51 = static_cast<uint32_t>(ctx.esi + 0x00000054u);
    mem.w32(t51, ctx.ebx);
    // 0x0043ca35: cmp dword ptr [esi + 0x44], 0x10
    uint32_t t52 = static_cast<uint32_t>(ctx.esi + 0x00000044u);
    uint32_t t53 = mem.r32(t52);
    uint32_t t54 = static_cast<uint32_t>(t53 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t53, 0x00000010u, t54);
    // 0x0043ca39: jb 0x43ca47
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043ca47;
    goto bb_0043ca3b;
}
bb_0043ca23: {
    // 0x0043ca23: push eax
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, ctx.eax);
    // 0x0043ca24: call 0x4e02f3
    uint32_t t56 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    mem.w32(t56, 0x0043ca29u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043ca29: add esp, 4
    uint32_t t57 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t57);
    ctx.esp = static_cast<uint32_t>(t57);
    goto bb_0043ca2c;
}
bb_0043ca47: {
    // 0x0043ca47: mov edi, 0xf
    ctx.edi = static_cast<uint32_t>(0x0000000fu);
    // 0x0043ca4c: mov dword ptr [esi + 0x44], edi
    uint32_t t58 = static_cast<uint32_t>(ctx.esi + 0x00000044u);
    mem.w32(t58, ctx.edi);
    // 0x0043ca4f: mov dword ptr [esi + 0x40], ebx
    uint32_t t59 = static_cast<uint32_t>(ctx.esi + 0x00000040u);
    mem.w32(t59, ctx.ebx);
    // 0x0043ca52: mov byte ptr [esi + 0x30], bl
    uint32_t t60 = static_cast<uint32_t>(ctx.esi + 0x00000030u);
    mem.w8(t60, recomp_detail::r8l(ctx.ebx));
    // 0x0043ca55: cmp dword ptr [esi + 0x28], 0x10
    uint32_t t61 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    uint32_t t62 = mem.r32(t61);
    uint32_t t63 = static_cast<uint32_t>(t62 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t62, 0x00000010u, t63);
    // 0x0043ca59: jb 0x43ca67
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043ca67;
    goto bb_0043ca5b;
}
bb_0043ca3b: {
    // 0x0043ca3b: mov eax, dword ptr [esi + 0x30]
    uint32_t t64 = static_cast<uint32_t>(ctx.esi + 0x00000030u);
    uint32_t t65 = mem.r32(t64);
    ctx.eax = static_cast<uint32_t>(t65);
    // 0x0043ca3e: push eax
    uint32_t t66 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    mem.w32(t66, ctx.eax);
    // 0x0043ca3f: call 0x4e02f3
    uint32_t t67 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t67);
    mem.w32(t67, 0x0043ca44u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043ca44: add esp, 4
    uint32_t t68 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t68);
    ctx.esp = static_cast<uint32_t>(t68);
    goto bb_0043ca47;
}
bb_0043ca67: {
    // 0x0043ca67: mov dword ptr [esi + 0x28], edi
    uint32_t t69 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    mem.w32(t69, ctx.edi);
    // 0x0043ca6a: mov dword ptr [esi + 0x24], ebx
    uint32_t t70 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    mem.w32(t70, ctx.ebx);
    // 0x0043ca6d: mov byte ptr [esi + 0x14], bl
    uint32_t t71 = static_cast<uint32_t>(ctx.esi + 0x00000014u);
    mem.w8(t71, recomp_detail::r8l(ctx.ebx));
    // 0x0043ca70: mov ecx, dword ptr [esp + 0x14]
    uint32_t t72 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t73 = mem.r32(t72);
    ctx.ecx = static_cast<uint32_t>(t73);
    // 0x0043ca74: mov dword ptr fs:[0], ecx
    uint32_t t74 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t74, ctx.ecx);
    // 0x0043ca7b: pop ecx
    uint32_t t75 = ctx.esp;
    uint32_t t76 = mem.r32(t75);
    uint32_t t77 = static_cast<uint32_t>(t75 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    ctx.ecx = static_cast<uint32_t>(t76);
    // 0x0043ca7c: pop edi
    uint32_t t78 = ctx.esp;
    uint32_t t79 = mem.r32(t78);
    uint32_t t80 = static_cast<uint32_t>(t78 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    ctx.edi = static_cast<uint32_t>(t79);
    // 0x0043ca7d: pop esi
    uint32_t t81 = ctx.esp;
    uint32_t t82 = mem.r32(t81);
    uint32_t t83 = static_cast<uint32_t>(t81 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t83);
    ctx.esi = static_cast<uint32_t>(t82);
    // 0x0043ca7e: pop ebx
    uint32_t t84 = ctx.esp;
    uint32_t t85 = mem.r32(t84);
    uint32_t t86 = static_cast<uint32_t>(t84 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t86);
    ctx.ebx = static_cast<uint32_t>(t85);
    // 0x0043ca7f: add esp, 0x10
    uint32_t t87 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t87);
    ctx.esp = static_cast<uint32_t>(t87);
    // 0x0043ca82: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043ca5b: {
    // 0x0043ca5b: mov ecx, dword ptr [esi + 0x14]
    uint32_t t88 = static_cast<uint32_t>(ctx.esi + 0x00000014u);
    uint32_t t89 = mem.r32(t88);
    ctx.ecx = static_cast<uint32_t>(t89);
    // 0x0043ca5e: push ecx
    uint32_t t90 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    mem.w32(t90, ctx.ecx);
    // 0x0043ca5f: call 0x4e02f3
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, 0x0043ca64u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043ca64: add esp, 4
    uint32_t t92 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t92);
    ctx.esp = static_cast<uint32_t>(t92);
    goto bb_0043ca67;
}
}

// sub_0043ca90 | subsystem=Replay | canonical | 12 blocks | 133 insns
void sub_0043ca90(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043ca90: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0043ca92: push 0x518978
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00518978u);
    // 0x0043ca97: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0043ca9d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0043ca9e: sub esp, 0x54
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000054u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000054u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x0043caa1: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0043caa6: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0043caa8: mov dword ptr [esp + 0x50], eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000050u);
    mem.w32(t8, ctx.eax);
    // 0x0043caac: push ebx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ebx);
    // 0x0043caad: push esi
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.esi);
    // 0x0043caae: mov eax, dword ptr [0x54b458]
    uint32_t t11 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x0043cab3: xor eax, esp
    uint32_t t12 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t12);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0043cab5: push eax
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, ctx.eax);
    // 0x0043cab6: lea eax, [esp + 0x60]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x0043caba: mov dword ptr fs:[0], eax
    uint32_t t15 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t15, ctx.eax);
    // 0x0043cac0: lea eax, [edi + 0xb4]
    uint32_t t16 = static_cast<uint32_t>(ctx.edi + 0x000000b4u);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0043cac6: xor ebx, ebx
    uint32_t t17 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t17);
    ctx.ebx = static_cast<uint32_t>(t17);
    // 0x0043cac8: push eax
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, ctx.eax);
    // 0x0043cac9: mov dword ptr [edi + 4], 2
    uint32_t t19 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    mem.w32(t19, 0x00000002u);
    // 0x0043cad0: mov dword ptr [edi + 0xa0], ebx
    uint32_t t20 = static_cast<uint32_t>(ctx.edi + 0x000000a0u);
    mem.w32(t20, ctx.ebx);
    // 0x0043cad6: mov dword ptr [edi + 0xa4], ebx
    uint32_t t21 = static_cast<uint32_t>(ctx.edi + 0x000000a4u);
    mem.w32(t21, ctx.ebx);
    // 0x0043cadc: call 0x43ffe0
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x0043cae1u);
    sub_0043ffe0(ctx, mem);
    // 0x0043cae1: push 0x48
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x00000048u);
    // 0x0043cae3: lea ecx, [esp + 0x18]
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.ecx = static_cast<uint32_t>(t24);
    // 0x0043cae7: push ebx
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, ctx.ebx);
    // 0x0043cae8: push ecx
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, ctx.ecx);
    // 0x0043cae9: call 0x4e6340
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x0043caeeu);
    hle_crt_004e6340(ctx, mem);
    // 0x0043caee: add esp, 0xc
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t28);
    ctx.esp = static_cast<uint32_t>(t28);
    // 0x0043caf1: lea esi, [esp + 0x14]
    uint32_t t29 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.esi = static_cast<uint32_t>(t29);
    // 0x0043caf5: call 0x43c360
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x0043cafau);
    sub_0043c360(ctx, mem);
    // 0x0043cafa: xor eax, eax
    uint32_t t31 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t31);
    ctx.eax = static_cast<uint32_t>(t31);
    // 0x0043cafc: lea esp, [esp]
    ctx.esp = static_cast<uint32_t>(ctx.esp);
}
bb_0043cb00: {
    // 0x0043cb00: mov cl, byte ptr [eax + 0x7b410e]
    uint32_t t32 = static_cast<uint32_t>(ctx.eax + 0x007b410eu);
    uint8_t t33 = mem.r8(t32);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t33));
    // 0x0043cb06: mov byte ptr [esp + eax + 0x3c], cl
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + ctx.eax);
    uint32_t t35 = static_cast<uint32_t>(t34 + 0x0000003cu);
    mem.w8(t35, recomp_detail::r8l(ctx.ecx));
    // 0x0043cb0a: add eax, 1
    uint32_t t36 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t36);
    ctx.eax = static_cast<uint32_t>(t36);
    // 0x0043cb0d: cmp cl, bl
    uint8_t t37 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) - static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.ecx), recomp_detail::r8l(ctx.ebx), t37);
    // 0x0043cb0f: jne 0x43cb00
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043cb00;
}
{
    // 0x0043cb11: xor eax, eax
    uint32_t t38 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t38);
    ctx.eax = static_cast<uint32_t>(t38);
}
bb_0043cb13: {
    // 0x0043cb13: mov cl, byte ptr [eax + 0x7b410e]
    uint32_t t39 = static_cast<uint32_t>(ctx.eax + 0x007b410eu);
    uint8_t t40 = mem.r8(t39);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t40));
    // 0x0043cb19: mov byte ptr [esp + eax + 0x3c], cl
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + ctx.eax);
    uint32_t t42 = static_cast<uint32_t>(t41 + 0x0000003cu);
    mem.w8(t42, recomp_detail::r8l(ctx.ecx));
    // 0x0043cb1d: add eax, 1
    uint32_t t43 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t43);
    ctx.eax = static_cast<uint32_t>(t43);
    // 0x0043cb20: cmp cl, bl
    uint8_t t44 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) - static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.ecx), recomp_detail::r8l(ctx.ebx), t44);
    // 0x0043cb22: jne 0x43cb13
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043cb13;
}
{
    // 0x0043cb24: mov edx, dword ptr [0x76e7d4]
    uint32_t t45 = mem.r32(0x0076e7d4u);
    ctx.edx = static_cast<uint32_t>(t45);
    // 0x0043cb2a: push 0xd3
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, 0x000000d3u);
    // 0x0043cb2f: push 0x536ab8
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, 0x00536ab8u);
    // 0x0043cb34: push 4
    uint32_t t48 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    mem.w32(t48, 0x00000004u);
    // 0x0043cb36: push 0xe4
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, 0x000000e4u);
    // 0x0043cb3b: mov dword ptr [esp + 0x28], ebx
    uint32_t t50 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t50, ctx.ebx);
    // 0x0043cb3f: mov dword ptr [esp + 0x2c], ebx
    uint32_t t51 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    mem.w32(t51, ctx.ebx);
    // 0x0043cb43: mov dword ptr [esp + 0x30], 0x15
    uint32_t t52 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    mem.w32(t52, 0x00000015u);
    // 0x0043cb4b: mov dword ptr [esp + 0x24], edx
    uint32_t t53 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t53, ctx.edx);
    // 0x0043cb4f: mov dword ptr [esp + 0x34], 0x14
    uint32_t t54 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    mem.w32(t54, 0x00000014u);
    // 0x0043cb57: mov byte ptr [esp + 0x4a], 4
    uint32_t t55 = static_cast<uint32_t>(ctx.esp + 0x0000004au);
    mem.w8(t55, uint8_t{0x04u});
    // 0x0043cb5c: call 0x4e0675
    uint32_t t56 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    mem.w32(t56, 0x0043cb61u);
    hle_crt_004e0675(ctx, mem);
    // 0x0043cb61: add esp, 0x10
    uint32_t t57 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t57);
    ctx.esp = static_cast<uint32_t>(t57);
    // 0x0043cb64: mov dword ptr [esp + 0x10], eax
    uint32_t t58 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t58, ctx.eax);
    // 0x0043cb68: cmp eax, ebx
    uint32_t t59 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t59);
    // 0x0043cb6a: mov dword ptr [esp + 0x68], ebx
    uint32_t t60 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    mem.w32(t60, ctx.ebx);
    // 0x0043cb6e: je 0x43cb7d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043cb7d;
    goto bb_0043cb70;
}
bb_0043cb7d: {
    // 0x0043cb7d: xor eax, eax
    uint32_t t61 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t61);
    ctx.eax = static_cast<uint32_t>(t61);
    goto bb_0043cb7f;
}
bb_0043cb70: {
    // 0x0043cb70: lea ecx, [esp + 0x14]
    uint32_t t62 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.ecx = static_cast<uint32_t>(t62);
    // 0x0043cb74: push ecx
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, ctx.ecx);
    // 0x0043cb75: push eax
    uint32_t t64 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    mem.w32(t64, ctx.eax);
    // 0x0043cb76: call 0x49ef70
    uint32_t t65 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t65);
    mem.w32(t65, 0x0043cb7bu);
    sub_0049ef70(ctx, mem);
    // 0x0043cb7b: jmp 0x43cb7f
}
bb_0043cb7f: {
    // 0x0043cb7f: mov dword ptr [esp + 0x68], 0xffffffff
    uint32_t t66 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    mem.w32(t66, 0xffffffffu);
    // 0x0043cb87: mov dword ptr [edi + 0xc], eax
    uint32_t t67 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    mem.w32(t67, ctx.eax);
    // 0x0043cb8a: mov dword ptr [eax + 0x40], 1
    uint32_t t68 = static_cast<uint32_t>(ctx.eax + 0x00000040u);
    mem.w32(t68, 0x00000001u);
    // 0x0043cb91: mov dword ptr [edi + 0x88], ebx
    uint32_t t69 = static_cast<uint32_t>(ctx.edi + 0x00000088u);
    mem.w32(t69, ctx.ebx);
    // 0x0043cb97: mov dword ptr [edi + 0x8c], ebx
    uint32_t t70 = static_cast<uint32_t>(ctx.edi + 0x0000008cu);
    mem.w32(t70, ctx.ebx);
    // 0x0043cb9d: mov dword ptr [esp + 0x10], ebx
    uint32_t t71 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t71, ctx.ebx);
    // 0x0043cba1: lea esi, [edi + 0x90]
    uint32_t t72 = static_cast<uint32_t>(ctx.edi + 0x00000090u);
    ctx.esi = static_cast<uint32_t>(t72);
    // 0x0043cba7: lea ebx, [esp + 0x10]
    uint32_t t73 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    ctx.ebx = static_cast<uint32_t>(t73);
    // 0x0043cbab: call 0x43fe30
    uint32_t t74 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    mem.w32(t74, 0x0043cbb0u);
    sub_0043fe30(ctx, mem);
    // 0x0043cbb0: push 0x536ad8
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, 0x00536ad8u);
    // 0x0043cbb5: xor eax, eax
    uint32_t t76 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t76);
    ctx.eax = static_cast<uint32_t>(t76);
    // 0x0043cbb7: xor ecx, ecx
    uint32_t t77 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t77);
    ctx.ecx = static_cast<uint32_t>(t77);
    // 0x0043cbb9: call 0x4c8aa0
    uint32_t t78 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    mem.w32(t78, 0x0043cbbeu);
    sub_004c8aa0(ctx, mem);
    // 0x0043cbbe: add esp, 4
    uint32_t t79 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t79);
    ctx.esp = static_cast<uint32_t>(t79);
    // 0x0043cbc1: mov dword ptr [edi + 0xac], eax
    uint32_t t80 = static_cast<uint32_t>(ctx.edi + 0x000000acu);
    mem.w32(t80, ctx.eax);
    // 0x0043cbc7: push 0x536aec
    uint32_t t81 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    mem.w32(t81, 0x00536aecu);
    // 0x0043cbcc: xor eax, eax
    uint32_t t82 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t82);
    ctx.eax = static_cast<uint32_t>(t82);
    // 0x0043cbce: xor ecx, ecx
    uint32_t t83 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t83);
    ctx.ecx = static_cast<uint32_t>(t83);
    // 0x0043cbd0: call 0x4c8aa0
    uint32_t t84 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    mem.w32(t84, 0x0043cbd5u);
    sub_004c8aa0(ctx, mem);
    // 0x0043cbd5: add esp, 4
    uint32_t t85 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t85);
    ctx.esp = static_cast<uint32_t>(t85);
    // 0x0043cbd8: mov dword ptr [edi + 0xb0], eax
    uint32_t t86 = static_cast<uint32_t>(ctx.edi + 0x000000b0u);
    mem.w32(t86, ctx.eax);
    // 0x0043cbde: xor eax, eax
    uint32_t t87 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t87);
    ctx.eax = static_cast<uint32_t>(t87);
    // 0x0043cbe0: lea edx, [edi + 0xc8]
    uint32_t t88 = static_cast<uint32_t>(ctx.edi + 0x000000c8u);
    ctx.edx = static_cast<uint32_t>(t88);
    // 0x0043cbe6: push edx
    uint32_t t89 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t89);
    mem.w32(t89, ctx.edx);
    // 0x0043cbe7: push eax
    uint32_t t90 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    mem.w32(t90, ctx.eax);
    // 0x0043cbe8: mov dword ptr [edi + 0xd8], 2
    uint32_t t91 = static_cast<uint32_t>(ctx.edi + 0x000000d8u);
    mem.w32(t91, 0x00000002u);
    // 0x0043cbf2: mov dword ptr [edi + 0xc4], eax
    uint32_t t92 = static_cast<uint32_t>(ctx.edi + 0x000000c4u);
    mem.w32(t92, ctx.eax);
    // 0x0043cbf8: mov esi, 1
    ctx.esi = static_cast<uint32_t>(0x00000001u);
    // 0x0043cbfd: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x0043cbff: push eax
    uint32_t t93 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    mem.w32(t93, ctx.eax);
    // 0x0043cc00: mov dword ptr [edi + 0xcc], 0x43c650
    uint32_t t94 = static_cast<uint32_t>(ctx.edi + 0x000000ccu);
    mem.w32(t94, 0x0043c650u);
    // 0x0043cc0a: mov dword ptr [edi + 0xd0], edi
    uint32_t t95 = static_cast<uint32_t>(ctx.edi + 0x000000d0u);
    mem.w32(t95, ctx.edi);
    // 0x0043cc10: mov dword ptr [edi + 0xc8], 0x4d2
    uint32_t t96 = static_cast<uint32_t>(ctx.edi + 0x000000c8u);
    mem.w32(t96, 0x000004d2u);
    // 0x0043cc1a: mov dword ptr [edi + 0xd4], esi
    uint32_t t97 = static_cast<uint32_t>(ctx.edi + 0x000000d4u);
    mem.w32(t97, ctx.esi);
    // 0x0043cc20: mov ecx, dword ptr [edi + 0xcc]
    uint32_t t98 = static_cast<uint32_t>(ctx.edi + 0x000000ccu);
    uint32_t t99 = mem.r32(t98);
    ctx.ecx = static_cast<uint32_t>(t99);
    // 0x0043cc26: push ecx
    uint32_t t100 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t100);
    mem.w32(t100, ctx.ecx);
    // 0x0043cc27: push 0
    uint32_t t101 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t101);
    mem.w32(t101, 0x00000000u);
    // 0x0043cc29: push 0
    uint32_t t102 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    mem.w32(t102, 0x00000000u);
    // 0x0043cc2b: call dword ptr [0x51b1c8]
    uint32_t t103 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    mem.w32(t103, 0x0043cc31u);
    hle_iat_call(ctx, mem, 0x0051b1c8u);
    // 0x0043cc31: mov dword ptr [edi + 0xc4], eax
    uint32_t t104 = static_cast<uint32_t>(ctx.edi + 0x000000c4u);
    mem.w32(t104, ctx.eax);
    // 0x0043cc37: mov ebx, dword ptr [edi + 0x80]
    uint32_t t105 = static_cast<uint32_t>(ctx.edi + 0x00000080u);
    uint32_t t106 = mem.r32(t105);
    ctx.ebx = static_cast<uint32_t>(t106);
    // 0x0043cc3d: test ebx, ebx
    uint32_t t107 = static_cast<uint32_t>(ctx.ebx & ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t107);
    // 0x0043cc3f: mov dword ptr [edi + 0x84], esi
    uint32_t t108 = static_cast<uint32_t>(ctx.edi + 0x00000084u);
    mem.w32(t108, ctx.esi);
    // 0x0043cc45: je 0x43cc73
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043cc73;
    goto bb_0043cc47;
}
bb_0043cc73: {
    // 0x0043cc73: mov dword ptr [edi + 0x80], 0
    uint32_t t109 = static_cast<uint32_t>(ctx.edi + 0x00000080u);
    mem.w32(t109, 0x00000000u);
    // 0x0043cc7d: mov ecx, dword ptr [esp + 0x60]
    uint32_t t110 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    uint32_t t111 = mem.r32(t110);
    ctx.ecx = static_cast<uint32_t>(t111);
    // 0x0043cc81: mov dword ptr fs:[0], ecx
    uint32_t t112 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t112, ctx.ecx);
    // 0x0043cc88: pop ecx
    uint32_t t113 = ctx.esp;
    uint32_t t114 = mem.r32(t113);
    uint32_t t115 = static_cast<uint32_t>(t113 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t115);
    ctx.ecx = static_cast<uint32_t>(t114);
    // 0x0043cc89: pop esi
    uint32_t t116 = ctx.esp;
    uint32_t t117 = mem.r32(t116);
    uint32_t t118 = static_cast<uint32_t>(t116 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    ctx.esi = static_cast<uint32_t>(t117);
    // 0x0043cc8a: pop ebx
    uint32_t t119 = ctx.esp;
    uint32_t t120 = mem.r32(t119);
    uint32_t t121 = static_cast<uint32_t>(t119 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t121);
    ctx.ebx = static_cast<uint32_t>(t120);
    // 0x0043cc8b: mov ecx, dword ptr [esp + 0x50]
    uint32_t t122 = static_cast<uint32_t>(ctx.esp + 0x00000050u);
    uint32_t t123 = mem.r32(t122);
    ctx.ecx = static_cast<uint32_t>(t123);
    // 0x0043cc8f: xor ecx, esp
    uint32_t t124 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t124);
    ctx.ecx = static_cast<uint32_t>(t124);
    // 0x0043cc91: call 0x4e02f8
    uint32_t t125 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t125);
    mem.w32(t125, 0x0043cc96u);
    hle_crt_004e02f8(ctx, mem);
    // 0x0043cc96: add esp, 0x60
    uint32_t t126 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000060u, t126);
    ctx.esp = static_cast<uint32_t>(t126);
    // 0x0043cc99: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043cc47: {
    // 0x0043cc47: push ebx
    uint32_t t127 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t127);
    mem.w32(t127, ctx.ebx);
    // 0x0043cc48: mov esi, 0x7b0928
    ctx.esi = static_cast<uint32_t>(0x007b0928u);
    // 0x0043cc4d: call 0x4bc9e0
    uint32_t t128 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t128);
    mem.w32(t128, 0x0043cc52u);
    sub_004bc9e0(ctx, mem);
    // 0x0043cc52: mov eax, dword ptr [ebx]
    uint32_t t129 = mem.r32(ctx.ebx);
    ctx.eax = static_cast<uint32_t>(t129);
    // 0x0043cc54: test eax, eax
    uint32_t t130 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t130);
    // 0x0043cc56: je 0x43cc63
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043cc63;
    goto bb_0043cc58;
}
bb_0043cc63: {
    // 0x0043cc63: push ebx
    uint32_t t131 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t131);
    mem.w32(t131, ctx.ebx);
    // 0x0043cc64: call 0x4e00d0
    uint32_t t132 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t132);
    mem.w32(t132, 0x0043cc69u);
    hle_crt_004e00d0(ctx, mem);
    // 0x0043cc69: add esp, 4
    uint32_t t133 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t133);
    ctx.esp = static_cast<uint32_t>(t133);
    // 0x0043cc6c: sub dword ptr [0x767440], 1
    uint32_t t134 = mem.r32(0x00767440u);
    uint32_t t135 = static_cast<uint32_t>(t134 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t134, 0x00000001u, t135);
    mem.w32(0x00767440u, t135);
    goto bb_0043cc73;
}
bb_0043cc58: {
    // 0x0043cc58: call 0x4bcfd0
    uint32_t t136 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t136);
    mem.w32(t136, 0x0043cc5du);
    sub_004bcfd0(ctx, mem);
    // 0x0043cc5d: mov dword ptr [ebx], 0
    mem.w32(ctx.ebx, 0x00000000u);
    goto bb_0043cc63;
}
}

// sub_0043cca0 | subsystem=Replay | canonical | 43 blocks | 221 insns
void sub_0043cca0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043cca0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0043cca2: push 0x5162b6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005162b6u);
    // 0x0043cca7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0043ccad: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0043ccae: sub esp, 0x18c
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x0000018cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x0000018cu, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x0043ccb4: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0043ccb9: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0043ccbb: mov dword ptr [esp + 0x188], eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000188u);
    mem.w32(t8, ctx.eax);
    // 0x0043ccc2: push ebx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ebx);
    // 0x0043ccc3: push ebp
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.ebp);
    // 0x0043ccc4: push esi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.esi);
    // 0x0043ccc5: push edi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.edi);
    // 0x0043ccc6: mov eax, dword ptr [0x54b458]
    uint32_t t13 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0043cccb: xor eax, esp
    uint32_t t14 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x0043cccd: push eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.eax);
    // 0x0043ccce: lea eax, [esp + 0x1a0]
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x000001a0u);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0043ccd5: mov dword ptr fs:[0], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t17, ctx.eax);
    // 0x0043ccdb: mov edi, ecx
    ctx.edi = static_cast<uint32_t>(ctx.ecx);
    // 0x0043ccdd: mov dword ptr [esp + 0x18], edi
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t18, ctx.edi);
    // 0x0043cce1: call 0x43d3f0
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x0043cce6u);
    sub_0043d3f0(ctx, mem);
    // 0x0043cce6: xor ebx, ebx
    uint32_t t20 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t20);
    ctx.ebx = static_cast<uint32_t>(t20);
    // 0x0043cce8: push -1
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0xffffffffu);
    // 0x0043ccea: push ebx
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, ctx.ebx);
    // 0x0043cceb: lea ebp, [edi + 0x2c]
    uint32_t t23 = static_cast<uint32_t>(ctx.edi + 0x0000002cu);
    ctx.ebp = static_cast<uint32_t>(t23);
    // 0x0043ccee: mov esi, 0xf
    ctx.esi = static_cast<uint32_t>(0x0000000fu);
    // 0x0043ccf3: push ebp
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, ctx.ebp);
    // 0x0043ccf4: lea ecx, [esp + 0x30]
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    ctx.ecx = static_cast<uint32_t>(t25);
    // 0x0043ccf8: mov dword ptr [esp + 0x48], esi
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    mem.w32(t26, ctx.esi);
    // 0x0043ccfc: mov dword ptr [esp + 0x44], ebx
    uint32_t t27 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    mem.w32(t27, ctx.ebx);
    // 0x0043cd00: mov byte ptr [esp + 0x34], bl
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    mem.w8(t28, recomp_detail::r8l(ctx.ebx));
    // 0x0043cd04: call 0x4079d0
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x0043cd09u);
    sub_004079d0(ctx, mem);
    // 0x0043cd09: push 2
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x00000002u);
    // 0x0043cd0b: push 0x536b04
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x00536b04u);
    // 0x0043cd10: lea eax, [esp + 0x2c]
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    ctx.eax = static_cast<uint32_t>(t32);
    // 0x0043cd14: mov dword ptr [esp + 0x1b0], ebx
    uint32_t t33 = static_cast<uint32_t>(ctx.esp + 0x000001b0u);
    mem.w32(t33, ctx.ebx);
    // 0x0043cd1b: call 0x414660
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x0043cd20u);
    sub_00414660(ctx, mem);
    // 0x0043cd20: cmp dword ptr [ebp + 0x18], 0x10
    uint32_t t35 = static_cast<uint32_t>(ctx.ebp + 0x00000018u);
    uint32_t t36 = mem.r32(t35);
    uint32_t t37 = static_cast<uint32_t>(t36 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t36, 0x00000010u, t37);
    // 0x0043cd24: jb 0x43cd2b
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043cd2b;
    goto bb_0043cd26;
}
bb_0043cd2b: {
    // 0x0043cd2b: add ebp, 4
    uint32_t t38 = static_cast<uint32_t>(ctx.ebp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebp, 0x00000004u, t38);
    ctx.ebp = static_cast<uint32_t>(t38);
    goto bb_0043cd2e;
}
bb_0043cd26: {
    // 0x0043cd26: mov ebp, dword ptr [ebp + 4]
    uint32_t t39 = static_cast<uint32_t>(ctx.ebp + 0x00000004u);
    uint32_t t40 = mem.r32(t39);
    ctx.ebp = static_cast<uint32_t>(t40);
    // 0x0043cd29: jmp 0x43cd2e
}
bb_0043cd2e: {
    // 0x0043cd2e: push ebp
    uint32_t t41 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    mem.w32(t41, ctx.ebp);
    // 0x0043cd2f: call dword ptr [0x51b214]
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, 0x0043cd35u);
    hle_iat_call(ctx, mem, 0x0051b214u);
    // 0x0043cd35: test eax, eax
    uint32_t t43 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t43);
    // 0x0043cd37: jne 0x43cd55
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043cd55;
    goto bb_0043cd39;
}
bb_0043cd55: {
    // 0x0043cd55: mov eax, dword ptr [esp + 0x28]
    uint32_t t44 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t45 = mem.r32(t44);
    ctx.eax = static_cast<uint32_t>(t45);
    // 0x0043cd59: mov ebp, 0x10
    ctx.ebp = static_cast<uint32_t>(0x00000010u);
    // 0x0043cd5e: cmp dword ptr [esp + 0x3c], ebp
    uint32_t t46 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    uint32_t t47 = mem.r32(t46);
    uint32_t t48 = static_cast<uint32_t>(t47 - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t47, ctx.ebp, t48);
    // 0x0043cd62: jae 0x43cd68
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0043cd68;
    goto bb_0043cd64;
}
bb_0043cd39: {
    // 0x0043cd39: cmp dword ptr [esp + 0x3c], 0x10
    uint32_t t49 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    uint32_t t50 = mem.r32(t49);
    uint32_t t51 = static_cast<uint32_t>(t50 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t50, 0x00000010u, t51);
    // 0x0043cd3e: jb 0x43cd4d
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043cd4d;
    goto bb_0043cd40;
}
bb_0043cd68: {
    // 0x0043cd68: lea ecx, [esp + 0x5c]
    uint32_t t52 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    ctx.ecx = static_cast<uint32_t>(t52);
    // 0x0043cd6c: push ecx
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, ctx.ecx);
    // 0x0043cd6d: push eax
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, ctx.eax);
    // 0x0043cd6e: call dword ptr [0x51b08c]
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, 0x0043cd74u);
    hle_iat_call(ctx, mem, 0x0051b08cu);
    // 0x0043cd74: cmp eax, -1
    uint32_t t56 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t56);
    // 0x0043cd77: mov dword ptr [esp + 0x20], eax
    uint32_t t57 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t57, ctx.eax);
    // 0x0043cd7b: jne 0x43cda9
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043cda9;
    goto bb_0043cd7d;
}
bb_0043cd64: {
    // 0x0043cd64: lea eax, [esp + 0x28]
    uint32_t t58 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.eax = static_cast<uint32_t>(t58);
    goto bb_0043cd68;
}
bb_0043cd4d: {
    // 0x0043cd4d: or eax, 0xffffffff
    uint32_t t59 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t59);
    ctx.eax = static_cast<uint32_t>(t59);
    // 0x0043cd50: jmp 0x43cf6d
    goto bb_0043cf6d;
}
bb_0043cd40: {
    // 0x0043cd40: mov eax, dword ptr [esp + 0x28]
    uint32_t t60 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t61 = mem.r32(t60);
    ctx.eax = static_cast<uint32_t>(t61);
    // 0x0043cd44: push eax
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, ctx.eax);
    // 0x0043cd45: call 0x4e02f3
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, 0x0043cd4au);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043cd4a: add esp, 4
    uint32_t t64 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t64);
    ctx.esp = static_cast<uint32_t>(t64);
    goto bb_0043cd4d;
}
bb_0043cda9: {
    // 0x0043cda9: push -1
    uint32_t t65 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t65);
    mem.w32(t65, 0xffffffffu);
    // 0x0043cdab: push ebx
    uint32_t t66 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    mem.w32(t66, ctx.ebx);
    // 0x0043cdac: lea eax, [edi + 0x2c]
    uint32_t t67 = static_cast<uint32_t>(ctx.edi + 0x0000002cu);
    ctx.eax = static_cast<uint32_t>(t67);
    // 0x0043cdaf: mov ebp, 1
    ctx.ebp = static_cast<uint32_t>(0x00000001u);
    // 0x0043cdb4: push eax
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, ctx.eax);
    // 0x0043cdb5: lea ecx, [esp + 0x4c]
    uint32_t t69 = static_cast<uint32_t>(ctx.esp + 0x0000004cu);
    ctx.ecx = static_cast<uint32_t>(t69);
    // 0x0043cdb9: mov dword ptr [esp + 0x28], ebp
    uint32_t t70 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t70, ctx.ebp);
    // 0x0043cdbd: mov dword ptr [esp + 0x64], esi
    uint32_t t71 = static_cast<uint32_t>(ctx.esp + 0x00000064u);
    mem.w32(t71, ctx.esi);
    // 0x0043cdc1: mov dword ptr [esp + 0x60], ebx
    uint32_t t72 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    mem.w32(t72, ctx.ebx);
    // 0x0043cdc5: mov byte ptr [esp + 0x50], bl
    uint32_t t73 = static_cast<uint32_t>(ctx.esp + 0x00000050u);
    mem.w8(t73, recomp_detail::r8l(ctx.ebx));
    // 0x0043cdc9: call 0x4079d0
    uint32_t t74 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    mem.w32(t74, 0x0043cdceu);
    sub_004079d0(ctx, mem);
    // 0x0043cdce: push ebp
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, ctx.ebp);
    // 0x0043cdcf: push 0x535310
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    mem.w32(t76, 0x00535310u);
    // 0x0043cdd4: lea eax, [esp + 0x48]
    uint32_t t77 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    ctx.eax = static_cast<uint32_t>(t77);
    // 0x0043cdd8: mov byte ptr [esp + 0x1b0], 1
    uint32_t t78 = static_cast<uint32_t>(ctx.esp + 0x000001b0u);
    mem.w8(t78, uint8_t{0x01u});
    // 0x0043cde0: call 0x414660
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, 0x0043cde5u);
    sub_00414660(ctx, mem);
    // 0x0043cde5: lea eax, [esp + 0x88]
    uint32_t t80 = static_cast<uint32_t>(ctx.esp + 0x00000088u);
    ctx.eax = static_cast<uint32_t>(t80);
    // 0x0043cdec: lea edx, [eax + 1]
    uint32_t t81 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.edx = static_cast<uint32_t>(t81);
    // 0x0043cdef: nop
    goto bb_0043cdf0;
}
bb_0043cd7d: {
    // 0x0043cd7d: cmp dword ptr [esp + 0x3c], ebp
    uint32_t t82 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    uint32_t t83 = mem.r32(t82);
    uint32_t t84 = static_cast<uint32_t>(t83 - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t83, ctx.ebp, t84);
    // 0x0043cd81: jb 0x43cd90
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043cd90;
    goto bb_0043cd83;
}
bb_0043cf6d: {
    // 0x0043cf6d: mov ecx, dword ptr [esp + 0x1a0]
    uint32_t t85 = static_cast<uint32_t>(ctx.esp + 0x000001a0u);
    uint32_t t86 = mem.r32(t85);
    ctx.ecx = static_cast<uint32_t>(t86);
    // 0x0043cf74: mov dword ptr fs:[0], ecx
    uint32_t t87 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t87, ctx.ecx);
    // 0x0043cf7b: pop ecx
    uint32_t t88 = ctx.esp;
    uint32_t t89 = mem.r32(t88);
    uint32_t t90 = static_cast<uint32_t>(t88 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    ctx.ecx = static_cast<uint32_t>(t89);
    // 0x0043cf7c: pop edi
    uint32_t t91 = ctx.esp;
    uint32_t t92 = mem.r32(t91);
    uint32_t t93 = static_cast<uint32_t>(t91 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    ctx.edi = static_cast<uint32_t>(t92);
    // 0x0043cf7d: pop esi
    uint32_t t94 = ctx.esp;
    uint32_t t95 = mem.r32(t94);
    uint32_t t96 = static_cast<uint32_t>(t94 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    ctx.esi = static_cast<uint32_t>(t95);
    // 0x0043cf7e: pop ebp
    uint32_t t97 = ctx.esp;
    uint32_t t98 = mem.r32(t97);
    uint32_t t99 = static_cast<uint32_t>(t97 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t99);
    ctx.ebp = static_cast<uint32_t>(t98);
    // 0x0043cf7f: pop ebx
    uint32_t t100 = ctx.esp;
    uint32_t t101 = mem.r32(t100);
    uint32_t t102 = static_cast<uint32_t>(t100 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    ctx.ebx = static_cast<uint32_t>(t101);
    // 0x0043cf80: mov ecx, dword ptr [esp + 0x188]
    uint32_t t103 = static_cast<uint32_t>(ctx.esp + 0x00000188u);
    uint32_t t104 = mem.r32(t103);
    ctx.ecx = static_cast<uint32_t>(t104);
    // 0x0043cf87: xor ecx, esp
    uint32_t t105 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t105);
    ctx.ecx = static_cast<uint32_t>(t105);
    // 0x0043cf89: call 0x4e02f8
    uint32_t t106 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t106);
    mem.w32(t106, 0x0043cf8eu);
    hle_crt_004e02f8(ctx, mem);
    // 0x0043cf8e: add esp, 0x198
    uint32_t t107 = static_cast<uint32_t>(ctx.esp + 0x00000198u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000198u, t107);
    ctx.esp = static_cast<uint32_t>(t107);
    // 0x0043cf94: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043cdf0: {
    // 0x0043cdf0: mov cl, byte ptr [eax]
    uint8_t t108 = mem.r8(ctx.eax);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t108));
    // 0x0043cdf2: add eax, 1
    uint32_t t109 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t109);
    ctx.eax = static_cast<uint32_t>(t109);
    // 0x0043cdf5: cmp cl, bl
    uint8_t t110 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) - static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.ecx), recomp_detail::r8l(ctx.ebx), t110);
    // 0x0043cdf7: jne 0x43cdf0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043cdf0;
    goto bb_0043cdf9;
}
bb_0043cd90: {
    // 0x0043cd90: mov eax, 0xfffffffe
    ctx.eax = static_cast<uint32_t>(0xfffffffeu);
    // 0x0043cd95: jmp 0x43cf6d
    goto bb_0043cf6d;
}
bb_0043cd83: {
    // 0x0043cd83: mov edx, dword ptr [esp + 0x28]
    uint32_t t111 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t112 = mem.r32(t111);
    ctx.edx = static_cast<uint32_t>(t112);
    // 0x0043cd87: push edx
    uint32_t t113 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t113);
    mem.w32(t113, ctx.edx);
    // 0x0043cd88: call 0x4e02f3
    uint32_t t114 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t114);
    mem.w32(t114, 0x0043cd8du);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043cd8d: add esp, 4
    uint32_t t115 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t115);
    ctx.esp = static_cast<uint32_t>(t115);
    goto bb_0043cd90;
}
bb_0043cdf9: {
    // 0x0043cdf9: sub eax, edx
    uint32_t t116 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t116);
    ctx.eax = static_cast<uint32_t>(t116);
    // 0x0043cdfb: push eax
    uint32_t t117 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t117);
    mem.w32(t117, ctx.eax);
    // 0x0043cdfc: lea eax, [esp + 0x8c]
    uint32_t t118 = static_cast<uint32_t>(ctx.esp + 0x0000008cu);
    ctx.eax = static_cast<uint32_t>(t118);
    // 0x0043ce03: push eax
    uint32_t t119 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t119);
    mem.w32(t119, ctx.eax);
    // 0x0043ce04: lea eax, [esp + 0x48]
    uint32_t t120 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    ctx.eax = static_cast<uint32_t>(t120);
    // 0x0043ce08: call 0x414660
    uint32_t t121 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t121);
    mem.w32(t121, 0x0043ce0du);
    sub_00414660(ctx, mem);
    // 0x0043ce0d: cmp dword ptr [esp + 0x58], 0x10
    uint32_t t122 = static_cast<uint32_t>(ctx.esp + 0x00000058u);
    uint32_t t123 = mem.r32(t122);
    uint32_t t124 = static_cast<uint32_t>(t123 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t123, 0x00000010u, t124);
    // 0x0043ce12: mov eax, dword ptr [esp + 0x44]
    uint32_t t125 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    uint32_t t126 = mem.r32(t125);
    ctx.eax = static_cast<uint32_t>(t126);
    // 0x0043ce16: jae 0x43ce1c
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0043ce1c;
    goto bb_0043ce18;
}
bb_0043ce1c: {
    // 0x0043ce1c: push eax
    uint32_t t127 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t127);
    mem.w32(t127, ctx.eax);
    // 0x0043ce1d: call dword ptr [0x51b214]
    uint32_t t128 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t128);
    mem.w32(t128, 0x0043ce23u);
    hle_iat_call(ctx, mem, 0x0051b214u);
    // 0x0043ce23: test eax, eax
    uint32_t t129 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t129);
    // 0x0043ce25: je 0x43ceb6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043ceb6;
    goto bb_0043ce2b;
}
bb_0043ce18: {
    // 0x0043ce18: lea eax, [esp + 0x44]
    uint32_t t130 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    ctx.eax = static_cast<uint32_t>(t130);
    goto bb_0043ce1c;
}
bb_0043ceb6: {
    // 0x0043ceb6: xor ebp, ebp
    uint32_t t131 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t131);
    ctx.ebp = static_cast<uint32_t>(t131);
    // 0x0043ceb8: jmp 0x43ce7e
    goto bb_0043ce7e;
}
bb_0043ce2b: {
    // 0x0043ce2b: lea edi, [esp + 0x88]
    uint32_t t132 = static_cast<uint32_t>(ctx.esp + 0x00000088u);
    ctx.edi = static_cast<uint32_t>(t132);
    // 0x0043ce32: mov esi, 0x535314
    ctx.esi = static_cast<uint32_t>(0x00535314u);
    // 0x0043ce37: mov ecx, 2
    ctx.ecx = static_cast<uint32_t>(0x00000002u);
    // 0x0043ce3c: xor edx, edx
    uint32_t t133 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t133);
    ctx.edx = static_cast<uint32_t>(t133);
    // 0x0043ce3e: repe cmpsb byte ptr [esi], byte ptr es:[edi]
    recomp_detail::exec_string_op<uint8_t>(ctx, mem, 2, 2);
    // 0x0043ce40: jne 0x43ce46
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043ce46;
    goto bb_0043ce42;
}
bb_0043ce7e: {
    // 0x0043ce7e: push 0x120
    uint32_t t134 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t134);
    mem.w32(t134, 0x00000120u);
    // 0x0043ce83: push 0x536ab8
    uint32_t t135 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t135);
    mem.w32(t135, 0x00536ab8u);
    // 0x0043ce88: push 4
    uint32_t t136 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t136);
    mem.w32(t136, 0x00000004u);
    // 0x0043ce8a: push 0x48
    uint32_t t137 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t137);
    mem.w32(t137, 0x00000048u);
    // 0x0043ce8c: call 0x4e0675
    uint32_t t138 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t138);
    mem.w32(t138, 0x0043ce91u);
    hle_crt_004e0675(ctx, mem);
    // 0x0043ce91: add esp, 0x10
    uint32_t t139 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t139);
    ctx.esp = static_cast<uint32_t>(t139);
    // 0x0043ce94: cmp eax, ebx
    uint32_t t140 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t140);
    // 0x0043ce96: je 0x43ceba
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043ceba;
    goto bb_0043ce98;
}
bb_0043ce46: {
    // 0x0043ce46: mov eax, dword ptr [esp + 0x1c]
    uint32_t t141 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t142 = mem.r32(t141);
    ctx.eax = static_cast<uint32_t>(t142);
    goto bb_0043ce4a;
}
bb_0043ce42: {
    // 0x0043ce42: xor eax, eax
    uint32_t t143 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t143);
    ctx.eax = static_cast<uint32_t>(t143);
    // 0x0043ce44: jmp 0x43ce4a
    goto bb_0043ce4a;
}
bb_0043ceba: {
    // 0x0043ceba: xor esi, esi
    uint32_t t144 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t144);
    ctx.esi = static_cast<uint32_t>(t144);
    goto bb_0043cebc;
}
bb_0043ce98: {
    // 0x0043ce98: mov dword ptr [eax + 0x20], esi
    uint32_t t145 = static_cast<uint32_t>(ctx.eax + 0x00000020u);
    mem.w32(t145, ctx.esi);
    // 0x0043ce9b: mov dword ptr [eax + 0x1c], ebx
    uint32_t t146 = static_cast<uint32_t>(ctx.eax + 0x0000001cu);
    mem.w32(t146, ctx.ebx);
    // 0x0043ce9e: mov byte ptr [eax + 0xc], bl
    uint32_t t147 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    mem.w8(t147, recomp_detail::r8l(ctx.ebx));
    // 0x0043cea1: mov dword ptr [eax + 0x3c], esi
    uint32_t t148 = static_cast<uint32_t>(ctx.eax + 0x0000003cu);
    mem.w32(t148, ctx.esi);
    // 0x0043cea4: mov dword ptr [eax + 0x38], ebx
    uint32_t t149 = static_cast<uint32_t>(ctx.eax + 0x00000038u);
    mem.w32(t149, ctx.ebx);
    // 0x0043cea7: mov byte ptr [eax + 0x28], bl
    uint32_t t150 = static_cast<uint32_t>(ctx.eax + 0x00000028u);
    mem.w8(t150, recomp_detail::r8l(ctx.ebx));
    // 0x0043ceaa: mov dword ptr [eax + 0x44], ebx
    uint32_t t151 = static_cast<uint32_t>(ctx.eax + 0x00000044u);
    mem.w32(t151, ctx.ebx);
    // 0x0043cead: mov dword ptr [eax], ebx
    mem.w32(ctx.eax, ctx.ebx);
    // 0x0043ceaf: mov dword ptr [eax + 0x40], ebx
    uint32_t t152 = static_cast<uint32_t>(ctx.eax + 0x00000040u);
    mem.w32(t152, ctx.ebx);
    // 0x0043ceb2: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0043ceb4: jmp 0x43cebc
    goto bb_0043cebc;
}
bb_0043ce4a: {
    // 0x0043ce4a: mov ecx, dword ptr [esp + 0x18]
    uint32_t t153 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t154 = mem.r32(t153);
    ctx.ecx = static_cast<uint32_t>(t154);
    // 0x0043ce4e: cmp dword ptr [ecx + 0x8c], ebx
    uint32_t t155 = static_cast<uint32_t>(ctx.ecx + 0x0000008cu);
    uint32_t t156 = mem.r32(t155);
    uint32_t t157 = static_cast<uint32_t>(t156 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t156, ctx.ebx, t157);
    // 0x0043ce54: jne 0x43ce71
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043ce71;
    goto bb_0043ce56;
}
bb_0043cebc: {
    // 0x0043cebc: lea eax, [esp + 0x88]
    uint32_t t158 = static_cast<uint32_t>(ctx.esp + 0x00000088u);
    ctx.eax = static_cast<uint32_t>(t158);
    // 0x0043cec3: mov dword ptr [esp + 0x1c], esi
    uint32_t t159 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t159, ctx.esi);
    // 0x0043cec7: lea ecx, [esi + 8]
    uint32_t t160 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    ctx.ecx = static_cast<uint32_t>(t160);
    // 0x0043ceca: lea edi, [eax + 1]
    uint32_t t161 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.edi = static_cast<uint32_t>(t161);
    // 0x0043cecd: lea ecx, [ecx]
    ctx.ecx = static_cast<uint32_t>(ctx.ecx);
    goto bb_0043ced0;
}
bb_0043ce71: {
    // 0x0043ce71: cmp eax, ebx
    uint32_t t162 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t162);
    // 0x0043ce73: je 0x43cf16
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043cf16;
    goto bb_0043ce79;
}
bb_0043ce56: {
    // 0x0043ce56: lea edi, [esp + 0x88]
    uint32_t t163 = static_cast<uint32_t>(ctx.esp + 0x00000088u);
    ctx.edi = static_cast<uint32_t>(t163);
    // 0x0043ce5d: mov esi, 0x535318
    ctx.esi = static_cast<uint32_t>(0x00535318u);
    // 0x0043ce62: mov ecx, 3
    ctx.ecx = static_cast<uint32_t>(0x00000003u);
    // 0x0043ce67: xor edx, edx
    uint32_t t164 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t164);
    ctx.edx = static_cast<uint32_t>(t164);
    // 0x0043ce69: repe cmpsb byte ptr [esi], byte ptr es:[edi]
    recomp_detail::exec_string_op<uint8_t>(ctx, mem, 2, 2);
    // 0x0043ce6b: je 0x43cf16
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043cf16;
    goto bb_0043ce71;
}
bb_0043ced0: {
    // 0x0043ced0: mov dl, byte ptr [eax]
    uint8_t t165 = mem.r8(ctx.eax);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t165));
    // 0x0043ced2: add eax, 1
    uint32_t t166 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t166);
    ctx.eax = static_cast<uint32_t>(t166);
    // 0x0043ced5: cmp dl, bl
    uint8_t t167 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)) - static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.edx), recomp_detail::r8l(ctx.ebx), t167);
    // 0x0043ced7: jne 0x43ced0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043ced0;
    goto bb_0043ced9;
}
bb_0043cf16: {
    // 0x0043cf16: mov byte ptr [esp + 0x1a8], bl
    uint32_t t168 = static_cast<uint32_t>(ctx.esp + 0x000001a8u);
    mem.w8(t168, recomp_detail::r8l(ctx.ebx));
    // 0x0043cf1d: cmp dword ptr [esp + 0x58], 0x10
    uint32_t t169 = static_cast<uint32_t>(ctx.esp + 0x00000058u);
    uint32_t t170 = mem.r32(t169);
    uint32_t t171 = static_cast<uint32_t>(t170 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t170, 0x00000010u, t171);
    // 0x0043cf22: jb 0x43cf31
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043cf31;
    goto bb_0043cf24;
}
bb_0043ce79: {
    // 0x0043ce79: mov esi, 0xf
    ctx.esi = static_cast<uint32_t>(0x0000000fu);
    goto bb_0043ce7e;
}
bb_0043ced9: {
    // 0x0043ced9: sub eax, edi
    uint32_t t172 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t172);
    ctx.eax = static_cast<uint32_t>(t172);
    // 0x0043cedb: push eax
    uint32_t t173 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t173);
    mem.w32(t173, ctx.eax);
    // 0x0043cedc: lea eax, [esp + 0x8c]
    uint32_t t174 = static_cast<uint32_t>(ctx.esp + 0x0000008cu);
    ctx.eax = static_cast<uint32_t>(t174);
    // 0x0043cee3: push eax
    uint32_t t175 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t175);
    mem.w32(t175, ctx.eax);
    // 0x0043cee4: call 0x407c10
    uint32_t t176 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t176);
    mem.w32(t176, 0x0043cee9u);
    sub_00407c10(ctx, mem);
    // 0x0043cee9: push -1
    uint32_t t177 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t177);
    mem.w32(t177, 0xffffffffu);
    // 0x0043ceeb: push ebx
    uint32_t t178 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t178);
    mem.w32(t178, ctx.ebx);
    // 0x0043ceec: lea edx, [esp + 0x48]
    uint32_t t179 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    ctx.edx = static_cast<uint32_t>(t179);
    // 0x0043cef0: lea ecx, [esi + 0x24]
    uint32_t t180 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    ctx.ecx = static_cast<uint32_t>(t180);
    // 0x0043cef3: push edx
    uint32_t t181 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t181);
    mem.w32(t181, ctx.edx);
    // 0x0043cef4: call 0x4079d0
    uint32_t t182 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t182);
    mem.w32(t182, 0x0043cef9u);
    sub_004079d0(ctx, mem);
    // 0x0043cef9: mov dword ptr [esi], ebp
    mem.w32(ctx.esi, ctx.ebp);
    // 0x0043cefb: mov esi, dword ptr [esp + 0x18]
    uint32_t t183 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t184 = mem.r32(t183);
    ctx.esi = static_cast<uint32_t>(t184);
    // 0x0043ceff: cmp ebp, ebx
    uint32_t t185 = static_cast<uint32_t>(ctx.ebp - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebp, ctx.ebx, t185);
    // 0x0043cf01: lea ebx, [esp + 0x1c]
    uint32_t t186 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.ebx = static_cast<uint32_t>(t186);
    // 0x0043cf05: je 0x43cf0c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043cf0c;
    goto bb_0043cf07;
}
bb_0043cf31: {
    // 0x0043cf31: mov edx, dword ptr [esp + 0x20]
    uint32_t t187 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t188 = mem.r32(t187);
    ctx.edx = static_cast<uint32_t>(t188);
    // 0x0043cf35: lea ecx, [esp + 0x5c]
    uint32_t t189 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    ctx.ecx = static_cast<uint32_t>(t189);
    // 0x0043cf39: push ecx
    uint32_t t190 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t190);
    mem.w32(t190, ctx.ecx);
    // 0x0043cf3a: push edx
    uint32_t t191 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t191);
    mem.w32(t191, ctx.edx);
    // 0x0043cf3b: call dword ptr [0x51b098]
    uint32_t t192 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t192);
    mem.w32(t192, 0x0043cf41u);
    hle_iat_call(ctx, mem, 0x0051b098u);
    // 0x0043cf41: test eax, eax
    uint32_t t193 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t193);
    // 0x0043cf43: jne 0x43cda0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043cda0;
    goto bb_0043cf49;
}
bb_0043cf24: {
    // 0x0043cf24: mov eax, dword ptr [esp + 0x44]
    uint32_t t194 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    uint32_t t195 = mem.r32(t194);
    ctx.eax = static_cast<uint32_t>(t195);
    // 0x0043cf28: push eax
    uint32_t t196 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t196);
    mem.w32(t196, ctx.eax);
    // 0x0043cf29: call 0x4e02f3
    uint32_t t197 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t197);
    mem.w32(t197, 0x0043cf2eu);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043cf2e: add esp, 4
    uint32_t t198 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t198);
    ctx.esp = static_cast<uint32_t>(t198);
    goto bb_0043cf31;
}
bb_0043cf0c: {
    // 0x0043cf0c: add esi, 0x58
    uint32_t t199 = static_cast<uint32_t>(ctx.esi + 0x00000058u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000058u, t199);
    ctx.esi = static_cast<uint32_t>(t199);
    goto bb_0043cf0f;
}
bb_0043cf07: {
    // 0x0043cf07: add esi, 0x48
    uint32_t t200 = static_cast<uint32_t>(ctx.esi + 0x00000048u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000048u, t200);
    ctx.esi = static_cast<uint32_t>(t200);
    // 0x0043cf0a: jmp 0x43cf0f
    goto bb_0043cf0f;
}
bb_0043cda0: {
    // 0x0043cda0: mov edi, dword ptr [esp + 0x18]
    uint32_t t201 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t202 = mem.r32(t201);
    ctx.edi = static_cast<uint32_t>(t202);
    // 0x0043cda4: mov esi, 0xf
    ctx.esi = static_cast<uint32_t>(0x0000000fu);
    goto bb_0043cda9;
}
bb_0043cf49: {
    // 0x0043cf49: mov eax, dword ptr [esp + 0x20]
    uint32_t t203 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t204 = mem.r32(t203);
    ctx.eax = static_cast<uint32_t>(t204);
    // 0x0043cf4d: push eax
    uint32_t t205 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t205);
    mem.w32(t205, ctx.eax);
    // 0x0043cf4e: call dword ptr [0x51b084]
    uint32_t t206 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t206);
    mem.w32(t206, 0x0043cf54u);
    hle_iat_call(ctx, mem, 0x0051b084u);
    // 0x0043cf54: cmp dword ptr [esp + 0x3c], 0x10
    uint32_t t207 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    uint32_t t208 = mem.r32(t207);
    uint32_t t209 = static_cast<uint32_t>(t208 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t208, 0x00000010u, t209);
    // 0x0043cf59: jb 0x43cf68
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043cf68;
    goto bb_0043cf5b;
}
bb_0043cf0f: {
    // 0x0043cf0f: call 0x43fe30
    uint32_t t210 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t210);
    mem.w32(t210, 0x0043cf14u);
    sub_0043fe30(ctx, mem);
    // 0x0043cf14: xor ebx, ebx
    uint32_t t211 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t211);
    ctx.ebx = static_cast<uint32_t>(t211);
    goto bb_0043cf16;
}
bb_0043cf68: {
    // 0x0043cf68: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    goto bb_0043cf6d;
}
bb_0043cf5b: {
    // 0x0043cf5b: mov ecx, dword ptr [esp + 0x28]
    uint32_t t212 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t213 = mem.r32(t212);
    ctx.ecx = static_cast<uint32_t>(t213);
    // 0x0043cf5f: push ecx
    uint32_t t214 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t214);
    mem.w32(t214, ctx.ecx);
    // 0x0043cf60: call 0x4e02f3
    uint32_t t215 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t215);
    mem.w32(t215, 0x0043cf65u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043cf65: add esp, 4
    uint32_t t216 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t216);
    ctx.esp = static_cast<uint32_t>(t216);
    goto bb_0043cf68;
}
}

// sub_0043cfa0 | subsystem=Replay | canonical | 71 blocks | 281 insns
void sub_0043cfa0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043cfa0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0043cfa2: push 0x516d4c
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00516d4cu);
    // 0x0043cfa7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0043cfad: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0043cfae: sub esp, 0x118
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000118u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000118u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x0043cfb4: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0043cfb9: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0043cfbb: mov dword ptr [esp + 0x110], eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000110u);
    mem.w32(t8, ctx.eax);
    // 0x0043cfc2: push ebx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ebx);
    // 0x0043cfc3: push ebp
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.ebp);
    // 0x0043cfc4: push esi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.esi);
    // 0x0043cfc5: push edi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.edi);
    // 0x0043cfc6: mov eax, dword ptr [0x54b458]
    uint32_t t13 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0043cfcb: xor eax, esp
    uint32_t t14 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x0043cfcd: push eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.eax);
    // 0x0043cfce: lea eax, [esp + 0x12c]
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x0000012cu);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0043cfd5: mov dword ptr fs:[0], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t17, ctx.eax);
    // 0x0043cfdb: mov ebp, dword ptr [esp + 0x13c]
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x0000013cu);
    uint32_t t19 = mem.r32(t18);
    ctx.ebp = static_cast<uint32_t>(t19);
    // 0x0043cfe2: lea eax, [esp + 0x74]
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x00000074u);
    ctx.eax = static_cast<uint32_t>(t20);
    // 0x0043cfe6: push eax
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, ctx.eax);
    // 0x0043cfe7: call 0x445f30
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x0043cfecu);
    sub_00445f30(ctx, mem);
    // 0x0043cfec: lea esi, [ebp + 0x68]
    uint32_t t23 = static_cast<uint32_t>(ctx.ebp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t23);
    // 0x0043cfef: mov dword ptr [esp + 0x134], 0
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x00000134u);
    mem.w32(t24, 0x00000000u);
    // 0x0043cffa: mov eax, dword ptr [esi + 4]
    uint32_t t25 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t26 = mem.r32(t25);
    ctx.eax = static_cast<uint32_t>(t26);
    // 0x0043cffd: test eax, eax
    uint32_t t27 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t27);
    // 0x0043cfff: mov dword ptr [esp + 0x1c], 1
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t28, 0x00000001u);
    // 0x0043d007: je 0x43d013
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d013;
    goto bb_0043d009;
}
bb_0043d013: {
    // 0x0043d013: mov eax, dword ptr [ebp + 0x5c]
    uint32_t t29 = static_cast<uint32_t>(ctx.ebp + 0x0000005cu);
    uint32_t t30 = mem.r32(t29);
    ctx.eax = static_cast<uint32_t>(t30);
    // 0x0043d016: test eax, eax
    uint32_t t31 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t31);
    // 0x0043d018: jne 0x43d01e
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043d01e;
    goto bb_0043d01a;
}
bb_0043d009: {
    // 0x0043d009: mov ecx, dword ptr [esi + 8]
    uint32_t t32 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t33 = mem.r32(t32);
    ctx.ecx = static_cast<uint32_t>(t33);
    // 0x0043d00c: sub ecx, eax
    uint32_t t34 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t34);
    ctx.ecx = static_cast<uint32_t>(t34);
    // 0x0043d00e: sar ecx, 2
    uint32_t t35 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t36 = recomp_detail::sar<uint32_t>(ctx.ecx, t35);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.ecx, t35, t36);
    ctx.ecx = static_cast<uint32_t>(t36);
    // 0x0043d011: jne 0x43d068
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043d068;
    goto bb_0043d013;
}
bb_0043d01e: {
    // 0x0043d01e: mov ecx, dword ptr [ebp + 0x60]
    uint32_t t37 = static_cast<uint32_t>(ctx.ebp + 0x00000060u);
    uint32_t t38 = mem.r32(t37);
    ctx.ecx = static_cast<uint32_t>(t38);
    // 0x0043d021: sub ecx, eax
    uint32_t t39 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t39);
    ctx.ecx = static_cast<uint32_t>(t39);
    // 0x0043d023: sar ecx, 2
    uint32_t t40 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t41 = recomp_detail::sar<uint32_t>(ctx.ecx, t40);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.ecx, t40, t41);
    ctx.ecx = static_cast<uint32_t>(t41);
    goto bb_0043d026;
}
bb_0043d01a: {
    // 0x0043d01a: xor ecx, ecx
    uint32_t t42 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t42);
    ctx.ecx = static_cast<uint32_t>(t42);
    // 0x0043d01c: jmp 0x43d026
    goto bb_0043d026;
}
bb_0043d068: {
    // 0x0043d068: mov eax, dword ptr [ebp + 0x4c]
    uint32_t t43 = static_cast<uint32_t>(ctx.ebp + 0x0000004cu);
    uint32_t t44 = mem.r32(t43);
    ctx.eax = static_cast<uint32_t>(t44);
    // 0x0043d06b: test eax, eax
    uint32_t t45 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t45);
    // 0x0043d06d: je 0x43d0c9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d0c9;
    goto bb_0043d06f;
}
bb_0043d026: {
    // 0x0043d026: mov edx, dword ptr [ebp + 0x4c]
    uint32_t t46 = static_cast<uint32_t>(ctx.ebp + 0x0000004cu);
    uint32_t t47 = mem.r32(t46);
    ctx.edx = static_cast<uint32_t>(t47);
    // 0x0043d029: test edx, edx
    uint32_t t48 = static_cast<uint32_t>(ctx.edx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t48);
    // 0x0043d02b: jne 0x43d031
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043d031;
    goto bb_0043d02d;
}
bb_0043d0c9: {
    // 0x0043d0c9: mov eax, dword ptr [ebp + 0x5c]
    uint32_t t49 = static_cast<uint32_t>(ctx.ebp + 0x0000005cu);
    uint32_t t50 = mem.r32(t49);
    ctx.eax = static_cast<uint32_t>(t50);
    // 0x0043d0cc: test eax, eax
    uint32_t t51 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t51);
    // 0x0043d0ce: je 0x43d2de
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d2de;
    goto bb_0043d0d4;
}
bb_0043d06f: {
    // 0x0043d06f: mov edx, dword ptr [ebp + 0x50]
    uint32_t t52 = static_cast<uint32_t>(ctx.ebp + 0x00000050u);
    uint32_t t53 = mem.r32(t52);
    ctx.edx = static_cast<uint32_t>(t53);
    // 0x0043d072: sub edx, eax
    uint32_t t54 = static_cast<uint32_t>(ctx.edx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.eax, t54);
    ctx.edx = static_cast<uint32_t>(t54);
    // 0x0043d074: sar edx, 2
    uint32_t t55 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t56 = recomp_detail::sar<uint32_t>(ctx.edx, t55);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t55, t56);
    ctx.edx = static_cast<uint32_t>(t56);
    // 0x0043d077: je 0x43d0c9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d0c9;
    goto bb_0043d079;
}
bb_0043d031: {
    // 0x0043d031: mov eax, dword ptr [ebp + 0x50]
    uint32_t t57 = static_cast<uint32_t>(ctx.ebp + 0x00000050u);
    uint32_t t58 = mem.r32(t57);
    ctx.eax = static_cast<uint32_t>(t58);
    // 0x0043d034: sub eax, edx
    uint32_t t59 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t59);
    ctx.eax = static_cast<uint32_t>(t59);
    // 0x0043d036: sar eax, 2
    uint32_t t60 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t61 = recomp_detail::sar<uint32_t>(ctx.eax, t60);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t60, t61);
    ctx.eax = static_cast<uint32_t>(t61);
    goto bb_0043d039;
}
bb_0043d02d: {
    // 0x0043d02d: xor eax, eax
    uint32_t t62 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t62);
    ctx.eax = static_cast<uint32_t>(t62);
    // 0x0043d02f: jmp 0x43d039
    goto bb_0043d039;
}
bb_0043d2de: {
    // 0x0043d2de: mov eax, dword ptr [ebp + 0x6c]
    uint32_t t63 = static_cast<uint32_t>(ctx.ebp + 0x0000006cu);
    uint32_t t64 = mem.r32(t63);
    ctx.eax = static_cast<uint32_t>(t64);
    // 0x0043d2e1: test eax, eax
    uint32_t t65 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t65);
    // 0x0043d2e3: je 0x43d2ef
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d2ef;
    goto bb_0043d2e5;
}
bb_0043d0d4: {
    // 0x0043d0d4: mov edx, dword ptr [ebp + 0x60]
    uint32_t t66 = static_cast<uint32_t>(ctx.ebp + 0x00000060u);
    uint32_t t67 = mem.r32(t66);
    ctx.edx = static_cast<uint32_t>(t67);
    // 0x0043d0d7: sub edx, eax
    uint32_t t68 = static_cast<uint32_t>(ctx.edx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.eax, t68);
    ctx.edx = static_cast<uint32_t>(t68);
    // 0x0043d0d9: sar edx, 2
    uint32_t t69 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t70 = recomp_detail::sar<uint32_t>(ctx.edx, t69);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t69, t70);
    ctx.edx = static_cast<uint32_t>(t70);
    // 0x0043d0dc: je 0x43d2de
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d2de;
    goto bb_0043d0e2;
}
bb_0043d079: {
    // 0x0043d079: test eax, eax
    uint32_t t71 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t71);
    // 0x0043d07b: je 0x43d087
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d087;
    goto bb_0043d07d;
}
bb_0043d039: {
    // 0x0043d039: add eax, ecx
    uint32_t t72 = static_cast<uint32_t>(ctx.eax + ctx.ecx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.ecx, t72);
    ctx.eax = static_cast<uint32_t>(t72);
    // 0x0043d03b: je 0x43d068
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d068;
    goto bb_0043d03d;
}
bb_0043d2ef: {
    // 0x0043d2ef: mov dword ptr [esp + 0x1c], 0xfffffffe
    uint32_t t73 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t73, 0xfffffffeu);
    goto bb_0043d2f7;
}
bb_0043d2e5: {
    // 0x0043d2e5: mov edx, dword ptr [ebp + 0x70]
    uint32_t t74 = static_cast<uint32_t>(ctx.ebp + 0x00000070u);
    uint32_t t75 = mem.r32(t74);
    ctx.edx = static_cast<uint32_t>(t75);
    // 0x0043d2e8: sub edx, eax
    uint32_t t76 = static_cast<uint32_t>(ctx.edx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.eax, t76);
    ctx.edx = static_cast<uint32_t>(t76);
    // 0x0043d2ea: sar edx, 2
    uint32_t t77 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t78 = recomp_detail::sar<uint32_t>(ctx.edx, t77);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t77, t78);
    ctx.edx = static_cast<uint32_t>(t78);
    // 0x0043d2ed: jne 0x43d2f7
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043d2f7;
    goto bb_0043d2ef;
}
bb_0043d0e2: {
    // 0x0043d0e2: test eax, eax
    uint32_t t79 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t79);
    // 0x0043d0e4: mov dword ptr [esp + 0x18], 1
    uint32_t t80 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t80, 0x00000001u);
    // 0x0043d0ec: je 0x43d0f8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d0f8;
    goto bb_0043d0ee;
}
bb_0043d087: {
    // 0x0043d087: call 0x4e0bf2
    uint32_t t81 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    mem.w32(t81, 0x0043d08cu);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d08c;
}
bb_0043d07d: {
    // 0x0043d07d: mov ecx, dword ptr [ebp + 0x50]
    uint32_t t82 = static_cast<uint32_t>(ctx.ebp + 0x00000050u);
    uint32_t t83 = mem.r32(t82);
    ctx.ecx = static_cast<uint32_t>(t83);
    // 0x0043d080: sub ecx, eax
    uint32_t t84 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t84);
    ctx.ecx = static_cast<uint32_t>(t84);
    // 0x0043d082: sar ecx, 2
    uint32_t t85 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t86 = recomp_detail::sar<uint32_t>(ctx.ecx, t85);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.ecx, t85, t86);
    ctx.ecx = static_cast<uint32_t>(t86);
    // 0x0043d085: jne 0x43d08c
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043d08c;
    goto bb_0043d087;
}
bb_0043d03d: {
    // 0x0043d03d: mov eax, dword ptr [ebp + 0x5c]
    uint32_t t87 = static_cast<uint32_t>(ctx.ebp + 0x0000005cu);
    uint32_t t88 = mem.r32(t87);
    ctx.eax = static_cast<uint32_t>(t88);
    // 0x0043d040: test eax, eax
    uint32_t t89 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t89);
    // 0x0043d042: jne 0x43d048
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043d048;
    goto bb_0043d044;
}
bb_0043d2f7: {
    // 0x0043d2f7: lea ecx, [esp + 0x74]
    uint32_t t90 = static_cast<uint32_t>(ctx.esp + 0x00000074u);
    ctx.ecx = static_cast<uint32_t>(t90);
    // 0x0043d2fb: mov dword ptr [ebp + 0x84], 1
    uint32_t t91 = static_cast<uint32_t>(ctx.ebp + 0x00000084u);
    mem.w32(t91, 0x00000001u);
    // 0x0043d305: call 0x446010
    uint32_t t92 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    mem.w32(t92, 0x0043d30au);
    sub_00446010(ctx, mem);
    // 0x0043d30a: mov eax, dword ptr [esp + 0x1c]
    uint32_t t93 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t94 = mem.r32(t93);
    ctx.eax = static_cast<uint32_t>(t94);
    // 0x0043d30e: mov ecx, dword ptr [esp + 0x12c]
    uint32_t t95 = static_cast<uint32_t>(ctx.esp + 0x0000012cu);
    uint32_t t96 = mem.r32(t95);
    ctx.ecx = static_cast<uint32_t>(t96);
    // 0x0043d315: mov dword ptr fs:[0], ecx
    uint32_t t97 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t97, ctx.ecx);
    // 0x0043d31c: pop ecx
    uint32_t t98 = ctx.esp;
    uint32_t t99 = mem.r32(t98);
    uint32_t t100 = static_cast<uint32_t>(t98 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t100);
    ctx.ecx = static_cast<uint32_t>(t99);
    // 0x0043d31d: pop edi
    uint32_t t101 = ctx.esp;
    uint32_t t102 = mem.r32(t101);
    uint32_t t103 = static_cast<uint32_t>(t101 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    ctx.edi = static_cast<uint32_t>(t102);
    // 0x0043d31e: pop esi
    uint32_t t104 = ctx.esp;
    uint32_t t105 = mem.r32(t104);
    uint32_t t106 = static_cast<uint32_t>(t104 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t106);
    ctx.esi = static_cast<uint32_t>(t105);
    // 0x0043d31f: pop ebp
    uint32_t t107 = ctx.esp;
    uint32_t t108 = mem.r32(t107);
    uint32_t t109 = static_cast<uint32_t>(t107 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t109);
    ctx.ebp = static_cast<uint32_t>(t108);
    // 0x0043d320: pop ebx
    uint32_t t110 = ctx.esp;
    uint32_t t111 = mem.r32(t110);
    uint32_t t112 = static_cast<uint32_t>(t110 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t112);
    ctx.ebx = static_cast<uint32_t>(t111);
    // 0x0043d321: mov ecx, dword ptr [esp + 0x110]
    uint32_t t113 = static_cast<uint32_t>(ctx.esp + 0x00000110u);
    uint32_t t114 = mem.r32(t113);
    ctx.ecx = static_cast<uint32_t>(t114);
    // 0x0043d328: xor ecx, esp
    uint32_t t115 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t115);
    ctx.ecx = static_cast<uint32_t>(t115);
    // 0x0043d32a: call 0x4e02f8
    uint32_t t116 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t116);
    mem.w32(t116, 0x0043d32fu);
    hle_crt_004e02f8(ctx, mem);
    // 0x0043d32f: add esp, 0x124
    uint32_t t117 = static_cast<uint32_t>(ctx.esp + 0x00000124u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000124u, t117);
    ctx.esp = static_cast<uint32_t>(t117);
    // 0x0043d335: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0043d0f8: {
    // 0x0043d0f8: call 0x4e0bf2
    uint32_t t118 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    mem.w32(t118, 0x0043d0fdu);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d0fd;
}
bb_0043d0ee: {
    // 0x0043d0ee: mov ecx, dword ptr [ebp + 0x60]
    uint32_t t119 = static_cast<uint32_t>(ctx.ebp + 0x00000060u);
    uint32_t t120 = mem.r32(t119);
    ctx.ecx = static_cast<uint32_t>(t120);
    // 0x0043d0f1: sub ecx, eax
    uint32_t t121 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t121);
    ctx.ecx = static_cast<uint32_t>(t121);
    // 0x0043d0f3: sar ecx, 2
    uint32_t t122 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t123 = recomp_detail::sar<uint32_t>(ctx.ecx, t122);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.ecx, t122, t123);
    ctx.ecx = static_cast<uint32_t>(t123);
    // 0x0043d0f6: jne 0x43d0fd
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043d0fd;
    goto bb_0043d0f8;
}
bb_0043d08c: {
    // 0x0043d08c: mov ebx, dword ptr [ebp + 0x4c]
    uint32_t t124 = static_cast<uint32_t>(ctx.ebp + 0x0000004cu);
    uint32_t t125 = mem.r32(t124);
    ctx.ebx = static_cast<uint32_t>(t125);
    // 0x0043d08f: call 0x43fe30
    uint32_t t126 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t126);
    mem.w32(t126, 0x0043d094u);
    sub_0043fe30(ctx, mem);
    // 0x0043d094: mov edi, dword ptr [ebp + 0x4c]
    uint32_t t127 = static_cast<uint32_t>(ctx.ebp + 0x0000004cu);
    uint32_t t128 = mem.r32(t127);
    ctx.edi = static_cast<uint32_t>(t128);
    // 0x0043d097: cmp edi, dword ptr [ebp + 0x50]
    uint32_t t129 = static_cast<uint32_t>(ctx.ebp + 0x00000050u);
    uint32_t t130 = mem.r32(t129);
    uint32_t t131 = static_cast<uint32_t>(ctx.edi - t130);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, t130, t131);
    // 0x0043d09a: jbe 0x43d0a1
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043d0a1;
    goto bb_0043d09c;
}
bb_0043d048: {
    // 0x0043d048: mov ecx, dword ptr [ebp + 0x60]
    uint32_t t132 = static_cast<uint32_t>(ctx.ebp + 0x00000060u);
    uint32_t t133 = mem.r32(t132);
    ctx.ecx = static_cast<uint32_t>(t133);
    // 0x0043d04b: sub ecx, eax
    uint32_t t134 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t134);
    ctx.ecx = static_cast<uint32_t>(t134);
    // 0x0043d04d: sar ecx, 2
    uint32_t t135 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t136 = recomp_detail::sar<uint32_t>(ctx.ecx, t135);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.ecx, t135, t136);
    ctx.ecx = static_cast<uint32_t>(t136);
    goto bb_0043d050;
}
bb_0043d044: {
    // 0x0043d044: xor ecx, ecx
    uint32_t t137 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t137);
    ctx.ecx = static_cast<uint32_t>(t137);
    // 0x0043d046: jmp 0x43d050
    goto bb_0043d050;
}
bb_0043d0fd: {
    // 0x0043d0fd: mov edx, dword ptr [ebp + 0x5c]
    uint32_t t138 = static_cast<uint32_t>(ctx.ebp + 0x0000005cu);
    uint32_t t139 = mem.r32(t138);
    ctx.edx = static_cast<uint32_t>(t139);
    // 0x0043d100: mov esi, dword ptr [edx]
    uint32_t t140 = mem.r32(ctx.edx);
    ctx.esi = static_cast<uint32_t>(t140);
    // 0x0043d102: lea ebx, [esi + 0x24]
    uint32_t t141 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    ctx.ebx = static_cast<uint32_t>(t141);
    // 0x0043d105: push 1
    uint32_t t142 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t142);
    mem.w32(t142, 0x00000001u);
    // 0x0043d107: mov edi, ebx
    ctx.edi = static_cast<uint32_t>(ctx.ebx);
    // 0x0043d109: mov dword ptr [esp + 0x18], esi
    uint32_t t143 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t143, ctx.esi);
    // 0x0043d10d: call 0x4400c0
    uint32_t t144 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t144);
    mem.w32(t144, 0x0043d112u);
    sub_004400c0(ctx, mem);
    // 0x0043d112: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x0043d114: cmp edi, -1
    uint32_t t145 = static_cast<uint32_t>(ctx.edi - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, 0xffffffffu, t145);
    // 0x0043d117: je 0x43d29b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d29b;
    goto bb_0043d11d;
}
bb_0043d0a1: {
    // 0x0043d0a1: mov eax, dword ptr [ebp + 0x50]
    uint32_t t146 = static_cast<uint32_t>(ctx.ebp + 0x00000050u);
    uint32_t t147 = mem.r32(t146);
    ctx.eax = static_cast<uint32_t>(t147);
    // 0x0043d0a4: lea ecx, [edi + 4]
    uint32_t t148 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    ctx.ecx = static_cast<uint32_t>(t148);
    // 0x0043d0a7: sub eax, ecx
    uint32_t t149 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t149);
    ctx.eax = static_cast<uint32_t>(t149);
    // 0x0043d0a9: sar eax, 2
    uint32_t t150 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t151 = recomp_detail::sar<uint32_t>(ctx.eax, t150);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t150, t151);
    ctx.eax = static_cast<uint32_t>(t151);
    // 0x0043d0ac: test eax, eax
    uint32_t t152 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t152);
    // 0x0043d0ae: jle 0x43d0c0
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0043d0c0;
    goto bb_0043d0b0;
}
bb_0043d09c: {
    // 0x0043d09c: call 0x4e0bf2
    uint32_t t153 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t153);
    mem.w32(t153, 0x0043d0a1u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d0a1;
}
bb_0043d050: {
    // 0x0043d050: test edx, edx
    uint32_t t154 = static_cast<uint32_t>(ctx.edx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t154);
    // 0x0043d052: jne 0x43d058
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043d058;
    goto bb_0043d054;
}
bb_0043d29b: {
    // 0x0043d29b: test esi, esi
    uint32_t t155 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t155);
    // 0x0043d29d: je 0x43d2ae
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d2ae;
    goto bb_0043d29f;
}
bb_0043d11d: {
    // 0x0043d11d: push 0x536b08
    uint32_t t156 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t156);
    mem.w32(t156, 0x00536b08u);
    // 0x0043d122: lea ecx, [esp + 0x5c]
    uint32_t t157 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    ctx.ecx = static_cast<uint32_t>(t157);
    // 0x0043d126: call 0x407810
    uint32_t t158 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t158);
    mem.w32(t158, 0x0043d12bu);
    sub_00407810(ctx, mem);
    // 0x0043d12b: mov byte ptr [esp + 0x134], 1
    uint32_t t159 = static_cast<uint32_t>(ctx.esp + 0x00000134u);
    mem.w8(t159, uint8_t{0x01u});
    // 0x0043d133: cmp edi, dword ptr [ebx + 0x14]
    uint32_t t160 = static_cast<uint32_t>(ctx.ebx + 0x00000014u);
    uint32_t t161 = mem.r32(t160);
    uint32_t t162 = static_cast<uint32_t>(ctx.edi - t161);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, t161, t162);
    // 0x0043d136: jbe 0x43d13d
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043d13d;
    goto bb_0043d138;
}
bb_0043d0c0: {
    // 0x0043d0c0: add dword ptr [ebp + 0x50], -4
    uint32_t t163 = static_cast<uint32_t>(ctx.ebp + 0x00000050u);
    uint32_t t164 = mem.r32(t163);
    uint32_t t165 = static_cast<uint32_t>(t164 + 0xfffffffcu);
    recomp_detail::update_flags_add<uint32_t>(ctx, t164, 0xfffffffcu, t165);
    mem.w32(t163, t165);
    // 0x0043d0c4: jmp 0x43d2de
    goto bb_0043d2de;
}
bb_0043d0b0: {
    // 0x0043d0b0: add eax, eax
    uint32_t t166 = static_cast<uint32_t>(ctx.eax + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.eax, t166);
    ctx.eax = static_cast<uint32_t>(t166);
    // 0x0043d0b2: add eax, eax
    uint32_t t167 = static_cast<uint32_t>(ctx.eax + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.eax, t167);
    ctx.eax = static_cast<uint32_t>(t167);
    // 0x0043d0b4: push eax
    uint32_t t168 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t168);
    mem.w32(t168, ctx.eax);
    // 0x0043d0b5: push ecx
    uint32_t t169 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t169);
    mem.w32(t169, ctx.ecx);
    // 0x0043d0b6: push eax
    uint32_t t170 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t170);
    mem.w32(t170, ctx.eax);
    // 0x0043d0b7: push edi
    uint32_t t171 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t171);
    mem.w32(t171, ctx.edi);
    // 0x0043d0b8: call 0x4e0c02
    uint32_t t172 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t172);
    mem.w32(t172, 0x0043d0bdu);
    hle_crt_004e0c02(ctx, mem);
    // 0x0043d0bd: add esp, 0x10
    uint32_t t173 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t173);
    ctx.esp = static_cast<uint32_t>(t173);
    goto bb_0043d0c0;
}
bb_0043d058: {
    // 0x0043d058: mov eax, dword ptr [ebp + 0x50]
    uint32_t t174 = static_cast<uint32_t>(ctx.ebp + 0x00000050u);
    uint32_t t175 = mem.r32(t174);
    ctx.eax = static_cast<uint32_t>(t175);
    // 0x0043d05b: sub eax, edx
    uint32_t t176 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t176);
    ctx.eax = static_cast<uint32_t>(t176);
    // 0x0043d05d: sar eax, 2
    uint32_t t177 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t178 = recomp_detail::sar<uint32_t>(ctx.eax, t177);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t177, t178);
    ctx.eax = static_cast<uint32_t>(t178);
    goto bb_0043d060;
}
bb_0043d054: {
    // 0x0043d054: xor eax, eax
    uint32_t t179 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t179);
    ctx.eax = static_cast<uint32_t>(t179);
    // 0x0043d056: jmp 0x43d060
    goto bb_0043d060;
}
bb_0043d2ae: {
    // 0x0043d2ae: mov edi, dword ptr [ebp + 0x5c]
    uint32_t t180 = static_cast<uint32_t>(ctx.ebp + 0x0000005cu);
    uint32_t t181 = mem.r32(t180);
    ctx.edi = static_cast<uint32_t>(t181);
    // 0x0043d2b1: cmp edi, dword ptr [ebp + 0x60]
    uint32_t t182 = static_cast<uint32_t>(ctx.ebp + 0x00000060u);
    uint32_t t183 = mem.r32(t182);
    uint32_t t184 = static_cast<uint32_t>(ctx.edi - t183);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, t183, t184);
    // 0x0043d2b4: jbe 0x43d2bb
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043d2bb;
    goto bb_0043d2b6;
}
bb_0043d29f: {
    // 0x0043d29f: push esi
    uint32_t t185 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t185);
    mem.w32(t185, ctx.esi);
    // 0x0043d2a0: call 0x43c530
    uint32_t t186 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t186);
    mem.w32(t186, 0x0043d2a5u);
    sub_0043c530(ctx, mem);
    // 0x0043d2a5: push esi
    uint32_t t187 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t187);
    mem.w32(t187, ctx.esi);
    // 0x0043d2a6: call 0x4e02f3
    uint32_t t188 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t188);
    mem.w32(t188, 0x0043d2abu);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043d2ab: add esp, 4
    uint32_t t189 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t189);
    ctx.esp = static_cast<uint32_t>(t189);
    goto bb_0043d2ae;
}
bb_0043d13d: {
    // 0x0043d13d: cmp dword ptr [ebx + 0x18], 0x10
    uint32_t t190 = static_cast<uint32_t>(ctx.ebx + 0x00000018u);
    uint32_t t191 = mem.r32(t190);
    uint32_t t192 = static_cast<uint32_t>(t191 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t191, 0x00000010u, t192);
    // 0x0043d141: jb 0x43d148
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043d148;
    goto bb_0043d143;
}
bb_0043d138: {
    // 0x0043d138: call 0x4e0bf2
    uint32_t t193 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t193);
    mem.w32(t193, 0x0043d13du);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d13d;
}
bb_0043d060: {
    // 0x0043d060: add eax, ecx
    uint32_t t194 = static_cast<uint32_t>(ctx.eax + ctx.ecx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.ecx, t194);
    ctx.eax = static_cast<uint32_t>(t194);
    // 0x0043d062: push eax
    uint32_t t195 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t195);
    mem.w32(t195, ctx.eax);
    // 0x0043d063: call 0x43fd70
    uint32_t t196 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t196);
    mem.w32(t196, 0x0043d068u);
    sub_0043fd70(ctx, mem);
    goto bb_0043d068;
}
bb_0043d2bb: {
    // 0x0043d2bb: mov eax, dword ptr [ebp + 0x60]
    uint32_t t197 = static_cast<uint32_t>(ctx.ebp + 0x00000060u);
    uint32_t t198 = mem.r32(t197);
    ctx.eax = static_cast<uint32_t>(t198);
    // 0x0043d2be: lea ecx, [edi + 4]
    uint32_t t199 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    ctx.ecx = static_cast<uint32_t>(t199);
    // 0x0043d2c1: sub eax, ecx
    uint32_t t200 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t200);
    ctx.eax = static_cast<uint32_t>(t200);
    // 0x0043d2c3: sar eax, 2
    uint32_t t201 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t202 = recomp_detail::sar<uint32_t>(ctx.eax, t201);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t201, t202);
    ctx.eax = static_cast<uint32_t>(t202);
    // 0x0043d2c6: test eax, eax
    uint32_t t203 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t203);
    // 0x0043d2c8: jle 0x43d2da
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0043d2da;
    goto bb_0043d2ca;
}
bb_0043d2b6: {
    // 0x0043d2b6: call 0x4e0bf2
    uint32_t t204 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t204);
    mem.w32(t204, 0x0043d2bbu);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d2bb;
}
bb_0043d148: {
    // 0x0043d148: lea eax, [ebx + 4]
    uint32_t t205 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    ctx.eax = static_cast<uint32_t>(t205);
    goto bb_0043d14b;
}
bb_0043d143: {
    // 0x0043d143: mov eax, dword ptr [ebx + 4]
    uint32_t t206 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    uint32_t t207 = mem.r32(t206);
    ctx.eax = static_cast<uint32_t>(t207);
    // 0x0043d146: jmp 0x43d14b
    goto bb_0043d14b;
}
bb_0043d2da: {
    // 0x0043d2da: add dword ptr [ebp + 0x60], -4
    uint32_t t208 = static_cast<uint32_t>(ctx.ebp + 0x00000060u);
    uint32_t t209 = mem.r32(t208);
    uint32_t t210 = static_cast<uint32_t>(t209 + 0xfffffffcu);
    recomp_detail::update_flags_add<uint32_t>(ctx, t209, 0xfffffffcu, t210);
    mem.w32(t208, t210);
    goto bb_0043d2de;
}
bb_0043d2ca: {
    // 0x0043d2ca: add eax, eax
    uint32_t t211 = static_cast<uint32_t>(ctx.eax + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.eax, t211);
    ctx.eax = static_cast<uint32_t>(t211);
    // 0x0043d2cc: add eax, eax
    uint32_t t212 = static_cast<uint32_t>(ctx.eax + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.eax, t212);
    ctx.eax = static_cast<uint32_t>(t212);
    // 0x0043d2ce: push eax
    uint32_t t213 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t213);
    mem.w32(t213, ctx.eax);
    // 0x0043d2cf: push ecx
    uint32_t t214 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t214);
    mem.w32(t214, ctx.ecx);
    // 0x0043d2d0: push eax
    uint32_t t215 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t215);
    mem.w32(t215, ctx.eax);
    // 0x0043d2d1: push edi
    uint32_t t216 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t216);
    mem.w32(t216, ctx.edi);
    // 0x0043d2d2: call 0x4e0c02
    uint32_t t217 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t217);
    mem.w32(t217, 0x0043d2d7u);
    hle_crt_004e0c02(ctx, mem);
    // 0x0043d2d7: add esp, 0x10
    uint32_t t218 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t218);
    ctx.esp = static_cast<uint32_t>(t218);
    goto bb_0043d2da;
}
bb_0043d14b: {
    // 0x0043d14b: add eax, edi
    uint32_t t219 = static_cast<uint32_t>(ctx.eax + ctx.edi);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edi, t219);
    ctx.eax = static_cast<uint32_t>(t219);
    // 0x0043d14d: push eax
    uint32_t t220 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t220);
    mem.w32(t220, ctx.eax);
    // 0x0043d14e: lea ecx, [esp + 0x40]
    uint32_t t221 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    ctx.ecx = static_cast<uint32_t>(t221);
    // 0x0043d152: call 0x407810
    uint32_t t222 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t222);
    mem.w32(t222, 0x0043d157u);
    sub_00407810(ctx, mem);
    // 0x0043d157: lea eax, [esp + 0x3c]
    uint32_t t223 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    ctx.eax = static_cast<uint32_t>(t223);
    // 0x0043d15b: push eax
    uint32_t t224 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t224);
    mem.w32(t224, ctx.eax);
    // 0x0043d15c: lea ecx, [esp + 0x24]
    uint32_t t225 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    ctx.ecx = static_cast<uint32_t>(t225);
    // 0x0043d160: mov byte ptr [esp + 0x138], 2
    uint32_t t226 = static_cast<uint32_t>(ctx.esp + 0x00000138u);
    mem.w8(t226, uint8_t{0x02u});
    // 0x0043d168: call 0x4c1f60
    uint32_t t227 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t227);
    mem.w32(t227, 0x0043d16du);
    sub_004c1f60(ctx, mem);
    // 0x0043d16d: add esp, 4
    uint32_t t228 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t228);
    ctx.esp = static_cast<uint32_t>(t228);
    // 0x0043d170: push -1
    uint32_t t229 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t229);
    mem.w32(t229, 0xffffffffu);
    // 0x0043d172: push 0
    uint32_t t230 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t230);
    mem.w32(t230, 0x00000000u);
    // 0x0043d174: push eax
    uint32_t t231 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t231);
    mem.w32(t231, ctx.eax);
    // 0x0043d175: lea ecx, [esp + 0x48]
    uint32_t t232 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    ctx.ecx = static_cast<uint32_t>(t232);
    // 0x0043d179: mov byte ptr [esp + 0x140], 3
    uint32_t t233 = static_cast<uint32_t>(ctx.esp + 0x00000140u);
    mem.w8(t233, uint8_t{0x03u});
    // 0x0043d181: call 0x4079d0
    uint32_t t234 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t234);
    mem.w32(t234, 0x0043d186u);
    sub_004079d0(ctx, mem);
    // 0x0043d186: mov edi, 0x10
    ctx.edi = static_cast<uint32_t>(0x00000010u);
    // 0x0043d18b: mov byte ptr [esp + 0x134], 2
    uint32_t t235 = static_cast<uint32_t>(ctx.esp + 0x00000134u);
    mem.w8(t235, uint8_t{0x02u});
    // 0x0043d193: cmp dword ptr [esp + 0x38], edi
    uint32_t t236 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    uint32_t t237 = mem.r32(t236);
    uint32_t t238 = static_cast<uint32_t>(t237 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t237, ctx.edi, t238);
    // 0x0043d197: jb 0x43d1a6
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043d1a6;
    goto bb_0043d199;
}
bb_0043d1a6: {
    // 0x0043d1a6: lea eax, [esp + 0x58]
    uint32_t t239 = static_cast<uint32_t>(ctx.esp + 0x00000058u);
    ctx.eax = static_cast<uint32_t>(t239);
    // 0x0043d1aa: lea edx, [esp + 0x3c]
    uint32_t t240 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    ctx.edx = static_cast<uint32_t>(t240);
    // 0x0043d1ae: call 0x42bd60
    uint32_t t241 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t241);
    mem.w32(t241, 0x0043d1b3u);
    sub_0042bd60(ctx, mem);
    // 0x0043d1b3: test al, al
    uint8_t t242 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t242);
    // 0x0043d1b5: jne 0x43d1bf
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043d1bf;
    goto bb_0043d1b7;
}
bb_0043d199: {
    // 0x0043d199: mov ecx, dword ptr [esp + 0x24]
    uint32_t t243 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t244 = mem.r32(t243);
    ctx.ecx = static_cast<uint32_t>(t244);
    // 0x0043d19d: push ecx
    uint32_t t245 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t245);
    mem.w32(t245, ctx.ecx);
    // 0x0043d19e: call 0x4e02f3
    uint32_t t246 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t246);
    mem.w32(t246, 0x0043d1a3u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043d1a3: add esp, 4
    uint32_t t247 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t247);
    ctx.esp = static_cast<uint32_t>(t247);
    goto bb_0043d1a6;
}
bb_0043d1bf: {
    // 0x0043d1bf: cmp dword ptr [esp + 0x54], edi
    uint32_t t248 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t249 = mem.r32(t248);
    uint32_t t250 = static_cast<uint32_t>(t249 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t249, ctx.edi, t250);
    // 0x0043d1c3: jb 0x43d1d2
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043d1d2;
    goto bb_0043d1c5;
}
bb_0043d1b7: {
    // 0x0043d1b7: mov dword ptr [esp + 0x18], 0
    uint32_t t251 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t251, 0x00000000u);
    goto bb_0043d1bf;
}
bb_0043d1d2: {
    // 0x0043d1d2: mov byte ptr [esp + 0x134], 0
    uint32_t t252 = static_cast<uint32_t>(ctx.esp + 0x00000134u);
    mem.w8(t252, uint8_t{0x00u});
    // 0x0043d1da: cmp dword ptr [esp + 0x70], edi
    uint32_t t253 = static_cast<uint32_t>(ctx.esp + 0x00000070u);
    uint32_t t254 = mem.r32(t253);
    uint32_t t255 = static_cast<uint32_t>(t254 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t254, ctx.edi, t255);
    // 0x0043d1de: mov dword ptr [esp + 0x54], 0xf
    uint32_t t256 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    mem.w32(t256, 0x0000000fu);
    // 0x0043d1e6: mov dword ptr [esp + 0x50], 0
    uint32_t t257 = static_cast<uint32_t>(ctx.esp + 0x00000050u);
    mem.w32(t257, 0x00000000u);
    // 0x0043d1ee: mov byte ptr [esp + 0x40], 0
    uint32_t t258 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    mem.w8(t258, uint8_t{0x00u});
    // 0x0043d1f3: jb 0x43d202
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043d202;
    goto bb_0043d1f5;
}
bb_0043d1c5: {
    // 0x0043d1c5: mov edx, dword ptr [esp + 0x40]
    uint32_t t259 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t260 = mem.r32(t259);
    ctx.edx = static_cast<uint32_t>(t260);
    // 0x0043d1c9: push edx
    uint32_t t261 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t261);
    mem.w32(t261, ctx.edx);
    // 0x0043d1ca: call 0x4e02f3
    uint32_t t262 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t262);
    mem.w32(t262, 0x0043d1cfu);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043d1cf: add esp, 4
    uint32_t t263 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t263);
    ctx.esp = static_cast<uint32_t>(t263);
    goto bb_0043d1d2;
}
bb_0043d202: {
    // 0x0043d202: cmp dword ptr [esp + 0x18], 0
    uint32_t t264 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t265 = mem.r32(t264);
    uint32_t t266 = static_cast<uint32_t>(t265 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t265, 0x00000000u, t266);
    // 0x0043d207: je 0x43d29b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d29b;
    goto bb_0043d20d;
}
bb_0043d1f5: {
    // 0x0043d1f5: mov eax, dword ptr [esp + 0x5c]
    uint32_t t267 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    uint32_t t268 = mem.r32(t267);
    ctx.eax = static_cast<uint32_t>(t268);
    // 0x0043d1f9: push eax
    uint32_t t269 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t269);
    mem.w32(t269, ctx.eax);
    // 0x0043d1fa: call 0x4e02f3
    uint32_t t270 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t270);
    mem.w32(t270, 0x0043d1ffu);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043d1ff: add esp, 4
    uint32_t t271 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t271);
    ctx.esp = static_cast<uint32_t>(t271);
    goto bb_0043d202;
}
bb_0043d20d: {
    // 0x0043d20d: cmp dword ptr [ebx + 0x18], edi
    uint32_t t272 = static_cast<uint32_t>(ctx.ebx + 0x00000018u);
    uint32_t t273 = mem.r32(t272);
    uint32_t t274 = static_cast<uint32_t>(t273 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t273, ctx.edi, t274);
    // 0x0043d210: jb 0x43d217
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043d217;
    goto bb_0043d212;
}
bb_0043d217: {
    // 0x0043d217: lea ecx, [ebx + 4]
    uint32_t t275 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    ctx.ecx = static_cast<uint32_t>(t275);
    goto bb_0043d21a;
}
bb_0043d212: {
    // 0x0043d212: mov ecx, dword ptr [ebx + 4]
    uint32_t t276 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    uint32_t t277 = mem.r32(t276);
    ctx.ecx = static_cast<uint32_t>(t277);
    // 0x0043d215: jmp 0x43d21a
}
bb_0043d21a: {
    // 0x0043d21a: call 0x446820
    uint32_t t278 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t278);
    mem.w32(t278, 0x0043d21fu);
    sub_00446820(ctx, mem);
    // 0x0043d21f: cmp eax, 1
    uint32_t t279 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t279);
    // 0x0043d222: je 0x43d239
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d239;
    goto bb_0043d224;
}
bb_0043d239: {
    // 0x0043d239: cmp dword ptr [esp + 0x18], 0
    uint32_t t280 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t281 = mem.r32(t280);
    uint32_t t282 = static_cast<uint32_t>(t281 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t281, 0x00000000u, t282);
    // 0x0043d23e: mov dword ptr [esi + 4], eax
    uint32_t t283 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t283, ctx.eax);
    // 0x0043d241: je 0x43d29b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d29b;
    goto bb_0043d243;
}
bb_0043d224: {
    // 0x0043d224: cmp eax, -3
    uint32_t t284 = static_cast<uint32_t>(ctx.eax - 0xfffffffdu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xfffffffdu, t284);
    // 0x0043d227: mov dword ptr [esp + 0x18], 0
    uint32_t t285 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t285, 0x00000000u);
    // 0x0043d22f: jne 0x43d239
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043d239;
    goto bb_0043d231;
}
bb_0043d243: {
    // 0x0043d243: cmp eax, 1
    uint32_t t286 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t286);
    // 0x0043d246: jne 0x43d28d
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043d28d;
    goto bb_0043d248;
}
bb_0043d231: {
    // 0x0043d231: mov dword ptr [esp + 0x18], 1
    uint32_t t287 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t287, 0x00000001u);
    goto bb_0043d239;
}
bb_0043d28d: {
    // 0x0043d28d: lea ebx, [esp + 0x14]
    uint32_t t288 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.ebx = static_cast<uint32_t>(t288);
    // 0x0043d291: lea esi, [ebp + 0x68]
    uint32_t t289 = static_cast<uint32_t>(ctx.ebp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t289);
    // 0x0043d294: call 0x43fe30
    uint32_t t290 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t290);
    mem.w32(t290, 0x0043d299u);
    sub_0043fe30(ctx, mem);
    // 0x0043d299: jmp 0x43d2ae
    goto bb_0043d2ae;
}
bb_0043d248: {
    // 0x0043d248: push 0x17b
    uint32_t t291 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t291);
    mem.w32(t291, 0x0000017bu);
    // 0x0043d24d: push 0x536ab8
    uint32_t t292 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t292);
    mem.w32(t292, 0x00536ab8u);
    // 0x0043d252: push 4
    uint32_t t293 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t293);
    mem.w32(t293, 0x00000004u);
    // 0x0043d254: push 0x5c
    uint32_t t294 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t294);
    mem.w32(t294, 0x0000005cu);
    // 0x0043d256: call 0x4e0675
    uint32_t t295 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t295);
    mem.w32(t295, 0x0043d25bu);
    hle_crt_004e0675(ctx, mem);
    // 0x0043d25b: add esp, 0x10
    uint32_t t296 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t296);
    ctx.esp = static_cast<uint32_t>(t296);
    // 0x0043d25e: test eax, eax
    uint32_t t297 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t297);
    // 0x0043d260: je 0x43d269
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d269;
    goto bb_0043d262;
}
bb_0043d269: {
    // 0x0043d269: xor eax, eax
    uint32_t t298 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t298);
    ctx.eax = static_cast<uint32_t>(t298);
    goto bb_0043d26b;
}
bb_0043d262: {
    // 0x0043d262: call 0x43c4b0
    uint32_t t299 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t299);
    mem.w32(t299, 0x0043d267u);
    sub_0043c4b0(ctx, mem);
    // 0x0043d267: jmp 0x43d26b
}
bb_0043d26b: {
    // 0x0043d26b: mov dword ptr [esi + 0x40], eax
    uint32_t t300 = static_cast<uint32_t>(ctx.esi + 0x00000040u);
    mem.w32(t300, ctx.eax);
    // 0x0043d26e: xor edi, edi
    uint32_t t301 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t301);
    ctx.edi = static_cast<uint32_t>(t301);
    // 0x0043d270: mov eax, ebx
    ctx.eax = static_cast<uint32_t>(ctx.ebx);
    // 0x0043d272: call 0x413890
    uint32_t t302 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t302);
    mem.w32(t302, 0x0043d277u);
    sub_00413890(ctx, mem);
    // 0x0043d277: mov ecx, dword ptr [esi + 0x40]
    uint32_t t303 = static_cast<uint32_t>(ctx.esi + 0x00000040u);
    uint32_t t304 = mem.r32(t303);
    ctx.ecx = static_cast<uint32_t>(t304);
    // 0x0043d27a: push ecx
    uint32_t t305 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t305);
    mem.w32(t305, ctx.ecx);
    // 0x0043d27b: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x0043d27d: call 0x445580
    uint32_t t306 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t306);
    mem.w32(t306, 0x0043d282u);
    sub_00445580(ctx, mem);
    // 0x0043d282: test eax, eax
    uint32_t t307 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t307);
    // 0x0043d284: jne 0x43d28d
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043d28d;
}
{
    // 0x0043d286: mov dword ptr [esi + 4], 0xffffffff
    uint32_t t308 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t308, 0xffffffffu);
    goto bb_0043d28d;
}
}

// sub_0043d3a0 | subsystem=Replay | canonical | 5 blocks | 23 insns
void sub_0043d3a0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043d3a0: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x0043d3a1: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
    // 0x0043d3a2: push edi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.edi);
    // 0x0043d3a3: mov edi, dword ptr [ebx + 0x80]
    uint32_t t3 = static_cast<uint32_t>(ctx.ebx + 0x00000080u);
    uint32_t t4 = mem.r32(t3);
    ctx.edi = static_cast<uint32_t>(t4);
    // 0x0043d3a9: test edi, edi
    uint32_t t5 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    // 0x0043d3ab: je 0x43d3d9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d3d9;
    goto bb_0043d3ad;
}
bb_0043d3d9: {
    // 0x0043d3d9: pop edi
    uint32_t t6 = ctx.esp;
    uint32_t t7 = mem.r32(t6);
    uint32_t t8 = static_cast<uint32_t>(t6 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    ctx.edi = static_cast<uint32_t>(t7);
    // 0x0043d3da: mov dword ptr [ebx + 0x80], 0
    uint32_t t9 = static_cast<uint32_t>(ctx.ebx + 0x00000080u);
    mem.w32(t9, 0x00000000u);
    // 0x0043d3e4: pop esi
    uint32_t t10 = ctx.esp;
    uint32_t t11 = mem.r32(t10);
    uint32_t t12 = static_cast<uint32_t>(t10 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    ctx.esi = static_cast<uint32_t>(t11);
    // 0x0043d3e5: pop ecx
    uint32_t t13 = ctx.esp;
    uint32_t t14 = mem.r32(t13);
    uint32_t t15 = static_cast<uint32_t>(t13 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    ctx.ecx = static_cast<uint32_t>(t14);
    // 0x0043d3e6: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043d3ad: {
    // 0x0043d3ad: push edi
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, ctx.edi);
    // 0x0043d3ae: mov esi, 0x7b0928
    ctx.esi = static_cast<uint32_t>(0x007b0928u);
    // 0x0043d3b3: call 0x4bc9e0
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x0043d3b8u);
    sub_004bc9e0(ctx, mem);
    // 0x0043d3b8: mov eax, dword ptr [edi]
    uint32_t t18 = mem.r32(ctx.edi);
    ctx.eax = static_cast<uint32_t>(t18);
    // 0x0043d3ba: test eax, eax
    uint32_t t19 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t19);
    // 0x0043d3bc: je 0x43d3c9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d3c9;
    goto bb_0043d3be;
}
bb_0043d3c9: {
    // 0x0043d3c9: push edi
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, ctx.edi);
    // 0x0043d3ca: call 0x4e00d0
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x0043d3cfu);
    hle_crt_004e00d0(ctx, mem);
    // 0x0043d3cf: add esp, 4
    uint32_t t22 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t22);
    ctx.esp = static_cast<uint32_t>(t22);
    // 0x0043d3d2: sub dword ptr [0x767440], 1
    uint32_t t23 = mem.r32(0x00767440u);
    uint32_t t24 = static_cast<uint32_t>(t23 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t23, 0x00000001u, t24);
    mem.w32(0x00767440u, t24);
    goto bb_0043d3d9;
}
bb_0043d3be: {
    // 0x0043d3be: call 0x4bcfd0
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x0043d3c3u);
    sub_004bcfd0(ctx, mem);
    // 0x0043d3c3: mov dword ptr [edi], 0
    mem.w32(ctx.edi, 0x00000000u);
    goto bb_0043d3c9;
}
}

// sub_0043d3f0 | subsystem=Replay | canonical | 50 blocks | 181 insns
void sub_0043d3f0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043d3f0: push ebx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebx);
    // 0x0043d3f1: push ebp
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebp);
    // 0x0043d3f2: push esi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.esi);
    // 0x0043d3f3: xor ebp, ebp
    uint32_t t3 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t3);
    ctx.ebp = static_cast<uint32_t>(t3);
    // 0x0043d3f5: xor esi, esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    ctx.esi = static_cast<uint32_t>(t4);
}
bb_0043d3f7: {
    // 0x0043d3f7: mov ecx, dword ptr [edi + 0x6c]
    uint32_t t5 = static_cast<uint32_t>(ctx.edi + 0x0000006cu);
    uint32_t t6 = mem.r32(t5);
    ctx.ecx = static_cast<uint32_t>(t6);
    // 0x0043d3fa: cmp ecx, ebp
    uint32_t t7 = static_cast<uint32_t>(ctx.ecx - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebp, t7);
    // 0x0043d3fc: je 0x43d43d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d43d;
    goto bb_0043d3fe;
}
bb_0043d43d: {
    // 0x0043d43d: mov ebx, dword ptr [edi + 0x70]
    uint32_t t8 = static_cast<uint32_t>(ctx.edi + 0x00000070u);
    uint32_t t9 = mem.r32(t8);
    ctx.ebx = static_cast<uint32_t>(t9);
    // 0x0043d440: cmp ecx, ebx
    uint32_t t10 = static_cast<uint32_t>(ctx.ecx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebx, t10);
    // 0x0043d442: jbe 0x43d449
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043d449;
    goto bb_0043d444;
}
bb_0043d3fe: {
    // 0x0043d3fe: mov eax, dword ptr [edi + 0x70]
    uint32_t t11 = static_cast<uint32_t>(ctx.edi + 0x00000070u);
    uint32_t t12 = mem.r32(t11);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0043d401: sub eax, ecx
    uint32_t t13 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t13);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0043d403: sar eax, 2
    uint32_t t14 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t15 = recomp_detail::sar<uint32_t>(ctx.eax, t14);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t14, t15);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x0043d406: cmp esi, eax
    uint32_t t16 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t16);
    // 0x0043d408: jae 0x43d43d
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0043d43d;
    goto bb_0043d40a;
}
bb_0043d449: {
    // 0x0043d449: mov esi, dword ptr [edi + 0x6c]
    uint32_t t17 = static_cast<uint32_t>(ctx.edi + 0x0000006cu);
    uint32_t t18 = mem.r32(t17);
    ctx.esi = static_cast<uint32_t>(t18);
    // 0x0043d44c: cmp esi, dword ptr [edi + 0x70]
    uint32_t t19 = static_cast<uint32_t>(ctx.edi + 0x00000070u);
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(ctx.esi - t20);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, t20, t21);
    // 0x0043d44f: jbe 0x43d456
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043d456;
    goto bb_0043d451;
}
bb_0043d444: {
    // 0x0043d444: call 0x4e0bf2
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x0043d449u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d449;
}
bb_0043d40a: {
    // 0x0043d40a: cmp ecx, ebp
    uint32_t t23 = static_cast<uint32_t>(ctx.ecx - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebp, t23);
    // 0x0043d40c: je 0x43d41a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d41a;
    goto bb_0043d40e;
}
bb_0043d456: {
    // 0x0043d456: cmp esi, ebx
    uint32_t t24 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t24);
    // 0x0043d458: je 0x43d481
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d481;
    goto bb_0043d45a;
}
bb_0043d451: {
    // 0x0043d451: call 0x4e0bf2
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x0043d456u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d456;
}
bb_0043d41a: {
    // 0x0043d41a: call 0x4e0bf2
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x0043d41fu);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d41f;
}
bb_0043d40e: {
    // 0x0043d40e: mov eax, dword ptr [edi + 0x70]
    uint32_t t27 = static_cast<uint32_t>(ctx.edi + 0x00000070u);
    uint32_t t28 = mem.r32(t27);
    ctx.eax = static_cast<uint32_t>(t28);
    // 0x0043d411: sub eax, ecx
    uint32_t t29 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t29);
    ctx.eax = static_cast<uint32_t>(t29);
    // 0x0043d413: sar eax, 2
    uint32_t t30 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t31 = recomp_detail::sar<uint32_t>(ctx.eax, t30);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t30, t31);
    ctx.eax = static_cast<uint32_t>(t31);
    // 0x0043d416: cmp esi, eax
    uint32_t t32 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t32);
    // 0x0043d418: jb 0x43d41f
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043d41f;
    goto bb_0043d41a;
}
bb_0043d481: {
    // 0x0043d481: mov ebx, dword ptr [edi + 0x50]
    uint32_t t33 = static_cast<uint32_t>(ctx.edi + 0x00000050u);
    uint32_t t34 = mem.r32(t33);
    ctx.ebx = static_cast<uint32_t>(t34);
    // 0x0043d484: cmp dword ptr [edi + 0x4c], ebx
    uint32_t t35 = static_cast<uint32_t>(ctx.edi + 0x0000004cu);
    uint32_t t36 = mem.r32(t35);
    uint32_t t37 = static_cast<uint32_t>(t36 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t36, ctx.ebx, t37);
    // 0x0043d487: jbe 0x43d48e
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043d48e;
    goto bb_0043d489;
}
bb_0043d45a: {
    // 0x0043d45a: mov eax, dword ptr [edi + 0x70]
    uint32_t t38 = static_cast<uint32_t>(ctx.edi + 0x00000070u);
    uint32_t t39 = mem.r32(t38);
    ctx.eax = static_cast<uint32_t>(t39);
    // 0x0043d45d: sub eax, ebx
    uint32_t t40 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t40);
    ctx.eax = static_cast<uint32_t>(t40);
    // 0x0043d45f: sar eax, 2
    uint32_t t41 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t42 = recomp_detail::sar<uint32_t>(ctx.eax, t41);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t41, t42);
    ctx.eax = static_cast<uint32_t>(t42);
    // 0x0043d462: test eax, eax
    uint32_t t43 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t43);
    // 0x0043d464: lea ecx, [eax*4]
    uint32_t t44 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000002u);
    ctx.ecx = static_cast<uint32_t>(t44);
    // 0x0043d46b: lea ebp, [ecx + esi]
    uint32_t t45 = static_cast<uint32_t>(ctx.ecx + ctx.esi);
    ctx.ebp = static_cast<uint32_t>(t45);
    // 0x0043d46e: jle 0x43d47c
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0043d47c;
    goto bb_0043d470;
}
bb_0043d41f: {
    // 0x0043d41f: mov eax, dword ptr [edi + 0x6c]
    uint32_t t46 = static_cast<uint32_t>(ctx.edi + 0x0000006cu);
    uint32_t t47 = mem.r32(t46);
    ctx.eax = static_cast<uint32_t>(t47);
    // 0x0043d422: mov ebx, dword ptr [eax + esi*4]
    uint32_t t48 = recomp_detail::shl<uint32_t>(ctx.esi, 0x00000002u);
    uint32_t t49 = static_cast<uint32_t>(ctx.eax + t48);
    uint32_t t50 = mem.r32(t49);
    ctx.ebx = static_cast<uint32_t>(t50);
    // 0x0043d425: cmp ebx, ebp
    uint32_t t51 = static_cast<uint32_t>(ctx.ebx - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.ebp, t51);
    // 0x0043d427: je 0x43d438
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d438;
    goto bb_0043d429;
}
bb_0043d48e: {
    // 0x0043d48e: mov esi, dword ptr [edi + 0x4c]
    uint32_t t52 = static_cast<uint32_t>(ctx.edi + 0x0000004cu);
    uint32_t t53 = mem.r32(t52);
    ctx.esi = static_cast<uint32_t>(t53);
    // 0x0043d491: cmp esi, dword ptr [edi + 0x50]
    uint32_t t54 = static_cast<uint32_t>(ctx.edi + 0x00000050u);
    uint32_t t55 = mem.r32(t54);
    uint32_t t56 = static_cast<uint32_t>(ctx.esi - t55);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, t55, t56);
    // 0x0043d494: jbe 0x43d49b
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043d49b;
    goto bb_0043d496;
}
bb_0043d489: {
    // 0x0043d489: call 0x4e0bf2
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, 0x0043d48eu);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d48e;
}
bb_0043d47c: {
    // 0x0043d47c: mov dword ptr [edi + 0x70], ebp
    uint32_t t58 = static_cast<uint32_t>(ctx.edi + 0x00000070u);
    mem.w32(t58, ctx.ebp);
    // 0x0043d47f: xor ebp, ebp
    uint32_t t59 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t59);
    ctx.ebp = static_cast<uint32_t>(t59);
    goto bb_0043d481;
}
bb_0043d470: {
    // 0x0043d470: push ecx
    uint32_t t60 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t60);
    mem.w32(t60, ctx.ecx);
    // 0x0043d471: push ebx
    uint32_t t61 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    mem.w32(t61, ctx.ebx);
    // 0x0043d472: push ecx
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, ctx.ecx);
    // 0x0043d473: push esi
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, ctx.esi);
    // 0x0043d474: call 0x4e0c02
    uint32_t t64 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    mem.w32(t64, 0x0043d479u);
    hle_crt_004e0c02(ctx, mem);
    // 0x0043d479: add esp, 0x10
    uint32_t t65 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t65);
    ctx.esp = static_cast<uint32_t>(t65);
    goto bb_0043d47c;
}
bb_0043d438: {
    // 0x0043d438: add esi, 1
    uint32_t t66 = static_cast<uint32_t>(ctx.esi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000001u, t66);
    ctx.esi = static_cast<uint32_t>(t66);
    // 0x0043d43b: jmp 0x43d3f7
    goto bb_0043d3f7;
}
bb_0043d429: {
    // 0x0043d429: push ebx
    uint32_t t67 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t67);
    mem.w32(t67, ctx.ebx);
    // 0x0043d42a: call 0x43c530
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, 0x0043d42fu);
    sub_0043c530(ctx, mem);
    // 0x0043d42f: push ebx
    uint32_t t69 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    mem.w32(t69, ctx.ebx);
    // 0x0043d430: call 0x4e02f3
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, 0x0043d435u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043d435: add esp, 4
    uint32_t t71 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t71);
    ctx.esp = static_cast<uint32_t>(t71);
    goto bb_0043d438;
}
bb_0043d49b: {
    // 0x0043d49b: cmp esi, ebx
    uint32_t t72 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t72);
    // 0x0043d49d: je 0x43d4c6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d4c6;
    goto bb_0043d49f;
}
bb_0043d496: {
    // 0x0043d496: call 0x4e0bf2
    uint32_t t73 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    mem.w32(t73, 0x0043d49bu);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d49b;
}
bb_0043d4c6: {
    // 0x0043d4c6: mov ebx, dword ptr [edi + 0x60]
    uint32_t t74 = static_cast<uint32_t>(ctx.edi + 0x00000060u);
    uint32_t t75 = mem.r32(t74);
    ctx.ebx = static_cast<uint32_t>(t75);
    // 0x0043d4c9: cmp dword ptr [edi + 0x5c], ebx
    uint32_t t76 = static_cast<uint32_t>(ctx.edi + 0x0000005cu);
    uint32_t t77 = mem.r32(t76);
    uint32_t t78 = static_cast<uint32_t>(t77 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t77, ctx.ebx, t78);
    // 0x0043d4cc: jbe 0x43d4d3
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043d4d3;
    goto bb_0043d4ce;
}
bb_0043d49f: {
    // 0x0043d49f: mov eax, dword ptr [edi + 0x50]
    uint32_t t79 = static_cast<uint32_t>(ctx.edi + 0x00000050u);
    uint32_t t80 = mem.r32(t79);
    ctx.eax = static_cast<uint32_t>(t80);
    // 0x0043d4a2: sub eax, ebx
    uint32_t t81 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t81);
    ctx.eax = static_cast<uint32_t>(t81);
    // 0x0043d4a4: sar eax, 2
    uint32_t t82 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t83 = recomp_detail::sar<uint32_t>(ctx.eax, t82);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t82, t83);
    ctx.eax = static_cast<uint32_t>(t83);
    // 0x0043d4a7: test eax, eax
    uint32_t t84 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t84);
    // 0x0043d4a9: lea ecx, [eax*4]
    uint32_t t85 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000002u);
    ctx.ecx = static_cast<uint32_t>(t85);
    // 0x0043d4b0: lea ebp, [ecx + esi]
    uint32_t t86 = static_cast<uint32_t>(ctx.ecx + ctx.esi);
    ctx.ebp = static_cast<uint32_t>(t86);
    // 0x0043d4b3: jle 0x43d4c1
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0043d4c1;
    goto bb_0043d4b5;
}
bb_0043d4d3: {
    // 0x0043d4d3: mov esi, dword ptr [edi + 0x5c]
    uint32_t t87 = static_cast<uint32_t>(ctx.edi + 0x0000005cu);
    uint32_t t88 = mem.r32(t87);
    ctx.esi = static_cast<uint32_t>(t88);
    // 0x0043d4d6: cmp esi, dword ptr [edi + 0x60]
    uint32_t t89 = static_cast<uint32_t>(ctx.edi + 0x00000060u);
    uint32_t t90 = mem.r32(t89);
    uint32_t t91 = static_cast<uint32_t>(ctx.esi - t90);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, t90, t91);
    // 0x0043d4d9: jbe 0x43d4e0
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043d4e0;
    goto bb_0043d4db;
}
bb_0043d4ce: {
    // 0x0043d4ce: call 0x4e0bf2
    uint32_t t92 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    mem.w32(t92, 0x0043d4d3u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d4d3;
}
bb_0043d4c1: {
    // 0x0043d4c1: mov dword ptr [edi + 0x50], ebp
    uint32_t t93 = static_cast<uint32_t>(ctx.edi + 0x00000050u);
    mem.w32(t93, ctx.ebp);
    // 0x0043d4c4: xor ebp, ebp
    uint32_t t94 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t94);
    ctx.ebp = static_cast<uint32_t>(t94);
    goto bb_0043d4c6;
}
bb_0043d4b5: {
    // 0x0043d4b5: push ecx
    uint32_t t95 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t95);
    mem.w32(t95, ctx.ecx);
    // 0x0043d4b6: push ebx
    uint32_t t96 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    mem.w32(t96, ctx.ebx);
    // 0x0043d4b7: push ecx
    uint32_t t97 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t97);
    mem.w32(t97, ctx.ecx);
    // 0x0043d4b8: push esi
    uint32_t t98 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t98);
    mem.w32(t98, ctx.esi);
    // 0x0043d4b9: call 0x4e0c02
    uint32_t t99 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t99);
    mem.w32(t99, 0x0043d4beu);
    hle_crt_004e0c02(ctx, mem);
    // 0x0043d4be: add esp, 0x10
    uint32_t t100 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t100);
    ctx.esp = static_cast<uint32_t>(t100);
    goto bb_0043d4c1;
}
bb_0043d4e0: {
    // 0x0043d4e0: cmp esi, ebx
    uint32_t t101 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t101);
    // 0x0043d4e2: je 0x43d50b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d50b;
    goto bb_0043d4e4;
}
bb_0043d4db: {
    // 0x0043d4db: call 0x4e0bf2
    uint32_t t102 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    mem.w32(t102, 0x0043d4e0u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d4e0;
}
bb_0043d50b: {
    // 0x0043d50b: mov ebx, dword ptr [edi + 0x7c]
    uint32_t t103 = static_cast<uint32_t>(ctx.edi + 0x0000007cu);
    uint32_t t104 = mem.r32(t103);
    ctx.ebx = static_cast<uint32_t>(t104);
    // 0x0043d50e: cmp ebx, ebp
    uint32_t t105 = static_cast<uint32_t>(ctx.ebx - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.ebp, t105);
    // 0x0043d510: je 0x43d567
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d567;
    goto bb_0043d512;
}
bb_0043d4e4: {
    // 0x0043d4e4: mov eax, dword ptr [edi + 0x60]
    uint32_t t106 = static_cast<uint32_t>(ctx.edi + 0x00000060u);
    uint32_t t107 = mem.r32(t106);
    ctx.eax = static_cast<uint32_t>(t107);
    // 0x0043d4e7: sub eax, ebx
    uint32_t t108 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t108);
    ctx.eax = static_cast<uint32_t>(t108);
    // 0x0043d4e9: sar eax, 2
    uint32_t t109 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t110 = recomp_detail::sar<uint32_t>(ctx.eax, t109);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t109, t110);
    ctx.eax = static_cast<uint32_t>(t110);
    // 0x0043d4ec: test eax, eax
    uint32_t t111 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t111);
    // 0x0043d4ee: lea ecx, [eax*4]
    uint32_t t112 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000002u);
    ctx.ecx = static_cast<uint32_t>(t112);
    // 0x0043d4f5: lea ebp, [ecx + esi]
    uint32_t t113 = static_cast<uint32_t>(ctx.ecx + ctx.esi);
    ctx.ebp = static_cast<uint32_t>(t113);
    // 0x0043d4f8: jle 0x43d506
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0043d506;
    goto bb_0043d4fa;
}
bb_0043d567: {
    // 0x0043d567: mov ebx, dword ptr [edi + 0x80]
    uint32_t t114 = static_cast<uint32_t>(ctx.edi + 0x00000080u);
    uint32_t t115 = mem.r32(t114);
    ctx.ebx = static_cast<uint32_t>(t115);
    // 0x0043d56d: cmp ebx, ebp
    uint32_t t116 = static_cast<uint32_t>(ctx.ebx - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.ebp, t116);
    // 0x0043d56f: mov dword ptr [edi + 0x7c], ebp
    uint32_t t117 = static_cast<uint32_t>(ctx.edi + 0x0000007cu);
    mem.w32(t117, ctx.ebp);
    // 0x0043d572: je 0x43d5c9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d5c9;
    goto bb_0043d574;
}
bb_0043d512: {
    // 0x0043d512: push ebx
    uint32_t t118 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    mem.w32(t118, ctx.ebx);
    // 0x0043d513: mov esi, 0x7b0928
    ctx.esi = static_cast<uint32_t>(0x007b0928u);
    // 0x0043d518: call 0x4bc9e0
    uint32_t t119 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t119);
    mem.w32(t119, 0x0043d51du);
    sub_004bc9e0(ctx, mem);
    // 0x0043d51d: mov esi, dword ptr [ebx]
    uint32_t t120 = mem.r32(ctx.ebx);
    ctx.esi = static_cast<uint32_t>(t120);
    // 0x0043d51f: cmp esi, ebp
    uint32_t t121 = static_cast<uint32_t>(ctx.esi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebp, t121);
    // 0x0043d521: je 0x43d557
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d557;
    goto bb_0043d523;
}
bb_0043d506: {
    // 0x0043d506: mov dword ptr [edi + 0x60], ebp
    uint32_t t122 = static_cast<uint32_t>(ctx.edi + 0x00000060u);
    mem.w32(t122, ctx.ebp);
    // 0x0043d509: xor ebp, ebp
    uint32_t t123 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t123);
    ctx.ebp = static_cast<uint32_t>(t123);
    goto bb_0043d50b;
}
bb_0043d4fa: {
    // 0x0043d4fa: push ecx
    uint32_t t124 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t124);
    mem.w32(t124, ctx.ecx);
    // 0x0043d4fb: push ebx
    uint32_t t125 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t125);
    mem.w32(t125, ctx.ebx);
    // 0x0043d4fc: push ecx
    uint32_t t126 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t126);
    mem.w32(t126, ctx.ecx);
    // 0x0043d4fd: push esi
    uint32_t t127 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t127);
    mem.w32(t127, ctx.esi);
    // 0x0043d4fe: call 0x4e0c02
    uint32_t t128 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t128);
    mem.w32(t128, 0x0043d503u);
    hle_crt_004e0c02(ctx, mem);
    // 0x0043d503: add esp, 0x10
    uint32_t t129 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t129);
    ctx.esp = static_cast<uint32_t>(t129);
    goto bb_0043d506;
}
bb_0043d5c9: {
    // 0x0043d5c9: pop esi
    uint32_t t130 = ctx.esp;
    uint32_t t131 = mem.r32(t130);
    uint32_t t132 = static_cast<uint32_t>(t130 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t132);
    ctx.esi = static_cast<uint32_t>(t131);
    // 0x0043d5ca: mov dword ptr [edi + 0x80], ebp
    uint32_t t133 = static_cast<uint32_t>(ctx.edi + 0x00000080u);
    mem.w32(t133, ctx.ebp);
    // 0x0043d5d0: pop ebp
    uint32_t t134 = ctx.esp;
    uint32_t t135 = mem.r32(t134);
    uint32_t t136 = static_cast<uint32_t>(t134 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t136);
    ctx.ebp = static_cast<uint32_t>(t135);
    // 0x0043d5d1: pop ebx
    uint32_t t137 = ctx.esp;
    uint32_t t138 = mem.r32(t137);
    uint32_t t139 = static_cast<uint32_t>(t137 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t139);
    ctx.ebx = static_cast<uint32_t>(t138);
    // 0x0043d5d2: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043d574: {
    // 0x0043d574: push ebx
    uint32_t t140 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t140);
    mem.w32(t140, ctx.ebx);
    // 0x0043d575: mov esi, 0x7b0928
    ctx.esi = static_cast<uint32_t>(0x007b0928u);
    // 0x0043d57a: call 0x4bc9e0
    uint32_t t141 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t141);
    mem.w32(t141, 0x0043d57fu);
    sub_004bc9e0(ctx, mem);
    // 0x0043d57f: mov esi, dword ptr [ebx]
    uint32_t t142 = mem.r32(ctx.ebx);
    ctx.esi = static_cast<uint32_t>(t142);
    // 0x0043d581: cmp esi, ebp
    uint32_t t143 = static_cast<uint32_t>(ctx.esi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebp, t143);
    // 0x0043d583: je 0x43d5b9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d5b9;
    goto bb_0043d585;
}
bb_0043d557: {
    // 0x0043d557: push ebx
    uint32_t t144 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t144);
    mem.w32(t144, ctx.ebx);
    // 0x0043d558: call 0x4e00d0
    uint32_t t145 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t145);
    mem.w32(t145, 0x0043d55du);
    hle_crt_004e00d0(ctx, mem);
    // 0x0043d55d: add esp, 4
    uint32_t t146 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t146);
    ctx.esp = static_cast<uint32_t>(t146);
    // 0x0043d560: sub dword ptr [0x767440], 1
    uint32_t t147 = mem.r32(0x00767440u);
    uint32_t t148 = static_cast<uint32_t>(t147 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t147, 0x00000001u, t148);
    mem.w32(0x00767440u, t148);
    goto bb_0043d567;
}
bb_0043d523: {
    // 0x0043d523: call 0x4bcc60
    uint32_t t149 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t149);
    mem.w32(t149, 0x0043d528u);
    sub_004bcc60(ctx, mem);
    // 0x0043d528: mov eax, dword ptr [esi + 0xc]
    uint32_t t150 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    uint32_t t151 = mem.r32(t150);
    ctx.eax = static_cast<uint32_t>(t151);
    // 0x0043d52b: cmp eax, ebp
    uint32_t t152 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t152);
    // 0x0043d52d: je 0x43d53a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d53a;
    goto bb_0043d52f;
}
bb_0043d5b9: {
    // 0x0043d5b9: push ebx
    uint32_t t153 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t153);
    mem.w32(t153, ctx.ebx);
    // 0x0043d5ba: call 0x4e00d0
    uint32_t t154 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t154);
    mem.w32(t154, 0x0043d5bfu);
    hle_crt_004e00d0(ctx, mem);
    // 0x0043d5bf: add esp, 4
    uint32_t t155 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t155);
    ctx.esp = static_cast<uint32_t>(t155);
    // 0x0043d5c2: sub dword ptr [0x767440], 1
    uint32_t t156 = mem.r32(0x00767440u);
    uint32_t t157 = static_cast<uint32_t>(t156 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t156, 0x00000001u, t157);
    mem.w32(0x00767440u, t157);
    goto bb_0043d5c9;
}
bb_0043d585: {
    // 0x0043d585: call 0x4bcc60
    uint32_t t158 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t158);
    mem.w32(t158, 0x0043d58au);
    sub_004bcc60(ctx, mem);
    // 0x0043d58a: mov eax, dword ptr [esi + 0xc]
    uint32_t t159 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    uint32_t t160 = mem.r32(t159);
    ctx.eax = static_cast<uint32_t>(t160);
    // 0x0043d58d: cmp eax, ebp
    uint32_t t161 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t161);
    // 0x0043d58f: je 0x43d59c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d59c;
    goto bb_0043d591;
}
bb_0043d53a: {
    // 0x0043d53a: mov eax, dword ptr [esi + 8]
    uint32_t t162 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t163 = mem.r32(t162);
    ctx.eax = static_cast<uint32_t>(t163);
    // 0x0043d53d: cmp eax, ebp
    uint32_t t164 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t164);
    // 0x0043d53f: je 0x43d54c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d54c;
    goto bb_0043d541;
}
bb_0043d52f: {
    // 0x0043d52f: mov ecx, dword ptr [eax]
    uint32_t t165 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t165);
    // 0x0043d531: mov edx, dword ptr [ecx + 8]
    uint32_t t166 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t167 = mem.r32(t166);
    ctx.edx = static_cast<uint32_t>(t167);
    // 0x0043d534: push eax
    uint32_t t168 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t168);
    mem.w32(t168, ctx.eax);
    // 0x0043d535: call edx
    uint32_t t169 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t169);
    mem.w32(t169, 0x0043d537u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0043d537: mov dword ptr [esi + 0xc], ebp
    uint32_t t170 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t170, ctx.ebp);
    goto bb_0043d53a;
}
bb_0043d59c: {
    // 0x0043d59c: mov eax, dword ptr [esi + 8]
    uint32_t t171 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t172 = mem.r32(t171);
    ctx.eax = static_cast<uint32_t>(t172);
    // 0x0043d59f: cmp eax, ebp
    uint32_t t173 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t173);
    // 0x0043d5a1: je 0x43d5ae
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d5ae;
    goto bb_0043d5a3;
}
bb_0043d591: {
    // 0x0043d591: mov ecx, dword ptr [eax]
    uint32_t t174 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t174);
    // 0x0043d593: mov edx, dword ptr [ecx + 8]
    uint32_t t175 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t176 = mem.r32(t175);
    ctx.edx = static_cast<uint32_t>(t176);
    // 0x0043d596: push eax
    uint32_t t177 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t177);
    mem.w32(t177, ctx.eax);
    // 0x0043d597: call edx
    uint32_t t178 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t178);
    mem.w32(t178, 0x0043d599u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0043d599: mov dword ptr [esi + 0xc], ebp
    uint32_t t179 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t179, ctx.ebp);
    goto bb_0043d59c;
}
bb_0043d54c: {
    // 0x0043d54c: push esi
    uint32_t t180 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t180);
    mem.w32(t180, ctx.esi);
    // 0x0043d54d: call 0x4e02f3
    uint32_t t181 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t181);
    mem.w32(t181, 0x0043d552u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043d552: add esp, 4
    uint32_t t182 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t182);
    ctx.esp = static_cast<uint32_t>(t182);
    // 0x0043d555: mov dword ptr [ebx], ebp
    mem.w32(ctx.ebx, ctx.ebp);
    goto bb_0043d557;
}
bb_0043d541: {
    // 0x0043d541: mov ecx, dword ptr [eax]
    uint32_t t183 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t183);
    // 0x0043d543: mov edx, dword ptr [ecx + 8]
    uint32_t t184 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t185 = mem.r32(t184);
    ctx.edx = static_cast<uint32_t>(t185);
    // 0x0043d546: push eax
    uint32_t t186 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t186);
    mem.w32(t186, ctx.eax);
    // 0x0043d547: call edx
    uint32_t t187 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t187);
    mem.w32(t187, 0x0043d549u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0043d549: mov dword ptr [esi + 8], ebp
    uint32_t t188 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t188, ctx.ebp);
    goto bb_0043d54c;
}
bb_0043d5ae: {
    // 0x0043d5ae: push esi
    uint32_t t189 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t189);
    mem.w32(t189, ctx.esi);
    // 0x0043d5af: call 0x4e02f3
    uint32_t t190 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t190);
    mem.w32(t190, 0x0043d5b4u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043d5b4: add esp, 4
    uint32_t t191 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t191);
    ctx.esp = static_cast<uint32_t>(t191);
    // 0x0043d5b7: mov dword ptr [ebx], ebp
    mem.w32(ctx.ebx, ctx.ebp);
    goto bb_0043d5b9;
}
bb_0043d5a3: {
    // 0x0043d5a3: mov ecx, dword ptr [eax]
    uint32_t t192 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t192);
    // 0x0043d5a5: mov edx, dword ptr [ecx + 8]
    uint32_t t193 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t194 = mem.r32(t193);
    ctx.edx = static_cast<uint32_t>(t194);
    // 0x0043d5a8: push eax
    uint32_t t195 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t195);
    mem.w32(t195, ctx.eax);
    // 0x0043d5a9: call edx
    uint32_t t196 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t196);
    mem.w32(t196, 0x0043d5abu);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0043d5ab: mov dword ptr [esi + 8], ebp
    uint32_t t197 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t197, ctx.ebp);
    goto bb_0043d5ae;
}
}

// sub_0043d5e0 | subsystem=Replay | canonical | 28 blocks | 146 insns
void sub_0043d5e0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043d5e0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0043d5e2: push 0x516d00
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00516d00u);
    // 0x0043d5e7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0043d5ed: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0043d5ee: sub esp, 0x14
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000014u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000014u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x0043d5f1: push ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebx);
    // 0x0043d5f2: push ebp
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.ebp);
    // 0x0043d5f3: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x0043d5f4: push edi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.edi);
    // 0x0043d5f5: mov eax, dword ptr [0x54b458]
    uint32_t t10 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0043d5fa: xor eax, esp
    uint32_t t11 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x0043d5fc: push eax
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.eax);
    // 0x0043d5fd: lea eax, [esp + 0x28]
    uint32_t t13 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0043d601: mov dword ptr fs:[0], eax
    uint32_t t14 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t14, ctx.eax);
    // 0x0043d607: mov edi, ecx
    ctx.edi = static_cast<uint32_t>(ctx.ecx);
    // 0x0043d609: xor ebp, ebp
    uint32_t t15 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t15);
    ctx.ebp = static_cast<uint32_t>(t15);
    // 0x0043d60b: lea esi, [edi + 0xc4]
    uint32_t t16 = static_cast<uint32_t>(ctx.edi + 0x000000c4u);
    ctx.esi = static_cast<uint32_t>(t16);
    // 0x0043d611: mov dword ptr [edi + 0xd4], ebp
    uint32_t t17 = static_cast<uint32_t>(ctx.edi + 0x000000d4u);
    mem.w32(t17, ctx.ebp);
    // 0x0043d617: mov eax, dword ptr [esi]
    uint32_t t18 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t18);
    // 0x0043d619: cmp eax, ebp
    uint32_t t19 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t19);
    // 0x0043d61b: je 0x43d627
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d627;
    goto bb_0043d61d;
}
bb_0043d627: {
    // 0x0043d627: cmp esi, ebp
    uint32_t t20 = static_cast<uint32_t>(ctx.esi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebp, t20);
    // 0x0043d629: je 0x43d63d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d63d;
    goto bb_0043d62b;
}
bb_0043d61d: {
    // 0x0043d61d: push ebp
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, ctx.ebp);
    // 0x0043d61e: push -1
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0xffffffffu);
    // 0x0043d620: push eax
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, ctx.eax);
    // 0x0043d621: call dword ptr [0x51b1c4]
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x0043d627u);
    hle_iat_call(ctx, mem, 0x0051b1c4u);
    goto bb_0043d627;
}
bb_0043d63d: {
    // 0x0043d63d: call 0x43d3f0
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x0043d642u);
    sub_0043d3f0(ctx, mem);
    // 0x0043d642: mov eax, dword ptr [edi + 0x6c]
    uint32_t t26 = static_cast<uint32_t>(ctx.edi + 0x0000006cu);
    uint32_t t27 = mem.r32(t26);
    ctx.eax = static_cast<uint32_t>(t27);
    // 0x0043d645: cmp eax, ebp
    uint32_t t28 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t28);
    // 0x0043d647: mov dword ptr [edi + 0x6c], ebp
    uint32_t t29 = static_cast<uint32_t>(ctx.edi + 0x0000006cu);
    mem.w32(t29, ctx.ebp);
    // 0x0043d64a: mov ecx, dword ptr [edi + 0x70]
    uint32_t t30 = static_cast<uint32_t>(ctx.edi + 0x00000070u);
    uint32_t t31 = mem.r32(t30);
    ctx.ecx = static_cast<uint32_t>(t31);
    // 0x0043d64d: mov dword ptr [edi + 0x70], ebp
    uint32_t t32 = static_cast<uint32_t>(ctx.edi + 0x00000070u);
    mem.w32(t32, ctx.ebp);
    // 0x0043d650: mov edx, dword ptr [edi + 0x74]
    uint32_t t33 = static_cast<uint32_t>(ctx.edi + 0x00000074u);
    uint32_t t34 = mem.r32(t33);
    ctx.edx = static_cast<uint32_t>(t34);
    // 0x0043d653: mov dword ptr [esp + 0x1c], eax
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t35, ctx.eax);
    // 0x0043d657: mov dword ptr [esp + 0x20], ecx
    uint32_t t36 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t36, ctx.ecx);
    // 0x0043d65b: mov dword ptr [esp + 0x24], edx
    uint32_t t37 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t37, ctx.edx);
    // 0x0043d65f: mov dword ptr [edi + 0x74], ebp
    uint32_t t38 = static_cast<uint32_t>(ctx.edi + 0x00000074u);
    mem.w32(t38, ctx.ebp);
    // 0x0043d662: je 0x43d66d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d66d;
    goto bb_0043d664;
}
bb_0043d62b: {
    // 0x0043d62b: mov eax, dword ptr [esi]
    uint32_t t39 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t39);
    // 0x0043d62d: cmp eax, ebp
    uint32_t t40 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t40);
    // 0x0043d62f: je 0x43d63d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d63d;
    goto bb_0043d631;
}
bb_0043d66d: {
    // 0x0043d66d: mov eax, dword ptr [edi + 0x94]
    uint32_t t41 = static_cast<uint32_t>(ctx.edi + 0x00000094u);
    uint32_t t42 = mem.r32(t41);
    ctx.eax = static_cast<uint32_t>(t42);
    // 0x0043d673: cmp eax, ebp
    uint32_t t43 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t43);
    // 0x0043d675: mov dword ptr [edi + 0x94], ebp
    uint32_t t44 = static_cast<uint32_t>(ctx.edi + 0x00000094u);
    mem.w32(t44, ctx.ebp);
    // 0x0043d67b: mov ecx, dword ptr [edi + 0x98]
    uint32_t t45 = static_cast<uint32_t>(ctx.edi + 0x00000098u);
    uint32_t t46 = mem.r32(t45);
    ctx.ecx = static_cast<uint32_t>(t46);
    // 0x0043d681: mov dword ptr [edi + 0x98], ebp
    uint32_t t47 = static_cast<uint32_t>(ctx.edi + 0x00000098u);
    mem.w32(t47, ctx.ebp);
    // 0x0043d687: mov edx, dword ptr [edi + 0x9c]
    uint32_t t48 = static_cast<uint32_t>(ctx.edi + 0x0000009cu);
    uint32_t t49 = mem.r32(t48);
    ctx.edx = static_cast<uint32_t>(t49);
    // 0x0043d68d: mov dword ptr [esp + 0x1c], eax
    uint32_t t50 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t50, ctx.eax);
    // 0x0043d691: mov dword ptr [esp + 0x20], ecx
    uint32_t t51 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t51, ctx.ecx);
    // 0x0043d695: mov dword ptr [esp + 0x24], edx
    uint32_t t52 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t52, ctx.edx);
    // 0x0043d699: mov dword ptr [edi + 0x9c], ebp
    uint32_t t53 = static_cast<uint32_t>(ctx.edi + 0x0000009cu);
    mem.w32(t53, ctx.ebp);
    // 0x0043d69f: mov dword ptr [esp + 0x30], 0xffffffff
    uint32_t t54 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    mem.w32(t54, 0xffffffffu);
    // 0x0043d6a7: je 0x43d6b2
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d6b2;
    goto bb_0043d6a9;
}
bb_0043d664: {
    // 0x0043d664: push eax
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, ctx.eax);
    // 0x0043d665: call 0x4e02f3
    uint32_t t56 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    mem.w32(t56, 0x0043d66au);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043d66a: add esp, 4
    uint32_t t57 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t57);
    ctx.esp = static_cast<uint32_t>(t57);
    goto bb_0043d66d;
}
bb_0043d631: {
    // 0x0043d631: push eax
    uint32_t t58 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    mem.w32(t58, ctx.eax);
    // 0x0043d632: call dword ptr [0x51b1cc]
    uint32_t t59 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    mem.w32(t59, 0x0043d638u);
    hle_iat_call(ctx, mem, 0x0051b1ccu);
    // 0x0043d638: mov dword ptr [esi], ebp
    mem.w32(ctx.esi, ctx.ebp);
    // 0x0043d63a: mov dword ptr [esi + 4], ebp
    uint32_t t60 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t60, ctx.ebp);
    goto bb_0043d63d;
}
bb_0043d6b2: {
    // 0x0043d6b2: mov ecx, dword ptr [edi + 0xc]
    uint32_t t61 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    uint32_t t62 = mem.r32(t61);
    ctx.ecx = static_cast<uint32_t>(t62);
    // 0x0043d6b5: cmp ecx, ebp
    uint32_t t63 = static_cast<uint32_t>(ctx.ecx - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebp, t63);
    // 0x0043d6b7: je 0x43d6c4
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d6c4;
    goto bb_0043d6b9;
}
bb_0043d6a9: {
    // 0x0043d6a9: push eax
    uint32_t t64 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    mem.w32(t64, ctx.eax);
    // 0x0043d6aa: call 0x4e02f3
    uint32_t t65 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t65);
    mem.w32(t65, 0x0043d6afu);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043d6af: add esp, 4
    uint32_t t66 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t66);
    ctx.esp = static_cast<uint32_t>(t66);
    goto bb_0043d6b2;
}
bb_0043d6c4: {
    // 0x0043d6c4: mov ebx, dword ptr [edi + 0x80]
    uint32_t t67 = static_cast<uint32_t>(ctx.edi + 0x00000080u);
    uint32_t t68 = mem.r32(t67);
    ctx.ebx = static_cast<uint32_t>(t68);
    // 0x0043d6ca: cmp ebx, ebp
    uint32_t t69 = static_cast<uint32_t>(ctx.ebx - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.ebp, t69);
    // 0x0043d6cc: je 0x43d6f6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d6f6;
    goto bb_0043d6ce;
}
bb_0043d6b9: {
    // 0x0043d6b9: mov eax, dword ptr [ecx]
    uint32_t t70 = mem.r32(ctx.ecx);
    ctx.eax = static_cast<uint32_t>(t70);
    // 0x0043d6bb: mov edx, dword ptr [eax]
    uint32_t t71 = mem.r32(ctx.eax);
    ctx.edx = static_cast<uint32_t>(t71);
    // 0x0043d6bd: push 1
    uint32_t t72 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    mem.w32(t72, 0x00000001u);
    // 0x0043d6bf: call edx
    uint32_t t73 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    mem.w32(t73, 0x0043d6c1u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0043d6c1: mov dword ptr [edi + 0xc], ebp
    uint32_t t74 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    mem.w32(t74, ctx.ebp);
    goto bb_0043d6c4;
}
bb_0043d6f6: {
    // 0x0043d6f6: mov ebx, dword ptr [edi + 0xac]
    uint32_t t75 = static_cast<uint32_t>(ctx.edi + 0x000000acu);
    uint32_t t76 = mem.r32(t75);
    ctx.ebx = static_cast<uint32_t>(t76);
    // 0x0043d6fc: cmp ebx, ebp
    uint32_t t77 = static_cast<uint32_t>(ctx.ebx - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.ebp, t77);
    // 0x0043d6fe: mov dword ptr [edi + 0x80], ebp
    uint32_t t78 = static_cast<uint32_t>(ctx.edi + 0x00000080u);
    mem.w32(t78, ctx.ebp);
    // 0x0043d704: je 0x43d72e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d72e;
    goto bb_0043d706;
}
bb_0043d6ce: {
    // 0x0043d6ce: push ebx
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, ctx.ebx);
    // 0x0043d6cf: mov esi, 0x7b0928
    ctx.esi = static_cast<uint32_t>(0x007b0928u);
    // 0x0043d6d4: call 0x4bc9e0
    uint32_t t80 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    mem.w32(t80, 0x0043d6d9u);
    sub_004bc9e0(ctx, mem);
    // 0x0043d6d9: mov eax, dword ptr [ebx]
    uint32_t t81 = mem.r32(ctx.ebx);
    ctx.eax = static_cast<uint32_t>(t81);
    // 0x0043d6db: cmp eax, ebp
    uint32_t t82 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t82);
    // 0x0043d6dd: je 0x43d6e6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d6e6;
    goto bb_0043d6df;
}
bb_0043d72e: {
    // 0x0043d72e: mov ebx, dword ptr [edi + 0xb0]
    uint32_t t83 = static_cast<uint32_t>(ctx.edi + 0x000000b0u);
    uint32_t t84 = mem.r32(t83);
    ctx.ebx = static_cast<uint32_t>(t84);
    // 0x0043d734: cmp ebx, ebp
    uint32_t t85 = static_cast<uint32_t>(ctx.ebx - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.ebp, t85);
    // 0x0043d736: mov dword ptr [edi + 0xac], ebp
    uint32_t t86 = static_cast<uint32_t>(ctx.edi + 0x000000acu);
    mem.w32(t86, ctx.ebp);
    // 0x0043d73c: je 0x43d766
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d766;
    goto bb_0043d73e;
}
bb_0043d706: {
    // 0x0043d706: push ebx
    uint32_t t87 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t87);
    mem.w32(t87, ctx.ebx);
    // 0x0043d707: mov esi, 0x7b0928
    ctx.esi = static_cast<uint32_t>(0x007b0928u);
    // 0x0043d70c: call 0x4bc9e0
    uint32_t t88 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t88);
    mem.w32(t88, 0x0043d711u);
    sub_004bc9e0(ctx, mem);
    // 0x0043d711: mov eax, dword ptr [ebx]
    uint32_t t89 = mem.r32(ctx.ebx);
    ctx.eax = static_cast<uint32_t>(t89);
    // 0x0043d713: cmp eax, ebp
    uint32_t t90 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t90);
    // 0x0043d715: je 0x43d71e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d71e;
    goto bb_0043d717;
}
bb_0043d6e6: {
    // 0x0043d6e6: push ebx
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, ctx.ebx);
    // 0x0043d6e7: call 0x4e00d0
    uint32_t t92 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    mem.w32(t92, 0x0043d6ecu);
    hle_crt_004e00d0(ctx, mem);
    // 0x0043d6ec: add esp, 4
    uint32_t t93 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t93);
    ctx.esp = static_cast<uint32_t>(t93);
    // 0x0043d6ef: sub dword ptr [0x767440], 1
    uint32_t t94 = mem.r32(0x00767440u);
    uint32_t t95 = static_cast<uint32_t>(t94 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t94, 0x00000001u, t95);
    mem.w32(0x00767440u, t95);
    goto bb_0043d6f6;
}
bb_0043d6df: {
    // 0x0043d6df: call 0x4bcfd0
    uint32_t t96 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    mem.w32(t96, 0x0043d6e4u);
    sub_004bcfd0(ctx, mem);
    // 0x0043d6e4: mov dword ptr [ebx], ebp
    mem.w32(ctx.ebx, ctx.ebp);
    goto bb_0043d6e6;
}
bb_0043d766: {
    // 0x0043d766: lea esi, [edi + 0xb4]
    uint32_t t97 = static_cast<uint32_t>(ctx.edi + 0x000000b4u);
    ctx.esi = static_cast<uint32_t>(t97);
    // 0x0043d76c: mov dword ptr [edi + 0xb0], ebp
    uint32_t t98 = static_cast<uint32_t>(ctx.edi + 0x000000b0u);
    mem.w32(t98, ctx.ebp);
    // 0x0043d772: mov edi, dword ptr [esi + 8]
    uint32_t t99 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t100 = mem.r32(t99);
    ctx.edi = static_cast<uint32_t>(t100);
    // 0x0043d775: cmp dword ptr [esi + 4], edi
    uint32_t t101 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t102 = mem.r32(t101);
    uint32_t t103 = static_cast<uint32_t>(t102 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t102, ctx.edi, t103);
    // 0x0043d778: jbe 0x43d77f
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043d77f;
    goto bb_0043d77a;
}
bb_0043d73e: {
    // 0x0043d73e: push ebx
    uint32_t t104 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t104);
    mem.w32(t104, ctx.ebx);
    // 0x0043d73f: mov esi, 0x7b0928
    ctx.esi = static_cast<uint32_t>(0x007b0928u);
    // 0x0043d744: call 0x4bc9e0
    uint32_t t105 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t105);
    mem.w32(t105, 0x0043d749u);
    sub_004bc9e0(ctx, mem);
    // 0x0043d749: mov eax, dword ptr [ebx]
    uint32_t t106 = mem.r32(ctx.ebx);
    ctx.eax = static_cast<uint32_t>(t106);
    // 0x0043d74b: cmp eax, ebp
    uint32_t t107 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t107);
    // 0x0043d74d: je 0x43d756
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d756;
    goto bb_0043d74f;
}
bb_0043d71e: {
    // 0x0043d71e: push ebx
    uint32_t t108 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t108);
    mem.w32(t108, ctx.ebx);
    // 0x0043d71f: call 0x4e00d0
    uint32_t t109 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t109);
    mem.w32(t109, 0x0043d724u);
    hle_crt_004e00d0(ctx, mem);
    // 0x0043d724: add esp, 4
    uint32_t t110 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t110);
    ctx.esp = static_cast<uint32_t>(t110);
    // 0x0043d727: sub dword ptr [0x767440], 1
    uint32_t t111 = mem.r32(0x00767440u);
    uint32_t t112 = static_cast<uint32_t>(t111 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t111, 0x00000001u, t112);
    mem.w32(0x00767440u, t112);
    goto bb_0043d72e;
}
bb_0043d717: {
    // 0x0043d717: call 0x4bcfd0
    uint32_t t113 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t113);
    mem.w32(t113, 0x0043d71cu);
    sub_004bcfd0(ctx, mem);
    // 0x0043d71c: mov dword ptr [ebx], ebp
    mem.w32(ctx.ebx, ctx.ebp);
    goto bb_0043d71e;
}
bb_0043d77f: {
    // 0x0043d77f: mov ebx, dword ptr [esi + 4]
    uint32_t t114 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t115 = mem.r32(t114);
    ctx.ebx = static_cast<uint32_t>(t115);
    // 0x0043d782: cmp ebx, dword ptr [esi + 8]
    uint32_t t116 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t117 = mem.r32(t116);
    uint32_t t118 = static_cast<uint32_t>(ctx.ebx - t117);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, t117, t118);
    // 0x0043d785: jbe 0x43d78c
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043d78c;
    goto bb_0043d787;
}
bb_0043d77a: {
    // 0x0043d77a: call 0x4e0bf2
    uint32_t t119 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t119);
    mem.w32(t119, 0x0043d77fu);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d77f;
}
bb_0043d756: {
    // 0x0043d756: push ebx
    uint32_t t120 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t120);
    mem.w32(t120, ctx.ebx);
    // 0x0043d757: call 0x4e00d0
    uint32_t t121 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t121);
    mem.w32(t121, 0x0043d75cu);
    hle_crt_004e00d0(ctx, mem);
    // 0x0043d75c: add esp, 4
    uint32_t t122 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t122);
    ctx.esp = static_cast<uint32_t>(t122);
    // 0x0043d75f: sub dword ptr [0x767440], 1
    uint32_t t123 = mem.r32(0x00767440u);
    uint32_t t124 = static_cast<uint32_t>(t123 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t123, 0x00000001u, t124);
    mem.w32(0x00767440u, t124);
    goto bb_0043d766;
}
bb_0043d74f: {
    // 0x0043d74f: call 0x4bcfd0
    uint32_t t125 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t125);
    mem.w32(t125, 0x0043d754u);
    sub_004bcfd0(ctx, mem);
    // 0x0043d754: mov dword ptr [ebx], ebp
    mem.w32(ctx.ebx, ctx.ebp);
    goto bb_0043d756;
}
bb_0043d78c: {
    // 0x0043d78c: push edi
    uint32_t t126 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t126);
    mem.w32(t126, ctx.edi);
    // 0x0043d78d: push esi
    uint32_t t127 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t127);
    mem.w32(t127, ctx.esi);
    // 0x0043d78e: push ebx
    uint32_t t128 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t128);
    mem.w32(t128, ctx.ebx);
    // 0x0043d78f: push esi
    uint32_t t129 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t129);
    mem.w32(t129, ctx.esi);
    // 0x0043d790: lea eax, [esp + 0x28]
    uint32_t t130 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.eax = static_cast<uint32_t>(t130);
    // 0x0043d794: push eax
    uint32_t t131 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t131);
    mem.w32(t131, ctx.eax);
    // 0x0043d795: push esi
    uint32_t t132 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t132);
    mem.w32(t132, ctx.esi);
    // 0x0043d796: call 0x440290
    uint32_t t133 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t133);
    mem.w32(t133, 0x0043d79bu);
    sub_00440290(ctx, mem);
    // 0x0043d79b: mov ecx, dword ptr [esp + 0x28]
    uint32_t t134 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t135 = mem.r32(t134);
    ctx.ecx = static_cast<uint32_t>(t135);
    // 0x0043d79f: mov dword ptr fs:[0], ecx
    uint32_t t136 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t136, ctx.ecx);
    // 0x0043d7a6: pop ecx
    uint32_t t137 = ctx.esp;
    uint32_t t138 = mem.r32(t137);
    uint32_t t139 = static_cast<uint32_t>(t137 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t139);
    ctx.ecx = static_cast<uint32_t>(t138);
    // 0x0043d7a7: pop edi
    uint32_t t140 = ctx.esp;
    uint32_t t141 = mem.r32(t140);
    uint32_t t142 = static_cast<uint32_t>(t140 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t142);
    ctx.edi = static_cast<uint32_t>(t141);
    // 0x0043d7a8: pop esi
    uint32_t t143 = ctx.esp;
    uint32_t t144 = mem.r32(t143);
    uint32_t t145 = static_cast<uint32_t>(t143 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t145);
    ctx.esi = static_cast<uint32_t>(t144);
    // 0x0043d7a9: pop ebp
    uint32_t t146 = ctx.esp;
    uint32_t t147 = mem.r32(t146);
    uint32_t t148 = static_cast<uint32_t>(t146 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t148);
    ctx.ebp = static_cast<uint32_t>(t147);
    // 0x0043d7aa: pop ebx
    uint32_t t149 = ctx.esp;
    uint32_t t150 = mem.r32(t149);
    uint32_t t151 = static_cast<uint32_t>(t149 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t151);
    ctx.ebx = static_cast<uint32_t>(t150);
    // 0x0043d7ab: add esp, 0x20
    uint32_t t152 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000020u, t152);
    ctx.esp = static_cast<uint32_t>(t152);
    // 0x0043d7ae: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043d787: {
    // 0x0043d787: call 0x4e0bf2
    uint32_t t153 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t153);
    mem.w32(t153, 0x0043d78cu);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d78c;
}
}

// sub_0043d7b0 | subsystem=Replay | canonical | 16 blocks | 36 insns
void sub_0043d7b0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043d7b0: mov eax, dword ptr [edi + 0x14]
    uint32_t t0 = static_cast<uint32_t>(ctx.edi + 0x00000014u);
    uint32_t t1 = mem.r32(t0);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x0043d7b3: push esi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.esi);
    // 0x0043d7b4: xor esi, esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t3);
    ctx.esi = static_cast<uint32_t>(t3);
    // 0x0043d7b6: test eax, eax
    uint32_t t4 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    // 0x0043d7b8: jbe 0x43d801
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043d801;
    goto bb_0043d7ba;
}
bb_0043d801: {
    // 0x0043d801: pop esi
    uint32_t t5 = ctx.esp;
    uint32_t t6 = mem.r32(t5);
    uint32_t t7 = static_cast<uint32_t>(t5 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x0043d802: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043d7ba: {
    // 0x0043d7ba: cmp esi, eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t8);
    // 0x0043d7bc: push ebx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ebx);
    // 0x0043d7bd: push ebp
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.ebp);
    // 0x0043d7be: lea ebx, [edi + 4]
    uint32_t t11 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    ctx.ebx = static_cast<uint32_t>(t11);
    // 0x0043d7c1: lea ebp, [esi + 0x10]
    uint32_t t12 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    ctx.ebp = static_cast<uint32_t>(t12);
    // 0x0043d7c4: jbe 0x43d7cb
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043d7cb;
    goto bb_0043d7c6;
}
bb_0043d7cb: {
    // 0x0043d7cb: cmp dword ptr [edi + 0x18], ebp
    uint32_t t13 = static_cast<uint32_t>(ctx.edi + 0x00000018u);
    uint32_t t14 = mem.r32(t13);
    uint32_t t15 = static_cast<uint32_t>(t14 - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t14, ctx.ebp, t15);
    // 0x0043d7ce: jb 0x43d7d4
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043d7d4;
    goto bb_0043d7d0;
}
bb_0043d7c6: {
    // 0x0043d7c6: call 0x4e0bf2
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x0043d7cbu);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d7cb;
}
bb_0043d7d4: {
    // 0x0043d7d4: mov eax, ebx
    ctx.eax = static_cast<uint32_t>(ctx.ebx);
    goto bb_0043d7d6;
}
bb_0043d7d0: {
    // 0x0043d7d0: mov eax, dword ptr [ebx]
    uint32_t t17 = mem.r32(ctx.ebx);
    ctx.eax = static_cast<uint32_t>(t17);
    // 0x0043d7d2: jmp 0x43d7d6
}
bb_0043d7d6: {
    // 0x0043d7d6: cmp byte ptr [eax + esi], 0x5c
    uint32_t t18 = static_cast<uint32_t>(ctx.eax + ctx.esi);
    uint8_t t19 = mem.r8(t18);
    uint8_t t20 = static_cast<uint8_t>(static_cast<uint32_t>(t19) - static_cast<uint32_t>(uint8_t{0x5cu}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, t19, uint8_t{0x5cu}, t20);
    // 0x0043d7da: jne 0x43d7f5
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043d7f5;
    goto bb_0043d7dc;
}
bb_0043d7f5: {
    // 0x0043d7f5: mov eax, dword ptr [edi + 0x14]
    uint32_t t21 = static_cast<uint32_t>(ctx.edi + 0x00000014u);
    uint32_t t22 = mem.r32(t21);
    ctx.eax = static_cast<uint32_t>(t22);
    // 0x0043d7f8: add esi, 1
    uint32_t t23 = static_cast<uint32_t>(ctx.esi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000001u, t23);
    ctx.esi = static_cast<uint32_t>(t23);
    // 0x0043d7fb: cmp esi, eax
    uint32_t t24 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t24);
    // 0x0043d7fd: jb 0x43d7cb
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043d7cb;
    goto bb_0043d7ff;
}
bb_0043d7dc: {
    // 0x0043d7dc: cmp esi, dword ptr [edi + 0x14]
    uint32_t t25 = static_cast<uint32_t>(ctx.edi + 0x00000014u);
    uint32_t t26 = mem.r32(t25);
    uint32_t t27 = static_cast<uint32_t>(ctx.esi - t26);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, t26, t27);
    // 0x0043d7df: jbe 0x43d7e6
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043d7e6;
    goto bb_0043d7e1;
}
bb_0043d7ff: {
    // 0x0043d7ff: pop ebp
    uint32_t t28 = ctx.esp;
    uint32_t t29 = mem.r32(t28);
    uint32_t t30 = static_cast<uint32_t>(t28 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    ctx.ebp = static_cast<uint32_t>(t29);
    // 0x0043d800: pop ebx
    uint32_t t31 = ctx.esp;
    uint32_t t32 = mem.r32(t31);
    uint32_t t33 = static_cast<uint32_t>(t31 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    ctx.ebx = static_cast<uint32_t>(t32);
    goto bb_0043d801;
}
bb_0043d7e6: {
    // 0x0043d7e6: cmp dword ptr [edi + 0x18], ebp
    uint32_t t34 = static_cast<uint32_t>(ctx.edi + 0x00000018u);
    uint32_t t35 = mem.r32(t34);
    uint32_t t36 = static_cast<uint32_t>(t35 - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t35, ctx.ebp, t36);
    // 0x0043d7e9: jb 0x43d7ef
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043d7ef;
    goto bb_0043d7eb;
}
bb_0043d7e1: {
    // 0x0043d7e1: call 0x4e0bf2
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, 0x0043d7e6u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d7e6;
}
bb_0043d7ef: {
    // 0x0043d7ef: mov eax, ebx
    ctx.eax = static_cast<uint32_t>(ctx.ebx);
    goto bb_0043d7f1;
}
bb_0043d7eb: {
    // 0x0043d7eb: mov eax, dword ptr [ebx]
    uint32_t t38 = mem.r32(ctx.ebx);
    ctx.eax = static_cast<uint32_t>(t38);
    // 0x0043d7ed: jmp 0x43d7f1
}
bb_0043d7f1: {
    // 0x0043d7f1: mov byte ptr [eax + esi], 0x2f
    uint32_t t39 = static_cast<uint32_t>(ctx.eax + ctx.esi);
    mem.w8(t39, uint8_t{0x2fu});
    goto bb_0043d7f5;
}
}

// sub_0043d810 | subsystem=Replay | canonical | 63 blocks | 229 insns
void sub_0043d810(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043d810: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0043d812: push 0x516cbb
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00516cbbu);
    // 0x0043d817: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0043d81d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0043d81e: sub esp, 0x1c8
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x000001c8u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x000001c8u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x0043d824: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0043d829: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0043d82b: mov dword ptr [esp + 0x1c0], eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w32(t8, ctx.eax);
    // 0x0043d832: push ebx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ebx);
    // 0x0043d833: push ebp
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.ebp);
    // 0x0043d834: push esi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.esi);
    // 0x0043d835: push edi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.edi);
    // 0x0043d836: mov eax, dword ptr [0x54b458]
    uint32_t t13 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0043d83b: xor eax, esp
    uint32_t t14 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x0043d83d: push eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.eax);
    // 0x0043d83e: lea eax, [esp + 0x1dc]
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x000001dcu);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0043d845: mov dword ptr fs:[0], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t17, ctx.eax);
    // 0x0043d84b: mov ebp, dword ptr [esp + 0x1ec]
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x000001ecu);
    uint32_t t19 = mem.r32(t18);
    ctx.ebp = static_cast<uint32_t>(t19);
    // 0x0043d852: mov dword ptr [ebp + 4], 2
    uint32_t t20 = static_cast<uint32_t>(ctx.ebp + 0x00000004u);
    mem.w32(t20, 0x00000002u);
    // 0x0043d859: mov eax, dword ptr [ebp + 0x6c]
    uint32_t t21 = static_cast<uint32_t>(ctx.ebp + 0x0000006cu);
    uint32_t t22 = mem.r32(t21);
    ctx.eax = static_cast<uint32_t>(t22);
    // 0x0043d85c: test eax, eax
    uint32_t t23 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t23);
    // 0x0043d85e: jne 0x43d864
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043d864;
    goto bb_0043d860;
}
bb_0043d864: {
    // 0x0043d864: mov edi, dword ptr [ebp + 0x70]
    uint32_t t24 = static_cast<uint32_t>(ctx.ebp + 0x00000070u);
    uint32_t t25 = mem.r32(t24);
    ctx.edi = static_cast<uint32_t>(t25);
    // 0x0043d867: sub edi, eax
    uint32_t t26 = static_cast<uint32_t>(ctx.edi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.eax, t26);
    ctx.edi = static_cast<uint32_t>(t26);
    // 0x0043d869: sar edi, 2
    uint32_t t27 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t28 = recomp_detail::sar<uint32_t>(ctx.edi, t27);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edi, t27, t28);
    ctx.edi = static_cast<uint32_t>(t28);
    goto bb_0043d86c;
}
bb_0043d860: {
    // 0x0043d860: xor edi, edi
    uint32_t t29 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t29);
    ctx.edi = static_cast<uint32_t>(t29);
    // 0x0043d862: jmp 0x43d86c
}
bb_0043d86c: {
    // 0x0043d86c: mov ecx, dword ptr [ebp + 0x94]
    uint32_t t30 = static_cast<uint32_t>(ctx.ebp + 0x00000094u);
    uint32_t t31 = mem.r32(t30);
    ctx.ecx = static_cast<uint32_t>(t31);
    // 0x0043d872: test ecx, ecx
    uint32_t t32 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t32);
    // 0x0043d874: mov esi, dword ptr [ebp + 0x8c]
    uint32_t t33 = static_cast<uint32_t>(ctx.ebp + 0x0000008cu);
    uint32_t t34 = mem.r32(t33);
    ctx.esi = static_cast<uint32_t>(t34);
    // 0x0043d87a: je 0x43d88b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d88b;
    goto bb_0043d87c;
}
bb_0043d88b: {
    // 0x0043d88b: call 0x4e0bf2
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, 0x0043d890u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d890;
}
bb_0043d87c: {
    // 0x0043d87c: mov eax, dword ptr [ebp + 0x98]
    uint32_t t36 = static_cast<uint32_t>(ctx.ebp + 0x00000098u);
    uint32_t t37 = mem.r32(t36);
    ctx.eax = static_cast<uint32_t>(t37);
    // 0x0043d882: sub eax, ecx
    uint32_t t38 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t38);
    ctx.eax = static_cast<uint32_t>(t38);
    // 0x0043d884: sar eax, 2
    uint32_t t39 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t40 = recomp_detail::sar<uint32_t>(ctx.eax, t39);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t39, t40);
    ctx.eax = static_cast<uint32_t>(t40);
    // 0x0043d887: cmp esi, eax
    uint32_t t41 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t41);
    // 0x0043d889: jb 0x43d890
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043d890;
    goto bb_0043d88b;
}
bb_0043d890: {
    // 0x0043d890: test edi, edi
    uint32_t t42 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t42);
    // 0x0043d892: mov eax, dword ptr [ebp + 0x94]
    uint32_t t43 = static_cast<uint32_t>(ctx.ebp + 0x00000094u);
    uint32_t t44 = mem.r32(t43);
    ctx.eax = static_cast<uint32_t>(t44);
    // 0x0043d898: mov esi, dword ptr [eax + esi*4]
    uint32_t t45 = recomp_detail::shl<uint32_t>(ctx.esi, 0x00000002u);
    uint32_t t46 = static_cast<uint32_t>(ctx.eax + t45);
    uint32_t t47 = mem.r32(t46);
    ctx.esi = static_cast<uint32_t>(t47);
    // 0x0043d89b: je 0x43d990
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d990;
    goto bb_0043d8a1;
}
bb_0043d990: {
    // 0x0043d990: mov eax, dword ptr [ebp + 0xa4]
    uint32_t t48 = static_cast<uint32_t>(ctx.ebp + 0x000000a4u);
    uint32_t t49 = mem.r32(t48);
    ctx.eax = static_cast<uint32_t>(t49);
    // 0x0043d996: sub eax, 1
    uint32_t t50 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t50);
    ctx.eax = static_cast<uint32_t>(t50);
    // 0x0043d999: je 0x43d9b0
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d9b0;
    goto bb_0043d99b;
}
bb_0043d8a1: {
    // 0x0043d8a1: mov eax, dword ptr [ebp + 0xa0]
    uint32_t t51 = static_cast<uint32_t>(ctx.ebp + 0x000000a0u);
    uint32_t t52 = mem.r32(t51);
    ctx.eax = static_cast<uint32_t>(t52);
    // 0x0043d8a7: cmp eax, 2
    uint32_t t53 = static_cast<uint32_t>(ctx.eax - 0x00000002u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000002u, t53);
    // 0x0043d8aa: jne 0x43d8af
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043d8af;
    goto bb_0043d8ac;
}
bb_0043d9b0: {
    // 0x0043d9b0: xor ebx, ebx
    uint32_t t54 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t54);
    ctx.ebx = static_cast<uint32_t>(t54);
    // 0x0043d9b2: cmp edi, ebx
    uint32_t t55 = static_cast<uint32_t>(ctx.edi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebx, t55);
    // 0x0043d9b4: je 0x43db49
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043db49;
    goto bb_0043d9ba;
}
bb_0043d99b: {
    // 0x0043d99b: sub eax, 1
    uint32_t t56 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t56);
    ctx.eax = static_cast<uint32_t>(t56);
    // 0x0043d99e: jne 0x43db49
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043db49;
    goto bb_0043d9a4;
}
bb_0043d8af: {
    // 0x0043d8af: cmp eax, 8
    uint32_t t57 = static_cast<uint32_t>(ctx.eax - 0x00000008u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000008u, t57);
    // 0x0043d8b2: jne 0x43d8b7
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043d8b7;
    goto bb_0043d8b4;
}
bb_0043d8ac: {
    // 0x0043d8ac: add esi, 1
    uint32_t t58 = static_cast<uint32_t>(ctx.esi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000001u, t58);
    ctx.esi = static_cast<uint32_t>(t58);
    goto bb_0043d8af;
}
bb_0043db49: {
    // 0x0043db49: mov ecx, dword ptr [esp + 0x1dc]
    uint32_t t59 = static_cast<uint32_t>(ctx.esp + 0x000001dcu);
    uint32_t t60 = mem.r32(t59);
    ctx.ecx = static_cast<uint32_t>(t60);
    // 0x0043db50: mov dword ptr fs:[0], ecx
    uint32_t t61 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t61, ctx.ecx);
    // 0x0043db57: pop ecx
    uint32_t t62 = ctx.esp;
    uint32_t t63 = mem.r32(t62);
    uint32_t t64 = static_cast<uint32_t>(t62 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    ctx.ecx = static_cast<uint32_t>(t63);
    // 0x0043db58: pop edi
    uint32_t t65 = ctx.esp;
    uint32_t t66 = mem.r32(t65);
    uint32_t t67 = static_cast<uint32_t>(t65 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t67);
    ctx.edi = static_cast<uint32_t>(t66);
    // 0x0043db59: pop esi
    uint32_t t68 = ctx.esp;
    uint32_t t69 = mem.r32(t68);
    uint32_t t70 = static_cast<uint32_t>(t68 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    ctx.esi = static_cast<uint32_t>(t69);
    // 0x0043db5a: pop ebp
    uint32_t t71 = ctx.esp;
    uint32_t t72 = mem.r32(t71);
    uint32_t t73 = static_cast<uint32_t>(t71 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    ctx.ebp = static_cast<uint32_t>(t72);
    // 0x0043db5b: pop ebx
    uint32_t t74 = ctx.esp;
    uint32_t t75 = mem.r32(t74);
    uint32_t t76 = static_cast<uint32_t>(t74 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    ctx.ebx = static_cast<uint32_t>(t75);
    // 0x0043db5c: mov ecx, dword ptr [esp + 0x1c0]
    uint32_t t77 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    uint32_t t78 = mem.r32(t77);
    ctx.ecx = static_cast<uint32_t>(t78);
    // 0x0043db63: xor ecx, esp
    uint32_t t79 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t79);
    ctx.ecx = static_cast<uint32_t>(t79);
    // 0x0043db65: call 0x4e02f8
    uint32_t t80 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    mem.w32(t80, 0x0043db6au);
    hle_crt_004e02f8(ctx, mem);
    // 0x0043db6a: add esp, 0x1d4
    uint32_t t81 = static_cast<uint32_t>(ctx.esp + 0x000001d4u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x000001d4u, t81);
    ctx.esp = static_cast<uint32_t>(t81);
    // 0x0043db70: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0043d9ba: {
    // 0x0043d9ba: mov ecx, dword ptr [ebp + 0x6c]
    uint32_t t82 = static_cast<uint32_t>(ctx.ebp + 0x0000006cu);
    uint32_t t83 = mem.r32(t82);
    ctx.ecx = static_cast<uint32_t>(t83);
    // 0x0043d9bd: cmp ecx, ebx
    uint32_t t84 = static_cast<uint32_t>(ctx.ecx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebx, t84);
    // 0x0043d9bf: je 0x43d9cd
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d9cd;
    goto bb_0043d9c1;
}
bb_0043d9a4: {
    // 0x0043d9a4: mov dword ptr [ebp + 4], 4
    uint32_t t85 = static_cast<uint32_t>(ctx.ebp + 0x00000004u);
    mem.w32(t85, 0x00000004u);
    // 0x0043d9ab: jmp 0x43db49
    goto bb_0043db49;
}
bb_0043d8b7: {
    // 0x0043d8b7: cmp eax, 4
    uint32_t t86 = static_cast<uint32_t>(ctx.eax - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000004u, t86);
    // 0x0043d8ba: jne 0x43d8bf
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043d8bf;
    goto bb_0043d8bc;
}
bb_0043d8b4: {
    // 0x0043d8b4: sub esi, 1
    uint32_t t87 = static_cast<uint32_t>(ctx.esi - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00000001u, t87);
    ctx.esi = static_cast<uint32_t>(t87);
    goto bb_0043d8b7;
}
bb_0043d9cd: {
    // 0x0043d9cd: call 0x4e0bf2
    uint32_t t88 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t88);
    mem.w32(t88, 0x0043d9d2u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d9d2;
}
bb_0043d9c1: {
    // 0x0043d9c1: mov eax, dword ptr [ebp + 0x70]
    uint32_t t89 = static_cast<uint32_t>(ctx.ebp + 0x00000070u);
    uint32_t t90 = mem.r32(t89);
    ctx.eax = static_cast<uint32_t>(t90);
    // 0x0043d9c4: sub eax, ecx
    uint32_t t91 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t91);
    ctx.eax = static_cast<uint32_t>(t91);
    // 0x0043d9c6: sar eax, 2
    uint32_t t92 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t93 = recomp_detail::sar<uint32_t>(ctx.eax, t92);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t92, t93);
    ctx.eax = static_cast<uint32_t>(t93);
    // 0x0043d9c9: cmp esi, eax
    uint32_t t94 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t94);
    // 0x0043d9cb: jb 0x43d9d2
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043d9d2;
    goto bb_0043d9cd;
}
bb_0043d8bf: {
    // 0x0043d8bf: cmp eax, 6
    uint32_t t95 = static_cast<uint32_t>(ctx.eax - 0x00000006u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000006u, t95);
    // 0x0043d8c2: jne 0x43d8c7
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043d8c7;
    goto bb_0043d8c4;
}
bb_0043d8bc: {
    // 0x0043d8bc: sub esi, 0xc
    uint32_t t96 = static_cast<uint32_t>(ctx.esi - 0x0000000cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x0000000cu, t96);
    ctx.esi = static_cast<uint32_t>(t96);
    goto bb_0043d8bf;
}
bb_0043d9d2: {
    // 0x0043d9d2: mov edx, dword ptr [ebp + 0x6c]
    uint32_t t97 = static_cast<uint32_t>(ctx.ebp + 0x0000006cu);
    uint32_t t98 = mem.r32(t97);
    ctx.edx = static_cast<uint32_t>(t98);
    // 0x0043d9d5: mov esi, dword ptr [edx + esi*4]
    uint32_t t99 = recomp_detail::shl<uint32_t>(ctx.esi, 0x00000002u);
    uint32_t t100 = static_cast<uint32_t>(ctx.edx + t99);
    uint32_t t101 = mem.r32(t100);
    ctx.esi = static_cast<uint32_t>(t101);
    // 0x0043d9d8: cmp dword ptr [esi + 4], -3
    uint32_t t102 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t103 = mem.r32(t102);
    uint32_t t104 = static_cast<uint32_t>(t103 - 0xfffffffdu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t103, 0xfffffffdu, t104);
    // 0x0043d9dc: je 0x43db49
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043db49;
    goto bb_0043d9e2;
}
bb_0043d8c7: {
    // 0x0043d8c7: test esi, esi
    uint32_t t105 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t105);
    // 0x0043d8c9: jge 0x43d8cd
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0043d8cd;
    goto bb_0043d8cb;
}
bb_0043d8c4: {
    // 0x0043d8c4: add esi, 0xc
    uint32_t t106 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x0000000cu, t106);
    ctx.esi = static_cast<uint32_t>(t106);
    goto bb_0043d8c7;
}
bb_0043d9e2: {
    // 0x0043d9e2: cmp dword ptr [esi], ebx
    uint32_t t107 = mem.r32(ctx.esi);
    uint32_t t108 = static_cast<uint32_t>(t107 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t107, ctx.ebx, t108);
    // 0x0043d9e4: je 0x43daf1
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043daf1;
    goto bb_0043d9ea;
}
bb_0043d8cd: {
    // 0x0043d8cd: cmp esi, edi
    uint32_t t109 = static_cast<uint32_t>(ctx.esi - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edi, t109);
    // 0x0043d8cf: jl 0x43d8d4
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0043d8d4;
    goto bb_0043d8d1;
}
bb_0043d8cb: {
    // 0x0043d8cb: xor esi, esi
    uint32_t t110 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t110);
    ctx.esi = static_cast<uint32_t>(t110);
    goto bb_0043d8cd;
}
bb_0043daf1: {
    // 0x0043daf1: lea ecx, [esp + 0x1c]
    uint32_t t111 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.ecx = static_cast<uint32_t>(t111);
    // 0x0043daf5: push ecx
    uint32_t t112 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t112);
    mem.w32(t112, ctx.ecx);
    // 0x0043daf6: call 0x445f30
    uint32_t t113 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t113);
    mem.w32(t113, 0x0043dafbu);
    sub_00445f30(ctx, mem);
    // 0x0043dafb: lea eax, [esi + 0x24]
    uint32_t t114 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    ctx.eax = static_cast<uint32_t>(t114);
    // 0x0043dafe: xor edi, edi
    uint32_t t115 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t115);
    ctx.edi = static_cast<uint32_t>(t115);
    // 0x0043db00: mov dword ptr [esp + 0x1e4], ebx
    uint32_t t116 = static_cast<uint32_t>(ctx.esp + 0x000001e4u);
    mem.w32(t116, ctx.ebx);
    // 0x0043db07: call 0x413890
    uint32_t t117 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t117);
    mem.w32(t117, 0x0043db0cu);
    sub_00413890(ctx, mem);
    // 0x0043db0c: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x0043db0e: call 0x446820
    uint32_t t118 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    mem.w32(t118, 0x0043db13u);
    sub_00446820(ctx, mem);
    // 0x0043db13: cmp eax, 1
    uint32_t t119 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t119);
    // 0x0043db16: jne 0x43db21
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043db21;
    goto bb_0043db18;
}
bb_0043d9ea: {
    // 0x0043d9ea: lea eax, [esi + 0x24]
    uint32_t t120 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    ctx.eax = static_cast<uint32_t>(t120);
    // 0x0043d9ed: xor edi, edi
    uint32_t t121 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t121);
    ctx.edi = static_cast<uint32_t>(t121);
    // 0x0043d9ef: call 0x413890
    uint32_t t122 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t122);
    mem.w32(t122, 0x0043d9f4u);
    sub_00413890(ctx, mem);
    // 0x0043d9f4: push eax
    uint32_t t123 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t123);
    mem.w32(t123, ctx.eax);
    // 0x0043d9f5: call dword ptr [0x51b214]
    uint32_t t124 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t124);
    mem.w32(t124, 0x0043d9fbu);
    hle_iat_call(ctx, mem, 0x0051b214u);
    // 0x0043d9fb: test eax, eax
    uint32_t t125 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t125);
    // 0x0043d9fd: je 0x43dad0
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043dad0;
    goto bb_0043da03;
}
bb_0043d8d4: {
    // 0x0043d8d4: cmp dword ptr [ebp + 0x88], esi
    uint32_t t126 = static_cast<uint32_t>(ctx.ebp + 0x00000088u);
    uint32_t t127 = mem.r32(t126);
    uint32_t t128 = static_cast<uint32_t>(t127 - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t127, ctx.esi, t128);
    // 0x0043d8da: jle 0x43d8e2
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0043d8e2;
    goto bb_0043d8dc;
}
bb_0043d8d1: {
    // 0x0043d8d1: lea esi, [edi - 1]
    uint32_t t129 = static_cast<uint32_t>(ctx.edi + 0xffffffffu);
    ctx.esi = static_cast<uint32_t>(t129);
    goto bb_0043d8d4;
}
bb_0043db21: {
    // 0x0043db21: mov ebx, esi
    ctx.ebx = static_cast<uint32_t>(ctx.esi);
    // 0x0043db23: mov dword ptr [esi + 4], 0xffffffff
    uint32_t t130 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t130, 0xffffffffu);
    // 0x0043db2a: call 0x43c600
    uint32_t t131 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t131);
    mem.w32(t131, 0x0043db2fu);
    sub_0043c600(ctx, mem);
    // 0x0043db2f: mov ebx, ebp
    ctx.ebx = static_cast<uint32_t>(ctx.ebp);
    // 0x0043db31: mov dword ptr [ebp + 0x84], 1
    uint32_t t132 = static_cast<uint32_t>(ctx.ebp + 0x00000084u);
    mem.w32(t132, 0x00000001u);
    // 0x0043db3b: call 0x43d3a0
    uint32_t t133 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t133);
    mem.w32(t133, 0x0043db40u);
    sub_0043d3a0(ctx, mem);
    goto bb_0043db40;
}
bb_0043db18: {
    // 0x0043db18: mov dword ptr [ebp + 4], 3
    uint32_t t134 = static_cast<uint32_t>(ctx.ebp + 0x00000004u);
    mem.w32(t134, 0x00000003u);
    // 0x0043db1f: jmp 0x43db40
    goto bb_0043db40;
}
bb_0043dad0: {
    // 0x0043dad0: mov ebx, esi
    ctx.ebx = static_cast<uint32_t>(ctx.esi);
    // 0x0043dad2: mov dword ptr [esi + 4], 0xffffffff
    uint32_t t135 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t135, 0xffffffffu);
    // 0x0043dad9: call 0x43c600
    uint32_t t136 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t136);
    mem.w32(t136, 0x0043dadeu);
    sub_0043c600(ctx, mem);
    // 0x0043dade: mov ebx, ebp
    ctx.ebx = static_cast<uint32_t>(ctx.ebp);
    // 0x0043dae0: mov dword ptr [ebp + 0x84], 1
    uint32_t t137 = static_cast<uint32_t>(ctx.ebp + 0x00000084u);
    mem.w32(t137, 0x00000001u);
    // 0x0043daea: call 0x43d3a0
    uint32_t t138 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t138);
    mem.w32(t138, 0x0043daefu);
    sub_0043d3a0(ctx, mem);
    // 0x0043daef: jmp 0x43db49
    goto bb_0043db49;
}
bb_0043da03: {
    // 0x0043da03: lea edi, [esi + 8]
    uint32_t t139 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    ctx.edi = static_cast<uint32_t>(t139);
    // 0x0043da06: mov ecx, 0x535318
    ctx.ecx = static_cast<uint32_t>(0x00535318u);
    // 0x0043da0b: call 0x42bdc0
    uint32_t t140 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t140);
    mem.w32(t140, 0x0043da10u);
    sub_0042bdc0(ctx, mem);
    // 0x0043da10: test al, al
    uint8_t t141 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t141);
    // 0x0043da12: je 0x43da6a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043da6a;
    goto bb_0043da14;
}
bb_0043d8e2: {
    // 0x0043d8e2: mov ecx, dword ptr [ebp + 0x88]
    uint32_t t142 = static_cast<uint32_t>(ctx.ebp + 0x00000088u);
    uint32_t t143 = mem.r32(t142);
    ctx.ecx = static_cast<uint32_t>(t143);
    // 0x0043d8e8: add ecx, 0xc
    uint32_t t144 = static_cast<uint32_t>(ctx.ecx + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x0000000cu, t144);
    ctx.ecx = static_cast<uint32_t>(t144);
    // 0x0043d8eb: cmp ecx, esi
    uint32_t t145 = static_cast<uint32_t>(ctx.ecx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.esi, t145);
    // 0x0043d8ed: jg 0x43d8f8
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0043d8f8;
    goto bb_0043d8ef;
}
bb_0043d8dc: {
    // 0x0043d8dc: mov dword ptr [ebp + 0x88], esi
    uint32_t t146 = static_cast<uint32_t>(ctx.ebp + 0x00000088u);
    mem.w32(t146, ctx.esi);
    goto bb_0043d8e2;
}
bb_0043db40: {
    // 0x0043db40: lea ecx, [esp + 0x1c]
    uint32_t t147 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.ecx = static_cast<uint32_t>(t147);
    // 0x0043db44: call 0x446010
    uint32_t t148 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t148);
    mem.w32(t148, 0x0043db49u);
    sub_00446010(ctx, mem);
    goto bb_0043db49;
}
bb_0043da6a: {
    // 0x0043da6a: lea esi, [ebp + 0x2c]
    uint32_t t149 = static_cast<uint32_t>(ctx.ebp + 0x0000002cu);
    ctx.esi = static_cast<uint32_t>(t149);
    // 0x0043da6d: push esi
    uint32_t t150 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t150);
    mem.w32(t150, ctx.esi);
    // 0x0043da6e: mov edx, 0x535310
    ctx.edx = static_cast<uint32_t>(0x00535310u);
    // 0x0043da73: call 0x414340
    uint32_t t151 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t151);
    mem.w32(t151, 0x0043da78u);
    sub_00414340(ctx, mem);
    // 0x0043da78: push ebx
    uint32_t t152 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t152);
    mem.w32(t152, ctx.ebx);
    // 0x0043da79: push edi
    uint32_t t153 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t153);
    mem.w32(t153, ctx.edi);
    // 0x0043da7a: or eax, 0xffffffff
    uint32_t t154 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t154);
    ctx.eax = static_cast<uint32_t>(t154);
    // 0x0043da7d: call 0x414360
    uint32_t t155 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t155);
    mem.w32(t155, 0x0043da82u);
    sub_00414360(ctx, mem);
    // 0x0043da82: mov dword ptr [esp + 0x18], ebx
    uint32_t t156 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t156, ctx.ebx);
    // 0x0043da86: lea ebx, [esp + 0x18]
    uint32_t t157 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.ebx = static_cast<uint32_t>(t157);
    // 0x0043da8a: lea esi, [ebp + 0x90]
    uint32_t t158 = static_cast<uint32_t>(ctx.ebp + 0x00000090u);
    ctx.esi = static_cast<uint32_t>(t158);
    // 0x0043da90: call 0x43fe30
    uint32_t t159 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t159);
    mem.w32(t159, 0x0043da95u);
    sub_0043fe30(ctx, mem);
    // 0x0043da95: add dword ptr [ebp + 0x8c], 1
    uint32_t t160 = static_cast<uint32_t>(ctx.ebp + 0x0000008cu);
    uint32_t t161 = mem.r32(t160);
    uint32_t t162 = static_cast<uint32_t>(t161 + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t161, 0x00000001u, t162);
    mem.w32(t160, t162);
    goto bb_0043da9c;
}
bb_0043da14: {
    // 0x0043da14: cmp dword ptr [ebp + 0x8c], ebx
    uint32_t t163 = static_cast<uint32_t>(ctx.ebp + 0x0000008cu);
    uint32_t t164 = mem.r32(t163);
    uint32_t t165 = static_cast<uint32_t>(t164 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t164, ctx.ebx, t165);
    // 0x0043da1a: jle 0x43db49
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0043db49;
    goto bb_0043da20;
}
bb_0043d8f8: {
    // 0x0043d8f8: lea eax, [edi - 0xb]
    uint32_t t166 = static_cast<uint32_t>(ctx.edi + 0xfffffff5u);
    ctx.eax = static_cast<uint32_t>(t166);
    // 0x0043d8fb: cmp dword ptr [ebp + 0x88], eax
    uint32_t t167 = static_cast<uint32_t>(ctx.ebp + 0x00000088u);
    uint32_t t168 = mem.r32(t167);
    uint32_t t169 = static_cast<uint32_t>(t168 - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t168, ctx.eax, t169);
    // 0x0043d901: jl 0x43d909
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0043d909;
    goto bb_0043d903;
}
bb_0043d8ef: {
    // 0x0043d8ef: lea edx, [esi - 0xb]
    uint32_t t170 = static_cast<uint32_t>(ctx.esi + 0xfffffff5u);
    ctx.edx = static_cast<uint32_t>(t170);
    // 0x0043d8f2: mov dword ptr [ebp + 0x88], edx
    uint32_t t171 = static_cast<uint32_t>(ctx.ebp + 0x00000088u);
    mem.w32(t171, ctx.edx);
    goto bb_0043d8f8;
}
bb_0043da9c: {
    // 0x0043da9c: mov esi, dword ptr [0x51b1d0]
    uint32_t t172 = mem.r32(0x0051b1d0u);
    ctx.esi = static_cast<uint32_t>(t172);
    // 0x0043daa2: mov dword ptr [ebp + 0xd8], 0
    uint32_t t173 = static_cast<uint32_t>(ctx.ebp + 0x000000d8u);
    mem.w32(t173, 0x00000000u);
    // 0x0043daac: lea esp, [esp]
    ctx.esp = static_cast<uint32_t>(ctx.esp);
    goto bb_0043dab0;
}
bb_0043da20: {
    // 0x0043da20: cmp dword ptr [ebp + 0x44], 0x10
    uint32_t t174 = static_cast<uint32_t>(ctx.ebp + 0x00000044u);
    uint32_t t175 = mem.r32(t174);
    uint32_t t176 = static_cast<uint32_t>(t175 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t175, 0x00000010u, t176);
    // 0x0043da24: lea esi, [ebp + 0x2c]
    uint32_t t177 = static_cast<uint32_t>(ctx.ebp + 0x0000002cu);
    ctx.esi = static_cast<uint32_t>(t177);
    // 0x0043da27: jb 0x43da2e
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043da2e;
    goto bb_0043da29;
}
bb_0043d909: {
    // 0x0043d909: cmp dword ptr [ebp + 0x88], 0
    uint32_t t178 = static_cast<uint32_t>(ctx.ebp + 0x00000088u);
    uint32_t t179 = mem.r32(t178);
    uint32_t t180 = static_cast<uint32_t>(t179 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t179, 0x00000000u, t180);
    // 0x0043d910: jge 0x43d91c
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0043d91c;
    goto bb_0043d912;
}
bb_0043d903: {
    // 0x0043d903: mov dword ptr [ebp + 0x88], eax
    uint32_t t181 = static_cast<uint32_t>(ctx.ebp + 0x00000088u);
    mem.w32(t181, ctx.eax);
    goto bb_0043d909;
}
bb_0043dab0: {
    // 0x0043dab0: push 1
    uint32_t t182 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t182);
    mem.w32(t182, 0x00000001u);
    // 0x0043dab2: call esi
    uint32_t t183 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t183);
    mem.w32(t183, 0x0043dab4u);
    call_indirect(ctx, mem, ctx.esi);
    // 0x0043dab4: cmp dword ptr [ebp + 0xd8], 1
    uint32_t t184 = static_cast<uint32_t>(ctx.ebp + 0x000000d8u);
    uint32_t t185 = mem.r32(t184);
    uint32_t t186 = static_cast<uint32_t>(t185 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t185, 0x00000001u, t186);
    // 0x0043dabb: jne 0x43dab0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043dab0;
    goto bb_0043dabd;
}
bb_0043da2e: {
    // 0x0043da2e: lea ecx, [esi + 4]
    uint32_t t187 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    ctx.ecx = static_cast<uint32_t>(t187);
    goto bb_0043da31;
}
bb_0043da29: {
    // 0x0043da29: mov ecx, dword ptr [esi + 4]
    uint32_t t188 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t189 = mem.r32(t188);
    ctx.ecx = static_cast<uint32_t>(t189);
    // 0x0043da2c: jmp 0x43da31
    goto bb_0043da31;
}
bb_0043d91c: {
    // 0x0043d91c: mov ecx, dword ptr [ebp + 0x94]
    uint32_t t190 = static_cast<uint32_t>(ctx.ebp + 0x00000094u);
    uint32_t t191 = mem.r32(t190);
    ctx.ecx = static_cast<uint32_t>(t191);
    // 0x0043d922: test ecx, ecx
    uint32_t t192 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t192);
    // 0x0043d924: mov ebx, dword ptr [ebp + 0x8c]
    uint32_t t193 = static_cast<uint32_t>(ctx.ebp + 0x0000008cu);
    uint32_t t194 = mem.r32(t193);
    ctx.ebx = static_cast<uint32_t>(t194);
    // 0x0043d92a: je 0x43d93b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d93b;
    goto bb_0043d92c;
}
bb_0043d912: {
    // 0x0043d912: mov dword ptr [ebp + 0x88], 0
    uint32_t t195 = static_cast<uint32_t>(ctx.ebp + 0x00000088u);
    mem.w32(t195, 0x00000000u);
    goto bb_0043d91c;
}
bb_0043dabd: {
    // 0x0043dabd: mov edi, ebp
    ctx.edi = static_cast<uint32_t>(ctx.ebp);
    // 0x0043dabf: call 0x43d3f0
    uint32_t t196 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t196);
    mem.w32(t196, 0x0043dac4u);
    sub_0043d3f0(ctx, mem);
    // 0x0043dac4: mov dword ptr [ebp + 0xd8], 2
    uint32_t t197 = static_cast<uint32_t>(ctx.ebp + 0x000000d8u);
    mem.w32(t197, 0x00000002u);
    // 0x0043dace: jmp 0x43db49
    goto bb_0043db49;
}
bb_0043da31: {
    // 0x0043da31: lea edx, [esp + 0xcc]
    uint32_t t198 = static_cast<uint32_t>(ctx.esp + 0x000000ccu);
    ctx.edx = static_cast<uint32_t>(t198);
    goto bb_0043da38;
}
bb_0043d93b: {
    // 0x0043d93b: call 0x4e0bf2
    uint32_t t199 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t199);
    mem.w32(t199, 0x0043d940u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d940;
}
bb_0043d92c: {
    // 0x0043d92c: mov eax, dword ptr [ebp + 0x98]
    uint32_t t200 = static_cast<uint32_t>(ctx.ebp + 0x00000098u);
    uint32_t t201 = mem.r32(t200);
    ctx.eax = static_cast<uint32_t>(t201);
    // 0x0043d932: sub eax, ecx
    uint32_t t202 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t202);
    ctx.eax = static_cast<uint32_t>(t202);
    // 0x0043d934: sar eax, 2
    uint32_t t203 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t204 = recomp_detail::sar<uint32_t>(ctx.eax, t203);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t203, t204);
    ctx.eax = static_cast<uint32_t>(t204);
    // 0x0043d937: cmp ebx, eax
    uint32_t t205 = static_cast<uint32_t>(ctx.ebx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.eax, t205);
    // 0x0043d939: jb 0x43d940
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043d940;
    goto bb_0043d93b;
}
bb_0043da38: {
    // 0x0043da38: mov al, byte ptr [ecx]
    uint8_t t206 = mem.r8(ctx.ecx);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t206));
    // 0x0043da3a: mov byte ptr [edx], al
    mem.w8(ctx.edx, recomp_detail::r8l(ctx.eax));
    // 0x0043da3c: add ecx, 1
    uint32_t t207 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t207);
    ctx.ecx = static_cast<uint32_t>(t207);
    // 0x0043da3f: add edx, 1
    uint32_t t208 = static_cast<uint32_t>(ctx.edx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000001u, t208);
    ctx.edx = static_cast<uint32_t>(t208);
    // 0x0043da42: test al, al
    uint8_t t209 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t209);
    // 0x0043da44: jne 0x43da38
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043da38;
    goto bb_0043da46;
}
bb_0043d940: {
    // 0x0043d940: mov eax, dword ptr [ebp + 0x94]
    uint32_t t210 = static_cast<uint32_t>(ctx.ebp + 0x00000094u);
    uint32_t t211 = mem.r32(t210);
    ctx.eax = static_cast<uint32_t>(t211);
    // 0x0043d946: cmp dword ptr [eax + ebx*4], esi
    uint32_t t212 = recomp_detail::shl<uint32_t>(ctx.ebx, 0x00000002u);
    uint32_t t213 = static_cast<uint32_t>(ctx.eax + t212);
    uint32_t t214 = mem.r32(t213);
    uint32_t t215 = static_cast<uint32_t>(t214 - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t214, ctx.esi, t215);
    // 0x0043d949: je 0x43d990
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d990;
    goto bb_0043d94b;
}
bb_0043da46: {
    // 0x0043da46: lea eax, [esp + 0xcc]
    uint32_t t216 = static_cast<uint32_t>(ctx.esp + 0x000000ccu);
    ctx.eax = static_cast<uint32_t>(t216);
    // 0x0043da4d: push eax
    uint32_t t217 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t217);
    mem.w32(t217, ctx.eax);
    // 0x0043da4e: call dword ptr [0x51b210]
    uint32_t t218 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t218);
    mem.w32(t218, 0x0043da54u);
    hle_iat_call(ctx, mem, 0x0051b210u);
    // 0x0043da54: push esi
    uint32_t t219 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t219);
    mem.w32(t219, ctx.esi);
    // 0x0043da55: lea edx, [esp + 0xd0]
    uint32_t t220 = static_cast<uint32_t>(ctx.esp + 0x000000d0u);
    ctx.edx = static_cast<uint32_t>(t220);
    // 0x0043da5c: call 0x410c60
    uint32_t t221 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t221);
    mem.w32(t221, 0x0043da61u);
    sub_00410c60(ctx, mem);
    // 0x0043da61: add dword ptr [ebp + 0x8c], -1
    uint32_t t222 = static_cast<uint32_t>(ctx.ebp + 0x0000008cu);
    uint32_t t223 = mem.r32(t222);
    uint32_t t224 = static_cast<uint32_t>(t223 + 0xffffffffu);
    recomp_detail::update_flags_add<uint32_t>(ctx, t223, 0xffffffffu, t224);
    mem.w32(t222, t224);
    // 0x0043da68: jmp 0x43da9c
    goto bb_0043da9c;
}
bb_0043d94b: {
    // 0x0043d94b: mov byte ptr [0x76e0a0], 1
    mem.w8(0x0076e0a0u, uint8_t{0x01u});
    // 0x0043d952: mov ecx, dword ptr [ebp + 0x94]
    uint32_t t225 = static_cast<uint32_t>(ctx.ebp + 0x00000094u);
    uint32_t t226 = mem.r32(t225);
    ctx.ecx = static_cast<uint32_t>(t226);
    // 0x0043d958: test ecx, ecx
    uint32_t t227 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t227);
    // 0x0043d95a: mov ebx, dword ptr [ebp + 0x8c]
    uint32_t t228 = static_cast<uint32_t>(ctx.ebp + 0x0000008cu);
    uint32_t t229 = mem.r32(t228);
    ctx.ebx = static_cast<uint32_t>(t229);
    // 0x0043d960: je 0x43d971
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043d971;
    goto bb_0043d962;
}
bb_0043d971: {
    // 0x0043d971: call 0x4e0bf2
    uint32_t t230 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t230);
    mem.w32(t230, 0x0043d976u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043d976;
}
bb_0043d962: {
    // 0x0043d962: mov eax, dword ptr [ebp + 0x98]
    uint32_t t231 = static_cast<uint32_t>(ctx.ebp + 0x00000098u);
    uint32_t t232 = mem.r32(t231);
    ctx.eax = static_cast<uint32_t>(t232);
    // 0x0043d968: sub eax, ecx
    uint32_t t233 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t233);
    ctx.eax = static_cast<uint32_t>(t233);
    // 0x0043d96a: sar eax, 2
    uint32_t t234 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t235 = recomp_detail::sar<uint32_t>(ctx.eax, t234);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t234, t235);
    ctx.eax = static_cast<uint32_t>(t235);
    // 0x0043d96d: cmp ebx, eax
    uint32_t t236 = static_cast<uint32_t>(ctx.ebx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.eax, t236);
    // 0x0043d96f: jb 0x43d976
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043d976;
    goto bb_0043d971;
}
bb_0043d976: {
    // 0x0043d976: mov ecx, dword ptr [ebp + 0x94]
    uint32_t t237 = static_cast<uint32_t>(ctx.ebp + 0x00000094u);
    uint32_t t238 = mem.r32(t237);
    ctx.ecx = static_cast<uint32_t>(t238);
    // 0x0043d97c: mov dword ptr [ecx + ebx*4], esi
    uint32_t t239 = recomp_detail::shl<uint32_t>(ctx.ebx, 0x00000002u);
    uint32_t t240 = static_cast<uint32_t>(ctx.ecx + t239);
    mem.w32(t240, ctx.esi);
    // 0x0043d97f: mov ebx, ebp
    ctx.ebx = static_cast<uint32_t>(ctx.ebp);
    // 0x0043d981: mov dword ptr [ebp + 0x84], 1
    uint32_t t241 = static_cast<uint32_t>(ctx.ebp + 0x00000084u);
    mem.w32(t241, 0x00000001u);
    // 0x0043d98b: call 0x43d3a0
    uint32_t t242 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t242);
    mem.w32(t242, 0x0043d990u);
    sub_0043d3a0(ctx, mem);
    goto bb_0043d990;
}
}

// sub_0043dce0 | subsystem=Replay | canonical | 14 blocks | 96 insns
void sub_0043dce0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043dce0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0043dce2: push 0x516c88
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00516c88u);
    // 0x0043dce7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0043dced: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0043dcee: sub esp, 0x20
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000020u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000020u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x0043dcf1: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0043dcf6: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0043dcf8: mov dword ptr [esp + 0x1c], eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t8, ctx.eax);
    // 0x0043dcfc: push ebx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ebx);
    // 0x0043dcfd: push ebp
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.ebp);
    // 0x0043dcfe: push esi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.esi);
    // 0x0043dcff: push edi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.edi);
    // 0x0043dd00: mov eax, dword ptr [0x54b458]
    uint32_t t13 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0043dd05: xor eax, esp
    uint32_t t14 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x0043dd07: push eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.eax);
    // 0x0043dd08: lea eax, [esp + 0x34]
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0043dd0c: mov dword ptr fs:[0], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t17, ctx.eax);
    // 0x0043dd12: mov ebp, dword ptr [esp + 0x44]
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    uint32_t t19 = mem.r32(t18);
    ctx.ebp = static_cast<uint32_t>(t19);
    // 0x0043dd16: xor ebx, ebx
    uint32_t t20 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t20);
    ctx.ebx = static_cast<uint32_t>(t20);
    // 0x0043dd18: push -1
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0xffffffffu);
    // 0x0043dd1a: lea eax, [ebp + 0x2c]
    uint32_t t22 = static_cast<uint32_t>(ctx.ebp + 0x0000002cu);
    ctx.eax = static_cast<uint32_t>(t22);
    // 0x0043dd1d: push ebx
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, ctx.ebx);
    // 0x0043dd1e: push eax
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, ctx.eax);
    // 0x0043dd1f: lea ecx, [esp + 0x20]
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    ctx.ecx = static_cast<uint32_t>(t25);
    // 0x0043dd23: mov dword ptr [esp + 0x38], 0xf
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    mem.w32(t26, 0x0000000fu);
    // 0x0043dd2b: mov dword ptr [esp + 0x34], ebx
    uint32_t t27 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    mem.w32(t27, ctx.ebx);
    // 0x0043dd2f: mov byte ptr [esp + 0x24], bl
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w8(t28, recomp_detail::r8l(ctx.ebx));
    // 0x0043dd33: call 0x4079d0
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x0043dd38u);
    sub_004079d0(ctx, mem);
    // 0x0043dd38: lea edi, [esp + 0x14]
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.edi = static_cast<uint32_t>(t30);
    // 0x0043dd3c: mov dword ptr [esp + 0x3c], ebx
    uint32_t t31 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    mem.w32(t31, ctx.ebx);
    // 0x0043dd40: call 0x43d7b0
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x0043dd45u);
    sub_0043d7b0(ctx, mem);
    // 0x0043dd45: cmp dword ptr [esp + 0x28], ebx
    uint32_t t33 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t34 = mem.r32(t33);
    uint32_t t35 = static_cast<uint32_t>(t34 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t34, ctx.ebx, t35);
    // 0x0043dd49: jne 0x43dd58
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043dd58;
    goto bb_0043dd4b;
}
bb_0043dd58: {
    // 0x0043dd58: mov eax, dword ptr [ebp + 0xa8]
    uint32_t t36 = static_cast<uint32_t>(ctx.ebp + 0x000000a8u);
    uint32_t t37 = mem.r32(t36);
    ctx.eax = static_cast<uint32_t>(t37);
    // 0x0043dd5e: cmp eax, -1
    uint32_t t38 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t38);
    // 0x0043dd61: jne 0x43dd6c
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043dd6c;
    goto bb_0043dd63;
}
bb_0043dd4b: {
    // 0x0043dd4b: push ebx
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, ctx.ebx);
    // 0x0043dd4c: push 0x534f8a
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, 0x00534f8au);
    // 0x0043dd51: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x0043dd53: call 0x407c10
    uint32_t t41 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    mem.w32(t41, 0x0043dd58u);
    sub_00407c10(ctx, mem);
    goto bb_0043dd58;
}
bb_0043dd6c: {
    // 0x0043dd6c: cmp eax, -2
    uint32_t t42 = static_cast<uint32_t>(ctx.eax - 0xfffffffeu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xfffffffeu, t42);
    // 0x0043dd6f: jne 0x43dd81
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043dd81;
    goto bb_0043dd71;
}
bb_0043dd63: {
    // 0x0043dd63: push 0x1b
    uint32_t t43 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    mem.w32(t43, 0x0000001bu);
    // 0x0043dd65: push 0x7b4124
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, 0x007b4124u);
    // 0x0043dd6a: jmp 0x43dd78
    goto bb_0043dd78;
}
bb_0043dd81: {
    // 0x0043dd81: cmp dword ptr [esp + 0x28], ebx
    uint32_t t45 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t46 = mem.r32(t45);
    uint32_t t47 = static_cast<uint32_t>(t46 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t46, ctx.ebx, t47);
    // 0x0043dd85: je 0x43dddf
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043dddf;
    goto bb_0043dd87;
}
bb_0043dd71: {
    // 0x0043dd71: push 0x23
    uint32_t t48 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    mem.w32(t48, 0x00000023u);
    // 0x0043dd73: push 0x7b413c
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, 0x007b413cu);
}
bb_0043dd78: {
    // 0x0043dd78: lea eax, [esp + 0x1c]
    uint32_t t50 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.eax = static_cast<uint32_t>(t50);
    // 0x0043dd7c: call 0x414660
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, 0x0043dd81u);
    sub_00414660(ctx, mem);
    goto bb_0043dd81;
}
bb_0043dddf: {
    // 0x0043dddf: cmp dword ptr [esp + 0x2c], 0x10
    uint32_t t52 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    uint32_t t53 = mem.r32(t52);
    uint32_t t54 = static_cast<uint32_t>(t53 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t53, 0x00000010u, t54);
    // 0x0043dde4: jb 0x43ddf3
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043ddf3;
    goto bb_0043dde6;
}
bb_0043dd87: {
    // 0x0043dd87: push 0x15
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, 0x00000015u);
    // 0x0043dd89: mov eax, 0x20
    ctx.eax = static_cast<uint32_t>(0x00000020u);
    // 0x0043dd8e: mov edi, 0x200
    ctx.edi = static_cast<uint32_t>(0x00000200u);
    // 0x0043dd93: call 0x4bd1e0
    uint32_t t56 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    mem.w32(t56, 0x0043dd98u);
    sub_004bd1e0(ctx, mem);
    // 0x0043dd98: mov esi, dword ptr [ebp + 0xc]
    uint32_t t57 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t58 = mem.r32(t57);
    ctx.esi = static_cast<uint32_t>(t58);
    // 0x0043dd9b: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x0043dd9d: mov eax, dword ptr [edi]
    uint32_t t59 = mem.r32(ctx.edi);
    ctx.eax = static_cast<uint32_t>(t59);
    // 0x0043dd9f: mov ebx, dword ptr [eax + 8]
    uint32_t t60 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    uint32_t t61 = mem.r32(t60);
    ctx.ebx = static_cast<uint32_t>(t61);
    // 0x0043dda2: add esp, 4
    uint32_t t62 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t62);
    ctx.esp = static_cast<uint32_t>(t62);
    // 0x0043dda5: call 0x49f090
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, 0x0043ddaau);
    sub_0049f090(ctx, mem);
    // 0x0043ddaa: mov esi, dword ptr [ebp + 0xc]
    uint32_t t64 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t65 = mem.r32(t64);
    ctx.esi = static_cast<uint32_t>(t65);
    // 0x0043ddad: call 0x43c3c0
    uint32_t t66 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    mem.w32(t66, 0x0043ddb2u);
    sub_0043c3c0(ctx, mem);
    // 0x0043ddb2: cmp dword ptr [esp + 0x2c], 0x10
    uint32_t t67 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    uint32_t t68 = mem.r32(t67);
    uint32_t t69 = static_cast<uint32_t>(t68 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t68, 0x00000010u, t69);
    // 0x0043ddb7: mov eax, dword ptr [esp + 0x18]
    uint32_t t70 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t71 = mem.r32(t70);
    ctx.eax = static_cast<uint32_t>(t71);
    // 0x0043ddbb: jae 0x43ddc1
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0043ddc1;
    goto bb_0043ddbd;
}
bb_0043ddf3: {
    // 0x0043ddf3: mov ecx, dword ptr [esp + 0x34]
    uint32_t t72 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    uint32_t t73 = mem.r32(t72);
    ctx.ecx = static_cast<uint32_t>(t73);
    // 0x0043ddf7: mov dword ptr fs:[0], ecx
    uint32_t t74 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t74, ctx.ecx);
    // 0x0043ddfe: pop ecx
    uint32_t t75 = ctx.esp;
    uint32_t t76 = mem.r32(t75);
    uint32_t t77 = static_cast<uint32_t>(t75 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    ctx.ecx = static_cast<uint32_t>(t76);
    // 0x0043ddff: pop edi
    uint32_t t78 = ctx.esp;
    uint32_t t79 = mem.r32(t78);
    uint32_t t80 = static_cast<uint32_t>(t78 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    ctx.edi = static_cast<uint32_t>(t79);
    // 0x0043de00: pop esi
    uint32_t t81 = ctx.esp;
    uint32_t t82 = mem.r32(t81);
    uint32_t t83 = static_cast<uint32_t>(t81 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t83);
    ctx.esi = static_cast<uint32_t>(t82);
    // 0x0043de01: pop ebp
    uint32_t t84 = ctx.esp;
    uint32_t t85 = mem.r32(t84);
    uint32_t t86 = static_cast<uint32_t>(t84 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t86);
    ctx.ebp = static_cast<uint32_t>(t85);
    // 0x0043de02: pop ebx
    uint32_t t87 = ctx.esp;
    uint32_t t88 = mem.r32(t87);
    uint32_t t89 = static_cast<uint32_t>(t87 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t89);
    ctx.ebx = static_cast<uint32_t>(t88);
    // 0x0043de03: mov ecx, dword ptr [esp + 0x1c]
    uint32_t t90 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t91 = mem.r32(t90);
    ctx.ecx = static_cast<uint32_t>(t91);
    // 0x0043de07: xor ecx, esp
    uint32_t t92 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t92);
    ctx.ecx = static_cast<uint32_t>(t92);
    // 0x0043de09: call 0x4e02f8
    uint32_t t93 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    mem.w32(t93, 0x0043de0eu);
    hle_crt_004e02f8(ctx, mem);
    // 0x0043de0e: add esp, 0x2c
    uint32_t t94 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000002cu, t94);
    ctx.esp = static_cast<uint32_t>(t94);
    // 0x0043de11: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0043dde6: {
    // 0x0043dde6: mov ecx, dword ptr [esp + 0x18]
    uint32_t t95 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t96 = mem.r32(t95);
    ctx.ecx = static_cast<uint32_t>(t96);
    // 0x0043ddea: push ecx
    uint32_t t97 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t97);
    mem.w32(t97, ctx.ecx);
    // 0x0043ddeb: call 0x4e02f3
    uint32_t t98 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t98);
    mem.w32(t98, 0x0043ddf0u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043ddf0: add esp, 4
    uint32_t t99 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t99);
    ctx.esp = static_cast<uint32_t>(t99);
    goto bb_0043ddf3;
}
bb_0043ddc1: {
    // 0x0043ddc1: mov esi, dword ptr [ebp + 0xc]
    uint32_t t100 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t101 = mem.r32(t100);
    ctx.esi = static_cast<uint32_t>(t101);
    // 0x0043ddc4: push 0
    uint32_t t102 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    mem.w32(t102, 0x00000000u);
    // 0x0043ddc6: push -1
    uint32_t t103 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    mem.w32(t103, 0xffffffffu);
    // 0x0043ddc8: push eax
    uint32_t t104 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t104);
    mem.w32(t104, ctx.eax);
    // 0x0043ddc9: push 0
    uint32_t t105 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t105);
    mem.w32(t105, 0x00000000u);
    // 0x0043ddcb: push 0
    uint32_t t106 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t106);
    mem.w32(t106, 0x00000000u);
    // 0x0043ddcd: xor eax, eax
    uint32_t t107 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t107);
    ctx.eax = static_cast<uint32_t>(t107);
    // 0x0043ddcf: call 0x49f280
    uint32_t t108 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t108);
    mem.w32(t108, 0x0043ddd4u);
    sub_0049f280(ctx, mem);
    // 0x0043ddd4: mov esi, dword ptr [ebp + 0xc]
    uint32_t t109 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t110 = mem.r32(t109);
    ctx.esi = static_cast<uint32_t>(t110);
    // 0x0043ddd7: call 0x43c420
    uint32_t t111 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t111);
    mem.w32(t111, 0x0043dddcu);
    sub_0043c420(ctx, mem);
    // 0x0043dddc: mov dword ptr [ebp + 0x7c], edi
    uint32_t t112 = static_cast<uint32_t>(ctx.ebp + 0x0000007cu);
    mem.w32(t112, ctx.edi);
    goto bb_0043dddf;
}
bb_0043ddbd: {
    // 0x0043ddbd: lea eax, [esp + 0x18]
    uint32_t t113 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.eax = static_cast<uint32_t>(t113);
    goto bb_0043ddc1;
}
}

// sub_0043de20 | subsystem=Replay | canonical | 14 blocks | 525 insns
void sub_0043de20(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043de20: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0043de22: push 0x5145b4
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005145b4u);
    // 0x0043de27: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0043de2d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0043de2e: sub esp, 0x714
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000714u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000714u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x0043de34: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0043de39: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0043de3b: mov dword ptr [esp + 0x710], eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000710u);
    mem.w32(t8, ctx.eax);
    // 0x0043de42: push ebx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ebx);
    // 0x0043de43: push ebp
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.ebp);
    // 0x0043de44: push esi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.esi);
    // 0x0043de45: push edi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.edi);
    // 0x0043de46: mov eax, dword ptr [0x54b458]
    uint32_t t13 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0043de4b: xor eax, esp
    uint32_t t14 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x0043de4d: push eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.eax);
    // 0x0043de4e: lea eax, [esp + 0x728]
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000728u);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0043de55: mov dword ptr fs:[0], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t17, ctx.eax);
    // 0x0043de5b: mov edi, ecx
    ctx.edi = static_cast<uint32_t>(ctx.ecx);
    // 0x0043de5d: mov ebp, dword ptr [esp + 0x738]
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x00000738u);
    uint32_t t19 = mem.r32(t18);
    ctx.ebp = static_cast<uint32_t>(t19);
    // 0x0043de64: xor ebx, ebx
    uint32_t t20 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t20);
    ctx.ebx = static_cast<uint32_t>(t20);
    // 0x0043de66: mov dword ptr [esp + 0x18], ebx
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t21, ctx.ebx);
    // 0x0043de6a: push 4
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x00000004u);
    // 0x0043de6c: mov esi, 0xf
    ctx.esi = static_cast<uint32_t>(0x0000000fu);
    // 0x0043de71: push 0x536b50
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x00536b50u);
    // 0x0043de76: lea ecx, [esp + 0x2c]
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    ctx.ecx = static_cast<uint32_t>(t24);
    // 0x0043de7a: mov dword ptr [esp + 0x28], ebp
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t25, ctx.ebp);
    // 0x0043de7e: mov dword ptr [esp + 0x44], esi
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    mem.w32(t26, ctx.esi);
    // 0x0043de82: mov dword ptr [esp + 0x40], ebx
    uint32_t t27 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    mem.w32(t27, ctx.ebx);
    // 0x0043de86: mov byte ptr [esp + 0x30], bl
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    mem.w8(t28, recomp_detail::r8l(ctx.ebx));
    // 0x0043de8a: call 0x407c10
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x0043de8fu);
    sub_00407c10(ctx, mem);
    // 0x0043de8f: mov dword ptr [esp + 0x730], 1
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w32(t30, 0x00000001u);
    // 0x0043de9a: push 4
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x00000004u);
    // 0x0043de9c: push 0x7b4159
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x007b4159u);
    // 0x0043dea1: lea ecx, [esp + 0x48]
    uint32_t t33 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    ctx.ecx = static_cast<uint32_t>(t33);
    // 0x0043dea5: mov dword ptr [esp + 0x60], esi
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    mem.w32(t34, ctx.esi);
    // 0x0043dea9: mov dword ptr [esp + 0x5c], ebx
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    mem.w32(t35, ctx.ebx);
    // 0x0043dead: mov byte ptr [esp + 0x4c], bl
    uint32_t t36 = static_cast<uint32_t>(ctx.esp + 0x0000004cu);
    mem.w8(t36, recomp_detail::r8l(ctx.ebx));
    // 0x0043deb1: call 0x407c10
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, 0x0043deb6u);
    sub_00407c10(ctx, mem);
    // 0x0043deb6: mov dword ptr [esp + 0x730], 2
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w32(t38, 0x00000002u);
    // 0x0043dec1: push 3
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, 0x00000003u);
    // 0x0043dec3: push 0x536b60
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, 0x00536b60u);
    // 0x0043dec8: lea ecx, [esp + 0x64]
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + 0x00000064u);
    ctx.ecx = static_cast<uint32_t>(t41);
    // 0x0043decc: mov dword ptr [esp + 0x7c], esi
    uint32_t t42 = static_cast<uint32_t>(ctx.esp + 0x0000007cu);
    mem.w32(t42, ctx.esi);
    // 0x0043ded0: mov dword ptr [esp + 0x78], ebx
    uint32_t t43 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    mem.w32(t43, ctx.ebx);
    // 0x0043ded4: mov byte ptr [esp + 0x68], bl
    uint32_t t44 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    mem.w8(t44, recomp_detail::r8l(ctx.ebx));
    // 0x0043ded8: call 0x407c10
    uint32_t t45 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    mem.w32(t45, 0x0043deddu);
    sub_00407c10(ctx, mem);
    // 0x0043dedd: mov byte ptr [esp + 0x730], 3
    uint32_t t46 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t46, uint8_t{0x03u});
    // 0x0043dee5: push 7
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, 0x00000007u);
    // 0x0043dee7: push 0x7b415e
    uint32_t t48 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    mem.w32(t48, 0x007b415eu);
    // 0x0043deec: lea ecx, [esp + 0x80]
    uint32_t t49 = static_cast<uint32_t>(ctx.esp + 0x00000080u);
    ctx.ecx = static_cast<uint32_t>(t49);
    // 0x0043def3: mov dword ptr [esp + 0x98], esi
    uint32_t t50 = static_cast<uint32_t>(ctx.esp + 0x00000098u);
    mem.w32(t50, ctx.esi);
    // 0x0043defa: mov dword ptr [esp + 0x94], ebx
    uint32_t t51 = static_cast<uint32_t>(ctx.esp + 0x00000094u);
    mem.w32(t51, ctx.ebx);
    // 0x0043df01: mov byte ptr [esp + 0x84], bl
    uint32_t t52 = static_cast<uint32_t>(ctx.esp + 0x00000084u);
    mem.w8(t52, recomp_detail::r8l(ctx.ebx));
    // 0x0043df08: call 0x407c10
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, 0x0043df0du);
    sub_00407c10(ctx, mem);
    // 0x0043df0d: mov byte ptr [esp + 0x730], 4
    uint32_t t54 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t54, uint8_t{0x04u});
    // 0x0043df15: push 4
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, 0x00000004u);
    // 0x0043df17: push 0x536b74
    uint32_t t56 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    mem.w32(t56, 0x00536b74u);
    // 0x0043df1c: lea ecx, [esp + 0x9c]
    uint32_t t57 = static_cast<uint32_t>(ctx.esp + 0x0000009cu);
    ctx.ecx = static_cast<uint32_t>(t57);
    // 0x0043df23: mov dword ptr [esp + 0xb4], esi
    uint32_t t58 = static_cast<uint32_t>(ctx.esp + 0x000000b4u);
    mem.w32(t58, ctx.esi);
    // 0x0043df2a: mov dword ptr [esp + 0xb0], ebx
    uint32_t t59 = static_cast<uint32_t>(ctx.esp + 0x000000b0u);
    mem.w32(t59, ctx.ebx);
    // 0x0043df31: mov byte ptr [esp + 0xa0], bl
    uint32_t t60 = static_cast<uint32_t>(ctx.esp + 0x000000a0u);
    mem.w8(t60, recomp_detail::r8l(ctx.ebx));
    // 0x0043df38: call 0x407c10
    uint32_t t61 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    mem.w32(t61, 0x0043df3du);
    sub_00407c10(ctx, mem);
    // 0x0043df3d: mov byte ptr [esp + 0x730], 5
    uint32_t t62 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t62, uint8_t{0x05u});
    // 0x0043df45: push 4
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, 0x00000004u);
    // 0x0043df47: push 0x7b4166
    uint32_t t64 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    mem.w32(t64, 0x007b4166u);
    // 0x0043df4c: lea ecx, [esp + 0xb8]
    uint32_t t65 = static_cast<uint32_t>(ctx.esp + 0x000000b8u);
    ctx.ecx = static_cast<uint32_t>(t65);
    // 0x0043df53: mov dword ptr [esp + 0xd0], esi
    uint32_t t66 = static_cast<uint32_t>(ctx.esp + 0x000000d0u);
    mem.w32(t66, ctx.esi);
    // 0x0043df5a: mov dword ptr [esp + 0xcc], ebx
    uint32_t t67 = static_cast<uint32_t>(ctx.esp + 0x000000ccu);
    mem.w32(t67, ctx.ebx);
    // 0x0043df61: mov byte ptr [esp + 0xbc], bl
    uint32_t t68 = static_cast<uint32_t>(ctx.esp + 0x000000bcu);
    mem.w8(t68, recomp_detail::r8l(ctx.ebx));
    // 0x0043df68: call 0x407c10
    uint32_t t69 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    mem.w32(t69, 0x0043df6du);
    sub_00407c10(ctx, mem);
    // 0x0043df6d: mov byte ptr [esp + 0x730], 6
    uint32_t t70 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t70, uint8_t{0x06u});
    // 0x0043df75: push 5
    uint32_t t71 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t71);
    mem.w32(t71, 0x00000005u);
    // 0x0043df77: push 0x536b84
    uint32_t t72 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    mem.w32(t72, 0x00536b84u);
    // 0x0043df7c: lea ecx, [esp + 0xd4]
    uint32_t t73 = static_cast<uint32_t>(ctx.esp + 0x000000d4u);
    ctx.ecx = static_cast<uint32_t>(t73);
    // 0x0043df83: mov dword ptr [esp + 0xec], esi
    uint32_t t74 = static_cast<uint32_t>(ctx.esp + 0x000000ecu);
    mem.w32(t74, ctx.esi);
    // 0x0043df8a: mov dword ptr [esp + 0xe8], ebx
    uint32_t t75 = static_cast<uint32_t>(ctx.esp + 0x000000e8u);
    mem.w32(t75, ctx.ebx);
    // 0x0043df91: mov byte ptr [esp + 0xd8], bl
    uint32_t t76 = static_cast<uint32_t>(ctx.esp + 0x000000d8u);
    mem.w8(t76, recomp_detail::r8l(ctx.ebx));
    // 0x0043df98: call 0x407c10
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, 0x0043df9du);
    sub_00407c10(ctx, mem);
    // 0x0043df9d: mov byte ptr [esp + 0x730], 7
    uint32_t t78 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t78, uint8_t{0x07u});
    // 0x0043dfa5: push 0xb
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, 0x0000000bu);
    // 0x0043dfa7: push 0x7b416b
    uint32_t t80 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    mem.w32(t80, 0x007b416bu);
    // 0x0043dfac: lea ecx, [esp + 0xf0]
    uint32_t t81 = static_cast<uint32_t>(ctx.esp + 0x000000f0u);
    ctx.ecx = static_cast<uint32_t>(t81);
    // 0x0043dfb3: mov dword ptr [esp + 0x108], esi
    uint32_t t82 = static_cast<uint32_t>(ctx.esp + 0x00000108u);
    mem.w32(t82, ctx.esi);
    // 0x0043dfba: mov dword ptr [esp + 0x104], ebx
    uint32_t t83 = static_cast<uint32_t>(ctx.esp + 0x00000104u);
    mem.w32(t83, ctx.ebx);
    // 0x0043dfc1: mov byte ptr [esp + 0xf4], bl
    uint32_t t84 = static_cast<uint32_t>(ctx.esp + 0x000000f4u);
    mem.w8(t84, recomp_detail::r8l(ctx.ebx));
    // 0x0043dfc8: call 0x407c10
    uint32_t t85 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t85);
    mem.w32(t85, 0x0043dfcdu);
    sub_00407c10(ctx, mem);
    // 0x0043dfcd: mov byte ptr [esp + 0x730], 8
    uint32_t t86 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t86, uint8_t{0x08u});
    // 0x0043dfd5: mov dword ptr [esp + 0x11c], esi
    uint32_t t87 = static_cast<uint32_t>(ctx.esp + 0x0000011cu);
    mem.w32(t87, ctx.esi);
    // 0x0043dfdc: mov dword ptr [esp + 0x118], ebx
    uint32_t t88 = static_cast<uint32_t>(ctx.esp + 0x00000118u);
    mem.w32(t88, ctx.ebx);
    // 0x0043dfe3: mov byte ptr [esp + 0x108], bl
    uint32_t t89 = static_cast<uint32_t>(ctx.esp + 0x00000108u);
    mem.w8(t89, recomp_detail::r8l(ctx.ebx));
    // 0x0043dfea: push 5
    uint32_t t90 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    mem.w32(t90, 0x00000005u);
    // 0x0043dfec: push 0x536b98
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, 0x00536b98u);
    // 0x0043dff1: lea ecx, [esp + 0x10c]
    uint32_t t92 = static_cast<uint32_t>(ctx.esp + 0x0000010cu);
    ctx.ecx = static_cast<uint32_t>(t92);
    // 0x0043dff8: call 0x407c10
    uint32_t t93 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    mem.w32(t93, 0x0043dffdu);
    sub_00407c10(ctx, mem);
    // 0x0043dffd: mov byte ptr [esp + 0x730], 9
    uint32_t t94 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t94, uint8_t{0x09u});
    // 0x0043e005: push 5
    uint32_t t95 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t95);
    mem.w32(t95, 0x00000005u);
    // 0x0043e007: push 0x7b4177
    uint32_t t96 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    mem.w32(t96, 0x007b4177u);
    // 0x0043e00c: lea ecx, [esp + 0x128]
    uint32_t t97 = static_cast<uint32_t>(ctx.esp + 0x00000128u);
    ctx.ecx = static_cast<uint32_t>(t97);
    // 0x0043e013: mov dword ptr [esp + 0x140], esi
    uint32_t t98 = static_cast<uint32_t>(ctx.esp + 0x00000140u);
    mem.w32(t98, ctx.esi);
    // 0x0043e01a: mov dword ptr [esp + 0x13c], ebx
    uint32_t t99 = static_cast<uint32_t>(ctx.esp + 0x0000013cu);
    mem.w32(t99, ctx.ebx);
    // 0x0043e021: mov byte ptr [esp + 0x12c], bl
    uint32_t t100 = static_cast<uint32_t>(ctx.esp + 0x0000012cu);
    mem.w8(t100, recomp_detail::r8l(ctx.ebx));
    // 0x0043e028: call 0x407c10
    uint32_t t101 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t101);
    mem.w32(t101, 0x0043e02du);
    sub_00407c10(ctx, mem);
    // 0x0043e02d: mov byte ptr [esp + 0x730], 0xa
    uint32_t t102 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t102, uint8_t{0x0au});
    // 0x0043e035: push 6
    uint32_t t103 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    mem.w32(t103, 0x00000006u);
    // 0x0043e037: push 0x536ba8
    uint32_t t104 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t104);
    mem.w32(t104, 0x00536ba8u);
    // 0x0043e03c: lea ecx, [esp + 0x144]
    uint32_t t105 = static_cast<uint32_t>(ctx.esp + 0x00000144u);
    ctx.ecx = static_cast<uint32_t>(t105);
    // 0x0043e043: mov dword ptr [esp + 0x15c], esi
    uint32_t t106 = static_cast<uint32_t>(ctx.esp + 0x0000015cu);
    mem.w32(t106, ctx.esi);
    // 0x0043e04a: mov dword ptr [esp + 0x158], ebx
    uint32_t t107 = static_cast<uint32_t>(ctx.esp + 0x00000158u);
    mem.w32(t107, ctx.ebx);
    // 0x0043e051: mov byte ptr [esp + 0x148], bl
    uint32_t t108 = static_cast<uint32_t>(ctx.esp + 0x00000148u);
    mem.w8(t108, recomp_detail::r8l(ctx.ebx));
    // 0x0043e058: call 0x407c10
    uint32_t t109 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t109);
    mem.w32(t109, 0x0043e05du);
    sub_00407c10(ctx, mem);
    // 0x0043e05d: mov byte ptr [esp + 0x730], 0xb
    uint32_t t110 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t110, uint8_t{0x0bu});
    // 0x0043e065: push 6
    uint32_t t111 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t111);
    mem.w32(t111, 0x00000006u);
    // 0x0043e067: push 0x7b417d
    uint32_t t112 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t112);
    mem.w32(t112, 0x007b417du);
    // 0x0043e06c: lea ecx, [esp + 0x160]
    uint32_t t113 = static_cast<uint32_t>(ctx.esp + 0x00000160u);
    ctx.ecx = static_cast<uint32_t>(t113);
    // 0x0043e073: mov dword ptr [esp + 0x178], esi
    uint32_t t114 = static_cast<uint32_t>(ctx.esp + 0x00000178u);
    mem.w32(t114, ctx.esi);
    // 0x0043e07a: mov dword ptr [esp + 0x174], ebx
    uint32_t t115 = static_cast<uint32_t>(ctx.esp + 0x00000174u);
    mem.w32(t115, ctx.ebx);
    // 0x0043e081: mov byte ptr [esp + 0x164], bl
    uint32_t t116 = static_cast<uint32_t>(ctx.esp + 0x00000164u);
    mem.w8(t116, recomp_detail::r8l(ctx.ebx));
    // 0x0043e088: call 0x407c10
    uint32_t t117 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t117);
    mem.w32(t117, 0x0043e08du);
    sub_00407c10(ctx, mem);
    // 0x0043e08d: mov byte ptr [esp + 0x730], 0xc
    uint32_t t118 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t118, uint8_t{0x0cu});
    // 0x0043e095: push 0x10
    uint32_t t119 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t119);
    mem.w32(t119, 0x00000010u);
    // 0x0043e097: push 0x536bb8
    uint32_t t120 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t120);
    mem.w32(t120, 0x00536bb8u);
    // 0x0043e09c: lea ecx, [esp + 0x17c]
    uint32_t t121 = static_cast<uint32_t>(ctx.esp + 0x0000017cu);
    ctx.ecx = static_cast<uint32_t>(t121);
    // 0x0043e0a3: mov dword ptr [esp + 0x194], esi
    uint32_t t122 = static_cast<uint32_t>(ctx.esp + 0x00000194u);
    mem.w32(t122, ctx.esi);
    // 0x0043e0aa: mov dword ptr [esp + 0x190], ebx
    uint32_t t123 = static_cast<uint32_t>(ctx.esp + 0x00000190u);
    mem.w32(t123, ctx.ebx);
    // 0x0043e0b1: mov byte ptr [esp + 0x180], bl
    uint32_t t124 = static_cast<uint32_t>(ctx.esp + 0x00000180u);
    mem.w8(t124, recomp_detail::r8l(ctx.ebx));
    // 0x0043e0b8: call 0x407c10
    uint32_t t125 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t125);
    mem.w32(t125, 0x0043e0bdu);
    sub_00407c10(ctx, mem);
    // 0x0043e0bd: mov byte ptr [esp + 0x730], 0xd
    uint32_t t126 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t126, uint8_t{0x0du});
    // 0x0043e0c5: push 0xe
    uint32_t t127 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t127);
    mem.w32(t127, 0x0000000eu);
    // 0x0043e0c7: push 0x7b4184
    uint32_t t128 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t128);
    mem.w32(t128, 0x007b4184u);
    // 0x0043e0cc: lea ecx, [esp + 0x198]
    uint32_t t129 = static_cast<uint32_t>(ctx.esp + 0x00000198u);
    ctx.ecx = static_cast<uint32_t>(t129);
    // 0x0043e0d3: mov dword ptr [esp + 0x1b0], esi
    uint32_t t130 = static_cast<uint32_t>(ctx.esp + 0x000001b0u);
    mem.w32(t130, ctx.esi);
    // 0x0043e0da: mov dword ptr [esp + 0x1ac], ebx
    uint32_t t131 = static_cast<uint32_t>(ctx.esp + 0x000001acu);
    mem.w32(t131, ctx.ebx);
    // 0x0043e0e1: mov byte ptr [esp + 0x19c], bl
    uint32_t t132 = static_cast<uint32_t>(ctx.esp + 0x0000019cu);
    mem.w8(t132, recomp_detail::r8l(ctx.ebx));
    // 0x0043e0e8: call 0x407c10
    uint32_t t133 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t133);
    mem.w32(t133, 0x0043e0edu);
    sub_00407c10(ctx, mem);
    // 0x0043e0ed: mov byte ptr [esp + 0x730], 0xe
    uint32_t t134 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t134, uint8_t{0x0eu});
    // 0x0043e0f5: push 5
    uint32_t t135 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t135);
    mem.w32(t135, 0x00000005u);
    // 0x0043e0f7: push 0x536bd8
    uint32_t t136 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t136);
    mem.w32(t136, 0x00536bd8u);
    // 0x0043e0fc: lea ecx, [esp + 0x1b4]
    uint32_t t137 = static_cast<uint32_t>(ctx.esp + 0x000001b4u);
    ctx.ecx = static_cast<uint32_t>(t137);
    // 0x0043e103: mov dword ptr [esp + 0x1cc], esi
    uint32_t t138 = static_cast<uint32_t>(ctx.esp + 0x000001ccu);
    mem.w32(t138, ctx.esi);
    // 0x0043e10a: mov dword ptr [esp + 0x1c8], ebx
    uint32_t t139 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w32(t139, ctx.ebx);
    // 0x0043e111: mov byte ptr [esp + 0x1b8], bl
    uint32_t t140 = static_cast<uint32_t>(ctx.esp + 0x000001b8u);
    mem.w8(t140, recomp_detail::r8l(ctx.ebx));
    // 0x0043e118: call 0x407c10
    uint32_t t141 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t141);
    mem.w32(t141, 0x0043e11du);
    sub_00407c10(ctx, mem);
    // 0x0043e11d: mov byte ptr [esp + 0x730], 0xf
    uint32_t t142 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t142, uint8_t{0x0fu});
    // 0x0043e125: push 0xb
    uint32_t t143 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t143);
    mem.w32(t143, 0x0000000bu);
    // 0x0043e127: push 0x7b4193
    uint32_t t144 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t144);
    mem.w32(t144, 0x007b4193u);
    // 0x0043e12c: lea ecx, [esp + 0x1d0]
    uint32_t t145 = static_cast<uint32_t>(ctx.esp + 0x000001d0u);
    ctx.ecx = static_cast<uint32_t>(t145);
    // 0x0043e133: mov dword ptr [esp + 0x1e8], esi
    uint32_t t146 = static_cast<uint32_t>(ctx.esp + 0x000001e8u);
    mem.w32(t146, ctx.esi);
    // 0x0043e13a: mov dword ptr [esp + 0x1e4], ebx
    uint32_t t147 = static_cast<uint32_t>(ctx.esp + 0x000001e4u);
    mem.w32(t147, ctx.ebx);
    // 0x0043e141: mov byte ptr [esp + 0x1d4], bl
    uint32_t t148 = static_cast<uint32_t>(ctx.esp + 0x000001d4u);
    mem.w8(t148, recomp_detail::r8l(ctx.ebx));
    // 0x0043e148: call 0x407c10
    uint32_t t149 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t149);
    mem.w32(t149, 0x0043e14du);
    sub_00407c10(ctx, mem);
    // 0x0043e14d: mov byte ptr [esp + 0x730], 0x10
    uint32_t t150 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t150, uint8_t{0x10u});
    // 0x0043e155: push 6
    uint32_t t151 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t151);
    mem.w32(t151, 0x00000006u);
    // 0x0043e157: push 0x536bec
    uint32_t t152 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t152);
    mem.w32(t152, 0x00536becu);
    // 0x0043e15c: lea ecx, [esp + 0x1ec]
    uint32_t t153 = static_cast<uint32_t>(ctx.esp + 0x000001ecu);
    ctx.ecx = static_cast<uint32_t>(t153);
    // 0x0043e163: mov dword ptr [esp + 0x204], esi
    uint32_t t154 = static_cast<uint32_t>(ctx.esp + 0x00000204u);
    mem.w32(t154, ctx.esi);
    // 0x0043e16a: mov dword ptr [esp + 0x200], ebx
    uint32_t t155 = static_cast<uint32_t>(ctx.esp + 0x00000200u);
    mem.w32(t155, ctx.ebx);
    // 0x0043e171: mov byte ptr [esp + 0x1f0], bl
    uint32_t t156 = static_cast<uint32_t>(ctx.esp + 0x000001f0u);
    mem.w8(t156, recomp_detail::r8l(ctx.ebx));
    // 0x0043e178: call 0x407c10
    uint32_t t157 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t157);
    mem.w32(t157, 0x0043e17du);
    sub_00407c10(ctx, mem);
    // 0x0043e17d: mov byte ptr [esp + 0x730], 0x11
    uint32_t t158 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t158, uint8_t{0x11u});
    // 0x0043e185: mov dword ptr [esp + 0x218], esi
    uint32_t t159 = static_cast<uint32_t>(ctx.esp + 0x00000218u);
    mem.w32(t159, ctx.esi);
    // 0x0043e18c: mov dword ptr [esp + 0x214], ebx
    uint32_t t160 = static_cast<uint32_t>(ctx.esp + 0x00000214u);
    mem.w32(t160, ctx.ebx);
    // 0x0043e193: mov byte ptr [esp + 0x204], bl
    uint32_t t161 = static_cast<uint32_t>(ctx.esp + 0x00000204u);
    mem.w8(t161, recomp_detail::r8l(ctx.ebx));
    // 0x0043e19a: push 0xc
    uint32_t t162 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t162);
    mem.w32(t162, 0x0000000cu);
    // 0x0043e19c: push 0x7b419f
    uint32_t t163 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t163);
    mem.w32(t163, 0x007b419fu);
    // 0x0043e1a1: lea ecx, [esp + 0x208]
    uint32_t t164 = static_cast<uint32_t>(ctx.esp + 0x00000208u);
    ctx.ecx = static_cast<uint32_t>(t164);
    // 0x0043e1a8: call 0x407c10
    uint32_t t165 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t165);
    mem.w32(t165, 0x0043e1adu);
    sub_00407c10(ctx, mem);
    // 0x0043e1ad: mov byte ptr [esp + 0x730], 0x12
    uint32_t t166 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t166, uint8_t{0x12u});
    // 0x0043e1b5: push 7
    uint32_t t167 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t167);
    mem.w32(t167, 0x00000007u);
    // 0x0043e1b7: push 0x536c00
    uint32_t t168 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t168);
    mem.w32(t168, 0x00536c00u);
    // 0x0043e1bc: lea ecx, [esp + 0x224]
    uint32_t t169 = static_cast<uint32_t>(ctx.esp + 0x00000224u);
    ctx.ecx = static_cast<uint32_t>(t169);
    // 0x0043e1c3: mov dword ptr [esp + 0x23c], esi
    uint32_t t170 = static_cast<uint32_t>(ctx.esp + 0x0000023cu);
    mem.w32(t170, ctx.esi);
    // 0x0043e1ca: mov dword ptr [esp + 0x238], ebx
    uint32_t t171 = static_cast<uint32_t>(ctx.esp + 0x00000238u);
    mem.w32(t171, ctx.ebx);
    // 0x0043e1d1: mov byte ptr [esp + 0x228], bl
    uint32_t t172 = static_cast<uint32_t>(ctx.esp + 0x00000228u);
    mem.w8(t172, recomp_detail::r8l(ctx.ebx));
    // 0x0043e1d8: call 0x407c10
    uint32_t t173 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t173);
    mem.w32(t173, 0x0043e1ddu);
    sub_00407c10(ctx, mem);
    // 0x0043e1dd: mov byte ptr [esp + 0x730], 0x13
    uint32_t t174 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t174, uint8_t{0x13u});
    // 0x0043e1e5: push 9
    uint32_t t175 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t175);
    mem.w32(t175, 0x00000009u);
    // 0x0043e1e7: push 0x7b41ac
    uint32_t t176 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t176);
    mem.w32(t176, 0x007b41acu);
    // 0x0043e1ec: lea ecx, [esp + 0x240]
    uint32_t t177 = static_cast<uint32_t>(ctx.esp + 0x00000240u);
    ctx.ecx = static_cast<uint32_t>(t177);
    // 0x0043e1f3: mov dword ptr [esp + 0x258], esi
    uint32_t t178 = static_cast<uint32_t>(ctx.esp + 0x00000258u);
    mem.w32(t178, ctx.esi);
    // 0x0043e1fa: mov dword ptr [esp + 0x254], ebx
    uint32_t t179 = static_cast<uint32_t>(ctx.esp + 0x00000254u);
    mem.w32(t179, ctx.ebx);
    // 0x0043e201: mov byte ptr [esp + 0x244], bl
    uint32_t t180 = static_cast<uint32_t>(ctx.esp + 0x00000244u);
    mem.w8(t180, recomp_detail::r8l(ctx.ebx));
    // 0x0043e208: call 0x407c10
    uint32_t t181 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t181);
    mem.w32(t181, 0x0043e20du);
    sub_00407c10(ctx, mem);
    // 0x0043e20d: mov byte ptr [esp + 0x730], 0x14
    uint32_t t182 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t182, uint8_t{0x14u});
    // 0x0043e215: push 4
    uint32_t t183 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t183);
    mem.w32(t183, 0x00000004u);
    // 0x0043e217: push 0x536c18
    uint32_t t184 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t184);
    mem.w32(t184, 0x00536c18u);
    // 0x0043e21c: lea ecx, [esp + 0x25c]
    uint32_t t185 = static_cast<uint32_t>(ctx.esp + 0x0000025cu);
    ctx.ecx = static_cast<uint32_t>(t185);
    // 0x0043e223: mov dword ptr [esp + 0x274], esi
    uint32_t t186 = static_cast<uint32_t>(ctx.esp + 0x00000274u);
    mem.w32(t186, ctx.esi);
    // 0x0043e22a: mov dword ptr [esp + 0x270], ebx
    uint32_t t187 = static_cast<uint32_t>(ctx.esp + 0x00000270u);
    mem.w32(t187, ctx.ebx);
    // 0x0043e231: mov byte ptr [esp + 0x260], bl
    uint32_t t188 = static_cast<uint32_t>(ctx.esp + 0x00000260u);
    mem.w8(t188, recomp_detail::r8l(ctx.ebx));
    // 0x0043e238: call 0x407c10
    uint32_t t189 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t189);
    mem.w32(t189, 0x0043e23du);
    sub_00407c10(ctx, mem);
    // 0x0043e23d: mov byte ptr [esp + 0x730], 0x15
    uint32_t t190 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t190, uint8_t{0x15u});
    // 0x0043e245: push 0xd
    uint32_t t191 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t191);
    mem.w32(t191, 0x0000000du);
    // 0x0043e247: push 0x7b41b6
    uint32_t t192 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t192);
    mem.w32(t192, 0x007b41b6u);
    // 0x0043e24c: lea ecx, [esp + 0x278]
    uint32_t t193 = static_cast<uint32_t>(ctx.esp + 0x00000278u);
    ctx.ecx = static_cast<uint32_t>(t193);
    // 0x0043e253: mov dword ptr [esp + 0x290], esi
    uint32_t t194 = static_cast<uint32_t>(ctx.esp + 0x00000290u);
    mem.w32(t194, ctx.esi);
    // 0x0043e25a: mov dword ptr [esp + 0x28c], ebx
    uint32_t t195 = static_cast<uint32_t>(ctx.esp + 0x0000028cu);
    mem.w32(t195, ctx.ebx);
    // 0x0043e261: mov byte ptr [esp + 0x27c], bl
    uint32_t t196 = static_cast<uint32_t>(ctx.esp + 0x0000027cu);
    mem.w8(t196, recomp_detail::r8l(ctx.ebx));
    // 0x0043e268: call 0x407c10
    uint32_t t197 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t197);
    mem.w32(t197, 0x0043e26du);
    sub_00407c10(ctx, mem);
    // 0x0043e26d: mov byte ptr [esp + 0x730], 0x16
    uint32_t t198 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t198, uint8_t{0x16u});
    // 0x0043e275: push 6
    uint32_t t199 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t199);
    mem.w32(t199, 0x00000006u);
    // 0x0043e277: push 0x536c30
    uint32_t t200 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t200);
    mem.w32(t200, 0x00536c30u);
    // 0x0043e27c: lea ecx, [esp + 0x294]
    uint32_t t201 = static_cast<uint32_t>(ctx.esp + 0x00000294u);
    ctx.ecx = static_cast<uint32_t>(t201);
    // 0x0043e283: mov dword ptr [esp + 0x2ac], esi
    uint32_t t202 = static_cast<uint32_t>(ctx.esp + 0x000002acu);
    mem.w32(t202, ctx.esi);
    // 0x0043e28a: mov dword ptr [esp + 0x2a8], ebx
    uint32_t t203 = static_cast<uint32_t>(ctx.esp + 0x000002a8u);
    mem.w32(t203, ctx.ebx);
    // 0x0043e291: mov byte ptr [esp + 0x298], bl
    uint32_t t204 = static_cast<uint32_t>(ctx.esp + 0x00000298u);
    mem.w8(t204, recomp_detail::r8l(ctx.ebx));
    // 0x0043e298: call 0x407c10
    uint32_t t205 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t205);
    mem.w32(t205, 0x0043e29du);
    sub_00407c10(ctx, mem);
    // 0x0043e29d: mov byte ptr [esp + 0x730], 0x17
    uint32_t t206 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t206, uint8_t{0x17u});
    // 0x0043e2a5: push 0xc
    uint32_t t207 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t207);
    mem.w32(t207, 0x0000000cu);
    // 0x0043e2a7: push 0x7b41c4
    uint32_t t208 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t208);
    mem.w32(t208, 0x007b41c4u);
    // 0x0043e2ac: lea ecx, [esp + 0x2b0]
    uint32_t t209 = static_cast<uint32_t>(ctx.esp + 0x000002b0u);
    ctx.ecx = static_cast<uint32_t>(t209);
    // 0x0043e2b3: mov dword ptr [esp + 0x2c8], esi
    uint32_t t210 = static_cast<uint32_t>(ctx.esp + 0x000002c8u);
    mem.w32(t210, ctx.esi);
    // 0x0043e2ba: mov dword ptr [esp + 0x2c4], ebx
    uint32_t t211 = static_cast<uint32_t>(ctx.esp + 0x000002c4u);
    mem.w32(t211, ctx.ebx);
    // 0x0043e2c1: mov byte ptr [esp + 0x2b4], bl
    uint32_t t212 = static_cast<uint32_t>(ctx.esp + 0x000002b4u);
    mem.w8(t212, recomp_detail::r8l(ctx.ebx));
    // 0x0043e2c8: call 0x407c10
    uint32_t t213 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t213);
    mem.w32(t213, 0x0043e2cdu);
    sub_00407c10(ctx, mem);
    // 0x0043e2cd: mov byte ptr [esp + 0x730], 0x18
    uint32_t t214 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t214, uint8_t{0x18u});
    // 0x0043e2d5: push 4
    uint32_t t215 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t215);
    mem.w32(t215, 0x00000004u);
    // 0x0043e2d7: push 0x536c48
    uint32_t t216 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t216);
    mem.w32(t216, 0x00536c48u);
    // 0x0043e2dc: lea ecx, [esp + 0x2cc]
    uint32_t t217 = static_cast<uint32_t>(ctx.esp + 0x000002ccu);
    ctx.ecx = static_cast<uint32_t>(t217);
    // 0x0043e2e3: mov dword ptr [esp + 0x2e4], esi
    uint32_t t218 = static_cast<uint32_t>(ctx.esp + 0x000002e4u);
    mem.w32(t218, ctx.esi);
    // 0x0043e2ea: mov dword ptr [esp + 0x2e0], ebx
    uint32_t t219 = static_cast<uint32_t>(ctx.esp + 0x000002e0u);
    mem.w32(t219, ctx.ebx);
    // 0x0043e2f1: mov byte ptr [esp + 0x2d0], bl
    uint32_t t220 = static_cast<uint32_t>(ctx.esp + 0x000002d0u);
    mem.w8(t220, recomp_detail::r8l(ctx.ebx));
    // 0x0043e2f8: call 0x407c10
    uint32_t t221 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t221);
    mem.w32(t221, 0x0043e2fdu);
    sub_00407c10(ctx, mem);
    // 0x0043e2fd: mov byte ptr [esp + 0x730], 0x19
    uint32_t t222 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t222, uint8_t{0x19u});
    // 0x0043e305: push 0xf
    uint32_t t223 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t223);
    mem.w32(t223, 0x0000000fu);
    // 0x0043e307: push 0x7b41d1
    uint32_t t224 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t224);
    mem.w32(t224, 0x007b41d1u);
    // 0x0043e30c: lea ecx, [esp + 0x2e8]
    uint32_t t225 = static_cast<uint32_t>(ctx.esp + 0x000002e8u);
    ctx.ecx = static_cast<uint32_t>(t225);
    // 0x0043e313: mov dword ptr [esp + 0x300], esi
    uint32_t t226 = static_cast<uint32_t>(ctx.esp + 0x00000300u);
    mem.w32(t226, ctx.esi);
    // 0x0043e31a: mov dword ptr [esp + 0x2fc], ebx
    uint32_t t227 = static_cast<uint32_t>(ctx.esp + 0x000002fcu);
    mem.w32(t227, ctx.ebx);
    // 0x0043e321: mov byte ptr [esp + 0x2ec], bl
    uint32_t t228 = static_cast<uint32_t>(ctx.esp + 0x000002ecu);
    mem.w8(t228, recomp_detail::r8l(ctx.ebx));
    // 0x0043e328: call 0x407c10
    uint32_t t229 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t229);
    mem.w32(t229, 0x0043e32du);
    sub_00407c10(ctx, mem);
    // 0x0043e32d: mov byte ptr [esp + 0x730], 0x1a
    uint32_t t230 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t230, uint8_t{0x1au});
    // 0x0043e335: mov dword ptr [esp + 0x314], esi
    uint32_t t231 = static_cast<uint32_t>(ctx.esp + 0x00000314u);
    mem.w32(t231, ctx.esi);
    // 0x0043e33c: mov dword ptr [esp + 0x310], ebx
    uint32_t t232 = static_cast<uint32_t>(ctx.esp + 0x00000310u);
    mem.w32(t232, ctx.ebx);
    // 0x0043e343: mov byte ptr [esp + 0x300], bl
    uint32_t t233 = static_cast<uint32_t>(ctx.esp + 0x00000300u);
    mem.w8(t233, recomp_detail::r8l(ctx.ebx));
    // 0x0043e34a: push 8
    uint32_t t234 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t234);
    mem.w32(t234, 0x00000008u);
    // 0x0043e34c: push 0x536c64
    uint32_t t235 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t235);
    mem.w32(t235, 0x00536c64u);
    // 0x0043e351: lea ecx, [esp + 0x304]
    uint32_t t236 = static_cast<uint32_t>(ctx.esp + 0x00000304u);
    ctx.ecx = static_cast<uint32_t>(t236);
    // 0x0043e358: call 0x407c10
    uint32_t t237 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t237);
    mem.w32(t237, 0x0043e35du);
    sub_00407c10(ctx, mem);
    // 0x0043e35d: mov byte ptr [esp + 0x730], 0x1b
    uint32_t t238 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t238, uint8_t{0x1bu});
    // 0x0043e365: push 0xd
    uint32_t t239 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t239);
    mem.w32(t239, 0x0000000du);
    // 0x0043e367: push 0x7b41e1
    uint32_t t240 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t240);
    mem.w32(t240, 0x007b41e1u);
    // 0x0043e36c: lea ecx, [esp + 0x320]
    uint32_t t241 = static_cast<uint32_t>(ctx.esp + 0x00000320u);
    ctx.ecx = static_cast<uint32_t>(t241);
    // 0x0043e373: mov dword ptr [esp + 0x338], esi
    uint32_t t242 = static_cast<uint32_t>(ctx.esp + 0x00000338u);
    mem.w32(t242, ctx.esi);
    // 0x0043e37a: mov dword ptr [esp + 0x334], ebx
    uint32_t t243 = static_cast<uint32_t>(ctx.esp + 0x00000334u);
    mem.w32(t243, ctx.ebx);
    // 0x0043e381: mov byte ptr [esp + 0x324], bl
    uint32_t t244 = static_cast<uint32_t>(ctx.esp + 0x00000324u);
    mem.w8(t244, recomp_detail::r8l(ctx.ebx));
    // 0x0043e388: call 0x407c10
    uint32_t t245 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t245);
    mem.w32(t245, 0x0043e38du);
    sub_00407c10(ctx, mem);
    // 0x0043e38d: mov byte ptr [esp + 0x730], 0x1c
    uint32_t t246 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t246, uint8_t{0x1cu});
    // 0x0043e395: push 7
    uint32_t t247 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t247);
    mem.w32(t247, 0x00000007u);
    // 0x0043e397: push 0x536c7c
    uint32_t t248 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t248);
    mem.w32(t248, 0x00536c7cu);
    // 0x0043e39c: lea ecx, [esp + 0x33c]
    uint32_t t249 = static_cast<uint32_t>(ctx.esp + 0x0000033cu);
    ctx.ecx = static_cast<uint32_t>(t249);
    // 0x0043e3a3: mov dword ptr [esp + 0x354], esi
    uint32_t t250 = static_cast<uint32_t>(ctx.esp + 0x00000354u);
    mem.w32(t250, ctx.esi);
    // 0x0043e3aa: mov dword ptr [esp + 0x350], ebx
    uint32_t t251 = static_cast<uint32_t>(ctx.esp + 0x00000350u);
    mem.w32(t251, ctx.ebx);
    // 0x0043e3b1: mov byte ptr [esp + 0x340], bl
    uint32_t t252 = static_cast<uint32_t>(ctx.esp + 0x00000340u);
    mem.w8(t252, recomp_detail::r8l(ctx.ebx));
    // 0x0043e3b8: call 0x407c10
    uint32_t t253 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t253);
    mem.w32(t253, 0x0043e3bdu);
    sub_00407c10(ctx, mem);
    // 0x0043e3bd: mov byte ptr [esp + 0x730], 0x1d
    uint32_t t254 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t254, uint8_t{0x1du});
    // 0x0043e3c5: push 0xa
    uint32_t t255 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t255);
    mem.w32(t255, 0x0000000au);
    // 0x0043e3c7: push 0x7b41ef
    uint32_t t256 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t256);
    mem.w32(t256, 0x007b41efu);
    // 0x0043e3cc: lea ecx, [esp + 0x358]
    uint32_t t257 = static_cast<uint32_t>(ctx.esp + 0x00000358u);
    ctx.ecx = static_cast<uint32_t>(t257);
    // 0x0043e3d3: mov dword ptr [esp + 0x370], esi
    uint32_t t258 = static_cast<uint32_t>(ctx.esp + 0x00000370u);
    mem.w32(t258, ctx.esi);
    // 0x0043e3da: mov dword ptr [esp + 0x36c], ebx
    uint32_t t259 = static_cast<uint32_t>(ctx.esp + 0x0000036cu);
    mem.w32(t259, ctx.ebx);
    // 0x0043e3e1: mov byte ptr [esp + 0x35c], bl
    uint32_t t260 = static_cast<uint32_t>(ctx.esp + 0x0000035cu);
    mem.w8(t260, recomp_detail::r8l(ctx.ebx));
    // 0x0043e3e8: call 0x407c10
    uint32_t t261 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t261);
    mem.w32(t261, 0x0043e3edu);
    sub_00407c10(ctx, mem);
    // 0x0043e3ed: mov byte ptr [esp + 0x730], 0x1e
    uint32_t t262 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t262, uint8_t{0x1eu});
    // 0x0043e3f5: push 6
    uint32_t t263 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t263);
    mem.w32(t263, 0x00000006u);
    // 0x0043e3f7: push 0x536c90
    uint32_t t264 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t264);
    mem.w32(t264, 0x00536c90u);
    // 0x0043e3fc: lea ecx, [esp + 0x374]
    uint32_t t265 = static_cast<uint32_t>(ctx.esp + 0x00000374u);
    ctx.ecx = static_cast<uint32_t>(t265);
    // 0x0043e403: mov dword ptr [esp + 0x38c], esi
    uint32_t t266 = static_cast<uint32_t>(ctx.esp + 0x0000038cu);
    mem.w32(t266, ctx.esi);
    // 0x0043e40a: mov dword ptr [esp + 0x388], ebx
    uint32_t t267 = static_cast<uint32_t>(ctx.esp + 0x00000388u);
    mem.w32(t267, ctx.ebx);
    // 0x0043e411: mov byte ptr [esp + 0x378], bl
    uint32_t t268 = static_cast<uint32_t>(ctx.esp + 0x00000378u);
    mem.w8(t268, recomp_detail::r8l(ctx.ebx));
    // 0x0043e418: call 0x407c10
    uint32_t t269 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t269);
    mem.w32(t269, 0x0043e41du);
    sub_00407c10(ctx, mem);
    // 0x0043e41d: mov byte ptr [esp + 0x730], 0x1f
    uint32_t t270 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t270, uint8_t{0x1fu});
    // 0x0043e425: push 0xc
    uint32_t t271 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t271);
    mem.w32(t271, 0x0000000cu);
    // 0x0043e427: push 0x7b41fa
    uint32_t t272 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t272);
    mem.w32(t272, 0x007b41fau);
    // 0x0043e42c: lea ecx, [esp + 0x390]
    uint32_t t273 = static_cast<uint32_t>(ctx.esp + 0x00000390u);
    ctx.ecx = static_cast<uint32_t>(t273);
    // 0x0043e433: mov dword ptr [esp + 0x3a8], esi
    uint32_t t274 = static_cast<uint32_t>(ctx.esp + 0x000003a8u);
    mem.w32(t274, ctx.esi);
    // 0x0043e43a: mov dword ptr [esp + 0x3a4], ebx
    uint32_t t275 = static_cast<uint32_t>(ctx.esp + 0x000003a4u);
    mem.w32(t275, ctx.ebx);
    // 0x0043e441: mov byte ptr [esp + 0x394], bl
    uint32_t t276 = static_cast<uint32_t>(ctx.esp + 0x00000394u);
    mem.w8(t276, recomp_detail::r8l(ctx.ebx));
    // 0x0043e448: call 0x407c10
    uint32_t t277 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t277);
    mem.w32(t277, 0x0043e44du);
    sub_00407c10(ctx, mem);
    // 0x0043e44d: mov byte ptr [esp + 0x730], 0x20
    uint32_t t278 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t278, uint8_t{0x20u});
    // 0x0043e455: push 7
    uint32_t t279 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t279);
    mem.w32(t279, 0x00000007u);
    // 0x0043e457: push 0x536ca4
    uint32_t t280 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t280);
    mem.w32(t280, 0x00536ca4u);
    // 0x0043e45c: lea ecx, [esp + 0x3ac]
    uint32_t t281 = static_cast<uint32_t>(ctx.esp + 0x000003acu);
    ctx.ecx = static_cast<uint32_t>(t281);
    // 0x0043e463: mov dword ptr [esp + 0x3c4], esi
    uint32_t t282 = static_cast<uint32_t>(ctx.esp + 0x000003c4u);
    mem.w32(t282, ctx.esi);
    // 0x0043e46a: mov dword ptr [esp + 0x3c0], ebx
    uint32_t t283 = static_cast<uint32_t>(ctx.esp + 0x000003c0u);
    mem.w32(t283, ctx.ebx);
    // 0x0043e471: mov byte ptr [esp + 0x3b0], bl
    uint32_t t284 = static_cast<uint32_t>(ctx.esp + 0x000003b0u);
    mem.w8(t284, recomp_detail::r8l(ctx.ebx));
    // 0x0043e478: call 0x407c10
    uint32_t t285 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t285);
    mem.w32(t285, 0x0043e47du);
    sub_00407c10(ctx, mem);
    // 0x0043e47d: mov byte ptr [esp + 0x730], 0x21
    uint32_t t286 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t286, uint8_t{0x21u});
    // 0x0043e485: push 0x10
    uint32_t t287 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t287);
    mem.w32(t287, 0x00000010u);
    // 0x0043e487: push 0x7b4207
    uint32_t t288 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t288);
    mem.w32(t288, 0x007b4207u);
    // 0x0043e48c: lea ecx, [esp + 0x3c8]
    uint32_t t289 = static_cast<uint32_t>(ctx.esp + 0x000003c8u);
    ctx.ecx = static_cast<uint32_t>(t289);
    // 0x0043e493: mov dword ptr [esp + 0x3e0], esi
    uint32_t t290 = static_cast<uint32_t>(ctx.esp + 0x000003e0u);
    mem.w32(t290, ctx.esi);
    // 0x0043e49a: mov dword ptr [esp + 0x3dc], ebx
    uint32_t t291 = static_cast<uint32_t>(ctx.esp + 0x000003dcu);
    mem.w32(t291, ctx.ebx);
    // 0x0043e4a1: mov byte ptr [esp + 0x3cc], bl
    uint32_t t292 = static_cast<uint32_t>(ctx.esp + 0x000003ccu);
    mem.w8(t292, recomp_detail::r8l(ctx.ebx));
    // 0x0043e4a8: call 0x407c10
    uint32_t t293 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t293);
    mem.w32(t293, 0x0043e4adu);
    sub_00407c10(ctx, mem);
    // 0x0043e4ad: mov byte ptr [esp + 0x730], 0x22
    uint32_t t294 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t294, uint8_t{0x22u});
    // 0x0043e4b5: push 3
    uint32_t t295 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t295);
    mem.w32(t295, 0x00000003u);
    // 0x0043e4b7: push 0x536cb8
    uint32_t t296 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t296);
    mem.w32(t296, 0x00536cb8u);
    // 0x0043e4bc: lea ecx, [esp + 0x3e4]
    uint32_t t297 = static_cast<uint32_t>(ctx.esp + 0x000003e4u);
    ctx.ecx = static_cast<uint32_t>(t297);
    // 0x0043e4c3: mov dword ptr [esp + 0x3fc], esi
    uint32_t t298 = static_cast<uint32_t>(ctx.esp + 0x000003fcu);
    mem.w32(t298, ctx.esi);
    // 0x0043e4ca: mov dword ptr [esp + 0x3f8], ebx
    uint32_t t299 = static_cast<uint32_t>(ctx.esp + 0x000003f8u);
    mem.w32(t299, ctx.ebx);
    // 0x0043e4d1: mov byte ptr [esp + 0x3e8], bl
    uint32_t t300 = static_cast<uint32_t>(ctx.esp + 0x000003e8u);
    mem.w8(t300, recomp_detail::r8l(ctx.ebx));
    // 0x0043e4d8: call 0x407c10
    uint32_t t301 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t301);
    mem.w32(t301, 0x0043e4ddu);
    sub_00407c10(ctx, mem);
    // 0x0043e4dd: mov byte ptr [esp + 0x730], 0x23
    uint32_t t302 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t302, uint8_t{0x23u});
    // 0x0043e4e5: mov dword ptr [esp + 0x410], esi
    uint32_t t303 = static_cast<uint32_t>(ctx.esp + 0x00000410u);
    mem.w32(t303, ctx.esi);
    // 0x0043e4ec: mov dword ptr [esp + 0x40c], ebx
    uint32_t t304 = static_cast<uint32_t>(ctx.esp + 0x0000040cu);
    mem.w32(t304, ctx.ebx);
    // 0x0043e4f3: mov byte ptr [esp + 0x3fc], bl
    uint32_t t305 = static_cast<uint32_t>(ctx.esp + 0x000003fcu);
    mem.w8(t305, recomp_detail::r8l(ctx.ebx));
    // 0x0043e4fa: push 3
    uint32_t t306 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t306);
    mem.w32(t306, 0x00000003u);
    // 0x0043e4fc: push 0x7b4218
    uint32_t t307 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t307);
    mem.w32(t307, 0x007b4218u);
    // 0x0043e501: lea ecx, [esp + 0x400]
    uint32_t t308 = static_cast<uint32_t>(ctx.esp + 0x00000400u);
    ctx.ecx = static_cast<uint32_t>(t308);
    // 0x0043e508: call 0x407c10
    uint32_t t309 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t309);
    mem.w32(t309, 0x0043e50du);
    sub_00407c10(ctx, mem);
    // 0x0043e50d: mov byte ptr [esp + 0x730], 0x24
    uint32_t t310 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t310, uint8_t{0x24u});
    // 0x0043e515: push 6
    uint32_t t311 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t311);
    mem.w32(t311, 0x00000006u);
    // 0x0043e517: push 0x536cc4
    uint32_t t312 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t312);
    mem.w32(t312, 0x00536cc4u);
    // 0x0043e51c: lea ecx, [esp + 0x41c]
    uint32_t t313 = static_cast<uint32_t>(ctx.esp + 0x0000041cu);
    ctx.ecx = static_cast<uint32_t>(t313);
    // 0x0043e523: mov dword ptr [esp + 0x434], esi
    uint32_t t314 = static_cast<uint32_t>(ctx.esp + 0x00000434u);
    mem.w32(t314, ctx.esi);
    // 0x0043e52a: mov dword ptr [esp + 0x430], ebx
    uint32_t t315 = static_cast<uint32_t>(ctx.esp + 0x00000430u);
    mem.w32(t315, ctx.ebx);
    // 0x0043e531: mov byte ptr [esp + 0x420], bl
    uint32_t t316 = static_cast<uint32_t>(ctx.esp + 0x00000420u);
    mem.w8(t316, recomp_detail::r8l(ctx.ebx));
    // 0x0043e538: call 0x407c10
    uint32_t t317 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t317);
    mem.w32(t317, 0x0043e53du);
    sub_00407c10(ctx, mem);
    // 0x0043e53d: mov byte ptr [esp + 0x730], 0x25
    uint32_t t318 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t318, uint8_t{0x25u});
    // 0x0043e545: push 0x10
    uint32_t t319 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t319);
    mem.w32(t319, 0x00000010u);
    // 0x0043e547: push 0x7b421c
    uint32_t t320 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t320);
    mem.w32(t320, 0x007b421cu);
    // 0x0043e54c: lea ecx, [esp + 0x438]
    uint32_t t321 = static_cast<uint32_t>(ctx.esp + 0x00000438u);
    ctx.ecx = static_cast<uint32_t>(t321);
    // 0x0043e553: mov dword ptr [esp + 0x450], esi
    uint32_t t322 = static_cast<uint32_t>(ctx.esp + 0x00000450u);
    mem.w32(t322, ctx.esi);
    // 0x0043e55a: mov dword ptr [esp + 0x44c], ebx
    uint32_t t323 = static_cast<uint32_t>(ctx.esp + 0x0000044cu);
    mem.w32(t323, ctx.ebx);
    // 0x0043e561: mov byte ptr [esp + 0x43c], bl
    uint32_t t324 = static_cast<uint32_t>(ctx.esp + 0x0000043cu);
    mem.w8(t324, recomp_detail::r8l(ctx.ebx));
    // 0x0043e568: call 0x407c10
    uint32_t t325 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t325);
    mem.w32(t325, 0x0043e56du);
    sub_00407c10(ctx, mem);
    // 0x0043e56d: mov byte ptr [esp + 0x730], 0x26
    uint32_t t326 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t326, uint8_t{0x26u});
    // 0x0043e575: push 4
    uint32_t t327 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t327);
    mem.w32(t327, 0x00000004u);
    // 0x0043e577: push 0x536cdc
    uint32_t t328 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t328);
    mem.w32(t328, 0x00536cdcu);
    // 0x0043e57c: lea ecx, [esp + 0x454]
    uint32_t t329 = static_cast<uint32_t>(ctx.esp + 0x00000454u);
    ctx.ecx = static_cast<uint32_t>(t329);
    // 0x0043e583: mov dword ptr [esp + 0x46c], esi
    uint32_t t330 = static_cast<uint32_t>(ctx.esp + 0x0000046cu);
    mem.w32(t330, ctx.esi);
    // 0x0043e58a: mov dword ptr [esp + 0x468], ebx
    uint32_t t331 = static_cast<uint32_t>(ctx.esp + 0x00000468u);
    mem.w32(t331, ctx.ebx);
    // 0x0043e591: mov byte ptr [esp + 0x458], bl
    uint32_t t332 = static_cast<uint32_t>(ctx.esp + 0x00000458u);
    mem.w8(t332, recomp_detail::r8l(ctx.ebx));
    // 0x0043e598: call 0x407c10
    uint32_t t333 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t333);
    mem.w32(t333, 0x0043e59du);
    sub_00407c10(ctx, mem);
    // 0x0043e59d: mov byte ptr [esp + 0x730], 0x27
    uint32_t t334 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t334, uint8_t{0x27u});
    // 0x0043e5a5: push 8
    uint32_t t335 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t335);
    mem.w32(t335, 0x00000008u);
    // 0x0043e5a7: push 0x7b422d
    uint32_t t336 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t336);
    mem.w32(t336, 0x007b422du);
    // 0x0043e5ac: lea ecx, [esp + 0x470]
    uint32_t t337 = static_cast<uint32_t>(ctx.esp + 0x00000470u);
    ctx.ecx = static_cast<uint32_t>(t337);
    // 0x0043e5b3: mov dword ptr [esp + 0x488], esi
    uint32_t t338 = static_cast<uint32_t>(ctx.esp + 0x00000488u);
    mem.w32(t338, ctx.esi);
    // 0x0043e5ba: mov dword ptr [esp + 0x484], ebx
    uint32_t t339 = static_cast<uint32_t>(ctx.esp + 0x00000484u);
    mem.w32(t339, ctx.ebx);
    // 0x0043e5c1: mov byte ptr [esp + 0x474], bl
    uint32_t t340 = static_cast<uint32_t>(ctx.esp + 0x00000474u);
    mem.w8(t340, recomp_detail::r8l(ctx.ebx));
    // 0x0043e5c8: call 0x407c10
    uint32_t t341 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t341);
    mem.w32(t341, 0x0043e5cdu);
    sub_00407c10(ctx, mem);
    // 0x0043e5cd: mov byte ptr [esp + 0x730], 0x28
    uint32_t t342 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t342, uint8_t{0x28u});
    // 0x0043e5d5: push 4
    uint32_t t343 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t343);
    mem.w32(t343, 0x00000004u);
    // 0x0043e5d7: push 0x536cf0
    uint32_t t344 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t344);
    mem.w32(t344, 0x00536cf0u);
    // 0x0043e5dc: lea ecx, [esp + 0x48c]
    uint32_t t345 = static_cast<uint32_t>(ctx.esp + 0x0000048cu);
    ctx.ecx = static_cast<uint32_t>(t345);
    // 0x0043e5e3: mov dword ptr [esp + 0x4a4], esi
    uint32_t t346 = static_cast<uint32_t>(ctx.esp + 0x000004a4u);
    mem.w32(t346, ctx.esi);
    // 0x0043e5ea: mov dword ptr [esp + 0x4a0], ebx
    uint32_t t347 = static_cast<uint32_t>(ctx.esp + 0x000004a0u);
    mem.w32(t347, ctx.ebx);
    // 0x0043e5f1: mov byte ptr [esp + 0x490], bl
    uint32_t t348 = static_cast<uint32_t>(ctx.esp + 0x00000490u);
    mem.w8(t348, recomp_detail::r8l(ctx.ebx));
    // 0x0043e5f8: call 0x407c10
    uint32_t t349 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t349);
    mem.w32(t349, 0x0043e5fdu);
    sub_00407c10(ctx, mem);
    // 0x0043e5fd: mov byte ptr [esp + 0x730], 0x29
    uint32_t t350 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t350, uint8_t{0x29u});
    // 0x0043e605: push 0xb
    uint32_t t351 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t351);
    mem.w32(t351, 0x0000000bu);
    // 0x0043e607: push 0x7b4236
    uint32_t t352 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t352);
    mem.w32(t352, 0x007b4236u);
    // 0x0043e60c: lea ecx, [esp + 0x4a8]
    uint32_t t353 = static_cast<uint32_t>(ctx.esp + 0x000004a8u);
    ctx.ecx = static_cast<uint32_t>(t353);
    // 0x0043e613: mov dword ptr [esp + 0x4c0], esi
    uint32_t t354 = static_cast<uint32_t>(ctx.esp + 0x000004c0u);
    mem.w32(t354, ctx.esi);
    // 0x0043e61a: mov dword ptr [esp + 0x4bc], ebx
    uint32_t t355 = static_cast<uint32_t>(ctx.esp + 0x000004bcu);
    mem.w32(t355, ctx.ebx);
    // 0x0043e621: mov byte ptr [esp + 0x4ac], bl
    uint32_t t356 = static_cast<uint32_t>(ctx.esp + 0x000004acu);
    mem.w8(t356, recomp_detail::r8l(ctx.ebx));
    // 0x0043e628: call 0x407c10
    uint32_t t357 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t357);
    mem.w32(t357, 0x0043e62du);
    sub_00407c10(ctx, mem);
    // 0x0043e62d: push 0x536d04
    uint32_t t358 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t358);
    mem.w32(t358, 0x00536d04u);
    // 0x0043e632: lea ecx, [esp + 0x4c0]
    uint32_t t359 = static_cast<uint32_t>(ctx.esp + 0x000004c0u);
    ctx.ecx = static_cast<uint32_t>(t359);
    // 0x0043e639: mov byte ptr [esp + 0x734], 0x2a
    uint32_t t360 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t360, uint8_t{0x2au});
    // 0x0043e641: call 0x407810
    uint32_t t361 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t361);
    mem.w32(t361, 0x0043e646u);
    sub_00407810(ctx, mem);
    // 0x0043e646: push 0x7b4242
    uint32_t t362 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t362);
    mem.w32(t362, 0x007b4242u);
    // 0x0043e64b: lea ecx, [esp + 0x4dc]
    uint32_t t363 = static_cast<uint32_t>(ctx.esp + 0x000004dcu);
    ctx.ecx = static_cast<uint32_t>(t363);
    // 0x0043e652: mov byte ptr [esp + 0x734], 0x2b
    uint32_t t364 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t364, uint8_t{0x2bu});
    // 0x0043e65a: call 0x407810
    uint32_t t365 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t365);
    mem.w32(t365, 0x0043e65fu);
    sub_00407810(ctx, mem);
    // 0x0043e65f: push 0x536d14
    uint32_t t366 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t366);
    mem.w32(t366, 0x00536d14u);
    // 0x0043e664: lea ecx, [esp + 0x4f8]
    uint32_t t367 = static_cast<uint32_t>(ctx.esp + 0x000004f8u);
    ctx.ecx = static_cast<uint32_t>(t367);
    // 0x0043e66b: mov byte ptr [esp + 0x734], 0x2c
    uint32_t t368 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t368, uint8_t{0x2cu});
    // 0x0043e673: call 0x407810
    uint32_t t369 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t369);
    mem.w32(t369, 0x0043e678u);
    sub_00407810(ctx, mem);
    // 0x0043e678: push 0x7b424c
    uint32_t t370 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t370);
    mem.w32(t370, 0x007b424cu);
    // 0x0043e67d: lea ecx, [esp + 0x514]
    uint32_t t371 = static_cast<uint32_t>(ctx.esp + 0x00000514u);
    ctx.ecx = static_cast<uint32_t>(t371);
    // 0x0043e684: mov byte ptr [esp + 0x734], 0x2d
    uint32_t t372 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t372, uint8_t{0x2du});
    // 0x0043e68c: call 0x407810
    uint32_t t373 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t373);
    mem.w32(t373, 0x0043e691u);
    sub_00407810(ctx, mem);
    // 0x0043e691: mov byte ptr [esp + 0x730], 0x2e
    uint32_t t374 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w8(t374, uint8_t{0x2eu});
    // 0x0043e699: push 0x536d30
    uint32_t t375 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t375);
    mem.w32(t375, 0x00536d30u);
    // 0x0043e69e: lea ecx, [esp + 0x530]
    uint32_t t376 = static_cast<uint32_t>(ctx.esp + 0x00000530u);
    ctx.ecx = static_cast<uint32_t>(t376);
    // 0x0043e6a5: call 0x407810
    uint32_t t377 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t377);
    mem.w32(t377, 0x0043e6aau);
    sub_00407810(ctx, mem);
    // 0x0043e6aa: push 0x7b425b
    uint32_t t378 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t378);
    mem.w32(t378, 0x007b425bu);
    // 0x0043e6af: lea ecx, [esp + 0x54c]
    uint32_t t379 = static_cast<uint32_t>(ctx.esp + 0x0000054cu);
    ctx.ecx = static_cast<uint32_t>(t379);
    // 0x0043e6b6: mov byte ptr [esp + 0x734], 0x2f
    uint32_t t380 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t380, uint8_t{0x2fu});
    // 0x0043e6be: call 0x407810
    uint32_t t381 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t381);
    mem.w32(t381, 0x0043e6c3u);
    sub_00407810(ctx, mem);
    // 0x0043e6c3: push 0x536d44
    uint32_t t382 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t382);
    mem.w32(t382, 0x00536d44u);
    // 0x0043e6c8: lea ecx, [esp + 0x568]
    uint32_t t383 = static_cast<uint32_t>(ctx.esp + 0x00000568u);
    ctx.ecx = static_cast<uint32_t>(t383);
    // 0x0043e6cf: mov byte ptr [esp + 0x734], 0x30
    uint32_t t384 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t384, uint8_t{0x30u});
    // 0x0043e6d7: call 0x407810
    uint32_t t385 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t385);
    mem.w32(t385, 0x0043e6dcu);
    sub_00407810(ctx, mem);
    // 0x0043e6dc: push 0x7b4269
    uint32_t t386 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t386);
    mem.w32(t386, 0x007b4269u);
    // 0x0043e6e1: lea ecx, [esp + 0x584]
    uint32_t t387 = static_cast<uint32_t>(ctx.esp + 0x00000584u);
    ctx.ecx = static_cast<uint32_t>(t387);
    // 0x0043e6e8: mov byte ptr [esp + 0x734], 0x31
    uint32_t t388 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t388, uint8_t{0x31u});
    // 0x0043e6f0: call 0x407810
    uint32_t t389 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t389);
    mem.w32(t389, 0x0043e6f5u);
    sub_00407810(ctx, mem);
    // 0x0043e6f5: push 0x536d60
    uint32_t t390 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t390);
    mem.w32(t390, 0x00536d60u);
    // 0x0043e6fa: lea ecx, [esp + 0x5a0]
    uint32_t t391 = static_cast<uint32_t>(ctx.esp + 0x000005a0u);
    ctx.ecx = static_cast<uint32_t>(t391);
    // 0x0043e701: mov byte ptr [esp + 0x734], 0x32
    uint32_t t392 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t392, uint8_t{0x32u});
    // 0x0043e709: call 0x407810
    uint32_t t393 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t393);
    mem.w32(t393, 0x0043e70eu);
    sub_00407810(ctx, mem);
    // 0x0043e70e: push 0x7b4279
    uint32_t t394 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t394);
    mem.w32(t394, 0x007b4279u);
    // 0x0043e713: lea ecx, [esp + 0x5bc]
    uint32_t t395 = static_cast<uint32_t>(ctx.esp + 0x000005bcu);
    ctx.ecx = static_cast<uint32_t>(t395);
    // 0x0043e71a: mov byte ptr [esp + 0x734], 0x33
    uint32_t t396 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t396, uint8_t{0x33u});
    // 0x0043e722: call 0x407810
    uint32_t t397 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t397);
    mem.w32(t397, 0x0043e727u);
    sub_00407810(ctx, mem);
    // 0x0043e727: push 0x536d78
    uint32_t t398 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t398);
    mem.w32(t398, 0x00536d78u);
    // 0x0043e72c: lea ecx, [esp + 0x5d8]
    uint32_t t399 = static_cast<uint32_t>(ctx.esp + 0x000005d8u);
    ctx.ecx = static_cast<uint32_t>(t399);
    // 0x0043e733: mov byte ptr [esp + 0x734], 0x34
    uint32_t t400 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t400, uint8_t{0x34u});
    // 0x0043e73b: call 0x407810
    uint32_t t401 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t401);
    mem.w32(t401, 0x0043e740u);
    sub_00407810(ctx, mem);
    // 0x0043e740: push 0x7b4282
    uint32_t t402 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t402);
    mem.w32(t402, 0x007b4282u);
    // 0x0043e745: lea ecx, [esp + 0x5f4]
    uint32_t t403 = static_cast<uint32_t>(ctx.esp + 0x000005f4u);
    ctx.ecx = static_cast<uint32_t>(t403);
    // 0x0043e74c: mov byte ptr [esp + 0x734], 0x35
    uint32_t t404 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t404, uint8_t{0x35u});
    // 0x0043e754: call 0x407810
    uint32_t t405 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t405);
    mem.w32(t405, 0x0043e759u);
    sub_00407810(ctx, mem);
    // 0x0043e759: push 0x536d84
    uint32_t t406 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t406);
    mem.w32(t406, 0x00536d84u);
    // 0x0043e75e: lea ecx, [esp + 0x610]
    uint32_t t407 = static_cast<uint32_t>(ctx.esp + 0x00000610u);
    ctx.ecx = static_cast<uint32_t>(t407);
    // 0x0043e765: mov byte ptr [esp + 0x734], 0x36
    uint32_t t408 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t408, uint8_t{0x36u});
    // 0x0043e76d: call 0x407810
    uint32_t t409 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t409);
    mem.w32(t409, 0x0043e772u);
    sub_00407810(ctx, mem);
    // 0x0043e772: push 0x7b4286
    uint32_t t410 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t410);
    mem.w32(t410, 0x007b4286u);
    // 0x0043e777: lea ecx, [esp + 0x62c]
    uint32_t t411 = static_cast<uint32_t>(ctx.esp + 0x0000062cu);
    ctx.ecx = static_cast<uint32_t>(t411);
    // 0x0043e77e: mov byte ptr [esp + 0x734], 0x37
    uint32_t t412 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t412, uint8_t{0x37u});
    // 0x0043e786: call 0x407810
    uint32_t t413 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t413);
    mem.w32(t413, 0x0043e78bu);
    sub_00407810(ctx, mem);
    // 0x0043e78b: push 0x536da8
    uint32_t t414 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t414);
    mem.w32(t414, 0x00536da8u);
    // 0x0043e790: lea ecx, [esp + 0x648]
    uint32_t t415 = static_cast<uint32_t>(ctx.esp + 0x00000648u);
    ctx.ecx = static_cast<uint32_t>(t415);
    // 0x0043e797: mov byte ptr [esp + 0x734], 0x38
    uint32_t t416 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t416, uint8_t{0x38u});
    // 0x0043e79f: call 0x407810
    uint32_t t417 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t417);
    mem.w32(t417, 0x0043e7a4u);
    sub_00407810(ctx, mem);
    // 0x0043e7a4: push 0x7b4292
    uint32_t t418 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t418);
    mem.w32(t418, 0x007b4292u);
    // 0x0043e7a9: lea ecx, [esp + 0x664]
    uint32_t t419 = static_cast<uint32_t>(ctx.esp + 0x00000664u);
    ctx.ecx = static_cast<uint32_t>(t419);
    // 0x0043e7b0: mov byte ptr [esp + 0x734], 0x39
    uint32_t t420 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t420, uint8_t{0x39u});
    // 0x0043e7b8: call 0x407810
    uint32_t t421 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t421);
    mem.w32(t421, 0x0043e7bdu);
    sub_00407810(ctx, mem);
    // 0x0043e7bd: push 0x536dcc
    uint32_t t422 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t422);
    mem.w32(t422, 0x00536dccu);
    // 0x0043e7c2: lea ecx, [esp + 0x680]
    uint32_t t423 = static_cast<uint32_t>(ctx.esp + 0x00000680u);
    ctx.ecx = static_cast<uint32_t>(t423);
    // 0x0043e7c9: mov byte ptr [esp + 0x734], 0x3a
    uint32_t t424 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t424, uint8_t{0x3au});
    // 0x0043e7d1: call 0x407810
    uint32_t t425 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t425);
    mem.w32(t425, 0x0043e7d6u);
    sub_00407810(ctx, mem);
    // 0x0043e7d6: push 0x7b429e
    uint32_t t426 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t426);
    mem.w32(t426, 0x007b429eu);
    // 0x0043e7db: lea ecx, [esp + 0x69c]
    uint32_t t427 = static_cast<uint32_t>(ctx.esp + 0x0000069cu);
    ctx.ecx = static_cast<uint32_t>(t427);
    // 0x0043e7e2: mov byte ptr [esp + 0x734], 0x3b
    uint32_t t428 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t428, uint8_t{0x3bu});
    // 0x0043e7ea: call 0x407810
    uint32_t t429 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t429);
    mem.w32(t429, 0x0043e7efu);
    sub_00407810(ctx, mem);
    // 0x0043e7ef: push 0x536ddc
    uint32_t t430 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t430);
    mem.w32(t430, 0x00536ddcu);
    // 0x0043e7f4: lea ecx, [esp + 0x6b8]
    uint32_t t431 = static_cast<uint32_t>(ctx.esp + 0x000006b8u);
    ctx.ecx = static_cast<uint32_t>(t431);
    // 0x0043e7fb: mov byte ptr [esp + 0x734], 0x3c
    uint32_t t432 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t432, uint8_t{0x3cu});
    // 0x0043e803: call 0x407810
    uint32_t t433 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t433);
    mem.w32(t433, 0x0043e808u);
    sub_00407810(ctx, mem);
    // 0x0043e808: push 0x7b42ab
    uint32_t t434 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t434);
    mem.w32(t434, 0x007b42abu);
    // 0x0043e80d: lea ecx, [esp + 0x6d4]
    uint32_t t435 = static_cast<uint32_t>(ctx.esp + 0x000006d4u);
    ctx.ecx = static_cast<uint32_t>(t435);
    // 0x0043e814: mov byte ptr [esp + 0x734], 0x3d
    uint32_t t436 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t436, uint8_t{0x3du});
    // 0x0043e81c: call 0x407810
    uint32_t t437 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t437);
    mem.w32(t437, 0x0043e821u);
    sub_00407810(ctx, mem);
    // 0x0043e821: push 0x534f8a
    uint32_t t438 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t438);
    mem.w32(t438, 0x00534f8au);
    // 0x0043e826: lea ecx, [esp + 0x6f0]
    uint32_t t439 = static_cast<uint32_t>(ctx.esp + 0x000006f0u);
    ctx.ecx = static_cast<uint32_t>(t439);
    // 0x0043e82d: mov byte ptr [esp + 0x734], 0x3e
    uint32_t t440 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t440, uint8_t{0x3eu});
    // 0x0043e835: call 0x407810
    uint32_t t441 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t441);
    mem.w32(t441, 0x0043e83au);
    sub_00407810(ctx, mem);
    // 0x0043e83a: push 0x7b42bc
    uint32_t t442 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t442);
    mem.w32(t442, 0x007b42bcu);
    // 0x0043e83f: lea ecx, [esp + 0x70c]
    uint32_t t443 = static_cast<uint32_t>(ctx.esp + 0x0000070cu);
    ctx.ecx = static_cast<uint32_t>(t443);
    // 0x0043e846: mov byte ptr [esp + 0x734], 0x3f
    uint32_t t444 = static_cast<uint32_t>(ctx.esp + 0x00000734u);
    mem.w8(t444, uint8_t{0x3fu});
    // 0x0043e84e: call 0x407810
    uint32_t t445 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t445);
    mem.w32(t445, 0x0043e853u);
    sub_00407810(ctx, mem);
    // 0x0043e853: mov dword ptr [esp + 0x730], 0x40
    uint32_t t446 = static_cast<uint32_t>(ctx.esp + 0x00000730u);
    mem.w32(t446, 0x00000040u);
    // 0x0043e85e: mov eax, dword ptr [0x55df18]
    uint32_t t447 = mem.r32(0x0055df18u);
    ctx.eax = static_cast<uint32_t>(t447);
    // 0x0043e863: cmp eax, ebx
    uint32_t t448 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t448);
    // 0x0043e865: je 0x43e885
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043e885;
    goto bb_0043e867;
}
bb_0043e885: {
    // 0x0043e885: push 0x534f8a
    uint32_t t449 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t449);
    mem.w32(t449, 0x00534f8au);
    // 0x0043e88a: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x0043e88c: call 0x407810
    uint32_t t450 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t450);
    mem.w32(t450, 0x0043e891u);
    sub_00407810(ctx, mem);
    // 0x0043e891: push 0x442d50
    uint32_t t451 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t451);
    mem.w32(t451, 0x00442d50u);
    // 0x0043e896: push 0x20
    uint32_t t452 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t452);
    mem.w32(t452, 0x00000020u);
    // 0x0043e898: push 0x38
    uint32_t t453 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t453);
    mem.w32(t453, 0x00000038u);
    // 0x0043e89a: lea ecx, [esp + 0x30]
    uint32_t t454 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    ctx.ecx = static_cast<uint32_t>(t454);
    // 0x0043e89e: push ecx
    uint32_t t455 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t455);
    mem.w32(t455, ctx.ecx);
    // 0x0043e89f: jmp 0x43e918
    goto bb_0043e918;
}
bb_0043e867: {
    // 0x0043e867: cmp dword ptr [eax + 0xc], edi
    uint32_t t456 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    uint32_t t457 = mem.r32(t456);
    uint32_t t458 = static_cast<uint32_t>(t457 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t457, ctx.edi, t458);
    // 0x0043e86a: jbe 0x43e885
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043e885;
    goto bb_0043e86c;
}
bb_0043e918: {
    // 0x0043e918: mov dword ptr [esp + 0x28], 1
    uint32_t t459 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t459, 0x00000001u);
    // 0x0043e920: mov byte ptr [esp + 0x740], bl
    uint32_t t460 = static_cast<uint32_t>(ctx.esp + 0x00000740u);
    mem.w8(t460, recomp_detail::r8l(ctx.ebx));
    // 0x0043e927: call 0x4e1c34
    uint32_t t461 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t461);
    mem.w32(t461, 0x0043e92cu);
    hle_crt_004e1c34(ctx, mem);
    // 0x0043e92c: mov eax, ebp
    ctx.eax = static_cast<uint32_t>(ctx.ebp);
    // 0x0043e92e: mov ecx, dword ptr [esp + 0x728]
    uint32_t t462 = static_cast<uint32_t>(ctx.esp + 0x00000728u);
    uint32_t t463 = mem.r32(t462);
    ctx.ecx = static_cast<uint32_t>(t463);
    // 0x0043e935: mov dword ptr fs:[0], ecx
    uint32_t t464 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t464, ctx.ecx);
    // 0x0043e93c: pop ecx
    uint32_t t465 = ctx.esp;
    uint32_t t466 = mem.r32(t465);
    uint32_t t467 = static_cast<uint32_t>(t465 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t467);
    ctx.ecx = static_cast<uint32_t>(t466);
    // 0x0043e93d: pop edi
    uint32_t t468 = ctx.esp;
    uint32_t t469 = mem.r32(t468);
    uint32_t t470 = static_cast<uint32_t>(t468 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t470);
    ctx.edi = static_cast<uint32_t>(t469);
    // 0x0043e93e: pop esi
    uint32_t t471 = ctx.esp;
    uint32_t t472 = mem.r32(t471);
    uint32_t t473 = static_cast<uint32_t>(t471 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t473);
    ctx.esi = static_cast<uint32_t>(t472);
    // 0x0043e93f: pop ebp
    uint32_t t474 = ctx.esp;
    uint32_t t475 = mem.r32(t474);
    uint32_t t476 = static_cast<uint32_t>(t474 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t476);
    ctx.ebp = static_cast<uint32_t>(t475);
    // 0x0043e940: pop ebx
    uint32_t t477 = ctx.esp;
    uint32_t t478 = mem.r32(t477);
    uint32_t t479 = static_cast<uint32_t>(t477 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t479);
    ctx.ebx = static_cast<uint32_t>(t478);
    // 0x0043e941: mov ecx, dword ptr [esp + 0x710]
    uint32_t t480 = static_cast<uint32_t>(ctx.esp + 0x00000710u);
    uint32_t t481 = mem.r32(t480);
    ctx.ecx = static_cast<uint32_t>(t481);
    // 0x0043e948: xor ecx, esp
    uint32_t t482 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t482);
    ctx.ecx = static_cast<uint32_t>(t482);
    // 0x0043e94a: call 0x4e02f8
    uint32_t t483 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t483);
    mem.w32(t483, 0x0043e94fu);
    hle_crt_004e02f8(ctx, mem);
    // 0x0043e94f: add esp, 0x720
    uint32_t t484 = static_cast<uint32_t>(ctx.esp + 0x00000720u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000720u, t484);
    ctx.esp = static_cast<uint32_t>(t484);
    // 0x0043e955: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043e86c: {
    // 0x0043e86c: cmp dword ptr [eax], ebx
    uint32_t t485 = mem.r32(ctx.eax);
    uint32_t t486 = static_cast<uint32_t>(t485 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t485, ctx.ebx, t486);
    // 0x0043e86e: jne 0x43e87b
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043e87b;
    goto bb_0043e870;
}
bb_0043e87b: {
    // 0x0043e87b: mov eax, dword ptr [eax + 4]
    uint32_t t487 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t488 = mem.r32(t487);
    ctx.eax = static_cast<uint32_t>(t488);
    // 0x0043e87e: mov ecx, dword ptr [eax + edi*4]
    uint32_t t489 = recomp_detail::shl<uint32_t>(ctx.edi, 0x00000002u);
    uint32_t t490 = static_cast<uint32_t>(ctx.eax + t489);
    uint32_t t491 = mem.r32(t490);
    ctx.ecx = static_cast<uint32_t>(t491);
    goto bb_0043e881;
}
bb_0043e870: {
    // 0x0043e870: mov ecx, dword ptr [eax + 8]
    uint32_t t492 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    uint32_t t493 = mem.r32(t492);
    ctx.ecx = static_cast<uint32_t>(t493);
    // 0x0043e873: imul ecx, edi
    uint64_t t494 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)) * static_cast<int64_t>(static_cast<int32_t>(ctx.edi)));
    uint32_t t495 = static_cast<uint32_t>(t494);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t494);
    ctx.ecx = static_cast<uint32_t>(t495);
    // 0x0043e876: add ecx, dword ptr [eax + 4]
    uint32_t t496 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t497 = mem.r32(t496);
    uint32_t t498 = static_cast<uint32_t>(ctx.ecx + t497);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, t497, t498);
    ctx.ecx = static_cast<uint32_t>(t498);
    // 0x0043e879: jmp 0x43e881
}
bb_0043e881: {
    // 0x0043e881: cmp ecx, ebx
    uint32_t t499 = static_cast<uint32_t>(ctx.ecx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebx, t499);
    // 0x0043e883: jne 0x43e8a1
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043e8a1;
    goto bb_0043e885;
}
bb_0043e8a1: {
    // 0x0043e8a1: xor eax, eax
    uint32_t t500 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t500);
    ctx.eax = static_cast<uint32_t>(t500);
    // 0x0043e8a3: cmp dword ptr [esp + 0x38], ebx
    uint32_t t501 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    uint32_t t502 = mem.r32(t501);
    uint32_t t503 = static_cast<uint32_t>(t502 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t502, ctx.ebx, t503);
    // 0x0043e8a7: mov dword ptr [esp + 0x14], eax
    uint32_t t504 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t504, ctx.eax);
    // 0x0043e8ab: je 0x43e8e9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043e8e9;
    goto bb_0043e8ad;
}
bb_0043e8e9: {
    // 0x0043e8e9: lea edx, [eax*8]
    uint32_t t505 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000003u);
    ctx.edx = static_cast<uint32_t>(t505);
    // 0x0043e8f0: push -1
    uint32_t t506 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t506);
    mem.w32(t506, 0xffffffffu);
    // 0x0043e8f2: sub edx, eax
    uint32_t t507 = static_cast<uint32_t>(ctx.edx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.eax, t507);
    ctx.edx = static_cast<uint32_t>(t507);
    // 0x0043e8f4: lea eax, [esp + edx*8 + 0x44]
    uint32_t t508 = recomp_detail::shl<uint32_t>(ctx.edx, 0x00000003u);
    uint32_t t509 = static_cast<uint32_t>(ctx.esp + t508);
    uint32_t t510 = static_cast<uint32_t>(t509 + 0x00000044u);
    ctx.eax = static_cast<uint32_t>(t510);
    // 0x0043e8f8: push ebx
    uint32_t t511 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t511);
    mem.w32(t511, ctx.ebx);
    // 0x0043e8f9: mov dword ptr [ebp + 0x18], esi
    uint32_t t512 = static_cast<uint32_t>(ctx.ebp + 0x00000018u);
    mem.w32(t512, ctx.esi);
    // 0x0043e8fc: mov dword ptr [ebp + 0x14], ebx
    uint32_t t513 = static_cast<uint32_t>(ctx.ebp + 0x00000014u);
    mem.w32(t513, ctx.ebx);
    // 0x0043e8ff: push eax
    uint32_t t514 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t514);
    mem.w32(t514, ctx.eax);
    // 0x0043e900: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x0043e902: mov byte ptr [ebp + 4], bl
    uint32_t t515 = static_cast<uint32_t>(ctx.ebp + 0x00000004u);
    mem.w8(t515, recomp_detail::r8l(ctx.ebx));
    // 0x0043e905: call 0x4079d0
    uint32_t t516 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t516);
    mem.w32(t516, 0x0043e90au);
    sub_004079d0(ctx, mem);
    // 0x0043e90a: push 0x442d50
    uint32_t t517 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t517);
    mem.w32(t517, 0x00442d50u);
    // 0x0043e90f: push 0x20
    uint32_t t518 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t518);
    mem.w32(t518, 0x00000020u);
    // 0x0043e911: push 0x38
    uint32_t t519 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t519);
    mem.w32(t519, 0x00000038u);
    // 0x0043e913: lea eax, [esp + 0x30]
    uint32_t t520 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    ctx.eax = static_cast<uint32_t>(t520);
    // 0x0043e917: push eax
    uint32_t t521 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t521);
    mem.w32(t521, ctx.eax);
    goto bb_0043e918;
}
bb_0043e8ad: {
    // 0x0043e8ad: add ecx, 4
    uint32_t t522 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000004u, t522);
    ctx.ecx = static_cast<uint32_t>(t522);
    // 0x0043e8b0: mov dword ptr [esp + 0x1c], ecx
    uint32_t t523 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t523, ctx.ecx);
}
bb_0043e8b4: {
    // 0x0043e8b4: mov ecx, dword ptr [esp + 0x1c]
    uint32_t t524 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t525 = mem.r32(t524);
    ctx.ecx = static_cast<uint32_t>(t525);
    // 0x0043e8b8: lea edi, [esp + eax + 0x24]
    uint32_t t526 = static_cast<uint32_t>(ctx.esp + ctx.eax);
    uint32_t t527 = static_cast<uint32_t>(t526 + 0x00000024u);
    ctx.edi = static_cast<uint32_t>(t527);
    // 0x0043e8bc: call 0x42bdc0
    uint32_t t528 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t528);
    mem.w32(t528, 0x0043e8c1u);
    sub_0042bdc0(ctx, mem);
    // 0x0043e8c1: test al, al
    uint8_t t529 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t529);
    // 0x0043e8c3: jne 0x43e8e5
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043e8e5;
    goto bb_0043e8c5;
}
bb_0043e8e5: {
    // 0x0043e8e5: mov eax, dword ptr [esp + 0x14]
    uint32_t t530 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t531 = mem.r32(t530);
    ctx.eax = static_cast<uint32_t>(t531);
    goto bb_0043e8e9;
}
bb_0043e8c5: {
    // 0x0043e8c5: mov ecx, dword ptr [esp + 0x14]
    uint32_t t532 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t533 = mem.r32(t532);
    ctx.ecx = static_cast<uint32_t>(t533);
    // 0x0043e8c9: add ecx, 1
    uint32_t t534 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t534);
    ctx.ecx = static_cast<uint32_t>(t534);
    // 0x0043e8cc: lea eax, [ecx*8]
    uint32_t t535 = recomp_detail::shl<uint32_t>(ctx.ecx, 0x00000003u);
    ctx.eax = static_cast<uint32_t>(t535);
    // 0x0043e8d3: sub eax, ecx
    uint32_t t536 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t536);
    ctx.eax = static_cast<uint32_t>(t536);
    // 0x0043e8d5: add eax, eax
    uint32_t t537 = static_cast<uint32_t>(ctx.eax + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.eax, t537);
    ctx.eax = static_cast<uint32_t>(t537);
    // 0x0043e8d7: add eax, eax
    uint32_t t538 = static_cast<uint32_t>(ctx.eax + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.eax, t538);
    ctx.eax = static_cast<uint32_t>(t538);
    // 0x0043e8d9: add eax, eax
    uint32_t t539 = static_cast<uint32_t>(ctx.eax + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.eax, t539);
    ctx.eax = static_cast<uint32_t>(t539);
    // 0x0043e8db: cmp dword ptr [esp + eax + 0x38], ebx
    uint32_t t540 = static_cast<uint32_t>(ctx.esp + ctx.eax);
    uint32_t t541 = static_cast<uint32_t>(t540 + 0x00000038u);
    uint32_t t542 = mem.r32(t541);
    uint32_t t543 = static_cast<uint32_t>(t542 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t542, ctx.ebx, t543);
    // 0x0043e8df: mov dword ptr [esp + 0x14], ecx
    uint32_t t544 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t544, ctx.ecx);
    // 0x0043e8e3: jne 0x43e8b4
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043e8b4;
    goto bb_0043e8e5;
}
}

// sub_0043e960 | subsystem=Replay | canonical | 4 blocks | 145 insns
void sub_0043e960(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043e960: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0043e962: push 0x51429d
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051429du);
    // 0x0043e967: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0043e96d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0043e96e: sub esp, 0x140
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000140u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000140u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x0043e974: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0043e979: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0043e97b: mov dword ptr [esp + 0x13c], eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x0000013cu);
    mem.w32(t8, ctx.eax);
    // 0x0043e982: push ebx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ebx);
    // 0x0043e983: push ebp
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.ebp);
    // 0x0043e984: push esi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.esi);
    // 0x0043e985: mov eax, dword ptr [0x54b458]
    uint32_t t12 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0043e98a: xor eax, esp
    uint32_t t13 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t13);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0043e98c: push eax
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, ctx.eax);
    // 0x0043e98d: lea eax, [esp + 0x150]
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x00000150u);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x0043e994: mov dword ptr fs:[0], eax
    uint32_t t16 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t16, ctx.eax);
    // 0x0043e99a: mov ebp, dword ptr [esp + 0x160]
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000160u);
    uint32_t t18 = mem.r32(t17);
    ctx.ebp = static_cast<uint32_t>(t18);
    // 0x0043e9a1: xor ebx, ebx
    uint32_t t19 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t19);
    ctx.ebx = static_cast<uint32_t>(t19);
    // 0x0043e9a3: mov dword ptr [esp + 0x10], ebx
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t20, ctx.ebx);
    // 0x0043e9a7: push 3
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x00000003u);
    // 0x0043e9a9: mov esi, 0xf
    ctx.esi = static_cast<uint32_t>(0x0000000fu);
    // 0x0043e9ae: push 0x536e0c
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x00536e0cu);
    // 0x0043e9b3: lea ecx, [esp + 0x20]
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    ctx.ecx = static_cast<uint32_t>(t23);
    // 0x0043e9b7: mov dword ptr [esp + 0x1c], edi
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t24, ctx.edi);
    // 0x0043e9bb: mov dword ptr [esp + 0x38], esi
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    mem.w32(t25, ctx.esi);
    // 0x0043e9bf: mov dword ptr [esp + 0x34], ebx
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    mem.w32(t26, ctx.ebx);
    // 0x0043e9c3: mov byte ptr [esp + 0x24], bl
    uint32_t t27 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w8(t27, recomp_detail::r8l(ctx.ebx));
    // 0x0043e9c7: call 0x407c10
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x0043e9ccu);
    sub_00407c10(ctx, mem);
    // 0x0043e9cc: mov dword ptr [esp + 0x158], 1
    uint32_t t29 = static_cast<uint32_t>(ctx.esp + 0x00000158u);
    mem.w32(t29, 0x00000001u);
    // 0x0043e9d7: push 3
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x00000003u);
    // 0x0043e9d9: push 0x536e10
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x00536e10u);
    // 0x0043e9de: lea ecx, [esp + 0x3c]
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    ctx.ecx = static_cast<uint32_t>(t32);
    // 0x0043e9e2: mov dword ptr [esp + 0x54], esi
    uint32_t t33 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    mem.w32(t33, ctx.esi);
    // 0x0043e9e6: mov dword ptr [esp + 0x50], ebx
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + 0x00000050u);
    mem.w32(t34, ctx.ebx);
    // 0x0043e9ea: mov byte ptr [esp + 0x40], bl
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    mem.w8(t35, recomp_detail::r8l(ctx.ebx));
    // 0x0043e9ee: call 0x407c10
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, 0x0043e9f3u);
    sub_00407c10(ctx, mem);
    // 0x0043e9f3: mov byte ptr [esp + 0x158], 2
    uint32_t t37 = static_cast<uint32_t>(ctx.esp + 0x00000158u);
    mem.w8(t37, uint8_t{0x02u});
    // 0x0043e9fb: push 3
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, 0x00000003u);
    // 0x0043e9fd: push 0x536e14
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, 0x00536e14u);
    // 0x0043ea02: lea ecx, [esp + 0x58]
    uint32_t t40 = static_cast<uint32_t>(ctx.esp + 0x00000058u);
    ctx.ecx = static_cast<uint32_t>(t40);
    // 0x0043ea06: mov dword ptr [esp + 0x70], esi
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + 0x00000070u);
    mem.w32(t41, ctx.esi);
    // 0x0043ea0a: mov dword ptr [esp + 0x6c], ebx
    uint32_t t42 = static_cast<uint32_t>(ctx.esp + 0x0000006cu);
    mem.w32(t42, ctx.ebx);
    // 0x0043ea0e: mov byte ptr [esp + 0x5c], bl
    uint32_t t43 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    mem.w8(t43, recomp_detail::r8l(ctx.ebx));
    // 0x0043ea12: call 0x407c10
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, 0x0043ea17u);
    sub_00407c10(ctx, mem);
    // 0x0043ea17: mov byte ptr [esp + 0x158], 3
    uint32_t t45 = static_cast<uint32_t>(ctx.esp + 0x00000158u);
    mem.w8(t45, uint8_t{0x03u});
    // 0x0043ea1f: push 0xe
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, 0x0000000eu);
    // 0x0043ea21: push 0x536e18
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, 0x00536e18u);
    // 0x0043ea26: lea ecx, [esp + 0x74]
    uint32_t t48 = static_cast<uint32_t>(ctx.esp + 0x00000074u);
    ctx.ecx = static_cast<uint32_t>(t48);
    // 0x0043ea2a: mov dword ptr [esp + 0x8c], esi
    uint32_t t49 = static_cast<uint32_t>(ctx.esp + 0x0000008cu);
    mem.w32(t49, ctx.esi);
    // 0x0043ea31: mov dword ptr [esp + 0x88], ebx
    uint32_t t50 = static_cast<uint32_t>(ctx.esp + 0x00000088u);
    mem.w32(t50, ctx.ebx);
    // 0x0043ea38: mov byte ptr [esp + 0x78], bl
    uint32_t t51 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    mem.w8(t51, recomp_detail::r8l(ctx.ebx));
    // 0x0043ea3c: call 0x407c10
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, 0x0043ea41u);
    sub_00407c10(ctx, mem);
    // 0x0043ea41: mov byte ptr [esp + 0x158], 4
    uint32_t t53 = static_cast<uint32_t>(ctx.esp + 0x00000158u);
    mem.w8(t53, uint8_t{0x04u});
    // 0x0043ea49: push 0xe
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, 0x0000000eu);
    // 0x0043ea4b: push 0x536e28
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, 0x00536e28u);
    // 0x0043ea50: lea ecx, [esp + 0x90]
    uint32_t t56 = static_cast<uint32_t>(ctx.esp + 0x00000090u);
    ctx.ecx = static_cast<uint32_t>(t56);
    // 0x0043ea57: mov dword ptr [esp + 0xa8], esi
    uint32_t t57 = static_cast<uint32_t>(ctx.esp + 0x000000a8u);
    mem.w32(t57, ctx.esi);
    // 0x0043ea5e: mov dword ptr [esp + 0xa4], ebx
    uint32_t t58 = static_cast<uint32_t>(ctx.esp + 0x000000a4u);
    mem.w32(t58, ctx.ebx);
    // 0x0043ea65: mov byte ptr [esp + 0x94], bl
    uint32_t t59 = static_cast<uint32_t>(ctx.esp + 0x00000094u);
    mem.w8(t59, recomp_detail::r8l(ctx.ebx));
    // 0x0043ea6c: call 0x407c10
    uint32_t t60 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t60);
    mem.w32(t60, 0x0043ea71u);
    sub_00407c10(ctx, mem);
    // 0x0043ea71: mov byte ptr [esp + 0x158], 5
    uint32_t t61 = static_cast<uint32_t>(ctx.esp + 0x00000158u);
    mem.w8(t61, uint8_t{0x05u});
    // 0x0043ea79: push 0xe
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, 0x0000000eu);
    // 0x0043ea7b: push 0x536e38
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, 0x00536e38u);
    // 0x0043ea80: lea ecx, [esp + 0xac]
    uint32_t t64 = static_cast<uint32_t>(ctx.esp + 0x000000acu);
    ctx.ecx = static_cast<uint32_t>(t64);
    // 0x0043ea87: mov dword ptr [esp + 0xc4], esi
    uint32_t t65 = static_cast<uint32_t>(ctx.esp + 0x000000c4u);
    mem.w32(t65, ctx.esi);
    // 0x0043ea8e: mov dword ptr [esp + 0xc0], ebx
    uint32_t t66 = static_cast<uint32_t>(ctx.esp + 0x000000c0u);
    mem.w32(t66, ctx.ebx);
    // 0x0043ea95: mov byte ptr [esp + 0xb0], bl
    uint32_t t67 = static_cast<uint32_t>(ctx.esp + 0x000000b0u);
    mem.w8(t67, recomp_detail::r8l(ctx.ebx));
    // 0x0043ea9c: call 0x407c10
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, 0x0043eaa1u);
    sub_00407c10(ctx, mem);
    // 0x0043eaa1: mov byte ptr [esp + 0x158], 6
    uint32_t t69 = static_cast<uint32_t>(ctx.esp + 0x00000158u);
    mem.w8(t69, uint8_t{0x06u});
    // 0x0043eaa9: push 0xe
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, 0x0000000eu);
    // 0x0043eaab: push 0x536e48
    uint32_t t71 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t71);
    mem.w32(t71, 0x00536e48u);
    // 0x0043eab0: lea ecx, [esp + 0xc8]
    uint32_t t72 = static_cast<uint32_t>(ctx.esp + 0x000000c8u);
    ctx.ecx = static_cast<uint32_t>(t72);
    // 0x0043eab7: mov dword ptr [esp + 0xe0], esi
    uint32_t t73 = static_cast<uint32_t>(ctx.esp + 0x000000e0u);
    mem.w32(t73, ctx.esi);
    // 0x0043eabe: mov dword ptr [esp + 0xdc], ebx
    uint32_t t74 = static_cast<uint32_t>(ctx.esp + 0x000000dcu);
    mem.w32(t74, ctx.ebx);
    // 0x0043eac5: mov byte ptr [esp + 0xcc], bl
    uint32_t t75 = static_cast<uint32_t>(ctx.esp + 0x000000ccu);
    mem.w8(t75, recomp_detail::r8l(ctx.ebx));
    // 0x0043eacc: call 0x407c10
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    mem.w32(t76, 0x0043ead1u);
    sub_00407c10(ctx, mem);
    // 0x0043ead1: mov byte ptr [esp + 0x158], 7
    uint32_t t77 = static_cast<uint32_t>(ctx.esp + 0x00000158u);
    mem.w8(t77, uint8_t{0x07u});
    // 0x0043ead9: push 0xe
    uint32_t t78 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    mem.w32(t78, 0x0000000eu);
    // 0x0043eadb: push 0x536e58
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, 0x00536e58u);
    // 0x0043eae0: lea ecx, [esp + 0xe4]
    uint32_t t80 = static_cast<uint32_t>(ctx.esp + 0x000000e4u);
    ctx.ecx = static_cast<uint32_t>(t80);
    // 0x0043eae7: mov dword ptr [esp + 0xfc], esi
    uint32_t t81 = static_cast<uint32_t>(ctx.esp + 0x000000fcu);
    mem.w32(t81, ctx.esi);
    // 0x0043eaee: mov dword ptr [esp + 0xf8], ebx
    uint32_t t82 = static_cast<uint32_t>(ctx.esp + 0x000000f8u);
    mem.w32(t82, ctx.ebx);
    // 0x0043eaf5: mov byte ptr [esp + 0xe8], bl
    uint32_t t83 = static_cast<uint32_t>(ctx.esp + 0x000000e8u);
    mem.w8(t83, recomp_detail::r8l(ctx.ebx));
    // 0x0043eafc: call 0x407c10
    uint32_t t84 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    mem.w32(t84, 0x0043eb01u);
    sub_00407c10(ctx, mem);
    // 0x0043eb01: mov byte ptr [esp + 0x158], 8
    uint32_t t85 = static_cast<uint32_t>(ctx.esp + 0x00000158u);
    mem.w8(t85, uint8_t{0x08u});
    // 0x0043eb09: push 0xe
    uint32_t t86 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t86);
    mem.w32(t86, 0x0000000eu);
    // 0x0043eb0b: mov dword ptr [esp + 0x114], esi
    uint32_t t87 = static_cast<uint32_t>(ctx.esp + 0x00000114u);
    mem.w32(t87, ctx.esi);
    // 0x0043eb12: mov dword ptr [esp + 0x110], ebx
    uint32_t t88 = static_cast<uint32_t>(ctx.esp + 0x00000110u);
    mem.w32(t88, ctx.ebx);
    // 0x0043eb19: mov byte ptr [esp + 0x100], bl
    uint32_t t89 = static_cast<uint32_t>(ctx.esp + 0x00000100u);
    mem.w8(t89, recomp_detail::r8l(ctx.ebx));
    // 0x0043eb20: push 0x536e68
    uint32_t t90 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    mem.w32(t90, 0x00536e68u);
    // 0x0043eb25: lea ecx, [esp + 0x100]
    uint32_t t91 = static_cast<uint32_t>(ctx.esp + 0x00000100u);
    ctx.ecx = static_cast<uint32_t>(t91);
    // 0x0043eb2c: call 0x407c10
    uint32_t t92 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    mem.w32(t92, 0x0043eb31u);
    sub_00407c10(ctx, mem);
    // 0x0043eb31: mov byte ptr [esp + 0x158], 9
    uint32_t t93 = static_cast<uint32_t>(ctx.esp + 0x00000158u);
    mem.w8(t93, uint8_t{0x09u});
    // 0x0043eb39: push 3
    uint32_t t94 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t94);
    mem.w32(t94, 0x00000003u);
    // 0x0043eb3b: push 0x536e78
    uint32_t t95 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t95);
    mem.w32(t95, 0x00536e78u);
    // 0x0043eb40: lea ecx, [esp + 0x11c]
    uint32_t t96 = static_cast<uint32_t>(ctx.esp + 0x0000011cu);
    ctx.ecx = static_cast<uint32_t>(t96);
    // 0x0043eb47: mov dword ptr [esp + 0x134], esi
    uint32_t t97 = static_cast<uint32_t>(ctx.esp + 0x00000134u);
    mem.w32(t97, ctx.esi);
    // 0x0043eb4e: mov dword ptr [esp + 0x130], ebx
    uint32_t t98 = static_cast<uint32_t>(ctx.esp + 0x00000130u);
    mem.w32(t98, ctx.ebx);
    // 0x0043eb55: mov byte ptr [esp + 0x120], bl
    uint32_t t99 = static_cast<uint32_t>(ctx.esp + 0x00000120u);
    mem.w8(t99, recomp_detail::r8l(ctx.ebx));
    // 0x0043eb5c: call 0x407c10
    uint32_t t100 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t100);
    mem.w32(t100, 0x0043eb61u);
    sub_00407c10(ctx, mem);
    // 0x0043eb61: mov byte ptr [esp + 0x158], 0xa
    uint32_t t101 = static_cast<uint32_t>(ctx.esp + 0x00000158u);
    mem.w8(t101, uint8_t{0x0au});
    // 0x0043eb69: push esi
    uint32_t t102 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    mem.w32(t102, ctx.esi);
    // 0x0043eb6a: push 0x536e7c
    uint32_t t103 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    mem.w32(t103, 0x00536e7cu);
    // 0x0043eb6f: lea ecx, [esp + 0x138]
    uint32_t t104 = static_cast<uint32_t>(ctx.esp + 0x00000138u);
    ctx.ecx = static_cast<uint32_t>(t104);
    // 0x0043eb76: mov dword ptr [esp + 0x150], esi
    uint32_t t105 = static_cast<uint32_t>(ctx.esp + 0x00000150u);
    mem.w32(t105, ctx.esi);
    // 0x0043eb7d: mov dword ptr [esp + 0x14c], ebx
    uint32_t t106 = static_cast<uint32_t>(ctx.esp + 0x0000014cu);
    mem.w32(t106, ctx.ebx);
    // 0x0043eb84: mov byte ptr [esp + 0x13c], bl
    uint32_t t107 = static_cast<uint32_t>(ctx.esp + 0x0000013cu);
    mem.w8(t107, recomp_detail::r8l(ctx.ebx));
    // 0x0043eb8b: call 0x407c10
    uint32_t t108 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t108);
    mem.w32(t108, 0x0043eb90u);
    sub_00407c10(ctx, mem);
    // 0x0043eb90: cmp ebp, ebx
    uint32_t t109 = static_cast<uint32_t>(ctx.ebp - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebp, ctx.ebx, t109);
    // 0x0043eb92: mov dword ptr [esp + 0x158], 0xb
    uint32_t t110 = static_cast<uint32_t>(ctx.esp + 0x00000158u);
    mem.w32(t110, 0x0000000bu);
    // 0x0043eb9d: jl 0x43eba4
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0043eba4;
    goto bb_0043eb9f;
}
bb_0043eba4: {
    // 0x0043eba4: mov ebp, 0xa
    ctx.ebp = static_cast<uint32_t>(0x0000000au);
    goto bb_0043eba9;
}
bb_0043eb9f: {
    // 0x0043eb9f: cmp ebp, 0xa
    uint32_t t111 = static_cast<uint32_t>(ctx.ebp - 0x0000000au);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebp, 0x0000000au, t111);
    // 0x0043eba2: jle 0x43eba9
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0043eba9;
    goto bb_0043eba4;
}
bb_0043eba9: {
    // 0x0043eba9: lea eax, [ebp*8]
    uint32_t t112 = recomp_detail::shl<uint32_t>(ctx.ebp, 0x00000003u);
    ctx.eax = static_cast<uint32_t>(t112);
    // 0x0043ebb0: push -1
    uint32_t t113 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t113);
    mem.w32(t113, 0xffffffffu);
    // 0x0043ebb2: sub eax, ebp
    uint32_t t114 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t114);
    ctx.eax = static_cast<uint32_t>(t114);
    // 0x0043ebb4: lea eax, [esp + eax*4 + 0x1c]
    uint32_t t115 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000002u);
    uint32_t t116 = static_cast<uint32_t>(ctx.esp + t115);
    uint32_t t117 = static_cast<uint32_t>(t116 + 0x0000001cu);
    ctx.eax = static_cast<uint32_t>(t117);
    // 0x0043ebb8: push ebx
    uint32_t t118 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    mem.w32(t118, ctx.ebx);
    // 0x0043ebb9: mov dword ptr [edi + 0x18], esi
    uint32_t t119 = static_cast<uint32_t>(ctx.edi + 0x00000018u);
    mem.w32(t119, ctx.esi);
    // 0x0043ebbc: mov dword ptr [edi + 0x14], ebx
    uint32_t t120 = static_cast<uint32_t>(ctx.edi + 0x00000014u);
    mem.w32(t120, ctx.ebx);
    // 0x0043ebbf: push eax
    uint32_t t121 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t121);
    mem.w32(t121, ctx.eax);
    // 0x0043ebc0: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x0043ebc2: mov byte ptr [edi + 4], bl
    uint32_t t122 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    mem.w8(t122, recomp_detail::r8l(ctx.ebx));
    // 0x0043ebc5: call 0x4079d0
    uint32_t t123 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t123);
    mem.w32(t123, 0x0043ebcau);
    sub_004079d0(ctx, mem);
    // 0x0043ebca: push 0x407850
    uint32_t t124 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t124);
    mem.w32(t124, 0x00407850u);
    // 0x0043ebcf: push 0xb
    uint32_t t125 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t125);
    mem.w32(t125, 0x0000000bu);
    // 0x0043ebd1: push 0x1c
    uint32_t t126 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t126);
    mem.w32(t126, 0x0000001cu);
    // 0x0043ebd3: lea eax, [esp + 0x24]
    uint32_t t127 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    ctx.eax = static_cast<uint32_t>(t127);
    // 0x0043ebd7: push eax
    uint32_t t128 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t128);
    mem.w32(t128, ctx.eax);
    // 0x0043ebd8: mov dword ptr [esp + 0x20], 1
    uint32_t t129 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t129, 0x00000001u);
    // 0x0043ebe0: mov byte ptr [esp + 0x168], bl
    uint32_t t130 = static_cast<uint32_t>(ctx.esp + 0x00000168u);
    mem.w8(t130, recomp_detail::r8l(ctx.ebx));
    // 0x0043ebe7: call 0x4e1c34
    uint32_t t131 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t131);
    mem.w32(t131, 0x0043ebecu);
    hle_crt_004e1c34(ctx, mem);
    // 0x0043ebec: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x0043ebee: mov ecx, dword ptr [esp + 0x150]
    uint32_t t132 = static_cast<uint32_t>(ctx.esp + 0x00000150u);
    uint32_t t133 = mem.r32(t132);
    ctx.ecx = static_cast<uint32_t>(t133);
    // 0x0043ebf5: mov dword ptr fs:[0], ecx
    uint32_t t134 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t134, ctx.ecx);
    // 0x0043ebfc: pop ecx
    uint32_t t135 = ctx.esp;
    uint32_t t136 = mem.r32(t135);
    uint32_t t137 = static_cast<uint32_t>(t135 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t137);
    ctx.ecx = static_cast<uint32_t>(t136);
    // 0x0043ebfd: pop esi
    uint32_t t138 = ctx.esp;
    uint32_t t139 = mem.r32(t138);
    uint32_t t140 = static_cast<uint32_t>(t138 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t140);
    ctx.esi = static_cast<uint32_t>(t139);
    // 0x0043ebfe: pop ebp
    uint32_t t141 = ctx.esp;
    uint32_t t142 = mem.r32(t141);
    uint32_t t143 = static_cast<uint32_t>(t141 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t143);
    ctx.ebp = static_cast<uint32_t>(t142);
    // 0x0043ebff: pop ebx
    uint32_t t144 = ctx.esp;
    uint32_t t145 = mem.r32(t144);
    uint32_t t146 = static_cast<uint32_t>(t144 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t146);
    ctx.ebx = static_cast<uint32_t>(t145);
    // 0x0043ec00: mov ecx, dword ptr [esp + 0x13c]
    uint32_t t147 = static_cast<uint32_t>(ctx.esp + 0x0000013cu);
    uint32_t t148 = mem.r32(t147);
    ctx.ecx = static_cast<uint32_t>(t148);
    // 0x0043ec07: xor ecx, esp
    uint32_t t149 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t149);
    ctx.ecx = static_cast<uint32_t>(t149);
    // 0x0043ec09: call 0x4e02f8
    uint32_t t150 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t150);
    mem.w32(t150, 0x0043ec0eu);
    hle_crt_004e02f8(ctx, mem);
    // 0x0043ec0e: add esp, 0x14c
    uint32_t t151 = static_cast<uint32_t>(ctx.esp + 0x0000014cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000014cu, t151);
    ctx.esp = static_cast<uint32_t>(t151);
    // 0x0043ec14: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0043ec20 | subsystem=Replay | canonical | 13 blocks | 54 insns
void sub_0043ec20(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043ec20: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x0043ec21: mov eax, dword ptr [esi + 0x94]
    uint32_t t1 = static_cast<uint32_t>(ctx.esi + 0x00000094u);
    uint32_t t2 = mem.r32(t1);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x0043ec27: push ebx
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.ebx);
    // 0x0043ec28: xor ebx, ebx
    uint32_t t4 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    ctx.ebx = static_cast<uint32_t>(t4);
    // 0x0043ec2a: test eax, eax
    uint32_t t5 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    // 0x0043ec2c: je 0x43ec97
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043ec97;
    goto bb_0043ec2e;
}
bb_0043ec97: {
    // 0x0043ec97: mov eax, ebx
    ctx.eax = static_cast<uint32_t>(ctx.ebx);
    // 0x0043ec99: pop ebx
    uint32_t t6 = ctx.esp;
    uint32_t t7 = mem.r32(t6);
    uint32_t t8 = static_cast<uint32_t>(t6 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    ctx.ebx = static_cast<uint32_t>(t7);
    // 0x0043ec9a: pop ecx
    uint32_t t9 = ctx.esp;
    uint32_t t10 = mem.r32(t9);
    uint32_t t11 = static_cast<uint32_t>(t9 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    ctx.ecx = static_cast<uint32_t>(t10);
    // 0x0043ec9b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043ec2e: {
    // 0x0043ec2e: mov ecx, dword ptr [esi + 0x98]
    uint32_t t12 = static_cast<uint32_t>(ctx.esi + 0x00000098u);
    uint32_t t13 = mem.r32(t12);
    ctx.ecx = static_cast<uint32_t>(t13);
    // 0x0043ec34: sub ecx, eax
    uint32_t t14 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t14);
    ctx.ecx = static_cast<uint32_t>(t14);
    // 0x0043ec36: sar ecx, 2
    uint32_t t15 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t16 = recomp_detail::sar<uint32_t>(ctx.ecx, t15);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.ecx, t15, t16);
    ctx.ecx = static_cast<uint32_t>(t16);
    // 0x0043ec39: je 0x43ec97
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043ec97;
}
{
    // 0x0043ec3b: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x0043ec3d: test ecx, ecx
    uint32_t t17 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t17);
    // 0x0043ec3f: push edi
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, ctx.edi);
    // 0x0043ec40: mov edi, dword ptr [esi + 0x8c]
    uint32_t t19 = static_cast<uint32_t>(ctx.esi + 0x0000008cu);
    uint32_t t20 = mem.r32(t19);
    ctx.edi = static_cast<uint32_t>(t20);
    // 0x0043ec46: je 0x43ec57
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043ec57;
    goto bb_0043ec48;
}
bb_0043ec57: {
    // 0x0043ec57: call 0x4e0bf2
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x0043ec5cu);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043ec5c;
}
bb_0043ec48: {
    // 0x0043ec48: mov eax, dword ptr [esi + 0x98]
    uint32_t t22 = static_cast<uint32_t>(ctx.esi + 0x00000098u);
    uint32_t t23 = mem.r32(t22);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x0043ec4e: sub eax, ecx
    uint32_t t24 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t24);
    ctx.eax = static_cast<uint32_t>(t24);
    // 0x0043ec50: sar eax, 2
    uint32_t t25 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t26 = recomp_detail::sar<uint32_t>(ctx.eax, t25);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t25, t26);
    ctx.eax = static_cast<uint32_t>(t26);
    // 0x0043ec53: cmp edi, eax
    uint32_t t27 = static_cast<uint32_t>(ctx.edi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.eax, t27);
    // 0x0043ec55: jb 0x43ec5c
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043ec5c;
    goto bb_0043ec57;
}
bb_0043ec5c: {
    // 0x0043ec5c: mov ecx, dword ptr [esi + 0x6c]
    uint32_t t28 = static_cast<uint32_t>(ctx.esi + 0x0000006cu);
    uint32_t t29 = mem.r32(t28);
    ctx.ecx = static_cast<uint32_t>(t29);
    // 0x0043ec5f: test ecx, ecx
    uint32_t t30 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t30);
    // 0x0043ec61: mov edx, dword ptr [esi + 0x94]
    uint32_t t31 = static_cast<uint32_t>(ctx.esi + 0x00000094u);
    uint32_t t32 = mem.r32(t31);
    ctx.edx = static_cast<uint32_t>(t32);
    // 0x0043ec67: mov edi, dword ptr [edx + edi*4]
    uint32_t t33 = recomp_detail::shl<uint32_t>(ctx.edi, 0x00000002u);
    uint32_t t34 = static_cast<uint32_t>(ctx.edx + t33);
    uint32_t t35 = mem.r32(t34);
    ctx.edi = static_cast<uint32_t>(t35);
    // 0x0043ec6a: je 0x43ec9c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043ec9c;
    goto bb_0043ec6c;
}
bb_0043ec9c: {
    // 0x0043ec9c: pop edi
    uint32_t t36 = ctx.esp;
    uint32_t t37 = mem.r32(t36);
    uint32_t t38 = static_cast<uint32_t>(t36 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    ctx.edi = static_cast<uint32_t>(t37);
    // 0x0043ec9d: mov eax, ebx
    ctx.eax = static_cast<uint32_t>(ctx.ebx);
    // 0x0043ec9f: pop ebx
    uint32_t t39 = ctx.esp;
    uint32_t t40 = mem.r32(t39);
    uint32_t t41 = static_cast<uint32_t>(t39 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    ctx.ebx = static_cast<uint32_t>(t40);
    // 0x0043eca0: pop ecx
    uint32_t t42 = ctx.esp;
    uint32_t t43 = mem.r32(t42);
    uint32_t t44 = static_cast<uint32_t>(t42 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    ctx.ecx = static_cast<uint32_t>(t43);
    // 0x0043eca1: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043ec6c: {
    // 0x0043ec6c: mov eax, dword ptr [esi + 0x70]
    uint32_t t45 = static_cast<uint32_t>(ctx.esi + 0x00000070u);
    uint32_t t46 = mem.r32(t45);
    ctx.eax = static_cast<uint32_t>(t46);
    // 0x0043ec6f: sub eax, ecx
    uint32_t t47 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t47);
    ctx.eax = static_cast<uint32_t>(t47);
    // 0x0043ec71: sar eax, 2
    uint32_t t48 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t49 = recomp_detail::sar<uint32_t>(ctx.eax, t48);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t48, t49);
    ctx.eax = static_cast<uint32_t>(t49);
    // 0x0043ec74: cmp eax, edi
    uint32_t t50 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t50);
    // 0x0043ec76: jbe 0x43ec9c
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043ec9c;
}
{
    // 0x0043ec78: test ecx, ecx
    uint32_t t51 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t51);
    // 0x0043ec7a: je 0x43ec88
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043ec88;
    goto bb_0043ec7c;
}
bb_0043ec88: {
    // 0x0043ec88: call 0x4e0bf2
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, 0x0043ec8du);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043ec8d;
}
bb_0043ec7c: {
    // 0x0043ec7c: mov eax, dword ptr [esi + 0x70]
    uint32_t t53 = static_cast<uint32_t>(ctx.esi + 0x00000070u);
    uint32_t t54 = mem.r32(t53);
    ctx.eax = static_cast<uint32_t>(t54);
    // 0x0043ec7f: sub eax, ecx
    uint32_t t55 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t55);
    ctx.eax = static_cast<uint32_t>(t55);
    // 0x0043ec81: sar eax, 2
    uint32_t t56 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t57 = recomp_detail::sar<uint32_t>(ctx.eax, t56);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t56, t57);
    ctx.eax = static_cast<uint32_t>(t57);
    // 0x0043ec84: cmp edi, eax
    uint32_t t58 = static_cast<uint32_t>(ctx.edi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.eax, t58);
    // 0x0043ec86: jb 0x43ec8d
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043ec8d;
    goto bb_0043ec88;
}
bb_0043ec8d: {
    // 0x0043ec8d: mov eax, dword ptr [esi + 0x6c]
    uint32_t t59 = static_cast<uint32_t>(ctx.esi + 0x0000006cu);
    uint32_t t60 = mem.r32(t59);
    ctx.eax = static_cast<uint32_t>(t60);
    // 0x0043ec90: mov eax, dword ptr [eax + edi*4]
    uint32_t t61 = recomp_detail::shl<uint32_t>(ctx.edi, 0x00000002u);
    uint32_t t62 = static_cast<uint32_t>(ctx.eax + t61);
    uint32_t t63 = mem.r32(t62);
    ctx.eax = static_cast<uint32_t>(t63);
    // 0x0043ec93: pop edi
    uint32_t t64 = ctx.esp;
    uint32_t t65 = mem.r32(t64);
    uint32_t t66 = static_cast<uint32_t>(t64 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    ctx.edi = static_cast<uint32_t>(t65);
    // 0x0043ec94: pop ebx
    uint32_t t67 = ctx.esp;
    uint32_t t68 = mem.r32(t67);
    uint32_t t69 = static_cast<uint32_t>(t67 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    ctx.ebx = static_cast<uint32_t>(t68);
    // 0x0043ec95: pop ecx
    uint32_t t70 = ctx.esp;
    uint32_t t71 = mem.r32(t70);
    uint32_t t72 = static_cast<uint32_t>(t70 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    ctx.ecx = static_cast<uint32_t>(t71);
    // 0x0043ec96: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0043ecb0 | subsystem=Replay | canonical | 38 blocks | 332 insns
void sub_0043ecb0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043ecb0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0043ecb2: push 0x516c58
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00516c58u);
    // 0x0043ecb7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0043ecbd: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0043ecbe: sub esp, 0x60
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000060u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000060u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x0043ecc1: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0043ecc6: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0043ecc8: mov dword ptr [esp + 0x5c], eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    mem.w32(t8, ctx.eax);
    // 0x0043eccc: push ebx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ebx);
    // 0x0043eccd: push ebp
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.ebp);
    // 0x0043ecce: push esi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.esi);
    // 0x0043eccf: push edi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.edi);
    // 0x0043ecd0: mov eax, dword ptr [0x54b458]
    uint32_t t13 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0043ecd5: xor eax, esp
    uint32_t t14 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x0043ecd7: push eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.eax);
    // 0x0043ecd8: lea eax, [esp + 0x74]
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000074u);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0043ecdc: mov dword ptr fs:[0], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t17, ctx.eax);
    // 0x0043ece2: mov ebp, dword ptr [esp + 0x84]
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x00000084u);
    uint32_t t19 = mem.r32(t18);
    ctx.ebp = static_cast<uint32_t>(t19);
    // 0x0043ece9: cmp dword ptr [ebp + 0x80], 0
    uint32_t t20 = static_cast<uint32_t>(ctx.ebp + 0x00000080u);
    uint32_t t21 = mem.r32(t20);
    uint32_t t22 = static_cast<uint32_t>(t21 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t21, 0x00000000u, t22);
    // 0x0043ecf0: jne 0x43f11e
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043f11e;
    goto bb_0043ecf6;
}
bb_0043f11e: {
    // 0x0043f11e: xor eax, eax
    uint32_t t23 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t23);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x0043f120: mov ecx, dword ptr [esp + 0x74]
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x00000074u);
    uint32_t t25 = mem.r32(t24);
    ctx.ecx = static_cast<uint32_t>(t25);
    // 0x0043f124: mov dword ptr fs:[0], ecx
    uint32_t t26 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t26, ctx.ecx);
    // 0x0043f12b: pop ecx
    uint32_t t27 = ctx.esp;
    uint32_t t28 = mem.r32(t27);
    uint32_t t29 = static_cast<uint32_t>(t27 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    ctx.ecx = static_cast<uint32_t>(t28);
    // 0x0043f12c: pop edi
    uint32_t t30 = ctx.esp;
    uint32_t t31 = mem.r32(t30);
    uint32_t t32 = static_cast<uint32_t>(t30 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    ctx.edi = static_cast<uint32_t>(t31);
    // 0x0043f12d: pop esi
    uint32_t t33 = ctx.esp;
    uint32_t t34 = mem.r32(t33);
    uint32_t t35 = static_cast<uint32_t>(t33 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    ctx.esi = static_cast<uint32_t>(t34);
    // 0x0043f12e: pop ebp
    uint32_t t36 = ctx.esp;
    uint32_t t37 = mem.r32(t36);
    uint32_t t38 = static_cast<uint32_t>(t36 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    ctx.ebp = static_cast<uint32_t>(t37);
    // 0x0043f12f: pop ebx
    uint32_t t39 = ctx.esp;
    uint32_t t40 = mem.r32(t39);
    uint32_t t41 = static_cast<uint32_t>(t39 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    ctx.ebx = static_cast<uint32_t>(t40);
    // 0x0043f130: mov ecx, dword ptr [esp + 0x5c]
    uint32_t t42 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    uint32_t t43 = mem.r32(t42);
    ctx.ecx = static_cast<uint32_t>(t43);
    // 0x0043f134: xor ecx, esp
    uint32_t t44 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t44);
    ctx.ecx = static_cast<uint32_t>(t44);
    // 0x0043f136: call 0x4e02f8
    uint32_t t45 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    mem.w32(t45, 0x0043f13bu);
    hle_crt_004e02f8(ctx, mem);
    // 0x0043f13b: add esp, 0x6c
    uint32_t t46 = static_cast<uint32_t>(ctx.esp + 0x0000006cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000006cu, t46);
    ctx.esp = static_cast<uint32_t>(t46);
    // 0x0043f13e: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0043ecf6: {
    // 0x0043ecf6: mov esi, ebp
    ctx.esi = static_cast<uint32_t>(ctx.ebp);
    // 0x0043ecf8: call 0x43ec20
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, 0x0043ecfdu);
    sub_0043ec20(ctx, mem);
    // 0x0043ecfd: test eax, eax
    uint32_t t48 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t48);
    // 0x0043ecff: mov dword ptr [esp + 0x14], eax
    uint32_t t49 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t49, ctx.eax);
    // 0x0043ed03: je 0x43f11e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043f11e;
}
{
    // 0x0043ed09: push 0x15
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, 0x00000015u);
    // 0x0043ed0b: mov eax, 0x80
    ctx.eax = static_cast<uint32_t>(0x00000080u);
    // 0x0043ed10: mov edi, 0x400
    ctx.edi = static_cast<uint32_t>(0x00000400u);
    // 0x0043ed15: call 0x4bd1e0
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, 0x0043ed1au);
    sub_004bd1e0(ctx, mem);
    // 0x0043ed1a: mov esi, dword ptr [ebp + 0xc]
    uint32_t t52 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t53 = mem.r32(t52);
    ctx.esi = static_cast<uint32_t>(t53);
    // 0x0043ed1d: mov dword ptr [esp + 0x38], eax
    uint32_t t54 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    mem.w32(t54, ctx.eax);
    // 0x0043ed21: mov eax, dword ptr [eax]
    uint32_t t55 = mem.r32(ctx.eax);
    ctx.eax = static_cast<uint32_t>(t55);
    // 0x0043ed23: mov ebx, dword ptr [eax + 8]
    uint32_t t56 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    uint32_t t57 = mem.r32(t56);
    ctx.ebx = static_cast<uint32_t>(t57);
    // 0x0043ed26: add esp, 4
    uint32_t t58 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t58);
    ctx.esp = static_cast<uint32_t>(t58);
    // 0x0043ed29: call 0x49f090
    uint32_t t59 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    mem.w32(t59, 0x0043ed2eu);
    sub_0049f090(ctx, mem);
    // 0x0043ed2e: mov ecx, dword ptr [ebp + 0xc]
    uint32_t t60 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t61 = mem.r32(t60);
    ctx.ecx = static_cast<uint32_t>(t61);
    // 0x0043ed31: call 0x49f440
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, 0x0043ed36u);
    sub_0049f440(ctx, mem);
    // 0x0043ed36: mov esi, dword ptr [ebp + 0xc]
    uint32_t t63 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t64 = mem.r32(t63);
    ctx.esi = static_cast<uint32_t>(t64);
    // 0x0043ed39: call 0x43c3c0
    uint32_t t65 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t65);
    mem.w32(t65, 0x0043ed3eu);
    sub_0043c3c0(ctx, mem);
    // 0x0043ed3e: mov ebx, dword ptr [esp + 0x14]
    uint32_t t66 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t67 = mem.r32(t66);
    ctx.ebx = static_cast<uint32_t>(t67);
    // 0x0043ed42: mov eax, dword ptr [ebx + 4]
    uint32_t t68 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    uint32_t t69 = mem.r32(t68);
    ctx.eax = static_cast<uint32_t>(t69);
    // 0x0043ed45: cmp eax, -3
    uint32_t t70 = static_cast<uint32_t>(ctx.eax - 0xfffffffdu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xfffffffdu, t70);
    // 0x0043ed48: jne 0x43ed55
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043ed55;
    goto bb_0043ed4a;
}
bb_0043ed55: {
    // 0x0043ed55: cmp eax, -1
    uint32_t t71 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t71);
    // 0x0043ed58: jne 0x43ed9c
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043ed9c;
    goto bb_0043ed5a;
}
bb_0043ed4a: {
    // 0x0043ed4a: push 0
    uint32_t t72 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    mem.w32(t72, 0x00000000u);
    // 0x0043ed4c: push -1
    uint32_t t73 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    mem.w32(t73, 0xffffffffu);
    // 0x0043ed4e: push 0x7b42c9
    uint32_t t74 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    mem.w32(t74, 0x007b42c9u);
    // 0x0043ed53: jmp 0x43ed8e
    goto bb_0043ed8e;
}
bb_0043ed9c: {
    // 0x0043ed9c: xor edi, edi
    uint32_t t75 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t75);
    ctx.edi = static_cast<uint32_t>(t75);
    // 0x0043ed9e: cmp dword ptr [ebx], edi
    uint32_t t76 = mem.r32(ctx.ebx);
    uint32_t t77 = static_cast<uint32_t>(t76 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t76, ctx.edi, t77);
    // 0x0043eda0: jne 0x43f10c
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043f10c;
    goto bb_0043eda6;
}
bb_0043ed5a: {
    // 0x0043ed5a: cmp dword ptr [ebx], 0
    uint32_t t78 = mem.r32(ctx.ebx);
    uint32_t t79 = static_cast<uint32_t>(t78 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t78, 0x00000000u, t79);
    // 0x0043ed5d: je 0x43ed85
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043ed85;
    goto bb_0043ed5f;
}
bb_0043ed8e: {
    // 0x0043ed8e: mov esi, dword ptr [ebp + 0xc]
    uint32_t t80 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t81 = mem.r32(t80);
    ctx.esi = static_cast<uint32_t>(t81);
    goto bb_0043ed91;
}
bb_0043f10c: {
    // 0x0043f10c: mov esi, dword ptr [ebp + 0xc]
    uint32_t t82 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t83 = mem.r32(t82);
    ctx.esi = static_cast<uint32_t>(t83);
    // 0x0043f10f: call 0x43c420
    uint32_t t84 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    mem.w32(t84, 0x0043f114u);
    sub_0043c420(ctx, mem);
    // 0x0043f114: mov ecx, dword ptr [esp + 0x34]
    uint32_t t85 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    uint32_t t86 = mem.r32(t85);
    ctx.ecx = static_cast<uint32_t>(t86);
    // 0x0043f118: mov dword ptr [ebp + 0x80], ecx
    uint32_t t87 = static_cast<uint32_t>(ctx.ebp + 0x00000080u);
    mem.w32(t87, ctx.ecx);
    goto bb_0043f11e;
}
bb_0043eda6: {
    // 0x0043eda6: mov esi, 1
    ctx.esi = static_cast<uint32_t>(0x00000001u);
    // 0x0043edab: cmp dword ptr [ebx + 4], esi
    uint32_t t88 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    uint32_t t89 = mem.r32(t88);
    uint32_t t90 = static_cast<uint32_t>(t89 - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t89, ctx.esi, t90);
    // 0x0043edae: jne 0x43f10c
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043f10c;
    goto bb_0043edb4;
}
bb_0043ed85: {
    // 0x0043ed85: push 0
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, 0x00000000u);
    // 0x0043ed87: push -1
    uint32_t t92 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    mem.w32(t92, 0xffffffffu);
    // 0x0043ed89: push 0x7b4335
    uint32_t t93 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    mem.w32(t93, 0x007b4335u);
    goto bb_0043ed8e;
}
bb_0043ed5f: {
    // 0x0043ed5f: lea edi, [ebx + 8]
    uint32_t t94 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    ctx.edi = static_cast<uint32_t>(t94);
    // 0x0043ed62: mov ecx, 0x535318
    ctx.ecx = static_cast<uint32_t>(0x00535318u);
    // 0x0043ed67: call 0x42bdc0
    uint32_t t95 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t95);
    mem.w32(t95, 0x0043ed6cu);
    sub_0042bdc0(ctx, mem);
    // 0x0043ed6c: test al, al
    uint8_t t96 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t96);
    // 0x0043ed6e: mov esi, dword ptr [ebp + 0xc]
    uint32_t t97 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t98 = mem.r32(t97);
    ctx.esi = static_cast<uint32_t>(t98);
    // 0x0043ed71: push 0
    uint32_t t99 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t99);
    mem.w32(t99, 0x00000000u);
    // 0x0043ed73: push -1
    uint32_t t100 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t100);
    mem.w32(t100, 0xffffffffu);
    // 0x0043ed75: je 0x43ed7e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043ed7e;
    goto bb_0043ed77;
}
bb_0043ed91: {
    // 0x0043ed91: push 0
    uint32_t t101 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t101);
    mem.w32(t101, 0x00000000u);
    // 0x0043ed93: push 0
    uint32_t t102 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    mem.w32(t102, 0x00000000u);
    // 0x0043ed95: xor eax, eax
    uint32_t t103 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t103);
    ctx.eax = static_cast<uint32_t>(t103);
    // 0x0043ed97: call 0x49f280
    uint32_t t104 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t104);
    mem.w32(t104, 0x0043ed9cu);
    sub_0049f280(ctx, mem);
    goto bb_0043ed9c;
}
bb_0043edb4: {
    // 0x0043edb4: mov dword ptr [esp + 0x6c], 0xf
    uint32_t t105 = static_cast<uint32_t>(ctx.esp + 0x0000006cu);
    mem.w32(t105, 0x0000000fu);
    // 0x0043edbc: mov dword ptr [esp + 0x68], edi
    uint32_t t106 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    mem.w32(t106, ctx.edi);
    // 0x0043edc0: mov byte ptr [esp + 0x58], 0
    uint32_t t107 = static_cast<uint32_t>(ctx.esp + 0x00000058u);
    mem.w8(t107, uint8_t{0x00u});
    // 0x0043edc5: mov eax, 0x100
    ctx.eax = static_cast<uint32_t>(0x00000100u);
    // 0x0043edca: lea ecx, [esp + 0x54]
    uint32_t t108 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    ctx.ecx = static_cast<uint32_t>(t108);
    // 0x0043edce: mov dword ptr [esp + 0x7c], edi
    uint32_t t109 = static_cast<uint32_t>(ctx.esp + 0x0000007cu);
    mem.w32(t109, ctx.edi);
    // 0x0043edd2: call 0x4138c0
    uint32_t t110 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t110);
    mem.w32(t110, 0x0043edd7u);
    sub_004138c0(ctx, mem);
    // 0x0043edd7: mov ebx, dword ptr [ebx + 0x40]
    uint32_t t111 = static_cast<uint32_t>(ctx.ebx + 0x00000040u);
    uint32_t t112 = mem.r32(t111);
    ctx.ebx = static_cast<uint32_t>(t112);
    // 0x0043edda: cmp ebx, edi
    uint32_t t113 = static_cast<uint32_t>(ctx.ebx - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.edi, t113);
    // 0x0043eddc: jne 0x43ee31
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043ee31;
    goto bb_0043edde;
}
bb_0043ed7e: {
    // 0x0043ed7e: push 0x7b431f
    uint32_t t114 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t114);
    mem.w32(t114, 0x007b431fu);
    // 0x0043ed83: jmp 0x43ed91
    goto bb_0043ed91;
}
bb_0043ed77: {
    // 0x0043ed77: push 0x7b42e7
    uint32_t t115 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t115);
    mem.w32(t115, 0x007b42e7u);
    // 0x0043ed7c: jmp 0x43ed91
    goto bb_0043ed91;
}
bb_0043ee31: {
    // 0x0043ee31: mov edx, dword ptr [esp + 0x14]
    uint32_t t116 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t117 = mem.r32(t116);
    ctx.edx = static_cast<uint32_t>(t117);
    // 0x0043ee35: cmp dword ptr [edx + 4], esi
    uint32_t t118 = static_cast<uint32_t>(ctx.edx + 0x00000004u);
    uint32_t t119 = mem.r32(t118);
    uint32_t t120 = static_cast<uint32_t>(t119 - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t119, ctx.esi, t120);
    // 0x0043ee38: jne 0x43f0fb
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043f0fb;
    goto bb_0043ee3e;
}
bb_0043edde: {
    // 0x0043edde: push 0x387
    uint32_t t121 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t121);
    mem.w32(t121, 0x00000387u);
    // 0x0043ede3: push 0x536ab8
    uint32_t t122 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t122);
    mem.w32(t122, 0x00536ab8u);
    // 0x0043ede8: push 4
    uint32_t t123 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t123);
    mem.w32(t123, 0x00000004u);
    // 0x0043edea: push 0x5c
    uint32_t t124 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t124);
    mem.w32(t124, 0x0000005cu);
    // 0x0043edec: call 0x4e0675
    uint32_t t125 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t125);
    mem.w32(t125, 0x0043edf1u);
    hle_crt_004e0675(ctx, mem);
    // 0x0043edf1: add esp, 0x10
    uint32_t t126 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t126);
    ctx.esp = static_cast<uint32_t>(t126);
    // 0x0043edf4: cmp eax, edi
    uint32_t t127 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t127);
    // 0x0043edf6: je 0x43edff
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043edff;
    goto bb_0043edf8;
}
bb_0043f0fb: {
    // 0x0043f0fb: lea ecx, [esp + 0x54]
    uint32_t t128 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    ctx.ecx = static_cast<uint32_t>(t128);
    // 0x0043f0ff: mov dword ptr [esp + 0x7c], 0xffffffff
    uint32_t t129 = static_cast<uint32_t>(ctx.esp + 0x0000007cu);
    mem.w32(t129, 0xffffffffu);
    // 0x0043f107: call 0x407850
    uint32_t t130 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t130);
    mem.w32(t130, 0x0043f10cu);
    sub_00407850(ctx, mem);
    goto bb_0043f10c;
}
bb_0043ee3e: {
    // 0x0043ee3e: lea eax, [esp + 0x54]
    uint32_t t131 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    ctx.eax = static_cast<uint32_t>(t131);
    // 0x0043ee42: push eax
    uint32_t t132 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t132);
    mem.w32(t132, ctx.eax);
    // 0x0043ee43: mov edx, 0x534f8a
    ctx.edx = static_cast<uint32_t>(0x00534f8au);
    // 0x0043ee48: call 0x410c60
    uint32_t t133 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t133);
    mem.w32(t133, 0x0043ee4du);
    sub_00410c60(ctx, mem);
    // 0x0043ee4d: cmp dword ptr [ebx + 0x3c], edi
    uint32_t t134 = static_cast<uint32_t>(ctx.ebx + 0x0000003cu);
    uint32_t t135 = mem.r32(t134);
    uint32_t t136 = static_cast<uint32_t>(t135 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t135, ctx.edi, t136);
    // 0x0043ee50: je 0x43ee61
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043ee61;
    goto bb_0043ee52;
}
bb_0043edff: {
    // 0x0043edff: xor eax, eax
    uint32_t t137 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t137);
    ctx.eax = static_cast<uint32_t>(t137);
    goto bb_0043ee01;
}
bb_0043edf8: {
    // 0x0043edf8: call 0x43c4b0
    uint32_t t138 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t138);
    mem.w32(t138, 0x0043edfdu);
    sub_0043c4b0(ctx, mem);
    // 0x0043edfd: jmp 0x43ee01
    goto bb_0043ee01;
}
bb_0043ee61: {
    // 0x0043ee61: mov ecx, dword ptr [ebx + 0x40]
    uint32_t t139 = static_cast<uint32_t>(ctx.ebx + 0x00000040u);
    uint32_t t140 = mem.r32(t139);
    ctx.ecx = static_cast<uint32_t>(t140);
    // 0x0043ee64: lea edx, [esp + 0x18]
    uint32_t t141 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.edx = static_cast<uint32_t>(t141);
    // 0x0043ee68: push edx
    uint32_t t142 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t142);
    mem.w32(t142, ctx.edx);
    // 0x0043ee69: call 0x43de20
    uint32_t t143 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t143);
    mem.w32(t143, 0x0043ee6eu);
    sub_0043de20(ctx, mem);
    // 0x0043ee6e: add esp, 4
    uint32_t t144 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t144);
    ctx.esp = static_cast<uint32_t>(t144);
    // 0x0043ee71: push edi
    uint32_t t145 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t145);
    mem.w32(t145, ctx.edi);
    // 0x0043ee72: push eax
    uint32_t t146 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t146);
    mem.w32(t146, ctx.eax);
    // 0x0043ee73: or eax, 0xffffffff
    uint32_t t147 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t147);
    ctx.eax = static_cast<uint32_t>(t147);
    // 0x0043ee76: lea esi, [esp + 0x5c]
    uint32_t t148 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    ctx.esi = static_cast<uint32_t>(t148);
    // 0x0043ee7a: mov byte ptr [esp + 0x84], 1
    uint32_t t149 = static_cast<uint32_t>(ctx.esp + 0x00000084u);
    mem.w8(t149, uint8_t{0x01u});
    // 0x0043ee82: call 0x414360
    uint32_t t150 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t150);
    mem.w32(t150, 0x0043ee87u);
    sub_00414360(ctx, mem);
    // 0x0043ee87: lea ecx, [esp + 0x18]
    uint32_t t151 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.ecx = static_cast<uint32_t>(t151);
    // 0x0043ee8b: mov byte ptr [esp + 0x7c], 0
    uint32_t t152 = static_cast<uint32_t>(ctx.esp + 0x0000007cu);
    mem.w8(t152, uint8_t{0x00u});
    // 0x0043ee90: call 0x407850
    uint32_t t153 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t153);
    mem.w32(t153, 0x0043ee95u);
    sub_00407850(ctx, mem);
    // 0x0043ee95: mov eax, dword ptr [ebx + 0x44]
    uint32_t t154 = static_cast<uint32_t>(ctx.ebx + 0x00000044u);
    uint32_t t155 = mem.r32(t154);
    ctx.eax = static_cast<uint32_t>(t155);
    // 0x0043ee98: push eax
    uint32_t t156 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t156);
    mem.w32(t156, ctx.eax);
    // 0x0043ee99: lea edi, [esp + 0x1c]
    uint32_t t157 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.edi = static_cast<uint32_t>(t157);
    // 0x0043ee9d: call 0x43e960
    uint32_t t158 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t158);
    mem.w32(t158, 0x0043eea2u);
    sub_0043e960(ctx, mem);
    // 0x0043eea2: add esp, 4
    uint32_t t159 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t159);
    ctx.esp = static_cast<uint32_t>(t159);
    // 0x0043eea5: push 0
    uint32_t t160 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t160);
    mem.w32(t160, 0x00000000u);
    // 0x0043eea7: push eax
    uint32_t t161 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t161);
    mem.w32(t161, ctx.eax);
    // 0x0043eea8: or eax, 0xffffffff
    uint32_t t162 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t162);
    ctx.eax = static_cast<uint32_t>(t162);
    // 0x0043eeab: mov byte ptr [esp + 0x84], 2
    uint32_t t163 = static_cast<uint32_t>(ctx.esp + 0x00000084u);
    mem.w8(t163, uint8_t{0x02u});
    // 0x0043eeb3: call 0x414360
    uint32_t t164 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t164);
    mem.w32(t164, 0x0043eeb8u);
    sub_00414360(ctx, mem);
    // 0x0043eeb8: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x0043eeba: mov byte ptr [esp + 0x7c], 0
    uint32_t t165 = static_cast<uint32_t>(ctx.esp + 0x0000007cu);
    mem.w8(t165, uint8_t{0x00u});
    // 0x0043eebf: call 0x407850
    uint32_t t166 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t166);
    mem.w32(t166, 0x0043eec4u);
    sub_00407850(ctx, mem);
    // 0x0043eec4: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x0043eec6: push ecx
    uint32_t t167 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t167);
    mem.w32(t167, ctx.ecx);
    // 0x0043eec7: mov edx, 0x536f48
    ctx.edx = static_cast<uint32_t>(0x00536f48u);
    // 0x0043eecc: call 0x414340
    uint32_t t168 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t168);
    mem.w32(t168, 0x0043eed1u);
    sub_00414340(ctx, mem);
    // 0x0043eed1: cmp dword ptr [ebx + 0x4c], 0
    uint32_t t169 = static_cast<uint32_t>(ctx.ebx + 0x0000004cu);
    uint32_t t170 = mem.r32(t169);
    uint32_t t171 = static_cast<uint32_t>(t170 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t170, 0x00000000u, t171);
    // 0x0043eed5: je 0x43eee4
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043eee4;
    goto bb_0043eed7;
}
bb_0043ee52: {
    // 0x0043ee52: lea ecx, [esp + 0x54]
    uint32_t t172 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    ctx.ecx = static_cast<uint32_t>(t172);
    // 0x0043ee56: push ecx
    uint32_t t173 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t173);
    mem.w32(t173, ctx.ecx);
    // 0x0043ee57: mov edx, 0x536f40
    ctx.edx = static_cast<uint32_t>(0x00536f40u);
    // 0x0043ee5c: call 0x414340
    uint32_t t174 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t174);
    mem.w32(t174, 0x0043ee61u);
    sub_00414340(ctx, mem);
    goto bb_0043ee61;
}
bb_0043ee01: {
    // 0x0043ee01: mov esi, dword ptr [esp + 0x14]
    uint32_t t175 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t176 = mem.r32(t175);
    ctx.esi = static_cast<uint32_t>(t176);
    // 0x0043ee05: mov dword ptr [esi + 0x40], eax
    uint32_t t177 = static_cast<uint32_t>(ctx.esi + 0x00000040u);
    mem.w32(t177, ctx.eax);
    // 0x0043ee08: lea eax, [esi + 0x24]
    uint32_t t178 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    ctx.eax = static_cast<uint32_t>(t178);
    // 0x0043ee0b: xor edi, edi
    uint32_t t179 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t179);
    ctx.edi = static_cast<uint32_t>(t179);
    // 0x0043ee0d: call 0x413890
    uint32_t t180 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t180);
    mem.w32(t180, 0x0043ee12u);
    sub_00413890(ctx, mem);
    // 0x0043ee12: mov ecx, dword ptr [esi + 0x40]
    uint32_t t181 = static_cast<uint32_t>(ctx.esi + 0x00000040u);
    uint32_t t182 = mem.r32(t181);
    ctx.ecx = static_cast<uint32_t>(t182);
    // 0x0043ee15: push ecx
    uint32_t t183 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t183);
    mem.w32(t183, ctx.ecx);
    // 0x0043ee16: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x0043ee18: call 0x445580
    uint32_t t184 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t184);
    mem.w32(t184, 0x0043ee1du);
    sub_00445580(ctx, mem);
    // 0x0043ee1d: test eax, eax
    uint32_t t185 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t185);
    // 0x0043ee1f: jne 0x43f0fb
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043f0fb;
    goto bb_0043ee25;
}
bb_0043eee4: {
    // 0x0043eee4: mov ecx, dword ptr [ebx + 0x50]
    uint32_t t186 = static_cast<uint32_t>(ctx.ebx + 0x00000050u);
    uint32_t t187 = mem.r32(t186);
    ctx.ecx = static_cast<uint32_t>(t187);
    // 0x0043eee7: lea eax, [esp + 0x18]
    uint32_t t188 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.eax = static_cast<uint32_t>(t188);
    // 0x0043eeeb: push eax
    uint32_t t189 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t189);
    mem.w32(t189, ctx.eax);
    // 0x0043eeec: call 0x43de20
    uint32_t t190 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t190);
    mem.w32(t190, 0x0043eef1u);
    sub_0043de20(ctx, mem);
    // 0x0043eef1: add esp, 4
    uint32_t t191 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t191);
    ctx.esp = static_cast<uint32_t>(t191);
    // 0x0043eef4: push 0
    uint32_t t192 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t192);
    mem.w32(t192, 0x00000000u);
    // 0x0043eef6: push eax
    uint32_t t193 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t193);
    mem.w32(t193, ctx.eax);
    // 0x0043eef7: or eax, 0xffffffff
    uint32_t t194 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t194);
    ctx.eax = static_cast<uint32_t>(t194);
    // 0x0043eefa: lea esi, [esp + 0x5c]
    uint32_t t195 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    ctx.esi = static_cast<uint32_t>(t195);
    // 0x0043eefe: mov byte ptr [esp + 0x84], 3
    uint32_t t196 = static_cast<uint32_t>(ctx.esp + 0x00000084u);
    mem.w8(t196, uint8_t{0x03u});
    // 0x0043ef06: call 0x414360
    uint32_t t197 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t197);
    mem.w32(t197, 0x0043ef0bu);
    sub_00414360(ctx, mem);
    // 0x0043ef0b: lea ecx, [esp + 0x18]
    uint32_t t198 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.ecx = static_cast<uint32_t>(t198);
    // 0x0043ef0f: mov byte ptr [esp + 0x7c], 0
    uint32_t t199 = static_cast<uint32_t>(ctx.esp + 0x0000007cu);
    mem.w8(t199, uint8_t{0x00u});
    // 0x0043ef14: call 0x407850
    uint32_t t200 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t200);
    mem.w32(t200, 0x0043ef19u);
    sub_00407850(ctx, mem);
    // 0x0043ef19: mov ecx, dword ptr [ebx + 0x54]
    uint32_t t201 = static_cast<uint32_t>(ctx.ebx + 0x00000054u);
    uint32_t t202 = mem.r32(t201);
    ctx.ecx = static_cast<uint32_t>(t202);
    // 0x0043ef1c: push ecx
    uint32_t t203 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t203);
    mem.w32(t203, ctx.ecx);
    // 0x0043ef1d: lea edi, [esp + 0x1c]
    uint32_t t204 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.edi = static_cast<uint32_t>(t204);
    // 0x0043ef21: call 0x43e960
    uint32_t t205 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t205);
    mem.w32(t205, 0x0043ef26u);
    sub_0043e960(ctx, mem);
    // 0x0043ef26: add esp, 4
    uint32_t t206 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t206);
    ctx.esp = static_cast<uint32_t>(t206);
    // 0x0043ef29: push 0
    uint32_t t207 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t207);
    mem.w32(t207, 0x00000000u);
    // 0x0043ef2b: push eax
    uint32_t t208 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t208);
    mem.w32(t208, ctx.eax);
    // 0x0043ef2c: or eax, 0xffffffff
    uint32_t t209 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t209);
    ctx.eax = static_cast<uint32_t>(t209);
    // 0x0043ef2f: mov byte ptr [esp + 0x84], 4
    uint32_t t210 = static_cast<uint32_t>(ctx.esp + 0x00000084u);
    mem.w8(t210, uint8_t{0x04u});
    // 0x0043ef37: call 0x414360
    uint32_t t211 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t211);
    mem.w32(t211, 0x0043ef3cu);
    sub_00414360(ctx, mem);
    // 0x0043ef3c: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x0043ef3e: mov byte ptr [esp + 0x7c], 0
    uint32_t t212 = static_cast<uint32_t>(ctx.esp + 0x0000007cu);
    mem.w8(t212, uint8_t{0x00u});
    // 0x0043ef43: call 0x407850
    uint32_t t213 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t213);
    mem.w32(t213, 0x0043ef48u);
    sub_00407850(ctx, mem);
    // 0x0043ef48: push 0
    uint32_t t214 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t214);
    mem.w32(t214, 0x00000000u);
    // 0x0043ef4a: push -1
    uint32_t t215 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t215);
    mem.w32(t215, 0xffffffffu);
    // 0x0043ef4c: xor edi, edi
    uint32_t t216 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t216);
    ctx.edi = static_cast<uint32_t>(t216);
    // 0x0043ef4e: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0043ef50: call 0x413890
    uint32_t t217 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t217);
    mem.w32(t217, 0x0043ef55u);
    sub_00413890(ctx, mem);
    // 0x0043ef55: mov esi, dword ptr [ebp + 0xc]
    uint32_t t218 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t219 = mem.r32(t218);
    ctx.esi = static_cast<uint32_t>(t219);
    // 0x0043ef58: push eax
    uint32_t t220 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t220);
    mem.w32(t220, ctx.eax);
    // 0x0043ef59: push edi
    uint32_t t221 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t221);
    mem.w32(t221, ctx.edi);
    // 0x0043ef5a: push edi
    uint32_t t222 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t222);
    mem.w32(t222, ctx.edi);
    // 0x0043ef5b: xor eax, eax
    uint32_t t223 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t223);
    ctx.eax = static_cast<uint32_t>(t223);
    // 0x0043ef5d: call 0x49f280
    uint32_t t224 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t224);
    mem.w32(t224, 0x0043ef62u);
    sub_0049f280(ctx, mem);
    // 0x0043ef62: mov eax, dword ptr [ebx + 0x34]
    uint32_t t225 = static_cast<uint32_t>(ctx.ebx + 0x00000034u);
    uint32_t t226 = mem.r32(t225);
    ctx.eax = static_cast<uint32_t>(t226);
    // 0x0043ef65: cmp eax, 1
    uint32_t t227 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t227);
    // 0x0043ef68: lea esi, [esp + 0x18]
    uint32_t t228 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.esi = static_cast<uint32_t>(t228);
    // 0x0043ef6c: jne 0x43ef83
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043ef83;
    goto bb_0043ef6e;
}
bb_0043eed7: {
    // 0x0043eed7: mov edx, esi
    ctx.edx = static_cast<uint32_t>(ctx.esi);
    // 0x0043eed9: push edx
    uint32_t t229 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t229);
    mem.w32(t229, ctx.edx);
    // 0x0043eeda: mov edx, 0x536f40
    ctx.edx = static_cast<uint32_t>(0x00536f40u);
    // 0x0043eedf: call 0x414340
    uint32_t t230 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t230);
    mem.w32(t230, 0x0043eee4u);
    sub_00414340(ctx, mem);
    goto bb_0043eee4;
}
bb_0043ee25: {
    // 0x0043ee25: mov dword ptr [esi + 4], 0xffffffff
    uint32_t t231 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t231, 0xffffffffu);
    // 0x0043ee2c: jmp 0x43f0fb
    goto bb_0043f0fb;
}
bb_0043ef83: {
    // 0x0043ef83: push eax
    uint32_t t232 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t232);
    mem.w32(t232, ctx.eax);
    // 0x0043ef84: push 0x7b4368
    uint32_t t233 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t233);
    mem.w32(t233, 0x007b4368u);
    // 0x0043ef89: call 0x4c1ec0
    uint32_t t234 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t234);
    mem.w32(t234, 0x0043ef8eu);
    sub_004c1ec0(ctx, mem);
    // 0x0043ef8e: add esp, 8
    uint32_t t235 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t235);
    ctx.esp = static_cast<uint32_t>(t235);
    // 0x0043ef91: mov byte ptr [esp + 0x7c], 6
    uint32_t t236 = static_cast<uint32_t>(ctx.esp + 0x0000007cu);
    mem.w8(t236, uint8_t{0x06u});
    goto bb_0043ef96;
}
bb_0043ef6e: {
    // 0x0043ef6e: push eax
    uint32_t t237 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t237);
    mem.w32(t237, ctx.eax);
    // 0x0043ef6f: push 0x7b4359
    uint32_t t238 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t238);
    mem.w32(t238, 0x007b4359u);
    // 0x0043ef74: call 0x4c1ec0
    uint32_t t239 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t239);
    mem.w32(t239, 0x0043ef79u);
    sub_004c1ec0(ctx, mem);
    // 0x0043ef79: add esp, 8
    uint32_t t240 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t240);
    ctx.esp = static_cast<uint32_t>(t240);
    // 0x0043ef7c: mov byte ptr [esp + 0x7c], 5
    uint32_t t241 = static_cast<uint32_t>(ctx.esp + 0x0000007cu);
    mem.w8(t241, uint8_t{0x05u});
    // 0x0043ef81: jmp 0x43ef96
}
bb_0043ef96: {
    // 0x0043ef96: push -1
    uint32_t t242 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t242);
    mem.w32(t242, 0xffffffffu);
    // 0x0043ef98: push 0
    uint32_t t243 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t243);
    mem.w32(t243, 0x00000000u);
    // 0x0043ef9a: push eax
    uint32_t t244 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t244);
    mem.w32(t244, ctx.eax);
    // 0x0043ef9b: lea ecx, [esp + 0x60]
    uint32_t t245 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    ctx.ecx = static_cast<uint32_t>(t245);
    // 0x0043ef9f: call 0x4079d0
    uint32_t t246 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t246);
    mem.w32(t246, 0x0043efa4u);
    sub_004079d0(ctx, mem);
    // 0x0043efa4: lea ecx, [esp + 0x18]
    uint32_t t247 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.ecx = static_cast<uint32_t>(t247);
    // 0x0043efa8: mov byte ptr [esp + 0x7c], 0
    uint32_t t248 = static_cast<uint32_t>(ctx.esp + 0x0000007cu);
    mem.w8(t248, uint8_t{0x00u});
    // 0x0043efad: call 0x407850
    uint32_t t249 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t249);
    mem.w32(t249, 0x0043efb2u);
    sub_00407850(ctx, mem);
    // 0x0043efb2: push 0
    uint32_t t250 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t250);
    mem.w32(t250, 0x00000000u);
    // 0x0043efb4: push -1
    uint32_t t251 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t251);
    mem.w32(t251, 0xffffffffu);
    // 0x0043efb6: xor edi, edi
    uint32_t t252 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t252);
    ctx.edi = static_cast<uint32_t>(t252);
    // 0x0043efb8: lea eax, [esp + 0x5c]
    uint32_t t253 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    ctx.eax = static_cast<uint32_t>(t253);
    // 0x0043efbc: call 0x413890
    uint32_t t254 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t254);
    mem.w32(t254, 0x0043efc1u);
    sub_00413890(ctx, mem);
    // 0x0043efc1: mov esi, dword ptr [ebp + 0xc]
    uint32_t t255 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t256 = mem.r32(t255);
    ctx.esi = static_cast<uint32_t>(t256);
    // 0x0043efc4: push eax
    uint32_t t257 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t257);
    mem.w32(t257, ctx.eax);
    // 0x0043efc5: push 0x14
    uint32_t t258 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t258);
    mem.w32(t258, 0x00000014u);
    // 0x0043efc7: push edi
    uint32_t t259 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t259);
    mem.w32(t259, ctx.edi);
    // 0x0043efc8: xor eax, eax
    uint32_t t260 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t260);
    ctx.eax = static_cast<uint32_t>(t260);
    // 0x0043efca: call 0x49f280
    uint32_t t261 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t261);
    mem.w32(t261, 0x0043efcfu);
    sub_0049f280(ctx, mem);
    // 0x0043efcf: mov eax, dword ptr [ebx + 0x30]
    uint32_t t262 = static_cast<uint32_t>(ctx.ebx + 0x00000030u);
    uint32_t t263 = mem.r32(t262);
    ctx.eax = static_cast<uint32_t>(t263);
    // 0x0043efd2: test eax, eax
    uint32_t t264 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t264);
    // 0x0043efd4: jl 0x43efdb
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0043efdb;
    goto bb_0043efd6;
}
bb_0043efdb: {
    // 0x0043efdb: mov eax, 5
    ctx.eax = static_cast<uint32_t>(0x00000005u);
    goto bb_0043efe0;
}
bb_0043efd6: {
    // 0x0043efd6: cmp eax, 4
    uint32_t t265 = static_cast<uint32_t>(ctx.eax - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000004u, t265);
    // 0x0043efd9: jle 0x43efe0
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0043efe0;
    goto bb_0043efdb;
}
bb_0043efe0: {
    // 0x0043efe0: mov ecx, dword ptr [ebx + 0x38]
    uint32_t t266 = static_cast<uint32_t>(ctx.ebx + 0x00000038u);
    uint32_t t267 = mem.r32(t266);
    ctx.ecx = static_cast<uint32_t>(t267);
    // 0x0043efe3: test ecx, ecx
    uint32_t t268 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t268);
    // 0x0043efe5: jl 0x43efec
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0043efec;
    goto bb_0043efe7;
}
bb_0043efec: {
    // 0x0043efec: mov eax, 5
    ctx.eax = static_cast<uint32_t>(0x00000005u);
    goto bb_0043eff1;
}
bb_0043efe7: {
    // 0x0043efe7: cmp ecx, 4
    uint32_t t269 = static_cast<uint32_t>(ctx.ecx - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000004u, t269);
    // 0x0043efea: jle 0x43eff1
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0043eff1;
    goto bb_0043efec;
}
bb_0043eff1: {
    // 0x0043eff1: mov esi, 0x536f70
    ctx.esi = static_cast<uint32_t>(0x00536f70u);
    // 0x0043eff6: mov edx, 0x534f8a
    ctx.edx = static_cast<uint32_t>(0x00534f8au);
    // 0x0043effb: mov edi, 0x5362f8
    ctx.edi = static_cast<uint32_t>(0x005362f8u);
    // 0x0043f000: mov dword ptr [esp + 0x30], edx
    uint32_t t270 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    mem.w32(t270, ctx.edx);
    // 0x0043f004: mov dword ptr [esp + 0x4c], esi
    uint32_t t271 = static_cast<uint32_t>(ctx.esp + 0x0000004cu);
    mem.w32(t271, ctx.esi);
    // 0x0043f008: mov dword ptr [esp + 0x50], edx
    uint32_t t272 = static_cast<uint32_t>(ctx.esp + 0x00000050u);
    mem.w32(t272, ctx.edx);
    // 0x0043f00c: mov dword ptr [esp + 0x2c], esi
    uint32_t t273 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    mem.w32(t273, ctx.esi);
    // 0x0043f010: mov dword ptr [esp + 0x38], 0x5363ac
    uint32_t t274 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    mem.w32(t274, 0x005363acu);
    // 0x0043f018: mov dword ptr [esp + 0x3c], 0x5363c0
    uint32_t t275 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    mem.w32(t275, 0x005363c0u);
    // 0x0043f020: mov dword ptr [esp + 0x40], edi
    uint32_t t276 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    mem.w32(t276, ctx.edi);
    // 0x0043f024: mov dword ptr [esp + 0x44], 0x5363d8
    uint32_t t277 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    mem.w32(t277, 0x005363d8u);
    // 0x0043f02c: mov dword ptr [esp + 0x48], 0x5363ec
    uint32_t t278 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    mem.w32(t278, 0x005363ecu);
    // 0x0043f034: mov edx, dword ptr [esp + ecx*4 + 0x38]
    uint32_t t279 = recomp_detail::shl<uint32_t>(ctx.ecx, 0x00000002u);
    uint32_t t280 = static_cast<uint32_t>(ctx.esp + t279);
    uint32_t t281 = static_cast<uint32_t>(t280 + 0x00000038u);
    uint32_t t282 = mem.r32(t281);
    ctx.edx = static_cast<uint32_t>(t282);
    // 0x0043f038: mov dword ptr [esp + 0x18], 0x536334
    uint32_t t283 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t283, 0x00536334u);
    // 0x0043f040: mov dword ptr [esp + 0x1c], 0x53633c
    uint32_t t284 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t284, 0x0053633cu);
    // 0x0043f048: mov dword ptr [esp + 0x20], edi
    uint32_t t285 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t285, ctx.edi);
    // 0x0043f04c: mov dword ptr [esp + 0x24], 0x536340
    uint32_t t286 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t286, 0x00536340u);
    // 0x0043f054: mov dword ptr [esp + 0x28], 0x536348
    uint32_t t287 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t287, 0x00536348u);
    // 0x0043f05c: mov eax, dword ptr [esp + eax*4 + 0x18]
    uint32_t t288 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000002u);
    uint32_t t289 = static_cast<uint32_t>(ctx.esp + t288);
    uint32_t t290 = static_cast<uint32_t>(t289 + 0x00000018u);
    uint32_t t291 = mem.r32(t290);
    ctx.eax = static_cast<uint32_t>(t291);
    // 0x0043f060: push edx
    uint32_t t292 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t292);
    mem.w32(t292, ctx.edx);
    // 0x0043f061: push eax
    uint32_t t293 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t293);
    mem.w32(t293, ctx.eax);
    // 0x0043f062: push 0x536f74
    uint32_t t294 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t294);
    mem.w32(t294, 0x00536f74u);
    // 0x0043f067: lea esi, [esp + 0x24]
    uint32_t t295 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    ctx.esi = static_cast<uint32_t>(t295);
    // 0x0043f06b: call 0x4c1ec0
    uint32_t t296 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t296);
    mem.w32(t296, 0x0043f070u);
    sub_004c1ec0(ctx, mem);
    // 0x0043f070: add esp, 0xc
    uint32_t t297 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t297);
    ctx.esp = static_cast<uint32_t>(t297);
    // 0x0043f073: push -1
    uint32_t t298 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t298);
    mem.w32(t298, 0xffffffffu);
    // 0x0043f075: push 0
    uint32_t t299 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t299);
    mem.w32(t299, 0x00000000u);
    // 0x0043f077: push eax
    uint32_t t300 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t300);
    mem.w32(t300, ctx.eax);
    // 0x0043f078: lea ecx, [esp + 0x60]
    uint32_t t301 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    ctx.ecx = static_cast<uint32_t>(t301);
    // 0x0043f07c: mov byte ptr [esp + 0x88], 7
    uint32_t t302 = static_cast<uint32_t>(ctx.esp + 0x00000088u);
    mem.w8(t302, uint8_t{0x07u});
    // 0x0043f084: call 0x4079d0
    uint32_t t303 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t303);
    mem.w32(t303, 0x0043f089u);
    sub_004079d0(ctx, mem);
    // 0x0043f089: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x0043f08b: mov byte ptr [esp + 0x7c], 0
    uint32_t t304 = static_cast<uint32_t>(ctx.esp + 0x0000007cu);
    mem.w8(t304, uint8_t{0x00u});
    // 0x0043f090: call 0x407850
    uint32_t t305 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t305);
    mem.w32(t305, 0x0043f095u);
    sub_00407850(ctx, mem);
    // 0x0043f095: push 0
    uint32_t t306 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t306);
    mem.w32(t306, 0x00000000u);
    // 0x0043f097: push -1
    uint32_t t307 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t307);
    mem.w32(t307, 0xffffffffu);
    // 0x0043f099: xor edi, edi
    uint32_t t308 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t308);
    ctx.edi = static_cast<uint32_t>(t308);
    // 0x0043f09b: lea eax, [esp + 0x5c]
    uint32_t t309 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    ctx.eax = static_cast<uint32_t>(t309);
    // 0x0043f09f: call 0x413890
    uint32_t t310 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t310);
    mem.w32(t310, 0x0043f0a4u);
    sub_00413890(ctx, mem);
    // 0x0043f0a4: mov esi, dword ptr [ebp + 0xc]
    uint32_t t311 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t312 = mem.r32(t311);
    ctx.esi = static_cast<uint32_t>(t312);
    // 0x0043f0a7: push eax
    uint32_t t313 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t313);
    mem.w32(t313, ctx.eax);
    // 0x0043f0a8: push 0x28
    uint32_t t314 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t314);
    mem.w32(t314, 0x00000028u);
    // 0x0043f0aa: push edi
    uint32_t t315 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t315);
    mem.w32(t315, ctx.edi);
    // 0x0043f0ab: xor eax, eax
    uint32_t t316 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t316);
    ctx.eax = static_cast<uint32_t>(t316);
    // 0x0043f0ad: call 0x49f280
    uint32_t t317 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t317);
    mem.w32(t317, 0x0043f0b2u);
    sub_0049f280(ctx, mem);
    // 0x0043f0b2: lea eax, [ebx + 0x18]
    uint32_t t318 = static_cast<uint32_t>(ctx.ebx + 0x00000018u);
    ctx.eax = static_cast<uint32_t>(t318);
    // 0x0043f0b5: lea ecx, [esp + 0x18]
    uint32_t t319 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.ecx = static_cast<uint32_t>(t319);
    // 0x0043f0b9: call 0x43c470
    uint32_t t320 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t320);
    mem.w32(t320, 0x0043f0beu);
    sub_0043c470(ctx, mem);
    // 0x0043f0be: push -1
    uint32_t t321 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t321);
    mem.w32(t321, 0xffffffffu);
    // 0x0043f0c0: push edi
    uint32_t t322 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t322);
    mem.w32(t322, ctx.edi);
    // 0x0043f0c1: push eax
    uint32_t t323 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t323);
    mem.w32(t323, ctx.eax);
    // 0x0043f0c2: lea ecx, [esp + 0x60]
    uint32_t t324 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    ctx.ecx = static_cast<uint32_t>(t324);
    // 0x0043f0c6: mov byte ptr [esp + 0x88], 8
    uint32_t t325 = static_cast<uint32_t>(ctx.esp + 0x00000088u);
    mem.w8(t325, uint8_t{0x08u});
    // 0x0043f0ce: call 0x4079d0
    uint32_t t326 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t326);
    mem.w32(t326, 0x0043f0d3u);
    sub_004079d0(ctx, mem);
    // 0x0043f0d3: lea ecx, [esp + 0x18]
    uint32_t t327 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.ecx = static_cast<uint32_t>(t327);
    // 0x0043f0d7: mov byte ptr [esp + 0x7c], 0
    uint32_t t328 = static_cast<uint32_t>(ctx.esp + 0x0000007cu);
    mem.w8(t328, uint8_t{0x00u});
    // 0x0043f0dc: call 0x407850
    uint32_t t329 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t329);
    mem.w32(t329, 0x0043f0e1u);
    sub_00407850(ctx, mem);
    // 0x0043f0e1: push edi
    uint32_t t330 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t330);
    mem.w32(t330, ctx.edi);
    // 0x0043f0e2: push -1
    uint32_t t331 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t331);
    mem.w32(t331, 0xffffffffu);
    // 0x0043f0e4: lea eax, [esp + 0x5c]
    uint32_t t332 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    ctx.eax = static_cast<uint32_t>(t332);
    // 0x0043f0e8: call 0x413890
    uint32_t t333 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t333);
    mem.w32(t333, 0x0043f0edu);
    sub_00413890(ctx, mem);
    // 0x0043f0ed: mov esi, dword ptr [ebp + 0xc]
    uint32_t t334 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t335 = mem.r32(t334);
    ctx.esi = static_cast<uint32_t>(t335);
    // 0x0043f0f0: push eax
    uint32_t t336 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t336);
    mem.w32(t336, ctx.eax);
    // 0x0043f0f1: push 0x3c
    uint32_t t337 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t337);
    mem.w32(t337, 0x0000003cu);
    // 0x0043f0f3: push edi
    uint32_t t338 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t338);
    mem.w32(t338, ctx.edi);
    // 0x0043f0f4: xor eax, eax
    uint32_t t339 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t339);
    ctx.eax = static_cast<uint32_t>(t339);
    // 0x0043f0f6: call 0x49f280
    uint32_t t340 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t340);
    mem.w32(t340, 0x0043f0fbu);
    sub_0049f280(ctx, mem);
    goto bb_0043f0fb;
}
}

// sub_0043f280 | subsystem=Replay | canonical | 9 blocks | 97 insns
void sub_0043f280(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043f280: sub esp, 8
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000008u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000008u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x0043f283: push ebx
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebx);
    // 0x0043f284: push ebp
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebp);
    // 0x0043f285: push esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.esi);
    // 0x0043f286: mov ebx, eax
    ctx.ebx = static_cast<uint32_t>(ctx.eax);
    // 0x0043f288: push edi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.edi);
    // 0x0043f289: mov esi, ebx
    ctx.esi = static_cast<uint32_t>(ctx.ebx);
    // 0x0043f28b: call 0x43ec20
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, 0x0043f290u);
    sub_0043ec20(ctx, mem);
    // 0x0043f290: test eax, eax
    uint32_t t6 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t6);
    // 0x0043f292: je 0x43f3b5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043f3b5;
    goto bb_0043f298;
}
bb_0043f3b5: {
    // 0x0043f3b5: pop edi
    uint32_t t7 = ctx.esp;
    uint32_t t8 = mem.r32(t7);
    uint32_t t9 = static_cast<uint32_t>(t7 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    ctx.edi = static_cast<uint32_t>(t8);
    // 0x0043f3b6: pop esi
    uint32_t t10 = ctx.esp;
    uint32_t t11 = mem.r32(t10);
    uint32_t t12 = static_cast<uint32_t>(t10 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    ctx.esi = static_cast<uint32_t>(t11);
    // 0x0043f3b7: pop ebp
    uint32_t t13 = ctx.esp;
    uint32_t t14 = mem.r32(t13);
    uint32_t t15 = static_cast<uint32_t>(t13 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    ctx.ebp = static_cast<uint32_t>(t14);
    // 0x0043f3b8: pop ebx
    uint32_t t16 = ctx.esp;
    uint32_t t17 = mem.r32(t16);
    uint32_t t18 = static_cast<uint32_t>(t16 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    ctx.ebx = static_cast<uint32_t>(t17);
    // 0x0043f3b9: add esp, 8
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t19);
    ctx.esp = static_cast<uint32_t>(t19);
    // 0x0043f3bc: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0043f298: {
    // 0x0043f298: cmp dword ptr [eax], 0
    uint32_t t20 = mem.r32(ctx.eax);
    uint32_t t21 = static_cast<uint32_t>(t20 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t20, 0x00000000u, t21);
    // 0x0043f29b: jne 0x43f3b5
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043f3b5;
}
{
    // 0x0043f2a1: cmp dword ptr [eax + 4], 1
    uint32_t t22 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t23 = mem.r32(t22);
    uint32_t t24 = static_cast<uint32_t>(t23 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t23, 0x00000001u, t24);
    // 0x0043f2a5: jne 0x43f3b5
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043f3b5;
}
{
    // 0x0043f2ab: mov eax, dword ptr [eax + 0x40]
    uint32_t t25 = static_cast<uint32_t>(ctx.eax + 0x00000040u);
    uint32_t t26 = mem.r32(t25);
    ctx.eax = static_cast<uint32_t>(t26);
    // 0x0043f2ae: mov ebp, dword ptr [eax + 0x40]
    uint32_t t27 = static_cast<uint32_t>(ctx.eax + 0x00000040u);
    uint32_t t28 = mem.r32(t27);
    ctx.ebp = static_cast<uint32_t>(t28);
    // 0x0043f2b1: mov eax, dword ptr [eax + 0x50]
    uint32_t t29 = static_cast<uint32_t>(ctx.eax + 0x00000050u);
    uint32_t t30 = mem.r32(t29);
    ctx.eax = static_cast<uint32_t>(t30);
    // 0x0043f2b4: lea esi, [ebx + 0xb4]
    uint32_t t31 = static_cast<uint32_t>(ctx.ebx + 0x000000b4u);
    ctx.esi = static_cast<uint32_t>(t31);
    // 0x0043f2ba: mov edi, ebp
    ctx.edi = static_cast<uint32_t>(ctx.ebp);
    // 0x0043f2bc: mov dword ptr [esp + 0x10], eax
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t32, ctx.eax);
    // 0x0043f2c0: call 0x440090
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x0043f2c5u);
    sub_00440090(ctx, mem);
    // 0x0043f2c5: or dword ptr [eax], 1
    uint32_t t34 = mem.r32(ctx.eax);
    uint32_t t35 = static_cast<uint32_t>(t34 | 0x00000001u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t35);
    mem.w32(ctx.eax, t35);
    // 0x0043f2c8: call 0x440090
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, 0x0043f2cdu);
    sub_00440090(ctx, mem);
    // 0x0043f2cd: or dword ptr [eax], 2
    uint32_t t37 = mem.r32(ctx.eax);
    uint32_t t38 = static_cast<uint32_t>(t37 | 0x00000002u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t38);
    mem.w32(ctx.eax, t38);
    // 0x0043f2d0: call 0x440090
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, 0x0043f2d5u);
    sub_00440090(ctx, mem);
    // 0x0043f2d5: cmp dword ptr [eax + 4], 0
    uint32_t t40 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t41 = mem.r32(t40);
    uint32_t t42 = static_cast<uint32_t>(t41 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t41, 0x00000000u, t42);
    // 0x0043f2d9: je 0x43f3b5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043f3b5;
}
{
    // 0x0043f2df: mov edi, dword ptr [esp + 0x10]
    uint32_t t43 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t44 = mem.r32(t43);
    ctx.edi = static_cast<uint32_t>(t44);
    // 0x0043f2e3: call 0x440090
    uint32_t t45 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    mem.w32(t45, 0x0043f2e8u);
    sub_00440090(ctx, mem);
    // 0x0043f2e8: cmp dword ptr [eax + 8], 0
    uint32_t t46 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    uint32_t t47 = mem.r32(t46);
    uint32_t t48 = static_cast<uint32_t>(t47 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t47, 0x00000000u, t48);
    // 0x0043f2ec: je 0x43f3b5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043f3b5;
}
{
    // 0x0043f2f2: fld dword ptr [esp + 0x1c]
    uint32_t t49 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    double t50 = static_cast<double>(mem.rf32(t49));
    ctx.fpu_push(t50);
    // 0x0043f2f6: fld qword ptr [0x53d9f8]
    double t51 = mem.rf64(0x0053d9f8u);
    ctx.fpu_push(t51);
    // 0x0043f2fc: fmul st(1)
    double t52 = ctx.fpu_st(0);
    double t53 = ctx.fpu_st(1);
    double t54 = (t52 * t53);
    ctx.fpu_st(0) = t54;
    // 0x0043f2fe: call 0x4f49f0
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, 0x0043f303u);
    hle_crt_004f49f0(ctx, mem);
    // 0x0043f303: fld qword ptr [0x53daa8]
    double t56 = mem.rf64(0x0053daa8u);
    ctx.fpu_push(t56);
    // 0x0043f309: fmul st(1)
    double t57 = ctx.fpu_st(0);
    double t58 = ctx.fpu_st(1);
    double t59 = (t57 * t58);
    ctx.fpu_st(0) = t59;
    // 0x0043f30b: mov dword ptr [esp + 0x1c], eax
    uint32_t t60 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t60, ctx.eax);
    // 0x0043f30f: call 0x4f49f0
    uint32_t t61 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    mem.w32(t61, 0x0043f314u);
    hle_crt_004f49f0(ctx, mem);
    // 0x0043f314: fld1
    ctx.fpu_push(1.0);
    // 0x0043f316: fucompp
    double t62 = ctx.fpu_st(0);
    double t63 = ctx.fpu_st(1);
    ctx.fpu_compare(t62, t63);
    ctx.fpu_pop();
    ctx.fpu_pop();
    // 0x0043f318: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x0043f31a: mov dword ptr [esp + 0x14], ecx
    uint32_t t64 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t64, ctx.ecx);
    // 0x0043f31e: fnstsw ax
    recomp_detail::w16(ctx.eax, static_cast<uint16_t>(ctx.fpu_sw));
    // 0x0043f320: test ah, 0x44
    uint8_t t65 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8h(ctx.eax)) & static_cast<uint32_t>(uint8_t{0x44u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t65);
    // 0x0043f323: jnp 0x43f32c
    if (recomp_detail::eval_cond(ctx, Cond::NP)) goto bb_0043f32c;
    goto bb_0043f325;
}
bb_0043f32c: {
    // 0x0043f32c: mov eax, dword ptr [ebx + 8]
    uint32_t t66 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t67 = mem.r32(t66);
    ctx.eax = static_cast<uint32_t>(t67);
    // 0x0043f32f: fild dword ptr [esp + 0x1c]
    uint32_t t68 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    double t69 = static_cast<double>(static_cast<int32_t>(mem.r32(t68)));
    ctx.fpu_push(t69);
    // 0x0043f333: push eax
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, ctx.eax);
    // 0x0043f334: push 0
    uint32_t t71 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t71);
    mem.w32(t71, 0x00000000u);
    // 0x0043f336: fmul qword ptr [0x53dc38]
    double t72 = ctx.fpu_st(0);
    double t73 = mem.rf64(0x0053dc38u);
    double t74 = (t72 * t73);
    ctx.fpu_st(0) = t74;
    // 0x0043f33c: push -1
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, 0xffffffffu);
    // 0x0043f33e: push 0x40
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    mem.w32(t76, 0x00000040u);
    // 0x0043f340: push 0x80
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, 0x00000080u);
    // 0x0043f345: push 0
    uint32_t t78 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    mem.w32(t78, 0x00000000u);
    // 0x0043f347: push 0
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, 0x00000000u);
    // 0x0043f349: push ecx
    uint32_t t80 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    mem.w32(t80, ctx.ecx);
    // 0x0043f34a: push 0x16c
    uint32_t t81 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    mem.w32(t81, 0x0000016cu);
    // 0x0043f34f: call 0x4f49f0
    uint32_t t82 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t82);
    mem.w32(t82, 0x0043f354u);
    hle_crt_004f49f0(ctx, mem);
    // 0x0043f354: mov ecx, 0x19c
    ctx.ecx = static_cast<uint32_t>(0x0000019cu);
    // 0x0043f359: sub ecx, eax
    uint32_t t83 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t83);
    ctx.ecx = static_cast<uint32_t>(t83);
    // 0x0043f35b: push ecx
    uint32_t t84 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    mem.w32(t84, ctx.ecx);
    // 0x0043f35c: call 0x440090
    uint32_t t85 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t85);
    mem.w32(t85, 0x0043f361u);
    sub_00440090(ctx, mem);
    // 0x0043f361: mov edx, dword ptr [eax + 8]
    uint32_t t86 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    uint32_t t87 = mem.r32(t86);
    ctx.edx = static_cast<uint32_t>(t87);
    // 0x0043f364: push edx
    uint32_t t88 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t88);
    mem.w32(t88, ctx.edx);
    // 0x0043f365: mov edx, dword ptr [esp + 0x48]
    uint32_t t89 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    uint32_t t90 = mem.r32(t89);
    ctx.edx = static_cast<uint32_t>(t90);
    // 0x0043f369: push 0
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, 0x00000000u);
    // 0x0043f36b: call 0x415580
    uint32_t t92 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    mem.w32(t92, 0x0043f370u);
    sub_00415580(ctx, mem);
    // 0x0043f370: mov ebx, dword ptr [ebx + 8]
    uint32_t t93 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t94 = mem.r32(t93);
    ctx.ebx = static_cast<uint32_t>(t94);
    // 0x0043f373: mov eax, dword ptr [esp + 0x44]
    uint32_t t95 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    uint32_t t96 = mem.r32(t95);
    ctx.eax = static_cast<uint32_t>(t96);
    // 0x0043f377: add esp, 0x30
    uint32_t t97 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000030u, t97);
    ctx.esp = static_cast<uint32_t>(t97);
    // 0x0043f37a: push ebx
    uint32_t t98 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t98);
    mem.w32(t98, ctx.ebx);
    // 0x0043f37b: push 0
    uint32_t t99 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t99);
    mem.w32(t99, 0x00000000u);
    // 0x0043f37d: push -1
    uint32_t t100 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t100);
    mem.w32(t100, 0xffffffffu);
    // 0x0043f37f: push 0x40
    uint32_t t101 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t101);
    mem.w32(t101, 0x00000040u);
    // 0x0043f381: push 0x80
    uint32_t t102 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    mem.w32(t102, 0x00000080u);
    // 0x0043f386: push 0
    uint32_t t103 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    mem.w32(t103, 0x00000000u);
    // 0x0043f388: push 0
    uint32_t t104 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t104);
    mem.w32(t104, 0x00000000u);
    // 0x0043f38a: push eax
    uint32_t t105 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t105);
    mem.w32(t105, ctx.eax);
    // 0x0043f38b: push 0x16c
    uint32_t t106 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t106);
    mem.w32(t106, 0x0000016cu);
    // 0x0043f390: push 0x19c
    uint32_t t107 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t107);
    mem.w32(t107, 0x0000019cu);
    // 0x0043f395: mov edi, ebp
    ctx.edi = static_cast<uint32_t>(ctx.ebp);
    // 0x0043f397: call 0x440090
    uint32_t t108 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t108);
    mem.w32(t108, 0x0043f39cu);
    sub_00440090(ctx, mem);
    // 0x0043f39c: mov ecx, dword ptr [eax + 4]
    uint32_t t109 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t110 = mem.r32(t109);
    ctx.ecx = static_cast<uint32_t>(t110);
    // 0x0043f39f: mov edx, dword ptr [esp + 0x44]
    uint32_t t111 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    uint32_t t112 = mem.r32(t111);
    ctx.edx = static_cast<uint32_t>(t112);
    // 0x0043f3a3: push ecx
    uint32_t t113 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t113);
    mem.w32(t113, ctx.ecx);
    // 0x0043f3a4: push 0
    uint32_t t114 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t114);
    mem.w32(t114, 0x00000000u);
    // 0x0043f3a6: call 0x415580
    uint32_t t115 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t115);
    mem.w32(t115, 0x0043f3abu);
    sub_00415580(ctx, mem);
    // 0x0043f3ab: add esp, 0x30
    uint32_t t116 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000030u, t116);
    ctx.esp = static_cast<uint32_t>(t116);
    // 0x0043f3ae: mov byte ptr [0x56447f], 1
    mem.w8(0x0056447fu, uint8_t{0x01u});
    goto bb_0043f3b5;
}
bb_0043f325: {
    // 0x0043f325: mov byte ptr [0x56447f], 2
    mem.w8(0x0056447fu, uint8_t{0x02u});
    goto bb_0043f32c;
}
}

// sub_0043f710 | subsystem=Replay | canonical | 19 blocks | 145 insns
void sub_0043f710(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043f710: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0043f712: push 0x5184d8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005184d8u);
    // 0x0043f717: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0043f71d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0043f71e: sub esp, 0x44
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000044u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000044u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x0043f721: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0043f726: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0043f728: mov dword ptr [esp + 0x40], eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    mem.w32(t8, ctx.eax);
    // 0x0043f72c: push ebx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ebx);
    // 0x0043f72d: push ebp
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.ebp);
    // 0x0043f72e: push esi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.esi);
    // 0x0043f72f: push edi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.edi);
    // 0x0043f730: mov eax, dword ptr [0x54b458]
    uint32_t t13 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0043f735: xor eax, esp
    uint32_t t14 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x0043f737: push eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.eax);
    // 0x0043f738: lea eax, [esp + 0x58]
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000058u);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0043f73c: mov dword ptr fs:[0], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t17, ctx.eax);
    // 0x0043f742: mov edi, ecx
    ctx.edi = static_cast<uint32_t>(ctx.ecx);
    // 0x0043f744: mov ebp, dword ptr [esp + 0x6c]
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x0000006cu);
    uint32_t t19 = mem.r32(t18);
    ctx.ebp = static_cast<uint32_t>(t19);
    // 0x0043f748: cmp edi, 0x63
    uint32_t t20 = static_cast<uint32_t>(ctx.edi - 0x00000063u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, 0x00000063u, t20);
    // 0x0043f74b: mov eax, dword ptr [esp + 0x68]
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    uint32_t t22 = mem.r32(t21);
    ctx.eax = static_cast<uint32_t>(t22);
    // 0x0043f74f: ja 0x43f8cc
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_0043f8cc;
    goto bb_0043f755;
}
bb_0043f8cc: {
    // 0x0043f8cc: xor eax, eax
    uint32_t t23 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t23);
    ctx.eax = static_cast<uint32_t>(t23);
    goto bb_0043f8ce;
}
bb_0043f755: {
    // 0x0043f755: lea ebx, [eax + 0xb4]
    uint32_t t24 = static_cast<uint32_t>(ctx.eax + 0x000000b4u);
    ctx.ebx = static_cast<uint32_t>(t24);
    // 0x0043f75b: mov eax, dword ptr [ebx + 4]
    uint32_t t25 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    uint32_t t26 = mem.r32(t25);
    ctx.eax = static_cast<uint32_t>(t26);
    // 0x0043f75e: test eax, eax
    uint32_t t27 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t27);
    // 0x0043f760: je 0x43f77c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043f77c;
    goto bb_0043f762;
}
bb_0043f8ce: {
    // 0x0043f8ce: mov ecx, dword ptr [esp + 0x58]
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x00000058u);
    uint32_t t29 = mem.r32(t28);
    ctx.ecx = static_cast<uint32_t>(t29);
    // 0x0043f8d2: mov dword ptr fs:[0], ecx
    uint32_t t30 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t30, ctx.ecx);
    // 0x0043f8d9: pop ecx
    uint32_t t31 = ctx.esp;
    uint32_t t32 = mem.r32(t31);
    uint32_t t33 = static_cast<uint32_t>(t31 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    ctx.ecx = static_cast<uint32_t>(t32);
    // 0x0043f8da: pop edi
    uint32_t t34 = ctx.esp;
    uint32_t t35 = mem.r32(t34);
    uint32_t t36 = static_cast<uint32_t>(t34 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    ctx.edi = static_cast<uint32_t>(t35);
    // 0x0043f8db: pop esi
    uint32_t t37 = ctx.esp;
    uint32_t t38 = mem.r32(t37);
    uint32_t t39 = static_cast<uint32_t>(t37 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    ctx.esi = static_cast<uint32_t>(t38);
    // 0x0043f8dc: pop ebp
    uint32_t t40 = ctx.esp;
    uint32_t t41 = mem.r32(t40);
    uint32_t t42 = static_cast<uint32_t>(t40 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    ctx.ebp = static_cast<uint32_t>(t41);
    // 0x0043f8dd: pop ebx
    uint32_t t43 = ctx.esp;
    uint32_t t44 = mem.r32(t43);
    uint32_t t45 = static_cast<uint32_t>(t43 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    ctx.ebx = static_cast<uint32_t>(t44);
    // 0x0043f8de: mov ecx, dword ptr [esp + 0x40]
    uint32_t t46 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t47 = mem.r32(t46);
    ctx.ecx = static_cast<uint32_t>(t47);
    // 0x0043f8e2: xor ecx, esp
    uint32_t t48 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t48);
    ctx.ecx = static_cast<uint32_t>(t48);
    // 0x0043f8e4: call 0x4e02f8
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, 0x0043f8e9u);
    hle_crt_004e02f8(ctx, mem);
    // 0x0043f8e9: add esp, 0x50
    uint32_t t50 = static_cast<uint32_t>(ctx.esp + 0x00000050u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000050u, t50);
    ctx.esp = static_cast<uint32_t>(t50);
    // 0x0043f8ec: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
bb_0043f77c: {
    // 0x0043f77c: call 0x4e0bf2
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, 0x0043f781u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043f781;
}
bb_0043f762: {
    // 0x0043f762: mov ecx, dword ptr [ebx + 8]
    uint32_t t52 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t53 = mem.r32(t52);
    ctx.ecx = static_cast<uint32_t>(t53);
    // 0x0043f765: sub ecx, eax
    uint32_t t54 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t54);
    ctx.ecx = static_cast<uint32_t>(t54);
    // 0x0043f767: mov eax, 0x66666667
    ctx.eax = static_cast<uint32_t>(0x66666667u);
    // 0x0043f76c: imul ecx
    uint64_t t55 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t56 = static_cast<uint32_t>(t55);
    uint32_t t57 = static_cast<uint32_t>(t55 >> 32);
    ctx.eax = static_cast<uint32_t>(t56);
    ctx.edx = static_cast<uint32_t>(t57);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t55);
    // 0x0043f76e: sar edx, 3
    uint32_t t58 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t59 = recomp_detail::sar<uint32_t>(ctx.edx, t58);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t58, t59);
    ctx.edx = static_cast<uint32_t>(t59);
    // 0x0043f771: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x0043f773: shr eax, 0x1f
    uint32_t t60 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t61 = recomp_detail::shr<uint32_t>(ctx.eax, t60);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t60, t61);
    ctx.eax = static_cast<uint32_t>(t61);
    // 0x0043f776: add eax, edx
    uint32_t t62 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t62);
    ctx.eax = static_cast<uint32_t>(t62);
    // 0x0043f778: cmp edi, eax
    uint32_t t63 = static_cast<uint32_t>(ctx.edi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.eax, t63);
    // 0x0043f77a: jb 0x43f781
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043f781;
    goto bb_0043f77c;
}
bb_0043f781: {
    // 0x0043f781: mov edx, dword ptr [ebx + 4]
    uint32_t t64 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    uint32_t t65 = mem.r32(t64);
    ctx.edx = static_cast<uint32_t>(t65);
    // 0x0043f784: mov esi, 1
    ctx.esi = static_cast<uint32_t>(0x00000001u);
    // 0x0043f789: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x0043f78b: shl esi, cl
    uint32_t t66 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t67 = static_cast<uint32_t>(t66 & 0x0000001fu);
    uint32_t t68 = recomp_detail::shl<uint32_t>(ctx.esi, t67);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.esi, t67, t68);
    ctx.esi = static_cast<uint32_t>(t68);
    // 0x0043f78d: lea eax, [edi + edi*4]
    uint32_t t69 = recomp_detail::shl<uint32_t>(ctx.edi, 0x00000002u);
    uint32_t t70 = static_cast<uint32_t>(ctx.edi + t69);
    ctx.eax = static_cast<uint32_t>(t70);
    // 0x0043f790: test dword ptr [edx + eax*4], esi
    uint32_t t71 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000002u);
    uint32_t t72 = static_cast<uint32_t>(ctx.edx + t71);
    uint32_t t73 = mem.r32(t72);
    uint32_t t74 = static_cast<uint32_t>(t73 & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t74);
    // 0x0043f793: je 0x43f8cc
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043f8cc;
}
{
    // 0x0043f799: xor eax, eax
    uint32_t t75 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t75);
    ctx.eax = static_cast<uint32_t>(t75);
    // 0x0043f79b: mov dword ptr [esp + 0x18], eax
    uint32_t t76 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t76, ctx.eax);
    // 0x0043f79f: mov dword ptr [esp + 0x50], 0xf
    uint32_t t77 = static_cast<uint32_t>(ctx.esp + 0x00000050u);
    mem.w32(t77, 0x0000000fu);
    // 0x0043f7a7: mov dword ptr [esp + 0x4c], eax
    uint32_t t78 = static_cast<uint32_t>(ctx.esp + 0x0000004cu);
    mem.w32(t78, ctx.eax);
    // 0x0043f7ab: mov byte ptr [esp + 0x3c], al
    uint32_t t79 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    mem.w8(t79, recomp_detail::r8l(ctx.eax));
    // 0x0043f7af: mov esi, ebx
    ctx.esi = static_cast<uint32_t>(ctx.ebx);
    // 0x0043f7b1: mov dword ptr [esp + 0x60], eax
    uint32_t t80 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    mem.w32(t80, ctx.eax);
    // 0x0043f7b5: call 0x440090
    uint32_t t81 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    mem.w32(t81, 0x0043f7bau);
    sub_00440090(ctx, mem);
    // 0x0043f7ba: cmp dword ptr [eax + ebp*4 + 4], 0
    uint32_t t82 = recomp_detail::shl<uint32_t>(ctx.ebp, 0x00000002u);
    uint32_t t83 = static_cast<uint32_t>(ctx.eax + t82);
    uint32_t t84 = static_cast<uint32_t>(t83 + 0x00000004u);
    uint32_t t85 = mem.r32(t84);
    uint32_t t86 = static_cast<uint32_t>(t85 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t85, 0x00000000u, t86);
    // 0x0043f7bf: jne 0x43f832
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043f832;
    goto bb_0043f7c1;
}
bb_0043f832: {
    // 0x0043f832: mov esi, ebx
    ctx.esi = static_cast<uint32_t>(ctx.ebx);
    // 0x0043f834: call 0x440090
    uint32_t t87 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t87);
    mem.w32(t87, 0x0043f839u);
    sub_00440090(ctx, mem);
    // 0x0043f839: cmp dword ptr [eax + ebp*4 + 0xc], 0
    uint32_t t88 = recomp_detail::shl<uint32_t>(ctx.ebp, 0x00000002u);
    uint32_t t89 = static_cast<uint32_t>(ctx.eax + t88);
    uint32_t t90 = static_cast<uint32_t>(t89 + 0x0000000cu);
    uint32_t t91 = mem.r32(t90);
    uint32_t t92 = static_cast<uint32_t>(t91 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t91, 0x00000000u, t92);
    // 0x0043f83e: jne 0x43f8b0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043f8b0;
    goto bb_0043f840;
}
bb_0043f7c1: {
    // 0x0043f7c1: push edi
    uint32_t t93 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    mem.w32(t93, ctx.edi);
    // 0x0043f7c2: lea eax, [ebp + 1]
    uint32_t t94 = static_cast<uint32_t>(ctx.ebp + 0x00000001u);
    ctx.eax = static_cast<uint32_t>(t94);
    // 0x0043f7c5: push eax
    uint32_t t95 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t95);
    mem.w32(t95, ctx.eax);
    // 0x0043f7c6: push 0x536f98
    uint32_t t96 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    mem.w32(t96, 0x00536f98u);
    // 0x0043f7cb: push 0x536fb0
    uint32_t t97 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t97);
    mem.w32(t97, 0x00536fb0u);
    // 0x0043f7d0: lea esi, [esp + 0x2c]
    uint32_t t98 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    ctx.esi = static_cast<uint32_t>(t98);
    // 0x0043f7d4: call 0x4c1ec0
    uint32_t t99 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t99);
    mem.w32(t99, 0x0043f7d9u);
    sub_004c1ec0(ctx, mem);
    // 0x0043f7d9: add esp, 0x10
    uint32_t t100 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t100);
    ctx.esp = static_cast<uint32_t>(t100);
    // 0x0043f7dc: push -1
    uint32_t t101 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t101);
    mem.w32(t101, 0xffffffffu);
    // 0x0043f7de: push 0
    uint32_t t102 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    mem.w32(t102, 0x00000000u);
    // 0x0043f7e0: push eax
    uint32_t t103 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    mem.w32(t103, ctx.eax);
    // 0x0043f7e1: lea ecx, [esp + 0x44]
    uint32_t t104 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    ctx.ecx = static_cast<uint32_t>(t104);
    // 0x0043f7e5: mov byte ptr [esp + 0x6c], 1
    uint32_t t105 = static_cast<uint32_t>(ctx.esp + 0x0000006cu);
    mem.w8(t105, uint8_t{0x01u});
    // 0x0043f7ea: call 0x4079d0
    uint32_t t106 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t106);
    mem.w32(t106, 0x0043f7efu);
    sub_004079d0(ctx, mem);
    // 0x0043f7ef: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x0043f7f1: mov byte ptr [esp + 0x60], 0
    uint32_t t107 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    mem.w8(t107, uint8_t{0x00u});
    // 0x0043f7f6: call 0x407850
    uint32_t t108 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t108);
    mem.w32(t108, 0x0043f7fbu);
    sub_00407850(ctx, mem);
    // 0x0043f7fb: cmp dword ptr [esp + 0x50], 0x10
    uint32_t t109 = static_cast<uint32_t>(ctx.esp + 0x00000050u);
    uint32_t t110 = mem.r32(t109);
    uint32_t t111 = static_cast<uint32_t>(t110 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t110, 0x00000010u, t111);
    // 0x0043f800: mov eax, dword ptr [esp + 0x3c]
    uint32_t t112 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    uint32_t t113 = mem.r32(t112);
    ctx.eax = static_cast<uint32_t>(t113);
    // 0x0043f804: jae 0x43f80a
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0043f80a;
    goto bb_0043f806;
}
bb_0043f8b0: {
    // 0x0043f8b0: mov esi, dword ptr [esp + 0x18]
    uint32_t t114 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t115 = mem.r32(t114);
    ctx.esi = static_cast<uint32_t>(t115);
    goto bb_0043f8b4;
}
bb_0043f840: {
    // 0x0043f840: push edi
    uint32_t t116 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t116);
    mem.w32(t116, ctx.edi);
    // 0x0043f841: lea edx, [ebp + 1]
    uint32_t t117 = static_cast<uint32_t>(ctx.ebp + 0x00000001u);
    ctx.edx = static_cast<uint32_t>(t117);
    // 0x0043f844: push edx
    uint32_t t118 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    mem.w32(t118, ctx.edx);
    // 0x0043f845: push 0x536fc4
    uint32_t t119 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t119);
    mem.w32(t119, 0x00536fc4u);
    // 0x0043f84a: push 0x536fdc
    uint32_t t120 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t120);
    mem.w32(t120, 0x00536fdcu);
    // 0x0043f84f: lea esi, [esp + 0x2c]
    uint32_t t121 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    ctx.esi = static_cast<uint32_t>(t121);
    // 0x0043f853: call 0x4c1ec0
    uint32_t t122 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t122);
    mem.w32(t122, 0x0043f858u);
    sub_004c1ec0(ctx, mem);
    // 0x0043f858: add esp, 0x10
    uint32_t t123 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t123);
    ctx.esp = static_cast<uint32_t>(t123);
    // 0x0043f85b: push -1
    uint32_t t124 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t124);
    mem.w32(t124, 0xffffffffu);
    // 0x0043f85d: push 0
    uint32_t t125 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t125);
    mem.w32(t125, 0x00000000u);
    // 0x0043f85f: push eax
    uint32_t t126 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t126);
    mem.w32(t126, ctx.eax);
    // 0x0043f860: lea ecx, [esp + 0x44]
    uint32_t t127 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    ctx.ecx = static_cast<uint32_t>(t127);
    // 0x0043f864: mov byte ptr [esp + 0x6c], 2
    uint32_t t128 = static_cast<uint32_t>(ctx.esp + 0x0000006cu);
    mem.w8(t128, uint8_t{0x02u});
    // 0x0043f869: call 0x4079d0
    uint32_t t129 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t129);
    mem.w32(t129, 0x0043f86eu);
    sub_004079d0(ctx, mem);
    // 0x0043f86e: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x0043f870: mov byte ptr [esp + 0x60], 0
    uint32_t t130 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    mem.w8(t130, uint8_t{0x00u});
    // 0x0043f875: call 0x407850
    uint32_t t131 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t131);
    mem.w32(t131, 0x0043f87au);
    sub_00407850(ctx, mem);
    // 0x0043f87a: cmp dword ptr [esp + 0x50], 0x10
    uint32_t t132 = static_cast<uint32_t>(ctx.esp + 0x00000050u);
    uint32_t t133 = mem.r32(t132);
    uint32_t t134 = static_cast<uint32_t>(t133 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t133, 0x00000010u, t134);
    // 0x0043f87f: mov eax, dword ptr [esp + 0x3c]
    uint32_t t135 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    uint32_t t136 = mem.r32(t135);
    ctx.eax = static_cast<uint32_t>(t136);
    // 0x0043f883: jae 0x43f889
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0043f889;
    goto bb_0043f885;
}
bb_0043f80a: {
    // 0x0043f80a: push eax
    uint32_t t137 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t137);
    mem.w32(t137, ctx.eax);
    // 0x0043f80b: xor eax, eax
    uint32_t t138 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t138);
    ctx.eax = static_cast<uint32_t>(t138);
    // 0x0043f80d: xor ecx, ecx
    uint32_t t139 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t139);
    ctx.ecx = static_cast<uint32_t>(t139);
    // 0x0043f80f: call 0x4c8aa0
    uint32_t t140 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t140);
    mem.w32(t140, 0x0043f814u);
    sub_004c8aa0(ctx, mem);
    // 0x0043f814: add esp, 4
    uint32_t t141 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t141);
    ctx.esp = static_cast<uint32_t>(t141);
    // 0x0043f817: mov esi, ebx
    ctx.esi = static_cast<uint32_t>(ctx.ebx);
    // 0x0043f819: mov dword ptr [esp + 0x18], eax
    uint32_t t142 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t142, ctx.eax);
    // 0x0043f81d: call 0x440090
    uint32_t t143 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t143);
    mem.w32(t143, 0x0043f822u);
    sub_00440090(ctx, mem);
    // 0x0043f822: mov ecx, dword ptr [esp + 0x18]
    uint32_t t144 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t145 = mem.r32(t144);
    ctx.ecx = static_cast<uint32_t>(t145);
    // 0x0043f826: mov dword ptr [eax + ebp*4 + 4], ecx
    uint32_t t146 = recomp_detail::shl<uint32_t>(ctx.ebp, 0x00000002u);
    uint32_t t147 = static_cast<uint32_t>(ctx.eax + t146);
    uint32_t t148 = static_cast<uint32_t>(t147 + 0x00000004u);
    mem.w32(t148, ctx.ecx);
    // 0x0043f82a: mov dword ptr [esp + 0x18], 1
    uint32_t t149 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t149, 0x00000001u);
    goto bb_0043f832;
}
bb_0043f806: {
    // 0x0043f806: lea eax, [esp + 0x3c]
    uint32_t t150 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    ctx.eax = static_cast<uint32_t>(t150);
    goto bb_0043f80a;
}
bb_0043f8b4: {
    // 0x0043f8b4: cmp dword ptr [esp + 0x50], 0x10
    uint32_t t151 = static_cast<uint32_t>(ctx.esp + 0x00000050u);
    uint32_t t152 = mem.r32(t151);
    uint32_t t153 = static_cast<uint32_t>(t152 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t152, 0x00000010u, t153);
    // 0x0043f8b9: jb 0x43f8c8
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043f8c8;
    goto bb_0043f8bb;
}
bb_0043f889: {
    // 0x0043f889: push eax
    uint32_t t154 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t154);
    mem.w32(t154, ctx.eax);
    // 0x0043f88a: xor eax, eax
    uint32_t t155 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t155);
    ctx.eax = static_cast<uint32_t>(t155);
    // 0x0043f88c: xor ecx, ecx
    uint32_t t156 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t156);
    ctx.ecx = static_cast<uint32_t>(t156);
    // 0x0043f88e: call 0x4c8aa0
    uint32_t t157 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t157);
    mem.w32(t157, 0x0043f893u);
    sub_004c8aa0(ctx, mem);
    // 0x0043f893: add esp, 4
    uint32_t t158 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t158);
    ctx.esp = static_cast<uint32_t>(t158);
    // 0x0043f896: mov esi, ebx
    ctx.esi = static_cast<uint32_t>(ctx.ebx);
    // 0x0043f898: mov dword ptr [esp + 0x18], eax
    uint32_t t159 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t159, ctx.eax);
    // 0x0043f89c: call 0x440090
    uint32_t t160 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t160);
    mem.w32(t160, 0x0043f8a1u);
    sub_00440090(ctx, mem);
    // 0x0043f8a1: mov ecx, dword ptr [esp + 0x18]
    uint32_t t161 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t162 = mem.r32(t161);
    ctx.ecx = static_cast<uint32_t>(t162);
    // 0x0043f8a5: mov dword ptr [eax + ebp*4 + 0xc], ecx
    uint32_t t163 = recomp_detail::shl<uint32_t>(ctx.ebp, 0x00000002u);
    uint32_t t164 = static_cast<uint32_t>(ctx.eax + t163);
    uint32_t t165 = static_cast<uint32_t>(t164 + 0x0000000cu);
    mem.w32(t165, ctx.ecx);
    // 0x0043f8a9: mov esi, 1
    ctx.esi = static_cast<uint32_t>(0x00000001u);
    // 0x0043f8ae: jmp 0x43f8b4
    goto bb_0043f8b4;
}
bb_0043f885: {
    // 0x0043f885: lea eax, [esp + 0x3c]
    uint32_t t166 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    ctx.eax = static_cast<uint32_t>(t166);
    goto bb_0043f889;
}
bb_0043f8c8: {
    // 0x0043f8c8: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0043f8ca: jmp 0x43f8ce
    goto bb_0043f8ce;
}
bb_0043f8bb: {
    // 0x0043f8bb: mov edx, dword ptr [esp + 0x3c]
    uint32_t t167 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    uint32_t t168 = mem.r32(t167);
    ctx.edx = static_cast<uint32_t>(t168);
    // 0x0043f8bf: push edx
    uint32_t t169 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t169);
    mem.w32(t169, ctx.edx);
    // 0x0043f8c0: call 0x4e02f3
    uint32_t t170 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t170);
    mem.w32(t170, 0x0043f8c5u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043f8c5: add esp, 4
    uint32_t t171 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t171);
    ctx.esp = static_cast<uint32_t>(t171);
    goto bb_0043f8c8;
}
}

// sub_0043f8f0 | subsystem=Replay | canonical | 20 blocks | 121 insns
void sub_0043f8f0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043f8f0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0043f8f2: push 0x516be8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00516be8u);
    // 0x0043f8f7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0043f8fd: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0043f8fe: sub esp, 0x28
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000028u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000028u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x0043f901: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0043f906: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0043f908: mov dword ptr [esp + 0x24], eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t8, ctx.eax);
    // 0x0043f90c: push ebx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ebx);
    // 0x0043f90d: push ebp
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.ebp);
    // 0x0043f90e: push esi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.esi);
    // 0x0043f90f: push edi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.edi);
    // 0x0043f910: mov eax, dword ptr [0x54b458]
    uint32_t t13 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0043f915: xor eax, esp
    uint32_t t14 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x0043f917: push eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.eax);
    // 0x0043f918: lea eax, [esp + 0x3c]
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0043f91c: mov dword ptr fs:[0], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t17, ctx.eax);
    // 0x0043f922: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x0043f924: mov ebp, dword ptr [esp + 0x4c]
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x0000004cu);
    uint32_t t19 = mem.r32(t18);
    ctx.ebp = static_cast<uint32_t>(t19);
    // 0x0043f928: mov ecx, dword ptr [ebp + 0x6c]
    uint32_t t20 = static_cast<uint32_t>(ctx.ebp + 0x0000006cu);
    uint32_t t21 = mem.r32(t20);
    ctx.ecx = static_cast<uint32_t>(t21);
    // 0x0043f92b: xor ebx, ebx
    uint32_t t22 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t22);
    ctx.ebx = static_cast<uint32_t>(t22);
    // 0x0043f92d: cmp ecx, ebx
    uint32_t t23 = static_cast<uint32_t>(ctx.ecx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebx, t23);
    // 0x0043f92f: je 0x43f93d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043f93d;
    goto bb_0043f931;
}
bb_0043f93d: {
    // 0x0043f93d: xor eax, eax
    uint32_t t24 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t24);
    ctx.eax = static_cast<uint32_t>(t24);
    // 0x0043f93f: jmp 0x43fa50
    goto bb_0043fa50;
}
bb_0043f931: {
    // 0x0043f931: mov eax, dword ptr [ebp + 0x70]
    uint32_t t25 = static_cast<uint32_t>(ctx.ebp + 0x00000070u);
    uint32_t t26 = mem.r32(t25);
    ctx.eax = static_cast<uint32_t>(t26);
    // 0x0043f934: sub eax, ecx
    uint32_t t27 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t27);
    ctx.eax = static_cast<uint32_t>(t27);
    // 0x0043f936: sar eax, 2
    uint32_t t28 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t29 = recomp_detail::sar<uint32_t>(ctx.eax, t28);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t28, t29);
    ctx.eax = static_cast<uint32_t>(t29);
    // 0x0043f939: cmp eax, esi
    uint32_t t30 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t30);
    // 0x0043f93b: ja 0x43f944
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_0043f944;
    goto bb_0043f93d;
}
bb_0043fa50: {
    // 0x0043fa50: mov ecx, dword ptr [esp + 0x3c]
    uint32_t t31 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    uint32_t t32 = mem.r32(t31);
    ctx.ecx = static_cast<uint32_t>(t32);
    // 0x0043fa54: mov dword ptr fs:[0], ecx
    uint32_t t33 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t33, ctx.ecx);
    // 0x0043fa5b: pop ecx
    uint32_t t34 = ctx.esp;
    uint32_t t35 = mem.r32(t34);
    uint32_t t36 = static_cast<uint32_t>(t34 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    ctx.ecx = static_cast<uint32_t>(t35);
    // 0x0043fa5c: pop edi
    uint32_t t37 = ctx.esp;
    uint32_t t38 = mem.r32(t37);
    uint32_t t39 = static_cast<uint32_t>(t37 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    ctx.edi = static_cast<uint32_t>(t38);
    // 0x0043fa5d: pop esi
    uint32_t t40 = ctx.esp;
    uint32_t t41 = mem.r32(t40);
    uint32_t t42 = static_cast<uint32_t>(t40 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    ctx.esi = static_cast<uint32_t>(t41);
    // 0x0043fa5e: pop ebp
    uint32_t t43 = ctx.esp;
    uint32_t t44 = mem.r32(t43);
    uint32_t t45 = static_cast<uint32_t>(t43 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    ctx.ebp = static_cast<uint32_t>(t44);
    // 0x0043fa5f: pop ebx
    uint32_t t46 = ctx.esp;
    uint32_t t47 = mem.r32(t46);
    uint32_t t48 = static_cast<uint32_t>(t46 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    ctx.ebx = static_cast<uint32_t>(t47);
    // 0x0043fa60: mov ecx, dword ptr [esp + 0x24]
    uint32_t t49 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t50 = mem.r32(t49);
    ctx.ecx = static_cast<uint32_t>(t50);
    // 0x0043fa64: xor ecx, esp
    uint32_t t51 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t51);
    ctx.ecx = static_cast<uint32_t>(t51);
    // 0x0043fa66: call 0x4e02f8
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, 0x0043fa6bu);
    hle_crt_004e02f8(ctx, mem);
    // 0x0043fa6b: add esp, 0x34
    uint32_t t53 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000034u, t53);
    ctx.esp = static_cast<uint32_t>(t53);
    // 0x0043fa6e: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0043f944: {
    // 0x0043f944: cmp ecx, ebx
    uint32_t t54 = static_cast<uint32_t>(ctx.ecx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebx, t54);
    // 0x0043f946: je 0x43f954
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043f954;
    goto bb_0043f948;
}
bb_0043f954: {
    // 0x0043f954: call 0x4e0bf2
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, 0x0043f959u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043f959;
}
bb_0043f948: {
    // 0x0043f948: mov eax, dword ptr [ebp + 0x70]
    uint32_t t56 = static_cast<uint32_t>(ctx.ebp + 0x00000070u);
    uint32_t t57 = mem.r32(t56);
    ctx.eax = static_cast<uint32_t>(t57);
    // 0x0043f94b: sub eax, ecx
    uint32_t t58 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t58);
    ctx.eax = static_cast<uint32_t>(t58);
    // 0x0043f94d: sar eax, 2
    uint32_t t59 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t60 = recomp_detail::sar<uint32_t>(ctx.eax, t59);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t59, t60);
    ctx.eax = static_cast<uint32_t>(t60);
    // 0x0043f950: cmp esi, eax
    uint32_t t61 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t61);
    // 0x0043f952: jb 0x43f959
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043f959;
    goto bb_0043f954;
}
bb_0043f959: {
    // 0x0043f959: mov eax, dword ptr [ebp + 0x6c]
    uint32_t t62 = static_cast<uint32_t>(ctx.ebp + 0x0000006cu);
    uint32_t t63 = mem.r32(t62);
    ctx.eax = static_cast<uint32_t>(t63);
    // 0x0043f95c: mov esi, dword ptr [eax + esi*4]
    uint32_t t64 = recomp_detail::shl<uint32_t>(ctx.esi, 0x00000002u);
    uint32_t t65 = static_cast<uint32_t>(ctx.eax + t64);
    uint32_t t66 = mem.r32(t65);
    ctx.esi = static_cast<uint32_t>(t66);
    // 0x0043f95f: cmp esi, ebx
    uint32_t t67 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t67);
    // 0x0043f961: mov dword ptr [esp + 0x18], esi
    uint32_t t68 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t68, ctx.esi);
    // 0x0043f965: je 0x43f93d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043f93d;
}
{
    // 0x0043f967: cmp dword ptr [esi + 0x44], ebx
    uint32_t t69 = static_cast<uint32_t>(ctx.esi + 0x00000044u);
    uint32_t t70 = mem.r32(t69);
    uint32_t t71 = static_cast<uint32_t>(t70 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t70, ctx.ebx, t71);
    // 0x0043f96a: jne 0x43f93d
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043f93d;
}
{
    // 0x0043f96c: push -1
    uint32_t t72 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    mem.w32(t72, 0xffffffffu);
    // 0x0043f96e: lea eax, [esi + 8]
    uint32_t t73 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    ctx.eax = static_cast<uint32_t>(t73);
    // 0x0043f971: push ebx
    uint32_t t74 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    mem.w32(t74, ctx.ebx);
    // 0x0043f972: push eax
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, ctx.eax);
    // 0x0043f973: lea ecx, [esp + 0x28]
    uint32_t t76 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.ecx = static_cast<uint32_t>(t76);
    // 0x0043f977: mov dword ptr [esp + 0x20], 0xffffffff
    uint32_t t77 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t77, 0xffffffffu);
    // 0x0043f97f: mov dword ptr [esp + 0x40], 0xf
    uint32_t t78 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    mem.w32(t78, 0x0000000fu);
    // 0x0043f987: mov dword ptr [esp + 0x3c], ebx
    uint32_t t79 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    mem.w32(t79, ctx.ebx);
    // 0x0043f98b: mov byte ptr [esp + 0x2c], bl
    uint32_t t80 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    mem.w8(t80, recomp_detail::r8l(ctx.ebx));
    // 0x0043f98f: call 0x4079d0
    uint32_t t81 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    mem.w32(t81, 0x0043f994u);
    sub_004079d0(ctx, mem);
    // 0x0043f994: mov ecx, 0x535318
    ctx.ecx = static_cast<uint32_t>(0x00535318u);
    // 0x0043f999: lea edi, [esp + 0x1c]
    uint32_t t82 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.edi = static_cast<uint32_t>(t82);
    // 0x0043f99d: mov dword ptr [esp + 0x44], ebx
    uint32_t t83 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    mem.w32(t83, ctx.ebx);
    // 0x0043f9a1: call 0x42bdc0
    uint32_t t84 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    mem.w32(t84, 0x0043f9a6u);
    sub_0042bdc0(ctx, mem);
    // 0x0043f9a6: test al, al
    uint8_t t85 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t85);
    // 0x0043f9a8: je 0x43f9b8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043f9b8;
    goto bb_0043f9aa;
}
bb_0043f9b8: {
    // 0x0043f9b8: mov esi, dword ptr [esi + 4]
    uint32_t t86 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t87 = mem.r32(t86);
    ctx.esi = static_cast<uint32_t>(t87);
    // 0x0043f9bb: cmp esi, -3
    uint32_t t88 = static_cast<uint32_t>(ctx.esi - 0xfffffffdu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0xfffffffdu, t88);
    // 0x0043f9be: jne 0x43f9c8
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043f9c8;
    goto bb_0043f9c0;
}
bb_0043f9aa: {
    // 0x0043f9aa: push 0x12
    uint32_t t89 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t89);
    mem.w32(t89, 0x00000012u);
    // 0x0043f9ac: push 0x7b4377
    uint32_t t90 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    mem.w32(t90, 0x007b4377u);
    // 0x0043f9b1: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x0043f9b3: call 0x407c10
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, 0x0043f9b8u);
    sub_00407c10(ctx, mem);
    goto bb_0043f9b8;
}
bb_0043f9c8: {
    // 0x0043f9c8: cmp esi, -1
    uint32_t t92 = static_cast<uint32_t>(ctx.esi - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0xffffffffu, t92);
    // 0x0043f9cb: jne 0x43f9d5
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043f9d5;
    goto bb_0043f9cd;
}
bb_0043f9c0: {
    // 0x0043f9c0: mov dword ptr [esp + 0x14], 0xffff6464
    uint32_t t93 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t93, 0xffff6464u);
    goto bb_0043f9c8;
}
bb_0043f9d5: {
    // 0x0043f9d5: push 0x15
    uint32_t t94 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t94);
    mem.w32(t94, 0x00000015u);
    // 0x0043f9d7: mov eax, 0x20
    ctx.eax = static_cast<uint32_t>(0x00000020u);
    // 0x0043f9dc: mov edi, 0x200
    ctx.edi = static_cast<uint32_t>(0x00000200u);
    // 0x0043f9e1: call 0x4bd1e0
    uint32_t t95 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t95);
    mem.w32(t95, 0x0043f9e6u);
    sub_004bd1e0(ctx, mem);
    // 0x0043f9e6: mov esi, dword ptr [ebp + 0xc]
    uint32_t t96 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t97 = mem.r32(t96);
    ctx.esi = static_cast<uint32_t>(t97);
    // 0x0043f9e9: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x0043f9eb: mov ecx, dword ptr [edi]
    uint32_t t98 = mem.r32(ctx.edi);
    ctx.ecx = static_cast<uint32_t>(t98);
    // 0x0043f9ed: mov ebx, dword ptr [ecx + 8]
    uint32_t t99 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t100 = mem.r32(t99);
    ctx.ebx = static_cast<uint32_t>(t100);
    // 0x0043f9f0: add esp, 4
    uint32_t t101 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t101);
    ctx.esp = static_cast<uint32_t>(t101);
    // 0x0043f9f3: call 0x49f090
    uint32_t t102 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    mem.w32(t102, 0x0043f9f8u);
    sub_0049f090(ctx, mem);
    // 0x0043f9f8: mov esi, dword ptr [ebp + 0xc]
    uint32_t t103 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t104 = mem.r32(t103);
    ctx.esi = static_cast<uint32_t>(t104);
    // 0x0043f9fb: call 0x43c3c0
    uint32_t t105 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t105);
    mem.w32(t105, 0x0043fa00u);
    sub_0043c3c0(ctx, mem);
    // 0x0043fa00: mov eax, dword ptr [esp + 0x20]
    uint32_t t106 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t107 = mem.r32(t106);
    ctx.eax = static_cast<uint32_t>(t107);
    // 0x0043fa04: mov ebx, 0x10
    ctx.ebx = static_cast<uint32_t>(0x00000010u);
    // 0x0043fa09: cmp dword ptr [esp + 0x34], ebx
    uint32_t t108 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    uint32_t t109 = mem.r32(t108);
    uint32_t t110 = static_cast<uint32_t>(t109 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t109, ctx.ebx, t110);
    // 0x0043fa0d: jae 0x43fa13
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0043fa13;
    goto bb_0043fa0f;
}
bb_0043f9cd: {
    // 0x0043f9cd: mov dword ptr [esp + 0x14], 0xff646464
    uint32_t t111 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t111, 0xff646464u);
    goto bb_0043f9d5;
}
bb_0043fa13: {
    // 0x0043fa13: mov edx, dword ptr [esp + 0x14]
    uint32_t t112 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t113 = mem.r32(t112);
    ctx.edx = static_cast<uint32_t>(t113);
    // 0x0043fa17: mov esi, dword ptr [ebp + 0xc]
    uint32_t t114 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t115 = mem.r32(t114);
    ctx.esi = static_cast<uint32_t>(t115);
    // 0x0043fa1a: push 0
    uint32_t t116 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t116);
    mem.w32(t116, 0x00000000u);
    // 0x0043fa1c: push edx
    uint32_t t117 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t117);
    mem.w32(t117, ctx.edx);
    // 0x0043fa1d: push eax
    uint32_t t118 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    mem.w32(t118, ctx.eax);
    // 0x0043fa1e: push 1
    uint32_t t119 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t119);
    mem.w32(t119, 0x00000001u);
    // 0x0043fa20: push 0
    uint32_t t120 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t120);
    mem.w32(t120, 0x00000000u);
    // 0x0043fa22: xor eax, eax
    uint32_t t121 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t121);
    ctx.eax = static_cast<uint32_t>(t121);
    // 0x0043fa24: call 0x49f280
    uint32_t t122 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t122);
    mem.w32(t122, 0x0043fa29u);
    sub_0049f280(ctx, mem);
    // 0x0043fa29: mov esi, dword ptr [ebp + 0xc]
    uint32_t t123 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t124 = mem.r32(t123);
    ctx.esi = static_cast<uint32_t>(t124);
    // 0x0043fa2c: call 0x43c420
    uint32_t t125 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t125);
    mem.w32(t125, 0x0043fa31u);
    sub_0043c420(ctx, mem);
    // 0x0043fa31: mov eax, dword ptr [esp + 0x18]
    uint32_t t126 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t127 = mem.r32(t126);
    ctx.eax = static_cast<uint32_t>(t127);
    // 0x0043fa35: mov dword ptr [eax + 0x44], edi
    uint32_t t128 = static_cast<uint32_t>(ctx.eax + 0x00000044u);
    mem.w32(t128, ctx.edi);
    // 0x0043fa38: cmp dword ptr [esp + 0x34], ebx
    uint32_t t129 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    uint32_t t130 = mem.r32(t129);
    uint32_t t131 = static_cast<uint32_t>(t130 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t130, ctx.ebx, t131);
    // 0x0043fa3c: jb 0x43fa4b
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0043fa4b;
    goto bb_0043fa3e;
}
bb_0043fa0f: {
    // 0x0043fa0f: lea eax, [esp + 0x20]
    uint32_t t132 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    ctx.eax = static_cast<uint32_t>(t132);
    goto bb_0043fa13;
}
bb_0043fa4b: {
    // 0x0043fa4b: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    goto bb_0043fa50;
}
bb_0043fa3e: {
    // 0x0043fa3e: mov ecx, dword ptr [esp + 0x20]
    uint32_t t133 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t134 = mem.r32(t133);
    ctx.ecx = static_cast<uint32_t>(t134);
    // 0x0043fa42: push ecx
    uint32_t t135 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t135);
    mem.w32(t135, ctx.ecx);
    // 0x0043fa43: call 0x4e02f3
    uint32_t t136 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t136);
    mem.w32(t136, 0x0043fa48u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043fa48: add esp, 4
    uint32_t t137 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t137);
    ctx.esp = static_cast<uint32_t>(t137);
    goto bb_0043fa4b;
}
}

// sub_0043fd70 | subsystem=Replay | canonical | 22 blocks | 68 insns
void sub_0043fd70(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043fd70: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x0043fd71: mov ecx, dword ptr [esp + 8]
    uint32_t t1 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t2 = mem.r32(t1);
    ctx.ecx = static_cast<uint32_t>(t2);
    // 0x0043fd75: cmp ecx, 0x3fffffff
    uint32_t t3 = static_cast<uint32_t>(ctx.ecx - 0x3fffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x3fffffffu, t3);
    // 0x0043fd7b: push ebx
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.ebx);
    // 0x0043fd7c: push ebp
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ebp);
    // 0x0043fd7d: push edi
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.edi);
    // 0x0043fd7e: jbe 0x43fd85
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043fd85;
    goto bb_0043fd80;
}
bb_0043fd85: {
    // 0x0043fd85: mov edx, dword ptr [esi + 4]
    uint32_t t7 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t8 = mem.r32(t7);
    ctx.edx = static_cast<uint32_t>(t8);
    // 0x0043fd88: test edx, edx
    uint32_t t9 = static_cast<uint32_t>(ctx.edx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    // 0x0043fd8a: jne 0x43fd90
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043fd90;
    goto bb_0043fd8c;
}
bb_0043fd80: {
    // 0x0043fd80: call 0x437280
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x0043fd85u);
    sub_00437280(ctx, mem);
    goto bb_0043fd85;
}
bb_0043fd90: {
    // 0x0043fd90: mov eax, dword ptr [esi + 0xc]
    uint32_t t11 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    uint32_t t12 = mem.r32(t11);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0043fd93: sub eax, edx
    uint32_t t13 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t13);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0043fd95: sar eax, 2
    uint32_t t14 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t15 = recomp_detail::sar<uint32_t>(ctx.eax, t14);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t14, t15);
    ctx.eax = static_cast<uint32_t>(t15);
    goto bb_0043fd98;
}
bb_0043fd8c: {
    // 0x0043fd8c: xor eax, eax
    uint32_t t16 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0043fd8e: jmp 0x43fd98
}
bb_0043fd98: {
    // 0x0043fd98: cmp eax, ecx
    uint32_t t17 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t17);
    // 0x0043fd9a: jae 0x43fe20
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0043fe20;
    goto bb_0043fda0;
}
bb_0043fe20: {
    // 0x0043fe20: pop edi
    uint32_t t18 = ctx.esp;
    uint32_t t19 = mem.r32(t18);
    uint32_t t20 = static_cast<uint32_t>(t18 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    ctx.edi = static_cast<uint32_t>(t19);
    // 0x0043fe21: pop ebp
    uint32_t t21 = ctx.esp;
    uint32_t t22 = mem.r32(t21);
    uint32_t t23 = static_cast<uint32_t>(t21 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    ctx.ebp = static_cast<uint32_t>(t22);
    // 0x0043fe22: pop ebx
    uint32_t t24 = ctx.esp;
    uint32_t t25 = mem.r32(t24);
    uint32_t t26 = static_cast<uint32_t>(t24 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    ctx.ebx = static_cast<uint32_t>(t25);
    // 0x0043fe23: pop ecx
    uint32_t t27 = ctx.esp;
    uint32_t t28 = mem.r32(t27);
    uint32_t t29 = static_cast<uint32_t>(t27 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    ctx.ecx = static_cast<uint32_t>(t28);
    // 0x0043fe24: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0043fda0: {
    // 0x0043fda0: test ecx, ecx
    uint32_t t30 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t30);
    // 0x0043fda2: ja 0x43fdb0
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_0043fdb0;
    goto bb_0043fda4;
}
bb_0043fdb0: {
    // 0x0043fdb0: call 0x4dd100
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x0043fdb5u);
    sub_004dd100(ctx, mem);
    goto bb_0043fdb5;
}
bb_0043fda4: {
    // 0x0043fda4: push 0
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x00000000u);
    // 0x0043fda6: call 0x4e0177
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x0043fdabu);
    hle_crt_004e0177(ctx, mem);
    // 0x0043fdab: add esp, 4
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t34);
    ctx.esp = static_cast<uint32_t>(t34);
    // 0x0043fdae: jmp 0x43fdb5
}
bb_0043fdb5: {
    // 0x0043fdb5: mov edi, dword ptr [esi + 8]
    uint32_t t35 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t36 = mem.r32(t35);
    ctx.edi = static_cast<uint32_t>(t36);
    // 0x0043fdb8: cmp dword ptr [esi + 4], edi
    uint32_t t37 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t38 = mem.r32(t37);
    uint32_t t39 = static_cast<uint32_t>(t38 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t38, ctx.edi, t39);
    // 0x0043fdbb: mov ebp, eax
    ctx.ebp = static_cast<uint32_t>(ctx.eax);
    // 0x0043fdbd: jbe 0x43fdc4
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043fdc4;
    goto bb_0043fdbf;
}
bb_0043fdc4: {
    // 0x0043fdc4: mov ebx, dword ptr [esi + 4]
    uint32_t t40 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t41 = mem.r32(t40);
    ctx.ebx = static_cast<uint32_t>(t41);
    // 0x0043fdc7: cmp ebx, dword ptr [esi + 8]
    uint32_t t42 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t43 = mem.r32(t42);
    uint32_t t44 = static_cast<uint32_t>(ctx.ebx - t43);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, t43, t44);
    // 0x0043fdca: jbe 0x43fdd1
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043fdd1;
    goto bb_0043fdcc;
}
bb_0043fdbf: {
    // 0x0043fdbf: call 0x4e0bf2
    uint32_t t45 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    mem.w32(t45, 0x0043fdc4u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043fdc4;
}
bb_0043fdd1: {
    // 0x0043fdd1: sub edi, ebx
    uint32_t t46 = static_cast<uint32_t>(ctx.edi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebx, t46);
    ctx.edi = static_cast<uint32_t>(t46);
    // 0x0043fdd3: sar edi, 2
    uint32_t t47 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t48 = recomp_detail::sar<uint32_t>(ctx.edi, t47);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edi, t47, t48);
    ctx.edi = static_cast<uint32_t>(t48);
    // 0x0043fdd6: je 0x43fdeb
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043fdeb;
    goto bb_0043fdd8;
}
bb_0043fdcc: {
    // 0x0043fdcc: call 0x4e0bf2
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, 0x0043fdd1u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043fdd1;
}
bb_0043fdeb: {
    // 0x0043fdeb: mov eax, dword ptr [esi + 4]
    uint32_t t50 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t51 = mem.r32(t50);
    ctx.eax = static_cast<uint32_t>(t51);
    // 0x0043fdee: test eax, eax
    uint32_t t52 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t52);
    // 0x0043fdf0: jne 0x43fdf6
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043fdf6;
    goto bb_0043fdf2;
}
bb_0043fdd8: {
    // 0x0043fdd8: lea eax, [edi*4]
    uint32_t t53 = recomp_detail::shl<uint32_t>(ctx.edi, 0x00000002u);
    ctx.eax = static_cast<uint32_t>(t53);
    // 0x0043fddf: push eax
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, ctx.eax);
    // 0x0043fde0: push ebx
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, ctx.ebx);
    // 0x0043fde1: push eax
    uint32_t t56 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    mem.w32(t56, ctx.eax);
    // 0x0043fde2: push ebp
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, ctx.ebp);
    // 0x0043fde3: call 0x4e0c02
    uint32_t t58 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    mem.w32(t58, 0x0043fde8u);
    hle_crt_004e0c02(ctx, mem);
    // 0x0043fde8: add esp, 0x10
    uint32_t t59 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t59);
    ctx.esp = static_cast<uint32_t>(t59);
    goto bb_0043fdeb;
}
bb_0043fdf6: {
    // 0x0043fdf6: mov edi, dword ptr [esi + 8]
    uint32_t t60 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t61 = mem.r32(t60);
    ctx.edi = static_cast<uint32_t>(t61);
    // 0x0043fdf9: sub edi, eax
    uint32_t t62 = static_cast<uint32_t>(ctx.edi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.eax, t62);
    ctx.edi = static_cast<uint32_t>(t62);
    // 0x0043fdfb: sar edi, 2
    uint32_t t63 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t64 = recomp_detail::sar<uint32_t>(ctx.edi, t63);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edi, t63, t64);
    ctx.edi = static_cast<uint32_t>(t64);
    goto bb_0043fdfe;
}
bb_0043fdf2: {
    // 0x0043fdf2: xor edi, edi
    uint32_t t65 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t65);
    ctx.edi = static_cast<uint32_t>(t65);
    // 0x0043fdf4: jmp 0x43fdfe
}
bb_0043fdfe: {
    // 0x0043fdfe: test eax, eax
    uint32_t t66 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t66);
    // 0x0043fe00: je 0x43fe0b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043fe0b;
    goto bb_0043fe02;
}
bb_0043fe0b: {
    // 0x0043fe0b: mov eax, dword ptr [esp + 0x14]
    uint32_t t67 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t68 = mem.r32(t67);
    ctx.eax = static_cast<uint32_t>(t68);
    // 0x0043fe0f: lea ecx, [ebp + eax*4]
    uint32_t t69 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000002u);
    uint32_t t70 = static_cast<uint32_t>(ctx.ebp + t69);
    ctx.ecx = static_cast<uint32_t>(t70);
    // 0x0043fe13: lea edx, [ebp + edi*4]
    uint32_t t71 = recomp_detail::shl<uint32_t>(ctx.edi, 0x00000002u);
    uint32_t t72 = static_cast<uint32_t>(ctx.ebp + t71);
    ctx.edx = static_cast<uint32_t>(t72);
    // 0x0043fe17: mov dword ptr [esi + 0xc], ecx
    uint32_t t73 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t73, ctx.ecx);
    // 0x0043fe1a: mov dword ptr [esi + 8], edx
    uint32_t t74 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t74, ctx.edx);
    // 0x0043fe1d: mov dword ptr [esi + 4], ebp
    uint32_t t75 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t75, ctx.ebp);
    goto bb_0043fe20;
}
bb_0043fe02: {
    // 0x0043fe02: push eax
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    mem.w32(t76, ctx.eax);
    // 0x0043fe03: call 0x4e02f3
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, 0x0043fe08u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043fe08: add esp, 4
    uint32_t t78 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t78);
    ctx.esp = static_cast<uint32_t>(t78);
    goto bb_0043fe0b;
}
}

// sub_0043fea0 | subsystem=Replay | canonical | 15 blocks | 98 insns
void sub_0043fea0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043fea0: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x0043fea1: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x0043fea3: push -1
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0xffffffffu);
    // 0x0043fea5: push 0x516280
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x00516280u);
    // 0x0043feaa: mov eax, dword ptr fs:[0]
    uint32_t t3 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t4 = mem.r32(t3);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0043feb0: push eax
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.eax);
    // 0x0043feb1: sub esp, 0xc
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x0000000cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x0000000cu, t6);
    ctx.esp = static_cast<uint32_t>(t6);
    // 0x0043feb4: push ebx
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.ebx);
    // 0x0043feb5: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x0043feb6: push edi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.edi);
    // 0x0043feb7: mov eax, dword ptr [0x54b458]
    uint32_t t10 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0043febc: xor eax, ebp
    uint32_t t11 = static_cast<uint32_t>(ctx.eax ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x0043febe: push eax
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.eax);
    // 0x0043febf: lea eax, [ebp - 0xc]
    uint32_t t13 = static_cast<uint32_t>(ctx.ebp + 0xfffffff4u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0043fec2: mov dword ptr fs:[0], eax
    uint32_t t14 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t14, ctx.eax);
    // 0x0043fec8: mov dword ptr [ebp - 0x10], esp
    uint32_t t15 = static_cast<uint32_t>(ctx.ebp + 0xfffffff0u);
    mem.w32(t15, ctx.esp);
    // 0x0043fecb: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x0043fecd: mov eax, dword ptr [esi + 4]
    uint32_t t16 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t17 = mem.r32(t16);
    ctx.eax = static_cast<uint32_t>(t17);
    // 0x0043fed0: test eax, eax
    uint32_t t18 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    // 0x0043fed2: je 0x43fef5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043fef5;
    goto bb_0043fed4;
}
bb_0043fef5: {
    // 0x0043fef5: mov ecx, 0x80
    ctx.ecx = static_cast<uint32_t>(0x00000080u);
    // 0x0043fefa: call 0x4406b0
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x0043feffu);
    sub_004406b0(ctx, mem);
    // 0x0043feff: mov dword ptr [ebp - 4], 0
    uint32_t t20 = static_cast<uint32_t>(ctx.ebp + 0xfffffffcu);
    mem.w32(t20, 0x00000000u);
    // 0x0043ff06: mov edi, dword ptr [esi + 8]
    uint32_t t21 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t22 = mem.r32(t21);
    ctx.edi = static_cast<uint32_t>(t22);
    // 0x0043ff09: cmp dword ptr [esi + 4], edi
    uint32_t t23 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t24 = mem.r32(t23);
    uint32_t t25 = static_cast<uint32_t>(t24 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t24, ctx.edi, t25);
    // 0x0043ff0c: mov dword ptr [ebp - 0x14], eax
    uint32_t t26 = static_cast<uint32_t>(ctx.ebp + 0xffffffecu);
    mem.w32(t26, ctx.eax);
    // 0x0043ff0f: jbe 0x43ff16
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043ff16;
    goto bb_0043ff11;
}
bb_0043fed4: {
    // 0x0043fed4: mov ecx, dword ptr [esi + 0xc]
    uint32_t t27 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    uint32_t t28 = mem.r32(t27);
    ctx.ecx = static_cast<uint32_t>(t28);
    // 0x0043fed7: sub ecx, eax
    uint32_t t29 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t29);
    ctx.ecx = static_cast<uint32_t>(t29);
    // 0x0043fed9: mov eax, 0x66666667
    ctx.eax = static_cast<uint32_t>(0x66666667u);
    // 0x0043fede: imul ecx
    uint64_t t30 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t31 = static_cast<uint32_t>(t30);
    uint32_t t32 = static_cast<uint32_t>(t30 >> 32);
    ctx.eax = static_cast<uint32_t>(t31);
    ctx.edx = static_cast<uint32_t>(t32);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t30);
    // 0x0043fee0: sar edx, 3
    uint32_t t33 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t34 = recomp_detail::sar<uint32_t>(ctx.edx, t33);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t33, t34);
    ctx.edx = static_cast<uint32_t>(t34);
    // 0x0043fee3: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x0043fee5: shr eax, 0x1f
    uint32_t t35 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t36 = recomp_detail::shr<uint32_t>(ctx.eax, t35);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t35, t36);
    ctx.eax = static_cast<uint32_t>(t36);
    // 0x0043fee8: add eax, edx
    uint32_t t37 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t37);
    ctx.eax = static_cast<uint32_t>(t37);
    // 0x0043feea: cmp eax, 0x80
    uint32_t t38 = static_cast<uint32_t>(ctx.eax - 0x00000080u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000080u, t38);
    // 0x0043feef: jae 0x43ffaa
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0043ffaa;
    goto bb_0043fef5;
}
bb_0043ff16: {
    // 0x0043ff16: mov ebx, dword ptr [esi + 4]
    uint32_t t39 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t40 = mem.r32(t39);
    ctx.ebx = static_cast<uint32_t>(t40);
    // 0x0043ff19: cmp ebx, dword ptr [esi + 8]
    uint32_t t41 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t42 = mem.r32(t41);
    uint32_t t43 = static_cast<uint32_t>(ctx.ebx - t42);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, t42, t43);
    // 0x0043ff1c: jbe 0x43ff23
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0043ff23;
    goto bb_0043ff1e;
}
bb_0043ff11: {
    // 0x0043ff11: call 0x4e0bf2
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, 0x0043ff16u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043ff16;
}
bb_0043ffaa: {
    // 0x0043ffaa: mov ecx, dword ptr [ebp - 0xc]
    uint32_t t45 = static_cast<uint32_t>(ctx.ebp + 0xfffffff4u);
    uint32_t t46 = mem.r32(t45);
    ctx.ecx = static_cast<uint32_t>(t46);
    // 0x0043ffad: mov dword ptr fs:[0], ecx
    uint32_t t47 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t47, ctx.ecx);
    // 0x0043ffb4: pop ecx
    uint32_t t48 = ctx.esp;
    uint32_t t49 = mem.r32(t48);
    uint32_t t50 = static_cast<uint32_t>(t48 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    ctx.ecx = static_cast<uint32_t>(t49);
    // 0x0043ffb5: pop edi
    uint32_t t51 = ctx.esp;
    uint32_t t52 = mem.r32(t51);
    uint32_t t53 = static_cast<uint32_t>(t51 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    ctx.edi = static_cast<uint32_t>(t52);
    // 0x0043ffb6: pop esi
    uint32_t t54 = ctx.esp;
    uint32_t t55 = mem.r32(t54);
    uint32_t t56 = static_cast<uint32_t>(t54 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    ctx.esi = static_cast<uint32_t>(t55);
    // 0x0043ffb7: pop ebx
    uint32_t t57 = ctx.esp;
    uint32_t t58 = mem.r32(t57);
    uint32_t t59 = static_cast<uint32_t>(t57 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    ctx.ebx = static_cast<uint32_t>(t58);
    // 0x0043ffb8: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0043ffba: pop ebp
    uint32_t t60 = ctx.esp;
    uint32_t t61 = mem.r32(t60);
    uint32_t t62 = static_cast<uint32_t>(t60 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    ctx.ebp = static_cast<uint32_t>(t61);
    // 0x0043ffbb: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043ff23: {
    // 0x0043ff23: mov byte ptr [ebp - 0x18], 0
    uint32_t t63 = static_cast<uint32_t>(ctx.ebp + 0xffffffe8u);
    mem.w8(t63, uint8_t{0x00u});
    // 0x0043ff27: mov eax, dword ptr [ebp - 0x18]
    uint32_t t64 = static_cast<uint32_t>(ctx.ebp + 0xffffffe8u);
    uint32_t t65 = mem.r32(t64);
    ctx.eax = static_cast<uint32_t>(t65);
    // 0x0043ff2a: mov ecx, dword ptr [ebp - 0x18]
    uint32_t t66 = static_cast<uint32_t>(ctx.ebp + 0xffffffe8u);
    uint32_t t67 = mem.r32(t66);
    ctx.ecx = static_cast<uint32_t>(t67);
    // 0x0043ff2d: push eax
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, ctx.eax);
    // 0x0043ff2e: mov eax, dword ptr [ebp - 0x14]
    uint32_t t69 = static_cast<uint32_t>(ctx.ebp + 0xffffffecu);
    uint32_t t70 = mem.r32(t69);
    ctx.eax = static_cast<uint32_t>(t70);
    // 0x0043ff31: push ecx
    uint32_t t71 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t71);
    mem.w32(t71, ctx.ecx);
    // 0x0043ff32: mov edx, edi
    ctx.edx = static_cast<uint32_t>(ctx.edi);
    // 0x0043ff34: mov ecx, ebx
    ctx.ecx = static_cast<uint32_t>(ctx.ebx);
    // 0x0043ff36: call 0x440880
    uint32_t t72 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    mem.w32(t72, 0x0043ff3bu);
    sub_00440880(ctx, mem);
    // 0x0043ff3b: mov dword ptr [ebp - 4], 0xffffffff
    uint32_t t73 = static_cast<uint32_t>(ctx.ebp + 0xfffffffcu);
    mem.w32(t73, 0xffffffffu);
    // 0x0043ff42: mov ebx, dword ptr [esi + 4]
    uint32_t t74 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t75 = mem.r32(t74);
    ctx.ebx = static_cast<uint32_t>(t75);
    // 0x0043ff45: add esp, 8
    uint32_t t76 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t76);
    ctx.esp = static_cast<uint32_t>(t76);
    // 0x0043ff48: test ebx, ebx
    uint32_t t77 = static_cast<uint32_t>(ctx.ebx & ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t77);
    // 0x0043ff4a: jne 0x43ff50
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043ff50;
    goto bb_0043ff4c;
}
bb_0043ff1e: {
    // 0x0043ff1e: call 0x4e0bf2
    uint32_t t78 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    mem.w32(t78, 0x0043ff23u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0043ff23;
}
bb_0043ff50: {
    // 0x0043ff50: mov ecx, dword ptr [esi + 8]
    uint32_t t79 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t80 = mem.r32(t79);
    ctx.ecx = static_cast<uint32_t>(t80);
    // 0x0043ff53: sub ecx, ebx
    uint32_t t81 = static_cast<uint32_t>(ctx.ecx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebx, t81);
    ctx.ecx = static_cast<uint32_t>(t81);
    // 0x0043ff55: mov eax, 0x66666667
    ctx.eax = static_cast<uint32_t>(0x66666667u);
    // 0x0043ff5a: imul ecx
    uint64_t t82 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t83 = static_cast<uint32_t>(t82);
    uint32_t t84 = static_cast<uint32_t>(t82 >> 32);
    ctx.eax = static_cast<uint32_t>(t83);
    ctx.edx = static_cast<uint32_t>(t84);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t82);
    // 0x0043ff5c: sar edx, 3
    uint32_t t85 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t86 = recomp_detail::sar<uint32_t>(ctx.edx, t85);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t85, t86);
    ctx.edx = static_cast<uint32_t>(t86);
    // 0x0043ff5f: mov edi, edx
    ctx.edi = static_cast<uint32_t>(ctx.edx);
    // 0x0043ff61: shr edi, 0x1f
    uint32_t t87 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t88 = recomp_detail::shr<uint32_t>(ctx.edi, t87);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.edi, t87, t88);
    ctx.edi = static_cast<uint32_t>(t88);
    // 0x0043ff64: add edi, edx
    uint32_t t89 = static_cast<uint32_t>(ctx.edi + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, ctx.edx, t89);
    ctx.edi = static_cast<uint32_t>(t89);
    goto bb_0043ff66;
}
bb_0043ff4c: {
    // 0x0043ff4c: xor edi, edi
    uint32_t t90 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t90);
    ctx.edi = static_cast<uint32_t>(t90);
    // 0x0043ff4e: jmp 0x43ff66
}
bb_0043ff66: {
    // 0x0043ff66: test ebx, ebx
    uint32_t t91 = static_cast<uint32_t>(ctx.ebx & ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t91);
    // 0x0043ff68: je 0x43ff8d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043ff8d;
    goto bb_0043ff6a;
}
bb_0043ff8d: {
    // 0x0043ff8d: mov eax, 0x80
    ctx.eax = static_cast<uint32_t>(0x00000080u);
    // 0x0043ff92: lea ecx, [eax + eax*4]
    uint32_t t92 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000002u);
    uint32_t t93 = static_cast<uint32_t>(ctx.eax + t92);
    ctx.ecx = static_cast<uint32_t>(t93);
    // 0x0043ff95: mov eax, dword ptr [ebp - 0x14]
    uint32_t t94 = static_cast<uint32_t>(ctx.ebp + 0xffffffecu);
    uint32_t t95 = mem.r32(t94);
    ctx.eax = static_cast<uint32_t>(t95);
    // 0x0043ff98: lea edx, [eax + ecx*4]
    uint32_t t96 = recomp_detail::shl<uint32_t>(ctx.ecx, 0x00000002u);
    uint32_t t97 = static_cast<uint32_t>(ctx.eax + t96);
    ctx.edx = static_cast<uint32_t>(t97);
    // 0x0043ff9b: lea ecx, [edi + edi*4]
    uint32_t t98 = recomp_detail::shl<uint32_t>(ctx.edi, 0x00000002u);
    uint32_t t99 = static_cast<uint32_t>(ctx.edi + t98);
    ctx.ecx = static_cast<uint32_t>(t99);
    // 0x0043ff9e: mov dword ptr [esi + 0xc], edx
    uint32_t t100 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t100, ctx.edx);
    // 0x0043ffa1: lea edx, [eax + ecx*4]
    uint32_t t101 = recomp_detail::shl<uint32_t>(ctx.ecx, 0x00000002u);
    uint32_t t102 = static_cast<uint32_t>(ctx.eax + t101);
    ctx.edx = static_cast<uint32_t>(t102);
    // 0x0043ffa4: mov dword ptr [esi + 8], edx
    uint32_t t103 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t103, ctx.edx);
    // 0x0043ffa7: mov dword ptr [esi + 4], eax
    uint32_t t104 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t104, ctx.eax);
    goto bb_0043ffaa;
}
bb_0043ff6a: {
    // 0x0043ff6a: mov eax, dword ptr [esi + 8]
    uint32_t t105 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t106 = mem.r32(t105);
    ctx.eax = static_cast<uint32_t>(t106);
    // 0x0043ff6d: cmp ebx, eax
    uint32_t t107 = static_cast<uint32_t>(ctx.ebx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.eax, t107);
    // 0x0043ff6f: mov dword ptr [ebp - 0x18], eax
    uint32_t t108 = static_cast<uint32_t>(ctx.ebp + 0xffffffe8u);
    mem.w32(t108, ctx.eax);
    // 0x0043ff72: je 0x43ff81
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043ff81;
    goto bb_0043ff74;
}
bb_0043ff81: {
    // 0x0043ff81: mov edx, dword ptr [esi + 4]
    uint32_t t109 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t110 = mem.r32(t109);
    ctx.edx = static_cast<uint32_t>(t110);
    // 0x0043ff84: push edx
    uint32_t t111 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t111);
    mem.w32(t111, ctx.edx);
    // 0x0043ff85: call 0x4e02f3
    uint32_t t112 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t112);
    mem.w32(t112, 0x0043ff8au);
    hle_crt_004e02f3(ctx, mem);
    // 0x0043ff8a: add esp, 4
    uint32_t t113 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t113);
    ctx.esp = static_cast<uint32_t>(t113);
    goto bb_0043ff8d;
}
bb_0043ff74: {
    // 0x0043ff74: call 0x43c280
    uint32_t t114 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t114);
    mem.w32(t114, 0x0043ff79u);
    sub_0043c280(ctx, mem);
    // 0x0043ff79: add ebx, 0x14
    uint32_t t115 = static_cast<uint32_t>(ctx.ebx + 0x00000014u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebx, 0x00000014u, t115);
    ctx.ebx = static_cast<uint32_t>(t115);
    // 0x0043ff7c: cmp ebx, dword ptr [ebp - 0x18]
    uint32_t t116 = static_cast<uint32_t>(ctx.ebp + 0xffffffe8u);
    uint32_t t117 = mem.r32(t116);
    uint32_t t118 = static_cast<uint32_t>(ctx.ebx - t117);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, t117, t118);
    // 0x0043ff7f: jne 0x43ff74
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043ff74;
    goto bb_0043ff81;
}
}

// sub_0043ffe0 | subsystem=Replay | canonical | 1 blocks | 44 insns
void sub_0043ffe0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043ffe0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0043ffe2: push 0x516258
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00516258u);
    // 0x0043ffe7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0043ffed: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0043ffee: sub esp, 0x14
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000014u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000014u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x0043fff1: push ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebx);
    // 0x0043fff2: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x0043fff3: push edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edi);
    // 0x0043fff4: mov eax, dword ptr [0x54b458]
    uint32_t t9 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x0043fff9: xor eax, esp
    uint32_t t10 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0043fffb: push eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.eax);
    // 0x0043fffc: lea eax, [esp + 0x24]
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x00440000: mov dword ptr fs:[0], eax
    uint32_t t13 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t13, ctx.eax);
    // 0x00440006: xor ebx, ebx
    uint32_t t14 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    ctx.ebx = static_cast<uint32_t>(t14);
    // 0x00440008: xor ecx, ecx
    uint32_t t15 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t15);
    ctx.ecx = static_cast<uint32_t>(t15);
    // 0x0044000a: xor edx, edx
    uint32_t t16 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    ctx.edx = static_cast<uint32_t>(t16);
    // 0x0044000c: xor esi, esi
    uint32_t t17 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t17);
    ctx.esi = static_cast<uint32_t>(t17);
    // 0x0044000e: xor edi, edi
    uint32_t t18 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    ctx.edi = static_cast<uint32_t>(t18);
    // 0x00440010: mov dword ptr [esp + 0x10], ecx
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t19, ctx.ecx);
    // 0x00440014: mov dword ptr [esp + 0x18], edx
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t20, ctx.edx);
    // 0x00440018: mov dword ptr [esp + 0x14], esi
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t21, ctx.esi);
    // 0x0044001c: mov dword ptr [esp + 0x20], edi
    uint32_t t22 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t22, ctx.edi);
    // 0x00440020: mov dword ptr [esp + 0x1c], ebx
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t23, ctx.ebx);
    // 0x00440024: mov dword ptr [esp + 0x2c], ebx
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    mem.w32(t24, ctx.ebx);
    // 0x00440028: sub esp, 0x14
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000014u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000014u, t25);
    ctx.esp = static_cast<uint32_t>(t25);
    // 0x0044002b: mov eax, esp
    ctx.eax = static_cast<uint32_t>(ctx.esp);
    // 0x0044002d: mov dword ptr [eax], ecx
    mem.w32(ctx.eax, ctx.ecx);
    // 0x0044002f: mov ecx, dword ptr [esp + 0x48]
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    uint32_t t27 = mem.r32(t26);
    ctx.ecx = static_cast<uint32_t>(t27);
    // 0x00440033: mov dword ptr [eax + 4], esi
    uint32_t t28 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w32(t28, ctx.esi);
    // 0x00440036: mov dword ptr [eax + 8], edx
    uint32_t t29 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    mem.w32(t29, ctx.edx);
    // 0x00440039: mov dword ptr [eax + 0xc], ebx
    uint32_t t30 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    mem.w32(t30, ctx.ebx);
    // 0x0044003c: mov dword ptr [eax + 0x10], edi
    uint32_t t31 = static_cast<uint32_t>(ctx.eax + 0x00000010u);
    mem.w32(t31, ctx.edi);
    // 0x0044003f: call 0x440190
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x00440044u);
    sub_00440190(ctx, mem);
    // 0x00440044: lea ebx, [esp + 0x10]
    uint32_t t33 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    ctx.ebx = static_cast<uint32_t>(t33);
    // 0x00440048: mov dword ptr [esp + 0x2c], 0xffffffff
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    mem.w32(t34, 0xffffffffu);
    // 0x00440050: call 0x43c280
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, 0x00440055u);
    sub_0043c280(ctx, mem);
    // 0x00440055: mov ecx, dword ptr [esp + 0x24]
    uint32_t t36 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t37 = mem.r32(t36);
    ctx.ecx = static_cast<uint32_t>(t37);
    // 0x00440059: mov dword ptr fs:[0], ecx
    uint32_t t38 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t38, ctx.ecx);
    // 0x00440060: pop ecx
    uint32_t t39 = ctx.esp;
    uint32_t t40 = mem.r32(t39);
    uint32_t t41 = static_cast<uint32_t>(t39 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    ctx.ecx = static_cast<uint32_t>(t40);
    // 0x00440061: pop edi
    uint32_t t42 = ctx.esp;
    uint32_t t43 = mem.r32(t42);
    uint32_t t44 = static_cast<uint32_t>(t42 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    ctx.edi = static_cast<uint32_t>(t43);
    // 0x00440062: pop esi
    uint32_t t45 = ctx.esp;
    uint32_t t46 = mem.r32(t45);
    uint32_t t47 = static_cast<uint32_t>(t45 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    ctx.esi = static_cast<uint32_t>(t46);
    // 0x00440063: pop ebx
    uint32_t t48 = ctx.esp;
    uint32_t t49 = mem.r32(t48);
    uint32_t t50 = static_cast<uint32_t>(t48 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    ctx.ebx = static_cast<uint32_t>(t49);
    // 0x00440064: add esp, 0x20
    uint32_t t51 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000020u, t51);
    ctx.esp = static_cast<uint32_t>(t51);
    // 0x00440067: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
}

// sub_00440070 | subsystem=Replay | canonical | 3 blocks | 13 insns
void sub_00440070(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00440070: mov eax, dword ptr [ecx + 4]
    uint32_t t0 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    uint32_t t1 = mem.r32(t0);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x00440073: test eax, eax
    uint32_t t2 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    // 0x00440075: jne 0x440078
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00440078;
    goto bb_00440077;
}
bb_00440078: {
    // 0x00440078: mov ecx, dword ptr [ecx + 8]
    uint32_t t3 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t4 = mem.r32(t3);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x0044007b: sub ecx, eax
    uint32_t t5 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t5);
    ctx.ecx = static_cast<uint32_t>(t5);
    // 0x0044007d: mov eax, 0x66666667
    ctx.eax = static_cast<uint32_t>(0x66666667u);
    // 0x00440082: imul ecx
    uint64_t t6 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t7 = static_cast<uint32_t>(t6);
    uint32_t t8 = static_cast<uint32_t>(t6 >> 32);
    ctx.eax = static_cast<uint32_t>(t7);
    ctx.edx = static_cast<uint32_t>(t8);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t6);
    // 0x00440084: sar edx, 3
    uint32_t t9 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t10 = recomp_detail::sar<uint32_t>(ctx.edx, t9);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t9, t10);
    ctx.edx = static_cast<uint32_t>(t10);
    // 0x00440087: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x00440089: shr eax, 0x1f
    uint32_t t11 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t12 = recomp_detail::shr<uint32_t>(ctx.eax, t11);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t11, t12);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0044008c: add eax, edx
    uint32_t t13 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t13);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0044008e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00440077: {
    // 0x00440077: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00440090 | subsystem=Replay | canonical | 4 blocks | 18 insns
void sub_00440090(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00440090: mov eax, dword ptr [esi + 4]
    uint32_t t0 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t1 = mem.r32(t0);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x00440093: test eax, eax
    uint32_t t2 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    // 0x00440095: je 0x4400b1
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004400b1;
    goto bb_00440097;
}
bb_004400b1: {
    // 0x004400b1: call 0x4e0bf2
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x004400b6u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004400b6;
}
bb_00440097: {
    // 0x00440097: mov ecx, dword ptr [esi + 8]
    uint32_t t4 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t5 = mem.r32(t4);
    ctx.ecx = static_cast<uint32_t>(t5);
    // 0x0044009a: sub ecx, eax
    uint32_t t6 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t6);
    ctx.ecx = static_cast<uint32_t>(t6);
    // 0x0044009c: mov eax, 0x66666667
    ctx.eax = static_cast<uint32_t>(0x66666667u);
    // 0x004400a1: imul ecx
    uint64_t t7 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t8 = static_cast<uint32_t>(t7);
    uint32_t t9 = static_cast<uint32_t>(t7 >> 32);
    ctx.eax = static_cast<uint32_t>(t8);
    ctx.edx = static_cast<uint32_t>(t9);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t7);
    // 0x004400a3: sar edx, 3
    uint32_t t10 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t11 = recomp_detail::sar<uint32_t>(ctx.edx, t10);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t10, t11);
    ctx.edx = static_cast<uint32_t>(t11);
    // 0x004400a6: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004400a8: shr eax, 0x1f
    uint32_t t12 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t13 = recomp_detail::shr<uint32_t>(ctx.eax, t12);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t12, t13);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x004400ab: add eax, edx
    uint32_t t14 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t14);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x004400ad: cmp edi, eax
    uint32_t t15 = static_cast<uint32_t>(ctx.edi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.eax, t15);
    // 0x004400af: jb 0x4400b6
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004400b6;
    goto bb_004400b1;
}
bb_004400b6: {
    // 0x004400b6: mov ecx, dword ptr [esi + 4]
    uint32_t t16 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t17 = mem.r32(t16);
    ctx.ecx = static_cast<uint32_t>(t17);
    // 0x004400b9: lea eax, [edi + edi*4]
    uint32_t t18 = recomp_detail::shl<uint32_t>(ctx.edi, 0x00000002u);
    uint32_t t19 = static_cast<uint32_t>(ctx.edi + t18);
    ctx.eax = static_cast<uint32_t>(t19);
    // 0x004400bc: lea eax, [ecx + eax*4]
    uint32_t t20 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000002u);
    uint32_t t21 = static_cast<uint32_t>(ctx.ecx + t20);
    ctx.eax = static_cast<uint32_t>(t21);
    // 0x004400bf: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004400c0 | subsystem=Replay | canonical | 15 blocks | 63 insns
void sub_004400c0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004400c0: push ebx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebx);
    // 0x004400c1: push ebp
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebp);
    // 0x004400c2: mov ebp, dword ptr [esp + 0xc]
    uint32_t t2 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t3 = mem.r32(t2);
    ctx.ebp = static_cast<uint32_t>(t3);
    // 0x004400c6: test ebp, ebp
    uint32_t t4 = static_cast<uint32_t>(ctx.ebp & ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    // 0x004400c8: push esi
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.esi);
    // 0x004400c9: jbe 0x44014a
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0044014a;
    goto bb_004400cb;
}
bb_0044014a: {
    // 0x0044014a: pop esi
    uint32_t t6 = ctx.esp;
    uint32_t t7 = mem.r32(t6);
    uint32_t t8 = static_cast<uint32_t>(t6 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    ctx.esi = static_cast<uint32_t>(t7);
    // 0x0044014b: pop ebp
    uint32_t t9 = ctx.esp;
    uint32_t t10 = mem.r32(t9);
    uint32_t t11 = static_cast<uint32_t>(t9 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    ctx.ebp = static_cast<uint32_t>(t10);
    // 0x0044014c: or eax, 0xffffffff
    uint32_t t12 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t12);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0044014f: pop ebx
    uint32_t t13 = ctx.esp;
    uint32_t t14 = mem.r32(t13);
    uint32_t t15 = static_cast<uint32_t>(t13 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    ctx.ebx = static_cast<uint32_t>(t14);
    // 0x00440150: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_004400cb: {
    // 0x004400cb: mov eax, dword ptr [edi + 0x14]
    uint32_t t16 = static_cast<uint32_t>(ctx.edi + 0x00000014u);
    uint32_t t17 = mem.r32(t16);
    ctx.eax = static_cast<uint32_t>(t17);
    // 0x004400ce: test eax, eax
    uint32_t t18 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    // 0x004400d0: jbe 0x44014a
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0044014a;
}
{
    // 0x004400d2: cmp eax, -1
    uint32_t t19 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t19);
    // 0x004400d5: jbe 0x4400dc
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_004400dc;
    goto bb_004400d7;
}
bb_004400dc: {
    // 0x004400dc: lea ecx, [eax - 1]
    uint32_t t20 = static_cast<uint32_t>(ctx.eax + 0xffffffffu);
    ctx.ecx = static_cast<uint32_t>(t20);
    goto bb_004400df;
}
bb_004400d7: {
    // 0x004400d7: or ecx, 0xffffffff
    uint32_t t21 = static_cast<uint32_t>(ctx.ecx | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t21);
    ctx.ecx = static_cast<uint32_t>(t21);
    // 0x004400da: jmp 0x4400df
}
bb_004400df: {
    // 0x004400df: cmp dword ptr [edi + 0x18], 0x10
    uint32_t t22 = static_cast<uint32_t>(ctx.edi + 0x00000018u);
    uint32_t t23 = mem.r32(t22);
    uint32_t t24 = static_cast<uint32_t>(t23 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t23, 0x00000010u, t24);
    // 0x004400e3: lea ebx, [edi + 4]
    uint32_t t25 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    ctx.ebx = static_cast<uint32_t>(t25);
    // 0x004400e6: jb 0x4400ec
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004400ec;
    goto bb_004400e8;
}
bb_004400ec: {
    // 0x004400ec: mov eax, ebx
    ctx.eax = static_cast<uint32_t>(ctx.ebx);
    goto bb_004400ee;
}
bb_004400e8: {
    // 0x004400e8: mov eax, dword ptr [ebx]
    uint32_t t26 = mem.r32(ctx.ebx);
    ctx.eax = static_cast<uint32_t>(t26);
    // 0x004400ea: jmp 0x4400ee
}
bb_004400ee: {
    // 0x004400ee: lea esi, [eax + ecx]
    uint32_t t27 = static_cast<uint32_t>(ctx.eax + ctx.ecx);
    ctx.esi = static_cast<uint32_t>(t27);
    // 0x004400f1: movsx eax, byte ptr [esi]
    uint8_t t28 = mem.r8(ctx.esi);
    uint32_t t29 = recomp_detail::sext8_32(static_cast<uint8_t>(t28));
    ctx.eax = static_cast<uint32_t>(t29);
    // 0x004400f4: push ebp
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, ctx.ebp);
    // 0x004400f5: push eax
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, ctx.eax);
    // 0x004400f6: push 0x535314
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x00535314u);
    // 0x004400fb: call 0x4e1d40
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x00440100u);
    hle_crt_004e1d40(ctx, mem);
    // 0x00440100: add esp, 0xc
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t34);
    ctx.esp = static_cast<uint32_t>(t34);
    // 0x00440103: test eax, eax
    uint32_t t35 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t35);
    // 0x00440105: jne 0x44012c
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0044012c;
    goto bb_00440107;
}
bb_0044012c: {
    // 0x0044012c: cmp dword ptr [edi + 0x18], 0x10
    uint32_t t36 = static_cast<uint32_t>(ctx.edi + 0x00000018u);
    uint32_t t37 = mem.r32(t36);
    uint32_t t38 = static_cast<uint32_t>(t37 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t37, 0x00000010u, t38);
    // 0x00440130: jb 0x44013e
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0044013e;
    goto bb_00440132;
}
bb_00440107: {
    // 0x00440107: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x00440109: call 0x407ab0
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, 0x0044010eu);
    sub_00407ab0(ctx, mem);
    // 0x0044010e: cmp esi, eax
    uint32_t t40 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t40);
    // 0x00440110: je 0x44014a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0044014a;
    goto bb_00440112;
}
bb_0044013e: {
    // 0x0044013e: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x00440140: pop esi
    uint32_t t41 = ctx.esp;
    uint32_t t42 = mem.r32(t41);
    uint32_t t43 = static_cast<uint32_t>(t41 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    ctx.esi = static_cast<uint32_t>(t42);
    // 0x00440141: mov ecx, ebx
    ctx.ecx = static_cast<uint32_t>(ctx.ebx);
    // 0x00440143: pop ebp
    uint32_t t44 = ctx.esp;
    uint32_t t45 = mem.r32(t44);
    uint32_t t46 = static_cast<uint32_t>(t44 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    ctx.ebp = static_cast<uint32_t>(t45);
    // 0x00440144: sub eax, ecx
    uint32_t t47 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t47);
    ctx.eax = static_cast<uint32_t>(t47);
    // 0x00440146: pop ebx
    uint32_t t48 = ctx.esp;
    uint32_t t49 = mem.r32(t48);
    uint32_t t50 = static_cast<uint32_t>(t48 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    ctx.ebx = static_cast<uint32_t>(t49);
    // 0x00440147: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_00440132: {
    // 0x00440132: mov ecx, dword ptr [ebx]
    uint32_t t51 = mem.r32(ctx.ebx);
    ctx.ecx = static_cast<uint32_t>(t51);
    // 0x00440134: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x00440136: pop esi
    uint32_t t52 = ctx.esp;
    uint32_t t53 = mem.r32(t52);
    uint32_t t54 = static_cast<uint32_t>(t52 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    ctx.esi = static_cast<uint32_t>(t53);
    // 0x00440137: pop ebp
    uint32_t t55 = ctx.esp;
    uint32_t t56 = mem.r32(t55);
    uint32_t t57 = static_cast<uint32_t>(t55 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    ctx.ebp = static_cast<uint32_t>(t56);
    // 0x00440138: sub eax, ecx
    uint32_t t58 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t58);
    ctx.eax = static_cast<uint32_t>(t58);
    // 0x0044013a: pop ebx
    uint32_t t59 = ctx.esp;
    uint32_t t60 = mem.r32(t59);
    uint32_t t61 = static_cast<uint32_t>(t59 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    ctx.ebx = static_cast<uint32_t>(t60);
    // 0x0044013b: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_00440112: {
    // 0x00440112: movsx ecx, byte ptr [esi - 1]
    uint32_t t62 = static_cast<uint32_t>(ctx.esi + 0xffffffffu);
    uint8_t t63 = mem.r8(t62);
    uint32_t t64 = recomp_detail::sext8_32(static_cast<uint8_t>(t63));
    ctx.ecx = static_cast<uint32_t>(t64);
    // 0x00440116: sub esi, 1
    uint32_t t65 = static_cast<uint32_t>(ctx.esi - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00000001u, t65);
    ctx.esi = static_cast<uint32_t>(t65);
    // 0x00440119: push ebp
    uint32_t t66 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    mem.w32(t66, ctx.ebp);
    // 0x0044011a: push ecx
    uint32_t t67 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t67);
    mem.w32(t67, ctx.ecx);
    // 0x0044011b: push 0x535314
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, 0x00535314u);
    // 0x00440120: call 0x4e1d40
    uint32_t t69 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    mem.w32(t69, 0x00440125u);
    hle_crt_004e1d40(ctx, mem);
    // 0x00440125: add esp, 0xc
    uint32_t t70 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t70);
    ctx.esp = static_cast<uint32_t>(t70);
    // 0x00440128: test eax, eax
    uint32_t t71 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t71);
    // 0x0044012a: je 0x440107
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00440107;
    goto bb_0044012c;
}
}

// sub_00440190 | subsystem=Replay | canonical | 17 blocks | 88 insns
void sub_00440190(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00440190: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x00440192: push 0x516228
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00516228u);
    // 0x00440197: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0044019d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0044019e: sub esp, 0xc
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x0000000cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x0000000cu, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x004401a1: push ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebx);
    // 0x004401a2: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x004401a3: push edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edi);
    // 0x004401a4: mov eax, dword ptr [0x54b458]
    uint32_t t9 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x004401a9: xor eax, esp
    uint32_t t10 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x004401ab: push eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.eax);
    // 0x004401ac: lea eax, [esp + 0x1c]
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x004401b0: mov dword ptr fs:[0], eax
    uint32_t t13 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t13, ctx.eax);
    // 0x004401b6: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004401b8: mov dword ptr [esp + 0x24], 0
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t14, 0x00000000u);
    // 0x004401c0: mov edi, dword ptr [esi + 4]
    uint32_t t15 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t16 = mem.r32(t15);
    ctx.edi = static_cast<uint32_t>(t16);
    // 0x004401c3: test edi, edi
    uint32_t t17 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t17);
    // 0x004401c5: je 0x4401e4
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004401e4;
    goto bb_004401c7;
}
bb_004401e4: {
    // 0x004401e4: mov ebx, dword ptr [esi + 8]
    uint32_t t18 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t19 = mem.r32(t18);
    ctx.ebx = static_cast<uint32_t>(t19);
    // 0x004401e7: cmp edi, ebx
    uint32_t t20 = static_cast<uint32_t>(ctx.edi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebx, t20);
    // 0x004401e9: jbe 0x4401f0
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_004401f0;
    goto bb_004401eb;
}
bb_004401c7: {
    // 0x004401c7: mov ebx, dword ptr [esi + 8]
    uint32_t t21 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t22 = mem.r32(t21);
    ctx.ebx = static_cast<uint32_t>(t22);
    // 0x004401ca: mov ecx, ebx
    ctx.ecx = static_cast<uint32_t>(ctx.ebx);
    // 0x004401cc: sub ecx, edi
    uint32_t t23 = static_cast<uint32_t>(ctx.ecx - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.edi, t23);
    ctx.ecx = static_cast<uint32_t>(t23);
    // 0x004401ce: mov eax, 0x66666667
    ctx.eax = static_cast<uint32_t>(0x66666667u);
    // 0x004401d3: imul ecx
    uint64_t t24 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t25 = static_cast<uint32_t>(t24);
    uint32_t t26 = static_cast<uint32_t>(t24 >> 32);
    ctx.eax = static_cast<uint32_t>(t25);
    ctx.edx = static_cast<uint32_t>(t26);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t24);
    // 0x004401d5: sar edx, 3
    uint32_t t27 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t28 = recomp_detail::sar<uint32_t>(ctx.edx, t27);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t27, t28);
    ctx.edx = static_cast<uint32_t>(t28);
    // 0x004401d8: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004401da: shr eax, 0x1f
    uint32_t t29 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t30 = recomp_detail::shr<uint32_t>(ctx.eax, t29);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t29, t30);
    ctx.eax = static_cast<uint32_t>(t30);
    // 0x004401dd: add eax, edx
    uint32_t t31 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t31);
    ctx.eax = static_cast<uint32_t>(t31);
    // 0x004401df: cmp eax, 0x64
    uint32_t t32 = static_cast<uint32_t>(ctx.eax - 0x00000064u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000064u, t32);
    // 0x004401e2: jae 0x440224
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_00440224;
    goto bb_004401e4;
}
bb_004401f0: {
    // 0x004401f0: mov eax, dword ptr [esi + 4]
    uint32_t t33 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t34 = mem.r32(t33);
    ctx.eax = static_cast<uint32_t>(t34);
    // 0x004401f3: test eax, eax
    uint32_t t35 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t35);
    // 0x004401f5: je 0x44020d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0044020d;
    goto bb_004401f7;
}
bb_004401eb: {
    // 0x004401eb: call 0x4e0bf2
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, 0x004401f0u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004401f0;
}
bb_00440224: {
    // 0x00440224: jbe 0x440264
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_00440264;
    goto bb_00440226;
}
bb_0044020d: {
    // 0x0044020d: push ebx
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, ctx.ebx);
    // 0x0044020e: push esi
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, ctx.esi);
    // 0x0044020f: lea ecx, [esp + 0x34]
    uint32_t t39 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    ctx.ecx = static_cast<uint32_t>(t39);
    // 0x00440213: push ecx
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, ctx.ecx);
    // 0x00440214: mov edx, 0x64
    ctx.edx = static_cast<uint32_t>(0x00000064u);
    // 0x00440219: sub edx, eax
    uint32_t t41 = static_cast<uint32_t>(ctx.edx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.eax, t41);
    ctx.edx = static_cast<uint32_t>(t41);
    // 0x0044021b: push edx
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, ctx.edx);
    // 0x0044021c: push esi
    uint32_t t43 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    mem.w32(t43, ctx.esi);
    // 0x0044021d: call 0x440380
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, 0x00440222u);
    sub_00440380(ctx, mem);
    // 0x00440222: jmp 0x440264
    goto bb_00440264;
}
bb_004401f7: {
    // 0x004401f7: mov ecx, dword ptr [esi + 8]
    uint32_t t45 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t46 = mem.r32(t45);
    ctx.ecx = static_cast<uint32_t>(t46);
    // 0x004401fa: sub ecx, eax
    uint32_t t47 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t47);
    ctx.ecx = static_cast<uint32_t>(t47);
    // 0x004401fc: mov eax, 0x66666667
    ctx.eax = static_cast<uint32_t>(0x66666667u);
    // 0x00440201: imul ecx
    uint64_t t48 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t49 = static_cast<uint32_t>(t48);
    uint32_t t50 = static_cast<uint32_t>(t48 >> 32);
    ctx.eax = static_cast<uint32_t>(t49);
    ctx.edx = static_cast<uint32_t>(t50);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t48);
    // 0x00440203: sar edx, 3
    uint32_t t51 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t52 = recomp_detail::sar<uint32_t>(ctx.edx, t51);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t51, t52);
    ctx.edx = static_cast<uint32_t>(t52);
    // 0x00440206: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x00440208: shr eax, 0x1f
    uint32_t t53 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t54 = recomp_detail::shr<uint32_t>(ctx.eax, t53);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t53, t54);
    ctx.eax = static_cast<uint32_t>(t54);
    // 0x0044020b: add eax, edx
    uint32_t t55 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t55);
    ctx.eax = static_cast<uint32_t>(t55);
    goto bb_0044020d;
}
bb_00440264: {
    // 0x00440264: lea ebx, [esp + 0x2c]
    uint32_t t56 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    ctx.ebx = static_cast<uint32_t>(t56);
    // 0x00440268: mov dword ptr [esp + 0x24], 0xffffffff
    uint32_t t57 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t57, 0xffffffffu);
    // 0x00440270: call 0x43c280
    uint32_t t58 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    mem.w32(t58, 0x00440275u);
    sub_0043c280(ctx, mem);
    // 0x00440275: mov ecx, dword ptr [esp + 0x1c]
    uint32_t t59 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t60 = mem.r32(t59);
    ctx.ecx = static_cast<uint32_t>(t60);
    // 0x00440279: mov dword ptr fs:[0], ecx
    uint32_t t61 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t61, ctx.ecx);
    // 0x00440280: pop ecx
    uint32_t t62 = ctx.esp;
    uint32_t t63 = mem.r32(t62);
    uint32_t t64 = static_cast<uint32_t>(t62 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    ctx.ecx = static_cast<uint32_t>(t63);
    // 0x00440281: pop edi
    uint32_t t65 = ctx.esp;
    uint32_t t66 = mem.r32(t65);
    uint32_t t67 = static_cast<uint32_t>(t65 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t67);
    ctx.edi = static_cast<uint32_t>(t66);
    // 0x00440282: pop esi
    uint32_t t68 = ctx.esp;
    uint32_t t69 = mem.r32(t68);
    uint32_t t70 = static_cast<uint32_t>(t68 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    ctx.esi = static_cast<uint32_t>(t69);
    // 0x00440283: pop ebx
    uint32_t t71 = ctx.esp;
    uint32_t t72 = mem.r32(t71);
    uint32_t t73 = static_cast<uint32_t>(t71 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    ctx.ebx = static_cast<uint32_t>(t72);
    // 0x00440284: add esp, 0x18
    uint32_t t74 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000018u, t74);
    ctx.esp = static_cast<uint32_t>(t74);
    // 0x00440287: ret 0x14
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 20u;
    return;
}
bb_00440226: {
    // 0x00440226: cmp edi, ebx
    uint32_t t75 = static_cast<uint32_t>(ctx.edi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebx, t75);
    // 0x00440228: jbe 0x44022f
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0044022f;
    goto bb_0044022a;
}
bb_0044022f: {
    // 0x0044022f: mov edi, dword ptr [esi + 4]
    uint32_t t76 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t77 = mem.r32(t76);
    ctx.edi = static_cast<uint32_t>(t77);
    // 0x00440232: cmp edi, dword ptr [esi + 8]
    uint32_t t78 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t79 = mem.r32(t78);
    uint32_t t80 = static_cast<uint32_t>(ctx.edi - t79);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, t79, t80);
    // 0x00440235: jbe 0x44023c
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0044023c;
    goto bb_00440237;
}
bb_0044022a: {
    // 0x0044022a: call 0x4e0bf2
    uint32_t t81 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    mem.w32(t81, 0x0044022fu);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0044022f;
}
bb_0044023c: {
    // 0x0044023c: mov dword ptr [esp + 0x14], edi
    uint32_t t82 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t82, ctx.edi);
    // 0x00440240: add edi, 0x7d0
    uint32_t t83 = static_cast<uint32_t>(ctx.edi + 0x000007d0u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x000007d0u, t83);
    ctx.edi = static_cast<uint32_t>(t83);
    // 0x00440246: cmp edi, dword ptr [esi + 8]
    uint32_t t84 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t85 = mem.r32(t84);
    uint32_t t86 = static_cast<uint32_t>(ctx.edi - t85);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, t85, t86);
    // 0x00440249: ja 0x440250
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_00440250;
    goto bb_0044024b;
}
bb_00440237: {
    // 0x00440237: call 0x4e0bf2
    uint32_t t87 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t87);
    mem.w32(t87, 0x0044023cu);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_0044023c;
}
bb_00440250: {
    // 0x00440250: call 0x4e0bf2
    uint32_t t88 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t88);
    mem.w32(t88, 0x00440255u);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_00440255;
}
bb_0044024b: {
    // 0x0044024b: cmp edi, dword ptr [esi + 4]
    uint32_t t89 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t90 = mem.r32(t89);
    uint32_t t91 = static_cast<uint32_t>(ctx.edi - t90);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, t90, t91);
    // 0x0044024e: jae 0x440255
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_00440255;
    goto bb_00440250;
}
bb_00440255: {
    // 0x00440255: push ebx
    uint32_t t92 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    mem.w32(t92, ctx.ebx);
    // 0x00440256: push esi
    uint32_t t93 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    mem.w32(t93, ctx.esi);
    // 0x00440257: push edi
    uint32_t t94 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t94);
    mem.w32(t94, ctx.edi);
    // 0x00440258: push esi
    uint32_t t95 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t95);
    mem.w32(t95, ctx.esi);
    // 0x00440259: lea eax, [esp + 0x20]
    uint32_t t96 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    ctx.eax = static_cast<uint32_t>(t96);
    // 0x0044025d: push eax
    uint32_t t97 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t97);
    mem.w32(t97, ctx.eax);
    // 0x0044025e: push esi
    uint32_t t98 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t98);
    mem.w32(t98, ctx.esi);
    // 0x0044025f: call 0x440290
    uint32_t t99 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t99);
    mem.w32(t99, 0x00440264u);
    sub_00440290(ctx, mem);
    goto bb_00440264;
}
}

// sub_00440290 | subsystem=Replay | canonical | 8 blocks | 48 insns
void sub_00440290(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00440290: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x00440291: push ebx
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebx);
    // 0x00440292: push ebp
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebp);
    // 0x00440293: mov ebp, dword ptr [esp + 0x10]
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t4 = mem.r32(t3);
    ctx.ebp = static_cast<uint32_t>(t4);
    // 0x00440297: push esi
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.esi);
    // 0x00440298: mov esi, dword ptr [esp + 0x1c]
    uint32_t t6 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t7 = mem.r32(t6);
    ctx.esi = static_cast<uint32_t>(t7);
    // 0x0044029c: test esi, esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t8);
    // 0x0044029e: push edi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.edi);
    // 0x0044029f: je 0x4402a7
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004402a7;
    goto bb_004402a1;
}
bb_004402a7: {
    // 0x004402a7: call 0x4e0bf2
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x004402acu);
    hle_crt_004e0bf2(ctx, mem);
    goto bb_004402ac;
}
bb_004402a1: {
    // 0x004402a1: cmp esi, dword ptr [esp + 0x28]
    uint32_t t11 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t12 = mem.r32(t11);
    uint32_t t13 = static_cast<uint32_t>(ctx.esi - t12);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, t12, t13);
    // 0x004402a5: je 0x4402ac
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004402ac;
    goto bb_004402a7;
}
bb_004402ac: {
    // 0x004402ac: mov ecx, dword ptr [esp + 0x2c]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    uint32_t t15 = mem.r32(t14);
    ctx.ecx = static_cast<uint32_t>(t15);
    // 0x004402b0: mov eax, dword ptr [esp + 0x24]
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t17 = mem.r32(t16);
    ctx.eax = static_cast<uint32_t>(t17);
    // 0x004402b4: cmp eax, ecx
    uint32_t t18 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t18);
    // 0x004402b6: je 0x4402f9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004402f9;
    goto bb_004402b8;
}
bb_004402f9: {
    // 0x004402f9: mov ecx, dword ptr [esp + 0x1c]
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t20 = mem.r32(t19);
    ctx.ecx = static_cast<uint32_t>(t20);
    // 0x004402fd: pop edi
    uint32_t t21 = ctx.esp;
    uint32_t t22 = mem.r32(t21);
    uint32_t t23 = static_cast<uint32_t>(t21 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    ctx.edi = static_cast<uint32_t>(t22);
    // 0x004402fe: mov dword ptr [ecx], esi
    mem.w32(ctx.ecx, ctx.esi);
    // 0x00440300: pop esi
    uint32_t t24 = ctx.esp;
    uint32_t t25 = mem.r32(t24);
    uint32_t t26 = static_cast<uint32_t>(t24 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    ctx.esi = static_cast<uint32_t>(t25);
    // 0x00440301: pop ebp
    uint32_t t27 = ctx.esp;
    uint32_t t28 = mem.r32(t27);
    uint32_t t29 = static_cast<uint32_t>(t27 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    ctx.ebp = static_cast<uint32_t>(t28);
    // 0x00440302: mov dword ptr [ecx + 4], eax
    uint32_t t30 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    mem.w32(t30, ctx.eax);
    // 0x00440305: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x00440307: pop ebx
    uint32_t t31 = ctx.esp;
    uint32_t t32 = mem.r32(t31);
    uint32_t t33 = static_cast<uint32_t>(t31 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    ctx.ebx = static_cast<uint32_t>(t32);
    // 0x00440308: pop ecx
    uint32_t t34 = ctx.esp;
    uint32_t t35 = mem.r32(t34);
    uint32_t t36 = static_cast<uint32_t>(t34 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    ctx.ecx = static_cast<uint32_t>(t35);
    // 0x00440309: ret 0x18
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 24u;
    return;
}
bb_004402b8: {
    // 0x004402b8: mov esi, dword ptr [ebp + 8]
    uint32_t t37 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t38 = mem.r32(t37);
    ctx.esi = static_cast<uint32_t>(t38);
    // 0x004402bb: mov byte ptr [esp + 0x18], 0
    uint32_t t39 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w8(t39, uint8_t{0x00u});
    // 0x004402c0: mov edx, dword ptr [esp + 0x18]
    uint32_t t40 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t41 = mem.r32(t40);
    ctx.edx = static_cast<uint32_t>(t41);
    // 0x004402c4: push edx
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, ctx.edx);
    // 0x004402c5: mov edx, dword ptr [esp + 0x1c]
    uint32_t t43 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t44 = mem.r32(t43);
    ctx.edx = static_cast<uint32_t>(t44);
    // 0x004402c9: push edx
    uint32_t t45 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    mem.w32(t45, ctx.edx);
    // 0x004402ca: mov edx, dword ptr [esp + 0x20]
    uint32_t t46 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t47 = mem.r32(t46);
    ctx.edx = static_cast<uint32_t>(t47);
    // 0x004402ce: push edx
    uint32_t t48 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    mem.w32(t48, ctx.edx);
    // 0x004402cf: call 0x440790
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, 0x004402d4u);
    sub_00440790(ctx, mem);
    // 0x004402d4: mov edi, dword ptr [ebp + 8]
    uint32_t t50 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t51 = mem.r32(t50);
    ctx.edi = static_cast<uint32_t>(t51);
    // 0x004402d7: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004402d9: add esp, 0xc
    uint32_t t52 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t52);
    ctx.esp = static_cast<uint32_t>(t52);
    // 0x004402dc: cmp esi, edi
    uint32_t t53 = static_cast<uint32_t>(ctx.esi - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edi, t53);
    // 0x004402de: mov ebx, esi
    ctx.ebx = static_cast<uint32_t>(ctx.esi);
    // 0x004402e0: je 0x4402ee
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004402ee;
    goto bb_004402e2;
}
bb_004402ee: {
    // 0x004402ee: mov eax, dword ptr [esp + 0x24]
    uint32_t t54 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t55 = mem.r32(t54);
    ctx.eax = static_cast<uint32_t>(t55);
    // 0x004402f2: mov dword ptr [ebp + 8], esi
    uint32_t t56 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    mem.w32(t56, ctx.esi);
    // 0x004402f5: mov esi, dword ptr [esp + 0x20]
    uint32_t t57 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t58 = mem.r32(t57);
    ctx.esi = static_cast<uint32_t>(t58);
    goto bb_004402f9;
}
bb_004402e2: {
    // 0x004402e2: call 0x43c280
    uint32_t t59 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    mem.w32(t59, 0x004402e7u);
    sub_0043c280(ctx, mem);
    // 0x004402e7: add ebx, 0x14
    uint32_t t60 = static_cast<uint32_t>(ctx.ebx + 0x00000014u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebx, 0x00000014u, t60);
    ctx.ebx = static_cast<uint32_t>(t60);
    // 0x004402ea: cmp ebx, edi
    uint32_t t61 = static_cast<uint32_t>(ctx.ebx - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.edi, t61);
    // 0x004402ec: jne 0x4402e2
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004402e2;
    goto bb_004402ee;
}
}

// sub_00440310 | subsystem=Replay | canonical | 3 blocks | 10 insns
void sub_00440310(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00440310: push ebx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebx);
    // 0x00440311: mov ebx, eax
    ctx.ebx = static_cast<uint32_t>(ctx.eax);
    // 0x00440313: cmp ebx, esi
    uint32_t t1 = static_cast<uint32_t>(ctx.ebx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.esi, t1);
    // 0x00440315: je 0x440323
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00440323;
    goto bb_00440317;
}
bb_00440323: {
    // 0x00440323: pop ebx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ebx = static_cast<uint32_t>(t3);
    // 0x00440324: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00440317: {
    // 0x00440317: call 0x43c280
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, 0x0044031cu);
    sub_0043c280(ctx, mem);
    // 0x0044031c: add ebx, 0x14
    uint32_t t6 = static_cast<uint32_t>(ctx.ebx + 0x00000014u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebx, 0x00000014u, t6);
    ctx.ebx = static_cast<uint32_t>(t6);
    // 0x0044031f: cmp ebx, esi
    uint32_t t7 = static_cast<uint32_t>(ctx.ebx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.esi, t7);
    // 0x00440321: jne 0x440317
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00440317;
    goto bb_00440323;
}
}

// sub_00440330 | subsystem=Replay | canonical | 5 blocks | 24 insns
void sub_00440330(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00440330: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x00440331: push ebx
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebx);
    // 0x00440332: mov ebx, dword ptr [edi + 4]
    uint32_t t2 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    uint32_t t3 = mem.r32(t2);
    ctx.ebx = static_cast<uint32_t>(t3);
    // 0x00440335: test ebx, ebx
    uint32_t t4 = static_cast<uint32_t>(ctx.ebx & ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    // 0x00440337: push esi
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.esi);
    // 0x00440338: je 0x440359
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00440359;
    goto bb_0044033a;
}
bb_00440359: {
    // 0x00440359: pop esi
    uint32_t t6 = ctx.esp;
    uint32_t t7 = mem.r32(t6);
    uint32_t t8 = static_cast<uint32_t>(t6 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    ctx.esi = static_cast<uint32_t>(t7);
    // 0x0044035a: mov dword ptr [edi + 4], 0
    uint32_t t9 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    mem.w32(t9, 0x00000000u);
    // 0x00440361: mov dword ptr [edi + 8], 0
    uint32_t t10 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    mem.w32(t10, 0x00000000u);
    // 0x00440368: mov dword ptr [edi + 0xc], 0
    uint32_t t11 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    mem.w32(t11, 0x00000000u);
    // 0x0044036f: pop ebx
    uint32_t t12 = ctx.esp;
    uint32_t t13 = mem.r32(t12);
    uint32_t t14 = static_cast<uint32_t>(t12 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    ctx.ebx = static_cast<uint32_t>(t13);
    // 0x00440370: pop ecx
    uint32_t t15 = ctx.esp;
    uint32_t t16 = mem.r32(t15);
    uint32_t t17 = static_cast<uint32_t>(t15 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    ctx.ecx = static_cast<uint32_t>(t16);
    // 0x00440371: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0044033a: {
    // 0x0044033a: mov esi, dword ptr [edi + 8]
    uint32_t t18 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t19 = mem.r32(t18);
    ctx.esi = static_cast<uint32_t>(t19);
    // 0x0044033d: cmp ebx, esi
    uint32_t t20 = static_cast<uint32_t>(ctx.ebx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.esi, t20);
    // 0x0044033f: je 0x44034d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0044034d;
    goto bb_00440341;
}
bb_0044034d: {
    // 0x0044034d: mov eax, dword ptr [edi + 4]
    uint32_t t21 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    uint32_t t22 = mem.r32(t21);
    ctx.eax = static_cast<uint32_t>(t22);
    // 0x00440350: push eax
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, ctx.eax);
    // 0x00440351: call 0x4e02f3
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x00440356u);
    hle_crt_004e02f3(ctx, mem);
    // 0x00440356: add esp, 4
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t25);
    ctx.esp = static_cast<uint32_t>(t25);
    goto bb_00440359;
}
bb_00440341: {
    // 0x00440341: call 0x43c280
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x00440346u);
    sub_0043c280(ctx, mem);
    // 0x00440346: add ebx, 0x14
    uint32_t t27 = static_cast<uint32_t>(ctx.ebx + 0x00000014u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebx, 0x00000014u, t27);
    ctx.ebx = static_cast<uint32_t>(t27);
    // 0x00440349: cmp ebx, esi
    uint32_t t28 = static_cast<uint32_t>(ctx.ebx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.esi, t28);
    // 0x0044034b: jne 0x440341
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00440341;
    goto bb_0044034d;
}
}

// sub_00440380 | subsystem=Replay | canonical | 34 blocks | 271 insns
void sub_00440380(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00440380: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x00440381: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x00440383: push -1
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0xffffffffu);
    // 0x00440385: push 0x5161f8
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x005161f8u);
    // 0x0044038a: mov eax, dword ptr fs:[0]
    uint32_t t3 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t4 = mem.r32(t3);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x00440390: push eax
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.eax);
    // 0x00440391: sub esp, 0x20
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000020u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000020u, t6);
    ctx.esp = static_cast<uint32_t>(t6);
    // 0x00440394: push ebx
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.ebx);
    // 0x00440395: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x00440396: push edi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.edi);
    // 0x00440397: mov eax, dword ptr [0x54b458]
    uint32_t t10 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0044039c: xor eax, ebp
    uint32_t t11 = static_cast<uint32_t>(ctx.eax ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x0044039e: push eax
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.eax);
    // 0x0044039f: lea eax, [ebp - 0xc]
    uint32_t t13 = static_cast<uint32_t>(ctx.ebp + 0xfffffff4u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x004403a2: mov dword ptr fs:[0], eax
    uint32_t t14 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t14, ctx.eax);
    // 0x004403a8: mov dword ptr [ebp - 0x10], esp
    uint32_t t15 = static_cast<uint32_t>(ctx.ebp + 0xfffffff0u);
    mem.w32(t15, ctx.esp);
    // 0x004403ab: mov eax, dword ptr [ebp + 0x10]
    uint32_t t16 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    uint32_t t17 = mem.r32(t16);
    ctx.eax = static_cast<uint32_t>(t17);
    // 0x004403ae: mov ebx, dword ptr [ebp + 0xc]
    uint32_t t18 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t19 = mem.r32(t18);
    ctx.ebx = static_cast<uint32_t>(t19);
    // 0x004403b1: mov edi, dword ptr [ebp + 8]
    uint32_t t20 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t21 = mem.r32(t20);
    ctx.edi = static_cast<uint32_t>(t21);
    // 0x004403b4: mov ecx, dword ptr [eax]
    uint32_t t22 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t22);
    // 0x004403b6: mov edx, dword ptr [eax + 4]
    uint32_t t23 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t24 = mem.r32(t23);
    ctx.edx = static_cast<uint32_t>(t24);
    // 0x004403b9: mov dword ptr [ebp - 0x28], ecx
    uint32_t t25 = static_cast<uint32_t>(ctx.ebp + 0xffffffd8u);
    mem.w32(t25, ctx.ecx);
    // 0x004403bc: mov ecx, dword ptr [eax + 8]
    uint32_t t26 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    uint32_t t27 = mem.r32(t26);
    ctx.ecx = static_cast<uint32_t>(t27);
    // 0x004403bf: mov dword ptr [ebp - 0x24], edx
    uint32_t t28 = static_cast<uint32_t>(ctx.ebp + 0xffffffdcu);
    mem.w32(t28, ctx.edx);
    // 0x004403c2: mov edx, dword ptr [eax + 0xc]
    uint32_t t29 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    uint32_t t30 = mem.r32(t29);
    ctx.edx = static_cast<uint32_t>(t30);
    // 0x004403c5: mov eax, dword ptr [eax + 0x10]
    uint32_t t31 = static_cast<uint32_t>(ctx.eax + 0x00000010u);
    uint32_t t32 = mem.r32(t31);
    ctx.eax = static_cast<uint32_t>(t32);
    // 0x004403c8: mov dword ptr [ebp - 0x20], ecx
    uint32_t t33 = static_cast<uint32_t>(ctx.ebp + 0xffffffe0u);
    mem.w32(t33, ctx.ecx);
    // 0x004403cb: mov dword ptr [ebp - 0x1c], edx
    uint32_t t34 = static_cast<uint32_t>(ctx.ebp + 0xffffffe4u);
    mem.w32(t34, ctx.edx);
    // 0x004403ce: mov dword ptr [ebp - 0x18], eax
    uint32_t t35 = static_cast<uint32_t>(ctx.ebp + 0xffffffe8u);
    mem.w32(t35, ctx.eax);
    // 0x004403d1: xor esi, esi
    uint32_t t36 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t36);
    ctx.esi = static_cast<uint32_t>(t36);
    // 0x004403d3: mov dword ptr [ebp - 4], esi
    uint32_t t37 = static_cast<uint32_t>(ctx.ebp + 0xfffffffcu);
    mem.w32(t37, ctx.esi);
    // 0x004403d6: mov ecx, dword ptr [edi + 4]
    uint32_t t38 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    uint32_t t39 = mem.r32(t38);
    ctx.ecx = static_cast<uint32_t>(t39);
    // 0x004403d9: cmp ecx, esi
    uint32_t t40 = static_cast<uint32_t>(ctx.ecx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.esi, t40);
    // 0x004403db: je 0x4403f5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004403f5;
    goto bb_004403dd;
}
bb_004403f5: {
    // 0x004403f5: test ebx, ebx
    uint32_t t41 = static_cast<uint32_t>(ctx.ebx & ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t41);
    // 0x004403f7: je 0x44068d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0044068d;
    goto bb_004403fd;
}
bb_004403dd: {
    // 0x004403dd: mov edx, dword ptr [edi + 0xc]
    uint32_t t42 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    uint32_t t43 = mem.r32(t42);
    ctx.edx = static_cast<uint32_t>(t43);
    // 0x004403e0: sub edx, ecx
    uint32_t t44 = static_cast<uint32_t>(ctx.edx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ecx, t44);
    ctx.edx = static_cast<uint32_t>(t44);
    // 0x004403e2: mov eax, 0x66666667
    ctx.eax = static_cast<uint32_t>(0x66666667u);
    // 0x004403e7: imul edx
    uint64_t t45 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.edx)));
    uint32_t t46 = static_cast<uint32_t>(t45);
    uint32_t t47 = static_cast<uint32_t>(t45 >> 32);
    ctx.eax = static_cast<uint32_t>(t46);
    ctx.edx = static_cast<uint32_t>(t47);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t45);
    // 0x004403e9: sar edx, 3
    uint32_t t48 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t49 = recomp_detail::sar<uint32_t>(ctx.edx, t48);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t48, t49);
    ctx.edx = static_cast<uint32_t>(t49);
    // 0x004403ec: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004403ee: shr eax, 0x1f
    uint32_t t50 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t51 = recomp_detail::shr<uint32_t>(ctx.eax, t50);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t50, t51);
    ctx.eax = static_cast<uint32_t>(t51);
    // 0x004403f1: add eax, edx
    uint32_t t52 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t52);
    ctx.eax = static_cast<uint32_t>(t52);
    // 0x004403f3: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    goto bb_004403f5;
}
bb_0044068d: {
    // 0x0044068d: lea ebx, [ebp - 0x28]
    uint32_t t53 = static_cast<uint32_t>(ctx.ebp + 0xffffffd8u);
    ctx.ebx = static_cast<uint32_t>(t53);
    // 0x00440690: mov dword ptr [ebp - 4], 0xffffffff
    uint32_t t54 = static_cast<uint32_t>(ctx.ebp + 0xfffffffcu);
    mem.w32(t54, 0xffffffffu);
    // 0x00440697: call 0x43c280
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, 0x0044069cu);
    sub_0043c280(ctx, mem);
    // 0x0044069c: mov ecx, dword ptr [ebp - 0xc]
    uint32_t t56 = static_cast<uint32_t>(ctx.ebp + 0xfffffff4u);
    uint32_t t57 = mem.r32(t56);
    ctx.ecx = static_cast<uint32_t>(t57);
    // 0x0044069f: mov dword ptr fs:[0], ecx
    uint32_t t58 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t58, ctx.ecx);
    // 0x004406a6: pop ecx
    uint32_t t59 = ctx.esp;
    uint32_t t60 = mem.r32(t59);
    uint32_t t61 = static_cast<uint32_t>(t59 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    ctx.ecx = static_cast<uint32_t>(t60);
    // 0x004406a7: pop edi
    uint32_t t62 = ctx.esp;
    uint32_t t63 = mem.r32(t62);
    uint32_t t64 = static_cast<uint32_t>(t62 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    ctx.edi = static_cast<uint32_t>(t63);
    // 0x004406a8: pop esi
    uint32_t t65 = ctx.esp;
    uint32_t t66 = mem.r32(t65);
    uint32_t t67 = static_cast<uint32_t>(t65 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t67);
    ctx.esi = static_cast<uint32_t>(t66);
    // 0x004406a9: pop ebx
    uint32_t t68 = ctx.esp;
    uint32_t t69 = mem.r32(t68);
    uint32_t t70 = static_cast<uint32_t>(t68 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    ctx.ebx = static_cast<uint32_t>(t69);
    // 0x004406aa: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x004406ac: pop ebp
    uint32_t t71 = ctx.esp;
    uint32_t t72 = mem.r32(t71);
    uint32_t t73 = static_cast<uint32_t>(t71 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    ctx.ebp = static_cast<uint32_t>(t72);
    // 0x004406ad: ret 0x14
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 20u;
    return;
}
bb_004403fd: {
    // 0x004403fd: test ecx, ecx
    uint32_t t74 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t74);
    // 0x004403ff: jne 0x440405
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00440405;
    goto bb_00440401;
}
bb_00440405: {
    // 0x00440405: mov edx, dword ptr [edi + 8]
    uint32_t t75 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t76 = mem.r32(t75);
    ctx.edx = static_cast<uint32_t>(t76);
    // 0x00440408: sub edx, ecx
    uint32_t t77 = static_cast<uint32_t>(ctx.edx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ecx, t77);
    ctx.edx = static_cast<uint32_t>(t77);
    // 0x0044040a: mov eax, 0x66666667
    ctx.eax = static_cast<uint32_t>(0x66666667u);
    // 0x0044040f: imul edx
    uint64_t t78 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.edx)));
    uint32_t t79 = static_cast<uint32_t>(t78);
    uint32_t t80 = static_cast<uint32_t>(t78 >> 32);
    ctx.eax = static_cast<uint32_t>(t79);
    ctx.edx = static_cast<uint32_t>(t80);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t78);
    // 0x00440411: sar edx, 3
    uint32_t t81 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t82 = recomp_detail::sar<uint32_t>(ctx.edx, t81);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t81, t82);
    ctx.edx = static_cast<uint32_t>(t82);
    // 0x00440414: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x00440416: shr eax, 0x1f
    uint32_t t83 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t84 = recomp_detail::shr<uint32_t>(ctx.eax, t83);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t83, t84);
    ctx.eax = static_cast<uint32_t>(t84);
    // 0x00440419: add eax, edx
    uint32_t t85 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t85);
    ctx.eax = static_cast<uint32_t>(t85);
    goto bb_0044041b;
}
bb_00440401: {
    // 0x00440401: xor eax, eax
    uint32_t t86 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t86);
    ctx.eax = static_cast<uint32_t>(t86);
    // 0x00440403: jmp 0x44041b
}
bb_0044041b: {
    // 0x0044041b: mov edx, 0xccccccc
    ctx.edx = static_cast<uint32_t>(0x0cccccccu);
    // 0x00440420: sub edx, eax
    uint32_t t87 = static_cast<uint32_t>(ctx.edx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.eax, t87);
    ctx.edx = static_cast<uint32_t>(t87);
    // 0x00440422: cmp edx, ebx
    uint32_t t88 = static_cast<uint32_t>(ctx.edx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ebx, t88);
    // 0x00440424: jae 0x44042b
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0044042b;
    goto bb_00440426;
}
bb_0044042b: {
    // 0x0044042b: test ecx, ecx
    uint32_t t89 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t89);
    // 0x0044042d: jne 0x440433
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00440433;
    goto bb_0044042f;
}
bb_00440426: {
    // 0x00440426: call 0x437280
    uint32_t t90 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    mem.w32(t90, 0x0044042bu);
    sub_00437280(ctx, mem);
    goto bb_0044042b;
}
bb_00440433: {
    // 0x00440433: mov edx, dword ptr [edi + 8]
    uint32_t t91 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t92 = mem.r32(t91);
    ctx.edx = static_cast<uint32_t>(t92);
    // 0x00440436: sub edx, ecx
    uint32_t t93 = static_cast<uint32_t>(ctx.edx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ecx, t93);
    ctx.edx = static_cast<uint32_t>(t93);
    // 0x00440438: mov eax, 0x66666667
    ctx.eax = static_cast<uint32_t>(0x66666667u);
    // 0x0044043d: imul edx
    uint64_t t94 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.edx)));
    uint32_t t95 = static_cast<uint32_t>(t94);
    uint32_t t96 = static_cast<uint32_t>(t94 >> 32);
    ctx.eax = static_cast<uint32_t>(t95);
    ctx.edx = static_cast<uint32_t>(t96);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t94);
    // 0x0044043f: sar edx, 3
    uint32_t t97 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t98 = recomp_detail::sar<uint32_t>(ctx.edx, t97);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t97, t98);
    ctx.edx = static_cast<uint32_t>(t98);
    // 0x00440442: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x00440444: shr eax, 0x1f
    uint32_t t99 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t100 = recomp_detail::shr<uint32_t>(ctx.eax, t99);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t99, t100);
    ctx.eax = static_cast<uint32_t>(t100);
    // 0x00440447: add eax, edx
    uint32_t t101 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t101);
    ctx.eax = static_cast<uint32_t>(t101);
    goto bb_00440449;
}
bb_0044042f: {
    // 0x0044042f: xor eax, eax
    uint32_t t102 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t102);
    ctx.eax = static_cast<uint32_t>(t102);
    // 0x00440431: jmp 0x440449
}
bb_00440449: {
    // 0x00440449: add eax, ebx
    uint32_t t103 = static_cast<uint32_t>(ctx.eax + ctx.ebx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.ebx, t103);
    ctx.eax = static_cast<uint32_t>(t103);
    // 0x0044044b: cmp esi, eax
    uint32_t t104 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t104);
    // 0x0044044d: jae 0x4405a9
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004405a9;
    goto bb_00440453;
}
bb_004405a9: {
    // 0x004405a9: mov ecx, dword ptr [edi + 8]
    uint32_t t105 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t106 = mem.r32(t105);
    ctx.ecx = static_cast<uint32_t>(t106);
    // 0x004405ac: mov esi, dword ptr [ebp + 0x18]
    uint32_t t107 = static_cast<uint32_t>(ctx.ebp + 0x00000018u);
    uint32_t t108 = mem.r32(t107);
    ctx.esi = static_cast<uint32_t>(t108);
    // 0x004405af: mov edx, ecx
    ctx.edx = static_cast<uint32_t>(ctx.ecx);
    // 0x004405b1: sub edx, esi
    uint32_t t109 = static_cast<uint32_t>(ctx.edx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.esi, t109);
    ctx.edx = static_cast<uint32_t>(t109);
    // 0x004405b3: mov eax, 0x66666667
    ctx.eax = static_cast<uint32_t>(0x66666667u);
    // 0x004405b8: imul edx
    uint64_t t110 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.edx)));
    uint32_t t111 = static_cast<uint32_t>(t110);
    uint32_t t112 = static_cast<uint32_t>(t110 >> 32);
    ctx.eax = static_cast<uint32_t>(t111);
    ctx.edx = static_cast<uint32_t>(t112);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t110);
    // 0x004405ba: sar edx, 3
    uint32_t t113 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t114 = recomp_detail::sar<uint32_t>(ctx.edx, t113);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t113, t114);
    ctx.edx = static_cast<uint32_t>(t114);
    // 0x004405bd: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004405bf: shr eax, 0x1f
    uint32_t t115 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t116 = recomp_detail::shr<uint32_t>(ctx.eax, t115);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t115, t116);
    ctx.eax = static_cast<uint32_t>(t116);
    // 0x004405c2: add eax, edx
    uint32_t t117 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t117);
    ctx.eax = static_cast<uint32_t>(t117);
    // 0x004405c4: cmp eax, ebx
    uint32_t t118 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t118);
    // 0x004405c6: mov dword ptr [ebp + 0x10], ecx
    uint32_t t119 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    mem.w32(t119, ctx.ecx);
    // 0x004405c9: mov edx, ecx
    ctx.edx = static_cast<uint32_t>(ctx.ecx);
    // 0x004405cb: jae 0x44064a
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0044064a;
    goto bb_004405cd;
}
bb_00440453: {
    // 0x00440453: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x00440455: shr eax, 1
    uint32_t t120 = static_cast<uint32_t>(0x00000001u & 0x0000001fu);
    uint32_t t121 = recomp_detail::shr<uint32_t>(ctx.eax, t120);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t120, t121);
    ctx.eax = static_cast<uint32_t>(t121);
    // 0x00440457: mov edx, 0xccccccc
    ctx.edx = static_cast<uint32_t>(0x0cccccccu);
    // 0x0044045c: sub edx, eax
    uint32_t t122 = static_cast<uint32_t>(ctx.edx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.eax, t122);
    ctx.edx = static_cast<uint32_t>(t122);
    // 0x0044045e: cmp edx, esi
    uint32_t t123 = static_cast<uint32_t>(ctx.edx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.esi, t123);
    // 0x00440460: jae 0x44046e
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0044046e;
    goto bb_00440462;
}
bb_0044064a: {
    // 0x0044064a: lea ebx, [ebx + ebx*4]
    uint32_t t124 = recomp_detail::shl<uint32_t>(ctx.ebx, 0x00000002u);
    uint32_t t125 = static_cast<uint32_t>(ctx.ebx + t124);
    ctx.ebx = static_cast<uint32_t>(t125);
    // 0x0044064d: add ebx, ebx
    uint32_t t126 = static_cast<uint32_t>(ctx.ebx + ctx.ebx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebx, ctx.ebx, t126);
    ctx.ebx = static_cast<uint32_t>(t126);
    // 0x0044064f: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x00440651: add ebx, ebx
    uint32_t t127 = static_cast<uint32_t>(ctx.ebx + ctx.ebx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebx, ctx.ebx, t127);
    ctx.ebx = static_cast<uint32_t>(t127);
    // 0x00440653: sub eax, ebx
    uint32_t t128 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t128);
    ctx.eax = static_cast<uint32_t>(t128);
    // 0x00440655: push ecx
    uint32_t t129 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t129);
    mem.w32(t129, ctx.ecx);
    // 0x00440656: push eax
    uint32_t t130 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t130);
    mem.w32(t130, ctx.eax);
    // 0x00440657: mov dword ptr [ebp + 8], eax
    uint32_t t131 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    mem.w32(t131, ctx.eax);
    // 0x0044065a: call 0x440730
    uint32_t t132 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t132);
    mem.w32(t132, 0x0044065fu);
    sub_00440730(ctx, mem);
    // 0x0044065f: mov dword ptr [edi + 8], eax
    uint32_t t133 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    mem.w32(t133, ctx.eax);
    // 0x00440662: mov byte ptr [ebp + 0xc], 0
    uint32_t t134 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    mem.w8(t134, uint8_t{0x00u});
    // 0x00440666: mov eax, dword ptr [ebp + 0xc]
    uint32_t t135 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t136 = mem.r32(t135);
    ctx.eax = static_cast<uint32_t>(t136);
    // 0x00440669: mov ecx, dword ptr [ebp + 0xc]
    uint32_t t137 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t138 = mem.r32(t137);
    ctx.ecx = static_cast<uint32_t>(t138);
    // 0x0044066c: mov edx, dword ptr [ebp + 0xc]
    uint32_t t139 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t140 = mem.r32(t139);
    ctx.edx = static_cast<uint32_t>(t140);
    // 0x0044066f: push eax
    uint32_t t141 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t141);
    mem.w32(t141, ctx.eax);
    // 0x00440670: mov eax, dword ptr [ebp + 0x10]
    uint32_t t142 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    uint32_t t143 = mem.r32(t142);
    ctx.eax = static_cast<uint32_t>(t143);
    // 0x00440673: push ecx
    uint32_t t144 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t144);
    mem.w32(t144, ctx.ecx);
    // 0x00440674: mov ecx, dword ptr [ebp + 8]
    uint32_t t145 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t146 = mem.r32(t145);
    ctx.ecx = static_cast<uint32_t>(t146);
    // 0x00440677: push edx
    uint32_t t147 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t147);
    mem.w32(t147, ctx.edx);
    // 0x00440678: call 0x440820
    uint32_t t148 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t148);
    mem.w32(t148, 0x0044067du);
    sub_00440820(ctx, mem);
    // 0x0044067d: add esp, 0xc
    uint32_t t149 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t149);
    ctx.esp = static_cast<uint32_t>(t149);
    // 0x00440680: lea edx, [ebx + esi]
    uint32_t t150 = static_cast<uint32_t>(ctx.ebx + ctx.esi);
    ctx.edx = static_cast<uint32_t>(t150);
    goto bb_00440683;
}
bb_004405cd: {
    // 0x004405cd: lea eax, [ebx + ebx*4]
    uint32_t t151 = recomp_detail::shl<uint32_t>(ctx.ebx, 0x00000002u);
    uint32_t t152 = static_cast<uint32_t>(ctx.ebx + t151);
    ctx.eax = static_cast<uint32_t>(t152);
    // 0x004405d0: add eax, eax
    uint32_t t153 = static_cast<uint32_t>(ctx.eax + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.eax, t153);
    ctx.eax = static_cast<uint32_t>(t153);
    // 0x004405d2: add eax, eax
    uint32_t t154 = static_cast<uint32_t>(ctx.eax + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.eax, t154);
    ctx.eax = static_cast<uint32_t>(t154);
    // 0x004405d4: mov dword ptr [ebp - 0x14], eax
    uint32_t t155 = static_cast<uint32_t>(ctx.ebp + 0xffffffecu);
    mem.w32(t155, ctx.eax);
    // 0x004405d7: add eax, esi
    uint32_t t156 = static_cast<uint32_t>(ctx.eax + ctx.esi);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.esi, t156);
    ctx.eax = static_cast<uint32_t>(t156);
    // 0x004405d9: push eax
    uint32_t t157 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t157);
    mem.w32(t157, ctx.eax);
    // 0x004405da: push esi
    uint32_t t158 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t158);
    mem.w32(t158, ctx.esi);
    // 0x004405db: call 0x440730
    uint32_t t159 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t159);
    mem.w32(t159, 0x004405e0u);
    sub_00440730(ctx, mem);
    // 0x004405e0: mov byte ptr [ebp - 4], 3
    uint32_t t160 = static_cast<uint32_t>(ctx.ebp + 0xfffffffcu);
    mem.w8(t160, uint8_t{0x03u});
    // 0x004405e4: mov ecx, dword ptr [edi + 8]
    uint32_t t161 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t162 = mem.r32(t161);
    ctx.ecx = static_cast<uint32_t>(t162);
    // 0x004405e7: sub ecx, esi
    uint32_t t163 = static_cast<uint32_t>(ctx.ecx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.esi, t163);
    ctx.ecx = static_cast<uint32_t>(t163);
    // 0x004405e9: mov eax, 0x66666667
    ctx.eax = static_cast<uint32_t>(0x66666667u);
    // 0x004405ee: imul ecx
    uint64_t t164 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t165 = static_cast<uint32_t>(t164);
    uint32_t t166 = static_cast<uint32_t>(t164 >> 32);
    ctx.eax = static_cast<uint32_t>(t165);
    ctx.edx = static_cast<uint32_t>(t166);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t164);
    // 0x004405f0: mov eax, dword ptr [ebp + 0xc]
    uint32_t t167 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t168 = mem.r32(t167);
    ctx.eax = static_cast<uint32_t>(t168);
    // 0x004405f3: sar edx, 3
    uint32_t t169 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t170 = recomp_detail::sar<uint32_t>(ctx.edx, t169);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t169, t170);
    ctx.edx = static_cast<uint32_t>(t170);
    // 0x004405f6: mov ecx, edx
    ctx.ecx = static_cast<uint32_t>(ctx.edx);
    // 0x004405f8: shr ecx, 0x1f
    uint32_t t171 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t172 = recomp_detail::shr<uint32_t>(ctx.ecx, t171);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.ecx, t171, t172);
    ctx.ecx = static_cast<uint32_t>(t172);
    // 0x004405fb: add ecx, edx
    uint32_t t173 = static_cast<uint32_t>(ctx.ecx + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, ctx.edx, t173);
    ctx.ecx = static_cast<uint32_t>(t173);
    // 0x004405fd: mov byte ptr [ebp + 0x10], 0
    uint32_t t174 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    mem.w8(t174, uint8_t{0x00u});
    // 0x00440601: mov edx, dword ptr [ebp + 0x10]
    uint32_t t175 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    uint32_t t176 = mem.r32(t175);
    ctx.edx = static_cast<uint32_t>(t176);
    // 0x00440604: push edx
    uint32_t t177 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t177);
    mem.w32(t177, ctx.edx);
    // 0x00440605: sub ebx, ecx
    uint32_t t178 = static_cast<uint32_t>(ctx.ebx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.ecx, t178);
    ctx.ebx = static_cast<uint32_t>(t178);
    // 0x00440607: push eax
    uint32_t t179 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t179);
    mem.w32(t179, ctx.eax);
    // 0x00440608: mov eax, dword ptr [edi + 8]
    uint32_t t180 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t181 = mem.r32(t180);
    ctx.eax = static_cast<uint32_t>(t181);
    // 0x0044060b: lea edx, [ebp - 0x28]
    uint32_t t182 = static_cast<uint32_t>(ctx.ebp + 0xffffffd8u);
    ctx.edx = static_cast<uint32_t>(t182);
    // 0x0044060e: mov ecx, ebx
    ctx.ecx = static_cast<uint32_t>(ctx.ebx);
    // 0x00440610: call 0x4407e0
    uint32_t t183 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t183);
    mem.w32(t183, 0x00440615u);
    sub_004407e0(ctx, mem);
    // 0x00440615: mov eax, dword ptr [ebp - 0x14]
    uint32_t t184 = static_cast<uint32_t>(ctx.ebp + 0xffffffecu);
    uint32_t t185 = mem.r32(t184);
    ctx.eax = static_cast<uint32_t>(t185);
    // 0x00440618: add dword ptr [edi + 8], eax
    uint32_t t186 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t187 = mem.r32(t186);
    uint32_t t188 = static_cast<uint32_t>(t187 + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, t187, ctx.eax, t188);
    mem.w32(t186, t188);
    // 0x0044061b: mov edx, dword ptr [edi + 8]
    uint32_t t189 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t190 = mem.r32(t189);
    ctx.edx = static_cast<uint32_t>(t190);
    // 0x0044061e: add esp, 8
    uint32_t t191 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t191);
    ctx.esp = static_cast<uint32_t>(t191);
    // 0x00440621: sub edx, eax
    uint32_t t192 = static_cast<uint32_t>(ctx.edx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.eax, t192);
    ctx.edx = static_cast<uint32_t>(t192);
    // 0x00440623: jmp 0x440683
    goto bb_00440683;
}
bb_0044046e: {
    // 0x0044046e: add esi, eax
    uint32_t t193 = static_cast<uint32_t>(ctx.esi + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, ctx.eax, t193);
    ctx.esi = static_cast<uint32_t>(t193);
    // 0x00440470: mov dword ptr [ebp + 0x10], esi
    uint32_t t194 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    mem.w32(t194, ctx.esi);
    goto bb_00440473;
}
bb_00440462: {
    // 0x00440462: mov dword ptr [ebp + 0x10], 0
    uint32_t t195 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    mem.w32(t195, 0x00000000u);
    // 0x00440469: mov esi, dword ptr [ebp + 0x10]
    uint32_t t196 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    uint32_t t197 = mem.r32(t196);
    ctx.esi = static_cast<uint32_t>(t197);
    // 0x0044046c: jmp 0x440473
    goto bb_00440473;
}
bb_00440683: {
    // 0x00440683: lea ecx, [ebp - 0x28]
    uint32_t t198 = static_cast<uint32_t>(ctx.ebp + 0xffffffd8u);
    ctx.ecx = static_cast<uint32_t>(t198);
    // 0x00440686: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x00440688: call 0x440760
    uint32_t t199 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t199);
    mem.w32(t199, 0x0044068du);
    sub_00440760(ctx, mem);
    goto bb_0044068d;
}
bb_00440473: {
    // 0x00440473: test ecx, ecx
    uint32_t t200 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t200);
    // 0x00440475: jne 0x44047b
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0044047b;
    goto bb_00440477;
}
bb_0044047b: {
    // 0x0044047b: mov edx, dword ptr [edi + 8]
    uint32_t t201 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t202 = mem.r32(t201);
    ctx.edx = static_cast<uint32_t>(t202);
    // 0x0044047e: sub edx, ecx
    uint32_t t203 = static_cast<uint32_t>(ctx.edx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ecx, t203);
    ctx.edx = static_cast<uint32_t>(t203);
    // 0x00440480: mov eax, 0x66666667
    ctx.eax = static_cast<uint32_t>(0x66666667u);
    // 0x00440485: imul edx
    uint64_t t204 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.edx)));
    uint32_t t205 = static_cast<uint32_t>(t204);
    uint32_t t206 = static_cast<uint32_t>(t204 >> 32);
    ctx.eax = static_cast<uint32_t>(t205);
    ctx.edx = static_cast<uint32_t>(t206);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t204);
    // 0x00440487: sar edx, 3
    uint32_t t207 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t208 = recomp_detail::sar<uint32_t>(ctx.edx, t207);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t207, t208);
    ctx.edx = static_cast<uint32_t>(t208);
    // 0x0044048a: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x0044048c: shr eax, 0x1f
    uint32_t t209 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t210 = recomp_detail::shr<uint32_t>(ctx.eax, t209);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t209, t210);
    ctx.eax = static_cast<uint32_t>(t210);
    // 0x0044048f: add eax, edx
    uint32_t t211 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t211);
    ctx.eax = static_cast<uint32_t>(t211);
    goto bb_00440491;
}
bb_00440477: {
    // 0x00440477: xor eax, eax
    uint32_t t212 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t212);
    ctx.eax = static_cast<uint32_t>(t212);
    // 0x00440479: jmp 0x440491
}
bb_00440491: {
    // 0x00440491: add eax, ebx
    uint32_t t213 = static_cast<uint32_t>(ctx.eax + ctx.ebx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.ebx, t213);
    ctx.eax = static_cast<uint32_t>(t213);
    // 0x00440493: cmp esi, eax
    uint32_t t214 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t214);
    // 0x00440495: jae 0x4404a5
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004404a5;
    goto bb_00440497;
}
bb_004404a5: {
    // 0x004404a5: test esi, esi
    uint32_t t215 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t215);
    // 0x004404a7: ja 0x4404b8
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_004404b8;
    goto bb_004404a9;
}
bb_00440497: {
    // 0x00440497: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x00440499: call 0x440070
    uint32_t t216 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t216);
    mem.w32(t216, 0x0044049eu);
    sub_00440070(ctx, mem);
    // 0x0044049e: add eax, ebx
    uint32_t t217 = static_cast<uint32_t>(ctx.eax + ctx.ebx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.ebx, t217);
    ctx.eax = static_cast<uint32_t>(t217);
    // 0x004404a0: mov dword ptr [ebp + 0x10], eax
    uint32_t t218 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    mem.w32(t218, ctx.eax);
    // 0x004404a3: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    goto bb_004404a5;
}
bb_004404b8: {
    // 0x004404b8: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004404ba: call 0x4406b0
    uint32_t t219 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t219);
    mem.w32(t219, 0x004404bfu);
    sub_004406b0(ctx, mem);
    // 0x004404bf: mov dword ptr [ebp + 0xc], eax
    uint32_t t220 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    mem.w32(t220, ctx.eax);
    goto bb_004404c2;
}
bb_004404a9: {
    // 0x004404a9: push 0
    uint32_t t221 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t221);
    mem.w32(t221, 0x00000000u);
    // 0x004404ab: call 0x4e0177
    uint32_t t222 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t222);
    mem.w32(t222, 0x004404b0u);
    hle_crt_004e0177(ctx, mem);
    // 0x004404b0: add esp, 4
    uint32_t t223 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t223);
    ctx.esp = static_cast<uint32_t>(t223);
    // 0x004404b3: mov dword ptr [ebp + 0xc], eax
    uint32_t t224 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    mem.w32(t224, ctx.eax);
    // 0x004404b6: jmp 0x4404c2
}
bb_004404c2: {
    // 0x004404c2: mov byte ptr [ebp - 4], 1
    uint32_t t225 = static_cast<uint32_t>(ctx.ebp + 0xfffffffcu);
    mem.w8(t225, uint8_t{0x01u});
    // 0x004404c6: mov ecx, dword ptr [edi + 4]
    uint32_t t226 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    uint32_t t227 = mem.r32(t226);
    ctx.ecx = static_cast<uint32_t>(t227);
    // 0x004404c9: mov byte ptr [ebp - 0x14], 0
    uint32_t t228 = static_cast<uint32_t>(ctx.ebp + 0xffffffecu);
    mem.w8(t228, uint8_t{0x00u});
    // 0x004404cd: mov edx, dword ptr [ebp - 0x14]
    uint32_t t229 = static_cast<uint32_t>(ctx.ebp + 0xffffffecu);
    uint32_t t230 = mem.r32(t229);
    ctx.edx = static_cast<uint32_t>(t230);
    // 0x004404d0: push edx
    uint32_t t231 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t231);
    mem.w32(t231, ctx.edx);
    // 0x004404d1: mov edx, dword ptr [ebp + 0xc]
    uint32_t t232 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t233 = mem.r32(t232);
    ctx.edx = static_cast<uint32_t>(t233);
    // 0x004404d4: push edx
    uint32_t t234 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t234);
    mem.w32(t234, ctx.edx);
    // 0x004404d5: mov edx, dword ptr [ebp + 0x18]
    uint32_t t235 = static_cast<uint32_t>(ctx.ebp + 0x00000018u);
    uint32_t t236 = mem.r32(t235);
    ctx.edx = static_cast<uint32_t>(t236);
    // 0x004404d8: mov dword ptr [ebp + 8], eax
    uint32_t t237 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    mem.w32(t237, ctx.eax);
    // 0x004404db: call 0x440880
    uint32_t t238 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t238);
    mem.w32(t238, 0x004404e0u);
    sub_00440880(ctx, mem);
    // 0x004404e0: mov ecx, dword ptr [ebp + 0xc]
    uint32_t t239 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t240 = mem.r32(t239);
    ctx.ecx = static_cast<uint32_t>(t240);
    // 0x004404e3: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004404e5: add esp, 8
    uint32_t t241 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t241);
    ctx.esp = static_cast<uint32_t>(t241);
    // 0x004404e8: mov byte ptr [ebp - 0x14], 0
    uint32_t t242 = static_cast<uint32_t>(ctx.ebp + 0xffffffecu);
    mem.w8(t242, uint8_t{0x00u});
    // 0x004404ec: mov eax, dword ptr [ebp - 0x14]
    uint32_t t243 = static_cast<uint32_t>(ctx.ebp + 0xffffffecu);
    uint32_t t244 = mem.r32(t243);
    ctx.eax = static_cast<uint32_t>(t244);
    // 0x004404ef: push eax
    uint32_t t245 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t245);
    mem.w32(t245, ctx.eax);
    // 0x004404f0: push ecx
    uint32_t t246 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t246);
    mem.w32(t246, ctx.ecx);
    // 0x004404f1: lea edx, [ebp - 0x28]
    uint32_t t247 = static_cast<uint32_t>(ctx.ebp + 0xffffffd8u);
    ctx.edx = static_cast<uint32_t>(t247);
    // 0x004404f4: mov ecx, ebx
    ctx.ecx = static_cast<uint32_t>(ctx.ebx);
    // 0x004404f6: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004404f8: mov dword ptr [ebp + 8], esi
    uint32_t t248 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    mem.w32(t248, ctx.esi);
    // 0x004404fb: call 0x4407e0
    uint32_t t249 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t249);
    mem.w32(t249, 0x00440500u);
    sub_004407e0(ctx, mem);
    // 0x00440500: add esp, 8
    uint32_t t250 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t250);
    ctx.esp = static_cast<uint32_t>(t250);
    // 0x00440503: mov byte ptr [ebp - 0x14], 0
    uint32_t t251 = static_cast<uint32_t>(ctx.ebp + 0xffffffecu);
    mem.w8(t251, uint8_t{0x00u});
    // 0x00440507: mov ecx, dword ptr [ebp - 0x14]
    uint32_t t252 = static_cast<uint32_t>(ctx.ebp + 0xffffffecu);
    uint32_t t253 = mem.r32(t252);
    ctx.ecx = static_cast<uint32_t>(t253);
    // 0x0044050a: push ecx
    uint32_t t254 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t254);
    mem.w32(t254, ctx.ecx);
    // 0x0044050b: mov ecx, dword ptr [ebp + 0xc]
    uint32_t t255 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t256 = mem.r32(t255);
    ctx.ecx = static_cast<uint32_t>(t256);
    // 0x0044050e: lea edx, [ebx + ebx*4]
    uint32_t t257 = recomp_detail::shl<uint32_t>(ctx.ebx, 0x00000002u);
    uint32_t t258 = static_cast<uint32_t>(ctx.ebx + t257);
    ctx.edx = static_cast<uint32_t>(t258);
    // 0x00440511: lea eax, [esi + edx*4]
    uint32_t t259 = recomp_detail::shl<uint32_t>(ctx.edx, 0x00000002u);
    uint32_t t260 = static_cast<uint32_t>(ctx.esi + t259);
    ctx.eax = static_cast<uint32_t>(t260);
    // 0x00440514: mov edx, dword ptr [edi + 8]
    uint32_t t261 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t262 = mem.r32(t261);
    ctx.edx = static_cast<uint32_t>(t262);
    // 0x00440517: push ecx
    uint32_t t263 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t263);
    mem.w32(t263, ctx.ecx);
    // 0x00440518: mov ecx, dword ptr [ebp + 0x18]
    uint32_t t264 = static_cast<uint32_t>(ctx.ebp + 0x00000018u);
    uint32_t t265 = mem.r32(t264);
    ctx.ecx = static_cast<uint32_t>(t265);
    // 0x0044051b: mov dword ptr [ebp + 8], eax
    uint32_t t266 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    mem.w32(t266, ctx.eax);
    // 0x0044051e: call 0x440880
    uint32_t t267 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t267);
    mem.w32(t267, 0x00440523u);
    sub_00440880(ctx, mem);
    // 0x00440523: mov dword ptr [ebp - 4], 0
    uint32_t t268 = static_cast<uint32_t>(ctx.ebp + 0xfffffffcu);
    mem.w32(t268, 0x00000000u);
    // 0x0044052a: mov ecx, dword ptr [edi + 4]
    uint32_t t269 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    uint32_t t270 = mem.r32(t269);
    ctx.ecx = static_cast<uint32_t>(t270);
    // 0x0044052d: add esp, 8
    uint32_t t271 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t271);
    ctx.esp = static_cast<uint32_t>(t271);
    // 0x00440530: test ecx, ecx
    uint32_t t272 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t272);
    // 0x00440532: jne 0x440538
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00440538;
    goto bb_00440534;
}
bb_00440538: {
    // 0x00440538: mov edx, dword ptr [edi + 8]
    uint32_t t273 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t274 = mem.r32(t273);
    ctx.edx = static_cast<uint32_t>(t274);
    // 0x0044053b: sub edx, ecx
    uint32_t t275 = static_cast<uint32_t>(ctx.edx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ecx, t275);
    ctx.edx = static_cast<uint32_t>(t275);
    // 0x0044053d: mov eax, 0x66666667
    ctx.eax = static_cast<uint32_t>(0x66666667u);
    // 0x00440542: imul edx
    uint64_t t276 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.edx)));
    uint32_t t277 = static_cast<uint32_t>(t276);
    uint32_t t278 = static_cast<uint32_t>(t276 >> 32);
    ctx.eax = static_cast<uint32_t>(t277);
    ctx.edx = static_cast<uint32_t>(t278);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t276);
    // 0x00440544: sar edx, 3
    uint32_t t279 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t280 = recomp_detail::sar<uint32_t>(ctx.edx, t279);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t279, t280);
    ctx.edx = static_cast<uint32_t>(t280);
    // 0x00440547: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x00440549: shr eax, 0x1f
    uint32_t t281 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t282 = recomp_detail::shr<uint32_t>(ctx.eax, t281);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t281, t282);
    ctx.eax = static_cast<uint32_t>(t282);
    // 0x0044054c: add eax, edx
    uint32_t t283 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t283);
    ctx.eax = static_cast<uint32_t>(t283);
    goto bb_0044054e;
}
bb_00440534: {
    // 0x00440534: xor eax, eax
    uint32_t t284 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t284);
    ctx.eax = static_cast<uint32_t>(t284);
    // 0x00440536: jmp 0x44054e
}
bb_0044054e: {
    // 0x0044054e: add ebx, eax
    uint32_t t285 = static_cast<uint32_t>(ctx.ebx + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebx, ctx.eax, t285);
    ctx.ebx = static_cast<uint32_t>(t285);
    // 0x00440550: test ecx, ecx
    uint32_t t286 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t286);
    // 0x00440552: je 0x44056a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0044056a;
    goto bb_00440554;
}
bb_0044056a: {
    // 0x0044056a: mov eax, dword ptr [ebp + 0x10]
    uint32_t t287 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    uint32_t t288 = mem.r32(t287);
    ctx.eax = static_cast<uint32_t>(t288);
    // 0x0044056d: lea edx, [eax + eax*4]
    uint32_t t289 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000002u);
    uint32_t t290 = static_cast<uint32_t>(ctx.eax + t289);
    ctx.edx = static_cast<uint32_t>(t290);
    // 0x00440570: mov eax, dword ptr [ebp + 0xc]
    uint32_t t291 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t292 = mem.r32(t291);
    ctx.eax = static_cast<uint32_t>(t292);
    // 0x00440573: lea ecx, [eax + edx*4]
    uint32_t t293 = recomp_detail::shl<uint32_t>(ctx.edx, 0x00000002u);
    uint32_t t294 = static_cast<uint32_t>(ctx.eax + t293);
    ctx.ecx = static_cast<uint32_t>(t294);
    // 0x00440576: lea edx, [ebx + ebx*4]
    uint32_t t295 = recomp_detail::shl<uint32_t>(ctx.ebx, 0x00000002u);
    uint32_t t296 = static_cast<uint32_t>(ctx.ebx + t295);
    ctx.edx = static_cast<uint32_t>(t296);
    // 0x00440579: mov dword ptr [edi + 0xc], ecx
    uint32_t t297 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    mem.w32(t297, ctx.ecx);
    // 0x0044057c: lea ecx, [eax + edx*4]
    uint32_t t298 = recomp_detail::shl<uint32_t>(ctx.edx, 0x00000002u);
    uint32_t t299 = static_cast<uint32_t>(ctx.eax + t298);
    ctx.ecx = static_cast<uint32_t>(t299);
    // 0x0044057f: mov dword ptr [edi + 8], ecx
    uint32_t t300 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    mem.w32(t300, ctx.ecx);
    // 0x00440582: mov dword ptr [edi + 4], eax
    uint32_t t301 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    mem.w32(t301, ctx.eax);
    // 0x00440585: jmp 0x44068d
    goto bb_0044068d;
}
bb_00440554: {
    // 0x00440554: mov esi, dword ptr [edi + 8]
    uint32_t t302 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t303 = mem.r32(t302);
    ctx.esi = static_cast<uint32_t>(t303);
    // 0x00440557: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x00440559: call 0x440310
    uint32_t t304 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t304);
    mem.w32(t304, 0x0044055eu);
    sub_00440310(ctx, mem);
    // 0x0044055e: mov eax, dword ptr [edi + 4]
    uint32_t t305 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    uint32_t t306 = mem.r32(t305);
    ctx.eax = static_cast<uint32_t>(t306);
    // 0x00440561: push eax
    uint32_t t307 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t307);
    mem.w32(t307, ctx.eax);
    // 0x00440562: call 0x4e02f3
    uint32_t t308 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t308);
    mem.w32(t308, 0x00440567u);
    hle_crt_004e02f3(ctx, mem);
    // 0x00440567: add esp, 4
    uint32_t t309 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t309);
    ctx.esp = static_cast<uint32_t>(t309);
    goto bb_0044056a;
}
}

// sub_004406b0 | subsystem=Replay | canonical | 3 blocks | 24 insns
void sub_004406b0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004406b0: or eax, 0xffffffff
    uint32_t t0 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x004406b3: xor edx, edx
    uint32_t t1 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.edx = static_cast<uint32_t>(t1);
    // 0x004406b5: div ecx
    uint64_t t2 = ((static_cast<uint64_t>(ctx.edx) << 32) | static_cast<uint64_t>(ctx.eax));
    uint32_t t3 = recomp_detail::div64_u(t2, ctx.ecx);
    uint32_t t4 = recomp_detail::mod64_u(t2, ctx.ecx);
    ctx.eax = static_cast<uint32_t>(t3);
    ctx.edx = static_cast<uint32_t>(t4);
    // 0x004406b7: sub esp, 0x10
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000010u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x004406ba: cmp eax, 0x14
    uint32_t t6 = static_cast<uint32_t>(ctx.eax - 0x00000014u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000014u, t6);
    // 0x004406bd: jae 0x4406eb
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004406eb;
    goto bb_004406bf;
}
bb_004406eb: {
    // 0x004406eb: lea edx, [ecx + ecx*4]
    uint32_t t7 = recomp_detail::shl<uint32_t>(ctx.ecx, 0x00000002u);
    uint32_t t8 = static_cast<uint32_t>(ctx.ecx + t7);
    ctx.edx = static_cast<uint32_t>(t8);
    // 0x004406ee: add edx, edx
    uint32_t t9 = static_cast<uint32_t>(ctx.edx + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, ctx.edx, t9);
    ctx.edx = static_cast<uint32_t>(t9);
    // 0x004406f0: add edx, edx
    uint32_t t10 = static_cast<uint32_t>(ctx.edx + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, ctx.edx, t10);
    ctx.edx = static_cast<uint32_t>(t10);
    // 0x004406f2: push edx
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.edx);
    // 0x004406f3: call 0x4e0177
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x004406f8u);
    hle_crt_004e0177(ctx, mem);
    // 0x004406f8: add esp, 4
    uint32_t t13 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t13);
    ctx.esp = static_cast<uint32_t>(t13);
    // 0x004406fb: add esp, 0x10
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t14);
    ctx.esp = static_cast<uint32_t>(t14);
    // 0x004406fe: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004406bf: {
    // 0x004406bf: lea eax, [esp]
    ctx.eax = static_cast<uint32_t>(ctx.esp);
    // 0x004406c2: push eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.eax);
    // 0x004406c3: lea ecx, [esp + 8]
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.ecx = static_cast<uint32_t>(t16);
    // 0x004406c7: mov dword ptr [esp + 4], 0
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    mem.w32(t17, 0x00000000u);
    // 0x004406cf: call 0x4e07d5
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x004406d4u);
    hle_crt_004e07d5(ctx, mem);
    // 0x004406d4: push 0x543b60
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x00543b60u);
    // 0x004406d9: lea ecx, [esp + 8]
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.ecx = static_cast<uint32_t>(t20);
    // 0x004406dd: push ecx
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, ctx.ecx);
    // 0x004406de: mov dword ptr [esp + 0xc], 0x51b5e0
    uint32_t t22 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t22, 0x0051b5e0u);
    // 0x004406e6: call 0x4e3e1b
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x004406ebu);
    hle_crt_004e3e1b(ctx, mem);
    goto bb_004406eb;
}
}

// sub_00440730 | subsystem=Replay | canonical | 1 blocks | 11 insns
void sub_00440730(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00440730: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x00440731: mov ecx, dword ptr [esp + 0xc]
    uint32_t t1 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t2 = mem.r32(t1);
    ctx.ecx = static_cast<uint32_t>(t2);
    // 0x00440735: mov byte ptr [esp], 0
    mem.w8(ctx.esp, uint8_t{0x00u});
    // 0x00440739: mov eax, dword ptr [esp]
    uint32_t t3 = mem.r32(ctx.esp);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0044073c: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0044073d: mov eax, dword ptr [esp + 0x10]
    uint32_t t5 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t6 = mem.r32(t5);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x00440741: push ecx
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.ecx);
    // 0x00440742: mov ecx, dword ptr [esp + 0x10]
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t9 = mem.r32(t8);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x00440746: call 0x440880
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x0044074bu);
    sub_00440880(ctx, mem);
    // 0x0044074b: add esp, 0xc
    uint32_t t11 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t11);
    ctx.esp = static_cast<uint32_t>(t11);
    // 0x0044074e: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
}

// sub_00440760 | subsystem=Replay | canonical | 5 blocks | 18 insns
void sub_00440760(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00440760: cmp eax, edx
    uint32_t t0 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t0);
    // 0x00440762: je 0x440789
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00440789;
    goto bb_00440764;
}
bb_00440789: {
    // 0x00440789: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00440764: {
    // 0x00440764: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
}
bb_00440765: {
    // 0x00440765: mov esi, dword ptr [ecx]
    uint32_t t2 = mem.r32(ctx.ecx);
    ctx.esi = static_cast<uint32_t>(t2);
    // 0x00440767: mov dword ptr [eax], esi
    mem.w32(ctx.eax, ctx.esi);
    // 0x00440769: mov esi, dword ptr [ecx + 4]
    uint32_t t3 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    uint32_t t4 = mem.r32(t3);
    ctx.esi = static_cast<uint32_t>(t4);
    // 0x0044076c: mov dword ptr [eax + 4], esi
    uint32_t t5 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w32(t5, ctx.esi);
    // 0x0044076f: mov esi, dword ptr [ecx + 8]
    uint32_t t6 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t7 = mem.r32(t6);
    ctx.esi = static_cast<uint32_t>(t7);
    // 0x00440772: mov dword ptr [eax + 8], esi
    uint32_t t8 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    mem.w32(t8, ctx.esi);
    // 0x00440775: mov esi, dword ptr [ecx + 0xc]
    uint32_t t9 = static_cast<uint32_t>(ctx.ecx + 0x0000000cu);
    uint32_t t10 = mem.r32(t9);
    ctx.esi = static_cast<uint32_t>(t10);
    // 0x00440778: mov dword ptr [eax + 0xc], esi
    uint32_t t11 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    mem.w32(t11, ctx.esi);
    // 0x0044077b: mov esi, dword ptr [ecx + 0x10]
    uint32_t t12 = static_cast<uint32_t>(ctx.ecx + 0x00000010u);
    uint32_t t13 = mem.r32(t12);
    ctx.esi = static_cast<uint32_t>(t13);
    // 0x0044077e: mov dword ptr [eax + 0x10], esi
    uint32_t t14 = static_cast<uint32_t>(ctx.eax + 0x00000010u);
    mem.w32(t14, ctx.esi);
    // 0x00440781: add eax, 0x14
    uint32_t t15 = static_cast<uint32_t>(ctx.eax + 0x00000014u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000014u, t15);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x00440784: cmp eax, edx
    uint32_t t16 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t16);
    // 0x00440786: jne 0x440765
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00440765;
}
{
    // 0x00440788: pop esi
    uint32_t t17 = ctx.esp;
    uint32_t t18 = mem.r32(t17);
    uint32_t t19 = static_cast<uint32_t>(t17 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    ctx.esi = static_cast<uint32_t>(t18);
    goto bb_00440789;
}
}

// sub_00440790 | subsystem=Replay | canonical | 4 blocks | 31 insns
void sub_00440790(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00440790: push edi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.edi);
    // 0x00440791: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x00440793: mov edx, esi
    ctx.edx = static_cast<uint32_t>(ctx.esi);
    // 0x00440795: sub edx, ecx
    uint32_t t1 = static_cast<uint32_t>(ctx.edx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ecx, t1);
    ctx.edx = static_cast<uint32_t>(t1);
    // 0x00440797: mov eax, 0x66666667
    ctx.eax = static_cast<uint32_t>(0x66666667u);
    // 0x0044079c: imul edx
    uint64_t t2 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.edx)));
    uint32_t t3 = static_cast<uint32_t>(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 >> 32);
    ctx.eax = static_cast<uint32_t>(t3);
    ctx.edx = static_cast<uint32_t>(t4);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t2);
    // 0x0044079e: sar edx, 3
    uint32_t t5 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t6 = recomp_detail::sar<uint32_t>(ctx.edx, t5);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t5, t6);
    ctx.edx = static_cast<uint32_t>(t6);
    // 0x004407a1: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004407a3: shr eax, 0x1f
    uint32_t t7 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t8 = recomp_detail::shr<uint32_t>(ctx.eax, t7);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t7, t8);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x004407a6: add eax, edx
    uint32_t t9 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t9);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x004407a8: cmp ecx, esi
    uint32_t t10 = static_cast<uint32_t>(ctx.ecx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.esi, t10);
    // 0x004407aa: lea eax, [eax + eax*4]
    uint32_t t11 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000002u);
    uint32_t t12 = static_cast<uint32_t>(ctx.eax + t11);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x004407ad: lea eax, [edi + eax*4]
    uint32_t t13 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000002u);
    uint32_t t14 = static_cast<uint32_t>(ctx.edi + t13);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x004407b0: je 0x4407de
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004407de;
    goto bb_004407b2;
}
bb_004407de: {
    // 0x004407de: pop edi
    uint32_t t15 = ctx.esp;
    uint32_t t16 = mem.r32(t15);
    uint32_t t17 = static_cast<uint32_t>(t15 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    ctx.edi = static_cast<uint32_t>(t16);
    // 0x004407df: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004407b2: {
    // 0x004407b2: mov edx, edi
    ctx.edx = static_cast<uint32_t>(ctx.edi);
    // 0x004407b4: sub edx, ecx
    uint32_t t18 = static_cast<uint32_t>(ctx.edx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ecx, t18);
    ctx.edx = static_cast<uint32_t>(t18);
}
bb_004407b6: {
    // 0x004407b6: mov edi, dword ptr [ecx]
    uint32_t t19 = mem.r32(ctx.ecx);
    ctx.edi = static_cast<uint32_t>(t19);
    // 0x004407b8: mov dword ptr [edx + ecx], edi
    uint32_t t20 = static_cast<uint32_t>(ctx.edx + ctx.ecx);
    mem.w32(t20, ctx.edi);
    // 0x004407bb: mov edi, dword ptr [ecx + 4]
    uint32_t t21 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    uint32_t t22 = mem.r32(t21);
    ctx.edi = static_cast<uint32_t>(t22);
    // 0x004407be: mov dword ptr [edx + ecx + 4], edi
    uint32_t t23 = static_cast<uint32_t>(ctx.edx + ctx.ecx);
    uint32_t t24 = static_cast<uint32_t>(t23 + 0x00000004u);
    mem.w32(t24, ctx.edi);
    // 0x004407c2: mov edi, dword ptr [ecx + 8]
    uint32_t t25 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t26 = mem.r32(t25);
    ctx.edi = static_cast<uint32_t>(t26);
    // 0x004407c5: mov dword ptr [edx + ecx + 8], edi
    uint32_t t27 = static_cast<uint32_t>(ctx.edx + ctx.ecx);
    uint32_t t28 = static_cast<uint32_t>(t27 + 0x00000008u);
    mem.w32(t28, ctx.edi);
    // 0x004407c9: mov edi, dword ptr [ecx + 0xc]
    uint32_t t29 = static_cast<uint32_t>(ctx.ecx + 0x0000000cu);
    uint32_t t30 = mem.r32(t29);
    ctx.edi = static_cast<uint32_t>(t30);
    // 0x004407cc: mov dword ptr [edx + ecx + 0xc], edi
    uint32_t t31 = static_cast<uint32_t>(ctx.edx + ctx.ecx);
    uint32_t t32 = static_cast<uint32_t>(t31 + 0x0000000cu);
    mem.w32(t32, ctx.edi);
    // 0x004407d0: mov edi, dword ptr [ecx + 0x10]
    uint32_t t33 = static_cast<uint32_t>(ctx.ecx + 0x00000010u);
    uint32_t t34 = mem.r32(t33);
    ctx.edi = static_cast<uint32_t>(t34);
    // 0x004407d3: mov dword ptr [edx + ecx + 0x10], edi
    uint32_t t35 = static_cast<uint32_t>(ctx.edx + ctx.ecx);
    uint32_t t36 = static_cast<uint32_t>(t35 + 0x00000010u);
    mem.w32(t36, ctx.edi);
    // 0x004407d7: add ecx, 0x14
    uint32_t t37 = static_cast<uint32_t>(ctx.ecx + 0x00000014u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000014u, t37);
    ctx.ecx = static_cast<uint32_t>(t37);
    // 0x004407da: cmp ecx, esi
    uint32_t t38 = static_cast<uint32_t>(ctx.ecx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.esi, t38);
    // 0x004407dc: jne 0x4407b6
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004407b6;
    goto bb_004407de;
}
}

// sub_004407e0 | subsystem=Replay | canonical | 7 blocks | 21 insns
void sub_004407e0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004407e0: test ecx, ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    // 0x004407e2: jbe 0x440810
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_00440810;
    goto bb_004407e4;
}
bb_00440810: {
    // 0x00440810: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004407e4: {
    // 0x004407e4: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
}
bb_004407e5: {
    // 0x004407e5: test eax, eax
    uint32_t t2 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    // 0x004407e7: je 0x440805
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00440805;
    goto bb_004407e9;
}
bb_00440805: {
    // 0x00440805: sub ecx, 1
    uint32_t t3 = static_cast<uint32_t>(ctx.ecx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000001u, t3);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x00440808: add eax, 0x14
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000014u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000014u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0044080b: test ecx, ecx
    uint32_t t5 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    // 0x0044080d: ja 0x4407e5
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_004407e5;
    goto bb_0044080f;
}
bb_004407e9: {
    // 0x004407e9: mov esi, dword ptr [edx]
    uint32_t t6 = mem.r32(ctx.edx);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x004407eb: mov dword ptr [eax], esi
    mem.w32(ctx.eax, ctx.esi);
    // 0x004407ed: mov esi, dword ptr [edx + 4]
    uint32_t t7 = static_cast<uint32_t>(ctx.edx + 0x00000004u);
    uint32_t t8 = mem.r32(t7);
    ctx.esi = static_cast<uint32_t>(t8);
    // 0x004407f0: mov dword ptr [eax + 4], esi
    uint32_t t9 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w32(t9, ctx.esi);
    // 0x004407f3: mov esi, dword ptr [edx + 8]
    uint32_t t10 = static_cast<uint32_t>(ctx.edx + 0x00000008u);
    uint32_t t11 = mem.r32(t10);
    ctx.esi = static_cast<uint32_t>(t11);
    // 0x004407f6: mov dword ptr [eax + 8], esi
    uint32_t t12 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    mem.w32(t12, ctx.esi);
    // 0x004407f9: mov esi, dword ptr [edx + 0xc]
    uint32_t t13 = static_cast<uint32_t>(ctx.edx + 0x0000000cu);
    uint32_t t14 = mem.r32(t13);
    ctx.esi = static_cast<uint32_t>(t14);
    // 0x004407fc: mov dword ptr [eax + 0xc], esi
    uint32_t t15 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    mem.w32(t15, ctx.esi);
    // 0x004407ff: mov esi, dword ptr [edx + 0x10]
    uint32_t t16 = static_cast<uint32_t>(ctx.edx + 0x00000010u);
    uint32_t t17 = mem.r32(t16);
    ctx.esi = static_cast<uint32_t>(t17);
    // 0x00440802: mov dword ptr [eax + 0x10], esi
    uint32_t t18 = static_cast<uint32_t>(ctx.eax + 0x00000010u);
    mem.w32(t18, ctx.esi);
    goto bb_00440805;
}
bb_0044080f: {
    // 0x0044080f: pop esi
    uint32_t t19 = ctx.esp;
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t19 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    ctx.esi = static_cast<uint32_t>(t20);
    goto bb_00440810;
}
}

// sub_00440820 | subsystem=Replay | canonical | 4 blocks | 36 insns
void sub_00440820(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00440820: push edi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.edi);
    // 0x00440821: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x00440823: mov edx, ecx
    ctx.edx = static_cast<uint32_t>(ctx.ecx);
    // 0x00440825: sub edx, esi
    uint32_t t1 = static_cast<uint32_t>(ctx.edx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.esi, t1);
    ctx.edx = static_cast<uint32_t>(t1);
    // 0x00440827: mov eax, 0x66666667
    ctx.eax = static_cast<uint32_t>(0x66666667u);
    // 0x0044082c: imul edx
    uint64_t t2 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.edx)));
    uint32_t t3 = static_cast<uint32_t>(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 >> 32);
    ctx.eax = static_cast<uint32_t>(t3);
    ctx.edx = static_cast<uint32_t>(t4);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t2);
    // 0x0044082e: sar edx, 3
    uint32_t t5 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x03u}) & 0x0000001fu);
    uint32_t t6 = recomp_detail::sar<uint32_t>(ctx.edx, t5);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t5, t6);
    ctx.edx = static_cast<uint32_t>(t6);
    // 0x00440831: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x00440833: shr eax, 0x1f
    uint32_t t7 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t8 = recomp_detail::shr<uint32_t>(ctx.eax, t7);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t7, t8);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x00440836: add eax, edx
    uint32_t t9 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t9);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x00440838: lea eax, [eax + eax*4]
    uint32_t t10 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000002u);
    uint32_t t11 = static_cast<uint32_t>(ctx.eax + t10);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x0044083b: add eax, eax
    uint32_t t12 = static_cast<uint32_t>(ctx.eax + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.eax, t12);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0044083d: add eax, eax
    uint32_t t13 = static_cast<uint32_t>(ctx.eax + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.eax, t13);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0044083f: mov edx, eax
    ctx.edx = static_cast<uint32_t>(ctx.eax);
    // 0x00440841: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x00440843: sub eax, edx
    uint32_t t14 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t14);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x00440845: cmp esi, ecx
    uint32_t t15 = static_cast<uint32_t>(ctx.esi - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ecx, t15);
    // 0x00440847: je 0x440879
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00440879;
    goto bb_00440849;
}
bb_00440879: {
    // 0x00440879: pop edi
    uint32_t t16 = ctx.esp;
    uint32_t t17 = mem.r32(t16);
    uint32_t t18 = static_cast<uint32_t>(t16 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    ctx.edi = static_cast<uint32_t>(t17);
    // 0x0044087a: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00440849: {
    // 0x00440849: mov edx, edi
    ctx.edx = static_cast<uint32_t>(ctx.edi);
    // 0x0044084b: sub edx, ecx
    uint32_t t19 = static_cast<uint32_t>(ctx.edx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ecx, t19);
    ctx.edx = static_cast<uint32_t>(t19);
    // 0x0044084d: lea ecx, [ecx]
    ctx.ecx = static_cast<uint32_t>(ctx.ecx);
}
bb_00440850: {
    // 0x00440850: mov edi, dword ptr [ecx - 0x14]
    uint32_t t20 = static_cast<uint32_t>(ctx.ecx + 0xffffffecu);
    uint32_t t21 = mem.r32(t20);
    ctx.edi = static_cast<uint32_t>(t21);
    // 0x00440853: sub ecx, 0x14
    uint32_t t22 = static_cast<uint32_t>(ctx.ecx - 0x00000014u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000014u, t22);
    ctx.ecx = static_cast<uint32_t>(t22);
    // 0x00440856: cmp ecx, esi
    uint32_t t23 = static_cast<uint32_t>(ctx.ecx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.esi, t23);
    // 0x00440858: mov dword ptr [edx + ecx], edi
    uint32_t t24 = static_cast<uint32_t>(ctx.edx + ctx.ecx);
    mem.w32(t24, ctx.edi);
    // 0x0044085b: mov edi, dword ptr [ecx + 4]
    uint32_t t25 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    uint32_t t26 = mem.r32(t25);
    ctx.edi = static_cast<uint32_t>(t26);
    // 0x0044085e: mov dword ptr [edx + ecx + 4], edi
    uint32_t t27 = static_cast<uint32_t>(ctx.edx + ctx.ecx);
    uint32_t t28 = static_cast<uint32_t>(t27 + 0x00000004u);
    mem.w32(t28, ctx.edi);
    // 0x00440862: mov edi, dword ptr [ecx + 8]
    uint32_t t29 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t30 = mem.r32(t29);
    ctx.edi = static_cast<uint32_t>(t30);
    // 0x00440865: mov dword ptr [edx + ecx + 8], edi
    uint32_t t31 = static_cast<uint32_t>(ctx.edx + ctx.ecx);
    uint32_t t32 = static_cast<uint32_t>(t31 + 0x00000008u);
    mem.w32(t32, ctx.edi);
    // 0x00440869: mov edi, dword ptr [ecx + 0xc]
    uint32_t t33 = static_cast<uint32_t>(ctx.ecx + 0x0000000cu);
    uint32_t t34 = mem.r32(t33);
    ctx.edi = static_cast<uint32_t>(t34);
    // 0x0044086c: mov dword ptr [edx + ecx + 0xc], edi
    uint32_t t35 = static_cast<uint32_t>(ctx.edx + ctx.ecx);
    uint32_t t36 = static_cast<uint32_t>(t35 + 0x0000000cu);
    mem.w32(t36, ctx.edi);
    // 0x00440870: mov edi, dword ptr [ecx + 0x10]
    uint32_t t37 = static_cast<uint32_t>(ctx.ecx + 0x00000010u);
    uint32_t t38 = mem.r32(t37);
    ctx.edi = static_cast<uint32_t>(t38);
    // 0x00440873: mov dword ptr [edx + ecx + 0x10], edi
    uint32_t t39 = static_cast<uint32_t>(ctx.edx + ctx.ecx);
    uint32_t t40 = static_cast<uint32_t>(t39 + 0x00000010u);
    mem.w32(t40, ctx.edi);
    // 0x00440877: jne 0x440850
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00440850;
    goto bb_00440879;
}
}

// sub_00440880 | subsystem=Replay | canonical | 7 blocks | 21 insns
void sub_00440880(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00440880: cmp ecx, edx
    uint32_t t0 = static_cast<uint32_t>(ctx.ecx - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.edx, t0);
    // 0x00440882: je 0x4408b0
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004408b0;
    goto bb_00440884;
}
bb_004408b0: {
    // 0x004408b0: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00440884: {
    // 0x00440884: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
}
bb_00440885: {
    // 0x00440885: test eax, eax
    uint32_t t2 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    // 0x00440887: je 0x4408a5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004408a5;
    goto bb_00440889;
}
bb_004408a5: {
    // 0x004408a5: add ecx, 0x14
    uint32_t t3 = static_cast<uint32_t>(ctx.ecx + 0x00000014u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000014u, t3);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x004408a8: add eax, 0x14
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000014u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000014u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x004408ab: cmp ecx, edx
    uint32_t t5 = static_cast<uint32_t>(ctx.ecx - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.edx, t5);
    // 0x004408ad: jne 0x440885
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00440885;
    goto bb_004408af;
}
bb_00440889: {
    // 0x00440889: mov esi, dword ptr [ecx]
    uint32_t t6 = mem.r32(ctx.ecx);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x0044088b: mov dword ptr [eax], esi
    mem.w32(ctx.eax, ctx.esi);
    // 0x0044088d: mov esi, dword ptr [ecx + 4]
    uint32_t t7 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    uint32_t t8 = mem.r32(t7);
    ctx.esi = static_cast<uint32_t>(t8);
    // 0x00440890: mov dword ptr [eax + 4], esi
    uint32_t t9 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w32(t9, ctx.esi);
    // 0x00440893: mov esi, dword ptr [ecx + 8]
    uint32_t t10 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t11 = mem.r32(t10);
    ctx.esi = static_cast<uint32_t>(t11);
    // 0x00440896: mov dword ptr [eax + 8], esi
    uint32_t t12 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    mem.w32(t12, ctx.esi);
    // 0x00440899: mov esi, dword ptr [ecx + 0xc]
    uint32_t t13 = static_cast<uint32_t>(ctx.ecx + 0x0000000cu);
    uint32_t t14 = mem.r32(t13);
    ctx.esi = static_cast<uint32_t>(t14);
    // 0x0044089c: mov dword ptr [eax + 0xc], esi
    uint32_t t15 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    mem.w32(t15, ctx.esi);
    // 0x0044089f: mov esi, dword ptr [ecx + 0x10]
    uint32_t t16 = static_cast<uint32_t>(ctx.ecx + 0x00000010u);
    uint32_t t17 = mem.r32(t16);
    ctx.esi = static_cast<uint32_t>(t17);
    // 0x004408a2: mov dword ptr [eax + 0x10], esi
    uint32_t t18 = static_cast<uint32_t>(ctx.eax + 0x00000010u);
    mem.w32(t18, ctx.esi);
    goto bb_004408a5;
}
bb_004408af: {
    // 0x004408af: pop esi
    uint32_t t19 = ctx.esp;
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t19 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    ctx.esi = static_cast<uint32_t>(t20);
    goto bb_004408b0;
}
}

// sub_00445430 | subsystem=Replay | canonical | 12 blocks | 63 insns
void sub_00445430(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00445430: push ebx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebx);
    // 0x00445431: push ebp
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebp);
    // 0x00445432: mov ebp, dword ptr [esp + 0xc]
    uint32_t t2 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t3 = mem.r32(t2);
    ctx.ebp = static_cast<uint32_t>(t3);
    // 0x00445436: push edi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.edi);
    // 0x00445437: mov edi, 0x10
    ctx.edi = static_cast<uint32_t>(0x00000010u);
    // 0x0044543c: push ebp
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ebp);
    // 0x0044543d: mov ebx, edi
    ctx.ebx = static_cast<uint32_t>(ctx.edi);
    // 0x0044543f: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x00445441: call 0x413e70
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x00445446u);
    sub_00413e70(ctx, mem);
    // 0x00445446: test eax, eax
    uint32_t t7 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    // 0x00445448: je 0x44545c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0044545c;
    goto bb_0044544a;
}
bb_0044545c: {
    // 0x0044545c: lea eax, [ebp + 0x10]
    uint32_t t8 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x0044545f: mov edi, 4
    ctx.edi = static_cast<uint32_t>(0x00000004u);
    // 0x00445464: push eax
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.eax);
    // 0x00445465: mov ebx, edi
    ctx.ebx = static_cast<uint32_t>(ctx.edi);
    // 0x00445467: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x00445469: call 0x413e70
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x0044546eu);
    sub_00413e70(ctx, mem);
    // 0x0044546e: test eax, eax
    uint32_t t11 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    // 0x00445470: je 0x445484
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00445484;
    goto bb_00445472;
}
bb_0044544a: {
    // 0x0044544a: mov eax, dword ptr [esi + 0x3c]
    uint32_t t12 = static_cast<uint32_t>(ctx.esi + 0x0000003cu);
    uint32_t t13 = mem.r32(t12);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0044544d: test eax, eax
    uint32_t t14 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    // 0x0044544f: je 0x44545c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0044545c;
    goto bb_00445451;
}
bb_00445484: {
    // 0x00445484: lea ecx, [ebp + 0x14]
    uint32_t t15 = static_cast<uint32_t>(ctx.ebp + 0x00000014u);
    ctx.ecx = static_cast<uint32_t>(t15);
    // 0x00445487: push ecx
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, ctx.ecx);
    // 0x00445488: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0044548a: call 0x413e70
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x0044548fu);
    sub_00413e70(ctx, mem);
    // 0x0044548f: test eax, eax
    uint32_t t18 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    // 0x00445491: je 0x4454a5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004454a5;
    goto bb_00445493;
}
bb_00445472: {
    // 0x00445472: mov eax, dword ptr [esi + 0x3c]
    uint32_t t19 = static_cast<uint32_t>(ctx.esi + 0x0000003cu);
    uint32_t t20 = mem.r32(t19);
    ctx.eax = static_cast<uint32_t>(t20);
    // 0x00445475: test eax, eax
    uint32_t t21 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t21);
    // 0x00445477: je 0x445484
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00445484;
    goto bb_00445479;
}
bb_00445451: {
    // 0x00445451: push 0
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x00000000u);
    // 0x00445453: push -1
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0xffffffffu);
    // 0x00445455: push eax
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, ctx.eax);
    // 0x00445456: call dword ptr [0x51b1c4]
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x0044545cu);
    hle_iat_call(ctx, mem, 0x0051b1c4u);
    goto bb_0044545c;
}
bb_004454a5: {
    // 0x004454a5: lea edx, [ebp + 0x18]
    uint32_t t26 = static_cast<uint32_t>(ctx.ebp + 0x00000018u);
    ctx.edx = static_cast<uint32_t>(t26);
    // 0x004454a8: push edx
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, ctx.edx);
    // 0x004454a9: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004454ab: call 0x444f90
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x004454b0u);
    sub_00444f90(ctx, mem);
    // 0x004454b0: lea edi, [ebp + 0x3c]
    uint32_t t29 = static_cast<uint32_t>(ctx.ebp + 0x0000003cu);
    ctx.edi = static_cast<uint32_t>(t29);
    // 0x004454b3: mov ebx, 2
    ctx.ebx = static_cast<uint32_t>(0x00000002u);
    goto bb_004454b8;
}
bb_00445493: {
    // 0x00445493: mov eax, dword ptr [esi + 0x3c]
    uint32_t t30 = static_cast<uint32_t>(ctx.esi + 0x0000003cu);
    uint32_t t31 = mem.r32(t30);
    ctx.eax = static_cast<uint32_t>(t31);
    // 0x00445496: test eax, eax
    uint32_t t32 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t32);
    // 0x00445498: je 0x4454a5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004454a5;
    goto bb_0044549a;
}
bb_00445479: {
    // 0x00445479: push 0
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x00000000u);
    // 0x0044547b: push -1
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0xffffffffu);
    // 0x0044547d: push eax
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, ctx.eax);
    // 0x0044547e: call dword ptr [0x51b1c4]
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, 0x00445484u);
    hle_iat_call(ctx, mem, 0x0051b1c4u);
    goto bb_00445484;
}
bb_004454b8: {
    // 0x004454b8: push edi
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, ctx.edi);
    // 0x004454b9: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004454bb: call 0x4452f0
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, 0x004454c0u);
    sub_004452f0(ctx, mem);
    // 0x004454c0: add edi, 0x10
    uint32_t t39 = static_cast<uint32_t>(ctx.edi + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000010u, t39);
    ctx.edi = static_cast<uint32_t>(t39);
    // 0x004454c3: sub ebx, 1
    uint32_t t40 = static_cast<uint32_t>(ctx.ebx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, 0x00000001u, t40);
    ctx.ebx = static_cast<uint32_t>(t40);
    // 0x004454c6: jne 0x4454b8
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004454b8;
    goto bb_004454c8;
}
bb_0044549a: {
    // 0x0044549a: push 0
    uint32_t t41 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    mem.w32(t41, 0x00000000u);
    // 0x0044549c: push -1
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, 0xffffffffu);
    // 0x0044549e: push eax
    uint32_t t43 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    mem.w32(t43, ctx.eax);
    // 0x0044549f: call dword ptr [0x51b1c4]
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, 0x004454a5u);
    hle_iat_call(ctx, mem, 0x0051b1c4u);
    goto bb_004454a5;
}
bb_004454c8: {
    // 0x004454c8: pop edi
    uint32_t t45 = ctx.esp;
    uint32_t t46 = mem.r32(t45);
    uint32_t t47 = static_cast<uint32_t>(t45 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    ctx.edi = static_cast<uint32_t>(t46);
    // 0x004454c9: pop ebp
    uint32_t t48 = ctx.esp;
    uint32_t t49 = mem.r32(t48);
    uint32_t t50 = static_cast<uint32_t>(t48 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    ctx.ebp = static_cast<uint32_t>(t49);
    // 0x004454ca: lea eax, [ebx + 1]
    uint32_t t51 = static_cast<uint32_t>(ctx.ebx + 0x00000001u);
    ctx.eax = static_cast<uint32_t>(t51);
    // 0x004454cd: pop ebx
    uint32_t t52 = ctx.esp;
    uint32_t t53 = mem.r32(t52);
    uint32_t t54 = static_cast<uint32_t>(t52 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    ctx.ebx = static_cast<uint32_t>(t53);
    // 0x004454ce: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
}

// sub_00445580 | subsystem=Replay | canonical | 7 blocks | 69 insns
void sub_00445580(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00445580: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x00445581: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x00445583: and esp, 0xfffffff8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xfffffff8u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x00445586: push -1
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0xffffffffu);
    // 0x00445588: push 0x516918
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x00516918u);
    // 0x0044558d: mov eax, dword ptr fs:[0]
    uint32_t t4 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t5 = mem.r32(t4);
    ctx.eax = static_cast<uint32_t>(t5);
    // 0x00445593: push eax
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.eax);
    // 0x00445594: sub esp, 0x64
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000064u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000064u, t7);
    ctx.esp = static_cast<uint32_t>(t7);
    // 0x00445597: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x00445598: push edi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.edi);
    // 0x00445599: mov eax, dword ptr [0x54b458]
    uint32_t t10 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0044559e: xor eax, esp
    uint32_t t11 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x004455a0: push eax
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.eax);
    // 0x004455a1: lea eax, [esp + 0x70]
    uint32_t t13 = static_cast<uint32_t>(ctx.esp + 0x00000070u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x004455a5: mov dword ptr fs:[0], eax
    uint32_t t14 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t14, ctx.eax);
    // 0x004455ab: mov edi, ecx
    ctx.edi = static_cast<uint32_t>(ctx.ecx);
    // 0x004455ad: lea esi, [esp + 0xc]
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    ctx.esi = static_cast<uint32_t>(t15);
    // 0x004455b1: call 0x413c60
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x004455b6u);
    sub_00413c60(ctx, mem);
    // 0x004455b6: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004455b8: mov dword ptr [esp + 0x78], 0
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    mem.w32(t17, 0x00000000u);
    // 0x004455c0: call 0x414000
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x004455c5u);
    sub_00414000(ctx, mem);
    // 0x004455c5: push edi
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, ctx.edi);
    // 0x004455c6: mov esi, 0x76e9c4
    ctx.esi = static_cast<uint32_t>(0x0076e9c4u);
    // 0x004455cb: call 0x4db8e0
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x004455d0u);
    sub_004db8e0(ctx, mem);
    // 0x004455d0: test eax, eax
    uint32_t t21 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t21);
    // 0x004455d2: je 0x4455ea
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004455ea;
    goto bb_004455d4;
}
bb_004455ea: {
    // 0x004455ea: push 0
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x00000000u);
    // 0x004455ec: push 0x10000080
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x10000080u);
    // 0x004455f1: push 3
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x00000003u);
    // 0x004455f3: push 0
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x00000000u);
    // 0x004455f5: push 1
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x00000001u);
    // 0x004455f7: push 0x80000000
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x80000000u);
    // 0x004455fc: push edi
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, ctx.edi);
    // 0x004455fd: call dword ptr [0x51b054]
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x00445603u);
    hle_iat_call(ctx, mem, 0x0051b054u);
    // 0x00445603: cmp eax, -1
    uint32_t t30 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t30);
    // 0x00445606: jne 0x44560c
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0044560c;
    goto bb_00445608;
}
bb_004455d4: {
    // 0x004455d4: mov dword ptr [esp + 0xc], 0
    uint32_t t31 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t31, 0x00000000u);
    // 0x004455dc: mov dword ptr [esp + 0x28], 3
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t32, 0x00000003u);
    // 0x004455e4: mov dword ptr [esp + 0x64], eax
    uint32_t t33 = static_cast<uint32_t>(ctx.esp + 0x00000064u);
    mem.w32(t33, ctx.eax);
    // 0x004455e8: jmp 0x445618
    goto bb_00445618;
}
bb_0044560c: {
    // 0x0044560c: mov dword ptr [esp + 0xc], eax
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t34, ctx.eax);
    // 0x00445610: mov dword ptr [esp + 0x28], 0
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t35, 0x00000000u);
    goto bb_00445618;
}
bb_00445608: {
    // 0x00445608: xor edi, edi
    uint32_t t36 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t36);
    ctx.edi = static_cast<uint32_t>(t36);
    // 0x0044560a: jmp 0x44563e
    goto bb_0044563e;
}
bb_00445618: {
    // 0x00445618: xor eax, eax
    uint32_t t37 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t37);
    ctx.eax = static_cast<uint32_t>(t37);
    // 0x0044561a: mov dword ptr [esp + 0x14], eax
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t38, ctx.eax);
    // 0x0044561e: mov dword ptr [esp + 0x18], eax
    uint32_t t39 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t39, ctx.eax);
    // 0x00445622: mov dword ptr [esp + 0x1c], eax
    uint32_t t40 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t40, ctx.eax);
    // 0x00445626: mov dword ptr [esp + 0x20], eax
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t41, ctx.eax);
    // 0x0044562a: mov dword ptr [esp + 0x24], eax
    uint32_t t42 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t42, ctx.eax);
    // 0x0044562e: lea edi, [eax + 1]
    uint32_t t43 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.edi = static_cast<uint32_t>(t43);
    // 0x00445631: mov eax, dword ptr [ebp + 8]
    uint32_t t44 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t45 = mem.r32(t44);
    ctx.eax = static_cast<uint32_t>(t45);
    // 0x00445634: push eax
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, ctx.eax);
    // 0x00445635: lea esi, [esp + 0x10]
    uint32_t t47 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    ctx.esi = static_cast<uint32_t>(t47);
    // 0x00445639: call 0x445430
    uint32_t t48 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    mem.w32(t48, 0x0044563eu);
    sub_00445430(ctx, mem);
}
bb_0044563e: {
    // 0x0044563e: lea ecx, [esp + 0xc]
    uint32_t t49 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    ctx.ecx = static_cast<uint32_t>(t49);
    // 0x00445642: call 0x414000
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, 0x00445647u);
    sub_00414000(ctx, mem);
    // 0x00445647: lea ecx, [esp + 0xc]
    uint32_t t51 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    ctx.ecx = static_cast<uint32_t>(t51);
    // 0x0044564b: mov dword ptr [esp + 0x78], 0xffffffff
    uint32_t t52 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    mem.w32(t52, 0xffffffffu);
    // 0x00445653: call 0x414000
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, 0x00445658u);
    sub_00414000(ctx, mem);
    // 0x00445658: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x0044565a: mov ecx, dword ptr [esp + 0x70]
    uint32_t t54 = static_cast<uint32_t>(ctx.esp + 0x00000070u);
    uint32_t t55 = mem.r32(t54);
    ctx.ecx = static_cast<uint32_t>(t55);
    // 0x0044565e: mov dword ptr fs:[0], ecx
    uint32_t t56 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t56, ctx.ecx);
    // 0x00445665: pop ecx
    uint32_t t57 = ctx.esp;
    uint32_t t58 = mem.r32(t57);
    uint32_t t59 = static_cast<uint32_t>(t57 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    ctx.ecx = static_cast<uint32_t>(t58);
    // 0x00445666: pop edi
    uint32_t t60 = ctx.esp;
    uint32_t t61 = mem.r32(t60);
    uint32_t t62 = static_cast<uint32_t>(t60 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    ctx.edi = static_cast<uint32_t>(t61);
    // 0x00445667: pop esi
    uint32_t t63 = ctx.esp;
    uint32_t t64 = mem.r32(t63);
    uint32_t t65 = static_cast<uint32_t>(t63 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t65);
    ctx.esi = static_cast<uint32_t>(t64);
    // 0x00445668: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0044566a: pop ebp
    uint32_t t66 = ctx.esp;
    uint32_t t67 = mem.r32(t66);
    uint32_t t68 = static_cast<uint32_t>(t66 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    ctx.ebp = static_cast<uint32_t>(t67);
    // 0x0044566b: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
}

// sub_00445f30 | subsystem=Replay | canonical | 9 blocks | 60 insns
void sub_00445f30(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00445f30: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x00445f32: push 0x515074
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00515074u);
    // 0x00445f37: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x00445f3d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x00445f3e: push ebx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ebx);
    // 0x00445f3f: push ebp
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebp);
    // 0x00445f40: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x00445f41: push edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edi);
    // 0x00445f42: mov eax, dword ptr [0x54b458]
    uint32_t t9 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x00445f47: xor eax, esp
    uint32_t t10 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x00445f49: push eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.eax);
    // 0x00445f4a: lea eax, [esp + 0x14]
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x00445f4e: mov dword ptr fs:[0], eax
    uint32_t t13 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t13, ctx.eax);
    // 0x00445f54: mov esi, dword ptr [esp + 0x24]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t15 = mem.r32(t14);
    ctx.esi = static_cast<uint32_t>(t15);
    // 0x00445f58: lea eax, [esi + 4]
    uint32_t t16 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x00445f5b: mov dword ptr [esi], 0x5371d0
    mem.w32(ctx.esi, 0x005371d0u);
    // 0x00445f61: call 0x43c4b0
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x00445f66u);
    sub_0043c4b0(ctx, mem);
    // 0x00445f66: xor ebx, ebx
    uint32_t t18 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    ctx.ebx = static_cast<uint32_t>(t18);
    // 0x00445f68: mov dword ptr [esi + 0x64], ebx
    uint32_t t19 = static_cast<uint32_t>(ctx.esi + 0x00000064u);
    mem.w32(t19, ctx.ebx);
    // 0x00445f6b: mov dword ptr [esi + 0x68], ebx
    uint32_t t20 = static_cast<uint32_t>(ctx.esi + 0x00000068u);
    mem.w32(t20, ctx.ebx);
    // 0x00445f6e: mov dword ptr [esi + 0x6c], ebx
    uint32_t t21 = static_cast<uint32_t>(ctx.esi + 0x0000006cu);
    mem.w32(t21, ctx.ebx);
    // 0x00445f71: lea edi, [esi + 0x78]
    uint32_t t22 = static_cast<uint32_t>(ctx.esi + 0x00000078u);
    ctx.edi = static_cast<uint32_t>(t22);
    // 0x00445f74: mov dword ptr [esp + 0x1c], ebx
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t23, ctx.ebx);
    // 0x00445f78: mov eax, 0xf
    ctx.eax = static_cast<uint32_t>(0x0000000fu);
    // 0x00445f7d: mov dword ptr [edi + 0x18], eax
    uint32_t t24 = static_cast<uint32_t>(ctx.edi + 0x00000018u);
    mem.w32(t24, ctx.eax);
    // 0x00445f80: mov dword ptr [edi + 0x14], ebx
    uint32_t t25 = static_cast<uint32_t>(ctx.edi + 0x00000014u);
    mem.w32(t25, ctx.ebx);
    // 0x00445f83: mov byte ptr [edi + 4], bl
    uint32_t t26 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    mem.w8(t26, recomp_detail::r8l(ctx.ebx));
    // 0x00445f86: mov dword ptr [esi + 0xac], eax
    uint32_t t27 = static_cast<uint32_t>(ctx.esi + 0x000000acu);
    mem.w32(t27, ctx.eax);
    // 0x00445f8c: mov dword ptr [esi + 0xa8], ebx
    uint32_t t28 = static_cast<uint32_t>(ctx.esi + 0x000000a8u);
    mem.w32(t28, ctx.ebx);
    // 0x00445f92: mov byte ptr [esi + 0x98], bl
    uint32_t t29 = static_cast<uint32_t>(ctx.esi + 0x00000098u);
    mem.w8(t29, recomp_detail::r8l(ctx.ebx));
    // 0x00445f98: mov byte ptr [esp + 0x1c], 2
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w8(t30, uint8_t{0x02u});
    // 0x00445f9d: mov dword ptr [esi + 0x74], ebx
    uint32_t t31 = static_cast<uint32_t>(ctx.esi + 0x00000074u);
    mem.w32(t31, ctx.ebx);
    // 0x00445fa0: mov ebp, dword ptr [edi + 0x14]
    uint32_t t32 = static_cast<uint32_t>(ctx.edi + 0x00000014u);
    uint32_t t33 = mem.r32(t32);
    ctx.ebp = static_cast<uint32_t>(t33);
    // 0x00445fa3: cmp ebp, 0x100
    uint32_t t34 = static_cast<uint32_t>(ctx.ebp - 0x00000100u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebp, 0x00000100u, t34);
    // 0x00445fa9: ja 0x445fd8
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_00445fd8;
    goto bb_00445fab;
}
bb_00445fd8: {
    // 0x00445fd8: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x00445fda: mov ecx, dword ptr [esp + 0x14]
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t36 = mem.r32(t35);
    ctx.ecx = static_cast<uint32_t>(t36);
    // 0x00445fde: mov dword ptr fs:[0], ecx
    uint32_t t37 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t37, ctx.ecx);
    // 0x00445fe5: pop ecx
    uint32_t t38 = ctx.esp;
    uint32_t t39 = mem.r32(t38);
    uint32_t t40 = static_cast<uint32_t>(t38 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    ctx.ecx = static_cast<uint32_t>(t39);
    // 0x00445fe6: pop edi
    uint32_t t41 = ctx.esp;
    uint32_t t42 = mem.r32(t41);
    uint32_t t43 = static_cast<uint32_t>(t41 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    ctx.edi = static_cast<uint32_t>(t42);
    // 0x00445fe7: pop esi
    uint32_t t44 = ctx.esp;
    uint32_t t45 = mem.r32(t44);
    uint32_t t46 = static_cast<uint32_t>(t44 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    ctx.esi = static_cast<uint32_t>(t45);
    // 0x00445fe8: pop ebp
    uint32_t t47 = ctx.esp;
    uint32_t t48 = mem.r32(t47);
    uint32_t t49 = static_cast<uint32_t>(t47 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    ctx.ebp = static_cast<uint32_t>(t48);
    // 0x00445fe9: pop ebx
    uint32_t t50 = ctx.esp;
    uint32_t t51 = mem.r32(t50);
    uint32_t t52 = static_cast<uint32_t>(t50 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    ctx.ebx = static_cast<uint32_t>(t51);
    // 0x00445fea: add esp, 0xc
    uint32_t t53 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t53);
    ctx.esp = static_cast<uint32_t>(t53);
    // 0x00445fed: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_00445fab: {
    // 0x00445fab: mov eax, dword ptr [edi + 0x18]
    uint32_t t54 = static_cast<uint32_t>(ctx.edi + 0x00000018u);
    uint32_t t55 = mem.r32(t54);
    ctx.eax = static_cast<uint32_t>(t55);
    // 0x00445fae: cmp eax, 0x100
    uint32_t t56 = static_cast<uint32_t>(ctx.eax - 0x00000100u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000100u, t56);
    // 0x00445fb3: je 0x445fd8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00445fd8;
}
{
    // 0x00445fb5: jae 0x445fc4
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_00445fc4;
    goto bb_00445fb7;
}
bb_00445fc4: {
    // 0x00445fc4: cmp dword ptr [edi + 0x18], 0x10
    uint32_t t57 = static_cast<uint32_t>(ctx.edi + 0x00000018u);
    uint32_t t58 = mem.r32(t57);
    uint32_t t59 = static_cast<uint32_t>(t58 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t58, 0x00000010u, t59);
    // 0x00445fc8: mov dword ptr [edi + 0x14], ebp
    uint32_t t60 = static_cast<uint32_t>(ctx.edi + 0x00000014u);
    mem.w32(t60, ctx.ebp);
    // 0x00445fcb: jb 0x445fd2
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_00445fd2;
    goto bb_00445fcd;
}
bb_00445fb7: {
    // 0x00445fb7: push ebp
    uint32_t t61 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    mem.w32(t61, ctx.ebp);
    // 0x00445fb8: push 0x100
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, 0x00000100u);
    // 0x00445fbd: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x00445fbf: call 0x408030
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, 0x00445fc4u);
    sub_00408030(ctx, mem);
    goto bb_00445fc4;
}
bb_00445fd2: {
    // 0x00445fd2: add edi, 4
    uint32_t t64 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000004u, t64);
    ctx.edi = static_cast<uint32_t>(t64);
    goto bb_00445fd5;
}
bb_00445fcd: {
    // 0x00445fcd: mov edi, dword ptr [edi + 4]
    uint32_t t65 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    uint32_t t66 = mem.r32(t65);
    ctx.edi = static_cast<uint32_t>(t66);
    // 0x00445fd0: jmp 0x445fd5
}
bb_00445fd5: {
    // 0x00445fd5: mov byte ptr [edi + ebp], bl
    uint32_t t67 = static_cast<uint32_t>(ctx.edi + ctx.ebp);
    mem.w8(t67, recomp_detail::r8l(ctx.ebx));
    goto bb_00445fd8;
}
}

// sub_00445ff0 | subsystem=Replay | canonical | 3 blocks | 11 insns
void sub_00445ff0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00445ff0: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x00445ff1: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x00445ff3: call 0x446010
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00445ff8u);
    sub_00446010(ctx, mem);
    // 0x00445ff8: test byte ptr [esp + 8], 1
    uint32_t t2 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint8_t t3 = mem.r8(t2);
    uint8_t t4 = static_cast<uint8_t>(static_cast<uint32_t>(t3) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t4);
    // 0x00445ffd: je 0x446008
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00446008;
    goto bb_00445fff;
}
bb_00446008: {
    // 0x00446008: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0044600a: pop esi
    uint32_t t5 = ctx.esp;
    uint32_t t6 = mem.r32(t5);
    uint32_t t7 = static_cast<uint32_t>(t5 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x0044600b: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_00445fff: {
    // 0x00445fff: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x00446000: call 0x4e02f3
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x00446005u);
    hle_crt_004e02f3(ctx, mem);
    // 0x00446005: add esp, 4
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t10);
    ctx.esp = static_cast<uint32_t>(t10);
    goto bb_00446008;
}
}

// sub_00446010 | subsystem=Replay | canonical | 5 blocks | 28 insns
void sub_00446010(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00446010: push ebx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebx);
    // 0x00446011: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
    // 0x00446012: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x00446014: mov dword ptr [esi], 0x5371d0
    mem.w32(ctx.esi, 0x005371d0u);
    // 0x0044601a: cmp dword ptr [esi + 0xac], 0x10
    uint32_t t2 = static_cast<uint32_t>(ctx.esi + 0x000000acu);
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t3 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t3, 0x00000010u, t4);
    // 0x00446021: jb 0x446032
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_00446032;
    goto bb_00446023;
}
bb_00446032: {
    // 0x00446032: xor ebx, ebx
    uint32_t t5 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    ctx.ebx = static_cast<uint32_t>(t5);
    // 0x00446034: mov dword ptr [esi + 0xac], 0xf
    uint32_t t6 = static_cast<uint32_t>(ctx.esi + 0x000000acu);
    mem.w32(t6, 0x0000000fu);
    // 0x0044603e: mov dword ptr [esi + 0xa8], ebx
    uint32_t t7 = static_cast<uint32_t>(ctx.esi + 0x000000a8u);
    mem.w32(t7, ctx.ebx);
    // 0x00446044: mov byte ptr [esi + 0x98], bl
    uint32_t t8 = static_cast<uint32_t>(ctx.esi + 0x00000098u);
    mem.w8(t8, recomp_detail::r8l(ctx.ebx));
    // 0x0044604a: cmp dword ptr [esi + 0x90], 0x10
    uint32_t t9 = static_cast<uint32_t>(ctx.esi + 0x00000090u);
    uint32_t t10 = mem.r32(t9);
    uint32_t t11 = static_cast<uint32_t>(t10 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t10, 0x00000010u, t11);
    // 0x00446051: jb 0x44605f
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0044605f;
    goto bb_00446053;
}
bb_00446023: {
    // 0x00446023: mov eax, dword ptr [esi + 0x98]
    uint32_t t12 = static_cast<uint32_t>(ctx.esi + 0x00000098u);
    uint32_t t13 = mem.r32(t12);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x00446029: push eax
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, ctx.eax);
    // 0x0044602a: call 0x4e02f3
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x0044602fu);
    hle_crt_004e02f3(ctx, mem);
    // 0x0044602f: add esp, 4
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t16);
    ctx.esp = static_cast<uint32_t>(t16);
    goto bb_00446032;
}
bb_0044605f: {
    // 0x0044605f: mov dword ptr [esi + 0x8c], ebx
    uint32_t t17 = static_cast<uint32_t>(ctx.esi + 0x0000008cu);
    mem.w32(t17, ctx.ebx);
    // 0x00446065: mov dword ptr [esi + 0x90], 0xf
    uint32_t t18 = static_cast<uint32_t>(ctx.esi + 0x00000090u);
    mem.w32(t18, 0x0000000fu);
    // 0x0044606f: mov byte ptr [esi + 0x7c], bl
    uint32_t t19 = static_cast<uint32_t>(ctx.esi + 0x0000007cu);
    mem.w8(t19, recomp_detail::r8l(ctx.ebx));
    // 0x00446072: lea ebx, [esi + 0x60]
    uint32_t t20 = static_cast<uint32_t>(ctx.esi + 0x00000060u);
    ctx.ebx = static_cast<uint32_t>(t20);
    // 0x00446075: call 0x447380
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x0044607au);
    sub_00447380(ctx, mem);
    // 0x0044607a: pop esi
    uint32_t t22 = ctx.esp;
    uint32_t t23 = mem.r32(t22);
    uint32_t t24 = static_cast<uint32_t>(t22 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    ctx.esi = static_cast<uint32_t>(t23);
    // 0x0044607b: pop ebx
    uint32_t t25 = ctx.esp;
    uint32_t t26 = mem.r32(t25);
    uint32_t t27 = static_cast<uint32_t>(t25 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    ctx.ebx = static_cast<uint32_t>(t26);
    // 0x0044607c: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00446053: {
    // 0x00446053: mov ecx, dword ptr [esi + 0x7c]
    uint32_t t28 = static_cast<uint32_t>(ctx.esi + 0x0000007cu);
    uint32_t t29 = mem.r32(t28);
    ctx.ecx = static_cast<uint32_t>(t29);
    // 0x00446056: push ecx
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, ctx.ecx);
    // 0x00446057: call 0x4e02f3
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x0044605cu);
    hle_crt_004e02f3(ctx, mem);
    // 0x0044605c: add esp, 4
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t32);
    ctx.esp = static_cast<uint32_t>(t32);
    goto bb_0044605f;
}
}

// sub_00446820 | subsystem=Replay | canonical | 13 blocks | 107 insns
void sub_00446820(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00446820: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x00446821: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x00446823: and esp, 0xfffffff8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xfffffff8u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x00446826: push -1
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0xffffffffu);
    // 0x00446828: push 0x5168db
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x005168dbu);
    // 0x0044682d: mov eax, dword ptr fs:[0]
    uint32_t t4 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t5 = mem.r32(t4);
    ctx.eax = static_cast<uint32_t>(t5);
    // 0x00446833: push eax
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.eax);
    // 0x00446834: sub esp, 0x88
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000088u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000088u, t7);
    ctx.esp = static_cast<uint32_t>(t7);
    // 0x0044683a: mov eax, dword ptr [0x54b458]
    uint32_t t8 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x0044683f: xor eax, esp
    uint32_t t9 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x00446841: mov dword ptr [esp + 0x80], eax
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x00000080u);
    mem.w32(t10, ctx.eax);
    // 0x00446848: push ebx
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.ebx);
    // 0x00446849: push esi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.esi);
    // 0x0044684a: push edi
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, ctx.edi);
    // 0x0044684b: mov eax, dword ptr [0x54b458]
    uint32_t t14 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x00446850: xor eax, esp
    uint32_t t15 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t15);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x00446852: push eax
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, ctx.eax);
    // 0x00446853: lea eax, [esp + 0x98]
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000098u);
    ctx.eax = static_cast<uint32_t>(t17);
    // 0x0044685a: mov dword ptr fs:[0], eax
    uint32_t t18 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t18, ctx.eax);
    // 0x00446860: lea esi, [esp + 0x1c]
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.esi = static_cast<uint32_t>(t19);
    // 0x00446864: mov edi, ecx
    ctx.edi = static_cast<uint32_t>(ctx.ecx);
    // 0x00446866: mov dword ptr [esp + 0x14], 1
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t20, 0x00000001u);
    // 0x0044686e: call 0x413c60
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x00446873u);
    sub_00413c60(ctx, mem);
    // 0x00446873: xor esi, esi
    uint32_t t22 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t22);
    ctx.esi = static_cast<uint32_t>(t22);
    // 0x00446875: lea ecx, [esp + 0x1c]
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.ecx = static_cast<uint32_t>(t23);
    // 0x00446879: mov dword ptr [esp + 0xa0], esi
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x000000a0u);
    mem.w32(t24, ctx.esi);
    // 0x00446880: call 0x414000
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x00446885u);
    sub_00414000(ctx, mem);
    // 0x00446885: push esi
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, ctx.esi);
    // 0x00446886: push 0x10000080
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x10000080u);
    // 0x0044688b: push 3
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x00000003u);
    // 0x0044688d: push esi
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, ctx.esi);
    // 0x0044688e: push 1
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x00000001u);
    // 0x00446890: push 0x80000000
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x80000000u);
    // 0x00446895: push edi
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, ctx.edi);
    // 0x00446896: call dword ptr [0x51b054]
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x0044689cu);
    hle_iat_call(ctx, mem, 0x0051b054u);
    // 0x0044689c: cmp eax, -1
    uint32_t t34 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t34);
    // 0x0044689f: je 0x44690e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0044690e;
    goto bb_004468a1;
}
bb_0044690e: {
    // 0x0044690e: mov dword ptr [esp + 0x14], 0xffffffff
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t35, 0xffffffffu);
    // 0x00446916: jmp 0x44695a
    goto bb_0044695a;
}
bb_004468a1: {
    // 0x004468a1: mov dword ptr [esp + 0x1c], eax
    uint32_t t36 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t36, ctx.eax);
    // 0x004468a5: xor eax, eax
    uint32_t t37 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t37);
    ctx.eax = static_cast<uint32_t>(t37);
    // 0x004468a7: mov dword ptr [esp + 0x24], eax
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t38, ctx.eax);
    // 0x004468ab: mov dword ptr [esp + 0x28], eax
    uint32_t t39 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t39, ctx.eax);
    // 0x004468af: mov dword ptr [esp + 0x2c], eax
    uint32_t t40 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    mem.w32(t40, ctx.eax);
    // 0x004468b3: mov dword ptr [esp + 0x30], eax
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    mem.w32(t41, ctx.eax);
    // 0x004468b7: mov dword ptr [esp + 0x34], eax
    uint32_t t42 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    mem.w32(t42, ctx.eax);
    // 0x004468bb: lea eax, [esp + 0x80]
    uint32_t t43 = static_cast<uint32_t>(ctx.esp + 0x00000080u);
    ctx.eax = static_cast<uint32_t>(t43);
    // 0x004468c2: mov edi, 0x10
    ctx.edi = static_cast<uint32_t>(0x00000010u);
    // 0x004468c7: push eax
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, ctx.eax);
    // 0x004468c8: mov ebx, edi
    ctx.ebx = static_cast<uint32_t>(ctx.edi);
    // 0x004468ca: lea eax, [esp + 0x20]
    uint32_t t45 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    ctx.eax = static_cast<uint32_t>(t45);
    // 0x004468ce: mov dword ptr [esp + 0x3c], esi
    uint32_t t46 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    mem.w32(t46, ctx.esi);
    // 0x004468d2: call 0x413e70
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, 0x004468d7u);
    sub_00413e70(ctx, mem);
    // 0x004468d7: cmp eax, esi
    uint32_t t48 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t48);
    // 0x004468d9: je 0x4468ed
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004468ed;
    goto bb_004468db;
}
bb_0044695a: {
    // 0x0044695a: lea ecx, [esp + 0x1c]
    uint32_t t49 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.ecx = static_cast<uint32_t>(t49);
    // 0x0044695e: call 0x414000
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, 0x00446963u);
    sub_00414000(ctx, mem);
    // 0x00446963: lea ecx, [esp + 0x1c]
    uint32_t t51 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.ecx = static_cast<uint32_t>(t51);
    // 0x00446967: mov dword ptr [esp + 0xa0], 0xffffffff
    uint32_t t52 = static_cast<uint32_t>(ctx.esp + 0x000000a0u);
    mem.w32(t52, 0xffffffffu);
    // 0x00446972: call 0x414000
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, 0x00446977u);
    sub_00414000(ctx, mem);
    // 0x00446977: mov eax, dword ptr [esp + 0x14]
    uint32_t t54 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t55 = mem.r32(t54);
    ctx.eax = static_cast<uint32_t>(t55);
    // 0x0044697b: mov ecx, dword ptr [esp + 0x98]
    uint32_t t56 = static_cast<uint32_t>(ctx.esp + 0x00000098u);
    uint32_t t57 = mem.r32(t56);
    ctx.ecx = static_cast<uint32_t>(t57);
    // 0x00446982: mov dword ptr fs:[0], ecx
    uint32_t t58 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t58, ctx.ecx);
    // 0x00446989: pop ecx
    uint32_t t59 = ctx.esp;
    uint32_t t60 = mem.r32(t59);
    uint32_t t61 = static_cast<uint32_t>(t59 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    ctx.ecx = static_cast<uint32_t>(t60);
    // 0x0044698a: pop edi
    uint32_t t62 = ctx.esp;
    uint32_t t63 = mem.r32(t62);
    uint32_t t64 = static_cast<uint32_t>(t62 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    ctx.edi = static_cast<uint32_t>(t63);
    // 0x0044698b: pop esi
    uint32_t t65 = ctx.esp;
    uint32_t t66 = mem.r32(t65);
    uint32_t t67 = static_cast<uint32_t>(t65 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t67);
    ctx.esi = static_cast<uint32_t>(t66);
    // 0x0044698c: pop ebx
    uint32_t t68 = ctx.esp;
    uint32_t t69 = mem.r32(t68);
    uint32_t t70 = static_cast<uint32_t>(t68 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    ctx.ebx = static_cast<uint32_t>(t69);
    // 0x0044698d: mov ecx, dword ptr [esp + 0x80]
    uint32_t t71 = static_cast<uint32_t>(ctx.esp + 0x00000080u);
    uint32_t t72 = mem.r32(t71);
    ctx.ecx = static_cast<uint32_t>(t72);
    // 0x00446994: xor ecx, esp
    uint32_t t73 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t73);
    ctx.ecx = static_cast<uint32_t>(t73);
    // 0x00446996: call 0x4e02f8
    uint32_t t74 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    mem.w32(t74, 0x0044699bu);
    hle_crt_004e02f8(ctx, mem);
    // 0x0044699b: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0044699d: pop ebp
    uint32_t t75 = ctx.esp;
    uint32_t t76 = mem.r32(t75);
    uint32_t t77 = static_cast<uint32_t>(t75 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    ctx.ebp = static_cast<uint32_t>(t76);
    // 0x0044699e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004468ed: {
    // 0x004468ed: mov edi, 0x536aa8
    ctx.edi = static_cast<uint32_t>(0x00536aa8u);
    // 0x004468f2: lea esi, [esp + 0x80]
    uint32_t t78 = static_cast<uint32_t>(ctx.esp + 0x00000080u);
    ctx.esi = static_cast<uint32_t>(t78);
    // 0x004468f9: mov ecx, 0xf
    ctx.ecx = static_cast<uint32_t>(0x0000000fu);
    // 0x004468fe: xor edx, edx
    uint32_t t79 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t79);
    ctx.edx = static_cast<uint32_t>(t79);
    // 0x00446900: repe cmpsb byte ptr [esi], byte ptr es:[edi]
    recomp_detail::exec_string_op<uint8_t>(ctx, mem, 2, 2);
    // 0x00446902: je 0x446918
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00446918;
    goto bb_00446904;
}
bb_004468db: {
    // 0x004468db: mov eax, dword ptr [esp + 0x58]
    uint32_t t80 = static_cast<uint32_t>(ctx.esp + 0x00000058u);
    uint32_t t81 = mem.r32(t80);
    ctx.eax = static_cast<uint32_t>(t81);
    // 0x004468df: cmp eax, esi
    uint32_t t82 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t82);
    // 0x004468e1: je 0x4468ed
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004468ed;
    goto bb_004468e3;
}
bb_00446918: {
    // 0x00446918: lea eax, [esp + 0x18]
    uint32_t t83 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.eax = static_cast<uint32_t>(t83);
    // 0x0044691c: mov edi, 4
    ctx.edi = static_cast<uint32_t>(0x00000004u);
    // 0x00446921: push eax
    uint32_t t84 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    mem.w32(t84, ctx.eax);
    // 0x00446922: mov ebx, edi
    ctx.ebx = static_cast<uint32_t>(ctx.edi);
    // 0x00446924: lea eax, [esp + 0x20]
    uint32_t t85 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    ctx.eax = static_cast<uint32_t>(t85);
    // 0x00446928: mov dword ptr [esp + 0x1c], edx
    uint32_t t86 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t86, ctx.edx);
    // 0x0044692c: call 0x413e70
    uint32_t t87 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t87);
    mem.w32(t87, 0x00446931u);
    sub_00413e70(ctx, mem);
    // 0x00446931: test eax, eax
    uint32_t t88 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t88);
    // 0x00446933: je 0x446948
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00446948;
    goto bb_00446935;
}
bb_00446904: {
    // 0x00446904: mov dword ptr [esp + 0x14], 0xfffffffe
    uint32_t t89 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t89, 0xfffffffeu);
    // 0x0044690c: jmp 0x44695a
    goto bb_0044695a;
}
bb_004468e3: {
    // 0x004468e3: push esi
    uint32_t t90 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    mem.w32(t90, ctx.esi);
    // 0x004468e4: push -1
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, 0xffffffffu);
    // 0x004468e6: push eax
    uint32_t t92 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    mem.w32(t92, ctx.eax);
    // 0x004468e7: call dword ptr [0x51b1c4]
    uint32_t t93 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    mem.w32(t93, 0x004468edu);
    hle_iat_call(ctx, mem, 0x0051b1c4u);
    goto bb_004468ed;
}
bb_00446948: {
    // 0x00446948: cmp dword ptr [esp + 0x18], 0xc0000004
    uint32_t t94 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t95 = mem.r32(t94);
    uint32_t t96 = static_cast<uint32_t>(t95 - 0xc0000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t95, 0xc0000004u, t96);
    // 0x00446950: je 0x44695a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0044695a;
    goto bb_00446952;
}
bb_00446935: {
    // 0x00446935: mov eax, dword ptr [esp + 0x58]
    uint32_t t97 = static_cast<uint32_t>(ctx.esp + 0x00000058u);
    uint32_t t98 = mem.r32(t97);
    ctx.eax = static_cast<uint32_t>(t98);
    // 0x00446939: test eax, eax
    uint32_t t99 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t99);
    // 0x0044693b: je 0x446948
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00446948;
    goto bb_0044693d;
}
bb_00446952: {
    // 0x00446952: mov dword ptr [esp + 0x14], 0xfffffffd
    uint32_t t100 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t100, 0xfffffffdu);
    goto bb_0044695a;
}
bb_0044693d: {
    // 0x0044693d: push 0
    uint32_t t101 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t101);
    mem.w32(t101, 0x00000000u);
    // 0x0044693f: push -1
    uint32_t t102 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    mem.w32(t102, 0xffffffffu);
    // 0x00446941: push eax
    uint32_t t103 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    mem.w32(t103, ctx.eax);
    // 0x00446942: call dword ptr [0x51b1c4]
    uint32_t t104 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t104);
    mem.w32(t104, 0x00446948u);
    hle_iat_call(ctx, mem, 0x0051b1c4u);
    goto bb_00446948;
}
}

// sub_00447380 | subsystem=Replay | canonical | 5 blocks | 22 insns
void sub_00447380(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00447380: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x00447381: mov esi, dword ptr [ebx + 4]
    uint32_t t1 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    uint32_t t2 = mem.r32(t1);
    ctx.esi = static_cast<uint32_t>(t2);
    // 0x00447384: test esi, esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t3);
    // 0x00447386: je 0x4473ac
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004473ac;
    goto bb_00447388;
}
bb_004473ac: {
    // 0x004473ac: mov dword ptr [ebx + 4], 0
    uint32_t t4 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    mem.w32(t4, 0x00000000u);
    // 0x004473b3: mov dword ptr [ebx + 8], 0
    uint32_t t5 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    mem.w32(t5, 0x00000000u);
    // 0x004473ba: mov dword ptr [ebx + 0xc], 0
    uint32_t t6 = static_cast<uint32_t>(ctx.ebx + 0x0000000cu);
    mem.w32(t6, 0x00000000u);
    // 0x004473c1: pop esi
    uint32_t t7 = ctx.esp;
    uint32_t t8 = mem.r32(t7);
    uint32_t t9 = static_cast<uint32_t>(t7 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    ctx.esi = static_cast<uint32_t>(t8);
    // 0x004473c2: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00447388: {
    // 0x00447388: push edi
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.edi);
    // 0x00447389: mov edi, dword ptr [ebx + 8]
    uint32_t t11 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t12 = mem.r32(t11);
    ctx.edi = static_cast<uint32_t>(t12);
    // 0x0044738c: cmp esi, edi
    uint32_t t13 = static_cast<uint32_t>(ctx.esi - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edi, t13);
    // 0x0044738e: je 0x44739f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0044739f;
    goto bb_00447390;
}
bb_0044739f: {
    // 0x0044739f: mov eax, dword ptr [ebx + 4]
    uint32_t t14 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    uint32_t t15 = mem.r32(t14);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x004473a2: push eax
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, ctx.eax);
    // 0x004473a3: call 0x4e02f3
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x004473a8u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004473a8: add esp, 4
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t18);
    ctx.esp = static_cast<uint32_t>(t18);
    // 0x004473ab: pop edi
    uint32_t t19 = ctx.esp;
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t19 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    ctx.edi = static_cast<uint32_t>(t20);
    goto bb_004473ac;
}
bb_00447390: {
    // 0x00447390: call 0x440b70
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x00447395u);
    sub_00440b70(ctx, mem);
    // 0x00447395: add esi, 0x140
    uint32_t t23 = static_cast<uint32_t>(ctx.esi + 0x00000140u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000140u, t23);
    ctx.esi = static_cast<uint32_t>(t23);
    // 0x0044739b: cmp esi, edi
    uint32_t t24 = static_cast<uint32_t>(ctx.esi - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edi, t24);
    // 0x0044739d: jne 0x447390
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00447390;
    goto bb_0044739f;
}
}

} // namespace mbaa_recomp

#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
