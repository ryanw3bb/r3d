cmake_minimum_required(VERSION 3.9)
project(r3d)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)
find_package(OpenGL)

add_executable(r3d
        main.cpp main.hpp
        r3d/scene.cpp r3d/scene.hpp
        r3d/core/game_object.cpp r3d/core/game_object.hpp
        r3d/component/mesh_renderer.cpp r3d/component/mesh_renderer.hpp
        r3d/load/load_shader.cpp r3d/load/load_shader.hpp
        r3d/load/load_texture.cpp r3d/load/load_texture.hpp
        r3d/load/load_mesh.cpp r3d/load/load_mesh.hpp
        r3d/shaders/diffuse_color.frag r3d/shaders/diffuse_color.vert
        r3d/shaders/diffuse_texture.frag r3d/shaders/diffuse_texture.vert
        r3d/shaders/diffuse_texture_bump.frag r3d/shaders/diffuse_texture_bump.vert
        r3d/shaders/unlit_texture.frag r3d/shaders/unlit_texture.vert
        r3d/shaders/unlit_color.frag r3d/shaders/unlit_color.vert
        r3d/component/component.cpp r3d/component/component.hpp
        r3d/core/gl_includes.hpp
        r3d/core/material.cpp r3d/core/material.hpp
        r3d/core/shader.cpp r3d/core/shader.hpp
        r3d/core/light.hpp
        r3d/component/behaviour.cpp r3d/component/behaviour.hpp
        r3d/core/constants.hpp r3d/core/constants.cpp
        r3d/core/camera.cpp r3d/core/camera.hpp
        r3d/core/time.cpp r3d/core/time.hpp
        r3d/utils/file.cpp r3d/utils/file.hpp
        r3d/utils/debug.cpp r3d/utils/debug.hpp
        r3d/utils/fps.cpp r3d/utils/fps.hpp
        r3d/libs/stb_image.h)

target_link_libraries(${PROJECT_NAME} glew glfw assimp ${OPENGL_gl_LIBRARY})

set_target_properties(
    r3d 
    PROPERTIES 
        OUTPUT_NAME "r3d_demo"
)

add_custom_command(TARGET r3d POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/r3d/shaders
        $<TARGET_FILE_DIR:r3d>/r3d/shaders)

add_custom_command(TARGET r3d POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:r3d>/assets)