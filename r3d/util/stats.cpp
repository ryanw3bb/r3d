//
// Created by Ryan on 17/10/2018.
//

#include "stats.hpp"

using namespace r3d;

void fps::update()
{
	double current_time = glfwGetTime();
	double elapsed = current_time - last_time;
	last_time = current_time;

	if (elapsed > 0)
	{
		interval_elapsed += elapsed;
		frame_count++;
	}

	if (interval_elapsed >= REFRESH_INTERVAL)
	{
		frame_time = interval_elapsed / frame_count;
		interval_elapsed = 0;
		frame_count = 0;
	}
}

int fps::get_fps() const
{
	return round(1.0 / frame_time);
}

double fps::get_frame_time() const
{
	return frame_time * 1000.0;
}
