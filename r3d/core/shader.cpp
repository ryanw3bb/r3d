//
// Created by Ryan on 21/05/2018.
//

#include "shader.hpp"
#include "light.hpp"
#include "../load/load_shader.hpp"

using namespace r3d;

shader::shader(id shader_id)
{
    switch(shader_id)
    {
        case id::UNLIT_TEXTURE:
            init("r3d/shaders/unlit_texture.vert", "r3d/shaders/unlit_texture.frag");
            break;

        case id::DIFFUSE_COLOR:
            uses_lighting = true;
            init("r3d/shaders/diffuse_color.vert", "r3d/shaders/diffuse_color.frag");
            break;

        case id::DIFFUSE_TEXTURE:
            uses_lighting = true;
            init("r3d/shaders/diffuse_texture.vert", "r3d/shaders/diffuse_texture.frag");
            break;

        case id::DIFFUSE_TEXTURE_BUMP:
            uses_lighting = true;
            uses_normal_map = true;
            init("r3d/shaders/diffuse_texture_bump.vert", "r3d/shaders/diffuse_texture_bump.frag");
            break;

        case id::VERTEX_COLOR:
            // todo: vertex color shader
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
    mvp_matrix = glGetUniformLocation(program, "mvp");
    view_matrix = glGetUniformLocation(program, "view");
    model_matrix = glGetUniformLocation(program, "model");
    texture_sampler = glGetUniformLocation(program, "sampler");

    if(uses_lighting)
    {
        light_world_pos = glGetUniformLocation(program, "light_position_world");
        light_color = glGetUniformLocation(program, "light_color");
        light_intensity = glGetUniformLocation(program, "light_power");
    }

    if(uses_normal_map)
    {
        model_view_3x3_matrix = glGetUniformLocation(program, "model_view_3x3");
        normal_sampler = glGetUniformLocation(program, "normal_sampler");
    }

    // attribute identifiers
    vertex_identifier = glGetAttribLocation(program, "vert_position_model");
    uv_identifier = glGetAttribLocation(program, "vert_uv_model");

    if(uses_lighting)
    {
        normal_identifier = glGetAttribLocation(program, "vert_normal_model");
    }

    if(uses_normal_map)
    {
        tangent_identifier = glGetAttribLocation(program, "vert_tangent_model");
        bitangent_identifier = glGetAttribLocation(program, "vert_bitangent_model");
    }

    glUseProgram(program);
}

void shader::set_camera_uniforms(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
    glm::mat4 mvp = projection * view * model;
    glm::mat3 mv3x3 = glm::mat3(view * model);

    glUniformMatrix4fv(mvp_matrix, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(model_matrix, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(view_matrix, 1, GL_FALSE, &view[0][0]);

    if(uses_normal_map)
    {
        glUniformMatrix3fv(model_view_3x3_matrix, 1, GL_FALSE, &mv3x3[0][0]);
    }
}

void shader::set_light_uniforms(r3d::light* light1)
{
    if(uses_lighting)
    {
        glUniform3f(light_world_pos, light1->position.x, light1->position.y, light1->position.z);
        glUniform3f(light_color, light1->color.x, light1->color.y, light1->color.z);
        glUniform1f(light_intensity, light1->intensity);
    }
}