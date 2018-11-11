#version 330 core

// Interpolated values from the vertex shaders
in vec3 vert_position_world;
in vec2 vert_uv_world;
in vec3 vert_normal_camera;
in vec3 look_direction_camera;
in vec3 light_direction_camera;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform vec3 base_color = vec3(0.6, 0.6, 0.6);
uniform vec3 light_position_world;
uniform vec3 light_color;
uniform float light_power;
uniform vec3 ambient = vec3(0.1, 0.1, 0.1);
uniform vec3 specular = vec3(0.3, 0.3, 0.3);
uniform float shininess = 5;

bool directional = false;

void main()
{
	// Material properties
	vec3 material_diffuse_color = base_color;
	vec3 material_ambient_color = ambient * base_color;

	vec3 normal = normalize(vert_normal_camera);

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
        surface_to_light = normalize(light_direction_camera);

        float distance_to_light = length(light_position_world - vert_position_world);

        attenuation = 1.0 / (1.0 + pow(distance_to_light, 2));
    }

	// Diffuse Strength
	// 1 - light position is directly vertical to triangle (or light direction is perpendicular)
	// 0 - light position is perpendicular to the triangle (or light direction is parallel)
	float diffuse_strength = max(0.0, dot(normal, surface_to_light));

	vec3 diffuse = material_diffuse_color * light_color * light_power * diffuse_strength;

	// Look vector (towards the camera)
	vec3 surface_to_camera = normalize(look_direction_camera);

	// Direction in which the triangle reflects the light
	vec3 reflect_direction = reflect(-surface_to_light, normal);

	// Specular Strength
	// Looking into the reflection = 1, otherwise < 1
	float specular_strength = max(0.0, dot(surface_to_camera, reflect_direction));

	vec3 specular = specular * light_color * light_power * pow(specular_strength, shininess);

	color = material_ambient_color + attenuation * (diffuse + specular);
}