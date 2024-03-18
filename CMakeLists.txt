cmake_minimum_required(VERSION 3.13)
project(r3d)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

IF(WIN32)
    include_directories(C:/dev/external/include)
    link_directories(C:/dev/external/lib)
ELSE()
    include_directories(/usr/local/include /usr/local/include/freetype2)
    link_directories(/usr/local/lib)
ENDIF()

include_directories(external/include)

file(GLOB r3d_src
        r3d/core/*.hpp r3d/core/*.cpp
        r3d/load/*.hpp r3d/load/*.cpp
        r3d/primitive/*.hpp r3d/primitive/*.cpp
        r3d/render/*.hpp r3d/render/*.cpp
        r3d/ui/*.hpp r3d/ui/*.cpp
        r3d/util/*.hpp r3d/util/*.cpp)

file(GLOB imgui
        external/include/imgui/*.hpp external/include/imgui/*.cpp)

add_executable(${PROJECT_NAME}
        main.cpp main.hpp
        ${r3d_src}
        ${imgui})

IF(WIN32)
    target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} glew32 glfw3 assimp)
ELSE()
    target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} glew glfw assimp)
ENDIF()

set_target_properties(
        ${PROJECT_NAME}
    PROPERTIES
        OUTPUT_NAME "r3d_demo"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:r3d>/resources)

IF(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/external/bin
            $<TARGET_FILE_DIR:r3d>)
ENDIF()
