#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_SDL3.h"
#include "Display.h"
#include "Shape.h"

class GUI
{
private:
	std::vector<std::string> dropdownItems = { "Cube", "Pyramid", "Torus"};
	int selectedItemIndex = 0;

	ImVec4 white = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 black = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	ImVec4 grey = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
	ImVec4 lightGrey = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
	ImVec4 superLightGrey = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
	ImVec4 darkGrey = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);

public:
	GUI() = default;

	const std::string& GetSelectedItemName() const { return dropdownItems[selectedItemIndex]; }
	void Draw(Display& display, unsigned int viewportTextureID, Shape* shape);
	void SetStyle();
	void ViewportWindow(Display& display, unsigned int viewportTextureID);
	void SettingsWindow(Display& display, Shape* shape);
};

