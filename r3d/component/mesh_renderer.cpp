//
// Created by Ryan on 19/05/2018.
//

#include <memory>
#include "mesh_renderer.hpp"
#include "../load/load_mesh.hpp"
#include "../utils/debug.hpp"
#include "../core/camera.hpp"

using namespace r3d;

mesh_renderer::mesh_renderer(std::string model_path,
        shader::id shader_type,
        std::string diffuse_map,
        std::string normal_map,
        bool debug)
{
    shader = std::make_shared<r3d::shader>(shader_type);
    material = std::make_shared<r3d::material>(diffuse_map, normal_map, shader);
    mesh = std::make_shared<r3d::mesh>();

    // Read file
    load_mesh(model_path,
            mesh->indices,
            mesh->vertices,
            mesh->uvs,
            mesh->normals,
            mesh->tangents,
            mesh->bitangents,
            true,
            material->shader->uses_normal_map);

    size_t v_size = mesh->vertices.size() * sizeof(glm::vec3);
    size_t n_size = mesh->normals.size() * sizeof(glm::vec3);
    size_t uv_size = mesh->uvs.size() * sizeof(glm::vec2);
    size_t t_size = mesh->tangents.size() * sizeof(glm::vec3);
    size_t b_size = mesh->bitangents.size() * sizeof(glm::vec3);
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
    glBufferSubData(GL_ARRAY_BUFFER, 0, v_size, &mesh->vertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, v_size, n_size, &mesh->normals[0]);
    glBufferSubData(GL_ARRAY_BUFFER, (v_size + n_size), uv_size, &mesh->uvs[0]);
    glBufferSubData(GL_ARRAY_BUFFER, (v_size + n_size + uv_size), t_size, &mesh->tangents[0]);
    glBufferSubData(GL_ARRAY_BUFFER, (v_size + n_size + uv_size + t_size), b_size, &mesh->bitangents[0]);
    //glBufferSubData(GL_ARRAY_BUFFER, (vtx + nrm + txc + tng + btng), vtx_col, &verticesColor[0]); 

    // create element buffer object to hold our indices
    glGenBuffers(1, &indices_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(unsigned short), &mesh->indices[0], GL_STATIC_DRAW);

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

    if(debug)
    {
        r3d::debug* debug_view;

        for(unsigned int i = 0; i < mesh->vertices.size(); i++)
        {
            glm::vec3 p = mesh->vertices[i];
            glm::vec3 n = p + glm::normalize(mesh->normals[i]) * 0.1f;

            debug_view->get_instance()->add_line(p, n, glm::vec3(1, 0, 0));
        }
    }

    printf("Add mesh_renderer: %s [vertices: %lu]\n", model_path.c_str(), mesh->vertices.size());
}

void mesh_renderer::render(glm::mat4 model,
        r3d::camera& main_camera,
        std::vector<r3d::light>& lights,
        bool change_shader,
        bool bind_vao,
        bool bind_textures)
{
    if(change_shader) { shader->use(); }

    if(bind_textures) { material->bind(); }

    // set camera uniforms
    material->shader->set_camera_uniforms(model, main_camera.view, main_camera.projection, main_camera.position);

    // set light uniforms
    material->shader->set_light_uniforms(lights);

    if(bind_vao) { glBindVertexArray(vertex_array_object); }

    // draw our object
    glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_SHORT, (void*)0);
}

void mesh_renderer::destroy()
{
    glDeleteTextures(1, &material->diffuse_texture);
    glDeleteTextures(1, &material->normal_texture);
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteProgram(material->shader->get_program());
}