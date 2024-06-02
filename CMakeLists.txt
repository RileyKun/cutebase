cmake_minimum_required(VERSION 3.28)
project(cutebase LANGUAGES CXX)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CPM.cmake)

CPMAddPackage("gh:freetype/freetype#VER-2-13-2")
CPMAddPackage("gh:g-truc/glm#1.0.1")
CPMAddPackage("gh:ocornut/imgui@1.90.5")
CPMAddPackage("gh:cursey/safetyhook@0.4.1")
CPMAddPackage(
  NAME zydis
  GITHUB_REPOSITORY zyantific/zydis
  VERSION 4.1.0
  OPTIONS "ZYDIS_BUILD_EXAMPLES OFF"
  "ZYDIS_BUILD_TOOLS OFF"
  "ZYDIS_BUILD_DOXYGEN OFF"
)


add_library(cutebase SHARED
  # cheat
  src/main_thread.cpp
  src/factory/factory.cpp
  src/hooks/lists/client.cpp
  src/hooks/lists/directx.cpp
  src/hooks/lists/wndproc.cpp
  src/hooks/lists/surface.cpp
  src/hooks/lists/studio.cpp
  src/hooks/lists/prediction.cpp
  src/hooks/lists/key_values.cpp
  src/gui/watermark/watermark.cpp
  src/gui/debug/debug.cpp
  src/gui/menu/menu.cpp

  # features
  src/cheat/movement/movement.cpp

  # sdk
  inc/link.cpp
  inc/console/console.cpp
  inc/valve/tf2/cdll_int.cpp
  inc/valve/tf2/studio_render.cpp
  inc/valve/tf2/input.cpp
  inc/valve/tf2/netvars/netvars.cpp
  inc/valve/tf2/c_entity.cpp
  inc/valve/tf2/prediction.cpp
  inc/valve/tf2/md5.cpp
  inc/valve/tf2/bitbuf.cpp
  inc/drawsystem/drawsystem.cpp
)

if(imgui_ADDED)
  target_sources(cutebase PRIVATE
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/misc/freetype/imgui_freetype.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_dx9.cpp
  )

  target_include_directories(cutebase PUBLIC
    $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>
    $<BUILD_INTERFACE:${imgui_SOURCE_DIR}/backends>)

  target_compile_definitions(cutebase PUBLIC
    "IMGUI_USER_CONFIG=\"${CMAKE_SOURCE_DIR}/inc/imconfig.hpp\""
    IMGUI_IMPL_WIN32_DISABLE_GAMEPAD
  )
endif()

# Check build types so we can apply specific settings per build type.
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(cutebase PRIVATE
    NOMINMAX GLM_FORCE_SWIZZLE GLM_FORCE_ALIGNED_GENTYPES CUTE_DEBUG CUTE_BETA
  )
  target_compile_options(cutebase PRIVATE
    /Od /Zi /MTd /arch:AVX2
  )
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
  target_compile_definitions(cutebase PRIVATE
    NOMINMAX NDEBUG GLM_FORCE_SWIZZLE GLM_FORCE_ALIGNED_GENTYPES CUTE_BETA
  )
  target_compile_options(cutebase PRIVATE
    /O2 /Zi /MT /arch:AVX2
  )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_definitions(cutebase PRIVATE
    NOMINMAX NDEBUG GLM_FORCE_SWIZZLE GLM_FORCE_ALIGNED_GENTYPES
  )
  target_compile_options(cutebase PRIVATE
    /O2 /MT /arch:AVX2
  )
else()
  message(FATAL_ERROR "Build type is not supported.")
endif()

target_include_directories(cutebase PRIVATE inc)
target_include_directories(cutebase PRIVATE src/cheat)

target_link_libraries(cutebase PRIVATE safetyhook::safetyhook glm::glm freetype d3d9)