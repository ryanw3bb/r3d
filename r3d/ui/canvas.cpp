//
// Created by Ryan on 2019-01-05.
//

#include "canvas.hpp"

using namespace r3d;

void canvas::init(int width, int height)
{
    shader = std::make_shared<r3d::shader>(shader::id::UI);
    font = std::make_shared<r3d::font>("assets/fonts/LiberationSans.ttf", 12);
    projection = glm::ortho(0.0f, static_cast<GLfloat>(width), 0.0f, static_cast<GLfloat>(height));

    // create and bind vertex array object
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    // create vertex buffer object for text
    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    // enabled and link vertex identifier
    glEnableVertexAttribArray(shader->get_vertex_identifier());
    glVertexAttribPointer(shader->get_vertex_identifier(), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
}

std::shared_ptr<text> canvas::add_text(std::string data, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
    auto ptr = std::make_shared<text>( data, font, x, y, scale, color );

    canvas_objects.emplace_back(std::move(ptr));

    return std::dynamic_pointer_cast<text>(canvas_objects.back());
}

void canvas::remove_text(std::shared_ptr<text>& ptr)
{
    canvas_objects.erase(std::remove(canvas_objects.begin(), canvas_objects.end(), ptr), canvas_objects.end());
    ptr.reset();
}

void canvas::destroy_object(std::shared_ptr<canvas_object>& ptr)
{
    canvas_objects.erase(std::remove(canvas_objects.begin(), canvas_objects.end(), ptr), canvas_objects.end());
    ptr.reset();
}

void canvas::enable_stats(bool state)
{
    if(state)
    {
        if(stats == nullptr)
        {
            stats = std::make_shared<fps>(font, 2, 16);
            canvas_objects.emplace_back(std::move(stats));
        }
    }
    else
    {
        canvas_objects.erase(std::remove(canvas_objects.begin(), canvas_objects.end(), stats), canvas_objects.end());
        stats.reset();
    }
}

void canvas::render()
{
    glClear(GL_DEPTH_BUFFER_BIT);

    shader->use();
    shader->set_scene_uniforms(projection);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vertex_array_object);

    for(auto& object : canvas_objects)
    {
        object->render(vertex_buffer_object);
    }
}