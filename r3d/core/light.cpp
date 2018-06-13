//
// Created by Ryan on 23/05/2018.
//

#include "light.hpp"

using namespace r3d;

light::light()
{

}

light::light(glm::vec3 position, glm::vec3 color, float intensity)
{
    this->position = position;
    this->color = color;
    this->intensity = intensity;
}

void light::set_uniforms(r3d::shader* shader)
{
    glUniform3f(shader->light_world_pos, position.x, position.y, position.z);
    glUniform3f(shader->light_color, color.x, color.y, color.z);
    glUniform1f(shader->light_intensity, intensity);
}