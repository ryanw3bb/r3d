//
// Created by Ryan on 2019-01-05.
//

#include "ui.hpp"
#include "theme.hpp"
#include "../core/scene.hpp"
#include "../core/game_object.hpp"
#include "../core/light.hpp"
#include "../core/camera.hpp"
#include "../core/mesh.hpp"
#include "../render/mesh_renderer.hpp"
#include "../render/material.hpp"
#include "../render/shader.hpp"

using namespace r3d;

static const char* shader_name(shader::id id)
{
	switch (id)
	{
		case shader::UNLIT_TEXTURE:       return "Unlit Texture";
		case shader::DIFFUSE_TEXTURE:     return "Diffuse Texture";
		case shader::DIFFUSE_TEXTURE_BUMP: return "Diffuse Texture Bump";
		case shader::DIFFUSE_COLOR:       return "Diffuse Color";
		case shader::VERTEX_COLOR:        return "Vertex Color";
		case shader::UI:                  return "UI";
		default:                          return "Unknown";
	}
}

void ui::init(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// keyboard nav disabled to avoid stealing focus from the viewport

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	r3d::apply_theme();

	stats = std::make_shared<fps>();
}

void ui::pre_render()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	stats->update();

	render_stats();

	if (current_scene)
	{
		render_hierarchy();
		render_properties();
	}
}

void ui::post_render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ui::render_stats()
{
	float window_width = ImGui::GetIO().DisplaySize.x;
	float window_height = ImGui::GetIO().DisplaySize.y;

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoScrollbar;

	ImGui::SetNextWindowPos(ImVec2(0, window_height - STATUS_BAR_HEIGHT), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(window_width, STATUS_BAR_HEIGHT), ImGuiCond_Always);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 5));
	ImGui::Begin("##StatusBar", nullptr, flags);

	ImGui::Text("%d FPS", stats->get_fps());
	ImGui::SameLine();
	ImGui::Text("%.2f ms", stats->get_frame_time());

	ImGui::End();
	ImGui::PopStyleVar();
}

void ui::render_hierarchy()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;

	float panel_height = ImGui::GetIO().DisplaySize.y - STATUS_BAR_HEIGHT;

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetNextWindowSizeConstraints(ImVec2(MIN_PANEL_WIDTH, panel_height), ImVec2(MAX_PANEL_WIDTH, panel_height));
	ImGui::SetNextWindowSize(ImVec2(hierarchy_width, panel_height), ImGuiCond_Once);
	ImGui::Begin("Hierarchy", nullptr, flags);
	hierarchy_width = ImGui::GetWindowSize().x;

	// camera
	bool cam_selected = camera_selected;
	if (ImGui::Selectable("Camera", cam_selected))
	{
		if (auto prev = selected_object.lock()) { prev->selected = false; }
		camera_selected = true;
		selected_object.reset();
		selected_light_index = -1;
	}

	ImGui::Separator();

	// game objects
	auto& objects = current_scene->get_game_objects();
	for (auto& obj : objects)
	{
		bool is_selected = false;
		if (auto sel = selected_object.lock())
		{
			is_selected = (sel == obj);
		}

		if (ImGui::Selectable(obj->name.c_str(), is_selected))
		{
			if (auto prev = selected_object.lock()) { prev->selected = false; }
			obj->selected = true;
			selected_object = obj;
			selected_light_index = -1;
			camera_selected = false;
		}
	}

	ImGui::Separator();

	// lights
	auto& lights = current_scene->get_lights();
	for (int i = 0; i < (int)lights.size(); i++)
	{
		char label[32];
		snprintf(label, sizeof(label), "Light %d", i);
		bool is_selected = (selected_light_index == i);

		if (ImGui::Selectable(label, is_selected))
		{
			if (auto prev = selected_object.lock()) { prev->selected = false; }
			selected_light_index = i;
			selected_object.reset();
			camera_selected = false;
		}
	}

	ImGui::End();
}

void ui::render_properties()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;

	float window_width = ImGui::GetIO().DisplaySize.x;
	float panel_height = ImGui::GetIO().DisplaySize.y - STATUS_BAR_HEIGHT;

	ImGui::SetNextWindowSizeConstraints(ImVec2(MIN_PANEL_WIDTH, panel_height), ImVec2(MAX_PANEL_WIDTH, panel_height));
	ImGui::SetNextWindowSize(ImVec2(properties_width, panel_height), ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2(window_width - properties_width, 0), ImGuiCond_Always);
	ImGui::Begin("Properties", nullptr, flags);
	properties_width = ImGui::GetWindowSize().x;

	// game object properties
	if (auto obj = selected_object.lock())
	{
		ImGui::Text("%s", obj->name.c_str());
		ImGui::Separator();

		ImGui::Checkbox("Enabled", &obj->enabled);

		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			glm::vec3 pos = obj->get_position();
			if (ImGui::DragFloat3("Position", &pos.x, 0.1f))
			{
				obj->set_position(pos);
			}

			glm::vec3 rot = obj->get_rotation_degrees();
			if (ImGui::DragFloat3("Rotation", &rot.x, 0.5f))
			{
				obj->set_rotation_degrees(rot);
			}

			glm::vec3 scl = obj->get_scale();
			if (ImGui::DragFloat3("Scale", &scl.x, 0.01f))
			{
				obj->set_scale(scl);
			}
		}

		if (obj->renderer != nullptr && ImGui::CollapsingHeader("Renderer", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (obj->renderer->mesh)
			{
				ImGui::Text("Vertices: %d", (int)obj->renderer->mesh->vertices.size());
				ImGui::Text("Indices: %d", (int)obj->renderer->mesh->indices.size());
			}

			if (obj->renderer->material)
			{
				ImGui::Text("Diffuse Tex: %u", obj->renderer->material->diffuse_texture);
				ImGui::Text("Normal Tex: %u", obj->renderer->material->normal_texture);
			}

			if (obj->renderer->shader)
			{
				ImGui::Text("Shader: %s", shader_name(static_cast<shader::id>(0))); // TODO: store shader id
			}
		}
	}
	// light properties
	else if (selected_light_index >= 0)
	{
		auto& lights = current_scene->get_lights();
		if (selected_light_index < (int)lights.size())
		{
			auto& light = lights[selected_light_index];

			char label[32];
			snprintf(label, sizeof(label), "Light %d", selected_light_index);
			ImGui::Text("%s", label);
			ImGui::Separator();

			if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::DragFloat3("Position", &light.position.x, 0.1f);
				ImGui::ColorEdit3("Color", &light.color.x);
				ImGui::DragFloat("Intensity", &light.intensity, 0.5f, 0.0f, 1000.0f);
			}
		}
	}
	// camera properties
	else if (camera_selected)
	{
		auto& cam = current_scene->get_camera();

		ImGui::Text("Camera");
		ImGui::Separator();

		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			glm::vec3 pos = cam.get_position();
			if (ImGui::DragFloat3("Position", &pos.x, 0.1f))
			{
				cam.set_position(pos);
			}

			glm::vec3 rot = cam.get_rotation_degrees();
			if (ImGui::DragFloat3("Rotation", &rot.x, 0.5f))
			{
				cam.set_rotation_degrees(rot);
			}
		}

		if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
		{
			float fov_deg = glm::degrees(cam.fov);
			if (ImGui::DragFloat("FOV", &fov_deg, 0.5f, 1.0f, 179.0f))
			{
				cam.fov = glm::radians(fov_deg);
			}

			ImGui::DragFloat("Near", &cam.near, 0.01f, 0.001f, 100.0f);
			ImGui::DragFloat("Far", &cam.far, 10.0f, 1.0f, 100000.0f);
			ImGui::Text("Aspect: %.3f", cam.aspect_ratio);
		}
	}
	else
	{
		ImGui::TextDisabled("No selection");
	}

	ImGui::End();
}

bool ui::wants_input() const
{
	return ImGui::GetIO().WantCaptureMouse;
}

void ui::shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
