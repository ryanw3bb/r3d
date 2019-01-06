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
            load("r3d/shaders/unlit_texture.vert", "r3d/shaders/unlit_texture.frag");
            break;

        case id::DIFFUSE_COLOR:
            uses_lighting = true;
            load("r3d/shaders/diffuse_color.vert", "r3d/shaders/diffuse_color.frag");
            break;

        case id::DIFFUSE_TEXTURE:
            uses_lighting = true;
            load("r3d/shaders/diffuse_texture.vert", "r3d/shaders/diffuse_texture.frag");
            break;

        case id::DIFFUSE_TEXTURE_BUMP:
            uses_lighting = true;
            uses_normal_map = true;
            load("r3d/shaders/diffuse_texture_bump.vert", "r3d/shaders/diffuse_texture_bump.frag");
            break;

        case id::VERTEX_COLOR:
            // todo: vertex color shader
            break;

        case id::UI:
            load("r3d/shaders/ui_text.vert", "r3d/shaders/ui_text.frag");
            break;
    }

    bind_uniforms();
}

void shader::load(std::string vert, std::string frag)
{
    program = load_shader(vert, frag);
}

void shader::bind_uniforms()
{
    // Get handles for our uniforms
    mvp_matrix = glGetUniformLocation(program, "mvp");
    view_matrix = glGetUniformLocation(program, "view");
    model_matrix = glGetUniformLocation(program, "model");
    projection_matrix = glGetUniformLocation(program, "projection");
    texture_sampler = glGetUniformLocation(program, "albedoSampler");
    tint = glGetAttribLocation(program, "tint");
    camera_world_pos = glGetUniformLocation(program, "viewPos");

    if(uses_lighting)
    {
        light_world_pos = glGetUniformLocation(program, "lightPos");
        light_color = glGetUniformLocation(program, "lightColor");
        light_intensity = glGetUniformLocation(program, "lightPower");
    }

    if(uses_normal_map)
    {
        normal_sampler = glGetUniformLocation(program, "normalSampler");
    }

    // attribute identifiers
    vertex_identifier = glGetAttribLocation(program, "position");
    uv_identifier = glGetAttribLocation(program, "texCoords");

    if(uses_lighting)
    {
        normal_identifier = glGetAttribLocation(program, "normal");
    }

    if(uses_normal_map)
    {
        tangent_identifier = glGetAttribLocation(program, "tangent");
        bitangent_identifier = glGetAttribLocation(program, "bitangent");
    }
}

void shader::set_camera_uniforms(glm::mat4& projection)
{
    glUniformMatrix4fv(projection_matrix, 1, GL_FALSE, &projection[0][0]);
}

void shader::set_camera_uniforms(glm::mat4& model, glm::mat4& view, glm::mat4& projection, glm::vec3& camera_pos)
{
    glm::mat4 mvp = projection * view * model;

    glUniformMatrix4fv(mvp_matrix, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(model_matrix, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(view_matrix, 1, GL_FALSE, &view[0][0]);

    glUniform3f(camera_world_pos, camera_pos.x, camera_pos.y, camera_pos.z);
}

void shader::set_light_uniforms(std::vector<r3d::light>& lights)
{
    if(uses_lighting)
    {
        glUniform3f(light_world_pos, lights.front().position.x, lights.front().position.y, lights.front().position.z);
        glUniform3f(light_color, lights.front().color.x, lights.front().color.y, lights.front().color.z);
        glUniform1f(light_intensity, lights.front().intensity);
    }
}

void shader::use()
{
    glUseProgram(program);
}