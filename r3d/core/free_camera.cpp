//
// Created by Ryan on 06/03/2026.
//

#include "free_camera.hpp"

using namespace r3d;

void free_camera::process_input(GLFWwindow* window, float delta_time)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		if (last_x != 0)
		{
			glm::vec3 rot = get_rotation();
			rot.x = fmod(rot.x + (rotate_speed * (float)(last_y - y)), glm::two_pi<float>());
			rot.y = fmod(rot.y + (rotate_speed * (float)(last_x - x)), glm::two_pi<float>());
			set_rotation(rot);
		}

		last_x = x;
		last_y = y;
	}
	else
	{
		last_x = last_y = 0;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE))
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		if (pan_last_x != 0)
		{
			glm::vec3 offset = right * (float)(pan_last_x - x) * pan_speed
				+ up * (float)(y - pan_last_y) * pan_speed;
			set_position(get_position() + offset);
		}

		pan_last_x = x;
		pan_last_y = y;
	}
	else
	{
		pan_last_x = pan_last_y = 0;
	}

	glm::vec3 pos = get_position();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		pos += forward * delta_time * move_speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		pos -= forward * delta_time * move_speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		pos += right * delta_time * move_speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		pos -= right * delta_time * move_speed;
	}

	set_position(pos);
}

void free_camera::init_input(r3d::gl_window& window)
{
	window.set_scroll_callback([this](double yoffset)
	{
		glm::vec3 pos = get_position();
		pos += forward * (float)yoffset * scroll_speed;
		set_position(pos);
	});
}
