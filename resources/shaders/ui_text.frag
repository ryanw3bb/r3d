#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform sampler2D albedoSampler;
uniform vec3 tint = vec3(1.0, 1.0, 1.0);

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(albedoSampler, TexCoords).r);
    color = vec4(tint, 1.0) * sampled;
}
