"""C++20 AOT code generator for lifted MBAA.exe IR -> mbaacc-recomp-ios/build_gen/."""

from __future__ import annotations

import json
import struct
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path

from .cfg import PEBinary, ProgramCFG
from .ir import (
    Assign,
    BinOp,
    CallCRT,
    CallDirect,
    CallIAT,
    CallIndirect,
    Comment,
    CondExpr,
    Const,
    FBinOp,
    FConst,
    Flag,
    FpuClearEx,
    FpuCmp,
    FpuLoadInt,
    FpuLoadMem,
    FpuPeek,
    FpuPop,
    FpuPush,
    FpuSet,
    FpuStoreInt,
    FpuStoreMem,
    FpuSwap,
    FUnOp,
    IRBlock,
    IRExpr,
    IRFunction,
    IRTerm,
    IRValue,
    MemLoad,
    ReadVal,
    Reg,
    Select,
    StringOp,
    Temp,
    TermBranch,
    TermFallthrough,
    TermJump,
    TermRet,
    TermSwitch,
    TermTailCallCRT,
    TermTailCallGame,
    TermTailCallIAT,
    TermTailCallIndirect,
    TermTrap,
    UnOp,
    UpdateFlags,
    WriteFlag,
    WriteMem,
    WriteReg,
)

# Exact shard mapping required by CMakeLists.txt (MBAA_GEN_SOURCES)
SUBSYSTEM_SHARDS: dict[str, str] = {
    "Core/Windows": "gen_core.cpp",
    "FilePacFunc": "gen_filepac.cpp",
    "Dxtools": "gen_dxtools.cpp",
    "Scene": "gen_scene.cpp",
    "Game/Engine": "gen_game_engine.cpp",
    "Chara": "gen_chara.cpp",
    "MenuWindow": "gen_menu.cpp",
    "Replay": "gen_replay.cpp",
    "Input": "gen_input.cpp",
    "Sound": "gen_sound.cpp",
    "NetVS": "gen_netvs.cpp",
}

ALL_SHARD_FILES: tuple[str, ...] = (
    "gen_core.cpp",
    "gen_filepac.cpp",
    "gen_dxtools.cpp",
    "gen_scene.cpp",
    "gen_game_engine.cpp",
    "gen_chara.cpp",
    "gen_menu.cpp",
    "gen_replay.cpp",
    "gen_input.cpp",
    "gen_sound.cpp",
    "gen_netvs.cpp",
    "gen_dispatch.cpp",
)

EXPECTED_GEN_HEADERS: tuple[str, ...] = (
    "recomp_funcs.h",
    "iat_table.h",
)

_FLAG_CONST = {
    "cf": "kFlagCF",
    "pf": "kFlagPF",
    "af": "kFlagAF",
    "zf": "kFlagZF",
    "sf": "kFlagSF",
    "of": "kFlagOF",
    "df": "kFlagDF",
}

_CTYPE = {8: "uint8_t", 16: "uint16_t", 32: "uint32_t", 64: "uint64_t"}

_COND_ENUM = {
    "o": "Cond::O",
    "no": "Cond::NO",
    "b": "Cond::B",
    "ae": "Cond::AE",
    "e": "Cond::E",
    "ne": "Cond::NE",
    "be": "Cond::BE",
    "a": "Cond::A",
    "s": "Cond::S",
    "ns": "Cond::NS",
    "p": "Cond::P",
    "np": "Cond::NP",
    "l": "Cond::L",
    "ge": "Cond::GE",
    "le": "Cond::LE",
    "g": "Cond::G",
}

_STRING_KIND = {"movs": 0, "stos": 1, "cmps": 2, "scas": 3}
_STRING_REP = {None: 0, "rep": 1, "repe": 2, "repne": 3}

_GPR32_BASE = {
    "ax": "eax",
    "al": "eax",
    "ah": "eax",
    "cx": "ecx",
    "cl": "ecx",
    "ch": "ecx",
    "dx": "edx",
    "dl": "edx",
    "dh": "edx",
    "bx": "ebx",
    "bl": "ebx",
    "bh": "ebx",
    "sp": "esp",
    "bp": "ebp",
    "si": "esi",
    "di": "edi",
}


@dataclass
class EmitResult:
    out_dir: Path
    files_written: list[str]
    function_count: int
    canonical_count: int
    extra_callback_count: int
    crt_init_count: int
    iat_count: int
    shard_counts: dict[str, int]
    manifest_path: Path


# ---------------------------------------------------------------------------
# Runtime Support Header Generation (`recomp_funcs.h`)
# ---------------------------------------------------------------------------

_RECOMP_DETAIL_HEADER = r"""
#include <bit>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <limits>
#include <type_traits>
#include <utility>

#include "mbaa_recomp/cpu_context.h"
#include "mbaa_recomp/guest_memory.h"
#include "mbaa_recomp/dispatch.h"
#include "mbaa_recomp/hle_crt.h"
#include "mbaa_recomp/hle_win32.h"

namespace mbaa_recomp::recomp_detail {

// ---------------------------------------------------------------------------
// Sub-register & flag helpers (covering all GPR widths including sp/bp/si/di)
// ---------------------------------------------------------------------------
inline uint8_t r8l(uint32_t reg) noexcept {
    return static_cast<uint8_t>(reg & 0xFFu);
}
inline void w8l(uint32_t& reg, uint8_t val) noexcept {
    reg = (reg & 0xFFFFFF00u) | static_cast<uint32_t>(val);
}
inline uint8_t r8h(uint32_t reg) noexcept {
    return static_cast<uint8_t>((reg >> 8) & 0xFFu);
}
inline void w8h(uint32_t& reg, uint8_t val) noexcept {
    reg = (reg & 0xFFFF00FFu) | (static_cast<uint32_t>(val) << 8);
}
inline uint16_t r16(uint32_t reg) noexcept {
    return static_cast<uint16_t>(reg & 0xFFFFu);
}
inline void w16(uint32_t& reg, uint16_t val) noexcept {
    reg = (reg & 0xFFFF0000u) | static_cast<uint32_t>(val);
}

inline uint32_t get_flag(const CpuContext& ctx, uint32_t mask) noexcept {
    return (ctx.eflags & mask) ? 1u : 0u;
}
inline void set_flag(CpuContext& ctx, uint32_t mask, bool on) noexcept {
    if (on) {
        ctx.eflags |= mask;
    } else {
        ctx.eflags &= ~mask;
    }
}
inline bool parity_even(uint32_t v) noexcept {
    return (std::popcount(v & 0xFFu) & 1) == 0;
}

template <typename T>
inline void set_szp(CpuContext& ctx, T res) noexcept {
    constexpr uint32_t kBits = static_cast<uint32_t>(sizeof(T) * 8u);
    constexpr uint32_t kSign = uint32_t{1} << (kBits - 1u);
    const uint32_t u = static_cast<uint32_t>(res);
    set_flag(ctx, kFlagZF, res == T{0});
    set_flag(ctx, kFlagSF, (u & kSign) != 0u);
    set_flag(ctx, kFlagPF, parity_even(u));
}

// ---------------------------------------------------------------------------
// UB-free shifts, rotates, extensions, and 64/32 divisions
// ---------------------------------------------------------------------------
template <typename T>
inline T shl(T a, uint32_t count) noexcept {
    constexpr uint32_t kBits = static_cast<uint32_t>(sizeof(T) * 8u);
    const uint32_t c = count & 0x1Fu;
    if (c == 0u) return a;
    if (c >= kBits) return T{0};
    return static_cast<T>(static_cast<uint32_t>(a) << c);
}

template <typename T>
inline T shr(T a, uint32_t count) noexcept {
    constexpr uint32_t kBits = static_cast<uint32_t>(sizeof(T) * 8u);
    const uint32_t c = count & 0x1Fu;
    if (c == 0u) return a;
    if (c >= kBits) return T{0};
    return static_cast<T>(static_cast<uint32_t>(a) >> c);
}

template <typename T>
inline T sar(T a, uint32_t count) noexcept {
    using S = std::make_signed_t<T>;
    const uint32_t c = count & 0x1Fu;
    const int32_t s = static_cast<int32_t>(static_cast<S>(a));
    if (c == 0u) return a;
    const uint32_t clamped = (c >= 31u) ? 31u : c;
    return static_cast<T>(s >> clamped);
}

template <typename T>
inline T rol(T a, uint32_t count) noexcept {
    constexpr uint32_t kBits = static_cast<uint32_t>(sizeof(T) * 8u);
    const uint32_t c = (count & 0x1Fu) % kBits;
    if (c == 0u) return a;
    const uint32_t ua = static_cast<uint32_t>(a);
    return static_cast<T>((ua << c) | (ua >> (kBits - c)));
}

template <typename T>
inline T ror(T a, uint32_t count) noexcept {
    constexpr uint32_t kBits = static_cast<uint32_t>(sizeof(T) * 8u);
    const uint32_t c = (count & 0x1Fu) % kBits;
    if (c == 0u) return a;
    const uint32_t ua = static_cast<uint32_t>(a);
    return static_cast<T>((ua >> c) | (ua << (kBits - c)));
}

inline uint32_t div64_u(uint64_t a, uint32_t b) noexcept {
    return (b == 0u) ? 0u : static_cast<uint32_t>(a / static_cast<uint64_t>(b));
}
inline uint32_t mod64_u(uint64_t a, uint32_t b) noexcept {
    return (b == 0u) ? 0u : static_cast<uint32_t>(a % static_cast<uint64_t>(b));
}
inline uint32_t div64_s(uint64_t a, uint32_t b) noexcept {
    const int64_t sa = static_cast<int64_t>(a);
    const int64_t sb = static_cast<int64_t>(static_cast<int32_t>(b));
    if (sb == 0 || (sa == std::numeric_limits<int64_t>::min() && sb == -1)) return 0u;
    return static_cast<uint32_t>(sa / sb);
}
inline uint32_t mod64_s(uint64_t a, uint32_t b) noexcept {
    const int64_t sa = static_cast<int64_t>(a);
    const int64_t sb = static_cast<int64_t>(static_cast<int32_t>(b));
    if (sb == 0 || (sa == std::numeric_limits<int64_t>::min() && sb == -1)) return 0u;
    return static_cast<uint32_t>(sa % sb);
}

inline uint16_t sext8_16(uint8_t v) noexcept {
    return static_cast<uint16_t>(static_cast<int16_t>(static_cast<int8_t>(v)));
}
inline uint32_t sext8_32(uint8_t v) noexcept {
    return static_cast<uint32_t>(static_cast<int32_t>(static_cast<int8_t>(v)));
}
inline uint32_t sext16_32(uint16_t v) noexcept {
    return static_cast<uint32_t>(static_cast<int32_t>(static_cast<int16_t>(v)));
}

// ---------------------------------------------------------------------------
// Condition Evaluation
// ---------------------------------------------------------------------------
enum class Cond { O, NO, B, AE, E, NE, BE, A, S, NS, P, NP, L, GE, LE, G };

inline bool eval_cond(const CpuContext& ctx, Cond c) noexcept {
    const bool cf = (ctx.eflags & kFlagCF) != 0u;
    const bool zf = (ctx.eflags & kFlagZF) != 0u;
    const bool sf = (ctx.eflags & kFlagSF) != 0u;
    const bool of = (ctx.eflags & kFlagOF) != 0u;
    const bool pf = (ctx.eflags & kFlagPF) != 0u;
    switch (c) {
        case Cond::O:  return of;
        case Cond::NO: return !of;
        case Cond::B:  return cf;
        case Cond::AE: return !cf;
        case Cond::E:  return zf;
        case Cond::NE: return !zf;
        case Cond::BE: return cf || zf;
        case Cond::A:  return !(cf || zf);
        case Cond::S:  return sf;
        case Cond::NS: return !sf;
        case Cond::P:  return pf;
        case Cond::NP: return !pf;
        case Cond::L:  return sf != of;
        case Cond::GE: return sf == of;
        case Cond::LE: return zf || (sf != of);
        case Cond::G:  return !zf && (sf == of);
    }
    return false;
}

// ---------------------------------------------------------------------------
// Exact EFLAGS Semantics
// ---------------------------------------------------------------------------
template <typename T>
inline void update_flags_add(CpuContext& ctx, T a, T b, T r, T cin = T{0}) noexcept {
    constexpr uint32_t kBits = static_cast<uint32_t>(sizeof(T) * 8u);
    constexpr uint32_t kSign = uint32_t{1} << (kBits - 1u);
    const uint64_t full = static_cast<uint64_t>(a) + static_cast<uint64_t>(b) + static_cast<uint64_t>(cin);
    const uint32_t ua = static_cast<uint32_t>(a);
    const uint32_t ub = static_cast<uint32_t>(b);
    const uint32_t ur = static_cast<uint32_t>(r);
    set_flag(ctx, kFlagCF, full > static_cast<uint64_t>(std::numeric_limits<T>::max()));
    set_flag(ctx, kFlagAF, ((ua ^ ub ^ ur) & 0x10u) != 0u);
    set_flag(ctx, kFlagOF, (((~(ua ^ ub)) & (ua ^ ur)) & kSign) != 0u);
    set_szp<T>(ctx, r);
}

template <typename T>
inline void update_flags_sub(CpuContext& ctx, T a, T b, T r, T cin = T{0}) noexcept {
    constexpr uint32_t kBits = static_cast<uint32_t>(sizeof(T) * 8u);
    constexpr uint32_t kSign = uint32_t{1} << (kBits - 1u);
    const uint64_t rhs_tot = static_cast<uint64_t>(b) + static_cast<uint64_t>(cin);
    const uint32_t ua = static_cast<uint32_t>(a);
    const uint32_t ub = static_cast<uint32_t>(b);
    const uint32_t ur = static_cast<uint32_t>(r);
    set_flag(ctx, kFlagCF, static_cast<uint64_t>(a) < rhs_tot);
    set_flag(ctx, kFlagAF, ((ua ^ ub ^ ur) & 0x10u) != 0u);
    set_flag(ctx, kFlagOF, (((ua ^ ub) & (ua ^ ur)) & kSign) != 0u);
    set_szp<T>(ctx, r);
}

template <typename T>
inline void update_flags_inc(CpuContext& ctx, T a, T r) noexcept {
    constexpr uint32_t kBits = static_cast<uint32_t>(sizeof(T) * 8u);
    constexpr uint32_t kSign = uint32_t{1} << (kBits - 1u);
    const uint32_t ua = static_cast<uint32_t>(a);
    const uint32_t ur = static_cast<uint32_t>(r);
    set_flag(ctx, kFlagAF, ((ua ^ 1u ^ ur) & 0x10u) != 0u);
    set_flag(ctx, kFlagOF, ua == (kSign - 1u));
    set_szp<T>(ctx, r);
}

template <typename T>
inline void update_flags_dec(CpuContext& ctx, T a, T r) noexcept {
    constexpr uint32_t kBits = static_cast<uint32_t>(sizeof(T) * 8u);
    constexpr uint32_t kSign = uint32_t{1} << (kBits - 1u);
    const uint32_t ua = static_cast<uint32_t>(a);
    const uint32_t ur = static_cast<uint32_t>(r);
    set_flag(ctx, kFlagAF, ((ua ^ 1u ^ ur) & 0x10u) != 0u);
    set_flag(ctx, kFlagOF, ua == kSign);
    set_szp<T>(ctx, r);
}

template <typename T>
inline void update_flags_neg(CpuContext& ctx, T a, T r) noexcept {
    constexpr uint32_t kBits = static_cast<uint32_t>(sizeof(T) * 8u);
    constexpr uint32_t kSign = uint32_t{1} << (kBits - 1u);
    const uint32_t ua = static_cast<uint32_t>(a);
    set_flag(ctx, kFlagCF, ua != 0u);
    set_flag(ctx, kFlagAF, (ua & 0xFu) != 0u);
    set_flag(ctx, kFlagOF, ua == kSign);
    set_szp<T>(ctx, r);
}

template <typename T>
inline void update_flags_logic(CpuContext& ctx, T r) noexcept {
    set_flag(ctx, kFlagCF, false);
    set_flag(ctx, kFlagOF, false);
    set_flag(ctx, kFlagAF, false);
    set_szp<T>(ctx, r);
}

template <typename T>
inline void update_flags_shl(CpuContext& ctx, T a, uint32_t raw_cnt, T r) noexcept {
    constexpr uint32_t kBits = static_cast<uint32_t>(sizeof(T) * 8u);
    const uint32_t cnt = raw_cnt & 0x1Fu;
    if (cnt == 0u) return;
    const uint32_t ua = static_cast<uint32_t>(a);
    const uint32_t ur = static_cast<uint32_t>(r);
    const bool cf = (cnt <= kBits) && (((ua >> (kBits - cnt)) & 1u) != 0u);
    set_flag(ctx, kFlagCF, cf);
    if (cnt == 1u) {
        set_flag(ctx, kFlagOF, (((ur >> (kBits - 1u)) & 1u) ^ (cf ? 1u : 0u)) != 0u);
    }
    set_szp<T>(ctx, r);
}

template <typename T>
inline void update_flags_shr(CpuContext& ctx, T a, uint32_t raw_cnt, T r) noexcept {
    constexpr uint32_t kBits = static_cast<uint32_t>(sizeof(T) * 8u);
    const uint32_t cnt = raw_cnt & 0x1Fu;
    if (cnt == 0u) return;
    const uint32_t ua = static_cast<uint32_t>(a);
    const bool cf = (cnt <= kBits) && (((ua >> (cnt - 1u)) & 1u) != 0u);
    set_flag(ctx, kFlagCF, cf);
    if (cnt == 1u) {
        set_flag(ctx, kFlagOF, ((ua >> (kBits - 1u)) & 1u) != 0u);
    }
    set_szp<T>(ctx, r);
}

template <typename T>
inline void update_flags_sar(CpuContext& ctx, T a, uint32_t raw_cnt, T r) noexcept {
    using S = std::make_signed_t<T>;
    constexpr uint32_t kBits = static_cast<uint32_t>(sizeof(T) * 8u);
    const uint32_t cnt = raw_cnt & 0x1Fu;
    if (cnt == 0u) return;
    const int32_t sa = static_cast<int32_t>(static_cast<S>(a));
    bool cf = false;
    if (cnt <= kBits) {
        cf = ((sa >> (cnt - 1u)) & 1) != 0;
    } else {
        cf = sa < 0;
    }
    set_flag(ctx, kFlagCF, cf);
    if (cnt == 1u) {
        set_flag(ctx, kFlagOF, false);
    }
    set_szp<T>(ctx, r);
}

template <typename T>
inline void update_flags_rol(CpuContext& ctx, uint32_t raw_cnt, T r) noexcept {
    constexpr uint32_t kBits = static_cast<uint32_t>(sizeof(T) * 8u);
    const uint32_t cnt = raw_cnt & 0x1Fu;
    if (cnt == 0u) return;
    const uint32_t ur = static_cast<uint32_t>(r);
    const uint32_t cf = ur & 1u;
    set_flag(ctx, kFlagCF, cf != 0u);
    if (cnt == 1u) {
        set_flag(ctx, kFlagOF, (((ur >> (kBits - 1u)) & 1u) ^ cf) != 0u);
    }
}

template <typename T>
inline void update_flags_ror(CpuContext& ctx, uint32_t raw_cnt, T r) noexcept {
    constexpr uint32_t kBits = static_cast<uint32_t>(sizeof(T) * 8u);
    const uint32_t cnt = raw_cnt & 0x1Fu;
    if (cnt == 0u) return;
    const uint32_t ur = static_cast<uint32_t>(r);
    const uint32_t cf = (ur >> (kBits - 1u)) & 1u;
    set_flag(ctx, kFlagCF, cf != 0u);
    if (cnt == 1u) {
        set_flag(ctx, kFlagOF, (((ur >> (kBits - 1u)) ^ (ur >> (kBits - 2u))) & 1u) != 0u);
    }
}

template <typename T>
inline void update_flags_mul(CpuContext& ctx, uint64_t full) noexcept {
    constexpr uint32_t kBits = static_cast<uint32_t>(sizeof(T) * 8u);
    const bool ov = (full >> kBits) != 0ULL;
    set_flag(ctx, kFlagCF, ov);
    set_flag(ctx, kFlagOF, ov);
}

template <typename T>
inline void update_flags_imul(CpuContext& ctx, uint64_t full) noexcept {
    using S = std::make_signed_t<T>;
    constexpr uint32_t kBits2 = static_cast<uint32_t>(sizeof(T) * 16u);
    const T lo = static_cast<T>(full);
    const uint64_t ext = static_cast<uint64_t>(static_cast<int64_t>(static_cast<S>(lo)));
    const uint64_t mask2 = (kBits2 >= 64u) ? ~0ULL : ((uint64_t{1} << kBits2) - 1ULL);
    const bool ov = (ext & mask2) != (full & mask2);
    set_flag(ctx, kFlagCF, ov);
    set_flag(ctx, kFlagOF, ov);
}

// ---------------------------------------------------------------------------
// x87 Extended Precision & Rounding Helpers
// ---------------------------------------------------------------------------
inline double load_ext80(const GuestMemory& mem, uint32_t addr) noexcept {
    const uint64_t mant = mem.r64(addr);
    const uint16_t exp_sign = mem.r16(addr + 8u);
    const double sign = (exp_sign & 0x8000u) ? -1.0 : 1.0;
    const int exp = static_cast<int>(exp_sign & 0x7FFFu);
    if (exp == 0 && mant == 0ULL) {
        return std::copysign(0.0, sign);
    }
    if (exp == 0x7FFF) {
        if ((mant & 0x7FFFFFFFFFFFFFFFULL) == 0ULL) {
            return std::copysign(std::numeric_limits<double>::infinity(), sign);
        }
        return std::numeric_limits<double>::quiet_NaN();
    }
    if (exp == 0) {
        return sign * std::ldexp(static_cast<double>(mant), -16382 - 63);
    }
    return sign * std::ldexp(static_cast<double>(mant), (exp - 16383) - 63);
}

inline int64_t round_x87_to_int64(double val, uint16_t fpu_cw) noexcept {
    if (std::isnan(val) || std::isinf(val)) {
        return std::numeric_limits<int64_t>::min();
    }
    const uint32_t rc = (static_cast<uint32_t>(fpu_cw) >> 10) & 3u;
    double rounded = val;
    if (rc == 0u) {
        const double f = std::floor(val);
        const double diff = val - f;
        if (diff > 0.5) {
            rounded = f + 1.0;
        } else if (diff < 0.5) {
            rounded = f;
        } else {
            const double even_f = std::floor(f * 0.5) * 2.0;
            rounded = (f == even_f) ? f : (f + 1.0);
        }
    } else if (rc == 1u) {
        rounded = std::floor(val);
    } else if (rc == 2u) {
        rounded = std::ceil(val);
    } else {
        rounded = std::trunc(val);
    }
    if (rounded < -9223372036854775808.0 || rounded >= 9223372036854775808.0) {
        return std::numeric_limits<int64_t>::min();
    }
    return static_cast<int64_t>(rounded);
}

template <typename T>
inline void fpu_store_int(const CpuContext& ctx, GuestMemory& mem, uint32_t addr, double val) noexcept {
    const int64_t iv = round_x87_to_int64(val, ctx.fpu_cw);
    if constexpr (sizeof(T) == 2) {
        mem.w16(addr, static_cast<uint16_t>(iv));
    } else if constexpr (sizeof(T) == 4) {
        mem.w32(addr, static_cast<uint32_t>(iv));
    } else {
        mem.w64(addr, static_cast<uint64_t>(iv));
    }
}

inline void fpu_swap(CpuContext& ctx, int idx) noexcept {
    std::swap(ctx.fpu_st(0), ctx.fpu_st(idx));
}

inline void fpu_clear_ex(CpuContext& ctx) noexcept {
    ctx.fpu_sw &= static_cast<uint16_t>(~0x80FFu);
}

// ---------------------------------------------------------------------------
// String Operations (`movs`, `stos`, `cmps`, `scas`)
// ---------------------------------------------------------------------------
template <typename T>
inline T mem_read_t(const GuestMemory& mem, uint32_t addr) noexcept {
    if constexpr (sizeof(T) == 1) return mem.r8(addr);
    else if constexpr (sizeof(T) == 2) return mem.r16(addr);
    else return mem.r32(addr);
}

template <typename T>
inline void mem_write_t(GuestMemory& mem, uint32_t addr, T val) noexcept {
    if constexpr (sizeof(T) == 1) mem.w8(addr, val);
    else if constexpr (sizeof(T) == 2) mem.w16(addr, val);
    else mem.w32(addr, val);
}

template <typename T>
inline void exec_string_op(CpuContext& ctx, GuestMemory& mem, int kind, int rep_mode) noexcept {
    const uint32_t unit = static_cast<uint32_t>(sizeof(T));
    const uint32_t step = (ctx.eflags & kFlagDF) ? (0u - unit) : unit;
    uint32_t count = (rep_mode == 0) ? 1u : ctx.ecx;
    while (count > 0u) {
        if (kind == 0) { // movs
            mem_write_t<T>(mem, ctx.edi, mem_read_t<T>(mem, ctx.esi));
            ctx.esi += step;
            ctx.edi += step;
        } else if (kind == 1) { // stos
            mem_write_t<T>(mem, ctx.edi, static_cast<T>(ctx.eax));
            ctx.edi += step;
        } else { // cmps (2) or scas (3)
            const T a = (kind == 2) ? mem_read_t<T>(mem, ctx.esi) : static_cast<T>(ctx.eax);
            const T b = mem_read_t<T>(mem, ctx.edi);
            if (kind == 2) {
                ctx.esi += step;
            }
            ctx.edi += step;
            const T r = static_cast<T>(static_cast<uint32_t>(a) - static_cast<uint32_t>(b));
            update_flags_sub<T>(ctx, a, b, r);
        }
        --count;
        if (rep_mode != 0) {
            ctx.ecx = count;
            if (kind >= 2) {
                const bool zf = (ctx.eflags & kFlagZF) != 0u;
                if (rep_mode == 2 && !zf) break; // repe
                if (rep_mode == 3 && zf) break;  // repne
            }
        }
    }
}

[[noreturn]] inline void trap_abort(CpuContext& ctx, uint32_t va, const char* kind) noexcept {
    ctx.eip = va;
    std::fprintf(stderr, "[mbaa_recomp] trap (%s) reached at 0x%08x\n", kind, va);
    std::abort();
}

inline void trap_halt(CpuContext& ctx, uint32_t va, const char* kind) noexcept {
    ctx.eip = va;
    std::fprintf(stderr, "[mbaa_recomp] trap (%s) at 0x%08x esp=0x%08x\n", kind, va, ctx.esp);
}

} // namespace mbaa_recomp::recomp_detail
""".lstrip("\n")


# ---------------------------------------------------------------------------
# Expression / Statement C++20 Lowering
# ---------------------------------------------------------------------------

def _reg_read_cpp(name: str) -> str:
    if name in ("eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "eflags", "fs_0", "fpu_cw", "fpu_sw"):
        return f"ctx.{name}"
    base = _GPR32_BASE[name]
    if name.endswith("l"):
        return f"recomp_detail::r8l(ctx.{base})"
    if name.endswith("h"):
        return f"recomp_detail::r8h(ctx.{base})"
    return f"recomp_detail::r16(ctx.{base})"


def _reg_write_cpp(name: str, val_cpp: str) -> str:
    if name in ("eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi", "eflags", "fs_0"):
        return f"ctx.{name} = static_cast<uint32_t>({val_cpp});"
    if name in ("fpu_cw", "fpu_sw"):
        return f"ctx.{name} = static_cast<uint16_t>({val_cpp});"
    base = _GPR32_BASE[name]
    if name.endswith("l"):
        return f"recomp_detail::w8l(ctx.{base}, static_cast<uint8_t>({val_cpp}));"
    if name.endswith("h"):
        return f"recomp_detail::w8h(ctx.{base}, static_cast<uint8_t>({val_cpp}));"
    return f"recomp_detail::w16(ctx.{base}, static_cast<uint16_t>({val_cpp}));"


def _val_cpp(val: IRValue, target_bits: int | None = None, expect_float: bool = False) -> str:
    if isinstance(val, Const):
        if val.bits == 8:
            raw = f"uint8_t{{0x{val.value & 0xFF:02x}u}}"
        elif val.bits == 16:
            raw = f"uint16_t{{0x{val.value & 0xFFFF:04x}u}}"
        elif val.bits == 64:
            raw = f"0x{val.value & 0xFFFFFFFFFFFFFFFF:016x}ULL"
        else:
            raw = f"0x{val.value & 0xFFFFFFFF:08x}u"
        if target_bits is not None and target_bits != val.bits and not expect_float:
            return f"static_cast<{_CTYPE[target_bits]}>({raw})"
        return raw
    if isinstance(val, FConst):
        if val.value == 0.0 and str(val.value) == "0.0":
            return "0.0"
        if val.value == 1.0:
            return "1.0"
        bits = struct.unpack("<Q", struct.pack("<d", val.value))[0]
        return f"std::bit_cast<double>(0x{bits:016x}ULL)"
    if isinstance(val, Temp):
        name = f"t{val.id}"
        if target_bits is not None and not expect_float and not val.is_float and target_bits != val.bits:
            return f"static_cast<{_CTYPE[target_bits]}>({name})"
        return name
    if isinstance(val, Reg):
        raw = _reg_read_cpp(val.name)
        rbits = 16 if val.name in ("fpu_cw", "fpu_sw") else (8 if val.name[-1] in ("l", "h") else (16 if val.name in _GPR32_BASE else 32))
        if target_bits is not None and target_bits != rbits and not expect_float:
            return f"static_cast<{_CTYPE[target_bits]}>({raw})"
        return raw
    if isinstance(val, Flag):
        raw = f"recomp_detail::get_flag(ctx, {_FLAG_CONST[val.name]})"
        if target_bits is not None and target_bits != 32 and not expect_float:
            return f"static_cast<{_CTYPE[target_bits]}>({raw})"
        return raw
    raise TypeError(val)


def _expr_cpp(expr: IRExpr, dst_bits: int) -> str:
    if isinstance(expr, ReadVal):
        return _val_cpp(expr.val, target_bits=dst_bits)

    if isinstance(expr, BinOp):
        op = expr.op
        w = expr.bits
        ctype = _CTYPE[w]
        if op in ("add", "sub", "mul", "imul", "and", "or", "xor"):
            sym = {"add": "+", "sub": "-", "mul": "*", "imul": "*", "and": "&", "or": "|", "xor": "^"}[op]
            if w == 64:
                return f"({_val_cpp(expr.lhs, 64)} {sym} {_val_cpp(expr.rhs, 64)})"
            # Perform unsigned 32-bit operation first to avoid signed int promotion UB on uint8/uint16 multiply
            return f"static_cast<{ctype}>({_val_cpp(expr.lhs, 32)} {sym} {_val_cpp(expr.rhs, 32)})"
        if op in ("shl", "shr", "sar", "rol", "ror"):
            return f"recomp_detail::{op}<{ctype}>({_val_cpp(expr.lhs, w)}, {_val_cpp(expr.rhs, 32)})"
        if op in ("mul64_u",):
            return f"(static_cast<uint64_t>({_val_cpp(expr.lhs, 32)}) * static_cast<uint64_t>({_val_cpp(expr.rhs, 32)}))"
        if op == "mul64_s":
            return (
                f"static_cast<uint64_t>("
                f"static_cast<int64_t>(static_cast<int32_t>({_val_cpp(expr.lhs, 32)})) * "
                f"static_cast<int64_t>(static_cast<int32_t>({_val_cpp(expr.rhs, 32)})))"
            )
        if op == "pack64":
            return f"((static_cast<uint64_t>({_val_cpp(expr.lhs, 32)}) << 32) | static_cast<uint64_t>({_val_cpp(expr.rhs, 32)}))"
        if op in ("div64_u", "mod64_u", "div64_s", "mod64_s"):
            return f"recomp_detail::{op}({_val_cpp(expr.lhs, 64)}, {_val_cpp(expr.rhs, 32)})"
        raise KeyError(op)

    if isinstance(expr, UnOp):
        op = expr.op
        if op == "neg":
            ctype = _CTYPE[expr.bits]
            return f"static_cast<{ctype}>(0u - {_val_cpp(expr.src, 32)})"
        if op == "not":
            ctype = _CTYPE[expr.bits]
            return f"static_cast<{ctype}>(~{_val_cpp(expr.src, 32)})"
        if op == "zext8_32":
            return f"static_cast<uint32_t>(static_cast<uint8_t>({_val_cpp(expr.src)}))"
        if op == "zext16_32":
            return f"static_cast<uint32_t>(static_cast<uint16_t>({_val_cpp(expr.src)}))"
        if op == "zext8_16":
            return f"static_cast<uint16_t>(static_cast<uint8_t>({_val_cpp(expr.src)}))"
        if op in ("sext8_32", "sext16_32", "sext8_16"):
            in_t = "uint8_t" if "8" in op.split("_")[0] else "uint16_t"
            return f"recomp_detail::{op}(static_cast<{in_t}>({_val_cpp(expr.src)}))"
        if op == "trunc32_16":
            return f"static_cast<uint16_t>({_val_cpp(expr.src)})"
        if op == "trunc32_8":
            return f"static_cast<uint8_t>({_val_cpp(expr.src)})"
        if op == "trunc64_lo":
            return f"static_cast<uint32_t>({_val_cpp(expr.src, 64)})"
        if op == "trunc64_hi":
            return f"static_cast<uint32_t>({_val_cpp(expr.src, 64)} >> 32)"
        raise KeyError(op)

    if isinstance(expr, MemLoad):
        return f"mem.r{expr.bits}({_val_cpp(expr.addr, 32)})"

    if isinstance(expr, FpuLoadMem):
        addr_cpp = _val_cpp(expr.addr, 32)
        if expr.bits == 32:
            return f"static_cast<double>(mem.rf32({addr_cpp}))"
        if expr.bits == 64:
            return f"mem.rf64({addr_cpp})"
        if expr.bits == 80:
            return f"recomp_detail::load_ext80(mem, {addr_cpp})"
        raise KeyError(expr.bits)

    if isinstance(expr, FpuLoadInt):
        addr_cpp = _val_cpp(expr.addr, 32)
        return f"static_cast<double>(static_cast<int{expr.bits}_t>(mem.r{expr.bits}({addr_cpp})))"

    if isinstance(expr, FpuPeek):
        return f"ctx.fpu_st({expr.index})"

    if isinstance(expr, FBinOp):
        sym = {"fadd": "+", "fsub": "-", "fmul": "*", "fdiv": "/"}[expr.op]
        return f"({_val_cpp(expr.lhs, expect_float=True)} {sym} {_val_cpp(expr.rhs, expect_float=True)})"

    if isinstance(expr, FUnOp):
        s = _val_cpp(expr.src, expect_float=True)
        if expr.op == "fchs":
            return f"(-{s})"
        if expr.op == "fabs":
            return f"std::fabs({s})"
        if expr.op == "fsqrt":
            return f"std::sqrt({s})"
        raise KeyError(expr.op)

    if isinstance(expr, CondExpr):
        return f"static_cast<uint8_t>(recomp_detail::eval_cond(ctx, {_COND_ENUM[expr.cond]}) ? 1u : 0u)"

    if isinstance(expr, Select):
        return (
            f"(({_val_cpp(expr.cond, 32)} != 0u) ? "
            f"{_val_cpp(expr.when_true, expr.bits)} : {_val_cpp(expr.when_false, expr.bits)})"
        )

    raise TypeError(expr)


def _cond_bool_cpp(cond: str) -> str:
    if cond == "ecx_z":
        return "(ctx.ecx == 0u)"
    if cond == "loop":
        return "(ctx.ecx != 0u)"
    if cond == "loope":
        return "(ctx.ecx != 0u && (ctx.eflags & kFlagZF) != 0u)"
    if cond == "loopne":
        return "(ctx.ecx != 0u && (ctx.eflags & kFlagZF) == 0u)"
    return f"recomp_detail::eval_cond(ctx, {_COND_ENUM[cond]})"


def _collect_needed_labels(fn: IRFunction) -> set[int]:
    """Return block entry VAs that are actually jumped to via `goto` (avoids unused labels)."""
    needed: set[int] = set()
    order = fn.block_order
    for idx, b_va in enumerate(order):
        next_va = order[idx + 1] if idx + 1 < len(order) else None
        term = fn.blocks[b_va].term
        if isinstance(term, (TermJump, TermFallthrough)):
            if term.target_va != next_va:
                needed.add(term.target_va)
        elif isinstance(term, TermBranch):
            needed.add(term.target_va)
            if term.fallthrough_va != next_va:
                needed.add(term.fallthrough_va)
        elif isinstance(term, TermSwitch):
            needed.update(term.targets)
    return needed


def _emit_stmt_lines(st, out: list[str], indent: str, emit_comments: bool) -> None:
    if isinstance(st, Comment):
        if emit_comments:
            out.append(f"{indent}// 0x{st.va:08x}: {st.text}")
        return
    if isinstance(st, Assign):
        ctype = "double" if st.dst.is_float else _CTYPE[st.dst.bits]
        out.append(f"{indent}{ctype} t{st.dst.id} = {_expr_cpp(st.expr, st.dst.bits)};")
        return
    if isinstance(st, WriteReg):
        out.append(f"{indent}{_reg_write_cpp(st.reg, _val_cpp(st.val))}")
        return
    if isinstance(st, WriteFlag):
        out.append(
            f"{indent}recomp_detail::set_flag(ctx, {_FLAG_CONST[st.flag]}, {_val_cpp(st.val, 32)} != 0u);"
        )
        return
    if isinstance(st, UpdateFlags):
        ctype = _CTYPE[st.bits]
        op = st.op
        if op in ("add", "adc"):
            cin = f", {_val_cpp(st.carry_in, st.bits)}" if st.carry_in is not None else ""
            out.append(
                f"{indent}recomp_detail::update_flags_add<{ctype}>("
                f"ctx, {_val_cpp(st.lhs, st.bits)}, {_val_cpp(st.rhs, st.bits)}, {_val_cpp(st.res, st.bits)}{cin});"
            )
        elif op in ("sub", "cmp", "sbb"):
            cin = f", {_val_cpp(st.carry_in, st.bits)}" if st.carry_in is not None else ""
            out.append(
                f"{indent}recomp_detail::update_flags_sub<{ctype}>("
                f"ctx, {_val_cpp(st.lhs, st.bits)}, {_val_cpp(st.rhs, st.bits)}, {_val_cpp(st.res, st.bits)}{cin});"
            )
        elif op in ("inc", "dec", "neg"):
            out.append(
                f"{indent}recomp_detail::update_flags_{op}<{ctype}>("
                f"ctx, {_val_cpp(st.lhs, st.bits)}, {_val_cpp(st.res, st.bits)});"
            )
        elif op == "logic":
            out.append(f"{indent}recomp_detail::update_flags_logic<{ctype}>(ctx, {_val_cpp(st.res, st.bits)});")
        elif op in ("shl", "shr", "sar"):
            out.append(
                f"{indent}recomp_detail::update_flags_{op}<{ctype}>("
                f"ctx, {_val_cpp(st.lhs, st.bits)}, {_val_cpp(st.rhs, 32)}, {_val_cpp(st.res, st.bits)});"
            )
        elif op in ("rol", "ror"):
            out.append(
                f"{indent}recomp_detail::update_flags_{op}<{ctype}>("
                f"ctx, {_val_cpp(st.rhs, 32)}, {_val_cpp(st.res, st.bits)});"
            )
        elif op in ("mul", "imul"):
            out.append(f"{indent}recomp_detail::update_flags_{op}<{ctype}>(ctx, {_val_cpp(st.res, 64)});")
        else:
            raise KeyError(op)
        return
    if isinstance(st, WriteMem):
        out.append(f"{indent}mem.w{st.bits}({_val_cpp(st.addr, 32)}, {_val_cpp(st.val, st.bits)});")
        return
    if isinstance(st, FpuStoreMem):
        val_cpp = _val_cpp(st.val, expect_float=True)
        if st.bits == 32:
            out.append(f"{indent}mem.wf32({_val_cpp(st.addr, 32)}, static_cast<float>({val_cpp}));")
        else:
            out.append(f"{indent}mem.wf64({_val_cpp(st.addr, 32)}, {val_cpp});")
        return
    if isinstance(st, FpuStoreInt):
        out.append(
            f"{indent}recomp_detail::fpu_store_int<{_CTYPE[st.bits]}>("
            f"ctx, mem, {_val_cpp(st.addr, 32)}, {_val_cpp(st.val, expect_float=True)});"
        )
        return
    if isinstance(st, FpuPush):
        out.append(f"{indent}ctx.fpu_push({_val_cpp(st.val, expect_float=True)});")
        return
    if isinstance(st, FpuPop):
        out.append(f"{indent}ctx.fpu_pop();")
        return
    if isinstance(st, FpuSet):
        out.append(f"{indent}ctx.fpu_st({st.index}) = {_val_cpp(st.val, expect_float=True)};")
        return
    if isinstance(st, FpuSwap):
        out.append(f"{indent}recomp_detail::fpu_swap(ctx, {st.index});")
        return
    if isinstance(st, FpuCmp):
        a = _val_cpp(st.lhs, expect_float=True)
        b = _val_cpp(st.rhs, expect_float=True)
        if st.set_eflags:
            out.append(f"{indent}ctx.fpu_compare_eflags({a}, {b});")
        else:
            out.append(f"{indent}ctx.fpu_compare({a}, {b});")
        return
    if isinstance(st, FpuClearEx):
        out.append(f"{indent}recomp_detail::fpu_clear_ex(ctx);")
        return
    if isinstance(st, StringOp):
        kind_i = _STRING_KIND[st.kind]
        rep_i = _STRING_REP[st.rep]
        out.append(f"{indent}recomp_detail::exec_string_op<{_CTYPE[st.bits]}>(ctx, mem, {kind_i}, {rep_i});")
        return
    if isinstance(st, CallDirect):
        out.append(f"{indent}sub_{st.target_va:08x}(ctx, mem);")
        return
    if isinstance(st, CallCRT):
        out.append(f"{indent}hle_crt_{st.target_va:08x}(ctx, mem);")
        return
    if isinstance(st, CallIAT):
        out.append(f"{indent}hle_iat_call(ctx, mem, 0x{st.iat_va:08x}u);")
        return
    if isinstance(st, CallIndirect):
        out.append(f"{indent}call_indirect(ctx, mem, {_val_cpp(st.target, 32)});")
        return
    raise TypeError(st)


def _emit_term_lines(term: IRTerm | None, next_va: int | None, out: list[str], indent: str) -> None:
    assert term is not None
    if isinstance(term, TermRet):
        out.append(f"{indent}ctx.eip = ctx.pop32(mem);")
        if term.pop_extra:
            out.append(f"{indent}ctx.esp += {term.pop_extra}u;")
        out.append(f"{indent}return;")
        return
    if isinstance(term, (TermJump, TermFallthrough)):
        if term.target_va != next_va:
            out.append(f"{indent}goto bb_{term.target_va:08x};")
        return
    if isinstance(term, TermBranch):
        if term.cond in ("loop", "loope", "loopne"):
            out.append(f"{indent}--ctx.ecx;")
        out.append(f"{indent}if ({_cond_bool_cpp(term.cond)}) goto bb_{term.target_va:08x};")
        if term.fallthrough_va != next_va:
            out.append(f"{indent}goto bb_{term.fallthrough_va:08x};")
        return
    if isinstance(term, TermSwitch):
        idx_cpp = _val_cpp(term.index, 32)
        out.append(f"{indent}switch ({idx_cpp}) {{")
        for case_idx, tgt_va in enumerate(term.targets):
            out.append(f"{indent}    case {case_idx}u: goto bb_{tgt_va:08x};")
        out.append(
            f"{indent}    default: recomp_detail::trap_halt(ctx, 0x{term.table_va:08x}u, \"switch_oob\"); return;"
        )
        out.append(f"{indent}}}")
        return
    if isinstance(term, TermTailCallGame):
        out.append(f"{indent}sub_{term.target_va:08x}(ctx, mem);")
        out.append(f"{indent}return;")
        return
    if isinstance(term, TermTailCallCRT):
        out.append(f"{indent}hle_crt_{term.target_va:08x}(ctx, mem);")
        out.append(f"{indent}return;")
        return
    if isinstance(term, TermTailCallIAT):
        out.append(f"{indent}hle_iat_call(ctx, mem, 0x{term.iat_va:08x}u);")
        out.append(f"{indent}return;")
        return
    if isinstance(term, TermTailCallIndirect):
        out.append(f"{indent}jump_indirect(ctx, mem, {_val_cpp(term.target, 32)});")
        out.append(f"{indent}return;")
        return
    if isinstance(term, TermTrap):
        out.append(f"{indent}recomp_detail::trap_halt(ctx, 0x{term.va:08x}u, \"{term.kind}\");")
        out.append(f"{indent}return;")
        return
    raise TypeError(term)


def emit_function_cpp(fn: IRFunction, emit_comments: bool = True) -> str:
    """Render one `IRFunction` into a complete C++20 function definition."""
    lines: list[str] = []
    kind_tag = "canonical" if fn.is_canonical else (".CRT$XCA init" if fn.entry_va >= 0x004E00D0 else ".data callback")
    lines.append(f"// {fn.name} | subsystem={fn.subsystem} | {kind_tag} | {len(fn.blocks)} blocks | {fn.insn_count} insns")
    lines.append(f"void {fn.name}(CpuContext& ctx, GuestMemory& mem) {{")

    needed_labels = _collect_needed_labels(fn)
    order = fn.block_order
    for idx, b_va in enumerate(order):
        blk: IRBlock = fn.blocks[b_va]
        next_va = order[idx + 1] if idx + 1 < len(order) else None
        if b_va in needed_labels:
            lines.append(f"bb_{b_va:08x}: {{")
        else:
            lines.append("{")
        for st in blk.stmts:
            _emit_stmt_lines(st, lines, "    ", emit_comments)
        _emit_term_lines(blk.term, next_va, lines, "    ")
        lines.append("}")

    lines.append("}")
    return "\n".join(lines)


# ---------------------------------------------------------------------------
# Game IAT Scanner (all 184 game .text IAT slots -> DLL!Name)
# ---------------------------------------------------------------------------

def collect_game_iat_entries(pcfg: ProgramCFG, pe: PEBinary) -> list[tuple[int, dict, bool]]:
    """Collect all game IAT VAs referenced in game `.text` (returns sorted `(va, info, reachable)`)."""
    all_iat_vas: set[int] = set(pcfg.used_iat_vas)
    # Also scan unreachable game `.text` regions (e.g. 0x004de358..0x004df020) for 4-byte IAT addresses
    # not already accounted for by switch jump tables, so dead win32 stubs still appear in `iat_table.h`.
    sec = next(s for s in pe.pe.sections if s.Name.rstrip(b"\x00").decode("ascii", "replace") == ".text")
    sec_va = pe.image_base + sec.VirtualAddress
    raw = pe.read_bytes(sec_va, pe.text_end - sec_va)
    game_end = sec_va + min(len(raw), 0x004DF020 - sec_va)
    for off in range(0, (game_end - sec_va) - 3):
        va = sec_va + off
        if va in pcfg.jump_table_bytes:
            continue
        val = struct.unpack_from("<I", raw, off)[0]
        if val in pe.iat:
            all_iat_vas.add(val)

    return [(va, pe.iat[va], va in pcfg.used_iat_vas) for va in sorted(all_iat_vas)]


# ---------------------------------------------------------------------------
# Header, Dispatch & Shard Emitters
# ---------------------------------------------------------------------------

def _emit_recomp_funcs_header(ir_funcs: dict[int, IRFunction]) -> str:
    parts: list[str] = [
        "#pragma once",
        "",
        "// Auto-generated by mbaacc-recomp-ios/recompiler/cpp_emitter.py — DO NOT EDIT",
        "",
        _RECOMP_DETAIL_HEADER,
        "",
        "namespace mbaa_recomp {",
        "",
    ]
    for va in sorted(ir_funcs.keys()):
        fn = ir_funcs[va]
        tag = "" if fn.is_canonical else (" // [.CRT$XCA init]" if va >= 0x004E00D0 else " // [.data callback]")
        parts.append(f"void {fn.name}(CpuContext& ctx, GuestMemory& mem);{tag}")
    parts.append("")
    parts.append("} // namespace mbaa_recomp")
    parts.append("")
    return "\n".join(parts)


def _emit_iat_table_header(iat_entries: list[tuple[int, dict, bool]]) -> str:
    lines: list[str] = [
        "#pragma once",
        "",
        "// Auto-generated by mbaacc-recomp-ios/recompiler/cpp_emitter.py — DO NOT EDIT",
        "",
        "#include <cstddef>",
        "#include <cstdint>",
        "#include <string_view>",
        "",
        "namespace mbaa_recomp {",
        "",
        "struct IatEntryInfo {",
        "    uint32_t va;",
        "    std::string_view dll;",
        "    std::string_view name;",
        "    std::string_view qname;",
        "    bool reachable_in_cfg;",
        "};",
        "",
        f"inline constexpr IatEntryInfo kGameIatTable[{len(iat_entries)}] = {{",
    ]
    for va, info, reach in iat_entries:
        dll = info["dll"].replace("\\", "\\\\").replace('"', '\\"')
        name = info["name"].replace("\\", "\\\\").replace('"', '\\"')
        qname = info["qname"].replace("\\", "\\\\").replace('"', '\\"')
        lines.append(
            f'    {{0x{va:08x}u, "{dll}", "{name}", "{qname}", {"true" if reach else "false"}}},'
        )
    lines.extend([
        "};",
        "",
        f"inline constexpr size_t kGameIatCount = {len(iat_entries)}u;",
        "",
        "} // namespace mbaa_recomp",
        "",
    ])
    return "\n".join(lines)


def _emit_dispatch_cpp(pcfg: ProgramCFG, ir_funcs: dict[int, IRFunction]) -> str:
    sorted_vas = sorted(ir_funcs.keys())
    lines: list[str] = [
        "// Auto-generated by mbaacc-recomp-ios/recompiler/cpp_emitter.py — DO NOT EDIT",
        f"// Registers {len(sorted_vas)} functions ({len(pcfg.canonical_vas)} canonical + "
        f"{len(pcfg.extra_callback_vas)} .data callbacks + {len(pcfg.crt_init_vas)} .CRT$XCA initializers).",
        f"// Covers {len(pcfg.vtable_slot_vas)} unique vtable method slots (190 vtables) and "
        f"{len(pcfg.func_ptr_vas)} func_ptr_imm callbacks.",
        "",
        '#include "recomp_funcs.h"',
        '#include "iat_table.h"',
        "",
        "namespace mbaa_recomp {",
        "",
        "void register_recomp_functions() {",
        f"    // Total registered VA -> C++ function mappings: {len(sorted_vas)}",
        f"    (void)kGameIatCount;",
    ]
    for va in sorted_vas:
        lines.append(f"    register_function(0x{va:08x}u, &{ir_funcs[va].name});")
    lines.extend([
        "}",
        "",
        "} // namespace mbaa_recomp",
        "",
    ])
    return "\n".join(lines)


def _emit_shard_cpp(filename: str, funcs: list[IRFunction], emit_comments: bool) -> str:
    lines: list[str] = [
        f"// Auto-generated C++20 shard: {filename} ({len(funcs)} functions) — DO NOT EDIT",
        "",
        '#include "recomp_funcs.h"',
        "",
        "#if defined(__clang__)",
        "#pragma clang diagnostic push",
        '#pragma clang diagnostic ignored "-Wunused-parameter"',
        "#elif defined(__GNUC__)",
        "#pragma GCC diagnostic push",
        '#pragma GCC diagnostic ignored "-Wunused-parameter"',
        "#endif",
        "",
        "namespace mbaa_recomp {",
        "",
    ]
    for fn in funcs:
        lines.append(emit_function_cpp(fn, emit_comments=emit_comments))
        lines.append("")
    lines.extend([
        "} // namespace mbaa_recomp",
        "",
        "#if defined(__clang__)",
        "#pragma clang diagnostic pop",
        "#elif defined(__GNUC__)",
        "#pragma GCC diagnostic pop",
        "#endif",
        "",
    ])
    return "\n".join(lines)


def emit_program(
    pcfg: ProgramCFG,
    ir_funcs: dict[int, IRFunction],
    out_dir: Path,
    pe: PEBinary | None = None,
    emit_comments: bool = True,
) -> EmitResult:
    """Emit all `build_gen/` headers, 12 `.cpp` shards, and `gen_manifest.json`."""
    out_dir.mkdir(parents=True, exist_ok=True)
    if pe is None:
        pe = PEBinary(pcfg.exe_path)

    # Bucket lifted functions into their exact CMake target .cpp files
    by_shard: dict[str, list[IRFunction]] = {s: [] for s in ALL_SHARD_FILES if s != "gen_dispatch.cpp"}
    for va in sorted(ir_funcs.keys()):
        fn = ir_funcs[va]
        shard = SUBSYSTEM_SHARDS.get(fn.subsystem, "gen_core.cpp")
        by_shard[shard].append(fn)

    written: list[str] = []

    def write_out(rel_name: str, content: str) -> None:
        p = out_dir / rel_name
        p.write_text(content, encoding="utf-8", newline="\n")
        written.append(str(p))

    write_out("recomp_funcs.h", _emit_recomp_funcs_header(ir_funcs))
    iat_entries = collect_game_iat_entries(pcfg, pe)
    write_out("iat_table.h", _emit_iat_table_header(iat_entries))

    shard_counts: dict[str, int] = {}
    for shard_name in ALL_SHARD_FILES:
        if shard_name == "gen_dispatch.cpp":
            write_out(shard_name, _emit_dispatch_cpp(pcfg, ir_funcs))
            shard_counts[shard_name] = 0
        else:
            funcs = by_shard[shard_name]
            write_out(shard_name, _emit_shard_cpp(shard_name, funcs, emit_comments=emit_comments))
            shard_counts[shard_name] = len(funcs)

    unhandled_total = sum(len(fn.unhandled) for fn in ir_funcs.values())
    manifest = {
        "schema_version": 1,
        "artifact": str(pcfg.exe_path),
        "canonical_functions": len(pcfg.canonical_vas),
        "extra_data_callbacks": len(pcfg.extra_callback_vas),
        "crt_xca_initializers": len(pcfg.crt_init_vas),
        "total_emitted_functions": len(ir_funcs),
        "total_blocks": pcfg.total_blocks,
        "total_instructions": pcfg.total_insns,
        "switch_tables": pcfg.total_switch_tables,
        "jump_table_bytes": len(pcfg.jump_table_bytes),
        "unhandled_instructions": unhandled_total,
        "unresolved_targets": pcfg.unresolved_count,
        "decode_errors": pcfg.decode_error_count,
        "used_iat_vas_cfg": len(pcfg.used_iat_vas),
        "game_iat_table_count": len(iat_entries),
        "used_crt_vas": len(pcfg.used_crt_vas),
        "vtable_slots_covered": len(pcfg.vtable_slot_vas),
        "func_ptrs_covered": len(pcfg.func_ptr_vas),
        "shards": shard_counts,
        "files": [Path(w).name for w in written] + ["gen_manifest.json"],
    }
    manifest_path = out_dir / "gen_manifest.json"
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8", newline="\n")
    written.append(str(manifest_path))

    return EmitResult(
        out_dir=out_dir,
        files_written=written,
        function_count=len(ir_funcs),
        canonical_count=len(pcfg.canonical_vas),
        extra_callback_count=len(pcfg.extra_callback_vas),
        crt_init_count=len(pcfg.crt_init_vas),
        iat_count=len(iat_entries),
        shard_counts=shard_counts,
        manifest_path=manifest_path,
    )
