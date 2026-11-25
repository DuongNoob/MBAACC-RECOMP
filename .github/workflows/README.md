# mbaacc-recomp-ios — Static x86-32 → C++20 AOT Recompilation of MBAACC for iOS (iPhone SE 2020)

> **Honest Build & Verification Boundary:**  
> This repository is authored and verified up to the Python/Unicorn static-lifting stage on a **Windows host with no local C/C++ or Apple Xcode toolchain**. The Python x86-32 → C++20 recompiler (`recompiler/`), DX9 `.cfx` disassembler, and IR differential verification against Unicorn Engine execute on Windows; **final compilation of the C++20 runtime, generated `build_gen/*.cpp`, Objective-C++ HLE bridges, and Metal shaders into an ARM64 `.ipa` must be performed on macOS with Xcode and `xcodegen`.**

---

## 1. Architecture Overview

`mbaacc-recomp-ios` statically recompiles the PC version of *Melty Blood Actress Again Current Code* (`MBAA.exe`, PE32 x86, MSVC8 / `MBAA-RING`) into **Ahead-of-Time (AOT) native C++20**, paired with an Apple Metal graphics backend and iOS High-Level Emulation (HLE) runtime tailored for **iPhone SE (2nd generation, 2020)**.

Because the lifted game logic compiles directly to native **ARM64 machine code**, **zero JIT (`dynamic-codesigning`) entitlements are required**. The resulting `.ipa` runs natively under standard iOS App Sandbox via Xcode, AltStore, or SideStore.

### Provenance Baseline (from [`../mbaacc-src/`](../mbaacc-src/))

- **Target binary:** `MBAA.exe` (`1,404,928` bytes, SHA-256 `6d1415ca9573100e86a779ac2f81e9bedd322664e3daeae0229a67d13720310a`)
- **PE32 Layout:** `ImageBase = 0x00400000`, `EntryPoint = 0x004E3D7E`, 5 sections (`.text`, `.rdata`, `.data`, `.rsrc`, and English translation section `.new00`)
- **Disassembly Map:** `4,777` total functions (`3,570` game functions in `0x00401000..0x004E00CF` + `1,207` MSVC8 CRT functions starting at `0x004E00D0`), `192` RTTI `TypeDescriptor`s, `190` vtables (`1,660` method slots), `1,657` switch jump tables, `292` SafeSEH handlers, `247` IAT imports across `13` DLLs (`184` referenced directly from game `.text`)
- **FilePac VFS:** `9` archives (`0008.p`, `0003.p`, `0005.p`, `0002.p`, `0007.p`, `0000.p`, `0004.p`, `0006.p`, `0001.p`), `93` directories, `11,420` raw file entries (`11,058` unique VFS entries)
- **Rollback State Table:** `24` deterministic `.data` memory regions (`252` bytes total) identified from `cccaster/hook.dll`

---

## 2. Target Hardware Design — iPhone SE (2020)

| Specification | iPhone SE 2020 Hardware | Design Decision in `mbaacc-recomp-ios` |
| --- | --- | --- |
| **SoC / CPU** | Apple A13 Bionic (ARM64, 6-core) | Pure AOT C++20 (`-O2`, zero JIT, zero dynamic code pages) |
| **RAM** | 3 GB LPDDR4X | 128 MiB guest heap arena (`GuestMemory`) + 192 MiB LRU Metal texture cache + `didReceiveMemoryWarning` -> `RuntimeEngine::handle_memory_warning()` |
| **Display** | 4.7" IPS LCD (`1334 × 750` px @ 2x, `667 × 375` pt, 16:9), 60 Hz | `MTKView` locked to `preferredFramesPerSecond = 60` (`BGRA8Unorm`); centered 4:3 (`1000 × 750` px) game viewport leaving `167 px` (`83.5 pt`) sidebars on left and right |
| **GPU / Textures** | Apple GPU (no hardware S3TC/DXT1–5) | Software DXT1–DXT5 decoder (`bcdec_dxt.cpp`) -> `MTLPixelFormatRGBA8Unorm` + `mbaa_shaders.metal` replacing DX9 fixed-function & `.cfx` (`ps_2_0`/`vs_2_0`) pipelines |
| **Controls** | Multi-touch + MFi / Bluetooth `GCController` | Ergonomic 8-way virtual D-pad + Start/Coin/Pause (left sidebar) + A/B/C/D/E + Dash (`A+B`) / Heat (`A+B+C`) / FN1 / FN2 (right sidebar) with opacity slider and automatic fade when a `GCController` connects |
| **Storage / BYOC** | iOS App Sandbox (`Documents/`) | `UIFileSharingEnabled = YES` & `LSSupportsOpeningDocumentsInPlace = YES` for Files/Finder transfer of user-owned `MBAA.exe` + `0000.p..0008.p` |

---

## 3. Repository Layout

| Path | Role |
| --- | --- |
| [`recompiler/`](recompiler/) | Python 3.12 static x86-32 → C++20 lifter (`cfg.py`, `crt_map.py`, `ir.py`, `x86_lifter.py`, `ir_eval.py`, `cpp_emitter.py`, `cli.py`) & DX9 `.cfx` shader disassembler (`cfx_disasm.py`) |
| [`runtime/`](runtime/) | C++20 / Objective-C++ runtime: `GuestMemory`, `CpuContext`, indirect dispatch, CRT/Win32/DirectShow/Input/Audio/Metal D3D9 HLE shims, software DXT1–5 decoder, 24-region rollback hooks |
| [`ios/App/`](ios/App/) | iOS UIKit / `MTKView` 60 Hz application shell, BYOC `Documents/MBAACC/` asset checker & bilingual onboarding screen, `TouchOverlayView`, `Info.plist`, `MBAACCRecomp.entitlements` |
| [`ios/Shaders/`](ios/Shaders/) | Apple Metal shading library (`mbaa_shaders.metal`), `shader_manifest.h`, and `cfx_analysis.json` |
| [`ios/project.yml`](ios/project.yml) | XcodeGen specification generating `MBAACCRecomp.xcodeproj` (iOS 15.0+, `arm64`, zero JIT) |
| [`ios/build_unsigned_ipa.sh`](ios/build_unsigned_ipa.sh) | Headless macOS script producing `dist/MBAACC-unsigned.ipa` ready for ESign (no code signing required) |
| [`.github/workflows/build-ios-ipa.yml`](.github/workflows/build-ios-ipa.yml) | GitHub Actions `macos-15` manual workflow (`workflow_dispatch`) building the unsigned `.ipa` without needing a local Mac |
| [`CMakeLists.txt`](CMakeLists.txt) | Dual-platform CMake build for `mbaa_runtime`, generated `mbaa_recomp_gen`, and iOS bundle |
| [`build_gen/`](build_gen/) | *(Git-ignored)* Sharded C++20 files (`gen_*.cpp`, `recomp_funcs.h`, `iat_table.h`) emitted locally by `recompiler` |
| [`IOS_BUILD_GUIDE.md`](IOS_BUILD_GUIDE.md) | Step-by-step Vietnamese & English guide: code generation, macOS XcodeGen/CMake build, sideloading without JIT, and BYOC file transfer |

---

## 4. Quick Start Workflow

1. **Generate C++20 sources (`build_gen/`) on Windows or macOS** (requires Python 3.12 + `pefile`, `capstone`, `unicorn`, and your legal `MBAA.exe`):
   - See [`IOS_BUILD_GUIDE.md`](IOS_BUILD_GUIDE.md) for exact `recompiler` CLI commands.
2. **Build `MBAACC-unsigned.ipa` on GitHub Actions `macos-15` (if you have no Mac)** — push to a **Private** GitHub repo (including `build_gen/`) and run **Actions → Build iOS Unsigned IPA (ESign)**, or on macOS run:
   ```bash
   bash ios/build_unsigned_ipa.sh
   # or interactively:
   cd ios && xcodegen generate && open MBAACCRecomp.xcodeproj
   ```
3. **Sign & install on iPhone SE 2020** via **ESign** (with your iOS cert), Xcode, AltStore, or SideStore — no JIT needed.
4. **Copy BYOC game files** (`MBAA.exe`, `0000.p` .. `0008.p`, `System/`, `Information/`) into **On My iPhone → MBAACC → MBAACC/** via iOS Files or macOS Finder.

---

## 5. BYOC & Clean-Room Policy

- **Zero copyrighted assets** (`MBAA.exe`, `*.p`, `*.dat`, `.ha6`, `.cg`, `.pal`, `.dds`, `.ogg`, `.wav`, videos) are stored in or distributed with this repository.
- **Zero DRM bypass or unpacking:** `reg.dll` (`sarcheck`) and `0000.dat` are never unpacked, spoofed, or circumvented; `LoadLibraryA` cleanly returns `NULL` for unshimmed external DLLs.
