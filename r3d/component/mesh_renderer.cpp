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
    load_mesh(model_path, indices, vertices, uvs, normals, tangents, bitangents, true, material->shader->uses_normal_map);

    size_t v_size = vertices.size() * sizeof(glm::vec3);
    size_t n_size = normals.size() * sizeof(glm::vec3);
    size_t uv_size = uvs.size() * sizeof(glm::vec2);
    size_t t_size = tangents.size() * sizeof(glm::vec3);
    size_t b_size = bitangents.size() * sizeof(glm::vec3);
    //size_t vertices_col_size = vertices_color.size() * sizeof(glm::vec4);

    size_t total = v_size + n_size + uv_size + t_size + b_size;

    // create and bind vertex array object
    // saves info about which vbo is connected to each attribute in shader
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    // create vertex buffer object and bind our mesh data
    // we use only 1 vbo to hold our data and offset for each attribute
    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object); 
    glBufferData(GL_ARRAY_BUFFER, total, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, v_size, &vertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, v_size, n_size, &normals[0]);
    glBufferSubData(GL_ARRAY_BUFFER, (v_size + n_size), uv_size, &uvs[0]);
    glBufferSubData(GL_ARRAY_BUFFER, (v_size + n_size + t_size), t_size, &tangents[0]);
    glBufferSubData(GL_ARRAY_BUFFER, (v_size + n_size + t_size + b_size), b_size, &bitangents[0]);
    //glBufferSubData(GL_ARRAY_BUFFER, (vtx + nrm + txc + tng + btng), vtx_col, &verticesColor[0]); 

    // create element buffer object to hold our indices
    glGenBuffers(1, &indices_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

    // point buffer locations to shader attribute locations
    glVertexAttribPointer(material->shader->get_vertex_identifier(), 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) 0);
    glVertexAttribPointer(material->shader->get_normal_identifier(), 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) v_size);
    glVertexAttribPointer(material->shader->get_uv_identifier(), 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) (v_size + n_size));

    // enable shader attributes
    glEnableVertexAttribArray(material->shader->get_vertex_identifier());
    glEnableVertexAttribArray(material->shader->get_uv_identifier());
    glEnableVertexAttribArray(material->shader->get_normal_identifier());

    // only use these if we're using a normal map
    if(material->shader->uses_normal_map)
    {
        glVertexAttribPointer(material->shader->get_tangent_identifier(), 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) (v_size + n_size + uv_size));
        glVertexAttribPointer(material->shader->get_bitangent_identifier(), 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) (v_size + n_size + uv_size + t_size));
        glEnableVertexAttribArray(material->shader->get_tangent_identifier());
        glEnableVertexAttribArray(material->shader->get_bitangent_identifier());
    }

    printf("Add mesh_renderer: %s [vertices: %lu]\n", model_path, vertices.size());
}

void mesh_renderer::render(glm::mat4 model, glm::mat4 view, glm::mat4 projection, std::vector<r3d::light*> lights)
{
    // use texture
    material->bind();

    // set camera uniforms
    material->shader->set_camera_uniforms(model, view, projection);

    // set light uniforms
    material->shader->set_light_uniforms(lights.front());

    // vao
    glBindVertexArray(vertex_array_object);

    // draw our object
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);
}

void mesh_renderer::destroy()
{
    glDeleteTextures(1, &material->diffuse_texture);
    glDeleteTextures(1, &material->normal_texture);
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(material->shader->get_program());
};