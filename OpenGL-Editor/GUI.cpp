#include "GUI.h"

void GUI::Draw()
{
	ImGui::Begin("Setting");

    // Konvertierung für ImGui::Combo
    std::vector<const char*> items_c_str;
    for (const auto& item : dropdownItems) {
        items_c_str.push_back(item.c_str());
    }

    ImGui::Text("Select Item:");
    if (ImGui::Combo("##ObjectSelector", &selectedItemIndex, items_c_str.data(), items_c_str.size()))
    {
        std::cout << "GUI: Auswahl geändert zu: " << dropdownItems[selectedItemIndex] << std::endl;
    }

    ImGui::Text("Current Item: %s", GetSelectedItemName().c_str());

    ImGui::End();
}
