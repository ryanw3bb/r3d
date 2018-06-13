#ifndef LOAD_TEXTURE_HPP
#define LOAD_TEXTURE_HPP

namespace r3d
{
    GLuint load_bmp(const char *image_path);
    GLuint load_dds(const char *image_path);
}

#endif