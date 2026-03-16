cmake_minimum_required(VERSION 3.16)
project(VEGA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This is what Premake uses to allow folder nesting
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# --- Output Directory Logic (Premake Style) ---
set(ARCH x64)
if(CMAKE_BUILD_TYPE)
    set(OUTPUT_DIR "${CMAKE_BUILD_TYPE}-windows-${ARCH}")
else()
    set(OUTPUT_DIR "Debug-windows-${ARCH}")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR})

foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${CONFIG} CONFIG_UPPER)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${CMAKE_SOURCE_DIR}/bin/${CONFIG}-windows-${ARCH})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${CMAKE_SOURCE_DIR}/bin/${CONFIG}-windows-${ARCH})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG_UPPER} ${CMAKE_SOURCE_DIR}/bin/${CONFIG}-windows-${ARCH})
endforeach()

# --- Subdirectories ---
# Vendor libs
add_subdirectory(VEGA/vendor/GLFW)
add_subdirectory(VEGA/vendor/Glad)
add_subdirectory(VEGA/vendor/imgui)

# Projects
add_subdirectory(VEGA)
add_subdirectory(Sandbox)
add_subdirectory(VEGA_EDITOR)

# REMOVED: The source_group call from here (It doesn't work at the root level)