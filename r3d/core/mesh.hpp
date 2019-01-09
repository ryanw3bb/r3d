//
// Created by Ryan on 2018-12-26.
//

#ifndef R3D_MESH_HPP
#define R3D_MESH_HPP

#include <vector>
#include "../core/gl_includes.hpp"

namespace r3d
{
    struct mesh
    {
    public:
        std::vector<unsigned short> indices;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec3> tangents;

        mesh() = default;
    };
}

#endif //R3D_MESH_HPP
