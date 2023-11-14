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

	class mesh_renderer
	{
	public:
		std::shared_ptr<r3d::mesh> mesh; // TODO: should these be unique_ptrs?
		std::shared_ptr<r3d::material> material;
		std::shared_ptr<r3d::shader> shader;
		std::shared_ptr<r3d::bounds> bounds;

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
			std::vector<r3d::light>& lights,
			bool change_shader = true,
			bool bind_vao = true,
			bool bind_textures = true);

		void destroy();

	private:
		GLuint vertex_array_object;
		GLuint vertex_buffer_object;
		GLuint indices_buffer;
	};
}

#endif //R3D_RENDEROBJECT_HPP
