//
// Created by ryan.webb on 22/05/2019.
//

#ifndef R3D_BOUNDS_HPP
#define R3D_BOUNDS_HPP

#include <vector>
#include "../render/gl_includes.hpp"

namespace r3d
{
	class bounds
	{
	public:
		glm::vec3 centre;
		glm::vec3 extents;
		glm::vec3 min;
		glm::vec3 max;
		std::vector<glm::vec3> corners;

		bounds() {}

		void update() {
			corners.clear();
			corners.push_back(glm::vec3(min.x, min.y, min.z));
			corners.push_back(glm::vec3(max.x, min.y, min.z));
			corners.push_back(glm::vec3(min.x, min.y, max.z));
			corners.push_back(glm::vec3(max.x, min.y, max.z));
			corners.push_back(glm::vec3(min.x, max.y, min.z));
			corners.push_back(glm::vec3(max.x, max.y, min.z));
			corners.push_back(glm::vec3(min.x, max.y, max.z));
			corners.push_back(glm::vec3(max.x, max.y, max.z));
		}
	};
}

#endif //R3D_BOUNDS_HPP
