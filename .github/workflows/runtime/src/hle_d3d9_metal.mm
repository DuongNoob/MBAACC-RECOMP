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
#include "mbaa_recomp/hle_win32.h"
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
#include <utility>
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
constexpr uint32_t kFmtA8P8     = 40u;
constexpr uint32_t kFmtP8       = 41u;
constexpr uint32_t kFmtL8       = 50u;
constexpr uint32_t kFmtD16      = 80u;
constexpr uint32_t kFmtD24S8    = 75u;
constexpr uint32_t kFmtDXT1     = 0x31545844u;
constexpr uint32_t kFmtDXT2     = 0x32545844u;
constexpr uint32_t kFmtDXT3     = 0x33545844u;
constexpr uint32_t kFmtDXT4     = 0x34545844u;
constexpr uint32_t kFmtDXT5     = 0x35545844u;

// D3DUSAGE, D3DPOOL, & D3DLOCK flags
constexpr uint32_t kUsageRenderTarget = 0x00000001u;
constexpr uint32_t kUsageDepthStencil = 0x00000002u;
constexpr uint32_t kPoolDefault       = 0u;
constexpr uint32_t kPoolManaged       = 1u;
constexpr uint32_t kPoolSystemMem     = 2u;
constexpr uint32_t kD3DLockReadOnly   = 0x00000010u;
constexpr uint32_t kD3DLockDiscard    = 0x00002000u;

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
using MtlTextureRef = id<MTLTexture>;

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
    bool     cpu_valid       = false;
    bool     lock_readonly   = false;
    uint32_t lock_x          = 0;
    uint32_t lock_y          = 0;
    uint32_t lock_w          = 0;
    uint32_t lock_h          = 0;
    uint64_t last_used_tick  = 0;
    size_t   gpu_bytes       = 0;

    MtlTextureRef mtl_tex    = nil;
    uint32_t staging_va      = 0;
    uint32_t staging_pitch   = 0;
    uint32_t staging_bytes   = 0;
    uint32_t surface_guest_va = 0; // cached level-0 IDirect3DSurface9*
    std::vector<uint8_t> cpu_backup; // canonical BGRA8 / 1B / 2B backup matching d3d_fmt_to_mtl()
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
    MtlTextureRef mtl_tex   = nil;
    uint32_t staging_va     = 0;
    uint32_t staging_pitch  = 0;
    uint32_t staging_bytes  = 0;
    uint32_t lock_x         = 0;
    uint32_t lock_y         = 0;
    uint32_t lock_w         = 0;
    uint32_t lock_h         = 0;
    bool     locked         = false;
    bool     cpu_valid      = false;
    bool     lock_readonly  = false;
    std::vector<uint8_t> cpu_backup;
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

inline bool is_dxt_format(uint32_t fmt) noexcept {
    return fmt == kFmtDXT1 || fmt == kFmtDXT2 || fmt == kFmtDXT3 ||
           fmt == kFmtDXT4 || fmt == kFmtDXT5;
}

inline DxtFormat d3d_to_dxt_format(uint32_t fmt) noexcept {
    switch (fmt) {
        case kFmtDXT1: return DxtFormat::DXT1;
        case kFmtDXT2: return DxtFormat::DXT2;
        case kFmtDXT3: return DxtFormat::DXT3;
        case kFmtDXT4: return DxtFormat::DXT4;
        case kFmtDXT5: return DxtFormat::DXT5;
        default:       return DxtFormat::Unknown;
    }
}

inline uint32_t bytes_per_pixel_for_d3d_fmt(uint32_t fmt) noexcept {
    switch (fmt) {
        case kFmtR8G8B8:   return 3u;
        case kFmtR5G6B5:
        case kFmtX1R5G5B5:
        case kFmtA1R5G5B5:
        case kFmtA4R4G4B4:
        case kFmtA8P8:
        case kFmtD16:      return 2u;
        case kFmtA8:
        case kFmtL8:
        case kFmtP8:       return 1u;
        default:           return 4u;
    }
}

inline MTLPixelFormat d3d_fmt_to_mtl(uint32_t fmt) noexcept {
    switch (fmt) {
        case kFmtA8:       return MTLPixelFormatA8Unorm;
        case kFmtL8:
        case kFmtP8:       return MTLPixelFormatR8Unorm;
        case kFmtA8P8:     return MTLPixelFormatRG8Unorm;
        case kFmtDXT1:
        case kFmtDXT2:
        case kFmtDXT3:
        case kFmtDXT4:
        case kFmtDXT5:
        case kFmtA8R8G8B8:
        case kFmtX8R8G8B8:
        default:           return MTLPixelFormatBGRA8Unorm;
    }
}

inline uint32_t mtl_bytes_per_pixel(MTLPixelFormat fmt) noexcept {
    switch (fmt) {
        case MTLPixelFormatA8Unorm:
        case MTLPixelFormatR8Unorm:  return 1u;
        case MTLPixelFormatRG8Unorm: return 2u;
        default:                     return 4u;
    }
}

inline void rgba8_to_bgra8_inplace(std::vector<uint8_t>& buf) noexcept {
    const size_t px = buf.size() / 4u;
    for (size_t i = 0; i < px; ++i) {
        std::swap(buf[i * 4u + 0u], buf[i * 4u + 2u]);
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
    if (fmt == kFmtA8 || fmt == kFmtL8 || fmt == kFmtP8) {
        out_pitch = w;
        out_bytes.resize(static_cast<size_t>(w) * h);
        for (uint32_t y = 0; y < h; ++y) {
            std::memcpy(out_bytes.data() + static_cast<size_t>(y) * out_pitch,
                        src + static_cast<size_t>(y) * src_pitch, w);
        }
        return;
    }
    if (fmt == kFmtA8P8) {
        out_pitch = w * 2u;
        out_bytes.resize(static_cast<size_t>(out_pitch) * h);
        for (uint32_t y = 0; y < h; ++y) {
            std::memcpy(out_bytes.data() + static_cast<size_t>(y) * out_pitch,
                        src + static_cast<size_t>(y) * src_pitch, out_pitch);
        }
        return;
    }
    if (is_dxt_format(fmt)) {
        out_pitch = w * 4u;
        const uint32_t blocks_y = std::max(1u, (h + 3u) / 4u);
        std::vector<uint8_t> decoded;
        if (decode_dxt_image(d3d_to_dxt_format(fmt), w, h, src,
                             static_cast<size_t>(src_pitch) * blocks_y, decoded)) {
            rgba8_to_bgra8_inplace(decoded);
            out_bytes = std::move(decoded);
        } else {
            out_bytes.assign(static_cast<size_t>(out_pitch) * h, 0u);
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

inline void write_staging_rect_to_cpu_backup(
    uint32_t fmt,
    uint32_t tex_w,
    uint32_t tex_h,
    uint32_t rx,
    uint32_t ry,
    uint32_t rw,
    uint32_t rh,
    const uint8_t* src,
    uint32_t src_pitch,
    std::vector<uint8_t>& cpu_backup)
{
    const MTLPixelFormat mfmt = d3d_fmt_to_mtl(fmt);
    const uint32_t m_bpp = mtl_bytes_per_pixel(mfmt);
    const size_t full_bytes = static_cast<size_t>(tex_w) * tex_h * m_bpp;
    if (cpu_backup.size() != full_bytes) {
        cpu_backup.assign(full_bytes, 0u);
    }

    std::vector<uint8_t> conv;
    uint32_t conv_pitch = 0u;
    convert_staging_to_mtl_pixels(fmt, rw, rh, src, src_pitch, conv, conv_pitch);

    const uint32_t dst_row_bytes = tex_w * m_bpp;
    const uint32_t copy_bytes = rw * m_bpp;
    for (uint32_t y = 0; y < rh; ++y) {
        if (ry + y >= tex_h) break;
        uint8_t* dst_row = cpu_backup.data() + static_cast<size_t>(ry + y) * dst_row_bytes + static_cast<size_t>(rx) * m_bpp;
        const uint8_t* src_row = conv.data() + static_cast<size_t>(y) * conv_pitch;
        std::memcpy(dst_row, src_row, copy_bytes);
    }
}

inline void convert_mtl_rect_to_staging(
    uint32_t fmt,
    uint32_t tex_w,
    uint32_t rx,
    uint32_t ry,
    uint32_t rw,
    uint32_t rh,
    const uint8_t* cpu_backup,
    uint8_t* dst,
    uint32_t dst_pitch)
{
    const MTLPixelFormat mfmt = d3d_fmt_to_mtl(fmt);
    const uint32_t m_bpp = mtl_bytes_per_pixel(mfmt);
    const uint32_t src_row_bytes = tex_w * m_bpp;

    for (uint32_t y = 0; y < rh; ++y) {
        const uint8_t* srow = cpu_backup + static_cast<size_t>(ry + y) * src_row_bytes + static_cast<size_t>(rx) * m_bpp;
        uint8_t* drow = dst + static_cast<size_t>(y) * dst_pitch;

        if (fmt == kFmtA8 || fmt == kFmtL8 || fmt == kFmtP8) {
            std::memcpy(drow, srow, rw);
        } else if (fmt == kFmtA8P8) {
            std::memcpy(drow, srow, static_cast<size_t>(rw) * 2u);
        } else if (fmt == kFmtA8R8G8B8 || fmt == kFmtX8R8G8B8 || fmt == kFmtUnknown) {
            std::memcpy(drow, srow, static_cast<size_t>(rw) * 4u);
        } else if (fmt == kFmtR8G8B8) {
            for (uint32_t x = 0; x < rw; ++x) {
                drow[x * 3u + 0u] = srow[x * 4u + 0u];
                drow[x * 3u + 1u] = srow[x * 4u + 1u];
                drow[x * 3u + 2u] = srow[x * 4u + 2u];
            }
        } else if (fmt == kFmtR5G6B5) {
            for (uint32_t x = 0; x < rw; ++x) {
                const uint16_t b = static_cast<uint16_t>(srow[x * 4u + 0u] >> 3);
                const uint16_t g = static_cast<uint16_t>(srow[x * 4u + 1u] >> 2);
                const uint16_t r = static_cast<uint16_t>(srow[x * 4u + 2u] >> 3);
                const uint16_t p = static_cast<uint16_t>((r << 11) | (g << 5) | b);
                drow[x * 2u + 0u] = static_cast<uint8_t>(p & 0xFFu);
                drow[x * 2u + 1u] = static_cast<uint8_t>(p >> 8);
            }
        } else if (fmt == kFmtA1R5G5B5 || fmt == kFmtX1R5G5B5) {
            for (uint32_t x = 0; x < rw; ++x) {
                const uint16_t b = static_cast<uint16_t>(srow[x * 4u + 0u] >> 3);
                const uint16_t g = static_cast<uint16_t>(srow[x * 4u + 1u] >> 3);
                const uint16_t r = static_cast<uint16_t>(srow[x * 4u + 2u] >> 3);
                const uint16_t a = (fmt == kFmtA1R5G5B5) ? ((srow[x * 4u + 3u] >= 128u) ? 0x8000u : 0u) : 0x8000u;
                const uint16_t p = static_cast<uint16_t>(a | (r << 10) | (g << 5) | b);
                drow[x * 2u + 0u] = static_cast<uint8_t>(p & 0xFFu);
                drow[x * 2u + 1u] = static_cast<uint8_t>(p >> 8);
            }
        } else if (fmt == kFmtA4R4G4B4) {
            for (uint32_t x = 0; x < rw; ++x) {
                const uint16_t b = static_cast<uint16_t>(srow[x * 4u + 0u] >> 4);
                const uint16_t g = static_cast<uint16_t>(srow[x * 4u + 1u] >> 4);
                const uint16_t r = static_cast<uint16_t>(srow[x * 4u + 2u] >> 4);
                const uint16_t a = static_cast<uint16_t>(srow[x * 4u + 3u] >> 4);
                const uint16_t p = static_cast<uint16_t>((a << 12) | (r << 8) | (g << 4) | b);
                drow[x * 2u + 0u] = static_cast<uint8_t>(p & 0xFFu);
                drow[x * 2u + 1u] = static_cast<uint8_t>(p >> 8);
            }
        } else {
            std::memcpy(drow, srow, static_cast<size_t>(rw) * 4u);
        }
    }
}

inline void parse_clamped_lock_rect(
    const GuestMemory& mem,
    uint32_t rect_va,
    uint32_t tex_w,
    uint32_t tex_h,
    uint32_t& out_x,
    uint32_t& out_y,
    uint32_t& out_w,
    uint32_t& out_h) noexcept
{
    out_x = 0u;
    out_y = 0u;
    out_w = std::max(1u, tex_w);
    out_h = std::max(1u, tex_h);
    if (rect_va != 0u && mem.in_bounds(rect_va, 16u)) {
        const int32_t l = static_cast<int32_t>(mem.r32(rect_va + 0u));
        const int32_t t = static_cast<int32_t>(mem.r32(rect_va + 4u));
        const int32_t r = static_cast<int32_t>(mem.r32(rect_va + 8u));
        const int32_t b = static_cast<int32_t>(mem.r32(rect_va + 12u));
        if (r > l && b > t) {
            const int32_t cl = std::clamp<int32_t>(l, 0, static_cast<int32_t>(tex_w) - 1);
            const int32_t ct = std::clamp<int32_t>(t, 0, static_cast<int32_t>(tex_h) - 1);
            const int32_t cr = std::clamp<int32_t>(r, cl + 1, static_cast<int32_t>(tex_w));
            const int32_t cb = std::clamp<int32_t>(b, ct + 1, static_cast<int32_t>(tex_h));
            out_x = static_cast<uint32_t>(cl);
            out_y = static_cast<uint32_t>(ct);
            out_w = static_cast<uint32_t>(cr - cl);
            out_h = static_cast<uint32_t>(cb - ct);
        }
    }
}

inline void compute_lock_pitch_bytes(
    uint32_t fmt,
    uint32_t rw,
    uint32_t rh,
    uint32_t& out_pitch,
    uint32_t& out_bytes) noexcept
{
    if (is_dxt_format(fmt)) {
        const uint32_t bx = std::max(1u, (rw + 3u) / 4u);
        const uint32_t by = std::max(1u, (rh + 3u) / 4u);
        const uint32_t block_bytes = (fmt == kFmtDXT1) ? 8u : 16u;
        out_pitch = bx * block_bytes;
        out_bytes = out_pitch * by;
    } else {
        const uint32_t bpp = bytes_per_pixel_for_d3d_fmt(fmt);
        out_pitch = (rw * bpp + 3u) & ~3u;
        out_bytes = out_pitch * std::max(1u, rh);
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

    static constexpr uint32_t kTransientRingSlots     = 4u;
    static constexpr size_t   kTransientRingSlotBytes = 2u * 1024u * 1024u;
    std::array<id<MTLBuffer>, kTransientRingSlots> transient_rings{};
    uint32_t transient_ring_slot   = 0u;
    size_t   transient_ring_offset = 0u;

    int drawable_width  = 1334;
    int drawable_height = 750;
    uint32_t logical_width  = kGameLogicalWidth;
    uint32_t logical_height = kGameLogicalHeight;

    bool initialized = false;
    bool in_frame    = false;
    bool in_scene    = false;
    bool guest_presented_this_frame = false;
    bool encoder_rt_dirty = true;
    uint32_t active_encoder_mrt_count = 0u;
    bool scissor_valid = false;
    MTLScissorRect scissor_rect{0, 0, 640, 480};
    uint64_t lru_clock = 1;
    uint64_t draw_calls = 0;
    uint64_t clear_calls = 0;
    uint64_t present_calls = 0;
    uint64_t create_device_calls = 0;
    uint64_t create_tex_calls = 0;
    uint64_t create_fx_calls = 0;
    uint64_t create_vb_calls = 0;
    uint64_t create_ib_calls = 0;
    uint64_t pso_failures = 0;
    uint64_t draw_dropped_no_enc = 0;
    uint64_t draw_dropped_no_pso = 0;

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
    uint32_t current_vb_id      = 0;
    uint32_t current_vb_offset  = 0;
    uint32_t current_vb_va      = 0;
    uint32_t current_vb_stride  = 32;
    uint32_t current_ib_id      = 0;
    uint32_t current_ib_va      = 0;
    uint32_t vp_x = 0, vp_y = 0, vp_w = 640, vp_h = 480;
    uint32_t active_effect_id   = 0;
    MbaaShaderPassId active_pass = MBAA_PASS_FIXED_2D;

    // -----------------------------------------------------------------------
    // Helpers: Guest COM Object Allocation & Resolution
    // -----------------------------------------------------------------------
    uint32_t alloc_com_object(GuestMemory& mem, uint32_t vtbl_va, uint32_t handle_id, uint32_t kind_tag, bool transient = false) {
        uint32_t obj_va = transient ? mem.guest_alloc(16u, 16u) : 0u;
        if (obj_va == 0u) {
            obj_va = mem.alloc_thunk_block(16u, 16u);
        }
        if (obj_va != 0u) {
            mem.w32(obj_va + 0u, vtbl_va);
            mem.w32(obj_va + 4u, handle_id);
            mem.w32(obj_va + 8u, 1u);
            mem.w32(obj_va + 12u, kind_tag);
        }
        return obj_va;
    }

    BufferRecord* find_buffer_by_va(const GuestMemory& mem, uint32_t buf_va) {
        if (buf_va == 0u || !mem.in_bounds(buf_va, 16u)) return nullptr;
        const uint32_t kind = mem.r32(buf_va + 12u);
        if (kind != kKindVBuf && kind != kKindIBuf) return nullptr;
        auto it = buffers.find(mem.r32(buf_va + 4u));
        return (it != buffers.end()) ? &it->second : nullptr;
    }

    id<MTLTexture> resolve_surface_texture(const GuestMemory& mem, uint32_t surf_va) {
        SurfaceRecord* s = find_surface_by_va(mem, surf_va);
        if (!s) return nil;
        if (s->parent_tex_id != 0u) {
            auto tit = textures.find(s->parent_tex_id);
            if (tit != textures.end()) {
                if (tit->second.mtl_tex != nil) return tit->second.mtl_tex;
                if (tit->second.cpu_valid && !tit->second.cpu_backup.empty() &&
                    tit->second.pool != kPoolSystemMem) {
                    return resolve_stage_texture(mem, tit->second.guest_va);
                }
            }
        }
        return s->mtl_tex;
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
    // Metal Texture Creation, Transient Ring Buffer, & 192 MiB LRU Cache Eviction
    // -----------------------------------------------------------------------
    id<MTLTexture> make_mtl_texture(uint32_t w, uint32_t h, MTLPixelFormat fmt, bool is_rt, bool is_ds) {
        if (!device || w == 0u || h == 0u) return nil;
        id<MTLTexture> tex = nil;
        @autoreleasepool {
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
            tex = [device newTextureWithDescriptor:desc];
        }
        return tex;
    }

    struct TransientSlice {
        id<MTLBuffer> buf = nil;
        NSUInteger offset = 0u;
    };

    TransientSlice alloc_transient_buffer(const void* data, size_t bytes) {
        TransientSlice res{};
        if (!device || !data || bytes == 0u) return res;
        const size_t aligned = (transient_ring_offset + 15u) & ~size_t(15u);
        if (bytes <= kTransientRingSlotBytes && aligned + bytes <= kTransientRingSlotBytes) {
            id<MTLBuffer> ring = transient_rings[transient_ring_slot];
            if (ring == nil) {
                @autoreleasepool {
                    ring = [device newBufferWithLength:kTransientRingSlotBytes
                                               options:MTLResourceStorageModeShared];
                }
                transient_rings[transient_ring_slot] = ring;
            }
            if (ring != nil) {
                std::memcpy(static_cast<uint8_t*>([ring contents]) + aligned, data, bytes);
                transient_ring_offset = aligned + bytes;
                res.buf = ring;
                res.offset = static_cast<NSUInteger>(aligned);
                return res;
            }
        }
        // Fallback for oversized single-frame submissions
        id<MTLBuffer> tmp = nil;
        @autoreleasepool {
            tmp = [device newBufferWithBytes:data
                                      length:bytes
                                     options:MTLResourceStorageModeShared];
        }
        res.buf = tmp;
        res.offset = 0u;
        return res;
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

        @autoreleasepool {
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
    }

    id<MTLTexture> resolve_stage_texture(const GuestMemory& mem, uint32_t tex_va) {
        TextureRecord* rec = find_texture_by_va(mem, tex_va);
        if (!rec) return dummy_black_tex;
        rec->last_used_tick = ++lru_clock;
        if (rec->mtl_tex == nil && rec->cpu_valid && !rec->cpu_backup.empty()) {
            const MTLPixelFormat mfmt = d3d_fmt_to_mtl(rec->format);
            rec->mtl_tex = make_mtl_texture(rec->width, rec->height, mfmt, false, false);
            if (rec->mtl_tex != nil) {
                const uint32_t bpp = mtl_bytes_per_pixel(mfmt);
                @autoreleasepool {
                    [rec->mtl_tex replaceRegion:MTLRegionMake2D(0, 0, rec->width, rec->height)
                                    mipmapLevel:0
                                      withBytes:rec->cpu_backup.data()
                                    bytesPerRow:rec->width * bpp];
                }
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

        id<MTLRenderPipelineState> pso = nil;
        @autoreleasepool {
            const auto& entry = shader_manifest::entry_for_pass_id(static_cast<MbaaShaderPassId>(key.pass_id));
            NSString* vsName = [NSString stringWithUTF8String:entry.vertex_fn];
            NSString* psName = [NSString stringWithUTF8String:entry.fragment_fn];
            id<MTLFunction> vsFn = [shader_lib newFunctionWithName:vsName];
            id<MTLFunction> psFn = [shader_lib newFunctionWithName:psName];
            if (!vsFn || !psFn) {
                ++pso_failures;
                hle_win32_log("[D3D9MetalBridge] Missing Metal shader function %s / %s",
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
                // DX9 D3DRS_ALPHABLENDENABLE applies uniformly across all MRT color attachments
                if (key.blend_enable && key.pass_id != MBAA_PASS_PRESENT_BLIT) {
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
            pso = [device newRenderPipelineStateWithDescriptor:desc error:&err];
            if (!pso || err) {
                ++pso_failures;
                hle_win32_log("[D3D9MetalBridge] PSO build failed for %s: %s",
                              entry.fragment_fn, err ? err.localizedDescription.UTF8String : "unknown");
                pso = nil;
            }
        }
        if (pso != nil) {
            pipeline_cache[key] = pso;
        }
        return pso;
    }

    id<MTLSamplerState> get_sampler(const SamplerStateBlock& s) {
        SamplerCacheKey k{s.address_u, s.address_v, s.mag_filter, s.min_filter, s.mip_filter};
        auto it = sampler_cache.find(k);
        if (it != sampler_cache.end()) return it->second;
        if (!device) return nil;

        id<MTLSamplerState> samp = nil;
        @autoreleasepool {
            MTLSamplerDescriptor* desc = [[MTLSamplerDescriptor alloc] init];
            desc.sAddressMode = d3d_addr_to_mtl(s.address_u);
            desc.tAddressMode = d3d_addr_to_mtl(s.address_v);
            desc.magFilter    = (s.mag_filter >= 2u) ? MTLSamplerMinMagFilterLinear : MTLSamplerMinMagFilterNearest;
            desc.minFilter    = (s.min_filter >= 2u) ? MTLSamplerMinMagFilterLinear : MTLSamplerMinMagFilterNearest;
            desc.mipFilter    = MTLSamplerMipFilterNotMipmapped;
            samp = [device newSamplerStateWithDescriptor:desc];
        }
        if (samp != nil) {
            sampler_cache[k] = samp;
        }
        return samp;
    }

    // -----------------------------------------------------------------------
    // Active Render Pass Encoder Management
    // -----------------------------------------------------------------------
    void end_active_encoder() {
        if (active_encoder != nil) {
            @autoreleasepool {
                [active_encoder endEncoding];
                active_encoder = nil;
            }
        }
        active_encoder_mrt_count = 0u;
    }

    id<MTLCommandBuffer> ensure_cmd_buffer() {
        if (frame_cmd_buf == nil && cmd_queue != nil) {
            @autoreleasepool {
                frame_cmd_buf = [cmd_queue commandBuffer];
            }
        }
        return frame_cmd_buf;
    }

    id<MTLTexture> resolve_rt_texture(const GuestMemory& mem, uint32_t rt_index) {
        if (rt_index >= bound_rt_surfaces.size()) return nil;
        const uint32_t surf_va = bound_rt_surfaces[rt_index];
        if (surf_va == 0u) return nil;
        return resolve_surface_texture(mem, surf_va);
    }

    id<MTLTexture> resolve_active_depth_texture(const GuestMemory& mem, id<MTLTexture> rt0) {
        if (bound_ds_surface == 0u || rt0 == nil) return nil;
        id<MTLTexture> ds_tex = resolve_surface_texture(mem, bound_ds_surface);
        if (ds_tex == nil) ds_tex = depth_tex;
        if (ds_tex != nil && ds_tex.width == rt0.width && ds_tex.height == rt0.height) {
            return ds_tex;
        }
        return nil;
    }

    void apply_encoder_scissor(id<MTLRenderCommandEncoder> enc, uint32_t rtw, uint32_t rth) {
        if (enc == nil || rtw == 0u || rth == 0u) return;
        if (render_states[kRsScissorTestEnable] && scissor_valid) {
            const NSUInteger sx = std::min<NSUInteger>(scissor_rect.x, rtw - 1u);
            const NSUInteger sy = std::min<NSUInteger>(scissor_rect.y, rth - 1u);
            const NSUInteger sw = std::max<NSUInteger>(1u, std::min<NSUInteger>(scissor_rect.width, rtw - sx));
            const NSUInteger sh = std::max<NSUInteger>(1u, std::min<NSUInteger>(scissor_rect.height, rth - sy));
            [enc setScissorRect:MTLScissorRect{sx, sy, sw, sh}];
        } else {
            [enc setScissorRect:MTLScissorRect{0u, 0u, rtw, rth}];
        }
    }

    id<MTLRenderCommandEncoder> ensure_render_encoder(
        const GuestMemory& mem,
        uint32_t mrt_count,
        bool clear_color = false,
        uint32_t clear_argb = 0u,
        bool clear_depth = false,
        double clear_z = 1.0,
        uint32_t clear_stencil = 0u)
    {
        id<MTLCommandBuffer> cb = ensure_cmd_buffer();
        if (!cb) return nil;

        if (active_encoder != nil && !encoder_rt_dirty && !clear_color && !clear_depth &&
            active_encoder_mrt_count == mrt_count) {
            return active_encoder;
        }
        end_active_encoder();

        id<MTLTexture> rt0 = resolve_rt_texture(mem, 0u);
        if (!rt0) return nil;

        @autoreleasepool {
            MTLRenderPassDescriptor* rpd = [MTLRenderPassDescriptor renderPassDescriptor];
            auto setup_rt = [&](NSUInteger idx, id<MTLTexture> tex, bool do_clear) {
                rpd.colorAttachments[idx].texture     = tex;
                rpd.colorAttachments[idx].loadAction  = do_clear ? MTLLoadActionClear : MTLLoadActionLoad;
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
                setup_rt(1, rt1 ? rt1 : dummy_mrt_tex, clear_color && (rt1 != nil));
            }
            if (mrt_count >= 3u) {
                id<MTLTexture> rt2 = resolve_rt_texture(mem, 2u);
                setup_rt(2, rt2 ? rt2 : dummy_mrt_tex, clear_color && (rt2 != nil));
            }

            id<MTLTexture> ds_tex = resolve_active_depth_texture(mem, rt0);
            if (ds_tex != nil) {
                rpd.depthAttachment.texture       = ds_tex;
                rpd.depthAttachment.loadAction    = clear_depth ? MTLLoadActionClear : MTLLoadActionLoad;
                rpd.depthAttachment.storeAction   = MTLStoreActionStore;
                rpd.depthAttachment.clearDepth    = clear_z;
                rpd.stencilAttachment.texture     = ds_tex;
                rpd.stencilAttachment.loadAction  = clear_depth ? MTLLoadActionClear : MTLLoadActionLoad;
                rpd.stencilAttachment.storeAction = MTLStoreActionStore;
                rpd.stencilAttachment.clearStencil = clear_stencil;
            }

            active_encoder = [cb renderCommandEncoderWithDescriptor:rpd];
            encoder_rt_dirty = false;
            active_encoder_mrt_count = (active_encoder != nil) ? mrt_count : 0u;

            if (active_encoder != nil) {
                const uint32_t rtw = static_cast<uint32_t>(rt0.width);
                const uint32_t rth = static_cast<uint32_t>(rt0.height);
                const uint32_t vx  = std::min<uint32_t>(vp_x, rtw > 0u ? rtw - 1u : 0u);
                const uint32_t vy  = std::min<uint32_t>(vp_y, rth > 0u ? rth - 1u : 0u);
                const uint32_t vw  = std::max<uint32_t>(1u, std::min<uint32_t>(vp_w ? vp_w : rtw, rtw - vx));
                const uint32_t vh  = std::max<uint32_t>(1u, std::min<uint32_t>(vp_h ? vp_h : rth, rth - vy));
                MTLViewport mvp{
                    static_cast<double>(vx),
                    static_cast<double>(vy),
                    static_cast<double>(vw),
                    static_cast<double>(vh),
                    0.0, 1.0
                };
                [active_encoder setViewport:mvp];
                apply_encoder_scissor(active_encoder, rtw, rth);
            }
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

        @autoreleasepool {
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
            if (!enc) {
                ++draw_dropped_no_enc;
                return;
            }

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
                if (!idata) return std::min<uint32_t>(k, vcount - 1u);
                const uint32_t raw_idx = (index_fmt == 101u)
                    ? read_u16_le_buf(idata + k * 2u)
                    : read_u32_le_buf(idata + k * 4u);
                return std::min<uint32_t>(raw_idx, vcount - 1u);
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
            id<MTLTexture> ds_tex = resolve_active_depth_texture(mem, rt0);

            uint32_t src_b = render_states[kRsSrcBlend] ? render_states[kRsSrcBlend] : 5u;
            uint32_t dst_b = render_states[kRsDestBlend] ? render_states[kRsDestBlend] : 6u;
            if (src_b == 12u) { // D3DBLEND_BOTHSRCALPHA
                src_b = 5u;
                dst_b = 6u;
            } else if (src_b == 13u) { // D3DBLEND_BOTHINVSRCALPHA
                src_b = 6u;
                dst_b = 5u;
            }

            PipelineCacheKey pkey{};
            pkey.pass_id      = static_cast<uint32_t>(pass_id);
            pkey.rt_fmt0      = rt0 ? static_cast<uint32_t>(rt0.pixelFormat) : static_cast<uint32_t>(MTLPixelFormatBGRA8Unorm);
            pkey.rt_fmt1      = rt1 ? static_cast<uint32_t>(rt1.pixelFormat) : static_cast<uint32_t>(MTLPixelFormatBGRA8Unorm);
            pkey.rt_fmt2      = rt2 ? static_cast<uint32_t>(rt2.pixelFormat) : static_cast<uint32_t>(MTLPixelFormatBGRA8Unorm);
            pkey.has_depth    = (ds_tex != nil) ? 1u : 0u;
            pkey.blend_enable = render_states[kRsAlphaBlendEnable] ? 1u : 0u;
            pkey.src_blend    = static_cast<uint8_t>(src_b);
            pkey.dst_blend    = static_cast<uint8_t>(dst_b);
            pkey.blend_op     = static_cast<uint8_t>(render_states[kRsBlendOp] ? render_states[kRsBlendOp] : 1u);
            pkey.sep_alpha    = render_states[kRsSeparateAlphaBlendEnable] ? 1u : 0u;
            pkey.src_alpha    = static_cast<uint8_t>(render_states[kRsSrcBlendAlpha] ? render_states[kRsSrcBlendAlpha] : 2u);
            pkey.dst_alpha    = static_cast<uint8_t>(render_states[kRsDestBlendAlpha] ? render_states[kRsDestBlendAlpha] : 1u);
            pkey.alpha_op     = static_cast<uint8_t>(render_states[kRsBlendOpAlpha] ? render_states[kRsBlendOpAlpha] : 1u);

            id<MTLRenderPipelineState> pso = get_pipeline(pkey);
            if (!pso) {
                ++draw_dropped_no_pso;
                return;
            }

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

            const size_t vbytes = verts.size() * sizeof(MbaaMetalVertex);
            if (vbytes <= 4096u) {
                [enc setVertexBytes:verts.data() length:vbytes atIndex:MBAA_BUF_VERTICES];
            } else {
                TransientSlice vslice = alloc_transient_buffer(verts.data(), vbytes);
                if (vslice.buf == nil) {
                    return;
                }
                [enc setVertexBuffer:vslice.buf offset:vslice.offset atIndex:MBAA_BUF_VERTICES];
            }
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
                TransientSlice islice = alloc_transient_buffer(draw_indices, draw_index_count * sizeof(uint32_t));
                if (islice.buf == nil) {
                    return;
                }
                [enc drawIndexedPrimitives:mtl_prim
                                indexCount:draw_index_count
                                 indexType:MTLIndexTypeUInt32
                               indexBuffer:islice.buf
                         indexBufferOffset:islice.offset];
            } else {
                [enc drawPrimitives:mtl_prim vertexStart:0 vertexCount:draw_index_count];
            }
            ++draw_calls;
            if (draw_calls == 1u) {
                hle_win32_log("First D3D9 draw: pass=%d fvf=0x%x vcnt=%u pcnt=%u rt=%ux%u tex0=0x%08x",
                              static_cast<int>(pass_id), current_fvf, vcount, prim_count,
                              static_cast<uint32_t>(rtw), static_cast<uint32_t>(rth), bound_textures[0]);
            }
        }
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
                @autoreleasepool {
                    [frame_cmd_buf commit];
                    frame_cmd_buf = nil;
                }
                transient_ring_slot = (transient_ring_slot + 1u) % kTransientRingSlots;
                transient_ring_offset = 0u;
            }
            return;
        }

        @autoreleasepool {
            id<CAMetalDrawable> drawable = [metal_layer nextDrawable];
            if (drawable == nil) {
                if (frame_cmd_buf != nil) {
                    [frame_cmd_buf commit];
                    frame_cmd_buf = nil;
                    transient_ring_slot = (transient_ring_slot + 1u) % kTransientRingSlots;
                    transient_ring_offset = 0u;
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
            transient_ring_slot = (transient_ring_slot + 1u) % kTransientRingSlots;
            transient_ring_offset = 0u;
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

inline std::atomic<D3D9MetalBridge::Impl*>& global_impl_slot() noexcept {
    static std::atomic<D3D9MetalBridge::Impl*> s_impl{nullptr};
    return s_impl;
}

inline D3D9MetalBridge::Impl* active_impl() noexcept {
    return global_impl_slot().load(std::memory_order_acquire);
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
                bool can_free_self = false;
                @autoreleasepool {
                    if (kind == kKindTexture) {
                        for (uint32_t& bva : im->bound_textures) {
                            if (bva == self_va) bva = 0u;
                        }
                        if (auto it = im->textures.find(hid); it != im->textures.end()) {
                            auto& tr = it->second;
                            if (tr.mtl_tex != nil && !tr.evicted && !tr.is_render_target && !tr.is_depth_stencil) {
                                if (im->cached_texture_bytes >= tr.gpu_bytes) {
                                    im->cached_texture_bytes -= tr.gpu_bytes;
                                } else {
                                    im->cached_texture_bytes = 0u;
                                }
                            }
                            // If a live child RT/DS surface outlives its parent texture, transfer ownership cleanly
                            if (tr.surface_guest_va != 0u && (tr.is_render_target || tr.is_depth_stencil) && tr.mtl_tex != nil) {
                                if (SurfaceRecord* sr = im->find_surface_by_va(mem, tr.surface_guest_va)) {
                                    sr->mtl_tex = tr.mtl_tex;
                                    sr->parent_tex_id = 0u;
                                }
                            }
                            tr.mtl_tex = nil;
                            if (tr.staging_va) mem.guest_free(tr.staging_va);
                            im->textures.erase(it);
                        }
                        can_free_self = true;
                    } else if (kind == kKindSurface && hid > 2u) {
                        for (uint32_t& rva : im->bound_rt_surfaces) {
                            if (rva == self_va) {
                                im->end_active_encoder();
                                rva = 0u;
                                im->encoder_rt_dirty = true;
                            }
                        }
                        if (im->bound_ds_surface == self_va) {
                            im->end_active_encoder();
                            im->bound_ds_surface = 0u;
                            im->encoder_rt_dirty = true;
                        }
                        if (auto it = im->surfaces.find(hid); it != im->surfaces.end()) {
                            auto& sr = it->second;
                            if (sr.parent_tex_id != 0u) {
                                if (auto tit = im->textures.find(sr.parent_tex_id); tit != im->textures.end()) {
                                    if (tit->second.surface_guest_va == self_va) {
                                        tit->second.surface_guest_va = 0u;
                                    }
                                }
                            }
                            sr.mtl_tex = nil;
                            if (sr.staging_va) mem.guest_free(sr.staging_va);
                            im->surfaces.erase(it);
                        }
                        can_free_self = true;
                    } else if (kind == kKindEffect) {
                        if (im->active_effect_id == hid || im->active_effect_id == self_va) {
                            im->active_effect_id = 0u;
                        }
                        im->effects.erase(hid);
                        can_free_self = true;
                    } else if (kind == kKindFont) {
                        if (auto it = im->fonts.find(hid); it != im->fonts.end()) {
                            if (it->second.ct_font) CFRelease(it->second.ct_font);
                            im->fonts.erase(it);
                        }
                        can_free_self = true;
                    } else if (kind == kKindVBuf || kind == kKindIBuf) {
                        if (auto it = im->buffers.find(hid); it != im->buffers.end()) {
                            if (it->second.data_va) mem.guest_free(it->second.data_va);
                            im->buffers.erase(it);
                        }
                        can_free_self = true;
                    }
                }
                if (can_free_self && self_va >= GuestMemory::kHeapBase) {
                    mem.guest_free(self_va);
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
    ++im->create_device_calls;
    hle_win32_log("D3D9 CreateDevice %ux%u -> dev=0x%08x bb=0x%08x",
                  bb_w, bb_h, im->device_guest_va, im->backbuffer_surf_va);

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
        if (im->d3d9_guest_va != 0u) {
            mem.w32(im->d3d9_guest_va + 8u, mem.r32(im->d3d9_guest_va + 8u) + 1u);
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void com_resource_get_device(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pp_dev_va = ctx.arg32(mem, 1);
    if (auto* im = active_impl(); im && pp_dev_va && mem.in_bounds(pp_dev_va, 4u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        mem.w32(pp_dev_va, im->device_guest_va);
        if (im->device_guest_va != 0u) {
            mem.w32(im->device_guest_va + 8u, mem.r32(im->device_guest_va + 8u) + 1u);
        }
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
        ++im->present_calls;
        if (im->present_calls == 1u) {
            hle_win32_log("First D3D9 Present call (in_frame=%d draws=%llu)",
                          im->in_frame ? 1 : 0, static_cast<unsigned long long>(im->draw_calls));
        }
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
    const uint32_t eff_fmt = format ? format : kFmtA8R8G8B8;
    const MTLPixelFormat mfmt = d3d_fmt_to_mtl(eff_fmt);
    const uint32_t m_bpp = mtl_bytes_per_pixel(mfmt);

    TextureRecord rec{};
    rec.id               = ++im.next_handle_id;
    rec.width            = w;
    rec.height           = h;
    rec.levels           = levels ? levels : 1u;
    rec.usage            = usage;
    rec.format           = eff_fmt;
    rec.pool             = pool;
    rec.is_render_target = is_rt;
    rec.is_depth_stencil = is_ds;
    rec.last_used_tick   = ++im.lru_clock;
    rec.gpu_bytes        = static_cast<size_t>(w) * h * m_bpp;

    // Defer GPU allocation for D3DPOOL_SYSTEMMEM textures (e.g. 256x256 .cg tile sheets
    // that are only used as CPU sources for D3DXLoadSurfaceFromSurface).
    if (pool == kPoolSystemMem && !is_rt && !is_ds) {
        rec.mtl_tex = nil;
    } else {
        rec.mtl_tex = im.make_mtl_texture(w, h, mfmt, is_rt, is_ds);
        if (!is_rt && !is_ds && rec.mtl_tex != nil) {
            im.cached_texture_bytes += rec.gpu_bytes;
            im.evict_lru_to_budget(D3D9MetalBridge::kTextureCacheLimitBytes);
        }
    }

    rec.guest_va = im.alloc_com_object(mem, im.vtbl_texture, rec.id, kKindTexture, true);
    ++im.create_tex_calls;
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

void com_dev_create_vertex_buffer(CpuContext& ctx, GuestMemory& mem) {
    // (this, Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle) -> 28 bytes
    const uint32_t len   = ctx.arg32(mem, 1);
    const uint32_t fvf   = ctx.arg32(mem, 3);
    const uint32_t pp_vb = ctx.arg32(mem, 5);
    if (auto* im = active_impl(); im && pp_vb && mem.in_bounds(pp_vb, 4u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        BufferRecord br{};
        br.id       = ++im->next_handle_id;
        br.size     = std::max<uint32_t>(len, 16u);
        br.fvf      = fvf;
        br.is_index = false;
        br.data_va  = mem.guest_calloc(1u, br.size);
        if (br.data_va != 0u) {
            br.guest_va = im->alloc_com_object(mem, im->vtbl_vbuf, br.id, kKindVBuf, true);
            im->buffers[br.id] = br;
            ++im->create_vb_calls;
            if (im->create_vb_calls <= 3u) {
                hle_win32_log("CreateVertexBuffer #%llu size=%u fvf=0x%x -> 0x%08x",
                              static_cast<unsigned long long>(im->create_vb_calls),
                              br.size, fvf, br.guest_va);
            }
            mem.w32(pp_vb, br.guest_va);
            ctx.eax = kS_OK;
        } else {
            ctx.eax = kE_FAIL;
        }
    } else {
        ctx.eax = kD3DERR_INVALIDCALL;
    }
    ctx.ret_stdcall(mem, 28u);
}

void com_dev_create_index_buffer(CpuContext& ctx, GuestMemory& mem) {
    // (this, Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle) -> 28 bytes
    const uint32_t len   = ctx.arg32(mem, 1);
    const uint32_t fmt   = ctx.arg32(mem, 3);
    const uint32_t pp_ib = ctx.arg32(mem, 5);
    if (auto* im = active_impl(); im && pp_ib && mem.in_bounds(pp_ib, 4u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        BufferRecord br{};
        br.id       = ++im->next_handle_id;
        br.size     = std::max<uint32_t>(len, 16u);
        br.format   = fmt ? fmt : 101u; // D3DFMT_INDEX16
        br.is_index = true;
        br.data_va  = mem.guest_calloc(1u, br.size);
        if (br.data_va != 0u) {
            br.guest_va = im->alloc_com_object(mem, im->vtbl_ibuf, br.id, kKindIBuf, true);
            im->buffers[br.id] = br;
            ++im->create_ib_calls;
            if (im->create_ib_calls <= 3u) {
                hle_win32_log("CreateIndexBuffer #%llu size=%u fmt=%u -> 0x%08x",
                              static_cast<unsigned long long>(im->create_ib_calls),
                              br.size, br.format, br.guest_va);
            }
            mem.w32(pp_ib, br.guest_va);
            ctx.eax = kS_OK;
        } else {
            ctx.eax = kE_FAIL;
        }
    } else {
        ctx.eax = kD3DERR_INVALIDCALL;
    }
    ctx.ret_stdcall(mem, 28u);
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
        sr.guest_va = im->alloc_com_object(mem, im->vtbl_surface, sr.id, kKindSurface, true);
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
        sr.guest_va = im->alloc_com_object(mem, im->vtbl_surface, sr.id, kKindSurface, true);
        im->surfaces[sr.id] = sr;
        mem.w32(pp_surf, sr.guest_va);
        ctx.eax = kS_OK;
    } else {
        ctx.eax = kD3DERR_INVALIDCALL;
    }
    ctx.ret_stdcall(mem, 36u);
}

void com_dev_stretch_rect(CpuContext& ctx, GuestMemory& mem) {
    // (this, pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter) -> 24 bytes
    const uint32_t src_va      = ctx.arg32(mem, 1);
    const uint32_t src_rect_va = ctx.arg32(mem, 2);
    const uint32_t dst_va      = ctx.arg32(mem, 3);
    const uint32_t dst_rect_va = ctx.arg32(mem, 4);
    const uint32_t filter      = ctx.arg32(mem, 5);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        @autoreleasepool {
            id<MTLTexture> src_tex = im->resolve_surface_texture(mem, src_va);
            id<MTLTexture> dst_tex = im->resolve_surface_texture(mem, dst_va);
            if (src_tex != nil && dst_tex != nil && src_tex != dst_tex) {
                im->end_active_encoder();
                const uint32_t sw_full = static_cast<uint32_t>(src_tex.width);
                const uint32_t sh_full = static_cast<uint32_t>(src_tex.height);
                const uint32_t dw_full = static_cast<uint32_t>(dst_tex.width);
                const uint32_t dh_full = static_cast<uint32_t>(dst_tex.height);

                uint32_t sx = 0u, sy = 0u, sw = sw_full, sh = sh_full;
                uint32_t dx = 0u, dy = 0u, dw = dw_full, dh = dh_full;
                parse_clamped_lock_rect(mem, src_rect_va, sw_full, sh_full, sx, sy, sw, sh);
                parse_clamped_lock_rect(mem, dst_rect_va, dw_full, dh_full, dx, dy, dw, dh);

                if (id<MTLCommandBuffer> cb = im->ensure_cmd_buffer()) {
                    if (sw == dw && sh == dh && src_tex.pixelFormat == dst_tex.pixelFormat) {
                        id<MTLBlitCommandEncoder> blit = [cb blitCommandEncoder];
                        if (blit != nil) {
                            [blit copyFromTexture:src_tex
                                      sourceSlice:0
                                      sourceLevel:0
                                     sourceOrigin:MTLOriginMake(sx, sy, 0)
                                       sourceSize:MTLSizeMake(sw, sh, 1)
                                        toTexture:dst_tex
                                 destinationSlice:0
                                 destinationLevel:0
                                destinationOrigin:MTLOriginMake(dx, dy, 0)];
                            [blit endEncoding];
                        }
                    } else if ((dst_tex.usage & MTLTextureUsageRenderTarget) != 0u) {
                        const bool full_src = (sx == 0u && sy == 0u && sw == sw_full && sh == sh_full);
                        const bool partial_dst = (dx > 0u || dy > 0u || dw < dw_full || dh < dh_full);
                        MTLRenderPassDescriptor* rpd = [MTLRenderPassDescriptor renderPassDescriptor];
                        rpd.colorAttachments[0].texture     = dst_tex;
                        rpd.colorAttachments[0].loadAction  = partial_dst ? MTLLoadActionLoad : MTLLoadActionDontCare;
                        rpd.colorAttachments[0].storeAction = MTLStoreActionStore;
                        id<MTLRenderCommandEncoder> enc = [cb renderCommandEncoderWithDescriptor:rpd];
                        if (enc != nil) {
                            SamplerStateBlock sb{};
                            sb.address_u = 3; sb.address_v = 3;
                            sb.mag_filter = (filter >= 2u) ? 2u : 1u;
                            sb.min_filter = sb.mag_filter;
                            if (full_src) {
                                [enc setViewport:MTLViewport{
                                    static_cast<double>(dx), static_cast<double>(dy),
                                    static_cast<double>(dw), static_cast<double>(dh), 0.0, 1.0}];
                                PipelineCacheKey pkey{};
                                pkey.pass_id = MBAA_PASS_PRESENT_BLIT;
                                pkey.rt_fmt0 = static_cast<uint32_t>(dst_tex.pixelFormat);
                                if (id<MTLRenderPipelineState> pso = im->get_pipeline(pkey)) {
                                    [enc setRenderPipelineState:pso];
                                    [enc setFragmentTexture:src_tex atIndex:MBAA_TEX_STAGE0];
                                    [enc setFragmentSamplerState:im->get_sampler(sb) atIndex:0];
                                    [enc drawPrimitives:MTLPrimitiveTypeTriangleStrip vertexStart:0 vertexCount:4];
                                }
                            } else {
                                [enc setViewport:MTLViewport{
                                    0.0, 0.0, static_cast<double>(dw_full), static_cast<double>(dh_full), 0.0, 1.0}];
                                PipelineCacheKey pkey{};
                                pkey.pass_id = MBAA_PASS_FIXED_2D;
                                pkey.rt_fmt0 = static_cast<uint32_t>(dst_tex.pixelFormat);
                                if (id<MTLRenderPipelineState> pso = im->get_pipeline(pkey)) {
                                    const float u0 = static_cast<float>(sx) / static_cast<float>(sw_full);
                                    const float v0 = static_cast<float>(sy) / static_cast<float>(sh_full);
                                    const float u1 = static_cast<float>(sx + sw) / static_cast<float>(sw_full);
                                    const float v1 = static_cast<float>(sy + sh) / static_cast<float>(sh_full);
                                    const float x0 = static_cast<float>(dx) - 0.5f;
                                    const float y0 = static_cast<float>(dy) - 0.5f;
                                    const float x1 = static_cast<float>(dx + dw) - 0.5f;
                                    const float y1 = static_cast<float>(dy + dh) - 0.5f;
                                    MbaaMetalVertex qv[4]{};
                                    qv[0] = {{x0, y0, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {u0, v0}, {u0, v0}};
                                    qv[1] = {{x1, y0, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {u1, v0}, {u1, v0}};
                                    qv[2] = {{x0, y1, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {u0, v1}, {u0, v1}};
                                    qv[3] = {{x1, y1, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {u1, v1}, {u1, v1}};
                                    MbaaDrawUniforms du{};
                                    du.viewport_inv   = {2.0f / static_cast<float>(dw_full), 2.0f / static_cast<float>(dh_full), 0.0f, 0.0f};
                                    du.is_transformed = 1u;
                                    du.has_texture    = 1u;
                                    du.color_op0      = 2u; // SELECTARG1
                                    du.alpha_op0      = 2u;
                                    [enc setRenderPipelineState:pso];
                                    [enc setCullMode:MTLCullModeNone];
                                    [enc setVertexBytes:qv length:sizeof(qv) atIndex:MBAA_BUF_VERTICES];
                                    [enc setVertexBytes:&du length:sizeof(du) atIndex:MBAA_BUF_DRAW_UNIFORMS];
                                    [enc setFragmentBytes:&du length:sizeof(du) atIndex:MBAA_BUF_DRAW_UNIFORMS];
                                    [enc setFragmentTexture:src_tex atIndex:MBAA_TEX_STAGE0];
                                    [enc setFragmentSamplerState:im->get_sampler(sb) atIndex:0];
                                    [enc drawPrimitives:MTLPrimitiveTypeTriangleStrip vertexStart:0 vertexCount:4];
                                }
                            }
                            [enc endEncoding];
                        }
                    }
                }
                im->encoder_rt_dirty = true;
            }
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 24u);
}

void com_dev_color_fill(CpuContext& ctx, GuestMemory& mem) {
    // (this, pSurface, pRect, color) -> 16 bytes
    const uint32_t surf_va = ctx.arg32(mem, 1);
    const uint32_t color   = ctx.arg32(mem, 3);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        @autoreleasepool {
            id<MTLTexture> dst_tex = im->resolve_surface_texture(mem, surf_va);
            if (dst_tex != nil && (dst_tex.usage & MTLTextureUsageRenderTarget) != 0u) {
                im->end_active_encoder();
                if (id<MTLCommandBuffer> cb = im->ensure_cmd_buffer()) {
                    mbaa_float4 cf{};
                    argb_u32_to_float4(color, cf);
                    MTLRenderPassDescriptor* rpd = [MTLRenderPassDescriptor renderPassDescriptor];
                    rpd.colorAttachments[0].texture     = dst_tex;
                    rpd.colorAttachments[0].loadAction  = MTLLoadActionClear;
                    rpd.colorAttachments[0].storeAction = MTLStoreActionStore;
                    rpd.colorAttachments[0].clearColor  = MTLClearColorMake(cf.x, cf.y, cf.z, cf.w);
                    id<MTLRenderCommandEncoder> enc = [cb renderCommandEncoderWithDescriptor:rpd];
                    if (enc != nil) {
                        [enc endEncoding];
                    }
                }
                im->encoder_rt_dirty = true;
            }
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 16u);
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
        sr.guest_va = im->alloc_com_object(mem, im->vtbl_surface, sr.id, kKindSurface, true);
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
        }
        // DX9 spec: SetRenderTarget(0, ...) always resets the viewport to the full RT dimensions
        if (idx == 0u) {
            if (SurfaceRecord* sr = im->find_surface_by_va(mem, surf_va)) {
                im->vp_x = 0u; im->vp_y = 0u; im->vp_w = sr->width; im->vp_h = sr->height;
                if (im->active_encoder != nil) {
                    [im->active_encoder setViewport:MTLViewport{
                        0.0, 0.0, static_cast<double>(sr->width), static_cast<double>(sr->height), 0.0, 1.0}];
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
    const uint32_t flags   = ctx.arg32(mem, 3);
    const uint32_t color   = ctx.arg32(mem, 4);
    const uint32_t z_bits  = ctx.arg32(mem, 5);
    const uint32_t stencil = ctx.arg32(mem, 6);
    float z_val = 1.0f;
    std::memcpy(&z_val, &z_bits, sizeof(float));
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        ++im->clear_calls;
        im->end_active_encoder();
        im->encoder_rt_dirty = true;
        uint32_t clear_mrt = 1u;
        if (im->resolve_rt_texture(mem, 2u) != nil) clear_mrt = 3u;
        else if (im->resolve_rt_texture(mem, 1u) != nil) clear_mrt = 2u;
        im->ensure_render_encoder(
            mem, clear_mrt, (flags & 1u) != 0u, color, (flags & 6u) != 0u,
            static_cast<double>(std::clamp(z_val, 0.0f, 1.0f)), stencil);
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
        else if (state == 256u || state == 0u) im->mat_world = m;
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
            id<MTLTexture> rt0 = im->resolve_rt_texture(mem, 0u);
            const uint32_t rtw = rt0 ? static_cast<uint32_t>(rt0.width) : 4096u;
            const uint32_t rth = rt0 ? static_cast<uint32_t>(rt0.height) : 4096u;
            const uint32_t vx = std::min<uint32_t>(im->vp_x, rtw > 0u ? rtw - 1u : 0u);
            const uint32_t vy = std::min<uint32_t>(im->vp_y, rth > 0u ? rth - 1u : 0u);
            const uint32_t vw = std::max<uint32_t>(1u, std::min<uint32_t>(im->vp_w ? im->vp_w : rtw, rtw - vx));
            const uint32_t vh = std::max<uint32_t>(1u, std::min<uint32_t>(im->vp_h ? im->vp_h : rth, rth - vy));
            MTLViewport mvp{
                static_cast<double>(vx), static_cast<double>(vy),
                static_cast<double>(vw), static_cast<double>(vh), 0.0, 1.0
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
        if (st == kRsScissorTestEnable && im->active_encoder != nil) {
            if (id<MTLTexture> rt0 = im->resolve_rt_texture(mem, 0u)) {
                im->apply_encoder_scissor(im->active_encoder,
                                          static_cast<uint32_t>(rt0.width),
                                          static_cast<uint32_t>(rt0.height));
            }
        }
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
        const int32_t l = static_cast<int32_t>(mem.r32(rva + 0u));
        const int32_t t = static_cast<int32_t>(mem.r32(rva + 4u));
        const int32_t r = static_cast<int32_t>(mem.r32(rva + 8u));
        const int32_t b = static_cast<int32_t>(mem.r32(rva + 12u));
        if (r > l && b > t) {
            const uint32_t cl = static_cast<uint32_t>(std::max<int32_t>(l, 0));
            const uint32_t ct = static_cast<uint32_t>(std::max<int32_t>(t, 0));
            const uint32_t cw = static_cast<uint32_t>(std::max<int32_t>(1, r - static_cast<int32_t>(cl)));
            const uint32_t ch = static_cast<uint32_t>(std::max<int32_t>(1, b - static_cast<int32_t>(ct)));
            im->scissor_rect  = MTLScissorRect{cl, ct, cw, ch};
            im->scissor_valid = true;
            if (im->active_encoder != nil && im->render_states[kRsScissorTestEnable]) {
                if (id<MTLTexture> rt0 = im->resolve_rt_texture(mem, 0u)) {
                    im->apply_encoder_scissor(im->active_encoder,
                                              static_cast<uint32_t>(rt0.width),
                                              static_cast<uint32_t>(rt0.height));
                }
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
        if (vcount > 0u && mem.in_bounds(base_va, static_cast<size_t>(vcount) * im->current_vb_stride)) {
            im->execute_draw(mem, prim_type, prim_count, mem.cptr(base_va), vcount, im->current_vb_stride, nullptr, 0u);
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 16u);
}

void com_dev_draw_indexed_primitive(CpuContext& ctx, GuestMemory& mem) {
    // (this, PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, StartIndex, PrimitiveCount) -> 28 bytes
    const uint32_t prim_type  = ctx.arg32(mem, 1);
    const int32_t  base_vidx  = static_cast<int32_t>(ctx.arg32(mem, 2));
    const uint32_t min_vidx   = ctx.arg32(mem, 3);
    const uint32_t num_verts  = ctx.arg32(mem, 4);
    const uint32_t start_idx  = ctx.arg32(mem, 5);
    const uint32_t prim_count = ctx.arg32(mem, 6);
    if (auto* im = active_impl(); im && prim_count > 0u && im->current_vb_va != 0u && im->current_vb_stride > 0u) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        auto iit = im->buffers.find(im->current_ib_id);
        if (iit != im->buffers.end() && iit->second.data_va != 0u) {
            const BufferRecord& ib = iit->second;
            const uint32_t idx_fmt  = ib.format ? ib.format : 101u;
            const uint32_t idx_elem = (idx_fmt == 102u) ? 4u : 2u;
            const uint32_t idx_cnt  = vertex_count_for_prim(prim_type, prim_count);
            const uint64_t idx_off  = static_cast<uint64_t>(start_idx) * idx_elem;
            const uint64_t idx_need = static_cast<uint64_t>(idx_cnt) * idx_elem;
            if (idx_off + idx_need <= ib.size) {
                const uint32_t idx_va = ib.data_va + static_cast<uint32_t>(idx_off);
                const int64_t vbase_s = static_cast<int64_t>(im->current_vb_va) +
                                        static_cast<int64_t>(base_vidx) * static_cast<int64_t>(im->current_vb_stride);
                if (vbase_s > 0 && vbase_s < static_cast<int64_t>(GuestMemory::kArenaSize)) {
                    const uint32_t vbase_va = static_cast<uint32_t>(vbase_s);
                    uint32_t avail_verts = 65536u;
                    if (auto vit = im->buffers.find(im->current_vb_id); vit != im->buffers.end()) {
                        const BufferRecord& vb = vit->second;
                        if (vbase_va >= vb.data_va && vbase_va < vb.data_va + vb.size) {
                            avail_verts = (vb.data_va + vb.size - vbase_va) / im->current_vb_stride;
                        } else {
                            avail_verts = 0u;
                        }
                    }
                    const uint64_t need64 = static_cast<uint64_t>(min_vidx) + num_verts;
                    uint32_t total_verts = (need64 == 0u || need64 > avail_verts)
                        ? avail_verts
                        : static_cast<uint32_t>(need64);
                    if (total_verts > 0u &&
                        mem.in_bounds(vbase_va, static_cast<size_t>(total_verts) * im->current_vb_stride) &&
                        mem.in_bounds(idx_va, static_cast<size_t>(idx_need))) {
                        im->execute_draw(mem, prim_type, prim_count, mem.cptr(vbase_va),
                                         total_verts, im->current_vb_stride, mem.cptr(idx_va), idx_fmt);
                    }
                }
            }
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 28u);
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
        if (BufferRecord* br = im->find_buffer_by_va(mem, vb_va)) {
            im->current_vb_id     = br->id;
            im->current_vb_offset = std::min(off_b, br->size);
            im->current_vb_va     = br->data_va + im->current_vb_offset;
        } else {
            im->current_vb_id     = 0u;
            im->current_vb_offset = 0u;
            im->current_vb_va     = 0u;
        }
        im->current_vb_stride = stride;
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 20u);
}

void com_dev_set_indices(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t ib_va = ctx.arg32(mem, 1);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (BufferRecord* br = im->find_buffer_by_va(mem, ib_va)) {
            im->current_ib_id = br->id;
            im->current_ib_va = ib_va;
        } else {
            im->current_ib_id = 0u;
            im->current_ib_va = 0u;
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

void com_dev_get_indices(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pp_ib = ctx.arg32(mem, 1);
    if (auto* im = active_impl(); im && pp_ib && mem.in_bounds(pp_ib, 4u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        mem.w32(pp_ib, im->current_ib_va);
        if (im->current_ib_va != 0u && mem.in_bounds(im->current_ib_va + 8u, 4u)) {
            mem.w32(im->current_ib_va + 8u, mem.r32(im->current_ib_va + 8u) + 1u);
        }
    }
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 8u);
}

// ---------------------------------------------------------------------------
// IDirect3DVertexBuffer9 / IDirect3DIndexBuffer9 Methods
// ---------------------------------------------------------------------------
void com_buf_lock(CpuContext& ctx, GuestMemory& mem) {
    // (this, OffsetToLock, SizeToLock, ppbData, Flags) -> 20 bytes
    const uint32_t self_va = ctx.arg32(mem, 0);
    const uint32_t offset  = ctx.arg32(mem, 1);
    const uint32_t pp_data = ctx.arg32(mem, 3);
    if (auto* im = active_impl(); im && pp_data && mem.in_bounds(pp_data, 4u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (BufferRecord* br = im->find_buffer_by_va(mem, self_va)) {
            const uint32_t clamped_off = std::min(offset, br->size);
            mem.w32(pp_data, br->data_va + clamped_off);
            ctx.eax = kS_OK;
            ctx.ret_stdcall(mem, 20u);
            return;
        }
    }
    ctx.eax = kD3DERR_INVALIDCALL;
    ctx.ret_stdcall(mem, 20u);
}

void com_buf_unlock(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = kS_OK;
    ctx.ret_stdcall(mem, 4u);
}

void com_buf_get_desc(CpuContext& ctx, GuestMemory& mem) {
    // (this, pDesc) -> 8 bytes (D3DVERTEXBUFFER_DESC = 24B, D3DINDEXBUFFER_DESC = 20B)
    const uint32_t self_va = ctx.arg32(mem, 0);
    const uint32_t desc_va = ctx.arg32(mem, 1);
    if (auto* im = active_impl(); im && desc_va && mem.in_bounds(desc_va, 24u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (BufferRecord* br = im->find_buffer_by_va(mem, self_va)) {
            mem.w32(desc_va + 0u,  br->is_index ? br->format : kFmtUnknown);
            mem.w32(desc_va + 4u,  br->is_index ? 7u : 6u); // D3DRTYPE_INDEXBUFFER / D3DRTYPE_VERTEXBUFFER
            mem.w32(desc_va + 8u,  0u);
            mem.w32(desc_va + 12u, 1u); // D3DPOOL_MANAGED
            mem.w32(desc_va + 16u, br->size);
            if (!br->is_index) mem.w32(desc_va + 20u, br->fvf);
            ctx.eax = kS_OK;
            ctx.ret_stdcall(mem, 8u);
            return;
        }
    }
    ctx.eax = kD3DERR_INVALIDCALL;
    ctx.ret_stdcall(mem, 8u);
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
            // Keep sr.mtl_tex nil for child surfaces so TextureRecord is the sole ARC owner
            // (allows LRU eviction to immediately release MTLTexture GPU memory; resolve_surface_texture
            // reads live tr->mtl_tex via parent_tex_id).
            sr.mtl_tex       = nil;
            sr.guest_va      = im->alloc_com_object(mem, im->vtbl_surface, sr.id, kKindSurface, true);
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

bool lock_texture_record_rect(
    GuestMemory& mem,
    TextureRecord& tr,
    uint32_t rect_va,
    uint32_t flags,
    uint32_t locked_va)
{
    uint32_t rx = 0u, ry = 0u, rw = tr.width, rh = tr.height;
    parse_clamped_lock_rect(mem, rect_va, tr.width, tr.height, rx, ry, rw, rh);

    uint32_t pitch = 0u, bytes = 0u;
    compute_lock_pitch_bytes(tr.format, rw, rh, pitch, bytes);
    if (bytes == 0u) bytes = 16u;

    if (tr.staging_va != 0u) {
        mem.guest_free(tr.staging_va);
        tr.staging_va = 0u;
        tr.staging_bytes = 0u;
    }
    const uint32_t alloc_va = mem.guest_alloc(bytes, 16u);
    if (alloc_va == 0u || !mem.in_bounds(alloc_va, bytes)) {
        if (alloc_va != 0u) mem.guest_free(alloc_va);
        return false;
    }

    tr.staging_va    = alloc_va;
    tr.staging_pitch = pitch;
    tr.staging_bytes = bytes;
    tr.lock_x        = rx;
    tr.lock_y        = ry;
    tr.lock_w        = rw;
    tr.lock_h        = rh;
    tr.lock_readonly = (flags & kD3DLockReadOnly) != 0u;
    tr.locked        = true;

    const bool discard = (flags & kD3DLockDiscard) != 0u;
    if (tr.cpu_valid && !tr.cpu_backup.empty() && !discard && !is_dxt_format(tr.format)) {
        convert_mtl_rect_to_staging(tr.format, tr.width, rx, ry, rw, rh,
                                    tr.cpu_backup.data(), mem.ptr(alloc_va), pitch);
    } else {
        mem.zero_bytes(alloc_va, bytes);
    }

    mem.w32(locked_va + 0u, tr.staging_pitch);
    mem.w32(locked_va + 4u, tr.staging_va);
    return true;
}

void upload_staging_to_texture(D3D9MetalBridge::Impl& im, GuestMemory& mem, TextureRecord& tr) {
    const uint32_t sva    = tr.staging_va;
    const uint32_t sbytes = tr.staging_bytes;
    const uint32_t spitch = tr.staging_pitch;
    const bool readonly   = tr.lock_readonly;
    const uint32_t rx     = tr.lock_x;
    const uint32_t ry     = tr.lock_y;
    const uint32_t rw     = tr.lock_w ? tr.lock_w : tr.width;
    const uint32_t rh     = tr.lock_h ? tr.lock_h : tr.height;

    if (!readonly && sva != 0u && sbytes > 0u && mem.in_bounds(sva, sbytes)) {
        const bool was_valid = tr.cpu_valid;
        const MTLPixelFormat mfmt = d3d_fmt_to_mtl(tr.format);
        const uint32_t m_bpp = mtl_bytes_per_pixel(mfmt);

        write_staging_rect_to_cpu_backup(tr.format, tr.width, tr.height,
                                         rx, ry, rw, rh, mem.cptr(sva), spitch, tr.cpu_backup);
        tr.cpu_valid = true;
        tr.last_used_tick = ++im.lru_clock;

        if (tr.pool != kPoolSystemMem && !tr.is_render_target && !tr.is_depth_stencil) {
            if (tr.mtl_tex == nil) {
                tr.mtl_tex = im.make_mtl_texture(tr.width, tr.height, mfmt, false, false);
                if (tr.mtl_tex != nil) {
                    tr.evicted = false;
                    im.cached_texture_bytes += tr.gpu_bytes;
                    im.evict_lru_to_budget(D3D9MetalBridge::kTextureCacheLimitBytes);
                }
            }
            if (tr.mtl_tex != nil && tr.mtl_tex.storageMode == MTLStorageModeShared) {
                const bool upload_full = !was_valid || (rx == 0u && ry == 0u && rw == tr.width && rh == tr.height);
                @autoreleasepool {
                    if (upload_full) {
                        [tr.mtl_tex replaceRegion:MTLRegionMake2D(0, 0, tr.width, tr.height)
                                        mipmapLevel:0
                                          withBytes:tr.cpu_backup.data()
                                        bytesPerRow:tr.width * m_bpp];
                    } else {
                        const uint8_t* sub_ptr = tr.cpu_backup.data() +
                            (static_cast<size_t>(ry) * tr.width + rx) * m_bpp;
                        [tr.mtl_tex replaceRegion:MTLRegionMake2D(rx, ry, rw, rh)
                                        mipmapLevel:0
                                          withBytes:sub_ptr
                                        bytesPerRow:tr.width * m_bpp];
                    }
                }
                tr.evicted = false;
            }
        }
    }

    // Free per-lock guest staging buffer immediately on unlock to avoid permanent guest heap bloat
    if (tr.staging_va != 0u) {
        mem.guest_free(tr.staging_va);
        tr.staging_va    = 0u;
        tr.staging_bytes = 0u;
        tr.staging_pitch = 0u;
    }
    tr.lock_readonly = false;
}

void com_tex_lock_rect(CpuContext& ctx, GuestMemory& mem) {
    // (this, Level, pLockedRect, pRect, Flags) -> 20 bytes
    const uint32_t tex_va    = ctx.arg32(mem, 0);
    const uint32_t locked_va = ctx.arg32(mem, 2);
    const uint32_t rect_va   = ctx.arg32(mem, 3);
    const uint32_t flags     = ctx.arg32(mem, 4);
    if (auto* im = active_impl(); im && locked_va && mem.in_bounds(locked_va, 8u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (TextureRecord* tr = im->find_texture_by_va(mem, tex_va)) {
            ctx.eax = lock_texture_record_rect(mem, *tr, rect_va, flags, locked_va) ? kS_OK : kE_FAIL;
            ctx.ret_stdcall(mem, 20u);
            return;
        }
    }
    ctx.eax = kD3DERR_INVALIDCALL;
    ctx.ret_stdcall(mem, 20u);
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
    // (this, pLockedRect, pRect, Flags) -> 16 bytes
    const uint32_t surf_va   = ctx.arg32(mem, 0);
    const uint32_t locked_va = ctx.arg32(mem, 1);
    const uint32_t rect_va   = ctx.arg32(mem, 2);
    const uint32_t flags     = ctx.arg32(mem, 3);
    if (auto* im = active_impl(); im && locked_va && mem.in_bounds(locked_va, 8u)) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (SurfaceRecord* sr = im->find_surface_by_va(mem, surf_va)) {
            if (sr->parent_tex_id != 0u) {
                if (auto tit = im->textures.find(sr->parent_tex_id); tit != im->textures.end()) {
                    const bool ok = lock_texture_record_rect(mem, tit->second, rect_va, flags, locked_va);
                    sr->locked = ok;
                    ctx.eax = ok ? kS_OK : kE_FAIL;
                    ctx.ret_stdcall(mem, 16u);
                    return;
                }
            }
            uint32_t rx = 0u, ry = 0u, rw = sr->width, rh = sr->height;
            parse_clamped_lock_rect(mem, rect_va, sr->width, sr->height, rx, ry, rw, rh);
            uint32_t pitch = 0u, bytes = 0u;
            compute_lock_pitch_bytes(sr->format, rw, rh, pitch, bytes);
            if (bytes == 0u) bytes = 16u;

            if (sr->staging_va != 0u) {
                mem.guest_free(sr->staging_va);
                sr->staging_va = 0u;
                sr->staging_bytes = 0u;
            }
            const uint32_t alloc_va = mem.guest_alloc(bytes, 16u);
            if (alloc_va == 0u || !mem.in_bounds(alloc_va, bytes)) {
                if (alloc_va != 0u) mem.guest_free(alloc_va);
                ctx.eax = kE_FAIL;
                ctx.ret_stdcall(mem, 16u);
                return;
            }
            sr->staging_va    = alloc_va;
            sr->staging_pitch = pitch;
            sr->staging_bytes = bytes;
            sr->lock_x        = rx;
            sr->lock_y        = ry;
            sr->lock_w        = rw;
            sr->lock_h        = rh;
            sr->lock_readonly = (flags & kD3DLockReadOnly) != 0u;
            sr->locked        = true;
            const bool discard = (flags & kD3DLockDiscard) != 0u;
            if (sr->cpu_valid && !sr->cpu_backup.empty() && !discard && !is_dxt_format(sr->format)) {
                convert_mtl_rect_to_staging(sr->format, sr->width, rx, ry, rw, rh,
                                            sr->cpu_backup.data(), mem.ptr(alloc_va), pitch);
            } else {
                mem.zero_bytes(alloc_va, bytes);
            }
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
            } else {
                if (!sr->lock_readonly && sr->staging_va != 0u && sr->staging_bytes > 0u &&
                    mem.in_bounds(sr->staging_va, sr->staging_bytes)) {
                    const bool was_valid = sr->cpu_valid;
                    const uint32_t rx = sr->lock_x;
                    const uint32_t ry = sr->lock_y;
                    const uint32_t rw = sr->lock_w ? sr->lock_w : sr->width;
                    const uint32_t rh = sr->lock_h ? sr->lock_h : sr->height;
                    const MTLPixelFormat mfmt = d3d_fmt_to_mtl(sr->format);
                    const uint32_t m_bpp = mtl_bytes_per_pixel(mfmt);
                    write_staging_rect_to_cpu_backup(sr->format, sr->width, sr->height,
                                                     rx, ry, rw, rh, mem.cptr(sr->staging_va),
                                                     sr->staging_pitch, sr->cpu_backup);
                    sr->cpu_valid = true;
                    if (sr->mtl_tex != nil && sr->mtl_tex.storageMode == MTLStorageModeShared) {
                        const bool upload_full = !was_valid || (rx == 0u && ry == 0u && rw == sr->width && rh == sr->height);
                        @autoreleasepool {
                            if (upload_full) {
                                [sr->mtl_tex replaceRegion:MTLRegionMake2D(0, 0, sr->width, sr->height)
                                                mipmapLevel:0
                                                  withBytes:sr->cpu_backup.data()
                                                bytesPerRow:sr->width * m_bpp];
                            } else {
                                const uint8_t* sub_ptr = sr->cpu_backup.data() +
                                    (static_cast<size_t>(ry) * sr->width + rx) * m_bpp;
                                [sr->mtl_tex replaceRegion:MTLRegionMake2D(rx, ry, rw, rh)
                                                mipmapLevel:0
                                                  withBytes:sub_ptr
                                                bytesPerRow:sr->width * m_bpp];
                            }
                        }
                    }
                }
                if (sr->staging_va != 0u) {
                    mem.guest_free(sr->staging_va);
                    sr->staging_va    = 0u;
                    sr->staging_bytes = 0u;
                    sr->staging_pitch = 0u;
                }
                sr->lock_readonly = false;
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

void com_fx_set_float_array(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t fx_va   = ctx.arg32(mem, 0);
    const uint32_t hparam  = ctx.arg32(mem, 1);
    const uint32_t data_va = ctx.arg32(mem, 2);
    const uint32_t count   = ctx.arg32(mem, 3);
    if (auto* im = active_impl()) {
        std::lock_guard<std::recursive_mutex> lk(im->mtx);
        if (EffectRecord* fx = im->find_effect_by_va(mem, fx_va)) {
            const std::string pname = resolve_effect_param_name(*fx, mem, hparam);
            apply_effect_param_value(*im, *fx, mem, pname, data_va, count * 4u);
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
    dev_slots[26] = &com_dev_create_vertex_buffer;
    dev_slots[27] = &com_dev_create_index_buffer;
    dev_slots[28] = &com_dev_create_render_target;
    dev_slots[29] = &com_dev_create_depth_stencil_surface;
    dev_slots[30] = &com_stub_ret<20u, kS_OK>; // UpdateSurface
    dev_slots[31] = &com_stub_ret<12u, kS_OK>; // UpdateTexture
    dev_slots[32] = &com_stub_ret<12u, kS_OK>; // GetRenderTargetData
    dev_slots[33] = &com_stub_ret<12u, kS_OK>; // GetFrontBufferData
    dev_slots[34] = &com_dev_stretch_rect;
    dev_slots[35] = &com_dev_color_fill;
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
    dev_slots[82] = &com_dev_draw_indexed_primitive;
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
    dev_slots[104] = &com_dev_set_indices;
    dev_slots[105] = &com_dev_get_indices;
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
        &com_resource_get_device,          // 3 GetDevice
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
        &com_resource_get_device,          // 3 GetDevice
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
    fx_slots[32] = &com_fx_set_float_array;    // SetFloatArray (hParam, pData, Count)
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
    fx_slots[68] = &com_resource_get_device;   // GetDevice (8 bytes)
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
        &com_resource_get_device,          // 3 GetDevice
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

    // 7. IDirect3DVertexBuffer9 (14 slots)
    vtbl_vbuf = build_vtable(mem, {
        &com_unknown_query_interface,      // 0
        &com_unknown_addref,               // 1
        &com_unknown_release,              // 2
        &com_resource_get_device,          // 3 GetDevice
        &com_stub_ret<20u, kS_OK>,         // 4 SetPrivateData
        &com_stub_ret<16u, kE_FAIL>,       // 5 GetPrivateData
        &com_stub_ret<8u, kS_OK>,          // 6 FreePrivateData
        &com_stub_ret<8u, 0u>,             // 7 SetPriority
        &com_stub_ret<4u, 0u>,             // 8 GetPriority
        &com_stub_ret<4u, kS_OK>,          // 9 PreLoad
        &com_stub_ret<4u, 6u>,             // 10 GetType = D3DRTYPE_VERTEXBUFFER
        &com_buf_lock,                     // 11 Lock (+0x2c)
        &com_buf_unlock,                   // 12 Unlock (+0x30)
        &com_buf_get_desc,                 // 13 GetDesc (+0x34)
    });

    // 8. IDirect3DIndexBuffer9 (14 slots)
    vtbl_ibuf = build_vtable(mem, {
        &com_unknown_query_interface,      // 0
        &com_unknown_addref,               // 1
        &com_unknown_release,              // 2
        &com_resource_get_device,          // 3 GetDevice
        &com_stub_ret<20u, kS_OK>,         // 4 SetPrivateData
        &com_stub_ret<16u, kE_FAIL>,       // 5 GetPrivateData
        &com_stub_ret<8u, kS_OK>,          // 6 FreePrivateData
        &com_stub_ret<8u, 0u>,             // 7 SetPriority
        &com_stub_ret<4u, 0u>,             // 8 GetPriority
        &com_stub_ret<4u, kS_OK>,          // 9 PreLoad
        &com_stub_ret<4u, 7u>,             // 10 GetType = D3DRTYPE_INDEXBUFFER
        &com_buf_lock,                     // 11 Lock (+0x2c)
        &com_buf_unlock,                   // 12 Unlock (+0x30)
        &com_buf_get_desc,                 // 13 GetDesc (+0x34)
    });
}

// ---------------------------------------------------------------------------
// D3D9MetalBridge Public Methods
// ---------------------------------------------------------------------------
D3D9MetalBridge::D3D9MetalBridge() : impl_(std::make_unique<Impl>()) {}
D3D9MetalBridge::~D3D9MetalBridge() { shutdown(); }

void D3D9MetalBridge::set_active(D3D9MetalBridge* bridge) noexcept {
    global_bridge_slot().store(bridge, std::memory_order_release);
    global_impl_slot().store(bridge ? bridge->impl_.get() : nullptr, std::memory_order_release);
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
    hle_win32_log("D3D9MetalBridge::init %dx%d layer=%s lib=%s",
                  impl_->drawable_width, impl_->drawable_height,
                  impl_->metal_layer ? "ok" : "nil",
                  impl_->shader_lib ? "ok" : "MISSING");
    return true;
}

void D3D9MetalBridge::shutdown() {
    std::lock_guard<std::recursive_mutex> lk(impl_->mtx);
    @autoreleasepool {
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
        for (auto& rb : impl_->transient_rings) {
            rb = nil;
        }
        impl_->transient_ring_slot   = 0u;
        impl_->transient_ring_offset = 0u;
        impl_->active_encoder_mrt_count = 0u;
        impl_->scissor_valid         = false;
        impl_->cached_texture_bytes  = 0u;
        impl_->dummy_black_tex = nil;
        impl_->dummy_mrt_tex   = nil;
        impl_->depth_tex       = nil;
        impl_->shader_lib      = nil;
        impl_->cmd_queue       = nil;
        impl_->device          = nil;
        impl_->metal_layer     = nil;
    }
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
    impl_->current_vb_id       = 0u;
    impl_->current_vb_offset   = 0u;
    impl_->current_vb_va       = 0u;
    impl_->current_ib_id       = 0u;
    impl_->current_ib_va       = 0u;
    impl_->draw_calls          = 0u;
    impl_->clear_calls         = 0u;
    impl_->present_calls       = 0u;
    impl_->create_device_calls = 0u;
    impl_->create_tex_calls    = 0u;
    impl_->create_fx_calls     = 0u;
    impl_->create_vb_calls     = 0u;
    impl_->create_ib_calls     = 0u;
    impl_->pso_failures        = 0u;
    impl_->draw_dropped_no_enc = 0u;
    impl_->draw_dropped_no_pso = 0u;
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

std::string D3D9MetalBridge::debug_stats() const {
    std::lock_guard<std::recursive_mutex> lk(impl_->mtx);
    char buf[384] = {};
    std::snprintf(
        buf, sizeof(buf),
        "dev=%llu clr=%llu drw=%llu prs=%llu tex=%llu(%zu) fx=%llu vb=%llu ib=%llu\n"
        "psoFail=%llu dropEnc=%llu dropPso=%llu vram=%.1fMB lib=%s",
        static_cast<unsigned long long>(impl_->create_device_calls),
        static_cast<unsigned long long>(impl_->clear_calls),
        static_cast<unsigned long long>(impl_->draw_calls),
        static_cast<unsigned long long>(impl_->present_calls),
        static_cast<unsigned long long>(impl_->create_tex_calls),
        impl_->textures.size(),
        static_cast<unsigned long long>(impl_->create_fx_calls),
        static_cast<unsigned long long>(impl_->create_vb_calls),
        static_cast<unsigned long long>(impl_->create_ib_calls),
        static_cast<unsigned long long>(impl_->pso_failures),
        static_cast<unsigned long long>(impl_->draw_dropped_no_enc),
        static_cast<unsigned long long>(impl_->draw_dropped_no_pso),
        static_cast<double>(impl_->cached_texture_bytes) / (1024.0 * 1024.0),
        impl_->shader_lib ? "ok" : "MISSING");
    return std::string(buf);
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
                hle_win32_log("Direct3DCreate9 -> 0x%08x", impl_->d3d9_guest_va);
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

                // Unify all 32-bit color textures onto canonical BGRA8 (matching D3D9 A8R8G8B8 layout)
                rgba8_to_bgra8_inplace(rgba);

                TextureRecord rec{};
                rec.id             = ++impl_->next_handle_id;
                rec.width          = (req_w != 0u && req_w != 0xFFFFFFFFu) ? req_w : w;
                rec.height         = (req_h != 0u && req_h != 0xFFFFFFFFu) ? req_h : h;
                rec.levels         = 1u;
                rec.usage          = usage;
                rec.format         = kFmtA8R8G8B8;
                rec.pool           = kPoolManaged;
                rec.cpu_valid      = true;
                rec.last_used_tick = ++impl_->lru_clock;
                rec.mtl_tex        = impl_->make_mtl_texture(w, h, MTLPixelFormatBGRA8Unorm, false, false);
                if (rec.mtl_tex != nil) {
                    @autoreleasepool {
                        [rec.mtl_tex replaceRegion:MTLRegionMake2D(0, 0, w, h)
                                        mipmapLevel:0
                                          withBytes:rgba.data()
                                        bytesPerRow:w * 4u];
                    }
                }
                rec.width     = w;
                rec.height    = h;
                rec.gpu_bytes = rgba.size();
                rec.cpu_backup = std::move(rgba);
                impl_->cached_texture_bytes += rec.gpu_bytes;
                impl_->evict_lru_to_budget(kTextureCacheLimitBytes);

                rec.guest_va = impl_->alloc_com_object(mem, impl_->vtbl_texture, rec.id, kKindTexture, true);
                ++impl_->create_tex_calls;
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
                    @autoreleasepool {
                        [tr->mtl_tex replaceRegion:MTLRegionMake2D(0, 0, tr->width, tr->height)
                                        mipmapLevel:0
                                          withBytes:fill.data()
                                        bytesPerRow:tr->width * 4u];
                    }
                }
                tr->cpu_backup = std::move(fill);
                tr->cpu_valid  = true;
            }
            ctx.eax = kS_OK;
            ctx.ret_stdcall(mem, 12u);
            return true;
        }

        case d3d_iat::kD3DXLoadSurfaceFromSurface: {
            // (0:pDest, 1:pDestPal, 2:pDestRect, 3:pSrc, 4:pSrcPal, 5:pSrcRect, 6:Filter, 7:ColorKey) -> 32 bytes
            const uint32_t dst_va      = ctx.arg32(mem, 0);
            const uint32_t dst_rect_va = ctx.arg32(mem, 2);
            const uint32_t src_va      = ctx.arg32(mem, 3);
            const uint32_t src_pal_va  = ctx.arg32(mem, 4);
            const uint32_t src_rect_va = ctx.arg32(mem, 5);
            const uint32_t filter      = ctx.arg32(mem, 6);
            const uint32_t colorkey    = ctx.arg32(mem, 7);

            SurfaceRecord* dst = impl_->find_surface_by_va(mem, dst_va);
            SurfaceRecord* src = impl_->find_surface_by_va(mem, src_va);
            if (dst && src && dst->width > 0u && dst->height > 0u && src->width > 0u && src->height > 0u) {
                TextureRecord* dst_tr = nullptr;
                TextureRecord* src_tr = nullptr;
                if (dst->parent_tex_id != 0u) {
                    if (auto it = impl_->textures.find(dst->parent_tex_id); it != impl_->textures.end()) {
                        dst_tr = &it->second;
                    }
                }
                if (src->parent_tex_id != 0u) {
                    if (auto it = impl_->textures.find(src->parent_tex_id); it != impl_->textures.end()) {
                        src_tr = &it->second;
                    }
                }

                const uint32_t src_w = src->width;
                const uint32_t src_h = src->height;
                const uint32_t dst_w = dst->width;
                const uint32_t dst_h = dst->height;
                const uint32_t src_fmt = src_tr ? src_tr->format : src->format;
                const uint32_t dst_fmt = dst_tr ? dst_tr->format : dst->format;

                int32_t sl = 0, st = 0, sr_x = static_cast<int32_t>(src_w), sb = static_cast<int32_t>(src_h);
                if (src_rect_va != 0u && mem.in_bounds(src_rect_va, 16u)) {
                    sl   = static_cast<int32_t>(mem.r32(src_rect_va + 0u));
                    st   = static_cast<int32_t>(mem.r32(src_rect_va + 4u));
                    sr_x = static_cast<int32_t>(mem.r32(src_rect_va + 8u));
                    sb   = static_cast<int32_t>(mem.r32(src_rect_va + 12u));
                }
                int32_t dl = 0, dt = 0, dr = static_cast<int32_t>(dst_w), db = static_cast<int32_t>(dst_h);
                if (dst_rect_va != 0u && mem.in_bounds(dst_rect_va, 16u)) {
                    dl = static_cast<int32_t>(mem.r32(dst_rect_va + 0u));
                    dt = static_cast<int32_t>(mem.r32(dst_rect_va + 4u));
                    dr = static_cast<int32_t>(mem.r32(dst_rect_va + 8u));
                    db = static_cast<int32_t>(mem.r32(dst_rect_va + 12u));
                }

                const int32_t src_rw = sr_x - sl;
                const int32_t src_rh = sb - st;
                const int32_t dst_rw = dr - dl;
                const int32_t dst_rh = db - dt;

                if (src_rw > 0 && src_rh > 0 && dst_rw > 0 && dst_rh > 0) {
                    const bool src_is_rt = src_tr ? src_tr->is_render_target : ((src->usage & kUsageRenderTarget) != 0u);
                    const bool dst_is_rt = dst_tr ? dst_tr->is_render_target : ((dst->usage & kUsageRenderTarget) != 0u);
                    const std::vector<uint8_t>* src_cpu = nullptr;
                    if (!src_is_rt) {
                        if (src_tr && src->mip_level == 0u && src_tr->cpu_valid && !src_tr->cpu_backup.empty()) {
                            src_cpu = &src_tr->cpu_backup;
                        } else if (!src_tr && src->cpu_valid && !src->cpu_backup.empty()) {
                            src_cpu = &src->cpu_backup;
                        }
                    }

                    if (src_cpu != nullptr) {
                        // Path A: CPU-backed source -> full sub-rect / palette / colorkey / cross-format transfer
                        const MTLPixelFormat src_mfmt = d3d_fmt_to_mtl(src_fmt);
                        const MTLPixelFormat dst_mfmt = d3d_fmt_to_mtl(dst_fmt);
                        const uint32_t src_m_bpp = mtl_bytes_per_pixel(src_mfmt);
                        const uint32_t dst_m_bpp = mtl_bytes_per_pixel(dst_mfmt);

                        // Optional 256-entry PALETTEENTRY (peRed, peGreen, peBlue, peFlags) for P8/A8P8
                        std::array<uint8_t, 256 * 4> pal_bgra{};
                        bool has_palette = false;
                        if ((src_fmt == kFmtP8 || src_fmt == kFmtA8P8) &&
                            src_pal_va != 0u && mem.in_bounds(src_pal_va, 1024u)) {
                            const uint8_t* psrc = mem.cptr(src_pal_va);
                            bool any_alpha = false;
                            for (uint32_t i = 0; i < 256u; ++i) {
                                if (psrc[i * 4u + 3u] != 0u) { any_alpha = true; break; }
                            }
                            for (uint32_t i = 0; i < 256u; ++i) {
                                pal_bgra[i * 4u + 0u] = psrc[i * 4u + 2u]; // B
                                pal_bgra[i * 4u + 1u] = psrc[i * 4u + 1u]; // G
                                pal_bgra[i * 4u + 2u] = psrc[i * 4u + 0u]; // R
                                pal_bgra[i * 4u + 3u] = any_alpha ? psrc[i * 4u + 3u] : 255u;
                            }
                            has_palette = true;
                        }

                        std::vector<uint8_t>& dst_cpu = dst_tr ? dst_tr->cpu_backup : dst->cpu_backup;
                        bool& dst_cpu_valid = dst_tr ? dst_tr->cpu_valid : dst->cpu_valid;
                        const bool dst_was_valid = dst_cpu_valid;
                        const size_t dst_full_bytes = static_cast<size_t>(dst_w) * dst_h * dst_m_bpp;
                        if (dst_cpu.size() != dst_full_bytes) {
                            dst_cpu.assign(dst_full_bytes, 0u);
                        }

                        const uint8_t ck_r = static_cast<uint8_t>((colorkey >> 16) & 0xFFu);
                        const uint8_t ck_g = static_cast<uint8_t>((colorkey >> 8)  & 0xFFu);
                        const uint8_t ck_b = static_cast<uint8_t>(colorkey & 0xFFu);
                        const bool force_opaque_dst = (dst_fmt == kFmtX8R8G8B8 || dst_fmt == kFmtR8G8B8 ||
                                                       dst_fmt == kFmtR5G6B5   || dst_fmt == kFmtX1R5G5B5);

                        const int32_t clip_x0 = std::max<int32_t>(0, dl);
                        const int32_t clip_y0 = std::max<int32_t>(0, dt);
                        const int32_t clip_x1 = std::min<int32_t>(static_cast<int32_t>(dst_w), dr);
                        const int32_t clip_y1 = std::min<int32_t>(static_cast<int32_t>(dst_h), db);

                        if (clip_x1 > clip_x0 && clip_y1 > clip_y0 &&
                            src_cpu->size() >= static_cast<size_t>(src_w) * src_h * src_m_bpp) {
                            const bool fast_1to1_bgra = (src_rw == dst_rw && src_rh == dst_rh &&
                                                         src_m_bpp == 4u && dst_m_bpp == 4u &&
                                                         colorkey == 0u && !force_opaque_dst);
                            if (fast_1to1_bgra) {
                                for (int32_t dy = clip_y0; dy < clip_y1; ++dy) {
                                    const int32_t sy = st + (dy - dt);
                                    if (sy < 0 || sy >= static_cast<int32_t>(src_h)) continue;
                                    int32_t dx_start = clip_x0;
                                    int32_t sx_start = sl + (dx_start - dl);
                                    if (sx_start < 0) {
                                        dx_start -= sx_start;
                                        sx_start = 0;
                                    }
                                    int32_t copy_px = clip_x1 - dx_start;
                                    if (sx_start + copy_px > static_cast<int32_t>(src_w)) {
                                        copy_px = static_cast<int32_t>(src_w) - sx_start;
                                    }
                                    if (copy_px <= 0) continue;
                                    const uint8_t* sp = src_cpu->data() + (static_cast<size_t>(sy) * src_w + sx_start) * 4u;
                                    uint8_t* dp = dst_cpu.data() + (static_cast<size_t>(dy) * dst_w + dx_start) * 4u;
                                    std::memmove(dp, sp, static_cast<size_t>(copy_px) * 4u);
                                }
                            } else {
                                for (int32_t dy = clip_y0; dy < clip_y1; ++dy) {
                                    const int32_t sy = st + static_cast<int32_t>((static_cast<int64_t>(dy - dt) * src_rh) / dst_rh);
                                    if (sy < 0 || sy >= static_cast<int32_t>(src_h)) continue;
                                    for (int32_t dx = clip_x0; dx < clip_x1; ++dx) {
                                        const int32_t sx = sl + static_cast<int32_t>((static_cast<int64_t>(dx - dl) * src_rw) / dst_rw);
                                        if (sx < 0 || sx >= static_cast<int32_t>(src_w)) continue;

                                        uint8_t b = 0u, g = 0u, r = 0u, a = 255u;
                                        const uint8_t* sp = src_cpu->data() + (static_cast<size_t>(sy) * src_w + sx) * src_m_bpp;
                                        if (src_m_bpp == 4u) {
                                            b = sp[0]; g = sp[1]; r = sp[2]; a = sp[3];
                                        } else if (src_fmt == kFmtP8) {
                                            const uint8_t idx = sp[0];
                                            if (has_palette) {
                                                b = pal_bgra[idx * 4u + 0u];
                                                g = pal_bgra[idx * 4u + 1u];
                                                r = pal_bgra[idx * 4u + 2u];
                                                a = pal_bgra[idx * 4u + 3u];
                                            } else {
                                                b = g = r = idx; a = 255u;
                                            }
                                        } else if (src_fmt == kFmtA8P8) {
                                            const uint8_t idx = sp[0];
                                            const uint8_t alpha = sp[1];
                                            if (has_palette) {
                                                b = pal_bgra[idx * 4u + 0u];
                                                g = pal_bgra[idx * 4u + 1u];
                                                r = pal_bgra[idx * 4u + 2u];
                                            } else {
                                                b = g = r = idx;
                                            }
                                            a = alpha;
                                        } else if (src_fmt == kFmtA8) {
                                            b = g = r = 255u; a = sp[0];
                                        } else {
                                            b = g = r = sp[0]; a = 255u;
                                        }

                                        if (colorkey != 0u && r == ck_r && g == ck_g && b == ck_b) {
                                            b = g = r = a = 0u;
                                        } else if (force_opaque_dst) {
                                            a = 255u;
                                        }

                                        uint8_t* dp = dst_cpu.data() + (static_cast<size_t>(dy) * dst_w + dx) * dst_m_bpp;
                                        if (dst_m_bpp == 4u) {
                                            dp[0] = b; dp[1] = g; dp[2] = r; dp[3] = a;
                                        } else if (dst_fmt == kFmtA8) {
                                            dp[0] = a;
                                        } else if (dst_m_bpp == 2u) {
                                            dp[0] = r; dp[1] = a;
                                        } else {
                                            dp[0] = static_cast<uint8_t>((77u * r + 150u * g + 29u * b) >> 8);
                                        }
                                    }
                                }
                            }

                            dst_cpu_valid = true;
                            id<MTLTexture> dst_mtl = dst_tr ? dst_tr->mtl_tex : dst->mtl_tex;
                            if (dst_tr && dst_mtl == nil && dst_tr->pool != kPoolSystemMem &&
                                !dst_tr->is_render_target && !dst_tr->is_depth_stencil) {
                                dst_tr->mtl_tex = impl_->make_mtl_texture(dst_w, dst_h, dst_mfmt, false, false);
                                dst_mtl = dst_tr->mtl_tex;
                                if (dst_mtl != nil) {
                                    dst_tr->evicted = false;
                                    impl_->cached_texture_bytes += dst_tr->gpu_bytes;
                                    impl_->evict_lru_to_budget(kTextureCacheLimitBytes);
                                }
                            }
                            if (dst_tr) dst_tr->last_used_tick = ++impl_->lru_clock;

                            if (dst_mtl != nil) {
                                @autoreleasepool {
                                    if (dst_mtl.storageMode == MTLStorageModeShared) {
                                        const bool upload_full = !dst_was_valid ||
                                            (clip_x0 == 0 && clip_y0 == 0 &&
                                             clip_x1 == static_cast<int32_t>(dst_w) &&
                                             clip_y1 == static_cast<int32_t>(dst_h));
                                        if (upload_full) {
                                            [dst_mtl replaceRegion:MTLRegionMake2D(0, 0, dst_w, dst_h)
                                                       mipmapLevel:0
                                                         withBytes:dst_cpu.data()
                                                       bytesPerRow:dst_w * dst_m_bpp];
                                        } else {
                                            const uint8_t* sub_ptr = dst_cpu.data() +
                                                (static_cast<size_t>(clip_y0) * dst_w + clip_x0) * dst_m_bpp;
                                            [dst_mtl replaceRegion:MTLRegionMake2D(
                                                                       static_cast<NSUInteger>(clip_x0),
                                                                       static_cast<NSUInteger>(clip_y0),
                                                                       static_cast<NSUInteger>(clip_x1 - clip_x0),
                                                                       static_cast<NSUInteger>(clip_y1 - clip_y0))
                                                       mipmapLevel:0
                                                         withBytes:sub_ptr
                                                       bytesPerRow:dst_w * dst_m_bpp];
                                        }
                                    } else if (dst_is_rt) {
                                        // Private RenderTarget destination: upload via temporary shared staging texture
                                        const uint32_t uw = static_cast<uint32_t>(clip_x1 - clip_x0);
                                        const uint32_t uh = static_cast<uint32_t>(clip_y1 - clip_y0);
                                        id<MTLTexture> stage = impl_->make_mtl_texture(uw, uh, dst_mtl.pixelFormat, false, false);
                                        if (stage != nil) {
                                            const uint8_t* sub_ptr = dst_cpu.data() +
                                                (static_cast<size_t>(clip_y0) * dst_w + clip_x0) * dst_m_bpp;
                                            [stage replaceRegion:MTLRegionMake2D(0, 0, uw, uh)
                                                     mipmapLevel:0
                                                       withBytes:sub_ptr
                                                     bytesPerRow:dst_w * dst_m_bpp];
                                            impl_->end_active_encoder();
                                            if (id<MTLCommandBuffer> cb = impl_->ensure_cmd_buffer()) {
                                                id<MTLBlitCommandEncoder> blit = [cb blitCommandEncoder];
                                                if (blit != nil) {
                                                    [blit copyFromTexture:stage
                                                              sourceSlice:0
                                                              sourceLevel:0
                                                             sourceOrigin:MTLOriginMake(0, 0, 0)
                                                               sourceSize:MTLSizeMake(uw, uh, 1)
                                                                toTexture:dst_mtl
                                                         destinationSlice:0
                                                         destinationLevel:0
                                                        destinationOrigin:MTLOriginMake(
                                                            static_cast<NSUInteger>(clip_x0),
                                                            static_cast<NSUInteger>(clip_y0), 0)];
                                                    [blit endEncoding];
                                                }
                                            }
                                            impl_->encoder_rt_dirty = true;
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        // Path B: GPU-backed source (e.g. RenderTarget -> Managed texture or RenderTarget)
                        @autoreleasepool {
                            id<MTLTexture> src_mtl = impl_->resolve_surface_texture(mem, src_va);
                            id<MTLTexture> dst_mtl = impl_->resolve_surface_texture(mem, dst_va);
                            if (dst_tr && dst_mtl == nil && dst_tr->pool != kPoolSystemMem &&
                                !dst_tr->is_render_target && !dst_tr->is_depth_stencil) {
                                dst_tr->mtl_tex = impl_->make_mtl_texture(dst_w, dst_h, d3d_fmt_to_mtl(dst_fmt), false, false);
                                dst_mtl = dst_tr->mtl_tex;
                                if (dst_mtl != nil) {
                                    dst_tr->evicted = false;
                                    impl_->cached_texture_bytes += dst_tr->gpu_bytes;
                                    impl_->evict_lru_to_budget(kTextureCacheLimitBytes);
                                }
                            }
                            if (src_mtl != nil && dst_mtl != nil && src_mtl != dst_mtl) {
                                impl_->end_active_encoder();
                                const uint32_t sx0 = static_cast<uint32_t>(std::clamp<int32_t>(sl, 0, static_cast<int32_t>(src_w) - 1));
                                const uint32_t sy0 = static_cast<uint32_t>(std::clamp<int32_t>(st, 0, static_cast<int32_t>(src_h) - 1));
                                const uint32_t sw_c = static_cast<uint32_t>(std::clamp<int32_t>(sr_x - static_cast<int32_t>(sx0), 1, static_cast<int32_t>(src_w - sx0)));
                                const uint32_t sh_c = static_cast<uint32_t>(std::clamp<int32_t>(sb - static_cast<int32_t>(sy0), 1, static_cast<int32_t>(src_h - sy0)));
                                const uint32_t dx0 = static_cast<uint32_t>(std::clamp<int32_t>(dl, 0, static_cast<int32_t>(dst_w) - 1));
                                const uint32_t dy0 = static_cast<uint32_t>(std::clamp<int32_t>(dt, 0, static_cast<int32_t>(dst_h) - 1));
                                const uint32_t dw_c = static_cast<uint32_t>(std::clamp<int32_t>(dr - static_cast<int32_t>(dx0), 1, static_cast<int32_t>(dst_w - dx0)));
                                const uint32_t dh_c = static_cast<uint32_t>(std::clamp<int32_t>(db - static_cast<int32_t>(dy0), 1, static_cast<int32_t>(dst_h - dy0)));

                                if (id<MTLCommandBuffer> cb = impl_->ensure_cmd_buffer()) {
                                    if (src_mtl.pixelFormat == dst_mtl.pixelFormat &&
                                        ((sw_c == dw_c && sh_c == dh_c) || (dst_mtl.usage & MTLTextureUsageRenderTarget) == 0u)) {
                                        const uint32_t cw = std::min(sw_c, dw_c);
                                        const uint32_t ch = std::min(sh_c, dh_c);
                                        id<MTLBlitCommandEncoder> blit = [cb blitCommandEncoder];
                                        if (blit != nil) {
                                            [blit copyFromTexture:src_mtl
                                                      sourceSlice:0
                                                      sourceLevel:0
                                                     sourceOrigin:MTLOriginMake(sx0, sy0, 0)
                                                       sourceSize:MTLSizeMake(cw, ch, 1)
                                                        toTexture:dst_mtl
                                                 destinationSlice:0
                                                 destinationLevel:0
                                                destinationOrigin:MTLOriginMake(dx0, dy0, 0)];
                                            [blit endEncoding];
                                        }
                                    } else if ((dst_mtl.usage & MTLTextureUsageRenderTarget) != 0u) {
                                        MTLRenderPassDescriptor* rpd = [MTLRenderPassDescriptor renderPassDescriptor];
                                        rpd.colorAttachments[0].texture     = dst_mtl;
                                        rpd.colorAttachments[0].loadAction  = MTLLoadActionLoad;
                                        rpd.colorAttachments[0].storeAction = MTLStoreActionStore;
                                        id<MTLRenderCommandEncoder> enc = [cb renderCommandEncoderWithDescriptor:rpd];
                                        if (enc != nil) {
                                            [enc setViewport:MTLViewport{0.0, 0.0, static_cast<double>(dst_w), static_cast<double>(dst_h), 0.0, 1.0}];
                                            PipelineCacheKey pkey{};
                                            pkey.pass_id = MBAA_PASS_FIXED_2D;
                                            pkey.rt_fmt0 = static_cast<uint32_t>(dst_mtl.pixelFormat);
                                            if (id<MTLRenderPipelineState> pso = impl_->get_pipeline(pkey)) {
                                                const float u0 = static_cast<float>(sx0) / static_cast<float>(src_w);
                                                const float v0 = static_cast<float>(sy0) / static_cast<float>(src_h);
                                                const float u1 = static_cast<float>(sx0 + sw_c) / static_cast<float>(src_w);
                                                const float v1 = static_cast<float>(sy0 + sh_c) / static_cast<float>(src_h);
                                                const float x0 = static_cast<float>(dx0) - 0.5f;
                                                const float y0 = static_cast<float>(dy0) - 0.5f;
                                                const float x1 = static_cast<float>(dx0 + dw_c) - 0.5f;
                                                const float y1 = static_cast<float>(dy0 + dh_c) - 0.5f;
                                                MbaaMetalVertex qv[4]{};
                                                qv[0] = {{x0, y0, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {u0, v0}, {u0, v0}};
                                                qv[1] = {{x1, y0, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {u1, v0}, {u1, v0}};
                                                qv[2] = {{x0, y1, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {u0, v1}, {u0, v1}};
                                                qv[3] = {{x1, y1, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {u1, v1}, {u1, v1}};
                                                MbaaDrawUniforms du{};
                                                du.viewport_inv   = {2.0f / static_cast<float>(dst_w), 2.0f / static_cast<float>(dst_h), 0.0f, 0.0f};
                                                du.is_transformed = 1u;
                                                du.has_texture    = 1u;
                                                du.color_op0      = 2u;
                                                du.alpha_op0      = 2u;
                                                SamplerStateBlock sb{};
                                                sb.address_u = 3; sb.address_v = 3;
                                                sb.mag_filter = (filter >= 2u) ? 2u : 1u;
                                                sb.min_filter = sb.mag_filter;
                                                [enc setRenderPipelineState:pso];
                                                [enc setCullMode:MTLCullModeNone];
                                                [enc setVertexBytes:qv length:sizeof(qv) atIndex:MBAA_BUF_VERTICES];
                                                [enc setVertexBytes:&du length:sizeof(du) atIndex:MBAA_BUF_DRAW_UNIFORMS];
                                                [enc setFragmentBytes:&du length:sizeof(du) atIndex:MBAA_BUF_DRAW_UNIFORMS];
                                                [enc setFragmentTexture:src_mtl atIndex:MBAA_TEX_STAGE0];
                                                [enc setFragmentSamplerState:impl_->get_sampler(sb) atIndex:0];
                                                [enc drawPrimitives:MTLPrimitiveTypeTriangleStrip vertexStart:0 vertexCount:4];
                                            }
                                            [enc endEncoding];
                                        }
                                    }
                                    impl_->encoder_rt_dirty = true;
                                }
                                if (dst_tr) {
                                    dst_tr->cpu_valid = false;
                                    dst_tr->last_used_tick = ++impl_->lru_clock;
                                } else {
                                    dst->cpu_valid = false;
                                }
                            }
                        }
                    }
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
                fx.guest_va = impl_->alloc_com_object(mem, impl_->vtbl_effect, fx.id, kKindEffect, true);
                ++impl_->create_fx_calls;
                if (impl_->create_fx_calls <= 3u) {
                    hle_win32_log("D3DXCreateEffect #%llu -> techs=%zu params=%zu",
                                  static_cast<unsigned long long>(impl_->create_fx_calls),
                                  fx.techniques.size(), fx.parameters.size());
                }
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
                fr.guest_va = impl_->alloc_com_object(mem, impl_->vtbl_font, fr.id, kKindFont, true);
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
