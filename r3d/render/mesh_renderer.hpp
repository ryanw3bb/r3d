//
// Created by Ryan on 19/05/2018.
//

#ifndef R3D_RENDEROBJECT_HPP
#define R3D_RENDEROBJECT_HPP

#include <iostream>
#include <vector>
#include <memory>
#include "../core/bounds.hpp"
#include "../core/light.hpp"
#include "../core/mesh.hpp"
#include "../load/load_mesh.hpp"
#include "../render/gl_includes.hpp"
#include "../render/material.hpp"
#include "../util/debug.hpp"

namespace r3d
{
	// forward declarations
	class camera;
	class game_object;

	struct instance_data
	{
		glm::mat4 transform;
		bool selected;
	};

	class mesh_renderer
	{
	public:
		std::shared_ptr<r3d::mesh> mesh;
		std::shared_ptr<r3d::material> material;
		std::shared_ptr<r3d::shader> shader;
		std::shared_ptr<r3d::bounds> bounds;
		float selection_outline_scale = 1.075f;

		// default constructor & overloads
		mesh_renderer() {}

		mesh_renderer(std::string model_path,
			shader::id shader_type,
			std::string diffuse_map,
			std::string normal_map = "",
			bool debug = false);

		// destructor
		~mesh_renderer()
		{
			printf("Delete mesh_renderer [address: %p]\n", this);
		}

		bool render(std::shared_ptr<r3d::game_object>&,
			r3d::camera& main_camera,
			std::vector<r3d::light>& lights);

		void render_instanced(std::vector<instance_data>& instances,
			r3d::camera& main_camera,
			std::vector<r3d::light>& lights);

		void destroy();

	private:
		void upload_and_draw_instanced(std::vector<glm::mat4>& transforms);

		void render_selection_outline(std::vector<glm::mat4>& selected_transforms,
			r3d::camera& main_camera,
			std::vector<r3d::light>& lights);

		std::unique_ptr<r3d::shader> outline_shader;
		GLuint vertex_array_object;
		GLuint vertex_buffer_object;
		GLuint indices_buffer;
		GLuint instance_buffer;
	};
}

#endif //R3D_RENDEROBJECT_HPP
