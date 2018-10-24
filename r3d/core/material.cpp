//
// Created by Ryan on 21/05/2018.
//

#include "material.hpp"
#include "../load/load_texture.hpp"

using namespace r3d;

material::material(r3d::shader* shader) : shader(shader)
{
    
}

material::material(const char* tex_path, r3d::shader* shader) : shader(shader)
{
    texture = load_dds(tex_path);
}

void material::bind()
{
    glUseProgram(shader->get_program());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(shader->get_texture_sampler(), 0);
}