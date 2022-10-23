//
// Created by eszdman on 23.10.2022.
//

#include "Preview.h"

void Preview(UiManager* manager){
    auto io = ImGui::GetIO();
    auto disp = io.DisplaySize;
    ImGui::SetNextWindowSize(disp);
    ImGui::SetNextWindowPos(ImVec2{});
    if(!ImGui::Begin("Preview", nullptr,ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoBringToFrontOnFocus)){
        ImGui::End();
        return;
    }
    ImGui::SetCursorPos(disp*0.2f);
    auto previewSize = disp*0.4f;//Example previewSize
    if(ImGui::BeginChild("previewTex",previewSize, true)){

        ImGui::EndChild();
    }
    auto bsize = ImVec2{60*disp.x/io.DPI,60*disp.x/io.DPI};
    ImGui::SetCursorPos(ImVec2{disp.x*0.2f-bsize.x/2,disp.y*0.88f});
    ImGui::Button("Cam",bsize);
    ImGui::SetCursorPos(ImVec2{disp.x*0.5f-bsize.x/2,disp.y*0.88f});
    ImGui::Button("Shot",bsize);
    ImGui::SetCursorPos(ImVec2{disp.x*0.8f-bsize.x/2,disp.y*0.88f});
    ImGui::Button("Gallery",bsize);

    ImGui::End();
}