//
// Created by eszdman on 23.10.2022.
//

#include "UiManager.h"
#include "Preview.h"
#include "Settings.h"

void UiManager::tick() {
    //ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,ImVec2{});
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize,0);
    auto prevPos = style->WindowMenuButtonPosition;
    style->WindowMenuButtonPosition = ImGuiDir_None;
    switch (UiManager::currentLayout) {
        case MAIN: {
            Preview(this);
            break;
        }
        case SETTINGS: {
            Settings(this);
            break;
        }
    }
    style->WindowMenuButtonPosition = prevPos;
    ImGui::PopStyleVar();
}