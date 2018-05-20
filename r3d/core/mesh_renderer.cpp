//
// Created by Ryan on 19/05/2018.
//

#include "mesh_renderer.hpp"
#include "../load/load_mesh.hpp"
#include "../load/load_texture.hpp"

using namespace r3d;

mesh_renderer::mesh_renderer(std::string model_path, std::string tex_path)
{
    // load bmp, get texture id
    texture = load_dds(tex_path.c_str());

    // Read file
    load_mesh(model_path.c_str(), indices, vertices, uvs, normals);

    // 1. Vertex buffer
    // Generate 1 buffer, put the resulting identifier in vertex_buffer
    glGenBuffers(1, &vertex_buffer);
    // The following commands will talk about our 'vertex_buffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    // 2. UV buffer (using instead of colour buffer)
    glGenBuffers(1, &uv_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    // 3. Normal buffer
    glGenBuffers(1, &normal_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

    printf("add mesh renderer: %s  vert count: %lu\n", model_path.c_str(), vertices.size());
}