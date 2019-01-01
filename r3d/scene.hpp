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

        r3d::camera& get_camera() { return main_camera; }

        const float get_delta_time() { return timer.delta_time; }

    private:
        std::vector<std::shared_ptr<r3d::game_object>> game_objects;
        std::vector<r3d::light> lights;
        std::shared_ptr<game_object> last_render_object;
        r3d::camera main_camera;
        r3d::time timer;
        r3d::debug debug_view;

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        static void error_callback(int error, const char* description);
    };
}

#endif //R3D_SCENE_HPP