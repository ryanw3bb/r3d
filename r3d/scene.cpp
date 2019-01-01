//
// Created by Ryan on 26/03/2018.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "scene.hpp"
#include "component/mesh_renderer.hpp"
#include "component/behaviour.hpp"
#include "core/constants.hpp"

using namespace r3d;

void scene::init(int width, int height)
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

    // grey background
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

    // setting callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetErrorCallback(error_callback);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    main_camera.set_aspect((float)width / (float)height);
    should_update = true;
}

std::shared_ptr<game_object> scene::create_object(std::string name, glm::vec3 position, glm::vec3 euler_angles, glm::vec3 scale)
{
    auto ptr = std::make_shared<game_object>( name, position, euler_angles, scale );

    game_objects.emplace_back(std::move(ptr));

    return game_objects.back();
}

std::shared_ptr<game_object> scene::instantiate_object(std::string name,
        std::shared_ptr<game_object> object,
        glm::vec3 position,
        glm::vec3 euler_angles,
        glm::vec3 scale)
{
    auto ptr = std::make_shared<game_object>( name, position, euler_angles, scale );
    ptr->renderer = object->renderer;

    game_objects.emplace_back(std::move(ptr));

    return game_objects.back();
}

void scene::destroy_object(std::shared_ptr<game_object>& ptr)
{
    game_objects.erase(std::remove(game_objects.begin(), game_objects.end(), ptr), game_objects.end());
    ptr.reset();
}

void scene::add_light(glm::vec3 position, glm::vec3 color, float intensity)
{
    lights.emplace_back(light { position, color, intensity });
}

void scene::update_time()
{
    timer.update();
}

void scene::update()
{
    update_time();

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

        // bind buffers and draw elements
        object->renderer->render(object->get_transform(), main_camera, lights);
    }

    // render debug if enabled
    if(debug_view.get_enabled())
    {
        debug_view.get_instance()->render(main_camera.get_view(), main_camera.get_projection());
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
        object->renderer->destroy();
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