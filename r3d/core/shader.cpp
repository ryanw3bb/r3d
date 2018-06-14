//
// Created by Ryan on 21/05/2018.
//

#include "shader.hpp"
#include "light.hpp"
#include "../load/load_shader.hpp"

using namespace r3d;

shader::shader(id i): shader_id(i)
{
    switch(shader_id)
    {
        case id::UNLIT_VERT_COLOR:
            init("r3d/shaders/unlit_vert_color.vertexshader", "r3d/shaders/unlit_vert_color.fragmentshader");
            break;

        case id::UNLIT_TEXTURE:
            init("r3d/shaders/unlit_texture.vertexshader", "r3d/shaders/unlit_texture.fragmentshader");
            break;

        case id::DIFFUSE:
            init("r3d/shaders/diffuse_texture.vertexshader", "r3d/shaders/diffuse_texture.fragmentshader");
            break;
    }
}

shader::shader(const char* vert, const char* frag)
{
    init(vert, frag);
}

void shader::init(const char* vert, const char* frag)
{
    program = load_shader(vert, frag);

    // Get handles for our uniforms
    mvp_matrix = glGetUniformLocation(program, "MVP");
    view_matrix = glGetUniformLocation(program, "V");
    model_matrix = glGetUniformLocation(program, "M");
    texture_sampler = glGetUniformLocation(program, "Sampler");
    light_world_pos = glGetUniformLocation(program, "LightPosition_worldspace");
    light_color = glGetUniformLocation(program, "LightColor");
    light_intensity = glGetUniformLocation(program, "LightPower");

    // attribute identifiers
    vertex_identifier = glGetAttribLocation(program, "vertexPosition_modelspace");
    uv_identifier = glGetAttribLocation(program, "vertexUV");
    normal_identifier = glGetAttribLocation(program, "vertexNormal_modelspace");

    glUseProgram(program);
}

void shader::set_camera_uniforms(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
    glm::mat4 mvp = projection * view * model;

    glUniformMatrix4fv(mvp_matrix, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(model_matrix, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(view_matrix, 1, GL_FALSE, &view[0][0]);
}

void shader::set_light_uniforms(r3d::light* light1)
{
    glUniform3f(light_world_pos, light1->position.x, light1->position.y, light1->position.z);
    glUniform3f(light_color, light1->color.x, light1->color.y, light1->color.z);
    glUniform1f(light_intensity, light1->intensity);
}