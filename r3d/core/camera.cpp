//
// Created by Ryan on 30/05/2018.
//

#include "camera.hpp"

using namespace r3d;

camera::camera(int w, int h): width(w), height(h)
{

}

glm::vec3 camera::get_rotation()
{
    return glm::degrees(euler_angles);
}

void camera::set_rotation(glm::vec3 euler_angles_degrees)
{
    this->euler_angles = glm::radians(euler_angles_degrees);

    // direction : spherical coordinates to cartesian coordinates conversion
    forward = glm::vec3(cos(euler_angles.x) * sin(euler_angles.y),
                        sin(euler_angles.x),
                        cos(euler_angles.x) * cos(euler_angles.y));

    right = glm::vec3(sin(euler_angles.y - constants::PI / 2.0f),
                      0,
                      cos(euler_angles.y - constants::PI / 2.0f));

    up = glm::cross(right, forward);
}

void camera::set_uniforms(r3d::shader * shader, glm::mat4 model)
{
    view = glm::lookAt(position, position + forward, up);

    projection = glm::perspective(glm::radians(fov), (float)width / (float)height, near, far);

    glm::mat4 mvp = projection * view * model;

    glUniformMatrix4fv(shader->mvp_matrix, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(shader->model_matrix, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(shader->view_matrix, 1, GL_FALSE, &view[0][0]);
}