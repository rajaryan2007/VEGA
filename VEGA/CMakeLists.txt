# VEGA Shared Library
project(VEGA)

file(GLOB_RECURSE VEGA_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image/*.cpp"
)

find_package(VULKAN REQUIRED)

file(GLOB_RECURSE GLM_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm/glm/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm/glm/*.inl"
)

set(ALL_VEGA_FILES ${VEGA_SOURCES} ${GLM_FILES})


add_library(VEGA SHARED ${ALL_VEGA_FILES})


source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "" FILES ${ALL_VEGA_FILES})


target_include_directories(VEGA PUBLIC
    "src"
    "vendor/spdlog/include"
    "vendor/GLFW/include"
    "vendor/Glad/include"
    "vendor/imgui"
    "vendor/glm"
    "vendor/stb_image"
    "vendor/entt/include"
    "vendor/volk"
    "vendor/VulkanMemoryAllocator/include"
)


target_compile_definitions(VEGA PUBLIC
    VG_PLATFORM_WINDOWS
    VG_DYNAMIC_LINK
    WINDLL
    GLFW_INCLUDE_NONE
    _CRT_SECURE_NO_WARNINGS
)

target_compile_definitions(VEGA PRIVATE VG_BUILD_DLL)


if(MSVC)
    target_precompile_headers(VEGA PRIVATE src/vgpch.h)
    target_compile_options(VEGA PRIVATE /utf-8)
endif()

target_link_libraries(VEGA PUBLIC 
glfw Glad Vulkan::Vulkan ImGui opengl32.lib
PRIVATE
VulkanMemoryAllocator volk
)
set_target_properties(VEGA PROPERTIES DEBUG_POSTFIX d)