//
// Created by Ryan on 2019-01-05.
//

#include "font.hpp"
#include "../utils/file.hpp"

using namespace r3d;

font::font(std::string path, int size, int line_spacing)
{
    this->size = size;
    this->line_spacing = line_spacing;

    std::string full_path = get_running_dir() + path;

    FT_Library ft;
    if(FT_Init_FreeType(&ft))
    {
        printf("Could not load FreeType Library\n");
    }

    FT_Face face;
    if(FT_New_Face(ft, full_path.c_str(), 0, &face))
    {
        printf("Failed to load font\n");
    }

    FT_Set_Pixel_Sizes(face, 0, size);

    for(GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if(FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            printf("Failed to load Glyph\n");
            continue;
        }

        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Now store character for later use
        character char0 = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
        };

        chars.insert(std::pair<GLchar, character>(c, char0));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}