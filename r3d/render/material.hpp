//
// Created by Ryan on 21/05/2018.
//

#ifndef R3D_MATERIAL_HPP
#define R3D_MATERIAL_HPP

#include <memory>
#include "shader.hpp"
#include "../render/gl_includes.hpp"

namespace r3d
{
    class material
    {
    public:
        GLuint diffuse_texture;
        GLuint normal_texture;
        std::shared_ptr<r3d::shader> shader;

        material(std::shared_ptr<r3d::shader> shader) : shader(shader) {}
        material(std::string tex_path, std::shared_ptr<r3d::shader> shader);
        material(std::string tex_path, std::string normal_tex_path, std::shared_ptr<r3d::shader> shader);

        void bind();
    };
}


#endif //R3D_MATERIAL_HPP
