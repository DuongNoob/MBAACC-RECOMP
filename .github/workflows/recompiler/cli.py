"""CLI entry point for the MBAA.exe x86-32 -> C++20 AOT recompiler."""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

from .cfg import (
    DEFAULT_FUNCTION_MAP,
    DEFAULT_MBAA_EXE,
    DEFAULT_RTTI_VTABLES,
    PEBinary,
    recover_program_cfg,
    summarize_cfg,
)
from .cpp_emitter import ALL_SHARD_FILES, EXPECTED_GEN_HEADERS, emit_program
from .x86_lifter import lift_program

DEFAULT_OUT_DIR = Path(__file__).resolve().parent.parent / "build_gen"


def check_balanced_cpp_braces(src: str) -> tuple[bool, int]:
    """Verify balanced `{}` in C++ source, ignoring comments and string/char literals."""
    depth = 0
    i = 0
    n = len(src)
    while i < n:
        ch = src[i]
        nxt = src[i + 1] if i + 1 < n else ""
        if ch == "/" and nxt == "/":
            nl = src.find("\n", i + 2)
            i = n if nl == -1 else nl + 1
            continue
        if ch == "/" and nxt == "*":
            end = src.find("*/", i + 2)
            i = n if end == -1 else end + 2
            continue
        if ch == '"':
            i += 1
            while i < n:
                if src[i] == "\\":
                    i += 2
                    continue
                if src[i] == '"':
                    i += 1
                    break
                i += 1
            continue
        if ch == "'":
            i += 1
            while i < n:
                if src[i] == "\\":
                    i += 2
                    continue
                if src[i] == "'":
                    i += 1
                    break
                i += 1
            continue
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth < 0:
                return False, depth
        i += 1
    return depth == 0, depth


def verify_build_gen(out_dir: Path) -> dict[str, object]:
    """Verify generated `build_gen/` artifacts, headers, brace balance, and manifest invariants."""
    errors: list[str] = []
    expected = list(EXPECTED_GEN_HEADERS) + list(ALL_SHARD_FILES) + ["gen_manifest.json"]
    for name in expected:
        if not (out_dir / name).is_file():
            errors.append(f"Missing generated file: {out_dir / name}")

    manifest_path = out_dir / "gen_manifest.json"
    manifest: dict[str, object] = {}
    if manifest_path.is_file():
        manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
        if manifest.get("unhandled_instructions", -1) != 0:
            errors.append(f"unhandled_instructions={manifest.get('unhandled_instructions')} != 0")
        if manifest.get("unresolved_targets", -1) != 0:
            errors.append(f"unresolved_targets={manifest.get('unresolved_targets')} != 0")
        if manifest.get("decode_errors", -1) != 0:
            errors.append(f"decode_errors={manifest.get('decode_errors')} != 0")

    recomp_hdr = out_dir / "recomp_funcs.h"
    if recomp_hdr.is_file():
        hdr_txt = recomp_hdr.read_text(encoding="utf-8")
        for req in (
            '#include "mbaa_recomp/cpu_context.h"',
            '#include "mbaa_recomp/guest_memory.h"',
            '#include "mbaa_recomp/dispatch.h"',
            '#include "mbaa_recomp/hle_crt.h"',
            '#include "mbaa_recomp/hle_win32.h"',
        ):
            if req not in hdr_txt:
                errors.append(f"recomp_funcs.h missing required include: {req}")

    brace_checked = 0
    total_lines = 0
    for name in list(EXPECTED_GEN_HEADERS) + list(ALL_SHARD_FILES):
        p = out_dir / name
        if not p.is_file():
            continue
        txt = p.read_text(encoding="utf-8")
        total_lines += txt.count("\n")
        ok, depth = check_balanced_cpp_braces(txt)
        brace_checked += 1
        if not ok:
            errors.append(f"Unbalanced C++ braces in {name} (final depth={depth})")
        if name.endswith(".cpp") and '#include "recomp_funcs.h"' not in txt:
            errors.append(f"{name} missing #include \"recomp_funcs.h\"")

    return {
        "ok": len(errors) == 0,
        "errors": errors,
        "brace_checked_files": brace_checked,
        "total_cpp_lines": total_lines,
        "manifest": manifest,
    }


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="MBAA.exe static x86-32 -> C++20 AOT recompiler CLI.")
    parser.add_argument("--exe", type=Path, default=DEFAULT_MBAA_EXE, help="Path to unmodified MBAA.exe")
    parser.add_argument("--function-map", type=Path, default=DEFAULT_FUNCTION_MAP, help="Path to function_map.json")
    parser.add_argument("--rtti-vtables", type=Path, default=DEFAULT_RTTI_VTABLES, help="Path to rtti_vtables.json")
    parser.add_argument("--out", type=Path, default=DEFAULT_OUT_DIR, help="Output directory (default: build_gen/)")
    parser.add_argument("--no-comments", action="store_true", help="Omit per-instruction disassembly comments")
    parser.add_argument("--run-eval", action="store_true", help="Also execute IR vs Unicorn differential test suite")
    parser.add_argument("--verify-only", action="store_true", help="Verify existing build_gen/ files without regenerating")
    args = parser.parse_args(argv)

    if not args.verify_only:
        pcfg = recover_program_cfg(args.exe, args.function_map, args.rtti_vtables)
        summary = summarize_cfg(pcfg)
        print(f"CFG recovered: {json.dumps(summary)}")
        if pcfg.unresolved_count != 0 or pcfg.decode_error_count != 0:
            print(
                f"ERROR: CFG check failed (unresolved={pcfg.unresolved_count}, decode_errors={pcfg.decode_error_count})",
                file=sys.stderr,
            )
            return 1

        ir_funcs, unhandled = lift_program(pcfg)
        total_stmts = sum(len(b.stmts) for f in ir_funcs.values() for b in f.blocks.values())
        print(
            f"IR lifted: {len(ir_funcs)} functions, {pcfg.total_insns} insns -> {total_stmts} stmts, "
            f"unhandled={len(unhandled)}"
        )
        if unhandled:
            for fn_va, iv, desc in unhandled[:20]:
                print(f"  UNHANDLED fn=0x{fn_va:08x} insn=0x{iv:08x}: {desc}", file=sys.stderr)
            return 1

        pe = PEBinary(args.exe)
        res = emit_program(pcfg, ir_funcs, args.out, pe=pe, emit_comments=not args.no_comments)
        print(
            f"Emitted {len(res.files_written)} files to {res.out_dir} "
            f"(funcs={res.function_count}, iat={res.iat_count})"
        )

    v = verify_build_gen(args.out)
    print(
        f"Verification: ok={v['ok']}, brace_checked={v['brace_checked_files']}, "
        f"cpp_lines={v['total_cpp_lines']}"
    )
    if not v["ok"]:
        for err in v["errors"]:  # type: ignore[union-attr]
            print(f"  VERIFY ERROR: {err}", file=sys.stderr)
        return 1

    if args.run_eval:
        from .ir_eval import DifferentialSuite

        ev = DifferentialSuite(args.exe).run_all()
        print(f"Differential tests: {ev['passed']}/{ev['passed']} PASSED ({ev['failed']} failed)")
        if ev["failed"] != 0:
            return 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
