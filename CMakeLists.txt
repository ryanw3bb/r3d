cmake_minimum_required(VERSION 3.9)
project(r3d)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include
        /usr/local/include/freetype2)
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
        resources/shaders/diffuse_color.frag resources/shaders/diffuse_color.vert
        resources/shaders/diffuse_texture.frag resources/shaders/diffuse_texture.vert
        resources/shaders/diffuse_texture_bump.frag resources/shaders/diffuse_texture_bump.vert
        resources/shaders/unlit_texture.frag resources/shaders/unlit_texture.vert
        resources/shaders/unlit_color.frag resources/shaders/unlit_color.vert
        resources/shaders/unlit_skybox.frag resources/shaders/unlit_skybox.vert
        r3d/core/gl_includes.hpp
        r3d/core/material.cpp r3d/core/material.hpp
        r3d/core/shader.cpp r3d/core/shader.hpp
        r3d/core/light.hpp
        r3d/component/behaviour.cpp r3d/component/behaviour.hpp
        r3d/core/constants.hpp r3d/core/constants.cpp
        r3d/core/camera.cpp r3d/core/camera.hpp
        r3d/core/time.cpp r3d/core/time.hpp
        r3d/core/mesh.hpp
        r3d/util/file.cpp r3d/util/file.hpp
        r3d/util/debug.cpp r3d/util/debug.hpp
        r3d/util/stats.cpp r3d/util/stats.hpp
        r3d/lib/stb_image.h
        r3d/ui/canvas_object.hpp
        r3d/ui/text.cpp r3d/ui/text.hpp
        r3d/ui/canvas.cpp r3d/ui/canvas.hpp
        r3d/ui/font.cpp r3d/ui/font.hpp
        r3d/primitive/skybox.cpp r3d/primitive/skybox.hpp)

target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} glew glfw assimp freetype)

set_target_properties(
    r3d 
    PROPERTIES 
        OUTPUT_NAME "r3d_demo"
)

add_custom_command(TARGET r3d POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:r3d>/resources)