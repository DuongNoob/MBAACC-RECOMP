/**
 * @file mbaa_shaders.metal
 * @brief Apple Metal 2.4 shaders for mbaacc-recomp-ios (iPhone SE 2020 / A13 Bionic).
 *
 * Implements:
 *   - Fixed-function Direct3D 9 2D (XYZRHW) & 3D (XYZ) sprite/polygon/font rendering
 *   - Aspect-preserving 4:3 (1000x750) centered present blit into 1334x750 MTKView
 *   - Exact Metal translations of all 9 MBAACC .cfx effects (22 techniques, 28 passes):
 *       1. sh_bloom_sakura.cfx (TecSakuraBloom, TecSakuraBloom_Ready, TecSakuraBloom_Update P0/P1)
 *       2. sh_blur.cfx         (BgPointBlur P0/P1)
 *       3. sh_chara.cfx        (TecCharaDraw, TecCharaDrawEx, TecCharaDraw_Edge)
 *       4. sh_fade.cfx         (TecFade_ExFade0, TecFade_ExFade1)
 *       5. sh_gaugedraw.cfx    (TecMagicCircuitDraw)
 *       6. sh_mono.cfx         (TecBloom_Blt, TecBloom_Fill, TecBloom_Make P0/P1, TecMono, TecMonoFill)
 *       7. sh_noise.cfx        (TecNoise P0/P1)
 *       8. sh_normal.cfx       (TecNormal P0/P1, TecNormalAngle P0/P1)
 *       9. vsfx.cfx            (TransformTec, TecFilterColorCut, TecFilter12Sample, TecBloom)
 */

#include <metal_stdlib>
using namespace metal;

#include "shader_manifest.h"

// ---------------------------------------------------------------------------
// Common Vertex / Fragment I/O Structures
// ---------------------------------------------------------------------------
struct VertexIn {
    float4 position  [[attribute(0)]];
    float4 diffuse   [[attribute(1)]];
    float4 specular  [[attribute(2)]];
    float2 texcoord0 [[attribute(3)]];
    float2 texcoord1 [[attribute(4)]];
};

struct VertexOut {
    float4 position  [[position]];
    float4 diffuse   [[user(color0)]];
    float4 specular  [[user(color1)]];
    float2 texcoord0 [[user(tex0)]];
    float2 texcoord1 [[user(tex1)]];
};

struct FragOut2 {
    float4 c0 [[color(0)]];
    float4 c1 [[color(1)]];
};

struct FragOut3 {
    float4 c0 [[color(0)]];
    float4 c1 [[color(1)]];
    float4 c2 [[color(2)]];
};

// ---------------------------------------------------------------------------
// Helpers: DX9 Alpha Test & Color-Op Emulation
// ---------------------------------------------------------------------------
inline bool dx9_alpha_test_pass(float a, uint func, float ref) {
    switch (func) {
        case 1u: return false;      // D3DCMP_NEVER
        case 2u: return a < ref;    // D3DCMP_LESS
        case 3u: return a == ref;   // D3DCMP_EQUAL
        case 4u: return a <= ref;   // D3DCMP_LESSEQUAL
        case 5u: return a > ref;    // D3DCMP_GREATER
        case 6u: return a != ref;   // D3DCMP_NOTEQUAL
        case 7u: return a >= ref;   // D3DCMP_GREATEREQUAL
        case 8u: default: return true; // D3DCMP_ALWAYS
    }
}

inline float4 mul_row_major4x4(float4 v, constant float4* m) {
    return float4(
        dot(v, m[0]),
        dot(v, m[1]),
        dot(v, m[2]),
        dot(v, m[3])
    );
}

// ---------------------------------------------------------------------------
// Vertex Shaders
// ---------------------------------------------------------------------------
vertex VertexOut vs_mbaa_main(
    VertexIn in [[stage_in]],
    constant MbaaDrawUniforms& u [[buffer(MBAA_BUF_DRAW_UNIFORMS)]])
{
    VertexOut out;
    if (u.is_transformed != 0u) {
        // DX9 D3DFVF_XYZRHW screen pixels -> Metal NDC:
        // Add +0.5 half-pixel shift so DX9 (-0.5..W-0.5) quads align with Metal pixel centers.
        float sx = (in.position.x + 0.5f) - u.viewport_inv.z;
        float sy = (in.position.y + 0.5f) - u.viewport_inv.w;
        float ndc_x = sx * u.viewport_inv.x - 1.0f;
        float ndc_y = 1.0f - sy * u.viewport_inv.y;
        float z = clamp(in.position.z, 0.0f, 1.0f);
        out.position = float4(ndc_x, ndc_y, z, 1.0f);
    } else {
        float4 p = float4(in.position.xyz, 1.0f);
        out.position = mul_row_major4x4(p, u.world_view_proj);
    }
    out.diffuse   = in.diffuse;
    out.specular  = in.specular;
    out.texcoord0 = in.texcoord0;
    out.texcoord1 = in.texcoord1;
    return out;
}

vertex VertexOut vs_vsfx_transform(
    VertexIn in [[stage_in]],
    constant MbaaDrawUniforms& u [[buffer(MBAA_BUF_DRAW_UNIFORMS)]])
{
    // Exact mirror of vsfx.cfx TransformTec VS_0:
    //   dp4 oPos.x..w, v0, c0..c3; mov oD0, v1; mov oD1, v2; mov oT0.xy, v3
    VertexOut out;
    float4 p = float4(in.position.xyz, 1.0f);
    out.position  = mul_row_major4x4(p, u.world_view_proj);
    out.diffuse   = in.diffuse;
    out.specular  = in.specular;
    out.texcoord0 = in.texcoord0;
    out.texcoord1 = in.texcoord1;
    return out;
}

struct PresentVertexOut {
    float4 position [[position]];
    float2 uv       [[user(uv)]];
};

vertex PresentVertexOut vs_present_quad(uint vid [[vertex_id]]) {
    // Full-viewport triangle strip (0: TL, 1: BL, 2: TR, 3: BR)
    const float2 pos[4] = {
        float2(-1.0f,  1.0f),
        float2(-1.0f, -1.0f),
        float2( 1.0f,  1.0f),
        float2( 1.0f, -1.0f)
    };
    const float2 uvs[4] = {
        float2(0.0f, 0.0f),
        float2(0.0f, 1.0f),
        float2(1.0f, 0.0f),
        float2(1.0f, 1.0f)
    };
    PresentVertexOut out;
    out.position = float4(pos[vid], 0.0f, 1.0f);
    out.uv       = uvs[vid];
    return out;
}

fragment float4 ps_present_blit(
    PresentVertexOut in [[stage_in]],
    texture2d<float> backbuffer [[texture(MBAA_TEX_STAGE0)]],
    sampler samp [[sampler(0)]])
{
    float4 c = backbuffer.sample(samp, in.uv);
    return float4(c.rgb, 1.0f);
}

// ---------------------------------------------------------------------------
// Fixed-Function Direct3D 9 Fragment Shader
// ---------------------------------------------------------------------------
fragment float4 ps_mbaa_fixed(
    VertexOut in [[stage_in]],
    constant MbaaDrawUniforms& u [[buffer(MBAA_BUF_DRAW_UNIFORMS)]],
    texture2d<float> tex0 [[texture(MBAA_TEX_STAGE0)]],
    sampler samp0 [[sampler(0)]])
{
    float4 base;
    if (u.has_texture != 0u) {
        float4 t = tex0.sample(samp0, in.texcoord0);
        // D3DTOP_SELECTARG1 (2) vs D3DTOP_MODULATE (4) vs D3DTOP_ADD (7)
        if (u.color_op0 == 2u) {
            base.rgb = t.rgb;
        } else if (u.color_op0 == 7u) {
            base.rgb = saturate(t.rgb + in.diffuse.rgb);
        } else {
            base.rgb = t.rgb * in.diffuse.rgb;
        }
        if (u.alpha_op0 == 2u) {
            base.a = t.a;
        } else {
            base.a = t.a * in.diffuse.a;
        }
    } else {
        base = in.diffuse;
    }

    base.rgb = saturate(base.rgb + in.specular.rgb);

    if (u.alpha_test_enable != 0u) {
        if (!dx9_alpha_test_pass(base.a, u.alpha_func, u.alpha_ref)) {
            discard_fragment();
        }
    }
    return base;
}

// ---------------------------------------------------------------------------
// 1. sh_bloom_sakura.cfx
//    Techniques: TecSakuraBloom, TecSakuraBloom_Ready, TecSakuraBloom_Update (P0/P1)
// ---------------------------------------------------------------------------
fragment FragOut2 ps_sakura_bloom(
    VertexOut in [[stage_in]],
    texture2d<float> tex0 [[texture(MBAA_TEX_STAGE0)]],
    sampler samp0 [[sampler(0)]])
{
    float4 output = tex0.sample(samp0, in.texcoord0) * in.diffuse + in.specular;
    FragOut2 out;
    out.c0 = output;
    out.c1 = output;
    return out;
}

fragment FragOut3 ps_sakura_bloom_ready(VertexOut in [[stage_in]]) {
    FragOut3 out;
    out.c0 = float4(0.0f, 0.0f, 0.0f, 0.0f);
    out.c1 = float4(0.0f, 0.0f, 0.0f, 1.0f);
    out.c2 = float4(0.0f, 0.0f, 0.0f, 1.0f);
    return out;
}

inline float4 sakura_9tap_gaussian(
    float2 uv,
    float2 texel,
    float4 color,
    float4 specular,
    texture2d<float> tex,
    sampler samp)
{
    float4 acc = float4(0.0f);
    acc += tex.sample(samp, uv + texel *  4.0f) * 0.05f;
    acc += tex.sample(samp, uv + texel *  3.0f) * 0.075f;
    acc += tex.sample(samp, uv + texel *  2.0f) * 0.10f;
    acc += tex.sample(samp, uv + texel *  1.0f) * 0.15f;
    acc += tex.sample(samp, uv)                  * 0.25f;
    acc += tex.sample(samp, uv + texel * -1.0f) * 0.15f;
    acc += tex.sample(samp, uv + texel * -2.0f) * 0.10f;
    acc += tex.sample(samp, uv + texel * -3.0f) * 0.075f;
    acc += tex.sample(samp, uv + texel * -4.0f) * 0.05f;
    return acc * color + specular;
}

fragment FragOut3 ps_sakura_bloom_update0(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> tex_target0 [[texture(MBAA_TEX_STAGE0)]],
    sampler samp0 [[sampler(0)]])
{
    FragOut3 out;
    out.c0 = float4(0.0f);
    out.c1 = float4(0.0f);
    out.c2 = sakura_9tap_gaussian(
        in.texcoord0, fx.bloom_texelA.xy, in.diffuse, in.specular, tex_target0, samp0);
    return out;
}

fragment FragOut2 ps_sakura_bloom_update1(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> tex_target1 [[texture(MBAA_TEX_STAGE0)]],
    sampler samp0 [[sampler(0)]])
{
    FragOut2 out;
    out.c0 = float4(0.0f);
    out.c1 = sakura_9tap_gaussian(
        in.texcoord0, fx.bloom_texelB.xy, in.diffuse, in.specular, tex_target1, samp0);
    return out;
}

// ---------------------------------------------------------------------------
// 2. sh_blur.cfx (BgPointBlur Pass 0 & Pass 1)
// ---------------------------------------------------------------------------
fragment FragOut3 ps_blur_p0(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> diffuse_tex [[texture(MBAA_TEX_STAGE0)]],
    sampler samp0 [[sampler(0)]])
{
    float2 uv = in.texcoord0 * fx.diff_wh.xy + fx.diff_uv.xy;
    float2 center = 0.5f * fx.diff_wh.xy;
    float2 delta = center - uv;
    float inv_len = rsqrt(max(dot(delta, delta), 1e-8f));
    float2 dir = delta * inv_len * (fx.power_vec.x * 0.2f); // fPower * 0.2

    const float weights[8] = {
        0.244f, 0.189f, 0.162f, 0.135f, 0.108f, 0.081f, 0.054f, 0.027f
    };

    float4 blur_sum = float4(0.0f);
    for (int k = 1; k <= 8; ++k) {
        blur_sum += diffuse_tex.sample(samp0, uv + dir * float(k)) * weights[k - 1];
    }

    float color_scale = fx.scalar_params.z * fx.scalar_params.x + 1.0f; // 1 + fColorHosei * fValue
    float4 center_sample = diffuse_tex.sample(samp0, uv);

    FragOut3 out;
    out.c0 = float4(0.0f);
    out.c1 = blur_sum * color_scale;
    out.c2 = center_sample * color_scale;
    return out;
}

fragment float4 ps_blur_p1(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> tex_temp0  [[texture(MBAA_TEX_STAGE0)]],
    texture2d<float> tex_temp1  [[texture(MBAA_TEX_STAGE1)]],
    texture2d<float> tex_normal [[texture(MBAA_TEX_STAGE2)]],
    sampler samp0 [[sampler(0)]],
    sampler samp1 [[sampler(1)]],
    sampler samp2 [[sampler(2)]])
{
    float4 n = tex_normal.sample(samp2, in.texcoord0);
    float2 uv = in.texcoord0 * fx.diff_wh.xy + fx.diff_uv.xy;
    float2 delta = fx.diff_centeruv.xy - uv;
    float inv_len = rsqrt(max(dot(delta, delta), 1e-8f));
    float2 offset_uv = uv + (delta * inv_len) * n.x * fx.power_vec.x * 3.0f;

    float4 c_orig = tex_temp1.sample(samp1, uv);
    float4 c_blur = tex_temp0.sample(samp0, offset_uv) * in.diffuse + in.specular;

    float fval = fx.scalar_params.x;
    float avg_blur = (c_blur.r + c_blur.g + c_blur.b) * (1.0f / 3.0f);
    float3 blur_desat = mix(c_blur.rgb, (c_blur.rgb + float3(avg_blur)) * 0.5f, fval);

    float avg_orig = (c_orig.r + c_orig.g + c_orig.b) * (1.0f / 3.0f);
    float3 orig_desat = mix(c_orig.rgb, (c_orig.rgb + float3(avg_orig)) * 0.5f, fval);

    float blend_w = n.x * c_blur.a;
    float3 final_rgb = mix(orig_desat, blur_desat, blend_w);
    return float4(final_rgb, 1.0f);
}

// ---------------------------------------------------------------------------
// 3. sh_chara.cfx (TecCharaDraw, TecCharaDrawEx, TecCharaDraw_Edge)
// ---------------------------------------------------------------------------
fragment float4 ps_chara_draw(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> tex0 [[texture(MBAA_TEX_STAGE0)]],
    sampler samp0 [[sampler(0)]])
{
    float2 uv = in.texcoord0;
    float2 tx = fx.texel_xy_n.xy;
    float4 c  = tex0.sample(samp0, uv);
    float4 up = tex0.sample(samp0, uv + float2( 0.0f,  tx.y));
    float4 lf = tex0.sample(samp0, uv + float2(-tx.x,  0.0f));
    float4 rt = tex0.sample(samp0, uv + float2( tx.x,  0.0f));
    float4 dn = tex0.sample(samp0, uv + float2( 0.0f, -tx.y));

    float4 accum = float4(0.0f);
    float  count = 0.0f;
    if (rt.a != 0.0f) { accum += rt; count += 1.0f; }
    if (lf.a != 0.0f) { accum += lf; count += 1.0f; }
    if (up.a != 0.0f) { accum += up; count += 1.0f; }
    if (dn.a != 0.0f) { accum += dn; count += 1.0f; }

    float4 edge_col = (count == 1.0f) ? fx.edge_color : accum;
    float4 blended  = (count >= 1.0f) ? edge_col : float4(accum.rgb / max(count, 1.0f), 1.0f);
    if (count > 1.0f) {
        blended = float4(accum.rgb / count, 1.0f);
    }

    float out_a = (count >= 1.0f && count <= 1.0f) ? c.a : ((count == 0.0f) ? c.a : 1.0f / count);
    float4 res = (c.a == 0.0f) ? float4(blended.rgb, blended.a) : float4(c.rgb, out_a);
    return res * in.diffuse + in.specular;
}

fragment float4 ps_chara_draw_ex(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> tex0 [[texture(MBAA_TEX_STAGE0)]],
    sampler samp0 [[sampler(0)]])
{
    float2 uv = in.texcoord0;
    float2 tx = fx.texel_xy_n.xy;
    float4 rt = tex0.sample(samp0, uv + float2( tx.x,  0.0f));
    float4 up = tex0.sample(samp0, uv + float2( 0.0f,  tx.y));
    float4 dn = tex0.sample(samp0, uv + float2( 0.0f, -tx.y));
    float4 lf = tex0.sample(samp0, uv + float2(-tx.x,  0.0f));
    float4 c  = tex0.sample(samp0, uv);

    // Pairwise similarity blend matching sh_chara.cfx ps_3_0
    float4 pair_sum = float4(0.0f);
    float  pair_cnt = 0.0f;
    if (dot(rt - dn, rt - dn) == 0.0f) { pair_sum += dn; pair_cnt += 1.0f; }
    if (dot(rt - up, rt - up) == 0.0f) { pair_sum += rt; pair_cnt += 1.0f; }
    if (dot(up - lf, up - lf) == 0.0f) { pair_sum += up; pair_cnt += 1.0f; }
    if (dot(lf - dn, lf - dn) == 0.0f) { pair_sum += lf; pair_cnt += 1.0f; }

    float4 smooth_c = (pair_cnt > 0.0f) ? (pair_sum / pair_cnt) : ((rt + dn + up + lf + c) * 0.2f);
    float4 interior = (pair_cnt >= 4.0f) ? c : smooth_c;

    float nz_a = (abs(dn.a) > 0.0f ? 1.0f : 0.0f) + (abs(rt.a) > 0.0f ? 1.0f : 0.0f) +
                 (abs(up.a) > 0.0f ? 1.0f : 0.0f) + (abs(lf.a) > 0.0f ? 1.0f : 0.0f);
    if (nz_a > 1.0f) {
        interior = float4(c.rgb, 1.0f / nz_a);
    }

    float4 edge_acc = float4(0.0f);
    float  edge_cnt = 0.0f;
    if (abs(rt.a) > 0.0f) { edge_acc += rt; edge_cnt += 1.0f; }
    if (abs(lf.a) > 0.0f) { edge_acc += lf; edge_cnt += 1.0f; }
    if (abs(up.a) > 0.0f) { edge_acc += up; edge_cnt += 1.0f; }
    if (abs(dn.a) > 0.0f) { edge_acc += dn; edge_cnt += 1.0f; }

    float4 empty_col = (edge_cnt == 1.0f) ? fx.edge_color
                                          : float4(edge_acc.rgb / max(edge_cnt, 1.0f), 1.0f);
    float4 final_c = (abs(c.a) == 0.0f) ? ((edge_cnt == 0.0f) ? float4(0.0f) : empty_col) : interior;
    return final_c * in.diffuse + in.specular;
}

fragment float4 ps_chara_draw_edge(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> tex0 [[texture(MBAA_TEX_STAGE0)]],
    sampler samp0 [[sampler(0)]])
{
    float2 uv = in.texcoord0;
    float2 tx = fx.texel_xy_n.xy;
    float  c_a  = tex0.sample(samp0, uv).a;
    float  lf_a = tex0.sample(samp0, uv + float2(-tx.x,  0.0f)).a;
    float  rt_a = tex0.sample(samp0, uv + float2( tx.x,  0.0f)).a;
    float  up_a = tex0.sample(samp0, uv + float2( 0.0f,  tx.y)).a;
    float  dn_a = tex0.sample(samp0, uv + float2( 0.0f, -tx.y)).a;

    float cnt = (lf_a != 0.0f ? 1.0f : 0.0f) + (rt_a != 0.0f ? 1.0f : 0.0f) +
                (up_a != 0.0f ? 1.0f : 0.0f) + (dn_a != 0.0f ? 1.0f : 0.0f);
    bool is_edge = (c_a == 0.0f) && (cnt == 1.0f);
    return is_edge ? (fx.edge_color * in.diffuse + in.specular) : float4(0.0f);
}

// ---------------------------------------------------------------------------
// 4. sh_fade.cfx (TecFade_ExFade0, TecFade_ExFade1)
// ---------------------------------------------------------------------------
fragment float4 ps_fade_ex(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> tex_empty [[texture(MBAA_TEX_STAGE0)]],
    texture2d<float> tex_fade  [[texture(MBAA_TEX_STAGE1)]],
    sampler samp0 [[sampler(0)]],
    sampler samp1 [[sampler(1)]])
{
    float4 mask_c = tex_fade.sample(samp1, in.texcoord0);
    float4 src_c  = tex_empty.sample(samp0, in.texcoord0);

    // Preshader from sh_fade.cfx PRES:
    //   t = max(2.0 * (1.0 - fPower), 0.0)
    //   c0.x = 1.0 - min(t, 1.0)
    //   c1.x = min(max(t - 1.0, 0.0), 1.0)
    float fpower = fx.power_vec.x;
    float t = max(2.0f * (1.0f - fpower), 0.0f);
    float c0x = 1.0f - min(t, 1.0f);
    float c1x = min(max(t - 1.0f, 0.0f), 1.0f);

    float alpha = saturate(max(mask_c.r - c0x, 0.0f) + c1x);
    float3 rgb  = src_c.rgb * in.diffuse.rgb + in.specular.rgb;
    return float4(rgb, alpha);
}

// ---------------------------------------------------------------------------
// 5. sh_gaugedraw.cfx (TecMagicCircuitDraw)
// ---------------------------------------------------------------------------
fragment float4 ps_magic_circuit_draw(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> tex0 [[texture(MBAA_TEX_STAGE0)]],
    sampler samp0 [[sampler(0)]])
{
    float4 base = tex0.sample(samp0, in.texcoord0) * in.diffuse + in.specular;
    float fvalue = fx.scalar_params.x;
    float fsu    = fx.scalar_params.w;
    float fwidth = (fx.gauge_params.x != 0.0f) ? fx.gauge_params.x : 1.0f;
    float fcolor = fx.gauge_params.y;

    float d  = abs((in.texcoord0.x - fsu) / fwidth - fvalue);
    float d2 = abs(d - 1.0f);
    float sel_d = (d >= 0.35f) ? d2 : d;
    bool in_band = (d < 0.35f) || (d2 < 0.35f);

    float w = 1.0f - sel_d * 2.85714f;
    float3 rgb = in_band ? mix(base.rgb, float3(fcolor), w) : base.rgb;
    return float4(rgb, base.a);
}

// ---------------------------------------------------------------------------
// 6. sh_mono.cfx (TecMono, TecMonoFill, TecBloom_Make, TecBloom_Fill, TecBloom_Blt)
// ---------------------------------------------------------------------------
fragment float4 ps_mono(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> tex0 [[texture(MBAA_TEX_STAGE0)]],
    sampler samp0 [[sampler(0)]])
{
    float4 c = tex0.sample(samp0, in.texcoord0) * in.diffuse + in.specular;
    float avg = (c.r + c.g + c.b) * (1.0f / 3.0f);
    float3 rgb = avg + (c.rgb - avg) * fx.power_vec.rgb;
    return float4(rgb, c.a);
}

fragment FragOut3 ps_mono_bloom_make0(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> diffuse_tex [[texture(MBAA_TEX_STAGE0)]],
    sampler samp0 [[sampler(0)]])
{
    float step_x = fx.scalar_params.x * fx.diff_texel.x * fx.scalar_params.y; // fValue * diff_texel.x * fShift
    float max_x  = fx.diff_wh.x - 0.5f * fx.diff_texel.x;
    float2 base  = in.texcoord0 * fx.diff_wh.xy;
    float  x0    = base.x - 3.0f * step_x;
    float  y     = base.y + fx.diff_uv.y;

    float4 sum = float4(0.0f);
    for (int k = 0; k < 7; ++k) {
        float sx = min(max_x, max(x0 + float(k) * step_x, 0.0f)) + fx.diff_uv.x;
        sum += diffuse_tex.sample(samp0, float2(sx, y));
    }

    FragOut3 out;
    out.c0 = float4(0.0f);
    out.c1 = sum * (1.0f / 7.0f);
    out.c2 = float4(0.0f);
    return out;
}

fragment FragOut3 ps_mono_bloom_make1(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> tex_tempA [[texture(MBAA_TEX_STAGE0)]],
    sampler samp0 [[sampler(0)]])
{
    float step_y = fx.scalar_params.x * fx.diff_texel.y * fx.scalar_params.y;
    float max_y  = fx.diff_wh.y - 0.5f * fx.diff_texel.y;
    float2 base  = in.texcoord0 * fx.diff_wh.xy;
    float  y0    = base.y - 3.0f * step_y;
    float  x     = base.x + fx.diff_uv.x;

    float4 sum = float4(0.0f);
    for (int k = 0; k < 7; ++k) {
        float sy = min(max_y, max(y0 + float(k) * step_y, 0.0f)) + fx.diff_uv.y;
        sum += tex_tempA.sample(samp0, float2(x, sy));
    }

    FragOut3 out;
    out.c0 = float4(0.0f);
    out.c1 = float4(0.0f);
    out.c2 = sum * (1.0f / 7.0f);
    return out;
}

fragment FragOut3 ps_mono_bloom_fill(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> tex_tempB [[texture(MBAA_TEX_STAGE0)]],
    sampler samp0 [[sampler(0)]])
{
    float2 uv = in.texcoord0 * fx.diff_wh.xy + fx.diff_uv.xy;
    FragOut3 out;
    out.c0 = tex_tempB.sample(samp0, uv) * in.diffuse + in.specular;
    out.c1 = float4(0.0f);
    out.c2 = float4(0.0f);
    return out;
}

fragment FragOut3 ps_mono_bloom_blt(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> tex_tempB [[texture(MBAA_TEX_STAGE0)]],
    texture2d<float> tex_src   [[texture(MBAA_TEX_STAGE1)]],
    sampler samp0 [[sampler(0)]],
    sampler samp1 [[sampler(1)]])
{
    float2 uv_b = in.texcoord0 * fx.diff_wh.xy + fx.diff_uv.xy;
    float2 uv_s = in.texcoord0 * fx.src_wh.xy  + fx.src_uv.xy;
    float4 b = tex_tempB.sample(samp0, uv_b);
    float4 s = tex_src.sample(samp1, uv_s);

    float w = s.a * fx.scalar_params.x; // fValue
    float3 rgb = mix(b.rgb, s.rgb, w);
    float  a   = (s.a != 0.0f) ? 1.0f : 0.0f;

    FragOut3 out;
    out.c0 = float4(rgb, a) * in.diffuse + in.specular;
    out.c1 = float4(0.0f);
    out.c2 = float4(0.0f);
    return out;
}

// ---------------------------------------------------------------------------
// 7. sh_noise.cfx (TecNoise Pass 0 & Pass 1)
// ---------------------------------------------------------------------------
fragment FragOut2 ps_noise_p0(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> diffuse_tex [[texture(MBAA_TEX_STAGE0)]],
    texture2d<float> noise_tex   [[texture(MBAA_TEX_STAGE1)]],
    sampler samp0 [[sampler(0)]],
    sampler samp1 [[sampler(1)]])
{
    float noise = noise_tex.sample(samp1, float2(0.0f, in.texcoord0.y)).r * 2.0f - 1.0f;
    float2 uv   = in.texcoord0 * fx.diff_wh.xy + fx.diff_uv.xy;
    float shift = fx.scalar_params.x * fx.diff_uv.x * fx.power_vec.x; // fValue * diff_uv.x * fPower
    float shifted_x = uv.x + noise * shift;
    float wrapped_x = (shifted_x >= fx.scalar_params.x) ? (shifted_x - fx.scalar_params.x) : shifted_x;

    FragOut2 out;
    out.c0 = float4(0.0f);
    out.c1 = diffuse_tex.sample(samp0, float2(wrapped_x, uv.y));
    return out;
}

fragment float4 ps_noise_p1(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> tex_temp [[texture(MBAA_TEX_STAGE0)]],
    sampler samp0 [[sampler(0)]])
{
    float2 uv = in.texcoord0 * fx.diff_wh.xy + fx.diff_uv.xy;
    return tex_temp.sample(samp0, uv) * in.diffuse + in.specular;
}

// ---------------------------------------------------------------------------
// 8. sh_normal.cfx (TecNormal P0/P1, TecNormalAngle P0/P1)
// ---------------------------------------------------------------------------
fragment FragOut2 ps_normal_p0(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> normal_tex  [[texture(MBAA_TEX_STAGE0)]],
    texture2d<float> diffuse_tex [[texture(MBAA_TEX_STAGE1)]],
    sampler samp0 [[sampler(0)]],
    sampler samp1 [[sampler(1)]])
{
    float3 n3 = normal_tex.sample(samp0, in.texcoord0).xyz * 2.0f - 1.0f;
    float2 n_dir = n3.xy * rsqrt(max(dot(n3, n3), 1e-8f));
    float2 disp  = n_dir * float2(-1.0f, 1.0f) * fx.diff_texel.xy * fx.power_vec.x;
    float2 uv    = clamp(in.texcoord0 * fx.diff_wh.xy + fx.diff_uv.xy + disp,
                         float2(0.0f), fx.diff_size.xy);

    FragOut2 out;
    out.c0 = float4(0.0f);
    out.c1 = diffuse_tex.sample(samp1, uv);
    return out;
}

fragment float4 ps_normal_p1(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> tex_temp   [[texture(MBAA_TEX_STAGE0)]],
    texture2d<float> normal_tex [[texture(MBAA_TEX_STAGE1)]],
    sampler samp0 [[sampler(0)]],
    sampler samp1 [[sampler(1)]])
{
    float4 n  = normal_tex.sample(samp1, in.texcoord0);
    float2 uv = in.texcoord0 * fx.diff_wh.xy + fx.diff_uv.xy;
    float4 t  = tex_temp.sample(samp0, uv) * in.diffuse + in.specular;
    return float4(t.rgb, t.a * n.a);
}

fragment FragOut2 ps_normal_angle_p0(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> normal_tex  [[texture(MBAA_TEX_STAGE0)]],
    texture2d<float> diffuse_tex [[texture(MBAA_TEX_STAGE1)]],
    sampler samp0 [[sampler(0)]],
    sampler samp1 [[sampler(1)]])
{
    float3 n3 = normal_tex.sample(samp0, in.texcoord0).xyz * 2.0f - 1.0f;
    float2 n_dir = n3.xy * rsqrt(max(dot(n3, n3), 1e-8f));
    float2 disp  = n_dir * float2(-1.0f, 1.0f) * fx.diff_texel.xy * fx.power_vec.x + in.texcoord0;
    float2 rot_uv = float2(
        dot(disp, fx.diff_texel_matrix0.xy),
        dot(disp, fx.diff_texel_matrix1.xy)
    ) + fx.diff_uv.xy;
    float2 uv = clamp(rot_uv, float2(0.0f), fx.diff_size.xy);

    FragOut2 out;
    out.c0 = float4(0.0f);
    out.c1 = diffuse_tex.sample(samp1, uv);
    return out;
}

fragment float4 ps_normal_angle_p1(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> tex_temp   [[texture(MBAA_TEX_STAGE0)]],
    texture2d<float> normal_tex [[texture(MBAA_TEX_STAGE1)]],
    sampler samp0 [[sampler(0)]],
    sampler samp1 [[sampler(1)]])
{
    float4 n = normal_tex.sample(samp1, in.texcoord0);
    float2 uv = float2(
        dot(in.texcoord0, fx.diff_texel_matrix0.xy),
        dot(in.texcoord0, fx.diff_texel_matrix1.xy)
    ) + fx.diff_uv.xy;
    float4 t = tex_temp.sample(samp0, uv) * in.diffuse + in.specular;
    return float4(t.rgb, t.a * n.a);
}

// ---------------------------------------------------------------------------
// 9. vsfx.cfx (TransformTec, TecFilterColorCut, TecFilter12Sample, TecBloom)
// ---------------------------------------------------------------------------
fragment float4 ps_vsfx_transform(
    VertexOut in [[stage_in]],
    texture2d<float> tex0 [[texture(MBAA_TEX_STAGE0)]],
    sampler samp0 [[sampler(0)]])
{
    return tex0.sample(samp0, in.texcoord0) * in.diffuse + in.specular;
}

fragment float4 ps_vsfx_filter_color_cut(
    VertexOut in [[stage_in]],
    texture2d<float> tex0 [[texture(MBAA_TEX_STAGE0)]],
    sampler samp0 [[sampler(0)]])
{
    float4 c = tex0.sample(samp0, in.texcoord0) * in.diffuse + in.specular;
    float peak = max(max(c.r, c.g), c.b);
    return (peak >= 0.5f) ? c : float4(0.0f, 0.0f, 0.0f, 1.0f);
}

fragment float4 ps_vsfx_filter_12sample(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> tex0 [[texture(MBAA_TEX_STAGE0)]],
    sampler samp0 [[sampler(0)]])
{
    float2 uv = in.texcoord0;
    float2 tx = fx.g_texel.xy;
    float4 acc = tex0.sample(samp0, uv);
    acc += tex0.sample(samp0, uv + float2( tx.x,        0.0f));
    acc += tex0.sample(samp0, uv + float2(-tx.x,        0.0f));
    acc += tex0.sample(samp0, uv + float2( 2.0f * tx.x, 0.0f));
    acc += tex0.sample(samp0, uv + float2(-2.0f * tx.x, 0.0f));
    acc += tex0.sample(samp0, uv + float2( 0.0f,        tx.y));
    acc += tex0.sample(samp0, uv + float2( 0.0f,       -tx.y));
    acc += tex0.sample(samp0, uv + float2( 0.0f,        2.0f * tx.y));
    acc += tex0.sample(samp0, uv + float2( 0.0f,       -2.0f * tx.y));
    acc += tex0.sample(samp0, uv + float2( tx.x,        tx.y));
    acc += tex0.sample(samp0, uv + float2(-tx.x,        tx.y));
    acc += tex0.sample(samp0, uv + float2( tx.x,       -tx.y));
    acc += tex0.sample(samp0, uv + float2(-tx.x,       -tx.y));
    return (acc * in.diffuse) * (1.0f / 13.0f) + in.specular;
}

fragment float4 ps_vsfx_bloom(
    VertexOut in [[stage_in]],
    constant MbaaEffectUniforms& fx [[buffer(MBAA_BUF_EFFECT_UNIFORMS)]],
    texture2d<float> tex0 [[texture(MBAA_TEX_STAGE0)]],
    sampler samp0 [[sampler(0)]])
{
    float4 acc = float4(0.0f);
    for (int i = 0; i < 15; ++i) {
        acc += fx.tex_weight[i] * tex0.sample(samp0, in.texcoord0 + fx.tex_off[i].xy);
    }
    return acc;
}
