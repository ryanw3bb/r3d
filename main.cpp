//
// Created by Ryan on 26/03/2018.
//

#include "main.hpp"
#include "r3d/scene.hpp"
#include "r3d/core/game_object.hpp"
#include "r3d/core/mesh_renderer.hpp"

const int width = 1024;
const int height = 768;

int main()
{
    r3d::scene * scene = new r3d::scene(width, height);

    r3d::game_object * monkey = new r3d::game_object("Monkey");
    r3d::mesh_renderer * renderer = new r3d::mesh_renderer("assets/suzanne.obj", "assets/uvmap.dds");

    monkey->add_component(renderer);
    scene->add_object(monkey);

    while(scene->shouldUpdate)
    {
        scene->update();
    }

    scene->exit();

    return 0;
}