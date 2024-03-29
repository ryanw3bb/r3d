//
// Created by Ryan on 26/03/2018.
//

#include <memory>
#include <vector>
#include <string>
#include "main.hpp"
#include "r3d/core/game_object.hpp"
#include "r3d/core/light.hpp"
#include "r3d/core/time.hpp"
#include "r3d/render/shader.hpp"
#include "r3d/render/mesh_renderer.hpp"

using namespace r3d;

const int WIDTH = 1280;
const int HEIGHT = 720;
const float CAMERA_MOVE_SPEED = 3;
const float CAMERA_ROTATE_SPEED = 0.05f;
const float CRATE_ROTATE_SPEED = 30;
const float FULL_ROTATION = 360;
const int NUM_ROWS = 5;

double last_x, last_y;
r3d::scene main_scene;
std::vector<std::shared_ptr<game_object>> crates;

int main()
{
    main_scene.init(WIDTH, HEIGHT);
    main_scene.get_camera().set_position(glm::vec3(1, 1, -6));
    main_scene.get_camera().set_rotation(glm::vec3(344, 322, 0));
    main_scene.add_light(glm::vec3(4, 8, 6), glm::vec3(0.9, 0.9, 0.9), 45.0f);
    main_scene.add_skybox(std::vector<std::string> { "resources/textures/skybox/left.png",
                                                     "resources/textures/skybox/right.png",
                                                     "resources/textures/skybox/top.png",
                                                     "resources/textures/skybox/bottom.png",
                                                     "resources/textures/skybox/front.png",
                                                     "resources/textures/skybox/back.png" });

    auto crate { main_scene.create_object("crate") };
    crate->add_renderer("resources/models/crate.obj",
            shader::id::DIFFUSE_TEXTURE_BUMP,
            "resources/textures/crate_diffuse.jpg",
            "resources/textures/crate_normal.jpg");
    crates.emplace_back(crate);

    for(int x = 0; x < NUM_ROWS; x++)
    {
        for(int y = 0; y < NUM_ROWS; y++)
        {
            if (x == 0 && y == 0) continue;

            std::string name = "crate " + std::to_string(x * NUM_ROWS + y);
            crates.emplace_back(main_scene.instantiate_object(name, crate, glm::vec3(-x, 0, -y), glm::vec3(0, 0, 0)));
        }
    }

    main_scene.update_time();

    while(main_scene.should_update)
    {
        move_camera(main_scene.get_window());
        rotate_crates();
        main_scene.update();
    }

    main_scene.exit();

    return 0;
}

void rotate_crates()
{
    glm::vec3 rotation = crates[0]->get_rotation();
    rotation.x = fmod(rotation.x - (CRATE_ROTATE_SPEED * main_scene.get_delta_time()), FULL_ROTATION);
    rotation.z = fmod(rotation.z - (CRATE_ROTATE_SPEED * main_scene.get_delta_time()), FULL_ROTATION);

    for(auto& crate : crates)
    {
        crate->set_rotation(rotation);
    }
}

void move_camera(GLFWwindow* window)
{
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        if(last_x != 0)
        {
            glm::vec3 rotation = main_scene.get_camera().get_rotation();
            rotation.x = fmod(rotation.x + (CAMERA_ROTATE_SPEED * (float)(last_y - y)), FULL_ROTATION);
            rotation.y = fmod(rotation.y + (CAMERA_ROTATE_SPEED * (float)(last_x - x)), FULL_ROTATION);
            main_scene.get_camera().set_rotation(rotation);
        }

        last_x = x;
        last_y = y;
    }
    else
    {
        last_x = last_y = 0;
    }

    glm::vec3 position = main_scene.get_camera().get_position();

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        position += main_scene.get_camera().forward * main_scene.get_delta_time() * CAMERA_MOVE_SPEED;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        position -= main_scene.get_camera().forward * main_scene.get_delta_time() * CAMERA_MOVE_SPEED;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        position += main_scene.get_camera().right * main_scene.get_delta_time() * CAMERA_MOVE_SPEED;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        position -= main_scene.get_camera().right * main_scene.get_delta_time() * CAMERA_MOVE_SPEED;
    }

    main_scene.get_camera().set_position(position);
}
