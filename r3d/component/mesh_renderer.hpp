//
// Created by Ryan on 19/05/2018.
//

#ifndef R3D_MESHRENDERER_HPP
#define R3D_MESHRENDERER_HPP

#include <iostream>
#include <vector>

#include "../core/gl_includes.hpp"
#include "../core/material.hpp"
#include "component.hpp"

namespace r3d
{
    class mesh_renderer : public component
    {
        public:
            mesh_renderer(std::string, r3d::material *);

            std::vector<unsigned short> indices;
            std::vector<glm::vec3> vertices;
            std::vector<glm::vec2> uvs;
            std::vector<glm::vec3> normals;
            GLuint vertex_array_object;
            GLuint vertex_buffer;
            GLuint uv_buffer;
            GLuint normal_buffer;
            GLuint indices_buffer;
            r3d::material * material;
    };
}

#endif //R3D_MESHRENDERER_HPP