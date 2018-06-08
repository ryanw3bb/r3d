//
// Created by Ryan on 30/05/2018.
//

#ifndef R3D_CAMERA_HPP
#define R3D_CAMERA_HPP

#include "gl_includes.hpp"
#include "shader.hpp"
#include "constants.hpp"

namespace r3d
{
    class camera
    {
        public:
            camera(int, int);
            void set_uniforms(r3d::shader *, glm::mat4);
            void set_rotation(glm::vec3);
            glm::vec3 get_rotation();
            void set_position(glm::vec3 p) { position = p; }
            glm::vec3 get_position() { return position; }
            glm::vec3 get_forward() { return forward; }
            glm::vec3 get_up() { return up; }
            glm::vec3 get_right() { return right; }
            float fov = 45;
            float near = 0.1f;
            float far = 100.0f;
            int width;
            int height;

        private:
            glm::vec3 position;
            glm::vec3 euler_angles;
            glm::vec3 forward;
            glm::vec3 right;
            glm::vec3 up;
            glm::mat4 projection;
            glm::mat4 view;
    };
}


#endif //R3D_CAMERA_HPP
