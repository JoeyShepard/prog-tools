# Configure with [fxsdk build-fx] or [fxsdk build-cg], which provide the
# toolchain file and module path of the fxSDK

cmake_minimum_required(VERSION 3.15)
project(prog-tools)

include(GenerateG1A)
include(GenerateG3A)
include(GenerateHH2Bin)
include(Fxconv)
find_package(Gint 2.9 REQUIRED)

set(SOURCES
  src/compatibility.c
  src/console.c
  src/debug.c
  src/dummy.c
  src/error.c
  src/exceptions.c
  src/forth-actions.c
  src/forth.c
  src/forth-compatibility.c
  src/forth-engine.c
  src/forth-primitives.c
  src/forth-process.c
  src/getkey.c
  src/graphics.c
  src/key-remap.c
  src/logging.c
  src/logging-config.c
  src/logging-custom.c
  src/main.c
  src/manager.c
  src/mem.c
  src/memory_manager.c
  src/menu.c
  src/shell.c
  src/text.c
  src/util.c
  # ...
)
# Shared assets, fx-9860G-only assets and fx-CG-50-only assets
set(ASSETS
  # ...
)
set(ASSETS_fx
  assets-fx/example.png
  # ...
)
set(ASSETS_cg
  assets-cg/example.png
  # ...
)

fxconv_declare_assets(${ASSETS} ${ASSETS_fx} ${ASSETS_cg} WITH_METADATA)

add_executable(prog-tools ${SOURCES} ${ASSETS} ${ASSETS_${FXSDK_PLATFORM}})
target_compile_options(prog-tools PRIVATE -Wall -Wextra -Os -g -flto -DCG50)
target_link_libraries(prog-tools Gint::Gint)

if("${FXSDK_PLATFORM_LONG}" STREQUAL fx9860G)
  generate_g1a(TARGET prog-tools OUTPUT "prog-tools.g1a"
    NAME "prog-tools" ICON assets-fx/icon.png)
elseif("${FXSDK_PLATFORM_LONG}" STREQUAL fxCG50)
  generate_g3a(TARGET prog-tools OUTPUT "prog-tools.g3a"
    NAME "prog-tools" ICONS assets-cg/icon-uns.png assets-cg/icon-sel.png)
elseif("${FXSDK_PLATFORM_LONG}" STREQUAL fx9860G_G3A)
  generate_g3a(TARGET prog-tools OUTPUT "prog-tools-fx.g3a"
    NAME "prog-tools-fx" ICONS assets-cg/icon-uns.png assets-cg/icon-sel.png)
elseif("${FXSDK_PLATFORM_LONG}" STREQUAL fxCP)
  generate_hh2_bin(TARGET prog-tools OUTPUT "prog-tools-hh2.bin")
endif()
