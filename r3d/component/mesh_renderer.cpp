//
// Created by Ryan on 19/05/2018.
//

#include "mesh_renderer.hpp"
#include "../load/load_mesh.hpp"

using namespace r3d;

mesh_renderer::mesh_renderer(const char* model_path, r3d::material* material)
{
    this->material = material;

    // Read file
    load_mesh(model_path, indices, vertices, uvs, normals);

    // Vertex Array Object (the boss)
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    // Vertex buffer
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

    // Remove bindings
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    printf("Add mesh_renderer: %s [indices: %lu]\n", model_path, indices.size());
}

void mesh_renderer::render(glm::mat4 model, glm::mat4 view, glm::mat4 projection, std::vector<r3d::light*> lights)
{
    // set camera uniforms
    material->shader->set_camera_uniforms(model, view, projection);

    // set light uniforms
    material->shader->set_light_uniforms(lights.front());

    // use texture
    material->bind();

    // vao
    glBindVertexArray(vertex_array_object);

    // vertex buffer
    glEnableVertexAttribArray(material->shader->get_vertex_identifier());
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(material->shader->get_vertex_identifier(), sizeof(glm::vec3) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, 0, (void*)0);

    // uv buffer
    glEnableVertexAttribArray(material->shader->get_uv_identifier());
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glVertexAttribPointer(material->shader->get_uv_identifier(), sizeof(glm::vec2) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, 0, (void*)0);

    // normal buffer
    glEnableVertexAttribArray(material->shader->get_normal_identifier());
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glVertexAttribPointer(material->shader->get_normal_identifier(), sizeof(glm::vec3) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, 0, (void*)0);

    // index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);

    glDisableVertexAttribArray(material->shader->get_vertex_identifier());
    glDisableVertexAttribArray(material->shader->get_uv_identifier());
    glDisableVertexAttribArray(material->shader->get_normal_identifier());

    glBindVertexArray(0);
}

void mesh_renderer::destroy()
{
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &uv_buffer);
    glDeleteBuffers(1, &normal_buffer);
    glDeleteTextures(1, &material->texture);
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(material->shader->get_program());
};