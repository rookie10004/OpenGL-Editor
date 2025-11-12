#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_SDL3.h"
#include "Display.h"

class GUI
{
private:
	std::vector<std::string> dropdownItems = { "Cube", "Pyramid", "Torus"};
	int selectedItemIndex = 0;

public:
	GUI() = default;

	const std::string& GetSelectedItemName() const { return dropdownItems[selectedItemIndex]; }
	void Draw(Display& display, unsigned int viewportTextureID);
	void ViewportWindow(Display& display, unsigned int viewportTextureID);
	void SettingsWindow(Display& display);
};

