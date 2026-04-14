cmake_minimum_required(VERSION 3.16)

project(Glad C)

add_library(Glad STATIC
    src/glad.c
    include/glad/glad.h
    include/KHR/khrplatform.h
)

target_include_directories(Glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Disable warnings
if(MSVC)
    target_compile_options(Glad PRIVATE /w)
else()
    target_compile_options(Glad PRIVATE -w)
endif()

# Debug configuration
target_compile_definitions(Glad PRIVATE
    $<$<CONFIG:Debug>:GLAD_DEBUG>
)

# Optimization flags
target_compile_options(Glad PRIVATE
    $<$<CONFIG:Release>:/O2>
    $<$<CONFIG:Dist>:/O2>
)

# Symbols
if(MSVC)
    target_compile_options(Glad PRIVATE
        $<$<CONFIG:Debug>:/Zi>
    )
endif()