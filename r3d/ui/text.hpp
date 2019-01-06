//
// Created by Ryan on 2019-01-05.
//

#ifndef R3D_TEXT_HPP
#define R3D_TEXT_HPP

#include "canvas_object.hpp"
#include "font.hpp"

namespace r3d
{
    class text : public canvas_object
    {
    public:
        std::string data;

        text() = default;

        text(std::string text, std::shared_ptr<r3d::font> font, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

        virtual void render(GLuint&);

    protected:
        std::shared_ptr<font> font;
    };
}

#endif //R3D_TEXT_HPP
