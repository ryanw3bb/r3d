#ifndef LOAD_MESH_H
#define LOAD_MESH_H

// uncomment to use tinyobjloader instead of assimp to load meshes
//#define USE_TINY_OBJ

#include "../core/gl_includes.hpp"

namespace r3d
{
#ifdef USE_TINY_OBJ
	bool load_mesh(
			std::string path,
			std::vector<glm::vec3> &vertices,
			std::vector<glm::vec2> &uvs,
			std::vector<glm::vec3> &normals
	);
#else
	bool load_mesh(
		std::string path,
		std::vector<unsigned short> &indices,
		std::vector<glm::vec3> &vertices,
		std::vector<glm::vec2> &uvs,
		std::vector<glm::vec3> &normals,
		std::vector<glm::vec3> &tangents,
		bool flip_uvs = false,
		bool calculate_tangents = false
	);
#endif
}

#endif
