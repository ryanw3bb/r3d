#version 330 core

// Interpolated values from the vertex shaders
in vec3 vert_position_world;
in vec2 vert_uv;
in vec3 eye_direction_camera;
in vec3 light_direction_camera;

// tangent space used for normal mapping
in vec3 eye_direction_tangent;
in vec3 light_direction_tangent;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D sampler;
uniform sampler2D normal_sampler;
uniform vec3 light_position_world;
uniform vec3 light_color;
uniform float light_power;
uniform vec3 ambient = vec3(0.1, 0.1, 0.1);
uniform vec3 specular = vec3(0.01, 0.01, 0.01);
uniform float shininess = 1;

bool directional = false;

void main()
{
	// Material properties
	vec3 material_diffuse_color = texture(sampler, vert_uv).rgb;
	vec3 material_ambient_color = ambient * material_diffuse_color;

	vec3 normal = normalize(texture(normal_sampler, vert_uv).rgb * 2 - 1.0);

    float attenuation = 1.0;
    vec3 surface_to_light;

    if(directional)
    {
        surface_to_light = normalize(light_position_world);
        attenuation = 1.0;
    }
    else
    {
        // Direction of the light (from the fragment to the light)
        surface_to_light = normalize(light_direction_tangent);

        float distance_to_light = length(light_position_world - vert_position_world);

        attenuation = 1.0 / (1.0 + pow(distance_to_light, 2));
    }

	// Diffuse Strength
	// 1 - light position is directly vertical to triangle (or light direction is perpendicular)
	// 0 - light position is perpendicular to the triangle (or light direction is parallel)
	float diffuse_strength = clamp(dot(normal, surface_to_light), 0, 1);

	vec3 diffuse = material_diffuse_color * light_color * light_power * diffuse_strength;

	// Look vector (towards the camera)
	vec3 surface_to_camera = normalize(eye_direction_tangent);

	// Direction in which the triangle reflects the light
	vec3 reflect_direction = reflect(-surface_to_light, normal);

	// Specular Strength
	// Looking into the reflection = 1, otherwise < 1
	float specular_strength = clamp(dot(surface_to_camera, reflect_direction), 0, 1);

	vec3 specular = specular * light_color * light_power * pow(specular_strength, shininess);

	color = material_ambient_color + attenuation * (diffuse + specular);
}