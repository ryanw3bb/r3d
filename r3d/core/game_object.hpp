//
// Created by Ryan on 16/05/2018.
//

#ifndef R3D_GAME_OBJECT_HPP
#define R3D_GAME_OBJECT_HPP

#include <iostream>
#include <vector>

#include "gl_includes.hpp"
#include "component.hpp"

namespace r3d
{
    class game_object
    {
        public:
            explicit game_object(std::string);
            void add_component(r3d::component *);

            std::string name;
            glm::vec3 position;
            glm::vec3 scale;
            glm::vec3 rotation;
            bool enabled;
            std::vector<r3d::component *> components;
    };
}

#endif //R3D_GAME_OBJECT_HPP