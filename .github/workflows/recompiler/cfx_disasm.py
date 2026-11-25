"""DirectX 9 (.cfx) Effect binary disassembler for MBAACC.

Reads the 9 compiled DX9 Effect (.cfx) binaries and `sh_bloom_sakura.txt` from
`0006.p` strictly in memory via `mbaacc.filepac.FilePacArchive` (BYOC compliant:
never writes raw .cfx binaries or copyrighted sources to disk) and emits a
metadata + disassembled shader analysis JSON (`ios/Shaders/cfx_analysis.json`).

Decodes:
- DX9 FX header (`0xFEFF0901`, parameter/technique/object counts)
- Parameter table + D3DXPARAMETER_TYPE / D3DXPARAMETER_CLASS + defaults
- Sampler state blocks (Texture bindings, MinFilter, MagFilter, MipFilter, AddressU/V)
- Techniques, passes, and pass render/shader states
- Shader object table (`vs_2_0`, `ps_2_0`, `ps_3_0`)
- CTAB constant tables & PRES/PRSI/CLIT/FXLC preshader metadata
- Complete SM 2.0 / 3.0 instruction token disassembly
"""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
import sys
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple


# Allow importing mbaacc.filepac from sibling ../mbaacc-src/py when run standalone
_REPO_ROOT = Path(__file__).resolve().parents[1]
_MBAACC_SRC_PY = _REPO_ROOT.parent / "mbaacc-src" / "py"
if _MBAACC_SRC_PY.is_dir() and str(_MBAACC_SRC_PY) not in sys.path:
    sys.path.insert(0, str(_MBAACC_SRC_PY))

from mbaacc.filepac import FilePacArchive  # noqa: E402


FX_MAGIC = 0xFEFF0901

D3DXPT_NAMES = {
    0: "void",
    1: "bool",
    2: "int",
    3: "float",
    4: "string",
    5: "texture",
    6: "texture1D",
    7: "texture2D",
    8: "texture3D",
    9: "textureCUBE",
    10: "sampler",
    11: "sampler1D",
    12: "sampler2D",
    13: "sampler3D",
    14: "samplerCUBE",
    15: "pixelshader",
    16: "vertexshader",
    17: "pixelFragment",
    18: "vertexFragment",
}

D3DXPC_NAMES = {
    0: "scalar",
    1: "vector",
    2: "matrix_rows",
    3: "matrix_columns",
    4: "object",
    5: "struct",
}

D3DXRS_NAMES = {
    0: "bool",
    1: "int4",
    2: "float4",
    3: "sampler",
}

# Wine / D3DX9 FX state table indices seen in MBAACC .cfx binaries
FX_PASS_STATE_NAMES = {
    0x00: "ZEnable",
    0x01: "FillMode",
    0x02: "ShadeMode",
    0x03: "ZWriteEnable",
    0x04: "AlphaTestEnable",
    0x05: "LastPixel",
    0x06: "SrcBlend",
    0x07: "DestBlend",
    0x08: "CullMode",
    0x09: "ZFunc",
    0x0A: "AlphaRef",
    0x0B: "AlphaFunc",
    0x0C: "DitherEnable",
    0x0D: "AlphaBlendEnable",
    0x0E: "FogEnable",
    0x92: "VertexShader",
    0x93: "PixelShader",
}

FX_SAMPLER_STATE_NAMES = {
    0xA4: "Texture",
    0xA5: "AddressU",
    0xA6: "AddressV",
    0xA7: "AddressW",
    0xA8: "BorderColor",
    0xA9: "MagFilter",
    0xAA: "MinFilter",
    0xAB: "MipFilter",
    0xAC: "MipMapLodBias",
    0xAD: "MaxMipLevel",
    0xAE: "MaxAnisotropy",
}

D3DTEXTUREFILTER_NAMES = {
    0: "None",
    1: "Point",
    2: "Linear",
    3: "Anisotropic",
    6: "PyramidalQuad",
    7: "GaussianQuad",
}

D3DTADDRESS_NAMES = {
    1: "Wrap",
    2: "Mirror",
    3: "Clamp",
    4: "Border",
    5: "MirrorOnce",
}

D3DSIO_OPCODES = {
    0: "nop",
    1: "mov",
    2: "add",
    3: "sub",
    4: "mad",
    5: "mul",
    6: "rcp",
    7: "rsq",
    8: "dp3",
    9: "dp4",
    10: "min",
    11: "max",
    12: "slt",
    13: "sge",
    14: "exp",
    15: "log",
    16: "lit",
    17: "dst",
    18: "lrp",
    19: "frc",
    20: "m4x4",
    21: "m4x3",
    22: "m3x4",
    23: "m3x3",
    24: "m3x2",
    25: "call",
    26: "callnz",
    27: "label",
    28: "else",
    29: "endif",
    30: "break",
    31: "dcl",
    32: "pow",
    33: "crs",
    34: "sgn",
    35: "abs",
    36: "nrm",
    37: "sincos",
    38: "rep",
    39: "endrep",
    40: "if",
    41: "ifc",
    42: "ret",
    43: "breakc",
    44: "defb",
    45: "defi",
    64: "texcoord",
    65: "texkill",
    66: "texld",
    67: "texbem",
    68: "texbeml",
    69: "texreg2ar",
    70: "texreg2gb",
    71: "texm3x2pad",
    72: "texm3x2tex",
    73: "texm3x3pad",
    74: "texm3x3tex",
    76: "texm3x3spec",
    77: "texm3x3vspec",
    78: "expp",
    79: "logp",
    80: "cnd",
    81: "def",
    82: "texreg2rgb",
    83: "texdp3tex",
    84: "texm3x2depth",
    85: "texdp3",
    86: "texm3x3",
    87: "texdepth",
    88: "cmp",
    89: "bem",
    90: "dp2add",
    91: "dsx",
    92: "dsy",
    93: "texldd",
    94: "setp",
    95: "texldl",
    96: "breakp",
}

D3DDECLUSAGE_NAMES = {
    0: "position",
    1: "blendweight",
    2: "blendindices",
    3: "normal",
    4: "psize",
    5: "texcoord",
    6: "tangent",
    7: "binormal",
    8: "tessfactor",
    9: "positiont",
    10: "color",
    11: "fog",
    12: "depth",
    13: "sample",
}

D3DSPR_NAMES = {
    0: "r",      # TEMP
    1: "v",      # INPUT
    2: "c",      # CONST
    3: "t_or_a", # ADDR (VS) / TEXTURE (PS)
    4: "rast",   # RASTOUT (oPos, oFog, oPts)
    5: "oD",     # ATTROUT
    6: "oT",     # TEXCRDOUT / OUTPUT
    7: "i",      # CONSTINT
    8: "oC",     # COLOROUT
    9: "oDepth", # DEPTHOUT
    10: "s",     # SAMPLER
    11: "c2",    # CONST2
    12: "c3",    # CONST3
    13: "c4",    # CONST4
    14: "b",     # CONSTBOOL
    15: "aL",    # LOOP
    16: "l",     # LABEL
    17: "misc",  # MISCTYPE
    18: "p",     # PREDICATE
}

RASTOUT_NAMES = {0: "oPos", 1: "oFog", 2: "oPts"}
MISCTYPE_NAMES = {0: "vPos", 1: "vFace"}


def _read_fx_string(data: bytes, base: int, rel_off: int) -> Optional[str]:
    if rel_off == 0:
        return None
    p = base + rel_off
    if p + 4 > len(data):
        return None
    slen = struct.unpack_from("<I", data, p)[0]
    raw = data[p + 4 : p + 4 + slen]
    return raw.split(b"\x00", 1)[0].decode("ascii", errors="replace")


def _decode_ctab(blob: bytes) -> Dict[str, Any]:
    """Decode a DX9 CTAB constant table chunk (without 'CTAB' 4-byte prefix)."""
    if len(blob) < 28:
        return {}
    (
        size,
        creator_off,
        version,
        constants,
        const_info_off,
        flags,
        target_off,
    ) = struct.unpack_from("<7I", blob, 0)

    def cstr(off: int) -> str:
        if off <= 0 or off >= len(blob):
            return ""
        end = blob.find(b"\x00", off)
        if end < 0:
            end = len(blob)
        return blob[off:end].decode("ascii", errors="replace")

    entries = []
    for i in range(constants):
        off = const_info_off + i * 20
        if off + 20 > len(blob):
            break
        name_off, reg_set, reg_idx, reg_cnt, type_off, def_off = struct.unpack_from(
            "<IHHHHII" if False else "<IHHHII", blob, off
        )
        # Wait: CTAB entry is 20 bytes:
        #   uint32 Name; uint16 RegisterSet; uint16 RegisterIndex;
        #   uint16 RegisterCount; uint16 Reserved; uint32 TypeInfo; uint32 DefaultValue;
        name_off, reg_set, reg_idx, reg_cnt, _res, type_off, def_off = struct.unpack_from(
            "<IHHHHII", blob, off
        )
        tclass, ttype, rows, cols, elems, members, mem_off = (0, 0, 0, 0, 0, 0, 0)
        if type_off and type_off + 16 <= len(blob):
            tclass, ttype, rows, cols, elems, members, mem_off = struct.unpack_from(
                "<HHHHHHI", blob, type_off
            )
        reg_prefix = {0: "b", 1: "i", 2: "c", 3: "s"}.get(reg_set, "?")
        entries.append(
            {
                "name": cstr(name_off),
                "register_set": D3DXRS_NAMES.get(reg_set, str(reg_set)),
                "register": f"{reg_prefix}{reg_idx}",
                "register_index": reg_idx,
                "register_count": reg_cnt,
                "class": D3DXPC_NAMES.get(tclass, str(tclass)),
                "type": D3DXPT_NAMES.get(ttype, str(ttype)),
                "rows": rows,
                "columns": cols,
                "elements": elems,
            }
        )

    return {
        "creator": cstr(creator_off),
        "target": cstr(target_off),
        "version": f"0x{version:08x}",
        "flags": flags,
        "constants": entries,
    }


def _decode_pres(blob: bytes) -> Dict[str, Any]:
    """Decode PRES preshader comment sub-chunks (PRSI / CLIT / FXLC / CTAB)."""
    if len(blob) < 4:
        return {}
    ver = struct.unpack_from("<I", blob, 0)[0]
    info: Dict[str, Any] = {"version": f"0x{ver:08x}", "chunks": []}
    # Preshader starts with version dword then embedded comment tokens (0xFFFE)
    pos = 4
    while pos + 4 <= len(blob):
        tok = struct.unpack_from("<I", blob, pos)[0]
        pos += 4
        op = tok & 0xFFFF
        if op == 0xFFFF:
            break
        if op == 0xFFFE:
            cnt = (tok >> 16) & 0xFFFF
            sub = blob[pos : pos + cnt * 4]
            pos += cnt * 4
            tag = sub[:4].decode("ascii", errors="replace")
            chunk_info: Dict[str, Any] = {"tag": tag, "bytes": len(sub) - 4}
            if tag == "CTAB":
                chunk_info["ctab"] = _decode_ctab(sub[4:])
            elif tag == "CLIT" and len(sub) >= 8:
                lit_cnt = struct.unpack_from("<I", sub, 4)[0]
                lits = list(struct.unpack_from(f"<{lit_cnt}d", sub, 8)) if 8 + lit_cnt * 8 <= len(sub) else []
                chunk_info["literals"] = lits
            elif tag == "PRSI" and len(sub) >= 16:
                hdr = struct.unpack_from("<4I", sub, 4)
                chunk_info["prsi_header"] = list(hdr)
            elif tag == "FXLC" and len(sub) >= 8:
                fxlc_cnt = struct.unpack_from("<I", sub, 4)[0]
                chunk_info["instruction_count"] = fxlc_cnt
            info["chunks"].append(chunk_info)
        else:
            break
    return info


def _format_reg(tok: int, is_vs: bool, major: int, is_dst: bool) -> str:
    rtype = ((tok >> 28) & 0x7) | (((tok >> 11) & 0x3) << 3)
    reg_num = tok & 0x7FF
    rel_addr = bool((tok >> 13) & 1)

    if rtype == 3:  # ADDR in VS, TEXTURE in PS (<3.0)
        name = f"a{reg_num}" if is_vs else f"t{reg_num}"
    elif rtype == 4:
        name = RASTOUT_NAMES.get(reg_num, f"rast{reg_num}")
    elif rtype == 6:
        name = f"oT{reg_num}" if (is_vs and major < 3) else f"o{reg_num}"
    elif rtype == 17:
        name = MISCTYPE_NAMES.get(reg_num, f"misc{reg_num}")
    else:
        prefix = D3DSPR_NAMES.get(rtype, f"reg{rtype}_")
        name = f"{prefix}{reg_num}"

    if rel_addr:
        name += "[a0]"

    if is_dst:
        mask = (tok >> 16) & 0xF
        if mask != 0xF and mask != 0:
            chars = "".join(c for bit, c in ((1, "x"), (2, "y"), (4, "z"), (8, "w")) if mask & bit)
            name += f".{chars}"
        return name

    # Source swizzle & modifier
    swiz = (tok >> 16) & 0xFF
    if swiz != 0xE4:  # not .xyzw
        comps = ("x", "y", "z", "w")
        s = "".join(comps[(swiz >> (2 * i)) & 3] for i in range(4))
        while len(s) > 1 and s[-1] == s[-2]:
            s = s[:-1]
        name += f".{s}"

    src_mod = (tok >> 24) & 0xF
    if src_mod == 1:
        name = f"-{name}"
    elif src_mod == 2:
        name = f"{name}_bias"
    elif src_mod == 3:
        name = f"-{name}_bias"
    elif src_mod == 4:
        name = f"{name}_bx2"
    elif src_mod == 5:
        name = f"-{name}_bx2"
    elif src_mod == 6:
        name = f"1-{name}"
    elif src_mod == 7:
        name = f"{name}_dz"
    elif src_mod == 8:
        name = f"{name}_dw"
    elif src_mod == 11:
        name = f"abs({name})"
    elif src_mod == 12:
        name = f"-abs({name})"
    elif src_mod == 13:
        name = f"!{name}"
    return name


def _decode_shader_blob(blob: bytes) -> Dict[str, Any]:
    if len(blob) < 4:
        return {"error": "truncated"}
    tokens = struct.unpack_from(f"<{len(blob) // 4}I", blob, 0)
    ver = tokens[0]
    shader_type = "ps" if ((ver >> 16) & 0xFFFF) == 0xFFFF else "vs"
    major = (ver >> 8) & 0xFF
    minor = ver & 0xFF
    profile = f"{shader_type}_{major}_{minor}"
    is_vs = shader_type == "vs"

    ctab: Optional[Dict[str, Any]] = None
    preshader: Optional[Dict[str, Any]] = None
    comment_strings: List[str] = []
    instructions: List[str] = []
    constants_def: List[Dict[str, Any]] = []
    declarations: List[str] = []

    idx = 1
    while idx < len(tokens):
        tok = tokens[idx]
        idx += 1
        op = tok & 0xFFFF
        if op == 0xFFFF:
            break
        if op == 0xFFFE:
            cnt = (tok >> 16) & 0xFFFF
            raw = blob[idx * 4 : (idx + cnt) * 4]
            idx += cnt
            fourcc = raw[:4]
            if fourcc == b"CTAB":
                ctab = _decode_ctab(raw[4:])
            elif fourcc == b"PRES":
                preshader = _decode_pres(raw[4:])
            else:
                txt = raw.split(b"\x00", 1)[0].decode("ascii", errors="replace")
                if txt:
                    comment_strings.append(txt)
            continue

        n_toks = (tok >> 24) & 0xF
        params = tokens[idx : idx + n_toks]
        idx += n_toks

        if op == 81 and len(params) == 5:  # def c#, x, y, z, w
            dst_name = _format_reg(params[0], is_vs, major, is_dst=True)
            vals = [struct.unpack("<f", struct.pack("<I", v))[0] for v in params[1:5]]
            constants_def.append({"register": dst_name, "value": vals})
            instructions.append(
                f"def {dst_name}, {vals[0]:.6g}, {vals[1]:.6g}, {vals[2]:.6g}, {vals[3]:.6g}"
            )
            continue

        if op == 31 and len(params) >= 2:  # dcl
            dcl_tok = params[0]
            dst_tok = params[1]
            dst_str = _format_reg(dst_tok, is_vs, major, is_dst=True)
            rtype = ((dst_tok >> 28) & 0x7) | (((dst_tok >> 11) & 0x3) << 3)
            if rtype == 10:  # sampler
                tex_type = (dcl_tok >> 27) & 0xF
                st_name = {2: "2d", 3: "cube", 4: "volume"}.get(tex_type, str(tex_type))
                decl = f"dcl_{st_name} {dst_str}"
            elif not is_vs and major < 3:
                # ps_2_0 input/texcoord declarations do not encode semantic usage
                decl = f"dcl {dst_str}"
            else:
                usage = dcl_tok & 0x1F
                usage_idx = (dcl_tok >> 16) & 0xF
                uname = D3DDECLUSAGE_NAMES.get(usage, f"u{usage}")
                suffix = f"{uname}{usage_idx if usage_idx or uname == 'texcoord' else ''}"
                decl = f"dcl_{suffix} {dst_str}"
            declarations.append(decl)
            instructions.append(decl)
            continue

        op_name = D3DSIO_OPCODES.get(op, f"op_{op}")
        dst_tok = params[0] if params else 0
        # dst result modifier (bits 20..23): bit 0 = _sat, bit 1 = _pp, bit 2 = _centroid
        res_mod = (dst_tok >> 20) & 0xF if params else 0
        mod_str = ""
        if res_mod & 1:
            mod_str += "_sat"
        if res_mod & 2:
            mod_str += "_pp"
        if res_mod & 4:
            mod_str += "_centroid"

        formatted_ops = []
        for j, pt in enumerate(params):
            formatted_ops.append(_format_reg(pt, is_vs, major, is_dst=(j == 0)))
        instructions.append(f"{op_name}{mod_str} " + ", ".join(formatted_ops))

    return {
        "profile": profile,
        "version_token": f"0x{ver:08x}",
        "byte_size": len(blob),
        "ctab": ctab,
        "preshader": preshader,
        "declarations": declarations,
        "def_constants": constants_def,
        "instructions": instructions,
    }


def _decode_default_value(
    data: bytes, base: int, val_off: int, ptype: int, pclass: int, rows: int, cols: int, elems: int
) -> Any:
    if val_off == 0:
        return None
    p = base + val_off
    if ptype in (10, 11, 12, 13, 14):  # sampler
        if p + 4 > len(data):
            return None
        num_states = struct.unpack_from("<I", data, p)[0]
        sp = p + 4
        states = []
        for _ in range(num_states):
            if sp + 16 > len(data):
                break
            sop, sunk, svoff, spoff = struct.unpack_from("<4I", data, sp)
            sp += 16
            sname = FX_SAMPLER_STATE_NAMES.get(sop, f"SamplerState_0x{sop:x}")
            sval: Any = None
            if sop == 0xA4:  # Texture = <name> referenced by object_id at spoff
                if spoff and base + spoff + 4 <= len(data):
                    sval = {"object_id": struct.unpack_from("<I", data, base + spoff)[0]}
            elif spoff and base + spoff + 4 <= len(data):
                raw_v = struct.unpack_from("<I", data, base + spoff)[0]
                if sop in (0xA9, 0xAA, 0xAB):
                    sval = D3DTEXTUREFILTER_NAMES.get(raw_v, raw_v)
                elif sop in (0xA5, 0xA6, 0xA7):
                    sval = D3DTADDRESS_NAMES.get(raw_v, raw_v)
                else:
                    sval = raw_v
            states.append({"state": sname, "value": sval})
        return {"sampler_states": states}

    if ptype in (5, 6, 7, 8, 9):  # texture
        obj_id = struct.unpack_from("<I", data, p)[0] if p + 4 <= len(data) else 0
        return {"object_id": obj_id}

    count = max(1, rows) * max(1, cols) * max(1, elems)
    if ptype == 3 and p + count * 4 <= len(data):  # float
        return list(struct.unpack_from(f"<{count}f", data, p))
    if ptype in (1, 2) and p + count * 4 <= len(data):  # bool / int
        return list(struct.unpack_from(f"<{count}i", data, p))
    return None


def parse_cfx_bytes(name: str, data: bytes) -> Dict[str, Any]:
    if len(data) < 8:
        raise ValueError(f"{name}: truncated FX binary ({len(data)} bytes)")
    magic, hdr_rel = struct.unpack_from("<II", data, 0)
    if magic != FX_MAGIC:
        raise ValueError(f"{name}: invalid FX magic 0x{magic:08x} (expected 0x{FX_MAGIC:08x})")

    base = 8
    hdr_off = base + hdr_rel
    n_param, n_tech, unk_count, n_obj = struct.unpack_from("<4I", data, hdr_off)
    pos = hdr_off + 16

    params: List[Dict[str, Any]] = []
    for _ in range(n_param):
        type_off, val_off, flags, ann_cnt = struct.unpack_from("<4I", data, pos)
        pos += 16
        pos += ann_cnt * 8
        tp = base + type_off
        ptype, pclass, name_off, sem_off, elems = struct.unpack_from("<5I", data, tp)
        rows, cols = (1, 1)
        if pclass in (0, 1, 2, 3):
            rows, cols = struct.unpack_from("<2I", data, tp + 20)
        pname = _read_fx_string(data, base, name_off)
        psem = _read_fx_string(data, base, sem_off)
        default_val = _decode_default_value(data, base, val_off, ptype, pclass, rows, cols, elems)
        params.append(
            {
                "name": pname,
                "semantic": psem,
                "type": D3DXPT_NAMES.get(ptype, f"type_{ptype}"),
                "class": D3DXPC_NAMES.get(pclass, f"class_{pclass}"),
                "rows": rows,
                "columns": cols,
                "elements": elems,
                "flags": flags,
                "default": default_val,
            }
        )

    techniques: List[Dict[str, Any]] = []
    for t_idx in range(n_tech):
        tname_off, ann_cnt, pass_cnt = struct.unpack_from("<3I", data, pos)
        pos += 12
        pos += ann_cnt * 8
        tname = _read_fx_string(data, base, tname_off)
        passes: List[Dict[str, Any]] = []
        for p_idx in range(pass_cnt):
            pname_off, pann_cnt, state_cnt = struct.unpack_from("<3I", data, pos)
            pos += 12
            pos += pann_cnt * 8
            pname = _read_fx_string(data, base, pname_off)
            states: List[Dict[str, Any]] = []
            for _ in range(state_cnt):
                sop, sunk, svoff, spoff = struct.unpack_from("<4I", data, pos)
                pos += 16
                sname = FX_PASS_STATE_NAMES.get(sop, f"State_0x{sop:x}")
                val = struct.unpack_from("<I", data, base + spoff)[0] if spoff else None
                states.append({"state": sname, "state_id": sop, "value": val})
            passes.append({"name": pname, "states": states})
        techniques.append({"index": t_idx, "name": tname, "passes": passes})

    n_small, n_blobs = struct.unpack_from("<2I", data, pos)
    pos += 8
    resource_bindings = []
    for _ in range(n_small):
        obj_id, bind_type = struct.unpack_from("<2I", data, pos)
        pos += 8
        resource_bindings.append({"object_id": obj_id, "kind": bind_type})

    string_objects: Dict[int, str] = {}
    shaders: List[Dict[str, Any]] = []
    for b_idx in range(n_blobs):
        tech_idx, pass_or_obj, arr_idx, state_idx, obj_type, sz = struct.unpack_from("<6I", data, pos)
        pos += 24
        blob = data[pos : pos + sz]
        pos += (sz + 3) & ~3
        if tech_idx == 0xFFFFFFFF and obj_type == 1:
            string_objects[pass_or_obj] = blob.split(b"\x00", 1)[0].decode("ascii", errors="replace")
        else:
            decoded = _decode_shader_blob(blob)
            decoded["blob_index"] = b_idx
            decoded["technique_index"] = tech_idx
            decoded["pass_index"] = pass_or_obj
            decoded["state_index"] = state_idx
            shaders.append(decoded)

    # Resolve string object references on sampler Texture states & technique pass shader bindings
    for p in params:
        d = p.get("default")
        if isinstance(d, dict) and "sampler_states" in d:
            for st in d["sampler_states"]:
                v = st.get("value")
                if isinstance(v, dict) and "object_id" in v:
                    oid = v["object_id"]
                    if oid in string_objects:
                        st["resolved_name"] = string_objects[oid]
                    elif (oid - 1) in string_objects:
                        st["resolved_name"] = string_objects[oid - 1]

    for tech in techniques:
        for ps_idx, pinfo in enumerate(tech["passes"]):
            for st in pinfo["states"]:
                if st["state"] in ("VertexShader", "PixelShader"):
                    match = [
                        s
                        for s in shaders
                        if s["technique_index"] == tech["index"]
                        and s["pass_index"] == ps_idx
                        and (
                            (st["state"] == "VertexShader" and s["profile"].startswith("vs_"))
                            or (st["state"] == "PixelShader" and s["profile"].startswith("ps_"))
                        )
                    ]
                    if match:
                        st["shader_blob_index"] = match[0]["blob_index"]
                        st["profile"] = match[0]["profile"]

    return {
        "file": name,
        "byte_size": len(data),
        "sha256": hashlib.sha256(data).hexdigest(),
        "header": {
            "magic": f"0x{magic:08x}",
            "header_offset": hdr_rel,
            "param_count": n_param,
            "technique_count": n_tech,
            "unk_count": unk_count,
            "object_count": n_obj,
        },
        "parameters": params,
        "techniques": techniques,
        "string_objects": {str(k): v for k, v in sorted(string_objects.items())},
        "shaders": shaders,
    }


def analyze_p0006(p0006_path: Path) -> Dict[str, Any]:
    arc = FilePacArchive(p0006_path)
    cfx_entries = sorted(
        (e for e in arc.files if e.name.lower().endswith(".cfx")),
        key=lambda e: e.name.lower(),
    )
    txt_entry = next((e for e in arc.files if e.name.lower() == "sh_bloom_sakura.txt"), None)

    effects = []
    total_techniques = 0
    total_passes = 0
    total_shaders = 0
    for e in cfx_entries:
        raw = arc.read(e)
        parsed = parse_cfx_bytes(e.name, raw)
        effects.append(parsed)
        total_techniques += len(parsed["techniques"])
        total_passes += sum(len(t["passes"]) for t in parsed["techniques"])
        total_shaders += len(parsed["shaders"])

    txt_meta: Optional[Dict[str, Any]] = None
    if txt_entry is not None:
        txt_bytes = arc.read(txt_entry)
        txt_str = txt_bytes.decode("cp932", errors="replace")
        txt_meta = {
            "file": txt_entry.name,
            "virtual_path": txt_entry.virtual_path,
            "byte_size": len(txt_bytes),
            "line_count": len(txt_str.splitlines()),
            "sha256": hashlib.sha256(txt_bytes).hexdigest(),
            "techniques_declared": [
                line.split()[1]
                for line in txt_str.splitlines()
                if line.strip().startswith("technique ")
            ],
        }

    return {
        "schema_version": 1,
        "source_archive": p0006_path.name,
        "byoc_policy": "metadata_and_disassembly_only_no_raw_assets",
        "summary": {
            "cfx_count": len(effects),
            "technique_count": total_techniques,
            "pass_count": total_passes,
            "shader_blob_count": total_shaders,
        },
        "reference_hlsl_txt": txt_meta,
        "effects": effects,
    }


def main(argv: Optional[List[str]] = None) -> int:
    parser = argparse.ArgumentParser(description="Disassemble MBAACC 0006.p DX9 .cfx shaders.")
    parser.add_argument(
        "--p0006",
        type=Path,
        default=Path(r"c:\Users\A\Desktop\AI\google\MBAACC\0006.p"),
        help="Path to 0006.p FilePac archive (read strictly in memory).",
    )
    parser.add_argument(
        "--out",
        type=Path,
        default=_REPO_ROOT / "ios" / "Shaders" / "cfx_analysis.json",
        help="Output JSON metadata file.",
    )
    args = parser.parse_args(argv)

    result = analyze_p0006(args.p0006)
    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text(json.dumps(result, indent=2), encoding="utf-8")
    s = result["summary"]
    print(
        f"cfx_disasm: decoded {s['cfx_count']} .cfx effects, "
        f"{s['technique_count']} techniques, {s['pass_count']} passes, "
        f"{s['shader_blob_count']} compiled shaders -> {args.out}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
