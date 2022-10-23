//
// Created by eszdman on 24.10.2022.
//

#include "Settings.h"

void Settings(UiManager* manager){
    auto io = ImGui::GetIO();
    auto disp = io.DisplaySize;
    ImGui::SetNextWindowSize(disp);
    ImGui::SetNextWindowPos(ImVec2{});
    if(!ImGui::Begin("Settings", nullptr,ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoBringToFrontOnFocus)){
        ImGui::End();
        return;
    }
    if (ImGui::Button("Back")){
        manager->currentLayout = MAIN;
    }
    ImGui::SliderFloat("SliderExample",&manager->sliderTest,0,1,"%.3f",ImGuiSliderFlags_AlwaysClamp);
    ImGui::End();
}