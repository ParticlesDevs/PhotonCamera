//
// Created by eszdman on 23.10.2022.
//

#include "UiManager.h"
#include "Preview.h"
void UiManager::tick() {
    //ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,ImVec2{});
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize,0);
    switch (UiManager::currentLayout) {
        case Main: {
            if(preview) {
                Preview(this);
            }
            break;
        }
        case Settings: {
            break;
        }
    }
    ImGui::PopStyleVar();
}