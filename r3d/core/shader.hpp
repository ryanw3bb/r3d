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
            shader(std::string, std::string);

            GLuint program;
            GLuint mvp_matrix;
            GLuint view_matrix;
            GLuint model_matrix;
            GLuint texture_sampler;
            GLuint light_world_pos;
    };
}


#endif //R3D_SHADER_HPP
