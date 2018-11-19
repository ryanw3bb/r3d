//
// Created by Ryan on 21/05/2018.
//

#ifndef R3D_SHADER_HPP
#define R3D_SHADER_HPP

#include <iostream>
#include "gl_includes.hpp"
#include "light.hpp"

namespace r3d
{
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
            VERTEX_COLOR
        };

        shader(id);

        shader(const char*, const char*);

        void set_camera_uniforms(glm::mat4, glm::mat4, glm::mat4, glm::vec3);

        void set_light_uniforms(r3d::light*);

        GLuint get_program() { return program; }

        GLuint get_texture_sampler() { return texture_sampler; }

        GLuint get_normal_sampler() { return normal_sampler; }

        GLuint get_vertex_identifier() { return vertex_identifier; }

        GLuint get_uv_identifier() { return uv_identifier; }

        GLuint get_normal_identifier() { return normal_identifier; }

        GLuint get_tangent_identifier() { return tangent_identifier; }

        GLuint get_bitangent_identifier() { return bitangent_identifier; }

    private:
        GLuint program;
        GLuint texture_sampler;
        GLuint normal_sampler;
        GLuint vertex_identifier;
        GLuint uv_identifier;
        GLuint normal_identifier;
        GLuint tangent_identifier;
        GLuint bitangent_identifier;
        GLuint mvp_matrix;
        GLuint view_matrix;
        GLuint model_matrix;
        GLuint light_world_pos;
        GLuint light_color;
        GLuint light_intensity;
        GLuint camera_world_pos;

        void init(const char*, const char*);
    };
}

#endif //R3D_SHADER_HPP