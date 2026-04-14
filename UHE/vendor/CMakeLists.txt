# Glad
add_library(Glad STATIC
    "${VEGA_VENDOR_DIR}/Glad/include/glad/glad.h"
    "${VEGA_VENDOR_DIR}/Glad/include/KHR/khrplatform.h"
    "${VEGA_VENDOR_DIR}/Glad/src/glad.c"
)
target_include_directories(Glad PUBLIC "${VEGA_VENDOR_DIR}/Glad/include")

# ImGui
file(GLOB IMGUI_SOURCES
    "${VEGA_VENDOR_DIR}/imgui/*.h"
    "${VEGA_VENDOR_DIR}/imgui/*.cpp"
)
add_library(ImGui STATIC ${IMGUI_SOURCES})
target_include_directories(ImGui PUBLIC "${VEGA_VENDOR_DIR}/imgui")

# Note: GLFW and spdlog are handled via add_subdirectory
add_subdirectory(GLFW)
add_subdirectory(spdlog)
