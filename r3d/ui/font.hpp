//
// Created by Ryan on 2019-01-05.
//

#ifndef R3D_FONT_HPP
#define R3D_FONT_HPP

#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../render/gl_includes.hpp"

namespace r3d
{
    struct character
    {
        GLuint texture_id;
        glm::ivec2 size;
        glm::ivec2 bearing; // Offset from baseline to left/top of glyph
        long advance; // Offset to advance to next glyph
    };

    class font
    {
    public:
        int size;
        int line_spacing;

        font(std::string path, int size, int line_spacing = 2);

        std::map<GLchar, character> chars;
    };
}


#endif //R3D_FONT_HPP
