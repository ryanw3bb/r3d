#version 330 core

layout(location = 0) in vec3 position;

out VS_OUT {
    vec3 TexCoords;
} vs_out;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    vs_out.TexCoords = position;
    vec4 pos = projection * view * vec4(position, 1.0);
    gl_Position = pos.xyww;
}