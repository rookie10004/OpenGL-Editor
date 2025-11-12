#include "GUI.h"

void GUI::Draw(Display& display, unsigned int viewportTextureID)
{
    // ImGui Frame Start
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    ViewportWindow(display, viewportTextureID);
    SettingsWindow(display);

    // ImGui Frame Ende und Rendern
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::ViewportWindow(Display& display, unsigned int viewportTextureID)
{
    ImGui::SetNextWindowSize(ImVec2(display.GetWidth() - 200, display.GetHeight()), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(200.0f, 0.0f), ImGuiCond_Once);

    ImGui::Begin("Object", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);

    ImVec2 viewportSize = ImVec2((float)(display.GetWidth() - 200), (float)display.GetHeight());

    ImGui::Image((void*)(intptr_t)viewportTextureID, viewportSize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
}

void GUI::SettingsWindow(Display& display)
{
    ImGui::SetNextWindowSize(ImVec2(display.GetWidth() - 600, display.GetHeight()), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Once);

    ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

    std::vector<const char*> items_c_str;
    for (const auto& item : dropdownItems) {
        items_c_str.push_back(item.c_str());
    }

    if (ImGui::Combo("##ObjectSelector", &selectedItemIndex, items_c_str.data(), items_c_str.size()))
    {
        std::cout << "GUI: Selection changed to: " << dropdownItems[selectedItemIndex] << std::endl;
    }

    ImGui::End();
}
