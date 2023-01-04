//
// Created by eszdman on 24.10.2022.
//

#include "Settings.h"
#include "Widgets.h"
#include "IconsMaterialDesign.h"
#include "logs.h"
#include <cstdlib>
#include <string>
void Settings(UiManager* manager){
    auto io = ImGui::GetIO();
    auto disp = io.DisplaySize;
    ImGui::SetNextWindowSize(disp);
    ImGui::SetNextWindowPos(ImVec2{});
    if(!ImGui::Begin("Settings", nullptr,ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove
    |ImGuiWindowFlags_NoBringToFrontOnFocus
    |ImGuiWindowFlags_NoDecoration)){
        ImGui::End();
        return;
    }
    ImGui::PushFont(io.Fonts->Fonts[3]);
    if (ImGui::Button(ICON_MD_ARROW_BACK_IOS_NEW)){
        manager->currentLayout = MAIN;
    }
    ImGui::PopFont();
    BeginGroupPanel(TextFmt("Camera: %s Settings ",manager->parameters->cameraIDs[manager->parameters->selectedID].c_str()),ImVec2{-1,0});
    {
        auto currentMain = manager->parameters->currentSensor->rawNames[manager->parameters->selectedRaw].c_str();
        if(ImGui::BeginCombo("##MainSize",currentMain)) {
            for(int i =0; i<manager->parameters->currentSensor->rawSizes.size(); i++){
                auto item = manager->parameters->currentSensor->rawNames[i].c_str();
                bool is_selected = (manager->parameters->selectedRaw == i); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(item, is_selected)){
                    manager->parameters->selectedRaw = i;
                    manager->parameters->resetResCamera = true;
                }
                if (is_selected)
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndCombo();
        }
        auto currentPreview = manager->parameters->currentSensor->previewNames[manager->parameters->selectedPreview].c_str();
        if(ImGui::BeginCombo("##PreviewSize",currentPreview)) {
            for(int i =0; i<manager->parameters->currentSensor->previewSizes.size(); i++){
                auto item = manager->parameters->currentSensor->previewNames[i].c_str();
                bool is_selected = (manager->parameters->selectedPreview == i); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(item, is_selected)){
                    manager->parameters->selectedPreview = i;
                    manager->parameters->resetResCamera = true;
                }
                if (is_selected)
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndCombo();
        }
    }
    EndGroupPanel();

    static bool show_demo_window = false;
    ImGui::SliderInt("FrameCount",&manager->parameters->maxRequest,3,50);
    ImGui::SliderFloat("SliderExample",&manager->sliderTest,0,1,"%.3f",ImGuiSliderFlags_AlwaysClamp);
    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    static int diffNum = 0;
    ImGui::Text("UI Difficulty");
    ImGui::RadioButton("EASY", &diffNum, 0); ImGui::SameLine();
    ImGui::RadioButton("NORMAL", &diffNum, 1); ImGui::SameLine();
    ImGui::RadioButton("EXPERT", &diffNum, 2);
    manager->currentDiff = static_cast<Difficulty>(diffNum);

    static float scrollAccel = 2.f;
    static float motionK = 0.95f;
    if(manager->currentDiff == EXPERT){
        ImGui::Text("Scroll acceleration");
        ImGui::SliderFloat("##Accel",&scrollAccel,0.f,5.f);
        ImGui::Text("Scroll friction");
        ImGui::SliderFloat("##Friction",&motionK,0.8f,1.f);
    }
    static int counter = 0;
    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;

    if(manager->currentDiff > EASY) {
        for (int i = 0; i < 90; i++) {

            if (ImGui::Button((std::string("Button") +
                               char(i)).c_str()))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
        }
    }


    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);
    ImGuiContext& g = *ImGui::GetCurrentContext();
    ImGuiWindow* window = g.CurrentWindow;
    auto delta = io.MouseDelta;
    //if(ImGui::IsMouseDragging(ImGuiMouseButton_Left))
    //    window->Scroll -= delta;
    ScrollWhenDraggingOnVoid(io.MouseDelta*ImVec2{0,-1},motionK,scrollAccel);
    ImGui::End();

    if (show_demo_window) {
        auto prev = manager->style->WindowMenuButtonPosition;
        manager->style->WindowMenuButtonPosition = ImGuiDir_Left;
        ImGui::ShowDemoWindow(&show_demo_window);
        manager->style->WindowMenuButtonPosition = prev;
    }
}