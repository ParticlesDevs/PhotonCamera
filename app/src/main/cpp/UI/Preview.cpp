//
// Created by eszdman on 23.10.2022.
//

#include "Preview.h"

void Preview(UiManager* manager){
    auto io = ImGui::GetIO();
    auto disp = io.DisplaySize;
    ImGui::SetNextWindowSize(disp);
    ImGui::SetNextWindowPos(ImVec2{});
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,ImVec2{});
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{0,0,0,0.35f});
    if(!ImGui::Begin("Preview", nullptr,ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoBringToFrontOnFocus|ImGuiWindowFlags_NoBackground)){
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
        ImGui::End();
        return;
    }

    auto cursor = ImGui::GetCursorPos();
    ImGui::SetCursorPos(cursor);
    auto previewSize = ImVec2{disp.x,disp.x*manager->previewAspect};//Example MainSize
    //Camera preview
    if(manager->previewTexture != 0)
        UiTexture::Image(manager->previewTexture,UiTexture::OES,previewSize);
    ImGui::SetCursorPos(cursor);
    if (ImGui::Button("Settings")) {
        manager->currentLayout = SETTINGS;
    }
    ImGui::SetCursorPos(cursor+ImVec2{0,previewSize.y-disp.y*0.1f});
    if (ImGui::BeginChild("##1")){
        auto bsize = ImVec2{0.5f*manager->DPI,0.5f*manager->DPI};
        auto shiftY = -(previewSize.y-disp.y)/4.f;
        ImGui::SetCursorPos(ImVec2{disp.x*0.2f-bsize.x/2,shiftY});
        ImGui::Button("Cam",bsize);
        ImGui::SetCursorPos(ImVec2{disp.x*0.5f-bsize.x/2,shiftY});
        manager->takeShot = ImGui::Button("Shot",bsize);
        ImGui::SameLine(0.f,disp.x*1.f/9.f);
        ImGui::SetCursorPos(ImVec2{disp.x*0.8f-bsize.x/2,shiftY});
        ImGui::Button("Gallery",bsize);
    }
    ImGui::EndChild();



    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
    ImGui::End();
}