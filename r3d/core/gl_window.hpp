//
// Created by Ryan on 2019-01-17.
//

#ifndef R3D_GL_WINDOW_HPP
#define R3D_GL_WINDOW_HPP

#include <functional>
#include <stdio.h>
#include "gl_includes.hpp"

namespace r3d
{
    class gl_window
    {
    public:
        gl_window() {}

        GLFWwindow* window;

        void init(int, int);

        void pre_render();

        bool post_render();

        void exit();

        void set_key_callback(std::function<void(int, int)> callback);

    private:
        static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        static void glfw_mouse_cursor_callback(GLFWwindow * window, double xpos, double ypos);

        static void glfw_window_pos_callback(GLFWwindow * window, int xpos, int ypos);

        static void glfw_error_callback(int error, const char* description);

        inline static std::function<void(int, int)> key_callback;
    };
}

#endif //R3D_GL_WINDOW_HPP
