//
// Created by Vibhor on 10/28/2022.
//
#include "Gallery.h"

void Gallery(UiManager *manager)
{
    auto io = ImGui::GetIO();
    auto disp = io.DisplaySize;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(disp);
    if (!ImGui::Begin("Gallery", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove))
    {
        ImGui::End();
        return;
    }
    if (ImGui::Button("Back"))
    {
        manager->currentLayout = MAIN;
    }
    static int img_count = 32;
    static int column = 4;

    ImGui::SliderInt("img_count", &img_count, 0, 200, "%d", ImGuiSliderFlags_AlwaysClamp);
    ImGui::SliderInt("column", &column, 1, 6, "%d", ImGuiSliderFlags_AlwaysClamp);

    //Image Grid
    ImGui::Columns(column, nullptr);
    ImGui::Separator();
    char name[16];
    for (int i = 0; i < img_count; i++)
    {
        if (i > 0 && i % column == 0) { ImGui::Separator(); }
        sprintf(name, "%d", i);
        if(ImGui::Button(name, ImVec2(0.5f * manager->DPI, 0.5f * manager->DPI)))
        {
            ImGui::Begin("Image",nullptr);
            ImGui::Text("Image: %d",i);
            ImGui::End();
        }
        ImGui::NextColumn();
    }
    ImGui::Columns(1);
    ImGui::Separator();
    ImGui::End();
}