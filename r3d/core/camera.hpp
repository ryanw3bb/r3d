//
// Created by Ryan on 30/05/2018.
//

#ifndef R3D_CAMERA_HPP
#define R3D_CAMERA_HPP

#include "gl_includes.hpp"
#include "game_object.hpp"

namespace r3d
{
    class camera : public game_object
    {
    public:
        glm::mat4 view;
        glm::mat4 projection;

        camera(): game_object("camera") { }

        camera(float ar): game_object("camera") { aspect_ratio = ar; }

        void set_fov(float f) { fov = glm::radians(f); }

        void set_aspect(float a) { aspect_ratio = a; }

        void set_rotation(glm::vec3);

        void set_position(glm::vec3);

        void update_matrices();

    private:
        float fov = 0.8f;
        float near = 0.1f;
        float far = 100.0f;
        float aspect_ratio = 1.0f;
    };
}


#endif //R3D_CAMERA_HPP
