//
// Created by Ryan on 16/05/2018.
//

#include "game_object.hpp"

using namespace r3d;

game_object::game_object(std::string name, glm::vec3 position, glm::vec3 euler_angles, glm::vec3 scale):
        enabled { true },
        name { name },
        position { position },
        euler_angles { euler_angles },
        scale { scale }
{
    init_print();
    set_rotation_degrees(euler_angles);
}

void game_object::add_renderer(std::string mesh_file_path, shader::id shader_type, std::string diffuse_map, std::string normal_map)
{
    renderer = std::make_shared<mesh_renderer>(mesh_file_path, shader_type, diffuse_map, normal_map);

    printf("Add mesh_renderer: %p to %p\n", renderer.get(), this);
}

void game_object::add_behaviour(r3d::behaviour behaviour)
{
    behaviours.emplace_back(behaviour);
}

void game_object::update_behaviours() const
{
    for(const auto& b : behaviours)
    {
        b.update();
    }
}

glm::mat4& game_object::get_transform()
{
    if (transform_dirty)
    {
        glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 rotation_matrix = glm::toMat4(rotation);
        glm::mat4 scale_matrix = glm::scale(glm::mat4(1.0f), scale);
        cached_transform = translation_matrix * rotation_matrix * scale_matrix;
        transform_dirty = false;
    }

    return cached_transform;
}

void game_object::set_rotation(glm::vec3 euler_radians)
{
    euler_angles = euler_radians;
    rotation = glm::quat(euler_angles);
    transform_dirty = true;
}

glm::vec3 game_object::get_rotation() const
{
    return euler_angles;
}

void game_object::set_rotation_degrees(glm::vec3 euler_degrees)
{
    set_rotation(glm::radians(euler_degrees));
}

glm::vec3 game_object::get_rotation_degrees() const
{
    return glm::degrees(euler_angles);
}

void game_object::update_directions()
{
    // direction : spherical coordinates to cartesian coordinates conversion
    forward = glm::normalize(
                        glm::vec3(cos(euler_angles.x) * sin(euler_angles.y),
                        sin(euler_angles.x),
                        cos(euler_angles.x) * cos(euler_angles.y)));

    right = glm::normalize(glm::vec3(sin(euler_angles.y - constants::PI / 2.0f),
                        0,
                        cos(euler_angles.y - constants::PI / 2.0f)));

    up = glm::normalize(glm::cross(right, forward));
}
