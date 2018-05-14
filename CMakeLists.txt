cmake_minimum_required(VERSION 3.9)
project(r3d)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)
find_package(OpenGL)

add_executable(r3d
        main.cpp main.hpp
        common/loadShaders.cpp common/loadShaders.hpp
        common/loadTexture.cpp common/loadTexture.hpp
        common/controls.cpp common/controls.hpp
        common/objLoader.cpp common/objLoader.hpp
        shaders/diffuse_frag.fragmentshader shaders/diffuse_vert.vertexshader
        shaders/color_frag.fragmentshader shaders/color_vert.vertexshader
        shaders/texture_frag.fragmentshader shaders/texture_vert.vertexshader)

target_link_libraries(${PROJECT_NAME} glew glfw assimp ${OPENGL_gl_LIBRARY})