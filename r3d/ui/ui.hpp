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
	class scene;
	class game_object;

	class ui
	{
	public:
		ui() = default;

		void init(GLFWwindow* window);

		void set_scene(scene* s) { current_scene = s; }

		void pre_render();

		void post_render();

		bool wants_input() const;

		void shutdown();

	private:
		void render_stats();
		void render_hierarchy();
		void render_properties();

		std::shared_ptr<fps> stats;
		scene* current_scene = nullptr;
		std::weak_ptr<game_object> selected_object;
		int selected_light_index = -1;
		bool camera_selected = false;

		float hierarchy_width = 220.0f;
		float properties_width = 220.0f;
		static constexpr float STATUS_BAR_HEIGHT = 24.0f;
		static constexpr float MIN_PANEL_WIDTH = 150.0f;
		static constexpr float MAX_PANEL_WIDTH = 500.0f;
	};
}


#endif //R3D_CANVAS_HPP
