//
// Created by Ryan on 08/04/2018.
//

#ifndef R3D_SCENE_HPP
#define R3D_SCENE_HPP

#include <memory>
#include "core/gl_includes.hpp"
#include "core/game_object.hpp"
#include "core/light.hpp"
#include "core/camera.hpp"
#include "core/time.hpp"
#include "utils/debug.hpp"

namespace r3d
{
    class scene
    {
    public:
        GLFWwindow* window;
        bool should_update;

        scene(int width, int height);

        void update();

        void exit();

        void add_object(std::shared_ptr<r3d::game_object>);

        void add_light(std::shared_ptr<r3d::light>);

        const std::shared_ptr<r3d::camera>& get_camera() { return main_camera; }

        const float get_delta_time() { return timer->delta_time; }

    private:
        std::vector<std::shared_ptr<r3d::game_object>> game_objects;
        std::vector<std::shared_ptr<r3d::light>> lights;
        std::shared_ptr<r3d::camera> main_camera;
        std::unique_ptr<r3d::time> timer;
        std::unique_ptr<r3d::debug> debug_view;

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        static void error_callback(int error, const char* description);
    };
}

#endif //R3D_SCENE_HPP