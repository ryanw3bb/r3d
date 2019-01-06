//
// Created by Ryan on 19/05/2018.
//

#ifndef R3D_RENDEROBJECT_HPP
#define R3D_RENDEROBJECT_HPP

#include <iostream>
#include <vector>
#include <memory>
#include "../core/light.hpp"
#include "../core/gl_includes.hpp"
#include "../core/material.hpp"
#include "../core/mesh.hpp"

namespace r3d
{
    class camera;

    class mesh_renderer
    {
    public:
        std::shared_ptr<r3d::mesh> mesh;
        std::shared_ptr<r3d::material> material;
        std::shared_ptr<r3d::shader> shader;

        // default constructor & overloads
        mesh_renderer() {}

        mesh_renderer(std::string model_path,
                shader::id shader_type,
                std::string diffuse_map,
                std::string normal_map = "",
                bool debug = false);

        // destructor
        ~mesh_renderer()
        {
            printf("Delete mesh_renderer [address: %p]\n", this);
        }

        void render(glm::mat4 model,
                r3d::camera& main_camera,
                std::vector<r3d::light>& lights,
                bool change_shader = true,
                bool bind_vao = true,
                bool bind_textures = true);

        void destroy();

    private:
        GLuint vertex_array_object;
        GLuint vertex_buffer_object;
        GLuint indices_buffer;
    };
}

#endif //R3D_RENDEROBJECT_HPP