#ifndef LOAD_TEXTURE_HPP
#define LOAD_TEXTURE_HPP

#include <string>

namespace r3d
{
    GLuint load_bmp(std::string image_path);
    GLuint load_texture(std::string image_path);
    GLuint load_dds(std::string image_path);
}

#endif