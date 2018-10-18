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
const float MOVE_SPEED = 3.0f;
const float TURN_SPEED = 0.003f;

int main()
{
    scene = new r3d::scene(WIDTH, HEIGHT);
    scene->get_camera()->set_position(glm::vec3(0, 0, 5));
    scene->get_camera()->set_rotation(glm::vec3(0, 180, 0));

    r3d::shader* diffuse = new r3d::shader(r3d::shader::id::DIFFUSE);
    r3d::mesh_renderer* renderer = new r3d::mesh_renderer("assets/suzanne.obj",
                                                          new r3d::material("assets/uvmap.dds", 
                                                          diffuse));

    r3d::game_object* monkey = new r3d::game_object("Monkeh", glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),
                                                    glm::vec3(1, 1, 1));
    monkey->add_renderer(renderer);
    scene->add_object(monkey);

    r3d::light* main_light = new r3d::light(glm::vec3(4, 4, 4), glm::vec3(1, 1, 1), 50.0f);
    scene->add_light(main_light);

    while(scene->get_should_update())
    {
        get_inputs(scene->get_window());
        scene->update();
    }

    scene->exit();

    return 0;
}

void get_inputs(GLFWwindow* window)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    glm::vec3 rotation = scene->get_camera()->get_rotation();
    rotation.x += TURN_SPEED * float(HEIGHT / 2 - ypos);
    rotation.y += TURN_SPEED * float(WIDTH / 2 - xpos);
    scene->get_camera()->set_rotation(rotation);

    glm::vec3 position = scene->get_camera()->get_position();

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        position += scene->get_camera()->get_forward() * scene->get_delta_time() * MOVE_SPEED;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        position -= scene->get_camera()->get_forward() * scene->get_delta_time() * MOVE_SPEED;
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        position += scene->get_camera()->get_right() * scene->get_delta_time() * MOVE_SPEED;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        position -= scene->get_camera()->get_right() * scene->get_delta_time() * MOVE_SPEED;
    }

    scene->get_camera()->set_position(position);
}