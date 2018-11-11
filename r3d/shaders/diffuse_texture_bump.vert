#version 330 core

// Input vertex data
layout(location = 0) in vec3 vert_position_model;
layout(location = 1) in vec2 vert_uv_model;
layout(location = 2) in vec3 vert_normal_model;
layout(location = 3) in vec3 vert_tangent_model;
layout(location = 4) in vec3 vert_bitangent_model;

// Output data - interpolated for each fragment.
out vec3 vert_position_world;
out vec2 vert_uv;
out vec3 eye_direction_camera;
out vec3 light_direction_camera;

// tangent space used for normal mapping
out vec3 light_direction_tangent;
out vec3 eye_direction_tangent;

// Values that stay constant for the whole mesh.
uniform mat4 mvp;
uniform mat4 view;
uniform mat4 model;
uniform mat3 model_view_3x3;
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
	eye_direction_camera = vec3(0, 0, 0) - vert_position_camera;

	// Vector that goes from the vertex to the light, in camera space.
	vec3 light_position_camera = (view * vec4(light_position_world, 1)).xyz;
	light_direction_camera = light_position_world + eye_direction_camera;

	// UV of the vertex. No special space for this one.
	vert_uv = vert_uv_model;

	// tangent calculations for normal mapping
	vec3 vert_tangent_camera = model_view_3x3 * vert_tangent_model;
	vec3 vertex_bitangent_camera = model_view_3x3 * vert_bitangent_model;
	vec3 vertex_normal_camera = model_view_3x3 * vert_normal_model;
	
	mat3 tbn = transpose(mat3(
		vert_tangent_camera,
		vertex_bitangent_camera,
		vertex_normal_camera	
	));

	light_direction_tangent = tbn * light_direction_camera;
	eye_direction_tangent =  tbn * eye_direction_camera;
}

