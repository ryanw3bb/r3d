//
// Created by Ryan on 17/10/2018.
//

#ifndef R3D_FPS_HPP
#define R3D_FPS_HPP

#include <string>
#include <vector>
#include "../render/gl_includes.hpp"

namespace r3d
{
	class fps
	{
	public:
		void render();

	private:
		const int REFRESH_RATE = 30;

		double last_time;
		std::vector<double> frame_times;
		double frame_time = 0.01;
	};
}

#endif //R3D_FPS_HPP