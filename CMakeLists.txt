# Configure with [fxsdk build-fx] or [fxsdk build-cg], which provide the
# toolchain file and module path of the fxSDK

cmake_minimum_required(VERSION 3.15)
project(Glacial)

include(GenerateG1A)
include(GenerateG3A)
include(Fxconv)
find_package(Gint 2.1 REQUIRED)

set(SOURCES
  src/primitives.cpp
  src/main.cpp
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
  assets-cg/levelsimple.png
  assets-cg/maintitle.png
  assets-cg/sprites.png
  assets-cg/player.png
  assets-cg/light.png
  assets-cg/cursor.png
  assets-cg/parchemin.png
  assets-cg/treasures.png
  assets-cg/chests.png
  assets-cg/fontFantasy.png
  assets-cg/fontTiny.png
  assets-cg/monstres.png
  assets-cg/hearts.png
  assets-cg/sorcerer.png
  assets-cg/bigboss.png
  assets-cg/bigparchvide.png
  assets-cg/bulletsbicolor.png
  assets-cg/fragments.png
  # ...
)

fxconv_declare_assets(${ASSETS} ${ASSETS_fx} ${ASSETS_cg} WITH_METADATA)

add_executable(myaddin ${SOURCES} ${ASSETS} ${ASSETS_${FXSDK_PLATFORM}})
target_compile_options(myaddin PRIVATE -fpermissive -Wall -Wextra -O3)
target_link_libraries(myaddin Gint::Gint)

if("${FXSDK_PLATFORM_LONG}" STREQUAL fx9860G)
  generate_g1a(TARGET myaddin OUTPUT "Glacial.g1a"
    NAME "MagicLight" ICON assets-fx/icon.png)
elseif("${FXSDK_PLATFORM_LONG}" STREQUAL fxCG50)
  generate_g3a(TARGET myaddin OUTPUT "MagicLight.g3a" VERSION 0.9b
    NAME "MagicLight" ICONS assets-cg/icon-uns.png assets-cg/icon-sel.png)
endif()
