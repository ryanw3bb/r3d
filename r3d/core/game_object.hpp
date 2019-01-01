//
// Created by Ryan on 16/05/2018.
//

#ifndef R3D_GAME_OBJECT_HPP
#define R3D_GAME_OBJECT_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <glm/gtx/quaternion.hpp>
#include "gl_includes.hpp"
#include "constants.hpp"
#include "../component/mesh_renderer.hpp"
#include "../component/behaviour.hpp"

namespace r3d
{
    class game_object
    {
    public:
        bool enabled;
        std::string name = "new game_object";
        glm::vec3 position;
        glm::vec3 euler_angles;
        glm::vec3 scale;
        glm::vec3 forward;
        glm::vec3 right;
        glm::vec3 up;
        std::vector<r3d::behaviour> behaviours;
        std::shared_ptr<r3d::mesh_renderer> renderer;

        // constructors
        game_object() { init_print(); }

        game_object(std::string name): enabled(true), name(name), scale(glm::vec3(1, 1, 1)) { init_print(); }

        game_object(std::string name, glm::vec3 position, glm::vec3 euler_angles, glm::vec3 scale);

        // destructor
        ~game_object()
        {
            printf("Delete game_object: %s [address: %p]\n", name.c_str(), this);
        }

        void add_renderer(std::string mesh_file_path, shader::id shader_type, std::string diffuse_map = "", std::string normal_map = "");

        void add_behaviour(r3d::behaviour);

        void update_behaviours() const;

        glm::mat4 get_transform() const;

        virtual void set_rotation(glm::vec3);

        glm::vec3 get_rotation() const;

        virtual void set_position(glm::vec3 p) { position = p; }

        glm::vec3 get_position() { return position; }

        void set_scale(glm::vec3 s) { scale = s; }

        glm::vec3 get_scale() { return scale; }

        void update_directions();

        void init_print()
        {
            printf("Init game_object: %s [address: %p]\n", name.c_str(), this);
        }

    protected:
        glm::quat rotation;
    };
}

#endif //R3D_GAME_OBJECT_HPP