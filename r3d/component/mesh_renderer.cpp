//
// Created by Ryan on 19/05/2018.
//

#include "mesh_renderer.hpp"
#include "../load/load_mesh.hpp"

using namespace r3d;

mesh_renderer::mesh_renderer(std::string model_path, r3d::material * material)
{
    this->material = material;

    // Read file
    load_mesh(model_path.c_str(), indices, vertices, uvs, normals);

    // Vertex Array Object (the boss)
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    // Vertex buffer
    // Generate 1 buffer, put the resulting identifier in vertex_buffer
    glGenBuffers(1, &vertex_buffer);
    // The following commands will talk about our 'vertex_buffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    // UV buffer (using instead of colour buffer)
    glGenBuffers(1, &uv_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    // Normal buffer
    glGenBuffers(1, &normal_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

    // Indices buffer
    glGenBuffers(1, &indices_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    printf("add mesh renderer: %s  vert count: %lu\n", model_path.c_str(), vertices.size());
}