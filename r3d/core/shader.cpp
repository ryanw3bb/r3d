//
// Created by Ryan on 21/05/2018.
//

#include "shader.hpp"
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

    glUseProgram(program);
}

void shader::bind()
{
    glUseProgram(program);
}