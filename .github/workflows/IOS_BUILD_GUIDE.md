# Hướng dẫn Build & Sideload `mbaacc-recomp-ios` cho iPhone SE 2020 (Zero JIT)

Tài liệu này hướng dẫn từng bước để sinh mã C++20 AOT từ tệp `MBAA.exe` hợp pháp của bạn, biên dịch ứng dụng iOS ARM64 + Metal trên macOS bằng **XcodeGen / Xcode** (hoặc **CMake**), cài đặt lên **iPhone SE (2020)** mà **không cần JIT**, và chép dữ liệu trò chơi theo cơ chế **BYOC (Bring Your Own Copy)**.

---

## 1. Kiến trúc & Ranh giới Xác minh (Honest Verification Boundary)

- **Giai đoạn đã chạy & kiểm chứng trên Windows:**
  - Phân tích nhị phân tĩnh `MBAA.exe` (`4,777` hàm: `3,570` hàm game + `1,207` hàm CRT), hệ thống `192` RTTI `TypeDescriptor` / `190` VTable, `247` IAT imports và `24` vùng bộ nhớ rollback (`252` bytes) được trích xuất trong [`../mbaacc-src/`](../mbaacc-src/).
  - Bộ dịch ngược tĩnh Python (`recompiler/`) nâng mã x86-32 sang IR và sinh mã C++20 vào thư mục `build_gen/`, đồng thời đối chiếu vi mô với **Unicorn Engine (`UC_ARCH_X86`, `UC_MODE_32`)** trên các hàm thực tế của `MBAA.exe`.
  - Bộ giải mã `.cfx` (`recompiler/cfx_disasm.py`) phân tích 9 shader DX9 trong `0006.p` hoàn toàn trong bộ nhớ để tạo `ios/Shaders/cfx_analysis.json` và chuyển thể sang `ios/Shaders/mbaa_shaders.metal`.
- **Giai đoạn cần macOS + Xcode:**
  - Máy chủ Windows không cài trình biên dịch C/C++ hay Xcode SDK. Do đó, bước biên dịch mã C++20 (`build_gen/*.cpp` + `runtime/src/*.cpp/*.mm`), biên dịch `.metal` và ký `.ipa` cho iPhone SE 2020 (`arm64`, iOS 15.0+) **bắt buộc thực hiện trên máy macOS có Xcode**.

---

## 2. Yêu cầu chuẩn bị

### Phần mềm & Phần cứng
1. **Bản cài đặt PC hợp pháp của `MBAACC`** (chứa `MBAA.exe`, `0000.p` .. `0008.p`, `System/`, `Information/`, v.v.).
2. **Bước sinh mã (`recompiler/` — chạy trên Windows hoặc macOS):**
   - Python **3.12+**
   - Các thư viện Python: `pefile`, `capstone`, `unicorn`
3. **Bước biên dịch iOS (chỉ chạy trên macOS):**
   - **macOS** với **Xcode 14+** (iOS 15.0+ SDK)
   - **XcodeGen** (`brew install xcodegen`)
   - Hoặc **CMake 3.22+** (`brew install cmake`)
4. **Thiết bị đích:**
   - **iPhone SE (thế hệ 2 — 2020)** chạy **iOS 15.0 trở lên** (chip A13 Bionic `arm64`, RAM 3 GB, màn hình `1334×750` 60 Hz).
   - Cáp Lightning/USB để cài qua Xcode hoặc sử dụng **AltStore / SideStore** (không cần jailbreak, không cần kích hoạt JIT).

---

## 3. Bước 1 — Sinh mã nguồn C++20 (`build_gen/`)

> **Lưu ý BYOC:** Thư mục `build_gen/` nằm trong `.gitignore` và **không** được commit lên git vì chứa mã máy được nâng từ tệp `MBAA.exe` của người dùng.

Từ thư mục gốc `mbaacc-recomp-ios/`, chạy bộ recompiler Python (trỏ tới tệp `MBAA.exe` và `function_map.json` / `rtti_vtables.json`):

```powershell
# Trên Windows (hoặc python3 trên macOS)
py -m recompiler.cli --help
```

Sau khi chạy xong lệnh sinh mã vào `build_gen/`, kiểm tra thấy các tệp sau đã được tạo:
- `build_gen/recomp_funcs.h`
- `build_gen/iat_table.h`
- `build_gen/gen_core.cpp`, `gen_filepac.cpp`, `gen_dxtools.cpp`, `gen_scene.cpp`, `gen_game_engine.cpp`, `gen_chara.cpp`, `gen_menu.cpp`, `gen_replay.cpp`, `gen_input.cpp`, `gen_sound.cpp`, `gen_netvs.cpp`, `gen_dispatch.cpp`
- `build_gen/gen_manifest.json`

---

## 4. Bước 2 — Tạo file `MBAACC-unsigned.ipa` (Không cần máy Mac hoặc Có máy Mac)

### Phương án 1 (Khuyên dùng khi bạn chỉ có Windows): Build `.ipa` miễn phí qua GitHub Actions (`macos-15`) để ký bằng ESign

> **Quan trọng về BYOC:** Vì `build_gen/` chứa mã C++20 nâng từ tệp `MBAA.exe` của bạn, hãy luôn tạo GitHub repository ở chế độ **Private** (Riêng tư). Mặc định `.gitignore` cũng chặn `build_gen/` để tránh lộ công khai nhầm. **Tuyệt đối không upload `MBAA.exe` hay `0000.p..0008.p` lên GitHub** — chúng ta sẽ chép chúng thẳng vào iPhone ở Bước 4.

1. Tạo một repository mới trên GitHub với quyền **Private**.
2. Đưa mã nguồn `mbaacc-recomp-ios/` (bao gồm thư mục `build_gen/` đã sinh sẵn) lên Private repo đó theo 1 trong 2 cách:
   - **Cách A — Dùng GitHub Desktop / Git CLI (nhanh và ổn định nhất):**
     - Mở GitHub Desktop (hoặc Git Bash/PowerShell sau khi cài Git for Windows) tại thư mục `mbaacc-recomp-ios/`.
     - Ép thêm `build_gen/` vào Private repo (vì `.gitignore` đang ẩn thư mục này):
       ```powershell
       git init
       git add .
       git add -f build_gen/
       git commit -m "Initial private MBAACC iOS recomp project"
       git branch -M main
       git remote add origin https://github.com/<USERNAME>/<PRIVATE_REPO>.git
       git push -u origin main
       ```
     - *(Nếu dùng GitHub Desktop giao diện: trước khi commit bạn có thể tạm chuyển `build_gen/` vào git bằng lệnh `git add -f build_gen/` một lần duy nhất, hoặc giữ nguyên `.gitignore` và nén `build_gen/` thành `build_gen.zip` rồi truyền URL trực tiếp qua ô `build_gen_zip_url` khi chạy Workflow.)*
   - **Cách B — Upload qua trình duyệt (nếu không cài Git):**
     - GitHub web cho phép upload tệp tối đa `25 MB/tệp` (`gen_game_engine.cpp` là tệp lớn nhất `14.05 MiB` / `14,731,660 bytes`, toàn bộ dự án gồm `70` tệp tổng cộng `46.61 MiB`, hoàn toàn vừa giới hạn).
     - Trước hết bấm **Add file → Create new file**, đặt tên `.github/workflows/build-ios-ipa.yml` và dán nội dung từ tệp `.github/workflows/build-ios-ipa.yml` vào (vì kéo thả trên web đôi khi bỏ qua thư mục bắt đầu bằng dấu `.` như `.github`). Tương tự cho `.gitignore`.
     - Sau đó bấm **Add file → Upload files** và kéo thả toàn bộ các thư mục `ios/`, `runtime/`, `recompiler/`, `build_gen/`, `tests/` và các tệp gốc (`CMakeLists.txt`, `README.md`, `IOS_BUILD_GUIDE.md`) rồi bấm **Commit changes**.
3. Chạy trình biên dịch đám mây Apple Silicon (`macos-15` + Xcode + XcodeGen):
   - Vào tab **Actions** trên GitHub repo → chọn workflow **`Build iOS Unsigned IPA (ESign)`** → bấm **Run workflow** → giữ `Release` → **Run workflow**.
   - Runner sẽ chạy `ios/build_unsigned_ipa.sh` để biên dịch toàn bộ C++20/Obj-C++ + `mbaa_shaders.metal` thành `MBAACC.app` (ARM64, **không ký**) và đóng gói thành `dist/MBAACC-unsigned.ipa`.
4. Tải `.ipa` và ký bằng **ESign** trên iPhone SE 2020:
   - Khi workflow hoàn tất (tích xanh), kéo xuống mục **Artifacts** ở trang run đó và tải **`MBAACC-unsigned-ipa`**.
   - Giải nén tệp zip tải về để lấy **`MBAACC-unsigned.ipa`** rồi gửi sang iPhone (AirDrop, Telegram/Cloud, iCloud Drive, SMB…).
   - Mở **ESign** → **Nhập (Import)** `MBAACC-unsigned.ipa` → **Ký (Sign)** bằng chứng chỉ của bạn (không cần bật hay thêm bất kỳ quyền JIT nào) → **Cài đặt (Install)**.
   - *(Mẹo debug: nếu lần đầu chạy trên Xcode gặp lỗi biên dịch do mã C++/Obj-C++ chưa từng test trên Clang thật, hãy tải artifact **`xcodebuild-log`** trong trang workflow và gửi lại nội dung log để sửa ngay.)*

---

### Phương án 2 (Nếu bạn có máy Mac): Tạo dự án Xcode & Build cục bộ

Chuyển toàn bộ thư mục `mbaacc-recomp-ios/` (kèm `build_gen/` vừa sinh) sang máy macOS.

#### Cách 2A: Chạy script tạo Unsigned IPA nhanh cho ESign
```bash
cd mbaacc-recomp-ios
chmod +x ios/build_unsigned_ipa.sh
bash ios/build_unsigned_ipa.sh
# Kết quả: dist/MBAACC-unsigned.ipa
```

#### Cách 2B: Dùng XcodeGen mở trực tiếp trong Xcode GUI

```bash
# Cài XcodeGen nếu chưa có
brew install xcodegen

# Tạo MBAACCRecomp.xcodeproj từ ios/project.yml
cd mbaacc-recomp-ios/ios
xcodegen generate

# Mở bằng Xcode
open MBAACCRecomp.xcodeproj
```

Trong Xcode:
1. Chọn target **`MBAACCRecomp`** → tab **Signing & Capabilities**.
2. Chọn **Team** (Apple ID cá nhân miễn phí hoặc tài khoản Apple Developer trả phí) và đổi **Bundle Identifier** nếu dùng tài khoản miễn phí (ví dụ: `com.yourname.mbaacc.recomp`).
3. **Không cần thêm JIT hay `dynamic-codesigning` entitlement** (`ios/App/MBAACCRecomp.entitlements` đã cấu hình chuẩn AOT).
4. Chọn thiết bị **iPhone SE (2nd generation)** hoặc **Any iOS Device (arm64)** → nhấn **Product → Run (`Cmd+R`)** hoặc **Product → Archive** để xuất tệp `.ipa`.

#### Cách 2C: Dùng CMake (Xây dựng thư viện `mbaa_runtime` / kiểm tra biên dịch)

- Để kiểm thử biên dịch riêng lớp runtime C++20 (không cần `build_gen/`):
  ```bash
  cmake -S . -B build -DMBAA_BUILD_RECOMP_APP=OFF
  cmake --build build -j
  ```
- Để cấu hình iOS bundle qua CMake + Xcode generator (khi đã có `build_gen/`):
  ```bash
  cmake -S . -B build-ios -G Xcode \
    -DCMAKE_SYSTEM_NAME=iOS \
    -DCMAKE_OSX_ARCHITECTURES=arm64 \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=15.0 \
    -DMBAA_BUILD_RECOMP_APP=ON
  ```

---

## 5. Bước 3 — Sideload lên iPhone SE 2020 (Zero JIT)

Vì ứng dụng biên dịch 100% sang **native ARM64 AOT**, bạn có thể cài bằng bất kỳ công cụ ký `.ipa` thông thường nào:

1. **Qua ESign trực tiếp trên iPhone (khuyên dùng nếu build từ GitHub Actions):**
   - Tải artifact `MBAACC-unsigned-ipa` → giải nén lấy `MBAACC-unsigned.ipa`.
   - Trong app **ESign**, nhấn Import → giải nén/thêm vào Kho ứng dụng → chọn **Chữ ký (Sign)** với chứng chỉ đang hoạt động trên máy → nhấn **Cài đặt (Install)** (**không** bật JIT).
2. **Qua Xcode trực tiếp:** Kết nối iPhone SE 2020 với Mac qua cáp → Trust máy tính → nhấn Run (`Cmd+R`).
3. **Qua AltStore / SideStore:**
   - Xuất tệp `.ipa` từ Xcode (`Product → Archive → Distribute App → Debugging / Development` hoặc dùng `MBAACC-unsigned.ipa`).
   - Gửi `.ipa` sang iPhone → mở bằng **AltStore** hoặc **SideStore** để cài đặt.
   - **Quan trọng:** Không cần bật *"Enable JIT"* trong AltStore/SideStore mỗi lần mở game! Mở biểu tượng **MBAACC** trực tiếp từ màn hình chính.

---

## 6. Bước 4 — Chép tệp Game BYOC vào iPhone SE 2020

`Info.plist` đã bật `UIFileSharingEnabled = YES` và `LSSupportsOpeningDocumentsInPlace = YES`. Ngay lần mở đầu tiên, ứng dụng tự tạo thư mục `Documents/MBAACC/` và hiển thị màn hình hướng dẫn kiểm tra tệp nếu chưa có dữ liệu.

### Cách 1: Dùng ứng dụng Tệp (Files) trên iPhone
1. Mở app **Tệp (Files)** → **Trên iPhone của tôi (On My iPhone)** → thư mục **MBAACC** → **MBAACC**.
2. Chép từ PC (qua AirDrop, iCloud Drive, hoặc ổ USB/SMB) các mục sau vào thư mục đó:
   - **Bắt buộc:** `MBAA.exe`, `0000.p`, `0001.p`, `0002.p`, `0003.p`, `0004.p`, `0005.p`, `0006.p`, `0007.p`, `0008.p`
   - **Khuyên dùng (đầy đủ UI/save/bg):** `System/`, `Information/`, `GRP/`, `dat/`, `Movie/`
3. Quay lại app **MBAACC** và bấm **"Kiểm tra lại / Re-scan Documents/MBAACC/"**.

### Cách 2: Dùng Finder trên macOS (hoặc iTunes trên Windows)
1. Cắm iPhone SE 2020 vào máy tính → mở **Finder** → chọn thiết bị iPhone → tab **Tệp (Files)**.
2. Mở rộng mục **MBAACC** → kéo thả `MBAA.exe`, `0000.p..0008.p`, `System/`, `Information/`, `GRP/`, `dat/`, `Movie/` vào thư mục `MBAACC/` (hoặc trực tiếp vào gốc Documents của app).
3. Quay lại app **MBAACC** trên iPhone — ứng dụng tự động quét lại khi vào foreground và khởi động vòng lặp Metal 60 Hz.

---

## 7. Điều khiển & Tối ưu Phần cứng trên iPhone SE 2020

- **Bố cục màn hình (`1334×750` px / `667×375` pt):**
  - Viewport game giữ đúng tỷ lệ **4:3 (`1000×750` px)** ở chính giữa, chừa ra **2 thanh bên rộng `167 px` (`83.5 pt`)** ở cạnh trái và phải cho ngón tay cái.
  - **Cạnh trái:** D-pad ảo 8 hướng (hỗ trợ trượt mượt cho 236 / 214 / 623 / 22) + nút `PAUSE`, `START`, `COIN`.
  - **Cạnh phải:** Cụm `A`, `B`, `C`, `D`, `E` + nút macro **`DASH (A+B)`**, **`HEAT (A+B+C)`**, `FN1`, `FN2`, và nút **`PAD`** ở góc trên phải để chỉnh độ mờ (`Opacity`) hoặc ẩn/hiện bàn phím ảo.
- **Tay cầm Bluetooth / MFi (`GCController`):**
  - Khi kết nối tay cầm Xbox / PlayStation / MFi, lớp phím ảo tự động làm mờ hoàn toàn (`alpha = 0`), chỉ giữ lại nút `PAD` mờ nhẹ ở góc để tùy chỉnh nếu cần.
- **Quản lý RAM 3 GB trên iPhone SE 2020:**
  - Bộ nhớ guest được giới hạn gọn trong arena `128 MiB`, bộ đệm texture Metal giới hạn LRU `192 MiB`, và tự động giải phóng cache GPU khi iOS phát cảnh báo `didReceiveMemoryWarning`.
