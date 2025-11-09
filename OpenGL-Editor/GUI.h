#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "imgui.h"

class GUI
{
private:
	std::vector<std::string> dropdownItems = { "Square", "Triangle", "Pyramid"};
	int selectedItemIndex = 0;

public:
	GUI() = default;

	const std::string& GetSelectedItemName() const { return dropdownItems[selectedItemIndex]; }
	void Draw();
};

