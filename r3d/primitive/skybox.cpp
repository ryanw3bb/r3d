//
// Created by Ryan on 2019-01-11.
//

#include "skybox.hpp"

using namespace r3d;

void skybox::init(std::vector<std::string> faces, r3d::camera& camera)
{
    glGenVertexArrays(1, &vertex_array_object);
    glGenBuffers(1, &vertex_buffer_object);
    glBindVertexArray(vertex_array_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), &verts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    shader_program = load_shader("resources/shaders/unlit_skybox.vert", "resources/shaders/unlit_skybox.frag");
    view_uniform = glGetUniformLocation(shader_program, "view");
    projection_uniform = glGetUniformLocation(shader_program, "projection");

    cubemap_texture = load_cubemap(faces);

    enabled = true;
}

void skybox::render(r3d::camera& camera)
{
    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content

    glUseProgram(shader_program);

    view_matrix = glm::mat4(glm::mat3(camera.view)); // remove translation from view matrix
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, &view_matrix[0][0]);
    glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, &camera.projection[0][0]);

    glBindVertexArray(vertex_array_object);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthFunc(GL_LESS); // set depth function back to default
}