//
// Created by Ryan on 2019-01-05.
//

#ifndef R3D_CANVAS_HPP
#define R3D_CANVAS_HPP

#include <memory>
#include "../render/gl_includes.hpp"
#include "../util/stats.hpp"
#include "../../external/include/imgui/imgui.h"
#include "../../external/include/imgui/imgui_impl_glfw.h"
#include "../../external/include/imgui/imgui_impl_opengl3.h"

namespace r3d
{
	class ui
	{
	public:
		ui() = default;

		void init(GLFWwindow* window);

		void pre_render();

		void post_render();

		void shutdown();

	private:
		std::shared_ptr<fps> stats;
	};
}


#endif //R3D_CANVAS_HPP
