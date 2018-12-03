//
// Created by Ryan on 26/03/2018.
//

#include <memory>
#include "main.hpp"
#include "r3d/scene.hpp"
#include "r3d/core/game_object.hpp"
#include "r3d/core/light.hpp"
#include "r3d/core/time.hpp"
#include "r3d/core/shader.hpp"
#include "r3d/component/mesh_renderer.hpp"

using namespace std;
using namespace glm;
using namespace r3d;

const int WIDTH = 1024;
const int HEIGHT = 768;
const float CAMERA_MOVE_SPEED = 3.0f;
const float CAMERA_ROTATE_SPEED = 0.05f;
const float CRATE_ROTATE_SPEED = 30;

double last_x, last_y;
unique_ptr<scene> main_scene;
shared_ptr<game_object> crate;
shared_ptr<light> main_light;

int main()
{
    main_scene = make_unique<scene>(WIDTH, HEIGHT);
    main_scene->get_camera()->set_position(vec3(0, 0, 1.5f));
    main_scene->get_camera()->set_rotation(vec3(0, 180, 0));

    main_light = make_shared<light>(vec3(0, 8, 1), vec3(0.9, 0.9, 0.9), 45.0f);
    main_scene->add_light(main_light);

    shared_ptr<shader> diffuse_shader = make_shared<shader>(shader::id::DIFFUSE_TEXTURE_BUMP);
    shared_ptr<material> crate_mat = make_shared<material>("assets/crate_diffuse.jpg", "assets/crate_normal.jpg", diffuse_shader);
    shared_ptr<mesh_renderer> crate_renderer = make_shared<mesh_renderer>("assets/crate.obj", crate_mat);
    crate = make_shared<game_object>("crate", vec3(0, 0, 0), vec3(-90, 0, -90), vec3(1, 1, 1));
    crate->add_renderer(crate_renderer);
    
    main_scene->add_object(crate);

    while(main_scene->should_update)
    {
        move_camera(main_scene->window);
        rotate_crate();
        main_scene->update();
    }

    main_scene->exit();

    return 0;
}

void move_camera(GLFWwindow* window)
{
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        if(last_x != 0)
        {
            vec3 rotation = main_scene->get_camera()->get_rotation();
            rotation.x -= CAMERA_ROTATE_SPEED * (last_y - y);
            rotation.y -= CAMERA_ROTATE_SPEED * (last_x - x);
            main_scene->get_camera()->set_rotation(rotation);
        }

        last_x = x;
        last_y = y;
    }
    else
    {
        last_x = last_y = 0;
    }

    vec3 position = main_scene->get_camera()->get_position();

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        position += main_scene->get_camera()->get_forward() * main_scene->get_delta_time() * CAMERA_MOVE_SPEED;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        position -= main_scene->get_camera()->get_forward() * main_scene->get_delta_time() * CAMERA_MOVE_SPEED;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        position += main_scene->get_camera()->get_right() * main_scene->get_delta_time() * CAMERA_MOVE_SPEED;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        position -= main_scene->get_camera()->get_right() * main_scene->get_delta_time() * CAMERA_MOVE_SPEED;
    }

    main_scene->get_camera()->set_position(position);
}

void rotate_crate()
{
    if(crate != nullptr)
    {
        vec3 rotation = crate->get_rotation();
        rotation.x -= CRATE_ROTATE_SPEED * main_scene->get_delta_time();
        rotation.z -= CRATE_ROTATE_SPEED * main_scene->get_delta_time();

        crate->set_rotation(rotation);
    }
}