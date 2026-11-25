#pragma once

/**
 * @file cpu_context.h
 * @brief Lifted x86-32 CPU, x87 FPU, and SSE register/flag state for mbaa_recomp.
 *
 * Shared contract across lifter-dev, runtime-hle, shader-gfx, and ios-shell.
 */

#include <bit>
#include <cmath>
#include <cstdint>
#include <cstring>

namespace mbaa_recomp {

struct CpuContext {
    // General-purpose 32-bit registers
    uint32_t eax = 0;
    uint32_t ecx = 0;
    uint32_t edx = 0;
    uint32_t ebx = 0;
    uint32_t esp = 0;
    uint32_t ebp = 0;
    uint32_t esi = 0;
    uint32_t edi = 0;

    // Instruction pointer & flags
    uint32_t eip    = 0;
    uint32_t eflags = 0x00000202u;

    // x87 FPU state (8-slot circular stack indexed via st_top)
    double   st[8]  = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    int      st_top = 0;
    uint16_t fpu_cw = 0x027Fu; // Default MSVC x87 CW: 53-bit precision, round-nearest, masked exceptions
    uint16_t fpu_sw = 0x0000u;

    // Thread Environment Block base for fs:[0] (SEH chain, TIB)
    uint32_t fs_0 = 0x00300000u;

    // SSE 128-bit registers XMM0..XMM7
    uint8_t xmm[8][16] = {};

    // EFLAGS bit masks
    static constexpr uint32_t kFlagCF = 1u << 0;
    static constexpr uint32_t kFlagPF = 1u << 2;
    static constexpr uint32_t kFlagAF = 1u << 4;
    static constexpr uint32_t kFlagZF = 1u << 6;
    static constexpr uint32_t kFlagSF = 1u << 7;
    static constexpr uint32_t kFlagIF = 1u << 9;
    static constexpr uint32_t kFlagDF = 1u << 10;
    static constexpr uint32_t kFlagOF = 1u << 11;

    // x87 FPU Status Word condition/status masks
    static constexpr uint16_t kFpuC0 = 0x0100u;
    static constexpr uint16_t kFpuC1 = 0x0200u;
    static constexpr uint16_t kFpuC2 = 0x0400u;
    static constexpr uint16_t kFpuC3 = 0x4000u;
    static constexpr uint16_t kFpuTopMask = 0x3800u;

    void reset(uint32_t initial_esp = 0x009FF000u, uint32_t teb_va = 0x00300000u) noexcept {
        eax = ecx = edx = ebx = ebp = esi = edi = 0;
        esp = initial_esp;
        eip = 0;
        eflags = 0x00000202u;
        for (double& slot : st) {
            slot = 0.0;
        }
        st_top = 0;
        fpu_cw = 0x027Fu;
        fpu_sw = 0x0000u;
        fs_0 = teb_va;
        std::memset(xmm, 0, sizeof(xmm));
    }

    // -----------------------------------------------------------------------
    // EFLAGS accessors and updaters
    // -----------------------------------------------------------------------
    [[nodiscard]] bool get_cf() const noexcept { return (eflags & kFlagCF) != 0; }
    [[nodiscard]] bool get_pf() const noexcept { return (eflags & kFlagPF) != 0; }
    [[nodiscard]] bool get_af() const noexcept { return (eflags & kFlagAF) != 0; }
    [[nodiscard]] bool get_zf() const noexcept { return (eflags & kFlagZF) != 0; }
    [[nodiscard]] bool get_sf() const noexcept { return (eflags & kFlagSF) != 0; }
    [[nodiscard]] bool get_df() const noexcept { return (eflags & kFlagDF) != 0; }
    [[nodiscard]] bool get_of() const noexcept { return (eflags & kFlagOF) != 0; }

    void set_flag(uint32_t mask, bool value) noexcept {
        if (value) {
            eflags |= mask;
        } else {
            eflags &= ~mask;
        }
    }

    void set_cf(bool v) noexcept { set_flag(kFlagCF, v); }
    void set_pf(bool v) noexcept { set_flag(kFlagPF, v); }
    void set_af(bool v) noexcept { set_flag(kFlagAF, v); }
    void set_zf(bool v) noexcept { set_flag(kFlagZF, v); }
    void set_sf(bool v) noexcept { set_flag(kFlagSF, v); }
    void set_df(bool v) noexcept { set_flag(kFlagDF, v); }
    void set_of(bool v) noexcept { set_flag(kFlagOF, v); }

    [[nodiscard]] static bool parity_even(uint8_t low_byte) noexcept {
        return (std::popcount(low_byte) & 1) == 0;
    }

    void set_szp8(uint8_t result) noexcept {
        set_zf(result == 0);
        set_sf((result & 0x80u) != 0);
        set_pf(parity_even(result));
    }

    void set_szp16(uint16_t result) noexcept {
        set_zf(result == 0);
        set_sf((result & 0x8000u) != 0);
        set_pf(parity_even(static_cast<uint8_t>(result & 0xFFu)));
    }

    void set_szp32(uint32_t result) noexcept {
        set_zf(result == 0);
        set_sf((result & 0x80000000u) != 0);
        set_pf(parity_even(static_cast<uint8_t>(result & 0xFFu)));
    }

    // -----------------------------------------------------------------------
    // 8/16-bit sub-register helpers
    // -----------------------------------------------------------------------
    [[nodiscard]] uint8_t  al() const noexcept { return static_cast<uint8_t>(eax & 0xFFu); }
    [[nodiscard]] uint8_t  ah() const noexcept { return static_cast<uint8_t>((eax >> 8) & 0xFFu); }
    [[nodiscard]] uint16_t ax() const noexcept { return static_cast<uint16_t>(eax & 0xFFFFu); }
    void set_al(uint8_t v)  noexcept { eax = (eax & 0xFFFFFF00u) | v; }
    void set_ah(uint8_t v)  noexcept { eax = (eax & 0xFFFF00FFu) | (static_cast<uint32_t>(v) << 8); }
    void set_ax(uint16_t v) noexcept { eax = (eax & 0xFFFF0000u) | v; }

    [[nodiscard]] uint8_t  cl() const noexcept { return static_cast<uint8_t>(ecx & 0xFFu); }
    [[nodiscard]] uint8_t  ch() const noexcept { return static_cast<uint8_t>((ecx >> 8) & 0xFFu); }
    [[nodiscard]] uint16_t cx() const noexcept { return static_cast<uint16_t>(ecx & 0xFFFFu); }
    void set_cl(uint8_t v)  noexcept { ecx = (ecx & 0xFFFFFF00u) | v; }
    void set_ch(uint8_t v)  noexcept { ecx = (ecx & 0xFFFF00FFu) | (static_cast<uint32_t>(v) << 8); }
    void set_cx(uint16_t v) noexcept { ecx = (ecx & 0xFFFF0000u) | v; }

    [[nodiscard]] uint8_t  dl() const noexcept { return static_cast<uint8_t>(edx & 0xFFu); }
    [[nodiscard]] uint8_t  dh() const noexcept { return static_cast<uint8_t>((edx >> 8) & 0xFFu); }
    [[nodiscard]] uint16_t dx() const noexcept { return static_cast<uint16_t>(edx & 0xFFFFu); }
    void set_dl(uint8_t v)  noexcept { edx = (edx & 0xFFFFFF00u) | v; }
    void set_dh(uint8_t v)  noexcept { edx = (edx & 0xFFFF00FFu) | (static_cast<uint32_t>(v) << 8); }
    void set_dx(uint16_t v) noexcept { edx = (edx & 0xFFFF0000u) | v; }

    [[nodiscard]] uint8_t  bl() const noexcept { return static_cast<uint8_t>(ebx & 0xFFu); }
    [[nodiscard]] uint8_t  bh() const noexcept { return static_cast<uint8_t>((ebx >> 8) & 0xFFu); }
    [[nodiscard]] uint16_t bx() const noexcept { return static_cast<uint16_t>(ebx & 0xFFFFu); }
    void set_bl(uint8_t v)  noexcept { ebx = (ebx & 0xFFFFFF00u) | v; }
    void set_bh(uint8_t v)  noexcept { ebx = (ebx & 0xFFFF00FFu) | (static_cast<uint32_t>(v) << 8); }
    void set_bx(uint16_t v) noexcept { ebx = (ebx & 0xFFFF0000u) | v; }

    // -----------------------------------------------------------------------
    // Guest stack helpers (templated on GuestMemory to avoid include cycles)
    // -----------------------------------------------------------------------
    template <typename Mem>
    void push32(Mem& mem, uint32_t val) noexcept {
        esp -= 4u;
        mem.w32(esp, val);
    }

    template <typename Mem>
    uint32_t pop32(const Mem& mem) noexcept {
        const uint32_t val = mem.r32(esp);
        esp += 4u;
        return val;
    }

    template <typename Mem>
    void push16(Mem& mem, uint16_t val) noexcept {
        esp -= 2u;
        mem.w16(esp, val);
    }

    template <typename Mem>
    uint16_t pop16(const Mem& mem) noexcept {
        const uint16_t val = mem.r16(esp);
        esp += 2u;
        return val;
    }

    /// Reads 32-bit stack argument `index` (0 = [esp+4], 1 = [esp+8], ...) at HLE entry.
    template <typename Mem>
    [[nodiscard]] uint32_t arg32(const Mem& mem, uint32_t index) const noexcept {
        return mem.r32(esp + 4u + (index * 4u));
    }

    /// Pops return address into `eip` and cleans `arg_bytes` from stack (stdcall).
    template <typename Mem>
    void ret_stdcall(const Mem& mem, uint32_t arg_bytes) noexcept {
        eip = pop32(mem);
        esp += arg_bytes;
    }

    /// Pops return address into `eip` without removing arguments (cdecl).
    template <typename Mem>
    void ret_cdecl(const Mem& mem) noexcept {
        eip = pop32(mem);
    }

    // -----------------------------------------------------------------------
    // x87 FPU stack helpers
    // -----------------------------------------------------------------------
    void sync_fpu_top() noexcept {
        fpu_sw = static_cast<uint16_t>((fpu_sw & ~kFpuTopMask) | ((st_top & 7) << 11));
    }

    void fpu_push(double value) noexcept {
        st_top = (st_top - 1) & 7;
        st[st_top] = value;
        sync_fpu_top();
    }

    double fpu_pop() noexcept {
        const double value = st[st_top & 7];
        st[st_top & 7] = 0.0;
        st_top = (st_top + 1) & 7;
        sync_fpu_top();
        return value;
    }

    [[nodiscard]] double& fpu_st(int i = 0) noexcept {
        return st[(st_top + i) & 7];
    }

    [[nodiscard]] double fpu_st(int i = 0) const noexcept {
        return st[(st_top + i) & 7];
    }

    void fpu_set_cc(bool c3, bool c2, bool c0, bool c1 = false) noexcept {
        fpu_sw &= static_cast<uint16_t>(~(kFpuC0 | kFpuC1 | kFpuC2 | kFpuC3));
        if (c0) fpu_sw |= kFpuC0;
        if (c1) fpu_sw |= kFpuC1;
        if (c2) fpu_sw |= kFpuC2;
        if (c3) fpu_sw |= kFpuC3;
    }

    void fpu_compare(double a, double b) noexcept {
        if (std::isnan(a) || std::isnan(b)) {
            fpu_set_cc(true, true, true);
        } else if (a > b) {
            fpu_set_cc(false, false, false);
        } else if (a < b) {
            fpu_set_cc(false, false, true);
        } else {
            fpu_set_cc(true, false, false);
        }
    }

    void fpu_compare_eflags(double a, double b) noexcept {
        set_of(false);
        set_sf(false);
        set_af(false);
        if (std::isnan(a) || std::isnan(b)) {
            set_zf(true);
            set_pf(true);
            set_cf(true);
        } else if (a > b) {
            set_zf(false);
            set_pf(false);
            set_cf(false);
        } else if (a < b) {
            set_zf(false);
            set_pf(false);
            set_cf(true);
        } else {
            set_zf(true);
            set_pf(false);
            set_cf(false);
        }
    }
};

} // namespace mbaa_recomp
