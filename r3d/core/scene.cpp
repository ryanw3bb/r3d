//
// Created by Ryan on 26/03/2018.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "constants.hpp"
#include "scene.hpp"
#include "../component/mesh_renderer.hpp"
#include "../component/behaviour.hpp"

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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

    canvas.init(width, height);
    canvas.enable_stats(true);

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

void scene::add_skybox(std::vector<std::string> faces)
{
    skybox.init(faces, main_camera);
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
    for(auto& object : game_objects)
    {
        if(object->enabled)
        {
            object->update_behaviours();
        }
    }

    bool change_shader, bind_vao, bind_textures;

    // render scene objects
    for(auto& object : game_objects)
    {
        if(!object->enabled || object->renderer == nullptr) { continue; }

        change_shader = (last_render_object == nullptr) || (object->renderer->shader != last_render_object->renderer->shader);
        bind_vao = (last_render_object == nullptr) || (object->renderer->mesh != last_render_object->renderer->mesh);
        bind_textures = (last_render_object == nullptr) || (object->renderer->material != last_render_object->renderer->material);

        // bind buffers and draw elements
        object->renderer->render(object->get_transform(), main_camera, lights, change_shader, bind_vao, bind_textures);

        last_render_object = object;
    }

    last_render_object.reset();

    // render debug if enabled
    if(debug_view.get_enabled())
    {
        debug_view.get_instance()->render(main_camera.view, main_camera.projection);
    }

    // render skybox if enabled
    if(skybox.enabled)
    {
        skybox.render(main_camera);
    }

    // render ui
    canvas.render();

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

    for(auto& object : game_objects)
    {
        if(object->renderer != nullptr)
        {
            object->renderer->destroy();
        }
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
