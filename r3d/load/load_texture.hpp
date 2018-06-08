#ifndef LOAD_TEXTURE_HPP
#define LOAD_TEXTURE_HPP

namespace r3d
{
    GLuint load_bmp(const char *imagepath);
    GLuint load_dds(const char *imagepath);
}

#endif