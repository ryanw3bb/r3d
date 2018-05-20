//
// Created by Ryan on 26/03/2018.
//

#include <iostream>
#include <vector>

#include "scene.hpp"
#include "core/controls.hpp"
#include "core/game_object.hpp"
#include "load/load_shaders.hpp"
#include "load/load_texture.hpp"
#include "load/load_mesh.hpp"
#include "core/mesh_renderer.hpp"

using namespace r3d;

std::vector<r3d::game_object *> game_objects;
GLuint vao;
GLuint program_id;
GLuint matrix_id;
GLuint view_matrix_id;
GLuint model_matrix_id;
GLuint texture_sampler_id;
GLuint light_id;

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

    glewExperimental = true; // Needed in scene profile
    if(glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return;
    }

    // setting callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetErrorCallback(error_callback);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    // glew VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // shader program
    program_id = load_shaders("shaders/diffuse_vert.vertexshader", "shaders/diffuse_frag.fragmentshader");

    // Get a handle for our "MVP" uniform
    matrix_id = glGetUniformLocation(program_id, "MVP");
    view_matrix_id = glGetUniformLocation(program_id, "V");
    model_matrix_id = glGetUniformLocation(program_id, "M");

    // Get a handle for our "myTextureSampler" uniform
    texture_sampler_id = glGetUniformLocation(program_id, "Sampler");

    glUseProgram(program_id);
    light_id = glGetUniformLocation(program_id, "LightPosition_worldspace");

    // load bmp, get texture id
    /*GLuint texture = load_dds("assets/uvmap.dds");

    // Read our .obj file
    std::vector<unsigned short> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals; // Won't be used at the moment.
    bool res = load_mesh("assets/suzanne.obj", indices, vertices, uvs, normals);

    // 1. Vertex buffer
    GLuint vertex_buffer;
    // Generate 1 buffer, put the resulting identifier in vertex_buffer
    glGenBuffers(1, &vertex_buffer);
    // The following commands will talk about our 'vertex_buffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    // 2. UV buffer (using instead of colour buffer)
    GLuint uv_buffer;
    glGenBuffers(1, &uv_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    // 3. Normal buffer
    GLuint normal_buffer;
    glGenBuffers(1, &normal_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

    // Get a handle for our "LightPosition" uniform
    glUseProgram(program_id);
    light_id = glGetUniformLocation(program_id, "LightPosition_worldspace");

    while(glfwWindowShouldClose(window) == 0)
    {
        // render scene loop
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // mvp bruv
        computeMatricesFromInputs(window);
        glm::mat4 projection = getProjectionMatrix();
        glm::mat4 view = getViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 mvp = projection * view * model;

        // use our shader
        glUseProgram(program_id);

        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &mvp[0][0]);
        glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, &view[0][0]);

        glm::vec3 lightPos = glm::vec3(4, 4, 4);
        glUniform3f(light_id, lightPos.x, lightPos.y, lightPos.z);

        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        // Set our sampler to use Texture Unit 0
        glUniform1i(texture_sampler_id, 0);

        // first attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
        );

        // 2nd attribute buffer : uv
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
        glVertexAttribPointer(
                1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                2,                                // size
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                (void*)0                          // array buffer offset
        );

        // 3rd attribute buffer : normals
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
        glVertexAttribPointer(
                2,                                // attribute
                3,                                // size
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                (void*)0                          // array buffer offset
        );

        // draw
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &uv_buffer);
    glDeleteBuffers(1, &normal_buffer);
    glDeleteProgram(program_id);
    glDeleteTextures(1, &texture);
    glDeleteVertexArrays(1, &vao);

    glfwTerminate();*/

    shouldUpdate = true;
}

void scene::add_object(r3d::game_object * obj)
{
    game_objects.push_back(obj);

    printf("add object: %s\n", obj->name.c_str());
}

void scene::update()
{
   for(std::vector<game_object *>::iterator it = game_objects.begin(); it != game_objects.end(); ++it)
   {
       r3d::mesh_renderer * renderer = (mesh_renderer *)(*it)->components.at(0);

       // render scene loop
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       // calculate mvp matrices
       computeMatricesFromInputs(window);
       glm::mat4 projection = getProjectionMatrix();
       glm::mat4 view = getViewMatrix();
       glm::mat4 model = glm::mat4(1.0f);
       glm::mat4 mvp = projection * view * model;

       // use our shader
       glUseProgram(program_id);

       // Send our transformation to the currently bound shader,
       // in the "MVP" uniform
       glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &mvp[0][0]);
       glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, &model[0][0]);
       glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, &view[0][0]);

       glm::vec3 light_pos = glm::vec3(4, 4, 4);
       glUniform3f(light_id, light_pos.x, light_pos.y, light_pos.z);

       // Bind our texture in Texture Unit 0
       glActiveTexture(GL_TEXTURE0);
       glBindTexture(GL_TEXTURE_2D, renderer->texture);
       // Set our sampler to use Texture Unit 0
       glUniform1i(texture_sampler_id, 0);

       // first attribute buffer : vertices
       glEnableVertexAttribArray(0);
       glBindBuffer(GL_ARRAY_BUFFER, renderer->vertex_buffer);
       glVertexAttribPointer(
               0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
               3,                  // size
               GL_FLOAT,           // type
               GL_FALSE,           // normalized?
               0,                  // stride
               (void*)0            // array buffer offset
       );

       // 2nd attribute buffer : uv
       glEnableVertexAttribArray(1);
       glBindBuffer(GL_ARRAY_BUFFER, renderer->uv_buffer);
       glVertexAttribPointer(
               1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
               2,                                // size
               GL_FLOAT,                         // type
               GL_FALSE,                         // normalized?
               0,                                // stride
               (void*)0                          // array buffer offset
       );

       // 3rd attribute buffer : normals
       glEnableVertexAttribArray(2);
       glBindBuffer(GL_ARRAY_BUFFER, renderer->normal_buffer);
       glVertexAttribPointer(
               2,                                // attribute
               3,                                // size
               GL_FLOAT,                         // type
               GL_FALSE,                         // normalized?
               0,                                // stride
               (void*)0                          // array buffer offset
       );

       // draw
       glDrawArrays(GL_TRIANGLES, 0, renderer->vertices.size());

       glDisableVertexAttribArray(0);
       glDisableVertexAttribArray(1);
       glDisableVertexAttribArray(2);

       glfwSwapBuffers(window);
       glfwPollEvents();
   }

   if(glfwWindowShouldClose(window) != 0)
   {
       shouldUpdate = false;
   }
}

void scene::exit()
{
    printf("exit\n");

    for(std::vector<game_object *>::iterator it = game_objects.begin(); it != game_objects.end(); ++it)
    {
        r3d::mesh_renderer * renderer = (mesh_renderer *) (*it)->components.at(0);

        /*glDeleteBuffers(1, renderer->vertex_buffer);
        glDeleteBuffers(1, renderer->uv_buffer);
        glDeleteBuffers(1, renderer->normal_buffer);
        glDeleteTextures(1, renderer->texture);*/
    }

    glDeleteProgram(program_id);
    glDeleteVertexArrays(1, &vao);
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