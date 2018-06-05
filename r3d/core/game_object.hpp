//
// Created by Ryan on 16/05/2018.
//

#ifndef R3D_GAME_OBJECT_HPP
#define R3D_GAME_OBJECT_HPP

#include <iostream>
#include <vector>

#include "gl_includes.hpp"
#include "../component/component.hpp"

namespace r3d
{
    class game_object
    {
        public:
            game_object(std::string);
            game_object(std::string, glm::vec3 position, glm::vec3 euler_angles, glm::vec3 scale);
            void add_component(r3d::component *);
            r3d::component * get_component(std::string);
            glm::mat4 get_transform();

            std::string name;
            glm::vec3 position = glm::vec3(0, 0, 0);
            glm::vec3 scale = glm::vec3(1, 1, 1);
            glm::vec3 euler_angles = glm::vec3(0, 0, 0);
            std::vector<r3d::component *> components;
            bool enabled;
    };
}

#endif //R3D_GAME_OBJECT_HPP