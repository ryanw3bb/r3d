//
// Created by Ryan on 16/05/2018.
//

#ifndef R3D_GAME_OBJECT_HPP
#define R3D_GAME_OBJECT_HPP

#include <iostream>
#include <vector>
#include <glm/gtx/quaternion.hpp>
#include "gl_includes.hpp"
#include "../component/component.hpp"
#include "constants.hpp"

namespace r3d
{
    class game_object
    {
        public:
            game_object();
            game_object(std::string);
            game_object(std::string, glm::vec3, glm::vec3, glm::vec3);
            void add_component(r3d::component *);
            r3d::component * get_component(std::string);
            glm::mat4 get_transform();
            void set_rotation(glm::vec3);
            glm::vec3 get_rotation();
            void set_position(glm::vec3 p) { position = p; }
            glm::vec3 get_position() { return position; }
            glm::vec3 get_forward() { return forward; }
            glm::vec3 get_up() { return up; }
            glm::vec3 get_right() { return right; }
            void set_scale(glm::vec3 s) { scale = s; }
            glm::vec3 get_scale() { return scale; }
            std::string name;
            std::vector<r3d::component *> components;
            bool enabled;

        protected:
            glm::vec3 position;
            glm::vec3 euler_angles;
            glm::quat rotation;
            glm::vec3 forward;
            glm::vec3 right;
            glm::vec3 up;
            glm::vec3 scale;
    };
}

#endif //R3D_GAME_OBJECT_HPP