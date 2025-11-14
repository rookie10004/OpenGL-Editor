#include "GUI.h"

void GUI::Draw(Display& display, unsigned int viewportTextureID, Shape* shape)
{
    // ImGui Frame Start
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    SetStyle();
    ViewportWindow(display, viewportTextureID);
    SettingsWindow(display, shape);

    // ImGui Frame Ende und Rendern
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::SetStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.Colors[ImGuiCol_WindowBg] = black;

    style.Colors[ImGuiCol_Text] = white;

    style.Colors[ImGuiCol_TitleBg] = darkGrey;
    style.Colors[ImGuiCol_TitleBgActive] = lightGrey;

    style.Colors[ImGuiCol_Border] = grey;
    style.Colors[ImGuiCol_BorderShadow] = grey;

    style.Colors[ImGuiCol_Button] = grey;
    style.Colors[ImGuiCol_ButtonActive] = superLightGrey;
    style.Colors[ImGuiCol_ButtonHovered] = lightGrey;

    style.Colors[ImGuiCol_Separator] = grey;
    style.Colors[ImGuiCol_SeparatorActive] = superLightGrey;
    style.Colors[ImGuiCol_SeparatorHovered] = lightGrey;

    style.Colors[ImGuiCol_FrameBg] = grey;
    style.Colors[ImGuiCol_FrameBgActive] = superLightGrey;
    style.Colors[ImGuiCol_FrameBgHovered] = lightGrey;

    style.Colors[ImGuiCol_Header] = grey;
    style.Colors[ImGuiCol_HeaderActive] = superLightGrey;
    style.Colors[ImGuiCol_HeaderHovered] = lightGrey;

    style.Colors[ImGuiCol_PopupBg] = black;
}

void GUI::ViewportWindow(Display& display, unsigned int viewportTextureID)
{
    ImGui::SetNextWindowSize(ImVec2(display.GetWidth() - display.GetSettingsWidth(), display.GetHeight()), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(display.GetSettingsWidth(), 0), ImGuiCond_Once);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    ImGui::Begin("Object Viewport", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    ImVec2 viewportSize = ImVec2(display.GetWidth() - display.GetSettingsWidth(), display.GetHeight());

    ImGui::Image((void*)(intptr_t)viewportTextureID, viewportSize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();

    ImGui::PopStyleVar();
}

void GUI::SettingsWindow(Display& display, Shape* shape)
{
    ImGui::SetNextWindowSize(ImVec2(display.GetSettingsWidth(), display.GetHeight()), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);

    ImGui::Begin("Object Settings", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

    ImGui::SeparatorText("Shape");

    std::vector<const char*> items_c_str;
    for (const auto& item : dropdownItems) {
        items_c_str.push_back(item.c_str());
    }

    if (ImGui::Combo("##ObjectSelector", &selectedItemIndex, items_c_str.data(), items_c_str.size()))
    {
        std::cout << "GUI: Selection changed to: " << dropdownItems[selectedItemIndex] << std::endl;
    }


    if (ImGui::Button("Reset", ImVec2(50, 20)))
    {
        shape->ResetTransformation();
    }

    ImGui::SeparatorText("Color");
    ImGui::End();
}
