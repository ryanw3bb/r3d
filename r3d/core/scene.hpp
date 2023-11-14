//
// Created by Ryan on 08/04/2018.
//

#ifndef R3D_SCENE_HPP
#define R3D_SCENE_HPP

#include <memory>
#include "game_object.hpp"
#include "light.hpp"
#include "camera.hpp"
#include "time.hpp"
#include "../primitive/skybox.hpp"
#include "../ui/canvas.hpp"
#include "../render/gl_includes.hpp"
#include "../render/gl_window.hpp"
#include "../util/debug.hpp"
#include "../util/stats.hpp"

namespace r3d
{
    class scene
    {
    public:
        r3d::gl_window window;

        bool should_update = true;

        scene() {}

        void init(int width, int height);

        void update_time();

        void update();

        void exit();

        std::shared_ptr<game_object> create_object(std::string name,
                glm::vec3 position = glm::vec3(0, 0, 0),
                glm::vec3 euler_angles = glm::vec3(0, 0, 0),
                glm::vec3 scale = glm::vec3(1, 1, 1));

        std::shared_ptr<game_object> instantiate_object(std::string name,
                std::shared_ptr<game_object> object,
                glm::vec3 position = glm::vec3(0, 0, 0),
                glm::vec3 euler_angles = glm::vec3(0, 0, 0),
                glm::vec3 scale = glm::vec3(1, 1, 1));

        void destroy_object(std::shared_ptr<game_object>& ptr);

        void add_light(glm::vec3 position, glm::vec3 color, float intensity);

        void add_skybox(std::vector<std::string>);

        r3d::camera& get_camera() { return main_camera; }

        const float get_delta_time() { return timer.delta_time; }

        r3d::canvas& get_canvas() { return canvas; }

        GLFWwindow* get_window() { return window.window; }

    private:
        std::vector<std::shared_ptr<r3d::game_object>> game_objects;
        std::vector<r3d::light> lights;
        std::shared_ptr<game_object> last_render_object;
        r3d::camera main_camera;
        r3d::time timer;
        r3d::debug debug_view;
        r3d::canvas canvas;
        r3d::skybox skybox;
    };
}

#endif //R3D_SCENE_HPP
