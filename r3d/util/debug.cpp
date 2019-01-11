//
// Created by Ryan on 15/11/2018.
//

#include "debug.hpp"
#include "../load/load_shader.hpp"

using namespace r3d;

debug* debug::instance;

debug* debug::get_instance()
{
    if(instance == nullptr)
    {
        instance = new debug();
        instance->init();
    }

    return instance;
}

bool debug::get_enabled()
{
    return instance != nullptr && instance->enabled;
}

void debug::init()
{
    // shader program and handles
    shader_program = load_shader("r3d/shaders/unlit_color.vert", "r3d/shaders/unlit_color.frag");
    vertex_identifier = glGetAttribLocation(shader_program, "position");
    mvp_matrix = glGetUniformLocation(shader_program, "mvp");
    tint_color = glGetUniformLocation(shader_program, "tint_color");

    // vao
	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);

    // vbo
    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);

    // indices
    glGenBuffers(1, &indices_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);

    // enable and setup vbo pointer
    glVertexAttribPointer(vertex_identifier, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
    glEnableVertexAttribArray(vertex_identifier);
}

void debug::add_line(glm::vec3 start_vec, glm::vec3 end_vec, glm::vec3 color)
{
    // line data
    vertices.push_back(start_vec);
    vertices.push_back(end_vec);
    
    indices.push_back(0);
    indices.push_back(1);

    lines.push_back(new r3d::debug::line(lines.size() * 2, color));

    enabled = true;
    dirty = true;
}

void debug::update()
{
    // add vertices and indices data
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

    dirty = false;
}

void debug::render(glm::mat4 view, glm::mat4 projection)
{
    if(!enabled) { return; }

    glBindVertexArray(vertex_array_object);

    if(dirty) { update(); }

    // bind shader and set color
    glUseProgram(shader_program);

    // matrices
    glm::mat4 mvp = projection * view * get_transform();
    glUniformMatrix4fv(mvp_matrix, 1, GL_FALSE, &mvp[0][0]);

    // draw elements using vao
    for(const auto& line : lines)
    {
        glUniform3f(tint_color, line->color.x, line->color.y, line->color.z);
        glDrawElementsBaseVertex(GL_LINES, 2, GL_UNSIGNED_INT, 0, line->index);   
    }
}

glm::mat4 debug::get_transform()
{
    glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 rotation_matrix = glm::toMat4(glm::quat(euler_angles));

    return translation_matrix * rotation_matrix;
}