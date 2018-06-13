//
// Created by Ryan on 21/05/2018.
//

#ifndef R3D_SHADER_HPP
#define R3D_SHADER_HPP

#include <iostream>
#include "gl_includes.hpp"

namespace r3d
{
    class shader
    {
    public:
        enum id
        {
            UNLIT_VERT_COLOR, UNLIT_TEXTURE, DIFFUSE
        };
        id shader_id;
        GLuint program;
        GLuint mvp_matrix;
        GLuint view_matrix;
        GLuint model_matrix;
        GLuint texture_sampler;
        GLuint light_world_pos;
        GLuint light_color;
        GLuint light_intensity;

        shader(id);

        shader(const char*, const char*);

        void bind();

    private:
        void init(const char*, const char*);
    };
}

#endif //R3D_SHADER_HPP