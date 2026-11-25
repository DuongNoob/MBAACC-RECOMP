"""Independent cross-file C++/ObjC++/iOS parity, rollback, and BYOC compliance audit."""

from __future__ import annotations

import json
import plistlib
import re
import sys
import unittest
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
BUILD_GEN = REPO_ROOT / "build_gen"
RECOMPILER_DIR = REPO_ROOT / "recompiler"
RUNTIME_INC = REPO_ROOT / "runtime" / "include" / "mbaa_recomp"
RUNTIME_SRC = REPO_ROOT / "runtime" / "src"
IOS_DIR = REPO_ROOT / "ios"
IOS_APP = IOS_DIR / "App"
IOS_SHADERS = IOS_DIR / "Shaders"
COMPANION_JSON = Path(r"c:\Users\A\Desktop\AI\google\mbaacc-src\evidence\companion_binaries.json")

if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from recompiler.cli import check_balanced_cpp_braces  # noqa: E402


class TestRuntimeAndIosAudit(unittest.TestCase):
    """Verify runtime/HLE/iOS/CMake/XcodeGen parity, rollback tables, and BYOC compliance."""

    @classmethod
    def setUpClass(cls) -> None:
        cls.crt_sigs = json.loads((RECOMPILER_DIR / "crt_signatures.json").read_text(encoding="utf-8"))
        cls.companion = json.loads(COMPANION_JSON.read_text(encoding="utf-8"))
        cls.hle_crt_h = (RUNTIME_INC / "hle_crt.h").read_text(encoding="utf-8")
        cls.hle_crt_cpp = (RUNTIME_SRC / "hle_crt.cpp").read_text(encoding="utf-8")
        cls.hle_win32_cpp = (RUNTIME_SRC / "hle_win32.cpp").read_text(encoding="utf-8")
        cls.d3d9_shim_h = (RUNTIME_INC / "d3d9_shim.h").read_text(encoding="utf-8")
        cls.d3d9_metal_mm = (RUNTIME_SRC / "hle_d3d9_metal.mm").read_text(encoding="utf-8")
        cls.audio_mm = (RUNTIME_SRC / "hle_audio_ios.mm").read_text(encoding="utf-8")
        cls.input_mm = (RUNTIME_SRC / "hle_input_ios.mm").read_text(encoding="utf-8")
        cls.iat_table_h = (BUILD_GEN / "iat_table.h").read_text(encoding="utf-8")
        cls.cmake_txt = (REPO_ROOT / "CMakeLists.txt").read_text(encoding="utf-8")
        cls.project_yml = (IOS_DIR / "project.yml").read_text(encoding="utf-8")
        cls.runtime_engine_h = (RUNTIME_INC / "runtime_engine.h").read_text(encoding="utf-8")
        cls.hle_input_h = (RUNTIME_INC / "hle_input.h").read_text(encoding="utf-8")
        cls.gvc_mm = (IOS_APP / "GameViewController.mm").read_text(encoding="utf-8")
        cls.touch_h = (IOS_APP / "TouchOverlayView.h").read_text(encoding="utf-8")
        cls.touch_mm = (IOS_APP / "TouchOverlayView.mm").read_text(encoding="utf-8")
        cls.rollback_h = (RUNTIME_INC / "rollback_hooks.h").read_text(encoding="utf-8")
        cls.rollback_cpp = (RUNTIME_SRC / "rollback_hooks.cpp").read_text(encoding="utf-8")
        cls.gitignore = (REPO_ROOT / ".gitignore").read_text(encoding="utf-8")

    def test_every_crt_call_in_build_gen_is_declared_and_implemented(self) -> None:
        referenced: set[str] = set()
        for cpp in sorted(BUILD_GEN.glob("gen_*.cpp")):
            referenced.update(re.findall(r"\bhle_crt_[0-9a-fA-F]{8}\b", cpp.read_text(encoding="utf-8")))

        expected_76 = {f["c_symbol"] for f in self.crt_sigs["functions"]}
        self.assertEqual(len(expected_76), 76)
        self.assertEqual(referenced, expected_76)

        decls = set(
            re.findall(
                r"^void\s+(hle_crt_[0-9a-fA-F]{8})\(\s*CpuContext&\s+\w+,\s*GuestMemory&\s+\w+\s*\)\s*;",
                self.hle_crt_h,
                flags=re.MULTILINE,
            )
        )
        defs = set(
            re.findall(
                r"^void\s+(hle_crt_[0-9a-fA-F]{8})\(\s*CpuContext&\s+\w+,\s*GuestMemory&\s+\w+\s*\)\s*\{",
                self.hle_crt_cpp,
                flags=re.MULTILINE,
            )
        )
        dispatched = set(
            re.findall(
                r"case\s+0x([0-9a-fA-F]+)u:\s*(hle_crt_[0-9a-fA-F]{8})\(ctx,\s*mem\);",
                self.hle_crt_cpp,
            )
        )

        self.assertEqual(decls, expected_76)
        self.assertEqual(defs, expected_76)
        self.assertEqual({sym for _, sym in dispatched}, expected_76)
        for va_hex, sym in dispatched:
            self.assertEqual(sym, f"hle_crt_{int(va_hex, 16):08x}")

    def test_all_184_iat_vas_dispatched_across_hle_modules(self) -> None:
        iat_rows = re.findall(
            r'\{\s*(0x[0-9a-fA-F]+)u,\s*"([^"]+)",\s*"([^"]+)",\s*"([^"]+)",\s*(?:true|false)\s*\}',
            self.iat_table_h,
        )
        self.assertEqual(len(iat_rows), 184)

        m_tbl = re.search(
            r"constexpr\s+IatDescriptor\s+kIatTable\[\]\s*=\s*\{(.*?)\};",
            self.hle_win32_cpp,
            flags=re.DOTALL,
        )
        self.assertIsNotNone(m_tbl, "kIatTable[] not found in hle_win32.cpp")
        win32_by_va = {
            int(va_s, 16): (qname, handler.strip())
            for va_s, qname, handler in re.findall(
                r'^\s*\{\s*(0x[0-9a-fA-F]+)u,\s*"([^"]+)",\s*(.+?)\},\s*$',
                m_tbl.group(1),
                flags=re.MULTILINE,
            )
        }
        self.assertEqual(len(win32_by_va), 247)

        d3d_cases = set(re.findall(r"case\s+d3d_iat::(k\w+):", self.d3d9_metal_mm))
        d3d_vas = {
            name: int(va_hex, 16)
            for name, va_hex in re.findall(
                r"inline constexpr uint32_t (k\w+)\s*=\s*(0x[0-9a-fA-F]+)u;",
                self.d3d9_shim_h,
            )
        }
        d3d_va_set = {va for name, va in d3d_vas.items() if name in d3d_cases}
        self.assertEqual(len(d3d_va_set), 23)

        self.assertIn("void hle_direct_input8_create(CpuContext& ctx, GuestMemory& mem)", self.input_mm)
        self.assertIn("void hle_direct_sound_create8(CpuContext& ctx, GuestMemory& mem)", self.audio_mm)

        for va_s, dll, _name, qname in iat_rows:
            va = int(va_s, 16)
            self.assertIn(va, win32_by_va, f"IAT VA 0x{va:08x} ({qname}) missing from hle_win32.cpp kIatTable")
            mapped_qname, handler = win32_by_va[va]
            self.assertEqual(mapped_qname, qname)
            if dll in ("d3d9.dll", "d3dx9_36.dll"):
                self.assertIn("d3d_iat_forward", handler)
                self.assertIn(va, d3d_va_set, f"D3D9 VA 0x{va:08x} ({qname}) missing in hle_d3d9_metal.mm")
            elif dll == "DINPUT8.dll":
                self.assertIn("hle_direct_input8_create", handler)
            elif dll == "DSOUND.dll":
                self.assertIn("hle_direct_sound_create8", handler)

        # Also verify DSOUND.dll!DirectSoundCreate8 (0x0051B008) is wired in kIatTable
        self.assertIn(0x0051B008, win32_by_va)
        self.assertIn("hle_direct_sound_create8", win32_by_va[0x0051B008][1])

    def test_cmake_and_xcodegen_sources_exist_on_disk(self) -> None:
        # CMakeLists.txt explicit source lists
        cmake_sources = re.findall(
            r"\b((?:runtime/src|build_gen|ios/App|ios/Shaders)/[^\s\)\"]+\.(?:cpp|mm|metal))",
            self.cmake_txt,
        )
        self.assertGreaterEqual(len(cmake_sources), 28)
        for rel in cmake_sources:
            self.assertTrue((REPO_ROOT / rel).is_file(), f"CMakeLists.txt source missing on disk: {rel}")

        self.assertIn("ios/App/Info.plist", self.cmake_txt)
        self.assertIn("ios/App/MBAACCRecomp.entitlements", self.cmake_txt)
        self.assertTrue((IOS_APP / "Info.plist").is_file())
        self.assertTrue((IOS_APP / "MBAACCRecomp.entitlements").is_file())

        # ios/project.yml referenced files and directories
        yml_paths = re.findall(r"(?:path|INFOPLIST_FILE|CODE_SIGN_ENTITLEMENTS):\s*([^\s#]+)", self.project_yml)
        self.assertGreater(len(yml_paths), 0)
        for rel in yml_paths:
            target = (IOS_DIR / rel).resolve()
            self.assertTrue(target.exists(), f"ios/project.yml path missing on disk: {rel} -> {target}")

    def test_ios_view_controller_and_touch_overlay_match_engine_and_buttons(self) -> None:
        # Check RuntimeEngine public methods referenced by GameViewController.mm exist in runtime_engine.h
        required_engine_methods = [
            "bool init(const std::string& assets_dir, void* metal_layer, int width, int height);",
            "void step_frame();",
            "void set_touch_state(const TouchInputState& state);",
            "void handle_memory_warning();",
            "void shutdown();",
            "const std::string& last_error() const noexcept;",
        ]
        for sig in required_engine_methods:
            self.assertIn(sig, self.runtime_engine_h)

        for call in ("->init(", "->step_frame()", "->set_touch_state(", "->handle_memory_warning()", "->shutdown()", "->last_error()"):
            self.assertIn(call, self.gvc_mm, f"GameViewController.mm missing RuntimeEngine call {call}")

        # Verify all 16 TouchButton bit shifts in hle_input.h match TouchOverlayView.h and GameViewController.mm static_asserts
        cpp_bits = {
            name: int(shift)
            for name, shift in re.findall(r"(kTouch\w+)\s*=\s*1u\s*<<\s*(\d+)", self.hle_input_h)
        }
        objc_bits = {
            name: int(shift)
            for name, shift in re.findall(r"(MBAAVirtualButton\w+)\s*=\s*1u\s*<<\s*(\d+)", self.touch_h)
        }
        self.assertEqual(len(cpp_bits), 16)
        self.assertEqual(len(objc_bits), 16)

        for suffix in ("Up", "Down", "Left", "Right", "A", "B", "C", "D", "E", "Start", "Coin", "FN1", "FN2", "Pause", "Dash", "Heat"):
            cpp_k = f"kTouch{suffix}"
            objc_k = f"MBAAVirtualButton{suffix}"
            self.assertIn(cpp_k, cpp_bits)
            self.assertIn(objc_k, objc_bits)
            self.assertEqual(cpp_bits[cpp_k], objc_bits[objc_k], f"Bit shift mismatch for {suffix}")
            self.assertIn(
                f"static_assert({objc_k} == mbaa_recomp::{cpp_k}",
                re.sub(r"\s+", " ", self.gvc_mm),
            )

        # Verify macro expansion in TouchOverlayView.mm matches A+B / A+B+C
        self.assertIn("MBAAVirtualButtonDash | MBAAVirtualButtonA | MBAAVirtualButtonB", self.touch_mm)
        self.assertIn("MBAAVirtualButtonHeat | MBAAVirtualButtonA | MBAAVirtualButtonB | MBAAVirtualButtonC", self.touch_mm)

    def test_24_rollback_regions_match_companion_binaries_json_bit_for_bit(self) -> None:
        expected_ranges = self.companion["hook_dll"]["rollback_state_ranges"]
        self.assertEqual(len(expected_ranges), 24)
        self.assertEqual(sum(r["byte_size"] for r in expected_ranges), 252)

        cpp_regions = re.findall(
            r"\{\s*(0x[0-9a-fA-F]+)u,\s*(\d+)u,\s*(\d+)u\s*\}",
            self.rollback_cpp,
        )
        self.assertEqual(len(cpp_regions), 24)

        running_off = 0
        for exp, (va_s, sz_s, off_s) in zip(expected_ranges, cpp_regions):
            exp_va = int(exp["mbaa_data_va"], 16)
            exp_sz = int(exp["byte_size"])
            got_va = int(va_s, 16)
            got_sz = int(sz_s)
            got_off = int(off_s)
            self.assertEqual(got_va, exp_va, f"Rollback VA mismatch: 0x{got_va:08x} != 0x{exp_va:08x}")
            self.assertEqual(got_sz, exp_sz, f"Rollback size mismatch at 0x{got_va:08x}")
            self.assertEqual(got_off, running_off, f"Rollback snapshot offset mismatch at 0x{got_va:08x}")
            running_off += got_sz

        self.assertEqual(running_off, 252)
        self.assertIn("kRegionCount    = 24;", self.rollback_h)
        self.assertIn("kTotalStateBytes = 252;", self.rollback_h)
        self.assertIn("kBattleTickVa = 0x007717D8u;", self.rollback_h)

    def test_byoc_and_zero_drm_bypass_compliance(self) -> None:
        # 1. LoadLibraryA must return 0 / NULL for unshimmed external DLLs (e.g., reg.dll)
        m_load = re.search(
            r"void\s+k32_load_library_a\s*\([^)]*\)\s*\{(?P<body>.*?)\n\}",
            self.hle_win32_cpp,
            flags=re.DOTALL,
        )
        self.assertIsNotNone(m_load)
        body = m_load.group("body")
        self.assertNotIn("reg.dll", re.sub(r"//.*", "", body).lower())
        self.assertNotIn("sarcheck", body.lower())
        self.assertNotIn("0000.dat", body.lower())
        self.assertIn("ctx.eax = 0u;", body)

        # Ensure zero sarcheck / 0000.dat spoofing anywhere in runtime/ or ios/
        for folder in (REPO_ROOT / "runtime", IOS_DIR):
            for f in folder.rglob("*"):
                if f.is_file() and f.suffix in (".h", ".cpp", ".mm", ".metal"):
                    txt_l = f.read_text(encoding="utf-8", errors="replace").lower()
                    self.assertNotIn("sarcheck", txt_l, f"Forbidden DRM symbol reference in {f}")
                    self.assertNotIn("0000.dat", txt_l, f"Forbidden 0000.dat reference in {f}")

        # 2. .gitignore must exclude build_gen/, *.exe, *.p, *.dat, *.cfx, and extracted assets
        gi_entries = {
            line.strip()
            for line in self.gitignore.splitlines()
            if line.strip() and not line.strip().startswith("#")
        }
        for req in (
            "build_gen/",
            "*.exe",
            "*.dll",
            "*.p",
            "*.dat",
            "*.cfx",
            "*.ha6",
            "*.cg",
            "*.pal",
            "*.pat",
            "*.dds",
            "*.ogg",
            "*.wav",
        ):
            self.assertIn(req, gi_entries, f".gitignore missing required exclusion '{req}'")

        # 3. ZERO copyrighted game files inside mbaacc-recomp-ios/
        forbidden_exts = {".exe", ".p", ".cfx", ".ha6", ".cg", ".pal", ".dds", ".ogg", ".wav"}
        forbidden_names = {"0000.dat", "reg.dll"}
        found_assets: list[str] = []
        for f in REPO_ROOT.rglob("*"):
            if f.is_file():
                if f.suffix.lower() in forbidden_exts or f.name.lower() in forbidden_names:
                    found_assets.append(str(f))
        self.assertEqual(found_assets, [], f"Copyrighted game files found in repo: {found_assets}")

    def test_info_plist_and_no_jit_entitlements(self) -> None:
        info = plistlib.loads((IOS_APP / "Info.plist").read_bytes())
        self.assertIs(info.get("UIFileSharingEnabled"), True)
        self.assertIs(info.get("LSSupportsOpeningDocumentsInPlace"), True)
        self.assertEqual(
            set(info.get("UISupportedInterfaceOrientations", [])),
            {"UIInterfaceOrientationLandscapeLeft", "UIInterfaceOrientationLandscapeRight"},
        )
        self.assertEqual(
            set(info.get("UISupportedInterfaceOrientations~ipad", [])),
            {"UIInterfaceOrientationLandscapeLeft", "UIInterfaceOrientationLandscapeRight"},
        )
        caps = set(info.get("UIRequiredDeviceCapabilities", []))
        self.assertTrue({"arm64", "metal"}.issubset(caps))

        entitlements = plistlib.loads((IOS_APP / "MBAACCRecomp.entitlements").read_bytes())
        self.assertIsInstance(entitlements, dict)
        for key in entitlements:
            kl = key.lower()
            self.assertNotIn("jit", kl)
            self.assertNotIn("dynamic-codesigning", kl)
            self.assertNotIn("unsigned-executable-memory", kl)

    def test_runtime_and_ios_balanced_braces_and_valid_includes(self) -> None:
        include_roots = [
            REPO_ROOT / "runtime" / "include",
            BUILD_GEN,
            IOS_SHADERS,
            IOS_APP,
        ]
        checked = 0
        for folder in (REPO_ROOT / "runtime", IOS_APP, IOS_SHADERS):
            for f in sorted(folder.rglob("*")):
                if not f.is_file() or f.suffix not in (".h", ".hpp", ".cpp", ".mm", ".m", ".metal"):
                    continue
                txt = f.read_text(encoding="utf-8")
                ok, depth = check_balanced_cpp_braces(txt)
                self.assertTrue(ok, f"Unbalanced braces in {f.relative_to(REPO_ROOT)} (depth={depth})")
                checked += 1

                for lineno, line in enumerate(txt.splitlines(), 1):
                    m = re.match(r'^\s*#(?:include|import)\s+"([^"]+)"', line)
                    if m:
                        inc = m.group(1)
                        exists = (f.parent / inc).is_file() or any((r / inc).is_file() for r in include_roots)
                        self.assertTrue(
                            exists,
                            f"Broken local include '{inc}' at {f.relative_to(REPO_ROOT)}:{lineno}",
                        )
        self.assertGreaterEqual(checked, 29)


if __name__ == "__main__":
    unittest.main()
