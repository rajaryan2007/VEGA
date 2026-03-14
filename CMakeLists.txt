cmake_minimum_required(VERSION 3.10)
project(VEGA_Workspace)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories mirroring premake structure
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})

# Common Include Directories
set(VEGA_VENDOR_DIR ${CMAKE_SOURCE_DIR}/VEGA/vendor)

# Subdirectories
add_subdirectory(VEGA/vendor)
add_subdirectory(VEGA)
add_subdirectory(Sandbox)
add_subdirectory(VEGA_EDITOR)
