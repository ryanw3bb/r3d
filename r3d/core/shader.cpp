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

    // Get a handle for our "MVP" uniform
    mvp_matrix = glGetUniformLocation(program, "MVP");
    view_matrix = glGetUniformLocation(program, "V");
    model_matrix = glGetUniformLocation(program, "M");

    // Get a handle for our "myTextureSampler" uniform
    texture_sampler = glGetUniformLocation(program, "Sampler");

    glUseProgram(program);
    light_world_pos = glGetUniformLocation(program, "LightPosition_worldspace");
}