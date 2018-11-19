#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out VS_OUT {
	vec3 FragPos;
	vec3 Normal;
 } vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 mvp;

void main()
{
    vs_out.FragPos = vec3(model * vec4(position, 1.0));
    vs_out.Normal = mat3(transpose(inverse(model))) * normal;
    
    gl_Position = mvp * vec4(position, 1.0);
}