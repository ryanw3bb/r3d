#version 330 core

layout(location = 0) in vec3 vert_position_model;
layout(location = 1) in vec2 vert_uv_model;

uniform mat4 mvp;

out vec2 vert_uv_world;

void main()
{
    gl_Position = mvp * vec4(vert_position_model, 1);

    vert_uv_world = vert_uv_model;
}