//
// Created by Ryan on 30/05/2018.
//

#include "camera.hpp"

using namespace r3d;

glm::mat4 camera::get_view()
{
    return glm::lookAt(position, position + forward, up);
}

glm::mat4 camera::get_projection()
{
    return glm::perspective(fov, aspect_ratio, near, far);
}