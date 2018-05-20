//
// Created by Ryan on 16/05/2018.
//

#include "game_object.hpp"

using namespace r3d;

game_object::game_object(std::string name)
{
    game_object::name = name;

    printf("new game_object: %s\n", name.c_str());
}

void game_object::add_component(r3d::component * component)
{
    components.push_back(component);

    printf("add component: %s\n", typeid(component).name());
}