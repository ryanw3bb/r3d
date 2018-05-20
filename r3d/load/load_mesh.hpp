#ifndef OBJLOADER_H
#define OBJLOADER_H

bool load_mesh(
		const char *path,
		std::vector<unsigned short> &indices,
		std::vector<glm::vec3> &vertices,
		std::vector<glm::vec2> &uvs,
		std::vector<glm::vec3> &normals
);

#endif