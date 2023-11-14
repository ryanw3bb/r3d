//
// Created by Ryan on 30/05/2018.
//

#ifndef R3D_CAMERA_HPP
#define R3D_CAMERA_HPP

#include "bounds.hpp"
#include "game_object.hpp"
#include "../render/shader.hpp"

namespace r3d
{
    class camera : public game_object
    {
    public:
        glm::mat4 view;
        glm::mat4 projection;
        float fov = 0.8f;
        float near = 0.1f;
        float far = 10000.0f;
        float aspect_ratio = 1.0f;
        int width;
        int height;
        glm::vec4 frustum_planes[6];

        camera(): game_object("camera") { }

        void init(int w, int h);

        void set_fov(float f) { fov = glm::radians(f); }

        void set_aspect(float a) { aspect_ratio = a; }

        void set_rotation(glm::vec3);

        void set_position(glm::vec3);

        void update();

        bool check_frustum_cull(glm::mat4& transform, std::shared_ptr<bounds>& bounds);

        bool check_frustum_cull(glm::vec3 point);

    private:
        void update_matrices();

        void update_frustum();
    };
}


#endif //R3D_CAMERA_HPP
