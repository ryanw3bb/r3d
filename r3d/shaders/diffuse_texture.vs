#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vert_position_model;
layout(location = 1) in vec2 vert_uv_model;
layout(location = 2) in vec3 vert_normal_model;

// Output data; will be interpolated for each fragment.
out vec3 vert_position_world;
out vec2 vert_uv_world;
out vec3 vert_normal_camera;
out vec3 look_direction_camera;
out vec3 light_direction_camera;

// Values that stay constant for the whole mesh.
uniform mat4 mvp;
uniform mat4 view;
uniform mat4 model;
uniform vec3 light_position_world;

void main()
{
	// Output position of the vertex, in clip space
	gl_Position =  mvp * vec4(vert_position_model, 1);
	
	// Position of the vertex, in world space
	vert_position_world = (model * vec4(vert_position_model, 1)).xyz;
	
	// Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0).
	vec3 vert_position_camera = (view * model * vec4(vert_position_model, 1)).xyz;
	look_direction_camera = vec3(0, 0, 0) - vert_position_camera;

	// Vector that goes from the vertex to the light, in camera space.
	vec3 light_position_camera = (view * vec4(light_position_world, 1)).xyz;
	light_direction_camera = light_position_world + look_direction_camera;
	
	// Normal of the the vertex, in camera space
	vert_normal_camera = (view * model * vec4(vert_normal_model, 0)).xyz;

	// UV of the vertex. No special space for this one.
	vert_uv_world = vert_uv_model;
}

