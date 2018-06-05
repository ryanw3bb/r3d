cmake_minimum_required(VERSION 3.9)
project(r3d)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)
find_package(OpenGL)

add_executable(r3d
        main.cpp main.hpp
        r3d/scene.cpp r3d/scene.hpp
        r3d/core/controls.cpp r3d/core/controls.hpp
        r3d/core/game_object.cpp r3d/core/game_object.hpp
        r3d/component/mesh_renderer.cpp r3d/component/mesh_renderer.hpp
        r3d/load/load_shaders.cpp r3d/load/load_shaders.hpp
        r3d/load/load_texture.cpp r3d/load/load_texture.hpp
        r3d/load/load_mesh.cpp r3d/load/load_mesh.hpp
        shaders/diffuse_frag.fragmentshader shaders/diffuse_vert.vertexshader
        shaders/color_frag.fragmentshader shaders/color_vert.vertexshader
        shaders/texture_frag.fragmentshader shaders/texture_vert.vertexshader
        r3d/component/component.cpp r3d/component/component.hpp
        r3d/core/gl_includes.hpp
        r3d/core/material.cpp r3d/core/material.hpp
        r3d/core/shader.cpp r3d/core/shader.hpp
        r3d/core/light.cpp r3d/core/light.hpp
        r3d/component/behaviour.cpp r3d/component/behaviour.hpp
        r3d/core/constants.hpp r3d/core/constants.cpp
        r3d/core/camera.cpp r3d/core/camera.hpp)

target_link_libraries(${PROJECT_NAME} glew glfw assimp ${OPENGL_gl_LIBRARY})