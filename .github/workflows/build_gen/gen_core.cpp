// Auto-generated C++20 shard: gen_core.cpp (152 functions) — DO NOT EDIT

#include "recomp_funcs.h"

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

namespace mbaa_recomp {

// sub_00401000 | subsystem=Core/Windows | canonical | 10 blocks | 24 insns
void sub_00401000(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00401000: mov eax, dword ptr [0x55413c]
    uint32_t t0 = mem.r32(0x0055413cu);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x00401005: test eax, eax
    uint32_t t1 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    // 0x00401007: je 0x401042
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00401042;
    goto bb_00401009;
}
bb_00401042: {
    // 0x00401042: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x00401047: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00401009: {
    // 0x00401009: cmp dword ptr [eax], 0xf0fff004
    uint32_t t2 = mem.r32(ctx.eax);
    uint32_t t3 = static_cast<uint32_t>(t2 - 0xf0fff004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t2, 0xf0fff004u, t3);
    // 0x0040100f: je 0x401014
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00401014;
    goto bb_00401011;
}
bb_00401014: {
    // 0x00401014: xor ecx, ecx
    uint32_t t4 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x00401016: add eax, 0x24
    uint32_t t5 = static_cast<uint32_t>(ctx.eax + 0x00000024u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000024u, t5);
    ctx.eax = static_cast<uint32_t>(t5);
    // 0x00401019: lea esp, [esp]
    ctx.esp = static_cast<uint32_t>(ctx.esp);
    goto bb_00401020;
}
bb_00401011: {
    // 0x00401011: xor eax, eax
    uint32_t t6 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t6);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x00401013: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00401020: {
    // 0x00401020: cmp dword ptr [eax - 0xc], 0
    uint32_t t7 = static_cast<uint32_t>(ctx.eax + 0xfffffff4u);
    uint32_t t8 = mem.r32(t7);
    uint32_t t9 = static_cast<uint32_t>(t8 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t8, 0x00000000u, t9);
    // 0x00401024: jl 0x401011
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_00401011;
}
{
    // 0x00401026: cmp dword ptr [eax - 8], 0
    uint32_t t10 = static_cast<uint32_t>(ctx.eax + 0xfffffff8u);
    uint32_t t11 = mem.r32(t10);
    uint32_t t12 = static_cast<uint32_t>(t11 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t11, 0x00000000u, t12);
    // 0x0040102a: jl 0x401011
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_00401011;
}
{
    // 0x0040102c: cmp dword ptr [eax], 0
    uint32_t t13 = mem.r32(ctx.eax);
    uint32_t t14 = static_cast<uint32_t>(t13 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t13, 0x00000000u, t14);
    // 0x0040102f: jl 0x401011
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_00401011;
}
{
    // 0x00401031: cmp dword ptr [eax - 4], 0
    uint32_t t15 = static_cast<uint32_t>(ctx.eax + 0xfffffffcu);
    uint32_t t16 = mem.r32(t15);
    uint32_t t17 = static_cast<uint32_t>(t16 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t16, 0x00000000u, t17);
    // 0x00401035: jl 0x401011
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_00401011;
}
{
    // 0x00401037: add ecx, 1
    uint32_t t18 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t18);
    ctx.ecx = static_cast<uint32_t>(t18);
    // 0x0040103a: add eax, 0x10
    uint32_t t19 = static_cast<uint32_t>(ctx.eax + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000010u, t19);
    ctx.eax = static_cast<uint32_t>(t19);
    // 0x0040103d: cmp ecx, 0x28
    uint32_t t20 = static_cast<uint32_t>(ctx.ecx - 0x00000028u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000028u, t20);
    // 0x00401040: jl 0x401020
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_00401020;
    goto bb_00401042;
}
}

// sub_00401050 | subsystem=Core/Windows | canonical | 1 blocks | 20 insns
void sub_00401050(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00401050: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x00401052: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
    // 0x00401053: mov esi, dword ptr [0x55413c]
    uint32_t t2 = mem.r32(0x0055413cu);
    ctx.esi = static_cast<uint32_t>(t2);
    // 0x00401059: push 0x280
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x00000280u);
    // 0x0040105e: lea ecx, [esi + 0x18]
    uint32_t t4 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x00401061: push eax
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.eax);
    // 0x00401062: push ecx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ecx);
    // 0x00401063: mov dword ptr [esi], 0xf0fff004
    mem.w32(ctx.esi, 0xf0fff004u);
    // 0x00401069: mov dword ptr [esi + 4], eax
    uint32_t t7 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t7, ctx.eax);
    // 0x0040106c: mov dword ptr [esi + 8], eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t8, ctx.eax);
    // 0x0040106f: mov dword ptr [esi + 0xc], eax
    uint32_t t9 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t9, ctx.eax);
    // 0x00401072: mov dword ptr [esi + 0x10], eax
    uint32_t t10 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    mem.w32(t10, ctx.eax);
    // 0x00401075: mov dword ptr [esi + 0x14], eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esi + 0x00000014u);
    mem.w32(t11, ctx.eax);
    // 0x00401078: call 0x4e6340
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x0040107du);
    hle_crt_004e6340(ctx, mem);
    // 0x0040107d: add esi, 0x298
    uint32_t t13 = static_cast<uint32_t>(ctx.esi + 0x00000298u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000298u, t13);
    ctx.esi = static_cast<uint32_t>(t13);
    // 0x00401083: push esi
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, ctx.esi);
    // 0x00401084: call 0x4bbfa0
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x00401089u);
    sub_004bbfa0(ctx, mem);
    // 0x00401089: add esp, 0x10
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t16);
    ctx.esp = static_cast<uint32_t>(t16);
    // 0x0040108c: pop esi
    uint32_t t17 = ctx.esp;
    uint32_t t18 = mem.r32(t17);
    uint32_t t19 = static_cast<uint32_t>(t17 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    ctx.esi = static_cast<uint32_t>(t18);
    // 0x0040108d: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00401110 | subsystem=Core/Windows | canonical | 13 blocks | 53 insns
void sub_00401110(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00401110: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x00401111: cmp dword ptr [0x55413c], 0
    uint32_t t1 = mem.r32(0x0055413cu);
    uint32_t t2 = static_cast<uint32_t>(t1 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t1, 0x00000000u, t2);
    // 0x00401118: je 0x4011b5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004011b5;
    goto bb_0040111e;
}
bb_004011b5: {
    // 0x004011b5: pop ecx
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x004011b6: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040111e: {
    // 0x0040111e: call 0x401000
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x00401123u);
    sub_00401000(ctx, mem);
    // 0x00401123: test eax, eax
    uint32_t t7 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    // 0x00401125: jne 0x40112c
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040112c;
    goto bb_00401127;
}
bb_0040112c: {
    // 0x0040112c: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x0040112d: push 0x5c
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x0000005cu);
    // 0x0040112f: call 0x4e0177
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x00401134u);
    hle_crt_004e0177(ctx, mem);
    // 0x00401134: add esp, 4
    uint32_t t11 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t11);
    ctx.esp = static_cast<uint32_t>(t11);
    // 0x00401137: test eax, eax
    uint32_t t12 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t12);
    // 0x00401139: je 0x401146
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00401146;
    goto bb_0040113b;
}
bb_00401127: {
    // 0x00401127: call 0x401050
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x0040112cu);
    sub_00401050(ctx, mem);
    goto bb_0040112c;
}
bb_00401146: {
    // 0x00401146: xor esi, esi
    uint32_t t14 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    ctx.esi = static_cast<uint32_t>(t14);
    goto bb_00401148;
}
bb_0040113b: {
    // 0x0040113b: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0040113d: call 0x413c60
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x00401142u);
    sub_00413c60(ctx, mem);
    // 0x00401142: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x00401144: jmp 0x401148
}
bb_00401148: {
    // 0x00401148: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x0040114a: call 0x414000
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x0040114fu);
    sub_00414000(ctx, mem);
    // 0x0040114f: push 0
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x00000000u);
    // 0x00401151: push 0x80
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x00000080u);
    // 0x00401156: push 2
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x00000002u);
    // 0x00401158: push 0
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x00000000u);
    // 0x0040115a: push 2
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x00000002u);
    // 0x0040115c: push 0x40000000
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x40000000u);
    // 0x00401161: push 0x534f38
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x00534f38u);
    // 0x00401166: call dword ptr [0x51b054]
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x0040116cu);
    hle_iat_call(ctx, mem, 0x0051b054u);
    // 0x0040116c: cmp eax, -1
    uint32_t t25 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t25);
    // 0x0040116f: je 0x4011a0
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004011a0;
    goto bb_00401171;
}
bb_004011a0: {
    // 0x004011a0: test esi, esi
    uint32_t t26 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t26);
    // 0x004011a2: je 0x4011b4
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004011b4;
    goto bb_004011a4;
}
bb_00401171: {
    // 0x00401171: test eax, eax
    uint32_t t27 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t27);
    // 0x00401173: mov dword ptr [esi], eax
    mem.w32(ctx.esi, ctx.eax);
    // 0x00401175: mov dword ptr [esi + 0x1c], 1
    uint32_t t28 = static_cast<uint32_t>(ctx.esi + 0x0000001cu);
    mem.w32(t28, 0x00000001u);
    // 0x0040117c: je 0x4011a0
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004011a0;
    goto bb_0040117e;
}
bb_004011b4: {
    // 0x004011b4: pop esi
    uint32_t t29 = ctx.esp;
    uint32_t t30 = mem.r32(t29);
    uint32_t t31 = static_cast<uint32_t>(t29 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    ctx.esi = static_cast<uint32_t>(t30);
    goto bb_004011b5;
}
bb_004011a4: {
    // 0x004011a4: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004011a6: call 0x414000
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x004011abu);
    sub_00414000(ctx, mem);
    // 0x004011ab: push esi
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, ctx.esi);
    // 0x004011ac: call 0x4e02f3
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x004011b1u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004011b1: add esp, 4
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t35);
    ctx.esp = static_cast<uint32_t>(t35);
    goto bb_004011b4;
}
bb_0040117e: {
    // 0x0040117e: mov edx, dword ptr [0x55413c]
    uint32_t t36 = mem.r32(0x0055413cu);
    ctx.edx = static_cast<uint32_t>(t36);
    // 0x00401184: push 0
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, 0x00000000u);
    // 0x00401186: lea ecx, [esp + 8]
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.ecx = static_cast<uint32_t>(t38);
    // 0x0040118a: push ecx
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, ctx.ecx);
    // 0x0040118b: push 0x3e0
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, 0x000003e0u);
    // 0x00401190: push edx
    uint32_t t41 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    mem.w32(t41, ctx.edx);
    // 0x00401191: push eax
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, ctx.eax);
    // 0x00401192: mov dword ptr [esp + 0x18], 0
    uint32_t t43 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t43, 0x00000000u);
    // 0x0040119a: call dword ptr [0x51b0ac]
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, 0x004011a0u);
    hle_iat_call(ctx, mem, 0x0051b0acu);
    goto bb_004011a0;
}
}

// sub_004011e0 | subsystem=Core/Windows | canonical | 19 blocks | 131 insns
void sub_004011e0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004011e0: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x004011e1: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x004011e3: and esp, 0xfffffff8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xfffffff8u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x004011e6: push ebx
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebx);
    // 0x004011e7: push ebp
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.ebp);
    // 0x004011e8: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x004011e9: push edi
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.edi);
    // 0x004011ea: push 0x5c
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0000005cu);
    // 0x004011ec: call 0x4e0177
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x004011f1u);
    hle_crt_004e0177(ctx, mem);
    // 0x004011f1: xor edi, edi
    uint32_t t8 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t8);
    ctx.edi = static_cast<uint32_t>(t8);
    // 0x004011f3: add esp, 4
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t9);
    ctx.esp = static_cast<uint32_t>(t9);
    // 0x004011f6: cmp eax, edi
    uint32_t t10 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t10);
    // 0x004011f8: je 0x401205
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00401205;
    goto bb_004011fa;
}
bb_00401205: {
    // 0x00401205: xor ebp, ebp
    uint32_t t11 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    ctx.ebp = static_cast<uint32_t>(t11);
    goto bb_00401207;
}
bb_004011fa: {
    // 0x004011fa: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004011fc: call 0x413c60
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x00401201u);
    sub_00413c60(ctx, mem);
    // 0x00401201: mov ebp, eax
    ctx.ebp = static_cast<uint32_t>(ctx.eax);
    // 0x00401203: jmp 0x401207
}
bb_00401207: {
    // 0x00401207: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x00401209: call 0x414000
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x0040120eu);
    sub_00414000(ctx, mem);
    // 0x0040120e: push 0x534f38
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x00534f38u);
    // 0x00401213: mov esi, 0x76e9c4
    ctx.esi = static_cast<uint32_t>(0x0076e9c4u);
    // 0x00401218: call 0x4db8e0
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x0040121du);
    sub_004db8e0(ctx, mem);
    // 0x0040121d: cmp eax, edi
    uint32_t t16 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t16);
    // 0x0040121f: je 0x401230
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00401230;
    goto bb_00401221;
}
bb_00401230: {
    // 0x00401230: push edi
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, ctx.edi);
    // 0x00401231: push 0x10000080
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x10000080u);
    // 0x00401236: push 3
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x00000003u);
    // 0x00401238: push edi
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, ctx.edi);
    // 0x00401239: push 1
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x00000001u);
    // 0x0040123b: push 0x80000000
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x80000000u);
    // 0x00401240: push 0x534f38
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x00534f38u);
    // 0x00401245: call dword ptr [0x51b054]
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x0040124bu);
    hle_iat_call(ctx, mem, 0x0051b054u);
    // 0x0040124b: cmp eax, -1
    uint32_t t25 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t25);
    // 0x0040124e: je 0x401299
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00401299;
    goto bb_00401250;
}
bb_00401221: {
    // 0x00401221: mov dword ptr [ebp], edi
    mem.w32(ctx.ebp, ctx.edi);
    // 0x00401224: mov dword ptr [ebp + 0x1c], 3
    uint32_t t26 = static_cast<uint32_t>(ctx.ebp + 0x0000001cu);
    mem.w32(t26, 0x00000003u);
    // 0x0040122b: mov dword ptr [ebp + 0x58], eax
    uint32_t t27 = static_cast<uint32_t>(ctx.ebp + 0x00000058u);
    mem.w32(t27, ctx.eax);
    // 0x0040122e: jmp 0x401256
    goto bb_00401256;
}
bb_00401299: {
    // 0x00401299: push 0x3e0
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x000003e0u);
    // 0x0040129e: call 0x4e0230
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x004012a3u);
    hle_crt_004e0230(ctx, mem);
    // 0x004012a3: mov ebx, eax
    ctx.ebx = static_cast<uint32_t>(ctx.eax);
    // 0x004012a5: push 0x280
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x00000280u);
    // 0x004012aa: lea eax, [ebx + 0x18]
    uint32_t t31 = static_cast<uint32_t>(ctx.ebx + 0x00000018u);
    ctx.eax = static_cast<uint32_t>(t31);
    // 0x004012ad: push edi
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, ctx.edi);
    // 0x004012ae: mov esi, ebx
    ctx.esi = static_cast<uint32_t>(ctx.ebx);
    // 0x004012b0: push eax
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, ctx.eax);
    // 0x004012b1: mov dword ptr [0x55413c], esi
    mem.w32(0x0055413cu, ctx.esi);
    // 0x004012b7: mov dword ptr [ebx], 0xf0fff004
    mem.w32(ctx.ebx, 0xf0fff004u);
    // 0x004012bd: mov dword ptr [ebx + 4], edi
    uint32_t t34 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    mem.w32(t34, ctx.edi);
    // 0x004012c0: mov dword ptr [ebx + 8], edi
    uint32_t t35 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    mem.w32(t35, ctx.edi);
    // 0x004012c3: mov dword ptr [ebx + 0xc], edi
    uint32_t t36 = static_cast<uint32_t>(ctx.ebx + 0x0000000cu);
    mem.w32(t36, ctx.edi);
    // 0x004012c6: mov dword ptr [ebx + 0x10], edi
    uint32_t t37 = static_cast<uint32_t>(ctx.ebx + 0x00000010u);
    mem.w32(t37, ctx.edi);
    // 0x004012c9: mov dword ptr [ebx + 0x14], edi
    uint32_t t38 = static_cast<uint32_t>(ctx.ebx + 0x00000014u);
    mem.w32(t38, ctx.edi);
    // 0x004012cc: call 0x4e6340
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, 0x004012d1u);
    hle_crt_004e6340(ctx, mem);
    // 0x004012d1: lea eax, [ebx + 0x298]
    uint32_t t40 = static_cast<uint32_t>(ctx.ebx + 0x00000298u);
    ctx.eax = static_cast<uint32_t>(t40);
    // 0x004012d7: push eax
    uint32_t t41 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    mem.w32(t41, ctx.eax);
    // 0x004012d8: call 0x4bbfa0
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, 0x004012ddu);
    sub_004bbfa0(ctx, mem);
    // 0x004012dd: add esp, 0x14
    uint32_t t43 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000014u, t43);
    ctx.esp = static_cast<uint32_t>(t43);
    goto bb_004012e0;
}
bb_00401250: {
    // 0x00401250: mov dword ptr [ebp], eax
    mem.w32(ctx.ebp, ctx.eax);
    // 0x00401253: mov dword ptr [ebp + 0x1c], edi
    uint32_t t44 = static_cast<uint32_t>(ctx.ebp + 0x0000001cu);
    mem.w32(t44, ctx.edi);
}
bb_00401256: {
    // 0x00401256: xor eax, eax
    uint32_t t45 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t45);
    ctx.eax = static_cast<uint32_t>(t45);
    // 0x00401258: mov dword ptr [ebp + 8], eax
    uint32_t t46 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    mem.w32(t46, ctx.eax);
    // 0x0040125b: mov dword ptr [ebp + 0xc], eax
    uint32_t t47 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    mem.w32(t47, ctx.eax);
    // 0x0040125e: mov dword ptr [ebp + 0x10], eax
    uint32_t t48 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    mem.w32(t48, ctx.eax);
    // 0x00401261: mov dword ptr [ebp + 0x14], eax
    uint32_t t49 = static_cast<uint32_t>(ctx.ebp + 0x00000014u);
    mem.w32(t49, ctx.eax);
    // 0x00401264: mov dword ptr [ebp + 0x18], eax
    uint32_t t50 = static_cast<uint32_t>(ctx.ebp + 0x00000018u);
    mem.w32(t50, ctx.eax);
    // 0x00401267: push edi
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, ctx.edi);
    // 0x00401268: xor edi, edi
    uint32_t t52 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t52);
    ctx.edi = static_cast<uint32_t>(t52);
    // 0x0040126a: xor ebx, ebx
    uint32_t t53 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t53);
    ctx.ebx = static_cast<uint32_t>(t53);
    // 0x0040126c: mov eax, ebp
    ctx.eax = static_cast<uint32_t>(ctx.ebp);
    // 0x0040126e: call 0x413e70
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, 0x00401273u);
    sub_00413e70(ctx, mem);
    // 0x00401273: test eax, eax
    uint32_t t55 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t55);
    // 0x00401275: je 0x401288
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00401288;
    goto bb_00401277;
}
bb_004012e0: {
    // 0x004012e0: cmp ebp, edi
    uint32_t t56 = static_cast<uint32_t>(ctx.ebp - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebp, ctx.edi, t56);
    // 0x004012e2: je 0x4012fa
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004012fa;
    goto bb_004012e4;
}
bb_00401288: {
    // 0x00401288: add dword ptr [ebp + 0x48], 1
    uint32_t t57 = static_cast<uint32_t>(ctx.ebp + 0x00000048u);
    uint32_t t58 = mem.r32(t57);
    uint32_t t59 = static_cast<uint32_t>(t58 + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t58, 0x00000001u, t59);
    mem.w32(t57, t59);
    // 0x0040128c: mov ebx, dword ptr [ebp + 0x30]
    uint32_t t60 = static_cast<uint32_t>(ctx.ebp + 0x00000030u);
    uint32_t t61 = mem.r32(t60);
    ctx.ebx = static_cast<uint32_t>(t61);
    // 0x0040128f: mov esi, dword ptr [0x55413c]
    uint32_t t62 = mem.r32(0x0055413cu);
    ctx.esi = static_cast<uint32_t>(t62);
    // 0x00401295: xor edi, edi
    uint32_t t63 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t63);
    ctx.edi = static_cast<uint32_t>(t63);
    // 0x00401297: jmp 0x4012e0
    goto bb_004012e0;
}
bb_00401277: {
    // 0x00401277: mov eax, dword ptr [ebp + 0x3c]
    uint32_t t64 = static_cast<uint32_t>(ctx.ebp + 0x0000003cu);
    uint32_t t65 = mem.r32(t64);
    ctx.eax = static_cast<uint32_t>(t65);
    // 0x0040127a: test eax, eax
    uint32_t t66 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t66);
    // 0x0040127c: je 0x401288
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00401288;
    goto bb_0040127e;
}
bb_004012fa: {
    // 0x004012fa: cmp ebx, edi
    uint32_t t67 = static_cast<uint32_t>(ctx.ebx - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.edi, t67);
    // 0x004012fc: je 0x401322
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00401322;
    goto bb_004012fe;
}
bb_004012e4: {
    // 0x004012e4: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x004012e6: call 0x414000
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, 0x004012ebu);
    sub_00414000(ctx, mem);
    // 0x004012eb: push ebp
    uint32_t t69 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    mem.w32(t69, ctx.ebp);
    // 0x004012ec: call 0x4e02f3
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, 0x004012f1u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004012f1: mov esi, dword ptr [0x55413c]
    uint32_t t71 = mem.r32(0x0055413cu);
    ctx.esi = static_cast<uint32_t>(t71);
    // 0x004012f7: add esp, 4
    uint32_t t72 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t72);
    ctx.esp = static_cast<uint32_t>(t72);
    goto bb_004012fa;
}
bb_0040127e: {
    // 0x0040127e: push ebx
    uint32_t t73 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    mem.w32(t73, ctx.ebx);
    // 0x0040127f: push -1
    uint32_t t74 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    mem.w32(t74, 0xffffffffu);
    // 0x00401281: push eax
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, ctx.eax);
    // 0x00401282: call dword ptr [0x51b1c4]
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    mem.w32(t76, 0x00401288u);
    hle_iat_call(ctx, mem, 0x0051b1c4u);
    goto bb_00401288;
}
bb_00401322: {
    // 0x00401322: call 0x401000
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, 0x00401327u);
    sub_00401000(ctx, mem);
    // 0x00401327: test eax, eax
    uint32_t t78 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t78);
    // 0x00401329: jne 0x40135e
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040135e;
    goto bb_0040132b;
}
bb_004012fe: {
    // 0x004012fe: mov ecx, 0xf8
    ctx.ecx = static_cast<uint32_t>(0x000000f8u);
    // 0x00401303: mov esi, ebx
    ctx.esi = static_cast<uint32_t>(ctx.ebx);
    // 0x00401305: mov edi, 0x553be0
    ctx.edi = static_cast<uint32_t>(0x00553be0u);
    // 0x0040130a: rep movsd dword ptr es:[edi], dword ptr [esi]
    recomp_detail::exec_string_op<uint32_t>(ctx, mem, 0, 1);
    // 0x0040130c: mov esi, 0x553be0
    ctx.esi = static_cast<uint32_t>(0x00553be0u);
    // 0x00401311: push ebx
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, ctx.ebx);
    // 0x00401312: mov dword ptr [0x55413c], esi
    mem.w32(0x0055413cu, ctx.esi);
    // 0x00401318: call 0x4e00d0
    uint32_t t80 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    mem.w32(t80, 0x0040131du);
    hle_crt_004e00d0(ctx, mem);
    // 0x0040131d: add esp, 4
    uint32_t t81 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t81);
    ctx.esp = static_cast<uint32_t>(t81);
    // 0x00401320: xor edi, edi
    uint32_t t82 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t82);
    ctx.edi = static_cast<uint32_t>(t82);
    goto bb_00401322;
}
bb_0040135e: {
    // 0x0040135e: pop edi
    uint32_t t83 = ctx.esp;
    uint32_t t84 = mem.r32(t83);
    uint32_t t85 = static_cast<uint32_t>(t83 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t85);
    ctx.edi = static_cast<uint32_t>(t84);
    // 0x0040135f: pop esi
    uint32_t t86 = ctx.esp;
    uint32_t t87 = mem.r32(t86);
    uint32_t t88 = static_cast<uint32_t>(t86 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t88);
    ctx.esi = static_cast<uint32_t>(t87);
    // 0x00401360: pop ebp
    uint32_t t89 = ctx.esp;
    uint32_t t90 = mem.r32(t89);
    uint32_t t91 = static_cast<uint32_t>(t89 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    ctx.ebp = static_cast<uint32_t>(t90);
    // 0x00401361: pop ebx
    uint32_t t92 = ctx.esp;
    uint32_t t93 = mem.r32(t92);
    uint32_t t94 = static_cast<uint32_t>(t92 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t94);
    ctx.ebx = static_cast<uint32_t>(t93);
    // 0x00401362: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x00401364: pop ebp
    uint32_t t95 = ctx.esp;
    uint32_t t96 = mem.r32(t95);
    uint32_t t97 = static_cast<uint32_t>(t95 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t97);
    ctx.ebp = static_cast<uint32_t>(t96);
    // 0x00401365: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040132b: {
    // 0x0040132b: push 0x280
    uint32_t t98 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t98);
    mem.w32(t98, 0x00000280u);
    // 0x00401330: lea eax, [esi + 0x18]
    uint32_t t99 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    ctx.eax = static_cast<uint32_t>(t99);
    // 0x00401333: push edi
    uint32_t t100 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t100);
    mem.w32(t100, ctx.edi);
    // 0x00401334: push eax
    uint32_t t101 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t101);
    mem.w32(t101, ctx.eax);
    // 0x00401335: mov dword ptr [esi], 0xf0fff004
    mem.w32(ctx.esi, 0xf0fff004u);
    // 0x0040133b: mov dword ptr [esi + 4], edi
    uint32_t t102 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t102, ctx.edi);
    // 0x0040133e: mov dword ptr [esi + 8], edi
    uint32_t t103 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t103, ctx.edi);
    // 0x00401341: mov dword ptr [esi + 0xc], edi
    uint32_t t104 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t104, ctx.edi);
    // 0x00401344: mov dword ptr [esi + 0x10], edi
    uint32_t t105 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    mem.w32(t105, ctx.edi);
    // 0x00401347: mov dword ptr [esi + 0x14], edi
    uint32_t t106 = static_cast<uint32_t>(ctx.esi + 0x00000014u);
    mem.w32(t106, ctx.edi);
    // 0x0040134a: call 0x4e6340
    uint32_t t107 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t107);
    mem.w32(t107, 0x0040134fu);
    hle_crt_004e6340(ctx, mem);
    // 0x0040134f: add esi, 0x298
    uint32_t t108 = static_cast<uint32_t>(ctx.esi + 0x00000298u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000298u, t108);
    ctx.esi = static_cast<uint32_t>(t108);
    // 0x00401355: push esi
    uint32_t t109 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t109);
    mem.w32(t109, ctx.esi);
    // 0x00401356: call 0x4bbfa0
    uint32_t t110 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t110);
    mem.w32(t110, 0x0040135bu);
    sub_004bbfa0(ctx, mem);
    // 0x0040135b: add esp, 0x10
    uint32_t t111 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t111);
    ctx.esp = static_cast<uint32_t>(t111);
    goto bb_0040135e;
}
}

// sub_00401370 | subsystem=Core/Windows | canonical | 34 blocks | 87 insns
void sub_00401370(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00401370: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x00401371: mov esi, dword ptr [0x554140]
    uint32_t t1 = mem.r32(0x00554140u);
    ctx.esi = static_cast<uint32_t>(t1);
    // 0x00401377: test esi, esi
    uint32_t t2 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    // 0x00401379: jne 0x401382
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00401382;
    goto bb_0040137b;
}
bb_00401382: {
    // 0x00401382: cmp dword ptr [esi], 0xf0fff004
    uint32_t t3 = mem.r32(ctx.esi);
    uint32_t t4 = static_cast<uint32_t>(t3 - 0xf0fff004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t3, 0xf0fff004u, t4);
    // 0x00401388: jne 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040148a;
    goto bb_0040138e;
}
bb_0040137b: {
    // 0x0040137b: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x00401380: pop esi
    uint32_t t5 = ctx.esp;
    uint32_t t6 = mem.r32(t5);
    uint32_t t7 = static_cast<uint32_t>(t5 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x00401381: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040148a: {
    // 0x0040148a: xor eax, eax
    uint32_t t8 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t8);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x0040148c: pop esi
    uint32_t t9 = ctx.esp;
    uint32_t t10 = mem.r32(t9);
    uint32_t t11 = static_cast<uint32_t>(t9 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    ctx.esi = static_cast<uint32_t>(t10);
    // 0x0040148d: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040138e: {
    // 0x0040138e: xor edx, edx
    uint32_t t12 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t12);
    ctx.edx = static_cast<uint32_t>(t12);
    // 0x00401390: lea eax, [esi + 0x10]
    uint32_t t13 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    ctx.eax = static_cast<uint32_t>(t13);
}
bb_00401393: {
    // 0x00401393: mov ecx, dword ptr [eax - 0xc]
    uint32_t t14 = static_cast<uint32_t>(ctx.eax + 0xfffffff4u);
    uint32_t t15 = mem.r32(t14);
    ctx.ecx = static_cast<uint32_t>(t15);
    // 0x00401396: test ecx, ecx
    uint32_t t16 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    // 0x00401398: jl 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040148a;
}
{
    // 0x0040139e: cmp ecx, 4
    uint32_t t17 = static_cast<uint32_t>(ctx.ecx - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000004u, t17);
    // 0x004013a1: jg 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0040148a;
}
{
    // 0x004013a7: mov ecx, dword ptr [eax - 8]
    uint32_t t18 = static_cast<uint32_t>(ctx.eax + 0xfffffff8u);
    uint32_t t19 = mem.r32(t18);
    ctx.ecx = static_cast<uint32_t>(t19);
    // 0x004013aa: cmp ecx, 1
    uint32_t t20 = static_cast<uint32_t>(ctx.ecx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000001u, t20);
    // 0x004013ad: jl 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040148a;
}
{
    // 0x004013b3: cmp ecx, 3
    uint32_t t21 = static_cast<uint32_t>(ctx.ecx - 0x00000003u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000003u, t21);
    // 0x004013b6: jg 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0040148a;
}
{
    // 0x004013bc: mov ecx, dword ptr [eax]
    uint32_t t22 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t22);
    // 0x004013be: test ecx, ecx
    uint32_t t23 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t23);
    // 0x004013c0: jl 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040148a;
}
{
    // 0x004013c6: cmp ecx, 4
    uint32_t t24 = static_cast<uint32_t>(ctx.ecx - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000004u, t24);
    // 0x004013c9: jg 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0040148a;
}
{
    // 0x004013cf: mov ecx, dword ptr [eax - 4]
    uint32_t t25 = static_cast<uint32_t>(ctx.eax + 0xfffffffcu);
    uint32_t t26 = mem.r32(t25);
    ctx.ecx = static_cast<uint32_t>(t26);
    // 0x004013d2: test ecx, ecx
    uint32_t t27 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t27);
    // 0x004013d4: jl 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040148a;
}
{
    // 0x004013da: cmp ecx, 4
    uint32_t t28 = static_cast<uint32_t>(ctx.ecx - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000004u, t28);
    // 0x004013dd: jg 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0040148a;
}
{
    // 0x004013e3: mov ecx, dword ptr [eax + 4]
    uint32_t t29 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t30 = mem.r32(t29);
    ctx.ecx = static_cast<uint32_t>(t30);
    // 0x004013e6: test ecx, ecx
    uint32_t t31 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t31);
    // 0x004013e8: jl 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040148a;
}
{
    // 0x004013ee: cmp ecx, 1
    uint32_t t32 = static_cast<uint32_t>(ctx.ecx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000001u, t32);
    // 0x004013f1: jg 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0040148a;
}
{
    // 0x004013f7: add edx, 1
    uint32_t t33 = static_cast<uint32_t>(ctx.edx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000001u, t33);
    ctx.edx = static_cast<uint32_t>(t33);
    // 0x004013fa: add eax, 0x14
    uint32_t t34 = static_cast<uint32_t>(ctx.eax + 0x00000014u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000014u, t34);
    ctx.eax = static_cast<uint32_t>(t34);
    // 0x004013fd: cmp edx, 0x10
    uint32_t t35 = static_cast<uint32_t>(ctx.edx - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000010u, t35);
    // 0x00401400: jl 0x401393
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_00401393;
}
{
    // 0x00401402: mov eax, dword ptr [esi + 0x144]
    uint32_t t36 = static_cast<uint32_t>(ctx.esi + 0x00000144u);
    uint32_t t37 = mem.r32(t36);
    ctx.eax = static_cast<uint32_t>(t37);
    // 0x00401408: test eax, eax
    uint32_t t38 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t38);
    // 0x0040140a: jl 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040148a;
}
{
    // 0x0040140c: cmp eax, 0x15
    uint32_t t39 = static_cast<uint32_t>(ctx.eax - 0x00000015u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000015u, t39);
    // 0x0040140f: jg 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0040148a;
}
{
    // 0x00401411: mov eax, dword ptr [esi + 0x148]
    uint32_t t40 = static_cast<uint32_t>(ctx.esi + 0x00000148u);
    uint32_t t41 = mem.r32(t40);
    ctx.eax = static_cast<uint32_t>(t41);
    // 0x00401417: test eax, eax
    uint32_t t42 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t42);
    // 0x00401419: jl 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040148a;
}
{
    // 0x0040141b: cmp eax, 0x15
    uint32_t t43 = static_cast<uint32_t>(ctx.eax - 0x00000015u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000015u, t43);
    // 0x0040141e: jg 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0040148a;
}
{
    // 0x00401420: mov eax, dword ptr [esi + 0x150]
    uint32_t t44 = static_cast<uint32_t>(ctx.esi + 0x00000150u);
    uint32_t t45 = mem.r32(t44);
    ctx.eax = static_cast<uint32_t>(t45);
    // 0x00401426: test eax, eax
    uint32_t t46 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t46);
    // 0x00401428: jl 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040148a;
}
{
    // 0x0040142a: cmp eax, 1
    uint32_t t47 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t47);
    // 0x0040142d: jg 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0040148a;
}
{
    // 0x0040142f: mov eax, dword ptr [esi + 0x154]
    uint32_t t48 = static_cast<uint32_t>(ctx.esi + 0x00000154u);
    uint32_t t49 = mem.r32(t48);
    ctx.eax = static_cast<uint32_t>(t49);
    // 0x00401435: test eax, eax
    uint32_t t50 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t50);
    // 0x00401437: jl 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040148a;
}
{
    // 0x00401439: cmp eax, 1
    uint32_t t51 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t51);
    // 0x0040143c: jg 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0040148a;
}
{
    // 0x0040143e: mov eax, dword ptr [esi + 0x158]
    uint32_t t52 = static_cast<uint32_t>(ctx.esi + 0x00000158u);
    uint32_t t53 = mem.r32(t52);
    ctx.eax = static_cast<uint32_t>(t53);
    // 0x00401444: test eax, eax
    uint32_t t54 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t54);
    // 0x00401446: jl 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040148a;
}
{
    // 0x00401448: cmp eax, 1
    uint32_t t55 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t55);
    // 0x0040144b: jg 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0040148a;
}
{
    // 0x0040144d: mov eax, dword ptr [esi + 0x15c]
    uint32_t t56 = static_cast<uint32_t>(ctx.esi + 0x0000015cu);
    uint32_t t57 = mem.r32(t56);
    ctx.eax = static_cast<uint32_t>(t57);
    // 0x00401453: test eax, eax
    uint32_t t58 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t58);
    // 0x00401455: jl 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040148a;
}
{
    // 0x00401457: cmp eax, 5
    uint32_t t59 = static_cast<uint32_t>(ctx.eax - 0x00000005u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000005u, t59);
    // 0x0040145a: jg 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0040148a;
}
{
    // 0x0040145c: mov eax, dword ptr [esi + 0x164]
    uint32_t t60 = static_cast<uint32_t>(ctx.esi + 0x00000164u);
    uint32_t t61 = mem.r32(t60);
    ctx.eax = static_cast<uint32_t>(t61);
    // 0x00401462: test eax, eax
    uint32_t t62 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t62);
    // 0x00401464: jl 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040148a;
}
{
    // 0x00401466: cmp eax, 1
    uint32_t t63 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t63);
    // 0x00401469: jg 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0040148a;
}
{
    // 0x0040146b: mov eax, dword ptr [esi + 0x170]
    uint32_t t64 = static_cast<uint32_t>(ctx.esi + 0x00000170u);
    uint32_t t65 = mem.r32(t64);
    ctx.eax = static_cast<uint32_t>(t65);
    // 0x00401471: test eax, eax
    uint32_t t66 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t66);
    // 0x00401473: jl 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040148a;
}
{
    // 0x00401475: jg 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0040148a;
}
{
    // 0x00401477: mov eax, dword ptr [esi + 0x14c]
    uint32_t t67 = static_cast<uint32_t>(ctx.esi + 0x0000014cu);
    uint32_t t68 = mem.r32(t67);
    ctx.eax = static_cast<uint32_t>(t68);
    // 0x0040147d: test eax, eax
    uint32_t t69 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t69);
    // 0x0040147f: jl 0x40148a
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040148a;
}
{
    // 0x00401481: cmp eax, 5
    uint32_t t70 = static_cast<uint32_t>(ctx.eax - 0x00000005u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000005u, t70);
    // 0x00401484: jle 0x40137b
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0040137b;
    goto bb_0040148a;
}
}

// sub_00401540 | subsystem=Core/Windows | canonical | 12 blocks | 55 insns
void sub_00401540(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00401540: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x00401541: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
    // 0x00401542: mov esi, dword ptr [0x554140]
    uint32_t t2 = mem.r32(0x00554140u);
    ctx.esi = static_cast<uint32_t>(t2);
    // 0x00401548: test esi, esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t3);
    // 0x0040154a: je 0x4015e7
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004015e7;
    goto bb_00401550;
}
bb_004015e7: {
    // 0x004015e7: pop esi
    uint32_t t4 = ctx.esp;
    uint32_t t5 = mem.r32(t4);
    uint32_t t6 = static_cast<uint32_t>(t4 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    ctx.esi = static_cast<uint32_t>(t5);
    // 0x004015e8: pop ecx
    uint32_t t7 = ctx.esp;
    uint32_t t8 = mem.r32(t7);
    uint32_t t9 = static_cast<uint32_t>(t7 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    ctx.ecx = static_cast<uint32_t>(t8);
    // 0x004015e9: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00401550: {
    // 0x00401550: call 0x401370
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x00401555u);
    sub_00401370(ctx, mem);
    // 0x00401555: test eax, eax
    uint32_t t11 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    // 0x00401557: jne 0x401560
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00401560;
    goto bb_00401559;
}
bb_00401560: {
    // 0x00401560: push 0x5c
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x0000005cu);
    // 0x00401562: call 0x4e0177
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x00401567u);
    hle_crt_004e0177(ctx, mem);
    // 0x00401567: add esp, 4
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t14);
    ctx.esp = static_cast<uint32_t>(t14);
    // 0x0040156a: test eax, eax
    uint32_t t15 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t15);
    // 0x0040156c: je 0x401579
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00401579;
    goto bb_0040156e;
}
bb_00401559: {
    // 0x00401559: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0040155b: call 0x401490
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x00401560u);
    sub_00401490(ctx, mem);
    goto bb_00401560;
}
bb_00401579: {
    // 0x00401579: xor esi, esi
    uint32_t t17 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t17);
    ctx.esi = static_cast<uint32_t>(t17);
    goto bb_0040157b;
}
bb_0040156e: {
    // 0x0040156e: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x00401570: call 0x413c60
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x00401575u);
    sub_00413c60(ctx, mem);
    // 0x00401575: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x00401577: jmp 0x40157b
}
bb_0040157b: {
    // 0x0040157b: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x0040157d: call 0x414000
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x00401582u);
    sub_00414000(ctx, mem);
    // 0x00401582: push 0
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x00000000u);
    // 0x00401584: push 0x80
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x00000080u);
    // 0x00401589: push 2
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x00000002u);
    // 0x0040158b: push 0
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x00000000u);
    // 0x0040158d: push 2
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x00000002u);
    // 0x0040158f: push 0x40000000
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x40000000u);
    // 0x00401594: push 0x534f54
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x00534f54u);
    // 0x00401599: call dword ptr [0x51b054]
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x0040159fu);
    hle_iat_call(ctx, mem, 0x0051b054u);
    // 0x0040159f: cmp eax, -1
    uint32_t t28 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t28);
    // 0x004015a2: je 0x4015d3
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004015d3;
    goto bb_004015a4;
}
bb_004015d3: {
    // 0x004015d3: test esi, esi
    uint32_t t29 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t29);
    // 0x004015d5: je 0x4015e7
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004015e7;
    goto bb_004015d7;
}
bb_004015a4: {
    // 0x004015a4: test eax, eax
    uint32_t t30 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t30);
    // 0x004015a6: mov dword ptr [esi], eax
    mem.w32(ctx.esi, ctx.eax);
    // 0x004015a8: mov dword ptr [esi + 0x1c], 1
    uint32_t t31 = static_cast<uint32_t>(ctx.esi + 0x0000001cu);
    mem.w32(t31, 0x00000001u);
    // 0x004015af: je 0x4015d3
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004015d3;
    goto bb_004015b1;
}
bb_004015d7: {
    // 0x004015d7: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004015d9: call 0x414000
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x004015deu);
    sub_00414000(ctx, mem);
    // 0x004015de: push esi
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, ctx.esi);
    // 0x004015df: call 0x4e02f3
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x004015e4u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004015e4: add esp, 4
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t35);
    ctx.esp = static_cast<uint32_t>(t35);
    goto bb_004015e7;
}
bb_004015b1: {
    // 0x004015b1: mov edx, dword ptr [0x554140]
    uint32_t t36 = mem.r32(0x00554140u);
    ctx.edx = static_cast<uint32_t>(t36);
    // 0x004015b7: push 0
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, 0x00000000u);
    // 0x004015b9: lea ecx, [esp + 8]
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.ecx = static_cast<uint32_t>(t38);
    // 0x004015bd: push ecx
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, ctx.ecx);
    // 0x004015be: push 0x17c
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, 0x0000017cu);
    // 0x004015c3: push edx
    uint32_t t41 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    mem.w32(t41, ctx.edx);
    // 0x004015c4: push eax
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, ctx.eax);
    // 0x004015c5: mov dword ptr [esp + 0x18], 0
    uint32_t t43 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t43, 0x00000000u);
    // 0x004015cd: call dword ptr [0x51b0ac]
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, 0x004015d3u);
    hle_iat_call(ctx, mem, 0x0051b0acu);
    goto bb_004015d3;
}
}

// sub_004015f0 | subsystem=Core/Windows | canonical | 19 blocks | 98 insns
void sub_004015f0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004015f0: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x004015f1: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x004015f3: and esp, 0xfffffff8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xfffffff8u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x004015f6: push ebx
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebx);
    // 0x004015f7: push ebp
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.ebp);
    // 0x004015f8: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x004015f9: push edi
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.edi);
    // 0x004015fa: push 0x5c
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0000005cu);
    // 0x004015fc: call 0x4e0177
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x00401601u);
    hle_crt_004e0177(ctx, mem);
    // 0x00401601: add esp, 4
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t8);
    ctx.esp = static_cast<uint32_t>(t8);
    // 0x00401604: test eax, eax
    uint32_t t9 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    // 0x00401606: je 0x401613
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00401613;
    goto bb_00401608;
}
bb_00401613: {
    // 0x00401613: xor ebp, ebp
    uint32_t t10 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.ebp = static_cast<uint32_t>(t10);
    goto bb_00401615;
}
bb_00401608: {
    // 0x00401608: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0040160a: call 0x413c60
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0x0040160fu);
    sub_00413c60(ctx, mem);
    // 0x0040160f: mov ebp, eax
    ctx.ebp = static_cast<uint32_t>(ctx.eax);
    // 0x00401611: jmp 0x401615
}
bb_00401615: {
    // 0x00401615: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x00401617: call 0x414000
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x0040161cu);
    sub_00414000(ctx, mem);
    // 0x0040161c: push 0x534f54
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x00534f54u);
    // 0x00401621: mov esi, 0x76e9c4
    ctx.esi = static_cast<uint32_t>(0x0076e9c4u);
    // 0x00401626: call 0x4db8e0
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x0040162bu);
    sub_004db8e0(ctx, mem);
    // 0x0040162b: test eax, eax
    uint32_t t15 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t15);
    // 0x0040162d: je 0x401642
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00401642;
    goto bb_0040162f;
}
bb_00401642: {
    // 0x00401642: push 0
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x00000000u);
    // 0x00401644: push 0x10000080
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x10000080u);
    // 0x00401649: push 3
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x00000003u);
    // 0x0040164b: push 0
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x00000000u);
    // 0x0040164d: push 1
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x00000001u);
    // 0x0040164f: push 0x80000000
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x80000000u);
    // 0x00401654: push 0x534f54
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x00534f54u);
    // 0x00401659: call dword ptr [0x51b054]
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x0040165fu);
    hle_iat_call(ctx, mem, 0x0051b054u);
    // 0x0040165f: cmp eax, -1
    uint32_t t24 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t24);
    // 0x00401662: je 0x4016a9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004016a9;
    goto bb_00401664;
}
bb_0040162f: {
    // 0x0040162f: mov dword ptr [ebp], 0
    mem.w32(ctx.ebp, 0x00000000u);
    // 0x00401636: mov dword ptr [ebp + 0x1c], 3
    uint32_t t25 = static_cast<uint32_t>(ctx.ebp + 0x0000001cu);
    mem.w32(t25, 0x00000003u);
    // 0x0040163d: mov dword ptr [ebp + 0x58], eax
    uint32_t t26 = static_cast<uint32_t>(ctx.ebp + 0x00000058u);
    mem.w32(t26, ctx.eax);
    // 0x00401640: jmp 0x40166e
    goto bb_0040166e;
}
bb_004016a9: {
    // 0x004016a9: push 0x17c
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x0000017cu);
    // 0x004016ae: call 0x4e0230
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x004016b3u);
    hle_crt_004e0230(ctx, mem);
    // 0x004016b3: mov ebx, eax
    ctx.ebx = static_cast<uint32_t>(ctx.eax);
    // 0x004016b5: add esp, 4
    uint32_t t29 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t29);
    ctx.esp = static_cast<uint32_t>(t29);
    // 0x004016b8: mov dword ptr [0x554140], ebx
    mem.w32(0x00554140u, ctx.ebx);
    // 0x004016be: call 0x401490
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x004016c3u);
    sub_00401490(ctx, mem);
    goto bb_004016c3;
}
bb_00401664: {
    // 0x00401664: mov dword ptr [ebp], eax
    mem.w32(ctx.ebp, ctx.eax);
    // 0x00401667: mov dword ptr [ebp + 0x1c], 0
    uint32_t t31 = static_cast<uint32_t>(ctx.ebp + 0x0000001cu);
    mem.w32(t31, 0x00000000u);
}
bb_0040166e: {
    // 0x0040166e: xor eax, eax
    uint32_t t32 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t32);
    ctx.eax = static_cast<uint32_t>(t32);
    // 0x00401670: mov dword ptr [ebp + 8], eax
    uint32_t t33 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    mem.w32(t33, ctx.eax);
    // 0x00401673: mov dword ptr [ebp + 0xc], eax
    uint32_t t34 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    mem.w32(t34, ctx.eax);
    // 0x00401676: mov dword ptr [ebp + 0x10], eax
    uint32_t t35 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    mem.w32(t35, ctx.eax);
    // 0x00401679: mov dword ptr [ebp + 0x14], eax
    uint32_t t36 = static_cast<uint32_t>(ctx.ebp + 0x00000014u);
    mem.w32(t36, ctx.eax);
    // 0x0040167c: mov dword ptr [ebp + 0x18], eax
    uint32_t t37 = static_cast<uint32_t>(ctx.ebp + 0x00000018u);
    mem.w32(t37, ctx.eax);
    // 0x0040167f: push eax
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, ctx.eax);
    // 0x00401680: xor edi, edi
    uint32_t t39 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t39);
    ctx.edi = static_cast<uint32_t>(t39);
    // 0x00401682: xor ebx, ebx
    uint32_t t40 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t40);
    ctx.ebx = static_cast<uint32_t>(t40);
    // 0x00401684: mov eax, ebp
    ctx.eax = static_cast<uint32_t>(ctx.ebp);
    // 0x00401686: call 0x413e70
    uint32_t t41 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    mem.w32(t41, 0x0040168bu);
    sub_00413e70(ctx, mem);
    // 0x0040168b: test eax, eax
    uint32_t t42 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t42);
    // 0x0040168d: je 0x4016a0
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004016a0;
    goto bb_0040168f;
}
bb_004016c3: {
    // 0x004016c3: test ebp, ebp
    uint32_t t43 = static_cast<uint32_t>(ctx.ebp & ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t43);
    // 0x004016c5: je 0x4016d7
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004016d7;
    goto bb_004016c7;
}
bb_004016a0: {
    // 0x004016a0: add dword ptr [ebp + 0x48], 1
    uint32_t t44 = static_cast<uint32_t>(ctx.ebp + 0x00000048u);
    uint32_t t45 = mem.r32(t44);
    uint32_t t46 = static_cast<uint32_t>(t45 + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t45, 0x00000001u, t46);
    mem.w32(t44, t46);
    // 0x004016a4: mov ebx, dword ptr [ebp + 0x30]
    uint32_t t47 = static_cast<uint32_t>(ctx.ebp + 0x00000030u);
    uint32_t t48 = mem.r32(t47);
    ctx.ebx = static_cast<uint32_t>(t48);
    // 0x004016a7: jmp 0x4016c3
    goto bb_004016c3;
}
bb_0040168f: {
    // 0x0040168f: mov eax, dword ptr [ebp + 0x3c]
    uint32_t t49 = static_cast<uint32_t>(ctx.ebp + 0x0000003cu);
    uint32_t t50 = mem.r32(t49);
    ctx.eax = static_cast<uint32_t>(t50);
    // 0x00401692: test eax, eax
    uint32_t t51 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t51);
    // 0x00401694: je 0x4016a0
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004016a0;
    goto bb_00401696;
}
bb_004016d7: {
    // 0x004016d7: test ebx, ebx
    uint32_t t52 = static_cast<uint32_t>(ctx.ebx & ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t52);
    // 0x004016d9: je 0x4016fc
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004016fc;
    goto bb_004016db;
}
bb_004016c7: {
    // 0x004016c7: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x004016c9: call 0x414000
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, 0x004016ceu);
    sub_00414000(ctx, mem);
    // 0x004016ce: push ebp
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, ctx.ebp);
    // 0x004016cf: call 0x4e02f3
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, 0x004016d4u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004016d4: add esp, 4
    uint32_t t56 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t56);
    ctx.esp = static_cast<uint32_t>(t56);
    goto bb_004016d7;
}
bb_00401696: {
    // 0x00401696: push ebx
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, ctx.ebx);
    // 0x00401697: push -1
    uint32_t t58 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    mem.w32(t58, 0xffffffffu);
    // 0x00401699: push eax
    uint32_t t59 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    mem.w32(t59, ctx.eax);
    // 0x0040169a: call dword ptr [0x51b1c4]
    uint32_t t60 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t60);
    mem.w32(t60, 0x004016a0u);
    hle_iat_call(ctx, mem, 0x0051b1c4u);
    goto bb_004016a0;
}
bb_004016fc: {
    // 0x004016fc: call 0x401370
    uint32_t t61 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    mem.w32(t61, 0x00401701u);
    sub_00401370(ctx, mem);
    // 0x00401701: test eax, eax
    uint32_t t62 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t62);
    // 0x00401703: jne 0x40170f
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040170f;
    goto bb_00401705;
}
bb_004016db: {
    // 0x004016db: mov ecx, 0x5f
    ctx.ecx = static_cast<uint32_t>(0x0000005fu);
    // 0x004016e0: mov esi, ebx
    ctx.esi = static_cast<uint32_t>(ctx.ebx);
    // 0x004016e2: mov edi, 0x553fc0
    ctx.edi = static_cast<uint32_t>(0x00553fc0u);
    // 0x004016e7: push ebx
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, ctx.ebx);
    // 0x004016e8: rep movsd dword ptr es:[edi], dword ptr [esi]
    recomp_detail::exec_string_op<uint32_t>(ctx, mem, 0, 1);
    // 0x004016ea: mov dword ptr [0x554140], 0x553fc0
    mem.w32(0x00554140u, 0x00553fc0u);
    // 0x004016f4: call 0x4e00d0
    uint32_t t64 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    mem.w32(t64, 0x004016f9u);
    hle_crt_004e00d0(ctx, mem);
    // 0x004016f9: add esp, 4
    uint32_t t65 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t65);
    ctx.esp = static_cast<uint32_t>(t65);
    goto bb_004016fc;
}
bb_0040170f: {
    // 0x0040170f: pop edi
    uint32_t t66 = ctx.esp;
    uint32_t t67 = mem.r32(t66);
    uint32_t t68 = static_cast<uint32_t>(t66 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    ctx.edi = static_cast<uint32_t>(t67);
    // 0x00401710: pop esi
    uint32_t t69 = ctx.esp;
    uint32_t t70 = mem.r32(t69);
    uint32_t t71 = static_cast<uint32_t>(t69 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t71);
    ctx.esi = static_cast<uint32_t>(t70);
    // 0x00401711: pop ebp
    uint32_t t72 = ctx.esp;
    uint32_t t73 = mem.r32(t72);
    uint32_t t74 = static_cast<uint32_t>(t72 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    ctx.ebp = static_cast<uint32_t>(t73);
    // 0x00401712: pop ebx
    uint32_t t75 = ctx.esp;
    uint32_t t76 = mem.r32(t75);
    uint32_t t77 = static_cast<uint32_t>(t75 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    ctx.ebx = static_cast<uint32_t>(t76);
    // 0x00401713: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x00401715: pop ebp
    uint32_t t78 = ctx.esp;
    uint32_t t79 = mem.r32(t78);
    uint32_t t80 = static_cast<uint32_t>(t78 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    ctx.ebp = static_cast<uint32_t>(t79);
    // 0x00401716: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00401705: {
    // 0x00401705: mov eax, dword ptr [0x554140]
    uint32_t t81 = mem.r32(0x00554140u);
    ctx.eax = static_cast<uint32_t>(t81);
    // 0x0040170a: call 0x401490
    uint32_t t82 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t82);
    mem.w32(t82, 0x0040170fu);
    sub_00401490(ctx, mem);
    goto bb_0040170f;
}
}

// sub_00406680 | subsystem=Core/Windows | canonical | 9 blocks | 27 insns
void sub_00406680(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00406680: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x00406681: xor esi, esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esi = static_cast<uint32_t>(t1);
}
bb_00406683: {
    // 0x00406683: mov ecx, dword ptr [0x76e9a8]
    uint32_t t2 = mem.r32(0x0076e9a8u);
    ctx.ecx = static_cast<uint32_t>(t2);
    // 0x00406689: test ecx, ecx
    uint32_t t3 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t3);
    // 0x0040668b: je 0x4066c8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004066c8;
    goto bb_0040668d;
}
bb_004066c8: {
    // 0x004066c8: pop esi
    uint32_t t4 = ctx.esp;
    uint32_t t5 = mem.r32(t4);
    uint32_t t6 = static_cast<uint32_t>(t4 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    ctx.esi = static_cast<uint32_t>(t5);
    // 0x004066c9: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040668d: {
    // 0x0040668d: mov eax, dword ptr [0x76e9ac]
    uint32_t t7 = mem.r32(0x0076e9acu);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x00406692: sub eax, ecx
    uint32_t t8 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t8);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x00406694: sar eax, 2
    uint32_t t9 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t10 = recomp_detail::sar<uint32_t>(ctx.eax, t9);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.eax, t9, t10);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x00406697: cmp esi, eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t11);
    // 0x00406699: jae 0x4066c8
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004066c8;
}
{
    // 0x0040669b: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x0040669d: mov eax, dword ptr [eax + esi*4]
    uint32_t t12 = recomp_detail::shl<uint32_t>(ctx.esi, 0x00000002u);
    uint32_t t13 = static_cast<uint32_t>(ctx.eax + t12);
    uint32_t t14 = mem.r32(t13);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x004066a0: test eax, eax
    uint32_t t15 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t15);
    // 0x004066a2: je 0x4066c3
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004066c3;
    goto bb_004066a4;
}
bb_004066c3: {
    // 0x004066c3: add esi, 1
    uint32_t t16 = static_cast<uint32_t>(ctx.esi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000001u, t16);
    ctx.esi = static_cast<uint32_t>(t16);
    // 0x004066c6: jmp 0x406683
    goto bb_00406683;
}
bb_004066a4: {
    // 0x004066a4: cmp dword ptr [eax + 0x2c], 0
    uint32_t t17 = static_cast<uint32_t>(ctx.eax + 0x0000002cu);
    uint32_t t18 = mem.r32(t17);
    uint32_t t19 = static_cast<uint32_t>(t18 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t18, 0x00000000u, t19);
    // 0x004066a8: je 0x4066c3
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004066c3;
}
{
    // 0x004066aa: add dword ptr [eax + 0x28], 1
    uint32_t t20 = static_cast<uint32_t>(ctx.eax + 0x00000028u);
    uint32_t t21 = mem.r32(t20);
    uint32_t t22 = static_cast<uint32_t>(t21 + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t21, 0x00000001u, t22);
    mem.w32(t20, t22);
    // 0x004066ae: cmp dword ptr [eax + 0x28], 0x12c
    uint32_t t23 = static_cast<uint32_t>(ctx.eax + 0x00000028u);
    uint32_t t24 = mem.r32(t23);
    uint32_t t25 = static_cast<uint32_t>(t24 - 0x0000012cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t24, 0x0000012cu, t25);
    // 0x004066b5: jl 0x4066c3
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004066c3;
}
{
    // 0x004066b7: push esi
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, ctx.esi);
    // 0x004066b8: call 0x406590
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x004066bdu);
    sub_00406590(ctx, mem);
    // 0x004066bd: add esp, 4
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t28);
    ctx.esp = static_cast<uint32_t>(t28);
    // 0x004066c0: sub esi, 1
    uint32_t t29 = static_cast<uint32_t>(ctx.esi - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00000001u, t29);
    ctx.esi = static_cast<uint32_t>(t29);
    goto bb_004066c3;
}
}

// sub_0040c380 | subsystem=Core/Windows | canonical | 3 blocks | 24 insns
void sub_0040c380(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040c380: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x0040c381: push edi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.edi);
    // 0x0040c382: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0040c384: call 0x40c3d0
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x0040c389u);
    sub_0040c3d0(ctx, mem);
    // 0x0040c389: push 0x100
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x00000100u);
    // 0x0040c38e: lea edi, [esi + 0xc]
    uint32_t t4 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    ctx.edi = static_cast<uint32_t>(t4);
    // 0x0040c391: push 0
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, 0x00000000u);
    // 0x0040c393: push edi
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.edi);
    // 0x0040c394: call 0x4e6340
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0040c399u);
    hle_crt_004e6340(ctx, mem);
    // 0x0040c399: mov edx, edi
    ctx.edx = static_cast<uint32_t>(ctx.edi);
    // 0x0040c39b: add esp, 0xc
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t8);
    ctx.esp = static_cast<uint32_t>(t8);
    // 0x0040c39e: mov eax, ebx
    ctx.eax = static_cast<uint32_t>(ctx.ebx);
    // 0x0040c3a0: sub edx, ebx
    uint32_t t9 = static_cast<uint32_t>(ctx.edx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ebx, t9);
    ctx.edx = static_cast<uint32_t>(t9);
}
bb_0040c3a2: {
    // 0x0040c3a2: mov cl, byte ptr [eax]
    uint8_t t10 = mem.r8(ctx.eax);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t10));
    // 0x0040c3a4: mov byte ptr [edx + eax], cl
    uint32_t t11 = static_cast<uint32_t>(ctx.edx + ctx.eax);
    mem.w8(t11, recomp_detail::r8l(ctx.ecx));
    // 0x0040c3a7: add eax, 1
    uint32_t t12 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t12);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0040c3aa: test cl, cl
    uint8_t t13 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t13);
    // 0x0040c3ac: jne 0x40c3a2
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040c3a2;
}
{
    // 0x0040c3ae: pop edi
    uint32_t t14 = ctx.esp;
    uint32_t t15 = mem.r32(t14);
    uint32_t t16 = static_cast<uint32_t>(t14 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    ctx.edi = static_cast<uint32_t>(t15);
    // 0x0040c3af: mov dword ptr [esi + 8], 0
    uint32_t t17 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t17, 0x00000000u);
    // 0x0040c3b6: mov dword ptr [esi], 1
    mem.w32(ctx.esi, 0x00000001u);
    // 0x0040c3bc: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0040c3c1: pop esi
    uint32_t t18 = ctx.esp;
    uint32_t t19 = mem.r32(t18);
    uint32_t t20 = static_cast<uint32_t>(t18 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    ctx.esi = static_cast<uint32_t>(t19);
    // 0x0040c3c2: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0040c8c0 | subsystem=Core/Windows | canonical | 4 blocks | 37 insns
void sub_0040c8c0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040c8c0: sub esp, 0x24
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000024u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000024u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x0040c8c3: mov eax, dword ptr [0x54b458]
    uint32_t t1 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x0040c8c8: xor eax, esp
    uint32_t t2 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x0040c8ca: mov dword ptr [esp + 0x20], eax
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t3, ctx.eax);
    // 0x0040c8ce: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x0040c8cf: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x0040c8d1: cmp dword ptr [esi], 1
    uint32_t t5 = mem.r32(ctx.esi);
    uint32_t t6 = static_cast<uint32_t>(t5 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t5, 0x00000001u, t6);
    // 0x0040c8d4: je 0x40c8ea
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040c8ea;
    goto bb_0040c8d6;
}
bb_0040c8ea: {
    // 0x0040c8ea: mov eax, dword ptr [esp + 0x2c]
    uint32_t t7 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    uint32_t t8 = mem.r32(t7);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x0040c8ee: push eax
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.eax);
    // 0x0040c8ef: lea ecx, [esp + 8]
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.ecx = static_cast<uint32_t>(t10);
    // 0x0040c8f3: push 0x5351b0
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0x005351b0u);
    // 0x0040c8f8: push ecx
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.ecx);
    // 0x0040c8f9: call 0x4e068b
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x0040c8feu);
    hle_crt_004e068b(ctx, mem);
    // 0x0040c8fe: add esp, 0xc
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t14);
    ctx.esp = static_cast<uint32_t>(t14);
    // 0x0040c901: cmp dword ptr [esi], 1
    uint32_t t15 = mem.r32(ctx.esi);
    uint32_t t16 = static_cast<uint32_t>(t15 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t15, 0x00000001u, t16);
    // 0x0040c904: jne 0x40c8d6
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040c8d6;
    goto bb_0040c906;
}
bb_0040c8d6: {
    // 0x0040c8d6: xor eax, eax
    uint32_t t17 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t17);
    ctx.eax = static_cast<uint32_t>(t17);
    // 0x0040c8d8: pop esi
    uint32_t t18 = ctx.esp;
    uint32_t t19 = mem.r32(t18);
    uint32_t t20 = static_cast<uint32_t>(t18 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    ctx.esi = static_cast<uint32_t>(t19);
    // 0x0040c8d9: mov ecx, dword ptr [esp + 0x20]
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t22 = mem.r32(t21);
    ctx.ecx = static_cast<uint32_t>(t22);
    // 0x0040c8dd: xor ecx, esp
    uint32_t t23 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t23);
    ctx.ecx = static_cast<uint32_t>(t23);
    // 0x0040c8df: call 0x4e02f8
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x0040c8e4u);
    hle_crt_004e02f8(ctx, mem);
    // 0x0040c8e4: add esp, 0x24
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000024u, t25);
    ctx.esp = static_cast<uint32_t>(t25);
    // 0x0040c8e7: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0040c906: {
    // 0x0040c906: add esi, 0xc
    uint32_t t26 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x0000000cu, t26);
    ctx.esi = static_cast<uint32_t>(t26);
    // 0x0040c909: push esi
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, ctx.esi);
    // 0x0040c90a: lea edx, [esp + 8]
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.edx = static_cast<uint32_t>(t28);
    // 0x0040c90e: push edx
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, ctx.edx);
    // 0x0040c90f: push ebx
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, ctx.ebx);
    // 0x0040c910: push edi
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, ctx.edi);
    // 0x0040c911: call dword ptr [0x51b02c]
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x0040c917u);
    hle_iat_call(ctx, mem, 0x0051b02cu);
    // 0x0040c917: mov ecx, dword ptr [esp + 0x24]
    uint32_t t33 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t34 = mem.r32(t33);
    ctx.ecx = static_cast<uint32_t>(t34);
    // 0x0040c91b: pop esi
    uint32_t t35 = ctx.esp;
    uint32_t t36 = mem.r32(t35);
    uint32_t t37 = static_cast<uint32_t>(t35 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    ctx.esi = static_cast<uint32_t>(t36);
    // 0x0040c91c: xor ecx, esp
    uint32_t t38 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t38);
    ctx.ecx = static_cast<uint32_t>(t38);
    // 0x0040c91e: call 0x4e02f8
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, 0x0040c923u);
    hle_crt_004e02f8(ctx, mem);
    // 0x0040c923: add esp, 0x24
    uint32_t t40 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000024u, t40);
    ctx.esp = static_cast<uint32_t>(t40);
    // 0x0040c926: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
}

// sub_0040d240 | subsystem=Core/Windows | canonical | 3 blocks | 31 insns
void sub_0040d240(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040d240: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x0040d241: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x0040d243: and esp, 0xfffffff8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xfffffff8u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x0040d246: sub esp, 0x28
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000028u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000028u, t2);
    ctx.esp = static_cast<uint32_t>(t2);
    // 0x0040d249: call 0x4e10aa
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x0040d24eu);
    hle_crt_004e10aa(ctx, mem);
    // 0x0040d24e: mov dword ptr [0x76e65c], eax
    mem.w32(0x0076e65cu, ctx.eax);
    // 0x0040d253: call 0x40d470
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x0040d258u);
    sub_0040d470(ctx, mem);
    // 0x0040d258: test eax, eax
    uint32_t t5 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    // 0x0040d25a: jne 0x40d262
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040d262;
    goto bb_0040d25c;
}
bb_0040d262: {
    // 0x0040d262: mov eax, dword ptr [ebp + 8]
    uint32_t t6 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t7 = mem.r32(t6);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0040d265: mov ecx, dword ptr [ebp + 0x14]
    uint32_t t8 = static_cast<uint32_t>(ctx.ebp + 0x00000014u);
    uint32_t t9 = mem.r32(t8);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0040d268: mov dword ptr [esp], eax
    mem.w32(ctx.esp, ctx.eax);
    // 0x0040d26b: xor eax, eax
    uint32_t t10 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0040d26d: mov dword ptr [esp + 4], ecx
    uint32_t t11 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    mem.w32(t11, ctx.ecx);
    // 0x0040d271: mov dword ptr [esp + 8], eax
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    mem.w32(t12, ctx.eax);
    // 0x0040d275: mov dword ptr [esp + 0xc], eax
    uint32_t t13 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t13, ctx.eax);
    // 0x0040d279: mov dword ptr [esp + 0x10], eax
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t14, ctx.eax);
    // 0x0040d27d: mov dword ptr [esp + 0x14], eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t15, ctx.eax);
    // 0x0040d281: mov dword ptr [esp + 0x18], eax
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t16, ctx.eax);
    // 0x0040d285: mov dword ptr [esp + 0x1c], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t17, ctx.eax);
    // 0x0040d289: mov dword ptr [esp + 0x20], eax
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t18, ctx.eax);
    // 0x0040d28d: mov eax, dword ptr [ebp + 0x10]
    uint32_t t19 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    uint32_t t20 = mem.r32(t19);
    ctx.eax = static_cast<uint32_t>(t20);
    // 0x0040d290: lea ecx, [esp]
    ctx.ecx = static_cast<uint32_t>(ctx.esp);
    // 0x0040d293: mov dword ptr [esp + 0x24], 0x5541c4
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t21, 0x005541c4u);
    // 0x0040d29b: call 0x401770
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x0040d2a0u);
    sub_00401770(ctx, mem);
    // 0x0040d2a0: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0040d2a2: pop ebp
    uint32_t t23 = ctx.esp;
    uint32_t t24 = mem.r32(t23);
    uint32_t t25 = static_cast<uint32_t>(t23 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    ctx.ebp = static_cast<uint32_t>(t24);
    // 0x0040d2a3: ret 0x10
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 16u;
    return;
}
bb_0040d25c: {
    // 0x0040d25c: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0040d25e: pop ebp
    uint32_t t26 = ctx.esp;
    uint32_t t27 = mem.r32(t26);
    uint32_t t28 = static_cast<uint32_t>(t26 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    ctx.ebp = static_cast<uint32_t>(t27);
    // 0x0040d25f: ret 0x10
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 16u;
    return;
}
}

// sub_0040d2b0 | subsystem=Core/Windows | canonical | 4 blocks | 30 insns
void sub_0040d2b0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040d2b0: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x0040d2b1: mov esi, dword ptr [edi]
    uint32_t t1 = mem.r32(ctx.edi);
    ctx.esi = static_cast<uint32_t>(t1);
    // 0x0040d2b3: call 0x40d380
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x0040d2b8u);
    sub_0040d380(ctx, mem);
    // 0x0040d2b8: mov eax, dword ptr [edi + 4]
    uint32_t t3 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    uint32_t t4 = mem.r32(t3);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0040d2bb: push eax
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.eax);
    // 0x0040d2bc: mov eax, dword ptr [edi]
    uint32_t t6 = mem.r32(ctx.edi);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0040d2be: call 0x40d420
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0040d2c3u);
    sub_0040d420(ctx, mem);
    // 0x0040d2c3: add esp, 4
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t8);
    ctx.esp = static_cast<uint32_t>(t8);
    // 0x0040d2c6: test eax, eax
    uint32_t t9 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    // 0x0040d2c8: jne 0x40d2ce
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040d2ce;
    goto bb_0040d2ca;
}
bb_0040d2ce: {
    // 0x0040d2ce: mov ecx, dword ptr [0x5541c4]
    uint32_t t10 = mem.r32(0x005541c4u);
    ctx.ecx = static_cast<uint32_t>(t10);
    // 0x0040d2d4: push ecx
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.ecx);
    // 0x0040d2d5: call 0x4de350
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x0040d2dau);
    sub_004de350(ctx, mem);
    // 0x0040d2da: sub eax, 1
    uint32_t t13 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t13);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0040d2dd: add esp, 4
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t14);
    ctx.esp = static_cast<uint32_t>(t14);
    // 0x0040d2e0: neg eax
    uint32_t t15 = static_cast<uint32_t>(0u - ctx.eax);
    recomp_detail::update_flags_neg<uint32_t>(ctx, ctx.eax, t15);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x0040d2e2: sbb eax, eax
    uint32_t t16 = recomp_detail::get_flag(ctx, kFlagCF);
    uint32_t t17 = static_cast<uint32_t>(ctx.eax - ctx.eax);
    uint32_t t18 = static_cast<uint32_t>(t17 - t16);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.eax, t18, t16);
    ctx.eax = static_cast<uint32_t>(t18);
    // 0x0040d2e4: inc eax
    uint32_t t19 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_inc<uint32_t>(ctx, ctx.eax, t19);
    ctx.eax = static_cast<uint32_t>(t19);
    // 0x0040d2e5: mov dword ptr [0x54c798], eax
    mem.w32(0x0054c798u, ctx.eax);
    // 0x0040d2ea: jmp 0x40d2f3
    goto bb_0040d2f3;
}
bb_0040d2ca: {
    // 0x0040d2ca: xor al, al
    uint8_t t20 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) ^ static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t20);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t20));
    // 0x0040d2cc: pop esi
    uint32_t t21 = ctx.esp;
    uint32_t t22 = mem.r32(t21);
    uint32_t t23 = static_cast<uint32_t>(t21 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    ctx.esi = static_cast<uint32_t>(t22);
    // 0x0040d2cd: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040d2f3: {
    // 0x0040d2f3: push 2
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x00000002u);
    // 0x0040d2f5: push 0
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x00000000u);
    // 0x0040d2f7: call dword ptr [0x51b408]
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x0040d2fdu);
    hle_iat_call(ctx, mem, 0x0051b408u);
    // 0x0040d2fd: mov dword ptr [0x5542c8], eax
    mem.w32(0x005542c8u, ctx.eax);
    // 0x0040d302: mov al, 1
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(uint8_t{0x01u}));
    // 0x0040d304: pop esi
    uint32_t t27 = ctx.esp;
    uint32_t t28 = mem.r32(t27);
    uint32_t t29 = static_cast<uint32_t>(t27 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    ctx.esi = static_cast<uint32_t>(t28);
    // 0x0040d305: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0040d310 | subsystem=Core/Windows | canonical | 8 blocks | 42 insns
void sub_0040d310(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040d310: push ebx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebx);
    // 0x0040d311: mov ebx, dword ptr [0x51b29c]
    uint32_t t1 = mem.r32(0x0051b29cu);
    ctx.ebx = static_cast<uint32_t>(t1);
    // 0x0040d317: push ebp
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebp);
    // 0x0040d318: mov ebp, dword ptr [0x51b2e4]
    uint32_t t3 = mem.r32(0x0051b2e4u);
    ctx.ebp = static_cast<uint32_t>(t3);
    // 0x0040d31e: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x0040d31f: mov esi, dword ptr [esp + 0x10]
    uint32_t t5 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t6 = mem.r32(t5);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x0040d323: push edi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.edi);
    // 0x0040d324: mov edi, dword ptr [0x51b238]
    uint32_t t8 = mem.r32(0x0051b238u);
    ctx.edi = static_cast<uint32_t>(t8);
    // 0x0040d32a: add esi, 8
    uint32_t t9 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000008u, t9);
    ctx.esi = static_cast<uint32_t>(t9);
    // 0x0040d32d: lea ecx, [ecx]
    ctx.ecx = static_cast<uint32_t>(ctx.ecx);
}
bb_0040d330: {
    // 0x0040d330: push 1
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x00000001u);
    // 0x0040d332: push 0
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0x00000000u);
    // 0x0040d334: push 0
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x00000000u);
    // 0x0040d336: push 0
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x00000000u);
    // 0x0040d338: push esi
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, ctx.esi);
    // 0x0040d339: call edi
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x0040d33bu);
    call_indirect(ctx, mem, ctx.edi);
    // 0x0040d33b: test eax, eax
    uint32_t t16 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    // 0x0040d33d: je 0x40d347
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040d347;
    goto bb_0040d33f;
}
bb_0040d347: {
    // 0x0040d347: cmp byte ptr [0x76e650], 0
    uint8_t t17 = mem.r8(0x0076e650u);
    uint8_t t18 = static_cast<uint8_t>(static_cast<uint32_t>(t17) - static_cast<uint32_t>(uint8_t{0x00u}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, t17, uint8_t{0x00u}, t18);
    // 0x0040d34e: je 0x40d364
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040d364;
    goto bb_0040d350;
}
bb_0040d33f: {
    // 0x0040d33f: push esi
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, ctx.esi);
    // 0x0040d340: call ebx
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x0040d342u);
    call_indirect(ctx, mem, ctx.ebx);
    // 0x0040d342: push esi
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, ctx.esi);
    // 0x0040d343: call ebp
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x0040d345u);
    call_indirect(ctx, mem, ctx.ebp);
    // 0x0040d345: jmp 0x40d370
    goto bb_0040d370;
}
bb_0040d364: {
    // 0x0040d364: mov eax, dword ptr [0x5541c4]
    uint32_t t23 = mem.r32(0x005541c4u);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x0040d369: push eax
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, ctx.eax);
    // 0x0040d36a: call dword ptr [0x51b22c]
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x0040d370u);
    hle_iat_call(ctx, mem, 0x0051b22cu);
    goto bb_0040d370;
}
bb_0040d350: {
    // 0x0040d350: call 0x40e390
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x0040d355u);
    sub_0040e390(ctx, mem);
    // 0x0040d355: cmp eax, 1
    uint32_t t27 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t27);
    // 0x0040d358: sete al
    uint8_t t28 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::E) ? 1u : 0u);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t28));
    // 0x0040d35b: test al, al
    uint8_t t29 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t29);
    // 0x0040d35d: mov byte ptr [0x76e650], al
    mem.w8(0x0076e650u, recomp_detail::r8l(ctx.eax));
    // 0x0040d362: jne 0x40d370
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040d370;
    goto bb_0040d364;
}
bb_0040d370: {
    // 0x0040d370: mov ecx, dword ptr [esp + 0x14]
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t31 = mem.r32(t30);
    ctx.ecx = static_cast<uint32_t>(t31);
    // 0x0040d374: cmp dword ptr [ecx + 0xc], 0x12
    uint32_t t32 = static_cast<uint32_t>(ctx.ecx + 0x0000000cu);
    uint32_t t33 = mem.r32(t32);
    uint32_t t34 = static_cast<uint32_t>(t33 - 0x00000012u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t33, 0x00000012u, t34);
    // 0x0040d378: jne 0x40d330
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040d330;
}
{
    // 0x0040d37a: pop edi
    uint32_t t35 = ctx.esp;
    uint32_t t36 = mem.r32(t35);
    uint32_t t37 = static_cast<uint32_t>(t35 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    ctx.edi = static_cast<uint32_t>(t36);
    // 0x0040d37b: pop esi
    uint32_t t38 = ctx.esp;
    uint32_t t39 = mem.r32(t38);
    uint32_t t40 = static_cast<uint32_t>(t38 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    ctx.esi = static_cast<uint32_t>(t39);
    // 0x0040d37c: pop ebp
    uint32_t t41 = ctx.esp;
    uint32_t t42 = mem.r32(t41);
    uint32_t t43 = static_cast<uint32_t>(t41 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    ctx.ebp = static_cast<uint32_t>(t42);
    // 0x0040d37d: pop ebx
    uint32_t t44 = ctx.esp;
    uint32_t t45 = mem.r32(t44);
    uint32_t t46 = static_cast<uint32_t>(t44 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    ctx.ebx = static_cast<uint32_t>(t45);
    // 0x0040d37e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0040d380 | subsystem=Core/Windows | canonical | 1 blocks | 33 insns
void sub_0040d380(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040d380: sub esp, 0x38
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000038u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000038u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x0040d383: push edi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.edi);
    // 0x0040d384: mov edi, dword ptr [0x51b2e0]
    uint32_t t2 = mem.r32(0x0051b2e0u);
    ctx.edi = static_cast<uint32_t>(t2);
    // 0x0040d38a: push 0x85
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x00000085u);
    // 0x0040d38f: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x0040d390: mov dword ptr [0x5542cc], esi
    mem.w32(0x005542ccu, ctx.esi);
    // 0x0040d396: mov dword ptr [esp + 0x10], 0x30
    uint32_t t5 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t5, 0x00000030u);
    // 0x0040d39e: mov dword ptr [esp + 0x14], 3
    uint32_t t6 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t6, 0x00000003u);
    // 0x0040d3a6: mov dword ptr [esp + 0x18], 0x40d4c0
    uint32_t t7 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t7, 0x0040d4c0u);
    // 0x0040d3ae: mov dword ptr [esp + 0x1c], 0
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t8, 0x00000000u);
    // 0x0040d3b6: mov dword ptr [esp + 0x20], 0
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t9, 0x00000000u);
    // 0x0040d3be: mov dword ptr [esp + 0x24], esi
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t10, ctx.esi);
    // 0x0040d3c2: call edi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0x0040d3c4u);
    call_indirect(ctx, mem, ctx.edi);
    // 0x0040d3c4: push 0x7f00
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x00007f00u);
    // 0x0040d3c9: push 0
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x00000000u);
    // 0x0040d3cb: mov dword ptr [esp + 0x28], eax
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t14, ctx.eax);
    // 0x0040d3cf: call dword ptr [0x51b2e8]
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x0040d3d5u);
    hle_iat_call(ctx, mem, 0x0051b2e8u);
    // 0x0040d3d5: push 4
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x00000004u);
    // 0x0040d3d7: mov dword ptr [esp + 0x28], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t17, ctx.eax);
    // 0x0040d3db: call dword ptr [0x51b024]
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x0040d3e1u);
    hle_iat_call(ctx, mem, 0x0051b024u);
    // 0x0040d3e1: push 0x85
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x00000085u);
    // 0x0040d3e6: push esi
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, ctx.esi);
    // 0x0040d3e7: mov dword ptr [esp + 0x30], eax
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    mem.w32(t21, ctx.eax);
    // 0x0040d3eb: mov dword ptr [esp + 0x34], 0
    uint32_t t22 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    mem.w32(t22, 0x00000000u);
    // 0x0040d3f3: mov dword ptr [esp + 0x38], 0x5351c4
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    mem.w32(t23, 0x005351c4u);
    // 0x0040d3fb: call edi
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x0040d3fdu);
    call_indirect(ctx, mem, ctx.edi);
    // 0x0040d3fd: mov dword ptr [esp + 0x34], eax
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    mem.w32(t25, ctx.eax);
    // 0x0040d401: lea eax, [esp + 8]
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.eax = static_cast<uint32_t>(t26);
    // 0x0040d405: push eax
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, ctx.eax);
    // 0x0040d406: call dword ptr [0x51b21c]
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x0040d40cu);
    hle_iat_call(ctx, mem, 0x0051b21cu);
    // 0x0040d40c: pop edi
    uint32_t t29 = ctx.esp;
    uint32_t t30 = mem.r32(t29);
    uint32_t t31 = static_cast<uint32_t>(t29 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    ctx.edi = static_cast<uint32_t>(t30);
    // 0x0040d40d: add esp, 0x38
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000038u, t32);
    ctx.esp = static_cast<uint32_t>(t32);
    // 0x0040d410: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0040d420 | subsystem=Core/Windows | canonical | 3 blocks | 29 insns
void sub_0040d420(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040d420: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x0040d421: push 0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00000000u);
    // 0x0040d423: push eax
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.eax);
    // 0x0040d424: push 0
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x00000000u);
    // 0x0040d426: push 0
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x00000000u);
    // 0x0040d428: push 0
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, 0x00000000u);
    // 0x0040d42a: push 0
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x00000000u);
    // 0x0040d42c: push 0
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x00000000u);
    // 0x0040d42e: push 0
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x00000000u);
    // 0x0040d430: push 0x90c80000
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x90c80000u);
    // 0x0040d435: push 0x5351f4
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x005351f4u);
    // 0x0040d43a: push 0x5351c4
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0x005351c4u);
    // 0x0040d43f: push 0
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x00000000u);
    // 0x0040d441: call dword ptr [0x51b30c]
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x0040d447u);
    hle_iat_call(ctx, mem, 0x0051b30cu);
    // 0x0040d447: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0040d449: test esi, esi
    uint32_t t14 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    // 0x0040d44b: jne 0x40d44f
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040d44f;
    goto bb_0040d44d;
}
bb_0040d44f: {
    // 0x0040d44f: mov ecx, dword ptr [esp + 8]
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t16 = mem.r32(t15);
    ctx.ecx = static_cast<uint32_t>(t16);
    // 0x0040d453: push ecx
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, ctx.ecx);
    // 0x0040d454: push esi
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, ctx.esi);
    // 0x0040d455: mov dword ptr [0x5541c4], esi
    mem.w32(0x005541c4u, ctx.esi);
    // 0x0040d45b: call dword ptr [0x51b23c]
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x0040d461u);
    hle_iat_call(ctx, mem, 0x0051b23cu);
    // 0x0040d461: push esi
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, ctx.esi);
    // 0x0040d462: call dword ptr [0x51b2ac]
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x0040d468u);
    hle_iat_call(ctx, mem, 0x0051b2acu);
    // 0x0040d468: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0040d46d: pop esi
    uint32_t t22 = ctx.esp;
    uint32_t t23 = mem.r32(t22);
    uint32_t t24 = static_cast<uint32_t>(t22 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    ctx.esi = static_cast<uint32_t>(t23);
    // 0x0040d46e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040d44d: {
    // 0x0040d44d: pop esi
    uint32_t t25 = ctx.esp;
    uint32_t t26 = mem.r32(t25);
    uint32_t t27 = static_cast<uint32_t>(t25 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    ctx.esi = static_cast<uint32_t>(t26);
    // 0x0040d44e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0040d470 | subsystem=Core/Windows | canonical | 5 blocks | 26 insns
void sub_0040d470(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040d470: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x0040d471: push 0x5351c4
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005351c4u);
    // 0x0040d476: push 1
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x00000001u);
    // 0x0040d478: push 0
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x00000000u);
    // 0x0040d47a: call dword ptr [0x51b038]
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x0040d480u);
    hle_iat_call(ctx, mem, 0x0051b038u);
    // 0x0040d480: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0040d482: call dword ptr [0x51b030]
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, 0x0040d488u);
    hle_iat_call(ctx, mem, 0x0051b030u);
    // 0x0040d488: cmp eax, 0xb7
    uint32_t t6 = static_cast<uint32_t>(ctx.eax - 0x000000b7u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x000000b7u, t6);
    // 0x0040d48d: jne 0x40d4b2
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040d4b2;
    goto bb_0040d48f;
}
bb_0040d4b2: {
    // 0x0040d4b2: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x0040d4b3: call dword ptr [0x51b034]
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x0040d4b9u);
    hle_iat_call(ctx, mem, 0x0051b034u);
    // 0x0040d4b9: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0040d4be: pop esi
    uint32_t t9 = ctx.esp;
    uint32_t t10 = mem.r32(t9);
    uint32_t t11 = static_cast<uint32_t>(t9 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    ctx.esi = static_cast<uint32_t>(t10);
    // 0x0040d4bf: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040d48f: {
    // 0x0040d48f: push 0
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x00000000u);
    // 0x0040d491: push 0x5351c4
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x005351c4u);
    // 0x0040d496: call dword ptr [0x51b2c4]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x0040d49cu);
    hle_iat_call(ctx, mem, 0x0051b2c4u);
    // 0x0040d49c: test eax, eax
    uint32_t t15 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t15);
    // 0x0040d49e: je 0x40d4ae
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040d4ae;
    goto bb_0040d4a0;
}
bb_0040d4ae: {
    // 0x0040d4ae: xor eax, eax
    uint32_t t16 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0040d4b0: pop esi
    uint32_t t17 = ctx.esp;
    uint32_t t18 = mem.r32(t17);
    uint32_t t19 = static_cast<uint32_t>(t17 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    ctx.esi = static_cast<uint32_t>(t18);
    // 0x0040d4b1: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040d4a0: {
    // 0x0040d4a0: push eax
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, ctx.eax);
    // 0x0040d4a1: call dword ptr [0x51b230]
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x0040d4a7u);
    hle_iat_call(ctx, mem, 0x0051b230u);
    // 0x0040d4a7: push eax
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, ctx.eax);
    // 0x0040d4a8: call dword ptr [0x51b298]
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x0040d4aeu);
    hle_iat_call(ctx, mem, 0x0051b298u);
    goto bb_0040d4ae;
}
}

// sub_0040d4c0 | subsystem=Core/Windows | canonical | 29 blocks | 337 insns
void sub_0040d4c0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040d4c0: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x0040d4c1: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x0040d4c3: and esp, 0xffffffc0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xffffffc0u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x0040d4c6: sub esp, 0x178
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000178u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000178u, t2);
    ctx.esp = static_cast<uint32_t>(t2);
    // 0x0040d4cc: mov eax, dword ptr [0x54b458]
    uint32_t t3 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0040d4d1: xor eax, esp
    uint32_t t4 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0040d4d3: mov dword ptr [esp + 0x174], eax
    uint32_t t5 = static_cast<uint32_t>(ctx.esp + 0x00000174u);
    mem.w32(t5, ctx.eax);
    // 0x0040d4da: mov eax, dword ptr [ebp + 0xc]
    uint32_t t6 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t7 = mem.r32(t6);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0040d4dd: cmp eax, 0x104
    uint32_t t8 = static_cast<uint32_t>(ctx.eax - 0x00000104u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000104u, t8);
    // 0x0040d4e2: push esi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.esi);
    // 0x0040d4e3: push edi
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.edi);
    // 0x0040d4e4: mov edi, dword ptr [ebp + 8]
    uint32_t t11 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t12 = mem.r32(t11);
    ctx.edi = static_cast<uint32_t>(t12);
    // 0x0040d4e7: ja 0x40d66c
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_0040d66c;
    goto bb_0040d4ed;
}
bb_0040d66c: {
    // 0x0040d66c: cmp eax, 0x401
    uint32_t t13 = static_cast<uint32_t>(ctx.eax - 0x00000401u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000401u, t13);
    // 0x0040d671: ja 0x40d88a
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_0040d88a;
    goto bb_0040d677;
}
bb_0040d4ed: {
    // 0x0040d4ed: je 0x40d62f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040d62f;
    goto bb_0040d4f3;
}
bb_0040d88a: {
    // 0x0040d88a: cmp eax, 0x402
    uint32_t t14 = static_cast<uint32_t>(ctx.eax - 0x00000402u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000402u, t14);
    // 0x0040d88f: je 0x40d8e3
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040d8e3;
    goto bb_0040d891;
}
bb_0040d677: {
    // 0x0040d677: je 0x40d8f3
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040d8f3;
    goto bb_0040d67d;
}
bb_0040d62f: {
    // 0x0040d62f: cmp dword ptr [ebp + 0x10], 0xd
    uint32_t t15 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    uint32_t t16 = mem.r32(t15);
    uint32_t t17 = static_cast<uint32_t>(t16 - 0x0000000du);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t16, 0x0000000du, t17);
    // 0x0040d633: jne 0x40d8f3
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040d8f3;
    goto bb_0040d639;
}
bb_0040d4f3: {
    // 0x0040d4f3: lea ecx, [eax - 1]
    uint32_t t18 = static_cast<uint32_t>(ctx.eax + 0xffffffffu);
    ctx.ecx = static_cast<uint32_t>(t18);
    // 0x0040d4f6: cmp ecx, 0xf
    uint32_t t19 = static_cast<uint32_t>(ctx.ecx - 0x0000000fu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x0000000fu, t19);
    // 0x0040d4f9: ja 0x40d898
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_0040d898;
    goto bb_0040d4ff;
}
bb_0040d8e3: {
    // 0x0040d8e3: fldz
    ctx.fpu_push(0.0);
    // 0x0040d8e5: sub esp, 8
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000008u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000008u, t20);
    ctx.esp = static_cast<uint32_t>(t20);
    // 0x0040d8e8: fstp qword ptr [esp]
    double t21 = ctx.fpu_st(0);
    mem.wf64(ctx.esp, t21);
    ctx.fpu_pop();
    // 0x0040d8eb: call 0x4136b0
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x0040d8f0u);
    sub_004136b0(ctx, mem);
    // 0x0040d8f0: add esp, 8
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t23);
    ctx.esp = static_cast<uint32_t>(t23);
    goto bb_0040d8f3;
}
bb_0040d891: {
    // 0x0040d891: cmp eax, 0x8001
    uint32_t t24 = static_cast<uint32_t>(ctx.eax - 0x00008001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00008001u, t24);
    // 0x0040d896: je 0x40d8be
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040d8be;
    goto bb_0040d898;
}
bb_0040d8f3: {
    // 0x0040d8f3: mov ecx, dword ptr [esp + 0x17c]
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x0000017cu);
    uint32_t t26 = mem.r32(t25);
    ctx.ecx = static_cast<uint32_t>(t26);
    // 0x0040d8fa: pop edi
    uint32_t t27 = ctx.esp;
    uint32_t t28 = mem.r32(t27);
    uint32_t t29 = static_cast<uint32_t>(t27 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    ctx.edi = static_cast<uint32_t>(t28);
    // 0x0040d8fb: pop esi
    uint32_t t30 = ctx.esp;
    uint32_t t31 = mem.r32(t30);
    uint32_t t32 = static_cast<uint32_t>(t30 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    ctx.esi = static_cast<uint32_t>(t31);
    // 0x0040d8fc: xor ecx, esp
    uint32_t t33 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t33);
    ctx.ecx = static_cast<uint32_t>(t33);
    // 0x0040d8fe: xor eax, eax
    uint32_t t34 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t34);
    ctx.eax = static_cast<uint32_t>(t34);
    // 0x0040d900: call 0x4e02f8
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, 0x0040d905u);
    hle_crt_004e02f8(ctx, mem);
    // 0x0040d905: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0040d907: pop ebp
    uint32_t t36 = ctx.esp;
    uint32_t t37 = mem.r32(t36);
    uint32_t t38 = static_cast<uint32_t>(t36 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    ctx.ebp = static_cast<uint32_t>(t37);
    // 0x0040d908: ret 0x10
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 16u;
    return;
}
bb_0040d67d: {
    // 0x0040d67d: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x0040d67f: sub ecx, 0x111
    uint32_t t39 = static_cast<uint32_t>(ctx.ecx - 0x00000111u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000111u, t39);
    ctx.ecx = static_cast<uint32_t>(t39);
    // 0x0040d685: je 0x40d6d0
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040d6d0;
    goto bb_0040d687;
}
bb_0040d639: {
    // 0x0040d639: push 0x12
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, 0x00000012u);
    // 0x0040d63b: call dword ptr [0x51b228]
    uint32_t t41 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    mem.w32(t41, 0x0040d641u);
    hle_iat_call(ctx, mem, 0x0051b228u);
    // 0x0040d641: test ax, ax
    uint16_t t42 = static_cast<uint16_t>(static_cast<uint32_t>(recomp_detail::r16(ctx.eax)) & static_cast<uint32_t>(recomp_detail::r16(ctx.eax)));
    recomp_detail::update_flags_logic<uint16_t>(ctx, t42);
    // 0x0040d644: jge 0x40d8f3
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0040d8f3;
    goto bb_0040d64a;
}
bb_0040d898: {
    // 0x0040d898: mov ecx, dword ptr [ebp + 0x14]
    uint32_t t43 = static_cast<uint32_t>(ctx.ebp + 0x00000014u);
    uint32_t t44 = mem.r32(t43);
    ctx.ecx = static_cast<uint32_t>(t44);
    // 0x0040d89b: mov edx, dword ptr [ebp + 0x10]
    uint32_t t45 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    uint32_t t46 = mem.r32(t45);
    ctx.edx = static_cast<uint32_t>(t46);
    // 0x0040d89e: push ecx
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, ctx.ecx);
    // 0x0040d89f: push edx
    uint32_t t48 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    mem.w32(t48, ctx.edx);
    // 0x0040d8a0: push eax
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, ctx.eax);
    // 0x0040d8a1: push edi
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, ctx.edi);
    // 0x0040d8a2: call dword ptr [0x51b2a4]
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, 0x0040d8a8u);
    hle_iat_call(ctx, mem, 0x0051b2a4u);
    // 0x0040d8a8: pop edi
    uint32_t t52 = ctx.esp;
    uint32_t t53 = mem.r32(t52);
    uint32_t t54 = static_cast<uint32_t>(t52 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    ctx.edi = static_cast<uint32_t>(t53);
    // 0x0040d8a9: pop esi
    uint32_t t55 = ctx.esp;
    uint32_t t56 = mem.r32(t55);
    uint32_t t57 = static_cast<uint32_t>(t55 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    ctx.esi = static_cast<uint32_t>(t56);
    // 0x0040d8aa: mov ecx, dword ptr [esp + 0x174]
    uint32_t t58 = static_cast<uint32_t>(ctx.esp + 0x00000174u);
    uint32_t t59 = mem.r32(t58);
    ctx.ecx = static_cast<uint32_t>(t59);
    // 0x0040d8b1: xor ecx, esp
    uint32_t t60 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t60);
    ctx.ecx = static_cast<uint32_t>(t60);
    // 0x0040d8b3: call 0x4e02f8
    uint32_t t61 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    mem.w32(t61, 0x0040d8b8u);
    hle_crt_004e02f8(ctx, mem);
    // 0x0040d8b8: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0040d8ba: pop ebp
    uint32_t t62 = ctx.esp;
    uint32_t t63 = mem.r32(t62);
    uint32_t t64 = static_cast<uint32_t>(t62 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    ctx.ebp = static_cast<uint32_t>(t63);
    // 0x0040d8bb: ret 0x10
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 16u;
    return;
}
bb_0040d4ff: {
    // 0x0040d4ff: movzx ecx, byte ptr [ecx + 0x40d924]
    uint32_t t65 = static_cast<uint32_t>(ctx.ecx + 0x0040d924u);
    uint8_t t66 = mem.r8(t65);
    uint32_t t67 = static_cast<uint32_t>(static_cast<uint8_t>(t66));
    ctx.ecx = static_cast<uint32_t>(t67);
    // 0x0040d506: jmp dword ptr [ecx*4 + 0x40d90c]
    switch (ctx.ecx) {
        case 0u: goto bb_0040d50d;
        case 1u: goto bb_0040d5f8;
        case 2u: goto bb_0040d58a;
        case 3u: goto bb_0040d5a9;
        case 4u: goto bb_0040d5d9;
        case 5u: goto bb_0040d898;
        default: recomp_detail::trap_halt(ctx, 0x0040d90cu, "switch_oob"); return;
    }
}
bb_0040d8be: {
    // 0x0040d8be: mov eax, dword ptr [ebp + 0x14]
    uint32_t t68 = static_cast<uint32_t>(ctx.ebp + 0x00000014u);
    uint32_t t69 = mem.r32(t68);
    ctx.eax = static_cast<uint32_t>(t69);
    // 0x0040d8c1: mov ecx, dword ptr [ebp + 0x10]
    uint32_t t70 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    uint32_t t71 = mem.r32(t70);
    ctx.ecx = static_cast<uint32_t>(t71);
    // 0x0040d8c4: push edi
    uint32_t t72 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    mem.w32(t72, ctx.edi);
    // 0x0040d8c5: call 0x495f50
    uint32_t t73 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    mem.w32(t73, 0x0040d8cau);
    sub_00495f50(ctx, mem);
    // 0x0040d8ca: add esp, 4
    uint32_t t74 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t74);
    ctx.esp = static_cast<uint32_t>(t74);
    // 0x0040d8cd: pop edi
    uint32_t t75 = ctx.esp;
    uint32_t t76 = mem.r32(t75);
    uint32_t t77 = static_cast<uint32_t>(t75 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    ctx.edi = static_cast<uint32_t>(t76);
    // 0x0040d8ce: pop esi
    uint32_t t78 = ctx.esp;
    uint32_t t79 = mem.r32(t78);
    uint32_t t80 = static_cast<uint32_t>(t78 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    ctx.esi = static_cast<uint32_t>(t79);
    // 0x0040d8cf: mov ecx, dword ptr [esp + 0x174]
    uint32_t t81 = static_cast<uint32_t>(ctx.esp + 0x00000174u);
    uint32_t t82 = mem.r32(t81);
    ctx.ecx = static_cast<uint32_t>(t82);
    // 0x0040d8d6: xor ecx, esp
    uint32_t t83 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t83);
    ctx.ecx = static_cast<uint32_t>(t83);
    // 0x0040d8d8: call 0x4e02f8
    uint32_t t84 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    mem.w32(t84, 0x0040d8ddu);
    hle_crt_004e02f8(ctx, mem);
    // 0x0040d8dd: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0040d8df: pop ebp
    uint32_t t85 = ctx.esp;
    uint32_t t86 = mem.r32(t85);
    uint32_t t87 = static_cast<uint32_t>(t85 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t87);
    ctx.ebp = static_cast<uint32_t>(t86);
    // 0x0040d8e0: ret 0x10
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 16u;
    return;
}
bb_0040d6d0: {
    // 0x0040d6d0: mov ecx, dword ptr [ebp + 0x10]
    uint32_t t88 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    uint32_t t89 = mem.r32(t88);
    ctx.ecx = static_cast<uint32_t>(t89);
    // 0x0040d6d3: movzx esi, cx
    uint32_t t90 = static_cast<uint32_t>(static_cast<uint16_t>(recomp_detail::r16(ctx.ecx)));
    ctx.esi = static_cast<uint32_t>(t90);
    // 0x0040d6d6: lea eax, [esi - 0x8004]
    uint32_t t91 = static_cast<uint32_t>(ctx.esi + 0xffff7ffcu);
    ctx.eax = static_cast<uint32_t>(t91);
    // 0x0040d6dc: cmp eax, 0x16
    uint32_t t92 = static_cast<uint32_t>(ctx.eax - 0x00000016u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000016u, t92);
    // 0x0040d6df: ja 0x40d863
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_0040d863;
    goto bb_0040d6e5;
}
bb_0040d687: {
    // 0x0040d687: sub ecx, 1
    uint32_t t93 = static_cast<uint32_t>(ctx.ecx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000001u, t93);
    ctx.ecx = static_cast<uint32_t>(t93);
    // 0x0040d68a: jne 0x40d898
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040d898;
    goto bb_0040d690;
}
bb_0040d64a: {
    // 0x0040d64a: mov dword ptr [0x76e660], 1
    mem.w32(0x0076e660u, 0x00000001u);
    // 0x0040d654: xor eax, eax
    uint32_t t94 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t94);
    ctx.eax = static_cast<uint32_t>(t94);
    // 0x0040d656: pop edi
    uint32_t t95 = ctx.esp;
    uint32_t t96 = mem.r32(t95);
    uint32_t t97 = static_cast<uint32_t>(t95 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t97);
    ctx.edi = static_cast<uint32_t>(t96);
    // 0x0040d657: pop esi
    uint32_t t98 = ctx.esp;
    uint32_t t99 = mem.r32(t98);
    uint32_t t100 = static_cast<uint32_t>(t98 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t100);
    ctx.esi = static_cast<uint32_t>(t99);
    // 0x0040d658: mov ecx, dword ptr [esp + 0x174]
    uint32_t t101 = static_cast<uint32_t>(ctx.esp + 0x00000174u);
    uint32_t t102 = mem.r32(t101);
    ctx.ecx = static_cast<uint32_t>(t102);
    // 0x0040d65f: xor ecx, esp
    uint32_t t103 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t103);
    ctx.ecx = static_cast<uint32_t>(t103);
    // 0x0040d661: call 0x4e02f8
    uint32_t t104 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t104);
    mem.w32(t104, 0x0040d666u);
    hle_crt_004e02f8(ctx, mem);
    // 0x0040d666: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0040d668: pop ebp
    uint32_t t105 = ctx.esp;
    uint32_t t106 = mem.r32(t105);
    uint32_t t107 = static_cast<uint32_t>(t105 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t107);
    ctx.ebp = static_cast<uint32_t>(t106);
    // 0x0040d669: ret 0x10
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 16u;
    return;
}
bb_0040d50d: {
    // 0x0040d50d: push 0x6d
    uint32_t t108 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t108);
    mem.w32(t108, 0x0000006du);
    // 0x0040d50f: push -6
    uint32_t t109 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t109);
    mem.w32(t109, 0xfffffffau);
    // 0x0040d511: push edi
    uint32_t t110 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t110);
    mem.w32(t110, ctx.edi);
    // 0x0040d512: call dword ptr [0x51b2dc]
    uint32_t t111 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t111);
    mem.w32(t111, 0x0040d518u);
    hle_iat_call(ctx, mem, 0x0051b2dcu);
    // 0x0040d518: push eax
    uint32_t t112 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t112);
    mem.w32(t112, ctx.eax);
    // 0x0040d519: call dword ptr [0x51b2cc]
    uint32_t t113 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t113);
    mem.w32(t113, 0x0040d51fu);
    hle_iat_call(ctx, mem, 0x0051b2ccu);
    // 0x0040d51f: push 2
    uint32_t t114 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t114);
    mem.w32(t114, 0x00000002u);
    // 0x0040d521: push eax
    uint32_t t115 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t115);
    mem.w32(t115, ctx.eax);
    // 0x0040d522: mov dword ptr [0x7b0bec], eax
    mem.w32(0x007b0becu, ctx.eax);
    // 0x0040d527: call dword ptr [0x51b224]
    uint32_t t116 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t116);
    mem.w32(t116, 0x0040d52du);
    hle_iat_call(ctx, mem, 0x0051b224u);
    // 0x0040d52d: push 0x534f8a
    uint32_t t117 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t117);
    mem.w32(t117, 0x00534f8au);
    // 0x0040d532: push 0x5351f4
    uint32_t t118 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    mem.w32(t118, 0x005351f4u);
    // 0x0040d537: lea edx, [esp + 0x80]
    uint32_t t119 = static_cast<uint32_t>(ctx.esp + 0x00000080u);
    ctx.edx = static_cast<uint32_t>(t119);
    // 0x0040d53e: push 0x535230
    uint32_t t120 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t120);
    mem.w32(t120, 0x00535230u);
    // 0x0040d543: push edx
    uint32_t t121 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t121);
    mem.w32(t121, ctx.edx);
    // 0x0040d544: mov dword ptr [0x7b0be8], eax
    mem.w32(0x007b0be8u, ctx.eax);
    // 0x0040d549: call dword ptr [0x51b240]
    uint32_t t122 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t122);
    mem.w32(t122, 0x0040d54fu);
    hle_iat_call(ctx, mem, 0x0051b240u);
    // 0x0040d54f: add esp, 0x10
    uint32_t t123 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t123);
    ctx.esp = static_cast<uint32_t>(t123);
    // 0x0040d552: lea eax, [esp + 0x78]
    uint32_t t124 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    ctx.eax = static_cast<uint32_t>(t124);
    // 0x0040d556: push eax
    uint32_t t125 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t125);
    mem.w32(t125, ctx.eax);
    // 0x0040d557: push edi
    uint32_t t126 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t126);
    mem.w32(t126, ctx.edi);
    // 0x0040d558: call dword ptr [0x51b294]
    uint32_t t127 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t127);
    mem.w32(t127, 0x0040d55eu);
    hle_iat_call(ctx, mem, 0x0051b294u);
    // 0x0040d55e: mov ecx, dword ptr [0x7b0be8]
    uint32_t t128 = mem.r32(0x007b0be8u);
    ctx.ecx = static_cast<uint32_t>(t128);
    // 0x0040d564: push 8
    uint32_t t129 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t129);
    mem.w32(t129, 0x00000008u);
    // 0x0040d566: push 0x8014
    uint32_t t130 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t130);
    mem.w32(t130, 0x00008014u);
    // 0x0040d56b: push ecx
    uint32_t t131 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t131);
    mem.w32(t131, ctx.ecx);
    // 0x0040d56c: call dword ptr [0x51b264]
    uint32_t t132 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t132);
    mem.w32(t132, 0x0040d572u);
    hle_iat_call(ctx, mem, 0x0051b264u);
    // 0x0040d572: xor eax, eax
    uint32_t t133 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t133);
    ctx.eax = static_cast<uint32_t>(t133);
    // 0x0040d574: pop edi
    uint32_t t134 = ctx.esp;
    uint32_t t135 = mem.r32(t134);
    uint32_t t136 = static_cast<uint32_t>(t134 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t136);
    ctx.edi = static_cast<uint32_t>(t135);
    // 0x0040d575: pop esi
    uint32_t t137 = ctx.esp;
    uint32_t t138 = mem.r32(t137);
    uint32_t t139 = static_cast<uint32_t>(t137 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t139);
    ctx.esi = static_cast<uint32_t>(t138);
    // 0x0040d576: mov ecx, dword ptr [esp + 0x174]
    uint32_t t140 = static_cast<uint32_t>(ctx.esp + 0x00000174u);
    uint32_t t141 = mem.r32(t140);
    ctx.ecx = static_cast<uint32_t>(t141);
    // 0x0040d57d: xor ecx, esp
    uint32_t t142 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t142);
    ctx.ecx = static_cast<uint32_t>(t142);
    // 0x0040d57f: call 0x4e02f8
    uint32_t t143 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t143);
    mem.w32(t143, 0x0040d584u);
    hle_crt_004e02f8(ctx, mem);
    // 0x0040d584: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0040d586: pop ebp
    uint32_t t144 = ctx.esp;
    uint32_t t145 = mem.r32(t144);
    uint32_t t146 = static_cast<uint32_t>(t144 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t146);
    ctx.ebp = static_cast<uint32_t>(t145);
    // 0x0040d587: ret 0x10
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 16u;
    return;
}
bb_0040d5f8: {
    // 0x0040d5f8: mov ecx, dword ptr [0x7b0bec]
    uint32_t t147 = mem.r32(0x007b0becu);
    ctx.ecx = static_cast<uint32_t>(t147);
    // 0x0040d5fe: push ecx
    uint32_t t148 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t148);
    mem.w32(t148, ctx.ecx);
    // 0x0040d5ff: call dword ptr [0x51b2c0]
    uint32_t t149 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t149);
    mem.w32(t149, 0x0040d605u);
    hle_iat_call(ctx, mem, 0x0051b2c0u);
    // 0x0040d605: push 0
    uint32_t t150 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t150);
    mem.w32(t150, 0x00000000u);
    // 0x0040d607: mov dword ptr [0x7b0bec], 0
    mem.w32(0x007b0becu, 0x00000000u);
    // 0x0040d611: call dword ptr [0x51b2a0]
    uint32_t t151 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t151);
    mem.w32(t151, 0x0040d617u);
    hle_iat_call(ctx, mem, 0x0051b2a0u);
    // 0x0040d617: xor eax, eax
    uint32_t t152 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t152);
    ctx.eax = static_cast<uint32_t>(t152);
    // 0x0040d619: pop edi
    uint32_t t153 = ctx.esp;
    uint32_t t154 = mem.r32(t153);
    uint32_t t155 = static_cast<uint32_t>(t153 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t155);
    ctx.edi = static_cast<uint32_t>(t154);
    // 0x0040d61a: pop esi
    uint32_t t156 = ctx.esp;
    uint32_t t157 = mem.r32(t156);
    uint32_t t158 = static_cast<uint32_t>(t156 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t158);
    ctx.esi = static_cast<uint32_t>(t157);
    // 0x0040d61b: mov ecx, dword ptr [esp + 0x174]
    uint32_t t159 = static_cast<uint32_t>(ctx.esp + 0x00000174u);
    uint32_t t160 = mem.r32(t159);
    ctx.ecx = static_cast<uint32_t>(t160);
    // 0x0040d622: xor ecx, esp
    uint32_t t161 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t161);
    ctx.ecx = static_cast<uint32_t>(t161);
    // 0x0040d624: call 0x4e02f8
    uint32_t t162 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t162);
    mem.w32(t162, 0x0040d629u);
    hle_crt_004e02f8(ctx, mem);
    // 0x0040d629: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0040d62b: pop ebp
    uint32_t t163 = ctx.esp;
    uint32_t t164 = mem.r32(t163);
    uint32_t t165 = static_cast<uint32_t>(t163 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t165);
    ctx.ebp = static_cast<uint32_t>(t164);
    // 0x0040d62c: ret 0x10
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 16u;
    return;
}
bb_0040d58a: {
    // 0x0040d58a: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x0040d58c: call 0x4a3ca0
    uint32_t t166 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t166);
    mem.w32(t166, 0x0040d591u);
    sub_004a3ca0(ctx, mem);
    // 0x0040d591: xor eax, eax
    uint32_t t167 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t167);
    ctx.eax = static_cast<uint32_t>(t167);
    // 0x0040d593: pop edi
    uint32_t t168 = ctx.esp;
    uint32_t t169 = mem.r32(t168);
    uint32_t t170 = static_cast<uint32_t>(t168 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t170);
    ctx.edi = static_cast<uint32_t>(t169);
    // 0x0040d594: pop esi
    uint32_t t171 = ctx.esp;
    uint32_t t172 = mem.r32(t171);
    uint32_t t173 = static_cast<uint32_t>(t171 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t173);
    ctx.esi = static_cast<uint32_t>(t172);
    // 0x0040d595: mov ecx, dword ptr [esp + 0x174]
    uint32_t t174 = static_cast<uint32_t>(ctx.esp + 0x00000174u);
    uint32_t t175 = mem.r32(t174);
    ctx.ecx = static_cast<uint32_t>(t175);
    // 0x0040d59c: xor ecx, esp
    uint32_t t176 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t176);
    ctx.ecx = static_cast<uint32_t>(t176);
    // 0x0040d59e: call 0x4e02f8
    uint32_t t177 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t177);
    mem.w32(t177, 0x0040d5a3u);
    hle_crt_004e02f8(ctx, mem);
    // 0x0040d5a3: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0040d5a5: pop ebp
    uint32_t t178 = ctx.esp;
    uint32_t t179 = mem.r32(t178);
    uint32_t t180 = static_cast<uint32_t>(t178 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t180);
    ctx.ebp = static_cast<uint32_t>(t179);
    // 0x0040d5a6: ret 0x10
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 16u;
    return;
}
bb_0040d5a9: {
    // 0x0040d5a9: lea edx, [esp + 0x38]
    uint32_t t181 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    ctx.edx = static_cast<uint32_t>(t181);
    // 0x0040d5ad: push edx
    uint32_t t182 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t182);
    mem.w32(t182, ctx.edx);
    // 0x0040d5ae: push edi
    uint32_t t183 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t183);
    mem.w32(t183, ctx.edi);
    // 0x0040d5af: call dword ptr [0x51b2ec]
    uint32_t t184 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t184);
    mem.w32(t184, 0x0040d5b5u);
    hle_iat_call(ctx, mem, 0x0051b2ecu);
    // 0x0040d5b5: lea eax, [esp + 0x38]
    uint32_t t185 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    ctx.eax = static_cast<uint32_t>(t185);
    // 0x0040d5b9: push eax
    uint32_t t186 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t186);
    mem.w32(t186, ctx.eax);
    // 0x0040d5ba: push edi
    uint32_t t187 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t187);
    mem.w32(t187, ctx.edi);
    // 0x0040d5bb: call dword ptr [0x51b308]
    uint32_t t188 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t188);
    mem.w32(t188, 0x0040d5c1u);
    hle_iat_call(ctx, mem, 0x0051b308u);
    // 0x0040d5c1: xor eax, eax
    uint32_t t189 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t189);
    ctx.eax = static_cast<uint32_t>(t189);
    // 0x0040d5c3: pop edi
    uint32_t t190 = ctx.esp;
    uint32_t t191 = mem.r32(t190);
    uint32_t t192 = static_cast<uint32_t>(t190 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t192);
    ctx.edi = static_cast<uint32_t>(t191);
    // 0x0040d5c4: pop esi
    uint32_t t193 = ctx.esp;
    uint32_t t194 = mem.r32(t193);
    uint32_t t195 = static_cast<uint32_t>(t193 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t195);
    ctx.esi = static_cast<uint32_t>(t194);
    // 0x0040d5c5: mov ecx, dword ptr [esp + 0x174]
    uint32_t t196 = static_cast<uint32_t>(ctx.esp + 0x00000174u);
    uint32_t t197 = mem.r32(t196);
    ctx.ecx = static_cast<uint32_t>(t197);
    // 0x0040d5cc: xor ecx, esp
    uint32_t t198 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t198);
    ctx.ecx = static_cast<uint32_t>(t198);
    // 0x0040d5ce: call 0x4e02f8
    uint32_t t199 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t199);
    mem.w32(t199, 0x0040d5d3u);
    hle_crt_004e02f8(ctx, mem);
    // 0x0040d5d3: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0040d5d5: pop ebp
    uint32_t t200 = ctx.esp;
    uint32_t t201 = mem.r32(t200);
    uint32_t t202 = static_cast<uint32_t>(t200 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t202);
    ctx.ebp = static_cast<uint32_t>(t201);
    // 0x0040d5d6: ret 0x10
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 16u;
    return;
}
bb_0040d5d9: {
    // 0x0040d5d9: push edi
    uint32_t t203 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t203);
    mem.w32(t203, ctx.edi);
    // 0x0040d5da: call dword ptr [0x51b22c]
    uint32_t t204 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t204);
    mem.w32(t204, 0x0040d5e0u);
    hle_iat_call(ctx, mem, 0x0051b22cu);
    // 0x0040d5e0: xor eax, eax
    uint32_t t205 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t205);
    ctx.eax = static_cast<uint32_t>(t205);
    // 0x0040d5e2: pop edi
    uint32_t t206 = ctx.esp;
    uint32_t t207 = mem.r32(t206);
    uint32_t t208 = static_cast<uint32_t>(t206 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t208);
    ctx.edi = static_cast<uint32_t>(t207);
    // 0x0040d5e3: pop esi
    uint32_t t209 = ctx.esp;
    uint32_t t210 = mem.r32(t209);
    uint32_t t211 = static_cast<uint32_t>(t209 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t211);
    ctx.esi = static_cast<uint32_t>(t210);
    // 0x0040d5e4: mov ecx, dword ptr [esp + 0x174]
    uint32_t t212 = static_cast<uint32_t>(ctx.esp + 0x00000174u);
    uint32_t t213 = mem.r32(t212);
    ctx.ecx = static_cast<uint32_t>(t213);
    // 0x0040d5eb: xor ecx, esp
    uint32_t t214 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t214);
    ctx.ecx = static_cast<uint32_t>(t214);
    // 0x0040d5ed: call 0x4e02f8
    uint32_t t215 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t215);
    mem.w32(t215, 0x0040d5f2u);
    hle_crt_004e02f8(ctx, mem);
    // 0x0040d5f2: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0040d5f4: pop ebp
    uint32_t t216 = ctx.esp;
    uint32_t t217 = mem.r32(t216);
    uint32_t t218 = static_cast<uint32_t>(t216 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t218);
    ctx.ebp = static_cast<uint32_t>(t217);
    // 0x0040d5f5: ret 0x10
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 16u;
    return;
}
bb_0040d863: {
    // 0x0040d863: mov edx, dword ptr [ebp + 0x14]
    uint32_t t219 = static_cast<uint32_t>(ctx.ebp + 0x00000014u);
    uint32_t t220 = mem.r32(t219);
    ctx.edx = static_cast<uint32_t>(t220);
    // 0x0040d866: push edx
    uint32_t t221 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t221);
    mem.w32(t221, ctx.edx);
    // 0x0040d867: push ecx
    uint32_t t222 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t222);
    mem.w32(t222, ctx.ecx);
    // 0x0040d868: push 0x111
    uint32_t t223 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t223);
    mem.w32(t223, 0x00000111u);
    // 0x0040d86d: push edi
    uint32_t t224 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t224);
    mem.w32(t224, ctx.edi);
    // 0x0040d86e: call dword ptr [0x51b2a4]
    uint32_t t225 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t225);
    mem.w32(t225, 0x0040d874u);
    hle_iat_call(ctx, mem, 0x0051b2a4u);
    // 0x0040d874: pop edi
    uint32_t t226 = ctx.esp;
    uint32_t t227 = mem.r32(t226);
    uint32_t t228 = static_cast<uint32_t>(t226 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t228);
    ctx.edi = static_cast<uint32_t>(t227);
    // 0x0040d875: pop esi
    uint32_t t229 = ctx.esp;
    uint32_t t230 = mem.r32(t229);
    uint32_t t231 = static_cast<uint32_t>(t229 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t231);
    ctx.esi = static_cast<uint32_t>(t230);
    // 0x0040d876: mov ecx, dword ptr [esp + 0x174]
    uint32_t t232 = static_cast<uint32_t>(ctx.esp + 0x00000174u);
    uint32_t t233 = mem.r32(t232);
    ctx.ecx = static_cast<uint32_t>(t233);
    // 0x0040d87d: xor ecx, esp
    uint32_t t234 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t234);
    ctx.ecx = static_cast<uint32_t>(t234);
    // 0x0040d87f: call 0x4e02f8
    uint32_t t235 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t235);
    mem.w32(t235, 0x0040d884u);
    hle_crt_004e02f8(ctx, mem);
    // 0x0040d884: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0040d886: pop ebp
    uint32_t t236 = ctx.esp;
    uint32_t t237 = mem.r32(t236);
    uint32_t t238 = static_cast<uint32_t>(t236 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t238);
    ctx.ebp = static_cast<uint32_t>(t237);
    // 0x0040d887: ret 0x10
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 16u;
    return;
}
bb_0040d6e5: {
    // 0x0040d6e5: movzx edx, byte ptr [eax + 0x40d944]
    uint32_t t239 = static_cast<uint32_t>(ctx.eax + 0x0040d944u);
    uint8_t t240 = mem.r8(t239);
    uint32_t t241 = static_cast<uint32_t>(static_cast<uint8_t>(t240));
    ctx.edx = static_cast<uint32_t>(t241);
    // 0x0040d6ec: jmp dword ptr [edx*4 + 0x40d934]
    switch (ctx.edx) {
        case 0u: goto bb_0040d6f3;
        case 1u: goto bb_0040d8f3;
        case 2u: goto bb_0040d748;
        case 3u: goto bb_0040d863;
        default: recomp_detail::trap_halt(ctx, 0x0040d934u, "switch_oob"); return;
    }
}
bb_0040d690: {
    // 0x0040d690: mov eax, dword ptr [ebp + 0x10]
    uint32_t t242 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    uint32_t t243 = mem.r32(t242);
    ctx.eax = static_cast<uint32_t>(t243);
    // 0x0040d693: mov edx, eax
    ctx.edx = static_cast<uint32_t>(ctx.eax);
    // 0x0040d695: and edx, 0xfff0
    uint32_t t244 = static_cast<uint32_t>(ctx.edx & 0x0000fff0u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t244);
    ctx.edx = static_cast<uint32_t>(t244);
    // 0x0040d69b: cmp edx, 0xf100
    uint32_t t245 = static_cast<uint32_t>(ctx.edx - 0x0000f100u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x0000f100u, t245);
    // 0x0040d6a1: je 0x40d8f3
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040d8f3;
    goto bb_0040d6a7;
}
bb_0040d6f3: {
    // 0x0040d6f3: mov eax, dword ptr [0x7b0be8]
    uint32_t t246 = mem.r32(0x007b0be8u);
    ctx.eax = static_cast<uint32_t>(t246);
    // 0x0040d6f8: mov esi, dword ptr [0x51b220]
    uint32_t t247 = mem.r32(0x0051b220u);
    ctx.esi = static_cast<uint32_t>(t247);
    // 0x0040d6fe: push 0
    uint32_t t248 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t248);
    mem.w32(t248, 0x00000000u);
    // 0x0040d700: push 0x8004
    uint32_t t249 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t249);
    mem.w32(t249, 0x00008004u);
    // 0x0040d705: push eax
    uint32_t t250 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t250);
    mem.w32(t250, ctx.eax);
    // 0x0040d706: call esi
    uint32_t t251 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t251);
    mem.w32(t251, 0x0040d708u);
    call_indirect(ctx, mem, ctx.esi);
    // 0x0040d708: mov ecx, dword ptr [0x7b0be8]
    uint32_t t252 = mem.r32(0x007b0be8u);
    ctx.ecx = static_cast<uint32_t>(t252);
    // 0x0040d70e: not eax
    uint32_t t253 = static_cast<uint32_t>(~ctx.eax);
    ctx.eax = static_cast<uint32_t>(t253);
    // 0x0040d710: and eax, 8
    uint32_t t254 = static_cast<uint32_t>(ctx.eax & 0x00000008u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t254);
    ctx.eax = static_cast<uint32_t>(t254);
    // 0x0040d713: push eax
    uint32_t t255 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t255);
    mem.w32(t255, ctx.eax);
    // 0x0040d714: push 0x8004
    uint32_t t256 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t256);
    mem.w32(t256, 0x00008004u);
    // 0x0040d719: push ecx
    uint32_t t257 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t257);
    mem.w32(t257, ctx.ecx);
    // 0x0040d71a: call dword ptr [0x51b264]
    uint32_t t258 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t258);
    mem.w32(t258, 0x0040d720u);
    hle_iat_call(ctx, mem, 0x0051b264u);
    // 0x0040d720: mov edx, dword ptr [0x7b0be8]
    uint32_t t259 = mem.r32(0x007b0be8u);
    ctx.edx = static_cast<uint32_t>(t259);
    // 0x0040d726: push 0
    uint32_t t260 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t260);
    mem.w32(t260, 0x00000000u);
    // 0x0040d728: push 0x8004
    uint32_t t261 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t261);
    mem.w32(t261, 0x00008004u);
    // 0x0040d72d: push edx
    uint32_t t262 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t262);
    mem.w32(t262, ctx.edx);
    // 0x0040d72e: call esi
    uint32_t t263 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t263);
    mem.w32(t263, 0x0040d730u);
    call_indirect(ctx, mem, ctx.esi);
    // 0x0040d730: xor eax, eax
    uint32_t t264 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t264);
    ctx.eax = static_cast<uint32_t>(t264);
    // 0x0040d732: pop edi
    uint32_t t265 = ctx.esp;
    uint32_t t266 = mem.r32(t265);
    uint32_t t267 = static_cast<uint32_t>(t265 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t267);
    ctx.edi = static_cast<uint32_t>(t266);
    // 0x0040d733: pop esi
    uint32_t t268 = ctx.esp;
    uint32_t t269 = mem.r32(t268);
    uint32_t t270 = static_cast<uint32_t>(t268 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t270);
    ctx.esi = static_cast<uint32_t>(t269);
    // 0x0040d734: mov ecx, dword ptr [esp + 0x174]
    uint32_t t271 = static_cast<uint32_t>(ctx.esp + 0x00000174u);
    uint32_t t272 = mem.r32(t271);
    ctx.ecx = static_cast<uint32_t>(t272);
    // 0x0040d73b: xor ecx, esp
    uint32_t t273 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t273);
    ctx.ecx = static_cast<uint32_t>(t273);
    // 0x0040d73d: call 0x4e02f8
    uint32_t t274 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t274);
    mem.w32(t274, 0x0040d742u);
    hle_crt_004e02f8(ctx, mem);
    // 0x0040d742: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0040d744: pop ebp
    uint32_t t275 = ctx.esp;
    uint32_t t276 = mem.r32(t275);
    uint32_t t277 = static_cast<uint32_t>(t275 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t277);
    ctx.ebp = static_cast<uint32_t>(t276);
    // 0x0040d745: ret 0x10
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 16u;
    return;
}
bb_0040d748: {
    // 0x0040d748: mov edi, dword ptr [0x51b264]
    uint32_t t278 = mem.r32(0x0051b264u);
    ctx.edi = static_cast<uint32_t>(t278);
    // 0x0040d74e: xor eax, eax
    uint32_t t279 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t279);
    ctx.eax = static_cast<uint32_t>(t279);
    // 0x0040d750: cmp esi, 0x8014
    uint32_t t280 = static_cast<uint32_t>(ctx.esi - 0x00008014u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00008014u, t280);
    // 0x0040d756: setne al
    uint8_t t281 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::NE) ? 1u : 0u);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t281));
    // 0x0040d759: sub eax, 1
    uint32_t t282 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t282);
    ctx.eax = static_cast<uint32_t>(t282);
    // 0x0040d75c: and eax, 8
    uint32_t t283 = static_cast<uint32_t>(ctx.eax & 0x00000008u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t283);
    ctx.eax = static_cast<uint32_t>(t283);
    // 0x0040d75f: push eax
    uint32_t t284 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t284);
    mem.w32(t284, ctx.eax);
    // 0x0040d760: mov eax, dword ptr [0x7b0be8]
    uint32_t t285 = mem.r32(0x007b0be8u);
    ctx.eax = static_cast<uint32_t>(t285);
    // 0x0040d765: push 0x8014
    uint32_t t286 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t286);
    mem.w32(t286, 0x00008014u);
    // 0x0040d76a: push eax
    uint32_t t287 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t287);
    mem.w32(t287, ctx.eax);
    // 0x0040d76b: call edi
    uint32_t t288 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t288);
    mem.w32(t288, 0x0040d76du);
    call_indirect(ctx, mem, ctx.edi);
    // 0x0040d76d: mov ecx, dword ptr [0x7b0be8]
    uint32_t t289 = mem.r32(0x007b0be8u);
    ctx.ecx = static_cast<uint32_t>(t289);
    // 0x0040d773: xor eax, eax
    uint32_t t290 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t290);
    ctx.eax = static_cast<uint32_t>(t290);
    // 0x0040d775: cmp esi, 0x8017
    uint32_t t291 = static_cast<uint32_t>(ctx.esi - 0x00008017u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00008017u, t291);
    // 0x0040d77b: setne al
    uint8_t t292 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::NE) ? 1u : 0u);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t292));
    // 0x0040d77e: sub eax, 1
    uint32_t t293 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t293);
    ctx.eax = static_cast<uint32_t>(t293);
    // 0x0040d781: and eax, 8
    uint32_t t294 = static_cast<uint32_t>(ctx.eax & 0x00000008u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t294);
    ctx.eax = static_cast<uint32_t>(t294);
    // 0x0040d784: push eax
    uint32_t t295 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t295);
    mem.w32(t295, ctx.eax);
    // 0x0040d785: push 0x8017
    uint32_t t296 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t296);
    mem.w32(t296, 0x00008017u);
    // 0x0040d78a: push ecx
    uint32_t t297 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t297);
    mem.w32(t297, ctx.ecx);
    // 0x0040d78b: call edi
    uint32_t t298 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t298);
    mem.w32(t298, 0x0040d78du);
    call_indirect(ctx, mem, ctx.edi);
    // 0x0040d78d: mov edx, dword ptr [0x7b0be8]
    uint32_t t299 = mem.r32(0x007b0be8u);
    ctx.edx = static_cast<uint32_t>(t299);
    // 0x0040d793: xor eax, eax
    uint32_t t300 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t300);
    ctx.eax = static_cast<uint32_t>(t300);
    // 0x0040d795: cmp esi, 0x8018
    uint32_t t301 = static_cast<uint32_t>(ctx.esi - 0x00008018u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00008018u, t301);
    // 0x0040d79b: setne al
    uint8_t t302 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::NE) ? 1u : 0u);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t302));
    // 0x0040d79e: sub eax, 1
    uint32_t t303 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t303);
    ctx.eax = static_cast<uint32_t>(t303);
    // 0x0040d7a1: and eax, 8
    uint32_t t304 = static_cast<uint32_t>(ctx.eax & 0x00000008u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t304);
    ctx.eax = static_cast<uint32_t>(t304);
    // 0x0040d7a4: push eax
    uint32_t t305 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t305);
    mem.w32(t305, ctx.eax);
    // 0x0040d7a5: push 0x8018
    uint32_t t306 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t306);
    mem.w32(t306, 0x00008018u);
    // 0x0040d7aa: push edx
    uint32_t t307 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t307);
    mem.w32(t307, ctx.edx);
    // 0x0040d7ab: call edi
    uint32_t t308 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t308);
    mem.w32(t308, 0x0040d7adu);
    call_indirect(ctx, mem, ctx.edi);
    // 0x0040d7ad: xor eax, eax
    uint32_t t309 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t309);
    ctx.eax = static_cast<uint32_t>(t309);
    // 0x0040d7af: cmp esi, 0x8019
    uint32_t t310 = static_cast<uint32_t>(ctx.esi - 0x00008019u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00008019u, t310);
    // 0x0040d7b5: setne al
    uint8_t t311 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::NE) ? 1u : 0u);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t311));
    // 0x0040d7b8: sub eax, 1
    uint32_t t312 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t312);
    ctx.eax = static_cast<uint32_t>(t312);
    // 0x0040d7bb: and eax, 8
    uint32_t t313 = static_cast<uint32_t>(ctx.eax & 0x00000008u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t313);
    ctx.eax = static_cast<uint32_t>(t313);
    // 0x0040d7be: push eax
    uint32_t t314 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t314);
    mem.w32(t314, ctx.eax);
    // 0x0040d7bf: mov eax, dword ptr [0x7b0be8]
    uint32_t t315 = mem.r32(0x007b0be8u);
    ctx.eax = static_cast<uint32_t>(t315);
    // 0x0040d7c4: push 0x8019
    uint32_t t316 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t316);
    mem.w32(t316, 0x00008019u);
    // 0x0040d7c9: push eax
    uint32_t t317 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t317);
    mem.w32(t317, ctx.eax);
    // 0x0040d7ca: call edi
    uint32_t t318 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t318);
    mem.w32(t318, 0x0040d7ccu);
    call_indirect(ctx, mem, ctx.edi);
    // 0x0040d7cc: mov ecx, dword ptr [0x7b0be8]
    uint32_t t319 = mem.r32(0x007b0be8u);
    ctx.ecx = static_cast<uint32_t>(t319);
    // 0x0040d7d2: xor eax, eax
    uint32_t t320 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t320);
    ctx.eax = static_cast<uint32_t>(t320);
    // 0x0040d7d4: cmp esi, 0x801a
    uint32_t t321 = static_cast<uint32_t>(ctx.esi - 0x0000801au);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x0000801au, t321);
    // 0x0040d7da: setne al
    uint8_t t322 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::NE) ? 1u : 0u);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t322));
    // 0x0040d7dd: sub eax, 1
    uint32_t t323 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t323);
    ctx.eax = static_cast<uint32_t>(t323);
    // 0x0040d7e0: and eax, 8
    uint32_t t324 = static_cast<uint32_t>(ctx.eax & 0x00000008u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t324);
    ctx.eax = static_cast<uint32_t>(t324);
    // 0x0040d7e3: push eax
    uint32_t t325 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t325);
    mem.w32(t325, ctx.eax);
    // 0x0040d7e4: push 0x801a
    uint32_t t326 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t326);
    mem.w32(t326, 0x0000801au);
    // 0x0040d7e9: push ecx
    uint32_t t327 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t327);
    mem.w32(t327, ctx.ecx);
    // 0x0040d7ea: call edi
    uint32_t t328 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t328);
    mem.w32(t328, 0x0040d7ecu);
    call_indirect(ctx, mem, ctx.edi);
    // 0x0040d7ec: mov edx, dword ptr [0x7b0be8]
    uint32_t t329 = mem.r32(0x007b0be8u);
    ctx.edx = static_cast<uint32_t>(t329);
    // 0x0040d7f2: xor eax, eax
    uint32_t t330 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t330);
    ctx.eax = static_cast<uint32_t>(t330);
    // 0x0040d7f4: cmp esi, 0x8011
    uint32_t t331 = static_cast<uint32_t>(ctx.esi - 0x00008011u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00008011u, t331);
    // 0x0040d7fa: setne al
    uint8_t t332 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::NE) ? 1u : 0u);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t332));
    // 0x0040d7fd: sub eax, 1
    uint32_t t333 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t333);
    ctx.eax = static_cast<uint32_t>(t333);
    // 0x0040d800: and eax, 8
    uint32_t t334 = static_cast<uint32_t>(ctx.eax & 0x00000008u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t334);
    ctx.eax = static_cast<uint32_t>(t334);
    // 0x0040d803: push eax
    uint32_t t335 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t335);
    mem.w32(t335, ctx.eax);
    // 0x0040d804: push 0x8011
    uint32_t t336 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t336);
    mem.w32(t336, 0x00008011u);
    // 0x0040d809: push edx
    uint32_t t337 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t337);
    mem.w32(t337, ctx.edx);
    // 0x0040d80a: call edi
    uint32_t t338 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t338);
    mem.w32(t338, 0x0040d80cu);
    call_indirect(ctx, mem, ctx.edi);
    // 0x0040d80c: xor eax, eax
    uint32_t t339 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t339);
    ctx.eax = static_cast<uint32_t>(t339);
    // 0x0040d80e: cmp esi, 0x8012
    uint32_t t340 = static_cast<uint32_t>(ctx.esi - 0x00008012u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00008012u, t340);
    // 0x0040d814: setne al
    uint8_t t341 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::NE) ? 1u : 0u);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t341));
    // 0x0040d817: sub eax, 1
    uint32_t t342 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t342);
    ctx.eax = static_cast<uint32_t>(t342);
    // 0x0040d81a: and eax, 8
    uint32_t t343 = static_cast<uint32_t>(ctx.eax & 0x00000008u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t343);
    ctx.eax = static_cast<uint32_t>(t343);
    // 0x0040d81d: push eax
    uint32_t t344 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t344);
    mem.w32(t344, ctx.eax);
    // 0x0040d81e: mov eax, dword ptr [0x7b0be8]
    uint32_t t345 = mem.r32(0x007b0be8u);
    ctx.eax = static_cast<uint32_t>(t345);
    // 0x0040d823: push 0x8012
    uint32_t t346 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t346);
    mem.w32(t346, 0x00008012u);
    // 0x0040d828: push eax
    uint32_t t347 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t347);
    mem.w32(t347, ctx.eax);
    // 0x0040d829: call edi
    uint32_t t348 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t348);
    mem.w32(t348, 0x0040d82bu);
    call_indirect(ctx, mem, ctx.edi);
    // 0x0040d82b: mov ecx, dword ptr [0x7b0be8]
    uint32_t t349 = mem.r32(0x007b0be8u);
    ctx.ecx = static_cast<uint32_t>(t349);
    // 0x0040d831: xor eax, eax
    uint32_t t350 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t350);
    ctx.eax = static_cast<uint32_t>(t350);
    // 0x0040d833: cmp esi, 0x8016
    uint32_t t351 = static_cast<uint32_t>(ctx.esi - 0x00008016u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00008016u, t351);
    // 0x0040d839: setne al
    uint8_t t352 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::NE) ? 1u : 0u);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t352));
    // 0x0040d83c: sub eax, 1
    uint32_t t353 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t353);
    ctx.eax = static_cast<uint32_t>(t353);
    // 0x0040d83f: and eax, 8
    uint32_t t354 = static_cast<uint32_t>(ctx.eax & 0x00000008u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t354);
    ctx.eax = static_cast<uint32_t>(t354);
    // 0x0040d842: push eax
    uint32_t t355 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t355);
    mem.w32(t355, ctx.eax);
    // 0x0040d843: push 0x8016
    uint32_t t356 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t356);
    mem.w32(t356, 0x00008016u);
    // 0x0040d848: push ecx
    uint32_t t357 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t357);
    mem.w32(t357, ctx.ecx);
    // 0x0040d849: call edi
    uint32_t t358 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t358);
    mem.w32(t358, 0x0040d84bu);
    call_indirect(ctx, mem, ctx.edi);
    // 0x0040d84b: xor eax, eax
    uint32_t t359 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t359);
    ctx.eax = static_cast<uint32_t>(t359);
    // 0x0040d84d: pop edi
    uint32_t t360 = ctx.esp;
    uint32_t t361 = mem.r32(t360);
    uint32_t t362 = static_cast<uint32_t>(t360 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t362);
    ctx.edi = static_cast<uint32_t>(t361);
    // 0x0040d84e: pop esi
    uint32_t t363 = ctx.esp;
    uint32_t t364 = mem.r32(t363);
    uint32_t t365 = static_cast<uint32_t>(t363 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t365);
    ctx.esi = static_cast<uint32_t>(t364);
    // 0x0040d84f: mov ecx, dword ptr [esp + 0x174]
    uint32_t t366 = static_cast<uint32_t>(ctx.esp + 0x00000174u);
    uint32_t t367 = mem.r32(t366);
    ctx.ecx = static_cast<uint32_t>(t367);
    // 0x0040d856: xor ecx, esp
    uint32_t t368 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t368);
    ctx.ecx = static_cast<uint32_t>(t368);
    // 0x0040d858: call 0x4e02f8
    uint32_t t369 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t369);
    mem.w32(t369, 0x0040d85du);
    hle_crt_004e02f8(ctx, mem);
    // 0x0040d85d: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0040d85f: pop ebp
    uint32_t t370 = ctx.esp;
    uint32_t t371 = mem.r32(t370);
    uint32_t t372 = static_cast<uint32_t>(t370 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t372);
    ctx.ebp = static_cast<uint32_t>(t371);
    // 0x0040d860: ret 0x10
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 16u;
    return;
}
bb_0040d6a7: {
    // 0x0040d6a7: mov ecx, dword ptr [ebp + 0x14]
    uint32_t t373 = static_cast<uint32_t>(ctx.ebp + 0x00000014u);
    uint32_t t374 = mem.r32(t373);
    ctx.ecx = static_cast<uint32_t>(t374);
    // 0x0040d6aa: push ecx
    uint32_t t375 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t375);
    mem.w32(t375, ctx.ecx);
    // 0x0040d6ab: push eax
    uint32_t t376 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t376);
    mem.w32(t376, ctx.eax);
    // 0x0040d6ac: push 0x112
    uint32_t t377 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t377);
    mem.w32(t377, 0x00000112u);
    // 0x0040d6b1: push edi
    uint32_t t378 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t378);
    mem.w32(t378, ctx.edi);
    // 0x0040d6b2: call dword ptr [0x51b2a4]
    uint32_t t379 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t379);
    mem.w32(t379, 0x0040d6b8u);
    hle_iat_call(ctx, mem, 0x0051b2a4u);
    // 0x0040d6b8: xor eax, eax
    uint32_t t380 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t380);
    ctx.eax = static_cast<uint32_t>(t380);
    // 0x0040d6ba: pop edi
    uint32_t t381 = ctx.esp;
    uint32_t t382 = mem.r32(t381);
    uint32_t t383 = static_cast<uint32_t>(t381 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t383);
    ctx.edi = static_cast<uint32_t>(t382);
    // 0x0040d6bb: pop esi
    uint32_t t384 = ctx.esp;
    uint32_t t385 = mem.r32(t384);
    uint32_t t386 = static_cast<uint32_t>(t384 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t386);
    ctx.esi = static_cast<uint32_t>(t385);
    // 0x0040d6bc: mov ecx, dword ptr [esp + 0x174]
    uint32_t t387 = static_cast<uint32_t>(ctx.esp + 0x00000174u);
    uint32_t t388 = mem.r32(t387);
    ctx.ecx = static_cast<uint32_t>(t388);
    // 0x0040d6c3: xor ecx, esp
    uint32_t t389 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t389);
    ctx.ecx = static_cast<uint32_t>(t389);
    // 0x0040d6c5: call 0x4e02f8
    uint32_t t390 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t390);
    mem.w32(t390, 0x0040d6cau);
    hle_crt_004e02f8(ctx, mem);
    // 0x0040d6ca: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0040d6cc: pop ebp
    uint32_t t391 = ctx.esp;
    uint32_t t392 = mem.r32(t391);
    uint32_t t393 = static_cast<uint32_t>(t391 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t393);
    ctx.ebp = static_cast<uint32_t>(t392);
    // 0x0040d6cd: ret 0x10
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 16u;
    return;
}
}

// sub_0040d960 | subsystem=Core/Windows | canonical | 16 blocks | 141 insns
void sub_0040d960(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040d960: sub esp, 0x24
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000024u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000024u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x0040d963: mov ecx, dword ptr [0x54d04c]
    uint32_t t1 = mem.r32(0x0054d04cu);
    ctx.ecx = static_cast<uint32_t>(t1);
    // 0x0040d969: push ebx
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebx);
    // 0x0040d96a: mov ebx, dword ptr [0x76e77c]
    uint32_t t3 = mem.r32(0x0076e77cu);
    ctx.ebx = static_cast<uint32_t>(t3);
    // 0x0040d970: push ebp
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.ebp);
    // 0x0040d971: mov ebp, dword ptr [0x54d048]
    uint32_t t5 = mem.r32(0x0054d048u);
    ctx.ebp = static_cast<uint32_t>(t5);
    // 0x0040d977: push esi
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.esi);
    // 0x0040d978: push edi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.edi);
    // 0x0040d979: mov edi, dword ptr [0x76e778]
    uint32_t t8 = mem.r32(0x0076e778u);
    ctx.edi = static_cast<uint32_t>(t8);
    // 0x0040d97f: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0040d981: mov eax, dword ptr [0x54d040]
    uint32_t t9 = mem.r32(0x0054d040u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x0040d986: push 0
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x00000000u);
    // 0x0040d988: mov dword ptr [esp + 0x1c], eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t11, ctx.eax);
    // 0x0040d98c: mov dword ptr [esp + 0x18], ecx
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t12, ctx.ecx);
    // 0x0040d990: mov dword ptr [esp + 0x20], ebp
    uint32_t t13 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t13, ctx.ebp);
    // 0x0040d994: call dword ptr [0x51b234]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x0040d99au);
    hle_iat_call(ctx, mem, 0x0051b234u);
    // 0x0040d99a: sub eax, ebp
    uint32_t t15 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t15);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x0040d99c: cmp edi, eax
    uint32_t t16 = static_cast<uint32_t>(ctx.edi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.eax, t16);
    // 0x0040d99e: jl 0x40d9ac
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040d9ac;
    goto bb_0040d9a0;
}
bb_0040d9ac: {
    // 0x0040d9ac: push 1
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x00000001u);
    // 0x0040d9ae: call dword ptr [0x51b234]
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x0040d9b4u);
    hle_iat_call(ctx, mem, 0x0051b234u);
    // 0x0040d9b4: mov ebp, dword ptr [esp + 0x14]
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t20 = mem.r32(t19);
    ctx.ebp = static_cast<uint32_t>(t20);
    // 0x0040d9b8: sub eax, ebp
    uint32_t t21 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t21);
    ctx.eax = static_cast<uint32_t>(t21);
    // 0x0040d9ba: cmp ebx, eax
    uint32_t t22 = static_cast<uint32_t>(ctx.ebx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.eax, t22);
    // 0x0040d9bc: jl 0x40d9ca
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040d9ca;
    goto bb_0040d9be;
}
bb_0040d9a0: {
    // 0x0040d9a0: push 0
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x00000000u);
    // 0x0040d9a2: call dword ptr [0x51b234]
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x0040d9a8u);
    hle_iat_call(ctx, mem, 0x0051b234u);
    // 0x0040d9a8: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x0040d9aa: sub edi, ebp
    uint32_t t25 = static_cast<uint32_t>(ctx.edi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebp, t25);
    ctx.edi = static_cast<uint32_t>(t25);
    goto bb_0040d9ac;
}
bb_0040d9ca: {
    // 0x0040d9ca: test edi, edi
    uint32_t t26 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t26);
    // 0x0040d9cc: jge 0x40d9d0
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0040d9d0;
    goto bb_0040d9ce;
}
bb_0040d9be: {
    // 0x0040d9be: push 1
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x00000001u);
    // 0x0040d9c0: call dword ptr [0x51b234]
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x0040d9c6u);
    hle_iat_call(ctx, mem, 0x0051b234u);
    // 0x0040d9c6: mov ebx, eax
    ctx.ebx = static_cast<uint32_t>(ctx.eax);
    // 0x0040d9c8: sub ebx, ebp
    uint32_t t29 = static_cast<uint32_t>(ctx.ebx - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.ebp, t29);
    ctx.ebx = static_cast<uint32_t>(t29);
    goto bb_0040d9ca;
}
bb_0040d9d0: {
    // 0x0040d9d0: test ebx, ebx
    uint32_t t30 = static_cast<uint32_t>(ctx.ebx & ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t30);
    // 0x0040d9d2: jge 0x40d9d6
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0040d9d6;
    goto bb_0040d9d4;
}
bb_0040d9ce: {
    // 0x0040d9ce: xor edi, edi
    uint32_t t31 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t31);
    ctx.edi = static_cast<uint32_t>(t31);
    goto bb_0040d9d0;
}
bb_0040d9d6: {
    // 0x0040d9d6: cmp dword ptr [esp + 0x18], 1
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t33 = mem.r32(t32);
    uint32_t t34 = static_cast<uint32_t>(t33 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t33, 0x00000001u, t34);
    // 0x0040d9db: jne 0x40da9e
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040da9e;
    goto bb_0040d9e1;
}
bb_0040d9d4: {
    // 0x0040d9d4: xor ebx, ebx
    uint32_t t35 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t35);
    ctx.ebx = static_cast<uint32_t>(t35);
    goto bb_0040d9d6;
}
bb_0040da9e: {
    // 0x0040da9e: mov ecx, dword ptr [esi]
    uint32_t t36 = mem.r32(ctx.esi);
    ctx.ecx = static_cast<uint32_t>(t36);
    // 0x0040daa0: push 0x12080000
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, 0x12080000u);
    // 0x0040daa5: push -0x10
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, 0xfffffff0u);
    // 0x0040daa7: push ecx
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, ctx.ecx);
    // 0x0040daa8: call dword ptr [0x51b268]
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, 0x0040daaeu);
    hle_iat_call(ctx, mem, 0x0051b268u);
    // 0x0040daae: mov edi, dword ptr [0x51b2a8]
    uint32_t t41 = mem.r32(0x0051b2a8u);
    ctx.edi = static_cast<uint32_t>(t41);
    // 0x0040dab4: push 0
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, 0x00000000u);
    // 0x0040dab6: call edi
    uint32_t t43 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    mem.w32(t43, 0x0040dab8u);
    call_indirect(ctx, mem, ctx.edi);
    // 0x0040dab8: test eax, eax
    uint32_t t44 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t44);
    // 0x0040daba: jl 0x40dac8
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040dac8;
    goto bb_0040dabc;
}
bb_0040d9e1: {
    // 0x0040d9e1: mov edx, dword ptr [esi]
    uint32_t t45 = mem.r32(ctx.esi);
    ctx.edx = static_cast<uint32_t>(t45);
    // 0x0040d9e3: push 0x12cc0000
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, 0x12cc0000u);
    // 0x0040d9e8: push -0x10
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, 0xfffffff0u);
    // 0x0040d9ea: push edx
    uint32_t t48 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    mem.w32(t48, ctx.edx);
    // 0x0040d9eb: call dword ptr [0x51b268]
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, 0x0040d9f1u);
    hle_iat_call(ctx, mem, 0x0051b268u);
    // 0x0040d9f1: mov ecx, dword ptr [esi]
    uint32_t t50 = mem.r32(ctx.esi);
    ctx.ecx = static_cast<uint32_t>(t50);
    // 0x0040d9f3: mov ebp, dword ptr [0x51b260]
    uint32_t t51 = mem.r32(0x0051b260u);
    ctx.ebp = static_cast<uint32_t>(t51);
    // 0x0040d9f9: lea eax, [esp + 0x20]
    uint32_t t52 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    ctx.eax = static_cast<uint32_t>(t52);
    // 0x0040d9fd: push eax
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, ctx.eax);
    // 0x0040d9fe: push ecx
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, ctx.ecx);
    // 0x0040d9ff: call ebp
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, 0x0040da01u);
    call_indirect(ctx, mem, ctx.ebp);
    // 0x0040da01: mov edx, dword ptr [esp + 0x2c]
    uint32_t t56 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    uint32_t t57 = mem.r32(t56);
    ctx.edx = static_cast<uint32_t>(t57);
    // 0x0040da05: sub edx, dword ptr [esp + 0x24]
    uint32_t t58 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t59 = mem.r32(t58);
    uint32_t t60 = static_cast<uint32_t>(ctx.edx - t59);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, t59, t60);
    ctx.edx = static_cast<uint32_t>(t60);
    // 0x0040da09: mov eax, dword ptr [esp + 0x28]
    uint32_t t61 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t62 = mem.r32(t61);
    ctx.eax = static_cast<uint32_t>(t62);
    // 0x0040da0d: sub eax, dword ptr [esp + 0x20]
    uint32_t t63 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t64 = mem.r32(t63);
    uint32_t t65 = static_cast<uint32_t>(ctx.eax - t64);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, t64, t65);
    ctx.eax = static_cast<uint32_t>(t65);
    // 0x0040da11: mov ecx, dword ptr [esi]
    uint32_t t66 = mem.r32(ctx.esi);
    ctx.ecx = static_cast<uint32_t>(t66);
    // 0x0040da13: push 0
    uint32_t t67 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t67);
    mem.w32(t67, 0x00000000u);
    // 0x0040da15: push edx
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, ctx.edx);
    // 0x0040da16: push eax
    uint32_t t69 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    mem.w32(t69, ctx.eax);
    // 0x0040da17: push 0
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, 0x00000000u);
    // 0x0040da19: push 0
    uint32_t t71 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t71);
    mem.w32(t71, 0x00000000u);
    // 0x0040da1b: push ecx
    uint32_t t72 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    mem.w32(t72, ctx.ecx);
    // 0x0040da1c: call dword ptr [0x51b270]
    uint32_t t73 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    mem.w32(t73, 0x0040da22u);
    hle_iat_call(ctx, mem, 0x0051b270u);
    // 0x0040da22: mov eax, dword ptr [esi]
    uint32_t t74 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t74);
    // 0x0040da24: lea edx, [esp + 0x20]
    uint32_t t75 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    ctx.edx = static_cast<uint32_t>(t75);
    // 0x0040da28: push edx
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    mem.w32(t76, ctx.edx);
    // 0x0040da29: push eax
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, ctx.eax);
    // 0x0040da2a: call ebp
    uint32_t t78 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    mem.w32(t78, 0x0040da2cu);
    call_indirect(ctx, mem, ctx.ebp);
    // 0x0040da2c: mov eax, dword ptr [esp + 0x24]
    uint32_t t79 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t80 = mem.r32(t79);
    ctx.eax = static_cast<uint32_t>(t80);
    // 0x0040da30: mov ecx, dword ptr [esp + 0x2c]
    uint32_t t81 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    uint32_t t82 = mem.r32(t81);
    ctx.ecx = static_cast<uint32_t>(t82);
    // 0x0040da34: mov edx, dword ptr [esp + 0x28]
    uint32_t t83 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t84 = mem.r32(t83);
    ctx.edx = static_cast<uint32_t>(t84);
    // 0x0040da38: push 1
    uint32_t t85 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t85);
    mem.w32(t85, 0x00000001u);
    // 0x0040da3a: sub ecx, eax
    uint32_t t86 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t86);
    ctx.ecx = static_cast<uint32_t>(t86);
    // 0x0040da3c: push ecx
    uint32_t t87 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t87);
    mem.w32(t87, ctx.ecx);
    // 0x0040da3d: mov ecx, dword ptr [esp + 0x28]
    uint32_t t88 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t89 = mem.r32(t88);
    ctx.ecx = static_cast<uint32_t>(t89);
    // 0x0040da41: sub edx, ecx
    uint32_t t90 = static_cast<uint32_t>(ctx.edx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ecx, t90);
    ctx.edx = static_cast<uint32_t>(t90);
    // 0x0040da43: push edx
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, ctx.edx);
    // 0x0040da44: add eax, ebx
    uint32_t t92 = static_cast<uint32_t>(ctx.eax + ctx.ebx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.ebx, t92);
    ctx.eax = static_cast<uint32_t>(t92);
    // 0x0040da46: push eax
    uint32_t t93 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    mem.w32(t93, ctx.eax);
    // 0x0040da47: mov eax, dword ptr [esi]
    uint32_t t94 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t94);
    // 0x0040da49: add ecx, edi
    uint32_t t95 = static_cast<uint32_t>(ctx.ecx + ctx.edi);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, ctx.edi, t95);
    ctx.ecx = static_cast<uint32_t>(t95);
    // 0x0040da4b: push ecx
    uint32_t t96 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    mem.w32(t96, ctx.ecx);
    // 0x0040da4c: push eax
    uint32_t t97 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t97);
    mem.w32(t97, ctx.eax);
    // 0x0040da4d: call dword ptr [0x51b270]
    uint32_t t98 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t98);
    mem.w32(t98, 0x0040da53u);
    hle_iat_call(ctx, mem, 0x0051b270u);
    // 0x0040da53: mov ecx, dword ptr [esp + 0x14]
    uint32_t t99 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t100 = mem.r32(t99);
    ctx.ecx = static_cast<uint32_t>(t100);
    // 0x0040da57: mov edx, dword ptr [esp + 0x1c]
    uint32_t t101 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t102 = mem.r32(t101);
    ctx.edx = static_cast<uint32_t>(t102);
    // 0x0040da5b: push ecx
    uint32_t t103 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    mem.w32(t103, ctx.ecx);
    // 0x0040da5c: push edx
    uint32_t t104 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t104);
    mem.w32(t104, ctx.edx);
    // 0x0040da5d: call 0x416f70
    uint32_t t105 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t105);
    mem.w32(t105, 0x0040da62u);
    sub_00416f70(ctx, mem);
    // 0x0040da62: mov edi, dword ptr [0x51b2a8]
    uint32_t t106 = mem.r32(0x0051b2a8u);
    ctx.edi = static_cast<uint32_t>(t106);
    // 0x0040da68: push 1
    uint32_t t107 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t107);
    mem.w32(t107, 0x00000001u);
    // 0x0040da6a: call edi
    uint32_t t108 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t108);
    mem.w32(t108, 0x0040da6cu);
    call_indirect(ctx, mem, ctx.edi);
    // 0x0040da6c: test eax, eax
    uint32_t t109 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t109);
    // 0x0040da6e: jge 0x40da78
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0040da78;
    goto bb_0040da70;
}
bb_0040dac8: {
    // 0x0040dac8: mov edx, dword ptr [esi]
    uint32_t t110 = mem.r32(ctx.esi);
    ctx.edx = static_cast<uint32_t>(t110);
    // 0x0040daca: push edx
    uint32_t t111 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t111);
    mem.w32(t111, ctx.edx);
    // 0x0040dacb: call dword ptr [0x51b2ac]
    uint32_t t112 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t112);
    mem.w32(t112, 0x0040dad1u);
    hle_iat_call(ctx, mem, 0x0051b2acu);
    // 0x0040dad1: pop edi
    uint32_t t113 = ctx.esp;
    uint32_t t114 = mem.r32(t113);
    uint32_t t115 = static_cast<uint32_t>(t113 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t115);
    ctx.edi = static_cast<uint32_t>(t114);
    // 0x0040dad2: pop esi
    uint32_t t116 = ctx.esp;
    uint32_t t117 = mem.r32(t116);
    uint32_t t118 = static_cast<uint32_t>(t116 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    ctx.esi = static_cast<uint32_t>(t117);
    // 0x0040dad3: pop ebp
    uint32_t t119 = ctx.esp;
    uint32_t t120 = mem.r32(t119);
    uint32_t t121 = static_cast<uint32_t>(t119 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t121);
    ctx.ebp = static_cast<uint32_t>(t120);
    // 0x0040dad4: pop ebx
    uint32_t t122 = ctx.esp;
    uint32_t t123 = mem.r32(t122);
    uint32_t t124 = static_cast<uint32_t>(t122 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t124);
    ctx.ebx = static_cast<uint32_t>(t123);
    // 0x0040dad5: add esp, 0x24
    uint32_t t125 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000024u, t125);
    ctx.esp = static_cast<uint32_t>(t125);
    // 0x0040dad8: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040dabc: {
    // 0x0040dabc: lea esp, [esp]
    ctx.esp = static_cast<uint32_t>(ctx.esp);
    goto bb_0040dac0;
}
bb_0040da78: {
    // 0x0040da78: mov eax, dword ptr [esi]
    uint32_t t126 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t126);
    // 0x0040da7a: push 0x43
    uint32_t t127 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t127);
    mem.w32(t127, 0x00000043u);
    // 0x0040da7c: push 0
    uint32_t t128 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t128);
    mem.w32(t128, 0x00000000u);
    // 0x0040da7e: push 0
    uint32_t t129 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t129);
    mem.w32(t129, 0x00000000u);
    // 0x0040da80: push 0
    uint32_t t130 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t130);
    mem.w32(t130, 0x00000000u);
    // 0x0040da82: push 0
    uint32_t t131 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t131);
    mem.w32(t131, 0x00000000u);
    // 0x0040da84: push -2
    uint32_t t132 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t132);
    mem.w32(t132, 0xfffffffeu);
    // 0x0040da86: push eax
    uint32_t t133 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t133);
    mem.w32(t133, ctx.eax);
    // 0x0040da87: call dword ptr [0x51b2c8]
    uint32_t t134 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t134);
    mem.w32(t134, 0x0040da8du);
    hle_iat_call(ctx, mem, 0x0051b2c8u);
    // 0x0040da8d: mov edx, dword ptr [esi]
    uint32_t t135 = mem.r32(ctx.esi);
    ctx.edx = static_cast<uint32_t>(t135);
    // 0x0040da8f: push edx
    uint32_t t136 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t136);
    mem.w32(t136, ctx.edx);
    // 0x0040da90: call dword ptr [0x51b2ac]
    uint32_t t137 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t137);
    mem.w32(t137, 0x0040da96u);
    hle_iat_call(ctx, mem, 0x0051b2acu);
    // 0x0040da96: pop edi
    uint32_t t138 = ctx.esp;
    uint32_t t139 = mem.r32(t138);
    uint32_t t140 = static_cast<uint32_t>(t138 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t140);
    ctx.edi = static_cast<uint32_t>(t139);
    // 0x0040da97: pop esi
    uint32_t t141 = ctx.esp;
    uint32_t t142 = mem.r32(t141);
    uint32_t t143 = static_cast<uint32_t>(t141 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t143);
    ctx.esi = static_cast<uint32_t>(t142);
    // 0x0040da98: pop ebp
    uint32_t t144 = ctx.esp;
    uint32_t t145 = mem.r32(t144);
    uint32_t t146 = static_cast<uint32_t>(t144 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t146);
    ctx.ebp = static_cast<uint32_t>(t145);
    // 0x0040da99: pop ebx
    uint32_t t147 = ctx.esp;
    uint32_t t148 = mem.r32(t147);
    uint32_t t149 = static_cast<uint32_t>(t147 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t149);
    ctx.ebx = static_cast<uint32_t>(t148);
    // 0x0040da9a: add esp, 0x24
    uint32_t t150 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000024u, t150);
    ctx.esp = static_cast<uint32_t>(t150);
    // 0x0040da9d: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040da70: {
    // 0x0040da70: push 1
    uint32_t t151 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t151);
    mem.w32(t151, 0x00000001u);
    // 0x0040da72: call edi
    uint32_t t152 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t152);
    mem.w32(t152, 0x0040da74u);
    call_indirect(ctx, mem, ctx.edi);
    // 0x0040da74: test eax, eax
    uint32_t t153 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t153);
    // 0x0040da76: jl 0x40da70
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040da70;
    goto bb_0040da78;
}
bb_0040dac0: {
    // 0x0040dac0: push 0
    uint32_t t154 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t154);
    mem.w32(t154, 0x00000000u);
    // 0x0040dac2: call edi
    uint32_t t155 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t155);
    mem.w32(t155, 0x0040dac4u);
    call_indirect(ctx, mem, ctx.edi);
    // 0x0040dac4: test eax, eax
    uint32_t t156 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t156);
    // 0x0040dac6: jge 0x40dac0
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0040dac0;
    goto bb_0040dac8;
}
}

// sub_0040dae0 | subsystem=Core/Windows | canonical | 14 blocks | 63 insns
void sub_0040dae0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040dae0: mov eax, dword ptr [0x76e7d4]
    uint32_t t0 = mem.r32(0x0076e7d4u);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x0040dae5: test eax, eax
    uint32_t t1 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    // 0x0040dae7: je 0x40db93
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040db93;
    goto bb_0040daed;
}
bb_0040db93: {
    // 0x0040db93: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040daed: {
    // 0x0040daed: mov ecx, dword ptr [0x5542d0]
    uint32_t t2 = mem.r32(0x005542d0u);
    ctx.ecx = static_cast<uint32_t>(t2);
    // 0x0040daf3: test ecx, ecx
    uint32_t t3 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t3);
    // 0x0040daf5: jne 0x40daff
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040daff;
    goto bb_0040daf7;
}
bb_0040daff: {
    // 0x0040daff: mov ecx, dword ptr [ecx]
    uint32_t t4 = mem.r32(ctx.ecx);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x0040db01: mov ecx, dword ptr [ecx + 0xc]
    uint32_t t5 = static_cast<uint32_t>(ctx.ecx + 0x0000000cu);
    uint32_t t6 = mem.r32(t5);
    ctx.ecx = static_cast<uint32_t>(t6);
    goto bb_0040db04;
}
bb_0040daf7: {
    // 0x0040daf7: mov ecx, dword ptr [0x767444]
    uint32_t t7 = mem.r32(0x00767444u);
    ctx.ecx = static_cast<uint32_t>(t7);
    // 0x0040dafd: jmp 0x40db04
}
bb_0040db04: {
    // 0x0040db04: mov edx, dword ptr [eax]
    uint32_t t8 = mem.r32(ctx.eax);
    ctx.edx = static_cast<uint32_t>(t8);
    // 0x0040db06: push ecx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ecx);
    // 0x0040db07: push 0
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x00000000u);
    // 0x0040db09: push eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.eax);
    // 0x0040db0a: mov eax, dword ptr [edx + 0x94]
    uint32_t t12 = static_cast<uint32_t>(ctx.edx + 0x00000094u);
    uint32_t t13 = mem.r32(t12);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0040db10: call eax
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x0040db12u);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0040db12: mov eax, dword ptr [0x76e7d4]
    uint32_t t15 = mem.r32(0x0076e7d4u);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x0040db17: test eax, eax
    uint32_t t16 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    // 0x0040db19: je 0x40db93
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040db93;
}
{
    // 0x0040db1b: mov ecx, dword ptr [0x5542d4]
    uint32_t t17 = mem.r32(0x005542d4u);
    ctx.ecx = static_cast<uint32_t>(t17);
    // 0x0040db21: test ecx, ecx
    uint32_t t18 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    // 0x0040db23: je 0x40db2a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040db2a;
    goto bb_0040db25;
}
bb_0040db2a: {
    // 0x0040db2a: mov edx, dword ptr [eax]
    uint32_t t19 = mem.r32(ctx.eax);
    ctx.edx = static_cast<uint32_t>(t19);
    // 0x0040db2c: push ecx
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, ctx.ecx);
    // 0x0040db2d: push 1
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x00000001u);
    // 0x0040db2f: push eax
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, ctx.eax);
    // 0x0040db30: mov eax, dword ptr [edx + 0x94]
    uint32_t t23 = static_cast<uint32_t>(ctx.edx + 0x00000094u);
    uint32_t t24 = mem.r32(t23);
    ctx.eax = static_cast<uint32_t>(t24);
    // 0x0040db36: call eax
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x0040db38u);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0040db38: mov ecx, dword ptr [0x76e7d4]
    uint32_t t26 = mem.r32(0x0076e7d4u);
    ctx.ecx = static_cast<uint32_t>(t26);
    // 0x0040db3e: test ecx, ecx
    uint32_t t27 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t27);
    // 0x0040db40: je 0x40db93
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040db93;
    goto bb_0040db42;
}
bb_0040db25: {
    // 0x0040db25: mov ecx, dword ptr [ecx]
    uint32_t t28 = mem.r32(ctx.ecx);
    ctx.ecx = static_cast<uint32_t>(t28);
    // 0x0040db27: mov ecx, dword ptr [ecx + 0xc]
    uint32_t t29 = static_cast<uint32_t>(ctx.ecx + 0x0000000cu);
    uint32_t t30 = mem.r32(t29);
    ctx.ecx = static_cast<uint32_t>(t30);
    goto bb_0040db2a;
}
bb_0040db42: {
    // 0x0040db42: mov eax, dword ptr [0x5542d8]
    uint32_t t31 = mem.r32(0x005542d8u);
    ctx.eax = static_cast<uint32_t>(t31);
    // 0x0040db47: test eax, eax
    uint32_t t32 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t32);
    // 0x0040db49: je 0x40db50
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040db50;
    goto bb_0040db4b;
}
bb_0040db50: {
    // 0x0040db50: mov edx, dword ptr [ecx]
    uint32_t t33 = mem.r32(ctx.ecx);
    ctx.edx = static_cast<uint32_t>(t33);
    // 0x0040db52: push eax
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, ctx.eax);
    // 0x0040db53: mov eax, dword ptr [edx + 0x94]
    uint32_t t35 = static_cast<uint32_t>(ctx.edx + 0x00000094u);
    uint32_t t36 = mem.r32(t35);
    ctx.eax = static_cast<uint32_t>(t36);
    // 0x0040db59: push 2
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, 0x00000002u);
    // 0x0040db5b: push ecx
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, ctx.ecx);
    // 0x0040db5c: call eax
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, 0x0040db5eu);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0040db5e: cmp dword ptr [0x76e7d4], 0
    uint32_t t40 = mem.r32(0x0076e7d4u);
    uint32_t t41 = static_cast<uint32_t>(t40 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t40, 0x00000000u, t41);
    // 0x0040db65: je 0x40db93
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040db93;
    goto bb_0040db67;
}
bb_0040db4b: {
    // 0x0040db4b: mov edx, dword ptr [eax]
    uint32_t t42 = mem.r32(ctx.eax);
    ctx.edx = static_cast<uint32_t>(t42);
    // 0x0040db4d: mov eax, dword ptr [edx + 0xc]
    uint32_t t43 = static_cast<uint32_t>(ctx.edx + 0x0000000cu);
    uint32_t t44 = mem.r32(t43);
    ctx.eax = static_cast<uint32_t>(t44);
    goto bb_0040db50;
}
bb_0040db67: {
    // 0x0040db67: mov eax, dword ptr [0x767448]
    uint32_t t45 = mem.r32(0x00767448u);
    ctx.eax = static_cast<uint32_t>(t45);
    // 0x0040db6c: cmp dword ptr [eax + 4], 0
    uint32_t t46 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t47 = mem.r32(t46);
    uint32_t t48 = static_cast<uint32_t>(t47 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t47, 0x00000000u, t48);
    // 0x0040db70: je 0x40db93
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040db93;
}
{
    // 0x0040db72: mov eax, dword ptr [eax + 4]
    uint32_t t49 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t50 = mem.r32(t49);
    ctx.eax = static_cast<uint32_t>(t50);
    // 0x0040db75: fld1
    ctx.fpu_push(1.0);
    // 0x0040db77: mov ecx, dword ptr [eax]
    uint32_t t51 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t51);
    // 0x0040db79: mov edx, dword ptr [ecx + 0xac]
    uint32_t t52 = static_cast<uint32_t>(ctx.ecx + 0x000000acu);
    uint32_t t53 = mem.r32(t52);
    ctx.edx = static_cast<uint32_t>(t53);
    // 0x0040db7f: push 0
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, 0x00000000u);
    // 0x0040db81: push ecx
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, ctx.ecx);
    // 0x0040db82: fstp dword ptr [esp]
    double t56 = ctx.fpu_st(0);
    mem.wf32(ctx.esp, static_cast<float>(t56));
    ctx.fpu_pop();
    // 0x0040db85: push 0xff000000
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, 0xff000000u);
    // 0x0040db8a: push 3
    uint32_t t58 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    mem.w32(t58, 0x00000003u);
    // 0x0040db8c: push 0
    uint32_t t59 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    mem.w32(t59, 0x00000000u);
    // 0x0040db8e: push 0
    uint32_t t60 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t60);
    mem.w32(t60, 0x00000000u);
    // 0x0040db90: push eax
    uint32_t t61 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    mem.w32(t61, ctx.eax);
    // 0x0040db91: call edx
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, 0x0040db93u);
    call_indirect(ctx, mem, ctx.edx);
    goto bb_0040db93;
}
}

// sub_0040dba0 | subsystem=Core/Windows | canonical | 11 blocks | 53 insns
void sub_0040dba0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040dba0: mov eax, dword ptr [0x76e7d4]
    uint32_t t0 = mem.r32(0x0076e7d4u);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x0040dba5: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
    // 0x0040dba6: xor esi, esi
    uint32_t t2 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.esi = static_cast<uint32_t>(t2);
    // 0x0040dba8: cmp eax, esi
    uint32_t t3 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t3);
    // 0x0040dbaa: push edi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.edi);
    // 0x0040dbab: je 0x40dbee
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040dbee;
    goto bb_0040dbad;
}
bb_0040dbee: {
    // 0x0040dbee: cmp dword ptr [0x76e68c], 1
    uint32_t t5 = mem.r32(0x0076e68cu);
    uint32_t t6 = static_cast<uint32_t>(t5 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t5, 0x00000001u, t6);
    // 0x0040dbf5: jne 0x40dc02
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040dc02;
    goto bb_0040dbf7;
}
bb_0040dbad: {
    // 0x0040dbad: mov edx, dword ptr [0x767444]
    uint32_t t7 = mem.r32(0x00767444u);
    ctx.edx = static_cast<uint32_t>(t7);
    // 0x0040dbb3: mov ecx, dword ptr [eax]
    uint32_t t8 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t8);
    // 0x0040dbb5: push edx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.edx);
    // 0x0040dbb6: push esi
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.esi);
    // 0x0040dbb7: push eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.eax);
    // 0x0040dbb8: mov eax, dword ptr [ecx + 0x94]
    uint32_t t12 = static_cast<uint32_t>(ctx.ecx + 0x00000094u);
    uint32_t t13 = mem.r32(t12);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0040dbbe: call eax
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x0040dbc0u);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0040dbc0: mov eax, dword ptr [0x76e7d4]
    uint32_t t15 = mem.r32(0x0076e7d4u);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x0040dbc5: cmp eax, esi
    uint32_t t16 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t16);
    // 0x0040dbc7: je 0x40dbee
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040dbee;
    goto bb_0040dbc9;
}
bb_0040dc02: {
    // 0x0040dc02: mov edi, dword ptr [0x5550a8]
    uint32_t t17 = mem.r32(0x005550a8u);
    ctx.edi = static_cast<uint32_t>(t17);
    // 0x0040dc08: cmp edi, esi
    uint32_t t18 = static_cast<uint32_t>(ctx.edi - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.esi, t18);
    // 0x0040dc0a: je 0x40dc19
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040dc19;
    goto bb_0040dc0c;
}
bb_0040dbf7: {
    // 0x0040dbf7: push 0x5550c4
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x005550c4u);
    // 0x0040dbfc: call dword ptr [0x51b078]
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x0040dc02u);
    hle_iat_call(ctx, mem, 0x0051b078u);
    goto bb_0040dc02;
}
bb_0040dbc9: {
    // 0x0040dbc9: mov ecx, dword ptr [eax]
    uint32_t t21 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t21);
    // 0x0040dbcb: mov edx, dword ptr [ecx + 0x94]
    uint32_t t22 = static_cast<uint32_t>(ctx.ecx + 0x00000094u);
    uint32_t t23 = mem.r32(t22);
    ctx.edx = static_cast<uint32_t>(t23);
    // 0x0040dbd1: push esi
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, ctx.esi);
    // 0x0040dbd2: push 1
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x00000001u);
    // 0x0040dbd4: push eax
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, ctx.eax);
    // 0x0040dbd5: call edx
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x0040dbd7u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040dbd7: mov eax, dword ptr [0x76e7d4]
    uint32_t t28 = mem.r32(0x0076e7d4u);
    ctx.eax = static_cast<uint32_t>(t28);
    // 0x0040dbdc: cmp eax, esi
    uint32_t t29 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t29);
    // 0x0040dbde: je 0x40dbee
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040dbee;
    goto bb_0040dbe0;
}
bb_0040dc19: {
    // 0x0040dc19: cmp dword ptr [0x76e68c], 1
    uint32_t t30 = mem.r32(0x0076e68cu);
    uint32_t t31 = static_cast<uint32_t>(t30 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t30, 0x00000001u, t31);
    // 0x0040dc20: pop edi
    uint32_t t32 = ctx.esp;
    uint32_t t33 = mem.r32(t32);
    uint32_t t34 = static_cast<uint32_t>(t32 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    ctx.edi = static_cast<uint32_t>(t33);
    // 0x0040dc21: mov dword ptr [0x5550b4], esi
    mem.w32(0x005550b4u, ctx.esi);
    // 0x0040dc27: mov dword ptr [0x5550b8], esi
    mem.w32(0x005550b8u, ctx.esi);
    // 0x0040dc2d: mov dword ptr [0x5550bc], esi
    mem.w32(0x005550bcu, ctx.esi);
    // 0x0040dc33: mov dword ptr [0x5550c0], esi
    mem.w32(0x005550c0u, ctx.esi);
    // 0x0040dc39: pop esi
    uint32_t t35 = ctx.esp;
    uint32_t t36 = mem.r32(t35);
    uint32_t t37 = static_cast<uint32_t>(t35 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    ctx.esi = static_cast<uint32_t>(t36);
    // 0x0040dc3a: jne 0x40dc47
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040dc47;
    goto bb_0040dc3c;
}
bb_0040dc0c: {
    // 0x0040dc0c: push ebx
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, ctx.ebx);
    // 0x0040dc0d: mov ebx, dword ptr [0x5550ac]
    uint32_t t39 = mem.r32(0x005550acu);
    ctx.ebx = static_cast<uint32_t>(t39);
    // 0x0040dc13: call 0x414e20
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, 0x0040dc18u);
    sub_00414e20(ctx, mem);
    // 0x0040dc18: pop ebx
    uint32_t t41 = ctx.esp;
    uint32_t t42 = mem.r32(t41);
    uint32_t t43 = static_cast<uint32_t>(t41 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    ctx.ebx = static_cast<uint32_t>(t42);
    goto bb_0040dc19;
}
bb_0040dbe0: {
    // 0x0040dbe0: mov ecx, dword ptr [eax]
    uint32_t t44 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t44);
    // 0x0040dbe2: mov edx, dword ptr [ecx + 0x94]
    uint32_t t45 = static_cast<uint32_t>(ctx.ecx + 0x00000094u);
    uint32_t t46 = mem.r32(t45);
    ctx.edx = static_cast<uint32_t>(t46);
    // 0x0040dbe8: push esi
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, ctx.esi);
    // 0x0040dbe9: push 2
    uint32_t t48 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    mem.w32(t48, 0x00000002u);
    // 0x0040dbeb: push eax
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, ctx.eax);
    // 0x0040dbec: call edx
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, 0x0040dbeeu);
    call_indirect(ctx, mem, ctx.edx);
    goto bb_0040dbee;
}
bb_0040dc47: {
    // 0x0040dc47: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040dc3c: {
    // 0x0040dc3c: push 0x5550c4
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, 0x005550c4u);
    // 0x0040dc41: call dword ptr [0x51b070]
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, 0x0040dc47u);
    hle_iat_call(ctx, mem, 0x0051b070u);
    goto bb_0040dc47;
}
}

// sub_0040dc50 | subsystem=Core/Windows | canonical | 22 blocks | 126 insns
void sub_0040dc50(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040dc50: sub esp, 0xc
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x0000000cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x0000000cu, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x0040dc53: push ebx
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebx);
    // 0x0040dc54: push ebp
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebp);
    // 0x0040dc55: push esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.esi);
    // 0x0040dc56: xor esi, esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    ctx.esi = static_cast<uint32_t>(t4);
    // 0x0040dc58: cmp dword ptr [0x76e664], esi
    uint32_t t5 = mem.r32(0x0076e664u);
    uint32_t t6 = static_cast<uint32_t>(t5 - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t5, ctx.esi, t6);
    // 0x0040dc5e: push edi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.edi);
    // 0x0040dc5f: je 0x40ddc2
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ddc2;
    goto bb_0040dc65;
}
bb_0040ddc2: {
    // 0x0040ddc2: pop edi
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.edi = static_cast<uint32_t>(t9);
    // 0x0040ddc3: pop esi
    uint32_t t11 = ctx.esp;
    uint32_t t12 = mem.r32(t11);
    uint32_t t13 = static_cast<uint32_t>(t11 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    ctx.esi = static_cast<uint32_t>(t12);
    // 0x0040ddc4: pop ebp
    uint32_t t14 = ctx.esp;
    uint32_t t15 = mem.r32(t14);
    uint32_t t16 = static_cast<uint32_t>(t14 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    ctx.ebp = static_cast<uint32_t>(t15);
    // 0x0040ddc5: pop ebx
    uint32_t t17 = ctx.esp;
    uint32_t t18 = mem.r32(t17);
    uint32_t t19 = static_cast<uint32_t>(t17 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    ctx.ebx = static_cast<uint32_t>(t18);
    // 0x0040ddc6: add esp, 0xc
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t20);
    ctx.esp = static_cast<uint32_t>(t20);
    // 0x0040ddc9: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040dc65: {
    // 0x0040dc65: lea edi, [esp + 0x10]
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    ctx.edi = static_cast<uint32_t>(t21);
    // 0x0040dc69: call 0x4bf1d0
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x0040dc6eu);
    sub_004bf1d0(ctx, mem);
    // 0x0040dc6e: mov eax, dword ptr [0x76e7d4]
    uint32_t t23 = mem.r32(0x0076e7d4u);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x0040dc73: cmp eax, esi
    uint32_t t24 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t24);
    // 0x0040dc75: je 0x40dcf5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040dcf5;
    goto bb_0040dc77;
}
bb_0040dcf5: {
    // 0x0040dcf5: cmp dword ptr [0x76e68c], 1
    uint32_t t25 = mem.r32(0x0076e68cu);
    uint32_t t26 = static_cast<uint32_t>(t25 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t25, 0x00000001u, t26);
    // 0x0040dcfc: mov ebp, dword ptr [0x51b078]
    uint32_t t27 = mem.r32(0x0051b078u);
    ctx.ebp = static_cast<uint32_t>(t27);
    // 0x0040dd02: jne 0x40dd0b
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040dd0b;
    goto bb_0040dd04;
}
bb_0040dc77: {
    // 0x0040dc77: mov ecx, dword ptr [0x5542dc]
    uint32_t t28 = mem.r32(0x005542dcu);
    ctx.ecx = static_cast<uint32_t>(t28);
    // 0x0040dc7d: cmp ecx, esi
    uint32_t t29 = static_cast<uint32_t>(ctx.ecx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.esi, t29);
    // 0x0040dc7f: jne 0x40dc89
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040dc89;
    goto bb_0040dc81;
}
bb_0040dd0b: {
    // 0x0040dd0b: mov edi, dword ptr [0x5550a8]
    uint32_t t30 = mem.r32(0x005550a8u);
    ctx.edi = static_cast<uint32_t>(t30);
    // 0x0040dd11: cmp edi, esi
    uint32_t t31 = static_cast<uint32_t>(ctx.edi - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.esi, t31);
    // 0x0040dd13: je 0x40dd20
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040dd20;
    goto bb_0040dd15;
}
bb_0040dd04: {
    // 0x0040dd04: push 0x5550c4
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x005550c4u);
    // 0x0040dd09: call ebp
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x0040dd0bu);
    call_indirect(ctx, mem, ctx.ebp);
    goto bb_0040dd0b;
}
bb_0040dc89: {
    // 0x0040dc89: mov ecx, dword ptr [ecx]
    uint32_t t34 = mem.r32(ctx.ecx);
    ctx.ecx = static_cast<uint32_t>(t34);
    // 0x0040dc8b: mov ecx, dword ptr [ecx + 0xc]
    uint32_t t35 = static_cast<uint32_t>(ctx.ecx + 0x0000000cu);
    uint32_t t36 = mem.r32(t35);
    ctx.ecx = static_cast<uint32_t>(t36);
    goto bb_0040dc8e;
}
bb_0040dc81: {
    // 0x0040dc81: mov ecx, dword ptr [0x767444]
    uint32_t t37 = mem.r32(0x00767444u);
    ctx.ecx = static_cast<uint32_t>(t37);
    // 0x0040dc87: jmp 0x40dc8e
    goto bb_0040dc8e;
}
bb_0040dd20: {
    // 0x0040dd20: cmp dword ptr [0x76e68c], 1
    uint32_t t38 = mem.r32(0x0076e68cu);
    uint32_t t39 = static_cast<uint32_t>(t38 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t38, 0x00000001u, t39);
    // 0x0040dd27: mov dword ptr [0x5550b4], esi
    mem.w32(0x005550b4u, ctx.esi);
    // 0x0040dd2d: mov dword ptr [0x5550b8], esi
    mem.w32(0x005550b8u, ctx.esi);
    // 0x0040dd33: mov dword ptr [0x5550bc], esi
    mem.w32(0x005550bcu, ctx.esi);
    // 0x0040dd39: mov dword ptr [0x5550c0], esi
    mem.w32(0x005550c0u, ctx.esi);
    // 0x0040dd3f: mov esi, dword ptr [0x51b070]
    uint32_t t40 = mem.r32(0x0051b070u);
    ctx.esi = static_cast<uint32_t>(t40);
    // 0x0040dd45: jne 0x40dd4e
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040dd4e;
    goto bb_0040dd47;
}
bb_0040dd15: {
    // 0x0040dd15: mov ebx, dword ptr [0x5550ac]
    uint32_t t41 = mem.r32(0x005550acu);
    ctx.ebx = static_cast<uint32_t>(t41);
    // 0x0040dd1b: call 0x414e20
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, 0x0040dd20u);
    sub_00414e20(ctx, mem);
    goto bb_0040dd20;
}
bb_0040dc8e: {
    // 0x0040dc8e: mov edx, dword ptr [eax]
    uint32_t t43 = mem.r32(ctx.eax);
    ctx.edx = static_cast<uint32_t>(t43);
    // 0x0040dc90: push ecx
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, ctx.ecx);
    // 0x0040dc91: push esi
    uint32_t t45 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    mem.w32(t45, ctx.esi);
    // 0x0040dc92: push eax
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, ctx.eax);
    // 0x0040dc93: mov eax, dword ptr [edx + 0x94]
    uint32_t t47 = static_cast<uint32_t>(ctx.edx + 0x00000094u);
    uint32_t t48 = mem.r32(t47);
    ctx.eax = static_cast<uint32_t>(t48);
    // 0x0040dc99: call eax
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, 0x0040dc9bu);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0040dc9b: mov eax, dword ptr [0x76e7d4]
    uint32_t t50 = mem.r32(0x0076e7d4u);
    ctx.eax = static_cast<uint32_t>(t50);
    // 0x0040dca0: cmp eax, esi
    uint32_t t51 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t51);
    // 0x0040dca2: je 0x40dcf5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040dcf5;
    goto bb_0040dca4;
}
bb_0040dd4e: {
    // 0x0040dd4e: mov eax, dword ptr [0x5542d0]
    uint32_t t52 = mem.r32(0x005542d0u);
    ctx.eax = static_cast<uint32_t>(t52);
    // 0x0040dd53: xor ebx, ebx
    uint32_t t53 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t53);
    ctx.ebx = static_cast<uint32_t>(t53);
    // 0x0040dd55: push ebx
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, ctx.ebx);
    // 0x0040dd56: push ebx
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, ctx.ebx);
    // 0x0040dd57: push -1
    uint32_t t56 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    mem.w32(t56, 0xffffffffu);
    // 0x0040dd59: push 0x1e0
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, 0x000001e0u);
    // 0x0040dd5e: push 0x280
    uint32_t t58 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    mem.w32(t58, 0x00000280u);
    // 0x0040dd63: push ebx
    uint32_t t59 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    mem.w32(t59, ctx.ebx);
    // 0x0040dd64: push ebx
    uint32_t t60 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t60);
    mem.w32(t60, ctx.ebx);
    // 0x0040dd65: push 0x1e0
    uint32_t t61 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    mem.w32(t61, 0x000001e0u);
    // 0x0040dd6a: push ebx
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, ctx.ebx);
    // 0x0040dd6b: push ebx
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, ctx.ebx);
    // 0x0040dd6c: push eax
    uint32_t t64 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    mem.w32(t64, ctx.eax);
    // 0x0040dd6d: push ebx
    uint32_t t65 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t65);
    mem.w32(t65, ctx.ebx);
    // 0x0040dd6e: mov edx, 0x280
    ctx.edx = static_cast<uint32_t>(0x00000280u);
    // 0x0040dd73: call 0x415580
    uint32_t t66 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    mem.w32(t66, 0x0040dd78u);
    sub_00415580(ctx, mem);
    // 0x0040dd78: add esp, 0x30
    uint32_t t67 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000030u, t67);
    ctx.esp = static_cast<uint32_t>(t67);
    // 0x0040dd7b: push 0x5550c4
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, 0x005550c4u);
    // 0x0040dd80: call ebp
    uint32_t t69 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    mem.w32(t69, 0x0040dd82u);
    call_indirect(ctx, mem, ctx.ebp);
    // 0x0040dd82: mov eax, dword ptr [0x5550a8]
    uint32_t t70 = mem.r32(0x005550a8u);
    ctx.eax = static_cast<uint32_t>(t70);
    // 0x0040dd87: call 0x4c04e0
    uint32_t t71 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t71);
    mem.w32(t71, 0x0040dd8cu);
    sub_004c04e0(ctx, mem);
    // 0x0040dd8c: push 0x5550c4
    uint32_t t72 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    mem.w32(t72, 0x005550c4u);
    // 0x0040dd91: call esi
    uint32_t t73 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    mem.w32(t73, 0x0040dd93u);
    call_indirect(ctx, mem, ctx.esi);
    // 0x0040dd93: lea edi, [esp + 0x10]
    uint32_t t74 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    ctx.edi = static_cast<uint32_t>(t74);
    // 0x0040dd97: call 0x4bf220
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, 0x0040dd9cu);
    sub_004bf220(ctx, mem);
    // 0x0040dd9c: xor esi, esi
    uint32_t t76 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t76);
    ctx.esi = static_cast<uint32_t>(t76);
    // 0x0040dd9e: mov edi, edi
    ctx.edi = static_cast<uint32_t>(ctx.edi);
    goto bb_0040dda0;
}
bb_0040dd47: {
    // 0x0040dd47: push 0x5550c4
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, 0x005550c4u);
    // 0x0040dd4c: call esi
    uint32_t t78 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    mem.w32(t78, 0x0040dd4eu);
    call_indirect(ctx, mem, ctx.esi);
    goto bb_0040dd4e;
}
bb_0040dca4: {
    // 0x0040dca4: mov ecx, dword ptr [eax]
    uint32_t t79 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t79);
    // 0x0040dca6: mov edx, dword ptr [ecx + 0x94]
    uint32_t t80 = static_cast<uint32_t>(ctx.ecx + 0x00000094u);
    uint32_t t81 = mem.r32(t80);
    ctx.edx = static_cast<uint32_t>(t81);
    // 0x0040dcac: push esi
    uint32_t t82 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t82);
    mem.w32(t82, ctx.esi);
    // 0x0040dcad: push 1
    uint32_t t83 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t83);
    mem.w32(t83, 0x00000001u);
    // 0x0040dcaf: push eax
    uint32_t t84 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    mem.w32(t84, ctx.eax);
    // 0x0040dcb0: call edx
    uint32_t t85 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t85);
    mem.w32(t85, 0x0040dcb2u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040dcb2: mov eax, dword ptr [0x76e7d4]
    uint32_t t86 = mem.r32(0x0076e7d4u);
    ctx.eax = static_cast<uint32_t>(t86);
    // 0x0040dcb7: cmp eax, esi
    uint32_t t87 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t87);
    // 0x0040dcb9: je 0x40dcf5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040dcf5;
    goto bb_0040dcbb;
}
bb_0040dda0: {
    // 0x0040dda0: mov eax, dword ptr [esp + esi*4 + 0x10]
    uint32_t t88 = recomp_detail::shl<uint32_t>(ctx.esi, 0x00000002u);
    uint32_t t89 = static_cast<uint32_t>(ctx.esp + t88);
    uint32_t t90 = static_cast<uint32_t>(t89 + 0x00000010u);
    uint32_t t91 = mem.r32(t90);
    ctx.eax = static_cast<uint32_t>(t91);
    // 0x0040dda4: cmp eax, ebx
    uint32_t t92 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t92);
    // 0x0040dda6: je 0x40ddb4
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ddb4;
    goto bb_0040dda8;
}
bb_0040dcbb: {
    // 0x0040dcbb: mov ecx, dword ptr [eax]
    uint32_t t93 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t93);
    // 0x0040dcbd: mov edx, dword ptr [ecx + 0x94]
    uint32_t t94 = static_cast<uint32_t>(ctx.ecx + 0x00000094u);
    uint32_t t95 = mem.r32(t94);
    ctx.edx = static_cast<uint32_t>(t95);
    // 0x0040dcc3: push esi
    uint32_t t96 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    mem.w32(t96, ctx.esi);
    // 0x0040dcc4: push 2
    uint32_t t97 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t97);
    mem.w32(t97, 0x00000002u);
    // 0x0040dcc6: push eax
    uint32_t t98 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t98);
    mem.w32(t98, ctx.eax);
    // 0x0040dcc7: call edx
    uint32_t t99 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t99);
    mem.w32(t99, 0x0040dcc9u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040dcc9: cmp dword ptr [0x76e7d4], esi
    uint32_t t100 = mem.r32(0x0076e7d4u);
    uint32_t t101 = static_cast<uint32_t>(t100 - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t100, ctx.esi, t101);
    // 0x0040dccf: je 0x40dcf5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040dcf5;
    goto bb_0040dcd1;
}
bb_0040ddb4: {
    // 0x0040ddb4: add esi, 1
    uint32_t t102 = static_cast<uint32_t>(ctx.esi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000001u, t102);
    ctx.esi = static_cast<uint32_t>(t102);
    // 0x0040ddb7: cmp esi, 3
    uint32_t t103 = static_cast<uint32_t>(ctx.esi - 0x00000003u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00000003u, t103);
    // 0x0040ddba: jb 0x40dda0
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0040dda0;
    goto bb_0040ddbc;
}
bb_0040dda8: {
    // 0x0040dda8: mov ecx, dword ptr [eax]
    uint32_t t104 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t104);
    // 0x0040ddaa: mov edx, dword ptr [ecx + 8]
    uint32_t t105 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t106 = mem.r32(t105);
    ctx.edx = static_cast<uint32_t>(t106);
    // 0x0040ddad: push eax
    uint32_t t107 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t107);
    mem.w32(t107, ctx.eax);
    // 0x0040ddae: call edx
    uint32_t t108 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t108);
    mem.w32(t108, 0x0040ddb0u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040ddb0: mov dword ptr [esp + esi*4 + 0x10], ebx
    uint32_t t109 = recomp_detail::shl<uint32_t>(ctx.esi, 0x00000002u);
    uint32_t t110 = static_cast<uint32_t>(ctx.esp + t109);
    uint32_t t111 = static_cast<uint32_t>(t110 + 0x00000010u);
    mem.w32(t111, ctx.ebx);
    goto bb_0040ddb4;
}
bb_0040dcd1: {
    // 0x0040dcd1: mov eax, dword ptr [0x767448]
    uint32_t t112 = mem.r32(0x00767448u);
    ctx.eax = static_cast<uint32_t>(t112);
    // 0x0040dcd6: cmp dword ptr [eax + 4], esi
    uint32_t t113 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t114 = mem.r32(t113);
    uint32_t t115 = static_cast<uint32_t>(t114 - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t114, ctx.esi, t115);
    // 0x0040dcd9: je 0x40dcf5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040dcf5;
    goto bb_0040dcdb;
}
bb_0040ddbc: {
    // 0x0040ddbc: mov dword ptr [0x76e664], ebx
    mem.w32(0x0076e664u, ctx.ebx);
    goto bb_0040ddc2;
}
bb_0040dcdb: {
    // 0x0040dcdb: mov eax, dword ptr [eax + 4]
    uint32_t t116 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t117 = mem.r32(t116);
    ctx.eax = static_cast<uint32_t>(t117);
    // 0x0040dcde: fld1
    ctx.fpu_push(1.0);
    // 0x0040dce0: mov ecx, dword ptr [eax]
    uint32_t t118 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t118);
    // 0x0040dce2: mov edx, dword ptr [ecx + 0xac]
    uint32_t t119 = static_cast<uint32_t>(ctx.ecx + 0x000000acu);
    uint32_t t120 = mem.r32(t119);
    ctx.edx = static_cast<uint32_t>(t120);
    // 0x0040dce8: push esi
    uint32_t t121 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t121);
    mem.w32(t121, ctx.esi);
    // 0x0040dce9: push ecx
    uint32_t t122 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t122);
    mem.w32(t122, ctx.ecx);
    // 0x0040dcea: fstp dword ptr [esp]
    double t123 = ctx.fpu_st(0);
    mem.wf32(ctx.esp, static_cast<float>(t123));
    ctx.fpu_pop();
    // 0x0040dced: push esi
    uint32_t t124 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t124);
    mem.w32(t124, ctx.esi);
    // 0x0040dcee: push 1
    uint32_t t125 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t125);
    mem.w32(t125, 0x00000001u);
    // 0x0040dcf0: push esi
    uint32_t t126 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t126);
    mem.w32(t126, ctx.esi);
    // 0x0040dcf1: push esi
    uint32_t t127 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t127);
    mem.w32(t127, ctx.esi);
    // 0x0040dcf2: push eax
    uint32_t t128 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t128);
    mem.w32(t128, ctx.eax);
    // 0x0040dcf3: call edx
    uint32_t t129 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t129);
    mem.w32(t129, 0x0040dcf5u);
    call_indirect(ctx, mem, ctx.edx);
    goto bb_0040dcf5;
}
}

// sub_0040e390 | subsystem=Core/Windows | canonical | 21 blocks | 99 insns
void sub_0040e390(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040e390: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x0040e391: mov ecx, dword ptr [0x76e6b0]
    uint32_t t1 = mem.r32(0x0076e6b0u);
    ctx.ecx = static_cast<uint32_t>(t1);
    // 0x0040e397: mov eax, dword ptr [ecx]
    uint32_t t2 = mem.r32(ctx.ecx);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x0040e399: mov edx, dword ptr [eax + 0xc]
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    uint32_t t4 = mem.r32(t3);
    ctx.edx = static_cast<uint32_t>(t4);
    // 0x0040e39c: push ebx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ebx);
    // 0x0040e39d: push ebp
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebp);
    // 0x0040e39e: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x0040e39f: mov ebx, 1
    ctx.ebx = static_cast<uint32_t>(0x00000001u);
    // 0x0040e3a4: push edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edi);
    // 0x0040e3a5: mov dword ptr [esp + 0x10], ebx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t9, ctx.ebx);
    // 0x0040e3a9: call edx
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x0040e3abu);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040e3ab: mov ecx, dword ptr [0x76e6b0]
    uint32_t t11 = mem.r32(0x0076e6b0u);
    ctx.ecx = static_cast<uint32_t>(t11);
    // 0x0040e3b1: mov eax, dword ptr [ecx]
    uint32_t t12 = mem.r32(ctx.ecx);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0040e3b3: mov edx, dword ptr [eax + 0x10]
    uint32_t t13 = static_cast<uint32_t>(ctx.eax + 0x00000010u);
    uint32_t t14 = mem.r32(t13);
    ctx.edx = static_cast<uint32_t>(t14);
    // 0x0040e3b6: call edx
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x0040e3b8u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040e3b8: xor ebp, ebp
    uint32_t t16 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    ctx.ebp = static_cast<uint32_t>(t16);
    // 0x0040e3ba: cmp eax, ebx
    uint32_t t17 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t17);
    // 0x0040e3bc: jne 0x40e3d1
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040e3d1;
    goto bb_0040e3be;
}
bb_0040e3d1: {
    // 0x0040e3d1: test byte ptr [0x5545a7], 0x40
    uint8_t t18 = mem.r8(0x005545a7u);
    uint8_t t19 = static_cast<uint8_t>(static_cast<uint32_t>(t18) & static_cast<uint32_t>(uint8_t{0x40u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t19);
    // 0x0040e3d8: je 0x40e3e2
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040e3e2;
    goto bb_0040e3da;
}
bb_0040e3be: {
    // 0x0040e3be: mov eax, dword ptr [0x76e740]
    uint32_t t20 = mem.r32(0x0076e740u);
    ctx.eax = static_cast<uint32_t>(t20);
    // 0x0040e3c3: mov byte ptr [eax + 8], bl
    uint32_t t21 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    mem.w8(t21, recomp_detail::r8l(ctx.ebx));
    // 0x0040e3c6: mov dword ptr [eax + 4], 0x3e8
    uint32_t t22 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w32(t22, 0x000003e8u);
    // 0x0040e3cd: mov dword ptr [esp + 0x10], ebp
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t23, ctx.ebp);
    goto bb_0040e3d1;
}
bb_0040e3e2: {
    // 0x0040e3e2: test byte ptr [0x554536], 0x80
    uint8_t t24 = mem.r8(0x00554536u);
    uint8_t t25 = static_cast<uint8_t>(static_cast<uint32_t>(t24) & static_cast<uint32_t>(uint8_t{0x80u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t25);
    // 0x0040e3e9: je 0x40e410
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040e410;
    goto bb_0040e3eb;
}
bb_0040e3da: {
    // 0x0040e3da: mov dword ptr [0x76e690], ebx
    mem.w32(0x0076e690u, ctx.ebx);
    // 0x0040e3e0: jmp 0x40e40a
    goto bb_0040e40a;
}
bb_0040e410: {
    // 0x0040e410: call 0x48e0a0
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x0040e415u);
    sub_0048e0a0(ctx, mem);
    // 0x0040e415: cmp dword ptr [0x76e68c], ebx
    uint32_t t27 = mem.r32(0x0076e68cu);
    uint32_t t28 = static_cast<uint32_t>(t27 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t27, ctx.ebx, t28);
    // 0x0040e41b: jne 0x40e428
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040e428;
    goto bb_0040e41d;
}
bb_0040e3eb: {
    // 0x0040e3eb: cmp dword ptr [0x7b0988], ebp
    uint32_t t29 = mem.r32(0x007b0988u);
    uint32_t t30 = static_cast<uint32_t>(t29 - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t29, ctx.ebp, t30);
    // 0x0040e3f1: jne 0x40e404
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040e404;
    goto bb_0040e3f3;
}
bb_0040e40a: {
    // 0x0040e40a: mov dword ptr [0x7b0988], ebp
    mem.w32(0x007b0988u, ctx.ebp);
    goto bb_0040e410;
}
bb_0040e428: {
    // 0x0040e428: mov edi, dword ptr [0x5550a8]
    uint32_t t31 = mem.r32(0x005550a8u);
    ctx.edi = static_cast<uint32_t>(t31);
    // 0x0040e42e: cmp edi, ebp
    uint32_t t32 = static_cast<uint32_t>(ctx.edi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebp, t32);
    // 0x0040e430: je 0x40e442
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040e442;
    goto bb_0040e432;
}
bb_0040e41d: {
    // 0x0040e41d: push 0x5550c4
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x005550c4u);
    // 0x0040e422: call dword ptr [0x51b078]
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x0040e428u);
    hle_iat_call(ctx, mem, 0x0051b078u);
    goto bb_0040e428;
}
bb_0040e404: {
    // 0x0040e404: mov dword ptr [0x76e690], ebp
    mem.w32(0x0076e690u, ctx.ebp);
    goto bb_0040e40a;
}
bb_0040e3f3: {
    // 0x0040e3f3: mov eax, 2
    ctx.eax = static_cast<uint32_t>(0x00000002u);
    // 0x0040e3f8: mov dword ptr [0x76e690], eax
    mem.w32(0x0076e690u, ctx.eax);
    // 0x0040e3fd: mov dword ptr [0x7b0988], eax
    mem.w32(0x007b0988u, ctx.eax);
    // 0x0040e402: jmp 0x40e410
    goto bb_0040e410;
}
bb_0040e442: {
    // 0x0040e442: cmp dword ptr [0x76e68c], ebx
    uint32_t t35 = mem.r32(0x0076e68cu);
    uint32_t t36 = static_cast<uint32_t>(t35 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t35, ctx.ebx, t36);
    // 0x0040e448: mov dword ptr [0x5550b4], ebp
    mem.w32(0x005550b4u, ctx.ebp);
    // 0x0040e44e: mov dword ptr [0x5550b8], ebp
    mem.w32(0x005550b8u, ctx.ebp);
    // 0x0040e454: mov dword ptr [0x5550bc], ebp
    mem.w32(0x005550bcu, ctx.ebp);
    // 0x0040e45a: mov dword ptr [0x5550c0], ebp
    mem.w32(0x005550c0u, ctx.ebp);
    // 0x0040e460: jne 0x40e46d
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040e46d;
    goto bb_0040e462;
}
bb_0040e432: {
    // 0x0040e432: mov ebx, dword ptr [0x5550ac]
    uint32_t t37 = mem.r32(0x005550acu);
    ctx.ebx = static_cast<uint32_t>(t37);
    // 0x0040e438: call 0x414e20
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, 0x0040e43du);
    sub_00414e20(ctx, mem);
    // 0x0040e43d: mov ebx, 1
    ctx.ebx = static_cast<uint32_t>(0x00000001u);
    goto bb_0040e442;
}
bb_0040e46d: {
    // 0x0040e46d: mov eax, dword ptr [esp + 0x10]
    uint32_t t39 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t40 = mem.r32(t39);
    ctx.eax = static_cast<uint32_t>(t40);
    // 0x0040e471: call 0x432c50
    uint32_t t41 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    mem.w32(t41, 0x0040e476u);
    sub_00432c50(ctx, mem);
    // 0x0040e476: test eax, eax
    uint32_t t42 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t42);
    // 0x0040e478: jne 0x40e47e
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040e47e;
    goto bb_0040e47a;
}
bb_0040e462: {
    // 0x0040e462: push 0x5550c4
    uint32_t t43 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    mem.w32(t43, 0x005550c4u);
    // 0x0040e467: call dword ptr [0x51b070]
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, 0x0040e46du);
    hle_iat_call(ctx, mem, 0x0051b070u);
    goto bb_0040e46d;
}
bb_0040e47e: {
    // 0x0040e47e: mov esi, 0x774a18
    ctx.esi = static_cast<uint32_t>(0x00774a18u);
    // 0x0040e483: call 0x43b8d0
    uint32_t t45 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    mem.w32(t45, 0x0040e488u);
    sub_0043b8d0(ctx, mem);
    // 0x0040e488: mov eax, dword ptr [0x5542d0]
    uint32_t t46 = mem.r32(0x005542d0u);
    ctx.eax = static_cast<uint32_t>(t46);
    // 0x0040e48d: push eax
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, ctx.eax);
    // 0x0040e48e: mov dword ptr [0x5542e0], ebp
    mem.w32(0x005542e0u, ctx.ebp);
    // 0x0040e494: call 0x4330c0
    uint32_t t48 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    mem.w32(t48, 0x0040e499u);
    sub_004330c0(ctx, mem);
    // 0x0040e499: call 0x433490
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, 0x0040e49eu);
    sub_00433490(ctx, mem);
    // 0x0040e49e: call 0x433310
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, 0x0040e4a3u);
    sub_00433310(ctx, mem);
    // 0x0040e4a3: call 0x43b950
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, 0x0040e4a8u);
    sub_0043b950(ctx, mem);
    // 0x0040e4a8: call 0x4bf970
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, 0x0040e4adu);
    sub_004bf970(ctx, mem);
    // 0x0040e4ad: add dword ptr [0x7749c8], ebx
    uint32_t t53 = mem.r32(0x007749c8u);
    uint32_t t54 = static_cast<uint32_t>(t53 + ctx.ebx);
    recomp_detail::update_flags_add<uint32_t>(ctx, t53, ctx.ebx, t54);
    mem.w32(0x007749c8u, t54);
    // 0x0040e4b3: mov dword ptr [0x54d36c], 0xffff
    mem.w32(0x0054d36cu, 0x0000ffffu);
    // 0x0040e4bd: call 0x4151f0
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, 0x0040e4c2u);
    sub_004151f0(ctx, mem);
    // 0x0040e4c2: fld dword ptr [0x54f214]
    double t56 = static_cast<double>(mem.rf32(0x0054f214u));
    ctx.fpu_push(t56);
    // 0x0040e4c8: fld1
    ctx.fpu_push(1.0);
    // 0x0040e4ca: fdivrp st(1)
    double t57 = ctx.fpu_st(1);
    double t58 = ctx.fpu_st(0);
    double t59 = (t58 / t57);
    ctx.fpu_st(1) = t59;
    ctx.fpu_pop();
    // 0x0040e4cc: fadd dword ptr [0x76e668]
    double t60 = ctx.fpu_st(0);
    double t61 = static_cast<double>(mem.rf32(0x0076e668u));
    double t62 = (t60 + t61);
    ctx.fpu_st(0) = t62;
    // 0x0040e4d2: fstp dword ptr [0x76e668]
    double t63 = ctx.fpu_st(0);
    mem.wf32(0x0076e668u, static_cast<float>(t63));
    ctx.fpu_pop();
    // 0x0040e4d8: fld dword ptr [0x76e668]
    double t64 = static_cast<double>(mem.rf32(0x0076e668u));
    ctx.fpu_push(t64);
    // 0x0040e4de: fld qword ptr [0x53d7e8]
    double t65 = mem.rf64(0x0053d7e8u);
    ctx.fpu_push(t65);
    // 0x0040e4e4: fcom st(1)
    double t66 = ctx.fpu_st(0);
    double t67 = ctx.fpu_st(1);
    ctx.fpu_compare(t66, t67);
    // 0x0040e4e6: fnstsw ax
    recomp_detail::w16(ctx.eax, static_cast<uint16_t>(ctx.fpu_sw));
    // 0x0040e4e8: test ah, 0x41
    uint8_t t68 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8h(ctx.eax)) & static_cast<uint32_t>(uint8_t{0x41u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t68);
    // 0x0040e4eb: jp 0x40e4f7
    if (recomp_detail::eval_cond(ctx, Cond::P)) goto bb_0040e4f7;
    goto bb_0040e4ed;
}
bb_0040e47a: {
    // 0x0040e47a: mov dword ptr [esp + 0x10], ebp
    uint32_t t69 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t69, ctx.ebp);
    goto bb_0040e47e;
}
bb_0040e4f7: {
    // 0x0040e4f7: fstp st(1)
    double t70 = ctx.fpu_st(0);
    ctx.fpu_st(1) = t70;
    ctx.fpu_pop();
    // 0x0040e4f9: fstp st(0)
    double t71 = ctx.fpu_st(0);
    ctx.fpu_st(0) = t71;
    ctx.fpu_pop();
    goto bb_0040e4fb;
}
bb_0040e4ed: {
    // 0x0040e4ed: fsubp st(1)
    double t72 = ctx.fpu_st(1);
    double t73 = ctx.fpu_st(0);
    double t74 = (t72 - t73);
    ctx.fpu_st(1) = t74;
    ctx.fpu_pop();
    // 0x0040e4ef: fstp dword ptr [0x76e668]
    double t75 = ctx.fpu_st(0);
    mem.wf32(0x0076e668u, static_cast<float>(t75));
    ctx.fpu_pop();
    // 0x0040e4f5: jmp 0x40e4fb
}
bb_0040e4fb: {
    // 0x0040e4fb: call 0x406680
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    mem.w32(t76, 0x0040e500u);
    sub_00406680(ctx, mem);
    // 0x0040e500: call 0x4be8b0
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, 0x0040e505u);
    sub_004be8b0(ctx, mem);
    // 0x0040e505: call 0x40e220
    uint32_t t78 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    mem.w32(t78, 0x0040e50au);
    sub_0040e220(ctx, mem);
    // 0x0040e50a: mov eax, dword ptr [esp + 0x10]
    uint32_t t79 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t80 = mem.r32(t79);
    ctx.eax = static_cast<uint32_t>(t80);
    // 0x0040e50e: pop edi
    uint32_t t81 = ctx.esp;
    uint32_t t82 = mem.r32(t81);
    uint32_t t83 = static_cast<uint32_t>(t81 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t83);
    ctx.edi = static_cast<uint32_t>(t82);
    // 0x0040e50f: pop esi
    uint32_t t84 = ctx.esp;
    uint32_t t85 = mem.r32(t84);
    uint32_t t86 = static_cast<uint32_t>(t84 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t86);
    ctx.esi = static_cast<uint32_t>(t85);
    // 0x0040e510: pop ebp
    uint32_t t87 = ctx.esp;
    uint32_t t88 = mem.r32(t87);
    uint32_t t89 = static_cast<uint32_t>(t87 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t89);
    ctx.ebp = static_cast<uint32_t>(t88);
    // 0x0040e511: pop ebx
    uint32_t t90 = ctx.esp;
    uint32_t t91 = mem.r32(t90);
    uint32_t t92 = static_cast<uint32_t>(t90 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    ctx.ebx = static_cast<uint32_t>(t91);
    // 0x0040e512: pop ecx
    uint32_t t93 = ctx.esp;
    uint32_t t94 = mem.r32(t93);
    uint32_t t95 = static_cast<uint32_t>(t93 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t95);
    ctx.ecx = static_cast<uint32_t>(t94);
    // 0x0040e513: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00414e20 | subsystem=Core/Windows | canonical | 4 blocks | 23 insns
void sub_00414e20(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00414e20: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x00414e21: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x00414e23: mov esi, edi
    ctx.esi = static_cast<uint32_t>(ctx.edi);
    // 0x00414e25: call 0x4c02b0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00414e2au);
    sub_004c02b0(ctx, mem);
    // 0x00414e2a: xor edx, edx
    uint32_t t2 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.edx = static_cast<uint32_t>(t2);
    // 0x00414e2c: lea eax, [ebx - 1]
    uint32_t t3 = static_cast<uint32_t>(ctx.ebx + 0xffffffffu);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x00414e2f: cmp eax, edx
    uint32_t t4 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t4);
    // 0x00414e31: mov dword ptr [edi + 8], edx
    uint32_t t5 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    mem.w32(t5, ctx.edx);
    // 0x00414e34: mov dword ptr [edi + 0xc], ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    mem.w32(t6, ctx.ebx);
    // 0x00414e37: jle 0x414e4f
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_00414e4f;
    goto bb_00414e39;
}
bb_00414e4f: {
    // 0x00414e4f: mov dword ptr [esi], edx
    mem.w32(ctx.esi, ctx.edx);
    // 0x00414e51: mov byte ptr [esi + 4], dl
    uint32_t t7 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w8(t7, recomp_detail::r8l(ctx.edx));
    // 0x00414e54: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x00414e56: pop esi
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.esi = static_cast<uint32_t>(t9);
    // 0x00414e57: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00414e39: {
    // 0x00414e39: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x00414e3b: jmp 0x414e40
}
bb_00414e40: {
    // 0x00414e40: sub ecx, 1
    uint32_t t11 = static_cast<uint32_t>(ctx.ecx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000001u, t11);
    ctx.ecx = static_cast<uint32_t>(t11);
    // 0x00414e43: lea eax, [esi + 0x10]
    uint32_t t12 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x00414e46: mov dword ptr [esi], eax
    mem.w32(ctx.esi, ctx.eax);
    // 0x00414e48: mov byte ptr [esi + 4], dl
    uint32_t t13 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w8(t13, recomp_detail::r8l(ctx.edx));
    // 0x00414e4b: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x00414e4d: jne 0x414e40
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00414e40;
    goto bb_00414e4f;
}
}

// sub_00416f70 | subsystem=Core/Windows | canonical | 1 blocks | 54 insns
void sub_00416f70(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00416f70: sub esp, 0x30
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000030u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000030u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x00416f73: mov eax, dword ptr [esi]
    uint32_t t1 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x00416f75: push edi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.edi);
    // 0x00416f76: push -0x10
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0xfffffff0u);
    // 0x00416f78: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x00416f79: call dword ptr [0x51b2dc]
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, 0x00416f7fu);
    hle_iat_call(ctx, mem, 0x0051b2dcu);
    // 0x00416f7f: mov ecx, dword ptr [esp + 0x3c]
    uint32_t t6 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    uint32_t t7 = mem.r32(t6);
    ctx.ecx = static_cast<uint32_t>(t7);
    // 0x00416f83: mov edx, dword ptr [esp + 0x38]
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    uint32_t t9 = mem.r32(t8);
    ctx.edx = static_cast<uint32_t>(t9);
    // 0x00416f87: push ecx
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.ecx);
    // 0x00416f88: push edx
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.edx);
    // 0x00416f89: push 0
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x00000000u);
    // 0x00416f8b: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x00416f8d: push 0
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x00000000u);
    // 0x00416f8f: lea eax, [esp + 0x20]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x00416f93: push eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.eax);
    // 0x00416f94: call dword ptr [0x51b310]
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x00416f9au);
    hle_iat_call(ctx, mem, 0x0051b310u);
    // 0x00416f9a: push 0
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x00000000u);
    // 0x00416f9c: push edi
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, ctx.edi);
    // 0x00416f9d: lea ecx, [esp + 0x18]
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.ecx = static_cast<uint32_t>(t19);
    // 0x00416fa1: push ecx
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, ctx.ecx);
    // 0x00416fa2: call dword ptr [0x51b258]
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x00416fa8u);
    hle_iat_call(ctx, mem, 0x0051b258u);
    // 0x00416fa8: mov eax, dword ptr [esi]
    uint32_t t22 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t22);
    // 0x00416faa: lea edx, [esp + 8]
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.edx = static_cast<uint32_t>(t23);
    // 0x00416fae: push edx
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, ctx.edx);
    // 0x00416faf: push eax
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, ctx.eax);
    // 0x00416fb0: mov dword ptr [esp + 0x10], 0
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t26, 0x00000000u);
    // 0x00416fb8: mov dword ptr [esp + 0x14], 0
    uint32_t t27 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t27, 0x00000000u);
    // 0x00416fc0: call dword ptr [0x51b26c]
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x00416fc6u);
    hle_iat_call(ctx, mem, 0x0051b26cu);
    // 0x00416fc6: push eax
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, ctx.eax);
    // 0x00416fc7: call dword ptr [0x51b328]
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x00416fcdu);
    hle_iat_call(ctx, mem, 0x0051b328u);
    // 0x00416fcd: mov edx, dword ptr [esi]
    uint32_t t31 = mem.r32(ctx.esi);
    ctx.edx = static_cast<uint32_t>(t31);
    // 0x00416fcf: lea ecx, [esp + 0x20]
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    ctx.ecx = static_cast<uint32_t>(t32);
    // 0x00416fd3: push ecx
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, ctx.ecx);
    // 0x00416fd4: push edx
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, ctx.edx);
    // 0x00416fd5: call dword ptr [0x51b260]
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, 0x00416fdbu);
    hle_iat_call(ctx, mem, 0x0051b260u);
    // 0x00416fdb: mov eax, dword ptr [esp + 0x1c]
    uint32_t t36 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t37 = mem.r32(t36);
    ctx.eax = static_cast<uint32_t>(t37);
    // 0x00416fdf: sub eax, dword ptr [esp + 0x14]
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t39 = mem.r32(t38);
    uint32_t t40 = static_cast<uint32_t>(ctx.eax - t39);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, t39, t40);
    ctx.eax = static_cast<uint32_t>(t40);
    // 0x00416fe3: mov ecx, dword ptr [esp + 0x18]
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t42 = mem.r32(t41);
    ctx.ecx = static_cast<uint32_t>(t42);
    // 0x00416fe7: sub ecx, dword ptr [esp + 0x10]
    uint32_t t43 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t44 = mem.r32(t43);
    uint32_t t45 = static_cast<uint32_t>(ctx.ecx - t44);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, t44, t45);
    ctx.ecx = static_cast<uint32_t>(t45);
    // 0x00416feb: mov edx, dword ptr [esp + 0x24]
    uint32_t t46 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t47 = mem.r32(t46);
    ctx.edx = static_cast<uint32_t>(t47);
    // 0x00416fef: sub edx, dword ptr [esp + 0xc]
    uint32_t t48 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t49 = mem.r32(t48);
    uint32_t t50 = static_cast<uint32_t>(ctx.edx - t49);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, t49, t50);
    ctx.edx = static_cast<uint32_t>(t50);
    // 0x00416ff3: push 1
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, 0x00000001u);
    // 0x00416ff5: push eax
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, ctx.eax);
    // 0x00416ff6: mov eax, dword ptr [esp + 0x28]
    uint32_t t53 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t54 = mem.r32(t53);
    ctx.eax = static_cast<uint32_t>(t54);
    // 0x00416ffa: sub eax, dword ptr [esp + 0x10]
    uint32_t t55 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t56 = mem.r32(t55);
    uint32_t t57 = static_cast<uint32_t>(ctx.eax - t56);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, t56, t57);
    ctx.eax = static_cast<uint32_t>(t57);
    // 0x00416ffe: push ecx
    uint32_t t58 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    mem.w32(t58, ctx.ecx);
    // 0x00416fff: mov ecx, dword ptr [esi]
    uint32_t t59 = mem.r32(ctx.esi);
    ctx.ecx = static_cast<uint32_t>(t59);
    // 0x00417001: push edx
    uint32_t t60 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t60);
    mem.w32(t60, ctx.edx);
    // 0x00417002: push eax
    uint32_t t61 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    mem.w32(t61, ctx.eax);
    // 0x00417003: push ecx
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, ctx.ecx);
    // 0x00417004: call dword ptr [0x51b270]
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, 0x0041700au);
    hle_iat_call(ctx, mem, 0x0051b270u);
    // 0x0041700a: pop edi
    uint32_t t64 = ctx.esp;
    uint32_t t65 = mem.r32(t64);
    uint32_t t66 = static_cast<uint32_t>(t64 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    ctx.edi = static_cast<uint32_t>(t65);
    // 0x0041700b: add esp, 0x30
    uint32_t t67 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000030u, t67);
    ctx.esp = static_cast<uint32_t>(t67);
    // 0x0041700e: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
}

// sub_00417020 | subsystem=Core/Windows | canonical | 9 blocks | 96 insns
void sub_00417020(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00417020: sub esp, 0x21c
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x0000021cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x0000021cu, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x00417026: mov eax, dword ptr [0x54b458]
    uint32_t t1 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x0041702b: xor eax, esp
    uint32_t t2 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x0041702d: mov dword ptr [esp + 0x214], eax
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x00000214u);
    mem.w32(t3, ctx.eax);
    // 0x00417034: push 2
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x00000002u);
    // 0x00417036: push 0
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, 0x00000000u);
    // 0x00417038: call dword ptr [0x51b408]
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0041703eu);
    hle_iat_call(ctx, mem, 0x0051b408u);
    // 0x0041703e: push 0x76e698
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0076e698u);
    // 0x00417043: push 0x51b634
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x0051b634u);
    // 0x00417048: push 1
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x00000001u);
    // 0x0041704a: test eax, eax
    uint32_t t10 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    // 0x0041704c: push 0
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0x00000000u);
    // 0x0041704e: setge al
    uint8_t t12 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::GE) ? 1u : 0u);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t12));
    // 0x00417051: push 0x51b644
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x0051b644u);
    // 0x00417056: mov byte ptr [0x76e651], al
    mem.w8(0x0076e651u, recomp_detail::r8l(ctx.eax));
    // 0x0041705b: call dword ptr [0x51b400]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x00417061u);
    hle_iat_call(ctx, mem, 0x0051b400u);
    // 0x00417061: test eax, eax
    uint32_t t15 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t15);
    // 0x00417063: jl 0x41712e
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0041712e;
    goto bb_00417069;
}
bb_0041712e: {
    // 0x0041712e: call 0x417170
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x00417133u);
    sub_00417170(ctx, mem);
    // 0x00417133: xor eax, eax
    uint32_t t17 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t17);
    ctx.eax = static_cast<uint32_t>(t17);
    // 0x00417135: mov ecx, dword ptr [esp + 0x214]
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x00000214u);
    uint32_t t19 = mem.r32(t18);
    ctx.ecx = static_cast<uint32_t>(t19);
    // 0x0041713c: xor ecx, esp
    uint32_t t20 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t20);
    ctx.ecx = static_cast<uint32_t>(t20);
    // 0x0041713e: call 0x4e02f8
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x00417143u);
    hle_crt_004e02f8(ctx, mem);
    // 0x00417143: add esp, 0x21c
    uint32_t t22 = static_cast<uint32_t>(ctx.esp + 0x0000021cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000021cu, t22);
    ctx.esp = static_cast<uint32_t>(t22);
    // 0x00417149: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00417069: {
    // 0x00417069: xor eax, eax
    uint32_t t23 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t23);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x0041706b: mov dword ptr [esp + 8], eax
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    mem.w32(t24, ctx.eax);
    // 0x0041706f: mov dword ptr [esp + 0xc], eax
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t25, ctx.eax);
    // 0x00417073: mov dword ptr [esp], eax
    mem.w32(ctx.esp, ctx.eax);
    // 0x00417076: mov dword ptr [esp + 4], eax
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    mem.w32(t26, ctx.eax);
    // 0x0041707a: mov dword ptr [esp + 8], eax
    uint32_t t27 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    mem.w32(t27, ctx.eax);
    // 0x0041707e: mov dword ptr [esp + 0xc], eax
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t28, ctx.eax);
    // 0x00417082: mov eax, dword ptr [0x76e698]
    uint32_t t29 = mem.r32(0x0076e698u);
    ctx.eax = static_cast<uint32_t>(t29);
    // 0x00417087: lea edx, [esp]
    ctx.edx = static_cast<uint32_t>(ctx.esp);
    // 0x0041708a: mov dword ptr [esp], 0x10
    mem.w32(ctx.esp, 0x00000010u);
    // 0x00417091: mov dword ptr [esp + 4], 0x6f
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    mem.w32(t30, 0x0000006fu);
    // 0x00417099: mov ecx, dword ptr [eax]
    uint32_t t31 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t31);
    // 0x0041709b: push edx
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, ctx.edx);
    // 0x0041709c: push eax
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, ctx.eax);
    // 0x0041709d: mov eax, dword ptr [ecx + 0xc]
    uint32_t t34 = static_cast<uint32_t>(ctx.ecx + 0x0000000cu);
    uint32_t t35 = mem.r32(t34);
    ctx.eax = static_cast<uint32_t>(t35);
    // 0x004170a0: call eax
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, 0x004170a2u);
    call_indirect(ctx, mem, ctx.eax);
    // 0x004170a2: test eax, eax
    uint32_t t37 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t37);
    // 0x004170a4: jl 0x41712e
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0041712e;
}
{
    // 0x004170aa: mov eax, dword ptr [0x76e698]
    uint32_t t38 = mem.r32(0x0076e698u);
    ctx.eax = static_cast<uint32_t>(t38);
    // 0x004170af: mov ecx, dword ptr [eax]
    uint32_t t39 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t39);
    // 0x004170b1: mov edx, dword ptr [ecx + 0x10]
    uint32_t t40 = static_cast<uint32_t>(ctx.ecx + 0x00000010u);
    uint32_t t41 = mem.r32(t40);
    ctx.edx = static_cast<uint32_t>(t41);
    // 0x004170b4: push 0x76e69c
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, 0x0076e69cu);
    // 0x004170b9: push eax
    uint32_t t43 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    mem.w32(t43, ctx.eax);
    // 0x004170ba: call edx
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, 0x004170bcu);
    call_indirect(ctx, mem, ctx.edx);
    // 0x004170bc: test eax, eax
    uint32_t t45 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t45);
    // 0x004170be: jl 0x41712e
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0041712e;
}
{
    // 0x004170c0: mov eax, dword ptr [0x76e69c]
    uint32_t t46 = mem.r32(0x0076e69cu);
    ctx.eax = static_cast<uint32_t>(t46);
    // 0x004170c5: mov ecx, dword ptr [eax]
    uint32_t t47 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t47);
    // 0x004170c7: mov edx, dword ptr [ecx + 0x14]
    uint32_t t48 = static_cast<uint32_t>(ctx.ecx + 0x00000014u);
    uint32_t t49 = mem.r32(t48);
    ctx.edx = static_cast<uint32_t>(t49);
    // 0x004170ca: push 0x76e6a0
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, 0x0076e6a0u);
    // 0x004170cf: push 0x5353dc
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, 0x005353dcu);
    // 0x004170d4: push eax
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, ctx.eax);
    // 0x004170d5: call edx
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, 0x004170d7u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x004170d7: test eax, eax
    uint32_t t54 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t54);
    // 0x004170d9: jl 0x41712e
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0041712e;
}
{
    // 0x004170db: mov eax, dword ptr [0x76e69c]
    uint32_t t55 = mem.r32(0x0076e69cu);
    ctx.eax = static_cast<uint32_t>(t55);
    // 0x004170e0: mov ecx, dword ptr [eax]
    uint32_t t56 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t56);
    // 0x004170e2: mov edx, dword ptr [ecx + 0x14]
    uint32_t t57 = static_cast<uint32_t>(ctx.ecx + 0x00000014u);
    uint32_t t58 = mem.r32(t57);
    ctx.edx = static_cast<uint32_t>(t58);
    // 0x004170e5: push 0x76e6a4
    uint32_t t59 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    mem.w32(t59, 0x0076e6a4u);
    // 0x004170ea: push 0x535400
    uint32_t t60 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t60);
    mem.w32(t60, 0x00535400u);
    // 0x004170ef: push eax
    uint32_t t61 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    mem.w32(t61, ctx.eax);
    // 0x004170f0: call edx
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, 0x004170f2u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x004170f2: test eax, eax
    uint32_t t63 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t63);
    // 0x004170f4: jl 0x41712e
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0041712e;
}
{
    // 0x004170f6: mov eax, dword ptr [0x76e6a4]
    uint32_t t64 = mem.r32(0x0076e6a4u);
    ctx.eax = static_cast<uint32_t>(t64);
    // 0x004170fb: mov ecx, dword ptr [eax]
    uint32_t t65 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t65);
    // 0x004170fd: push 0x100
    uint32_t t66 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    mem.w32(t66, 0x00000100u);
    // 0x00417102: lea edx, [esp + 0x14]
    uint32_t t67 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.edx = static_cast<uint32_t>(t67);
    // 0x00417106: push edx
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, ctx.edx);
    // 0x00417107: push 0
    uint32_t t69 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    mem.w32(t69, 0x00000000u);
    // 0x00417109: push eax
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, ctx.eax);
    // 0x0041710a: mov eax, dword ptr [ecx + 0x10]
    uint32_t t71 = static_cast<uint32_t>(ctx.ecx + 0x00000010u);
    uint32_t t72 = mem.r32(t71);
    ctx.eax = static_cast<uint32_t>(t72);
    // 0x0041710d: call eax
    uint32_t t73 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    mem.w32(t73, 0x0041710fu);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0041710f: test eax, eax
    uint32_t t74 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t74);
    // 0x00417111: jl 0x41712e
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0041712e;
}
{
    // 0x00417113: mov eax, dword ptr [0x76e6a4]
    uint32_t t75 = mem.r32(0x0076e6a4u);
    ctx.eax = static_cast<uint32_t>(t75);
    // 0x00417118: mov ecx, dword ptr [eax]
    uint32_t t76 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t76);
    // 0x0041711a: push 0x76e6a8
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, 0x0076e6a8u);
    // 0x0041711f: lea edx, [esp + 0x14]
    uint32_t t78 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.edx = static_cast<uint32_t>(t78);
    // 0x00417123: push edx
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, ctx.edx);
    // 0x00417124: push eax
    uint32_t t80 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    mem.w32(t80, ctx.eax);
    // 0x00417125: mov eax, dword ptr [ecx + 0x14]
    uint32_t t81 = static_cast<uint32_t>(ctx.ecx + 0x00000014u);
    uint32_t t82 = mem.r32(t81);
    ctx.eax = static_cast<uint32_t>(t82);
    // 0x00417128: call eax
    uint32_t t83 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t83);
    mem.w32(t83, 0x0041712au);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0041712a: test eax, eax
    uint32_t t84 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t84);
    // 0x0041712c: jge 0x41714a
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0041714a;
    goto bb_0041712e;
}
bb_0041714a: {
    // 0x0041714a: mov ecx, dword ptr [esp + 0x214]
    uint32_t t85 = static_cast<uint32_t>(ctx.esp + 0x00000214u);
    uint32_t t86 = mem.r32(t85);
    ctx.ecx = static_cast<uint32_t>(t86);
    // 0x00417151: xor ecx, esp
    uint32_t t87 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t87);
    ctx.ecx = static_cast<uint32_t>(t87);
    // 0x00417153: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x00417158: call 0x4e02f8
    uint32_t t88 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t88);
    mem.w32(t88, 0x0041715du);
    hle_crt_004e02f8(ctx, mem);
    // 0x0041715d: add esp, 0x21c
    uint32_t t89 = static_cast<uint32_t>(ctx.esp + 0x0000021cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000021cu, t89);
    ctx.esp = static_cast<uint32_t>(t89);
    // 0x00417163: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00417170 | subsystem=Core/Windows | canonical | 13 blocks | 48 insns
void sub_00417170(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00417170: mov eax, dword ptr [0x76e6a8]
    uint32_t t0 = mem.r32(0x0076e6a8u);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x00417175: push ebx
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebx);
    // 0x00417176: xor ebx, ebx
    uint32_t t2 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.ebx = static_cast<uint32_t>(t2);
    // 0x00417178: cmp eax, ebx
    uint32_t t3 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t3);
    // 0x0041717a: je 0x41718a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041718a;
    goto bb_0041717c;
}
bb_0041718a: {
    // 0x0041718a: mov eax, dword ptr [0x76e6a4]
    uint32_t t4 = mem.r32(0x0076e6a4u);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0041718f: cmp eax, ebx
    uint32_t t5 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t5);
    // 0x00417191: je 0x4171a1
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004171a1;
    goto bb_00417193;
}
bb_0041717c: {
    // 0x0041717c: mov ecx, dword ptr [eax]
    uint32_t t6 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t6);
    // 0x0041717e: mov edx, dword ptr [ecx + 8]
    uint32_t t7 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t8 = mem.r32(t7);
    ctx.edx = static_cast<uint32_t>(t8);
    // 0x00417181: push eax
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.eax);
    // 0x00417182: call edx
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x00417184u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x00417184: mov dword ptr [0x76e6a8], ebx
    mem.w32(0x0076e6a8u, ctx.ebx);
    goto bb_0041718a;
}
bb_004171a1: {
    // 0x004171a1: mov eax, dword ptr [0x76e6a0]
    uint32_t t11 = mem.r32(0x0076e6a0u);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x004171a6: cmp eax, ebx
    uint32_t t12 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t12);
    // 0x004171a8: je 0x4171b8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004171b8;
    goto bb_004171aa;
}
bb_00417193: {
    // 0x00417193: mov ecx, dword ptr [eax]
    uint32_t t13 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t13);
    // 0x00417195: mov edx, dword ptr [ecx + 8]
    uint32_t t14 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t15 = mem.r32(t14);
    ctx.edx = static_cast<uint32_t>(t15);
    // 0x00417198: push eax
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, ctx.eax);
    // 0x00417199: call edx
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x0041719bu);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0041719b: mov dword ptr [0x76e6a4], ebx
    mem.w32(0x0076e6a4u, ctx.ebx);
    goto bb_004171a1;
}
bb_004171b8: {
    // 0x004171b8: mov eax, dword ptr [0x76e69c]
    uint32_t t18 = mem.r32(0x0076e69cu);
    ctx.eax = static_cast<uint32_t>(t18);
    // 0x004171bd: cmp eax, ebx
    uint32_t t19 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t19);
    // 0x004171bf: je 0x4171cf
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004171cf;
    goto bb_004171c1;
}
bb_004171aa: {
    // 0x004171aa: mov ecx, dword ptr [eax]
    uint32_t t20 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t20);
    // 0x004171ac: mov edx, dword ptr [ecx + 8]
    uint32_t t21 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t22 = mem.r32(t21);
    ctx.edx = static_cast<uint32_t>(t22);
    // 0x004171af: push eax
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, ctx.eax);
    // 0x004171b0: call edx
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x004171b2u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x004171b2: mov dword ptr [0x76e6a0], ebx
    mem.w32(0x0076e6a0u, ctx.ebx);
    goto bb_004171b8;
}
bb_004171cf: {
    // 0x004171cf: mov eax, dword ptr [0x76e698]
    uint32_t t25 = mem.r32(0x0076e698u);
    ctx.eax = static_cast<uint32_t>(t25);
    // 0x004171d4: cmp eax, ebx
    uint32_t t26 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t26);
    // 0x004171d6: je 0x4171e6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004171e6;
    goto bb_004171d8;
}
bb_004171c1: {
    // 0x004171c1: mov ecx, dword ptr [eax]
    uint32_t t27 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t27);
    // 0x004171c3: mov edx, dword ptr [ecx + 8]
    uint32_t t28 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t29 = mem.r32(t28);
    ctx.edx = static_cast<uint32_t>(t29);
    // 0x004171c6: push eax
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, ctx.eax);
    // 0x004171c7: call edx
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x004171c9u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x004171c9: mov dword ptr [0x76e69c], ebx
    mem.w32(0x0076e69cu, ctx.ebx);
    goto bb_004171cf;
}
bb_004171e6: {
    // 0x004171e6: cmp byte ptr [0x76e651], bl
    uint8_t t32 = mem.r8(0x0076e651u);
    uint8_t t33 = static_cast<uint8_t>(static_cast<uint32_t>(t32) - static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, t32, recomp_detail::r8l(ctx.ebx), t33);
    // 0x004171ec: je 0x4171f4
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004171f4;
    goto bb_004171ee;
}
bb_004171d8: {
    // 0x004171d8: mov ecx, dword ptr [eax]
    uint32_t t34 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t34);
    // 0x004171da: mov edx, dword ptr [ecx + 8]
    uint32_t t35 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t36 = mem.r32(t35);
    ctx.edx = static_cast<uint32_t>(t36);
    // 0x004171dd: push eax
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, ctx.eax);
    // 0x004171de: call edx
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, 0x004171e0u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x004171e0: mov dword ptr [0x76e698], ebx
    mem.w32(0x0076e698u, ctx.ebx);
    goto bb_004171e6;
}
bb_004171f4: {
    // 0x004171f4: mov byte ptr [0x76e651], bl
    mem.w8(0x0076e651u, recomp_detail::r8l(ctx.ebx));
    // 0x004171fa: pop ebx
    uint32_t t39 = ctx.esp;
    uint32_t t40 = mem.r32(t39);
    uint32_t t41 = static_cast<uint32_t>(t39 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    ctx.ebx = static_cast<uint32_t>(t40);
    // 0x004171fb: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004171ee: {
    // 0x004171ee: call dword ptr [0x51b404]
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, 0x004171f4u);
    hle_iat_call(ctx, mem, 0x0051b404u);
    goto bb_004171f4;
}
}

// sub_00417200 | subsystem=Core/Windows | canonical | 5 blocks | 37 insns
void sub_00417200(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00417200: sub esp, 0x10
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000010u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x00417203: lea eax, [esp]
    ctx.eax = static_cast<uint32_t>(ctx.esp);
    // 0x00417206: push eax
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.eax);
    // 0x00417207: call dword ptr [0x51b1f4]
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x0041720du);
    hle_iat_call(ctx, mem, 0x0051b1f4u);
    // 0x0041720d: push 0x100
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x00000100u);
    // 0x00417212: push 0
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x00000000u);
    // 0x00417214: push esi
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.esi);
    // 0x00417215: call 0x4e6340
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0041721au);
    hle_crt_004e6340(ctx, mem);
    // 0x0041721a: mov eax, dword ptr [esp + 0x20]
    uint32_t t7 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t8 = mem.r32(t7);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x0041721e: mov ecx, dword ptr [edi]
    uint32_t t9 = mem.r32(ctx.edi);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x00417220: mov ecx, dword ptr [ecx + 0x20]
    uint32_t t10 = static_cast<uint32_t>(ctx.ecx + 0x00000020u);
    uint32_t t11 = mem.r32(t10);
    ctx.ecx = static_cast<uint32_t>(t11);
    // 0x00417223: add esp, 0xc
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t12);
    ctx.esp = static_cast<uint32_t>(t12);
    // 0x00417226: lea edx, [esp]
    ctx.edx = static_cast<uint32_t>(ctx.esp);
    // 0x00417229: push edx
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, ctx.edx);
    // 0x0041722a: push eax
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, ctx.eax);
    // 0x0041722b: push edi
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.edi);
    // 0x0041722c: call ecx
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x0041722eu);
    call_indirect(ctx, mem, ctx.ecx);
    // 0x0041722e: test eax, eax
    uint32_t t17 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t17);
    // 0x00417230: jl 0x417268
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_00417268;
    goto bb_00417232;
}
bb_00417268: {
    // 0x00417268: add esp, 0x10
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t18);
    ctx.esp = static_cast<uint32_t>(t18);
    // 0x0041726b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00417232: {
    // 0x00417232: cmp word ptr [esp], 8
    uint16_t t19 = mem.r16(ctx.esp);
    uint16_t t20 = static_cast<uint16_t>(static_cast<uint32_t>(t19) - static_cast<uint32_t>(uint16_t{0x0008u}));
    recomp_detail::update_flags_sub<uint16_t>(ctx, t19, uint16_t{0x0008u}, t20);
    // 0x00417237: je 0x417242
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00417242;
    goto bb_00417239;
}
bb_00417242: {
    // 0x00417242: mov edx, dword ptr [esp + 8]
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t22 = mem.r32(t21);
    ctx.edx = static_cast<uint32_t>(t22);
    // 0x00417246: push 0x100
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x00000100u);
    // 0x0041724b: push edx
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, ctx.edx);
    // 0x0041724c: push esi
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, ctx.esi);
    // 0x0041724d: call 0x4e18d3
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x00417252u);
    hle_crt_004e18d3(ctx, mem);
    // 0x00417252: add esp, 0xc
    uint32_t t27 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t27);
    ctx.esp = static_cast<uint32_t>(t27);
    // 0x00417255: lea eax, [esp]
    ctx.eax = static_cast<uint32_t>(ctx.esp);
    // 0x00417258: push eax
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, ctx.eax);
    // 0x00417259: mov byte ptr [esi + 0xff], 0
    uint32_t t29 = static_cast<uint32_t>(ctx.esi + 0x000000ffu);
    mem.w8(t29, uint8_t{0x00u});
    // 0x00417260: call dword ptr [0x51b1f0]
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x00417266u);
    hle_iat_call(ctx, mem, 0x0051b1f0u);
    // 0x00417266: xor eax, eax
    uint32_t t31 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t31);
    ctx.eax = static_cast<uint32_t>(t31);
    goto bb_00417268;
}
bb_00417239: {
    // 0x00417239: mov eax, 0x80070057
    ctx.eax = static_cast<uint32_t>(0x80070057u);
    // 0x0041723e: add esp, 0x10
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t32);
    ctx.esp = static_cast<uint32_t>(t32);
    // 0x00417241: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0041e390 | subsystem=Core/Windows | canonical | 6 blocks | 70 insns
void sub_0041e390(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041e390: sub esp, 0x210
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000210u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000210u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x0041e396: mov eax, dword ptr [0x54b458]
    uint32_t t1 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x0041e39b: xor eax, esp
    uint32_t t2 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x0041e39d: mov dword ptr [esp + 0x208], eax
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x00000208u);
    mem.w32(t3, ctx.eax);
    // 0x0041e3a4: push ebx
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.ebx);
    // 0x0041e3a5: push esi
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.esi);
    // 0x0041e3a6: push edi
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.edi);
    // 0x0041e3a7: mov ebx, 0x5358ec
    ctx.ebx = static_cast<uint32_t>(0x005358ecu);
    // 0x0041e3ac: mov byte ptr [esp + 0xf], 0
    uint32_t t7 = static_cast<uint32_t>(ctx.esp + 0x0000000fu);
    mem.w8(t7, uint8_t{0x00u});
    // 0x0041e3b1: call 0x41fca0
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x0041e3b6u);
    sub_0041fca0(ctx, mem);
    // 0x0041e3b6: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0041e3b8: test esi, esi
    uint32_t t9 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    // 0x0041e3ba: je 0x41e448
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041e448;
    goto bb_0041e3c0;
}
bb_0041e448: {
    // 0x0041e448: mov ecx, dword ptr [esp + 0x214]
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x00000214u);
    uint32_t t11 = mem.r32(t10);
    ctx.ecx = static_cast<uint32_t>(t11);
    // 0x0041e44f: mov al, byte ptr [esp + 0xf]
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x0000000fu);
    uint8_t t13 = mem.r8(t12);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t13));
    // 0x0041e453: pop edi
    uint32_t t14 = ctx.esp;
    uint32_t t15 = mem.r32(t14);
    uint32_t t16 = static_cast<uint32_t>(t14 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    ctx.edi = static_cast<uint32_t>(t15);
    // 0x0041e454: pop esi
    uint32_t t17 = ctx.esp;
    uint32_t t18 = mem.r32(t17);
    uint32_t t19 = static_cast<uint32_t>(t17 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    ctx.esi = static_cast<uint32_t>(t18);
    // 0x0041e455: pop ebx
    uint32_t t20 = ctx.esp;
    uint32_t t21 = mem.r32(t20);
    uint32_t t22 = static_cast<uint32_t>(t20 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    ctx.ebx = static_cast<uint32_t>(t21);
    // 0x0041e456: xor ecx, esp
    uint32_t t23 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t23);
    ctx.ecx = static_cast<uint32_t>(t23);
    // 0x0041e458: call 0x4e02f8
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x0041e45du);
    hle_crt_004e02f8(ctx, mem);
    // 0x0041e45d: add esp, 0x210
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000210u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000210u, t25);
    ctx.esp = static_cast<uint32_t>(t25);
    // 0x0041e463: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0041e3c0: {
    // 0x0041e3c0: mov eax, dword ptr [esi]
    uint32_t t26 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t26);
    // 0x0041e3c2: mov edx, dword ptr [eax + 0xc]
    uint32_t t27 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    uint32_t t28 = mem.r32(t27);
    ctx.edx = static_cast<uint32_t>(t28);
    // 0x0041e3c5: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x0041e3c7: call edx
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x0041e3c9u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0041e3c9: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x0041e3cb: mov eax, dword ptr [esi]
    uint32_t t30 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t30);
    // 0x0041e3cd: mov edx, dword ptr [eax + 4]
    uint32_t t31 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t32 = mem.r32(t31);
    ctx.edx = static_cast<uint32_t>(t32);
    // 0x0041e3d0: push edi
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, ctx.edi);
    // 0x0041e3d1: lea ecx, [esp + 0x14]
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.ecx = static_cast<uint32_t>(t34);
    // 0x0041e3d5: push ecx
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, ctx.ecx);
    // 0x0041e3d6: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x0041e3d8: call edx
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, 0x0041e3dau);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0041e3da: lea eax, [esp + 0x110]
    uint32_t t37 = static_cast<uint32_t>(ctx.esp + 0x00000110u);
    ctx.eax = static_cast<uint32_t>(t37);
    // 0x0041e3e1: push eax
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, ctx.eax);
    // 0x0041e3e2: push edi
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, ctx.edi);
    // 0x0041e3e3: push 0
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, 0x00000000u);
    // 0x0041e3e5: lea edx, [esp + 0x1c]
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.edx = static_cast<uint32_t>(t41);
    // 0x0041e3e9: mov byte ptr [esp + edi + 0x1c], 0
    uint32_t t42 = static_cast<uint32_t>(ctx.esp + ctx.edi);
    uint32_t t43 = static_cast<uint32_t>(t42 + 0x0000001cu);
    mem.w8(t43, uint8_t{0x00u});
    // 0x0041e3ee: call 0x49c9f0
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, 0x0041e3f3u);
    sub_0049c9f0(ctx, mem);
    // 0x0041e3f3: add esp, 0xc
    uint32_t t45 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t45);
    ctx.esp = static_cast<uint32_t>(t45);
    // 0x0041e3f6: cmp byte ptr [esp + 0x110], 0
    uint32_t t46 = static_cast<uint32_t>(ctx.esp + 0x00000110u);
    uint8_t t47 = mem.r8(t46);
    uint8_t t48 = static_cast<uint8_t>(static_cast<uint32_t>(t47) - static_cast<uint32_t>(uint8_t{0x00u}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, t47, uint8_t{0x00u}, t48);
    // 0x0041e3fe: je 0x41e417
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041e417;
    goto bb_0041e400;
}
bb_0041e417: {
    // 0x0041e417: mov bl, byte ptr [esp + 0xf]
    uint32_t t49 = static_cast<uint32_t>(ctx.esp + 0x0000000fu);
    uint8_t t50 = mem.r8(t49);
    recomp_detail::w8l(ctx.ebx, static_cast<uint8_t>(t50));
    goto bb_0041e41b;
}
bb_0041e400: {
    // 0x0041e400: lea ecx, [esp + 0x110]
    uint32_t t51 = static_cast<uint32_t>(ctx.esp + 0x00000110u);
    ctx.ecx = static_cast<uint32_t>(t51);
    // 0x0041e407: push ecx
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, ctx.ecx);
    // 0x0041e408: call 0x4e0eb7
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, 0x0041e40du);
    hle_crt_004e0eb7(ctx, mem);
    // 0x0041e40d: add esp, 4
    uint32_t t54 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t54);
    ctx.esp = static_cast<uint32_t>(t54);
    // 0x0041e410: cmp eax, 3
    uint32_t t55 = static_cast<uint32_t>(ctx.eax - 0x00000003u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000003u, t55);
    // 0x0041e413: mov bl, 1
    recomp_detail::w8l(ctx.ebx, static_cast<uint8_t>(uint8_t{0x01u}));
    // 0x0041e415: je 0x41e41b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041e41b;
    goto bb_0041e417;
}
bb_0041e41b: {
    // 0x0041e41b: mov edx, dword ptr [esi]
    uint32_t t56 = mem.r32(ctx.esi);
    ctx.edx = static_cast<uint32_t>(t56);
    // 0x0041e41d: mov eax, dword ptr [edx + 0x14]
    uint32_t t57 = static_cast<uint32_t>(ctx.edx + 0x00000014u);
    uint32_t t58 = mem.r32(t57);
    ctx.eax = static_cast<uint32_t>(t58);
    // 0x0041e420: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x0041e422: call eax
    uint32_t t59 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    mem.w32(t59, 0x0041e424u);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0041e424: mov edx, dword ptr [esi]
    uint32_t t60 = mem.r32(ctx.esi);
    ctx.edx = static_cast<uint32_t>(t60);
    // 0x0041e426: mov eax, dword ptr [edx]
    uint32_t t61 = mem.r32(ctx.edx);
    ctx.eax = static_cast<uint32_t>(t61);
    // 0x0041e428: push 1
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, 0x00000001u);
    // 0x0041e42a: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x0041e42c: call eax
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, 0x0041e42eu);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0041e42e: mov al, bl
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(recomp_detail::r8l(ctx.ebx)));
    // 0x0041e430: pop edi
    uint32_t t64 = ctx.esp;
    uint32_t t65 = mem.r32(t64);
    uint32_t t66 = static_cast<uint32_t>(t64 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    ctx.edi = static_cast<uint32_t>(t65);
    // 0x0041e431: pop esi
    uint32_t t67 = ctx.esp;
    uint32_t t68 = mem.r32(t67);
    uint32_t t69 = static_cast<uint32_t>(t67 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    ctx.esi = static_cast<uint32_t>(t68);
    // 0x0041e432: pop ebx
    uint32_t t70 = ctx.esp;
    uint32_t t71 = mem.r32(t70);
    uint32_t t72 = static_cast<uint32_t>(t70 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    ctx.ebx = static_cast<uint32_t>(t71);
    // 0x0041e433: mov ecx, dword ptr [esp + 0x208]
    uint32_t t73 = static_cast<uint32_t>(ctx.esp + 0x00000208u);
    uint32_t t74 = mem.r32(t73);
    ctx.ecx = static_cast<uint32_t>(t74);
    // 0x0041e43a: xor ecx, esp
    uint32_t t75 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t75);
    ctx.ecx = static_cast<uint32_t>(t75);
    // 0x0041e43c: call 0x4e02f8
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    mem.w32(t76, 0x0041e441u);
    hle_crt_004e02f8(ctx, mem);
    // 0x0041e441: add esp, 0x210
    uint32_t t77 = static_cast<uint32_t>(ctx.esp + 0x00000210u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000210u, t77);
    ctx.esp = static_cast<uint32_t>(t77);
    // 0x0041e447: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0041e530 | subsystem=Core/Windows | canonical | 7 blocks | 36 insns
void sub_0041e530(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041e530: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x0041e531: call 0x4011e0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0041e536u);
    sub_004011e0(ctx, mem);
    // 0x0041e536: call 0x4015f0
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x0041e53bu);
    sub_004015f0(ctx, mem);
    // 0x0041e53b: mov esi, dword ptr [0x55413c]
    uint32_t t3 = mem.r32(0x0055413cu);
    ctx.esi = static_cast<uint32_t>(t3);
    // 0x0041e541: test esi, esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    // 0x0041e543: je 0x41e571
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041e571;
    goto bb_0041e545;
}
bb_0041e571: {
    // 0x0041e571: call 0x421820
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, 0x0041e576u);
    sub_00421820(ctx, mem);
    // 0x0041e576: mov dword ptr [0x55df14], 1
    mem.w32(0x0055df14u, 0x00000001u);
    // 0x0041e580: call 0x4dd840
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0041e585u);
    sub_004dd840(ctx, mem);
    // 0x0041e585: call 0x4ddf40
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0041e58au);
    sub_004ddf40(ctx, mem);
    // 0x0041e58a: mov ecx, dword ptr [0x76dff8]
    uint32_t t8 = mem.r32(0x0076dff8u);
    ctx.ecx = static_cast<uint32_t>(t8);
    // 0x0041e590: test ecx, ecx
    uint32_t t9 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    // 0x0041e592: je 0x41e5a6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041e5a6;
    goto bb_0041e594;
}
bb_0041e545: {
    // 0x0041e545: cmp dword ptr [esi + 0x298], 0xfff00002
    uint32_t t10 = static_cast<uint32_t>(ctx.esi + 0x00000298u);
    uint32_t t11 = mem.r32(t10);
    uint32_t t12 = static_cast<uint32_t>(t11 - 0xfff00002u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t11, 0xfff00002u, t12);
    // 0x0041e54f: mov eax, dword ptr [esi + 4]
    uint32_t t13 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t14 = mem.r32(t13);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x0041e552: mov dword ptr [0x554144], eax
    mem.w32(0x00554144u, ctx.eax);
    // 0x0041e557: lea eax, [esi + 0x298]
    uint32_t t15 = static_cast<uint32_t>(ctx.esi + 0x00000298u);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x0041e55d: je 0x41e571
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041e571;
    goto bb_0041e55f;
}
bb_0041e5a6: {
    // 0x0041e5a6: mov dword ptr [0x54c7a0], 2
    mem.w32(0x0054c7a0u, 0x00000002u);
    // 0x0041e5b0: call 0x418030
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x0041e5b5u);
    sub_00418030(ctx, mem);
    // 0x0041e5b5: call 0x401110
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x0041e5bau);
    sub_00401110(ctx, mem);
    // 0x0041e5ba: call 0x41e0c0
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x0041e5bfu);
    sub_0041e0c0(ctx, mem);
    // 0x0041e5bf: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0041e5c4: pop esi
    uint32_t t19 = ctx.esp;
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t19 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    ctx.esi = static_cast<uint32_t>(t20);
    // 0x0041e5c5: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0041e594: {
    // 0x0041e594: mov edx, dword ptr [ecx]
    uint32_t t22 = mem.r32(ctx.ecx);
    ctx.edx = static_cast<uint32_t>(t22);
    // 0x0041e596: mov eax, dword ptr [edx]
    uint32_t t23 = mem.r32(ctx.edx);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x0041e598: push 1
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x00000001u);
    // 0x0041e59a: call eax
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x0041e59cu);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0041e59c: mov dword ptr [0x76dff8], 0
    mem.w32(0x0076dff8u, 0x00000000u);
    goto bb_0041e5a6;
}
bb_0041e55f: {
    // 0x0041e55f: push eax
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, ctx.eax);
    // 0x0041e560: call 0x4bbfa0
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x0041e565u);
    sub_004bbfa0(ctx, mem);
    // 0x0041e565: add esp, 4
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t28);
    ctx.esp = static_cast<uint32_t>(t28);
    // 0x0041e568: test esi, esi
    uint32_t t29 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t29);
    // 0x0041e56a: je 0x41e571
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041e571;
}
{
    // 0x0041e56c: call 0x401110
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x0041e571u);
    sub_00401110(ctx, mem);
    goto bb_0041e571;
}
}

// sub_0041faa0 | subsystem=Core/Windows | canonical | 1 blocks | 2 insns
void sub_0041faa0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041faa0: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x0041faa2: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
}

// sub_0041fab0 | subsystem=Core/Windows | canonical | 3 blocks | 11 insns
void sub_0041fab0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041fab0: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x0041fab1: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x0041fab3: call 0x41fad0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0041fab8u);
    sub_0041fad0(ctx, mem);
    // 0x0041fab8: test byte ptr [esp + 8], 1
    uint32_t t2 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint8_t t3 = mem.r8(t2);
    uint8_t t4 = static_cast<uint8_t>(static_cast<uint32_t>(t3) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t4);
    // 0x0041fabd: je 0x41fac8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041fac8;
    goto bb_0041fabf;
}
bb_0041fac8: {
    // 0x0041fac8: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0041faca: pop esi
    uint32_t t5 = ctx.esp;
    uint32_t t6 = mem.r32(t5);
    uint32_t t7 = static_cast<uint32_t>(t5 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x0041facb: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0041fabf: {
    // 0x0041fabf: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x0041fac0: call 0x4e02f3
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x0041fac5u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0041fac5: add esp, 4
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t10);
    ctx.esp = static_cast<uint32_t>(t10);
    goto bb_0041fac8;
}
}

// sub_0041fb40 | subsystem=Core/Windows | canonical | 6 blocks | 52 insns
void sub_0041fb40(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041fb40: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x0041fb41: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x0041fb43: and esp, 0xfffffff8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xfffffff8u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x0041fb46: push esi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.esi);
    // 0x0041fb47: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0041fb49: mov eax, dword ptr [esi]
    uint32_t t3 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0041fb4b: mov edx, dword ptr [eax + 0x14]
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000014u);
    uint32_t t5 = mem.r32(t4);
    ctx.edx = static_cast<uint32_t>(t5);
    // 0x0041fb4e: push edi
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.edi);
    // 0x0041fb4f: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x0041fb51: call edx
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0041fb53u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0041fb53: lea edi, [esi + 4]
    uint32_t t8 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    ctx.edi = static_cast<uint32_t>(t8);
    // 0x0041fb56: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x0041fb58: call 0x414000
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x0041fb5du);
    sub_00414000(ctx, mem);
    // 0x0041fb5d: push ebx
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.ebx);
    // 0x0041fb5e: mov esi, 0x76e9c4
    ctx.esi = static_cast<uint32_t>(0x0076e9c4u);
    // 0x0041fb63: call 0x4db8e0
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0x0041fb68u);
    sub_004db8e0(ctx, mem);
    // 0x0041fb68: test eax, eax
    uint32_t t12 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t12);
    // 0x0041fb6a: je 0x41fb7e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041fb7e;
    goto bb_0041fb6c;
}
bb_0041fb7e: {
    // 0x0041fb7e: push 0
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x00000000u);
    // 0x0041fb80: push 0x10000080
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x10000080u);
    // 0x0041fb85: push 3
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x00000003u);
    // 0x0041fb87: push 0
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x00000000u);
    // 0x0041fb89: push 1
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x00000001u);
    // 0x0041fb8b: push 0x80000000
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x80000000u);
    // 0x0041fb90: push ebx
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, ctx.ebx);
    // 0x0041fb91: call dword ptr [0x51b054]
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x0041fb97u);
    hle_iat_call(ctx, mem, 0x0051b054u);
    // 0x0041fb97: cmp eax, -1
    uint32_t t21 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t21);
    // 0x0041fb9a: je 0x41fbc1
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041fbc1;
    goto bb_0041fb9c;
}
bb_0041fb6c: {
    // 0x0041fb6c: mov dword ptr [edi], 0
    mem.w32(ctx.edi, 0x00000000u);
    // 0x0041fb72: mov dword ptr [edi + 0x1c], 3
    uint32_t t22 = static_cast<uint32_t>(ctx.edi + 0x0000001cu);
    mem.w32(t22, 0x00000003u);
    // 0x0041fb79: mov dword ptr [edi + 0x58], eax
    uint32_t t23 = static_cast<uint32_t>(ctx.edi + 0x00000058u);
    mem.w32(t23, ctx.eax);
    // 0x0041fb7c: jmp 0x41fba5
    goto bb_0041fba5;
}
bb_0041fbc1: {
    // 0x0041fbc1: pop edi
    uint32_t t24 = ctx.esp;
    uint32_t t25 = mem.r32(t24);
    uint32_t t26 = static_cast<uint32_t>(t24 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    ctx.edi = static_cast<uint32_t>(t25);
    // 0x0041fbc2: xor eax, eax
    uint32_t t27 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t27);
    ctx.eax = static_cast<uint32_t>(t27);
    // 0x0041fbc4: pop esi
    uint32_t t28 = ctx.esp;
    uint32_t t29 = mem.r32(t28);
    uint32_t t30 = static_cast<uint32_t>(t28 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    ctx.esi = static_cast<uint32_t>(t29);
    // 0x0041fbc5: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0041fbc7: pop ebp
    uint32_t t31 = ctx.esp;
    uint32_t t32 = mem.r32(t31);
    uint32_t t33 = static_cast<uint32_t>(t31 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    ctx.ebp = static_cast<uint32_t>(t32);
    // 0x0041fbc8: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0041fb9c: {
    // 0x0041fb9c: mov dword ptr [edi], eax
    mem.w32(ctx.edi, ctx.eax);
    // 0x0041fb9e: mov dword ptr [edi + 0x1c], 0
    uint32_t t34 = static_cast<uint32_t>(ctx.edi + 0x0000001cu);
    mem.w32(t34, 0x00000000u);
}
bb_0041fba5: {
    // 0x0041fba5: xor eax, eax
    uint32_t t35 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t35);
    ctx.eax = static_cast<uint32_t>(t35);
    // 0x0041fba7: mov dword ptr [edi + 8], eax
    uint32_t t36 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    mem.w32(t36, ctx.eax);
    // 0x0041fbaa: mov dword ptr [edi + 0xc], eax
    uint32_t t37 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    mem.w32(t37, ctx.eax);
    // 0x0041fbad: mov dword ptr [edi + 0x10], eax
    uint32_t t38 = static_cast<uint32_t>(ctx.edi + 0x00000010u);
    mem.w32(t38, ctx.eax);
    // 0x0041fbb0: mov dword ptr [edi + 0x14], eax
    uint32_t t39 = static_cast<uint32_t>(ctx.edi + 0x00000014u);
    mem.w32(t39, ctx.eax);
    // 0x0041fbb3: mov dword ptr [edi + 0x18], eax
    uint32_t t40 = static_cast<uint32_t>(ctx.edi + 0x00000018u);
    mem.w32(t40, ctx.eax);
    // 0x0041fbb6: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0041fbbb: pop edi
    uint32_t t41 = ctx.esp;
    uint32_t t42 = mem.r32(t41);
    uint32_t t43 = static_cast<uint32_t>(t41 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    ctx.edi = static_cast<uint32_t>(t42);
    // 0x0041fbbc: pop esi
    uint32_t t44 = ctx.esp;
    uint32_t t45 = mem.r32(t44);
    uint32_t t46 = static_cast<uint32_t>(t44 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    ctx.esi = static_cast<uint32_t>(t45);
    // 0x0041fbbd: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0041fbbf: pop ebp
    uint32_t t47 = ctx.esp;
    uint32_t t48 = mem.r32(t47);
    uint32_t t49 = static_cast<uint32_t>(t47 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    ctx.ebp = static_cast<uint32_t>(t48);
    // 0x0041fbc0: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0041fbd0 | subsystem=Core/Windows | canonical | 11 blocks | 40 insns
void sub_0041fbd0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041fbd0: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x0041fbd1: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
    // 0x0041fbd2: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x0041fbd4: mov eax, dword ptr [esi + 0x20]
    uint32_t t2 = static_cast<uint32_t>(ctx.esi + 0x00000020u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0041fbd7: cmp eax, 2
    uint32_t t4 = static_cast<uint32_t>(ctx.eax - 0x00000002u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000002u, t4);
    // 0x0041fbda: je 0x41fc1c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041fc1c;
    goto bb_0041fbdc;
}
bb_0041fc1c: {
    // 0x0041fc1c: mov eax, dword ptr [esi + 0x2c]
    uint32_t t5 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    uint32_t t6 = mem.r32(t5);
    ctx.eax = static_cast<uint32_t>(t6);
    goto bb_0041fc1f;
}
bb_0041fbdc: {
    // 0x0041fbdc: cmp eax, 3
    uint32_t t7 = static_cast<uint32_t>(ctx.eax - 0x00000003u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000003u, t7);
    // 0x0041fbdf: jne 0x41fbfa
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0041fbfa;
    goto bb_0041fbe1;
}
bb_0041fc1f: {
    // 0x0041fc1f: pop esi
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.esi = static_cast<uint32_t>(t9);
    // 0x0041fc20: pop ecx
    uint32_t t11 = ctx.esp;
    uint32_t t12 = mem.r32(t11);
    uint32_t t13 = static_cast<uint32_t>(t11 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    ctx.ecx = static_cast<uint32_t>(t12);
    // 0x0041fc21: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0041fbfa: {
    // 0x0041fbfa: mov ecx, dword ptr [esi + 4]
    uint32_t t14 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t15 = mem.r32(t14);
    ctx.ecx = static_cast<uint32_t>(t15);
    // 0x0041fbfd: test ecx, ecx
    uint32_t t16 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    // 0x0041fbff: jne 0x41fc06
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0041fc06;
    goto bb_0041fc01;
}
bb_0041fbe1: {
    // 0x0041fbe1: mov eax, dword ptr [esi + 0x5c]
    uint32_t t17 = static_cast<uint32_t>(ctx.esi + 0x0000005cu);
    uint32_t t18 = mem.r32(t17);
    ctx.eax = static_cast<uint32_t>(t18);
    // 0x0041fbe4: mov eax, dword ptr [eax + 0x78]
    uint32_t t19 = static_cast<uint32_t>(ctx.eax + 0x00000078u);
    uint32_t t20 = mem.r32(t19);
    ctx.eax = static_cast<uint32_t>(t20);
    // 0x0041fbe7: test eax, eax
    uint32_t t21 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t21);
    // 0x0041fbe9: jne 0x41fbf1
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0041fbf1;
    goto bb_0041fbeb;
}
bb_0041fc06: {
    // 0x0041fc06: mov eax, dword ptr [esi + 0x2c]
    uint32_t t22 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    uint32_t t23 = mem.r32(t22);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x0041fc09: test eax, eax
    uint32_t t24 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t24);
    // 0x0041fc0b: jne 0x41fc1f
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0041fc1f;
    goto bb_0041fc0d;
}
bb_0041fc01: {
    // 0x0041fc01: xor eax, eax
    uint32_t t25 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t25);
    ctx.eax = static_cast<uint32_t>(t25);
    // 0x0041fc03: pop esi
    uint32_t t26 = ctx.esp;
    uint32_t t27 = mem.r32(t26);
    uint32_t t28 = static_cast<uint32_t>(t26 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    ctx.esi = static_cast<uint32_t>(t27);
    // 0x0041fc04: pop ecx
    uint32_t t29 = ctx.esp;
    uint32_t t30 = mem.r32(t29);
    uint32_t t31 = static_cast<uint32_t>(t29 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    ctx.ecx = static_cast<uint32_t>(t30);
    // 0x0041fc05: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0041fbf1: {
    // 0x0041fbf1: mov eax, dword ptr [eax + 0x28]
    uint32_t t32 = static_cast<uint32_t>(ctx.eax + 0x00000028u);
    uint32_t t33 = mem.r32(t32);
    ctx.eax = static_cast<uint32_t>(t33);
    // 0x0041fbf4: mov dword ptr [esi + 0x2c], eax
    uint32_t t34 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    mem.w32(t34, ctx.eax);
    // 0x0041fbf7: pop esi
    uint32_t t35 = ctx.esp;
    uint32_t t36 = mem.r32(t35);
    uint32_t t37 = static_cast<uint32_t>(t35 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    ctx.esi = static_cast<uint32_t>(t36);
    // 0x0041fbf8: pop ecx
    uint32_t t38 = ctx.esp;
    uint32_t t39 = mem.r32(t38);
    uint32_t t40 = static_cast<uint32_t>(t38 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    ctx.ecx = static_cast<uint32_t>(t39);
    // 0x0041fbf9: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0041fbeb: {
    // 0x0041fbeb: mov dword ptr [esi + 0x2c], eax
    uint32_t t41 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    mem.w32(t41, ctx.eax);
    // 0x0041fbee: pop esi
    uint32_t t42 = ctx.esp;
    uint32_t t43 = mem.r32(t42);
    uint32_t t44 = static_cast<uint32_t>(t42 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    ctx.esi = static_cast<uint32_t>(t43);
    // 0x0041fbef: pop ecx
    uint32_t t45 = ctx.esp;
    uint32_t t46 = mem.r32(t45);
    uint32_t t47 = static_cast<uint32_t>(t45 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    ctx.ecx = static_cast<uint32_t>(t46);
    // 0x0041fbf0: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0041fc0d: {
    // 0x0041fc0d: lea eax, [esp + 4]
    uint32_t t48 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    ctx.eax = static_cast<uint32_t>(t48);
    // 0x0041fc11: push eax
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, ctx.eax);
    // 0x0041fc12: push ecx
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, ctx.ecx);
    // 0x0041fc13: call dword ptr [0x51b058]
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, 0x0041fc19u);
    hle_iat_call(ctx, mem, 0x0051b058u);
    // 0x0041fc19: mov dword ptr [esi + 0x2c], eax
    uint32_t t52 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    mem.w32(t52, ctx.eax);
    goto bb_0041fc1c;
}
}

// sub_0041fc30 | subsystem=Core/Windows | canonical | 1 blocks | 2 insns
void sub_0041fc30(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041fc30: add ecx, 4
    uint32_t t0 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000004u, t0);
    ctx.ecx = static_cast<uint32_t>(t0);
    // 0x0041fc33: jmp 0x413e00
    sub_00413e00(ctx, mem);
    return;
}
}

// sub_0041fc40 | subsystem=Core/Windows | canonical | 1 blocks | 2 insns
void sub_0041fc40(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041fc40: add ecx, 4
    uint32_t t0 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000004u, t0);
    ctx.ecx = static_cast<uint32_t>(t0);
    // 0x0041fc43: jmp 0x414000
    sub_00414000(ctx, mem);
    return;
}
}

// sub_0041fc50 | subsystem=Core/Windows | canonical | 6 blocks | 33 insns
void sub_0041fc50(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041fc50: mov eax, dword ptr [esp + 4]
    uint32_t t0 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint32_t t1 = mem.r32(t0);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x0041fc54: push ebx
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebx);
    // 0x0041fc55: push esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.esi);
    // 0x0041fc56: push edi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.edi);
    // 0x0041fc57: mov edi, dword ptr [esp + 0x14]
    uint32_t t5 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t6 = mem.r32(t5);
    ctx.edi = static_cast<uint32_t>(t6);
    // 0x0041fc5b: lea esi, [ecx + 4]
    uint32_t t7 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    ctx.esi = static_cast<uint32_t>(t7);
    // 0x0041fc5e: push eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.eax);
    // 0x0041fc5f: mov ebx, edi
    ctx.ebx = static_cast<uint32_t>(ctx.edi);
    // 0x0041fc61: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0041fc63: call 0x413e70
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x0041fc68u);
    sub_00413e70(ctx, mem);
    // 0x0041fc68: test eax, eax
    uint32_t t10 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    // 0x0041fc6a: jne 0x41fc74
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0041fc74;
    goto bb_0041fc6c;
}
bb_0041fc74: {
    // 0x0041fc74: mov eax, dword ptr [esi + 0x3c]
    uint32_t t11 = static_cast<uint32_t>(ctx.esi + 0x0000003cu);
    uint32_t t12 = mem.r32(t11);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0041fc77: test eax, eax
    uint32_t t13 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t13);
    // 0x0041fc79: je 0x41fc91
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041fc91;
    goto bb_0041fc7b;
}
bb_0041fc6c: {
    // 0x0041fc6c: pop edi
    uint32_t t14 = ctx.esp;
    uint32_t t15 = mem.r32(t14);
    uint32_t t16 = static_cast<uint32_t>(t14 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    ctx.edi = static_cast<uint32_t>(t15);
    // 0x0041fc6d: pop esi
    uint32_t t17 = ctx.esp;
    uint32_t t18 = mem.r32(t17);
    uint32_t t19 = static_cast<uint32_t>(t17 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    ctx.esi = static_cast<uint32_t>(t18);
    // 0x0041fc6e: xor eax, eax
    uint32_t t20 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t20);
    ctx.eax = static_cast<uint32_t>(t20);
    // 0x0041fc70: pop ebx
    uint32_t t21 = ctx.esp;
    uint32_t t22 = mem.r32(t21);
    uint32_t t23 = static_cast<uint32_t>(t21 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    ctx.ebx = static_cast<uint32_t>(t22);
    // 0x0041fc71: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
bb_0041fc91: {
    // 0x0041fc91: pop edi
    uint32_t t24 = ctx.esp;
    uint32_t t25 = mem.r32(t24);
    uint32_t t26 = static_cast<uint32_t>(t24 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    ctx.edi = static_cast<uint32_t>(t25);
    // 0x0041fc92: pop esi
    uint32_t t27 = ctx.esp;
    uint32_t t28 = mem.r32(t27);
    uint32_t t29 = static_cast<uint32_t>(t27 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    ctx.esi = static_cast<uint32_t>(t28);
    // 0x0041fc93: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0041fc98: pop ebx
    uint32_t t30 = ctx.esp;
    uint32_t t31 = mem.r32(t30);
    uint32_t t32 = static_cast<uint32_t>(t30 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    ctx.ebx = static_cast<uint32_t>(t31);
    // 0x0041fc99: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
bb_0041fc7b: {
    // 0x0041fc7b: push 0
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x00000000u);
    // 0x0041fc7d: push -1
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0xffffffffu);
    // 0x0041fc7f: push eax
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, ctx.eax);
    // 0x0041fc80: call dword ptr [0x51b1c4]
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, 0x0041fc86u);
    hle_iat_call(ctx, mem, 0x0051b1c4u);
    // 0x0041fc86: cmp eax, 0xc0
    uint32_t t37 = static_cast<uint32_t>(ctx.eax - 0x000000c0u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x000000c0u, t37);
    // 0x0041fc8b: je 0x41fc6c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041fc6c;
}
{
    // 0x0041fc8d: test eax, eax
    uint32_t t38 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t38);
    // 0x0041fc8f: jne 0x41fc6c
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0041fc6c;
    goto bb_0041fc91;
}
}

// sub_0041fca0 | subsystem=Core/Windows | canonical | 8 blocks | 36 insns
void sub_0041fca0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041fca0: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x0041fca1: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
    // 0x0041fca2: push edi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.edi);
    // 0x0041fca3: push 0x60
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x00000060u);
    // 0x0041fca5: call 0x4e0177
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x0041fcaau);
    hle_crt_004e0177(ctx, mem);
    // 0x0041fcaa: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x0041fcac: add esp, 4
    uint32_t t5 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x0041fcaf: test edi, edi
    uint32_t t6 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t6);
    // 0x0041fcb1: je 0x41fcc5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041fcc5;
    goto bb_0041fcb3;
}
bb_0041fcc5: {
    // 0x0041fcc5: xor esi, esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.esi = static_cast<uint32_t>(t7);
    goto bb_0041fcc7;
}
bb_0041fcb3: {
    // 0x0041fcb3: lea esi, [edi + 4]
    uint32_t t8 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    ctx.esi = static_cast<uint32_t>(t8);
    // 0x0041fcb6: mov dword ptr [edi], 0x535a4c
    mem.w32(ctx.edi, 0x00535a4cu);
    // 0x0041fcbc: call 0x413c60
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x0041fcc1u);
    sub_00413c60(ctx, mem);
    // 0x0041fcc1: mov esi, edi
    ctx.esi = static_cast<uint32_t>(ctx.edi);
    // 0x0041fcc3: jmp 0x41fcc7
}
bb_0041fcc7: {
    // 0x0041fcc7: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0041fcc9: call 0x41fb40
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x0041fcceu);
    sub_0041fb40(ctx, mem);
    // 0x0041fcce: cmp eax, 1
    uint32_t t11 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t11);
    // 0x0041fcd1: jne 0x41fcd9
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0041fcd9;
    goto bb_0041fcd3;
}
bb_0041fcd9: {
    // 0x0041fcd9: test esi, esi
    uint32_t t12 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t12);
    // 0x0041fcdb: je 0x41fce7
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041fce7;
    goto bb_0041fcdd;
}
bb_0041fcd3: {
    // 0x0041fcd3: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0041fcd5: pop edi
    uint32_t t13 = ctx.esp;
    uint32_t t14 = mem.r32(t13);
    uint32_t t15 = static_cast<uint32_t>(t13 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    ctx.edi = static_cast<uint32_t>(t14);
    // 0x0041fcd6: pop esi
    uint32_t t16 = ctx.esp;
    uint32_t t17 = mem.r32(t16);
    uint32_t t18 = static_cast<uint32_t>(t16 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    ctx.esi = static_cast<uint32_t>(t17);
    // 0x0041fcd7: pop ecx
    uint32_t t19 = ctx.esp;
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t19 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    ctx.ecx = static_cast<uint32_t>(t20);
    // 0x0041fcd8: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0041fce7: {
    // 0x0041fce7: pop edi
    uint32_t t22 = ctx.esp;
    uint32_t t23 = mem.r32(t22);
    uint32_t t24 = static_cast<uint32_t>(t22 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    ctx.edi = static_cast<uint32_t>(t23);
    // 0x0041fce8: xor eax, eax
    uint32_t t25 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t25);
    ctx.eax = static_cast<uint32_t>(t25);
    // 0x0041fcea: pop esi
    uint32_t t26 = ctx.esp;
    uint32_t t27 = mem.r32(t26);
    uint32_t t28 = static_cast<uint32_t>(t26 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    ctx.esi = static_cast<uint32_t>(t27);
    // 0x0041fceb: pop ecx
    uint32_t t29 = ctx.esp;
    uint32_t t30 = mem.r32(t29);
    uint32_t t31 = static_cast<uint32_t>(t29 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    ctx.ecx = static_cast<uint32_t>(t30);
    // 0x0041fcec: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0041fcdd: {
    // 0x0041fcdd: mov eax, dword ptr [esi]
    uint32_t t32 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t32);
    // 0x0041fcdf: mov edx, dword ptr [eax]
    uint32_t t33 = mem.r32(ctx.eax);
    ctx.edx = static_cast<uint32_t>(t33);
    // 0x0041fce1: push 1
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x00000001u);
    // 0x0041fce3: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x0041fce5: call edx
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, 0x0041fce7u);
    call_indirect(ctx, mem, ctx.edx);
    goto bb_0041fce7;
}
}

// sub_004230f0 | subsystem=Core/Windows | canonical | 1 blocks | 5 insns
void sub_004230f0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004230f0: mov eax, dword ptr [esp + 8]
    uint32_t t0 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t1 = mem.r32(t0);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x004230f4: mov edx, dword ptr [esp + 4]
    uint32_t t2 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint32_t t3 = mem.r32(t2);
    ctx.edx = static_cast<uint32_t>(t3);
    // 0x004230f8: mov dword ptr [ecx + 0xc], eax
    uint32_t t4 = static_cast<uint32_t>(ctx.ecx + 0x0000000cu);
    mem.w32(t4, ctx.eax);
    // 0x004230fb: mov dword ptr [ecx + 8], edx
    uint32_t t5 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    mem.w32(t5, ctx.edx);
    // 0x004230fe: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
}

// sub_00432c50 | subsystem=Core/Windows | canonical | 11 blocks | 41 insns
void sub_00432c50(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00432c50: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x00432c51: fld dword ptr [0x53de08]
    double t1 = static_cast<double>(mem.rf32(0x0053de08u));
    ctx.fpu_push(t1);
    // 0x00432c57: push esi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.esi);
    // 0x00432c58: push edi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.edi);
    // 0x00432c59: fstp dword ptr [0x7749b8]
    double t4 = ctx.fpu_st(0);
    mem.wf32(0x007749b8u, static_cast<float>(t4));
    ctx.fpu_pop();
    // 0x00432c5f: mov esi, 0x7749d0
    ctx.esi = static_cast<uint32_t>(0x007749d0u);
    // 0x00432c64: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x00432c66: call 0x43b8d0
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, 0x00432c6bu);
    sub_0043b8d0(ctx, mem);
    // 0x00432c6b: cmp byte ptr [0x76e652], 0
    uint8_t t6 = mem.r8(0x0076e652u);
    uint8_t t7 = static_cast<uint8_t>(static_cast<uint32_t>(t6) - static_cast<uint32_t>(uint8_t{0x00u}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, t6, uint8_t{0x00u}, t7);
    // 0x00432c72: je 0x432c7b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00432c7b;
    goto bb_00432c74;
}
bb_00432c7b: {
    // 0x00432c7b: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x00432c7d: call 0x432b40
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x00432c82u);
    sub_00432b40(ctx, mem);
    // 0x00432c82: test eax, eax
    uint32_t t9 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    // 0x00432c84: jne 0x432c88
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00432c88;
    goto bb_00432c86;
}
bb_00432c74: {
    // 0x00432c74: call 0x40dae0
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x00432c79u);
    sub_0040dae0(ctx, mem);
    // 0x00432c79: jmp 0x432c88
}
bb_00432c88: {
    // 0x00432c88: mov esi, 0x7749d0
    ctx.esi = static_cast<uint32_t>(0x007749d0u);
    // 0x00432c8d: call 0x43b950
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0x00432c92u);
    sub_0043b950(ctx, mem);
    // 0x00432c92: mov eax, dword ptr [0x76e740]
    uint32_t t12 = mem.r32(0x0076e740u);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x00432c97: cmp byte ptr [eax + 8], 0
    uint32_t t13 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    uint8_t t14 = mem.r8(t13);
    uint8_t t15 = static_cast<uint8_t>(static_cast<uint32_t>(t14) - static_cast<uint32_t>(uint8_t{0x00u}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, t14, uint8_t{0x00u}, t15);
    // 0x00432c9b: je 0x432c9f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00432c9f;
    goto bb_00432c9d;
}
bb_00432c86: {
    // 0x00432c86: xor edi, edi
    uint32_t t16 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    ctx.edi = static_cast<uint32_t>(t16);
    goto bb_00432c88;
}
bb_00432c9f: {
    // 0x00432c9f: cmp dword ptr [0x54c798], 0
    uint32_t t17 = mem.r32(0x0054c798u);
    uint32_t t18 = static_cast<uint32_t>(t17 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t17, 0x00000000u, t18);
    // 0x00432ca6: je 0x432cb8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00432cb8;
    goto bb_00432ca8;
}
bb_00432c9d: {
    // 0x00432c9d: xor edi, edi
    uint32_t t19 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t19);
    ctx.edi = static_cast<uint32_t>(t19);
    goto bb_00432c9f;
}
bb_00432cb8: {
    // 0x00432cb8: mov eax, dword ptr [0x76e64c]
    uint32_t t20 = mem.r32(0x0076e64cu);
    ctx.eax = static_cast<uint32_t>(t20);
    // 0x00432cbd: add eax, 1
    uint32_t t21 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t21);
    ctx.eax = static_cast<uint32_t>(t21);
    // 0x00432cc0: cmp eax, 0x1e0
    uint32_t t22 = static_cast<uint32_t>(ctx.eax - 0x000001e0u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x000001e0u, t22);
    // 0x00432cc5: mov dword ptr [0x76e64c], eax
    mem.w32(0x0076e64cu, ctx.eax);
    // 0x00432cca: jl 0x432cb2
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_00432cb2;
    goto bb_00432ccc;
}
bb_00432ca8: {
    // 0x00432ca8: mov dword ptr [0x76e64c], 0
    mem.w32(0x0076e64cu, 0x00000000u);
}
bb_00432cb2: {
    // 0x00432cb2: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x00432cb4: pop edi
    uint32_t t23 = ctx.esp;
    uint32_t t24 = mem.r32(t23);
    uint32_t t25 = static_cast<uint32_t>(t23 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    ctx.edi = static_cast<uint32_t>(t24);
    // 0x00432cb5: pop esi
    uint32_t t26 = ctx.esp;
    uint32_t t27 = mem.r32(t26);
    uint32_t t28 = static_cast<uint32_t>(t26 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    ctx.esi = static_cast<uint32_t>(t27);
    // 0x00432cb6: pop ecx
    uint32_t t29 = ctx.esp;
    uint32_t t30 = mem.r32(t29);
    uint32_t t31 = static_cast<uint32_t>(t29 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    ctx.ecx = static_cast<uint32_t>(t30);
    // 0x00432cb7: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00432ccc: {
    // 0x00432ccc: pop edi
    uint32_t t32 = ctx.esp;
    uint32_t t33 = mem.r32(t32);
    uint32_t t34 = static_cast<uint32_t>(t32 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    ctx.edi = static_cast<uint32_t>(t33);
    // 0x00432ccd: xor eax, eax
    uint32_t t35 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t35);
    ctx.eax = static_cast<uint32_t>(t35);
    // 0x00432ccf: pop esi
    uint32_t t36 = ctx.esp;
    uint32_t t37 = mem.r32(t36);
    uint32_t t38 = static_cast<uint32_t>(t36 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    ctx.esi = static_cast<uint32_t>(t37);
    // 0x00432cd0: pop ecx
    uint32_t t39 = ctx.esp;
    uint32_t t40 = mem.r32(t39);
    uint32_t t41 = static_cast<uint32_t>(t39 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    ctx.ecx = static_cast<uint32_t>(t40);
    // 0x00432cd1: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00432e30 | subsystem=Core/Windows | canonical | 24 blocks | 178 insns
void sub_00432e30(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00432e30: sub esp, 0x28
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000028u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000028u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x00432e33: push ebx
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebx);
    // 0x00432e34: push ebp
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebp);
    // 0x00432e35: push esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.esi);
    // 0x00432e36: push edi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.edi);
    // 0x00432e37: call 0x40dba0
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, 0x00432e3cu);
    sub_0040dba0(ctx, mem);
    // 0x00432e3c: cmp byte ptr [0x76e652], 0
    uint8_t t6 = mem.r8(0x0076e652u);
    uint8_t t7 = static_cast<uint8_t>(static_cast<uint32_t>(t6) - static_cast<uint32_t>(uint8_t{0x00u}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, t6, uint8_t{0x00u}, t7);
    // 0x00432e43: je 0x432e73
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00432e73;
    goto bb_00432e45;
}
bb_00432e73: {
    // 0x00432e73: fld dword ptr [0x53d618]
    double t8 = static_cast<double>(mem.rf32(0x0053d618u));
    ctx.fpu_push(t8);
    // 0x00432e79: mov eax, dword ptr [0x767448]
    uint32_t t9 = mem.r32(0x00767448u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x00432e7e: mov ebp, dword ptr [0x554140]
    uint32_t t10 = mem.r32(0x00554140u);
    ctx.ebp = static_cast<uint32_t>(t10);
    // 0x00432e84: fstp dword ptr [esp + 0x10]
    double t11 = ctx.fpu_st(0);
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.wf32(t12, static_cast<float>(t11));
    ctx.fpu_pop();
    // 0x00432e88: fld dword ptr [0x53d614]
    double t13 = static_cast<double>(mem.rf32(0x0053d614u));
    ctx.fpu_push(t13);
    // 0x00432e8e: mov edi, dword ptr [eax + 0x28]
    uint32_t t14 = static_cast<uint32_t>(ctx.eax + 0x00000028u);
    uint32_t t15 = mem.r32(t14);
    ctx.edi = static_cast<uint32_t>(t15);
    // 0x00432e91: mov esi, dword ptr [eax + 0x2c]
    uint32_t t16 = static_cast<uint32_t>(ctx.eax + 0x0000002cu);
    uint32_t t17 = mem.r32(t16);
    ctx.esi = static_cast<uint32_t>(t17);
    // 0x00432e94: fstp dword ptr [esp + 0x14]
    double t18 = ctx.fpu_st(0);
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.wf32(t19, static_cast<float>(t18));
    ctx.fpu_pop();
    // 0x00432e98: xor ebx, ebx
    uint32_t t20 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t20);
    ctx.ebx = static_cast<uint32_t>(t20);
    // 0x00432e9a: cmp dword ptr [ebp + 0x178], ebx
    uint32_t t21 = static_cast<uint32_t>(ctx.ebp + 0x00000178u);
    uint32_t t22 = mem.r32(t21);
    uint32_t t23 = static_cast<uint32_t>(t22 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t22, ctx.ebx, t23);
    // 0x00432ea0: mov dword ptr [esp + 0x1c], ebx
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t24, ctx.ebx);
    // 0x00432ea4: mov dword ptr [esp + 0x20], edi
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t25, ctx.edi);
    // 0x00432ea8: mov dword ptr [esp + 0x24], esi
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t26, ctx.esi);
    // 0x00432eac: je 0x433017
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00433017;
    goto bb_00432eb2;
}
bb_00432e45: {
    // 0x00432e45: mov ecx, dword ptr [0x767448]
    uint32_t t27 = mem.r32(0x00767448u);
    ctx.ecx = static_cast<uint32_t>(t27);
    // 0x00432e4b: mov eax, dword ptr [ecx + 0x2c]
    uint32_t t28 = static_cast<uint32_t>(ctx.ecx + 0x0000002cu);
    uint32_t t29 = mem.r32(t28);
    ctx.eax = static_cast<uint32_t>(t29);
    // 0x00432e4e: mov edx, dword ptr [ecx + 0x28]
    uint32_t t30 = static_cast<uint32_t>(ctx.ecx + 0x00000028u);
    uint32_t t31 = mem.r32(t30);
    ctx.edx = static_cast<uint32_t>(t31);
    // 0x00432e51: push 0
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x00000000u);
    // 0x00432e53: push 0
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x00000000u);
    // 0x00432e55: push -1
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0xffffffffu);
    // 0x00432e57: push eax
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, ctx.eax);
    // 0x00432e58: push edx
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, ctx.edx);
    // 0x00432e59: push 0
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, 0x00000000u);
    // 0x00432e5b: push 0
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, 0x00000000u);
    // 0x00432e5d: push eax
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, ctx.eax);
    // 0x00432e5e: mov eax, dword ptr [esp + 0x5c]
    uint32_t t40 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    uint32_t t41 = mem.r32(t40);
    ctx.eax = static_cast<uint32_t>(t41);
    // 0x00432e62: push 0
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, 0x00000000u);
    // 0x00432e64: push 0
    uint32_t t43 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    mem.w32(t43, 0x00000000u);
    // 0x00432e66: push eax
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, ctx.eax);
    // 0x00432e67: push 0
    uint32_t t45 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    mem.w32(t45, 0x00000000u);
    // 0x00432e69: call 0x415580
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, 0x00432e6eu);
    sub_00415580(ctx, mem);
    // 0x00432e6e: jmp 0x433057
    goto bb_00433057;
}
bb_00433017: {
    // 0x00433017: cmp dword ptr [ebp + 0x174], 1
    uint32_t t47 = static_cast<uint32_t>(ctx.ebp + 0x00000174u);
    uint32_t t48 = mem.r32(t47);
    uint32_t t49 = static_cast<uint32_t>(t48 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t48, 0x00000001u, t49);
    // 0x0043301e: jne 0x433027
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00433027;
    goto bb_00433020;
}
bb_00432eb2: {
    // 0x00432eb2: push ebx
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, ctx.ebx);
    // 0x00432eb3: push 0xff000000
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, 0xff000000u);
    // 0x00432eb8: push 0xff000000
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, 0xff000000u);
    // 0x00432ebd: push 0xff000000
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, 0xff000000u);
    // 0x00432ec2: push 0xff000000
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, 0xff000000u);
    // 0x00432ec7: push esi
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, ctx.esi);
    // 0x00432ec8: push edi
    uint32_t t56 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    mem.w32(t56, ctx.edi);
    // 0x00432ec9: push ebx
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, ctx.ebx);
    // 0x00432eca: push ebx
    uint32_t t58 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    mem.w32(t58, ctx.ebx);
    // 0x00432ecb: xor eax, eax
    uint32_t t59 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t59);
    ctx.eax = static_cast<uint32_t>(t59);
    // 0x00432ecd: call 0x415450
    uint32_t t60 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t60);
    mem.w32(t60, 0x00432ed2u);
    sub_00415450(ctx, mem);
    // 0x00432ed2: mov eax, dword ptr [ebp + 0x178]
    uint32_t t61 = static_cast<uint32_t>(ctx.ebp + 0x00000178u);
    uint32_t t62 = mem.r32(t61);
    ctx.eax = static_cast<uint32_t>(t62);
    // 0x00432ed8: add eax, -1
    uint32_t t63 = static_cast<uint32_t>(ctx.eax + 0xffffffffu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0xffffffffu, t63);
    ctx.eax = static_cast<uint32_t>(t63);
    // 0x00432edb: add esp, 0x24
    uint32_t t64 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000024u, t64);
    ctx.esp = static_cast<uint32_t>(t64);
    // 0x00432ede: cmp eax, 5
    uint32_t t65 = static_cast<uint32_t>(ctx.eax - 0x00000005u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000005u, t65);
    // 0x00432ee1: ja 0x432fa2
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_00432fa2;
    goto bb_00432ee7;
}
bb_00433057: {
    // 0x00433057: add esp, 0x30
    uint32_t t66 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000030u, t66);
    ctx.esp = static_cast<uint32_t>(t66);
    // 0x0043305a: push 0x5550c4
    uint32_t t67 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t67);
    mem.w32(t67, 0x005550c4u);
    // 0x0043305f: call dword ptr [0x51b078]
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, 0x00433065u);
    hle_iat_call(ctx, mem, 0x0051b078u);
    // 0x00433065: mov eax, dword ptr [0x5550a8]
    uint32_t t69 = mem.r32(0x005550a8u);
    ctx.eax = static_cast<uint32_t>(t69);
    // 0x0043306a: call 0x4c04e0
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, 0x0043306fu);
    sub_004c04e0(ctx, mem);
    // 0x0043306f: push 0x5550c4
    uint32_t t71 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t71);
    mem.w32(t71, 0x005550c4u);
    // 0x00433074: call dword ptr [0x51b070]
    uint32_t t72 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    mem.w32(t72, 0x0043307au);
    hle_iat_call(ctx, mem, 0x0051b070u);
    // 0x0043307a: mov eax, dword ptr [0x76e7d4]
    uint32_t t73 = mem.r32(0x0076e7d4u);
    ctx.eax = static_cast<uint32_t>(t73);
    // 0x0043307f: test eax, eax
    uint32_t t74 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t74);
    // 0x00433081: mov byte ptr [0x56447f], 1
    mem.w8(0x0056447fu, uint8_t{0x01u});
    // 0x00433088: je 0x433099
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00433099;
    goto bb_0043308a;
}
bb_00433027: {
    // 0x00433027: mov eax, dword ptr [esp + 0x1c]
    uint32_t t75 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t76 = mem.r32(t75);
    ctx.eax = static_cast<uint32_t>(t76);
    // 0x0043302b: mov ecx, dword ptr [esp + 0x3c]
    uint32_t t77 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    uint32_t t78 = mem.r32(t77);
    ctx.ecx = static_cast<uint32_t>(t78);
    // 0x0043302f: push 1
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, 0x00000001u);
    // 0x00433031: push 0
    uint32_t t80 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    mem.w32(t80, 0x00000000u);
    // 0x00433033: push -1
    uint32_t t81 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    mem.w32(t81, 0xffffffffu);
    // 0x00433035: push 0x1e0
    uint32_t t82 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t82);
    mem.w32(t82, 0x000001e0u);
    // 0x0043303a: push 0x280
    uint32_t t83 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t83);
    mem.w32(t83, 0x00000280u);
    // 0x0043303f: push 0
    uint32_t t84 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    mem.w32(t84, 0x00000000u);
    // 0x00433041: push 0
    uint32_t t85 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t85);
    mem.w32(t85, 0x00000000u);
    // 0x00433043: push esi
    uint32_t t86 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t86);
    mem.w32(t86, ctx.esi);
    // 0x00433044: push ebx
    uint32_t t87 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t87);
    mem.w32(t87, ctx.ebx);
    // 0x00433045: push eax
    uint32_t t88 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t88);
    mem.w32(t88, ctx.eax);
    // 0x00433046: push ecx
    uint32_t t89 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t89);
    mem.w32(t89, ctx.ecx);
    // 0x00433047: push 0
    uint32_t t90 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    mem.w32(t90, 0x00000000u);
    // 0x00433049: mov edx, edi
    ctx.edx = static_cast<uint32_t>(ctx.edi);
    // 0x0043304b: call 0x415580
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, 0x00433050u);
    sub_00415580(ctx, mem);
    // 0x00433050: mov byte ptr [0x56447f], 1
    mem.w8(0x0056447fu, uint8_t{0x01u});
    goto bb_00433057;
}
bb_00433020: {
    // 0x00433020: mov byte ptr [0x56447f], 2
    mem.w8(0x0056447fu, uint8_t{0x02u});
    goto bb_00433027;
}
bb_00432fa2: {
    // 0x00432fa2: fld dword ptr [esp + 0x10]
    uint32_t t92 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    double t93 = static_cast<double>(mem.rf32(t92));
    ctx.fpu_push(t93);
    // 0x00432fa6: fld st(0)
    double t94 = ctx.fpu_st(0);
    ctx.fpu_push(t94);
    // 0x00432fa8: fld dword ptr [esp + 0x14]
    uint32_t t95 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    double t96 = static_cast<double>(mem.rf32(t95));
    ctx.fpu_push(t96);
    // 0x00432fac: fld st(0)
    double t97 = ctx.fpu_st(0);
    ctx.fpu_push(t97);
    // 0x00432fae: fdivp st(2)
    double t98 = ctx.fpu_st(2);
    double t99 = ctx.fpu_st(0);
    double t100 = (t98 / t99);
    ctx.fpu_st(2) = t100;
    ctx.fpu_pop();
    // 0x00432fb0: fxch st(1)
    recomp_detail::fpu_swap(ctx, 1);
    // 0x00432fb2: fcomp qword ptr [0x53dd30]
    double t101 = ctx.fpu_st(0);
    double t102 = mem.rf64(0x0053dd30u);
    ctx.fpu_compare(t101, t102);
    ctx.fpu_pop();
    // 0x00432fb8: fnstsw ax
    recomp_detail::w16(ctx.eax, static_cast<uint16_t>(ctx.fpu_sw));
    // 0x00432fba: test ah, 0x41
    uint8_t t103 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8h(ctx.eax)) & static_cast<uint32_t>(uint8_t{0x41u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t103);
    // 0x00432fbd: jne 0x432fed
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00432fed;
    goto bb_00432fbf;
}
bb_00432ee7: {
    // 0x00432ee7: jmp dword ptr [eax*4 + 0x4330a4]
    switch (ctx.eax) {
        case 0u: goto bb_00432eee;
        case 1u: goto bb_00432f50;
        case 2u: goto bb_00432f62;
        case 3u: goto bb_00432f6a;
        case 4u: goto bb_00432f7c;
        case 5u: goto bb_00432f8e;
        default: recomp_detail::trap_halt(ctx, 0x004330a4u, "switch_oob"); return;
    }
}
bb_00433099: {
    // 0x00433099: pop edi
    uint32_t t104 = ctx.esp;
    uint32_t t105 = mem.r32(t104);
    uint32_t t106 = static_cast<uint32_t>(t104 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t106);
    ctx.edi = static_cast<uint32_t>(t105);
    // 0x0043309a: pop esi
    uint32_t t107 = ctx.esp;
    uint32_t t108 = mem.r32(t107);
    uint32_t t109 = static_cast<uint32_t>(t107 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t109);
    ctx.esi = static_cast<uint32_t>(t108);
    // 0x0043309b: pop ebp
    uint32_t t110 = ctx.esp;
    uint32_t t111 = mem.r32(t110);
    uint32_t t112 = static_cast<uint32_t>(t110 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t112);
    ctx.ebp = static_cast<uint32_t>(t111);
    // 0x0043309c: pop ebx
    uint32_t t113 = ctx.esp;
    uint32_t t114 = mem.r32(t113);
    uint32_t t115 = static_cast<uint32_t>(t113 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t115);
    ctx.ebx = static_cast<uint32_t>(t114);
    // 0x0043309d: add esp, 0x28
    uint32_t t116 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000028u, t116);
    ctx.esp = static_cast<uint32_t>(t116);
    // 0x004330a0: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0043308a: {
    // 0x0043308a: mov edx, dword ptr [eax]
    uint32_t t117 = mem.r32(ctx.eax);
    ctx.edx = static_cast<uint32_t>(t117);
    // 0x0043308c: push 0
    uint32_t t118 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    mem.w32(t118, 0x00000000u);
    // 0x0043308e: push 7
    uint32_t t119 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t119);
    mem.w32(t119, 0x00000007u);
    // 0x00433090: push eax
    uint32_t t120 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t120);
    mem.w32(t120, ctx.eax);
    // 0x00433091: mov eax, dword ptr [edx + 0xe4]
    uint32_t t121 = static_cast<uint32_t>(ctx.edx + 0x000000e4u);
    uint32_t t122 = mem.r32(t121);
    ctx.eax = static_cast<uint32_t>(t122);
    // 0x00433097: call eax
    uint32_t t123 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t123);
    mem.w32(t123, 0x00433099u);
    call_indirect(ctx, mem, ctx.eax);
    goto bb_00433099;
}
bb_00432fed: {
    // 0x00432fed: fxch st(1)
    recomp_detail::fpu_swap(ctx, 1);
    // 0x00432fef: fmul qword ptr [0x53da08]
    double t124 = ctx.fpu_st(0);
    double t125 = mem.rf64(0x0053da08u);
    double t126 = (t124 * t125);
    ctx.fpu_st(0) = t126;
    // 0x00432ff5: fxch st(1)
    recomp_detail::fpu_swap(ctx, 1);
    // 0x00432ff7: fmul qword ptr [0x53da18]
    double t127 = ctx.fpu_st(0);
    double t128 = mem.rf64(0x0053da18u);
    double t129 = (t127 * t128);
    ctx.fpu_st(0) = t129;
    // 0x00432ffd: fdivp st(1)
    double t130 = ctx.fpu_st(1);
    double t131 = ctx.fpu_st(0);
    double t132 = (t130 / t131);
    ctx.fpu_st(1) = t132;
    ctx.fpu_pop();
    // 0x00432fff: fimul dword ptr [esp + 0x24]
    uint32_t t133 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    double t134 = static_cast<double>(static_cast<int32_t>(mem.r32(t133)));
    double t135 = ctx.fpu_st(0);
    double t136 = (t135 * t134);
    ctx.fpu_st(0) = t136;
    // 0x00433003: call 0x4f49f0
    uint32_t t137 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t137);
    mem.w32(t137, 0x00433008u);
    hle_crt_004f49f0(ctx, mem);
    // 0x00433008: mov edx, dword ptr [0x767448]
    uint32_t t138 = mem.r32(0x00767448u);
    ctx.edx = static_cast<uint32_t>(t138);
    // 0x0043300e: mov ebx, dword ptr [edx + 0x2c]
    uint32_t t139 = static_cast<uint32_t>(ctx.edx + 0x0000002cu);
    uint32_t t140 = mem.r32(t139);
    ctx.ebx = static_cast<uint32_t>(t140);
    // 0x00433011: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x00433013: sub ebx, esi
    uint32_t t141 = static_cast<uint32_t>(ctx.ebx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.esi, t141);
    ctx.ebx = static_cast<uint32_t>(t141);
    // 0x00433015: shr ebx, 1
    uint32_t t142 = static_cast<uint32_t>(0x00000001u & 0x0000001fu);
    uint32_t t143 = recomp_detail::shr<uint32_t>(ctx.ebx, t142);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.ebx, t142, t143);
    ctx.ebx = static_cast<uint32_t>(t143);
    goto bb_00433017;
}
bb_00432fbf: {
    // 0x00432fbf: fmul qword ptr [0x53da18]
    double t144 = ctx.fpu_st(0);
    double t145 = mem.rf64(0x0053da18u);
    double t146 = (t144 * t145);
    ctx.fpu_st(0) = t146;
    // 0x00432fc5: fxch st(1)
    recomp_detail::fpu_swap(ctx, 1);
    // 0x00432fc7: fmul qword ptr [0x53da08]
    double t147 = ctx.fpu_st(0);
    double t148 = mem.rf64(0x0053da08u);
    double t149 = (t147 * t148);
    ctx.fpu_st(0) = t149;
    // 0x00432fcd: fdivp st(1)
    double t150 = ctx.fpu_st(1);
    double t151 = ctx.fpu_st(0);
    double t152 = (t150 / t151);
    ctx.fpu_st(1) = t152;
    ctx.fpu_pop();
    // 0x00432fcf: fimul dword ptr [esp + 0x20]
    uint32_t t153 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    double t154 = static_cast<double>(static_cast<int32_t>(mem.r32(t153)));
    double t155 = ctx.fpu_st(0);
    double t156 = (t155 * t154);
    ctx.fpu_st(0) = t156;
    // 0x00432fd3: call 0x4f49f0
    uint32_t t157 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t157);
    mem.w32(t157, 0x00432fd8u);
    hle_crt_004f49f0(ctx, mem);
    // 0x00432fd8: mov ecx, dword ptr [0x767448]
    uint32_t t158 = mem.r32(0x00767448u);
    ctx.ecx = static_cast<uint32_t>(t158);
    // 0x00432fde: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x00432fe0: mov eax, dword ptr [ecx + 0x28]
    uint32_t t159 = static_cast<uint32_t>(ctx.ecx + 0x00000028u);
    uint32_t t160 = mem.r32(t159);
    ctx.eax = static_cast<uint32_t>(t160);
    // 0x00432fe3: sub eax, edi
    uint32_t t161 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t161);
    ctx.eax = static_cast<uint32_t>(t161);
    // 0x00432fe5: shr eax, 1
    uint32_t t162 = static_cast<uint32_t>(0x00000001u & 0x0000001fu);
    uint32_t t163 = recomp_detail::shr<uint32_t>(ctx.eax, t162);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t162, t163);
    ctx.eax = static_cast<uint32_t>(t163);
    // 0x00432fe7: mov dword ptr [esp + 0x1c], eax
    uint32_t t164 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t164, ctx.eax);
    // 0x00432feb: jmp 0x433017
    goto bb_00433017;
}
bb_00432eee: {
    // 0x00432eee: cmp dword ptr [0x54d040], 1
    uint32_t t165 = mem.r32(0x0054d040u);
    uint32_t t166 = static_cast<uint32_t>(t165 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t165, 0x00000001u, t166);
    // 0x00432ef5: jne 0x432f2f
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00432f2f;
    goto bb_00432ef7;
}
bb_00432f50: {
    // 0x00432f50: fld dword ptr [0x53d618]
    double t167 = static_cast<double>(mem.rf32(0x0053d618u));
    ctx.fpu_push(t167);
    // 0x00432f56: fstp dword ptr [esp + 0x10]
    double t168 = ctx.fpu_st(0);
    uint32_t t169 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.wf32(t169, static_cast<float>(t168));
    ctx.fpu_pop();
    // 0x00432f5a: fld dword ptr [0x53d614]
    double t170 = static_cast<double>(mem.rf32(0x0053d614u));
    ctx.fpu_push(t170);
    // 0x00432f60: jmp 0x432f9e
    goto bb_00432f9e;
}
bb_00432f62: {
    // 0x00432f62: fld dword ptr [0x53d670]
    double t171 = static_cast<double>(mem.rf32(0x0053d670u));
    ctx.fpu_push(t171);
    // 0x00432f68: jmp 0x432f94
    goto bb_00432f94;
}
bb_00432f6a: {
    // 0x00432f6a: fld dword ptr [0x53d670]
    double t172 = static_cast<double>(mem.rf32(0x0053d670u));
    ctx.fpu_push(t172);
    // 0x00432f70: fstp dword ptr [esp + 0x10]
    double t173 = ctx.fpu_st(0);
    uint32_t t174 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.wf32(t174, static_cast<float>(t173));
    ctx.fpu_pop();
    // 0x00432f74: fld dword ptr [0x53d624]
    double t175 = static_cast<double>(mem.rf32(0x0053d624u));
    ctx.fpu_push(t175);
    // 0x00432f7a: jmp 0x432f9e
    goto bb_00432f9e;
}
bb_00432f7c: {
    // 0x00432f7c: fld dword ptr [0x53d668]
    double t176 = static_cast<double>(mem.rf32(0x0053d668u));
    ctx.fpu_push(t176);
    // 0x00432f82: fstp dword ptr [esp + 0x10]
    double t177 = ctx.fpu_st(0);
    uint32_t t178 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.wf32(t178, static_cast<float>(t177));
    ctx.fpu_pop();
    // 0x00432f86: fld dword ptr [0x53d618]
    double t179 = static_cast<double>(mem.rf32(0x0053d618u));
    ctx.fpu_push(t179);
    // 0x00432f8c: jmp 0x432f9e
    goto bb_00432f9e;
}
bb_00432f8e: {
    // 0x00432f8e: fld dword ptr [0x53dd38]
    double t180 = static_cast<double>(mem.rf32(0x0053dd38u));
    ctx.fpu_push(t180);
    goto bb_00432f94;
}
bb_00432f2f: {
    // 0x00432f2f: mov edx, dword ptr [0x54d048]
    uint32_t t181 = mem.r32(0x0054d048u);
    ctx.edx = static_cast<uint32_t>(t181);
    // 0x00432f35: mov eax, dword ptr [0x54d04c]
    uint32_t t182 = mem.r32(0x0054d04cu);
    ctx.eax = static_cast<uint32_t>(t182);
    // 0x00432f3a: mov dword ptr [esp + 0x14], edx
    uint32_t t183 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t183, ctx.edx);
    // 0x00432f3e: fild dword ptr [esp + 0x14]
    uint32_t t184 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    double t185 = static_cast<double>(static_cast<int32_t>(mem.r32(t184)));
    ctx.fpu_push(t185);
    // 0x00432f42: mov dword ptr [esp + 0x18], eax
    uint32_t t186 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t186, ctx.eax);
    // 0x00432f46: fstp dword ptr [esp + 0x10]
    double t187 = ctx.fpu_st(0);
    uint32_t t188 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.wf32(t188, static_cast<float>(t187));
    ctx.fpu_pop();
    // 0x00432f4a: fild dword ptr [esp + 0x18]
    uint32_t t189 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    double t190 = static_cast<double>(static_cast<int32_t>(mem.r32(t189)));
    ctx.fpu_push(t190);
    // 0x00432f4e: jmp 0x432f9e
    goto bb_00432f9e;
}
bb_00432ef7: {
    // 0x00432ef7: mov edx, dword ptr [0x74dfac]
    uint32_t t191 = mem.r32(0x0074dfacu);
    ctx.edx = static_cast<uint32_t>(t191);
    // 0x00432efd: lea ecx, [esp + 0x28]
    uint32_t t192 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.ecx = static_cast<uint32_t>(t192);
    // 0x00432f01: push ecx
    uint32_t t193 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t193);
    mem.w32(t193, ctx.ecx);
    // 0x00432f02: push edx
    uint32_t t194 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t194);
    mem.w32(t194, ctx.edx);
    // 0x00432f03: call dword ptr [0x51b250]
    uint32_t t195 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t195);
    mem.w32(t195, 0x00432f09u);
    hle_iat_call(ctx, mem, 0x0051b250u);
    // 0x00432f09: mov eax, dword ptr [esp + 0x30]
    uint32_t t196 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    uint32_t t197 = mem.r32(t196);
    ctx.eax = static_cast<uint32_t>(t197);
    // 0x00432f0d: sub eax, dword ptr [esp + 0x28]
    uint32_t t198 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t199 = mem.r32(t198);
    uint32_t t200 = static_cast<uint32_t>(ctx.eax - t199);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, t199, t200);
    ctx.eax = static_cast<uint32_t>(t200);
    // 0x00432f11: mov ecx, dword ptr [esp + 0x34]
    uint32_t t201 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    uint32_t t202 = mem.r32(t201);
    ctx.ecx = static_cast<uint32_t>(t202);
    // 0x00432f15: sub ecx, dword ptr [esp + 0x2c]
    uint32_t t203 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    uint32_t t204 = mem.r32(t203);
    uint32_t t205 = static_cast<uint32_t>(ctx.ecx - t204);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, t204, t205);
    ctx.ecx = static_cast<uint32_t>(t205);
    // 0x00432f19: mov dword ptr [esp + 0x14], eax
    uint32_t t206 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t206, ctx.eax);
    // 0x00432f1d: fild dword ptr [esp + 0x14]
    uint32_t t207 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    double t208 = static_cast<double>(static_cast<int32_t>(mem.r32(t207)));
    ctx.fpu_push(t208);
    // 0x00432f21: mov dword ptr [esp + 0x18], ecx
    uint32_t t209 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t209, ctx.ecx);
    // 0x00432f25: fstp dword ptr [esp + 0x10]
    double t210 = ctx.fpu_st(0);
    uint32_t t211 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.wf32(t211, static_cast<float>(t210));
    ctx.fpu_pop();
    // 0x00432f29: fild dword ptr [esp + 0x18]
    uint32_t t212 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    double t213 = static_cast<double>(static_cast<int32_t>(mem.r32(t212)));
    ctx.fpu_push(t213);
    // 0x00432f2d: jmp 0x432f9e
}
bb_00432f9e: {
    // 0x00432f9e: fstp dword ptr [esp + 0x14]
    double t214 = ctx.fpu_st(0);
    uint32_t t215 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.wf32(t215, static_cast<float>(t214));
    ctx.fpu_pop();
    goto bb_00432fa2;
}
bb_00432f94: {
    // 0x00432f94: fstp dword ptr [esp + 0x10]
    double t216 = ctx.fpu_st(0);
    uint32_t t217 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.wf32(t217, static_cast<float>(t216));
    ctx.fpu_pop();
    // 0x00432f98: fld dword ptr [0x53d66c]
    double t218 = static_cast<double>(mem.rf32(0x0053d66cu));
    ctx.fpu_push(t218);
    goto bb_00432f9e;
}
}

// sub_00433490 | subsystem=Core/Windows | canonical | 44 blocks | 221 insns
void sub_00433490(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00433490: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x00433491: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x00433493: and esp, 0xfffffff8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xfffffff8u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x00433496: sub esp, 0x58
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000058u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000058u, t2);
    ctx.esp = static_cast<uint32_t>(t2);
    // 0x00433499: push ebx
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.ebx);
    // 0x0043349a: push ebp
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.ebp);
    // 0x0043349b: xor ebx, ebx
    uint32_t t5 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    ctx.ebx = static_cast<uint32_t>(t5);
    // 0x0043349d: cmp dword ptr [0x774ac4], ebx
    uint32_t t6 = mem.r32(0x00774ac4u);
    uint32_t t7 = static_cast<uint32_t>(t6 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t6, ctx.ebx, t7);
    // 0x004334a3: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x004334a4: push edi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.edi);
    // 0x004334a5: je 0x43375f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043375f;
    goto bb_004334ab;
}
bb_0043375f: {
    // 0x0043375f: pop edi
    uint32_t t10 = ctx.esp;
    uint32_t t11 = mem.r32(t10);
    uint32_t t12 = static_cast<uint32_t>(t10 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    ctx.edi = static_cast<uint32_t>(t11);
    // 0x00433760: pop esi
    uint32_t t13 = ctx.esp;
    uint32_t t14 = mem.r32(t13);
    uint32_t t15 = static_cast<uint32_t>(t13 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    ctx.esi = static_cast<uint32_t>(t14);
    // 0x00433761: pop ebp
    uint32_t t16 = ctx.esp;
    uint32_t t17 = mem.r32(t16);
    uint32_t t18 = static_cast<uint32_t>(t16 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    ctx.ebp = static_cast<uint32_t>(t17);
    // 0x00433762: pop ebx
    uint32_t t19 = ctx.esp;
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t19 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    ctx.ebx = static_cast<uint32_t>(t20);
    // 0x00433763: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x00433765: pop ebp
    uint32_t t22 = ctx.esp;
    uint32_t t23 = mem.r32(t22);
    uint32_t t24 = static_cast<uint32_t>(t22 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    ctx.ebp = static_cast<uint32_t>(t23);
    // 0x00433766: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004334ab: {
    // 0x004334ab: lea esi, [esp + 0x28]
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.esi = static_cast<uint32_t>(t25);
    // 0x004334af: call 0x401830
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x004334b4u);
    sub_00401830(ctx, mem);
    // 0x004334b4: fld qword ptr [esp + 0x50]
    uint32_t t27 = static_cast<uint32_t>(ctx.esp + 0x00000050u);
    double t28 = mem.rf64(t27);
    ctx.fpu_push(t28);
    // 0x004334b8: cmp dword ptr [esp + 0x28], ebx
    uint32_t t29 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t30 = mem.r32(t29);
    uint32_t t31 = static_cast<uint32_t>(t30 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t30, ctx.ebx, t31);
    // 0x004334bc: mov dword ptr [esp + 0x10], ebx
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t32, ctx.ebx);
    // 0x004334c0: je 0x4334fb
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004334fb;
    goto bb_004334c2;
}
bb_004334fb: {
    // 0x004334fb: fldz
    ctx.fpu_push(0.0);
    // 0x004334fd: fucomp st(1)
    double t33 = ctx.fpu_st(0);
    double t34 = ctx.fpu_st(1);
    ctx.fpu_compare(t33, t34);
    ctx.fpu_pop();
    // 0x004334ff: fnstsw ax
    recomp_detail::w16(ctx.eax, static_cast<uint16_t>(ctx.fpu_sw));
    // 0x00433501: test ah, 0x44
    uint8_t t35 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8h(ctx.eax)) & static_cast<uint32_t>(uint8_t{0x44u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t35);
    // 0x00433504: jp 0x433526
    if (recomp_detail::eval_cond(ctx, Cond::P)) goto bb_00433526;
    goto bb_00433506;
}
bb_004334c2: {
    // 0x004334c2: mov ecx, dword ptr [esp + 0x38]
    uint32_t t36 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    uint32_t t37 = mem.r32(t36);
    ctx.ecx = static_cast<uint32_t>(t37);
    // 0x004334c6: fstp st(0)
    double t38 = ctx.fpu_st(0);
    ctx.fpu_st(0) = t38;
    ctx.fpu_pop();
    // 0x004334c8: mov edi, dword ptr [esp + 0x3c]
    uint32_t t39 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    uint32_t t40 = mem.r32(t39);
    ctx.edi = static_cast<uint32_t>(t40);
    // 0x004334cc: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x004334ce: or eax, edi
    uint32_t t41 = static_cast<uint32_t>(ctx.eax | ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t41);
    ctx.eax = static_cast<uint32_t>(t41);
    // 0x004334d0: je 0x4334de
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004334de;
    goto bb_004334d2;
}
bb_00433526: {
    // 0x00433526: mov edi, dword ptr [esp + 0x3c]
    uint32_t t42 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    uint32_t t43 = mem.r32(t42);
    ctx.edi = static_cast<uint32_t>(t43);
    // 0x0043352a: fstp qword ptr [esp + 0x60]
    double t44 = ctx.fpu_st(0);
    uint32_t t45 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    mem.wf64(t45, t44);
    ctx.fpu_pop();
    goto bb_0043352e;
}
bb_00433506: {
    // 0x00433506: fstp st(0)
    double t46 = ctx.fpu_st(0);
    ctx.fpu_st(0) = t46;
    ctx.fpu_pop();
    // 0x00433508: call dword ptr [0x51b334]
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, 0x0043350eu);
    hle_iat_call(ctx, mem, 0x0051b334u);
    // 0x0043350e: test eax, eax
    uint32_t t48 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t48);
    // 0x00433510: mov dword ptr [esp + 0x14], eax
    uint32_t t49 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t49, ctx.eax);
    // 0x00433514: fild dword ptr [esp + 0x14]
    uint32_t t50 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    double t51 = static_cast<double>(static_cast<int32_t>(mem.r32(t50)));
    ctx.fpu_push(t51);
    // 0x00433518: jge 0x433520
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_00433520;
    goto bb_0043351a;
}
bb_004334de: {
    // 0x004334de: lea ecx, [esp + 0x18]
    uint32_t t52 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.ecx = static_cast<uint32_t>(t52);
    // 0x004334e2: push ecx
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, ctx.ecx);
    // 0x004334e3: call dword ptr [0x51b1d4]
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, 0x004334e9u);
    hle_iat_call(ctx, mem, 0x0051b1d4u);
    // 0x004334e9: mov eax, dword ptr [esp + 0x1c]
    uint32_t t55 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t56 = mem.r32(t55);
    ctx.eax = static_cast<uint32_t>(t56);
    // 0x004334ed: mov ecx, dword ptr [esp + 0x18]
    uint32_t t57 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t58 = mem.r32(t57);
    ctx.ecx = static_cast<uint32_t>(t58);
    // 0x004334f1: mov dword ptr [esp + 0x48], ecx
    uint32_t t59 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    mem.w32(t59, ctx.ecx);
    // 0x004334f5: mov dword ptr [esp + 0x4c], eax
    uint32_t t60 = static_cast<uint32_t>(ctx.esp + 0x0000004cu);
    mem.w32(t60, ctx.eax);
    // 0x004334f9: jmp 0x43352e
    goto bb_0043352e;
}
bb_004334d2: {
    // 0x004334d2: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x004334d4: mov dword ptr [esp + 0x48], ecx
    uint32_t t61 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    mem.w32(t61, ctx.ecx);
    // 0x004334d8: mov dword ptr [esp + 0x4c], eax
    uint32_t t62 = static_cast<uint32_t>(ctx.esp + 0x0000004cu);
    mem.w32(t62, ctx.eax);
    // 0x004334dc: jmp 0x43352e
}
bb_0043352e: {
    // 0x0043352e: mov ebp, dword ptr [0x51b078]
    uint32_t t63 = mem.r32(0x0051b078u);
    ctx.ebp = static_cast<uint32_t>(t63);
    goto bb_00433534;
}
bb_00433520: {
    // 0x00433520: fmul qword ptr [0x53d810]
    double t64 = ctx.fpu_st(0);
    double t65 = mem.rf64(0x0053d810u);
    double t66 = (t64 * t65);
    ctx.fpu_st(0) = t66;
    goto bb_00433526;
}
bb_0043351a: {
    // 0x0043351a: fadd qword ptr [0x53d818]
    double t67 = ctx.fpu_st(0);
    double t68 = mem.rf64(0x0053d818u);
    double t69 = (t67 + t68);
    ctx.fpu_st(0) = t69;
    goto bb_00433520;
}
bb_00433534: {
    // 0x00433534: cmp dword ptr [0x76e68c], 1
    uint32_t t70 = mem.r32(0x0076e68cu);
    uint32_t t71 = static_cast<uint32_t>(t70 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t70, 0x00000001u, t71);
    // 0x0043353b: jne 0x433544
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00433544;
    goto bb_0043353d;
}
bb_00433544: {
    // 0x00433544: mov eax, dword ptr [0x5550a8]
    uint32_t t72 = mem.r32(0x005550a8u);
    ctx.eax = static_cast<uint32_t>(t72);
    // 0x00433549: cmp eax, ebx
    uint32_t t73 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t73);
    // 0x0043354b: je 0x43357f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043357f;
    goto bb_0043354d;
}
bb_0043353d: {
    // 0x0043353d: push 0x5550c4
    uint32_t t74 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    mem.w32(t74, 0x005550c4u);
    // 0x00433542: call ebp
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, 0x00433544u);
    call_indirect(ctx, mem, ctx.ebp);
    goto bb_00433544;
}
bb_0043357f: {
    // 0x0043357f: cmp dword ptr [0x76e68c], 1
    uint32_t t76 = mem.r32(0x0076e68cu);
    uint32_t t77 = static_cast<uint32_t>(t76 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t76, 0x00000001u, t77);
    // 0x00433586: mov dword ptr [0x5550b4], ebx
    mem.w32(0x005550b4u, ctx.ebx);
    // 0x0043358c: mov dword ptr [0x5550b8], ebx
    mem.w32(0x005550b8u, ctx.ebx);
    // 0x00433592: mov dword ptr [0x5550bc], ebx
    mem.w32(0x005550bcu, ctx.ebx);
    // 0x00433598: mov dword ptr [0x5550c0], ebx
    mem.w32(0x005550c0u, ctx.ebx);
    // 0x0043359e: jne 0x4335ab
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004335ab;
    goto bb_004335a0;
}
bb_0043354d: {
    // 0x0043354d: mov edi, dword ptr [0x5550ac]
    uint32_t t78 = mem.r32(0x005550acu);
    ctx.edi = static_cast<uint32_t>(t78);
    // 0x00433553: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x00433555: call 0x4c02b0
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, 0x0043355au);
    sub_004c02b0(ctx, mem);
    // 0x0043355a: lea ecx, [edi - 1]
    uint32_t t80 = static_cast<uint32_t>(ctx.edi + 0xffffffffu);
    ctx.ecx = static_cast<uint32_t>(t80);
    // 0x0043355d: cmp ecx, ebx
    uint32_t t81 = static_cast<uint32_t>(ctx.ecx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebx, t81);
    // 0x0043355f: mov dword ptr [esi + 8], ebx
    uint32_t t82 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t82, ctx.ebx);
    // 0x00433562: mov dword ptr [esi + 0xc], edi
    uint32_t t83 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t83, ctx.edi);
    // 0x00433565: jle 0x433576
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_00433576;
    goto bb_00433567;
}
bb_004335ab: {
    // 0x004335ab: mov edx, dword ptr [0x5542d0]
    uint32_t t84 = mem.r32(0x005542d0u);
    ctx.edx = static_cast<uint32_t>(t84);
    // 0x004335b1: push 0x4e7
    uint32_t t85 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t85);
    mem.w32(t85, 0x000004e7u);
    // 0x004335b6: push ebx
    uint32_t t86 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t86);
    mem.w32(t86, ctx.ebx);
    // 0x004335b7: push -1
    uint32_t t87 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t87);
    mem.w32(t87, 0xffffffffu);
    // 0x004335b9: push 0x80
    uint32_t t88 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t88);
    mem.w32(t88, 0x00000080u);
    // 0x004335be: push 0x80
    uint32_t t89 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t89);
    mem.w32(t89, 0x00000080u);
    // 0x004335c3: push ebx
    uint32_t t90 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    mem.w32(t90, ctx.ebx);
    // 0x004335c4: push ebx
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, ctx.ebx);
    // 0x004335c5: push 0x80
    uint32_t t92 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    mem.w32(t92, 0x00000080u);
    // 0x004335ca: push ebx
    uint32_t t93 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    mem.w32(t93, ctx.ebx);
    // 0x004335cb: push ebx
    uint32_t t94 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t94);
    mem.w32(t94, ctx.ebx);
    // 0x004335cc: push edx
    uint32_t t95 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t95);
    mem.w32(t95, ctx.edx);
    // 0x004335cd: push ebx
    uint32_t t96 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    mem.w32(t96, ctx.ebx);
    // 0x004335ce: mov edx, 0x80
    ctx.edx = static_cast<uint32_t>(0x00000080u);
    // 0x004335d3: call 0x415580
    uint32_t t97 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t97);
    mem.w32(t97, 0x004335d8u);
    sub_00415580(ctx, mem);
    // 0x004335d8: mov eax, dword ptr [0x5542d4]
    uint32_t t98 = mem.r32(0x005542d4u);
    ctx.eax = static_cast<uint32_t>(t98);
    // 0x004335dd: push 0x4e7
    uint32_t t99 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t99);
    mem.w32(t99, 0x000004e7u);
    // 0x004335e2: push ebx
    uint32_t t100 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t100);
    mem.w32(t100, ctx.ebx);
    // 0x004335e3: push -1
    uint32_t t101 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t101);
    mem.w32(t101, 0xffffffffu);
    // 0x004335e5: push 0x80
    uint32_t t102 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    mem.w32(t102, 0x00000080u);
    // 0x004335ea: push 0x80
    uint32_t t103 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    mem.w32(t103, 0x00000080u);
    // 0x004335ef: push ebx
    uint32_t t104 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t104);
    mem.w32(t104, ctx.ebx);
    // 0x004335f0: push ebx
    uint32_t t105 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t105);
    mem.w32(t105, ctx.ebx);
    // 0x004335f1: push 0x80
    uint32_t t106 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t106);
    mem.w32(t106, 0x00000080u);
    // 0x004335f6: push ebx
    uint32_t t107 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t107);
    mem.w32(t107, ctx.ebx);
    // 0x004335f7: push ebx
    uint32_t t108 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t108);
    mem.w32(t108, ctx.ebx);
    // 0x004335f8: push eax
    uint32_t t109 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t109);
    mem.w32(t109, ctx.eax);
    // 0x004335f9: push ebx
    uint32_t t110 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t110);
    mem.w32(t110, ctx.ebx);
    // 0x004335fa: mov edx, 0x80
    ctx.edx = static_cast<uint32_t>(0x00000080u);
    // 0x004335ff: call 0x415580
    uint32_t t111 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t111);
    mem.w32(t111, 0x00433604u);
    sub_00415580(ctx, mem);
    // 0x00433604: mov ecx, dword ptr [0x5542d8]
    uint32_t t112 = mem.r32(0x005542d8u);
    ctx.ecx = static_cast<uint32_t>(t112);
    // 0x0043360a: add esp, 0x60
    uint32_t t113 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000060u, t113);
    ctx.esp = static_cast<uint32_t>(t113);
    // 0x0043360d: push 0x4e7
    uint32_t t114 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t114);
    mem.w32(t114, 0x000004e7u);
    // 0x00433612: push ebx
    uint32_t t115 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t115);
    mem.w32(t115, ctx.ebx);
    // 0x00433613: push -1
    uint32_t t116 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t116);
    mem.w32(t116, 0xffffffffu);
    // 0x00433615: push 0x80
    uint32_t t117 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t117);
    mem.w32(t117, 0x00000080u);
    // 0x0043361a: push 0x80
    uint32_t t118 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    mem.w32(t118, 0x00000080u);
    // 0x0043361f: push ebx
    uint32_t t119 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t119);
    mem.w32(t119, ctx.ebx);
    // 0x00433620: push ebx
    uint32_t t120 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t120);
    mem.w32(t120, ctx.ebx);
    // 0x00433621: push 0x80
    uint32_t t121 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t121);
    mem.w32(t121, 0x00000080u);
    // 0x00433626: push ebx
    uint32_t t122 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t122);
    mem.w32(t122, ctx.ebx);
    // 0x00433627: push ebx
    uint32_t t123 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t123);
    mem.w32(t123, ctx.ebx);
    // 0x00433628: push ecx
    uint32_t t124 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t124);
    mem.w32(t124, ctx.ecx);
    // 0x00433629: push ebx
    uint32_t t125 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t125);
    mem.w32(t125, ctx.ebx);
    // 0x0043362a: mov edx, 0x80
    ctx.edx = static_cast<uint32_t>(0x00000080u);
    // 0x0043362f: call 0x415580
    uint32_t t126 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t126);
    mem.w32(t126, 0x00433634u);
    sub_00415580(ctx, mem);
    // 0x00433634: add esp, 0x30
    uint32_t t127 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000030u, t127);
    ctx.esp = static_cast<uint32_t>(t127);
    // 0x00433637: push 0x5550c4
    uint32_t t128 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t128);
    mem.w32(t128, 0x005550c4u);
    // 0x0043363c: call ebp
    uint32_t t129 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t129);
    mem.w32(t129, 0x0043363eu);
    call_indirect(ctx, mem, ctx.ebp);
    // 0x0043363e: mov eax, dword ptr [0x5550a8]
    uint32_t t130 = mem.r32(0x005550a8u);
    ctx.eax = static_cast<uint32_t>(t130);
    // 0x00433643: call 0x4c04e0
    uint32_t t131 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t131);
    mem.w32(t131, 0x00433648u);
    sub_004c04e0(ctx, mem);
    // 0x00433648: push 0x5550c4
    uint32_t t132 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t132);
    mem.w32(t132, 0x005550c4u);
    // 0x0043364d: call dword ptr [0x51b070]
    uint32_t t133 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t133);
    mem.w32(t133, 0x00433653u);
    hle_iat_call(ctx, mem, 0x0051b070u);
    // 0x00433653: mov edx, dword ptr [0x54d36c]
    uint32_t t134 = mem.r32(0x0054d36cu);
    ctx.edx = static_cast<uint32_t>(t134);
    // 0x00433659: cmp edx, dword ptr [0x55d1d0]
    uint32_t t135 = mem.r32(0x0055d1d0u);
    uint32_t t136 = static_cast<uint32_t>(ctx.edx - t135);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, t135, t136);
    // 0x0043365f: jne 0x43366e
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043366e;
    goto bb_00433661;
}
bb_004335a0: {
    // 0x004335a0: push 0x5550c4
    uint32_t t137 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t137);
    mem.w32(t137, 0x005550c4u);
    // 0x004335a5: call dword ptr [0x51b070]
    uint32_t t138 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t138);
    mem.w32(t138, 0x004335abu);
    hle_iat_call(ctx, mem, 0x0051b070u);
    goto bb_004335ab;
}
bb_00433576: {
    // 0x00433576: mov edi, dword ptr [esp + 0x3c]
    uint32_t t139 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    uint32_t t140 = mem.r32(t139);
    ctx.edi = static_cast<uint32_t>(t140);
    // 0x0043357a: mov dword ptr [esi], ebx
    mem.w32(ctx.esi, ctx.ebx);
    // 0x0043357c: mov byte ptr [esi + 4], bl
    uint32_t t141 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w8(t141, recomp_detail::r8l(ctx.ebx));
    goto bb_0043357f;
}
bb_00433567: {
    // 0x00433567: sub ecx, 1
    uint32_t t142 = static_cast<uint32_t>(ctx.ecx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000001u, t142);
    ctx.ecx = static_cast<uint32_t>(t142);
    // 0x0043356a: lea eax, [esi + 0x10]
    uint32_t t143 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    ctx.eax = static_cast<uint32_t>(t143);
    // 0x0043356d: mov dword ptr [esi], eax
    mem.w32(ctx.esi, ctx.eax);
    // 0x0043356f: mov byte ptr [esi + 4], bl
    uint32_t t144 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w8(t144, recomp_detail::r8l(ctx.ebx));
    // 0x00433572: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x00433574: jne 0x433567
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00433567;
    goto bb_00433576;
}
bb_0043366e: {
    // 0x0043366e: mov ecx, dword ptr [0x77c7a4]
    uint32_t t145 = mem.r32(0x0077c7a4u);
    ctx.ecx = static_cast<uint32_t>(t145);
    // 0x00433674: xor esi, esi
    uint32_t t146 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t146);
    ctx.esi = static_cast<uint32_t>(t146);
    // 0x00433676: cmp ecx, ebx
    uint32_t t147 = static_cast<uint32_t>(ctx.ecx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebx, t147);
    // 0x00433678: je 0x433689
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00433689;
    goto bb_0043367a;
}
bb_00433661: {
    // 0x00433661: call 0x490a90
    uint32_t t148 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t148);
    mem.w32(t148, 0x00433666u);
    sub_00490a90(ctx, mem);
    // 0x00433666: cmp eax, ebx
    uint32_t t149 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t149);
    // 0x00433668: je 0x43375f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043375f;
    goto bb_0043366e;
}
bb_00433689: {
    // 0x00433689: mov eax, 0x77cbb4
    ctx.eax = static_cast<uint32_t>(0x0077cbb4u);
    // 0x0043368e: mov edi, edi
    ctx.edi = static_cast<uint32_t>(ctx.edi);
    goto bb_00433690;
}
bb_0043367a: {
    // 0x0043367a: push -1
    uint32_t t150 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t150);
    mem.w32(t150, 0xffffffffu);
    // 0x0043367c: push ecx
    uint32_t t151 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t151);
    mem.w32(t151, ctx.ecx);
    // 0x0043367d: call dword ptr [0x51b040]
    uint32_t t152 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t152);
    mem.w32(t152, 0x00433683u);
    hle_iat_call(ctx, mem, 0x0051b040u);
    // 0x00433683: mov ecx, dword ptr [0x77c7a4]
    uint32_t t153 = mem.r32(0x0077c7a4u);
    ctx.ecx = static_cast<uint32_t>(t153);
    goto bb_00433689;
}
bb_00433690: {
    // 0x00433690: cmp dword ptr [eax], ebx
    uint32_t t154 = mem.r32(ctx.eax);
    uint32_t t155 = static_cast<uint32_t>(t154 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t154, ctx.ebx, t155);
    // 0x00433692: je 0x4336a3
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004336a3;
    goto bb_00433694;
}
bb_004336a3: {
    // 0x004336a3: cmp ecx, ebx
    uint32_t t156 = static_cast<uint32_t>(ctx.ecx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebx, t156);
    // 0x004336a5: je 0x4336b1
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004336b1;
    goto bb_004336a7;
}
bb_00433694: {
    // 0x00433694: add eax, 4
    uint32_t t157 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000004u, t157);
    ctx.eax = static_cast<uint32_t>(t157);
    // 0x00433697: cmp eax, 0x77cbbc
    uint32_t t158 = static_cast<uint32_t>(ctx.eax - 0x0077cbbcu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x0077cbbcu, t158);
    // 0x0043369c: jl 0x433690
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_00433690;
    goto bb_0043369e;
}
bb_004336b1: {
    // 0x004336b1: cmp esi, 1
    uint32_t t159 = static_cast<uint32_t>(ctx.esi - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00000001u, t159);
    // 0x004336b4: je 0x43375f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043375f;
    goto bb_004336ba;
}
bb_004336a7: {
    // 0x004336a7: push ebx
    uint32_t t160 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t160);
    mem.w32(t160, ctx.ebx);
    // 0x004336a8: push 1
    uint32_t t161 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t161);
    mem.w32(t161, 0x00000001u);
    // 0x004336aa: push ecx
    uint32_t t162 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t162);
    mem.w32(t162, ctx.ecx);
    // 0x004336ab: call dword ptr [0x51b0d8]
    uint32_t t163 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t163);
    mem.w32(t163, 0x004336b1u);
    hle_iat_call(ctx, mem, 0x0051b0d8u);
    goto bb_004336b1;
}
bb_0043369e: {
    // 0x0043369e: mov esi, 1
    ctx.esi = static_cast<uint32_t>(0x00000001u);
    goto bb_004336a3;
}
bb_004336ba: {
    // 0x004336ba: cmp dword ptr [esp + 0x10], -1
    uint32_t t164 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t165 = mem.r32(t164);
    uint32_t t166 = static_cast<uint32_t>(t165 - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t165, 0xffffffffu, t166);
    // 0x004336bf: jae 0x4336c6
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004336c6;
    goto bb_004336c1;
}
bb_004336c6: {
    // 0x004336c6: cmp dword ptr [esp + 0x28], ebx
    uint32_t t167 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t168 = mem.r32(t167);
    uint32_t t169 = static_cast<uint32_t>(t168 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t168, ctx.ebx, t169);
    // 0x004336ca: je 0x433711
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00433711;
    goto bb_004336cc;
}
bb_004336c1: {
    // 0x004336c1: add dword ptr [esp + 0x10], 1
    uint32_t t170 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t171 = mem.r32(t170);
    uint32_t t172 = static_cast<uint32_t>(t171 + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t171, 0x00000001u, t172);
    mem.w32(t170, t172);
    goto bb_004336c6;
}
bb_00433711: {
    // 0x00433711: fldz
    ctx.fpu_push(0.0);
    // 0x00433713: fld qword ptr [esp + 0x50]
    uint32_t t173 = static_cast<uint32_t>(ctx.esp + 0x00000050u);
    double t174 = mem.rf64(t173);
    ctx.fpu_push(t174);
    // 0x00433717: fucom st(1)
    double t175 = ctx.fpu_st(0);
    double t176 = ctx.fpu_st(1);
    ctx.fpu_compare(t175, t176);
    // 0x00433719: fnstsw ax
    recomp_detail::w16(ctx.eax, static_cast<uint16_t>(ctx.fpu_sw));
    // 0x0043371b: fstp st(1)
    double t177 = ctx.fpu_st(0);
    ctx.fpu_st(1) = t177;
    ctx.fpu_pop();
    // 0x0043371d: test ah, 0x44
    uint8_t t178 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8h(ctx.eax)) & static_cast<uint32_t>(uint8_t{0x44u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t178);
    // 0x00433720: jp 0x433742
    if (recomp_detail::eval_cond(ctx, Cond::P)) goto bb_00433742;
    goto bb_00433722;
}
bb_004336cc: {
    // 0x004336cc: mov ecx, dword ptr [esp + 0x38]
    uint32_t t179 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    uint32_t t180 = mem.r32(t179);
    ctx.ecx = static_cast<uint32_t>(t180);
    // 0x004336d0: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x004336d2: or eax, edi
    uint32_t t181 = static_cast<uint32_t>(ctx.eax | ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t181);
    ctx.eax = static_cast<uint32_t>(t181);
    // 0x004336d4: je 0x4336e2
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004336e2;
    goto bb_004336d6;
}
bb_00433742: {
    // 0x00433742: fsub qword ptr [esp + 0x60]
    double t182 = ctx.fpu_st(0);
    uint32_t t183 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    double t184 = mem.rf64(t183);
    double t185 = (t182 - t184);
    ctx.fpu_st(0) = t185;
    goto bb_00433746;
}
bb_00433722: {
    // 0x00433722: fstp st(0)
    double t186 = ctx.fpu_st(0);
    ctx.fpu_st(0) = t186;
    ctx.fpu_pop();
    // 0x00433724: call dword ptr [0x51b334]
    uint32_t t187 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t187);
    mem.w32(t187, 0x0043372au);
    hle_iat_call(ctx, mem, 0x0051b334u);
    // 0x0043372a: test eax, eax
    uint32_t t188 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t188);
    // 0x0043372c: mov dword ptr [esp + 0x14], eax
    uint32_t t189 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t189, ctx.eax);
    // 0x00433730: fild dword ptr [esp + 0x14]
    uint32_t t190 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    double t191 = static_cast<double>(static_cast<int32_t>(mem.r32(t190)));
    ctx.fpu_push(t191);
    // 0x00433734: jge 0x43373c
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0043373c;
    goto bb_00433736;
}
bb_004336e2: {
    // 0x004336e2: lea ecx, [esp + 0x18]
    uint32_t t192 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.ecx = static_cast<uint32_t>(t192);
    // 0x004336e6: push ecx
    uint32_t t193 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t193);
    mem.w32(t193, ctx.ecx);
    // 0x004336e7: call dword ptr [0x51b1d4]
    uint32_t t194 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t194);
    mem.w32(t194, 0x004336edu);
    hle_iat_call(ctx, mem, 0x0051b1d4u);
    // 0x004336ed: mov eax, dword ptr [esp + 0x1c]
    uint32_t t195 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t196 = mem.r32(t195);
    ctx.eax = static_cast<uint32_t>(t196);
    // 0x004336f1: mov ecx, dword ptr [esp + 0x18]
    uint32_t t197 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t198 = mem.r32(t197);
    ctx.ecx = static_cast<uint32_t>(t198);
    goto bb_004336f5;
}
bb_004336d6: {
    // 0x004336d6: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x004336d8: mov dword ptr [esp + 0x18], ecx
    uint32_t t199 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t199, ctx.ecx);
    // 0x004336dc: mov dword ptr [esp + 0x1c], eax
    uint32_t t200 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t200, ctx.eax);
    // 0x004336e0: jmp 0x4336f5
    goto bb_004336f5;
}
bb_00433746: {
    // 0x00433746: fstp dword ptr [esp + 0x14]
    double t201 = ctx.fpu_st(0);
    uint32_t t202 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.wf32(t202, static_cast<float>(t201));
    ctx.fpu_pop();
    // 0x0043374a: fld dword ptr [esp + 0x14]
    uint32_t t203 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    double t204 = static_cast<double>(mem.rf32(t203));
    ctx.fpu_push(t204);
    // 0x0043374e: fcomp qword ptr [0x53d6c0]
    double t205 = ctx.fpu_st(0);
    double t206 = mem.rf64(0x0053d6c0u);
    ctx.fpu_compare(t205, t206);
    ctx.fpu_pop();
    // 0x00433754: fnstsw ax
    recomp_detail::w16(ctx.eax, static_cast<uint16_t>(ctx.fpu_sw));
    // 0x00433756: test ah, 5
    uint8_t t207 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8h(ctx.eax)) & static_cast<uint32_t>(uint8_t{0x05u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t207);
    // 0x00433759: jnp 0x433534
    if (recomp_detail::eval_cond(ctx, Cond::NP)) goto bb_00433534;
    goto bb_0043375f;
}
bb_0043373c: {
    // 0x0043373c: fmul qword ptr [0x53d810]
    double t208 = ctx.fpu_st(0);
    double t209 = mem.rf64(0x0053d810u);
    double t210 = (t208 * t209);
    ctx.fpu_st(0) = t210;
    goto bb_00433742;
}
bb_00433736: {
    // 0x00433736: fadd qword ptr [0x53d818]
    double t211 = ctx.fpu_st(0);
    double t212 = mem.rf64(0x0053d818u);
    double t213 = (t211 + t212);
    ctx.fpu_st(0) = t213;
    goto bb_0043373c;
}
bb_004336f5: {
    // 0x004336f5: sub ecx, dword ptr [esp + 0x48]
    uint32_t t214 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    uint32_t t215 = mem.r32(t214);
    uint32_t t216 = static_cast<uint32_t>(ctx.ecx - t215);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, t215, t216);
    ctx.ecx = static_cast<uint32_t>(t216);
    // 0x004336f9: sbb eax, dword ptr [esp + 0x4c]
    uint32_t t217 = static_cast<uint32_t>(ctx.esp + 0x0000004cu);
    uint32_t t218 = mem.r32(t217);
    uint32_t t219 = recomp_detail::get_flag(ctx, kFlagCF);
    uint32_t t220 = static_cast<uint32_t>(ctx.eax - t218);
    uint32_t t221 = static_cast<uint32_t>(t220 - t219);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, t218, t221, t219);
    ctx.eax = static_cast<uint32_t>(t221);
    // 0x004336fd: mov dword ptr [esp + 0x20], ecx
    uint32_t t222 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t222, ctx.ecx);
    // 0x00433701: mov dword ptr [esp + 0x24], eax
    uint32_t t223 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t223, ctx.eax);
    // 0x00433705: fild qword ptr [esp + 0x20]
    uint32_t t224 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    double t225 = static_cast<double>(static_cast<int64_t>(mem.r64(t224)));
    ctx.fpu_push(t225);
    // 0x00433709: fild qword ptr [esp + 0x30]
    uint32_t t226 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    double t227 = static_cast<double>(static_cast<int64_t>(mem.r64(t226)));
    ctx.fpu_push(t227);
    // 0x0043370d: fdivp st(1)
    double t228 = ctx.fpu_st(1);
    double t229 = ctx.fpu_st(0);
    double t230 = (t228 / t229);
    ctx.fpu_st(1) = t230;
    ctx.fpu_pop();
    // 0x0043370f: jmp 0x433746
    goto bb_00433746;
}
}

// sub_0043b8d0 | subsystem=Core/Windows | canonical | 9 blocks | 46 insns
void sub_0043b8d0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043b8d0: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x0043b8d1: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x0043b8d3: and esp, 0xfffffff8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xfffffff8u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x0043b8d6: sub esp, 8
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000008u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000008u, t2);
    ctx.esp = static_cast<uint32_t>(t2);
    // 0x0043b8d9: cmp dword ptr [esi], 0
    uint32_t t3 = mem.r32(ctx.esi);
    uint32_t t4 = static_cast<uint32_t>(t3 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t3, 0x00000000u, t4);
    // 0x0043b8dc: je 0x43b90b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043b90b;
    goto bb_0043b8de;
}
bb_0043b90b: {
    // 0x0043b90b: fldz
    ctx.fpu_push(0.0);
    // 0x0043b90d: fcomp qword ptr [esi + 0x28]
    double t5 = ctx.fpu_st(0);
    uint32_t t6 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    double t7 = mem.rf64(t6);
    ctx.fpu_compare(t5, t7);
    ctx.fpu_pop();
    // 0x0043b910: fnstsw ax
    recomp_detail::w16(ctx.eax, static_cast<uint16_t>(ctx.fpu_sw));
    // 0x0043b912: test ah, 0x44
    uint8_t t8 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8h(ctx.eax)) & static_cast<uint32_t>(uint8_t{0x44u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t8);
    // 0x0043b915: jnp 0x43b924
    if (recomp_detail::eval_cond(ctx, Cond::NP)) goto bb_0043b924;
    goto bb_0043b917;
}
bb_0043b8de: {
    // 0x0043b8de: mov ecx, dword ptr [esi + 0x10]
    uint32_t t9 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    uint32_t t10 = mem.r32(t9);
    ctx.ecx = static_cast<uint32_t>(t10);
    // 0x0043b8e1: mov eax, dword ptr [esi + 0x14]
    uint32_t t11 = static_cast<uint32_t>(ctx.esi + 0x00000014u);
    uint32_t t12 = mem.r32(t11);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0043b8e4: mov edx, ecx
    ctx.edx = static_cast<uint32_t>(ctx.ecx);
    // 0x0043b8e6: or edx, eax
    uint32_t t13 = static_cast<uint32_t>(ctx.edx | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t13);
    ctx.edx = static_cast<uint32_t>(t13);
    // 0x0043b8e8: jne 0x43b8fb
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043b8fb;
    goto bb_0043b8ea;
}
bb_0043b924: {
    // 0x0043b924: call dword ptr [0x51b334]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x0043b92au);
    hle_iat_call(ctx, mem, 0x0051b334u);
    // 0x0043b92a: test eax, eax
    uint32_t t15 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t15);
    // 0x0043b92c: mov dword ptr [esp], eax
    mem.w32(ctx.esp, ctx.eax);
    // 0x0043b92f: fild dword ptr [esp]
    double t16 = static_cast<double>(static_cast<int32_t>(mem.r32(ctx.esp)));
    ctx.fpu_push(t16);
    // 0x0043b932: jge 0x43b93a
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0043b93a;
    goto bb_0043b934;
}
bb_0043b917: {
    // 0x0043b917: fld qword ptr [esi + 0x28]
    uint32_t t17 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    double t18 = mem.rf64(t17);
    ctx.fpu_push(t18);
    // 0x0043b91a: fst qword ptr [esi + 0x38]
    double t19 = ctx.fpu_st(0);
    uint32_t t20 = static_cast<uint32_t>(ctx.esi + 0x00000038u);
    mem.wf64(t20, t19);
    // 0x0043b91d: fstp qword ptr [esi + 0x30]
    double t21 = ctx.fpu_st(0);
    uint32_t t22 = static_cast<uint32_t>(ctx.esi + 0x00000030u);
    mem.wf64(t22, t21);
    ctx.fpu_pop();
    // 0x0043b920: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0043b922: pop ebp
    uint32_t t23 = ctx.esp;
    uint32_t t24 = mem.r32(t23);
    uint32_t t25 = static_cast<uint32_t>(t23 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    ctx.ebp = static_cast<uint32_t>(t24);
    // 0x0043b923: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043b8fb: {
    // 0x0043b8fb: mov dword ptr [esi + 0x20], ecx
    uint32_t t26 = static_cast<uint32_t>(ctx.esi + 0x00000020u);
    mem.w32(t26, ctx.ecx);
    // 0x0043b8fe: mov dword ptr [esi + 0x24], eax
    uint32_t t27 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    mem.w32(t27, ctx.eax);
    // 0x0043b901: mov dword ptr [esi + 0x18], ecx
    uint32_t t28 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    mem.w32(t28, ctx.ecx);
    // 0x0043b904: mov dword ptr [esi + 0x1c], eax
    uint32_t t29 = static_cast<uint32_t>(ctx.esi + 0x0000001cu);
    mem.w32(t29, ctx.eax);
    // 0x0043b907: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0043b909: pop ebp
    uint32_t t30 = ctx.esp;
    uint32_t t31 = mem.r32(t30);
    uint32_t t32 = static_cast<uint32_t>(t30 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    ctx.ebp = static_cast<uint32_t>(t31);
    // 0x0043b90a: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043b8ea: {
    // 0x0043b8ea: lea eax, [esp]
    ctx.eax = static_cast<uint32_t>(ctx.esp);
    // 0x0043b8ed: push eax
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, ctx.eax);
    // 0x0043b8ee: call dword ptr [0x51b1d4]
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x0043b8f4u);
    hle_iat_call(ctx, mem, 0x0051b1d4u);
    // 0x0043b8f4: mov eax, dword ptr [esp + 4]
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint32_t t36 = mem.r32(t35);
    ctx.eax = static_cast<uint32_t>(t36);
    // 0x0043b8f8: mov ecx, dword ptr [esp]
    uint32_t t37 = mem.r32(ctx.esp);
    ctx.ecx = static_cast<uint32_t>(t37);
    goto bb_0043b8fb;
}
bb_0043b93a: {
    // 0x0043b93a: fmul qword ptr [0x53d810]
    double t38 = ctx.fpu_st(0);
    double t39 = mem.rf64(0x0053d810u);
    double t40 = (t38 * t39);
    ctx.fpu_st(0) = t40;
    // 0x0043b940: fst qword ptr [esi + 0x38]
    double t41 = ctx.fpu_st(0);
    uint32_t t42 = static_cast<uint32_t>(ctx.esi + 0x00000038u);
    mem.wf64(t42, t41);
    // 0x0043b943: fstp qword ptr [esi + 0x30]
    double t43 = ctx.fpu_st(0);
    uint32_t t44 = static_cast<uint32_t>(ctx.esi + 0x00000030u);
    mem.wf64(t44, t43);
    ctx.fpu_pop();
    // 0x0043b946: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0043b948: pop ebp
    uint32_t t45 = ctx.esp;
    uint32_t t46 = mem.r32(t45);
    uint32_t t47 = static_cast<uint32_t>(t45 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    ctx.ebp = static_cast<uint32_t>(t46);
    // 0x0043b949: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043b934: {
    // 0x0043b934: fadd qword ptr [0x53d818]
    double t48 = ctx.fpu_st(0);
    double t49 = mem.rf64(0x0053d818u);
    double t50 = (t48 + t49);
    ctx.fpu_st(0) = t50;
    goto bb_0043b93a;
}
}

// sub_0043b950 | subsystem=Core/Windows | canonical | 9 blocks | 56 insns
void sub_0043b950(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0043b950: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x0043b951: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x0043b953: and esp, 0xfffffff8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xfffffff8u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x0043b956: sub esp, 8
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000008u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000008u, t2);
    ctx.esp = static_cast<uint32_t>(t2);
    // 0x0043b959: cmp dword ptr [esi], 0
    uint32_t t3 = mem.r32(ctx.esi);
    uint32_t t4 = static_cast<uint32_t>(t3 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t3, 0x00000000u, t4);
    // 0x0043b95c: je 0x43b99d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0043b99d;
    goto bb_0043b95e;
}
bb_0043b99d: {
    // 0x0043b99d: fldz
    ctx.fpu_push(0.0);
    // 0x0043b99f: fcomp qword ptr [esi + 0x28]
    double t5 = ctx.fpu_st(0);
    uint32_t t6 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    double t7 = mem.rf64(t6);
    ctx.fpu_compare(t5, t7);
    ctx.fpu_pop();
    // 0x0043b9a2: fnstsw ax
    recomp_detail::w16(ctx.eax, static_cast<uint16_t>(ctx.fpu_sw));
    // 0x0043b9a4: test ah, 0x44
    uint8_t t8 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8h(ctx.eax)) & static_cast<uint32_t>(uint8_t{0x44u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t8);
    // 0x0043b9a7: jnp 0x43b9bc
    if (recomp_detail::eval_cond(ctx, Cond::NP)) goto bb_0043b9bc;
    goto bb_0043b9a9;
}
bb_0043b95e: {
    // 0x0043b95e: mov ecx, dword ptr [esi + 0x10]
    uint32_t t9 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    uint32_t t10 = mem.r32(t9);
    ctx.ecx = static_cast<uint32_t>(t10);
    // 0x0043b961: mov eax, dword ptr [esi + 0x14]
    uint32_t t11 = static_cast<uint32_t>(ctx.esi + 0x00000014u);
    uint32_t t12 = mem.r32(t11);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0043b964: mov edx, ecx
    ctx.edx = static_cast<uint32_t>(ctx.ecx);
    // 0x0043b966: or edx, eax
    uint32_t t13 = static_cast<uint32_t>(ctx.edx | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t13);
    ctx.edx = static_cast<uint32_t>(t13);
    // 0x0043b968: jne 0x43b97b
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0043b97b;
    goto bb_0043b96a;
}
bb_0043b9bc: {
    // 0x0043b9bc: call dword ptr [0x51b334]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x0043b9c2u);
    hle_iat_call(ctx, mem, 0x0051b334u);
    // 0x0043b9c2: test eax, eax
    uint32_t t15 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t15);
    // 0x0043b9c4: mov dword ptr [esp], eax
    mem.w32(ctx.esp, ctx.eax);
    // 0x0043b9c7: fild dword ptr [esp]
    double t16 = static_cast<double>(static_cast<int32_t>(mem.r32(ctx.esp)));
    ctx.fpu_push(t16);
    // 0x0043b9ca: jge 0x43b9d2
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0043b9d2;
    goto bb_0043b9cc;
}
bb_0043b9a9: {
    // 0x0043b9a9: fld qword ptr [esi + 0x28]
    uint32_t t17 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    double t18 = mem.rf64(t17);
    ctx.fpu_push(t18);
    // 0x0043b9ac: fsub qword ptr [esi + 0x38]
    double t19 = ctx.fpu_st(0);
    uint32_t t20 = static_cast<uint32_t>(ctx.esi + 0x00000038u);
    double t21 = mem.rf64(t20);
    double t22 = (t19 - t21);
    ctx.fpu_st(0) = t22;
    // 0x0043b9af: fstp dword ptr [esp]
    double t23 = ctx.fpu_st(0);
    mem.wf32(ctx.esp, static_cast<float>(t23));
    ctx.fpu_pop();
    // 0x0043b9b2: fld dword ptr [esp]
    double t24 = static_cast<double>(mem.rf32(ctx.esp));
    ctx.fpu_push(t24);
    // 0x0043b9b5: fstp dword ptr [esi + 0x40]
    double t25 = ctx.fpu_st(0);
    uint32_t t26 = static_cast<uint32_t>(ctx.esi + 0x00000040u);
    mem.wf32(t26, static_cast<float>(t25));
    ctx.fpu_pop();
    // 0x0043b9b8: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0043b9ba: pop ebp
    uint32_t t27 = ctx.esp;
    uint32_t t28 = mem.r32(t27);
    uint32_t t29 = static_cast<uint32_t>(t27 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    ctx.ebp = static_cast<uint32_t>(t28);
    // 0x0043b9bb: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043b97b: {
    // 0x0043b97b: sub ecx, dword ptr [esi + 0x20]
    uint32_t t30 = static_cast<uint32_t>(ctx.esi + 0x00000020u);
    uint32_t t31 = mem.r32(t30);
    uint32_t t32 = static_cast<uint32_t>(ctx.ecx - t31);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, t31, t32);
    ctx.ecx = static_cast<uint32_t>(t32);
    // 0x0043b97e: sbb eax, dword ptr [esi + 0x24]
    uint32_t t33 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    uint32_t t34 = mem.r32(t33);
    uint32_t t35 = recomp_detail::get_flag(ctx, kFlagCF);
    uint32_t t36 = static_cast<uint32_t>(ctx.eax - t34);
    uint32_t t37 = static_cast<uint32_t>(t36 - t35);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, t34, t37, t35);
    ctx.eax = static_cast<uint32_t>(t37);
    // 0x0043b981: mov dword ptr [esp], ecx
    mem.w32(ctx.esp, ctx.ecx);
    // 0x0043b984: mov dword ptr [esp + 4], eax
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    mem.w32(t38, ctx.eax);
    // 0x0043b988: fild qword ptr [esp]
    double t39 = static_cast<double>(static_cast<int64_t>(mem.r64(ctx.esp)));
    ctx.fpu_push(t39);
    // 0x0043b98b: fild qword ptr [esi + 8]
    uint32_t t40 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    double t41 = static_cast<double>(static_cast<int64_t>(mem.r64(t40)));
    ctx.fpu_push(t41);
    // 0x0043b98e: fdivp st(1)
    double t42 = ctx.fpu_st(1);
    double t43 = ctx.fpu_st(0);
    double t44 = (t42 / t43);
    ctx.fpu_st(1) = t44;
    ctx.fpu_pop();
    // 0x0043b990: fstp dword ptr [esp]
    double t45 = ctx.fpu_st(0);
    mem.wf32(ctx.esp, static_cast<float>(t45));
    ctx.fpu_pop();
    // 0x0043b993: fld dword ptr [esp]
    double t46 = static_cast<double>(mem.rf32(ctx.esp));
    ctx.fpu_push(t46);
    // 0x0043b996: fstp dword ptr [esi + 0x40]
    double t47 = ctx.fpu_st(0);
    uint32_t t48 = static_cast<uint32_t>(ctx.esi + 0x00000040u);
    mem.wf32(t48, static_cast<float>(t47));
    ctx.fpu_pop();
    // 0x0043b999: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0043b99b: pop ebp
    uint32_t t49 = ctx.esp;
    uint32_t t50 = mem.r32(t49);
    uint32_t t51 = static_cast<uint32_t>(t49 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    ctx.ebp = static_cast<uint32_t>(t50);
    // 0x0043b99c: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043b96a: {
    // 0x0043b96a: lea eax, [esp]
    ctx.eax = static_cast<uint32_t>(ctx.esp);
    // 0x0043b96d: push eax
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, ctx.eax);
    // 0x0043b96e: call dword ptr [0x51b1d4]
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, 0x0043b974u);
    hle_iat_call(ctx, mem, 0x0051b1d4u);
    // 0x0043b974: mov eax, dword ptr [esp + 4]
    uint32_t t54 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint32_t t55 = mem.r32(t54);
    ctx.eax = static_cast<uint32_t>(t55);
    // 0x0043b978: mov ecx, dword ptr [esp]
    uint32_t t56 = mem.r32(ctx.esp);
    ctx.ecx = static_cast<uint32_t>(t56);
    goto bb_0043b97b;
}
bb_0043b9d2: {
    // 0x0043b9d2: fmul qword ptr [0x53d810]
    double t57 = ctx.fpu_st(0);
    double t58 = mem.rf64(0x0053d810u);
    double t59 = (t57 * t58);
    ctx.fpu_st(0) = t59;
    // 0x0043b9d8: fsub qword ptr [esi + 0x38]
    double t60 = ctx.fpu_st(0);
    uint32_t t61 = static_cast<uint32_t>(ctx.esi + 0x00000038u);
    double t62 = mem.rf64(t61);
    double t63 = (t60 - t62);
    ctx.fpu_st(0) = t63;
    // 0x0043b9db: fstp dword ptr [esp]
    double t64 = ctx.fpu_st(0);
    mem.wf32(ctx.esp, static_cast<float>(t64));
    ctx.fpu_pop();
    // 0x0043b9de: fld dword ptr [esp]
    double t65 = static_cast<double>(mem.rf32(ctx.esp));
    ctx.fpu_push(t65);
    // 0x0043b9e1: fstp dword ptr [esi + 0x40]
    double t66 = ctx.fpu_st(0);
    uint32_t t67 = static_cast<uint32_t>(ctx.esi + 0x00000040u);
    mem.wf32(t67, static_cast<float>(t66));
    ctx.fpu_pop();
    // 0x0043b9e4: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x0043b9e6: pop ebp
    uint32_t t68 = ctx.esp;
    uint32_t t69 = mem.r32(t68);
    uint32_t t70 = static_cast<uint32_t>(t68 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    ctx.ebp = static_cast<uint32_t>(t69);
    // 0x0043b9e7: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0043b9cc: {
    // 0x0043b9cc: fadd qword ptr [0x53d818]
    double t71 = ctx.fpu_st(0);
    double t72 = mem.rf64(0x0053d818u);
    double t73 = (t71 + t72);
    ctx.fpu_st(0) = t73;
    goto bb_0043b9d2;
}
}

// sub_0048e0a0 | subsystem=Core/Windows | canonical | 65 blocks | 253 insns
void sub_0048e0a0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0048e0a0: sub esp, 0x1c
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x0000001cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x0000001cu, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x0048e0a3: push ebx
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebx);
    // 0x0048e0a4: push ebp
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebp);
    // 0x0048e0a5: push esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.esi);
    // 0x0048e0a6: xor esi, esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    ctx.esi = static_cast<uint32_t>(t4);
    // 0x0048e0a8: xor ebx, ebx
    uint32_t t5 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    ctx.ebx = static_cast<uint32_t>(t5);
    // 0x0048e0aa: push edi
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.edi);
    // 0x0048e0ab: mov dword ptr [0x74d98c], esi
    mem.w32(0x0074d98cu, ctx.esi);
    // 0x0048e0b1: mov dword ptr [0x74d988], esi
    mem.w32(0x0074d988u, ctx.esi);
    // 0x0048e0b7: mov dword ptr [0x74d9cc], esi
    mem.w32(0x0074d9ccu, ctx.esi);
    // 0x0048e0bd: mov dword ptr [0x74d9c8], esi
    mem.w32(0x0074d9c8u, ctx.esi);
    // 0x0048e0c3: mov dword ptr [0x76e734], esi
    mem.w32(0x0076e734u, ctx.esi);
    // 0x0048e0c9: mov dword ptr [0x76e730], esi
    mem.w32(0x0076e730u, ctx.esi);
    // 0x0048e0cf: mov dword ptr [esp + 0x10], esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t7, ctx.esi);
    // 0x0048e0d3: mov dword ptr [esp + 0x18], 0x771700
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t8, 0x00771700u);
    // 0x0048e0db: mov dword ptr [esp + 0x14], 0x74e250
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t9, 0x0074e250u);
    // 0x0048e0e3: xor ebp, ebp
    uint32_t t10 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.ebp = static_cast<uint32_t>(t10);
}
bb_0048e0e5: {
    // 0x0048e0e5: mov ecx, dword ptr [0x76e6b0]
    uint32_t t11 = mem.r32(0x0076e6b0u);
    ctx.ecx = static_cast<uint32_t>(t11);
    // 0x0048e0eb: mov eax, dword ptr [ecx]
    uint32_t t12 = mem.r32(ctx.ecx);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0048e0ed: mov edx, dword ptr [eax + 0x20]
    uint32_t t13 = static_cast<uint32_t>(ctx.eax + 0x00000020u);
    uint32_t t14 = mem.r32(t13);
    ctx.edx = static_cast<uint32_t>(t14);
    // 0x0048e0f0: push ebx
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.ebx);
    // 0x0048e0f1: call edx
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x0048e0f3u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0048e0f3: test eax, eax
    uint32_t t17 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t17);
    // 0x0048e0f5: je 0x48e12d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e12d;
    goto bb_0048e0f7;
}
bb_0048e12d: {
    // 0x0048e12d: mov eax, dword ptr [ebp + 0x74d9d4]
    uint32_t t18 = static_cast<uint32_t>(ctx.ebp + 0x0074d9d4u);
    uint32_t t19 = mem.r32(t18);
    ctx.eax = static_cast<uint32_t>(t19);
    // 0x0048e133: mov ecx, dword ptr [ebp + 0x74d990]
    uint32_t t20 = static_cast<uint32_t>(ctx.ebp + 0x0074d990u);
    uint32_t t21 = mem.r32(t20);
    ctx.ecx = static_cast<uint32_t>(t21);
    // 0x0048e139: cmp eax, ecx
    uint32_t t22 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t22);
    // 0x0048e13b: lea edi, [ebp + 0x74d9d4]
    uint32_t t23 = static_cast<uint32_t>(ctx.ebp + 0x0074d9d4u);
    ctx.edi = static_cast<uint32_t>(t23);
    // 0x0048e141: lea esi, [ebp + 0x74d990]
    uint32_t t24 = static_cast<uint32_t>(ctx.ebp + 0x0074d990u);
    ctx.esi = static_cast<uint32_t>(t24);
    // 0x0048e147: jl 0x48e157
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0048e157;
    goto bb_0048e149;
}
bb_0048e0f7: {
    // 0x0048e0f7: mov eax, dword ptr [ebp + 0x74d990]
    uint32_t t25 = static_cast<uint32_t>(ctx.ebp + 0x0074d990u);
    uint32_t t26 = mem.r32(t25);
    ctx.eax = static_cast<uint32_t>(t26);
    // 0x0048e0fd: add eax, 1
    uint32_t t27 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t27);
    ctx.eax = static_cast<uint32_t>(t27);
    // 0x0048e100: cmp eax, esi
    uint32_t t28 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t28);
    // 0x0048e102: jl 0x48e110
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0048e110;
    goto bb_0048e104;
}
bb_0048e157: {
    // 0x0048e157: mov dword ptr [ebx*4 + 0x74d988], 1
    uint32_t t29 = recomp_detail::shl<uint32_t>(ctx.ebx, 0x00000002u);
    uint32_t t30 = static_cast<uint32_t>(t29 + 0x0074d988u);
    mem.w32(t30, 0x00000001u);
    goto bb_0048e162;
}
bb_0048e149: {
    // 0x0048e149: mov edx, dword ptr [ebp + 0x74d9d8]
    uint32_t t31 = static_cast<uint32_t>(ctx.ebp + 0x0074d9d8u);
    uint32_t t32 = mem.r32(t31);
    ctx.edx = static_cast<uint32_t>(t32);
    // 0x0048e14f: cmp edx, dword ptr [ebp + 0x74d994]
    uint32_t t33 = static_cast<uint32_t>(ctx.ebp + 0x0074d994u);
    uint32_t t34 = mem.r32(t33);
    uint32_t t35 = static_cast<uint32_t>(ctx.edx - t34);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, t34, t35);
    // 0x0048e155: jge 0x48e162
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0048e162;
    goto bb_0048e157;
}
bb_0048e110: {
    // 0x0048e110: xor ecx, ecx
    uint32_t t36 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t36);
    ctx.ecx = static_cast<uint32_t>(t36);
    // 0x0048e112: cmp eax, esi
    uint32_t t37 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t37);
    // 0x0048e114: setl cl
    uint8_t t38 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::L) ? 1u : 0u);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t38));
    // 0x0048e117: sub ecx, 1
    uint32_t t39 = static_cast<uint32_t>(ctx.ecx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000001u, t39);
    ctx.ecx = static_cast<uint32_t>(t39);
    // 0x0048e11a: and eax, ecx
    uint32_t t40 = static_cast<uint32_t>(ctx.eax & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t40);
    ctx.eax = static_cast<uint32_t>(t40);
    goto bb_0048e11c;
}
bb_0048e104: {
    // 0x0048e104: cmp eax, 0x63
    uint32_t t41 = static_cast<uint32_t>(ctx.eax - 0x00000063u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000063u, t41);
    // 0x0048e107: jle 0x48e110
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0048e110;
    goto bb_0048e109;
}
bb_0048e162: {
    // 0x0048e162: cmp eax, ecx
    uint32_t t42 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t42);
    // 0x0048e164: jne 0x48e174
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0048e174;
    goto bb_0048e166;
}
bb_0048e11c: {
    // 0x0048e11c: mov dword ptr [ebp + 0x74d990], eax
    uint32_t t43 = static_cast<uint32_t>(ctx.ebp + 0x0074d990u);
    mem.w32(t43, ctx.eax);
    // 0x0048e122: mov dword ptr [ebx*4 + 0x74d988], 1
    uint32_t t44 = recomp_detail::shl<uint32_t>(ctx.ebx, 0x00000002u);
    uint32_t t45 = static_cast<uint32_t>(t44 + 0x0074d988u);
    mem.w32(t45, 0x00000001u);
    goto bb_0048e12d;
}
bb_0048e109: {
    // 0x0048e109: mov eax, 0x63
    ctx.eax = static_cast<uint32_t>(0x00000063u);
    // 0x0048e10e: jmp 0x48e11c
    goto bb_0048e11c;
}
bb_0048e174: {
    // 0x0048e174: xor edx, edx
    uint32_t t46 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t46);
    ctx.edx = static_cast<uint32_t>(t46);
    // 0x0048e176: mov dword ptr [0x74d9d0], edx
    mem.w32(0x0074d9d0u, ctx.edx);
    // 0x0048e17c: jmp 0x48e180
    goto bb_0048e180;
}
bb_0048e166: {
    // 0x0048e166: mov eax, dword ptr [ebp + 0x74d9d8]
    uint32_t t47 = static_cast<uint32_t>(ctx.ebp + 0x0074d9d8u);
    uint32_t t48 = mem.r32(t47);
    ctx.eax = static_cast<uint32_t>(t48);
    // 0x0048e16c: cmp eax, dword ptr [ebp + 0x74d994]
    uint32_t t49 = static_cast<uint32_t>(ctx.ebp + 0x0074d994u);
    uint32_t t50 = mem.r32(t49);
    uint32_t t51 = static_cast<uint32_t>(ctx.eax - t50);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, t50, t51);
    // 0x0048e172: je 0x48e17e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e17e;
    goto bb_0048e174;
}
bb_0048e180: {
    // 0x0048e180: mov eax, dword ptr [0x74d99c]
    uint32_t t52 = mem.r32(0x0074d99cu);
    ctx.eax = static_cast<uint32_t>(t52);
    // 0x0048e185: sub eax, edx
    uint32_t t53 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t53);
    ctx.eax = static_cast<uint32_t>(t53);
    // 0x0048e187: mov ecx, 7
    ctx.ecx = static_cast<uint32_t>(0x00000007u);
    // 0x0048e18c: rep movsd dword ptr es:[edi], dword ptr [esi]
    recomp_detail::exec_string_op<uint32_t>(ctx, mem, 0, 1);
    // 0x0048e18e: mov dword ptr [esp + 0x20], edx
    uint32_t t54 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t54, ctx.edx);
    // 0x0048e192: mov dword ptr [esp + 0x24], edx
    uint32_t t55 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t55, ctx.edx);
    // 0x0048e196: je 0x48e1aa
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e1aa;
    goto bb_0048e198;
}
bb_0048e17e: {
    // 0x0048e17e: xor edx, edx
    uint32_t t56 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t56);
    ctx.edx = static_cast<uint32_t>(t56);
    goto bb_0048e180;
}
bb_0048e1aa: {
    // 0x0048e1aa: mov esi, dword ptr [ebp + 0x74d9a0]
    uint32_t t57 = static_cast<uint32_t>(ctx.ebp + 0x0074d9a0u);
    uint32_t t58 = mem.r32(t57);
    ctx.esi = static_cast<uint32_t>(t58);
    // 0x0048e1b0: cmp esi, edx
    uint32_t t59 = static_cast<uint32_t>(ctx.esi - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edx, t59);
    // 0x0048e1b2: je 0x48e2f5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e2f5;
    goto bb_0048e1b8;
}
bb_0048e198: {
    // 0x0048e198: sub eax, 1
    uint32_t t60 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t60);
    ctx.eax = static_cast<uint32_t>(t60);
    // 0x0048e19b: je 0x48e22a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e22a;
    goto bb_0048e1a1;
}
bb_0048e2f5: {
    // 0x0048e2f5: mov eax, dword ptr [esp + 0x14]
    uint32_t t61 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t62 = mem.r32(t61);
    ctx.eax = static_cast<uint32_t>(t62);
    // 0x0048e2f9: cmp byte ptr [eax], 0
    uint8_t t63 = mem.r8(ctx.eax);
    uint8_t t64 = static_cast<uint8_t>(static_cast<uint32_t>(t63) - static_cast<uint32_t>(uint8_t{0x00u}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, t63, uint8_t{0x00u}, t64);
    // 0x0048e2fc: je 0x48e313
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e313;
    goto bb_0048e2fe;
}
bb_0048e1b8: {
    // 0x0048e1b8: mov eax, dword ptr [ebp + 0x74d9a4]
    uint32_t t65 = static_cast<uint32_t>(ctx.ebp + 0x0074d9a4u);
    uint32_t t66 = mem.r32(t65);
    ctx.eax = static_cast<uint32_t>(t66);
    // 0x0048e1be: cmp eax, edx
    uint32_t t67 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t67);
    // 0x0048e1c0: je 0x48e2f5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e2f5;
    goto bb_0048e1c6;
}
bb_0048e22a: {
    // 0x0048e22a: cmp dword ptr [ebp + 0x74d9a0], edx
    uint32_t t68 = static_cast<uint32_t>(ctx.ebp + 0x0074d9a0u);
    uint32_t t69 = mem.r32(t68);
    uint32_t t70 = static_cast<uint32_t>(t69 - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t69, ctx.edx, t70);
    // 0x0048e230: je 0x48e313
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e313;
    goto bb_0048e236;
}
bb_0048e1a1: {
    // 0x0048e1a1: sub eax, 1
    uint32_t t71 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t71);
    ctx.eax = static_cast<uint32_t>(t71);
    // 0x0048e1a4: jne 0x48e313
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0048e313;
    goto bb_0048e1aa;
}
bb_0048e313: {
    // 0x0048e313: mov eax, dword ptr [0x76e6ac]
    uint32_t t72 = mem.r32(0x0076e6acu);
    ctx.eax = static_cast<uint32_t>(t72);
    // 0x0048e318: mov dword ptr [esp + 0x1c], edx
    uint32_t t73 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t73, ctx.edx);
    // 0x0048e31c: mov dword ptr [esp + 0x28], edx
    uint32_t t74 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t74, ctx.edx);
    // 0x0048e320: mov edx, dword ptr [esp + 0x10]
    uint32_t t75 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t76 = mem.r32(t75);
    ctx.edx = static_cast<uint32_t>(t76);
    // 0x0048e324: lea ecx, [edx + eax + 0x518]
    uint32_t t77 = static_cast<uint32_t>(ctx.edx + ctx.eax);
    uint32_t t78 = static_cast<uint32_t>(t77 + 0x00000518u);
    ctx.ecx = static_cast<uint32_t>(t78);
    // 0x0048e32b: lea edx, [esp + 0x28]
    uint32_t t79 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.edx = static_cast<uint32_t>(t79);
    // 0x0048e32f: lea esi, [esp + 0x1c]
    uint32_t t80 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.esi = static_cast<uint32_t>(t80);
    // 0x0048e333: call 0x41f5a0
    uint32_t t81 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    mem.w32(t81, 0x0048e338u);
    sub_0041f5a0(ctx, mem);
    // 0x0048e338: test byte ptr [esp + 0x1c], 4
    uint32_t t82 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint8_t t83 = mem.r8(t82);
    uint8_t t84 = static_cast<uint8_t>(static_cast<uint32_t>(t83) & static_cast<uint32_t>(uint8_t{0x04u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t84);
    // 0x0048e33d: jne 0x48e349
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0048e349;
    goto bb_0048e33f;
}
bb_0048e2fe: {
    // 0x0048e2fe: cmp dword ptr [eax + 0x30], 3
    uint32_t t85 = static_cast<uint32_t>(ctx.eax + 0x00000030u);
    uint32_t t86 = mem.r32(t85);
    uint32_t t87 = static_cast<uint32_t>(t86 - 0x00000003u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t86, 0x00000003u, t87);
    // 0x0048e302: je 0x48e313
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e313;
    goto bb_0048e304;
}
bb_0048e1c6: {
    // 0x0048e1c6: add eax, -1
    uint32_t t88 = static_cast<uint32_t>(ctx.eax + 0xffffffffu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0xffffffffu, t88);
    ctx.eax = static_cast<uint32_t>(t88);
    // 0x0048e1c9: xor ecx, ecx
    uint32_t t89 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t89);
    ctx.ecx = static_cast<uint32_t>(t89);
    // 0x0048e1cb: cmp eax, edx
    uint32_t t90 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t90);
    // 0x0048e1cd: setl cl
    uint8_t t91 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::L) ? 1u : 0u);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t91));
    // 0x0048e1d0: mov dword ptr [ebx*4 + 0x76e730], 1
    uint32_t t92 = recomp_detail::shl<uint32_t>(ctx.ebx, 0x00000002u);
    uint32_t t93 = static_cast<uint32_t>(t92 + 0x0076e730u);
    mem.w32(t93, 0x00000001u);
    // 0x0048e1db: sub ecx, 1
    uint32_t t94 = static_cast<uint32_t>(ctx.ecx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000001u, t94);
    ctx.ecx = static_cast<uint32_t>(t94);
    // 0x0048e1de: and ecx, eax
    uint32_t t95 = static_cast<uint32_t>(ctx.ecx & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t95);
    ctx.ecx = static_cast<uint32_t>(t95);
    // 0x0048e1e0: mov edi, ecx
    ctx.edi = static_cast<uint32_t>(ctx.ecx);
    // 0x0048e1e2: cmp edi, edx
    uint32_t t96 = static_cast<uint32_t>(ctx.edi - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.edx, t96);
    // 0x0048e1e4: mov dword ptr [ebp + 0x74d9a4], edi
    uint32_t t97 = static_cast<uint32_t>(ctx.ebp + 0x0074d9a4u);
    mem.w32(t97, ctx.edi);
    // 0x0048e1ea: jne 0x48e25e
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0048e25e;
    goto bb_0048e1ec;
}
bb_0048e236: {
    // 0x0048e236: cmp dword ptr [ebp + 0x74d9a4], edx
    uint32_t t98 = static_cast<uint32_t>(ctx.ebp + 0x0074d9a4u);
    uint32_t t99 = mem.r32(t98);
    uint32_t t100 = static_cast<uint32_t>(t99 - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t99, ctx.edx, t100);
    // 0x0048e23c: je 0x48e313
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e313;
    goto bb_0048e242;
}
bb_0048e349: {
    // 0x0048e349: mov dword ptr [ebx*4 + 0x74d9c8], 1
    uint32_t t101 = recomp_detail::shl<uint32_t>(ctx.ebx, 0x00000002u);
    uint32_t t102 = static_cast<uint32_t>(t101 + 0x0074d9c8u);
    mem.w32(t102, 0x00000001u);
    goto bb_0048e354;
}
bb_0048e33f: {
    // 0x0048e33f: cmp dword ptr [ebx*4 + 0x74d988], 0
    uint32_t t103 = recomp_detail::shl<uint32_t>(ctx.ebx, 0x00000002u);
    uint32_t t104 = static_cast<uint32_t>(t103 + 0x0074d988u);
    uint32_t t105 = mem.r32(t104);
    uint32_t t106 = static_cast<uint32_t>(t105 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t105, 0x00000000u, t106);
    // 0x0048e347: je 0x48e354
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e354;
    goto bb_0048e349;
}
bb_0048e304: {
    // 0x0048e304: mov dword ptr [esp + 0x20], 1
    uint32_t t107 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t107, 0x00000001u);
    // 0x0048e30c: mov dword ptr [ebx*4 + 0x76e730], edx
    uint32_t t108 = recomp_detail::shl<uint32_t>(ctx.ebx, 0x00000002u);
    uint32_t t109 = static_cast<uint32_t>(t108 + 0x0076e730u);
    mem.w32(t109, ctx.edx);
    goto bb_0048e313;
}
bb_0048e25e: {
    // 0x0048e25e: cmp dword ptr [ebx*4 + 0x74d988], edx
    uint32_t t110 = recomp_detail::shl<uint32_t>(ctx.ebx, 0x00000002u);
    uint32_t t111 = static_cast<uint32_t>(t110 + 0x0074d988u);
    uint32_t t112 = mem.r32(t111);
    uint32_t t113 = static_cast<uint32_t>(t112 - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t112, ctx.edx, t113);
    // 0x0048e265: je 0x48e271
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e271;
    goto bb_0048e267;
}
bb_0048e1ec: {
    // 0x0048e1ec: mov esi, ebx
    ctx.esi = static_cast<uint32_t>(ctx.ebx);
    // 0x0048e1ee: call 0x4a8700
    uint32_t t114 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t114);
    mem.w32(t114, 0x0048e1f3u);
    sub_004a8700(ctx, mem);
    // 0x0048e1f3: xor esi, esi
    uint32_t t115 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t115);
    ctx.esi = static_cast<uint32_t>(t115);
    // 0x0048e1f5: test eax, eax
    uint32_t t116 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t116);
    // 0x0048e1f7: jne 0x48e209
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0048e209;
    goto bb_0048e1f9;
}
bb_0048e242: {
    // 0x0048e242: cmp dword ptr [ebx*4 + 0x74d988], edx
    uint32_t t117 = recomp_detail::shl<uint32_t>(ctx.ebx, 0x00000002u);
    uint32_t t118 = static_cast<uint32_t>(t117 + 0x0074d988u);
    uint32_t t119 = mem.r32(t118);
    uint32_t t120 = static_cast<uint32_t>(t119 - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t119, ctx.edx, t120);
    // 0x0048e249: je 0x48e313
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e313;
    goto bb_0048e24f;
}
bb_0048e354: {
    // 0x0048e354: mov ecx, dword ptr [esp + 0x20]
    uint32_t t121 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t122 = mem.r32(t121);
    ctx.ecx = static_cast<uint32_t>(t122);
    // 0x0048e358: push ecx
    uint32_t t123 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t123);
    mem.w32(t123, ctx.ecx);
    // 0x0048e359: call 0x41e5d0
    uint32_t t124 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t124);
    mem.w32(t124, 0x0048e35eu);
    sub_0041e5d0(ctx, mem);
    // 0x0048e35e: add esp, 4
    uint32_t t125 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t125);
    ctx.esp = static_cast<uint32_t>(t125);
    // 0x0048e361: test eax, eax
    uint32_t t126 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t126);
    // 0x0048e363: je 0x48e36e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e36e;
    goto bb_0048e365;
}
bb_0048e271: {
    // 0x0048e271: cmp esi, 1
    uint32_t t127 = static_cast<uint32_t>(ctx.esi - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00000001u, t127);
    // 0x0048e274: jne 0x48e313
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0048e313;
    goto bb_0048e27a;
}
bb_0048e267: {
    // 0x0048e267: mov dword ptr [ebp + 0x74d9a4], 0x257
    uint32_t t128 = static_cast<uint32_t>(ctx.ebp + 0x0074d9a4u);
    mem.w32(t128, 0x00000257u);
    goto bb_0048e271;
}
bb_0048e209: {
    // 0x0048e209: mov eax, ebx
    ctx.eax = static_cast<uint32_t>(ctx.ebx);
    // 0x0048e20b: mov dword ptr [ebp + 0x74d9a0], esi
    uint32_t t129 = static_cast<uint32_t>(ctx.ebp + 0x0074d9a0u);
    mem.w32(t129, ctx.esi);
    // 0x0048e211: mov dword ptr [ebp + 0x74d9a4], esi
    uint32_t t130 = static_cast<uint32_t>(ctx.ebp + 0x0074d9a4u);
    mem.w32(t130, ctx.esi);
    // 0x0048e217: call 0x41c560
    uint32_t t131 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t131);
    mem.w32(t131, 0x0048e21cu);
    sub_0041c560(ctx, mem);
    // 0x0048e21c: mov dword ptr [ebx*4 + 0x76e730], esi
    uint32_t t132 = recomp_detail::shl<uint32_t>(ctx.ebx, 0x00000002u);
    uint32_t t133 = static_cast<uint32_t>(t132 + 0x0076e730u);
    mem.w32(t133, ctx.esi);
    // 0x0048e223: xor edx, edx
    uint32_t t134 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t134);
    ctx.edx = static_cast<uint32_t>(t134);
    // 0x0048e225: jmp 0x48e313
    goto bb_0048e313;
}
bb_0048e1f9: {
    // 0x0048e1f9: cmp dword ptr [ebp + 0x74d9a8], esi
    uint32_t t135 = static_cast<uint32_t>(ctx.ebp + 0x0074d9a8u);
    uint32_t t136 = mem.r32(t135);
    uint32_t t137 = static_cast<uint32_t>(t136 - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t136, ctx.esi, t137);
    // 0x0048e1ff: je 0x48e209
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e209;
    goto bb_0048e201;
}
bb_0048e24f: {
    // 0x0048e24f: mov dword ptr [ebp + 0x74d9a4], 0x257
    uint32_t t138 = static_cast<uint32_t>(ctx.ebp + 0x0074d9a4u);
    mem.w32(t138, 0x00000257u);
    // 0x0048e259: jmp 0x48e313
    goto bb_0048e313;
}
bb_0048e36e: {
    // 0x0048e36e: cmp dword ptr [esp + 0x24], 0
    uint32_t t139 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t140 = mem.r32(t139);
    uint32_t t141 = static_cast<uint32_t>(t140 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t140, 0x00000000u, t141);
    // 0x0048e373: je 0x48e388
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e388;
    goto bb_0048e375;
}
bb_0048e365: {
    // 0x0048e365: cmp dword ptr [ebp + 0x74d9a8], 0
    uint32_t t142 = static_cast<uint32_t>(ctx.ebp + 0x0074d9a8u);
    uint32_t t143 = mem.r32(t142);
    uint32_t t144 = static_cast<uint32_t>(t143 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t143, 0x00000000u, t144);
    // 0x0048e36c: jne 0x48e375
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0048e375;
    goto bb_0048e36e;
}
bb_0048e27a: {
    // 0x0048e27a: mov eax, dword ptr [0x76e6ac]
    uint32_t t145 = mem.r32(0x0076e6acu);
    ctx.eax = static_cast<uint32_t>(t145);
    // 0x0048e27f: mov dword ptr [esp + 0x1c], edx
    uint32_t t146 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t146, ctx.edx);
    // 0x0048e283: mov dword ptr [esp + 0x28], edx
    uint32_t t147 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t147, ctx.edx);
    // 0x0048e287: mov edx, dword ptr [esp + 0x10]
    uint32_t t148 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t149 = mem.r32(t148);
    ctx.edx = static_cast<uint32_t>(t149);
    // 0x0048e28b: lea ecx, [edx + eax + 0x518]
    uint32_t t150 = static_cast<uint32_t>(ctx.edx + ctx.eax);
    uint32_t t151 = static_cast<uint32_t>(t150 + 0x00000518u);
    ctx.ecx = static_cast<uint32_t>(t151);
    // 0x0048e292: lea edx, [esp + 0x28]
    uint32_t t152 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.edx = static_cast<uint32_t>(t152);
    // 0x0048e296: lea esi, [esp + 0x1c]
    uint32_t t153 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.esi = static_cast<uint32_t>(t153);
    // 0x0048e29a: call 0x41f5a0
    uint32_t t154 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t154);
    mem.w32(t154, 0x0048e29fu);
    sub_0041f5a0(ctx, mem);
    // 0x0048e29f: test byte ptr [esp + 0x1c], 1
    uint32_t t155 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint8_t t156 = mem.r8(t155);
    uint8_t t157 = static_cast<uint8_t>(static_cast<uint32_t>(t156) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t157);
    // 0x0048e2a4: je 0x48e2ea
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e2ea;
    goto bb_0048e2a6;
}
bb_0048e201: {
    // 0x0048e201: mov dword ptr [esp + 0x24], 1
    uint32_t t158 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t158, 0x00000001u);
    goto bb_0048e209;
}
bb_0048e388: {
    // 0x0048e388: mov eax, dword ptr [esp + 0x14]
    uint32_t t159 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t160 = mem.r32(t159);
    ctx.eax = static_cast<uint32_t>(t160);
    // 0x0048e38c: add dword ptr [esp + 0x10], 0x2c
    uint32_t t161 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t162 = mem.r32(t161);
    uint32_t t163 = static_cast<uint32_t>(t162 + 0x0000002cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, t162, 0x0000002cu, t163);
    mem.w32(t161, t163);
    // 0x0048e391: add dword ptr [esp + 0x18], 0x48
    uint32_t t164 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t165 = mem.r32(t164);
    uint32_t t166 = static_cast<uint32_t>(t165 + 0x00000048u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t165, 0x00000048u, t166);
    mem.w32(t164, t166);
    // 0x0048e396: add eax, 0x40
    uint32_t t167 = static_cast<uint32_t>(ctx.eax + 0x00000040u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000040u, t167);
    ctx.eax = static_cast<uint32_t>(t167);
    // 0x0048e399: add ebx, 1
    uint32_t t168 = static_cast<uint32_t>(ctx.ebx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebx, 0x00000001u, t168);
    ctx.ebx = static_cast<uint32_t>(t168);
    // 0x0048e39c: add ebp, 0x1c
    uint32_t t169 = static_cast<uint32_t>(ctx.ebp + 0x0000001cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebp, 0x0000001cu, t169);
    ctx.ebp = static_cast<uint32_t>(t169);
    // 0x0048e39f: xor esi, esi
    uint32_t t170 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t170);
    ctx.esi = static_cast<uint32_t>(t170);
    // 0x0048e3a1: cmp eax, 0x74e2d0
    uint32_t t171 = static_cast<uint32_t>(ctx.eax - 0x0074e2d0u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x0074e2d0u, t171);
    // 0x0048e3a6: mov dword ptr [esp + 0x14], eax
    uint32_t t172 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t172, ctx.eax);
    // 0x0048e3aa: jl 0x48e0e5
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0048e0e5;
    goto bb_0048e3b0;
}
bb_0048e375: {
    // 0x0048e375: call 0x421940
    uint32_t t173 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t173);
    mem.w32(t173, 0x0048e37au);
    sub_00421940(ctx, mem);
    // 0x0048e37a: mov esi, dword ptr [esp + 0x18]
    uint32_t t174 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t175 = mem.r32(t174);
    ctx.esi = static_cast<uint32_t>(t175);
    // 0x0048e37e: call 0x4216c0
    uint32_t t176 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t176);
    mem.w32(t176, 0x0048e383u);
    sub_004216c0(ctx, mem);
    // 0x0048e383: call 0x401110
    uint32_t t177 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t177);
    mem.w32(t177, 0x0048e388u);
    sub_00401110(ctx, mem);
    goto bb_0048e388;
}
bb_0048e2ea: {
    // 0x0048e2ea: mov eax, ebx
    ctx.eax = static_cast<uint32_t>(ctx.ebx);
    // 0x0048e2ec: call 0x419a20
    uint32_t t178 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t178);
    mem.w32(t178, 0x0048e2f1u);
    sub_00419a20(ctx, mem);
    // 0x0048e2f1: xor edx, edx
    uint32_t t179 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t179);
    ctx.edx = static_cast<uint32_t>(t179);
    // 0x0048e2f3: jmp 0x48e313
    goto bb_0048e313;
}
bb_0048e2a6: {
    // 0x0048e2a6: mov eax, 0x88888889
    ctx.eax = static_cast<uint32_t>(0x88888889u);
    // 0x0048e2ab: imul edi
    uint64_t t180 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.edi)));
    uint32_t t181 = static_cast<uint32_t>(t180);
    uint32_t t182 = static_cast<uint32_t>(t180 >> 32);
    ctx.eax = static_cast<uint32_t>(t181);
    ctx.edx = static_cast<uint32_t>(t182);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t180);
    // 0x0048e2ad: add edx, edi
    uint32_t t183 = static_cast<uint32_t>(ctx.edx + ctx.edi);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, ctx.edi, t183);
    ctx.edx = static_cast<uint32_t>(t183);
    // 0x0048e2af: sar edx, 5
    uint32_t t184 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x05u}) & 0x0000001fu);
    uint32_t t185 = recomp_detail::sar<uint32_t>(ctx.edx, t184);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t184, t185);
    ctx.edx = static_cast<uint32_t>(t185);
    // 0x0048e2b2: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x0048e2b4: shr eax, 0x1f
    uint32_t t186 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t187 = recomp_detail::shr<uint32_t>(ctx.eax, t186);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t186, t187);
    ctx.eax = static_cast<uint32_t>(t187);
    // 0x0048e2b7: add eax, edx
    uint32_t t188 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t188);
    ctx.eax = static_cast<uint32_t>(t188);
    // 0x0048e2b9: cmp eax, 6
    uint32_t t189 = static_cast<uint32_t>(ctx.eax - 0x00000006u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000006u, t189);
    // 0x0048e2bc: jg 0x48e2e0
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0048e2e0;
    goto bb_0048e2be;
}
bb_0048e3b0: {
    // 0x0048e3b0: cmp dword ptr [0x76e738], esi
    uint32_t t190 = mem.r32(0x0076e738u);
    uint32_t t191 = static_cast<uint32_t>(t190 - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t190, ctx.esi, t191);
    // 0x0048e3b6: je 0x48e3d1
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e3d1;
    goto bb_0048e3b8;
}
bb_0048e2e0: {
    // 0x0048e2e0: mov dword ptr [ebp + 0x74d9a4], edi
    uint32_t t192 = static_cast<uint32_t>(ctx.ebp + 0x0074d9a4u);
    mem.w32(t192, ctx.edi);
    // 0x0048e2e6: xor edx, edx
    uint32_t t193 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t193);
    ctx.edx = static_cast<uint32_t>(t193);
    // 0x0048e2e8: jmp 0x48e313
    goto bb_0048e313;
}
bb_0048e2be: {
    // 0x0048e2be: cmp eax, 1
    uint32_t t194 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t194);
    // 0x0048e2c1: jl 0x48e2db
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0048e2db;
    goto bb_0048e2c3;
}
bb_0048e3d1: {
    // 0x0048e3d1: cmp dword ptr [0x74d988], esi
    uint32_t t195 = mem.r32(0x0074d988u);
    uint32_t t196 = static_cast<uint32_t>(t195 - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t195, ctx.esi, t196);
    // 0x0048e3d7: jne 0x48e3e1
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0048e3e1;
    goto bb_0048e3d9;
}
bb_0048e3b8: {
    // 0x0048e3b8: mov dword ptr [0x76e738], esi
    mem.w32(0x0076e738u, ctx.esi);
    goto bb_0048e3be;
}
bb_0048e2db: {
    // 0x0048e2db: mov edi, 1
    ctx.edi = static_cast<uint32_t>(0x00000001u);
    goto bb_0048e2e0;
}
bb_0048e2c3: {
    // 0x0048e2c3: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x0048e2c5: shl ecx, 4
    uint32_t t197 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x04u}) & 0x0000001fu);
    uint32_t t198 = recomp_detail::shl<uint32_t>(ctx.ecx, t197);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.ecx, t197, t198);
    ctx.ecx = static_cast<uint32_t>(t198);
    // 0x0048e2c8: sub ecx, eax
    uint32_t t199 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t199);
    ctx.ecx = static_cast<uint32_t>(t199);
    // 0x0048e2ca: lea edi, [ecx*4 - 1]
    uint32_t t200 = recomp_detail::shl<uint32_t>(ctx.ecx, 0x00000002u);
    uint32_t t201 = static_cast<uint32_t>(t200 + 0xffffffffu);
    ctx.edi = static_cast<uint32_t>(t201);
    // 0x0048e2d1: mov dword ptr [ebp + 0x74d9a4], edi
    uint32_t t202 = static_cast<uint32_t>(ctx.ebp + 0x0074d9a4u);
    mem.w32(t202, ctx.edi);
    // 0x0048e2d7: xor edx, edx
    uint32_t t203 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t203);
    ctx.edx = static_cast<uint32_t>(t203);
    // 0x0048e2d9: jmp 0x48e313
    goto bb_0048e313;
}
bb_0048e3e1: {
    // 0x0048e3e1: mov ecx, dword ptr [0x554140]
    uint32_t t204 = mem.r32(0x00554140u);
    ctx.ecx = static_cast<uint32_t>(t204);
    // 0x0048e3e7: cmp ecx, esi
    uint32_t t205 = static_cast<uint32_t>(ctx.ecx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.esi, t205);
    // 0x0048e3e9: jne 0x48e3f2
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0048e3f2;
    goto bb_0048e3eb;
}
bb_0048e3d9: {
    // 0x0048e3d9: cmp dword ptr [0x74d98c], esi
    uint32_t t206 = mem.r32(0x0074d98cu);
    uint32_t t207 = static_cast<uint32_t>(t206 - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t206, ctx.esi, t207);
    // 0x0048e3df: je 0x48e3be
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e3be;
    goto bb_0048e3e1;
}
bb_0048e3be: {
    // 0x0048e3be: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0048e3c3: add dword ptr [0x74d9d0], eax
    uint32_t t208 = mem.r32(0x0074d9d0u);
    uint32_t t209 = static_cast<uint32_t>(t208 + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, t208, ctx.eax, t209);
    mem.w32(0x0074d9d0u, t209);
    // 0x0048e3c9: pop edi
    uint32_t t210 = ctx.esp;
    uint32_t t211 = mem.r32(t210);
    uint32_t t212 = static_cast<uint32_t>(t210 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t212);
    ctx.edi = static_cast<uint32_t>(t211);
    // 0x0048e3ca: pop esi
    uint32_t t213 = ctx.esp;
    uint32_t t214 = mem.r32(t213);
    uint32_t t215 = static_cast<uint32_t>(t213 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t215);
    ctx.esi = static_cast<uint32_t>(t214);
    // 0x0048e3cb: pop ebp
    uint32_t t216 = ctx.esp;
    uint32_t t217 = mem.r32(t216);
    uint32_t t218 = static_cast<uint32_t>(t216 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t218);
    ctx.ebp = static_cast<uint32_t>(t217);
    // 0x0048e3cc: pop ebx
    uint32_t t219 = ctx.esp;
    uint32_t t220 = mem.r32(t219);
    uint32_t t221 = static_cast<uint32_t>(t219 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t221);
    ctx.ebx = static_cast<uint32_t>(t220);
    // 0x0048e3cd: add esp, 0x1c
    uint32_t t222 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000001cu, t222);
    ctx.esp = static_cast<uint32_t>(t222);
    // 0x0048e3d0: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0048e3f2: {
    // 0x0048e3f2: mov ecx, dword ptr [ecx + 0x148]
    uint32_t t223 = static_cast<uint32_t>(ctx.ecx + 0x00000148u);
    uint32_t t224 = mem.r32(t223);
    ctx.ecx = static_cast<uint32_t>(t224);
    // 0x0048e3f8: cmp ecx, 0x15
    uint32_t t225 = static_cast<uint32_t>(ctx.ecx - 0x00000015u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000015u, t225);
    // 0x0048e3fb: mov eax, 0xffffd8f0
    ctx.eax = static_cast<uint32_t>(0xffffd8f0u);
    // 0x0048e400: mov dword ptr [esp + 0x28], ecx
    uint32_t t226 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t226, ctx.ecx);
    // 0x0048e404: jge 0x48e415
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0048e415;
    goto bb_0048e406;
}
bb_0048e3eb: {
    // 0x0048e3eb: mov ebp, 0xffffd8f0
    ctx.ebp = static_cast<uint32_t>(0xffffd8f0u);
    // 0x0048e3f0: jmp 0x48e417
    goto bb_0048e417;
}
bb_0048e415: {
    // 0x0048e415: mov ebp, eax
    ctx.ebp = static_cast<uint32_t>(ctx.eax);
    goto bb_0048e417;
}
bb_0048e406: {
    // 0x0048e406: fild dword ptr [esp + 0x28]
    uint32_t t227 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    double t228 = static_cast<double>(static_cast<int32_t>(mem.r32(t227)));
    ctx.fpu_push(t228);
    // 0x0048e40a: fmul qword ptr [0x53d938]
    double t229 = ctx.fpu_st(0);
    double t230 = mem.rf64(0x0053d938u);
    double t231 = (t229 * t230);
    ctx.fpu_st(0) = t231;
    // 0x0048e410: call 0x4f49f0
    uint32_t t232 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t232);
    mem.w32(t232, 0x0048e415u);
    hle_crt_004f49f0(ctx, mem);
    goto bb_0048e415;
}
bb_0048e417: {
    // 0x0048e417: mov eax, dword ptr [0x76c928]
    uint32_t t233 = mem.r32(0x0076c928u);
    ctx.eax = static_cast<uint32_t>(t233);
    // 0x0048e41c: cmp eax, esi
    uint32_t t234 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t234);
    // 0x0048e41e: je 0x48e44c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0048e44c;
    goto bb_0048e420;
}
bb_0048e44c: {
    // 0x0048e44c: pop edi
    uint32_t t235 = ctx.esp;
    uint32_t t236 = mem.r32(t235);
    uint32_t t237 = static_cast<uint32_t>(t235 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t237);
    ctx.edi = static_cast<uint32_t>(t236);
    // 0x0048e44d: pop esi
    uint32_t t238 = ctx.esp;
    uint32_t t239 = mem.r32(t238);
    uint32_t t240 = static_cast<uint32_t>(t238 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t240);
    ctx.esi = static_cast<uint32_t>(t239);
    // 0x0048e44e: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0048e453: add dword ptr [0x74d9d0], eax
    uint32_t t241 = mem.r32(0x0074d9d0u);
    uint32_t t242 = static_cast<uint32_t>(t241 + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, t241, ctx.eax, t242);
    mem.w32(0x0074d9d0u, t242);
    // 0x0048e459: pop ebp
    uint32_t t243 = ctx.esp;
    uint32_t t244 = mem.r32(t243);
    uint32_t t245 = static_cast<uint32_t>(t243 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t245);
    ctx.ebp = static_cast<uint32_t>(t244);
    // 0x0048e45a: mov byte ptr [0x76e094], al
    mem.w8(0x0076e094u, recomp_detail::r8l(ctx.eax));
    // 0x0048e45f: pop ebx
    uint32_t t246 = ctx.esp;
    uint32_t t247 = mem.r32(t246);
    uint32_t t248 = static_cast<uint32_t>(t246 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t248);
    ctx.ebx = static_cast<uint32_t>(t247);
    // 0x0048e460: add esp, 0x1c
    uint32_t t249 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000001cu, t249);
    ctx.esp = static_cast<uint32_t>(t249);
    // 0x0048e463: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0048e420: {
    // 0x0048e420: cmp dword ptr [eax + 0x10], esi
    uint32_t t250 = static_cast<uint32_t>(ctx.eax + 0x00000010u);
    uint32_t t251 = mem.r32(t250);
    uint32_t t252 = static_cast<uint32_t>(t251 - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t251, ctx.esi, t252);
    // 0x0048e423: lea edi, [eax + 0x10]
    uint32_t t253 = static_cast<uint32_t>(ctx.eax + 0x00000010u);
    ctx.edi = static_cast<uint32_t>(t253);
    // 0x0048e426: mov dword ptr [esp + 0x28], eax
    uint32_t t254 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t254, ctx.eax);
    // 0x0048e42a: jle 0x48e445
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0048e445;
    goto bb_0048e42c;
}
bb_0048e445: {
    // 0x0048e445: mov eax, dword ptr [esp + 0x28]
    uint32_t t255 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t256 = mem.r32(t255);
    ctx.eax = static_cast<uint32_t>(t256);
    // 0x0048e449: mov dword ptr [eax + 0x18], ebp
    uint32_t t257 = static_cast<uint32_t>(ctx.eax + 0x00000018u);
    mem.w32(t257, ctx.ebp);
    goto bb_0048e44c;
}
bb_0048e42c: {
    // 0x0048e42c: lea ebx, [eax + 4]
    uint32_t t258 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    ctx.ebx = static_cast<uint32_t>(t258);
    // 0x0048e42f: nop
}
bb_0048e430: {
    // 0x0048e430: mov edx, dword ptr [ebx]
    uint32_t t259 = mem.r32(ctx.ebx);
    ctx.edx = static_cast<uint32_t>(t259);
    // 0x0048e432: mov eax, dword ptr [edx + esi*4]
    uint32_t t260 = recomp_detail::shl<uint32_t>(ctx.esi, 0x00000002u);
    uint32_t t261 = static_cast<uint32_t>(ctx.edx + t260);
    uint32_t t262 = mem.r32(t261);
    ctx.eax = static_cast<uint32_t>(t262);
    // 0x0048e435: mov ecx, dword ptr [eax]
    uint32_t t263 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t263);
    // 0x0048e437: mov edx, dword ptr [ecx + 0x3c]
    uint32_t t264 = static_cast<uint32_t>(ctx.ecx + 0x0000003cu);
    uint32_t t265 = mem.r32(t264);
    ctx.edx = static_cast<uint32_t>(t265);
    // 0x0048e43a: push ebp
    uint32_t t266 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t266);
    mem.w32(t266, ctx.ebp);
    // 0x0048e43b: push eax
    uint32_t t267 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t267);
    mem.w32(t267, ctx.eax);
    // 0x0048e43c: call edx
    uint32_t t268 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t268);
    mem.w32(t268, 0x0048e43eu);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0048e43e: add esi, 1
    uint32_t t269 = static_cast<uint32_t>(ctx.esi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000001u, t269);
    ctx.esi = static_cast<uint32_t>(t269);
    // 0x0048e441: cmp esi, dword ptr [edi]
    uint32_t t270 = mem.r32(ctx.edi);
    uint32_t t271 = static_cast<uint32_t>(ctx.esi - t270);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, t270, t271);
    // 0x0048e443: jl 0x48e430
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0048e430;
    goto bb_0048e445;
}
}

// sub_004a0720 | subsystem=Core/Windows | canonical | 12 blocks | 110 insns
void sub_004a0720(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a0720: sub esp, 0x228
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000228u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000228u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x004a0726: mov eax, dword ptr [0x54b458]
    uint32_t t1 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x004a072b: xor eax, esp
    uint32_t t2 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x004a072d: mov dword ptr [esp + 0x224], eax
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x00000224u);
    mem.w32(t3, ctx.eax);
    // 0x004a0734: test esi, esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    // 0x004a0736: jne 0x4a074f
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a074f;
    goto bb_004a0738;
}
bb_004a074f: {
    // 0x004a074f: push ebx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ebx);
    // 0x004a0750: push ebp
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebp);
    // 0x004a0751: push edi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.edi);
    // 0x004a0752: lea eax, [esp + 0x130]
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000130u);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x004a0759: push 0x53a5dc
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x0053a5dcu);
    // 0x004a075e: push eax
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.eax);
    // 0x004a075f: call 0x4e068b
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0x004a0764u);
    hle_crt_004e068b(ctx, mem);
    // 0x004a0764: lea ecx, [esp + 0x38]
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    ctx.ecx = static_cast<uint32_t>(t12);
    // 0x004a0768: push 0x53a5e8
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x0053a5e8u);
    // 0x004a076d: push ecx
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, ctx.ecx);
    // 0x004a076e: call 0x4e068b
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x004a0773u);
    hle_crt_004e068b(ctx, mem);
    // 0x004a0773: mov edx, dword ptr [0x76e768]
    uint32_t t16 = mem.r32(0x0076e768u);
    ctx.edx = static_cast<uint32_t>(t16);
    // 0x004a0779: add esp, 0x10
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t17);
    ctx.esp = static_cast<uint32_t>(t17);
    // 0x004a077c: push edx
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, ctx.edx);
    // 0x004a077d: lea ebx, [esp + 0x34]
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    ctx.ebx = static_cast<uint32_t>(t19);
    // 0x004a0781: lea edi, [esp + 0x134]
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x00000134u);
    ctx.edi = static_cast<uint32_t>(t20);
    // 0x004a0788: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a078a: call 0x40c8c0
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x004a078fu);
    sub_0040c8c0(ctx, mem);
    // 0x004a078f: xor ebp, ebp
    uint32_t t22 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t22);
    ctx.ebp = static_cast<uint32_t>(t22);
    // 0x004a0791: mov dword ptr [esp + 0xc], 0x74db1c
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t23, 0x0074db1cu);
    // 0x004a0799: lea esp, [esp]
    ctx.esp = static_cast<uint32_t>(ctx.esp);
    goto bb_004a07a0;
}
bb_004a0738: {
    // 0x004a0738: xor eax, eax
    uint32_t t24 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t24);
    ctx.eax = static_cast<uint32_t>(t24);
    // 0x004a073a: mov ecx, dword ptr [esp + 0x224]
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000224u);
    uint32_t t26 = mem.r32(t25);
    ctx.ecx = static_cast<uint32_t>(t26);
    // 0x004a0741: xor ecx, esp
    uint32_t t27 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t27);
    ctx.ecx = static_cast<uint32_t>(t27);
    // 0x004a0743: call 0x4e02f8
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x004a0748u);
    hle_crt_004e02f8(ctx, mem);
    // 0x004a0748: add esp, 0x228
    uint32_t t29 = static_cast<uint32_t>(ctx.esp + 0x00000228u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000228u, t29);
    ctx.esp = static_cast<uint32_t>(t29);
    // 0x004a074e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a07a0: {
    // 0x004a07a0: push ebp
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, ctx.ebp);
    // 0x004a07a1: lea eax, [esp + 0x34]
    uint32_t t31 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    ctx.eax = static_cast<uint32_t>(t31);
    // 0x004a07a5: push 0x53a5f4
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x0053a5f4u);
    // 0x004a07aa: push eax
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, ctx.eax);
    // 0x004a07ab: call 0x4e068b
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x004a07b0u);
    hle_crt_004e068b(ctx, mem);
    // 0x004a07b0: mov ecx, dword ptr [esp + 0x18]
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t36 = mem.r32(t35);
    ctx.ecx = static_cast<uint32_t>(t36);
    // 0x004a07b4: mov edx, dword ptr [ecx - 0x104]
    uint32_t t37 = static_cast<uint32_t>(ctx.ecx + 0xfffffefcu);
    uint32_t t38 = mem.r32(t37);
    ctx.edx = static_cast<uint32_t>(t38);
    // 0x004a07ba: add esp, 0xc
    uint32_t t39 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t39);
    ctx.esp = static_cast<uint32_t>(t39);
    // 0x004a07bd: push edx
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, ctx.edx);
    // 0x004a07be: lea ebx, [esp + 0x34]
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    ctx.ebx = static_cast<uint32_t>(t41);
    // 0x004a07c2: lea edi, [esp + 0x134]
    uint32_t t42 = static_cast<uint32_t>(ctx.esp + 0x00000134u);
    ctx.edi = static_cast<uint32_t>(t42);
    // 0x004a07c9: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a07cb: call 0x40c8c0
    uint32_t t43 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    mem.w32(t43, 0x004a07d0u);
    sub_0040c8c0(ctx, mem);
    // 0x004a07d0: push ebp
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, ctx.ebp);
    // 0x004a07d1: mov eax, ebx
    ctx.eax = static_cast<uint32_t>(ctx.ebx);
    // 0x004a07d3: push 0x53a600
    uint32_t t45 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    mem.w32(t45, 0x0053a600u);
    // 0x004a07d8: push eax
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, ctx.eax);
    // 0x004a07d9: call 0x4e068b
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, 0x004a07deu);
    hle_crt_004e068b(ctx, mem);
    // 0x004a07de: add esp, 0xc
    uint32_t t48 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t48);
    ctx.esp = static_cast<uint32_t>(t48);
    // 0x004a07e1: cmp dword ptr [esi], 1
    uint32_t t49 = mem.r32(ctx.esi);
    uint32_t t50 = static_cast<uint32_t>(t49 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t49, 0x00000001u, t50);
    // 0x004a07e4: jne 0x4a0801
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a0801;
    goto bb_004a07e6;
}
bb_004a0801: {
    // 0x004a0801: mov ebx, dword ptr [esp + 0xc]
    uint32_t t51 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t52 = mem.r32(t51);
    ctx.ebx = static_cast<uint32_t>(t52);
    // 0x004a0805: xor edi, edi
    uint32_t t53 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t53);
    ctx.edi = static_cast<uint32_t>(t53);
    goto bb_004a0807;
}
bb_004a07e6: {
    // 0x004a07e6: mov edx, dword ptr [esp + 0xc]
    uint32_t t54 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t55 = mem.r32(t54);
    ctx.edx = static_cast<uint32_t>(t55);
    // 0x004a07ea: lea ecx, [esi + 0xc]
    uint32_t t56 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    ctx.ecx = static_cast<uint32_t>(t56);
    // 0x004a07ed: push ecx
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, ctx.ecx);
    // 0x004a07ee: add edx, 0xffffff00
    uint32_t t58 = static_cast<uint32_t>(ctx.edx + 0xffffff00u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0xffffff00u, t58);
    ctx.edx = static_cast<uint32_t>(t58);
    // 0x004a07f4: push edx
    uint32_t t59 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    mem.w32(t59, ctx.edx);
    // 0x004a07f5: mov eax, ebx
    ctx.eax = static_cast<uint32_t>(ctx.ebx);
    // 0x004a07f7: push eax
    uint32_t t60 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t60);
    mem.w32(t60, ctx.eax);
    // 0x004a07f8: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004a07fa: push ecx
    uint32_t t61 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    mem.w32(t61, ctx.ecx);
    // 0x004a07fb: call dword ptr [0x51b02c]
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, 0x004a0801u);
    hle_iat_call(ctx, mem, 0x0051b02cu);
    goto bb_004a0801;
}
bb_004a0807: {
    // 0x004a0807: push edi
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, ctx.edi);
    // 0x004a0808: push ebp
    uint32_t t64 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    mem.w32(t64, ctx.ebp);
    // 0x004a0809: lea edx, [esp + 0x38]
    uint32_t t65 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    ctx.edx = static_cast<uint32_t>(t65);
    // 0x004a080d: push 0x53a60c
    uint32_t t66 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    mem.w32(t66, 0x0053a60cu);
    // 0x004a0812: push edx
    uint32_t t67 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t67);
    mem.w32(t67, ctx.edx);
    // 0x004a0813: call 0x4e068b
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, 0x004a0818u);
    hle_crt_004e068b(ctx, mem);
    // 0x004a0818: add esp, 0x10
    uint32_t t69 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t69);
    ctx.esp = static_cast<uint32_t>(t69);
    // 0x004a081b: cmp dword ptr [esi], 1
    uint32_t t70 = mem.r32(ctx.esi);
    uint32_t t71 = static_cast<uint32_t>(t70 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t70, 0x00000001u, t71);
    // 0x004a081e: jne 0x4a0856
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a0856;
    goto bb_004a0820;
}
bb_004a0856: {
    // 0x004a0856: add edi, 1
    uint32_t t72 = static_cast<uint32_t>(ctx.edi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000001u, t72);
    ctx.edi = static_cast<uint32_t>(t72);
    // 0x004a0859: add ebx, 4
    uint32_t t73 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebx, 0x00000004u, t73);
    ctx.ebx = static_cast<uint32_t>(t73);
    // 0x004a085c: cmp edi, 0x18
    uint32_t t74 = static_cast<uint32_t>(ctx.edi - 0x00000018u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, 0x00000018u, t74);
    // 0x004a085f: jl 0x4a0807
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004a0807;
    goto bb_004a0861;
}
bb_004a0820: {
    // 0x004a0820: mov eax, dword ptr [ebx]
    uint32_t t75 = mem.r32(ctx.ebx);
    ctx.eax = static_cast<uint32_t>(t75);
    // 0x004a0822: push eax
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    mem.w32(t76, ctx.eax);
    // 0x004a0823: lea ecx, [esp + 0x14]
    uint32_t t77 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.ecx = static_cast<uint32_t>(t77);
    // 0x004a0827: push 0x5351b0
    uint32_t t78 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    mem.w32(t78, 0x005351b0u);
    // 0x004a082c: push ecx
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, ctx.ecx);
    // 0x004a082d: call 0x4e068b
    uint32_t t80 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    mem.w32(t80, 0x004a0832u);
    hle_crt_004e068b(ctx, mem);
    // 0x004a0832: add esp, 0xc
    uint32_t t81 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t81);
    ctx.esp = static_cast<uint32_t>(t81);
    // 0x004a0835: cmp dword ptr [esi], 1
    uint32_t t82 = mem.r32(ctx.esi);
    uint32_t t83 = static_cast<uint32_t>(t82 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t82, 0x00000001u, t83);
    // 0x004a0838: jne 0x4a0856
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a0856;
    goto bb_004a083a;
}
bb_004a0861: {
    // 0x004a0861: add dword ptr [esp + 0xc], 0x164
    uint32_t t84 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t85 = mem.r32(t84);
    uint32_t t86 = static_cast<uint32_t>(t85 + 0x00000164u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t85, 0x00000164u, t86);
    mem.w32(t84, t86);
    // 0x004a0869: add ebp, 1
    uint32_t t87 = static_cast<uint32_t>(ctx.ebp + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebp, 0x00000001u, t87);
    ctx.ebp = static_cast<uint32_t>(t87);
    // 0x004a086c: cmp ebp, 4
    uint32_t t88 = static_cast<uint32_t>(ctx.ebp - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebp, 0x00000004u, t88);
    // 0x004a086f: jl 0x4a07a0
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004a07a0;
    goto bb_004a0875;
}
bb_004a083a: {
    // 0x004a083a: lea edx, [esi + 0xc]
    uint32_t t89 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    ctx.edx = static_cast<uint32_t>(t89);
    // 0x004a083d: push edx
    uint32_t t90 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    mem.w32(t90, ctx.edx);
    // 0x004a083e: lea eax, [esp + 0x14]
    uint32_t t91 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.eax = static_cast<uint32_t>(t91);
    // 0x004a0842: push eax
    uint32_t t92 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    mem.w32(t92, ctx.eax);
    // 0x004a0843: lea ecx, [esp + 0x38]
    uint32_t t93 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    ctx.ecx = static_cast<uint32_t>(t93);
    // 0x004a0847: push ecx
    uint32_t t94 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t94);
    mem.w32(t94, ctx.ecx);
    // 0x004a0848: lea edx, [esp + 0x13c]
    uint32_t t95 = static_cast<uint32_t>(ctx.esp + 0x0000013cu);
    ctx.edx = static_cast<uint32_t>(t95);
    // 0x004a084f: push edx
    uint32_t t96 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    mem.w32(t96, ctx.edx);
    // 0x004a0850: call dword ptr [0x51b02c]
    uint32_t t97 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t97);
    mem.w32(t97, 0x004a0856u);
    hle_iat_call(ctx, mem, 0x0051b02cu);
    goto bb_004a0856;
}
bb_004a0875: {
    // 0x004a0875: mov ecx, dword ptr [esp + 0x230]
    uint32_t t98 = static_cast<uint32_t>(ctx.esp + 0x00000230u);
    uint32_t t99 = mem.r32(t98);
    ctx.ecx = static_cast<uint32_t>(t99);
    // 0x004a087c: pop edi
    uint32_t t100 = ctx.esp;
    uint32_t t101 = mem.r32(t100);
    uint32_t t102 = static_cast<uint32_t>(t100 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    ctx.edi = static_cast<uint32_t>(t101);
    // 0x004a087d: pop ebp
    uint32_t t103 = ctx.esp;
    uint32_t t104 = mem.r32(t103);
    uint32_t t105 = static_cast<uint32_t>(t103 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t105);
    ctx.ebp = static_cast<uint32_t>(t104);
    // 0x004a087e: pop ebx
    uint32_t t106 = ctx.esp;
    uint32_t t107 = mem.r32(t106);
    uint32_t t108 = static_cast<uint32_t>(t106 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t108);
    ctx.ebx = static_cast<uint32_t>(t107);
    // 0x004a087f: xor ecx, esp
    uint32_t t109 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t109);
    ctx.ecx = static_cast<uint32_t>(t109);
    // 0x004a0881: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x004a0886: call 0x4e02f8
    uint32_t t110 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t110);
    mem.w32(t110, 0x004a088bu);
    hle_crt_004e02f8(ctx, mem);
    // 0x004a088b: add esp, 0x228
    uint32_t t111 = static_cast<uint32_t>(ctx.esp + 0x00000228u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000228u, t111);
    ctx.esp = static_cast<uint32_t>(t111);
    // 0x004a0891: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004a1c00 | subsystem=Core/Windows | canonical | 22 blocks | 120 insns
void sub_004a1c00(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a1c00: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x004a1c01: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x004a1c03: and esp, 0xfffffff8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xfffffff8u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x004a1c06: push -1
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0xffffffffu);
    // 0x004a1c08: push 0x514ca8
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x00514ca8u);
    // 0x004a1c0d: mov eax, dword ptr fs:[0]
    uint32_t t4 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t5 = mem.r32(t4);
    ctx.eax = static_cast<uint32_t>(t5);
    // 0x004a1c13: push eax
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.eax);
    // 0x004a1c14: sub esp, 0x68
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000068u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000068u, t7);
    ctx.esp = static_cast<uint32_t>(t7);
    // 0x004a1c17: mov eax, dword ptr [0x54b458]
    uint32_t t8 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x004a1c1c: xor eax, esp
    uint32_t t9 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x004a1c1e: mov dword ptr [esp + 0x60], eax
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    mem.w32(t10, ctx.eax);
    // 0x004a1c22: push ebx
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.ebx);
    // 0x004a1c23: push esi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.esi);
    // 0x004a1c24: push edi
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, ctx.edi);
    // 0x004a1c25: mov eax, dword ptr [0x54b458]
    uint32_t t14 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x004a1c2a: xor eax, esp
    uint32_t t15 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t15);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x004a1c2c: push eax
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, ctx.eax);
    // 0x004a1c2d: lea eax, [esp + 0x78]
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    ctx.eax = static_cast<uint32_t>(t17);
    // 0x004a1c31: mov dword ptr fs:[0], eax
    uint32_t t18 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t18, ctx.eax);
    // 0x004a1c37: mov eax, dword ptr [ebp + 0xc]
    uint32_t t19 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t20 = mem.r32(t19);
    ctx.eax = static_cast<uint32_t>(t20);
    // 0x004a1c3a: cmp eax, 0x110
    uint32_t t21 = static_cast<uint32_t>(ctx.eax - 0x00000110u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000110u, t21);
    // 0x004a1c3f: mov esi, dword ptr [ebp + 8]
    uint32_t t22 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t23 = mem.r32(t22);
    ctx.esi = static_cast<uint32_t>(t23);
    // 0x004a1c42: ja 0x4a1d3d
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_004a1d3d;
    goto bb_004a1c48;
}
bb_004a1d3d: {
    // 0x004a1d3d: cmp eax, 0x111
    uint32_t t24 = static_cast<uint32_t>(ctx.eax - 0x00000111u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000111u, t24);
    // 0x004a1d42: jne 0x4a1d5a
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a1d5a;
    goto bb_004a1d44;
}
bb_004a1c48: {
    // 0x004a1c48: je 0x4a1cac
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1cac;
    goto bb_004a1c4a;
}
bb_004a1d5a: {
    // 0x004a1d5a: xor eax, eax
    uint32_t t25 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t25);
    ctx.eax = static_cast<uint32_t>(t25);
    // 0x004a1d5c: jmp 0x4a1d6c
    goto bb_004a1d6c;
}
bb_004a1d44: {
    // 0x004a1d44: movzx eax, word ptr [ebp + 0x10]
    uint32_t t26 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    uint16_t t27 = mem.r16(t26);
    uint32_t t28 = static_cast<uint32_t>(static_cast<uint16_t>(t27));
    ctx.eax = static_cast<uint32_t>(t28);
    // 0x004a1d48: sub eax, 1
    uint32_t t29 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t29);
    ctx.eax = static_cast<uint32_t>(t29);
    // 0x004a1d4b: je 0x4a1d5e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1d5e;
    goto bb_004a1d4d;
}
bb_004a1cac: {
    // 0x004a1cac: xor ebx, ebx
    uint32_t t30 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t30);
    ctx.ebx = static_cast<uint32_t>(t30);
    // 0x004a1cae: mov dword ptr [esp + 0x28], 0xf
    uint32_t t31 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t31, 0x0000000fu);
    // 0x004a1cb6: mov dword ptr [esp + 0x24], ebx
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t32, ctx.ebx);
    // 0x004a1cba: mov byte ptr [esp + 0x14], bl
    uint32_t t33 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w8(t33, recomp_detail::r8l(ctx.ebx));
    // 0x004a1cbe: push 0x39
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x00000039u);
    // 0x004a1cc0: push 0x5351f4
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, 0x005351f4u);
    // 0x004a1cc5: lea ecx, [esp + 0x18]
    uint32_t t36 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.ecx = static_cast<uint32_t>(t36);
    // 0x004a1cc9: mov dword ptr [esp + 0x88], ebx
    uint32_t t37 = static_cast<uint32_t>(ctx.esp + 0x00000088u);
    mem.w32(t37, ctx.ebx);
    // 0x004a1cd0: call 0x407c10
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, 0x004a1cd5u);
    sub_00407c10(ctx, mem);
    // 0x004a1cd5: push 0xd
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, 0x0000000du);
    // 0x004a1cd7: push 0x7b4b6b
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, 0x007b4b6bu);
    // 0x004a1cdc: lea eax, [esp + 0x18]
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.eax = static_cast<uint32_t>(t41);
    // 0x004a1ce0: call 0x414660
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, 0x004a1ce5u);
    sub_00414660(ctx, mem);
    // 0x004a1ce5: cmp dword ptr [esp + 0x28], 0x10
    uint32_t t43 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t44 = mem.r32(t43);
    uint32_t t45 = static_cast<uint32_t>(t44 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t44, 0x00000010u, t45);
    // 0x004a1cea: mov eax, dword ptr [esp + 0x14]
    uint32_t t46 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t47 = mem.r32(t46);
    ctx.eax = static_cast<uint32_t>(t47);
    // 0x004a1cee: jae 0x4a1cf4
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004a1cf4;
    goto bb_004a1cf0;
}
bb_004a1c4a: {
    // 0x004a1c4a: cmp eax, 0xf
    uint32_t t48 = static_cast<uint32_t>(ctx.eax - 0x0000000fu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x0000000fu, t48);
    // 0x004a1c4d: je 0x4a1c8d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1c8d;
    goto bb_004a1c4f;
}
bb_004a1d6c: {
    // 0x004a1d6c: mov ecx, dword ptr [esp + 0x78]
    uint32_t t49 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    uint32_t t50 = mem.r32(t49);
    ctx.ecx = static_cast<uint32_t>(t50);
    // 0x004a1d70: mov dword ptr fs:[0], ecx
    uint32_t t51 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t51, ctx.ecx);
    // 0x004a1d77: pop ecx
    uint32_t t52 = ctx.esp;
    uint32_t t53 = mem.r32(t52);
    uint32_t t54 = static_cast<uint32_t>(t52 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    ctx.ecx = static_cast<uint32_t>(t53);
    // 0x004a1d78: pop edi
    uint32_t t55 = ctx.esp;
    uint32_t t56 = mem.r32(t55);
    uint32_t t57 = static_cast<uint32_t>(t55 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    ctx.edi = static_cast<uint32_t>(t56);
    // 0x004a1d79: pop esi
    uint32_t t58 = ctx.esp;
    uint32_t t59 = mem.r32(t58);
    uint32_t t60 = static_cast<uint32_t>(t58 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t60);
    ctx.esi = static_cast<uint32_t>(t59);
    // 0x004a1d7a: pop ebx
    uint32_t t61 = ctx.esp;
    uint32_t t62 = mem.r32(t61);
    uint32_t t63 = static_cast<uint32_t>(t61 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    ctx.ebx = static_cast<uint32_t>(t62);
    // 0x004a1d7b: mov ecx, dword ptr [esp + 0x60]
    uint32_t t64 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    uint32_t t65 = mem.r32(t64);
    ctx.ecx = static_cast<uint32_t>(t65);
    // 0x004a1d7f: xor ecx, esp
    uint32_t t66 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t66);
    ctx.ecx = static_cast<uint32_t>(t66);
    // 0x004a1d81: call 0x4e02f8
    uint32_t t67 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t67);
    mem.w32(t67, 0x004a1d86u);
    hle_crt_004e02f8(ctx, mem);
    // 0x004a1d86: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x004a1d88: pop ebp
    uint32_t t68 = ctx.esp;
    uint32_t t69 = mem.r32(t68);
    uint32_t t70 = static_cast<uint32_t>(t68 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    ctx.ebp = static_cast<uint32_t>(t69);
    // 0x004a1d89: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a1d5e: {
    // 0x004a1d5e: push 1
    uint32_t t71 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t71);
    mem.w32(t71, 0x00000001u);
    // 0x004a1d60: push esi
    uint32_t t72 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    mem.w32(t72, ctx.esi);
    // 0x004a1d61: call dword ptr [0x51b31c]
    uint32_t t73 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    mem.w32(t73, 0x004a1d67u);
    hle_iat_call(ctx, mem, 0x0051b31cu);
    goto bb_004a1d67;
}
bb_004a1d4d: {
    // 0x004a1d4d: sub eax, 1
    uint32_t t74 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t74);
    ctx.eax = static_cast<uint32_t>(t74);
    // 0x004a1d50: jne 0x4a1d5a
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a1d5a;
    goto bb_004a1d52;
}
bb_004a1cf4: {
    // 0x004a1cf4: push eax
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, ctx.eax);
    // 0x004a1cf5: push esi
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    mem.w32(t76, ctx.esi);
    // 0x004a1cf6: call dword ptr [0x51b294]
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, 0x004a1cfcu);
    hle_iat_call(ctx, mem, 0x0051b294u);
    // 0x004a1cfc: mov edi, dword ptr [0x51b2f4]
    uint32_t t78 = mem.r32(0x0051b2f4u);
    ctx.edi = static_cast<uint32_t>(t78);
    // 0x004a1d02: push 1
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, 0x00000001u);
    // 0x004a1d04: push esi
    uint32_t t80 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    mem.w32(t80, ctx.esi);
    // 0x004a1d05: call edi
    uint32_t t81 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    mem.w32(t81, 0x004a1d07u);
    call_indirect(ctx, mem, ctx.edi);
    // 0x004a1d07: push eax
    uint32_t t82 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t82);
    mem.w32(t82, ctx.eax);
    // 0x004a1d08: call dword ptr [0x51b2f8]
    uint32_t t83 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t83);
    mem.w32(t83, 0x004a1d0eu);
    hle_iat_call(ctx, mem, 0x0051b2f8u);
    // 0x004a1d0e: push 0x3eb
    uint32_t t84 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    mem.w32(t84, 0x000003ebu);
    // 0x004a1d13: push esi
    uint32_t t85 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t85);
    mem.w32(t85, ctx.esi);
    // 0x004a1d14: call edi
    uint32_t t86 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t86);
    mem.w32(t86, 0x004a1d16u);
    call_indirect(ctx, mem, ctx.edi);
    // 0x004a1d16: cmp eax, ebx
    uint32_t t87 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t87);
    // 0x004a1d18: je 0x4a1d25
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1d25;
    goto bb_004a1d1a;
}
bb_004a1cf0: {
    // 0x004a1cf0: lea eax, [esp + 0x14]
    uint32_t t88 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.eax = static_cast<uint32_t>(t88);
    goto bb_004a1cf4;
}
bb_004a1c8d: {
    // 0x004a1c8d: lea ecx, [esp + 0x2c]
    uint32_t t89 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    ctx.ecx = static_cast<uint32_t>(t89);
    // 0x004a1c91: push ecx
    uint32_t t90 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    mem.w32(t90, ctx.ecx);
    // 0x004a1c92: push esi
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, ctx.esi);
    // 0x004a1c93: call dword ptr [0x51b2ec]
    uint32_t t92 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    mem.w32(t92, 0x004a1c99u);
    hle_iat_call(ctx, mem, 0x0051b2ecu);
    // 0x004a1c99: lea edx, [esp + 0x2c]
    uint32_t t93 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    ctx.edx = static_cast<uint32_t>(t93);
    // 0x004a1c9d: push edx
    uint32_t t94 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t94);
    mem.w32(t94, ctx.edx);
    // 0x004a1c9e: push esi
    uint32_t t95 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t95);
    mem.w32(t95, ctx.esi);
    // 0x004a1c9f: call dword ptr [0x51b308]
    uint32_t t96 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    mem.w32(t96, 0x004a1ca5u);
    hle_iat_call(ctx, mem, 0x0051b308u);
    // 0x004a1ca5: xor eax, eax
    uint32_t t97 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t97);
    ctx.eax = static_cast<uint32_t>(t97);
    // 0x004a1ca7: jmp 0x4a1d6c
    goto bb_004a1d6c;
}
bb_004a1c4f: {
    // 0x004a1c4f: cmp eax, 0x4e
    uint32_t t98 = static_cast<uint32_t>(ctx.eax - 0x0000004eu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x0000004eu, t98);
    // 0x004a1c52: jne 0x4a1d5a
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a1d5a;
    goto bb_004a1c58;
}
bb_004a1d67: {
    // 0x004a1d67: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    goto bb_004a1d6c;
}
bb_004a1d52: {
    // 0x004a1d52: push eax
    uint32_t t99 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t99);
    mem.w32(t99, ctx.eax);
    // 0x004a1d53: push esi
    uint32_t t100 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t100);
    mem.w32(t100, ctx.esi);
    // 0x004a1d54: call dword ptr [0x51b31c]
    uint32_t t101 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t101);
    mem.w32(t101, 0x004a1d5au);
    hle_iat_call(ctx, mem, 0x0051b31cu);
    goto bb_004a1d5a;
}
bb_004a1d25: {
    // 0x004a1d25: cmp dword ptr [esp + 0x28], 0x10
    uint32_t t102 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t103 = mem.r32(t102);
    uint32_t t104 = static_cast<uint32_t>(t103 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t103, 0x00000010u, t104);
    // 0x004a1d2a: jb 0x4a1d5a
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a1d5a;
    goto bb_004a1d2c;
}
bb_004a1d1a: {
    // 0x004a1d1a: push esi
    uint32_t t105 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t105);
    mem.w32(t105, ctx.esi);
    // 0x004a1d1b: mov ebx, eax
    ctx.ebx = static_cast<uint32_t>(ctx.eax);
    // 0x004a1d1d: call 0x4a1d90
    uint32_t t106 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t106);
    mem.w32(t106, 0x004a1d22u);
    sub_004a1d90(ctx, mem);
    // 0x004a1d22: add esp, 4
    uint32_t t107 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t107);
    ctx.esp = static_cast<uint32_t>(t107);
    goto bb_004a1d25;
}
bb_004a1c58: {
    // 0x004a1c58: cmp dword ptr [ebp + 0x10], 0x3eb
    uint32_t t108 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    uint32_t t109 = mem.r32(t108);
    uint32_t t110 = static_cast<uint32_t>(t109 - 0x000003ebu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t109, 0x000003ebu, t110);
    // 0x004a1c5f: jne 0x4a1d67
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a1d67;
    goto bb_004a1c65;
}
bb_004a1d2c: {
    // 0x004a1d2c: mov eax, dword ptr [esp + 0x14]
    uint32_t t111 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t112 = mem.r32(t111);
    ctx.eax = static_cast<uint32_t>(t112);
    // 0x004a1d30: push eax
    uint32_t t113 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t113);
    mem.w32(t113, ctx.eax);
    // 0x004a1d31: call 0x4e02f3
    uint32_t t114 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t114);
    mem.w32(t114, 0x004a1d36u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a1d36: add esp, 4
    uint32_t t115 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t115);
    ctx.esp = static_cast<uint32_t>(t115);
    // 0x004a1d39: xor eax, eax
    uint32_t t116 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t116);
    ctx.eax = static_cast<uint32_t>(t116);
    // 0x004a1d3b: jmp 0x4a1d6c
    goto bb_004a1d6c;
}
bb_004a1c65: {
    // 0x004a1c65: push 0x3eb
    uint32_t t117 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t117);
    mem.w32(t117, 0x000003ebu);
    // 0x004a1c6a: push esi
    uint32_t t118 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    mem.w32(t118, ctx.esi);
    // 0x004a1c6b: call dword ptr [0x51b2f4]
    uint32_t t119 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t119);
    mem.w32(t119, 0x004a1c71u);
    hle_iat_call(ctx, mem, 0x0051b2f4u);
    // 0x004a1c71: mov eax, dword ptr [ebp + 0x14]
    uint32_t t120 = static_cast<uint32_t>(ctx.ebp + 0x00000014u);
    uint32_t t121 = mem.r32(t120);
    ctx.eax = static_cast<uint32_t>(t121);
    // 0x004a1c74: cmp dword ptr [eax + 8], 0xfffffdd9
    uint32_t t122 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    uint32_t t123 = mem.r32(t122);
    uint32_t t124 = static_cast<uint32_t>(t123 - 0xfffffdd9u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t123, 0xfffffdd9u, t124);
    // 0x004a1c7b: jne 0x4a1d67
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a1d67;
}
{
    // 0x004a1c81: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004a1c83: call 0x4a1ed0
    uint32_t t125 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t125);
    mem.w32(t125, 0x004a1c88u);
    sub_004a1ed0(ctx, mem);
    // 0x004a1c88: jmp 0x4a1d67
    goto bb_004a1d67;
}
}

// sub_004a1d90 | subsystem=Core/Windows | canonical | 8 blocks | 100 insns
void sub_004a1d90(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a1d90: sub esp, 0x34
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000034u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000034u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x004a1d93: mov eax, dword ptr [esp + 0x38]
    uint32_t t1 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    uint32_t t2 = mem.r32(t1);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x004a1d97: push ebp
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.ebp);
    // 0x004a1d98: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x004a1d99: push edi
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.edi);
    // 0x004a1d9a: push -6
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0xfffffffau);
    // 0x004a1d9c: push eax
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.eax);
    // 0x004a1d9d: mov dword ptr [esp + 0x14], 0
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t8, 0x00000000u);
    // 0x004a1da5: call dword ptr [0x51b2dc]
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x004a1dabu);
    hle_iat_call(ctx, mem, 0x0051b2dcu);
    // 0x004a1dab: cmp dword ptr [0x54d058], 0
    uint32_t t10 = mem.r32(0x0054d058u);
    uint32_t t11 = static_cast<uint32_t>(t10 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t10, 0x00000000u, t11);
    // 0x004a1db2: mov dword ptr [esp + 0x10], eax
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t12, ctx.eax);
    // 0x004a1db6: je 0x4a1ebc
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1ebc;
    goto bb_004a1dbc;
}
bb_004a1ebc: {
    // 0x004a1ebc: pop edi
    uint32_t t13 = ctx.esp;
    uint32_t t14 = mem.r32(t13);
    uint32_t t15 = static_cast<uint32_t>(t13 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    ctx.edi = static_cast<uint32_t>(t14);
    // 0x004a1ebd: pop esi
    uint32_t t16 = ctx.esp;
    uint32_t t17 = mem.r32(t16);
    uint32_t t18 = static_cast<uint32_t>(t16 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    ctx.esi = static_cast<uint32_t>(t17);
    // 0x004a1ebe: pop ebp
    uint32_t t19 = ctx.esp;
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t19 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    ctx.ebp = static_cast<uint32_t>(t20);
    // 0x004a1ebf: add esp, 0x34
    uint32_t t22 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000034u, t22);
    ctx.esp = static_cast<uint32_t>(t22);
    // 0x004a1ec2: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a1dbc: {
    // 0x004a1dbc: mov ebp, dword ptr [0x51b254]
    uint32_t t23 = mem.r32(0x0051b254u);
    ctx.ebp = static_cast<uint32_t>(t23);
    // 0x004a1dc2: mov edi, 0x54d060
    ctx.edi = static_cast<uint32_t>(0x0054d060u);
}
bb_004a1dc7: {
    // 0x004a1dc7: mov ecx, dword ptr [edi - 4]
    uint32_t t24 = static_cast<uint32_t>(ctx.edi + 0xfffffffcu);
    uint32_t t25 = mem.r32(t24);
    ctx.ecx = static_cast<uint32_t>(t25);
    // 0x004a1dca: xor eax, eax
    uint32_t t26 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t26);
    ctx.eax = static_cast<uint32_t>(t26);
    // 0x004a1dcc: mov dword ptr [esp + 0x24], eax
    uint32_t t27 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t27, ctx.eax);
    // 0x004a1dd0: mov dword ptr [esp + 0x30], eax
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    mem.w32(t28, ctx.eax);
    // 0x004a1dd4: mov dword ptr [esp + 0x34], eax
    uint32_t t29 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    mem.w32(t29, ctx.eax);
    // 0x004a1dd8: lea edx, [esp + 0x24]
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    ctx.edx = static_cast<uint32_t>(t30);
    // 0x004a1ddc: push edx
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, ctx.edx);
    // 0x004a1ddd: mov dword ptr [esp + 0x2c], eax
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    mem.w32(t32, ctx.eax);
    // 0x004a1de1: mov dword ptr [esp + 0x30], eax
    uint32_t t33 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    mem.w32(t33, ctx.eax);
    // 0x004a1de5: mov dword ptr [esp + 0x3c], eax
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    mem.w32(t34, ctx.eax);
    // 0x004a1de9: mov dword ptr [esp + 0x40], eax
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    mem.w32(t35, ctx.eax);
    // 0x004a1ded: mov eax, dword ptr [esp + 0x10]
    uint32_t t36 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t37 = mem.r32(t36);
    ctx.eax = static_cast<uint32_t>(t37);
    // 0x004a1df1: push eax
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, ctx.eax);
    // 0x004a1df2: push 0x1307
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, 0x00001307u);
    // 0x004a1df7: push ebx
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, ctx.ebx);
    // 0x004a1df8: mov dword ptr [esp + 0x34], 1
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    mem.w32(t41, 0x00000001u);
    // 0x004a1e00: mov dword ptr [esp + 0x44], 0x100
    uint32_t t42 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    mem.w32(t42, 0x00000100u);
    // 0x004a1e08: mov dword ptr [esp + 0x40], ecx
    uint32_t t43 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    mem.w32(t43, ctx.ecx);
    // 0x004a1e0c: call ebp
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, 0x004a1e0eu);
    call_indirect(ctx, mem, ctx.ebp);
    // 0x004a1e0e: mov ecx, dword ptr [edi]
    uint32_t t45 = mem.r32(ctx.edi);
    ctx.ecx = static_cast<uint32_t>(t45);
    // 0x004a1e10: mov edx, dword ptr [esp + 0x44]
    uint32_t t46 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    uint32_t t47 = mem.r32(t46);
    ctx.edx = static_cast<uint32_t>(t47);
    // 0x004a1e14: movzx eax, word ptr [edi - 8]
    uint32_t t48 = static_cast<uint32_t>(ctx.edi + 0xfffffff8u);
    uint16_t t49 = mem.r16(t48);
    uint32_t t50 = static_cast<uint32_t>(static_cast<uint16_t>(t49));
    ctx.eax = static_cast<uint32_t>(t50);
    // 0x004a1e18: push 0
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, 0x00000000u);
    // 0x004a1e1a: push ecx
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, ctx.ecx);
    // 0x004a1e1b: mov ecx, dword ptr [esp + 0x18]
    uint32_t t53 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t54 = mem.r32(t53);
    ctx.ecx = static_cast<uint32_t>(t54);
    // 0x004a1e1f: push edx
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, ctx.edx);
    // 0x004a1e20: push eax
    uint32_t t56 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    mem.w32(t56, ctx.eax);
    // 0x004a1e21: push ecx
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, ctx.ecx);
    // 0x004a1e22: call dword ptr [0x51b25c]
    uint32_t t58 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    mem.w32(t58, 0x004a1e28u);
    hle_iat_call(ctx, mem, 0x0051b25cu);
    // 0x004a1e28: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004a1e2a: test esi, esi
    uint32_t t59 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t59);
    // 0x004a1e2c: je 0x4a1e89
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1e89;
    goto bb_004a1e2e;
}
bb_004a1e89: {
    // 0x004a1e89: add dword ptr [esp + 0xc], 1
    uint32_t t60 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t61 = mem.r32(t60);
    uint32_t t62 = static_cast<uint32_t>(t61 + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t61, 0x00000001u, t62);
    mem.w32(t60, t62);
    // 0x004a1e8e: add edi, 0x10
    uint32_t t63 = static_cast<uint32_t>(ctx.edi + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000010u, t63);
    ctx.edi = static_cast<uint32_t>(t63);
    // 0x004a1e91: cmp dword ptr [edi - 8], 0
    uint32_t t64 = static_cast<uint32_t>(ctx.edi + 0xfffffff8u);
    uint32_t t65 = mem.r32(t64);
    uint32_t t66 = static_cast<uint32_t>(t65 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t65, 0x00000000u, t66);
    // 0x004a1e95: jne 0x4a1dc7
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a1dc7;
    goto bb_004a1e9b;
}
bb_004a1e2e: {
    // 0x004a1e2e: lea edx, [esp + 0x14]
    uint32_t t67 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.edx = static_cast<uint32_t>(t67);
    // 0x004a1e32: push edx
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, ctx.edx);
    // 0x004a1e33: push ebx
    uint32_t t69 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    mem.w32(t69, ctx.ebx);
    // 0x004a1e34: call dword ptr [0x51b250]
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, 0x004a1e3au);
    hle_iat_call(ctx, mem, 0x0051b250u);
    // 0x004a1e3a: lea eax, [esp + 0x14]
    uint32_t t71 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.eax = static_cast<uint32_t>(t71);
    // 0x004a1e3e: push eax
    uint32_t t72 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    mem.w32(t72, ctx.eax);
    // 0x004a1e3f: push 0
    uint32_t t73 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    mem.w32(t73, 0x00000000u);
    // 0x004a1e41: push 0x1328
    uint32_t t74 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    mem.w32(t74, 0x00001328u);
    // 0x004a1e46: push ebx
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, ctx.ebx);
    // 0x004a1e47: call ebp
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    mem.w32(t76, 0x004a1e49u);
    call_indirect(ctx, mem, ctx.ebp);
    // 0x004a1e49: mov edx, dword ptr [esp + 0x44]
    uint32_t t77 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    uint32_t t78 = mem.r32(t77);
    ctx.edx = static_cast<uint32_t>(t78);
    // 0x004a1e4d: push 2
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, 0x00000002u);
    // 0x004a1e4f: lea ecx, [esp + 0x18]
    uint32_t t80 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.ecx = static_cast<uint32_t>(t80);
    // 0x004a1e53: push ecx
    uint32_t t81 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    mem.w32(t81, ctx.ecx);
    // 0x004a1e54: push edx
    uint32_t t82 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t82);
    mem.w32(t82, ctx.edx);
    // 0x004a1e55: push ebx
    uint32_t t83 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t83);
    mem.w32(t83, ctx.ebx);
    // 0x004a1e56: call dword ptr [0x51b324]
    uint32_t t84 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    mem.w32(t84, 0x004a1e5cu);
    hle_iat_call(ctx, mem, 0x0051b324u);
    // 0x004a1e5c: mov eax, dword ptr [esp + 0x18]
    uint32_t t85 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t86 = mem.r32(t85);
    ctx.eax = static_cast<uint32_t>(t86);
    // 0x004a1e60: mov ecx, dword ptr [esp + 0x20]
    uint32_t t87 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t88 = mem.r32(t87);
    ctx.ecx = static_cast<uint32_t>(t88);
    // 0x004a1e64: mov edx, dword ptr [esp + 0x1c]
    uint32_t t89 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t90 = mem.r32(t89);
    ctx.edx = static_cast<uint32_t>(t90);
    // 0x004a1e68: push 1
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, 0x00000001u);
    // 0x004a1e6a: sub ecx, eax
    uint32_t t92 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t92);
    ctx.ecx = static_cast<uint32_t>(t92);
    // 0x004a1e6c: push ecx
    uint32_t t93 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    mem.w32(t93, ctx.ecx);
    // 0x004a1e6d: mov ecx, dword ptr [esp + 0x1c]
    uint32_t t94 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t95 = mem.r32(t94);
    ctx.ecx = static_cast<uint32_t>(t95);
    // 0x004a1e71: sub edx, ecx
    uint32_t t96 = static_cast<uint32_t>(ctx.edx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ecx, t96);
    ctx.edx = static_cast<uint32_t>(t96);
    // 0x004a1e73: push edx
    uint32_t t97 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t97);
    mem.w32(t97, ctx.edx);
    // 0x004a1e74: push eax
    uint32_t t98 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t98);
    mem.w32(t98, ctx.eax);
    // 0x004a1e75: push ecx
    uint32_t t99 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t99);
    mem.w32(t99, ctx.ecx);
    // 0x004a1e76: push esi
    uint32_t t100 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t100);
    mem.w32(t100, ctx.esi);
    // 0x004a1e77: call dword ptr [0x51b270]
    uint32_t t101 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t101);
    mem.w32(t101, 0x004a1e7du);
    hle_iat_call(ctx, mem, 0x0051b270u);
    // 0x004a1e7d: push 0
    uint32_t t102 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    mem.w32(t102, 0x00000000u);
    // 0x004a1e7f: push esi
    uint32_t t103 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    mem.w32(t103, ctx.esi);
    // 0x004a1e80: call dword ptr [0x51b23c]
    uint32_t t104 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t104);
    mem.w32(t104, 0x004a1e86u);
    hle_iat_call(ctx, mem, 0x0051b23cu);
    // 0x004a1e86: mov dword ptr [edi + 4], esi
    uint32_t t105 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    mem.w32(t105, ctx.esi);
    goto bb_004a1e89;
}
bb_004a1e9b: {
    // 0x004a1e9b: cmp dword ptr [esp + 0xc], 0
    uint32_t t106 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t107 = mem.r32(t106);
    uint32_t t108 = static_cast<uint32_t>(t107 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t107, 0x00000000u, t108);
    // 0x004a1ea0: je 0x4a1ebc
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1ebc;
}
{
    // 0x004a1ea2: push 0
    uint32_t t109 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t109);
    mem.w32(t109, 0x00000000u);
    // 0x004a1ea4: push 0
    uint32_t t110 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t110);
    mem.w32(t110, 0x00000000u);
    // 0x004a1ea6: push 0x130c
    uint32_t t111 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t111);
    mem.w32(t111, 0x0000130cu);
    // 0x004a1eab: push ebx
    uint32_t t112 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t112);
    mem.w32(t112, ctx.ebx);
    // 0x004a1eac: call ebp
    uint32_t t113 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t113);
    mem.w32(t113, 0x004a1eaeu);
    call_indirect(ctx, mem, ctx.ebp);
    // 0x004a1eae: mov eax, dword ptr [0x54d064]
    uint32_t t114 = mem.r32(0x0054d064u);
    ctx.eax = static_cast<uint32_t>(t114);
    // 0x004a1eb3: push 5
    uint32_t t115 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t115);
    mem.w32(t115, 0x00000005u);
    // 0x004a1eb5: push eax
    uint32_t t116 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t116);
    mem.w32(t116, ctx.eax);
    // 0x004a1eb6: call dword ptr [0x51b23c]
    uint32_t t117 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t117);
    mem.w32(t117, 0x004a1ebcu);
    hle_iat_call(ctx, mem, 0x0051b23cu);
    goto bb_004a1ebc;
}
}

// sub_004a1ed0 | subsystem=Core/Windows | canonical | 8 blocks | 37 insns
void sub_004a1ed0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a1ed0: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x004a1ed1: push edi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.edi);
    // 0x004a1ed2: push 0x3eb
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x000003ebu);
    // 0x004a1ed7: push eax
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.eax);
    // 0x004a1ed8: call dword ptr [0x51b2f4]
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x004a1edeu);
    hle_iat_call(ctx, mem, 0x0051b2f4u);
    // 0x004a1ede: push 0
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, 0x00000000u);
    // 0x004a1ee0: push 0
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x00000000u);
    // 0x004a1ee2: push 0x130b
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0000130bu);
    // 0x004a1ee7: push eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.eax);
    // 0x004a1ee8: call dword ptr [0x51b254]
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x004a1eeeu);
    hle_iat_call(ctx, mem, 0x0051b254u);
    // 0x004a1eee: xor edi, edi
    uint32_t t10 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.edi = static_cast<uint32_t>(t10);
    // 0x004a1ef0: cmp dword ptr [0x54d058], edi
    uint32_t t11 = mem.r32(0x0054d058u);
    uint32_t t12 = static_cast<uint32_t>(t11 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t11, ctx.edi, t12);
    // 0x004a1ef6: mov ebp, eax
    ctx.ebp = static_cast<uint32_t>(ctx.eax);
    // 0x004a1ef8: je 0x4a1f27
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1f27;
    goto bb_004a1efa;
}
bb_004a1f27: {
    // 0x004a1f27: pop edi
    uint32_t t13 = ctx.esp;
    uint32_t t14 = mem.r32(t13);
    uint32_t t15 = static_cast<uint32_t>(t13 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    ctx.edi = static_cast<uint32_t>(t14);
    // 0x004a1f28: pop ebp
    uint32_t t16 = ctx.esp;
    uint32_t t17 = mem.r32(t16);
    uint32_t t18 = static_cast<uint32_t>(t16 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    ctx.ebp = static_cast<uint32_t>(t17);
    // 0x004a1f29: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a1efa: {
    // 0x004a1efa: push ebx
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, ctx.ebx);
    // 0x004a1efb: mov ebx, dword ptr [0x51b23c]
    uint32_t t20 = mem.r32(0x0051b23cu);
    ctx.ebx = static_cast<uint32_t>(t20);
    // 0x004a1f01: push esi
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, ctx.esi);
    // 0x004a1f02: mov esi, 0x54d064
    ctx.esi = static_cast<uint32_t>(0x0054d064u);
}
bb_004a1f07: {
    // 0x004a1f07: cmp edi, ebp
    uint32_t t22 = static_cast<uint32_t>(ctx.edi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebp, t22);
    // 0x004a1f09: jne 0x4a1f12
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a1f12;
    goto bb_004a1f0b;
}
bb_004a1f12: {
    // 0x004a1f12: mov edx, dword ptr [esi]
    uint32_t t23 = mem.r32(ctx.esi);
    ctx.edx = static_cast<uint32_t>(t23);
    // 0x004a1f14: push 0
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x00000000u);
    // 0x004a1f16: push edx
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, ctx.edx);
    goto bb_004a1f17;
}
bb_004a1f0b: {
    // 0x004a1f0b: mov ecx, dword ptr [esi]
    uint32_t t26 = mem.r32(ctx.esi);
    ctx.ecx = static_cast<uint32_t>(t26);
    // 0x004a1f0d: push 5
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x00000005u);
    // 0x004a1f0f: push ecx
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, ctx.ecx);
    // 0x004a1f10: jmp 0x4a1f17
}
bb_004a1f17: {
    // 0x004a1f17: call ebx
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x004a1f19u);
    call_indirect(ctx, mem, ctx.ebx);
    // 0x004a1f19: add esi, 0x10
    uint32_t t30 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000010u, t30);
    ctx.esi = static_cast<uint32_t>(t30);
    // 0x004a1f1c: add edi, 1
    uint32_t t31 = static_cast<uint32_t>(ctx.edi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000001u, t31);
    ctx.edi = static_cast<uint32_t>(t31);
    // 0x004a1f1f: cmp dword ptr [esi - 0xc], 0
    uint32_t t32 = static_cast<uint32_t>(ctx.esi + 0xfffffff4u);
    uint32_t t33 = mem.r32(t32);
    uint32_t t34 = static_cast<uint32_t>(t33 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t33, 0x00000000u, t34);
    // 0x004a1f23: jne 0x4a1f07
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a1f07;
}
{
    // 0x004a1f25: pop esi
    uint32_t t35 = ctx.esp;
    uint32_t t36 = mem.r32(t35);
    uint32_t t37 = static_cast<uint32_t>(t35 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    ctx.esi = static_cast<uint32_t>(t36);
    // 0x004a1f26: pop ebx
    uint32_t t38 = ctx.esp;
    uint32_t t39 = mem.r32(t38);
    uint32_t t40 = static_cast<uint32_t>(t38 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    ctx.ebx = static_cast<uint32_t>(t39);
    goto bb_004a1f27;
}
}

// sub_004a1f30 | subsystem=Core/Windows | .data callback | 3 blocks | 8 insns
void sub_004a1f30(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a1f30: cmp dword ptr [esp + 8], 0x110
    uint32_t t0 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t1 = mem.r32(t0);
    uint32_t t2 = static_cast<uint32_t>(t1 - 0x00000110u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t1, 0x00000110u, t2);
    // 0x004a1f38: jne 0x4a1f47
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a1f47;
    goto bb_004a1f3a;
}
bb_004a1f47: {
    // 0x004a1f47: xor eax, eax
    uint32_t t3 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t3);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004a1f49: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a1f3a: {
    // 0x004a1f3a: mov eax, dword ptr [esp + 4]
    uint32_t t4 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint32_t t5 = mem.r32(t4);
    ctx.eax = static_cast<uint32_t>(t5);
    // 0x004a1f3e: push eax
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.eax);
    // 0x004a1f3f: call 0x4a2190
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x004a1f44u);
    sub_004a2190(ctx, mem);
    // 0x004a1f44: add esp, 4
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t8);
    ctx.esp = static_cast<uint32_t>(t8);
    goto bb_004a1f47;
}
}

// sub_004a2190 | subsystem=Core/Windows | canonical | 67 blocks | 660 insns
void sub_004a2190(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a2190: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x004a2191: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x004a2193: and esp, 0xffffffc0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xffffffc0u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x004a2196: push -1
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0xffffffffu);
    // 0x004a2198: push 0x515f73
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x00515f73u);
    // 0x004a219d: mov eax, dword ptr fs:[0]
    uint32_t t4 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t5 = mem.r32(t4);
    ctx.eax = static_cast<uint32_t>(t5);
    // 0x004a21a3: push eax
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.eax);
    // 0x004a21a4: sub esp, 0x1a8
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x000001a8u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x000001a8u, t7);
    ctx.esp = static_cast<uint32_t>(t7);
    // 0x004a21aa: mov eax, dword ptr [0x54b458]
    uint32_t t8 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x004a21af: xor eax, esp
    uint32_t t9 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x004a21b1: mov dword ptr [esp + 0x170], eax
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x00000170u);
    mem.w32(t10, ctx.eax);
    // 0x004a21b8: push ebx
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.ebx);
    // 0x004a21b9: push esi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.esi);
    // 0x004a21ba: push edi
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, ctx.edi);
    // 0x004a21bb: mov eax, dword ptr [0x54b458]
    uint32_t t14 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x004a21c0: xor eax, esp
    uint32_t t15 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t15);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x004a21c2: push eax
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, ctx.eax);
    // 0x004a21c3: lea eax, [esp + 0x1b8]
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x000001b8u);
    ctx.eax = static_cast<uint32_t>(t17);
    // 0x004a21ca: mov dword ptr fs:[0], eax
    uint32_t t18 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t18, ctx.eax);
    // 0x004a21d0: mov eax, dword ptr [ebp + 8]
    uint32_t t19 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t20 = mem.r32(t19);
    ctx.eax = static_cast<uint32_t>(t20);
    // 0x004a21d3: xor ebx, ebx
    uint32_t t21 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t21);
    ctx.ebx = static_cast<uint32_t>(t21);
    // 0x004a21d5: mov dword ptr [esp + 0x58], eax
    uint32_t t22 = static_cast<uint32_t>(ctx.esp + 0x00000058u);
    mem.w32(t22, ctx.eax);
    // 0x004a21d9: mov dword ptr [esp + 0x78], 0xf
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    mem.w32(t23, 0x0000000fu);
    // 0x004a21e1: mov dword ptr [esp + 0x74], ebx
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x00000074u);
    mem.w32(t24, ctx.ebx);
    // 0x004a21e5: mov byte ptr [esp + 0x64], bl
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000064u);
    mem.w8(t25, recomp_detail::r8l(ctx.ebx));
    // 0x004a21e9: mov dword ptr [esp + 0x1c0], ebx
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w32(t26, ctx.ebx);
    // 0x004a21f0: mov ecx, dword ptr [0x76744c]
    uint32_t t27 = mem.r32(0x0076744cu);
    ctx.ecx = static_cast<uint32_t>(t27);
    // 0x004a21f6: mov dword ptr [esp + 0x5c], ecx
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    mem.w32(t28, ctx.ecx);
    // 0x004a21fa: call 0x417020
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x004a21ffu);
    sub_00417020(ctx, mem);
    // 0x004a21ff: push 0x53a6b0
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x0053a6b0u);
    // 0x004a2204: lea esi, [esp + 0x40]
    uint32_t t31 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    ctx.esi = static_cast<uint32_t>(t31);
    // 0x004a2208: call 0x4c1ec0
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x004a220du);
    sub_004c1ec0(ctx, mem);
    // 0x004a220d: add esp, 4
    uint32_t t33 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t33);
    ctx.esp = static_cast<uint32_t>(t33);
    // 0x004a2210: push ebx
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, ctx.ebx);
    // 0x004a2211: push eax
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, ctx.eax);
    // 0x004a2212: or eax, 0xffffffff
    uint32_t t36 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t36);
    ctx.eax = static_cast<uint32_t>(t36);
    // 0x004a2215: lea esi, [esp + 0x68]
    uint32_t t37 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t37);
    // 0x004a2219: mov byte ptr [esp + 0x1c8], 1
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t38, uint8_t{0x01u});
    // 0x004a2221: call 0x414360
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, 0x004a2226u);
    sub_00414360(ctx, mem);
    // 0x004a2226: mov byte ptr [esp + 0x1c0], bl
    uint32_t t40 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t40, recomp_detail::r8l(ctx.ebx));
    // 0x004a222d: cmp dword ptr [esp + 0x54], 0x10
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t42 = mem.r32(t41);
    uint32_t t43 = static_cast<uint32_t>(t42 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t42, 0x00000010u, t43);
    // 0x004a2232: jb 0x4a2241
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a2241;
    goto bb_004a2234;
}
bb_004a2241: {
    // 0x004a2241: mov edi, dword ptr [0x76e6a0]
    uint32_t t44 = mem.r32(0x0076e6a0u);
    ctx.edi = static_cast<uint32_t>(t44);
    // 0x004a2247: push 0x53542c
    uint32_t t45 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    mem.w32(t45, 0x0053542cu);
    // 0x004a224c: lea esi, [esp + 0x80]
    uint32_t t46 = static_cast<uint32_t>(ctx.esp + 0x00000080u);
    ctx.esi = static_cast<uint32_t>(t46);
    // 0x004a2253: call 0x417200
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, 0x004a2258u);
    sub_00417200(ctx, mem);
    // 0x004a2258: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004a225a: add esp, 4
    uint32_t t48 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t48);
    ctx.esp = static_cast<uint32_t>(t48);
    // 0x004a225d: push eax
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, ctx.eax);
    // 0x004a225e: push 0x53a6bc
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, 0x0053a6bcu);
    // 0x004a2263: lea esi, [esp + 0x44]
    uint32_t t51 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    ctx.esi = static_cast<uint32_t>(t51);
    // 0x004a2267: call 0x4c1ec0
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, 0x004a226cu);
    sub_004c1ec0(ctx, mem);
    // 0x004a226c: add esp, 8
    uint32_t t53 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t53);
    ctx.esp = static_cast<uint32_t>(t53);
    // 0x004a226f: push ebx
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, ctx.ebx);
    // 0x004a2270: push eax
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, ctx.eax);
    // 0x004a2271: or eax, 0xffffffff
    uint32_t t56 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t56);
    ctx.eax = static_cast<uint32_t>(t56);
    // 0x004a2274: lea esi, [esp + 0x68]
    uint32_t t57 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t57);
    // 0x004a2278: mov byte ptr [esp + 0x1c8], 2
    uint32_t t58 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t58, uint8_t{0x02u});
    // 0x004a2280: call 0x414360
    uint32_t t59 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    mem.w32(t59, 0x004a2285u);
    sub_00414360(ctx, mem);
    // 0x004a2285: mov edi, 0x10
    ctx.edi = static_cast<uint32_t>(0x00000010u);
    // 0x004a228a: mov byte ptr [esp + 0x1c0], bl
    uint32_t t60 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t60, recomp_detail::r8l(ctx.ebx));
    // 0x004a2291: cmp dword ptr [esp + 0x54], edi
    uint32_t t61 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t62 = mem.r32(t61);
    uint32_t t63 = static_cast<uint32_t>(t62 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t62, ctx.edi, t63);
    // 0x004a2295: jb 0x4a22a4
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a22a4;
    goto bb_004a2297;
}
bb_004a2234: {
    // 0x004a2234: mov edx, dword ptr [esp + 0x40]
    uint32_t t64 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t65 = mem.r32(t64);
    ctx.edx = static_cast<uint32_t>(t65);
    // 0x004a2238: push edx
    uint32_t t66 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    mem.w32(t66, ctx.edx);
    // 0x004a2239: call 0x4e02f3
    uint32_t t67 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t67);
    mem.w32(t67, 0x004a223eu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a223e: add esp, 4
    uint32_t t68 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t68);
    ctx.esp = static_cast<uint32_t>(t68);
    goto bb_004a2241;
}
bb_004a22a4: {
    // 0x004a22a4: push 0x53a6c4
    uint32_t t69 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    mem.w32(t69, 0x0053a6c4u);
    // 0x004a22a9: lea esi, [esp + 0x40]
    uint32_t t70 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    ctx.esi = static_cast<uint32_t>(t70);
    // 0x004a22ad: call 0x4c1ec0
    uint32_t t71 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t71);
    mem.w32(t71, 0x004a22b2u);
    sub_004c1ec0(ctx, mem);
    // 0x004a22b2: add esp, 4
    uint32_t t72 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t72);
    ctx.esp = static_cast<uint32_t>(t72);
    // 0x004a22b5: push ebx
    uint32_t t73 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    mem.w32(t73, ctx.ebx);
    // 0x004a22b6: push eax
    uint32_t t74 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    mem.w32(t74, ctx.eax);
    // 0x004a22b7: or eax, 0xffffffff
    uint32_t t75 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t75);
    ctx.eax = static_cast<uint32_t>(t75);
    // 0x004a22ba: lea esi, [esp + 0x68]
    uint32_t t76 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t76);
    // 0x004a22be: mov byte ptr [esp + 0x1c8], 3
    uint32_t t77 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t77, uint8_t{0x03u});
    // 0x004a22c6: call 0x414360
    uint32_t t78 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    mem.w32(t78, 0x004a22cbu);
    sub_00414360(ctx, mem);
    // 0x004a22cb: mov byte ptr [esp + 0x1c0], bl
    uint32_t t79 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t79, recomp_detail::r8l(ctx.ebx));
    // 0x004a22d2: cmp dword ptr [esp + 0x54], edi
    uint32_t t80 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t81 = mem.r32(t80);
    uint32_t t82 = static_cast<uint32_t>(t81 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t81, ctx.edi, t82);
    // 0x004a22d6: jb 0x4a22e5
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a22e5;
    goto bb_004a22d8;
}
bb_004a2297: {
    // 0x004a2297: mov ecx, dword ptr [esp + 0x40]
    uint32_t t83 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t84 = mem.r32(t83);
    ctx.ecx = static_cast<uint32_t>(t84);
    // 0x004a229b: push ecx
    uint32_t t85 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t85);
    mem.w32(t85, ctx.ecx);
    // 0x004a229c: call 0x4e02f3
    uint32_t t86 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t86);
    mem.w32(t86, 0x004a22a1u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a22a1: add esp, 4
    uint32_t t87 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t87);
    ctx.esp = static_cast<uint32_t>(t87);
    goto bb_004a22a4;
}
bb_004a22e5: {
    // 0x004a22e5: mov edi, dword ptr [0x76e6a0]
    uint32_t t88 = mem.r32(0x0076e6a0u);
    ctx.edi = static_cast<uint32_t>(t88);
    // 0x004a22eb: push 0x5354b8
    uint32_t t89 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t89);
    mem.w32(t89, 0x005354b8u);
    // 0x004a22f0: lea esi, [esp + 0x80]
    uint32_t t90 = static_cast<uint32_t>(ctx.esp + 0x00000080u);
    ctx.esi = static_cast<uint32_t>(t90);
    // 0x004a22f7: call 0x417200
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, 0x004a22fcu);
    sub_00417200(ctx, mem);
    // 0x004a22fc: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004a22fe: add esp, 4
    uint32_t t92 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t92);
    ctx.esp = static_cast<uint32_t>(t92);
    // 0x004a2301: push eax
    uint32_t t93 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    mem.w32(t93, ctx.eax);
    // 0x004a2302: push 0x53a6bc
    uint32_t t94 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t94);
    mem.w32(t94, 0x0053a6bcu);
    // 0x004a2307: lea esi, [esp + 0x44]
    uint32_t t95 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    ctx.esi = static_cast<uint32_t>(t95);
    // 0x004a230b: call 0x4c1ec0
    uint32_t t96 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    mem.w32(t96, 0x004a2310u);
    sub_004c1ec0(ctx, mem);
    // 0x004a2310: add esp, 8
    uint32_t t97 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t97);
    ctx.esp = static_cast<uint32_t>(t97);
    // 0x004a2313: push ebx
    uint32_t t98 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t98);
    mem.w32(t98, ctx.ebx);
    // 0x004a2314: push eax
    uint32_t t99 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t99);
    mem.w32(t99, ctx.eax);
    // 0x004a2315: or eax, 0xffffffff
    uint32_t t100 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t100);
    ctx.eax = static_cast<uint32_t>(t100);
    // 0x004a2318: lea esi, [esp + 0x68]
    uint32_t t101 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t101);
    // 0x004a231c: mov byte ptr [esp + 0x1c8], 4
    uint32_t t102 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t102, uint8_t{0x04u});
    // 0x004a2324: call 0x414360
    uint32_t t103 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    mem.w32(t103, 0x004a2329u);
    sub_00414360(ctx, mem);
    // 0x004a2329: mov edi, 0x10
    ctx.edi = static_cast<uint32_t>(0x00000010u);
    // 0x004a232e: mov byte ptr [esp + 0x1c0], bl
    uint32_t t104 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t104, recomp_detail::r8l(ctx.ebx));
    // 0x004a2335: cmp dword ptr [esp + 0x54], edi
    uint32_t t105 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t106 = mem.r32(t105);
    uint32_t t107 = static_cast<uint32_t>(t106 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t106, ctx.edi, t107);
    // 0x004a2339: jb 0x4a2348
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a2348;
    goto bb_004a233b;
}
bb_004a22d8: {
    // 0x004a22d8: mov edx, dword ptr [esp + 0x40]
    uint32_t t108 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t109 = mem.r32(t108);
    ctx.edx = static_cast<uint32_t>(t109);
    // 0x004a22dc: push edx
    uint32_t t110 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t110);
    mem.w32(t110, ctx.edx);
    // 0x004a22dd: call 0x4e02f3
    uint32_t t111 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t111);
    mem.w32(t111, 0x004a22e2u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a22e2: add esp, 4
    uint32_t t112 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t112);
    ctx.esp = static_cast<uint32_t>(t112);
    goto bb_004a22e5;
}
bb_004a2348: {
    // 0x004a2348: push 0x53a6d0
    uint32_t t113 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t113);
    mem.w32(t113, 0x0053a6d0u);
    // 0x004a234d: lea esi, [esp + 0x40]
    uint32_t t114 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    ctx.esi = static_cast<uint32_t>(t114);
    // 0x004a2351: call 0x4c1ec0
    uint32_t t115 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t115);
    mem.w32(t115, 0x004a2356u);
    sub_004c1ec0(ctx, mem);
    // 0x004a2356: add esp, 4
    uint32_t t116 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t116);
    ctx.esp = static_cast<uint32_t>(t116);
    // 0x004a2359: push ebx
    uint32_t t117 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t117);
    mem.w32(t117, ctx.ebx);
    // 0x004a235a: push eax
    uint32_t t118 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    mem.w32(t118, ctx.eax);
    // 0x004a235b: or eax, 0xffffffff
    uint32_t t119 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t119);
    ctx.eax = static_cast<uint32_t>(t119);
    // 0x004a235e: lea esi, [esp + 0x68]
    uint32_t t120 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t120);
    // 0x004a2362: mov byte ptr [esp + 0x1c8], 5
    uint32_t t121 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t121, uint8_t{0x05u});
    // 0x004a236a: call 0x414360
    uint32_t t122 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t122);
    mem.w32(t122, 0x004a236fu);
    sub_00414360(ctx, mem);
    // 0x004a236f: mov byte ptr [esp + 0x1c0], bl
    uint32_t t123 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t123, recomp_detail::r8l(ctx.ebx));
    // 0x004a2376: cmp dword ptr [esp + 0x54], edi
    uint32_t t124 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t125 = mem.r32(t124);
    uint32_t t126 = static_cast<uint32_t>(t125 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t125, ctx.edi, t126);
    // 0x004a237a: jb 0x4a2389
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a2389;
    goto bb_004a237c;
}
bb_004a233b: {
    // 0x004a233b: mov ecx, dword ptr [esp + 0x40]
    uint32_t t127 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t128 = mem.r32(t127);
    ctx.ecx = static_cast<uint32_t>(t128);
    // 0x004a233f: push ecx
    uint32_t t129 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t129);
    mem.w32(t129, ctx.ecx);
    // 0x004a2340: call 0x4e02f3
    uint32_t t130 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t130);
    mem.w32(t130, 0x004a2345u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a2345: add esp, 4
    uint32_t t131 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t131);
    ctx.esp = static_cast<uint32_t>(t131);
    goto bb_004a2348;
}
bb_004a2389: {
    // 0x004a2389: mov edi, dword ptr [0x76e6a0]
    uint32_t t132 = mem.r32(0x0076e6a0u);
    ctx.edi = static_cast<uint32_t>(t132);
    // 0x004a238f: push 0x535488
    uint32_t t133 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t133);
    mem.w32(t133, 0x00535488u);
    // 0x004a2394: lea esi, [esp + 0x80]
    uint32_t t134 = static_cast<uint32_t>(ctx.esp + 0x00000080u);
    ctx.esi = static_cast<uint32_t>(t134);
    // 0x004a239b: call 0x417200
    uint32_t t135 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t135);
    mem.w32(t135, 0x004a23a0u);
    sub_00417200(ctx, mem);
    // 0x004a23a0: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004a23a2: add esp, 4
    uint32_t t136 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t136);
    ctx.esp = static_cast<uint32_t>(t136);
    // 0x004a23a5: push eax
    uint32_t t137 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t137);
    mem.w32(t137, ctx.eax);
    // 0x004a23a6: push 0x53a6bc
    uint32_t t138 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t138);
    mem.w32(t138, 0x0053a6bcu);
    // 0x004a23ab: lea esi, [esp + 0x44]
    uint32_t t139 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    ctx.esi = static_cast<uint32_t>(t139);
    // 0x004a23af: call 0x4c1ec0
    uint32_t t140 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t140);
    mem.w32(t140, 0x004a23b4u);
    sub_004c1ec0(ctx, mem);
    // 0x004a23b4: add esp, 8
    uint32_t t141 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t141);
    ctx.esp = static_cast<uint32_t>(t141);
    // 0x004a23b7: push ebx
    uint32_t t142 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t142);
    mem.w32(t142, ctx.ebx);
    // 0x004a23b8: push eax
    uint32_t t143 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t143);
    mem.w32(t143, ctx.eax);
    // 0x004a23b9: or eax, 0xffffffff
    uint32_t t144 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t144);
    ctx.eax = static_cast<uint32_t>(t144);
    // 0x004a23bc: lea esi, [esp + 0x68]
    uint32_t t145 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t145);
    // 0x004a23c0: mov byte ptr [esp + 0x1c8], 6
    uint32_t t146 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t146, uint8_t{0x06u});
    // 0x004a23c8: call 0x414360
    uint32_t t147 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t147);
    mem.w32(t147, 0x004a23cdu);
    sub_00414360(ctx, mem);
    // 0x004a23cd: mov edi, 0x10
    ctx.edi = static_cast<uint32_t>(0x00000010u);
    // 0x004a23d2: mov byte ptr [esp + 0x1c0], bl
    uint32_t t148 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t148, recomp_detail::r8l(ctx.ebx));
    // 0x004a23d9: cmp dword ptr [esp + 0x54], edi
    uint32_t t149 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t150 = mem.r32(t149);
    uint32_t t151 = static_cast<uint32_t>(t150 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t150, ctx.edi, t151);
    // 0x004a23dd: jb 0x4a23ec
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a23ec;
    goto bb_004a23df;
}
bb_004a237c: {
    // 0x004a237c: mov edx, dword ptr [esp + 0x40]
    uint32_t t152 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t153 = mem.r32(t152);
    ctx.edx = static_cast<uint32_t>(t153);
    // 0x004a2380: push edx
    uint32_t t154 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t154);
    mem.w32(t154, ctx.edx);
    // 0x004a2381: call 0x4e02f3
    uint32_t t155 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t155);
    mem.w32(t155, 0x004a2386u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a2386: add esp, 4
    uint32_t t156 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t156);
    ctx.esp = static_cast<uint32_t>(t156);
    goto bb_004a2389;
}
bb_004a23ec: {
    // 0x004a23ec: push 0x53a6e0
    uint32_t t157 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t157);
    mem.w32(t157, 0x0053a6e0u);
    // 0x004a23f1: lea esi, [esp + 0x40]
    uint32_t t158 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    ctx.esi = static_cast<uint32_t>(t158);
    // 0x004a23f5: call 0x4c1ec0
    uint32_t t159 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t159);
    mem.w32(t159, 0x004a23fau);
    sub_004c1ec0(ctx, mem);
    // 0x004a23fa: add esp, 4
    uint32_t t160 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t160);
    ctx.esp = static_cast<uint32_t>(t160);
    // 0x004a23fd: push ebx
    uint32_t t161 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t161);
    mem.w32(t161, ctx.ebx);
    // 0x004a23fe: push eax
    uint32_t t162 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t162);
    mem.w32(t162, ctx.eax);
    // 0x004a23ff: or eax, 0xffffffff
    uint32_t t163 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t163);
    ctx.eax = static_cast<uint32_t>(t163);
    // 0x004a2402: lea esi, [esp + 0x68]
    uint32_t t164 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t164);
    // 0x004a2406: mov byte ptr [esp + 0x1c8], 7
    uint32_t t165 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t165, uint8_t{0x07u});
    // 0x004a240e: call 0x414360
    uint32_t t166 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t166);
    mem.w32(t166, 0x004a2413u);
    sub_00414360(ctx, mem);
    // 0x004a2413: mov byte ptr [esp + 0x1c0], bl
    uint32_t t167 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t167, recomp_detail::r8l(ctx.ebx));
    // 0x004a241a: cmp dword ptr [esp + 0x54], edi
    uint32_t t168 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t169 = mem.r32(t168);
    uint32_t t170 = static_cast<uint32_t>(t169 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t169, ctx.edi, t170);
    // 0x004a241e: jb 0x4a242d
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a242d;
    goto bb_004a2420;
}
bb_004a23df: {
    // 0x004a23df: mov ecx, dword ptr [esp + 0x40]
    uint32_t t171 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t172 = mem.r32(t171);
    ctx.ecx = static_cast<uint32_t>(t172);
    // 0x004a23e3: push ecx
    uint32_t t173 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t173);
    mem.w32(t173, ctx.ecx);
    // 0x004a23e4: call 0x4e02f3
    uint32_t t174 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t174);
    mem.w32(t174, 0x004a23e9u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a23e9: add esp, 4
    uint32_t t175 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t175);
    ctx.esp = static_cast<uint32_t>(t175);
    goto bb_004a23ec;
}
bb_004a242d: {
    // 0x004a242d: mov edi, dword ptr [0x76e6a8]
    uint32_t t176 = mem.r32(0x0076e6a8u);
    ctx.edi = static_cast<uint32_t>(t176);
    // 0x004a2433: push 0x535574
    uint32_t t177 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t177);
    mem.w32(t177, 0x00535574u);
    // 0x004a2438: lea esi, [esp + 0x80]
    uint32_t t178 = static_cast<uint32_t>(ctx.esp + 0x00000080u);
    ctx.esi = static_cast<uint32_t>(t178);
    // 0x004a243f: call 0x417200
    uint32_t t179 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t179);
    mem.w32(t179, 0x004a2444u);
    sub_00417200(ctx, mem);
    // 0x004a2444: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004a2446: add esp, 4
    uint32_t t180 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t180);
    ctx.esp = static_cast<uint32_t>(t180);
    // 0x004a2449: push eax
    uint32_t t181 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t181);
    mem.w32(t181, ctx.eax);
    // 0x004a244a: push 0x53a6bc
    uint32_t t182 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t182);
    mem.w32(t182, 0x0053a6bcu);
    // 0x004a244f: lea esi, [esp + 0x44]
    uint32_t t183 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    ctx.esi = static_cast<uint32_t>(t183);
    // 0x004a2453: call 0x4c1ec0
    uint32_t t184 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t184);
    mem.w32(t184, 0x004a2458u);
    sub_004c1ec0(ctx, mem);
    // 0x004a2458: add esp, 8
    uint32_t t185 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t185);
    ctx.esp = static_cast<uint32_t>(t185);
    // 0x004a245b: push ebx
    uint32_t t186 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t186);
    mem.w32(t186, ctx.ebx);
    // 0x004a245c: push eax
    uint32_t t187 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t187);
    mem.w32(t187, ctx.eax);
    // 0x004a245d: or eax, 0xffffffff
    uint32_t t188 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t188);
    ctx.eax = static_cast<uint32_t>(t188);
    // 0x004a2460: lea esi, [esp + 0x68]
    uint32_t t189 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t189);
    // 0x004a2464: mov byte ptr [esp + 0x1c8], 8
    uint32_t t190 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t190, uint8_t{0x08u});
    // 0x004a246c: call 0x414360
    uint32_t t191 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t191);
    mem.w32(t191, 0x004a2471u);
    sub_00414360(ctx, mem);
    // 0x004a2471: mov edi, 0x10
    ctx.edi = static_cast<uint32_t>(0x00000010u);
    // 0x004a2476: mov byte ptr [esp + 0x1c0], bl
    uint32_t t192 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t192, recomp_detail::r8l(ctx.ebx));
    // 0x004a247d: cmp dword ptr [esp + 0x54], edi
    uint32_t t193 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t194 = mem.r32(t193);
    uint32_t t195 = static_cast<uint32_t>(t194 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t194, ctx.edi, t195);
    // 0x004a2481: jb 0x4a2490
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a2490;
    goto bb_004a2483;
}
bb_004a2420: {
    // 0x004a2420: mov edx, dword ptr [esp + 0x40]
    uint32_t t196 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t197 = mem.r32(t196);
    ctx.edx = static_cast<uint32_t>(t197);
    // 0x004a2424: push edx
    uint32_t t198 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t198);
    mem.w32(t198, ctx.edx);
    // 0x004a2425: call 0x4e02f3
    uint32_t t199 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t199);
    mem.w32(t199, 0x004a242au);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a242a: add esp, 4
    uint32_t t200 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t200);
    ctx.esp = static_cast<uint32_t>(t200);
    goto bb_004a242d;
}
bb_004a2490: {
    // 0x004a2490: push 2
    uint32_t t201 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t201);
    mem.w32(t201, 0x00000002u);
    // 0x004a2492: push 0x538d44
    uint32_t t202 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t202);
    mem.w32(t202, 0x00538d44u);
    // 0x004a2497: lea eax, [esp + 0x68]
    uint32_t t203 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.eax = static_cast<uint32_t>(t203);
    // 0x004a249b: call 0x414660
    uint32_t t204 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t204);
    mem.w32(t204, 0x004a24a0u);
    sub_00414660(ctx, mem);
    // 0x004a24a0: push 0x7b4b79
    uint32_t t205 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t205);
    mem.w32(t205, 0x007b4b79u);
    // 0x004a24a5: lea esi, [esp + 0x40]
    uint32_t t206 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    ctx.esi = static_cast<uint32_t>(t206);
    // 0x004a24a9: call 0x4c1ec0
    uint32_t t207 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t207);
    mem.w32(t207, 0x004a24aeu);
    sub_004c1ec0(ctx, mem);
    // 0x004a24ae: add esp, 4
    uint32_t t208 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t208);
    ctx.esp = static_cast<uint32_t>(t208);
    // 0x004a24b1: push ebx
    uint32_t t209 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t209);
    mem.w32(t209, ctx.ebx);
    // 0x004a24b2: push eax
    uint32_t t210 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t210);
    mem.w32(t210, ctx.eax);
    // 0x004a24b3: or eax, 0xffffffff
    uint32_t t211 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t211);
    ctx.eax = static_cast<uint32_t>(t211);
    // 0x004a24b6: lea esi, [esp + 0x68]
    uint32_t t212 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t212);
    // 0x004a24ba: mov byte ptr [esp + 0x1c8], 9
    uint32_t t213 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t213, uint8_t{0x09u});
    // 0x004a24c2: call 0x414360
    uint32_t t214 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t214);
    mem.w32(t214, 0x004a24c7u);
    sub_00414360(ctx, mem);
    // 0x004a24c7: mov byte ptr [esp + 0x1c0], bl
    uint32_t t215 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t215, recomp_detail::r8l(ctx.ebx));
    // 0x004a24ce: cmp dword ptr [esp + 0x54], edi
    uint32_t t216 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t217 = mem.r32(t216);
    uint32_t t218 = static_cast<uint32_t>(t217 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t217, ctx.edi, t218);
    // 0x004a24d2: jb 0x4a24e1
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a24e1;
    goto bb_004a24d4;
}
bb_004a2483: {
    // 0x004a2483: mov ecx, dword ptr [esp + 0x40]
    uint32_t t219 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t220 = mem.r32(t219);
    ctx.ecx = static_cast<uint32_t>(t220);
    // 0x004a2487: push ecx
    uint32_t t221 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t221);
    mem.w32(t221, ctx.ecx);
    // 0x004a2488: call 0x4e02f3
    uint32_t t222 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t222);
    mem.w32(t222, 0x004a248du);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a248d: add esp, 4
    uint32_t t223 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t223);
    ctx.esp = static_cast<uint32_t>(t223);
    goto bb_004a2490;
}
bb_004a24e1: {
    // 0x004a24e1: mov edi, dword ptr [0x76e6a8]
    uint32_t t224 = mem.r32(0x0076e6a8u);
    ctx.edi = static_cast<uint32_t>(t224);
    // 0x004a24e7: push 0x535544
    uint32_t t225 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t225);
    mem.w32(t225, 0x00535544u);
    // 0x004a24ec: lea esi, [esp + 0x80]
    uint32_t t226 = static_cast<uint32_t>(ctx.esp + 0x00000080u);
    ctx.esi = static_cast<uint32_t>(t226);
    // 0x004a24f3: call 0x417200
    uint32_t t227 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t227);
    mem.w32(t227, 0x004a24f8u);
    sub_00417200(ctx, mem);
    // 0x004a24f8: mov eax, dword ptr [esp + 0x60]
    uint32_t t228 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    uint32_t t229 = mem.r32(t228);
    ctx.eax = static_cast<uint32_t>(t229);
    // 0x004a24fc: mov ecx, dword ptr [eax + 0xc]
    uint32_t t230 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    uint32_t t231 = mem.r32(t230);
    ctx.ecx = static_cast<uint32_t>(t231);
    // 0x004a24ff: add esp, 4
    uint32_t t232 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t232);
    ctx.esp = static_cast<uint32_t>(t232);
    // 0x004a2502: add ecx, 0x200
    uint32_t t233 = static_cast<uint32_t>(ctx.ecx + 0x00000200u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000200u, t233);
    ctx.ecx = static_cast<uint32_t>(t233);
    // 0x004a2508: push ecx
    uint32_t t234 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t234);
    mem.w32(t234, ctx.ecx);
    // 0x004a2509: push 0x53a6bc
    uint32_t t235 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t235);
    mem.w32(t235, 0x0053a6bcu);
    // 0x004a250e: lea esi, [esp + 0x44]
    uint32_t t236 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    ctx.esi = static_cast<uint32_t>(t236);
    // 0x004a2512: call 0x4c1ec0
    uint32_t t237 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t237);
    mem.w32(t237, 0x004a2517u);
    sub_004c1ec0(ctx, mem);
    // 0x004a2517: add esp, 8
    uint32_t t238 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t238);
    ctx.esp = static_cast<uint32_t>(t238);
    // 0x004a251a: push ebx
    uint32_t t239 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t239);
    mem.w32(t239, ctx.ebx);
    // 0x004a251b: push eax
    uint32_t t240 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t240);
    mem.w32(t240, ctx.eax);
    // 0x004a251c: or eax, 0xffffffff
    uint32_t t241 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t241);
    ctx.eax = static_cast<uint32_t>(t241);
    // 0x004a251f: lea esi, [esp + 0x68]
    uint32_t t242 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t242);
    // 0x004a2523: mov byte ptr [esp + 0x1c8], 0xa
    uint32_t t243 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t243, uint8_t{0x0au});
    // 0x004a252b: call 0x414360
    uint32_t t244 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t244);
    mem.w32(t244, 0x004a2530u);
    sub_00414360(ctx, mem);
    // 0x004a2530: mov edi, 0x10
    ctx.edi = static_cast<uint32_t>(0x00000010u);
    // 0x004a2535: mov byte ptr [esp + 0x1c0], bl
    uint32_t t245 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t245, recomp_detail::r8l(ctx.ebx));
    // 0x004a253c: cmp dword ptr [esp + 0x54], edi
    uint32_t t246 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t247 = mem.r32(t246);
    uint32_t t248 = static_cast<uint32_t>(t247 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t247, ctx.edi, t248);
    // 0x004a2540: jb 0x4a254f
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a254f;
    goto bb_004a2542;
}
bb_004a24d4: {
    // 0x004a24d4: mov edx, dword ptr [esp + 0x40]
    uint32_t t249 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t250 = mem.r32(t249);
    ctx.edx = static_cast<uint32_t>(t250);
    // 0x004a24d8: push edx
    uint32_t t251 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t251);
    mem.w32(t251, ctx.edx);
    // 0x004a24d9: call 0x4e02f3
    uint32_t t252 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t252);
    mem.w32(t252, 0x004a24deu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a24de: add esp, 4
    uint32_t t253 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t253);
    ctx.esp = static_cast<uint32_t>(t253);
    goto bb_004a24e1;
}
bb_004a254f: {
    // 0x004a254f: lea eax, [esp + 0x7c]
    uint32_t t254 = static_cast<uint32_t>(ctx.esp + 0x0000007cu);
    ctx.eax = static_cast<uint32_t>(t254);
    // 0x004a2553: push eax
    uint32_t t255 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t255);
    mem.w32(t255, ctx.eax);
    // 0x004a2554: push 0x53a708
    uint32_t t256 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t256);
    mem.w32(t256, 0x0053a708u);
    // 0x004a2559: lea esi, [esp + 0x44]
    uint32_t t257 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    ctx.esi = static_cast<uint32_t>(t257);
    // 0x004a255d: call 0x4c1ec0
    uint32_t t258 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t258);
    mem.w32(t258, 0x004a2562u);
    sub_004c1ec0(ctx, mem);
    // 0x004a2562: add esp, 8
    uint32_t t259 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t259);
    ctx.esp = static_cast<uint32_t>(t259);
    // 0x004a2565: push ebx
    uint32_t t260 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t260);
    mem.w32(t260, ctx.ebx);
    // 0x004a2566: push eax
    uint32_t t261 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t261);
    mem.w32(t261, ctx.eax);
    // 0x004a2567: or eax, 0xffffffff
    uint32_t t262 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t262);
    ctx.eax = static_cast<uint32_t>(t262);
    // 0x004a256a: lea esi, [esp + 0x68]
    uint32_t t263 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t263);
    // 0x004a256e: mov byte ptr [esp + 0x1c8], 0xb
    uint32_t t264 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t264, uint8_t{0x0bu});
    // 0x004a2576: call 0x414360
    uint32_t t265 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t265);
    mem.w32(t265, 0x004a257bu);
    sub_00414360(ctx, mem);
    // 0x004a257b: mov byte ptr [esp + 0x1c0], bl
    uint32_t t266 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t266, recomp_detail::r8l(ctx.ebx));
    // 0x004a2582: cmp dword ptr [esp + 0x54], edi
    uint32_t t267 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t268 = mem.r32(t267);
    uint32_t t269 = static_cast<uint32_t>(t268 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t268, ctx.edi, t269);
    // 0x004a2586: jb 0x4a2595
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a2595;
    goto bb_004a2588;
}
bb_004a2542: {
    // 0x004a2542: mov edx, dword ptr [esp + 0x40]
    uint32_t t270 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t271 = mem.r32(t270);
    ctx.edx = static_cast<uint32_t>(t271);
    // 0x004a2546: push edx
    uint32_t t272 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t272);
    mem.w32(t272, ctx.edx);
    // 0x004a2547: call 0x4e02f3
    uint32_t t273 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t273);
    mem.w32(t273, 0x004a254cu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a254c: add esp, 4
    uint32_t t274 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t274);
    ctx.esp = static_cast<uint32_t>(t274);
    goto bb_004a254f;
}
bb_004a2595: {
    // 0x004a2595: mov edi, dword ptr [0x76e6a8]
    uint32_t t275 = mem.r32(0x0076e6a8u);
    ctx.edi = static_cast<uint32_t>(t275);
    // 0x004a259b: push 0x5355a0
    uint32_t t276 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t276);
    mem.w32(t276, 0x005355a0u);
    // 0x004a25a0: lea esi, [esp + 0x80]
    uint32_t t277 = static_cast<uint32_t>(ctx.esp + 0x00000080u);
    ctx.esi = static_cast<uint32_t>(t277);
    // 0x004a25a7: call 0x417200
    uint32_t t278 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t278);
    mem.w32(t278, 0x004a25acu);
    sub_00417200(ctx, mem);
    // 0x004a25ac: mov edx, esi
    ctx.edx = static_cast<uint32_t>(ctx.esi);
    // 0x004a25ae: add esp, 4
    uint32_t t279 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t279);
    ctx.esp = static_cast<uint32_t>(t279);
    // 0x004a25b1: push edx
    uint32_t t280 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t280);
    mem.w32(t280, ctx.edx);
    // 0x004a25b2: push 0x7b4b8f
    uint32_t t281 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t281);
    mem.w32(t281, 0x007b4b8fu);
    // 0x004a25b7: lea esi, [esp + 0x44]
    uint32_t t282 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    ctx.esi = static_cast<uint32_t>(t282);
    // 0x004a25bb: call 0x4c1ec0
    uint32_t t283 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t283);
    mem.w32(t283, 0x004a25c0u);
    sub_004c1ec0(ctx, mem);
    // 0x004a25c0: add esp, 8
    uint32_t t284 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t284);
    ctx.esp = static_cast<uint32_t>(t284);
    // 0x004a25c3: push ebx
    uint32_t t285 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t285);
    mem.w32(t285, ctx.ebx);
    // 0x004a25c4: push eax
    uint32_t t286 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t286);
    mem.w32(t286, ctx.eax);
    // 0x004a25c5: or eax, 0xffffffff
    uint32_t t287 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t287);
    ctx.eax = static_cast<uint32_t>(t287);
    // 0x004a25c8: lea esi, [esp + 0x68]
    uint32_t t288 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t288);
    // 0x004a25cc: mov byte ptr [esp + 0x1c8], 0xc
    uint32_t t289 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t289, uint8_t{0x0cu});
    // 0x004a25d4: call 0x414360
    uint32_t t290 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t290);
    mem.w32(t290, 0x004a25d9u);
    sub_00414360(ctx, mem);
    // 0x004a25d9: mov edi, 0x10
    ctx.edi = static_cast<uint32_t>(0x00000010u);
    // 0x004a25de: mov byte ptr [esp + 0x1c0], bl
    uint32_t t291 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t291, recomp_detail::r8l(ctx.ebx));
    // 0x004a25e5: cmp dword ptr [esp + 0x54], edi
    uint32_t t292 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t293 = mem.r32(t292);
    uint32_t t294 = static_cast<uint32_t>(t293 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t293, ctx.edi, t294);
    // 0x004a25e9: jb 0x4a25f8
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a25f8;
    goto bb_004a25eb;
}
bb_004a2588: {
    // 0x004a2588: mov ecx, dword ptr [esp + 0x40]
    uint32_t t295 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t296 = mem.r32(t295);
    ctx.ecx = static_cast<uint32_t>(t296);
    // 0x004a258c: push ecx
    uint32_t t297 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t297);
    mem.w32(t297, ctx.ecx);
    // 0x004a258d: call 0x4e02f3
    uint32_t t298 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t298);
    mem.w32(t298, 0x004a2592u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a2592: add esp, 4
    uint32_t t299 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t299);
    ctx.esp = static_cast<uint32_t>(t299);
    goto bb_004a2595;
}
bb_004a25f8: {
    // 0x004a25f8: push 2
    uint32_t t300 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t300);
    mem.w32(t300, 0x00000002u);
    // 0x004a25fa: push 0x538d44
    uint32_t t301 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t301);
    mem.w32(t301, 0x00538d44u);
    // 0x004a25ff: lea eax, [esp + 0x68]
    uint32_t t302 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.eax = static_cast<uint32_t>(t302);
    // 0x004a2603: call 0x414660
    uint32_t t303 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t303);
    mem.w32(t303, 0x004a2608u);
    sub_00414660(ctx, mem);
    // 0x004a2608: push 0x53a72c
    uint32_t t304 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t304);
    mem.w32(t304, 0x0053a72cu);
    // 0x004a260d: lea esi, [esp + 0x40]
    uint32_t t305 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    ctx.esi = static_cast<uint32_t>(t305);
    // 0x004a2611: call 0x4c1ec0
    uint32_t t306 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t306);
    mem.w32(t306, 0x004a2616u);
    sub_004c1ec0(ctx, mem);
    // 0x004a2616: add esp, 4
    uint32_t t307 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t307);
    ctx.esp = static_cast<uint32_t>(t307);
    // 0x004a2619: push ebx
    uint32_t t308 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t308);
    mem.w32(t308, ctx.ebx);
    // 0x004a261a: push eax
    uint32_t t309 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t309);
    mem.w32(t309, ctx.eax);
    // 0x004a261b: or eax, 0xffffffff
    uint32_t t310 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t310);
    ctx.eax = static_cast<uint32_t>(t310);
    // 0x004a261e: lea esi, [esp + 0x68]
    uint32_t t311 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t311);
    // 0x004a2622: mov byte ptr [esp + 0x1c8], 0xd
    uint32_t t312 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t312, uint8_t{0x0du});
    // 0x004a262a: call 0x414360
    uint32_t t313 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t313);
    mem.w32(t313, 0x004a262fu);
    sub_00414360(ctx, mem);
    // 0x004a262f: mov byte ptr [esp + 0x1c0], bl
    uint32_t t314 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t314, recomp_detail::r8l(ctx.ebx));
    // 0x004a2636: cmp dword ptr [esp + 0x54], edi
    uint32_t t315 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t316 = mem.r32(t315);
    uint32_t t317 = static_cast<uint32_t>(t316 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t316, ctx.edi, t317);
    // 0x004a263a: jb 0x4a2649
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a2649;
    goto bb_004a263c;
}
bb_004a25eb: {
    // 0x004a25eb: mov eax, dword ptr [esp + 0x40]
    uint32_t t318 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t319 = mem.r32(t318);
    ctx.eax = static_cast<uint32_t>(t319);
    // 0x004a25ef: push eax
    uint32_t t320 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t320);
    mem.w32(t320, ctx.eax);
    // 0x004a25f0: call 0x4e02f3
    uint32_t t321 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t321);
    mem.w32(t321, 0x004a25f5u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a25f5: add esp, 4
    uint32_t t322 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t322);
    ctx.esp = static_cast<uint32_t>(t322);
    goto bb_004a25f8;
}
bb_004a2649: {
    // 0x004a2649: mov edi, dword ptr [0x76e6a0]
    uint32_t t323 = mem.r32(0x0076e6a0u);
    ctx.edi = static_cast<uint32_t>(t323);
    // 0x004a264f: push 0x535450
    uint32_t t324 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t324);
    mem.w32(t324, 0x00535450u);
    // 0x004a2654: lea esi, [esp + 0x80]
    uint32_t t325 = static_cast<uint32_t>(ctx.esp + 0x00000080u);
    ctx.esi = static_cast<uint32_t>(t325);
    // 0x004a265b: call 0x417200
    uint32_t t326 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t326);
    mem.w32(t326, 0x004a2660u);
    sub_00417200(ctx, mem);
    // 0x004a2660: mov edx, esi
    ctx.edx = static_cast<uint32_t>(ctx.esi);
    // 0x004a2662: add esp, 4
    uint32_t t327 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t327);
    ctx.esp = static_cast<uint32_t>(t327);
    // 0x004a2665: push edx
    uint32_t t328 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t328);
    mem.w32(t328, ctx.edx);
    // 0x004a2666: push 0x53a6bc
    uint32_t t329 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t329);
    mem.w32(t329, 0x0053a6bcu);
    // 0x004a266b: lea esi, [esp + 0x44]
    uint32_t t330 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    ctx.esi = static_cast<uint32_t>(t330);
    // 0x004a266f: call 0x4c1ec0
    uint32_t t331 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t331);
    mem.w32(t331, 0x004a2674u);
    sub_004c1ec0(ctx, mem);
    // 0x004a2674: add esp, 8
    uint32_t t332 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t332);
    ctx.esp = static_cast<uint32_t>(t332);
    // 0x004a2677: push ebx
    uint32_t t333 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t333);
    mem.w32(t333, ctx.ebx);
    // 0x004a2678: push eax
    uint32_t t334 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t334);
    mem.w32(t334, ctx.eax);
    // 0x004a2679: or eax, 0xffffffff
    uint32_t t335 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t335);
    ctx.eax = static_cast<uint32_t>(t335);
    // 0x004a267c: lea esi, [esp + 0x68]
    uint32_t t336 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t336);
    // 0x004a2680: mov byte ptr [esp + 0x1c8], 0xe
    uint32_t t337 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t337, uint8_t{0x0eu});
    // 0x004a2688: call 0x414360
    uint32_t t338 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t338);
    mem.w32(t338, 0x004a268du);
    sub_00414360(ctx, mem);
    // 0x004a268d: mov edi, 0x10
    ctx.edi = static_cast<uint32_t>(0x00000010u);
    // 0x004a2692: mov byte ptr [esp + 0x1c0], bl
    uint32_t t339 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t339, recomp_detail::r8l(ctx.ebx));
    // 0x004a2699: cmp dword ptr [esp + 0x54], edi
    uint32_t t340 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t341 = mem.r32(t340);
    uint32_t t342 = static_cast<uint32_t>(t341 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t341, ctx.edi, t342);
    // 0x004a269d: jb 0x4a26ac
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a26ac;
    goto bb_004a269f;
}
bb_004a263c: {
    // 0x004a263c: mov ecx, dword ptr [esp + 0x40]
    uint32_t t343 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t344 = mem.r32(t343);
    ctx.ecx = static_cast<uint32_t>(t344);
    // 0x004a2640: push ecx
    uint32_t t345 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t345);
    mem.w32(t345, ctx.ecx);
    // 0x004a2641: call 0x4e02f3
    uint32_t t346 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t346);
    mem.w32(t346, 0x004a2646u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a2646: add esp, 4
    uint32_t t347 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t347);
    ctx.esp = static_cast<uint32_t>(t347);
    goto bb_004a2649;
}
bb_004a26ac: {
    // 0x004a26ac: cmp dword ptr [esp + 0x78], edi
    uint32_t t348 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    uint32_t t349 = mem.r32(t348);
    uint32_t t350 = static_cast<uint32_t>(t349 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t349, ctx.edi, t350);
    // 0x004a26b0: mov eax, dword ptr [esp + 0x64]
    uint32_t t351 = static_cast<uint32_t>(ctx.esp + 0x00000064u);
    uint32_t t352 = mem.r32(t351);
    ctx.eax = static_cast<uint32_t>(t352);
    // 0x004a26b4: jae 0x4a26ba
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004a26ba;
    goto bb_004a26b6;
}
bb_004a269f: {
    // 0x004a269f: mov eax, dword ptr [esp + 0x40]
    uint32_t t353 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t354 = mem.r32(t353);
    ctx.eax = static_cast<uint32_t>(t354);
    // 0x004a26a3: push eax
    uint32_t t355 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t355);
    mem.w32(t355, ctx.eax);
    // 0x004a26a4: call 0x4e02f3
    uint32_t t356 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t356);
    mem.w32(t356, 0x004a26a9u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a26a9: add esp, 4
    uint32_t t357 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t357);
    ctx.esp = static_cast<uint32_t>(t357);
    goto bb_004a26ac;
}
bb_004a26ba: {
    // 0x004a26ba: mov ecx, dword ptr [esp + 0x58]
    uint32_t t358 = static_cast<uint32_t>(ctx.esp + 0x00000058u);
    uint32_t t359 = mem.r32(t358);
    ctx.ecx = static_cast<uint32_t>(t359);
    // 0x004a26be: push eax
    uint32_t t360 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t360);
    mem.w32(t360, ctx.eax);
    // 0x004a26bf: push 0x3ee
    uint32_t t361 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t361);
    mem.w32(t361, 0x000003eeu);
    // 0x004a26c4: push ecx
    uint32_t t362 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t362);
    mem.w32(t362, ctx.ecx);
    // 0x004a26c5: call dword ptr [0x51b2d4]
    uint32_t t363 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t363);
    mem.w32(t363, 0x004a26cbu);
    hle_iat_call(ctx, mem, 0x0051b2d4u);
    // 0x004a26cb: push 0x7b4ba4
    uint32_t t364 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t364);
    mem.w32(t364, 0x007b4ba4u);
    // 0x004a26d0: lea esi, [esp + 0x40]
    uint32_t t365 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    ctx.esi = static_cast<uint32_t>(t365);
    // 0x004a26d4: call 0x4c1ec0
    uint32_t t366 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t366);
    mem.w32(t366, 0x004a26d9u);
    sub_004c1ec0(ctx, mem);
    // 0x004a26d9: add esp, 4
    uint32_t t367 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t367);
    ctx.esp = static_cast<uint32_t>(t367);
    // 0x004a26dc: push ebx
    uint32_t t368 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t368);
    mem.w32(t368, ctx.ebx);
    // 0x004a26dd: push eax
    uint32_t t369 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t369);
    mem.w32(t369, ctx.eax);
    // 0x004a26de: or eax, 0xffffffff
    uint32_t t370 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t370);
    ctx.eax = static_cast<uint32_t>(t370);
    // 0x004a26e1: lea esi, [esp + 0x68]
    uint32_t t371 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t371);
    // 0x004a26e5: mov byte ptr [esp + 0x1c8], 0xf
    uint32_t t372 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t372, uint8_t{0x0fu});
    // 0x004a26ed: call 0x414360
    uint32_t t373 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t373);
    mem.w32(t373, 0x004a26f2u);
    sub_00414360(ctx, mem);
    // 0x004a26f2: mov byte ptr [esp + 0x1c0], bl
    uint32_t t374 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t374, recomp_detail::r8l(ctx.ebx));
    // 0x004a26f9: cmp dword ptr [esp + 0x54], edi
    uint32_t t375 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t376 = mem.r32(t375);
    uint32_t t377 = static_cast<uint32_t>(t376 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t376, ctx.edi, t377);
    // 0x004a26fd: jb 0x4a270c
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a270c;
    goto bb_004a26ff;
}
bb_004a26b6: {
    // 0x004a26b6: lea eax, [esp + 0x64]
    uint32_t t378 = static_cast<uint32_t>(ctx.esp + 0x00000064u);
    ctx.eax = static_cast<uint32_t>(t378);
    goto bb_004a26ba;
}
bb_004a270c: {
    // 0x004a270c: mov edi, dword ptr [0x76e6a0]
    uint32_t t379 = mem.r32(0x0076e6a0u);
    ctx.edi = static_cast<uint32_t>(t379);
    // 0x004a2712: push 0x53550c
    uint32_t t380 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t380);
    mem.w32(t380, 0x0053550cu);
    // 0x004a2717: lea esi, [esp + 0x80]
    uint32_t t381 = static_cast<uint32_t>(ctx.esp + 0x00000080u);
    ctx.esi = static_cast<uint32_t>(t381);
    // 0x004a271e: call 0x417200
    uint32_t t382 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t382);
    mem.w32(t382, 0x004a2723u);
    sub_00417200(ctx, mem);
    // 0x004a2723: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004a2725: add esp, 4
    uint32_t t383 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t383);
    ctx.esp = static_cast<uint32_t>(t383);
    // 0x004a2728: push eax
    uint32_t t384 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t384);
    mem.w32(t384, ctx.eax);
    // 0x004a2729: push 0x53a6bc
    uint32_t t385 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t385);
    mem.w32(t385, 0x0053a6bcu);
    // 0x004a272e: lea esi, [esp + 0x44]
    uint32_t t386 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    ctx.esi = static_cast<uint32_t>(t386);
    // 0x004a2732: call 0x4c1ec0
    uint32_t t387 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t387);
    mem.w32(t387, 0x004a2737u);
    sub_004c1ec0(ctx, mem);
    // 0x004a2737: add esp, 8
    uint32_t t388 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t388);
    ctx.esp = static_cast<uint32_t>(t388);
    // 0x004a273a: push ebx
    uint32_t t389 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t389);
    mem.w32(t389, ctx.ebx);
    // 0x004a273b: push eax
    uint32_t t390 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t390);
    mem.w32(t390, ctx.eax);
    // 0x004a273c: or eax, 0xffffffff
    uint32_t t391 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t391);
    ctx.eax = static_cast<uint32_t>(t391);
    // 0x004a273f: lea esi, [esp + 0x68]
    uint32_t t392 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t392);
    // 0x004a2743: mov byte ptr [esp + 0x1c8], 0x10
    uint32_t t393 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t393, uint8_t{0x10u});
    // 0x004a274b: call 0x414360
    uint32_t t394 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t394);
    mem.w32(t394, 0x004a2750u);
    sub_00414360(ctx, mem);
    // 0x004a2750: mov byte ptr [esp + 0x1c0], bl
    uint32_t t395 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t395, recomp_detail::r8l(ctx.ebx));
    // 0x004a2757: cmp dword ptr [esp + 0x54], 0x10
    uint32_t t396 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t397 = mem.r32(t396);
    uint32_t t398 = static_cast<uint32_t>(t397 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t397, 0x00000010u, t398);
    // 0x004a275c: jb 0x4a276b
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a276b;
    goto bb_004a275e;
}
bb_004a26ff: {
    // 0x004a26ff: mov edx, dword ptr [esp + 0x40]
    uint32_t t399 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t400 = mem.r32(t399);
    ctx.edx = static_cast<uint32_t>(t400);
    // 0x004a2703: push edx
    uint32_t t401 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t401);
    mem.w32(t401, ctx.edx);
    // 0x004a2704: call 0x4e02f3
    uint32_t t402 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t402);
    mem.w32(t402, 0x004a2709u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a2709: add esp, 4
    uint32_t t403 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t403);
    ctx.esp = static_cast<uint32_t>(t403);
    goto bb_004a270c;
}
bb_004a276b: {
    // 0x004a276b: mov edi, dword ptr [0x76e6a0]
    uint32_t t404 = mem.r32(0x0076e6a0u);
    ctx.edi = static_cast<uint32_t>(t404);
    // 0x004a2771: push 0x5354e0
    uint32_t t405 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t405);
    mem.w32(t405, 0x005354e0u);
    // 0x004a2776: lea esi, [esp + 0x80]
    uint32_t t406 = static_cast<uint32_t>(ctx.esp + 0x00000080u);
    ctx.esi = static_cast<uint32_t>(t406);
    // 0x004a277d: call 0x417200
    uint32_t t407 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t407);
    mem.w32(t407, 0x004a2782u);
    sub_00417200(ctx, mem);
    // 0x004a2782: mov edx, esi
    ctx.edx = static_cast<uint32_t>(ctx.esi);
    // 0x004a2784: add esp, 4
    uint32_t t408 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t408);
    ctx.esp = static_cast<uint32_t>(t408);
    // 0x004a2787: push edx
    uint32_t t409 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t409);
    mem.w32(t409, ctx.edx);
    // 0x004a2788: push 0x53a6bc
    uint32_t t410 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t410);
    mem.w32(t410, 0x0053a6bcu);
    // 0x004a278d: lea esi, [esp + 0x44]
    uint32_t t411 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    ctx.esi = static_cast<uint32_t>(t411);
    // 0x004a2791: call 0x4c1ec0
    uint32_t t412 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t412);
    mem.w32(t412, 0x004a2796u);
    sub_004c1ec0(ctx, mem);
    // 0x004a2796: add esp, 8
    uint32_t t413 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t413);
    ctx.esp = static_cast<uint32_t>(t413);
    // 0x004a2799: push ebx
    uint32_t t414 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t414);
    mem.w32(t414, ctx.ebx);
    // 0x004a279a: push eax
    uint32_t t415 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t415);
    mem.w32(t415, ctx.eax);
    // 0x004a279b: or eax, 0xffffffff
    uint32_t t416 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t416);
    ctx.eax = static_cast<uint32_t>(t416);
    // 0x004a279e: lea esi, [esp + 0x68]
    uint32_t t417 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t417);
    // 0x004a27a2: mov byte ptr [esp + 0x1c8], 0x11
    uint32_t t418 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t418, uint8_t{0x11u});
    // 0x004a27aa: call 0x414360
    uint32_t t419 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t419);
    mem.w32(t419, 0x004a27afu);
    sub_00414360(ctx, mem);
    // 0x004a27af: mov edi, 0x10
    ctx.edi = static_cast<uint32_t>(0x00000010u);
    // 0x004a27b4: mov byte ptr [esp + 0x1c0], bl
    uint32_t t420 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t420, recomp_detail::r8l(ctx.ebx));
    // 0x004a27bb: cmp dword ptr [esp + 0x54], edi
    uint32_t t421 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t422 = mem.r32(t421);
    uint32_t t423 = static_cast<uint32_t>(t422 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t422, ctx.edi, t423);
    // 0x004a27bf: jb 0x4a27ce
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a27ce;
    goto bb_004a27c1;
}
bb_004a275e: {
    // 0x004a275e: mov ecx, dword ptr [esp + 0x40]
    uint32_t t424 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t425 = mem.r32(t424);
    ctx.ecx = static_cast<uint32_t>(t425);
    // 0x004a2762: push ecx
    uint32_t t426 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t426);
    mem.w32(t426, ctx.ecx);
    // 0x004a2763: call 0x4e02f3
    uint32_t t427 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t427);
    mem.w32(t427, 0x004a2768u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a2768: add esp, 4
    uint32_t t428 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t428);
    ctx.esp = static_cast<uint32_t>(t428);
    goto bb_004a276b;
}
bb_004a27ce: {
    // 0x004a27ce: push 2
    uint32_t t429 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t429);
    mem.w32(t429, 0x00000002u);
    // 0x004a27d0: push 0x538d44
    uint32_t t430 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t430);
    mem.w32(t430, 0x00538d44u);
    // 0x004a27d5: lea eax, [esp + 0x68]
    uint32_t t431 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.eax = static_cast<uint32_t>(t431);
    // 0x004a27d9: call 0x414660
    uint32_t t432 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t432);
    mem.w32(t432, 0x004a27deu);
    sub_00414660(ctx, mem);
    // 0x004a27de: push 0x7b4bbe
    uint32_t t433 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t433);
    mem.w32(t433, 0x007b4bbeu);
    // 0x004a27e3: lea esi, [esp + 0x40]
    uint32_t t434 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    ctx.esi = static_cast<uint32_t>(t434);
    // 0x004a27e7: call 0x4c1ec0
    uint32_t t435 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t435);
    mem.w32(t435, 0x004a27ecu);
    sub_004c1ec0(ctx, mem);
    // 0x004a27ec: add esp, 4
    uint32_t t436 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t436);
    ctx.esp = static_cast<uint32_t>(t436);
    // 0x004a27ef: push ebx
    uint32_t t437 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t437);
    mem.w32(t437, ctx.ebx);
    // 0x004a27f0: push eax
    uint32_t t438 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t438);
    mem.w32(t438, ctx.eax);
    // 0x004a27f1: or eax, 0xffffffff
    uint32_t t439 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t439);
    ctx.eax = static_cast<uint32_t>(t439);
    // 0x004a27f4: lea esi, [esp + 0x68]
    uint32_t t440 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t440);
    // 0x004a27f8: mov byte ptr [esp + 0x1c8], 0x12
    uint32_t t441 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t441, uint8_t{0x12u});
    // 0x004a2800: call 0x414360
    uint32_t t442 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t442);
    mem.w32(t442, 0x004a2805u);
    sub_00414360(ctx, mem);
    // 0x004a2805: mov byte ptr [esp + 0x1c0], bl
    uint32_t t443 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t443, recomp_detail::r8l(ctx.ebx));
    // 0x004a280c: cmp dword ptr [esp + 0x54], edi
    uint32_t t444 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t445 = mem.r32(t444);
    uint32_t t446 = static_cast<uint32_t>(t445 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t445, ctx.edi, t446);
    // 0x004a2810: jb 0x4a281f
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a281f;
    goto bb_004a2812;
}
bb_004a27c1: {
    // 0x004a27c1: mov eax, dword ptr [esp + 0x40]
    uint32_t t447 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t448 = mem.r32(t447);
    ctx.eax = static_cast<uint32_t>(t448);
    // 0x004a27c5: push eax
    uint32_t t449 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t449);
    mem.w32(t449, ctx.eax);
    // 0x004a27c6: call 0x4e02f3
    uint32_t t450 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t450);
    mem.w32(t450, 0x004a27cbu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a27cb: add esp, 4
    uint32_t t451 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t451);
    ctx.esp = static_cast<uint32_t>(t451);
    goto bb_004a27ce;
}
bb_004a281f: {
    // 0x004a281f: mov edi, dword ptr [esp + 0x5c]
    uint32_t t452 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    uint32_t t453 = mem.r32(t452);
    ctx.edi = static_cast<uint32_t>(t453);
    // 0x004a2823: mov eax, dword ptr [edi + 8]
    uint32_t t454 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t455 = mem.r32(t454);
    ctx.eax = static_cast<uint32_t>(t455);
    // 0x004a2826: mov ecx, dword ptr [eax + 0xc4]
    uint32_t t456 = static_cast<uint32_t>(ctx.eax + 0x000000c4u);
    uint32_t t457 = mem.r32(t456);
    ctx.ecx = static_cast<uint32_t>(t457);
    // 0x004a282c: mov edx, dword ptr [eax + 0xcc]
    uint32_t t458 = static_cast<uint32_t>(ctx.eax + 0x000000ccu);
    uint32_t t459 = mem.r32(t458);
    ctx.edx = static_cast<uint32_t>(t459);
    // 0x004a2832: movzx eax, cl
    uint32_t t460 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    ctx.eax = static_cast<uint32_t>(t460);
    // 0x004a2835: movzx ecx, ch
    uint32_t t461 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8h(ctx.ecx)));
    ctx.ecx = static_cast<uint32_t>(t461);
    // 0x004a2838: push eax
    uint32_t t462 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t462);
    mem.w32(t462, ctx.eax);
    // 0x004a2839: push ecx
    uint32_t t463 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t463);
    mem.w32(t463, ctx.ecx);
    // 0x004a283a: push 0x7b4bd8
    uint32_t t464 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t464);
    mem.w32(t464, 0x007b4bd8u);
    // 0x004a283f: lea esi, [esp + 0x48]
    uint32_t t465 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    ctx.esi = static_cast<uint32_t>(t465);
    // 0x004a2843: mov dword ptr [esp + 0x64], edx
    uint32_t t466 = static_cast<uint32_t>(ctx.esp + 0x00000064u);
    mem.w32(t466, ctx.edx);
    // 0x004a2847: call 0x4c1ec0
    uint32_t t467 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t467);
    mem.w32(t467, 0x004a284cu);
    sub_004c1ec0(ctx, mem);
    // 0x004a284c: add esp, 0xc
    uint32_t t468 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t468);
    ctx.esp = static_cast<uint32_t>(t468);
    // 0x004a284f: push ebx
    uint32_t t469 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t469);
    mem.w32(t469, ctx.ebx);
    // 0x004a2850: push eax
    uint32_t t470 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t470);
    mem.w32(t470, ctx.eax);
    // 0x004a2851: or eax, 0xffffffff
    uint32_t t471 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t471);
    ctx.eax = static_cast<uint32_t>(t471);
    // 0x004a2854: lea esi, [esp + 0x68]
    uint32_t t472 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t472);
    // 0x004a2858: mov byte ptr [esp + 0x1c8], 0x13
    uint32_t t473 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t473, uint8_t{0x13u});
    // 0x004a2860: call 0x414360
    uint32_t t474 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t474);
    mem.w32(t474, 0x004a2865u);
    sub_00414360(ctx, mem);
    // 0x004a2865: mov byte ptr [esp + 0x1c0], bl
    uint32_t t475 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t475, recomp_detail::r8l(ctx.ebx));
    // 0x004a286c: cmp dword ptr [esp + 0x54], 0x10
    uint32_t t476 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t477 = mem.r32(t476);
    uint32_t t478 = static_cast<uint32_t>(t477 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t477, 0x00000010u, t478);
    // 0x004a2871: jb 0x4a2880
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a2880;
    goto bb_004a2873;
}
bb_004a2812: {
    // 0x004a2812: mov ecx, dword ptr [esp + 0x40]
    uint32_t t479 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t480 = mem.r32(t479);
    ctx.ecx = static_cast<uint32_t>(t480);
    // 0x004a2816: push ecx
    uint32_t t481 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t481);
    mem.w32(t481, ctx.ecx);
    // 0x004a2817: call 0x4e02f3
    uint32_t t482 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t482);
    mem.w32(t482, 0x004a281cu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a281c: add esp, 4
    uint32_t t483 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t483);
    ctx.esp = static_cast<uint32_t>(t483);
    goto bb_004a281f;
}
bb_004a2880: {
    // 0x004a2880: mov eax, dword ptr [esp + 0x58]
    uint32_t t484 = static_cast<uint32_t>(ctx.esp + 0x00000058u);
    uint32_t t485 = mem.r32(t484);
    ctx.eax = static_cast<uint32_t>(t485);
    // 0x004a2884: movzx ecx, al
    uint32_t t486 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.eax)));
    ctx.ecx = static_cast<uint32_t>(t486);
    // 0x004a2887: movzx edx, ah
    uint32_t t487 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8h(ctx.eax)));
    ctx.edx = static_cast<uint32_t>(t487);
    // 0x004a288a: push ecx
    uint32_t t488 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t488);
    mem.w32(t488, ctx.ecx);
    // 0x004a288b: push edx
    uint32_t t489 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t489);
    mem.w32(t489, ctx.edx);
    // 0x004a288c: push 0x7b4bee
    uint32_t t490 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t490);
    mem.w32(t490, 0x007b4beeu);
    // 0x004a2891: lea esi, [esp + 0x48]
    uint32_t t491 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    ctx.esi = static_cast<uint32_t>(t491);
    // 0x004a2895: call 0x4c1ec0
    uint32_t t492 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t492);
    mem.w32(t492, 0x004a289au);
    sub_004c1ec0(ctx, mem);
    // 0x004a289a: add esp, 0xc
    uint32_t t493 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t493);
    ctx.esp = static_cast<uint32_t>(t493);
    // 0x004a289d: push ebx
    uint32_t t494 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t494);
    mem.w32(t494, ctx.ebx);
    // 0x004a289e: push eax
    uint32_t t495 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t495);
    mem.w32(t495, ctx.eax);
    // 0x004a289f: or eax, 0xffffffff
    uint32_t t496 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t496);
    ctx.eax = static_cast<uint32_t>(t496);
    // 0x004a28a2: lea esi, [esp + 0x68]
    uint32_t t497 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t497);
    // 0x004a28a6: mov byte ptr [esp + 0x1c8], 0x14
    uint32_t t498 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t498, uint8_t{0x14u});
    // 0x004a28ae: call 0x414360
    uint32_t t499 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t499);
    mem.w32(t499, 0x004a28b3u);
    sub_00414360(ctx, mem);
    // 0x004a28b3: mov byte ptr [esp + 0x1c0], bl
    uint32_t t500 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t500, recomp_detail::r8l(ctx.ebx));
    // 0x004a28ba: cmp dword ptr [esp + 0x54], 0x10
    uint32_t t501 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t502 = mem.r32(t501);
    uint32_t t503 = static_cast<uint32_t>(t502 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t502, 0x00000010u, t503);
    // 0x004a28bf: jb 0x4a28ce
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a28ce;
    goto bb_004a28c1;
}
bb_004a2873: {
    // 0x004a2873: mov edx, dword ptr [esp + 0x40]
    uint32_t t504 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t505 = mem.r32(t504);
    ctx.edx = static_cast<uint32_t>(t505);
    // 0x004a2877: push edx
    uint32_t t506 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t506);
    mem.w32(t506, ctx.edx);
    // 0x004a2878: call 0x4e02f3
    uint32_t t507 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t507);
    mem.w32(t507, 0x004a287du);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a287d: add esp, 4
    uint32_t t508 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t508);
    ctx.esp = static_cast<uint32_t>(t508);
    goto bb_004a2880;
}
bb_004a28ce: {
    // 0x004a28ce: mov eax, dword ptr [edi + 8]
    uint32_t t509 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t510 = mem.r32(t509);
    ctx.eax = static_cast<uint32_t>(t510);
    // 0x004a28d1: mov ecx, dword ptr [eax + 0x5c]
    uint32_t t511 = static_cast<uint32_t>(ctx.eax + 0x0000005cu);
    uint32_t t512 = mem.r32(t511);
    ctx.ecx = static_cast<uint32_t>(t512);
    // 0x004a28d4: mov edx, dword ptr [eax + 0x58]
    uint32_t t513 = static_cast<uint32_t>(ctx.eax + 0x00000058u);
    uint32_t t514 = mem.r32(t513);
    ctx.edx = static_cast<uint32_t>(t514);
    // 0x004a28d7: push ecx
    uint32_t t515 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t515);
    mem.w32(t515, ctx.ecx);
    // 0x004a28d8: push edx
    uint32_t t516 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t516);
    mem.w32(t516, ctx.edx);
    // 0x004a28d9: push 0x7b4c03
    uint32_t t517 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t517);
    mem.w32(t517, 0x007b4c03u);
    // 0x004a28de: lea esi, [esp + 0x48]
    uint32_t t518 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    ctx.esi = static_cast<uint32_t>(t518);
    // 0x004a28e2: call 0x4c1ec0
    uint32_t t519 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t519);
    mem.w32(t519, 0x004a28e7u);
    sub_004c1ec0(ctx, mem);
    // 0x004a28e7: add esp, 0xc
    uint32_t t520 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t520);
    ctx.esp = static_cast<uint32_t>(t520);
    // 0x004a28ea: push ebx
    uint32_t t521 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t521);
    mem.w32(t521, ctx.ebx);
    // 0x004a28eb: push eax
    uint32_t t522 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t522);
    mem.w32(t522, ctx.eax);
    // 0x004a28ec: or eax, 0xffffffff
    uint32_t t523 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t523);
    ctx.eax = static_cast<uint32_t>(t523);
    // 0x004a28ef: lea esi, [esp + 0x68]
    uint32_t t524 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t524);
    // 0x004a28f3: mov byte ptr [esp + 0x1c8], 0x15
    uint32_t t525 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t525, uint8_t{0x15u});
    // 0x004a28fb: call 0x414360
    uint32_t t526 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t526);
    mem.w32(t526, 0x004a2900u);
    sub_00414360(ctx, mem);
    // 0x004a2900: mov byte ptr [esp + 0x1c0], bl
    uint32_t t527 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t527, recomp_detail::r8l(ctx.ebx));
    // 0x004a2907: cmp dword ptr [esp + 0x54], 0x10
    uint32_t t528 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t529 = mem.r32(t528);
    uint32_t t530 = static_cast<uint32_t>(t529 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t529, 0x00000010u, t530);
    // 0x004a290c: jb 0x4a291b
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a291b;
    goto bb_004a290e;
}
bb_004a28c1: {
    // 0x004a28c1: mov eax, dword ptr [esp + 0x40]
    uint32_t t531 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t532 = mem.r32(t531);
    ctx.eax = static_cast<uint32_t>(t532);
    // 0x004a28c5: push eax
    uint32_t t533 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t533);
    mem.w32(t533, ctx.eax);
    // 0x004a28c6: call 0x4e02f3
    uint32_t t534 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t534);
    mem.w32(t534, 0x004a28cbu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a28cb: add esp, 4
    uint32_t t535 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t535);
    ctx.esp = static_cast<uint32_t>(t535);
    goto bb_004a28ce;
}
bb_004a291b: {
    // 0x004a291b: mov ecx, dword ptr [edi + 8]
    uint32_t t536 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t537 = mem.r32(t536);
    ctx.ecx = static_cast<uint32_t>(t537);
    // 0x004a291e: mov edx, dword ptr [ecx + 0x94]
    uint32_t t538 = static_cast<uint32_t>(ctx.ecx + 0x00000094u);
    uint32_t t539 = mem.r32(t538);
    ctx.edx = static_cast<uint32_t>(t539);
    // 0x004a2924: push edx
    uint32_t t540 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t540);
    mem.w32(t540, ctx.edx);
    // 0x004a2925: push 0x7b4c21
    uint32_t t541 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t541);
    mem.w32(t541, 0x007b4c21u);
    // 0x004a292a: lea esi, [esp + 0x44]
    uint32_t t542 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    ctx.esi = static_cast<uint32_t>(t542);
    // 0x004a292e: call 0x4c1ec0
    uint32_t t543 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t543);
    mem.w32(t543, 0x004a2933u);
    sub_004c1ec0(ctx, mem);
    // 0x004a2933: add esp, 8
    uint32_t t544 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t544);
    ctx.esp = static_cast<uint32_t>(t544);
    // 0x004a2936: push ebx
    uint32_t t545 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t545);
    mem.w32(t545, ctx.ebx);
    // 0x004a2937: push eax
    uint32_t t546 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t546);
    mem.w32(t546, ctx.eax);
    // 0x004a2938: or eax, 0xffffffff
    uint32_t t547 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t547);
    ctx.eax = static_cast<uint32_t>(t547);
    // 0x004a293b: lea esi, [esp + 0x68]
    uint32_t t548 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t548);
    // 0x004a293f: mov byte ptr [esp + 0x1c8], 0x16
    uint32_t t549 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t549, uint8_t{0x16u});
    // 0x004a2947: call 0x414360
    uint32_t t550 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t550);
    mem.w32(t550, 0x004a294cu);
    sub_00414360(ctx, mem);
    // 0x004a294c: mov byte ptr [esp + 0x1c0], bl
    uint32_t t551 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t551, recomp_detail::r8l(ctx.ebx));
    // 0x004a2953: cmp dword ptr [esp + 0x54], 0x10
    uint32_t t552 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t553 = mem.r32(t552);
    uint32_t t554 = static_cast<uint32_t>(t553 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t553, 0x00000010u, t554);
    // 0x004a2958: jb 0x4a2967
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a2967;
    goto bb_004a295a;
}
bb_004a290e: {
    // 0x004a290e: mov eax, dword ptr [esp + 0x40]
    uint32_t t555 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t556 = mem.r32(t555);
    ctx.eax = static_cast<uint32_t>(t556);
    // 0x004a2912: push eax
    uint32_t t557 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t557);
    mem.w32(t557, ctx.eax);
    // 0x004a2913: call 0x4e02f3
    uint32_t t558 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t558);
    mem.w32(t558, 0x004a2918u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a2918: add esp, 4
    uint32_t t559 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t559);
    ctx.esp = static_cast<uint32_t>(t559);
    goto bb_004a291b;
}
bb_004a2967: {
    // 0x004a2967: mov ecx, dword ptr [edi + 8]
    uint32_t t560 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t561 = mem.r32(t560);
    ctx.ecx = static_cast<uint32_t>(t561);
    // 0x004a296a: fld dword ptr [ecx + 0xb0]
    uint32_t t562 = static_cast<uint32_t>(ctx.ecx + 0x000000b0u);
    double t563 = static_cast<double>(mem.rf32(t562));
    ctx.fpu_push(t563);
    // 0x004a2970: sub esp, 8
    uint32_t t564 = static_cast<uint32_t>(ctx.esp - 0x00000008u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000008u, t564);
    ctx.esp = static_cast<uint32_t>(t564);
    // 0x004a2973: fstp qword ptr [esp]
    double t565 = ctx.fpu_st(0);
    mem.wf64(ctx.esp, t565);
    ctx.fpu_pop();
    // 0x004a2976: push 0x7b4c44
    uint32_t t566 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t566);
    mem.w32(t566, 0x007b4c44u);
    // 0x004a297b: lea esi, [esp + 0x48]
    uint32_t t567 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    ctx.esi = static_cast<uint32_t>(t567);
    // 0x004a297f: call 0x4c1ec0
    uint32_t t568 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t568);
    mem.w32(t568, 0x004a2984u);
    sub_004c1ec0(ctx, mem);
    // 0x004a2984: add esp, 0xc
    uint32_t t569 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t569);
    ctx.esp = static_cast<uint32_t>(t569);
    // 0x004a2987: push ebx
    uint32_t t570 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t570);
    mem.w32(t570, ctx.ebx);
    // 0x004a2988: push eax
    uint32_t t571 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t571);
    mem.w32(t571, ctx.eax);
    // 0x004a2989: or eax, 0xffffffff
    uint32_t t572 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t572);
    ctx.eax = static_cast<uint32_t>(t572);
    // 0x004a298c: lea esi, [esp + 0x68]
    uint32_t t573 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t573);
    // 0x004a2990: mov byte ptr [esp + 0x1c8], 0x17
    uint32_t t574 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t574, uint8_t{0x17u});
    // 0x004a2998: call 0x414360
    uint32_t t575 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t575);
    mem.w32(t575, 0x004a299du);
    sub_00414360(ctx, mem);
    // 0x004a299d: mov byte ptr [esp + 0x1c0], bl
    uint32_t t576 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t576, recomp_detail::r8l(ctx.ebx));
    // 0x004a29a4: cmp dword ptr [esp + 0x54], 0x10
    uint32_t t577 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t578 = mem.r32(t577);
    uint32_t t579 = static_cast<uint32_t>(t578 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t578, 0x00000010u, t579);
    // 0x004a29a9: jb 0x4a29b8
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a29b8;
    goto bb_004a29ab;
}
bb_004a295a: {
    // 0x004a295a: mov eax, dword ptr [esp + 0x40]
    uint32_t t580 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t581 = mem.r32(t580);
    ctx.eax = static_cast<uint32_t>(t581);
    // 0x004a295e: push eax
    uint32_t t582 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t582);
    mem.w32(t582, ctx.eax);
    // 0x004a295f: call 0x4e02f3
    uint32_t t583 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t583);
    mem.w32(t583, 0x004a2964u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a2964: add esp, 4
    uint32_t t584 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t584);
    ctx.esp = static_cast<uint32_t>(t584);
    goto bb_004a2967;
}
bb_004a29b8: {
    // 0x004a29b8: mov eax, dword ptr [edi + 8]
    uint32_t t585 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t586 = mem.r32(t585);
    ctx.eax = static_cast<uint32_t>(t586);
    // 0x004a29bb: mov ecx, dword ptr [eax + 0xb4]
    uint32_t t587 = static_cast<uint32_t>(ctx.eax + 0x000000b4u);
    uint32_t t588 = mem.r32(t587);
    ctx.ecx = static_cast<uint32_t>(t588);
    // 0x004a29c1: push ecx
    uint32_t t589 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t589);
    mem.w32(t589, ctx.ecx);
    // 0x004a29c2: push 0x7b4c5d
    uint32_t t590 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t590);
    mem.w32(t590, 0x007b4c5du);
    // 0x004a29c7: lea esi, [esp + 0x44]
    uint32_t t591 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    ctx.esi = static_cast<uint32_t>(t591);
    // 0x004a29cb: call 0x4c1ec0
    uint32_t t592 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t592);
    mem.w32(t592, 0x004a29d0u);
    sub_004c1ec0(ctx, mem);
    // 0x004a29d0: add esp, 8
    uint32_t t593 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t593);
    ctx.esp = static_cast<uint32_t>(t593);
    // 0x004a29d3: push ebx
    uint32_t t594 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t594);
    mem.w32(t594, ctx.ebx);
    // 0x004a29d4: push eax
    uint32_t t595 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t595);
    mem.w32(t595, ctx.eax);
    // 0x004a29d5: or eax, 0xffffffff
    uint32_t t596 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t596);
    ctx.eax = static_cast<uint32_t>(t596);
    // 0x004a29d8: lea esi, [esp + 0x68]
    uint32_t t597 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.esi = static_cast<uint32_t>(t597);
    // 0x004a29dc: mov byte ptr [esp + 0x1c8], 0x18
    uint32_t t598 = static_cast<uint32_t>(ctx.esp + 0x000001c8u);
    mem.w8(t598, uint8_t{0x18u});
    // 0x004a29e4: call 0x414360
    uint32_t t599 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t599);
    mem.w32(t599, 0x004a29e9u);
    sub_00414360(ctx, mem);
    // 0x004a29e9: mov edi, 0x10
    ctx.edi = static_cast<uint32_t>(0x00000010u);
    // 0x004a29ee: mov byte ptr [esp + 0x1c0], bl
    uint32_t t600 = static_cast<uint32_t>(ctx.esp + 0x000001c0u);
    mem.w8(t600, recomp_detail::r8l(ctx.ebx));
    // 0x004a29f5: cmp dword ptr [esp + 0x54], edi
    uint32_t t601 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    uint32_t t602 = mem.r32(t601);
    uint32_t t603 = static_cast<uint32_t>(t602 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t602, ctx.edi, t603);
    // 0x004a29f9: jb 0x4a2a08
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a2a08;
    goto bb_004a29fb;
}
bb_004a29ab: {
    // 0x004a29ab: mov edx, dword ptr [esp + 0x40]
    uint32_t t604 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t605 = mem.r32(t604);
    ctx.edx = static_cast<uint32_t>(t605);
    // 0x004a29af: push edx
    uint32_t t606 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t606);
    mem.w32(t606, ctx.edx);
    // 0x004a29b0: call 0x4e02f3
    uint32_t t607 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t607);
    mem.w32(t607, 0x004a29b5u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a29b5: add esp, 4
    uint32_t t608 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t608);
    ctx.esp = static_cast<uint32_t>(t608);
    goto bb_004a29b8;
}
bb_004a2a08: {
    // 0x004a2a08: push 2
    uint32_t t609 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t609);
    mem.w32(t609, 0x00000002u);
    // 0x004a2a0a: push 0x538d44
    uint32_t t610 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t610);
    mem.w32(t610, 0x00538d44u);
    // 0x004a2a0f: lea eax, [esp + 0x68]
    uint32_t t611 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    ctx.eax = static_cast<uint32_t>(t611);
    // 0x004a2a13: call 0x414660
    uint32_t t612 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t612);
    mem.w32(t612, 0x004a2a18u);
    sub_00414660(ctx, mem);
    // 0x004a2a18: mov eax, dword ptr [0x767448]
    uint32_t t613 = mem.r32(0x00767448u);
    ctx.eax = static_cast<uint32_t>(t613);
    // 0x004a2a1d: cmp eax, ebx
    uint32_t t614 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t614);
    // 0x004a2a1f: jne 0x4a2a25
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a2a25;
    goto bb_004a2a21;
}
bb_004a29fb: {
    // 0x004a29fb: mov edx, dword ptr [esp + 0x40]
    uint32_t t615 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    uint32_t t616 = mem.r32(t615);
    ctx.edx = static_cast<uint32_t>(t616);
    // 0x004a29ff: push edx
    uint32_t t617 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t617);
    mem.w32(t617, ctx.edx);
    // 0x004a2a00: call 0x4e02f3
    uint32_t t618 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t618);
    mem.w32(t618, 0x004a2a05u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a2a05: add esp, 4
    uint32_t t619 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t619);
    ctx.esp = static_cast<uint32_t>(t619);
    goto bb_004a2a08;
}
bb_004a2a25: {
    // 0x004a2a25: mov ecx, dword ptr [eax]
    uint32_t t620 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t620);
    // 0x004a2a27: mov eax, dword ptr [eax + 0x20]
    uint32_t t621 = static_cast<uint32_t>(ctx.eax + 0x00000020u);
    uint32_t t622 = mem.r32(t621);
    ctx.eax = static_cast<uint32_t>(t622);
    // 0x004a2a2a: mov edx, dword ptr [ecx]
    uint32_t t623 = mem.r32(ctx.ecx);
    ctx.edx = static_cast<uint32_t>(t623);
    // 0x004a2a2c: lea esi, [esp + 0x3c]
    uint32_t t624 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    ctx.esi = static_cast<uint32_t>(t624);
    // 0x004a2a30: push esi
    uint32_t t625 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t625);
    mem.w32(t625, ctx.esi);
    // 0x004a2a31: push eax
    uint32_t t626 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t626);
    mem.w32(t626, ctx.eax);
    // 0x004a2a32: push ecx
    uint32_t t627 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t627);
    mem.w32(t627, ctx.ecx);
    // 0x004a2a33: mov ecx, dword ptr [edx + 0x20]
    uint32_t t628 = static_cast<uint32_t>(ctx.edx + 0x00000020u);
    uint32_t t629 = mem.r32(t628);
    ctx.ecx = static_cast<uint32_t>(t629);
    // 0x004a2a36: call ecx
    uint32_t t630 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t630);
    mem.w32(t630, 0x004a2a38u);
    call_indirect(ctx, mem, ctx.ecx);
    // 0x004a2a38: neg eax
    uint32_t t631 = static_cast<uint32_t>(0u - ctx.eax);
    recomp_detail::update_flags_neg<uint32_t>(ctx, ctx.eax, t631);
    ctx.eax = static_cast<uint32_t>(t631);
    // 0x004a2a3a: sbb eax, eax
    uint32_t t632 = recomp_detail::get_flag(ctx, kFlagCF);
    uint32_t t633 = static_cast<uint32_t>(ctx.eax - ctx.eax);
    uint32_t t634 = static_cast<uint32_t>(t633 - t632);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.eax, t634, t632);
    ctx.eax = static_cast<uint32_t>(t634);
    // 0x004a2a3c: not eax
    uint32_t t635 = static_cast<uint32_t>(~ctx.eax);
    ctx.eax = static_cast<uint32_t>(t635);
    // 0x004a2a3e: and eax, dword ptr [esp + 0x48]
    uint32_t t636 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    uint32_t t637 = mem.r32(t636);
    uint32_t t638 = static_cast<uint32_t>(ctx.eax & t637);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t638);
    ctx.eax = static_cast<uint32_t>(t638);
    goto bb_004a2a42;
}
bb_004a2a21: {
    // 0x004a2a21: xor eax, eax
    uint32_t t639 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t639);
    ctx.eax = static_cast<uint32_t>(t639);
    // 0x004a2a23: jmp 0x4a2a42
}
bb_004a2a42: {
    // 0x004a2a42: lea edx, [esp + 0x60]
    uint32_t t640 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    ctx.edx = static_cast<uint32_t>(t640);
    // 0x004a2a46: push edx
    uint32_t t641 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t641);
    mem.w32(t641, ctx.edx);
    // 0x004a2a47: push eax
    uint32_t t642 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t642);
    mem.w32(t642, ctx.eax);
    // 0x004a2a48: call 0x4a2b30
    uint32_t t643 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t643);
    mem.w32(t643, 0x004a2a4du);
    sub_004a2b30(ctx, mem);
    // 0x004a2a4d: add esp, 8
    uint32_t t644 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t644);
    ctx.esp = static_cast<uint32_t>(t644);
    // 0x004a2a50: cmp dword ptr [esp + 0x74], ebx
    uint32_t t645 = static_cast<uint32_t>(ctx.esp + 0x00000074u);
    uint32_t t646 = mem.r32(t645);
    uint32_t t647 = static_cast<uint32_t>(t646 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t646, ctx.ebx, t647);
    // 0x004a2a54: je 0x4a2aee
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a2aee;
    goto bb_004a2a5a;
}
bb_004a2aee: {
    // 0x004a2aee: call 0x417170
    uint32_t t648 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t648);
    mem.w32(t648, 0x004a2af3u);
    sub_00417170(ctx, mem);
    // 0x004a2af3: cmp dword ptr [esp + 0x78], edi
    uint32_t t649 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    uint32_t t650 = mem.r32(t649);
    uint32_t t651 = static_cast<uint32_t>(t650 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t650, ctx.edi, t651);
    // 0x004a2af7: jb 0x4a2b06
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a2b06;
    goto bb_004a2af9;
}
bb_004a2a5a: {
    // 0x004a2a5a: push 0x1d3
    uint32_t t652 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t652);
    mem.w32(t652, 0x000001d3u);
    // 0x004a2a5f: push 0x53a804
    uint32_t t653 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t653);
    mem.w32(t653, 0x0053a804u);
    // 0x004a2a64: push 4
    uint32_t t654 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t654);
    mem.w32(t654, 0x00000004u);
    // 0x004a2a66: push 0x5c
    uint32_t t655 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t655);
    mem.w32(t655, 0x0000005cu);
    // 0x004a2a68: call 0x4e0675
    uint32_t t656 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t656);
    mem.w32(t656, 0x004a2a6du);
    hle_crt_004e0675(ctx, mem);
    // 0x004a2a6d: add esp, 0x10
    uint32_t t657 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t657);
    ctx.esp = static_cast<uint32_t>(t657);
    // 0x004a2a70: cmp eax, ebx
    uint32_t t658 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t658);
    // 0x004a2a72: je 0x4a2a7f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a2a7f;
    goto bb_004a2a74;
}
bb_004a2b06: {
    // 0x004a2b06: mov ecx, dword ptr [esp + 0x1b8]
    uint32_t t659 = static_cast<uint32_t>(ctx.esp + 0x000001b8u);
    uint32_t t660 = mem.r32(t659);
    ctx.ecx = static_cast<uint32_t>(t660);
    // 0x004a2b0d: mov dword ptr fs:[0], ecx
    uint32_t t661 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t661, ctx.ecx);
    // 0x004a2b14: pop ecx
    uint32_t t662 = ctx.esp;
    uint32_t t663 = mem.r32(t662);
    uint32_t t664 = static_cast<uint32_t>(t662 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t664);
    ctx.ecx = static_cast<uint32_t>(t663);
    // 0x004a2b15: pop edi
    uint32_t t665 = ctx.esp;
    uint32_t t666 = mem.r32(t665);
    uint32_t t667 = static_cast<uint32_t>(t665 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t667);
    ctx.edi = static_cast<uint32_t>(t666);
    // 0x004a2b16: pop esi
    uint32_t t668 = ctx.esp;
    uint32_t t669 = mem.r32(t668);
    uint32_t t670 = static_cast<uint32_t>(t668 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t670);
    ctx.esi = static_cast<uint32_t>(t669);
    // 0x004a2b17: pop ebx
    uint32_t t671 = ctx.esp;
    uint32_t t672 = mem.r32(t671);
    uint32_t t673 = static_cast<uint32_t>(t671 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t673);
    ctx.ebx = static_cast<uint32_t>(t672);
    // 0x004a2b18: mov ecx, dword ptr [esp + 0x170]
    uint32_t t674 = static_cast<uint32_t>(ctx.esp + 0x00000170u);
    uint32_t t675 = mem.r32(t674);
    ctx.ecx = static_cast<uint32_t>(t675);
    // 0x004a2b1f: xor ecx, esp
    uint32_t t676 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t676);
    ctx.ecx = static_cast<uint32_t>(t676);
    // 0x004a2b21: call 0x4e02f8
    uint32_t t677 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t677);
    mem.w32(t677, 0x004a2b26u);
    hle_crt_004e02f8(ctx, mem);
    // 0x004a2b26: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x004a2b28: pop ebp
    uint32_t t678 = ctx.esp;
    uint32_t t679 = mem.r32(t678);
    uint32_t t680 = static_cast<uint32_t>(t678 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t680);
    ctx.ebp = static_cast<uint32_t>(t679);
    // 0x004a2b29: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a2af9: {
    // 0x004a2af9: mov eax, dword ptr [esp + 0x64]
    uint32_t t681 = static_cast<uint32_t>(ctx.esp + 0x00000064u);
    uint32_t t682 = mem.r32(t681);
    ctx.eax = static_cast<uint32_t>(t682);
    // 0x004a2afd: push eax
    uint32_t t683 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t683);
    mem.w32(t683, ctx.eax);
    // 0x004a2afe: call 0x4e02f3
    uint32_t t684 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t684);
    mem.w32(t684, 0x004a2b03u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a2b03: add esp, 4
    uint32_t t685 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t685);
    ctx.esp = static_cast<uint32_t>(t685);
    goto bb_004a2b06;
}
bb_004a2a7f: {
    // 0x004a2a7f: xor esi, esi
    uint32_t t686 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t686);
    ctx.esi = static_cast<uint32_t>(t686);
    goto bb_004a2a81;
}
bb_004a2a74: {
    // 0x004a2a74: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004a2a76: call 0x413c60
    uint32_t t687 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t687);
    mem.w32(t687, 0x004a2a7bu);
    sub_00413c60(ctx, mem);
    // 0x004a2a7b: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004a2a7d: jmp 0x4a2a81
}
bb_004a2a81: {
    // 0x004a2a81: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a2a83: call 0x414000
    uint32_t t688 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t688);
    mem.w32(t688, 0x004a2a88u);
    sub_00414000(ctx, mem);
    // 0x004a2a88: push ebx
    uint32_t t689 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t689);
    mem.w32(t689, ctx.ebx);
    // 0x004a2a89: push 0x80
    uint32_t t690 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t690);
    mem.w32(t690, 0x00000080u);
    // 0x004a2a8e: push 2
    uint32_t t691 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t691);
    mem.w32(t691, 0x00000002u);
    // 0x004a2a90: push ebx
    uint32_t t692 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t692);
    mem.w32(t692, ctx.ebx);
    // 0x004a2a91: push 2
    uint32_t t693 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t693);
    mem.w32(t693, 0x00000002u);
    // 0x004a2a93: push 0x40000000
    uint32_t t694 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t694);
    mem.w32(t694, 0x40000000u);
    // 0x004a2a98: push 0x53a824
    uint32_t t695 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t695);
    mem.w32(t695, 0x0053a824u);
    // 0x004a2a9d: call dword ptr [0x51b054]
    uint32_t t696 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t696);
    mem.w32(t696, 0x004a2aa3u);
    hle_iat_call(ctx, mem, 0x0051b054u);
    // 0x004a2aa3: cmp eax, -1
    uint32_t t697 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t697);
    // 0x004a2aa6: je 0x4a2ada
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a2ada;
    goto bb_004a2aa8;
}
bb_004a2ada: {
    // 0x004a2ada: cmp esi, ebx
    uint32_t t698 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t698);
    // 0x004a2adc: je 0x4a2aee
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a2aee;
    goto bb_004a2ade;
}
bb_004a2aa8: {
    // 0x004a2aa8: mov dword ptr [esi], eax
    mem.w32(ctx.esi, ctx.eax);
    // 0x004a2aaa: mov dword ptr [esi + 0x1c], 1
    uint32_t t699 = static_cast<uint32_t>(ctx.esi + 0x0000001cu);
    mem.w32(t699, 0x00000001u);
    // 0x004a2ab1: cmp dword ptr [esp + 0x78], edi
    uint32_t t700 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    uint32_t t701 = mem.r32(t700);
    uint32_t t702 = static_cast<uint32_t>(t701 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t701, ctx.edi, t702);
    // 0x004a2ab5: mov ecx, dword ptr [esp + 0x64]
    uint32_t t703 = static_cast<uint32_t>(ctx.esp + 0x00000064u);
    uint32_t t704 = mem.r32(t703);
    ctx.ecx = static_cast<uint32_t>(t704);
    // 0x004a2ab9: jae 0x4a2abf
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004a2abf;
    goto bb_004a2abb;
}
bb_004a2ade: {
    // 0x004a2ade: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a2ae0: call 0x414000
    uint32_t t705 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t705);
    mem.w32(t705, 0x004a2ae5u);
    sub_00414000(ctx, mem);
    // 0x004a2ae5: push esi
    uint32_t t706 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t706);
    mem.w32(t706, ctx.esi);
    // 0x004a2ae6: call 0x4e02f3
    uint32_t t707 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t707);
    mem.w32(t707, 0x004a2aebu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a2aeb: add esp, 4
    uint32_t t708 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t708);
    ctx.esp = static_cast<uint32_t>(t708);
    goto bb_004a2aee;
}
bb_004a2abf: {
    // 0x004a2abf: cmp eax, ebx
    uint32_t t709 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t709);
    // 0x004a2ac1: je 0x4a2ada
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a2ada;
    goto bb_004a2ac3;
}
bb_004a2abb: {
    // 0x004a2abb: lea ecx, [esp + 0x64]
    uint32_t t710 = static_cast<uint32_t>(ctx.esp + 0x00000064u);
    ctx.ecx = static_cast<uint32_t>(t710);
    goto bb_004a2abf;
}
bb_004a2ac3: {
    // 0x004a2ac3: push ebx
    uint32_t t711 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t711);
    mem.w32(t711, ctx.ebx);
    // 0x004a2ac4: lea edx, [esp + 0x5c]
    uint32_t t712 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    ctx.edx = static_cast<uint32_t>(t712);
    // 0x004a2ac8: push edx
    uint32_t t713 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t713);
    mem.w32(t713, ctx.edx);
    // 0x004a2ac9: mov edx, dword ptr [esp + 0x7c]
    uint32_t t714 = static_cast<uint32_t>(ctx.esp + 0x0000007cu);
    uint32_t t715 = mem.r32(t714);
    ctx.edx = static_cast<uint32_t>(t715);
    // 0x004a2acd: push edx
    uint32_t t716 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t716);
    mem.w32(t716, ctx.edx);
    // 0x004a2ace: push ecx
    uint32_t t717 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t717);
    mem.w32(t717, ctx.ecx);
    // 0x004a2acf: push eax
    uint32_t t718 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t718);
    mem.w32(t718, ctx.eax);
    // 0x004a2ad0: mov dword ptr [esp + 0x6c], ebx
    uint32_t t719 = static_cast<uint32_t>(ctx.esp + 0x0000006cu);
    mem.w32(t719, ctx.ebx);
    // 0x004a2ad4: call dword ptr [0x51b0ac]
    uint32_t t720 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t720);
    mem.w32(t720, 0x004a2adau);
    hle_iat_call(ctx, mem, 0x0051b0acu);
    goto bb_004a2ada;
}
}

// sub_004a2b30 | subsystem=Core/Windows | canonical | 27 blocks | 287 insns
void sub_004a2b30(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a2b30: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x004a2b32: push 0x514c68
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00514c68u);
    // 0x004a2b37: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004a2b3d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x004a2b3e: sub esp, 0x108
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000108u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000108u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x004a2b44: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x004a2b49: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x004a2b4b: mov dword ptr [esp + 0x104], eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000104u);
    mem.w32(t8, ctx.eax);
    // 0x004a2b52: push ebx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ebx);
    // 0x004a2b53: push ebp
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.ebp);
    // 0x004a2b54: push esi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.esi);
    // 0x004a2b55: push edi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.edi);
    // 0x004a2b56: mov eax, dword ptr [0x54b458]
    uint32_t t13 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x004a2b5b: xor eax, esp
    uint32_t t14 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x004a2b5d: push eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.eax);
    // 0x004a2b5e: lea eax, [esp + 0x11c]
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x0000011cu);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x004a2b65: mov dword ptr fs:[0], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t17, ctx.eax);
    // 0x004a2b6b: mov eax, dword ptr [esp + 0x130]
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x00000130u);
    uint32_t t19 = mem.r32(t18);
    ctx.eax = static_cast<uint32_t>(t19);
    // 0x004a2b72: push 0x36
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x00000036u);
    // 0x004a2b74: xor ebx, ebx
    uint32_t t21 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t21);
    ctx.ebx = static_cast<uint32_t>(t21);
    // 0x004a2b76: push 0x53a83c
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x0053a83cu);
    // 0x004a2b7b: mov dword ptr [esp + 0x20], eax
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t23, ctx.eax);
    // 0x004a2b7f: mov dword ptr [esp + 0x24], 0x14
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t24, 0x00000014u);
    // 0x004a2b87: mov dword ptr [esp + 0x28], 0x15
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t25, 0x00000015u);
    // 0x004a2b8f: mov dword ptr [esp + 0x2c], 0x16
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    mem.w32(t26, 0x00000016u);
    // 0x004a2b97: mov dword ptr [esp + 0x30], 0x17
    uint32_t t27 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    mem.w32(t27, 0x00000017u);
    // 0x004a2b9f: mov dword ptr [esp + 0x34], 0x18
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    mem.w32(t28, 0x00000018u);
    // 0x004a2ba7: mov dword ptr [esp + 0x38], 0x19
    uint32_t t29 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    mem.w32(t29, 0x00000019u);
    // 0x004a2baf: mov dword ptr [esp + 0x3c], 0x1a
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    mem.w32(t30, 0x0000001au);
    // 0x004a2bb7: mov dword ptr [esp + 0x40], 0x1b
    uint32_t t31 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    mem.w32(t31, 0x0000001bu);
    // 0x004a2bbf: mov dword ptr [esp + 0x44], 0x1c
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    mem.w32(t32, 0x0000001cu);
    // 0x004a2bc7: mov dword ptr [esp + 0x48], 0x1d
    uint32_t t33 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    mem.w32(t33, 0x0000001du);
    // 0x004a2bcf: mov dword ptr [esp + 0x4c], 0x1e
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + 0x0000004cu);
    mem.w32(t34, 0x0000001eu);
    // 0x004a2bd7: mov dword ptr [esp + 0x50], 0x1f
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x00000050u);
    mem.w32(t35, 0x0000001fu);
    // 0x004a2bdf: mov dword ptr [esp + 0x54], 0x22
    uint32_t t36 = static_cast<uint32_t>(ctx.esp + 0x00000054u);
    mem.w32(t36, 0x00000022u);
    // 0x004a2be7: mov dword ptr [esp + 0x58], 0x28
    uint32_t t37 = static_cast<uint32_t>(ctx.esp + 0x00000058u);
    mem.w32(t37, 0x00000028u);
    // 0x004a2bef: mov dword ptr [esp + 0x5c], 0x29
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x0000005cu);
    mem.w32(t38, 0x00000029u);
    // 0x004a2bf7: mov dword ptr [esp + 0x60], 0x32
    uint32_t t39 = static_cast<uint32_t>(ctx.esp + 0x00000060u);
    mem.w32(t39, 0x00000032u);
    // 0x004a2bff: mov dword ptr [esp + 0x64], 0x51
    uint32_t t40 = static_cast<uint32_t>(ctx.esp + 0x00000064u);
    mem.w32(t40, 0x00000051u);
    // 0x004a2c07: mov dword ptr [esp + 0x68], 0x33
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + 0x00000068u);
    mem.w32(t41, 0x00000033u);
    // 0x004a2c0f: mov dword ptr [esp + 0x6c], 0x34
    uint32_t t42 = static_cast<uint32_t>(ctx.esp + 0x0000006cu);
    mem.w32(t42, 0x00000034u);
    // 0x004a2c17: mov dword ptr [esp + 0x70], 0x3c
    uint32_t t43 = static_cast<uint32_t>(ctx.esp + 0x00000070u);
    mem.w32(t43, 0x0000003cu);
    // 0x004a2c1f: mov dword ptr [esp + 0x74], 0x3f
    uint32_t t44 = static_cast<uint32_t>(ctx.esp + 0x00000074u);
    mem.w32(t44, 0x0000003fu);
    // 0x004a2c27: mov dword ptr [esp + 0x78], 0x40
    uint32_t t45 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    mem.w32(t45, 0x00000040u);
    // 0x004a2c2f: mov dword ptr [esp + 0x7c], 0x6e
    uint32_t t46 = static_cast<uint32_t>(ctx.esp + 0x0000007cu);
    mem.w32(t46, 0x0000006eu);
    // 0x004a2c37: mov dword ptr [esp + 0x80], 0x75
    uint32_t t47 = static_cast<uint32_t>(ctx.esp + 0x00000080u);
    mem.w32(t47, 0x00000075u);
    // 0x004a2c42: mov dword ptr [esp + 0x84], 0x3d
    uint32_t t48 = static_cast<uint32_t>(ctx.esp + 0x00000084u);
    mem.w32(t48, 0x0000003du);
    // 0x004a2c4d: mov dword ptr [esp + 0x88], 0x3e
    uint32_t t49 = static_cast<uint32_t>(ctx.esp + 0x00000088u);
    mem.w32(t49, 0x0000003eu);
    // 0x004a2c58: mov dword ptr [esp + 0x8c], 0x43
    uint32_t t50 = static_cast<uint32_t>(ctx.esp + 0x0000008cu);
    mem.w32(t50, 0x00000043u);
    // 0x004a2c63: mov dword ptr [esp + 0x90], 0x3154454d
    uint32_t t51 = static_cast<uint32_t>(ctx.esp + 0x00000090u);
    mem.w32(t51, 0x3154454du);
    // 0x004a2c6e: mov dword ptr [esp + 0x94], 0x42475247
    uint32_t t52 = static_cast<uint32_t>(ctx.esp + 0x00000094u);
    mem.w32(t52, 0x42475247u);
    // 0x004a2c79: mov dword ptr [esp + 0x98], 0x47424752
    uint32_t t53 = static_cast<uint32_t>(ctx.esp + 0x00000098u);
    mem.w32(t53, 0x47424752u);
    // 0x004a2c84: mov dword ptr [esp + 0x9c], 0x31545844
    uint32_t t54 = static_cast<uint32_t>(ctx.esp + 0x0000009cu);
    mem.w32(t54, 0x31545844u);
    // 0x004a2c8f: mov dword ptr [esp + 0xa0], 0x32545844
    uint32_t t55 = static_cast<uint32_t>(ctx.esp + 0x000000a0u);
    mem.w32(t55, 0x32545844u);
    // 0x004a2c9a: mov dword ptr [esp + 0xa4], 0x33545844
    uint32_t t56 = static_cast<uint32_t>(ctx.esp + 0x000000a4u);
    mem.w32(t56, 0x33545844u);
    // 0x004a2ca5: mov dword ptr [esp + 0xa8], 0x34545844
    uint32_t t57 = static_cast<uint32_t>(ctx.esp + 0x000000a8u);
    mem.w32(t57, 0x34545844u);
    // 0x004a2cb0: mov dword ptr [esp + 0xac], 0x35545844
    uint32_t t58 = static_cast<uint32_t>(ctx.esp + 0x000000acu);
    mem.w32(t58, 0x35545844u);
    // 0x004a2cbb: mov dword ptr [esp + 0xb0], 0x59565955
    uint32_t t59 = static_cast<uint32_t>(ctx.esp + 0x000000b0u);
    mem.w32(t59, 0x59565955u);
    // 0x004a2cc6: mov dword ptr [esp + 0xb4], 0x32595559
    uint32_t t60 = static_cast<uint32_t>(ctx.esp + 0x000000b4u);
    mem.w32(t60, 0x32595559u);
    // 0x004a2cd1: mov dword ptr [esp + 0xb8], 0x46
    uint32_t t61 = static_cast<uint32_t>(ctx.esp + 0x000000b8u);
    mem.w32(t61, 0x00000046u);
    // 0x004a2cdc: mov dword ptr [esp + 0xbc], 0x47
    uint32_t t62 = static_cast<uint32_t>(ctx.esp + 0x000000bcu);
    mem.w32(t62, 0x00000047u);
    // 0x004a2ce7: mov dword ptr [esp + 0xc0], 0x49
    uint32_t t63 = static_cast<uint32_t>(ctx.esp + 0x000000c0u);
    mem.w32(t63, 0x00000049u);
    // 0x004a2cf2: mov dword ptr [esp + 0xc4], 0x4b
    uint32_t t64 = static_cast<uint32_t>(ctx.esp + 0x000000c4u);
    mem.w32(t64, 0x0000004bu);
    // 0x004a2cfd: mov dword ptr [esp + 0xc8], 0x4d
    uint32_t t65 = static_cast<uint32_t>(ctx.esp + 0x000000c8u);
    mem.w32(t65, 0x0000004du);
    // 0x004a2d08: mov dword ptr [esp + 0xcc], 0x4f
    uint32_t t66 = static_cast<uint32_t>(ctx.esp + 0x000000ccu);
    mem.w32(t66, 0x0000004fu);
    // 0x004a2d13: mov dword ptr [esp + 0xd0], 0x52
    uint32_t t67 = static_cast<uint32_t>(ctx.esp + 0x000000d0u);
    mem.w32(t67, 0x00000052u);
    // 0x004a2d1e: mov dword ptr [esp + 0xd4], 0x53
    uint32_t t68 = static_cast<uint32_t>(ctx.esp + 0x000000d4u);
    mem.w32(t68, 0x00000053u);
    // 0x004a2d29: mov dword ptr [esp + 0xd8], 0x50
    uint32_t t69 = static_cast<uint32_t>(ctx.esp + 0x000000d8u);
    mem.w32(t69, 0x00000050u);
    // 0x004a2d34: mov dword ptr [esp + 0xdc], 0x64
    uint32_t t70 = static_cast<uint32_t>(ctx.esp + 0x000000dcu);
    mem.w32(t70, 0x00000064u);
    // 0x004a2d3f: mov dword ptr [esp + 0xe0], 0x65
    uint32_t t71 = static_cast<uint32_t>(ctx.esp + 0x000000e0u);
    mem.w32(t71, 0x00000065u);
    // 0x004a2d4a: mov dword ptr [esp + 0xe4], 0x66
    uint32_t t72 = static_cast<uint32_t>(ctx.esp + 0x000000e4u);
    mem.w32(t72, 0x00000066u);
    // 0x004a2d55: mov dword ptr [esp + 0xe8], 0x6f
    uint32_t t73 = static_cast<uint32_t>(ctx.esp + 0x000000e8u);
    mem.w32(t73, 0x0000006fu);
    // 0x004a2d60: mov dword ptr [esp + 0xec], 0x70
    uint32_t t74 = static_cast<uint32_t>(ctx.esp + 0x000000ecu);
    mem.w32(t74, 0x00000070u);
    // 0x004a2d6b: mov dword ptr [esp + 0xf0], 0x71
    uint32_t t75 = static_cast<uint32_t>(ctx.esp + 0x000000f0u);
    mem.w32(t75, 0x00000071u);
    // 0x004a2d76: mov dword ptr [esp + 0xf4], 0x72
    uint32_t t76 = static_cast<uint32_t>(ctx.esp + 0x000000f4u);
    mem.w32(t76, 0x00000072u);
    // 0x004a2d81: mov dword ptr [esp + 0xf8], 0x73
    uint32_t t77 = static_cast<uint32_t>(ctx.esp + 0x000000f8u);
    mem.w32(t77, 0x00000073u);
    // 0x004a2d8c: mov dword ptr [esp + 0xfc], 0x74
    uint32_t t78 = static_cast<uint32_t>(ctx.esp + 0x000000fcu);
    mem.w32(t78, 0x00000074u);
    // 0x004a2d97: mov dword ptr [esp + 0x100], ebx
    uint32_t t79 = static_cast<uint32_t>(ctx.esp + 0x00000100u);
    mem.w32(t79, ctx.ebx);
    // 0x004a2d9e: call 0x414660
    uint32_t t80 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    mem.w32(t80, 0x004a2da3u);
    sub_00414660(ctx, mem);
    // 0x004a2da3: lea eax, [esp + 0x1c]
    uint32_t t81 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.eax = static_cast<uint32_t>(t81);
    // 0x004a2da7: mov dword ptr [esp + 0x14], eax
    uint32_t t82 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t82, ctx.eax);
}
bb_004a2dab: {
    // 0x004a2dab: mov dword ptr [esp + 0x114], 0xf
    uint32_t t83 = static_cast<uint32_t>(ctx.esp + 0x00000114u);
    mem.w32(t83, 0x0000000fu);
    // 0x004a2db6: mov dword ptr [esp + 0x110], ebx
    uint32_t t84 = static_cast<uint32_t>(ctx.esp + 0x00000110u);
    mem.w32(t84, ctx.ebx);
    // 0x004a2dbd: mov byte ptr [esp + 0x100], bl
    uint32_t t85 = static_cast<uint32_t>(ctx.esp + 0x00000100u);
    mem.w8(t85, recomp_detail::r8l(ctx.ebx));
    // 0x004a2dc4: mov ecx, dword ptr [esp + 0x14]
    uint32_t t86 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t87 = mem.r32(t86);
    ctx.ecx = static_cast<uint32_t>(t87);
    // 0x004a2dc8: mov dword ptr [esp + 0x124], ebx
    uint32_t t88 = static_cast<uint32_t>(ctx.esp + 0x00000124u);
    mem.w32(t88, ctx.ebx);
    // 0x004a2dcf: mov edi, dword ptr [ecx]
    uint32_t t89 = mem.r32(ctx.ecx);
    ctx.edi = static_cast<uint32_t>(t89);
    // 0x004a2dd1: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x004a2dd3: call 0x4c0cf0
    uint32_t t90 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    mem.w32(t90, 0x004a2dd8u);
    sub_004c0cf0(ctx, mem);
    // 0x004a2dd8: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x004a2dda: lea ebp, [ecx + 1]
    uint32_t t91 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    ctx.ebp = static_cast<uint32_t>(t91);
    // 0x004a2ddd: lea ecx, [ecx]
    ctx.ecx = static_cast<uint32_t>(ctx.ecx);
}
bb_004a2de0: {
    // 0x004a2de0: mov dl, byte ptr [ecx]
    uint8_t t92 = mem.r8(ctx.ecx);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t92));
    // 0x004a2de2: add ecx, 1
    uint32_t t93 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t93);
    ctx.ecx = static_cast<uint32_t>(t93);
    // 0x004a2de5: cmp dl, bl
    uint8_t t94 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)) - static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.edx), recomp_detail::r8l(ctx.ebx), t94);
    // 0x004a2de7: jne 0x4a2de0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a2de0;
}
{
    // 0x004a2de9: sub ecx, ebp
    uint32_t t95 = static_cast<uint32_t>(ctx.ecx - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebp, t95);
    ctx.ecx = static_cast<uint32_t>(t95);
    // 0x004a2deb: push ecx
    uint32_t t96 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    mem.w32(t96, ctx.ecx);
    // 0x004a2dec: push eax
    uint32_t t97 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t97);
    mem.w32(t97, ctx.eax);
    // 0x004a2ded: lea eax, [esp + 0x104]
    uint32_t t98 = static_cast<uint32_t>(ctx.esp + 0x00000104u);
    ctx.eax = static_cast<uint32_t>(t98);
    // 0x004a2df4: call 0x414660
    uint32_t t99 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t99);
    mem.w32(t99, 0x004a2df9u);
    sub_00414660(ctx, mem);
    // 0x004a2df9: push 2
    uint32_t t100 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t100);
    mem.w32(t100, 0x00000002u);
    // 0x004a2dfb: push 0x53a874
    uint32_t t101 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t101);
    mem.w32(t101, 0x0053a874u);
    // 0x004a2e00: lea eax, [esp + 0x104]
    uint32_t t102 = static_cast<uint32_t>(ctx.esp + 0x00000104u);
    ctx.eax = static_cast<uint32_t>(t102);
    // 0x004a2e07: call 0x414660
    uint32_t t103 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    mem.w32(t103, 0x004a2e0cu);
    sub_00414660(ctx, mem);
    // 0x004a2e0c: mov eax, dword ptr [0x767448]
    uint32_t t104 = mem.r32(0x00767448u);
    ctx.eax = static_cast<uint32_t>(t104);
    // 0x004a2e11: cmp eax, ebx
    uint32_t t105 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t105);
    // 0x004a2e13: je 0x4a2e3a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a2e3a;
    goto bb_004a2e15;
}
bb_004a2e3a: {
    // 0x004a2e3a: mov edx, 0x539144
    ctx.edx = static_cast<uint32_t>(0x00539144u);
    goto bb_004a2e3f;
}
bb_004a2e15: {
    // 0x004a2e15: mov ecx, dword ptr [eax]
    uint32_t t106 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t106);
    // 0x004a2e17: mov eax, dword ptr [eax + 0x20]
    uint32_t t107 = static_cast<uint32_t>(ctx.eax + 0x00000020u);
    uint32_t t108 = mem.r32(t107);
    ctx.eax = static_cast<uint32_t>(t108);
    // 0x004a2e1a: mov edx, dword ptr [ecx]
    uint32_t t109 = mem.r32(ctx.ecx);
    ctx.edx = static_cast<uint32_t>(t109);
    // 0x004a2e1c: push ebx
    uint32_t t110 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t110);
    mem.w32(t110, ctx.ebx);
    // 0x004a2e1d: push edi
    uint32_t t111 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t111);
    mem.w32(t111, ctx.edi);
    // 0x004a2e1e: push edi
    uint32_t t112 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t112);
    mem.w32(t112, ctx.edi);
    // 0x004a2e1f: push 1
    uint32_t t113 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t113);
    mem.w32(t113, 0x00000001u);
    // 0x004a2e21: push eax
    uint32_t t114 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t114);
    mem.w32(t114, ctx.eax);
    // 0x004a2e22: push ecx
    uint32_t t115 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t115);
    mem.w32(t115, ctx.ecx);
    // 0x004a2e23: mov ecx, dword ptr [edx + 0x24]
    uint32_t t116 = static_cast<uint32_t>(ctx.edx + 0x00000024u);
    uint32_t t117 = mem.r32(t116);
    ctx.ecx = static_cast<uint32_t>(t117);
    // 0x004a2e26: call ecx
    uint32_t t118 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    mem.w32(t118, 0x004a2e28u);
    call_indirect(ctx, mem, ctx.ecx);
    // 0x004a2e28: xor edx, edx
    uint32_t t119 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t119);
    ctx.edx = static_cast<uint32_t>(t119);
    // 0x004a2e2a: cmp eax, ebx
    uint32_t t120 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t120);
    // 0x004a2e2c: sete dl
    uint8_t t121 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::E) ? 1u : 0u);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t121));
    // 0x004a2e2f: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004a2e31: cmp eax, ebx
    uint32_t t122 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t122);
    // 0x004a2e33: mov edx, 0x53a878
    ctx.edx = static_cast<uint32_t>(0x0053a878u);
    // 0x004a2e38: jne 0x4a2e3f
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a2e3f;
    goto bb_004a2e3a;
}
bb_004a2e3f: {
    // 0x004a2e3f: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004a2e41: lea ebp, [eax + 1]
    uint32_t t123 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.ebp = static_cast<uint32_t>(t123);
}
bb_004a2e44: {
    // 0x004a2e44: mov cl, byte ptr [eax]
    uint8_t t124 = mem.r8(ctx.eax);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t124));
    // 0x004a2e46: add eax, 1
    uint32_t t125 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t125);
    ctx.eax = static_cast<uint32_t>(t125);
    // 0x004a2e49: cmp cl, bl
    uint8_t t126 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) - static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.ecx), recomp_detail::r8l(ctx.ebx), t126);
    // 0x004a2e4b: jne 0x4a2e44
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a2e44;
}
{
    // 0x004a2e4d: sub eax, ebp
    uint32_t t127 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t127);
    ctx.eax = static_cast<uint32_t>(t127);
    // 0x004a2e4f: push eax
    uint32_t t128 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t128);
    mem.w32(t128, ctx.eax);
    // 0x004a2e50: push edx
    uint32_t t129 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t129);
    mem.w32(t129, ctx.edx);
    // 0x004a2e51: lea eax, [esp + 0x104]
    uint32_t t130 = static_cast<uint32_t>(ctx.esp + 0x00000104u);
    ctx.eax = static_cast<uint32_t>(t130);
    // 0x004a2e58: call 0x414660
    uint32_t t131 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t131);
    mem.w32(t131, 0x004a2e5du);
    sub_00414660(ctx, mem);
    // 0x004a2e5d: mov ecx, dword ptr [0x767448]
    uint32_t t132 = mem.r32(0x00767448u);
    ctx.ecx = static_cast<uint32_t>(t132);
    // 0x004a2e63: cmp ecx, ebx
    uint32_t t133 = static_cast<uint32_t>(ctx.ecx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebx, t133);
    // 0x004a2e65: mov esi, dword ptr [esp + 0x12c]
    uint32_t t134 = static_cast<uint32_t>(ctx.esp + 0x0000012cu);
    uint32_t t135 = mem.r32(t134);
    ctx.esi = static_cast<uint32_t>(t135);
    // 0x004a2e6c: je 0x4a2e95
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a2e95;
    goto bb_004a2e6e;
}
bb_004a2e95: {
    // 0x004a2e95: mov edx, 0x539144
    ctx.edx = static_cast<uint32_t>(0x00539144u);
    goto bb_004a2e9a;
}
bb_004a2e6e: {
    // 0x004a2e6e: mov eax, dword ptr [ecx]
    uint32_t t136 = mem.r32(ctx.ecx);
    ctx.eax = static_cast<uint32_t>(t136);
    // 0x004a2e70: mov ecx, dword ptr [ecx + 0x20]
    uint32_t t137 = static_cast<uint32_t>(ctx.ecx + 0x00000020u);
    uint32_t t138 = mem.r32(t137);
    ctx.ecx = static_cast<uint32_t>(t138);
    // 0x004a2e73: mov edx, dword ptr [eax]
    uint32_t t139 = mem.r32(ctx.eax);
    ctx.edx = static_cast<uint32_t>(t139);
    // 0x004a2e75: mov edx, dword ptr [edx + 0x28]
    uint32_t t140 = static_cast<uint32_t>(ctx.edx + 0x00000028u);
    uint32_t t141 = mem.r32(t140);
    ctx.edx = static_cast<uint32_t>(t141);
    // 0x004a2e78: push edi
    uint32_t t142 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t142);
    mem.w32(t142, ctx.edi);
    // 0x004a2e79: push 3
    uint32_t t143 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t143);
    mem.w32(t143, 0x00000003u);
    // 0x004a2e7b: push ebx
    uint32_t t144 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t144);
    mem.w32(t144, ctx.ebx);
    // 0x004a2e7c: push esi
    uint32_t t145 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t145);
    mem.w32(t145, ctx.esi);
    // 0x004a2e7d: push 1
    uint32_t t146 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t146);
    mem.w32(t146, 0x00000001u);
    // 0x004a2e7f: push ecx
    uint32_t t147 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t147);
    mem.w32(t147, ctx.ecx);
    // 0x004a2e80: push eax
    uint32_t t148 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t148);
    mem.w32(t148, ctx.eax);
    // 0x004a2e81: call edx
    uint32_t t149 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t149);
    mem.w32(t149, 0x004a2e83u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x004a2e83: xor ecx, ecx
    uint32_t t150 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t150);
    ctx.ecx = static_cast<uint32_t>(t150);
    // 0x004a2e85: cmp eax, ebx
    uint32_t t151 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t151);
    // 0x004a2e87: sete cl
    uint8_t t152 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::E) ? 1u : 0u);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t152));
    // 0x004a2e8a: mov edx, 0x53a87c
    ctx.edx = static_cast<uint32_t>(0x0053a87cu);
    // 0x004a2e8f: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x004a2e91: cmp eax, ebx
    uint32_t t153 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t153);
    // 0x004a2e93: jne 0x4a2e9a
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a2e9a;
    goto bb_004a2e95;
}
bb_004a2e9a: {
    // 0x004a2e9a: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004a2e9c: lea ebp, [eax + 1]
    uint32_t t154 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.ebp = static_cast<uint32_t>(t154);
    // 0x004a2e9f: nop
}
bb_004a2ea0: {
    // 0x004a2ea0: mov cl, byte ptr [eax]
    uint8_t t155 = mem.r8(ctx.eax);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t155));
    // 0x004a2ea2: add eax, 1
    uint32_t t156 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t156);
    ctx.eax = static_cast<uint32_t>(t156);
    // 0x004a2ea5: cmp cl, bl
    uint8_t t157 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) - static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.ecx), recomp_detail::r8l(ctx.ebx), t157);
    // 0x004a2ea7: jne 0x4a2ea0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a2ea0;
}
{
    // 0x004a2ea9: sub eax, ebp
    uint32_t t158 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t158);
    ctx.eax = static_cast<uint32_t>(t158);
    // 0x004a2eab: push eax
    uint32_t t159 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t159);
    mem.w32(t159, ctx.eax);
    // 0x004a2eac: push edx
    uint32_t t160 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t160);
    mem.w32(t160, ctx.edx);
    // 0x004a2ead: lea eax, [esp + 0x104]
    uint32_t t161 = static_cast<uint32_t>(ctx.esp + 0x00000104u);
    ctx.eax = static_cast<uint32_t>(t161);
    // 0x004a2eb4: call 0x414660
    uint32_t t162 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t162);
    mem.w32(t162, 0x004a2eb9u);
    sub_00414660(ctx, mem);
    // 0x004a2eb9: mov ecx, dword ptr [0x767448]
    uint32_t t163 = mem.r32(0x00767448u);
    ctx.ecx = static_cast<uint32_t>(t163);
    // 0x004a2ebf: cmp ecx, ebx
    uint32_t t164 = static_cast<uint32_t>(ctx.ecx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebx, t164);
    // 0x004a2ec1: je 0x4a2eeb
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a2eeb;
    goto bb_004a2ec3;
}
bb_004a2eeb: {
    // 0x004a2eeb: mov edx, 0x539144
    ctx.edx = static_cast<uint32_t>(0x00539144u);
    goto bb_004a2ef0;
}
bb_004a2ec3: {
    // 0x004a2ec3: mov eax, dword ptr [ecx]
    uint32_t t165 = mem.r32(ctx.ecx);
    ctx.eax = static_cast<uint32_t>(t165);
    // 0x004a2ec5: mov ecx, dword ptr [ecx + 0x20]
    uint32_t t166 = static_cast<uint32_t>(ctx.ecx + 0x00000020u);
    uint32_t t167 = mem.r32(t166);
    ctx.ecx = static_cast<uint32_t>(t167);
    // 0x004a2ec8: mov edx, dword ptr [eax]
    uint32_t t168 = mem.r32(ctx.eax);
    ctx.edx = static_cast<uint32_t>(t168);
    // 0x004a2eca: mov edx, dword ptr [edx + 0x28]
    uint32_t t169 = static_cast<uint32_t>(ctx.edx + 0x00000028u);
    uint32_t t170 = mem.r32(t169);
    ctx.edx = static_cast<uint32_t>(t170);
    // 0x004a2ecd: push edi
    uint32_t t171 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t171);
    mem.w32(t171, ctx.edi);
    // 0x004a2ece: push 1
    uint32_t t172 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t172);
    mem.w32(t172, 0x00000001u);
    // 0x004a2ed0: push 2
    uint32_t t173 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t173);
    mem.w32(t173, 0x00000002u);
    // 0x004a2ed2: push esi
    uint32_t t174 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t174);
    mem.w32(t174, ctx.esi);
    // 0x004a2ed3: push 1
    uint32_t t175 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t175);
    mem.w32(t175, 0x00000001u);
    // 0x004a2ed5: push ecx
    uint32_t t176 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t176);
    mem.w32(t176, ctx.ecx);
    // 0x004a2ed6: push eax
    uint32_t t177 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t177);
    mem.w32(t177, ctx.eax);
    // 0x004a2ed7: call edx
    uint32_t t178 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t178);
    mem.w32(t178, 0x004a2ed9u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x004a2ed9: xor ecx, ecx
    uint32_t t179 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t179);
    ctx.ecx = static_cast<uint32_t>(t179);
    // 0x004a2edb: cmp eax, ebx
    uint32_t t180 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t180);
    // 0x004a2edd: sete cl
    uint8_t t181 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::E) ? 1u : 0u);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t181));
    // 0x004a2ee0: mov edx, 0x5370e8
    ctx.edx = static_cast<uint32_t>(0x005370e8u);
    // 0x004a2ee5: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x004a2ee7: cmp eax, ebx
    uint32_t t182 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t182);
    // 0x004a2ee9: jne 0x4a2ef0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a2ef0;
    goto bb_004a2eeb;
}
bb_004a2ef0: {
    // 0x004a2ef0: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004a2ef2: lea ebp, [eax + 1]
    uint32_t t183 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.ebp = static_cast<uint32_t>(t183);
}
bb_004a2ef5: {
    // 0x004a2ef5: mov cl, byte ptr [eax]
    uint8_t t184 = mem.r8(ctx.eax);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t184));
    // 0x004a2ef7: add eax, 1
    uint32_t t185 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t185);
    ctx.eax = static_cast<uint32_t>(t185);
    // 0x004a2efa: cmp cl, bl
    uint8_t t186 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) - static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.ecx), recomp_detail::r8l(ctx.ebx), t186);
    // 0x004a2efc: jne 0x4a2ef5
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a2ef5;
}
{
    // 0x004a2efe: sub eax, ebp
    uint32_t t187 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t187);
    ctx.eax = static_cast<uint32_t>(t187);
    // 0x004a2f00: push eax
    uint32_t t188 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t188);
    mem.w32(t188, ctx.eax);
    // 0x004a2f01: push edx
    uint32_t t189 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t189);
    mem.w32(t189, ctx.edx);
    // 0x004a2f02: lea eax, [esp + 0x104]
    uint32_t t190 = static_cast<uint32_t>(ctx.esp + 0x00000104u);
    ctx.eax = static_cast<uint32_t>(t190);
    // 0x004a2f09: call 0x414660
    uint32_t t191 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t191);
    mem.w32(t191, 0x004a2f0eu);
    sub_00414660(ctx, mem);
    // 0x004a2f0e: mov ecx, dword ptr [0x767448]
    uint32_t t192 = mem.r32(0x00767448u);
    ctx.ecx = static_cast<uint32_t>(t192);
    // 0x004a2f14: cmp ecx, ebx
    uint32_t t193 = static_cast<uint32_t>(ctx.ecx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebx, t193);
    // 0x004a2f16: je 0x4a2f40
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a2f40;
    goto bb_004a2f18;
}
bb_004a2f40: {
    // 0x004a2f40: mov ecx, 0x539144
    ctx.ecx = static_cast<uint32_t>(0x00539144u);
    goto bb_004a2f45;
}
bb_004a2f18: {
    // 0x004a2f18: mov eax, dword ptr [ecx]
    uint32_t t194 = mem.r32(ctx.ecx);
    ctx.eax = static_cast<uint32_t>(t194);
    // 0x004a2f1a: mov ecx, dword ptr [ecx + 0x20]
    uint32_t t195 = static_cast<uint32_t>(ctx.ecx + 0x00000020u);
    uint32_t t196 = mem.r32(t195);
    ctx.ecx = static_cast<uint32_t>(t196);
    // 0x004a2f1d: mov edx, dword ptr [eax]
    uint32_t t197 = mem.r32(ctx.eax);
    ctx.edx = static_cast<uint32_t>(t197);
    // 0x004a2f1f: mov edx, dword ptr [edx + 0x28]
    uint32_t t198 = static_cast<uint32_t>(ctx.edx + 0x00000028u);
    uint32_t t199 = mem.r32(t198);
    ctx.edx = static_cast<uint32_t>(t199);
    // 0x004a2f22: push edi
    uint32_t t200 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t200);
    mem.w32(t200, ctx.edi);
    // 0x004a2f23: push 3
    uint32_t t201 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t201);
    mem.w32(t201, 0x00000003u);
    // 0x004a2f25: push 1
    uint32_t t202 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t202);
    mem.w32(t202, 0x00000001u);
    // 0x004a2f27: push esi
    uint32_t t203 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t203);
    mem.w32(t203, ctx.esi);
    // 0x004a2f28: push 1
    uint32_t t204 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t204);
    mem.w32(t204, 0x00000001u);
    // 0x004a2f2a: push ecx
    uint32_t t205 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t205);
    mem.w32(t205, ctx.ecx);
    // 0x004a2f2b: push eax
    uint32_t t206 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t206);
    mem.w32(t206, ctx.eax);
    // 0x004a2f2c: call edx
    uint32_t t207 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t207);
    mem.w32(t207, 0x004a2f2eu);
    call_indirect(ctx, mem, ctx.edx);
    // 0x004a2f2e: xor ecx, ecx
    uint32_t t208 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t208);
    ctx.ecx = static_cast<uint32_t>(t208);
    // 0x004a2f30: cmp eax, ebx
    uint32_t t209 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t209);
    // 0x004a2f32: sete cl
    uint8_t t210 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::E) ? 1u : 0u);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t210));
    // 0x004a2f35: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x004a2f37: cmp eax, ebx
    uint32_t t211 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t211);
    // 0x004a2f39: mov ecx, 0x53a880
    ctx.ecx = static_cast<uint32_t>(0x0053a880u);
    // 0x004a2f3e: jne 0x4a2f45
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a2f45;
    goto bb_004a2f40;
}
bb_004a2f45: {
    // 0x004a2f45: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x004a2f47: lea edi, [eax + 1]
    uint32_t t212 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.edi = static_cast<uint32_t>(t212);
    // 0x004a2f4a: lea ebx, [ebx]
    ctx.ebx = static_cast<uint32_t>(ctx.ebx);
}
bb_004a2f50: {
    // 0x004a2f50: mov dl, byte ptr [eax]
    uint8_t t213 = mem.r8(ctx.eax);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t213));
    // 0x004a2f52: add eax, 1
    uint32_t t214 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t214);
    ctx.eax = static_cast<uint32_t>(t214);
    // 0x004a2f55: cmp dl, bl
    uint8_t t215 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)) - static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.edx), recomp_detail::r8l(ctx.ebx), t215);
    // 0x004a2f57: jne 0x4a2f50
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a2f50;
}
{
    // 0x004a2f59: sub eax, edi
    uint32_t t216 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t216);
    ctx.eax = static_cast<uint32_t>(t216);
    // 0x004a2f5b: push eax
    uint32_t t217 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t217);
    mem.w32(t217, ctx.eax);
    // 0x004a2f5c: push ecx
    uint32_t t218 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t218);
    mem.w32(t218, ctx.ecx);
    // 0x004a2f5d: lea eax, [esp + 0x104]
    uint32_t t219 = static_cast<uint32_t>(ctx.esp + 0x00000104u);
    ctx.eax = static_cast<uint32_t>(t219);
    // 0x004a2f64: call 0x414660
    uint32_t t220 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t220);
    mem.w32(t220, 0x004a2f69u);
    sub_00414660(ctx, mem);
    // 0x004a2f69: push 1
    uint32_t t221 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t221);
    mem.w32(t221, 0x00000001u);
    // 0x004a2f6b: push 0x538510
    uint32_t t222 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t222);
    mem.w32(t222, 0x00538510u);
    // 0x004a2f70: lea eax, [esp + 0x104]
    uint32_t t223 = static_cast<uint32_t>(ctx.esp + 0x00000104u);
    ctx.eax = static_cast<uint32_t>(t223);
    // 0x004a2f77: call 0x414660
    uint32_t t224 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t224);
    mem.w32(t224, 0x004a2f7cu);
    sub_00414660(ctx, mem);
    // 0x004a2f7c: push 2
    uint32_t t225 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t225);
    mem.w32(t225, 0x00000002u);
    // 0x004a2f7e: push 0x538d44
    uint32_t t226 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t226);
    mem.w32(t226, 0x00538d44u);
    // 0x004a2f83: lea eax, [esp + 0x104]
    uint32_t t227 = static_cast<uint32_t>(ctx.esp + 0x00000104u);
    ctx.eax = static_cast<uint32_t>(t227);
    // 0x004a2f8a: call 0x414660
    uint32_t t228 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t228);
    mem.w32(t228, 0x004a2f8fu);
    sub_00414660(ctx, mem);
    // 0x004a2f8f: mov esi, dword ptr [esp + 0x18]
    uint32_t t229 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t230 = mem.r32(t229);
    ctx.esi = static_cast<uint32_t>(t230);
    // 0x004a2f93: push ebx
    uint32_t t231 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t231);
    mem.w32(t231, ctx.ebx);
    // 0x004a2f94: lea edx, [esp + 0x100]
    uint32_t t232 = static_cast<uint32_t>(ctx.esp + 0x00000100u);
    ctx.edx = static_cast<uint32_t>(t232);
    // 0x004a2f9b: push edx
    uint32_t t233 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t233);
    mem.w32(t233, ctx.edx);
    // 0x004a2f9c: or eax, 0xffffffff
    uint32_t t234 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t234);
    ctx.eax = static_cast<uint32_t>(t234);
    // 0x004a2f9f: call 0x414360
    uint32_t t235 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t235);
    mem.w32(t235, 0x004a2fa4u);
    sub_00414360(ctx, mem);
    // 0x004a2fa4: add dword ptr [esp + 0x14], 4
    uint32_t t236 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t237 = mem.r32(t236);
    uint32_t t238 = static_cast<uint32_t>(t237 + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t237, 0x00000004u, t238);
    mem.w32(t236, t238);
    // 0x004a2fa9: mov dword ptr [esp + 0x124], 0xffffffff
    uint32_t t239 = static_cast<uint32_t>(ctx.esp + 0x00000124u);
    mem.w32(t239, 0xffffffffu);
    // 0x004a2fb4: cmp dword ptr [esp + 0x114], 0x10
    uint32_t t240 = static_cast<uint32_t>(ctx.esp + 0x00000114u);
    uint32_t t241 = mem.r32(t240);
    uint32_t t242 = static_cast<uint32_t>(t241 - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t241, 0x00000010u, t242);
    // 0x004a2fbc: jb 0x4a2fce
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a2fce;
    goto bb_004a2fbe;
}
bb_004a2fce: {
    // 0x004a2fce: mov ecx, dword ptr [esp + 0x14]
    uint32_t t243 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t244 = mem.r32(t243);
    ctx.ecx = static_cast<uint32_t>(t244);
    // 0x004a2fd2: cmp dword ptr [ecx], ebx
    uint32_t t245 = mem.r32(ctx.ecx);
    uint32_t t246 = static_cast<uint32_t>(t245 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t245, ctx.ebx, t246);
    // 0x004a2fd4: mov dword ptr [esp + 0x114], 0xf
    uint32_t t247 = static_cast<uint32_t>(ctx.esp + 0x00000114u);
    mem.w32(t247, 0x0000000fu);
    // 0x004a2fdf: mov dword ptr [esp + 0x110], ebx
    uint32_t t248 = static_cast<uint32_t>(ctx.esp + 0x00000110u);
    mem.w32(t248, ctx.ebx);
    // 0x004a2fe6: mov byte ptr [esp + 0x100], bl
    uint32_t t249 = static_cast<uint32_t>(ctx.esp + 0x00000100u);
    mem.w8(t249, recomp_detail::r8l(ctx.ebx));
    // 0x004a2fed: jne 0x4a2dab
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a2dab;
    goto bb_004a2ff3;
}
bb_004a2fbe: {
    // 0x004a2fbe: mov eax, dword ptr [esp + 0x100]
    uint32_t t250 = static_cast<uint32_t>(ctx.esp + 0x00000100u);
    uint32_t t251 = mem.r32(t250);
    ctx.eax = static_cast<uint32_t>(t251);
    // 0x004a2fc5: push eax
    uint32_t t252 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t252);
    mem.w32(t252, ctx.eax);
    // 0x004a2fc6: call 0x4e02f3
    uint32_t t253 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t253);
    mem.w32(t253, 0x004a2fcbu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a2fcb: add esp, 4
    uint32_t t254 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t254);
    ctx.esp = static_cast<uint32_t>(t254);
    goto bb_004a2fce;
}
bb_004a2ff3: {
    // 0x004a2ff3: push 2
    uint32_t t255 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t255);
    mem.w32(t255, 0x00000002u);
    // 0x004a2ff5: push 0x538d44
    uint32_t t256 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t256);
    mem.w32(t256, 0x00538d44u);
    // 0x004a2ffa: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004a2ffc: call 0x414660
    uint32_t t257 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t257);
    mem.w32(t257, 0x004a3001u);
    sub_00414660(ctx, mem);
    // 0x004a3001: mov ecx, dword ptr [esp + 0x11c]
    uint32_t t258 = static_cast<uint32_t>(ctx.esp + 0x0000011cu);
    uint32_t t259 = mem.r32(t258);
    ctx.ecx = static_cast<uint32_t>(t259);
    // 0x004a3008: mov dword ptr fs:[0], ecx
    uint32_t t260 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t260, ctx.ecx);
    // 0x004a300f: pop ecx
    uint32_t t261 = ctx.esp;
    uint32_t t262 = mem.r32(t261);
    uint32_t t263 = static_cast<uint32_t>(t261 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t263);
    ctx.ecx = static_cast<uint32_t>(t262);
    // 0x004a3010: pop edi
    uint32_t t264 = ctx.esp;
    uint32_t t265 = mem.r32(t264);
    uint32_t t266 = static_cast<uint32_t>(t264 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t266);
    ctx.edi = static_cast<uint32_t>(t265);
    // 0x004a3011: pop esi
    uint32_t t267 = ctx.esp;
    uint32_t t268 = mem.r32(t267);
    uint32_t t269 = static_cast<uint32_t>(t267 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t269);
    ctx.esi = static_cast<uint32_t>(t268);
    // 0x004a3012: pop ebp
    uint32_t t270 = ctx.esp;
    uint32_t t271 = mem.r32(t270);
    uint32_t t272 = static_cast<uint32_t>(t270 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t272);
    ctx.ebp = static_cast<uint32_t>(t271);
    // 0x004a3013: pop ebx
    uint32_t t273 = ctx.esp;
    uint32_t t274 = mem.r32(t273);
    uint32_t t275 = static_cast<uint32_t>(t273 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t275);
    ctx.ebx = static_cast<uint32_t>(t274);
    // 0x004a3014: mov ecx, dword ptr [esp + 0x104]
    uint32_t t276 = static_cast<uint32_t>(ctx.esp + 0x00000104u);
    uint32_t t277 = mem.r32(t276);
    ctx.ecx = static_cast<uint32_t>(t277);
    // 0x004a301b: xor ecx, esp
    uint32_t t278 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t278);
    ctx.ecx = static_cast<uint32_t>(t278);
    // 0x004a301d: call 0x4e02f8
    uint32_t t279 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t279);
    mem.w32(t279, 0x004a3022u);
    hle_crt_004e02f8(ctx, mem);
    // 0x004a3022: add esp, 0x114
    uint32_t t280 = static_cast<uint32_t>(ctx.esp + 0x00000114u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000114u, t280);
    ctx.esp = static_cast<uint32_t>(t280);
    // 0x004a3028: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004a38d0 | subsystem=Core/Windows | canonical | 55 blocks | 199 insns
void sub_004a38d0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a38d0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x004a38d2: push 0x51671b
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051671bu);
    // 0x004a38d7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004a38dd: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x004a38de: sub esp, 8
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000008u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000008u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x004a38e1: push ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebx);
    // 0x004a38e2: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x004a38e3: push edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edi);
    // 0x004a38e4: mov eax, dword ptr [0x54b458]
    uint32_t t9 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x004a38e9: xor eax, esp
    uint32_t t10 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x004a38eb: push eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.eax);
    // 0x004a38ec: lea eax, [esp + 0x18]
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x004a38f0: mov dword ptr fs:[0], eax
    uint32_t t13 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t13, ctx.eax);
    // 0x004a38f6: push 0x140
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x00000140u);
    // 0x004a38fb: call 0x4e0177
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x004a3900u);
    hle_crt_004e0177(ctx, mem);
    // 0x004a3900: add esp, 4
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t16);
    ctx.esp = static_cast<uint32_t>(t16);
    // 0x004a3903: mov dword ptr [esp + 0x14], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t17, ctx.eax);
    // 0x004a3907: xor edi, edi
    uint32_t t18 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    ctx.edi = static_cast<uint32_t>(t18);
    // 0x004a3909: cmp eax, edi
    uint32_t t19 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t19);
    // 0x004a390b: mov dword ptr [esp + 0x20], edi
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t20, ctx.edi);
    // 0x004a390f: je 0x4a391c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a391c;
    goto bb_004a3911;
}
bb_004a391c: {
    // 0x004a391c: xor esi, esi
    uint32_t t21 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t21);
    ctx.esi = static_cast<uint32_t>(t21);
    goto bb_004a391e;
}
bb_004a3911: {
    // 0x004a3911: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004a3913: call 0x40c260
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x004a3918u);
    sub_0040c260(ctx, mem);
    // 0x004a3918: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004a391a: jmp 0x4a391e
}
bb_004a391e: {
    // 0x004a391e: push 0x53a898
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x0053a898u);
    // 0x004a3923: mov ebx, esi
    ctx.ebx = static_cast<uint32_t>(ctx.esi);
    // 0x004a3925: mov dword ptr [esp + 0x24], 0xffffffff
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t24, 0xffffffffu);
    // 0x004a392d: call 0x40c2b0
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x004a3932u);
    sub_0040c2b0(ctx, mem);
    // 0x004a3932: test eax, eax
    uint32_t t26 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t26);
    // 0x004a3934: je 0x4a3aee
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a3aee;
    goto bb_004a393a;
}
bb_004a3aee: {
    // 0x004a3aee: mov dword ptr [0x76e770], edi
    mem.w32(0x0076e770u, ctx.edi);
    // 0x004a3af4: mov dword ptr [0x54d040], 1
    mem.w32(0x0054d040u, 0x00000001u);
    // 0x004a3afe: mov dword ptr [0x54d044], 0x20
    mem.w32(0x0054d044u, 0x00000020u);
    // 0x004a3b08: mov dword ptr [0x54d048], 0x280
    mem.w32(0x0054d048u, 0x00000280u);
    // 0x004a3b12: mov dword ptr [0x54d04c], 0x1e0
    mem.w32(0x0054d04cu, 0x000001e0u);
    // 0x004a3b1c: mov dword ptr [0x76e774], edi
    mem.w32(0x0076e774u, ctx.edi);
    goto bb_004a3b22;
}
bb_004a393a: {
    // 0x004a393a: cmp dword ptr [esi], edi
    uint32_t t27 = mem.r32(ctx.esi);
    uint32_t t28 = static_cast<uint32_t>(t27 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t27, ctx.edi, t28);
    // 0x004a393c: je 0x4a3942
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a3942;
    goto bb_004a393e;
}
bb_004a3b22: {
    // 0x004a3b22: cmp dword ptr [0x76e778], edi
    uint32_t t29 = mem.r32(0x0076e778u);
    uint32_t t30 = static_cast<uint32_t>(t29 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t29, ctx.edi, t30);
    // 0x004a3b28: jge 0x4a3b30
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_004a3b30;
    goto bb_004a3b2a;
}
bb_004a3942: {
    // 0x004a3942: mov eax, 0x53a8ac
    ctx.eax = static_cast<uint32_t>(0x0053a8acu);
    // 0x004a3947: mov ebx, 0x5350b4
    ctx.ebx = static_cast<uint32_t>(0x005350b4u);
    // 0x004a394c: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a394e: call 0x40c670
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x004a3953u);
    sub_0040c670(ctx, mem);
    // 0x004a3953: cmp eax, edi
    uint32_t t32 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t32);
    // 0x004a3955: jne 0x4a395b
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a395b;
    goto bb_004a3957;
}
bb_004a393e: {
    // 0x004a393e: xor eax, eax
    uint32_t t33 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t33);
    ctx.eax = static_cast<uint32_t>(t33);
    // 0x004a3940: jmp 0x4a3964
    goto bb_004a3964;
}
bb_004a3b30: {
    // 0x004a3b30: cmp dword ptr [0x76e77c], edi
    uint32_t t34 = mem.r32(0x0076e77cu);
    uint32_t t35 = static_cast<uint32_t>(t34 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t34, ctx.edi, t35);
    // 0x004a3b36: jge 0x4a3b3e
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_004a3b3e;
    goto bb_004a3b38;
}
bb_004a3b2a: {
    // 0x004a3b2a: mov dword ptr [0x76e778], edi
    mem.w32(0x0076e778u, ctx.edi);
    goto bb_004a3b30;
}
bb_004a395b: {
    // 0x004a395b: push eax
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, ctx.eax);
    // 0x004a395c: call 0x4e0eb7
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, 0x004a3961u);
    hle_crt_004e0eb7(ctx, mem);
    // 0x004a3961: add esp, 4
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t38);
    ctx.esp = static_cast<uint32_t>(t38);
    goto bb_004a3964;
}
bb_004a3957: {
    // 0x004a3957: xor eax, eax
    uint32_t t39 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t39);
    ctx.eax = static_cast<uint32_t>(t39);
    // 0x004a3959: jmp 0x4a3964
}
bb_004a3964: {
    // 0x004a3964: xor ecx, ecx
    uint32_t t40 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t40);
    ctx.ecx = static_cast<uint32_t>(t40);
    // 0x004a3966: cmp eax, edi
    uint32_t t41 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t41);
    // 0x004a3968: setne cl
    uint8_t t42 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::NE) ? 1u : 0u);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t42));
    // 0x004a396b: cmp dword ptr [esi], edi
    uint32_t t43 = mem.r32(ctx.esi);
    uint32_t t44 = static_cast<uint32_t>(t43 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t43, ctx.edi, t44);
    // 0x004a396d: mov dword ptr [0x76e770], ecx
    mem.w32(0x0076e770u, ctx.ecx);
    // 0x004a3973: je 0x4a397c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a397c;
    goto bb_004a3975;
}
bb_004a3b3e: {
    // 0x004a3b3e: cmp esi, edi
    uint32_t t45 = static_cast<uint32_t>(ctx.esi - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edi, t45);
    // 0x004a3b40: je 0x4a3b49
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a3b49;
    goto bb_004a3b42;
}
bb_004a3b38: {
    // 0x004a3b38: mov dword ptr [0x76e77c], edi
    mem.w32(0x0076e77cu, ctx.edi);
    goto bb_004a3b3e;
}
bb_004a397c: {
    // 0x004a397c: mov eax, 0x53a8b8
    ctx.eax = static_cast<uint32_t>(0x0053a8b8u);
    // 0x004a3981: mov ebx, 0x5350b4
    ctx.ebx = static_cast<uint32_t>(0x005350b4u);
    // 0x004a3986: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a3988: call 0x40c670
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, 0x004a398du);
    sub_0040c670(ctx, mem);
    // 0x004a398d: cmp eax, edi
    uint32_t t47 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t47);
    // 0x004a398f: jne 0x4a3998
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a3998;
    goto bb_004a3991;
}
bb_004a3975: {
    // 0x004a3975: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x004a397a: jmp 0x4a39a1
    goto bb_004a39a1;
}
bb_004a3b49: {
    // 0x004a3b49: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x004a3b4e: mov ecx, dword ptr [esp + 0x18]
    uint32_t t48 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t49 = mem.r32(t48);
    ctx.ecx = static_cast<uint32_t>(t49);
    // 0x004a3b52: mov dword ptr fs:[0], ecx
    uint32_t t50 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t50, ctx.ecx);
    // 0x004a3b59: pop ecx
    uint32_t t51 = ctx.esp;
    uint32_t t52 = mem.r32(t51);
    uint32_t t53 = static_cast<uint32_t>(t51 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    ctx.ecx = static_cast<uint32_t>(t52);
    // 0x004a3b5a: pop edi
    uint32_t t54 = ctx.esp;
    uint32_t t55 = mem.r32(t54);
    uint32_t t56 = static_cast<uint32_t>(t54 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    ctx.edi = static_cast<uint32_t>(t55);
    // 0x004a3b5b: pop esi
    uint32_t t57 = ctx.esp;
    uint32_t t58 = mem.r32(t57);
    uint32_t t59 = static_cast<uint32_t>(t57 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    ctx.esi = static_cast<uint32_t>(t58);
    // 0x004a3b5c: pop ebx
    uint32_t t60 = ctx.esp;
    uint32_t t61 = mem.r32(t60);
    uint32_t t62 = static_cast<uint32_t>(t60 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    ctx.ebx = static_cast<uint32_t>(t61);
    // 0x004a3b5d: add esp, 0x14
    uint32_t t63 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000014u, t63);
    ctx.esp = static_cast<uint32_t>(t63);
    // 0x004a3b60: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a3b42: {
    // 0x004a3b42: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004a3b44: call 0x40b480
    uint32_t t64 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    mem.w32(t64, 0x004a3b49u);
    sub_0040b480(ctx, mem);
    goto bb_004a3b49;
}
bb_004a3998: {
    // 0x004a3998: push eax
    uint32_t t65 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t65);
    mem.w32(t65, ctx.eax);
    // 0x004a3999: call 0x4e0eb7
    uint32_t t66 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    mem.w32(t66, 0x004a399eu);
    hle_crt_004e0eb7(ctx, mem);
    // 0x004a399e: add esp, 4
    uint32_t t67 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t67);
    ctx.esp = static_cast<uint32_t>(t67);
    goto bb_004a39a1;
}
bb_004a3991: {
    // 0x004a3991: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x004a3996: jmp 0x4a39a1
}
bb_004a39a1: {
    // 0x004a39a1: xor edx, edx
    uint32_t t68 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t68);
    ctx.edx = static_cast<uint32_t>(t68);
    // 0x004a39a3: cmp eax, edi
    uint32_t t69 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t69);
    // 0x004a39a5: setne dl
    uint8_t t70 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::NE) ? 1u : 0u);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t70));
    // 0x004a39a8: cmp dword ptr [esi], edi
    uint32_t t71 = mem.r32(ctx.esi);
    uint32_t t72 = static_cast<uint32_t>(t71 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t71, ctx.edi, t72);
    // 0x004a39aa: mov dword ptr [0x54d040], edx
    mem.w32(0x0054d040u, ctx.edx);
    // 0x004a39b0: je 0x4a39b6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a39b6;
    goto bb_004a39b2;
}
bb_004a39b6: {
    // 0x004a39b6: mov eax, 0x53a8c4
    ctx.eax = static_cast<uint32_t>(0x0053a8c4u);
    // 0x004a39bb: mov ebx, 0x5350b4
    ctx.ebx = static_cast<uint32_t>(0x005350b4u);
    // 0x004a39c0: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a39c2: call 0x40c670
    uint32_t t73 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    mem.w32(t73, 0x004a39c7u);
    sub_0040c670(ctx, mem);
    // 0x004a39c7: cmp eax, edi
    uint32_t t74 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t74);
    // 0x004a39c9: jne 0x4a39cf
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a39cf;
    goto bb_004a39cb;
}
bb_004a39b2: {
    // 0x004a39b2: xor eax, eax
    uint32_t t75 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t75);
    ctx.eax = static_cast<uint32_t>(t75);
    // 0x004a39b4: jmp 0x4a39d8
    goto bb_004a39d8;
}
bb_004a39cf: {
    // 0x004a39cf: push eax
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    mem.w32(t76, ctx.eax);
    // 0x004a39d0: call 0x4e0eb7
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, 0x004a39d5u);
    hle_crt_004e0eb7(ctx, mem);
    // 0x004a39d5: add esp, 4
    uint32_t t78 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t78);
    ctx.esp = static_cast<uint32_t>(t78);
    goto bb_004a39d8;
}
bb_004a39cb: {
    // 0x004a39cb: xor eax, eax
    uint32_t t79 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t79);
    ctx.eax = static_cast<uint32_t>(t79);
    // 0x004a39cd: jmp 0x4a39d8
}
bb_004a39d8: {
    // 0x004a39d8: cmp dword ptr [esi], edi
    uint32_t t80 = mem.r32(ctx.esi);
    uint32_t t81 = static_cast<uint32_t>(t80 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t80, ctx.edi, t81);
    // 0x004a39da: mov dword ptr [0x54d048], eax
    mem.w32(0x0054d048u, ctx.eax);
    // 0x004a39df: je 0x4a39e5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a39e5;
    goto bb_004a39e1;
}
bb_004a39e5: {
    // 0x004a39e5: mov eax, 0x53a8cc
    ctx.eax = static_cast<uint32_t>(0x0053a8ccu);
    // 0x004a39ea: mov ebx, 0x5350b4
    ctx.ebx = static_cast<uint32_t>(0x005350b4u);
    // 0x004a39ef: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a39f1: call 0x40c670
    uint32_t t82 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t82);
    mem.w32(t82, 0x004a39f6u);
    sub_0040c670(ctx, mem);
    // 0x004a39f6: cmp eax, edi
    uint32_t t83 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t83);
    // 0x004a39f8: jne 0x4a39fe
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a39fe;
    goto bb_004a39fa;
}
bb_004a39e1: {
    // 0x004a39e1: xor eax, eax
    uint32_t t84 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t84);
    ctx.eax = static_cast<uint32_t>(t84);
    // 0x004a39e3: jmp 0x4a3a07
    goto bb_004a3a07;
}
bb_004a39fe: {
    // 0x004a39fe: push eax
    uint32_t t85 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t85);
    mem.w32(t85, ctx.eax);
    // 0x004a39ff: call 0x4e0eb7
    uint32_t t86 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t86);
    mem.w32(t86, 0x004a3a04u);
    hle_crt_004e0eb7(ctx, mem);
    // 0x004a3a04: add esp, 4
    uint32_t t87 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t87);
    ctx.esp = static_cast<uint32_t>(t87);
    goto bb_004a3a07;
}
bb_004a39fa: {
    // 0x004a39fa: xor eax, eax
    uint32_t t88 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t88);
    ctx.eax = static_cast<uint32_t>(t88);
    // 0x004a39fc: jmp 0x4a3a07
}
bb_004a3a07: {
    // 0x004a3a07: cmp dword ptr [esi], edi
    uint32_t t89 = mem.r32(ctx.esi);
    uint32_t t90 = static_cast<uint32_t>(t89 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t89, ctx.edi, t90);
    // 0x004a3a09: mov dword ptr [0x54d04c], eax
    mem.w32(0x0054d04cu, ctx.eax);
    // 0x004a3a0e: je 0x4a3a17
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a3a17;
    goto bb_004a3a10;
}
bb_004a3a17: {
    // 0x004a3a17: mov eax, 0x53a8d4
    ctx.eax = static_cast<uint32_t>(0x0053a8d4u);
    // 0x004a3a1c: mov ebx, 0x5350b4
    ctx.ebx = static_cast<uint32_t>(0x005350b4u);
    // 0x004a3a21: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a3a23: call 0x40c670
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, 0x004a3a28u);
    sub_0040c670(ctx, mem);
    // 0x004a3a28: cmp eax, edi
    uint32_t t92 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t92);
    // 0x004a3a2a: jne 0x4a3a33
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a3a33;
    goto bb_004a3a2c;
}
bb_004a3a10: {
    // 0x004a3a10: mov eax, 0x20
    ctx.eax = static_cast<uint32_t>(0x00000020u);
    // 0x004a3a15: jmp 0x4a3a3c
    goto bb_004a3a3c;
}
bb_004a3a33: {
    // 0x004a3a33: push eax
    uint32_t t93 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    mem.w32(t93, ctx.eax);
    // 0x004a3a34: call 0x4e0eb7
    uint32_t t94 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t94);
    mem.w32(t94, 0x004a3a39u);
    hle_crt_004e0eb7(ctx, mem);
    // 0x004a3a39: add esp, 4
    uint32_t t95 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t95);
    ctx.esp = static_cast<uint32_t>(t95);
    goto bb_004a3a3c;
}
bb_004a3a2c: {
    // 0x004a3a2c: mov eax, 0x20
    ctx.eax = static_cast<uint32_t>(0x00000020u);
    // 0x004a3a31: jmp 0x4a3a3c
}
bb_004a3a3c: {
    // 0x004a3a3c: cmp eax, 0x20
    uint32_t t96 = static_cast<uint32_t>(ctx.eax - 0x00000020u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000020u, t96);
    // 0x004a3a3f: mov dword ptr [0x54d044], 0x20
    mem.w32(0x0054d044u, 0x00000020u);
    // 0x004a3a49: je 0x4a3a50
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a3a50;
    goto bb_004a3a4b;
}
bb_004a3a50: {
    // 0x004a3a50: mov dword ptr [0x54d044], eax
    mem.w32(0x0054d044u, ctx.eax);
    goto bb_004a3a55;
}
bb_004a3a4b: {
    // 0x004a3a4b: cmp eax, 0x10
    uint32_t t97 = static_cast<uint32_t>(ctx.eax - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000010u, t97);
    // 0x004a3a4e: jne 0x4a3a55
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a3a55;
    goto bb_004a3a50;
}
bb_004a3a55: {
    // 0x004a3a55: cmp dword ptr [esi], edi
    uint32_t t98 = mem.r32(ctx.esi);
    uint32_t t99 = static_cast<uint32_t>(t98 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t98, ctx.edi, t99);
    // 0x004a3a57: je 0x4a3a5d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a3a5d;
    goto bb_004a3a59;
}
bb_004a3a5d: {
    // 0x004a3a5d: mov eax, 0x53a8d8
    ctx.eax = static_cast<uint32_t>(0x0053a8d8u);
    // 0x004a3a62: mov ebx, 0x5350b4
    ctx.ebx = static_cast<uint32_t>(0x005350b4u);
    // 0x004a3a67: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a3a69: call 0x40c670
    uint32_t t100 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t100);
    mem.w32(t100, 0x004a3a6eu);
    sub_0040c670(ctx, mem);
    // 0x004a3a6e: cmp eax, edi
    uint32_t t101 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t101);
    // 0x004a3a70: jne 0x4a3a76
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a3a76;
    goto bb_004a3a72;
}
bb_004a3a59: {
    // 0x004a3a59: xor eax, eax
    uint32_t t102 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t102);
    ctx.eax = static_cast<uint32_t>(t102);
    // 0x004a3a5b: jmp 0x4a3a7f
    goto bb_004a3a7f;
}
bb_004a3a76: {
    // 0x004a3a76: push eax
    uint32_t t103 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    mem.w32(t103, ctx.eax);
    // 0x004a3a77: call 0x4e0eb7
    uint32_t t104 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t104);
    mem.w32(t104, 0x004a3a7cu);
    hle_crt_004e0eb7(ctx, mem);
    // 0x004a3a7c: add esp, 4
    uint32_t t105 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t105);
    ctx.esp = static_cast<uint32_t>(t105);
    goto bb_004a3a7f;
}
bb_004a3a72: {
    // 0x004a3a72: xor eax, eax
    uint32_t t106 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t106);
    ctx.eax = static_cast<uint32_t>(t106);
    // 0x004a3a74: jmp 0x4a3a7f
}
bb_004a3a7f: {
    // 0x004a3a7f: cmp dword ptr [esi], edi
    uint32_t t107 = mem.r32(ctx.esi);
    uint32_t t108 = static_cast<uint32_t>(t107 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t107, ctx.edi, t108);
    // 0x004a3a81: mov dword ptr [0x76e778], eax
    mem.w32(0x0076e778u, ctx.eax);
    // 0x004a3a86: je 0x4a3a8c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a3a8c;
    goto bb_004a3a88;
}
bb_004a3a8c: {
    // 0x004a3a8c: mov eax, 0x53a8e0
    ctx.eax = static_cast<uint32_t>(0x0053a8e0u);
    // 0x004a3a91: mov ebx, 0x5350b4
    ctx.ebx = static_cast<uint32_t>(0x005350b4u);
    // 0x004a3a96: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a3a98: call 0x40c670
    uint32_t t109 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t109);
    mem.w32(t109, 0x004a3a9du);
    sub_0040c670(ctx, mem);
    // 0x004a3a9d: cmp eax, edi
    uint32_t t110 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t110);
    // 0x004a3a9f: jne 0x4a3aa5
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a3aa5;
    goto bb_004a3aa1;
}
bb_004a3a88: {
    // 0x004a3a88: xor eax, eax
    uint32_t t111 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t111);
    ctx.eax = static_cast<uint32_t>(t111);
    // 0x004a3a8a: jmp 0x4a3aae
    goto bb_004a3aae;
}
bb_004a3aa5: {
    // 0x004a3aa5: push eax
    uint32_t t112 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t112);
    mem.w32(t112, ctx.eax);
    // 0x004a3aa6: call 0x4e0eb7
    uint32_t t113 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t113);
    mem.w32(t113, 0x004a3aabu);
    hle_crt_004e0eb7(ctx, mem);
    // 0x004a3aab: add esp, 4
    uint32_t t114 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t114);
    ctx.esp = static_cast<uint32_t>(t114);
    goto bb_004a3aae;
}
bb_004a3aa1: {
    // 0x004a3aa1: xor eax, eax
    uint32_t t115 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t115);
    ctx.eax = static_cast<uint32_t>(t115);
    // 0x004a3aa3: jmp 0x4a3aae
}
bb_004a3aae: {
    // 0x004a3aae: cmp dword ptr [esi], edi
    uint32_t t116 = mem.r32(ctx.esi);
    uint32_t t117 = static_cast<uint32_t>(t116 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t116, ctx.edi, t117);
    // 0x004a3ab0: mov dword ptr [0x76e77c], eax
    mem.w32(0x0076e77cu, ctx.eax);
    // 0x004a3ab5: je 0x4a3ac0
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a3ac0;
    goto bb_004a3ab7;
}
bb_004a3ac0: {
    // 0x004a3ac0: mov eax, 0x53a8e8
    ctx.eax = static_cast<uint32_t>(0x0053a8e8u);
    // 0x004a3ac5: mov ebx, 0x5350b4
    ctx.ebx = static_cast<uint32_t>(0x005350b4u);
    // 0x004a3aca: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a3acc: call 0x40c670
    uint32_t t118 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    mem.w32(t118, 0x004a3ad1u);
    sub_0040c670(ctx, mem);
    // 0x004a3ad1: cmp eax, edi
    uint32_t t119 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t119);
    // 0x004a3ad3: jne 0x4a3ade
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a3ade;
    goto bb_004a3ad5;
}
bb_004a3ab7: {
    // 0x004a3ab7: xor eax, eax
    uint32_t t120 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t120);
    ctx.eax = static_cast<uint32_t>(t120);
    // 0x004a3ab9: mov dword ptr [0x76e774], eax
    mem.w32(0x0076e774u, ctx.eax);
    // 0x004a3abe: jmp 0x4a3b22
    goto bb_004a3b22;
}
bb_004a3ade: {
    // 0x004a3ade: push eax
    uint32_t t121 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t121);
    mem.w32(t121, ctx.eax);
    // 0x004a3adf: call 0x4e0eb7
    uint32_t t122 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t122);
    mem.w32(t122, 0x004a3ae4u);
    hle_crt_004e0eb7(ctx, mem);
    // 0x004a3ae4: add esp, 4
    uint32_t t123 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t123);
    ctx.esp = static_cast<uint32_t>(t123);
    // 0x004a3ae7: mov dword ptr [0x76e774], eax
    mem.w32(0x0076e774u, ctx.eax);
    // 0x004a3aec: jmp 0x4a3b22
    goto bb_004a3b22;
}
bb_004a3ad5: {
    // 0x004a3ad5: xor eax, eax
    uint32_t t124 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t124);
    ctx.eax = static_cast<uint32_t>(t124);
    // 0x004a3ad7: mov dword ptr [0x76e774], eax
    mem.w32(0x0076e774u, ctx.eax);
    // 0x004a3adc: jmp 0x4a3b22
    goto bb_004a3b22;
}
}

// sub_004a3b70 | subsystem=Core/Windows | canonical | 8 blocks | 85 insns
void sub_004a3b70(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a3b70: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x004a3b72: push 0x51393b
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051393bu);
    // 0x004a3b77: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004a3b7d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x004a3b7e: push ecx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ecx);
    // 0x004a3b7f: push ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebx);
    // 0x004a3b80: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x004a3b81: push edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edi);
    // 0x004a3b82: mov eax, dword ptr [0x54b458]
    uint32_t t9 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x004a3b87: xor eax, esp
    uint32_t t10 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x004a3b89: push eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.eax);
    // 0x004a3b8a: lea eax, [esp + 0x14]
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x004a3b8e: mov dword ptr fs:[0], eax
    uint32_t t13 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t13, ctx.eax);
    // 0x004a3b94: push 0x140
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x00000140u);
    // 0x004a3b99: call 0x4e0177
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x004a3b9eu);
    hle_crt_004e0177(ctx, mem);
    // 0x004a3b9e: add esp, 4
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t16);
    ctx.esp = static_cast<uint32_t>(t16);
    // 0x004a3ba1: mov dword ptr [esp + 0x10], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t17, ctx.eax);
    // 0x004a3ba5: test eax, eax
    uint32_t t18 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    // 0x004a3ba7: mov dword ptr [esp + 0x1c], 0
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t19, 0x00000000u);
    // 0x004a3baf: je 0x4a3bbc
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a3bbc;
    goto bb_004a3bb1;
}
bb_004a3bbc: {
    // 0x004a3bbc: xor esi, esi
    uint32_t t20 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t20);
    ctx.esi = static_cast<uint32_t>(t20);
    goto bb_004a3bbe;
}
bb_004a3bb1: {
    // 0x004a3bb1: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004a3bb3: call 0x40c260
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x004a3bb8u);
    sub_0040c260(ctx, mem);
    // 0x004a3bb8: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004a3bba: jmp 0x4a3bbe
}
bb_004a3bbe: {
    // 0x004a3bbe: mov ebx, 0x53a898
    ctx.ebx = static_cast<uint32_t>(0x0053a898u);
    // 0x004a3bc3: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004a3bc5: mov dword ptr [esp + 0x1c], 0xffffffff
    uint32_t t22 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t22, 0xffffffffu);
    // 0x004a3bcd: call 0x40c380
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x004a3bd2u);
    sub_0040c380(ctx, mem);
    // 0x004a3bd2: test eax, eax
    uint32_t t24 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t24);
    // 0x004a3bd4: je 0x4a3c74
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a3c74;
    goto bb_004a3bda;
}
bb_004a3c74: {
    // 0x004a3c74: test esi, esi
    uint32_t t25 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t25);
    // 0x004a3c76: je 0x4a3c7f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a3c7f;
    goto bb_004a3c78;
}
bb_004a3bda: {
    // 0x004a3bda: mov eax, dword ptr [0x76e770]
    uint32_t t26 = mem.r32(0x0076e770u);
    ctx.eax = static_cast<uint32_t>(t26);
    // 0x004a3bdf: push eax
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, ctx.eax);
    // 0x004a3be0: mov ebx, 0x53a8ac
    ctx.ebx = static_cast<uint32_t>(0x0053a8acu);
    // 0x004a3be5: mov edi, 0x5350b4
    ctx.edi = static_cast<uint32_t>(0x005350b4u);
    // 0x004a3bea: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a3bec: call 0x40c8c0
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x004a3bf1u);
    sub_0040c8c0(ctx, mem);
    // 0x004a3bf1: mov ecx, dword ptr [0x54d040]
    uint32_t t29 = mem.r32(0x0054d040u);
    ctx.ecx = static_cast<uint32_t>(t29);
    // 0x004a3bf7: push ecx
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, ctx.ecx);
    // 0x004a3bf8: mov ebx, 0x53a8b8
    ctx.ebx = static_cast<uint32_t>(0x0053a8b8u);
    // 0x004a3bfd: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a3bff: call 0x40c8c0
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x004a3c04u);
    sub_0040c8c0(ctx, mem);
    // 0x004a3c04: mov edx, dword ptr [0x54d048]
    uint32_t t32 = mem.r32(0x0054d048u);
    ctx.edx = static_cast<uint32_t>(t32);
    // 0x004a3c0a: push edx
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, ctx.edx);
    // 0x004a3c0b: mov ebx, 0x53a8c4
    ctx.ebx = static_cast<uint32_t>(0x0053a8c4u);
    // 0x004a3c10: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a3c12: call 0x40c8c0
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x004a3c17u);
    sub_0040c8c0(ctx, mem);
    // 0x004a3c17: mov eax, dword ptr [0x54d04c]
    uint32_t t35 = mem.r32(0x0054d04cu);
    ctx.eax = static_cast<uint32_t>(t35);
    // 0x004a3c1c: push eax
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, ctx.eax);
    // 0x004a3c1d: mov ebx, 0x53a8cc
    ctx.ebx = static_cast<uint32_t>(0x0053a8ccu);
    // 0x004a3c22: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a3c24: call 0x40c8c0
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, 0x004a3c29u);
    sub_0040c8c0(ctx, mem);
    // 0x004a3c29: mov ecx, dword ptr [0x54d044]
    uint32_t t38 = mem.r32(0x0054d044u);
    ctx.ecx = static_cast<uint32_t>(t38);
    // 0x004a3c2f: push ecx
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, ctx.ecx);
    // 0x004a3c30: mov ebx, 0x53a8d4
    ctx.ebx = static_cast<uint32_t>(0x0053a8d4u);
    // 0x004a3c35: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a3c37: call 0x40c8c0
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, 0x004a3c3cu);
    sub_0040c8c0(ctx, mem);
    // 0x004a3c3c: mov edx, dword ptr [0x76e778]
    uint32_t t41 = mem.r32(0x0076e778u);
    ctx.edx = static_cast<uint32_t>(t41);
    // 0x004a3c42: push edx
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, ctx.edx);
    // 0x004a3c43: mov ebx, 0x53a8d8
    ctx.ebx = static_cast<uint32_t>(0x0053a8d8u);
    // 0x004a3c48: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a3c4a: call 0x40c8c0
    uint32_t t43 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    mem.w32(t43, 0x004a3c4fu);
    sub_0040c8c0(ctx, mem);
    // 0x004a3c4f: mov eax, dword ptr [0x76e77c]
    uint32_t t44 = mem.r32(0x0076e77cu);
    ctx.eax = static_cast<uint32_t>(t44);
    // 0x004a3c54: push eax
    uint32_t t45 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    mem.w32(t45, ctx.eax);
    // 0x004a3c55: mov ebx, 0x53a8e0
    ctx.ebx = static_cast<uint32_t>(0x0053a8e0u);
    // 0x004a3c5a: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a3c5c: call 0x40c8c0
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, 0x004a3c61u);
    sub_0040c8c0(ctx, mem);
    // 0x004a3c61: mov ecx, dword ptr [0x76e774]
    uint32_t t47 = mem.r32(0x0076e774u);
    ctx.ecx = static_cast<uint32_t>(t47);
    // 0x004a3c67: push ecx
    uint32_t t48 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    mem.w32(t48, ctx.ecx);
    // 0x004a3c68: mov ebx, 0x53a8e8
    ctx.ebx = static_cast<uint32_t>(0x0053a8e8u);
    // 0x004a3c6d: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a3c6f: call 0x40c8c0
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, 0x004a3c74u);
    sub_0040c8c0(ctx, mem);
    goto bb_004a3c74;
}
bb_004a3c7f: {
    // 0x004a3c7f: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x004a3c84: mov ecx, dword ptr [esp + 0x14]
    uint32_t t50 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t51 = mem.r32(t50);
    ctx.ecx = static_cast<uint32_t>(t51);
    // 0x004a3c88: mov dword ptr fs:[0], ecx
    uint32_t t52 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t52, ctx.ecx);
    // 0x004a3c8f: pop ecx
    uint32_t t53 = ctx.esp;
    uint32_t t54 = mem.r32(t53);
    uint32_t t55 = static_cast<uint32_t>(t53 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    ctx.ecx = static_cast<uint32_t>(t54);
    // 0x004a3c90: pop edi
    uint32_t t56 = ctx.esp;
    uint32_t t57 = mem.r32(t56);
    uint32_t t58 = static_cast<uint32_t>(t56 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    ctx.edi = static_cast<uint32_t>(t57);
    // 0x004a3c91: pop esi
    uint32_t t59 = ctx.esp;
    uint32_t t60 = mem.r32(t59);
    uint32_t t61 = static_cast<uint32_t>(t59 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    ctx.esi = static_cast<uint32_t>(t60);
    // 0x004a3c92: pop ebx
    uint32_t t62 = ctx.esp;
    uint32_t t63 = mem.r32(t62);
    uint32_t t64 = static_cast<uint32_t>(t62 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    ctx.ebx = static_cast<uint32_t>(t63);
    // 0x004a3c93: add esp, 0x10
    uint32_t t65 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t65);
    ctx.esp = static_cast<uint32_t>(t65);
    // 0x004a3c96: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a3c78: {
    // 0x004a3c78: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004a3c7a: call 0x40b480
    uint32_t t66 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    mem.w32(t66, 0x004a3c7fu);
    sub_0040b480(ctx, mem);
    goto bb_004a3c7f;
}
}

// sub_004a3ca0 | subsystem=Core/Windows | canonical | 1 blocks | 11 insns
void sub_004a3ca0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a3ca0: sub esp, 0x14
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000014u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000014u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x004a3ca3: lea eax, [esp]
    ctx.eax = static_cast<uint32_t>(ctx.esp);
    // 0x004a3ca6: push eax
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.eax);
    // 0x004a3ca7: push ecx
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ecx);
    // 0x004a3ca8: call dword ptr [0x51b260]
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x004a3caeu);
    hle_iat_call(ctx, mem, 0x0051b260u);
    // 0x004a3cae: mov edx, dword ptr [esp]
    uint32_t t4 = mem.r32(ctx.esp);
    ctx.edx = static_cast<uint32_t>(t4);
    // 0x004a3cb1: mov eax, dword ptr [esp + 4]
    uint32_t t5 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint32_t t6 = mem.r32(t5);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x004a3cb5: mov dword ptr [0x76e778], edx
    mem.w32(0x0076e778u, ctx.edx);
    // 0x004a3cbb: mov dword ptr [0x76e77c], eax
    mem.w32(0x0076e77cu, ctx.eax);
    // 0x004a3cc0: add esp, 0x14
    uint32_t t7 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000014u, t7);
    ctx.esp = static_cast<uint32_t>(t7);
    // 0x004a3cc3: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004a3ec0 | subsystem=Core/Windows | canonical | 1 blocks | 33 insns
void sub_004a3ec0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a3ec0: sub esp, 0x14
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000014u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000014u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x004a3ec3: mov eax, dword ptr [esi]
    uint32_t t1 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x004a3ec5: xor ecx, ecx
    uint32_t t2 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.ecx = static_cast<uint32_t>(t2);
    // 0x004a3ec7: cmp dword ptr [esp + 0x18], ecx
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t4 - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t4, ctx.ecx, t5);
    // 0x004a3ecb: push edi
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.edi);
    // 0x004a3ecc: mov edi, dword ptr [0x51b260]
    uint32_t t7 = mem.r32(0x0051b260u);
    ctx.edi = static_cast<uint32_t>(t7);
    // 0x004a3ed2: setne cl
    uint8_t t8 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::NE) ? 1u : 0u);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t8));
    // 0x004a3ed5: lea edx, [esp + 8]
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.edx = static_cast<uint32_t>(t9);
    // 0x004a3ed9: push edx
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.edx);
    // 0x004a3eda: push eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.eax);
    // 0x004a3edb: mov dword ptr [esp + 0xc], eax
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t12, ctx.eax);
    // 0x004a3edf: mov dword ptr [0x54d040], ecx
    mem.w32(0x0054d040u, ctx.ecx);
    // 0x004a3ee5: call edi
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x004a3ee7u);
    call_indirect(ctx, mem, ctx.edi);
    // 0x004a3ee7: mov eax, dword ptr [esp + 8]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t15 = mem.r32(t14);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x004a3eeb: mov ecx, dword ptr [esp + 0xc]
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t17 = mem.r32(t16);
    ctx.ecx = static_cast<uint32_t>(t17);
    // 0x004a3eef: mov dword ptr [0x76e778], eax
    mem.w32(0x0076e778u, ctx.eax);
    // 0x004a3ef4: lea eax, [esp + 4]
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    ctx.eax = static_cast<uint32_t>(t18);
    // 0x004a3ef8: mov dword ptr [0x76e77c], ecx
    mem.w32(0x0076e77cu, ctx.ecx);
    // 0x004a3efe: call 0x40d960
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x004a3f03u);
    sub_0040d960(ctx, mem);
    // 0x004a3f03: mov eax, dword ptr [esi]
    uint32_t t20 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t20);
    // 0x004a3f05: lea edx, [esp + 8]
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.edx = static_cast<uint32_t>(t21);
    // 0x004a3f09: push edx
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, ctx.edx);
    // 0x004a3f0a: push eax
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, ctx.eax);
    // 0x004a3f0b: call edi
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x004a3f0du);
    call_indirect(ctx, mem, ctx.edi);
    // 0x004a3f0d: mov ecx, dword ptr [esp + 8]
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t26 = mem.r32(t25);
    ctx.ecx = static_cast<uint32_t>(t26);
    // 0x004a3f11: mov edx, dword ptr [esp + 0xc]
    uint32_t t27 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t28 = mem.r32(t27);
    ctx.edx = static_cast<uint32_t>(t28);
    // 0x004a3f15: mov dword ptr [0x76e778], ecx
    mem.w32(0x0076e778u, ctx.ecx);
    // 0x004a3f1b: mov dword ptr [0x76e77c], edx
    mem.w32(0x0076e77cu, ctx.edx);
    // 0x004a3f21: call 0x4a3b70
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x004a3f26u);
    sub_004a3b70(ctx, mem);
    // 0x004a3f26: mov al, 1
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(uint8_t{0x01u}));
    // 0x004a3f28: pop edi
    uint32_t t30 = ctx.esp;
    uint32_t t31 = mem.r32(t30);
    uint32_t t32 = static_cast<uint32_t>(t30 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    ctx.edi = static_cast<uint32_t>(t31);
    // 0x004a3f29: add esp, 0x14
    uint32_t t33 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000014u, t33);
    ctx.esp = static_cast<uint32_t>(t33);
    // 0x004a3f2c: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004bbfa0 | subsystem=Core/Windows | canonical | 8 blocks | 48 insns
void sub_004bbfa0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004bbfa0: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x004bbfa1: mov ebp, dword ptr [esp + 8]
    uint32_t t1 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t2 = mem.r32(t1);
    ctx.ebp = static_cast<uint32_t>(t2);
    // 0x004bbfa5: push esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.esi);
    // 0x004bbfa6: push edi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.edi);
    // 0x004bbfa7: push 0x148
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, 0x00000148u);
    // 0x004bbfac: xor edi, edi
    uint32_t t6 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t6);
    ctx.edi = static_cast<uint32_t>(t6);
    // 0x004bbfae: push edi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.edi);
    // 0x004bbfaf: push ebp
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.ebp);
    // 0x004bbfb0: call 0x4e6340
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x004bbfb5u);
    hle_crt_004e6340(ctx, mem);
    // 0x004bbfb5: add esp, 0xc
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t10);
    ctx.esp = static_cast<uint32_t>(t10);
    // 0x004bbfb8: mov dword ptr [ebp], 0xfff00002
    mem.w32(ctx.ebp, 0xfff00002u);
    // 0x004bbfbf: xor esi, esi
    uint32_t t11 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    ctx.esi = static_cast<uint32_t>(t11);
}
bb_004bbfc1: {
    // 0x004bbfc1: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004bbfc3: shl eax, 5
    uint32_t t12 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x05u}) & 0x0000001fu);
    uint32_t t13 = recomp_detail::shl<uint32_t>(ctx.eax, t12);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.eax, t12, t13);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x004bbfc6: cmp esi, edi
    uint32_t t14 = static_cast<uint32_t>(ctx.esi - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edi, t14);
    // 0x004bbfc8: lea ecx, [eax + ebp + 8]
    uint32_t t15 = static_cast<uint32_t>(ctx.eax + ctx.ebp);
    uint32_t t16 = static_cast<uint32_t>(t15 + 0x00000008u);
    ctx.ecx = static_cast<uint32_t>(t16);
    // 0x004bbfcc: jne 0x4bbfd9
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004bbfd9;
    goto bb_004bbfce;
}
bb_004bbfd9: {
    // 0x004bbfd9: cmp esi, 1
    uint32_t t17 = static_cast<uint32_t>(ctx.esi - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00000001u, t17);
    // 0x004bbfdc: jne 0x4bbfe9
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004bbfe9;
    goto bb_004bbfde;
}
bb_004bbfce: {
    // 0x004bbfce: mov dword ptr [ecx], 0xd0fc0
    mem.w32(ctx.ecx, 0x000d0fc0u);
    // 0x004bbfd4: mov dword ptr [ecx + 4], edi
    uint32_t t18 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    mem.w32(t18, ctx.edi);
    // 0x004bbfd7: jmp 0x4bbffc
    goto bb_004bbffc;
}
bb_004bbfe9: {
    // 0x004bbfe9: mov eax, 0x14
    ctx.eax = static_cast<uint32_t>(0x00000014u);
    // 0x004bbfee: sub eax, esi
    uint32_t t19 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t19);
    ctx.eax = static_cast<uint32_t>(t19);
    // 0x004bbff0: imul eax, eax, 0x3a98
    uint64_t t20 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(0x00003a98u)));
    uint32_t t21 = static_cast<uint32_t>(t20);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t20);
    ctx.eax = static_cast<uint32_t>(t21);
    // 0x004bbff6: cdq
    uint32_t t22 = recomp_detail::sar<uint32_t>(ctx.eax, 0x0000001fu);
    ctx.edx = static_cast<uint32_t>(t22);
    // 0x004bbff7: mov dword ptr [ecx], eax
    mem.w32(ctx.ecx, ctx.eax);
    // 0x004bbff9: mov dword ptr [ecx + 4], edx
    uint32_t t23 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    mem.w32(t23, ctx.edx);
    goto bb_004bbffc;
}
bb_004bbfde: {
    // 0x004bbfde: mov dword ptr [ecx], 0xa2be8
    mem.w32(ctx.ecx, 0x000a2be8u);
    // 0x004bbfe4: mov dword ptr [ecx + 4], edi
    uint32_t t24 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    mem.w32(t24, ctx.edi);
    // 0x004bbfe7: jmp 0x4bbffc
}
bb_004bbffc: {
    // 0x004bbffc: mov eax, 0xaaaaaaab
    ctx.eax = static_cast<uint32_t>(0xaaaaaaabu);
    // 0x004bc001: mul esi
    uint64_t t25 = (static_cast<uint64_t>(ctx.eax) * static_cast<uint64_t>(ctx.esi));
    uint32_t t26 = static_cast<uint32_t>(t25);
    uint32_t t27 = static_cast<uint32_t>(t25 >> 32);
    ctx.eax = static_cast<uint32_t>(t26);
    ctx.edx = static_cast<uint32_t>(t27);
    recomp_detail::update_flags_mul<uint32_t>(ctx, t25);
    // 0x004bc003: shr edx, 1
    uint32_t t28 = static_cast<uint32_t>(0x00000001u & 0x0000001fu);
    uint32_t t29 = recomp_detail::shr<uint32_t>(ctx.edx, t28);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.edx, t28, t29);
    ctx.edx = static_cast<uint32_t>(t29);
    // 0x004bc005: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004bc007: mov dword ptr [ecx + 0x10], esi
    uint32_t t30 = static_cast<uint32_t>(ctx.ecx + 0x00000010u);
    mem.w32(t30, ctx.esi);
    // 0x004bc00a: lea edx, [edx + edx*2]
    uint32_t t31 = recomp_detail::shl<uint32_t>(ctx.edx, 0x00000001u);
    uint32_t t32 = static_cast<uint32_t>(ctx.edx + t31);
    ctx.edx = static_cast<uint32_t>(t32);
    // 0x004bc00d: sub eax, edx
    uint32_t t33 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t33);
    ctx.eax = static_cast<uint32_t>(t33);
    // 0x004bc00f: add esi, 1
    uint32_t t34 = static_cast<uint32_t>(ctx.esi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000001u, t34);
    ctx.esi = static_cast<uint32_t>(t34);
    // 0x004bc012: cmp esi, 0xa
    uint32_t t35 = static_cast<uint32_t>(ctx.esi - 0x0000000au);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x0000000au, t35);
    // 0x004bc015: mov dword ptr [ecx + 0x14], eax
    uint32_t t36 = static_cast<uint32_t>(ctx.ecx + 0x00000014u);
    mem.w32(t36, ctx.eax);
    // 0x004bc018: mov dword ptr [ecx + 0x18], edi
    uint32_t t37 = static_cast<uint32_t>(ctx.ecx + 0x00000018u);
    mem.w32(t37, ctx.edi);
    // 0x004bc01b: mov dword ptr [ecx + 8], 0x41424d
    uint32_t t38 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    mem.w32(t38, 0x0041424du);
    // 0x004bc022: jl 0x4bbfc1
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004bbfc1;
}
{
    // 0x004bc024: pop edi
    uint32_t t39 = ctx.esp;
    uint32_t t40 = mem.r32(t39);
    uint32_t t41 = static_cast<uint32_t>(t39 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    ctx.edi = static_cast<uint32_t>(t40);
    // 0x004bc025: pop esi
    uint32_t t42 = ctx.esp;
    uint32_t t43 = mem.r32(t42);
    uint32_t t44 = static_cast<uint32_t>(t42 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    ctx.esi = static_cast<uint32_t>(t43);
    // 0x004bc026: pop ebp
    uint32_t t45 = ctx.esp;
    uint32_t t46 = mem.r32(t45);
    uint32_t t47 = static_cast<uint32_t>(t45 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    ctx.ebp = static_cast<uint32_t>(t46);
    // 0x004bc027: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004bf970 | subsystem=Core/Windows | canonical | 14 blocks | 40 insns
void sub_004bf970(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004bf970: cmp dword ptr [0x76743c], 0
    uint32_t t0 = mem.r32(0x0076743cu);
    uint32_t t1 = static_cast<uint32_t>(t0 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t0, 0x00000000u, t1);
    // 0x004bf977: je 0x4bf9e2
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004bf9e2;
    goto bb_004bf979;
}
bb_004bf9e2: {
    // 0x004bf9e2: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004bf979: {
    // 0x004bf979: push edi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.edi);
    // 0x004bf97a: mov edi, dword ptr [0x767438]
    uint32_t t3 = mem.r32(0x00767438u);
    ctx.edi = static_cast<uint32_t>(t3);
    // 0x004bf980: mov eax, dword ptr [edi + 0xc]
    uint32_t t4 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    uint32_t t5 = mem.r32(t4);
    ctx.eax = static_cast<uint32_t>(t5);
    // 0x004bf983: test eax, eax
    uint32_t t6 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t6);
    // 0x004bf985: je 0x4bf9e1
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004bf9e1;
    goto bb_004bf987;
}
bb_004bf9e1: {
    // 0x004bf9e1: pop edi
    uint32_t t7 = ctx.esp;
    uint32_t t8 = mem.r32(t7);
    uint32_t t9 = static_cast<uint32_t>(t7 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    ctx.edi = static_cast<uint32_t>(t8);
    goto bb_004bf9e2;
}
bb_004bf987: {
    // 0x004bf987: push ebx
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.ebx);
    // 0x004bf988: xor ebx, ebx
    uint32_t t11 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    ctx.ebx = static_cast<uint32_t>(t11);
    // 0x004bf98a: test eax, eax
    uint32_t t12 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t12);
    // 0x004bf98c: jbe 0x4bf9cf
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_004bf9cf;
    goto bb_004bf98e;
}
bb_004bf9cf: {
    // 0x004bf9cf: mov dword ptr [edi + 0xc], 0
    uint32_t t13 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    mem.w32(t13, 0x00000000u);
    // 0x004bf9d6: mov dword ptr [0x54c978], 0xffffffff
    mem.w32(0x0054c978u, 0xffffffffu);
    // 0x004bf9e0: pop ebx
    uint32_t t14 = ctx.esp;
    uint32_t t15 = mem.r32(t14);
    uint32_t t16 = static_cast<uint32_t>(t14 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    ctx.ebx = static_cast<uint32_t>(t15);
    goto bb_004bf9e1;
}
bb_004bf98e: {
    // 0x004bf98e: push esi
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, ctx.esi);
    // 0x004bf98f: nop
}
bb_004bf990: {
    // 0x004bf990: cmp dword ptr [edi], 0
    uint32_t t18 = mem.r32(ctx.edi);
    uint32_t t19 = static_cast<uint32_t>(t18 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t18, 0x00000000u, t19);
    // 0x004bf993: jne 0x4bf9a0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004bf9a0;
    goto bb_004bf995;
}
bb_004bf9a0: {
    // 0x004bf9a0: mov eax, dword ptr [edi + 4]
    uint32_t t20 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    uint32_t t21 = mem.r32(t20);
    ctx.eax = static_cast<uint32_t>(t21);
    // 0x004bf9a3: mov esi, dword ptr [eax + ebx*4]
    uint32_t t22 = recomp_detail::shl<uint32_t>(ctx.ebx, 0x00000002u);
    uint32_t t23 = static_cast<uint32_t>(ctx.eax + t22);
    uint32_t t24 = mem.r32(t23);
    ctx.esi = static_cast<uint32_t>(t24);
    goto bb_004bf9a6;
}
bb_004bf995: {
    // 0x004bf995: mov esi, dword ptr [edi + 8]
    uint32_t t25 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t26 = mem.r32(t25);
    ctx.esi = static_cast<uint32_t>(t26);
    // 0x004bf998: imul esi, ebx
    uint64_t t27 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.esi)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ebx)));
    uint32_t t28 = static_cast<uint32_t>(t27);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t27);
    ctx.esi = static_cast<uint32_t>(t28);
    // 0x004bf99b: add esi, dword ptr [edi + 4]
    uint32_t t29 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    uint32_t t30 = mem.r32(t29);
    uint32_t t31 = static_cast<uint32_t>(ctx.esi + t30);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, t30, t31);
    ctx.esi = static_cast<uint32_t>(t31);
    // 0x004bf99e: jmp 0x4bf9a6
}
bb_004bf9a6: {
    // 0x004bf9a6: mov eax, dword ptr [esi + 8]
    uint32_t t32 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t33 = mem.r32(t32);
    ctx.eax = static_cast<uint32_t>(t33);
    // 0x004bf9a9: test eax, eax
    uint32_t t34 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t34);
    // 0x004bf9ab: je 0x4bf9bd
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004bf9bd;
    goto bb_004bf9ad;
}
bb_004bf9bd: {
    // 0x004bf9bd: push esi
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, ctx.esi);
    // 0x004bf9be: call 0x4e00d0
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, 0x004bf9c3u);
    hle_crt_004e00d0(ctx, mem);
    // 0x004bf9c3: add ebx, 1
    uint32_t t37 = static_cast<uint32_t>(ctx.ebx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebx, 0x00000001u, t37);
    ctx.ebx = static_cast<uint32_t>(t37);
    // 0x004bf9c6: add esp, 4
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t38);
    ctx.esp = static_cast<uint32_t>(t38);
    // 0x004bf9c9: cmp ebx, dword ptr [edi + 0xc]
    uint32_t t39 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    uint32_t t40 = mem.r32(t39);
    uint32_t t41 = static_cast<uint32_t>(ctx.ebx - t40);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, t40, t41);
    // 0x004bf9cc: jb 0x4bf990
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004bf990;
    goto bb_004bf9ce;
}
bb_004bf9ad: {
    // 0x004bf9ad: push eax
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, ctx.eax);
    // 0x004bf9ae: call 0x4e00d0
    uint32_t t43 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    mem.w32(t43, 0x004bf9b3u);
    hle_crt_004e00d0(ctx, mem);
    // 0x004bf9b3: add esp, 4
    uint32_t t44 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t44);
    ctx.esp = static_cast<uint32_t>(t44);
    // 0x004bf9b6: mov dword ptr [esi + 8], 0
    uint32_t t45 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t45, 0x00000000u);
    goto bb_004bf9bd;
}
bb_004bf9ce: {
    // 0x004bf9ce: pop esi
    uint32_t t46 = ctx.esp;
    uint32_t t47 = mem.r32(t46);
    uint32_t t48 = static_cast<uint32_t>(t46 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    ctx.esi = static_cast<uint32_t>(t47);
    goto bb_004bf9cf;
}
}

// sub_004c0cf0 | subsystem=Core/Windows | canonical | 72 blocks | 141 insns
void sub_004c0cf0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004c0cf0: cmp eax, 0x3154454d
    uint32_t t0 = static_cast<uint32_t>(ctx.eax - 0x3154454du);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x3154454du, t0);
    // 0x004c0cf5: jg 0x4c0e2f
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_004c0e2f;
    goto bb_004c0cfb;
}
bb_004c0e2f: {
    // 0x004c0e2f: cmp eax, 0x34545844
    uint32_t t1 = static_cast<uint32_t>(ctx.eax - 0x34545844u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x34545844u, t1);
    // 0x004c0e34: jg 0x4c0e74
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_004c0e74;
    goto bb_004c0e36;
}
bb_004c0cfb: {
    // 0x004c0cfb: je 0x4c0e29
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004c0e29;
    goto bb_004c0d01;
}
bb_004c0e74: {
    // 0x004c0e74: cmp eax, 0x47424752
    uint32_t t2 = static_cast<uint32_t>(ctx.eax - 0x47424752u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x47424752u, t2);
    // 0x004c0e79: jg 0x4c0e9d
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_004c0e9d;
    goto bb_004c0e7b;
}
bb_004c0e36: {
    // 0x004c0e36: je 0x4c0e6e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004c0e6e;
    goto bb_004c0e38;
}
bb_004c0e29: {
    // 0x004c0e29: mov eax, 0x53b8ec
    ctx.eax = static_cast<uint32_t>(0x0053b8ecu);
    // 0x004c0e2e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d01: {
    // 0x004c0d01: add eax, -0x14
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0xffffffecu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0xffffffecu, t3);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004c0d04: cmp eax, 0x61
    uint32_t t4 = static_cast<uint32_t>(ctx.eax - 0x00000061u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000061u, t4);
    // 0x004c0d07: ja 0x4c0ea4
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_004c0ea4;
    goto bb_004c0d0d;
}
bb_004c0e9d: {
    // 0x004c0e9d: cmp eax, 0x59565955
    uint32_t t5 = static_cast<uint32_t>(ctx.eax - 0x59565955u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x59565955u, t5);
    // 0x004c0ea2: je 0x4c0eaa
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004c0eaa;
    goto bb_004c0ea4;
}
bb_004c0e7b: {
    // 0x004c0e7b: je 0x4c0e97
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004c0e97;
    goto bb_004c0e7d;
}
bb_004c0e6e: {
    // 0x004c0e6e: mov eax, 0x53b94c
    ctx.eax = static_cast<uint32_t>(0x0053b94cu);
    // 0x004c0e73: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0e38: {
    // 0x004c0e38: cmp eax, 0x32595559
    uint32_t t6 = static_cast<uint32_t>(ctx.eax - 0x32595559u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x32595559u, t6);
    // 0x004c0e3d: jg 0x4c0e61
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_004c0e61;
    goto bb_004c0e3f;
}
bb_004c0ea4: {
    // 0x004c0ea4: mov eax, 0x53baac
    ctx.eax = static_cast<uint32_t>(0x0053baacu);
    // 0x004c0ea9: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d0d: {
    // 0x004c0d0d: movzx eax, byte ptr [eax + 0x4c0f68]
    uint32_t t7 = static_cast<uint32_t>(ctx.eax + 0x004c0f68u);
    uint8_t t8 = mem.r8(t7);
    uint32_t t9 = static_cast<uint32_t>(static_cast<uint8_t>(t8));
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x004c0d14: jmp dword ptr [eax*4 + 0x4c0eb0]
    switch (ctx.eax) {
        case 0u: goto bb_004c0d1b;
        case 1u: goto bb_004c0d21;
        case 2u: goto bb_004c0d27;
        case 3u: goto bb_004c0d2d;
        case 4u: goto bb_004c0d33;
        case 5u: goto bb_004c0d39;
        case 6u: goto bb_004c0d3f;
        case 7u: goto bb_004c0d45;
        case 8u: goto bb_004c0d4b;
        case 9u: goto bb_004c0d51;
        case 10u: goto bb_004c0d57;
        case 11u: goto bb_004c0d5d;
        case 12u: goto bb_004c0d63;
        case 13u: goto bb_004c0d69;
        case 14u: goto bb_004c0d6f;
        case 15u: goto bb_004c0d75;
        case 16u: goto bb_004c0d81;
        case 17u: goto bb_004c0d87;
        case 18u: goto bb_004c0d8d;
        case 19u: goto bb_004c0dab;
        case 20u: goto bb_004c0db1;
        case 21u: goto bb_004c0d93;
        case 22u: goto bb_004c0d99;
        case 23u: goto bb_004c0db7;
        case 24u: goto bb_004c0dbd;
        case 25u: goto bb_004c0dc3;
        case 26u: goto bb_004c0dc9;
        case 27u: goto bb_004c0dcf;
        case 28u: goto bb_004c0dd5;
        case 29u: goto bb_004c0ddb;
        case 30u: goto bb_004c0ded;
        case 31u: goto bb_004c0d7b;
        case 32u: goto bb_004c0de1;
        case 33u: goto bb_004c0de7;
        case 34u: goto bb_004c0df3;
        case 35u: goto bb_004c0df9;
        case 36u: goto bb_004c0dff;
        case 37u: goto bb_004c0d9f;
        case 38u: goto bb_004c0e05;
        case 39u: goto bb_004c0e0b;
        case 40u: goto bb_004c0e11;
        case 41u: goto bb_004c0e17;
        case 42u: goto bb_004c0e1d;
        case 43u: goto bb_004c0e23;
        case 44u: goto bb_004c0da5;
        case 45u: goto bb_004c0ea4;
        default: recomp_detail::trap_halt(ctx, 0x004c0eb0u, "switch_oob"); return;
    }
}
bb_004c0eaa: {
    // 0x004c0eaa: mov eax, 0x53b964
    ctx.eax = static_cast<uint32_t>(0x0053b964u);
    // 0x004c0eaf: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0e97: {
    // 0x004c0e97: mov eax, 0x53b914
    ctx.eax = static_cast<uint32_t>(0x0053b914u);
    // 0x004c0e9c: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0e7d: {
    // 0x004c0e7d: cmp eax, 0x35545844
    uint32_t t10 = static_cast<uint32_t>(ctx.eax - 0x35545844u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x35545844u, t10);
    // 0x004c0e82: je 0x4c0e91
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004c0e91;
    goto bb_004c0e84;
}
bb_004c0e61: {
    // 0x004c0e61: cmp eax, 0x33545844
    uint32_t t11 = static_cast<uint32_t>(ctx.eax - 0x33545844u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x33545844u, t11);
    // 0x004c0e66: jne 0x4c0ea4
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004c0ea4;
    goto bb_004c0e68;
}
bb_004c0e3f: {
    // 0x004c0e3f: je 0x4c0e5b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004c0e5b;
    goto bb_004c0e41;
}
bb_004c0d1b: {
    // 0x004c0d1b: mov eax, 0x53b750
    ctx.eax = static_cast<uint32_t>(0x0053b750u);
    // 0x004c0d20: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d21: {
    // 0x004c0d21: mov eax, 0x53b760
    ctx.eax = static_cast<uint32_t>(0x0053b760u);
    // 0x004c0d26: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d27: {
    // 0x004c0d27: mov eax, 0x53b770
    ctx.eax = static_cast<uint32_t>(0x0053b770u);
    // 0x004c0d2c: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d2d: {
    // 0x004c0d2d: mov eax, 0x53b780
    ctx.eax = static_cast<uint32_t>(0x0053b780u);
    // 0x004c0d32: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d33: {
    // 0x004c0d33: mov eax, 0x53b790
    ctx.eax = static_cast<uint32_t>(0x0053b790u);
    // 0x004c0d38: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d39: {
    // 0x004c0d39: mov eax, 0x53b7a0
    ctx.eax = static_cast<uint32_t>(0x0053b7a0u);
    // 0x004c0d3e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d3f: {
    // 0x004c0d3f: mov eax, 0x53b7b0
    ctx.eax = static_cast<uint32_t>(0x0053b7b0u);
    // 0x004c0d44: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d45: {
    // 0x004c0d45: mov eax, 0x53b7c0
    ctx.eax = static_cast<uint32_t>(0x0053b7c0u);
    // 0x004c0d4a: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d4b: {
    // 0x004c0d4b: mov eax, 0x53b7d0
    ctx.eax = static_cast<uint32_t>(0x0053b7d0u);
    // 0x004c0d50: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d51: {
    // 0x004c0d51: mov eax, 0x53b7dc
    ctx.eax = static_cast<uint32_t>(0x0053b7dcu);
    // 0x004c0d56: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d57: {
    // 0x004c0d57: mov eax, 0x53b7ec
    ctx.eax = static_cast<uint32_t>(0x0053b7ecu);
    // 0x004c0d5c: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d5d: {
    // 0x004c0d5d: mov eax, 0x53b7fc
    ctx.eax = static_cast<uint32_t>(0x0053b7fcu);
    // 0x004c0d62: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d63: {
    // 0x004c0d63: mov eax, 0x53b810
    ctx.eax = static_cast<uint32_t>(0x0053b810u);
    // 0x004c0d68: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d69: {
    // 0x004c0d69: mov eax, 0x53b820
    ctx.eax = static_cast<uint32_t>(0x0053b820u);
    // 0x004c0d6e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d6f: {
    // 0x004c0d6f: mov eax, 0x53b82c
    ctx.eax = static_cast<uint32_t>(0x0053b82cu);
    // 0x004c0d74: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d75: {
    // 0x004c0d75: mov eax, 0x53b838
    ctx.eax = static_cast<uint32_t>(0x0053b838u);
    // 0x004c0d7a: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d81: {
    // 0x004c0d81: mov eax, 0x53b850
    ctx.eax = static_cast<uint32_t>(0x0053b850u);
    // 0x004c0d86: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d87: {
    // 0x004c0d87: mov eax, 0x53b85c
    ctx.eax = static_cast<uint32_t>(0x0053b85cu);
    // 0x004c0d8c: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d8d: {
    // 0x004c0d8d: mov eax, 0x53b868
    ctx.eax = static_cast<uint32_t>(0x0053b868u);
    // 0x004c0d92: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0dab: {
    // 0x004c0dab: mov eax, 0x53b8b8
    ctx.eax = static_cast<uint32_t>(0x0053b8b8u);
    // 0x004c0db0: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0db1: {
    // 0x004c0db1: mov eax, 0x53b8c8
    ctx.eax = static_cast<uint32_t>(0x0053b8c8u);
    // 0x004c0db6: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d93: {
    // 0x004c0d93: mov eax, 0x53b874
    ctx.eax = static_cast<uint32_t>(0x0053b874u);
    // 0x004c0d98: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d99: {
    // 0x004c0d99: mov eax, 0x53b884
    ctx.eax = static_cast<uint32_t>(0x0053b884u);
    // 0x004c0d9e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0db7: {
    // 0x004c0db7: mov eax, 0x53b8d8
    ctx.eax = static_cast<uint32_t>(0x0053b8d8u);
    // 0x004c0dbc: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0dbd: {
    // 0x004c0dbd: mov eax, 0x53b97c
    ctx.eax = static_cast<uint32_t>(0x0053b97cu);
    // 0x004c0dc2: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0dc3: {
    // 0x004c0dc3: mov eax, 0x53b990
    ctx.eax = static_cast<uint32_t>(0x0053b990u);
    // 0x004c0dc8: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0dc9: {
    // 0x004c0dc9: mov eax, 0x53b99c
    ctx.eax = static_cast<uint32_t>(0x0053b99cu);
    // 0x004c0dce: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0dcf: {
    // 0x004c0dcf: mov eax, 0x53b9ac
    ctx.eax = static_cast<uint32_t>(0x0053b9acu);
    // 0x004c0dd4: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0dd5: {
    // 0x004c0dd5: mov eax, 0x53b9bc
    ctx.eax = static_cast<uint32_t>(0x0053b9bcu);
    // 0x004c0dda: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0ddb: {
    // 0x004c0ddb: mov eax, 0x53b9cc
    ctx.eax = static_cast<uint32_t>(0x0053b9ccu);
    // 0x004c0de0: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0ded: {
    // 0x004c0ded: mov eax, 0x53ba04
    ctx.eax = static_cast<uint32_t>(0x0053ba04u);
    // 0x004c0df2: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d7b: {
    // 0x004c0d7b: mov eax, 0x53b844
    ctx.eax = static_cast<uint32_t>(0x0053b844u);
    // 0x004c0d80: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0de1: {
    // 0x004c0de1: mov eax, 0x53b9dc
    ctx.eax = static_cast<uint32_t>(0x0053b9dcu);
    // 0x004c0de6: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0de7: {
    // 0x004c0de7: mov eax, 0x53b9f4
    ctx.eax = static_cast<uint32_t>(0x0053b9f4u);
    // 0x004c0dec: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0df3: {
    // 0x004c0df3: mov eax, 0x53ba10
    ctx.eax = static_cast<uint32_t>(0x0053ba10u);
    // 0x004c0df8: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0df9: {
    // 0x004c0df9: mov eax, 0x53ba24
    ctx.eax = static_cast<uint32_t>(0x0053ba24u);
    // 0x004c0dfe: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0dff: {
    // 0x004c0dff: mov eax, 0x53ba34
    ctx.eax = static_cast<uint32_t>(0x0053ba34u);
    // 0x004c0e04: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0d9f: {
    // 0x004c0d9f: mov eax, 0x53b894
    ctx.eax = static_cast<uint32_t>(0x0053b894u);
    // 0x004c0da4: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0e05: {
    // 0x004c0e05: mov eax, 0x53ba44
    ctx.eax = static_cast<uint32_t>(0x0053ba44u);
    // 0x004c0e0a: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0e0b: {
    // 0x004c0e0b: mov eax, 0x53ba50
    ctx.eax = static_cast<uint32_t>(0x0053ba50u);
    // 0x004c0e10: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0e11: {
    // 0x004c0e11: mov eax, 0x53ba60
    ctx.eax = static_cast<uint32_t>(0x0053ba60u);
    // 0x004c0e16: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0e17: {
    // 0x004c0e17: mov eax, 0x53ba78
    ctx.eax = static_cast<uint32_t>(0x0053ba78u);
    // 0x004c0e1c: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0e1d: {
    // 0x004c0e1d: mov eax, 0x53ba84
    ctx.eax = static_cast<uint32_t>(0x0053ba84u);
    // 0x004c0e22: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0e23: {
    // 0x004c0e23: mov eax, 0x53ba94
    ctx.eax = static_cast<uint32_t>(0x0053ba94u);
    // 0x004c0e28: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0da5: {
    // 0x004c0da5: mov eax, 0x53b8a8
    ctx.eax = static_cast<uint32_t>(0x0053b8a8u);
    // 0x004c0daa: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0e91: {
    // 0x004c0e91: mov eax, 0x53b958
    ctx.eax = static_cast<uint32_t>(0x0053b958u);
    // 0x004c0e96: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0e84: {
    // 0x004c0e84: cmp eax, 0x42475247
    uint32_t t12 = static_cast<uint32_t>(ctx.eax - 0x42475247u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x42475247u, t12);
    // 0x004c0e89: jne 0x4c0ea4
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004c0ea4;
    goto bb_004c0e8b;
}
bb_004c0e68: {
    // 0x004c0e68: mov eax, 0x53b940
    ctx.eax = static_cast<uint32_t>(0x0053b940u);
    // 0x004c0e6d: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0e5b: {
    // 0x004c0e5b: mov eax, 0x53b970
    ctx.eax = static_cast<uint32_t>(0x0053b970u);
    // 0x004c0e60: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0e41: {
    // 0x004c0e41: cmp eax, 0x31545844
    uint32_t t13 = static_cast<uint32_t>(ctx.eax - 0x31545844u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x31545844u, t13);
    // 0x004c0e46: je 0x4c0e55
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004c0e55;
    goto bb_004c0e48;
}
bb_004c0e8b: {
    // 0x004c0e8b: mov eax, 0x53b900
    ctx.eax = static_cast<uint32_t>(0x0053b900u);
    // 0x004c0e90: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0e55: {
    // 0x004c0e55: mov eax, 0x53b928
    ctx.eax = static_cast<uint32_t>(0x0053b928u);
    // 0x004c0e5a: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004c0e48: {
    // 0x004c0e48: cmp eax, 0x32545844
    uint32_t t14 = static_cast<uint32_t>(ctx.eax - 0x32545844u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x32545844u, t14);
    // 0x004c0e4d: jne 0x4c0ea4
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004c0ea4;
}
{
    // 0x004c0e4f: mov eax, 0x53b934
    ctx.eax = static_cast<uint32_t>(0x0053b934u);
    // 0x004c0e54: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004de300 | subsystem=Core/Windows | canonical | 7 blocks | 27 insns
void sub_004de300(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004de300: push ebx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebx);
    // 0x004de301: xor ecx, ecx
    uint32_t t1 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.ecx = static_cast<uint32_t>(t1);
    // 0x004de303: xor edx, edx
    uint32_t t2 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.edx = static_cast<uint32_t>(t2);
    // 0x004de305: push esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.esi);
}
bb_004de306: {
    // 0x004de306: movzx eax, cx
    uint32_t t4 = static_cast<uint32_t>(static_cast<uint16_t>(recomp_detail::r16(ctx.ecx)));
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x004de309: xor ecx, ecx
    uint32_t t5 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    ctx.ecx = static_cast<uint32_t>(t5);
    // 0x004de30b: mov ch, byte ptr [edx + edi]
    uint32_t t6 = static_cast<uint32_t>(ctx.edx + ctx.edi);
    uint8_t t7 = mem.r8(t6);
    recomp_detail::w8h(ctx.ecx, static_cast<uint8_t>(t7));
    // 0x004de30e: mov si, 8
    recomp_detail::w16(ctx.esi, static_cast<uint16_t>(uint16_t{0x0008u}));
    // 0x004de312: movzx ecx, cx
    uint32_t t8 = static_cast<uint32_t>(static_cast<uint16_t>(recomp_detail::r16(ctx.ecx)));
    ctx.ecx = static_cast<uint32_t>(t8);
}
bb_004de315: {
    // 0x004de315: mov ebx, ecx
    ctx.ebx = static_cast<uint32_t>(ctx.ecx);
    // 0x004de317: xor ebx, eax
    uint32_t t9 = static_cast<uint32_t>(ctx.ebx ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    ctx.ebx = static_cast<uint32_t>(t9);
    // 0x004de319: add eax, eax
    uint32_t t10 = static_cast<uint32_t>(ctx.eax + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.eax, t10);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x004de31b: test ebx, 0x8000
    uint32_t t11 = static_cast<uint32_t>(ctx.ebx & 0x00008000u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    // 0x004de321: je 0x4de32b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004de32b;
    goto bb_004de323;
}
bb_004de32b: {
    // 0x004de32b: add ecx, ecx
    uint32_t t12 = static_cast<uint32_t>(ctx.ecx + ctx.ecx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, ctx.ecx, t12);
    ctx.ecx = static_cast<uint32_t>(t12);
    // 0x004de32d: add si, 0xffff
    uint16_t t13 = static_cast<uint16_t>(static_cast<uint32_t>(recomp_detail::r16(ctx.esi)) + static_cast<uint32_t>(uint16_t{0xffffu}));
    recomp_detail::update_flags_add<uint16_t>(ctx, recomp_detail::r16(ctx.esi), uint16_t{0xffffu}, t13);
    recomp_detail::w16(ctx.esi, static_cast<uint16_t>(t13));
    // 0x004de332: jne 0x4de315
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004de315;
    goto bb_004de334;
}
bb_004de323: {
    // 0x004de323: xor eax, 0x1021
    uint32_t t14 = static_cast<uint32_t>(ctx.eax ^ 0x00001021u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x004de328: movzx eax, ax
    uint32_t t15 = static_cast<uint32_t>(static_cast<uint16_t>(recomp_detail::r16(ctx.eax)));
    ctx.eax = static_cast<uint32_t>(t15);
    goto bb_004de32b;
}
bb_004de334: {
    // 0x004de334: add edx, 1
    uint32_t t16 = static_cast<uint32_t>(ctx.edx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000001u, t16);
    ctx.edx = static_cast<uint32_t>(t16);
    // 0x004de337: cmp edx, 0x22
    uint32_t t17 = static_cast<uint32_t>(ctx.edx - 0x00000022u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000022u, t17);
    // 0x004de33a: mov word ptr [0x7b09b0], si
    mem.w16(0x007b09b0u, recomp_detail::r16(ctx.esi));
    // 0x004de341: movzx ecx, ax
    uint32_t t18 = static_cast<uint32_t>(static_cast<uint16_t>(recomp_detail::r16(ctx.eax)));
    ctx.ecx = static_cast<uint32_t>(t18);
    // 0x004de344: jl 0x4de306
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004de306;
}
{
    // 0x004de346: pop esi
    uint32_t t19 = ctx.esp;
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t19 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    ctx.esi = static_cast<uint32_t>(t20);
    // 0x004de347: pop ebx
    uint32_t t22 = ctx.esp;
    uint32_t t23 = mem.r32(t22);
    uint32_t t24 = static_cast<uint32_t>(t22 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    ctx.ebx = static_cast<uint32_t>(t23);
    // 0x004de348: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004de350 | subsystem=Core/Windows | canonical | 1 blocks | 2 insns
void sub_004de350(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004de350: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x004de355: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518d50 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00518d50(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518d50: push 0x519840
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519840u);
    // 0x00518d55: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00518d5au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518d5a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x00518d5b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518d60 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00518d60(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518d60: push 0x519880
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519880u);
    // 0x00518d65: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00518d6au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518d6a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x00518d6b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518d70 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00518d70(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518d70: push 0x519890
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519890u);
    // 0x00518d75: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00518d7au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518d7a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x00518d7b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518d80 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 6 insns
void sub_00518d80(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518d80: push 0x76e9d4
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x0076e9d4u);
    // 0x00518d85: call dword ptr [0x51b068]
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00518d8bu);
    hle_iat_call(ctx, mem, 0x0051b068u);
    // 0x00518d8b: push 0x5198a0
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x005198a0u);
    // 0x00518d90: call 0x4e0ab6
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x00518d95u);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518d95: pop ecx
    uint32_t t4 = ctx.esp;
    uint32_t t5 = mem.r32(t4);
    uint32_t t6 = static_cast<uint32_t>(t4 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    ctx.ecx = static_cast<uint32_t>(t5);
    // 0x00518d96: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518da0 | subsystem=Core/Windows | .CRT$XCA init | 5 blocks | 53 insns
void sub_00518da0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518da0: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x00518da1: push ebx
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebx);
    // 0x00518da2: push esi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.esi);
    // 0x00518da3: push edi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.edi);
    // 0x00518da4: mov dword ptr [esp + 0xc], 1
    uint32_t t4 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t4, 0x00000001u);
    // 0x00518dac: mov esi, 0x76fc00
    ctx.esi = static_cast<uint32_t>(0x0076fc00u);
    // 0x00518db1: xor edi, edi
    uint32_t t5 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    ctx.edi = static_cast<uint32_t>(t5);
    // 0x00518db3: mov ebx, 0xff
    ctx.ebx = static_cast<uint32_t>(0x000000ffu);
}
bb_00518db8: {
    // 0x00518db8: push 0x64
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x00000064u);
    // 0x00518dba: lea eax, [esi + 0x2c]
    uint32_t t7 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x00518dbd: push edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edi);
    // 0x00518dbe: push eax
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.eax);
    // 0x00518dbf: mov dword ptr [esi - 0x1210], edi
    uint32_t t10 = static_cast<uint32_t>(ctx.esi + 0xffffedf0u);
    mem.w32(t10, ctx.edi);
    // 0x00518dc5: mov dword ptr [esi - 0x120c], edi
    uint32_t t11 = static_cast<uint32_t>(ctx.esi + 0xffffedf4u);
    mem.w32(t11, ctx.edi);
    // 0x00518dcb: mov dword ptr [esi - 4], edi
    uint32_t t12 = static_cast<uint32_t>(ctx.esi + 0xfffffffcu);
    mem.w32(t12, ctx.edi);
    // 0x00518dce: mov dword ptr [esi], edi
    mem.w32(ctx.esi, ctx.edi);
    // 0x00518dd0: mov dword ptr [esi + 4], edi
    uint32_t t13 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t13, ctx.edi);
    // 0x00518dd3: mov dword ptr [esi - 0x1208], edi
    uint32_t t14 = static_cast<uint32_t>(ctx.esi + 0xffffedf8u);
    mem.w32(t14, ctx.edi);
    // 0x00518dd9: mov dword ptr [esi + 8], edi
    uint32_t t15 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t15, ctx.edi);
    // 0x00518ddc: mov dword ptr [esi + 0xc], edi
    uint32_t t16 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t16, ctx.edi);
    // 0x00518ddf: mov dword ptr [esi + 0x10], edi
    uint32_t t17 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    mem.w32(t17, ctx.edi);
    // 0x00518de2: mov dword ptr [esi + 0x14], edi
    uint32_t t18 = static_cast<uint32_t>(ctx.esi + 0x00000014u);
    mem.w32(t18, ctx.edi);
    // 0x00518de5: mov dword ptr [esi + 0x18], edi
    uint32_t t19 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    mem.w32(t19, ctx.edi);
    // 0x00518de8: mov dword ptr [esi + 0x1c], edi
    uint32_t t20 = static_cast<uint32_t>(ctx.esi + 0x0000001cu);
    mem.w32(t20, ctx.edi);
    // 0x00518deb: mov dword ptr [esi + 0x20], 0xffffffff
    uint32_t t21 = static_cast<uint32_t>(ctx.esi + 0x00000020u);
    mem.w32(t21, 0xffffffffu);
    // 0x00518df2: mov dword ptr [esi + 0x24], edi
    uint32_t t22 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    mem.w32(t22, ctx.edi);
    // 0x00518df5: mov dword ptr [esi + 0x28], edi
    uint32_t t23 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    mem.w32(t23, ctx.edi);
    // 0x00518df8: call 0x4e6340
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x00518dfdu);
    hle_crt_004e6340(ctx, mem);
    // 0x00518dfd: push 0x1200
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x00001200u);
    // 0x00518e02: lea ecx, [esi - 0x1204]
    uint32_t t26 = static_cast<uint32_t>(ctx.esi + 0xffffedfcu);
    ctx.ecx = static_cast<uint32_t>(t26);
    // 0x00518e08: push edi
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, ctx.edi);
    // 0x00518e09: push ecx
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, ctx.ecx);
    // 0x00518e0a: call 0x4e6340
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x00518e0fu);
    hle_crt_004e6340(ctx, mem);
    // 0x00518e0f: add esp, 0x18
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000018u, t30);
    ctx.esp = static_cast<uint32_t>(t30);
    // 0x00518e12: lea eax, [esi - 0x11fc]
    uint32_t t31 = static_cast<uint32_t>(ctx.esi + 0xffffee04u);
    ctx.eax = static_cast<uint32_t>(t31);
    // 0x00518e18: mov ecx, 0x80
    ctx.ecx = static_cast<uint32_t>(0x00000080u);
    // 0x00518e1d: lea ecx, [ecx]
    ctx.ecx = static_cast<uint32_t>(ctx.ecx);
}
bb_00518e20: {
    // 0x00518e20: mov dword ptr [eax + 4], ebx
    uint32_t t32 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w32(t32, ctx.ebx);
    // 0x00518e23: mov dword ptr [eax], ebx
    mem.w32(ctx.eax, ctx.ebx);
    // 0x00518e25: mov dword ptr [eax - 4], ebx
    uint32_t t33 = static_cast<uint32_t>(ctx.eax + 0xfffffffcu);
    mem.w32(t33, ctx.ebx);
    // 0x00518e28: mov dword ptr [eax - 8], ebx
    uint32_t t34 = static_cast<uint32_t>(ctx.eax + 0xfffffff8u);
    mem.w32(t34, ctx.ebx);
    // 0x00518e2b: add eax, 0x24
    uint32_t t35 = static_cast<uint32_t>(ctx.eax + 0x00000024u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000024u, t35);
    ctx.eax = static_cast<uint32_t>(t35);
    // 0x00518e2e: sub ecx, 1
    uint32_t t36 = static_cast<uint32_t>(ctx.ecx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000001u, t36);
    ctx.ecx = static_cast<uint32_t>(t36);
    // 0x00518e31: jne 0x518e20
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00518e20;
}
{
    // 0x00518e33: mov dword ptr [esi - 0x120c], edi
    uint32_t t37 = static_cast<uint32_t>(ctx.esi + 0xffffedf4u);
    mem.w32(t37, ctx.edi);
    // 0x00518e39: add esi, 0x12a0
    uint32_t t38 = static_cast<uint32_t>(ctx.esi + 0x000012a0u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x000012a0u, t38);
    ctx.esi = static_cast<uint32_t>(t38);
    // 0x00518e3f: sub dword ptr [esp + 0xc], 1
    uint32_t t39 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t40 = mem.r32(t39);
    uint32_t t41 = static_cast<uint32_t>(t40 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t40, 0x00000001u, t41);
    mem.w32(t39, t41);
    // 0x00518e44: jns 0x518db8
    if (recomp_detail::eval_cond(ctx, Cond::NS)) goto bb_00518db8;
}
{
    // 0x00518e4a: pop edi
    uint32_t t42 = ctx.esp;
    uint32_t t43 = mem.r32(t42);
    uint32_t t44 = static_cast<uint32_t>(t42 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    ctx.edi = static_cast<uint32_t>(t43);
    // 0x00518e4b: pop esi
    uint32_t t45 = ctx.esp;
    uint32_t t46 = mem.r32(t45);
    uint32_t t47 = static_cast<uint32_t>(t45 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    ctx.esi = static_cast<uint32_t>(t46);
    // 0x00518e4c: pop ebx
    uint32_t t48 = ctx.esp;
    uint32_t t49 = mem.r32(t48);
    uint32_t t50 = static_cast<uint32_t>(t48 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    ctx.ebx = static_cast<uint32_t>(t49);
    // 0x00518e4d: pop ecx
    uint32_t t51 = ctx.esp;
    uint32_t t52 = mem.r32(t51);
    uint32_t t53 = static_cast<uint32_t>(t51 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    ctx.ecx = static_cast<uint32_t>(t52);
    // 0x00518e4e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518e50 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00518e50(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518e50: push 0x5198b0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x005198b0u);
    // 0x00518e55: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00518e5au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518e5a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x00518e5b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518e60 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_00518e60(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518e60: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x00518e62: jmp 0x518e70
}
bb_00518e70: {
    // 0x00518e70: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x00518e76: mov byte ptr [eax + 0x54f3fc], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0054f3fcu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x00518e7c: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x00518e7f: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x00518e81: jne 0x518e70
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00518e70;
}
{
    // 0x00518e83: push 0x5198e0
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x005198e0u);
    // 0x00518e88: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x00518e8du);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518e8d: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x00518e8e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518e90 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 6 insns
void sub_00518e90(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518e90: call 0x41ecb0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00518e95u);
    sub_0041ecb0(ctx, mem);
    // 0x00518e95: push 0x5198f0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005198f0u);
    // 0x00518e9a: mov dword ptr [0x770f30], 0x53a040
    mem.w32(0x00770f30u, 0x0053a040u);
    // 0x00518ea4: call 0x4e0ab6
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x00518ea9u);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518ea9: pop ecx
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x00518eaa: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518eb0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 5 insns
void sub_00518eb0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518eb0: call 0x49fef0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00518eb5u);
    sub_0049fef0(ctx, mem);
    // 0x00518eb5: push 0x519910
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00519910u);
    // 0x00518eba: call 0x4e0ab6
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x00518ebfu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518ebf: pop ecx
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x00518ec0: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518ed0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 18 insns
void sub_00518ed0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518ed0: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x00518ed1: mov esi, 0x771678
    ctx.esi = static_cast<uint32_t>(0x00771678u);
    // 0x00518ed6: call 0x401830
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00518edbu);
    sub_00401830(ctx, mem);
    // 0x00518edb: mov esi, 0x7716c0
    ctx.esi = static_cast<uint32_t>(0x007716c0u);
    // 0x00518ee0: call 0x401830
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x00518ee5u);
    sub_00401830(ctx, mem);
    // 0x00518ee5: push 0x4d5ef0
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x004d5ef0u);
    // 0x00518eea: push 0x421800
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x00421800u);
    // 0x00518eef: push 2
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, 0x00000002u);
    // 0x00518ef1: push 0x48
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x00000048u);
    // 0x00518ef3: push 0x771700
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x00771700u);
    // 0x00518ef8: call 0x4e1c97
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x00518efdu);
    hle_crt_004e1c97(ctx, mem);
    // 0x00518efd: mov esi, 0x771798
    ctx.esi = static_cast<uint32_t>(0x00771798u);
    // 0x00518f02: call 0x401830
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x00518f07u);
    sub_00401830(ctx, mem);
    // 0x00518f07: push 0x519920
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x00519920u);
    // 0x00518f0c: call 0x4e0ab6
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0x00518f11u);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518f11: add esp, 4
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t12);
    ctx.esp = static_cast<uint32_t>(t12);
    // 0x00518f14: pop esi
    uint32_t t13 = ctx.esp;
    uint32_t t14 = mem.r32(t13);
    uint32_t t15 = static_cast<uint32_t>(t13 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    ctx.esi = static_cast<uint32_t>(t14);
    // 0x00518f15: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518f20 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00518f20(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518f20: push 0x519940
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519940u);
    // 0x00518f25: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00518f2au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518f2a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x00518f2b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518f30 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_00518f30(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518f30: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x00518f32: jmp 0x518f40
}
bb_00518f40: {
    // 0x00518f40: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x00518f46: mov byte ptr [eax + 0x54f50c], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0054f50cu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x00518f4c: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x00518f4f: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x00518f51: jne 0x518f40
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00518f40;
}
{
    // 0x00518f53: push 0x519950
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x00519950u);
    // 0x00518f58: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x00518f5du);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518f5d: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x00518f5e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518f60 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00518f60(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518f60: push 0x519960
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519960u);
    // 0x00518f65: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00518f6au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518f6a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x00518f6b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518f70 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00518f70(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518f70: push 0x519970
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519970u);
    // 0x00518f75: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00518f7au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518f7a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x00518f7b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518f80 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00518f80(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518f80: push 0x519980
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519980u);
    // 0x00518f85: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00518f8au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518f8a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x00518f8b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518f90 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00518f90(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518f90: push 0x519990
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519990u);
    // 0x00518f95: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00518f9au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518f9a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x00518f9b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518fa0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00518fa0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518fa0: push 0x5199a0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x005199a0u);
    // 0x00518fa5: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00518faau);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518faa: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x00518fab: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518fb0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 5 insns
void sub_00518fb0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518fb0: call 0x486720
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00518fb5u);
    sub_00486720(ctx, mem);
    // 0x00518fb5: push 0x5199b0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005199b0u);
    // 0x00518fba: call 0x4e0ab6
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x00518fbfu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518fbf: pop ecx
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x00518fc0: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518fd0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00518fd0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518fd0: push 0x5199c0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x005199c0u);
    // 0x00518fd5: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00518fdau);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518fda: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x00518fdb: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518fe0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00518fe0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518fe0: push 0x5199d0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x005199d0u);
    // 0x00518fe5: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00518feau);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518fea: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x00518feb: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00518ff0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00518ff0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00518ff0: push 0x5199e0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x005199e0u);
    // 0x00518ff5: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00518ffau);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00518ffa: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x00518ffb: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519000 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519000(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519000: push 0x5199f0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x005199f0u);
    // 0x00519005: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051900au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051900a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051900b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519010 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519010(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519010: push 0x519a00
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519a00u);
    // 0x00519015: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051901au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051901a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051901b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519020 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519020(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519020: push 0x519a40
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519a40u);
    // 0x00519025: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051902au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051902a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051902b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519030 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_00519030(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519030: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x00519032: jmp 0x519040
}
bb_00519040: {
    // 0x00519040: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x00519046: mov byte ptr [eax + 0x54f624], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0054f624u);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x0051904c: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0051904f: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x00519051: jne 0x519040
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00519040;
}
{
    // 0x00519053: push 0x519a50
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x00519a50u);
    // 0x00519058: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0051905du);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051905d: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0051905e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519060 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_00519060(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519060: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x00519062: jmp 0x519070
}
bb_00519070: {
    // 0x00519070: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x00519076: mov byte ptr [eax + 0x54f734], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0054f734u);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x0051907c: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0051907f: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x00519081: jne 0x519070
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00519070;
}
{
    // 0x00519083: push 0x519a60
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x00519a60u);
    // 0x00519088: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0051908du);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051908d: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0051908e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519090 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519090(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519090: push 0x519a70
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519a70u);
    // 0x00519095: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051909au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051909a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051909b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005190a0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_005190a0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005190a0: push 0x519a80
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519a80u);
    // 0x005190a5: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005190aau);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005190aa: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x005190ab: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005190b0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_005190b0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005190b0: push 0x519a90
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519a90u);
    // 0x005190b5: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005190bau);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005190ba: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x005190bb: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005190c0 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_005190c0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005190c0: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x005190c2: jmp 0x5190d0
}
bb_005190d0: {
    // 0x005190d0: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x005190d6: mov byte ptr [eax + 0x54f844], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0054f844u);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x005190dc: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x005190df: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x005190e1: jne 0x5190d0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_005190d0;
}
{
    // 0x005190e3: push 0x519aa0
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x00519aa0u);
    // 0x005190e8: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x005190edu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005190ed: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x005190ee: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005190f0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 5 insns
void sub_005190f0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005190f0: call 0x432a70
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x005190f5u);
    sub_00432a70(ctx, mem);
    // 0x005190f5: push 0x519ab0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00519ab0u);
    // 0x005190fa: call 0x4e0ab6
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x005190ffu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005190ff: pop ecx
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x00519100: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519110 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 5 insns
void sub_00519110(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519110: call 0x438260
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519115u);
    sub_00438260(ctx, mem);
    // 0x00519115: push 0x519ad0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00519ad0u);
    // 0x0051911a: call 0x4e0ab6
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x0051911fu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051911f: pop ecx
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x00519120: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519130 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519130(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519130: push 0x519ae0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519ae0u);
    // 0x00519135: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051913au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051913a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051913b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519140 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519140(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519140: push 0x519af0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519af0u);
    // 0x00519145: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051914au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051914a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051914b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519150 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519150(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519150: push 0x519b00
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519b00u);
    // 0x00519155: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051915au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051915a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051915b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519160 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519160(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519160: push 0x519b10
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519b10u);
    // 0x00519165: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051916au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051916a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051916b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519170 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 5 insns
void sub_00519170(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519170: call 0x4391f0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519175u);
    sub_004391f0(ctx, mem);
    // 0x00519175: push 0x519b20
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00519b20u);
    // 0x0051917a: call 0x4e0ab6
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x0051917fu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051917f: pop ecx
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x00519180: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519190 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 5 insns
void sub_00519190(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519190: call 0x426d00
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519195u);
    sub_00426d00(ctx, mem);
    // 0x00519195: push 0x519b30
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00519b30u);
    // 0x0051919a: call 0x4e0ab6
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x0051919fu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051919f: pop ecx
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x005191a0: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005191b0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 5 insns
void sub_005191b0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005191b0: call 0x4232a0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x005191b5u);
    sub_004232a0(ctx, mem);
    // 0x005191b5: push 0x519b40
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00519b40u);
    // 0x005191ba: call 0x4e0ab6
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x005191bfu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005191bf: pop ecx
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x005191c0: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005191d0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_005191d0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005191d0: push 0x519b50
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519b50u);
    // 0x005191d5: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005191dau);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005191da: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x005191db: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005191e0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_005191e0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005191e0: push 0x519b70
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519b70u);
    // 0x005191e5: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005191eau);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005191ea: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x005191eb: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005191f0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_005191f0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005191f0: push 0x519bb0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519bb0u);
    // 0x005191f5: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005191fau);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005191fa: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x005191fb: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519200 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519200(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519200: push 0x519bc0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519bc0u);
    // 0x00519205: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051920au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051920a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051920b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519210 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519210(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519210: push 0x519bd0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519bd0u);
    // 0x00519215: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051921au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051921a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051921b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519220 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 5 insns
void sub_00519220(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519220: call 0x482c20
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519225u);
    sub_00482c20(ctx, mem);
    // 0x00519225: push 0x519be0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00519be0u);
    // 0x0051922a: call 0x4e0ab6
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x0051922fu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051922f: pop ecx
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x00519230: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519240 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 12 insns
void sub_00519240(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519240: push 0x77bf34
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x0077bf34u);
    // 0x00519245: call 0x445f30
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051924au);
    sub_00445f30(ctx, mem);
    // 0x0051924a: mov ecx, 1
    ctx.ecx = static_cast<uint32_t>(0x00000001u);
    // 0x0051924f: xor eax, eax
    uint32_t t2 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x00519251: push 0x519c10
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x00519c10u);
    // 0x00519256: mov dword ptr [0x77bfe4], ecx
    mem.w32(0x0077bfe4u, ctx.ecx);
    // 0x0051925c: mov dword ptr [0x77bf30], eax
    mem.w32(0x0077bf30u, ctx.eax);
    // 0x00519261: mov dword ptr [0x77bf2c], ecx
    mem.w32(0x0077bf2cu, ctx.ecx);
    // 0x00519267: mov dword ptr [0x77bf28], eax
    mem.w32(0x0077bf28u, ctx.eax);
    // 0x0051926c: call 0x4e0ab6
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x00519271u);
    hle_crt_004e0ab6(ctx, mem);
    // 0x00519271: pop ecx
    uint32_t t5 = ctx.esp;
    uint32_t t6 = mem.r32(t5);
    uint32_t t7 = static_cast<uint32_t>(t5 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    ctx.ecx = static_cast<uint32_t>(t6);
    // 0x00519272: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519280 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519280(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519280: push 0x519c20
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519c20u);
    // 0x00519285: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051928au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051928a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051928b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519290 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519290(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519290: push 0x519c30
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519c30u);
    // 0x00519295: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051929au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051929a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051929b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005192a0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_005192a0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005192a0: push 0x519c40
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519c40u);
    // 0x005192a5: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005192aau);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005192aa: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x005192ab: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005192b0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_005192b0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005192b0: push 0x519c50
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519c50u);
    // 0x005192b5: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005192bau);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005192ba: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x005192bb: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005192c0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_005192c0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005192c0: push 0x519c60
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519c60u);
    // 0x005192c5: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005192cau);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005192ca: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x005192cb: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005192d0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_005192d0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005192d0: push 0x519c70
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519c70u);
    // 0x005192d5: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005192dau);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005192da: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x005192db: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005192e0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 6 insns
void sub_005192e0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005192e0: call 0x47b010
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x005192e5u);
    sub_0047b010(ctx, mem);
    // 0x005192e5: push 0x519cc0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00519cc0u);
    // 0x005192ea: mov dword ptr [0x77c21c], 1
    mem.w32(0x0077c21cu, 0x00000001u);
    // 0x005192f4: call 0x4e0ab6
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x005192f9u);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005192f9: pop ecx
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x005192fa: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519300 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 5 insns
void sub_00519300(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519300: call 0x47cdd0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519305u);
    sub_0047cdd0(ctx, mem);
    // 0x00519305: push 0x519cd0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00519cd0u);
    // 0x0051930a: call 0x4e0ab6
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x0051930fu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051930f: pop ecx
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x00519310: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519320 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519320(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519320: push 0x519ce0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519ce0u);
    // 0x00519325: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051932au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051932a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051932b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519330 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519330(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519330: push 0x519d30
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519d30u);
    // 0x00519335: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051933au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051933a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051933b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519340 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519340(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519340: push 0x519d40
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519d40u);
    // 0x00519345: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051934au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051934a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051934b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519350 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519350(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519350: push 0x519d90
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519d90u);
    // 0x00519355: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051935au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051935a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051935b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519360 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519360(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519360: push 0x519de0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519de0u);
    // 0x00519365: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051936au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051936a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051936b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519370 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 7 insns
void sub_00519370(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519370: mov eax, 0x77c29c
    ctx.eax = static_cast<uint32_t>(0x0077c29cu);
    // 0x00519375: call 0x48e990
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x0051937au);
    sub_0048e990(ctx, mem);
    // 0x0051937a: push 0x519df0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00519df0u);
    // 0x0051937f: mov dword ptr [0x77c298], 0
    mem.w32(0x0077c298u, 0x00000000u);
    // 0x00519389: call 0x4e0ab6
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x0051938eu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051938e: pop ecx
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x0051938f: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519390 | subsystem=Core/Windows | .CRT$XCA init | 4 blocks | 25 insns
void sub_00519390(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519390: jmp 0x490840
}
{
    // 0x00490840: mov edx, 1
    ctx.edx = static_cast<uint32_t>(0x00000001u);
    // 0x00490845: mov eax, 0x77c45c
    ctx.eax = static_cast<uint32_t>(0x0077c45cu);
    // 0x0049084a: xor ecx, ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.ecx = static_cast<uint32_t>(t0);
    // 0x0049084c: lea esp, [esp]
    ctx.esp = static_cast<uint32_t>(ctx.esp);
}
bb_00490850: {
    // 0x00490850: mov dword ptr [eax - 0x2c], ecx
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0xffffffd4u);
    mem.w32(t1, ctx.ecx);
    // 0x00490853: mov dword ptr [eax - 0x28], ecx
    uint32_t t2 = static_cast<uint32_t>(ctx.eax + 0xffffffd8u);
    mem.w32(t2, ctx.ecx);
    // 0x00490856: mov dword ptr [eax - 0x24], ecx
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0xffffffdcu);
    mem.w32(t3, ctx.ecx);
    // 0x00490859: mov dword ptr [eax - 0x20], ecx
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0xffffffe0u);
    mem.w32(t4, ctx.ecx);
    // 0x0049085c: mov dword ptr [eax - 0x1c], ecx
    uint32_t t5 = static_cast<uint32_t>(ctx.eax + 0xffffffe4u);
    mem.w32(t5, ctx.ecx);
    // 0x0049085f: mov dword ptr [eax - 0x18], ecx
    uint32_t t6 = static_cast<uint32_t>(ctx.eax + 0xffffffe8u);
    mem.w32(t6, ctx.ecx);
    // 0x00490862: mov dword ptr [eax - 0x14], ecx
    uint32_t t7 = static_cast<uint32_t>(ctx.eax + 0xffffffecu);
    mem.w32(t7, ctx.ecx);
    // 0x00490865: mov dword ptr [eax - 0x10], ecx
    uint32_t t8 = static_cast<uint32_t>(ctx.eax + 0xfffffff0u);
    mem.w32(t8, ctx.ecx);
    // 0x00490868: mov dword ptr [eax - 0xc], ecx
    uint32_t t9 = static_cast<uint32_t>(ctx.eax + 0xfffffff4u);
    mem.w32(t9, ctx.ecx);
    // 0x0049086b: mov dword ptr [eax - 8], ecx
    uint32_t t10 = static_cast<uint32_t>(ctx.eax + 0xfffffff8u);
    mem.w32(t10, ctx.ecx);
    // 0x0049086e: mov dword ptr [eax - 4], ecx
    uint32_t t11 = static_cast<uint32_t>(ctx.eax + 0xfffffffcu);
    mem.w32(t11, ctx.ecx);
    // 0x00490871: mov dword ptr [eax], ecx
    mem.w32(ctx.eax, ctx.ecx);
    // 0x00490873: mov dword ptr [eax + 4], ecx
    uint32_t t12 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w32(t12, ctx.ecx);
    // 0x00490876: add eax, 0x34
    uint32_t t13 = static_cast<uint32_t>(ctx.eax + 0x00000034u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000034u, t13);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x00490879: sub edx, 1
    uint32_t t14 = static_cast<uint32_t>(ctx.edx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000001u, t14);
    ctx.edx = static_cast<uint32_t>(t14);
    // 0x0049087c: jns 0x490850
    if (recomp_detail::eval_cond(ctx, Cond::NS)) goto bb_00490850;
}
{
    // 0x0049087e: mov dword ptr [0x77c418], ecx
    mem.w32(0x0077c418u, ctx.ecx);
    // 0x00490884: call 0x490890
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x00490889u);
    sub_00490890(ctx, mem);
    // 0x00490889: mov eax, 0x77c418
    ctx.eax = static_cast<uint32_t>(0x0077c418u);
    // 0x0049088e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005193a0 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_005193a0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005193a0: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x005193a2: jmp 0x5193b0
}
bb_005193b0: {
    // 0x005193b0: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x005193b6: mov byte ptr [eax + 0x54f9bc], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0054f9bcu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x005193bc: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x005193bf: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x005193c1: jne 0x5193b0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_005193b0;
}
{
    // 0x005193c3: push 0x519e00
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x00519e00u);
    // 0x005193c8: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x005193cdu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005193cd: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x005193ce: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005193d0 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_005193d0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005193d0: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x005193d2: jmp 0x5193e0
}
bb_005193e0: {
    // 0x005193e0: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x005193e6: mov byte ptr [eax + 0x54facc], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0054faccu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x005193ec: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x005193ef: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x005193f1: jne 0x5193e0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_005193e0;
}
{
    // 0x005193f3: push 0x519e10
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x00519e10u);
    // 0x005193f8: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x005193fdu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005193fd: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x005193fe: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519400 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 5 insns
void sub_00519400(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519400: call 0x490cc0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519405u);
    sub_00490cc0(ctx, mem);
    // 0x00519405: push 0x519e20
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00519e20u);
    // 0x0051940a: call 0x4e0ab6
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x0051940fu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051940f: pop ecx
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x00519410: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519420 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 5 insns
void sub_00519420(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519420: call 0x49dfc0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519425u);
    sub_0049dfc0(ctx, mem);
    // 0x00519425: push 0x519e30
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00519e30u);
    // 0x0051942a: call 0x4e0ab6
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x0051942fu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051942f: pop ecx
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x00519430: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519440 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 5 insns
void sub_00519440(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519440: call 0x492310
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519445u);
    sub_00492310(ctx, mem);
    // 0x00519445: push 0x519e40
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00519e40u);
    // 0x0051944a: call 0x4e0ab6
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x0051944fu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051944f: pop ecx
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x00519450: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519460 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_00519460(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519460: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x00519462: jmp 0x519470
}
bb_00519470: {
    // 0x00519470: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x00519476: mov byte ptr [eax + 0x54fbdc], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0054fbdcu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x0051947c: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0051947f: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x00519481: jne 0x519470
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00519470;
}
{
    // 0x00519483: push 0x519e50
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x00519e50u);
    // 0x00519488: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0051948du);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051948d: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0051948e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519490 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 9 insns
void sub_00519490(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519490: call 0x497a10
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519495u);
    sub_00497a10(ctx, mem);
    // 0x00519495: xor eax, eax
    uint32_t t1 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x00519497: push 0x519e60
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x00519e60u);
    // 0x0051949c: mov dword ptr [0x7b03c0], 0x5393d8
    mem.w32(0x007b03c0u, 0x005393d8u);
    // 0x005194a6: mov dword ptr [0x7b0688], eax
    mem.w32(0x007b0688u, ctx.eax);
    // 0x005194ab: mov dword ptr [0x7b068c], eax
    mem.w32(0x007b068cu, ctx.eax);
    // 0x005194b0: call 0x4e0ab6
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x005194b5u);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005194b5: pop ecx
    uint32_t t4 = ctx.esp;
    uint32_t t5 = mem.r32(t4);
    uint32_t t6 = static_cast<uint32_t>(t4 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    ctx.ecx = static_cast<uint32_t>(t5);
    // 0x005194b6: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005194c0 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_005194c0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005194c0: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x005194c2: jmp 0x5194d0
}
bb_005194d0: {
    // 0x005194d0: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x005194d6: mov byte ptr [eax + 0x54fcec], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0054fcecu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x005194dc: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x005194df: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x005194e1: jne 0x5194d0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_005194d0;
}
{
    // 0x005194e3: push 0x519e80
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x00519e80u);
    // 0x005194e8: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x005194edu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005194ed: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x005194ee: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005194f0 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_005194f0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005194f0: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x005194f2: jmp 0x519500
}
bb_00519500: {
    // 0x00519500: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x00519506: mov byte ptr [eax + 0x54fdfc], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0054fdfcu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x0051950c: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0051950f: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x00519511: jne 0x519500
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00519500;
}
{
    // 0x00519513: push 0x519e90
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x00519e90u);
    // 0x00519518: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0051951du);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051951d: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0051951e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519520 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_00519520(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519520: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x00519522: jmp 0x519530
}
bb_00519530: {
    // 0x00519530: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x00519536: mov byte ptr [eax + 0x54ff0c], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0054ff0cu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x0051953c: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0051953f: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x00519541: jne 0x519530
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00519530;
}
{
    // 0x00519543: push 0x519ea0
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x00519ea0u);
    // 0x00519548: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0051954du);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051954d: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0051954e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519550 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 5 insns
void sub_00519550(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519550: call 0x49a4a0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519555u);
    sub_0049a4a0(ctx, mem);
    // 0x00519555: push 0x519eb0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00519eb0u);
    // 0x0051955a: call 0x4e0ab6
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x0051955fu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051955f: pop ecx
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x00519560: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519570 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519570(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519570: push 0x519ec0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519ec0u);
    // 0x00519575: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051957au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051957a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051957b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519580 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519580(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519580: push 0x519ed0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519ed0u);
    // 0x00519585: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051958au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051958a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051958b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519590 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519590(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519590: push 0x519f10
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519f10u);
    // 0x00519595: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051959au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051959a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051959b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005195a0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 5 insns
void sub_005195a0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005195a0: call 0x4bc990
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x005195a5u);
    sub_004bc990(ctx, mem);
    // 0x005195a5: push 0x519f20
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00519f20u);
    // 0x005195aa: call 0x4e0ab6
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x005195afu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005195af: pop ecx
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x005195b0: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005195c0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_005195c0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005195c0: push 0x519f60
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519f60u);
    // 0x005195c5: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005195cau);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005195ca: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x005195cb: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005195d0 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_005195d0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005195d0: push 0x519fa0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x00519fa0u);
    // 0x005195d5: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005195dau);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005195da: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x005195db: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005195e0 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_005195e0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005195e0: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x005195e2: jmp 0x5195f0
}
bb_005195f0: {
    // 0x005195f0: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x005195f6: mov byte ptr [eax + 0x55002c], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0055002cu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x005195fc: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x005195ff: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x00519601: jne 0x5195f0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_005195f0;
}
{
    // 0x00519603: push 0x51a060
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0051a060u);
    // 0x00519608: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0051960du);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051960d: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0051960e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519610 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_00519610(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519610: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x00519612: jmp 0x519620
}
bb_00519620: {
    // 0x00519620: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x00519626: mov byte ptr [eax + 0x55013c], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0055013cu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x0051962c: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0051962f: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x00519631: jne 0x519620
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00519620;
}
{
    // 0x00519633: push 0x51a070
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0051a070u);
    // 0x00519638: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0051963du);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051963d: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0051963e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519640 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_00519640(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519640: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x00519642: jmp 0x519650
}
bb_00519650: {
    // 0x00519650: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x00519656: mov byte ptr [eax + 0x55024c], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0055024cu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x0051965c: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0051965f: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x00519661: jne 0x519650
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00519650;
}
{
    // 0x00519663: push 0x51a080
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0051a080u);
    // 0x00519668: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0051966du);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051966d: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0051966e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519670 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_00519670(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519670: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x00519672: jmp 0x519680
}
bb_00519680: {
    // 0x00519680: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x00519686: mov byte ptr [eax + 0x55035c], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0055035cu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x0051968c: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0051968f: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x00519691: jne 0x519680
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00519680;
}
{
    // 0x00519693: push 0x51a090
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0051a090u);
    // 0x00519698: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0051969du);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051969d: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0051969e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005196a0 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_005196a0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005196a0: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x005196a2: jmp 0x5196b0
}
bb_005196b0: {
    // 0x005196b0: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x005196b6: mov byte ptr [eax + 0x55046c], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0055046cu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x005196bc: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x005196bf: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x005196c1: jne 0x5196b0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_005196b0;
}
{
    // 0x005196c3: push 0x51a0a0
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0051a0a0u);
    // 0x005196c8: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x005196cdu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005196cd: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x005196ce: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005196d0 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_005196d0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005196d0: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x005196d2: jmp 0x5196e0
}
bb_005196e0: {
    // 0x005196e0: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x005196e6: mov byte ptr [eax + 0x55057c], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0055057cu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x005196ec: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x005196ef: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x005196f1: jne 0x5196e0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_005196e0;
}
{
    // 0x005196f3: push 0x51a0b0
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0051a0b0u);
    // 0x005196f8: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x005196fdu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005196fd: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x005196fe: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519700 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_00519700(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519700: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x00519702: jmp 0x519710
}
bb_00519710: {
    // 0x00519710: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x00519716: mov byte ptr [eax + 0x55068c], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0055068cu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x0051971c: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0051971f: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x00519721: jne 0x519710
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00519710;
}
{
    // 0x00519723: push 0x51a0c0
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0051a0c0u);
    // 0x00519728: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0051972du);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051972d: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0051972e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519730 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_00519730(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519730: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x00519732: jmp 0x519740
}
bb_00519740: {
    // 0x00519740: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x00519746: mov byte ptr [eax + 0x55079c], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0055079cu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x0051974c: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0051974f: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x00519751: jne 0x519740
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00519740;
}
{
    // 0x00519753: push 0x51a0d0
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0051a0d0u);
    // 0x00519758: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0051975du);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051975d: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0051975e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519760 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519760(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519760: push 0x51a0e0
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x0051a0e0u);
    // 0x00519765: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051976au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051976a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051976b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519770 | subsystem=Core/Windows | .CRT$XCA init | 1 blocks | 4 insns
void sub_00519770(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519770: push 0x51a110
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0x0051a110u);
    // 0x00519775: call 0x4e0ab6
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0051977au);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051977a: pop ecx
    uint32_t t2 = ctx.esp;
    uint32_t t3 = mem.r32(t2);
    uint32_t t4 = static_cast<uint32_t>(t2 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x0051977b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519780 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_00519780(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519780: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x00519782: jmp 0x519790
}
bb_00519790: {
    // 0x00519790: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x00519796: mov byte ptr [eax + 0x5508bc], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x005508bcu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x0051979c: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0051979f: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x005197a1: jne 0x519790
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00519790;
}
{
    // 0x005197a3: push 0x51a140
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0051a140u);
    // 0x005197a8: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x005197adu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005197ad: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x005197ae: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005197b0 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_005197b0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005197b0: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x005197b2: jmp 0x5197c0
}
bb_005197c0: {
    // 0x005197c0: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x005197c6: mov byte ptr [eax + 0x5509cc], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x005509ccu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x005197cc: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x005197cf: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x005197d1: jne 0x5197c0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_005197c0;
}
{
    // 0x005197d3: push 0x51a150
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0051a150u);
    // 0x005197d8: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x005197ddu);
    hle_crt_004e0ab6(ctx, mem);
    // 0x005197dd: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x005197de: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_005197e0 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_005197e0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x005197e0: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x005197e2: jmp 0x5197f0
}
bb_005197f0: {
    // 0x005197f0: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x005197f6: mov byte ptr [eax + 0x550adc], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x00550adcu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x005197fc: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x005197ff: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x00519801: jne 0x5197f0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_005197f0;
}
{
    // 0x00519803: push 0x51a160
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0051a160u);
    // 0x00519808: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0051980du);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051980d: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0051980e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00519810 | subsystem=Core/Windows | .CRT$XCA init | 3 blocks | 11 insns
void sub_00519810(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00519810: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x00519812: jmp 0x519820
}
bb_00519820: {
    // 0x00519820: mov cl, byte ptr [eax + 0x534f8a]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00534f8au);
    uint8_t t2 = mem.r8(t1);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t2));
    // 0x00519826: mov byte ptr [eax + 0x550bec], cl
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x00550becu);
    mem.w8(t3, recomp_detail::r8l(ctx.ecx));
    // 0x0051982c: add eax, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0051982f: test cl, cl
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x00519831: jne 0x519820
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00519820;
}
{
    // 0x00519833: push 0x51a170
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0051a170u);
    // 0x00519838: call 0x4e0ab6
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0051983du);
    hle_crt_004e0ab6(ctx, mem);
    // 0x0051983d: pop ecx
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0051983e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

} // namespace mbaa_recomp

#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
