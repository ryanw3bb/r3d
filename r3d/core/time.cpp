//
// Created by Ryan on 08/06/2018.
//

#include "time.hpp"
#include "gl_includes.hpp"

using namespace r3d;

time::time()
{
    last_time = glfwGetTime();
}

void time::update()
{
    current_time = glfwGetTime();
    delta_time = float(current_time - last_time);
    last_time = current_time;
}