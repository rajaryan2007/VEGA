# Sandbox Executable

file(GLOB_RECURSE SANDBOX_SOURCES 
    "src/*.h" 
    "src/*.cpp"
)

add_executable(Sandbox ${SANDBOX_SOURCES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "" FILES ${SANDBOX_SOURCES})

target_include_directories(Sandbox PRIVATE 
    "src"
    "${CMAKE_SOURCE_DIR}/VEGA/src"
    "${CMAKE_SOURCE_DIR}/VEGA/vendor"
    "${CMAKE_SOURCE_DIR}/VEGA/vendor/glm"
    "${CMAKE_SOURCE_DIR}/VEGA/vendor/entt/include"
    "${CMAKE_SOURCE_DIR}/VEGA/vendor/spdlog/include"
)

target_link_libraries(Sandbox PRIVATE VEGA)

target_compile_definitions(Sandbox PRIVATE 
    VG_PLATFORM_WINDOWS
    VG_DYNAMIC_LINK
)

if(MSVC)
    target_compile_options(Sandbox PRIVATE /utf-8)
endif()
