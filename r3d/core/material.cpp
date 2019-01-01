//
// Created by Ryan on 21/05/2018.
//

#include "material.hpp"
#include "../load/load_texture.hpp"

using namespace std;
using namespace glm;
using namespace r3d;

material::material(std::string tex_path, shared_ptr<r3d::shader> shader) : shader(shader)
{
    diffuse_texture = load_texture(tex_path);
}

material::material(std::string tex_path, std::string normal_tex_path, std::shared_ptr<r3d::shader> shader) : shader(shader)
{
    diffuse_texture = load_texture(tex_path);
    normal_texture = load_texture(normal_tex_path);
}

void material::bind()
{
    glUseProgram(shader->get_program());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuse_texture);
    glUniform1i(shader->get_texture_sampler(), 0);
    
    if(shader->uses_normal_map)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, normal_texture);
        glUniform1i(shader->get_normal_sampler(), 1);
    }
}