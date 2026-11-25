// Auto-generated C++20 shard: gen_sound.cpp (54 functions) — DO NOT EDIT

#include "recomp_funcs.h"

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

namespace mbaa_recomp {

// sub_0040c870 | subsystem=Sound | canonical | 7 blocks | 34 insns
void sub_0040c870(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040c870: cmp dword ptr [ecx], 0
    uint32_t t0 = mem.r32(ctx.ecx);
    uint32_t t1 = static_cast<uint32_t>(t0 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t0, 0x00000000u, t1);
    // 0x0040c873: push ebp
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebp);
    // 0x0040c874: mov ebp, dword ptr [esp + 0xc]
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t4 = mem.r32(t3);
    ctx.ebp = static_cast<uint32_t>(t4);
    // 0x0040c878: je 0x40c880
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040c880;
    goto bb_0040c87a;
}
bb_0040c880: {
    // 0x0040c880: mov eax, dword ptr [esp + 8]
    uint32_t t5 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t6 = mem.r32(t5);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0040c884: push edi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.edi);
    // 0x0040c885: call 0x40c670
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x0040c88au);
    sub_0040c670(ctx, mem);
    // 0x0040c88a: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x0040c88c: test edi, edi
    uint32_t t9 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    // 0x0040c88e: jne 0x40c895
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040c895;
    goto bb_0040c890;
}
bb_0040c87a: {
    // 0x0040c87a: xor eax, eax
    uint32_t t10 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0040c87c: pop ebp
    uint32_t t11 = ctx.esp;
    uint32_t t12 = mem.r32(t11);
    uint32_t t13 = static_cast<uint32_t>(t11 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    ctx.ebp = static_cast<uint32_t>(t12);
    // 0x0040c87d: ret 0xc
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 12u;
    return;
}
bb_0040c895: {
    // 0x0040c895: push esi
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, ctx.esi);
    // 0x0040c896: call 0x40cb40
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x0040c89bu);
    sub_0040cb40(ctx, mem);
    // 0x0040c89b: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0040c89d: mov eax, dword ptr [esp + 0x18]
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t17 = mem.r32(t16);
    ctx.eax = static_cast<uint32_t>(t17);
    // 0x0040c8a1: cmp eax, esi
    uint32_t t18 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t18);
    // 0x0040c8a3: jge 0x40c8a7
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0040c8a7;
    goto bb_0040c8a5;
}
bb_0040c890: {
    // 0x0040c890: pop edi
    uint32_t t19 = ctx.esp;
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t19 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    ctx.edi = static_cast<uint32_t>(t20);
    // 0x0040c891: pop ebp
    uint32_t t22 = ctx.esp;
    uint32_t t23 = mem.r32(t22);
    uint32_t t24 = static_cast<uint32_t>(t22 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    ctx.ebp = static_cast<uint32_t>(t23);
    // 0x0040c892: ret 0xc
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 12u;
    return;
}
bb_0040c8a7: {
    // 0x0040c8a7: push esi
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, ctx.esi);
    // 0x0040c8a8: push edi
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, ctx.edi);
    // 0x0040c8a9: push ebp
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, ctx.ebp);
    // 0x0040c8aa: call 0x4e0cf0
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x0040c8afu);
    hle_crt_004e0cf0(ctx, mem);
    // 0x0040c8af: add esp, 0xc
    uint32_t t29 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t29);
    ctx.esp = static_cast<uint32_t>(t29);
    // 0x0040c8b2: mov byte ptr [esi + ebp], 0
    uint32_t t30 = static_cast<uint32_t>(ctx.esi + ctx.ebp);
    mem.w8(t30, uint8_t{0x00u});
    // 0x0040c8b6: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0040c8b8: pop esi
    uint32_t t31 = ctx.esp;
    uint32_t t32 = mem.r32(t31);
    uint32_t t33 = static_cast<uint32_t>(t31 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    ctx.esi = static_cast<uint32_t>(t32);
    // 0x0040c8b9: pop edi
    uint32_t t34 = ctx.esp;
    uint32_t t35 = mem.r32(t34);
    uint32_t t36 = static_cast<uint32_t>(t34 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    ctx.edi = static_cast<uint32_t>(t35);
    // 0x0040c8ba: pop ebp
    uint32_t t37 = ctx.esp;
    uint32_t t38 = mem.r32(t37);
    uint32_t t39 = static_cast<uint32_t>(t37 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    ctx.ebp = static_cast<uint32_t>(t38);
    // 0x0040c8bb: ret 0xc
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 12u;
    return;
}
bb_0040c8a5: {
    // 0x0040c8a5: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    goto bb_0040c8a7;
}
}

// sub_0040cb40 | subsystem=Sound | canonical | 19 blocks | 54 insns
void sub_0040cb40(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040cb40: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x0040cb41: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
    // 0x0040cb42: push edi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.edi);
    // 0x0040cb43: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x0040cb45: mov ecx, 0x5351a8
    ctx.ecx = static_cast<uint32_t>(0x005351a8u);
    // 0x0040cb4a: xor eax, eax
    uint32_t t3 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t3);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0040cb4c: xor ebp, ebp
    uint32_t t4 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    ctx.ebp = static_cast<uint32_t>(t4);
    // 0x0040cb4e: lea esi, [ecx + 1]
    uint32_t t5 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    ctx.esi = static_cast<uint32_t>(t5);
}
bb_0040cb51: {
    // 0x0040cb51: mov dl, byte ptr [ecx]
    uint8_t t6 = mem.r8(ctx.ecx);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t6));
    // 0x0040cb53: add ecx, 1
    uint32_t t7 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t7);
    ctx.ecx = static_cast<uint32_t>(t7);
    // 0x0040cb56: test dl, dl
    uint8_t t8 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t8);
    // 0x0040cb58: jne 0x40cb51
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040cb51;
}
{
    // 0x0040cb5a: sub ecx, esi
    uint32_t t9 = static_cast<uint32_t>(ctx.ecx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.esi, t9);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0040cb5c: cmp byte ptr [edi], al
    uint8_t t10 = mem.r8(ctx.edi);
    uint8_t t11 = static_cast<uint8_t>(static_cast<uint32_t>(t10) - static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, t10, recomp_detail::r8l(ctx.eax), t11);
    // 0x0040cb5e: jne 0x40cb66
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040cb66;
    goto bb_0040cb60;
}
bb_0040cb66: {
    // 0x0040cb66: push ebx
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.ebx);
    goto bb_0040cb67;
}
bb_0040cb60: {
    // 0x0040cb60: pop edi
    uint32_t t13 = ctx.esp;
    uint32_t t14 = mem.r32(t13);
    uint32_t t15 = static_cast<uint32_t>(t13 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    ctx.edi = static_cast<uint32_t>(t14);
    // 0x0040cb61: pop esi
    uint32_t t16 = ctx.esp;
    uint32_t t17 = mem.r32(t16);
    uint32_t t18 = static_cast<uint32_t>(t16 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    ctx.esi = static_cast<uint32_t>(t17);
    // 0x0040cb62: xor eax, eax
    uint32_t t19 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t19);
    ctx.eax = static_cast<uint32_t>(t19);
    // 0x0040cb64: pop ebp
    uint32_t t20 = ctx.esp;
    uint32_t t21 = mem.r32(t20);
    uint32_t t22 = static_cast<uint32_t>(t20 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    ctx.ebp = static_cast<uint32_t>(t21);
    // 0x0040cb65: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040cb67: {
    // 0x0040cb67: xor edx, edx
    uint32_t t23 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t23);
    ctx.edx = static_cast<uint32_t>(t23);
    // 0x0040cb69: test ecx, ecx
    uint32_t t24 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t24);
    // 0x0040cb6b: jle 0x40cb7f
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0040cb7f;
    goto bb_0040cb6d;
}
bb_0040cb7f: {
    // 0x0040cb7f: mov dl, byte ptr [edi]
    uint8_t t25 = mem.r8(ctx.edi);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t25));
    // 0x0040cb81: test dl, dl
    uint8_t t26 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t26);
    // 0x0040cb83: je 0x40cbaa
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040cbaa;
    goto bb_0040cb85;
}
bb_0040cb6d: {
    // 0x0040cb6d: mov bl, byte ptr [edi]
    uint8_t t27 = mem.r8(ctx.edi);
    recomp_detail::w8l(ctx.ebx, static_cast<uint8_t>(t27));
    // 0x0040cb6f: nop
    goto bb_0040cb70;
}
bb_0040cbaa: {
    // 0x0040cbaa: pop ebx
    uint32_t t28 = ctx.esp;
    uint32_t t29 = mem.r32(t28);
    uint32_t t30 = static_cast<uint32_t>(t28 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    ctx.ebx = static_cast<uint32_t>(t29);
    // 0x0040cbab: pop edi
    uint32_t t31 = ctx.esp;
    uint32_t t32 = mem.r32(t31);
    uint32_t t33 = static_cast<uint32_t>(t31 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    ctx.edi = static_cast<uint32_t>(t32);
    // 0x0040cbac: pop esi
    uint32_t t34 = ctx.esp;
    uint32_t t35 = mem.r32(t34);
    uint32_t t36 = static_cast<uint32_t>(t34 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    ctx.esi = static_cast<uint32_t>(t35);
    // 0x0040cbad: pop ebp
    uint32_t t37 = ctx.esp;
    uint32_t t38 = mem.r32(t37);
    uint32_t t39 = static_cast<uint32_t>(t37 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    ctx.ebp = static_cast<uint32_t>(t38);
    // 0x0040cbae: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040cb85: {
    // 0x0040cb85: cmp dl, 0xd
    uint8_t t40 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)) - static_cast<uint32_t>(uint8_t{0x0du}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.edx), uint8_t{0x0du}, t40);
    // 0x0040cb88: je 0x40cba8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040cba8;
    goto bb_0040cb8a;
}
bb_0040cb70: {
    // 0x0040cb70: cmp bl, byte ptr [edx + 0x5351a8]
    uint32_t t41 = static_cast<uint32_t>(ctx.edx + 0x005351a8u);
    uint8_t t42 = mem.r8(t41);
    uint8_t t43 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)) - static_cast<uint32_t>(t42));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.ebx), t42, t43);
    // 0x0040cb76: je 0x40cbaa
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040cbaa;
    goto bb_0040cb78;
}
bb_0040cba8: {
    // 0x0040cba8: xor eax, eax
    uint32_t t44 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t44);
    ctx.eax = static_cast<uint32_t>(t44);
    goto bb_0040cbaa;
}
bb_0040cb8a: {
    // 0x0040cb8a: cmp dl, 0x2f
    uint8_t t45 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)) - static_cast<uint32_t>(uint8_t{0x2fu}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.edx), uint8_t{0x2fu}, t45);
    // 0x0040cb8d: jne 0x40cb94
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040cb94;
    goto bb_0040cb8f;
}
bb_0040cb78: {
    // 0x0040cb78: add edx, 1
    uint32_t t46 = static_cast<uint32_t>(ctx.edx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000001u, t46);
    ctx.edx = static_cast<uint32_t>(t46);
    // 0x0040cb7b: cmp edx, ecx
    uint32_t t47 = static_cast<uint32_t>(ctx.edx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ecx, t47);
    // 0x0040cb7d: jl 0x40cb70
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040cb70;
    goto bb_0040cb7f;
}
bb_0040cb94: {
    // 0x0040cb94: add ebp, 1
    uint32_t t48 = static_cast<uint32_t>(ctx.ebp + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebp, 0x00000001u, t48);
    ctx.ebp = static_cast<uint32_t>(t48);
    // 0x0040cb97: cmp dl, 9
    uint8_t t49 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)) - static_cast<uint32_t>(uint8_t{0x09u}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.edx), uint8_t{0x09u}, t49);
    // 0x0040cb9a: je 0x40cba3
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040cba3;
    goto bb_0040cb9c;
}
bb_0040cb8f: {
    // 0x0040cb8f: cmp byte ptr [edi + 1], dl
    uint32_t t50 = static_cast<uint32_t>(ctx.edi + 0x00000001u);
    uint8_t t51 = mem.r8(t50);
    uint8_t t52 = static_cast<uint8_t>(static_cast<uint32_t>(t51) - static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, t51, recomp_detail::r8l(ctx.edx), t52);
    // 0x0040cb92: je 0x40cbaa
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040cbaa;
    goto bb_0040cb94;
}
bb_0040cba3: {
    // 0x0040cba3: add edi, 1
    uint32_t t53 = static_cast<uint32_t>(ctx.edi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000001u, t53);
    ctx.edi = static_cast<uint32_t>(t53);
    // 0x0040cba6: jmp 0x40cb67
    goto bb_0040cb67;
}
bb_0040cb9c: {
    // 0x0040cb9c: cmp dl, 0x20
    uint8_t t54 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)) - static_cast<uint32_t>(uint8_t{0x20u}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.edx), uint8_t{0x20u}, t54);
    // 0x0040cb9f: je 0x40cba3
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040cba3;
}
{
    // 0x0040cba1: mov eax, ebp
    ctx.eax = static_cast<uint32_t>(ctx.ebp);
    goto bb_0040cba3;
}
}

// sub_0040d130 | subsystem=Sound | canonical | 7 blocks | 34 insns
void sub_0040d130(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040d130: cmp dword ptr [ecx], 0
    uint32_t t0 = mem.r32(ctx.ecx);
    uint32_t t1 = static_cast<uint32_t>(t0 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t0, 0x00000000u, t1);
    // 0x0040d133: push ebp
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebp);
    // 0x0040d134: mov ebp, dword ptr [esp + 0xc]
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t4 = mem.r32(t3);
    ctx.ebp = static_cast<uint32_t>(t4);
    // 0x0040d138: je 0x40d13e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040d13e;
    goto bb_0040d13a;
}
bb_0040d13e: {
    // 0x0040d13e: mov eax, dword ptr [esp + 8]
    uint32_t t5 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t6 = mem.r32(t5);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0040d142: push edi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.edi);
    // 0x0040d143: call 0x40cf10
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x0040d148u);
    sub_0040cf10(ctx, mem);
    // 0x0040d148: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x0040d14a: test edi, edi
    uint32_t t9 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    // 0x0040d14c: jne 0x40d151
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040d151;
    goto bb_0040d14e;
}
bb_0040d13a: {
    // 0x0040d13a: xor eax, eax
    uint32_t t10 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0040d13c: pop ebp
    uint32_t t11 = ctx.esp;
    uint32_t t12 = mem.r32(t11);
    uint32_t t13 = static_cast<uint32_t>(t11 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    ctx.ebp = static_cast<uint32_t>(t12);
    // 0x0040d13d: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040d151: {
    // 0x0040d151: push esi
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, ctx.esi);
    // 0x0040d152: call 0x40cb40
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x0040d157u);
    sub_0040cb40(ctx, mem);
    // 0x0040d157: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0040d159: mov eax, dword ptr [esp + 0x18]
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t17 = mem.r32(t16);
    ctx.eax = static_cast<uint32_t>(t17);
    // 0x0040d15d: cmp eax, esi
    uint32_t t18 = static_cast<uint32_t>(ctx.eax - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.esi, t18);
    // 0x0040d15f: jge 0x40d163
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0040d163;
    goto bb_0040d161;
}
bb_0040d14e: {
    // 0x0040d14e: pop edi
    uint32_t t19 = ctx.esp;
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t19 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    ctx.edi = static_cast<uint32_t>(t20);
    // 0x0040d14f: pop ebp
    uint32_t t22 = ctx.esp;
    uint32_t t23 = mem.r32(t22);
    uint32_t t24 = static_cast<uint32_t>(t22 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    ctx.ebp = static_cast<uint32_t>(t23);
    // 0x0040d150: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040d163: {
    // 0x0040d163: push esi
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, ctx.esi);
    // 0x0040d164: push edi
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, ctx.edi);
    // 0x0040d165: push ebp
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, ctx.ebp);
    // 0x0040d166: call 0x4e0cf0
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x0040d16bu);
    hle_crt_004e0cf0(ctx, mem);
    // 0x0040d16b: add esp, 0xc
    uint32_t t29 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t29);
    ctx.esp = static_cast<uint32_t>(t29);
    // 0x0040d16e: mov byte ptr [esi + ebp], 0
    uint32_t t30 = static_cast<uint32_t>(ctx.esi + ctx.ebp);
    mem.w8(t30, uint8_t{0x00u});
    // 0x0040d172: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0040d174: pop esi
    uint32_t t31 = ctx.esp;
    uint32_t t32 = mem.r32(t31);
    uint32_t t33 = static_cast<uint32_t>(t31 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    ctx.esi = static_cast<uint32_t>(t32);
    // 0x0040d175: pop edi
    uint32_t t34 = ctx.esp;
    uint32_t t35 = mem.r32(t34);
    uint32_t t36 = static_cast<uint32_t>(t34 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    ctx.edi = static_cast<uint32_t>(t35);
    // 0x0040d176: pop ebp
    uint32_t t37 = ctx.esp;
    uint32_t t38 = mem.r32(t37);
    uint32_t t39 = static_cast<uint32_t>(t37 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    ctx.ebp = static_cast<uint32_t>(t38);
    // 0x0040d177: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040d161: {
    // 0x0040d161: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    goto bb_0040d163;
}
}

// sub_0040e730 | subsystem=Sound | canonical | 3 blocks | 41 insns
void sub_0040e730(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040e730: sub esp, 0x2c
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x0000002cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x0000002cu, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x0040e733: mov eax, dword ptr [0x54b458]
    uint32_t t1 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x0040e738: xor eax, esp
    uint32_t t2 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x0040e73a: mov dword ptr [esp + 0x28], eax
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t3, ctx.eax);
    // 0x0040e73e: mov eax, dword ptr [esp + 0x30]
    uint32_t t4 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    uint32_t t5 = mem.r32(t4);
    ctx.eax = static_cast<uint32_t>(t5);
    // 0x0040e742: mov ecx, dword ptr [eax]
    uint32_t t6 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t6);
    // 0x0040e744: xor eax, eax
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0040e746: test ecx, ecx
    uint32_t t8 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t8);
    // 0x0040e748: je 0x40e7a7
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040e7a7;
    goto bb_0040e74a;
}
bb_0040e7a7: {
    // 0x0040e7a7: mov ecx, dword ptr [esp + 0x28]
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t10 = mem.r32(t9);
    ctx.ecx = static_cast<uint32_t>(t10);
    // 0x0040e7ab: xor ecx, esp
    uint32_t t11 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    ctx.ecx = static_cast<uint32_t>(t11);
    // 0x0040e7ad: call 0x4e02f8
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x0040e7b2u);
    hle_crt_004e02f8(ctx, mem);
    // 0x0040e7b2: add esp, 0x2c
    uint32_t t13 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000002cu, t13);
    ctx.esp = static_cast<uint32_t>(t13);
    // 0x0040e7b5: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
bb_0040e74a: {
    // 0x0040e74a: mov dword ptr [esp + 4], eax
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    mem.w32(t14, ctx.eax);
    // 0x0040e74e: mov dword ptr [esp + 8], eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    mem.w32(t15, ctx.eax);
    // 0x0040e752: mov dword ptr [esp + 0xc], eax
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t16, ctx.eax);
    // 0x0040e756: mov dword ptr [esp + 0x14], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t17, ctx.eax);
    // 0x0040e75a: mov dword ptr [esp + 0x10], eax
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t18, ctx.eax);
    // 0x0040e75e: mov dword ptr [esp + 0x18], eax
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t19, ctx.eax);
    // 0x0040e762: mov dword ptr [esp + 0x1c], eax
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t20, ctx.eax);
    // 0x0040e766: mov dword ptr [esp + 0x20], eax
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t21, ctx.eax);
    // 0x0040e76a: mov dword ptr [esp + 0x24], eax
    uint32_t t22 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t22, ctx.eax);
    // 0x0040e76e: mov eax, dword ptr [esp + 0x34]
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    uint32_t t24 = mem.r32(t23);
    ctx.eax = static_cast<uint32_t>(t24);
    // 0x0040e772: mov dword ptr [esp + 0xc], eax
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t25, ctx.eax);
    // 0x0040e776: push 0
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x00000000u);
    // 0x0040e778: lea eax, [esp + 4]
    uint32_t t27 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    ctx.eax = static_cast<uint32_t>(t27);
    // 0x0040e77c: push eax
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, ctx.eax);
    // 0x0040e77d: lea eax, [esp + 0xc]
    uint32_t t29 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    ctx.eax = static_cast<uint32_t>(t29);
    // 0x0040e781: mov dword ptr [esp + 0xc], 0x24
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t30, 0x00000024u);
    // 0x0040e789: mov dword ptr [esp + 0x10], 0x80e0
    uint32_t t31 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t31, 0x000080e0u);
    // 0x0040e791: mov dword ptr [esp + 0x1c], edx
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t32, ctx.edx);
    // 0x0040e795: mov edx, dword ptr [ecx]
    uint32_t t33 = mem.r32(ctx.ecx);
    ctx.edx = static_cast<uint32_t>(t33);
    // 0x0040e797: push eax
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, ctx.eax);
    // 0x0040e798: push ecx
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, ctx.ecx);
    // 0x0040e799: mov ecx, dword ptr [edx + 0xc]
    uint32_t t36 = static_cast<uint32_t>(ctx.edx + 0x0000000cu);
    uint32_t t37 = mem.r32(t36);
    ctx.ecx = static_cast<uint32_t>(t37);
    // 0x0040e79c: call ecx
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, 0x0040e79eu);
    call_indirect(ctx, mem, ctx.ecx);
    // 0x0040e79e: neg eax
    uint32_t t39 = static_cast<uint32_t>(0u - ctx.eax);
    recomp_detail::update_flags_neg<uint32_t>(ctx, ctx.eax, t39);
    ctx.eax = static_cast<uint32_t>(t39);
    // 0x0040e7a0: sbb eax, eax
    uint32_t t40 = recomp_detail::get_flag(ctx, kFlagCF);
    uint32_t t41 = static_cast<uint32_t>(ctx.eax - ctx.eax);
    uint32_t t42 = static_cast<uint32_t>(t41 - t40);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.eax, t42, t40);
    ctx.eax = static_cast<uint32_t>(t42);
    // 0x0040e7a2: not eax
    uint32_t t43 = static_cast<uint32_t>(~ctx.eax);
    ctx.eax = static_cast<uint32_t>(t43);
    // 0x0040e7a4: and eax, dword ptr [esp]
    uint32_t t44 = mem.r32(ctx.esp);
    uint32_t t45 = static_cast<uint32_t>(ctx.eax & t44);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t45);
    ctx.eax = static_cast<uint32_t>(t45);
    goto bb_0040e7a7;
}
}

// sub_0040e7c0 | subsystem=Sound | canonical | 3 blocks | 56 insns
void sub_0040e7c0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040e7c0: sub esp, 0x8c
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x0000008cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x0000008cu, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x0040e7c6: mov eax, dword ptr [0x54b458]
    uint32_t t1 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x0040e7cb: xor eax, esp
    uint32_t t2 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x0040e7cd: mov dword ptr [esp + 0x88], eax
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x00000088u);
    mem.w32(t3, ctx.eax);
    // 0x0040e7d4: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x0040e7d5: mov esi, dword ptr [edi]
    uint32_t t5 = mem.r32(ctx.edi);
    ctx.esi = static_cast<uint32_t>(t5);
    // 0x0040e7d7: xor eax, eax
    uint32_t t6 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t6);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0040e7d9: test esi, esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    // 0x0040e7db: je 0x40e876
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040e876;
    goto bb_0040e7e1;
}
bb_0040e876: {
    // 0x0040e876: mov ecx, dword ptr [esp + 0x8c]
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x0000008cu);
    uint32_t t9 = mem.r32(t8);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0040e87d: pop esi
    uint32_t t10 = ctx.esp;
    uint32_t t11 = mem.r32(t10);
    uint32_t t12 = static_cast<uint32_t>(t10 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    ctx.esi = static_cast<uint32_t>(t11);
    // 0x0040e87e: xor ecx, esp
    uint32_t t13 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t13);
    ctx.ecx = static_cast<uint32_t>(t13);
    // 0x0040e880: call 0x4e02f8
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x0040e885u);
    hle_crt_004e02f8(ctx, mem);
    // 0x0040e885: add esp, 0x8c
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x0000008cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000008cu, t15);
    ctx.esp = static_cast<uint32_t>(t15);
    // 0x0040e88b: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0040e7e1: {
    // 0x0040e7e1: mov dword ptr [esp + 0x78], eax
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    mem.w32(t16, ctx.eax);
    // 0x0040e7e5: push 0x60
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x00000060u);
    // 0x0040e7e7: mov dword ptr [esp + 0x6c], eax
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x0000006cu);
    mem.w32(t18, ctx.eax);
    // 0x0040e7eb: mov dword ptr [esp + 0x70], eax
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000070u);
    mem.w32(t19, ctx.eax);
    // 0x0040e7ef: mov dword ptr [esp + 0x74], eax
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x00000074u);
    mem.w32(t20, ctx.eax);
    // 0x0040e7f3: mov dword ptr [esp + 0x7c], ecx
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x0000007cu);
    mem.w32(t21, ctx.ecx);
    // 0x0040e7f7: mov dword ptr [esp + 0x78], eax
    uint32_t t22 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    mem.w32(t22, ctx.eax);
    // 0x0040e7fb: mov dword ptr [esp + 0x80], eax
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x00000080u);
    mem.w32(t23, ctx.eax);
    // 0x0040e802: mov dword ptr [esp + 0x84], eax
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x00000084u);
    mem.w32(t24, ctx.eax);
    // 0x0040e809: mov dword ptr [esp + 0x88], eax
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000088u);
    mem.w32(t25, ctx.eax);
    // 0x0040e810: mov dword ptr [esp + 0x8c], eax
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x0000008cu);
    mem.w32(t26, ctx.eax);
    // 0x0040e817: mov eax, dword ptr [esp + 0x98]
    uint32_t t27 = static_cast<uint32_t>(ctx.esp + 0x00000098u);
    uint32_t t28 = mem.r32(t27);
    ctx.eax = static_cast<uint32_t>(t28);
    // 0x0040e81e: lea ecx, [esp + 0xc]
    uint32_t t29 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    ctx.ecx = static_cast<uint32_t>(t29);
    // 0x0040e822: push 0
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x00000000u);
    // 0x0040e824: push ecx
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, ctx.ecx);
    // 0x0040e825: mov dword ptr [esp + 0x74], 0x24
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x00000074u);
    mem.w32(t32, 0x00000024u);
    // 0x0040e82d: mov dword ptr [esp + 0x78], 0x181e8
    uint32_t t33 = static_cast<uint32_t>(ctx.esp + 0x00000078u);
    mem.w32(t33, 0x000181e8u);
    // 0x0040e835: mov dword ptr [esp + 0x7c], eax
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + 0x0000007cu);
    mem.w32(t34, ctx.eax);
    // 0x0040e839: call 0x4e6340
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, 0x0040e83eu);
    hle_crt_004e6340(ctx, mem);
    // 0x0040e83e: add esp, 0xc
    uint32_t t36 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t36);
    ctx.esp = static_cast<uint32_t>(t36);
    // 0x0040e841: lea eax, [esp + 8]
    uint32_t t37 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.eax = static_cast<uint32_t>(t37);
    // 0x0040e845: mov dword ptr [esp + 8], 0x60
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    mem.w32(t38, 0x00000060u);
    // 0x0040e84d: mov edx, dword ptr [esi]
    uint32_t t39 = mem.r32(ctx.esi);
    ctx.edx = static_cast<uint32_t>(t39);
    // 0x0040e84f: mov ecx, dword ptr [edx + 0x10]
    uint32_t t40 = static_cast<uint32_t>(ctx.edx + 0x00000010u);
    uint32_t t41 = mem.r32(t40);
    ctx.ecx = static_cast<uint32_t>(t41);
    // 0x0040e852: push eax
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, ctx.eax);
    // 0x0040e853: push esi
    uint32_t t43 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    mem.w32(t43, ctx.esi);
    // 0x0040e854: call ecx
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, 0x0040e856u);
    call_indirect(ctx, mem, ctx.ecx);
    // 0x0040e856: mov eax, dword ptr [edi]
    uint32_t t45 = mem.r32(ctx.edi);
    ctx.eax = static_cast<uint32_t>(t45);
    // 0x0040e858: mov edx, dword ptr [eax]
    uint32_t t46 = mem.r32(ctx.eax);
    ctx.edx = static_cast<uint32_t>(t46);
    // 0x0040e85a: mov edx, dword ptr [edx + 0xc]
    uint32_t t47 = static_cast<uint32_t>(ctx.edx + 0x0000000cu);
    uint32_t t48 = mem.r32(t47);
    ctx.edx = static_cast<uint32_t>(t48);
    // 0x0040e85d: push 0
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, 0x00000000u);
    // 0x0040e85f: lea ecx, [esp + 8]
    uint32_t t50 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.ecx = static_cast<uint32_t>(t50);
    // 0x0040e863: push ecx
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, ctx.ecx);
    // 0x0040e864: lea ecx, [esp + 0x70]
    uint32_t t52 = static_cast<uint32_t>(ctx.esp + 0x00000070u);
    ctx.ecx = static_cast<uint32_t>(t52);
    // 0x0040e868: push ecx
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, ctx.ecx);
    // 0x0040e869: push eax
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, ctx.eax);
    // 0x0040e86a: call edx
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, 0x0040e86cu);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040e86c: neg eax
    uint32_t t56 = static_cast<uint32_t>(0u - ctx.eax);
    recomp_detail::update_flags_neg<uint32_t>(ctx, ctx.eax, t56);
    ctx.eax = static_cast<uint32_t>(t56);
    // 0x0040e86e: sbb eax, eax
    uint32_t t57 = recomp_detail::get_flag(ctx, kFlagCF);
    uint32_t t58 = static_cast<uint32_t>(ctx.eax - ctx.eax);
    uint32_t t59 = static_cast<uint32_t>(t58 - t57);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.eax, t59, t57);
    ctx.eax = static_cast<uint32_t>(t59);
    // 0x0040e870: not eax
    uint32_t t60 = static_cast<uint32_t>(~ctx.eax);
    ctx.eax = static_cast<uint32_t>(t60);
    // 0x0040e872: and eax, dword ptr [esp + 4]
    uint32_t t61 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint32_t t62 = mem.r32(t61);
    uint32_t t63 = static_cast<uint32_t>(ctx.eax & t62);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t63);
    ctx.eax = static_cast<uint32_t>(t63);
    goto bb_0040e876;
}
}

// sub_0040e890 | subsystem=Sound | canonical | 15 blocks | 128 insns
void sub_0040e890(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040e890: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0040e892: push 0x513588
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00513588u);
    // 0x0040e897: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0040e89d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0040e89e: sub esp, 0x14
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000014u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000014u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x0040e8a1: push ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebx);
    // 0x0040e8a2: push ebp
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.ebp);
    // 0x0040e8a3: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x0040e8a4: push edi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.edi);
    // 0x0040e8a5: mov eax, dword ptr [0x54b458]
    uint32_t t10 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0040e8aa: xor eax, esp
    uint32_t t11 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x0040e8ac: push eax
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.eax);
    // 0x0040e8ad: lea eax, [esp + 0x28]
    uint32_t t13 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0040e8b1: mov dword ptr fs:[0], eax
    uint32_t t14 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t14, ctx.eax);
    // 0x0040e8b7: mov esi, dword ptr [0x76e000]
    uint32_t t15 = mem.r32(0x0076e000u);
    ctx.esi = static_cast<uint32_t>(t15);
    // 0x0040e8bd: push 0x152
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x00000152u);
    // 0x0040e8c2: push 0x535268
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x00535268u);
    // 0x0040e8c7: push 4
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x00000004u);
    // 0x0040e8c9: push 0x20
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x00000020u);
    // 0x0040e8cb: call 0x4e0675
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x0040e8d0u);
    hle_crt_004e0675(ctx, mem);
    // 0x0040e8d0: xor ebp, ebp
    uint32_t t21 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t21);
    ctx.ebp = static_cast<uint32_t>(t21);
    // 0x0040e8d2: add esp, 0x10
    uint32_t t22 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t22);
    ctx.esp = static_cast<uint32_t>(t22);
    // 0x0040e8d5: cmp eax, ebp
    uint32_t t23 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t23);
    // 0x0040e8d7: je 0x40e8f4
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040e8f4;
    goto bb_0040e8d9;
}
bb_0040e8f4: {
    // 0x0040e8f4: xor ebx, ebx
    uint32_t t24 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t24);
    ctx.ebx = static_cast<uint32_t>(t24);
    goto bb_0040e8f6;
}
bb_0040e8d9: {
    // 0x0040e8d9: mov dword ptr [eax], ebp
    mem.w32(ctx.eax, ctx.ebp);
    // 0x0040e8db: mov dword ptr [eax + 4], ebp
    uint32_t t25 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w32(t25, ctx.ebp);
    // 0x0040e8de: mov dword ptr [eax + 8], ebp
    uint32_t t26 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    mem.w32(t26, ctx.ebp);
    // 0x0040e8e1: mov dword ptr [eax + 0x18], ebp
    uint32_t t27 = static_cast<uint32_t>(ctx.eax + 0x00000018u);
    mem.w32(t27, ctx.ebp);
    // 0x0040e8e4: mov dword ptr [eax + 0x1c], ebp
    uint32_t t28 = static_cast<uint32_t>(ctx.eax + 0x0000001cu);
    mem.w32(t28, ctx.ebp);
    // 0x0040e8e7: mov dword ptr [eax + 0xc], ebp
    uint32_t t29 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    mem.w32(t29, ctx.ebp);
    // 0x0040e8ea: mov dword ptr [eax + 0x10], ebp
    uint32_t t30 = static_cast<uint32_t>(ctx.eax + 0x00000010u);
    mem.w32(t30, ctx.ebp);
    // 0x0040e8ed: mov dword ptr [eax + 0x14], ebp
    uint32_t t31 = static_cast<uint32_t>(ctx.eax + 0x00000014u);
    mem.w32(t31, ctx.ebp);
    // 0x0040e8f0: mov ebx, eax
    ctx.ebx = static_cast<uint32_t>(ctx.eax);
    // 0x0040e8f2: jmp 0x40e8f6
}
bb_0040e8f6: {
    // 0x0040e8f6: mov eax, dword ptr [esp + 0x38]
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    uint32_t t33 = mem.r32(t32);
    ctx.eax = static_cast<uint32_t>(t33);
    // 0x0040e8fa: mov edi, dword ptr [eax]
    uint32_t t34 = mem.r32(ctx.eax);
    ctx.edi = static_cast<uint32_t>(t34);
    // 0x0040e8fc: cmp edi, ebp
    uint32_t t35 = static_cast<uint32_t>(ctx.edi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebp, t35);
    // 0x0040e8fe: je 0x40e943
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040e943;
    goto bb_0040e900;
}
bb_0040e943: {
    // 0x0040e943: cmp ebx, ebp
    uint32_t t36 = static_cast<uint32_t>(ctx.ebx - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.ebp, t36);
    // 0x0040e945: je 0x40e957
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040e957;
    goto bb_0040e947;
}
bb_0040e900: {
    // 0x0040e900: call 0x40fbf0
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, 0x0040e905u);
    sub_0040fbf0(ctx, mem);
    // 0x0040e905: test eax, eax
    uint32_t t38 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t38);
    // 0x0040e907: je 0x40e943
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040e943;
    goto bb_0040e909;
}
bb_0040e957: {
    // 0x0040e957: xor eax, eax
    uint32_t t39 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t39);
    ctx.eax = static_cast<uint32_t>(t39);
    goto bb_0040e959;
}
bb_0040e947: {
    // 0x0040e947: mov esi, ebx
    ctx.esi = static_cast<uint32_t>(ctx.ebx);
    // 0x0040e949: call 0x40fd90
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, 0x0040e94eu);
    sub_0040fd90(ctx, mem);
    // 0x0040e94e: push ebx
    uint32_t t41 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    mem.w32(t41, ctx.ebx);
    // 0x0040e94f: call 0x4e02f3
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, 0x0040e954u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0040e954: add esp, 4
    uint32_t t43 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t43);
    ctx.esp = static_cast<uint32_t>(t43);
    goto bb_0040e957;
}
bb_0040e909: {
    // 0x0040e909: mov edi, dword ptr [ebx + 0xc]
    uint32_t t44 = static_cast<uint32_t>(ctx.ebx + 0x0000000cu);
    uint32_t t45 = mem.r32(t44);
    ctx.edi = static_cast<uint32_t>(t45);
    // 0x0040e90c: mov edx, dword ptr [ebx + 4]
    uint32_t t46 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    uint32_t t47 = mem.r32(t46);
    ctx.edx = static_cast<uint32_t>(t47);
    // 0x0040e90f: push edi
    uint32_t t48 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    mem.w32(t48, ctx.edi);
    // 0x0040e910: push esi
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, ctx.esi);
    // 0x0040e911: call 0x40e730
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, 0x0040e916u);
    sub_0040e730(ctx, mem);
    // 0x0040e916: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0040e918: cmp esi, ebp
    uint32_t t51 = static_cast<uint32_t>(ctx.esi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebp, t51);
    // 0x0040e91a: mov dword ptr [esp + 0x38], esi
    uint32_t t52 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    mem.w32(t52, ctx.esi);
    // 0x0040e91e: je 0x40e943
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040e943;
    goto bb_0040e920;
}
bb_0040e959: {
    // 0x0040e959: mov ecx, dword ptr [esp + 0x28]
    uint32_t t53 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t54 = mem.r32(t53);
    ctx.ecx = static_cast<uint32_t>(t54);
    // 0x0040e95d: mov dword ptr fs:[0], ecx
    uint32_t t55 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t55, ctx.ecx);
    // 0x0040e964: pop ecx
    uint32_t t56 = ctx.esp;
    uint32_t t57 = mem.r32(t56);
    uint32_t t58 = static_cast<uint32_t>(t56 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    ctx.ecx = static_cast<uint32_t>(t57);
    // 0x0040e965: pop edi
    uint32_t t59 = ctx.esp;
    uint32_t t60 = mem.r32(t59);
    uint32_t t61 = static_cast<uint32_t>(t59 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    ctx.edi = static_cast<uint32_t>(t60);
    // 0x0040e966: pop esi
    uint32_t t62 = ctx.esp;
    uint32_t t63 = mem.r32(t62);
    uint32_t t64 = static_cast<uint32_t>(t62 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    ctx.esi = static_cast<uint32_t>(t63);
    // 0x0040e967: pop ebp
    uint32_t t65 = ctx.esp;
    uint32_t t66 = mem.r32(t65);
    uint32_t t67 = static_cast<uint32_t>(t65 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t67);
    ctx.ebp = static_cast<uint32_t>(t66);
    // 0x0040e968: pop ebx
    uint32_t t68 = ctx.esp;
    uint32_t t69 = mem.r32(t68);
    uint32_t t70 = static_cast<uint32_t>(t68 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    ctx.ebx = static_cast<uint32_t>(t69);
    // 0x0040e969: add esp, 0x20
    uint32_t t71 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000020u, t71);
    ctx.esp = static_cast<uint32_t>(t71);
    // 0x0040e96c: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0040e920: {
    // 0x0040e920: mov ecx, dword ptr [esi]
    uint32_t t72 = mem.r32(ctx.esi);
    ctx.ecx = static_cast<uint32_t>(t72);
    // 0x0040e922: mov ecx, dword ptr [ecx + 0x2c]
    uint32_t t73 = static_cast<uint32_t>(ctx.ecx + 0x0000002cu);
    uint32_t t74 = mem.r32(t73);
    ctx.ecx = static_cast<uint32_t>(t74);
    // 0x0040e925: push ebp
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, ctx.ebp);
    // 0x0040e926: lea edx, [esp + 0x18]
    uint32_t t76 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.edx = static_cast<uint32_t>(t76);
    // 0x0040e92a: push edx
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, ctx.edx);
    // 0x0040e92b: lea eax, [esp + 0x20]
    uint32_t t78 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    ctx.eax = static_cast<uint32_t>(t78);
    // 0x0040e92f: push eax
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, ctx.eax);
    // 0x0040e930: lea edx, [esp + 0x28]
    uint32_t t80 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.edx = static_cast<uint32_t>(t80);
    // 0x0040e934: push edx
    uint32_t t81 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    mem.w32(t81, ctx.edx);
    // 0x0040e935: lea eax, [esp + 0x30]
    uint32_t t82 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    ctx.eax = static_cast<uint32_t>(t82);
    // 0x0040e939: push eax
    uint32_t t83 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t83);
    mem.w32(t83, ctx.eax);
    // 0x0040e93a: push edi
    uint32_t t84 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    mem.w32(t84, ctx.edi);
    // 0x0040e93b: push ebp
    uint32_t t85 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t85);
    mem.w32(t85, ctx.ebp);
    // 0x0040e93c: push esi
    uint32_t t86 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t86);
    mem.w32(t86, ctx.esi);
    // 0x0040e93d: call ecx
    uint32_t t87 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t87);
    mem.w32(t87, 0x0040e93fu);
    call_indirect(ctx, mem, ctx.ecx);
    // 0x0040e93f: cmp eax, ebp
    uint32_t t88 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t88);
    // 0x0040e941: je 0x40e96f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040e96f;
    goto bb_0040e943;
}
bb_0040e96f: {
    // 0x0040e96f: mov edx, dword ptr [esp + 0x20]
    uint32_t t89 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t90 = mem.r32(t89);
    ctx.edx = static_cast<uint32_t>(t90);
    // 0x0040e973: mov eax, dword ptr [esp + 0x1c]
    uint32_t t91 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t92 = mem.r32(t91);
    ctx.eax = static_cast<uint32_t>(t92);
    // 0x0040e977: push ebp
    uint32_t t93 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    mem.w32(t93, ctx.ebp);
    // 0x0040e978: push edx
    uint32_t t94 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t94);
    mem.w32(t94, ctx.edx);
    // 0x0040e979: call 0x40fcd0
    uint32_t t95 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t95);
    mem.w32(t95, 0x0040e97eu);
    sub_0040fcd0(ctx, mem);
    // 0x0040e97e: mov eax, dword ptr [esp + 0x14]
    uint32_t t96 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t97 = mem.r32(t96);
    ctx.eax = static_cast<uint32_t>(t97);
    // 0x0040e982: cmp eax, ebp
    uint32_t t98 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t98);
    // 0x0040e984: je 0x40e995
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040e995;
    goto bb_0040e986;
}
bb_0040e995: {
    // 0x0040e995: mov ecx, dword ptr [esp + 0x1c]
    uint32_t t99 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t100 = mem.r32(t99);
    ctx.ecx = static_cast<uint32_t>(t100);
    // 0x0040e999: mov edx, dword ptr [esi]
    uint32_t t101 = mem.r32(ctx.esi);
    ctx.edx = static_cast<uint32_t>(t101);
    // 0x0040e99b: push eax
    uint32_t t102 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    mem.w32(t102, ctx.eax);
    // 0x0040e99c: mov eax, dword ptr [esp + 0x1c]
    uint32_t t103 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t104 = mem.r32(t103);
    ctx.eax = static_cast<uint32_t>(t104);
    // 0x0040e9a0: push eax
    uint32_t t105 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t105);
    mem.w32(t105, ctx.eax);
    // 0x0040e9a1: mov eax, dword ptr [esp + 0x28]
    uint32_t t106 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t107 = mem.r32(t106);
    ctx.eax = static_cast<uint32_t>(t107);
    // 0x0040e9a5: push ecx
    uint32_t t108 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t108);
    mem.w32(t108, ctx.ecx);
    // 0x0040e9a6: mov ecx, dword ptr [edx + 0x4c]
    uint32_t t109 = static_cast<uint32_t>(ctx.edx + 0x0000004cu);
    uint32_t t110 = mem.r32(t109);
    ctx.ecx = static_cast<uint32_t>(t110);
    // 0x0040e9a9: push eax
    uint32_t t111 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t111);
    mem.w32(t111, ctx.eax);
    // 0x0040e9aa: push esi
    uint32_t t112 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t112);
    mem.w32(t112, ctx.esi);
    // 0x0040e9ab: call ecx
    uint32_t t113 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t113);
    mem.w32(t113, 0x0040e9adu);
    call_indirect(ctx, mem, ctx.ecx);
    // 0x0040e9ad: mov eax, ebx
    ctx.eax = static_cast<uint32_t>(ctx.ebx);
    // 0x0040e9af: call 0x40ea00
    uint32_t t114 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t114);
    mem.w32(t114, 0x0040e9b4u);
    sub_0040ea00(ctx, mem);
    // 0x0040e9b4: push 0x16a
    uint32_t t115 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t115);
    mem.w32(t115, 0x0000016au);
    // 0x0040e9b9: push 0x535268
    uint32_t t116 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t116);
    mem.w32(t116, 0x00535268u);
    // 0x0040e9be: push 4
    uint32_t t117 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t117);
    mem.w32(t117, 0x00000004u);
    // 0x0040e9c0: push 0x34
    uint32_t t118 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    mem.w32(t118, 0x00000034u);
    // 0x0040e9c2: call 0x4e0675
    uint32_t t119 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t119);
    mem.w32(t119, 0x0040e9c7u);
    hle_crt_004e0675(ctx, mem);
    // 0x0040e9c7: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0040e9c9: add esp, 0x10
    uint32_t t120 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t120);
    ctx.esp = static_cast<uint32_t>(t120);
    // 0x0040e9cc: mov dword ptr [esp + 0x24], esi
    uint32_t t121 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t121, ctx.esi);
    // 0x0040e9d0: cmp esi, ebp
    uint32_t t122 = static_cast<uint32_t>(ctx.esi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebp, t122);
    // 0x0040e9d2: mov dword ptr [esp + 0x30], ebp
    uint32_t t123 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    mem.w32(t123, ctx.ebp);
    // 0x0040e9d6: je 0x40e957
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040e957;
    goto bb_0040e9dc;
}
bb_0040e986: {
    // 0x0040e986: mov ecx, dword ptr [esp + 0x18]
    uint32_t t124 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t125 = mem.r32(t124);
    ctx.ecx = static_cast<uint32_t>(t125);
    // 0x0040e98a: push ebp
    uint32_t t126 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t126);
    mem.w32(t126, ctx.ebp);
    // 0x0040e98b: push ecx
    uint32_t t127 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t127);
    mem.w32(t127, ctx.ecx);
    // 0x0040e98c: call 0x40fcd0
    uint32_t t128 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t128);
    mem.w32(t128, 0x0040e991u);
    sub_0040fcd0(ctx, mem);
    // 0x0040e991: mov eax, dword ptr [esp + 0x14]
    uint32_t t129 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t130 = mem.r32(t129);
    ctx.eax = static_cast<uint32_t>(t130);
    goto bb_0040e995;
}
bb_0040e9dc: {
    // 0x0040e9dc: lea edx, [esp + 0x38]
    uint32_t t131 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    ctx.edx = static_cast<uint32_t>(t131);
    // 0x0040e9e0: push edx
    uint32_t t132 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t132);
    mem.w32(t132, ctx.edx);
    // 0x0040e9e1: mov dword ptr [esi], 0x5352a8
    mem.w32(ctx.esi, 0x005352a8u);
    // 0x0040e9e7: call 0x40f1e0
    uint32_t t133 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t133);
    mem.w32(t133, 0x0040e9ecu);
    sub_0040f1e0(ctx, mem);
    // 0x0040e9ec: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0040e9ee: jmp 0x40e959
    goto bb_0040e959;
}
}

// sub_0040ea00 | subsystem=Sound | canonical | 1 blocks | 9 insns
void sub_0040ea00(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040ea00: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x0040ea01: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0040ea03: call 0x40fd90
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0040ea08u);
    sub_0040fd90(ctx, mem);
    // 0x0040ea08: push esi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.esi);
    // 0x0040ea09: call 0x4e02f3
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x0040ea0eu);
    hle_crt_004e02f3(ctx, mem);
    // 0x0040ea0e: add esp, 4
    uint32_t t4 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t4);
    ctx.esp = static_cast<uint32_t>(t4);
    // 0x0040ea11: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0040ea13: pop esi
    uint32_t t5 = ctx.esp;
    uint32_t t6 = mem.r32(t5);
    uint32_t t7 = static_cast<uint32_t>(t5 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x0040ea14: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0040ea20 | subsystem=Sound | canonical | 14 blocks | 152 insns
void sub_0040ea20(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040ea20: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0040ea22: push 0x513858
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00513858u);
    // 0x0040ea27: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0040ea2d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0040ea2e: sub esp, 0x28
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000028u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000028u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x0040ea31: push ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebx);
    // 0x0040ea32: push ebp
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.ebp);
    // 0x0040ea33: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x0040ea34: push edi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.edi);
    // 0x0040ea35: mov eax, dword ptr [0x54b458]
    uint32_t t10 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0040ea3a: xor eax, esp
    uint32_t t11 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x0040ea3c: push eax
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.eax);
    // 0x0040ea3d: lea eax, [esp + 0x3c]
    uint32_t t13 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x0040ea41: mov dword ptr fs:[0], eax
    uint32_t t14 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t14, ctx.eax);
    // 0x0040ea47: mov eax, dword ptr [esp + 0x4c]
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x0000004cu);
    uint32_t t16 = mem.r32(t15);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0040ea4b: mov ecx, dword ptr [eax]
    uint32_t t17 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t17);
    // 0x0040ea4d: mov edx, dword ptr [eax + 8]
    uint32_t t18 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    uint32_t t19 = mem.r32(t18);
    ctx.edx = static_cast<uint32_t>(t19);
    // 0x0040ea50: mov eax, dword ptr [eax + 4]
    uint32_t t20 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t21 = mem.r32(t20);
    ctx.eax = static_cast<uint32_t>(t21);
    // 0x0040ea53: mov ebx, dword ptr [0x76e000]
    uint32_t t22 = mem.r32(0x0076e000u);
    ctx.ebx = static_cast<uint32_t>(t22);
    // 0x0040ea59: push 0x1b4
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x000001b4u);
    // 0x0040ea5e: push 0x535268
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x00535268u);
    // 0x0040ea63: xor edi, edi
    uint32_t t25 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t25);
    ctx.edi = static_cast<uint32_t>(t25);
    // 0x0040ea65: push 4
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x00000004u);
    // 0x0040ea67: push 0x328
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x00000328u);
    // 0x0040ea6c: mov dword ptr [esp + 0x30], edi
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    mem.w32(t28, ctx.edi);
    // 0x0040ea70: mov dword ptr [esp + 0x44], edi
    uint32_t t29 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    mem.w32(t29, ctx.edi);
    // 0x0040ea74: mov dword ptr [esp + 0x38], ecx
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    mem.w32(t30, ctx.ecx);
    // 0x0040ea78: mov dword ptr [esp + 0x3c], edx
    uint32_t t31 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    mem.w32(t31, ctx.edx);
    // 0x0040ea7c: mov dword ptr [esp + 0x40], eax
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    mem.w32(t32, ctx.eax);
    // 0x0040ea80: call 0x4e0675
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x0040ea85u);
    hle_crt_004e0675(ctx, mem);
    // 0x0040ea85: add esp, 0x10
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t34);
    ctx.esp = static_cast<uint32_t>(t34);
    // 0x0040ea88: cmp eax, edi
    uint32_t t35 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t35);
    // 0x0040ea8a: je 0x40ebd1
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ebd1;
    goto bb_0040ea90;
}
bb_0040ebd1: {
    // 0x0040ebd1: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    goto bb_0040ebd3;
}
bb_0040ea90: {
    // 0x0040ea90: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0040ea92: call 0x416b50
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, 0x0040ea97u);
    sub_00416b50(ctx, mem);
    // 0x0040ea97: mov ebp, eax
    ctx.ebp = static_cast<uint32_t>(ctx.eax);
    // 0x0040ea99: cmp ebp, edi
    uint32_t t37 = static_cast<uint32_t>(ctx.ebp - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebp, ctx.edi, t37);
    // 0x0040ea9b: je 0x40ebd1
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ebd1;
    goto bb_0040eaa1;
}
bb_0040ebd3: {
    // 0x0040ebd3: mov ecx, dword ptr [esp + 0x3c]
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    uint32_t t39 = mem.r32(t38);
    ctx.ecx = static_cast<uint32_t>(t39);
    // 0x0040ebd7: mov dword ptr fs:[0], ecx
    uint32_t t40 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t40, ctx.ecx);
    // 0x0040ebde: pop ecx
    uint32_t t41 = ctx.esp;
    uint32_t t42 = mem.r32(t41);
    uint32_t t43 = static_cast<uint32_t>(t41 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    ctx.ecx = static_cast<uint32_t>(t42);
    // 0x0040ebdf: pop edi
    uint32_t t44 = ctx.esp;
    uint32_t t45 = mem.r32(t44);
    uint32_t t46 = static_cast<uint32_t>(t44 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    ctx.edi = static_cast<uint32_t>(t45);
    // 0x0040ebe0: pop esi
    uint32_t t47 = ctx.esp;
    uint32_t t48 = mem.r32(t47);
    uint32_t t49 = static_cast<uint32_t>(t47 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    ctx.esi = static_cast<uint32_t>(t48);
    // 0x0040ebe1: pop ebp
    uint32_t t50 = ctx.esp;
    uint32_t t51 = mem.r32(t50);
    uint32_t t52 = static_cast<uint32_t>(t50 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    ctx.ebp = static_cast<uint32_t>(t51);
    // 0x0040ebe2: pop ebx
    uint32_t t53 = ctx.esp;
    uint32_t t54 = mem.r32(t53);
    uint32_t t55 = static_cast<uint32_t>(t53 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    ctx.ebx = static_cast<uint32_t>(t54);
    // 0x0040ebe3: add esp, 0x34
    uint32_t t56 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000034u, t56);
    ctx.esp = static_cast<uint32_t>(t56);
    // 0x0040ebe6: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0040eaa1: {
    // 0x0040eaa1: lea ecx, [esp + 0x28]
    uint32_t t57 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.ecx = static_cast<uint32_t>(t57);
    // 0x0040eaa5: push ecx
    uint32_t t58 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    mem.w32(t58, ctx.ecx);
    // 0x0040eaa6: call 0x416c40
    uint32_t t59 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    mem.w32(t59, 0x0040eaabu);
    sub_00416c40(ctx, mem);
    // 0x0040eaab: test eax, eax
    uint32_t t60 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t60);
    // 0x0040eaad: je 0x40ebbb
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ebbb;
    goto bb_0040eab3;
}
bb_0040ebbb: {
    // 0x0040ebbb: mov esi, ebp
    ctx.esi = static_cast<uint32_t>(ctx.ebp);
    // 0x0040ebbd: call 0x416e30
    uint32_t t61 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    mem.w32(t61, 0x0040ebc2u);
    sub_00416e30(ctx, mem);
    // 0x0040ebc2: push ebp
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, ctx.ebp);
    // 0x0040ebc3: call 0x4e02f3
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, 0x0040ebc8u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0040ebc8: mov eax, dword ptr [esp + 0x24]
    uint32_t t64 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t65 = mem.r32(t64);
    ctx.eax = static_cast<uint32_t>(t65);
    // 0x0040ebcc: add esp, 4
    uint32_t t66 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t66);
    ctx.esp = static_cast<uint32_t>(t66);
    // 0x0040ebcf: jmp 0x40ebd3
    goto bb_0040ebd3;
}
bb_0040eab3: {
    // 0x0040eab3: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x0040eab5: call 0x416df0
    uint32_t t67 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t67);
    mem.w32(t67, 0x0040eabau);
    sub_00416df0(ctx, mem);
    // 0x0040eaba: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x0040eabc: push edi
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, ctx.edi);
    // 0x0040eabd: lea edx, [ebp + 0x2f0]
    uint32_t t69 = static_cast<uint32_t>(ctx.ebp + 0x000002f0u);
    ctx.edx = static_cast<uint32_t>(t69);
    // 0x0040eac3: push ebx
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, ctx.ebx);
    // 0x0040eac4: call 0x40e730
    uint32_t t71 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t71);
    mem.w32(t71, 0x0040eac9u);
    sub_0040e730(ctx, mem);
    // 0x0040eac9: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0040eacb: test esi, esi
    uint32_t t72 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t72);
    // 0x0040eacd: mov dword ptr [esp + 0x24], esi
    uint32_t t73 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t73, ctx.esi);
    // 0x0040ead1: je 0x40ebbb
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ebbb;
}
{
    // 0x0040ead7: push 0x1bf
    uint32_t t74 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    mem.w32(t74, 0x000001bfu);
    // 0x0040eadc: push 0x535268
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, 0x00535268u);
    // 0x0040eae1: push 4
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    mem.w32(t76, 0x00000004u);
    // 0x0040eae3: push edi
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, ctx.edi);
    // 0x0040eae4: call 0x4e0680
    uint32_t t78 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    mem.w32(t78, 0x0040eae9u);
    hle_crt_004e0680(ctx, mem);
    // 0x0040eae9: add esp, 0x10
    uint32_t t79 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t79);
    ctx.esp = static_cast<uint32_t>(t79);
    // 0x0040eaec: mov ebx, eax
    ctx.ebx = static_cast<uint32_t>(ctx.eax);
    // 0x0040eaee: push 0
    uint32_t t80 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    mem.w32(t80, 0x00000000u);
    // 0x0040eaf0: push ebx
    uint32_t t81 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    mem.w32(t81, ctx.ebx);
    // 0x0040eaf1: push ebp
    uint32_t t82 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t82);
    mem.w32(t82, ctx.ebp);
    // 0x0040eaf2: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x0040eaf4: call 0x416ea0
    uint32_t t83 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t83);
    mem.w32(t83, 0x0040eaf9u);
    sub_00416ea0(ctx, mem);
    // 0x0040eaf9: mov edx, dword ptr [esi]
    uint32_t t84 = mem.r32(ctx.esi);
    ctx.edx = static_cast<uint32_t>(t84);
    // 0x0040eafb: mov edx, dword ptr [edx + 0x2c]
    uint32_t t85 = static_cast<uint32_t>(ctx.edx + 0x0000002cu);
    uint32_t t86 = mem.r32(t85);
    ctx.edx = static_cast<uint32_t>(t86);
    // 0x0040eafe: push 0
    uint32_t t87 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t87);
    mem.w32(t87, 0x00000000u);
    // 0x0040eb00: lea eax, [esp + 0x18]
    uint32_t t88 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.eax = static_cast<uint32_t>(t88);
    // 0x0040eb04: push eax
    uint32_t t89 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t89);
    mem.w32(t89, ctx.eax);
    // 0x0040eb05: lea ecx, [esp + 0x20]
    uint32_t t90 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    ctx.ecx = static_cast<uint32_t>(t90);
    // 0x0040eb09: push ecx
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, ctx.ecx);
    // 0x0040eb0a: lea eax, [esp + 0x58]
    uint32_t t92 = static_cast<uint32_t>(ctx.esp + 0x00000058u);
    ctx.eax = static_cast<uint32_t>(t92);
    // 0x0040eb0e: push eax
    uint32_t t93 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    mem.w32(t93, ctx.eax);
    // 0x0040eb0f: lea ecx, [esp + 0x2c]
    uint32_t t94 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    ctx.ecx = static_cast<uint32_t>(t94);
    // 0x0040eb13: push ecx
    uint32_t t95 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t95);
    mem.w32(t95, ctx.ecx);
    // 0x0040eb14: push edi
    uint32_t t96 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    mem.w32(t96, ctx.edi);
    // 0x0040eb15: push 0
    uint32_t t97 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t97);
    mem.w32(t97, 0x00000000u);
    // 0x0040eb17: push esi
    uint32_t t98 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t98);
    mem.w32(t98, ctx.esi);
    // 0x0040eb18: call edx
    uint32_t t99 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t99);
    mem.w32(t99, 0x0040eb1au);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040eb1a: mov eax, dword ptr [esp + 0x4c]
    uint32_t t100 = static_cast<uint32_t>(ctx.esp + 0x0000004cu);
    uint32_t t101 = mem.r32(t100);
    ctx.eax = static_cast<uint32_t>(t101);
    // 0x0040eb1e: mov ecx, dword ptr [esp + 0x1c]
    uint32_t t102 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t103 = mem.r32(t102);
    ctx.ecx = static_cast<uint32_t>(t103);
    // 0x0040eb22: push eax
    uint32_t t104 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t104);
    mem.w32(t104, ctx.eax);
    // 0x0040eb23: push ebx
    uint32_t t105 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t105);
    mem.w32(t105, ctx.ebx);
    // 0x0040eb24: push ecx
    uint32_t t106 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t106);
    mem.w32(t106, ctx.ecx);
    // 0x0040eb25: call 0x4e63c0
    uint32_t t107 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t107);
    mem.w32(t107, 0x0040eb2au);
    hle_crt_004e63c0(ctx, mem);
    // 0x0040eb2a: mov eax, dword ptr [esp + 0x20]
    uint32_t t108 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t109 = mem.r32(t108);
    ctx.eax = static_cast<uint32_t>(t109);
    // 0x0040eb2e: add esp, 0xc
    uint32_t t110 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t110);
    ctx.esp = static_cast<uint32_t>(t110);
    // 0x0040eb31: test eax, eax
    uint32_t t111 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t111);
    // 0x0040eb33: je 0x40eb4e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040eb4e;
    goto bb_0040eb35;
}
bb_0040eb4e: {
    // 0x0040eb4e: mov edx, dword ptr [esp + 0x18]
    uint32_t t112 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t113 = mem.r32(t112);
    ctx.edx = static_cast<uint32_t>(t113);
    // 0x0040eb52: mov ecx, dword ptr [esi]
    uint32_t t114 = mem.r32(ctx.esi);
    ctx.ecx = static_cast<uint32_t>(t114);
    // 0x0040eb54: push eax
    uint32_t t115 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t115);
    mem.w32(t115, ctx.eax);
    // 0x0040eb55: mov eax, dword ptr [esp + 0x50]
    uint32_t t116 = static_cast<uint32_t>(ctx.esp + 0x00000050u);
    uint32_t t117 = mem.r32(t116);
    ctx.eax = static_cast<uint32_t>(t117);
    // 0x0040eb59: push edx
    uint32_t t118 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    mem.w32(t118, ctx.edx);
    // 0x0040eb5a: mov edx, dword ptr [esp + 0x24]
    uint32_t t119 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t120 = mem.r32(t119);
    ctx.edx = static_cast<uint32_t>(t120);
    // 0x0040eb5e: push eax
    uint32_t t121 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t121);
    mem.w32(t121, ctx.eax);
    // 0x0040eb5f: mov eax, dword ptr [ecx + 0x4c]
    uint32_t t122 = static_cast<uint32_t>(ctx.ecx + 0x0000004cu);
    uint32_t t123 = mem.r32(t122);
    ctx.eax = static_cast<uint32_t>(t123);
    // 0x0040eb62: push edx
    uint32_t t124 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t124);
    mem.w32(t124, ctx.edx);
    // 0x0040eb63: push esi
    uint32_t t125 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t125);
    mem.w32(t125, ctx.esi);
    // 0x0040eb64: call eax
    uint32_t t126 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t126);
    mem.w32(t126, 0x0040eb66u);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0040eb66: push 0x1cc
    uint32_t t127 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t127);
    mem.w32(t127, 0x000001ccu);
    // 0x0040eb6b: push 0x535268
    uint32_t t128 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t128);
    mem.w32(t128, 0x00535268u);
    // 0x0040eb70: push 4
    uint32_t t129 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t129);
    mem.w32(t129, 0x00000004u);
    // 0x0040eb72: push 0x34
    uint32_t t130 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t130);
    mem.w32(t130, 0x00000034u);
    // 0x0040eb74: call 0x4e0675
    uint32_t t131 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t131);
    mem.w32(t131, 0x0040eb79u);
    hle_crt_004e0675(ctx, mem);
    // 0x0040eb79: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0040eb7b: add esp, 0x10
    uint32_t t132 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t132);
    ctx.esp = static_cast<uint32_t>(t132);
    // 0x0040eb7e: mov dword ptr [esp + 0x20], esi
    uint32_t t133 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t133, ctx.esi);
    // 0x0040eb82: test esi, esi
    uint32_t t134 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t134);
    // 0x0040eb84: mov dword ptr [esp + 0x44], 0
    uint32_t t135 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    mem.w32(t135, 0x00000000u);
    // 0x0040eb8c: je 0x40eba0
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040eba0;
    goto bb_0040eb8e;
}
bb_0040eb35: {
    // 0x0040eb35: mov edx, dword ptr [esp + 0x4c]
    uint32_t t136 = static_cast<uint32_t>(ctx.esp + 0x0000004cu);
    uint32_t t137 = mem.r32(t136);
    ctx.edx = static_cast<uint32_t>(t137);
    // 0x0040eb39: push eax
    uint32_t t138 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t138);
    mem.w32(t138, ctx.eax);
    // 0x0040eb3a: mov eax, dword ptr [esp + 0x1c]
    uint32_t t139 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t140 = mem.r32(t139);
    ctx.eax = static_cast<uint32_t>(t140);
    // 0x0040eb3e: add edx, ebx
    uint32_t t141 = static_cast<uint32_t>(ctx.edx + ctx.ebx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, ctx.ebx, t141);
    ctx.edx = static_cast<uint32_t>(t141);
    // 0x0040eb40: push edx
    uint32_t t142 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t142);
    mem.w32(t142, ctx.edx);
    // 0x0040eb41: push eax
    uint32_t t143 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t143);
    mem.w32(t143, ctx.eax);
    // 0x0040eb42: call 0x4e63c0
    uint32_t t144 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t144);
    mem.w32(t144, 0x0040eb47u);
    hle_crt_004e63c0(ctx, mem);
    // 0x0040eb47: mov eax, dword ptr [esp + 0x20]
    uint32_t t145 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t146 = mem.r32(t145);
    ctx.eax = static_cast<uint32_t>(t146);
    // 0x0040eb4b: add esp, 0xc
    uint32_t t147 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t147);
    ctx.esp = static_cast<uint32_t>(t147);
    goto bb_0040eb4e;
}
bb_0040eba0: {
    // 0x0040eba0: xor esi, esi
    uint32_t t148 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t148);
    ctx.esi = static_cast<uint32_t>(t148);
    goto bb_0040eba2;
}
bb_0040eb8e: {
    // 0x0040eb8e: lea ecx, [esp + 0x24]
    uint32_t t149 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    ctx.ecx = static_cast<uint32_t>(t149);
    // 0x0040eb92: push ecx
    uint32_t t150 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t150);
    mem.w32(t150, ctx.ecx);
    // 0x0040eb93: mov dword ptr [esi], 0x5352a8
    mem.w32(ctx.esi, 0x005352a8u);
    // 0x0040eb99: call 0x40f1e0
    uint32_t t151 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t151);
    mem.w32(t151, 0x0040eb9eu);
    sub_0040f1e0(ctx, mem);
    // 0x0040eb9e: jmp 0x40eba2
}
bb_0040eba2: {
    // 0x0040eba2: test ebx, ebx
    uint32_t t152 = static_cast<uint32_t>(ctx.ebx & ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t152);
    // 0x0040eba4: mov dword ptr [esp + 0x44], 0xffffffff
    uint32_t t153 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    mem.w32(t153, 0xffffffffu);
    // 0x0040ebac: mov dword ptr [esp + 0x20], esi
    uint32_t t154 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t154, ctx.esi);
    // 0x0040ebb0: je 0x40ebbb
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ebbb;
}
{
    // 0x0040ebb2: push ebx
    uint32_t t155 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t155);
    mem.w32(t155, ctx.ebx);
    // 0x0040ebb3: call 0x4e0307
    uint32_t t156 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t156);
    mem.w32(t156, 0x0040ebb8u);
    hle_crt_004e0307(ctx, mem);
    // 0x0040ebb8: add esp, 4
    uint32_t t157 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t157);
    ctx.esp = static_cast<uint32_t>(t157);
    goto bb_0040ebbb;
}
}

// sub_0040ebf0 | subsystem=Sound | canonical | 12 blocks | 110 insns
void sub_0040ebf0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040ebf0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0040ebf2: push 0x514938
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00514938u);
    // 0x0040ebf7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0040ebfd: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0040ebfe: sub esp, 0x3c
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x0000003cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x0000003cu, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x0040ec01: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0040ec06: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0040ec08: mov dword ptr [esp + 0x38], eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    mem.w32(t8, ctx.eax);
    // 0x0040ec0c: push esi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.esi);
    // 0x0040ec0d: push edi
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.edi);
    // 0x0040ec0e: mov eax, dword ptr [0x54b458]
    uint32_t t11 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x0040ec13: xor eax, esp
    uint32_t t12 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t12);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0040ec15: push eax
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, ctx.eax);
    // 0x0040ec16: lea eax, [esp + 0x48]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x0040ec1a: mov dword ptr fs:[0], eax
    uint32_t t15 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t15, ctx.eax);
    // 0x0040ec20: xor eax, eax
    uint32_t t16 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0040ec22: mov edx, dword ptr [ebx + 0xc]
    uint32_t t17 = static_cast<uint32_t>(ctx.ebx + 0x0000000cu);
    uint32_t t18 = mem.r32(t17);
    ctx.edx = static_cast<uint32_t>(t18);
    // 0x0040ec25: mov dword ptr [esp + 0x1c], eax
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t19, ctx.eax);
    // 0x0040ec29: mov dword ptr [esp + 0x20], eax
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t20, ctx.eax);
    // 0x0040ec2d: mov dword ptr [esp + 0x24], eax
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t21, ctx.eax);
    // 0x0040ec31: mov dword ptr [esp + 0x28], eax
    uint32_t t22 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t22, ctx.eax);
    // 0x0040ec35: mov dword ptr [esp + 0x2c], eax
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    mem.w32(t23, ctx.eax);
    // 0x0040ec39: mov dword ptr [esp + 0x30], eax
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    mem.w32(t24, ctx.eax);
    // 0x0040ec3d: mov dword ptr [esp + 0x34], eax
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    mem.w32(t25, ctx.eax);
    // 0x0040ec41: mov dword ptr [esp + 0x38], eax
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    mem.w32(t26, ctx.eax);
    // 0x0040ec45: mov dword ptr [esp + 0x3c], eax
    uint32_t t27 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    mem.w32(t27, ctx.eax);
    // 0x0040ec49: mov dword ptr [esp + 0x40], eax
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    mem.w32(t28, ctx.eax);
    // 0x0040ec4d: mov eax, dword ptr [ebx + 4]
    uint32_t t29 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    uint32_t t30 = mem.r32(t29);
    ctx.eax = static_cast<uint32_t>(t30);
    // 0x0040ec50: mov edi, ecx
    ctx.edi = static_cast<uint32_t>(ctx.ecx);
    // 0x0040ec52: mov ecx, dword ptr [eax]
    uint32_t t31 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t31);
    // 0x0040ec54: mov dword ptr [esp + 0x1c], ecx
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t32, ctx.ecx);
    // 0x0040ec58: mov ecx, dword ptr [eax + 4]
    uint32_t t33 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t34 = mem.r32(t33);
    ctx.ecx = static_cast<uint32_t>(t34);
    // 0x0040ec5b: mov dword ptr [esp + 0x20], ecx
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t35, ctx.ecx);
    // 0x0040ec5f: mov ecx, dword ptr [eax + 8]
    uint32_t t36 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    uint32_t t37 = mem.r32(t36);
    ctx.ecx = static_cast<uint32_t>(t37);
    // 0x0040ec62: mov dword ptr [esp + 0x24], ecx
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t38, ctx.ecx);
    // 0x0040ec66: mov esi, dword ptr [eax + 0xc]
    uint32_t t39 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    uint32_t t40 = mem.r32(t39);
    ctx.esi = static_cast<uint32_t>(t40);
    // 0x0040ec69: mov dword ptr [esp + 0x28], esi
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t41, ctx.esi);
    // 0x0040ec6d: movzx eax, word ptr [eax + 0x10]
    uint32_t t42 = static_cast<uint32_t>(ctx.eax + 0x00000010u);
    uint16_t t43 = mem.r16(t42);
    uint32_t t44 = static_cast<uint32_t>(static_cast<uint16_t>(t43));
    ctx.eax = static_cast<uint32_t>(t44);
    // 0x0040ec71: mov word ptr [esp + 0x2c], ax
    uint32_t t45 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    mem.w16(t45, recomp_detail::r16(ctx.eax));
    // 0x0040ec76: mov ax, word ptr [esp + 0x2a]
    uint32_t t46 = static_cast<uint32_t>(ctx.esp + 0x0000002au);
    uint16_t t47 = mem.r16(t46);
    recomp_detail::w16(ctx.eax, static_cast<uint16_t>(t47));
    // 0x0040ec7b: cmp ax, 8
    uint16_t t48 = static_cast<uint16_t>(static_cast<uint32_t>(recomp_detail::r16(ctx.eax)) - static_cast<uint32_t>(uint16_t{0x0008u}));
    recomp_detail::update_flags_sub<uint16_t>(ctx, recomp_detail::r16(ctx.eax), uint16_t{0x0008u}, t48);
    // 0x0040ec7f: je 0x40ecb9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ecb9;
    goto bb_0040ec81;
}
bb_0040ecb9: {
    // 0x0040ecb9: test ecx, ecx
    uint32_t t49 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t49);
    // 0x0040ecbb: mov dword ptr [esp + 0x14], ecx
    uint32_t t50 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t50, ctx.ecx);
    // 0x0040ecbf: fild dword ptr [esp + 0x14]
    uint32_t t51 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    double t52 = static_cast<double>(static_cast<int32_t>(mem.r32(t51)));
    ctx.fpu_push(t52);
    // 0x0040ecc3: jge 0x40eccb
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_0040eccb;
    goto bb_0040ecc5;
}
bb_0040ec81: {
    // 0x0040ec81: cmp ax, 0x10
    uint16_t t53 = static_cast<uint16_t>(static_cast<uint32_t>(recomp_detail::r16(ctx.eax)) - static_cast<uint32_t>(uint16_t{0x0010u}));
    recomp_detail::update_flags_sub<uint16_t>(ctx, recomp_detail::r16(ctx.eax), uint16_t{0x0010u}, t53);
    // 0x0040ec85: je 0x40ecb9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ecb9;
    goto bb_0040ec87;
}
bb_0040eccb: {
    // 0x0040eccb: fnstcw word ptr [esp + 0x10]
    uint32_t t54 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w16(t54, ctx.fpu_cw);
    // 0x0040eccf: movzx eax, word ptr [esp + 0x10]
    uint32_t t55 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint16_t t56 = mem.r16(t55);
    uint32_t t57 = static_cast<uint32_t>(static_cast<uint16_t>(t56));
    ctx.eax = static_cast<uint32_t>(t57);
    // 0x0040ecd4: fadd st(0), st(0)
    double t58 = ctx.fpu_st(0);
    double t59 = ctx.fpu_st(0);
    double t60 = (t58 + t59);
    ctx.fpu_st(0) = t60;
    // 0x0040ecd6: or eax, 0xc00
    uint32_t t61 = static_cast<uint32_t>(ctx.eax | 0x00000c00u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t61);
    ctx.eax = static_cast<uint32_t>(t61);
    // 0x0040ecdb: mov dword ptr [esp + 0x14], eax
    uint32_t t62 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t62, ctx.eax);
    // 0x0040ecdf: fmul qword ptr [0x53da08]
    double t63 = ctx.fpu_st(0);
    double t64 = mem.rf64(0x0053da08u);
    double t65 = (t63 * t64);
    ctx.fpu_st(0) = t65;
    // 0x0040ece5: fldcw word ptr [esp + 0x14]
    uint32_t t66 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint16_t t67 = mem.r16(t66);
    ctx.fpu_cw = static_cast<uint16_t>(t67);
    // 0x0040ece9: fistp qword ptr [esp + 0x14]
    uint32_t t68 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    double t69 = ctx.fpu_st(0);
    recomp_detail::fpu_store_int<uint64_t>(ctx, mem, t68, t69);
    ctx.fpu_pop();
    // 0x0040eced: mov ecx, dword ptr [esp + 0x14]
    uint32_t t70 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t71 = mem.r32(t70);
    ctx.ecx = static_cast<uint32_t>(t71);
    // 0x0040ecf1: cmp ecx, edx
    uint32_t t72 = static_cast<uint32_t>(ctx.ecx - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.edx, t72);
    // 0x0040ecf3: fldcw word ptr [esp + 0x10]
    uint32_t t73 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint16_t t74 = mem.r16(t73);
    ctx.fpu_cw = static_cast<uint16_t>(t74);
    // 0x0040ecf7: jbe 0x40ecfb
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0040ecfb;
    goto bb_0040ecf9;
}
bb_0040ecc5: {
    // 0x0040ecc5: fadd dword ptr [0x53d610]
    double t75 = ctx.fpu_st(0);
    double t76 = static_cast<double>(mem.rf32(0x0053d610u));
    double t77 = (t75 + t76);
    ctx.fpu_st(0) = t77;
    goto bb_0040eccb;
}
bb_0040ec87: {
    // 0x0040ec87: mov eax, dword ptr [0x5352bc]
    uint32_t t78 = mem.r32(0x005352bcu);
    ctx.eax = static_cast<uint32_t>(t78);
    // 0x0040ec8c: mov dword ptr [esp + 0x34], eax
    uint32_t t79 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    mem.w32(t79, ctx.eax);
    // 0x0040ec90: mov eax, dword ptr [0x5352c0]
    uint32_t t80 = mem.r32(0x005352c0u);
    ctx.eax = static_cast<uint32_t>(t80);
    // 0x0040ec95: mov dword ptr [esp + 0x38], eax
    uint32_t t81 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    mem.w32(t81, ctx.eax);
    // 0x0040ec99: mov eax, dword ptr [0x5352c4]
    uint32_t t82 = mem.r32(0x005352c4u);
    ctx.eax = static_cast<uint32_t>(t82);
    // 0x0040ec9e: mov dword ptr [esp + 0x3c], eax
    uint32_t t83 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    mem.w32(t83, ctx.eax);
    // 0x0040eca2: mov eax, dword ptr [0x5352c8]
    uint32_t t84 = mem.r32(0x005352c8u);
    ctx.eax = static_cast<uint32_t>(t84);
    // 0x0040eca7: mov word ptr [esp + 0x1c], 0xfffe
    uint32_t t85 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w16(t85, uint16_t{0xfffeu});
    // 0x0040ecae: mov word ptr [esp + 0x2c], 0x28
    uint32_t t86 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    mem.w16(t86, uint16_t{0x0028u});
    // 0x0040ecb5: mov dword ptr [esp + 0x40], eax
    uint32_t t87 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    mem.w32(t87, ctx.eax);
    goto bb_0040ecb9;
}
bb_0040ecfb: {
    // 0x0040ecfb: mov eax, 0xaaaaaaab
    ctx.eax = static_cast<uint32_t>(0xaaaaaaabu);
    // 0x0040ed00: mul ecx
    uint64_t t88 = (static_cast<uint64_t>(ctx.eax) * static_cast<uint64_t>(ctx.ecx));
    uint32_t t89 = static_cast<uint32_t>(t88);
    uint32_t t90 = static_cast<uint32_t>(t88 >> 32);
    ctx.eax = static_cast<uint32_t>(t89);
    ctx.edx = static_cast<uint32_t>(t90);
    recomp_detail::update_flags_mul<uint32_t>(ctx, t88);
    // 0x0040ed02: mov esi, edx
    ctx.esi = static_cast<uint32_t>(ctx.edx);
    // 0x0040ed04: push ecx
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, ctx.ecx);
    // 0x0040ed05: lea ecx, [esp + 0x20]
    uint32_t t92 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    ctx.ecx = static_cast<uint32_t>(t92);
    // 0x0040ed09: shr esi, 1
    uint32_t t93 = static_cast<uint32_t>(0x00000001u & 0x0000001fu);
    uint32_t t94 = recomp_detail::shr<uint32_t>(ctx.esi, t93);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.esi, t93, t94);
    ctx.esi = static_cast<uint32_t>(t94);
    // 0x0040ed0b: call 0x40e7c0
    uint32_t t95 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t95);
    mem.w32(t95, 0x0040ed10u);
    sub_0040e7c0(ctx, mem);
    // 0x0040ed10: test eax, eax
    uint32_t t96 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t96);
    // 0x0040ed12: mov dword ptr [esp + 0x14], eax
    uint32_t t97 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t97, ctx.eax);
    // 0x0040ed16: je 0x40ed50
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ed50;
    goto bb_0040ed18;
}
bb_0040ecf9: {
    // 0x0040ecf9: mov ecx, edx
    ctx.ecx = static_cast<uint32_t>(ctx.edx);
    goto bb_0040ecfb;
}
bb_0040ed50: {
    // 0x0040ed50: xor eax, eax
    uint32_t t98 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t98);
    ctx.eax = static_cast<uint32_t>(t98);
    goto bb_0040ed52;
}
bb_0040ed18: {
    // 0x0040ed18: push 0x20c
    uint32_t t99 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t99);
    mem.w32(t99, 0x0000020cu);
    // 0x0040ed1d: push 0x535268
    uint32_t t100 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t100);
    mem.w32(t100, 0x00535268u);
    // 0x0040ed22: push 4
    uint32_t t101 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t101);
    mem.w32(t101, 0x00000004u);
    // 0x0040ed24: push 0x98
    uint32_t t102 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    mem.w32(t102, 0x00000098u);
    // 0x0040ed29: call 0x4e0675
    uint32_t t103 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    mem.w32(t103, 0x0040ed2eu);
    hle_crt_004e0675(ctx, mem);
    // 0x0040ed2e: add esp, 0x10
    uint32_t t104 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t104);
    ctx.esp = static_cast<uint32_t>(t104);
    // 0x0040ed31: mov dword ptr [esp + 0x10], eax
    uint32_t t105 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t105, ctx.eax);
    // 0x0040ed35: test eax, eax
    uint32_t t106 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t106);
    // 0x0040ed37: mov dword ptr [esp + 0x50], 0
    uint32_t t107 = static_cast<uint32_t>(ctx.esp + 0x00000050u);
    mem.w32(t107, 0x00000000u);
    // 0x0040ed3f: je 0x40ed50
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ed50;
    goto bb_0040ed41;
}
bb_0040ed52: {
    // 0x0040ed52: mov ecx, dword ptr [esp + 0x48]
    uint32_t t108 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    uint32_t t109 = mem.r32(t108);
    ctx.ecx = static_cast<uint32_t>(t109);
    // 0x0040ed56: mov dword ptr fs:[0], ecx
    uint32_t t110 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t110, ctx.ecx);
    // 0x0040ed5d: pop ecx
    uint32_t t111 = ctx.esp;
    uint32_t t112 = mem.r32(t111);
    uint32_t t113 = static_cast<uint32_t>(t111 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t113);
    ctx.ecx = static_cast<uint32_t>(t112);
    // 0x0040ed5e: pop edi
    uint32_t t114 = ctx.esp;
    uint32_t t115 = mem.r32(t114);
    uint32_t t116 = static_cast<uint32_t>(t114 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t116);
    ctx.edi = static_cast<uint32_t>(t115);
    // 0x0040ed5f: pop esi
    uint32_t t117 = ctx.esp;
    uint32_t t118 = mem.r32(t117);
    uint32_t t119 = static_cast<uint32_t>(t117 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t119);
    ctx.esi = static_cast<uint32_t>(t118);
    // 0x0040ed60: mov ecx, dword ptr [esp + 0x38]
    uint32_t t120 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    uint32_t t121 = mem.r32(t120);
    ctx.ecx = static_cast<uint32_t>(t121);
    // 0x0040ed64: xor ecx, esp
    uint32_t t122 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t122);
    ctx.ecx = static_cast<uint32_t>(t122);
    // 0x0040ed66: call 0x4e02f8
    uint32_t t123 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t123);
    mem.w32(t123, 0x0040ed6bu);
    hle_crt_004e02f8(ctx, mem);
    // 0x0040ed6b: add esp, 0x48
    uint32_t t124 = static_cast<uint32_t>(ctx.esp + 0x00000048u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000048u, t124);
    ctx.esp = static_cast<uint32_t>(t124);
    // 0x0040ed6e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040ed41: {
    // 0x0040ed41: push esi
    uint32_t t125 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t125);
    mem.w32(t125, ctx.esi);
    // 0x0040ed42: push ebx
    uint32_t t126 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t126);
    mem.w32(t126, ctx.ebx);
    // 0x0040ed43: lea ecx, [esp + 0x1c]
    uint32_t t127 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.ecx = static_cast<uint32_t>(t127);
    // 0x0040ed47: push ecx
    uint32_t t128 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t128);
    mem.w32(t128, ctx.ecx);
    // 0x0040ed48: push eax
    uint32_t t129 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t129);
    mem.w32(t129, ctx.eax);
    // 0x0040ed49: call 0x40f640
    uint32_t t130 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t130);
    mem.w32(t130, 0x0040ed4eu);
    sub_0040f640(ctx, mem);
    // 0x0040ed4e: jmp 0x40ed52
    goto bb_0040ed52;
}
}

// sub_0040ed70 | subsystem=Sound | canonical | 12 blocks | 96 insns
void sub_0040ed70(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040ed70: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0040ed72: push 0x514908
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00514908u);
    // 0x0040ed77: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0040ed7d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0040ed7e: sub esp, 0x18
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000018u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000018u, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x0040ed81: push esi
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.esi);
    // 0x0040ed82: push edi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.edi);
    // 0x0040ed83: mov eax, dword ptr [0x54b458]
    uint32_t t8 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x0040ed88: xor eax, esp
    uint32_t t9 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x0040ed8a: push eax
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.eax);
    // 0x0040ed8b: lea eax, [esp + 0x24]
    uint32_t t11 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x0040ed8f: mov dword ptr fs:[0], eax
    uint32_t t12 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t12, ctx.eax);
    // 0x0040ed95: mov eax, dword ptr [ebx + 0x18]
    uint32_t t13 = static_cast<uint32_t>(ctx.ebx + 0x00000018u);
    uint32_t t14 = mem.r32(t13);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x0040ed98: test eax, eax
    uint32_t t15 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t15);
    // 0x0040ed9a: jne 0x40eda0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040eda0;
    goto bb_0040ed9c;
}
bb_0040eda0: {
    // 0x0040eda0: mov edi, dword ptr [eax + 4]
    uint32_t t16 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t17 = mem.r32(t16);
    ctx.edi = static_cast<uint32_t>(t17);
    // 0x0040eda3: mov esi, dword ptr [eax + 8]
    uint32_t t18 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    uint32_t t19 = mem.r32(t18);
    ctx.esi = static_cast<uint32_t>(t19);
    // 0x0040eda6: lea eax, [ebx + 0x20]
    uint32_t t20 = static_cast<uint32_t>(ctx.ebx + 0x00000020u);
    ctx.eax = static_cast<uint32_t>(t20);
    // 0x0040eda9: push -1
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0xffffffffu);
    // 0x0040edab: push eax
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, ctx.eax);
    // 0x0040edac: call 0x4f32f0
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x0040edb1u);
    hle_crt_004f32f0(ctx, mem);
    // 0x0040edb1: imul esi, edi
    uint64_t t24 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.esi)) * static_cast<int64_t>(static_cast<int32_t>(ctx.edi)));
    uint32_t t25 = static_cast<uint32_t>(t24);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t24);
    ctx.esi = static_cast<uint32_t>(t25);
    // 0x0040edb4: mov dword ptr [esp + 0x18], esi
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t26, ctx.esi);
    // 0x0040edb8: add esp, 8
    uint32_t t27 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t27);
    ctx.esp = static_cast<uint32_t>(t27);
    // 0x0040edbb: fild dword ptr [esp + 0x10]
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    double t29 = static_cast<double>(static_cast<int32_t>(mem.r32(t28)));
    ctx.fpu_push(t29);
    // 0x0040edbf: fmulp st(1)
    double t30 = ctx.fpu_st(1);
    double t31 = ctx.fpu_st(0);
    double t32 = (t30 * t31);
    ctx.fpu_st(1) = t32;
    ctx.fpu_pop();
    // 0x0040edc1: fadd st(0), st(0)
    double t33 = ctx.fpu_st(0);
    double t34 = ctx.fpu_st(0);
    double t35 = (t33 + t34);
    ctx.fpu_st(0) = t35;
    // 0x0040edc3: call 0x4f49f0
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, 0x0040edc8u);
    hle_crt_004f49f0(ctx, mem);
    // 0x0040edc8: mov edx, eax
    ctx.edx = static_cast<uint32_t>(ctx.eax);
    goto bb_0040edca;
}
bb_0040ed9c: {
    // 0x0040ed9c: xor edx, edx
    uint32_t t37 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t37);
    ctx.edx = static_cast<uint32_t>(t37);
    // 0x0040ed9e: jmp 0x40edca
}
bb_0040edca: {
    // 0x0040edca: cmp dword ptr [ebx + 0x18], 0
    uint32_t t38 = static_cast<uint32_t>(ctx.ebx + 0x00000018u);
    uint32_t t39 = mem.r32(t38);
    uint32_t t40 = static_cast<uint32_t>(t39 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t39, 0x00000000u, t40);
    // 0x0040edce: lea ecx, [ebx + 0x2f0]
    uint32_t t41 = static_cast<uint32_t>(ctx.ebx + 0x000002f0u);
    ctx.ecx = static_cast<uint32_t>(t41);
    // 0x0040edd4: je 0x40ede8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ede8;
    goto bb_0040edd6;
}
bb_0040ede8: {
    // 0x0040ede8: mov dword ptr [esp + 0x10], 0
    uint32_t t42 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t42, 0x00000000u);
    goto bb_0040edf0;
}
bb_0040edd6: {
    // 0x0040edd6: mov eax, dword ptr [ebx + 0x18]
    uint32_t t43 = static_cast<uint32_t>(ctx.ebx + 0x00000018u);
    uint32_t t44 = mem.r32(t43);
    ctx.eax = static_cast<uint32_t>(t44);
    // 0x0040edd9: mov esi, dword ptr [eax + 8]
    uint32_t t45 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    uint32_t t46 = mem.r32(t45);
    ctx.esi = static_cast<uint32_t>(t46);
    // 0x0040eddc: imul esi, dword ptr [eax + 4]
    uint32_t t47 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t48 = mem.r32(t47);
    uint64_t t49 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.esi)) * static_cast<int64_t>(static_cast<int32_t>(t48)));
    uint32_t t50 = static_cast<uint32_t>(t49);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t49);
    ctx.esi = static_cast<uint32_t>(t50);
    // 0x0040ede0: add esi, esi
    uint32_t t51 = static_cast<uint32_t>(ctx.esi + ctx.esi);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, ctx.esi, t51);
    ctx.esi = static_cast<uint32_t>(t51);
    // 0x0040ede2: mov dword ptr [esp + 0x10], esi
    uint32_t t52 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t52, ctx.esi);
    // 0x0040ede6: jmp 0x40edf0
}
bb_0040edf0: {
    // 0x0040edf0: fild dword ptr [esp + 0x10]
    uint32_t t53 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    double t54 = static_cast<double>(static_cast<int32_t>(mem.r32(t53)));
    ctx.fpu_push(t54);
    // 0x0040edf4: fnstcw word ptr [esp + 0x10]
    uint32_t t55 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w16(t55, ctx.fpu_cw);
    // 0x0040edf8: movzx eax, word ptr [esp + 0x10]
    uint32_t t56 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint16_t t57 = mem.r16(t56);
    uint32_t t58 = static_cast<uint32_t>(static_cast<uint16_t>(t57));
    ctx.eax = static_cast<uint32_t>(t58);
    // 0x0040edfd: fadd st(0), st(0)
    double t59 = ctx.fpu_st(0);
    double t60 = ctx.fpu_st(0);
    double t61 = (t59 + t60);
    ctx.fpu_st(0) = t61;
    // 0x0040edff: or eax, 0xc00
    uint32_t t62 = static_cast<uint32_t>(ctx.eax | 0x00000c00u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t62);
    ctx.eax = static_cast<uint32_t>(t62);
    // 0x0040ee04: mov dword ptr [esp + 0x14], eax
    uint32_t t63 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t63, ctx.eax);
    // 0x0040ee08: fmul qword ptr [0x53da08]
    double t64 = ctx.fpu_st(0);
    double t65 = mem.rf64(0x0053da08u);
    double t66 = (t64 * t65);
    ctx.fpu_st(0) = t66;
    // 0x0040ee0e: fldcw word ptr [esp + 0x14]
    uint32_t t67 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint16_t t68 = mem.r16(t67);
    ctx.fpu_cw = static_cast<uint16_t>(t68);
    // 0x0040ee12: fistp qword ptr [esp + 0x14]
    uint32_t t69 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    double t70 = ctx.fpu_st(0);
    recomp_detail::fpu_store_int<uint64_t>(ctx, mem, t69, t70);
    ctx.fpu_pop();
    // 0x0040ee16: mov edi, dword ptr [esp + 0x14]
    uint32_t t71 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t72 = mem.r32(t71);
    ctx.edi = static_cast<uint32_t>(t72);
    // 0x0040ee1a: cmp edi, edx
    uint32_t t73 = static_cast<uint32_t>(ctx.edi - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.edx, t73);
    // 0x0040ee1c: fldcw word ptr [esp + 0x10]
    uint32_t t74 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint16_t t75 = mem.r16(t74);
    ctx.fpu_cw = static_cast<uint16_t>(t75);
    // 0x0040ee20: jbe 0x40ee24
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0040ee24;
    goto bb_0040ee22;
}
bb_0040ee24: {
    // 0x0040ee24: mov eax, 0xaaaaaaab
    ctx.eax = static_cast<uint32_t>(0xaaaaaaabu);
    // 0x0040ee29: mul edi
    uint64_t t76 = (static_cast<uint64_t>(ctx.eax) * static_cast<uint64_t>(ctx.edi));
    uint32_t t77 = static_cast<uint32_t>(t76);
    uint32_t t78 = static_cast<uint32_t>(t76 >> 32);
    ctx.eax = static_cast<uint32_t>(t77);
    ctx.edx = static_cast<uint32_t>(t78);
    recomp_detail::update_flags_mul<uint32_t>(ctx, t76);
    // 0x0040ee2b: mov esi, edx
    ctx.esi = static_cast<uint32_t>(ctx.edx);
    // 0x0040ee2d: push edi
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, ctx.edi);
    // 0x0040ee2e: mov edi, dword ptr [esp + 0x38]
    uint32_t t80 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    uint32_t t81 = mem.r32(t80);
    ctx.edi = static_cast<uint32_t>(t81);
    // 0x0040ee32: shr esi, 1
    uint32_t t82 = static_cast<uint32_t>(0x00000001u & 0x0000001fu);
    uint32_t t83 = recomp_detail::shr<uint32_t>(ctx.esi, t82);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.esi, t82, t83);
    ctx.esi = static_cast<uint32_t>(t83);
    // 0x0040ee34: call 0x40e7c0
    uint32_t t84 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    mem.w32(t84, 0x0040ee39u);
    sub_0040e7c0(ctx, mem);
    // 0x0040ee39: test eax, eax
    uint32_t t85 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t85);
    // 0x0040ee3b: mov dword ptr [esp + 0x34], eax
    uint32_t t86 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    mem.w32(t86, ctx.eax);
    // 0x0040ee3f: je 0x40ee8b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ee8b;
    goto bb_0040ee41;
}
bb_0040ee22: {
    // 0x0040ee22: mov edi, edx
    ctx.edi = static_cast<uint32_t>(ctx.edx);
    goto bb_0040ee24;
}
bb_0040ee8b: {
    // 0x0040ee8b: xor eax, eax
    uint32_t t87 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t87);
    ctx.eax = static_cast<uint32_t>(t87);
    // 0x0040ee8d: mov ecx, dword ptr [esp + 0x24]
    uint32_t t88 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t89 = mem.r32(t88);
    ctx.ecx = static_cast<uint32_t>(t89);
    // 0x0040ee91: mov dword ptr fs:[0], ecx
    uint32_t t90 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t90, ctx.ecx);
    // 0x0040ee98: pop ecx
    uint32_t t91 = ctx.esp;
    uint32_t t92 = mem.r32(t91);
    uint32_t t93 = static_cast<uint32_t>(t91 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    ctx.ecx = static_cast<uint32_t>(t92);
    // 0x0040ee99: pop edi
    uint32_t t94 = ctx.esp;
    uint32_t t95 = mem.r32(t94);
    uint32_t t96 = static_cast<uint32_t>(t94 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    ctx.edi = static_cast<uint32_t>(t95);
    // 0x0040ee9a: pop esi
    uint32_t t97 = ctx.esp;
    uint32_t t98 = mem.r32(t97);
    uint32_t t99 = static_cast<uint32_t>(t97 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t99);
    ctx.esi = static_cast<uint32_t>(t98);
    // 0x0040ee9b: add esp, 0x24
    uint32_t t100 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000024u, t100);
    ctx.esp = static_cast<uint32_t>(t100);
    // 0x0040ee9e: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0040ee41: {
    // 0x0040ee41: push 0x230
    uint32_t t101 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t101);
    mem.w32(t101, 0x00000230u);
    // 0x0040ee46: push 0x535268
    uint32_t t102 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    mem.w32(t102, 0x00535268u);
    // 0x0040ee4b: push 4
    uint32_t t103 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    mem.w32(t103, 0x00000004u);
    // 0x0040ee4d: push 0x98
    uint32_t t104 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t104);
    mem.w32(t104, 0x00000098u);
    // 0x0040ee52: call 0x4e0675
    uint32_t t105 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t105);
    mem.w32(t105, 0x0040ee57u);
    hle_crt_004e0675(ctx, mem);
    // 0x0040ee57: add esp, 0x10
    uint32_t t106 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t106);
    ctx.esp = static_cast<uint32_t>(t106);
    // 0x0040ee5a: mov dword ptr [esp + 0x14], eax
    uint32_t t107 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t107, ctx.eax);
    // 0x0040ee5e: test eax, eax
    uint32_t t108 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t108);
    // 0x0040ee60: mov dword ptr [esp + 0x2c], 0
    uint32_t t109 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    mem.w32(t109, 0x00000000u);
    // 0x0040ee68: je 0x40ee8b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ee8b;
}
{
    // 0x0040ee6a: push esi
    uint32_t t110 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t110);
    mem.w32(t110, ctx.esi);
    // 0x0040ee6b: push ebx
    uint32_t t111 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t111);
    mem.w32(t111, ctx.ebx);
    // 0x0040ee6c: lea ecx, [esp + 0x3c]
    uint32_t t112 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    ctx.ecx = static_cast<uint32_t>(t112);
    // 0x0040ee70: push ecx
    uint32_t t113 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t113);
    mem.w32(t113, ctx.ecx);
    // 0x0040ee71: push eax
    uint32_t t114 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t114);
    mem.w32(t114, ctx.eax);
    // 0x0040ee72: call 0x40f6f0
    uint32_t t115 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t115);
    mem.w32(t115, 0x0040ee77u);
    sub_0040f6f0(ctx, mem);
    // 0x0040ee77: mov ecx, dword ptr [esp + 0x24]
    uint32_t t116 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t117 = mem.r32(t116);
    ctx.ecx = static_cast<uint32_t>(t117);
    // 0x0040ee7b: mov dword ptr fs:[0], ecx
    uint32_t t118 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t118, ctx.ecx);
    // 0x0040ee82: pop ecx
    uint32_t t119 = ctx.esp;
    uint32_t t120 = mem.r32(t119);
    uint32_t t121 = static_cast<uint32_t>(t119 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t121);
    ctx.ecx = static_cast<uint32_t>(t120);
    // 0x0040ee83: pop edi
    uint32_t t122 = ctx.esp;
    uint32_t t123 = mem.r32(t122);
    uint32_t t124 = static_cast<uint32_t>(t122 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t124);
    ctx.edi = static_cast<uint32_t>(t123);
    // 0x0040ee84: pop esi
    uint32_t t125 = ctx.esp;
    uint32_t t126 = mem.r32(t125);
    uint32_t t127 = static_cast<uint32_t>(t125 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t127);
    ctx.esi = static_cast<uint32_t>(t126);
    // 0x0040ee85: add esp, 0x24
    uint32_t t128 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000024u, t128);
    ctx.esp = static_cast<uint32_t>(t128);
    // 0x0040ee88: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
}

// sub_0040eeb0 | subsystem=Sound | canonical | 48 blocks | 176 insns
void sub_0040eeb0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040eeb0: push ebx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebx);
    // 0x0040eeb1: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
    // 0x0040eeb2: push edi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.edi);
    // 0x0040eeb3: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x0040eeb5: mov edx, 4
    ctx.edx = static_cast<uint32_t>(0x00000004u);
    // 0x0040eeba: mov eax, 0x53528c
    ctx.eax = static_cast<uint32_t>(0x0053528cu);
    // 0x0040eebf: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
}
bb_0040eec1: {
    // 0x0040eec1: mov esi, dword ptr [ecx]
    uint32_t t3 = mem.r32(ctx.ecx);
    ctx.esi = static_cast<uint32_t>(t3);
    // 0x0040eec3: cmp esi, dword ptr [eax]
    uint32_t t4 = mem.r32(ctx.eax);
    uint32_t t5 = static_cast<uint32_t>(ctx.esi - t4);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, t4, t5);
    // 0x0040eec5: jne 0x40eed9
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040eed9;
    goto bb_0040eec7;
}
bb_0040eed9: {
    // 0x0040eed9: movzx esi, byte ptr [ecx]
    uint8_t t6 = mem.r8(ctx.ecx);
    uint32_t t7 = static_cast<uint32_t>(static_cast<uint8_t>(t6));
    ctx.esi = static_cast<uint32_t>(t7);
    // 0x0040eedc: movzx ebx, byte ptr [eax]
    uint8_t t8 = mem.r8(ctx.eax);
    uint32_t t9 = static_cast<uint32_t>(static_cast<uint8_t>(t8));
    ctx.ebx = static_cast<uint32_t>(t9);
    // 0x0040eedf: sub esi, ebx
    uint32_t t10 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t10);
    ctx.esi = static_cast<uint32_t>(t10);
    // 0x0040eee1: jne 0x40ef28
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040ef28;
    goto bb_0040eee3;
}
bb_0040eec7: {
    // 0x0040eec7: sub edx, 4
    uint32_t t11 = static_cast<uint32_t>(ctx.edx - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000004u, t11);
    ctx.edx = static_cast<uint32_t>(t11);
    // 0x0040eeca: add eax, 4
    uint32_t t12 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000004u, t12);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0040eecd: add ecx, 4
    uint32_t t13 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000004u, t13);
    ctx.ecx = static_cast<uint32_t>(t13);
    // 0x0040eed0: cmp edx, 4
    uint32_t t14 = static_cast<uint32_t>(ctx.edx - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000004u, t14);
    // 0x0040eed3: jae 0x40eec1
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0040eec1;
    goto bb_0040eed5;
}
bb_0040ef28: {
    // 0x0040ef28: test esi, esi
    uint32_t t15 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t15);
    // 0x0040ef2a: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0040ef2f: jg 0x40ef38
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0040ef38;
    goto bb_0040ef31;
}
bb_0040eee3: {
    // 0x0040eee3: sub edx, 1
    uint32_t t16 = static_cast<uint32_t>(ctx.edx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000001u, t16);
    ctx.edx = static_cast<uint32_t>(t16);
    // 0x0040eee6: add eax, 1
    uint32_t t17 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t17);
    ctx.eax = static_cast<uint32_t>(t17);
    // 0x0040eee9: add ecx, 1
    uint32_t t18 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t18);
    ctx.ecx = static_cast<uint32_t>(t18);
    // 0x0040eeec: test edx, edx
    uint32_t t19 = static_cast<uint32_t>(ctx.edx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t19);
    // 0x0040eeee: je 0x40ef36
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ef36;
    goto bb_0040eef0;
}
bb_0040eed5: {
    // 0x0040eed5: test edx, edx
    uint32_t t20 = static_cast<uint32_t>(ctx.edx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t20);
    // 0x0040eed7: je 0x40ef36
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ef36;
    goto bb_0040eed9;
}
bb_0040ef38: {
    // 0x0040ef38: test eax, eax
    uint32_t t21 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t21);
    // 0x0040ef3a: jne 0x40ef45
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040ef45;
    goto bb_0040ef3c;
}
bb_0040ef31: {
    // 0x0040ef31: or eax, 0xffffffff
    uint32_t t22 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t22);
    ctx.eax = static_cast<uint32_t>(t22);
    // 0x0040ef34: jmp 0x40ef38
    goto bb_0040ef38;
}
bb_0040ef36: {
    // 0x0040ef36: xor eax, eax
    uint32_t t23 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t23);
    ctx.eax = static_cast<uint32_t>(t23);
    goto bb_0040ef38;
}
bb_0040eef0: {
    // 0x0040eef0: movzx esi, byte ptr [ecx]
    uint8_t t24 = mem.r8(ctx.ecx);
    uint32_t t25 = static_cast<uint32_t>(static_cast<uint8_t>(t24));
    ctx.esi = static_cast<uint32_t>(t25);
    // 0x0040eef3: movzx ebx, byte ptr [eax]
    uint8_t t26 = mem.r8(ctx.eax);
    uint32_t t27 = static_cast<uint32_t>(static_cast<uint8_t>(t26));
    ctx.ebx = static_cast<uint32_t>(t27);
    // 0x0040eef6: sub esi, ebx
    uint32_t t28 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t28);
    ctx.esi = static_cast<uint32_t>(t28);
    // 0x0040eef8: jne 0x40ef28
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040ef28;
    goto bb_0040eefa;
}
bb_0040ef45: {
    // 0x0040ef45: mov eax, 4
    ctx.eax = static_cast<uint32_t>(0x00000004u);
    // 0x0040ef4a: mov ecx, 0x535294
    ctx.ecx = static_cast<uint32_t>(0x00535294u);
    // 0x0040ef4f: mov edx, edi
    ctx.edx = static_cast<uint32_t>(ctx.edi);
    goto bb_0040ef51;
}
bb_0040ef3c: {
    // 0x0040ef3c: pop edi
    uint32_t t29 = ctx.esp;
    uint32_t t30 = mem.r32(t29);
    uint32_t t31 = static_cast<uint32_t>(t29 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    ctx.edi = static_cast<uint32_t>(t30);
    // 0x0040ef3d: pop esi
    uint32_t t32 = ctx.esp;
    uint32_t t33 = mem.r32(t32);
    uint32_t t34 = static_cast<uint32_t>(t32 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    ctx.esi = static_cast<uint32_t>(t33);
    // 0x0040ef3e: mov eax, 2
    ctx.eax = static_cast<uint32_t>(0x00000002u);
    // 0x0040ef43: pop ebx
    uint32_t t35 = ctx.esp;
    uint32_t t36 = mem.r32(t35);
    uint32_t t37 = static_cast<uint32_t>(t35 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    ctx.ebx = static_cast<uint32_t>(t36);
    // 0x0040ef44: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040eefa: {
    // 0x0040eefa: sub edx, 1
    uint32_t t38 = static_cast<uint32_t>(ctx.edx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000001u, t38);
    ctx.edx = static_cast<uint32_t>(t38);
    // 0x0040eefd: add eax, 1
    uint32_t t39 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t39);
    ctx.eax = static_cast<uint32_t>(t39);
    // 0x0040ef00: add ecx, 1
    uint32_t t40 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t40);
    ctx.ecx = static_cast<uint32_t>(t40);
    // 0x0040ef03: test edx, edx
    uint32_t t41 = static_cast<uint32_t>(ctx.edx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t41);
    // 0x0040ef05: je 0x40ef36
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ef36;
    goto bb_0040ef07;
}
bb_0040ef51: {
    // 0x0040ef51: mov esi, dword ptr [edx]
    uint32_t t42 = mem.r32(ctx.edx);
    ctx.esi = static_cast<uint32_t>(t42);
    // 0x0040ef53: cmp esi, dword ptr [ecx]
    uint32_t t43 = mem.r32(ctx.ecx);
    uint32_t t44 = static_cast<uint32_t>(ctx.esi - t43);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, t43, t44);
    // 0x0040ef55: jne 0x40ef69
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040ef69;
    goto bb_0040ef57;
}
bb_0040ef07: {
    // 0x0040ef07: movzx esi, byte ptr [ecx]
    uint8_t t45 = mem.r8(ctx.ecx);
    uint32_t t46 = static_cast<uint32_t>(static_cast<uint8_t>(t45));
    ctx.esi = static_cast<uint32_t>(t46);
    // 0x0040ef0a: movzx ebx, byte ptr [eax]
    uint8_t t47 = mem.r8(ctx.eax);
    uint32_t t48 = static_cast<uint32_t>(static_cast<uint8_t>(t47));
    ctx.ebx = static_cast<uint32_t>(t48);
    // 0x0040ef0d: sub esi, ebx
    uint32_t t49 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t49);
    ctx.esi = static_cast<uint32_t>(t49);
    // 0x0040ef0f: jne 0x40ef28
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040ef28;
    goto bb_0040ef11;
}
bb_0040ef69: {
    // 0x0040ef69: movzx ebx, byte ptr [ecx]
    uint8_t t50 = mem.r8(ctx.ecx);
    uint32_t t51 = static_cast<uint32_t>(static_cast<uint8_t>(t50));
    ctx.ebx = static_cast<uint32_t>(t51);
    // 0x0040ef6c: movzx esi, byte ptr [edx]
    uint8_t t52 = mem.r8(ctx.edx);
    uint32_t t53 = static_cast<uint32_t>(static_cast<uint8_t>(t52));
    ctx.esi = static_cast<uint32_t>(t53);
    // 0x0040ef6f: sub esi, ebx
    uint32_t t54 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t54);
    ctx.esi = static_cast<uint32_t>(t54);
    // 0x0040ef71: jne 0x40efb8
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040efb8;
    goto bb_0040ef73;
}
bb_0040ef57: {
    // 0x0040ef57: sub eax, 4
    uint32_t t55 = static_cast<uint32_t>(ctx.eax - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000004u, t55);
    ctx.eax = static_cast<uint32_t>(t55);
    // 0x0040ef5a: add ecx, 4
    uint32_t t56 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000004u, t56);
    ctx.ecx = static_cast<uint32_t>(t56);
    // 0x0040ef5d: add edx, 4
    uint32_t t57 = static_cast<uint32_t>(ctx.edx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000004u, t57);
    ctx.edx = static_cast<uint32_t>(t57);
    // 0x0040ef60: cmp eax, 4
    uint32_t t58 = static_cast<uint32_t>(ctx.eax - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000004u, t58);
    // 0x0040ef63: jae 0x40ef51
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0040ef51;
    goto bb_0040ef65;
}
bb_0040ef11: {
    // 0x0040ef11: sub edx, 1
    uint32_t t59 = static_cast<uint32_t>(ctx.edx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000001u, t59);
    ctx.edx = static_cast<uint32_t>(t59);
    // 0x0040ef14: add eax, 1
    uint32_t t60 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t60);
    ctx.eax = static_cast<uint32_t>(t60);
    // 0x0040ef17: add ecx, 1
    uint32_t t61 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t61);
    ctx.ecx = static_cast<uint32_t>(t61);
    // 0x0040ef1a: test edx, edx
    uint32_t t62 = static_cast<uint32_t>(ctx.edx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t62);
    // 0x0040ef1c: je 0x40ef36
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ef36;
    goto bb_0040ef1e;
}
bb_0040efb8: {
    // 0x0040efb8: test esi, esi
    uint32_t t63 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t63);
    // 0x0040efba: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0040efbf: jg 0x40efc8
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0040efc8;
    goto bb_0040efc1;
}
bb_0040ef73: {
    // 0x0040ef73: sub eax, 1
    uint32_t t64 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t64);
    ctx.eax = static_cast<uint32_t>(t64);
    // 0x0040ef76: add ecx, 1
    uint32_t t65 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t65);
    ctx.ecx = static_cast<uint32_t>(t65);
    // 0x0040ef79: add edx, 1
    uint32_t t66 = static_cast<uint32_t>(ctx.edx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000001u, t66);
    ctx.edx = static_cast<uint32_t>(t66);
    // 0x0040ef7c: test eax, eax
    uint32_t t67 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t67);
    // 0x0040ef7e: je 0x40efc6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040efc6;
    goto bb_0040ef80;
}
bb_0040ef65: {
    // 0x0040ef65: test eax, eax
    uint32_t t68 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t68);
    // 0x0040ef67: je 0x40efc6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040efc6;
    goto bb_0040ef69;
}
bb_0040ef1e: {
    // 0x0040ef1e: movzx esi, byte ptr [ecx]
    uint8_t t69 = mem.r8(ctx.ecx);
    uint32_t t70 = static_cast<uint32_t>(static_cast<uint8_t>(t69));
    ctx.esi = static_cast<uint32_t>(t70);
    // 0x0040ef21: movzx eax, byte ptr [eax]
    uint8_t t71 = mem.r8(ctx.eax);
    uint32_t t72 = static_cast<uint32_t>(static_cast<uint8_t>(t71));
    ctx.eax = static_cast<uint32_t>(t72);
    // 0x0040ef24: sub esi, eax
    uint32_t t73 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t73);
    ctx.esi = static_cast<uint32_t>(t73);
    // 0x0040ef26: je 0x40ef36
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040ef36;
    goto bb_0040ef28;
}
bb_0040efc8: {
    // 0x0040efc8: test eax, eax
    uint32_t t74 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t74);
    // 0x0040efca: jne 0x40f064
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040f064;
    goto bb_0040efd0;
}
bb_0040efc1: {
    // 0x0040efc1: or eax, 0xffffffff
    uint32_t t75 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t75);
    ctx.eax = static_cast<uint32_t>(t75);
    // 0x0040efc4: jmp 0x40efc8
    goto bb_0040efc8;
}
bb_0040efc6: {
    // 0x0040efc6: xor eax, eax
    uint32_t t76 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t76);
    ctx.eax = static_cast<uint32_t>(t76);
    goto bb_0040efc8;
}
bb_0040ef80: {
    // 0x0040ef80: movzx ebx, byte ptr [ecx]
    uint8_t t77 = mem.r8(ctx.ecx);
    uint32_t t78 = static_cast<uint32_t>(static_cast<uint8_t>(t77));
    ctx.ebx = static_cast<uint32_t>(t78);
    // 0x0040ef83: movzx esi, byte ptr [edx]
    uint8_t t79 = mem.r8(ctx.edx);
    uint32_t t80 = static_cast<uint32_t>(static_cast<uint8_t>(t79));
    ctx.esi = static_cast<uint32_t>(t80);
    // 0x0040ef86: sub esi, ebx
    uint32_t t81 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t81);
    ctx.esi = static_cast<uint32_t>(t81);
    // 0x0040ef88: jne 0x40efb8
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040efb8;
    goto bb_0040ef8a;
}
bb_0040f064: {
    // 0x0040f064: pop edi
    uint32_t t82 = ctx.esp;
    uint32_t t83 = mem.r32(t82);
    uint32_t t84 = static_cast<uint32_t>(t82 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    ctx.edi = static_cast<uint32_t>(t83);
    // 0x0040f065: pop esi
    uint32_t t85 = ctx.esp;
    uint32_t t86 = mem.r32(t85);
    uint32_t t87 = static_cast<uint32_t>(t85 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t87);
    ctx.esi = static_cast<uint32_t>(t86);
    // 0x0040f066: xor eax, eax
    uint32_t t88 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t88);
    ctx.eax = static_cast<uint32_t>(t88);
    // 0x0040f068: pop ebx
    uint32_t t89 = ctx.esp;
    uint32_t t90 = mem.r32(t89);
    uint32_t t91 = static_cast<uint32_t>(t89 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    ctx.ebx = static_cast<uint32_t>(t90);
    // 0x0040f069: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040efd0: {
    // 0x0040efd0: mov eax, 7
    ctx.eax = static_cast<uint32_t>(0x00000007u);
    // 0x0040efd5: mov ecx, 0x53529c
    ctx.ecx = static_cast<uint32_t>(0x0053529cu);
    // 0x0040efda: lea edx, [edi + 8]
    uint32_t t92 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    ctx.edx = static_cast<uint32_t>(t92);
    // 0x0040efdd: lea ecx, [ecx]
    ctx.ecx = static_cast<uint32_t>(ctx.ecx);
    goto bb_0040efe0;
}
bb_0040ef8a: {
    // 0x0040ef8a: sub eax, 1
    uint32_t t93 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t93);
    ctx.eax = static_cast<uint32_t>(t93);
    // 0x0040ef8d: add ecx, 1
    uint32_t t94 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t94);
    ctx.ecx = static_cast<uint32_t>(t94);
    // 0x0040ef90: add edx, 1
    uint32_t t95 = static_cast<uint32_t>(ctx.edx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000001u, t95);
    ctx.edx = static_cast<uint32_t>(t95);
    // 0x0040ef93: test eax, eax
    uint32_t t96 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t96);
    // 0x0040ef95: je 0x40efc6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040efc6;
    goto bb_0040ef97;
}
bb_0040efe0: {
    // 0x0040efe0: mov esi, dword ptr [edx]
    uint32_t t97 = mem.r32(ctx.edx);
    ctx.esi = static_cast<uint32_t>(t97);
    // 0x0040efe2: cmp esi, dword ptr [ecx]
    uint32_t t98 = mem.r32(ctx.ecx);
    uint32_t t99 = static_cast<uint32_t>(ctx.esi - t98);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, t98, t99);
    // 0x0040efe4: jne 0x40eff8
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040eff8;
    goto bb_0040efe6;
}
bb_0040ef97: {
    // 0x0040ef97: movzx ebx, byte ptr [ecx]
    uint8_t t100 = mem.r8(ctx.ecx);
    uint32_t t101 = static_cast<uint32_t>(static_cast<uint8_t>(t100));
    ctx.ebx = static_cast<uint32_t>(t101);
    // 0x0040ef9a: movzx esi, byte ptr [edx]
    uint8_t t102 = mem.r8(ctx.edx);
    uint32_t t103 = static_cast<uint32_t>(static_cast<uint8_t>(t102));
    ctx.esi = static_cast<uint32_t>(t103);
    // 0x0040ef9d: sub esi, ebx
    uint32_t t104 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t104);
    ctx.esi = static_cast<uint32_t>(t104);
    // 0x0040ef9f: jne 0x40efb8
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040efb8;
    goto bb_0040efa1;
}
bb_0040eff8: {
    // 0x0040eff8: movzx esi, byte ptr [edx]
    uint8_t t105 = mem.r8(ctx.edx);
    uint32_t t106 = static_cast<uint32_t>(static_cast<uint8_t>(t105));
    ctx.esi = static_cast<uint32_t>(t106);
    // 0x0040effb: movzx edi, byte ptr [ecx]
    uint8_t t107 = mem.r8(ctx.ecx);
    uint32_t t108 = static_cast<uint32_t>(static_cast<uint8_t>(t107));
    ctx.edi = static_cast<uint32_t>(t108);
    // 0x0040effe: sub esi, edi
    uint32_t t109 = static_cast<uint32_t>(ctx.esi - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edi, t109);
    ctx.esi = static_cast<uint32_t>(t109);
    // 0x0040f000: jne 0x40f047
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040f047;
    goto bb_0040f002;
}
bb_0040efe6: {
    // 0x0040efe6: sub eax, 4
    uint32_t t110 = static_cast<uint32_t>(ctx.eax - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000004u, t110);
    ctx.eax = static_cast<uint32_t>(t110);
    // 0x0040efe9: add ecx, 4
    uint32_t t111 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000004u, t111);
    ctx.ecx = static_cast<uint32_t>(t111);
    // 0x0040efec: add edx, 4
    uint32_t t112 = static_cast<uint32_t>(ctx.edx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000004u, t112);
    ctx.edx = static_cast<uint32_t>(t112);
    // 0x0040efef: cmp eax, 4
    uint32_t t113 = static_cast<uint32_t>(ctx.eax - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000004u, t113);
    // 0x0040eff2: jae 0x40efe0
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0040efe0;
    goto bb_0040eff4;
}
bb_0040efa1: {
    // 0x0040efa1: sub eax, 1
    uint32_t t114 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t114);
    ctx.eax = static_cast<uint32_t>(t114);
    // 0x0040efa4: add ecx, 1
    uint32_t t115 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t115);
    ctx.ecx = static_cast<uint32_t>(t115);
    // 0x0040efa7: add edx, 1
    uint32_t t116 = static_cast<uint32_t>(ctx.edx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000001u, t116);
    ctx.edx = static_cast<uint32_t>(t116);
    // 0x0040efaa: test eax, eax
    uint32_t t117 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t117);
    // 0x0040efac: je 0x40efc6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040efc6;
    goto bb_0040efae;
}
bb_0040f047: {
    // 0x0040f047: test esi, esi
    uint32_t t118 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t118);
    // 0x0040f049: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0040f04e: jg 0x40f057
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0040f057;
    goto bb_0040f050;
}
bb_0040f002: {
    // 0x0040f002: sub eax, 1
    uint32_t t119 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t119);
    ctx.eax = static_cast<uint32_t>(t119);
    // 0x0040f005: add ecx, 1
    uint32_t t120 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t120);
    ctx.ecx = static_cast<uint32_t>(t120);
    // 0x0040f008: add edx, 1
    uint32_t t121 = static_cast<uint32_t>(ctx.edx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000001u, t121);
    ctx.edx = static_cast<uint32_t>(t121);
    // 0x0040f00b: test eax, eax
    uint32_t t122 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t122);
    // 0x0040f00d: je 0x40f055
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f055;
    goto bb_0040f00f;
}
bb_0040eff4: {
    // 0x0040eff4: test eax, eax
    uint32_t t123 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t123);
    // 0x0040eff6: je 0x40f055
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f055;
    goto bb_0040eff8;
}
bb_0040efae: {
    // 0x0040efae: movzx ecx, byte ptr [ecx]
    uint8_t t124 = mem.r8(ctx.ecx);
    uint32_t t125 = static_cast<uint32_t>(static_cast<uint8_t>(t124));
    ctx.ecx = static_cast<uint32_t>(t125);
    // 0x0040efb1: movzx esi, byte ptr [edx]
    uint8_t t126 = mem.r8(ctx.edx);
    uint32_t t127 = static_cast<uint32_t>(static_cast<uint8_t>(t126));
    ctx.esi = static_cast<uint32_t>(t127);
    // 0x0040efb4: sub esi, ecx
    uint32_t t128 = static_cast<uint32_t>(ctx.esi - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ecx, t128);
    ctx.esi = static_cast<uint32_t>(t128);
    // 0x0040efb6: je 0x40efc6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040efc6;
    goto bb_0040efb8;
}
bb_0040f057: {
    // 0x0040f057: test eax, eax
    uint32_t t129 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t129);
    // 0x0040f059: jne 0x40f064
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040f064;
    goto bb_0040f05b;
}
bb_0040f050: {
    // 0x0040f050: or eax, 0xffffffff
    uint32_t t130 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t130);
    ctx.eax = static_cast<uint32_t>(t130);
    // 0x0040f053: jmp 0x40f057
    goto bb_0040f057;
}
bb_0040f055: {
    // 0x0040f055: xor eax, eax
    uint32_t t131 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t131);
    ctx.eax = static_cast<uint32_t>(t131);
    goto bb_0040f057;
}
bb_0040f00f: {
    // 0x0040f00f: movzx esi, byte ptr [edx]
    uint8_t t132 = mem.r8(ctx.edx);
    uint32_t t133 = static_cast<uint32_t>(static_cast<uint8_t>(t132));
    ctx.esi = static_cast<uint32_t>(t133);
    // 0x0040f012: movzx edi, byte ptr [ecx]
    uint8_t t134 = mem.r8(ctx.ecx);
    uint32_t t135 = static_cast<uint32_t>(static_cast<uint8_t>(t134));
    ctx.edi = static_cast<uint32_t>(t135);
    // 0x0040f015: sub esi, edi
    uint32_t t136 = static_cast<uint32_t>(ctx.esi - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edi, t136);
    ctx.esi = static_cast<uint32_t>(t136);
    // 0x0040f017: jne 0x40f047
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040f047;
    goto bb_0040f019;
}
bb_0040f05b: {
    // 0x0040f05b: pop edi
    uint32_t t137 = ctx.esp;
    uint32_t t138 = mem.r32(t137);
    uint32_t t139 = static_cast<uint32_t>(t137 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t139);
    ctx.edi = static_cast<uint32_t>(t138);
    // 0x0040f05c: pop esi
    uint32_t t140 = ctx.esp;
    uint32_t t141 = mem.r32(t140);
    uint32_t t142 = static_cast<uint32_t>(t140 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t142);
    ctx.esi = static_cast<uint32_t>(t141);
    // 0x0040f05d: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0040f062: pop ebx
    uint32_t t143 = ctx.esp;
    uint32_t t144 = mem.r32(t143);
    uint32_t t145 = static_cast<uint32_t>(t143 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t145);
    ctx.ebx = static_cast<uint32_t>(t144);
    // 0x0040f063: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040f019: {
    // 0x0040f019: sub eax, 1
    uint32_t t146 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t146);
    ctx.eax = static_cast<uint32_t>(t146);
    // 0x0040f01c: add ecx, 1
    uint32_t t147 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t147);
    ctx.ecx = static_cast<uint32_t>(t147);
    // 0x0040f01f: add edx, 1
    uint32_t t148 = static_cast<uint32_t>(ctx.edx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000001u, t148);
    ctx.edx = static_cast<uint32_t>(t148);
    // 0x0040f022: test eax, eax
    uint32_t t149 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t149);
    // 0x0040f024: je 0x40f055
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f055;
}
{
    // 0x0040f026: movzx esi, byte ptr [edx]
    uint8_t t150 = mem.r8(ctx.edx);
    uint32_t t151 = static_cast<uint32_t>(static_cast<uint8_t>(t150));
    ctx.esi = static_cast<uint32_t>(t151);
    // 0x0040f029: movzx edi, byte ptr [ecx]
    uint8_t t152 = mem.r8(ctx.ecx);
    uint32_t t153 = static_cast<uint32_t>(static_cast<uint8_t>(t152));
    ctx.edi = static_cast<uint32_t>(t153);
    // 0x0040f02c: sub esi, edi
    uint32_t t154 = static_cast<uint32_t>(ctx.esi - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edi, t154);
    ctx.esi = static_cast<uint32_t>(t154);
    // 0x0040f02e: jne 0x40f047
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040f047;
}
{
    // 0x0040f030: sub eax, 1
    uint32_t t155 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t155);
    ctx.eax = static_cast<uint32_t>(t155);
    // 0x0040f033: add ecx, 1
    uint32_t t156 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t156);
    ctx.ecx = static_cast<uint32_t>(t156);
    // 0x0040f036: add edx, 1
    uint32_t t157 = static_cast<uint32_t>(ctx.edx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000001u, t157);
    ctx.edx = static_cast<uint32_t>(t157);
    // 0x0040f039: test eax, eax
    uint32_t t158 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t158);
    // 0x0040f03b: je 0x40f055
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f055;
}
{
    // 0x0040f03d: movzx esi, byte ptr [edx]
    uint8_t t159 = mem.r8(ctx.edx);
    uint32_t t160 = static_cast<uint32_t>(static_cast<uint8_t>(t159));
    ctx.esi = static_cast<uint32_t>(t160);
    // 0x0040f040: movzx edx, byte ptr [ecx]
    uint8_t t161 = mem.r8(ctx.ecx);
    uint32_t t162 = static_cast<uint32_t>(static_cast<uint8_t>(t161));
    ctx.edx = static_cast<uint32_t>(t162);
    // 0x0040f043: sub esi, edx
    uint32_t t163 = static_cast<uint32_t>(ctx.esi - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edx, t163);
    ctx.esi = static_cast<uint32_t>(t163);
    // 0x0040f045: je 0x40f055
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f055;
    goto bb_0040f047;
}
}

// sub_0040f070 | subsystem=Sound | canonical | 28 blocks | 120 insns
void sub_0040f070(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040f070: sub esp, 0x20
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000020u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000020u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x0040f073: mov eax, dword ptr [0x76e000]
    uint32_t t1 = mem.r32(0x0076e000u);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x0040f078: push ebx
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebx);
    // 0x0040f079: push ebp
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.ebp);
    // 0x0040f07a: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x0040f07b: xor ebp, ebp
    uint32_t t5 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    ctx.ebp = static_cast<uint32_t>(t5);
    // 0x0040f07d: push edi
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.edi);
    // 0x0040f07e: mov edi, dword ptr [esp + 0x34]
    uint32_t t7 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    uint32_t t8 = mem.r32(t7);
    ctx.edi = static_cast<uint32_t>(t8);
    // 0x0040f082: mov esi, dword ptr [edi]
    uint32_t t9 = mem.r32(ctx.edi);
    ctx.esi = static_cast<uint32_t>(t9);
    // 0x0040f084: xor ebx, ebx
    uint32_t t10 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.ebx = static_cast<uint32_t>(t10);
    // 0x0040f086: cmp esi, ebp
    uint32_t t11 = static_cast<uint32_t>(ctx.esi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebp, t11);
    // 0x0040f088: mov dword ptr [esp + 0x18], eax
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t12, ctx.eax);
    // 0x0040f08c: mov dword ptr [esp + 0x1c], ebp
    uint32_t t13 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t13, ctx.ebp);
    // 0x0040f090: mov dword ptr [esp + 0x14], ebx
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t14, ctx.ebx);
    // 0x0040f094: mov dword ptr [esp + 0x20], ebp
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t15, ctx.ebp);
    // 0x0040f098: mov dword ptr [esp + 0x28], ebp
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t16, ctx.ebp);
    // 0x0040f09c: mov dword ptr [esp + 0x24], ebp
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t17, ctx.ebp);
    // 0x0040f0a0: mov dword ptr [esp + 0x2c], ebp
    uint32_t t18 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    mem.w32(t18, ctx.ebp);
    // 0x0040f0a4: jne 0x40f0ab
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040f0ab;
    goto bb_0040f0a6;
}
bb_0040f0ab: {
    // 0x0040f0ab: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0040f0ad: call 0x40eeb0
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x0040f0b2u);
    sub_0040eeb0(ctx, mem);
    goto bb_0040f0b2;
}
bb_0040f0a6: {
    // 0x0040f0a6: or eax, 0xffffffff
    uint32_t t20 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t20);
    ctx.eax = static_cast<uint32_t>(t20);
    // 0x0040f0a9: jmp 0x40f0b2
}
bb_0040f0b2: {
    // 0x0040f0b2: sub eax, 1
    uint32_t t21 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t21);
    ctx.eax = static_cast<uint32_t>(t21);
    // 0x0040f0b5: je 0x40f12b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f12b;
    goto bb_0040f0b7;
}
bb_0040f12b: {
    // 0x0040f12b: push 0x2ad
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x000002adu);
    // 0x0040f130: push 0x535268
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x00535268u);
    // 0x0040f135: push 4
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x00000004u);
    // 0x0040f137: push 0x20
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x00000020u);
    // 0x0040f139: call 0x4e0675
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x0040f13eu);
    hle_crt_004e0675(ctx, mem);
    // 0x0040f13e: add esp, 0x10
    uint32_t t27 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t27);
    ctx.esp = static_cast<uint32_t>(t27);
    // 0x0040f141: cmp eax, ebp
    uint32_t t28 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t28);
    // 0x0040f143: je 0x40f160
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f160;
    goto bb_0040f145;
}
bb_0040f0b7: {
    // 0x0040f0b7: sub eax, 1
    uint32_t t29 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t29);
    ctx.eax = static_cast<uint32_t>(t29);
    // 0x0040f0ba: jne 0x40f1a2
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040f1a2;
    goto bb_0040f0c0;
}
bb_0040f160: {
    // 0x0040f160: xor ebx, ebx
    uint32_t t30 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t30);
    ctx.ebx = static_cast<uint32_t>(t30);
    goto bb_0040f162;
}
bb_0040f145: {
    // 0x0040f145: mov dword ptr [eax], ebp
    mem.w32(ctx.eax, ctx.ebp);
    // 0x0040f147: mov dword ptr [eax + 4], ebp
    uint32_t t31 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w32(t31, ctx.ebp);
    // 0x0040f14a: mov dword ptr [eax + 8], ebp
    uint32_t t32 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    mem.w32(t32, ctx.ebp);
    // 0x0040f14d: mov dword ptr [eax + 0x18], ebp
    uint32_t t33 = static_cast<uint32_t>(ctx.eax + 0x00000018u);
    mem.w32(t33, ctx.ebp);
    // 0x0040f150: mov dword ptr [eax + 0x1c], ebp
    uint32_t t34 = static_cast<uint32_t>(ctx.eax + 0x0000001cu);
    mem.w32(t34, ctx.ebp);
    // 0x0040f153: mov dword ptr [eax + 0xc], ebp
    uint32_t t35 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    mem.w32(t35, ctx.ebp);
    // 0x0040f156: mov dword ptr [eax + 0x10], ebp
    uint32_t t36 = static_cast<uint32_t>(ctx.eax + 0x00000010u);
    mem.w32(t36, ctx.ebp);
    // 0x0040f159: mov dword ptr [eax + 0x14], ebp
    uint32_t t37 = static_cast<uint32_t>(ctx.eax + 0x00000014u);
    mem.w32(t37, ctx.ebp);
    // 0x0040f15c: mov ebx, eax
    ctx.ebx = static_cast<uint32_t>(ctx.eax);
    // 0x0040f15e: jmp 0x40f162
    goto bb_0040f162;
}
bb_0040f1a2: {
    // 0x0040f1a2: cmp ebx, ebp
    uint32_t t38 = static_cast<uint32_t>(ctx.ebx - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.ebp, t38);
    // 0x0040f1a4: je 0x40f1b6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f1b6;
    goto bb_0040f1a6;
}
bb_0040f0c0: {
    // 0x0040f0c0: mov ecx, dword ptr [edi + 4]
    uint32_t t39 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    uint32_t t40 = mem.r32(t39);
    ctx.ecx = static_cast<uint32_t>(t40);
    // 0x0040f0c3: mov edx, dword ptr [edi + 8]
    uint32_t t41 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t42 = mem.r32(t41);
    ctx.edx = static_cast<uint32_t>(t42);
    // 0x0040f0c6: mov eax, dword ptr [edi + 0xc]
    uint32_t t43 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    uint32_t t44 = mem.r32(t43);
    ctx.eax = static_cast<uint32_t>(t44);
    // 0x0040f0c9: push 0x2b9
    uint32_t t45 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    mem.w32(t45, 0x000002b9u);
    // 0x0040f0ce: push 0x535268
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, 0x00535268u);
    // 0x0040f0d3: push 4
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, 0x00000004u);
    // 0x0040f0d5: push 0x328
    uint32_t t48 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    mem.w32(t48, 0x00000328u);
    // 0x0040f0da: mov dword ptr [esp + 0x38], ecx
    uint32_t t49 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    mem.w32(t49, ctx.ecx);
    // 0x0040f0de: mov dword ptr [esp + 0x34], edx
    uint32_t t50 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    mem.w32(t50, ctx.edx);
    // 0x0040f0e2: mov dword ptr [esp + 0x30], esi
    uint32_t t51 = static_cast<uint32_t>(ctx.esp + 0x00000030u);
    mem.w32(t51, ctx.esi);
    // 0x0040f0e6: mov dword ptr [esp + 0x3c], eax
    uint32_t t52 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    mem.w32(t52, ctx.eax);
    // 0x0040f0ea: call 0x4e0675
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, 0x0040f0efu);
    hle_crt_004e0675(ctx, mem);
    // 0x0040f0ef: add esp, 0x10
    uint32_t t54 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t54);
    ctx.esp = static_cast<uint32_t>(t54);
    // 0x0040f0f2: cmp eax, ebp
    uint32_t t55 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t55);
    // 0x0040f0f4: je 0x40f101
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f101;
    goto bb_0040f0f6;
}
bb_0040f162: {
    // 0x0040f162: mov edi, dword ptr [edi]
    uint32_t t56 = mem.r32(ctx.edi);
    ctx.edi = static_cast<uint32_t>(t56);
    // 0x0040f164: mov dword ptr [esp + 0x1c], ebx
    uint32_t t57 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t57, ctx.ebx);
    // 0x0040f168: call 0x40fbf0
    uint32_t t58 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    mem.w32(t58, 0x0040f16du);
    sub_0040fbf0(ctx, mem);
    // 0x0040f16d: test eax, eax
    uint32_t t59 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t59);
    // 0x0040f16f: je 0x40f184
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f184;
    goto bb_0040f171;
}
bb_0040f1b6: {
    // 0x0040f1b6: mov eax, dword ptr [edi + 0xc]
    uint32_t t60 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    uint32_t t61 = mem.r32(t60);
    ctx.eax = static_cast<uint32_t>(t61);
    // 0x0040f1b9: cmp eax, ebp
    uint32_t t62 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t62);
    // 0x0040f1bb: je 0x40f1c5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f1c5;
    goto bb_0040f1bd;
}
bb_0040f1a6: {
    // 0x0040f1a6: mov esi, ebx
    ctx.esi = static_cast<uint32_t>(ctx.ebx);
    // 0x0040f1a8: call 0x416e30
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, 0x0040f1adu);
    sub_00416e30(ctx, mem);
    // 0x0040f1ad: push ebx
    uint32_t t64 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    mem.w32(t64, ctx.ebx);
    // 0x0040f1ae: call 0x4e02f3
    uint32_t t65 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t65);
    mem.w32(t65, 0x0040f1b3u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0040f1b3: add esp, 4
    uint32_t t66 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t66);
    ctx.esp = static_cast<uint32_t>(t66);
    goto bb_0040f1b6;
}
bb_0040f101: {
    // 0x0040f101: xor ebx, ebx
    uint32_t t67 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t67);
    ctx.ebx = static_cast<uint32_t>(t67);
    goto bb_0040f103;
}
bb_0040f0f6: {
    // 0x0040f0f6: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0040f0f8: call 0x416b50
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, 0x0040f0fdu);
    sub_00416b50(ctx, mem);
    // 0x0040f0fd: mov ebx, eax
    ctx.ebx = static_cast<uint32_t>(ctx.eax);
    // 0x0040f0ff: jmp 0x40f103
    goto bb_0040f103;
}
bb_0040f184: {
    // 0x0040f184: mov edi, dword ptr [esp + 0x34]
    uint32_t t69 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    uint32_t t70 = mem.r32(t69);
    ctx.edi = static_cast<uint32_t>(t70);
    goto bb_0040f188;
}
bb_0040f171: {
    // 0x0040f171: mov ecx, dword ptr [esp + 0x18]
    uint32_t t71 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t72 = mem.r32(t71);
    ctx.ecx = static_cast<uint32_t>(t72);
    // 0x0040f175: call 0x40ebf0
    uint32_t t73 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    mem.w32(t73, 0x0040f17au);
    sub_0040ebf0(ctx, mem);
    // 0x0040f17a: mov edi, dword ptr [esp + 0x34]
    uint32_t t74 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    uint32_t t75 = mem.r32(t74);
    ctx.edi = static_cast<uint32_t>(t75);
    goto bb_0040f17e;
}
bb_0040f1c5: {
    // 0x0040f1c5: xor eax, eax
    uint32_t t76 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t76);
    ctx.eax = static_cast<uint32_t>(t76);
    goto bb_0040f1c7;
}
bb_0040f1bd: {
    // 0x0040f1bd: mov ecx, dword ptr [edi]
    uint32_t t77 = mem.r32(ctx.edi);
    ctx.ecx = static_cast<uint32_t>(t77);
    // 0x0040f1bf: push ecx
    uint32_t t78 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    mem.w32(t78, ctx.ecx);
    // 0x0040f1c0: call eax
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, 0x0040f1c2u);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0040f1c2: add esp, 4
    uint32_t t80 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t80);
    ctx.esp = static_cast<uint32_t>(t80);
    goto bb_0040f1c5;
}
bb_0040f103: {
    // 0x0040f103: cmp ebx, ebp
    uint32_t t81 = static_cast<uint32_t>(ctx.ebx - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.ebp, t81);
    // 0x0040f105: mov dword ptr [esp + 0x14], ebx
    uint32_t t82 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t82, ctx.ebx);
    // 0x0040f109: je 0x40f1b6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f1b6;
    goto bb_0040f10f;
}
bb_0040f188: {
    // 0x0040f188: mov esi, dword ptr [esp + 0x1c]
    uint32_t t83 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t84 = mem.r32(t83);
    ctx.esi = static_cast<uint32_t>(t84);
    // 0x0040f18c: cmp esi, ebp
    uint32_t t85 = static_cast<uint32_t>(ctx.esi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebp, t85);
    // 0x0040f18e: je 0x40f19e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f19e;
    goto bb_0040f190;
}
bb_0040f17e: {
    // 0x0040f17e: cmp eax, ebp
    uint32_t t86 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t86);
    // 0x0040f180: jne 0x40f1c7
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040f1c7;
    goto bb_0040f182;
}
bb_0040f1c7: {
    // 0x0040f1c7: pop edi
    uint32_t t87 = ctx.esp;
    uint32_t t88 = mem.r32(t87);
    uint32_t t89 = static_cast<uint32_t>(t87 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t89);
    ctx.edi = static_cast<uint32_t>(t88);
    // 0x0040f1c8: pop esi
    uint32_t t90 = ctx.esp;
    uint32_t t91 = mem.r32(t90);
    uint32_t t92 = static_cast<uint32_t>(t90 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    ctx.esi = static_cast<uint32_t>(t91);
    // 0x0040f1c9: pop ebp
    uint32_t t93 = ctx.esp;
    uint32_t t94 = mem.r32(t93);
    uint32_t t95 = static_cast<uint32_t>(t93 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t95);
    ctx.ebp = static_cast<uint32_t>(t94);
    // 0x0040f1ca: pop ebx
    uint32_t t96 = ctx.esp;
    uint32_t t97 = mem.r32(t96);
    uint32_t t98 = static_cast<uint32_t>(t96 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t98);
    ctx.ebx = static_cast<uint32_t>(t97);
    // 0x0040f1cb: add esp, 0x20
    uint32_t t99 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000020u, t99);
    ctx.esp = static_cast<uint32_t>(t99);
    // 0x0040f1ce: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0040f10f: {
    // 0x0040f10f: lea ecx, [esp + 0x20]
    uint32_t t100 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    ctx.ecx = static_cast<uint32_t>(t100);
    // 0x0040f113: push ecx
    uint32_t t101 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t101);
    mem.w32(t101, ctx.ecx);
    // 0x0040f114: mov eax, ebx
    ctx.eax = static_cast<uint32_t>(ctx.ebx);
    // 0x0040f116: call 0x416c40
    uint32_t t102 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    mem.w32(t102, 0x0040f11bu);
    sub_00416c40(ctx, mem);
    // 0x0040f11b: test eax, eax
    uint32_t t103 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t103);
    // 0x0040f11d: je 0x40f19e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f19e;
    goto bb_0040f11f;
}
bb_0040f19e: {
    // 0x0040f19e: mov ebx, dword ptr [esp + 0x14]
    uint32_t t104 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t105 = mem.r32(t104);
    ctx.ebx = static_cast<uint32_t>(t105);
    goto bb_0040f1a2;
}
bb_0040f190: {
    // 0x0040f190: call 0x40fd90
    uint32_t t106 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t106);
    mem.w32(t106, 0x0040f195u);
    sub_0040fd90(ctx, mem);
    // 0x0040f195: push esi
    uint32_t t107 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t107);
    mem.w32(t107, ctx.esi);
    // 0x0040f196: call 0x4e02f3
    uint32_t t108 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t108);
    mem.w32(t108, 0x0040f19bu);
    hle_crt_004e02f3(ctx, mem);
    // 0x0040f19b: add esp, 4
    uint32_t t109 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t109);
    ctx.esp = static_cast<uint32_t>(t109);
    goto bb_0040f19e;
}
bb_0040f182: {
    // 0x0040f182: jmp 0x40f188
    goto bb_0040f188;
}
bb_0040f11f: {
    // 0x0040f11f: mov edx, dword ptr [esp + 0x18]
    uint32_t t110 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t111 = mem.r32(t110);
    ctx.edx = static_cast<uint32_t>(t111);
    // 0x0040f123: push edx
    uint32_t t112 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t112);
    mem.w32(t112, ctx.edx);
    // 0x0040f124: call 0x40ed70
    uint32_t t113 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t113);
    mem.w32(t113, 0x0040f129u);
    sub_0040ed70(ctx, mem);
    // 0x0040f129: jmp 0x40f17e
    goto bb_0040f17e;
}
}

// sub_0040f1e0 | subsystem=Sound | canonical | 9 blocks | 84 insns
void sub_0040f1e0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040f1e0: sub esp, 0x14
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000014u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000014u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x0040f1e3: xor eax, eax
    uint32_t t1 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x0040f1e5: push ebp
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebp);
    // 0x0040f1e6: mov dword ptr [esp + 4], eax
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    mem.w32(t3, ctx.eax);
    // 0x0040f1ea: mov dword ptr [esp + 8], eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    mem.w32(t4, ctx.eax);
    // 0x0040f1ee: mov dword ptr [esp + 0xc], eax
    uint32_t t5 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t5, ctx.eax);
    // 0x0040f1f2: mov dword ptr [esp + 0x10], eax
    uint32_t t6 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t6, ctx.eax);
    // 0x0040f1f6: mov dword ptr [esp + 0x14], eax
    uint32_t t7 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t7, ctx.eax);
    // 0x0040f1fa: xor ecx, ecx
    uint32_t t8 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t8);
    ctx.ecx = static_cast<uint32_t>(t8);
    // 0x0040f1fc: xor ebp, ebp
    uint32_t t9 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    ctx.ebp = static_cast<uint32_t>(t9);
    // 0x0040f1fe: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0040f203: mov edx, 4
    ctx.edx = static_cast<uint32_t>(0x00000004u);
    // 0x0040f208: mul edx
    uint64_t t10 = (static_cast<uint64_t>(ctx.eax) * static_cast<uint64_t>(ctx.edx));
    uint32_t t11 = static_cast<uint32_t>(t10);
    uint32_t t12 = static_cast<uint32_t>(t10 >> 32);
    ctx.eax = static_cast<uint32_t>(t11);
    ctx.edx = static_cast<uint32_t>(t12);
    recomp_detail::update_flags_mul<uint32_t>(ctx, t10);
    // 0x0040f20a: seto cl
    uint8_t t13 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::O) ? 1u : 0u);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t13));
    // 0x0040f20d: push 0x2e4
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x000002e4u);
    // 0x0040f212: push 0x535268
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, 0x00535268u);
    // 0x0040f217: push 4
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x00000004u);
    // 0x0040f219: mov dword ptr [esi + 0x10], 1
    uint32_t t17 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    mem.w32(t17, 0x00000001u);
    // 0x0040f220: mov dword ptr [esi + 0xc], ebp
    uint32_t t18 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t18, ctx.ebp);
    // 0x0040f223: mov dword ptr [esp + 0x10], 0x14
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t19, 0x00000014u);
    // 0x0040f22b: neg ecx
    uint32_t t20 = static_cast<uint32_t>(0u - ctx.ecx);
    recomp_detail::update_flags_neg<uint32_t>(ctx, ctx.ecx, t20);
    ctx.ecx = static_cast<uint32_t>(t20);
    // 0x0040f22d: or ecx, eax
    uint32_t t21 = static_cast<uint32_t>(ctx.ecx | ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t21);
    ctx.ecx = static_cast<uint32_t>(t21);
    // 0x0040f22f: push ecx
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, ctx.ecx);
    // 0x0040f230: call 0x4e0680
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x0040f235u);
    hle_crt_004e0680(ctx, mem);
    // 0x0040f235: add esp, 0x10
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t24);
    ctx.esp = static_cast<uint32_t>(t24);
    // 0x0040f238: cmp eax, ebp
    uint32_t t25 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t25);
    // 0x0040f23a: mov dword ptr [esi + 4], eax
    uint32_t t26 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t26, ctx.eax);
    // 0x0040f23d: je 0x40f2c1
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f2c1;
    goto bb_0040f243;
}
bb_0040f2c1: {
    // 0x0040f2c1: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0040f2c6: pop ebp
    uint32_t t27 = ctx.esp;
    uint32_t t28 = mem.r32(t27);
    uint32_t t29 = static_cast<uint32_t>(t27 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    ctx.ebp = static_cast<uint32_t>(t28);
    // 0x0040f2c7: add esp, 0x14
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000014u, t30);
    ctx.esp = static_cast<uint32_t>(t30);
    // 0x0040f2ca: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0040f243: {
    // 0x0040f243: mov ecx, dword ptr [esp + 0x1c]
    uint32_t t31 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t32 = mem.r32(t31);
    ctx.ecx = static_cast<uint32_t>(t32);
    // 0x0040f247: mov edx, dword ptr [ecx]
    uint32_t t33 = mem.r32(ctx.ecx);
    ctx.edx = static_cast<uint32_t>(t33);
    // 0x0040f249: mov dword ptr [eax], edx
    mem.w32(ctx.eax, ctx.edx);
    // 0x0040f24b: mov eax, dword ptr [esi + 4]
    uint32_t t34 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t35 = mem.r32(t34);
    ctx.eax = static_cast<uint32_t>(t35);
    // 0x0040f24e: cmp dword ptr [eax], ebp
    uint32_t t36 = mem.r32(ctx.eax);
    uint32_t t37 = static_cast<uint32_t>(t36 - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t36, ctx.ebp, t37);
    // 0x0040f250: je 0x40f268
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f268;
    goto bb_0040f252;
}
bb_0040f268: {
    // 0x0040f268: push edi
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, ctx.edi);
    // 0x0040f269: xor edi, edi
    uint32_t t39 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t39);
    ctx.edi = static_cast<uint32_t>(t39);
    // 0x0040f26b: cmp dword ptr [esi + 0x10], ebp
    uint32_t t40 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    uint32_t t41 = mem.r32(t40);
    uint32_t t42 = static_cast<uint32_t>(t41 - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t41, ctx.ebp, t42);
    // 0x0040f26e: jle 0x40f287
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0040f287;
    goto bb_0040f270;
}
bb_0040f252: {
    // 0x0040f252: mov eax, dword ptr [eax]
    uint32_t t43 = mem.r32(ctx.eax);
    ctx.eax = static_cast<uint32_t>(t43);
    // 0x0040f254: mov ecx, dword ptr [eax]
    uint32_t t44 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t44);
    // 0x0040f256: lea edx, [esp + 4]
    uint32_t t45 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    ctx.edx = static_cast<uint32_t>(t45);
    // 0x0040f25a: push edx
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, ctx.edx);
    // 0x0040f25b: push eax
    uint32_t t47 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    mem.w32(t47, ctx.eax);
    // 0x0040f25c: mov eax, dword ptr [ecx + 0xc]
    uint32_t t48 = static_cast<uint32_t>(ctx.ecx + 0x0000000cu);
    uint32_t t49 = mem.r32(t48);
    ctx.eax = static_cast<uint32_t>(t49);
    // 0x0040f25f: call eax
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, 0x0040f261u);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0040f261: mov ecx, dword ptr [esp + 0xc]
    uint32_t t51 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t52 = mem.r32(t51);
    ctx.ecx = static_cast<uint32_t>(t52);
    // 0x0040f265: add dword ptr [esi + 0xc], ecx
    uint32_t t53 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    uint32_t t54 = mem.r32(t53);
    uint32_t t55 = static_cast<uint32_t>(t54 + ctx.ecx);
    recomp_detail::update_flags_add<uint32_t>(ctx, t54, ctx.ecx, t55);
    mem.w32(t53, t55);
    goto bb_0040f268;
}
bb_0040f287: {
    // 0x0040f287: xor edi, edi
    uint32_t t56 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t56);
    ctx.edi = static_cast<uint32_t>(t56);
    // 0x0040f289: cmp dword ptr [esi + 0x10], ebp
    uint32_t t57 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    uint32_t t58 = mem.r32(t57);
    uint32_t t59 = static_cast<uint32_t>(t58 - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t58, ctx.ebp, t59);
    // 0x0040f28c: mov dword ptr [esi + 0x14], ebp
    uint32_t t60 = static_cast<uint32_t>(ctx.esi + 0x00000014u);
    mem.w32(t60, ctx.ebp);
    // 0x0040f28f: jle 0x40f2a8
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0040f2a8;
    goto bb_0040f291;
}
bb_0040f270: {
    // 0x0040f270: mov edx, dword ptr [esi + 4]
    uint32_t t61 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t62 = mem.r32(t61);
    ctx.edx = static_cast<uint32_t>(t62);
    // 0x0040f273: mov eax, dword ptr [edx + edi*4]
    uint32_t t63 = recomp_detail::shl<uint32_t>(ctx.edi, 0x00000002u);
    uint32_t t64 = static_cast<uint32_t>(ctx.edx + t63);
    uint32_t t65 = mem.r32(t64);
    ctx.eax = static_cast<uint32_t>(t65);
    // 0x0040f276: mov ecx, dword ptr [eax]
    uint32_t t66 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t66);
    // 0x0040f278: mov edx, dword ptr [ecx + 0x40]
    uint32_t t67 = static_cast<uint32_t>(ctx.ecx + 0x00000040u);
    uint32_t t68 = mem.r32(t67);
    ctx.edx = static_cast<uint32_t>(t68);
    // 0x0040f27b: push ebp
    uint32_t t69 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    mem.w32(t69, ctx.ebp);
    // 0x0040f27c: push eax
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, ctx.eax);
    // 0x0040f27d: call edx
    uint32_t t71 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t71);
    mem.w32(t71, 0x0040f27fu);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040f27f: add edi, 1
    uint32_t t72 = static_cast<uint32_t>(ctx.edi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000001u, t72);
    ctx.edi = static_cast<uint32_t>(t72);
    // 0x0040f282: cmp edi, dword ptr [esi + 0x10]
    uint32_t t73 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    uint32_t t74 = mem.r32(t73);
    uint32_t t75 = static_cast<uint32_t>(ctx.edi - t74);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, t74, t75);
    // 0x0040f285: jl 0x40f270
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040f270;
    goto bb_0040f287;
}
bb_0040f2a8: {
    // 0x0040f2a8: mov dword ptr [esi + 0x18], ebp
    uint32_t t76 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    mem.w32(t76, ctx.ebp);
    // 0x0040f2ab: mov dword ptr [esi + 0x1c], ebp
    uint32_t t77 = static_cast<uint32_t>(ctx.esi + 0x0000001cu);
    mem.w32(t77, ctx.ebp);
    // 0x0040f2ae: mov dword ptr [esi + 0x20], ebp
    uint32_t t78 = static_cast<uint32_t>(ctx.esi + 0x00000020u);
    mem.w32(t78, ctx.ebp);
    // 0x0040f2b1: mov dword ptr [esi + 0x24], ebp
    uint32_t t79 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    mem.w32(t79, ctx.ebp);
    // 0x0040f2b4: mov dword ptr [esi + 0x28], ebp
    uint32_t t80 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    mem.w32(t80, ctx.ebp);
    // 0x0040f2b7: mov dword ptr [esi + 0x2c], ebp
    uint32_t t81 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    mem.w32(t81, ctx.ebp);
    // 0x0040f2ba: mov dword ptr [esi + 0x30], ebp
    uint32_t t82 = static_cast<uint32_t>(ctx.esi + 0x00000030u);
    mem.w32(t82, ctx.ebp);
    // 0x0040f2bd: mov dword ptr [esi + 8], ebp
    uint32_t t83 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t83, ctx.ebp);
    // 0x0040f2c0: pop edi
    uint32_t t84 = ctx.esp;
    uint32_t t85 = mem.r32(t84);
    uint32_t t86 = static_cast<uint32_t>(t84 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t86);
    ctx.edi = static_cast<uint32_t>(t85);
    goto bb_0040f2c1;
}
bb_0040f291: {
    // 0x0040f291: mov eax, dword ptr [esi + 4]
    uint32_t t87 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t88 = mem.r32(t87);
    ctx.eax = static_cast<uint32_t>(t88);
    // 0x0040f294: mov eax, dword ptr [eax + edi*4]
    uint32_t t89 = recomp_detail::shl<uint32_t>(ctx.edi, 0x00000002u);
    uint32_t t90 = static_cast<uint32_t>(ctx.eax + t89);
    uint32_t t91 = mem.r32(t90);
    ctx.eax = static_cast<uint32_t>(t91);
    // 0x0040f297: mov ecx, dword ptr [eax]
    uint32_t t92 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t92);
    // 0x0040f299: mov edx, dword ptr [ecx + 0x3c]
    uint32_t t93 = static_cast<uint32_t>(ctx.ecx + 0x0000003cu);
    uint32_t t94 = mem.r32(t93);
    ctx.edx = static_cast<uint32_t>(t94);
    // 0x0040f29c: push ebp
    uint32_t t95 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t95);
    mem.w32(t95, ctx.ebp);
    // 0x0040f29d: push eax
    uint32_t t96 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    mem.w32(t96, ctx.eax);
    // 0x0040f29e: call edx
    uint32_t t97 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t97);
    mem.w32(t97, 0x0040f2a0u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040f2a0: add edi, 1
    uint32_t t98 = static_cast<uint32_t>(ctx.edi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000001u, t98);
    ctx.edi = static_cast<uint32_t>(t98);
    // 0x0040f2a3: cmp edi, dword ptr [esi + 0x10]
    uint32_t t99 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    uint32_t t100 = mem.r32(t99);
    uint32_t t101 = static_cast<uint32_t>(ctx.edi - t100);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, t100, t101);
    // 0x0040f2a6: jl 0x40f291
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040f291;
    goto bb_0040f2a8;
}
}

// sub_0040f2d0 | subsystem=Sound | canonical | 3 blocks | 11 insns
void sub_0040f2d0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040f2d0: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x0040f2d1: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x0040f2d3: call 0x40f2f0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x0040f2d8u);
    sub_0040f2f0(ctx, mem);
    // 0x0040f2d8: test byte ptr [esp + 8], 1
    uint32_t t2 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint8_t t3 = mem.r8(t2);
    uint8_t t4 = static_cast<uint8_t>(static_cast<uint32_t>(t3) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t4);
    // 0x0040f2dd: je 0x40f2e8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f2e8;
    goto bb_0040f2df;
}
bb_0040f2e8: {
    // 0x0040f2e8: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0040f2ea: pop esi
    uint32_t t5 = ctx.esp;
    uint32_t t6 = mem.r32(t5);
    uint32_t t7 = static_cast<uint32_t>(t5 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x0040f2eb: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0040f2df: {
    // 0x0040f2df: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x0040f2e0: call 0x4e02f3
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x0040f2e5u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0040f2e5: add esp, 4
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t10);
    ctx.esp = static_cast<uint32_t>(t10);
    goto bb_0040f2e8;
}
}

// sub_0040f2f0 | subsystem=Sound | canonical | 3 blocks | 25 insns
void sub_0040f2f0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040f2f0: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x0040f2f1: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x0040f2f3: cmp dword ptr [esi + 0x24], 0
    uint32_t t1 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    uint32_t t2 = mem.r32(t1);
    uint32_t t3 = static_cast<uint32_t>(t2 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t2, 0x00000000u, t3);
    // 0x0040f2f7: mov dword ptr [esi], 0x5352a8
    mem.w32(ctx.esi, 0x005352a8u);
    // 0x0040f2fd: je 0x40f339
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f339;
    goto bb_0040f2ff;
}
bb_0040f339: {
    // 0x0040f339: call 0x40f340
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x0040f33eu);
    sub_0040f340(ctx, mem);
    // 0x0040f33e: pop esi
    uint32_t t5 = ctx.esp;
    uint32_t t6 = mem.r32(t5);
    uint32_t t7 = static_cast<uint32_t>(t5 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x0040f33f: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040f2ff: {
    // 0x0040f2ff: mov ecx, dword ptr [esi + 0x28]
    uint32_t t8 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    uint32_t t9 = mem.r32(t8);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0040f302: mov eax, dword ptr [esi + 0x18]
    uint32_t t10 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    uint32_t t11 = mem.r32(t10);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x0040f305: push 0
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x00000000u);
    // 0x0040f307: push 0
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x00000000u);
    // 0x0040f309: push 0x12
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x00000012u);
    // 0x0040f30b: push ecx
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.ecx);
    // 0x0040f30c: mov dword ptr [esi + 0x2c], eax
    uint32_t t16 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    mem.w32(t16, ctx.eax);
    // 0x0040f30f: call dword ptr [0x51b244]
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x0040f315u);
    hle_iat_call(ctx, mem, 0x0051b244u);
    // 0x0040f315: mov edx, dword ptr [esi + 0x24]
    uint32_t t18 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    uint32_t t19 = mem.r32(t18);
    ctx.edx = static_cast<uint32_t>(t19);
    // 0x0040f318: push -1
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0xffffffffu);
    // 0x0040f31a: push edx
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, ctx.edx);
    // 0x0040f31b: call dword ptr [0x51b040]
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x0040f321u);
    hle_iat_call(ctx, mem, 0x0051b040u);
    // 0x0040f321: mov eax, dword ptr [esi + 0x24]
    uint32_t t23 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    uint32_t t24 = mem.r32(t23);
    ctx.eax = static_cast<uint32_t>(t24);
    // 0x0040f324: push eax
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, ctx.eax);
    // 0x0040f325: call dword ptr [0x51b1cc]
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x0040f32bu);
    hle_iat_call(ctx, mem, 0x0051b1ccu);
    // 0x0040f32b: mov dword ptr [esi + 0x24], 0
    uint32_t t27 = static_cast<uint32_t>(ctx.esi + 0x00000024u);
    mem.w32(t27, 0x00000000u);
    // 0x0040f332: mov dword ptr [esi + 0x28], 0
    uint32_t t28 = static_cast<uint32_t>(ctx.esi + 0x00000028u);
    mem.w32(t28, 0x00000000u);
    goto bb_0040f339;
}
}

// sub_0040f340 | subsystem=Sound | canonical | 7 blocks | 31 insns
void sub_0040f340(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040f340: mov eax, dword ptr [esi]
    uint32_t t0 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x0040f342: mov edx, dword ptr [eax + 4]
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t2 = mem.r32(t1);
    ctx.edx = static_cast<uint32_t>(t2);
    // 0x0040f345: push edi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.edi);
    // 0x0040f346: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x0040f348: call edx
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x0040f34au);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040f34a: xor edi, edi
    uint32_t t5 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    ctx.edi = static_cast<uint32_t>(t5);
    // 0x0040f34c: cmp dword ptr [esi + 0x10], edi
    uint32_t t6 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    uint32_t t7 = mem.r32(t6);
    uint32_t t8 = static_cast<uint32_t>(t7 - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t7, ctx.edi, t8);
    // 0x0040f34f: jle 0x40f379
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_0040f379;
    goto bb_0040f351;
}
bb_0040f379: {
    // 0x0040f379: mov eax, dword ptr [esi + 4]
    uint32_t t9 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t10 = mem.r32(t9);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0040f37c: test eax, eax
    uint32_t t11 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    // 0x0040f37e: pop edi
    uint32_t t12 = ctx.esp;
    uint32_t t13 = mem.r32(t12);
    uint32_t t14 = static_cast<uint32_t>(t12 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    ctx.edi = static_cast<uint32_t>(t13);
    // 0x0040f37f: je 0x40f391
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f391;
    goto bb_0040f381;
}
bb_0040f351: {
    // 0x0040f351: mov eax, dword ptr [esi + 4]
    uint32_t t15 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t16 = mem.r32(t15);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0040f354: cmp dword ptr [eax + edi*4], 0
    uint32_t t17 = recomp_detail::shl<uint32_t>(ctx.edi, 0x00000002u);
    uint32_t t18 = static_cast<uint32_t>(ctx.eax + t17);
    uint32_t t19 = mem.r32(t18);
    uint32_t t20 = static_cast<uint32_t>(t19 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t19, 0x00000000u, t20);
    // 0x0040f358: lea eax, [eax + edi*4]
    uint32_t t21 = recomp_detail::shl<uint32_t>(ctx.edi, 0x00000002u);
    uint32_t t22 = static_cast<uint32_t>(ctx.eax + t21);
    ctx.eax = static_cast<uint32_t>(t22);
    // 0x0040f35b: je 0x40f371
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f371;
    goto bb_0040f35d;
}
bb_0040f391: {
    // 0x0040f391: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040f381: {
    // 0x0040f381: push eax
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, ctx.eax);
    // 0x0040f382: call 0x4e0307
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x0040f387u);
    hle_crt_004e0307(ctx, mem);
    // 0x0040f387: add esp, 4
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t25);
    ctx.esp = static_cast<uint32_t>(t25);
    // 0x0040f38a: mov dword ptr [esi + 4], 0
    uint32_t t26 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t26, 0x00000000u);
    goto bb_0040f391;
}
bb_0040f371: {
    // 0x0040f371: add edi, 1
    uint32_t t27 = static_cast<uint32_t>(ctx.edi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000001u, t27);
    ctx.edi = static_cast<uint32_t>(t27);
    // 0x0040f374: cmp edi, dword ptr [esi + 0x10]
    uint32_t t28 = static_cast<uint32_t>(ctx.esi + 0x00000010u);
    uint32_t t29 = mem.r32(t28);
    uint32_t t30 = static_cast<uint32_t>(ctx.edi - t29);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, t29, t30);
    // 0x0040f377: jl 0x40f351
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_0040f351;
    goto bb_0040f379;
}
bb_0040f35d: {
    // 0x0040f35d: mov eax, dword ptr [eax]
    uint32_t t31 = mem.r32(ctx.eax);
    ctx.eax = static_cast<uint32_t>(t31);
    // 0x0040f35f: mov ecx, dword ptr [eax]
    uint32_t t32 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t32);
    // 0x0040f361: mov edx, dword ptr [ecx + 8]
    uint32_t t33 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t34 = mem.r32(t33);
    ctx.edx = static_cast<uint32_t>(t34);
    // 0x0040f364: push eax
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, ctx.eax);
    // 0x0040f365: call edx
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, 0x0040f367u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040f367: mov eax, dword ptr [esi + 4]
    uint32_t t37 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t38 = mem.r32(t37);
    ctx.eax = static_cast<uint32_t>(t38);
    // 0x0040f36a: mov dword ptr [eax + edi*4], 0
    uint32_t t39 = recomp_detail::shl<uint32_t>(ctx.edi, 0x00000002u);
    uint32_t t40 = static_cast<uint32_t>(ctx.eax + t39);
    mem.w32(t40, 0x00000000u);
    goto bb_0040f371;
}
}

// sub_0040f3a0 | subsystem=Sound | canonical | 3 blocks | 41 insns
void sub_0040f3a0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040f3a0: mov eax, dword ptr [edi + 4]
    uint32_t t0 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    uint32_t t1 = mem.r32(t0);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x0040f3a3: push esi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.esi);
    // 0x0040f3a4: mov esi, dword ptr [eax]
    uint32_t t3 = mem.r32(ctx.eax);
    ctx.esi = static_cast<uint32_t>(t3);
    // 0x0040f3a6: test esi, esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    // 0x0040f3a8: jne 0x40f3b1
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040f3b1;
    goto bb_0040f3aa;
}
bb_0040f3b1: {
    // 0x0040f3b1: call 0x40f4a0
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, 0x0040f3b6u);
    sub_0040f4a0(ctx, mem);
    // 0x0040f3b6: mov edx, dword ptr [edi]
    uint32_t t6 = mem.r32(ctx.edi);
    ctx.edx = static_cast<uint32_t>(t6);
    // 0x0040f3b8: mov eax, dword ptr [edx + 4]
    uint32_t t7 = static_cast<uint32_t>(ctx.edx + 0x00000004u);
    uint32_t t8 = mem.r32(t7);
    ctx.eax = static_cast<uint32_t>(t8);
    // 0x0040f3bb: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x0040f3bd: call eax
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x0040f3bfu);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0040f3bf: mov dword ptr [edi + 8], 0
    uint32_t t10 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    mem.w32(t10, 0x00000000u);
    // 0x0040f3c6: mov ecx, dword ptr [esi]
    uint32_t t11 = mem.r32(ctx.esi);
    ctx.ecx = static_cast<uint32_t>(t11);
    // 0x0040f3c8: mov edx, dword ptr [ecx + 0x34]
    uint32_t t12 = static_cast<uint32_t>(ctx.ecx + 0x00000034u);
    uint32_t t13 = mem.r32(t12);
    ctx.edx = static_cast<uint32_t>(t13);
    // 0x0040f3cb: push 0
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x00000000u);
    // 0x0040f3cd: push esi
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.esi);
    // 0x0040f3ce: call edx
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x0040f3d0u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040f3d0: mov ecx, dword ptr [edi + 0x18]
    uint32_t t17 = static_cast<uint32_t>(ctx.edi + 0x00000018u);
    uint32_t t18 = mem.r32(t17);
    ctx.ecx = static_cast<uint32_t>(t18);
    // 0x0040f3d3: mov eax, dword ptr [esi]
    uint32_t t19 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t19);
    // 0x0040f3d5: mov edx, dword ptr [eax + 0x3c]
    uint32_t t20 = static_cast<uint32_t>(ctx.eax + 0x0000003cu);
    uint32_t t21 = mem.r32(t20);
    ctx.edx = static_cast<uint32_t>(t21);
    // 0x0040f3d8: push ecx
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, ctx.ecx);
    // 0x0040f3d9: push esi
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, ctx.esi);
    // 0x0040f3da: call edx
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x0040f3dcu);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040f3dc: mov ecx, dword ptr [edi + 0x14]
    uint32_t t25 = static_cast<uint32_t>(ctx.edi + 0x00000014u);
    uint32_t t26 = mem.r32(t25);
    ctx.ecx = static_cast<uint32_t>(t26);
    // 0x0040f3df: mov eax, dword ptr [esi]
    uint32_t t27 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t27);
    // 0x0040f3e1: mov edx, dword ptr [eax + 0x40]
    uint32_t t28 = static_cast<uint32_t>(ctx.eax + 0x00000040u);
    uint32_t t29 = mem.r32(t28);
    ctx.edx = static_cast<uint32_t>(t29);
    // 0x0040f3e4: push ecx
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, ctx.ecx);
    // 0x0040f3e5: push esi
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, ctx.esi);
    // 0x0040f3e6: call edx
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x0040f3e8u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040f3e8: mov ecx, dword ptr [edi + 0x1c]
    uint32_t t33 = static_cast<uint32_t>(ctx.edi + 0x0000001cu);
    uint32_t t34 = mem.r32(t33);
    ctx.ecx = static_cast<uint32_t>(t34);
    // 0x0040f3eb: mov eax, dword ptr [esi]
    uint32_t t35 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t35);
    // 0x0040f3ed: mov edx, dword ptr [eax + 0x30]
    uint32_t t36 = static_cast<uint32_t>(ctx.eax + 0x00000030u);
    uint32_t t37 = mem.r32(t36);
    ctx.edx = static_cast<uint32_t>(t37);
    // 0x0040f3f0: push ecx
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, ctx.ecx);
    // 0x0040f3f1: push 0
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, 0x00000000u);
    // 0x0040f3f3: push 0
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, 0x00000000u);
    // 0x0040f3f5: push esi
    uint32_t t41 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    mem.w32(t41, ctx.esi);
    // 0x0040f3f6: call edx
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, 0x0040f3f8u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040f3f8: pop esi
    uint32_t t43 = ctx.esp;
    uint32_t t44 = mem.r32(t43);
    uint32_t t45 = static_cast<uint32_t>(t43 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    ctx.esi = static_cast<uint32_t>(t44);
    // 0x0040f3f9: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040f3aa: {
    // 0x0040f3aa: mov eax, 0x800401f0
    ctx.eax = static_cast<uint32_t>(0x800401f0u);
    // 0x0040f3af: pop esi
    uint32_t t46 = ctx.esp;
    uint32_t t47 = mem.r32(t46);
    uint32_t t48 = static_cast<uint32_t>(t46 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    ctx.esi = static_cast<uint32_t>(t47);
    // 0x0040f3b0: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0040f400 | subsystem=Sound | canonical | 3 blocks | 11 insns
void sub_0040f400(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040f400: mov eax, dword ptr [ecx + 4]
    uint32_t t0 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    uint32_t t1 = mem.r32(t0);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x0040f403: mov eax, dword ptr [eax]
    uint32_t t2 = mem.r32(ctx.eax);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x0040f405: test eax, eax
    uint32_t t3 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t3);
    // 0x0040f407: jne 0x40f40f
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040f40f;
    goto bb_0040f409;
}
bb_0040f40f: {
    // 0x0040f40f: mov ecx, dword ptr [eax]
    uint32_t t4 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x0040f411: mov edx, dword ptr [ecx + 0x48]
    uint32_t t5 = static_cast<uint32_t>(ctx.ecx + 0x00000048u);
    uint32_t t6 = mem.r32(t5);
    ctx.edx = static_cast<uint32_t>(t6);
    // 0x0040f414: push eax
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.eax);
    // 0x0040f415: call edx
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x0040f417u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040f417: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040f409: {
    // 0x0040f409: mov eax, 0x800401f0
    ctx.eax = static_cast<uint32_t>(0x800401f0u);
    // 0x0040f40e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0040f4a0 | subsystem=Sound | canonical | 7 blocks | 39 insns
void sub_0040f4a0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040f4a0: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x0040f4a1: mov eax, dword ptr [esi]
    uint32_t t1 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x0040f4a3: mov edx, dword ptr [eax + 0x24]
    uint32_t t2 = static_cast<uint32_t>(ctx.eax + 0x00000024u);
    uint32_t t3 = mem.r32(t2);
    ctx.edx = static_cast<uint32_t>(t3);
    // 0x0040f4a6: lea ecx, [esp]
    ctx.ecx = static_cast<uint32_t>(ctx.esp);
    // 0x0040f4a9: push ecx
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.ecx);
    // 0x0040f4aa: push esi
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.esi);
    // 0x0040f4ab: call edx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x0040f4adu);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040f4ad: test byte ptr [esp], 2
    uint8_t t7 = mem.r8(ctx.esp);
    uint8_t t8 = static_cast<uint8_t>(static_cast<uint32_t>(t7) & static_cast<uint32_t>(uint8_t{0x02u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t8);
    // 0x0040f4b1: je 0x40f4f1
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f4f1;
    goto bb_0040f4b3;
}
bb_0040f4f1: {
    // 0x0040f4f1: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0040f4f6: pop ecx
    uint32_t t9 = ctx.esp;
    uint32_t t10 = mem.r32(t9);
    uint32_t t11 = static_cast<uint32_t>(t9 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    ctx.ecx = static_cast<uint32_t>(t10);
    // 0x0040f4f7: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040f4b3: {
    // 0x0040f4b3: mov eax, dword ptr [esi]
    uint32_t t12 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0040f4b5: mov ecx, dword ptr [eax + 0x50]
    uint32_t t13 = static_cast<uint32_t>(ctx.eax + 0x00000050u);
    uint32_t t14 = mem.r32(t13);
    ctx.ecx = static_cast<uint32_t>(t14);
    // 0x0040f4b8: push ebx
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.ebx);
    // 0x0040f4b9: push edi
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, ctx.edi);
    // 0x0040f4ba: push esi
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, ctx.esi);
    // 0x0040f4bb: xor edi, edi
    uint32_t t18 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    ctx.edi = static_cast<uint32_t>(t18);
    // 0x0040f4bd: call ecx
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x0040f4bfu);
    call_indirect(ctx, mem, ctx.ecx);
    // 0x0040f4bf: cmp eax, 0x88780096
    uint32_t t20 = static_cast<uint32_t>(ctx.eax - 0x88780096u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x88780096u, t20);
    // 0x0040f4c4: jne 0x40f4eb
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040f4eb;
    goto bb_0040f4c6;
}
bb_0040f4eb: {
    // 0x0040f4eb: pop edi
    uint32_t t21 = ctx.esp;
    uint32_t t22 = mem.r32(t21);
    uint32_t t23 = static_cast<uint32_t>(t21 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    ctx.edi = static_cast<uint32_t>(t22);
    // 0x0040f4ec: xor eax, eax
    uint32_t t24 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t24);
    ctx.eax = static_cast<uint32_t>(t24);
    // 0x0040f4ee: pop ebx
    uint32_t t25 = ctx.esp;
    uint32_t t26 = mem.r32(t25);
    uint32_t t27 = static_cast<uint32_t>(t25 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    ctx.ebx = static_cast<uint32_t>(t26);
    // 0x0040f4ef: pop ecx
    uint32_t t28 = ctx.esp;
    uint32_t t29 = mem.r32(t28);
    uint32_t t30 = static_cast<uint32_t>(t28 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    ctx.ecx = static_cast<uint32_t>(t29);
    // 0x0040f4f0: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040f4c6: {
    // 0x0040f4c6: mov ebx, dword ptr [0x51b1d0]
    uint32_t t31 = mem.r32(0x0051b1d0u);
    ctx.ebx = static_cast<uint32_t>(t31);
    // 0x0040f4cc: lea esp, [esp]
    ctx.esp = static_cast<uint32_t>(ctx.esp);
}
bb_0040f4d0: {
    // 0x0040f4d0: push 0xa
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x0000000au);
    // 0x0040f4d2: call ebx
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x0040f4d4u);
    call_indirect(ctx, mem, ctx.ebx);
    // 0x0040f4d4: cmp edi, 0x14
    uint32_t t34 = static_cast<uint32_t>(ctx.edi - 0x00000014u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, 0x00000014u, t34);
    // 0x0040f4d7: jg 0x40f4eb
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0040f4eb;
}
{
    // 0x0040f4d9: mov edx, dword ptr [esi]
    uint32_t t35 = mem.r32(ctx.esi);
    ctx.edx = static_cast<uint32_t>(t35);
    // 0x0040f4db: mov eax, dword ptr [edx + 0x50]
    uint32_t t36 = static_cast<uint32_t>(ctx.edx + 0x00000050u);
    uint32_t t37 = mem.r32(t36);
    ctx.eax = static_cast<uint32_t>(t37);
    // 0x0040f4de: push esi
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, ctx.esi);
    // 0x0040f4df: add edi, 1
    uint32_t t39 = static_cast<uint32_t>(ctx.edi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000001u, t39);
    ctx.edi = static_cast<uint32_t>(t39);
    // 0x0040f4e2: call eax
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, 0x0040f4e4u);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0040f4e4: cmp eax, 0x88780096
    uint32_t t41 = static_cast<uint32_t>(ctx.eax - 0x88780096u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x88780096u, t41);
    // 0x0040f4e9: je 0x40f4d0
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f4d0;
    goto bb_0040f4eb;
}
}

// sub_0040f500 | subsystem=Sound | canonical | 5 blocks | 77 insns
void sub_0040f500(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040f500: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x0040f501: push ebp
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebp);
    // 0x0040f502: push esi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.esi);
    // 0x0040f503: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0040f505: mov eax, dword ptr [esi + 4]
    uint32_t t3 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t4 = mem.r32(t3);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0040f508: push edi
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.edi);
    // 0x0040f509: xor ebp, ebp
    uint32_t t6 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t6);
    ctx.ebp = static_cast<uint32_t>(t6);
    // 0x0040f50b: lea edx, [esp + 0xc]
    uint32_t t7 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    ctx.edx = static_cast<uint32_t>(t7);
    // 0x0040f50f: mov dword ptr [esp + 0xc], ebp
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t8, ctx.ebp);
    // 0x0040f513: mov dword ptr [esi + 0x70], ebp
    uint32_t t9 = static_cast<uint32_t>(ctx.esi + 0x00000070u);
    mem.w32(t9, ctx.ebp);
    // 0x0040f516: mov eax, dword ptr [eax]
    uint32_t t10 = mem.r32(ctx.eax);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0040f518: mov ecx, dword ptr [eax]
    uint32_t t11 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t11);
    // 0x0040f51a: push edx
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.edx);
    // 0x0040f51b: push 0x51b654
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x0051b654u);
    // 0x0040f520: push eax
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, ctx.eax);
    // 0x0040f521: mov eax, dword ptr [ecx]
    uint32_t t15 = mem.r32(ctx.ecx);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x0040f523: call eax
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x0040f525u);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0040f525: push 0x42c
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x0000042cu);
    // 0x0040f52a: push 0x535268
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x00535268u);
    // 0x0040f52f: push 4
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x00000004u);
    // 0x0040f531: push 0x28
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x00000028u);
    // 0x0040f533: call 0x4e0680
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x0040f538u);
    hle_crt_004e0680(ctx, mem);
    // 0x0040f538: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x0040f53a: mov eax, dword ptr [esi + 0x48]
    uint32_t t22 = static_cast<uint32_t>(ctx.esi + 0x00000048u);
    uint32_t t23 = mem.r32(t22);
    ctx.eax = static_cast<uint32_t>(t23);
    // 0x0040f53d: lea ecx, [eax + eax*2]
    uint32_t t24 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000001u);
    uint32_t t25 = static_cast<uint32_t>(ctx.eax + t24);
    ctx.ecx = static_cast<uint32_t>(t25);
    // 0x0040f540: add esp, 0x10
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t26);
    ctx.esp = static_cast<uint32_t>(t26);
    // 0x0040f543: cmp ebx, ecx
    uint32_t t27 = static_cast<uint32_t>(ctx.ebx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.ecx, t27);
    // 0x0040f545: sbb edx, edx
    uint32_t t28 = recomp_detail::get_flag(ctx, kFlagCF);
    uint32_t t29 = static_cast<uint32_t>(ctx.edx - ctx.edx);
    uint32_t t30 = static_cast<uint32_t>(t29 - t28);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.edx, t30, t28);
    ctx.edx = static_cast<uint32_t>(t30);
    // 0x0040f547: neg edx
    uint32_t t31 = static_cast<uint32_t>(0u - ctx.edx);
    recomp_detail::update_flags_neg<uint32_t>(ctx, ctx.edx, t31);
    ctx.edx = static_cast<uint32_t>(t31);
    // 0x0040f549: add edx, 4
    uint32_t t32 = static_cast<uint32_t>(ctx.edx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000004u, t32);
    ctx.edx = static_cast<uint32_t>(t32);
    // 0x0040f54c: mov dword ptr [esi + 0x70], edx
    uint32_t t33 = static_cast<uint32_t>(ctx.esi + 0x00000070u);
    mem.w32(t33, ctx.edx);
    // 0x0040f54f: mov dword ptr [edi], ebp
    mem.w32(ctx.edi, ctx.ebp);
    // 0x0040f551: mov eax, dword ptr [esi + 0x5c]
    uint32_t t34 = static_cast<uint32_t>(ctx.esi + 0x0000005cu);
    uint32_t t35 = mem.r32(t34);
    ctx.eax = static_cast<uint32_t>(t35);
    // 0x0040f554: mov dword ptr [edi + 4], eax
    uint32_t t36 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    mem.w32(t36, ctx.eax);
    // 0x0040f557: mov ecx, dword ptr [esi + 0x48]
    uint32_t t37 = static_cast<uint32_t>(ctx.esi + 0x00000048u);
    uint32_t t38 = mem.r32(t37);
    ctx.ecx = static_cast<uint32_t>(t38);
    // 0x0040f55a: mov dword ptr [edi + 8], ecx
    uint32_t t39 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    mem.w32(t39, ctx.ecx);
    // 0x0040f55d: mov edx, dword ptr [esi + 0x60]
    uint32_t t40 = static_cast<uint32_t>(ctx.esi + 0x00000060u);
    uint32_t t41 = mem.r32(t40);
    ctx.edx = static_cast<uint32_t>(t41);
    // 0x0040f560: mov dword ptr [edi + 0xc], edx
    uint32_t t42 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    mem.w32(t42, ctx.edx);
    // 0x0040f563: mov eax, dword ptr [esi + 0x48]
    uint32_t t43 = static_cast<uint32_t>(ctx.esi + 0x00000048u);
    uint32_t t44 = mem.r32(t43);
    ctx.eax = static_cast<uint32_t>(t44);
    // 0x0040f566: add eax, eax
    uint32_t t45 = static_cast<uint32_t>(ctx.eax + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.eax, t45);
    ctx.eax = static_cast<uint32_t>(t45);
    // 0x0040f568: mov dword ptr [edi + 0x10], eax
    uint32_t t46 = static_cast<uint32_t>(ctx.edi + 0x00000010u);
    mem.w32(t46, ctx.eax);
    // 0x0040f56b: mov ecx, dword ptr [esi + 0x64]
    uint32_t t47 = static_cast<uint32_t>(ctx.esi + 0x00000064u);
    uint32_t t48 = mem.r32(t47);
    ctx.ecx = static_cast<uint32_t>(t48);
    // 0x0040f56e: mov dword ptr [edi + 0x14], ecx
    uint32_t t49 = static_cast<uint32_t>(ctx.edi + 0x00000014u);
    mem.w32(t49, ctx.ecx);
    // 0x0040f571: mov dword ptr [edi + 0x18], 0xffffffff
    uint32_t t50 = static_cast<uint32_t>(ctx.edi + 0x00000018u);
    mem.w32(t50, 0xffffffffu);
    // 0x0040f578: mov edx, dword ptr [esi + 0x68]
    uint32_t t51 = static_cast<uint32_t>(ctx.esi + 0x00000068u);
    uint32_t t52 = mem.r32(t51);
    ctx.edx = static_cast<uint32_t>(t52);
    // 0x0040f57b: mov dword ptr [edi + 0x1c], edx
    uint32_t t53 = static_cast<uint32_t>(ctx.edi + 0x0000001cu);
    mem.w32(t53, ctx.edx);
    // 0x0040f57e: mov dword ptr [edi + 0x20], ebx
    uint32_t t54 = static_cast<uint32_t>(ctx.edi + 0x00000020u);
    mem.w32(t54, ctx.ebx);
    // 0x0040f581: mov eax, dword ptr [esi + 0x6c]
    uint32_t t55 = static_cast<uint32_t>(ctx.esi + 0x0000006cu);
    uint32_t t56 = mem.r32(t55);
    ctx.eax = static_cast<uint32_t>(t56);
    // 0x0040f584: mov dword ptr [edi + 0x24], eax
    uint32_t t57 = static_cast<uint32_t>(ctx.edi + 0x00000024u);
    mem.w32(t57, ctx.eax);
    // 0x0040f587: mov eax, dword ptr [esp + 0xc]
    uint32_t t58 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t59 = mem.r32(t58);
    ctx.eax = static_cast<uint32_t>(t59);
    // 0x0040f58b: mov esi, dword ptr [esi + 0x70]
    uint32_t t60 = static_cast<uint32_t>(ctx.esi + 0x00000070u);
    uint32_t t61 = mem.r32(t60);
    ctx.esi = static_cast<uint32_t>(t61);
    // 0x0040f58e: mov ecx, dword ptr [eax]
    uint32_t t62 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t62);
    // 0x0040f590: mov edx, dword ptr [ecx + 0xc]
    uint32_t t63 = static_cast<uint32_t>(ctx.ecx + 0x0000000cu);
    uint32_t t64 = mem.r32(t63);
    ctx.edx = static_cast<uint32_t>(t64);
    // 0x0040f593: push edi
    uint32_t t65 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t65);
    mem.w32(t65, ctx.edi);
    // 0x0040f594: push esi
    uint32_t t66 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    mem.w32(t66, ctx.esi);
    // 0x0040f595: push eax
    uint32_t t67 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t67);
    mem.w32(t67, ctx.eax);
    // 0x0040f596: call edx
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, 0x0040f598u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040f598: test eax, eax
    uint32_t t69 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t69);
    // 0x0040f59a: jne 0x40f59f
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040f59f;
    goto bb_0040f59c;
}
bb_0040f59f: {
    // 0x0040f59f: mov eax, dword ptr [esp + 0xc]
    uint32_t t70 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t71 = mem.r32(t70);
    ctx.eax = static_cast<uint32_t>(t71);
    // 0x0040f5a3: test eax, eax
    uint32_t t72 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t72);
    // 0x0040f5a5: je 0x40f5b7
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f5b7;
    goto bb_0040f5a7;
}
bb_0040f59c: {
    // 0x0040f59c: lea ebp, [eax + 1]
    uint32_t t73 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.ebp = static_cast<uint32_t>(t73);
    goto bb_0040f59f;
}
bb_0040f5b7: {
    // 0x0040f5b7: push edi
    uint32_t t74 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    mem.w32(t74, ctx.edi);
    // 0x0040f5b8: call 0x4e0307
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, 0x0040f5bdu);
    hle_crt_004e0307(ctx, mem);
    // 0x0040f5bd: add esp, 4
    uint32_t t76 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t76);
    ctx.esp = static_cast<uint32_t>(t76);
    // 0x0040f5c0: pop edi
    uint32_t t77 = ctx.esp;
    uint32_t t78 = mem.r32(t77);
    uint32_t t79 = static_cast<uint32_t>(t77 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    ctx.edi = static_cast<uint32_t>(t78);
    // 0x0040f5c1: pop esi
    uint32_t t80 = ctx.esp;
    uint32_t t81 = mem.r32(t80);
    uint32_t t82 = static_cast<uint32_t>(t80 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t82);
    ctx.esi = static_cast<uint32_t>(t81);
    // 0x0040f5c2: mov eax, ebp
    ctx.eax = static_cast<uint32_t>(ctx.ebp);
    // 0x0040f5c4: pop ebp
    uint32_t t83 = ctx.esp;
    uint32_t t84 = mem.r32(t83);
    uint32_t t85 = static_cast<uint32_t>(t83 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t85);
    ctx.ebp = static_cast<uint32_t>(t84);
    // 0x0040f5c5: pop ecx
    uint32_t t86 = ctx.esp;
    uint32_t t87 = mem.r32(t86);
    uint32_t t88 = static_cast<uint32_t>(t86 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t88);
    ctx.ecx = static_cast<uint32_t>(t87);
    // 0x0040f5c6: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040f5a7: {
    // 0x0040f5a7: mov ecx, dword ptr [eax]
    uint32_t t89 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t89);
    // 0x0040f5a9: mov edx, dword ptr [ecx + 8]
    uint32_t t90 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t91 = mem.r32(t90);
    ctx.edx = static_cast<uint32_t>(t91);
    // 0x0040f5ac: push eax
    uint32_t t92 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    mem.w32(t92, ctx.eax);
    // 0x0040f5ad: call edx
    uint32_t t93 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    mem.w32(t93, 0x0040f5afu);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040f5af: mov dword ptr [esp + 0xc], 0
    uint32_t t94 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t94, 0x00000000u);
    goto bb_0040f5b7;
}
}

// sub_0040f5d0 | subsystem=Sound | canonical | 3 blocks | 37 insns
void sub_0040f5d0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040f5d0: push ebx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebx);
    // 0x0040f5d1: xor ebx, ebx
    uint32_t t1 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.ebx = static_cast<uint32_t>(t1);
    // 0x0040f5d3: push ebp
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ebp);
    // 0x0040f5d4: mov dword ptr [esi + 0x48], eax
    uint32_t t3 = static_cast<uint32_t>(ctx.esi + 0x00000048u);
    mem.w32(t3, ctx.eax);
    // 0x0040f5d7: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0040f5dc: push edi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.edi);
    // 0x0040f5dd: mov dword ptr [esi + 0x34], ebx
    uint32_t t5 = static_cast<uint32_t>(ctx.esi + 0x00000034u);
    mem.w32(t5, ctx.ebx);
    // 0x0040f5e0: mov dword ptr [esi + 0x38], ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.esi + 0x00000038u);
    mem.w32(t6, ctx.ebx);
    // 0x0040f5e3: mov byte ptr [esi + 0x3c], bl
    uint32_t t7 = static_cast<uint32_t>(ctx.esi + 0x0000003cu);
    mem.w8(t7, recomp_detail::r8l(ctx.ebx));
    // 0x0040f5e6: mov dword ptr [esi + 0x50], ebx
    uint32_t t8 = static_cast<uint32_t>(ctx.esi + 0x00000050u);
    mem.w32(t8, ctx.ebx);
    // 0x0040f5e9: mov dword ptr [esi + 0x44], ebx
    uint32_t t9 = static_cast<uint32_t>(ctx.esi + 0x00000044u);
    mem.w32(t9, ctx.ebx);
    // 0x0040f5ec: mov dword ptr [esi + 0x4c], ebx
    uint32_t t10 = static_cast<uint32_t>(ctx.esi + 0x0000004cu);
    mem.w32(t10, ctx.ebx);
    // 0x0040f5ef: mov dword ptr [esi + 0x78], ebx
    uint32_t t11 = static_cast<uint32_t>(ctx.esi + 0x00000078u);
    mem.w32(t11, ctx.ebx);
    // 0x0040f5f2: mov dword ptr [esi + 0x74], ebx
    uint32_t t12 = static_cast<uint32_t>(ctx.esi + 0x00000074u);
    mem.w32(t12, ctx.ebx);
    // 0x0040f5f5: mov dword ptr [esi + 0x90], ebx
    uint32_t t13 = static_cast<uint32_t>(ctx.esi + 0x00000090u);
    mem.w32(t13, ctx.ebx);
    // 0x0040f5fb: mov dword ptr [esi + 0x1c], eax
    uint32_t t14 = static_cast<uint32_t>(ctx.esi + 0x0000001cu);
    mem.w32(t14, ctx.eax);
    // 0x0040f5fe: mov dword ptr [esi + 0x80], eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esi + 0x00000080u);
    mem.w32(t15, ctx.eax);
    // 0x0040f604: mov dword ptr [esi + 0x58], 0xffffffff
    uint32_t t16 = static_cast<uint32_t>(ctx.esi + 0x00000058u);
    mem.w32(t16, 0xffffffffu);
    // 0x0040f60b: lea edi, [esi + 0x5c]
    uint32_t t17 = static_cast<uint32_t>(ctx.esi + 0x0000005cu);
    ctx.edi = static_cast<uint32_t>(t17);
    // 0x0040f60e: lea ebp, [ebx + 5]
    uint32_t t18 = static_cast<uint32_t>(ctx.ebx + 0x00000005u);
    ctx.ebp = static_cast<uint32_t>(t18);
}
bb_0040f611: {
    // 0x0040f611: push ebx
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, ctx.ebx);
    // 0x0040f612: push ebx
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, ctx.ebx);
    // 0x0040f613: push ebx
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, ctx.ebx);
    // 0x0040f614: push ebx
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, ctx.ebx);
    // 0x0040f615: call dword ptr [0x51b048]
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x0040f61bu);
    hle_iat_call(ctx, mem, 0x0051b048u);
    // 0x0040f61b: mov dword ptr [edi], eax
    mem.w32(ctx.edi, ctx.eax);
    // 0x0040f61d: add edi, 4
    uint32_t t24 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000004u, t24);
    ctx.edi = static_cast<uint32_t>(t24);
    // 0x0040f620: sub ebp, 1
    uint32_t t25 = static_cast<uint32_t>(ctx.ebp - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebp, 0x00000001u, t25);
    ctx.ebp = static_cast<uint32_t>(t25);
    // 0x0040f623: jne 0x40f611
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040f611;
}
{
    // 0x0040f625: mov eax, dword ptr [esi + 0x48]
    uint32_t t26 = static_cast<uint32_t>(ctx.esi + 0x00000048u);
    uint32_t t27 = mem.r32(t26);
    ctx.eax = static_cast<uint32_t>(t27);
    // 0x0040f628: lea ebx, [eax + eax*2 + 1]
    uint32_t t28 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000001u);
    uint32_t t29 = static_cast<uint32_t>(ctx.eax + t28);
    uint32_t t30 = static_cast<uint32_t>(t29 + 0x00000001u);
    ctx.ebx = static_cast<uint32_t>(t30);
    // 0x0040f62c: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0040f62e: call 0x40f500
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x0040f633u);
    sub_0040f500(ctx, mem);
    // 0x0040f633: pop edi
    uint32_t t32 = ctx.esp;
    uint32_t t33 = mem.r32(t32);
    uint32_t t34 = static_cast<uint32_t>(t32 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    ctx.edi = static_cast<uint32_t>(t33);
    // 0x0040f634: pop ebp
    uint32_t t35 = ctx.esp;
    uint32_t t36 = mem.r32(t35);
    uint32_t t37 = static_cast<uint32_t>(t35 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    ctx.ebp = static_cast<uint32_t>(t36);
    // 0x0040f635: pop ebx
    uint32_t t38 = ctx.esp;
    uint32_t t39 = mem.r32(t38);
    uint32_t t40 = static_cast<uint32_t>(t38 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    ctx.ebx = static_cast<uint32_t>(t39);
    // 0x0040f636: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0040f640 | subsystem=Sound | canonical | 1 blocks | 40 insns
void sub_0040f640(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040f640: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0040f642: push 0x5148d8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005148d8u);
    // 0x0040f647: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0040f64d: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0040f64e: push esi
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.esi);
    // 0x0040f64f: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0040f654: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0040f656: push eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.eax);
    // 0x0040f657: lea eax, [esp + 8]
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x0040f65b: mov dword ptr fs:[0], eax
    uint32_t t10 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t10, ctx.eax);
    // 0x0040f661: mov esi, dword ptr [esp + 0x18]
    uint32_t t11 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t12 = mem.r32(t11);
    ctx.esi = static_cast<uint32_t>(t12);
    // 0x0040f665: mov eax, dword ptr [esp + 0x1c]
    uint32_t t13 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t14 = mem.r32(t13);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x0040f669: push eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.eax);
    // 0x0040f66a: mov dword ptr [esi], 0x5352a8
    mem.w32(ctx.esi, 0x005352a8u);
    // 0x0040f670: call 0x40f1e0
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x0040f675u);
    sub_0040f1e0(ctx, mem);
    // 0x0040f675: mov eax, dword ptr [esp + 0x24]
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t18 = mem.r32(t17);
    ctx.eax = static_cast<uint32_t>(t18);
    // 0x0040f679: mov dword ptr [esp + 0x10], 0
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t19, 0x00000000u);
    // 0x0040f681: mov dword ptr [esi], 0x5352b4
    mem.w32(ctx.esi, 0x005352b4u);
    // 0x0040f687: call 0x40f5d0
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x0040f68cu);
    sub_0040f5d0(ctx, mem);
    // 0x0040f68c: mov ecx, dword ptr [esp + 0x20]
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t22 = mem.r32(t21);
    ctx.ecx = static_cast<uint32_t>(t22);
    // 0x0040f690: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0040f692: mov dword ptr [esi + 0x54], 1
    uint32_t t23 = static_cast<uint32_t>(ctx.esi + 0x00000054u);
    mem.w32(t23, 0x00000001u);
    // 0x0040f699: mov dword ptr [esi + 0x34], ecx
    uint32_t t24 = static_cast<uint32_t>(ctx.esi + 0x00000034u);
    mem.w32(t24, ctx.ecx);
    // 0x0040f69c: call 0x40fa60
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x0040f6a1u);
    sub_0040fa60(ctx, mem);
    // 0x0040f6a1: lea edx, [esi + 0x78]
    uint32_t t26 = static_cast<uint32_t>(ctx.esi + 0x00000078u);
    ctx.edx = static_cast<uint32_t>(t26);
    // 0x0040f6a4: push edx
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, ctx.edx);
    // 0x0040f6a5: push 0
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x00000000u);
    // 0x0040f6a7: push esi
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, ctx.esi);
    // 0x0040f6a8: push 0x40faf0
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x0040faf0u);
    // 0x0040f6ad: push 0
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x00000000u);
    // 0x0040f6af: push 0
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x00000000u);
    // 0x0040f6b1: call dword ptr [0x51b1c8]
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x0040f6b7u);
    hle_iat_call(ctx, mem, 0x0051b1c8u);
    // 0x0040f6b7: mov dword ptr [esi + 0x74], eax
    uint32_t t34 = static_cast<uint32_t>(ctx.esi + 0x00000074u);
    mem.w32(t34, ctx.eax);
    // 0x0040f6ba: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0040f6bc: mov ecx, dword ptr [esp + 8]
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t36 = mem.r32(t35);
    ctx.ecx = static_cast<uint32_t>(t36);
    // 0x0040f6c0: mov dword ptr fs:[0], ecx
    uint32_t t37 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t37, ctx.ecx);
    // 0x0040f6c7: pop ecx
    uint32_t t38 = ctx.esp;
    uint32_t t39 = mem.r32(t38);
    uint32_t t40 = static_cast<uint32_t>(t38 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    ctx.ecx = static_cast<uint32_t>(t39);
    // 0x0040f6c8: pop esi
    uint32_t t41 = ctx.esp;
    uint32_t t42 = mem.r32(t41);
    uint32_t t43 = static_cast<uint32_t>(t41 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    ctx.esi = static_cast<uint32_t>(t42);
    // 0x0040f6c9: add esp, 0xc
    uint32_t t44 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t44);
    ctx.esp = static_cast<uint32_t>(t44);
    // 0x0040f6cc: ret 0x10
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 16u;
    return;
}
}

// sub_0040f6d0 | subsystem=Sound | canonical | 3 blocks | 12 insns
void sub_0040f6d0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040f6d0: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x0040f6d1: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x0040f6d3: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
    // 0x0040f6d4: call 0x40f7a0
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0x0040f6d9u);
    sub_0040f7a0(ctx, mem);
    // 0x0040f6d9: test byte ptr [esp + 8], 1
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint8_t t4 = mem.r8(t3);
    uint8_t t5 = static_cast<uint8_t>(static_cast<uint32_t>(t4) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t5);
    // 0x0040f6de: je 0x40f6e9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f6e9;
    goto bb_0040f6e0;
}
bb_0040f6e9: {
    // 0x0040f6e9: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0040f6eb: pop esi
    uint32_t t6 = ctx.esp;
    uint32_t t7 = mem.r32(t6);
    uint32_t t8 = static_cast<uint32_t>(t6 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    ctx.esi = static_cast<uint32_t>(t7);
    // 0x0040f6ec: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0040f6e0: {
    // 0x0040f6e0: push esi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.esi);
    // 0x0040f6e1: call 0x4e02f3
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x0040f6e6u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0040f6e6: add esp, 4
    uint32_t t11 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t11);
    ctx.esp = static_cast<uint32_t>(t11);
    goto bb_0040f6e9;
}
}

// sub_0040f6f0 | subsystem=Sound | canonical | 1 blocks | 45 insns
void sub_0040f6f0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040f6f0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0040f6f2: push 0x5148d8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005148d8u);
    // 0x0040f6f7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0040f6fd: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0040f6fe: push esi
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.esi);
    // 0x0040f6ff: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x0040f704: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x0040f706: push eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.eax);
    // 0x0040f707: lea eax, [esp + 8]
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x0040f70b: mov dword ptr fs:[0], eax
    uint32_t t10 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t10, ctx.eax);
    // 0x0040f711: mov esi, dword ptr [esp + 0x18]
    uint32_t t11 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t12 = mem.r32(t11);
    ctx.esi = static_cast<uint32_t>(t12);
    // 0x0040f715: mov eax, dword ptr [esp + 0x1c]
    uint32_t t13 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t14 = mem.r32(t13);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x0040f719: push eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.eax);
    // 0x0040f71a: mov dword ptr [esi], 0x5352a8
    mem.w32(ctx.esi, 0x005352a8u);
    // 0x0040f720: call 0x40f1e0
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x0040f725u);
    sub_0040f1e0(ctx, mem);
    // 0x0040f725: mov eax, dword ptr [esp + 0x24]
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t18 = mem.r32(t17);
    ctx.eax = static_cast<uint32_t>(t18);
    // 0x0040f729: mov dword ptr [esp + 0x10], 0
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t19, 0x00000000u);
    // 0x0040f731: mov dword ptr [esi], 0x5352b4
    mem.w32(ctx.esi, 0x005352b4u);
    // 0x0040f737: call 0x40f5d0
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x0040f73cu);
    sub_0040f5d0(ctx, mem);
    // 0x0040f73c: mov edx, dword ptr [esi + 0x48]
    uint32_t t21 = static_cast<uint32_t>(ctx.esi + 0x00000048u);
    uint32_t t22 = mem.r32(t21);
    ctx.edx = static_cast<uint32_t>(t22);
    // 0x0040f73f: mov ecx, dword ptr [esp + 0x20]
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t24 = mem.r32(t23);
    ctx.ecx = static_cast<uint32_t>(t24);
    // 0x0040f743: push edx
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, ctx.edx);
    // 0x0040f744: mov dword ptr [esi + 0x54], 2
    uint32_t t26 = static_cast<uint32_t>(ctx.esi + 0x00000054u);
    mem.w32(t26, 0x00000002u);
    // 0x0040f74b: mov dword ptr [esi + 0x38], ecx
    uint32_t t27 = static_cast<uint32_t>(ctx.esi + 0x00000038u);
    mem.w32(t27, ctx.ecx);
    // 0x0040f74e: call 0x4e0230
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x0040f753u);
    hle_crt_004e0230(ctx, mem);
    // 0x0040f753: mov dword ptr [esi + 0x90], eax
    uint32_t t29 = static_cast<uint32_t>(ctx.esi + 0x00000090u);
    mem.w32(t29, ctx.eax);
    // 0x0040f759: add esp, 4
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t30);
    ctx.esp = static_cast<uint32_t>(t30);
    // 0x0040f75c: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0040f75e: call 0x40fa60
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x0040f763u);
    sub_0040fa60(ctx, mem);
    // 0x0040f763: lea eax, [esi + 0x78]
    uint32_t t32 = static_cast<uint32_t>(ctx.esi + 0x00000078u);
    ctx.eax = static_cast<uint32_t>(t32);
    // 0x0040f766: push eax
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, ctx.eax);
    // 0x0040f767: push 0
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x00000000u);
    // 0x0040f769: push esi
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, ctx.esi);
    // 0x0040f76a: push 0x40faf0
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, 0x0040faf0u);
    // 0x0040f76f: push 0
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, 0x00000000u);
    // 0x0040f771: push 0
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, 0x00000000u);
    // 0x0040f773: call dword ptr [0x51b1c8]
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, 0x0040f779u);
    hle_iat_call(ctx, mem, 0x0051b1c8u);
    // 0x0040f779: mov dword ptr [esi + 0x74], eax
    uint32_t t40 = static_cast<uint32_t>(ctx.esi + 0x00000074u);
    mem.w32(t40, ctx.eax);
    // 0x0040f77c: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x0040f77e: mov ecx, dword ptr [esp + 8]
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t42 = mem.r32(t41);
    ctx.ecx = static_cast<uint32_t>(t42);
    // 0x0040f782: mov dword ptr fs:[0], ecx
    uint32_t t43 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t43, ctx.ecx);
    // 0x0040f789: pop ecx
    uint32_t t44 = ctx.esp;
    uint32_t t45 = mem.r32(t44);
    uint32_t t46 = static_cast<uint32_t>(t44 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    ctx.ecx = static_cast<uint32_t>(t45);
    // 0x0040f78a: pop esi
    uint32_t t47 = ctx.esp;
    uint32_t t48 = mem.r32(t47);
    uint32_t t49 = static_cast<uint32_t>(t47 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    ctx.esi = static_cast<uint32_t>(t48);
    // 0x0040f78b: add esp, 0xc
    uint32_t t50 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t50);
    ctx.esp = static_cast<uint32_t>(t50);
    // 0x0040f78e: ret 0x10
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 16u;
    return;
}
}

// sub_0040f7a0 | subsystem=Sound | canonical | 19 blocks | 107 insns
void sub_0040f7a0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040f7a0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x0040f7a2: push 0x513828
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00513828u);
    // 0x0040f7a7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0040f7ad: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x0040f7ae: push ebx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ebx);
    // 0x0040f7af: push ebp
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebp);
    // 0x0040f7b0: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x0040f7b1: push edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edi);
    // 0x0040f7b2: mov eax, dword ptr [0x54b458]
    uint32_t t9 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x0040f7b7: xor eax, esp
    uint32_t t10 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0040f7b9: push eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.eax);
    // 0x0040f7ba: lea eax, [esp + 0x14]
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x0040f7be: mov dword ptr fs:[0], eax
    uint32_t t13 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t13, ctx.eax);
    // 0x0040f7c4: mov edi, dword ptr [esp + 0x24]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    uint32_t t15 = mem.r32(t14);
    ctx.edi = static_cast<uint32_t>(t15);
    // 0x0040f7c8: mov dword ptr [edi], 0x5352b4
    mem.w32(ctx.edi, 0x005352b4u);
    // 0x0040f7ce: xor ebp, ebp
    uint32_t t16 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    ctx.ebp = static_cast<uint32_t>(t16);
    // 0x0040f7d0: mov dword ptr [esp + 0x1c], ebp
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t17, ctx.ebp);
    // 0x0040f7d4: mov eax, dword ptr [edi + 4]
    uint32_t t18 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    uint32_t t19 = mem.r32(t18);
    ctx.eax = static_cast<uint32_t>(t19);
    // 0x0040f7d7: mov eax, dword ptr [eax]
    uint32_t t20 = mem.r32(ctx.eax);
    ctx.eax = static_cast<uint32_t>(t20);
    // 0x0040f7d9: cmp eax, ebp
    uint32_t t21 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t21);
    // 0x0040f7db: je 0x40f7e5
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f7e5;
    goto bb_0040f7dd;
}
bb_0040f7e5: {
    // 0x0040f7e5: mov ebx, dword ptr [0x51b044]
    uint32_t t22 = mem.r32(0x0051b044u);
    ctx.ebx = static_cast<uint32_t>(t22);
    // 0x0040f7eb: mov byte ptr [edi + 0x3c], 1
    uint32_t t23 = static_cast<uint32_t>(ctx.edi + 0x0000003cu);
    mem.w8(t23, uint8_t{0x01u});
    // 0x0040f7ef: lea esi, [edi + 0x5c]
    uint32_t t24 = static_cast<uint32_t>(ctx.edi + 0x0000005cu);
    ctx.esi = static_cast<uint32_t>(t24);
    goto bb_0040f7f2;
}
bb_0040f7dd: {
    // 0x0040f7dd: mov ecx, dword ptr [eax]
    uint32_t t25 = mem.r32(ctx.eax);
    ctx.ecx = static_cast<uint32_t>(t25);
    // 0x0040f7df: mov edx, dword ptr [ecx + 0x48]
    uint32_t t26 = static_cast<uint32_t>(ctx.ecx + 0x00000048u);
    uint32_t t27 = mem.r32(t26);
    ctx.edx = static_cast<uint32_t>(t27);
    // 0x0040f7e2: push eax
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, ctx.eax);
    // 0x0040f7e3: call edx
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x0040f7e5u);
    call_indirect(ctx, mem, ctx.edx);
    goto bb_0040f7e5;
}
bb_0040f7f2: {
    // 0x0040f7f2: cmp esi, ebp
    uint32_t t30 = static_cast<uint32_t>(ctx.esi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebp, t30);
    // 0x0040f7f4: je 0x40f7fb
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f7fb;
    goto bb_0040f7f6;
}
bb_0040f7fb: {
    // 0x0040f7fb: mov ecx, dword ptr [edi + 0x74]
    uint32_t t31 = static_cast<uint32_t>(ctx.edi + 0x00000074u);
    uint32_t t32 = mem.r32(t31);
    ctx.ecx = static_cast<uint32_t>(t32);
    // 0x0040f7fe: push 0x64
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x00000064u);
    // 0x0040f800: push ecx
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, ctx.ecx);
    // 0x0040f801: call dword ptr [0x51b040]
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, 0x0040f807u);
    hle_iat_call(ctx, mem, 0x0051b040u);
    // 0x0040f807: test eax, eax
    uint32_t t36 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t36);
    // 0x0040f809: jne 0x40f7f2
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040f7f2;
    goto bb_0040f80b;
}
bb_0040f7f6: {
    // 0x0040f7f6: mov eax, dword ptr [esi]
    uint32_t t37 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t37);
    // 0x0040f7f8: push eax
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, ctx.eax);
    // 0x0040f7f9: call ebx
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, 0x0040f7fbu);
    call_indirect(ctx, mem, ctx.ebx);
    goto bb_0040f7fb;
}
bb_0040f80b: {
    // 0x0040f80b: mov edx, dword ptr [edi + 0x74]
    uint32_t t40 = static_cast<uint32_t>(ctx.edi + 0x00000074u);
    uint32_t t41 = mem.r32(t40);
    ctx.edx = static_cast<uint32_t>(t41);
    // 0x0040f80e: push edx
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, ctx.edx);
    // 0x0040f80f: call dword ptr [0x51b1cc]
    uint32_t t43 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    mem.w32(t43, 0x0040f815u);
    hle_iat_call(ctx, mem, 0x0051b1ccu);
    // 0x0040f815: mov eax, dword ptr [edi + 0x90]
    uint32_t t44 = static_cast<uint32_t>(ctx.edi + 0x00000090u);
    uint32_t t45 = mem.r32(t44);
    ctx.eax = static_cast<uint32_t>(t45);
    // 0x0040f81b: cmp eax, ebp
    uint32_t t46 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t46);
    // 0x0040f81d: mov dword ptr [edi + 0x74], ebp
    uint32_t t47 = static_cast<uint32_t>(ctx.edi + 0x00000074u);
    mem.w32(t47, ctx.ebp);
    // 0x0040f820: je 0x40f831
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f831;
    goto bb_0040f822;
}
bb_0040f831: {
    // 0x0040f831: mov ebx, 5
    ctx.ebx = static_cast<uint32_t>(0x00000005u);
    goto bb_0040f836;
}
bb_0040f822: {
    // 0x0040f822: push eax
    uint32_t t48 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    mem.w32(t48, ctx.eax);
    // 0x0040f823: call 0x4e00d0
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, 0x0040f828u);
    hle_crt_004e00d0(ctx, mem);
    // 0x0040f828: add esp, 4
    uint32_t t50 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t50);
    ctx.esp = static_cast<uint32_t>(t50);
    // 0x0040f82b: mov dword ptr [edi + 0x90], ebp
    uint32_t t51 = static_cast<uint32_t>(ctx.edi + 0x00000090u);
    mem.w32(t51, ctx.ebp);
    goto bb_0040f831;
}
bb_0040f836: {
    // 0x0040f836: mov eax, dword ptr [esi]
    uint32_t t52 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t52);
    // 0x0040f838: cmp eax, ebp
    uint32_t t53 = static_cast<uint32_t>(ctx.eax - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebp, t53);
    // 0x0040f83a: je 0x40f843
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f843;
    goto bb_0040f83c;
}
bb_0040f843: {
    // 0x0040f843: add esi, 4
    uint32_t t54 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000004u, t54);
    ctx.esi = static_cast<uint32_t>(t54);
    // 0x0040f846: sub ebx, 1
    uint32_t t55 = static_cast<uint32_t>(ctx.ebx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, 0x00000001u, t55);
    ctx.ebx = static_cast<uint32_t>(t55);
    // 0x0040f849: jne 0x40f836
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040f836;
    goto bb_0040f84b;
}
bb_0040f83c: {
    // 0x0040f83c: push eax
    uint32_t t56 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    mem.w32(t56, ctx.eax);
    // 0x0040f83d: call dword ptr [0x51b1cc]
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, 0x0040f843u);
    hle_iat_call(ctx, mem, 0x0051b1ccu);
    goto bb_0040f843;
}
bb_0040f84b: {
    // 0x0040f84b: mov esi, dword ptr [edi + 0x34]
    uint32_t t58 = static_cast<uint32_t>(ctx.edi + 0x00000034u);
    uint32_t t59 = mem.r32(t58);
    ctx.esi = static_cast<uint32_t>(t59);
    // 0x0040f84e: cmp esi, ebp
    uint32_t t60 = static_cast<uint32_t>(ctx.esi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebp, t60);
    // 0x0040f850: je 0x40f863
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f863;
    goto bb_0040f852;
}
bb_0040f863: {
    // 0x0040f863: mov esi, dword ptr [edi + 0x38]
    uint32_t t61 = static_cast<uint32_t>(ctx.edi + 0x00000038u);
    uint32_t t62 = mem.r32(t61);
    ctx.esi = static_cast<uint32_t>(t62);
    // 0x0040f866: cmp esi, ebp
    uint32_t t63 = static_cast<uint32_t>(ctx.esi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebp, t63);
    // 0x0040f868: je 0x40f87b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f87b;
    goto bb_0040f86a;
}
bb_0040f852: {
    // 0x0040f852: call 0x40fd90
    uint32_t t64 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    mem.w32(t64, 0x0040f857u);
    sub_0040fd90(ctx, mem);
    // 0x0040f857: push esi
    uint32_t t65 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t65);
    mem.w32(t65, ctx.esi);
    // 0x0040f858: call 0x4e02f3
    uint32_t t66 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    mem.w32(t66, 0x0040f85du);
    hle_crt_004e02f3(ctx, mem);
    // 0x0040f85d: add esp, 4
    uint32_t t67 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t67);
    ctx.esp = static_cast<uint32_t>(t67);
    // 0x0040f860: mov dword ptr [edi + 0x34], ebp
    uint32_t t68 = static_cast<uint32_t>(ctx.edi + 0x00000034u);
    mem.w32(t68, ctx.ebp);
    goto bb_0040f863;
}
bb_0040f87b: {
    // 0x0040f87b: mov dword ptr [esp + 0x1c], 0xffffffff
    uint32_t t69 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t69, 0xffffffffu);
    // 0x0040f883: cmp dword ptr [edi + 0x24], ebp
    uint32_t t70 = static_cast<uint32_t>(ctx.edi + 0x00000024u);
    uint32_t t71 = mem.r32(t70);
    uint32_t t72 = static_cast<uint32_t>(t71 - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t71, ctx.ebp, t72);
    // 0x0040f886: mov dword ptr [edi], 0x5352a8
    mem.w32(ctx.edi, 0x005352a8u);
    // 0x0040f88c: je 0x40f8be
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f8be;
    goto bb_0040f88e;
}
bb_0040f86a: {
    // 0x0040f86a: call 0x416e30
    uint32_t t73 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    mem.w32(t73, 0x0040f86fu);
    sub_00416e30(ctx, mem);
    // 0x0040f86f: push esi
    uint32_t t74 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    mem.w32(t74, ctx.esi);
    // 0x0040f870: call 0x4e02f3
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, 0x0040f875u);
    hle_crt_004e02f3(ctx, mem);
    // 0x0040f875: add esp, 4
    uint32_t t76 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t76);
    ctx.esp = static_cast<uint32_t>(t76);
    // 0x0040f878: mov dword ptr [edi + 0x38], ebp
    uint32_t t77 = static_cast<uint32_t>(ctx.edi + 0x00000038u);
    mem.w32(t77, ctx.ebp);
    goto bb_0040f87b;
}
bb_0040f8be: {
    // 0x0040f8be: mov esi, edi
    ctx.esi = static_cast<uint32_t>(ctx.edi);
    // 0x0040f8c0: call 0x40f340
    uint32_t t78 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    mem.w32(t78, 0x0040f8c5u);
    sub_0040f340(ctx, mem);
    // 0x0040f8c5: mov ecx, dword ptr [esp + 0x14]
    uint32_t t79 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t80 = mem.r32(t79);
    ctx.ecx = static_cast<uint32_t>(t80);
    // 0x0040f8c9: mov dword ptr fs:[0], ecx
    uint32_t t81 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t81, ctx.ecx);
    // 0x0040f8d0: pop ecx
    uint32_t t82 = ctx.esp;
    uint32_t t83 = mem.r32(t82);
    uint32_t t84 = static_cast<uint32_t>(t82 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    ctx.ecx = static_cast<uint32_t>(t83);
    // 0x0040f8d1: pop edi
    uint32_t t85 = ctx.esp;
    uint32_t t86 = mem.r32(t85);
    uint32_t t87 = static_cast<uint32_t>(t85 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t87);
    ctx.edi = static_cast<uint32_t>(t86);
    // 0x0040f8d2: pop esi
    uint32_t t88 = ctx.esp;
    uint32_t t89 = mem.r32(t88);
    uint32_t t90 = static_cast<uint32_t>(t88 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    ctx.esi = static_cast<uint32_t>(t89);
    // 0x0040f8d3: pop ebp
    uint32_t t91 = ctx.esp;
    uint32_t t92 = mem.r32(t91);
    uint32_t t93 = static_cast<uint32_t>(t91 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    ctx.ebp = static_cast<uint32_t>(t92);
    // 0x0040f8d4: pop ebx
    uint32_t t94 = ctx.esp;
    uint32_t t95 = mem.r32(t94);
    uint32_t t96 = static_cast<uint32_t>(t94 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    ctx.ebx = static_cast<uint32_t>(t95);
    // 0x0040f8d5: add esp, 0xc
    uint32_t t97 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t97);
    ctx.esp = static_cast<uint32_t>(t97);
    // 0x0040f8d8: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0040f88e: {
    // 0x0040f88e: mov ecx, dword ptr [edi + 0x28]
    uint32_t t98 = static_cast<uint32_t>(ctx.edi + 0x00000028u);
    uint32_t t99 = mem.r32(t98);
    ctx.ecx = static_cast<uint32_t>(t99);
    // 0x0040f891: mov eax, dword ptr [edi + 0x18]
    uint32_t t100 = static_cast<uint32_t>(ctx.edi + 0x00000018u);
    uint32_t t101 = mem.r32(t100);
    ctx.eax = static_cast<uint32_t>(t101);
    // 0x0040f894: push ebp
    uint32_t t102 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    mem.w32(t102, ctx.ebp);
    // 0x0040f895: push ebp
    uint32_t t103 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    mem.w32(t103, ctx.ebp);
    // 0x0040f896: push 0x12
    uint32_t t104 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t104);
    mem.w32(t104, 0x00000012u);
    // 0x0040f898: push ecx
    uint32_t t105 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t105);
    mem.w32(t105, ctx.ecx);
    // 0x0040f899: mov dword ptr [edi + 0x2c], eax
    uint32_t t106 = static_cast<uint32_t>(ctx.edi + 0x0000002cu);
    mem.w32(t106, ctx.eax);
    // 0x0040f89c: call dword ptr [0x51b244]
    uint32_t t107 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t107);
    mem.w32(t107, 0x0040f8a2u);
    hle_iat_call(ctx, mem, 0x0051b244u);
    // 0x0040f8a2: mov edx, dword ptr [edi + 0x24]
    uint32_t t108 = static_cast<uint32_t>(ctx.edi + 0x00000024u);
    uint32_t t109 = mem.r32(t108);
    ctx.edx = static_cast<uint32_t>(t109);
    // 0x0040f8a5: push -1
    uint32_t t110 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t110);
    mem.w32(t110, 0xffffffffu);
    // 0x0040f8a7: push edx
    uint32_t t111 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t111);
    mem.w32(t111, ctx.edx);
    // 0x0040f8a8: call dword ptr [0x51b040]
    uint32_t t112 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t112);
    mem.w32(t112, 0x0040f8aeu);
    hle_iat_call(ctx, mem, 0x0051b040u);
    // 0x0040f8ae: mov eax, dword ptr [edi + 0x24]
    uint32_t t113 = static_cast<uint32_t>(ctx.edi + 0x00000024u);
    uint32_t t114 = mem.r32(t113);
    ctx.eax = static_cast<uint32_t>(t114);
    // 0x0040f8b1: push eax
    uint32_t t115 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t115);
    mem.w32(t115, ctx.eax);
    // 0x0040f8b2: call dword ptr [0x51b1cc]
    uint32_t t116 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t116);
    mem.w32(t116, 0x0040f8b8u);
    hle_iat_call(ctx, mem, 0x0051b1ccu);
    // 0x0040f8b8: mov dword ptr [edi + 0x24], ebp
    uint32_t t117 = static_cast<uint32_t>(ctx.edi + 0x00000024u);
    mem.w32(t117, ctx.ebp);
    // 0x0040f8bb: mov dword ptr [edi + 0x28], ebp
    uint32_t t118 = static_cast<uint32_t>(ctx.edi + 0x00000028u);
    mem.w32(t118, ctx.ebp);
    goto bb_0040f8be;
}
}

// sub_0040f8e0 | subsystem=Sound | canonical | 6 blocks | 62 insns
void sub_0040f8e0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040f8e0: mov eax, dword ptr [esi + 4]
    uint32_t t0 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t1 = mem.r32(t0);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x0040f8e3: mov edx, dword ptr [esi + 0x34]
    uint32_t t2 = static_cast<uint32_t>(ctx.esi + 0x00000034u);
    uint32_t t3 = mem.r32(t2);
    ctx.edx = static_cast<uint32_t>(t3);
    // 0x0040f8e6: mov ecx, dword ptr [esi + 0x48]
    uint32_t t4 = static_cast<uint32_t>(ctx.esi + 0x00000048u);
    uint32_t t5 = mem.r32(t4);
    ctx.ecx = static_cast<uint32_t>(t5);
    // 0x0040f8e9: sub esp, 0xc
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x0000000cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x0000000cu, t6);
    ctx.esp = static_cast<uint32_t>(t6);
    // 0x0040f8ec: push edi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.edi);
    // 0x0040f8ed: mov edi, dword ptr [eax]
    uint32_t t8 = mem.r32(ctx.eax);
    ctx.edi = static_cast<uint32_t>(t8);
    // 0x0040f8ef: mov eax, 0xaaaaaaab
    ctx.eax = static_cast<uint32_t>(0xaaaaaaabu);
    // 0x0040f8f4: mul dword ptr [edx + 0xc]
    uint32_t t9 = static_cast<uint32_t>(ctx.edx + 0x0000000cu);
    uint32_t t10 = mem.r32(t9);
    uint64_t t11 = (static_cast<uint64_t>(ctx.eax) * static_cast<uint64_t>(t10));
    uint32_t t12 = static_cast<uint32_t>(t11);
    uint32_t t13 = static_cast<uint32_t>(t11 >> 32);
    ctx.eax = static_cast<uint32_t>(t12);
    ctx.edx = static_cast<uint32_t>(t13);
    recomp_detail::update_flags_mul<uint32_t>(ctx, t11);
    // 0x0040f8f7: shr edx, 1
    uint32_t t14 = static_cast<uint32_t>(0x00000001u & 0x0000001fu);
    uint32_t t15 = recomp_detail::shr<uint32_t>(ctx.edx, t14);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.edx, t14, t15);
    ctx.edx = static_cast<uint32_t>(t15);
    // 0x0040f8f9: cmp edx, ecx
    uint32_t t16 = static_cast<uint32_t>(ctx.edx - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, ctx.ecx, t16);
    // 0x0040f8fb: je 0x40f978
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f978;
    goto bb_0040f8fd;
}
bb_0040f978: {
    // 0x0040f978: pop edi
    uint32_t t17 = ctx.esp;
    uint32_t t18 = mem.r32(t17);
    uint32_t t19 = static_cast<uint32_t>(t17 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    ctx.edi = static_cast<uint32_t>(t18);
    // 0x0040f979: add esp, 0xc
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t20);
    ctx.esp = static_cast<uint32_t>(t20);
    // 0x0040f97c: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0040f8fd: {
    // 0x0040f8fd: mov eax, dword ptr [edi]
    uint32_t t21 = mem.r32(ctx.edi);
    ctx.eax = static_cast<uint32_t>(t21);
    // 0x0040f8ff: push 0
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x00000000u);
    // 0x0040f901: mov eax, dword ptr [eax + 0x2c]
    uint32_t t23 = static_cast<uint32_t>(ctx.eax + 0x0000002cu);
    uint32_t t24 = mem.r32(t23);
    ctx.eax = static_cast<uint32_t>(t24);
    // 0x0040f904: lea edx, [esp + 0x18]
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.edx = static_cast<uint32_t>(t25);
    // 0x0040f908: push edx
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, ctx.edx);
    // 0x0040f909: lea edx, [esp + 0xc]
    uint32_t t27 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    ctx.edx = static_cast<uint32_t>(t27);
    // 0x0040f90d: push edx
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, ctx.edx);
    // 0x0040f90e: lea edx, [esp + 0x14]
    uint32_t t29 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.edx = static_cast<uint32_t>(t29);
    // 0x0040f912: push edx
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, ctx.edx);
    // 0x0040f913: lea edx, [esp + 0x1c]
    uint32_t t31 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.edx = static_cast<uint32_t>(t31);
    // 0x0040f917: push edx
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, ctx.edx);
    // 0x0040f918: push ecx
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, ctx.ecx);
    // 0x0040f919: imul ecx, dword ptr [esp + 0x2c]
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    uint32_t t35 = mem.r32(t34);
    uint64_t t36 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)) * static_cast<int64_t>(static_cast<int32_t>(t35)));
    uint32_t t37 = static_cast<uint32_t>(t36);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t36);
    ctx.ecx = static_cast<uint32_t>(t37);
    // 0x0040f91e: push ecx
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, ctx.ecx);
    // 0x0040f91f: push edi
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, ctx.edi);
    // 0x0040f920: call eax
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, 0x0040f922u);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0040f922: test eax, eax
    uint32_t t41 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t41);
    // 0x0040f924: jne 0x40f978
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040f978;
}
{
    // 0x0040f926: mov ecx, dword ptr [esi + 0x80]
    uint32_t t42 = static_cast<uint32_t>(ctx.esi + 0x00000080u);
    uint32_t t43 = mem.r32(t42);
    ctx.ecx = static_cast<uint32_t>(t43);
    // 0x0040f92c: mov edx, dword ptr [esp + 0xc]
    uint32_t t44 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t45 = mem.r32(t44);
    ctx.edx = static_cast<uint32_t>(t45);
    // 0x0040f930: mov eax, dword ptr [esp + 8]
    uint32_t t46 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t47 = mem.r32(t46);
    ctx.eax = static_cast<uint32_t>(t47);
    // 0x0040f934: push ebx
    uint32_t t48 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    mem.w32(t48, ctx.ebx);
    // 0x0040f935: mov ebx, dword ptr [esi + 0x34]
    uint32_t t49 = static_cast<uint32_t>(ctx.esi + 0x00000034u);
    uint32_t t50 = mem.r32(t49);
    ctx.ebx = static_cast<uint32_t>(t50);
    // 0x0040f938: push ecx
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, ctx.ecx);
    // 0x0040f939: push edx
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, ctx.edx);
    // 0x0040f93a: call 0x40fcd0
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, 0x0040f93fu);
    sub_0040fcd0(ctx, mem);
    // 0x0040f93f: mov eax, dword ptr [esp + 0x18]
    uint32_t t54 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t55 = mem.r32(t54);
    ctx.eax = static_cast<uint32_t>(t55);
    // 0x0040f943: test eax, eax
    uint32_t t56 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t56);
    // 0x0040f945: je 0x40f95f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040f95f;
    goto bb_0040f947;
}
bb_0040f95f: {
    // 0x0040f95f: mov edx, dword ptr [esp + 8]
    uint32_t t57 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t58 = mem.r32(t57);
    ctx.edx = static_cast<uint32_t>(t58);
    // 0x0040f963: mov ecx, dword ptr [edi]
    uint32_t t59 = mem.r32(ctx.edi);
    ctx.ecx = static_cast<uint32_t>(t59);
    // 0x0040f965: push eax
    uint32_t t60 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t60);
    mem.w32(t60, ctx.eax);
    // 0x0040f966: mov eax, dword ptr [esp + 0x10]
    uint32_t t61 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t62 = mem.r32(t61);
    ctx.eax = static_cast<uint32_t>(t62);
    // 0x0040f96a: push edx
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, ctx.edx);
    // 0x0040f96b: mov edx, dword ptr [esp + 0x18]
    uint32_t t64 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t65 = mem.r32(t64);
    ctx.edx = static_cast<uint32_t>(t65);
    // 0x0040f96f: push eax
    uint32_t t66 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    mem.w32(t66, ctx.eax);
    // 0x0040f970: mov eax, dword ptr [ecx + 0x4c]
    uint32_t t67 = static_cast<uint32_t>(ctx.ecx + 0x0000004cu);
    uint32_t t68 = mem.r32(t67);
    ctx.eax = static_cast<uint32_t>(t68);
    // 0x0040f973: push edx
    uint32_t t69 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    mem.w32(t69, ctx.edx);
    // 0x0040f974: push edi
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, ctx.edi);
    // 0x0040f975: call eax
    uint32_t t71 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t71);
    mem.w32(t71, 0x0040f977u);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0040f977: pop ebx
    uint32_t t72 = ctx.esp;
    uint32_t t73 = mem.r32(t72);
    uint32_t t74 = static_cast<uint32_t>(t72 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    ctx.ebx = static_cast<uint32_t>(t73);
    goto bb_0040f978;
}
bb_0040f947: {
    // 0x0040f947: mov ecx, dword ptr [esi + 0x80]
    uint32_t t75 = static_cast<uint32_t>(ctx.esi + 0x00000080u);
    uint32_t t76 = mem.r32(t75);
    ctx.ecx = static_cast<uint32_t>(t76);
    // 0x0040f94d: mov edx, dword ptr [esp + 8]
    uint32_t t77 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t78 = mem.r32(t77);
    ctx.edx = static_cast<uint32_t>(t78);
    // 0x0040f951: mov ebx, dword ptr [esi + 0x34]
    uint32_t t79 = static_cast<uint32_t>(ctx.esi + 0x00000034u);
    uint32_t t80 = mem.r32(t79);
    ctx.ebx = static_cast<uint32_t>(t80);
    // 0x0040f954: push ecx
    uint32_t t81 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    mem.w32(t81, ctx.ecx);
    // 0x0040f955: push edx
    uint32_t t82 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t82);
    mem.w32(t82, ctx.edx);
    // 0x0040f956: call 0x40fcd0
    uint32_t t83 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t83);
    mem.w32(t83, 0x0040f95bu);
    sub_0040fcd0(ctx, mem);
    // 0x0040f95b: mov eax, dword ptr [esp + 0x18]
    uint32_t t84 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t85 = mem.r32(t84);
    ctx.eax = static_cast<uint32_t>(t85);
    goto bb_0040f95f;
}
}

// sub_0040f980 | subsystem=Sound | canonical | 8 blocks | 85 insns
void sub_0040f980(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040f980: sub esp, 0x14
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000014u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000014u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x0040f983: mov eax, dword ptr [esi + 4]
    uint32_t t1 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t2 = mem.r32(t1);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x0040f986: mov ecx, dword ptr [esi + 0x90]
    uint32_t t3 = static_cast<uint32_t>(ctx.esi + 0x00000090u);
    uint32_t t4 = mem.r32(t3);
    ctx.ecx = static_cast<uint32_t>(t4);
    // 0x0040f98c: mov edx, dword ptr [esi + 0x38]
    uint32_t t5 = static_cast<uint32_t>(ctx.esi + 0x00000038u);
    uint32_t t6 = mem.r32(t5);
    ctx.edx = static_cast<uint32_t>(t6);
    // 0x0040f98f: push ebx
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.ebx);
    // 0x0040f990: mov ebx, dword ptr [eax]
    uint32_t t8 = mem.r32(ctx.eax);
    ctx.ebx = static_cast<uint32_t>(t8);
    // 0x0040f992: mov eax, dword ptr [esi + 0x80]
    uint32_t t9 = static_cast<uint32_t>(ctx.esi + 0x00000080u);
    uint32_t t10 = mem.r32(t9);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x0040f998: push ebp
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.ebp);
    // 0x0040f999: push edi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.edi);
    // 0x0040f99a: mov edi, dword ptr [esi + 0x48]
    uint32_t t13 = static_cast<uint32_t>(ctx.esi + 0x00000048u);
    uint32_t t14 = mem.r32(t13);
    ctx.edi = static_cast<uint32_t>(t14);
    // 0x0040f99d: push eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.eax);
    // 0x0040f99e: push ecx
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, ctx.ecx);
    // 0x0040f99f: push edx
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, ctx.edx);
    // 0x0040f9a0: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x0040f9a2: call 0x416ea0
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x0040f9a7u);
    sub_00416ea0(ctx, mem);
    // 0x0040f9a7: push 0
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x00000000u);
    // 0x0040f9a9: mov ebp, edi
    ctx.ebp = static_cast<uint32_t>(ctx.edi);
    // 0x0040f9ab: imul ebp, dword ptr [esp + 0x28]
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    uint32_t t21 = mem.r32(t20);
    uint64_t t22 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.ebp)) * static_cast<int64_t>(static_cast<int32_t>(t21)));
    uint32_t t23 = static_cast<uint32_t>(t22);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t22);
    ctx.ebp = static_cast<uint32_t>(t23);
    // 0x0040f9b0: lea ecx, [esp + 0x14]
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.ecx = static_cast<uint32_t>(t24);
    // 0x0040f9b4: push ecx
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, ctx.ecx);
    // 0x0040f9b5: lea edx, [esp + 0x1c]
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.edx = static_cast<uint32_t>(t26);
    // 0x0040f9b9: push edx
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, ctx.edx);
    // 0x0040f9ba: lea ecx, [esp + 0x18]
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.ecx = static_cast<uint32_t>(t28);
    // 0x0040f9be: push ecx
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, ctx.ecx);
    // 0x0040f9bf: lea edx, [esp + 0x28]
    uint32_t t30 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.edx = static_cast<uint32_t>(t30);
    // 0x0040f9c3: push edx
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, ctx.edx);
    // 0x0040f9c4: push edi
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, ctx.edi);
    // 0x0040f9c5: mov dword ptr [esp + 0x34], eax
    uint32_t t33 = static_cast<uint32_t>(ctx.esp + 0x00000034u);
    mem.w32(t33, ctx.eax);
    // 0x0040f9c9: mov eax, dword ptr [ebx]
    uint32_t t34 = mem.r32(ctx.ebx);
    ctx.eax = static_cast<uint32_t>(t34);
    // 0x0040f9cb: mov eax, dword ptr [eax + 0x2c]
    uint32_t t35 = static_cast<uint32_t>(ctx.eax + 0x0000002cu);
    uint32_t t36 = mem.r32(t35);
    ctx.eax = static_cast<uint32_t>(t36);
    // 0x0040f9ce: push ebp
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, ctx.ebp);
    // 0x0040f9cf: push ebx
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, ctx.ebx);
    // 0x0040f9d0: call eax
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, 0x0040f9d2u);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0040f9d2: test eax, eax
    uint32_t t40 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t40);
    // 0x0040f9d4: jne 0x40fa4d
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fa4d;
    goto bb_0040f9d6;
}
bb_0040fa4d: {
    // 0x0040fa4d: pop edi
    uint32_t t41 = ctx.esp;
    uint32_t t42 = mem.r32(t41);
    uint32_t t43 = static_cast<uint32_t>(t41 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    ctx.edi = static_cast<uint32_t>(t42);
    // 0x0040fa4e: pop ebp
    uint32_t t44 = ctx.esp;
    uint32_t t45 = mem.r32(t44);
    uint32_t t46 = static_cast<uint32_t>(t44 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    ctx.ebp = static_cast<uint32_t>(t45);
    // 0x0040fa4f: pop ebx
    uint32_t t47 = ctx.esp;
    uint32_t t48 = mem.r32(t47);
    uint32_t t49 = static_cast<uint32_t>(t47 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    ctx.ebx = static_cast<uint32_t>(t48);
    // 0x0040fa50: add esp, 0x14
    uint32_t t50 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000014u, t50);
    ctx.esp = static_cast<uint32_t>(t50);
    // 0x0040fa53: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_0040f9d6: {
    // 0x0040f9d6: mov ecx, dword ptr [esp + 0xc]
    uint32_t t51 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t52 = mem.r32(t51);
    ctx.ecx = static_cast<uint32_t>(t52);
    // 0x0040f9da: mov edx, dword ptr [esi + 0x90]
    uint32_t t53 = static_cast<uint32_t>(ctx.esi + 0x00000090u);
    uint32_t t54 = mem.r32(t53);
    ctx.edx = static_cast<uint32_t>(t54);
    // 0x0040f9e0: mov eax, dword ptr [esp + 0x18]
    uint32_t t55 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t56 = mem.r32(t55);
    ctx.eax = static_cast<uint32_t>(t56);
    // 0x0040f9e4: push ecx
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, ctx.ecx);
    // 0x0040f9e5: push edx
    uint32_t t58 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    mem.w32(t58, ctx.edx);
    // 0x0040f9e6: push eax
    uint32_t t59 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    mem.w32(t59, ctx.eax);
    // 0x0040f9e7: call 0x4e63c0
    uint32_t t60 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t60);
    mem.w32(t60, 0x0040f9ecu);
    hle_crt_004e63c0(ctx, mem);
    // 0x0040f9ec: mov eax, dword ptr [esp + 0x1c]
    uint32_t t61 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t62 = mem.r32(t61);
    ctx.eax = static_cast<uint32_t>(t62);
    // 0x0040f9f0: add esp, 0xc
    uint32_t t63 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t63);
    ctx.esp = static_cast<uint32_t>(t63);
    // 0x0040f9f3: test eax, eax
    uint32_t t64 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t64);
    // 0x0040f9f5: je 0x40fa14
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fa14;
    goto bb_0040f9f7;
}
bb_0040fa14: {
    // 0x0040fa14: mov edx, dword ptr [esp + 0x14]
    uint32_t t65 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t66 = mem.r32(t65);
    ctx.edx = static_cast<uint32_t>(t66);
    // 0x0040fa18: mov ecx, dword ptr [ebx]
    uint32_t t67 = mem.r32(ctx.ebx);
    ctx.ecx = static_cast<uint32_t>(t67);
    // 0x0040fa1a: push eax
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, ctx.eax);
    // 0x0040fa1b: mov eax, dword ptr [esp + 0x10]
    uint32_t t69 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t70 = mem.r32(t69);
    ctx.eax = static_cast<uint32_t>(t70);
    // 0x0040fa1f: push edx
    uint32_t t71 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t71);
    mem.w32(t71, ctx.edx);
    // 0x0040fa20: mov edx, dword ptr [esp + 0x20]
    uint32_t t72 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    uint32_t t73 = mem.r32(t72);
    ctx.edx = static_cast<uint32_t>(t73);
    // 0x0040fa24: push eax
    uint32_t t74 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    mem.w32(t74, ctx.eax);
    // 0x0040fa25: mov eax, dword ptr [ecx + 0x4c]
    uint32_t t75 = static_cast<uint32_t>(ctx.ecx + 0x0000004cu);
    uint32_t t76 = mem.r32(t75);
    ctx.eax = static_cast<uint32_t>(t76);
    // 0x0040fa28: push edx
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, ctx.edx);
    // 0x0040fa29: push ebx
    uint32_t t78 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    mem.w32(t78, ctx.ebx);
    // 0x0040fa2a: call eax
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, 0x0040fa2cu);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0040fa2c: cmp dword ptr [esp + 0x1c], 0
    uint32_t t80 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t81 = mem.r32(t80);
    uint32_t t82 = static_cast<uint32_t>(t81 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t81, 0x00000000u, t82);
    // 0x0040fa31: jne 0x40fa4d
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fa4d;
    goto bb_0040fa33;
}
bb_0040f9f7: {
    // 0x0040f9f7: mov ecx, dword ptr [esi + 0x90]
    uint32_t t83 = static_cast<uint32_t>(ctx.esi + 0x00000090u);
    uint32_t t84 = mem.r32(t83);
    ctx.ecx = static_cast<uint32_t>(t84);
    // 0x0040f9fd: add ecx, dword ptr [esp + 0xc]
    uint32_t t85 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t86 = mem.r32(t85);
    uint32_t t87 = static_cast<uint32_t>(ctx.ecx + t86);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, t86, t87);
    ctx.ecx = static_cast<uint32_t>(t87);
    // 0x0040fa01: mov edx, dword ptr [esp + 0x14]
    uint32_t t88 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t89 = mem.r32(t88);
    ctx.edx = static_cast<uint32_t>(t89);
    // 0x0040fa05: push eax
    uint32_t t90 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    mem.w32(t90, ctx.eax);
    // 0x0040fa06: push ecx
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, ctx.ecx);
    // 0x0040fa07: push edx
    uint32_t t92 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    mem.w32(t92, ctx.edx);
    // 0x0040fa08: call 0x4e63c0
    uint32_t t93 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    mem.w32(t93, 0x0040fa0du);
    hle_crt_004e63c0(ctx, mem);
    // 0x0040fa0d: mov eax, dword ptr [esp + 0x1c]
    uint32_t t94 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    uint32_t t95 = mem.r32(t94);
    ctx.eax = static_cast<uint32_t>(t95);
    // 0x0040fa11: add esp, 0xc
    uint32_t t96 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t96);
    ctx.esp = static_cast<uint32_t>(t96);
    goto bb_0040fa14;
}
bb_0040fa33: {
    // 0x0040fa33: cmp dword ptr [esi + 0x58], -1
    uint32_t t97 = static_cast<uint32_t>(ctx.esi + 0x00000058u);
    uint32_t t98 = mem.r32(t97);
    uint32_t t99 = static_cast<uint32_t>(t98 - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t98, 0xffffffffu, t99);
    // 0x0040fa37: jne 0x40fa45
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fa45;
    goto bb_0040fa39;
}
bb_0040fa45: {
    // 0x0040fa45: mov ecx, dword ptr [ebx]
    uint32_t t100 = mem.r32(ctx.ebx);
    ctx.ecx = static_cast<uint32_t>(t100);
    // 0x0040fa47: mov edx, dword ptr [ecx + 0x48]
    uint32_t t101 = static_cast<uint32_t>(ctx.ecx + 0x00000048u);
    uint32_t t102 = mem.r32(t101);
    ctx.edx = static_cast<uint32_t>(t102);
    // 0x0040fa4a: push ebx
    uint32_t t103 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t103);
    mem.w32(t103, ctx.ebx);
    // 0x0040fa4b: call edx
    uint32_t t104 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t104);
    mem.w32(t104, 0x0040fa4du);
    call_indirect(ctx, mem, ctx.edx);
    goto bb_0040fa4d;
}
bb_0040fa39: {
    // 0x0040fa39: mov dword ptr [esi + 0x58], ebp
    uint32_t t105 = static_cast<uint32_t>(ctx.esi + 0x00000058u);
    mem.w32(t105, ctx.ebp);
    // 0x0040fa3c: pop edi
    uint32_t t106 = ctx.esp;
    uint32_t t107 = mem.r32(t106);
    uint32_t t108 = static_cast<uint32_t>(t106 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t108);
    ctx.edi = static_cast<uint32_t>(t107);
    // 0x0040fa3d: pop ebp
    uint32_t t109 = ctx.esp;
    uint32_t t110 = mem.r32(t109);
    uint32_t t111 = static_cast<uint32_t>(t109 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t111);
    ctx.ebp = static_cast<uint32_t>(t110);
    // 0x0040fa3e: pop ebx
    uint32_t t112 = ctx.esp;
    uint32_t t113 = mem.r32(t112);
    uint32_t t114 = static_cast<uint32_t>(t112 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t114);
    ctx.ebx = static_cast<uint32_t>(t113);
    // 0x0040fa3f: add esp, 0x14
    uint32_t t115 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000014u, t115);
    ctx.esp = static_cast<uint32_t>(t115);
    // 0x0040fa42: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
}

// sub_0040fa60 | subsystem=Sound | canonical | 10 blocks | 53 insns
void sub_0040fa60(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040fa60: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x0040fa61: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
    // 0x0040fa62: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0040fa64: mov eax, dword ptr [esi + 4]
    uint32_t t2 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x0040fa67: push edi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.edi);
    // 0x0040fa68: mov dword ptr [esi + 0x44], 0
    uint32_t t5 = static_cast<uint32_t>(ctx.esi + 0x00000044u);
    mem.w32(t5, 0x00000000u);
    // 0x0040fa6f: mov dword ptr [esi + 0x4c], 0
    uint32_t t6 = static_cast<uint32_t>(ctx.esi + 0x0000004cu);
    mem.w32(t6, 0x00000000u);
    // 0x0040fa76: mov dword ptr [esi + 0x40], 0
    uint32_t t7 = static_cast<uint32_t>(ctx.esi + 0x00000040u);
    mem.w32(t7, 0x00000000u);
    // 0x0040fa7d: mov edi, dword ptr [eax]
    uint32_t t8 = mem.r32(ctx.eax);
    ctx.edi = static_cast<uint32_t>(t8);
    // 0x0040fa7f: test edi, edi
    uint32_t t9 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    // 0x0040fa81: jne 0x40fa89
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fa89;
    goto bb_0040fa83;
}
bb_0040fa89: {
    // 0x0040fa89: mov ecx, dword ptr [edi]
    uint32_t t10 = mem.r32(ctx.edi);
    ctx.ecx = static_cast<uint32_t>(t10);
    // 0x0040fa8b: mov edx, dword ptr [ecx + 0x48]
    uint32_t t11 = static_cast<uint32_t>(ctx.ecx + 0x00000048u);
    uint32_t t12 = mem.r32(t11);
    ctx.edx = static_cast<uint32_t>(t12);
    // 0x0040fa8e: push edi
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, ctx.edi);
    // 0x0040fa8f: call edx
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x0040fa91u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x0040fa91: mov eax, dword ptr [edi]
    uint32_t t15 = mem.r32(ctx.edi);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x0040fa93: mov ecx, dword ptr [eax + 0x34]
    uint32_t t16 = static_cast<uint32_t>(ctx.eax + 0x00000034u);
    uint32_t t17 = mem.r32(t16);
    ctx.ecx = static_cast<uint32_t>(t17);
    // 0x0040fa96: push 0
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x00000000u);
    // 0x0040fa98: push edi
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, ctx.edi);
    // 0x0040fa99: call ecx
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x0040fa9bu);
    call_indirect(ctx, mem, ctx.ecx);
    // 0x0040fa9b: mov eax, dword ptr [esi + 8]
    uint32_t t21 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t22 = mem.r32(t21);
    ctx.eax = static_cast<uint32_t>(t22);
    // 0x0040fa9e: test eax, eax
    uint32_t t23 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t23);
    // 0x0040faa0: jne 0x40fac0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fac0;
    goto bb_0040faa2;
}
bb_0040fa83: {
    // 0x0040fa83: xor eax, eax
    uint32_t t24 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t24);
    ctx.eax = static_cast<uint32_t>(t24);
    // 0x0040fa85: pop edi
    uint32_t t25 = ctx.esp;
    uint32_t t26 = mem.r32(t25);
    uint32_t t27 = static_cast<uint32_t>(t25 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    ctx.edi = static_cast<uint32_t>(t26);
    // 0x0040fa86: pop esi
    uint32_t t28 = ctx.esp;
    uint32_t t29 = mem.r32(t28);
    uint32_t t30 = static_cast<uint32_t>(t28 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    ctx.esi = static_cast<uint32_t>(t29);
    // 0x0040fa87: pop ecx
    uint32_t t31 = ctx.esp;
    uint32_t t32 = mem.r32(t31);
    uint32_t t33 = static_cast<uint32_t>(t31 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    ctx.ecx = static_cast<uint32_t>(t32);
    // 0x0040fa88: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040fac0: {
    // 0x0040fac0: cmp eax, 1
    uint32_t t34 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t34);
    // 0x0040fac3: jne 0x40facc
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040facc;
    goto bb_0040fac5;
}
bb_0040faa2: {
    // 0x0040faa2: mov eax, dword ptr [esi + 0x54]
    uint32_t t35 = static_cast<uint32_t>(ctx.esi + 0x00000054u);
    uint32_t t36 = mem.r32(t35);
    ctx.eax = static_cast<uint32_t>(t36);
    // 0x0040faa5: sub eax, 1
    uint32_t t37 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t37);
    ctx.eax = static_cast<uint32_t>(t37);
    // 0x0040faa8: je 0x40fab7
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fab7;
    goto bb_0040faaa;
}
bb_0040facc: {
    // 0x0040facc: mov eax, dword ptr [esi + 0x40]
    uint32_t t38 = static_cast<uint32_t>(ctx.esi + 0x00000040u);
    uint32_t t39 = mem.r32(t38);
    ctx.eax = static_cast<uint32_t>(t39);
    // 0x0040facf: add eax, 1
    uint32_t t40 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t40);
    ctx.eax = static_cast<uint32_t>(t40);
    // 0x0040fad2: mov ecx, 3
    ctx.ecx = static_cast<uint32_t>(0x00000003u);
    // 0x0040fad7: xor edx, edx
    uint32_t t41 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t41);
    ctx.edx = static_cast<uint32_t>(t41);
    // 0x0040fad9: div ecx
    uint64_t t42 = ((static_cast<uint64_t>(ctx.edx) << 32) | static_cast<uint64_t>(ctx.eax));
    uint32_t t43 = recomp_detail::div64_u(t42, ctx.ecx);
    uint32_t t44 = recomp_detail::mod64_u(t42, ctx.ecx);
    ctx.eax = static_cast<uint32_t>(t43);
    ctx.edx = static_cast<uint32_t>(t44);
    // 0x0040fadb: pop edi
    uint32_t t45 = ctx.esp;
    uint32_t t46 = mem.r32(t45);
    uint32_t t47 = static_cast<uint32_t>(t45 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    ctx.edi = static_cast<uint32_t>(t46);
    // 0x0040fadc: lea eax, [ecx - 2]
    uint32_t t48 = static_cast<uint32_t>(ctx.ecx + 0xfffffffeu);
    ctx.eax = static_cast<uint32_t>(t48);
    // 0x0040fadf: mov dword ptr [esi + 0x40], edx
    uint32_t t49 = static_cast<uint32_t>(ctx.esi + 0x00000040u);
    mem.w32(t49, ctx.edx);
    // 0x0040fae2: pop esi
    uint32_t t50 = ctx.esp;
    uint32_t t51 = mem.r32(t50);
    uint32_t t52 = static_cast<uint32_t>(t50 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    ctx.esi = static_cast<uint32_t>(t51);
    // 0x0040fae3: pop ecx
    uint32_t t53 = ctx.esp;
    uint32_t t54 = mem.r32(t53);
    uint32_t t55 = static_cast<uint32_t>(t53 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    ctx.ecx = static_cast<uint32_t>(t54);
    // 0x0040fae4: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040fac5: {
    // 0x0040fac5: mov dword ptr [esi + 8], 2
    uint32_t t56 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t56, 0x00000002u);
    goto bb_0040facc;
}
bb_0040fab7: {
    // 0x0040fab7: push 0
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, 0x00000000u);
    // 0x0040fab9: call 0x40f8e0
    uint32_t t58 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    mem.w32(t58, 0x0040fabeu);
    sub_0040f8e0(ctx, mem);
    // 0x0040fabe: jmp 0x40facc
    goto bb_0040facc;
}
bb_0040faaa: {
    // 0x0040faaa: sub eax, 1
    uint32_t t59 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t59);
    ctx.eax = static_cast<uint32_t>(t59);
    // 0x0040faad: jne 0x40facc
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040facc;
}
{
    // 0x0040faaf: push eax
    uint32_t t60 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t60);
    mem.w32(t60, ctx.eax);
    // 0x0040fab0: call 0x40f980
    uint32_t t61 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    mem.w32(t61, 0x0040fab5u);
    sub_0040f980(ctx, mem);
    // 0x0040fab5: jmp 0x40facc
    goto bb_0040facc;
}
}

// sub_0040fb10 | subsystem=Sound | canonical | 25 blocks | 80 insns
void sub_0040fb10(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040fb10: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x0040fb11: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x0040fb13: cmp byte ptr [esi + 0x3c], 0
    uint32_t t1 = static_cast<uint32_t>(ctx.esi + 0x0000003cu);
    uint8_t t2 = mem.r8(t1);
    uint8_t t3 = static_cast<uint8_t>(static_cast<uint32_t>(t2) - static_cast<uint32_t>(uint8_t{0x00u}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, t2, uint8_t{0x00u}, t3);
    // 0x0040fb17: jne 0x40fbc3
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fbc3;
    goto bb_0040fb1d;
}
bb_0040fbc3: {
    // 0x0040fbc3: mov esi, dword ptr [esi + 4]
    uint32_t t4 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t5 = mem.r32(t4);
    ctx.esi = static_cast<uint32_t>(t5);
    // 0x0040fbc6: test esi, esi
    uint32_t t6 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t6);
    // 0x0040fbc8: je 0x40fbd8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fbd8;
    goto bb_0040fbca;
}
bb_0040fb1d: {
    // 0x0040fb1d: push ebx
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.ebx);
    // 0x0040fb1e: push edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edi);
    // 0x0040fb1f: mov edi, dword ptr [0x51b03c]
    uint32_t t9 = mem.r32(0x0051b03cu);
    ctx.edi = static_cast<uint32_t>(t9);
    // 0x0040fb25: lea ebx, [esi + 0x5c]
    uint32_t t10 = static_cast<uint32_t>(ctx.esi + 0x0000005cu);
    ctx.ebx = static_cast<uint32_t>(t10);
    goto bb_0040fb28;
}
bb_0040fbd8: {
    // 0x0040fbd8: sub dword ptr [0x76e66c], 1
    uint32_t t11 = mem.r32(0x0076e66cu);
    uint32_t t12 = static_cast<uint32_t>(t11 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t11, 0x00000001u, t12);
    mem.w32(0x0076e66cu, t12);
    // 0x0040fbdf: push 0xfefefefe
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0xfefefefeu);
    // 0x0040fbe4: call dword ptr [0x51b050]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x0040fbeau);
    hle_iat_call(ctx, mem, 0x0051b050u);
    // 0x0040fbea: pop esi
    uint32_t t15 = ctx.esp;
    uint32_t t16 = mem.r32(t15);
    uint32_t t17 = static_cast<uint32_t>(t15 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    ctx.esi = static_cast<uint32_t>(t16);
    // 0x0040fbeb: int3
    recomp_detail::trap_halt(ctx, 0x0040fbebu, "int3");
    return;
}
bb_0040fbca: {
    // 0x0040fbca: mov esi, dword ptr [esi]
    uint32_t t18 = mem.r32(ctx.esi);
    ctx.esi = static_cast<uint32_t>(t18);
    // 0x0040fbcc: test esi, esi
    uint32_t t19 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t19);
    // 0x0040fbce: je 0x40fbd8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fbd8;
    goto bb_0040fbd0;
}
bb_0040fb28: {
    // 0x0040fb28: mov eax, dword ptr [esi + 0x70]
    uint32_t t20 = static_cast<uint32_t>(ctx.esi + 0x00000070u);
    uint32_t t21 = mem.r32(t20);
    ctx.eax = static_cast<uint32_t>(t21);
    // 0x0040fb2b: push -1
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0xffffffffu);
    // 0x0040fb2d: push 0
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x00000000u);
    // 0x0040fb2f: push ebx
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, ctx.ebx);
    // 0x0040fb30: push eax
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, ctx.eax);
    // 0x0040fb31: call edi
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, 0x0040fb33u);
    call_indirect(ctx, mem, ctx.edi);
    // 0x0040fb33: cmp byte ptr [esi + 0x3c], 0
    uint32_t t27 = static_cast<uint32_t>(ctx.esi + 0x0000003cu);
    uint8_t t28 = mem.r8(t27);
    uint8_t t29 = static_cast<uint8_t>(static_cast<uint32_t>(t28) - static_cast<uint32_t>(uint8_t{0x00u}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, t28, uint8_t{0x00u}, t29);
    // 0x0040fb37: jne 0x40fbc1
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fbc1;
    goto bb_0040fb3d;
}
bb_0040fbd0: {
    // 0x0040fbd0: mov ecx, dword ptr [esi]
    uint32_t t30 = mem.r32(ctx.esi);
    ctx.ecx = static_cast<uint32_t>(t30);
    // 0x0040fbd2: mov edx, dword ptr [ecx + 0x48]
    uint32_t t31 = static_cast<uint32_t>(ctx.ecx + 0x00000048u);
    uint32_t t32 = mem.r32(t31);
    ctx.edx = static_cast<uint32_t>(t32);
    // 0x0040fbd5: push esi
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, ctx.esi);
    // 0x0040fbd6: call edx
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x0040fbd8u);
    call_indirect(ctx, mem, ctx.edx);
    goto bb_0040fbd8;
}
bb_0040fbc1: {
    // 0x0040fbc1: pop edi
    uint32_t t35 = ctx.esp;
    uint32_t t36 = mem.r32(t35);
    uint32_t t37 = static_cast<uint32_t>(t35 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    ctx.edi = static_cast<uint32_t>(t36);
    // 0x0040fbc2: pop ebx
    uint32_t t38 = ctx.esp;
    uint32_t t39 = mem.r32(t38);
    uint32_t t40 = static_cast<uint32_t>(t38 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    ctx.ebx = static_cast<uint32_t>(t39);
    goto bb_0040fbc3;
}
bb_0040fb3d: {
    // 0x0040fb3d: cmp eax, 3
    uint32_t t41 = static_cast<uint32_t>(ctx.eax - 0x00000003u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000003u, t41);
    // 0x0040fb40: jae 0x40fb89
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0040fb89;
    goto bb_0040fb42;
}
bb_0040fb89: {
    // 0x0040fb89: sub eax, 3
    uint32_t t42 = static_cast<uint32_t>(ctx.eax - 0x00000003u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000003u, t42);
    ctx.eax = static_cast<uint32_t>(t42);
    // 0x0040fb8c: je 0x40fbaa
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fbaa;
    goto bb_0040fb8e;
}
bb_0040fb42: {
    // 0x0040fb42: mov eax, dword ptr [esi + 8]
    uint32_t t43 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t44 = mem.r32(t43);
    ctx.eax = static_cast<uint32_t>(t44);
    // 0x0040fb45: test eax, eax
    uint32_t t45 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t45);
    // 0x0040fb47: mov ecx, dword ptr [esi + 0x40]
    uint32_t t46 = static_cast<uint32_t>(ctx.esi + 0x00000040u);
    uint32_t t47 = mem.r32(t46);
    ctx.ecx = static_cast<uint32_t>(t47);
    // 0x0040fb4a: jne 0x40fb69
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fb69;
    goto bb_0040fb4c;
}
bb_0040fbaa: {
    // 0x0040fbaa: cmp dword ptr [esi + 8], 1
    uint32_t t48 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t49 = mem.r32(t48);
    uint32_t t50 = static_cast<uint32_t>(t49 - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t49, 0x00000001u, t50);
    // 0x0040fbae: jne 0x40fbb7
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fbb7;
    goto bb_0040fbb0;
}
bb_0040fb8e: {
    // 0x0040fb8e: sub eax, 1
    uint32_t t51 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t51);
    ctx.eax = static_cast<uint32_t>(t51);
    // 0x0040fb91: jne 0x40fbb7
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fbb7;
    goto bb_0040fb93;
}
bb_0040fb69: {
    // 0x0040fb69: cmp eax, 1
    uint32_t t52 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t52);
    // 0x0040fb6c: jne 0x40fb75
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fb75;
    goto bb_0040fb6e;
}
bb_0040fb4c: {
    // 0x0040fb4c: mov eax, dword ptr [esi + 0x54]
    uint32_t t53 = static_cast<uint32_t>(ctx.esi + 0x00000054u);
    uint32_t t54 = mem.r32(t53);
    ctx.eax = static_cast<uint32_t>(t54);
    // 0x0040fb4f: sub eax, 1
    uint32_t t55 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t55);
    ctx.eax = static_cast<uint32_t>(t55);
    // 0x0040fb52: je 0x40fb61
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fb61;
    goto bb_0040fb54;
}
bb_0040fbb7: {
    // 0x0040fbb7: cmp byte ptr [esi + 0x3c], 0
    uint32_t t56 = static_cast<uint32_t>(ctx.esi + 0x0000003cu);
    uint8_t t57 = mem.r8(t56);
    uint8_t t58 = static_cast<uint8_t>(static_cast<uint32_t>(t57) - static_cast<uint32_t>(uint8_t{0x00u}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, t57, uint8_t{0x00u}, t58);
    // 0x0040fbbb: je 0x40fb28
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fb28;
    goto bb_0040fbc1;
}
bb_0040fbb0: {
    // 0x0040fbb0: mov dword ptr [esi + 8], 2
    uint32_t t59 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t59, 0x00000002u);
    goto bb_0040fbb7;
}
bb_0040fb93: {
    // 0x0040fb93: mov eax, dword ptr [esi + 4]
    uint32_t t60 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t61 = mem.r32(t60);
    ctx.eax = static_cast<uint32_t>(t61);
    // 0x0040fb96: test eax, eax
    uint32_t t62 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t62);
    // 0x0040fb98: je 0x40fbb7
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fbb7;
    goto bb_0040fb9a;
}
bb_0040fb75: {
    // 0x0040fb75: mov eax, dword ptr [esi + 0x40]
    uint32_t t63 = static_cast<uint32_t>(ctx.esi + 0x00000040u);
    uint32_t t64 = mem.r32(t63);
    ctx.eax = static_cast<uint32_t>(t64);
    // 0x0040fb78: add eax, 1
    uint32_t t65 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t65);
    ctx.eax = static_cast<uint32_t>(t65);
    // 0x0040fb7b: xor edx, edx
    uint32_t t66 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t66);
    ctx.edx = static_cast<uint32_t>(t66);
    // 0x0040fb7d: mov ecx, 3
    ctx.ecx = static_cast<uint32_t>(0x00000003u);
    // 0x0040fb82: div ecx
    uint64_t t67 = ((static_cast<uint64_t>(ctx.edx) << 32) | static_cast<uint64_t>(ctx.eax));
    uint32_t t68 = recomp_detail::div64_u(t67, ctx.ecx);
    uint32_t t69 = recomp_detail::mod64_u(t67, ctx.ecx);
    ctx.eax = static_cast<uint32_t>(t68);
    ctx.edx = static_cast<uint32_t>(t69);
    // 0x0040fb84: mov dword ptr [esi + 0x40], edx
    uint32_t t70 = static_cast<uint32_t>(ctx.esi + 0x00000040u);
    mem.w32(t70, ctx.edx);
    // 0x0040fb87: jmp 0x40fbb7
    goto bb_0040fbb7;
}
bb_0040fb6e: {
    // 0x0040fb6e: mov dword ptr [esi + 8], 2
    uint32_t t71 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t71, 0x00000002u);
    goto bb_0040fb75;
}
bb_0040fb61: {
    // 0x0040fb61: push ecx
    uint32_t t72 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    mem.w32(t72, ctx.ecx);
    // 0x0040fb62: call 0x40f8e0
    uint32_t t73 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    mem.w32(t73, 0x0040fb67u);
    sub_0040f8e0(ctx, mem);
    // 0x0040fb67: jmp 0x40fb75
    goto bb_0040fb75;
}
bb_0040fb54: {
    // 0x0040fb54: sub eax, 1
    uint32_t t74 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t74);
    ctx.eax = static_cast<uint32_t>(t74);
    // 0x0040fb57: jne 0x40fb75
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fb75;
    goto bb_0040fb59;
}
bb_0040fb9a: {
    // 0x0040fb9a: mov eax, dword ptr [eax]
    uint32_t t75 = mem.r32(ctx.eax);
    ctx.eax = static_cast<uint32_t>(t75);
    // 0x0040fb9c: test eax, eax
    uint32_t t76 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t76);
    // 0x0040fb9e: je 0x40fbb7
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fbb7;
    goto bb_0040fba0;
}
bb_0040fb59: {
    // 0x0040fb59: push ecx
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, ctx.ecx);
    // 0x0040fb5a: call 0x40f980
    uint32_t t78 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    mem.w32(t78, 0x0040fb5fu);
    sub_0040f980(ctx, mem);
    // 0x0040fb5f: jmp 0x40fb75
    goto bb_0040fb75;
}
bb_0040fba0: {
    // 0x0040fba0: mov edx, dword ptr [eax]
    uint32_t t79 = mem.r32(ctx.eax);
    ctx.edx = static_cast<uint32_t>(t79);
    // 0x0040fba2: push eax
    uint32_t t80 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    mem.w32(t80, ctx.eax);
    // 0x0040fba3: mov eax, dword ptr [edx + 0x48]
    uint32_t t81 = static_cast<uint32_t>(ctx.edx + 0x00000048u);
    uint32_t t82 = mem.r32(t81);
    ctx.eax = static_cast<uint32_t>(t82);
    // 0x0040fba6: call eax
    uint32_t t83 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t83);
    mem.w32(t83, 0x0040fba8u);
    call_indirect(ctx, mem, ctx.eax);
    // 0x0040fba8: jmp 0x40fbb7
    goto bb_0040fbb7;
}
}

// sub_0040fbf0 | subsystem=Sound | canonical | 23 blocks | 79 insns
void sub_0040fbf0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040fbf0: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x0040fbf1: mov dword ptr [ebx], edi
    mem.w32(ctx.ebx, ctx.edi);
    // 0x0040fbf3: mov edx, 4
    ctx.edx = static_cast<uint32_t>(0x00000004u);
    // 0x0040fbf8: mov eax, 0x535294
    ctx.eax = static_cast<uint32_t>(0x00535294u);
    // 0x0040fbfd: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x0040fbff: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
}
bb_0040fc00: {
    // 0x0040fc00: mov esi, dword ptr [ecx]
    uint32_t t2 = mem.r32(ctx.ecx);
    ctx.esi = static_cast<uint32_t>(t2);
    // 0x0040fc02: cmp esi, dword ptr [eax]
    uint32_t t3 = mem.r32(ctx.eax);
    uint32_t t4 = static_cast<uint32_t>(ctx.esi - t3);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, t3, t4);
    // 0x0040fc04: jne 0x40fc18
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fc18;
    goto bb_0040fc06;
}
bb_0040fc18: {
    // 0x0040fc18: movzx esi, byte ptr [ecx]
    uint8_t t5 = mem.r8(ctx.ecx);
    uint32_t t6 = static_cast<uint32_t>(static_cast<uint8_t>(t5));
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x0040fc1b: movzx ebp, byte ptr [eax]
    uint8_t t7 = mem.r8(ctx.eax);
    uint32_t t8 = static_cast<uint32_t>(static_cast<uint8_t>(t7));
    ctx.ebp = static_cast<uint32_t>(t8);
    // 0x0040fc1e: sub esi, ebp
    uint32_t t9 = static_cast<uint32_t>(ctx.esi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebp, t9);
    ctx.esi = static_cast<uint32_t>(t9);
    // 0x0040fc20: jne 0x40fc67
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fc67;
    goto bb_0040fc22;
}
bb_0040fc06: {
    // 0x0040fc06: sub edx, 4
    uint32_t t10 = static_cast<uint32_t>(ctx.edx - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000004u, t10);
    ctx.edx = static_cast<uint32_t>(t10);
    // 0x0040fc09: add eax, 4
    uint32_t t11 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000004u, t11);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x0040fc0c: add ecx, 4
    uint32_t t12 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000004u, t12);
    ctx.ecx = static_cast<uint32_t>(t12);
    // 0x0040fc0f: cmp edx, 4
    uint32_t t13 = static_cast<uint32_t>(ctx.edx - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000004u, t13);
    // 0x0040fc12: jae 0x40fc00
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_0040fc00;
    goto bb_0040fc14;
}
bb_0040fc67: {
    // 0x0040fc67: test esi, esi
    uint32_t t14 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    // 0x0040fc69: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0040fc6e: jg 0x40fc77
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_0040fc77;
    goto bb_0040fc70;
}
bb_0040fc22: {
    // 0x0040fc22: sub edx, 1
    uint32_t t15 = static_cast<uint32_t>(ctx.edx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000001u, t15);
    ctx.edx = static_cast<uint32_t>(t15);
    // 0x0040fc25: add eax, 1
    uint32_t t16 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t16);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x0040fc28: add ecx, 1
    uint32_t t17 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t17);
    ctx.ecx = static_cast<uint32_t>(t17);
    // 0x0040fc2b: test edx, edx
    uint32_t t18 = static_cast<uint32_t>(ctx.edx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    // 0x0040fc2d: je 0x40fc75
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fc75;
    goto bb_0040fc2f;
}
bb_0040fc14: {
    // 0x0040fc14: test edx, edx
    uint32_t t19 = static_cast<uint32_t>(ctx.edx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t19);
    // 0x0040fc16: je 0x40fc75
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fc75;
    goto bb_0040fc18;
}
bb_0040fc77: {
    // 0x0040fc77: test eax, eax
    uint32_t t20 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t20);
    // 0x0040fc79: pop esi
    uint32_t t21 = ctx.esp;
    uint32_t t22 = mem.r32(t21);
    uint32_t t23 = static_cast<uint32_t>(t21 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    ctx.esi = static_cast<uint32_t>(t22);
    // 0x0040fc7a: pop ebp
    uint32_t t24 = ctx.esp;
    uint32_t t25 = mem.r32(t24);
    uint32_t t26 = static_cast<uint32_t>(t24 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    ctx.ebp = static_cast<uint32_t>(t25);
    // 0x0040fc7b: je 0x40fc80
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fc80;
    goto bb_0040fc7d;
}
bb_0040fc70: {
    // 0x0040fc70: or eax, 0xffffffff
    uint32_t t27 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t27);
    ctx.eax = static_cast<uint32_t>(t27);
    // 0x0040fc73: jmp 0x40fc77
    goto bb_0040fc77;
}
bb_0040fc75: {
    // 0x0040fc75: xor eax, eax
    uint32_t t28 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t28);
    ctx.eax = static_cast<uint32_t>(t28);
    goto bb_0040fc77;
}
bb_0040fc2f: {
    // 0x0040fc2f: movzx esi, byte ptr [ecx]
    uint8_t t29 = mem.r8(ctx.ecx);
    uint32_t t30 = static_cast<uint32_t>(static_cast<uint8_t>(t29));
    ctx.esi = static_cast<uint32_t>(t30);
    // 0x0040fc32: movzx ebp, byte ptr [eax]
    uint8_t t31 = mem.r8(ctx.eax);
    uint32_t t32 = static_cast<uint32_t>(static_cast<uint8_t>(t31));
    ctx.ebp = static_cast<uint32_t>(t32);
    // 0x0040fc35: sub esi, ebp
    uint32_t t33 = static_cast<uint32_t>(ctx.esi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebp, t33);
    ctx.esi = static_cast<uint32_t>(t33);
    // 0x0040fc37: jne 0x40fc67
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fc67;
    goto bb_0040fc39;
}
bb_0040fc80: {
    // 0x0040fc80: lea eax, [edi + 1]
    uint32_t t34 = static_cast<uint32_t>(ctx.edi + 0x00000001u);
    ctx.eax = static_cast<uint32_t>(t34);
    goto bb_0040fc83;
}
bb_0040fc7d: {
    // 0x0040fc7d: xor eax, eax
    uint32_t t35 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t35);
    ctx.eax = static_cast<uint32_t>(t35);
    // 0x0040fc7f: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040fc39: {
    // 0x0040fc39: sub edx, 1
    uint32_t t36 = static_cast<uint32_t>(ctx.edx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000001u, t36);
    ctx.edx = static_cast<uint32_t>(t36);
    // 0x0040fc3c: add eax, 1
    uint32_t t37 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t37);
    ctx.eax = static_cast<uint32_t>(t37);
    // 0x0040fc3f: add ecx, 1
    uint32_t t38 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t38);
    ctx.ecx = static_cast<uint32_t>(t38);
    // 0x0040fc42: test edx, edx
    uint32_t t39 = static_cast<uint32_t>(ctx.edx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t39);
    // 0x0040fc44: je 0x40fc75
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fc75;
    goto bb_0040fc46;
}
bb_0040fc83: {
    // 0x0040fc83: add eax, 1
    uint32_t t40 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t40);
    ctx.eax = static_cast<uint32_t>(t40);
    // 0x0040fc86: cmp dword ptr [eax], 0x45564157
    uint32_t t41 = mem.r32(ctx.eax);
    uint32_t t42 = static_cast<uint32_t>(t41 - 0x45564157u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t41, 0x45564157u, t42);
    // 0x0040fc8c: jne 0x40fc83
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fc83;
    goto bb_0040fc8e;
}
bb_0040fc46: {
    // 0x0040fc46: movzx esi, byte ptr [ecx]
    uint8_t t43 = mem.r8(ctx.ecx);
    uint32_t t44 = static_cast<uint32_t>(static_cast<uint8_t>(t43));
    ctx.esi = static_cast<uint32_t>(t44);
    // 0x0040fc49: movzx ebp, byte ptr [eax]
    uint8_t t45 = mem.r8(ctx.eax);
    uint32_t t46 = static_cast<uint32_t>(static_cast<uint8_t>(t45));
    ctx.ebp = static_cast<uint32_t>(t46);
    // 0x0040fc4c: sub esi, ebp
    uint32_t t47 = static_cast<uint32_t>(ctx.esi - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebp, t47);
    ctx.esi = static_cast<uint32_t>(t47);
    // 0x0040fc4e: jne 0x40fc67
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fc67;
    goto bb_0040fc50;
}
bb_0040fc8e: {
    // 0x0040fc8e: mov edi, edi
    ctx.edi = static_cast<uint32_t>(ctx.edi);
    goto bb_0040fc90;
}
bb_0040fc50: {
    // 0x0040fc50: sub edx, 1
    uint32_t t48 = static_cast<uint32_t>(ctx.edx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000001u, t48);
    ctx.edx = static_cast<uint32_t>(t48);
    // 0x0040fc53: add eax, 1
    uint32_t t49 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t49);
    ctx.eax = static_cast<uint32_t>(t49);
    // 0x0040fc56: add ecx, 1
    uint32_t t50 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t50);
    ctx.ecx = static_cast<uint32_t>(t50);
    // 0x0040fc59: test edx, edx
    uint32_t t51 = static_cast<uint32_t>(ctx.edx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t51);
    // 0x0040fc5b: je 0x40fc75
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fc75;
    goto bb_0040fc5d;
}
bb_0040fc90: {
    // 0x0040fc90: add eax, 1
    uint32_t t52 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t52);
    ctx.eax = static_cast<uint32_t>(t52);
    // 0x0040fc93: cmp dword ptr [eax], 0x20746d66
    uint32_t t53 = mem.r32(ctx.eax);
    uint32_t t54 = static_cast<uint32_t>(t53 - 0x20746d66u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t53, 0x20746d66u, t54);
    // 0x0040fc99: jne 0x40fc90
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fc90;
    goto bb_0040fc9b;
}
bb_0040fc5d: {
    // 0x0040fc5d: movzx esi, byte ptr [ecx]
    uint8_t t55 = mem.r8(ctx.ecx);
    uint32_t t56 = static_cast<uint32_t>(static_cast<uint8_t>(t55));
    ctx.esi = static_cast<uint32_t>(t56);
    // 0x0040fc60: movzx eax, byte ptr [eax]
    uint8_t t57 = mem.r8(ctx.eax);
    uint32_t t58 = static_cast<uint32_t>(static_cast<uint8_t>(t57));
    ctx.eax = static_cast<uint32_t>(t58);
    // 0x0040fc63: sub esi, eax
    uint32_t t59 = static_cast<uint32_t>(ctx.esi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.eax, t59);
    ctx.esi = static_cast<uint32_t>(t59);
    // 0x0040fc65: je 0x40fc75
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fc75;
    goto bb_0040fc67;
}
bb_0040fc9b: {
    // 0x0040fc9b: add eax, 8
    uint32_t t60 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000008u, t60);
    ctx.eax = static_cast<uint32_t>(t60);
    // 0x0040fc9e: mov dword ptr [ebx + 4], eax
    uint32_t t61 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    mem.w32(t61, ctx.eax);
}
bb_0040fca1: {
    // 0x0040fca1: add eax, 1
    uint32_t t62 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t62);
    ctx.eax = static_cast<uint32_t>(t62);
    // 0x0040fca4: cmp dword ptr [eax], 0x61746164
    uint32_t t63 = mem.r32(ctx.eax);
    uint32_t t64 = static_cast<uint32_t>(t63 - 0x61746164u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t63, 0x61746164u, t64);
    // 0x0040fcaa: jne 0x40fca1
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fca1;
}
{
    // 0x0040fcac: mov ecx, dword ptr [eax + 4]
    uint32_t t65 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t66 = mem.r32(t65);
    ctx.ecx = static_cast<uint32_t>(t66);
    // 0x0040fcaf: add eax, 4
    uint32_t t67 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000004u, t67);
    ctx.eax = static_cast<uint32_t>(t67);
    // 0x0040fcb2: add eax, 4
    uint32_t t68 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000004u, t68);
    ctx.eax = static_cast<uint32_t>(t68);
    // 0x0040fcb5: mov dword ptr [ebx + 8], eax
    uint32_t t69 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    mem.w32(t69, ctx.eax);
    // 0x0040fcb8: mov dword ptr [ebx + 0xc], ecx
    uint32_t t70 = static_cast<uint32_t>(ctx.ebx + 0x0000000cu);
    mem.w32(t70, ctx.ecx);
    // 0x0040fcbb: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0040fcc0: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_0040fcd0 | subsystem=Sound | canonical | 13 blocks | 73 insns
void sub_0040fcd0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040fcd0: mov edx, dword ptr [ebx + 8]
    uint32_t t0 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t1 = mem.r32(t0);
    ctx.edx = static_cast<uint32_t>(t1);
    // 0x0040fcd3: test edx, edx
    uint32_t t2 = static_cast<uint32_t>(ctx.edx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    // 0x0040fcd5: push edi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.edi);
    // 0x0040fcd6: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x0040fcd8: jne 0x40fce0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fce0;
    goto bb_0040fcda;
}
bb_0040fce0: {
    // 0x0040fce0: mov ecx, dword ptr [ebx + 0xc]
    uint32_t t4 = static_cast<uint32_t>(ctx.ebx + 0x0000000cu);
    uint32_t t5 = mem.r32(t4);
    ctx.ecx = static_cast<uint32_t>(t5);
    // 0x0040fce3: cmp dword ptr [ebx + 0x10], ecx
    uint32_t t6 = static_cast<uint32_t>(ctx.ebx + 0x00000010u);
    uint32_t t7 = mem.r32(t6);
    uint32_t t8 = static_cast<uint32_t>(t7 - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t7, ctx.ecx, t8);
    // 0x0040fce6: jne 0x40fcf6
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fcf6;
    goto bb_0040fce8;
}
bb_0040fcda: {
    // 0x0040fcda: xor eax, eax
    uint32_t t9 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x0040fcdc: pop edi
    uint32_t t10 = ctx.esp;
    uint32_t t11 = mem.r32(t10);
    uint32_t t12 = static_cast<uint32_t>(t10 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    ctx.edi = static_cast<uint32_t>(t11);
    // 0x0040fcdd: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
bb_0040fcf6: {
    // 0x0040fcf6: mov eax, dword ptr [ebx + 0x10]
    uint32_t t13 = static_cast<uint32_t>(ctx.ebx + 0x00000010u);
    uint32_t t14 = mem.r32(t13);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x0040fcf9: push ebp
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.ebp);
    // 0x0040fcfa: lea ebp, [eax + edi]
    uint32_t t16 = static_cast<uint32_t>(ctx.eax + ctx.edi);
    ctx.ebp = static_cast<uint32_t>(t16);
    // 0x0040fcfd: cmp ebp, ecx
    uint32_t t17 = static_cast<uint32_t>(ctx.ebp - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebp, ctx.ecx, t17);
    // 0x0040fcff: push esi
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, ctx.esi);
    // 0x0040fd00: mov esi, edi
    ctx.esi = static_cast<uint32_t>(ctx.edi);
    // 0x0040fd02: jbe 0x40fd08
    if (recomp_detail::eval_cond(ctx, Cond::BE)) goto bb_0040fd08;
    goto bb_0040fd04;
}
bb_0040fce8: {
    // 0x0040fce8: cmp dword ptr [esp + 0xc], 0
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t20 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t20, 0x00000000u, t21);
    // 0x0040fced: je 0x40fd53
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fd53;
    goto bb_0040fcef;
}
bb_0040fd08: {
    // 0x0040fd08: mov ebp, dword ptr [esp + 0x10]
    uint32_t t22 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t23 = mem.r32(t22);
    ctx.ebp = static_cast<uint32_t>(t23);
    // 0x0040fd0c: push esi
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, ctx.esi);
    // 0x0040fd0d: add eax, edx
    uint32_t t25 = static_cast<uint32_t>(ctx.eax + ctx.edx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, ctx.edx, t25);
    ctx.eax = static_cast<uint32_t>(t25);
    // 0x0040fd0f: push eax
    uint32_t t26 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    mem.w32(t26, ctx.eax);
    // 0x0040fd10: push ebp
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, ctx.ebp);
    // 0x0040fd11: call 0x4e63c0
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x0040fd16u);
    hle_crt_004e63c0(ctx, mem);
    // 0x0040fd16: add dword ptr [ebx + 0x10], esi
    uint32_t t29 = static_cast<uint32_t>(ctx.ebx + 0x00000010u);
    uint32_t t30 = mem.r32(t29);
    uint32_t t31 = static_cast<uint32_t>(t30 + ctx.esi);
    recomp_detail::update_flags_add<uint32_t>(ctx, t30, ctx.esi, t31);
    mem.w32(t29, t31);
    // 0x0040fd19: add esp, 0xc
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t32);
    ctx.esp = static_cast<uint32_t>(t32);
    // 0x0040fd1c: cmp esi, edi
    uint32_t t33 = static_cast<uint32_t>(ctx.esi - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.edi, t33);
    // 0x0040fd1e: je 0x40fd7c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fd7c;
    goto bb_0040fd20;
}
bb_0040fd04: {
    // 0x0040fd04: sub ecx, eax
    uint32_t t34 = static_cast<uint32_t>(ctx.ecx - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.eax, t34);
    ctx.ecx = static_cast<uint32_t>(t34);
    // 0x0040fd06: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    goto bb_0040fd08;
}
bb_0040fd53: {
    // 0x0040fd53: mov eax, dword ptr [esp + 8]
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint32_t t36 = mem.r32(t35);
    ctx.eax = static_cast<uint32_t>(t36);
    // 0x0040fd57: push edi
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, ctx.edi);
    // 0x0040fd58: push 0
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, 0x00000000u);
    // 0x0040fd5a: push eax
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, ctx.eax);
    // 0x0040fd5b: call 0x4e6340
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, 0x0040fd60u);
    hle_crt_004e6340(ctx, mem);
    // 0x0040fd60: add esp, 0xc
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t41);
    ctx.esp = static_cast<uint32_t>(t41);
    // 0x0040fd63: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0040fd68: pop edi
    uint32_t t42 = ctx.esp;
    uint32_t t43 = mem.r32(t42);
    uint32_t t44 = static_cast<uint32_t>(t42 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    ctx.edi = static_cast<uint32_t>(t43);
    // 0x0040fd69: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
bb_0040fcef: {
    // 0x0040fcef: mov dword ptr [ebx + 0x10], 0
    uint32_t t45 = static_cast<uint32_t>(ctx.ebx + 0x00000010u);
    mem.w32(t45, 0x00000000u);
    goto bb_0040fcf6;
}
bb_0040fd7c: {
    // 0x0040fd7c: pop esi
    uint32_t t46 = ctx.esp;
    uint32_t t47 = mem.r32(t46);
    uint32_t t48 = static_cast<uint32_t>(t46 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    ctx.esi = static_cast<uint32_t>(t47);
    // 0x0040fd7d: pop ebp
    uint32_t t49 = ctx.esp;
    uint32_t t50 = mem.r32(t49);
    uint32_t t51 = static_cast<uint32_t>(t49 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    ctx.ebp = static_cast<uint32_t>(t50);
    // 0x0040fd7e: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0040fd83: pop edi
    uint32_t t52 = ctx.esp;
    uint32_t t53 = mem.r32(t52);
    uint32_t t54 = static_cast<uint32_t>(t52 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    ctx.edi = static_cast<uint32_t>(t53);
    // 0x0040fd84: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
bb_0040fd20: {
    // 0x0040fd20: cmp dword ptr [esp + 0x14], 0
    uint32_t t55 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t56 = mem.r32(t55);
    uint32_t t57 = static_cast<uint32_t>(t56 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t56, 0x00000000u, t57);
    // 0x0040fd25: je 0x40fd6c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fd6c;
    goto bb_0040fd27;
}
bb_0040fd6c: {
    // 0x0040fd6c: sub edi, esi
    uint32_t t58 = static_cast<uint32_t>(ctx.edi - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.esi, t58);
    ctx.edi = static_cast<uint32_t>(t58);
    // 0x0040fd6e: push edi
    uint32_t t59 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    mem.w32(t59, ctx.edi);
    // 0x0040fd6f: push 0
    uint32_t t60 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t60);
    mem.w32(t60, 0x00000000u);
    // 0x0040fd71: add esi, ebp
    uint32_t t61 = static_cast<uint32_t>(ctx.esi + ctx.ebp);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, ctx.ebp, t61);
    ctx.esi = static_cast<uint32_t>(t61);
    // 0x0040fd73: push esi
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, ctx.esi);
    // 0x0040fd74: call 0x4e6340
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, 0x0040fd79u);
    hle_crt_004e6340(ctx, mem);
    // 0x0040fd79: add esp, 0xc
    uint32_t t64 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t64);
    ctx.esp = static_cast<uint32_t>(t64);
    goto bb_0040fd7c;
}
bb_0040fd27: {
    // 0x0040fd27: mov edx, dword ptr [ebx + 8]
    uint32_t t65 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    uint32_t t66 = mem.r32(t65);
    ctx.edx = static_cast<uint32_t>(t66);
    // 0x0040fd2a: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x0040fd2c: sub ecx, esi
    uint32_t t67 = static_cast<uint32_t>(ctx.ecx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.esi, t67);
    ctx.ecx = static_cast<uint32_t>(t67);
    // 0x0040fd2e: push ecx
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, ctx.ecx);
    // 0x0040fd2f: push edx
    uint32_t t69 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    mem.w32(t69, ctx.edx);
    // 0x0040fd30: lea eax, [esi + ebp]
    uint32_t t70 = static_cast<uint32_t>(ctx.esi + ctx.ebp);
    ctx.eax = static_cast<uint32_t>(t70);
    // 0x0040fd33: push eax
    uint32_t t71 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t71);
    mem.w32(t71, ctx.eax);
    // 0x0040fd34: mov dword ptr [ebx + 0x10], 0
    uint32_t t72 = static_cast<uint32_t>(ctx.ebx + 0x00000010u);
    mem.w32(t72, 0x00000000u);
    // 0x0040fd3b: call 0x4e63c0
    uint32_t t73 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    mem.w32(t73, 0x0040fd40u);
    hle_crt_004e63c0(ctx, mem);
    // 0x0040fd40: add esp, 0xc
    uint32_t t74 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t74);
    ctx.esp = static_cast<uint32_t>(t74);
    // 0x0040fd43: sub edi, esi
    uint32_t t75 = static_cast<uint32_t>(ctx.edi - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.esi, t75);
    ctx.edi = static_cast<uint32_t>(t75);
    // 0x0040fd45: add dword ptr [ebx + 0x10], edi
    uint32_t t76 = static_cast<uint32_t>(ctx.ebx + 0x00000010u);
    uint32_t t77 = mem.r32(t76);
    uint32_t t78 = static_cast<uint32_t>(t77 + ctx.edi);
    recomp_detail::update_flags_add<uint32_t>(ctx, t77, ctx.edi, t78);
    mem.w32(t76, t78);
    // 0x0040fd48: pop esi
    uint32_t t79 = ctx.esp;
    uint32_t t80 = mem.r32(t79);
    uint32_t t81 = static_cast<uint32_t>(t79 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    ctx.esi = static_cast<uint32_t>(t80);
    // 0x0040fd49: pop ebp
    uint32_t t82 = ctx.esp;
    uint32_t t83 = mem.r32(t82);
    uint32_t t84 = static_cast<uint32_t>(t82 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    ctx.ebp = static_cast<uint32_t>(t83);
    // 0x0040fd4a: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0040fd4f: pop edi
    uint32_t t85 = ctx.esp;
    uint32_t t86 = mem.r32(t85);
    uint32_t t87 = static_cast<uint32_t>(t85 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t87);
    ctx.edi = static_cast<uint32_t>(t86);
    // 0x0040fd50: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
}

// sub_0040fd90 | subsystem=Sound | canonical | 6 blocks | 41 insns
void sub_0040fd90(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x0040fd90: mov eax, dword ptr [esi + 0x14]
    uint32_t t0 = static_cast<uint32_t>(ctx.esi + 0x00000014u);
    uint32_t t1 = mem.r32(t0);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x0040fd93: sub eax, 1
    uint32_t t2 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t2);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x0040fd96: push edi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.edi);
    // 0x0040fd97: mov edi, 0
    ctx.edi = static_cast<uint32_t>(0x00000000u);
    // 0x0040fd9c: je 0x40fdc2
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fdc2;
    goto bb_0040fd9e;
}
bb_0040fdc2: {
    // 0x0040fdc2: mov eax, dword ptr [esi]
    uint32_t t4 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x0040fdc4: push ebx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ebx);
    // 0x0040fdc5: push eax
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.eax);
    // 0x0040fdc6: call dword ptr [0x51b05c]
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x0040fdccu);
    hle_iat_call(ctx, mem, 0x0051b05cu);
    // 0x0040fdcc: mov ecx, dword ptr [esi + 0x1c]
    uint32_t t8 = static_cast<uint32_t>(ctx.esi + 0x0000001cu);
    uint32_t t9 = mem.r32(t8);
    ctx.ecx = static_cast<uint32_t>(t9);
    // 0x0040fdcf: mov ebx, dword ptr [0x51b1cc]
    uint32_t t10 = mem.r32(0x0051b1ccu);
    ctx.ebx = static_cast<uint32_t>(t10);
    // 0x0040fdd5: push ecx
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.ecx);
    // 0x0040fdd6: call ebx
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x0040fdd8u);
    call_indirect(ctx, mem, ctx.ebx);
    // 0x0040fdd8: mov edx, dword ptr [esi + 0x18]
    uint32_t t13 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    uint32_t t14 = mem.r32(t13);
    ctx.edx = static_cast<uint32_t>(t14);
    // 0x0040fddb: push edx
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.edx);
    // 0x0040fddc: call ebx
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x0040fddeu);
    call_indirect(ctx, mem, ctx.ebx);
    // 0x0040fdde: mov dword ptr [esi + 0x18], edi
    uint32_t t17 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    mem.w32(t17, ctx.edi);
    // 0x0040fde1: mov dword ptr [esi + 0x1c], edi
    uint32_t t18 = static_cast<uint32_t>(ctx.esi + 0x0000001cu);
    mem.w32(t18, ctx.edi);
    // 0x0040fde4: pop ebx
    uint32_t t19 = ctx.esp;
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t19 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    ctx.ebx = static_cast<uint32_t>(t20);
    // 0x0040fde5: mov dword ptr [esi], edi
    mem.w32(ctx.esi, ctx.edi);
    goto bb_0040fde7;
}
bb_0040fd9e: {
    // 0x0040fd9e: sub eax, 1
    uint32_t t22 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t22);
    ctx.eax = static_cast<uint32_t>(t22);
    // 0x0040fda1: jne 0x40fde7
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_0040fde7;
    goto bb_0040fda3;
}
bb_0040fde7: {
    // 0x0040fde7: mov dword ptr [esi + 8], edi
    uint32_t t23 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t23, ctx.edi);
    // 0x0040fdea: mov dword ptr [esi + 4], edi
    uint32_t t24 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t24, ctx.edi);
    // 0x0040fded: mov dword ptr [esi + 0xc], edi
    uint32_t t25 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t25, ctx.edi);
    // 0x0040fdf0: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x0040fdf5: pop edi
    uint32_t t26 = ctx.esp;
    uint32_t t27 = mem.r32(t26);
    uint32_t t28 = static_cast<uint32_t>(t26 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    ctx.edi = static_cast<uint32_t>(t27);
    // 0x0040fdf6: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_0040fda3: {
    // 0x0040fda3: mov eax, dword ptr [esi]
    uint32_t t29 = mem.r32(ctx.esi);
    ctx.eax = static_cast<uint32_t>(t29);
    // 0x0040fda5: cmp eax, edi
    uint32_t t30 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t30);
    // 0x0040fda7: je 0x40fde7
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_0040fde7;
}
{
    // 0x0040fda9: push eax
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, ctx.eax);
    // 0x0040fdaa: call 0x4e00d0
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x0040fdafu);
    hle_crt_004e00d0(ctx, mem);
    // 0x0040fdaf: add esp, 4
    uint32_t t33 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t33);
    ctx.esp = static_cast<uint32_t>(t33);
    // 0x0040fdb2: mov dword ptr [esi], edi
    mem.w32(ctx.esi, ctx.edi);
    // 0x0040fdb4: mov dword ptr [esi + 8], edi
    uint32_t t34 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w32(t34, ctx.edi);
    // 0x0040fdb7: mov dword ptr [esi + 4], edi
    uint32_t t35 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t35, ctx.edi);
    // 0x0040fdba: mov dword ptr [esi + 0xc], edi
    uint32_t t36 = static_cast<uint32_t>(ctx.esi + 0x0000000cu);
    mem.w32(t36, ctx.edi);
    // 0x0040fdbd: lea eax, [edi + 1]
    uint32_t t37 = static_cast<uint32_t>(ctx.edi + 0x00000001u);
    ctx.eax = static_cast<uint32_t>(t37);
    // 0x0040fdc0: pop edi
    uint32_t t38 = ctx.esp;
    uint32_t t39 = mem.r32(t38);
    uint32_t t40 = static_cast<uint32_t>(t38 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    ctx.edi = static_cast<uint32_t>(t39);
    // 0x0040fdc1: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00416ad0 | subsystem=Sound | canonical | 7 blocks | 27 insns
void sub_00416ad0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00416ad0: xor eax, eax
    uint32_t t0 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.eax = static_cast<uint32_t>(t0);
    // 0x00416ad2: mov dword ptr [ecx + 8], eax
    uint32_t t1 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    mem.w32(t1, ctx.eax);
    // 0x00416ad5: mov dword ptr [ecx + 0xc], eax
    uint32_t t2 = static_cast<uint32_t>(ctx.ecx + 0x0000000cu);
    mem.w32(t2, ctx.eax);
    // 0x00416ad8: mov dword ptr [ecx + 0x10], eax
    uint32_t t3 = static_cast<uint32_t>(ctx.ecx + 0x00000010u);
    mem.w32(t3, ctx.eax);
    // 0x00416adb: mov dword ptr [ecx + 0x14], eax
    uint32_t t4 = static_cast<uint32_t>(ctx.ecx + 0x00000014u);
    mem.w32(t4, ctx.eax);
    // 0x00416ade: mov eax, dword ptr [esp + 4]
    uint32_t t5 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint32_t t6 = mem.r32(t5);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x00416ae2: sub eax, 0
    uint32_t t7 = static_cast<uint32_t>(ctx.eax - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000000u, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x00416ae5: je 0x416b2d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00416b2d;
    goto bb_00416ae7;
}
bb_00416b2d: {
    // 0x00416b2d: mov dword ptr [edx], 0x416940
    mem.w32(ctx.edx, 0x00416940u);
    // 0x00416b33: mov dword ptr [edx + 4], 0x416980
    uint32_t t8 = static_cast<uint32_t>(ctx.edx + 0x00000004u);
    mem.w32(t8, 0x00416980u);
    // 0x00416b3a: mov dword ptr [edx + 8], 0x4169d0
    uint32_t t9 = static_cast<uint32_t>(ctx.edx + 0x00000008u);
    mem.w32(t9, 0x004169d0u);
    // 0x00416b41: mov dword ptr [edx + 0xc], 0x4169e0
    uint32_t t10 = static_cast<uint32_t>(ctx.edx + 0x0000000cu);
    mem.w32(t10, 0x004169e0u);
    goto bb_00416b48;
}
bb_00416ae7: {
    // 0x00416ae7: sub eax, 1
    uint32_t t11 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t11);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x00416aea: je 0x416b0f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00416b0f;
    goto bb_00416aec;
}
bb_00416b48: {
    // 0x00416b48: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_00416b0f: {
    // 0x00416b0f: mov dword ptr [edx], 0x416a00
    mem.w32(ctx.edx, 0x00416a00u);
    // 0x00416b15: mov dword ptr [edx + 4], 0x416a50
    uint32_t t12 = static_cast<uint32_t>(ctx.edx + 0x00000004u);
    mem.w32(t12, 0x00416a50u);
    // 0x00416b1c: mov dword ptr [edx + 8], 0x4a0130
    uint32_t t13 = static_cast<uint32_t>(ctx.edx + 0x00000008u);
    mem.w32(t13, 0x004a0130u);
    // 0x00416b23: mov dword ptr [edx + 0xc], 0x416ac0
    uint32_t t14 = static_cast<uint32_t>(ctx.edx + 0x0000000cu);
    mem.w32(t14, 0x00416ac0u);
    // 0x00416b2a: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_00416aec: {
    // 0x00416aec: sub eax, 2
    uint32_t t15 = static_cast<uint32_t>(ctx.eax - 0x00000002u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000002u, t15);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x00416aef: jne 0x416b48
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00416b48;
}
{
    // 0x00416af1: mov dword ptr [edx], 0x416a00
    mem.w32(ctx.edx, 0x00416a00u);
    // 0x00416af7: mov dword ptr [edx + 4], 0x416a50
    uint32_t t16 = static_cast<uint32_t>(ctx.edx + 0x00000004u);
    mem.w32(t16, 0x00416a50u);
    // 0x00416afe: mov dword ptr [edx + 8], 0x4a0130
    uint32_t t17 = static_cast<uint32_t>(ctx.edx + 0x00000008u);
    mem.w32(t17, 0x004a0130u);
    // 0x00416b05: mov dword ptr [edx + 0xc], 0x416ac0
    uint32_t t18 = static_cast<uint32_t>(ctx.edx + 0x0000000cu);
    mem.w32(t18, 0x00416ac0u);
    // 0x00416b0c: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
}

// sub_00416b50 | subsystem=Sound | canonical | 1 blocks | 23 insns
void sub_00416b50(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00416b50: push edi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.edi);
    // 0x00416b51: push 0x2d0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x000002d0u);
    // 0x00416b56: xor edi, edi
    uint32_t t2 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.edi = static_cast<uint32_t>(t2);
    // 0x00416b58: lea eax, [esi + 0x20]
    uint32_t t3 = static_cast<uint32_t>(ctx.esi + 0x00000020u);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x00416b5b: push edi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.edi);
    // 0x00416b5c: push eax
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.eax);
    // 0x00416b5d: call 0x4e6340
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x00416b62u);
    hle_crt_004e6340(ctx, mem);
    // 0x00416b62: fldz
    ctx.fpu_push(0.0);
    // 0x00416b64: xor eax, eax
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x00416b66: mov dword ptr [esi + 0x310], eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esi + 0x00000310u);
    mem.w32(t8, ctx.eax);
    // 0x00416b6c: mov dword ptr [esi + 0x314], eax
    uint32_t t9 = static_cast<uint32_t>(ctx.esi + 0x00000314u);
    mem.w32(t9, ctx.eax);
    // 0x00416b72: mov dword ptr [esi + 0x318], eax
    uint32_t t10 = static_cast<uint32_t>(ctx.esi + 0x00000318u);
    mem.w32(t10, ctx.eax);
    // 0x00416b78: mov dword ptr [esi + 0x31c], eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esi + 0x0000031cu);
    mem.w32(t11, ctx.eax);
    // 0x00416b7e: fstp qword ptr [esi + 0x308]
    double t12 = ctx.fpu_st(0);
    uint32_t t13 = static_cast<uint32_t>(ctx.esi + 0x00000308u);
    mem.wf64(t13, t12);
    ctx.fpu_pop();
    // 0x00416b84: add esp, 0xc
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t14);
    ctx.esp = static_cast<uint32_t>(t14);
    // 0x00416b87: mov dword ptr [esi + 4], edi
    uint32_t t15 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t15, ctx.edi);
    // 0x00416b8a: mov dword ptr [esi + 0x18], edi
    uint32_t t16 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    mem.w32(t16, ctx.edi);
    // 0x00416b8d: mov dword ptr [esi + 0x324], edi
    uint32_t t17 = static_cast<uint32_t>(ctx.esi + 0x00000324u);
    mem.w32(t17, ctx.edi);
    // 0x00416b93: mov dword ptr [esi + 0x320], edi
    uint32_t t18 = static_cast<uint32_t>(ctx.esi + 0x00000320u);
    mem.w32(t18, ctx.edi);
    // 0x00416b99: mov dword ptr [esi], 0xffffffff
    mem.w32(ctx.esi, 0xffffffffu);
    // 0x00416b9f: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x00416ba1: pop edi
    uint32_t t19 = ctx.esp;
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t19 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    ctx.edi = static_cast<uint32_t>(t20);
    // 0x00416ba2: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00416bb0 | subsystem=Sound | canonical | 12 blocks | 52 insns
void sub_00416bb0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00416bb0: xor ecx, ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t0);
    ctx.ecx = static_cast<uint32_t>(t0);
    // 0x00416bb2: mov dword ptr [eax], ecx
    mem.w32(ctx.eax, ctx.ecx);
    // 0x00416bb4: mov dword ptr [eax + 4], ecx
    uint32_t t1 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w32(t1, ctx.ecx);
    // 0x00416bb7: mov dword ptr [eax + 8], ecx
    uint32_t t2 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    mem.w32(t2, ctx.ecx);
    // 0x00416bba: mov dword ptr [eax + 0xc], ecx
    uint32_t t3 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    mem.w32(t3, ctx.ecx);
    // 0x00416bbd: mov word ptr [eax + 0x10], 0x12
    uint32_t t4 = static_cast<uint32_t>(ctx.eax + 0x00000010u);
    mem.w16(t4, uint16_t{0x0012u});
    // 0x00416bc3: mov word ptr [eax], 1
    mem.w16(ctx.eax, uint16_t{0x0001u});
    // 0x00416bc8: mov ecx, dword ptr [edx + 0x18]
    uint32_t t5 = static_cast<uint32_t>(ctx.edx + 0x00000018u);
    uint32_t t6 = mem.r32(t5);
    ctx.ecx = static_cast<uint32_t>(t6);
    // 0x00416bcb: test ecx, ecx
    uint32_t t7 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    // 0x00416bcd: je 0x416bd4
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00416bd4;
    goto bb_00416bcf;
}
bb_00416bd4: {
    // 0x00416bd4: xor ecx, ecx
    uint32_t t8 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t8);
    ctx.ecx = static_cast<uint32_t>(t8);
    goto bb_00416bd6;
}
bb_00416bcf: {
    // 0x00416bcf: mov ecx, dword ptr [ecx + 4]
    uint32_t t9 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    uint32_t t10 = mem.r32(t9);
    ctx.ecx = static_cast<uint32_t>(t10);
    // 0x00416bd2: jmp 0x416bd6
}
bb_00416bd6: {
    // 0x00416bd6: mov word ptr [eax + 2], cx
    uint32_t t11 = static_cast<uint32_t>(ctx.eax + 0x00000002u);
    mem.w16(t11, recomp_detail::r16(ctx.ecx));
    // 0x00416bda: mov ecx, dword ptr [edx + 0x18]
    uint32_t t12 = static_cast<uint32_t>(ctx.edx + 0x00000018u);
    uint32_t t13 = mem.r32(t12);
    ctx.ecx = static_cast<uint32_t>(t13);
    // 0x00416bdd: test ecx, ecx
    uint32_t t14 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    // 0x00416bdf: je 0x416be6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00416be6;
    goto bb_00416be1;
}
bb_00416be6: {
    // 0x00416be6: xor ecx, ecx
    uint32_t t15 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t15);
    ctx.ecx = static_cast<uint32_t>(t15);
    goto bb_00416be8;
}
bb_00416be1: {
    // 0x00416be1: mov ecx, dword ptr [ecx + 8]
    uint32_t t16 = static_cast<uint32_t>(ctx.ecx + 0x00000008u);
    uint32_t t17 = mem.r32(t16);
    ctx.ecx = static_cast<uint32_t>(t17);
    // 0x00416be4: jmp 0x416be8
}
bb_00416be8: {
    // 0x00416be8: mov dword ptr [eax + 4], ecx
    uint32_t t18 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w32(t18, ctx.ecx);
    // 0x00416beb: cmp dword ptr [edx + 0x18], 0
    uint32_t t19 = static_cast<uint32_t>(ctx.edx + 0x00000018u);
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t20 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t20, 0x00000000u, t21);
    // 0x00416bef: je 0x416c01
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00416c01;
    goto bb_00416bf1;
}
bb_00416c01: {
    // 0x00416c01: xor ecx, ecx
    uint32_t t22 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t22);
    ctx.ecx = static_cast<uint32_t>(t22);
    goto bb_00416c03;
}
bb_00416bf1: {
    // 0x00416bf1: push esi
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, ctx.esi);
    // 0x00416bf2: mov esi, dword ptr [edx + 0x18]
    uint32_t t24 = static_cast<uint32_t>(ctx.edx + 0x00000018u);
    uint32_t t25 = mem.r32(t24);
    ctx.esi = static_cast<uint32_t>(t25);
    // 0x00416bf5: mov ecx, dword ptr [esi + 8]
    uint32_t t26 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    uint32_t t27 = mem.r32(t26);
    ctx.ecx = static_cast<uint32_t>(t27);
    // 0x00416bf8: imul ecx, dword ptr [esi + 4]
    uint32_t t28 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t29 = mem.r32(t28);
    uint64_t t30 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.ecx)) * static_cast<int64_t>(static_cast<int32_t>(t29)));
    uint32_t t31 = static_cast<uint32_t>(t30);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t30);
    ctx.ecx = static_cast<uint32_t>(t31);
    // 0x00416bfc: add ecx, ecx
    uint32_t t32 = static_cast<uint32_t>(ctx.ecx + ctx.ecx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, ctx.ecx, t32);
    ctx.ecx = static_cast<uint32_t>(t32);
    // 0x00416bfe: pop esi
    uint32_t t33 = ctx.esp;
    uint32_t t34 = mem.r32(t33);
    uint32_t t35 = static_cast<uint32_t>(t33 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    ctx.esi = static_cast<uint32_t>(t34);
    // 0x00416bff: jmp 0x416c03
}
bb_00416c03: {
    // 0x00416c03: mov dword ptr [eax + 8], ecx
    uint32_t t36 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    mem.w32(t36, ctx.ecx);
    // 0x00416c06: mov ecx, dword ptr [edx + 0x18]
    uint32_t t37 = static_cast<uint32_t>(ctx.edx + 0x00000018u);
    uint32_t t38 = mem.r32(t37);
    ctx.ecx = static_cast<uint32_t>(t38);
    // 0x00416c09: test ecx, ecx
    uint32_t t39 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t39);
    // 0x00416c0b: je 0x416c25
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00416c25;
    goto bb_00416c0d;
}
bb_00416c25: {
    // 0x00416c25: xor ecx, ecx
    uint32_t t40 = static_cast<uint32_t>(ctx.ecx ^ ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t40);
    ctx.ecx = static_cast<uint32_t>(t40);
    // 0x00416c27: mov word ptr [eax + 0xc], cx
    uint32_t t41 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    mem.w16(t41, recomp_detail::r16(ctx.ecx));
    // 0x00416c2b: mov ecx, dword ptr [edx + 0x18]
    uint32_t t42 = static_cast<uint32_t>(ctx.edx + 0x00000018u);
    uint32_t t43 = mem.r32(t42);
    ctx.ecx = static_cast<uint32_t>(t43);
    // 0x00416c2e: neg ecx
    uint32_t t44 = static_cast<uint32_t>(0u - ctx.ecx);
    recomp_detail::update_flags_neg<uint32_t>(ctx, ctx.ecx, t44);
    ctx.ecx = static_cast<uint32_t>(t44);
    // 0x00416c30: sbb ecx, ecx
    uint32_t t45 = recomp_detail::get_flag(ctx, kFlagCF);
    uint32_t t46 = static_cast<uint32_t>(ctx.ecx - ctx.ecx);
    uint32_t t47 = static_cast<uint32_t>(t46 - t45);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ecx, t47, t45);
    ctx.ecx = static_cast<uint32_t>(t47);
    // 0x00416c32: and ecx, 0x10
    uint32_t t48 = static_cast<uint32_t>(ctx.ecx & 0x00000010u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t48);
    ctx.ecx = static_cast<uint32_t>(t48);
    // 0x00416c35: mov word ptr [eax + 0xe], cx
    uint32_t t49 = static_cast<uint32_t>(ctx.eax + 0x0000000eu);
    mem.w16(t49, recomp_detail::r16(ctx.ecx));
    // 0x00416c39: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00416c0d: {
    // 0x00416c0d: mov ecx, dword ptr [ecx + 4]
    uint32_t t50 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    uint32_t t51 = mem.r32(t50);
    ctx.ecx = static_cast<uint32_t>(t51);
    // 0x00416c10: add ecx, ecx
    uint32_t t52 = static_cast<uint32_t>(ctx.ecx + ctx.ecx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, ctx.ecx, t52);
    ctx.ecx = static_cast<uint32_t>(t52);
    // 0x00416c12: mov word ptr [eax + 0xc], cx
    uint32_t t53 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    mem.w16(t53, recomp_detail::r16(ctx.ecx));
    // 0x00416c16: mov ecx, dword ptr [edx + 0x18]
    uint32_t t54 = static_cast<uint32_t>(ctx.edx + 0x00000018u);
    uint32_t t55 = mem.r32(t54);
    ctx.ecx = static_cast<uint32_t>(t55);
    // 0x00416c19: neg ecx
    uint32_t t56 = static_cast<uint32_t>(0u - ctx.ecx);
    recomp_detail::update_flags_neg<uint32_t>(ctx, ctx.ecx, t56);
    ctx.ecx = static_cast<uint32_t>(t56);
    // 0x00416c1b: sbb ecx, ecx
    uint32_t t57 = recomp_detail::get_flag(ctx, kFlagCF);
    uint32_t t58 = static_cast<uint32_t>(ctx.ecx - ctx.ecx);
    uint32_t t59 = static_cast<uint32_t>(t58 - t57);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ecx, t59, t57);
    ctx.ecx = static_cast<uint32_t>(t59);
    // 0x00416c1d: and ecx, 0x10
    uint32_t t60 = static_cast<uint32_t>(ctx.ecx & 0x00000010u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t60);
    ctx.ecx = static_cast<uint32_t>(t60);
    // 0x00416c20: mov word ptr [eax + 0xe], cx
    uint32_t t61 = static_cast<uint32_t>(ctx.eax + 0x0000000eu);
    mem.w16(t61, recomp_detail::r16(ctx.ecx));
    // 0x00416c24: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00416c40 | subsystem=Sound | canonical | 22 blocks | 143 insns
void sub_00416c40(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00416c40: push ebx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebx);
    // 0x00416c41: push ebp
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.ebp);
    // 0x00416c42: mov ebp, dword ptr [esp + 0xc]
    uint32_t t2 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t3 = mem.r32(t2);
    ctx.ebp = static_cast<uint32_t>(t3);
    // 0x00416c46: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x00416c47: push edi
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.edi);
    // 0x00416c48: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x00416c4a: call 0x416e30
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x00416c4fu);
    sub_00416e30(ctx, mem);
    // 0x00416c4f: mov ecx, dword ptr [ebp]
    uint32_t t7 = mem.r32(ctx.ebp);
    ctx.ecx = static_cast<uint32_t>(t7);
    // 0x00416c52: test ecx, ecx
    uint32_t t8 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t8);
    // 0x00416c54: je 0x416d97
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00416d97;
    goto bb_00416c5a;
}
bb_00416d97: {
    // 0x00416d97: xor eax, eax
    uint32_t t9 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t9);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x00416d99: pop edi
    uint32_t t10 = ctx.esp;
    uint32_t t11 = mem.r32(t10);
    uint32_t t12 = static_cast<uint32_t>(t10 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    ctx.edi = static_cast<uint32_t>(t11);
    // 0x00416d9a: pop esi
    uint32_t t13 = ctx.esp;
    uint32_t t14 = mem.r32(t13);
    uint32_t t15 = static_cast<uint32_t>(t13 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    ctx.esi = static_cast<uint32_t>(t14);
    // 0x00416d9b: pop ebp
    uint32_t t16 = ctx.esp;
    uint32_t t17 = mem.r32(t16);
    uint32_t t18 = static_cast<uint32_t>(t16 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    ctx.ebp = static_cast<uint32_t>(t17);
    // 0x00416d9c: pop ebx
    uint32_t t19 = ctx.esp;
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t19 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    ctx.ebx = static_cast<uint32_t>(t20);
    // 0x00416d9d: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_00416c5a: {
    // 0x00416c5a: mov edx, 4
    ctx.edx = static_cast<uint32_t>(0x00000004u);
    // 0x00416c5f: mov eax, 0x53528c
    ctx.eax = static_cast<uint32_t>(0x0053528cu);
}
bb_00416c64: {
    // 0x00416c64: mov edi, dword ptr [ecx]
    uint32_t t22 = mem.r32(ctx.ecx);
    ctx.edi = static_cast<uint32_t>(t22);
    // 0x00416c66: cmp edi, dword ptr [eax]
    uint32_t t23 = mem.r32(ctx.eax);
    uint32_t t24 = static_cast<uint32_t>(ctx.edi - t23);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, t23, t24);
    // 0x00416c68: jne 0x416c7c
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00416c7c;
    goto bb_00416c6a;
}
bb_00416c7c: {
    // 0x00416c7c: movzx edi, byte ptr [ecx]
    uint8_t t25 = mem.r8(ctx.ecx);
    uint32_t t26 = static_cast<uint32_t>(static_cast<uint8_t>(t25));
    ctx.edi = static_cast<uint32_t>(t26);
    // 0x00416c7f: movzx ebx, byte ptr [eax]
    uint8_t t27 = mem.r8(ctx.eax);
    uint32_t t28 = static_cast<uint32_t>(static_cast<uint8_t>(t27));
    ctx.ebx = static_cast<uint32_t>(t28);
    // 0x00416c82: sub edi, ebx
    uint32_t t29 = static_cast<uint32_t>(ctx.edi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebx, t29);
    ctx.edi = static_cast<uint32_t>(t29);
    // 0x00416c84: jne 0x416ccb
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00416ccb;
    goto bb_00416c86;
}
bb_00416c6a: {
    // 0x00416c6a: sub edx, 4
    uint32_t t30 = static_cast<uint32_t>(ctx.edx - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000004u, t30);
    ctx.edx = static_cast<uint32_t>(t30);
    // 0x00416c6d: add eax, 4
    uint32_t t31 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000004u, t31);
    ctx.eax = static_cast<uint32_t>(t31);
    // 0x00416c70: add ecx, 4
    uint32_t t32 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000004u, t32);
    ctx.ecx = static_cast<uint32_t>(t32);
    // 0x00416c73: cmp edx, 4
    uint32_t t33 = static_cast<uint32_t>(ctx.edx - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000004u, t33);
    // 0x00416c76: jae 0x416c64
    if (recomp_detail::eval_cond(ctx, Cond::AE)) goto bb_00416c64;
    goto bb_00416c78;
}
bb_00416ccb: {
    // 0x00416ccb: test edi, edi
    uint32_t t34 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t34);
    // 0x00416ccd: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x00416cd2: jg 0x416cdb
    if (recomp_detail::eval_cond(ctx, Cond::G)) goto bb_00416cdb;
    goto bb_00416cd4;
}
bb_00416c86: {
    // 0x00416c86: sub edx, 1
    uint32_t t35 = static_cast<uint32_t>(ctx.edx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000001u, t35);
    ctx.edx = static_cast<uint32_t>(t35);
    // 0x00416c89: add eax, 1
    uint32_t t36 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t36);
    ctx.eax = static_cast<uint32_t>(t36);
    // 0x00416c8c: add ecx, 1
    uint32_t t37 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t37);
    ctx.ecx = static_cast<uint32_t>(t37);
    // 0x00416c8f: test edx, edx
    uint32_t t38 = static_cast<uint32_t>(ctx.edx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t38);
    // 0x00416c91: je 0x416cd9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00416cd9;
    goto bb_00416c93;
}
bb_00416c78: {
    // 0x00416c78: test edx, edx
    uint32_t t39 = static_cast<uint32_t>(ctx.edx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t39);
    // 0x00416c7a: je 0x416cd9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00416cd9;
    goto bb_00416c7c;
}
bb_00416cdb: {
    // 0x00416cdb: test eax, eax
    uint32_t t40 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t40);
    // 0x00416cdd: jne 0x416d97
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00416d97;
    goto bb_00416ce3;
}
bb_00416cd4: {
    // 0x00416cd4: or eax, 0xffffffff
    uint32_t t41 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t41);
    ctx.eax = static_cast<uint32_t>(t41);
    // 0x00416cd7: jmp 0x416cdb
    goto bb_00416cdb;
}
bb_00416cd9: {
    // 0x00416cd9: xor eax, eax
    uint32_t t42 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t42);
    ctx.eax = static_cast<uint32_t>(t42);
    goto bb_00416cdb;
}
bb_00416c93: {
    // 0x00416c93: movzx edi, byte ptr [ecx]
    uint8_t t43 = mem.r8(ctx.ecx);
    uint32_t t44 = static_cast<uint32_t>(static_cast<uint8_t>(t43));
    ctx.edi = static_cast<uint32_t>(t44);
    // 0x00416c96: movzx ebx, byte ptr [eax]
    uint8_t t45 = mem.r8(ctx.eax);
    uint32_t t46 = static_cast<uint32_t>(static_cast<uint8_t>(t45));
    ctx.ebx = static_cast<uint32_t>(t46);
    // 0x00416c99: sub edi, ebx
    uint32_t t47 = static_cast<uint32_t>(ctx.edi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebx, t47);
    ctx.edi = static_cast<uint32_t>(t47);
    // 0x00416c9b: jne 0x416ccb
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00416ccb;
    goto bb_00416c9d;
}
bb_00416ce3: {
    // 0x00416ce3: lea edi, [esi + 8]
    uint32_t t48 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    ctx.edi = static_cast<uint32_t>(t48);
    // 0x00416ce6: push 1
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, 0x00000001u);
    // 0x00416ce8: mov edx, edi
    ctx.edx = static_cast<uint32_t>(ctx.edi);
    // 0x00416cea: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x00416cec: mov dword ptr [esi], 1
    mem.w32(ctx.esi, 0x00000001u);
    // 0x00416cf2: call 0x416ad0
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, 0x00416cf7u);
    sub_00416ad0(ctx, mem);
    // 0x00416cf7: mov ecx, dword ptr [ebp]
    uint32_t t51 = mem.r32(ctx.ebp);
    ctx.ecx = static_cast<uint32_t>(t51);
    // 0x00416cfa: mov dword ptr [esi + 0x310], ecx
    uint32_t t52 = static_cast<uint32_t>(ctx.esi + 0x00000310u);
    mem.w32(t52, ctx.ecx);
    // 0x00416d00: mov edx, dword ptr [ebp + 4]
    uint32_t t53 = static_cast<uint32_t>(ctx.ebp + 0x00000004u);
    uint32_t t54 = mem.r32(t53);
    ctx.edx = static_cast<uint32_t>(t54);
    // 0x00416d03: lea ebx, [esi + 0x310]
    uint32_t t55 = static_cast<uint32_t>(ctx.esi + 0x00000310u);
    ctx.ebx = static_cast<uint32_t>(t55);
    // 0x00416d09: mov dword ptr [ebx + 4], edx
    uint32_t t56 = static_cast<uint32_t>(ctx.ebx + 0x00000004u);
    mem.w32(t56, ctx.edx);
    // 0x00416d0c: mov eax, dword ptr [ebp + 8]
    uint32_t t57 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t58 = mem.r32(t57);
    ctx.eax = static_cast<uint32_t>(t58);
    // 0x00416d0f: mov dword ptr [ebx + 8], eax
    uint32_t t59 = static_cast<uint32_t>(ctx.ebx + 0x00000008u);
    mem.w32(t59, ctx.eax);
    // 0x00416d12: mov ecx, dword ptr [ebp + 0xc]
    uint32_t t60 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t61 = mem.r32(t60);
    ctx.ecx = static_cast<uint32_t>(t61);
    // 0x00416d15: push 0x76e9d4
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, 0x0076e9d4u);
    // 0x00416d1a: mov dword ptr [ebx + 0xc], ecx
    uint32_t t63 = static_cast<uint32_t>(ctx.ebx + 0x0000000cu);
    mem.w32(t63, ctx.ecx);
    // 0x00416d1d: call dword ptr [0x51b078]
    uint32_t t64 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t64);
    mem.w32(t64, 0x00416d23u);
    hle_iat_call(ctx, mem, 0x0051b078u);
    // 0x00416d23: mov edx, dword ptr [edi]
    uint32_t t65 = mem.r32(ctx.edi);
    ctx.edx = static_cast<uint32_t>(t65);
    // 0x00416d25: mov ecx, dword ptr [edi + 4]
    uint32_t t66 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    uint32_t t67 = mem.r32(t66);
    ctx.ecx = static_cast<uint32_t>(t67);
    // 0x00416d28: sub esp, 0x10
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000010u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000010u, t68);
    ctx.esp = static_cast<uint32_t>(t68);
    // 0x00416d2b: mov eax, esp
    ctx.eax = static_cast<uint32_t>(ctx.esp);
    // 0x00416d2d: push 0
    uint32_t t69 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t69);
    mem.w32(t69, 0x00000000u);
    // 0x00416d2f: mov dword ptr [eax], edx
    mem.w32(ctx.eax, ctx.edx);
    // 0x00416d31: mov edx, dword ptr [edi + 8]
    uint32_t t70 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    uint32_t t71 = mem.r32(t70);
    ctx.edx = static_cast<uint32_t>(t71);
    // 0x00416d34: mov dword ptr [eax + 4], ecx
    uint32_t t72 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w32(t72, ctx.ecx);
    // 0x00416d37: mov ecx, dword ptr [edi + 0xc]
    uint32_t t73 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    uint32_t t74 = mem.r32(t73);
    ctx.ecx = static_cast<uint32_t>(t74);
    // 0x00416d3a: push 0
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, 0x00000000u);
    // 0x00416d3c: lea ebp, [esi + 0x20]
    uint32_t t76 = static_cast<uint32_t>(ctx.esi + 0x00000020u);
    ctx.ebp = static_cast<uint32_t>(t76);
    // 0x00416d3f: push ebp
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, ctx.ebp);
    // 0x00416d40: mov dword ptr [eax + 8], edx
    uint32_t t78 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    mem.w32(t78, ctx.edx);
    // 0x00416d43: push ebx
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, ctx.ebx);
    // 0x00416d44: mov dword ptr [eax + 0xc], ecx
    uint32_t t80 = static_cast<uint32_t>(ctx.eax + 0x0000000cu);
    mem.w32(t80, ctx.ecx);
    // 0x00416d47: call 0x4f49a0
    uint32_t t81 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    mem.w32(t81, 0x00416d4cu);
    hle_crt_004f49a0(ctx, mem);
    // 0x00416d4c: add esp, 0x20
    uint32_t t82 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000020u, t82);
    ctx.esp = static_cast<uint32_t>(t82);
    // 0x00416d4f: test eax, eax
    uint32_t t83 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t83);
    // 0x00416d51: jge 0x416d60
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_00416d60;
    goto bb_00416d53;
}
bb_00416c9d: {
    // 0x00416c9d: sub edx, 1
    uint32_t t84 = static_cast<uint32_t>(ctx.edx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000001u, t84);
    ctx.edx = static_cast<uint32_t>(t84);
    // 0x00416ca0: add eax, 1
    uint32_t t85 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t85);
    ctx.eax = static_cast<uint32_t>(t85);
    // 0x00416ca3: add ecx, 1
    uint32_t t86 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t86);
    ctx.ecx = static_cast<uint32_t>(t86);
    // 0x00416ca6: test edx, edx
    uint32_t t87 = static_cast<uint32_t>(ctx.edx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t87);
    // 0x00416ca8: je 0x416cd9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00416cd9;
    goto bb_00416caa;
}
bb_00416d60: {
    // 0x00416d60: push -1
    uint32_t t88 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t88);
    mem.w32(t88, 0xffffffffu);
    // 0x00416d62: push ebp
    uint32_t t89 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t89);
    mem.w32(t89, ctx.ebp);
    // 0x00416d63: call 0x4f4290
    uint32_t t90 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    mem.w32(t90, 0x00416d68u);
    hle_crt_004f4290(ctx, mem);
    // 0x00416d68: add esp, 8
    uint32_t t91 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t91);
    ctx.esp = static_cast<uint32_t>(t91);
    // 0x00416d6b: push 0x76e9d4
    uint32_t t92 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    mem.w32(t92, 0x0076e9d4u);
    // 0x00416d70: mov dword ptr [esi + 0x18], eax
    uint32_t t93 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    mem.w32(t93, ctx.eax);
    // 0x00416d73: call dword ptr [0x51b070]
    uint32_t t94 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t94);
    mem.w32(t94, 0x00416d79u);
    hle_iat_call(ctx, mem, 0x0051b070u);
    // 0x00416d79: mov eax, dword ptr [esi + 0x18]
    uint32_t t95 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    uint32_t t96 = mem.r32(t95);
    ctx.eax = static_cast<uint32_t>(t96);
    // 0x00416d7c: test eax, eax
    uint32_t t97 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t97);
    // 0x00416d7e: jne 0x416da0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00416da0;
    goto bb_00416d80;
}
bb_00416d53: {
    // 0x00416d53: push 0x76e9d4
    uint32_t t98 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t98);
    mem.w32(t98, 0x0076e9d4u);
    // 0x00416d58: call dword ptr [0x51b070]
    uint32_t t99 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t99);
    mem.w32(t99, 0x00416d5eu);
    hle_iat_call(ctx, mem, 0x0051b070u);
    // 0x00416d5e: jmp 0x416d80
    goto bb_00416d80;
}
bb_00416caa: {
    // 0x00416caa: movzx edi, byte ptr [ecx]
    uint8_t t100 = mem.r8(ctx.ecx);
    uint32_t t101 = static_cast<uint32_t>(static_cast<uint8_t>(t100));
    ctx.edi = static_cast<uint32_t>(t101);
    // 0x00416cad: movzx ebx, byte ptr [eax]
    uint8_t t102 = mem.r8(ctx.eax);
    uint32_t t103 = static_cast<uint32_t>(static_cast<uint8_t>(t102));
    ctx.ebx = static_cast<uint32_t>(t103);
    // 0x00416cb0: sub edi, ebx
    uint32_t t104 = static_cast<uint32_t>(ctx.edi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebx, t104);
    ctx.edi = static_cast<uint32_t>(t104);
    // 0x00416cb2: jne 0x416ccb
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00416ccb;
    goto bb_00416cb4;
}
bb_00416da0: {
    // 0x00416da0: mov edi, dword ptr [eax + 4]
    uint32_t t105 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t106 = mem.r32(t105);
    ctx.edi = static_cast<uint32_t>(t106);
    // 0x00416da3: mov ebx, dword ptr [eax + 8]
    uint32_t t107 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    uint32_t t108 = mem.r32(t107);
    ctx.ebx = static_cast<uint32_t>(t108);
    // 0x00416da6: push -1
    uint32_t t109 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t109);
    mem.w32(t109, 0xffffffffu);
    // 0x00416da8: push ebp
    uint32_t t110 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t110);
    mem.w32(t110, ctx.ebp);
    // 0x00416da9: call 0x4f32f0
    uint32_t t111 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t111);
    mem.w32(t111, 0x00416daeu);
    hle_crt_004f32f0(ctx, mem);
    // 0x00416dae: imul edi, ebx
    uint64_t t112 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.edi)) * static_cast<int64_t>(static_cast<int32_t>(ctx.ebx)));
    uint32_t t113 = static_cast<uint32_t>(t112);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t112);
    ctx.edi = static_cast<uint32_t>(t113);
    // 0x00416db1: mov dword ptr [esp + 0x1c], edi
    uint32_t t114 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t114, ctx.edi);
    // 0x00416db5: add esp, 8
    uint32_t t115 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t115);
    ctx.esp = static_cast<uint32_t>(t115);
    // 0x00416db8: fild dword ptr [esp + 0x14]
    uint32_t t116 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    double t117 = static_cast<double>(static_cast<int32_t>(mem.r32(t116)));
    ctx.fpu_push(t117);
    // 0x00416dbc: fmulp st(1)
    double t118 = ctx.fpu_st(1);
    double t119 = ctx.fpu_st(0);
    double t120 = (t118 * t119);
    ctx.fpu_st(1) = t120;
    ctx.fpu_pop();
    // 0x00416dbe: fadd st(0), st(0)
    double t121 = ctx.fpu_st(0);
    double t122 = ctx.fpu_st(0);
    double t123 = (t121 + t122);
    ctx.fpu_st(0) = t123;
    // 0x00416dc0: call 0x4f49f0
    uint32_t t124 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t124);
    mem.w32(t124, 0x00416dc5u);
    hle_crt_004f49f0(ctx, mem);
    // 0x00416dc5: mov dword ptr [esi + 0x320], eax
    uint32_t t125 = static_cast<uint32_t>(ctx.esi + 0x00000320u);
    mem.w32(t125, ctx.eax);
    // 0x00416dcb: lea eax, [esi + 0x2f0]
    uint32_t t126 = static_cast<uint32_t>(ctx.esi + 0x000002f0u);
    ctx.eax = static_cast<uint32_t>(t126);
    // 0x00416dd1: mov edx, esi
    ctx.edx = static_cast<uint32_t>(ctx.esi);
    // 0x00416dd3: call 0x416bb0
    uint32_t t127 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t127);
    mem.w32(t127, 0x00416dd8u);
    sub_00416bb0(ctx, mem);
    // 0x00416dd8: pop edi
    uint32_t t128 = ctx.esp;
    uint32_t t129 = mem.r32(t128);
    uint32_t t130 = static_cast<uint32_t>(t128 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t130);
    ctx.edi = static_cast<uint32_t>(t129);
    // 0x00416dd9: pop esi
    uint32_t t131 = ctx.esp;
    uint32_t t132 = mem.r32(t131);
    uint32_t t133 = static_cast<uint32_t>(t131 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t133);
    ctx.esi = static_cast<uint32_t>(t132);
    // 0x00416dda: pop ebp
    uint32_t t134 = ctx.esp;
    uint32_t t135 = mem.r32(t134);
    uint32_t t136 = static_cast<uint32_t>(t134 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t136);
    ctx.ebp = static_cast<uint32_t>(t135);
    // 0x00416ddb: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x00416de0: pop ebx
    uint32_t t137 = ctx.esp;
    uint32_t t138 = mem.r32(t137);
    uint32_t t139 = static_cast<uint32_t>(t137 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t139);
    ctx.ebx = static_cast<uint32_t>(t138);
    // 0x00416de1: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_00416d80: {
    // 0x00416d80: mov edx, dword ptr [esi + 4]
    uint32_t t140 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t141 = mem.r32(t140);
    ctx.edx = static_cast<uint32_t>(t141);
    // 0x00416d83: push edx
    uint32_t t142 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t142);
    mem.w32(t142, ctx.edx);
    // 0x00416d84: call dword ptr [0x51b1cc]
    uint32_t t143 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t143);
    mem.w32(t143, 0x00416d8au);
    hle_iat_call(ctx, mem, 0x0051b1ccu);
    // 0x00416d8a: mov dword ptr [esi + 4], 0
    uint32_t t144 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t144, 0x00000000u);
    // 0x00416d91: mov dword ptr [esi], 0xffffffff
    mem.w32(ctx.esi, 0xffffffffu);
    goto bb_00416d97;
}
bb_00416cb4: {
    // 0x00416cb4: sub edx, 1
    uint32_t t145 = static_cast<uint32_t>(ctx.edx - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edx, 0x00000001u, t145);
    ctx.edx = static_cast<uint32_t>(t145);
    // 0x00416cb7: add eax, 1
    uint32_t t146 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t146);
    ctx.eax = static_cast<uint32_t>(t146);
    // 0x00416cba: add ecx, 1
    uint32_t t147 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t147);
    ctx.ecx = static_cast<uint32_t>(t147);
    // 0x00416cbd: test edx, edx
    uint32_t t148 = static_cast<uint32_t>(ctx.edx & ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t148);
    // 0x00416cbf: je 0x416cd9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00416cd9;
}
{
    // 0x00416cc1: movzx edi, byte ptr [ecx]
    uint8_t t149 = mem.r8(ctx.ecx);
    uint32_t t150 = static_cast<uint32_t>(static_cast<uint8_t>(t149));
    ctx.edi = static_cast<uint32_t>(t150);
    // 0x00416cc4: movzx eax, byte ptr [eax]
    uint8_t t151 = mem.r8(ctx.eax);
    uint32_t t152 = static_cast<uint32_t>(static_cast<uint8_t>(t151));
    ctx.eax = static_cast<uint32_t>(t152);
    // 0x00416cc7: sub edi, eax
    uint32_t t153 = static_cast<uint32_t>(ctx.edi - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.eax, t153);
    ctx.edi = static_cast<uint32_t>(t153);
    // 0x00416cc9: je 0x416cd9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00416cd9;
    goto bb_00416ccb;
}
}

// sub_00416df0 | subsystem=Sound | canonical | 3 blocks | 24 insns
void sub_00416df0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00416df0: push ecx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ecx);
    // 0x00416df1: mov eax, dword ptr [ecx + 0x18]
    uint32_t t1 = static_cast<uint32_t>(ctx.ecx + 0x00000018u);
    uint32_t t2 = mem.r32(t1);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x00416df4: test eax, eax
    uint32_t t3 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t3);
    // 0x00416df6: jne 0x416dfa
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00416dfa;
    goto bb_00416df8;
}
bb_00416dfa: {
    // 0x00416dfa: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x00416dfb: mov esi, dword ptr [eax + 8]
    uint32_t t5 = static_cast<uint32_t>(ctx.eax + 0x00000008u);
    uint32_t t6 = mem.r32(t5);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x00416dfe: push edi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.edi);
    // 0x00416dff: mov edi, dword ptr [eax + 4]
    uint32_t t8 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    uint32_t t9 = mem.r32(t8);
    ctx.edi = static_cast<uint32_t>(t9);
    // 0x00416e02: add ecx, 0x20
    uint32_t t10 = static_cast<uint32_t>(ctx.ecx + 0x00000020u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000020u, t10);
    ctx.ecx = static_cast<uint32_t>(t10);
    // 0x00416e05: push -1
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, 0xffffffffu);
    // 0x00416e07: push ecx
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.ecx);
    // 0x00416e08: call 0x4f32f0
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x00416e0du);
    hle_crt_004f32f0(ctx, mem);
    // 0x00416e0d: add esp, 8
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t14);
    ctx.esp = static_cast<uint32_t>(t14);
    // 0x00416e10: imul esi, edi
    uint64_t t15 = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(ctx.esi)) * static_cast<int64_t>(static_cast<int32_t>(ctx.edi)));
    uint32_t t16 = static_cast<uint32_t>(t15);
    recomp_detail::update_flags_imul<uint32_t>(ctx, t15);
    ctx.esi = static_cast<uint32_t>(t16);
    // 0x00416e13: mov dword ptr [esp + 8], esi
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    mem.w32(t17, ctx.esi);
    // 0x00416e17: pop edi
    uint32_t t18 = ctx.esp;
    uint32_t t19 = mem.r32(t18);
    uint32_t t20 = static_cast<uint32_t>(t18 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    ctx.edi = static_cast<uint32_t>(t19);
    // 0x00416e18: pop esi
    uint32_t t21 = ctx.esp;
    uint32_t t22 = mem.r32(t21);
    uint32_t t23 = static_cast<uint32_t>(t21 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    ctx.esi = static_cast<uint32_t>(t22);
    // 0x00416e19: fild dword ptr [esp]
    double t24 = static_cast<double>(static_cast<int32_t>(mem.r32(ctx.esp)));
    ctx.fpu_push(t24);
    // 0x00416e1c: fmulp st(1)
    double t25 = ctx.fpu_st(1);
    double t26 = ctx.fpu_st(0);
    double t27 = (t25 * t26);
    ctx.fpu_st(1) = t27;
    ctx.fpu_pop();
    // 0x00416e1e: fadd st(0), st(0)
    double t28 = ctx.fpu_st(0);
    double t29 = ctx.fpu_st(0);
    double t30 = (t28 + t29);
    ctx.fpu_st(0) = t30;
    // 0x00416e20: add esp, 4
    uint32_t t31 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t31);
    ctx.esp = static_cast<uint32_t>(t31);
    // 0x00416e23: jmp 0x4f49f0
    hle_crt_004f49f0(ctx, mem);
    return;
}
bb_00416df8: {
    // 0x00416df8: pop ecx
    uint32_t t32 = ctx.esp;
    uint32_t t33 = mem.r32(t32);
    uint32_t t34 = static_cast<uint32_t>(t32 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    ctx.ecx = static_cast<uint32_t>(t33);
    // 0x00416df9: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_00416e30 | subsystem=Sound | canonical | 5 blocks | 34 insns
void sub_00416e30(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00416e30: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x00416e31: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x00416e33: and esp, 0xfffffff8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xfffffff8u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x00416e36: push ecx
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.ecx);
    // 0x00416e37: push edi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.edi);
    // 0x00416e38: push 0x76e9d4
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x0076e9d4u);
    // 0x00416e3d: call dword ptr [0x51b078]
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, 0x00416e43u);
    hle_iat_call(ctx, mem, 0x0051b078u);
    // 0x00416e43: cmp dword ptr [esi], -1
    uint32_t t6 = mem.r32(ctx.esi);
    uint32_t t7 = static_cast<uint32_t>(t6 - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t6, 0xffffffffu, t7);
    // 0x00416e46: je 0x416e54
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00416e54;
    goto bb_00416e48;
}
bb_00416e54: {
    // 0x00416e54: mov eax, dword ptr [esi + 0x31c]
    uint32_t t8 = static_cast<uint32_t>(ctx.esi + 0x0000031cu);
    uint32_t t9 = mem.r32(t8);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x00416e5a: xor edi, edi
    uint32_t t10 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.edi = static_cast<uint32_t>(t10);
    // 0x00416e5c: cmp eax, edi
    uint32_t t11 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t11);
    // 0x00416e5e: je 0x416e6c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00416e6c;
    goto bb_00416e60;
}
bb_00416e48: {
    // 0x00416e48: lea eax, [esi + 0x20]
    uint32_t t12 = static_cast<uint32_t>(ctx.esi + 0x00000020u);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x00416e4b: push eax
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, ctx.eax);
    // 0x00416e4c: call 0x4f3170
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, 0x00416e51u);
    hle_crt_004f3170(ctx, mem);
    // 0x00416e51: add esp, 4
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t15);
    ctx.esp = static_cast<uint32_t>(t15);
    goto bb_00416e54;
}
bb_00416e6c: {
    // 0x00416e6c: fldz
    ctx.fpu_push(0.0);
    // 0x00416e6e: push 0x76e9d4
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x0076e9d4u);
    // 0x00416e73: fstp qword ptr [esi + 0x308]
    double t17 = ctx.fpu_st(0);
    uint32_t t18 = static_cast<uint32_t>(ctx.esi + 0x00000308u);
    mem.wf64(t18, t17);
    ctx.fpu_pop();
    // 0x00416e79: mov dword ptr [esi + 4], edi
    uint32_t t19 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    mem.w32(t19, ctx.edi);
    // 0x00416e7c: mov dword ptr [esi + 0x18], edi
    uint32_t t20 = static_cast<uint32_t>(ctx.esi + 0x00000018u);
    mem.w32(t20, ctx.edi);
    // 0x00416e7f: mov dword ptr [esi + 0x324], edi
    uint32_t t21 = static_cast<uint32_t>(ctx.esi + 0x00000324u);
    mem.w32(t21, ctx.edi);
    // 0x00416e85: mov dword ptr [esi + 0x320], edi
    uint32_t t22 = static_cast<uint32_t>(ctx.esi + 0x00000320u);
    mem.w32(t22, ctx.edi);
    // 0x00416e8b: call dword ptr [0x51b070]
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x00416e91u);
    hle_iat_call(ctx, mem, 0x0051b070u);
    // 0x00416e91: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x00416e96: pop edi
    uint32_t t24 = ctx.esp;
    uint32_t t25 = mem.r32(t24);
    uint32_t t26 = static_cast<uint32_t>(t24 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t26);
    ctx.edi = static_cast<uint32_t>(t25);
    // 0x00416e97: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x00416e99: pop ebp
    uint32_t t27 = ctx.esp;
    uint32_t t28 = mem.r32(t27);
    uint32_t t29 = static_cast<uint32_t>(t27 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    ctx.ebp = static_cast<uint32_t>(t28);
    // 0x00416e9a: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_00416e60: {
    // 0x00416e60: mov ecx, dword ptr [esi + 0x310]
    uint32_t t30 = static_cast<uint32_t>(ctx.esi + 0x00000310u);
    uint32_t t31 = mem.r32(t30);
    ctx.ecx = static_cast<uint32_t>(t31);
    // 0x00416e66: push ecx
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, ctx.ecx);
    // 0x00416e67: call eax
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x00416e69u);
    call_indirect(ctx, mem, ctx.eax);
    // 0x00416e69: add esp, 4
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t34);
    ctx.esp = static_cast<uint32_t>(t34);
    goto bb_00416e6c;
}
}

// sub_00416ea0 | subsystem=Sound | canonical | 12 blocks | 81 insns
void sub_00416ea0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x00416ea0: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x00416ea1: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x00416ea3: and esp, 0xffffffc0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xffffffc0u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x00416ea6: sub esp, 0x34
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000034u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000034u, t2);
    ctx.esp = static_cast<uint32_t>(t2);
    // 0x00416ea9: push ebx
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.ebx);
    // 0x00416eaa: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x00416eab: mov ebx, eax
    ctx.ebx = static_cast<uint32_t>(ctx.eax);
    // 0x00416ead: mov eax, dword ptr [ebp + 8]
    uint32_t t5 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t6 = mem.r32(t5);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x00416eb0: push edi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.edi);
    // 0x00416eb1: xor edi, edi
    uint32_t t8 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t8);
    ctx.edi = static_cast<uint32_t>(t8);
    // 0x00416eb3: cmp dword ptr [eax], -1
    uint32_t t9 = mem.r32(ctx.eax);
    uint32_t t10 = static_cast<uint32_t>(t9 - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t9, 0xffffffffu, t10);
    // 0x00416eb6: mov dword ptr [esp + 0x38], ebx
    uint32_t t11 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    mem.w32(t11, ctx.ebx);
    // 0x00416eba: jne 0x416ec7
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00416ec7;
    goto bb_00416ebc;
}
bb_00416ec7: {
    // 0x00416ec7: push 0x76e9d4
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, 0x0076e9d4u);
    // 0x00416ecc: call dword ptr [0x51b078]
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x00416ed2u);
    hle_iat_call(ctx, mem, 0x0051b078u);
    // 0x00416ed2: test ebx, ebx
    uint32_t t14 = static_cast<uint32_t>(ctx.ebx & ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    // 0x00416ed4: je 0x416f4f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00416f4f;
    goto bb_00416ed6;
}
bb_00416ebc: {
    // 0x00416ebc: xor eax, eax
    uint32_t t15 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t15);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x00416ebe: pop edi
    uint32_t t16 = ctx.esp;
    uint32_t t17 = mem.r32(t16);
    uint32_t t18 = static_cast<uint32_t>(t16 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    ctx.edi = static_cast<uint32_t>(t17);
    // 0x00416ebf: pop esi
    uint32_t t19 = ctx.esp;
    uint32_t t20 = mem.r32(t19);
    uint32_t t21 = static_cast<uint32_t>(t19 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    ctx.esi = static_cast<uint32_t>(t20);
    // 0x00416ec0: pop ebx
    uint32_t t22 = ctx.esp;
    uint32_t t23 = mem.r32(t22);
    uint32_t t24 = static_cast<uint32_t>(t22 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    ctx.ebx = static_cast<uint32_t>(t23);
    // 0x00416ec1: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x00416ec3: pop ebp
    uint32_t t25 = ctx.esp;
    uint32_t t26 = mem.r32(t25);
    uint32_t t27 = static_cast<uint32_t>(t25 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    ctx.ebp = static_cast<uint32_t>(t26);
    // 0x00416ec4: ret 0xc
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 12u;
    return;
}
bb_00416f4f: {
    // 0x00416f4f: push 0x76e9d4
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x0076e9d4u);
    // 0x00416f54: call dword ptr [0x51b070]
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x00416f5au);
    hle_iat_call(ctx, mem, 0x0051b070u);
    // 0x00416f5a: mov eax, dword ptr [ebp + 8]
    uint32_t t30 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t31 = mem.r32(t30);
    ctx.eax = static_cast<uint32_t>(t31);
    // 0x00416f5d: add dword ptr [eax + 0x324], edi
    uint32_t t32 = static_cast<uint32_t>(ctx.eax + 0x00000324u);
    uint32_t t33 = mem.r32(t32);
    uint32_t t34 = static_cast<uint32_t>(t33 + ctx.edi);
    recomp_detail::update_flags_add<uint32_t>(ctx, t33, ctx.edi, t34);
    mem.w32(t32, t34);
    // 0x00416f63: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x00416f65: pop edi
    uint32_t t35 = ctx.esp;
    uint32_t t36 = mem.r32(t35);
    uint32_t t37 = static_cast<uint32_t>(t35 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    ctx.edi = static_cast<uint32_t>(t36);
    // 0x00416f66: pop esi
    uint32_t t38 = ctx.esp;
    uint32_t t39 = mem.r32(t38);
    uint32_t t40 = static_cast<uint32_t>(t38 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    ctx.esi = static_cast<uint32_t>(t39);
    // 0x00416f67: pop ebx
    uint32_t t41 = ctx.esp;
    uint32_t t42 = mem.r32(t41);
    uint32_t t43 = static_cast<uint32_t>(t41 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    ctx.ebx = static_cast<uint32_t>(t42);
    // 0x00416f68: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x00416f6a: pop ebp
    uint32_t t44 = ctx.esp;
    uint32_t t45 = mem.r32(t44);
    uint32_t t46 = static_cast<uint32_t>(t44 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    ctx.ebp = static_cast<uint32_t>(t45);
    // 0x00416f6b: ret 0xc
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 12u;
    return;
}
bb_00416ed6: {
    // 0x00416ed6: mov edx, dword ptr [ebp + 0xc]
    uint32_t t47 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t48 = mem.r32(t47);
    ctx.edx = static_cast<uint32_t>(t48);
    // 0x00416ed9: lea ecx, [esp + 0x3c]
    uint32_t t49 = static_cast<uint32_t>(ctx.esp + 0x0000003cu);
    ctx.ecx = static_cast<uint32_t>(t49);
    // 0x00416edd: push ecx
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, ctx.ecx);
    // 0x00416ede: push 1
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, 0x00000001u);
    // 0x00416ee0: push 2
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, 0x00000002u);
    // 0x00416ee2: push 0
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, 0x00000000u);
    // 0x00416ee4: lea eax, [edi + edx]
    uint32_t t54 = static_cast<uint32_t>(ctx.edi + ctx.edx);
    ctx.eax = static_cast<uint32_t>(t54);
    // 0x00416ee7: push ebx
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, ctx.ebx);
    // 0x00416ee8: push eax
    uint32_t t56 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    mem.w32(t56, ctx.eax);
    // 0x00416ee9: mov eax, dword ptr [ebp + 8]
    uint32_t t57 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t58 = mem.r32(t57);
    ctx.eax = static_cast<uint32_t>(t58);
    // 0x00416eec: add eax, 0x20
    uint32_t t59 = static_cast<uint32_t>(ctx.eax + 0x00000020u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000020u, t59);
    ctx.eax = static_cast<uint32_t>(t59);
    // 0x00416eef: push eax
    uint32_t t60 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t60);
    mem.w32(t60, ctx.eax);
    // 0x00416ef0: call 0x4f4620
    uint32_t t61 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    mem.w32(t61, 0x00416ef5u);
    hle_crt_004f4620(ctx, mem);
    // 0x00416ef5: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x00416ef7: add esp, 0x1c
    uint32_t t62 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000001cu, t62);
    ctx.esp = static_cast<uint32_t>(t62);
    // 0x00416efa: test esi, esi
    uint32_t t63 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t63);
    // 0x00416efc: jne 0x416f20
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00416f20;
    goto bb_00416efe;
}
bb_00416f20: {
    // 0x00416f20: cmp esi, -3
    uint32_t t64 = static_cast<uint32_t>(ctx.esi - 0xfffffffdu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0xfffffffdu, t64);
    // 0x00416f23: je 0x416f33
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00416f33;
    goto bb_00416f25;
}
bb_00416efe: {
    // 0x00416efe: cmp dword ptr [ebp + 0x10], eax
    uint32_t t65 = static_cast<uint32_t>(ctx.ebp + 0x00000010u);
    uint32_t t66 = mem.r32(t65);
    uint32_t t67 = static_cast<uint32_t>(t66 - ctx.eax);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t66, ctx.eax, t67);
    // 0x00416f01: je 0x416f33
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00416f33;
    goto bb_00416f03;
}
bb_00416f33: {
    // 0x00416f33: mov eax, dword ptr [esp + 0x38]
    uint32_t t68 = static_cast<uint32_t>(ctx.esp + 0x00000038u);
    uint32_t t69 = mem.r32(t68);
    ctx.eax = static_cast<uint32_t>(t69);
    // 0x00416f37: cmp eax, edi
    uint32_t t70 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t70);
    // 0x00416f39: je 0x416f4f
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00416f4f;
    goto bb_00416f3b;
}
bb_00416f25: {
    // 0x00416f25: cmp esi, 0xffffff77
    uint32_t t71 = static_cast<uint32_t>(ctx.esi - 0xffffff77u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0xffffff77u, t71);
    // 0x00416f2b: je 0x416f33
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_00416f33;
    goto bb_00416f2d;
}
bb_00416f03: {
    // 0x00416f03: mov eax, dword ptr [ebp + 8]
    uint32_t t72 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t73 = mem.r32(t72);
    ctx.eax = static_cast<uint32_t>(t73);
    // 0x00416f06: fld qword ptr [eax + 0x308]
    uint32_t t74 = static_cast<uint32_t>(ctx.eax + 0x00000308u);
    double t75 = mem.rf64(t74);
    ctx.fpu_push(t75);
    // 0x00416f0c: sub esp, 8
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000008u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000008u, t76);
    ctx.esp = static_cast<uint32_t>(t76);
    // 0x00416f0f: add eax, 0x20
    uint32_t t77 = static_cast<uint32_t>(ctx.eax + 0x00000020u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000020u, t77);
    ctx.eax = static_cast<uint32_t>(t77);
    // 0x00416f12: fstp qword ptr [esp]
    double t78 = ctx.fpu_st(0);
    mem.wf64(ctx.esp, t78);
    ctx.fpu_pop();
    // 0x00416f15: push eax
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, ctx.eax);
    // 0x00416f16: call 0x4f41a0
    uint32_t t80 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    mem.w32(t80, 0x00416f1bu);
    hle_crt_004f41a0(ctx, mem);
    // 0x00416f1b: add esp, 0xc
    uint32_t t81 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t81);
    ctx.esp = static_cast<uint32_t>(t81);
    // 0x00416f1e: jmp 0x416f2d
    goto bb_00416f2d;
}
bb_00416f3b: {
    // 0x00416f3b: mov ecx, dword ptr [ebp + 0xc]
    uint32_t t82 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t83 = mem.r32(t82);
    ctx.ecx = static_cast<uint32_t>(t83);
    // 0x00416f3e: sub eax, edi
    uint32_t t84 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t84);
    ctx.eax = static_cast<uint32_t>(t84);
    // 0x00416f40: push eax
    uint32_t t85 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t85);
    mem.w32(t85, ctx.eax);
    // 0x00416f41: lea edx, [edi + ecx]
    uint32_t t86 = static_cast<uint32_t>(ctx.edi + ctx.ecx);
    ctx.edx = static_cast<uint32_t>(t86);
    // 0x00416f44: push 0
    uint32_t t87 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t87);
    mem.w32(t87, 0x00000000u);
    // 0x00416f46: push edx
    uint32_t t88 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t88);
    mem.w32(t88, ctx.edx);
    // 0x00416f47: call 0x4e6340
    uint32_t t89 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t89);
    mem.w32(t89, 0x00416f4cu);
    hle_crt_004e6340(ctx, mem);
    // 0x00416f4c: add esp, 0xc
    uint32_t t90 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t90);
    ctx.esp = static_cast<uint32_t>(t90);
    goto bb_00416f4f;
}
bb_00416f2d: {
    // 0x00416f2d: add edi, esi
    uint32_t t91 = static_cast<uint32_t>(ctx.edi + ctx.esi);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, ctx.esi, t91);
    ctx.edi = static_cast<uint32_t>(t91);
    // 0x00416f2f: sub ebx, esi
    uint32_t t92 = static_cast<uint32_t>(ctx.ebx - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, ctx.esi, t92);
    ctx.ebx = static_cast<uint32_t>(t92);
    // 0x00416f31: jne 0x416ed6
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_00416ed6;
    goto bb_00416f33;
}
}

// sub_004a0540 | subsystem=Sound | canonical | 27 blocks | 141 insns
void sub_004a0540(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a0540: push ebx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebx);
    // 0x004a0541: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
    // 0x004a0542: push edi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.edi);
    // 0x004a0543: lea eax, [esp + 0x11c]
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x0000011cu);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004a054a: push 0x53a5dc
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, 0x0053a5dcu);
    // 0x004a054f: push eax
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.eax);
    // 0x004a0550: call 0x4e068b
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, 0x004a0555u);
    hle_crt_004e068b(ctx, mem);
    // 0x004a0555: lea ecx, [esp + 0x24]
    uint32_t t7 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    ctx.ecx = static_cast<uint32_t>(t7);
    // 0x004a0559: push 0x53a5e8
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x0053a5e8u);
    // 0x004a055e: push ecx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ecx);
    // 0x004a055f: call 0x4e068b
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x004a0564u);
    hle_crt_004e068b(ctx, mem);
    // 0x004a0564: add esp, 0x10
    uint32_t t11 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t11);
    ctx.esp = static_cast<uint32_t>(t11);
    // 0x004a0567: cmp dword ptr [ebp], 0
    uint32_t t12 = mem.r32(ctx.ebp);
    uint32_t t13 = static_cast<uint32_t>(t12 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t12, 0x00000000u, t13);
    // 0x004a056b: je 0x4a0571
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a0571;
    goto bb_004a056d;
}
bb_004a0571: {
    // 0x004a0571: lea eax, [esp + 0x1c]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x004a0575: lea ebx, [esp + 0x11c]
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x0000011cu);
    ctx.ebx = static_cast<uint32_t>(t15);
    // 0x004a057c: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x004a057e: call 0x40c670
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x004a0583u);
    sub_0040c670(ctx, mem);
    // 0x004a0583: test eax, eax
    uint32_t t17 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t17);
    // 0x004a0585: je 0x4a0590
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a0590;
    goto bb_004a0587;
}
bb_004a056d: {
    // 0x004a056d: xor eax, eax
    uint32_t t18 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    ctx.eax = static_cast<uint32_t>(t18);
    // 0x004a056f: jmp 0x4a0590
}
bb_004a0590: {
    // 0x004a0590: mov dword ptr [0x76e768], eax
    mem.w32(0x0076e768u, ctx.eax);
    // 0x004a0595: xor esi, esi
    uint32_t t19 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t19);
    ctx.esi = static_cast<uint32_t>(t19);
    // 0x004a0597: mov eax, 4
    ctx.eax = static_cast<uint32_t>(0x00000004u);
    // 0x004a059c: lea edx, [esp + 0x21c]
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x0000021cu);
    ctx.edx = static_cast<uint32_t>(t20);
    // 0x004a05a3: sub eax, edx
    uint32_t t21 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t21);
    ctx.eax = static_cast<uint32_t>(t21);
    // 0x004a05a5: mov dword ptr [esp + 0x14], esi
    uint32_t t22 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t22, ctx.esi);
    // 0x004a05a9: mov dword ptr [esp + 0x18], eax
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t23, ctx.eax);
    // 0x004a05ad: jmp 0x4a05b4
    goto bb_004a05b4;
}
bb_004a0587: {
    // 0x004a0587: push eax
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, ctx.eax);
    // 0x004a0588: call 0x4e0eb7
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x004a058du);
    hle_crt_004e0eb7(ctx, mem);
    // 0x004a058d: add esp, 4
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t26);
    ctx.esp = static_cast<uint32_t>(t26);
    goto bb_004a0590;
}
bb_004a05b4: {
    // 0x004a05b4: push esi
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, ctx.esi);
    // 0x004a05b5: lea eax, [esp + 0x20]
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    ctx.eax = static_cast<uint32_t>(t28);
    // 0x004a05b9: push 0x53a5f4
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x0053a5f4u);
    // 0x004a05be: push eax
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, ctx.eax);
    // 0x004a05bf: call 0x4e068b
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x004a05c4u);
    hle_crt_004e068b(ctx, mem);
    // 0x004a05c4: add esp, 0xc
    uint32_t t32 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t32);
    ctx.esp = static_cast<uint32_t>(t32);
    // 0x004a05c7: cmp dword ptr [ebp], 0
    uint32_t t33 = mem.r32(ctx.ebp);
    uint32_t t34 = static_cast<uint32_t>(t33 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t33, 0x00000000u, t34);
    // 0x004a05cb: je 0x4a05d2
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a05d2;
    goto bb_004a05cd;
}
bb_004a05d2: {
    // 0x004a05d2: lea eax, [esp + 0x1c]
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.eax = static_cast<uint32_t>(t35);
    // 0x004a05d6: lea ebx, [esp + 0x11c]
    uint32_t t36 = static_cast<uint32_t>(ctx.esp + 0x0000011cu);
    ctx.ebx = static_cast<uint32_t>(t36);
    // 0x004a05dd: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x004a05df: call 0x40c670
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, 0x004a05e4u);
    sub_0040c670(ctx, mem);
    // 0x004a05e4: test eax, eax
    uint32_t t38 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t38);
    // 0x004a05e6: jne 0x4a05ed
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a05ed;
    goto bb_004a05e8;
}
bb_004a05cd: {
    // 0x004a05cd: or eax, 0xffffffff
    uint32_t t39 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t39);
    ctx.eax = static_cast<uint32_t>(t39);
    // 0x004a05d0: jmp 0x4a05f6
    goto bb_004a05f6;
}
bb_004a05ed: {
    // 0x004a05ed: push eax
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, ctx.eax);
    // 0x004a05ee: call 0x4e0eb7
    uint32_t t41 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    mem.w32(t41, 0x004a05f3u);
    hle_crt_004e0eb7(ctx, mem);
    // 0x004a05f3: add esp, 4
    uint32_t t42 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t42);
    ctx.esp = static_cast<uint32_t>(t42);
    goto bb_004a05f6;
}
bb_004a05e8: {
    // 0x004a05e8: or eax, 0xffffffff
    uint32_t t43 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t43);
    ctx.eax = static_cast<uint32_t>(t43);
    // 0x004a05eb: jmp 0x4a05f6
}
bb_004a05f6: {
    // 0x004a05f6: mov ecx, dword ptr [esp + 0x10]
    uint32_t t44 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t45 = mem.r32(t44);
    ctx.ecx = static_cast<uint32_t>(t45);
    // 0x004a05fa: push esi
    uint32_t t46 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    mem.w32(t46, ctx.esi);
    // 0x004a05fb: lea edx, [esp + 0x20]
    uint32_t t47 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    ctx.edx = static_cast<uint32_t>(t47);
    // 0x004a05ff: push 0x53a600
    uint32_t t48 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t48);
    mem.w32(t48, 0x0053a600u);
    // 0x004a0604: push edx
    uint32_t t49 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    mem.w32(t49, ctx.edx);
    // 0x004a0605: mov dword ptr [ecx], eax
    mem.w32(ctx.ecx, ctx.eax);
    // 0x004a0607: call 0x4e068b
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, 0x004a060cu);
    hle_crt_004e068b(ctx, mem);
    // 0x004a060c: add esp, 0xc
    uint32_t t51 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t51);
    ctx.esp = static_cast<uint32_t>(t51);
    // 0x004a060f: cmp dword ptr [ebp], 0
    uint32_t t52 = mem.r32(ctx.ebp);
    uint32_t t53 = static_cast<uint32_t>(t52 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t52, 0x00000000u, t53);
    // 0x004a0613: jne 0x4a065b
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a065b;
    goto bb_004a0615;
}
bb_004a065b: {
    // 0x004a065b: mov ecx, dword ptr [esp + 0x18]
    uint32_t t54 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    uint32_t t55 = mem.r32(t54);
    ctx.ecx = static_cast<uint32_t>(t55);
    // 0x004a065f: mov edx, dword ptr [esp + 0x10]
    uint32_t t56 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t57 = mem.r32(t56);
    ctx.edx = static_cast<uint32_t>(t57);
    // 0x004a0663: lea eax, [esp + 0x21c]
    uint32_t t58 = static_cast<uint32_t>(ctx.esp + 0x0000021cu);
    ctx.eax = static_cast<uint32_t>(t58);
    // 0x004a066a: add edx, ecx
    uint32_t t59 = static_cast<uint32_t>(ctx.edx + ctx.ecx);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, ctx.ecx, t59);
    ctx.edx = static_cast<uint32_t>(t59);
    // 0x004a066c: lea esp, [esp]
    ctx.esp = static_cast<uint32_t>(ctx.esp);
    goto bb_004a0670;
}
bb_004a0615: {
    // 0x004a0615: lea eax, [esp + 0x1c]
    uint32_t t60 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.eax = static_cast<uint32_t>(t60);
    // 0x004a0619: lea ebx, [esp + 0x11c]
    uint32_t t61 = static_cast<uint32_t>(ctx.esp + 0x0000011cu);
    ctx.ebx = static_cast<uint32_t>(t61);
    // 0x004a0620: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x004a0622: call 0x40c670
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, 0x004a0627u);
    sub_0040c670(ctx, mem);
    // 0x004a0627: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x004a0629: test edi, edi
    uint32_t t63 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t63);
    // 0x004a062b: je 0x4a065b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a065b;
    goto bb_004a062d;
}
bb_004a0670: {
    // 0x004a0670: mov cl, byte ptr [eax]
    uint8_t t64 = mem.r8(ctx.eax);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t64));
    // 0x004a0672: mov byte ptr [edx + eax], cl
    uint32_t t65 = static_cast<uint32_t>(ctx.edx + ctx.eax);
    mem.w8(t65, recomp_detail::r8l(ctx.ecx));
    // 0x004a0675: add eax, 1
    uint32_t t66 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t66);
    ctx.eax = static_cast<uint32_t>(t66);
    // 0x004a0678: test cl, cl
    uint8_t t67 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t67);
    // 0x004a067a: jne 0x4a0670
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a0670;
    goto bb_004a067c;
}
bb_004a062d: {
    // 0x004a062d: call 0x40cb40
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, 0x004a0632u);
    sub_0040cb40(ctx, mem);
    // 0x004a0632: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004a0634: cmp esi, 0x100
    uint32_t t69 = static_cast<uint32_t>(ctx.esi - 0x00000100u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00000100u, t69);
    // 0x004a063a: jle 0x4a0641
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_004a0641;
    goto bb_004a063c;
}
bb_004a067c: {
    // 0x004a067c: mov edi, dword ptr [esp + 0x10]
    uint32_t t70 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t71 = mem.r32(t70);
    ctx.edi = static_cast<uint32_t>(t71);
    // 0x004a0680: xor esi, esi
    uint32_t t72 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t72);
    ctx.esi = static_cast<uint32_t>(t72);
    // 0x004a0682: add edi, 0x104
    uint32_t t73 = static_cast<uint32_t>(ctx.edi + 0x00000104u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000104u, t73);
    ctx.edi = static_cast<uint32_t>(t73);
    goto bb_004a0688;
}
bb_004a0641: {
    // 0x004a0641: push esi
    uint32_t t74 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    mem.w32(t74, ctx.esi);
    // 0x004a0642: lea eax, [esp + 0x220]
    uint32_t t75 = static_cast<uint32_t>(ctx.esp + 0x00000220u);
    ctx.eax = static_cast<uint32_t>(t75);
    // 0x004a0649: push edi
    uint32_t t76 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t76);
    mem.w32(t76, ctx.edi);
    // 0x004a064a: push eax
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, ctx.eax);
    // 0x004a064b: call 0x4e0cf0
    uint32_t t78 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    mem.w32(t78, 0x004a0650u);
    hle_crt_004e0cf0(ctx, mem);
    // 0x004a0650: add esp, 0xc
    uint32_t t79 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t79);
    ctx.esp = static_cast<uint32_t>(t79);
    // 0x004a0653: mov byte ptr [esp + esi + 0x21c], 0
    uint32_t t80 = static_cast<uint32_t>(ctx.esp + ctx.esi);
    uint32_t t81 = static_cast<uint32_t>(t80 + 0x0000021cu);
    mem.w8(t81, uint8_t{0x00u});
    goto bb_004a065b;
}
bb_004a063c: {
    // 0x004a063c: mov esi, 0x100
    ctx.esi = static_cast<uint32_t>(0x00000100u);
    goto bb_004a0641;
}
bb_004a0688: {
    // 0x004a0688: mov eax, dword ptr [esp + 0x14]
    uint32_t t82 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t83 = mem.r32(t82);
    ctx.eax = static_cast<uint32_t>(t83);
    // 0x004a068c: push esi
    uint32_t t84 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    mem.w32(t84, ctx.esi);
    // 0x004a068d: push eax
    uint32_t t85 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t85);
    mem.w32(t85, ctx.eax);
    // 0x004a068e: lea ecx, [esp + 0x24]
    uint32_t t86 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    ctx.ecx = static_cast<uint32_t>(t86);
    // 0x004a0692: push 0x53a60c
    uint32_t t87 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t87);
    mem.w32(t87, 0x0053a60cu);
    // 0x004a0697: push ecx
    uint32_t t88 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t88);
    mem.w32(t88, ctx.ecx);
    // 0x004a0698: call 0x4e068b
    uint32_t t89 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t89);
    mem.w32(t89, 0x004a069du);
    hle_crt_004e068b(ctx, mem);
    // 0x004a069d: add esp, 0x10
    uint32_t t90 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t90);
    ctx.esp = static_cast<uint32_t>(t90);
    // 0x004a06a0: cmp dword ptr [ebp], 0
    uint32_t t91 = mem.r32(ctx.ebp);
    uint32_t t92 = static_cast<uint32_t>(t91 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t91, 0x00000000u, t92);
    // 0x004a06a4: je 0x4a06ab
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a06ab;
    goto bb_004a06a6;
}
bb_004a06ab: {
    // 0x004a06ab: lea eax, [esp + 0x1c]
    uint32_t t93 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.eax = static_cast<uint32_t>(t93);
    // 0x004a06af: lea ebx, [esp + 0x11c]
    uint32_t t94 = static_cast<uint32_t>(ctx.esp + 0x0000011cu);
    ctx.ebx = static_cast<uint32_t>(t94);
    // 0x004a06b6: mov ecx, ebp
    ctx.ecx = static_cast<uint32_t>(ctx.ebp);
    // 0x004a06b8: call 0x40c670
    uint32_t t95 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t95);
    mem.w32(t95, 0x004a06bdu);
    sub_0040c670(ctx, mem);
    // 0x004a06bd: test eax, eax
    uint32_t t96 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t96);
    // 0x004a06bf: jne 0x4a06c6
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a06c6;
    goto bb_004a06c1;
}
bb_004a06a6: {
    // 0x004a06a6: or eax, 0xffffffff
    uint32_t t97 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t97);
    ctx.eax = static_cast<uint32_t>(t97);
    // 0x004a06a9: jmp 0x4a06cf
    goto bb_004a06cf;
}
bb_004a06c6: {
    // 0x004a06c6: push eax
    uint32_t t98 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t98);
    mem.w32(t98, ctx.eax);
    // 0x004a06c7: call 0x4e0eb7
    uint32_t t99 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t99);
    mem.w32(t99, 0x004a06ccu);
    hle_crt_004e0eb7(ctx, mem);
    // 0x004a06cc: add esp, 4
    uint32_t t100 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t100);
    ctx.esp = static_cast<uint32_t>(t100);
    goto bb_004a06cf;
}
bb_004a06c1: {
    // 0x004a06c1: or eax, 0xffffffff
    uint32_t t101 = static_cast<uint32_t>(ctx.eax | 0xffffffffu);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t101);
    ctx.eax = static_cast<uint32_t>(t101);
    // 0x004a06c4: jmp 0x4a06cf
}
bb_004a06cf: {
    // 0x004a06cf: mov dword ptr [edi], eax
    mem.w32(ctx.edi, ctx.eax);
    // 0x004a06d1: add esi, 1
    uint32_t t102 = static_cast<uint32_t>(ctx.esi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000001u, t102);
    ctx.esi = static_cast<uint32_t>(t102);
    // 0x004a06d4: add edi, 4
    uint32_t t103 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000004u, t103);
    ctx.edi = static_cast<uint32_t>(t103);
    // 0x004a06d7: cmp esi, 0x18
    uint32_t t104 = static_cast<uint32_t>(ctx.esi - 0x00000018u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00000018u, t104);
    // 0x004a06da: jl 0x4a0688
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004a0688;
}
{
    // 0x004a06dc: mov eax, dword ptr [esp + 0x14]
    uint32_t t105 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t106 = mem.r32(t105);
    ctx.eax = static_cast<uint32_t>(t106);
    // 0x004a06e0: add dword ptr [esp + 0x10], 0x164
    uint32_t t107 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t108 = mem.r32(t107);
    uint32_t t109 = static_cast<uint32_t>(t108 + 0x00000164u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t108, 0x00000164u, t109);
    mem.w32(t107, t109);
    // 0x004a06e8: add eax, 1
    uint32_t t110 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t110);
    ctx.eax = static_cast<uint32_t>(t110);
    // 0x004a06eb: cmp eax, 4
    uint32_t t111 = static_cast<uint32_t>(ctx.eax - 0x00000004u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000004u, t111);
    // 0x004a06ee: mov dword ptr [esp + 0x14], eax
    uint32_t t112 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t112, ctx.eax);
    // 0x004a06f2: jl 0x4a05b0
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004a05b0;
    goto bb_004a06f8;
}
bb_004a05b0: {
    // 0x004a05b0: mov esi, dword ptr [esp + 0x14]
    uint32_t t113 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t114 = mem.r32(t113);
    ctx.esi = static_cast<uint32_t>(t114);
    goto bb_004a05b4;
}
bb_004a06f8: {
    // 0x004a06f8: mov ecx, dword ptr [esp + 0x31c]
    uint32_t t115 = static_cast<uint32_t>(ctx.esp + 0x0000031cu);
    uint32_t t116 = mem.r32(t115);
    ctx.ecx = static_cast<uint32_t>(t116);
    // 0x004a06ff: pop edi
    uint32_t t117 = ctx.esp;
    uint32_t t118 = mem.r32(t117);
    uint32_t t119 = static_cast<uint32_t>(t117 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t119);
    ctx.edi = static_cast<uint32_t>(t118);
    // 0x004a0700: pop esi
    uint32_t t120 = ctx.esp;
    uint32_t t121 = mem.r32(t120);
    uint32_t t122 = static_cast<uint32_t>(t120 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t122);
    ctx.esi = static_cast<uint32_t>(t121);
    // 0x004a0701: pop ebx
    uint32_t t123 = ctx.esp;
    uint32_t t124 = mem.r32(t123);
    uint32_t t125 = static_cast<uint32_t>(t123 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t125);
    ctx.ebx = static_cast<uint32_t>(t124);
    // 0x004a0702: pop ebp
    uint32_t t126 = ctx.esp;
    uint32_t t127 = mem.r32(t126);
    uint32_t t128 = static_cast<uint32_t>(t126 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t128);
    ctx.ebp = static_cast<uint32_t>(t127);
    // 0x004a0703: xor ecx, esp
    uint32_t t129 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t129);
    ctx.ecx = static_cast<uint32_t>(t129);
    // 0x004a0705: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x004a070a: call 0x4e02f8
    uint32_t t130 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t130);
    mem.w32(t130, 0x004a070fu);
    hle_crt_004e02f8(ctx, mem);
    // 0x004a070f: add esp, 0x310
    uint32_t t131 = static_cast<uint32_t>(ctx.esp + 0x00000310u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000310u, t131);
    ctx.esp = static_cast<uint32_t>(t131);
    // 0x004a0715: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004a19c0 | subsystem=Sound | canonical | 3 blocks | 11 insns
void sub_004a19c0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a19c0: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x004a19c1: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004a19c3: call 0x4a19e0
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x004a19c8u);
    sub_004a19e0(ctx, mem);
    // 0x004a19c8: test byte ptr [esp + 8], 1
    uint32_t t2 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    uint8_t t3 = mem.r8(t2);
    uint8_t t4 = static_cast<uint8_t>(static_cast<uint32_t>(t3) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t4);
    // 0x004a19cd: je 0x4a19d8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a19d8;
    goto bb_004a19cf;
}
bb_004a19d8: {
    // 0x004a19d8: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004a19da: pop esi
    uint32_t t5 = ctx.esp;
    uint32_t t6 = mem.r32(t5);
    uint32_t t7 = static_cast<uint32_t>(t5 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x004a19db: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_004a19cf: {
    // 0x004a19cf: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x004a19d0: call 0x4e02f3
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x004a19d5u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004a19d5: add esp, 4
    uint32_t t10 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t10);
    ctx.esp = static_cast<uint32_t>(t10);
    goto bb_004a19d8;
}
}

// sub_004a19e0 | subsystem=Sound | canonical | 3 blocks | 40 insns
void sub_004a19e0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a19e0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x004a19e2: push 0x513973
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x00513973u);
    // 0x004a19e7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004a19ed: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x004a19ee: push ecx
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    mem.w32(t5, ctx.ecx);
    // 0x004a19ef: push ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebx);
    // 0x004a19f0: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x004a19f1: push edi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.edi);
    // 0x004a19f2: mov eax, dword ptr [0x54b458]
    uint32_t t9 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t9);
    // 0x004a19f7: xor eax, esp
    uint32_t t10 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.eax = static_cast<uint32_t>(t10);
    // 0x004a19f9: push eax
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.eax);
    // 0x004a19fa: lea eax, [esp + 0x14]
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x004a19fe: mov dword ptr fs:[0], eax
    uint32_t t13 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t13, ctx.eax);
    // 0x004a1a04: mov edi, ecx
    ctx.edi = static_cast<uint32_t>(ctx.ecx);
    // 0x004a1a06: mov dword ptr [esp + 0x10], edi
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t14, ctx.edi);
    // 0x004a1a0a: mov dword ptr [edi], 0x53a660
    mem.w32(ctx.edi, 0x0053a660u);
    // 0x004a1a10: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x004a1a15: lea esi, [edi + 4]
    uint32_t t15 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    ctx.esi = static_cast<uint32_t>(t15);
    // 0x004a1a18: mov dword ptr [esp + 0x1c], eax
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t16, ctx.eax);
    // 0x004a1a1c: add dword ptr [esi + 0x48], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.esi + 0x00000048u);
    uint32_t t18 = mem.r32(t17);
    uint32_t t19 = static_cast<uint32_t>(t18 + ctx.eax);
    recomp_detail::update_flags_add<uint32_t>(ctx, t18, ctx.eax, t19);
    mem.w32(t17, t19);
    // 0x004a1a1f: mov ebx, dword ptr [esi + 0x30]
    uint32_t t20 = static_cast<uint32_t>(ctx.esi + 0x00000030u);
    uint32_t t21 = mem.r32(t20);
    ctx.ebx = static_cast<uint32_t>(t21);
    // 0x004a1a22: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a1a24: call 0x414000
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x004a1a29u);
    sub_00414000(ctx, mem);
    // 0x004a1a29: test ebx, ebx
    uint32_t t23 = static_cast<uint32_t>(ctx.ebx & ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t23);
    // 0x004a1a2b: je 0x4a1a36
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1a36;
    goto bb_004a1a2d;
}
bb_004a1a36: {
    // 0x004a1a36: mov ecx, esi
    ctx.ecx = static_cast<uint32_t>(ctx.esi);
    // 0x004a1a38: mov byte ptr [esp + 0x1c], 0
    uint32_t t24 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w8(t24, uint8_t{0x00u});
    // 0x004a1a3d: call 0x414000
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x004a1a42u);
    sub_00414000(ctx, mem);
    // 0x004a1a42: mov dword ptr [edi], 0x53d540
    mem.w32(ctx.edi, 0x0053d540u);
    // 0x004a1a48: mov ecx, dword ptr [esp + 0x14]
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t27 = mem.r32(t26);
    ctx.ecx = static_cast<uint32_t>(t27);
    // 0x004a1a4c: mov dword ptr fs:[0], ecx
    uint32_t t28 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t28, ctx.ecx);
    // 0x004a1a53: pop ecx
    uint32_t t29 = ctx.esp;
    uint32_t t30 = mem.r32(t29);
    uint32_t t31 = static_cast<uint32_t>(t29 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    ctx.ecx = static_cast<uint32_t>(t30);
    // 0x004a1a54: pop edi
    uint32_t t32 = ctx.esp;
    uint32_t t33 = mem.r32(t32);
    uint32_t t34 = static_cast<uint32_t>(t32 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    ctx.edi = static_cast<uint32_t>(t33);
    // 0x004a1a55: pop esi
    uint32_t t35 = ctx.esp;
    uint32_t t36 = mem.r32(t35);
    uint32_t t37 = static_cast<uint32_t>(t35 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    ctx.esi = static_cast<uint32_t>(t36);
    // 0x004a1a56: pop ebx
    uint32_t t38 = ctx.esp;
    uint32_t t39 = mem.r32(t38);
    uint32_t t40 = static_cast<uint32_t>(t38 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    ctx.ebx = static_cast<uint32_t>(t39);
    // 0x004a1a57: add esp, 0x10
    uint32_t t41 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t41);
    ctx.esp = static_cast<uint32_t>(t41);
    // 0x004a1a5a: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a1a2d: {
    // 0x004a1a2d: push ebx
    uint32_t t42 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t42);
    mem.w32(t42, ctx.ebx);
    // 0x004a1a2e: call 0x4e00d0
    uint32_t t43 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    mem.w32(t43, 0x004a1a33u);
    hle_crt_004e00d0(ctx, mem);
    // 0x004a1a33: add esp, 4
    uint32_t t44 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t44);
    ctx.esp = static_cast<uint32_t>(t44);
    goto bb_004a1a36;
}
}

// sub_004a1a60 | subsystem=Sound | canonical | 10 blocks | 92 insns
void sub_004a1a60(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a1a60: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x004a1a61: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x004a1a63: and esp, 0xfffffff8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xfffffff8u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x004a1a66: sub esp, 0x114
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000114u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000114u, t2);
    ctx.esp = static_cast<uint32_t>(t2);
    // 0x004a1a6c: mov eax, dword ptr [0x54b458]
    uint32_t t3 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004a1a71: xor eax, esp
    uint32_t t4 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x004a1a73: mov dword ptr [esp + 0x110], eax
    uint32_t t5 = static_cast<uint32_t>(ctx.esp + 0x00000110u);
    mem.w32(t5, ctx.eax);
    // 0x004a1a7a: mov eax, dword ptr [ebp + 8]
    uint32_t t6 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t7 = mem.r32(t6);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x004a1a7d: push ebx
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.ebx);
    // 0x004a1a7e: push esi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.esi);
    // 0x004a1a7f: push edi
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.edi);
    // 0x004a1a80: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004a1a82: mov ecx, dword ptr [ebp + 0xc]
    uint32_t t11 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t12 = mem.r32(t11);
    ctx.ecx = static_cast<uint32_t>(t12);
    // 0x004a1a85: push ecx
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, ctx.ecx);
    // 0x004a1a86: push eax
    uint32_t t14 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    mem.w32(t14, ctx.eax);
    // 0x004a1a87: lea eax, [esp + 0x18]
    uint32_t t15 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x004a1a8b: push 0x53a654
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x0053a654u);
    // 0x004a1a90: push eax
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, ctx.eax);
    // 0x004a1a91: call 0x4e068b
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x004a1a96u);
    hle_crt_004e068b(ctx, mem);
    // 0x004a1a96: lea edi, [esi + 4]
    uint32_t t19 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    ctx.edi = static_cast<uint32_t>(t19);
    // 0x004a1a99: add esp, 0x10
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t20);
    ctx.esp = static_cast<uint32_t>(t20);
    // 0x004a1a9c: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004a1a9e: mov dword ptr [esp + 0xc], edi
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    mem.w32(t21, ctx.edi);
    // 0x004a1aa2: call 0x414000
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x004a1aa7u);
    sub_00414000(ctx, mem);
    // 0x004a1aa7: lea ecx, [esp + 0x10]
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    ctx.ecx = static_cast<uint32_t>(t23);
    // 0x004a1aab: push ecx
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, ctx.ecx);
    // 0x004a1aac: mov esi, 0x76e9c4
    ctx.esi = static_cast<uint32_t>(0x0076e9c4u);
    // 0x004a1ab1: call 0x4db8e0
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x004a1ab6u);
    sub_004db8e0(ctx, mem);
    // 0x004a1ab6: test eax, eax
    uint32_t t26 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t26);
    // 0x004a1ab8: je 0x4a1acc
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1acc;
    goto bb_004a1aba;
}
bb_004a1acc: {
    // 0x004a1acc: push 0
    uint32_t t27 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    mem.w32(t27, 0x00000000u);
    // 0x004a1ace: push 0x10000080
    uint32_t t28 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t28);
    mem.w32(t28, 0x10000080u);
    // 0x004a1ad3: push 3
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x00000003u);
    // 0x004a1ad5: push 0
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x00000000u);
    // 0x004a1ad7: push 1
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x00000001u);
    // 0x004a1ad9: push 0x80000000
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x80000000u);
    // 0x004a1ade: lea edx, [esp + 0x28]
    uint32_t t33 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.edx = static_cast<uint32_t>(t33);
    // 0x004a1ae2: push edx
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, ctx.edx);
    // 0x004a1ae3: call dword ptr [0x51b054]
    uint32_t t35 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t35);
    mem.w32(t35, 0x004a1ae9u);
    hle_iat_call(ctx, mem, 0x0051b054u);
    // 0x004a1ae9: cmp eax, -1
    uint32_t t36 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t36);
    // 0x004a1aec: je 0x4a1b51
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1b51;
    goto bb_004a1aee;
}
bb_004a1aba: {
    // 0x004a1aba: mov dword ptr [edi], 0
    mem.w32(ctx.edi, 0x00000000u);
    // 0x004a1ac0: mov dword ptr [edi + 0x1c], 3
    uint32_t t37 = static_cast<uint32_t>(ctx.edi + 0x0000001cu);
    mem.w32(t37, 0x00000003u);
    // 0x004a1ac7: mov dword ptr [edi + 0x58], eax
    uint32_t t38 = static_cast<uint32_t>(ctx.edi + 0x00000058u);
    mem.w32(t38, ctx.eax);
    // 0x004a1aca: jmp 0x4a1af7
    goto bb_004a1af7;
}
bb_004a1b51: {
    // 0x004a1b51: mov ecx, dword ptr [esp + 0x11c]
    uint32_t t39 = static_cast<uint32_t>(ctx.esp + 0x0000011cu);
    uint32_t t40 = mem.r32(t39);
    ctx.ecx = static_cast<uint32_t>(t40);
    // 0x004a1b58: pop edi
    uint32_t t41 = ctx.esp;
    uint32_t t42 = mem.r32(t41);
    uint32_t t43 = static_cast<uint32_t>(t41 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    ctx.edi = static_cast<uint32_t>(t42);
    // 0x004a1b59: pop esi
    uint32_t t44 = ctx.esp;
    uint32_t t45 = mem.r32(t44);
    uint32_t t46 = static_cast<uint32_t>(t44 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    ctx.esi = static_cast<uint32_t>(t45);
    // 0x004a1b5a: pop ebx
    uint32_t t47 = ctx.esp;
    uint32_t t48 = mem.r32(t47);
    uint32_t t49 = static_cast<uint32_t>(t47 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    ctx.ebx = static_cast<uint32_t>(t48);
    // 0x004a1b5b: xor ecx, esp
    uint32_t t50 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t50);
    ctx.ecx = static_cast<uint32_t>(t50);
    // 0x004a1b5d: xor al, al
    uint8_t t51 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) ^ static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t51);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t51));
    // 0x004a1b5f: call 0x4e02f8
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, 0x004a1b64u);
    hle_crt_004e02f8(ctx, mem);
    // 0x004a1b64: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x004a1b66: pop ebp
    uint32_t t53 = ctx.esp;
    uint32_t t54 = mem.r32(t53);
    uint32_t t55 = static_cast<uint32_t>(t53 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    ctx.ebp = static_cast<uint32_t>(t54);
    // 0x004a1b67: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
bb_004a1aee: {
    // 0x004a1aee: mov dword ptr [edi], eax
    mem.w32(ctx.edi, ctx.eax);
    // 0x004a1af0: mov dword ptr [edi + 0x1c], 0
    uint32_t t56 = static_cast<uint32_t>(ctx.edi + 0x0000001cu);
    mem.w32(t56, 0x00000000u);
}
bb_004a1af7: {
    // 0x004a1af7: mov esi, dword ptr [esp + 0xc]
    uint32_t t57 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t58 = mem.r32(t57);
    ctx.esi = static_cast<uint32_t>(t58);
    // 0x004a1afb: xor eax, eax
    uint32_t t59 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t59);
    ctx.eax = static_cast<uint32_t>(t59);
    // 0x004a1afd: mov dword ptr [edi + 8], eax
    uint32_t t60 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    mem.w32(t60, ctx.eax);
    // 0x004a1b00: mov dword ptr [edi + 0xc], eax
    uint32_t t61 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    mem.w32(t61, ctx.eax);
    // 0x004a1b03: mov dword ptr [edi + 0x10], eax
    uint32_t t62 = static_cast<uint32_t>(ctx.edi + 0x00000010u);
    mem.w32(t62, ctx.eax);
    // 0x004a1b06: mov dword ptr [edi + 0x14], eax
    uint32_t t63 = static_cast<uint32_t>(ctx.edi + 0x00000014u);
    mem.w32(t63, ctx.eax);
    // 0x004a1b09: mov dword ptr [edi + 0x18], eax
    uint32_t t64 = static_cast<uint32_t>(ctx.edi + 0x00000018u);
    mem.w32(t64, ctx.eax);
    // 0x004a1b0c: push eax
    uint32_t t65 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t65);
    mem.w32(t65, ctx.eax);
    // 0x004a1b0d: xor edi, edi
    uint32_t t66 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t66);
    ctx.edi = static_cast<uint32_t>(t66);
    // 0x004a1b0f: xor ebx, ebx
    uint32_t t67 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t67);
    ctx.ebx = static_cast<uint32_t>(t67);
    // 0x004a1b11: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004a1b13: call 0x413e70
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, 0x004a1b18u);
    sub_00413e70(ctx, mem);
    // 0x004a1b18: test eax, eax
    uint32_t t69 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t69);
    // 0x004a1b1a: je 0x4a1b51
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1b51;
}
{
    // 0x004a1b1c: mov eax, dword ptr [esi + 0x3c]
    uint32_t t70 = static_cast<uint32_t>(ctx.esi + 0x0000003cu);
    uint32_t t71 = mem.r32(t70);
    ctx.eax = static_cast<uint32_t>(t71);
    // 0x004a1b1f: test eax, eax
    uint32_t t72 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t72);
    // 0x004a1b21: je 0x4a1b38
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1b38;
    goto bb_004a1b23;
}
bb_004a1b38: {
    // 0x004a1b38: mov al, 1
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(uint8_t{0x01u}));
    // 0x004a1b3a: pop edi
    uint32_t t73 = ctx.esp;
    uint32_t t74 = mem.r32(t73);
    uint32_t t75 = static_cast<uint32_t>(t73 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    ctx.edi = static_cast<uint32_t>(t74);
    // 0x004a1b3b: pop esi
    uint32_t t76 = ctx.esp;
    uint32_t t77 = mem.r32(t76);
    uint32_t t78 = static_cast<uint32_t>(t76 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t78);
    ctx.esi = static_cast<uint32_t>(t77);
    // 0x004a1b3c: pop ebx
    uint32_t t79 = ctx.esp;
    uint32_t t80 = mem.r32(t79);
    uint32_t t81 = static_cast<uint32_t>(t79 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    ctx.ebx = static_cast<uint32_t>(t80);
    // 0x004a1b3d: mov ecx, dword ptr [esp + 0x110]
    uint32_t t82 = static_cast<uint32_t>(ctx.esp + 0x00000110u);
    uint32_t t83 = mem.r32(t82);
    ctx.ecx = static_cast<uint32_t>(t83);
    // 0x004a1b44: xor ecx, esp
    uint32_t t84 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t84);
    ctx.ecx = static_cast<uint32_t>(t84);
    // 0x004a1b46: call 0x4e02f8
    uint32_t t85 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t85);
    mem.w32(t85, 0x004a1b4bu);
    hle_crt_004e02f8(ctx, mem);
    // 0x004a1b4b: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x004a1b4d: pop ebp
    uint32_t t86 = ctx.esp;
    uint32_t t87 = mem.r32(t86);
    uint32_t t88 = static_cast<uint32_t>(t86 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t88);
    ctx.ebp = static_cast<uint32_t>(t87);
    // 0x004a1b4e: ret 8
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 8u;
    return;
}
bb_004a1b23: {
    // 0x004a1b23: push ebx
    uint32_t t89 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t89);
    mem.w32(t89, ctx.ebx);
    // 0x004a1b24: push -1
    uint32_t t90 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t90);
    mem.w32(t90, 0xffffffffu);
    // 0x004a1b26: push eax
    uint32_t t91 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t91);
    mem.w32(t91, ctx.eax);
    // 0x004a1b27: call dword ptr [0x51b1c4]
    uint32_t t92 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    mem.w32(t92, 0x004a1b2du);
    hle_iat_call(ctx, mem, 0x0051b1c4u);
    // 0x004a1b2d: cmp eax, 0xc0
    uint32_t t93 = static_cast<uint32_t>(ctx.eax - 0x000000c0u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x000000c0u, t93);
    // 0x004a1b32: je 0x4a1b51
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1b51;
}
{
    // 0x004a1b34: test eax, eax
    uint32_t t94 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t94);
    // 0x004a1b36: jne 0x4a1b51
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a1b51;
    goto bb_004a1b38;
}
}

// sub_004a1b70 | subsystem=Sound | canonical | 3 blocks | 12 insns
void sub_004a1b70(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a1b70: add dword ptr [ecx + 0x4c], 1
    uint32_t t0 = static_cast<uint32_t>(ctx.ecx + 0x0000004cu);
    uint32_t t1 = mem.r32(t0);
    uint32_t t2 = static_cast<uint32_t>(t1 + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t1, 0x00000001u, t2);
    mem.w32(t0, t2);
    // 0x004a1b74: add ecx, 4
    uint32_t t3 = static_cast<uint32_t>(ctx.ecx + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000004u, t3);
    ctx.ecx = static_cast<uint32_t>(t3);
    // 0x004a1b77: push esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.esi);
    // 0x004a1b78: mov esi, dword ptr [ecx + 0x30]
    uint32_t t5 = static_cast<uint32_t>(ctx.ecx + 0x00000030u);
    uint32_t t6 = mem.r32(t5);
    ctx.esi = static_cast<uint32_t>(t6);
    // 0x004a1b7b: call 0x414000
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x004a1b80u);
    sub_00414000(ctx, mem);
    // 0x004a1b80: test esi, esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esi & ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t8);
    // 0x004a1b82: je 0x4a1b8d
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1b8d;
    goto bb_004a1b84;
}
bb_004a1b8d: {
    // 0x004a1b8d: pop esi
    uint32_t t9 = ctx.esp;
    uint32_t t10 = mem.r32(t9);
    uint32_t t11 = static_cast<uint32_t>(t9 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    ctx.esi = static_cast<uint32_t>(t10);
    // 0x004a1b8e: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004a1b84: {
    // 0x004a1b84: push esi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.esi);
    // 0x004a1b85: call 0x4e00d0
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, 0x004a1b8au);
    hle_crt_004e00d0(ctx, mem);
    // 0x004a1b8a: add esp, 4
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t14);
    ctx.esp = static_cast<uint32_t>(t14);
    goto bb_004a1b8d;
}
}

// sub_004a1b90 | subsystem=Sound | canonical | 11 blocks | 43 insns
void sub_004a1b90(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004a1b90: push esi
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.esi);
    // 0x004a1b91: push edi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.edi);
    // 0x004a1b92: mov edi, dword ptr [esp + 0xc]
    uint32_t t2 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t3 = mem.r32(t2);
    ctx.edi = static_cast<uint32_t>(t3);
    // 0x004a1b96: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004a1b98: mov dword ptr [edi + 4], 0
    uint32_t t4 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    mem.w32(t4, 0x00000000u);
    // 0x004a1b9f: mov eax, dword ptr [esi + 0x20]
    uint32_t t5 = static_cast<uint32_t>(ctx.esi + 0x00000020u);
    uint32_t t6 = mem.r32(t5);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x004a1ba2: cmp eax, 2
    uint32_t t7 = static_cast<uint32_t>(ctx.eax - 0x00000002u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000002u, t7);
    // 0x004a1ba5: je 0x4a1beb
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1beb;
    goto bb_004a1ba7;
}
bb_004a1beb: {
    // 0x004a1beb: mov eax, dword ptr [esi + 0x2c]
    uint32_t t8 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    uint32_t t9 = mem.r32(t8);
    ctx.eax = static_cast<uint32_t>(t9);
    goto bb_004a1bee;
}
bb_004a1ba7: {
    // 0x004a1ba7: cmp eax, 3
    uint32_t t10 = static_cast<uint32_t>(ctx.eax - 0x00000003u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000003u, t10);
    // 0x004a1baa: jne 0x4a1bbb
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a1bbb;
    goto bb_004a1bac;
}
bb_004a1bee: {
    // 0x004a1bee: mov dword ptr [edi + 8], eax
    uint32_t t11 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    mem.w32(t11, ctx.eax);
    // 0x004a1bf1: mov ecx, dword ptr [esi + 0x34]
    uint32_t t12 = static_cast<uint32_t>(ctx.esi + 0x00000034u);
    uint32_t t13 = mem.r32(t12);
    ctx.ecx = static_cast<uint32_t>(t13);
    // 0x004a1bf4: add dword ptr [esi + 0x4c], 1
    uint32_t t14 = static_cast<uint32_t>(ctx.esi + 0x0000004cu);
    uint32_t t15 = mem.r32(t14);
    uint32_t t16 = static_cast<uint32_t>(t15 + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t15, 0x00000001u, t16);
    mem.w32(t14, t16);
    // 0x004a1bf8: mov dword ptr [edi], ecx
    mem.w32(ctx.edi, ctx.ecx);
    // 0x004a1bfa: pop edi
    uint32_t t17 = ctx.esp;
    uint32_t t18 = mem.r32(t17);
    uint32_t t19 = static_cast<uint32_t>(t17 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    ctx.edi = static_cast<uint32_t>(t18);
    // 0x004a1bfb: pop esi
    uint32_t t20 = ctx.esp;
    uint32_t t21 = mem.r32(t20);
    uint32_t t22 = static_cast<uint32_t>(t20 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    ctx.esi = static_cast<uint32_t>(t21);
    // 0x004a1bfc: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_004a1bbb: {
    // 0x004a1bbb: mov ecx, dword ptr [esi + 4]
    uint32_t t23 = static_cast<uint32_t>(ctx.esi + 0x00000004u);
    uint32_t t24 = mem.r32(t23);
    ctx.ecx = static_cast<uint32_t>(t24);
    // 0x004a1bbe: test ecx, ecx
    uint32_t t25 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t25);
    // 0x004a1bc0: jne 0x4a1bd5
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a1bd5;
    goto bb_004a1bc2;
}
bb_004a1bac: {
    // 0x004a1bac: mov eax, dword ptr [esi + 0x5c]
    uint32_t t26 = static_cast<uint32_t>(ctx.esi + 0x0000005cu);
    uint32_t t27 = mem.r32(t26);
    ctx.eax = static_cast<uint32_t>(t27);
    // 0x004a1baf: mov eax, dword ptr [eax + 0x78]
    uint32_t t28 = static_cast<uint32_t>(ctx.eax + 0x00000078u);
    uint32_t t29 = mem.r32(t28);
    ctx.eax = static_cast<uint32_t>(t29);
    // 0x004a1bb2: test eax, eax
    uint32_t t30 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t30);
    // 0x004a1bb4: je 0x4a1be8
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004a1be8;
    goto bb_004a1bb6;
}
bb_004a1bd5: {
    // 0x004a1bd5: mov eax, dword ptr [esi + 0x2c]
    uint32_t t31 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    uint32_t t32 = mem.r32(t31);
    ctx.eax = static_cast<uint32_t>(t32);
    // 0x004a1bd8: test eax, eax
    uint32_t t33 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t33);
    // 0x004a1bda: jne 0x4a1bee
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004a1bee;
    goto bb_004a1bdc;
}
bb_004a1bc2: {
    // 0x004a1bc2: xor eax, eax
    uint32_t t34 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t34);
    ctx.eax = static_cast<uint32_t>(t34);
    // 0x004a1bc4: mov dword ptr [edi + 8], eax
    uint32_t t35 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    mem.w32(t35, ctx.eax);
    // 0x004a1bc7: mov ecx, dword ptr [esi + 0x34]
    uint32_t t36 = static_cast<uint32_t>(ctx.esi + 0x00000034u);
    uint32_t t37 = mem.r32(t36);
    ctx.ecx = static_cast<uint32_t>(t37);
    // 0x004a1bca: add dword ptr [esi + 0x4c], 1
    uint32_t t38 = static_cast<uint32_t>(ctx.esi + 0x0000004cu);
    uint32_t t39 = mem.r32(t38);
    uint32_t t40 = static_cast<uint32_t>(t39 + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t39, 0x00000001u, t40);
    mem.w32(t38, t40);
    // 0x004a1bce: mov dword ptr [edi], ecx
    mem.w32(ctx.edi, ctx.ecx);
    // 0x004a1bd0: pop edi
    uint32_t t41 = ctx.esp;
    uint32_t t42 = mem.r32(t41);
    uint32_t t43 = static_cast<uint32_t>(t41 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    ctx.edi = static_cast<uint32_t>(t42);
    // 0x004a1bd1: pop esi
    uint32_t t44 = ctx.esp;
    uint32_t t45 = mem.r32(t44);
    uint32_t t46 = static_cast<uint32_t>(t44 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    ctx.esi = static_cast<uint32_t>(t45);
    // 0x004a1bd2: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_004a1be8: {
    // 0x004a1be8: mov dword ptr [esi + 0x2c], eax
    uint32_t t47 = static_cast<uint32_t>(ctx.esi + 0x0000002cu);
    mem.w32(t47, ctx.eax);
    goto bb_004a1beb;
}
bb_004a1bb6: {
    // 0x004a1bb6: mov eax, dword ptr [eax + 0x28]
    uint32_t t48 = static_cast<uint32_t>(ctx.eax + 0x00000028u);
    uint32_t t49 = mem.r32(t48);
    ctx.eax = static_cast<uint32_t>(t49);
    // 0x004a1bb9: jmp 0x4a1be8
    goto bb_004a1be8;
}
bb_004a1bdc: {
    // 0x004a1bdc: lea eax, [esp + 0xc]
    uint32_t t50 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    ctx.eax = static_cast<uint32_t>(t50);
    // 0x004a1be0: push eax
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, ctx.eax);
    // 0x004a1be1: push ecx
    uint32_t t52 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    mem.w32(t52, ctx.ecx);
    // 0x004a1be2: call dword ptr [0x51b058]
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, 0x004a1be8u);
    hle_iat_call(ctx, mem, 0x0051b058u);
    goto bb_004a1be8;
}
}

// sub_004dd4d0 | subsystem=Sound | canonical | 3 blocks | 11 insns
void sub_004dd4d0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dd4d0: test byte ptr [esp + 4], 1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    uint8_t t1 = mem.r8(t0);
    uint8_t t2 = static_cast<uint8_t>(static_cast<uint32_t>(t1) & static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t2);
    // 0x004dd4d5: push esi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.esi);
    // 0x004dd4d6: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004dd4d8: mov dword ptr [esi], 0x53d540
    mem.w32(ctx.esi, 0x0053d540u);
    // 0x004dd4de: je 0x4dd4e9
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dd4e9;
    goto bb_004dd4e0;
}
bb_004dd4e9: {
    // 0x004dd4e9: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004dd4eb: pop esi
    uint32_t t4 = ctx.esp;
    uint32_t t5 = mem.r32(t4);
    uint32_t t6 = static_cast<uint32_t>(t4 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    ctx.esi = static_cast<uint32_t>(t5);
    // 0x004dd4ec: ret 4
    ctx.eip = ctx.pop32(mem);
    ctx.esp += 4u;
    return;
}
bb_004dd4e0: {
    // 0x004dd4e0: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x004dd4e1: call 0x4e02f3
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x004dd4e6u);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dd4e6: add esp, 4
    uint32_t t9 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t9);
    ctx.esp = static_cast<uint32_t>(t9);
    goto bb_004dd4e9;
}
}

// sub_004dd560 | subsystem=Sound | canonical | 11 blocks | 35 insns
void sub_004dd560(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dd560: cmp esi, 0x640
    uint32_t t0 = static_cast<uint32_t>(ctx.esi - 0x00000640u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x00000640u, t0);
    // 0x004dd566: jge 0x4dd5c6
    if (recomp_detail::eval_cond(ctx, Cond::GE)) goto bb_004dd5c6;
    goto bb_004dd568;
}
bb_004dd5c6: {
    // 0x004dd5c6: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004dd568: {
    // 0x004dd568: mov eax, dword ptr [esi*4 + 0x76a7b0]
    uint32_t t1 = recomp_detail::shl<uint32_t>(ctx.esi, 0x00000002u);
    uint32_t t2 = static_cast<uint32_t>(t1 + 0x0076a7b0u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004dd56f: test eax, eax
    uint32_t t4 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    // 0x004dd571: je 0x4dd587
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dd587;
    goto bb_004dd573;
}
bb_004dd587: {
    // 0x004dd587: test edi, edi
    uint32_t t5 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    // 0x004dd589: je 0x4dd5c6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dd5c6;
    goto bb_004dd58b;
}
bb_004dd573: {
    // 0x004dd573: push eax
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.eax);
    // 0x004dd574: call 0x4e00d0
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, 0x004dd579u);
    hle_crt_004e00d0(ctx, mem);
    // 0x004dd579: add esp, 4
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t8);
    ctx.esp = static_cast<uint32_t>(t8);
    // 0x004dd57c: mov dword ptr [esi*4 + 0x76a7b0], 0
    uint32_t t9 = recomp_detail::shl<uint32_t>(ctx.esi, 0x00000002u);
    uint32_t t10 = static_cast<uint32_t>(t9 + 0x0076a7b0u);
    mem.w32(t10, 0x00000000u);
    goto bb_004dd587;
}
bb_004dd58b: {
    // 0x004dd58b: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x004dd58d: lea edx, [eax + 1]
    uint32_t t11 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    ctx.edx = static_cast<uint32_t>(t11);
}
bb_004dd590: {
    // 0x004dd590: mov cl, byte ptr [eax]
    uint8_t t12 = mem.r8(ctx.eax);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t12));
    // 0x004dd592: add eax, 1
    uint32_t t13 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t13);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x004dd595: test cl, cl
    uint8_t t14 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t14);
    // 0x004dd597: jne 0x4dd590
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dd590;
}
{
    // 0x004dd599: sub eax, edx
    uint32_t t15 = static_cast<uint32_t>(ctx.eax - ctx.edx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edx, t15);
    ctx.eax = static_cast<uint32_t>(t15);
    // 0x004dd59b: je 0x4dd5c6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dd5c6;
}
{
    // 0x004dd59d: add eax, 1
    uint32_t t16 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t16);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x004dd5a0: push eax
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, ctx.eax);
    // 0x004dd5a1: call 0x4e0230
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x004dd5a6u);
    hle_crt_004e0230(ctx, mem);
    // 0x004dd5a6: add esp, 4
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t19);
    ctx.esp = static_cast<uint32_t>(t19);
    // 0x004dd5a9: test eax, eax
    uint32_t t20 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t20);
    // 0x004dd5ab: mov dword ptr [esi*4 + 0x76a7b0], eax
    uint32_t t21 = recomp_detail::shl<uint32_t>(ctx.esi, 0x00000002u);
    uint32_t t22 = static_cast<uint32_t>(t21 + 0x0076a7b0u);
    mem.w32(t22, ctx.eax);
    // 0x004dd5b2: je 0x4dd5c6
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dd5c6;
}
{
    // 0x004dd5b4: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004dd5b6: mov edx, eax
    ctx.edx = static_cast<uint32_t>(ctx.eax);
}
bb_004dd5b8: {
    // 0x004dd5b8: mov al, byte ptr [ecx]
    uint8_t t23 = mem.r8(ctx.ecx);
    recomp_detail::w8l(ctx.eax, static_cast<uint8_t>(t23));
    // 0x004dd5ba: mov byte ptr [edx], al
    mem.w8(ctx.edx, recomp_detail::r8l(ctx.eax));
    // 0x004dd5bc: add ecx, 1
    uint32_t t24 = static_cast<uint32_t>(ctx.ecx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ecx, 0x00000001u, t24);
    ctx.ecx = static_cast<uint32_t>(t24);
    // 0x004dd5bf: add edx, 1
    uint32_t t25 = static_cast<uint32_t>(ctx.edx + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edx, 0x00000001u, t25);
    ctx.edx = static_cast<uint32_t>(t25);
    // 0x004dd5c2: test al, al
    uint8_t t26 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) & static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)));
    recomp_detail::update_flags_logic<uint8_t>(ctx, t26);
    // 0x004dd5c4: jne 0x4dd5b8
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dd5b8;
    goto bb_004dd5c6;
}
}

// sub_004dd5d0 | subsystem=Sound | canonical | 25 blocks | 136 insns
void sub_004dd5d0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dd5d0: push -1
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, 0xffffffffu);
    // 0x004dd5d2: push 0x5164ae
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, 0x005164aeu);
    // 0x004dd5d7: mov eax, dword ptr fs:[0]
    uint32_t t2 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t3 = mem.r32(t2);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004dd5dd: push eax
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.eax);
    // 0x004dd5de: sub esp, 0x10c
    uint32_t t5 = static_cast<uint32_t>(ctx.esp - 0x0000010cu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x0000010cu, t5);
    ctx.esp = static_cast<uint32_t>(t5);
    // 0x004dd5e4: mov eax, dword ptr [0x54b458]
    uint32_t t6 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t6);
    // 0x004dd5e9: xor eax, esp
    uint32_t t7 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    ctx.eax = static_cast<uint32_t>(t7);
    // 0x004dd5eb: mov dword ptr [esp + 0x108], eax
    uint32_t t8 = static_cast<uint32_t>(ctx.esp + 0x00000108u);
    mem.w32(t8, ctx.eax);
    // 0x004dd5f2: push ebx
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.ebx);
    // 0x004dd5f3: push ebp
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.ebp);
    // 0x004dd5f4: push esi
    uint32_t t11 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    mem.w32(t11, ctx.esi);
    // 0x004dd5f5: push edi
    uint32_t t12 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t12);
    mem.w32(t12, ctx.edi);
    // 0x004dd5f6: mov eax, dword ptr [0x54b458]
    uint32_t t13 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x004dd5fb: xor eax, esp
    uint32_t t14 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x004dd5fd: push eax
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.eax);
    // 0x004dd5fe: lea eax, [esp + 0x120]
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000120u);
    ctx.eax = static_cast<uint32_t>(t16);
    // 0x004dd605: mov dword ptr fs:[0], eax
    uint32_t t17 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t17, ctx.eax);
    // 0x004dd60b: push 0x1c20
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x00001c20u);
    // 0x004dd610: xor edi, edi
    uint32_t t19 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t19);
    ctx.edi = static_cast<uint32_t>(t19);
    // 0x004dd612: push edi
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, ctx.edi);
    // 0x004dd613: push 0x768b90
    uint32_t t21 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t21);
    mem.w32(t21, 0x00768b90u);
    // 0x004dd618: call 0x4e6340
    uint32_t t22 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t22);
    mem.w32(t22, 0x004dd61du);
    hle_crt_004e6340(ctx, mem);
    // 0x004dd61d: add esp, 0xc
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t23);
    ctx.esp = static_cast<uint32_t>(t23);
    // 0x004dd620: push 0x140
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x00000140u);
    // 0x004dd625: call 0x4e0177
    uint32_t t25 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    mem.w32(t25, 0x004dd62au);
    hle_crt_004e0177(ctx, mem);
    // 0x004dd62a: add esp, 4
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t26);
    ctx.esp = static_cast<uint32_t>(t26);
    // 0x004dd62d: mov dword ptr [esp + 0x14], eax
    uint32_t t27 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t27, ctx.eax);
    // 0x004dd631: cmp eax, edi
    uint32_t t28 = static_cast<uint32_t>(ctx.eax - ctx.edi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.edi, t28);
    // 0x004dd633: mov dword ptr [esp + 0x128], edi
    uint32_t t29 = static_cast<uint32_t>(ctx.esp + 0x00000128u);
    mem.w32(t29, ctx.edi);
    // 0x004dd63a: je 0x4dd645
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dd645;
    goto bb_004dd63c;
}
bb_004dd645: {
    // 0x004dd645: push 0x53d550
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x0053d550u);
    // 0x004dd64a: mov ebx, edi
    ctx.ebx = static_cast<uint32_t>(ctx.edi);
    // 0x004dd64c: mov dword ptr [esp + 0x12c], 0xffffffff
    uint32_t t31 = static_cast<uint32_t>(ctx.esp + 0x0000012cu);
    mem.w32(t31, 0xffffffffu);
    // 0x004dd657: call 0x40c2b0
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x004dd65cu);
    sub_0040c2b0(ctx, mem);
    // 0x004dd65c: test eax, eax
    uint32_t t33 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t33);
    // 0x004dd65e: je 0x4dd766
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dd766;
    goto bb_004dd664;
}
bb_004dd63c: {
    // 0x004dd63c: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004dd63e: call 0x40c260
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x004dd643u);
    sub_0040c260(ctx, mem);
    // 0x004dd643: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    goto bb_004dd645;
}
bb_004dd766: {
    // 0x004dd766: test edi, edi
    uint32_t t35 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t35);
    // 0x004dd768: je 0x4dd771
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dd771;
    goto bb_004dd76a;
}
bb_004dd664: {
    // 0x004dd664: xor eax, eax
    uint32_t t36 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t36);
    ctx.eax = static_cast<uint32_t>(t36);
    // 0x004dd666: mov dword ptr [esp + 0x14], eax
    uint32_t t37 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t37, ctx.eax);
    // 0x004dd66a: mov esi, 0x768b98
    ctx.esi = static_cast<uint32_t>(0x00768b98u);
    // 0x004dd66f: jmp 0x4dd673
    goto bb_004dd673;
}
bb_004dd771: {
    // 0x004dd771: mov ecx, dword ptr [esp + 0x120]
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000120u);
    uint32_t t39 = mem.r32(t38);
    ctx.ecx = static_cast<uint32_t>(t39);
    // 0x004dd778: mov dword ptr fs:[0], ecx
    uint32_t t40 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t40, ctx.ecx);
    // 0x004dd77f: pop ecx
    uint32_t t41 = ctx.esp;
    uint32_t t42 = mem.r32(t41);
    uint32_t t43 = static_cast<uint32_t>(t41 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    ctx.ecx = static_cast<uint32_t>(t42);
    // 0x004dd780: pop edi
    uint32_t t44 = ctx.esp;
    uint32_t t45 = mem.r32(t44);
    uint32_t t46 = static_cast<uint32_t>(t44 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t46);
    ctx.edi = static_cast<uint32_t>(t45);
    // 0x004dd781: pop esi
    uint32_t t47 = ctx.esp;
    uint32_t t48 = mem.r32(t47);
    uint32_t t49 = static_cast<uint32_t>(t47 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t49);
    ctx.esi = static_cast<uint32_t>(t48);
    // 0x004dd782: pop ebp
    uint32_t t50 = ctx.esp;
    uint32_t t51 = mem.r32(t50);
    uint32_t t52 = static_cast<uint32_t>(t50 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t52);
    ctx.ebp = static_cast<uint32_t>(t51);
    // 0x004dd783: pop ebx
    uint32_t t53 = ctx.esp;
    uint32_t t54 = mem.r32(t53);
    uint32_t t55 = static_cast<uint32_t>(t53 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    ctx.ebx = static_cast<uint32_t>(t54);
    // 0x004dd784: mov ecx, dword ptr [esp + 0x108]
    uint32_t t56 = static_cast<uint32_t>(ctx.esp + 0x00000108u);
    uint32_t t57 = mem.r32(t56);
    ctx.ecx = static_cast<uint32_t>(t57);
    // 0x004dd78b: xor ecx, esp
    uint32_t t58 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t58);
    ctx.ecx = static_cast<uint32_t>(t58);
    // 0x004dd78d: call 0x4e02f8
    uint32_t t59 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    mem.w32(t59, 0x004dd792u);
    hle_crt_004e02f8(ctx, mem);
    // 0x004dd792: add esp, 0x118
    uint32_t t60 = static_cast<uint32_t>(ctx.esp + 0x00000118u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000118u, t60);
    ctx.esp = static_cast<uint32_t>(t60);
    // 0x004dd798: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004dd76a: {
    // 0x004dd76a: mov eax, edi
    ctx.eax = static_cast<uint32_t>(ctx.edi);
    // 0x004dd76c: call 0x40b480
    uint32_t t61 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t61);
    mem.w32(t61, 0x004dd771u);
    sub_0040b480(ctx, mem);
    goto bb_004dd771;
}
bb_004dd673: {
    // 0x004dd673: fldz
    ctx.fpu_push(0.0);
    // 0x004dd675: mov dword ptr [esi - 8], eax
    uint32_t t62 = static_cast<uint32_t>(ctx.esi + 0xfffffff8u);
    mem.w32(t62, ctx.eax);
    // 0x004dd678: mov dword ptr [esi - 4], eax
    uint32_t t63 = static_cast<uint32_t>(ctx.esi + 0xfffffffcu);
    mem.w32(t63, ctx.eax);
    // 0x004dd67b: fstp qword ptr [esi]
    double t64 = ctx.fpu_st(0);
    mem.wf64(ctx.esi, t64);
    ctx.fpu_pop();
    // 0x004dd67d: mov byte ptr [esi + 8], al
    uint32_t t65 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    mem.w8(t65, recomp_detail::r8l(ctx.eax));
    // 0x004dd680: mov eax, dword ptr [esp + 0x14]
    uint32_t t66 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t67 = mem.r32(t66);
    ctx.eax = static_cast<uint32_t>(t67);
    // 0x004dd684: push eax
    uint32_t t68 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t68);
    mem.w32(t68, ctx.eax);
    // 0x004dd685: lea ecx, [esp + 0x20]
    uint32_t t69 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    ctx.ecx = static_cast<uint32_t>(t69);
    // 0x004dd689: push 0x53d560
    uint32_t t70 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    mem.w32(t70, 0x0053d560u);
    // 0x004dd68e: push ecx
    uint32_t t71 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t71);
    mem.w32(t71, ctx.ecx);
    // 0x004dd68f: call 0x4e068b
    uint32_t t72 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    mem.w32(t72, 0x004dd694u);
    hle_crt_004e068b(ctx, mem);
    // 0x004dd694: add esp, 0xc
    uint32_t t73 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t73);
    ctx.esp = static_cast<uint32_t>(t73);
    // 0x004dd697: lea ebx, [esp + 0x1c]
    uint32_t t74 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.ebx = static_cast<uint32_t>(t74);
    // 0x004dd69b: call 0x40c440
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, 0x004dd6a0u);
    sub_0040c440(ctx, mem);
    // 0x004dd6a0: test eax, eax
    uint32_t t76 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t76);
    // 0x004dd6a2: je 0x4dd752
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dd752;
    goto bb_004dd6a8;
}
bb_004dd752: {
    // 0x004dd752: add dword ptr [esp + 0x14], 1
    uint32_t t77 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t78 = mem.r32(t77);
    uint32_t t79 = static_cast<uint32_t>(t78 + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t78, 0x00000001u, t79);
    mem.w32(t77, t79);
    // 0x004dd757: add esi, 0x30
    uint32_t t80 = static_cast<uint32_t>(ctx.esi + 0x00000030u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000030u, t80);
    ctx.esi = static_cast<uint32_t>(t80);
    // 0x004dd75a: cmp esi, 0x76a7b8
    uint32_t t81 = static_cast<uint32_t>(ctx.esi - 0x0076a7b8u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x0076a7b8u, t81);
    // 0x004dd760: jl 0x4dd671
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004dd671;
    goto bb_004dd766;
}
bb_004dd6a8: {
    // 0x004dd6a8: cmp dword ptr [edi], 0
    uint32_t t82 = mem.r32(ctx.edi);
    uint32_t t83 = static_cast<uint32_t>(t82 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t82, 0x00000000u, t83);
    // 0x004dd6ab: je 0x4dd6b1
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dd6b1;
    goto bb_004dd6ad;
}
bb_004dd671: {
    // 0x004dd671: xor eax, eax
    uint32_t t84 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t84);
    ctx.eax = static_cast<uint32_t>(t84);
    goto bb_004dd673;
}
bb_004dd6b1: {
    // 0x004dd6b1: mov eax, 0x53d56c
    ctx.eax = static_cast<uint32_t>(0x0053d56cu);
    // 0x004dd6b6: lea ebx, [esp + 0x1c]
    uint32_t t85 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.ebx = static_cast<uint32_t>(t85);
    // 0x004dd6ba: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004dd6bc: call 0x40c670
    uint32_t t86 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t86);
    mem.w32(t86, 0x004dd6c1u);
    sub_0040c670(ctx, mem);
    // 0x004dd6c1: test eax, eax
    uint32_t t87 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t87);
    // 0x004dd6c3: je 0x4dd6ce
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dd6ce;
    goto bb_004dd6c5;
}
bb_004dd6ad: {
    // 0x004dd6ad: xor eax, eax
    uint32_t t88 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t88);
    ctx.eax = static_cast<uint32_t>(t88);
    // 0x004dd6af: jmp 0x4dd6ce
}
bb_004dd6ce: {
    // 0x004dd6ce: mov dword ptr [esi - 4], eax
    uint32_t t89 = static_cast<uint32_t>(ctx.esi + 0xfffffffcu);
    mem.w32(t89, ctx.eax);
    // 0x004dd6d1: cmp dword ptr [edi], 0
    uint32_t t90 = mem.r32(ctx.edi);
    uint32_t t91 = static_cast<uint32_t>(t90 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t90, 0x00000000u, t91);
    // 0x004dd6d4: je 0x4dd6de
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dd6de;
    goto bb_004dd6d6;
}
bb_004dd6c5: {
    // 0x004dd6c5: push eax
    uint32_t t92 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t92);
    mem.w32(t92, ctx.eax);
    // 0x004dd6c6: call 0x4e0eb7
    uint32_t t93 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t93);
    mem.w32(t93, 0x004dd6cbu);
    hle_crt_004e0eb7(ctx, mem);
    // 0x004dd6cb: add esp, 4
    uint32_t t94 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t94);
    ctx.esp = static_cast<uint32_t>(t94);
    goto bb_004dd6ce;
}
bb_004dd6de: {
    // 0x004dd6de: mov eax, 0x53d574
    ctx.eax = static_cast<uint32_t>(0x0053d574u);
    // 0x004dd6e3: lea ebx, [esp + 0x1c]
    uint32_t t95 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.ebx = static_cast<uint32_t>(t95);
    // 0x004dd6e7: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004dd6e9: call 0x40c670
    uint32_t t96 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    mem.w32(t96, 0x004dd6eeu);
    sub_0040c670(ctx, mem);
    // 0x004dd6ee: test eax, eax
    uint32_t t97 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t97);
    // 0x004dd6f0: jne 0x4dd6fa
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dd6fa;
    goto bb_004dd6f2;
}
bb_004dd6d6: {
    // 0x004dd6d6: fldz
    ctx.fpu_push(0.0);
    // 0x004dd6d8: fstp dword ptr [esp + 0x18]
    double t98 = ctx.fpu_st(0);
    uint32_t t99 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.wf32(t99, static_cast<float>(t98));
    ctx.fpu_pop();
    // 0x004dd6dc: jmp 0x4dd707
    goto bb_004dd707;
}
bb_004dd6fa: {
    // 0x004dd6fa: push eax
    uint32_t t100 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t100);
    mem.w32(t100, ctx.eax);
    // 0x004dd6fb: call 0x4e0fe7
    uint32_t t101 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t101);
    mem.w32(t101, 0x004dd700u);
    hle_crt_004e0fe7(ctx, mem);
    // 0x004dd700: fstp dword ptr [esp + 0x1c]
    double t102 = ctx.fpu_st(0);
    uint32_t t103 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.wf32(t103, static_cast<float>(t102));
    ctx.fpu_pop();
    // 0x004dd704: add esp, 4
    uint32_t t104 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t104);
    ctx.esp = static_cast<uint32_t>(t104);
    goto bb_004dd707;
}
bb_004dd6f2: {
    // 0x004dd6f2: fldz
    ctx.fpu_push(0.0);
    // 0x004dd6f4: fstp dword ptr [esp + 0x18]
    double t105 = ctx.fpu_st(0);
    uint32_t t106 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.wf32(t106, static_cast<float>(t105));
    ctx.fpu_pop();
    // 0x004dd6f8: jmp 0x4dd707
}
bb_004dd707: {
    // 0x004dd707: fld dword ptr [esp + 0x18]
    uint32_t t107 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    double t108 = static_cast<double>(mem.rf32(t107));
    ctx.fpu_push(t108);
    // 0x004dd70b: fstp qword ptr [esi]
    double t109 = ctx.fpu_st(0);
    mem.wf64(ctx.esi, t109);
    ctx.fpu_pop();
    // 0x004dd70d: cmp dword ptr [edi], 0
    uint32_t t110 = mem.r32(ctx.edi);
    uint32_t t111 = static_cast<uint32_t>(t110 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t110, 0x00000000u, t111);
    // 0x004dd710: jne 0x4dd74b
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dd74b;
    goto bb_004dd712;
}
bb_004dd74b: {
    // 0x004dd74b: mov dword ptr [esi - 8], 1
    uint32_t t112 = static_cast<uint32_t>(ctx.esi + 0xfffffff8u);
    mem.w32(t112, 0x00000001u);
    goto bb_004dd752;
}
bb_004dd712: {
    // 0x004dd712: mov eax, 0x5350bc
    ctx.eax = static_cast<uint32_t>(0x005350bcu);
    // 0x004dd717: lea ebx, [esp + 0x1c]
    uint32_t t113 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.ebx = static_cast<uint32_t>(t113);
    // 0x004dd71b: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004dd71d: call 0x40c670
    uint32_t t114 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t114);
    mem.w32(t114, 0x004dd722u);
    sub_0040c670(ctx, mem);
    // 0x004dd722: mov ebp, eax
    ctx.ebp = static_cast<uint32_t>(ctx.eax);
    // 0x004dd724: test ebp, ebp
    uint32_t t115 = static_cast<uint32_t>(ctx.ebp & ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t115);
    // 0x004dd726: je 0x4dd74b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dd74b;
}
{
    // 0x004dd728: call 0x40cb40
    uint32_t t116 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t116);
    mem.w32(t116, 0x004dd72du);
    sub_0040cb40(ctx, mem);
    // 0x004dd72d: mov ebx, eax
    ctx.ebx = static_cast<uint32_t>(ctx.eax);
    // 0x004dd72f: cmp ebx, 0x20
    uint32_t t117 = static_cast<uint32_t>(ctx.ebx - 0x00000020u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ebx, 0x00000020u, t117);
    // 0x004dd732: jle 0x4dd739
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_004dd739;
    goto bb_004dd734;
}
bb_004dd739: {
    // 0x004dd739: push ebx
    uint32_t t118 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t118);
    mem.w32(t118, ctx.ebx);
    // 0x004dd73a: push ebp
    uint32_t t119 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t119);
    mem.w32(t119, ctx.ebp);
    // 0x004dd73b: lea ebp, [esi + 8]
    uint32_t t120 = static_cast<uint32_t>(ctx.esi + 0x00000008u);
    ctx.ebp = static_cast<uint32_t>(t120);
    // 0x004dd73e: push ebp
    uint32_t t121 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t121);
    mem.w32(t121, ctx.ebp);
    // 0x004dd73f: call 0x4e0cf0
    uint32_t t122 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t122);
    mem.w32(t122, 0x004dd744u);
    hle_crt_004e0cf0(ctx, mem);
    // 0x004dd744: add esp, 0xc
    uint32_t t123 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t123);
    ctx.esp = static_cast<uint32_t>(t123);
    // 0x004dd747: mov byte ptr [ebx + ebp], 0
    uint32_t t124 = static_cast<uint32_t>(ctx.ebx + ctx.ebp);
    mem.w8(t124, uint8_t{0x00u});
    goto bb_004dd74b;
}
bb_004dd734: {
    // 0x004dd734: mov ebx, 0x20
    ctx.ebx = static_cast<uint32_t>(0x00000020u);
    goto bb_004dd739;
}
}

// sub_004dd8c0 | subsystem=Sound | canonical | 10 blocks | 97 insns
void sub_004dd8c0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dd8c0: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x004dd8c1: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x004dd8c3: and esp, 0xfffffff8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xfffffff8u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x004dd8c6: push -1
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, 0xffffffffu);
    // 0x004dd8c8: push 0x516ea8
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, 0x00516ea8u);
    // 0x004dd8cd: mov eax, dword ptr fs:[0]
    uint32_t t4 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    uint32_t t5 = mem.r32(t4);
    ctx.eax = static_cast<uint32_t>(t5);
    // 0x004dd8d3: push eax
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.eax);
    // 0x004dd8d4: sub esp, 0x78
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000078u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000078u, t7);
    ctx.esp = static_cast<uint32_t>(t7);
    // 0x004dd8d7: push ebx
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.ebx);
    // 0x004dd8d8: push esi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.esi);
    // 0x004dd8d9: push edi
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, ctx.edi);
    // 0x004dd8da: mov eax, dword ptr [0x54b458]
    uint32_t t11 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x004dd8df: xor eax, esp
    uint32_t t12 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t12);
    ctx.eax = static_cast<uint32_t>(t12);
    // 0x004dd8e1: push eax
    uint32_t t13 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t13);
    mem.w32(t13, ctx.eax);
    // 0x004dd8e2: lea eax, [esp + 0x88]
    uint32_t t14 = static_cast<uint32_t>(ctx.esp + 0x00000088u);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x004dd8e9: mov dword ptr fs:[0], eax
    uint32_t t15 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t15, ctx.eax);
    // 0x004dd8ef: xor ebx, ebx
    uint32_t t16 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    ctx.ebx = static_cast<uint32_t>(t16);
    // 0x004dd8f1: lea esi, [esp + 0x28]
    uint32_t t17 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.esi = static_cast<uint32_t>(t17);
    // 0x004dd8f5: xor edi, edi
    uint32_t t18 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t18);
    ctx.edi = static_cast<uint32_t>(t18);
    // 0x004dd8f7: mov dword ptr [esp + 0x14], ebx
    uint32_t t19 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t19, ctx.ebx);
    // 0x004dd8fb: mov dword ptr [esp + 0x1c], ebx
    uint32_t t20 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t20, ctx.ebx);
    // 0x004dd8ff: mov dword ptr [esp + 0x18], ebx
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t21, ctx.ebx);
    // 0x004dd903: mov dword ptr [esp + 0x20], ebx
    uint32_t t22 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t22, ctx.ebx);
    // 0x004dd907: mov dword ptr [esp + 0x24], 0x53a660
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    mem.w32(t23, 0x0053a660u);
    // 0x004dd90f: call 0x413c60
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x004dd914u);
    sub_00413c60(ctx, mem);
    // 0x004dd914: mov dword ptr [esp + 0x90], ebx
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000090u);
    mem.w32(t25, ctx.ebx);
    // 0x004dd91b: cmp dword ptr [0x76e000], ebx
    uint32_t t26 = mem.r32(0x0076e000u);
    uint32_t t27 = static_cast<uint32_t>(t26 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t26, ctx.ebx, t27);
    // 0x004dd921: lea ecx, [esp + 0x24]
    uint32_t t28 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    ctx.ecx = static_cast<uint32_t>(t28);
    // 0x004dd925: jne 0x4dd950
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dd950;
    goto bb_004dd927;
}
bb_004dd950: {
    // 0x004dd950: mov esi, dword ptr [ebp + 8]
    uint32_t t29 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t30 = mem.r32(t29);
    ctx.esi = static_cast<uint32_t>(t30);
    // 0x004dd953: push 0x53d57c
    uint32_t t31 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t31);
    mem.w32(t31, 0x0053d57cu);
    // 0x004dd958: push esi
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, ctx.esi);
    // 0x004dd959: call 0x4a1a60
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, 0x004dd95eu);
    sub_004a1a60(ctx, mem);
    // 0x004dd95e: cmp al, 1
    uint8_t t34 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) - static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.eax), uint8_t{0x01u}, t34);
    // 0x004dd960: lea ecx, [esp + 0x24]
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    ctx.ecx = static_cast<uint32_t>(t35);
    // 0x004dd964: jne 0x4dd97c
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dd97c;
    goto bb_004dd966;
}
bb_004dd927: {
    // 0x004dd927: mov dword ptr [esp + 0x90], 0xffffffff
    uint32_t t36 = static_cast<uint32_t>(ctx.esp + 0x00000090u);
    mem.w32(t36, 0xffffffffu);
    // 0x004dd932: call 0x4a19e0
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, 0x004dd937u);
    sub_004a19e0(ctx, mem);
    // 0x004dd937: lea eax, [ebx + 1]
    uint32_t t38 = static_cast<uint32_t>(ctx.ebx + 0x00000001u);
    ctx.eax = static_cast<uint32_t>(t38);
    // 0x004dd93a: mov ecx, dword ptr [esp + 0x88]
    uint32_t t39 = static_cast<uint32_t>(ctx.esp + 0x00000088u);
    uint32_t t40 = mem.r32(t39);
    ctx.ecx = static_cast<uint32_t>(t40);
    // 0x004dd941: mov dword ptr fs:[0], ecx
    uint32_t t41 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t41, ctx.ecx);
    // 0x004dd948: pop ecx
    uint32_t t42 = ctx.esp;
    uint32_t t43 = mem.r32(t42);
    uint32_t t44 = static_cast<uint32_t>(t42 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    ctx.ecx = static_cast<uint32_t>(t43);
    // 0x004dd949: pop edi
    uint32_t t45 = ctx.esp;
    uint32_t t46 = mem.r32(t45);
    uint32_t t47 = static_cast<uint32_t>(t45 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t47);
    ctx.edi = static_cast<uint32_t>(t46);
    // 0x004dd94a: pop esi
    uint32_t t48 = ctx.esp;
    uint32_t t49 = mem.r32(t48);
    uint32_t t50 = static_cast<uint32_t>(t48 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    ctx.esi = static_cast<uint32_t>(t49);
    // 0x004dd94b: pop ebx
    uint32_t t51 = ctx.esp;
    uint32_t t52 = mem.r32(t51);
    uint32_t t53 = static_cast<uint32_t>(t51 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    ctx.ebx = static_cast<uint32_t>(t52);
    // 0x004dd94c: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x004dd94e: pop ebp
    uint32_t t54 = ctx.esp;
    uint32_t t55 = mem.r32(t54);
    uint32_t t56 = static_cast<uint32_t>(t54 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    ctx.ebp = static_cast<uint32_t>(t55);
    // 0x004dd94f: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004dd97c: {
    // 0x004dd97c: push 0x53d580
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, 0x0053d580u);
    // 0x004dd981: push esi
    uint32_t t58 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t58);
    mem.w32(t58, ctx.esi);
    // 0x004dd982: call 0x4a1a60
    uint32_t t59 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    mem.w32(t59, 0x004dd987u);
    sub_004a1a60(ctx, mem);
    // 0x004dd987: cmp al, 1
    uint8_t t60 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.eax)) - static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.eax), uint8_t{0x01u}, t60);
    // 0x004dd989: jne 0x4dd9a5
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dd9a5;
    goto bb_004dd98b;
}
bb_004dd966: {
    // 0x004dd966: lea eax, [esp + 0x14]
    uint32_t t61 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.eax = static_cast<uint32_t>(t61);
    // 0x004dd96a: push eax
    uint32_t t62 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t62);
    mem.w32(t62, ctx.eax);
    // 0x004dd96b: call 0x4a1b90
    uint32_t t63 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t63);
    mem.w32(t63, 0x004dd970u);
    sub_004a1b90(ctx, mem);
    // 0x004dd970: lea ecx, [esp + 0x14]
    uint32_t t64 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.ecx = static_cast<uint32_t>(t64);
    // 0x004dd974: push ecx
    uint32_t t65 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t65);
    mem.w32(t65, ctx.ecx);
    // 0x004dd975: call 0x40ea20
    uint32_t t66 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t66);
    mem.w32(t66, 0x004dd97au);
    sub_0040ea20(ctx, mem);
    // 0x004dd97a: jmp 0x4dd9a3
    goto bb_004dd9a3;
}
bb_004dd9a5: {
    // 0x004dd9a5: mov ecx, dword ptr [ebp + 0xc]
    uint32_t t67 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t68 = mem.r32(t67);
    ctx.ecx = static_cast<uint32_t>(t68);
    // 0x004dd9a8: add dword ptr [esp + 0x70], 1
    uint32_t t69 = static_cast<uint32_t>(ctx.esp + 0x00000070u);
    uint32_t t70 = mem.r32(t69);
    uint32_t t71 = static_cast<uint32_t>(t70 + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t70, 0x00000001u, t71);
    mem.w32(t69, t71);
    // 0x004dd9ad: mov esi, dword ptr [esp + 0x58]
    uint32_t t72 = static_cast<uint32_t>(ctx.esp + 0x00000058u);
    uint32_t t73 = mem.r32(t72);
    ctx.esi = static_cast<uint32_t>(t73);
    // 0x004dd9b1: mov dword ptr [ecx*4 + 0x76c6f8], edi
    uint32_t t74 = recomp_detail::shl<uint32_t>(ctx.ecx, 0x00000002u);
    uint32_t t75 = static_cast<uint32_t>(t74 + 0x0076c6f8u);
    mem.w32(t75, ctx.edi);
    // 0x004dd9b8: lea ecx, [esp + 0x28]
    uint32_t t76 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.ecx = static_cast<uint32_t>(t76);
    // 0x004dd9bc: call 0x414000
    uint32_t t77 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t77);
    mem.w32(t77, 0x004dd9c1u);
    sub_00414000(ctx, mem);
    // 0x004dd9c1: cmp esi, ebx
    uint32_t t78 = static_cast<uint32_t>(ctx.esi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, ctx.ebx, t78);
    // 0x004dd9c3: je 0x4dd9ce
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dd9ce;
    goto bb_004dd9c5;
}
bb_004dd98b: {
    // 0x004dd98b: lea edx, [esp + 0x14]
    uint32_t t79 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.edx = static_cast<uint32_t>(t79);
    // 0x004dd98f: push edx
    uint32_t t80 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    mem.w32(t80, ctx.edx);
    // 0x004dd990: lea ecx, [esp + 0x28]
    uint32_t t81 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.ecx = static_cast<uint32_t>(t81);
    // 0x004dd994: call 0x4a1b90
    uint32_t t82 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t82);
    mem.w32(t82, 0x004dd999u);
    sub_004a1b90(ctx, mem);
    // 0x004dd999: lea eax, [esp + 0x14]
    uint32_t t83 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.eax = static_cast<uint32_t>(t83);
    // 0x004dd99d: push eax
    uint32_t t84 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    mem.w32(t84, ctx.eax);
    // 0x004dd99e: call 0x40e890
    uint32_t t85 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t85);
    mem.w32(t85, 0x004dd9a3u);
    sub_0040e890(ctx, mem);
}
bb_004dd9a3: {
    // 0x004dd9a3: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    goto bb_004dd9a5;
}
bb_004dd9ce: {
    // 0x004dd9ce: mov eax, dword ptr [ebp + 0xc]
    uint32_t t86 = static_cast<uint32_t>(ctx.ebp + 0x0000000cu);
    uint32_t t87 = mem.r32(t86);
    ctx.eax = static_cast<uint32_t>(t87);
    // 0x004dd9d1: xor edx, edx
    uint32_t t88 = static_cast<uint32_t>(ctx.edx ^ ctx.edx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t88);
    ctx.edx = static_cast<uint32_t>(t88);
    // 0x004dd9d3: cmp dword ptr [eax*4 + 0x76c6f8], ebx
    uint32_t t89 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000002u);
    uint32_t t90 = static_cast<uint32_t>(t89 + 0x0076c6f8u);
    uint32_t t91 = mem.r32(t90);
    uint32_t t92 = static_cast<uint32_t>(t91 - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t91, ctx.ebx, t92);
    // 0x004dd9da: lea ecx, [esp + 0x24]
    uint32_t t93 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    ctx.ecx = static_cast<uint32_t>(t93);
    // 0x004dd9de: setne dl
    uint8_t t94 = static_cast<uint8_t>(recomp_detail::eval_cond(ctx, Cond::NE) ? 1u : 0u);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t94));
    // 0x004dd9e1: mov dword ptr [esp + 0x90], 0xffffffff
    uint32_t t95 = static_cast<uint32_t>(ctx.esp + 0x00000090u);
    mem.w32(t95, 0xffffffffu);
    // 0x004dd9ec: mov esi, edx
    ctx.esi = static_cast<uint32_t>(ctx.edx);
    // 0x004dd9ee: call 0x4a19e0
    uint32_t t96 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t96);
    mem.w32(t96, 0x004dd9f3u);
    sub_004a19e0(ctx, mem);
    // 0x004dd9f3: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004dd9f5: mov ecx, dword ptr [esp + 0x88]
    uint32_t t97 = static_cast<uint32_t>(ctx.esp + 0x00000088u);
    uint32_t t98 = mem.r32(t97);
    ctx.ecx = static_cast<uint32_t>(t98);
    // 0x004dd9fc: mov dword ptr fs:[0], ecx
    uint32_t t99 = static_cast<uint32_t>(ctx.fs_0 + 0x00000000u);
    mem.w32(t99, ctx.ecx);
    // 0x004dda03: pop ecx
    uint32_t t100 = ctx.esp;
    uint32_t t101 = mem.r32(t100);
    uint32_t t102 = static_cast<uint32_t>(t100 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t102);
    ctx.ecx = static_cast<uint32_t>(t101);
    // 0x004dda04: pop edi
    uint32_t t103 = ctx.esp;
    uint32_t t104 = mem.r32(t103);
    uint32_t t105 = static_cast<uint32_t>(t103 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t105);
    ctx.edi = static_cast<uint32_t>(t104);
    // 0x004dda05: pop esi
    uint32_t t106 = ctx.esp;
    uint32_t t107 = mem.r32(t106);
    uint32_t t108 = static_cast<uint32_t>(t106 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t108);
    ctx.esi = static_cast<uint32_t>(t107);
    // 0x004dda06: pop ebx
    uint32_t t109 = ctx.esp;
    uint32_t t110 = mem.r32(t109);
    uint32_t t111 = static_cast<uint32_t>(t109 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t111);
    ctx.ebx = static_cast<uint32_t>(t110);
    // 0x004dda07: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x004dda09: pop ebp
    uint32_t t112 = ctx.esp;
    uint32_t t113 = mem.r32(t112);
    uint32_t t114 = static_cast<uint32_t>(t112 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t114);
    ctx.ebp = static_cast<uint32_t>(t113);
    // 0x004dda0a: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004dd9c5: {
    // 0x004dd9c5: push esi
    uint32_t t115 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t115);
    mem.w32(t115, ctx.esi);
    // 0x004dd9c6: call 0x4e00d0
    uint32_t t116 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t116);
    mem.w32(t116, 0x004dd9cbu);
    hle_crt_004e00d0(ctx, mem);
    // 0x004dd9cb: add esp, 4
    uint32_t t117 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t117);
    ctx.esp = static_cast<uint32_t>(t117);
    goto bb_004dd9ce;
}
}

// sub_004dda10 | subsystem=Sound | canonical | 9 blocks | 68 insns
void sub_004dda10(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004dda10: sub esp, 0x130
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000130u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000130u, t0);
    ctx.esp = static_cast<uint32_t>(t0);
    // 0x004dda16: mov eax, dword ptr [0x54b458]
    uint32_t t1 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t1);
    // 0x004dda1b: xor eax, esp
    uint32_t t2 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.eax = static_cast<uint32_t>(t2);
    // 0x004dda1d: mov dword ptr [esp + 0x128], eax
    uint32_t t3 = static_cast<uint32_t>(ctx.esp + 0x00000128u);
    mem.w32(t3, ctx.eax);
    // 0x004dda24: push ebp
    uint32_t t4 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t4);
    mem.w32(t4, ctx.ebp);
    // 0x004dda25: xor ebp, ebp
    uint32_t t5 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    ctx.ebp = static_cast<uint32_t>(t5);
    // 0x004dda27: cmp dword ptr [0x76e000], ebp
    uint32_t t6 = mem.r32(0x0076e000u);
    uint32_t t7 = static_cast<uint32_t>(t6 - ctx.ebp);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t6, ctx.ebp, t7);
    // 0x004dda2d: push esi
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, ctx.esi);
    // 0x004dda2e: push edi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.edi);
    // 0x004dda2f: jne 0x4dda4b
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dda4b;
    goto bb_004dda31;
}
bb_004dda4b: {
    // 0x004dda4b: xor esi, esi
    uint32_t t10 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t10);
    ctx.esi = static_cast<uint32_t>(t10);
    // 0x004dda4d: lea ecx, [ecx]
    ctx.ecx = static_cast<uint32_t>(ctx.ecx);
    goto bb_004dda50;
}
bb_004dda31: {
    // 0x004dda31: xor eax, eax
    uint32_t t11 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t11);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x004dda33: pop edi
    uint32_t t12 = ctx.esp;
    uint32_t t13 = mem.r32(t12);
    uint32_t t14 = static_cast<uint32_t>(t12 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t14);
    ctx.edi = static_cast<uint32_t>(t13);
    // 0x004dda34: pop esi
    uint32_t t15 = ctx.esp;
    uint32_t t16 = mem.r32(t15);
    uint32_t t17 = static_cast<uint32_t>(t15 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    ctx.esi = static_cast<uint32_t>(t16);
    // 0x004dda35: pop ebp
    uint32_t t18 = ctx.esp;
    uint32_t t19 = mem.r32(t18);
    uint32_t t20 = static_cast<uint32_t>(t18 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    ctx.ebp = static_cast<uint32_t>(t19);
    // 0x004dda36: mov ecx, dword ptr [esp + 0x128]
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x00000128u);
    uint32_t t22 = mem.r32(t21);
    ctx.ecx = static_cast<uint32_t>(t22);
    // 0x004dda3d: xor ecx, esp
    uint32_t t23 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t23);
    ctx.ecx = static_cast<uint32_t>(t23);
    // 0x004dda3f: call 0x4e02f8
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x004dda44u);
    hle_crt_004e02f8(ctx, mem);
    // 0x004dda44: add esp, 0x130
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x00000130u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000130u, t25);
    ctx.esp = static_cast<uint32_t>(t25);
    // 0x004dda4a: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004dda50: {
    // 0x004dda50: mov ecx, dword ptr [esi*4 + 0x76c6f8]
    uint32_t t26 = recomp_detail::shl<uint32_t>(ctx.esi, 0x00000002u);
    uint32_t t27 = static_cast<uint32_t>(t26 + 0x0076c6f8u);
    uint32_t t28 = mem.r32(t27);
    ctx.ecx = static_cast<uint32_t>(t28);
    // 0x004dda57: test ecx, ecx
    uint32_t t29 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t29);
    // 0x004dda59: je 0x4dda6e
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dda6e;
    goto bb_004dda5b;
}
bb_004dda6e: {
    // 0x004dda6e: push esi
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, ctx.esi);
    // 0x004dda6f: lea eax, [esp + 0x14]
    uint32_t t31 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    ctx.eax = static_cast<uint32_t>(t31);
    // 0x004dda73: push 0x53d584
    uint32_t t32 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t32);
    mem.w32(t32, 0x0053d584u);
    // 0x004dda78: push eax
    uint32_t t33 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t33);
    mem.w32(t33, ctx.eax);
    // 0x004dda79: call 0x4e068b
    uint32_t t34 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t34);
    mem.w32(t34, 0x004dda7eu);
    hle_crt_004e068b(ctx, mem);
    // 0x004dda7e: lea ecx, [esp + 0x1c]
    uint32_t t35 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    ctx.ecx = static_cast<uint32_t>(t35);
    // 0x004dda82: push ecx
    uint32_t t36 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t36);
    mem.w32(t36, ctx.ecx);
    // 0x004dda83: push 0x53d58c
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, 0x0053d58cu);
    // 0x004dda88: lea edx, [esp + 0x44]
    uint32_t t38 = static_cast<uint32_t>(ctx.esp + 0x00000044u);
    ctx.edx = static_cast<uint32_t>(t38);
    // 0x004dda8c: push 0x5357d4
    uint32_t t39 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t39);
    mem.w32(t39, 0x005357d4u);
    // 0x004dda91: push edx
    uint32_t t40 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t40);
    mem.w32(t40, ctx.edx);
    // 0x004dda92: call 0x4e068b
    uint32_t t41 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    mem.w32(t41, 0x004dda97u);
    hle_crt_004e068b(ctx, mem);
    // 0x004dda97: lea eax, [esp + 0x4c]
    uint32_t t42 = static_cast<uint32_t>(ctx.esp + 0x0000004cu);
    ctx.eax = static_cast<uint32_t>(t42);
    // 0x004dda9b: push esi
    uint32_t t43 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t43);
    mem.w32(t43, ctx.esi);
    // 0x004dda9c: push eax
    uint32_t t44 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t44);
    mem.w32(t44, ctx.eax);
    // 0x004dda9d: call 0x4dd8c0
    uint32_t t45 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t45);
    mem.w32(t45, 0x004ddaa2u);
    sub_004dd8c0(ctx, mem);
    // 0x004ddaa2: add esp, 0x24
    uint32_t t46 = static_cast<uint32_t>(ctx.esp + 0x00000024u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000024u, t46);
    ctx.esp = static_cast<uint32_t>(t46);
    // 0x004ddaa5: test eax, eax
    uint32_t t47 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t47);
    // 0x004ddaa7: je 0x4ddac7
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004ddac7;
    goto bb_004ddaa9;
}
bb_004dda5b: {
    // 0x004dda5b: mov eax, dword ptr [ecx]
    uint32_t t48 = mem.r32(ctx.ecx);
    ctx.eax = static_cast<uint32_t>(t48);
    // 0x004dda5d: mov edx, dword ptr [eax]
    uint32_t t49 = mem.r32(ctx.eax);
    ctx.edx = static_cast<uint32_t>(t49);
    // 0x004dda5f: push 1
    uint32_t t50 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t50);
    mem.w32(t50, 0x00000001u);
    // 0x004dda61: call edx
    uint32_t t51 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t51);
    mem.w32(t51, 0x004dda63u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x004dda63: mov dword ptr [esi*4 + 0x76c6f8], 0
    uint32_t t52 = recomp_detail::shl<uint32_t>(ctx.esi, 0x00000002u);
    uint32_t t53 = static_cast<uint32_t>(t52 + 0x0076c6f8u);
    mem.w32(t53, 0x00000000u);
    goto bb_004dda6e;
}
bb_004ddac7: {
    // 0x004ddac7: add esi, 1
    uint32_t t54 = static_cast<uint32_t>(ctx.esi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000001u, t54);
    ctx.esi = static_cast<uint32_t>(t54);
    // 0x004ddaca: cmp esi, 0xc8
    uint32_t t55 = static_cast<uint32_t>(ctx.esi - 0x000000c8u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x000000c8u, t55);
    // 0x004ddad0: jl 0x4dda50
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004dda50;
    goto bb_004ddad6;
}
bb_004ddaa9: {
    // 0x004ddaa9: lea edi, [esp + 0x10]
    uint32_t t56 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    ctx.edi = static_cast<uint32_t>(t56);
    // 0x004ddaad: call 0x4dd560
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, 0x004ddab2u);
    sub_004dd560(ctx, mem);
    // 0x004ddab2: mov ecx, dword ptr [0x76e648]
    uint32_t t58 = mem.r32(0x0076e648u);
    ctx.ecx = static_cast<uint32_t>(t58);
    // 0x004ddab8: push 0
    uint32_t t59 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t59);
    mem.w32(t59, 0x00000000u);
    // 0x004ddaba: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004ddabc: call 0x4de100
    uint32_t t60 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t60);
    mem.w32(t60, 0x004ddac1u);
    sub_004de100(ctx, mem);
    // 0x004ddac1: add esp, 4
    uint32_t t61 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t61);
    ctx.esp = static_cast<uint32_t>(t61);
    // 0x004ddac4: add ebp, 1
    uint32_t t62 = static_cast<uint32_t>(ctx.ebp + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebp, 0x00000001u, t62);
    ctx.ebp = static_cast<uint32_t>(t62);
    goto bb_004ddac7;
}
bb_004ddad6: {
    // 0x004ddad6: mov ecx, dword ptr [esp + 0x134]
    uint32_t t63 = static_cast<uint32_t>(ctx.esp + 0x00000134u);
    uint32_t t64 = mem.r32(t63);
    ctx.ecx = static_cast<uint32_t>(t64);
    // 0x004ddadd: pop edi
    uint32_t t65 = ctx.esp;
    uint32_t t66 = mem.r32(t65);
    uint32_t t67 = static_cast<uint32_t>(t65 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t67);
    ctx.edi = static_cast<uint32_t>(t66);
    // 0x004ddade: pop esi
    uint32_t t68 = ctx.esp;
    uint32_t t69 = mem.r32(t68);
    uint32_t t70 = static_cast<uint32_t>(t68 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t70);
    ctx.esi = static_cast<uint32_t>(t69);
    // 0x004ddadf: mov eax, ebp
    ctx.eax = static_cast<uint32_t>(ctx.ebp);
    // 0x004ddae1: pop ebp
    uint32_t t71 = ctx.esp;
    uint32_t t72 = mem.r32(t71);
    uint32_t t73 = static_cast<uint32_t>(t71 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t73);
    ctx.ebp = static_cast<uint32_t>(t72);
    // 0x004ddae2: xor ecx, esp
    uint32_t t74 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t74);
    ctx.ecx = static_cast<uint32_t>(t74);
    // 0x004ddae4: call 0x4e02f8
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, 0x004ddae9u);
    hle_crt_004e02f8(ctx, mem);
    // 0x004ddae9: add esp, 0x130
    uint32_t t76 = static_cast<uint32_t>(ctx.esp + 0x00000130u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000130u, t76);
    ctx.esp = static_cast<uint32_t>(t76);
    // 0x004ddaef: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
}

// sub_004ddaf0 | subsystem=Sound | canonical | 10 blocks | 35 insns
void sub_004ddaf0(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004ddaf0: cmp dword ptr [0x76e000], 0
    uint32_t t0 = mem.r32(0x0076e000u);
    uint32_t t1 = static_cast<uint32_t>(t0 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t0, 0x00000000u, t1);
    // 0x004ddaf7: push edi
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t2);
    mem.w32(t2, ctx.edi);
    // 0x004ddaf8: je 0x4ddb6c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004ddb6c;
    goto bb_004ddafa;
}
bb_004ddb6c: {
    // 0x004ddb6c: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x004ddb71: pop edi
    uint32_t t3 = ctx.esp;
    uint32_t t4 = mem.r32(t3);
    uint32_t t5 = static_cast<uint32_t>(t3 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t5);
    ctx.edi = static_cast<uint32_t>(t4);
    // 0x004ddb72: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004ddafa: {
    // 0x004ddafa: mov ecx, dword ptr [0x76de68]
    uint32_t t6 = mem.r32(0x0076de68u);
    ctx.ecx = static_cast<uint32_t>(t6);
    // 0x004ddb00: test ecx, ecx
    uint32_t t7 = static_cast<uint32_t>(ctx.ecx & ctx.ecx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t7);
    // 0x004ddb02: je 0x4ddb16
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004ddb16;
    goto bb_004ddb04;
}
bb_004ddb16: {
    // 0x004ddb16: push 0x5dc
    uint32_t t8 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    mem.w32(t8, 0x000005dcu);
    // 0x004ddb1b: push 0x76e850
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, 0x0076e850u);
    // 0x004ddb20: call 0x4dd8c0
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x004ddb25u);
    sub_004dd8c0(ctx, mem);
    // 0x004ddb25: mov eax, dword ptr [0x554140]
    uint32_t t11 = mem.r32(0x00554140u);
    ctx.eax = static_cast<uint32_t>(t11);
    // 0x004ddb2a: add esp, 8
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x00000008u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000008u, t12);
    ctx.esp = static_cast<uint32_t>(t12);
    // 0x004ddb2d: test eax, eax
    uint32_t t13 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t13);
    // 0x004ddb2f: je 0x4ddb3a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004ddb3a;
    goto bb_004ddb31;
}
bb_004ddb04: {
    // 0x004ddb04: mov eax, dword ptr [ecx]
    uint32_t t14 = mem.r32(ctx.ecx);
    ctx.eax = static_cast<uint32_t>(t14);
    // 0x004ddb06: mov edx, dword ptr [eax]
    uint32_t t15 = mem.r32(ctx.eax);
    ctx.edx = static_cast<uint32_t>(t15);
    // 0x004ddb08: push 1
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x00000001u);
    // 0x004ddb0a: call edx
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x004ddb0cu);
    call_indirect(ctx, mem, ctx.edx);
    // 0x004ddb0c: mov dword ptr [0x76de68], 0
    mem.w32(0x0076de68u, 0x00000000u);
    goto bb_004ddb16;
}
bb_004ddb3a: {
    // 0x004ddb3a: cmp dword ptr [0x55df14], 0
    uint32_t t18 = mem.r32(0x0055df14u);
    uint32_t t19 = static_cast<uint32_t>(t18 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t18, 0x00000000u, t19);
    // 0x004ddb41: mov ecx, 0xffffd8f0
    ctx.ecx = static_cast<uint32_t>(0xffffd8f0u);
    // 0x004ddb46: jne 0x4ddb4e
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004ddb4e;
    goto bb_004ddb48;
}
bb_004ddb31: {
    // 0x004ddb31: cmp dword ptr [eax + 0x150], 0
    uint32_t t20 = static_cast<uint32_t>(ctx.eax + 0x00000150u);
    uint32_t t21 = mem.r32(t20);
    uint32_t t22 = static_cast<uint32_t>(t21 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t21, 0x00000000u, t22);
    // 0x004ddb38: jne 0x4ddb48
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004ddb48;
    goto bb_004ddb3a;
}
bb_004ddb4e: {
    // 0x004ddb4e: push 0
    uint32_t t23 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t23);
    mem.w32(t23, 0x00000000u);
    // 0x004ddb50: mov eax, 0x5dc
    ctx.eax = static_cast<uint32_t>(0x000005dcu);
    // 0x004ddb55: call 0x4de100
    uint32_t t24 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    mem.w32(t24, 0x004ddb5au);
    sub_004de100(ctx, mem);
    // 0x004ddb5a: mov edi, dword ptr [0x76de68]
    uint32_t t25 = mem.r32(0x0076de68u);
    ctx.edi = static_cast<uint32_t>(t25);
    // 0x004ddb60: add esp, 4
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t26);
    ctx.esp = static_cast<uint32_t>(t26);
    // 0x004ddb63: test edi, edi
    uint32_t t27 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t27);
    // 0x004ddb65: je 0x4ddb6c
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004ddb6c;
    goto bb_004ddb67;
}
bb_004ddb48: {
    // 0x004ddb48: mov ecx, dword ptr [0x76e648]
    uint32_t t28 = mem.r32(0x0076e648u);
    ctx.ecx = static_cast<uint32_t>(t28);
    goto bb_004ddb4e;
}
bb_004ddb67: {
    // 0x004ddb67: call 0x40f3a0
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x004ddb6cu);
    sub_0040f3a0(ctx, mem);
    goto bb_004ddb6c;
}
}

// sub_004ddc40 | subsystem=Sound | canonical | 34 blocks | 196 insns
void sub_004ddc40(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004ddc40: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x004ddc41: mov ebp, esp
    ctx.ebp = static_cast<uint32_t>(ctx.esp);
    // 0x004ddc43: and esp, 0xfffffff8
    uint32_t t1 = static_cast<uint32_t>(ctx.esp & 0xfffffff8u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t1);
    ctx.esp = static_cast<uint32_t>(t1);
    // 0x004ddc46: sub esp, 0x124
    uint32_t t2 = static_cast<uint32_t>(ctx.esp - 0x00000124u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esp, 0x00000124u, t2);
    ctx.esp = static_cast<uint32_t>(t2);
    // 0x004ddc4c: mov eax, dword ptr [0x54b458]
    uint32_t t3 = mem.r32(0x0054b458u);
    ctx.eax = static_cast<uint32_t>(t3);
    // 0x004ddc51: xor eax, esp
    uint32_t t4 = static_cast<uint32_t>(ctx.eax ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    ctx.eax = static_cast<uint32_t>(t4);
    // 0x004ddc53: mov dword ptr [esp + 0x120], eax
    uint32_t t5 = static_cast<uint32_t>(ctx.esp + 0x00000120u);
    mem.w32(t5, ctx.eax);
    // 0x004ddc5a: push ebx
    uint32_t t6 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t6);
    mem.w32(t6, ctx.ebx);
    // 0x004ddc5b: push esi
    uint32_t t7 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t7);
    mem.w32(t7, ctx.esi);
    // 0x004ddc5c: xor ebx, ebx
    uint32_t t8 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t8);
    ctx.ebx = static_cast<uint32_t>(t8);
    // 0x004ddc5e: push edi
    uint32_t t9 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t9);
    mem.w32(t9, ctx.edi);
    // 0x004ddc5f: mov dword ptr [0x76e838], ebx
    mem.w32(0x0076e838u, ctx.ebx);
    // 0x004ddc65: mov dword ptr [0x76e83c], ebx
    mem.w32(0x0076e83cu, ctx.ebx);
    // 0x004ddc6b: call 0x4ddf40
    uint32_t t10 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t10);
    mem.w32(t10, 0x004ddc70u);
    sub_004ddf40(ctx, mem);
    // 0x004ddc70: mov ecx, dword ptr [0x76dff8]
    uint32_t t11 = mem.r32(0x0076dff8u);
    ctx.ecx = static_cast<uint32_t>(t11);
    // 0x004ddc76: cmp ecx, ebx
    uint32_t t12 = static_cast<uint32_t>(ctx.ecx - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, ctx.ebx, t12);
    // 0x004ddc78: je 0x4ddc88
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004ddc88;
    goto bb_004ddc7a;
}
bb_004ddc88: {
    // 0x004ddc88: mov eax, dword ptr [0x53d59c]
    uint32_t t13 = mem.r32(0x0053d59cu);
    ctx.eax = static_cast<uint32_t>(t13);
    // 0x004ddc8d: mov cx, word ptr [0x53d5a0]
    uint16_t t14 = mem.r16(0x0053d5a0u);
    recomp_detail::w16(ctx.ecx, static_cast<uint16_t>(t14));
    // 0x004ddc94: mov dl, byte ptr [0x53d5a2]
    uint8_t t15 = mem.r8(0x0053d5a2u);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t15));
    // 0x004ddc9a: mov dword ptr [esp + 0x28], eax
    uint32_t t16 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t16, ctx.eax);
    // 0x004ddc9e: mov eax, dword ptr [ebp + 8]
    uint32_t t17 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t18 = mem.r32(t17);
    ctx.eax = static_cast<uint32_t>(t18);
    // 0x004ddca1: lea eax, [eax + eax*2]
    uint32_t t19 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000001u);
    uint32_t t20 = static_cast<uint32_t>(ctx.eax + t19);
    ctx.eax = static_cast<uint32_t>(t20);
    // 0x004ddca4: shl eax, 4
    uint32_t t21 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x04u}) & 0x0000001fu);
    uint32_t t22 = recomp_detail::shl<uint32_t>(ctx.eax, t21);
    recomp_detail::update_flags_shl<uint32_t>(ctx, ctx.eax, t21, t22);
    ctx.eax = static_cast<uint32_t>(t22);
    // 0x004ddca7: mov dword ptr [esp + 0x14], eax
    uint32_t t23 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    mem.w32(t23, ctx.eax);
    // 0x004ddcab: lea eax, [eax + 0x768ba0]
    uint32_t t24 = static_cast<uint32_t>(ctx.eax + 0x00768ba0u);
    ctx.eax = static_cast<uint32_t>(t24);
    // 0x004ddcb1: mov word ptr [esp + 0x2c], cx
    uint32_t t25 = static_cast<uint32_t>(ctx.esp + 0x0000002cu);
    mem.w16(t25, recomp_detail::r16(ctx.ecx));
    // 0x004ddcb6: mov byte ptr [esp + 0x2e], dl
    uint32_t t26 = static_cast<uint32_t>(ctx.esp + 0x0000002eu);
    mem.w8(t26, recomp_detail::r8l(ctx.edx));
    // 0x004ddcba: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x004ddcbc: lea esp, [esp]
    ctx.esp = static_cast<uint32_t>(ctx.esp);
    goto bb_004ddcc0;
}
bb_004ddc7a: {
    // 0x004ddc7a: mov eax, dword ptr [ecx]
    uint32_t t27 = mem.r32(ctx.ecx);
    ctx.eax = static_cast<uint32_t>(t27);
    // 0x004ddc7c: mov edx, dword ptr [eax]
    uint32_t t28 = mem.r32(ctx.eax);
    ctx.edx = static_cast<uint32_t>(t28);
    // 0x004ddc7e: push 1
    uint32_t t29 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t29);
    mem.w32(t29, 0x00000001u);
    // 0x004ddc80: call edx
    uint32_t t30 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    mem.w32(t30, 0x004ddc82u);
    call_indirect(ctx, mem, ctx.edx);
    // 0x004ddc82: mov dword ptr [0x76dff8], ebx
    mem.w32(0x0076dff8u, ctx.ebx);
    goto bb_004ddc88;
}
bb_004ddcc0: {
    // 0x004ddcc0: mov dl, byte ptr [eax]
    uint8_t t31 = mem.r8(ctx.eax);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t31));
    // 0x004ddcc2: add eax, 1
    uint32_t t32 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t32);
    ctx.eax = static_cast<uint32_t>(t32);
    // 0x004ddcc5: cmp dl, bl
    uint8_t t33 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.edx)) - static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.edx), recomp_detail::r8l(ctx.ebx), t33);
    // 0x004ddcc7: jne 0x4ddcc0
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004ddcc0;
}
{
    // 0x004ddcc9: lea edi, [esp + 0x28]
    uint32_t t34 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.edi = static_cast<uint32_t>(t34);
    // 0x004ddccd: sub eax, ecx
    uint32_t t35 = static_cast<uint32_t>(ctx.eax - ctx.ecx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ecx, t35);
    ctx.eax = static_cast<uint32_t>(t35);
    // 0x004ddccf: mov esi, ecx
    ctx.esi = static_cast<uint32_t>(ctx.ecx);
    // 0x004ddcd1: add edi, -1
    uint32_t t36 = static_cast<uint32_t>(ctx.edi + 0xffffffffu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0xffffffffu, t36);
    ctx.edi = static_cast<uint32_t>(t36);
}
bb_004ddcd4: {
    // 0x004ddcd4: mov cl, byte ptr [edi + 1]
    uint32_t t37 = static_cast<uint32_t>(ctx.edi + 0x00000001u);
    uint8_t t38 = mem.r8(t37);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t38));
    // 0x004ddcd7: add edi, 1
    uint32_t t39 = static_cast<uint32_t>(ctx.edi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.edi, 0x00000001u, t39);
    ctx.edi = static_cast<uint32_t>(t39);
    // 0x004ddcda: cmp cl, bl
    uint8_t t40 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) - static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.ecx), recomp_detail::r8l(ctx.ebx), t40);
    // 0x004ddcdc: jne 0x4ddcd4
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004ddcd4;
}
{
    // 0x004ddcde: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x004ddce0: shr ecx, 2
    uint32_t t41 = static_cast<uint32_t>(static_cast<uint32_t>(uint8_t{0x02u}) & 0x0000001fu);
    uint32_t t42 = recomp_detail::shr<uint32_t>(ctx.ecx, t41);
    recomp_detail::update_flags_shr<uint32_t>(ctx, ctx.ecx, t41, t42);
    ctx.ecx = static_cast<uint32_t>(t42);
    // 0x004ddce3: rep movsd dword ptr es:[edi], dword ptr [esi]
    recomp_detail::exec_string_op<uint32_t>(ctx, mem, 0, 1);
    // 0x004ddce5: mov ecx, eax
    ctx.ecx = static_cast<uint32_t>(ctx.eax);
    // 0x004ddce7: mov eax, dword ptr [0x54c7a0]
    uint32_t t43 = mem.r32(0x0054c7a0u);
    ctx.eax = static_cast<uint32_t>(t43);
    // 0x004ddcec: and ecx, 3
    uint32_t t44 = static_cast<uint32_t>(ctx.ecx & 0x00000003u);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t44);
    ctx.ecx = static_cast<uint32_t>(t44);
    // 0x004ddcef: sub eax, 1
    uint32_t t45 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t45);
    ctx.eax = static_cast<uint32_t>(t45);
    // 0x004ddcf2: rep movsb byte ptr es:[edi], byte ptr [esi]
    recomp_detail::exec_string_op<uint8_t>(ctx, mem, 0, 1);
    // 0x004ddcf4: je 0x4ddd1a
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004ddd1a;
    goto bb_004ddcf6;
}
bb_004ddd1a: {
    // 0x004ddd1a: lea eax, [esp + 0x28]
    uint32_t t46 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.eax = static_cast<uint32_t>(t46);
    // 0x004ddd1e: add eax, -1
    uint32_t t47 = static_cast<uint32_t>(ctx.eax + 0xffffffffu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0xffffffffu, t47);
    ctx.eax = static_cast<uint32_t>(t47);
    goto bb_004ddd21;
}
bb_004ddcf6: {
    // 0x004ddcf6: sub eax, 1
    uint32_t t48 = static_cast<uint32_t>(ctx.eax - 0x00000001u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0x00000001u, t48);
    ctx.eax = static_cast<uint32_t>(t48);
    // 0x004ddcf9: jne 0x4ddd3c
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004ddd3c;
    goto bb_004ddcfb;
}
bb_004ddd21: {
    // 0x004ddd21: mov cl, byte ptr [eax + 1]
    uint32_t t49 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    uint8_t t50 = mem.r8(t49);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t50));
    // 0x004ddd24: add eax, 1
    uint32_t t51 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t51);
    ctx.eax = static_cast<uint32_t>(t51);
    // 0x004ddd27: cmp cl, bl
    uint8_t t52 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) - static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.ecx), recomp_detail::r8l(ctx.ebx), t52);
    // 0x004ddd29: jne 0x4ddd21
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004ddd21;
    goto bb_004ddd2b;
}
bb_004ddd3c: {
    // 0x004ddd3c: push 0x292
    uint32_t t53 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t53);
    mem.w32(t53, 0x00000292u);
    // 0x004ddd41: push 0x53d5b4
    uint32_t t54 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t54);
    mem.w32(t54, 0x0053d5b4u);
    // 0x004ddd46: push 4
    uint32_t t55 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t55);
    mem.w32(t55, 0x00000004u);
    // 0x004ddd48: push 0x5c
    uint32_t t56 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t56);
    mem.w32(t56, 0x0000005cu);
    // 0x004ddd4a: call 0x4e0675
    uint32_t t57 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t57);
    mem.w32(t57, 0x004ddd4fu);
    hle_crt_004e0675(ctx, mem);
    // 0x004ddd4f: add esp, 0x10
    uint32_t t58 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000010u, t58);
    ctx.esp = static_cast<uint32_t>(t58);
    // 0x004ddd52: cmp eax, ebx
    uint32_t t59 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t59);
    // 0x004ddd54: je 0x4ddd65
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004ddd65;
    goto bb_004ddd56;
}
bb_004ddcfb: {
    // 0x004ddcfb: lea eax, [esp + 0x28]
    uint32_t t60 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.eax = static_cast<uint32_t>(t60);
    // 0x004ddcff: add eax, -1
    uint32_t t61 = static_cast<uint32_t>(ctx.eax + 0xffffffffu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0xffffffffu, t61);
    ctx.eax = static_cast<uint32_t>(t61);
    goto bb_004ddd02;
}
bb_004ddd2b: {
    // 0x004ddd2b: mov ecx, dword ptr [0x53d5a4]
    uint32_t t62 = mem.r32(0x0053d5a4u);
    ctx.ecx = static_cast<uint32_t>(t62);
    // 0x004ddd31: mov dl, byte ptr [0x53d5a8]
    uint8_t t63 = mem.r8(0x0053d5a8u);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t63));
    goto bb_004ddd37;
}
bb_004ddd65: {
    // 0x004ddd65: mov dword ptr [esp + 0x10], ebx
    uint32_t t64 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t64, ctx.ebx);
    // 0x004ddd69: mov edi, ebx
    ctx.edi = static_cast<uint32_t>(ctx.ebx);
    goto bb_004ddd6b;
}
bb_004ddd56: {
    // 0x004ddd56: mov esi, eax
    ctx.esi = static_cast<uint32_t>(ctx.eax);
    // 0x004ddd58: call 0x413c60
    uint32_t t65 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t65);
    mem.w32(t65, 0x004ddd5du);
    sub_00413c60(ctx, mem);
    // 0x004ddd5d: mov edi, eax
    ctx.edi = static_cast<uint32_t>(ctx.eax);
    // 0x004ddd5f: mov dword ptr [esp + 0x10], edi
    uint32_t t66 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    mem.w32(t66, ctx.edi);
    // 0x004ddd63: jmp 0x4ddd6b
    goto bb_004ddd6b;
}
bb_004ddd02: {
    // 0x004ddd02: mov cl, byte ptr [eax + 1]
    uint32_t t67 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    uint8_t t68 = mem.r8(t67);
    recomp_detail::w8l(ctx.ecx, static_cast<uint8_t>(t68));
    // 0x004ddd05: add eax, 1
    uint32_t t69 = static_cast<uint32_t>(ctx.eax + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.eax, 0x00000001u, t69);
    ctx.eax = static_cast<uint32_t>(t69);
    // 0x004ddd08: cmp cl, bl
    uint8_t t70 = static_cast<uint8_t>(static_cast<uint32_t>(recomp_detail::r8l(ctx.ecx)) - static_cast<uint32_t>(recomp_detail::r8l(ctx.ebx)));
    recomp_detail::update_flags_sub<uint8_t>(ctx, recomp_detail::r8l(ctx.ecx), recomp_detail::r8l(ctx.ebx), t70);
    // 0x004ddd0a: jne 0x4ddd02
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004ddd02;
    goto bb_004ddd0c;
}
bb_004ddd37: {
    // 0x004ddd37: mov dword ptr [eax], ecx
    mem.w32(ctx.eax, ctx.ecx);
    // 0x004ddd39: mov byte ptr [eax + 4], dl
    uint32_t t71 = static_cast<uint32_t>(ctx.eax + 0x00000004u);
    mem.w8(t71, recomp_detail::r8l(ctx.edx));
    goto bb_004ddd3c;
}
bb_004ddd6b: {
    // 0x004ddd6b: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004ddd6d: call 0x414000
    uint32_t t72 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t72);
    mem.w32(t72, 0x004ddd72u);
    sub_00414000(ctx, mem);
    // 0x004ddd72: lea eax, [esp + 0x28]
    uint32_t t73 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    ctx.eax = static_cast<uint32_t>(t73);
    // 0x004ddd76: push eax
    uint32_t t74 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t74);
    mem.w32(t74, ctx.eax);
    // 0x004ddd77: mov esi, 0x76e9c4
    ctx.esi = static_cast<uint32_t>(0x0076e9c4u);
    // 0x004ddd7c: call 0x4db8e0
    uint32_t t75 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t75);
    mem.w32(t75, 0x004ddd81u);
    sub_004db8e0(ctx, mem);
    // 0x004ddd81: cmp eax, ebx
    uint32_t t76 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t76);
    // 0x004ddd83: je 0x4ddd93
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004ddd93;
    goto bb_004ddd85;
}
bb_004ddd0c: {
    // 0x004ddd0c: mov ecx, dword ptr [0x53d5ac]
    uint32_t t77 = mem.r32(0x0053d5acu);
    ctx.ecx = static_cast<uint32_t>(t77);
    // 0x004ddd12: mov dl, byte ptr [0x53d5b0]
    uint8_t t78 = mem.r8(0x0053d5b0u);
    recomp_detail::w8l(ctx.edx, static_cast<uint8_t>(t78));
    // 0x004ddd18: jmp 0x4ddd37
    goto bb_004ddd37;
}
bb_004ddd93: {
    // 0x004ddd93: push ebx
    uint32_t t79 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t79);
    mem.w32(t79, ctx.ebx);
    // 0x004ddd94: push 0x10000080
    uint32_t t80 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t80);
    mem.w32(t80, 0x10000080u);
    // 0x004ddd99: push 3
    uint32_t t81 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t81);
    mem.w32(t81, 0x00000003u);
    // 0x004ddd9b: push ebx
    uint32_t t82 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t82);
    mem.w32(t82, ctx.ebx);
    // 0x004ddd9c: push 1
    uint32_t t83 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t83);
    mem.w32(t83, 0x00000001u);
    // 0x004ddd9e: push 0x80000000
    uint32_t t84 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t84);
    mem.w32(t84, 0x80000000u);
    // 0x004ddda3: lea ecx, [esp + 0x40]
    uint32_t t85 = static_cast<uint32_t>(ctx.esp + 0x00000040u);
    ctx.ecx = static_cast<uint32_t>(t85);
    // 0x004ddda7: push ecx
    uint32_t t86 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t86);
    mem.w32(t86, ctx.ecx);
    // 0x004ddda8: call dword ptr [0x51b054]
    uint32_t t87 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t87);
    mem.w32(t87, 0x004dddaeu);
    hle_iat_call(ctx, mem, 0x0051b054u);
    // 0x004dddae: cmp eax, -1
    uint32_t t88 = static_cast<uint32_t>(ctx.eax - 0xffffffffu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, 0xffffffffu, t88);
    // 0x004dddb1: je 0x4dde25
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dde25;
    goto bb_004dddb3;
}
bb_004ddd85: {
    // 0x004ddd85: mov dword ptr [edi], ebx
    mem.w32(ctx.edi, ctx.ebx);
    // 0x004ddd87: mov dword ptr [edi + 0x1c], 3
    uint32_t t89 = static_cast<uint32_t>(ctx.edi + 0x0000001cu);
    mem.w32(t89, 0x00000003u);
    // 0x004ddd8e: mov dword ptr [edi + 0x58], eax
    uint32_t t90 = static_cast<uint32_t>(ctx.edi + 0x00000058u);
    mem.w32(t90, ctx.eax);
    // 0x004ddd91: jmp 0x4dddb8
    goto bb_004dddb8;
}
bb_004dde25: {
    // 0x004dde25: mov eax, dword ptr [0x76dff8]
    uint32_t t91 = mem.r32(0x0076dff8u);
    ctx.eax = static_cast<uint32_t>(t91);
    goto bb_004dde2a;
}
bb_004dddb3: {
    // 0x004dddb3: mov dword ptr [edi], eax
    mem.w32(ctx.edi, ctx.eax);
    // 0x004dddb5: mov dword ptr [edi + 0x1c], ebx
    uint32_t t92 = static_cast<uint32_t>(ctx.edi + 0x0000001cu);
    mem.w32(t92, ctx.ebx);
}
bb_004dddb8: {
    // 0x004dddb8: mov esi, dword ptr [esp + 0x10]
    uint32_t t93 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t94 = mem.r32(t93);
    ctx.esi = static_cast<uint32_t>(t94);
    // 0x004dddbc: xor eax, eax
    uint32_t t95 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t95);
    ctx.eax = static_cast<uint32_t>(t95);
    // 0x004dddbe: mov dword ptr [edi + 8], eax
    uint32_t t96 = static_cast<uint32_t>(ctx.edi + 0x00000008u);
    mem.w32(t96, ctx.eax);
    // 0x004dddc1: mov dword ptr [edi + 0xc], eax
    uint32_t t97 = static_cast<uint32_t>(ctx.edi + 0x0000000cu);
    mem.w32(t97, ctx.eax);
    // 0x004dddc4: mov dword ptr [edi + 0x10], eax
    uint32_t t98 = static_cast<uint32_t>(ctx.edi + 0x00000010u);
    mem.w32(t98, ctx.eax);
    // 0x004dddc7: mov dword ptr [edi + 0x14], eax
    uint32_t t99 = static_cast<uint32_t>(ctx.edi + 0x00000014u);
    mem.w32(t99, ctx.eax);
    // 0x004dddca: mov dword ptr [edi + 0x18], eax
    uint32_t t100 = static_cast<uint32_t>(ctx.edi + 0x00000018u);
    mem.w32(t100, ctx.eax);
    // 0x004dddcd: push ebx
    uint32_t t101 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t101);
    mem.w32(t101, ctx.ebx);
    // 0x004dddce: xor edi, edi
    uint32_t t102 = static_cast<uint32_t>(ctx.edi ^ ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t102);
    ctx.edi = static_cast<uint32_t>(t102);
    // 0x004dddd0: xor ebx, ebx
    uint32_t t103 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t103);
    ctx.ebx = static_cast<uint32_t>(t103);
    // 0x004dddd2: mov eax, esi
    ctx.eax = static_cast<uint32_t>(ctx.esi);
    // 0x004dddd4: call 0x413e70
    uint32_t t104 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t104);
    mem.w32(t104, 0x004dddd9u);
    sub_00413e70(ctx, mem);
    // 0x004dddd9: test eax, eax
    uint32_t t105 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t105);
    // 0x004ddddb: je 0x4dddee
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dddee;
    goto bb_004ddddd;
}
bb_004dde2a: {
    // 0x004dde2a: cmp edi, ebx
    uint32_t t106 = static_cast<uint32_t>(ctx.edi - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.edi, ctx.ebx, t106);
    // 0x004dde2c: je 0x4dde43
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dde43;
    goto bb_004dde2e;
}
bb_004dddee: {
    // 0x004dddee: mov edx, dword ptr [esi + 0x30]
    uint32_t t107 = static_cast<uint32_t>(ctx.esi + 0x00000030u);
    uint32_t t108 = mem.r32(t107);
    ctx.edx = static_cast<uint32_t>(t108);
    // 0x004dddf1: add dword ptr [esi + 0x48], 1
    uint32_t t109 = static_cast<uint32_t>(ctx.esi + 0x00000048u);
    uint32_t t110 = mem.r32(t109);
    uint32_t t111 = static_cast<uint32_t>(t110 + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, t110, 0x00000001u, t111);
    mem.w32(t109, t111);
    // 0x004dddf5: mov dword ptr [esp + 0x18], edx
    uint32_t t112 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    mem.w32(t112, ctx.edx);
    // 0x004dddf9: mov dword ptr [esp + 0x1c], ebx
    uint32_t t113 = static_cast<uint32_t>(ctx.esp + 0x0000001cu);
    mem.w32(t113, ctx.ebx);
    // 0x004dddfd: call 0x413db0
    uint32_t t114 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t114);
    mem.w32(t114, 0x004dde02u);
    sub_00413db0(ctx, mem);
    // 0x004dde02: mov dword ptr [esp + 0x20], eax
    uint32_t t115 = static_cast<uint32_t>(ctx.esp + 0x00000020u);
    mem.w32(t115, ctx.eax);
    // 0x004dde06: lea eax, [esp + 0x18]
    uint32_t t116 = static_cast<uint32_t>(ctx.esp + 0x00000018u);
    ctx.eax = static_cast<uint32_t>(t116);
    // 0x004dde0a: push eax
    uint32_t t117 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t117);
    mem.w32(t117, ctx.eax);
    // 0x004dde0b: mov dword ptr [esp + 0x28], 0x401da0
    uint32_t t118 = static_cast<uint32_t>(ctx.esp + 0x00000028u);
    mem.w32(t118, 0x00401da0u);
    // 0x004dde13: call 0x40f070
    uint32_t t119 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t119);
    mem.w32(t119, 0x004dde18u);
    sub_0040f070(ctx, mem);
    // 0x004dde18: mov edi, dword ptr [esp + 0x10]
    uint32_t t120 = static_cast<uint32_t>(ctx.esp + 0x00000010u);
    uint32_t t121 = mem.r32(t120);
    ctx.edi = static_cast<uint32_t>(t121);
    // 0x004dde1c: mov dword ptr [0x76dff8], eax
    mem.w32(0x0076dff8u, ctx.eax);
    // 0x004dde21: xor ebx, ebx
    uint32_t t122 = static_cast<uint32_t>(ctx.ebx ^ ctx.ebx);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t122);
    ctx.ebx = static_cast<uint32_t>(t122);
    // 0x004dde23: jmp 0x4dde2a
    goto bb_004dde2a;
}
bb_004ddddd: {
    // 0x004ddddd: mov eax, dword ptr [esi + 0x3c]
    uint32_t t123 = static_cast<uint32_t>(ctx.esi + 0x0000003cu);
    uint32_t t124 = mem.r32(t123);
    ctx.eax = static_cast<uint32_t>(t124);
    // 0x004ddde0: test eax, eax
    uint32_t t125 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t125);
    // 0x004ddde2: je 0x4dddee
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004dddee;
    goto bb_004ddde4;
}
bb_004dde43: {
    // 0x004dde43: cmp eax, ebx
    uint32_t t126 = static_cast<uint32_t>(ctx.eax - ctx.ebx);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.eax, ctx.ebx, t126);
    // 0x004dde45: jne 0x4dde5e
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dde5e;
    goto bb_004dde47;
}
bb_004dde2e: {
    // 0x004dde2e: mov ecx, edi
    ctx.ecx = static_cast<uint32_t>(ctx.edi);
    // 0x004dde30: call 0x414000
    uint32_t t127 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t127);
    mem.w32(t127, 0x004dde35u);
    sub_00414000(ctx, mem);
    // 0x004dde35: push edi
    uint32_t t128 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t128);
    mem.w32(t128, ctx.edi);
    // 0x004dde36: call 0x4e02f3
    uint32_t t129 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t129);
    mem.w32(t129, 0x004dde3bu);
    hle_crt_004e02f3(ctx, mem);
    // 0x004dde3b: mov eax, dword ptr [0x76dff8]
    uint32_t t130 = mem.r32(0x0076dff8u);
    ctx.eax = static_cast<uint32_t>(t130);
    // 0x004dde40: add esp, 4
    uint32_t t131 = static_cast<uint32_t>(ctx.esp + 0x00000004u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x00000004u, t131);
    ctx.esp = static_cast<uint32_t>(t131);
    goto bb_004dde43;
}
bb_004ddde4: {
    // 0x004ddde4: push ebx
    uint32_t t132 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t132);
    mem.w32(t132, ctx.ebx);
    // 0x004ddde5: push -1
    uint32_t t133 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t133);
    mem.w32(t133, 0xffffffffu);
    // 0x004ddde7: push eax
    uint32_t t134 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t134);
    mem.w32(t134, ctx.eax);
    // 0x004ddde8: call dword ptr [0x51b1c4]
    uint32_t t135 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t135);
    mem.w32(t135, 0x004dddeeu);
    hle_iat_call(ctx, mem, 0x0051b1c4u);
    goto bb_004dddee;
}
bb_004dde5e: {
    // 0x004dde5e: mov ecx, dword ptr [eax + 0x54]
    uint32_t t136 = static_cast<uint32_t>(ctx.eax + 0x00000054u);
    uint32_t t137 = mem.r32(t136);
    ctx.ecx = static_cast<uint32_t>(t137);
    // 0x004dde61: sub ecx, 2
    uint32_t t138 = static_cast<uint32_t>(ctx.ecx - 0x00000002u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.ecx, 0x00000002u, t138);
    ctx.ecx = static_cast<uint32_t>(t138);
    // 0x004dde64: mov edx, dword ptr [esp + 0x14]
    uint32_t t139 = static_cast<uint32_t>(ctx.esp + 0x00000014u);
    uint32_t t140 = mem.r32(t139);
    ctx.edx = static_cast<uint32_t>(t140);
    // 0x004dde68: fld qword ptr [edx + 0x768b98]
    uint32_t t141 = static_cast<uint32_t>(ctx.edx + 0x00768b98u);
    double t142 = mem.rf64(t141);
    ctx.fpu_push(t142);
    // 0x004dde6e: jne 0x4dde79
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004dde79;
    goto bb_004dde70;
}
bb_004dde47: {
    // 0x004dde47: xor eax, eax
    uint32_t t143 = static_cast<uint32_t>(ctx.eax ^ ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t143);
    ctx.eax = static_cast<uint32_t>(t143);
    // 0x004dde49: pop edi
    uint32_t t144 = ctx.esp;
    uint32_t t145 = mem.r32(t144);
    uint32_t t146 = static_cast<uint32_t>(t144 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t146);
    ctx.edi = static_cast<uint32_t>(t145);
    // 0x004dde4a: pop esi
    uint32_t t147 = ctx.esp;
    uint32_t t148 = mem.r32(t147);
    uint32_t t149 = static_cast<uint32_t>(t147 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t149);
    ctx.esi = static_cast<uint32_t>(t148);
    // 0x004dde4b: pop ebx
    uint32_t t150 = ctx.esp;
    uint32_t t151 = mem.r32(t150);
    uint32_t t152 = static_cast<uint32_t>(t150 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t152);
    ctx.ebx = static_cast<uint32_t>(t151);
    // 0x004dde4c: mov ecx, dword ptr [esp + 0x120]
    uint32_t t153 = static_cast<uint32_t>(ctx.esp + 0x00000120u);
    uint32_t t154 = mem.r32(t153);
    ctx.ecx = static_cast<uint32_t>(t154);
    // 0x004dde53: xor ecx, esp
    uint32_t t155 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t155);
    ctx.ecx = static_cast<uint32_t>(t155);
    // 0x004dde55: call 0x4e02f8
    uint32_t t156 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t156);
    mem.w32(t156, 0x004dde5au);
    hle_crt_004e02f8(ctx, mem);
    // 0x004dde5a: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x004dde5c: pop ebp
    uint32_t t157 = ctx.esp;
    uint32_t t158 = mem.r32(t157);
    uint32_t t159 = static_cast<uint32_t>(t157 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t159);
    ctx.ebp = static_cast<uint32_t>(t158);
    // 0x004dde5d: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004dde79: {
    // 0x004dde79: mov ecx, dword ptr [ebp + 8]
    uint32_t t160 = static_cast<uint32_t>(ctx.ebp + 0x00000008u);
    uint32_t t161 = mem.r32(t160);
    ctx.ecx = static_cast<uint32_t>(t161);
    // 0x004dde7c: fstp qword ptr [eax + 0x88]
    double t162 = ctx.fpu_st(0);
    uint32_t t163 = static_cast<uint32_t>(ctx.eax + 0x00000088u);
    mem.wf64(t163, t162);
    ctx.fpu_pop();
    // 0x004dde82: mov edx, dword ptr [edx + 0x768b94]
    uint32_t t164 = static_cast<uint32_t>(ctx.edx + 0x00768b94u);
    uint32_t t165 = mem.r32(t164);
    ctx.edx = static_cast<uint32_t>(t165);
    // 0x004dde88: pop edi
    uint32_t t166 = ctx.esp;
    uint32_t t167 = mem.r32(t166);
    uint32_t t168 = static_cast<uint32_t>(t166 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t168);
    ctx.edi = static_cast<uint32_t>(t167);
    // 0x004dde89: mov dword ptr [0x76c0b0], ecx
    mem.w32(0x0076c0b0u, ctx.ecx);
    // 0x004dde8f: mov ecx, dword ptr [esp + 0x128]
    uint32_t t169 = static_cast<uint32_t>(ctx.esp + 0x00000128u);
    uint32_t t170 = mem.r32(t169);
    ctx.ecx = static_cast<uint32_t>(t170);
    // 0x004dde96: pop esi
    uint32_t t171 = ctx.esp;
    uint32_t t172 = mem.r32(t171);
    uint32_t t173 = static_cast<uint32_t>(t171 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t173);
    ctx.esi = static_cast<uint32_t>(t172);
    // 0x004dde97: mov dword ptr [eax + 0x80], edx
    uint32_t t174 = static_cast<uint32_t>(ctx.eax + 0x00000080u);
    mem.w32(t174, ctx.edx);
    // 0x004dde9d: pop ebx
    uint32_t t175 = ctx.esp;
    uint32_t t176 = mem.r32(t175);
    uint32_t t177 = static_cast<uint32_t>(t175 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t177);
    ctx.ebx = static_cast<uint32_t>(t176);
    // 0x004dde9e: mov eax, 1
    ctx.eax = static_cast<uint32_t>(0x00000001u);
    // 0x004ddea3: xor ecx, esp
    uint32_t t178 = static_cast<uint32_t>(ctx.ecx ^ ctx.esp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t178);
    ctx.ecx = static_cast<uint32_t>(t178);
    // 0x004ddea5: mov dword ptr [0x76e83c], eax
    mem.w32(0x0076e83cu, ctx.eax);
    // 0x004ddeaa: call 0x4e02f8
    uint32_t t179 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t179);
    mem.w32(t179, 0x004ddeafu);
    hle_crt_004e02f8(ctx, mem);
    // 0x004ddeaf: mov esp, ebp
    ctx.esp = static_cast<uint32_t>(ctx.ebp);
    // 0x004ddeb1: pop ebp
    uint32_t t180 = ctx.esp;
    uint32_t t181 = mem.r32(t180);
    uint32_t t182 = static_cast<uint32_t>(t180 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t182);
    ctx.ebp = static_cast<uint32_t>(t181);
    // 0x004ddeb2: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004dde70: {
    // 0x004dde70: mov ecx, dword ptr [eax + 0x38]
    uint32_t t183 = static_cast<uint32_t>(ctx.eax + 0x00000038u);
    uint32_t t184 = mem.r32(t183);
    ctx.ecx = static_cast<uint32_t>(t184);
    // 0x004dde73: fst qword ptr [ecx + 0x308]
    double t185 = ctx.fpu_st(0);
    uint32_t t186 = static_cast<uint32_t>(ctx.ecx + 0x00000308u);
    mem.wf64(t186, t185);
    goto bb_004dde79;
}
}

// sub_004de100 | subsystem=Sound | canonical | 11 blocks | 36 insns
void sub_004de100(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004de100: push ebx
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebx);
    // 0x004de101: push edi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.edi);
    // 0x004de102: mov edi, dword ptr [eax*4 + 0x76c6f8]
    uint32_t t2 = recomp_detail::shl<uint32_t>(ctx.eax, 0x00000002u);
    uint32_t t3 = static_cast<uint32_t>(t2 + 0x0076c6f8u);
    uint32_t t4 = mem.r32(t3);
    ctx.edi = static_cast<uint32_t>(t4);
    // 0x004de109: test edi, edi
    uint32_t t5 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t5);
    // 0x004de10b: mov ebx, ecx
    ctx.ebx = static_cast<uint32_t>(ctx.ecx);
    // 0x004de10d: je 0x4de15b
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004de15b;
    goto bb_004de10f;
}
bb_004de15b: {
    // 0x004de15b: pop edi
    uint32_t t6 = ctx.esp;
    uint32_t t7 = mem.r32(t6);
    uint32_t t8 = static_cast<uint32_t>(t6 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t8);
    ctx.edi = static_cast<uint32_t>(t7);
    // 0x004de15c: pop ebx
    uint32_t t9 = ctx.esp;
    uint32_t t10 = mem.r32(t9);
    uint32_t t11 = static_cast<uint32_t>(t9 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t11);
    ctx.ebx = static_cast<uint32_t>(t10);
    // 0x004de15d: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004de10f: {
    // 0x004de10f: cmp dword ptr [esp + 0xc], 0
    uint32_t t12 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    uint32_t t13 = mem.r32(t12);
    uint32_t t14 = static_cast<uint32_t>(t13 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t13, 0x00000000u, t14);
    // 0x004de114: jne 0x4de136
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004de136;
    goto bb_004de116;
}
bb_004de136: {
    // 0x004de136: push esi
    uint32_t t15 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t15);
    mem.w32(t15, ctx.esi);
    // 0x004de137: xor esi, esi
    uint32_t t16 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t16);
    ctx.esi = static_cast<uint32_t>(t16);
    // 0x004de139: cmp dword ptr [edi + 0x10], esi
    uint32_t t17 = static_cast<uint32_t>(ctx.edi + 0x00000010u);
    uint32_t t18 = mem.r32(t17);
    uint32_t t19 = static_cast<uint32_t>(t18 - ctx.esi);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t18, ctx.esi, t19);
    // 0x004de13c: jle 0x4de157
    if (recomp_detail::eval_cond(ctx, Cond::LE)) goto bb_004de157;
    goto bb_004de13e;
}
bb_004de116: {
    // 0x004de116: mov eax, dword ptr [0x554140]
    uint32_t t20 = mem.r32(0x00554140u);
    ctx.eax = static_cast<uint32_t>(t20);
    // 0x004de11b: test eax, eax
    uint32_t t21 = static_cast<uint32_t>(ctx.eax & ctx.eax);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t21);
    // 0x004de11d: je 0x4de128
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004de128;
    goto bb_004de11f;
}
bb_004de157: {
    // 0x004de157: mov dword ptr [edi + 0x18], ebx
    uint32_t t22 = static_cast<uint32_t>(ctx.edi + 0x00000018u);
    mem.w32(t22, ctx.ebx);
    // 0x004de15a: pop esi
    uint32_t t23 = ctx.esp;
    uint32_t t24 = mem.r32(t23);
    uint32_t t25 = static_cast<uint32_t>(t23 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t25);
    ctx.esi = static_cast<uint32_t>(t24);
    goto bb_004de15b;
}
bb_004de13e: {
    // 0x004de13e: mov edi, edi
    ctx.edi = static_cast<uint32_t>(ctx.edi);
    goto bb_004de140;
}
bb_004de128: {
    // 0x004de128: cmp dword ptr [0x55df14], 0
    uint32_t t26 = mem.r32(0x0055df14u);
    uint32_t t27 = static_cast<uint32_t>(t26 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t26, 0x00000000u, t27);
    // 0x004de12f: je 0x4de136
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004de136;
    goto bb_004de131;
}
bb_004de11f: {
    // 0x004de11f: cmp dword ptr [eax + 0x150], 0
    uint32_t t28 = static_cast<uint32_t>(ctx.eax + 0x00000150u);
    uint32_t t29 = mem.r32(t28);
    uint32_t t30 = static_cast<uint32_t>(t29 - 0x00000000u);
    recomp_detail::update_flags_sub<uint32_t>(ctx, t29, 0x00000000u, t30);
    // 0x004de126: jne 0x4de136
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004de136;
    goto bb_004de128;
}
bb_004de140: {
    // 0x004de140: mov ecx, dword ptr [edi + 4]
    uint32_t t31 = static_cast<uint32_t>(ctx.edi + 0x00000004u);
    uint32_t t32 = mem.r32(t31);
    ctx.ecx = static_cast<uint32_t>(t32);
    // 0x004de143: mov eax, dword ptr [ecx + esi*4]
    uint32_t t33 = recomp_detail::shl<uint32_t>(ctx.esi, 0x00000002u);
    uint32_t t34 = static_cast<uint32_t>(ctx.ecx + t33);
    uint32_t t35 = mem.r32(t34);
    ctx.eax = static_cast<uint32_t>(t35);
    // 0x004de146: mov edx, dword ptr [eax]
    uint32_t t36 = mem.r32(ctx.eax);
    ctx.edx = static_cast<uint32_t>(t36);
    // 0x004de148: push ebx
    uint32_t t37 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t37);
    mem.w32(t37, ctx.ebx);
    // 0x004de149: push eax
    uint32_t t38 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t38);
    mem.w32(t38, ctx.eax);
    // 0x004de14a: mov eax, dword ptr [edx + 0x3c]
    uint32_t t39 = static_cast<uint32_t>(ctx.edx + 0x0000003cu);
    uint32_t t40 = mem.r32(t39);
    ctx.eax = static_cast<uint32_t>(t40);
    // 0x004de14d: call eax
    uint32_t t41 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t41);
    mem.w32(t41, 0x004de14fu);
    call_indirect(ctx, mem, ctx.eax);
    // 0x004de14f: add esi, 1
    uint32_t t42 = static_cast<uint32_t>(ctx.esi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000001u, t42);
    ctx.esi = static_cast<uint32_t>(t42);
    // 0x004de152: cmp esi, dword ptr [edi + 0x10]
    uint32_t t43 = static_cast<uint32_t>(ctx.edi + 0x00000010u);
    uint32_t t44 = mem.r32(t43);
    uint32_t t45 = static_cast<uint32_t>(ctx.esi - t44);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, t44, t45);
    // 0x004de155: jl 0x4de140
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004de140;
    goto bb_004de157;
}
bb_004de131: {
    // 0x004de131: mov ebx, 0xffffd8f0
    ctx.ebx = static_cast<uint32_t>(0xffffd8f0u);
    goto bb_004de136;
}
}

// sub_004de200 | subsystem=Sound | canonical | 9 blocks | 30 insns
void sub_004de200(CpuContext& ctx, GuestMemory& mem) {
{
    // 0x004de200: push ebp
    uint32_t t0 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t0);
    mem.w32(t0, ctx.ebp);
    // 0x004de201: push esi
    uint32_t t1 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t1);
    mem.w32(t1, ctx.esi);
    // 0x004de202: xor ebp, ebp
    uint32_t t2 = static_cast<uint32_t>(ctx.ebp ^ ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t2);
    ctx.ebp = static_cast<uint32_t>(t2);
    // 0x004de204: push edi
    uint32_t t3 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t3);
    mem.w32(t3, ctx.edi);
    // 0x004de205: xor esi, esi
    uint32_t t4 = static_cast<uint32_t>(ctx.esi ^ ctx.esi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t4);
    ctx.esi = static_cast<uint32_t>(t4);
}
bb_004de207: {
    // 0x004de207: cmp byte ptr [esi + 0x76e008], 1
    uint32_t t5 = static_cast<uint32_t>(ctx.esi + 0x0076e008u);
    uint8_t t6 = mem.r8(t5);
    uint8_t t7 = static_cast<uint8_t>(static_cast<uint32_t>(t6) - static_cast<uint32_t>(uint8_t{0x01u}));
    recomp_detail::update_flags_sub<uint8_t>(ctx, t6, uint8_t{0x01u}, t7);
    // 0x004de20e: jne 0x4de223
    if (recomp_detail::eval_cond(ctx, Cond::NE)) goto bb_004de223;
    goto bb_004de210;
}
bb_004de223: {
    // 0x004de223: add esi, 1
    uint32_t t8 = static_cast<uint32_t>(ctx.esi + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esi, 0x00000001u, t8);
    ctx.esi = static_cast<uint32_t>(t8);
    // 0x004de226: cmp esi, 0x5dc
    uint32_t t9 = static_cast<uint32_t>(ctx.esi - 0x000005dcu);
    recomp_detail::update_flags_sub<uint32_t>(ctx, ctx.esi, 0x000005dcu, t9);
    // 0x004de22c: jl 0x4de207
    if (recomp_detail::eval_cond(ctx, Cond::L)) goto bb_004de207;
    goto bb_004de22e;
}
bb_004de210: {
    // 0x004de210: mov edi, dword ptr [esi*4 + 0x76c6f8]
    uint32_t t10 = recomp_detail::shl<uint32_t>(ctx.esi, 0x00000002u);
    uint32_t t11 = static_cast<uint32_t>(t10 + 0x0076c6f8u);
    uint32_t t12 = mem.r32(t11);
    ctx.edi = static_cast<uint32_t>(t12);
    // 0x004de217: test edi, edi
    uint32_t t13 = static_cast<uint32_t>(ctx.edi & ctx.edi);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t13);
    // 0x004de219: je 0x4de220
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004de220;
    goto bb_004de21b;
}
bb_004de22e: {
    // 0x004de22e: test ebp, ebp
    uint32_t t14 = static_cast<uint32_t>(ctx.ebp & ctx.ebp);
    recomp_detail::update_flags_logic<uint32_t>(ctx, t14);
    // 0x004de230: je 0x4de243
    if (recomp_detail::eval_cond(ctx, Cond::E)) goto bb_004de243;
    goto bb_004de232;
}
bb_004de220: {
    // 0x004de220: add ebp, 1
    uint32_t t15 = static_cast<uint32_t>(ctx.ebp + 0x00000001u);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.ebp, 0x00000001u, t15);
    ctx.ebp = static_cast<uint32_t>(t15);
    goto bb_004de223;
}
bb_004de21b: {
    // 0x004de21b: call 0x40f3a0
    uint32_t t16 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t16);
    mem.w32(t16, 0x004de220u);
    sub_0040f3a0(ctx, mem);
    goto bb_004de220;
}
bb_004de243: {
    // 0x004de243: push 0x5dc
    uint32_t t17 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t17);
    mem.w32(t17, 0x000005dcu);
    // 0x004de248: push 0
    uint32_t t18 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t18);
    mem.w32(t18, 0x00000000u);
    // 0x004de24a: push 0x76e008
    uint32_t t19 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t19);
    mem.w32(t19, 0x0076e008u);
    // 0x004de24f: call 0x4e6340
    uint32_t t20 = static_cast<uint32_t>(ctx.esp - 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t20);
    mem.w32(t20, 0x004de254u);
    hle_crt_004e6340(ctx, mem);
    // 0x004de254: add esp, 0xc
    uint32_t t21 = static_cast<uint32_t>(ctx.esp + 0x0000000cu);
    recomp_detail::update_flags_add<uint32_t>(ctx, ctx.esp, 0x0000000cu, t21);
    ctx.esp = static_cast<uint32_t>(t21);
    // 0x004de257: pop edi
    uint32_t t22 = ctx.esp;
    uint32_t t23 = mem.r32(t22);
    uint32_t t24 = static_cast<uint32_t>(t22 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t24);
    ctx.edi = static_cast<uint32_t>(t23);
    // 0x004de258: pop esi
    uint32_t t25 = ctx.esp;
    uint32_t t26 = mem.r32(t25);
    uint32_t t27 = static_cast<uint32_t>(t25 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t27);
    ctx.esi = static_cast<uint32_t>(t26);
    // 0x004de259: pop ebp
    uint32_t t28 = ctx.esp;
    uint32_t t29 = mem.r32(t28);
    uint32_t t30 = static_cast<uint32_t>(t28 + 0x00000004u);
    ctx.esp = static_cast<uint32_t>(t30);
    ctx.ebp = static_cast<uint32_t>(t29);
    // 0x004de25a: ret
    ctx.eip = ctx.pop32(mem);
    return;
}
bb_004de232: {
    // 0x004de232: mov ecx, 0x177
    ctx.ecx = static_cast<uint32_t>(0x00000177u);
    // 0x004de237: mov esi, 0x76e008
    ctx.esi = static_cast<uint32_t>(0x0076e008u);
    // 0x004de23c: mov edi, 0x76c0b8
    ctx.edi = static_cast<uint32_t>(0x0076c0b8u);
    // 0x004de241: rep movsd dword ptr es:[edi], dword ptr [esi]
    recomp_detail::exec_string_op<uint32_t>(ctx, mem, 0, 1);
    goto bb_004de243;
}
}

} // namespace mbaa_recomp

#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
