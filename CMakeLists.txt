cmake_minimum_required(VERSION 3.9)
project(r3d)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)
find_package(OpenGL)

add_executable(r3d
        main.cpp main.hpp
        r3d/r3d.cpp r3d/r3d.hpp
        r3d/core/controls.cpp r3d/core/controls.hpp
        r3d/core/object.cpp r3d/core/object.hpp
        r3d/load/loadShaders.cpp r3d/load/loadShaders.hpp
        r3d/load/loadTexture.cpp r3d/load/loadTexture.hpp
        r3d/load/loadMesh.cpp r3d/load/loadMesh.hpp
        shaders/diffuse_frag.fragmentshader shaders/diffuse_vert.vertexshader
        shaders/color_frag.fragmentshader shaders/color_vert.vertexshader
        shaders/texture_frag.fragmentshader shaders/texture_vert.vertexshader r3d/core/object.cpp r3d/core/object.hpp)

target_link_libraries(${PROJECT_NAME} glew glfw assimp ${OPENGL_gl_LIBRARY})