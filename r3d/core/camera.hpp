//
// Created by Ryan on 30/05/2018.
//

#ifndef R3D_CAMERA_HPP
#define R3D_CAMERA_HPP

#include "gl_includes.hpp"
#include "shader.hpp"

namespace r3d
{
    class camera
    {
        public:
            camera();
            glm::mat4 projection;
            glm::mat4 view;

            void set_uniforms(r3d::shader *, glm::mat4);
    };
}


#endif //R3D_CAMERA_HPP
