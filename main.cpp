//
// Created by Ryan on 26/03/2018.
//

#include "main.hpp"
#include "r3d/scene.hpp"
#include "r3d/core/game_object.hpp"
#include "r3d/core/light.hpp"
#include "r3d/core/time.hpp"
#include "r3d/core/shader.hpp"
#include "r3d/component/mesh_renderer.hpp"

const int WIDTH = 1024;
const int HEIGHT = 768;
const float CAMERA_MOVE_SPEED = 3.0f;
const float CAMERA_ROTATE_SPEED = 0.05f;
const float CRATE_ROTATE_SPEED = 0.5f;

double last_x, last_y;
r3d::game_object* crate;
r3d::game_object* crate_bump;

int main()
{
    scene = new r3d::scene(WIDTH, HEIGHT);
    scene->get_camera()->set_position(glm::vec3(0, 0, 8));
    scene->get_camera()->set_rotation(glm::vec3(0, 180, 0));

    r3d::light* main_light = new r3d::light(glm::vec3(0, 7, 0), glm::vec3(0.9, 0.9, 0.9), 45.0f);
    scene->add_light(main_light);

    r3d::shader* diffuse = new r3d::shader(r3d::shader::id::DIFFUSE_TEXTURE);
    r3d::material* crate_diffuse_mat = new r3d::material("assets/crate_color.png", diffuse);
    r3d::mesh_renderer* crate_renderer = new r3d::mesh_renderer("assets/crate.obj", crate_diffuse_mat);
    crate_bump = new r3d::game_object("crate", glm::vec3(-2, 0, 0), glm::vec3(-90, 0, -90), glm::vec3(0.01, 0.01, 0.01));
    crate_bump->add_renderer(crate_renderer);
    scene->add_object(crate_bump);

    r3d::shader* diffuse_bump = new r3d::shader(r3d::shader::id::DIFFUSE_TEXTURE_BUMP);
    r3d::material* crate_bump_mat = new r3d::material("assets/crate_color.png", "assets/crate_normal.png", diffuse_bump);
    r3d::mesh_renderer* crate_bump_renderer = new r3d::mesh_renderer("assets/crate.obj", crate_bump_mat);
    crate = new r3d::game_object("crate_bump", glm::vec3(2, 0, 0), glm::vec3(-90, 0, -90), glm::vec3(0.01, 0.01, 0.01));
    crate->add_renderer(crate_bump_renderer);
    scene->add_object(crate);

    while(scene->get_should_update())
    {
        move_camera(scene->get_window());
        rotate_crates();
        scene->update();
    }

    scene->exit();

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
            glm::vec3 rotation = scene->get_camera()->get_rotation();
            rotation.x -= CAMERA_ROTATE_SPEED * (last_y - y);
            rotation.y -= CAMERA_ROTATE_SPEED * (last_x - x);
            scene->get_camera()->set_rotation(rotation);
        }

        last_x = x;
        last_y = y;
    }
    else
    {
        last_x = last_y = 0;
    }

    glm::vec3 position = scene->get_camera()->get_position();

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        position += scene->get_camera()->get_forward() * scene->get_delta_time() * CAMERA_MOVE_SPEED;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        position -= scene->get_camera()->get_forward() * scene->get_delta_time() * CAMERA_MOVE_SPEED;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        position += scene->get_camera()->get_right() * scene->get_delta_time() * CAMERA_MOVE_SPEED;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        position -= scene->get_camera()->get_right() * scene->get_delta_time() * CAMERA_MOVE_SPEED;
    }

    scene->get_camera()->set_position(position);
}

void rotate_crates()
{
    glm::vec3 rotation = crate->get_rotation();
    rotation.x -= CRATE_ROTATE_SPEED;
    rotation.z -= CRATE_ROTATE_SPEED;

    crate->set_rotation(rotation);
    crate_bump->set_rotation(rotation);
}