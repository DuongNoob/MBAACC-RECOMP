#pragma once

/**
 * @file hle_crt.h
 * @brief MSVC8 CRT, x87 math intrinsics, int64 helpers, SEH, and libvorbisfile HLE shims.
 *
 * Synced 100% against recompiler/crt_signatures.json (all 76 CRT VAs called by MBAA.exe .text).
 */

#include "mbaa_recomp/cpu_context.h"
#include "mbaa_recomp/guest_memory.h"

#include <cstdint>

namespace mbaa_recomp {

/// Dynamic dispatcher for any CRT VA in 0x004E00D0..0x0051AFFF.
void hle_crt_dispatch(CpuContext& ctx, GuestMemory& mem, uint32_t va);

/// Direct per-VA CRT HLE entrypoints (all 76 entries from recompiler/crt_signatures.json):
void hle_crt_004e00d0(CpuContext& ctx, GuestMemory& mem); // free
void hle_crt_004e0177(CpuContext& ctx, GuestMemory& mem); // operator new
void hle_crt_004e0230(CpuContext& ctx, GuestMemory& mem); // malloc
void hle_crt_004e02f3(CpuContext& ctx, GuestMemory& mem); // operator delete
void hle_crt_004e02f8(CpuContext& ctx, GuestMemory& mem); // __security_check_cookie
void hle_crt_004e0307(CpuContext& ctx, GuestMemory& mem); // operator delete[]
void hle_crt_004e0675(CpuContext& ctx, GuestMemory& mem); // operator new[]
void hle_crt_004e0680(CpuContext& ctx, GuestMemory& mem); // operator new[] (dbg/variant)
void hle_crt_004e068b(CpuContext& ctx, GuestMemory& mem); // sprintf
void hle_crt_004e0706(CpuContext& ctx, GuestMemory& mem); // strncmp
void hle_crt_004e07c4(CpuContext& ctx, GuestMemory& mem); // std::exception::exception()
void hle_crt_004e07d5(CpuContext& ctx, GuestMemory& mem); // std::exception::exception(const char* const&)
void hle_crt_004e083b(CpuContext& ctx, GuestMemory& mem); // std::exception::exception(const std::exception&)
void hle_crt_004e0893(CpuContext& ctx, GuestMemory& mem); // std::exception::~exception()
void hle_crt_004e0917(CpuContext& ctx, GuestMemory& mem); // memcpy_s
void hle_crt_004e0ab6(CpuContext& ctx, GuestMemory& mem); // atexit
void hle_crt_004e0bf2(CpuContext& ctx, GuestMemory& mem); // _invalid_parameter_noinfo
void hle_crt_004e0c02(CpuContext& ctx, GuestMemory& mem); // memmove_s
void hle_crt_004e0cc5(CpuContext& ctx, GuestMemory& mem); // sscanf
void hle_crt_004e0cf0(CpuContext& ctx, GuestMemory& mem); // strncpy
void hle_crt_004e0e20(CpuContext& ctx, GuestMemory& mem); // strstr
void hle_crt_004e0eb7(CpuContext& ctx, GuestMemory& mem); // atoi
void hle_crt_004e0fe7(CpuContext& ctx, GuestMemory& mem); // atof
void hle_crt_004e10aa(CpuContext& ctx, GuestMemory& mem); // _get_crtheap
void hle_crt_004e1340(CpuContext& ctx, GuestMemory& mem); // exit
void hle_crt_004e13cc(CpuContext& ctx, GuestMemory& mem); // realloc
void hle_crt_004e1660(CpuContext& ctx, GuestMemory& mem); // strrchr
void hle_crt_004e18d3(CpuContext& ctx, GuestMemory& mem); // wcstombs
void hle_crt_004e1900(CpuContext& ctx, GuestMemory& mem); // strchr
void hle_crt_004e1a12(CpuContext& ctx, GuestMemory& mem); // isalnum
void hle_crt_004e1a8c(CpuContext& ctx, GuestMemory& mem); // isdigit
void hle_crt_004e1b09(CpuContext& ctx, GuestMemory& mem); // isprint
void hle_crt_004e1c34(CpuContext& ctx, GuestMemory& mem); // __ehvec_dtor
void hle_crt_004e1c97(CpuContext& ctx, GuestMemory& mem); // __ehvec_ctor
void hle_crt_004e1cfc(CpuContext& ctx, GuestMemory& mem); // _time64
void hle_crt_004e1d40(CpuContext& ctx, GuestMemory& mem); // memchr
void hle_crt_004e1ded(CpuContext& ctx, GuestMemory& mem); // _difftime64
void hle_crt_004e1e2e(CpuContext& ctx, GuestMemory& mem); // _endthreadex
void hle_crt_004e1f28(CpuContext& ctx, GuestMemory& mem); // _beginthreadex
void hle_crt_004e20de(CpuContext& ctx, GuestMemory& mem); // _stricmp
void hle_crt_004e21df(CpuContext& ctx, GuestMemory& mem); // _vsnprintf
void hle_crt_004e2ca0(CpuContext& ctx, GuestMemory& mem); // strftime
void hle_crt_004e2cbd(CpuContext& ctx, GuestMemory& mem); // remove
void hle_crt_004e2d59(CpuContext& ctx, GuestMemory& mem); // fclose
void hle_crt_004e309a(CpuContext& ctx, GuestMemory& mem); // _localtime32
void hle_crt_004e30be(CpuContext& ctx, GuestMemory& mem); // _snprintf
void hle_crt_004e325b(CpuContext& ctx, GuestMemory& mem); // _strnicmp
void hle_crt_004e3333(CpuContext& ctx, GuestMemory& mem); // vsprintf
void hle_crt_004e334a(CpuContext& ctx, GuestMemory& mem); // _controlfp_s
void hle_crt_004e34e2(CpuContext& ctx, GuestMemory& mem); // _clearfp
void hle_crt_004e3b12(CpuContext& ctx, GuestMemory& mem); // toupper
void hle_crt_004e3e1b(CpuContext& ctx, GuestMemory& mem); // _CxxThrowException
void hle_crt_004e422c(CpuContext& ctx, GuestMemory& mem); // __EH_prolog3
void hle_crt_004e6340(CpuContext& ctx, GuestMemory& mem); // memset
void hle_crt_004e63c0(CpuContext& ctx, GuestMemory& mem); // memcpy
void hle_crt_004eae60(CpuContext& ctx, GuestMemory& mem); // _alldiv
void hle_crt_004eaf10(CpuContext& ctx, GuestMemory& mem); // _allrem
void hle_crt_004edba0(CpuContext& ctx, GuestMemory& mem); // _allmul
void hle_crt_004efab0(CpuContext& ctx, GuestMemory& mem); // __alloca_probe (__chkstk)
void hle_crt_004f0a50(CpuContext& ctx, GuestMemory& mem); // _alldvrm
void hle_crt_004f1ece(CpuContext& ctx, GuestMemory& mem); // DirectSoundCreate8 thunk
void hle_crt_004f3170(CpuContext& ctx, GuestMemory& mem); // ov_clear
void hle_crt_004f32f0(CpuContext& ctx, GuestMemory& mem); // ov_time_total
void hle_crt_004f41a0(CpuContext& ctx, GuestMemory& mem); // ov_time_seek
void hle_crt_004f4290(CpuContext& ctx, GuestMemory& mem); // ov_info
void hle_crt_004f4620(CpuContext& ctx, GuestMemory& mem); // ov_read
void hle_crt_004f49a0(CpuContext& ctx, GuestMemory& mem); // ov_open_callbacks
void hle_crt_004f49f0(CpuContext& ctx, GuestMemory& mem); // _ftol2_sse
void hle_crt_004f4a26(CpuContext& ctx, GuestMemory& mem); // _ftol2
void hle_crt_0050e1d0(CpuContext& ctx, GuestMemory& mem); // _CIatan
void hle_crt_0050e2b0(CpuContext& ctx, GuestMemory& mem); // _CIsqrt
void hle_crt_0050e8d0(CpuContext& ctx, GuestMemory& mem); // _CIpow
void hle_crt_0050eb60(CpuContext& ctx, GuestMemory& mem); // _CIsin
void hle_crt_0050ec90(CpuContext& ctx, GuestMemory& mem); // _CIcos
void hle_crt_0050edc0(CpuContext& ctx, GuestMemory& mem); // _CIacos
void hle_crt_00513030(CpuContext& ctx, GuestMemory& mem); // _CItan

} // namespace mbaa_recomp
