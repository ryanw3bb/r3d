//
// Created by Ryan on 19/05/2018.
//

#include "mesh_renderer.hpp"
#include "../load/load_mesh.hpp"

using namespace r3d;

mesh_renderer::mesh_renderer(std::string model_path, r3d::material * material)
{
    name = "mesh_renderer";

    this->material = material;

    // Read file
    load_mesh(model_path.c_str(), indices, vertices, uvs, normals);

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

    printf("Add mesh renderer: %s [indices: %lu]\n", model_path.c_str(), indices.size());
}

void mesh_renderer::render(glm::mat4 projection, glm::mat4 view, std::vector<r3d::light *> lights)
{
    // calculate mvp matrix per model
    /*glm::mat4 model = (*it)->get_transform();
    glm::mat4 mvp = projection * view * model;

    // use our shader
    glUseProgram(material->shader->program);

    // Send our transformation to the currently bound shader
    glUniformMatrix4fv(material->shader->mvp_matrix, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(material->shader->model_matrix, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(material->shader->view_matrix, 1, GL_FALSE, &view[0][0]);

    // setting light uniforms
    glUniform3f(material->shader->light_world_pos, lights.front()->position.x, lights.front()->position.y, lights.front()->position.z);
    glUniform3f(material->shader->color, lights.front()->color.x, lights.front()->color.y, lights.front()->color.z);
    glUniform1f(material->shader->intensity, lights.front()->intensity);

    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, material->texture);
    // Set our sampler to use Texture Unit 0
    glUniform1i(material->shader->texture_sampler, 0);

    // vao
    glBindVertexArray(vertex_array_object);

    // vertex buffer
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // uv buffer
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // normal buffer
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);

    glBindVertexArray(0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);*/
}