//
// Created by Ryan on 21/05/2018.
//

#ifndef R3D_MATERIAL_HPP
#define R3D_MATERIAL_HPP

#import <iostream>
#include "../core/gl_includes.hpp"
#include "shader.hpp"

namespace r3d
{
    class material
    {
        public:
            material(std::string tex_path, r3d::shader * shad);
            void bind();

            GLuint texture;
            r3d::shader * shader;
    };
}


#endif //R3D_MATERIAL_HPP
