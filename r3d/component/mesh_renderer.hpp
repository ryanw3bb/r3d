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
    class camera;

    class mesh_renderer : public component
    {
    public:
        mesh_renderer();

        mesh_renderer(const char* model_path, r3d::material* material, bool debug = false);

        void render(glm::mat4 model, r3d::camera* main_camera, std::vector<r3d::light*> lights);

        void destroy();

    private:
        std::vector<unsigned short> indices;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec3> tangents;
        std::vector<glm::vec3> bitangents;
        GLuint vertex_array_object;
        GLuint vertex_buffer_object;
        GLuint vertex_buffer;
        GLuint uv_buffer;
        GLuint normal_buffer;
        GLuint indices_buffer;
        GLuint tangent_buffer;
        GLuint bitangent_buffer;
        r3d::material *material;
    };
}

#endif //R3D_RENDEROBJECT_HPP