"""Independent verification of DX9 .cfx -> Metal 2.4 shaders, D3D9MetalBridge, live DDS headers, and DXT1-5 decoder."""

from __future__ import annotations

import json
import re
import struct
import sys
import unittest
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
MBAACC_DIR = Path(r"c:\Users\A\Desktop\AI\google\MBAACC")
MBAACC_SRC_PY = Path(r"c:\Users\A\Desktop\AI\google\mbaacc-src\py")
SHADERS_DIR = REPO_ROOT / "ios" / "Shaders"
D3D9_SHIM_H = REPO_ROOT / "runtime" / "include" / "mbaa_recomp" / "d3d9_shim.h"
D3D9_METAL_MM = REPO_ROOT / "runtime" / "src" / "hle_d3d9_metal.mm"
BCDEC_CPP = REPO_ROOT / "runtime" / "src" / "bcdec_dxt.cpp"

if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))
if str(MBAACC_SRC_PY) not in sys.path:
    sys.path.insert(0, str(MBAACC_SRC_PY))

from mbaacc.filepac import MOUNT_ORDER, FilePacArchive  # noqa: E402
from recompiler.cfx_disasm import analyze_p0006  # noqa: E402
from recompiler.cli import check_balanced_cpp_braces  # noqa: E402


# ---------------------------------------------------------------------------
# Pure-Python Reference Block Decoders Matching DX9 / BC1-BC3 Spec
# ---------------------------------------------------------------------------
def _ref_rgb565_to_rgb8(c: int) -> tuple[int, int, int]:
    r5 = (c >> 11) & 0x1F
    g6 = (c >> 5) & 0x3F
    b5 = c & 0x1F
    return ((r5 << 3) | (r5 >> 2), (g6 << 2) | (g6 >> 4), (b5 << 3) | (b5 >> 2))


def _ref_unpremul(c: int, a: int) -> int:
    if a == 0:
        return 0
    if a == 255:
        return c
    return min(255, (c * 255 + (a >> 1)) // a)


def _ref_color_palette(blk: bytes, allow_3color: bool) -> tuple[list[tuple[int, int, int, int]], int]:
    c0, c1, idx = struct.unpack_from("<HHI", blk, 0)
    r0, g0, b0 = _ref_rgb565_to_rgb8(c0)
    r1, g1, b1 = _ref_rgb565_to_rgb8(c1)
    pal = [(r0, g0, b0, 255), (r1, g1, b1, 255)]
    if allow_3color and c0 <= c1:
        pal.append(((r0 + r1) >> 1, (g0 + g1) >> 1, (b0 + b1) >> 1, 255))
        pal.append((0, 0, 0, 0))
    else:
        pal.append(((2 * r0 + r1 + 1) // 3, (2 * g0 + g1 + 1) // 3, (2 * b0 + b1 + 1) // 3, 255))
        pal.append(((r0 + 2 * r1 + 1) // 3, (g0 + 2 * g1 + 1) // 3, (b0 + 2 * b1 + 1) // 3, 255))
    return pal, idx


def ref_decode_dxt1_block(blk: bytes) -> list[tuple[int, int, int, int]]:
    pal, idx = _ref_color_palette(blk, allow_3color=True)
    return [pal[(idx >> (2 * i)) & 3] for i in range(16)]


def ref_decode_dxt23_block(blk: bytes, unpremul: bool) -> list[tuple[int, int, int, int]]:
    alpha_bits = int.from_bytes(blk[:8], "little")
    pal, idx = _ref_color_palette(blk[8:16], allow_3color=False)
    out = []
    for i in range(16):
        a4 = (alpha_bits >> (4 * i)) & 0xF
        a8 = (a4 << 4) | a4
        r, g, b, _ = pal[(idx >> (2 * i)) & 3]
        if unpremul:
            r, g, b = _ref_unpremul(r, a8), _ref_unpremul(g, a8), _ref_unpremul(b, a8)
        out.append((r, g, b, a8))
    return out


def ref_decode_dxt45_block(blk: bytes, unpremul: bool) -> list[tuple[int, int, int, int]]:
    a0, a1 = blk[0], blk[1]
    aidx = int.from_bytes(blk[2:8], "little")
    apal = [a0, a1] + [0] * 6
    if a0 > a1:
        for k in range(1, 7):
            apal[k + 1] = ((7 - k) * a0 + k * a1 + 3) // 7
    else:
        for k in range(1, 5):
            apal[k + 1] = ((5 - k) * a0 + k * a1 + 2) // 5
        apal[6] = 0
        apal[7] = 255
    pal, idx = _ref_color_palette(blk[8:16], allow_3color=False)
    out = []
    for i in range(16):
        a8 = apal[(aidx >> (3 * i)) & 7]
        r, g, b, _ = pal[(idx >> (2 * i)) & 3]
        if unpremul:
            r, g, b = _ref_unpremul(r, a8), _ref_unpremul(g, a8), _ref_unpremul(b, a8)
        out.append((r, g, b, a8))
    return out


class TestShadersAndDxt(unittest.TestCase):
    """Cross-verify .cfx disassembly, Metal shaders, D3D9MetalBridge, and DDS/DXT1-5 decoder."""

    @classmethod
    def setUpClass(cls) -> None:
        cls.cfx_disk = json.loads((SHADERS_DIR / "cfx_analysis.json").read_text(encoding="utf-8"))
        cls.cfx_live = analyze_p0006(MBAACC_DIR / "0006.p")
        cls.manifest_h = (SHADERS_DIR / "shader_manifest.h").read_text(encoding="utf-8")
        cls.metal_src = (SHADERS_DIR / "mbaa_shaders.metal").read_text(encoding="utf-8")
        cls.d3d9_shim_h = D3D9_SHIM_H.read_text(encoding="utf-8")
        cls.d3d9_metal_mm = D3D9_METAL_MM.read_text(encoding="utf-8")
        cls.bcdec_cpp = BCDEC_CPP.read_text(encoding="utf-8")

    def test_cfx_disasm_matches_cfx_analysis_json(self) -> None:
        self.assertEqual(self.cfx_live["summary"], {
            "cfx_count": 9,
            "technique_count": 22,
            "pass_count": 28,
            "shader_blob_count": 29,
        })
        self.assertEqual(self.cfx_live, self.cfx_disk)

        expected_files = {
            "sh_bloom_sakura.cfx",
            "sh_blur.cfx",
            "sh_chara.cfx",
            "sh_fade.cfx",
            "sh_gaugedraw.cfx",
            "sh_mono.cfx",
            "sh_noise.cfx",
            "sh_normal.cfx",
            "vsfx.cfx",
        }
        self.assertEqual({e["file"] for e in self.cfx_live["effects"]}, expected_files)

    def test_every_cfx_technique_pass_and_uniform_mapped_in_manifest_and_metal(self) -> None:
        # 1. Check shader_manifest.h kTechniquePasses table covers every .cfx technique & pass
        pass_rows = re.findall(
            r'\{\s*(nullptr|"[^"]+")\s*,\s*(nullptr|"[^"]+")\s*,\s*(\d+)\s*,\s*(MBAA_PASS_\w+)\s*,\s*"([^"]+)"\s*,\s*"([^"]+)"\s*,\s*(\d+)\s*\}',
            self.manifest_h,
        )
        self.assertEqual(len(pass_rows), 30)  # 2 fixed/present + 28 .cfx passes

        mapped_passes: dict[tuple[str, str, int], tuple[str, str, str]] = {}
        fixed_passes: dict[str, tuple[str, str]] = {}
        for eff_raw, tech_raw, pidx_s, pass_id, vs_fn, ps_fn, _mrt in pass_rows:
            if eff_raw == "nullptr":
                fixed_passes[pass_id] = (vs_fn, ps_fn)
            else:
                eff = eff_raw.strip('"')
                tech = tech_raw.strip('"')
                mapped_passes[(eff, tech, int(pidx_s))] = (pass_id, vs_fn, ps_fn)

        self.assertIn("MBAA_PASS_FIXED_2D", fixed_passes)
        self.assertIn("MBAA_PASS_PRESENT_BLIT", fixed_passes)
        self.assertEqual(len(mapped_passes), 28)

        # Verify 1:1 parity with all 22 techniques / 28 passes in cfx_analysis.json
        cfx_keys: set[tuple[str, str, int]] = set()
        for eff in self.cfx_disk["effects"]:
            for tech in eff["techniques"]:
                for pidx in range(len(tech["passes"])):
                    key = (eff["file"], tech["name"], pidx)
                    cfx_keys.add(key)
                    self.assertIn(key, mapped_passes, f"Missing technique/pass in shader_manifest.h: {key}")
        self.assertEqual(set(mapped_passes.keys()), cfx_keys)

        # 2. Verify every Metal entry point referenced in shader_manifest.h exists in mbaa_shaders.metal
        metal_entries = set(
            re.findall(r"\b(?:vertex|fragment)\s+\S+\s+(\w+)\s*\(", self.metal_src)
        )
        for _eff, _tech, _pidx, _pid, vs_fn, ps_fn, _mrt in re.findall(
            r'\{\s*(nullptr|"[^"]+")\s*,\s*(nullptr|"[^"]+")\s*,\s*(\d+)\s*,\s*(MBAA_PASS_\w+)\s*,\s*"([^"]+)"\s*,\s*"([^"]+)"\s*,\s*(\d+)\s*\}',
            self.manifest_h,
        ):
            self.assertIn(vs_fn, metal_entries, f"Missing Metal vertex shader {vs_fn}")
            self.assertIn(ps_fn, metal_entries, f"Missing Metal fragment shader {ps_fn}")
        self.assertEqual(len(metal_entries), 31)

        # 3. Verify every CTAB uniform from all 9 .cfx shaders is handled in MbaaEffectUniforms / hle_d3d9_metal.mm
        ctab_non_sampler_uniforms: set[str] = set()
        for eff in self.cfx_disk["effects"]:
            for sh in eff["shaders"]:
                for c in sh.get("ctab", {}).get("constants", []):
                    if c.get("register_set") != "sampler":
                        ctab_non_sampler_uniforms.add(c["name"])
        for param_name in sorted(ctab_non_sampler_uniforms):
            self.assertIn(
                f'"{param_name}"',
                self.d3d9_metal_mm,
                f"CTAB uniform '{param_name}' not handled in hle_d3d9_metal.mm",
            )

        # 4. Verify Metal syntax balance
        ok_m, depth_m = check_balanced_cpp_braces(self.metal_src)
        self.assertTrue(ok_m, f"Unbalanced braces in mbaa_shaders.metal (depth={depth_m})")
        self.assertEqual(self.metal_src.count("("), self.metal_src.count(")"))
        self.assertIn('#include "shader_manifest.h"', self.metal_src)

    def test_d3d9_metal_bridge_covers_23_iat_vtables_lru_present_viewport(self) -> None:
        self.assertTrue(D3D9_METAL_MM.is_file())

        # All 23 d3d_iat::k* constants in d3d9_shim.h (0x0051B398..0x0051B3F4)
        iat_consts = re.findall(
            r"inline constexpr uint32_t (k\w+)\s*=\s*(0x[0-9a-fA-F]+)u;",
            self.d3d9_shim_h,
        )
        self.assertEqual(len(iat_consts), 23)
        for name, va_hex in iat_consts:
            va = int(va_hex, 16)
            self.assertTrue(va == 0x0051B398 or (0x0051B3A0 <= va <= 0x0051B3F4))
            self.assertIn(
                f"case d3d_iat::{name}:",
                self.d3d9_metal_mm,
                f"d3d_iat::{name} missing switch handler in hle_d3d9_metal.mm",
            )

        # Synthetic COM vtables for all 6 D3D9/D3DX9 interfaces
        for vtbl_sym in (
            "vtbl_d3d9",
            "vtbl_device",
            "vtbl_texture",
            "vtbl_surface",
            "vtbl_effect",
            "vtbl_font",
        ):
            self.assertIn(f"{vtbl_sym} = build_vtable(", self.d3d9_metal_mm)

        # 192 MiB LRU cache + evict_on_memory_warning
        self.assertIn("kTextureCacheLimitBytes = 192u * 1024u * 1024u", self.d3d9_shim_h)
        self.assertIn("evict_lru_to_budget(kTextureCacheLimitBytes)", self.d3d9_metal_mm)
        self.assertIn("void D3D9MetalBridge::evict_on_memory_warning()", self.d3d9_metal_mm)
        self.assertIn("evict_lru_to_budget(", self.d3d9_metal_mm)

        # Idempotent begin_frame / end_frame_and_present composition with com_dev_present
        self.assertIn("void D3D9MetalBridge::begin_frame()", self.d3d9_metal_mm)
        self.assertIn("void D3D9MetalBridge::end_frame_and_present()", self.d3d9_metal_mm)
        self.assertIn("impl_->in_frame = true;", self.d3d9_metal_mm)
        self.assertIn("impl_->guest_presented_this_frame = false;", self.d3d9_metal_mm)
        self.assertIn("if (!im->in_frame)", self.d3d9_metal_mm)
        self.assertIn("MBAA_PASS_PRESENT_BLIT", self.d3d9_metal_mm)

        # Centered 4:3 viewport inside drawable (1000x750 in 1334x750)
        self.assertIn("4.0 / 3.0", self.d3d9_metal_mm)
        self.assertIn("3.0 / 4.0", self.d3d9_metal_mm)
        self.assertIn("MTLViewport mvp{vpX, vpY, vpW, vpH, 0.0, 1.0};", self.d3d9_metal_mm)

    def test_live_dds_headers_across_archives_match_bcdec_dxt_support(self) -> None:
        dds_count = 0
        format_counts: dict[str, int] = {}

        for pname in sorted(MOUNT_ORDER):
            arc_path = MBAACC_DIR / pname
            if not arc_path.is_file():
                continue
            arc = FilePacArchive(arc_path)
            for entry in arc.files:
                if not entry.name.lower().endswith(".dds"):
                    continue
                raw = arc.read(entry)
                self.assertGreaterEqual(len(raw), 128, f"{pname}/{entry.name} truncated DDS")
                self.assertEqual(raw[:4], b"DDS ", f"{pname}/{entry.name} missing DDS magic")
                hdr_size = struct.unpack_from("<I", raw, 4)[0]
                self.assertEqual(hdr_size, 124)
                height, width = struct.unpack_from("<II", raw, 12)
                self.assertGreater(width, 0)
                self.assertGreater(height, 0)
                pf_size, pf_flags, fourcc, bitcount, rmask, gmask, bmask, amask = struct.unpack_from(
                    "<8I", raw, 76
                )
                self.assertEqual(pf_size, 32)
                dds_count += 1

                if pf_flags & 0x4:  # DDPF_FOURCC
                    fmt_key = fourcc.to_bytes(4, "little").decode("ascii", errors="replace")
                    self.assertIn(
                        fmt_key,
                        ("DXT1", "DXT2", "DXT3", "DXT4", "DXT5"),
                        f"Unsupported FourCC {fmt_key} in {pname}/{entry.name}",
                    )
                    self.assertIn(f"kD3DFMT_{fmt_key}", self.bcdec_cpp)
                else:
                    self.assertTrue((pf_flags & 0x40) != 0, f"Unexpected non-RGB DDS flags 0x{pf_flags:x}")
                    self.assertIn(bitcount, (16, 24, 32))
                    if bitcount == 32 and rmask == 0x00FF0000 and gmask == 0x0000FF00 and bmask == 0x000000FF:
                        fmt_key = "A8R8G8B8" if amask else "X8R8G8B8"
                    else:
                        fmt_key = f"RGB_{bitcount}"
                format_counts[fmt_key] = format_counts.get(fmt_key, 0) + 1

        self.assertGreaterEqual(dds_count, 1167)
        for req in ("DXT1", "DXT2", "DXT3", "DXT4", "DXT5", "A8R8G8B8"):
            self.assertGreater(format_counts.get(req, 0), 0, f"Expected live DDS format {req}")

    def test_bcdec_dxt_block_formulas_and_reference_math(self) -> None:
        # Verify bcdec_dxt.cpp contains exact formulas & edge guards matching reference math
        required_snippets = [
            "r = static_cast<uint8_t>((r5 << 3) | (r5 >> 2));",
            "g = static_cast<uint8_t>((g6 << 2) | (g6 >> 4));",
            "b = static_cast<uint8_t>((b5 << 3) | (b5 >> 2));",
            "if (a == 0u) {",
            "const uint32_t v = (static_cast<uint32_t>(c) * 255u + (static_cast<uint32_t>(a) >> 1)) /",
            "if (allow_3color_transparent && c0 <= c1)",
            "(2u * r0 + r1 + 1u) / 3u",
            "(r0 + 2u * r1 + 1u) / 3u",
            "decode_color_block(src_block + 8, false, pal, indices);",
            "static_cast<uint8_t>((a4 << 4) | a4);",
            "((7u - k) * a0 + k * a1 + 3u) / 7u",
            "((5u - k) * a0 + k * a1 + 2u) / 5u",
            "case DxtFormat::DXT2:",
            "bcdec_dxt23_block(src_ptr, dst_target, dst_pitch, true);",
            "case DxtFormat::DXT4:",
            "bcdec_dxt45_block(src_ptr, dst_target, dst_pitch, true);",
        ]
        for snip in required_snippets:
            self.assertIn(snip, self.bcdec_cpp, f"Missing expected formula in bcdec_dxt.cpp: {snip}")

        # Exercise Python reference DXT1/2/3/4/5 edge cases directly
        # DXT1 3-color + transparent (c0 <= c1)
        dxt1_trans = struct.pack("<HHI", 0x0000, 0xFFFF, 0xFFFFFFFF)
        px1 = ref_decode_dxt1_block(dxt1_trans)
        self.assertEqual(px1[0], (0, 0, 0, 0))
        dxt1_mid = struct.pack("<HHI", 0x0000, 0xFFFF, 0xAAAAAAAA)
        self.assertEqual(ref_decode_dxt1_block(dxt1_mid)[0], (127, 127, 127, 255))

        # DXT2 unpremultiply vs DXT3 straight (forced 4-color RGB even with c0==c1)
        alpha_4bit = struct.pack("<Q", 0x0000000000000080)  # pixel0=0, pixel1=8 (a8=0x88=136)
        rgb_blk = struct.pack("<HHI", 0xFFFF, 0x0000, 0x00000009)  # pixel0=c1(0), pixel1=c2(170)
        dxt2_px = ref_decode_dxt23_block(alpha_4bit + rgb_blk, unpremul=True)
        dxt3_px = ref_decode_dxt23_block(alpha_4bit + rgb_blk, unpremul=False)
        self.assertEqual(dxt2_px[0], (0, 0, 0, 0))  # a==0 guard
        self.assertEqual(dxt3_px[1][3], 136)
        self.assertEqual(dxt2_px[1], (255, 255, 255, 136))  # 170 * 255 / 136 -> clamped 255

        # DXT4/DXT5 interpolated 6-alpha mode (a0 <= a1) endpoints 0 and 255 at indices 6,7
        a_hdr = bytes([40, 200]) + (6 | (7 << 3)).to_bytes(6, "little")
        c_hdr = struct.pack("<HHI", 0x8410, 0x8410, 0)  # rgb=(132, 130, 132)
        dxt5_px = ref_decode_dxt45_block(a_hdr + c_hdr, unpremul=False)
        self.assertEqual(dxt5_px[0][3], 0)
        self.assertEqual(dxt5_px[1][3], 255)
        dxt4_px = ref_decode_dxt45_block(a_hdr + c_hdr, unpremul=True)
        self.assertEqual(dxt4_px[0], (0, 0, 0, 0))
        self.assertEqual(dxt4_px[1][3], 255)


if __name__ == "__main__":
    unittest.main()
