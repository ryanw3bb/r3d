//
// Created by Ryan on 19/05/2018.
//

#ifndef R3D_RENDEROBJECT_HPP
#define R3D_RENDEROBJECT_HPP

#include <iostream>
#include <vector>
#include "../core/light.hpp"
#include "../core/gl_includes.hpp"
#include "../core/material.hpp"
#include "component.hpp"

namespace r3d
{
    class mesh_renderer : public component
    {
    public:
        std::vector<unsigned short> indices;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals;
        GLuint vertex_array_object;
        GLuint vertex_buffer;
        GLuint uv_buffer;
        GLuint normal_buffer;
        GLuint indices_buffer;
        r3d::material *material;

        mesh_renderer();

        mesh_renderer(const char*, r3d::material*);

        void render();
    };
}

#endif //R3D_RENDEROBJECT_HPP