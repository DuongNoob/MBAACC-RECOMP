"""Typed x86-32 + x87 intermediate representation (IR) for MBAA.exe AOT recompilation.

Shared between `x86_lifter.py` (producer), `ir_eval.py` (direct Python IR
interpreter for Unicorn differential testing), and `cpp_emitter.py` (C++20 codegen).
"""

from __future__ import annotations

from dataclasses import dataclass, field
from typing import Union

GPR32_NAMES = ("eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi")
GPR16_NAMES = ("ax", "cx", "dx", "bx", "sp", "bp", "si", "di")
GPR8_LO_NAMES = ("al", "cl", "dl", "bl")
GPR8_HI_NAMES = ("ah", "ch", "dh", "bh")
FLAG_NAMES = ("cf", "pf", "af", "zf", "sf", "of", "df")

REG_BITS: dict[str, int] = {
    **{r: 32 for r in GPR32_NAMES},
    **{r: 16 for r in GPR16_NAMES},
    **{r: 8 for r in GPR8_LO_NAMES},
    **{r: 8 for r in GPR8_HI_NAMES},
    "eflags": 32,
    "fs_0": 32,
    "fpu_cw": 16,
    "fpu_sw": 16,
}

JCC_CONDITIONS = (
    "o", "no", "b", "ae", "e", "ne", "be", "a",
    "s", "ns", "p", "np", "l", "ge", "le", "g",
)


def reg_bits(name: str) -> int:
    return REG_BITS[name]


# ---------------------------------------------------------------------------
# IR Value References
# ---------------------------------------------------------------------------

@dataclass(frozen=True, slots=True)
class Const:
    value: int
    bits: int = 32


@dataclass(frozen=True, slots=True)
class FConst:
    value: float


@dataclass(frozen=True, slots=True)
class Temp:
    id: int
    bits: int = 32
    is_float: bool = False


@dataclass(frozen=True, slots=True)
class Reg:
    name: str


@dataclass(frozen=True, slots=True)
class Flag:
    name: str


IRValue = Union[Const, FConst, Temp, Reg, Flag]


# ---------------------------------------------------------------------------
# Pure IR Expressions (RHS of Assign)
# ---------------------------------------------------------------------------

@dataclass(frozen=True, slots=True)
class ReadVal:
    val: IRValue


@dataclass(frozen=True, slots=True)
class BinOp:
    op: str
    bits: int
    lhs: IRValue
    rhs: IRValue


@dataclass(frozen=True, slots=True)
class UnOp:
    op: str
    bits: int
    src: IRValue


@dataclass(frozen=True, slots=True)
class MemLoad:
    addr: IRValue
    bits: int


@dataclass(frozen=True, slots=True)
class FpuLoadMem:
    addr: IRValue
    bits: int  # 32, 64, or 80


@dataclass(frozen=True, slots=True)
class FpuLoadInt:
    addr: IRValue
    bits: int  # 16, 32, or 64


@dataclass(frozen=True, slots=True)
class FpuPeek:
    index: int


@dataclass(frozen=True, slots=True)
class FBinOp:
    op: str  # fadd, fsub, fmul, fdiv
    lhs: IRValue
    rhs: IRValue


@dataclass(frozen=True, slots=True)
class FUnOp:
    op: str  # fchs, fabs, fsqrt
    src: IRValue


@dataclass(frozen=True, slots=True)
class CondExpr:
    cond: str


@dataclass(frozen=True, slots=True)
class Select:
    cond: IRValue
    when_true: IRValue
    when_false: IRValue
    bits: int


IRExpr = Union[
    ReadVal,
    BinOp,
    UnOp,
    MemLoad,
    FpuLoadMem,
    FpuLoadInt,
    FpuPeek,
    FBinOp,
    FUnOp,
    CondExpr,
    Select,
]


# ---------------------------------------------------------------------------
# IR Statements
# ---------------------------------------------------------------------------

@dataclass(frozen=True, slots=True)
class Comment:
    va: int
    text: str


@dataclass(frozen=True, slots=True)
class Assign:
    dst: Temp
    expr: IRExpr


@dataclass(frozen=True, slots=True)
class WriteReg:
    reg: str
    val: IRValue


@dataclass(frozen=True, slots=True)
class WriteFlag:
    flag: str
    val: IRValue


@dataclass(frozen=True, slots=True)
class UpdateFlags:
    op: str  # add, adc, sub, sbb, cmp, inc, dec, neg, logic, shl, shr, sar, rol, ror, mul, imul
    bits: int
    lhs: IRValue
    rhs: IRValue
    res: IRValue
    carry_in: IRValue | None = None


@dataclass(frozen=True, slots=True)
class WriteMem:
    addr: IRValue
    bits: int
    val: IRValue


@dataclass(frozen=True, slots=True)
class FpuStoreMem:
    addr: IRValue
    bits: int  # 32 or 64
    val: IRValue


@dataclass(frozen=True, slots=True)
class FpuStoreInt:
    addr: IRValue
    bits: int  # 16, 32, or 64
    val: IRValue


@dataclass(frozen=True, slots=True)
class FpuPush:
    val: IRValue


@dataclass(frozen=True, slots=True)
class FpuPop:
    pass


@dataclass(frozen=True, slots=True)
class FpuSet:
    index: int
    val: IRValue


@dataclass(frozen=True, slots=True)
class FpuSwap:
    index: int


@dataclass(frozen=True, slots=True)
class FpuCmp:
    lhs: IRValue
    rhs: IRValue
    set_eflags: bool = False


@dataclass(frozen=True, slots=True)
class FpuClearEx:
    pass


@dataclass(frozen=True, slots=True)
class StringOp:
    kind: str  # movs, stos, cmps, scas
    bits: int  # 8, 16, 32
    rep: str | None  # None, rep, repe, repne


@dataclass(frozen=True, slots=True)
class CallDirect:
    target_va: int
    return_va: int


@dataclass(frozen=True, slots=True)
class CallCRT:
    target_va: int
    return_va: int


@dataclass(frozen=True, slots=True)
class CallIAT:
    iat_va: int
    return_va: int


@dataclass(frozen=True, slots=True)
class CallIndirect:
    target: IRValue
    return_va: int


IRStmt = Union[
    Comment,
    Assign,
    WriteReg,
    WriteFlag,
    UpdateFlags,
    WriteMem,
    FpuStoreMem,
    FpuStoreInt,
    FpuPush,
    FpuPop,
    FpuSet,
    FpuSwap,
    FpuCmp,
    FpuClearEx,
    StringOp,
    CallDirect,
    CallCRT,
    CallIAT,
    CallIndirect,
]


# ---------------------------------------------------------------------------
# Block Terminators
# ---------------------------------------------------------------------------

@dataclass(frozen=True, slots=True)
class TermRet:
    pop_extra: int = 0


@dataclass(frozen=True, slots=True)
class TermJump:
    target_va: int


@dataclass(frozen=True, slots=True)
class TermFallthrough:
    target_va: int


@dataclass(frozen=True, slots=True)
class TermBranch:
    cond: str  # JCC_CONDITIONS or ecx_z, loop, loope, loopne
    target_va: int
    fallthrough_va: int


@dataclass(frozen=True, slots=True)
class TermSwitch:
    index: IRValue
    targets: tuple[int, ...]
    table_va: int


@dataclass(frozen=True, slots=True)
class TermTailCallGame:
    target_va: int


@dataclass(frozen=True, slots=True)
class TermTailCallCRT:
    target_va: int


@dataclass(frozen=True, slots=True)
class TermTailCallIAT:
    iat_va: int


@dataclass(frozen=True, slots=True)
class TermTailCallIndirect:
    target: IRValue


@dataclass(frozen=True, slots=True)
class TermTrap:
    va: int
    kind: str


IRTerm = Union[
    TermRet,
    TermJump,
    TermFallthrough,
    TermBranch,
    TermSwitch,
    TermTailCallGame,
    TermTailCallCRT,
    TermTailCallIAT,
    TermTailCallIndirect,
    TermTrap,
]


# ---------------------------------------------------------------------------
# Block & Function IR Containers
# ---------------------------------------------------------------------------

@dataclass
class IRBlock:
    start_va: int
    stmts: list[IRStmt] = field(default_factory=list)
    term: IRTerm | None = None


@dataclass
class IRFunction:
    entry_va: int
    name: str
    subsystem: str
    is_canonical: bool
    blocks: dict[int, IRBlock]
    block_order: list[int]
    temp_types: dict[int, tuple[int, bool]]  # temp_id -> (bits, is_float)
    insn_count: int
    unhandled: list[tuple[int, str]] = field(default_factory=list)
