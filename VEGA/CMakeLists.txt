# VEGA Shared Library

file(GLOB_RECURSE VEGA_SOURCES 
    "src/*.h" 
    "src/*.cpp"
    "vendor/stb_image/*.h" 
    "vendor/stb_image/*.cpp"
)

# Premake also included glm in files, but usually we just include it as headers.
# However, for consistency with premake:
file(GLOB_RECURSE GLM_FILES
    "vendor/glm/glm/*.hpp"
    "vendor/glm/glm/*.inl"
)
list(APPEND VEGA_SOURCES ${GLM_FILES})

add_library(VEGA SHARED ${VEGA_SOURCES})

target_include_directories(VEGA PUBLIC 
    "src"
    "${VEGA_VENDOR_DIR}/spdlog/include"
    "${VEGA_VENDOR_DIR}/GLFW/include"
    "${VEGA_VENDOR_DIR}/Glad/include"
    "${VEGA_VENDOR_DIR}/imgui"
    "${VEGA_VENDOR_DIR}/glm"
    "${VEGA_VENDOR_DIR}/stb_image"
    "${VEGA_VENDOR_DIR}/entt/include"
)

# Definitions
target_compile_definitions(VEGA PUBLIC 
    VG_PLATFORM_WINDOWS
    VG_BUILD_DLL
    WINDLL
    GLFW_INCLUDE_NONE
    _CRT_SECURE_NO_WARNINGS
)

# Precompiled Header
if(MSVC)
    target_precompile_headers(VEGA PRIVATE src/vgpch.h)
endif()

# Links
target_link_libraries(VEGA PUBLIC 
    glfw 
    Glad 
    ImGui 
    spdlog
    opengl32.lib
)

# Debug symbols
set_target_properties(VEGA PROPERTIES
    DEBUG_POSTFIX d
)
