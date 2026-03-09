//
// Created by Ryan on 17/10/2018.
//

#ifndef R3D_FPS_HPP
#define R3D_FPS_HPP

#include "../render/gl_includes.hpp"

namespace r3d
{
	class fps
	{
	public:
		void update();

		int get_fps() const;
		double get_frame_time() const;

	private:
		const double REFRESH_INTERVAL = 0.5;

		double last_time = 0;
		double interval_elapsed = 0;
		int frame_count = 0;
		double frame_time = 0.01;
	};
}

#endif //R3D_FPS_HPP