#include "GUI.h"

void GUI::Draw(Display& display, unsigned int viewportTextureID, Mesh* mesh, float FPS)
{
    // ImGui Frame Start
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    SetStyle();
    ViewportWindow(display, viewportTextureID, FPS);
    SettingsWindow(display, mesh);

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

void GUI::ViewportWindow(Display& display, unsigned int viewportTextureID, float FPS)
{
    ImGui::SetNextWindowSize(ImVec2(display.GetWidth() - display.GetSettingsWidth(), display.GetHeight()), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(display.GetSettingsWidth(), 0), ImGuiCond_Once);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    ImGui::Begin("Object Viewport", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    ImGui::Image((void*)(intptr_t)viewportTextureID, ImVec2(display.GetWidth() - display.GetSettingsWidth(), display.GetHeight()), ImVec2(0, 1), ImVec2(1, 0));

    float titleBarHeight = ImGui::GetStyle().FramePadding.y * 2 + ImGui::GetFontSize();
    ImGui::SetCursorScreenPos(ImVec2(display.GetWidth() - 90, ImGui::GetWindowPos().y + titleBarHeight + 5.0f));

    ImGui::Text("FPS: %.2f", FPS);

    ImGui::End();

    ImGui::PopStyleVar();
}

void GUI::SettingsWindow(Display& display, Mesh* mesh)
{
    ImGui::SetNextWindowSize(ImVec2(display.GetSettingsWidth(), display.GetHeight()), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);

    ImGui::Begin("Object Settings", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

    ImGui::SeparatorText("Shape");
    std::vector<const char*> meshItems_c_str;
    for (const auto& item : dropdownMesh) {
        meshItems_c_str.push_back(item.c_str());
    }
    ImGui::Combo("##ObjectSelector", &selectedMeshIndex, meshItems_c_str.data(), meshItems_c_str.size());

    ImGui::SeparatorText("Material");
    std::vector<const char*> materialItems_c_str;
    for (const auto& item : dropdownMaterial) {
        materialItems_c_str.push_back(item.c_str());
    }
    ImGui::Combo("##MaterialSelector", &selectedMaterialIndex, materialItems_c_str.data(), materialItems_c_str.size());

    if (ImGui::Button("Reset", ImVec2(50, 20)))
    {
        mesh->ResetTransformation();
    }

    ImGui::End();
}
