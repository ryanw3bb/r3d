//
// Created by Ryan on 16/05/2018.
//

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include "game_object.hpp"

using namespace r3d;

game_object::game_object(std::string name)
{
    this->name = name;

    printf("New game_object: %s\n", name.c_str());
}

game_object::game_object(std::string name, glm::vec3 position, glm::vec3 euler_angles, glm::vec3 scale)
{
    this->name = name;
    this->position = position;
    this->euler_angles = euler_angles;
    this->scale = scale;

    printf("New game_object: %s\n", name.c_str());
}

void game_object::add_component(r3d::component * component)
{
    components.push_back(component);
}

glm::mat4 game_object::get_transform()
{
    glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position);

    glm::mat4 rotation_matrix = glm::toMat4(glm::quat(euler_angles));

    glm::mat4 scale_matrix = glm::scale(scale);

    return translation_matrix * rotation_matrix * scale_matrix;
}