#pragma once

/**
 * @file d3d9_shim.h
 * @brief Direct3D 9 / D3DX9_36 -> Apple Metal graphics shim and software DXT1-5 decoder
 *        for mbaacc-recomp-ios (iPhone SE 2020: A13 Bionic, 3 GB RAM, 1334x750 60 Hz).
 *
 * Shared contract across shader-gfx, runtime-hle, and ios-shell:
 *   - Namespace: mbaa_recomp
 *   - Handles all 23 D3D9/D3DX9 IAT imports from MBAA.exe (0x0051B398..0x0051B3F4):
 *       d3d9.dll!Direct3DCreate9 (0x0051B398)
 *       d3dx9_36.dll!D3DXMatrixRotationX (0x0051B3A0)
 *       d3dx9_36.dll!D3DXMatrixScaling (0x0051B3A4)
 *       d3dx9_36.dll!D3DXMatrixRotationY (0x0051B3A8)
 *       d3dx9_36.dll!D3DXMatrixMultiply (0x0051B3AC)
 *       d3dx9_36.dll!D3DXMatrixTranslation (0x0051B3B0)
 *       d3dx9_36.dll!D3DXSaveSurfaceToFileA (0x0051B3B4)
 *       d3dx9_36.dll!D3DXVec3Transform (0x0051B3B8)
 *       d3dx9_36.dll!D3DXVec3TransformCoord (0x0051B3BC)
 *       d3dx9_36.dll!D3DXVec3TransformCoordArray (0x0051B3C0)
 *       d3dx9_36.dll!D3DXMatrixLookAtLH (0x0051B3C4)
 *       d3dx9_36.dll!D3DXMatrixPerspectiveFovLH (0x0051B3C8)
 *       d3dx9_36.dll!D3DXVec3Normalize (0x0051B3CC)
 *       d3dx9_36.dll!D3DXLoadSurfaceFromSurface (0x0051B3D0)
 *       d3dx9_36.dll!D3DXCreateFontA (0x0051B3D4)
 *       d3dx9_36.dll!D3DXFillTexture (0x0051B3D8)
 *       d3dx9_36.dll!D3DXMatrixRotationYawPitchRoll (0x0051B3DC)
 *       d3dx9_36.dll!D3DXCreateEffect (0x0051B3E0)
 *       d3dx9_36.dll!D3DXCreateTextureFromFileInMemoryEx (0x0051B3E4)
 *       d3dx9_36.dll!D3DXGetImageInfoFromFileInMemory (0x0051B3E8)
 *       d3dx9_36.dll!D3DXVec3TransformArray (0x0051B3EC)
 *       d3dx9_36.dll!D3DXMatrixRotationZ (0x0051B3F0)
 *       d3dx9_36.dll!D3DXCreateTexture (0x0051B3F4)
 *   - Allocates synthetic 32-bit COM vtable stubs inside GuestMemory for:
 *       IDirect3D9, IDirect3DDevice9, IDirect3DTexture9,
 *       IDirect3DSurface9, ID3DXEffect, ID3DXFont.
 */

#include "mbaa_recomp/cpu_context.h"
#include "mbaa_recomp/guest_memory.h"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace mbaa_recomp {

// ---------------------------------------------------------------------------
// Canonical MBAA.exe D3D9 / D3DX9 IAT Virtual Addresses [Verified from PE IAT]
// ---------------------------------------------------------------------------
namespace d3d_iat {
inline constexpr uint32_t kDirect3DCreate9                      = 0x0051B398u;
inline constexpr uint32_t kD3DXMatrixRotationX                  = 0x0051B3A0u;
inline constexpr uint32_t kD3DXMatrixScaling                    = 0x0051B3A4u;
inline constexpr uint32_t kD3DXMatrixRotationY                  = 0x0051B3A8u;
inline constexpr uint32_t kD3DXMatrixMultiply                   = 0x0051B3ACu;
inline constexpr uint32_t kD3DXMatrixTranslation                = 0x0051B3B0u;
inline constexpr uint32_t kD3DXSaveSurfaceToFileA               = 0x0051B3B4u;
inline constexpr uint32_t kD3DXVec3Transform                    = 0x0051B3B8u;
inline constexpr uint32_t kD3DXVec3TransformCoord               = 0x0051B3BCu;
inline constexpr uint32_t kD3DXVec3TransformCoordArray          = 0x0051B3C0u;
inline constexpr uint32_t kD3DXMatrixLookAtLH                   = 0x0051B3C4u;
inline constexpr uint32_t kD3DXMatrixPerspectiveFovLH           = 0x0051B3C8u;
inline constexpr uint32_t kD3DXVec3Normalize                    = 0x0051B3CCu;
inline constexpr uint32_t kD3DXLoadSurfaceFromSurface           = 0x0051B3D0u;
inline constexpr uint32_t kD3DXCreateFontA                      = 0x0051B3D4u;
inline constexpr uint32_t kD3DXFillTexture                      = 0x0051B3D8u;
inline constexpr uint32_t kD3DXMatrixRotationYawPitchRoll       = 0x0051B3DCu;
inline constexpr uint32_t kD3DXCreateEffect                     = 0x0051B3E0u;
inline constexpr uint32_t kD3DXCreateTextureFromFileInMemoryEx = 0x0051B3E4u;
inline constexpr uint32_t kD3DXGetImageInfoFromFileInMemory     = 0x0051B3E8u;
inline constexpr uint32_t kD3DXVec3TransformArray               = 0x0051B3ECu;
inline constexpr uint32_t kD3DXMatrixRotationZ                  = 0x0051B3F0u;
inline constexpr uint32_t kD3DXCreateTexture                    = 0x0051B3F4u;
} // namespace d3d_iat

// ---------------------------------------------------------------------------
// Software DXT1 / DXT2 / DXT3 / DXT4 / DXT5 & DDS -> RGBA8 Decoder (bcdec_dxt.cpp)
// ---------------------------------------------------------------------------
enum class DxtFormat : uint32_t {
    Unknown = 0,
    DXT1    = 1, // BC1 (opaque or 1-bit punch-through alpha)
    DXT2    = 2, // BC2 premultiplied alpha -> un-premultiplied to straight RGBA8
    DXT3    = 3, // BC2 explicit 4-bit straight alpha
    DXT4    = 4, // BC3 premultiplied alpha -> un-premultiplied to straight RGBA8
    DXT5    = 5, // BC3 interpolated 8-bit straight alpha
};

struct DdsProbeInfo {
    uint32_t  width          = 0;
    uint32_t  height         = 0;
    uint32_t  mip_count      = 1;
    uint32_t  d3d_format     = 0; // D3DFORMAT numeric code
    DxtFormat dxt_format     = DxtFormat::Unknown;
    bool      is_compressed  = false;
    bool      has_alpha      = false;
    bool      premultiplied  = false;
    uint32_t  bits_per_pixel = 0;
    size_t    pixel_offset   = 0; // Byte offset of mip 0 pixel data
};

/// Decodes a single 4x4 DXT1 block (8 bytes) into 16 RGBA8 pixels (dst_pitch in bytes).
void bcdec_dxt1_block(const uint8_t* src_block, uint8_t* dst_rgba, int dst_pitch) noexcept;

/// Decodes a single 4x4 DXT2 or DXT3 block (16 bytes) into 16 straight RGBA8 pixels.
/// When `unpremultiply` is true (DXT2), divides RGB by alpha to restore straight RGBA8.
void bcdec_dxt23_block(const uint8_t* src_block, uint8_t* dst_rgba, int dst_pitch, bool unpremultiply) noexcept;

/// Decodes a single 4x4 DXT4 or DXT5 block (16 bytes) into 16 straight RGBA8 pixels.
/// When `unpremultiply` is true (DXT4), divides RGB by alpha to restore straight RGBA8.
void bcdec_dxt45_block(const uint8_t* src_block, uint8_t* dst_rgba, int dst_pitch, bool unpremultiply) noexcept;

/// Decodes an entire DXT1..DXT5 image mip level to tightly-packed RGBA8 (width * height * 4 bytes).
bool decode_dxt_image(
    DxtFormat format,
    uint32_t width,
    uint32_t height,
    const uint8_t* src,
    size_t src_bytes,
    std::vector<uint8_t>& out_rgba);

/// Parses a DDS header without copying or decoding pixels.
bool dds_probe_info(const uint8_t* dds_data, size_t dds_bytes, DdsProbeInfo& out_info) noexcept;

/// Decodes a DDS file in memory (DXT1..DXT5 or uncompressed A8R8G8B8/X8R8G8B8/R5G6B5/A1R5G5B5/A4R4G4B4/L8)
/// into straight RGBA8 pixels (`out_rgba`).
bool decode_dds_to_rgba8(
    const uint8_t* dds_data,
    size_t dds_bytes,
    uint32_t& out_width,
    uint32_t& out_height,
    std::vector<uint8_t>& out_rgba,
    DdsProbeInfo* out_info = nullptr);

// ---------------------------------------------------------------------------
// Direct3D 9 -> Apple Metal Bridge
// ---------------------------------------------------------------------------
class D3D9MetalBridge {
public:
    /// Texture cache budget sized for iPhone SE 2020 (A13 Bionic, 3 GB RAM): 192 MiB.
    static constexpr size_t kTextureCacheLimitBytes = 192u * 1024u * 1024u;
    /// Canonical game logical canvas (4:3) centered inside 1334x750 SE 2020 display as 1000x750.
    static constexpr uint32_t kGameLogicalWidth  = 640u;
    static constexpr uint32_t kGameLogicalHeight = 480u;

    D3D9MetalBridge();
    ~D3D9MetalBridge();

    D3D9MetalBridge(const D3D9MetalBridge&) = delete;
    D3D9MetalBridge& operator=(const D3D9MetalBridge&) = delete;

    /// Binds an opaque `CAMetalLayer*` (`void*`) and drawable pixel dimensions (e.g. 1334x750).
    /// Also sets this instance as the active global bridge if none is active yet.
    bool init(void* cametal_layer, int width, int height);
    void shutdown();

    /// Updates drawable size and recomputes the centered 4:3 (1000x750 inside 1334x750) Metal viewport.
    void resize(int width, int height);

    /// Begins a frame on the Metal command queue / drawable backbuffer.
    void begin_frame();

    /// Submits any pending work, copies backbuffer into centered 4:3 drawable viewport, and presents.
    void end_frame_and_present();

    /// Evicts oldest LRU Metal textures down to minimal live footprint on iOS memory warnings.
    void evict_on_memory_warning();

    /// Dispatches any `d3d9.dll` / `d3dx9_36.dll` IAT call from lifted x86 code.
    /// Returns true if `iat_va` (or `api_name`) was recognized and handled.
    bool handle_d3d_iat(uint32_t iat_va, const char* api_name, CpuContext& ctx, GuestMemory& mem);

    /// Returns true if `iat_va` belongs to MBAA.exe's d3d9.dll or d3dx9_36.dll IAT range.
    [[nodiscard]] static bool is_d3d_iat(uint32_t iat_va) noexcept {
        return iat_va == d3d_iat::kDirect3DCreate9 ||
               (iat_va >= d3d_iat::kD3DXMatrixRotationX && iat_va <= d3d_iat::kD3DXCreateTexture);
    }

    /// Global active bridge registration (used by hle_iat_call -> handle_d3d_iat).
    static void set_active(D3D9MetalBridge* bridge) noexcept;
    [[nodiscard]] static D3D9MetalBridge* active() noexcept;

    [[nodiscard]] bool is_initialized() const noexcept;
    [[nodiscard]] size_t texture_cache_bytes() const noexcept;
    [[nodiscard]] size_t texture_cache_count() const noexcept;
    [[nodiscard]] uint64_t draw_call_count() const noexcept;
    [[nodiscard]] std::string debug_stats() const;

#ifdef __APPLE__
    struct Impl;
#else
    struct Impl {};
#endif

private:
    std::unique_ptr<Impl> impl_;
};

#ifndef __APPLE__
// Non-Apple host stub definitions so portable CMake C++20 targets link cleanly without Metal.
inline D3D9MetalBridge*& _d3d9_active_bridge_slot() noexcept {
    static D3D9MetalBridge* s_active = nullptr;
    return s_active;
}
inline D3D9MetalBridge::D3D9MetalBridge() : impl_(std::make_unique<Impl>()) {}
inline D3D9MetalBridge::~D3D9MetalBridge() = default;
inline bool D3D9MetalBridge::init(void*, int, int) {
    set_active(this);
    return true;
}
inline void D3D9MetalBridge::shutdown() {
    if (active() == this) set_active(nullptr);
}
inline void D3D9MetalBridge::resize(int, int) {}
inline void D3D9MetalBridge::begin_frame() {}
inline void D3D9MetalBridge::end_frame_and_present() {}
inline void D3D9MetalBridge::evict_on_memory_warning() {}
inline bool D3D9MetalBridge::handle_d3d_iat(uint32_t, const char*, CpuContext&, GuestMemory&) { return false; }
inline void D3D9MetalBridge::set_active(D3D9MetalBridge* bridge) noexcept { _d3d9_active_bridge_slot() = bridge; }
inline D3D9MetalBridge* D3D9MetalBridge::active() noexcept { return _d3d9_active_bridge_slot(); }
inline bool D3D9MetalBridge::is_initialized() const noexcept { return false; }
inline size_t D3D9MetalBridge::texture_cache_bytes() const noexcept { return 0; }
inline size_t D3D9MetalBridge::texture_cache_count() const noexcept { return 0; }
inline uint64_t D3D9MetalBridge::draw_call_count() const noexcept { return 0; }
inline std::string D3D9MetalBridge::debug_stats() const { return "non-apple"; }
#endif // !__APPLE__

} // namespace mbaa_recomp
