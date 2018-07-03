#version 330 core

layout(location = 0) in vec3 vert_position_model;
layout(location = 1) in vec3 vert_color;

uniform mat4 mvp;

out vec3 frag_color;

void main()
{
    // Output position of the vertex, in clip space
    gl_Position = mvp * vec4(vert_position_model, 1);
    frag_color = vert_color;
}