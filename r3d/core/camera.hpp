//
// Created by Ryan on 30/05/2018.
//

#ifndef R3D_CAMERA_HPP
#define R3D_CAMERA_HPP

#include "gl_includes.hpp"
#include "game_object.hpp"

namespace r3d
{
    class camera : public game_object
    {
    public:
        float fov = 0.8f;
        float near = 0.1f;
        float far = 100.0f;
        float aspect_ratio = 1.0f;

        camera();

        camera(float ar) : aspect_ratio(ar) {};

        glm::mat4 get_projection();

        glm::mat4 get_view();
    };
}


#endif //R3D_CAMERA_HPP
