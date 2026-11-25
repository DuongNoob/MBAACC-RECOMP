// Auto-generated C++20 shard: gen_input.cpp (53 functions) — DO NOT EDIT

#include "recomp_funcs.h"

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

namespace mbaa_recomp {

// sub_0040ff50 | subsystem=Input | canonical | 5 blocks | 30 insns
void sub_0040ff50(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040ff50: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x0040ff51: push 0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00000000u);
    // 0x0040ff53: push 0x5544e8
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x005544e8u);
    // 0x0040ff58: push 0x51b714
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x0051b714u);
    // 0x0040ff5d: push 0x800
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x00000800u);
    // 0x0040ff62: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0040ff64: push 0
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, 0x00000000u);
    // 0x0040ff66: mov dword ptr [0x5542e4], esi
    mem.w32(0x005542e4u, ctx.esi);
    // 0x0040ff6c: call dword ptr [0x51b060]
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0040ff72u);
    hle_iat_call(ctx, mem, 0x0051b060u);
    // 0x0040ff72: push eax
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.eax);
    // 0x0040ff73: call 0x4de5d8
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x0040ff78u);
    sub_004de5d8(ctx, mem);
    // 0x0040ff78: test eax, eax
    uint32_t t9 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    // 0x0040ff7a: je 0x40ff80
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ff80;
    goto bb_0040ff7c;
}
bb_0040ff80: {
    // 0x0040ff80: push esi
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.esi);
    // 0x0040ff81: call 0x410000
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0x0040ff86u);
    sub_00410000(ctx, mem);
    // 0x0040ff86: add esp, 4
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t12);
    ctx.esp = static_cast<uint32_t>(t12);
    // 0x0040ff89: test eax, eax
    uint32_t t13 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t13);
    // 0x0040ff8b: je 0x40ff7c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ff7c;
    goto bb_0040ff8d;
}
bb_0040ff7c: {
    // 0x0040ff7c: xor eax, eax
    uint32_t t14 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x0040ff7e: pop esi
    uint32_t t15 = ctx.esp;
    uint32_t t16 = mem.r32(t15);
    uint32_t t17 = static_cast<uint32_t>(t15 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    ctx.esi = static_cast<uint32_t>(t16);
    // 0x0040ff7f: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040ff8d: {
    // 0x0040ff8d: call 0x4100a0
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x0040ff92u);
    sub_004100a0(ctx, mem);
    // 0x0040ff92: test eax, eax
    uint32_t t19 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t19);
    // 0x0040ff94: je 0x40ff7c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ff7c;
}
{
    // 0x0040ff96: call 0x40ffb0
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x0040ff9bu);
    sub_0040ffb0(ctx, mem);
    // 0x0040ff9b: neg eax
    uint32_t t21 = static_cast<uint32_t>(0u - ctx.eax);
    recomp_detail::update_flags_neg<uint32_t>(ctx, ctx.eax, t21);
    ctx.eax = static_cast<uint32_t>(t21);
    // 0x0040ff9d: sbb eax, eax
    uint32_t t22 = recomp_detail::get_flag(ctx, kFlagCF);
    uint32_t t23 = static_cast<uint32_t>(ctx.eax - ctx.eax);
    uint32_t t24 = static_cast<uint32_t>(t23 - t22);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.eax, t24, t22);
    ctx.eax = static_cast<uint32_t>(t24);
    // 0x0040ff9f: neg eax
    uint32_t t25 = static_cast<uint32_t>(0u - ctx.eax);
    recomp_detail::update_flags_neg<uint32_t>(ctx, ctx.eax, t25);
    ctx.eax = static_cast<uint32_t>(t25);
    // 0x0040ffa1: pop esi
    uint32_t t26 = ctx.esp;
    uint32_t t27 = mem.r32(t26);
    uint32_t t28 = static_cast<uint32_t>(t26 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    ctx.esi = static_cast<uint32_t>(t27);
    // 0x0040ffa2: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0040ffb0 | subsystem=Input | canonical | 3 blocks | 23 insns
void sub_0040ffb0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040ffb0: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x0040ffb1: mov esi, 0x5545f8
    ctx.esi = static_cast<uint32_t>(0x005545f8u);
}
bb_0040ffb6: {
    // 0x0040ffb6: push 0x38
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00000038u);
    // 0x0040ffb8: push 0
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x00000000u);
    // 0x0040ffba: push esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.esi);
    // 0x0040ffbb: call 0x4e6340
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x0040ffc0u);
    hle_crt_004e6340(ctx, mem);
    // 0x0040ffc0: mov dword ptr [esi + 0x28], 0xffffffff
    uint32_t t5 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    mem.w32(t5, 0xffffffffu);
    // 0x0040ffc7: add esi, 0x38
    uint32_t t6 = static_cast<uint32_t>(ctx.esi + 0x00000038u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000038u, t6);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x0040ffca: add esp, 0xc
    uint32_t t7 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t7);
    ctx.esp = static_cast<uint32_t>(t7);
    // 0x0040ffcd: cmp esi, 0x554978
    uint32_t t8 = static_cast<uint32_t>(ctx.esi - 0x00554978u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00554978u, t8);
    // 0x0040ffd3: jl 0x40ffb6
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040ffb6;
}
{
    // 0x0040ffd5: mov eax, dword ptr [0x5544e8]
    uint32_t t9 = mem.r32(0x005544e8u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x0040ffda: mov ecx, dword ptr [eax]
    uint32_t t10 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t10);
    // 0x0040ffdc: mov edx, dword ptr [ecx + 0x10]
    uint32_t t11 = static_cast<uint32_t>(ctx.ecx + 0x00000010u);
    uint32_t t12 = mem.r32(t11);
    ctx.edx = static_cast<uint32_t>(t12);
    // 0x0040ffdf: push 1
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x00000001u);
    // 0x0040ffe1: push 0x76e9b4
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x0076e9b4u);
    // 0x0040ffe6: push 0x410490
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x00410490u);
    // 0x0040ffeb: push 4
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x00000004u);
    // 0x0040ffed: push eax
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, ctx.eax);
    // 0x0040ffee: call edx
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x0040fff0u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040fff0: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0040fff5: pop esi
    uint32_t t19 = ctx.esp;
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t19 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    ctx.esi = static_cast<uint32_t>(t20);
    // 0x0040fff6: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00410000 | subsystem=Input | canonical | 5 blocks | 56 insns
void sub_00410000(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00410000: mov eax, dword ptr [0x5544e8]
    uint32_t t0 = mem.r32(0x005544e8u);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x00410005: mov ecx, dword ptr [eax]
    uint32_t t1 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t1);
    // 0x00410007: sub esp, 0x18
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000018u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000018u, t2);
    ctx.esp = static_cast<uint32_t>(t2);
    // 0x0041000a: push 0
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x00000000u);
    // 0x0041000c: lea edx, [esp + 4]
    uint32_t t4 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    ctx.edx = static_cast<uint32_t>(t4);
    // 0x00410010: push edx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.edx);
    // 0x00410011: push 0x51b664
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0051b664u);
    // 0x00410016: push eax
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.eax);
    // 0x00410017: mov eax, dword ptr [ecx + 0xc]
    uint32_t t8 = static_cast<uint32_t>(ctx.ecx + 0x0000000cu);
    uint32_t t9 = mem.r32(t8);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x0041001a: call eax
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x0041001cu);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0041001c: test eax, eax
    uint32_t t11 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    // 0x0041001e: je 0x410026
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410026;
    goto bb_00410020;
}
bb_00410026: {
    // 0x00410026: mov eax, dword ptr [esp]
    uint32_t t12 = mem.r32(ctx.esp);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x00410029: mov ecx, dword ptr [eax]
    uint32_t t13 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t13);
    // 0x0041002b: mov edx, dword ptr [ecx + 0x2c]
    uint32_t t14 = static_cast<uint32_t>(ctx.ecx + 0x0000002cu);
    uint32_t t15 = mem.r32(t14);
    ctx.edx = static_cast<uint32_t>(t15);
    // 0x0041002e: push 0x51bd24
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x0051bd24u);
    // 0x00410033: push eax
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, ctx.eax);
    // 0x00410034: call edx
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x00410036u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x00410036: test eax, eax
    uint32_t t19 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t19);
    // 0x00410038: jne 0x410020
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00410020;
    goto bb_0041003a;
}
bb_00410020: {
    // 0x00410020: xor eax, eax
    uint32_t t20 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t20);
    ctx.eax = static_cast<uint32_t>(t20);
    // 0x00410022: add esp, 0x18
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000018u, t21);
    ctx.esp = static_cast<uint32_t>(t21);
    // 0x00410025: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0041003a: {
    // 0x0041003a: mov eax, dword ptr [esp]
    uint32_t t22 = mem.r32(ctx.esp);
    ctx.eax = static_cast<uint32_t>(t22);
    // 0x0041003d: mov edx, dword ptr [esp + 0x1c]
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t24 = mem.r32(t23);
    ctx.edx = static_cast<uint32_t>(t24);
    // 0x00410041: mov ecx, dword ptr [eax]
    uint32_t t25 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t25);
    // 0x00410043: push 6
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x00000006u);
    // 0x00410045: push edx
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, ctx.edx);
    // 0x00410046: push eax
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, ctx.eax);
    // 0x00410047: mov eax, dword ptr [ecx + 0x34]
    uint32_t t29 = static_cast<uint32_t>(ctx.ecx + 0x00000034u);
    uint32_t t30 = mem.r32(t29);
    ctx.eax = static_cast<uint32_t>(t30);
    // 0x0041004a: call eax
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x0041004cu);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0041004c: test eax, eax
    uint32_t t32 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t32);
    // 0x0041004e: jne 0x410020
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00410020;
}
{
    // 0x00410050: mov dword ptr [esp + 0xc], eax
    uint32_t t33 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t33, ctx.eax);
    // 0x00410054: mov dword ptr [esp + 0x10], eax
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t34, ctx.eax);
    // 0x00410058: mov eax, dword ptr [esp]
    uint32_t t35 = mem.r32(ctx.esp);
    ctx.eax = static_cast<uint32_t>(t35);
    // 0x0041005b: lea edx, [esp + 4]
    uint32_t t36 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    ctx.edx = static_cast<uint32_t>(t36);
    // 0x0041005f: push edx
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, ctx.edx);
    // 0x00410060: mov dword ptr [esp + 8], 0x14
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    mem.w32(t38, 0x00000014u);
    // 0x00410068: mov dword ptr [esp + 0xc], 0x10
    uint32_t t39 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t39, 0x00000010u);
    // 0x00410070: mov dword ptr [esp + 0x18], 8
    uint32_t t40 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t40, 0x00000008u);
    // 0x00410078: mov ecx, dword ptr [eax]
    uint32_t t41 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t41);
    // 0x0041007a: push 1
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, 0x00000001u);
    // 0x0041007c: push eax
    uint32_t t43 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    mem.w32(t43, ctx.eax);
    // 0x0041007d: mov eax, dword ptr [ecx + 0x18]
    uint32_t t44 = static_cast<uint32_t>(ctx.ecx + 0x00000018u);
    uint32_t t45 = mem.r32(t44);
    ctx.eax = static_cast<uint32_t>(t45);
    // 0x00410080: call eax
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, 0x00410082u);
    call_indirect(ctx, mem, ctx.eax);
    // 0x00410082: mov eax, dword ptr [esp]
    uint32_t t47 = mem.r32(ctx.esp);
    ctx.eax = static_cast<uint32_t>(t47);
    // 0x00410085: mov ecx, dword ptr [eax]
    uint32_t t48 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t48);
    // 0x00410087: mov edx, dword ptr [ecx + 0x1c]
    uint32_t t49 = static_cast<uint32_t>(ctx.ecx + 0x0000001cu);
    uint32_t t50 = mem.r32(t49);
    ctx.edx = static_cast<uint32_t>(t50);
    // 0x0041008a: push eax
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, ctx.eax);
    // 0x0041008b: call edx
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, 0x0041008du);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0041008d: mov eax, dword ptr [esp]
    uint32_t t53 = mem.r32(ctx.esp);
    ctx.eax = static_cast<uint32_t>(t53);
    // 0x00410090: mov dword ptr [0x5544ec], eax
    mem.w32(0x005544ecu, ctx.eax);
    // 0x00410095: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0041009a: add esp, 0x18
    uint32_t t54 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000018u, t54);
    ctx.esp = static_cast<uint32_t>(t54);
    // 0x0041009d: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004100a0 | subsystem=Input | canonical | 5 blocks | 71 insns
void sub_004100a0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004100a0: sub esp, 0x28
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000028u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000028u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x004100a3: mov eax, dword ptr [0x54b458]
    uint32_t t1 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x004100a8: xor eax, esp
    uint32_t t2 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x004100aa: mov dword ptr [esp + 0x24], eax
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t3, ctx.eax);
    // 0x004100ae: mov ecx, dword ptr [0x51b678]
    uint32_t t4 = mem.r32(0x0051b678u);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x004100b4: mov eax, dword ptr [0x51b674]
    uint32_t t5 = mem.r32(0x0051b674u);
    ctx.eax = static_cast<uint32_t>(t5);
    // 0x004100b9: mov edx, dword ptr [0x51b67c]
    uint32_t t6 = mem.r32(0x0051b67cu);
    ctx.edx = static_cast<uint32_t>(t6);
    // 0x004100bf: mov dword ptr [esp + 0x18], ecx
    uint32_t t7 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t7, ctx.ecx);
    // 0x004100c3: xor ecx, ecx
    uint32_t t8 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t8);
    ctx.ecx = static_cast<uint32_t>(t8);
    // 0x004100c5: mov dword ptr [esp + 0x14], eax
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t9, ctx.eax);
    // 0x004100c9: mov eax, dword ptr [0x51b680]
    uint32_t t10 = mem.r32(0x0051b680u);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x004100ce: push ecx
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.ecx);
    // 0x004100cf: mov dword ptr [esp + 0x24], eax
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t12, ctx.eax);
    // 0x004100d3: mov eax, dword ptr [0x5544e8]
    uint32_t t13 = mem.r32(0x005544e8u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x004100d8: mov dword ptr [esp + 0xc], ecx
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t14, ctx.ecx);
    // 0x004100dc: mov dword ptr [esp + 0x10], ecx
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t15, ctx.ecx);
    // 0x004100e0: push 0x5545f4
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x005545f4u);
    // 0x004100e5: mov dword ptr [esp + 0x24], edx
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t17, ctx.edx);
    // 0x004100e9: lea ecx, [esp + 0x1c]
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.ecx = static_cast<uint32_t>(t18);
    // 0x004100ed: mov dword ptr [esp + 8], 0x14
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    mem.w32(t19, 0x00000014u);
    // 0x004100f5: mov dword ptr [esp + 0xc], 0x10
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t20, 0x00000010u);
    // 0x004100fd: mov dword ptr [esp + 0x18], 8
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t21, 0x00000008u);
    // 0x00410105: mov edx, dword ptr [eax]
    uint32_t t22 = mem.r32(ctx.eax);
    ctx.edx = static_cast<uint32_t>(t22);
    // 0x00410107: mov edx, dword ptr [edx + 0xc]
    uint32_t t23 = static_cast<uint32_t>(ctx.edx + 0x0000000cu);
    uint32_t t24 = mem.r32(t23);
    ctx.edx = static_cast<uint32_t>(t24);
    // 0x0041010a: push ecx
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, ctx.ecx);
    // 0x0041010b: push eax
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, ctx.eax);
    // 0x0041010c: call edx
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x0041010eu);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0041010e: test eax, eax
    uint32_t t28 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t28);
    // 0x00410110: je 0x410123
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410123;
    goto bb_00410112;
}
bb_00410123: {
    // 0x00410123: mov eax, dword ptr [0x5545f4]
    uint32_t t29 = mem.r32(0x005545f4u);
    ctx.eax = static_cast<uint32_t>(t29);
    // 0x00410128: mov ecx, dword ptr [eax]
    uint32_t t30 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t30);
    // 0x0041012a: mov edx, dword ptr [ecx + 0x2c]
    uint32_t t31 = static_cast<uint32_t>(ctx.ecx + 0x0000002cu);
    uint32_t t32 = mem.r32(t31);
    ctx.edx = static_cast<uint32_t>(t32);
    // 0x0041012d: push 0x51bb1c
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x0051bb1cu);
    // 0x00410132: push eax
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, ctx.eax);
    // 0x00410133: call edx
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, 0x00410135u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x00410135: test eax, eax
    uint32_t t36 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t36);
    // 0x00410137: jne 0x410112
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00410112;
    goto bb_00410139;
}
bb_00410112: {
    // 0x00410112: xor eax, eax
    uint32_t t37 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t37);
    ctx.eax = static_cast<uint32_t>(t37);
    // 0x00410114: mov ecx, dword ptr [esp + 0x24]
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t39 = mem.r32(t38);
    ctx.ecx = static_cast<uint32_t>(t39);
    // 0x00410118: xor ecx, esp
    uint32_t t40 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t40);
    ctx.ecx = static_cast<uint32_t>(t40);
    // 0x0041011a: call 0x4e02f8
    uint32_t t41 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    mem.w32(t41, 0x0041011fu);
    hle_crt_004e02f8(ctx, mem);
    // 0x0041011f: add esp, 0x28
    uint32_t t42 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000028u, t42);
    ctx.esp = static_cast<uint32_t>(t42);
    // 0x00410122: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00410139: {
    // 0x00410139: mov eax, dword ptr [0x5545f4]
    uint32_t t43 = mem.r32(0x005545f4u);
    ctx.eax = static_cast<uint32_t>(t43);
    // 0x0041013e: mov ecx, dword ptr [eax]
    uint32_t t44 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t44);
    // 0x00410140: mov edx, dword ptr [ecx + 0x34]
    uint32_t t45 = static_cast<uint32_t>(ctx.ecx + 0x00000034u);
    uint32_t t46 = mem.r32(t45);
    ctx.edx = static_cast<uint32_t>(t46);
    // 0x00410143: push 6
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, 0x00000006u);
    // 0x00410145: push esi
    uint32_t t48 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    mem.w32(t48, ctx.esi);
    // 0x00410146: push eax
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, ctx.eax);
    // 0x00410147: call edx
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, 0x00410149u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x00410149: test eax, eax
    uint32_t t51 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t51);
    // 0x0041014b: jne 0x410112
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00410112;
}
{
    // 0x0041014d: mov eax, dword ptr [0x5545f4]
    uint32_t t52 = mem.r32(0x005545f4u);
    ctx.eax = static_cast<uint32_t>(t52);
    // 0x00410152: mov ecx, dword ptr [eax]
    uint32_t t53 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t53);
    // 0x00410154: lea edx, [esp]
    ctx.edx = static_cast<uint32_t>(ctx.esp);
    // 0x00410157: push edx
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, ctx.edx);
    // 0x00410158: push 1
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, 0x00000001u);
    // 0x0041015a: push eax
    uint32_t t56 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    mem.w32(t56, ctx.eax);
    // 0x0041015b: mov eax, dword ptr [ecx + 0x18]
    uint32_t t57 = static_cast<uint32_t>(ctx.ecx + 0x00000018u);
    uint32_t t58 = mem.r32(t57);
    ctx.eax = static_cast<uint32_t>(t58);
    // 0x0041015e: call eax
    uint32_t t59 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    mem.w32(t59, 0x00410160u);
    call_indirect(ctx, mem, ctx.eax);
    // 0x00410160: mov eax, dword ptr [0x5545f4]
    uint32_t t60 = mem.r32(0x005545f4u);
    ctx.eax = static_cast<uint32_t>(t60);
    // 0x00410165: mov ecx, dword ptr [eax]
    uint32_t t61 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t61);
    // 0x00410167: mov edx, dword ptr [ecx + 0x1c]
    uint32_t t62 = static_cast<uint32_t>(ctx.ecx + 0x0000001cu);
    uint32_t t63 = mem.r32(t62);
    ctx.edx = static_cast<uint32_t>(t63);
    // 0x0041016a: push eax
    uint32_t t64 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    mem.w32(t64, ctx.eax);
    // 0x0041016b: call edx
    uint32_t t65 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t65);
    mem.w32(t65, 0x0041016du);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0041016d: mov ecx, dword ptr [esp + 0x24]
    uint32_t t66 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t67 = mem.r32(t66);
    ctx.ecx = static_cast<uint32_t>(t67);
    // 0x00410171: xor ecx, esp
    uint32_t t68 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t68);
    ctx.ecx = static_cast<uint32_t>(t68);
    // 0x00410173: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x00410178: call 0x4e02f8
    uint32_t t69 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    mem.w32(t69, 0x0041017du);
    hle_crt_004e02f8(ctx, mem);
    // 0x0041017d: add esp, 0x28
    uint32_t t70 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000028u, t70);
    ctx.esp = static_cast<uint32_t>(t70);
    // 0x00410180: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004106d0 | subsystem=Input | canonical | 34 blocks | 138 insns
void sub_004106d0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004106d0: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x004106d1: push ebx
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebx);
    // 0x004106d2: mov ebx, dword ptr [0x76e9b8]
    uint32_t t2 = mem.r32(0x0076e9b8u);
    ctx.ebx = static_cast<uint32_t>(t2);
    // 0x004106d8: push ebp
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.ebp);
    // 0x004106d9: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x004106da: push edi
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.edi);
    // 0x004106db: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x004106dd: lea esi, [edi*8]
    uint32_t t6 = recomp_detail::shl<uint32_t>(ctx.edi, 0x00000003u);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x004106e4: sub esi, edi
    uint32_t t7 = static_cast<uint32_t>(ctx.esi - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edi, t7);
    ctx.esi = static_cast<uint32_t>(t7);
    // 0x004106e6: xor ebp, ebp
    uint32_t t8 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t8);
    ctx.ebp = static_cast<uint32_t>(t8);
    // 0x004106e8: cmp ebx, ebp
    uint32_t t9 = static_cast<uint32_t>(ctx.ebx - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.ebp, t9);
    // 0x004106ea: lea esi, [esi*8 + 0x5545f8]
    uint32_t t10 = recomp_detail::shl<uint32_t>(ctx.esi, 0x00000003u);
    uint32_t t11 = static_cast<uint32_t>(t10 + 0x005545f8u);
    ctx.esi = static_cast<uint32_t>(t11);
    // 0x004106f1: je 0x410710
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410710;
    goto bb_004106f3;
}
bb_00410710: {
    // 0x00410710: call 0x4e0bf2
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x00410715u);
    hle_crt_004e0bf2(ctx, mem);
    // 0x00410715: mov ebx, dword ptr [0x76e9b8]
    uint32_t t13 = mem.r32(0x0076e9b8u);
    ctx.ebx = static_cast<uint32_t>(t13);
    goto bb_0041071b;
}
bb_004106f3: {
    // 0x004106f3: mov ecx, dword ptr [0x76e9bc]
    uint32_t t14 = mem.r32(0x0076e9bcu);
    ctx.ecx = static_cast<uint32_t>(t14);
    // 0x004106f9: sub ecx, ebx
    uint32_t t15 = static_cast<uint32_t>(ctx.ecx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebx, t15);
    ctx.ecx = static_cast<uint32_t>(t15);
    // 0x004106fb: mov eax, 0x30c30c31
    ctx.eax = static_cast<uint32_t>(0x30c30c31u);
    // 0x00410700: imul ecx
    uint64_t t16 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t17 = static_cast<uint32_t>(t16);
    uint32_t t18 = static_cast<uint32_t>(t16 >> 32);
    ctx.eax = static_cast<uint32_t>(t17);
    ctx.edx = static_cast<uint32_t>(t18);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t16);
    // 0x00410702: sar edx, 6
    uint32_t t19 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x06u}) & 0x0000001fu);
    uint32_t t20 = recomp_detail::sar<uint32_t>(ctx.edx, t19);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t19, t20);
    ctx.edx = static_cast<uint32_t>(t20);
    // 0x00410705: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x00410707: shr eax, 0x1f
    uint32_t t21 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t22 = recomp_detail::shr<uint32_t>(ctx.eax, t21);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t21, t22);
    ctx.eax = static_cast<uint32_t>(t22);
    // 0x0041070a: add eax, edx
    uint32_t t23 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t23);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x0041070c: cmp edi, eax
    uint32_t t24 = static_cast<uint32_t>(ctx.edi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.eax, t24);
    // 0x0041070e: jb 0x41071b
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_0041071b;
    goto bb_00410710;
}
bb_0041071b: {
    // 0x0041071b: imul edi, edi, 0x150
    uint64_t t25 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.edi)) * static_cast<int64_t>(static_cast<int32_t>(0x00000150u)));
    uint32_t t26 = static_cast<uint32_t>(t25);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t25);
    ctx.edi = static_cast<uint32_t>(t26);
    // 0x00410721: fild dword ptr [edi + ebx + 0x40]
    uint32_t t27 = static_cast<uint32_t>(ctx.edi + ctx.ebx);
    uint32_t t28 = static_cast<uint32_t>(t27 + 0x00000040u);
    double t29 = static_cast<double>(static_cast<int32_t>(mem.r32(t28)));
    ctx.fpu_push(t29);
    // 0x00410725: fld qword ptr [0x53d7e0]
    double t30 = mem.rf64(0x0053d7e0u);
    ctx.fpu_push(t30);
    // 0x0041072b: fmul st(1), st(0)
    double t31 = ctx.fpu_st(1);
    double t32 = ctx.fpu_st(0);
    double t33 = (t31 * t32);
    ctx.fpu_st(1) = t33;
    // 0x0041072d: fxch st(1)
    recomp_detail::fpu_swap(ctx, 1);
    // 0x0041072f: lea edi, [edi + ebx + 0x40]
    uint32_t t34 = static_cast<uint32_t>(ctx.edi + ctx.ebx);
    uint32_t t35 = static_cast<uint32_t>(t34 + 0x00000040u);
    ctx.edi = static_cast<uint32_t>(t35);
    // 0x00410733: call 0x4f49f0
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, 0x00410738u);
    hle_crt_004f49f0(ctx, mem);
    // 0x00410738: mov dword ptr [esi], eax
    mem.w32(ctx.esi, ctx.eax);
    // 0x0041073a: fild dword ptr [edi + 4]
    uint32_t t37 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    double t38 = static_cast<double>(static_cast<int32_t>(mem.r32(t37)));
    ctx.fpu_push(t38);
    // 0x0041073d: fmul st(1)
    double t39 = ctx.fpu_st(0);
    double t40 = ctx.fpu_st(1);
    double t41 = (t39 * t40);
    ctx.fpu_st(0) = t41;
    // 0x0041073f: call 0x4f49f0
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, 0x00410744u);
    hle_crt_004f49f0(ctx, mem);
    // 0x00410744: mov dword ptr [esi + 4], eax
    uint32_t t43 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t43, ctx.eax);
    // 0x00410747: fild dword ptr [edi + 8]
    uint32_t t44 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    double t45 = static_cast<double>(static_cast<int32_t>(mem.r32(t44)));
    ctx.fpu_push(t45);
    // 0x0041074a: fmul st(1)
    double t46 = ctx.fpu_st(0);
    double t47 = ctx.fpu_st(1);
    double t48 = (t46 * t47);
    ctx.fpu_st(0) = t48;
    // 0x0041074c: call 0x4f49f0
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, 0x00410751u);
    hle_crt_004f49f0(ctx, mem);
    // 0x00410751: mov dword ptr [esi + 8], eax
    uint32_t t50 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t50, ctx.eax);
    // 0x00410754: fild dword ptr [edi + 0xc]
    uint32_t t51 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    double t52 = static_cast<double>(static_cast<int32_t>(mem.r32(t51)));
    ctx.fpu_push(t52);
    // 0x00410757: fmul st(1)
    double t53 = ctx.fpu_st(0);
    double t54 = ctx.fpu_st(1);
    double t55 = (t53 * t54);
    ctx.fpu_st(0) = t55;
    // 0x00410759: call 0x4f49f0
    uint32_t t56 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    mem.w32(t56, 0x0041075eu);
    hle_crt_004f49f0(ctx, mem);
    // 0x0041075e: mov dword ptr [esi + 0xc], eax
    uint32_t t57 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t57, ctx.eax);
    // 0x00410761: fild dword ptr [edi + 0x10]
    uint32_t t58 = static_cast<uint32_t>(ctx.edi + 0x00000010u);
    double t59 = static_cast<double>(static_cast<int32_t>(mem.r32(t58)));
    ctx.fpu_push(t59);
    // 0x00410764: fmul st(1)
    double t60 = ctx.fpu_st(0);
    double t61 = ctx.fpu_st(1);
    double t62 = (t60 * t61);
    ctx.fpu_st(0) = t62;
    // 0x00410766: call 0x4f49f0
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, 0x0041076bu);
    hle_crt_004f49f0(ctx, mem);
    // 0x0041076b: mov dword ptr [esi + 0x10], eax
    uint32_t t64 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    mem.w32(t64, ctx.eax);
    // 0x0041076e: fild dword ptr [edi + 0x14]
    uint32_t t65 = static_cast<uint32_t>(ctx.edi + 0x00000014u);
    double t66 = static_cast<double>(static_cast<int32_t>(mem.r32(t65)));
    ctx.fpu_push(t66);
    // 0x00410771: fmul st(1)
    double t67 = ctx.fpu_st(0);
    double t68 = ctx.fpu_st(1);
    double t69 = (t67 * t68);
    ctx.fpu_st(0) = t69;
    // 0x00410773: call 0x4f49f0
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, 0x00410778u);
    hle_crt_004f49f0(ctx, mem);
    // 0x00410778: mov dword ptr [esi + 0x14], eax
    uint32_t t71 = static_cast<uint32_t>(ctx.esi + 0x00000014u);
    mem.w32(t71, ctx.eax);
    // 0x0041077b: fimul dword ptr [edi + 0x18]
    uint32_t t72 = static_cast<uint32_t>(ctx.edi + 0x00000018u);
    double t73 = static_cast<double>(static_cast<int32_t>(mem.r32(t72)));
    double t74 = ctx.fpu_st(0);
    double t75 = (t74 * t73);
    ctx.fpu_st(0) = t75;
    // 0x0041077e: call 0x4f49f0
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    mem.w32(t76, 0x00410783u);
    hle_crt_004f49f0(ctx, mem);
    // 0x00410783: mov ecx, dword ptr [esi + 0x28]
    uint32_t t77 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    uint32_t t78 = mem.r32(t77);
    ctx.ecx = static_cast<uint32_t>(t78);
    // 0x00410786: mov ebx, dword ptr [esi + 0x24]
    uint32_t t79 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    uint32_t t80 = mem.r32(t79);
    ctx.ebx = static_cast<uint32_t>(t80);
    // 0x00410789: mov dword ptr [esi + 0x1c], eax
    uint32_t t81 = static_cast<uint32_t>(ctx.esi + 0x0000001cu);
    mem.w32(t81, ctx.eax);
    // 0x0041078c: mov eax, dword ptr [edi + 0x20]
    uint32_t t82 = static_cast<uint32_t>(ctx.edi + 0x00000020u);
    uint32_t t83 = mem.r32(t82);
    ctx.eax = static_cast<uint32_t>(t83);
    // 0x0041078f: mov dword ptr [esi + 0x18], eax
    uint32_t t84 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    mem.w32(t84, ctx.eax);
    // 0x00410792: mov dword ptr [esi + 0x28], ebp
    uint32_t t85 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    mem.w32(t85, ctx.ebp);
    // 0x00410795: mov dword ptr [esi + 0x24], ebp
    uint32_t t86 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    mem.w32(t86, ctx.ebp);
    // 0x00410798: mov dword ptr [esi + 0x30], ebp
    uint32_t t87 = static_cast<uint32_t>(ctx.esi + 0x00000030u);
    mem.w32(t87, ctx.ebp);
    // 0x0041079b: mov dword ptr [esi + 0x2c], ebp
    uint32_t t88 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    mem.w32(t88, ctx.ebp);
    // 0x0041079e: mov dword ptr [esp + 0x10], ecx
    uint32_t t89 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t89, ctx.ecx);
    // 0x004107a2: mov eax, 2
    ctx.eax = static_cast<uint32_t>(0x00000002u);
    // 0x004107a7: lea ebp, [edi + 0x31]
    uint32_t t90 = static_cast<uint32_t>(ctx.edi + 0x00000031u);
    ctx.ebp = static_cast<uint32_t>(t90);
    // 0x004107aa: lea ebx, [ebx]
    ctx.ebx = static_cast<uint32_t>(ctx.ebx);
}
bb_004107b0: {
    // 0x004107b0: lea ecx, [eax - 2]
    uint32_t t91 = static_cast<uint32_t>(ctx.eax + 0xfffffffeu);
    ctx.ecx = static_cast<uint32_t>(t91);
    // 0x004107b3: mov edx, 1
    ctx.edx = static_cast<uint32_t>(0x00000001u);
    // 0x004107b8: shl edx, cl
    uint32_t t92 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t93 = static_cast<uint32_t>(t92 & 0x0000001fu);
    uint32_t t94 = recomp_detail::shl<uint32_t>(ctx.edx, t93);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.edx, t93, t94);
    ctx.edx = static_cast<uint32_t>(t94);
    // 0x004107ba: test byte ptr [ebp - 1], 0x80
    uint32_t t95 = static_cast<uint32_t>(ctx.ebp + 0xffffffffu);
    uint8_t t96 = mem.r8(t95);
    uint8_t t97 = static_cast<uint8_t>(static_cast<uint32_t>(t96) & static_cast<uint32_t>(uint8_t{0x80u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t97);
    // 0x004107be: je 0x4107d0
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004107d0;
    goto bb_004107c0;
}
bb_004107d0: {
    // 0x004107d0: test ebx, edx
    uint32_t t98 = static_cast<uint32_t>(ctx.ebx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t98);
    // 0x004107d2: je 0x4107d7
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004107d7;
    goto bb_004107d4;
}
bb_004107c0: {
    // 0x004107c0: mov edi, dword ptr [esp + 0x10]
    uint32_t t99 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t100 = mem.r32(t99);
    ctx.edi = static_cast<uint32_t>(t100);
    // 0x004107c4: test edi, edx
    uint32_t t101 = static_cast<uint32_t>(ctx.edi & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t101);
    // 0x004107c6: je 0x4107cb
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004107cb;
    goto bb_004107c8;
}
bb_004107d7: {
    // 0x004107d7: or dword ptr [esi + 0x28], edx
    uint32_t t102 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    uint32_t t103 = mem.r32(t102);
    uint32_t t104 = static_cast<uint32_t>(t103 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t104);
    mem.w32(t102, t104);
    // 0x004107da: mov edi, dword ptr [esp + 0x10]
    uint32_t t105 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t106 = mem.r32(t105);
    ctx.edi = static_cast<uint32_t>(t106);
    goto bb_004107de;
}
bb_004107d4: {
    // 0x004107d4: or dword ptr [esi + 0x30], edx
    uint32_t t107 = static_cast<uint32_t>(ctx.esi + 0x00000030u);
    uint32_t t108 = mem.r32(t107);
    uint32_t t109 = static_cast<uint32_t>(t108 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t109);
    mem.w32(t107, t109);
    goto bb_004107d7;
}
bb_004107cb: {
    // 0x004107cb: or dword ptr [esi + 0x24], edx
    uint32_t t110 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    uint32_t t111 = mem.r32(t110);
    uint32_t t112 = static_cast<uint32_t>(t111 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t112);
    mem.w32(t110, t112);
    // 0x004107ce: jmp 0x4107de
    goto bb_004107de;
}
bb_004107c8: {
    // 0x004107c8: or dword ptr [esi + 0x2c], edx
    uint32_t t113 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    uint32_t t114 = mem.r32(t113);
    uint32_t t115 = static_cast<uint32_t>(t114 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t115);
    mem.w32(t113, t115);
    goto bb_004107cb;
}
bb_004107de: {
    // 0x004107de: lea ecx, [eax - 1]
    uint32_t t116 = static_cast<uint32_t>(ctx.eax + 0xffffffffu);
    ctx.ecx = static_cast<uint32_t>(t116);
    // 0x004107e1: mov edx, 1
    ctx.edx = static_cast<uint32_t>(0x00000001u);
    // 0x004107e6: shl edx, cl
    uint32_t t117 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t118 = static_cast<uint32_t>(t117 & 0x0000001fu);
    uint32_t t119 = recomp_detail::shl<uint32_t>(ctx.edx, t118);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.edx, t118, t119);
    ctx.edx = static_cast<uint32_t>(t119);
    // 0x004107e8: test byte ptr [ebp], 0x80
    uint8_t t120 = mem.r8(ctx.ebp);
    uint8_t t121 = static_cast<uint8_t>(static_cast<uint32_t>(t120) & static_cast<uint32_t>(uint8_t{0x80u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t121);
    // 0x004107ec: je 0x4107fa
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004107fa;
    goto bb_004107ee;
}
bb_004107fa: {
    // 0x004107fa: test ebx, edx
    uint32_t t122 = static_cast<uint32_t>(ctx.ebx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t122);
    // 0x004107fc: je 0x410801
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410801;
    goto bb_004107fe;
}
bb_004107ee: {
    // 0x004107ee: test edi, edx
    uint32_t t123 = static_cast<uint32_t>(ctx.edi & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t123);
    // 0x004107f0: je 0x4107f5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004107f5;
    goto bb_004107f2;
}
bb_00410801: {
    // 0x00410801: or dword ptr [esi + 0x28], edx
    uint32_t t124 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    uint32_t t125 = mem.r32(t124);
    uint32_t t126 = static_cast<uint32_t>(t125 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t126);
    mem.w32(t124, t126);
    goto bb_00410804;
}
bb_004107fe: {
    // 0x004107fe: or dword ptr [esi + 0x30], edx
    uint32_t t127 = static_cast<uint32_t>(ctx.esi + 0x00000030u);
    uint32_t t128 = mem.r32(t127);
    uint32_t t129 = static_cast<uint32_t>(t128 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t129);
    mem.w32(t127, t129);
    goto bb_00410801;
}
bb_004107f5: {
    // 0x004107f5: or dword ptr [esi + 0x24], edx
    uint32_t t130 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    uint32_t t131 = mem.r32(t130);
    uint32_t t132 = static_cast<uint32_t>(t131 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t132);
    mem.w32(t130, t132);
    // 0x004107f8: jmp 0x410804
    goto bb_00410804;
}
bb_004107f2: {
    // 0x004107f2: or dword ptr [esi + 0x2c], edx
    uint32_t t133 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    uint32_t t134 = mem.r32(t133);
    uint32_t t135 = static_cast<uint32_t>(t134 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t135);
    mem.w32(t133, t135);
    goto bb_004107f5;
}
bb_00410804: {
    // 0x00410804: mov edx, 1
    ctx.edx = static_cast<uint32_t>(0x00000001u);
    // 0x00410809: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x0041080b: shl edx, cl
    uint32_t t136 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t137 = static_cast<uint32_t>(t136 & 0x0000001fu);
    uint32_t t138 = recomp_detail::shl<uint32_t>(ctx.edx, t137);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.edx, t137, t138);
    ctx.edx = static_cast<uint32_t>(t138);
    // 0x0041080d: test byte ptr [ebp + 1], 0x80
    uint32_t t139 = static_cast<uint32_t>(ctx.ebp + 0x00000001u);
    uint8_t t140 = mem.r8(t139);
    uint8_t t141 = static_cast<uint8_t>(static_cast<uint32_t>(t140) & static_cast<uint32_t>(uint8_t{0x80u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t141);
    // 0x00410811: je 0x41081f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041081f;
    goto bb_00410813;
}
bb_0041081f: {
    // 0x0041081f: test ebx, edx
    uint32_t t142 = static_cast<uint32_t>(ctx.ebx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t142);
    // 0x00410821: je 0x410826
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410826;
    goto bb_00410823;
}
bb_00410813: {
    // 0x00410813: test edi, edx
    uint32_t t143 = static_cast<uint32_t>(ctx.edi & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t143);
    // 0x00410815: je 0x41081a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041081a;
    goto bb_00410817;
}
bb_00410826: {
    // 0x00410826: or dword ptr [esi + 0x28], edx
    uint32_t t144 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    uint32_t t145 = mem.r32(t144);
    uint32_t t146 = static_cast<uint32_t>(t145 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t146);
    mem.w32(t144, t146);
    goto bb_00410829;
}
bb_00410823: {
    // 0x00410823: or dword ptr [esi + 0x30], edx
    uint32_t t147 = static_cast<uint32_t>(ctx.esi + 0x00000030u);
    uint32_t t148 = mem.r32(t147);
    uint32_t t149 = static_cast<uint32_t>(t148 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t149);
    mem.w32(t147, t149);
    goto bb_00410826;
}
bb_0041081a: {
    // 0x0041081a: or dword ptr [esi + 0x24], edx
    uint32_t t150 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    uint32_t t151 = mem.r32(t150);
    uint32_t t152 = static_cast<uint32_t>(t151 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t152);
    mem.w32(t150, t152);
    // 0x0041081d: jmp 0x410829
    goto bb_00410829;
}
bb_00410817: {
    // 0x00410817: or dword ptr [esi + 0x2c], edx
    uint32_t t153 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    uint32_t t154 = mem.r32(t153);
    uint32_t t155 = static_cast<uint32_t>(t154 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t155);
    mem.w32(t153, t155);
    goto bb_0041081a;
}
bb_00410829: {
    // 0x00410829: lea ecx, [eax + 1]
    uint32_t t156 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.ecx = static_cast<uint32_t>(t156);
    // 0x0041082c: mov edx, 1
    ctx.edx = static_cast<uint32_t>(0x00000001u);
    // 0x00410831: shl edx, cl
    uint32_t t157 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t158 = static_cast<uint32_t>(t157 & 0x0000001fu);
    uint32_t t159 = recomp_detail::shl<uint32_t>(ctx.edx, t158);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.edx, t158, t159);
    ctx.edx = static_cast<uint32_t>(t159);
    // 0x00410833: test byte ptr [ebp + 2], 0x80
    uint32_t t160 = static_cast<uint32_t>(ctx.ebp + 0x00000002u);
    uint8_t t161 = mem.r8(t160);
    uint8_t t162 = static_cast<uint8_t>(static_cast<uint32_t>(t161) & static_cast<uint32_t>(uint8_t{0x80u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t162);
    // 0x00410837: je 0x410845
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410845;
    goto bb_00410839;
}
bb_00410845: {
    // 0x00410845: test ebx, edx
    uint32_t t163 = static_cast<uint32_t>(ctx.ebx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t163);
    // 0x00410847: je 0x41084c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041084c;
    goto bb_00410849;
}
bb_00410839: {
    // 0x00410839: test edi, edx
    uint32_t t164 = static_cast<uint32_t>(ctx.edi & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t164);
    // 0x0041083b: je 0x410840
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410840;
    goto bb_0041083d;
}
bb_0041084c: {
    // 0x0041084c: or dword ptr [esi + 0x28], edx
    uint32_t t165 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    uint32_t t166 = mem.r32(t165);
    uint32_t t167 = static_cast<uint32_t>(t166 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t167);
    mem.w32(t165, t167);
    goto bb_0041084f;
}
bb_00410849: {
    // 0x00410849: or dword ptr [esi + 0x30], edx
    uint32_t t168 = static_cast<uint32_t>(ctx.esi + 0x00000030u);
    uint32_t t169 = mem.r32(t168);
    uint32_t t170 = static_cast<uint32_t>(t169 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t170);
    mem.w32(t168, t170);
    goto bb_0041084c;
}
bb_00410840: {
    // 0x00410840: or dword ptr [esi + 0x24], edx
    uint32_t t171 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    uint32_t t172 = mem.r32(t171);
    uint32_t t173 = static_cast<uint32_t>(t172 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t173);
    mem.w32(t171, t173);
    // 0x00410843: jmp 0x41084f
    goto bb_0041084f;
}
bb_0041083d: {
    // 0x0041083d: or dword ptr [esi + 0x2c], edx
    uint32_t t174 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    uint32_t t175 = mem.r32(t174);
    uint32_t t176 = static_cast<uint32_t>(t175 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t176);
    mem.w32(t174, t176);
    goto bb_00410840;
}
bb_0041084f: {
    // 0x0041084f: add eax, 4
    uint32_t t177 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000004u, t177);
    ctx.eax = static_cast<uint32_t>(t177);
    // 0x00410852: lea edx, [eax - 2]
    uint32_t t178 = static_cast<uint32_t>(ctx.eax + 0xfffffffeu);
    ctx.edx = static_cast<uint32_t>(t178);
    // 0x00410855: add ebp, 4
    uint32_t t179 = static_cast<uint32_t>(ctx.ebp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebp, 0x00000004u, t179);
    ctx.ebp = static_cast<uint32_t>(t179);
    // 0x00410858: cmp edx, 0x20
    uint32_t t180 = static_cast<uint32_t>(ctx.edx - 0x00000020u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000020u, t180);
    // 0x0041085b: jl 0x4107b0
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004107b0;
}
{
    // 0x00410861: pop edi
    uint32_t t181 = ctx.esp;
    uint32_t t182 = mem.r32(t181);
    uint32_t t183 = static_cast<uint32_t>(t181 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t183);
    ctx.edi = static_cast<uint32_t>(t182);
    // 0x00410862: mov byte ptr [esi + 0x34], 1
    uint32_t t184 = static_cast<uint32_t>(ctx.esi + 0x00000034u);
    mem.w8(t184, uint8_t{0x01u});
    // 0x00410866: pop esi
    uint32_t t185 = ctx.esp;
    uint32_t t186 = mem.r32(t185);
    uint32_t t187 = static_cast<uint32_t>(t185 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t187);
    ctx.esi = static_cast<uint32_t>(t186);
    // 0x00410867: pop ebp
    uint32_t t188 = ctx.esp;
    uint32_t t189 = mem.r32(t188);
    uint32_t t190 = static_cast<uint32_t>(t188 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t190);
    ctx.ebp = static_cast<uint32_t>(t189);
    // 0x00410868: pop ebx
    uint32_t t191 = ctx.esp;
    uint32_t t192 = mem.r32(t191);
    uint32_t t193 = static_cast<uint32_t>(t191 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t193);
    ctx.ebx = static_cast<uint32_t>(t192);
    // 0x00410869: pop ecx
    uint32_t t194 = ctx.esp;
    uint32_t t195 = mem.r32(t194);
    uint32_t t196 = static_cast<uint32_t>(t194 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t196);
    ctx.ecx = static_cast<uint32_t>(t195);
    // 0x0041086a: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00410870 | subsystem=Input | canonical | 12 blocks | 68 insns
void sub_00410870(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00410870: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x00410871: push ebx
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebx);
    // 0x00410872: push ebp
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebp);
    // 0x00410873: push esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.esi);
    // 0x00410874: push edi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.edi);
    // 0x00410875: xor ebp, ebp
    uint32_t t5 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    ctx.ebp = static_cast<uint32_t>(t5);
    // 0x00410877: xor edi, edi
    uint32_t t6 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t6);
    ctx.edi = static_cast<uint32_t>(t6);
}
bb_00410879: {
    // 0x00410879: mov esi, dword ptr [0x76e9b8]
    uint32_t t7 = mem.r32(0x0076e9b8u);
    ctx.esi = static_cast<uint32_t>(t7);
    // 0x0041087f: test esi, esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t8);
    // 0x00410881: mov dword ptr [esp + 0x10], edi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t9, ctx.edi);
    // 0x00410885: je 0x41091f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041091f;
    goto bb_0041088b;
}
bb_0041091f: {
    // 0x0041091f: pop edi
    uint32_t t10 = ctx.esp;
    uint32_t t11 = mem.r32(t10);
    uint32_t t12 = static_cast<uint32_t>(t10 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    ctx.edi = static_cast<uint32_t>(t11);
    // 0x00410920: pop esi
    uint32_t t13 = ctx.esp;
    uint32_t t14 = mem.r32(t13);
    uint32_t t15 = static_cast<uint32_t>(t13 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    ctx.esi = static_cast<uint32_t>(t14);
    // 0x00410921: pop ebp
    uint32_t t16 = ctx.esp;
    uint32_t t17 = mem.r32(t16);
    uint32_t t18 = static_cast<uint32_t>(t16 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    ctx.ebp = static_cast<uint32_t>(t17);
    // 0x00410922: pop ebx
    uint32_t t19 = ctx.esp;
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t19 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    ctx.ebx = static_cast<uint32_t>(t20);
    // 0x00410923: pop ecx
    uint32_t t22 = ctx.esp;
    uint32_t t23 = mem.r32(t22);
    uint32_t t24 = static_cast<uint32_t>(t22 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    ctx.ecx = static_cast<uint32_t>(t23);
    // 0x00410924: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0041088b: {
    // 0x0041088b: mov ecx, dword ptr [0x76e9bc]
    uint32_t t25 = mem.r32(0x0076e9bcu);
    ctx.ecx = static_cast<uint32_t>(t25);
    // 0x00410891: sub ecx, esi
    uint32_t t26 = static_cast<uint32_t>(ctx.ecx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.esi, t26);
    ctx.ecx = static_cast<uint32_t>(t26);
    // 0x00410893: mov eax, 0x30c30c31
    ctx.eax = static_cast<uint32_t>(0x30c30c31u);
    // 0x00410898: imul ecx
    uint64_t t27 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)));
    uint32_t t28 = static_cast<uint32_t>(t27);
    uint32_t t29 = static_cast<uint32_t>(t27 >> 32);
    ctx.eax = static_cast<uint32_t>(t28);
    ctx.edx = static_cast<uint32_t>(t29);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t27);
    // 0x0041089a: sar edx, 6
    uint32_t t30 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x06u}) & 0x0000001fu);
    uint32_t t31 = recomp_detail::sar<uint32_t>(ctx.edx, t30);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t30, t31);
    ctx.edx = static_cast<uint32_t>(t31);
    // 0x0041089d: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x0041089f: shr eax, 0x1f
    uint32_t t32 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t33 = recomp_detail::shr<uint32_t>(ctx.eax, t32);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t32, t33);
    ctx.eax = static_cast<uint32_t>(t33);
    // 0x004108a2: add eax, edx
    uint32_t t34 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t34);
    ctx.eax = static_cast<uint32_t>(t34);
    // 0x004108a4: cmp ebp, eax
    uint32_t t35 = static_cast<uint32_t>(ctx.ebp - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebp, ctx.eax, t35);
    // 0x004108a6: jae 0x41091f
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0041091f;
}
{
    // 0x004108a8: add edi, esi
    uint32_t t36 = static_cast<uint32_t>(ctx.edi + ctx.esi);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, ctx.esi, t36);
    ctx.edi = static_cast<uint32_t>(t36);
    // 0x004108aa: mov esi, dword ptr [edi + 4]
    uint32_t t37 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    uint32_t t38 = mem.r32(t37);
    ctx.esi = static_cast<uint32_t>(t38);
    // 0x004108ad: test esi, esi
    uint32_t t39 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t39);
    // 0x004108af: je 0x410906
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410906;
    goto bb_004108b1;
}
bb_00410906: {
    // 0x00410906: mov eax, ebp
    ctx.eax = static_cast<uint32_t>(ctx.ebp);
    // 0x00410908: call 0x4106d0
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, 0x0041090du);
    sub_004106d0(ctx, mem);
    // 0x0041090d: mov edi, dword ptr [esp + 0x10]
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t42 = mem.r32(t41);
    ctx.edi = static_cast<uint32_t>(t42);
    // 0x00410911: add ebp, 1
    uint32_t t43 = static_cast<uint32_t>(ctx.ebp + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebp, 0x00000001u, t43);
    ctx.ebp = static_cast<uint32_t>(t43);
    // 0x00410914: add edi, 0x150
    uint32_t t44 = static_cast<uint32_t>(ctx.edi + 0x00000150u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000150u, t44);
    ctx.edi = static_cast<uint32_t>(t44);
    // 0x0041091a: jmp 0x410879
    goto bb_00410879;
}
bb_004108b1: {
    // 0x004108b1: mov eax, dword ptr [esi]
    uint32_t t45 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t45);
    // 0x004108b3: mov ecx, dword ptr [eax + 0x64]
    uint32_t t46 = static_cast<uint32_t>(ctx.eax + 0x00000064u);
    uint32_t t47 = mem.r32(t46);
    ctx.ecx = static_cast<uint32_t>(t47);
    // 0x004108b6: push esi
    uint32_t t48 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    mem.w32(t48, ctx.esi);
    // 0x004108b7: call ecx
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, 0x004108b9u);
    call_indirect(ctx, mem, ctx.ecx);
    // 0x004108b9: test eax, eax
    uint32_t t50 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t50);
    // 0x004108bb: jge 0x4108de
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_004108de;
    goto bb_004108bd;
}
bb_004108de: {
    // 0x004108de: mov ecx, dword ptr [esi]
    uint32_t t51 = mem.r32(ctx.esi);
    ctx.ecx = static_cast<uint32_t>(t51);
    // 0x004108e0: mov edx, dword ptr [ecx + 0x24]
    uint32_t t52 = static_cast<uint32_t>(ctx.ecx + 0x00000024u);
    uint32_t t53 = mem.r32(t52);
    ctx.edx = static_cast<uint32_t>(t53);
    // 0x004108e3: lea ebx, [edi + 0x40]
    uint32_t t54 = static_cast<uint32_t>(ctx.edi + 0x00000040u);
    ctx.ebx = static_cast<uint32_t>(t54);
    // 0x004108e6: push ebx
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, ctx.ebx);
    // 0x004108e7: push 0x110
    uint32_t t56 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    mem.w32(t56, 0x00000110u);
    // 0x004108ec: push esi
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, ctx.esi);
    // 0x004108ed: call edx
    uint32_t t58 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    mem.w32(t58, 0x004108efu);
    call_indirect(ctx, mem, ctx.edx);
    // 0x004108ef: cmp dword ptr [edi + 0x34], 0
    uint32_t t59 = static_cast<uint32_t>(ctx.edi + 0x00000034u);
    uint32_t t60 = mem.r32(t59);
    uint32_t t61 = static_cast<uint32_t>(t60 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t60, 0x00000000u, t61);
    // 0x004108f3: jne 0x410906
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00410906;
    goto bb_004108f5;
}
bb_004108bd: {
    // 0x004108bd: lea ecx, [ecx]
    ctx.ecx = static_cast<uint32_t>(ctx.ecx);
    goto bb_004108c0;
}
bb_004108f5: {
    // 0x004108f5: mov eax, 0xffff
    ctx.eax = static_cast<uint32_t>(0x0000ffffu);
    // 0x004108fa: mov dword ptr [ebx + 0x20], eax
    uint32_t t62 = static_cast<uint32_t>(ctx.ebx + 0x00000020u);
    mem.w32(t62, ctx.eax);
    // 0x004108fd: mov dword ptr [ebx + 0x24], eax
    uint32_t t63 = static_cast<uint32_t>(ctx.ebx + 0x00000024u);
    mem.w32(t63, ctx.eax);
    // 0x00410900: mov dword ptr [ebx + 0x28], eax
    uint32_t t64 = static_cast<uint32_t>(ctx.ebx + 0x00000028u);
    mem.w32(t64, ctx.eax);
    // 0x00410903: mov dword ptr [ebx + 0x2c], eax
    uint32_t t65 = static_cast<uint32_t>(ctx.ebx + 0x0000002cu);
    mem.w32(t65, ctx.eax);
    goto bb_00410906;
}
bb_004108c0: {
    // 0x004108c0: mov edx, dword ptr [esi]
    uint32_t t66 = mem.r32(ctx.esi);
    ctx.edx = static_cast<uint32_t>(t66);
    // 0x004108c2: mov eax, dword ptr [edx + 0x1c]
    uint32_t t67 = static_cast<uint32_t>(ctx.edx + 0x0000001cu);
    uint32_t t68 = mem.r32(t67);
    ctx.eax = static_cast<uint32_t>(t68);
    // 0x004108c5: push esi
    uint32_t t69 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    mem.w32(t69, ctx.esi);
    // 0x004108c6: call eax
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, 0x004108c8u);
    call_indirect(ctx, mem, ctx.eax);
    // 0x004108c8: cmp eax, 0x8007001e
    uint32_t t71 = static_cast<uint32_t>(ctx.eax - 0x8007001eu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x8007001eu, t71);
    // 0x004108cd: je 0x4108c0
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004108c0;
}
{
    // 0x004108cf: mov edi, dword ptr [esp + 0x10]
    uint32_t t72 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t73 = mem.r32(t72);
    ctx.edi = static_cast<uint32_t>(t73);
    // 0x004108d3: add ebp, 1
    uint32_t t74 = static_cast<uint32_t>(ctx.ebp + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebp, 0x00000001u, t74);
    ctx.ebp = static_cast<uint32_t>(t74);
    // 0x004108d6: add edi, 0x150
    uint32_t t75 = static_cast<uint32_t>(ctx.edi + 0x00000150u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000150u, t75);
    ctx.edi = static_cast<uint32_t>(t75);
    // 0x004108dc: jmp 0x410879
    goto bb_00410879;
}
}

// sub_00410930 | subsystem=Input | canonical | 32 blocks | 108 insns
void sub_00410930(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00410930: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x00410931: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x00410933: and esp, 0xfffffff8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xfffffff8u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x00410936: sub esp, 0x10c
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x0000010cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x0000010cu, t2);
    ctx.esp = static_cast<uint32_t>(t2);
    // 0x0041093c: mov eax, dword ptr [0x54b458]
    uint32_t t3 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x00410941: xor eax, esp
    uint32_t t4 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x00410943: mov dword ptr [esp + 0x108], eax
    uint32_t t5 = static_cast<uint32_t>(ctx.esp + 0x00000108u);
    mem.w32(t5, ctx.eax);
    // 0x0041094a: push ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebx);
    // 0x0041094b: mov ebx, dword ptr [0x5544ec]
    uint32_t t7 = mem.r32(0x005544ecu);
    ctx.ebx = static_cast<uint32_t>(t7);
    // 0x00410951: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x00410952: push edi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.edi);
    // 0x00410953: push 0x100
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x00000100u);
    // 0x00410958: push 0
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0x00000000u);
    // 0x0041095a: mov ecx, 0x40
    ctx.ecx = static_cast<uint32_t>(0x00000040u);
    // 0x0041095f: mov esi, 0x5544f0
    ctx.esi = static_cast<uint32_t>(0x005544f0u);
    // 0x00410964: lea edi, [esp + 0x18]
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.edi = static_cast<uint32_t>(t12);
    // 0x00410968: push 0x5544f0
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x005544f0u);
    // 0x0041096d: rep movsd dword ptr es:[edi], dword ptr [esi]
    recomp_detail::exec_string_op<uint32_t>(ctx, mem, 0, 1);
    // 0x0041096f: call 0x4e6340
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x00410974u);
    hle_crt_004e6340(ctx, mem);
    // 0x00410974: add esp, 0xc
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t15);
    ctx.esp = static_cast<uint32_t>(t15);
    // 0x00410977: test ebx, ebx
    uint32_t t16 = static_cast<uint32_t>(ctx.ebx & ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    // 0x00410979: je 0x4109bd
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004109bd;
    goto bb_0041097b;
}
bb_004109bd: {
    // 0x004109bd: xor eax, eax
    uint32_t t17 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t17);
    ctx.eax = static_cast<uint32_t>(t17);
    // 0x004109bf: mov dl, 0x80
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(uint8_t{0x80u}));
    goto bb_004109c1;
}
bb_0041097b: {
    // 0x0041097b: mov eax, dword ptr [ebx]
    uint32_t t18 = mem.r32(ctx.ebx);
    ctx.eax = static_cast<uint32_t>(t18);
    // 0x0041097d: mov ecx, dword ptr [eax + 0x64]
    uint32_t t19 = static_cast<uint32_t>(ctx.eax + 0x00000064u);
    uint32_t t20 = mem.r32(t19);
    ctx.ecx = static_cast<uint32_t>(t20);
    // 0x00410980: push ebx
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, ctx.ebx);
    // 0x00410981: call ecx
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x00410983u);
    call_indirect(ctx, mem, ctx.ecx);
    // 0x00410983: test eax, eax
    uint32_t t23 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t23);
    // 0x00410985: jge 0x4109ab
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_004109ab;
    goto bb_00410987;
}
bb_004109c1: {
    // 0x004109c1: mov cl, byte ptr [eax + 0x5544f0]
    uint32_t t24 = static_cast<uint32_t>(ctx.eax + 0x005544f0u);
    uint8_t t25 = mem.r8(t24);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t25));
    // 0x004109c7: test dl, cl
    uint8_t t26 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t26);
    // 0x004109c9: je 0x4109d6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004109d6;
    goto bb_004109cb;
}
bb_004109ab: {
    // 0x004109ab: mov ecx, dword ptr [ebx]
    uint32_t t27 = mem.r32(ctx.ebx);
    ctx.ecx = static_cast<uint32_t>(t27);
    // 0x004109ad: mov edx, dword ptr [ecx + 0x24]
    uint32_t t28 = static_cast<uint32_t>(ctx.ecx + 0x00000024u);
    uint32_t t29 = mem.r32(t28);
    ctx.edx = static_cast<uint32_t>(t29);
    // 0x004109b0: push 0x5544f0
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x005544f0u);
    // 0x004109b5: push 0x100
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x00000100u);
    // 0x004109ba: push ebx
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, ctx.ebx);
    // 0x004109bb: call edx
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x004109bdu);
    call_indirect(ctx, mem, ctx.edx);
    goto bb_004109bd;
}
bb_00410987: {
    // 0x00410987: mov edx, dword ptr [ebx]
    uint32_t t34 = mem.r32(ctx.ebx);
    ctx.edx = static_cast<uint32_t>(t34);
    // 0x00410989: mov eax, dword ptr [edx + 0x1c]
    uint32_t t35 = static_cast<uint32_t>(ctx.edx + 0x0000001cu);
    uint32_t t36 = mem.r32(t35);
    ctx.eax = static_cast<uint32_t>(t36);
    // 0x0041098c: push ebx
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, ctx.ebx);
    // 0x0041098d: call eax
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, 0x0041098fu);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0041098f: cmp eax, 0x8007001e
    uint32_t t39 = static_cast<uint32_t>(ctx.eax - 0x8007001eu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x8007001eu, t39);
    // 0x00410994: je 0x410987
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410987;
    goto bb_00410996;
}
bb_004109d6: {
    // 0x004109d6: test byte ptr [esp + eax + 0x10], dl
    uint32_t t40 = static_cast<uint32_t>(ctx.esp + ctx.eax);
    uint32_t t41 = static_cast<uint32_t>(t40 + 0x00000010u);
    uint8_t t42 = mem.r8(t41);
    uint8_t t43 = static_cast<uint8_t>(static_cast<uint32_t>(t42) & static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t43);
    // 0x004109da: je 0x4109e5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004109e5;
    goto bb_004109dc;
}
bb_004109cb: {
    // 0x004109cb: test byte ptr [esp + eax + 0x10], dl
    uint32_t t44 = static_cast<uint32_t>(ctx.esp + ctx.eax);
    uint32_t t45 = static_cast<uint32_t>(t44 + 0x00000010u);
    uint8_t t46 = mem.r8(t45);
    uint8_t t47 = static_cast<uint8_t>(static_cast<uint32_t>(t46) & static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t47);
    // 0x004109cf: jne 0x4109e5
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004109e5;
    goto bb_004109d1;
}
bb_00410996: {
    // 0x00410996: pop edi
    uint32_t t48 = ctx.esp;
    uint32_t t49 = mem.r32(t48);
    uint32_t t50 = static_cast<uint32_t>(t48 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    ctx.edi = static_cast<uint32_t>(t49);
    // 0x00410997: pop esi
    uint32_t t51 = ctx.esp;
    uint32_t t52 = mem.r32(t51);
    uint32_t t53 = static_cast<uint32_t>(t51 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    ctx.esi = static_cast<uint32_t>(t52);
    // 0x00410998: pop ebx
    uint32_t t54 = ctx.esp;
    uint32_t t55 = mem.r32(t54);
    uint32_t t56 = static_cast<uint32_t>(t54 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    ctx.ebx = static_cast<uint32_t>(t55);
    // 0x00410999: mov ecx, dword ptr [esp + 0x108]
    uint32_t t57 = static_cast<uint32_t>(ctx.esp + 0x00000108u);
    uint32_t t58 = mem.r32(t57);
    ctx.ecx = static_cast<uint32_t>(t58);
    // 0x004109a0: xor ecx, esp
    uint32_t t59 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t59);
    ctx.ecx = static_cast<uint32_t>(t59);
    // 0x004109a2: call 0x4e02f8
    uint32_t t60 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t60);
    mem.w32(t60, 0x004109a7u);
    hle_crt_004e02f8(ctx, mem);
    // 0x004109a7: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x004109a9: pop ebp
    uint32_t t61 = ctx.esp;
    uint32_t t62 = mem.r32(t61);
    uint32_t t63 = static_cast<uint32_t>(t61 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    ctx.ebp = static_cast<uint32_t>(t62);
    // 0x004109aa: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004109e5: {
    // 0x004109e5: mov cl, byte ptr [eax + 0x5544f1]
    uint32_t t64 = static_cast<uint32_t>(ctx.eax + 0x005544f1u);
    uint8_t t65 = mem.r8(t64);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t65));
    // 0x004109eb: test dl, cl
    uint8_t t66 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t66);
    // 0x004109ed: je 0x4109fa
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004109fa;
    goto bb_004109ef;
}
bb_004109dc: {
    // 0x004109dc: or cl, 0x20
    uint8_t t67 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) | static_cast<uint32_t>(uint8_t{0x20u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t67);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t67));
    goto bb_004109df;
}
bb_004109d1: {
    // 0x004109d1: or cl, 0x40
    uint8_t t68 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) | static_cast<uint32_t>(uint8_t{0x40u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t68);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t68));
    // 0x004109d4: jmp 0x4109df
    goto bb_004109df;
}
bb_004109fa: {
    // 0x004109fa: test byte ptr [esp + eax + 0x11], dl
    uint32_t t69 = static_cast<uint32_t>(ctx.esp + ctx.eax);
    uint32_t t70 = static_cast<uint32_t>(t69 + 0x00000011u);
    uint8_t t71 = mem.r8(t70);
    uint8_t t72 = static_cast<uint8_t>(static_cast<uint32_t>(t71) & static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t72);
    // 0x004109fe: je 0x410a09
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410a09;
    goto bb_00410a00;
}
bb_004109ef: {
    // 0x004109ef: test byte ptr [esp + eax + 0x11], dl
    uint32_t t73 = static_cast<uint32_t>(ctx.esp + ctx.eax);
    uint32_t t74 = static_cast<uint32_t>(t73 + 0x00000011u);
    uint8_t t75 = mem.r8(t74);
    uint8_t t76 = static_cast<uint8_t>(static_cast<uint32_t>(t75) & static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t76);
    // 0x004109f3: jne 0x410a09
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00410a09;
    goto bb_004109f5;
}
bb_004109df: {
    // 0x004109df: mov byte ptr [eax + 0x5544f0], cl
    uint32_t t77 = static_cast<uint32_t>(ctx.eax + 0x005544f0u);
    mem.w8(t77, recomp_detail::r8l(ctx.ecx));
    goto bb_004109e5;
}
bb_00410a09: {
    // 0x00410a09: mov cl, byte ptr [eax + 0x5544f2]
    uint32_t t78 = static_cast<uint32_t>(ctx.eax + 0x005544f2u);
    uint8_t t79 = mem.r8(t78);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t79));
    // 0x00410a0f: test dl, cl
    uint8_t t80 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t80);
    // 0x00410a11: je 0x410a1e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410a1e;
    goto bb_00410a13;
}
bb_00410a00: {
    // 0x00410a00: or cl, 0x20
    uint8_t t81 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) | static_cast<uint32_t>(uint8_t{0x20u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t81);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t81));
    goto bb_00410a03;
}
bb_004109f5: {
    // 0x004109f5: or cl, 0x40
    uint8_t t82 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) | static_cast<uint32_t>(uint8_t{0x40u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t82);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t82));
    // 0x004109f8: jmp 0x410a03
    goto bb_00410a03;
}
bb_00410a1e: {
    // 0x00410a1e: test byte ptr [esp + eax + 0x12], dl
    uint32_t t83 = static_cast<uint32_t>(ctx.esp + ctx.eax);
    uint32_t t84 = static_cast<uint32_t>(t83 + 0x00000012u);
    uint8_t t85 = mem.r8(t84);
    uint8_t t86 = static_cast<uint8_t>(static_cast<uint32_t>(t85) & static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t86);
    // 0x00410a22: je 0x410a2d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410a2d;
    goto bb_00410a24;
}
bb_00410a13: {
    // 0x00410a13: test byte ptr [esp + eax + 0x12], dl
    uint32_t t87 = static_cast<uint32_t>(ctx.esp + ctx.eax);
    uint32_t t88 = static_cast<uint32_t>(t87 + 0x00000012u);
    uint8_t t89 = mem.r8(t88);
    uint8_t t90 = static_cast<uint8_t>(static_cast<uint32_t>(t89) & static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t90);
    // 0x00410a17: jne 0x410a2d
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00410a2d;
    goto bb_00410a19;
}
bb_00410a03: {
    // 0x00410a03: mov byte ptr [eax + 0x5544f1], cl
    uint32_t t91 = static_cast<uint32_t>(ctx.eax + 0x005544f1u);
    mem.w8(t91, recomp_detail::r8l(ctx.ecx));
    goto bb_00410a09;
}
bb_00410a2d: {
    // 0x00410a2d: mov cl, byte ptr [eax + 0x5544f3]
    uint32_t t92 = static_cast<uint32_t>(ctx.eax + 0x005544f3u);
    uint8_t t93 = mem.r8(t92);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t93));
    // 0x00410a33: test dl, cl
    uint8_t t94 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t94);
    // 0x00410a35: je 0x410a42
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410a42;
    goto bb_00410a37;
}
bb_00410a24: {
    // 0x00410a24: or cl, 0x20
    uint8_t t95 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) | static_cast<uint32_t>(uint8_t{0x20u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t95);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t95));
    goto bb_00410a27;
}
bb_00410a19: {
    // 0x00410a19: or cl, 0x40
    uint8_t t96 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) | static_cast<uint32_t>(uint8_t{0x40u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t96);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t96));
    // 0x00410a1c: jmp 0x410a27
    goto bb_00410a27;
}
bb_00410a42: {
    // 0x00410a42: test byte ptr [esp + eax + 0x13], dl
    uint32_t t97 = static_cast<uint32_t>(ctx.esp + ctx.eax);
    uint32_t t98 = static_cast<uint32_t>(t97 + 0x00000013u);
    uint8_t t99 = mem.r8(t98);
    uint8_t t100 = static_cast<uint8_t>(static_cast<uint32_t>(t99) & static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t100);
    // 0x00410a46: je 0x410a51
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410a51;
    goto bb_00410a48;
}
bb_00410a37: {
    // 0x00410a37: test byte ptr [esp + eax + 0x13], dl
    uint32_t t101 = static_cast<uint32_t>(ctx.esp + ctx.eax);
    uint32_t t102 = static_cast<uint32_t>(t101 + 0x00000013u);
    uint8_t t103 = mem.r8(t102);
    uint8_t t104 = static_cast<uint8_t>(static_cast<uint32_t>(t103) & static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t104);
    // 0x00410a3b: jne 0x410a51
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00410a51;
    goto bb_00410a3d;
}
bb_00410a27: {
    // 0x00410a27: mov byte ptr [eax + 0x5544f2], cl
    uint32_t t105 = static_cast<uint32_t>(ctx.eax + 0x005544f2u);
    mem.w8(t105, recomp_detail::r8l(ctx.ecx));
    goto bb_00410a2d;
}
bb_00410a51: {
    // 0x00410a51: add eax, 4
    uint32_t t106 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000004u, t106);
    ctx.eax = static_cast<uint32_t>(t106);
    // 0x00410a54: cmp eax, 0x100
    uint32_t t107 = static_cast<uint32_t>(ctx.eax - 0x00000100u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000100u, t107);
    // 0x00410a59: jl 0x4109c1
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004109c1;
    goto bb_00410a5f;
}
bb_00410a48: {
    // 0x00410a48: or cl, 0x20
    uint8_t t108 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) | static_cast<uint32_t>(uint8_t{0x20u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t108);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t108));
    goto bb_00410a4b;
}
bb_00410a3d: {
    // 0x00410a3d: or cl, 0x40
    uint8_t t109 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) | static_cast<uint32_t>(uint8_t{0x40u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t109);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t109));
    // 0x00410a40: jmp 0x410a4b
    goto bb_00410a4b;
}
bb_00410a5f: {
    // 0x00410a5f: mov ecx, dword ptr [esp + 0x114]
    uint32_t t110 = static_cast<uint32_t>(ctx.esp + 0x00000114u);
    uint32_t t111 = mem.r32(t110);
    ctx.ecx = static_cast<uint32_t>(t111);
    // 0x00410a66: pop edi
    uint32_t t112 = ctx.esp;
    uint32_t t113 = mem.r32(t112);
    uint32_t t114 = static_cast<uint32_t>(t112 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t114);
    ctx.edi = static_cast<uint32_t>(t113);
    // 0x00410a67: pop esi
    uint32_t t115 = ctx.esp;
    uint32_t t116 = mem.r32(t115);
    uint32_t t117 = static_cast<uint32_t>(t115 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t117);
    ctx.esi = static_cast<uint32_t>(t116);
    // 0x00410a68: pop ebx
    uint32_t t118 = ctx.esp;
    uint32_t t119 = mem.r32(t118);
    uint32_t t120 = static_cast<uint32_t>(t118 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t120);
    ctx.ebx = static_cast<uint32_t>(t119);
    // 0x00410a69: xor ecx, esp
    uint32_t t121 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t121);
    ctx.ecx = static_cast<uint32_t>(t121);
    // 0x00410a6b: mov byte ptr [0x5545f0], 1
    mem.w8(0x005545f0u, uint8_t{0x01u});
    // 0x00410a72: call 0x4e02f8
    uint32_t t122 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t122);
    mem.w32(t122, 0x00410a77u);
    hle_crt_004e02f8(ctx, mem);
    // 0x00410a77: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x00410a79: pop ebp
    uint32_t t123 = ctx.esp;
    uint32_t t124 = mem.r32(t123);
    uint32_t t125 = static_cast<uint32_t>(t123 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t125);
    ctx.ebp = static_cast<uint32_t>(t124);
    // 0x00410a7a: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00410a4b: {
    // 0x00410a4b: mov byte ptr [eax + 0x5544f3], cl
    uint32_t t126 = static_cast<uint32_t>(ctx.eax + 0x005544f3u);
    mem.w8(t126, recomp_detail::r8l(ctx.ecx));
    goto bb_00410a51;
}
}

// sub_00410a80 | subsystem=Input | canonical | 38 blocks | 139 insns
void sub_00410a80(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00410a80: sub esp, 0x20
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000020u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000020u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x00410a83: mov eax, dword ptr [0x54b458]
    uint32_t t1 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x00410a88: xor eax, esp
    uint32_t t2 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x00410a8a: mov dword ptr [esp + 0x1c], eax
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t3, ctx.eax);
    // 0x00410a8e: xor eax, eax
    uint32_t t4 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x00410a90: push ebx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ebx);
    // 0x00410a91: mov ebx, dword ptr [0x55498c]
    uint32_t t6 = mem.r32(0x0055498cu);
    ctx.ebx = static_cast<uint32_t>(t6);
    // 0x00410a97: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x00410a98: mov esi, dword ptr [0x5545f4]
    uint32_t t8 = mem.r32(0x005545f4u);
    ctx.esi = static_cast<uint32_t>(t8);
    // 0x00410a9e: push edi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.edi);
    // 0x00410a9f: xor edi, edi
    uint32_t t10 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.edi = static_cast<uint32_t>(t10);
    // 0x00410aa1: cmp esi, edi
    uint32_t t11 = static_cast<uint32_t>(ctx.esi - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edi, t11);
    // 0x00410aa3: mov dword ptr [esp + 0x14], eax
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t12, ctx.eax);
    // 0x00410aa7: mov dword ptr [esp + 0x18], eax
    uint32_t t13 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t13, ctx.eax);
    // 0x00410aab: mov dword ptr [esp + 0x1c], eax
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t14, ctx.eax);
    // 0x00410aaf: mov dword ptr [esp + 0x20], eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t15, ctx.eax);
    // 0x00410ab3: mov dword ptr [esp + 0x24], eax
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t16, ctx.eax);
    // 0x00410ab7: mov eax, dword ptr [0x554988]
    uint32_t t17 = mem.r32(0x00554988u);
    ctx.eax = static_cast<uint32_t>(t17);
    // 0x00410abc: mov dword ptr [esp + 0x10], eax
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t18, ctx.eax);
    // 0x00410ac0: mov dword ptr [0x55498c], edi
    mem.w32(0x0055498cu, ctx.edi);
    // 0x00410ac6: mov dword ptr [0x554988], edi
    mem.w32(0x00554988u, ctx.edi);
    // 0x00410acc: mov dword ptr [0x554994], edi
    mem.w32(0x00554994u, ctx.edi);
    // 0x00410ad2: mov dword ptr [0x554990], edi
    mem.w32(0x00554990u, ctx.edi);
    // 0x00410ad8: je 0x410c3a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410c3a;
    goto bb_00410ade;
}
bb_00410c3a: {
    // 0x00410c3a: mov ecx, dword ptr [esp + 0x28]
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t20 = mem.r32(t19);
    ctx.ecx = static_cast<uint32_t>(t20);
    // 0x00410c3e: pop edi
    uint32_t t21 = ctx.esp;
    uint32_t t22 = mem.r32(t21);
    uint32_t t23 = static_cast<uint32_t>(t21 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    ctx.edi = static_cast<uint32_t>(t22);
    // 0x00410c3f: pop esi
    uint32_t t24 = ctx.esp;
    uint32_t t25 = mem.r32(t24);
    uint32_t t26 = static_cast<uint32_t>(t24 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    ctx.esi = static_cast<uint32_t>(t25);
    // 0x00410c40: pop ebx
    uint32_t t27 = ctx.esp;
    uint32_t t28 = mem.r32(t27);
    uint32_t t29 = static_cast<uint32_t>(t27 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    ctx.ebx = static_cast<uint32_t>(t28);
    // 0x00410c41: xor ecx, esp
    uint32_t t30 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t30);
    ctx.ecx = static_cast<uint32_t>(t30);
    // 0x00410c43: mov byte ptr [0x554998], 1
    mem.w8(0x00554998u, uint8_t{0x01u});
    // 0x00410c4a: call 0x4e02f8
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x00410c4fu);
    hle_crt_004e02f8(ctx, mem);
    // 0x00410c4f: add esp, 0x20
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000020u, t32);
    ctx.esp = static_cast<uint32_t>(t32);
    // 0x00410c52: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00410ade: {
    // 0x00410ade: mov ecx, dword ptr [esi]
    uint32_t t33 = mem.r32(ctx.esi);
    ctx.ecx = static_cast<uint32_t>(t33);
    // 0x00410ae0: mov edx, dword ptr [ecx + 0x64]
    uint32_t t34 = static_cast<uint32_t>(ctx.ecx + 0x00000064u);
    uint32_t t35 = mem.r32(t34);
    ctx.edx = static_cast<uint32_t>(t35);
    // 0x00410ae3: push esi
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, ctx.esi);
    // 0x00410ae4: call edx
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, 0x00410ae6u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x00410ae6: test eax, eax
    uint32_t t38 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t38);
    // 0x00410ae8: jge 0x410b11
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_00410b11;
    goto bb_00410aea;
}
bb_00410b11: {
    // 0x00410b11: mov edx, dword ptr [esi]
    uint32_t t39 = mem.r32(ctx.esi);
    ctx.edx = static_cast<uint32_t>(t39);
    // 0x00410b13: mov ecx, dword ptr [edx + 0x24]
    uint32_t t40 = static_cast<uint32_t>(ctx.edx + 0x00000024u);
    uint32_t t41 = mem.r32(t40);
    ctx.ecx = static_cast<uint32_t>(t41);
    // 0x00410b16: push ebp
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, ctx.ebp);
    // 0x00410b17: lea eax, [esp + 0x18]
    uint32_t t43 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.eax = static_cast<uint32_t>(t43);
    // 0x00410b1b: push eax
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, ctx.eax);
    // 0x00410b1c: push 0x14
    uint32_t t45 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    mem.w32(t45, 0x00000014u);
    // 0x00410b1e: push esi
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, ctx.esi);
    // 0x00410b1f: call ecx
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, 0x00410b21u);
    call_indirect(ctx, mem, ctx.ecx);
    // 0x00410b21: mov ecx, dword ptr [esp + 0x20]
    uint32_t t48 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t49 = mem.r32(t48);
    ctx.ecx = static_cast<uint32_t>(t49);
    // 0x00410b25: mov edx, dword ptr [esp + 0x18]
    uint32_t t50 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t51 = mem.r32(t50);
    ctx.edx = static_cast<uint32_t>(t51);
    // 0x00410b29: mov eax, dword ptr [esp + 0x1c]
    uint32_t t52 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t53 = mem.r32(t52);
    ctx.eax = static_cast<uint32_t>(t53);
    // 0x00410b2d: mov dword ptr [0x554984], ecx
    mem.w32(0x00554984u, ctx.ecx);
    // 0x00410b33: xor ecx, ecx
    uint32_t t54 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t54);
    ctx.ecx = static_cast<uint32_t>(t54);
    // 0x00410b35: mov dword ptr [0x55497c], edx
    mem.w32(0x0055497cu, ctx.edx);
    // 0x00410b3b: mov dword ptr [0x554980], eax
    mem.w32(0x00554980u, ctx.eax);
    // 0x00410b40: mov dword ptr [esp + 0x10], ecx
    uint32_t t55 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t55, ctx.ecx);
    // 0x00410b44: lea ebp, [ecx + 3]
    uint32_t t56 = static_cast<uint32_t>(ctx.ecx + 0x00000003u);
    ctx.ebp = static_cast<uint32_t>(t56);
    // 0x00410b47: lea esi, [ecx + 2]
    uint32_t t57 = static_cast<uint32_t>(ctx.ecx + 0x00000002u);
    ctx.esi = static_cast<uint32_t>(t57);
    // 0x00410b4a: lea edx, [ecx + 1]
    uint32_t t58 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    ctx.edx = static_cast<uint32_t>(t58);
    // 0x00410b4d: jmp 0x410b54
    goto bb_00410b54;
}
bb_00410aea: {
    // 0x00410aea: lea ebx, [ebx]
    ctx.ebx = static_cast<uint32_t>(ctx.ebx);
    goto bb_00410af0;
}
bb_00410b54: {
    // 0x00410b54: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x00410b59: shl eax, cl
    uint32_t t59 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t60 = static_cast<uint32_t>(t59 & 0x0000001fu);
    uint32_t t61 = recomp_detail::shl<uint32_t>(ctx.eax, t60);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.eax, t60, t61);
    ctx.eax = static_cast<uint32_t>(t61);
    // 0x00410b5b: test byte ptr [esp + edx + 0x23], 0x80
    uint32_t t62 = static_cast<uint32_t>(ctx.esp + ctx.edx);
    uint32_t t63 = static_cast<uint32_t>(t62 + 0x00000023u);
    uint8_t t64 = mem.r8(t63);
    uint8_t t65 = static_cast<uint8_t>(static_cast<uint32_t>(t64) & static_cast<uint32_t>(uint8_t{0x80u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t65);
    // 0x00410b60: je 0x410b78
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410b78;
    goto bb_00410b62;
}
bb_00410af0: {
    // 0x00410af0: mov eax, dword ptr [esi]
    uint32_t t66 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t66);
    // 0x00410af2: mov ecx, dword ptr [eax + 0x1c]
    uint32_t t67 = static_cast<uint32_t>(ctx.eax + 0x0000001cu);
    uint32_t t68 = mem.r32(t67);
    ctx.ecx = static_cast<uint32_t>(t68);
    // 0x00410af5: push esi
    uint32_t t69 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    mem.w32(t69, ctx.esi);
    // 0x00410af6: call ecx
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, 0x00410af8u);
    call_indirect(ctx, mem, ctx.ecx);
    // 0x00410af8: cmp eax, 0x8007001e
    uint32_t t71 = static_cast<uint32_t>(ctx.eax - 0x8007001eu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x8007001eu, t71);
    // 0x00410afd: je 0x410af0
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410af0;
    goto bb_00410aff;
}
bb_00410b78: {
    // 0x00410b78: mov edi, dword ptr [esp + 0x14]
    uint32_t t72 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t73 = mem.r32(t72);
    ctx.edi = static_cast<uint32_t>(t73);
    // 0x00410b7c: test edi, eax
    uint32_t t74 = static_cast<uint32_t>(ctx.edi & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t74);
    // 0x00410b7e: je 0x410b86
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410b86;
    goto bb_00410b80;
}
bb_00410b62: {
    // 0x00410b62: test ebx, eax
    uint32_t t75 = static_cast<uint32_t>(ctx.ebx & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t75);
    // 0x00410b64: je 0x410b6c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410b6c;
    goto bb_00410b66;
}
bb_00410aff: {
    // 0x00410aff: pop edi
    uint32_t t76 = ctx.esp;
    uint32_t t77 = mem.r32(t76);
    uint32_t t78 = static_cast<uint32_t>(t76 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    ctx.edi = static_cast<uint32_t>(t77);
    // 0x00410b00: pop esi
    uint32_t t79 = ctx.esp;
    uint32_t t80 = mem.r32(t79);
    uint32_t t81 = static_cast<uint32_t>(t79 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    ctx.esi = static_cast<uint32_t>(t80);
    // 0x00410b01: pop ebx
    uint32_t t82 = ctx.esp;
    uint32_t t83 = mem.r32(t82);
    uint32_t t84 = static_cast<uint32_t>(t82 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    ctx.ebx = static_cast<uint32_t>(t83);
    // 0x00410b02: mov ecx, dword ptr [esp + 0x1c]
    uint32_t t85 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t86 = mem.r32(t85);
    ctx.ecx = static_cast<uint32_t>(t86);
    // 0x00410b06: xor ecx, esp
    uint32_t t87 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t87);
    ctx.ecx = static_cast<uint32_t>(t87);
    // 0x00410b08: call 0x4e02f8
    uint32_t t88 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t88);
    mem.w32(t88, 0x00410b0du);
    hle_crt_004e02f8(ctx, mem);
    // 0x00410b0d: add esp, 0x20
    uint32_t t89 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000020u, t89);
    ctx.esp = static_cast<uint32_t>(t89);
    // 0x00410b10: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00410b86: {
    // 0x00410b86: or dword ptr [0x55498c], eax
    uint32_t t90 = mem.r32(0x0055498cu);
    uint32_t t91 = static_cast<uint32_t>(t90 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t91);
    mem.w32(0x0055498cu, t91);
    goto bb_00410b8c;
}
bb_00410b80: {
    // 0x00410b80: or dword ptr [0x554994], eax
    uint32_t t92 = mem.r32(0x00554994u);
    uint32_t t93 = static_cast<uint32_t>(t92 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t93);
    mem.w32(0x00554994u, t93);
    goto bb_00410b86;
}
bb_00410b6c: {
    // 0x00410b6c: or dword ptr [0x554988], eax
    uint32_t t94 = mem.r32(0x00554988u);
    uint32_t t95 = static_cast<uint32_t>(t94 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t95);
    mem.w32(0x00554988u, t95);
    // 0x00410b72: mov edi, dword ptr [esp + 0x14]
    uint32_t t96 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t97 = mem.r32(t96);
    ctx.edi = static_cast<uint32_t>(t97);
    // 0x00410b76: jmp 0x410b8c
    goto bb_00410b8c;
}
bb_00410b66: {
    // 0x00410b66: or dword ptr [0x554990], eax
    uint32_t t98 = mem.r32(0x00554990u);
    uint32_t t99 = static_cast<uint32_t>(t98 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t99);
    mem.w32(0x00554990u, t99);
    goto bb_00410b6c;
}
bb_00410b8c: {
    // 0x00410b8c: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x00410b91: mov ecx, edx
    ctx.ecx = static_cast<uint32_t>(ctx.edx);
    // 0x00410b93: shl eax, cl
    uint32_t t100 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t101 = static_cast<uint32_t>(t100 & 0x0000001fu);
    uint32_t t102 = recomp_detail::shl<uint32_t>(ctx.eax, t101);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.eax, t101, t102);
    ctx.eax = static_cast<uint32_t>(t102);
    // 0x00410b95: test byte ptr [esp + edx + 0x24], 0x80
    uint32_t t103 = static_cast<uint32_t>(ctx.esp + ctx.edx);
    uint32_t t104 = static_cast<uint32_t>(t103 + 0x00000024u);
    uint8_t t105 = mem.r8(t104);
    uint8_t t106 = static_cast<uint8_t>(static_cast<uint32_t>(t105) & static_cast<uint32_t>(uint8_t{0x80u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t106);
    // 0x00410b9a: je 0x410bae
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410bae;
    goto bb_00410b9c;
}
bb_00410bae: {
    // 0x00410bae: test edi, eax
    uint32_t t107 = static_cast<uint32_t>(ctx.edi & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t107);
    // 0x00410bb0: je 0x410bb8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410bb8;
    goto bb_00410bb2;
}
bb_00410b9c: {
    // 0x00410b9c: test ebx, eax
    uint32_t t108 = static_cast<uint32_t>(ctx.ebx & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t108);
    // 0x00410b9e: je 0x410ba6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410ba6;
    goto bb_00410ba0;
}
bb_00410bb8: {
    // 0x00410bb8: or dword ptr [0x55498c], eax
    uint32_t t109 = mem.r32(0x0055498cu);
    uint32_t t110 = static_cast<uint32_t>(t109 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t110);
    mem.w32(0x0055498cu, t110);
    goto bb_00410bbe;
}
bb_00410bb2: {
    // 0x00410bb2: or dword ptr [0x554994], eax
    uint32_t t111 = mem.r32(0x00554994u);
    uint32_t t112 = static_cast<uint32_t>(t111 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t112);
    mem.w32(0x00554994u, t112);
    goto bb_00410bb8;
}
bb_00410ba6: {
    // 0x00410ba6: or dword ptr [0x554988], eax
    uint32_t t113 = mem.r32(0x00554988u);
    uint32_t t114 = static_cast<uint32_t>(t113 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t114);
    mem.w32(0x00554988u, t114);
    // 0x00410bac: jmp 0x410bbe
    goto bb_00410bbe;
}
bb_00410ba0: {
    // 0x00410ba0: or dword ptr [0x554990], eax
    uint32_t t115 = mem.r32(0x00554990u);
    uint32_t t116 = static_cast<uint32_t>(t115 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t116);
    mem.w32(0x00554990u, t116);
    goto bb_00410ba6;
}
bb_00410bbe: {
    // 0x00410bbe: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x00410bc3: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x00410bc5: shl eax, cl
    uint32_t t117 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t118 = static_cast<uint32_t>(t117 & 0x0000001fu);
    uint32_t t119 = recomp_detail::shl<uint32_t>(ctx.eax, t118);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.eax, t118, t119);
    ctx.eax = static_cast<uint32_t>(t119);
    // 0x00410bc7: test byte ptr [esp + esi + 0x24], 0x80
    uint32_t t120 = static_cast<uint32_t>(ctx.esp + ctx.esi);
    uint32_t t121 = static_cast<uint32_t>(t120 + 0x00000024u);
    uint8_t t122 = mem.r8(t121);
    uint8_t t123 = static_cast<uint8_t>(static_cast<uint32_t>(t122) & static_cast<uint32_t>(uint8_t{0x80u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t123);
    // 0x00410bcc: je 0x410be0
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410be0;
    goto bb_00410bce;
}
bb_00410be0: {
    // 0x00410be0: test edi, eax
    uint32_t t124 = static_cast<uint32_t>(ctx.edi & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t124);
    // 0x00410be2: je 0x410bea
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410bea;
    goto bb_00410be4;
}
bb_00410bce: {
    // 0x00410bce: test ebx, eax
    uint32_t t125 = static_cast<uint32_t>(ctx.ebx & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t125);
    // 0x00410bd0: je 0x410bd8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410bd8;
    goto bb_00410bd2;
}
bb_00410bea: {
    // 0x00410bea: or dword ptr [0x55498c], eax
    uint32_t t126 = mem.r32(0x0055498cu);
    uint32_t t127 = static_cast<uint32_t>(t126 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t127);
    mem.w32(0x0055498cu, t127);
    goto bb_00410bf0;
}
bb_00410be4: {
    // 0x00410be4: or dword ptr [0x554994], eax
    uint32_t t128 = mem.r32(0x00554994u);
    uint32_t t129 = static_cast<uint32_t>(t128 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t129);
    mem.w32(0x00554994u, t129);
    goto bb_00410bea;
}
bb_00410bd8: {
    // 0x00410bd8: or dword ptr [0x554988], eax
    uint32_t t130 = mem.r32(0x00554988u);
    uint32_t t131 = static_cast<uint32_t>(t130 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t131);
    mem.w32(0x00554988u, t131);
    // 0x00410bde: jmp 0x410bf0
    goto bb_00410bf0;
}
bb_00410bd2: {
    // 0x00410bd2: or dword ptr [0x554990], eax
    uint32_t t132 = mem.r32(0x00554990u);
    uint32_t t133 = static_cast<uint32_t>(t132 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t133);
    mem.w32(0x00554990u, t133);
    goto bb_00410bd8;
}
bb_00410bf0: {
    // 0x00410bf0: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x00410bf5: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x00410bf7: shl eax, cl
    uint32_t t134 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t135 = static_cast<uint32_t>(t134 & 0x0000001fu);
    uint32_t t136 = recomp_detail::shl<uint32_t>(ctx.eax, t135);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.eax, t135, t136);
    ctx.eax = static_cast<uint32_t>(t136);
    // 0x00410bf9: test byte ptr [esp + ebp + 0x24], 0x80
    uint32_t t137 = static_cast<uint32_t>(ctx.esp + ctx.ebp);
    uint32_t t138 = static_cast<uint32_t>(t137 + 0x00000024u);
    uint8_t t139 = mem.r8(t138);
    uint8_t t140 = static_cast<uint8_t>(static_cast<uint32_t>(t139) & static_cast<uint32_t>(uint8_t{0x80u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t140);
    // 0x00410bfe: je 0x410c12
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410c12;
    goto bb_00410c00;
}
bb_00410c12: {
    // 0x00410c12: test edi, eax
    uint32_t t141 = static_cast<uint32_t>(ctx.edi & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t141);
    // 0x00410c14: je 0x410c1c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410c1c;
    goto bb_00410c16;
}
bb_00410c00: {
    // 0x00410c00: test ebx, eax
    uint32_t t142 = static_cast<uint32_t>(ctx.ebx & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t142);
    // 0x00410c02: je 0x410c0a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00410c0a;
    goto bb_00410c04;
}
bb_00410c1c: {
    // 0x00410c1c: or dword ptr [0x55498c], eax
    uint32_t t143 = mem.r32(0x0055498cu);
    uint32_t t144 = static_cast<uint32_t>(t143 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t144);
    mem.w32(0x0055498cu, t144);
    goto bb_00410c22;
}
bb_00410c16: {
    // 0x00410c16: or dword ptr [0x554994], eax
    uint32_t t145 = mem.r32(0x00554994u);
    uint32_t t146 = static_cast<uint32_t>(t145 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t146);
    mem.w32(0x00554994u, t146);
    goto bb_00410c1c;
}
bb_00410c0a: {
    // 0x00410c0a: or dword ptr [0x554988], eax
    uint32_t t147 = mem.r32(0x00554988u);
    uint32_t t148 = static_cast<uint32_t>(t147 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t148);
    mem.w32(0x00554988u, t148);
    // 0x00410c10: jmp 0x410c22
    goto bb_00410c22;
}
bb_00410c04: {
    // 0x00410c04: or dword ptr [0x554990], eax
    uint32_t t149 = mem.r32(0x00554990u);
    uint32_t t150 = static_cast<uint32_t>(t149 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t150);
    mem.w32(0x00554990u, t150);
    goto bb_00410c0a;
}
bb_00410c22: {
    // 0x00410c22: add dword ptr [esp + 0x10], 4
    uint32_t t151 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t152 = mem.r32(t151);
    uint32_t t153 = static_cast<uint32_t>(t152 + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t152, 0x00000004u, t153);
    mem.w32(t151, t153);
    // 0x00410c27: add edx, 4
    uint32_t t154 = static_cast<uint32_t>(ctx.edx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000004u, t154);
    ctx.edx = static_cast<uint32_t>(t154);
    // 0x00410c2a: add esi, 4
    uint32_t t155 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000004u, t155);
    ctx.esi = static_cast<uint32_t>(t155);
    // 0x00410c2d: add ebp, 4
    uint32_t t156 = static_cast<uint32_t>(ctx.ebp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebp, 0x00000004u, t156);
    ctx.ebp = static_cast<uint32_t>(t156);
    // 0x00410c30: cmp edx, 9
    uint32_t t157 = static_cast<uint32_t>(ctx.edx - 0x00000009u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000009u, t157);
    // 0x00410c33: jl 0x410b50
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_00410b50;
    goto bb_00410c39;
}
bb_00410b50: {
    // 0x00410b50: mov ecx, dword ptr [esp + 0x10]
    uint32_t t158 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t159 = mem.r32(t158);
    ctx.ecx = static_cast<uint32_t>(t159);
    goto bb_00410b54;
}
bb_00410c39: {
    // 0x00410c39: pop ebp
    uint32_t t160 = ctx.esp;
    uint32_t t161 = mem.r32(t160);
    uint32_t t162 = static_cast<uint32_t>(t160 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t162);
    ctx.ebp = static_cast<uint32_t>(t161);
    goto bb_00410c3a;
}
}

// sub_0041ec80 | subsystem=Input | canonical | 3 blocks | 11 insns
void sub_0041ec80(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041ec80: test byte ptr [esp + 4], 1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint8_t t1 = mem.r8(t0);
    uint8_t t2 = static_cast<uint8_t>(static_cast<uint32_t>(t1) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t2);
    // 0x0041ec85: push esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.esi);
    // 0x0041ec86: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x0041ec88: mov dword ptr [esi], 0x5359dc
    mem.w32(ctx.esi, 0x005359dcu);
    // 0x0041ec8e: je 0x41ec99
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041ec99;
    goto bb_0041ec90;
}
bb_0041ec99: {
    // 0x0041ec99: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0041ec9b: pop esi
    uint32_t t4 = ctx.esp;
    uint32_t t5 = mem.r32(t4);
    uint32_t t6 = static_cast<uint32_t>(t4 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    ctx.esi = static_cast<uint32_t>(t5);
    // 0x0041ec9c: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0041ec90: {
    // 0x0041ec90: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x0041ec91: call 0x4e02f3
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x0041ec96u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0041ec96: add esp, 4
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t9);
    ctx.esp = static_cast<uint32_t>(t9);
    goto bb_0041ec99;
}
}

// sub_0041ecb0 | subsystem=Input | canonical | 1 blocks | 47 insns
void sub_0041ecb0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041ecb0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0041ecb2: push 0x513440
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00513440u);
    // 0x0041ecb7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0041ecbd: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0041ecbe: push ecx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ecx);
    // 0x0041ecbf: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0041ecc4: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0041ecc6: push eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.eax);
    // 0x0041ecc7: lea eax, [esp + 8]
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x0041eccb: mov dword ptr fs:[0], eax
    uint32_t t10 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t10, ctx.eax);
    // 0x0041ecd1: push 0x4d5ef0
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0x004d5ef0u);
    // 0x0041ecd6: push 0x41f2c0
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x0041f2c0u);
    // 0x0041ecdb: push 4
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x00000004u);
    // 0x0041ecdd: push 0x2c
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x0000002cu);
    // 0x0041ecdf: push 0x771398
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x00771398u);
    // 0x0041ece4: mov dword ptr [esp + 0x18], 0x770f30
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t16, 0x00770f30u);
    // 0x0041ecec: mov dword ptr [0x770f30], 0x535a04
    mem.w32(0x00770f30u, 0x00535a04u);
    // 0x0041ecf6: call 0x4e1c97
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x0041ecfbu);
    hle_crt_004e1c97(ctx, mem);
    // 0x0041ecfb: push 0x4d5ef0
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x004d5ef0u);
    // 0x0041ed00: push 0x41f2c0
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x0041f2c0u);
    // 0x0041ed05: push 4
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x00000004u);
    // 0x0041ed07: push 0x2c
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x0000002cu);
    // 0x0041ed09: push 0x771448
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x00771448u);
    // 0x0041ed0e: mov dword ptr [esp + 0x24], 0
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t23, 0x00000000u);
    // 0x0041ed16: call 0x4e1c97
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x0041ed1bu);
    hle_crt_004e1c97(ctx, mem);
    // 0x0041ed1b: push 0x4d5ef0
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x004d5ef0u);
    // 0x0041ed20: push 0x41f2c0
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x0041f2c0u);
    // 0x0041ed25: push 4
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x00000004u);
    // 0x0041ed27: push 0x2c
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x0000002cu);
    // 0x0041ed29: push 0x7714f8
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x007714f8u);
    // 0x0041ed2e: mov byte ptr [esp + 0x24], 1
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w8(t30, uint8_t{0x01u});
    // 0x0041ed33: call 0x4e1c97
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x0041ed38u);
    hle_crt_004e1c97(ctx, mem);
    // 0x0041ed38: push 0x200
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x00000200u);
    // 0x0041ed3d: push 0
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x00000000u);
    // 0x0041ed3f: push 0x770f98
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x00770f98u);
    // 0x0041ed44: call 0x4e6340
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, 0x0041ed49u);
    hle_crt_004e6340(ctx, mem);
    // 0x0041ed49: push 0x200
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, 0x00000200u);
    // 0x0041ed4e: push 0
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, 0x00000000u);
    // 0x0041ed50: push 0x771198
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, 0x00771198u);
    // 0x0041ed55: call 0x4e6340
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, 0x0041ed5au);
    hle_crt_004e6340(ctx, mem);
    // 0x0041ed5a: add esp, 0x18
    uint32_t t40 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000018u, t40);
    ctx.esp = static_cast<uint32_t>(t40);
    // 0x0041ed5d: mov eax, 0x770f30
    ctx.eax = static_cast<uint32_t>(0x00770f30u);
    // 0x0041ed62: mov ecx, dword ptr [esp + 8]
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t42 = mem.r32(t41);
    ctx.ecx = static_cast<uint32_t>(t42);
    // 0x0041ed66: mov dword ptr fs:[0], ecx
    uint32_t t43 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t43, ctx.ecx);
    // 0x0041ed6d: pop ecx
    uint32_t t44 = ctx.esp;
    uint32_t t45 = mem.r32(t44);
    uint32_t t46 = static_cast<uint32_t>(t44 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    ctx.ecx = static_cast<uint32_t>(t45);
    // 0x0041ed6e: add esp, 0x10
    uint32_t t47 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t47);
    ctx.esp = static_cast<uint32_t>(t47);
    // 0x0041ed71: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0041ed80 | subsystem=Input | canonical | 3 blocks | 11 insns
void sub_0041ed80(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041ed80: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x0041ed81: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x0041ed83: call 0x41eda0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0041ed88u);
    sub_0041eda0(ctx, mem);
    // 0x0041ed88: test byte ptr [esp + 8], 1
    uint32_t t2 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint8_t t3 = mem.r8(t2);
    uint8_t t4 = static_cast<uint8_t>(static_cast<uint32_t>(t3) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t4);
    // 0x0041ed8d: je 0x41ed98
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0041ed98;
    goto bb_0041ed8f;
}
bb_0041ed98: {
    // 0x0041ed98: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0041ed9a: pop esi
    uint32_t t5 = ctx.esp;
    uint32_t t6 = mem.r32(t5);
    uint32_t t7 = static_cast<uint32_t>(t5 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x0041ed9b: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0041ed8f: {
    // 0x0041ed8f: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x0041ed90: call 0x4e02f3
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x0041ed95u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0041ed95: add esp, 4
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t10);
    ctx.esp = static_cast<uint32_t>(t10);
    goto bb_0041ed98;
}
}

// sub_0041eda0 | subsystem=Input | canonical | 1 blocks | 41 insns
void sub_0041eda0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041eda0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0041eda2: push 0x5133f0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005133f0u);
    // 0x0041eda7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0041edad: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0041edae: push ecx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ecx);
    // 0x0041edaf: push esi
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.esi);
    // 0x0041edb0: mov eax, dword ptr [0x54b458]
    uint32_t t7 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0041edb5: xor eax, esp
    uint32_t t8 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t8);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x0041edb7: push eax
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.eax);
    // 0x0041edb8: lea eax, [esp + 0xc]
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0041edbc: mov dword ptr fs:[0], eax
    uint32_t t11 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t11, ctx.eax);
    // 0x0041edc2: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x0041edc4: mov dword ptr [esp + 8], esi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    mem.w32(t12, ctx.esi);
    // 0x0041edc8: mov dword ptr [esi], 0x535a04
    mem.w32(ctx.esi, 0x00535a04u);
    // 0x0041edce: push 0x4d5ef0
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x004d5ef0u);
    // 0x0041edd3: push 4
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x00000004u);
    // 0x0041edd5: push 0x2c
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x0000002cu);
    // 0x0041edd7: lea eax, [esi + 0x5c8]
    uint32_t t16 = static_cast<uint32_t>(ctx.esi + 0x000005c8u);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0041eddd: push eax
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, ctx.eax);
    // 0x0041edde: mov dword ptr [esp + 0x24], 1
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t18, 0x00000001u);
    // 0x0041ede6: call 0x4e1c34
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x0041edebu);
    hle_crt_004e1c34(ctx, mem);
    // 0x0041edeb: push 0x4d5ef0
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x004d5ef0u);
    // 0x0041edf0: push 4
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x00000004u);
    // 0x0041edf2: push 0x2c
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x0000002cu);
    // 0x0041edf4: lea ecx, [esi + 0x518]
    uint32_t t23 = static_cast<uint32_t>(ctx.esi + 0x00000518u);
    ctx.ecx = static_cast<uint32_t>(t23);
    // 0x0041edfa: push ecx
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, ctx.ecx);
    // 0x0041edfb: mov byte ptr [esp + 0x24], 0
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w8(t25, uint8_t{0x00u});
    // 0x0041ee00: call 0x4e1c34
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x0041ee05u);
    hle_crt_004e1c34(ctx, mem);
    // 0x0041ee05: push 0x4d5ef0
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x004d5ef0u);
    // 0x0041ee0a: push 4
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x00000004u);
    // 0x0041ee0c: push 0x2c
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x0000002cu);
    // 0x0041ee0e: add esi, 0x468
    uint32_t t30 = static_cast<uint32_t>(ctx.esi + 0x00000468u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000468u, t30);
    ctx.esi = static_cast<uint32_t>(t30);
    // 0x0041ee14: push esi
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, ctx.esi);
    // 0x0041ee15: mov dword ptr [esp + 0x24], 0xffffffff
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t32, 0xffffffffu);
    // 0x0041ee1d: call 0x4e1c34
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x0041ee22u);
    hle_crt_004e1c34(ctx, mem);
    // 0x0041ee22: mov ecx, dword ptr [esp + 0xc]
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t35 = mem.r32(t34);
    ctx.ecx = static_cast<uint32_t>(t35);
    // 0x0041ee26: mov dword ptr fs:[0], ecx
    uint32_t t36 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t36, ctx.ecx);
    // 0x0041ee2d: pop ecx
    uint32_t t37 = ctx.esp;
    uint32_t t38 = mem.r32(t37);
    uint32_t t39 = static_cast<uint32_t>(t37 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    ctx.ecx = static_cast<uint32_t>(t38);
    // 0x0041ee2e: pop esi
    uint32_t t40 = ctx.esp;
    uint32_t t41 = mem.r32(t40);
    uint32_t t42 = static_cast<uint32_t>(t40 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    ctx.esi = static_cast<uint32_t>(t41);
    // 0x0041ee2f: add esp, 0x10
    uint32_t t43 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t43);
    ctx.esp = static_cast<uint32_t>(t43);
    // 0x0041ee32: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0041ee40 | subsystem=Input | canonical | 3 blocks | 20 insns
void sub_0041ee40(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041ee40: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x0041ee41: push edi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.edi);
    // 0x0041ee42: mov edi, ecx
    ctx.edi = static_cast<uint32_t>(ctx.ecx);
    // 0x0041ee44: xor esi, esi
    uint32_t t2 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.esi = static_cast<uint32_t>(t2);
}
bb_0041ee46: {
    // 0x0041ee46: mov eax, dword ptr [edi]
    uint32_t t3 = mem.r32(ctx.edi);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0041ee48: mov edx, dword ptr [eax + 0x14]
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000014u);
    uint32_t t5 = mem.r32(t4);
    ctx.edx = static_cast<uint32_t>(t5);
    // 0x0041ee4b: push esi
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.esi);
    // 0x0041ee4c: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x0041ee4e: call edx
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0041ee50u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0041ee50: mov eax, dword ptr [edi]
    uint32_t t8 = mem.r32(ctx.edi);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x0041ee52: mov edx, dword ptr [eax + 0x18]
    uint32_t t9 = static_cast<uint32_t>(ctx.eax + 0x00000018u);
    uint32_t t10 = mem.r32(t9);
    ctx.edx = static_cast<uint32_t>(t10);
    // 0x0041ee55: push esi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.esi);
    // 0x0041ee56: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x0041ee58: call edx
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x0041ee5au);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0041ee5a: add esi, 1
    uint32_t t13 = static_cast<uint32_t>(ctx.esi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000001u, t13);
    ctx.esi = static_cast<uint32_t>(t13);
    // 0x0041ee5d: cmp esi, 4
    uint32_t t14 = static_cast<uint32_t>(ctx.esi - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00000004u, t14);
    // 0x0041ee60: jl 0x41ee46
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0041ee46;
}
{
    // 0x0041ee62: pop edi
    uint32_t t15 = ctx.esp;
    uint32_t t16 = mem.r32(t15);
    uint32_t t17 = static_cast<uint32_t>(t15 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    ctx.edi = static_cast<uint32_t>(t16);
    // 0x0041ee63: pop esi
    uint32_t t18 = ctx.esp;
    uint32_t t19 = mem.r32(t18);
    uint32_t t20 = static_cast<uint32_t>(t18 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    ctx.esi = static_cast<uint32_t>(t19);
    // 0x0041ee64: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0041ee70 | subsystem=Input | canonical | 3 blocks | 21 insns
void sub_0041ee70(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041ee70: push ebx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebx);
    // 0x0041ee71: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
    // 0x0041ee72: push edi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.edi);
    // 0x0041ee73: mov edi, ecx
    ctx.edi = static_cast<uint32_t>(ctx.ecx);
    // 0x0041ee75: mov dword ptr [edi + 4], 0
    uint32_t t3 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    mem.w32(t3, 0x00000000u);
    // 0x0041ee7c: xor esi, esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    ctx.esi = static_cast<uint32_t>(t4);
    // 0x0041ee7e: lea ebx, [edi + 8]
    uint32_t t5 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    ctx.ebx = static_cast<uint32_t>(t5);
}
bb_0041ee81: {
    // 0x0041ee81: mov eax, dword ptr [edi]
    uint32_t t6 = mem.r32(ctx.edi);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0041ee83: mov edx, dword ptr [eax + 0xc]
    uint32_t t7 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    uint32_t t8 = mem.r32(t7);
    ctx.edx = static_cast<uint32_t>(t8);
    // 0x0041ee86: push esi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.esi);
    // 0x0041ee87: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x0041ee89: call edx
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x0041ee8bu);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0041ee8b: mov dword ptr [ebx], 0
    mem.w32(ctx.ebx, 0x00000000u);
    // 0x0041ee91: add esi, 1
    uint32_t t11 = static_cast<uint32_t>(ctx.esi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000001u, t11);
    ctx.esi = static_cast<uint32_t>(t11);
    // 0x0041ee94: add ebx, 4
    uint32_t t12 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebx, 0x00000004u, t12);
    ctx.ebx = static_cast<uint32_t>(t12);
    // 0x0041ee97: cmp esi, 4
    uint32_t t13 = static_cast<uint32_t>(ctx.esi - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00000004u, t13);
    // 0x0041ee9a: jl 0x41ee81
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0041ee81;
}
{
    // 0x0041ee9c: pop edi
    uint32_t t14 = ctx.esp;
    uint32_t t15 = mem.r32(t14);
    uint32_t t16 = static_cast<uint32_t>(t14 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    ctx.edi = static_cast<uint32_t>(t15);
    // 0x0041ee9d: pop esi
    uint32_t t17 = ctx.esp;
    uint32_t t18 = mem.r32(t17);
    uint32_t t19 = static_cast<uint32_t>(t17 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    ctx.esi = static_cast<uint32_t>(t18);
    // 0x0041ee9e: pop ebx
    uint32_t t20 = ctx.esp;
    uint32_t t21 = mem.r32(t20);
    uint32_t t22 = static_cast<uint32_t>(t20 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    ctx.ebx = static_cast<uint32_t>(t21);
    // 0x0041ee9f: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0041eea0 | subsystem=Input | canonical | 1 blocks | 17 insns
void sub_0041eea0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041eea0: mov eax, dword ptr [esp + 4]
    uint32_t t0 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint32_t t1 = mem.r32(t0);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x0041eea4: imul eax, eax, 0x2c
    uint64_t t2 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(0x0000002cu)));
    uint32_t t3 = static_cast<uint32_t>(t2);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0041eea7: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x0041eea8: lea esi, [eax + ecx]
    uint32_t t5 = static_cast<uint32_t>(ctx.eax + ctx.ecx);
    ctx.esi = static_cast<uint32_t>(t5);
    // 0x0041eeab: push 0x2c
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0000002cu);
    // 0x0041eead: lea ecx, [esi + 0x468]
    uint32_t t7 = static_cast<uint32_t>(ctx.esi + 0x00000468u);
    ctx.ecx = static_cast<uint32_t>(t7);
    // 0x0041eeb3: push 0
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x00000000u);
    // 0x0041eeb5: push ecx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ecx);
    // 0x0041eeb6: call 0x4e6340
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x0041eebbu);
    hle_crt_004e6340(ctx, mem);
    // 0x0041eebb: push 0x2c
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0x0000002cu);
    // 0x0041eebd: push 0
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x00000000u);
    // 0x0041eebf: add esi, 0x518
    uint32_t t13 = static_cast<uint32_t>(ctx.esi + 0x00000518u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000518u, t13);
    ctx.esi = static_cast<uint32_t>(t13);
    // 0x0041eec5: push esi
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, ctx.esi);
    // 0x0041eec6: call 0x4e6340
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x0041eecbu);
    hle_crt_004e6340(ctx, mem);
    // 0x0041eecb: add esp, 0x18
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000018u, t16);
    ctx.esp = static_cast<uint32_t>(t16);
    // 0x0041eece: pop esi
    uint32_t t17 = ctx.esp;
    uint32_t t18 = mem.r32(t17);
    uint32_t t19 = static_cast<uint32_t>(t17 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    ctx.esi = static_cast<uint32_t>(t18);
    // 0x0041eecf: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
}

// sub_0041eee0 | subsystem=Input | canonical | 1 blocks | 13 insns
void sub_0041eee0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041eee0: mov eax, dword ptr [esp + 4]
    uint32_t t0 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint32_t t1 = mem.r32(t0);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x0041eee4: mov edx, dword ptr [esp + 8]
    uint32_t t2 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t3 = mem.r32(t2);
    ctx.edx = static_cast<uint32_t>(t3);
    // 0x0041eee8: imul eax, eax, 0x2c
    uint64_t t4 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(0x0000002cu)));
    uint32_t t5 = static_cast<uint32_t>(t4);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t4);
    ctx.eax = static_cast<uint32_t>(t5);
    // 0x0041eeeb: imul edx, edx, 0x2c
    uint64_t t6 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.edx)) * static_cast<int64_t>(static_cast<int32_t>(0x0000002cu)));
    uint32_t t7 = static_cast<uint32_t>(t6);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t6);
    ctx.edx = static_cast<uint32_t>(t7);
    // 0x0041eeee: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x0041eeef: push edi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.edi);
    // 0x0041eef0: lea esi, [eax + ecx + 0x5c8]
    uint32_t t10 = static_cast<uint32_t>(ctx.eax + ctx.ecx);
    uint32_t t11 = static_cast<uint32_t>(t10 + 0x000005c8u);
    ctx.esi = static_cast<uint32_t>(t11);
    // 0x0041eef7: lea edi, [edx + ecx + 0x518]
    uint32_t t12 = static_cast<uint32_t>(ctx.edx + ctx.ecx);
    uint32_t t13 = static_cast<uint32_t>(t12 + 0x00000518u);
    ctx.edi = static_cast<uint32_t>(t13);
    // 0x0041eefe: mov ecx, 0xb
    ctx.ecx = static_cast<uint32_t>(0x0000000bu);
    // 0x0041ef03: rep movsd dword ptr es:[edi], dword ptr [esi]
    recomp_detail::exec_string_op<uint32_t>(ctx, mem, 0, 1);
    // 0x0041ef05: pop edi
    uint32_t t14 = ctx.esp;
    uint32_t t15 = mem.r32(t14);
    uint32_t t16 = static_cast<uint32_t>(t14 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    ctx.edi = static_cast<uint32_t>(t15);
    // 0x0041ef06: pop esi
    uint32_t t17 = ctx.esp;
    uint32_t t18 = mem.r32(t17);
    uint32_t t19 = static_cast<uint32_t>(t17 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    ctx.esi = static_cast<uint32_t>(t18);
    // 0x0041ef07: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
}

// sub_0041ef10 | subsystem=Input | canonical | 3 blocks | 16 insns
void sub_0041ef10(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041ef10: mov edx, dword ptr [esp + 4]
    uint32_t t0 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint32_t t1 = mem.r32(t0);
    ctx.edx = static_cast<uint32_t>(t1);
    // 0x0041ef14: xor eax, eax
    uint32_t t2 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x0041ef16: shl edx, 7
    uint32_t t3 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x07u}) & 0x0000001fu);
    uint32_t t4 = recomp_detail::shl<uint32_t>(ctx.edx, t3);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.edx, t3, t4);
    ctx.edx = static_cast<uint32_t>(t4);
    // 0x0041ef19: lea edx, [edx + ecx + 0x68]
    uint32_t t5 = static_cast<uint32_t>(ctx.edx + ctx.ecx);
    uint32_t t6 = static_cast<uint32_t>(t5 + 0x00000068u);
    ctx.edx = static_cast<uint32_t>(t6);
    // 0x0041ef1d: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x0041ef1e: mov edi, edi
    ctx.edi = static_cast<uint32_t>(ctx.edi);
}
bb_0041ef20: {
    // 0x0041ef20: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x0041ef22: mov esi, 1
    ctx.esi = static_cast<uint32_t>(0x00000001u);
    // 0x0041ef27: shl esi, cl
    uint32_t t8 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t9 = static_cast<uint32_t>(t8 & 0x0000001fu);
    uint32_t t10 = recomp_detail::shl<uint32_t>(ctx.esi, t9);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.esi, t9, t10);
    ctx.esi = static_cast<uint32_t>(t10);
    // 0x0041ef29: add eax, 1
    uint32_t t11 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t11);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x0041ef2c: add edx, 4
    uint32_t t12 = static_cast<uint32_t>(ctx.edx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000004u, t12);
    ctx.edx = static_cast<uint32_t>(t12);
    // 0x0041ef2f: cmp eax, 0x20
    uint32_t t13 = static_cast<uint32_t>(ctx.eax - 0x00000020u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000020u, t13);
    // 0x0041ef32: mov dword ptr [edx - 4], esi
    uint32_t t14 = static_cast<uint32_t>(ctx.edx + 0xfffffffcu);
    mem.w32(t14, ctx.esi);
    // 0x0041ef35: jl 0x41ef20
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0041ef20;
}
{
    // 0x0041ef37: pop esi
    uint32_t t15 = ctx.esp;
    uint32_t t16 = mem.r32(t15);
    uint32_t t17 = static_cast<uint32_t>(t15 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    ctx.esi = static_cast<uint32_t>(t16);
    // 0x0041ef38: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
}

// sub_0041ef40 | subsystem=Input | canonical | 3 blocks | 15 insns
void sub_0041ef40(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0041ef40: mov edx, dword ptr [esp + 4]
    uint32_t t0 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint32_t t1 = mem.r32(t0);
    ctx.edx = static_cast<uint32_t>(t1);
    // 0x0041ef44: xor eax, eax
    uint32_t t2 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x0041ef46: shl edx, 7
    uint32_t t3 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x07u}) & 0x0000001fu);
    uint32_t t4 = recomp_detail::shl<uint32_t>(ctx.edx, t3);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.edx, t3, t4);
    ctx.edx = static_cast<uint32_t>(t4);
    // 0x0041ef49: lea edx, [edx + ecx + 0x268]
    uint32_t t5 = static_cast<uint32_t>(ctx.edx + ctx.ecx);
    uint32_t t6 = static_cast<uint32_t>(t5 + 0x00000268u);
    ctx.edx = static_cast<uint32_t>(t6);
    // 0x0041ef50: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
}
bb_0041ef51: {
    // 0x0041ef51: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x0041ef53: mov esi, 1
    ctx.esi = static_cast<uint32_t>(0x00000001u);
    // 0x0041ef58: shl esi, cl
    uint32_t t8 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t9 = static_cast<uint32_t>(t8 & 0x0000001fu);
    uint32_t t10 = recomp_detail::shl<uint32_t>(ctx.esi, t9);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.esi, t9, t10);
    ctx.esi = static_cast<uint32_t>(t10);
    // 0x0041ef5a: add eax, 1
    uint32_t t11 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t11);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x0041ef5d: add edx, 4
    uint32_t t12 = static_cast<uint32_t>(ctx.edx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000004u, t12);
    ctx.edx = static_cast<uint32_t>(t12);
    // 0x0041ef60: cmp eax, 0x20
    uint32_t t13 = static_cast<uint32_t>(ctx.eax - 0x00000020u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000020u, t13);
    // 0x0041ef63: mov dword ptr [edx - 4], esi
    uint32_t t14 = static_cast<uint32_t>(ctx.edx + 0xfffffffcu);
    mem.w32(t14, ctx.esi);
    // 0x0041ef66: jl 0x41ef51
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0041ef51;
}
{
    // 0x0041ef68: pop esi
    uint32_t t15 = ctx.esp;
    uint32_t t16 = mem.r32(t15);
    uint32_t t17 = static_cast<uint32_t>(t15 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    ctx.esi = static_cast<uint32_t>(t16);
    // 0x0041ef69: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
}

// sub_0042cc40 | subsystem=Input | canonical | 1 blocks | 14 insns
void sub_0042cc40(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0042cc40: mov dword ptr [esi + 4], 4
    uint32_t t0 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t0, 0x00000004u);
    // 0x0042cc47: lea eax, [esi + 8]
    uint32_t t1 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x0042cc4a: mov dword ptr [esi + 0x40f0], 0
    uint32_t t2 = static_cast<uint32_t>(ctx.esi + 0x000040f0u);
    mem.w32(t2, 0x00000000u);
    // 0x0042cc54: mov dword ptr [esi + 0x45c4], eax
    uint32_t t3 = static_cast<uint32_t>(ctx.esi + 0x000045c4u);
    mem.w32(t3, ctx.eax);
    // 0x0042cc5a: call 0x4c9210
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x0042cc5fu);
    sub_004c9210(ctx, mem);
    // 0x0042cc5f: mov ecx, dword ptr [esi + 0x45c4]
    uint32_t t5 = static_cast<uint32_t>(ctx.esi + 0x000045c4u);
    uint32_t t6 = mem.r32(t5);
    ctx.ecx = static_cast<uint32_t>(t6);
    // 0x0042cc65: mov edx, dword ptr [esi + 0x40f4]
    uint32_t t7 = static_cast<uint32_t>(ctx.esi + 0x000040f4u);
    uint32_t t8 = mem.r32(t7);
    ctx.edx = static_cast<uint32_t>(t8);
    // 0x0042cc6b: mov dword ptr [esi + 0x4498], ecx
    uint32_t t9 = static_cast<uint32_t>(ctx.esi + 0x00004498u);
    mem.w32(t9, ctx.ecx);
    // 0x0042cc71: lea eax, [esi + 0x2e9c]
    uint32_t t10 = static_cast<uint32_t>(ctx.esi + 0x00002e9cu);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0042cc77: lea ecx, [esi + 0x40f4]
    uint32_t t11 = static_cast<uint32_t>(ctx.esi + 0x000040f4u);
    ctx.ecx = static_cast<uint32_t>(t11);
    // 0x0042cc7d: mov dword ptr [esi + 0x4130], eax
    uint32_t t12 = static_cast<uint32_t>(ctx.esi + 0x00004130u);
    mem.w32(t12, ctx.eax);
    // 0x0042cc83: mov eax, dword ptr [edx + 0x80]
    uint32_t t13 = static_cast<uint32_t>(ctx.edx + 0x00000080u);
    uint32_t t14 = mem.r32(t13);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x0042cc89: mov dword ptr [esi + 0x40ec], 1
    uint32_t t15 = static_cast<uint32_t>(ctx.esi + 0x000040ecu);
    mem.w32(t15, 0x00000001u);
    // 0x0042cc93: jmp eax
    jump_indirect(ctx, mem, ctx.eax);
    return;
}
}

// sub_0049d340 | subsystem=Input | canonical | 11 blocks | 47 insns
void sub_0049d340(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0049d340: cmp dword ptr [eax], ecx
    uint32_t t0 = mem.r32(ctx.eax);
    uint32_t t1 = static_cast<uint32_t>(t0 - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t0, ctx.ecx, t1);
    // 0x0049d342: push ebx
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebx);
    // 0x0049d343: push ebp
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.ebp);
    // 0x0049d344: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x0049d345: push edi
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.edi);
    // 0x0049d346: mov edi, 0xa
    ctx.edi = static_cast<uint32_t>(0x0000000au);
    // 0x0049d34b: jge 0x49d34f
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0049d34f;
    goto bb_0049d34d;
}
bb_0049d34f: {
    // 0x0049d34f: cmp dword ptr [eax], 0x12
    uint32_t t6 = mem.r32(ctx.eax);
    uint32_t t7 = static_cast<uint32_t>(t6 - 0x00000012u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t6, 0x00000012u, t7);
    // 0x0049d352: jle 0x49d35a
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0049d35a;
    goto bb_0049d354;
}
bb_0049d34d: {
    // 0x0049d34d: mov dword ptr [eax], ecx
    mem.w32(ctx.eax, ctx.ecx);
    goto bb_0049d34f;
}
bb_0049d35a: {
    // 0x0049d35a: mov ecx, dword ptr [esp + 0x14]
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t9 = mem.r32(t8);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0049d35e: mov esi, dword ptr [eax]
    uint32_t t10 = mem.r32(ctx.eax);
    ctx.esi = static_cast<uint32_t>(t10);
    // 0x0049d360: mov ebp, 1
    ctx.ebp = static_cast<uint32_t>(0x00000001u);
    // 0x0049d365: sub ebp, ecx
    uint32_t t11 = static_cast<uint32_t>(ctx.ebp - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebp, ctx.ecx, t11);
    ctx.ebp = static_cast<uint32_t>(t11);
    // 0x0049d367: mov ebx, 2
    ctx.ebx = static_cast<uint32_t>(0x00000002u);
    // 0x0049d36c: lea esp, [esp]
    ctx.esp = static_cast<uint32_t>(ctx.esp);
    goto bb_0049d370;
}
bb_0049d354: {
    // 0x0049d354: mov dword ptr [eax], 0x12
    mem.w32(ctx.eax, 0x00000012u);
    goto bb_0049d35a;
}
bb_0049d370: {
    // 0x0049d370: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0049d372: cdq
    uint32_t t12 = recomp_detail::sar<uint32_t>(ctx.eax, 0x0000001fu);
    ctx.edx = static_cast<uint32_t>(t12);
    // 0x0049d373: idiv edi
    uint64_t t13 = ((static_cast<uint64_t>(ctx.edx) << 32) | static_cast<uint64_t>(ctx.eax));
    uint32_t t14 = recomp_detail::div64_s(t13, ctx.edi);
    uint32_t t15 = recomp_detail::mod64_s(t13, ctx.edi);
    ctx.eax = static_cast<uint32_t>(t14);
    ctx.edx = static_cast<uint32_t>(t15);
    // 0x0049d375: test eax, eax
    uint32_t t16 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    // 0x0049d377: jne 0x49d386
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049d386;
    goto bb_0049d379;
}
bb_0049d386: {
    // 0x0049d386: add al, 0x30
    uint8_t t17 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) + static_cast<uint32_t>(uint8_t{0x30u}));
    recomp_detail::update_flags_add<uint8_t>(ctx, recomp_detail::r8l(ctx.eax), uint8_t{0x30u}, t17);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t17));
    // 0x0049d388: mov byte ptr [ecx], al
    mem.w8(ctx.ecx, recomp_detail::r8l(ctx.eax));
    goto bb_0049d38a;
}
bb_0049d379: {
    // 0x0049d379: lea esi, [ecx + ebp]
    uint32_t t18 = static_cast<uint32_t>(ctx.ecx + ctx.ebp);
    ctx.esi = static_cast<uint32_t>(t18);
    // 0x0049d37c: cmp esi, 2
    uint32_t t19 = static_cast<uint32_t>(ctx.esi - 0x00000002u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00000002u, t19);
    // 0x0049d37f: je 0x49d386
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049d386;
    goto bb_0049d381;
}
bb_0049d38a: {
    // 0x0049d38a: mov esi, edx
    ctx.esi = static_cast<uint32_t>(ctx.edx);
    // 0x0049d38c: mov eax, 0x66666667
    ctx.eax = static_cast<uint32_t>(0x66666667u);
    // 0x0049d391: imul edi
    uint64_t t20 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(ctx.edi)));
    uint32_t t21 = static_cast<uint32_t>(t20);
    uint32_t t22 = static_cast<uint32_t>(t20 >> 32);
    ctx.eax = static_cast<uint32_t>(t21);
    ctx.edx = static_cast<uint32_t>(t22);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t20);
    // 0x0049d393: sar edx, 2
    uint32_t t23 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t24 = recomp_detail::sar<uint32_t>(ctx.edx, t23);
    recomp_detail::update_flags_sar<uint32_t>(ctx, ctx.edx, t23, t24);
    ctx.edx = static_cast<uint32_t>(t24);
    // 0x0049d396: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x0049d398: shr eax, 0x1f
    uint32_t t25 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x1fu}) & 0x0000001fu);
    uint32_t t26 = recomp_detail::shr<uint32_t>(ctx.eax, t25);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.eax, t25, t26);
    ctx.eax = static_cast<uint32_t>(t26);
    // 0x0049d39b: add eax, edx
    uint32_t t27 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t27);
    ctx.eax = static_cast<uint32_t>(t27);
    // 0x0049d39d: add ecx, 1
    uint32_t t28 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t28);
    ctx.ecx = static_cast<uint32_t>(t28);
    // 0x0049d3a0: sub ebx, 1
    uint32_t t29 = static_cast<uint32_t>(ctx.ebx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, 0x00000001u, t29);
    ctx.ebx = static_cast<uint32_t>(t29);
    // 0x0049d3a3: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x0049d3a5: jne 0x49d370
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049d370;
    goto bb_0049d3a7;
}
bb_0049d381: {
    // 0x0049d381: mov byte ptr [ecx], 0x20
    mem.w8(ctx.ecx, uint8_t{0x20u});
    // 0x0049d384: jmp 0x49d38a
    goto bb_0049d38a;
}
bb_0049d3a7: {
    // 0x0049d3a7: mov ecx, dword ptr [esp + 0x14]
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t31 = mem.r32(t30);
    ctx.ecx = static_cast<uint32_t>(t31);
    // 0x0049d3ab: pop edi
    uint32_t t32 = ctx.esp;
    uint32_t t33 = mem.r32(t32);
    uint32_t t34 = static_cast<uint32_t>(t32 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    ctx.edi = static_cast<uint32_t>(t33);
    // 0x0049d3ac: pop esi
    uint32_t t35 = ctx.esp;
    uint32_t t36 = mem.r32(t35);
    uint32_t t37 = static_cast<uint32_t>(t35 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    ctx.esi = static_cast<uint32_t>(t36);
    // 0x0049d3ad: pop ebp
    uint32_t t38 = ctx.esp;
    uint32_t t39 = mem.r32(t38);
    uint32_t t40 = static_cast<uint32_t>(t38 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    ctx.ebp = static_cast<uint32_t>(t39);
    // 0x0049d3ae: mov byte ptr [ecx + 2], bl
    uint32_t t41 = static_cast<uint32_t>(ctx.ecx + 0x00000002u);
    mem.w8(t41, recomp_detail::r8l(ctx.ebx));
    // 0x0049d3b1: pop ebx
    uint32_t t42 = ctx.esp;
    uint32_t t43 = mem.r32(t42);
    uint32_t t44 = static_cast<uint32_t>(t42 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    ctx.ebx = static_cast<uint32_t>(t43);
    // 0x0049d3b2: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0049f9e0 | subsystem=Input | canonical | 27 blocks | 86 insns
void sub_0049f9e0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0049f9e0: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x0049f9e1: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
    // 0x0049f9e2: push edi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.edi);
    // 0x0049f9e3: mov esi, 0x148
    ctx.esi = static_cast<uint32_t>(0x00000148u);
    // 0x0049f9e8: lea edi, [ebx + 0x14]
    uint32_t t3 = static_cast<uint32_t>(ctx.ebx + 0x00000014u);
    ctx.edi = static_cast<uint32_t>(t3);
    // 0x0049f9eb: mov ebp, 2
    ctx.ebp = static_cast<uint32_t>(0x00000002u);
}
bb_0049f9f0: {
    // 0x0049f9f0: mov eax, dword ptr [ebx]
    uint32_t t4 = mem.r32(ctx.ebx);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0049f9f2: cmp eax, -1
    uint32_t t5 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t5);
    // 0x0049f9f5: jne 0x49f9fb
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049f9fb;
    goto bb_0049f9f7;
}
bb_0049f9fb: {
    // 0x0049f9fb: imul eax, eax, 0x164
    uint64_t t6 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(0x00000164u)));
    uint32_t t7 = static_cast<uint32_t>(t6);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t6);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0049fa01: add eax, 0x74da18
    uint32_t t8 = static_cast<uint32_t>(ctx.eax + 0x0074da18u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x0074da18u, t8);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x0049fa06: mov ecx, dword ptr [eax]
    uint32_t t9 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0049fa08: test ecx, ecx
    uint32_t t10 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    // 0x0049fa0a: jne 0x49fa10
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049fa10;
    goto bb_0049fa0c;
}
bb_0049f9f7: {
    // 0x0049f9f7: xor eax, eax
    uint32_t t11 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x0049f9f9: jmp 0x49fa1d
    goto bb_0049fa1d;
}
bb_0049fa10: {
    // 0x0049fa10: mov eax, dword ptr [esi + eax - 4]
    uint32_t t12 = static_cast<uint32_t>(ctx.esi + ctx.eax);
    uint32_t t13 = static_cast<uint32_t>(t12 + 0xfffffffcu);
    uint32_t t14 = mem.r32(t13);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x0049fa14: push eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.eax);
    // 0x0049fa15: lea eax, [ecx - 1]
    uint32_t t16 = static_cast<uint32_t>(ctx.ecx + 0xffffffffu);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0049fa18: call 0x49fca0
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x0049fa1du);
    sub_0049fca0(ctx, mem);
    goto bb_0049fa1d;
}
bb_0049fa0c: {
    // 0x0049fa0c: xor eax, eax
    uint32_t t18 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    ctx.eax = static_cast<uint32_t>(t18);
    // 0x0049fa0e: jmp 0x49fa1d
}
bb_0049fa1d: {
    // 0x0049fa1d: neg eax
    uint32_t t19 = static_cast<uint32_t>(0u - ctx.eax);
    recomp_detail::update_flags_neg<uint32_t>(ctx, ctx.eax, t19);
    ctx.eax = static_cast<uint32_t>(t19);
    // 0x0049fa1f: mov dword ptr [edi + 4], eax
    uint32_t t20 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    mem.w32(t20, ctx.eax);
    // 0x0049fa22: jne 0x49fa53
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049fa53;
    goto bb_0049fa24;
}
bb_0049fa53: {
    // 0x0049fa53: mov eax, dword ptr [ebx]
    uint32_t t21 = mem.r32(ctx.ebx);
    ctx.eax = static_cast<uint32_t>(t21);
    // 0x0049fa55: cmp eax, -1
    uint32_t t22 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t22);
    // 0x0049fa58: jne 0x49fa5e
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049fa5e;
    goto bb_0049fa5a;
}
bb_0049fa24: {
    // 0x0049fa24: mov eax, dword ptr [ebx]
    uint32_t t23 = mem.r32(ctx.ebx);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x0049fa26: cmp eax, -1
    uint32_t t24 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t24);
    // 0x0049fa29: jne 0x49fa2f
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049fa2f;
    goto bb_0049fa2b;
}
bb_0049fa5e: {
    // 0x0049fa5e: imul eax, eax, 0x164
    uint64_t t25 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(0x00000164u)));
    uint32_t t26 = static_cast<uint32_t>(t25);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t25);
    ctx.eax = static_cast<uint32_t>(t26);
    // 0x0049fa64: add eax, 0x74da18
    uint32_t t27 = static_cast<uint32_t>(ctx.eax + 0x0074da18u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x0074da18u, t27);
    ctx.eax = static_cast<uint32_t>(t27);
    // 0x0049fa69: mov ecx, dword ptr [eax]
    uint32_t t28 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t28);
    // 0x0049fa6b: test ecx, ecx
    uint32_t t29 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t29);
    // 0x0049fa6d: jne 0x49fa73
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049fa73;
    goto bb_0049fa6f;
}
bb_0049fa5a: {
    // 0x0049fa5a: xor eax, eax
    uint32_t t30 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t30);
    ctx.eax = static_cast<uint32_t>(t30);
    // 0x0049fa5c: jmp 0x49fa80
    goto bb_0049fa80;
}
bb_0049fa2f: {
    // 0x0049fa2f: imul eax, eax, 0x164
    uint64_t t31 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(0x00000164u)));
    uint32_t t32 = static_cast<uint32_t>(t31);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t31);
    ctx.eax = static_cast<uint32_t>(t32);
    // 0x0049fa35: add eax, 0x74da18
    uint32_t t33 = static_cast<uint32_t>(ctx.eax + 0x0074da18u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x0074da18u, t33);
    ctx.eax = static_cast<uint32_t>(t33);
    // 0x0049fa3a: mov ecx, dword ptr [eax]
    uint32_t t34 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t34);
    // 0x0049fa3c: test ecx, ecx
    uint32_t t35 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t35);
    // 0x0049fa3e: jne 0x49fa44
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049fa44;
    goto bb_0049fa40;
}
bb_0049fa2b: {
    // 0x0049fa2b: xor eax, eax
    uint32_t t36 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t36);
    ctx.eax = static_cast<uint32_t>(t36);
    // 0x0049fa2d: jmp 0x49fa50
    goto bb_0049fa50;
}
bb_0049fa73: {
    // 0x0049fa73: mov eax, dword ptr [esi + eax + 4]
    uint32_t t37 = static_cast<uint32_t>(ctx.esi + ctx.eax);
    uint32_t t38 = static_cast<uint32_t>(t37 + 0x00000004u);
    uint32_t t39 = mem.r32(t38);
    ctx.eax = static_cast<uint32_t>(t39);
    // 0x0049fa77: push eax
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, ctx.eax);
    // 0x0049fa78: lea eax, [ecx - 1]
    uint32_t t41 = static_cast<uint32_t>(ctx.ecx + 0xffffffffu);
    ctx.eax = static_cast<uint32_t>(t41);
    // 0x0049fa7b: call 0x49fca0
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, 0x0049fa80u);
    sub_0049fca0(ctx, mem);
    goto bb_0049fa80;
}
bb_0049fa6f: {
    // 0x0049fa6f: xor eax, eax
    uint32_t t43 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t43);
    ctx.eax = static_cast<uint32_t>(t43);
    // 0x0049fa71: jmp 0x49fa80
}
bb_0049fa80: {
    // 0x0049fa80: neg eax
    uint32_t t44 = static_cast<uint32_t>(0u - ctx.eax);
    recomp_detail::update_flags_neg<uint32_t>(ctx, ctx.eax, t44);
    ctx.eax = static_cast<uint32_t>(t44);
    // 0x0049fa82: mov dword ptr [edi], eax
    mem.w32(ctx.edi, ctx.eax);
    // 0x0049fa84: jne 0x49fab5
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049fab5;
    goto bb_0049fa86;
}
bb_0049fa44: {
    // 0x0049fa44: mov edx, dword ptr [esi + eax]
    uint32_t t45 = static_cast<uint32_t>(ctx.esi + ctx.eax);
    uint32_t t46 = mem.r32(t45);
    ctx.edx = static_cast<uint32_t>(t46);
    // 0x0049fa47: push edx
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, ctx.edx);
    // 0x0049fa48: lea eax, [ecx - 1]
    uint32_t t48 = static_cast<uint32_t>(ctx.ecx + 0xffffffffu);
    ctx.eax = static_cast<uint32_t>(t48);
    // 0x0049fa4b: call 0x49fca0
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, 0x0049fa50u);
    sub_0049fca0(ctx, mem);
    goto bb_0049fa50;
}
bb_0049fa40: {
    // 0x0049fa40: xor eax, eax
    uint32_t t50 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t50);
    ctx.eax = static_cast<uint32_t>(t50);
    // 0x0049fa42: jmp 0x49fa50
}
bb_0049fa50: {
    // 0x0049fa50: mov dword ptr [edi + 4], eax
    uint32_t t51 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    mem.w32(t51, ctx.eax);
    goto bb_0049fa53;
}
bb_0049fab5: {
    // 0x0049fab5: add edi, 8
    uint32_t t52 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000008u, t52);
    ctx.edi = static_cast<uint32_t>(t52);
    // 0x0049fab8: add esi, 0x10
    uint32_t t53 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000010u, t53);
    ctx.esi = static_cast<uint32_t>(t53);
    // 0x0049fabb: sub ebp, 1
    uint32_t t54 = static_cast<uint32_t>(ctx.ebp - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebp, 0x00000001u, t54);
    ctx.ebp = static_cast<uint32_t>(t54);
    // 0x0049fabe: jne 0x49f9f0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049f9f0;
    goto bb_0049fac4;
}
bb_0049fa86: {
    // 0x0049fa86: mov eax, dword ptr [ebx]
    uint32_t t55 = mem.r32(ctx.ebx);
    ctx.eax = static_cast<uint32_t>(t55);
    // 0x0049fa88: cmp eax, -1
    uint32_t t56 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t56);
    // 0x0049fa8b: jne 0x49fa91
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049fa91;
    goto bb_0049fa8d;
}
bb_0049fac4: {
    // 0x0049fac4: pop edi
    uint32_t t57 = ctx.esp;
    uint32_t t58 = mem.r32(t57);
    uint32_t t59 = static_cast<uint32_t>(t57 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    ctx.edi = static_cast<uint32_t>(t58);
    // 0x0049fac5: pop esi
    uint32_t t60 = ctx.esp;
    uint32_t t61 = mem.r32(t60);
    uint32_t t62 = static_cast<uint32_t>(t60 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    ctx.esi = static_cast<uint32_t>(t61);
    // 0x0049fac6: pop ebp
    uint32_t t63 = ctx.esp;
    uint32_t t64 = mem.r32(t63);
    uint32_t t65 = static_cast<uint32_t>(t63 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t65);
    ctx.ebp = static_cast<uint32_t>(t64);
    // 0x0049fac7: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0049fa91: {
    // 0x0049fa91: imul eax, eax, 0x164
    uint64_t t66 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(0x00000164u)));
    uint32_t t67 = static_cast<uint32_t>(t66);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t66);
    ctx.eax = static_cast<uint32_t>(t67);
    // 0x0049fa97: add eax, 0x74da18
    uint32_t t68 = static_cast<uint32_t>(ctx.eax + 0x0074da18u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x0074da18u, t68);
    ctx.eax = static_cast<uint32_t>(t68);
    // 0x0049fa9c: mov ecx, dword ptr [eax]
    uint32_t t69 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t69);
    // 0x0049fa9e: test ecx, ecx
    uint32_t t70 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t70);
    // 0x0049faa0: jne 0x49faa6
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049faa6;
    goto bb_0049faa2;
}
bb_0049fa8d: {
    // 0x0049fa8d: xor eax, eax
    uint32_t t71 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t71);
    ctx.eax = static_cast<uint32_t>(t71);
    // 0x0049fa8f: jmp 0x49fab3
    goto bb_0049fab3;
}
bb_0049faa6: {
    // 0x0049faa6: mov edx, dword ptr [esi + eax + 8]
    uint32_t t72 = static_cast<uint32_t>(ctx.esi + ctx.eax);
    uint32_t t73 = static_cast<uint32_t>(t72 + 0x00000008u);
    uint32_t t74 = mem.r32(t73);
    ctx.edx = static_cast<uint32_t>(t74);
    // 0x0049faaa: push edx
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, ctx.edx);
    // 0x0049faab: lea eax, [ecx - 1]
    uint32_t t76 = static_cast<uint32_t>(ctx.ecx + 0xffffffffu);
    ctx.eax = static_cast<uint32_t>(t76);
    // 0x0049faae: call 0x49fca0
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, 0x0049fab3u);
    sub_0049fca0(ctx, mem);
    goto bb_0049fab3;
}
bb_0049faa2: {
    // 0x0049faa2: xor eax, eax
    uint32_t t78 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t78);
    ctx.eax = static_cast<uint32_t>(t78);
    // 0x0049faa4: jmp 0x49fab3
}
bb_0049fab3: {
    // 0x0049fab3: mov dword ptr [edi], eax
    mem.w32(ctx.edi, ctx.eax);
    goto bb_0049fab5;
}
}

// sub_0049fad0 | subsystem=Input | canonical | 10 blocks | 45 insns
void sub_0049fad0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0049fad0: push ebx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebx);
    // 0x0049fad1: push ebp
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebp);
    // 0x0049fad2: mov ebp, dword ptr [esi + 0x24]
    uint32_t t2 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    uint32_t t3 = mem.r32(t2);
    ctx.ebp = static_cast<uint32_t>(t3);
    // 0x0049fad5: push edi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.edi);
    // 0x0049fad6: xor edi, edi
    uint32_t t5 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    ctx.edi = static_cast<uint32_t>(t5);
    // 0x0049fad8: mov dword ptr [esi + 0x2c], edi
    uint32_t t6 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    mem.w32(t6, ctx.edi);
    // 0x0049fadb: mov dword ptr [esi + 0x28], edi
    uint32_t t7 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    mem.w32(t7, ctx.edi);
    // 0x0049fade: mov dword ptr [esi + 0x24], edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    mem.w32(t8, ctx.edi);
    // 0x0049fae1: mov ebx, 0x114
    ctx.ebx = static_cast<uint32_t>(0x00000114u);
}
bb_0049fae6: {
    // 0x0049fae6: mov eax, dword ptr [esi]
    uint32_t t9 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x0049fae8: cmp eax, -1
    uint32_t t10 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t10);
    // 0x0049faeb: je 0x49fb23
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049fb23;
    goto bb_0049faed;
}
bb_0049fb23: {
    // 0x0049fb23: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0049fb28: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x0049fb2a: shl eax, cl
    uint32_t t11 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t12 = static_cast<uint32_t>(t11 & 0x0000001fu);
    uint32_t t13 = recomp_detail::shl<uint32_t>(ctx.eax, t12);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.eax, t12, t13);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0049fb2c: test ebp, eax
    uint32_t t14 = static_cast<uint32_t>(ctx.ebp & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    // 0x0049fb2e: je 0x49fb33
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049fb33;
    goto bb_0049fb30;
}
bb_0049faed: {
    // 0x0049faed: imul eax, eax, 0x164
    uint64_t t15 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(0x00000164u)));
    uint32_t t16 = static_cast<uint32_t>(t15);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t15);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0049faf3: add eax, 0x74da18
    uint32_t t17 = static_cast<uint32_t>(ctx.eax + 0x0074da18u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x0074da18u, t17);
    ctx.eax = static_cast<uint32_t>(t17);
    // 0x0049faf8: mov ecx, dword ptr [eax]
    uint32_t t18 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t18);
    // 0x0049fafa: test ecx, ecx
    uint32_t t19 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t19);
    // 0x0049fafc: je 0x49fb23
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049fb23;
    goto bb_0049fafe;
}
bb_0049fb33: {
    // 0x0049fb33: add ebx, 4
    uint32_t t20 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebx, 0x00000004u, t20);
    ctx.ebx = static_cast<uint32_t>(t20);
    // 0x0049fb36: add edi, 1
    uint32_t t21 = static_cast<uint32_t>(ctx.edi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000001u, t21);
    ctx.edi = static_cast<uint32_t>(t21);
    // 0x0049fb39: cmp ebx, 0x154
    uint32_t t22 = static_cast<uint32_t>(ctx.ebx - 0x00000154u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, 0x00000154u, t22);
    // 0x0049fb3f: jl 0x49fae6
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0049fae6;
    goto bb_0049fb41;
}
bb_0049fb30: {
    // 0x0049fb30: or dword ptr [esi + 0x2c], eax
    uint32_t t23 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    uint32_t t24 = mem.r32(t23);
    uint32_t t25 = static_cast<uint32_t>(t24 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t25);
    mem.w32(t23, t25);
    goto bb_0049fb33;
}
bb_0049fafe: {
    // 0x0049fafe: mov eax, dword ptr [ebx + eax]
    uint32_t t26 = static_cast<uint32_t>(ctx.ebx + ctx.eax);
    uint32_t t27 = mem.r32(t26);
    ctx.eax = static_cast<uint32_t>(t27);
    // 0x0049fb01: push eax
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, ctx.eax);
    // 0x0049fb02: lea eax, [ecx - 1]
    uint32_t t29 = static_cast<uint32_t>(ctx.ecx + 0xffffffffu);
    ctx.eax = static_cast<uint32_t>(t29);
    // 0x0049fb05: call 0x49fca0
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x0049fb0au);
    sub_0049fca0(ctx, mem);
    // 0x0049fb0a: test eax, eax
    uint32_t t31 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t31);
    // 0x0049fb0c: je 0x49fb23
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049fb23;
    goto bb_0049fb0e;
}
bb_0049fb41: {
    // 0x0049fb41: pop edi
    uint32_t t32 = ctx.esp;
    uint32_t t33 = mem.r32(t32);
    uint32_t t34 = static_cast<uint32_t>(t32 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    ctx.edi = static_cast<uint32_t>(t33);
    // 0x0049fb42: pop ebp
    uint32_t t35 = ctx.esp;
    uint32_t t36 = mem.r32(t35);
    uint32_t t37 = static_cast<uint32_t>(t35 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    ctx.ebp = static_cast<uint32_t>(t36);
    // 0x0049fb43: pop ebx
    uint32_t t38 = ctx.esp;
    uint32_t t39 = mem.r32(t38);
    uint32_t t40 = static_cast<uint32_t>(t38 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    ctx.ebx = static_cast<uint32_t>(t39);
    // 0x0049fb44: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0049fb0e: {
    // 0x0049fb0e: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0049fb13: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x0049fb15: shl eax, cl
    uint32_t t41 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t42 = static_cast<uint32_t>(t41 & 0x0000001fu);
    uint32_t t43 = recomp_detail::shl<uint32_t>(ctx.eax, t42);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.eax, t42, t43);
    ctx.eax = static_cast<uint32_t>(t43);
    // 0x0049fb17: or dword ptr [esi + 0x24], eax
    uint32_t t44 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    uint32_t t45 = mem.r32(t44);
    uint32_t t46 = static_cast<uint32_t>(t45 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t46);
    mem.w32(t44, t46);
    // 0x0049fb1a: test ebp, eax
    uint32_t t47 = static_cast<uint32_t>(ctx.ebp & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t47);
    // 0x0049fb1c: jne 0x49fb33
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049fb33;
}
{
    // 0x0049fb1e: or dword ptr [esi + 0x28], eax
    uint32_t t48 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    uint32_t t49 = mem.r32(t48);
    uint32_t t50 = static_cast<uint32_t>(t49 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t50);
    mem.w32(t48, t50);
    // 0x0049fb21: jmp 0x49fb33
    goto bb_0049fb33;
}
}

// sub_0049fb50 | subsystem=Input | canonical | 15 blocks | 99 insns
void sub_0049fb50(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0049fb50: mov eax, dword ptr [edi]
    uint32_t t0 = mem.r32(ctx.edi);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x0049fb52: cmp eax, -1
    uint32_t t1 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t1);
    // 0x0049fb55: push esi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.esi);
    // 0x0049fb56: je 0x49fc2c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049fc2c;
    goto bb_0049fb5c;
}
bb_0049fc2c: {
    // 0x0049fc2c: mov edx, 2
    ctx.edx = static_cast<uint32_t>(0x00000002u);
    // 0x0049fc31: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x0049fc33: call 0x49fc60
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x0049fc38u);
    sub_0049fc60(ctx, mem);
    // 0x0049fc38: test eax, eax
    uint32_t t4 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    // 0x0049fc3a: je 0x49fc43
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049fc43;
    goto bb_0049fc3c;
}
bb_0049fb5c: {
    // 0x0049fb5c: imul eax, eax, 0x164
    uint64_t t5 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(0x00000164u)));
    uint32_t t6 = static_cast<uint32_t>(t5);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t5);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0049fb62: lea esi, [eax + 0x74da18]
    uint32_t t7 = static_cast<uint32_t>(ctx.eax + 0x0074da18u);
    ctx.esi = static_cast<uint32_t>(t7);
    // 0x0049fb68: mov eax, dword ptr [esi]
    uint32_t t8 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x0049fb6a: test eax, eax
    uint32_t t9 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    // 0x0049fb6c: je 0x49fbd6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049fbd6;
    goto bb_0049fb6e;
}
bb_0049fc43: {
    // 0x0049fc43: mov edx, 3
    ctx.edx = static_cast<uint32_t>(0x00000003u);
    // 0x0049fc48: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x0049fc4a: call 0x49fc60
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x0049fc4fu);
    sub_0049fc60(ctx, mem);
    // 0x0049fc4f: neg eax
    uint32_t t11 = static_cast<uint32_t>(0u - ctx.eax);
    recomp_detail::update_flags_neg<uint32_t>(ctx, ctx.eax, t11);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x0049fc51: sbb eax, eax
    uint32_t t12 = recomp_detail::get_flag(ctx, kFlagCF);
    uint32_t t13 = static_cast<uint32_t>(ctx.eax - ctx.eax);
    uint32_t t14 = static_cast<uint32_t>(t13 - t12);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.eax, t14, t12);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x0049fc53: and eax, 6
    uint32_t t15 = static_cast<uint32_t>(ctx.eax & 0x00000006u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t15);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x0049fc56: pop esi
    uint32_t t16 = ctx.esp;
    uint32_t t17 = mem.r32(t16);
    uint32_t t18 = static_cast<uint32_t>(t16 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    ctx.esi = static_cast<uint32_t>(t17);
    // 0x0049fc57: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0049fc3c: {
    // 0x0049fc3c: mov eax, 4
    ctx.eax = static_cast<uint32_t>(0x00000004u);
    // 0x0049fc41: pop esi
    uint32_t t19 = ctx.esp;
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t19 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    ctx.esi = static_cast<uint32_t>(t20);
    // 0x0049fc42: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0049fbd6: {
    // 0x0049fbd6: mov eax, dword ptr [esi]
    uint32_t t22 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t22);
    // 0x0049fbd8: test eax, eax
    uint32_t t23 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t23);
    // 0x0049fbda: je 0x49fc2c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049fc2c;
    goto bb_0049fbdc;
}
bb_0049fb6e: {
    // 0x0049fb6e: mov ecx, dword ptr [esi + 0x104]
    uint32_t t24 = static_cast<uint32_t>(ctx.esi + 0x00000104u);
    uint32_t t25 = mem.r32(t24);
    ctx.ecx = static_cast<uint32_t>(t25);
    // 0x0049fb74: push ecx
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, ctx.ecx);
    // 0x0049fb75: add eax, -1
    uint32_t t27 = static_cast<uint32_t>(ctx.eax + 0xffffffffu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0xffffffffu, t27);
    ctx.eax = static_cast<uint32_t>(t27);
    // 0x0049fb78: call 0x49fca0
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x0049fb7du);
    sub_0049fca0(ctx, mem);
    // 0x0049fb7d: cdq
    uint32_t t29 = recomp_detail::sar<uint32_t>(ctx.eax, 0x0000001fu);
    ctx.edx = static_cast<uint32_t>(t29);
    // 0x0049fb7e: xor eax, edx
    uint32_t t30 = static_cast<uint32_t>(ctx.eax ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t30);
    ctx.eax = static_cast<uint32_t>(t30);
    // 0x0049fb80: sub eax, edx
    uint32_t t31 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t31);
    ctx.eax = static_cast<uint32_t>(t31);
    // 0x0049fb82: xor edx, edx
    uint32_t t32 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t32);
    ctx.edx = static_cast<uint32_t>(t32);
    // 0x0049fb84: cmp eax, 0x3f
    uint32_t t33 = static_cast<uint32_t>(ctx.eax - 0x0000003fu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x0000003fu, t33);
    // 0x0049fb87: setg dl
    uint8_t t34 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::G) ? 1u : 0u);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t34));
    // 0x0049fb8a: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x0049fb8c: test eax, eax
    uint32_t t35 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t35);
    // 0x0049fb8e: je 0x49fbd6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049fbd6;
    goto bb_0049fb90;
}
bb_0049fbdc: {
    // 0x0049fbdc: mov ecx, dword ptr [esi + 0x108]
    uint32_t t36 = static_cast<uint32_t>(ctx.esi + 0x00000108u);
    uint32_t t37 = mem.r32(t36);
    ctx.ecx = static_cast<uint32_t>(t37);
    // 0x0049fbe2: push ecx
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, ctx.ecx);
    // 0x0049fbe3: add eax, -1
    uint32_t t39 = static_cast<uint32_t>(ctx.eax + 0xffffffffu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0xffffffffu, t39);
    ctx.eax = static_cast<uint32_t>(t39);
    // 0x0049fbe6: call 0x49fca0
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, 0x0049fbebu);
    sub_0049fca0(ctx, mem);
    // 0x0049fbeb: cdq
    uint32_t t41 = recomp_detail::sar<uint32_t>(ctx.eax, 0x0000001fu);
    ctx.edx = static_cast<uint32_t>(t41);
    // 0x0049fbec: xor eax, edx
    uint32_t t42 = static_cast<uint32_t>(ctx.eax ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t42);
    ctx.eax = static_cast<uint32_t>(t42);
    // 0x0049fbee: sub eax, edx
    uint32_t t43 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t43);
    ctx.eax = static_cast<uint32_t>(t43);
    // 0x0049fbf0: xor edx, edx
    uint32_t t44 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t44);
    ctx.edx = static_cast<uint32_t>(t44);
    // 0x0049fbf2: cmp eax, 0x3f
    uint32_t t45 = static_cast<uint32_t>(ctx.eax - 0x0000003fu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x0000003fu, t45);
    // 0x0049fbf5: setg dl
    uint8_t t46 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::G) ? 1u : 0u);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t46));
    // 0x0049fbf8: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x0049fbfa: test eax, eax
    uint32_t t47 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t47);
    // 0x0049fbfc: je 0x49fc2c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049fc2c;
    goto bb_0049fbfe;
}
bb_0049fb90: {
    // 0x0049fb90: mov eax, dword ptr [esi]
    uint32_t t48 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t48);
    // 0x0049fb92: test eax, eax
    uint32_t t49 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t49);
    // 0x0049fb94: je 0x49fbbf
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049fbbf;
    goto bb_0049fb96;
}
bb_0049fbfe: {
    // 0x0049fbfe: mov edx, 2
    ctx.edx = static_cast<uint32_t>(0x00000002u);
    // 0x0049fc03: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x0049fc05: call 0x49fc60
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, 0x0049fc0au);
    sub_0049fc60(ctx, mem);
    // 0x0049fc0a: test eax, eax
    uint32_t t51 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t51);
    // 0x0049fc0c: je 0x49fc15
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049fc15;
    goto bb_0049fc0e;
}
bb_0049fbbf: {
    // 0x0049fbbf: mov edx, 3
    ctx.edx = static_cast<uint32_t>(0x00000003u);
    // 0x0049fbc4: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x0049fbc6: call 0x49fc60
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, 0x0049fbcbu);
    sub_0049fc60(ctx, mem);
    // 0x0049fbcb: neg eax
    uint32_t t53 = static_cast<uint32_t>(0u - ctx.eax);
    recomp_detail::update_flags_neg<uint32_t>(ctx, ctx.eax, t53);
    ctx.eax = static_cast<uint32_t>(t53);
    // 0x0049fbcd: sbb eax, eax
    uint32_t t54 = recomp_detail::get_flag(ctx, kFlagCF);
    uint32_t t55 = static_cast<uint32_t>(ctx.eax - ctx.eax);
    uint32_t t56 = static_cast<uint32_t>(t55 - t54);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.eax, t56, t54);
    ctx.eax = static_cast<uint32_t>(t56);
    // 0x0049fbcf: neg eax
    uint32_t t57 = static_cast<uint32_t>(0u - ctx.eax);
    recomp_detail::update_flags_neg<uint32_t>(ctx, ctx.eax, t57);
    ctx.eax = static_cast<uint32_t>(t57);
    // 0x0049fbd1: add eax, 8
    uint32_t t58 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000008u, t58);
    ctx.eax = static_cast<uint32_t>(t58);
    // 0x0049fbd4: pop esi
    uint32_t t59 = ctx.esp;
    uint32_t t60 = mem.r32(t59);
    uint32_t t61 = static_cast<uint32_t>(t59 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    ctx.esi = static_cast<uint32_t>(t60);
    // 0x0049fbd5: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0049fb96: {
    // 0x0049fb96: mov ecx, dword ptr [esi + 0x10c]
    uint32_t t62 = static_cast<uint32_t>(ctx.esi + 0x0000010cu);
    uint32_t t63 = mem.r32(t62);
    ctx.ecx = static_cast<uint32_t>(t63);
    // 0x0049fb9c: push ecx
    uint32_t t64 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    mem.w32(t64, ctx.ecx);
    // 0x0049fb9d: add eax, -1
    uint32_t t65 = static_cast<uint32_t>(ctx.eax + 0xffffffffu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0xffffffffu, t65);
    ctx.eax = static_cast<uint32_t>(t65);
    // 0x0049fba0: call 0x49fca0
    uint32_t t66 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    mem.w32(t66, 0x0049fba5u);
    sub_0049fca0(ctx, mem);
    // 0x0049fba5: cdq
    uint32_t t67 = recomp_detail::sar<uint32_t>(ctx.eax, 0x0000001fu);
    ctx.edx = static_cast<uint32_t>(t67);
    // 0x0049fba6: xor eax, edx
    uint32_t t68 = static_cast<uint32_t>(ctx.eax ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t68);
    ctx.eax = static_cast<uint32_t>(t68);
    // 0x0049fba8: sub eax, edx
    uint32_t t69 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t69);
    ctx.eax = static_cast<uint32_t>(t69);
    // 0x0049fbaa: xor edx, edx
    uint32_t t70 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t70);
    ctx.edx = static_cast<uint32_t>(t70);
    // 0x0049fbac: cmp eax, 0x3f
    uint32_t t71 = static_cast<uint32_t>(ctx.eax - 0x0000003fu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x0000003fu, t71);
    // 0x0049fbaf: setg dl
    uint8_t t72 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::G) ? 1u : 0u);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t72));
    // 0x0049fbb2: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x0049fbb4: test eax, eax
    uint32_t t73 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t73);
    // 0x0049fbb6: je 0x49fbbf
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049fbbf;
    goto bb_0049fbb8;
}
bb_0049fc15: {
    // 0x0049fc15: mov edx, 3
    ctx.edx = static_cast<uint32_t>(0x00000003u);
    // 0x0049fc1a: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x0049fc1c: call 0x49fc60
    uint32_t t74 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    mem.w32(t74, 0x0049fc21u);
    sub_0049fc60(ctx, mem);
    // 0x0049fc21: neg eax
    uint32_t t75 = static_cast<uint32_t>(0u - ctx.eax);
    recomp_detail::update_flags_neg<uint32_t>(ctx, ctx.eax, t75);
    ctx.eax = static_cast<uint32_t>(t75);
    // 0x0049fc23: sbb eax, eax
    uint32_t t76 = recomp_detail::get_flag(ctx, kFlagCF);
    uint32_t t77 = static_cast<uint32_t>(ctx.eax - ctx.eax);
    uint32_t t78 = static_cast<uint32_t>(t77 - t76);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.eax, t78, t76);
    ctx.eax = static_cast<uint32_t>(t78);
    // 0x0049fc25: neg eax
    uint32_t t79 = static_cast<uint32_t>(0u - ctx.eax);
    recomp_detail::update_flags_neg<uint32_t>(ctx, ctx.eax, t79);
    ctx.eax = static_cast<uint32_t>(t79);
    // 0x0049fc27: add eax, 2
    uint32_t t80 = static_cast<uint32_t>(ctx.eax + 0x00000002u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000002u, t80);
    ctx.eax = static_cast<uint32_t>(t80);
    // 0x0049fc2a: pop esi
    uint32_t t81 = ctx.esp;
    uint32_t t82 = mem.r32(t81);
    uint32_t t83 = static_cast<uint32_t>(t81 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t83);
    ctx.esi = static_cast<uint32_t>(t82);
    // 0x0049fc2b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0049fc0e: {
    // 0x0049fc0e: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0049fc13: pop esi
    uint32_t t84 = ctx.esp;
    uint32_t t85 = mem.r32(t84);
    uint32_t t86 = static_cast<uint32_t>(t84 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t86);
    ctx.esi = static_cast<uint32_t>(t85);
    // 0x0049fc14: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0049fbb8: {
    // 0x0049fbb8: mov eax, 7
    ctx.eax = static_cast<uint32_t>(0x00000007u);
    // 0x0049fbbd: pop esi
    uint32_t t87 = ctx.esp;
    uint32_t t88 = mem.r32(t87);
    uint32_t t89 = static_cast<uint32_t>(t87 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t89);
    ctx.esi = static_cast<uint32_t>(t88);
    // 0x0049fbbe: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0049fc60 | subsystem=Input | canonical | 4 blocks | 22 insns
void sub_0049fc60(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0049fc60: mov eax, dword ptr [eax]
    uint32_t t0 = mem.r32(ctx.eax);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x0049fc62: cmp eax, -1
    uint32_t t1 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t1);
    // 0x0049fc65: jne 0x49fc6a
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049fc6a;
    goto bb_0049fc67;
}
bb_0049fc6a: {
    // 0x0049fc6a: imul eax, eax, 0x164
    uint64_t t2 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(0x00000164u)));
    uint32_t t3 = static_cast<uint32_t>(t2);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0049fc70: add eax, 0x74da18
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x0074da18u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x0074da18u, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0049fc75: mov ecx, dword ptr [eax]
    uint32_t t5 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t5);
    // 0x0049fc77: test ecx, ecx
    uint32_t t6 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t6);
    // 0x0049fc79: je 0x49fc67
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049fc67;
    goto bb_0049fc7b;
}
bb_0049fc67: {
    // 0x0049fc67: xor eax, eax
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0049fc69: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0049fc7b: {
    // 0x0049fc7b: mov eax, dword ptr [eax + edx*4 + 0x104]
    uint32_t t8 = recomp_detail::shl<uint32_t>(ctx.edx, 0x00000002u);
    uint32_t t9 = static_cast<uint32_t>(ctx.eax + t8);
    uint32_t t10 = static_cast<uint32_t>(t9 + 0x00000104u);
    uint32_t t11 = mem.r32(t10);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x0049fc82: push eax
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.eax);
    // 0x0049fc83: lea eax, [ecx - 1]
    uint32_t t13 = static_cast<uint32_t>(ctx.ecx + 0xffffffffu);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0049fc86: call 0x49fca0
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x0049fc8bu);
    sub_0049fca0(ctx, mem);
    // 0x0049fc8b: cdq
    uint32_t t15 = recomp_detail::sar<uint32_t>(ctx.eax, 0x0000001fu);
    ctx.edx = static_cast<uint32_t>(t15);
    // 0x0049fc8c: xor eax, edx
    uint32_t t16 = static_cast<uint32_t>(ctx.eax ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0049fc8e: sub eax, edx
    uint32_t t17 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t17);
    ctx.eax = static_cast<uint32_t>(t17);
    // 0x0049fc90: xor ecx, ecx
    uint32_t t18 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    ctx.ecx = static_cast<uint32_t>(t18);
    // 0x0049fc92: cmp eax, 0x3f
    uint32_t t19 = static_cast<uint32_t>(ctx.eax - 0x0000003fu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x0000003fu, t19);
    // 0x0049fc95: setg cl
    uint8_t t20 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::G) ? 1u : 0u);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t20));
    // 0x0049fc98: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x0049fc9a: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0049fca0 | subsystem=Input | canonical | 43 blocks | 130 insns
void sub_0049fca0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0049fca0: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x0049fca1: xor esi, esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esi = static_cast<uint32_t>(t1);
    // 0x0049fca3: cmp eax, 0x10
    uint32_t t2 = static_cast<uint32_t>(ctx.eax - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000010u, t2);
    // 0x0049fca6: jae 0x49fcbc
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0049fcbc;
    goto bb_0049fca8;
}
bb_0049fcbc: {
    // 0x0049fcbc: xor eax, eax
    uint32_t t3 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t3);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0049fcbe: pop esi
    uint32_t t4 = ctx.esp;
    uint32_t t5 = mem.r32(t4);
    uint32_t t6 = static_cast<uint32_t>(t4 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    ctx.esi = static_cast<uint32_t>(t5);
    // 0x0049fcbf: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0049fca8: {
    // 0x0049fca8: lea ecx, [eax*8]
    uint32_t t7 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000003u);
    ctx.ecx = static_cast<uint32_t>(t7);
    // 0x0049fcaf: sub ecx, eax
    uint32_t t8 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t8);
    ctx.ecx = static_cast<uint32_t>(t8);
    // 0x0049fcb1: lea eax, [ecx*8 + 0x5545f8]
    uint32_t t9 = recomp_detail::shl<uint32_t>(ctx.ecx, 0x00000003u);
    uint32_t t10 = static_cast<uint32_t>(t9 + 0x005545f8u);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0049fcb8: test eax, eax
    uint32_t t11 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    // 0x0049fcba: jne 0x49fcc2
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049fcc2;
    goto bb_0049fcbc;
}
bb_0049fcc2: {
    // 0x0049fcc2: mov ecx, dword ptr [esp + 8]
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t13 = mem.r32(t12);
    ctx.ecx = static_cast<uint32_t>(t13);
    // 0x0049fcc6: add ecx, -1
    uint32_t t14 = static_cast<uint32_t>(ctx.ecx + 0xffffffffu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0xffffffffu, t14);
    ctx.ecx = static_cast<uint32_t>(t14);
    // 0x0049fcc9: cmp ecx, 0x21
    uint32_t t15 = static_cast<uint32_t>(ctx.ecx - 0x00000021u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000021u, t15);
    // 0x0049fccc: ja 0x49fe07
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_0049fe07;
    goto bb_0049fcd2;
}
bb_0049fe07: {
    // 0x0049fe07: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0049fe09: pop esi
    uint32_t t16 = ctx.esp;
    uint32_t t17 = mem.r32(t16);
    uint32_t t18 = static_cast<uint32_t>(t16 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    ctx.esi = static_cast<uint32_t>(t17);
    // 0x0049fe0a: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0049fcd2: {
    // 0x0049fcd2: movzx edx, byte ptr [ecx + 0x49fe5c]
    uint32_t t19 = static_cast<uint32_t>(ctx.ecx + 0x0049fe5cu);
    uint8_t t20 = mem.r8(t19);
    uint32_t t21 = static_cast<uint32_t>(static_cast<uint8_t>(t20));
    ctx.edx = static_cast<uint32_t>(t21);
    // 0x0049fcd9: jmp dword ptr [edx*4 + 0x49fe10]
    switch (ctx.edx) {
        case 0u: goto bb_0049fce0;
        case 1u: goto bb_0049fcfb;
        case 2u: goto bb_0049fd1a;
        case 3u: goto bb_0049fd39;
        case 4u: goto bb_0049fd5f;
        case 5u: goto bb_0049fd85;
        case 6u: goto bb_0049fd91;
        case 7u: goto bb_0049fd95;
        case 8u: goto bb_0049fda2;
        case 9u: goto bb_0049fda7;
        case 10u: goto bb_0049fdb4;
        case 11u: goto bb_0049fdb9;
        case 12u: goto bb_0049fdc6;
        case 13u: goto bb_0049fdcb;
        case 14u: goto bb_0049fdd8;
        case 15u: goto bb_0049fddd;
        case 16u: goto bb_0049fdea;
        case 17u: goto bb_0049fdef;
        case 18u: goto bb_0049fdfc;
        default: recomp_detail::trap_halt(ctx, 0x0049fe10u, "switch_oob"); return;
    }
}
bb_0049fce0: {
    // 0x0049fce0: mov edx, 1
    ctx.edx = static_cast<uint32_t>(0x00000001u);
    // 0x0049fce5: shl edx, cl
    uint32_t t22 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t23 = static_cast<uint32_t>(t22 & 0x0000001fu);
    uint32_t t24 = recomp_detail::shl<uint32_t>(ctx.edx, t23);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.edx, t23, t24);
    ctx.edx = static_cast<uint32_t>(t24);
    // 0x0049fce7: test dword ptr [eax + 0x24], edx
    uint32_t t25 = static_cast<uint32_t>(ctx.eax + 0x00000024u);
    uint32_t t26 = mem.r32(t25);
    uint32_t t27 = static_cast<uint32_t>(t26 & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t27);
    // 0x0049fcea: je 0x49fe07
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049fe07;
    goto bb_0049fcf0;
}
bb_0049fcfb: {
    // 0x0049fcfb: mov ecx, dword ptr [eax + 0x18]
    uint32_t t28 = static_cast<uint32_t>(ctx.eax + 0x00000018u);
    uint32_t t29 = mem.r32(t28);
    ctx.ecx = static_cast<uint32_t>(t29);
    // 0x0049fcfe: call 0x4106a0
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x0049fd03u);
    sub_004106a0(ctx, mem);
    // 0x0049fd03: add eax, -7
    uint32_t t31 = static_cast<uint32_t>(ctx.eax + 0xfffffff9u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0xfffffff9u, t31);
    ctx.eax = static_cast<uint32_t>(t31);
    // 0x0049fd06: cmp eax, 2
    uint32_t t32 = static_cast<uint32_t>(ctx.eax - 0x00000002u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000002u, t32);
    // 0x0049fd09: ja 0x49fe07
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_0049fe07;
    goto bb_0049fd0f;
}
bb_0049fd1a: {
    // 0x0049fd1a: mov ecx, dword ptr [eax + 0x18]
    uint32_t t33 = static_cast<uint32_t>(ctx.eax + 0x00000018u);
    uint32_t t34 = mem.r32(t33);
    ctx.ecx = static_cast<uint32_t>(t34);
    // 0x0049fd1d: call 0x4106a0
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, 0x0049fd22u);
    sub_004106a0(ctx, mem);
    // 0x0049fd22: add eax, -1
    uint32_t t36 = static_cast<uint32_t>(ctx.eax + 0xffffffffu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0xffffffffu, t36);
    ctx.eax = static_cast<uint32_t>(t36);
    // 0x0049fd25: cmp eax, 2
    uint32_t t37 = static_cast<uint32_t>(ctx.eax - 0x00000002u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000002u, t37);
    // 0x0049fd28: ja 0x49fe07
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_0049fe07;
    goto bb_0049fd2e;
}
bb_0049fd39: {
    // 0x0049fd39: mov ecx, dword ptr [eax + 0x18]
    uint32_t t38 = static_cast<uint32_t>(ctx.eax + 0x00000018u);
    uint32_t t39 = mem.r32(t38);
    ctx.ecx = static_cast<uint32_t>(t39);
    // 0x0049fd3c: call 0x4106a0
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, 0x0049fd41u);
    sub_004106a0(ctx, mem);
    // 0x0049fd41: sub eax, 1
    uint32_t t41 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t41);
    ctx.eax = static_cast<uint32_t>(t41);
    // 0x0049fd44: je 0x49fd54
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049fd54;
    goto bb_0049fd46;
}
bb_0049fd5f: {
    // 0x0049fd5f: mov ecx, dword ptr [eax + 0x18]
    uint32_t t42 = static_cast<uint32_t>(ctx.eax + 0x00000018u);
    uint32_t t43 = mem.r32(t42);
    ctx.ecx = static_cast<uint32_t>(t43);
    // 0x0049fd62: call 0x4106a0
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, 0x0049fd67u);
    sub_004106a0(ctx, mem);
    // 0x0049fd67: cmp eax, 3
    uint32_t t45 = static_cast<uint32_t>(ctx.eax - 0x00000003u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000003u, t45);
    // 0x0049fd6a: je 0x49fd7a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049fd7a;
    goto bb_0049fd6c;
}
bb_0049fd85: {
    // 0x0049fd85: mov eax, dword ptr [eax]
    uint32_t t46 = mem.r32(ctx.eax);
    ctx.eax = static_cast<uint32_t>(t46);
    // 0x0049fd87: test eax, eax
    uint32_t t47 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t47);
    // 0x0049fd89: jle 0x49fe07
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0049fe07;
    goto bb_0049fd8b;
}
bb_0049fd91: {
    // 0x0049fd91: mov eax, dword ptr [eax]
    uint32_t t48 = mem.r32(ctx.eax);
    ctx.eax = static_cast<uint32_t>(t48);
    // 0x0049fd93: jmp 0x49fdff
    goto bb_0049fdff;
}
bb_0049fd95: {
    // 0x0049fd95: mov eax, dword ptr [eax + 4]
    uint32_t t49 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t50 = mem.r32(t49);
    ctx.eax = static_cast<uint32_t>(t50);
    // 0x0049fd98: test eax, eax
    uint32_t t51 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t51);
    // 0x0049fd9a: jle 0x49fe07
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0049fe07;
    goto bb_0049fd9c;
}
bb_0049fda2: {
    // 0x0049fda2: mov eax, dword ptr [eax + 4]
    uint32_t t52 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t53 = mem.r32(t52);
    ctx.eax = static_cast<uint32_t>(t53);
    // 0x0049fda5: jmp 0x49fdff
    goto bb_0049fdff;
}
bb_0049fda7: {
    // 0x0049fda7: mov eax, dword ptr [eax + 8]
    uint32_t t54 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    uint32_t t55 = mem.r32(t54);
    ctx.eax = static_cast<uint32_t>(t55);
    // 0x0049fdaa: test eax, eax
    uint32_t t56 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t56);
    // 0x0049fdac: jle 0x49fe07
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0049fe07;
    goto bb_0049fdae;
}
bb_0049fdb4: {
    // 0x0049fdb4: mov eax, dword ptr [eax + 8]
    uint32_t t57 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    uint32_t t58 = mem.r32(t57);
    ctx.eax = static_cast<uint32_t>(t58);
    // 0x0049fdb7: jmp 0x49fdff
    goto bb_0049fdff;
}
bb_0049fdb9: {
    // 0x0049fdb9: mov eax, dword ptr [eax + 0xc]
    uint32_t t59 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    uint32_t t60 = mem.r32(t59);
    ctx.eax = static_cast<uint32_t>(t60);
    // 0x0049fdbc: test eax, eax
    uint32_t t61 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t61);
    // 0x0049fdbe: jle 0x49fe07
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0049fe07;
    goto bb_0049fdc0;
}
bb_0049fdc6: {
    // 0x0049fdc6: mov eax, dword ptr [eax + 0xc]
    uint32_t t62 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    uint32_t t63 = mem.r32(t62);
    ctx.eax = static_cast<uint32_t>(t63);
    // 0x0049fdc9: jmp 0x49fdff
    goto bb_0049fdff;
}
bb_0049fdcb: {
    // 0x0049fdcb: mov eax, dword ptr [eax + 0x10]
    uint32_t t64 = static_cast<uint32_t>(ctx.eax + 0x00000010u);
    uint32_t t65 = mem.r32(t64);
    ctx.eax = static_cast<uint32_t>(t65);
    // 0x0049fdce: test eax, eax
    uint32_t t66 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t66);
    // 0x0049fdd0: jle 0x49fe07
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0049fe07;
    goto bb_0049fdd2;
}
bb_0049fdd8: {
    // 0x0049fdd8: mov eax, dword ptr [eax + 0x10]
    uint32_t t67 = static_cast<uint32_t>(ctx.eax + 0x00000010u);
    uint32_t t68 = mem.r32(t67);
    ctx.eax = static_cast<uint32_t>(t68);
    // 0x0049fddb: jmp 0x49fdff
    goto bb_0049fdff;
}
bb_0049fddd: {
    // 0x0049fddd: mov eax, dword ptr [eax + 0x14]
    uint32_t t69 = static_cast<uint32_t>(ctx.eax + 0x00000014u);
    uint32_t t70 = mem.r32(t69);
    ctx.eax = static_cast<uint32_t>(t70);
    // 0x0049fde0: test eax, eax
    uint32_t t71 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t71);
    // 0x0049fde2: jle 0x49fe07
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0049fe07;
    goto bb_0049fde4;
}
bb_0049fdea: {
    // 0x0049fdea: mov eax, dword ptr [eax + 0x14]
    uint32_t t72 = static_cast<uint32_t>(ctx.eax + 0x00000014u);
    uint32_t t73 = mem.r32(t72);
    ctx.eax = static_cast<uint32_t>(t73);
    // 0x0049fded: jmp 0x49fdff
    goto bb_0049fdff;
}
bb_0049fdef: {
    // 0x0049fdef: mov eax, dword ptr [eax + 0x1c]
    uint32_t t74 = static_cast<uint32_t>(ctx.eax + 0x0000001cu);
    uint32_t t75 = mem.r32(t74);
    ctx.eax = static_cast<uint32_t>(t75);
    // 0x0049fdf2: test eax, eax
    uint32_t t76 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t76);
    // 0x0049fdf4: jle 0x49fe07
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0049fe07;
    goto bb_0049fdf6;
}
bb_0049fdfc: {
    // 0x0049fdfc: mov eax, dword ptr [eax + 0x1c]
    uint32_t t77 = static_cast<uint32_t>(ctx.eax + 0x0000001cu);
    uint32_t t78 = mem.r32(t77);
    ctx.eax = static_cast<uint32_t>(t78);
    goto bb_0049fdff;
}
bb_0049fcf0: {
    // 0x0049fcf0: mov esi, 0x7f
    ctx.esi = static_cast<uint32_t>(0x0000007fu);
    // 0x0049fcf5: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0049fcf7: pop esi
    uint32_t t79 = ctx.esp;
    uint32_t t80 = mem.r32(t79);
    uint32_t t81 = static_cast<uint32_t>(t79 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    ctx.esi = static_cast<uint32_t>(t80);
    // 0x0049fcf8: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0049fd0f: {
    // 0x0049fd0f: mov esi, 0x7f
    ctx.esi = static_cast<uint32_t>(0x0000007fu);
    // 0x0049fd14: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0049fd16: pop esi
    uint32_t t82 = ctx.esp;
    uint32_t t83 = mem.r32(t82);
    uint32_t t84 = static_cast<uint32_t>(t82 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    ctx.esi = static_cast<uint32_t>(t83);
    // 0x0049fd17: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0049fd2e: {
    // 0x0049fd2e: mov esi, 0x7f
    ctx.esi = static_cast<uint32_t>(0x0000007fu);
    // 0x0049fd33: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0049fd35: pop esi
    uint32_t t85 = ctx.esp;
    uint32_t t86 = mem.r32(t85);
    uint32_t t87 = static_cast<uint32_t>(t85 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t87);
    ctx.esi = static_cast<uint32_t>(t86);
    // 0x0049fd36: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0049fd54: {
    // 0x0049fd54: mov esi, 0x7f
    ctx.esi = static_cast<uint32_t>(0x0000007fu);
    // 0x0049fd59: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0049fd5b: pop esi
    uint32_t t88 = ctx.esp;
    uint32_t t89 = mem.r32(t88);
    uint32_t t90 = static_cast<uint32_t>(t88 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    ctx.esi = static_cast<uint32_t>(t89);
    // 0x0049fd5c: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0049fd46: {
    // 0x0049fd46: sub eax, 3
    uint32_t t91 = static_cast<uint32_t>(ctx.eax - 0x00000003u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000003u, t91);
    ctx.eax = static_cast<uint32_t>(t91);
    // 0x0049fd49: je 0x49fd54
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049fd54;
    goto bb_0049fd4b;
}
bb_0049fd7a: {
    // 0x0049fd7a: mov esi, 0x7f
    ctx.esi = static_cast<uint32_t>(0x0000007fu);
    // 0x0049fd7f: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0049fd81: pop esi
    uint32_t t92 = ctx.esp;
    uint32_t t93 = mem.r32(t92);
    uint32_t t94 = static_cast<uint32_t>(t92 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t94);
    ctx.esi = static_cast<uint32_t>(t93);
    // 0x0049fd82: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0049fd6c: {
    // 0x0049fd6c: cmp eax, 6
    uint32_t t95 = static_cast<uint32_t>(ctx.eax - 0x00000006u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000006u, t95);
    // 0x0049fd6f: je 0x49fd7a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049fd7a;
    goto bb_0049fd71;
}
bb_0049fd8b: {
    // 0x0049fd8b: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0049fd8d: pop esi
    uint32_t t96 = ctx.esp;
    uint32_t t97 = mem.r32(t96);
    uint32_t t98 = static_cast<uint32_t>(t96 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t98);
    ctx.esi = static_cast<uint32_t>(t97);
    // 0x0049fd8e: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0049fdff: {
    // 0x0049fdff: test eax, eax
    uint32_t t99 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t99);
    // 0x0049fe01: jge 0x49fe07
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0049fe07;
    goto bb_0049fe03;
}
bb_0049fd9c: {
    // 0x0049fd9c: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0049fd9e: pop esi
    uint32_t t100 = ctx.esp;
    uint32_t t101 = mem.r32(t100);
    uint32_t t102 = static_cast<uint32_t>(t100 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    ctx.esi = static_cast<uint32_t>(t101);
    // 0x0049fd9f: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0049fdae: {
    // 0x0049fdae: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0049fdb0: pop esi
    uint32_t t103 = ctx.esp;
    uint32_t t104 = mem.r32(t103);
    uint32_t t105 = static_cast<uint32_t>(t103 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t105);
    ctx.esi = static_cast<uint32_t>(t104);
    // 0x0049fdb1: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0049fdc0: {
    // 0x0049fdc0: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0049fdc2: pop esi
    uint32_t t106 = ctx.esp;
    uint32_t t107 = mem.r32(t106);
    uint32_t t108 = static_cast<uint32_t>(t106 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t108);
    ctx.esi = static_cast<uint32_t>(t107);
    // 0x0049fdc3: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0049fdd2: {
    // 0x0049fdd2: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0049fdd4: pop esi
    uint32_t t109 = ctx.esp;
    uint32_t t110 = mem.r32(t109);
    uint32_t t111 = static_cast<uint32_t>(t109 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t111);
    ctx.esi = static_cast<uint32_t>(t110);
    // 0x0049fdd5: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0049fde4: {
    // 0x0049fde4: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0049fde6: pop esi
    uint32_t t112 = ctx.esp;
    uint32_t t113 = mem.r32(t112);
    uint32_t t114 = static_cast<uint32_t>(t112 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t114);
    ctx.esi = static_cast<uint32_t>(t113);
    // 0x0049fde7: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0049fdf6: {
    // 0x0049fdf6: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0049fdf8: pop esi
    uint32_t t115 = ctx.esp;
    uint32_t t116 = mem.r32(t115);
    uint32_t t117 = static_cast<uint32_t>(t115 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t117);
    ctx.esi = static_cast<uint32_t>(t116);
    // 0x0049fdf9: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0049fd4b: {
    // 0x0049fd4b: sub eax, 3
    uint32_t t118 = static_cast<uint32_t>(ctx.eax - 0x00000003u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000003u, t118);
    ctx.eax = static_cast<uint32_t>(t118);
    // 0x0049fd4e: jne 0x49fe07
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049fe07;
    goto bb_0049fd54;
}
bb_0049fd71: {
    // 0x0049fd71: cmp eax, 9
    uint32_t t119 = static_cast<uint32_t>(ctx.eax - 0x00000009u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000009u, t119);
    // 0x0049fd74: jne 0x49fe07
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0049fe07;
    goto bb_0049fd7a;
}
bb_0049fe03: {
    // 0x0049fe03: neg eax
    uint32_t t120 = static_cast<uint32_t>(0u - ctx.eax);
    recomp_detail::update_flags_neg<uint32_t>(ctx, ctx.eax, t120);
    ctx.eax = static_cast<uint32_t>(t120);
    // 0x0049fe05: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    goto bb_0049fe07;
}
}

// sub_0049fe80 | subsystem=Input | canonical | 11 blocks | 41 insns
void sub_0049fe80(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0049fe80: mov edx, dword ptr [ecx + eax*8 + 0x14]
    uint32_t t0 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000003u);
    uint32_t t1 = static_cast<uint32_t>(ctx.ecx + t0);
    uint32_t t2 = static_cast<uint32_t>(t1 + 0x00000014u);
    uint32_t t3 = mem.r32(t2);
    ctx.edx = static_cast<uint32_t>(t3);
    // 0x0049fe84: cmp edx, 0x3f
    uint32_t t4 = static_cast<uint32_t>(ctx.edx - 0x0000003fu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x0000003fu, t4);
    // 0x0049fe87: mov eax, dword ptr [ecx + eax*8 + 0x18]
    uint32_t t5 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000003u);
    uint32_t t6 = static_cast<uint32_t>(ctx.ecx + t5);
    uint32_t t7 = static_cast<uint32_t>(t6 + 0x00000018u);
    uint32_t t8 = mem.r32(t7);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x0049fe8b: jle 0x49feac
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0049feac;
    goto bb_0049fe8d;
}
bb_0049feac: {
    // 0x0049feac: cmp edx, -0x3f
    uint32_t t9 = static_cast<uint32_t>(ctx.edx - 0xffffffc1u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0xffffffc1u, t9);
    // 0x0049feaf: jge 0x49fed0
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0049fed0;
    goto bb_0049feb1;
}
bb_0049fe8d: {
    // 0x0049fe8d: cmp eax, 0x3f
    uint32_t t10 = static_cast<uint32_t>(ctx.eax - 0x0000003fu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x0000003fu, t10);
    // 0x0049fe90: jle 0x49fe98
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0049fe98;
    goto bb_0049fe92;
}
bb_0049fed0: {
    // 0x0049fed0: cmp eax, 0x3f
    uint32_t t11 = static_cast<uint32_t>(ctx.eax - 0x0000003fu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x0000003fu, t11);
    // 0x0049fed3: jle 0x49fedb
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0049fedb;
    goto bb_0049fed5;
}
bb_0049feb1: {
    // 0x0049feb1: cmp eax, 0x3f
    uint32_t t12 = static_cast<uint32_t>(ctx.eax - 0x0000003fu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x0000003fu, t12);
    // 0x0049feb4: jle 0x49febc
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0049febc;
    goto bb_0049feb6;
}
bb_0049fe98: {
    // 0x0049fe98: xor ecx, ecx
    uint32_t t13 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t13);
    ctx.ecx = static_cast<uint32_t>(t13);
    // 0x0049fe9a: cmp eax, -0x3f
    uint32_t t14 = static_cast<uint32_t>(ctx.eax - 0xffffffc1u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffc1u, t14);
    // 0x0049fe9d: setge cl
    uint8_t t15 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::GE) ? 1u : 0u);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t15));
    // 0x0049fea0: sub ecx, 1
    uint32_t t16 = static_cast<uint32_t>(ctx.ecx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000001u, t16);
    ctx.ecx = static_cast<uint32_t>(t16);
    // 0x0049fea3: and ecx, 3
    uint32_t t17 = static_cast<uint32_t>(ctx.ecx & 0x00000003u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t17);
    ctx.ecx = static_cast<uint32_t>(t17);
    // 0x0049fea6: add ecx, 6
    uint32_t t18 = static_cast<uint32_t>(ctx.ecx + 0x00000006u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000006u, t18);
    ctx.ecx = static_cast<uint32_t>(t18);
    // 0x0049fea9: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x0049feab: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0049fe92: {
    // 0x0049fe92: mov eax, 3
    ctx.eax = static_cast<uint32_t>(0x00000003u);
    // 0x0049fe97: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0049fedb: {
    // 0x0049fedb: xor ecx, ecx
    uint32_t t19 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t19);
    ctx.ecx = static_cast<uint32_t>(t19);
    // 0x0049fedd: cmp eax, -0x3f
    uint32_t t20 = static_cast<uint32_t>(ctx.eax - 0xffffffc1u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffc1u, t20);
    // 0x0049fee0: setge cl
    uint8_t t21 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::GE) ? 1u : 0u);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t21));
    // 0x0049fee3: sub ecx, 1
    uint32_t t22 = static_cast<uint32_t>(ctx.ecx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000001u, t22);
    ctx.ecx = static_cast<uint32_t>(t22);
    // 0x0049fee6: and ecx, 8
    uint32_t t23 = static_cast<uint32_t>(ctx.ecx & 0x00000008u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t23);
    ctx.ecx = static_cast<uint32_t>(t23);
    // 0x0049fee9: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x0049feeb: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0049fed5: {
    // 0x0049fed5: mov eax, 2
    ctx.eax = static_cast<uint32_t>(0x00000002u);
    // 0x0049feda: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0049febc: {
    // 0x0049febc: xor edx, edx
    uint32_t t24 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t24);
    ctx.edx = static_cast<uint32_t>(t24);
    // 0x0049febe: cmp eax, -0x3f
    uint32_t t25 = static_cast<uint32_t>(ctx.eax - 0xffffffc1u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffc1u, t25);
    // 0x0049fec1: setge dl
    uint8_t t26 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::GE) ? 1u : 0u);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t26));
    // 0x0049fec4: sub edx, 1
    uint32_t t27 = static_cast<uint32_t>(ctx.edx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000001u, t27);
    ctx.edx = static_cast<uint32_t>(t27);
    // 0x0049fec7: and edx, 3
    uint32_t t28 = static_cast<uint32_t>(ctx.edx & 0x00000003u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t28);
    ctx.edx = static_cast<uint32_t>(t28);
    // 0x0049feca: add edx, 4
    uint32_t t29 = static_cast<uint32_t>(ctx.edx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000004u, t29);
    ctx.edx = static_cast<uint32_t>(t29);
    // 0x0049fecd: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x0049fecf: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0049feb6: {
    // 0x0049feb6: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0049febb: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0049fef0 | subsystem=Input | canonical | 1 blocks | 27 insns
void sub_0049fef0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0049fef0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0049fef2: push 0x513648
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00513648u);
    // 0x0049fef7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0049fefd: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0049fefe: push ecx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ecx);
    // 0x0049feff: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0049ff04: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0049ff06: push eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.eax);
    // 0x0049ff07: lea eax, [esp + 8]
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x0049ff0b: mov dword ptr fs:[0], eax
    uint32_t t10 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t10, ctx.eax);
    // 0x0049ff11: mov dword ptr [esp + 4], 0x7715a8
    uint32_t t11 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    mem.w32(t11, 0x007715a8u);
    // 0x0049ff19: push 0x4d5ef0
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x004d5ef0u);
    // 0x0049ff1e: push 0x49f9b0
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x0049f9b0u);
    // 0x0049ff23: push 4
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x00000004u);
    // 0x0049ff25: push 0x30
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x00000030u);
    // 0x0049ff27: mov dword ptr [esp + 0x20], 0
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t16, 0x00000000u);
    // 0x0049ff2f: push 0x7715ac
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x007715acu);
    // 0x0049ff34: mov dword ptr [0x7715a8], 0x53a018
    mem.w32(0x007715a8u, 0x0053a018u);
    // 0x0049ff3e: call 0x4e1c97
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x0049ff43u);
    hle_crt_004e1c97(ctx, mem);
    // 0x0049ff43: mov eax, 0x7715a8
    ctx.eax = static_cast<uint32_t>(0x007715a8u);
    // 0x0049ff48: call 0x49fff0
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x0049ff4du);
    sub_0049fff0(ctx, mem);
    // 0x0049ff4d: mov eax, 0x7715a8
    ctx.eax = static_cast<uint32_t>(0x007715a8u);
    // 0x0049ff52: mov ecx, dword ptr [esp + 8]
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t21 = mem.r32(t20);
    ctx.ecx = static_cast<uint32_t>(t21);
    // 0x0049ff56: mov dword ptr fs:[0], ecx
    uint32_t t22 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t22, ctx.ecx);
    // 0x0049ff5d: pop ecx
    uint32_t t23 = ctx.esp;
    uint32_t t24 = mem.r32(t23);
    uint32_t t25 = static_cast<uint32_t>(t23 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    ctx.ecx = static_cast<uint32_t>(t24);
    // 0x0049ff5e: add esp, 0x10
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t26);
    ctx.esp = static_cast<uint32_t>(t26);
    // 0x0049ff61: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0049ff70 | subsystem=Input | canonical | 3 blocks | 11 insns
void sub_0049ff70(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0049ff70: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x0049ff71: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x0049ff73: call 0x49ff90
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0049ff78u);
    sub_0049ff90(ctx, mem);
    // 0x0049ff78: test byte ptr [esp + 8], 1
    uint32_t t2 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint8_t t3 = mem.r8(t2);
    uint8_t t4 = static_cast<uint8_t>(static_cast<uint32_t>(t3) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t4);
    // 0x0049ff7d: je 0x49ff88
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0049ff88;
    goto bb_0049ff7f;
}
bb_0049ff88: {
    // 0x0049ff88: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0049ff8a: pop esi
    uint32_t t5 = ctx.esp;
    uint32_t t6 = mem.r32(t5);
    uint32_t t7 = static_cast<uint32_t>(t5 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x0049ff8b: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0049ff7f: {
    // 0x0049ff7f: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x0049ff80: call 0x4e02f3
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x0049ff85u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0049ff85: add esp, 4
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t10);
    ctx.esp = static_cast<uint32_t>(t10);
    goto bb_0049ff88;
}
}

// sub_0049ff90 | subsystem=Input | canonical | 1 blocks | 28 insns
void sub_0049ff90(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0049ff90: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0049ff92: push 0x5134c8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005134c8u);
    // 0x0049ff97: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0049ff9d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0049ff9e: push ecx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ecx);
    // 0x0049ff9f: push esi
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.esi);
    // 0x0049ffa0: mov eax, dword ptr [0x54b458]
    uint32_t t7 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0049ffa5: xor eax, esp
    uint32_t t8 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t8);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x0049ffa7: push eax
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.eax);
    // 0x0049ffa8: lea eax, [esp + 0xc]
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0049ffac: mov dword ptr fs:[0], eax
    uint32_t t11 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t11, ctx.eax);
    // 0x0049ffb2: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x0049ffb4: mov dword ptr [esp + 8], esi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    mem.w32(t12, ctx.esi);
    // 0x0049ffb8: mov dword ptr [esi], 0x53a018
    mem.w32(ctx.esi, 0x0053a018u);
    // 0x0049ffbe: push 0x4d5ef0
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x004d5ef0u);
    // 0x0049ffc3: push 4
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x00000004u);
    // 0x0049ffc5: push 0x30
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x00000030u);
    // 0x0049ffc7: lea eax, [esi + 4]
    uint32_t t16 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0049ffca: push eax
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, ctx.eax);
    // 0x0049ffcb: mov dword ptr [esp + 0x24], 0
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t18, 0x00000000u);
    // 0x0049ffd3: call 0x4e1c34
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x0049ffd8u);
    hle_crt_004e1c34(ctx, mem);
    // 0x0049ffd8: mov dword ptr [esi], 0x5359dc
    mem.w32(ctx.esi, 0x005359dcu);
    // 0x0049ffde: mov ecx, dword ptr [esp + 0xc]
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t21 = mem.r32(t20);
    ctx.ecx = static_cast<uint32_t>(t21);
    // 0x0049ffe2: mov dword ptr fs:[0], ecx
    uint32_t t22 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t22, ctx.ecx);
    // 0x0049ffe9: pop ecx
    uint32_t t23 = ctx.esp;
    uint32_t t24 = mem.r32(t23);
    uint32_t t25 = static_cast<uint32_t>(t23 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    ctx.ecx = static_cast<uint32_t>(t24);
    // 0x0049ffea: pop esi
    uint32_t t26 = ctx.esp;
    uint32_t t27 = mem.r32(t26);
    uint32_t t28 = static_cast<uint32_t>(t26 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    ctx.esi = static_cast<uint32_t>(t27);
    // 0x0049ffeb: add esp, 0x10
    uint32_t t29 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t29);
    ctx.esp = static_cast<uint32_t>(t29);
    // 0x0049ffee: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0049fff0 | subsystem=Input | canonical | 5 blocks | 22 insns
void sub_0049fff0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0049fff0: xor ecx, ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.ecx = static_cast<uint32_t>(t0);
    // 0x0049fff2: xor edx, edx
    uint32_t t1 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.edx = static_cast<uint32_t>(t1);
    // 0x0049fff4: add eax, 0xc
    uint32_t t2 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x0000000cu, t2);
    ctx.eax = static_cast<uint32_t>(t2);
}
bb_0049fff7: {
    // 0x0049fff7: cmp edx, 3
    uint32_t t3 = static_cast<uint32_t>(ctx.edx - 0x00000003u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000003u, t3);
    // 0x0049fffa: ja 0x4a001f
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_004a001f;
    goto bb_0049fffc;
}
bb_004a001f: {
    // 0x004a001f: add edx, 1
    uint32_t t4 = static_cast<uint32_t>(ctx.edx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000001u, t4);
    ctx.edx = static_cast<uint32_t>(t4);
    // 0x004a0022: add eax, 0x30
    uint32_t t5 = static_cast<uint32_t>(ctx.eax + 0x00000030u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000030u, t5);
    ctx.eax = static_cast<uint32_t>(t5);
    // 0x004a0025: cmp edx, 4
    uint32_t t6 = static_cast<uint32_t>(ctx.edx - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000004u, t6);
    // 0x004a0028: jl 0x49fff7
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0049fff7;
    goto bb_004a002a;
}
bb_0049fffc: {
    // 0x0049fffc: mov dword ptr [eax - 4], ecx
    uint32_t t7 = static_cast<uint32_t>(ctx.eax + 0xfffffffcu);
    mem.w32(t7, ctx.ecx);
    // 0x0049ffff: mov dword ptr [eax], ecx
    mem.w32(ctx.eax, ctx.ecx);
    // 0x004a0001: mov dword ptr [eax + 4], ecx
    uint32_t t8 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w32(t8, ctx.ecx);
    // 0x004a0004: mov dword ptr [eax + 8], ecx
    uint32_t t9 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    mem.w32(t9, ctx.ecx);
    // 0x004a0007: mov dword ptr [eax + 0xc], ecx
    uint32_t t10 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    mem.w32(t10, ctx.ecx);
    // 0x004a000a: mov dword ptr [eax + 0x10], ecx
    uint32_t t11 = static_cast<uint32_t>(ctx.eax + 0x00000010u);
    mem.w32(t11, ctx.ecx);
    // 0x004a000d: mov dword ptr [eax + 0x14], ecx
    uint32_t t12 = static_cast<uint32_t>(ctx.eax + 0x00000014u);
    mem.w32(t12, ctx.ecx);
    // 0x004a0010: mov dword ptr [eax + 0x18], ecx
    uint32_t t13 = static_cast<uint32_t>(ctx.eax + 0x00000018u);
    mem.w32(t13, ctx.ecx);
    // 0x004a0013: mov dword ptr [eax + 0x1c], ecx
    uint32_t t14 = static_cast<uint32_t>(ctx.eax + 0x0000001cu);
    mem.w32(t14, ctx.ecx);
    // 0x004a0016: mov dword ptr [eax + 0x20], ecx
    uint32_t t15 = static_cast<uint32_t>(ctx.eax + 0x00000020u);
    mem.w32(t15, ctx.ecx);
    // 0x004a0019: mov dword ptr [eax + 0x24], ecx
    uint32_t t16 = static_cast<uint32_t>(ctx.eax + 0x00000024u);
    mem.w32(t16, ctx.ecx);
    // 0x004a001c: mov dword ptr [eax - 8], edx
    uint32_t t17 = static_cast<uint32_t>(ctx.eax + 0xfffffff8u);
    mem.w32(t17, ctx.edx);
    goto bb_004a001f;
}
bb_004a002a: {
    // 0x004a002a: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004a0030 | subsystem=Input | canonical | 3 blocks | 14 insns
void sub_004a0030(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a0030: mov eax, dword ptr [esp + 4]
    uint32_t t0 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint32_t t1 = mem.r32(t0);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x004a0034: mov eax, dword ptr [eax]
    uint32_t t2 = mem.r32(ctx.eax);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x004a0036: push esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.esi);
    // 0x004a0037: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004a0039: call 0x40ff50
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x004a003eu);
    sub_0040ff50(ctx, mem);
    // 0x004a003e: test eax, eax
    uint32_t t5 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    // 0x004a0040: jne 0x4a0046
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a0046;
    goto bb_004a0042;
}
bb_004a0046: {
    // 0x004a0046: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004a0048: call 0x49fff0
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x004a004du);
    sub_0049fff0(ctx, mem);
    // 0x004a004d: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x004a0052: pop esi
    uint32_t t7 = ctx.esp;
    uint32_t t8 = mem.r32(t7);
    uint32_t t9 = static_cast<uint32_t>(t7 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    ctx.esi = static_cast<uint32_t>(t8);
    // 0x004a0053: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_004a0042: {
    // 0x004a0042: pop esi
    uint32_t t10 = ctx.esp;
    uint32_t t11 = mem.r32(t10);
    uint32_t t12 = static_cast<uint32_t>(t10 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    ctx.esi = static_cast<uint32_t>(t11);
    // 0x004a0043: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
}

// sub_004a0060 | subsystem=Input | canonical | 1 blocks | 1 insns
void sub_004a0060(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a0060: jmp 0x40fe80
    sub_0040fe80(ctx, mem);
    return;
}
}

// sub_004a0070 | subsystem=Input | canonical | 1 blocks | 7 insns
void sub_004a0070(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a0070: mov al, byte ptr [0x5544f1]
    uint8_t t0 = mem.r8(0x005544f1u);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t0));
    // 0x004a0075: and al, 0x80
    uint8_t t1 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) & static_cast<uint32_t>(uint8_t{0x80u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t1);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t1));
    // 0x004a0077: xor ecx, ecx
    uint32_t t2 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.ecx = static_cast<uint32_t>(t2);
    // 0x004a0079: cmp al, 0x80
    uint8_t t3 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) - static_cast<uint32_t>(uint8_t{0x80u}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.eax), uint8_t{0x80u}, t3);
    // 0x004a007b: sete cl
    uint8_t t4 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::E) ? 1u : 0u);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t4));
    // 0x004a007e: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x004a0080: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004a0090 | subsystem=Input | canonical | 1 blocks | 9 insns
void sub_004a0090(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a0090: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x004a0091: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004a0093: call 0x410870
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x004a0098u);
    sub_00410870(ctx, mem);
    // 0x004a0098: call 0x410930
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x004a009du);
    sub_00410930(ctx, mem);
    // 0x004a009d: call 0x410a80
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x004a00a2u);
    sub_00410a80(ctx, mem);
    // 0x004a00a2: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x004a00a3: call 0x4a00d0
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, 0x004a00a8u);
    sub_004a00d0(ctx, mem);
    // 0x004a00a8: pop esi
    uint32_t t6 = ctx.esp;
    uint32_t t7 = mem.r32(t6);
    uint32_t t8 = static_cast<uint32_t>(t6 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    ctx.esi = static_cast<uint32_t>(t7);
    // 0x004a00a9: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004a00b0 | subsystem=Input | canonical | 1 blocks | 11 insns
void sub_004a00b0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a00b0: push ebx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebx);
    // 0x004a00b1: mov ebx, dword ptr [esp + 8]
    uint32_t t1 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t2 = mem.r32(t1);
    ctx.ebx = static_cast<uint32_t>(t2);
    // 0x004a00b5: lea eax, [ebx + ebx*2]
    uint32_t t3 = recomp_detail::shl<uint32_t>(ctx.ebx, 0x00000001u);
    uint32_t t4 = static_cast<uint32_t>(ctx.ebx + t3);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x004a00b8: shl eax, 4
    uint32_t t5 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x04u}) & 0x0000001fu);
    uint32_t t6 = recomp_detail::shl<uint32_t>(ctx.eax, t5);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.eax, t5, t6);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x004a00bb: push edi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.edi);
    // 0x004a00bc: mov edi, dword ptr [esp + 0x10]
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t9 = mem.r32(t8);
    ctx.edi = static_cast<uint32_t>(t9);
    // 0x004a00c0: lea eax, [eax + ecx + 4]
    uint32_t t10 = static_cast<uint32_t>(ctx.eax + ctx.ecx);
    uint32_t t11 = static_cast<uint32_t>(t10 + 0x00000004u);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x004a00c4: call 0x4a0230
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x004a00c9u);
    sub_004a0230(ctx, mem);
    // 0x004a00c9: pop edi
    uint32_t t13 = ctx.esp;
    uint32_t t14 = mem.r32(t13);
    uint32_t t15 = static_cast<uint32_t>(t13 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    ctx.edi = static_cast<uint32_t>(t14);
    // 0x004a00ca: pop ebx
    uint32_t t16 = ctx.esp;
    uint32_t t17 = mem.r32(t16);
    uint32_t t18 = static_cast<uint32_t>(t16 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    ctx.ebx = static_cast<uint32_t>(t17);
    // 0x004a00cb: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
}

// sub_004a00d0 | subsystem=Input | canonical | 8 blocks | 33 insns
void sub_004a00d0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a00d0: push ebx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebx);
    // 0x004a00d1: push ebp
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebp);
    // 0x004a00d2: mov ebp, dword ptr [esp + 0xc]
    uint32_t t2 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t3 = mem.r32(t2);
    ctx.ebp = static_cast<uint32_t>(t3);
    // 0x004a00d6: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x004a00d7: push edi
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.edi);
    // 0x004a00d8: add ebp, 0xc
    uint32_t t6 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebp, 0x0000000cu, t6);
    ctx.ebp = static_cast<uint32_t>(t6);
    // 0x004a00db: mov dword ptr [esp + 0x14], 4
    uint32_t t7 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t7, 0x00000004u);
}
bb_004a00e3: {
    // 0x004a00e3: mov ebx, dword ptr [ebp - 4]
    uint32_t t8 = static_cast<uint32_t>(ctx.ebp + 0xfffffffcu);
    uint32_t t9 = mem.r32(t8);
    ctx.ebx = static_cast<uint32_t>(t9);
    // 0x004a00e6: lea esi, [ebp - 8]
    uint32_t t10 = static_cast<uint32_t>(ctx.ebp + 0xfffffff8u);
    ctx.esi = static_cast<uint32_t>(t10);
    // 0x004a00e9: mov edi, esi
    ctx.edi = static_cast<uint32_t>(ctx.esi);
    // 0x004a00eb: mov dword ptr [ebp], 0
    mem.w32(ctx.ebp, 0x00000000u);
    // 0x004a00f2: mov dword ptr [ebp + 4], 0
    uint32_t t11 = static_cast<uint32_t>(ctx.ebp + 0x00000004u);
    mem.w32(t11, 0x00000000u);
    // 0x004a00f9: call 0x49fb50
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x004a00feu);
    sub_0049fb50(ctx, mem);
    // 0x004a00fe: cmp eax, ebx
    uint32_t t13 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t13);
    // 0x004a0100: mov dword ptr [ebp - 4], eax
    uint32_t t14 = static_cast<uint32_t>(ctx.ebp + 0xfffffffcu);
    mem.w32(t14, ctx.eax);
    // 0x004a0103: je 0x4a0108
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a0108;
    goto bb_004a0105;
}
bb_004a0108: {
    // 0x004a0108: test eax, eax
    uint32_t t15 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t15);
    // 0x004a010a: jne 0x4a0113
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a0113;
    goto bb_004a010c;
}
bb_004a0105: {
    // 0x004a0105: mov dword ptr [ebp], eax
    mem.w32(ctx.ebp, ctx.eax);
    goto bb_004a0108;
}
bb_004a0113: {
    // 0x004a0113: call 0x49fad0
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x004a0118u);
    sub_0049fad0(ctx, mem);
    // 0x004a0118: mov ebx, esi
    ctx.ebx = static_cast<uint32_t>(ctx.esi);
    // 0x004a011a: call 0x49f9e0
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x004a011fu);
    sub_0049f9e0(ctx, mem);
    // 0x004a011f: add ebp, 0x30
    uint32_t t18 = static_cast<uint32_t>(ctx.ebp + 0x00000030u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebp, 0x00000030u, t18);
    ctx.ebp = static_cast<uint32_t>(t18);
    // 0x004a0122: sub dword ptr [esp + 0x14], 1
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t20 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t20, 0x00000001u, t21);
    mem.w32(t19, t21);
    // 0x004a0127: jne 0x4a00e3
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a00e3;
    goto bb_004a0129;
}
bb_004a010c: {
    // 0x004a010c: test ebx, ebx
    uint32_t t22 = static_cast<uint32_t>(ctx.ebx & ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t22);
    // 0x004a010e: je 0x4a0113
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a0113;
    goto bb_004a0110;
}
bb_004a0129: {
    // 0x004a0129: pop edi
    uint32_t t23 = ctx.esp;
    uint32_t t24 = mem.r32(t23);
    uint32_t t25 = static_cast<uint32_t>(t23 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    ctx.edi = static_cast<uint32_t>(t24);
    // 0x004a012a: pop esi
    uint32_t t26 = ctx.esp;
    uint32_t t27 = mem.r32(t26);
    uint32_t t28 = static_cast<uint32_t>(t26 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    ctx.esi = static_cast<uint32_t>(t27);
    // 0x004a012b: pop ebp
    uint32_t t29 = ctx.esp;
    uint32_t t30 = mem.r32(t29);
    uint32_t t31 = static_cast<uint32_t>(t29 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    ctx.ebp = static_cast<uint32_t>(t30);
    // 0x004a012c: pop ebx
    uint32_t t32 = ctx.esp;
    uint32_t t33 = mem.r32(t32);
    uint32_t t34 = static_cast<uint32_t>(t32 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    ctx.ebx = static_cast<uint32_t>(t33);
    // 0x004a012d: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_004a0110: {
    // 0x004a0110: mov dword ptr [ebp + 4], ebx
    uint32_t t35 = static_cast<uint32_t>(ctx.ebp + 0x00000004u);
    mem.w32(t35, ctx.ebx);
    goto bb_004a0113;
}
}

// sub_004a0140 | subsystem=Input | canonical | 11 blocks | 38 insns
void sub_004a0140(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a0140: movzx edx, byte ptr [eax]
    uint8_t t0 = mem.r8(ctx.eax);
    uint32_t t1 = static_cast<uint32_t>(static_cast<uint8_t>(t0));
    ctx.edx = static_cast<uint32_t>(t1);
    // 0x004a0143: mov cl, 0x80
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(uint8_t{0x80u}));
    // 0x004a0145: test byte ptr [edx + 0x5544f0], cl
    uint32_t t2 = static_cast<uint32_t>(ctx.edx + 0x005544f0u);
    uint8_t t3 = mem.r8(t2);
    uint8_t t4 = static_cast<uint8_t>(static_cast<uint32_t>(t3) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t4);
    // 0x004a014b: je 0x4a016c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a016c;
    goto bb_004a014d;
}
bb_004a016c: {
    // 0x004a016c: movzx edx, byte ptr [eax + 1]
    uint32_t t5 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    uint8_t t6 = mem.r8(t5);
    uint32_t t7 = static_cast<uint32_t>(static_cast<uint8_t>(t6));
    ctx.edx = static_cast<uint32_t>(t7);
    // 0x004a0170: test byte ptr [edx + 0x5544f0], cl
    uint32_t t8 = static_cast<uint32_t>(ctx.edx + 0x005544f0u);
    uint8_t t9 = mem.r8(t8);
    uint8_t t10 = static_cast<uint8_t>(static_cast<uint32_t>(t9) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t10);
    // 0x004a0176: movzx edx, byte ptr [eax + 2]
    uint32_t t11 = static_cast<uint32_t>(ctx.eax + 0x00000002u);
    uint8_t t12 = mem.r8(t11);
    uint32_t t13 = static_cast<uint32_t>(static_cast<uint8_t>(t12));
    ctx.edx = static_cast<uint32_t>(t13);
    // 0x004a017a: je 0x4a0197
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a0197;
    goto bb_004a017c;
}
bb_004a014d: {
    // 0x004a014d: movzx edx, byte ptr [eax + 2]
    uint32_t t14 = static_cast<uint32_t>(ctx.eax + 0x00000002u);
    uint8_t t15 = mem.r8(t14);
    uint32_t t16 = static_cast<uint32_t>(static_cast<uint8_t>(t15));
    ctx.edx = static_cast<uint32_t>(t16);
    // 0x004a0151: test byte ptr [edx + 0x5544f0], cl
    uint32_t t17 = static_cast<uint32_t>(ctx.edx + 0x005544f0u);
    uint8_t t18 = mem.r8(t17);
    uint8_t t19 = static_cast<uint8_t>(static_cast<uint32_t>(t18) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t19);
    // 0x004a0157: je 0x4a015c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a015c;
    goto bb_004a0159;
}
bb_004a0197: {
    // 0x004a0197: test byte ptr [edx + 0x5544f0], cl
    uint32_t t20 = static_cast<uint32_t>(ctx.edx + 0x005544f0u);
    uint8_t t21 = mem.r8(t20);
    uint8_t t22 = static_cast<uint8_t>(static_cast<uint32_t>(t21) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t22);
    // 0x004a019d: je 0x4a01a2
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a01a2;
    goto bb_004a019f;
}
bb_004a017c: {
    // 0x004a017c: test byte ptr [edx + 0x5544f0], cl
    uint32_t t23 = static_cast<uint32_t>(ctx.edx + 0x005544f0u);
    uint8_t t24 = mem.r8(t23);
    uint8_t t25 = static_cast<uint8_t>(static_cast<uint32_t>(t24) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t25);
    // 0x004a0182: je 0x4a0187
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a0187;
    goto bb_004a0184;
}
bb_004a015c: {
    // 0x004a015c: movzx eax, byte ptr [eax + 3]
    uint32_t t26 = static_cast<uint32_t>(ctx.eax + 0x00000003u);
    uint8_t t27 = mem.r8(t26);
    uint32_t t28 = static_cast<uint32_t>(static_cast<uint8_t>(t27));
    ctx.eax = static_cast<uint32_t>(t28);
    // 0x004a0160: mov al, byte ptr [eax + 0x5544f0]
    uint32_t t29 = static_cast<uint32_t>(ctx.eax + 0x005544f0u);
    uint8_t t30 = mem.r8(t29);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t30));
    // 0x004a0166: shr al, 7
    uint32_t t31 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x07u}) & 0x0000001fu);
    uint8_t t32 = recomp_detail::shr<uint8_t>(recomp_detail::r8l(ctx.eax), t31);
    recomp_detail::update_flags_shr<uint8_t>(ctx, recomp_detail::r8l(ctx.eax), t31, t32);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t32));
    // 0x004a0169: or al, 2
    uint8_t t33 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) | static_cast<uint32_t>(uint8_t{0x02u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t33);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t33));
    // 0x004a016b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a0159: {
    // 0x004a0159: mov al, 1
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(uint8_t{0x01u}));
    // 0x004a015b: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a01a2: {
    // 0x004a01a2: movzx eax, byte ptr [eax + 3]
    uint32_t t34 = static_cast<uint32_t>(ctx.eax + 0x00000003u);
    uint8_t t35 = mem.r8(t34);
    uint32_t t36 = static_cast<uint32_t>(static_cast<uint8_t>(t35));
    ctx.eax = static_cast<uint32_t>(t36);
    // 0x004a01a6: mov al, byte ptr [eax + 0x5544f0]
    uint32_t t37 = static_cast<uint32_t>(ctx.eax + 0x005544f0u);
    uint8_t t38 = mem.r8(t37);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t38));
    // 0x004a01ac: and al, cl
    uint8_t t39 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t39);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t39));
    // 0x004a01ae: neg al
    uint8_t t40 = static_cast<uint8_t>(0u - static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)));
    recomp_detail::update_flags_neg<uint8_t>(ctx, recomp_detail::r8l(ctx.eax), t40);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t40));
    // 0x004a01b0: sbb al, al
    uint8_t t41 = static_cast<uint8_t>(recomp_detail::get_flag(ctx, kFlagCF));
    uint8_t t42 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) - static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)));
    uint8_t t43 = static_cast<uint8_t>(static_cast<uint32_t>(t42) - static_cast<uint32_t>(t41));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.eax), recomp_detail::r8l(ctx.eax), t43, t41);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t43));
    // 0x004a01b2: and eax, 6
    uint32_t t44 = static_cast<uint32_t>(ctx.eax & 0x00000006u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t44);
    ctx.eax = static_cast<uint32_t>(t44);
    // 0x004a01b5: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a019f: {
    // 0x004a019f: mov al, 4
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(uint8_t{0x04u}));
    // 0x004a01a1: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a0187: {
    // 0x004a0187: movzx eax, byte ptr [eax + 3]
    uint32_t t45 = static_cast<uint32_t>(ctx.eax + 0x00000003u);
    uint8_t t46 = mem.r8(t45);
    uint32_t t47 = static_cast<uint32_t>(static_cast<uint8_t>(t46));
    ctx.eax = static_cast<uint32_t>(t47);
    // 0x004a018b: mov al, byte ptr [eax + 0x5544f0]
    uint32_t t48 = static_cast<uint32_t>(ctx.eax + 0x005544f0u);
    uint8_t t49 = mem.r8(t48);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t49));
    // 0x004a0191: shr al, 7
    uint32_t t50 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x07u}) & 0x0000001fu);
    uint8_t t51 = recomp_detail::shr<uint8_t>(recomp_detail::r8l(ctx.eax), t50);
    recomp_detail::update_flags_shr<uint8_t>(ctx, recomp_detail::r8l(ctx.eax), t50, t51);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t51));
    // 0x004a0194: or al, 8
    uint8_t t52 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) | static_cast<uint32_t>(uint8_t{0x08u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t52);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t52));
    // 0x004a0196: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a0184: {
    // 0x004a0184: mov al, 7
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(uint8_t{0x07u}));
    // 0x004a0186: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004a01c0 | subsystem=Input | canonical | 13 blocks | 29 insns
void sub_004a01c0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a01c0: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x004a01c1: movzx esi, byte ptr [ecx + 4]
    uint32_t t1 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    uint8_t t2 = mem.r8(t1);
    uint32_t t3 = static_cast<uint32_t>(static_cast<uint8_t>(t2));
    ctx.esi = static_cast<uint32_t>(t3);
    // 0x004a01c5: mov edx, 0x80
    ctx.edx = static_cast<uint32_t>(0x00000080u);
    // 0x004a01ca: xor eax, eax
    uint32_t t4 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x004a01cc: test byte ptr [esi + 0x5544f0], dl
    uint32_t t5 = static_cast<uint32_t>(ctx.esi + 0x005544f0u);
    uint8_t t6 = mem.r8(t5);
    uint8_t t7 = static_cast<uint8_t>(static_cast<uint32_t>(t6) & static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t7);
    // 0x004a01d2: je 0x4a01d9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a01d9;
    goto bb_004a01d4;
}
bb_004a01d9: {
    // 0x004a01d9: movzx esi, byte ptr [ecx + 5]
    uint32_t t8 = static_cast<uint32_t>(ctx.ecx + 0x00000005u);
    uint8_t t9 = mem.r8(t8);
    uint32_t t10 = static_cast<uint32_t>(static_cast<uint8_t>(t9));
    ctx.esi = static_cast<uint32_t>(t10);
    // 0x004a01dd: test byte ptr [esi + 0x5544f0], dl
    uint32_t t11 = static_cast<uint32_t>(ctx.esi + 0x005544f0u);
    uint8_t t12 = mem.r8(t11);
    uint8_t t13 = static_cast<uint8_t>(static_cast<uint32_t>(t12) & static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t13);
    // 0x004a01e3: je 0x4a01ea
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a01ea;
    goto bb_004a01e5;
}
bb_004a01d4: {
    // 0x004a01d4: mov eax, 0x410
    ctx.eax = static_cast<uint32_t>(0x00000410u);
    goto bb_004a01d9;
}
bb_004a01ea: {
    // 0x004a01ea: movzx esi, byte ptr [ecx + 6]
    uint32_t t14 = static_cast<uint32_t>(ctx.ecx + 0x00000006u);
    uint8_t t15 = mem.r8(t14);
    uint32_t t16 = static_cast<uint32_t>(static_cast<uint8_t>(t15));
    ctx.esi = static_cast<uint32_t>(t16);
    // 0x004a01ee: test byte ptr [esi + 0x5544f0], dl
    uint32_t t17 = static_cast<uint32_t>(ctx.esi + 0x005544f0u);
    uint8_t t18 = mem.r8(t17);
    uint8_t t19 = static_cast<uint8_t>(static_cast<uint32_t>(t18) & static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t19);
    // 0x004a01f4: je 0x4a01f9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a01f9;
    goto bb_004a01f6;
}
bb_004a01e5: {
    // 0x004a01e5: or eax, 0x820
    uint32_t t20 = static_cast<uint32_t>(ctx.eax | 0x00000820u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t20);
    ctx.eax = static_cast<uint32_t>(t20);
    goto bb_004a01ea;
}
bb_004a01f9: {
    // 0x004a01f9: movzx esi, byte ptr [ecx + 7]
    uint32_t t21 = static_cast<uint32_t>(ctx.ecx + 0x00000007u);
    uint8_t t22 = mem.r8(t21);
    uint32_t t23 = static_cast<uint32_t>(static_cast<uint8_t>(t22));
    ctx.esi = static_cast<uint32_t>(t23);
    // 0x004a01fd: test byte ptr [esi + 0x5544f0], dl
    uint32_t t24 = static_cast<uint32_t>(ctx.esi + 0x005544f0u);
    uint8_t t25 = mem.r8(t24);
    uint8_t t26 = static_cast<uint8_t>(static_cast<uint32_t>(t25) & static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t26);
    // 0x004a0203: je 0x4a0208
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a0208;
    goto bb_004a0205;
}
bb_004a01f6: {
    // 0x004a01f6: or eax, 8
    uint32_t t27 = static_cast<uint32_t>(ctx.eax | 0x00000008u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t27);
    ctx.eax = static_cast<uint32_t>(t27);
    goto bb_004a01f9;
}
bb_004a0208: {
    // 0x004a0208: movzx esi, byte ptr [ecx + 8]
    uint32_t t28 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint8_t t29 = mem.r8(t28);
    uint32_t t30 = static_cast<uint32_t>(static_cast<uint8_t>(t29));
    ctx.esi = static_cast<uint32_t>(t30);
    // 0x004a020c: test byte ptr [esi + 0x5544f0], dl
    uint32_t t31 = static_cast<uint32_t>(ctx.esi + 0x005544f0u);
    uint8_t t32 = mem.r8(t31);
    uint8_t t33 = static_cast<uint8_t>(static_cast<uint32_t>(t32) & static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t33);
    // 0x004a0212: pop esi
    uint32_t t34 = ctx.esp;
    uint32_t t35 = mem.r32(t34);
    uint32_t t36 = static_cast<uint32_t>(t34 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    ctx.esi = static_cast<uint32_t>(t35);
    // 0x004a0213: je 0x4a0217
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a0217;
    goto bb_004a0215;
}
bb_004a0205: {
    // 0x004a0205: or eax, 4
    uint32_t t37 = static_cast<uint32_t>(ctx.eax | 0x00000004u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t37);
    ctx.eax = static_cast<uint32_t>(t37);
    goto bb_004a0208;
}
bb_004a0217: {
    // 0x004a0217: movzx ecx, byte ptr [ecx + 9]
    uint32_t t38 = static_cast<uint32_t>(ctx.ecx + 0x00000009u);
    uint8_t t39 = mem.r8(t38);
    uint32_t t40 = static_cast<uint32_t>(static_cast<uint8_t>(t39));
    ctx.ecx = static_cast<uint32_t>(t40);
    // 0x004a021b: test byte ptr [ecx + 0x5544f0], dl
    uint32_t t41 = static_cast<uint32_t>(ctx.ecx + 0x005544f0u);
    uint8_t t42 = mem.r8(t41);
    uint8_t t43 = static_cast<uint8_t>(static_cast<uint32_t>(t42) & static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t43);
    // 0x004a0221: je 0x4a0226
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a0226;
    goto bb_004a0223;
}
bb_004a0215: {
    // 0x004a0215: or eax, edx
    uint32_t t44 = static_cast<uint32_t>(ctx.eax | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t44);
    ctx.eax = static_cast<uint32_t>(t44);
    goto bb_004a0217;
}
bb_004a0226: {
    // 0x004a0226: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a0223: {
    // 0x004a0223: or eax, 1
    uint32_t t45 = static_cast<uint32_t>(ctx.eax | 0x00000001u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t45);
    ctx.eax = static_cast<uint32_t>(t45);
    goto bb_004a0226;
}
}

// sub_004a0230 | subsystem=Input | canonical | 21 blocks | 66 insns
void sub_004a0230(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a0230: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x004a0231: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004a0233: test esi, esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    // 0x004a0235: je 0x4a02c2
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a02c2;
    goto bb_004a023b;
}
bb_004a02c2: {
    // 0x004a02c2: cmp dword ptr [0x76e768], 0
    uint32_t t2 = mem.r32(0x0076e768u);
    uint32_t t3 = static_cast<uint32_t>(t2 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t2, 0x00000000u, t3);
    // 0x004a02c9: jne 0x4a02f5
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a02f5;
    goto bb_004a02cb;
}
bb_004a023b: {
    // 0x004a023b: cmp dword ptr [edi], 0
    uint32_t t4 = mem.r32(ctx.edi);
    uint32_t t5 = static_cast<uint32_t>(t4 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t4, 0x00000000u, t5);
    // 0x004a023e: jne 0x4a0250
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a0250;
    goto bb_004a0240;
}
bb_004a02f5: {
    // 0x004a02f5: pop esi
    uint32_t t6 = ctx.esp;
    uint32_t t7 = mem.r32(t6);
    uint32_t t8 = static_cast<uint32_t>(t6 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    ctx.esi = static_cast<uint32_t>(t7);
    // 0x004a02f6: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a02cb: {
    // 0x004a02cb: cmp ebx, 2
    uint32_t t9 = static_cast<uint32_t>(ctx.ebx - 0x00000002u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, 0x00000002u, t9);
    // 0x004a02ce: jge 0x4a02f5
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_004a02f5;
    goto bb_004a02d0;
}
bb_004a0250: {
    // 0x004a0250: xor eax, eax
    uint32_t t10 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x004a0252: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a0254: call 0x49fe80
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0x004a0259u);
    sub_0049fe80(ctx, mem);
    // 0x004a0259: mov dword ptr [edi + 4], eax
    uint32_t t12 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    mem.w32(t12, ctx.eax);
    // 0x004a025c: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x004a0261: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a0263: call 0x49fe80
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x004a0268u);
    sub_0049fe80(ctx, mem);
    // 0x004a0268: mov dword ptr [edi + 8], eax
    uint32_t t14 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    mem.w32(t14, ctx.eax);
    // 0x004a026b: mov eax, 2
    ctx.eax = static_cast<uint32_t>(0x00000002u);
    goto bb_004a0270;
}
bb_004a0240: {
    // 0x004a0240: mov eax, dword ptr [esi + 4]
    uint32_t t15 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t16 = mem.r32(t15);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x004a0243: test eax, eax
    uint32_t t17 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t17);
    // 0x004a0245: jne 0x4a024e
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a024e;
    goto bb_004a0247;
}
bb_004a02d0: {
    // 0x004a02d0: cmp dword ptr [edi], 0
    uint32_t t18 = mem.r32(ctx.edi);
    uint32_t t19 = static_cast<uint32_t>(t18 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t18, 0x00000000u, t19);
    // 0x004a02d3: lea esi, [ebx + ebx*4]
    uint32_t t20 = recomp_detail::shl<uint32_t>(ctx.ebx, 0x00000002u);
    uint32_t t21 = static_cast<uint32_t>(ctx.ebx + t20);
    ctx.esi = static_cast<uint32_t>(t21);
    // 0x004a02d6: lea esi, [esi*2 + 0x54d2c0]
    uint32_t t22 = recomp_detail::shl<uint32_t>(ctx.esi, 0x00000001u);
    uint32_t t23 = static_cast<uint32_t>(t22 + 0x0054d2c0u);
    ctx.esi = static_cast<uint32_t>(t23);
    // 0x004a02dd: jne 0x4a02eb
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a02eb;
    goto bb_004a02df;
}
bb_004a0270: {
    // 0x004a0270: lea ecx, [eax - 2]
    uint32_t t24 = static_cast<uint32_t>(ctx.eax + 0xfffffffeu);
    ctx.ecx = static_cast<uint32_t>(t24);
    // 0x004a0273: mov edx, 1
    ctx.edx = static_cast<uint32_t>(0x00000001u);
    // 0x004a0278: shl edx, cl
    uint32_t t25 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t26 = static_cast<uint32_t>(t25 & 0x0000001fu);
    uint32_t t27 = recomp_detail::shl<uint32_t>(ctx.edx, t26);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.edx, t26, t27);
    ctx.edx = static_cast<uint32_t>(t27);
    // 0x004a027a: test dword ptr [esi + 0x24], edx
    uint32_t t28 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    uint32_t t29 = mem.r32(t28);
    uint32_t t30 = static_cast<uint32_t>(t29 & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t30);
    // 0x004a027d: je 0x4a0282
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a0282;
    goto bb_004a027f;
}
bb_004a024e: {
    // 0x004a024e: mov dword ptr [edi], eax
    mem.w32(ctx.edi, ctx.eax);
    goto bb_004a0250;
}
bb_004a0247: {
    // 0x004a0247: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a0249: call 0x49fe80
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x004a024eu);
    sub_0049fe80(ctx, mem);
    goto bb_004a024e;
}
bb_004a02eb: {
    // 0x004a02eb: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a02ed: call 0x4a01c0
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x004a02f2u);
    sub_004a01c0(ctx, mem);
    // 0x004a02f2: or dword ptr [edi + 0xc], eax
    uint32_t t33 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    uint32_t t34 = mem.r32(t33);
    uint32_t t35 = static_cast<uint32_t>(t34 | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t35);
    mem.w32(t33, t35);
    goto bb_004a02f5;
}
bb_004a02df: {
    // 0x004a02df: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004a02e1: call 0x4a0140
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, 0x004a02e6u);
    sub_004a0140(ctx, mem);
    // 0x004a02e6: movzx edx, al
    uint32_t t37 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.eax)));
    ctx.edx = static_cast<uint32_t>(t37);
    // 0x004a02e9: mov dword ptr [edi], edx
    mem.w32(ctx.edi, ctx.edx);
    goto bb_004a02eb;
}
bb_004a0282: {
    // 0x004a0282: lea ecx, [eax - 1]
    uint32_t t38 = static_cast<uint32_t>(ctx.eax + 0xffffffffu);
    ctx.ecx = static_cast<uint32_t>(t38);
    // 0x004a0285: mov edx, 1
    ctx.edx = static_cast<uint32_t>(0x00000001u);
    // 0x004a028a: shl edx, cl
    uint32_t t39 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t40 = static_cast<uint32_t>(t39 & 0x0000001fu);
    uint32_t t41 = recomp_detail::shl<uint32_t>(ctx.edx, t40);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.edx, t40, t41);
    ctx.edx = static_cast<uint32_t>(t41);
    // 0x004a028c: test dword ptr [esi + 0x24], edx
    uint32_t t42 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    uint32_t t43 = mem.r32(t42);
    uint32_t t44 = static_cast<uint32_t>(t43 & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t44);
    // 0x004a028f: je 0x4a0294
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a0294;
    goto bb_004a0291;
}
bb_004a027f: {
    // 0x004a027f: or dword ptr [edi + 0xc], edx
    uint32_t t45 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    uint32_t t46 = mem.r32(t45);
    uint32_t t47 = static_cast<uint32_t>(t46 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t47);
    mem.w32(t45, t47);
    goto bb_004a0282;
}
bb_004a0294: {
    // 0x004a0294: mov edx, 1
    ctx.edx = static_cast<uint32_t>(0x00000001u);
    // 0x004a0299: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x004a029b: shl edx, cl
    uint32_t t48 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t49 = static_cast<uint32_t>(t48 & 0x0000001fu);
    uint32_t t50 = recomp_detail::shl<uint32_t>(ctx.edx, t49);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.edx, t49, t50);
    ctx.edx = static_cast<uint32_t>(t50);
    // 0x004a029d: test dword ptr [esi + 0x24], edx
    uint32_t t51 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    uint32_t t52 = mem.r32(t51);
    uint32_t t53 = static_cast<uint32_t>(t52 & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t53);
    // 0x004a02a0: je 0x4a02a5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a02a5;
    goto bb_004a02a2;
}
bb_004a0291: {
    // 0x004a0291: or dword ptr [edi + 0xc], edx
    uint32_t t54 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    uint32_t t55 = mem.r32(t54);
    uint32_t t56 = static_cast<uint32_t>(t55 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t56);
    mem.w32(t54, t56);
    goto bb_004a0294;
}
bb_004a02a5: {
    // 0x004a02a5: lea ecx, [eax + 1]
    uint32_t t57 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.ecx = static_cast<uint32_t>(t57);
    // 0x004a02a8: mov edx, 1
    ctx.edx = static_cast<uint32_t>(0x00000001u);
    // 0x004a02ad: shl edx, cl
    uint32_t t58 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t59 = static_cast<uint32_t>(t58 & 0x0000001fu);
    uint32_t t60 = recomp_detail::shl<uint32_t>(ctx.edx, t59);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.edx, t59, t60);
    ctx.edx = static_cast<uint32_t>(t60);
    // 0x004a02af: test dword ptr [esi + 0x24], edx
    uint32_t t61 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    uint32_t t62 = mem.r32(t61);
    uint32_t t63 = static_cast<uint32_t>(t62 & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t63);
    // 0x004a02b2: je 0x4a02b7
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a02b7;
    goto bb_004a02b4;
}
bb_004a02a2: {
    // 0x004a02a2: or dword ptr [edi + 0xc], edx
    uint32_t t64 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    uint32_t t65 = mem.r32(t64);
    uint32_t t66 = static_cast<uint32_t>(t65 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t66);
    mem.w32(t64, t66);
    goto bb_004a02a5;
}
bb_004a02b7: {
    // 0x004a02b7: add eax, 4
    uint32_t t67 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000004u, t67);
    ctx.eax = static_cast<uint32_t>(t67);
    // 0x004a02ba: lea ecx, [eax - 2]
    uint32_t t68 = static_cast<uint32_t>(ctx.eax + 0xfffffffeu);
    ctx.ecx = static_cast<uint32_t>(t68);
    // 0x004a02bd: cmp ecx, 0x20
    uint32_t t69 = static_cast<uint32_t>(ctx.ecx - 0x00000020u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000020u, t69);
    // 0x004a02c0: jl 0x4a0270
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004a0270;
    goto bb_004a02c2;
}
bb_004a02b4: {
    // 0x004a02b4: or dword ptr [edi + 0xc], edx
    uint32_t t70 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    uint32_t t71 = mem.r32(t70);
    uint32_t t72 = static_cast<uint32_t>(t71 | ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t72);
    mem.w32(t70, t72);
    goto bb_004a02b7;
}
}

// sub_004a0300 | subsystem=Input | canonical | 3 blocks | 12 insns
void sub_004a0300(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a0300: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x004a0301: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004a0303: mov dword ptr [esi], 0x53a040
    mem.w32(ctx.esi, 0x0053a040u);
    // 0x004a0309: call 0x41eda0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x004a030eu);
    sub_0041eda0(ctx, mem);
    // 0x004a030e: test byte ptr [esp + 8], 1
    uint32_t t2 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint8_t t3 = mem.r8(t2);
    uint8_t t4 = static_cast<uint8_t>(static_cast<uint32_t>(t3) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t4);
    // 0x004a0313: je 0x4a031e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a031e;
    goto bb_004a0315;
}
bb_004a031e: {
    // 0x004a031e: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004a0320: pop esi
    uint32_t t5 = ctx.esp;
    uint32_t t6 = mem.r32(t5);
    uint32_t t7 = static_cast<uint32_t>(t5 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x004a0321: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_004a0315: {
    // 0x004a0315: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x004a0316: call 0x4e02f3
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x004a031bu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a031b: add esp, 4
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t10);
    ctx.esp = static_cast<uint32_t>(t10);
    goto bb_004a031e;
}
}

// sub_004a0330 | subsystem=Input | canonical | 1 blocks | 37 insns
void sub_004a0330(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a0330: mov eax, dword ptr [esp + 4]
    uint32_t t0 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint32_t t1 = mem.r32(t0);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x004a0334: shl eax, 7
    uint32_t t2 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x07u}) & 0x0000001fu);
    uint32_t t3 = recomp_detail::shl<uint32_t>(ctx.eax, t2);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.eax, t2, t3);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004a0337: add eax, ecx
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + ctx.ecx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.ecx, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x004a0339: xor ecx, ecx
    uint32_t t5 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    ctx.ecx = static_cast<uint32_t>(t5);
    // 0x004a033b: mov dword ptr [eax + 0x80], ecx
    uint32_t t6 = static_cast<uint32_t>(ctx.eax + 0x00000080u);
    mem.w32(t6, ctx.ecx);
    // 0x004a0341: mov dword ptr [eax + 0x84], ecx
    uint32_t t7 = static_cast<uint32_t>(ctx.eax + 0x00000084u);
    mem.w32(t7, ctx.ecx);
    // 0x004a0347: mov dword ptr [eax + 0x88], ecx
    uint32_t t8 = static_cast<uint32_t>(ctx.eax + 0x00000088u);
    mem.w32(t8, ctx.ecx);
    // 0x004a034d: mov dword ptr [eax + 0x8c], ecx
    uint32_t t9 = static_cast<uint32_t>(ctx.eax + 0x0000008cu);
    mem.w32(t9, ctx.ecx);
    // 0x004a0353: mov dword ptr [eax + 0x90], ecx
    uint32_t t10 = static_cast<uint32_t>(ctx.eax + 0x00000090u);
    mem.w32(t10, ctx.ecx);
    // 0x004a0359: mov dword ptr [eax + 0x94], ecx
    uint32_t t11 = static_cast<uint32_t>(ctx.eax + 0x00000094u);
    mem.w32(t11, ctx.ecx);
    // 0x004a035f: mov dword ptr [eax + 0x98], ecx
    uint32_t t12 = static_cast<uint32_t>(ctx.eax + 0x00000098u);
    mem.w32(t12, ctx.ecx);
    // 0x004a0365: mov dword ptr [eax + 0x9c], ecx
    uint32_t t13 = static_cast<uint32_t>(ctx.eax + 0x0000009cu);
    mem.w32(t13, ctx.ecx);
    // 0x004a036b: mov dword ptr [eax + 0xa0], ecx
    uint32_t t14 = static_cast<uint32_t>(ctx.eax + 0x000000a0u);
    mem.w32(t14, ctx.ecx);
    // 0x004a0371: mov dword ptr [eax + 0xa4], ecx
    uint32_t t15 = static_cast<uint32_t>(ctx.eax + 0x000000a4u);
    mem.w32(t15, ctx.ecx);
    // 0x004a0377: mov dword ptr [eax + 0xa8], ecx
    uint32_t t16 = static_cast<uint32_t>(ctx.eax + 0x000000a8u);
    mem.w32(t16, ctx.ecx);
    // 0x004a037d: mov dword ptr [eax + 0xac], ecx
    uint32_t t17 = static_cast<uint32_t>(ctx.eax + 0x000000acu);
    mem.w32(t17, ctx.ecx);
    // 0x004a0383: mov dword ptr [eax + 0xb0], ecx
    uint32_t t18 = static_cast<uint32_t>(ctx.eax + 0x000000b0u);
    mem.w32(t18, ctx.ecx);
    // 0x004a0389: mov dword ptr [eax + 0xb4], ecx
    uint32_t t19 = static_cast<uint32_t>(ctx.eax + 0x000000b4u);
    mem.w32(t19, ctx.ecx);
    // 0x004a038f: mov dword ptr [eax + 0xb8], ecx
    uint32_t t20 = static_cast<uint32_t>(ctx.eax + 0x000000b8u);
    mem.w32(t20, ctx.ecx);
    // 0x004a0395: mov dword ptr [eax + 0xbc], ecx
    uint32_t t21 = static_cast<uint32_t>(ctx.eax + 0x000000bcu);
    mem.w32(t21, ctx.ecx);
    // 0x004a039b: mov dword ptr [eax + 0xc0], ecx
    uint32_t t22 = static_cast<uint32_t>(ctx.eax + 0x000000c0u);
    mem.w32(t22, ctx.ecx);
    // 0x004a03a1: mov dword ptr [eax + 0xc4], ecx
    uint32_t t23 = static_cast<uint32_t>(ctx.eax + 0x000000c4u);
    mem.w32(t23, ctx.ecx);
    // 0x004a03a7: mov dword ptr [eax + 0xc8], ecx
    uint32_t t24 = static_cast<uint32_t>(ctx.eax + 0x000000c8u);
    mem.w32(t24, ctx.ecx);
    // 0x004a03ad: mov dword ptr [eax + 0xcc], ecx
    uint32_t t25 = static_cast<uint32_t>(ctx.eax + 0x000000ccu);
    mem.w32(t25, ctx.ecx);
    // 0x004a03b3: mov dword ptr [eax + 0xd0], ecx
    uint32_t t26 = static_cast<uint32_t>(ctx.eax + 0x000000d0u);
    mem.w32(t26, ctx.ecx);
    // 0x004a03b9: mov dword ptr [eax + 0xd4], ecx
    uint32_t t27 = static_cast<uint32_t>(ctx.eax + 0x000000d4u);
    mem.w32(t27, ctx.ecx);
    // 0x004a03bf: mov dword ptr [eax + 0xd8], ecx
    uint32_t t28 = static_cast<uint32_t>(ctx.eax + 0x000000d8u);
    mem.w32(t28, ctx.ecx);
    // 0x004a03c5: mov dword ptr [eax + 0xdc], ecx
    uint32_t t29 = static_cast<uint32_t>(ctx.eax + 0x000000dcu);
    mem.w32(t29, ctx.ecx);
    // 0x004a03cb: mov dword ptr [eax + 0xe0], ecx
    uint32_t t30 = static_cast<uint32_t>(ctx.eax + 0x000000e0u);
    mem.w32(t30, ctx.ecx);
    // 0x004a03d1: mov dword ptr [eax + 0xe4], ecx
    uint32_t t31 = static_cast<uint32_t>(ctx.eax + 0x000000e4u);
    mem.w32(t31, ctx.ecx);
    // 0x004a03d7: mov dword ptr [eax + 0x68], 0x10
    uint32_t t32 = static_cast<uint32_t>(ctx.eax + 0x00000068u);
    mem.w32(t32, 0x00000010u);
    // 0x004a03de: mov dword ptr [eax + 0x6c], 0x20
    uint32_t t33 = static_cast<uint32_t>(ctx.eax + 0x0000006cu);
    mem.w32(t33, 0x00000020u);
    // 0x004a03e5: mov dword ptr [eax + 0x70], 8
    uint32_t t34 = static_cast<uint32_t>(ctx.eax + 0x00000070u);
    mem.w32(t34, 0x00000008u);
    // 0x004a03ec: mov dword ptr [eax + 0x74], 4
    uint32_t t35 = static_cast<uint32_t>(ctx.eax + 0x00000074u);
    mem.w32(t35, 0x00000004u);
    // 0x004a03f3: mov dword ptr [eax + 0x78], 0x80
    uint32_t t36 = static_cast<uint32_t>(ctx.eax + 0x00000078u);
    mem.w32(t36, 0x00000080u);
    // 0x004a03fa: mov dword ptr [eax + 0x7c], 0x40
    uint32_t t37 = static_cast<uint32_t>(ctx.eax + 0x0000007cu);
    mem.w32(t37, 0x00000040u);
    // 0x004a0401: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
}

// sub_004a0410 | subsystem=Input | canonical | 1 blocks | 37 insns
void sub_004a0410(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a0410: mov eax, dword ptr [esp + 4]
    uint32_t t0 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint32_t t1 = mem.r32(t0);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x004a0414: shl eax, 7
    uint32_t t2 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x07u}) & 0x0000001fu);
    uint32_t t3 = recomp_detail::shl<uint32_t>(ctx.eax, t2);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.eax, t2, t3);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004a0417: add eax, ecx
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + ctx.ecx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.ecx, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x004a0419: xor ecx, ecx
    uint32_t t5 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    ctx.ecx = static_cast<uint32_t>(t5);
    // 0x004a041b: mov dword ptr [eax + 0x27c], ecx
    uint32_t t6 = static_cast<uint32_t>(ctx.eax + 0x0000027cu);
    mem.w32(t6, ctx.ecx);
    // 0x004a0421: mov dword ptr [eax + 0x280], ecx
    uint32_t t7 = static_cast<uint32_t>(ctx.eax + 0x00000280u);
    mem.w32(t7, ctx.ecx);
    // 0x004a0427: mov dword ptr [eax + 0x284], ecx
    uint32_t t8 = static_cast<uint32_t>(ctx.eax + 0x00000284u);
    mem.w32(t8, ctx.ecx);
    // 0x004a042d: mov dword ptr [eax + 0x288], ecx
    uint32_t t9 = static_cast<uint32_t>(ctx.eax + 0x00000288u);
    mem.w32(t9, ctx.ecx);
    // 0x004a0433: mov dword ptr [eax + 0x28c], ecx
    uint32_t t10 = static_cast<uint32_t>(ctx.eax + 0x0000028cu);
    mem.w32(t10, ctx.ecx);
    // 0x004a0439: mov dword ptr [eax + 0x290], ecx
    uint32_t t11 = static_cast<uint32_t>(ctx.eax + 0x00000290u);
    mem.w32(t11, ctx.ecx);
    // 0x004a043f: mov dword ptr [eax + 0x294], ecx
    uint32_t t12 = static_cast<uint32_t>(ctx.eax + 0x00000294u);
    mem.w32(t12, ctx.ecx);
    // 0x004a0445: mov dword ptr [eax + 0x298], ecx
    uint32_t t13 = static_cast<uint32_t>(ctx.eax + 0x00000298u);
    mem.w32(t13, ctx.ecx);
    // 0x004a044b: mov dword ptr [eax + 0x29c], ecx
    uint32_t t14 = static_cast<uint32_t>(ctx.eax + 0x0000029cu);
    mem.w32(t14, ctx.ecx);
    // 0x004a0451: mov dword ptr [eax + 0x2a0], ecx
    uint32_t t15 = static_cast<uint32_t>(ctx.eax + 0x000002a0u);
    mem.w32(t15, ctx.ecx);
    // 0x004a0457: mov dword ptr [eax + 0x2a4], ecx
    uint32_t t16 = static_cast<uint32_t>(ctx.eax + 0x000002a4u);
    mem.w32(t16, ctx.ecx);
    // 0x004a045d: mov dword ptr [eax + 0x2a8], ecx
    uint32_t t17 = static_cast<uint32_t>(ctx.eax + 0x000002a8u);
    mem.w32(t17, ctx.ecx);
    // 0x004a0463: mov dword ptr [eax + 0x2ac], ecx
    uint32_t t18 = static_cast<uint32_t>(ctx.eax + 0x000002acu);
    mem.w32(t18, ctx.ecx);
    // 0x004a0469: mov dword ptr [eax + 0x2b0], ecx
    uint32_t t19 = static_cast<uint32_t>(ctx.eax + 0x000002b0u);
    mem.w32(t19, ctx.ecx);
    // 0x004a046f: mov dword ptr [eax + 0x2b4], ecx
    uint32_t t20 = static_cast<uint32_t>(ctx.eax + 0x000002b4u);
    mem.w32(t20, ctx.ecx);
    // 0x004a0475: mov dword ptr [eax + 0x2b8], ecx
    uint32_t t21 = static_cast<uint32_t>(ctx.eax + 0x000002b8u);
    mem.w32(t21, ctx.ecx);
    // 0x004a047b: mov dword ptr [eax + 0x2bc], ecx
    uint32_t t22 = static_cast<uint32_t>(ctx.eax + 0x000002bcu);
    mem.w32(t22, ctx.ecx);
    // 0x004a0481: mov dword ptr [eax + 0x2c0], ecx
    uint32_t t23 = static_cast<uint32_t>(ctx.eax + 0x000002c0u);
    mem.w32(t23, ctx.ecx);
    // 0x004a0487: mov dword ptr [eax + 0x2c4], ecx
    uint32_t t24 = static_cast<uint32_t>(ctx.eax + 0x000002c4u);
    mem.w32(t24, ctx.ecx);
    // 0x004a048d: mov dword ptr [eax + 0x2c8], ecx
    uint32_t t25 = static_cast<uint32_t>(ctx.eax + 0x000002c8u);
    mem.w32(t25, ctx.ecx);
    // 0x004a0493: mov dword ptr [eax + 0x2cc], ecx
    uint32_t t26 = static_cast<uint32_t>(ctx.eax + 0x000002ccu);
    mem.w32(t26, ctx.ecx);
    // 0x004a0499: mov dword ptr [eax + 0x2d0], ecx
    uint32_t t27 = static_cast<uint32_t>(ctx.eax + 0x000002d0u);
    mem.w32(t27, ctx.ecx);
    // 0x004a049f: mov dword ptr [eax + 0x2d4], ecx
    uint32_t t28 = static_cast<uint32_t>(ctx.eax + 0x000002d4u);
    mem.w32(t28, ctx.ecx);
    // 0x004a04a5: mov dword ptr [eax + 0x2d8], ecx
    uint32_t t29 = static_cast<uint32_t>(ctx.eax + 0x000002d8u);
    mem.w32(t29, ctx.ecx);
    // 0x004a04ab: mov dword ptr [eax + 0x2dc], ecx
    uint32_t t30 = static_cast<uint32_t>(ctx.eax + 0x000002dcu);
    mem.w32(t30, ctx.ecx);
    // 0x004a04b1: mov dword ptr [eax + 0x2e0], ecx
    uint32_t t31 = static_cast<uint32_t>(ctx.eax + 0x000002e0u);
    mem.w32(t31, ctx.ecx);
    // 0x004a04b7: mov dword ptr [eax + 0x268], 0x400
    uint32_t t32 = static_cast<uint32_t>(ctx.eax + 0x00000268u);
    mem.w32(t32, 0x00000400u);
    // 0x004a04c1: mov dword ptr [eax + 0x26c], 0x800
    uint32_t t33 = static_cast<uint32_t>(ctx.eax + 0x0000026cu);
    mem.w32(t33, 0x00000800u);
    // 0x004a04cb: mov dword ptr [eax + 0x270], 1
    uint32_t t34 = static_cast<uint32_t>(ctx.eax + 0x00000270u);
    mem.w32(t34, 0x00000001u);
    // 0x004a04d5: mov dword ptr [eax + 0x274], 0x100
    uint32_t t35 = static_cast<uint32_t>(ctx.eax + 0x00000274u);
    mem.w32(t35, 0x00000100u);
    // 0x004a04df: mov dword ptr [eax + 0x278], 0x200
    uint32_t t36 = static_cast<uint32_t>(ctx.eax + 0x00000278u);
    mem.w32(t36, 0x00000200u);
    // 0x004a04e9: mov dword ptr [eax + 0x2e4], 0xfffff3fe
    uint32_t t37 = static_cast<uint32_t>(ctx.eax + 0x000002e4u);
    mem.w32(t37, 0xfffff3feu);
    // 0x004a04f3: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
}

// sub_004a0f30 | subsystem=Input | canonical | 38 blocks | 190 insns
void sub_004a0f30(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a0f30: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x004a0f31: mov ebp, dword ptr [esp + 8]
    uint32_t t1 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t2 = mem.r32(t1);
    ctx.ebp = static_cast<uint32_t>(t2);
    // 0x004a0f35: push edi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.edi);
    // 0x004a0f36: xor edi, edi
    uint32_t t4 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    ctx.edi = static_cast<uint32_t>(t4);
    // 0x004a0f38: test ebp, ebp
    uint32_t t5 = static_cast<uint32_t>(ctx.ebp & ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    // 0x004a0f3a: jne 0x4a0f41
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a0f41;
    goto bb_004a0f3c;
}
bb_004a0f41: {
    // 0x004a0f41: push ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebx);
    // 0x004a0f42: mov eax, 2
    ctx.eax = static_cast<uint32_t>(0x00000002u);
    // 0x004a0f47: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x004a0f48: mov esi, dword ptr [ebp + 0x24]
    uint32_t t8 = static_cast<uint32_t>(ctx.ebp + 0x00000024u);
    uint32_t t9 = mem.r32(t8);
    ctx.esi = static_cast<uint32_t>(t9);
    // 0x004a0f4b: lea edx, [eax + 6]
    uint32_t t10 = static_cast<uint32_t>(ctx.eax + 0x00000006u);
    ctx.edx = static_cast<uint32_t>(t10);
    // 0x004a0f4e: mov edi, edi
    ctx.edi = static_cast<uint32_t>(ctx.edi);
    goto bb_004a0f50;
}
bb_004a0f3c: {
    // 0x004a0f3c: pop edi
    uint32_t t11 = ctx.esp;
    uint32_t t12 = mem.r32(t11);
    uint32_t t13 = static_cast<uint32_t>(t11 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    ctx.edi = static_cast<uint32_t>(t12);
    // 0x004a0f3d: xor eax, eax
    uint32_t t14 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x004a0f3f: pop ebp
    uint32_t t15 = ctx.esp;
    uint32_t t16 = mem.r32(t15);
    uint32_t t17 = static_cast<uint32_t>(t15 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    ctx.ebp = static_cast<uint32_t>(t16);
    // 0x004a0f40: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a0f50: {
    // 0x004a0f50: lea ecx, [eax - 2]
    uint32_t t18 = static_cast<uint32_t>(ctx.eax + 0xfffffffeu);
    ctx.ecx = static_cast<uint32_t>(t18);
    // 0x004a0f53: mov ebx, esi
    ctx.ebx = static_cast<uint32_t>(ctx.esi);
    // 0x004a0f55: shr ebx, cl
    uint32_t t19 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t20 = static_cast<uint32_t>(t19 & 0x0000001fu);
    uint32_t t21 = recomp_detail::shr<uint32_t>(ctx.ebx, t20);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.ebx, t20, t21);
    ctx.ebx = static_cast<uint32_t>(t21);
    // 0x004a0f57: test bl, 1
    uint8_t t22 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t22);
    // 0x004a0f5a: je 0x4a0f5f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a0f5f;
    goto bb_004a0f5c;
}
bb_004a0f5f: {
    // 0x004a0f5f: lea ecx, [eax - 1]
    uint32_t t23 = static_cast<uint32_t>(ctx.eax + 0xffffffffu);
    ctx.ecx = static_cast<uint32_t>(t23);
    // 0x004a0f62: mov ebx, esi
    ctx.ebx = static_cast<uint32_t>(ctx.esi);
    // 0x004a0f64: shr ebx, cl
    uint32_t t24 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t25 = static_cast<uint32_t>(t24 & 0x0000001fu);
    uint32_t t26 = recomp_detail::shr<uint32_t>(ctx.ebx, t25);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.ebx, t25, t26);
    ctx.ebx = static_cast<uint32_t>(t26);
    // 0x004a0f66: test bl, 1
    uint8_t t27 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t27);
    // 0x004a0f69: je 0x4a0f6d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a0f6d;
    goto bb_004a0f6b;
}
bb_004a0f5c: {
    // 0x004a0f5c: lea edi, [eax - 1]
    uint32_t t28 = static_cast<uint32_t>(ctx.eax + 0xffffffffu);
    ctx.edi = static_cast<uint32_t>(t28);
    goto bb_004a0f5f;
}
bb_004a0f6d: {
    // 0x004a0f6d: mov ebx, esi
    ctx.ebx = static_cast<uint32_t>(ctx.esi);
    // 0x004a0f6f: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x004a0f71: shr ebx, cl
    uint32_t t29 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t30 = static_cast<uint32_t>(t29 & 0x0000001fu);
    uint32_t t31 = recomp_detail::shr<uint32_t>(ctx.ebx, t30);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.ebx, t30, t31);
    ctx.ebx = static_cast<uint32_t>(t31);
    // 0x004a0f73: test bl, 1
    uint8_t t32 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t32);
    // 0x004a0f76: je 0x4a0f7b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a0f7b;
    goto bb_004a0f78;
}
bb_004a0f6b: {
    // 0x004a0f6b: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    goto bb_004a0f6d;
}
bb_004a0f7b: {
    // 0x004a0f7b: lea ecx, [eax + 1]
    uint32_t t33 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.ecx = static_cast<uint32_t>(t33);
    // 0x004a0f7e: mov ebx, esi
    ctx.ebx = static_cast<uint32_t>(ctx.esi);
    // 0x004a0f80: shr ebx, cl
    uint32_t t34 = static_cast<uint32_t>(static_cast<uint8_t>(recomp_detail::r8l(ctx.ecx)));
    uint32_t t35 = static_cast<uint32_t>(t34 & 0x0000001fu);
    uint32_t t36 = recomp_detail::shr<uint32_t>(ctx.ebx, t35);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.ebx, t35, t36);
    ctx.ebx = static_cast<uint32_t>(t36);
    // 0x004a0f82: test bl, 1
    uint8_t t37 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t37);
    // 0x004a0f85: je 0x4a0f8a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a0f8a;
    goto bb_004a0f87;
}
bb_004a0f78: {
    // 0x004a0f78: lea edi, [eax + 1]
    uint32_t t38 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.edi = static_cast<uint32_t>(t38);
    goto bb_004a0f7b;
}
bb_004a0f8a: {
    // 0x004a0f8a: add eax, 4
    uint32_t t39 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000004u, t39);
    ctx.eax = static_cast<uint32_t>(t39);
    // 0x004a0f8d: sub edx, 1
    uint32_t t40 = static_cast<uint32_t>(ctx.edx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000001u, t40);
    ctx.edx = static_cast<uint32_t>(t40);
    // 0x004a0f90: jne 0x4a0f50
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a0f50;
    goto bb_004a0f92;
}
bb_004a0f87: {
    // 0x004a0f87: lea edi, [eax + 2]
    uint32_t t41 = static_cast<uint32_t>(ctx.eax + 0x00000002u);
    ctx.edi = static_cast<uint32_t>(t41);
    goto bb_004a0f8a;
}
bb_004a0f92: {
    // 0x004a0f92: test edi, edi
    uint32_t t42 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t42);
    // 0x004a0f94: pop esi
    uint32_t t43 = ctx.esp;
    uint32_t t44 = mem.r32(t43);
    uint32_t t45 = static_cast<uint32_t>(t43 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    ctx.esi = static_cast<uint32_t>(t44);
    // 0x004a0f95: pop ebx
    uint32_t t46 = ctx.esp;
    uint32_t t47 = mem.r32(t46);
    uint32_t t48 = static_cast<uint32_t>(t46 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    ctx.ebx = static_cast<uint32_t>(t47);
    // 0x004a0f96: jne 0x4a10ca
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a10ca;
    goto bb_004a0f9c;
}
bb_004a10ca: {
    // 0x004a10ca: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x004a10cc: pop edi
    uint32_t t49 = ctx.esp;
    uint32_t t50 = mem.r32(t49);
    uint32_t t51 = static_cast<uint32_t>(t49 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    ctx.edi = static_cast<uint32_t>(t50);
    // 0x004a10cd: pop ebp
    uint32_t t52 = ctx.esp;
    uint32_t t53 = mem.r32(t52);
    uint32_t t54 = static_cast<uint32_t>(t52 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    ctx.ebp = static_cast<uint32_t>(t53);
    // 0x004a10ce: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a0f9c: {
    // 0x004a0f9c: mov ecx, dword ptr [ebp]
    uint32_t t55 = mem.r32(ctx.ebp);
    ctx.ecx = static_cast<uint32_t>(t55);
    // 0x004a0f9f: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x004a0fa1: cdq
    uint32_t t56 = recomp_detail::sar<uint32_t>(ctx.eax, 0x0000001fu);
    ctx.edx = static_cast<uint32_t>(t56);
    // 0x004a0fa2: xor eax, edx
    uint32_t t57 = static_cast<uint32_t>(ctx.eax ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t57);
    ctx.eax = static_cast<uint32_t>(t57);
    // 0x004a0fa4: sub eax, edx
    uint32_t t58 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t58);
    ctx.eax = static_cast<uint32_t>(t58);
    // 0x004a0fa6: cmp eax, 0x65
    uint32_t t59 = static_cast<uint32_t>(ctx.eax - 0x00000065u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000065u, t59);
    // 0x004a0fa9: jl 0x4a0fba
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004a0fba;
    goto bb_004a0fab;
}
bb_004a0fba: {
    // 0x004a0fba: mov ecx, dword ptr [ebp + 4]
    uint32_t t60 = static_cast<uint32_t>(ctx.ebp + 0x00000004u);
    uint32_t t61 = mem.r32(t60);
    ctx.ecx = static_cast<uint32_t>(t61);
    // 0x004a0fbd: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x004a0fbf: cdq
    uint32_t t62 = recomp_detail::sar<uint32_t>(ctx.eax, 0x0000001fu);
    ctx.edx = static_cast<uint32_t>(t62);
    // 0x004a0fc0: xor eax, edx
    uint32_t t63 = static_cast<uint32_t>(ctx.eax ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t63);
    ctx.eax = static_cast<uint32_t>(t63);
    // 0x004a0fc2: sub eax, edx
    uint32_t t64 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t64);
    ctx.eax = static_cast<uint32_t>(t64);
    // 0x004a0fc4: cmp eax, 0x65
    uint32_t t65 = static_cast<uint32_t>(ctx.eax - 0x00000065u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000065u, t65);
    // 0x004a0fc7: jl 0x4a0fda
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004a0fda;
    goto bb_004a0fc9;
}
bb_004a0fab: {
    // 0x004a0fab: xor eax, eax
    uint32_t t66 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t66);
    ctx.eax = static_cast<uint32_t>(t66);
    // 0x004a0fad: test ecx, ecx
    uint32_t t67 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t67);
    // 0x004a0faf: setle al
    uint8_t t68 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::LE) ? 1u : 0u);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t68));
    // 0x004a0fb2: add eax, 0x15
    uint32_t t69 = static_cast<uint32_t>(ctx.eax + 0x00000015u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000015u, t69);
    ctx.eax = static_cast<uint32_t>(t69);
    // 0x004a0fb5: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x004a0fb7: pop edi
    uint32_t t70 = ctx.esp;
    uint32_t t71 = mem.r32(t70);
    uint32_t t72 = static_cast<uint32_t>(t70 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    ctx.edi = static_cast<uint32_t>(t71);
    // 0x004a0fb8: pop ebp
    uint32_t t73 = ctx.esp;
    uint32_t t74 = mem.r32(t73);
    uint32_t t75 = static_cast<uint32_t>(t73 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    ctx.ebp = static_cast<uint32_t>(t74);
    // 0x004a0fb9: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a0fda: {
    // 0x004a0fda: mov ecx, dword ptr [ebp + 8]
    uint32_t t76 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t77 = mem.r32(t76);
    ctx.ecx = static_cast<uint32_t>(t77);
    // 0x004a0fdd: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x004a0fdf: cdq
    uint32_t t78 = recomp_detail::sar<uint32_t>(ctx.eax, 0x0000001fu);
    ctx.edx = static_cast<uint32_t>(t78);
    // 0x004a0fe0: xor eax, edx
    uint32_t t79 = static_cast<uint32_t>(ctx.eax ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t79);
    ctx.eax = static_cast<uint32_t>(t79);
    // 0x004a0fe2: sub eax, edx
    uint32_t t80 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t80);
    ctx.eax = static_cast<uint32_t>(t80);
    // 0x004a0fe4: cmp eax, 0x65
    uint32_t t81 = static_cast<uint32_t>(ctx.eax - 0x00000065u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000065u, t81);
    // 0x004a0fe7: jl 0x4a0ff8
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004a0ff8;
    goto bb_004a0fe9;
}
bb_004a0fc9: {
    // 0x004a0fc9: xor edx, edx
    uint32_t t82 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t82);
    ctx.edx = static_cast<uint32_t>(t82);
    // 0x004a0fcb: test ecx, ecx
    uint32_t t83 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t83);
    // 0x004a0fcd: setle dl
    uint8_t t84 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::LE) ? 1u : 0u);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t84));
    // 0x004a0fd0: add edx, 0x17
    uint32_t t85 = static_cast<uint32_t>(ctx.edx + 0x00000017u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000017u, t85);
    ctx.edx = static_cast<uint32_t>(t85);
    // 0x004a0fd3: mov edi, edx
    ctx.edi = static_cast<uint32_t>(ctx.edx);
    // 0x004a0fd5: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x004a0fd7: pop edi
    uint32_t t86 = ctx.esp;
    uint32_t t87 = mem.r32(t86);
    uint32_t t88 = static_cast<uint32_t>(t86 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t88);
    ctx.edi = static_cast<uint32_t>(t87);
    // 0x004a0fd8: pop ebp
    uint32_t t89 = ctx.esp;
    uint32_t t90 = mem.r32(t89);
    uint32_t t91 = static_cast<uint32_t>(t89 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    ctx.ebp = static_cast<uint32_t>(t90);
    // 0x004a0fd9: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a0ff8: {
    // 0x004a0ff8: mov ecx, dword ptr [ebp + 0xc]
    uint32_t t92 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t93 = mem.r32(t92);
    ctx.ecx = static_cast<uint32_t>(t93);
    // 0x004a0ffb: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x004a0ffd: cdq
    uint32_t t94 = recomp_detail::sar<uint32_t>(ctx.eax, 0x0000001fu);
    ctx.edx = static_cast<uint32_t>(t94);
    // 0x004a0ffe: xor eax, edx
    uint32_t t95 = static_cast<uint32_t>(ctx.eax ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t95);
    ctx.eax = static_cast<uint32_t>(t95);
    // 0x004a1000: sub eax, edx
    uint32_t t96 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t96);
    ctx.eax = static_cast<uint32_t>(t96);
    // 0x004a1002: cmp eax, 0x65
    uint32_t t97 = static_cast<uint32_t>(ctx.eax - 0x00000065u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000065u, t97);
    // 0x004a1005: jl 0x4a1018
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004a1018;
    goto bb_004a1007;
}
bb_004a0fe9: {
    // 0x004a0fe9: xor eax, eax
    uint32_t t98 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t98);
    ctx.eax = static_cast<uint32_t>(t98);
    // 0x004a0feb: test ecx, ecx
    uint32_t t99 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t99);
    // 0x004a0fed: setle al
    uint8_t t100 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::LE) ? 1u : 0u);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t100));
    // 0x004a0ff0: add eax, 0x19
    uint32_t t101 = static_cast<uint32_t>(ctx.eax + 0x00000019u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000019u, t101);
    ctx.eax = static_cast<uint32_t>(t101);
    // 0x004a0ff3: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x004a0ff5: pop edi
    uint32_t t102 = ctx.esp;
    uint32_t t103 = mem.r32(t102);
    uint32_t t104 = static_cast<uint32_t>(t102 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t104);
    ctx.edi = static_cast<uint32_t>(t103);
    // 0x004a0ff6: pop ebp
    uint32_t t105 = ctx.esp;
    uint32_t t106 = mem.r32(t105);
    uint32_t t107 = static_cast<uint32_t>(t105 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t107);
    ctx.ebp = static_cast<uint32_t>(t106);
    // 0x004a0ff7: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a1018: {
    // 0x004a1018: mov ecx, dword ptr [ebp + 0x10]
    uint32_t t108 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    uint32_t t109 = mem.r32(t108);
    ctx.ecx = static_cast<uint32_t>(t109);
    // 0x004a101b: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x004a101d: cdq
    uint32_t t110 = recomp_detail::sar<uint32_t>(ctx.eax, 0x0000001fu);
    ctx.edx = static_cast<uint32_t>(t110);
    // 0x004a101e: xor eax, edx
    uint32_t t111 = static_cast<uint32_t>(ctx.eax ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t111);
    ctx.eax = static_cast<uint32_t>(t111);
    // 0x004a1020: sub eax, edx
    uint32_t t112 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t112);
    ctx.eax = static_cast<uint32_t>(t112);
    // 0x004a1022: cmp eax, 0x65
    uint32_t t113 = static_cast<uint32_t>(ctx.eax - 0x00000065u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000065u, t113);
    // 0x004a1025: jl 0x4a1036
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004a1036;
    goto bb_004a1027;
}
bb_004a1007: {
    // 0x004a1007: xor edx, edx
    uint32_t t114 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t114);
    ctx.edx = static_cast<uint32_t>(t114);
    // 0x004a1009: test ecx, ecx
    uint32_t t115 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t115);
    // 0x004a100b: setle dl
    uint8_t t116 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::LE) ? 1u : 0u);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t116));
    // 0x004a100e: add edx, 0x1b
    uint32_t t117 = static_cast<uint32_t>(ctx.edx + 0x0000001bu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x0000001bu, t117);
    ctx.edx = static_cast<uint32_t>(t117);
    // 0x004a1011: mov edi, edx
    ctx.edi = static_cast<uint32_t>(ctx.edx);
    // 0x004a1013: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x004a1015: pop edi
    uint32_t t118 = ctx.esp;
    uint32_t t119 = mem.r32(t118);
    uint32_t t120 = static_cast<uint32_t>(t118 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t120);
    ctx.edi = static_cast<uint32_t>(t119);
    // 0x004a1016: pop ebp
    uint32_t t121 = ctx.esp;
    uint32_t t122 = mem.r32(t121);
    uint32_t t123 = static_cast<uint32_t>(t121 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t123);
    ctx.ebp = static_cast<uint32_t>(t122);
    // 0x004a1017: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a1036: {
    // 0x004a1036: mov ecx, dword ptr [ebp + 0x14]
    uint32_t t124 = static_cast<uint32_t>(ctx.ebp + 0x00000014u);
    uint32_t t125 = mem.r32(t124);
    ctx.ecx = static_cast<uint32_t>(t125);
    // 0x004a1039: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x004a103b: cdq
    uint32_t t126 = recomp_detail::sar<uint32_t>(ctx.eax, 0x0000001fu);
    ctx.edx = static_cast<uint32_t>(t126);
    // 0x004a103c: xor eax, edx
    uint32_t t127 = static_cast<uint32_t>(ctx.eax ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t127);
    ctx.eax = static_cast<uint32_t>(t127);
    // 0x004a103e: sub eax, edx
    uint32_t t128 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t128);
    ctx.eax = static_cast<uint32_t>(t128);
    // 0x004a1040: cmp eax, 0x65
    uint32_t t129 = static_cast<uint32_t>(ctx.eax - 0x00000065u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000065u, t129);
    // 0x004a1043: jl 0x4a1056
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004a1056;
    goto bb_004a1045;
}
bb_004a1027: {
    // 0x004a1027: xor eax, eax
    uint32_t t130 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t130);
    ctx.eax = static_cast<uint32_t>(t130);
    // 0x004a1029: test ecx, ecx
    uint32_t t131 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t131);
    // 0x004a102b: setle al
    uint8_t t132 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::LE) ? 1u : 0u);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t132));
    // 0x004a102e: add eax, 0x1d
    uint32_t t133 = static_cast<uint32_t>(ctx.eax + 0x0000001du);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x0000001du, t133);
    ctx.eax = static_cast<uint32_t>(t133);
    // 0x004a1031: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x004a1033: pop edi
    uint32_t t134 = ctx.esp;
    uint32_t t135 = mem.r32(t134);
    uint32_t t136 = static_cast<uint32_t>(t134 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t136);
    ctx.edi = static_cast<uint32_t>(t135);
    // 0x004a1034: pop ebp
    uint32_t t137 = ctx.esp;
    uint32_t t138 = mem.r32(t137);
    uint32_t t139 = static_cast<uint32_t>(t137 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t139);
    ctx.ebp = static_cast<uint32_t>(t138);
    // 0x004a1035: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a1056: {
    // 0x004a1056: mov ecx, dword ptr [ebp + 0x1c]
    uint32_t t140 = static_cast<uint32_t>(ctx.ebp + 0x0000001cu);
    uint32_t t141 = mem.r32(t140);
    ctx.ecx = static_cast<uint32_t>(t141);
    // 0x004a1059: mov eax, ecx
    ctx.eax = static_cast<uint32_t>(ctx.ecx);
    // 0x004a105b: cdq
    uint32_t t142 = recomp_detail::sar<uint32_t>(ctx.eax, 0x0000001fu);
    ctx.edx = static_cast<uint32_t>(t142);
    // 0x004a105c: xor eax, edx
    uint32_t t143 = static_cast<uint32_t>(ctx.eax ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t143);
    ctx.eax = static_cast<uint32_t>(t143);
    // 0x004a105e: sub eax, edx
    uint32_t t144 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t144);
    ctx.eax = static_cast<uint32_t>(t144);
    // 0x004a1060: cmp eax, 0x65
    uint32_t t145 = static_cast<uint32_t>(ctx.eax - 0x00000065u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000065u, t145);
    // 0x004a1063: jl 0x4a1074
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004a1074;
    goto bb_004a1065;
}
bb_004a1045: {
    // 0x004a1045: xor edx, edx
    uint32_t t146 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t146);
    ctx.edx = static_cast<uint32_t>(t146);
    // 0x004a1047: test ecx, ecx
    uint32_t t147 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t147);
    // 0x004a1049: setle dl
    uint8_t t148 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::LE) ? 1u : 0u);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t148));
    // 0x004a104c: add edx, 0x1f
    uint32_t t149 = static_cast<uint32_t>(ctx.edx + 0x0000001fu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x0000001fu, t149);
    ctx.edx = static_cast<uint32_t>(t149);
    // 0x004a104f: mov edi, edx
    ctx.edi = static_cast<uint32_t>(ctx.edx);
    // 0x004a1051: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x004a1053: pop edi
    uint32_t t150 = ctx.esp;
    uint32_t t151 = mem.r32(t150);
    uint32_t t152 = static_cast<uint32_t>(t150 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t152);
    ctx.edi = static_cast<uint32_t>(t151);
    // 0x004a1054: pop ebp
    uint32_t t153 = ctx.esp;
    uint32_t t154 = mem.r32(t153);
    uint32_t t155 = static_cast<uint32_t>(t153 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t155);
    ctx.ebp = static_cast<uint32_t>(t154);
    // 0x004a1055: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a1074: {
    // 0x004a1074: mov ecx, dword ptr [ebp + 0x18]
    uint32_t t156 = static_cast<uint32_t>(ctx.ebp + 0x00000018u);
    uint32_t t157 = mem.r32(t156);
    ctx.ecx = static_cast<uint32_t>(t157);
    // 0x004a1077: cmp cx, 0xffff
    uint16_t t158 = static_cast<uint16_t>(static_cast<uint32_t>(recomp_detail::r16(ctx.ecx)) - static_cast<uint32_t>(uint16_t{0xffffu}));
    recomp_detail::update_flags_sub<uint16_t>(ctx, recomp_detail::r16(ctx.ecx), uint16_t{0xffffu}, t158);
    // 0x004a107c: je 0x4a1096
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1096;
    goto bb_004a107e;
}
bb_004a1065: {
    // 0x004a1065: xor eax, eax
    uint32_t t159 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t159);
    ctx.eax = static_cast<uint32_t>(t159);
    // 0x004a1067: test ecx, ecx
    uint32_t t160 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t160);
    // 0x004a1069: setle al
    uint8_t t161 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::LE) ? 1u : 0u);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t161));
    // 0x004a106c: add eax, 0x21
    uint32_t t162 = static_cast<uint32_t>(ctx.eax + 0x00000021u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000021u, t162);
    ctx.eax = static_cast<uint32_t>(t162);
    // 0x004a106f: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x004a1071: pop edi
    uint32_t t163 = ctx.esp;
    uint32_t t164 = mem.r32(t163);
    uint32_t t165 = static_cast<uint32_t>(t163 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t165);
    ctx.edi = static_cast<uint32_t>(t164);
    // 0x004a1072: pop ebp
    uint32_t t166 = ctx.esp;
    uint32_t t167 = mem.r32(t166);
    uint32_t t168 = static_cast<uint32_t>(t166 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t168);
    ctx.ebp = static_cast<uint32_t>(t167);
    // 0x004a1073: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a1096: {
    // 0x004a1096: xor eax, eax
    uint32_t t169 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t169);
    ctx.eax = static_cast<uint32_t>(t169);
    goto bb_004a1098;
}
bb_004a107e: {
    // 0x004a107e: mov eax, 0xe90452d5
    ctx.eax = static_cast<uint32_t>(0xe90452d5u);
    // 0x004a1083: mul ecx
    uint64_t t170 = (static_cast<uint64_t>(ctx.eax) * static_cast<uint64_t>(ctx.ecx));
    uint32_t t171 = static_cast<uint32_t>(t170);
    uint32_t t172 = static_cast<uint32_t>(t170 >> 32);
    ctx.eax = static_cast<uint32_t>(t171);
    ctx.edx = static_cast<uint32_t>(t172);
    recomp_detail::update_flags_mul<uint32_t>(ctx, t170);
    // 0x004a1085: shr edx, 0xc
    uint32_t t173 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x0cu}) & 0x0000001fu);
    uint32_t t174 = recomp_detail::shr<uint32_t>(ctx.edx, t173);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.edx, t173, t174);
    ctx.edx = static_cast<uint32_t>(t174);
    // 0x004a1088: cmp edx, 9
    uint32_t t175 = static_cast<uint32_t>(ctx.edx - 0x00000009u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000009u, t175);
    // 0x004a108b: ja 0x4a1096
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_004a1096;
    goto bb_004a108d;
}
bb_004a1098: {
    // 0x004a1098: sub eax, 2
    uint32_t t176 = static_cast<uint32_t>(ctx.eax - 0x00000002u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000002u, t176);
    ctx.eax = static_cast<uint32_t>(t176);
    // 0x004a109b: cmp eax, 6
    uint32_t t177 = static_cast<uint32_t>(ctx.eax - 0x00000006u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000006u, t177);
    // 0x004a109e: ja 0x4a10ca
    if (recomp_detail::eval_cond(ctx, Cond::A)) goto bb_004a10ca;
    goto bb_004a10a0;
}
bb_004a108d: {
    // 0x004a108d: mov eax, dword ptr [edx*4 + 0x550dc8]
    uint32_t t178 = recomp_detail::shl<uint32_t>(ctx.edx, 0x00000002u);
    uint32_t t179 = static_cast<uint32_t>(t178 + 0x00550dc8u);
    uint32_t t180 = mem.r32(t179);
    ctx.eax = static_cast<uint32_t>(t180);
    // 0x004a1094: jmp 0x4a1098
    goto bb_004a1098;
}
bb_004a10a0: {
    // 0x004a10a0: jmp dword ptr [eax*4 + 0x4a10d0]
    switch (ctx.eax) {
        case 0u: goto bb_004a10b1;
        case 1u: goto bb_004a10ca;
        case 2u: goto bb_004a10bb;
        case 3u: goto bb_004a10ca;
        case 4u: goto bb_004a10c5;
        case 5u: goto bb_004a10ca;
        case 6u: goto bb_004a10a7;
        default: recomp_detail::trap_halt(ctx, 0x004a10d0u, "switch_oob"); return;
    }
}
bb_004a10b1: {
    // 0x004a10b1: mov edi, 0x12
    ctx.edi = static_cast<uint32_t>(0x00000012u);
    // 0x004a10b6: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x004a10b8: pop edi
    uint32_t t181 = ctx.esp;
    uint32_t t182 = mem.r32(t181);
    uint32_t t183 = static_cast<uint32_t>(t181 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t183);
    ctx.edi = static_cast<uint32_t>(t182);
    // 0x004a10b9: pop ebp
    uint32_t t184 = ctx.esp;
    uint32_t t185 = mem.r32(t184);
    uint32_t t186 = static_cast<uint32_t>(t184 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t186);
    ctx.ebp = static_cast<uint32_t>(t185);
    // 0x004a10ba: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a10bb: {
    // 0x004a10bb: mov edi, 0x13
    ctx.edi = static_cast<uint32_t>(0x00000013u);
    // 0x004a10c0: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x004a10c2: pop edi
    uint32_t t187 = ctx.esp;
    uint32_t t188 = mem.r32(t187);
    uint32_t t189 = static_cast<uint32_t>(t187 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t189);
    ctx.edi = static_cast<uint32_t>(t188);
    // 0x004a10c3: pop ebp
    uint32_t t190 = ctx.esp;
    uint32_t t191 = mem.r32(t190);
    uint32_t t192 = static_cast<uint32_t>(t190 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t192);
    ctx.ebp = static_cast<uint32_t>(t191);
    // 0x004a10c4: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a10c5: {
    // 0x004a10c5: mov edi, 0x14
    ctx.edi = static_cast<uint32_t>(0x00000014u);
    goto bb_004a10ca;
}
bb_004a10a7: {
    // 0x004a10a7: mov edi, 0x11
    ctx.edi = static_cast<uint32_t>(0x00000011u);
    // 0x004a10ac: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x004a10ae: pop edi
    uint32_t t193 = ctx.esp;
    uint32_t t194 = mem.r32(t193);
    uint32_t t195 = static_cast<uint32_t>(t193 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t195);
    ctx.edi = static_cast<uint32_t>(t194);
    // 0x004a10af: pop ebp
    uint32_t t196 = ctx.esp;
    uint32_t t197 = mem.r32(t196);
    uint32_t t198 = static_cast<uint32_t>(t196 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t198);
    ctx.ebp = static_cast<uint32_t>(t197);
    // 0x004a10b0: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004a10f0 | subsystem=Input | canonical | 6 blocks | 23 insns
void sub_004a10f0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a10f0: cmp dword ptr [0x54d14c], 0
    uint32_t t0 = mem.r32(0x0054d14cu);
    uint32_t t1 = static_cast<uint32_t>(t0 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t0, 0x00000000u, t1);
    // 0x004a10f7: push esi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.esi);
    // 0x004a10f8: push edi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.edi);
    // 0x004a10f9: mov esi, 0x54d138
    ctx.esi = static_cast<uint32_t>(0x0054d138u);
    // 0x004a10fe: je 0x4a111a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a111a;
    goto bb_004a1100;
}
bb_004a111a: {
    // 0x004a111a: pop edi
    uint32_t t4 = ctx.esp;
    uint32_t t5 = mem.r32(t4);
    uint32_t t6 = static_cast<uint32_t>(t4 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    ctx.edi = static_cast<uint32_t>(t5);
    // 0x004a111b: xor eax, eax
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x004a111d: pop esi
    uint32_t t8 = ctx.esp;
    uint32_t t9 = mem.r32(t8);
    uint32_t t10 = static_cast<uint32_t>(t8 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    ctx.esi = static_cast<uint32_t>(t9);
    // 0x004a111e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a1100: {
    // 0x004a1100: mov edi, dword ptr [0x51b300]
    uint32_t t11 = mem.r32(0x0051b300u);
    ctx.edi = static_cast<uint32_t>(t11);
}
bb_004a1106: {
    // 0x004a1106: mov eax, dword ptr [esi]
    uint32_t t12 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x004a1108: push eax
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, ctx.eax);
    // 0x004a1109: push ebx
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, ctx.ebx);
    // 0x004a110a: call edi
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x004a110cu);
    call_indirect(ctx, mem, ctx.edi);
    // 0x004a110c: cmp eax, 1
    uint32_t t16 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t16);
    // 0x004a110f: je 0x4a111f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a111f;
    goto bb_004a1111;
}
bb_004a111f: {
    // 0x004a111f: mov eax, dword ptr [esi + 4]
    uint32_t t17 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t18 = mem.r32(t17);
    ctx.eax = static_cast<uint32_t>(t18);
    // 0x004a1122: pop edi
    uint32_t t19 = ctx.esp;
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t19 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    ctx.edi = static_cast<uint32_t>(t20);
    // 0x004a1123: pop esi
    uint32_t t22 = ctx.esp;
    uint32_t t23 = mem.r32(t22);
    uint32_t t24 = static_cast<uint32_t>(t22 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    ctx.esi = static_cast<uint32_t>(t23);
    // 0x004a1124: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a1111: {
    // 0x004a1111: add esi, 0x18
    uint32_t t25 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000018u, t25);
    ctx.esi = static_cast<uint32_t>(t25);
    // 0x004a1114: cmp dword ptr [esi + 0x14], 0
    uint32_t t26 = static_cast<uint32_t>(ctx.esi + 0x00000014u);
    uint32_t t27 = mem.r32(t26);
    uint32_t t28 = static_cast<uint32_t>(t27 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t27, 0x00000000u, t28);
    // 0x004a1118: jne 0x4a1106
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a1106;
    goto bb_004a111a;
}
}

// sub_004a1130 | subsystem=Input | canonical | 11 blocks | 57 insns
void sub_004a1130(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a1130: cmp dword ptr [0x54d14c], 0
    uint32_t t0 = mem.r32(0x0054d14cu);
    uint32_t t1 = static_cast<uint32_t>(t0 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t0, 0x00000000u, t1);
    // 0x004a1137: push ebx
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebx);
    // 0x004a1138: push esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.esi);
    // 0x004a1139: mov esi, 0x54d138
    ctx.esi = static_cast<uint32_t>(0x0054d138u);
    // 0x004a113e: je 0x4a115a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a115a;
    goto bb_004a1140;
}
bb_004a115a: {
    // 0x004a115a: cmp dword ptr [esi], 0
    uint32_t t4 = mem.r32(ctx.esi);
    uint32_t t5 = static_cast<uint32_t>(t4 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t4, 0x00000000u, t5);
    // 0x004a115d: je 0x4a11b8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a11b8;
    goto bb_004a115f;
}
bb_004a1140: {
    // 0x004a1140: mov ebx, dword ptr [0x51b300]
    uint32_t t6 = mem.r32(0x0051b300u);
    ctx.ebx = static_cast<uint32_t>(t6);
    goto bb_004a1146;
}
bb_004a11b8: {
    // 0x004a11b8: pop esi
    uint32_t t7 = ctx.esp;
    uint32_t t8 = mem.r32(t7);
    uint32_t t9 = static_cast<uint32_t>(t7 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    ctx.esi = static_cast<uint32_t>(t8);
    // 0x004a11b9: pop ebx
    uint32_t t10 = ctx.esp;
    uint32_t t11 = mem.r32(t10);
    uint32_t t12 = static_cast<uint32_t>(t10 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    ctx.ebx = static_cast<uint32_t>(t11);
    // 0x004a11ba: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a115f: {
    // 0x004a115f: mov ebx, dword ptr [0x51b2f4]
    uint32_t t13 = mem.r32(0x0051b2f4u);
    ctx.ebx = static_cast<uint32_t>(t13);
    // 0x004a1165: push ebp
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, ctx.ebp);
    // 0x004a1166: mov ebp, dword ptr [0x51b2b4]
    uint32_t t15 = mem.r32(0x0051b2b4u);
    ctx.ebp = static_cast<uint32_t>(t15);
    goto bb_004a116c;
}
bb_004a1146: {
    // 0x004a1146: mov eax, dword ptr [esi]
    uint32_t t16 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x004a1148: push eax
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, ctx.eax);
    // 0x004a1149: push edi
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, ctx.edi);
    // 0x004a114a: call ebx
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x004a114cu);
    call_indirect(ctx, mem, ctx.ebx);
    // 0x004a114c: cmp eax, 1
    uint32_t t20 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t20);
    // 0x004a114f: je 0x4a115a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a115a;
    goto bb_004a1151;
}
bb_004a116c: {
    // 0x004a116c: add esi, 0x18
    uint32_t t21 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000018u, t21);
    ctx.esi = static_cast<uint32_t>(t21);
    // 0x004a116f: cmp dword ptr [esi + 0x14], 0
    uint32_t t22 = static_cast<uint32_t>(ctx.esi + 0x00000014u);
    uint32_t t23 = mem.r32(t22);
    uint32_t t24 = static_cast<uint32_t>(t23 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t23, 0x00000000u, t24);
    // 0x004a1173: jne 0x4a117a
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a117a;
    goto bb_004a1175;
}
bb_004a1151: {
    // 0x004a1151: add esi, 0x18
    uint32_t t25 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000018u, t25);
    ctx.esi = static_cast<uint32_t>(t25);
    // 0x004a1154: cmp dword ptr [esi + 0x14], 0
    uint32_t t26 = static_cast<uint32_t>(ctx.esi + 0x00000014u);
    uint32_t t27 = mem.r32(t26);
    uint32_t t28 = static_cast<uint32_t>(t27 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t27, 0x00000000u, t28);
    // 0x004a1158: jne 0x4a1146
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a1146;
    goto bb_004a115a;
}
bb_004a117a: {
    // 0x004a117a: mov eax, dword ptr [esi]
    uint32_t t29 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t29);
    // 0x004a117c: push eax
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, ctx.eax);
    // 0x004a117d: push edi
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, ctx.edi);
    // 0x004a117e: call ebx
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x004a1180u);
    call_indirect(ctx, mem, ctx.ebx);
    // 0x004a1180: push eax
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, ctx.eax);
    // 0x004a1181: call ebp
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x004a1183u);
    call_indirect(ctx, mem, ctx.ebp);
    // 0x004a1183: test eax, eax
    uint32_t t35 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t35);
    // 0x004a1185: je 0x4a116c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a116c;
    goto bb_004a1187;
}
bb_004a1175: {
    // 0x004a1175: mov esi, 0x54d138
    ctx.esi = static_cast<uint32_t>(0x0054d138u);
    goto bb_004a117a;
}
bb_004a1187: {
    // 0x004a1187: mov ecx, dword ptr [esi]
    uint32_t t36 = mem.r32(ctx.esi);
    ctx.ecx = static_cast<uint32_t>(t36);
    // 0x004a1189: mov edx, dword ptr [0x74da0c]
    uint32_t t37 = mem.r32(0x0074da0cu);
    ctx.edx = static_cast<uint32_t>(t37);
    // 0x004a118f: mov eax, dword ptr [0x74da10]
    uint32_t t38 = mem.r32(0x0074da10u);
    ctx.eax = static_cast<uint32_t>(t38);
    // 0x004a1194: push ecx
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, ctx.ecx);
    // 0x004a1195: push edx
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, ctx.edx);
    // 0x004a1196: push eax
    uint32_t t41 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    mem.w32(t41, ctx.eax);
    // 0x004a1197: push edi
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, ctx.edi);
    // 0x004a1198: call dword ptr [0x51b2d8]
    uint32_t t43 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    mem.w32(t43, 0x004a119eu);
    hle_iat_call(ctx, mem, 0x0051b2d8u);
    // 0x004a119e: mov ecx, dword ptr [esi + 4]
    uint32_t t44 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t45 = mem.r32(t44);
    ctx.ecx = static_cast<uint32_t>(t45);
    // 0x004a11a1: push ecx
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, ctx.ecx);
    // 0x004a11a2: push edi
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, ctx.edi);
    // 0x004a11a3: call ebx
    uint32_t t48 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    mem.w32(t48, 0x004a11a5u);
    call_indirect(ctx, mem, ctx.ebx);
    // 0x004a11a5: mov ebp, dword ptr [0x51b2f8]
    uint32_t t49 = mem.r32(0x0051b2f8u);
    ctx.ebp = static_cast<uint32_t>(t49);
    // 0x004a11ab: push eax
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, ctx.eax);
    // 0x004a11ac: call ebp
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, 0x004a11aeu);
    call_indirect(ctx, mem, ctx.ebp);
    // 0x004a11ae: mov edx, dword ptr [esi]
    uint32_t t52 = mem.r32(ctx.esi);
    ctx.edx = static_cast<uint32_t>(t52);
    // 0x004a11b0: push edx
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, ctx.edx);
    // 0x004a11b1: push edi
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, ctx.edi);
    // 0x004a11b2: call ebx
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, 0x004a11b4u);
    call_indirect(ctx, mem, ctx.ebx);
    // 0x004a11b4: push eax
    uint32_t t56 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    mem.w32(t56, ctx.eax);
    // 0x004a11b5: call ebp
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, 0x004a11b7u);
    call_indirect(ctx, mem, ctx.ebp);
    // 0x004a11b7: pop ebp
    uint32_t t58 = ctx.esp;
    uint32_t t59 = mem.r32(t58);
    uint32_t t60 = static_cast<uint32_t>(t58 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t60);
    ctx.ebp = static_cast<uint32_t>(t59);
    goto bb_004a11b8;
}
}

// sub_004a11c0 | subsystem=Input | canonical | 25 blocks | 126 insns
void sub_004a11c0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a11c0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x004a11c2: push 0x516c88
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00516c88u);
    // 0x004a11c7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004a11cd: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x004a11ce: sub esp, 0x20
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000020u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000020u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x004a11d1: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x004a11d6: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x004a11d8: mov dword ptr [esp + 0x1c], eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t8, ctx.eax);
    // 0x004a11dc: push ebx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ebx);
    // 0x004a11dd: push ebp
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.ebp);
    // 0x004a11de: push esi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.esi);
    // 0x004a11df: push edi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.edi);
    // 0x004a11e0: mov eax, dword ptr [0x54b458]
    uint32_t t13 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x004a11e5: xor eax, esp
    uint32_t t14 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x004a11e7: push eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.eax);
    // 0x004a11e8: lea eax, [esp + 0x34]
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x004a11ec: mov dword ptr fs:[0], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t17, ctx.eax);
    // 0x004a11f2: add dword ptr [0x7b0a74], 1
    uint32_t t18 = mem.r32(0x007b0a74u);
    uint32_t t19 = static_cast<uint32_t>(t18 + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t18, 0x00000001u, t19);
    mem.w32(0x007b0a74u, t19);
    // 0x004a11f9: mov ebx, ecx
    ctx.ebx = static_cast<uint32_t>(ctx.ecx);
    // 0x004a11fb: call 0x410870
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x004a1200u);
    sub_00410870(ctx, mem);
    // 0x004a1200: mov eax, dword ptr [0x76e764]
    uint32_t t21 = mem.r32(0x0076e764u);
    ctx.eax = static_cast<uint32_t>(t21);
    // 0x004a1205: imul eax, eax, 0x164
    uint64_t t22 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.eax)) * static_cast<int64_t>(static_cast<int32_t>(0x00000164u)));
    uint32_t t23 = static_cast<uint32_t>(t22);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t22);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x004a120b: add eax, 0x74da18
    uint32_t t24 = static_cast<uint32_t>(ctx.eax + 0x0074da18u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x0074da18u, t24);
    ctx.eax = static_cast<uint32_t>(t24);
    // 0x004a1210: mov eax, dword ptr [eax]
    uint32_t t25 = mem.r32(ctx.eax);
    ctx.eax = static_cast<uint32_t>(t25);
    // 0x004a1212: xor esi, esi
    uint32_t t26 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t26);
    ctx.esi = static_cast<uint32_t>(t26);
    // 0x004a1214: cmp eax, esi
    uint32_t t27 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t27);
    // 0x004a1216: je 0x4a1338
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1338;
    goto bb_004a121c;
}
bb_004a1338: {
    // 0x004a1338: mov ecx, dword ptr [esp + 0x34]
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    uint32_t t29 = mem.r32(t28);
    ctx.ecx = static_cast<uint32_t>(t29);
    // 0x004a133c: mov dword ptr fs:[0], ecx
    uint32_t t30 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t30, ctx.ecx);
    // 0x004a1343: pop ecx
    uint32_t t31 = ctx.esp;
    uint32_t t32 = mem.r32(t31);
    uint32_t t33 = static_cast<uint32_t>(t31 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    ctx.ecx = static_cast<uint32_t>(t32);
    // 0x004a1344: pop edi
    uint32_t t34 = ctx.esp;
    uint32_t t35 = mem.r32(t34);
    uint32_t t36 = static_cast<uint32_t>(t34 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    ctx.edi = static_cast<uint32_t>(t35);
    // 0x004a1345: pop esi
    uint32_t t37 = ctx.esp;
    uint32_t t38 = mem.r32(t37);
    uint32_t t39 = static_cast<uint32_t>(t37 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    ctx.esi = static_cast<uint32_t>(t38);
    // 0x004a1346: pop ebp
    uint32_t t40 = ctx.esp;
    uint32_t t41 = mem.r32(t40);
    uint32_t t42 = static_cast<uint32_t>(t40 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    ctx.ebp = static_cast<uint32_t>(t41);
    // 0x004a1347: pop ebx
    uint32_t t43 = ctx.esp;
    uint32_t t44 = mem.r32(t43);
    uint32_t t45 = static_cast<uint32_t>(t43 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    ctx.ebx = static_cast<uint32_t>(t44);
    // 0x004a1348: mov ecx, dword ptr [esp + 0x1c]
    uint32_t t46 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t47 = mem.r32(t46);
    ctx.ecx = static_cast<uint32_t>(t47);
    // 0x004a134c: xor ecx, esp
    uint32_t t48 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t48);
    ctx.ecx = static_cast<uint32_t>(t48);
    // 0x004a134e: call 0x4e02f8
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, 0x004a1353u);
    hle_crt_004e02f8(ctx, mem);
    // 0x004a1353: add esp, 0x2c
    uint32_t t50 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000002cu, t50);
    ctx.esp = static_cast<uint32_t>(t50);
    // 0x004a1356: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a121c: {
    // 0x004a121c: add eax, -1
    uint32_t t51 = static_cast<uint32_t>(ctx.eax + 0xffffffffu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0xffffffffu, t51);
    ctx.eax = static_cast<uint32_t>(t51);
    // 0x004a121f: mov ebp, 0x10
    ctx.ebp = static_cast<uint32_t>(0x00000010u);
    // 0x004a1224: cmp eax, ebp
    uint32_t t52 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t52);
    // 0x004a1226: jb 0x4a122c
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a122c;
    goto bb_004a1228;
}
bb_004a122c: {
    // 0x004a122c: lea edi, [eax*8]
    uint32_t t53 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000003u);
    ctx.edi = static_cast<uint32_t>(t53);
    // 0x004a1233: sub edi, eax
    uint32_t t54 = static_cast<uint32_t>(ctx.edi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.eax, t54);
    ctx.edi = static_cast<uint32_t>(t54);
    // 0x004a1235: lea edi, [edi*8 + 0x5545f8]
    uint32_t t55 = recomp_detail::shl<uint32_t>(ctx.edi, 0x00000003u);
    uint32_t t56 = static_cast<uint32_t>(t55 + 0x005545f8u);
    ctx.edi = static_cast<uint32_t>(t56);
    goto bb_004a123c;
}
bb_004a1228: {
    // 0x004a1228: xor edi, edi
    uint32_t t57 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t57);
    ctx.edi = static_cast<uint32_t>(t57);
    // 0x004a122a: jmp 0x4a123c
}
bb_004a123c: {
    // 0x004a123c: push ebx
    uint32_t t58 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    mem.w32(t58, ctx.ebx);
    // 0x004a123d: call dword ptr [0x51b2b0]
    uint32_t t59 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    mem.w32(t59, 0x004a1243u);
    hle_iat_call(ctx, mem, 0x0051b2b0u);
    // 0x004a1243: test eax, eax
    uint32_t t60 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t60);
    // 0x004a1245: je 0x4a1338
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1338;
}
{
    // 0x004a124b: cmp edi, esi
    uint32_t t61 = static_cast<uint32_t>(ctx.edi - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.esi, t61);
    // 0x004a124d: je 0x4a12c8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a12c8;
    goto bb_004a124f;
}
bb_004a12c8: {
    // 0x004a12c8: push edi
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, ctx.edi);
    // 0x004a12c9: call 0x4a0f30
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, 0x004a12ceu);
    sub_004a0f30(ctx, mem);
    // 0x004a12ce: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x004a12d0: add esp, 4
    uint32_t t64 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t64);
    ctx.esp = static_cast<uint32_t>(t64);
    // 0x004a12d3: test edi, edi
    uint32_t t65 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t65);
    // 0x004a12d5: je 0x4a132e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a132e;
    goto bb_004a12d7;
}
bb_004a124f: {
    // 0x004a124f: mov dword ptr [esp + 0x2c], 0xf
    uint32_t t66 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    mem.w32(t66, 0x0000000fu);
    // 0x004a1257: mov dword ptr [esp + 0x28], esi
    uint32_t t67 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t67, ctx.esi);
    // 0x004a125b: mov byte ptr [esp + 0x18], 0
    uint32_t t68 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w8(t68, uint8_t{0x00u});
    // 0x004a1260: push edi
    uint32_t t69 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    mem.w32(t69, ctx.edi);
    // 0x004a1261: mov dword ptr [esp + 0x40], esi
    uint32_t t70 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    mem.w32(t70, ctx.esi);
    // 0x004a1265: call 0x4a0f30
    uint32_t t71 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t71);
    mem.w32(t71, 0x004a126au);
    sub_004a0f30(ctx, mem);
    // 0x004a126a: add esp, 4
    uint32_t t72 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t72);
    ctx.esp = static_cast<uint32_t>(t72);
    // 0x004a126d: cmp eax, esi
    uint32_t t73 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t73);
    // 0x004a126f: jl 0x4a1276
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004a1276;
    goto bb_004a1271;
}
bb_004a132e: {
    // 0x004a132e: mov dword ptr [0x74da14], 1
    mem.w32(0x0074da14u, 0x00000001u);
    goto bb_004a1338;
}
bb_004a12d7: {
    // 0x004a12d7: cmp dword ptr [0x74da10], 0
    uint32_t t74 = mem.r32(0x0074da10u);
    uint32_t t75 = static_cast<uint32_t>(t74 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t74, 0x00000000u, t75);
    // 0x004a12de: je 0x4a1322
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1322;
    goto bb_004a12e0;
}
bb_004a1276: {
    // 0x004a1276: xor eax, eax
    uint32_t t76 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t76);
    ctx.eax = static_cast<uint32_t>(t76);
    goto bb_004a1278;
}
bb_004a1271: {
    // 0x004a1271: cmp eax, 0x21
    uint32_t t77 = static_cast<uint32_t>(ctx.eax - 0x00000021u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000021u, t77);
    // 0x004a1274: jl 0x4a1278
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004a1278;
    goto bb_004a1276;
}
bb_004a1322: {
    // 0x004a1322: mov dword ptr [0x74da14], 0
    mem.w32(0x0074da14u, 0x00000000u);
    // 0x004a132c: jmp 0x4a1338
    goto bb_004a1338;
}
bb_004a12e0: {
    // 0x004a12e0: cmp dword ptr [0x74da14], 0
    uint32_t t78 = mem.r32(0x0074da14u);
    uint32_t t79 = static_cast<uint32_t>(t78 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t78, 0x00000000u, t79);
    // 0x004a12e7: je 0x4a1322
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1322;
    goto bb_004a12e9;
}
bb_004a1278: {
    // 0x004a1278: mov edx, dword ptr [eax*4 + 0x54d0a8]
    uint32_t t80 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000002u);
    uint32_t t81 = static_cast<uint32_t>(t80 + 0x0054d0a8u);
    uint32_t t82 = mem.r32(t81);
    ctx.edx = static_cast<uint32_t>(t82);
    // 0x004a127f: mov eax, edx
    ctx.eax = static_cast<uint32_t>(ctx.edx);
    // 0x004a1281: lea esi, [eax + 1]
    uint32_t t83 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.esi = static_cast<uint32_t>(t83);
    goto bb_004a1284;
}
bb_004a12e9: {
    // 0x004a12e9: call 0x4a10f0
    uint32_t t84 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    mem.w32(t84, 0x004a12eeu);
    sub_004a10f0(ctx, mem);
    // 0x004a12ee: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004a12f0: test esi, esi
    uint32_t t85 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t85);
    // 0x004a12f2: je 0x4a1322
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1322;
    goto bb_004a12f4;
}
bb_004a1284: {
    // 0x004a1284: mov cl, byte ptr [eax]
    uint8_t t86 = mem.r8(ctx.eax);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t86));
    // 0x004a1286: add eax, 1
    uint32_t t87 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t87);
    ctx.eax = static_cast<uint32_t>(t87);
    // 0x004a1289: test cl, cl
    uint8_t t88 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t88);
    // 0x004a128b: jne 0x4a1284
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a1284;
    goto bb_004a128d;
}
bb_004a12f4: {
    // 0x004a12f4: mov ebp, dword ptr [0x51b2f0]
    uint32_t t89 = mem.r32(0x0051b2f0u);
    ctx.ebp = static_cast<uint32_t>(t89);
    // 0x004a12fa: push 0
    uint32_t t90 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    mem.w32(t90, 0x00000000u);
    // 0x004a12fc: push 0
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, 0x00000000u);
    // 0x004a12fe: push 0x147
    uint32_t t92 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    mem.w32(t92, 0x00000147u);
    // 0x004a1303: push esi
    uint32_t t93 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    mem.w32(t93, ctx.esi);
    // 0x004a1304: push ebx
    uint32_t t94 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t94);
    mem.w32(t94, ctx.ebx);
    // 0x004a1305: call ebp
    uint32_t t95 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t95);
    mem.w32(t95, 0x004a1307u);
    call_indirect(ctx, mem, ctx.ebp);
    // 0x004a1307: cmp eax, dword ptr [0x74da10]
    uint32_t t96 = mem.r32(0x0074da10u);
    uint32_t t97 = static_cast<uint32_t>(ctx.eax - t96);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, t96, t97);
    // 0x004a130d: je 0x4a131b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a131b;
    goto bb_004a130f;
}
bb_004a128d: {
    // 0x004a128d: sub eax, esi
    uint32_t t98 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t98);
    ctx.eax = static_cast<uint32_t>(t98);
    // 0x004a128f: push eax
    uint32_t t99 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t99);
    mem.w32(t99, ctx.eax);
    // 0x004a1290: push edx
    uint32_t t100 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t100);
    mem.w32(t100, ctx.edx);
    // 0x004a1291: lea ecx, [esp + 0x1c]
    uint32_t t101 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.ecx = static_cast<uint32_t>(t101);
    // 0x004a1295: call 0x407c10
    uint32_t t102 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    mem.w32(t102, 0x004a129au);
    sub_00407c10(ctx, mem);
    // 0x004a129a: cmp dword ptr [esp + 0x2c], ebp
    uint32_t t103 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    uint32_t t104 = mem.r32(t103);
    uint32_t t105 = static_cast<uint32_t>(t104 - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t104, ctx.ebp, t105);
    // 0x004a129e: mov eax, dword ptr [esp + 0x18]
    uint32_t t106 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t107 = mem.r32(t106);
    ctx.eax = static_cast<uint32_t>(t107);
    // 0x004a12a2: jae 0x4a12a8
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_004a12a8;
    goto bb_004a12a4;
}
bb_004a131b: {
    // 0x004a131b: mov edi, ebx
    ctx.edi = static_cast<uint32_t>(ctx.ebx);
    // 0x004a131d: call 0x4a1130
    uint32_t t108 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t108);
    mem.w32(t108, 0x004a1322u);
    sub_004a1130(ctx, mem);
    goto bb_004a1322;
}
bb_004a130f: {
    // 0x004a130f: push 0
    uint32_t t109 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t109);
    mem.w32(t109, 0x00000000u);
    // 0x004a1311: push edi
    uint32_t t110 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t110);
    mem.w32(t110, ctx.edi);
    // 0x004a1312: push 0x14e
    uint32_t t111 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t111);
    mem.w32(t111, 0x0000014eu);
    // 0x004a1317: push esi
    uint32_t t112 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t112);
    mem.w32(t112, ctx.esi);
    // 0x004a1318: push ebx
    uint32_t t113 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t113);
    mem.w32(t113, ctx.ebx);
    // 0x004a1319: call ebp
    uint32_t t114 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t114);
    mem.w32(t114, 0x004a131bu);
    call_indirect(ctx, mem, ctx.ebp);
    goto bb_004a131b;
}
bb_004a12a8: {
    // 0x004a12a8: push eax
    uint32_t t115 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t115);
    mem.w32(t115, ctx.eax);
    // 0x004a12a9: push 0x3f2
    uint32_t t116 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t116);
    mem.w32(t116, 0x000003f2u);
    // 0x004a12ae: push ebx
    uint32_t t117 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t117);
    mem.w32(t117, ctx.ebx);
    // 0x004a12af: call dword ptr [0x51b2d4]
    uint32_t t118 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    mem.w32(t118, 0x004a12b5u);
    hle_iat_call(ctx, mem, 0x0051b2d4u);
    // 0x004a12b5: cmp dword ptr [esp + 0x2c], ebp
    uint32_t t119 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    uint32_t t120 = mem.r32(t119);
    uint32_t t121 = static_cast<uint32_t>(t120 - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t120, ctx.ebp, t121);
    // 0x004a12b9: jb 0x4a12c8
    if (recomp_detail::eval_cond(ctx, Cond::B)) goto bb_004a12c8;
    goto bb_004a12bb;
}
bb_004a12a4: {
    // 0x004a12a4: lea eax, [esp + 0x18]
    uint32_t t122 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.eax = static_cast<uint32_t>(t122);
    goto bb_004a12a8;
}
bb_004a12bb: {
    // 0x004a12bb: mov eax, dword ptr [esp + 0x18]
    uint32_t t123 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t124 = mem.r32(t123);
    ctx.eax = static_cast<uint32_t>(t124);
    // 0x004a12bf: push eax
    uint32_t t125 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t125);
    mem.w32(t125, ctx.eax);
    // 0x004a12c0: call 0x4e02f3
    uint32_t t126 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t126);
    mem.w32(t126, 0x004a12c5u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a12c5: add esp, 4
    uint32_t t127 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t127);
    ctx.esp = static_cast<uint32_t>(t127);
    goto bb_004a12c8;
}
}

// sub_004c8f90 | subsystem=Input | canonical | 1 blocks | 56 insns
void sub_004c8f90(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004c8f90: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x004c8f91: mov dword ptr [esi + 0x108], 2
    uint32_t t1 = static_cast<uint32_t>(ctx.esi + 0x00000108u);
    mem.w32(t1, 0x00000002u);
    // 0x004c8f9b: mov dword ptr [esi + 0x10c], 2
    uint32_t t2 = static_cast<uint32_t>(ctx.esi + 0x0000010cu);
    mem.w32(t2, 0x00000002u);
    // 0x004c8fa5: mov dword ptr [esi + 0x110], 2
    uint32_t t3 = static_cast<uint32_t>(ctx.esi + 0x00000110u);
    mem.w32(t3, 0x00000002u);
    // 0x004c8faf: lea eax, [esi + 0x118]
    uint32_t t4 = static_cast<uint32_t>(ctx.esi + 0x00000118u);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x004c8fb5: xor ecx, ecx
    uint32_t t5 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    ctx.ecx = static_cast<uint32_t>(t5);
    // 0x004c8fb7: mov dword ptr [esi + 0x114], 0x53bf2c
    uint32_t t6 = static_cast<uint32_t>(ctx.esi + 0x00000114u);
    mem.w32(t6, 0x0053bf2cu);
    // 0x004c8fc1: mov dword ptr [eax], ecx
    mem.w32(ctx.eax, ctx.ecx);
    // 0x004c8fc3: mov dword ptr [eax + 4], ecx
    uint32_t t7 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w32(t7, ctx.ecx);
    // 0x004c8fc6: push eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.eax);
    // 0x004c8fc7: mov dword ptr [eax + 8], ecx
    uint32_t t9 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    mem.w32(t9, ctx.ecx);
    // 0x004c8fca: push 0x539f88
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x00539f88u);
    // 0x004c8fcf: mov dword ptr [eax + 0xc], ecx
    uint32_t t11 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    mem.w32(t11, ctx.ecx);
    // 0x004c8fd2: call 0x49df40
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x004c8fd7u);
    sub_0049df40(ctx, mem);
    // 0x004c8fd7: push 0x56ce
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x000056ceu);
    // 0x004c8fdc: lea eax, [esi + 0x12c]
    uint32_t t14 = static_cast<uint32_t>(ctx.esi + 0x0000012cu);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x004c8fe2: push 5
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x00000005u);
    // 0x004c8fe4: xor ecx, ecx
    uint32_t t16 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    ctx.ecx = static_cast<uint32_t>(t16);
    // 0x004c8fe6: mov dword ptr [esi + 0x128], 0x53bf34
    uint32_t t17 = static_cast<uint32_t>(ctx.esi + 0x00000128u);
    mem.w32(t17, 0x0053bf34u);
    // 0x004c8ff0: push 0x539f6c
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x00539f6cu);
    // 0x004c8ff5: mov dword ptr [eax], ecx
    mem.w32(ctx.eax, ctx.ecx);
    // 0x004c8ff7: push eax
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, ctx.eax);
    // 0x004c8ff8: mov byte ptr [eax + 4], cl
    uint32_t t20 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w8(t20, recomp_detail::r8l(ctx.ecx));
    // 0x004c8ffb: call 0x4e068b
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x004c9000u);
    hle_crt_004e068b(ctx, mem);
    // 0x004c9000: push 0x56ce
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x000056ceu);
    // 0x004c9005: lea eax, [esi + 0x138]
    uint32_t t23 = static_cast<uint32_t>(ctx.esi + 0x00000138u);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x004c900b: push 5
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x00000005u);
    // 0x004c900d: xor ecx, ecx
    uint32_t t25 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t25);
    ctx.ecx = static_cast<uint32_t>(t25);
    // 0x004c900f: mov dword ptr [esi + 0x134], 0x53bf34
    uint32_t t26 = static_cast<uint32_t>(ctx.esi + 0x00000134u);
    mem.w32(t26, 0x0053bf34u);
    // 0x004c9019: push 0x539f6c
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x00539f6cu);
    // 0x004c901e: mov dword ptr [eax], ecx
    mem.w32(ctx.eax, ctx.ecx);
    // 0x004c9020: push eax
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, ctx.eax);
    // 0x004c9021: mov byte ptr [eax + 4], cl
    uint32_t t29 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w8(t29, recomp_detail::r8l(ctx.ecx));
    // 0x004c9024: call 0x4e068b
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x004c9029u);
    hle_crt_004e068b(ctx, mem);
    // 0x004c9029: lea ecx, [esi + 0x148]
    uint32_t t31 = static_cast<uint32_t>(ctx.esi + 0x00000148u);
    ctx.ecx = static_cast<uint32_t>(t31);
    // 0x004c902f: lea eax, [esi + 0x144]
    uint32_t t32 = static_cast<uint32_t>(ctx.esi + 0x00000144u);
    ctx.eax = static_cast<uint32_t>(t32);
    // 0x004c9035: push ecx
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, ctx.ecx);
    // 0x004c9036: xor ecx, ecx
    uint32_t t34 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t34);
    ctx.ecx = static_cast<uint32_t>(t34);
    // 0x004c9038: mov dword ptr [esi + 0x140], 0x53bf3c
    uint32_t t35 = static_cast<uint32_t>(ctx.esi + 0x00000140u);
    mem.w32(t35, 0x0053bf3cu);
    // 0x004c9042: mov dword ptr [eax], 2
    mem.w32(ctx.eax, 0x00000002u);
    // 0x004c9048: call 0x49d340
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, 0x004c904du);
    sub_0049d340(ctx, mem);
    // 0x004c904d: lea edx, [esi + 0x150]
    uint32_t t37 = static_cast<uint32_t>(ctx.esi + 0x00000150u);
    ctx.edx = static_cast<uint32_t>(t37);
    // 0x004c9053: add esp, 0x2c
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000002cu, t38);
    ctx.esp = static_cast<uint32_t>(t38);
    // 0x004c9056: lea eax, [esi + 0x14c]
    uint32_t t39 = static_cast<uint32_t>(ctx.esi + 0x0000014cu);
    ctx.eax = static_cast<uint32_t>(t39);
    // 0x004c905c: push edx
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, ctx.edx);
    // 0x004c905d: mov ecx, 1
    ctx.ecx = static_cast<uint32_t>(0x00000001u);
    // 0x004c9062: mov dword ptr [eax], 1
    mem.w32(ctx.eax, 0x00000001u);
    // 0x004c9068: call 0x49d340
    uint32_t t41 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    mem.w32(t41, 0x004c906du);
    sub_0049d340(ctx, mem);
    // 0x004c906d: add esp, 4
    uint32_t t42 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t42);
    ctx.esp = static_cast<uint32_t>(t42);
    // 0x004c9070: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004c9072: mov dword ptr [esi], 0
    mem.w32(ctx.esi, 0x00000000u);
    // 0x004c9078: call 0x4c90c0
    uint32_t t43 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    mem.w32(t43, 0x004c907du);
    sub_004c90c0(ctx, mem);
    // 0x004c907d: mov dword ptr [esi + 0x104], 0x29d0
    uint32_t t44 = static_cast<uint32_t>(ctx.esi + 0x00000104u);
    mem.w32(t44, 0x000029d0u);
    // 0x004c9087: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004c9089: pop ecx
    uint32_t t45 = ctx.esp;
    uint32_t t46 = mem.r32(t45);
    uint32_t t47 = static_cast<uint32_t>(t45 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    ctx.ecx = static_cast<uint32_t>(t46);
    // 0x004c908a: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004c9210 | subsystem=Input | canonical | 7 blocks | 56 insns
void sub_004c9210(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004c9210: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x004c9211: push edi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.edi);
    // 0x004c9212: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x004c9214: push 0x77c280
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x0077c280u);
    // 0x004c9219: lea esi, [edi + 0x114]
    uint32_t t3 = static_cast<uint32_t>(ctx.edi + 0x00000114u);
    ctx.esi = static_cast<uint32_t>(t3);
    // 0x004c921f: call 0x4c98d0
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x004c9224u);
    sub_004c98d0(ctx, mem);
    // 0x004c9224: mov edx, dword ptr [0x77c270]
    uint32_t t5 = mem.r32(0x0077c270u);
    ctx.edx = static_cast<uint32_t>(t5);
    // 0x004c922a: push edx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.edx);
    // 0x004c922b: lea eax, [edi + 0x12c]
    uint32_t t7 = static_cast<uint32_t>(ctx.edi + 0x0000012cu);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x004c9231: push 5
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x00000005u);
    // 0x004c9233: xor ecx, ecx
    uint32_t t9 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x004c9235: push 0x539f6c
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x00539f6cu);
    // 0x004c923a: mov dword ptr [eax], ecx
    mem.w32(ctx.eax, ctx.ecx);
    // 0x004c923c: push eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.eax);
    // 0x004c923d: mov byte ptr [eax + 4], cl
    uint32_t t12 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w8(t12, recomp_detail::r8l(ctx.ecx));
    // 0x004c9240: call 0x4e068b
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x004c9245u);
    hle_crt_004e068b(ctx, mem);
    // 0x004c9245: mov edx, dword ptr [0x77c274]
    uint32_t t14 = mem.r32(0x0077c274u);
    ctx.edx = static_cast<uint32_t>(t14);
    // 0x004c924b: push edx
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.edx);
    // 0x004c924c: lea eax, [edi + 0x138]
    uint32_t t16 = static_cast<uint32_t>(ctx.edi + 0x00000138u);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x004c9252: push 5
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x00000005u);
    // 0x004c9254: xor ecx, ecx
    uint32_t t18 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    ctx.ecx = static_cast<uint32_t>(t18);
    // 0x004c9256: push 0x539f6c
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x00539f6cu);
    // 0x004c925b: mov dword ptr [eax], ecx
    mem.w32(ctx.eax, ctx.ecx);
    // 0x004c925d: push eax
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, ctx.eax);
    // 0x004c925e: mov byte ptr [eax + 4], cl
    uint32_t t21 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w8(t21, recomp_detail::r8l(ctx.ecx));
    // 0x004c9261: call 0x4e068b
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x004c9266u);
    hle_crt_004e068b(ctx, mem);
    // 0x004c9266: mov eax, dword ptr [0x77c290]
    uint32_t t23 = mem.r32(0x0077c290u);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x004c926b: mov esi, dword ptr [0x77c294]
    uint32_t t24 = mem.r32(0x0077c294u);
    ctx.esi = static_cast<uint32_t>(t24);
    // 0x004c9271: add esp, 0x20
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000020u, t25);
    ctx.esp = static_cast<uint32_t>(t25);
    // 0x004c9274: test eax, eax
    uint32_t t26 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t26);
    // 0x004c9276: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x004c9278: jl 0x4c927f
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004c927f;
    goto bb_004c927a;
}
bb_004c927f: {
    // 0x004c927f: mov ecx, 2
    ctx.ecx = static_cast<uint32_t>(0x00000002u);
    goto bb_004c9284;
}
bb_004c927a: {
    // 0x004c927a: cmp eax, 0x12
    uint32_t t27 = static_cast<uint32_t>(ctx.eax - 0x00000012u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000012u, t27);
    // 0x004c927d: jle 0x4c9284
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_004c9284;
    goto bb_004c927f;
}
bb_004c9284: {
    // 0x004c9284: cmp esi, 1
    uint32_t t28 = static_cast<uint32_t>(ctx.esi - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00000001u, t28);
    // 0x004c9287: jl 0x4c928e
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004c928e;
    goto bb_004c9289;
}
bb_004c928e: {
    // 0x004c928e: mov esi, 1
    ctx.esi = static_cast<uint32_t>(0x00000001u);
    goto bb_004c9293;
}
bb_004c9289: {
    // 0x004c9289: cmp esi, 0x12
    uint32_t t29 = static_cast<uint32_t>(ctx.esi - 0x00000012u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00000012u, t29);
    // 0x004c928c: jle 0x4c9293
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_004c9293;
    goto bb_004c928e;
}
bb_004c9293: {
    // 0x004c9293: lea eax, [edi + 0x144]
    uint32_t t30 = static_cast<uint32_t>(ctx.edi + 0x00000144u);
    ctx.eax = static_cast<uint32_t>(t30);
    // 0x004c9299: mov dword ptr [eax], ecx
    mem.w32(ctx.eax, ctx.ecx);
    // 0x004c929b: lea ecx, [edi + 0x148]
    uint32_t t31 = static_cast<uint32_t>(ctx.edi + 0x00000148u);
    ctx.ecx = static_cast<uint32_t>(t31);
    // 0x004c92a1: push ecx
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, ctx.ecx);
    // 0x004c92a2: xor ecx, ecx
    uint32_t t33 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t33);
    ctx.ecx = static_cast<uint32_t>(t33);
    // 0x004c92a4: call 0x49d340
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x004c92a9u);
    sub_0049d340(ctx, mem);
    // 0x004c92a9: lea eax, [edi + 0x14c]
    uint32_t t35 = static_cast<uint32_t>(ctx.edi + 0x0000014cu);
    ctx.eax = static_cast<uint32_t>(t35);
    // 0x004c92af: add edi, 0x150
    uint32_t t36 = static_cast<uint32_t>(ctx.edi + 0x00000150u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000150u, t36);
    ctx.edi = static_cast<uint32_t>(t36);
    // 0x004c92b5: push edi
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, ctx.edi);
    // 0x004c92b6: mov ecx, 1
    ctx.ecx = static_cast<uint32_t>(0x00000001u);
    // 0x004c92bb: mov dword ptr [eax], esi
    mem.w32(ctx.eax, ctx.esi);
    // 0x004c92bd: call 0x49d340
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, 0x004c92c2u);
    sub_0049d340(ctx, mem);
    // 0x004c92c2: add esp, 8
    uint32_t t39 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t39);
    ctx.esp = static_cast<uint32_t>(t39);
    // 0x004c92c5: pop edi
    uint32_t t40 = ctx.esp;
    uint32_t t41 = mem.r32(t40);
    uint32_t t42 = static_cast<uint32_t>(t40 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    ctx.edi = static_cast<uint32_t>(t41);
    // 0x004c92c6: pop esi
    uint32_t t43 = ctx.esp;
    uint32_t t44 = mem.r32(t43);
    uint32_t t45 = static_cast<uint32_t>(t43 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    ctx.esi = static_cast<uint32_t>(t44);
    // 0x004c92c7: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004c97f0 | subsystem=Input | canonical | 7 blocks | 56 insns
void sub_004c97f0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004c97f0: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x004c97f1: push edi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.edi);
    // 0x004c97f2: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x004c97f4: push 0x539130
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x00539130u);
    // 0x004c97f9: lea esi, [edi + 0x114]
    uint32_t t3 = static_cast<uint32_t>(ctx.edi + 0x00000114u);
    ctx.esi = static_cast<uint32_t>(t3);
    // 0x004c97ff: call 0x4c98d0
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x004c9804u);
    sub_004c98d0(ctx, mem);
    // 0x004c9804: mov edx, dword ptr [0x77c268]
    uint32_t t5 = mem.r32(0x0077c268u);
    ctx.edx = static_cast<uint32_t>(t5);
    // 0x004c980a: push edx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.edx);
    // 0x004c980b: lea eax, [edi + 0x12c]
    uint32_t t7 = static_cast<uint32_t>(ctx.edi + 0x0000012cu);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x004c9811: push 5
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x00000005u);
    // 0x004c9813: xor ecx, ecx
    uint32_t t9 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x004c9815: push 0x539f6c
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x00539f6cu);
    // 0x004c981a: mov dword ptr [eax], ecx
    mem.w32(ctx.eax, ctx.ecx);
    // 0x004c981c: push eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.eax);
    // 0x004c981d: mov byte ptr [eax + 4], cl
    uint32_t t12 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w8(t12, recomp_detail::r8l(ctx.ecx));
    // 0x004c9820: call 0x4e068b
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x004c9825u);
    hle_crt_004e068b(ctx, mem);
    // 0x004c9825: mov edx, dword ptr [0x77c26c]
    uint32_t t14 = mem.r32(0x0077c26cu);
    ctx.edx = static_cast<uint32_t>(t14);
    // 0x004c982b: push edx
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.edx);
    // 0x004c982c: lea eax, [edi + 0x138]
    uint32_t t16 = static_cast<uint32_t>(ctx.edi + 0x00000138u);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x004c9832: push 5
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x00000005u);
    // 0x004c9834: xor ecx, ecx
    uint32_t t18 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    ctx.ecx = static_cast<uint32_t>(t18);
    // 0x004c9836: push 0x539f6c
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x00539f6cu);
    // 0x004c983b: mov dword ptr [eax], ecx
    mem.w32(ctx.eax, ctx.ecx);
    // 0x004c983d: push eax
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, ctx.eax);
    // 0x004c983e: mov byte ptr [eax + 4], cl
    uint32_t t21 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w8(t21, recomp_detail::r8l(ctx.ecx));
    // 0x004c9841: call 0x4e068b
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x004c9846u);
    hle_crt_004e068b(ctx, mem);
    // 0x004c9846: mov eax, dword ptr [0x77c290]
    uint32_t t23 = mem.r32(0x0077c290u);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x004c984b: mov esi, dword ptr [0x77c294]
    uint32_t t24 = mem.r32(0x0077c294u);
    ctx.esi = static_cast<uint32_t>(t24);
    // 0x004c9851: add esp, 0x20
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000020u, t25);
    ctx.esp = static_cast<uint32_t>(t25);
    // 0x004c9854: test eax, eax
    uint32_t t26 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t26);
    // 0x004c9856: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x004c9858: jl 0x4c985f
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004c985f;
    goto bb_004c985a;
}
bb_004c985f: {
    // 0x004c985f: mov ecx, 2
    ctx.ecx = static_cast<uint32_t>(0x00000002u);
    goto bb_004c9864;
}
bb_004c985a: {
    // 0x004c985a: cmp eax, 0x12
    uint32_t t27 = static_cast<uint32_t>(ctx.eax - 0x00000012u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000012u, t27);
    // 0x004c985d: jle 0x4c9864
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_004c9864;
    goto bb_004c985f;
}
bb_004c9864: {
    // 0x004c9864: cmp esi, 1
    uint32_t t28 = static_cast<uint32_t>(ctx.esi - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00000001u, t28);
    // 0x004c9867: jl 0x4c986e
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004c986e;
    goto bb_004c9869;
}
bb_004c986e: {
    // 0x004c986e: mov esi, 1
    ctx.esi = static_cast<uint32_t>(0x00000001u);
    goto bb_004c9873;
}
bb_004c9869: {
    // 0x004c9869: cmp esi, 0x12
    uint32_t t29 = static_cast<uint32_t>(ctx.esi - 0x00000012u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00000012u, t29);
    // 0x004c986c: jle 0x4c9873
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_004c9873;
    goto bb_004c986e;
}
bb_004c9873: {
    // 0x004c9873: lea eax, [edi + 0x144]
    uint32_t t30 = static_cast<uint32_t>(ctx.edi + 0x00000144u);
    ctx.eax = static_cast<uint32_t>(t30);
    // 0x004c9879: mov dword ptr [eax], ecx
    mem.w32(ctx.eax, ctx.ecx);
    // 0x004c987b: lea ecx, [edi + 0x148]
    uint32_t t31 = static_cast<uint32_t>(ctx.edi + 0x00000148u);
    ctx.ecx = static_cast<uint32_t>(t31);
    // 0x004c9881: push ecx
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, ctx.ecx);
    // 0x004c9882: xor ecx, ecx
    uint32_t t33 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t33);
    ctx.ecx = static_cast<uint32_t>(t33);
    // 0x004c9884: call 0x49d340
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x004c9889u);
    sub_0049d340(ctx, mem);
    // 0x004c9889: lea eax, [edi + 0x14c]
    uint32_t t35 = static_cast<uint32_t>(ctx.edi + 0x0000014cu);
    ctx.eax = static_cast<uint32_t>(t35);
    // 0x004c988f: add edi, 0x150
    uint32_t t36 = static_cast<uint32_t>(ctx.edi + 0x00000150u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000150u, t36);
    ctx.edi = static_cast<uint32_t>(t36);
    // 0x004c9895: push edi
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, ctx.edi);
    // 0x004c9896: mov ecx, 1
    ctx.ecx = static_cast<uint32_t>(0x00000001u);
    // 0x004c989b: mov dword ptr [eax], esi
    mem.w32(ctx.eax, ctx.esi);
    // 0x004c989d: call 0x49d340
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, 0x004c98a2u);
    sub_0049d340(ctx, mem);
    // 0x004c98a2: add esp, 8
    uint32_t t39 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t39);
    ctx.esp = static_cast<uint32_t>(t39);
    // 0x004c98a5: pop edi
    uint32_t t40 = ctx.esp;
    uint32_t t41 = mem.r32(t40);
    uint32_t t42 = static_cast<uint32_t>(t40 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    ctx.edi = static_cast<uint32_t>(t41);
    // 0x004c98a6: pop esi
    uint32_t t43 = ctx.esp;
    uint32_t t44 = mem.r32(t43);
    uint32_t t45 = static_cast<uint32_t>(t43 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    ctx.esi = static_cast<uint32_t>(t44);
    // 0x004c98a7: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004c98b0 | subsystem=Input | canonical | 3 blocks | 11 insns
void sub_004c98b0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004c98b0: test byte ptr [esp + 4], 1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint8_t t1 = mem.r8(t0);
    uint8_t t2 = static_cast<uint8_t>(static_cast<uint32_t>(t1) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t2);
    // 0x004c98b5: push esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.esi);
    // 0x004c98b6: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004c98b8: mov dword ptr [esi], 0x53bf2c
    mem.w32(ctx.esi, 0x0053bf2cu);
    // 0x004c98be: je 0x4c98c9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004c98c9;
    goto bb_004c98c0;
}
bb_004c98c9: {
    // 0x004c98c9: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004c98cb: pop esi
    uint32_t t4 = ctx.esp;
    uint32_t t5 = mem.r32(t4);
    uint32_t t6 = static_cast<uint32_t>(t4 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    ctx.esi = static_cast<uint32_t>(t5);
    // 0x004c98cc: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_004c98c0: {
    // 0x004c98c0: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x004c98c1: call 0x4e02f3
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x004c98c6u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004c98c6: add esp, 4
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t9);
    ctx.esp = static_cast<uint32_t>(t9);
    goto bb_004c98c9;
}
}

// sub_004c9970 | subsystem=Input | canonical | 3 blocks | 11 insns
void sub_004c9970(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004c9970: test byte ptr [esp + 4], 1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint8_t t1 = mem.r8(t0);
    uint8_t t2 = static_cast<uint8_t>(static_cast<uint32_t>(t1) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t2);
    // 0x004c9975: push esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.esi);
    // 0x004c9976: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004c9978: mov dword ptr [esi], 0x53bf34
    mem.w32(ctx.esi, 0x0053bf34u);
    // 0x004c997e: je 0x4c9989
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004c9989;
    goto bb_004c9980;
}
bb_004c9989: {
    // 0x004c9989: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004c998b: pop esi
    uint32_t t4 = ctx.esp;
    uint32_t t5 = mem.r32(t4);
    uint32_t t6 = static_cast<uint32_t>(t4 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    ctx.esi = static_cast<uint32_t>(t5);
    // 0x004c998c: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_004c9980: {
    // 0x004c9980: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x004c9981: call 0x4e02f3
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x004c9986u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004c9986: add esp, 4
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t9);
    ctx.esp = static_cast<uint32_t>(t9);
    goto bb_004c9989;
}
}

// sub_004c99c0 | subsystem=Input | canonical | 3 blocks | 11 insns
void sub_004c99c0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004c99c0: test byte ptr [esp + 4], 1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint8_t t1 = mem.r8(t0);
    uint8_t t2 = static_cast<uint8_t>(static_cast<uint32_t>(t1) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t2);
    // 0x004c99c5: push esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.esi);
    // 0x004c99c6: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004c99c8: mov dword ptr [esi], 0x53bf3c
    mem.w32(ctx.esi, 0x0053bf3cu);
    // 0x004c99ce: je 0x4c99d9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004c99d9;
    goto bb_004c99d0;
}
bb_004c99d9: {
    // 0x004c99d9: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004c99db: pop esi
    uint32_t t4 = ctx.esp;
    uint32_t t5 = mem.r32(t4);
    uint32_t t6 = static_cast<uint32_t>(t4 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    ctx.esi = static_cast<uint32_t>(t5);
    // 0x004c99dc: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_004c99d0: {
    // 0x004c99d0: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x004c99d1: call 0x4e02f3
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x004c99d6u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004c99d6: add esp, 4
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t9);
    ctx.esp = static_cast<uint32_t>(t9);
    goto bb_004c99d9;
}
}

// sub_004de5d8 | subsystem=Input | canonical | 1 blocks | 1 insns
void sub_004de5d8(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004de5d8: jmp dword ptr [0x51b000]
    hle_iat_call(ctx, mem, 0x0051b000u);
    return;
}
}

} // namespace mbaa_recomp

#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
