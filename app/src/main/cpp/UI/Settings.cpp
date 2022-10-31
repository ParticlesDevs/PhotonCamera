//
// Created by eszdman on 24.10.2022.
//

#include "Settings.h"

void Settings(UiManager* manager){
    auto io = ImGui::GetIO();
    auto disp = io.DisplaySize;
    ImGui::SetNextWindowSize(disp);
    ImGui::SetNextWindowPos(ImVec2{});
    if(!ImGui::Begin("Settings", nullptr,ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoBringToFrontOnFocus)){
        ImGui::End();
        return;
    }
    if (ImGui::Button("Back")){
        manager->currentLayout = MAIN;
    }
    static bool show_demo_window = false;
    ImGui::SliderFloat("SliderExample",&manager->sliderTest,0,1,"%.3f",ImGuiSliderFlags_AlwaysClamp);
    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    static int counter = 0;
    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);
    ImGui::End();

    if (show_demo_window) {
        auto prev = manager->style->WindowMenuButtonPosition;
        manager->style->WindowMenuButtonPosition = ImGuiDir_Left;
        ImGui::ShowDemoWindow(&show_demo_window);
        manager->style->WindowMenuButtonPosition = prev;
    }
}