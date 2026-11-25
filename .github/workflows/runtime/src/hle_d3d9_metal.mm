/**
 * @file hle_d3d9_metal.mm
 * @brief Direct3D 9 / D3DX9_36 -> Apple Metal Objective-C++ HLE shim for mbaacc-recomp-ios.
 *
 * Implements:
 *   - Guest 32-bit COM vtables in GuestMemory for IDirect3D9, IDirect3DDevice9,
 *     IDirect3DTexture9, IDirect3DSurface9, ID3DXEffect, ID3DXFont.
 *   - All 23 D3D9 / D3DX9 IAT handlers (0x0051B398..0x0051B3F4).
 *   - Software DXT1-5 / DDS decode + CoreGraphics/UIKit PNG/BMP/TGA/JPG load into Metal.
 *   - 192 MiB LRU Metal texture cache with evict_on_memory_warning() (for iPhone SE 2020 3 GB RAM).
 *   - Centered 4:3 (1000x750) viewport inside 1334x750 60 Hz display.
 *   - Idempotent frame composition: begin_frame() / end_frame_and_present() compose cleanly
 *     with guest BeginScene() / EndScene() / Present() without double-presenting.
 */

#ifdef __APPLE__

#include "mbaa_recomp/d3d9_shim.h"
#include "mbaa_recomp/dispatch.h"
#include "shader_manifest.h"

#import <TargetConditionals.h>
#import <Foundation/Foundation.h>
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreText/CoreText.h>
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace mbaa_recomp {

namespace {

// ---------------------------------------------------------------------------
// Direct3D 9 Constants & HRESULT Codes
// ---------------------------------------------------------------------------
constexpr uint32_t kS_OK         = 0x00000000u;
constexpr uint32_t kE_FAIL       = 0x80004005u;
constexpr uint32_t kE_INVALIDARG = 0x80070057u;
constexpr uint32_t kE_NOTIMPL    = 0x80004001u;
constexpr uint32_t kD3DERR_INVALIDCALL = 0x8876086Cu;

constexpr uint32_t kKindD3D9    = 0x39443344u; // 'D3D9'
constexpr uint32_t kKindDevice  = 0x39564544u; // 'DEV9'
constexpr uint32_t kKindTexture = 0x39584554u; // 'TEX9'
constexpr uint32_t kKindSurface = 0x39465253u; // 'SRF9'
constexpr uint32_t kKindEffect  = 0x20395846u; // 'FX9 '
constexpr uint32_t kKindFont    = 0x39544E46u; // 'FNT9'
constexpr uint32_t kKindVBuf    = 0x39425644u; // 'DVB9'
constexpr uint32_t kKindIBuf    = 0x39424944u; // 'DIB9'

// D3DFORMAT codes
constexpr uint32_t kFmtUnknown  = 0u;
constexpr uint32_t kFmtR8G8B8   = 20u;
constexpr uint32_t kFmtA8R8G8B8 = 21u;
constexpr uint32_t kFmtX8R8G8B8 = 22u;
constexpr uint32_t kFmtR5G6B5   = 23u;
constexpr uint32_t kFmtX1R5G5B5 = 24u;
constexpr uint32_t kFmtA1R5G5B5 = 25u;
constexpr uint32_t kFmtA4R4G4B4 = 26u;
constexpr uint32_t kFmtA8       = 28u;
constexpr uint32_t kFmtL8       = 50u;
constexpr uint32_t kFmtD16      = 80u;
constexpr uint32_t kFmtD24S8    = 75u;
constexpr uint32_t kFmtDXT1     = 0x31545844u;
constexpr uint32_t kFmtDXT2     = 0x32545844u;
constexpr uint32_t kFmtDXT3     = 0x33545844u;
constexpr uint32_t kFmtDXT4     = 0x34545844u;
constexpr uint32_t kFmtDXT5     = 0x35545844u;

// D3DUSAGE & D3DPOOL
constexpr uint32_t kUsageRenderTarget = 0x00000001u;
constexpr uint32_t kUsageDepthStencil = 0x00000002u;

// D3DRENDERSTATETYPE values used by MBAA.exe
constexpr uint32_t kRsZEnable                  = 7u;
constexpr uint32_t kRsFillMode                 = 8u;
constexpr uint32_t kRsShadeMode                = 9u;
constexpr uint32_t kRsZWriteEnable             = 14u;
constexpr uint32_t kRsAlphaTestEnable          = 15u;
constexpr uint32_t kRsSrcBlend                 = 19u;
constexpr uint32_t kRsDestBlend                = 20u;
constexpr uint32_t kRsCullMode                 = 22u;
constexpr uint32_t kRsZFunc                    = 23u;
constexpr uint32_t kRsAlphaRef                 = 24u;
constexpr uint32_t kRsAlphaFunc                = 25u;
constexpr uint32_t kRsAlphaBlendEnable         = 27u;
constexpr uint32_t kRsTextureFactor            = 60u;
constexpr uint32_t kRsBlendOp                  = 171u;
constexpr uint32_t kRsScissorTestEnable        = 174u;
constexpr uint32_t kRsSeparateAlphaBlendEnable = 206u;
constexpr uint32_t kRsSrcBlendAlpha            = 207u;
constexpr uint32_t kRsDestBlendAlpha           = 208u;
constexpr uint32_t kRsBlendOpAlpha             = 209u;

// D3DFVF masks
constexpr uint32_t kFvfXyz      = 0x002u;
constexpr uint32_t kFvfXyzRhw   = 0x004u;
constexpr uint32_t kFvfNormal   = 0x010u;
constexpr uint32_t kFvfDiffuse  = 0x040u;
constexpr uint32_t kFvfSpecular = 0x080u;
constexpr uint32_t kFvfTexMask  = 0xF00u;

// D3DPRIMITIVETYPE
constexpr uint32_t kPtPointList     = 1u;
constexpr uint32_t kPtLineList      = 2u;
constexpr uint32_t kPtLineStrip     = 3u;
constexpr uint32_t kPtTriangleList  = 4u;
constexpr uint32_t kPtTriangleStrip = 5u;
constexpr uint32_t kPtTriangleFan   = 6u;

// ---------------------------------------------------------------------------
// Host Backing Structs
// ---------------------------------------------------------------------------
struct TextureRecord {
    uint32_t id              = 0;
    uint32_t guest_va        = 0;
    uint32_t width           = 0;
    uint32_t height          = 0;
    uint32_t levels          = 1;
    uint32_t usage           = 0;
    uint32_t format          = kFmtA8R8G8B8;
    uint32_t pool            = 0;
    uint32_t ref_count       = 1;
    bool     is_render_target = false;
    bool     is_depth_stencil = false;
    bool     is_backbuffer   = false;
    bool     locked          = false;
    bool     evicted         = false;
    uint64_t last_used_tick  = 0;
    size_t   gpu_bytes       = 0;

    id<MTLTexture> mtl_tex   = nil;
    uint32_t staging_va      = 0;
    uint32_t staging_pitch   = 0;
    uint32_t staging_bytes   = 0;
    uint32_t surface_guest_va = 0; // cached level-0 IDirect3DSurface9*
    std::vector<uint8_t> cpu_backup; // optional RGBA8/BGRA8 backup for LRU re-hydration
};

struct SurfaceRecord {
    uint32_t id             = 0;
    uint32_t guest_va       = 0;
    uint32_t parent_tex_id  = 0; // 0 if standalone RT / backbuffer / offscreen
    uint32_t mip_level      = 0;
    uint32_t width          = 0;
    uint32_t height         = 0;
    uint32_t format         = kFmtA8R8G8B8;
    uint32_t usage          = 0;
    uint32_t ref_count      = 1;
    id<MTLTexture> mtl_tex  = nil;
    uint32_t staging_va     = 0;
    uint32_t staging_pitch  = 0;
    uint32_t staging_bytes  = 0;
    bool     locked         = false;
};

struct EffectRecord {
    uint32_t id        = 0;
    uint32_t guest_va  = 0;
    uint32_t ref_count = 1;
    std::vector<std::string> techniques;
    std::vector<std::string> parameters;
    std::unordered_map<std::string, uint32_t> tech_handles;
    std::unordered_map<std::string, uint32_t> param_handles;
    uint32_t active_tech_handle = 0;
    std::string active_tech_name;
    uint32_t active_pass_index  = 0;
    bool     in_effect          = false;

    MbaaEffectUniforms uniforms{};
    std::unordered_map<std::string, uint32_t> texture_params; // param name -> guest texture VA
};

struct FontRecord {
    uint32_t id        = 0;
    uint32_t guest_va  = 0;
    uint32_t ref_count = 1;
    int32_t  height    = 12;
    uint32_t weight    = 400;
    bool     italic    = false;
    std::string face_name = "MS Gothic";
    CTFontRef ct_font  = nullptr;
};

struct BufferRecord {
    uint32_t id        = 0;
    uint32_t guest_va  = 0;
    uint32_t ref_count = 1;
    uint32_t size      = 0;
    uint32_t fvf       = 0;
    uint32_t format    = 0;
    uint32_t data_va   = 0;
    bool     is_index  = false;
};

struct SamplerStateBlock {
    uint32_t address_u  = 1; // D3DTADDRESS_WRAP
    uint32_t address_v  = 1;
    uint32_t mag_filter = 1; // D3DTEXF_POINT
    uint32_t min_filter = 1;
    uint32_t mip_filter = 0; // D3DTEXF_NONE
};

struct PipelineCacheKey {
    uint32_t pass_id       = 0;
    uint32_t rt_fmt0       = 0;
    uint32_t rt_fmt1       = 0;
    uint32_t rt_fmt2       = 0;
    uint32_t has_depth     = 0;
    uint8_t  blend_enable  = 0;
    uint8_t  src_blend     = 2; // ONE
    uint8_t  dst_blend     = 1; // ZERO
    uint8_t  blend_op      = 1; // ADD
    uint8_t  sep_alpha     = 0;
    uint8_t  src_alpha     = 2;
    uint8_t  dst_alpha     = 1;
    uint8_t  alpha_op      = 1;

    bool operator==(const PipelineCacheKey& o) const noexcept {
        return std::memcmp(this, &o, sizeof(*this)) == 0;
    }
};

struct PipelineCacheKeyHash {
    size_t operator()(const PipelineCacheKey& k) const noexcept {
        const uint64_t* p = reinterpret_cast<const uint64_t*>(&k);
        uint64_t h = 14695981039346656037ull;
        for (size_t i = 0; i < sizeof(k) / 8u; ++i) {
            h ^= p[i];
            h *= 1099511628211ull;
        }
        return static_cast<size_t>(h);
    }
};

struct SamplerCacheKey {
    uint32_t address_u  = 1;
    uint32_t address_v  = 1;
    uint32_t mag_filter = 1;
    uint32_t min_filter = 1;
    uint32_t mip_filter = 0;

    bool operator==(const SamplerCacheKey& o) const noexcept {
        return address_u == o.address_u && address_v == o.address_v &&
               mag_filter == o.mag_filter && min_filter == o.min_filter &&
               mip_filter == o.mip_filter;
    }
};

struct SamplerCacheKeyHash {
    size_t operator()(const SamplerCacheKey& k) const noexcept {
        return (static_cast<size_t>(k.address_u)) |
               (static_cast<size_t>(k.address_v) << 4) |
               (static_cast<size_t>(k.mag_filter) << 8) |
               (static_cast<size_t>(k.min_filter) << 12) |
               (static_cast<size_t>(k.mip_filter) << 16);
    }
};

// ---------------------------------------------------------------------------
// Math & Color Conversion Helpers
// ---------------------------------------------------------------------------
inline uint32_t read_u32_le_buf(const uint8_t* p) noexcept {
    return static_cast<uint32_t>(p[0]) |
           (static_cast<uint32_t>(p[1]) << 8) |
           (static_cast<uint32_t>(p[2]) << 16) |
           (static_cast<uint32_t>(p[3]) << 24);
}

inline uint16_t read_u16_le_buf(const uint8_t* p) noexcept {
    return static_cast<uint16_t>(p[0]) | (static_cast<uint16_t>(p[1]) << 8);
}

inline void argb_u32_to_float4(uint32_t c, mbaa_float4& out) noexcept {
    out.x = static_cast<float>((c >> 16) & 0xFFu) * (1.0f / 255.0f);
    out.y = static_cast<float>((c >> 8)  & 0xFFu) * (1.0f / 255.0f);
    out.z = static_cast<float>(c & 0xFFu)         * (1.0f / 255.0f);
    out.w = static_cast<float>((c >> 24) & 0xFFu) * (1.0f / 255.0f);
}

inline std::array<float, 16> identity_matrix() noexcept {
    return {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
}

inline std::array<float, 16> read_matrix(const GuestMemory& mem, uint32_t va) noexcept {
    std::array<float, 16> m = identity_matrix();
    if (va != 0u && mem.in_bounds(va, 64u)) {
        for (int i = 0; i < 16; ++i) {
            m[static_cast<size_t>(i)] = mem.rf32(va + static_cast<uint32_t>(i) * 4u);
        }
    }
    return m;
}

inline void write_matrix(GuestMemory& mem, uint32_t va, const std::array<float, 16>& m) noexcept {
    if (va != 0u && mem.in_bounds(va, 64u)) {
        for (int i = 0; i < 16; ++i) {
            mem.wf32(va + static_cast<uint32_t>(i) * 4u, m[static_cast<size_t>(i)]);
        }
    }
}

inline std::array<float, 16> mul_matrix(const std::array<float, 16>& a, const std::array<float, 16>& b) noexcept {
    std::array<float, 16> r{};
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            r[static_cast<size_t>(row * 4 + col)] =
                a[static_cast<size_t>(row * 4 + 0)] * b[static_cast<size_t>(0 * 4 + col)] +
                a[static_cast<size_t>(row * 4 + 1)] * b[static_cast<size_t>(1 * 4 + col)] +
                a[static_cast<size_t>(row * 4 + 2)] * b[static_cast<size_t>(2 * 4 + col)] +
                a[static_cast<size_t>(row * 4 + 3)] * b[static_cast<size_t>(3 * 4 + col)];
        }
    }
    return r;
}

inline uint32_t bytes_per_pixel_for_d3d_fmt(uint32_t fmt) noexcept {
    switch (fmt) {
        case kFmtR8G8B8:   return 3u;
        case kFmtR5G6B5:
        case kFmtX1R5G5B5:
        case kFmtA1R5G5B5:
        case kFmtA4R4G4B4:
        case kFmtD16:      return 2u;
        case kFmtA8:
        case kFmtL8:       return 1u;
        default:           return 4u;
    }
}

inline MTLPixelFormat d3d_fmt_to_mtl(uint32_t fmt) noexcept {
    switch (fmt) {
        case kFmtA8:       return MTLPixelFormatA8Unorm;
        case kFmtL8:       return MTLPixelFormatR8Unorm;
        case kFmtDXT1:
        case kFmtDXT2:
        case kFmtDXT3:
        case kFmtDXT4:
        case kFmtDXT5:     return MTLPixelFormatRGBA8Unorm; // decoded on CPU via bcdec_dxt.cpp
        case kFmtA8R8G8B8:
        case kFmtX8R8G8B8:
        default:           return MTLPixelFormatBGRA8Unorm;
    }
}

inline MTLBlendFactor d3d_blend_to_mtl(uint32_t b) noexcept {
    switch (b) {
        case 1u:  return MTLBlendFactorZero;
        case 2u:  return MTLBlendFactorOne;
        case 3u:  return MTLBlendFactorSourceColor;
        case 4u:  return MTLBlendFactorOneMinusSourceColor;
        case 5u:  return MTLBlendFactorSourceAlpha;
        case 6u:  return MTLBlendFactorOneMinusSourceAlpha;
        case 7u:  return MTLBlendFactorDestinationAlpha;
        case 8u:  return MTLBlendFactorOneMinusDestinationAlpha;
        case 9u:  return MTLBlendFactorDestinationColor;
        case 10u: return MTLBlendFactorOneMinusDestinationColor;
        case 11u: return MTLBlendFactorSourceAlphaSaturated;
        case 14u: return MTLBlendFactorBlendColor;
        case 15u: return MTLBlendFactorOneMinusBlendColor;
        default:  return MTLBlendFactorOne;
    }
}

inline MTLBlendOperation d3d_blendop_to_mtl(uint32_t op) noexcept {
    switch (op) {
        case 2u:  return MTLBlendOperationSubtract;
        case 3u:  return MTLBlendOperationReverseSubtract;
        case 4u:  return MTLBlendOperationMin;
        case 5u:  return MTLBlendOperationMax;
        case 1u:
        default:  return MTLBlendOperationAdd;
    }
}

inline MTLSamplerAddressMode d3d_addr_to_mtl(uint32_t a) noexcept {
    switch (a) {
        case 2u:  return MTLSamplerAddressModeMirrorRepeat;
        case 3u:  return MTLSamplerAddressModeClampToEdge;
        case 4u:  return MTLSamplerAddressModeClampToZero;
        case 1u:
        default:  return MTLSamplerAddressModeRepeat;
    }
}

inline void convert_staging_to_mtl_pixels(
    uint32_t fmt,
    uint32_t w,
    uint32_t h,
    const uint8_t* src,
    uint32_t src_pitch,
    std::vector<uint8_t>& out_bytes,
    uint32_t& out_pitch)
{
    if (fmt == kFmtA8 || fmt == kFmtL8) {
        out_pitch = w;
        out_bytes.resize(static_cast<size_t>(w) * h);
        for (uint32_t y = 0; y < h; ++y) {
            std::memcpy(out_bytes.data() + y * out_pitch, src + y * src_pitch, w);
        }
        return;
    }

    out_pitch = w * 4u;
    out_bytes.resize(static_cast<size_t>(out_pitch) * h);

    for (uint32_t y = 0; y < h; ++y) {
        const uint8_t* srow = src + static_cast<size_t>(y) * src_pitch;
        uint8_t* drow = out_bytes.data() + static_cast<size_t>(y) * out_pitch;

        if (fmt == kFmtA8R8G8B8 || fmt == kFmtX8R8G8B8 || fmt == kFmtUnknown) {
            std::memcpy(drow, srow, out_pitch);
            if (fmt == kFmtX8R8G8B8) {
                for (uint32_t x = 0; x < w; ++x) {
                    drow[x * 4u + 3u] = 255u;
                }
            }
        } else if (fmt == kFmtR8G8B8) {
            for (uint32_t x = 0; x < w; ++x) {
                drow[x * 4u + 0u] = srow[x * 3u + 0u];
                drow[x * 4u + 1u] = srow[x * 3u + 1u];
                drow[x * 4u + 2u] = srow[x * 3u + 2u];
                drow[x * 4u + 3u] = 255u;
            }
        } else if (fmt == kFmtR5G6B5) {
            for (uint32_t x = 0; x < w; ++x) {
                const uint16_t p = read_u16_le_buf(srow + x * 2u);
                const uint32_t r = (p >> 11) & 0x1Fu;
                const uint32_t g = (p >> 5) & 0x3Fu;
                const uint32_t b = p & 0x1Fu;
                drow[x * 4u + 0u] = static_cast<uint8_t>((b << 3) | (b >> 2));
                drow[x * 4u + 1u] = static_cast<uint8_t>((g << 2) | (g >> 4));
                drow[x * 4u + 2u] = static_cast<uint8_t>((r << 3) | (r >> 2));
                drow[x * 4u + 3u] = 255u;
            }
        } else if (fmt == kFmtA1R5G5B5 || fmt == kFmtX1R5G5B5) {
            for (uint32_t x = 0; x < w; ++x) {
                const uint16_t p = read_u16_le_buf(srow + x * 2u);
                const uint32_t r = (p >> 10) & 0x1Fu;
                const uint32_t g = (p >> 5) & 0x1Fu;
                const uint32_t b = p & 0x1Fu;
                drow[x * 4u + 0u] = static_cast<uint8_t>((b << 3) | (b >> 2));
                drow[x * 4u + 1u] = static_cast<uint8_t>((g << 3) | (g >> 2));
                drow[x * 4u + 2u] = static_cast<uint8_t>((r << 3) | (r >> 2));
                drow[x * 4u + 3u] = (fmt == kFmtA1R5G5B5) ? ((p & 0x8000u) ? 255u : 0u) : 255u;
            }
        } else if (fmt == kFmtA4R4G4B4) {
            for (uint32_t x = 0; x < w; ++x) {
                const uint16_t p = read_u16_le_buf(srow + x * 2u);
                const uint32_t a = (p >> 12) & 0xFu;
                const uint32_t r = (p >> 8)  & 0xFu;
                const uint32_t g = (p >> 4)  & 0xFu;
                const uint32_t b = p & 0xFu;
                drow[x * 4u + 0u] = static_cast<uint8_t>((b << 4) | b);
                drow[x * 4u + 1u] = static_cast<uint8_t>((g << 4) | g);
                drow[x * 4u + 2u] = static_cast<uint8_t>((r << 4) | r);
                drow[x * 4u + 3u] = static_cast<uint8_t>((a << 4) | a);
            }
        } else {
            std::memcpy(drow, srow, out_pitch);
        }
    }
}

inline bool decode_tga_to_rgba8(
    const uint8_t* data,
    size_t size,
    uint32_t& out_w,
    uint32_t& out_h,
    std::vector<uint8_t>& out_rgba)
{
    if (!data || size < 18u) return false;
    const uint8_t id_len   = data[0];
    const uint8_t cmap_typ = data[1];
    const uint8_t img_typ  = data[2];
    const uint16_t w       = read_u16_le_buf(data + 12);
    const uint16_t h       = read_u16_le_buf(data + 14);
    const uint8_t bpp      = data[16];
    const uint8_t desc     = data[17];
    if (cmap_typ != 0u || (img_typ != 2u && img_typ != 10u) || w == 0u || h == 0u) return false;
    if (bpp != 24u && bpp != 32u) return false;

    const size_t hdr_end = 18u + id_len;
    if (hdr_end >= size) return false;

    out_w = w;
    out_h = h;
    const size_t total_px = static_cast<size_t>(w) * h;
    out_rgba.resize(total_px * 4u);

    const bool top_down = (desc & 0x20u) != 0u;
    const size_t bytes_pp = bpp / 8u;
    size_t pos = hdr_end;

    auto write_px = [&](size_t idx, const uint8_t* p) {
        const size_t x = idx % w;
        const size_t y_raw = idx / w;
        const size_t y = top_down ? y_raw : (h - 1u - y_raw);
        uint8_t* dst = out_rgba.data() + (y * w + x) * 4u;
        dst[0] = p[2];
        dst[1] = p[1];
        dst[2] = p[0];
        dst[3] = (bytes_pp == 4u) ? p[3] : 255u;
    };

    if (img_typ == 2u) {
        if (pos + total_px * bytes_pp > size) return false;
        for (size_t i = 0; i < total_px; ++i) {
            write_px(i, data + pos + i * bytes_pp);
        }
        return true;
    }

    // RLE TGA (type 10)
    size_t px_i = 0;
    while (px_i < total_px && pos < size) {
        const uint8_t pkt = data[pos++];
        const size_t count = static_cast<size_t>(pkt & 0x7Fu) + 1u;
        if (pkt & 0x80u) {
            if (pos + bytes_pp > size) return false;
            const uint8_t* px = data + pos;
            pos += bytes_pp;
            for (size_t k = 0; k < count && px_i < total_px; ++k, ++px_i) {
                write_px(px_i, px);
            }
        } else {
            if (pos + count * bytes_pp > size) return false;
            for (size_t k = 0; k < count && px_i < total_px; ++k, ++px_i) {
                write_px(px_i, data + pos);
                pos += bytes_pp;
            }
        }
    }
    return px_i == total_px;
}

inline bool decode_generic_image_to_rgba8(
    const uint8_t* data,
    size_t size,
    uint32_t& out_w,
    uint32_t& out_h,
    std::vector<uint8_t>& out_rgba,
    DdsProbeInfo* out_dds_info = nullptr)
{
    if (!data || size < 4u) return false;

    if (size >= 128u && data[0] == 'D' && data[1] == 'D' && data[2] == 'S' && data[3] == ' ') {
        return decode_dds_to_rgba8(data, size, out_w, out_h, out_rgba, out_dds_info);
    }

    // Try UIKit/AppKit native image decoder first (PNG, JPG, BMP, GIF, TIFF)
    @autoreleasepool {
        NSData* nsData = [NSData dataWithBytesNoCopy:const_cast<uint8_t*>(data)
                                              length:size
                                        freeWhenDone:NO];
        CGImageRef cgImg = nullptr;
#if TARGET_OS_IPHONE
        UIImage* img = [UIImage imageWithData:nsData];
        cgImg = img.CGImage;
#else
        NSImage* img = [[NSImage alloc] initWithData:nsData];
        if (img) {
            cgImg = [img CGImageForProposedRect:nullptr context:nil hints:nil];
        }
#endif
        if (cgImg != nullptr) {
            const size_t w = CGImageGetWidth(cgImg);
            const size_t h = CGImageGetHeight(cgImg);
            if (w > 0 && h > 0) {
                out_w = static_cast<uint32_t>(w);
                out_h = static_cast<uint32_t>(h);
                out_rgba.assign(w * h * 4u, 0u);
                CGColorSpaceRef cs = CGColorSpaceCreateDeviceRGB();
                CGContextRef ctx = CGBitmapContextCreate(
                    out_rgba.data(), w, h, 8, w * 4u, cs,
                    static_cast<uint32_t>(kCGImageAlphaPremultipliedLast) | kCGBitmapByteOrder32Big);
                if (ctx != nullptr) {
                    CGContextSetBlendMode(ctx, kCGBlendModeCopy);
                    CGContextDrawImage(ctx, CGRectMake(0, 0, static_cast<CGFloat>(w), static_cast<CGFloat>(h)), cgImg);
                    CGContextRelease(ctx);
                    CGColorSpaceRelease(cs);
                    // Un-premultiply CGContext output back to straight RGBA8
                    for (size_t i = 0; i < w * h; ++i) {
                        const uint8_t a = out_rgba[i * 4u + 3u];
                        if (a > 0u && a < 255u) {
                            out_rgba[i * 4u + 0u] = static_cast<uint8_t>(std::min<uint32_t>(255u, (out_rgba[i * 4u + 0u] * 255u + (a >> 1)) / a));
                            out_rgba[i * 4u + 1u] = static_cast<uint8_t>(std::min<uint32_t>(255u, (out_rgba[i * 4u + 1u] * 255u + (a >> 1)) / a));
                            out_rgba[i * 4u + 2u] = static_cast<uint8_t>(std::min<uint32_t>(255u, (out_rgba[i * 4u + 2u] * 255u + (a >> 1)) / a));
                        }
                    }
                    return true;
                }
                CGColorSpaceRelease(cs);
            }
        }
    }

    // Fallback: TGA (uncompressed/RLE)
    return decode_tga_to_rgba8(data, size, out_w, out_h, out_rgba);
}

inline void parse_cfx_metadata(const uint8_t* data, size_t size, EffectRecord& eff) {
    if (!data || size < 24u) return;
    const uint32_t magic = read_u32_le_buf(data);
    if (magic != 0xFEFF0901u) return;

    const uint32_t base = 8u;
    const uint32_t hdr_rel = read_u32_le_buf(data + 4u);
    const size_t hdr_off = static_cast<size_t>(base) + hdr_rel;
    if (hdr_off + 16u > size) return;

    const uint32_t n_param = read_u32_le_buf(data + hdr_off);
    const uint32_t n_tech  = read_u32_le_buf(data + hdr_off + 4u);
    size_t pos = hdr_off + 16u;

    auto read_fx_str = [&](uint32_t rel_off) -> std::string {
        if (rel_off == 0u) return {};
        const size_t p = static_cast<size_t>(base) + rel_off;
        if (p + 4u > size) return {};
        const uint32_t slen = read_u32_le_buf(data + p);
        if (p + 4u + slen > size) return {};
        std::string s(reinterpret_cast<const char*>(data + p + 4u), slen);
        while (!s.empty() && s.back() == '\0') s.pop_back();
        return s;
    };

    for (uint32_t i = 0; i < n_param && pos + 16u <= size; ++i) {
        const uint32_t type_off = read_u32_le_buf(data + pos);
        const uint32_t ann_cnt  = read_u32_le_buf(data + pos + 12u);
        pos += 16u + static_cast<size_t>(ann_cnt) * 8u;
        const size_t tp = static_cast<size_t>(base) + type_off;
        if (tp + 20u <= size) {
            const uint32_t name_off = read_u32_le_buf(data + tp + 8u);
            std::string pname = read_fx_str(name_off);
            if (!pname.empty()) {
                const uint32_t h = static_cast<uint32_t>(eff.parameters.size() + 1u);
                eff.parameters.push_back(pname);
                eff.param_handles[pname] = h;
            }
        }
    }

    for (uint32_t i = 0; i < n_tech && pos + 12u <= size; ++i) {
        const uint32_t tname_off = read_u32_le_buf(data + pos);
        const uint32_t ann_cnt   = read_u32_le_buf(data + pos + 4u);
        const uint32_t pass_cnt  = read_u32_le_buf(data + pos + 8u);
        pos += 12u + static_cast<size_t>(ann_cnt) * 8u;
        std::string tname = read_fx_str(tname_off);
        if (!tname.empty()) {
            const uint32_t th = static_cast<uint32_t>(eff.techniques.size() + 1u);
            eff.techniques.push_back(tname);
            eff.tech_handles[tname] = th;
        }
        for (uint32_t j = 0; j < pass_cnt && pos + 12u <= size; ++j) {
            const uint32_t pann_cnt  = read_u32_le_buf(data + pos + 4u);
            const uint32_t state_cnt = read_u32_le_buf(data + pos + 8u);
            pos += 12u + static_cast<size_t>(pann_cnt) * 8u + static_cast<size_t>(state_cnt) * 16u;
        }
    }
}

inline std::atomic<D3D9MetalBridge*>& global_bridge_slot() noexcept {
    static std::atomic<D3D9MetalBridge*> s_bridge{nullptr};
    return s_bridge;
}

} // namespace

// ---------------------------------------------------------------------------
// D3D9MetalBridge::Impl (Metal Device, Pipelines, LRU Cache, Guest COM Tables)
// ---------------------------------------------------------------------------
struct D3D9MetalBridge::Impl {
    mutable std::recursive_mutex mtx;

    CAMetalLayer*              metal_layer    = nil;
    id<MTLDevice>              device         = nil;
    id<MTLCommandQueue>        cmd_queue      = nil;
    id<MTLLibrary>             shader_lib     = nil;
    MTLVertexDescriptor*       vertex_desc    = nil;
    id<MTLCommandBuffer>       frame_cmd_buf  = nil;
    id<MTLRenderCommandEncoder> active_encoder = nil;
    id<MTLDepthStencilState>   depth_disabled = nil;
    id<MTLDepthStencilState>   depth_enabled  = nil;
    id<MTLTexture>             dummy_black_tex = nil;
    id<MTLTexture>             dummy_mrt_tex   = nil;
    id<MTLTexture>             depth_tex       = nil;

    int drawable_width  = 1334;
    int drawable_height = 750;
    uint32_t logical_width  = kGameLogicalWidth;
    uint32_t logical_height = kGameLogicalHeight;

    bool initialized = false;
    bool in_frame    = false;
    bool in_scene    = false;
    bool guest_presented_this_frame = false;
    bool encoder_rt_dirty = true;
    uint64_t lru_clock = 1;
    uint64_t draw_calls = 0;

    // Caches
    std::unordered_map<PipelineCacheKey, id<MTLRenderPipelineState>, PipelineCacheKeyHash> pipeline_cache;
    std::unordered_map<SamplerCacheKey, id<MTLSamplerState>, SamplerCacheKeyHash> sampler_cache;

    // Guest COM objects & vtables
    uint32_t vtbl_d3d9    = 0;
    uint32_t vtbl_device  = 0;
    uint32_t vtbl_texture = 0;
    uint32_t vtbl_surface = 0;
    uint32_t vtbl_effect  = 0;
    uint32_t vtbl_font    = 0;
    uint32_t vtbl_vbuf    = 0;
    uint32_t vtbl_ibuf    = 0;

    uint32_t d3d9_guest_va       = 0;
    uint32_t device_guest_va     = 0;
    uint32_t backbuffer_surf_va  = 0;
    uint32_t depth_surf_va       = 0;
    uint32_t fill_scratch_va     = 0;
    uint32_t font_scratch_tex_id = 0;
    uint32_t font_scratch_tex_va = 0;
    uint32_t next_handle_id      = 1;

    std::unordered_map<uint32_t, TextureRecord> textures; // handle_id -> TextureRecord
    std::unordered_map<uint32_t, SurfaceRecord> surfaces; // handle_id -> SurfaceRecord
    std::unordered_map<uint32_t, EffectRecord>  effects;  // handle_id -> EffectRecord
    std::unordered_map<uint32_t, FontRecord>    fonts;    // handle_id -> FontRecord
    std::unordered_map<uint32_t, BufferRecord>  buffers;  // handle_id -> BufferRecord
    size_t cached_texture_bytes = 0;

    // Active D3D9 device pipeline state
    std::array<uint32_t, 4> bound_rt_surfaces{};       // RT0..RT3 guest surface VAs
    uint32_t                bound_ds_surface = 0;      // Depth-stencil surface VA
    std::array<uint32_t, 8> bound_textures{};          // Stage 0..7 guest texture VAs
    std::array<SamplerStateBlock, 8> sampler_states{};
    std::array<uint32_t, 32> tss_stage0_colorop{};     // stage -> colorop
    std::array<uint32_t, 32> tss_stage0_alphaop{};     // stage -> alphaop
    std::array<uint32_t, 256> render_states{};

    std::array<float, 16> mat_world = identity_matrix();
    std::array<float, 16> mat_view  = identity_matrix();
    std::array<float, 16> mat_proj  = identity_matrix();

    uint32_t current_fvf        = 0x000001C4u;
    uint32_t current_vb_va      = 0;
    uint32_t current_vb_stride  = 32;
    uint32_t current_ib_va      = 0;
    uint32_t vp_x = 0, vp_y = 0, vp_w = 640, vp_h = 480;
    uint32_t active_effect_id   = 0;
    MbaaShaderPassId active_pass = MBAA_PASS_FIXED_2D;

    // -----------------------------------------------------------------------
    // Helpers: Guest COM Object Allocation & Resolution
    // -----------------------------------------------------------------------
    uint32_t alloc_com_object(GuestMemory& mem, uint32_t vtbl_va, uint32_t handle_id, uint32_t kind_tag) {
        const uint32_t obj_va = mem.alloc_thunk_block(16u, 16u);
        mem.w32(obj_va + 0u, vtbl_va);
        mem.w32(obj_va + 4u, handle_id);
        mem.w32(obj_va + 8u, 1u);
        mem.w32(obj_va + 12u, kind_tag);
        return obj_va;
    }

    TextureRecord* find_texture_by_va(const GuestMemory& mem, uint32_t tex_va) {
        if (tex_va == 0u || !mem.in_bounds(tex_va, 16u)) return nullptr;
        if (mem.r32(tex_va + 12u) != kKindTexture) return nullptr;
        auto it = textures.find(mem.r32(tex_va + 4u));
        return (it != textures.end()) ? &it->second : nullptr;
    }

    SurfaceRecord* find_surface_by_va(const GuestMemory& mem, uint32_t surf_va) {
        if (surf_va == 0u || !mem.in_bounds(surf_va, 16u)) return nullptr;
        if (mem.r32(surf_va + 12u) != kKindSurface) return nullptr;
        auto it = surfaces.find(mem.r32(surf_va + 4u));
        return (it != surfaces.end()) ? &it->second : nullptr;
    }

    EffectRecord* find_effect_by_va(const GuestMemory& mem, uint32_t fx_va) {
        if (fx_va == 0u || !mem.in_bounds(fx_va, 16u)) return nullptr;
        if (mem.r32(fx_va + 12u) != kKindEffect) return nullptr;
        auto it = effects.find(mem.r32(fx_va + 4u));
        return (it != effects.end()) ? &it->second : nullptr;
    }

    FontRecord* find_font_by_va(const GuestMemory& mem, uint32_t font_va) {
        if (font_va == 0u || !mem.in_bounds(font_va, 16u)) return nullptr;
        if (mem.r32(font_va + 12u) != kKindFont) return nullptr;
        auto it = fonts.find(mem.r32(font_va + 4u));
        return (it != fonts.end()) ? &it->second : nullptr;
    }

    // -----------------------------------------------------------------------
    // Metal Texture Creation & 192 MiB LRU Cache Eviction
    // -----------------------------------------------------------------------
    id<MTLTexture> make_mtl_texture(uint32_t w, uint32_t h, MTLPixelFormat fmt, bool is_rt, bool is_ds) {
        if (!device || w == 0u || h == 0u) return nil;
        MTLTextureDescriptor* desc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:fmt
                                                                                        width:w
                                                                                       height:h
                                                                                    mipmapped:NO];
        if (is_ds) {
            desc.storageMode = MTLStorageModePrivate;
            desc.usage       = MTLTextureUsageRenderTarget;
        } else if (is_rt) {
            desc.storageMode = MTLStorageModePrivate;
            desc.usage       = MTLTextureUsageRenderTarget | MTLTextureUsageShaderRead;
        } else {
            desc.storageMode = MTLStorageModeShared;
            desc.usage       = MTLTextureUsageShaderRead;
        }
        return [device newTextureWithDescriptor:desc];
    }

    void evict_lru_to_budget(size_t target_bytes) {
        if (cached_texture_bytes <= target_bytes) return;
        std::vector<TextureRecord*> candidates;
        candidates.reserve(textures.size());
        for (auto& [id, rec] : textures) {
            if (!rec.is_render_target && !rec.is_depth_stencil && !rec.is_backbuffer &&
                rec.mtl_tex != nil && !rec.locked) {
                bool currently_bound = false;
                for (uint32_t bva : bound_textures) {
                    if (bva == rec.guest_va) {
                        currently_bound = true;
                        break;
                    }
                }
                if (!currently_bound) {
                    candidates.push_back(&rec);
                }
            }
        }
        std::sort(candidates.begin(), candidates.end(), [](const TextureRecord* a, const TextureRecord* b) {
            return a->last_used_tick < b->last_used_tick;
        });

        for (TextureRecord* rec : candidates) {
            if (cached_texture_bytes <= target_bytes) break;
            if (rec->mtl_tex != nil) {
                rec->mtl_tex = nil;
                rec->evicted = true;
                if (cached_texture_bytes >= rec->gpu_bytes) {
                    cached_texture_bytes -= rec->gpu_bytes;
                } else {
                    cached_texture_bytes = 0;
                }
            }
        }
    }

    id<MTLTexture> resolve_stage_texture(const GuestMemory& mem, uint32_t tex_va) {
        TextureRecord* rec = find_texture_by_va(mem, tex_va);
        if (!rec) return dummy_black_tex;
        rec->last_used_tick = ++lru_clock;
        if (rec->mtl_tex == nil && !rec->cpu_backup.empty()) {
            const MTLPixelFormat mfmt = (rec->format >= kFmtDXT1 && rec->format <= kFmtDXT5)
                                            ? MTLPixelFormatRGBA8Unorm
                                            : d3d_fmt_to_mtl(rec->format);
            rec->mtl_tex = make_mtl_texture(rec->width, rec->height, mfmt, false, false);
            if (rec->mtl_tex != nil) {
                const uint32_t bpp = (mfmt == MTLPixelFormatA8Unorm || mfmt == MTLPixelFormatR8Unorm) ? 1u : 4u;
                [rec->mtl_tex replaceRegion:MTLRegionMake2D(0, 0, rec->width, rec->height)
                                mipmapLevel:0
                                  withBytes:rec->cpu_backup.data()
                                bytesPerRow:rec->width * bpp];
                rec->evicted = false;
                cached_texture_bytes += rec->gpu_bytes;
                evict_lru_to_budget(kTextureCacheLimitBytes);
            }
        }
        return rec->mtl_tex ? rec->mtl_tex : dummy_black_tex;
    }

    // -----------------------------------------------------------------------
    // Pipeline & Sampler State Caching
    // -----------------------------------------------------------------------
    id<MTLRenderPipelineState> get_pipeline(const PipelineCacheKey& key) {
        auto it = pipeline_cache.find(key);
        if (it != pipeline_cache.end()) {
            return it->second;
        }
        if (!device || !shader_lib) return nil;

        const auto& entry = shader_manifest::entry_for_pass_id(static_cast<MbaaShaderPassId>(key.pass_id));
        NSString* vsName = [NSString stringWithUTF8String:entry.vertex_fn];
        NSString* psName = [NSString stringWithUTF8String:entry.fragment_fn];
        id<MTLFunction> vsFn = [shader_lib newFunctionWithName:vsName];
        id<MTLFunction> psFn = [shader_lib newFunctionWithName:psName];
        if (!vsFn || !psFn) {
            std::fprintf(stderr, "[D3D9MetalBridge] Missing Metal shader function %s / %s\n",
                         entry.vertex_fn, entry.fragment_fn);
            return nil;
        }

        MTLRenderPipelineDescriptor* desc = [[MTLRenderPipelineDescriptor alloc] init];
        desc.vertexFunction   = vsFn;
        desc.fragmentFunction = psFn;
        if (key.pass_id != MBAA_PASS_PRESENT_BLIT) {
            desc.vertexDescriptor = vertex_desc;
        }

        auto configure_attachment = [&](NSUInteger idx, uint32_t fmt_val) {
            if (fmt_val == 0u) return;
            MTLRenderPipelineColorAttachmentDescriptor* att = desc.colorAttachments[idx];
            att.pixelFormat = static_cast<MTLPixelFormat>(fmt_val);
            if (key.blend_enable && idx == 0u && key.pass_id != MBAA_PASS_PRESENT_BLIT) {
                att.blendingEnabled             = YES;
                att.sourceRGBBlendFactor        = d3d_blend_to_mtl(key.src_blend);
                att.destinationRGBBlendFactor   = d3d_blend_to_mtl(key.dst_blend);
                att.rgbBlendOperation           = d3d_blendop_to_mtl(key.blend_op);
                if (key.sep_alpha) {
                    att.sourceAlphaBlendFactor      = d3d_blend_to_mtl(key.src_alpha);
                    att.destinationAlphaBlendFactor = d3d_blend_to_mtl(key.dst_alpha);
                    att.alphaBlendOperation         = d3d_blendop_to_mtl(key.alpha_op);
                } else {
                    att.sourceAlphaBlendFactor      = att.sourceRGBBlendFactor;
                    att.destinationAlphaBlendFactor = att.destinationRGBBlendFactor;
                    att.alphaBlendOperation         = att.rgbBlendOperation;
                }
            } else {
                att.blendingEnabled = NO;
            }
        };

        configure_attachment(0, key.rt_fmt0);
        if (entry.mrt_count >= 2u) configure_attachment(1, key.rt_fmt1 ? key.rt_fmt1 : static_cast<uint32_t>(MTLPixelFormatBGRA8Unorm));
        if (entry.mrt_count >= 3u) configure_attachment(2, key.rt_fmt2 ? key.rt_fmt2 : static_cast<uint32_t>(MTLPixelFormatBGRA8Unorm));
        if (key.has_depth) {
            desc.depthAttachmentPixelFormat   = MTLPixelFormatDepth32Float_Stencil8;
            desc.stencilAttachmentPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
        }

        NSError* err = nil;
        id<MTLRenderPipelineState> pso = [device newRenderPipelineStateWithDescriptor:desc error:&err];
        if (!pso || err) {
            std::fprintf(stderr, "[D3D9MetalBridge] PSO build failed for %s: %s\n",
                         entry.fragment_fn, err ? err.localizedDescription.UTF8String : "unknown");
            return nil;
        }
        pipeline_cache[key] = pso;
        return pso;
    }

    id<MTLSamplerState> get_sampler(const SamplerStateBlock& s) {
        SamplerCacheKey k{s.address_u, s.address_v, s.mag_filter, s.min_filter, s.mip_filter};
        auto it = sampler_cache.find(k);
        if (it != sampler_cache.end()) return it->second;
        if (!device) return nil;

        MTLSamplerDescriptor* desc = [[MTLSamplerDescriptor alloc] init];
        desc.sAddressMode = d3d_addr_to_mtl(s.address_u);
        desc.tAddressMode = d3d_addr_to_mtl(s.address_v);
        desc.magFilter    = (s.mag_filter >= 2u) ? MTLSamplerMinMagFilterLinear : MTLSamplerMinMagFilterNearest;
        desc.minFilter    = (s.min_filter >= 2u) ? MTLSamplerMinMagFilterLinear : MTLSamplerMinMagFilterNearest;
        desc.mipFilter    = MTLSamplerMipFilterNotMipmapped;
        id<MTLSamplerState> samp = [device newSamplerStateWithDescriptor:desc];
        sampler_cache[k] = samp;
        return samp;
    }

    // -----------------------------------------------------------------------
    // Active Render Pass Encoder Management
    // -----------------------------------------------------------------------
    void end_active_encoder() {
        if (active_encoder != nil) {
            [active_encoder endEncoding];
            active_encoder = nil;
        }
    }

    id<MTLCommandBuffer> ensure_cmd_buffer() {
        if (frame_cmd_buf == nil && cmd_queue != nil) {
            frame_cmd_buf = [cmd_queue commandBuffer];
        }
        return frame_cmd_buf;
    }

    id<MTLTexture> resolve_rt_texture(const GuestMemory& mem, uint32_t rt_index) {
        if (rt_index >= bound_rt_surfaces.size()) return nil;
        const uint32_t surf_va = bound_rt_surfaces[rt_index];
        if (surf_va == 0u) return nil;
        SurfaceRecord* s = find_surface_by_va(mem, surf_va);
        if (!s) return nil;
        if (s->mtl_tex != nil) return s->mtl_tex;
        if (s->parent_tex_id != 0u) {
            auto tit = textures.find(s->parent_tex_id);
            if (tit != textures.end()) return tit->second.mtl_tex;
        }
        return nil;
    }

    id<MTLRenderCommandEncoder> ensure_render_encoder(const GuestMemory& mem, uint32_t mrt_count, bool clear_color = false, uint32_t clear_argb = 0u, bool clear_depth = false) {
        id<MTLCommandBuffer> cb = ensure_cmd_buffer();
        if (!cb) return nil;

        if (active_encoder != nil && !encoder_rt_dirty && !clear_color && !clear_depth) {
            return active_encoder;
        }
        end_active_encoder();

        id<MTLTexture> rt0 = resolve_rt_texture(mem, 0u);
        if (!rt0) return nil;

        MTLRenderPassDescriptor* rpd = [MTLRenderPassDescriptor renderPassDescriptor];
        auto setup_rt = [&](NSUInteger idx, id<MTLTexture> tex, bool do_clear) {
            rpd.colorAttachments[idx].texture    = tex;
            rpd.colorAttachments[idx].loadAction = do_clear ? MTLLoadActionClear : MTLLoadActionLoad;
            rpd.colorAttachments[idx].storeAction = MTLStoreActionStore;
            if (do_clear) {
                mbaa_float4 cf{};
                argb_u32_to_float4(clear_argb, cf);
                rpd.colorAttachments[idx].clearColor = MTLClearColorMake(cf.x, cf.y, cf.z, cf.w);
            }
        };

        setup_rt(0, rt0, clear_color);
        if (mrt_count >= 2u) {
            id<MTLTexture> rt1 = resolve_rt_texture(mem, 1u);
            setup_rt(1, rt1 ? rt1 : dummy_mrt_tex, false);
        }
        if (mrt_count >= 3u) {
            id<MTLTexture> rt2 = resolve_rt_texture(mem, 2u);
            setup_rt(2, rt2 ? rt2 : dummy_mrt_tex, false);
        }

        if (bound_ds_surface != 0u && depth_tex != nil &&
            depth_tex.width == rt0.width && depth_tex.height == rt0.height) {
            rpd.depthAttachment.texture     = depth_tex;
            rpd.depthAttachment.loadAction  = clear_depth ? MTLLoadActionClear : MTLLoadActionLoad;
            rpd.depthAttachment.storeAction = MTLStoreActionStore;
            rpd.depthAttachment.clearDepth  = 1.0;
            rpd.stencilAttachment.texture     = depth_tex;
            rpd.stencilAttachment.loadAction  = clear_depth ? MTLLoadActionClear : MTLLoadActionLoad;
            rpd.stencilAttachment.storeAction = MTLStoreActionStore;
        }

        active_encoder = [cb renderCommandEncoderWithDescriptor:rpd];
        encoder_rt_dirty = false;

        if (active_encoder != nil) {
            MTLViewport mvp{
                static_cast<double>(vp_x),
                static_cast<double>(vp_y),
                static_cast<double>(std::min<uint32_t>(vp_w, static_cast<uint32_t>(rt0.width))),
                static_cast<double>(std::min<uint32_t>(vp_h, static_cast<uint32_t>(rt0.height))),
                0.0, 1.0
            };
            [active_encoder setViewport:mvp];
        }
        return active_encoder;
    }

    // -----------------------------------------------------------------------
    // Draw Execution (Fixed-Function & Active .cfx Technique Pass)
    // -----------------------------------------------------------------------
    void execute_draw(
        const GuestMemory& mem,
        uint32_t prim_type,
        uint32_t prim_count,
        const uint8_t* vdata,
        uint32_t vcount,
        uint32_t vstride,
        const uint8_t* idata,
        uint32_t index_fmt)
    {
        if (!vdata || prim_count == 0u || vcount == 0u) return;

        // Determine active pass & effect parameters
        MbaaShaderPassId pass_id = MBAA_PASS_FIXED_2D;
        EffectRecord* fx = nullptr;
        if (active_effect_id != 0u) {
            auto eit = effects.find(active_effect_id);
            if (eit != effects.end() && eit->second.in_effect) {
                fx = &eit->second;
                if (const auto* e = shader_manifest::find_technique_pass(
                        fx->active_tech_name.c_str(), fx->active_pass_index)) {
                    pass_id = e->pass_id;
                }
            }
        }

        const auto& pass_entry = shader_manifest::entry_for_pass_id(pass_id);
        id<MTLRenderCommandEncoder> enc = ensure_render_encoder(mem, pass_entry.mrt_count);
        if (!enc) return;

        // Decode FVF vertices into unified MbaaMetalVertex buffer
        const bool has_rhw      = (current_fvf & kFvfXyzRhw) != 0u;
        const bool has_xyz      = (current_fvf & kFvfXyz) != 0u;
        const bool has_normal   = (current_fvf & kFvfNormal) != 0u;
        const bool has_diffuse  = (current_fvf & kFvfDiffuse) != 0u;
        const bool has_specular = (current_fvf & kFvfSpecular) != 0u;
        const uint32_t tex_cnt  = (current_fvf & kFvfTexMask) >> 8;

        // Compute fallback stride if caller didn't provide one
        uint32_t stride = vstride;
        if (stride == 0u) {
            stride = (has_rhw ? 16u : (has_xyz ? 12u : 12u)) +
                     (has_normal ? 12u : 0u) +
                     (has_diffuse ? 4u : 0u) +
                     (has_specular ? 4u : 0u) +
                     tex_cnt * 8u;
        }

        std::vector<MbaaMetalVertex> verts(vcount);
        for (uint32_t i = 0; i < vcount; ++i) {
            const uint8_t* p = vdata + static_cast<size_t>(i) * stride;
            MbaaMetalVertex& dst = verts[i];
            size_t off = 0u;

            if (has_rhw) {
                float xyzw[4]{};
                std::memcpy(xyzw, p + off, 16u);
                dst.position = {xyzw[0], xyzw[1], xyzw[2], xyzw[3]};
                off += 16u;
            } else {
                float xyz[3]{};
                std::memcpy(xyz, p + off, 12u);
                dst.position = {xyz[0], xyz[1], xyz[2], 1.0f};
                off += 12u;
            }
            if (has_normal) {
                off += 12u;
            }
            if (has_diffuse) {
                argb_u32_to_float4(read_u32_le_buf(p + off), dst.diffuse);
                off += 4u;
            } else {
                dst.diffuse = {1.0f, 1.0f, 1.0f, 1.0f};
            }
            if (has_specular) {
                argb_u32_to_float4(read_u32_le_buf(p + off), dst.specular);
                off += 4u;
            } else {
                dst.specular = {0.0f, 0.0f, 0.0f, 0.0f};
            }
            if (tex_cnt >= 1u && off + 8u <= stride) {
                float uv0[2]{};
                std::memcpy(uv0, p + off, 8u);
                dst.texcoord0 = {uv0[0], uv0[1]};
                off += 8u;
            } else {
                dst.texcoord0 = {0.0f, 0.0f};
            }
            if (tex_cnt >= 2u && off + 8u <= stride) {
                float uv1[2]{};
                std::memcpy(uv1, p + off, 8u);
                dst.texcoord1 = {uv1[0], uv1[1]};
            } else {
                dst.texcoord1 = dst.texcoord0;
            }
        }

        // Convert D3D9 primitive/index topology to Metal
        MTLPrimitiveType mtl_prim = MTLPrimitiveTypeTriangle;
        std::vector<uint32_t> expanded_indices;
        const uint32_t* draw_indices = nullptr;
        uint32_t draw_index_count = 0u;

        auto read_idx = [&](uint32_t k) -> uint32_t {
            if (!idata) return k;
            if (index_fmt == 101u) { // D3DFMT_INDEX16
                return read_u16_le_buf(idata + k * 2u);
            }
            return read_u32_le_buf(idata + k * 4u);
        };

        switch (prim_type) {
            case kPtPointList:
                mtl_prim = MTLPrimitiveTypePoint;
                draw_index_count = prim_count;
                break;
            case kPtLineList:
                mtl_prim = MTLPrimitiveTypeLine;
                draw_index_count = prim_count * 2u;
                break;
            case kPtLineStrip:
                mtl_prim = MTLPrimitiveTypeLineStrip;
                draw_index_count = prim_count + 1u;
                break;
            case kPtTriangleStrip:
                mtl_prim = MTLPrimitiveTypeTriangleStrip;
                draw_index_count = prim_count + 2u;
                break;
            case kPtTriangleFan:
                mtl_prim = MTLPrimitiveTypeTriangle;
                expanded_indices.resize(prim_count * 3u);
                for (uint32_t t = 0; t < prim_count; ++t) {
                    expanded_indices[t * 3u + 0u] = read_idx(0u);
                    expanded_indices[t * 3u + 1u] = read_idx(t + 1u);
                    expanded_indices[t * 3u + 2u] = read_idx(t + 2u);
                }
                draw_indices = expanded_indices.data();
                draw_index_count = prim_count * 3u;
                break;
            case kPtTriangleList:
            default:
                mtl_prim = MTLPrimitiveTypeTriangle;
                draw_index_count = prim_count * 3u;
                break;
        }

        if (draw_indices == nullptr && idata != nullptr) {
            expanded_indices.resize(draw_index_count);
            for (uint32_t k = 0; k < draw_index_count; ++k) {
                expanded_indices[k] = read_idx(k);
            }
            draw_indices = expanded_indices.data();
        }

        // Resolve PSO
        id<MTLTexture> rt0 = resolve_rt_texture(mem, 0u);
        id<MTLTexture> rt1 = (pass_entry.mrt_count >= 2u) ? resolve_rt_texture(mem, 1u) : nil;
        id<MTLTexture> rt2 = (pass_entry.mrt_count >= 3u) ? resolve_rt_texture(mem, 2u) : nil;

        PipelineCacheKey pkey{};
        pkey.pass_id      = static_cast<uint32_t>(pass_id);
        pkey.rt_fmt0      = rt0 ? static_cast<uint32_t>(rt0.pixelFormat) : static_cast<uint32_t>(MTLPixelFormatBGRA8Unorm);
        pkey.rt_fmt1      = rt1 ? static_cast<uint32_t>(rt1.pixelFormat) : static_cast<uint32_t>(MTLPixelFormatBGRA8Unorm);
        pkey.rt_fmt2      = rt2 ? static_cast<uint32_t>(rt2.pixelFormat) : static_cast<uint32_t>(MTLPixelFormatBGRA8Unorm);
        pkey.has_depth    = (bound_ds_surface != 0u && depth_tex != nil &&
                             rt0 != nil && depth_tex.width == rt0.width && depth_tex.height == rt0.height) ? 1u : 0u;
        pkey.blend_enable = render_states[kRsAlphaBlendEnable] ? 1u : 0u;
        pkey.src_blend    = static_cast<uint8_t>(render_states[kRsSrcBlend] ? render_states[kRsSrcBlend] : 5u);
        pkey.dst_blend    = static_cast<uint8_t>(render_states[kRsDestBlend] ? render_states[kRsDestBlend] : 6u);
        pkey.blend_op     = static_cast<uint8_t>(render_states[kRsBlendOp] ? render_states[kRsBlendOp] : 1u);
        pkey.sep_alpha    = render_states[kRsSeparateAlphaBlendEnable] ? 1u : 0u;
        pkey.src_alpha    = static_cast<uint8_t>(render_states[kRsSrcBlendAlpha] ? render_states[kRsSrcBlendAlpha] : 2u);
        pkey.dst_alpha    = static_cast<uint8_t>(render_states[kRsDestBlendAlpha] ? render_states[kRsDestBlendAlpha] : 1u);
        pkey.alpha_op     = static_cast<uint8_t>(render_states[kRsBlendOpAlpha] ? render_states[kRsBlendOpAlpha] : 1u);

        id<MTLRenderPipelineState> pso = get_pipeline(pkey);
        if (!pso) return;

        [enc setRenderPipelineState:pso];
        if (pkey.has_depth) {
            [enc setDepthStencilState:(render_states[kRsZEnable] ? depth_enabled : depth_disabled)];
        }
        [enc setCullMode:MTLCullModeNone]; // 2D sprite quads in MBAACC can flip UVs/X via negative scale

        // Populate MbaaDrawUniforms
        MbaaDrawUniforms du{};
        const auto wvp = mul_matrix(mul_matrix(mat_world, mat_view), mat_proj);
        for (int row = 0; row < 4; ++row) {
            // Transpose columns into row-major dot products so row-vector v * (W*V*P) matches D3D9!
            du.world_view_proj[row] = {
                wvp[static_cast<size_t>(0 * 4 + row)],
                wvp[static_cast<size_t>(1 * 4 + row)],
                wvp[static_cast<size_t>(2 * 4 + row)],
                wvp[static_cast<size_t>(3 * 4 + row)]
            };
        }
        const float rtw = rt0 ? static_cast<float>(rt0.width)  : 640.0f;
        const float rth = rt0 ? static_cast<float>(rt0.height) : 480.0f;
        const float use_w = (vp_w > 0u) ? static_cast<float>(vp_w) : rtw;
        const float use_h = (vp_h > 0u) ? static_cast<float>(vp_h) : rth;
        du.viewport_inv      = {2.0f / use_w, 2.0f / use_h, static_cast<float>(vp_x), static_cast<float>(vp_y)};
        du.is_transformed    = has_rhw ? 1u : 0u;
        du.has_texture       = (bound_textures[0] != 0u) ? 1u : 0u;
        du.alpha_test_enable = render_states[kRsAlphaTestEnable];
        du.alpha_func        = render_states[kRsAlphaFunc] ? render_states[kRsAlphaFunc] : 8u;
        du.alpha_ref         = static_cast<float>(render_states[kRsAlphaRef] & 0xFFu) * (1.0f / 255.0f);
        du.color_op0         = tss_stage0_colorop[0] ? tss_stage0_colorop[0] : 4u;
        du.alpha_op0         = tss_stage0_alphaop[0] ? tss_stage0_alphaop[0] : 4u;
        argb_u32_to_float4(render_states[kRsTextureFactor], du.texture_factor);

        [enc setVertexBytes:verts.data() length:verts.size() * sizeof(MbaaMetalVertex) atIndex:MBAA_BUF_VERTICES];
        [enc setVertexBytes:&du length:sizeof(du) atIndex:MBAA_BUF_DRAW_UNIFORMS];
        [enc setFragmentBytes:&du length:sizeof(du) atIndex:MBAA_BUF_DRAW_UNIFORMS];

        if (fx != nullptr) {
            [enc setFragmentBytes:&fx->uniforms length:sizeof(fx->uniforms) atIndex:MBAA_BUF_EFFECT_UNIFORMS];
            bind_effect_textures(mem, enc, *fx, pass_id);
        } else {
            [enc setFragmentTexture:resolve_stage_texture(mem, bound_textures[0]) atIndex:MBAA_TEX_STAGE0];
            [enc setFragmentSamplerState:get_sampler(sampler_states[0]) atIndex:0];
        }

        if (draw_indices != nullptr) {
            id<MTLBuffer> ib = [device newBufferWithBytes:draw_indices
                                                 length:draw_index_count * sizeof(uint32_t)
                                                options:MTLResourceStorageModeShared];
            [enc drawIndexedPrimitives:mtl_prim
                            indexCount:draw_index_count
                             indexType:MTLIndexTypeUInt32
                           indexBuffer:ib
                     indexBufferOffset:0];
        } else {
            [enc drawPrimitives:mtl_prim vertexStart:0 vertexCount:draw_index_count];
        }
        ++draw_calls;
    }

    void bind_effect_textures(
        const GuestMemory& mem,
        id<MTLRenderCommandEncoder> enc,
        const EffectRecord& fx,
        MbaaShaderPassId pass_id)
    {
        auto lookup_param = [&](const char* name, uint32_t fallback_stage) -> uint32_t {
            auto it = fx.texture_params.find(name);
            if (it != fx.texture_params.end() && it->second != 0u) {
                return it->second;
            }
            return bound_textures[fallback_stage];
        };

        uint32_t t0 = bound_textures[0];
        uint32_t t1 = bound_textures[1];
        uint32_t t2 = bound_textures[2];
        SamplerStateBlock s0 = sampler_states[0];
        SamplerStateBlock s1 = sampler_states[1];
        SamplerStateBlock s2 = sampler_states[2];
        auto set_linear = [](SamplerStateBlock& s) {
            s.mag_filter = 2; s.min_filter = 2; s.address_u = 3; s.address_v = 3;
        };
        auto set_point = [](SamplerStateBlock& s) {
            s.mag_filter = 1; s.min_filter = 1; s.address_u = 3; s.address_v = 3;
        };

        switch (pass_id) {
            case MBAA_PASS_SAKURA_BLOOM_UPDATE_P0:
                t0 = lookup_param("targetTex0", 0u); set_linear(s0); break;
            case MBAA_PASS_SAKURA_BLOOM_UPDATE_P1:
                t0 = lookup_param("targetTex1", 0u); set_linear(s0); break;
            case MBAA_PASS_BG_POINT_BLUR_P0:
                t0 = lookup_param("diffuse_texture", 0u); set_linear(s0); break;
            case MBAA_PASS_BG_POINT_BLUR_P1:
                t0 = lookup_param("temp_texture0", 0u); set_linear(s0);
                t1 = lookup_param("temp_texture1", 1u); set_linear(s1);
                t2 = lookup_param("normal_texture", 2u); set_linear(s2);
                break;
            case MBAA_PASS_FADE_EX0:
            case MBAA_PASS_FADE_EX1:
                t1 = lookup_param("tex_Fade", 1u); break;
            case MBAA_PASS_BLOOM_MAKE_P0:
                t0 = lookup_param("diffuse_texture", 0u); set_point(s0); break;
            case MBAA_PASS_BLOOM_MAKE_P1:
                t0 = lookup_param("temp_textureA", 0u); set_linear(s0); break;
            case MBAA_PASS_BLOOM_FILL:
                t0 = lookup_param("temp_textureB", 0u); set_point(s0); break;
            case MBAA_PASS_BLOOM_BLT:
                t0 = lookup_param("temp_textureB", 0u); set_linear(s0);
                t1 = lookup_param("src_texture", 1u);   set_point(s1);
                break;
            case MBAA_PASS_MONO_FILL:
                t0 = lookup_param("tex_r", 0u); break;
            case MBAA_PASS_NOISE_P0:
                t0 = lookup_param("diffuse_texture", 0u); set_point(s0);
                t1 = lookup_param("tex_Noise", 1u); break;
            case MBAA_PASS_NOISE_P1:
                t0 = lookup_param("temp_texture", 0u); break;
            case MBAA_PASS_NORMAL_P0:
            case MBAA_PASS_NORMAL_ANGLE_P0:
                t0 = lookup_param("normal_texture", 0u);  set_linear(s0);
                t1 = lookup_param("diffuse_texture", 1u); set_linear(s1);
                break;
            case MBAA_PASS_NORMAL_P1:
            case MBAA_PASS_NORMAL_ANGLE_P1:
                t0 = lookup_param("temp_texture", 0u);
                t1 = lookup_param("normal_texture", 1u); set_linear(s1);
                break;
            default:
                break;
        }

        [enc setFragmentTexture:resolve_stage_texture(mem, t0) atIndex:MBAA_TEX_STAGE0];
        [enc setFragmentTexture:resolve_stage_texture(mem, t1) atIndex:MBAA_TEX_STAGE1];
        [enc setFragmentTexture:resolve_stage_texture(mem, t2) atIndex:MBAA_TEX_STAGE2];
        [enc setFragmentSamplerState:get_sampler(s0) atIndex:0];
        [enc setFragmentSamplerState:get_sampler(s1) atIndex:1];
        [enc setFragmentSamplerState:get_sampler(s2) atIndex:2];
    }

    // -----------------------------------------------------------------------
    // Present Backbuffer (640x480) into Centered 4:3 Viewport (1000x750 in 1334x750)
    // -----------------------------------------------------------------------
    void present_backbuffer_to_layer() {
        end_active_encoder();
        if (!metal_layer || !device || !cmd_queue) {
            if (frame_cmd_buf != nil) {
                [frame_cmd_buf commit];
                frame_cmd_buf = nil;
            }
            return;
        }

        @autoreleasepool {
            id<CAMetalDrawable> drawable = [metal_layer nextDrawable];
            if (drawable == nil) {
                if (frame_cmd_buf != nil) {
                    [frame_cmd_buf commit];
                    frame_cmd_buf = nil;
                }
                return;
            }

            id<MTLTexture> dst_tex = drawable.texture;
            id<MTLTexture> bb_tex  = nil;
            if (backbuffer_surf_va != 0u) {
                auto it = surfaces.find(1u);
                if (it != surfaces.end()) {
                    bb_tex = it->second.mtl_tex;
                }
            }

            id<MTLCommandBuffer> cb = ensure_cmd_buffer();
            MTLRenderPassDescriptor* rpd = [MTLRenderPassDescriptor renderPassDescriptor];
            rpd.colorAttachments[0].texture     = dst_tex;
            rpd.colorAttachments[0].loadAction  = MTLLoadActionClear;
            rpd.colorAttachments[0].storeAction = MTLStoreActionStore;
            rpd.colorAttachments[0].clearColor  = MTLClearColorMake(0.0, 0.0, 0.0, 1.0);

            id<MTLRenderCommandEncoder> enc = [cb renderCommandEncoderWithDescriptor:rpd];
            if (enc != nil && bb_tex != nil) {
                const double dw = static_cast<double>(dst_tex.width);
                const double dh = static_cast<double>(dst_tex.height);
                const double vpW = std::min(dw, dh * (4.0 / 3.0));
                const double vpH = vpW * (3.0 / 4.0);
                const double vpX = (dw - vpW) * 0.5;
                const double vpY = (dh - vpH) * 0.5;

                MTLViewport mvp{vpX, vpY, vpW, vpH, 0.0, 1.0};
                [enc setViewport:mvp];

                PipelineCacheKey pkey{};
                pkey.pass_id = MBAA_PASS_PRESENT_BLIT;
                pkey.rt_fmt0 = static_cast<uint32_t>(dst_tex.pixelFormat);
                id<MTLRenderPipelineState> pso = get_pipeline(pkey);
                if (pso != nil) {
                    SamplerStateBlock sb{};
                    sb.address_u = 3; sb.address_v = 3; sb.mag_filter = 2; sb.min_filter = 2;
                    [enc setRenderPipelineState:pso];
                    [enc setFragmentTexture:bb_tex atIndex:MBAA_TEX_STAGE0];
                    [enc setFragmentSamplerState:get_sampler(sb) atIndex:0];
                    [enc drawPrimitives:MTLPrimitiveTypeTriangleStrip vertexStart:0 vertexCount:4];
                }
            }
            if (enc != nil) {
                [enc endEncoding];
            }
            [cb presentDrawable:drawable];
            [cb commit];
            frame_cmd_buf = nil;
        }
    }

    // -----------------------------------------------------------------------
    // COM Vtable Initializers (allocated once inside GuestMemory 0x00F00000..)
    // -----------------------------------------------------------------------
    void init_com_vtables(GuestMemory& mem);
};

// ---------------------------------------------------------------------------
// Global COM Thunk Dispatcher Bridge
// ---------------------------------------------------------------------------
namespace {

inline D3D9MetalBridge::Impl* active_impl() noexcept {
    D3D9MetalBridge* b = D3D9MetalBridge::active();
    return b ? b->impl_.get() : nullptr;
}

template <uint32_t TotalArgBytes, uint32_t ReturnValue = kS_OK>
void com_stub_ret(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = ReturnValue;
    ctx.ret_stdcall(mem, TotalArgBytes);
}

void com_unknown_query_interface(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t self_va = ctx.arg32(mem, 0);
    const uint32_t ppv_va  = ctx.arg32(mem, 2);
    if (ppv_va != 0u && mem.in_bounds(ppv_va, 4u)) {
        mem.w32(ppv_va, self_va);
    }
    if (self_va != 0u && mem.in_bounds(self_va + 8u, 4u)) {
        mem.w32(self_va + 8u, mem.r32(self_va + 8u) + 1u);
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

void com_unknown_addref(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t self_va = ctx.arg32(mem, 0);
    uint32_t rc = 1u;
    if (self_va != 0u && mem.in_bounds(self_va + 8u, 4u)) {
        rc = mem.r32(self_va + 8u) + 1u;
        mem.w32(self_va + 8u, rc);
    }
    ctx.eax = rc;
    ctx.ret_stdcall(mem, 4u);
}

void com_unknown_release(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t self_va = ctx.arg32(mem, 0);
    uint32_t rc = 0u;
    if (self_va != 0u && mem.in_bounds(self_va + 12u, 4u)) {
        rc = mem.r32(self_va + 8u);
        if (rc > 0u) --rc;
        mem.w32(self_va + 8u, rc);
        if (rc == 0u) {
            if (auto* im = active_impl()) {
                std::lock_guard<std::recursive_mutex> lk(im->mtx);
                const uint32_t hid  = mem.r32(self_va + 4u);
                const uint32_t kind = mem.r32(self_va + 12u);
                if (kind == kKindTexture) {
                    if (auto it = im->textures.find(hid); it != im->textures.end()) {
                        if (im->cached_texture_bytes >= it->second.gpu_bytes) {
                            im->cached_texture_bytes -= it->second.gpu_bytes;
                        } else {
                            im->cached_texture_bytes = 0u;
                        }
                        if (it->second.staging_va) mem.guest_free(it->second.staging_va);
                        im->textures.erase(it);
                    }
                } else if (kind == kKindSurface && hid > 2u) {
                    if (auto it = im->surfaces.find(hid); it != im->surfaces.end()) {
                        if (it->second.staging_va) mem.guest_free(it->second.staging_va);
                        im->surfaces.erase(it);
                    }
                } else if (kind == kKindEffect) {
                    im->effects.erase(hid);
                } else if (kind == kKindFont) {
                    if (auto it = im->fonts.find(hid); it != im->fonts.end()) {
                        if (it->second.ct_font) CFRelease(it->second.ct_font);
                        im->fonts.erase(it);
                    }
                } else if (kind == kKindVBuf || kind == kKindIBuf) {
                    if (auto it = im->buffers.find(hid); it != im->buffers.end()) {
                        if (it->second.data_va) mem.guest_free(it->second.data_va);
                        im->buffers.erase(it);
                    }
                }
            }
        }
    }
    ctx.eax = rc;
    ctx.ret_stdcall(mem, 4u);
}

// ---------------------------------------------------------------------------
// IDirect3D9 Methods
// ---------------------------------------------------------------------------
void com_d3d9_get_adapter_identifier(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pId_va = ctx.arg32(mem, 3);
    if (pId_va != 0u && mem.in_bounds(pId_va, 1100u)) {
        mem.zero_bytes(pId_va, 1100u);
        mem.write_cstring(pId_va + 0u,   "mbaa_metal_shim.dll", 512u);
        mem.write_cstring(pId_va + 512u, "Apple A13 Bionic GPU (Metal)", 512u);
        mem.w32(pId_va + 1072u, 0x106Bu); // Apple VendorId
        mem.w32(pId_va + 1076u, 0x0013u); // DeviceId
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 16u);
}

void com_d3d9_get_adapter_mode_count(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = 4u;
    ctx.ret_stdcall(mem, 12u);
}

void com_d3d9_enum_adapter_modes(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t fmt     = ctx.arg32(mem, 2);
    const uint32_t mode    = ctx.arg32(mem, 3);
    const uint32_t pModeVa = ctx.arg32(mem, 4);
    static constexpr uint32_t kWidths[4]  = {640u, 800u, 1024u, 1280u};
    static constexpr uint32_t kHeights[4] = {480u, 600u, 768u,  960u};
    if (mode >= 4u || pModeVa == 0u || !mem.in_bounds(pModeVa, 16u)) {
        ctx.eax = kD3DERR_INVALIDCALL;
        ctx.ret_stdcall(mem, 20u);
        return;
    }
    mem.w32(pModeVa + 0u,  kWidths[mode]);
    mem.w32(pModeVa + 4u,  kHeights[mode]);
    mem.w32(pModeVa + 8u,  60u);
    mem.w32(pModeVa + 12u, fmt ? fmt : kFmtX8R8G8B8);
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 20u);
}

void com_d3d9_get_adapter_display_mode(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pModeVa = ctx.arg32(mem, 2);
    if (pModeVa != 0u && mem.in_bounds(pModeVa, 16u)) {
        mem.w32(pModeVa + 0u,  640u);
        mem.w32(pModeVa + 4u,  480u);
        mem.w32(pModeVa + 8u,  60u);
        mem.w32(pModeVa + 12u, kFmtX8R8G8B8);
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

void fill_d3dcaps9(GuestMemory& mem, uint32_t caps_va) {
    if (caps_va == 0u || !mem.in_bounds(caps_va, 304u)) return;
    mem.zero_bytes(caps_va, 304u);
    mem.w32(caps_va + 0x00u, 1u);          // DeviceType = HAL
    mem.w32(caps_va + 0x04u, 0u);          // AdapterOrdinal
    mem.w32(caps_va + 0x08u, 0x00020000u); // Caps
    mem.w32(caps_va + 0x0Cu, 0x00000000u);
    mem.w32(caps_va + 0x10u, 0x000B0000u); // DevCaps (HWTRANSFORMANDLIGHT | HWRENDER)
    mem.w32(caps_va + 0x14u, 0x00030FFFu); // PrimitiveMiscCaps
    mem.w32(caps_va + 0x38u, 0x00000002u); // TextureCaps (POW2 not required)
    mem.w32(caps_va + 0x3Cu, 0x03030300u); // TextureFilterCaps
    mem.w32(caps_va + 0x6Cu, 4096u);       // MaxTextureWidth
    mem.w32(caps_va + 0x70u, 4096u);       // MaxTextureHeight
    mem.w32(caps_va + 0x94u, 8u);          // MaxTextureBlendStages
    mem.w32(caps_va + 0x98u, 8u);          // MaxSimultaneousTextures
    mem.w32(caps_va + 0xB8u, 0x00010000u); // MaxVertexIndex
    mem.w32(caps_va + 0xC4u, 0xFFFE0300u); // VertexShaderVersion = vs_3_0
    mem.w32(caps_va + 0xC8u, 256u);        // MaxVertexShaderConst
    mem.w32(caps_va + 0xCCu, 0xFFFF0300u); // PixelShaderVersion = ps_3_0
    mem.wf32(caps_va + 0xD0u, 8.0f);       // PixelShader1xMaxValue
    mem.w32(caps_va + 0x11Cu, 4u);         // NumSimultaneousRTs
}

void com_d3d9_get_device_caps(CpuContext& ctx, GuestMemory& mem) {
    fill_d3dcaps9(mem, ctx.arg32(mem, 3));
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 16u);
}

void com_d3d9_create_device(CpuContext& ctx, GuestMemory& mem) {
    // IDirect3D9::CreateDevice(this, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPP, ppDevice)
    const uint32_t pp_va      = ctx.arg32(mem, 5);
    const uint32_t pp_dev_va  = ctx.arg32(mem, 6);

    auto* im = active_impl();
    if (!im || pp_dev_va == 0u || !mem.in_bounds(pp_dev_va, 4u)) {
        ctx.eax = kE_FAIL;
        ctx.ret_stdcall(mem, 28u);
        return;
    }

    std::lock_guard<std::recursive_mutex> lk(im->mtx);
    uint32_t bb_w = 640u, bb_h = 480u;
    if (pp_va != 0u && mem.in_bounds(pp_va, 56u)) {
        const uint32_t req_w = mem.r32(pp_va + 0u);
        const uint32_t req_h = mem.r32(pp_va + 4u);
        if (req_w >= 64u && req_w <= 4096u && req_h >= 64u && req_h <= 4096u) {
            bb_w = req_w;
            bb_h = req_h;
        }
    }
    im->logical_width  = bb_w;
    im->logical_height = bb_h;
    im->vp_x = 0u;
    im->vp_y = 0u;
    im->vp_w = bb_w;
    im->vp_h = bb_h;

    if (im->device_guest_va == 0u) {
        im->device_guest_va = im->alloc_com_object(mem, im->vtbl_device, 1u, kKindDevice);
    }

    // Create offscreen Metal backbuffer surface (ID 1) and depth-stencil surface (ID 2)
    SurfaceRecord bb{};
    bb.id       = 1u;
    bb.width    = bb_w;
    bb.height   = bb_h;
    bb.format   = kFmtA8R8G8B8;
    bb.usage    = kUsageRenderTarget;
    bb.mtl_tex  = im->make_mtl_texture(bb_w, bb_h, MTLPixelFormatBGRA8Unorm, true, false);
    if (im->backbuffer_surf_va == 0u) {
        im->backbuffer_surf_va = im->alloc_com_object(mem, im->vtbl_surface, 1u, kKindSurface);
    }
    bb.guest_va = im->backbuffer_surf_va;
    im->surfaces[1u] = bb;

    im->depth_tex = im->make_mtl_texture(bb_w, bb_h, MTLPixelFormatDepth32Float_Stencil8, false, true);
    SurfaceRecord ds{};
    ds.id       = 2u;
    ds.width    = bb_w;
    ds.height   = bb_h;
    ds.format   = kFmtD24S8;
    ds.usage    = kUsageDepthStencil;
    ds.mtl_tex  = im->depth_tex;
    if (im->depth_surf_va == 0u) {
        im->depth_surf_va = im->alloc_com_object(mem, im->vtbl_surface, 2u, kKindSurface);
    }
    ds.guest_va = im->depth_surf_va;
    im->surfaces[2u] = ds;

    im->bound_rt_surfaces.fill(0u);
    im->bound_rt_surfaces[0] = im->backbuffer_surf_va;
    im->bound_ds_surface     = im->depth_surf_va;
    im->encoder_rt_dirty     = true;

    mem.w32(pp_dev_va, im->device_guest_va);
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 28u);
}

// ---------------------------------------------------------------------------
// IDirect3DDevice9 Methods
// ---------------------------------------------------------------------------
void com_dev_get_available_tex_mem(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = static_cast<uint32_t>(D3D9MetalBridge::kTextureCacheLimitBytes);
    ctx.ret_stdcall(mem, 4u);
}

void com_dev_evict_managed_resources(CpuContext& ctx, GuestMemory& mem) {
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        im->evict_lru_to_budget(64u * 1024u * 1024u);
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 4u);
}

void com_dev_get_direct3d(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pp_d3d_va = ctx.arg32(mem, 1);
    if (auto* im = active_impl(); im && pp_d3d_va && mem.in_bounds(pp_d3d_va, 4u)) {
        mem.w32(pp_d3d_va, im->d3d9_guest_va);
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void com_dev_get_device_caps(CpuContext& ctx, GuestMemory& mem) {
    fill_d3dcaps9(mem, ctx.arg32(mem, 1));
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void com_dev_get_display_mode(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pModeVa = ctx.arg32(mem, 2);
    if (pModeVa != 0u && mem.in_bounds(pModeVa, 16u)) {
        auto* im = active_impl();
        mem.w32(pModeVa + 0u, im ? im->logical_width  : 640u);
        mem.w32(pModeVa + 4u, im ? im->logical_height : 480u);
        mem.w32(pModeVa + 8u, 60u);
        mem.w32(pModeVa + 12u, kFmtX8R8G8B8);
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

void com_dev_reset(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pp_va = ctx.arg32(mem, 1);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        im->end_active_encoder();
        if (pp_va != 0u && mem.in_bounds(pp_va, 8u)) {
            const uint32_t rw = mem.r32(pp_va + 0u);
            const uint32_t rh = mem.r32(pp_va + 4u);
            if (rw >= 64u && rw <= 4096u && rh >= 64u && rh <= 4096u &&
                (rw != im->logical_width || rh != im->logical_height)) {
                im->logical_width  = rw;
                im->logical_height = rh;
                im->vp_x = 0u; im->vp_y = 0u; im->vp_w = rw; im->vp_h = rh;
                auto& bb = im->surfaces[1u];
                bb.width = rw; bb.height = rh;
                bb.mtl_tex = im->make_mtl_texture(rw, rh, MTLPixelFormatBGRA8Unorm, true, false);
                im->depth_tex = im->make_mtl_texture(rw, rh, MTLPixelFormatDepth32Float_Stencil8, false, true);
                im->surfaces[2u].width = rw; im->surfaces[2u].height = rh;
                im->surfaces[2u].mtl_tex = im->depth_tex;
            }
        }
        im->encoder_rt_dirty = true;
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void com_dev_present(CpuContext& ctx, GuestMemory& mem) {
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        im->end_active_encoder();
        im->guest_presented_this_frame = true;
        if (!im->in_frame) {
            // Outside MTKView step_frame() (e.g. startup notice): present immediately
            im->present_backbuffer_to_layer();
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 20u);
}

void com_dev_get_back_buffer(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pp_surf_va = ctx.arg32(mem, 4);
    if (auto* im = active_impl(); im && pp_surf_va && mem.in_bounds(pp_surf_va, 4u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        mem.w32(pp_surf_va, im->backbuffer_surf_va);
        mem.w32(im->backbuffer_surf_va + 8u, mem.r32(im->backbuffer_surf_va + 8u) + 1u);
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 20u);
}

uint32_t create_texture_internal(
    D3D9MetalBridge::Impl& im,
    GuestMemory& mem,
    uint32_t w,
    uint32_t h,
    uint32_t levels,
    uint32_t usage,
    uint32_t format,
    uint32_t pool)
{
    if (w == 0u) w = 1u;
    if (h == 0u) h = 1u;
    const bool is_rt = (usage & kUsageRenderTarget) != 0u;
    const bool is_ds = (usage & kUsageDepthStencil) != 0u;
    const MTLPixelFormat mfmt = d3d_fmt_to_mtl(format);

    TextureRecord rec{};
    rec.id               = ++im.next_handle_id;
    rec.width            = w;
    rec.height           = h;
    rec.levels           = levels ? levels : 1u;
    rec.usage            = usage;
    rec.format           = format ? format : kFmtA8R8G8B8;
    rec.pool             = pool;
    rec.is_render_target = is_rt;
    rec.is_depth_stencil = is_ds;
    rec.last_used_tick   = ++im.lru_clock;
    rec.mtl_tex          = im.make_mtl_texture(w, h, mfmt, is_rt, is_ds);

    const uint32_t m_bpp = (mfmt == MTLPixelFormatA8Unorm || mfmt == MTLPixelFormatR8Unorm) ? 1u : 4u;
    rec.gpu_bytes = static_cast<size_t>(w) * h * m_bpp;
    if (!is_rt && !is_ds) {
        im.cached_texture_bytes += rec.gpu_bytes;
        im.evict_lru_to_budget(D3D9MetalBridge::kTextureCacheLimitBytes);
    }

    rec.guest_va = im.alloc_com_object(mem, im.vtbl_texture, rec.id, kKindTexture);
    im.textures[rec.id] = std::move(rec);
    return im.textures[rec.id].guest_va;
}

void com_dev_create_texture(CpuContext& ctx, GuestMemory& mem) {
    // (this, Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle) -> 36 bytes
    const uint32_t w        = ctx.arg32(mem, 1);
    const uint32_t h        = ctx.arg32(mem, 2);
    const uint32_t levels   = ctx.arg32(mem, 3);
    const uint32_t usage    = ctx.arg32(mem, 4);
    const uint32_t format   = ctx.arg32(mem, 5);
    const uint32_t pool     = ctx.arg32(mem, 6);
    const uint32_t pp_tex   = ctx.arg32(mem, 7);

    if (auto* im = active_impl(); im && pp_tex && mem.in_bounds(pp_tex, 4u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        const uint32_t tva = create_texture_internal(*im, mem, w, h, levels, usage, format, pool);
        mem.w32(pp_tex, tva);
        ctx.eax = kS_OK;
    } else {
        ctx.eax = kD3DERR_INVALIDCALL;
    }
    ctx.ret_stdcall(mem, 36u);
}

void com_dev_create_render_target(CpuContext& ctx, GuestMemory& mem) {
    // (this, Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle) -> 36 bytes
    const uint32_t w       = ctx.arg32(mem, 1);
    const uint32_t h       = ctx.arg32(mem, 2);
    const uint32_t fmt     = ctx.arg32(mem, 3);
    const uint32_t pp_surf = ctx.arg32(mem, 7);
    if (auto* im = active_impl(); im && pp_surf && mem.in_bounds(pp_surf, 4u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        SurfaceRecord sr{};
        sr.id       = ++im->next_handle_id;
        sr.width    = w ? w : 640u;
        sr.height   = h ? h : 480u;
        sr.format   = fmt ? fmt : kFmtA8R8G8B8;
        sr.usage    = kUsageRenderTarget;
        sr.mtl_tex  = im->make_mtl_texture(sr.width, sr.height, d3d_fmt_to_mtl(sr.format), true, false);
        sr.guest_va = im->alloc_com_object(mem, im->vtbl_surface, sr.id, kKindSurface);
        im->surfaces[sr.id] = sr;
        mem.w32(pp_surf, sr.guest_va);
        ctx.eax = kS_OK;
    } else {
        ctx.eax = kD3DERR_INVALIDCALL;
    }
    ctx.ret_stdcall(mem, 36u);
}

void com_dev_create_depth_stencil_surface(CpuContext& ctx, GuestMemory& mem) {
    // (this, Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle) -> 36 bytes
    const uint32_t w       = ctx.arg32(mem, 1);
    const uint32_t h       = ctx.arg32(mem, 2);
    const uint32_t fmt     = ctx.arg32(mem, 3);
    const uint32_t pp_surf = ctx.arg32(mem, 7);
    if (auto* im = active_impl(); im && pp_surf && mem.in_bounds(pp_surf, 4u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        SurfaceRecord sr{};
        sr.id       = ++im->next_handle_id;
        sr.width    = w ? w : 640u;
        sr.height   = h ? h : 480u;
        sr.format   = fmt ? fmt : kFmtD24S8;
        sr.usage    = kUsageDepthStencil;
        sr.mtl_tex  = im->make_mtl_texture(sr.width, sr.height, MTLPixelFormatDepth32Float_Stencil8, false, true);
        sr.guest_va = im->alloc_com_object(mem, im->vtbl_surface, sr.id, kKindSurface);
        im->surfaces[sr.id] = sr;
        mem.w32(pp_surf, sr.guest_va);
        ctx.eax = kS_OK;
    } else {
        ctx.eax = kD3DERR_INVALIDCALL;
    }
    ctx.ret_stdcall(mem, 36u);
}

void com_dev_create_offscreen_plain_surface(CpuContext& ctx, GuestMemory& mem) {
    // (this, Width, Height, Format, Pool, ppSurface, pSharedHandle) -> 28 bytes
    const uint32_t w       = ctx.arg32(mem, 1);
    const uint32_t h       = ctx.arg32(mem, 2);
    const uint32_t fmt     = ctx.arg32(mem, 3);
    const uint32_t pp_surf = ctx.arg32(mem, 5);
    if (auto* im = active_impl(); im && pp_surf && mem.in_bounds(pp_surf, 4u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        SurfaceRecord sr{};
        sr.id       = ++im->next_handle_id;
        sr.width    = w ? w : 640u;
        sr.height   = h ? h : 480u;
        sr.format   = fmt ? fmt : kFmtA8R8G8B8;
        sr.mtl_tex  = im->make_mtl_texture(sr.width, sr.height, d3d_fmt_to_mtl(sr.format), false, false);
        sr.guest_va = im->alloc_com_object(mem, im->vtbl_surface, sr.id, kKindSurface);
        im->surfaces[sr.id] = sr;
        mem.w32(pp_surf, sr.guest_va);
        ctx.eax = kS_OK;
    } else {
        ctx.eax = kD3DERR_INVALIDCALL;
    }
    ctx.ret_stdcall(mem, 28u);
}

void com_dev_set_render_target(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t idx     = ctx.arg32(mem, 1);
    const uint32_t surf_va = ctx.arg32(mem, 2);
    if (auto* im = active_impl(); im && idx < im->bound_rt_surfaces.size()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (im->bound_rt_surfaces[idx] != surf_va) {
            im->end_active_encoder();
            im->bound_rt_surfaces[idx] = surf_va;
            im->encoder_rt_dirty = true;
            if (idx == 0u) {
                if (SurfaceRecord* sr = im->find_surface_by_va(mem, surf_va)) {
                    im->vp_x = 0u; im->vp_y = 0u; im->vp_w = sr->width; im->vp_h = sr->height;
                }
            }
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

void com_dev_get_render_target(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t idx     = ctx.arg32(mem, 1);
    const uint32_t pp_surf = ctx.arg32(mem, 2);
    if (auto* im = active_impl(); im && idx < im->bound_rt_surfaces.size() && pp_surf && mem.in_bounds(pp_surf, 4u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        const uint32_t sva = im->bound_rt_surfaces[idx];
        mem.w32(pp_surf, sva);
        if (sva != 0u) mem.w32(sva + 8u, mem.r32(sva + 8u) + 1u);
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

void com_dev_set_depth_stencil(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t surf_va = ctx.arg32(mem, 1);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (im->bound_ds_surface != surf_va) {
            im->end_active_encoder();
            im->bound_ds_surface = surf_va;
            im->encoder_rt_dirty = true;
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void com_dev_get_depth_stencil(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pp_surf = ctx.arg32(mem, 1);
    if (auto* im = active_impl(); im && pp_surf && mem.in_bounds(pp_surf, 4u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        mem.w32(pp_surf, im->bound_ds_surface);
        if (im->bound_ds_surface != 0u) {
            mem.w32(im->bound_ds_surface + 8u, mem.r32(im->bound_ds_surface + 8u) + 1u);
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void com_dev_begin_scene(CpuContext& ctx, GuestMemory& mem) {
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        im->in_scene = true;
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 4u);
}

void com_dev_end_scene(CpuContext& ctx, GuestMemory& mem) {
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        im->end_active_encoder();
        im->in_scene = false;
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 4u);
}

void com_dev_clear(CpuContext& ctx, GuestMemory& mem) {
    // (this, Count, pRects, Flags, Color, Z, Stencil) -> 28 bytes
    const uint32_t flags = ctx.arg32(mem, 3);
    const uint32_t color = ctx.arg32(mem, 4);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        im->end_active_encoder();
        im->encoder_rt_dirty = true;
        im->ensure_render_encoder(mem, 1u, (flags & 1u) != 0u, color, (flags & 2u) != 0u);
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 28u);
}

void com_dev_set_transform(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t state  = ctx.arg32(mem, 1);
    const uint32_t mat_va = ctx.arg32(mem, 2);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        const auto m = read_matrix(mem, mat_va);
        if (state == 2u)      im->mat_view  = m;
        else if (state == 3u) im->mat_proj  = m;
        else                  im->mat_world = m;
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

void com_dev_get_transform(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t state  = ctx.arg32(mem, 1);
    const uint32_t mat_va = ctx.arg32(mem, 2);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (state == 2u)      write_matrix(mem, mat_va, im->mat_view);
        else if (state == 3u) write_matrix(mem, mat_va, im->mat_proj);
        else                  write_matrix(mem, mat_va, im->mat_world);
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

void com_dev_set_viewport(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t vp_va = ctx.arg32(mem, 1);
    if (auto* im = active_impl(); im && vp_va && mem.in_bounds(vp_va, 24u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        im->vp_x = mem.r32(vp_va + 0u);
        im->vp_y = mem.r32(vp_va + 4u);
        im->vp_w = mem.r32(vp_va + 8u);
        im->vp_h = mem.r32(vp_va + 12u);
        if (im->active_encoder != nil) {
            MTLViewport mvp{
                static_cast<double>(im->vp_x), static_cast<double>(im->vp_y),
                static_cast<double>(im->vp_w), static_cast<double>(im->vp_h), 0.0, 1.0
            };
            [im->active_encoder setViewport:mvp];
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void com_dev_get_viewport(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t vp_va = ctx.arg32(mem, 1);
    if (auto* im = active_impl(); im && vp_va && mem.in_bounds(vp_va, 24u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        mem.w32(vp_va + 0u, im->vp_x);
        mem.w32(vp_va + 4u, im->vp_y);
        mem.w32(vp_va + 8u, im->vp_w);
        mem.w32(vp_va + 12u, im->vp_h);
        mem.wf32(vp_va + 16u, 0.0f);
        mem.wf32(vp_va + 20u, 1.0f);
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void com_dev_set_render_state(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t st  = ctx.arg32(mem, 1);
    const uint32_t val = ctx.arg32(mem, 2);
    if (auto* im = active_impl(); im && st < im->render_states.size()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        im->render_states[st] = val;
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

void com_dev_get_render_state(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t st   = ctx.arg32(mem, 1);
    const uint32_t pVal = ctx.arg32(mem, 2);
    if (auto* im = active_impl(); im && st < im->render_states.size() && pVal && mem.in_bounds(pVal, 4u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        mem.w32(pVal, im->render_states[st]);
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

void com_dev_get_texture(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t stage = ctx.arg32(mem, 1);
    const uint32_t ppTex = ctx.arg32(mem, 2);
    if (auto* im = active_impl(); im && stage < im->bound_textures.size() && ppTex && mem.in_bounds(ppTex, 4u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        mem.w32(ppTex, im->bound_textures[stage]);
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

void com_dev_set_texture(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t stage  = ctx.arg32(mem, 1);
    const uint32_t tex_va = ctx.arg32(mem, 2);
    if (auto* im = active_impl(); im && stage < im->bound_textures.size()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        im->bound_textures[stage] = tex_va;
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

void com_dev_set_tss(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t stage = ctx.arg32(mem, 1);
    const uint32_t type  = ctx.arg32(mem, 2);
    const uint32_t val   = ctx.arg32(mem, 3);
    if (auto* im = active_impl(); im && stage < im->tss_stage0_colorop.size()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (type == 1u) im->tss_stage0_colorop[stage] = val;
        if (type == 4u) im->tss_stage0_alphaop[stage] = val;
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 16u);
}

void com_dev_set_sampler_state(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t stage = ctx.arg32(mem, 1);
    const uint32_t type  = ctx.arg32(mem, 2);
    const uint32_t val   = ctx.arg32(mem, 3);
    if (auto* im = active_impl(); im && stage < im->sampler_states.size()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        auto& s = im->sampler_states[stage];
        if (type == 1u) s.address_u  = val;
        if (type == 2u) s.address_v  = val;
        if (type == 5u) s.mag_filter = val;
        if (type == 6u) s.min_filter = val;
        if (type == 7u) s.mip_filter = val;
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 16u);
}

void com_dev_set_scissor_rect(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t rva = ctx.arg32(mem, 1);
    if (auto* im = active_impl(); im && rva && mem.in_bounds(rva, 16u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (im->active_encoder != nil && im->render_states[kRsScissorTestEnable]) {
            const uint32_t l = mem.r32(rva + 0u), t = mem.r32(rva + 4u);
            const uint32_t r = mem.r32(rva + 8u), b = mem.r32(rva + 12u);
            if (r > l && b > t) {
                [im->active_encoder setScissorRect:MTLScissorRect{l, t, r - l, b - t}];
            }
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

inline uint32_t vertex_count_for_prim(uint32_t prim_type, uint32_t prim_count) noexcept {
    switch (prim_type) {
        case kPtPointList:     return prim_count;
        case kPtLineList:      return prim_count * 2u;
        case kPtLineStrip:     return prim_count + 1u;
        case kPtTriangleStrip: return prim_count + 2u;
        case kPtTriangleFan:   return prim_count + 2u;
        case kPtTriangleList:
        default:               return prim_count * 3u;
    }
}

void com_dev_draw_primitive_up(CpuContext& ctx, GuestMemory& mem) {
    // (this, PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride) -> 20 bytes
    const uint32_t prim_type  = ctx.arg32(mem, 1);
    const uint32_t prim_count = ctx.arg32(mem, 2);
    const uint32_t vdata_va   = ctx.arg32(mem, 3);
    const uint32_t stride     = ctx.arg32(mem, 4);
    const uint32_t vcount     = vertex_count_for_prim(prim_type, prim_count);
    if (auto* im = active_impl(); im && vdata_va && vcount > 0u && stride > 0u &&
        mem.in_bounds(vdata_va, static_cast<size_t>(vcount) * stride)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        im->execute_draw(mem, prim_type, prim_count, mem.cptr(vdata_va), vcount, stride, nullptr, 0u);
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 20u);
}

void com_dev_draw_indexed_primitive_up(CpuContext& ctx, GuestMemory& mem) {
    // (this, PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexData, Stride) -> 36 bytes
    const uint32_t prim_type  = ctx.arg32(mem, 1);
    const uint32_t min_vidx   = ctx.arg32(mem, 2);
    const uint32_t num_verts  = ctx.arg32(mem, 3);
    const uint32_t prim_count = ctx.arg32(mem, 4);
    const uint32_t idata_va   = ctx.arg32(mem, 5);
    const uint32_t idx_fmt    = ctx.arg32(mem, 6);
    const uint32_t vdata_va   = ctx.arg32(mem, 7);
    const uint32_t stride     = ctx.arg32(mem, 8);
    const uint32_t total_verts = min_vidx + num_verts;
    if (auto* im = active_impl(); im && vdata_va && idata_va && total_verts > 0u && stride > 0u &&
        mem.in_bounds(vdata_va, static_cast<size_t>(total_verts) * stride)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        im->execute_draw(mem, prim_type, prim_count, mem.cptr(vdata_va), total_verts, stride, mem.cptr(idata_va), idx_fmt);
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 36u);
}

void com_dev_draw_primitive(CpuContext& ctx, GuestMemory& mem) {
    // (this, PrimitiveType, StartVertex, PrimitiveCount) -> 16 bytes
    const uint32_t prim_type  = ctx.arg32(mem, 1);
    const uint32_t start_v    = ctx.arg32(mem, 2);
    const uint32_t prim_count = ctx.arg32(mem, 3);
    if (auto* im = active_impl(); im && im->current_vb_va && im->current_vb_stride) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        const uint32_t vcount = vertex_count_for_prim(prim_type, prim_count);
        const uint32_t base_va = im->current_vb_va + start_v * im->current_vb_stride;
        if (mem.in_bounds(base_va, static_cast<size_t>(vcount) * im->current_vb_stride)) {
            im->execute_draw(mem, prim_type, prim_count, mem.cptr(base_va), vcount, im->current_vb_stride, nullptr, 0u);
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 16u);
}

void com_dev_set_fvf(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t fvf = ctx.arg32(mem, 1);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        im->current_fvf = fvf;
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void com_dev_get_fvf(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pFvf = ctx.arg32(mem, 1);
    if (auto* im = active_impl(); im && pFvf && mem.in_bounds(pFvf, 4u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        mem.w32(pFvf, im->current_fvf);
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void com_dev_set_stream_source(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t stream = ctx.arg32(mem, 1);
    const uint32_t vb_va  = ctx.arg32(mem, 2);
    const uint32_t off_b  = ctx.arg32(mem, 3);
    const uint32_t stride = ctx.arg32(mem, 4);
    if (auto* im = active_impl(); im && stream == 0u) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        im->current_vb_va     = vb_va ? (mem.r32(vb_va + 4u) + off_b) : 0u;
        im->current_vb_stride = stride;
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 20u);
}

// ---------------------------------------------------------------------------
// IDirect3DTexture9 & IDirect3DSurface9 Methods
// ---------------------------------------------------------------------------
void write_d3d_surface_desc(GuestMemory& mem, uint32_t desc_va, uint32_t w, uint32_t h, uint32_t fmt, uint32_t usage, uint32_t type) {
    if (desc_va == 0u || !mem.in_bounds(desc_va, 32u)) return;
    mem.w32(desc_va + 0u,  fmt);
    mem.w32(desc_va + 4u,  type);
    mem.w32(desc_va + 8u,  usage);
    mem.w32(desc_va + 12u, 1u); // D3DPOOL_MANAGED
    mem.w32(desc_va + 16u, 0u);
    mem.w32(desc_va + 20u, 0u);
    mem.w32(desc_va + 24u, w);
    mem.w32(desc_va + 28u, h);
}

void com_tex_get_level_desc(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t tex_va  = ctx.arg32(mem, 0);
    const uint32_t level   = ctx.arg32(mem, 1);
    const uint32_t desc_va = ctx.arg32(mem, 2);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (TextureRecord* tr = im->find_texture_by_va(mem, tex_va)) {
            const uint32_t lw = std::max(1u, tr->width >> level);
            const uint32_t lh = std::max(1u, tr->height >> level);
            write_d3d_surface_desc(mem, desc_va, lw, lh, tr->format, tr->usage, 3u);
            ctx.eax = kS_OK;
            ctx.ret_stdcall(mem, 12u);
            return;
        }
    }
    ctx.eax = kD3DERR_INVALIDCALL;
    ctx.ret_stdcall(mem, 12u);
}

void com_tex_get_surface_level(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t tex_va  = ctx.arg32(mem, 0);
    const uint32_t level   = ctx.arg32(mem, 1);
    const uint32_t pp_surf = ctx.arg32(mem, 2);
    if (auto* im = active_impl(); im && pp_surf && mem.in_bounds(pp_surf, 4u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (TextureRecord* tr = im->find_texture_by_va(mem, tex_va)) {
            if (level == 0u && tr->surface_guest_va != 0u) {
                mem.w32(pp_surf, tr->surface_guest_va);
                mem.w32(tr->surface_guest_va + 8u, mem.r32(tr->surface_guest_va + 8u) + 1u);
                ctx.eax = kS_OK;
                ctx.ret_stdcall(mem, 12u);
                return;
            }
            SurfaceRecord sr{};
            sr.id            = ++im->next_handle_id;
            sr.parent_tex_id = tr->id;
            sr.mip_level     = level;
            sr.width         = std::max(1u, tr->width >> level);
            sr.height        = std::max(1u, tr->height >> level);
            sr.format        = tr->format;
            sr.usage         = tr->usage;
            sr.mtl_tex       = tr->mtl_tex;
            sr.guest_va      = im->alloc_com_object(mem, im->vtbl_surface, sr.id, kKindSurface);
            if (level == 0u) tr->surface_guest_va = sr.guest_va;
            im->surfaces[sr.id] = sr;
            mem.w32(pp_surf, sr.guest_va);
            ctx.eax = kS_OK;
            ctx.ret_stdcall(mem, 12u);
            return;
        }
    }
    ctx.eax = kD3DERR_INVALIDCALL;
    ctx.ret_stdcall(mem, 12u);
}

void com_tex_lock_rect(CpuContext& ctx, GuestMemory& mem) {
    // (this, Level, pLockedRect, pRect, Flags) -> 20 bytes
    const uint32_t tex_va     = ctx.arg32(mem, 0);
    const uint32_t locked_va  = ctx.arg32(mem, 2);
    if (auto* im = active_impl(); im && locked_va && mem.in_bounds(locked_va, 8u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (TextureRecord* tr = im->find_texture_by_va(mem, tex_va)) {
            const uint32_t bpp = bytes_per_pixel_for_d3d_fmt(tr->format);
            const uint32_t pitch = tr->width * bpp;
            const uint32_t bytes = pitch * tr->height;
            if (tr->staging_va == 0u || tr->staging_bytes < bytes) {
                if (tr->staging_va) mem.guest_free(tr->staging_va);
                tr->staging_va    = mem.guest_alloc(bytes, 16u);
                tr->staging_pitch = pitch;
                tr->staging_bytes = bytes;
                mem.zero_bytes(tr->staging_va, bytes);
            }
            tr->locked = true;
            mem.w32(locked_va + 0u, tr->staging_pitch);
            mem.w32(locked_va + 4u, tr->staging_va);
            ctx.eax = kS_OK;
            ctx.ret_stdcall(mem, 20u);
            return;
        }
    }
    ctx.eax = kD3DERR_INVALIDCALL;
    ctx.ret_stdcall(mem, 20u);
}

void upload_staging_to_texture(D3D9MetalBridge::Impl& im, const GuestMemory& mem, TextureRecord& tr) {
    if (!tr.staging_va || !mem.in_bounds(tr.staging_va, tr.staging_bytes)) return;
    const MTLPixelFormat mfmt = d3d_fmt_to_mtl(tr.format);
    if (tr.mtl_tex == nil) {
        tr.mtl_tex = im.make_mtl_texture(tr.width, tr.height, mfmt, tr.is_render_target, tr.is_depth_stencil);
    }
    if (tr.mtl_tex == nil) return;

    std::vector<uint8_t> conv;
    uint32_t out_pitch = 0u;
    convert_staging_to_mtl_pixels(tr.format, tr.width, tr.height,
                                  mem.cptr(tr.staging_va), tr.staging_pitch, conv, out_pitch);
    [tr.mtl_tex replaceRegion:MTLRegionMake2D(0, 0, tr.width, tr.height)
                    mipmapLevel:0
                      withBytes:conv.data()
                    bytesPerRow:out_pitch];
    tr.cpu_backup = std::move(conv);
    tr.evicted    = false;
    tr.last_used_tick = ++im.lru_clock;
}

void com_tex_unlock_rect(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t tex_va = ctx.arg32(mem, 0);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (TextureRecord* tr = im->find_texture_by_va(mem, tex_va)) {
            tr->locked = false;
            upload_staging_to_texture(*im, mem, *tr);
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void com_surf_get_desc(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t surf_va = ctx.arg32(mem, 0);
    const uint32_t desc_va = ctx.arg32(mem, 1);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (SurfaceRecord* sr = im->find_surface_by_va(mem, surf_va)) {
            write_d3d_surface_desc(mem, desc_va, sr->width, sr->height, sr->format, sr->usage, 1u);
            ctx.eax = kS_OK;
            ctx.ret_stdcall(mem, 8u);
            return;
        }
    }
    ctx.eax = kD3DERR_INVALIDCALL;
    ctx.ret_stdcall(mem, 8u);
}

void com_surf_lock_rect(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t surf_va   = ctx.arg32(mem, 0);
    const uint32_t locked_va = ctx.arg32(mem, 1);
    if (auto* im = active_impl(); im && locked_va && mem.in_bounds(locked_va, 8u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (SurfaceRecord* sr = im->find_surface_by_va(mem, surf_va)) {
            if (sr->parent_tex_id != 0u) {
                if (auto tit = im->textures.find(sr->parent_tex_id); tit != im->textures.end()) {
                    auto& tr = tit->second;
                    const uint32_t pitch = tr.width * bytes_per_pixel_for_d3d_fmt(tr.format);
                    const uint32_t bytes = pitch * tr.height;
                    if (!tr.staging_va || tr.staging_bytes < bytes) {
                        if (tr.staging_va) mem.guest_free(tr.staging_va);
                        tr.staging_va = mem.guest_alloc(bytes, 16u);
                        tr.staging_pitch = pitch;
                        tr.staging_bytes = bytes;
                    }
                    tr.locked = true;
                    mem.w32(locked_va + 0u, tr.staging_pitch);
                    mem.w32(locked_va + 4u, tr.staging_va);
                    ctx.eax = kS_OK;
                    ctx.ret_stdcall(mem, 16u);
                    return;
                }
            }
            const uint32_t pitch = sr->width * 4u;
            const uint32_t bytes = pitch * sr->height;
            if (!sr->staging_va || sr->staging_bytes < bytes) {
                if (sr->staging_va) mem.guest_free(sr->staging_va);
                sr->staging_va = mem.guest_alloc(bytes, 16u);
                sr->staging_pitch = pitch;
                sr->staging_bytes = bytes;
            }
            sr->locked = true;
            mem.w32(locked_va + 0u, sr->staging_pitch);
            mem.w32(locked_va + 4u, sr->staging_va);
            ctx.eax = kS_OK;
            ctx.ret_stdcall(mem, 16u);
            return;
        }
    }
    ctx.eax = kD3DERR_INVALIDCALL;
    ctx.ret_stdcall(mem, 16u);
}

void com_surf_unlock_rect(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t surf_va = ctx.arg32(mem, 0);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (SurfaceRecord* sr = im->find_surface_by_va(mem, surf_va)) {
            sr->locked = false;
            if (sr->parent_tex_id != 0u) {
                if (auto tit = im->textures.find(sr->parent_tex_id); tit != im->textures.end()) {
                    tit->second.locked = false;
                    upload_staging_to_texture(*im, mem, tit->second);
                }
            } else if (sr->mtl_tex != nil && sr->staging_va != 0u &&
                       sr->mtl_tex.storageMode == MTLStorageModeShared) {
                [sr->mtl_tex replaceRegion:MTLRegionMake2D(0, 0, sr->width, sr->height)
                                mipmapLevel:0
                                  withBytes:mem.cptr(sr->staging_va)
                                bytesPerRow:sr->staging_pitch];
            }
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 4u);
}

// ---------------------------------------------------------------------------
// ID3DXEffect Methods
// ---------------------------------------------------------------------------
std::string resolve_effect_param_name(const EffectRecord& fx, const GuestMemory& mem, uint32_t hparam) {
    if (hparam == 0u) return {};
    if (hparam <= fx.parameters.size()) {
        return fx.parameters[hparam - 1u];
    }
    return mem.read_cstring(hparam, 128u);
}

void apply_effect_param_value(
    D3D9MetalBridge::Impl& im,
    EffectRecord& fx,
    const GuestMemory& mem,
    const std::string& name,
    uint32_t data_va,
    uint32_t bytes)
{
    if (name.empty() || data_va == 0u || !mem.in_bounds(data_va, std::max<uint32_t>(4u, bytes))) return;

    auto read_f = [&](uint32_t idx) -> float {
        return (idx * 4u + 4u <= bytes) ? mem.rf32(data_va + idx * 4u) : 0.0f;
    };

    // Check if parameter refers to a texture handle (4 bytes matching a known guest Texture VA)
    if (bytes == 4u) {
        const uint32_t maybe_va = mem.r32(data_va);
        if (maybe_va == 0u || im.find_texture_by_va(mem, maybe_va) != nullptr) {
            if (name.find("tex") != std::string::npos || name.find("Tex") != std::string::npos ||
                name.find("Target") != std::string::npos || name.find("Diffuse") != std::string::npos) {
                if (name.find("texel") == std::string::npos && name.find("Texel") == std::string::npos &&
                    name.find("TexOff") == std::string::npos && name.find("TexWeight") == std::string::npos) {
                    fx.texture_params[name] = maybe_va;
                    return;
                }
            }
        }
    }

    auto& u = fx.uniforms;
    if (name == "bloom_texelA")       { u.bloom_texelA = {read_f(0), read_f(1), 0.0f, 0.0f}; }
    else if (name == "bloom_texelB")  { u.bloom_texelB = {read_f(0), read_f(1), 0.0f, 0.0f}; }
    else if (name == "diff_uv")       { u.diff_uv = {read_f(0), read_f(1), 0.0f, 0.0f}; }
    else if (name == "diff_wh")       { u.diff_wh = {read_f(0), read_f(1), 0.0f, 0.0f}; }
    else if (name == "diff_texel")    { u.diff_texel = {read_f(0), read_f(1), 0.0f, 0.0f}; }
    else if (name == "diff_centeruv") { u.diff_centeruv = {read_f(0), read_f(1), 0.0f, 0.0f}; }
    else if (name == "diff_size")     { u.diff_size = {read_f(0), read_f(1), 0.0f, 0.0f}; }
    else if (name == "src_uv")        { u.src_uv = {read_f(0), read_f(1), 0.0f, 0.0f}; }
    else if (name == "src_wh")        { u.src_wh = {read_f(0), read_f(1), 0.0f, 0.0f}; }
    else if (name == "diff_texel_matrix") {
        u.diff_texel_matrix0 = {read_f(0), read_f(1), 0.0f, 0.0f};
        u.diff_texel_matrix1 = {read_f(2), read_f(3), 0.0f, 0.0f};
    }
    else if (name == "fTexelX")       { u.texel_xy_n.x = read_f(0); u.texel_xy_n.y = read_f(1); }
    else if (name == "fTexelN")       { u.texel_xy_n.z = read_f(0); u.texel_xy_n.w = read_f(1); }
    else if (name == "fEdgeColor")    { u.edge_color = {read_f(0), read_f(1), read_f(2), read_f(3)}; }
    else if (name == "fPower") {
        if (bytes >= 16u) u.power_vec = {read_f(0), read_f(1), read_f(2), read_f(3)};
        else              u.power_vec = {read_f(0), read_f(0), read_f(0), 1.0f};
    }
    else if (name == "fValue")        { u.scalar_params.x = read_f(0); }
    else if (name == "fShift")        { u.scalar_params.y = read_f(0); }
    else if (name == "fColorHosei")   { u.scalar_params.z = read_f(0); }
    else if (name == "fSU")           { u.scalar_params.w = read_f(0); }
    else if (name == "fWidth")        { u.gauge_params.x  = read_f(0); }
    else if (name == "fColor")        { u.gauge_params.y  = read_f(0); }
    else if (name == "fUVSample")     { u.gauge_params.z  = read_f(0); }
    else if (name == "g_fTexel")      { u.g_texel.x = read_f(0); u.g_texel.y = read_f(1); }
    else if (name == "fRollTexel")    { u.g_texel.z = read_f(0); u.g_texel.w = read_f(1); }
    else if (name == "fTexOff") {
        const uint32_t cnt = std::min<uint32_t>(15u, bytes / 8u);
        for (uint32_t i = 0; i < cnt; ++i) {
            u.tex_off[i] = {read_f(i * 2u), read_f(i * 2u + 1u), 0.0f, 0.0f};
        }
    }
    else if (name == "fTexWeight") {
        const uint32_t cnt = std::min<uint32_t>(15u, bytes / 16u);
        for (uint32_t i = 0; i < cnt; ++i) {
            u.tex_weight[i] = {read_f(i * 4u), read_f(i * 4u + 1u), read_f(i * 4u + 2u), read_f(i * 4u + 3u)};
        }
    }
    else if (name == "worldViewProj") {
        im.mat_world = read_matrix(mem, data_va);
        im.mat_view  = identity_matrix();
        im.mat_proj  = identity_matrix();
    }
}

void apply_effect_scalar_float(EffectRecord& fx, const std::string& name, float v) noexcept {
    if (name.empty()) return;
    auto& u = fx.uniforms;
    if (name == "fPower")           { u.power_vec = {v, v, v, 1.0f}; }
    else if (name == "fValue")      { u.scalar_params.x = v; }
    else if (name == "fShift")      { u.scalar_params.y = v; }
    else if (name == "fColorHosei") { u.scalar_params.z = v; }
    else if (name == "fSU")         { u.scalar_params.w = v; }
    else if (name == "fWidth")      { u.gauge_params.x  = v; }
    else if (name == "fColor")      { u.gauge_params.y  = v; }
    else if (name == "fUVSample")   { u.gauge_params.z  = v; }
}

void com_fx_get_technique_by_name(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t fx_va   = ctx.arg32(mem, 0);
    const uint32_t name_va = ctx.arg32(mem, 1);
    uint32_t out_handle = 0u;
    if (auto* im = active_impl(); im && name_va) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (EffectRecord* fx = im->find_effect_by_va(mem, fx_va)) {
            const std::string tname = mem.read_cstring(name_va, 128u);
            auto it = fx->tech_handles.find(tname);
            if (it != fx->tech_handles.end()) {
                out_handle = it->second;
            } else if (shader_manifest::find_technique_pass(tname.c_str(), 0u) != nullptr) {
                const uint32_t th = static_cast<uint32_t>(fx->techniques.size() + 1u);
                fx->techniques.push_back(tname);
                fx->tech_handles[tname] = th;
                out_handle = th;
            }
        }
    }
    ctx.eax = out_handle;
    ctx.ret_stdcall(mem, 8u);
}

void com_fx_get_parameter_by_name(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t fx_va   = ctx.arg32(mem, 0);
    const uint32_t name_va = ctx.arg32(mem, 2);
    uint32_t out_handle = 0u;
    if (auto* im = active_impl(); im && name_va) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (EffectRecord* fx = im->find_effect_by_va(mem, fx_va)) {
            const std::string pname = mem.read_cstring(name_va, 128u);
            auto it = fx->param_handles.find(pname);
            if (it != fx->param_handles.end()) {
                out_handle = it->second;
            } else {
                const uint32_t h = static_cast<uint32_t>(fx->parameters.size() + 1u);
                fx->parameters.push_back(pname);
                fx->param_handles[pname] = h;
                out_handle = h;
            }
        }
    }
    ctx.eax = out_handle;
    ctx.ret_stdcall(mem, 12u);
}

void com_fx_set_value(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t fx_va   = ctx.arg32(mem, 0);
    const uint32_t hparam  = ctx.arg32(mem, 1);
    const uint32_t data_va = ctx.arg32(mem, 2);
    const uint32_t bytes   = ctx.arg32(mem, 3);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (EffectRecord* fx = im->find_effect_by_va(mem, fx_va)) {
            const std::string pname = resolve_effect_param_name(*fx, mem, hparam);
            apply_effect_param_value(*im, *fx, mem, pname, data_va, bytes);
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 16u);
}

void com_fx_set_float(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t fx_va  = ctx.arg32(mem, 0);
    const uint32_t hparam = ctx.arg32(mem, 1);
    const uint32_t f_bits = ctx.arg32(mem, 2);
    float f_val = 0.0f;
    std::memcpy(&f_val, &f_bits, sizeof(float));
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (EffectRecord* fx = im->find_effect_by_va(mem, fx_va)) {
            const std::string pname = resolve_effect_param_name(*fx, mem, hparam);
            apply_effect_scalar_float(*fx, pname, f_val);
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

void com_fx_set_vector(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t fx_va   = ctx.arg32(mem, 0);
    const uint32_t hparam  = ctx.arg32(mem, 1);
    const uint32_t vec_va  = ctx.arg32(mem, 2);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (EffectRecord* fx = im->find_effect_by_va(mem, fx_va)) {
            const std::string pname = resolve_effect_param_name(*fx, mem, hparam);
            apply_effect_param_value(*im, *fx, mem, pname, vec_va, 16u);
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

void com_fx_set_matrix(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t fx_va  = ctx.arg32(mem, 0);
    const uint32_t hparam = ctx.arg32(mem, 1);
    const uint32_t mat_va = ctx.arg32(mem, 2);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (EffectRecord* fx = im->find_effect_by_va(mem, fx_va)) {
            const std::string pname = resolve_effect_param_name(*fx, mem, hparam);
            apply_effect_param_value(*im, *fx, mem, pname, mat_va, 64u);
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

void com_fx_set_texture(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t fx_va  = ctx.arg32(mem, 0);
    const uint32_t hparam = ctx.arg32(mem, 1);
    const uint32_t tex_va = ctx.arg32(mem, 2);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (EffectRecord* fx = im->find_effect_by_va(mem, fx_va)) {
            const std::string pname = resolve_effect_param_name(*fx, mem, hparam);
            if (!pname.empty()) fx->texture_params[pname] = tex_va;
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

void com_fx_set_technique(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t fx_va = ctx.arg32(mem, 0);
    const uint32_t htech = ctx.arg32(mem, 1);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (EffectRecord* fx = im->find_effect_by_va(mem, fx_va)) {
            fx->active_tech_handle = htech;
            if (htech >= 1u && htech <= fx->techniques.size()) {
                fx->active_tech_name = fx->techniques[htech - 1u];
            } else if (htech != 0u) {
                fx->active_tech_name = mem.read_cstring(htech, 128u);
            }
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void com_fx_begin(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t fx_va     = ctx.arg32(mem, 0);
    const uint32_t p_passes  = ctx.arg32(mem, 1);
    uint32_t passes = 1u;
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (EffectRecord* fx = im->find_effect_by_va(mem, fx_va)) {
            fx->in_effect = true;
            im->active_effect_id = fx->id;
            if (shader_manifest::find_technique_pass(fx->active_tech_name.c_str(), 1u) != nullptr) {
                passes = 2u;
            }
        }
    }
    if (p_passes && mem.in_bounds(p_passes, 4u)) {
        mem.w32(p_passes, passes);
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 12u);
}

void com_fx_begin_pass(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t fx_va = ctx.arg32(mem, 0);
    const uint32_t pass  = ctx.arg32(mem, 1);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (EffectRecord* fx = im->find_effect_by_va(mem, fx_va)) {
            fx->active_pass_index = pass;
            im->active_effect_id  = fx->id;
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void com_fx_end_pass(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 4u);
}

void com_fx_end(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t fx_va = ctx.arg32(mem, 0);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (EffectRecord* fx = im->find_effect_by_va(mem, fx_va)) {
            fx->in_effect = false;
            if (im->active_effect_id == fx->id || im->active_effect_id == fx_va) {
                im->active_effect_id = 0u;
            }
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 4u);
}

// ---------------------------------------------------------------------------
// ID3DXFont::DrawTextA (CoreText Shift-JIS CP932 / UTF-8 Rasterizer -> Metal)
// ---------------------------------------------------------------------------
void com_font_draw_text_a(CpuContext& ctx, GuestMemory& mem) {
    // (this, pSprite, pString, Count, pRect, Format, Color) -> 28 bytes
    const uint32_t font_va  = ctx.arg32(mem, 0);
    const uint32_t str_va   = ctx.arg32(mem, 2);
    const int32_t  count    = static_cast<int32_t>(ctx.arg32(mem, 3));
    const uint32_t rect_va  = ctx.arg32(mem, 4);
    const uint32_t format   = ctx.arg32(mem, 5);
    const uint32_t color    = ctx.arg32(mem, 6);

    int32_t out_height = 16;
    if (auto* im = active_impl(); im && str_va != 0u) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        FontRecord* fr = im->find_font_by_va(mem, font_va);
        std::string raw = mem.read_cstring(str_va, count > 0 ? static_cast<size_t>(count) : 1024u);
        if (!raw.empty()) {
            @autoreleasepool {
                NSData* sdata = [NSData dataWithBytes:raw.data() length:raw.size()];
                NSStringEncoding sjisEnc = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingDOSJapanese);
                NSString* nsStr = [[NSString alloc] initWithData:sdata encoding:sjisEnc];
                if (!nsStr) {
                    nsStr = [[NSString alloc] initWithData:sdata encoding:NSUTF8StringEncoding];
                }
                if (!nsStr) {
                    nsStr = [NSString stringWithUTF8String:raw.c_str()];
                }
                if (nsStr && nsStr.length > 0) {
                    CTFontRef font = (fr && fr->ct_font) ? fr->ct_font
                                   : CTFontCreateWithName(CFSTR("HiraginoSans-W3"), 14.0, nullptr);
                    const uint8_t ca = (color >> 24) & 0xFFu;
                    const uint8_t cr = (color >> 16) & 0xFFu;
                    const uint8_t cg = (color >> 8)  & 0xFFu;
                    const uint8_t cb = color & 0xFFu;
                    CGColorSpaceRef cs = CGColorSpaceCreateDeviceRGB();
                    const CGFloat rgba[4] = {cr / 255.0, cg / 255.0, cb / 255.0, ca / 255.0};
                    CGColorRef cgCol = CGColorCreate(cs, rgba);

                    NSDictionary* attrs = @{
                        (__bridge id)kCTFontAttributeName: (__bridge id)font,
                        (__bridge id)kCTForegroundColorAttributeName: (__bridge id)cgCol
                    };
                    NSAttributedString* attrStr = [[NSAttributedString alloc] initWithString:nsStr attributes:attrs];
                    CTLineRef line = CTLineCreateWithAttributedString((__bridge CFAttributedStringRef)attrStr);
                    CGFloat ascent = 0, descent = 0, leading = 0;
                    const double line_w = CTLineGetTypographicBounds(line, &ascent, &descent, &leading);
                    const uint32_t tex_w = std::max<uint32_t>(4u, static_cast<uint32_t>(std::ceil(line_w)) + 2u);
                    const uint32_t tex_h = std::max<uint32_t>(4u, static_cast<uint32_t>(std::ceil(ascent + descent)) + 2u);
                    out_height = static_cast<int32_t>(tex_h);

                    int32_t rx = 0, ry = 0, rw = static_cast<int32_t>(tex_w), rh = static_cast<int32_t>(tex_h);
                    if (rect_va && mem.in_bounds(rect_va, 16u)) {
                        rx = static_cast<int32_t>(mem.r32(rect_va + 0u));
                        ry = static_cast<int32_t>(mem.r32(rect_va + 4u));
                        const int32_t rr = static_cast<int32_t>(mem.r32(rect_va + 8u));
                        const int32_t rb = static_cast<int32_t>(mem.r32(rect_va + 12u));
                        if (format & 0x00000400u) { // DT_CALCRECT
                            mem.w32(rect_va + 8u,  static_cast<uint32_t>(rx + static_cast<int32_t>(tex_w)));
                            mem.w32(rect_va + 12u, static_cast<uint32_t>(ry + static_cast<int32_t>(tex_h)));
                        } else if (rr > rx && rb > ry) {
                            rw = rr - rx;
                            rh = rb - ry;
                            if (format & 1u) rx += (rw - static_cast<int32_t>(tex_w)) / 2; // DT_CENTER
                            if (format & 2u) rx = rr - static_cast<int32_t>(tex_w);      // DT_RIGHT
                            if (format & 4u) ry += (rh - static_cast<int32_t>(tex_h)) / 2; // DT_VCENTER
                        }
                    }

                    if ((format & 0x00000400u) == 0u) {
                        std::vector<uint8_t> buf(static_cast<size_t>(tex_w) * tex_h * 4u, 0u);
                        CGContextRef cgCtx = CGBitmapContextCreate(
                            buf.data(), tex_w, tex_h, 8, tex_w * 4u, cs,
                            static_cast<uint32_t>(kCGImageAlphaPremultipliedLast) | kCGBitmapByteOrder32Big);
                        if (cgCtx != nullptr) {
                            CGContextSetTextPosition(cgCtx, 1.0, descent + 1.0);
                            CTLineDraw(line, cgCtx);
                            CGContextRelease(cgCtx);

                            id<MTLTexture> glyphTex = im->make_mtl_texture(tex_w, tex_h, MTLPixelFormatRGBA8Unorm, false, false);
                            if (glyphTex != nil) {
                                [glyphTex replaceRegion:MTLRegionMake2D(0, 0, tex_w, tex_h)
                                            mipmapLevel:0
                                              withBytes:buf.data()
                                            bytesPerRow:tex_w * 4u];

                                // Submit textured screen quad through fixed-function pipeline
                                const uint32_t saved_fvf = im->current_fvf;
                                const uint32_t saved_blend = im->render_states[kRsAlphaBlendEnable];
                                const uint32_t saved_src   = im->render_states[kRsSrcBlend];
                                const uint32_t saved_dst   = im->render_states[kRsDestBlend];
                                const uint32_t saved_tex0  = im->bound_textures[0];

                                if (im->font_scratch_tex_va == 0u) {
                                    im->font_scratch_tex_id = ++im->next_handle_id;
                                    im->font_scratch_tex_va = im->alloc_com_object(
                                        mem, im->vtbl_texture, im->font_scratch_tex_id, kKindTexture);
                                }
                                TextureRecord tmp_rec{};
                                tmp_rec.id = im->font_scratch_tex_id;
                                tmp_rec.width = tex_w; tmp_rec.height = tex_h;
                                tmp_rec.mtl_tex = glyphTex;
                                tmp_rec.guest_va = im->font_scratch_tex_va;
                                im->textures[tmp_rec.id] = tmp_rec;

                                struct QuadVert { float x, y, z, rhw; uint32_t diff, spec; float u, v; };
                                const float x0 = static_cast<float>(rx);
                                const float y0 = static_cast<float>(ry);
                                const float x1 = x0 + static_cast<float>(tex_w);
                                const float y1 = y0 + static_cast<float>(tex_h);
                                QuadVert qv[4] = {
                                    {x0, y0, 0.0f, 1.0f, 0xFFFFFFFFu, 0u, 0.0f, 0.0f},
                                    {x1, y0, 0.0f, 1.0f, 0xFFFFFFFFu, 0u, 1.0f, 0.0f},
                                    {x0, y1, 0.0f, 1.0f, 0xFFFFFFFFu, 0u, 0.0f, 1.0f},
                                    {x1, y1, 0.0f, 1.0f, 0xFFFFFFFFu, 0u, 1.0f, 1.0f},
                                };

                                im->current_fvf = 0x000001C4u;
                                im->render_states[kRsAlphaBlendEnable] = 1u;
                                im->render_states[kRsSrcBlend]  = 2u; // ONE (premultiplied from CGContext)
                                im->render_states[kRsDestBlend] = 6u; // INVSRCALPHA
                                im->bound_textures[0] = tmp_rec.guest_va;
                                im->execute_draw(mem, kPtTriangleStrip, 2u,
                                                 reinterpret_cast<const uint8_t*>(qv), 4u, sizeof(QuadVert),
                                                 nullptr, 0u);

                                im->textures.erase(tmp_rec.id);
                                im->current_fvf = saved_fvf;
                                im->render_states[kRsAlphaBlendEnable] = saved_blend;
                                im->render_states[kRsSrcBlend]  = saved_src;
                                im->render_states[kRsDestBlend] = saved_dst;
                                im->bound_textures[0] = saved_tex0;
                            }
                        }
                    }

                    CFRelease(line);
                    CGColorRelease(cgCol);
                    CGColorSpaceRelease(cs);
                    if (!(fr && fr->ct_font)) CFRelease(font);
                }
            }
        }
    }
    ctx.eax = static_cast<uint32_t>(out_height);
    ctx.ret_stdcall(mem, 28u);
}

// ---------------------------------------------------------------------------
// Populate All 6 Guest COM VTables Inside GuestMemory
// ---------------------------------------------------------------------------
uint32_t build_vtable(GuestMemory& mem, const std::vector<RecompFn>& slots) {
    const uint32_t tbl_va = mem.alloc_thunk_block(static_cast<uint32_t>(slots.size() * 4u), 16u);
    for (size_t i = 0; i < slots.size(); ++i) {
        const uint32_t thunk = alloc_com_method_thunk(slots[i]);
        mem.w32(tbl_va + static_cast<uint32_t>(i * 4u), thunk);
    }
    return tbl_va;
}

} // namespace

void D3D9MetalBridge::Impl::init_com_vtables(GuestMemory& mem) {
    if (vtbl_d3d9 != 0u) return;

    // 1. IDirect3D9 (17 slots)
    vtbl_d3d9 = build_vtable(mem, {
        &com_unknown_query_interface,      // 0
        &com_unknown_addref,               // 1
        &com_unknown_release,              // 2
        &com_stub_ret<8u, kS_OK>,          // 3 RegisterSoftwareDevice
        &com_stub_ret<4u, 1u>,             // 4 GetAdapterCount
        &com_d3d9_get_adapter_identifier,  // 5 GetAdapterIdentifier
        &com_d3d9_get_adapter_mode_count,  // 6 GetAdapterModeCount
        &com_d3d9_enum_adapter_modes,      // 7 EnumAdapterModes
        &com_d3d9_get_adapter_display_mode,// 8 GetAdapterDisplayMode
        &com_stub_ret<24u, kS_OK>,         // 9 CheckDeviceType
        &com_stub_ret<28u, kS_OK>,         // 10 CheckDeviceFormat
        &com_stub_ret<28u, kS_OK>,         // 11 CheckDeviceMultiSampleType
        &com_stub_ret<24u, kS_OK>,         // 12 CheckDepthStencilMatch
        &com_stub_ret<20u, kS_OK>,         // 13 CheckDeviceFormatConversion
        &com_d3d9_get_device_caps,         // 14 GetDeviceCaps
        &com_stub_ret<8u, 0x00010001u>,    // 15 GetAdapterMonitor
        &com_d3d9_create_device,           // 16 CreateDevice
    });

    // 2. IDirect3DDevice9 (119 slots)
    std::vector<RecompFn> dev_slots(119u, &com_stub_ret<4u, kS_OK>);
    dev_slots[0]  = &com_unknown_query_interface;
    dev_slots[1]  = &com_unknown_addref;
    dev_slots[2]  = &com_unknown_release;
    dev_slots[3]  = &com_stub_ret<4u, kS_OK>;  // TestCooperativeLevel
    dev_slots[4]  = &com_dev_get_available_tex_mem;
    dev_slots[5]  = &com_dev_evict_managed_resources;
    dev_slots[6]  = &com_dev_get_direct3d;
    dev_slots[7]  = &com_dev_get_device_caps;
    dev_slots[8]  = &com_dev_get_display_mode;
    dev_slots[9]  = &com_stub_ret<8u, kS_OK>;  // GetCreationParameters
    dev_slots[10] = &com_stub_ret<16u, kS_OK>; // SetCursorProperties
    dev_slots[11] = &com_stub_ret<16u, kS_OK>; // SetCursorPosition
    dev_slots[12] = &com_stub_ret<8u, 1u>;     // ShowCursor
    dev_slots[13] = &com_stub_ret<12u, kE_NOTIMPL>;
    dev_slots[14] = &com_stub_ret<12u, kS_OK>;
    dev_slots[15] = &com_stub_ret<4u, 1u>;
    dev_slots[16] = &com_dev_reset;
    dev_slots[17] = &com_dev_present;
    dev_slots[18] = &com_dev_get_back_buffer;
    dev_slots[19] = &com_stub_ret<12u, kS_OK>;
    dev_slots[20] = &com_stub_ret<8u, kS_OK>;
    dev_slots[21] = &com_stub_ret<16u, kS_OK>;
    dev_slots[22] = &com_stub_ret<12u, kS_OK>;
    dev_slots[23] = &com_dev_create_texture;
    dev_slots[24] = &com_stub_ret<40u, kE_NOTIMPL>;
    dev_slots[25] = &com_stub_ret<32u, kE_NOTIMPL>;
    dev_slots[26] = &com_stub_ret<28u, kS_OK>;
    dev_slots[27] = &com_stub_ret<28u, kS_OK>;
    dev_slots[28] = &com_dev_create_render_target;
    dev_slots[29] = &com_dev_create_depth_stencil_surface;
    dev_slots[30] = &com_stub_ret<20u, kS_OK>; // UpdateSurface
    dev_slots[31] = &com_stub_ret<12u, kS_OK>; // UpdateTexture
    dev_slots[32] = &com_stub_ret<12u, kS_OK>; // GetRenderTargetData
    dev_slots[33] = &com_stub_ret<12u, kS_OK>; // GetFrontBufferData
    dev_slots[34] = &com_stub_ret<24u, kS_OK>; // StretchRect
    dev_slots[35] = &com_stub_ret<16u, kS_OK>; // ColorFill
    dev_slots[36] = &com_dev_create_offscreen_plain_surface;
    dev_slots[37] = &com_dev_set_render_target;
    dev_slots[38] = &com_dev_get_render_target;
    dev_slots[39] = &com_dev_set_depth_stencil;
    dev_slots[40] = &com_dev_get_depth_stencil;
    dev_slots[41] = &com_dev_begin_scene;
    dev_slots[42] = &com_dev_end_scene;
    dev_slots[43] = &com_dev_clear;
    dev_slots[44] = &com_dev_set_transform;
    dev_slots[45] = &com_dev_get_transform;
    dev_slots[46] = &com_stub_ret<12u, kS_OK>; // MultiplyTransform
    dev_slots[47] = &com_dev_set_viewport;
    dev_slots[48] = &com_dev_get_viewport;
    dev_slots[49] = &com_stub_ret<8u, kS_OK>;  // SetMaterial
    dev_slots[50] = &com_stub_ret<8u, kS_OK>;  // GetMaterial
    dev_slots[51] = &com_stub_ret<12u, kS_OK>; // SetLight
    dev_slots[52] = &com_stub_ret<12u, kS_OK>; // GetLight
    dev_slots[53] = &com_stub_ret<12u, kS_OK>; // LightEnable
    dev_slots[54] = &com_stub_ret<12u, kS_OK>; // GetLightEnable
    dev_slots[55] = &com_stub_ret<12u, kS_OK>; // SetClipPlane
    dev_slots[56] = &com_stub_ret<12u, kS_OK>; // GetClipPlane
    dev_slots[57] = &com_dev_set_render_state;
    dev_slots[58] = &com_dev_get_render_state;
    dev_slots[59] = &com_stub_ret<12u, kS_OK>; // CreateStateBlock
    dev_slots[60] = &com_stub_ret<4u, kS_OK>;  // BeginStateBlock
    dev_slots[61] = &com_stub_ret<8u, kS_OK>;  // EndStateBlock
    dev_slots[62] = &com_stub_ret<8u, kS_OK>;  // SetClipStatus
    dev_slots[63] = &com_stub_ret<8u, kS_OK>;  // GetClipStatus
    dev_slots[64] = &com_dev_get_texture;
    dev_slots[65] = &com_dev_set_texture;
    dev_slots[66] = &com_stub_ret<16u, kS_OK>; // GetTextureStageState
    dev_slots[67] = &com_dev_set_tss;
    dev_slots[68] = &com_stub_ret<16u, kS_OK>; // GetSamplerState
    dev_slots[69] = &com_dev_set_sampler_state;
    dev_slots[70] = &com_stub_ret<8u, kS_OK>;  // ValidateDevice
    dev_slots[71] = &com_stub_ret<12u, kS_OK>; // SetPaletteEntries
    dev_slots[72] = &com_stub_ret<12u, kS_OK>; // GetPaletteEntries
    dev_slots[73] = &com_stub_ret<8u, kS_OK>;  // SetCurrentTexturePalette
    dev_slots[74] = &com_stub_ret<8u, kS_OK>;  // GetCurrentTexturePalette
    dev_slots[75] = &com_dev_set_scissor_rect;
    dev_slots[76] = &com_stub_ret<8u, kS_OK>;  // GetScissorRect
    dev_slots[77] = &com_stub_ret<8u, kS_OK>;  // SetSoftwareVertexProcessing
    dev_slots[78] = &com_stub_ret<4u, 0u>;     // GetSoftwareVertexProcessing
    dev_slots[79] = &com_stub_ret<8u, kS_OK>;  // SetNPatchMode
    dev_slots[80] = &com_stub_ret<4u, 0u>;     // GetNPatchMode
    dev_slots[81] = &com_dev_draw_primitive;
    dev_slots[82] = &com_stub_ret<28u, kS_OK>; // DrawIndexedPrimitive
    dev_slots[83] = &com_dev_draw_primitive_up;
    dev_slots[84] = &com_dev_draw_indexed_primitive_up;
    dev_slots[85] = &com_stub_ret<24u, kS_OK>; // ProcessVertices
    dev_slots[86] = &com_stub_ret<12u, kS_OK>; // CreateVertexDeclaration
    dev_slots[87] = &com_stub_ret<8u, kS_OK>;  // SetVertexDeclaration
    dev_slots[88] = &com_stub_ret<8u, kS_OK>;  // GetVertexDeclaration
    dev_slots[89] = &com_dev_set_fvf;
    dev_slots[90] = &com_dev_get_fvf;
    dev_slots[91] = &com_stub_ret<12u, kS_OK>; // CreateVertexShader
    dev_slots[92] = &com_stub_ret<8u, kS_OK>;  // SetVertexShader
    dev_slots[93] = &com_stub_ret<8u, kS_OK>;  // GetVertexShader
    dev_slots[94] = &com_stub_ret<16u, kS_OK>; // SetVertexShaderConstantF
    dev_slots[95] = &com_stub_ret<16u, kS_OK>;
    dev_slots[96] = &com_stub_ret<16u, kS_OK>;
    dev_slots[97] = &com_stub_ret<16u, kS_OK>;
    dev_slots[98] = &com_stub_ret<16u, kS_OK>;
    dev_slots[99] = &com_stub_ret<16u, kS_OK>;
    dev_slots[100] = &com_dev_set_stream_source;
    dev_slots[101] = &com_stub_ret<20u, kS_OK>;
    dev_slots[102] = &com_stub_ret<12u, kS_OK>;
    dev_slots[103] = &com_stub_ret<12u, kS_OK>;
    dev_slots[104] = &com_stub_ret<8u, kS_OK>;  // SetIndices
    dev_slots[105] = &com_stub_ret<8u, kS_OK>;  // GetIndices
    dev_slots[106] = &com_stub_ret<12u, kS_OK>; // CreatePixelShader
    dev_slots[107] = &com_stub_ret<8u, kS_OK>;  // SetPixelShader
    dev_slots[108] = &com_stub_ret<8u, kS_OK>;  // GetPixelShader
    dev_slots[109] = &com_stub_ret<16u, kS_OK>; // SetPixelShaderConstantF
    dev_slots[110] = &com_stub_ret<16u, kS_OK>;
    dev_slots[111] = &com_stub_ret<16u, kS_OK>;
    dev_slots[112] = &com_stub_ret<16u, kS_OK>;
    dev_slots[113] = &com_stub_ret<16u, kS_OK>;
    dev_slots[114] = &com_stub_ret<16u, kS_OK>;
    dev_slots[115] = &com_stub_ret<20u, kS_OK>;
    dev_slots[116] = &com_stub_ret<20u, kS_OK>;
    dev_slots[117] = &com_stub_ret<8u, kS_OK>;
    dev_slots[118] = &com_stub_ret<16u, kS_OK>;
    vtbl_device = build_vtable(mem, dev_slots);

    // 3. IDirect3DTexture9 (22 slots)
    vtbl_texture = build_vtable(mem, {
        &com_unknown_query_interface,      // 0
        &com_unknown_addref,               // 1
        &com_unknown_release,              // 2
        &com_dev_get_direct3d,             // 3 GetDevice (same arg count 8 bytes)
        &com_stub_ret<20u, kS_OK>,         // 4 SetPrivateData
        &com_stub_ret<16u, kE_FAIL>,       // 5 GetPrivateData
        &com_stub_ret<8u, kS_OK>,          // 6 FreePrivateData
        &com_stub_ret<8u, 0u>,             // 7 SetPriority
        &com_stub_ret<4u, 0u>,             // 8 GetPriority
        &com_stub_ret<4u, kS_OK>,          // 9 PreLoad
        &com_stub_ret<4u, 3u>,             // 10 GetType = D3DRTYPE_TEXTURE
        &com_stub_ret<8u, 0u>,             // 11 SetLOD
        &com_stub_ret<4u, 0u>,             // 12 GetLOD
        &com_stub_ret<4u, 1u>,             // 13 GetLevelCount
        &com_stub_ret<8u, kS_OK>,          // 14 SetAutoGenFilterType
        &com_stub_ret<4u, 2u>,             // 15 GetAutoGenFilterType
        &com_stub_ret<4u, kS_OK>,          // 16 GenerateMipSubLevels
        &com_tex_get_level_desc,           // 17 GetLevelDesc
        &com_tex_get_surface_level,        // 18 GetSurfaceLevel
        &com_tex_lock_rect,                // 19 LockRect
        &com_tex_unlock_rect,              // 20 UnlockRect
        &com_stub_ret<8u, kS_OK>,          // 21 AddDirtyRect
    });

    // 4. IDirect3DSurface9 (17 slots)
    vtbl_surface = build_vtable(mem, {
        &com_unknown_query_interface,      // 0
        &com_unknown_addref,               // 1
        &com_unknown_release,              // 2
        &com_dev_get_direct3d,             // 3 GetDevice
        &com_stub_ret<20u, kS_OK>,         // 4 SetPrivateData
        &com_stub_ret<16u, kE_FAIL>,       // 5 GetPrivateData
        &com_stub_ret<8u, kS_OK>,          // 6 FreePrivateData
        &com_stub_ret<8u, 0u>,             // 7 SetPriority
        &com_stub_ret<4u, 0u>,             // 8 GetPriority
        &com_stub_ret<4u, kS_OK>,          // 9 PreLoad
        &com_stub_ret<4u, 1u>,             // 10 GetType = D3DRTYPE_SURFACE
        &com_stub_ret<12u, kE_NOTIMPL>,    // 11 GetContainer
        &com_surf_get_desc,                // 12 GetDesc
        &com_surf_lock_rect,               // 13 LockRect
        &com_surf_unlock_rect,             // 14 UnlockRect
        &com_stub_ret<8u, kE_NOTIMPL>,     // 15 GetDC
        &com_stub_ret<8u, kS_OK>,          // 16 ReleaseDC
    });

    // 5. ID3DXEffect (74 slots)
    std::vector<RecompFn> fx_slots(74u, &com_stub_ret<12u, kS_OK>);
    fx_slots[0]  = &com_unknown_query_interface;
    fx_slots[1]  = &com_unknown_addref;
    fx_slots[2]  = &com_unknown_release;
    fx_slots[3]  = &com_stub_ret<8u, kS_OK>;   // GetDesc
    fx_slots[4]  = &com_stub_ret<12u, kS_OK>;  // GetParameterDesc
    fx_slots[5]  = &com_stub_ret<12u, kS_OK>;  // GetTechniqueDesc
    fx_slots[6]  = &com_stub_ret<12u, kS_OK>;  // GetPassDesc
    fx_slots[7]  = &com_stub_ret<12u, kS_OK>;  // GetFunctionDesc
    fx_slots[8]  = &com_stub_ret<12u, 0u>;     // GetParameter
    fx_slots[9]  = &com_fx_get_parameter_by_name;
    fx_slots[10] = &com_stub_ret<12u, 0u>;     // GetParameterBySemantic
    fx_slots[11] = &com_stub_ret<12u, 0u>;     // GetParameterElement
    fx_slots[12] = &com_stub_ret<8u, 0u>;      // GetTechnique
    fx_slots[13] = &com_fx_get_technique_by_name;
    fx_slots[14] = &com_stub_ret<12u, 0u>;     // GetPass
    fx_slots[15] = &com_stub_ret<12u, 0u>;     // GetPassByName
    fx_slots[16] = &com_stub_ret<8u, 0u>;
    fx_slots[17] = &com_stub_ret<8u, 0u>;
    fx_slots[18] = &com_stub_ret<12u, 0u>;
    fx_slots[19] = &com_stub_ret<12u, 0u>;
    fx_slots[20] = &com_fx_set_value;
    fx_slots[21] = &com_stub_ret<16u, kS_OK>;  // GetValue
    fx_slots[22] = &com_stub_ret<12u, kS_OK>;  // SetBool
    fx_slots[23] = &com_stub_ret<12u, kS_OK>;  // GetBool
    fx_slots[24] = &com_stub_ret<16u, kS_OK>;
    fx_slots[25] = &com_stub_ret<16u, kS_OK>;
    fx_slots[26] = &com_stub_ret<12u, kS_OK>;  // SetInt
    fx_slots[27] = &com_stub_ret<12u, kS_OK>;  // GetInt
    fx_slots[28] = &com_stub_ret<16u, kS_OK>;
    fx_slots[29] = &com_stub_ret<16u, kS_OK>;
    fx_slots[30] = &com_fx_set_float;
    fx_slots[31] = &com_stub_ret<12u, kS_OK>;  // GetFloat
    fx_slots[32] = &com_fx_set_value;          // SetFloatArray (hParam, pData, Count -> wait: 16 bytes)
    fx_slots[33] = &com_stub_ret<16u, kS_OK>;
    fx_slots[34] = &com_fx_set_vector;
    fx_slots[35] = &com_stub_ret<12u, kS_OK>;
    fx_slots[36] = &com_stub_ret<16u, kS_OK>;
    fx_slots[37] = &com_stub_ret<16u, kS_OK>;
    fx_slots[38] = &com_fx_set_matrix;
    fx_slots[39] = &com_stub_ret<12u, kS_OK>;
    for (size_t s = 40; s <= 49; ++s) fx_slots[s] = &com_stub_ret<16u, kS_OK>;
    fx_slots[50] = &com_stub_ret<12u, kS_OK>;  // SetString
    fx_slots[51] = &com_stub_ret<12u, kS_OK>;  // GetString
    fx_slots[52] = &com_fx_set_texture;        // SetTexture
    fx_slots[53] = &com_stub_ret<12u, kS_OK>;  // GetTexture
    fx_slots[54] = &com_stub_ret<12u, kS_OK>;
    fx_slots[55] = &com_stub_ret<12u, kS_OK>;
    fx_slots[56] = &com_stub_ret<16u, kS_OK>;  // SetArrayRange
    fx_slots[57] = &com_stub_ret<8u, kS_OK>;   // GetPool
    fx_slots[58] = &com_fx_set_technique;      // SetTechnique (+0xe8)
    fx_slots[59] = &com_stub_ret<4u, 0u>;      // GetCurrentTechnique
    fx_slots[60] = &com_stub_ret<8u, kS_OK>;   // ValidateTechnique
    fx_slots[61] = &com_stub_ret<12u, kS_OK>;  // FindNextValidTechnique
    fx_slots[62] = &com_stub_ret<12u, 1u>;     // IsParameterUsed
    fx_slots[63] = &com_fx_begin;              // Begin (+0xfc)
    fx_slots[64] = &com_fx_begin_pass;         // BeginPass (+0x100)
    fx_slots[65] = &com_stub_ret<4u, kS_OK>;   // CommitChanges (+0x104)
    fx_slots[66] = &com_fx_end_pass;           // EndPass (+0x108)
    fx_slots[67] = &com_fx_end;                // End (+0x10c)
    fx_slots[68] = &com_dev_get_direct3d;      // GetDevice (8 bytes)
    fx_slots[69] = &com_stub_ret<4u, kS_OK>;   // OnLostDevice (+0x114)
    fx_slots[70] = &com_stub_ret<4u, kS_OK>;   // OnResetDevice (+0x118)
    fx_slots[71] = &com_stub_ret<8u, kS_OK>;
    fx_slots[72] = &com_stub_ret<8u, kS_OK>;
    fx_slots[73] = &com_stub_ret<4u, kS_OK>;
    vtbl_effect = build_vtable(mem, fx_slots);

    // 6. ID3DXFont (18 slots)
    vtbl_font = build_vtable(mem, {
        &com_unknown_query_interface,      // 0
        &com_unknown_addref,               // 1
        &com_unknown_release,              // 2
        &com_dev_get_direct3d,             // 3 GetDevice
        &com_stub_ret<8u, kS_OK>,          // 4 GetDescA
        &com_stub_ret<8u, kS_OK>,          // 5 GetDescW
        &com_stub_ret<8u, 1u>,             // 6 GetTextMetricsA
        &com_stub_ret<8u, 1u>,             // 7 GetTextMetricsW
        &com_stub_ret<4u, 0u>,             // 8 GetDC
        &com_stub_ret<24u, kE_NOTIMPL>,    // 9 GetGlyphData
        &com_stub_ret<12u, kS_OK>,         // 10 PreloadCharacters
        &com_stub_ret<12u, kS_OK>,         // 11 PreloadGlyphs
        &com_stub_ret<12u, kS_OK>,         // 12 PreloadTextA
        &com_stub_ret<12u, kS_OK>,         // 13 PreloadTextW
        &com_font_draw_text_a,             // 14 DrawTextA (+0x38)
        &com_font_draw_text_a,             // 15 DrawTextW (+0x3c)
        &com_stub_ret<4u, kS_OK>,          // 16 OnLostDevice (+0x40)
        &com_stub_ret<4u, kS_OK>,          // 17 OnResetDevice (+0x44)
    });
}

// ---------------------------------------------------------------------------
// D3D9MetalBridge Public Methods
// ---------------------------------------------------------------------------
D3D9MetalBridge::D3D9MetalBridge() : impl_(std::make_unique<Impl>()) {}
D3D9MetalBridge::~D3D9MetalBridge() { shutdown(); }

void D3D9MetalBridge::set_active(D3D9MetalBridge* bridge) noexcept {
    global_bridge_slot().store(bridge, std::memory_order_release);
}

D3D9MetalBridge* D3D9MetalBridge::active() noexcept {
    return global_bridge_slot().load(std::memory_order_acquire);
}

bool D3D9MetalBridge::init(void* cametal_layer, int width, int height) {
    std::lock_guard<std::recursive_mutex> lk(impl_->mtx);
    impl_->drawable_width  = (width > 0)  ? width  : 1334;
    impl_->drawable_height = (height > 0) ? height : 750;
    impl_->metal_layer     = (__bridge CAMetalLayer*)cametal_layer;

    if (impl_->metal_layer != nil && impl_->metal_layer.device != nil) {
        impl_->device = impl_->metal_layer.device;
    } else {
        impl_->device = MTLCreateSystemDefaultDevice();
    }

    if (impl_->device == nil) {
        if (cametal_layer != nullptr) {
            return false;
        }
        // Headless fallback
        impl_->initialized = true;
        if (active() == nullptr) set_active(this);
        return true;
    }

    if (impl_->metal_layer != nil) {
        impl_->metal_layer.device      = impl_->device;
        impl_->metal_layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
        impl_->metal_layer.drawableSize = CGSizeMake(impl_->drawable_width, impl_->drawable_height);
    }

    impl_->cmd_queue = [impl_->device newCommandQueue];
    impl_->shader_lib = [impl_->device newDefaultLibrary];
    if (impl_->shader_lib == nil) {
        // Fallback: load mbaa_shaders.metal from bundle resource or relative path
        NSString* path = [[NSBundle mainBundle] pathForResource:@"mbaa_shaders" ofType:@"metal"];
        if (path != nil) {
            NSError* err = nil;
            NSString* src = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:&err];
            if (src != nil) {
                impl_->shader_lib = [impl_->device newLibraryWithSource:src options:nil error:&err];
            }
        }
    }

    // Build shared VertexDescriptor matching MbaaMetalVertex
    MTLVertexDescriptor* vd = [[MTLVertexDescriptor alloc] init];
    vd.attributes[0].format = MTLVertexFormatFloat4; vd.attributes[0].offset = offsetof(MbaaMetalVertex, position);  vd.attributes[0].bufferIndex = MBAA_BUF_VERTICES;
    vd.attributes[1].format = MTLVertexFormatFloat4; vd.attributes[1].offset = offsetof(MbaaMetalVertex, diffuse);   vd.attributes[1].bufferIndex = MBAA_BUF_VERTICES;
    vd.attributes[2].format = MTLVertexFormatFloat4; vd.attributes[2].offset = offsetof(MbaaMetalVertex, specular);  vd.attributes[2].bufferIndex = MBAA_BUF_VERTICES;
    vd.attributes[3].format = MTLVertexFormatFloat2; vd.attributes[3].offset = offsetof(MbaaMetalVertex, texcoord0); vd.attributes[3].bufferIndex = MBAA_BUF_VERTICES;
    vd.attributes[4].format = MTLVertexFormatFloat2; vd.attributes[4].offset = offsetof(MbaaMetalVertex, texcoord1); vd.attributes[4].bufferIndex = MBAA_BUF_VERTICES;
    vd.layouts[MBAA_BUF_VERTICES].stride       = sizeof(MbaaMetalVertex);
    vd.layouts[MBAA_BUF_VERTICES].stepFunction = MTLVertexStepFunctionPerVertex;
    impl_->vertex_desc = vd;

    MTLDepthStencilDescriptor* dsOff = [[MTLDepthStencilDescriptor alloc] init];
    dsOff.depthCompareFunction = MTLCompareFunctionAlways;
    dsOff.depthWriteEnabled    = NO;
    impl_->depth_disabled = [impl_->device newDepthStencilStateWithDescriptor:dsOff];

    MTLDepthStencilDescriptor* dsOn = [[MTLDepthStencilDescriptor alloc] init];
    dsOn.depthCompareFunction = MTLCompareFunctionLessEqual;
    dsOn.depthWriteEnabled    = YES;
    impl_->depth_enabled = [impl_->device newDepthStencilStateWithDescriptor:dsOn];

    // 1x1 fallback black texture and scratch MRT target
    impl_->dummy_black_tex = impl_->make_mtl_texture(4u, 4u, MTLPixelFormatBGRA8Unorm, false, false);
    if (impl_->dummy_black_tex != nil) {
        const uint8_t zeros[4 * 4 * 4]{};
        [impl_->dummy_black_tex replaceRegion:MTLRegionMake2D(0, 0, 4, 4) mipmapLevel:0 withBytes:zeros bytesPerRow:16];
    }
    impl_->dummy_mrt_tex = impl_->make_mtl_texture(640u, 480u, MTLPixelFormatBGRA8Unorm, true, false);

    // Default DX9 render states
    impl_->render_states.fill(0u);
    impl_->render_states[kRsSrcBlend]  = 2u; // ONE
    impl_->render_states[kRsDestBlend] = 1u; // ZERO
    impl_->render_states[kRsBlendOp]   = 1u; // ADD
    impl_->render_states[kRsAlphaFunc] = 8u; // ALWAYS
    impl_->render_states[kRsAlphaRef]  = 0u;
    impl_->render_states[kRsTextureFactor] = 0xFFFFFFFFu;
    impl_->tss_stage0_colorop.fill(4u); // MODULATE
    impl_->tss_stage0_alphaop.fill(4u);

    impl_->initialized = true;
    if (active() == nullptr) set_active(this);
    return true;
}

void D3D9MetalBridge::shutdown() {
    std::lock_guard<std::recursive_mutex> lk(impl_->mtx);
    impl_->end_active_encoder();
    if (impl_->frame_cmd_buf != nil) {
        [impl_->frame_cmd_buf commit];
        impl_->frame_cmd_buf = nil;
    }
    for (auto& [id, fr] : impl_->fonts) {
        if (fr.ct_font) CFRelease(fr.ct_font);
    }
    impl_->fonts.clear();
    impl_->effects.clear();
    impl_->surfaces.clear();
    impl_->textures.clear();
    impl_->buffers.clear();
    impl_->pipeline_cache.clear();
    impl_->sampler_cache.clear();
    impl_->cached_texture_bytes = 0u;
    impl_->dummy_black_tex = nil;
    impl_->dummy_mrt_tex   = nil;
    impl_->depth_tex       = nil;
    impl_->shader_lib      = nil;
    impl_->cmd_queue       = nil;
    impl_->device          = nil;
    impl_->metal_layer     = nil;
    impl_->vtbl_d3d9       = 0u;
    impl_->vtbl_device     = 0u;
    impl_->vtbl_texture    = 0u;
    impl_->vtbl_surface    = 0u;
    impl_->vtbl_effect     = 0u;
    impl_->vtbl_font       = 0u;
    impl_->vtbl_vbuf       = 0u;
    impl_->vtbl_ibuf       = 0u;
    impl_->d3d9_guest_va       = 0u;
    impl_->device_guest_va     = 0u;
    impl_->backbuffer_surf_va  = 0u;
    impl_->depth_surf_va       = 0u;
    impl_->fill_scratch_va     = 0u;
    impl_->font_scratch_tex_id = 0u;
    impl_->font_scratch_tex_va = 0u;
    impl_->initialized     = false;
    if (active() == this) set_active(nullptr);
}

void D3D9MetalBridge::resize(int width, int height) {
    std::lock_guard<std::recursive_mutex> lk(impl_->mtx);
    impl_->drawable_width  = (width > 0)  ? width  : 1334;
    impl_->drawable_height = (height > 0) ? height : 750;
    if (impl_->metal_layer != nil) {
        impl_->metal_layer.drawableSize = CGSizeMake(impl_->drawable_width, impl_->drawable_height);
    }
}

void D3D9MetalBridge::begin_frame() {
    std::lock_guard<std::recursive_mutex> lk(impl_->mtx);
    if (!impl_->initialized) return;
    impl_->in_frame = true;
    impl_->guest_presented_this_frame = false;
    impl_->ensure_cmd_buffer();
}

void D3D9MetalBridge::end_frame_and_present() {
    std::lock_guard<std::recursive_mutex> lk(impl_->mtx);
    if (!impl_->initialized) return;
    impl_->present_backbuffer_to_layer();
    impl_->in_frame = false;
    impl_->guest_presented_this_frame = false;
}

void D3D9MetalBridge::evict_on_memory_warning() {
    std::lock_guard<std::recursive_mutex> lk(impl_->mtx);
    // SE 2020 3 GB RAM guard: trim managed texture pool down to <= 32 MiB immediately
    impl_->evict_lru_to_budget(32u * 1024u * 1024u);
}

bool D3D9MetalBridge::is_initialized() const noexcept {
    std::lock_guard<std::recursive_mutex> lk(impl_->mtx);
    return impl_->initialized;
}

size_t D3D9MetalBridge::texture_cache_bytes() const noexcept {
    std::lock_guard<std::recursive_mutex> lk(impl_->mtx);
    return impl_->cached_texture_bytes;
}

size_t D3D9MetalBridge::texture_cache_count() const noexcept {
    std::lock_guard<std::recursive_mutex> lk(impl_->mtx);
    return impl_->textures.size();
}

uint64_t D3D9MetalBridge::draw_call_count() const noexcept {
    std::lock_guard<std::recursive_mutex> lk(impl_->mtx);
    return impl_->draw_calls;
}

// ---------------------------------------------------------------------------
// All 23 Direct3D 9 & D3DX9_36 IAT Handlers (0x0051B398..0x0051B3F4)
// ---------------------------------------------------------------------------
bool D3D9MetalBridge::handle_d3d_iat(uint32_t iat_va, const char* api_name, CpuContext& ctx, GuestMemory& mem) {
    (void)api_name;
    std::lock_guard<std::recursive_mutex> lk(impl_->mtx);
    impl_->init_com_vtables(mem);

    switch (iat_va) {
        case d3d_iat::kDirect3DCreate9: {
            if (impl_->d3d9_guest_va == 0u) {
                impl_->d3d9_guest_va = impl_->alloc_com_object(mem, impl_->vtbl_d3d9, 1u, kKindD3D9);
            }
            ctx.eax = impl_->d3d9_guest_va;
            ctx.ret_stdcall(mem, 4u);
            return true;
        }

        case d3d_iat::kD3DXMatrixRotationX: {
            const uint32_t out_va = ctx.arg32(mem, 0);
            const float angle = std::bit_cast<float>(ctx.arg32(mem, 1));
            const float c = std::cos(angle), s = std::sin(angle);
            write_matrix(mem, out_va, {
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f,    c,    s, 0.0f,
                0.0f,   -s,    c, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            });
            ctx.eax = out_va;
            ctx.ret_stdcall(mem, 8u);
            return true;
        }

        case d3d_iat::kD3DXMatrixRotationY: {
            const uint32_t out_va = ctx.arg32(mem, 0);
            const float angle = std::bit_cast<float>(ctx.arg32(mem, 1));
            const float c = std::cos(angle), s = std::sin(angle);
            write_matrix(mem, out_va, {
                   c, 0.0f,   -s, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                   s, 0.0f,    c, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            });
            ctx.eax = out_va;
            ctx.ret_stdcall(mem, 8u);
            return true;
        }

        case d3d_iat::kD3DXMatrixRotationZ: {
            const uint32_t out_va = ctx.arg32(mem, 0);
            const float angle = std::bit_cast<float>(ctx.arg32(mem, 1));
            const float c = std::cos(angle), s = std::sin(angle);
            write_matrix(mem, out_va, {
                   c,    s, 0.0f, 0.0f,
                  -s,    c, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            });
            ctx.eax = out_va;
            ctx.ret_stdcall(mem, 8u);
            return true;
        }

        case d3d_iat::kD3DXMatrixRotationYawPitchRoll: {
            const uint32_t out_va = ctx.arg32(mem, 0);
            const float yaw   = std::bit_cast<float>(ctx.arg32(mem, 1));
            const float pitch = std::bit_cast<float>(ctx.arg32(mem, 2));
            const float roll  = std::bit_cast<float>(ctx.arg32(mem, 3));
            const float cy = std::cos(yaw),   sy = std::sin(yaw);
            const float cx = std::cos(pitch), sx = std::sin(pitch);
            const float cz = std::cos(roll),  sz = std::sin(roll);
            const std::array<float, 16> rz{cz, sz, 0, 0, -sz, cz, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
            const std::array<float, 16> rx{1, 0, 0, 0, 0, cx, sx, 0, 0, -sx, cx, 0, 0, 0, 0, 1};
            const std::array<float, 16> ry{cy, 0, -sy, 0, 0, 1, 0, 0, sy, 0, cy, 0, 0, 0, 0, 1};
            write_matrix(mem, out_va, mul_matrix(mul_matrix(rz, rx), ry));
            ctx.eax = out_va;
            ctx.ret_stdcall(mem, 16u);
            return true;
        }

        case d3d_iat::kD3DXMatrixScaling: {
            const uint32_t out_va = ctx.arg32(mem, 0);
            const float sx = std::bit_cast<float>(ctx.arg32(mem, 1));
            const float sy = std::bit_cast<float>(ctx.arg32(mem, 2));
            const float sz = std::bit_cast<float>(ctx.arg32(mem, 3));
            write_matrix(mem, out_va, {
                  sx, 0.0f, 0.0f, 0.0f,
                0.0f,   sy, 0.0f, 0.0f,
                0.0f, 0.0f,   sz, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            });
            ctx.eax = out_va;
            ctx.ret_stdcall(mem, 16u);
            return true;
        }

        case d3d_iat::kD3DXMatrixTranslation: {
            const uint32_t out_va = ctx.arg32(mem, 0);
            const float x = std::bit_cast<float>(ctx.arg32(mem, 1));
            const float y = std::bit_cast<float>(ctx.arg32(mem, 2));
            const float z = std::bit_cast<float>(ctx.arg32(mem, 3));
            write_matrix(mem, out_va, {
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                   x,    y,    z, 1.0f
            });
            ctx.eax = out_va;
            ctx.ret_stdcall(mem, 16u);
            return true;
        }

        case d3d_iat::kD3DXMatrixMultiply: {
            const uint32_t out_va = ctx.arg32(mem, 0);
            const uint32_t m1_va  = ctx.arg32(mem, 1);
            const uint32_t m2_va  = ctx.arg32(mem, 2);
            write_matrix(mem, out_va, mul_matrix(read_matrix(mem, m1_va), read_matrix(mem, m2_va)));
            ctx.eax = out_va;
            ctx.ret_stdcall(mem, 12u);
            return true;
        }

        case d3d_iat::kD3DXMatrixLookAtLH: {
            const uint32_t out_va = ctx.arg32(mem, 0);
            const uint32_t eye_va = ctx.arg32(mem, 1);
            const uint32_t at_va  = ctx.arg32(mem, 2);
            const uint32_t up_va  = ctx.arg32(mem, 3);
            const float ex = mem.rf32(eye_va), ey = mem.rf32(eye_va + 4u), ez = mem.rf32(eye_va + 8u);
            float zx = mem.rf32(at_va) - ex, zy = mem.rf32(at_va + 4u) - ey, zz = mem.rf32(at_va + 8u) - ez;
            float zlen = std::sqrt(zx * zx + zy * zy + zz * zz);
            if (zlen > 1e-8f) { zx /= zlen; zy /= zlen; zz /= zlen; }
            const float ux = mem.rf32(up_va), uy = mem.rf32(up_va + 4u), uz = mem.rf32(up_va + 8u);
            float xx = uy * zz - uz * zy, xy = uz * zx - ux * zz, xz = ux * zy - uy * zx;
            float xlen = std::sqrt(xx * xx + xy * xy + xz * xz);
            if (xlen > 1e-8f) { xx /= xlen; xy /= xlen; xz /= xlen; }
            const float yx = zy * xz - zz * xy, yy = zz * xx - zx * xz, yz = zx * xy - zy * xx;
            write_matrix(mem, out_va, {
                xx, yx, zx, 0.0f,
                xy, yy, zy, 0.0f,
                xz, yz, zz, 0.0f,
                -(xx * ex + xy * ey + xz * ez),
                -(yx * ex + yy * ey + yz * ez),
                -(zx * ex + zy * ey + zz * ez),
                1.0f
            });
            ctx.eax = out_va;
            ctx.ret_stdcall(mem, 16u);
            return true;
        }

        case d3d_iat::kD3DXMatrixPerspectiveFovLH: {
            const uint32_t out_va = ctx.arg32(mem, 0);
            const float fovy   = std::bit_cast<float>(ctx.arg32(mem, 1));
            const float aspect = std::bit_cast<float>(ctx.arg32(mem, 2));
            const float zn     = std::bit_cast<float>(ctx.arg32(mem, 3));
            const float zf     = std::bit_cast<float>(ctx.arg32(mem, 4));
            const float yScale = 1.0f / std::tan(fovy * 0.5f);
            const float xScale = yScale / (aspect != 0.0f ? aspect : 1.0f);
            const float q = zf / (zf - zn);
            write_matrix(mem, out_va, {
                xScale,   0.0f,     0.0f, 0.0f,
                  0.0f, yScale,     0.0f, 0.0f,
                  0.0f,   0.0f,        q, 1.0f,
                  0.0f,   0.0f, -zn * q,  0.0f
            });
            ctx.eax = out_va;
            ctx.ret_stdcall(mem, 20u);
            return true;
        }

        case d3d_iat::kD3DXVec3Normalize: {
            const uint32_t out_va = ctx.arg32(mem, 0);
            const uint32_t in_va  = ctx.arg32(mem, 1);
            const float x = mem.rf32(in_va), y = mem.rf32(in_va + 4u), z = mem.rf32(in_va + 8u);
            const float len = std::sqrt(x * x + y * y + z * z);
            const float inv = (len > 1e-12f) ? (1.0f / len) : 0.0f;
            mem.wf32(out_va + 0u, x * inv);
            mem.wf32(out_va + 4u, y * inv);
            mem.wf32(out_va + 8u, z * inv);
            ctx.eax = out_va;
            ctx.ret_stdcall(mem, 8u);
            return true;
        }

        case d3d_iat::kD3DXVec3Transform: {
            const uint32_t out_va = ctx.arg32(mem, 0);
            const uint32_t v_va   = ctx.arg32(mem, 1);
            const uint32_t m_va   = ctx.arg32(mem, 2);
            const auto m = read_matrix(mem, m_va);
            const float x = mem.rf32(v_va), y = mem.rf32(v_va + 4u), z = mem.rf32(v_va + 8u);
            mem.wf32(out_va + 0u,  x * m[0] + y * m[4] + z * m[8]  + m[12]);
            mem.wf32(out_va + 4u,  x * m[1] + y * m[5] + z * m[9]  + m[13]);
            mem.wf32(out_va + 8u,  x * m[2] + y * m[6] + z * m[10] + m[14]);
            mem.wf32(out_va + 12u, x * m[3] + y * m[7] + z * m[11] + m[15]);
            ctx.eax = out_va;
            ctx.ret_stdcall(mem, 12u);
            return true;
        }

        case d3d_iat::kD3DXVec3TransformCoord: {
            const uint32_t out_va = ctx.arg32(mem, 0);
            const uint32_t v_va   = ctx.arg32(mem, 1);
            const uint32_t m_va   = ctx.arg32(mem, 2);
            const auto m = read_matrix(mem, m_va);
            const float x = mem.rf32(v_va), y = mem.rf32(v_va + 4u), z = mem.rf32(v_va + 8u);
            const float w = x * m[3] + y * m[7] + z * m[11] + m[15];
            const float inv = (std::fabs(w) > 1e-12f) ? (1.0f / w) : 1.0f;
            mem.wf32(out_va + 0u, (x * m[0] + y * m[4] + z * m[8]  + m[12]) * inv);
            mem.wf32(out_va + 4u, (x * m[1] + y * m[5] + z * m[9]  + m[13]) * inv);
            mem.wf32(out_va + 8u, (x * m[2] + y * m[6] + z * m[10] + m[14]) * inv);
            ctx.eax = out_va;
            ctx.ret_stdcall(mem, 12u);
            return true;
        }

        case d3d_iat::kD3DXVec3TransformArray: {
            const uint32_t out_va   = ctx.arg32(mem, 0);
            const uint32_t o_stride = ctx.arg32(mem, 1);
            const uint32_t v_va     = ctx.arg32(mem, 2);
            const uint32_t v_stride = ctx.arg32(mem, 3);
            const uint32_t m_va     = ctx.arg32(mem, 4);
            const uint32_t n        = ctx.arg32(mem, 5);
            const auto m = read_matrix(mem, m_va);
            for (uint32_t i = 0; i < n; ++i) {
                const uint32_t sv = v_va + i * v_stride;
                const uint32_t dv = out_va + i * o_stride;
                const float x = mem.rf32(sv), y = mem.rf32(sv + 4u), z = mem.rf32(sv + 8u);
                mem.wf32(dv + 0u,  x * m[0] + y * m[4] + z * m[8]  + m[12]);
                mem.wf32(dv + 4u,  x * m[1] + y * m[5] + z * m[9]  + m[13]);
                mem.wf32(dv + 8u,  x * m[2] + y * m[6] + z * m[10] + m[14]);
                mem.wf32(dv + 12u, x * m[3] + y * m[7] + z * m[11] + m[15]);
            }
            ctx.eax = out_va;
            ctx.ret_stdcall(mem, 24u);
            return true;
        }

        case d3d_iat::kD3DXVec3TransformCoordArray: {
            const uint32_t out_va   = ctx.arg32(mem, 0);
            const uint32_t o_stride = ctx.arg32(mem, 1);
            const uint32_t v_va     = ctx.arg32(mem, 2);
            const uint32_t v_stride = ctx.arg32(mem, 3);
            const uint32_t m_va     = ctx.arg32(mem, 4);
            const uint32_t n        = ctx.arg32(mem, 5);
            const auto m = read_matrix(mem, m_va);
            for (uint32_t i = 0; i < n; ++i) {
                const uint32_t sv = v_va + i * v_stride;
                const uint32_t dv = out_va + i * o_stride;
                const float x = mem.rf32(sv), y = mem.rf32(sv + 4u), z = mem.rf32(sv + 8u);
                const float w = x * m[3] + y * m[7] + z * m[11] + m[15];
                const float inv = (std::fabs(w) > 1e-12f) ? (1.0f / w) : 1.0f;
                mem.wf32(dv + 0u, (x * m[0] + y * m[4] + z * m[8]  + m[12]) * inv);
                mem.wf32(dv + 4u, (x * m[1] + y * m[5] + z * m[9]  + m[13]) * inv);
                mem.wf32(dv + 8u, (x * m[2] + y * m[6] + z * m[10] + m[14]) * inv);
            }
            ctx.eax = out_va;
            ctx.ret_stdcall(mem, 24u);
            return true;
        }

        case d3d_iat::kD3DXCreateTexture: {
            // (pDevice, Width, Height, MipLevels, Usage, Format, Pool, ppTexture) -> 32 bytes
            const uint32_t w      = ctx.arg32(mem, 1);
            const uint32_t h      = ctx.arg32(mem, 2);
            const uint32_t levels = ctx.arg32(mem, 3);
            const uint32_t usage  = ctx.arg32(mem, 4);
            const uint32_t fmt    = ctx.arg32(mem, 5);
            const uint32_t pool   = ctx.arg32(mem, 6);
            const uint32_t pp_tex = ctx.arg32(mem, 7);
            if (pp_tex && mem.in_bounds(pp_tex, 4u)) {
                mem.w32(pp_tex, create_texture_internal(*impl_, mem, w, h, levels, usage, fmt, pool));
                ctx.eax = kS_OK;
            } else {
                ctx.eax = kD3DERR_INVALIDCALL;
            }
            ctx.ret_stdcall(mem, 32u);
            return true;
        }

        case d3d_iat::kD3DXGetImageInfoFromFileInMemory: {
            // (pSrcData, SrcDataSize, pSrcInfo) -> 12 bytes
            const uint32_t data_va = ctx.arg32(mem, 0);
            const uint32_t sz      = ctx.arg32(mem, 1);
            const uint32_t info_va = ctx.arg32(mem, 2);
            uint32_t w = 0u, h = 0u;
            uint32_t fmt = kFmtA8R8G8B8, mips = 1u, img_fmt = 4u; // 4 = DDS
            DdsProbeInfo dds_info{};
            if (data_va && sz >= 4u && mem.in_bounds(data_va, sz)) {
                const uint8_t* ptr = mem.cptr(data_va);
                if (dds_probe_info(ptr, sz, dds_info)) {
                    w = dds_info.width; h = dds_info.height;
                    fmt = dds_info.d3d_format; mips = dds_info.mip_count; img_fmt = 4u;
                } else {
                    std::vector<uint8_t> tmp;
                    if (decode_generic_image_to_rgba8(ptr, sz, w, h, tmp)) {
                        fmt = kFmtA8R8G8B8; img_fmt = 3u;
                    }
                }
            }
            if (w > 0u && h > 0u && info_va && mem.in_bounds(info_va, 28u)) {
                mem.w32(info_va + 0u,  w);
                mem.w32(info_va + 4u,  h);
                mem.w32(info_va + 8u,  1u);    // Depth
                mem.w32(info_va + 12u, mips);
                mem.w32(info_va + 16u, fmt);
                mem.w32(info_va + 20u, 3u);    // D3DRTYPE_TEXTURE
                mem.w32(info_va + 24u, img_fmt);
                ctx.eax = kS_OK;
            } else {
                ctx.eax = kE_FAIL;
            }
            ctx.ret_stdcall(mem, 12u);
            return true;
        }

        case d3d_iat::kD3DXCreateTextureFromFileInMemoryEx: {
            // 15 args = 60 bytes:
            // (0:Dev, 1:Data, 2:Size, 3:W, 4:H, 5:Mips, 6:Usage, 7:Fmt, 8:Pool,
            //  9:Filter, 10:MipFilter, 11:ColorKey, 12:pSrcInfo, 13:pPalette, 14:ppTexture)
            const uint32_t data_va  = ctx.arg32(mem, 1);
            const uint32_t sz       = ctx.arg32(mem, 2);
            const uint32_t req_w    = ctx.arg32(mem, 3);
            const uint32_t req_h    = ctx.arg32(mem, 4);
            const uint32_t usage    = ctx.arg32(mem, 6);
            const uint32_t colorkey = ctx.arg32(mem, 11);
            const uint32_t info_va  = ctx.arg32(mem, 12);
            const uint32_t pp_tex   = ctx.arg32(mem, 14);

            uint32_t w = 0u, h = 0u;
            std::vector<uint8_t> rgba;
            DdsProbeInfo dds_info{};
            if (data_va && sz >= 4u && mem.in_bounds(data_va, sz) &&
                decode_generic_image_to_rgba8(mem.cptr(data_va), sz, w, h, rgba, &dds_info)) {

                if (colorkey != 0u) {
                    const uint8_t ck_r = (colorkey >> 16) & 0xFFu;
                    const uint8_t ck_g = (colorkey >> 8)  & 0xFFu;
                    const uint8_t ck_b = colorkey & 0xFFu;
                    for (size_t i = 0; i < static_cast<size_t>(w) * h; ++i) {
                        if (rgba[i * 4u + 0u] == ck_r && rgba[i * 4u + 1u] == ck_g && rgba[i * 4u + 2u] == ck_b) {
                            rgba[i * 4u + 3u] = 0u;
                        }
                    }
                }

                TextureRecord rec{};
                rec.id             = ++impl_->next_handle_id;
                rec.width          = (req_w != 0u && req_w != 0xFFFFFFFFu) ? req_w : w;
                rec.height         = (req_h != 0u && req_h != 0xFFFFFFFFu) ? req_h : h;
                rec.levels         = 1u;
                rec.usage          = usage;
                rec.format         = kFmtA8R8G8B8; // stored as straight RGBA8 in Metal
                rec.last_used_tick = ++impl_->lru_clock;
                rec.mtl_tex        = impl_->make_mtl_texture(w, h, MTLPixelFormatRGBA8Unorm, false, false);
                if (rec.mtl_tex != nil) {
                    [rec.mtl_tex replaceRegion:MTLRegionMake2D(0, 0, w, h)
                                    mipmapLevel:0
                                      withBytes:rgba.data()
                                    bytesPerRow:w * 4u];
                }
                rec.width     = w;
                rec.height    = h;
                rec.gpu_bytes = rgba.size();
                rec.cpu_backup = std::move(rgba);
                impl_->cached_texture_bytes += rec.gpu_bytes;
                impl_->evict_lru_to_budget(kTextureCacheLimitBytes);

                rec.guest_va = impl_->alloc_com_object(mem, impl_->vtbl_texture, rec.id, kKindTexture);
                impl_->textures[rec.id] = std::move(rec);

                if (pp_tex && mem.in_bounds(pp_tex, 4u)) mem.w32(pp_tex, impl_->textures[rec.id].guest_va);
                if (info_va && mem.in_bounds(info_va, 28u)) {
                    mem.w32(info_va + 0u,  w);
                    mem.w32(info_va + 4u,  h);
                    mem.w32(info_va + 8u,  1u);
                    mem.w32(info_va + 12u, dds_info.mip_count ? dds_info.mip_count : 1u);
                    mem.w32(info_va + 16u, dds_info.d3d_format ? dds_info.d3d_format : kFmtA8R8G8B8);
                    mem.w32(info_va + 20u, 3u);
                    mem.w32(info_va + 24u, dds_info.width ? 4u : 3u);
                }
                ctx.eax = kS_OK;
            } else {
                ctx.eax = kE_FAIL;
            }
            ctx.ret_stdcall(mem, 60u);
            return true;
        }

        case d3d_iat::kD3DXFillTexture: {
            // (pTexture, pFunction, pData) -> 12 bytes
            const uint32_t tex_va  = ctx.arg32(mem, 0);
            const uint32_t fn_va   = ctx.arg32(mem, 1);
            const uint32_t data_va = ctx.arg32(mem, 2);
            if (TextureRecord* tr = impl_->find_texture_by_va(mem, tex_va); tr && fn_va) {
                // Evaluate guest LPD3DXFILL2D callback on (0,0) and sample/fill texture cleanly
                if (impl_->fill_scratch_va == 0u) {
                    impl_->fill_scratch_va = mem.alloc_thunk_block(64u, 16u);
                }
                const uint32_t scratch = impl_->fill_scratch_va;
                const uint32_t out_va  = scratch + 0u;
                const uint32_t uv_va   = scratch + 16u;
                const uint32_t tsz_va  = scratch + 32u;
                mem.wf32(tsz_va + 0u, 1.0f / static_cast<float>(std::max(1u, tr->width)));
                mem.wf32(tsz_va + 4u, 1.0f / static_cast<float>(std::max(1u, tr->height)));

                // Invoke callback once at center to test uniform color or full grid if small
                CpuContext cb = ctx;
                mem.wf32(uv_va + 0u, 0.5f);
                mem.wf32(uv_va + 4u, 0.5f);
                cb.push32(mem, data_va);
                cb.push32(mem, tsz_va);
                cb.push32(mem, uv_va);
                cb.push32(mem, out_va);
                cb.push32(mem, 0x00F0FFFFu);
                call_indirect(cb, mem, fn_va);

                const float fr = std::clamp(mem.rf32(out_va + 0u), 0.0f, 1.0f);
                const float fg = std::clamp(mem.rf32(out_va + 4u), 0.0f, 1.0f);
                const float fb = std::clamp(mem.rf32(out_va + 8u), 0.0f, 1.0f);
                const float fa = std::clamp(mem.rf32(out_va + 12u), 0.0f, 1.0f);
                const uint8_t b8 = static_cast<uint8_t>(fb * 255.0f + 0.5f);
                const uint8_t g8 = static_cast<uint8_t>(fg * 255.0f + 0.5f);
                const uint8_t r8 = static_cast<uint8_t>(fr * 255.0f + 0.5f);
                const uint8_t a8 = static_cast<uint8_t>(fa * 255.0f + 0.5f);

                const bool is_rgba = (tr->mtl_tex != nil && tr->mtl_tex.pixelFormat == MTLPixelFormatRGBA8Unorm);
                std::vector<uint8_t> fill(static_cast<size_t>(tr->width) * tr->height * 4u);
                for (size_t i = 0; i < static_cast<size_t>(tr->width) * tr->height; ++i) {
                    fill[i * 4u + 0u] = is_rgba ? r8 : b8;
                    fill[i * 4u + 1u] = g8;
                    fill[i * 4u + 2u] = is_rgba ? b8 : r8;
                    fill[i * 4u + 3u] = a8;
                }
                if (tr->mtl_tex != nil && tr->mtl_tex.storageMode == MTLStorageModeShared) {
                    [tr->mtl_tex replaceRegion:MTLRegionMake2D(0, 0, tr->width, tr->height)
                                    mipmapLevel:0
                                      withBytes:fill.data()
                                    bytesPerRow:tr->width * 4u];
                }
                tr->cpu_backup = std::move(fill);
            }
            ctx.eax = kS_OK;
            ctx.ret_stdcall(mem, 12u);
            return true;
        }

        case d3d_iat::kD3DXLoadSurfaceFromSurface: {
            // (pDest, pDestPal, pDestRect, pSrc, pSrcPal, pSrcRect, Filter, ColorKey) -> 32 bytes
            const uint32_t dst_va = ctx.arg32(mem, 0);
            const uint32_t src_va = ctx.arg32(mem, 3);
            SurfaceRecord* dst = impl_->find_surface_by_va(mem, dst_va);
            SurfaceRecord* src = impl_->find_surface_by_va(mem, src_va);
            if (dst && src && dst->mtl_tex != nil && src->mtl_tex != nil &&
                dst->width == src->width && dst->height == src->height &&
                dst->mtl_tex.pixelFormat == src->mtl_tex.pixelFormat) {
                impl_->end_active_encoder();
                id<MTLCommandBuffer> cb = impl_->ensure_cmd_buffer();
                if (cb != nil) {
                    id<MTLBlitCommandEncoder> blit = [cb blitCommandEncoder];
                    [blit copyFromTexture:src->mtl_tex
                              sourceSlice:0
                              sourceLevel:0
                             sourceOrigin:MTLOriginMake(0, 0, 0)
                               sourceSize:MTLSizeMake(src->width, src->height, 1)
                                toTexture:dst->mtl_tex
                         destinationSlice:0
                         destinationLevel:0
                        destinationOrigin:MTLOriginMake(0, 0, 0)];
                    [blit endEncoding];
                }
            }
            ctx.eax = kS_OK;
            ctx.ret_stdcall(mem, 32u);
            return true;
        }

        case d3d_iat::kD3DXSaveSurfaceToFileA: {
            ctx.eax = kS_OK;
            ctx.ret_stdcall(mem, 20u);
            return true;
        }

        case d3d_iat::kD3DXCreateEffect: {
            // (pDevice, pSrcData, SrcDataLen, pDefines, pInclude, Flags, pPool, ppEffect, ppErrors) -> 36 bytes
            const uint32_t data_va = ctx.arg32(mem, 1);
            const uint32_t sz      = ctx.arg32(mem, 2);
            const uint32_t pp_fx   = ctx.arg32(mem, 7);
            if (pp_fx && mem.in_bounds(pp_fx, 4u)) {
                EffectRecord fx{};
                fx.id = ++impl_->next_handle_id;
                if (data_va && sz >= 24u && mem.in_bounds(data_va, sz)) {
                    parse_cfx_metadata(mem.cptr(data_va), sz, fx);
                }
                fx.guest_va = impl_->alloc_com_object(mem, impl_->vtbl_effect, fx.id, kKindEffect);
                impl_->effects[fx.id] = std::move(fx);
                mem.w32(pp_fx, impl_->effects[fx.id].guest_va);
                ctx.eax = kS_OK;
            } else {
                ctx.eax = kE_FAIL;
            }
            ctx.ret_stdcall(mem, 36u);
            return true;
        }

        case d3d_iat::kD3DXCreateFontA: {
            // (pDevice, Height, Width, Weight, Mips, Italic, CharSet, OutPrec, Quality, PitchFam, pFace, ppFont) -> 48 bytes
            const int32_t  height  = static_cast<int32_t>(ctx.arg32(mem, 1));
            const uint32_t weight  = ctx.arg32(mem, 3);
            const uint32_t italic  = ctx.arg32(mem, 5);
            const uint32_t face_va = ctx.arg32(mem, 10);
            const uint32_t pp_font = ctx.arg32(mem, 11);
            if (pp_font && mem.in_bounds(pp_font, 4u)) {
                FontRecord fr{};
                fr.id     = ++impl_->next_handle_id;
                fr.height = (height != 0) ? std::abs(height) : 14;
                fr.weight = weight;
                fr.italic = (italic != 0u);
                if (face_va) fr.face_name = mem.read_cstring(face_va, 64u);
                fr.ct_font = CTFontCreateWithName(CFSTR("HiraginoSans-W3"),
                                                  static_cast<CGFloat>(fr.height), nullptr);
                fr.guest_va = impl_->alloc_com_object(mem, impl_->vtbl_font, fr.id, kKindFont);
                impl_->fonts[fr.id] = fr;
                mem.w32(pp_font, fr.guest_va);
                ctx.eax = kS_OK;
            } else {
                ctx.eax = kE_FAIL;
            }
            ctx.ret_stdcall(mem, 48u);
            return true;
        }

        default:
            return false;
    }
}

} // namespace mbaa_recomp

#endif // __APPLE__
