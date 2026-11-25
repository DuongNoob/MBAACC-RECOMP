"""Independent verification of static x86-32 -> C++20 lifter coverage and build_gen/ invariants."""

from __future__ import annotations

import json
import re
import struct
import sys
import unittest
from pathlib import Path

import capstone
import pefile

REPO_ROOT = Path(__file__).resolve().parents[1]
BUILD_GEN = REPO_ROOT / "build_gen"
RECOMPILER_DIR = REPO_ROOT / "recompiler"
MBAA_EXE = Path(r"c:\Users\A\Desktop\AI\google\MBAACC\MBAA.exe")
EVIDENCE_DIR = Path(r"c:\Users\A\Desktop\AI\google\mbaacc-src\evidence")
RTTI_JSON = EVIDENCE_DIR / "rtti_vtables.json"
FUNC_MAP_JSON = EVIDENCE_DIR / "function_map.json"
CRT_SIGS_JSON = RECOMPILER_DIR / "crt_signatures.json"

if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from recompiler.cfg import (  # noqa: E402
    EXTRA_DATA_CALLBACK_VAS,
    MBAA_CRT_START_VA,
    MBAA_CRT_XCA_CODE_START,
    MBAA_CRT_XCA_START,
    MBAA_CRT_XCZ_END,
    MBAA_GAME_TEXT_END,
)
from recompiler.cli import check_balanced_cpp_braces, verify_build_gen  # noqa: E402
from recompiler.cpp_emitter import ALL_SHARD_FILES, EXPECTED_GEN_HEADERS  # noqa: E402


class TestLifterCoverage(unittest.TestCase):
    """Verify 3,682 lifted functions, 0 gaps, CRT/IAT/RTTI coverage, and brace/symbol parity."""

    @classmethod
    def setUpClass(cls) -> None:
        cls.manifest = json.loads((BUILD_GEN / "gen_manifest.json").read_text(encoding="utf-8"))
        cls.crt_sigs = json.loads(CRT_SIGS_JSON.read_text(encoding="utf-8"))
        cls.rtti = json.loads(RTTI_JSON.read_text(encoding="utf-8"))
        cls.func_map = json.loads(FUNC_MAP_JSON.read_text(encoding="utf-8"))

        cls.recomp_funcs_text = (BUILD_GEN / "recomp_funcs.h").read_text(encoding="utf-8")
        cls.dispatch_text = (BUILD_GEN / "gen_dispatch.cpp").read_text(encoding="utf-8")
        cls.iat_table_text = (BUILD_GEN / "iat_table.h").read_text(encoding="utf-8")

        cls.shard_texts: dict[str, str] = {}
        for name in ALL_SHARD_FILES:
            if name != "gen_dispatch.cpp":
                cls.shard_texts[name] = (BUILD_GEN / name).read_text(encoding="utf-8")

        cls.pe = pefile.PE(str(MBAA_EXE), fast_load=False)
        cls.pe_raw = MBAA_EXE.read_bytes()
        cls.image_base = cls.pe.OPTIONAL_HEADER.ImageBase

    def _read_u32_va(self, va: int) -> int:
        off = self.pe.get_offset_from_rva(va - self.image_base)
        return struct.unpack_from("<I", self.pe_raw, off)[0]

    def test_verify_build_gen_and_zero_errors(self) -> None:
        res = verify_build_gen(BUILD_GEN)
        self.assertTrue(res["ok"], f"verify_build_gen failed: {res['errors']}")
        self.assertEqual(res["brace_checked_files"], 14)

        self.assertEqual(self.manifest["unhandled_instructions"], 0)
        self.assertEqual(self.manifest["unresolved_targets"], 0)
        self.assertEqual(self.manifest["decode_errors"], 0)

    def test_exact_function_counts_and_crt_xca_initializers(self) -> None:
        self.assertEqual(self.manifest["canonical_functions"], 3570)
        self.assertEqual(self.manifest["extra_data_callbacks"], 20)
        self.assertEqual(self.manifest["crt_xca_initializers"], 92)
        self.assertEqual(self.manifest["total_emitted_functions"], 3682)

        # Independently verify canonical VAs from function_map.json (< 0x004E00D0)
        canonical_vas = {
            int(fn["start_va"], 16)
            for fn in self.func_map["functions"]
            if int(fn["start_va"], 16) < MBAA_CRT_START_VA
        }
        self.assertEqual(len(canonical_vas), 3570)

        # Independently verify 20 extra .data callbacks not already in canonical_vas
        extra_vas = {va for va in EXTRA_DATA_CALLBACK_VAS if va not in canonical_vas}
        self.assertEqual(len(extra_vas), 20)

        # Independently read .CRT$XCA..XCZ pointer table directly from live MBAA.exe
        xca_vas: set[int] = set()
        for ptr_va in range(MBAA_CRT_XCA_START, MBAA_CRT_XCZ_END, 4):
            fn_va = self._read_u32_va(ptr_va)
            if fn_va != 0:
                self.assertGreaterEqual(fn_va, 0x00518D50)
                self.assertLessEqual(fn_va, 0x00519810)
                xca_vas.add(fn_va)
        self.assertEqual(len(xca_vas), 92)

        expected_all_vas = canonical_vas | extra_vas | xca_vas
        self.assertEqual(len(expected_all_vas), 3682)

        # Verify gen_dispatch.cpp registers the exact 3,682 VAs
        reg_matches = re.findall(
            r"register_function\((0x[0-9a-fA-F]+)u,\s*&(sub_[0-9a-fA-F]{8})\);",
            self.dispatch_text,
        )
        self.assertEqual(len(reg_matches), 3682)
        reg_vas = {int(va_s, 16) for va_s, _ in reg_matches}
        self.assertEqual(reg_vas, expected_all_vas)
        for va_s, sym in reg_matches:
            self.assertEqual(sym, f"sub_{int(va_s, 16):08x}")

        # Verify shard function counts sum to 3,682
        shard_sum = sum(self.manifest["shards"].values())
        self.assertEqual(shard_sum, 3682)

    def test_recomp_funcs_declaration_vs_definition_parity(self) -> None:
        decls = re.findall(
            r"^void\s+(sub_[0-9a-fA-F]{8})\(CpuContext&\s+ctx,\s+GuestMemory&\s+mem\);",
            self.recomp_funcs_text,
            flags=re.MULTILINE,
        )
        self.assertEqual(len(decls), 3682)
        decl_set = set(decls)
        self.assertEqual(len(decl_set), 3682)

        defs: list[str] = []
        for shard_name, txt in self.shard_texts.items():
            found = re.findall(
                r"^void\s+(sub_[0-9a-fA-F]{8})\(CpuContext&\s+ctx,\s+GuestMemory&\s+mem\)\s*\{",
                txt,
                flags=re.MULTILINE,
            )
            self.assertEqual(
                len(found),
                self.manifest["shards"][shard_name],
                f"Manifest shard count mismatch in {shard_name}",
            )
            defs.extend(found)

        self.assertEqual(len(defs), 3682)
        def_set = set(defs)
        self.assertEqual(len(def_set), 3682, "Duplicate sub_00XXXXXX definitions across shards")
        self.assertEqual(decl_set, def_set)

    def test_balanced_braces_across_all_build_gen_files(self) -> None:
        checked = 0
        for name in list(EXPECTED_GEN_HEADERS) + list(ALL_SHARD_FILES):
            path = BUILD_GEN / name
            self.assertTrue(path.is_file(), f"Missing {path}")
            ok, depth = check_balanced_cpp_braces(path.read_text(encoding="utf-8"))
            self.assertTrue(ok, f"Unbalanced braces in {name} (final depth={depth})")
            checked += 1
        self.assertEqual(checked, 14)

    def test_crt_signatures_76_vas_match_live_exe_and_generated_calls(self) -> None:
        self.assertEqual(self.crt_sigs["count"], 76)
        sigs = self.crt_sigs["functions"]
        self.assertEqual(len(sigs), 76)

        crt_vas = {int(f["va"], 16) for f in sigs}
        self.assertEqual(len(crt_vas), 76)
        self.assertEqual(self.manifest["used_crt_vas"], 76)

        for entry in sigs:
            va = int(entry["va"], 16)
            self.assertEqual(entry["c_symbol"], f"hle_crt_{va:08x}")
            self.assertGreaterEqual(va, MBAA_CRT_START_VA)
            self.assertLess(va, MBAA_CRT_XCA_CODE_START)
            # Check sample call sites in live MBAA.exe actually target this CRT VA
            for cs_hex in entry.get("sample_call_sites", [])[:2]:
                cs_va = int(cs_hex, 16)
                off = self.pe.get_offset_from_rva(cs_va - self.image_base)
                insn_bytes = self.pe_raw[off : off + 6]
                self.assertIn(insn_bytes[0], (0xE8, 0xE9), f"Call site 0x{cs_va:08x} is not E8/E9")
                rel = struct.unpack_from("<i", insn_bytes, 1)[0]
                self.assertEqual((cs_va + 5 + rel) & 0xFFFFFFFF, va)

        # Verify every hle_crt_00XXXXXX emitted in build_gen/*.cpp is in the 76 CRT signatures
        emitted_crt: set[str] = set()
        for txt in self.shard_texts.values():
            emitted_crt.update(re.findall(r"\bhle_crt_[0-9a-fA-F]{8}\b", txt))
        expected_crt_syms = {f["c_symbol"] for f in sigs}
        self.assertEqual(emitted_crt, expected_crt_syms)

    def test_iat_table_184_vas_match_pe_iat_and_text_sites(self) -> None:
        iat_rows = re.findall(
            r'\{\s*(0x[0-9a-fA-F]+)u,\s*"([^"]+)",\s*"([^"]+)",\s*"([^"]+)",\s*(true|false)\s*\}',
            self.iat_table_text,
        )
        self.assertEqual(len(iat_rows), 184)
        self.assertEqual(self.manifest["game_iat_table_count"], 184)
        self.assertIn("kGameIatCount = 184u;", self.iat_table_text)

        # Build ground-truth PE IAT from live MBAA.exe
        pe_iat: dict[int, tuple[str, str]] = {}
        for imp_dir in self.pe.DIRECTORY_ENTRY_IMPORT:
            dll = imp_dir.dll.decode("latin1", errors="replace")
            for imp in imp_dir.imports:
                name = imp.name.decode("latin1", errors="replace") if imp.name else f"ord_{imp.ordinal}"
                pe_iat[imp.address] = (dll, name)

        # Scan game .text (0x00401000..0x004DF020) for 32-bit references to PE IAT VAs
        text_sec = next(s for s in self.pe.sections if s.Name.rstrip(b"\x00") == b".text")
        text_va = self.image_base + text_sec.VirtualAddress
        text_bytes = self.pe_raw[text_sec.PointerToRawData : text_sec.PointerToRawData + (MBAA_GAME_TEXT_END - text_va)]
        text_iat_refs: set[int] = set()
        for off in range(0, len(text_bytes) - 3):
            val = struct.unpack_from("<I", text_bytes, off)[0]
            if val in pe_iat:
                text_iat_refs.add(val)

        # Also verify emitted hle_iat_call(..., 0x...u) VAs in build_gen
        emitted_iat_vas: set[int] = set()
        for txt in self.shard_texts.values():
            for m in re.findall(r"hle_iat_call\(ctx,\s*mem,\s*(0x[0-9a-fA-F]+)u\)", txt):
                emitted_iat_vas.add(int(m, 16))

        table_vas: set[int] = set()
        reachable_count = 0
        for va_s, dll, name, qname, reach_s in iat_rows:
            va = int(va_s, 16)
            self.assertIn(va, pe_iat, f"IAT VA 0x{va:08x} not in MBAA.exe PE IAT")
            self.assertEqual((dll, name), pe_iat[va])
            self.assertEqual(qname, f"{dll}!{name}")
            self.assertIn(va, text_iat_refs, f"IAT VA 0x{va:08x} ({qname}) missing in game .text")
            table_vas.add(va)
            if reach_s == "true":
                reachable_count += 1

        self.assertEqual(len(table_vas), 184)
        self.assertEqual(reachable_count, 180)
        self.assertTrue(emitted_iat_vas.issubset(table_vas))

    def test_rtti_190_vtables_and_methods_registered(self) -> None:
        vtables = self.rtti["vtables"]
        self.assertEqual(len(vtables), 190)

        reg_vas = {
            int(m, 16)
            for m in re.findall(r"register_function\((0x[0-9a-fA-F]+)u,", self.dispatch_text)
        }

        all_unique_slots: set[int] = set()
        game_slots: set[int] = set()
        crt_slots: set[int] = set()
        for vt in vtables:
            for meth in vt["methods"]:
                va = int(meth["va"], 16)
                all_unique_slots.add(va)
                if va < MBAA_CRT_START_VA:
                    game_slots.add(va)
                else:
                    crt_slots.add(va)

        self.assertEqual(len(all_unique_slots), 562)
        self.assertEqual(len(game_slots), 557)
        self.assertEqual(self.manifest["vtable_slots_covered"], 557)

        missing_game = game_slots - reg_vas
        self.assertEqual(missing_game, set(), f"Unregistered RTTI game methods: {sorted(hex(v) for v in missing_game)}")

        # Remaining 5 slots >= 0x004E00D0 must be MSVC runtime (_purecall / std::exception / type_info)
        self.assertEqual(
            crt_slots,
            {0x004E08A9, 0x004E08B6, 0x004E08E0, 0x004E1BAC, 0x004EBBD1},
        )
        # Verify every one of the 190 vtables is accounted for (187 have >=1 registered game slot;
        # the remaining 3 are pure CRT runtime vtables std::exception, type_info, std::bad_exception).
        vtables_without_game_slots = [
            vt["class_name"]
            for vt in vtables
            if not any(int(m["va"], 16) in reg_vas for m in vt["methods"])
        ]
        self.assertEqual(
            sorted(vtables_without_game_slots),
            ["std::bad_exception", "std::exception", "type_info"],
        )

    def test_capstone_spot_check_on_core_and_callback_entries(self) -> None:
        md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        for va in (0x0040D240, 0x0040E390, 0x004DB470, 0x00417270, 0x004020A0, 0x00518D50):
            off = self.pe.get_offset_from_rva(va - self.image_base)
            insns = list(md.disasm(self.pe_raw[off : off + 16], va))
            self.assertGreater(len(insns), 0, f"Capstone decode failed at 0x{va:08x}")
            self.assertIn(f"sub_{va:08x}", self.recomp_funcs_text)


if __name__ == "__main__":
    unittest.main()
