#!/usr/bin/env bash
set -euo pipefail

# Build an unsigned arm64 iOS .ipa for MBAACCRecomp (ready for ESign / AltStore / SideStore).
# Must be run on macOS with Xcode (iOS SDK) and XcodeGen installed.

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
IOS_DIR="${SCRIPT_DIR}"
REPO_ROOT="$(cd "${IOS_DIR}/.." && pwd)"

BUILD_CONFIG="${BUILD_CONFIG:-Release}"
OUT_DIR="${OUT_DIR:-${REPO_ROOT}/dist}"
OUT_IPA="${OUT_IPA:-${OUT_DIR}/MBAACC-unsigned.ipa}"
DERIVED_DATA="${DERIVED_DATA:-${REPO_ROOT}/build-ios-derived}"
BUILD_GEN_DIR="${REPO_ROOT}/build_gen"

echo "=== MBAACC AOT Recomp iOS Unsigned IPA Builder ==="
echo "Repo root     : ${REPO_ROOT}"
echo "Configuration : ${BUILD_CONFIG}"
echo "Output IPA    : ${OUT_IPA}"

# 1. Preflight check on macOS tools
for cmd in xcodegen xcodebuild ditto zip shasum; do
    if ! command -v "${cmd}" >/dev/null 2>&1; then
        echo "ERROR: Missing required tool '${cmd}'. On macOS install Xcode + 'brew install xcodegen'." >&2
        exit 1
    fi
done

# 2. Preflight check on generated AOT C++20 sources (BYOC build_gen/)
REQUIRED_GEN_FILES=(
    "recomp_funcs.h"
    "iat_table.h"
    "gen_core.cpp"
    "gen_filepac.cpp"
    "gen_dxtools.cpp"
    "gen_scene.cpp"
    "gen_game_engine.cpp"
    "gen_chara.cpp"
    "gen_menu.cpp"
    "gen_replay.cpp"
    "gen_input.cpp"
    "gen_sound.cpp"
    "gen_netvs.cpp"
    "gen_dispatch.cpp"
)

missing_count=0
for fname in "${REQUIRED_GEN_FILES[@]}"; do
    if [[ ! -s "${BUILD_GEN_DIR}/${fname}" ]]; then
        echo "ERROR: Missing required generated file: build_gen/${fname}" >&2
        missing_count=$((missing_count + 1))
    fi
done
if [[ "${missing_count}" -gt 0 ]]; then
    echo "ERROR: ${missing_count} build_gen/ file(s) missing. Run 'py -m recompiler.cli' locally first or provide build_gen.zip." >&2
    exit 1
fi

# 3. Generate Xcode project from ios/project.yml
echo ">>> Generating MBAACCRecomp.xcodeproj with xcodegen..."
(
    cd "${IOS_DIR}"
    rm -rf MBAACCRecomp.xcodeproj
    xcodegen generate --spec project.yml
)

# 4. Compile arm64 iOS .app without code signing
echo ">>> Building arm64 Release .app (CODE_SIGNING_ALLOWED=NO)..."
rm -rf "${DERIVED_DATA}"
xcodebuild \
    -project "${IOS_DIR}/MBAACCRecomp.xcodeproj" \
    -scheme MBAACCRecomp \
    -configuration "${BUILD_CONFIG}" \
    -sdk iphoneos \
    -arch arm64 \
    -derivedDataPath "${DERIVED_DATA}" \
    CODE_SIGNING_ALLOWED=NO \
    CODE_SIGNING_REQUIRED=NO \
    CODE_SIGN_IDENTITY="" \
    DEVELOPMENT_TEAM="" \
    AD_HOC_CODE_SIGNING_ALLOWED=NO \
    build

APP_PATH="${DERIVED_DATA}/Build/Products/${BUILD_CONFIG}-iphoneos/MBAACC.app"
if [[ ! -d "${APP_PATH}" ]]; then
    echo "ERROR: Expected app bundle not found at ${APP_PATH}" >&2
    exit 1
fi

APP_BIN="${APP_PATH}/MBAACC"
if [[ ! -f "${APP_BIN}" ]]; then
    echo "ERROR: Expected Mach-O binary not found at ${APP_BIN}" >&2
    exit 1
fi

echo ">>> Binary verification:"
file "${APP_BIN}"
lipo -info "${APP_BIN}" || true
if [[ ! -f "${APP_PATH}/default.metallib" ]]; then
    echo "ERROR: Expected compiled Metal shader library default.metallib missing inside ${APP_PATH}" >&2
    exit 1
fi
ls -lh "${APP_PATH}/default.metallib"

# 5. Package clean unsigned Payload -> .ipa (for ESign)
echo ">>> Packaging unsigned IPA for ESign..."
WORK_DIR="$(mktemp -d)"
trap 'rm -rf "${WORK_DIR}"' EXIT

mkdir -p "${WORK_DIR}/Payload" "${OUT_DIR}"
ditto "${APP_PATH}" "${WORK_DIR}/Payload/MBAACC.app"

# Ensure zero stale signatures/profiles so ESign can sign cleanly with user certificate
rm -rf "${WORK_DIR}/Payload/MBAACC.app/_CodeSignature" \
       "${WORK_DIR}/Payload/MBAACC.app/embedded.mobileprovision"

rm -f "${OUT_IPA}"
(
    cd "${WORK_DIR}"
    zip -r -y -q "${OUT_IPA}" Payload
)

echo "=== Success ==="
ls -lh "${OUT_IPA}"
shasum -a 256 "${OUT_IPA}"
