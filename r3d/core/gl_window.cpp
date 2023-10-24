//
// Created by Ryan on 2019-01-17.
//

#include "gl_window.hpp"

using namespace r3d;

void gl_window::init(int width, int height)
{
    // Initialise GLFW
    if(!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(width, height, "r3d", NULL, NULL);
    if(!window)
    {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window); // Initialize GLFW
    glfwSwapInterval(1); // Enable vsync

    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    glewExperimental = true;
    if(glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return;
    }

    // setting callbacks
    glfwSetKeyCallback(window, glfw_key_callback);
    glfwSetCursorPosCallback(window, glfw_mouse_cursor_callback);
    glfwSetWindowPosCallback(window, glfw_window_pos_callback);
    glfwSetErrorCallback(glfw_error_callback);

    // grey background
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
}

void gl_window::pre_render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool gl_window::post_render()
{
    glfwSwapBuffers(window);
    glfwPollEvents();

    if(glfwWindowShouldClose(window) != 0)
    {
        return false;
    }

    return true;
}

void gl_window::exit()
{
    glfwTerminate();
}

void gl_window::set_key_callback(std::function<void(int, int)> callback)
{
    key_callback = callback;
}

void gl_window::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (key_callback)
    {
        key_callback(key, action);
    }
}

void gl_window::glfw_mouse_cursor_callback(GLFWwindow * window, double xpos, double ypos)
{

}

void gl_window::glfw_window_pos_callback(GLFWwindow* window, int xpos, int ypos)
{

}

void gl_window::glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
