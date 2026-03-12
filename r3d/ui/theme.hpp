//
// Created by Ryan on 09/03/2026.
//

#ifndef R3D_THEME_HPP
#define R3D_THEME_HPP

#include "../../external/include/imgui/imgui.h"

namespace r3d
{
	inline void apply_theme()
	{
		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 0.0f;
		style.FrameRounding = 2.0f;
		style.GrabRounding = 2.0f;
		style.ScrollbarRounding = 2.0f;
		style.WindowBorderSize = 1.0f;
		style.FrameBorderSize = 0.0f;
		style.FramePadding = ImVec2(6, 4);
		style.ItemSpacing = ImVec2(8, 4);
		style.WindowPadding = ImVec2(8, 8);

		ImVec4* colors = style.Colors;

		// backgrounds
		colors[ImGuiCol_WindowBg]           = ImVec4(0.12f, 0.12f, 0.15f, 0.85f);
		colors[ImGuiCol_ChildBg]            = ImVec4(0.12f, 0.12f, 0.15f, 0.85f);
		colors[ImGuiCol_PopupBg]            = ImVec4(0.10f, 0.10f, 0.13f, 0.90f);

		// borders
		colors[ImGuiCol_Border]             = ImVec4(0.20f, 0.20f, 0.25f, 1.00f);
		colors[ImGuiCol_BorderShadow]       = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

		// frame (input fields, checkboxes)
		colors[ImGuiCol_FrameBg]            = ImVec4(0.18f, 0.18f, 0.22f, 1.00f);
		colors[ImGuiCol_FrameBgHovered]     = ImVec4(0.22f, 0.22f, 0.28f, 1.00f);
		colors[ImGuiCol_FrameBgActive]      = ImVec4(0.25f, 0.25f, 0.32f, 1.00f);

		// title bar
		colors[ImGuiCol_TitleBg]            = ImVec4(0.08f, 0.08f, 0.10f, 1.00f);
		colors[ImGuiCol_TitleBgActive]      = ImVec4(0.10f, 0.10f, 0.14f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed]   = ImVec4(0.08f, 0.08f, 0.10f, 0.75f);

		// header (collapsing headers, tree nodes)
		colors[ImGuiCol_Header]             = ImVec4(0.18f, 0.22f, 0.30f, 1.00f);
		colors[ImGuiCol_HeaderHovered]      = ImVec4(0.22f, 0.28f, 0.40f, 1.00f);
		colors[ImGuiCol_HeaderActive]       = ImVec4(0.25f, 0.32f, 0.45f, 1.00f);

		// buttons
		colors[ImGuiCol_Button]             = ImVec4(0.20f, 0.22f, 0.28f, 1.00f);
		colors[ImGuiCol_ButtonHovered]      = ImVec4(0.25f, 0.30f, 0.40f, 1.00f);
		colors[ImGuiCol_ButtonActive]       = ImVec4(0.28f, 0.35f, 0.48f, 1.00f);

		// tabs
		colors[ImGuiCol_Tab]                = ImVec4(0.12f, 0.12f, 0.15f, 1.00f);
		colors[ImGuiCol_TabHovered]         = ImVec4(0.22f, 0.28f, 0.40f, 1.00f);
		colors[ImGuiCol_TabActive]          = ImVec4(0.18f, 0.22f, 0.30f, 1.00f);

		// scrollbar
		colors[ImGuiCol_ScrollbarBg]        = ImVec4(0.10f, 0.10f, 0.12f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab]      = ImVec4(0.25f, 0.25f, 0.30f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.30f, 0.30f, 0.38f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.35f, 0.35f, 0.45f, 1.00f);

		// separator
		colors[ImGuiCol_Separator]          = ImVec4(0.20f, 0.20f, 0.25f, 1.00f);
		colors[ImGuiCol_SeparatorHovered]   = ImVec4(0.25f, 0.30f, 0.40f, 1.00f);
		colors[ImGuiCol_SeparatorActive]    = ImVec4(0.30f, 0.38f, 0.50f, 1.00f);

		// slider / drag
		colors[ImGuiCol_SliderGrab]         = ImVec4(0.30f, 0.40f, 0.60f, 1.00f);
		colors[ImGuiCol_SliderGrabActive]   = ImVec4(0.35f, 0.48f, 0.72f, 1.00f);

		// check mark
		colors[ImGuiCol_CheckMark]          = ImVec4(0.40f, 0.55f, 0.80f, 1.00f);

		// text
		colors[ImGuiCol_Text]              = ImVec4(0.85f, 0.85f, 0.88f, 1.00f);
		colors[ImGuiCol_TextDisabled]      = ImVec4(0.45f, 0.45f, 0.50f, 1.00f);
	}
}

#endif //R3D_THEME_HPP
