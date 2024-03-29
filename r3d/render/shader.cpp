//
// Created by Ryan on 21/05/2018.
//

#include "shader.hpp"
#include "../core/light.hpp"
#include "../core/camera.hpp"
#include "../load/load_shader.hpp"

using namespace r3d;

shader::shader(id shader_id)
{
    switch(shader_id)
    {
        case id::UNLIT_TEXTURE:
            load("resources/shaders/unlit_texture.vert", "resources/shaders/unlit_texture.frag");
            break;

        case id::DIFFUSE_COLOR:
            uses_lighting = true;
            load("resources/shaders/diffuse_color.vert", "resources/shaders/diffuse_color.frag");
            break;

        case id::DIFFUSE_TEXTURE:
            uses_lighting = true;
            load("resources/shaders/diffuse_texture.vert", "resources/shaders/diffuse_texture.frag");
            break;

        case id::DIFFUSE_TEXTURE_BUMP:
            uses_lighting = true;
            uses_normal_map = true;
            load("resources/shaders/diffuse_texture_bump.vert", "resources/shaders/diffuse_texture_bump.frag");
            break;

        case id::VERTEX_COLOR:
            // todo: vertex color shader
            break;

        case id::UI:
            load("resources/shaders/ui_text.vert", "resources/shaders/ui_text.frag");
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
    }

    // uniforms
    model_matrix = glGetUniformLocation(program, "model");
    view_matrix = glGetUniformLocation(program, "view");
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
}

void shader::set_scene_uniforms(glm::mat4 &projection)
{
    glUniformMatrix4fv(projection_matrix, 1, GL_FALSE, &projection[0][0]);
}

void shader::set_scene_uniforms(r3d::camera &camera, std::vector<r3d::light> &lights)
{
    if(uses_lighting)
    {
        glUniform3fv(light_world_pos, 1, &lights[0].position[0]);
        if(light_color >= 0) { glUniform3fv(light_color, 1, &lights[0].color[0]); }
        if(light_intensity >= 0) { glUniform1f(light_intensity, lights[0].intensity); }
    }

    glUniformMatrix4fv(view_matrix, 1, GL_FALSE, &camera.view[0][0]);
    glUniformMatrix4fv(projection_matrix, 1, GL_FALSE, &camera.projection[0][0]);
    glUniform3fv(camera_world_pos, 1, &camera.position[0]);
}

void shader::set_model_uniforms(glm::mat4 &model)
{
    glUniformMatrix4fv(model_matrix, 1, GL_FALSE, &model[0][0]);
}

void shader::use()
{
    glUseProgram(program);
}