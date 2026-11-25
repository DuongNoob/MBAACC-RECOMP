"""Disassemble and classify all 76 MSVC8 CRT / static-lib functions called by MBAA.exe game .text.

Generates `crt_signatures.json` with exact calling conventions, stack cleanup sizes,
parameter/return locations, disassembly previews, and semantic implementation notes
for `runtime-hle` and `cpp_emitter`.
"""

from __future__ import annotations

import argparse
import hashlib
import json
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Any

import capstone
import pefile

DEFAULT_MBAA_EXE = Path(r"c:\Users\A\Desktop\AI\google\MBAACC\MBAA.exe")
DEFAULT_FUNCTION_MAP = Path(r"c:\Users\A\Desktop\AI\google\mbaacc-src\evidence\function_map.json")
DEFAULT_OUTPUT_JSON = Path(__file__).resolve().with_name("crt_signatures.json")

MBAA_CRT_START_VA = 0x004E00D0


@dataclass(frozen=True)
class CrtSpec:
    name: str
    signature: str
    calling_convention: str
    stack_cleanup: int
    params: tuple[str, ...]
    returns: str
    category: str
    notes: str


# All 76 unique CRT / statically-linked library VAs called from game .text (0x00401000..0x004e00cf).
# Verified directly from Capstone disassembly of MBAA.exe (SHA-256 6d1415ca...).
CRT_SPECS: dict[int, CrtSpec] = {
    0x004E00D0: CrtSpec(
        "free",
        "void __cdecl free(void* ptr)",
        "cdecl",
        0,
        ("stack+4:ptr:u32",),
        "void",
        "memory",
        "Frees guest heap block allocated by malloc/calloc/realloc/new; NULL is a no-op.",
    ),
    0x004E0177: CrtSpec(
        "operator_new",
        "void* __cdecl operator new(size_t size)",
        "cdecl",
        0,
        ("stack+4:size:u32",),
        "eax:u32",
        "memory",
        "Allocates `size` bytes via guest_alloc (min 1 byte); returns VA in EAX.",
    ),
    0x004E0230: CrtSpec(
        "malloc",
        "void* __cdecl malloc(size_t size)",
        "cdecl",
        0,
        ("stack+4:size:u32",),
        "eax:u32",
        "memory",
        "Allocates `size` bytes via guest_alloc (min 1 byte); returns VA in EAX or 0 on failure.",
    ),
    0x004E02F3: CrtSpec(
        "operator_delete",
        "void __cdecl operator delete(void* ptr)",
        "cdecl",
        0,
        ("stack+4:ptr:u32",),
        "void",
        "memory",
        "Tail-jump thunk (jmp 0x004e00d0) to free(ptr).",
    ),
    0x004E02F8: CrtSpec(
        "__security_check_cookie",
        "void __fastcall __security_check_cookie(uintptr_t cookie)",
        "fastcall_ecx",
        0,
        ("ecx:cookie:u32",),
        "void",
        "security",
        "Checks ECX against [0x54b458] GS cookie; no stack args (repz ret). Safe no-op if cookie untouched or matching.",
    ),
    0x004E0307: CrtSpec(
        "operator_delete_array",
        "void __cdecl operator delete[](void* ptr)",
        "cdecl",
        0,
        ("stack+4:ptr:u32",),
        "void",
        "memory",
        "Tail-jump thunk (jmp 0x004e02f3) to free(ptr).",
    ),
    0x004E0675: CrtSpec(
        "operator_new_array",
        "void* __cdecl operator new[](size_t size)",
        "cdecl",
        0,
        ("stack+4:size:u32",),
        "eax:u32",
        "memory",
        "Forwards [esp+4] to operator new (0x004e0177); returns VA in EAX.",
    ),
    0x004E0680: CrtSpec(
        "operator_new_array_2",
        "void* __cdecl operator new[](size_t size)",
        "cdecl",
        0,
        ("stack+4:size:u32",),
        "eax:u32",
        "memory",
        "Forwards [esp+4] through 0x004de548 -> operator new (0x004e0177); returns VA in EAX.",
    ),
    0x004E068B: CrtSpec(
        "sprintf",
        "int __cdecl sprintf(char* buf, const char* fmt, ...)",
        "cdecl",
        0,
        ("stack+4:buf:ptr", "stack+8:fmt:cstr", "stack+12:varargs"),
        "eax:i32",
        "stdio",
        "Formats printf specifiers reading guest varargs from [esp+12..]; writes NUL-terminated string to buf, returns length in EAX.",
    ),
    0x004E0706: CrtSpec(
        "strncmp",
        "int __cdecl strncmp(const char* s1, const char* s2, size_t count)",
        "cdecl",
        0,
        ("stack+4:s1:cstr", "stack+8:s2:cstr", "stack+12:count:u32"),
        "eax:i32",
        "string",
        "Unsigned-char lexicographical compare up to `count` bytes; returns <0, 0, or >0 in EAX.",
    ),
    0x004E07C4: CrtSpec(
        "std_exception_ctor_default",
        "std::exception* __thiscall std::exception::exception(void)",
        "thiscall",
        0,
        ("ecx:this:ptr",),
        "eax:ptr",
        "eh_rtti",
        "Initializes std::exception struct at ECX: [this+0]=0x0051bd40 (vftable), [this+4]=0, [this+8]=0; returns this in EAX.",
    ),
    0x004E07D5: CrtSpec(
        "std_exception_ctor_what",
        "std::exception* __thiscall std::exception::exception(const char* const& what)",
        "thiscall",
        4,
        ("ecx:this:ptr", "stack+4:pwhat:ptr"),
        "eax:ptr",
        "eh_rtti",
        "Copies *pwhat into heap buffer at [this+4], sets [this+0]=0x0051bd40, [this+8]=1; pops 4-byte stack arg (ret 4); returns this in EAX.",
    ),
    0x004E083B: CrtSpec(
        "std_exception_ctor_copy",
        "std::exception* __thiscall std::exception::exception(const std::exception& rhs)",
        "thiscall",
        4,
        ("ecx:this:ptr", "stack+4:rhs:ptr"),
        "eax:ptr",
        "eh_rtti",
        "Copy-constructs std::exception at ECX from rhs; pops 4-byte stack arg (ret 4); returns this in EAX.",
    ),
    0x004E0893: CrtSpec(
        "std_exception_dtor",
        "void __thiscall std::exception::~exception(void)",
        "thiscall",
        0,
        ("ecx:this:ptr",),
        "void",
        "eh_rtti",
        "Sets [this+0]=0x0051bd40 and frees [this+4] if [this+8] != 0.",
    ),
    0x004E0917: CrtSpec(
        "memcpy_s",
        "errno_t __cdecl memcpy_s(void* dest, size_t destsz, const void* src, size_t count)",
        "cdecl",
        0,
        ("stack+4:dest:ptr", "stack+8:destsz:u32", "stack+12:src:ptr", "stack+16:count:u32"),
        "eax:i32",
        "memory",
        "Bounds-checked copy of `count` bytes from `src` to `dest`; returns 0 on success or EINVAL(22)/ERANGE(34).",
    ),
    0x004E0AB6: CrtSpec(
        "atexit",
        "int __cdecl atexit(void (*func)(void))",
        "cdecl",
        0,
        ("stack+4:func:va",),
        "eax:i32",
        "runtime",
        "Registers guest cleanup callback VA (e.g., 0x00519fe0, 0x0051a020) for process exit; returns 0.",
    ),
    0x004E0BF2: CrtSpec(
        "_invalid_parameter_noinfo",
        "void __cdecl _invalid_parameter_noinfo(void)",
        "cdecl",
        0,
        (),
        "void",
        "runtime",
        "MSVC8 CRT invalid-parameter handler (calls _invoke_watson if registered; safe log + return in HLE).",
    ),
    0x004E0C02: CrtSpec(
        "memmove_s",
        "errno_t __cdecl memmove_s(void* dest, size_t destsz, const void* src, size_t count)",
        "cdecl",
        0,
        ("stack+4:dest:ptr", "stack+8:destsz:u32", "stack+12:src:ptr", "stack+16:count:u32"),
        "eax:i32",
        "memory",
        "Bounds-checked overlap-safe copy of `count` bytes from `src` to `dest`; returns 0 on success.",
    ),
    0x004E0CC5: CrtSpec(
        "sscanf",
        "int __cdecl sscanf(const char* str, const char* fmt, ...)",
        "cdecl",
        0,
        ("stack+4:str:cstr", "stack+8:fmt:cstr", "stack+12:varargs"),
        "eax:i32",
        "stdio",
        "Parses formatted tokens from guest string `str` into guest pointer destinations at [esp+12..]; returns matched field count in EAX.",
    ),
    0x004E0CF0: CrtSpec(
        "strncpy",
        "char* __cdecl strncpy(char* dest, const char* src, size_t count)",
        "cdecl",
        0,
        ("stack+4:dest:ptr", "stack+8:src:cstr", "stack+12:count:u32"),
        "eax:ptr",
        "string",
        "Copies up to `count` bytes from `src` to `dest`, zero-padding remainder up to `count`; returns `dest` in EAX.",
    ),
    0x004E0E20: CrtSpec(
        "strstr",
        "const char* __cdecl strstr(const char* haystack, const char* needle)",
        "cdecl",
        0,
        ("stack+4:haystack:cstr", "stack+8:needle:cstr"),
        "eax:ptr",
        "string",
        "Finds first occurrence of NUL-terminated `needle` in `haystack`; returns guest VA or 0.",
    ),
    0x004E0EB7: CrtSpec(
        "atoi",
        "int __cdecl atoi(const char* str)",
        "cdecl",
        0,
        ("stack+4:str:cstr",),
        "eax:i32",
        "stdlib",
        "Jumps to 0x004e0ea6 -> strtol(str, NULL, 10); returns parsed 32-bit signed int in EAX.",
    ),
    0x004E0FE7: CrtSpec(
        "atof",
        "double __cdecl atof(const char* str)",
        "cdecl",
        0,
        ("stack+4:str:cstr",),
        "st0:f64",
        "stdlib",
        "Parses floating-point ASCII string and pushes double result onto x87 FPU stack (`ctx.fpu_push(val)`).",
    ),
    0x004E10AA: CrtSpec(
        "_get_crtheap",
        "HANDLE __cdecl _get_crtheap(void)",
        "cdecl",
        0,
        (),
        "eax:u32",
        "runtime",
        "Returns CRT heap handle [0x00553114] (must return non-zero handle in EAX; WinMain stores it in [0x0076e65c]).",
    ),
    0x004E1340: CrtSpec(
        "exit",
        "void __cdecl exit(int status)",
        "cdecl",
        0,
        ("stack+4:status:i32",),
        "void",
        "runtime",
        "Requests clean shutdown via hle_win32_post_quit(status) (do NOT abort host iOS app!).",
    ),
    0x004E13CC: CrtSpec(
        "realloc",
        "void* __cdecl realloc(void* ptr, size_t new_size)",
        "cdecl",
        0,
        ("stack+4:ptr:ptr", "stack+8:new_size:u32"),
        "eax:u32",
        "memory",
        "Resizes guest heap block via guest_realloc; returns new VA in EAX.",
    ),
    0x004E1660: CrtSpec(
        "strrchr",
        "const char* __cdecl strrchr(const char* str, int c)",
        "cdecl",
        0,
        ("stack+4:str:cstr", "stack+8:c:i32"),
        "eax:ptr",
        "string",
        "Finds last occurrence of `(uint8_t)c` (including NUL) in `str`; returns guest VA or 0.",
    ),
    0x004E18D3: CrtSpec(
        "wcstombs",
        "size_t __cdecl wcstombs(char* mbstr, const wchar_t* wcstr, size_t count)",
        "cdecl",
        0,
        ("stack+4:mbstr:ptr", "stack+8:wcstr:wstr", "stack+12:count:u32"),
        "eax:u32",
        "string",
        "Converts UTF-16LE `wcstr` to Shift-JIS/CP932 or ASCII multibyte string in `mbstr` up to `count` bytes; returns byte count (excluding NUL).",
    ),
    0x004E1900: CrtSpec(
        "strchr",
        "const char* __cdecl strchr(const char* str, int c)",
        "cdecl",
        0,
        ("stack+4:str:cstr", "stack+8:c:i32"),
        "eax:ptr",
        "string",
        "Finds first occurrence of `(uint8_t)c` (including NUL) in `str`; returns guest VA or 0.",
    ),
    0x004E1A12: CrtSpec(
        "isalnum",
        "int __cdecl isalnum(int c)",
        "cdecl",
        0,
        ("stack+4:c:i32",),
        "eax:i32",
        "ctype",
        "C-locale alphanumeric check (`std::isalnum((unsigned char)c)` or table mask 0x103); returns non-zero if alphanumeric, 0 otherwise.",
    ),
    0x004E1A8C: CrtSpec(
        "isdigit",
        "int __cdecl isdigit(int c)",
        "cdecl",
        0,
        ("stack+4:c:i32",),
        "eax:i32",
        "ctype",
        "C-locale decimal digit check ('0'..'9' -> non-zero 4, else 0).",
    ),
    0x004E1B09: CrtSpec(
        "isprint",
        "int __cdecl isprint(int c)",
        "cdecl",
        0,
        ("stack+4:c:i32",),
        "eax:i32",
        "ctype",
        "C-locale printable ASCII check (0x20..0x7E -> non-zero 0x80, else 0).",
    ),
    0x004E1C34: CrtSpec(
        "__ehvec_dtor",
        "void __stdcall __ehvec_dtor(void* ptr, size_t size, int count, void (__thiscall *dtor)(void*))",
        "stdcall",
        16,
        ("stack+4:ptr:ptr", "stack+8:size:u32", "stack+12:count:i32", "stack+16:dtor:va"),
        "void",
        "eh_rtti",
        "Calls `dtor` with ECX = ptr + i*size for i = count-1 down to 0 via call_indirect (pushing dummy return address before each dtor); ret 0x10.",
    ),
    0x004E1C97: CrtSpec(
        "__ehvec_ctor",
        "void __stdcall __ehvec_ctor(void* ptr, size_t size, int count, void (__thiscall *ctor)(void*), void (__thiscall *dtor)(void*))",
        "stdcall",
        20,
        ("stack+4:ptr:ptr", "stack+8:size:u32", "stack+12:count:i32", "stack+16:ctor:va", "stack+20:dtor:va"),
        "void",
        "eh_rtti",
        "Calls `ctor` with ECX = ptr + i*size for i = 0..count-1 via call_indirect (pushing dummy return address before each ctor); ret 0x14.",
    ),
    0x004E1CFC: CrtSpec(
        "_time64",
        "int64_t __cdecl _time64(int64_t* timer)",
        "cdecl",
        0,
        ("stack+4:timer:ptr",),
        "edx_eax:i64",
        "time",
        "Gets current Unix epoch seconds as 64-bit int, writes to `*timer` if non-null, returns low in EAX and high in EDX.",
    ),
    0x004E1D40: CrtSpec(
        "memchr",
        "const void* __cdecl memchr(const void* buf, int c, size_t count)",
        "cdecl",
        0,
        ("stack+4:buf:ptr", "stack+8:c:i32", "stack+12:count:u32"),
        "eax:ptr",
        "memory",
        "Scans `count` bytes at `buf` for `(uint8_t)c`; returns guest VA or 0.",
    ),
    0x004E1DED: CrtSpec(
        "_difftime64",
        "double __cdecl _difftime64(int64_t time1, int64_t time0)",
        "cdecl",
        0,
        ("stack+4:time1:i64", "stack+12:time0:i64"),
        "st0:f64",
        "time",
        "Computes `double(time1 - time0)` (if both >= 0) and pushes result onto x87 FPU stack (`ctx.fpu_push(diff)`).",
    ),
    0x004E1E2E: CrtSpec(
        "_endthreadex",
        "void __cdecl _endthreadex(unsigned retval)",
        "cdecl",
        0,
        ("stack+4:retval:u32",),
        "void",
        "thread",
        "Terminates current spawned guest worker thread cleanly (sets exit code).",
    ),
    0x004E1F28: CrtSpec(
        "_beginthreadex",
        "uintptr_t __cdecl _beginthreadex(void* security, unsigned stack_size, unsigned (__stdcall *start_address)(void*), void* arglist, unsigned initflag, unsigned* thrdaddr)",
        "cdecl",
        0,
        ("stack+4:security:ptr", "stack+8:stack_size:u32", "stack+12:start_address:va", "stack+16:arglist:ptr", "stack+20:initflag:u32", "stack+24:thrdaddr:ptr"),
        "eax:u32",
        "thread",
        "Spawns std::thread running guest `start_address(arglist)` with freshly allocated GuestMemory thread stack and CpuContext; returns synthetic thread HANDLE in EAX.",
    ),
    0x004E20DE: CrtSpec(
        "_stricmp",
        "int __cdecl _stricmp(const char* s1, const char* s2)",
        "cdecl",
        0,
        ("stack+4:s1:cstr", "stack+8:s2:cstr"),
        "eax:i32",
        "string",
        "ASCII case-insensitive string compare; returns <0, 0, or >0 in EAX.",
    ),
    0x004E21DF: CrtSpec(
        "_vsnprintf",
        "int __cdecl _vsnprintf(char* buf, size_t count, const char* fmt, va_list ap)",
        "cdecl",
        0,
        ("stack+4:buf:ptr", "stack+8:count:u32", "stack+12:fmt:cstr", "stack+16:ap:ptr"),
        "eax:i32",
        "stdio",
        "Formats `fmt` using guest `va_list` pointer `ap` into `buf` (up to `count` chars); returns written count or -1 if truncated.",
    ),
    0x004E2CA0: CrtSpec(
        "strftime",
        "size_t __cdecl strftime(char* str, size_t maxsize, const char* fmt, const struct tm* timeptr)",
        "cdecl",
        0,
        ("stack+4:str:ptr", "stack+8:maxsize:u32", "stack+12:fmt:cstr", "stack+16:timeptr:ptr"),
        "eax:u32",
        "time",
        "Formats 36-byte MSVC `struct tm` at `timeptr` (9 int32 fields: sec, min, hour, mday, mon, year, wday, yday, isdst) into `str`.",
    ),
    0x004E2CBD: CrtSpec(
        "remove",
        "int __cdecl remove(const char* path)",
        "cdecl",
        0,
        ("stack+4:path:cstr",),
        "eax:i32",
        "stdio",
        "Deletes file mapped case-insensitively inside BYOC assets dir; returns 0 on success or -1.",
    ),
    0x004E2D59: CrtSpec(
        "fclose",
        "int __cdecl fclose(FILE* stream)",
        "cdecl",
        0,
        ("stack+4:stream:ptr",),
        "eax:i32",
        "stdio",
        "Closes guest FILE* stream if tracked in HLE FILE table (e.g. from fopen), else safe no-op returning 0.",
    ),
    0x004E309A: CrtSpec(
        "_localtime32",
        "struct tm* __cdecl _localtime32(const int32_t* timep)",
        "cdecl",
        0,
        ("stack+4:timep:ptr",),
        "eax:ptr",
        "time",
        "Converts 32-bit Unix timestamp `*timep` to local time and writes 9 int32 fields into static/TLS guest `struct tm` buffer; returns buffer VA in EAX.",
    ),
    0x004E30BE: CrtSpec(
        "_snprintf",
        "int __cdecl _snprintf(char* buf, size_t count, const char* fmt, ...)",
        "cdecl",
        0,
        ("stack+4:buf:ptr", "stack+8:count:u32", "stack+12:fmt:cstr", "stack+16:varargs"),
        "eax:i32",
        "stdio",
        "Formats printf specifiers reading guest varargs from [esp+16..] into `buf` (max `count` bytes); returns chars written or -1.",
    ),
    0x004E325B: CrtSpec(
        "_strnicmp",
        "int __cdecl _strnicmp(const char* s1, const char* s2, size_t count)",
        "cdecl",
        0,
        ("stack+4:s1:cstr", "stack+8:s2:cstr", "stack+12:count:u32"),
        "eax:i32",
        "string",
        "ASCII case-insensitive compare up to `count` chars; returns <0, 0, or >0 in EAX.",
    ),
    0x004E3333: CrtSpec(
        "vsprintf",
        "int __cdecl vsprintf(char* buf, const char* fmt, va_list ap)",
        "cdecl",
        0,
        ("stack+4:buf:ptr", "stack+8:fmt:cstr", "stack+12:ap:ptr"),
        "eax:i32",
        "stdio",
        "Formats `fmt` using guest `va_list` pointer `ap` into `buf`; returns written length in EAX.",
    ),
    0x004E334A: CrtSpec(
        "_controlfp_s",
        "errno_t __cdecl _controlfp_s(unsigned int* currentControl, unsigned int newControl, unsigned int mask)",
        "cdecl",
        0,
        ("stack+4:currentControl:ptr", "stack+8:newControl:u32", "stack+12:mask:u32"),
        "eax:i32",
        "float",
        "Updates masked x87 rounding/precision bits in `ctx.fpu_cw` and writes previous/current control word to `*currentControl` if non-null; returns 0.",
    ),
    0x004E34E2: CrtSpec(
        "_clearfp",
        "unsigned int __cdecl _clearfp(void)",
        "cdecl",
        0,
        (),
        "eax:u32",
        "float",
        "Clears sticky exception bits (0..5, 7) in `ctx.fpu_sw` and returns prior exception status in EAX.",
    ),
    0x004E3B12: CrtSpec(
        "toupper",
        "int __cdecl toupper(int c)",
        "cdecl",
        0,
        ("stack+4:c:i32",),
        "eax:i32",
        "ctype",
        "ASCII 'a'..'z' -> 'A'..'Z' conversion; returns result in EAX.",
    ),
    0x004E3E1B: CrtSpec(
        "_CxxThrowException",
        "void __stdcall _CxxThrowException(void* pExceptionObject, const void* pThrowInfo)",
        "stdcall",
        8,
        ("stack+4:pExceptionObject:ptr", "stack+8:pThrowInfo:ptr"),
        "void",
        "eh_rtti",
        "Logs C++ exception throw (type info VA + object VA) and either unwinds via C++ exception or handles cleanly without crashing; ret 8.",
    ),
    0x004E422C: CrtSpec(
        "__EH_prolog3",
        "void __cdecl __EH_prolog3(void)",
        "custom_stack",
        0,
        ("eax:handler:va", "stack+4:frame_size:u32"),
        "void",
        "eh_rtti",
        "MSVC8 EH frame setup: caller pushes frame_size and sets EAX=handler; sets EBP=old_esp+4, saves old EBP at [EBP], [EBP-4]=-1, [EBP-8]=handler, [EBP-12]=old fs_0, fs_0=EBP-12, allocates frame_size + saved ebx/esi/edi + cookie, pops retaddr.",
    ),
    0x004E6340: CrtSpec(
        "memset",
        "void* __cdecl memset(void* dest, int c, size_t count)",
        "cdecl",
        0,
        ("stack+4:dest:ptr", "stack+8:c:i32", "stack+12:count:u32"),
        "eax:ptr",
        "memory",
        "Fills `count` bytes at `dest` with `(uint8_t)c`; returns `dest` in EAX.",
    ),
    0x004E63C0: CrtSpec(
        "memcpy",
        "void* __cdecl memcpy(void* dest, const void* src, size_t count)",
        "cdecl",
        0,
        ("stack+4:dest:ptr", "stack+8:src:ptr", "stack+12:count:u32"),
        "eax:ptr",
        "memory",
        "Copies `count` bytes from `src` to `dest` (uses memmove semantics to match VC8 overlap branch); returns `dest` in EAX.",
    ),
    0x004EAE60: CrtSpec(
        "_alldiv",
        "int64_t __stdcall _alldiv(int64_t a, int64_t b)",
        "stdcall",
        16,
        ("stack+4:a:i64", "stack+12:b:i64"),
        "edx_eax:i64",
        "int64",
        "Signed 64-bit division a / b (truncating toward zero); result in EDX:EAX; pops 16 bytes (ret 0x10).",
    ),
    0x004EAF10: CrtSpec(
        "_allrem",
        "int64_t __stdcall _allrem(int64_t a, int64_t b)",
        "stdcall",
        16,
        ("stack+4:a:i64", "stack+12:b:i64"),
        "edx_eax:i64",
        "int64",
        "Signed 64-bit remainder a % b; result in EDX:EAX; pops 16 bytes (ret 0x10).",
    ),
    0x004EDBA0: CrtSpec(
        "_allmul",
        "int64_t __stdcall _allmul(int64_t a, int64_t b)",
        "stdcall",
        16,
        ("stack+4:a:i64", "stack+12:b:i64"),
        "edx_eax:i64",
        "int64",
        "64-bit integer multiplication a * b; low 64 bits in EDX:EAX; pops 16 bytes (ret 0x10).",
    ),
    0x004EFAB0: CrtSpec(
        "__alloca_probe",
        "void __cdecl __chkstk(void)",
        "custom_stack",
        0,
        ("eax:size:u32",),
        "eax:u32",
        "stack",
        "Stack probe helper: pops retaddr into EAX, subtracts original EAX (`size`) from ESP (ESP = old_esp_after_ret - size), preserves ECX.",
    ),
    0x004F0A50: CrtSpec(
        "_alldvrm",
        "void __stdcall _alldvrm(int64_t a, int64_t b)",
        "stdcall",
        16,
        ("stack+4:a:i64", "stack+12:b:i64"),
        "edx_eax:quot_i64,ebx_ecx:rem_i64",
        "int64",
        "Signed 64-bit divmod: quotient (a / b) in EDX:EAX, remainder (a % b) in EBX:ECX; pops 16 bytes (ret 0x10).",
    ),
    0x004F1ECE: CrtSpec(
        "DirectSoundCreate8_thunk",
        "HRESULT __stdcall DirectSoundCreate8(LPCGUID pcGuidDevice, LPDIRECTSOUND8* ppDS8, LPUNKNOWN pUnkOuter)",
        "stdcall",
        12,
        ("stack+4:pcGuidDevice:ptr", "stack+8:ppDS8:ptr", "stack+12:pUnkOuter:ptr"),
        "eax:u32",
        "dsound_thunk",
        "Jumps through IAT 0x0051b008 (DSOUND.dll!ord_11); delegate directly to hle_iat_call(ctx, mem, 0x0051b008u).",
    ),
    0x004F3170: CrtSpec(
        "ov_clear",
        "int __cdecl ov_clear(OggVorbis_File* vf)",
        "cdecl",
        0,
        ("stack+4:vf:ptr",),
        "eax:i32",
        "vorbis",
        "Statically-linked libvorbisfile ov_clear(vf): closes Vorbis decoder handle associated with guest `vf` VA (calls close callback if open) and zeroes struct; returns 0.",
    ),
    0x004F32F0: CrtSpec(
        "ov_time_total",
        "double __cdecl ov_time_total(OggVorbis_File* vf, int i)",
        "cdecl",
        0,
        ("stack+4:vf:ptr", "stack+8:i:i32"),
        "st0:f64",
        "vorbis",
        "Statically-linked libvorbisfile ov_time_total(vf, i): returns total duration in seconds pushed onto x87 `st(0)` (`OV_EINVAL`=-131.0 on error).",
    ),
    0x004F41A0: CrtSpec(
        "ov_time_seek",
        "int __cdecl ov_time_seek(OggVorbis_File* vf, double pos)",
        "cdecl",
        0,
        ("stack+4:vf:ptr", "stack+8:pos:f64"),
        "eax:i32",
        "vorbis",
        "Statically-linked libvorbisfile ov_time_seek(vf, pos): seeks Vorbis stream to `pos` seconds; returns 0 on success.",
    ),
    0x004F4290: CrtSpec(
        "ov_info",
        "vorbis_info* __cdecl ov_info(OggVorbis_File* vf, int link)",
        "cdecl",
        0,
        ("stack+4:vf:ptr", "stack+8:link:i32"),
        "eax:ptr",
        "vorbis",
        "Statically-linked libvorbisfile ov_info(vf, link): returns guest VA of `vorbis_info` (version, channels@+4, rate@+8) inside/backing `vf`.",
    ),
    0x004F4620: CrtSpec(
        "ov_read",
        "long __cdecl ov_read(OggVorbis_File* vf, char* buffer, int length, int bigendianp, int word, int sgned, int* bitstream)",
        "cdecl",
        0,
        ("stack+4:vf:ptr", "stack+8:buffer:ptr", "stack+12:length:i32", "stack+16:bigendianp:i32", "stack+20:word:i32", "stack+24:sgned:i32", "stack+28:bitstream:ptr"),
        "eax:i32",
        "vorbis",
        "Statically-linked libvorbisfile ov_read(...): decodes up to `length` PCM bytes into guest `buffer`; returns byte count (>0), 0 on EOF, <0 on error.",
    ),
    0x004F49A0: CrtSpec(
        "ov_open_callbacks",
        "int __cdecl ov_open_callbacks(void* datasource, OggVorbis_File* vf, const char* initial, long ibytes, ov_callbacks callbacks)",
        "cdecl",
        0,
        ("stack+4:datasource:ptr", "stack+8:vf:ptr", "stack+12:initial:ptr", "stack+16:ibytes:i32", "stack+20:cb_read:va", "stack+24:cb_seek:va", "stack+28:cb_close:va", "stack+32:cb_tell:va"),
        "eax:i32",
        "vorbis",
        "Statically-linked libvorbisfile ov_open_callbacks(...): `ov_callbacks` is passed by value (4 guest fn ptrs at [esp+20..32]); reads Ogg stream via guest callbacks (`call_indirect`) into decoder state mapped to `vf`.",
    ),
    0x004F49F0: CrtSpec(
        "_ftol2_sse",
        "int64_t __cdecl _ftol2_sse(void)",
        "custom_x87",
        0,
        ("st0:f64",),
        "edx_eax:i64",
        "float",
        "Truncates `st(0)` toward zero (`cvttsd2si` / `fistp`), pops `st(0)`, writes 32-bit signed int to EAX (and sign-extended/64-bit EDX when outside int32).",
    ),
    0x004F4A26: CrtSpec(
        "_ftol2",
        "int64_t __cdecl _ftol2(void)",
        "custom_x87",
        0,
        ("st0:f64",),
        "edx_eax:i64",
        "float",
        "Truncates `st(0)` toward zero to 64-bit signed integer in EDX:EAX and pops `st(0)`.",
    ),
    0x0050E1D0: CrtSpec(
        "_CIatan",
        "void __cdecl _CIatan(void)",
        "custom_x87",
        0,
        ("st0:f64",),
        "st0:f64",
        "math",
        "MSVC CRT x87 intrinsic: replaces `st(0)` in-place with `std::atan(st(0))` (net x87 stack change 0).",
    ),
    0x0050E2B0: CrtSpec(
        "_CIsqrt",
        "void __cdecl _CIsqrt(void)",
        "custom_x87",
        0,
        ("st0:f64",),
        "st0:f64",
        "math",
        "MSVC CRT x87 intrinsic: replaces `st(0)` in-place with `std::sqrt(st(0))` (net x87 stack change 0).",
    ),
    0x0050E8D0: CrtSpec(
        "_CIpow",
        "void __cdecl _CIpow(void)",
        "custom_x87",
        0,
        ("st1:f64", "st0:f64"),
        "st0:f64",
        "math",
        "MSVC CRT x87 intrinsic: pops `exp = fpu_pop()`, reads `base = st(0)`, writes `std::pow(base, exp)` into new `st(0)` (net x87 stack pop 1).",
    ),
    0x0050EB60: CrtSpec(
        "_CIsin",
        "void __cdecl _CIsin(void)",
        "custom_x87",
        0,
        ("st0:f64",),
        "st0:f64",
        "math",
        "MSVC CRT x87 intrinsic: replaces `st(0)` in-place with `std::sin(st(0))` (net x87 stack change 0).",
    ),
    0x0050EC90: CrtSpec(
        "_CIcos",
        "void __cdecl _CIcos(void)",
        "custom_x87",
        0,
        ("st0:f64",),
        "st0:f64",
        "math",
        "MSVC CRT x87 intrinsic: replaces `st(0)` in-place with `std::cos(st(0))` (net x87 stack change 0).",
    ),
    0x0050EDC0: CrtSpec(
        "_CIacos",
        "void __cdecl _CIacos(void)",
        "custom_x87",
        0,
        ("st0:f64",),
        "st0:f64",
        "math",
        "MSVC CRT x87 intrinsic: replaces `st(0)` in-place with `std::acos(st(0))` (net x87 stack change 0).",
    ),
    0x00513030: CrtSpec(
        "_CItan",
        "void __cdecl _CItan(void)",
        "custom_x87",
        0,
        ("st0:f64",),
        "st0:f64",
        "math",
        "MSVC CRT x87 intrinsic: replaces `st(0)` in-place with `std::tan(st(0))` (net x87 stack change 0).",
    ),
}


def extract_crt_signatures(
    exe_path: Path = DEFAULT_MBAA_EXE,
    function_map_path: Path = DEFAULT_FUNCTION_MAP,
) -> dict[str, Any]:
    """Scan game .text calls to CRT VAs and return complete structured CRT signature map."""
    raw = exe_path.read_bytes()
    pe = pefile.PE(data=raw, fast_load=True)
    image_base = pe.OPTIONAL_HEADER.ImageBase

    text_sec = next(s for s in pe.sections if s.Name.rstrip(b"\x00") == b".text")
    text_va = image_base + text_sec.VirtualAddress
    text_size = text_sec.Misc_VirtualSize
    text_bytes = raw[text_sec.PointerToRawData : text_sec.PointerToRawData + text_size]

    fm = json.loads(function_map_path.read_text(encoding="utf-8"))
    funcs = {int(f["start_va"], 16): f for f in fm["functions"]}
    game_funcs = [f for va, f in sorted(funcs.items()) if va < MBAA_CRT_START_VA]

    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True

    call_sites: dict[int, list[str]] = {}
    for fn in game_funcs:
        sva = int(fn["start_va"], 16)
        eva = int(fn["end_va"], 16)
        chunk = text_bytes[sva - text_va : eva - text_va]
        for insn in md.disasm(chunk, sva):
            if insn.mnemonic in ("call", "jmp") and insn.operands:
                op0 = insn.operands[0]
                if op0.type == capstone.x86.X86_OP_IMM:
                    tgt = op0.imm & 0xFFFFFFFF
                    if MBAA_CRT_START_VA <= tgt < text_va + text_size:
                        call_sites.setdefault(tgt, []).append(f"0x{insn.address:08x}")

    discovered_vas = sorted(call_sites.keys())
    known_vas = sorted(CRT_SPECS.keys())
    if discovered_vas != known_vas:
        missing = [f"0x{v:08x}" for v in discovered_vas if v not in CRT_SPECS]
        extra = [f"0x{v:08x}" for v in known_vas if v not in call_sites]
        raise RuntimeError(f"CRT VA set mismatch: missing={missing}, extra={extra}")

    entries: list[dict[str, Any]] = []
    for va in discovered_vas:
        spec = CRT_SPECS[va]
        fn_meta = funcs.get(va, {})
        eva = int(fn_meta.get("end_va", hex(va + 64)), 16)
        span = max(32, min(256, eva - va))
        chunk = text_bytes[va - text_va : va - text_va + span]
        disasm_head = [
            f"0x{insn.address:08x}: {insn.mnemonic} {insn.op_str}".strip()
            for insn in list(md.disasm(chunk, va))[:10]
        ]

        spec_dict = asdict(spec)
        entries.append(
            {
                "va": f"0x{va:08x}",
                "va_int": va,
                "c_symbol": f"hle_crt_{va:08x}",
                "name": spec_dict["name"],
                "signature": spec_dict["signature"],
                "calling_convention": spec_dict["calling_convention"],
                "stack_cleanup": spec_dict["stack_cleanup"],
                "ret_pop_total": 4 + spec_dict["stack_cleanup"],
                "params": list(spec_dict["params"]),
                "returns": spec_dict["returns"],
                "category": spec_dict["category"],
                "game_call_sites": len(call_sites[va]),
                "sample_call_sites": call_sites[va][:5],
                "disasm_head": disasm_head,
                "notes": spec_dict["notes"],
            }
        )

    return {
        "schema_version": 1,
        "artifact": {
            "path": str(exe_path),
            "sha256": hashlib.sha256(raw).hexdigest(),
            "crt_start_va": f"0x{MBAA_CRT_START_VA:08x}",
        },
        "calling_contract": {
            "entry_stack": "[esp+0] holds 32-bit return address pushed by caller; [esp+4] is first stack arg.",
            "exit_stack": "Each hle_crt_00XXXXXX MUST pop the 4-byte return address (ctx.ret_cdecl(mem)) plus `stack_cleanup` bytes (ctx.ret_stdcall(mem, stack_cleanup)), EXCEPT custom_stack (__EH_prolog3 / __chkstk).",
            "dispatch_signature": "void hle_crt_00XXXXXX(CpuContext& ctx, GuestMemory& mem);",
        },
        "count": len(entries),
        "functions": entries,
    }


def write_crt_signatures(
    exe_path: Path = DEFAULT_MBAA_EXE,
    function_map_path: Path = DEFAULT_FUNCTION_MAP,
    output_path: Path = DEFAULT_OUTPUT_JSON,
) -> dict[str, Any]:
    data = extract_crt_signatures(exe_path, function_map_path)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_text(json.dumps(data, indent=2) + "\n", encoding="utf-8")
    return data


def main() -> None:
    parser = argparse.ArgumentParser(description="Extract MBAA.exe CRT signatures to JSON.")
    parser.add_argument("--exe", type=Path, default=DEFAULT_MBAA_EXE)
    parser.add_argument("--function-map", type=Path, default=DEFAULT_FUNCTION_MAP)
    parser.add_argument("--out", type=Path, default=DEFAULT_OUTPUT_JSON)
    args = parser.parse_args()
    data = write_crt_signatures(args.exe, args.function_map, args.out)
    print(f"Wrote {data['count']} CRT signatures to {args.out}")


if __name__ == "__main__":
    main()
