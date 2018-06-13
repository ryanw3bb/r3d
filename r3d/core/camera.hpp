//
// Created by Ryan on 30/05/2018.
//

#ifndef R3D_CAMERA_HPP
#define R3D_CAMERA_HPP

#include "gl_includes.hpp"
#include "shader.hpp"
#include "game_object.hpp"

namespace r3d
{
    class camera : public game_object
    {
    public:
        float fov = 45;
        float near = 0.1f;
        float far = 100.0f;
        int width = 1024;
        int height = 768;

        camera();

        camera(int w, int h) : width(w), height(h) {};

        void set_uniforms(r3d::shader*, glm::mat4);

    private:
        glm::mat4 projection;
        glm::mat4 view;
    };
}


#endif //R3D_CAMERA_HPP
