cmake_minimum_required(VERSION 3.16)
project(VEGA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)


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


function(auto_group target)
    get_target_property(files ${target} SOURCES)
    foreach(file ${files})
        file(RELATIVE_PATH rel ${CMAKE_SOURCE_DIR} ${file})
        get_filename_component(dir ${rel} PATH)
        string(REPLACE "/" "\\" group ${dir})
        source_group("${group}" FILES ${file})
    endforeach()
endfunction()

add_subdirectory(VEGA/vendor/GLFW)
add_subdirectory(VEGA/vendor/Glad)
add_subdirectory(VEGA/vendor/imgui)
add_subdirectory(VEGA/vendor/imGuizmo)
add_subdirectory(VEGA/vendor/volk)
add_subdirectory(VEGA/vendor/VulkanMemoryAllocator)
add_subdirectory(VEGA/vendor/yaml-cpp)

add_subdirectory(VEGA)
add_subdirectory(sandbox)
add_subdirectory(VEGA_EDITOR)


get_property(all_targets DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)
foreach(t ${all_targets})
    auto_group(${t})
endforeach()

