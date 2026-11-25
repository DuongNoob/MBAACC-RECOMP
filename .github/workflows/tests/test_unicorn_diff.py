"""Independent differential verification of lifted x86-32 + x87 IR against Unicorn x86-32."""

from __future__ import annotations

import struct
import sys
import unittest
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
MBAA_EXE = Path(r"c:\Users\A\Desktop\AI\google\MBAACC\MBAA.exe")

if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from recompiler.ir_eval import (  # noqa: E402
    FLAG_AF,
    FLAG_CF,
    FLAG_DF,
    FLAG_OF,
    FLAG_PF,
    FLAG_SF,
    FLAG_ZF,
    SCRATCH_BASE,
    DifferentialSuite,
)


class TestUnicornDifferential(unittest.TestCase):
    """Run lifted IR interpreter side-by-side against Unicorn x86-32 on live MBAA.exe."""

    @classmethod
    def setUpClass(cls) -> None:
        cls.suite = DifferentialSuite(MBAA_EXE)

    def test_full_ir_eval_differential_suite(self) -> None:
        res = self.suite.run_all()
        self.assertEqual(res["failed"], 0, f"Unicorn differential failures: {res}")
        self.assertGreaterEqual(res["passed"], 83)

    def test_filepac_hash_cipher_seek_xor_individual_cases(self) -> None:
        # Signed-byte weighted hash (0x004db470) including high-bit Shift-JIS bytes
        uc, mem, ctx = self.suite._new_pair()
        s = b"\x83\x81\x83\x8b\x83u\x00_test.ha6"[:11]
        self.suite._sync_write(uc, mem, SCRATCH_BASE, b"\x00" * 32)
        self.suite._sync_write(uc, mem, SCRATCH_BASE + 4, s + b"\x00")
        self.suite._sync_write(uc, mem, SCRATCH_BASE + 0x14, struct.pack("<II", len(s), 15))
        ctx_out, uc_out = self.suite._run_both(0x004DB470, uc, mem, ctx, regs={"edi": SCRATCH_BASE})
        self.assertEqual(ctx_out.eax, uc_out["eax"])

        # Stream cipher seek (0x004db590) + XOR (0x004db5e0) across boundary 4096
        uc, mem, ctx = self.suite._new_pair()
        seed = 0x13579BDF
        blob = struct.pack("<IBB4s2sII", seed, 5, 0, seed.to_bytes(4, "little"), b"\x00\x00", 0, 4096)
        payload = bytes((i * 37 + 11) & 0xFF for i in range(4120))
        self.suite._sync_write(uc, mem, SCRATCH_BASE, blob)
        self.suite._sync_write(uc, mem, SCRATCH_BASE + 0x1000, payload)
        self.suite._run_both(0x004DB590, uc, mem, ctx, regs={"eax": SCRATCH_BASE, "ecx": 4090})
        self.suite._run_both(0x004DB5E0, uc, mem, ctx, regs={"eax": SCRATCH_BASE}, push_args=[SCRATCH_BASE + 0x1000, len(payload)])
        self.assertEqual(
            mem.read_bytes(SCRATCH_BASE + 0x1000, len(payload)),
            bytes(uc.mem_read(SCRATCH_BASE + 0x1000, len(payload))),
        )

    def test_bpe_palette_and_savedata_functions(self) -> None:
        # BPE (0x00417270) literal pass-through
        uc, mem, ctx = self.suite._new_pair()
        hdr = bytearray(0x48)
        hdr[0:4] = b"BPE\x00"
        raw = bytes(hdr) + bytes([0xFF, 128, 0xFE, 0, 6]) + b"MBAACC"
        in_ptr = SCRATCH_BASE
        out_ptr = SCRATCH_BASE + 0x20000
        self.suite._sync_write(uc, mem, in_ptr, raw)
        self.suite._sync_write(uc, mem, out_ptr, b"\x00" * 64)
        ctx_out, uc_out = self.suite._run_both(0x00417270, uc, mem, ctx, push_args=[out_ptr, in_ptr, len(raw)])
        self.assertEqual(ctx_out.eax, uc_out["eax"])
        self.assertEqual(mem.read_bytes(out_ptr, 64), bytes(uc.mem_read(out_ptr, 64)))

        # Palette index-0 remap (0x004020a0)
        uc, mem, ctx = self.suite._new_pair()
        pal = bytearray(256 * 4)
        pal[0:4] = b"\x00\x00\x00\xFF"
        pal[4:8] = b"\x00\x00\x00\xFF"
        pal[8:12] = b"\x10\x20\x30\xFF"
        self.suite._sync_write(uc, mem, SCRATCH_BASE, bytes(pal))
        self.suite._run_both(0x004020A0, uc, mem, ctx, regs={"eax": SCRATCH_BASE})
        self.assertEqual(mem.read_bytes(SCRATCH_BASE, 1024), bytes(uc.mem_read(SCRATCH_BASE, 1024)))

        # SaveData reset + validate roundtrip (0x00401050 + 0x00401000, 0x00401490 + 0x00401370)
        uc, mem, ctx = self.suite._new_pair()
        self.suite._sync_write(uc, mem, SCRATCH_BASE, b"\x55" * 0x3E0)
        self.suite._sync_write(uc, mem, 0x0055413C, struct.pack("<I", SCRATCH_BASE))
        self.suite._run_both(0x00401050, uc, mem, ctx)
        ctx_v, uc_v = self.suite._run_both(0x00401000, uc, mem, ctx)
        self.assertEqual(ctx_v.eax, uc_v["eax"])
        self.assertEqual(mem.read_bytes(SCRATCH_BASE, 0x3E0), bytes(uc.mem_read(SCRATCH_BASE, 0x3E0)))

        uc, mem, ctx = self.suite._new_pair()
        self.suite._sync_write(uc, mem, SCRATCH_BASE, b"\x55" * 0x17C)
        self.suite._sync_write(uc, mem, 0x00554140, struct.pack("<I", SCRATCH_BASE))
        self.suite._run_both(0x00401490, uc, mem, ctx, regs={"eax": SCRATCH_BASE})
        ctx_v2, uc_v2 = self.suite._run_both(0x00401370, uc, mem, ctx)
        self.assertEqual(ctx_v2.eax, uc_v2["eax"])
        self.assertEqual(mem.read_bytes(SCRATCH_BASE, 0x17C), bytes(uc.mem_read(SCRATCH_BASE, 0x17C)))

    def test_extra_x87_flags_shifts_and_string_diff(self) -> None:
        # Edge-case x87 fild/fabs/fimul/fistp + shift/rotate + partial-reg AL write + rep stosb
        snip = bytes.fromhex(
            "db0500000002"          # fild dword ptr [0x02000000] (-12345)
            "d9e1"                  # fabs (12345)
            "da0d04000002"          # fimul dword ptr [0x02000004] (*3 = 37035)
            "db1d08000002"          # fistp dword ptr [0x02000008]
            "b880000000"            # mov eax, 0x80
            "b103"                  # mov cl, 3
            "d3c8"                  # ror eax, cl -> 0x10
            "c1c018"                # rol eax, 24 -> 0x10000000
            "bf20000002"            # mov edi, 0x02000020
            "b05a"                  # mov al, 0x5a -> preserves upper 24 bits: 0x1000005a
            "b907000000"            # mov ecx, 7
            "f3aa"                  # rep stosb
            "c3"
        )
        self.suite.run_machine_snippet_diff(
            snip,
            mem_init={SCRATCH_BASE: struct.pack("<ii", -12345, 3)},
            flag_mask=FLAG_CF | FLAG_PF | FLAG_ZF | FLAG_SF | FLAG_DF | FLAG_OF,
        )


if __name__ == "__main__":
    unittest.main()
