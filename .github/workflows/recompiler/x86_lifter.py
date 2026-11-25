"""Complete x86-32 + x87 FPU instruction lifter to typed IR for MBAA.exe."""

from __future__ import annotations

import capstone
from capstone import x86 as cs_x86

from .cfg import BasicBlock, FunctionCFG, MBAA_CRT_START_VA, PEBinary, ProgramCFG
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
    IRStmt,
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
    reg_bits,
)

_MASK = {8: 0xFF, 16: 0xFFFF, 32: 0xFFFFFFFF, 64: 0xFFFFFFFFFFFFFFFF}


class _LiftContext:
    """Per-function lifting state managing temporary allocation and statement emission."""

    def __init__(self, pe: PEBinary, all_entry_vas: set[int]) -> None:
        self.pe = pe
        self.all_entry_vas = all_entry_vas
        self._next_temp = 0
        self.temp_types: dict[int, tuple[int, bool]] = {}
        self.stmts: list[IRStmt] = []
        self.unhandled: list[tuple[int, str]] = []

    def temp(self, bits: int = 32, is_float: bool = False) -> Temp:
        tid = self._next_temp
        self._next_temp += 1
        self.temp_types[tid] = (bits, is_float)
        return Temp(id=tid, bits=bits, is_float=is_float)

    def emit(self, stmt: IRStmt) -> None:
        self.stmts.append(stmt)

    def eval_expr(self, expr: IRExpr, bits: int = 32, is_float: bool = False) -> Temp:
        t = self.temp(bits=bits, is_float=is_float)
        self.emit(Assign(dst=t, expr=expr))
        return t

    def reg_name(self, insn: capstone.CsInsn, reg_id: int) -> str:
        return insn.reg_name(reg_id).lower()

    def st_index(self, insn: capstone.CsInsn, reg_id: int) -> int:
        rname = self.reg_name(insn, reg_id)
        if rname == "st":
            return 0
        if rname.startswith("st(") and rname.endswith(")"):
            return int(rname[3:-1])
        raise ValueError(f"Unexpected FPU register {rname!r} at 0x{insn.address:08x}")

    def calc_ea(self, insn: capstone.CsInsn, mem: cs_x86.X86OpMem) -> IRValue:
        parts: list[IRValue] = []
        if mem.base != 0:
            parts.append(Reg(self.reg_name(insn, mem.base)))
        if mem.index != 0:
            idx_val: IRValue = Reg(self.reg_name(insn, mem.index))
            if mem.scale > 1:
                shift = {2: 1, 4: 2, 8: 3}[mem.scale]
                idx_val = self.eval_expr(BinOp("shl", 32, idx_val, Const(shift, 32)), 32)
            parts.append(idx_val)
        disp = mem.disp & 0xFFFFFFFF
        if disp != 0 or not parts:
            parts.append(Const(disp, 32))

        acc = parts[0]
        for p in parts[1:]:
            acc = self.eval_expr(BinOp("add", 32, acc, p), 32)

        if mem.segment != 0:
            seg_name = self.reg_name(insn, mem.segment)
            if seg_name == "fs":
                acc = self.eval_expr(BinOp("add", 32, Reg("fs_0"), acc), 32)
            elif seg_name not in ("ds", "es", "ss", "cs"):
                raise ValueError(f"Unsupported segment {seg_name} at 0x{insn.address:08x}")
        return acc

    def read_op(self, insn: capstone.CsInsn, op: cs_x86.X86Op, bits: int | None = None) -> IRValue:
        w = bits if bits is not None else op.size * 8
        if op.type == cs_x86.X86_OP_REG:
            rname = self.reg_name(insn, op.reg)
            return Reg(rname)
        if op.type == cs_x86.X86_OP_IMM:
            return Const(op.imm & _MASK[w], w)
        if op.type == cs_x86.X86_OP_MEM:
            ea = self.calc_ea(insn, op.mem)
            return self.eval_expr(MemLoad(ea, w), w)
        raise ValueError(f"Unsupported operand type {op.type} at 0x{insn.address:08x}")

    def write_op(self, insn: capstone.CsInsn, op: cs_x86.X86Op, val: IRValue, bits: int | None = None) -> None:
        w = bits if bits is not None else op.size * 8
        if op.type == cs_x86.X86_OP_REG:
            rname = self.reg_name(insn, op.reg)
            self.emit(WriteReg(rname, val))
            return
        if op.type == cs_x86.X86_OP_MEM:
            ea = self.calc_ea(insn, op.mem)
            self.emit(WriteMem(ea, w, val))
            return
        raise ValueError(f"Cannot write operand type {op.type} at 0x{insn.address:08x}")

    def read_fpu_src(self, insn: capstone.CsInsn, op: cs_x86.X86Op) -> IRValue:
        if op.type == cs_x86.X86_OP_REG:
            idx = self.st_index(insn, op.reg)
            return self.eval_expr(FpuPeek(idx), 64, is_float=True)
        if op.type == cs_x86.X86_OP_MEM:
            ea = self.calc_ea(insn, op.mem)
            return self.eval_expr(FpuLoadMem(ea, op.size * 8), 64, is_float=True)
        raise ValueError(f"Unsupported FPU src operand at 0x{insn.address:08x}")

    def push32(self, val: IRValue) -> None:
        new_esp = self.eval_expr(BinOp("sub", 32, Reg("esp"), Const(4, 32)), 32)
        self.emit(WriteReg("esp", new_esp))
        self.emit(WriteMem(new_esp, 32, val))

    def pop32_to_temp(self) -> Temp:
        cur_esp = self.eval_expr(ReadVal(Reg("esp")), 32)
        val = self.eval_expr(MemLoad(cur_esp, 32), 32)
        new_esp = self.eval_expr(BinOp("add", 32, cur_esp, Const(4, 32)), 32)
        self.emit(WriteReg("esp", new_esp))
        return val


def _lift_bin_alu(ctx: _LiftContext, insn: capstone.CsInsn, op_kind: str) -> None:
    op0, op1 = insn.operands[0], insn.operands[1]
    w = op0.size * 8
    # Evaluate EA once for RMW memory destination so side effects/loads stay clean
    if op0.type == cs_x86.X86_OP_MEM:
        ea = ctx.calc_ea(insn, op0.mem)
        lhs: IRValue = ctx.eval_expr(MemLoad(ea, w), w)
    else:
        ea = None
        lhs = ctx.read_op(insn, op0, w)
    rhs = ctx.read_op(insn, op1, w)

    if op_kind in ("adc", "sbb"):
        cf = ctx.eval_expr(ReadVal(Flag("cf")), w)
        if op_kind == "adc":
            tmp = ctx.eval_expr(BinOp("add", w, lhs, rhs), w)
            res = ctx.eval_expr(BinOp("add", w, tmp, cf), w)
        else:
            tmp = ctx.eval_expr(BinOp("sub", w, lhs, rhs), w)
            res = ctx.eval_expr(BinOp("sub", w, tmp, cf), w)
        ctx.emit(UpdateFlags(op_kind, w, lhs, rhs, res, carry_in=cf))
    elif op_kind in ("cmp", "test"):
        alu = "sub" if op_kind == "cmp" else "and"
        flag_op = "cmp" if op_kind == "cmp" else "logic"
        res = ctx.eval_expr(BinOp(alu, w, lhs, rhs), w)
        ctx.emit(UpdateFlags(flag_op, w, lhs, rhs, res))
        return
    else:
        res = ctx.eval_expr(BinOp(op_kind, w, lhs, rhs), w)
        flag_op = "logic" if op_kind in ("and", "or", "xor") else op_kind
        ctx.emit(UpdateFlags(flag_op, w, lhs, rhs, res))

    if ea is not None:
        ctx.emit(WriteMem(ea, w, res))
    else:
        ctx.write_op(insn, op0, res, w)


def _lift_shift(ctx: _LiftContext, insn: capstone.CsInsn, op_kind: str) -> None:
    op0, op1 = insn.operands[0], insn.operands[1]
    w = op0.size * 8
    if op0.type == cs_x86.X86_OP_MEM:
        ea = ctx.calc_ea(insn, op0.mem)
        lhs: IRValue = ctx.eval_expr(MemLoad(ea, w), w)
    else:
        ea = None
        lhs = ctx.read_op(insn, op0, w)

    cnt_raw = ctx.read_op(insn, op1, 8 if op1.size == 1 else w)
    cnt32 = cnt_raw if isinstance(cnt_raw, Const) else ctx.eval_expr(UnOp("zext8_32", 32, cnt_raw), 32)
    cnt_masked = ctx.eval_expr(BinOp("and", 32, cnt32, Const(0x1F, 32)), 32)
    res = ctx.eval_expr(BinOp(op_kind, w, lhs, cnt_masked), w)
    ctx.emit(UpdateFlags(op_kind, w, lhs, cnt_masked, res))
    if ea is not None:
        ctx.emit(WriteMem(ea, w, res))
    else:
        ctx.write_op(insn, op0, res, w)


def _lift_unary_alu(ctx: _LiftContext, insn: capstone.CsInsn, mn: str) -> None:
    op0 = insn.operands[0]
    w = op0.size * 8
    if op0.type == cs_x86.X86_OP_MEM:
        ea = ctx.calc_ea(insn, op0.mem)
        val: IRValue = ctx.eval_expr(MemLoad(ea, w), w)
    else:
        ea = None
        val = ctx.read_op(insn, op0, w)

    if mn == "inc":
        res = ctx.eval_expr(BinOp("add", w, val, Const(1, w)), w)
        ctx.emit(UpdateFlags("inc", w, val, Const(1, w), res))
    elif mn == "dec":
        res = ctx.eval_expr(BinOp("sub", w, val, Const(1, w)), w)
        ctx.emit(UpdateFlags("dec", w, val, Const(1, w), res))
    elif mn == "neg":
        res = ctx.eval_expr(UnOp("neg", w, val), w)
        ctx.emit(UpdateFlags("neg", w, val, Const(0, w), res))
    elif mn == "not":
        res = ctx.eval_expr(UnOp("not", w, val), w)
    else:
        raise ValueError(f"Unexpected unary op {mn}")

    if ea is not None:
        ctx.emit(WriteMem(ea, w, res))
    else:
        ctx.write_op(insn, op0, res, w)


def _lift_mul_imul(ctx: _LiftContext, insn: capstone.CsInsn, signed: bool) -> None:
    ops = insn.operands
    if len(ops) == 1:
        op0 = ops[0]
        w = op0.size * 8
        rhs = ctx.read_op(insn, op0, w)
        if w == 8:
            lhs64 = ctx.eval_expr(UnOp("sext8_32" if signed else "zext8_32", 32, Reg("al")), 32)
            rhs64 = ctx.eval_expr(UnOp("sext8_32" if signed else "zext8_32", 32, rhs), 32)
            prod = ctx.eval_expr(BinOp("mul", 32, lhs64, rhs64), 32)
            ax_val = ctx.eval_expr(UnOp("trunc32_16", 16, prod), 16)
            ctx.emit(WriteReg("ax", ax_val))
            ctx.emit(UpdateFlags("imul" if signed else "mul", 8, Reg("al"), rhs, prod))
        elif w == 16:
            lhs32 = ctx.eval_expr(UnOp("sext16_32" if signed else "zext16_32", 32, Reg("ax")), 32)
            rhs32 = ctx.eval_expr(UnOp("sext16_32" if signed else "zext16_32", 32, rhs), 32)
            prod = ctx.eval_expr(BinOp("mul", 32, lhs32, rhs32), 32)
            lo = ctx.eval_expr(UnOp("trunc32_16", 16, prod), 16)
            hi32 = ctx.eval_expr(BinOp("shr", 32, prod, Const(16, 32)), 32)
            hi = ctx.eval_expr(UnOp("trunc32_16", 16, hi32), 16)
            ctx.emit(WriteReg("ax", lo))
            ctx.emit(WriteReg("dx", hi))
            ctx.emit(UpdateFlags("imul" if signed else "mul", 16, Reg("ax"), rhs, prod))
        else:
            op_64 = "mul64_s" if signed else "mul64_u"
            prod64 = ctx.eval_expr(BinOp(op_64, 64, Reg("eax"), rhs), 64)
            lo = ctx.eval_expr(UnOp("trunc64_lo", 32, prod64), 32)
            hi = ctx.eval_expr(UnOp("trunc64_hi", 32, prod64), 32)
            ctx.emit(WriteReg("eax", lo))
            ctx.emit(WriteReg("edx", hi))
            ctx.emit(UpdateFlags("imul" if signed else "mul", 32, Reg("eax"), rhs, prod64))
        return

    # 2-operand or 3-operand imul
    op0 = ops[0]
    w = op0.size * 8
    if len(ops) == 2:
        lhs = ctx.read_op(insn, op0, w)
        rhs = ctx.read_op(insn, ops[1], w)
    else:
        lhs = ctx.read_op(insn, ops[1], w)
        rhs = ctx.read_op(insn, ops[2], w)

    if w == 16:
        s_lhs = ctx.eval_expr(UnOp("sext16_32", 32, lhs), 32)
        s_rhs = ctx.eval_expr(UnOp("sext16_32", 32, rhs), 32)
        prod = ctx.eval_expr(BinOp("mul", 32, s_lhs, s_rhs), 32)
        res = ctx.eval_expr(UnOp("trunc32_16", 16, prod), 16)
        ctx.emit(UpdateFlags("imul", 16, lhs, rhs, prod))
    else:
        prod64 = ctx.eval_expr(BinOp("mul64_s", 64, lhs, rhs), 64)
        res = ctx.eval_expr(UnOp("trunc64_lo", 32, prod64), 32)
        ctx.emit(UpdateFlags("imul", 32, lhs, rhs, prod64))
    ctx.write_op(insn, op0, res, w)


def _lift_div(ctx: _LiftContext, insn: capstone.CsInsn, signed: bool) -> None:
    op0 = insn.operands[0]
    w = op0.size * 8
    if w != 32:
        raise ValueError(f"Unsupported div width {w} at 0x{insn.address:08x}")
    divisor = ctx.read_op(insn, op0, 32)
    dividend64 = ctx.eval_expr(BinOp("pack64", 64, Reg("edx"), Reg("eax")), 64)
    q_op = "div64_s" if signed else "div64_u"
    r_op = "mod64_s" if signed else "mod64_u"
    quot = ctx.eval_expr(BinOp(q_op, 32, dividend64, divisor), 32)
    rem = ctx.eval_expr(BinOp(r_op, 32, dividend64, divisor), 32)
    ctx.emit(WriteReg("eax", quot))
    ctx.emit(WriteReg("edx", rem))


def _lift_x87(ctx: _LiftContext, insn: capstone.CsInsn) -> bool:
    mn = insn.mnemonic
    ops = insn.operands

    if mn == "fldz":
        ctx.emit(FpuPush(FConst(0.0)))
        return True
    if mn == "fld1":
        ctx.emit(FpuPush(FConst(1.0)))
        return True
    if mn == "fchs":
        v = ctx.eval_expr(FpuPeek(0), 64, is_float=True)
        ctx.emit(FpuSet(0, ctx.eval_expr(FUnOp("fchs", v), 64, is_float=True)))
        return True
    if mn == "fabs":
        v = ctx.eval_expr(FpuPeek(0), 64, is_float=True)
        ctx.emit(FpuSet(0, ctx.eval_expr(FUnOp("fabs", v), 64, is_float=True)))
        return True
    if mn == "fld":
        val = ctx.read_fpu_src(insn, ops[0])
        ctx.emit(FpuPush(val))
        return True
    if mn == "fild":
        ea = ctx.calc_ea(insn, ops[0].mem)
        val = ctx.eval_expr(FpuLoadInt(ea, ops[0].size * 8), 64, is_float=True)
        ctx.emit(FpuPush(val))
        return True
    if mn in ("fst", "fstp"):
        pop = mn == "fstp"
        st0 = ctx.eval_expr(FpuPeek(0), 64, is_float=True)
        if ops[0].type == cs_x86.X86_OP_MEM:
            ea = ctx.calc_ea(insn, ops[0].mem)
            ctx.emit(FpuStoreMem(ea, ops[0].size * 8, st0))
        else:
            idx = ctx.st_index(insn, ops[0].reg)
            ctx.emit(FpuSet(idx, st0))
        if pop:
            ctx.emit(FpuPop())
        return True
    if mn in ("fist", "fistp"):
        ea = ctx.calc_ea(insn, ops[0].mem)
        st0 = ctx.eval_expr(FpuPeek(0), 64, is_float=True)
        ctx.emit(FpuStoreInt(ea, ops[0].size * 8, st0))
        if mn == "fistp":
            ctx.emit(FpuPop())
        return True
    if mn == "fxch":
        idx = 1
        if len(ops) == 1:
            idx = ctx.st_index(insn, ops[0].reg)
        elif len(ops) == 2:
            i0 = ctx.st_index(insn, ops[0].reg)
            i1 = ctx.st_index(insn, ops[1].reg)
            idx = i1 if i0 == 0 else i0
        if idx != 0:
            ctx.emit(FpuSwap(idx))
        return True
    if mn == "fnstsw":
        ctx.write_op(insn, ops[0], Reg("fpu_sw"), 16)
        return True
    if mn == "fnstcw":
        ea = ctx.calc_ea(insn, ops[0].mem)
        ctx.emit(WriteMem(ea, 16, Reg("fpu_cw")))
        return True
    if mn == "fldcw":
        ea = ctx.calc_ea(insn, ops[0].mem)
        cw = ctx.eval_expr(MemLoad(ea, 16), 16)
        ctx.emit(WriteReg("fpu_cw", cw))
        return True
    if mn in ("fnclex", "fclex"):
        ctx.emit(FpuClearEx())
        return True
    if mn in ("fcom", "fcomp", "fcompp", "fucom", "fucomp", "fucompp"):
        lhs = ctx.eval_expr(FpuPeek(0), 64, is_float=True)
        if not ops:
            rhs: IRValue = ctx.eval_expr(FpuPeek(1), 64, is_float=True)
        else:
            rhs = ctx.read_fpu_src(insn, ops[0])
        ctx.emit(FpuCmp(lhs, rhs, set_eflags=False))
        if mn.endswith("pp"):
            ctx.emit(FpuPop())
            ctx.emit(FpuPop())
        elif mn.endswith("p"):
            ctx.emit(FpuPop())
        return True

    # Integer-mem FPU arithmetic: fiadd/fisub/fisubr/fimul/fidiv/fidivr
    int_arith = {
        "fiadd": ("fadd", False),
        "fisub": ("fsub", False),
        "fisubr": ("fsub", True),
        "fimul": ("fmul", False),
        "fidiv": ("fdiv", False),
        "fidivr": ("fdiv", True),
    }
    if mn in int_arith:
        fop, rev = int_arith[mn]
        ea = ctx.calc_ea(insn, ops[0].mem)
        rhs = ctx.eval_expr(FpuLoadInt(ea, ops[0].size * 8), 64, is_float=True)
        lhs = ctx.eval_expr(FpuPeek(0), 64, is_float=True)
        a, b = (rhs, lhs) if rev else (lhs, rhs)
        ctx.emit(FpuSet(0, ctx.eval_expr(FBinOp(fop, a, b), 64, is_float=True)))
        return True

    # Standard FPU binary arithmetic: fadd/faddp/fsub/fsubp/fsubr/fsubrp/fmul/fmulp/fdiv/fdivp/fdivr/fdivrp
    fp_arith = {
        "fadd": ("fadd", False, False),
        "faddp": ("fadd", False, True),
        "fsub": ("fsub", False, False),
        "fsubp": ("fsub", False, True),
        "fsubr": ("fsub", True, False),
        "fsubrp": ("fsub", True, True),
        "fmul": ("fmul", False, False),
        "fmulp": ("fmul", False, True),
        "fdiv": ("fdiv", False, False),
        "fdivp": ("fdiv", False, True),
        "fdivr": ("fdiv", True, False),
        "fdivrp": ("fdiv", True, True),
    }
    if mn in fp_arith:
        fop, rev, pop = fp_arith[mn]
        if len(ops) == 0:
            # Implicit `f*p` == `f*p st(1), st(0)`
            dst_idx = 1
            dst_val = ctx.eval_expr(FpuPeek(1), 64, is_float=True)
            src_val = ctx.eval_expr(FpuPeek(0), 64, is_float=True)
        elif len(ops) == 1:
            op0 = ops[0]
            if op0.type == cs_x86.X86_OP_MEM:
                dst_idx = 0
                dst_val = ctx.eval_expr(FpuPeek(0), 64, is_float=True)
                src_val = ctx.read_fpu_src(insn, op0)
            elif pop:
                # `fsubp st(i)` / `fsubrp st(i)` etc. -> dst=st(i), src=st(0), then pop
                dst_idx = ctx.st_index(insn, op0.reg)
                dst_val = ctx.eval_expr(FpuPeek(dst_idx), 64, is_float=True)
                src_val = ctx.eval_expr(FpuPeek(0), 64, is_float=True)
            else:
                # `fsub st(i)` / `fsubr st(i)` -> dst=st(0), src=st(i)
                dst_idx = 0
                dst_val = ctx.eval_expr(FpuPeek(0), 64, is_float=True)
                src_val = ctx.read_fpu_src(insn, op0)
        else:
            # 2 operands: `fsub st(i), st(0)` or `fsubr st(i), st(0)`
            dst_idx = ctx.st_index(insn, ops[0].reg)
            dst_val = ctx.eval_expr(FpuPeek(dst_idx), 64, is_float=True)
            src_val = ctx.read_fpu_src(insn, ops[1])

        a, b = (src_val, dst_val) if rev else (dst_val, src_val)
        res = ctx.eval_expr(FBinOp(fop, a, b), 64, is_float=True)
        ctx.emit(FpuSet(dst_idx, res))
        if pop:
            ctx.emit(FpuPop())
        return True

    return False


def _lift_instruction(ctx: _LiftContext, insn: capstone.CsInsn, is_terminator: bool, blk: BasicBlock) -> None:
    mn = insn.mnemonic
    ops = insn.operands
    ctx.emit(Comment(insn.address, f"{mn} {insn.op_str}".strip()))

    if is_terminator:
        return

    if mn == "nop":
        return

    if mn == "mov":
        op0, op1 = ops[0], ops[1]
        w = op0.size * 8
        val = ctx.read_op(insn, op1, w)
        ctx.write_op(insn, op0, val, w)
        return

    if mn == "movzx":
        op0, op1 = ops[0], ops[1]
        dw, sw = op0.size * 8, op1.size * 8
        src = ctx.read_op(insn, op1, sw)
        op_name = f"zext{sw}_{dw}"
        res = ctx.eval_expr(UnOp(op_name, dw, src), dw)
        ctx.write_op(insn, op0, res, dw)
        return

    if mn == "movsx":
        op0, op1 = ops[0], ops[1]
        dw, sw = op0.size * 8, op1.size * 8
        src = ctx.read_op(insn, op1, sw)
        op_name = f"sext{sw}_{dw}"
        res = ctx.eval_expr(UnOp(op_name, dw, src), dw)
        ctx.write_op(insn, op0, res, dw)
        return

    if mn == "lea":
        op0, op1 = ops[0], ops[1]
        ea = ctx.calc_ea(insn, op1.mem)
        ctx.write_op(insn, op0, ea, 32)
        return

    if mn == "push":
        val = ctx.read_op(insn, ops[0], 32)
        ctx.push32(val)
        return

    if mn == "pop":
        val = ctx.pop32_to_temp()
        ctx.write_op(insn, ops[0], val, 32)
        return

    if mn in ("add", "adc", "sub", "sbb", "and", "or", "xor", "cmp", "test"):
        _lift_bin_alu(ctx, insn, mn)
        return

    if mn in ("shl", "shr", "sar", "rol", "ror"):
        _lift_shift(ctx, insn, mn)
        return

    if mn in ("inc", "dec", "neg", "not"):
        _lift_unary_alu(ctx, insn, mn)
        return

    if mn == "mul":
        _lift_mul_imul(ctx, insn, signed=False)
        return
    if mn == "imul":
        _lift_mul_imul(ctx, insn, signed=True)
        return
    if mn == "div":
        _lift_div(ctx, insn, signed=False)
        return
    if mn == "idiv":
        _lift_div(ctx, insn, signed=True)
        return

    if mn == "cdq":
        hi = ctx.eval_expr(BinOp("sar", 32, Reg("eax"), Const(31, 32)), 32)
        ctx.emit(WriteReg("edx", hi))
        return

    if mn.startswith("set"):
        cond = mn[3:]
        cval = ctx.eval_expr(CondExpr(cond), 8)
        ctx.write_op(insn, ops[0], cval, 8)
        return

    if mn.startswith("cmov"):
        cond = mn[4:]
        op0, op1 = ops[0], ops[1]
        w = op0.size * 8
        cval = ctx.eval_expr(CondExpr(cond), 8)
        lhs = ctx.read_op(insn, op0, w)
        rhs = ctx.read_op(insn, op1, w)
        sel = ctx.eval_expr(Select(cval, rhs, lhs, w), w)
        ctx.write_op(insn, op0, sel, w)
        return

    # String operations (handle both prefixed `rep*` and bare `movsb`/`movsw` etc.)
    parts = mn.split()
    rep_pref = parts[0] if len(parts) == 2 and parts[0] in ("rep", "repe", "repz", "repne", "repnz") else None
    base_str = parts[-1]
    str_map = {
        "movsb": ("movs", 8),
        "movsw": ("movs", 16),
        "movsd": ("movs", 32),
        "stosb": ("stos", 8),
        "stosw": ("stos", 16),
        "stosd": ("stos", 32),
        "cmpsb": ("cmps", 8),
        "cmpsw": ("cmps", 16),
        "cmpsd": ("cmps", 32),
        "scasb": ("scas", 8),
        "scasw": ("scas", 16),
        "scasd": ("scas", 32),
    }
    if base_str in str_map:
        kind, bits = str_map[base_str]
        norm_rep = "repe" if rep_pref == "repz" else ("repne" if rep_pref == "repnz" else rep_pref)
        ctx.emit(StringOp(kind=kind, bits=bits, rep=norm_rep))
        return

    if mn == "call":
        ret_va = insn.address + insn.size
        op0 = ops[0]
        if op0.type == cs_x86.X86_OP_IMM:
            tgt = op0.imm & 0xFFFFFFFF
            ctx.push32(Const(ret_va, 32))
            if tgt in ctx.all_entry_vas:
                ctx.emit(CallDirect(tgt, ret_va))
            elif tgt >= MBAA_CRT_START_VA:
                ctx.emit(CallCRT(tgt, ret_va))
            else:
                ctx.unhandled.append((insn.address, f"unknown call target 0x{tgt:08x}"))
            return
        if op0.type == cs_x86.X86_OP_MEM and op0.mem.base == 0 and op0.mem.index == 0:
            disp = op0.mem.disp & 0xFFFFFFFF
            if disp in ctx.pe.iat:
                ctx.push32(Const(ret_va, 32))
                ctx.emit(CallIAT(disp, ret_va))
                return
        tgt_val = ctx.read_op(insn, op0, 32)
        ctx.push32(Const(ret_va, 32))
        ctx.emit(CallIndirect(tgt_val, ret_va))
        return

    if _lift_x87(ctx, insn):
        return

    ctx.unhandled.append((insn.address, f"{mn} {insn.op_str}".strip()))


def _lift_terminator(ctx: _LiftContext, blk: BasicBlock) -> IRTerm:
    last = blk.insns[-1]
    mn = last.mnemonic
    ops = last.operands
    term = blk.terminator

    if term == "ret":
        extra = (ops[0].imm & 0xFFFF) if ops and ops[0].type == cs_x86.X86_OP_IMM else 0
        return TermRet(pop_extra=extra)
    if term == "fallthrough":
        return TermFallthrough(blk.fallthrough_target)  # type: ignore[arg-type]
    if term == "branch":
        return TermJump(blk.fallthrough_target)  # type: ignore[arg-type]
    if term == "cond_branch":
        assert blk.cond_target is not None and blk.fallthrough_target is not None
        if mn.startswith("j"):
            cond = "ecx_z" if mn in ("jcxz", "jecxz") else mn[1:]
        else:
            cond = mn  # loop / loope / loopne
        return TermBranch(cond=cond, target_va=blk.cond_target, fallthrough_va=blk.fallthrough_target)
    if term == "switch":
        assert blk.switch_table is not None
        idx_val = Reg(blk.switch_table.index_reg)
        return TermSwitch(
            index=idx_val,
            targets=tuple(blk.switch_table.targets),
            table_va=blk.switch_table.table_va,
        )
    if term == "tail_call_game":
        assert blk.tail_target is not None
        return TermTailCallGame(blk.tail_target)
    if term == "tail_call_crt":
        assert blk.tail_target is not None
        return TermTailCallCRT(blk.tail_target)
    if term == "tail_call_iat":
        assert blk.tail_target is not None
        return TermTailCallIAT(blk.tail_target)
    if term == "tail_call_indirect":
        tgt_val = ctx.read_op(last, ops[0], 32)
        return TermTailCallIndirect(tgt_val)
    if term == "trap":
        return TermTrap(last.address, mn)
    raise ValueError(f"Unknown block terminator {term!r} at 0x{blk.start_va:08x}")


def lift_function(fcfg: FunctionCFG, pe: PEBinary, all_entry_vas: set[int]) -> IRFunction:
    """Lift a recovered FunctionCFG into typed IR."""
    ctx = _LiftContext(pe, all_entry_vas)
    ir_blocks: dict[int, IRBlock] = {}

    for b_va in fcfg.block_order:
        blk = fcfg.blocks[b_va]
        ctx.stmts = []
        n = len(blk.insns)
        has_term_insn = blk.terminator != "fallthrough"
        for idx, insn in enumerate(blk.insns):
            is_term = has_term_insn and (idx == n - 1)
            _lift_instruction(ctx, insn, is_term, blk)
        term = _lift_terminator(ctx, blk)
        ir_blocks[b_va] = IRBlock(start_va=b_va, stmts=ctx.stmts, term=term)

    return IRFunction(
        entry_va=fcfg.entry_va,
        name=fcfg.name,
        subsystem=fcfg.subsystem,
        is_canonical=fcfg.is_canonical,
        blocks=ir_blocks,
        block_order=list(fcfg.block_order),
        temp_types=ctx.temp_types,
        insn_count=fcfg.insn_count,
        unhandled=ctx.unhandled,
    )


def lift_program(pcfg: ProgramCFG) -> tuple[dict[int, IRFunction], list[tuple[int, int, str]]]:
    """Lift all functions in a ProgramCFG and return `(ir_funcs, unhandled_list)`."""
    pe = PEBinary(pcfg.exe_path)
    all_entry_vas = set(pcfg.functions.keys())
    ir_funcs: dict[int, IRFunction] = {}
    all_unhandled: list[tuple[int, int, str]] = []

    for va, fcfg in pcfg.functions.items():
        ir_fn = lift_function(fcfg, pe, all_entry_vas)
        ir_funcs[va] = ir_fn
        for insn_va, desc in ir_fn.unhandled:
            all_unhandled.append((va, insn_va, desc))

    return ir_funcs, all_unhandled


def main() -> None:
    from .cfg import recover_program_cfg

    pcfg = recover_program_cfg()
    ir_funcs, unhandled = lift_program(pcfg)
    total_stmts = sum(len(b.stmts) for f in ir_funcs.values() for b in f.blocks.values())
    print(f"Lifted {len(ir_funcs)} functions, {pcfg.total_insns} x86 insns -> {total_stmts} IR stmts, unhandled={len(unhandled)}")
    if unhandled:
        for fn_va, iv, desc in unhandled[:20]:
            print(f"  UNHANDLED fn=0x{fn_va:08x} insn=0x{iv:08x}: {desc}")
        raise SystemExit(1)


if __name__ == "__main__":
    main()
