# Melty Blood: Actress Again Current Code (MBAACC) — iOS / iPadOS

A **Native ARM64 (Static AOT Recompilation + Apple Metal)** port of *Melty Blood Actress Again Current Code* for **iPhone & iPad**, running at full **60 FPS** with **no Jailbreak** and **no JIT** required.

> **BYOC (Bring Your Own Copy) Notice:**  
> This repository and `.ipa` file **do not contain any copyrighted game assets**. After installing the app, you must copy your own legal PC installation of MBAACC onto your iPhone/iPad.

---

## Features

- **Native ARM64 + Apple Metal at 60 FPS:** Compiled AOT to ARM64 machine code — requires **zero JIT (`dynamic-codesigning`) entitlements**, compatible with all standard iOS sideloading tools.
- **All 56 Stages Unlocked (CCCaster Parity):** Includes all hidden Training and Versus stages normally locked in vanilla (`...and nothing heart`, `G TABLE`, `Random Select.`, `Artificial Eden`, etc.).
- **Title Screen & VS Video Playback:** Built-in MPEG-1 video decoder for `dat_m_ttl.d` and `dat_m_vs.d`.
- **Full Story & Win-Quote Text Support:** Preserves English patch fonts (`0008.p`) while automatically merging Japanese glyphs (`0004.p`) for untranslated Shift-JIS dialogue and win-quote scripts.
- **AetherSX2-Style PS2 Touch Overlay + Bluetooth/MFi Controllers:** Smooth 8-way fighting-game D-Pad (`236`, `623`, `214`, IAD), adjustable opacity / hide toggle (`PAD`), and automatic touch fade-out when a physical `GCController` connects.

---

## Requirements

| Requirement | Details |
| --- | --- |
| **OS Version** | **iOS 15.0 / iPadOS 15.0 or later** (`arm64` + Metal) |
| **Supported Devices** | **iPhone** (iPhone 6s / SE 2020 or newer; **3 GB RAM+ recommended** such as iPhone X / XR / SE 2020 / 11–16 series) and **iPad** on iPadOS 15+ |
| **Jailbreak / JIT** | **Not required** |
| **Game Files** | Legal PC copy of **MBAACC** (`MBAA.exe`, `0000.p` – `0008.p`, `System/`, `dat/`, `Information/`) |

---

## Step 1: Download the `.ipa`

1. Open the main page of this GitHub repository.
2. Click **`MBAACC_1.0.7_1795712332.ipa`**, then click **Download raw file** (top-right download button) to save it to your PC or iPhone/iPad.

*(The included **`manifest.plist`** supports OTA installation via `itms-services://` if the `.ipa` is signed with a valid Enterprise or Developer certificate.)*

---

## Step 2: Install on iPhone / iPad

Use **any one** of the following sideloading methods (**no JIT needed** — simply sign and install):

### Option A: Install directly on iPhone with **ESign** (Recommended)
1. Open **ESign** -> **Import** `MBAACC_1.0.7_1795712332.ipa`.
2. Tap the imported app under **Apps** -> **Sign** with your certificate -> tap **Sign** -> **Install**.
3. If this is your first time using that certificate, go to **iOS Settings -> General -> VPN & Device Management** and **Trust** the developer certificate.

### Option B: Install with **AltStore / SideStore / Sideloadly**
- Open AltStore, SideStore, or Sideloadly, select `MBAACC_1.0.7_1795712332.ipa`, and install with your Apple ID (JIT is not needed).

### Option C: Install with **TrollStore** (if supported)
- Share `MBAACC_1.0.7_1795712332.ipa` directly to **TrollStore** and tap **Install**.

---

## Step 3: Copy PC Game Files to iPhone / iPad (Required)

1. Launch **MBAACC** on your iPhone/iPad at least **once** so it creates its Documents folder and opens the BYOC asset checker screen.
2. From your PC **MBAACC** folder, prepare the following files and folders:

```text
MBAACC/
├── MBAA.exe          (required)
├── 0000.p            (required)
├── 0001.p            (required)
├── 0002.p            (required)
├── 0003.p            (required)
├── 0004.p            (required)
├── 0005.p            (required)
├── 0006.p            (required)
├── 0007.p            (required)
├── 0008.p            (required)
├── System/           (recommended - system config)
├── Information/      (recommended - dialogue / info data)
├── dat/              (recommended - dat_m_ttl.d & dat_m_vs.d for Title/VS videos)
├── GRP/              (optional, if present in your PC install)
└── Movie/            (optional, if present in your PC install)
```

3. Transfer them using **either** method:
   - **On iPhone/iPad (Files app):**  
     Send/extract the files via AirDrop, iCloud Drive, or SMB and move everything into:  
     **`Files -> On My iPhone -> MBAACC -> MBAACC/`**
   - **Over USB via Windows (iTunes / Apple Devices) or macOS (Finder):**  
     Select your device -> **File Sharing -> MBAACC** -> drop the files/folders into **`MBAACC/`** (or directly into the app's root `Documents/` folder as a fallback).
4. Return to the **MBAACC** app and tap **`Kiểm tra lại / Re-scan Documents/MBAACC/`**. Once every required file shows **`[OK]`**, the game boots automatically.

---

## Step 4: Controls (PS2 Layout)

| On-Screen Control | Game Action | Notes |
| --- | --- | --- |
| **D-Pad (Left)** | 8-Way Movement | Supports smooth touch sliding (`236`, `623`, `214`, IAD) |
| **`□` (Square)** | **A** — Light Attack / Menu Confirm | Official Melty Blood PS2 layout |
| **`×` (Cross)** | **B** — Medium Attack / Menu Cancel | Official Melty Blood PS2 layout |
| **`○` (Circle)** | **C** — Heavy Attack | Official Melty Blood PS2 layout |
| **`△` (Triangle)** | **D** — Shield / Parry | Official Melty Blood PS2 layout |
| **`L1`** | **A + D** — Throw / Dodge Macro | PS2 shoulder shortcut |
| **`L2`** | **A + B + C** — Heat / Blood Heat Macro | PS2 shoulder shortcut |
| **`R1`** | **E** — Quick Action | Dedicated MBAACC 5th button |
| **`R2`** | **A + B** — Dash / Quick Evade Macro | PS2 shoulder shortcut |
| **`▭` (Select)** | **FN1** — Training Position Reset | Unbound to system keys |
| **`◎` (Double-Ring)** | **FN2** — Training Function 2 / Dummy Record | Training Mode utility |
| **`▷` (Start)** | **Pause Menu** — In-Game Pause | Opens MBAACC pause menu |
| **`\|\|` (Top-Right)** | **iOS Pause & Debug Overlay** | Includes *Trim GPU Memory Cache* |
| **`PAD` (Top-Left)** | **Touch Opacity / Hide Virtual Pad** | Preferences persist across launches |

- **Bluetooth / MFi Controllers (DualSense, DualShock 4, Xbox, Backbone, etc.):** Automatically supported with the same PS2 button layout above; the virtual overlay fades out automatically when a controller connects.

---

## Troubleshooting

- **Onboarding screen shows `[MISSING]` for `.p` files or `MBAA.exe`:**  
  Verify files are placed directly inside `On My iPhone -> MBAACC -> MBAACC/` (avoid an extra nested `MBAACC/` subfolder) and tap *Re-scan*.
- **"Untrusted Developer" prompt on iOS:**  
  Open **Settings -> General -> VPN & Device Management**, select the signing certificate, and tap **Trust**.
- **Black Title Screen (only `Rev.1.4.0` is visible):**  
  Make sure you copied the `dat/` folder containing `dat_m_ttl.d` and `dat_m_vs.d` into `MBAACC/dat/`.
- **Stuttering or crashes on 2–3 GB RAM devices after long sessions:**  
  Tap **`||`** in the top-right corner and press **`Trim GPU Memory Cache`** to evict cached Metal textures.

---

## Disclaimer

This project distributes only the AOT runtime and platform bridge; **no copyrighted game binaries, archives, scripts, audio, or video assets** from **TYPE-MOON / ECOLE / FRENCH-BREAD / ARC SYSTEM WORKS** are included. A legal PC copy of the game is required.
