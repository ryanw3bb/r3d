//
// Created by Ryan on 21/05/2018.
//

#include "shader.hpp"
#include "../load/load_shaders.hpp"

using namespace r3d;

shader::shader(std::string vert, std::string frag)
{
    // shader program
    program = load_shaders(vert.c_str(), frag.c_str());

    // Get handles for our uniforms
    mvp_matrix = glGetUniformLocation(program, "MVP");
    view_matrix = glGetUniformLocation(program, "V");
    model_matrix = glGetUniformLocation(program, "M");
    texture_sampler = glGetUniformLocation(program, "Sampler");
    light_world_pos = glGetUniformLocation(program, "LightPosition_worldspace");
    color = glGetUniformLocation(program, "LightColor");
    intensity = glGetUniformLocation(program, "LightPower");

    glUseProgram(program);
}

void shader::bind()
{
    glUseProgram(program);
}