//
// Created by Ryan on 2019-01-05.
//

#ifndef R3D_CANVAS_HPP
#define R3D_CANVAS_HPP

#include <memory>
#include "../render/gl_includes.hpp"
#include "../render/shader.hpp"
#include "../util/stats.hpp"
#include "canvas_object.hpp"
#include "font.hpp"
#include "text.hpp"

namespace r3d
{
    class canvas
    {
    public:
        canvas() = default;

        void init(int width, int height);

        std::shared_ptr<text> add_text(std::string, GLfloat, GLfloat, GLfloat scale = 1, glm::vec3 color = glm::vec3(1, 1, 1));

        void remove_text(std::shared_ptr<text>&);

        void destroy_object(std::shared_ptr<canvas_object>&);

        void render();

        void enable_stats(bool);

    private:
        std::vector<std::shared_ptr<r3d::canvas_object>> canvas_objects;
        std::shared_ptr<fps> stats;
        glm::mat4 projection;
        GLuint vertex_array_object;
        GLuint vertex_buffer_object;
        std::shared_ptr<r3d::shader> shader;
        std::shared_ptr<r3d::font> font;
    };
}


#endif //R3D_CANVAS_HPP
