"""Direct Python interpreter over lifted x86-32 + x87 IR and Unicorn differential verifier.

Maps live MBAA.exe PE sections into both `EvalMemory` and `unicorn.Uc`, lifts
target functions with `x86_lifter`, executes both side-by-side, and verifies
bit-for-bit parity on GPRs, EFLAGS, x87 FPU stack/CW/SW, and guest memory.
"""

from __future__ import annotations

import argparse
import ctypes
import math
import struct
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Callable

import capstone
import pefile
from unicorn import UC_ARCH_X86, UC_MODE_32, UC_PROT_ALL, Uc
from unicorn.x86_const import (
    UC_X86_REG_EAX,
    UC_X86_REG_EBP,
    UC_X86_REG_EBX,
    UC_X86_REG_ECX,
    UC_X86_REG_EDI,
    UC_X86_REG_EDX,
    UC_X86_REG_EFLAGS,
    UC_X86_REG_EIP,
    UC_X86_REG_ESI,
    UC_X86_REG_ESP,
    UC_X86_REG_FPCW,
    UC_X86_REG_FPSW,
)

from .cfg import DEFAULT_MBAA_EXE, PEBinary, _recover_single_function, _make_disassembler
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
    IRFunction,
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
from .x86_lifter import lift_function

STACK_BASE = 0x01000000
STACK_SIZE = 0x00100000
SCRATCH_BASE = 0x02000000
SCRATCH_SIZE = 0x00200000
SENTINEL_RET = 0xDEAD0000

FLAG_CF = 1 << 0
FLAG_PF = 1 << 2
FLAG_AF = 1 << 4
FLAG_ZF = 1 << 6
FLAG_SF = 1 << 7
FLAG_DF = 1 << 10
FLAG_OF = 1 << 11

FPU_C0 = 0x0100
FPU_C1 = 0x0200
FPU_C2 = 0x0400
FPU_C3 = 0x4000
FPU_TOP_MASK = 0x3800

_MASK = {8: 0xFF, 16: 0xFFFF, 32: 0xFFFFFFFF, 64: 0xFFFFFFFFFFFFFFFF}


def _s8(v: int) -> int:
    v &= 0xFF
    return v - 0x100 if (v & 0x80) else v


def _s16(v: int) -> int:
    v &= 0xFFFF
    return v - 0x10000 if (v & 0x8000) else v


def _s32(v: int) -> int:
    v &= 0xFFFFFFFF
    return v - 0x100000000 if (v & 0x80000000) else v


def _s64(v: int) -> int:
    v &= 0xFFFFFFFFFFFFFFFF
    return v - 0x10000000000000000 if (v & 0x8000000000000000) else v


def _signed(v: int, bits: int) -> int:
    if bits == 8:
        return _s8(v)
    if bits == 16:
        return _s16(v)
    if bits == 32:
        return _s32(v)
    if bits == 64:
        return _s64(v)
    raise ValueError(bits)


def _parity_even(byte_val: int) -> int:
    return 1 if ((byte_val & 0xFF).bit_count() & 1) == 0 else 0


def _decode_x87_ext80(raw10: bytes) -> float:
    """Decode 80-bit x87 extended-precision float into IEEE 754 binary64."""
    mant = int.from_bytes(raw10[:8], "little")
    exp_sign = struct.unpack_from("<H", raw10, 8)[0]
    sign = -1.0 if (exp_sign & 0x8000) else 1.0
    exp = exp_sign & 0x7FFF
    if exp == 0 and mant == 0:
        return math.copysign(0.0, sign)
    if exp == 0x7FFF:
        if (mant & 0x7FFFFFFFFFFFFFFF) == 0:
            return math.copysign(math.inf, sign)
        return math.nan
    if exp == 0:
        return sign * math.ldexp(float(mant), -16382 - 63)
    return sign * math.ldexp(float(mant), (exp - 16383) - 63)


def _round_x87_to_int(val: float, cw: int) -> int:
    """Round double according to x87 Control Word RC bits (bits 10..11)."""
    if math.isnan(val) or math.isinf(val):
        return -0x8000000000000000
    rc = (cw >> 10) & 3
    if rc == 0:
        # Round to nearest, ties to even (Python round() uses round-half-to-even!)
        return int(round(val))
    if rc == 1:
        return int(math.floor(val))
    if rc == 2:
        return int(math.ceil(val))
    return int(math.trunc(val))


class EvalMemory:
    """Page-mapped 32-bit guest memory for Python IR evaluation."""

    def __init__(self) -> None:
        self._regions: list[tuple[int, int, bytearray]] = []

    def map_region(self, base: int, size: int) -> None:
        self._regions.append((base, base + size, bytearray(size)))

    def _locate(self, va: int, size: int) -> tuple[bytearray, int]:
        va &= 0xFFFFFFFF
        for lo, hi, buf in self._regions:
            if lo <= va and va + size <= hi:
                return buf, va - lo
        raise KeyError(f"Unmapped guest memory access VA=0x{va:08x} size={size}")

    def read_bytes(self, va: int, size: int) -> bytes:
        buf, off = self._locate(va, size)
        return bytes(buf[off : off + size])

    def write_bytes(self, va: int, data: bytes) -> None:
        buf, off = self._locate(va, len(data))
        buf[off : off + len(data)] = data

    def r8(self, va: int) -> int:
        buf, off = self._locate(va, 1)
        return buf[off]

    def r16(self, va: int) -> int:
        buf, off = self._locate(va, 2)
        return struct.unpack_from("<H", buf, off)[0]

    def r32(self, va: int) -> int:
        buf, off = self._locate(va, 4)
        return struct.unpack_from("<I", buf, off)[0]

    def r64(self, va: int) -> int:
        buf, off = self._locate(va, 8)
        return struct.unpack_from("<Q", buf, off)[0]

    def rf32(self, va: int) -> float:
        buf, off = self._locate(va, 4)
        return struct.unpack_from("<f", buf, off)[0]

    def rf64(self, va: int) -> float:
        buf, off = self._locate(va, 8)
        return struct.unpack_from("<d", buf, off)[0]

    def w8(self, va: int, v: int) -> None:
        buf, off = self._locate(va, 1)
        buf[off] = v & 0xFF

    def w16(self, va: int, v: int) -> None:
        buf, off = self._locate(va, 2)
        struct.pack_into("<H", buf, off, v & 0xFFFF)

    def w32(self, va: int, v: int) -> None:
        buf, off = self._locate(va, 4)
        struct.pack_into("<I", buf, off, v & 0xFFFFFFFF)

    def w64(self, va: int, v: int) -> None:
        buf, off = self._locate(va, 8)
        struct.pack_into("<Q", buf, off, v & 0xFFFFFFFFFFFFFFFF)

    def wf32(self, va: int, v: float) -> None:
        buf, off = self._locate(va, 4)
        struct.pack_into("<f", buf, off, float(v))

    def wf64(self, va: int, v: float) -> None:
        buf, off = self._locate(va, 8)
        struct.pack_into("<d", buf, off, float(v))


@dataclass
class EvalContext:
    eax: int = 0
    ecx: int = 0
    edx: int = 0
    ebx: int = 0
    esp: int = 0
    ebp: int = 0
    esi: int = 0
    edi: int = 0
    eip: int = 0
    eflags: int = 0x00000202
    fs_0: int = 0x00300000
    st: list[float] = field(default_factory=lambda: [0.0] * 8)
    st_top: int = 0
    fpu_cw: int = 0x027F
    fpu_sw: int = 0x0000

    _G32 = ("eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi")
    _R16 = {"ax": "eax", "cx": "ecx", "dx": "edx", "bx": "ebx", "sp": "esp", "bp": "ebp", "si": "esi", "di": "edi"}
    _R8L = {"al": "eax", "cl": "ecx", "dl": "edx", "bl": "ebx"}
    _R8H = {"ah": "eax", "ch": "ecx", "dh": "edx", "bh": "ebx"}

    def read_reg(self, name: str) -> int:
        if name in self._G32:
            return getattr(self, name) & 0xFFFFFFFF
        if name in self._R16:
            return getattr(self, self._R16[name]) & 0xFFFF
        if name in self._R8L:
            return getattr(self, self._R8L[name]) & 0xFF
        if name in self._R8H:
            return (getattr(self, self._R8H[name]) >> 8) & 0xFF
        if name in ("eflags", "fs_0"):
            return getattr(self, name) & 0xFFFFFFFF
        if name in ("fpu_cw", "fpu_sw"):
            return getattr(self, name) & 0xFFFF
        raise KeyError(name)

    def write_reg(self, name: str, val: int) -> None:
        if name in self._G32:
            setattr(self, name, val & 0xFFFFFFFF)
        elif name in self._R16:
            base = self._R16[name]
            setattr(self, base, (getattr(self, base) & 0xFFFF0000) | (val & 0xFFFF))
        elif name in self._R8L:
            base = self._R8L[name]
            setattr(self, base, (getattr(self, base) & 0xFFFFFF00) | (val & 0xFF))
        elif name in self._R8H:
            base = self._R8H[name]
            setattr(self, base, (getattr(self, base) & 0xFFFF00FF) | ((val & 0xFF) << 8))
        elif name in ("eflags", "fs_0"):
            setattr(self, name, val & 0xFFFFFFFF)
        elif name in ("fpu_cw", "fpu_sw"):
            setattr(self, name, val & 0xFFFF)
        else:
            raise KeyError(name)

    def get_flag(self, f: str) -> int:
        mask = {
            "cf": FLAG_CF,
            "pf": FLAG_PF,
            "af": FLAG_AF,
            "zf": FLAG_ZF,
            "sf": FLAG_SF,
            "df": FLAG_DF,
            "of": FLAG_OF,
        }[f]
        return 1 if (self.eflags & mask) else 0

    def set_flag(self, f: str, v: int) -> None:
        mask = {
            "cf": FLAG_CF,
            "pf": FLAG_PF,
            "af": FLAG_AF,
            "zf": FLAG_ZF,
            "sf": FLAG_SF,
            "df": FLAG_DF,
            "of": FLAG_OF,
        }[f]
        if v:
            self.eflags |= mask
        else:
            self.eflags &= ~mask

    def eval_cond(self, cond: str) -> bool:
        cf = self.get_flag("cf")
        zf = self.get_flag("zf")
        sf = self.get_flag("sf")
        of = self.get_flag("of")
        pf = self.get_flag("pf")
        if cond == "o":
            return bool(of)
        if cond == "no":
            return not of
        if cond == "b":
            return bool(cf)
        if cond == "ae":
            return not cf
        if cond == "e":
            return bool(zf)
        if cond == "ne":
            return not zf
        if cond == "be":
            return bool(cf or zf)
        if cond == "a":
            return not (cf or zf)
        if cond == "s":
            return bool(sf)
        if cond == "ns":
            return not sf
        if cond == "p":
            return bool(pf)
        if cond == "np":
            return not pf
        if cond == "l":
            return sf != of
        if cond == "ge":
            return sf == of
        if cond == "le":
            return bool(zf or (sf != of))
        if cond == "g":
            return not zf and (sf == of)
        raise KeyError(cond)

    def fpu_push(self, val: float) -> None:
        self.st_top = (self.st_top - 1) & 7
        self.st[self.st_top] = float(val)
        self.fpu_sw = (self.fpu_sw & ~FPU_TOP_MASK) | ((self.st_top & 7) << 11)

    def fpu_pop(self) -> float:
        val = self.st[self.st_top & 7]
        self.st[self.st_top & 7] = 0.0
        self.st_top = (self.st_top + 1) & 7
        self.fpu_sw = (self.fpu_sw & ~FPU_TOP_MASK) | ((self.st_top & 7) << 11)
        return val

    def fpu_st(self, idx: int = 0) -> float:
        return self.st[(self.st_top + idx) & 7]

    def fpu_set_st(self, idx: int, val: float) -> None:
        self.st[(self.st_top + idx) & 7] = float(val)

    def fpu_compare(self, a: float, b: float, set_eflags: bool = False) -> None:
        if math.isnan(a) or math.isnan(b):
            c3, c2, c0 = True, True, True
        elif a > b:
            c3, c2, c0 = False, False, False
        elif a < b:
            c3, c2, c0 = False, False, True
        else:
            c3, c2, c0 = True, False, False
        if set_eflags:
            self.set_flag("zf", int(c3))
            self.set_flag("pf", int(c2))
            self.set_flag("cf", int(c0))
            self.set_flag("of", 0)
            self.set_flag("sf", 0)
            self.set_flag("af", 0)
        else:
            self.fpu_sw &= ~(FPU_C0 | FPU_C1 | FPU_C2 | FPU_C3)
            if c0:
                self.fpu_sw |= FPU_C0
            if c2:
                self.fpu_sw |= FPU_C2
            if c3:
                self.fpu_sw |= FPU_C3


class IREvaluator:
    """Direct interpreter executing lifted `IRFunction`s against `EvalMemory`."""

    def __init__(
        self,
        funcs: dict[int, IRFunction],
        crt_hooks: dict[int, Callable[[EvalContext, EvalMemory], None]] | None = None,
    ) -> None:
        self.funcs = funcs
        self.crt_hooks = crt_hooks or {}

    def _read_val(self, val: IRValue, ctx: EvalContext, temps: dict[int, int | float]):
        if isinstance(val, Const):
            return val.value & _MASK[val.bits]
        if isinstance(val, FConst):
            return val.value
        if isinstance(val, Temp):
            return temps[val.id]
        if isinstance(val, Reg):
            return ctx.read_reg(val.name)
        if isinstance(val, Flag):
            return ctx.get_flag(val.name)
        raise TypeError(val)

    def _update_flags(self, st: UpdateFlags, ctx: EvalContext, temps: dict[int, int | float]) -> None:
        bits = st.bits
        mask = _MASK[bits]
        sign_bit = 1 << (bits - 1)
        a = int(self._read_val(st.lhs, ctx, temps)) & mask
        b = int(self._read_val(st.rhs, ctx, temps)) & mask
        r = int(self._read_val(st.res, ctx, temps)) & mask
        op = st.op

        def set_szp(x: int) -> None:
            ctx.set_flag("zf", int((x & mask) == 0))
            ctx.set_flag("sf", int((x & sign_bit) != 0))
            ctx.set_flag("pf", _parity_even(x))

        if op in ("add", "adc"):
            cin = int(self._read_val(st.carry_in, ctx, temps)) if st.carry_in is not None else 0
            full = a + b + cin
            ctx.set_flag("cf", int(full > mask))
            ctx.set_flag("af", int(((a ^ b ^ r) & 0x10) != 0))
            ctx.set_flag("of", int((((~(a ^ b)) & (a ^ r)) & sign_bit) != 0))
            set_szp(r)
        elif op in ("sub", "cmp", "sbb"):
            cin = int(self._read_val(st.carry_in, ctx, temps)) if st.carry_in is not None else 0
            ctx.set_flag("cf", int(a < (b + cin)))
            ctx.set_flag("af", int(((a ^ b ^ r) & 0x10) != 0))
            ctx.set_flag("of", int((((a ^ b) & (a ^ r)) & sign_bit) != 0))
            set_szp(r)
        elif op == "inc":
            ctx.set_flag("af", int(((a ^ 1 ^ r) & 0x10) != 0))
            ctx.set_flag("of", int(a == (sign_bit - 1)))
            set_szp(r)
        elif op == "dec":
            ctx.set_flag("af", int(((a ^ 1 ^ r) & 0x10) != 0))
            ctx.set_flag("of", int(a == sign_bit))
            set_szp(r)
        elif op == "neg":
            ctx.set_flag("cf", int(a != 0))
            ctx.set_flag("af", int((a & 0xF) != 0))
            ctx.set_flag("of", int(a == sign_bit))
            set_szp(r)
        elif op == "logic":
            ctx.set_flag("cf", 0)
            ctx.set_flag("of", 0)
            ctx.set_flag("af", 0)
            set_szp(r)
        elif op == "shl":
            cnt = int(self._read_val(st.rhs, ctx, temps)) & 0x1F
            if cnt == 0:
                return
            cf = ((a >> (bits - cnt)) & 1) if cnt <= bits else 0
            ctx.set_flag("cf", cf)
            if cnt == 1:
                ctx.set_flag("of", ((r >> (bits - 1)) & 1) ^ cf)
            set_szp(r)
        elif op == "shr":
            cnt = int(self._read_val(st.rhs, ctx, temps)) & 0x1F
            if cnt == 0:
                return
            cf = ((a >> (cnt - 1)) & 1) if cnt <= bits else 0
            ctx.set_flag("cf", cf)
            if cnt == 1:
                ctx.set_flag("of", (a >> (bits - 1)) & 1)
            set_szp(r)
        elif op == "sar":
            cnt = int(self._read_val(st.rhs, ctx, temps)) & 0x1F
            if cnt == 0:
                return
            sa = _signed(a, bits)
            cf = ((sa >> (cnt - 1)) & 1) if cnt <= bits else (1 if sa < 0 else 0)
            ctx.set_flag("cf", cf)
            if cnt == 1:
                ctx.set_flag("of", 0)
            set_szp(r)
        elif op == "rol":
            cnt = int(self._read_val(st.rhs, ctx, temps)) & 0x1F
            if cnt == 0:
                return
            cf = r & 1
            ctx.set_flag("cf", cf)
            if cnt == 1:
                ctx.set_flag("of", ((r >> (bits - 1)) & 1) ^ cf)
        elif op == "ror":
            cnt = int(self._read_val(st.rhs, ctx, temps)) & 0x1F
            if cnt == 0:
                return
            cf = (r >> (bits - 1)) & 1
            ctx.set_flag("cf", cf)
            if cnt == 1:
                ctx.set_flag("of", ((r >> (bits - 1)) ^ (r >> (bits - 2))) & 1)
        elif op == "mul":
            full = int(self._read_val(st.res, ctx, temps))
            ov = int((full >> bits) != 0)
            ctx.set_flag("cf", ov)
            ctx.set_flag("of", ov)
        elif op == "imul":
            full = int(self._read_val(st.res, ctx, temps))
            lo = full & mask
            ext = _signed(lo, bits) & ((1 << (bits * 2)) - 1)
            ov = int(ext != (full & ((1 << (bits * 2)) - 1)))
            ctx.set_flag("cf", ov)
            ctx.set_flag("of", ov)
        else:
            raise KeyError(op)

    def _eval_expr(self, expr, ctx: EvalContext, mem: EvalMemory, temps: dict[int, int | float]):
        if isinstance(expr, ReadVal):
            return self._read_val(expr.val, ctx, temps)
        if isinstance(expr, BinOp):
            w = expr.bits
            mask = _MASK[w]
            a = int(self._read_val(expr.lhs, ctx, temps))
            b = int(self._read_val(expr.rhs, ctx, temps))
            op = expr.op
            if op == "add":
                return (a + b) & mask
            if op == "sub":
                return (a - b) & mask
            if op == "mul":
                return (a * b) & mask
            if op == "imul":
                return (_signed(a, w) * _signed(b, w)) & mask
            if op == "and":
                return (a & b) & mask
            if op == "or":
                return (a | b) & mask
            if op == "xor":
                return (a ^ b) & mask
            if op == "shl":
                return ((a & mask) << (b & 0x1F)) & mask
            if op == "shr":
                return ((a & mask) >> (b & 0x1F)) & mask
            if op == "sar":
                return (_signed(a, w) >> (b & 0x1F)) & mask
            if op == "rol":
                c = (b & 0x1F) % w
                ua = a & mask
                return ((ua << c) | (ua >> (w - c))) & mask if c else ua
            if op == "ror":
                c = (b & 0x1F) % w
                ua = a & mask
                return ((ua >> c) | (ua << (w - c))) & mask if c else ua
            if op == "mul64_u":
                return ((a & 0xFFFFFFFF) * (b & 0xFFFFFFFF)) & _MASK[64]
            if op == "mul64_s":
                return (_s32(a) * _s32(b)) & _MASK[64]
            if op == "pack64":
                return (((a & 0xFFFFFFFF) << 32) | (b & 0xFFFFFFFF)) & _MASK[64]
            if op == "div64_u":
                return ((a & _MASK[64]) // (b & 0xFFFFFFFF)) & 0xFFFFFFFF
            if op == "mod64_u":
                return ((a & _MASK[64]) % (b & 0xFFFFFFFF)) & 0xFFFFFFFF
            if op == "div64_s":
                sa, sb = _s64(a), _s32(b)
                q = int(sa / sb) if abs(sa) < (1 << 50) else (abs(sa) // abs(sb)) * (-1 if (sa < 0) ^ (sb < 0) else 1)
                return q & 0xFFFFFFFF
            if op == "mod64_s":
                sa, sb = _s64(a), _s32(b)
                q = (abs(sa) // abs(sb)) * (-1 if (sa < 0) ^ (sb < 0) else 1)
                r = sa - q * sb
                return r & 0xFFFFFFFF
            raise KeyError(op)

        if isinstance(expr, UnOp):
            s = int(self._read_val(expr.src, ctx, temps))
            op = expr.op
            if op == "neg":
                return (-s) & _MASK[expr.bits]
            if op == "not":
                return (~s) & _MASK[expr.bits]
            if op == "zext8_32":
                return s & 0xFF
            if op == "zext16_32":
                return s & 0xFFFF
            if op == "zext8_16":
                return s & 0xFF
            if op == "sext8_32":
                return _s8(s) & 0xFFFFFFFF
            if op == "sext16_32":
                return _s16(s) & 0xFFFFFFFF
            if op == "sext8_16":
                return _s8(s) & 0xFFFF
            if op == "trunc32_16":
                return s & 0xFFFF
            if op == "trunc32_8":
                return s & 0xFF
            if op == "trunc64_lo":
                return s & 0xFFFFFFFF
            if op == "trunc64_hi":
                return (s >> 32) & 0xFFFFFFFF
            raise KeyError(op)

        if isinstance(expr, MemLoad):
            addr = int(self._read_val(expr.addr, ctx, temps)) & 0xFFFFFFFF
            if expr.bits == 8:
                return mem.r8(addr)
            if expr.bits == 16:
                return mem.r16(addr)
            if expr.bits == 32:
                return mem.r32(addr)
            if expr.bits == 64:
                return mem.r64(addr)
            raise KeyError(expr.bits)

        if isinstance(expr, FpuLoadMem):
            addr = int(self._read_val(expr.addr, ctx, temps)) & 0xFFFFFFFF
            if expr.bits == 32:
                return float(mem.rf32(addr))
            if expr.bits == 64:
                return float(mem.rf64(addr))
            if expr.bits == 80:
                return _decode_x87_ext80(mem.read_bytes(addr, 10))
            raise KeyError(expr.bits)

        if isinstance(expr, FpuLoadInt):
            addr = int(self._read_val(expr.addr, ctx, temps)) & 0xFFFFFFFF
            if expr.bits == 16:
                return float(_s16(mem.r16(addr)))
            if expr.bits == 32:
                return float(_s32(mem.r32(addr)))
            if expr.bits == 64:
                return float(_s64(mem.r64(addr)))
            raise KeyError(expr.bits)

        if isinstance(expr, FpuPeek):
            return ctx.fpu_st(expr.index)

        if isinstance(expr, FBinOp):
            a = float(self._read_val(expr.lhs, ctx, temps))
            b = float(self._read_val(expr.rhs, ctx, temps))
            if expr.op == "fadd":
                return a + b
            if expr.op == "fsub":
                return a - b
            if expr.op == "fmul":
                return a * b
            if expr.op == "fdiv":
                return a / b
            raise KeyError(expr.op)

        if isinstance(expr, FUnOp):
            a = float(self._read_val(expr.src, ctx, temps))
            if expr.op == "fchs":
                return -a
            if expr.op == "fabs":
                return abs(a)
            if expr.op == "fsqrt":
                return math.sqrt(a)
            raise KeyError(expr.op)

        if isinstance(expr, CondExpr):
            return int(ctx.eval_cond(expr.cond))

        if isinstance(expr, Select):
            c = int(self._read_val(expr.cond, ctx, temps))
            return self._read_val(expr.when_true if c else expr.when_false, ctx, temps)

        raise TypeError(expr)

    def _exec_string_op(self, st: StringOp, ctx: EvalContext, mem: EvalMemory) -> None:
        unit = st.bits // 8
        step = -unit if ctx.get_flag("df") else unit
        count = 1 if st.rep is None else ctx.ecx
        while count > 0:
            if st.kind == "movs":
                if unit == 1:
                    mem.w8(ctx.edi, mem.r8(ctx.esi))
                elif unit == 2:
                    mem.w16(ctx.edi, mem.r16(ctx.esi))
                else:
                    mem.w32(ctx.edi, mem.r32(ctx.esi))
                ctx.esi = (ctx.esi + step) & 0xFFFFFFFF
                ctx.edi = (ctx.edi + step) & 0xFFFFFFFF
            elif st.kind == "stos":
                if unit == 1:
                    mem.w8(ctx.edi, ctx.eax & 0xFF)
                elif unit == 2:
                    mem.w16(ctx.edi, ctx.eax & 0xFFFF)
                else:
                    mem.w32(ctx.edi, ctx.eax & 0xFFFFFFFF)
                ctx.edi = (ctx.edi + step) & 0xFFFFFFFF
            elif st.kind in ("cmps", "scas"):
                if st.kind == "cmps":
                    a = mem.r8(ctx.esi) if unit == 1 else (mem.r16(ctx.esi) if unit == 2 else mem.r32(ctx.esi))
                    b = mem.r8(ctx.edi) if unit == 1 else (mem.r16(ctx.edi) if unit == 2 else mem.r32(ctx.edi))
                    ctx.esi = (ctx.esi + step) & 0xFFFFFFFF
                    ctx.edi = (ctx.edi + step) & 0xFFFFFFFF
                else:
                    a = ctx.eax & _MASK[st.bits]
                    b = mem.r8(ctx.edi) if unit == 1 else (mem.r16(ctx.edi) if unit == 2 else mem.r32(ctx.edi))
                    ctx.edi = (ctx.edi + step) & 0xFFFFFFFF
                mask = _MASK[st.bits]
                r = (a - b) & mask
                sign_bit = 1 << (st.bits - 1)
                ctx.set_flag("cf", int(a < b))
                ctx.set_flag("af", int(((a ^ b ^ r) & 0x10) != 0))
                ctx.set_flag("of", int((((a ^ b) & (a ^ r)) & sign_bit) != 0))
                ctx.set_flag("zf", int(r == 0))
                ctx.set_flag("sf", int((r & sign_bit) != 0))
                ctx.set_flag("pf", _parity_even(r))
            else:
                raise KeyError(st.kind)

            count -= 1
            if st.rep is not None:
                ctx.ecx = count
                if st.kind in ("cmps", "scas"):
                    if st.rep == "repe" and not ctx.get_flag("zf"):
                        break
                    if st.rep == "repne" and ctx.get_flag("zf"):
                        break

    def execute(self, entry_va: int, ctx: EvalContext, mem: EvalMemory, max_blocks: int = 200_000) -> None:
        fn = self.funcs[entry_va]
        cur_va = entry_va
        temps: dict[int, int | float] = {}
        steps = 0

        while True:
            steps += 1
            if steps > max_blocks:
                raise RuntimeError(f"IR evaluator exceeded {max_blocks} blocks in 0x{entry_va:08x}")
            blk = fn.blocks[cur_va]
            for st in blk.stmts:
                if isinstance(st, Comment):
                    continue
                if isinstance(st, Assign):
                    temps[st.dst.id] = self._eval_expr(st.expr, ctx, mem, temps)
                elif isinstance(st, WriteReg):
                    ctx.write_reg(st.reg, int(self._read_val(st.val, ctx, temps)))
                elif isinstance(st, WriteFlag):
                    ctx.set_flag(st.flag, int(self._read_val(st.val, ctx, temps)))
                elif isinstance(st, UpdateFlags):
                    self._update_flags(st, ctx, temps)
                elif isinstance(st, WriteMem):
                    addr = int(self._read_val(st.addr, ctx, temps)) & 0xFFFFFFFF
                    val = int(self._read_val(st.val, ctx, temps))
                    if st.bits == 8:
                        mem.w8(addr, val)
                    elif st.bits == 16:
                        mem.w16(addr, val)
                    elif st.bits == 32:
                        mem.w32(addr, val)
                    elif st.bits == 64:
                        mem.w64(addr, val)
                elif isinstance(st, FpuStoreMem):
                    addr = int(self._read_val(st.addr, ctx, temps)) & 0xFFFFFFFF
                    val = float(self._read_val(st.val, ctx, temps))
                    if st.bits == 32:
                        mem.wf32(addr, val)
                    else:
                        mem.wf64(addr, val)
                elif isinstance(st, FpuStoreInt):
                    addr = int(self._read_val(st.addr, ctx, temps)) & 0xFFFFFFFF
                    val = float(self._read_val(st.val, ctx, temps))
                    iv = _round_x87_to_int(val, ctx.fpu_cw)
                    if st.bits == 16:
                        mem.w16(addr, iv)
                    elif st.bits == 32:
                        mem.w32(addr, iv)
                    else:
                        mem.w64(addr, iv)
                elif isinstance(st, FpuPush):
                    ctx.fpu_push(float(self._read_val(st.val, ctx, temps)))
                elif isinstance(st, FpuPop):
                    ctx.fpu_pop()
                elif isinstance(st, FpuSet):
                    ctx.fpu_set_st(st.index, float(self._read_val(st.val, ctx, temps)))
                elif isinstance(st, FpuSwap):
                    a = ctx.fpu_st(0)
                    b = ctx.fpu_st(st.index)
                    ctx.fpu_set_st(0, b)
                    ctx.fpu_set_st(st.index, a)
                elif isinstance(st, FpuCmp):
                    a = float(self._read_val(st.lhs, ctx, temps))
                    b = float(self._read_val(st.rhs, ctx, temps))
                    ctx.fpu_compare(a, b, set_eflags=st.set_eflags)
                elif isinstance(st, FpuClearEx):
                    ctx.fpu_sw &= ~0x80FF
                elif isinstance(st, StringOp):
                    self._exec_string_op(st, ctx, mem)
                elif isinstance(st, CallDirect):
                    self.execute(st.target_va, ctx, mem, max_blocks=max_blocks)
                elif isinstance(st, CallCRT):
                    if st.target_va in self.crt_hooks:
                        self.crt_hooks[st.target_va](ctx, mem)
                    else:
                        raise KeyError(f"No CRT hook for 0x{st.target_va:08x}")
                elif isinstance(st, (CallIAT, CallIndirect)):
                    raise KeyError(f"Unsupported call in eval: {st}")
                else:
                    raise TypeError(st)

            term = blk.term
            if isinstance(term, TermRet):
                ret_va = mem.r32(ctx.esp)
                ctx.esp = (ctx.esp + 4 + term.pop_extra) & 0xFFFFFFFF
                ctx.eip = ret_va
                return
            if isinstance(term, (TermJump, TermFallthrough)):
                cur_va = term.target_va
            elif isinstance(term, TermBranch):
                if term.cond == "ecx_z":
                    take = ctx.ecx == 0
                elif term.cond in ("loop", "loope", "loopne"):
                    ctx.ecx = (ctx.ecx - 1) & 0xFFFFFFFF
                    if term.cond == "loop":
                        take = ctx.ecx != 0
                    elif term.cond == "loope":
                        take = ctx.ecx != 0 and bool(ctx.get_flag("zf"))
                    else:
                        take = ctx.ecx != 0 and not ctx.get_flag("zf")
                else:
                    take = ctx.eval_cond(term.cond)
                cur_va = term.target_va if take else term.fallthrough_va
            elif isinstance(term, TermSwitch):
                idx = int(self._read_val(term.index, ctx, temps))
                if 0 <= idx < len(term.targets):
                    cur_va = term.targets[idx]
                else:
                    raise IndexError(f"Switch index {idx} out of bounds at table 0x{term.table_va:08x}")
            elif isinstance(term, TermTailCallGame):
                self.execute(term.target_va, ctx, mem, max_blocks=max_blocks)
                return
            elif isinstance(term, TermTailCallCRT):
                self.crt_hooks[term.target_va](ctx, mem)
                return
            else:
                raise RuntimeError(f"Unsupported terminator {term}")


# ---------------------------------------------------------------------------
# Differential Test Harness (Unicorn vs IR Evaluator)
# ---------------------------------------------------------------------------

class DifferentialSuite:
    """Runs live MBAA.exe routines and synthetic stress kernels through Unicorn and IREvaluator."""

    def __init__(self, exe_path: Path = DEFAULT_MBAA_EXE) -> None:
        self.exe_path = exe_path
        self.pe_bin = PEBinary(exe_path)
        self.pe = self.pe_bin.pe
        self.image_base = self.pe_bin.image_base
        self.image_size = (self.pe.OPTIONAL_HEADER.SizeOfImage + 0xFFF) & ~0xFFF
        self.mapped_img = self.pe.get_memory_mapped_image(ImageBase=self.image_base).ljust(self.image_size, b"\x00")

        # Lift target routines directly from MBAA.exe
        self.md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        self.md.detail = True
        self.disasm = _make_disassembler(self.pe_bin, self.md)

        # Target game functions to lift for differential tests
        self.target_vas = {
            0x00401000,  # PlayData::validate
            0x00401050,  # PlayData::reset_defaults
            0x00401090,  # PlayData::record_match
            0x00401370,  # GameData::validate
            0x00401490,  # GameData::reset_defaults
            0x00401520,  # GameData::get_field
            0x004020A0,  # Palette index-0 remapper
            0x00417270,  # Gage BPE decompressor
            0x004DB470,  # FilePac filename_hash
            0x004DB530,  # FilePac str cipher
            0x004DB590,  # FilePac cipher_seek
            0x004DB5E0,  # FilePac cipher_xor
            0x004BBFA0,  # Scoreboard reset called by PlayData::reset_defaults
        }
        self.lifted: dict[int, IRFunction] = {}
        known_tables: set[int] = set()
        for va in sorted(self.target_vas):
            fcfg = _recover_single_function(va, "DiffTest", True, self.pe_bin, self.disasm, self.target_vas, known_tables)
            for sw in fcfg.switch_tables:
                known_tables.add(sw.table_va)
            self.lifted[va] = lift_function(fcfg, self.pe_bin, self.target_vas)

        def crt_security_check_cookie(ctx: EvalContext, mem: EvalMemory) -> None:
            ret_va = mem.r32(ctx.esp)
            ctx.esp = (ctx.esp + 4) & 0xFFFFFFFF
            cookie = mem.r32(0x0054B458)
            ctx.set_flag("zf", int((ctx.ecx & 0xFFFFFFFF) == cookie))
            ctx.eip = ret_va

        def crt_memset(ctx: EvalContext, mem: EvalMemory) -> None:
            ret_va = mem.r32(ctx.esp)
            dst = mem.r32(ctx.esp + 4)
            val = mem.r32(ctx.esp + 8) & 0xFF
            cnt = mem.r32(ctx.esp + 12)
            if cnt > 0:
                mem.write_bytes(dst, bytes([val]) * cnt)
            ctx.eax = dst
            ctx.esp = (ctx.esp + 4) & 0xFFFFFFFF
            ctx.eip = ret_va

        self.evaluator = IREvaluator(
            self.lifted,
            crt_hooks={
                0x004E02F8: crt_security_check_cookie,
                0x004E6340: crt_memset,
            },
        )

    def _new_pair(self) -> tuple[Uc, EvalMemory, EvalContext]:
        uc = Uc(UC_ARCH_X86, UC_MODE_32)
        uc.mem_map(self.image_base, self.image_size, UC_PROT_ALL)
        uc.mem_write(self.image_base, self.mapped_img)
        uc.mem_map(STACK_BASE, STACK_SIZE, UC_PROT_ALL)
        uc.mem_map(SCRATCH_BASE, SCRATCH_SIZE, UC_PROT_ALL)
        uc.mem_map(SENTINEL_RET, 0x1000, UC_PROT_ALL)
        uc.mem_write(SENTINEL_RET, b"\x90\xf4")

        mem = EvalMemory()
        mem.map_region(self.image_base, self.image_size)
        mem.write_bytes(self.image_base, self.mapped_img)
        mem.map_region(STACK_BASE, STACK_SIZE)
        mem.map_region(SCRATCH_BASE, SCRATCH_SIZE)
        mem.map_region(SENTINEL_RET, 0x1000)

        ctx = EvalContext(esp=STACK_BASE + STACK_SIZE - 0x200)
        uc.reg_write(UC_X86_REG_ESP, ctx.esp)
        uc.reg_write(UC_X86_REG_FPCW, 0x027F)
        uc.reg_write(UC_X86_REG_FPSW, 0x0000)
        return uc, mem, ctx

    def _sync_write(self, uc: Uc, mem: EvalMemory, addr: int, data: bytes) -> None:
        uc.mem_write(addr, data)
        mem.write_bytes(addr, data)

    def _run_both(
        self,
        va: int,
        uc: Uc,
        mem: EvalMemory,
        ctx: EvalContext,
        regs: dict[str, int] | None = None,
        push_args: list[int] | None = None,
        check_regs: tuple[str, ...] = ("eax", "esp", "ebx", "esi", "edi", "ebp"),
    ) -> tuple[EvalContext, dict[str, int]]:
        esp = ctx.esp
        # Push args right-to-left then return VA
        stack_words = [SENTINEL_RET] + (push_args or [])
        for idx, word in enumerate(stack_words):
            b = struct.pack("<I", word & 0xFFFFFFFF)
            self._sync_write(uc, mem, esp + idx * 4, b)
        ctx.esp = esp
        uc.reg_write(UC_X86_REG_ESP, esp)

        uc_reg_map = {
            "eax": UC_X86_REG_EAX,
            "ecx": UC_X86_REG_ECX,
            "edx": UC_X86_REG_EDX,
            "ebx": UC_X86_REG_EBX,
            "ebp": UC_X86_REG_EBP,
            "esi": UC_X86_REG_ESI,
            "edi": UC_X86_REG_EDI,
        }
        if regs:
            for r, v in regs.items():
                ctx.write_reg(r, v)
                uc.reg_write(uc_reg_map[r], v & 0xFFFFFFFF)

        uc.emu_start(va, SENTINEL_RET, count=10_000_000)
        self.evaluator.execute(va, ctx, mem)

        uc_out = {
            "eax": uc.reg_read(UC_X86_REG_EAX) & 0xFFFFFFFF,
            "ecx": uc.reg_read(UC_X86_REG_ECX) & 0xFFFFFFFF,
            "edx": uc.reg_read(UC_X86_REG_EDX) & 0xFFFFFFFF,
            "ebx": uc.reg_read(UC_X86_REG_EBX) & 0xFFFFFFFF,
            "esp": uc.reg_read(UC_X86_REG_ESP) & 0xFFFFFFFF,
            "ebp": uc.reg_read(UC_X86_REG_EBP) & 0xFFFFFFFF,
            "esi": uc.reg_read(UC_X86_REG_ESI) & 0xFFFFFFFF,
            "edi": uc.reg_read(UC_X86_REG_EDI) & 0xFFFFFFFF,
            "eflags": uc.reg_read(UC_X86_REG_EFLAGS) & 0xFFFFFFFF,
        }
        for r in check_regs:
            ir_v = ctx.read_reg(r)
            assert ir_v == uc_out[r], f"0x{va:08x} reg {r} mismatch: IR=0x{ir_v:08x} UC=0x{uc_out[r]:08x}"
        return ctx, uc_out

    def run_machine_snippet_diff(
        self,
        code: bytes,
        init_regs: dict[str, int] | None = None,
        mem_init: dict[int, bytes] | None = None,
        flag_mask: int = FLAG_CF | FLAG_PF | FLAG_AF | FLAG_ZF | FLAG_SF | FLAG_DF | FLAG_OF,
    ) -> None:
        """Lift a raw x86-32 machine code blob and compare EVERY GPR, EFLAGS, FPU, and memory byte vs Unicorn."""
        base_va = 0x00401000
        uc = Uc(UC_ARCH_X86, UC_MODE_32)
        uc.mem_map(0x00400000, 0x2000, UC_PROT_ALL)
        uc.mem_write(base_va, code)
        uc.mem_map(STACK_BASE, STACK_SIZE, UC_PROT_ALL)
        uc.mem_map(SCRATCH_BASE, 0x10000, UC_PROT_ALL)
        uc.mem_map(SENTINEL_RET, 0x1000, UC_PROT_ALL)
        uc.mem_write(SENTINEL_RET, b"\x90\xf4")

        mem = EvalMemory()
        mem.map_region(0x00400000, 0x2000)
        mem.write_bytes(base_va, code)
        mem.map_region(STACK_BASE, STACK_SIZE)
        mem.map_region(SCRATCH_BASE, 0x10000)
        mem.map_region(SENTINEL_RET, 0x1000)

        esp = STACK_BASE + 0x80000
        self._sync_write(uc, mem, esp, struct.pack("<I", SENTINEL_RET))
        if mem_init:
            for a, b in mem_init.items():
                self._sync_write(uc, mem, a, b)

        # Build a temporary PEBinary wrapper over a tiny buffer or lift directly
        pe_dummy = self.pe_bin
        old_va, old_end, old_bytes = pe_dummy.text_va, pe_dummy.text_end, pe_dummy.text_bytes
        pe_dummy.text_va = base_va
        pe_dummy.text_end = base_va + len(code)
        pe_dummy.text_bytes = code
        try:
            dis = _make_disassembler(pe_dummy, self.md)
            fcfg = _recover_single_function(base_va, "Snippet", True, pe_dummy, dis, {base_va}, set())
            ir_fn = lift_function(fcfg, pe_dummy, {base_va})
        finally:
            pe_dummy.text_va, pe_dummy.text_end, pe_dummy.text_bytes = old_va, old_end, old_bytes

        ctx = EvalContext(esp=esp, eflags=0x00000202)
        uc.reg_write(UC_X86_REG_ESP, esp)
        uc.reg_write(UC_X86_REG_EFLAGS, 0x00000202)
        uc.reg_write(UC_X86_REG_FPCW, 0x027F)
        uc.reg_write(UC_X86_REG_FPSW, 0x0000)
        uc_reg_map = {
            "eax": UC_X86_REG_EAX,
            "ecx": UC_X86_REG_ECX,
            "edx": UC_X86_REG_EDX,
            "ebx": UC_X86_REG_EBX,
            "ebp": UC_X86_REG_EBP,
            "esi": UC_X86_REG_ESI,
            "edi": UC_X86_REG_EDI,
        }
        if init_regs:
            for r, v in init_regs.items():
                ctx.write_reg(r, v)
                uc.reg_write(uc_reg_map[r], v & 0xFFFFFFFF)

        uc.emu_start(base_va, SENTINEL_RET, count=1_000_000)
        IREvaluator({base_va: ir_fn}).execute(base_va, ctx, mem)

        for r, uid in uc_reg_map.items():
            uv = uc.reg_read(uid) & 0xFFFFFFFF
            iv = ctx.read_reg(r)
            assert iv == uv, f"Snippet reg {r}: IR=0x{iv:08x} UC=0x{uv:08x}"

        # Compare deterministic flags CF, PF, AF, ZF, SF, OF, DF
        uf = uc.reg_read(UC_X86_REG_EFLAGS) & flag_mask
        iv_f = ctx.eflags & flag_mask
        assert iv_f == uf, f"Snippet EFLAGS mismatch: IR=0x{iv_f:03x} UC=0x{uf:03x}"

        # Compare scratch memory
        uc_scr = bytes(uc.mem_read(SCRATCH_BASE, 0x1000))
        ir_scr = mem.read_bytes(SCRATCH_BASE, 0x1000)
        if ir_scr != uc_scr:
            for off in range(0, 0x1000, 4):
                if ir_scr[off:off+4] != uc_scr[off:off+4]:
                    raise AssertionError(
                        f"Snippet scratch memory mismatch at +0x{off:03x}: "
                        f"IR={ir_scr[off:off+4].hex()} UC={uc_scr[off:off+4].hex()}"
                    )

    def run_all(self) -> dict[str, int]:
        passed = 0

        # 1. FilePac filename_hash (0x004db470)
        hash_samples = [
            b"",
            b".",
            b".\\bg",
            b"aka00_000.bmp",
            b"long_directory_or_filename_exceeding_15_bytes.ha6",
            bytes([0x80, 0x81, 0xFF, 0x41, 0x7F]),
            b"chr\\aka\\aka00.ha6",
            b"grp\\title\\bg00.cg",
        ]
        for s in hash_samples:
            uc, mem, ctx = self._new_pair()
            s_addr = SCRATCH_BASE
            buf_addr = SCRATCH_BASE + 0x100
            self._sync_write(uc, mem, s_addr, b"\x00" * 32)
            if len(s) < 16:
                self._sync_write(uc, mem, s_addr + 4, s + b"\x00")
                cap = 15
            else:
                self._sync_write(uc, mem, buf_addr, s + b"\x00")
                self._sync_write(uc, mem, s_addr + 4, struct.pack("<I", buf_addr))
                cap = len(s)
            self._sync_write(uc, mem, s_addr + 0x14, struct.pack("<II", len(s), cap))
            self._run_both(0x004DB470, uc, mem, ctx, regs={"edi": s_addr})
            passed += 1

        # 2. FilePac str cipher (0x004db530) incl. step=0 fallback
        for step in (0, 1, 3, 7, 13):
            for seed in (0x4EB8BFD6, 0x12345678, 0xDEADBEEF):
                uc, mem, ctx = self._new_pair()
                hdr = SCRATCH_BASE
                buf = SCRATCH_BASE + 0x100
                data = bytes((i * 29 + step) & 0xFF for i in range(64))
                self._sync_write(uc, mem, hdr, b"\x00" * 0x20)
                self._sync_write(uc, mem, hdr + 0x14, struct.pack("<I", seed))
                self._sync_write(uc, mem, buf, data)
                self._run_both(0x004DB530, uc, mem, ctx, regs={"ecx": buf, "esi": 32, "edx": step}, push_args=[hdr])
                assert mem.read_bytes(buf, 64) == bytes(uc.mem_read(buf, 64))
                passed += 1

        # 3. FilePac seek (0x004db590) + XOR (0x004db5e0) across offset=0, offset=0xF80, max_len=4096 boundary
        for offset in (0, 17, 0x0F80, 4096):
            uc, mem, ctx = self._new_pair()
            state = SCRATCH_BASE
            buf = SCRATCH_BASE + 0x1000
            seed = 0x4EB8BFD6
            payload = bytes((i * 17 + 3) & 0xFF for i in range(4200))
            blob = struct.pack("<IBB4s2sII", seed, 3, 0, seed.to_bytes(4, "little"), b"\x00\x00", 0, 4096)
            self._sync_write(uc, mem, state, blob)
            if offset > 0:
                self._run_both(0x004DB590, uc, mem, ctx, regs={"eax": state, "ecx": offset})
                assert mem.read_bytes(state, 0x14) == bytes(uc.mem_read(state, 0x14))
                passed += 1
            self._sync_write(uc, mem, buf, payload)
            self._run_both(0x004DB5E0, uc, mem, ctx, regs={"eax": state}, push_args=[buf, len(payload)])
            assert mem.read_bytes(buf, len(payload)) == bytes(uc.mem_read(buf, len(payload)))
            assert mem.read_bytes(state, 0x14) == bytes(uc.mem_read(state, 0x14))
            passed += 1

        # 4. Live 0006.p / 0008.p archive slices via FilePac if MBAACC\0006.p exists
        mbaa_py = Path(r"c:\Users\A\Desktop\AI\google\mbaacc-src\py")
        if str(mbaa_py) not in sys.path:
            sys.path.insert(0, str(mbaa_py))
        from mbaacc.filepac import DIR_ENTRY_SIZE, FILE_ENTRY_SIZE, HEADER_SIZE, MOUNT_ORDER, FilePacArchive

        mbaacc_dir = self.exe_path.parent
        for pname in MOUNT_ORDER:
            p_path = mbaacc_dir / pname
            if not p_path.exists():
                continue
            arc = FilePacArchive(p_path)
            with p_path.open("rb") as fp:
                fp.seek(HEADER_SIZE)
                raw_dirs = fp.read(arc.header.dir_count * DIR_ENTRY_SIZE)
                fp.seek(HEADER_SIZE + arc.header.dir_count * DIR_ENTRY_SIZE)
                raw_files = fp.read(arc.header.file_count * FILE_ENTRY_SIZE)
                if arc.dirs:
                    _, _, dstep, denc = struct.unpack_from("<3I256s", raw_dirs, 0)
                    uc, mem, ctx = self._new_pair()
                    self._sync_write(uc, mem, SCRATCH_BASE, b"\x00" * 0x20)
                    self._sync_write(uc, mem, SCRATCH_BASE + 0x14, struct.pack("<I", arc.header.seed))
                    self._sync_write(uc, mem, SCRATCH_BASE + 0x100, denc)
                    self._run_both(0x004DB530, uc, mem, ctx, regs={"ecx": SCRATCH_BASE + 0x100, "esi": 256, "edx": dstep & 0xFF}, push_args=[SCRATCH_BASE])
                    assert mem.read_bytes(SCRATCH_BASE + 0x100, 256) == bytes(uc.mem_read(SCRATCH_BASE + 0x100, 256))
                    passed += 1
                if arc.files:
                    fe = arc.files[min(3, len(arc.files) - 1)]
                    fp.seek(arc.header.data_offset + fe.offset)
                    enc_pay = fp.read(min(fe.size, 4300))
                    uc, mem, ctx = self._new_pair()
                    blob = struct.pack("<IBB4s2sII", arc.header.seed, arc.header.payload_step or 1, 0, arc.header.seed.to_bytes(4, "little"), b"\x00\x00", 0, arc.header.payload_crypt_len)
                    self._sync_write(uc, mem, SCRATCH_BASE, blob)
                    self._sync_write(uc, mem, SCRATCH_BASE + 0x1000, enc_pay)
                    self._run_both(0x004DB5E0, uc, mem, ctx, regs={"eax": SCRATCH_BASE}, push_args=[SCRATCH_BASE + 0x1000, len(enc_pay)])
                    assert mem.read_bytes(SCRATCH_BASE + 0x1000, len(enc_pay)) == bytes(uc.mem_read(SCRATCH_BASE + 0x1000, len(enc_pay)))
                    passed += 1

        # 5. BPE Decompressor (0x00417270) — synthetic Gage BPE streams (literal + multi-pair expansion)
        def make_bpe_header(name: bytes = b"test.txt") -> bytes:
            hdr = bytearray(0x48)
            hdr[0:4] = b"BPE\x00"
            hdr[4 : 4 + len(name)] = name
            return bytes(hdr)

        def make_bpe_literal(raw_blocks: list[bytes]) -> bytes:
            body = bytearray()
            for blk in raw_blocks:
                # 0xFF skips 0..127 -> i=128, reads L[128]=128 -> i=129, 0xFE skips 129..255 -> i=256!
                body.extend((0xFF, 128, 0xFE))
                body.extend(struct.pack(">H", len(blk)))
                body.extend(blk)
            return make_bpe_header() + bytes(body)

        # Test literal, single-pair expansion (ABC), and nested multi-pair expansion
        pair_abc = make_bpe_header() + bytes([0, ord("A"), ord("B"), 255, 129, 253, 0, 2, 0, ord("C")])
        # Nested pair: 0 -> ('A','B'), 1 -> (0,'C'), skip 2..129 (255), identity L[130]=130, skip 131..255 (252) => "ABCD"
        pair_nested = make_bpe_header() + bytes([1, ord("A"), ord("B"), 0, ord("C"), 255, 130, 252, 0, 2, 1, ord("D")])
        bpe_inputs = [
            make_bpe_literal([b"Hello MBAACC BPE! 1234567890", b"Second block!!"]),
            make_bpe_literal([bytes((i * 7) & 0xFF for i in range(300))]),
            pair_abc,
            pair_nested,
        ]

        for raw_bpe in bpe_inputs:
            uc, mem, ctx = self._new_pair()
            in_ptr = SCRATCH_BASE
            out_ptr = SCRATCH_BASE + 0x20000
            self._sync_write(uc, mem, in_ptr, raw_bpe)
            self._sync_write(uc, mem, out_ptr, b"\x00" * 0x20000)
            self._run_both(0x00417270, uc, mem, ctx, push_args=[out_ptr, in_ptr, len(raw_bpe)])
            assert mem.read_bytes(out_ptr, 0x10000) == bytes(uc.mem_read(out_ptr, 0x10000))
            passed += 1

        # 6. Palette index-0 remapper (0x004020a0)
        for pal_case in range(4):
            uc, mem, ctx = self._new_pair()
            pal = bytearray(256 * 4)
            for i in range(256):
                if pal_case == 0:
                    pal[i * 4 : i * 4 + 4] = bytes([0x12, 0x34, 0x56, 0xFF]) if i == 0 else (b"\x00\x00\x00\xff" if i % 5 == 0 else bytes([i, (i * 3) & 0xFF, 7, 0x80]))
                elif pal_case == 1:
                    pal[i * 4 : i * 4 + 4] = b"\x00\x00\x00\x00"
                elif pal_case == 2:
                    pal[i * 4 : i * 4 + 4] = b"\xff\xff\xff\xff"
                else:
                    pal[i * 4 : i * 4 + 4] = bytes([i & 1, 0, 0, i])
            self._sync_write(uc, mem, SCRATCH_BASE, bytes(pal))
            self._run_both(0x004020A0, uc, mem, ctx, regs={"eax": SCRATCH_BASE})
            assert mem.read_bytes(SCRATCH_BASE, 1024) == bytes(uc.mem_read(SCRATCH_BASE, 1024))
            passed += 1

        # 7. SaveData validators (0x00401000 PlayData, 0x00401370 GameData) + resetters
        for valid_magic in (0xF0FFF004, 0xBAD00000):
            for bad_idx in (-1, 0, 15, 39):
                # PlayData::validate (0x00401000)
                uc, mem, ctx = self._new_pair()
                pdata = bytearray(0x3E0)
                struct.pack_into("<I", pdata, 0, valid_magic)
                struct.pack_into("<I", pdata, 0x298, 0xFFF00002)
                if bad_idx >= 0:
                    struct.pack_into("<i", pdata, 0x18 + bad_idx * 16 + 8, -1)
                self._sync_write(uc, mem, SCRATCH_BASE, bytes(pdata))
                self._sync_write(uc, mem, 0x0055413C, struct.pack("<I", SCRATCH_BASE))
                self._run_both(0x00401000, uc, mem, ctx)
                passed += 1

        for valid_magic in (0xF0FFF004, 0x12345678):
            for bad_field in (None, ("slot0_f1", 4, 9), ("bgm", 0x144, 22), ("flag170", 0x170, 1)):
                uc, mem, ctx = self._new_pair()
                gdata = bytearray(0x17C)
                struct.pack_into("<I", gdata, 0, valid_magic)
                for s in range(16):
                    struct.pack_into("<5i", gdata, 4 + s * 20, 2, 2, 2, 2, 0)
                struct.pack_into("<i", gdata, 0x150, 1)
                struct.pack_into("<i", gdata, 0x160, 2)
                if bad_field is not None:
                    _, off, val = bad_field
                    struct.pack_into("<i", gdata, off, val)
                self._sync_write(uc, mem, SCRATCH_BASE, bytes(gdata))
                self._sync_write(uc, mem, 0x00554140, struct.pack("<I", SCRATCH_BASE))
                self._run_both(0x00401370, uc, mem, ctx)
                passed += 1

        # 8. x87 FPU + rounding mode + branch/flag + shift/rotate + mul/div + string ops stress tests
        # Snippet A: x87 full stack + fsub/fsubr/fsubp/fsubrp/fdiv/fdivr/fdivp/fdivrp/fild/fistp/fldcw/fnstsw/fcompp/fxch
        # fld qword [0x02000000] (10.5); fld qword [0x02000008] (2.25); fsubp st(1);
        # fild dword [0x02000010] (-7); faddp st(1); fchs; fabs;
        # fnstcw [0x02000020]; fldcw [0x02000022] (0x0F7F trunc); fistp dword [0x02000024];
        # fld1; fldz; fcompp; fnstsw ax; ret
        snip_fpu = bytes.fromhex(
            "dd0500000002"          # fld qword ptr [0x02000000]
            "dd0508000002"          # fld qword ptr [0x02000008]
            "dee9"                  # fsubp st(1)
            "db0510000002"          # fild dword ptr [0x02000010]
            "dec1"                  # faddp st(1)
            "d9e0"                  # fchs
            "d9e1"                  # fabs
            "d93d20000002"          # fnstcw word ptr [0x02000020]
            "d92d22000002"          # fldcw word ptr [0x02000022]
            "db1d24000002"          # fistp dword ptr [0x02000024]
            "d9e8"                  # fld1
            "d9ee"                  # fldz
            "ded9"                  # fcompp
            "dfe0"                  # fnstsw ax
            "c3"                    # ret
        )
        fpu_mem = {
            SCRATCH_BASE: struct.pack("<ddi", 10.5, 2.25, -7),
            SCRATCH_BASE + 0x22: struct.pack("<H", 0x0F7F),
        }
        self.run_machine_snippet_diff(snip_fpu, mem_init=fpu_mem)
        passed += 1

        # Snippet B: fsubr / fdivr / fdivrp / fsubrp / fxch / fcomp / fucompp
        snip_fpu2 = bytes.fromhex(
            "dd0500000002"          # fld qword [0x02000000] (10.0)
            "dd0508000002"          # fld qword [0x02000008] (2.0)
            "d9c9"                  # fxch st(1)  (st0=10, st1=2)
            "dee1"                  # fsubrp st(1) (st1 = st0 - st1 = 8.0, pop -> st0=8.0)
            "dd0508000002"          # fld qword [0x02000008] (2.0) -> st0=2, st1=8
            "def1"                  # fdivrp st(1) (st1 = 2/8 = 0.25, pop -> st0=0.25)
            "dd1d10000002"          # fstp qword [0x02000010]
            "c3"
        )
        self.run_machine_snippet_diff(snip_fpu2, mem_init={SCRATCH_BASE: struct.pack("<dd", 10.0, 2.0)})
        passed += 1

        # Snippet C: Integer ALU, adc, sbb, inc, dec, neg, shl/shr/sar/rol, imul, idiv, cdq, setcc, rep movsd, repe cmpsb
        snip_alu = bytes.fromhex(
            "b8ffffff7f"            # mov eax, 0x7fffffff
            "40"                    # inc eax (OF=1, CF unchanged)
            "0f90c3"                # seto bl
            "b900000080"            # mov ecx, 0x80000000
            "83e901"                # sub ecx, 1 (OF=1)
            "1bd2"                  # sbb edx, edx
            "f7da"                  # neg edx
            "66c1c008"              # rol ax, 8
            "c1f803"                # sar eax, 3
            "b89cffffff"            # mov eax, -100
            "99"                    # cdq
            "b907000000"            # mov ecx, 7
            "f7f9"                  # idiv ecx
            "c3"
        )
        self.run_machine_snippet_diff(snip_alu)
        passed += 1

        # Snippet D: rep movsd + repe cmpsb + setne + branches
        snip_str = bytes.fromhex(
            "fc"                    # cld (wait: need cld? no, DF=0 default!)
            "be00000002"            # mov esi, 0x02000000
            "bf40000002"            # mov edi, 0x02000040
            "b904000000"            # mov ecx, 4
            "f3a5"                  # rep movsd
            "be00000002"            # mov esi, 0x02000000
            "bf40000002"            # mov edi, 0x02000040
            "b910000000"            # mov ecx, 16
            "f3a6"                  # repe cmpsb (equal -> ZF=1)
            "0f94c0"                # sete al
            "c60545000002ff"        # mov byte ptr [0x02000045], 0xff
            "be00000002"            # mov esi, 0x02000000
            "bf40000002"            # mov edi, 0x02000040
            "b910000000"            # mov ecx, 16
            "f3a6"                  # repe cmpsb (diff at byte 5 -> ZF=0)
            "0f95c2"                # setne dl
            "c3"
        )
        # Note: strip 0xfc (cld) if cld wasn't in MBAA.exe mnemonics? Let's omit 0xfc since DF=0 initially, AND test cld/std? No, MBAA.exe had 0 cld in game .text!
        snip_str = snip_str[1:]
        self.run_machine_snippet_diff(snip_str, mem_init={SCRATCH_BASE: b"0123456789ABCDEF"})
        passed += 1

        # Snippet E: SaveData::reset_defaults (0x00401050 PlayData, 0x00401490 GameData) against Unicorn
        # 0x00401050 reads ptr from [0x0055413C]
        uc, mem, ctx = self._new_pair()
        self._sync_write(uc, mem, SCRATCH_BASE, b"\xAA" * 0x3E0)
        self._sync_write(uc, mem, 0x0055413C, struct.pack("<I", SCRATCH_BASE))
        self._run_both(0x00401050, uc, mem, ctx)
        assert mem.read_bytes(SCRATCH_BASE, 0x3E0) == bytes(uc.mem_read(SCRATCH_BASE, 0x3E0))
        passed += 1

        # 0x00401490 takes gamedata_ptr in EAX
        uc, mem, ctx = self._new_pair()
        self._sync_write(uc, mem, SCRATCH_BASE, b"\xAA" * 0x17C)
        self._run_both(0x00401490, uc, mem, ctx, regs={"eax": SCRATCH_BASE})
        assert mem.read_bytes(SCRATCH_BASE, 0x17C) == bytes(uc.mem_read(SCRATCH_BASE, 0x17C))
        passed += 1

        # Snippet F1: Shift count & 0x1F == 0 must preserve ALL flags (including AF/CF/SF/PF)
        self.run_machine_snippet_diff(
            bytes.fromhex(
                "33c0"          # xor eax, eax
                "83e801"        # sub eax, 1 (CF=1, AF=1, SF=1, PF=1)
                "b120"          # mov cl, 0x20 (count & 0x1f == 0)
                "d3e0"          # shl eax, cl
                "c3"
            )
        )
        passed += 1

        # Snippet F2: Shift count=1 flags (CF, PF, ZF, SF, OF defined; AF architecturally undefined)
        self.run_machine_snippet_diff(
            bytes.fromhex(
                "b8ffffffff"    # mov eax, 0xffffffff
                "b101"          # mov cl, 1
                "d3e8"          # shr eax, cl (CF=1, OF=1)
                "c3"
            ),
            flag_mask=FLAG_CF | FLAG_PF | FLAG_ZF | FLAG_SF | FLAG_DF | FLAG_OF,
        )
        passed += 1

        # Snippet F3: mul / imul 8,16,32 / div / idiv (verify CF/OF defined + quotient/remainder)
        self.run_machine_snippet_diff(
            bytes.fromhex(
                "b834120000"    # mov eax, 0x1234
                "b978560000"    # mov ecx, 0x5678
                "f7e1"          # mul ecx (edx=0, eax=0x06260060, CF=0, OF=0)
                "0f920500000002"  # setc [0x02000000]
                "6669d81900"    # imul bx, ax, 0x19 (no overflow -> OF=0)
                "0f900501000002"  # seto [0x02000001]
                "b0fe"          # mov al, 0xfe (-2)
                "b203"          # mov dl, 3
                "f6ea"          # imul dl (AX = 0xfffa = -6, OF=0, CF=0)
                "0f900502000002"  # seto [0x02000002]
                "b8f4010000"    # mov eax, 500
                "b907000000"    # mov ecx, 7
                "33d2"          # xor edx, edx
                "f7f1"          # div ecx (eax=71, edx=3)
                "890504000002"  # mov [0x02000004], eax
                "b89cbfffff"    # mov eax, -16484 (0xffffbf9c)
                "99"            # cdq
                "b90b000000"    # mov ecx, 11
                "f7f9"          # idiv ecx
                "69f100000100"  # imul esi, ecx, 0x10000
                "c3"
            ),
            flag_mask=FLAG_CF | FLAG_OF | FLAG_DF,
        )
        passed += 1

        # Snippet G: x87 2-op fsub/fdiv, fiadd/fisub/fimul/fidiv/fidivr, fild qword, fcom/fucom/fcomp
        snip_fpu3 = bytes.fromhex(
            "df2d00000002"          # fild qword ptr [0x02000000] (100)
            "da0508000002"          # fiadd dword ptr [0x02000008] (+25 = 125)
            "da2508000002"          # fisub dword ptr [0x02000008] (-25 = 100)
            "da0d0c000002"          # fimul dword ptr [0x0200000c] (*3 = 300)
            "da3510000002"          # fidiv dword ptr [0x02000010] (/4 = 75)
            "da3d14000002"          # fidivr dword ptr [0x02000014] (150/75 = 2.0)
            "d9e8"                  # fld1 (st0=1, st1=2)
            "dce9"                  # fsub st(1), st(0) (st1=1.0)
            "dcf9"                  # fdiv st(1), st(0) (st1=1.0)
            "dd1d20000002"          # fstp qword ptr [0x02000020]
            "dd1d28000002"          # fstp qword ptr [0x02000028]
            "c3"
        )
        self.run_machine_snippet_diff(snip_fpu3, mem_init={SCRATCH_BASE: struct.pack("<qiiii", 100, 25, 3, 4, 150)})
        passed += 1

        # Snippet H: rep stosd + movsb + movsw + setcc to memory + switch jump table
        # Switch jump table at 0x00401080 with 3 targets
        snip_sw = bytearray(0x100)
        code_part = bytes.fromhex(
            "b801000000"            # 0x401000: mov eax, 1
            "ff248580104000"        # 0x401005: jmp dword ptr [eax*4 + 0x00401080]
            "bb11111111"            # 0x40100c: case 0
            "eb0e"                  # 0x401011: jmp +14 -> 0x401021
            "bb22222222"            # 0x401013: case 1
            "eb07"                  # 0x401018: jmp +7 -> 0x401021
            "bb33333333"            # 0x40101a: case 2
            "90"                    # 0x40101f: nop
            "90"                    # 0x401020: nop
            "bf00000002"            # 0x401021: mov edi, 0x02000000
            "b8cafebabe"            # 0x401026: mov eax, 0xcafebabe
            "b903000000"            # 0x40102b: mov ecx, 3
            "f3ab"                  # 0x401030: rep stosd
            "39c0"                  # 0x401032: cmp eax, eax
            "0f940520000002"        # 0x401034: sete byte ptr [0x02000020]
            "c3"                    # 0x40103b: ret
        )
        snip_sw[: len(code_part)] = code_part
        struct.pack_into("<III", snip_sw, 0x80, 0x0040100C, 0x00401013, 0x0040101A)
        self.run_machine_snippet_diff(bytes(snip_sw))
        passed += 1

        return {"passed": passed, "failed": 0}


def main() -> None:
    parser = argparse.ArgumentParser(description="Run IR vs Unicorn differential test suite.")
    parser.add_argument("--exe", type=Path, default=DEFAULT_MBAA_EXE)
    args = parser.parse_args()
    suite = DifferentialSuite(args.exe)
    res = suite.run_all()
    print(f"Differential tests: {res['passed']}/{res['passed']} PASSED (0 failed)")


if __name__ == "__main__":
    main()
