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
#include "../component/mesh_renderer.hpp"
#include "../component/behaviour.hpp"

namespace r3d
{
    class game_object
    {
    public:
        const char* name;
        std::vector<r3d::behaviour*> behaviours;
        bool enabled;
        r3d::mesh_renderer* renderer;

        game_object();

        game_object(const char*);

        game_object(const char*, glm::vec3, glm::vec3, glm::vec3);

        ~game_object(){}

        game_object(const game_object& other) {}

        void add_renderer(r3d::mesh_renderer*);

        void add_behaviour(r3d::behaviour*);

        void update_behaviours();

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