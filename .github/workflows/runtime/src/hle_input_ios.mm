#include "mbaa_recomp/hle_input.h"
#include "mbaa_recomp/dispatch.h"

#if defined(__APPLE__)
#import <Foundation/Foundation.h>
#import <GameController/GameController.h>
#endif

#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <mutex>

namespace mbaa_recomp {

namespace {

// DirectInput8 constants & error codes
constexpr uint32_t kDI_OK                 = 0x00000000u;
constexpr uint32_t kDIERR_INVALIDPARAM    = 0x80070057u;
constexpr uint32_t kDIERR_NOTINITIALIZED  = 0x80070015u;
constexpr uint32_t kDI8DEVCLASS_GAMECTRL  = 4u;
constexpr uint32_t kDI8DEVTYPE_GAMEPAD    = 0x00010215u;
constexpr uint32_t kDIDFT_AXIS            = 0x00000003u;
constexpr uint32_t kDIDFT_BUTTON          = 0x0000000Cu;
constexpr uint32_t kDIDFT_POV             = 0x00000010u;

// DirectInput keyboard scancodes (DIK_*) matching MBAA.exe P1 table at 0x0054d2c0:
//   Up=W(0x11), Down=S(0x1F), Left=A(0x1E), Right=D(0x20),
//   A=C(0x2E), B=V(0x2F), C=B(0x30), D=F(0x21), E=E(0x12), Start=Q(0x10)
constexpr uint8_t kDIK_Q      = 0x10u;
constexpr uint8_t kDIK_W      = 0x11u;
constexpr uint8_t kDIK_E      = 0x12u;
constexpr uint8_t kDIK_A      = 0x1Eu;
constexpr uint8_t kDIK_S      = 0x1Fu;
constexpr uint8_t kDIK_D      = 0x20u;
constexpr uint8_t kDIK_F      = 0x21u;
constexpr uint8_t kDIK_C      = 0x2Eu;
constexpr uint8_t kDIK_V      = 0x2Fu;
constexpr uint8_t kDIK_B      = 0x30u;

// GUID_SysKeyboard {6F1D2B61-D5A0-11CF-BFC7-444553540000}
constexpr uint8_t kGuidSysKeyboard[16] = {
    0x61, 0x2B, 0x1D, 0x6F, 0xA0, 0xD5, 0xCF, 0x11,
    0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00
};
// GUID_SysMouse {6F1D2B60-D5A0-11CF-BFC7-444553540000}
constexpr uint8_t kGuidSysMouse[16] = {
    0x60, 0x2B, 0x1D, 0x6F, 0xA0, 0xD5, 0xCF, 0x11,
    0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00
};

enum class DiDeviceKind : uint32_t {
    Keyboard = 0,
    Mouse    = 1,
    Gamepad  = 2,
};

struct CombinedPadSnapshot {
    uint32_t buttons = 0; // TouchButton bitmask
    float    axis_x  = 0.0f;
    float    axis_y  = 0.0f;
    bool     connected = false;
};

struct InputState {
    std::mutex touch_mutex;
    TouchInputState touch{};
    std::array<CombinedPadSnapshot, 2> pads{};
    std::atomic<bool> has_gc{false};
    std::atomic<bool> initialized{false};

    // Guest COM vtables and objects
    uint32_t di8_vtable     = 0;
    uint32_t dev_vtable     = 0;
    uint32_t di8_obj_va     = 0;
    uint32_t kbd_obj_va     = 0;
    uint32_t mouse_obj_va   = 0;
    uint32_t pad_obj_va[2]  = {0, 0};

#if defined(__APPLE__)
    id connect_observer    = nil;
    id disconnect_observer = nil;
#endif
};

InputState g_input;

uint32_t expand_macros(uint32_t raw_buttons) noexcept {
    uint32_t b = raw_buttons;
    if (b & kTouchDash) {
        b |= (kTouchA | kTouchB);
    }
    if (b & kTouchHeat) {
        b |= (kTouchA | kTouchB | kTouchC);
    }
    return b;
}

uint32_t pov_from_dpad(uint32_t b) noexcept {
    const bool up    = (b & kTouchUp) != 0;
    const bool down  = (b & kTouchDown) != 0;
    const bool left  = (b & kTouchLeft) != 0;
    const bool right = (b & kTouchRight) != 0;

    if (up && !down) {
        if (right && !left) return 4500u;
        if (left && !right) return 31500u;
        return 0u;
    }
    if (down && !up) {
        if (right && !left) return 13500u;
        if (left && !right) return 22500u;
        return 18000u;
    }
    if (right && !left) return 9000u;
    if (left && !right) return 27000u;
    return 0xFFFFFFFFu; // Centered
}

#if defined(__APPLE__)
void poll_gc_controller(GCController* ctrl, CombinedPadSnapshot& out) {
    out = CombinedPadSnapshot{};
    if (!ctrl) return;
    out.connected = true;

    if (ctrl.extendedGamepad != nil) {
        GCExtendedGamepad* gp = ctrl.extendedGamepad;
        const float lx = gp.leftThumbstick.xAxis.value;
        const float ly = gp.leftThumbstick.yAxis.value; // Apple: +Y is UP

        out.axis_x = lx;
        out.axis_y = -ly; // DirectInput: -Y is UP

        if (gp.dpad.up.isPressed || ly > 0.35f)    out.buttons |= kTouchUp;
        if (gp.dpad.down.isPressed || ly < -0.35f) out.buttons |= kTouchDown;
        if (gp.dpad.left.isPressed || lx < -0.35f) out.buttons |= kTouchLeft;
        if (gp.dpad.right.isPressed || lx > 0.35f) out.buttons |= kTouchRight;

        // Authentic Melty Blood PS2 controller mapping + MBAACC E (R1):
        //   Square (X)   = A (Punch / Light)
        //   Cross (A)    = B (Low Kick / Medium)
        //   Circle (B)   = C (High Kick / Heavy)
        //   Triangle (Y) = D (Magic / Shield)
        //   L1           = A + D (Throw / Evade)
        //   L2           = A + B + C (Heat)
        //   R1           = E (Quick Action)
        //   R2           = A + B (Dash)
        //   Start (Menu) = Start / Pause game
        //   Select       = FN1
        //   R3           = FN2
        if (gp.buttonX.isPressed) out.buttons |= kTouchA;
        if (gp.buttonA.isPressed) out.buttons |= kTouchB;
        if (gp.buttonB.isPressed) out.buttons |= kTouchC;
        if (gp.buttonY.isPressed) out.buttons |= kTouchD;
        if (gp.leftShoulder.isPressed)  out.buttons |= (kTouchA | kTouchD);
        if (gp.leftTrigger.isPressed)   out.buttons |= kTouchHeat;
        if (gp.rightShoulder.isPressed) out.buttons |= kTouchE;
        if (gp.rightTrigger.isPressed)  out.buttons |= kTouchDash;
        if (gp.buttonMenu.isPressed)    out.buttons |= kTouchStart;
        if (@available(iOS 13.0, macOS 10.15, *)) {
            if (gp.buttonOptions != nil && gp.buttonOptions.isPressed) {
                out.buttons |= kTouchFN1;
            }
            if (gp.rightThumbstickButton != nil && gp.rightThumbstickButton.isPressed) {
                out.buttons |= kTouchFN2;
            }
        }
    } else if (ctrl.microGamepad != nil) {
        GCMicroGamepad* mgp = ctrl.microGamepad;
        const float lx = mgp.dpad.xAxis.value;
        const float ly = mgp.dpad.yAxis.value;
        out.axis_x = lx;
        out.axis_y = -ly;
        if (mgp.dpad.up.isPressed || ly > 0.35f)    out.buttons |= kTouchUp;
        if (mgp.dpad.down.isPressed || ly < -0.35f) out.buttons |= kTouchDown;
        if (mgp.dpad.left.isPressed || lx < -0.35f) out.buttons |= kTouchLeft;
        if (mgp.dpad.right.isPressed || lx > 0.35f) out.buttons |= kTouchRight;
        if (mgp.buttonA.isPressed) out.buttons |= kTouchA;
        if (mgp.buttonX.isPressed) out.buttons |= kTouchB;
        if (mgp.buttonMenu.isPressed) out.buttons |= kTouchStart;
    }
}
#endif

// ---------------------------------------------------------------------------
// DirectInput8 Guest COM Method Implementations (stdcall)
// ---------------------------------------------------------------------------
void di_unk_query_interface(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t this_va = ctx.arg32(mem, 0);
    const uint32_t ppv_va  = ctx.arg32(mem, 2);
    if (ppv_va) mem.w32(ppv_va, this_va);
    ctx.eax = kDI_OK;
    ctx.ret_stdcall(mem, 12u);
}

void di_unk_addref(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 4u);
}

void di_unk_release(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = 0u;
    ctx.ret_stdcall(mem, 4u);
}

template <uint32_t ArgBytes>
void di_ret_ok(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = kDI_OK;
    ctx.ret_stdcall(mem, ArgBytes);
}

// IDirectInput8A::CreateDevice(this, rguid, lplpDirectInputDevice, pUnkOuter) -> 16 bytes
void di8_create_device(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t rguid_va = ctx.arg32(mem, 1);
    const uint32_t ppdev_va = ctx.arg32(mem, 2);
    if (ppdev_va == 0u || rguid_va == 0u) {
        ctx.eax = kDIERR_INVALIDPARAM;
        ctx.ret_stdcall(mem, 16u);
        return;
    }

    uint8_t guid[16] = {};
    mem.read_bytes(rguid_va, guid, 16);

    uint32_t dev_va = g_input.pad_obj_va[0];
    if (std::memcmp(guid, kGuidSysKeyboard, 16) == 0) {
        dev_va = g_input.kbd_obj_va;
    } else if (std::memcmp(guid, kGuidSysMouse, 16) == 0) {
        dev_va = g_input.mouse_obj_va;
    } else if (guid[0] == 0x02u && guid[1] == 0x50u) {
        dev_va = g_input.pad_obj_va[1];
    }

    mem.w32(ppdev_va, dev_va);
    ctx.eax = kDI_OK;
    ctx.ret_stdcall(mem, 16u);
}

// IDirectInput8A::EnumDevices(this, dwDevType, lpCallback, pvRef, dwFlags) -> 20 bytes
void di8_enum_devices(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t dev_type = ctx.arg32(mem, 1);
    const uint32_t cb_va    = ctx.arg32(mem, 2);
    const uint32_t pv_ref   = ctx.arg32(mem, 3);

    if (cb_va != 0u && (dev_type == kDI8DEVCLASS_GAMECTRL || dev_type == 0u)) {
        const uint32_t inst_va = mem.guest_calloc(1u, 580u); // sizeof(DIDEVICEINSTANCEA) == 580
        if (inst_va != 0u) {
            const int pad_count = g_input.has_gc.load(std::memory_order_relaxed) ? 2 : 1;
            for (int p = 0; p < pad_count; ++p) {
                if (p == 1 && !g_input.pads[1].connected) break;
                mem.zero_bytes(inst_va, 580u);
                mem.w32(inst_va + 0u, 580u); // dwSize
                // guidInstance
                mem.w32(inst_va + 4u, 0x4D425001u + static_cast<uint32_t>(p));
                mem.w32(inst_va + 8u, 0x11D30001u);
                mem.w32(inst_va + 12u, 0x44455600u);
                mem.w32(inst_va + 16u, 0x00000001u + static_cast<uint32_t>(p));
                // guidProduct
                mem.w32(inst_va + 20u, 0x4D425000u);
                mem.w32(inst_va + 24u, 0x11D30001u);
                mem.w32(inst_va + 28u, 0x44455600u);
                mem.w32(inst_va + 32u, 0x00000001u);
                // dwDevType
                mem.w32(inst_va + 36u, kDI8DEVTYPE_GAMEPAD);
                // tszInstanceName (+40) and tszProductName (+300)
                const char* name = (p == 0) ? "iOS Controller P1" : "iOS Controller P2";
                mem.write_cstring(inst_va + 40u, name, 260u);
                mem.write_cstring(inst_va + 300u, name, 260u);

                // DIENUMCALLBACKA(lpddi, pvRef) __stdcall
                const uint32_t ret_sentinel = 0x00FFFFF1u;
                ctx.push32(mem, pv_ref);
                ctx.push32(mem, inst_va);
                ctx.push32(mem, ret_sentinel);
                call_indirect(ctx, mem, cb_va);
                if (ctx.eax == 0u) break; // DIENUM_STOP
            }
            mem.guest_free(inst_va);
        }
    }

    ctx.eax = kDI_OK;
    ctx.ret_stdcall(mem, 20u);
}

// IDirectInputDevice8A::EnumObjects(this, lpCallback, pvRef, dwFlags) -> 16 bytes
void dev_enum_objects(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t this_va = ctx.arg32(mem, 0);
    const uint32_t cb_va   = ctx.arg32(mem, 1);
    const uint32_t pv_ref  = ctx.arg32(mem, 2);
    const uint32_t dw_flags = ctx.arg32(mem, 3);
    const auto kind = static_cast<DiDeviceKind>(mem.r32(this_va + 4u));

    if (cb_va != 0u && kind == DiDeviceKind::Gamepad) {
        // DIDEVICEOBJECTINSTANCEA size == 316 bytes (0x13C)
        const uint32_t obj_va = mem.guest_calloc(1u, 316u);
        if (obj_va != 0u) {
            auto invoke_cb = [&](uint32_t dw_type, uint32_t dw_ofs, const char* label) -> bool {
                mem.zero_bytes(obj_va, 316u);
                mem.w32(obj_va + 0u, 316u);
                mem.w32(obj_va + 20u, dw_ofs);
                mem.w32(obj_va + 24u, dw_type);
                mem.write_cstring(obj_va + 32u, label, 260u);

                ctx.push32(mem, pv_ref);
                ctx.push32(mem, obj_va);
                ctx.push32(mem, 0x00FFFFF2u);
                call_indirect(ctx, mem, cb_va);
                return ctx.eax != 0u;
            };

            const bool want_axis = (dw_flags == 0u) || ((dw_flags & kDIDFT_AXIS) != 0u);
            const bool want_pov  = (dw_flags == 0u) || ((dw_flags & kDIDFT_POV) != 0u);
            const bool want_btn  = (dw_flags == 0u) || ((dw_flags & kDIDFT_BUTTON) != 0u);

            bool cont = true;
            if (want_axis && cont) cont = invoke_cb(kDIDFT_AXIS | 0x00000000u, 0u, "X Axis");
            if (want_axis && cont) cont = invoke_cb(kDIDFT_AXIS | 0x00000100u, 4u, "Y Axis");
            if (want_pov && cont)  cont = invoke_cb(kDIDFT_POV  | 0x00000000u, 32u, "POV Hat");
            if (want_btn && cont) {
                for (uint32_t b = 0; b < 12u && cont; ++b) {
                    char label[24];
                    std::snprintf(label, sizeof(label), "Button %u", b);
                    cont = invoke_cb(kDIDFT_BUTTON | (b << 8), 48u + b, label);
                }
            }
            mem.guest_free(obj_va);
        }
    }

    ctx.eax = kDI_OK;
    ctx.ret_stdcall(mem, 16u);
}

// Ensures MBAA.exe's in-memory PadConfig (0x0074DA18, stride 0x164) stays bound to
// iOS virtual/GCController pads with canonical button slots even when a PC System/_KeyConfig.ini
// (e.g. P0_Num=0 or a different USB stick like Xin-Mo Controller) is present in Assets.
void sync_ios_pad_config(GuestMemory& mem) {
    constexpr uint32_t kPadConfigBaseVa  = 0x0074DA18u;
    constexpr uint32_t kPadConfigStride  = 0x00000164u;
    constexpr uint32_t kJoyVecBeginVa    = 0x0076E9B8u;
    constexpr uint32_t kJoyVecEndVa      = 0x0076E9BCu;
    constexpr uint32_t kJoyEntrySize     = 0x00000150u;

    const uint32_t vec_begin = mem.r32(kJoyVecBeginVa);
    const uint32_t vec_end   = mem.r32(kJoyVecEndVa);
    if (vec_begin == 0u || vec_end <= vec_begin) {
        return;
    }

    const uint32_t joy_count = (vec_end - vec_begin) / kJoyEntrySize;
    if (joy_count < 1u) {
        return;
    }

    auto ensure_slot = [&](uint32_t slot, uint32_t joy_num, const char* expected_name) {
        const uint32_t base = kPadConfigBaseVa + slot * kPadConfigStride;
        if (!mem.in_bounds(base, kPadConfigStride)) {
            return;
        }
        const uint32_t cur_num = mem.r32(base);
        char cur_name[20] = {};
        mem.read_bytes(base + 4u, cur_name, sizeof(cur_name));
        if (cur_num == joy_num && std::strncmp(cur_name, expected_name, sizeof(cur_name) - 1) == 0) {
            return;
        }

        mem.zero_bytes(base, kPadConfigStride);
        mem.w32(base, joy_num);
        mem.write_cstring(base + 4u, expected_name, 256u);

        // val_idx mapping matching MBAA.exe 0x0054d138 + sub_0049fad0/sub_0049fca0:
        //   val=1..16 -> rgbButtons[val - 1], val=21..24 -> +/- X/Y axes
        const uint32_t vals_va = base + 0x104u;
        mem.w32(vals_va +  0u * 4u, 24u); // Up    (lY < 0)
        mem.w32(vals_va +  1u * 4u, 23u); // Down  (lY > 0)
        mem.w32(vals_va +  2u * 4u, 22u); // Left  (lX < 0)
        mem.w32(vals_va +  3u * 4u, 21u); // Right (lX > 0)
        mem.w32(vals_va +  4u * 4u,  6u); // Pause/Start (0x001) -> rgbButtons[5]
        mem.w32(vals_va +  6u * 4u,  4u); // Shield D    (0x004) -> rgbButtons[3]
        mem.w32(vals_va +  7u * 4u,  3u); // Strong C    (0x008) -> rgbButtons[2]
        mem.w32(vals_va +  8u * 4u,  1u); // Weak A      (0x010) -> rgbButtons[0]
        mem.w32(vals_va +  9u * 4u,  2u); // Medium B    (0x020) -> rgbButtons[1]
        mem.w32(vals_va + 10u * 4u,  9u); // A+B macro   (0x040) -> rgbButtons[8]
        mem.w32(vals_va + 11u * 4u,  5u); // Quick E     (0x080) -> rgbButtons[4]
        mem.w32(vals_va + 12u * 4u,  7u); // FN1         (0x100) -> rgbButtons[6]
        mem.w32(vals_va + 13u * 4u,  8u); // FN2         (0x200) -> rgbButtons[7]
        mem.w32(vals_va + 14u * 4u,  1u); // Menu Confirm(0x400) -> rgbButtons[0]
        mem.w32(vals_va + 15u * 4u,  2u); // Menu Cancel (0x800) -> rgbButtons[1]
    };

    ensure_slot(0u, 1u, "iOS Controller P1");
    if (joy_count >= 2u && g_input.pads[1].connected) {
        ensure_slot(1u, 2u, "iOS Controller P2");
    }
}

// IDirectInputDevice8A::GetDeviceState(this, cbData, lpvData) -> 12 bytes
void dev_get_device_state(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t this_va = ctx.arg32(mem, 0);
    const uint32_t cb_data = ctx.arg32(mem, 1);
    const uint32_t lpv_va  = ctx.arg32(mem, 2);

    if (lpv_va == 0u || cb_data == 0u) {
        ctx.eax = kDIERR_INVALIDPARAM;
        ctx.ret_stdcall(mem, 12u);
        return;
    }

    mem.zero_bytes(lpv_va, cb_data);

    const auto kind = static_cast<DiDeviceKind>(mem.r32(this_va + 4u));
    const uint32_t pad_idx = mem.r32(this_va + 8u) & 1u;

    const CombinedPadSnapshot& p1 = g_input.pads[0];
    const CombinedPadSnapshot& p  = g_input.pads[pad_idx];

    if (kind == DiDeviceKind::Keyboard && cb_data >= 256u) {
        // Bridge Touch + P1 GCController to exact MBAA.exe P1 DIK scancodes (0x0054d2c0)
        const uint32_t b = p1.buttons;
        if (b & kTouchUp)     mem.w8(lpv_va + kDIK_W, 0x80u);
        if (b & kTouchDown)   mem.w8(lpv_va + kDIK_S, 0x80u);
        if (b & kTouchLeft)   mem.w8(lpv_va + kDIK_A, 0x80u);
        if (b & kTouchRight)  mem.w8(lpv_va + kDIK_D, 0x80u);
        if (b & kTouchA)      mem.w8(lpv_va + kDIK_C, 0x80u);
        if (b & kTouchB)      mem.w8(lpv_va + kDIK_V, 0x80u);
        if (b & kTouchC)      mem.w8(lpv_va + kDIK_B, 0x80u);
        if (b & kTouchD)      mem.w8(lpv_va + kDIK_F, 0x80u);
        if (b & kTouchE)      mem.w8(lpv_va + kDIK_E, 0x80u);
        if (b & kTouchStart)  mem.w8(lpv_va + kDIK_Q, 0x80u);
    } else if (kind == DiDeviceKind::Gamepad && cb_data >= 272u) {
        sync_ios_pad_config(mem);

        // DIJOYSTATE2 (0x110 = 272 bytes):
        //   +0x00 lX, +0x04 lY (scaled by 0.1275 in MBAA.exe 0x00410725 -> use -1000..+1000)
        //   +0x20 rgdwPOV[4]
        //   +0x30 rgbButtons[128]
        const uint32_t b = p.buttons;
        int32_t lx = static_cast<int32_t>(std::clamp(p.axis_x, -1.0f, 1.0f) * 1000.0f);
        int32_t ly = static_cast<int32_t>(std::clamp(p.axis_y, -1.0f, 1.0f) * 1000.0f);
        if (b & kTouchLeft)  lx = -1000;
        if (b & kTouchRight) lx = 1000;
        if (b & kTouchUp)    ly = -1000;
        if (b & kTouchDown)  ly = 1000;

        mem.w32(lpv_va + 0x00u, static_cast<uint32_t>(lx));
        mem.w32(lpv_va + 0x04u, static_cast<uint32_t>(ly));
        mem.w32(lpv_va + 0x20u, pov_from_dpad(b));
        mem.w32(lpv_va + 0x24u, 0xFFFFFFFFu);
        mem.w32(lpv_va + 0x28u, 0xFFFFFFFFu);
        mem.w32(lpv_va + 0x2Cu, 0xFFFFFFFFu);

        if (b & kTouchA)     mem.w8(lpv_va + 0x30u + 0u, 0x80u); // Button 1: A
        if (b & kTouchB)     mem.w8(lpv_va + 0x30u + 1u, 0x80u); // Button 2: B
        if (b & kTouchC)     mem.w8(lpv_va + 0x30u + 2u, 0x80u); // Button 3: C
        if (b & kTouchD)     mem.w8(lpv_va + 0x30u + 3u, 0x80u); // Button 4: D
        if (b & kTouchE)     mem.w8(lpv_va + 0x30u + 4u, 0x80u); // Button 5: E
        if (b & kTouchStart) mem.w8(lpv_va + 0x30u + 5u, 0x80u); // Button 6: Pause/Start
        if (b & kTouchFN1)   mem.w8(lpv_va + 0x30u + 6u, 0x80u); // Button 7: FN1
        if (b & kTouchFN2)   mem.w8(lpv_va + 0x30u + 7u, 0x80u); // Button 8: FN2
        if (b & kTouchDash)  mem.w8(lpv_va + 0x30u + 8u, 0x80u); // Button 9: A+B Dash
    }

    ctx.eax = kDI_OK;
    ctx.ret_stdcall(mem, 12u);
}

// IDirectInputDevice8A::GetDeviceData(this, cbObjectData, rgdod, pdwInOut, dwFlags) -> 20 bytes
void dev_get_device_data(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pdw_inout = ctx.arg32(mem, 3);
    if (pdw_inout) mem.w32(pdw_inout, 0u);
    ctx.eax = kDI_OK;
    ctx.ret_stdcall(mem, 20u);
}

uint32_t build_vtable(GuestMemory& mem, const RecompFn* slots, size_t count) {
    const uint32_t vt = mem.alloc_thunk_block(static_cast<uint32_t>(count * 4u), 4u);
    for (size_t i = 0; i < count; ++i) {
        mem.w32(vt + static_cast<uint32_t>(i * 4u), alloc_com_method_thunk(slots[i]));
    }
    return vt;
}

void ensure_dinput_objects(GuestMemory& mem) {
    if (g_input.di8_obj_va != 0u && mem.r32(g_input.di8_obj_va) != 0u) {
        return;
    }

    // IDirectInput8A: 10 slots
    RecompFn di8_slots[10] = {
        &di_unk_query_interface,
        &di_unk_addref,
        &di_unk_release,
        &di8_create_device,  // +0x0C
        &di8_enum_devices,   // +0x10
        &di_ret_ok<8u>,      // +0x14 GetDeviceStatus
        &di_ret_ok<12u>,     // +0x18 RunControlPanel
        &di_ret_ok<12u>,     // +0x1C Initialize
        &di_ret_ok<16u>,     // +0x20 FindDevice
        &di_ret_ok<20u>,     // +0x24 EnumDevicesBySemantics
    };
    g_input.di8_vtable = build_vtable(mem, di8_slots, 10);

    // IDirectInputDevice8A: 32 slots (+0x00 .. +0x7C, Poll is at +0x64 = slot 25)
    RecompFn dev_slots[32];
    for (auto& fn : dev_slots) fn = &di_ret_ok<4u>;
    dev_slots[0]  = &di_unk_query_interface;
    dev_slots[1]  = &di_unk_addref;
    dev_slots[2]  = &di_unk_release;
    dev_slots[3]  = &di_ret_ok<8u>;      // +0x0C GetCapabilities
    dev_slots[4]  = &dev_enum_objects;   // +0x10 EnumObjects
    dev_slots[5]  = &di_ret_ok<12u>;     // +0x14 GetProperty
    dev_slots[6]  = &di_ret_ok<12u>;     // +0x18 SetProperty
    dev_slots[7]  = &di_ret_ok<4u>;      // +0x1C Acquire
    dev_slots[8]  = &di_ret_ok<4u>;      // +0x20 Unacquire
    dev_slots[9]  = &dev_get_device_state; // +0x24 GetDeviceState
    dev_slots[10] = &dev_get_device_data;  // +0x28 GetDeviceData
    dev_slots[11] = &di_ret_ok<8u>;      // +0x2C SetDataFormat
    dev_slots[12] = &di_ret_ok<8u>;      // +0x30 SetEventNotification
    dev_slots[13] = &di_ret_ok<12u>;     // +0x34 SetCooperativeLevel
    dev_slots[14] = &di_ret_ok<16u>;     // +0x38 GetObjectInfo
    dev_slots[15] = &di_ret_ok<8u>;      // +0x3C GetDeviceInfo
    dev_slots[25] = &di_ret_ok<4u>;      // +0x64 Poll
    g_input.dev_vtable = build_vtable(mem, dev_slots, 32);

    g_input.di8_obj_va = mem.alloc_thunk_block(16u, 8u);
    mem.w32(g_input.di8_obj_va, g_input.di8_vtable);

    auto make_dev = [&](DiDeviceKind kind, uint32_t pad_idx) {
        const uint32_t va = mem.alloc_thunk_block(16u, 8u);
        mem.w32(va + 0u, g_input.dev_vtable);
        mem.w32(va + 4u, static_cast<uint32_t>(kind));
        mem.w32(va + 8u, pad_idx);
        return va;
    };
    g_input.kbd_obj_va    = make_dev(DiDeviceKind::Keyboard, 0u);
    g_input.mouse_obj_va  = make_dev(DiDeviceKind::Mouse, 0u);
    g_input.pad_obj_va[0] = make_dev(DiDeviceKind::Gamepad, 0u);
    g_input.pad_obj_va[1] = make_dev(DiDeviceKind::Gamepad, 1u);
}

} // namespace

void input_set_touch_state(const TouchInputState& state) {
    std::lock_guard<std::mutex> lock(g_input.touch_mutex);
    g_input.touch = state;
}

TouchInputState input_get_touch_state() {
    std::lock_guard<std::mutex> lock(g_input.touch_mutex);
    return g_input.touch;
}

void input_init() {
    if (g_input.initialized.exchange(true)) return;
#if defined(__APPLE__)
    NSNotificationCenter* nc = [NSNotificationCenter defaultCenter];
    g_input.connect_observer = [nc addObserverForName:GCControllerDidConnectNotification
                                               object:nil
                                                queue:nil
                                           usingBlock:^(NSNotification*) {
        g_input.has_gc.store([[GCController controllers] count] > 0, std::memory_order_relaxed);
    }];
    g_input.disconnect_observer = [nc addObserverForName:GCControllerDidDisconnectNotification
                                                  object:nil
                                                   queue:nil
                                              usingBlock:^(NSNotification*) {
        g_input.has_gc.store([[GCController controllers] count] > 0, std::memory_order_relaxed);
    }];
    [GCController startWirelessControllerDiscoveryWithCompletionHandler:nil];
    g_input.has_gc.store([[GCController controllers] count] > 0, std::memory_order_relaxed);
#endif
}

void input_shutdown() {
    if (!g_input.initialized.exchange(false)) return;
#if defined(__APPLE__)
    [GCController stopWirelessControllerDiscovery];
    NSNotificationCenter* nc = [NSNotificationCenter defaultCenter];
    if (g_input.connect_observer != nil) {
        [nc removeObserver:g_input.connect_observer];
        g_input.connect_observer = nil;
    }
    if (g_input.disconnect_observer != nil) {
        [nc removeObserver:g_input.disconnect_observer];
        g_input.disconnect_observer = nil;
    }
#endif
    g_input.has_gc.store(false, std::memory_order_relaxed);
}

void input_poll_platform() {
    TouchInputState touch_copy;
    {
        std::lock_guard<std::mutex> lock(g_input.touch_mutex);
        touch_copy = g_input.touch;
    }

    CombinedPadSnapshot p1{};
    CombinedPadSnapshot p2{};

#if defined(__APPLE__)
    NSArray<GCController*>* ctrls = [GCController controllers];
    const NSUInteger count = [ctrls count];
    g_input.has_gc.store(count > 0, std::memory_order_relaxed);
    if (count >= 1) poll_gc_controller(ctrls[0], p1);
    if (count >= 2) poll_gc_controller(ctrls[1], p2);
#endif

    // Merge virtual TouchOverlayView into P1 (TouchOverlayView uses +1=up, DirectInput uses -1=up)
    p1.buttons = expand_macros(p1.buttons | touch_copy.buttons);
    const float touch_di_y = -touch_copy.stick_y;
    if (std::abs(touch_copy.stick_x) > std::abs(p1.axis_x)) p1.axis_x = touch_copy.stick_x;
    if (std::abs(touch_di_y) > std::abs(p1.axis_y)) p1.axis_y = touch_di_y;
    p1.connected = true;

    p2.buttons = expand_macros(p2.buttons);

    g_input.pads[0] = p1;
    g_input.pads[1] = p2;
}

bool input_has_gc_controller() {
    return g_input.has_gc.load(std::memory_order_relaxed);
}

int16_t input_get_vk_state(int vk_code) {
    const uint32_t b = g_input.pads[0].buttons;
    bool down = false;
    switch (vk_code) {
        case 'W': down = (b & kTouchUp) != 0; break;
        case 'S': down = (b & kTouchDown) != 0; break;
        case 'A': down = (b & kTouchLeft) != 0; break;
        case 'D': down = (b & kTouchRight) != 0; break;
        case 'C': down = (b & kTouchA) != 0; break;
        case 'V': down = (b & kTouchB) != 0; break;
        case 'B': down = (b & kTouchC) != 0; break;
        case 'F': down = (b & kTouchD) != 0; break;
        case 'E': down = (b & kTouchE) != 0; break;
        case 'Q': down = (b & kTouchStart) != 0; break;
        default: break;
    }
    return down ? static_cast<int16_t>(-32767) : 0;
}

// DirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter) -> 20 bytes
void hle_direct_input8_create(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t ppv_out_va = ctx.arg32(mem, 3);
    if (ppv_out_va == 0u) {
        ctx.eax = kDIERR_INVALIDPARAM;
        ctx.ret_stdcall(mem, 20u);
        return;
    }
    ensure_dinput_objects(mem);
    mem.w32(ppv_out_va, g_input.di8_obj_va);
    ctx.eax = kDI_OK;
    ctx.ret_stdcall(mem, 20u);
}

} // namespace mbaa_recomp
