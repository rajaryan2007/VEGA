# VEGA Shared Library
project(VEGA)

# 1. Collect all files with absolute paths to ensure the TREE logic works
file(GLOB_RECURSE VEGA_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image/*.cpp"
)

file(GLOB_RECURSE GLM_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm/glm/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm/glm/*.inl"
)

# Combine the lists
set(ALL_VEGA_FILES ${VEGA_SOURCES} ${GLM_FILES})

# 2. Add the library
add_library(VEGA SHARED ${ALL_VEGA_FILES})

# 3. THE FIX: Use the VEGA folder as the root for EVERYTHING in this target
# This matches the folder structure on disk 1:1 in Visual Studio
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${ALL_VEGA_FILES})

# 4. Include Directories
target_include_directories(VEGA PUBLIC
    "src"
    "vendor/spdlog/include"
    "vendor/GLFW/include"
    "vendor/Glad/include"
    "vendor/imgui"
    "vendor/glm"
    "vendor/stb_image"
    "vendor/entt/include"
)

# 5. Definitions
target_compile_definitions(VEGA PUBLIC
    VG_PLATFORM_WINDOWS
    VG_DYNAMIC_LINK
    WINDLL
    GLFW_INCLUDE_NONE
    _CRT_SECURE_NO_WARNINGS
)

target_compile_definitions(VEGA PRIVATE VG_BUILD_DLL)

# 6. Precompiled Header
if(MSVC)
    target_precompile_headers(VEGA PRIVATE src/vgpch.h)
    target_compile_options(VEGA PRIVATE /utf-8)
endif()

# 7. Links
target_link_libraries(VEGA PUBLIC glfw Glad ImGui opengl32.lib)

set_target_properties(VEGA PROPERTIES DEBUG_POSTFIX d)