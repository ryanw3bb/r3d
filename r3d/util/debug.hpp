//
// Created by Ryan on 15/11/2018.
//

#ifndef R3D_DEBUG_HPP
#define R3D_DEBUG_HPP

#include <iostream>
#include <vector>
#include "../render/gl_includes.hpp"

namespace r3d
{
    class debug
    {
        struct line
        {
            line(int index, glm::vec3 color):index(index), color(color) { }

            int index;
            glm::vec3 color = glm::vec3(1, 1, 1);
        };

    public:
        static debug* get_instance();
        static bool get_enabled();

        debug() { }
        void init();
        void add_line(glm::vec3 start_vec, glm::vec3 end_vec, glm::vec3 color);
        void render(glm::mat4 view, glm::mat4 projection);
        glm::mat4 get_transform();

        bool enabled = false;

    private:
        void update();

        static debug* instance;

        bool dirty = false;
        std::vector<GLuint> indices;
        std::vector<glm::vec3> vertices;
        GLuint vertex_array_object;
        GLuint vertex_buffer_object;
        GLuint indices_buffer;
        GLuint vertex_identifier;
        GLuint shader_program;
        GLuint mvp_matrix;
        GLuint tint_color;
        glm::vec3 position = glm::vec3(0, 0, 0);
        glm::vec3 euler_angles = glm::vec3(0, 0, 0);
        std::vector<line*> lines;
    };
}

#endif //R3D_DEBUG_HPP
