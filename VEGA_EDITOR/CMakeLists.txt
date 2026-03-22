project(VEGA_EDITOR)


file(GLOB_RECURSE EDITOR_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

foreach(_FILE ${EDITOR_SOURCES})
  
    get_filename_component(_DIR "${_FILE}" DIRECTORY)
    

    file(RELATIVE_PATH _REL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" "${_DIR}")
    
  
    string(REPLACE "/" "\\" _GROUP "${_REL_DIR}")
    
   
    source_group("${_GROUP}" FILES "${_FILE}")
    
  
endforeach()

add_executable(VEGA_EDITOR ${EDITOR_SOURCES})

target_include_directories(VEGA_EDITOR PRIVATE
    "src"
    "${CMAKE_SOURCE_DIR}/VEGA/src"
    "${CMAKE_SOURCE_DIR}/VEGA/vendor"
    "${CMAKE_SOURCE_DIR}/VEGA/vendor/glm"
    "${CMAKE_SOURCE_DIR}/VEGA/vendor/entt/include"
    "${CMAKE_SOURCE_DIR}/VEGA/vendor/spdlog/include"
    "${CMAKE_SOURCE_DIR}/VEGA/vendor/yaml-cpp/include"
)


target_link_libraries(VEGA_EDITOR PRIVATE VEGA)

target_compile_definitions(VEGA_EDITOR PRIVATE
    VG_PLATFORM_WINDOWS
    VG_DYNAMIC_LINK
    VG_PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)


if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assests")
    add_custom_command(TARGET VEGA_EDITOR POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assests"
            "$<TARGET_FILE_DIR:VEGA_EDITOR>/assests"
        COMMENT "Copying assets to: $<TARGET_FILE_DIR:VEGA_EDITOR>/assests"
    )
else()
    message(WARNING "Assets directory not found at ${CMAKE_CURRENT_SOURCE_DIR}/assets - skipping copy!")
endif()

if(MSVC)
    target_compile_options(VEGA_EDITOR PRIVATE /utf-8)
endif()