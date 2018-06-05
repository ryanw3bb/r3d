//
// Created by Ryan on 26/03/2018.
//

#include "main.hpp"
#include "r3d/scene.hpp"
#include "r3d/core/game_object.hpp"
#include "r3d/core/light.hpp"
#include "r3d/component/mesh_renderer.hpp"

const int width = 1024;
const int height = 768;

int main()
{
    r3d::scene * scene = new r3d::scene(width, height);

    r3d::shader * diffuse = new r3d::shader("shaders/diffuse_vert.vertexshader", "shaders/diffuse_frag.fragmentshader");
    r3d::mesh_renderer * render_object = new r3d::mesh_renderer("assets/suzanne.obj", new r3d::material("assets/uvmap.dds", diffuse));

    r3d::game_object * monkey = new r3d::game_object("Monkey", glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
    monkey->add_component(render_object);
    scene->add_object(monkey);

    r3d::game_object * monkey2 = new r3d::game_object("Monkey 2", glm::vec3(5, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
    monkey2->add_component(render_object);
    scene->add_object(monkey2);

    r3d::light * main_light = new r3d::light(glm::vec3(4, 4, 4), glm::vec3(1, 1, 1), 50.0f);
    scene->add_light(main_light);

    while(scene->shouldUpdate)
    {
        scene->update();
    }

    scene->exit();

    return 0;
}