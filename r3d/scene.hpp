//
// Created by Ryan on 08/04/2018.
//

#ifndef R3D_SCENE_HPP
#define R3D_SCENE_HPP

#include "core/gl_includes.hpp"
#include "core/game_object.hpp"
#include "core/light.hpp"
#include "core/camera.hpp"
#include "core/time.hpp"

namespace r3d
{
    class scene
    {
    public:
        GLFWwindow* window;
        r3d::camera* main_camera;
        r3d::time* time;
        bool should_update;

        scene(int width, int height);

        void update();

        void exit();

        void add_object(r3d::game_object*);

        void add_light(r3d::light*);

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        static void error_callback(int error, const char* description);
    };
}

#endif //R3D_SCENE_HPP