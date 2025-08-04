# Configure with [fxsdk build-fx] or [fxsdk build-cg], which provide the
# toolchain file and module path of the fxSDK

cmake_minimum_required(VERSION 3.15)
project(prog-tools LANGUAGES ASM C)

include(GenerateG3A)
include(Fxconv)
find_package(Gint 2.9 REQUIRED)
find_package(LibProf 2.4 REQUIRED)

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
  src/forth-locals.c
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

  #Assembly file generated separately by GCC 15.1.0 for __attribute__((musttail))
  #src/custom/generated/test.s
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
target_link_libraries(prog-tools Gint::Gint LibProf::LibProf)

generate_g3a(TARGET prog-tools OUTPUT "prog-tools.g3a"
    NAME "prog-tools" ICONS assets-cg/icon-uns.png assets-cg/icon-sel.png)
