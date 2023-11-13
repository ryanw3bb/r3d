//
// Created by Ryan on 30/05/2018.
//

#include "camera.hpp"

using namespace r3d;

void camera::init(int width, int height)
{
	this->width = width;
	this->height = height;
	this->aspect_ratio = (float)width / (float)height;
}

void camera::set_rotation(glm::vec3 euler_degrees)
{
	this->game_object::set_rotation(euler_degrees);
}

void camera::set_position(glm::vec3 position)
{
	this->game_object::set_position(position);
}

void camera::update_matrices()
{
	this->game_object::update_directions();
	view = glm::lookAt(position, position + forward, up);
	projection = glm::perspective(fov, aspect_ratio, near, far);
}

void camera::update()
{
	update_matrices();
	update_frustum();
}

void camera::update_frustum()
{
	// view projection matrix in world space
	glm::mat4 vp = projection * view;

	// extract frustum planes from the view projection matrix
	// each is comprised of a normal direction (x, y, z) and a distance from the origin (w)
	// using glm::row because glm is column major so m[3] would actually give the third column
	frustum_planes[0] = glm::row(vp, 3) + glm::row(vp, 0); // left
	frustum_planes[1] = glm::row(vp, 3) - glm::row(vp, 0); // right
	frustum_planes[2] = glm::row(vp, 3) + glm::row(vp, 1); // bottom
	frustum_planes[3] = glm::row(vp, 3) - glm::row(vp, 1); // top
	frustum_planes[4] = glm::row(vp, 3) + glm::row(vp, 2); // near
	frustum_planes[5] = glm::row(vp, 3) - glm::row(vp, 2); // far

	// normalize the frustum planes so that they are unit length vectors in world space, also normalise distance
	for (int i = 0; i < 6; i++)
	{
		float t = sqrt(frustum_planes[i].x * frustum_planes[i].x + frustum_planes[i].y * frustum_planes[i].y + frustum_planes[i].z * frustum_planes[i].z);
		frustum_planes[i] /= t;
	}
}

bool camera::check_frustum_cull(glm::mat4& transform, std::shared_ptr<bounds>& bounds)
{
	for (int i = 0; i < bounds->corners.size(); i++)
	{
		glm::vec4 world_corner = transform * glm::vec4(bounds->corners[i], 1.0f);
		if (check_frustum_cull(world_corner))
		{
			return true;
		}
	}

	return false;
}

bool camera::check_frustum_cull(glm::vec3 point)
{
	// check if world space point is inside all six frustum planes
	for (int i = 0; i < 6; i++)
	{
		// project the point onto the frustum plane's normal using dot, then compare to the distance from origin to frustum plane
		// if the value is less than or equal to zero, the point is outside the plane
		if (glm::dot(frustum_planes[i].xyz(), point) + frustum_planes[i].w <= 0)
		{
			return false;
		}
	}

	return true;
}
