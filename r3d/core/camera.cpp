//
// Created by Ryan on 30/05/2018.
//

#include "camera.hpp"

using namespace r3d;

camera::camera()
{

}

void camera::set_uniforms(r3d::shader * shader, glm::mat4 model)
{
    glm::mat4 mvp = projection * view * model;

    glUniformMatrix4fv(shader->mvp_matrix, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(shader->model_matrix, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(shader->view_matrix, 1, GL_FALSE, &view[0][0]);
}