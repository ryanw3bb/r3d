//
// Created by Ryan on 2019-01-03.
//

#ifndef R3D_UI_RENDERER_HPP
#define R3D_UI_RENDERER_HPP

#include "../core/shader.hpp"

namespace r3d
{
    class canvas_object
    {
    public:
        glm::vec2 position = glm::vec2(0, 0);
        float scale = 1;

        canvas_object() = default;

        virtual void render(GLuint&) {};
    };
}

#endif //R3D_UI_RENDERER_HPP
