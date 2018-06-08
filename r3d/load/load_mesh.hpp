#ifndef LOAD_MESH_H
#define LOAD_MESH_H

#include "../core/gl_includes.hpp"

namespace r3d
{
	bool load_mesh(
			const char *path,
			std::vector<unsigned short> &indices,
			std::vector<glm::vec3> &vertices,
			std::vector<glm::vec2> &uvs,
			std::vector<glm::vec3> &normals
	);
}

#endif