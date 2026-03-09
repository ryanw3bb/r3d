//
// Created by Ryan on 06/03/2026.
//

#ifndef R3D_FREE_CAMERA_HPP
#define R3D_FREE_CAMERA_HPP

#include "camera.hpp"
#include "../render/gl_window.hpp"

namespace r3d
{
	class free_camera : public camera
	{
	public:
		float move_speed = 3.0f;
		float rotate_speed = 0.005f;
		float scroll_speed = 1.0f;
		float pan_speed = 0.005f;

		free_camera() : camera() {}

		void init_input(r3d::gl_window& window);

		void process_input(GLFWwindow* window, float delta_time);

	private:
		double last_x = 0;
		double last_y = 0;
		double pan_last_x = 0;
		double pan_last_y = 0;
	};
}

#endif //R3D_FREE_CAMERA_HPP
