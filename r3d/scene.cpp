//
// Created by Ryan on 26/03/2018.
//

#include <iostream>
#include <vector>
#include "scene.hpp"
#include "component/mesh_renderer.hpp"
#include "component/behaviour.hpp"
#include "core/constants.hpp"

using namespace r3d;

std::vector<r3d::game_object*> game_objects;
std::vector<r3d::light*> lights;

scene::scene(int width, int height)
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

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(width, height, "r3d", NULL, NULL);
    if(!window)
    {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window); // Initialize GLFW

    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    glewExperimental = true;
    if(glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return;
    }

    // setting callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetErrorCallback(error_callback);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    main_camera = new r3d::camera(width, height);

    time = new r3d::time;

    should_update = true;
}

void scene::add_object(r3d::game_object* obj)
{
    game_objects.push_back(obj);

    printf("Add object to scene: %s\n", obj->name);
}

void scene::add_light(r3d::light* light)
{
    lights.push_back(light);
}

void scene::update()
{
    time->update();

    // render scene loop
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // update scripts
    for(const auto& object : game_objects)
    {
        if(object->enabled)
        {
            object->update_behaviours();
        }
    }

    // render objects
    for(const auto& object : game_objects)
    {
        if(!object->enabled || object->renderer == nullptr) { continue; }

        // use our shader
        object->renderer->material->shader->bind();

        // set camera uniforms
        main_camera->set_uniforms(object->renderer->material->shader, object->get_transform());

        // set light uniforms
        lights.front()->set_uniforms(object->renderer->material->shader);

        // bind texture
        object->renderer->material->bind();

        // bind buffers and draw elements
        object->renderer->render();
    }

    glfwSwapBuffers(window);
    glfwPollEvents();

    if(glfwWindowShouldClose(window) != 0)
    {
        should_update = false;
    }
}

void scene::exit()
{
    printf("Exit\n");

    for(const auto& object : game_objects)
    {
        glDeleteBuffers(1, &object->renderer->vertex_buffer);
        glDeleteBuffers(1, &object->renderer->uv_buffer);
        glDeleteBuffers(1, &object->renderer->normal_buffer);
        glDeleteTextures(1, &object->renderer->material->texture);
        glDeleteVertexArrays(1, &object->renderer->vertex_array_object);
        glDeleteProgram(object->renderer->material->shader->program);
    }

    glfwTerminate();
}

void scene::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        if(key == GLFW_KEY_ESCAPE)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }
}

void scene::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}