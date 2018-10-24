#version 330 core

in vec2 vert_uv_world;

out vec3 color;

uniform sampler2D sampler;

void main()
{
    color = texture(sampler, vert_uv_world).rgb;
}