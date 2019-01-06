//
// Created by Ryan on 2019-01-05.
//

#include "text.hpp"

using namespace r3d;

text::text(std::string text, std::shared_ptr<r3d::font> font, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
    this->data = text;
    this->position.x = x;
    this->position.y = y;
    this->scale = scale;
    this->font = font;
}

void text::render(GLuint& vertex_buffer_object)
{
    GLfloat x = position.x;
    GLfloat y = position.y;

    std::string::const_iterator c;
    for(c = data.begin(); c != data.end(); c++)
    {
        if(*c == '\n')
        {
            x = position.x;
            y -= font->size + font->line_spacing;
            continue;
        }

        r3d::character ch = font->chars[*c];

        GLfloat xpos = x + ch.bearing.x * scale;
        GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

        GLfloat w = ch.size.x * scale;
        GLfloat h = ch.size.y * scale;

        GLfloat vertices[6][4] = {
                { xpos, ypos + h, 0.0, 0.0 },
                { xpos, ypos, 0.0, 1.0 },
                { xpos + w, ypos, 1.0, 1.0 },

                { xpos, ypos + h, 0.0, 0.0 },
                { xpos + w, ypos, 1.0, 1.0 },
                { xpos + w, ypos + h, 1.0, 0.0 }
        };

        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.texture_id);

        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        x += (ch.advance >> 6) * scale;
    }
}