//
// Created by Ryan on 17/10/2018.
//

#include "math.h"
#include "stats.hpp"

using namespace r3d;

fps::fps(std::shared_ptr<r3d::font> font, GLfloat x, GLfloat y)
{
    this->position.x = x;
    this->position.y = y;
    this->font = font;
}

void fps::render(GLuint& vertex_buffer_object)
{
    double current_time = glfwGetTime();
    double elapsed = current_time - last_time;
    last_time = current_time;

    if(elapsed > 0)
    {
        frame_times.emplace_back(elapsed);
    }

    if(frame_times.size() >= REFRESH_RATE)
    {
        double sum_of_frame_times = 0;

        for(auto& n : frame_times)
        {
            sum_of_frame_times += n;
        }

        frame_time = sum_of_frame_times / (float)REFRESH_RATE;
        frame_times.clear();
    }

    int fps = round(1.0 / frame_time);
    int ms = round(frame_time * 1000.0);

    data = "r3d\n" + std::to_string(fps) + " fps (" + std::to_string(ms) + "ms)";

    text::render(vertex_buffer_object);
}
