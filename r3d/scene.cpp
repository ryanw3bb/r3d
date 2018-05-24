//
// Created by Ryan on 26/03/2018.
//

#include <iostream>
#include <vector>

#include "scene.hpp"
#include "core/controls.hpp"
#include "component/mesh_renderer.hpp"

using namespace r3d;

std::vector<r3d::game_object *> game_objects;
std::vector<r3d::light *> lights;

scene::scene(int width, int height)
{
    // Initialise GLFW
    if(!glfwInit())
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(width, height, "scene", NULL, NULL);
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

    shouldUpdate = true;
}

void scene::add_object(r3d::game_object * obj)
{
    game_objects.push_back(obj);

    printf("Add object to scene: %s\n", obj->name.c_str());
}

void scene::add_light(r3d::light * light)
{
    lights.push_back(light);
}

void scene::update()
{
    // render scene loop
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // calculate view and projection matrices
    computeMatricesFromInputs(window);
    glm::mat4 projection = get_projection_matrix();
    glm::mat4 view = get_view_matrix();

    for(std::vector<game_object *>::iterator it = game_objects.begin(); it != game_objects.end(); ++it)
    {
        r3d::mesh_renderer * renderer = (mesh_renderer *)(*it)->components.at(0);

        // calculate mvp matrix per model
        glm::mat4 model = (*it)->get_transform();
        glm::mat4 mvp = projection * view * model;

        // use our shader
        glUseProgram(renderer->material->shader->program);

        // Send our transformation to the currently bound shader
        glUniformMatrix4fv(renderer->material->shader->mvp_matrix, 1, GL_FALSE, &mvp[0][0]);
        glUniformMatrix4fv(renderer->material->shader->model_matrix, 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(renderer->material->shader->view_matrix, 1, GL_FALSE, &view[0][0]);

        // setting light uniforms
        glUniform3f(renderer->material->shader->light_world_pos, lights.front()->position.x, lights.front()->position.y, lights.front()->position.z);
        glUniform3f(renderer->material->shader->color, lights.front()->color.x, lights.front()->color.y, lights.front()->color.z);
        glUniform1f(renderer->material->shader->intensity, lights.front()->intensity);

        // Bind texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, renderer->material->texture);
        // Set our sampler to use Texture Unit 0
        glUniform1i(renderer->material->shader->texture_sampler, 0);

        // vao
        glBindVertexArray(renderer->vertex_array_object);

        // vertex buffer
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, renderer->vertex_buffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        // uv buffer
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, renderer->uv_buffer);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

        // normal buffer
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, renderer->normal_buffer);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        // index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->indices_buffer);
        glDrawElements(GL_TRIANGLES, renderer->indices.size(), GL_UNSIGNED_SHORT, (void*)0);

        glBindVertexArray(0);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    glfwSwapBuffers(window);
    glfwPollEvents();

    if(glfwWindowShouldClose(window) != 0)
    {
        shouldUpdate = false;
    }
}

void scene::exit()
{
    printf("Exit\n");

    for(std::vector<game_object *>::iterator it = game_objects.begin(); it != game_objects.end(); ++it)
    {
        r3d::mesh_renderer * renderer = (mesh_renderer *) (*it)->components.at(0);

        glDeleteBuffers(1, &renderer->vertex_buffer);
        glDeleteBuffers(1, &renderer->uv_buffer);
        glDeleteBuffers(1, &renderer->normal_buffer);
        glDeleteTextures(1, &renderer->material->texture);
        glDeleteVertexArrays(1, &renderer->vertex_array_object);
        glDeleteProgram(renderer->material->shader->program);
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