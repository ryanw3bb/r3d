//
// Created by Ryan on 21/05/2018.
//

#ifndef R3D_SHADER_HPP
#define R3D_SHADER_HPP

#include <iostream>
#include <vector>
#include "gl_includes.hpp"
#include "light.hpp"

namespace r3d
{
    class camera;

    class shader
    {
    public:
        bool uses_normal_map = false;
        bool uses_lighting = true;
        bool uses_vertex_color = false;

        enum id
        {
            UNLIT_TEXTURE, 
            DIFFUSE_TEXTURE, 
            DIFFUSE_TEXTURE_BUMP, 
            DIFFUSE_COLOR, 
            VERTEX_COLOR,
            UI
        };

        shader(id);

        void bind_uniforms();

        void set_scene_uniforms(glm::mat4 &);

        void set_model_uniforms(glm::mat4 &);

        void set_scene_uniforms(r3d::camera &, std::vector<r3d::light> &);

        void use();

        GLuint get_program() { return program; }

        GLuint get_texture_sampler() { return texture_sampler; }

        GLuint get_normal_sampler() { return normal_sampler; }

        GLuint get_vertex_identifier() { return vertex_identifier; }

        GLuint get_uv_identifier() { return uv_identifier; }

        GLuint get_normal_identifier() { return normal_identifier; }

        GLuint get_tangent_identifier() { return tangent_identifier; }

    protected:
        GLuint program;
        GLuint texture_sampler;
        GLuint normal_sampler;
        GLuint vertex_identifier;
        GLuint uv_identifier;
        GLuint normal_identifier;
        GLuint tangent_identifier;
        GLuint model_matrix;
        GLuint view_matrix;
        GLuint projection_matrix;
        GLuint tint;
        GLuint light_world_pos;
        GLuint light_color;
        GLuint light_intensity;
        GLuint camera_world_pos;

        void load(std::string vert, std::string frag);
    };
}

#endif //R3D_SHADER_HPP