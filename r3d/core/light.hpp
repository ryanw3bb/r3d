//
// Created by Ryan on 23/05/2018.
//

#ifndef R3D_LIGHT_HPP
#define R3D_LIGHT_HPP

#include "gl_includes.hpp"

namespace r3d
{
    class light
    {
    public:
        glm::vec3 position;
        glm::vec3 color;
        float intensity;

        light();

        light(glm::vec3, glm::vec3, float);
    };
}


#endif //R3D_LIGHT_HPP
