//
// Created by Ryan on 26/03/2018.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "constants.hpp"
#include "scene.hpp"
#include "../core/behaviour.hpp"
#include "../render/mesh_renderer.hpp"

using namespace r3d;

void scene::init(int width, int height)
{
	window.init(width, height);

	main_camera.init(width, height);

	canvas.init(get_window());

	should_update = true;
}

// TODO: this could return std::unique_ptr<game_object>&
// game_objects can be an array of unique_ptrs (this class manages life cycle)
std::shared_ptr<game_object> scene::create_object(std::string name, glm::vec3 position, glm::vec3 euler_angles, glm::vec3 scale)
{
	auto ptr = std::make_shared<game_object>(name, position, euler_angles, scale);

	game_objects.emplace_back(std::move(ptr));

	return game_objects.back();
}

std::shared_ptr<game_object> scene::instantiate_object(std::string name,
	std::shared_ptr<game_object> object,
	glm::vec3 position,
	glm::vec3 euler_angles,
	glm::vec3 scale)
{
	auto ptr = std::make_shared<game_object>(name, position, euler_angles, scale);
	ptr->renderer = object->renderer;

	game_objects.emplace_back(std::move(ptr));

	return game_objects.back();
}

void scene::destroy_object(std::shared_ptr<game_object>& ptr)
{
	game_objects.erase(std::remove(game_objects.begin(), game_objects.end(), ptr), game_objects.end());
	ptr.reset();
}

void scene::add_light(glm::vec3 position, glm::vec3 color, float intensity)
{
	lights.emplace_back(light{ position, color, intensity });
}

void scene::add_skybox(std::vector<std::string> faces)
{
	skybox.init(faces, main_camera);
}

void scene::update_time()
{
	timer.update();
}

void scene::update()
{
	// render scene loop
	update_time();

	window.pre_render();

	canvas.pre_render();

	main_camera.update();

	// update scripts
	for (auto& object : game_objects)
	{
		if (object->enabled)
		{
			object->update_behaviours();
		}
	}

	// group objects by renderer for instanced drawing
	std::unordered_map<mesh_renderer*, std::vector<glm::mat4>> render_groups;

	for (auto& object : game_objects)
	{
		if (!object->enabled || object->renderer == nullptr) { continue; }

		glm::mat4& model = object->get_transform();
		if (!main_camera.check_frustum_cull(model, object->renderer->bounds)) { continue; }

		render_groups[object->renderer.get()].push_back(model);
	}

	for (auto& [renderer, transforms] : render_groups)
	{
		renderer->render_instanced(transforms, main_camera, lights);
	}

	// render debug if enabled
	if (debug_view.get_enabled())
	{
		debug_view.get_instance()->render(main_camera.view, main_camera.projection);
	}

	// render skybox if enabled
	if (skybox.enabled)
	{
		skybox.render(main_camera);
	}

	// render ui
	canvas.post_render();

	should_update = window.post_render();
}

void scene::exit()
{
	printf("Exit\n");

	for (auto& object : game_objects)
	{
		if (object->renderer != nullptr)
		{
			object->renderer->destroy();
		}
	}

	canvas.shutdown();

	window.exit();
}
