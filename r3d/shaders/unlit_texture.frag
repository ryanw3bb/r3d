#version 330 core

out vec3 color;

in VS_OUT {
    vec2 TexCoords;
} fs_in;

uniform sampler2D diffuseSampler;

void main()
{
    color = texture(diffuseSampler, fs_in.TexCoords).rgb;
}