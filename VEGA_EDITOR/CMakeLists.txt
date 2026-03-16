# VEGA_EDITOR Executable

file(GLOB_RECURSE EDITOR_SOURCES
    "src/*.h"
    "src/*.cpp"
)

add_executable(VEGA_EDITOR ${EDITOR_SOURCES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "" FILES ${EDITOR_SOURCES})

target_include_directories(VEGA_EDITOR PRIVATE
    "src"
    "${CMAKE_SOURCE_DIR}/VEGA/src"
    "${CMAKE_SOURCE_DIR}/VEGA/vendor"
    "${CMAKE_SOURCE_DIR}/VEGA/vendor/glm"
    "${CMAKE_SOURCE_DIR}/VEGA/vendor/entt/include"
    "${CMAKE_SOURCE_DIR}/VEGA/vendor/spdlog/include"
)

target_link_libraries(VEGA_EDITOR PRIVATE VEGA)

target_compile_definitions(VEGA_EDITOR PRIVATE
    VG_PLATFORM_WINDOWS
    VG_DYNAMIC_LINK
)

if(MSVC)
    target_compile_options(VEGA_EDITOR PRIVATE /utf-8)
endif()
target_compile_definitions(VEGA_EDITOR PRIVATE
    VG_PROJECT_DIR="${CMAKE_SOURCE_DIR}/VEGA_EDITOR"
)
