"""Clean recursive-descent CFG recovery for MBAA.exe game .text functions.

Starts strictly from verified function entry VAs, follows branches, fallthroughs,
and switch jump tables, and never decodes inline jump-table data bytes or padding
as instructions. Verifies 0 unresolved intra-function branch targets.
"""

from __future__ import annotations

import argparse
import json
import struct
from collections import Counter, deque
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any

import capstone
import pefile

DEFAULT_MBAA_EXE = Path(r"c:\Users\A\Desktop\AI\google\MBAACC\MBAA.exe")
DEFAULT_FUNCTION_MAP = Path(r"c:\Users\A\Desktop\AI\google\mbaacc-src\evidence\function_map.json")
DEFAULT_RTTI_VTABLES = Path(r"c:\Users\A\Desktop\AI\google\mbaacc-src\evidence\rtti_vtables.json")

MBAA_IMAGE_BASE = 0x00400000
MBAA_GAME_TEXT_END = 0x004DF020  # Static locale/ctype table begins at 0x004DF020; CRT begins at 0x004E00D0
MBAA_CRT_START_VA = 0x004E00D0
MBAA_CRT_XCA_CODE_START = 0x00518D50
MBAA_CRT_XCA_START = 0x0051B410
MBAA_CRT_XCZ_END = 0x0051B584

# Known verified function-pointer callbacks stored solely in .data tables
# (e.g. 0x0054ede8 scene dispatch table, 0x0054dd88 menu callbacks, 0x0054d080 dialog proc).
EXTRA_DATA_CALLBACK_VAS: tuple[int, ...] = (
    0x00433BC0,
    0x004367C0,
    0x00479F70,
    0x0047A010,
    0x0047A060,
    0x0047A130,
    0x0047A200,
    0x0047A2D0,
    0x0047A3A0,
    0x0047A470,
    0x0047A540,
    0x0047A620,
    0x0047A740,
    0x0047A840,
    0x0047A930,
    0x0047AA70,
    0x0047AB70,
    0x0047AC50,
    0x0047AD10,
    0x004A1F30,
)

EXTRA_DATA_CALLBACK_SUBSYSTEMS: dict[int, str] = {
    0x00433BC0: "Scene",
    0x004367C0: "Scene",
    0x004A1F30: "Core/Windows",
}


@dataclass
class SwitchTable:
    site_va: int
    table_va: int
    index_reg: str
    targets: list[int]  # Ordered case targets [0..N-1]


@dataclass
class BasicBlock:
    start_va: int
    end_va: int
    insns: list[capstone.CsInsn]
    succs: list[int] = field(default_factory=list)
    terminator: str = "fallthrough"
    cond_target: int | None = None
    fallthrough_target: int | None = None
    tail_target: int | None = None
    switch_table: SwitchTable | None = None


@dataclass
class FunctionCFG:
    entry_va: int
    name: str
    subsystem: str
    is_canonical: bool
    blocks: dict[int, BasicBlock]
    block_order: list[int]
    switch_tables: list[SwitchTable]
    direct_calls: set[int] = field(default_factory=set)
    crt_calls: set[int] = field(default_factory=set)
    iat_calls: set[int] = field(default_factory=set)
    iat_refs: set[int] = field(default_factory=set)
    unresolved_targets: list[tuple[int, int, str]] = field(default_factory=list)
    decode_errors: list[tuple[int, str]] = field(default_factory=list)

    @property
    def insn_count(self) -> int:
        return sum(len(b.insns) for b in self.blocks.values())


@dataclass
class ProgramCFG:
    exe_path: Path
    image_base: int
    text_va: int
    text_end: int
    iat: dict[int, dict[str, str]]
    functions: dict[int, FunctionCFG]
    canonical_vas: list[int]
    extra_callback_vas: list[int]
    crt_init_vas: list[int]
    vtable_slot_vas: set[int]
    func_ptr_vas: set[int]
    jump_table_bytes: set[int]
    total_blocks: int
    total_insns: int
    total_switch_tables: int
    unresolved_count: int
    decode_error_count: int
    used_iat_vas: set[int]
    used_crt_vas: set[int]


class PEBinary:
    """PE32 image helper with fast VA -> bytes/u32 reads and IAT extraction."""

    def __init__(self, exe_path: Path = DEFAULT_MBAA_EXE) -> None:
        self.exe_path = exe_path
        self.raw = exe_path.read_bytes()
        self.pe = pefile.PE(data=self.raw)
        self.image_base = self.pe.OPTIONAL_HEADER.ImageBase

        self.sections: list[tuple[int, int, int, int, str]] = []
        self.text_va = 0
        self.text_end = 0
        self.text_bytes = b""
        for sec in self.pe.sections:
            name = sec.Name.rstrip(b"\x00").decode("latin1", errors="replace")
            va_start = self.image_base + sec.VirtualAddress
            vsize = max(sec.Misc_VirtualSize, sec.SizeOfRawData)
            self.sections.append((va_start, va_start + vsize, sec.PointerToRawData, sec.SizeOfRawData, name))
            if name == ".text":
                self.text_va = va_start
                self.text_end = va_start + sec.Misc_VirtualSize
                self.text_bytes = self.raw[sec.PointerToRawData : sec.PointerToRawData + sec.Misc_VirtualSize]

        self.iat: dict[int, dict[str, str]] = {}
        for entry in getattr(self.pe, "DIRECTORY_ENTRY_IMPORT", []):
            dll = entry.dll.decode("latin1", errors="replace")
            for imp in entry.imports:
                imp_name = imp.name.decode("latin1", errors="replace") if imp.name else f"ord_{imp.ordinal}"
                self.iat[imp.address] = {
                    "va": f"0x{imp.address:08x}",
                    "dll": dll,
                    "name": imp_name,
                    "qname": f"{dll}!{imp_name}",
                }

    def va_to_offset(self, va: int) -> int | None:
        for va_s, va_e, raw_s, raw_sz, _ in self.sections:
            if va_s <= va < va_e:
                rel = va - va_s
                if rel < raw_sz:
                    return raw_s + rel
                return None
        return None

    def read_bytes(self, va: int, size: int) -> bytes:
        off = self.va_to_offset(va)
        if off is None or off + size > len(self.raw):
            return b""
        return self.raw[off : off + size]

    def read_u32(self, va: int) -> int | None:
        b = self.read_bytes(va, 4)
        if len(b) < 4:
            return None
        return struct.unpack_from("<I", b, 0)[0]


_BRANCH_MNEMONICS = {
    "jo", "jno", "jb", "jae", "je", "jne", "jbe", "ja",
    "js", "jns", "jp", "jnp", "jl", "jge", "jle", "jg",
    "jcxz", "jecxz", "loop", "loope", "loopne",
}


def _is_switch_mem_jmp(insn: capstone.CsInsn, pe: PEBinary) -> tuple[int, str] | None:
    if insn.mnemonic != "jmp" or not insn.operands:
        return None
    op0 = insn.operands[0]
    if op0.type != capstone.x86.X86_OP_MEM:
        return None
    mem = op0.mem
    disp = mem.disp & 0xFFFFFFFF
    if mem.base == 0 and mem.index != 0 and mem.scale == 4 and pe.text_va <= disp < MBAA_CRT_START_VA:
        reg_name = insn.reg_name(mem.index).lower()
        return disp, reg_name
    return None


def _parse_switch_targets(
    table_va: int,
    pe: PEBinary,
    known_table_starts: set[int],
) -> list[int]:
    targets: list[int] = []
    off = table_va - pe.text_va
    while 0 <= off and off + 4 <= len(pe.text_bytes):
        cur_tva = pe.text_va + off
        if targets and cur_tva in known_table_starts:
            break
        val = struct.unpack_from("<I", pe.text_bytes, off)[0]
        if not (pe.text_va <= val < MBAA_GAME_TEXT_END):
            break
        if abs(val - cur_tva) > 0x10000:
            break
        targets.append(val)
        off += 4
    return targets


def _make_disassembler(pe: PEBinary, md: capstone.Cs):
    """Create a cached block-batching x86-32 disassembler over game .text."""
    text_va = pe.text_va
    text_bytes = pe.text_bytes
    text_len = len(text_bytes)
    cache: dict[int, capstone.CsInsn | None] = {}

    def disasm_one(va: int) -> capstone.CsInsn | None:
        hit = cache.get(va)
        if hit is not None or va in cache:
            return hit
        pos = va - text_va
        if pos < 0 or pos >= text_len:
            cache[va] = None
            return None
        # Decode a contiguous chunk up to the next terminator to amortize Capstone FFI calls
        end_pos = min(text_len, pos + 128)
        first: capstone.CsInsn | None = None
        for insn in md.disasm(text_bytes[pos:end_pos], va):
            if insn.id == 0:
                break
            cache[insn.address] = insn
            if first is None:
                first = insn
            mn = insn.mnemonic
            if mn in ("ret", "retn", "retf", "iret", "iretd", "int3", "ud2", "jmp") or mn in _BRANCH_MNEMONICS:
                break
        if va not in cache:
            cache[va] = None
        return first

    return disasm_one


def _recover_single_function(
    entry_va: int,
    subsystem: str,
    is_canonical: bool,
    pe: PEBinary,
    disasm_one,
    all_entry_vas: set[int],
    known_table_starts: set[int],
    code_end: int = MBAA_GAME_TEXT_END,
) -> FunctionCFG:
    """Recover clean intra-function CFG for one function via recursive descent."""
    text_va = pe.text_va

    # Stage A: Discover all reachable instructions, switch tables, and block start VAs.
    block_starts: set[int] = {entry_va}
    insn_at: dict[int, capstone.CsInsn] = {}
    switch_by_site: dict[int, SwitchTable] = {}
    decode_errors: list[tuple[int, str]] = []
    unresolved_targets: list[tuple[int, int, str]] = []
    direct_calls: set[int] = set()
    crt_calls: set[int] = set()
    iat_calls: set[int] = set()
    iat_refs: set[int] = set()

    queue: deque[int] = deque([entry_va])
    while queue:
        cur = queue.popleft()
        if cur in insn_at:
            continue
        while True:
            if cur in insn_at:
                break
            if not (text_va <= cur < code_end):
                decode_errors.append((cur, "va_out_of_game_text"))
                break
            insn = disasm_one(cur)
            if insn is None or insn.id == 0:
                decode_errors.append((cur, "capstone_decode_failed"))
                break
            insn_at[cur] = insn

            # Record all IAT / call / CRT references
            for op in insn.operands:
                if op.type == capstone.x86.X86_OP_MEM:
                    disp = op.mem.disp & 0xFFFFFFFF
                    if disp in pe.iat:
                        iat_refs.add(disp)
                elif op.type == capstone.x86.X86_OP_IMM:
                    imm = op.imm & 0xFFFFFFFF
                    if imm in pe.iat:
                        iat_refs.add(imm)

            mn = insn.mnemonic
            op0 = insn.operands[0] if insn.operands else None

            if mn == "call" and op0 is not None:
                if op0.type == capstone.x86.X86_OP_IMM:
                    tgt = op0.imm & 0xFFFFFFFF
                    if tgt >= MBAA_CRT_START_VA:
                        crt_calls.add(tgt)
                    elif tgt in all_entry_vas:
                        direct_calls.add(tgt)
                    else:
                        unresolved_targets.append((cur, tgt, "call_unknown_game_va"))
                elif op0.type == capstone.x86.X86_OP_MEM and op0.mem.base == 0 and op0.mem.index == 0:
                    disp = op0.mem.disp & 0xFFFFFFFF
                    if disp in pe.iat:
                        iat_calls.add(disp)

            if mn in ("ret", "retn", "retf", "iret", "iretd", "int3", "ud2"):
                break

            if mn == "jmp":
                if op0 is not None and op0.type == capstone.x86.X86_OP_IMM:
                    tgt = op0.imm & 0xFFFFFFFF
                    if tgt in all_entry_vas and tgt != entry_va:
                        direct_calls.add(tgt)
                    elif MBAA_CRT_START_VA <= tgt < MBAA_CRT_XCA_CODE_START:
                        crt_calls.add(tgt)
                    elif text_va <= tgt < code_end:
                        block_starts.add(tgt)
                        if tgt not in insn_at:
                            queue.append(tgt)
                    else:
                        unresolved_targets.append((cur, tgt, "jmp_out_of_range"))
                elif op0 is not None and op0.type == capstone.x86.X86_OP_MEM:
                    sw = _is_switch_mem_jmp(insn, pe)
                    if sw is not None:
                        table_va, idx_reg = sw
                        known_table_starts.add(table_va)
                        targets = _parse_switch_targets(table_va, pe, known_table_starts)
                        if not targets:
                            unresolved_targets.append((cur, table_va, "empty_switch_table"))
                        else:
                            switch_by_site[cur] = SwitchTable(
                                site_va=cur,
                                table_va=table_va,
                                index_reg=idx_reg,
                                targets=targets,
                            )
                            for tgt in targets:
                                block_starts.add(tgt)
                                if tgt not in insn_at:
                                    queue.append(tgt)
                    elif op0.mem.base == 0 and op0.mem.index == 0 and (op0.mem.disp & 0xFFFFFFFF) in pe.iat:
                        iat_calls.add(op0.mem.disp & 0xFFFFFFFF)
                break

            if mn in _BRANCH_MNEMONICS:
                if op0 is not None and op0.type == capstone.x86.X86_OP_IMM:
                    tgt = op0.imm & 0xFFFFFFFF
                    if text_va <= tgt < code_end:
                        block_starts.add(tgt)
                        if tgt not in insn_at:
                            queue.append(tgt)
                    else:
                        unresolved_targets.append((cur, tgt, "jcc_out_of_range"))
                fall = cur + insn.size
                block_starts.add(fall)
                if fall not in insn_at:
                    queue.append(fall)
                break

            cur += insn.size

    # Stage B: Split discovered instructions into disjoint basic blocks.
    valid_starts = sorted(va for va in block_starts if va in insn_at)
    blocks: dict[int, BasicBlock] = {}
    for b_va in valid_starts:
        b_insns: list[capstone.CsInsn] = []
        cur = b_va
        succs: list[int] = []
        term = "fallthrough"
        cond_tgt: int | None = None
        fall_tgt: int | None = None
        tail_tgt: int | None = None
        sw_obj: SwitchTable | None = None

        while True:
            insn = insn_at.get(cur)
            if insn is None:
                term = "trap"
                break
            b_insns.append(insn)
            nxt = cur + insn.size
            mn = insn.mnemonic
            op0 = insn.operands[0] if insn.operands else None

            if mn in ("ret", "retn", "retf", "iret", "iretd"):
                term = "ret"
                break
            if mn in ("int3", "ud2"):
                term = "trap"
                break
            if mn == "jmp":
                if op0 is not None and op0.type == capstone.x86.X86_OP_IMM:
                    tgt = op0.imm & 0xFFFFFFFF
                    if tgt in all_entry_vas and tgt != entry_va:
                        term = "tail_call_game"
                        tail_tgt = tgt
                    elif MBAA_CRT_START_VA <= tgt < MBAA_CRT_XCA_CODE_START:
                        term = "tail_call_crt"
                        tail_tgt = tgt
                    else:
                        term = "branch"
                        succs = [tgt]
                        fall_tgt = tgt
                elif cur in switch_by_site:
                    term = "switch"
                    sw_obj = switch_by_site[cur]
                    seen_s: set[int] = set()
                    for t in sw_obj.targets:
                        if t not in seen_s:
                            seen_s.add(t)
                            succs.append(t)
                elif op0 is not None and op0.type == capstone.x86.X86_OP_MEM and op0.mem.base == 0 and op0.mem.index == 0 and (op0.mem.disp & 0xFFFFFFFF) in pe.iat:
                    term = "tail_call_iat"
                    tail_tgt = op0.mem.disp & 0xFFFFFFFF
                else:
                    term = "tail_call_indirect"
                break
            if mn in _BRANCH_MNEMONICS:
                term = "cond_branch"
                if op0 is not None and op0.type == capstone.x86.X86_OP_IMM:
                    cond_tgt = op0.imm & 0xFFFFFFFF
                fall_tgt = nxt
                succs = []
                if cond_tgt is not None:
                    succs.append(cond_tgt)
                if fall_tgt not in succs:
                    succs.append(fall_tgt)
                break
            if nxt in block_starts:
                term = "fallthrough"
                fall_tgt = nxt
                succs = [nxt]
                break
            cur = nxt

        for s_va in succs:
            if s_va not in insn_at:
                unresolved_targets.append((b_insns[-1].address, s_va, f"missing_block_{term}"))

        blocks[b_va] = BasicBlock(
            start_va=b_va,
            end_va=b_insns[-1].address + b_insns[-1].size if b_insns else b_va,
            insns=b_insns,
            succs=succs,
            terminator=term,
            cond_target=cond_tgt,
            fallthrough_target=fall_tgt,
            tail_target=tail_tgt,
            switch_table=sw_obj,
        )

    # Compute deterministic BFS order starting from entry_va (preserving entry first, then sorted reachable)
    order: list[int] = []
    seen_order: set[int] = set()
    oq: deque[int] = deque([entry_va])
    while oq:
        v = oq.popleft()
        if v in seen_order or v not in blocks:
            continue
        seen_order.add(v)
        order.append(v)
        for s in blocks[v].succs:
            if s not in seen_order:
                oq.append(s)
    # Any remaining blocks (should be none) appended in VA order
    for v in valid_starts:
        if v not in seen_order:
            order.append(v)

    # Verify disjoint non-overlapping blocks
    sorted_blocks = sorted(blocks.values(), key=lambda b: b.start_va)
    for idx in range(len(sorted_blocks) - 1):
        if sorted_blocks[idx].end_va > sorted_blocks[idx + 1].start_va:
            unresolved_targets.append(
                (sorted_blocks[idx].start_va, sorted_blocks[idx + 1].start_va, "overlapping_blocks")
            )

    return FunctionCFG(
        entry_va=entry_va,
        name=f"sub_{entry_va:08x}",
        subsystem=subsystem,
        is_canonical=is_canonical,
        blocks=blocks,
        block_order=order,
        switch_tables=list(switch_by_site.values()),
        direct_calls=direct_calls,
        crt_calls=crt_calls,
        iat_calls=iat_calls,
        iat_refs=iat_refs,
        unresolved_targets=unresolved_targets,
        decode_errors=decode_errors,
    )


def _collect_crt_xca_inits(pe: PEBinary) -> list[int]:
    """Read non-zero C++ dynamic initializer pointers from .CRT$XCA..XCZ (0x0051B410..0x0051B584)."""
    inits: list[int] = []
    seen: set[int] = set()
    for table_va in range(MBAA_CRT_XCA_START, MBAA_CRT_XCZ_END, 4):
        fn_va = pe.read_u32(table_va)
        if fn_va and pe.text_va <= fn_va < pe.text_end and fn_va not in seen:
            seen.add(fn_va)
            inits.append(fn_va)
    return sorted(inits)


def recover_program_cfg(
    exe_path: Path = DEFAULT_MBAA_EXE,
    function_map_path: Path = DEFAULT_FUNCTION_MAP,
    rtti_vtables_path: Path = DEFAULT_RTTI_VTABLES,
    include_extra_callbacks: bool = True,
    include_crt_inits: bool = True,
) -> ProgramCFG:
    """Recover clean CFGs for all 3,570 canonical game functions (+ optional .data callbacks & .CRT$XCA inits)."""
    pe = PEBinary(exe_path)
    fm = json.loads(function_map_path.read_text(encoding="utf-8"))
    rtti = json.loads(rtti_vtables_path.read_text(encoding="utf-8"))

    canonical_map: dict[int, dict[str, Any]] = {}
    func_ptr_vas: set[int] = set()
    for fn in fm["functions"]:
        va = int(fn["start_va"], 16)
        if va < MBAA_CRT_START_VA:
            canonical_map[va] = fn
            if "func_ptr_imm" in fn.get("sources", []):
                func_ptr_vas.add(va)

    vtable_slot_vas: set[int] = set()
    for vt in rtti["vtables"]:
        for m in vt["methods"]:
            sva = int(m["va"], 16)
            if sva < MBAA_CRT_START_VA:
                vtable_slot_vas.add(sva)

    canonical_vas = sorted(canonical_map.keys())
    extra_vas = [va for va in EXTRA_DATA_CALLBACK_VAS if va not in canonical_map] if include_extra_callbacks else []
    crt_init_vas = _collect_crt_xca_inits(pe) if include_crt_inits else []
    crt_init_set = set(crt_init_vas)
    all_entry_vas = set(canonical_vas) | set(extra_vas) | crt_init_set

    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    disasm_one = _make_disassembler(pe, md)

    # Pass 1: discover all switch table start VAs so adjacent jump tables stop cleanly at boundaries.
    known_table_starts: set[int] = set()
    for va in sorted(all_entry_vas):
        sub = canonical_map[va]["subsystem"] if va in canonical_map else EXTRA_DATA_CALLBACK_SUBSYSTEMS.get(va, "Core/Windows" if va in crt_init_set else "MenuWindow")
        cend = pe.text_end if va in crt_init_set else MBAA_GAME_TEXT_END
        cfg_p1 = _recover_single_function(va, sub, va in canonical_map, pe, disasm_one, all_entry_vas, known_table_starts, code_end=cend)
        for sw in cfg_p1.switch_tables:
            known_table_starts.add(sw.table_va)

    # Pass 2: final CFG recovery with complete switch-table boundary knowledge.
    functions: dict[int, FunctionCFG] = {}
    jump_table_bytes: set[int] = set()
    used_iat_vas: set[int] = set()
    used_crt_vas: set[int] = set()
    total_blocks = 0
    total_insns = 0
    total_switch_tables = 0
    unresolved_count = 0
    decode_error_count = 0

    for va in sorted(all_entry_vas):
        is_can = va in canonical_map
        sub = canonical_map[va]["subsystem"] if is_can else EXTRA_DATA_CALLBACK_SUBSYSTEMS.get(va, "Core/Windows" if va in crt_init_set else "MenuWindow")
        cend = pe.text_end if va in crt_init_set else MBAA_GAME_TEXT_END
        fcfg = _recover_single_function(va, sub, is_can, pe, disasm_one, all_entry_vas, known_table_starts, code_end=cend)
        functions[va] = fcfg
        total_blocks += len(fcfg.blocks)
        total_insns += fcfg.insn_count
        total_switch_tables += len(fcfg.switch_tables)
        unresolved_count += len(fcfg.unresolved_targets)
        decode_error_count += len(fcfg.decode_errors)
        used_iat_vas |= fcfg.iat_refs
        used_crt_vas |= fcfg.crt_calls
        for sw in fcfg.switch_tables:
            for i in range(len(sw.targets) * 4):
                jump_table_bytes.add(sw.table_va + i)

    return ProgramCFG(
        exe_path=exe_path,
        image_base=pe.image_base,
        text_va=pe.text_va,
        text_end=pe.text_end,
        iat=pe.iat,
        functions=functions,
        canonical_vas=canonical_vas,
        extra_callback_vas=extra_vas,
        crt_init_vas=crt_init_vas,
        vtable_slot_vas=vtable_slot_vas,
        func_ptr_vas=func_ptr_vas,
        jump_table_bytes=jump_table_bytes,
        total_blocks=total_blocks,
        total_insns=total_insns,
        total_switch_tables=total_switch_tables,
        unresolved_count=unresolved_count,
        decode_error_count=decode_error_count,
        used_iat_vas=used_iat_vas,
        used_crt_vas=used_crt_vas,
    )


def summarize_cfg(pcfg: ProgramCFG) -> dict[str, Any]:
    mnemonics: Counter[str] = Counter()
    for fn in pcfg.functions.values():
        for blk in fn.blocks.values():
            for insn in blk.insns:
                mnemonics[insn.mnemonic] += 1
    canonical_insns = sum(pcfg.functions[va].insn_count for va in pcfg.canonical_vas)
    canonical_blocks = sum(len(pcfg.functions[va].blocks) for va in pcfg.canonical_vas)
    return {
        "canonical_functions": len(pcfg.canonical_vas),
        "extra_data_callbacks": len(pcfg.extra_callback_vas),
        "crt_xca_initializers": len(pcfg.crt_init_vas),
        "total_functions": len(pcfg.functions),
        "canonical_blocks": canonical_blocks,
        "canonical_instructions": canonical_insns,
        "total_blocks": pcfg.total_blocks,
        "total_instructions": pcfg.total_insns,
        "switch_tables": pcfg.total_switch_tables,
        "jump_table_bytes": len(pcfg.jump_table_bytes),
        "unresolved_targets": pcfg.unresolved_count,
        "decode_errors": pcfg.decode_error_count,
        "used_iat_vas": len(pcfg.used_iat_vas),
        "used_crt_vas": len(pcfg.used_crt_vas),
        "unique_mnemonics": len(mnemonics),
        "vtable_slots": len(pcfg.vtable_slot_vas),
        "func_ptrs": len(pcfg.func_ptr_vas),
    }


def main() -> None:
    parser = argparse.ArgumentParser(description="Recover and verify clean MBAA.exe game CFG.")
    parser.add_argument("--exe", type=Path, default=DEFAULT_MBAA_EXE)
    parser.add_argument("--function-map", type=Path, default=DEFAULT_FUNCTION_MAP)
    parser.add_argument("--rtti-vtables", type=Path, default=DEFAULT_RTTI_VTABLES)
    args = parser.parse_args()
    pcfg = recover_program_cfg(args.exe, args.function_map, args.rtti_vtables)
    summary = summarize_cfg(pcfg)
    print(json.dumps(summary, indent=2))
    if pcfg.unresolved_count != 0 or pcfg.decode_error_count != 0:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
