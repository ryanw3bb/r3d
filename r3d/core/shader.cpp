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
    texture_sampler = glGetUniformLocation(program, "diffuseSampler");
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

    glUseProgram(program);
}

void shader::set_camera_uniforms(glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 camera_pos)
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