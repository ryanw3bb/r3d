//
// Created by Ryan on 30/05/2018.
//

#include "camera.hpp"

using namespace r3d;

void camera::set_rotation(glm::vec3 euler_degrees)
{
    this->game_object::set_rotation(euler_degrees);
    update_matrices();
}

void camera::set_position(glm::vec3 position)
{
    this->game_object::set_position(position);
    update_matrices();
}

void camera::update_matrices()
{
    update_directions();
    view = glm::lookAt(position, position + forward, up);
    projection = glm::perspective(fov, aspect_ratio, near, far);
}
