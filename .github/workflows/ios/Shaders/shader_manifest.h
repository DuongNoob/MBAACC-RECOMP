#pragma once

/**
 * @file shader_manifest.h
 * @brief Shared C++20 / Apple Metal 2.4 vertex layout, uniform buffers, and technique manifest
 *        covering fixed-function DX9 sprite/UI rendering and all 9 MBAACC .cfx effects
 *        (22 techniques / 28 passes from 0006.p).
 */

#ifdef __METAL_VERSION__
#include <metal_stdlib>
using namespace metal;
#define MBAA_ALIGN16
typedef float4 mbaa_float4;
typedef float2 mbaa_float2;
typedef uint   mbaa_uint;
typedef int    mbaa_int;
#else
#include <cstdint>
#include <cstring>
#define MBAA_ALIGN16 alignas(16)
struct MBAA_ALIGN16 mbaa_float4 { float x, y, z, w; };
struct mbaa_float2 { float x, y; };
typedef uint32_t mbaa_uint;
typedef int32_t  mbaa_int;
#endif

// ---------------------------------------------------------------------------
// Metal Buffer & Texture Slot Assignments
// ---------------------------------------------------------------------------
#define MBAA_BUF_VERTICES        0
#define MBAA_BUF_DRAW_UNIFORMS   1
#define MBAA_BUF_EFFECT_UNIFORMS 2

#define MBAA_TEX_STAGE0          0
#define MBAA_TEX_STAGE1          1
#define MBAA_TEX_STAGE2          2
#define MBAA_TEX_STAGE3          3

// ---------------------------------------------------------------------------
// Unified Vertex Layout (decoded from D3DFVF 0x1c4 / 0x1c2 / 0x112 / 0x8c4)
// ---------------------------------------------------------------------------
struct MBAA_ALIGN16 MbaaMetalVertex {
    mbaa_float4 position;   // [[attribute(0)]] Screen pixels (XYZRHW) or World XYZ
    mbaa_float4 diffuse;    // [[attribute(1)]] COLOR0 RGBA linear 0..1
    mbaa_float4 specular;   // [[attribute(2)]] COLOR1 RGBA linear 0..1
    mbaa_float2 texcoord0;  // [[attribute(3)]] TEXCOORD0
    mbaa_float2 texcoord1;  // [[attribute(4)]] TEXCOORD1
};

// ---------------------------------------------------------------------------
// Fixed-Function / Vertex Transform Uniforms
// ---------------------------------------------------------------------------
struct MBAA_ALIGN16 MbaaDrawUniforms {
    mbaa_float4 world_view_proj[4]; // Row-major 4x4 matrix (used when is_transformed == 0)
    mbaa_float4 viewport_inv;       // (2/vpW, -2/vpH, vpX, vpY) for XYZRHW -> Metal NDC
    mbaa_uint   is_transformed;     // 1 = D3DFVF_XYZRHW screen space, 0 = 3D World*View*Proj
    mbaa_uint   has_texture;        // 1 = sample MBAA_TEX_STAGE0, 0 = vertex color only
    mbaa_uint   alpha_test_enable;  // D3DRS_ALPHATESTENABLE
    mbaa_uint   alpha_func;         // D3DCMPFUNC (1=Never..8=Always)
    float       alpha_ref;          // Normalized 0..1 (D3DRS_ALPHAREF / 255.0)
    mbaa_uint   color_op0;          // D3DTSS_COLOROP (stage 0)
    mbaa_uint   alpha_op0;          // D3DTSS_ALPHAOP (stage 0)
    float       _pad0;
    mbaa_float4 texture_factor;     // D3DRS_TEXTUREFACTOR RGBA
};

// ---------------------------------------------------------------------------
// .cfx Effect Parameter Uniforms (covers all 9 .cfx files)
// ---------------------------------------------------------------------------
struct MBAA_ALIGN16 MbaaEffectUniforms {
    // 16 float4 general register slots matching c0..c15 / named parameters
    mbaa_float4 bloom_texelA;       // sh_bloom_sakura
    mbaa_float4 bloom_texelB;       // sh_bloom_sakura
    mbaa_float4 diff_uv;            // sh_blur, sh_mono, sh_noise, sh_normal (.xy)
    mbaa_float4 diff_wh;            // sh_blur, sh_mono, sh_noise, sh_normal (.xy)
    mbaa_float4 diff_texel;         // sh_blur, sh_mono, sh_normal (.xy)
    mbaa_float4 diff_centeruv;      // sh_blur (.xy)
    mbaa_float4 diff_size;          // sh_normal (.xy)
    mbaa_float4 src_uv;             // sh_mono (.xy)
    mbaa_float4 src_wh;             // sh_mono (.xy)
    mbaa_float4 diff_texel_matrix0; // sh_normal row 0 (.xy)
    mbaa_float4 diff_texel_matrix1; // sh_normal row 1 (.xy)
    mbaa_float4 texel_xy_n;         // sh_chara: (fTexelX.xy, fTexelN.xy)
    mbaa_float4 edge_color;         // sh_chara: fEdgeColor
    mbaa_float4 power_vec;          // sh_mono fPower (float4) or scalar fPower in .x
    mbaa_float4 scalar_params;      // .x=fValue, .y=fShift, .z=fColorHosei, .w=fSU
    mbaa_float4 gauge_params;       // .x=fWidth, .y=fColor, .z=fUVSample, .w=reserved
    mbaa_float4 g_texel;            // vsfx: g_fTexel (.xy), sh_chara fRollTexel (.zw)
    mbaa_float4 tex_off[15];        // vsfx TecBloom fTexOff[15] (.xy)
    mbaa_float4 tex_weight[15];     // vsfx TecBloom fTexWeight[15] (.xyzw)
};

// ---------------------------------------------------------------------------
// All 9 .cfx Effect IDs + Fixed-Function & Present Pipelines
// ---------------------------------------------------------------------------
enum MbaaShaderPassId : mbaa_uint {
    MBAA_PASS_FIXED_2D = 0,
    MBAA_PASS_PRESENT_BLIT,
    // sh_bloom_sakura.cfx
    MBAA_PASS_SAKURA_BLOOM,
    MBAA_PASS_SAKURA_BLOOM_READY,
    MBAA_PASS_SAKURA_BLOOM_UPDATE_P0,
    MBAA_PASS_SAKURA_BLOOM_UPDATE_P1,
    // sh_blur.cfx
    MBAA_PASS_BG_POINT_BLUR_P0,
    MBAA_PASS_BG_POINT_BLUR_P1,
    // sh_chara.cfx
    MBAA_PASS_CHARA_DRAW,
    MBAA_PASS_CHARA_DRAW_EX,
    MBAA_PASS_CHARA_DRAW_EDGE,
    // sh_fade.cfx
    MBAA_PASS_FADE_EX0,
    MBAA_PASS_FADE_EX1,
    // sh_gaugedraw.cfx
    MBAA_PASS_MAGIC_CIRCUIT_DRAW,
    // sh_mono.cfx
    MBAA_PASS_BLOOM_BLT,
    MBAA_PASS_BLOOM_FILL,
    MBAA_PASS_BLOOM_MAKE_P0,
    MBAA_PASS_BLOOM_MAKE_P1,
    MBAA_PASS_MONO,
    MBAA_PASS_MONO_FILL,
    // sh_noise.cfx
    MBAA_PASS_NOISE_P0,
    MBAA_PASS_NOISE_P1,
    // sh_normal.cfx
    MBAA_PASS_NORMAL_P0,
    MBAA_PASS_NORMAL_P1,
    MBAA_PASS_NORMAL_ANGLE_P0,
    MBAA_PASS_NORMAL_ANGLE_P1,
    // vsfx.cfx
    MBAA_PASS_VSFX_TRANSFORM,
    MBAA_PASS_VSFX_FILTER_COLOR_CUT,
    MBAA_PASS_VSFX_FILTER_12_SAMPLE,
    MBAA_PASS_VSFX_BLOOM,

    MBAA_PASS_COUNT
};

#ifndef __METAL_VERSION__

namespace mbaa_recomp::shader_manifest {

struct TechniquePassEntry {
    const char*      effect_file;
    const char*      technique_name;
    uint32_t         pass_index;
    MbaaShaderPassId pass_id;
    const char*      vertex_fn;
    const char*      fragment_fn;
    uint32_t         mrt_count;
};

inline constexpr TechniquePassEntry kTechniquePasses[] = {
    { nullptr,               nullptr,                0, MBAA_PASS_FIXED_2D,              "vs_mbaa_main",      "ps_mbaa_fixed",            1 },
    { nullptr,               nullptr,                0, MBAA_PASS_PRESENT_BLIT,          "vs_present_quad",   "ps_present_blit",          1 },
    // sh_bloom_sakura.cfx (3 techniques, 4 passes)
    { "sh_bloom_sakura.cfx", "TecSakuraBloom",       0, MBAA_PASS_SAKURA_BLOOM,          "vs_mbaa_main",      "ps_sakura_bloom",          2 },
    { "sh_bloom_sakura.cfx", "TecSakuraBloom_Ready", 0, MBAA_PASS_SAKURA_BLOOM_READY,    "vs_mbaa_main",      "ps_sakura_bloom_ready",    3 },
    { "sh_bloom_sakura.cfx", "TecSakuraBloom_Update",0, MBAA_PASS_SAKURA_BLOOM_UPDATE_P0,"vs_mbaa_main",      "ps_sakura_bloom_update0",  3 },
    { "sh_bloom_sakura.cfx", "TecSakuraBloom_Update",1, MBAA_PASS_SAKURA_BLOOM_UPDATE_P1,"vs_mbaa_main",      "ps_sakura_bloom_update1",  2 },
    // sh_blur.cfx (1 technique, 2 passes)
    { "sh_blur.cfx",         "BgPointBlur",          0, MBAA_PASS_BG_POINT_BLUR_P0,      "vs_mbaa_main",      "ps_blur_p0",               3 },
    { "sh_blur.cfx",         "BgPointBlur",          1, MBAA_PASS_BG_POINT_BLUR_P1,      "vs_mbaa_main",      "ps_blur_p1",               1 },
    // sh_chara.cfx (3 techniques, 3 passes)
    { "sh_chara.cfx",        "TecCharaDraw",         0, MBAA_PASS_CHARA_DRAW,            "vs_mbaa_main",      "ps_chara_draw",            1 },
    { "sh_chara.cfx",        "TecCharaDrawEx",       0, MBAA_PASS_CHARA_DRAW_EX,         "vs_mbaa_main",      "ps_chara_draw_ex",         1 },
    { "sh_chara.cfx",        "TecCharaDraw_Edge",    0, MBAA_PASS_CHARA_DRAW_EDGE,       "vs_mbaa_main",      "ps_chara_draw_edge",       1 },
    // sh_fade.cfx (2 techniques, 2 passes)
    { "sh_fade.cfx",         "TecFade_ExFade0",      0, MBAA_PASS_FADE_EX0,              "vs_mbaa_main",      "ps_fade_ex",               1 },
    { "sh_fade.cfx",         "TecFade_ExFade1",      0, MBAA_PASS_FADE_EX1,              "vs_mbaa_main",      "ps_fade_ex",               1 },
    // sh_gaugedraw.cfx (1 technique, 1 pass)
    { "sh_gaugedraw.cfx",    "TecMagicCircuitDraw",  0, MBAA_PASS_MAGIC_CIRCUIT_DRAW,    "vs_mbaa_main",      "ps_magic_circuit_draw",    1 },
    // sh_mono.cfx (5 techniques, 6 passes)
    { "sh_mono.cfx",         "TecBloom_Blt",         0, MBAA_PASS_BLOOM_BLT,             "vs_mbaa_main",      "ps_mono_bloom_blt",        3 },
    { "sh_mono.cfx",         "TecBloom_Fill",        0, MBAA_PASS_BLOOM_FILL,            "vs_mbaa_main",      "ps_mono_bloom_fill",       3 },
    { "sh_mono.cfx",         "TecBloom_Make",        0, MBAA_PASS_BLOOM_MAKE_P0,         "vs_mbaa_main",      "ps_mono_bloom_make0",      3 },
    { "sh_mono.cfx",         "TecBloom_Make",        1, MBAA_PASS_BLOOM_MAKE_P1,         "vs_mbaa_main",      "ps_mono_bloom_make1",      3 },
    { "sh_mono.cfx",         "TecMono",              0, MBAA_PASS_MONO,                  "vs_mbaa_main",      "ps_mono",                  1 },
    { "sh_mono.cfx",         "TecMonoFill",          0, MBAA_PASS_MONO_FILL,             "vs_mbaa_main",      "ps_mono",                  1 },
    // sh_noise.cfx (1 technique, 2 passes)
    { "sh_noise.cfx",        "TecNoise",             0, MBAA_PASS_NOISE_P0,              "vs_mbaa_main",      "ps_noise_p0",              2 },
    { "sh_noise.cfx",        "TecNoise",             1, MBAA_PASS_NOISE_P1,              "vs_mbaa_main",      "ps_noise_p1",              1 },
    // sh_normal.cfx (2 techniques, 4 passes)
    { "sh_normal.cfx",       "TecNormal",            0, MBAA_PASS_NORMAL_P0,             "vs_mbaa_main",      "ps_normal_p0",             2 },
    { "sh_normal.cfx",       "TecNormal",            1, MBAA_PASS_NORMAL_P1,             "vs_mbaa_main",      "ps_normal_p1",             1 },
    { "sh_normal.cfx",       "TecNormalAngle",       0, MBAA_PASS_NORMAL_ANGLE_P0,       "vs_mbaa_main",      "ps_normal_angle_p0",       2 },
    { "sh_normal.cfx",       "TecNormalAngle",       1, MBAA_PASS_NORMAL_ANGLE_P1,       "vs_mbaa_main",      "ps_normal_angle_p1",       1 },
    // vsfx.cfx (4 techniques, 4 passes)
    { "vsfx.cfx",            "TransformTec",         0, MBAA_PASS_VSFX_TRANSFORM,        "vs_vsfx_transform", "ps_vsfx_transform",        1 },
    { "vsfx.cfx",            "TecFilterColorCut",    0, MBAA_PASS_VSFX_FILTER_COLOR_CUT, "vs_mbaa_main",      "ps_vsfx_filter_color_cut", 1 },
    { "vsfx.cfx",            "TecFilter12Sample",    0, MBAA_PASS_VSFX_FILTER_12_SAMPLE, "vs_mbaa_main",      "ps_vsfx_filter_12sample",  1 },
    { "vsfx.cfx",            "TecBloom",             0, MBAA_PASS_VSFX_BLOOM,            "vs_mbaa_main",      "ps_vsfx_bloom",            1 },
};

inline const TechniquePassEntry* find_technique_pass(const char* tech_name, uint32_t pass_index) noexcept {
    if (!tech_name) return nullptr;
    for (const auto& entry : kTechniquePasses) {
        if (entry.technique_name && std::strcmp(entry.technique_name, tech_name) == 0 && entry.pass_index == pass_index) {
            return &entry;
        }
    }
    return nullptr;
}

inline const TechniquePassEntry& entry_for_pass_id(MbaaShaderPassId id) noexcept {
    const uint32_t idx = static_cast<uint32_t>(id);
    if (idx < MBAA_PASS_COUNT) {
        return kTechniquePasses[idx];
    }
    return kTechniquePasses[0];
}

} // namespace mbaa_recomp::shader_manifest

#endif // !__METAL_VERSION__
