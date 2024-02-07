#include "include/gui.hpp"

Gui::Gui(SceneConfiguration  *sceneConfig, Bezier_plane *bezierPlane) {
    this->sceneConfig = sceneConfig;
    this->bezierPlane = bezierPlane;
}

void Gui::Show(bool* p_open) {
    if(!ImGui::Begin("Scene Config", p_open, 0)) {
        ImGui::End();
        return;
    }
    ImGui::SeparatorText("Tesselation");
    ImGui::SliderInt("level (1:64)", &(sceneConfig->tesselationLevel), 1, 64, 0);

    ImGui::SeparatorText("Weather");
    ImGui::Checkbox("Day", &(sceneConfig->day));
    ImGui::Checkbox("Fog", &(sceneConfig->fog));
    ImGui::SliderFloat("Fog Intensity (0:1)", &(sceneConfig->fogIntensity), 0.0f, 1.0f, 0);

    ImGui::SeparatorText("Camera");


    ImGui::SeparatorText("Control Point height controller");
    const int rows = 4;
    const int columns = 4;
    const float spacing = 10.0f;
    const ImVec2 small_slider_size(25, (float)(int)((200.0f - (rows - 1) * spacing) / rows));
    for (int nx = 0; nx < columns; nx++)
    {
        if (nx > 0) ImGui::SameLine();
        ImGui::BeginGroup();
        for (int ny = rows - 1; ny >= 0; ny--)
        {
            ImGui::PushID(nx * rows + ny);
            ImGui::VSliderFloat("##v", small_slider_size, &bezierPlane->vertices[(nx*rows + ny) * 3 + 2], -1.0f, 1.0f, "");
            ImGui::PopID();
        }
        ImGui::EndGroup();
    }


    ImGui::End();
}

