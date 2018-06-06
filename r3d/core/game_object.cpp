//
// Created by Ryan on 16/05/2018.
//

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <algorithm>
#include "game_object.hpp"
#include "../component/mesh_renderer.hpp"

using namespace r3d;

game_object::game_object(std::string name): enabled(true)
{
    this->name = name;

    printf("New game_object: %s\n", name.c_str());
}

game_object::game_object(std::string name, glm::vec3 position, glm::vec3 euler_angles, glm::vec3 scale): enabled(true)
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

r3d::component * game_object::get_component(std::string component_name)
{
    std::vector<component *>::iterator it = find_if(components.begin(), components.end(),
                                                    [component_name](r3d::component * c)
                                                    {
                                                        return c->name == component_name;
                                                    });

    if(it != components.end())
    {
        return (r3d::component *)(*it);
    }
    else
    {
        return nullptr;
    }
}

glm::mat4 game_object::get_transform()
{
    glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position);

    glm::mat4 rotation_matrix = glm::toMat4(glm::quat(euler_angles));

    glm::mat4 scale_matrix = glm::scale(scale);

    return translation_matrix * rotation_matrix * scale_matrix;
}