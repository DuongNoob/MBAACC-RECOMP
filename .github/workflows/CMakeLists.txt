cmake_minimum_required(VERSION 3.22)
project(MBAACC_Recomp_iOS VERSION 1.0.7 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(APPLE)
    enable_language(OBJCXX)
endif()

option(MBAA_BUILD_RECOMP_APP "Link lifted C++20 game sources from build_gen/" ON)

# Portable C++20 runtime & software DXT1-5 / HLE library
set(MBAA_RUNTIME_CORE_SOURCES
    runtime/src/guest_memory.cpp
    runtime/src/dispatch.cpp
    runtime/src/hle_crt.cpp
    runtime/src/hle_win32.cpp
    runtime/src/hle_dshow.cpp
    runtime/src/rollback_hooks.cpp
    runtime/src/bcdec_dxt.cpp
)

set(MBAA_RUNTIME_APPLE_SOURCES
    runtime/src/hle_d3d9_metal.mm
    runtime/src/hle_input_ios.mm
    runtime/src/hle_audio_ios.mm
    runtime/src/runtime_engine.mm
)

add_library(mbaa_runtime STATIC
    ${MBAA_RUNTIME_CORE_SOURCES}
    $<$<BOOL:${APPLE}>:${MBAA_RUNTIME_APPLE_SOURCES}>
)

target_include_directories(mbaa_runtime
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/runtime/include
        ${CMAKE_CURRENT_SOURCE_DIR}/ios/Shaders
        $<$<BOOL:${MBAA_BUILD_RECOMP_APP}>:${CMAKE_CURRENT_SOURCE_DIR}/build_gen>
)

target_compile_features(mbaa_runtime PUBLIC cxx_std_20)

if(MSVC)
    target_compile_definitions(mbaa_runtime PRIVATE _CRT_SECURE_NO_WARNINGS NOMINMAX)
    target_compile_options(mbaa_runtime PRIVATE /W4 /utf-8)
else()
    target_compile_options(mbaa_runtime PRIVATE -Wall -Wextra -Wno-unused-parameter)
endif()

if(APPLE)
    target_compile_options(mbaa_runtime PRIVATE
        $<$<COMPILE_LANGUAGE:OBJCXX>:-fobjc-arc>
    )
    find_library(METAL_FRAMEWORK Metal REQUIRED)
    find_library(METALKIT_FRAMEWORK MetalKit REQUIRED)
    find_library(QUARTZCORE_FRAMEWORK QuartzCore REQUIRED)
    find_library(GAMECONTROLLER_FRAMEWORK GameController REQUIRED)
    find_library(AVFOUNDATION_FRAMEWORK AVFoundation REQUIRED)
    find_library(AUDIOTOOLBOX_FRAMEWORK AudioToolbox REQUIRED)
    find_library(CORETEXT_FRAMEWORK CoreText REQUIRED)
    find_library(COREGRAPHICS_FRAMEWORK CoreGraphics REQUIRED)
    find_library(FOUNDATION_FRAMEWORK Foundation REQUIRED)

    target_link_libraries(mbaa_runtime PUBLIC
        ${METAL_FRAMEWORK}
        ${METALKIT_FRAMEWORK}
        ${QUARTZCORE_FRAMEWORK}
        ${GAMECONTROLLER_FRAMEWORK}
        ${AVFOUNDATION_FRAMEWORK}
        ${AUDIOTOOLBOX_FRAMEWORK}
        ${CORETEXT_FRAMEWORK}
        ${COREGRAPHICS_FRAMEWORK}
        ${FOUNDATION_FRAMEWORK}
        iconv
    )
endif()

if(MBAA_BUILD_RECOMP_APP)
    set(MBAA_GEN_SOURCES
        build_gen/gen_core.cpp
        build_gen/gen_filepac.cpp
        build_gen/gen_dxtools.cpp
        build_gen/gen_scene.cpp
        build_gen/gen_game_engine.cpp
        build_gen/gen_chara.cpp
        build_gen/gen_menu.cpp
        build_gen/gen_replay.cpp
        build_gen/gen_input.cpp
        build_gen/gen_sound.cpp
        build_gen/gen_netvs.cpp
        build_gen/gen_dispatch.cpp
    )

    foreach(_gen_src IN LISTS MBAA_GEN_SOURCES)
        if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${_gen_src}")
            message(FATAL_ERROR
                "Missing generated file '${_gen_src}'. "
                "Run the recompiler first: py -m recompiler ... or disable -DMBAA_BUILD_RECOMP_APP=OFF."
            )
        endif()
    endforeach()

    add_library(mbaa_recomp_gen STATIC ${MBAA_GEN_SOURCES})
    target_link_libraries(mbaa_recomp_gen PUBLIC mbaa_runtime)
    target_include_directories(mbaa_recomp_gen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/build_gen)

    if(APPLE AND CMAKE_SYSTEM_NAME STREQUAL "iOS")
        find_library(UIKIT_FRAMEWORK UIKit REQUIRED)
        add_executable(MBAACCRecomp MACOSX_BUNDLE
            ios/App/main.mm
            ios/App/AppDelegate.mm
            ios/App/GameViewController.mm
            ios/App/TouchOverlayView.mm
            ios/Shaders/mbaa_shaders.metal
        )
        set_source_files_properties(ios/Shaders/mbaa_shaders.metal PROPERTIES LANGUAGE METAL)
        target_compile_options(MBAACCRecomp PRIVATE -fobjc-arc)
        target_link_libraries(MBAACCRecomp PRIVATE mbaa_recomp_gen ${UIKIT_FRAMEWORK})
        set_target_properties(MBAACCRecomp PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/ios/App/Info.plist"
            XCODE_ATTRIBUTE_CODE_SIGN_ENTITLEMENTS "${CMAKE_CURRENT_SOURCE_DIR}/ios/App/MBAACCRecomp.entitlements"
            XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"
            XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET "15.0"
        )
    endif()
endif()
