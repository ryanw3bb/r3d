#ifndef LOAD_TEXTURE_HPP
#define LOAD_TEXTURE_HPP

#include <string>
#include <vector>

namespace r3d
{
    GLuint load_texture(std::string);
    GLuint load_cubemap(std::vector<std::string>);
    GLuint load_dds(std::string);
}

#endif