//
// Created by Ryan on 21/05/2018.
//

#include "material.hpp"
#include "../load/load_texture.hpp"

using namespace r3d;

material::material(const char* tex_path, r3d::shader* shad)
{
    texture = load_dds(tex_path);
    this->shader = shad;
}

void material::bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(shader->texture_sampler, 0);
}