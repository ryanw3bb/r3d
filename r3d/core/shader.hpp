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
            enum id { UNLIT_VERT_COLOR, UNLIT_TEXTURE, DIFFUSE };
            shader(id);
            shader(std::string, std::string);
            void bind();
            id shader_id;
            bool unlit;
            GLuint program;
            GLuint mvp_matrix;
            GLuint view_matrix;
            GLuint model_matrix;
            GLuint texture_sampler;
            GLuint light_world_pos;
            GLuint light_color;
            GLuint light_intensity;

        private:
            void init(std::string, std::string);
    };
}

#endif //R3D_SHADER_HPP