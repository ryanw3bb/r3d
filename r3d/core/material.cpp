//
// Created by Ryan on 21/05/2018.
//

#include "material.hpp"
#include "../load/load_texture.hpp"

using namespace r3d;

material::material(std::string tex_path, r3d::shader * shader)
{
    // load bmp, get texture id
    texture = load_dds(tex_path.c_str());

    this->shader = shader;
}