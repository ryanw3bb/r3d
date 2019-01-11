#version 330 core

out vec3 color;

in VS_OUT {
    vec3 TexCoords;
} fs_in;

uniform samplerCube sampler;

void main()
{
    color = texture(sampler, fs_in.TexCoords).rgb;
}