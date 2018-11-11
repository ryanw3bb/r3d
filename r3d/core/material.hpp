//
// Created by Ryan on 21/05/2018.
//

#ifndef R3D_MATERIAL_HPP
#define R3D_MATERIAL_HPP

#include <iostream>
#include "../core/gl_includes.hpp"
#include "shader.hpp"

namespace r3d
{
    class material
    {
    public:
        GLuint diffuse_texture;
        GLuint normal_texture;
        r3d::shader* shader;

        material(r3d::shader* shader) : shader(shader) {}
        material(const char* tex_path, r3d::shader* shader);
        material(const char* tex_path, const char* normal_tex_path, r3d::shader* shader);

        void bind();
    };
}


#endif //R3D_MATERIAL_HPP
