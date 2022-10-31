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

    if(!ImGui::Begin("Preview", nullptr,ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoBringToFrontOnFocus|
    ImGuiWindowFlags_NoBackground|ImGuiWindowFlags_NoResize)){
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
        ImGui::End();
        return;
    }
    auto cursor = ImGui::GetCursorPos();
    auto edisp = disp-cursor;
    //ImGui::SetCursorPos(cursor+ImVec2{0,manager->DPI*0.25f});


    ImGui::SetCursorPos(cursor);
    auto previewSize = ImVec2{disp.x,disp.x*manager->previewAspect};//Example MainSize
    //Camera preview
    if(manager->previewTexture != 0)
        UiTexture::Image(manager->previewTexture,UiTexture::OES,previewSize);
    ImGui::SetCursorPos(cursor);
    if (ImGui::Button("Settings")) {
        manager->currentLayout = SETTINGS;
    }
    if (ImGui::BeginChild("##0")){
        auto col = ImVec4{0,1,0,1};
        ImGui::TextColored(col,"%.2f FPS", ImGui::GetIO().Framerate);
        ImGui::TextColored(col,"Resolutions");
        ImGui::TextColored(col,"%d x %d Preview",manager->previewResolution.first,manager->previewResolution.second);
        ImGui::TextColored(col,"%d x %d Camera",manager->cameraResolution.first,manager->cameraResolution.second);
    }
    ImGui::EndChild();
    auto bsize = ImVec2{0.45f*manager->DPI,0.45f*manager->DPI};
    ImGui::SetCursorPos(cursor+ImVec2{0,edisp.y - bsize.y*2});
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{0,0,0,0.35f});
    if (ImGui::BeginChild("##1")){
        auto shiftY = bsize.y;
        ImGui::SetCursorPos(ImVec2{edisp.x*0.2f-bsize.x/2,shiftY - bsize.y/2});
        ImGui::Button("Cam",bsize);
        ImGui::SetCursorPos(ImVec2{edisp.x*0.5f-bsize.x*1.2f/2.0f,shiftY - bsize.y*1.2f/2.f});
        manager->takeShot = ImGui::Button("Shot",bsize*1.2);
        ImGui::SetCursorPos(ImVec2{edisp.x*0.8f-bsize.x/2,shiftY - bsize.y/2});

#if 0 //trying ImageButton for Gallery

        ImTextureID my_tex_id = io.Fonts->TexID;
        auto my_tex_w = (float)bsize.x;
        auto my_tex_h = (float)bsize.y;
        ImVec2 uv0 = ImVec2(0.0f, 0.0f);                            // UV coordinates for lower-left
        ImVec2 uv1 = ImVec2(32.0f / my_tex_w, 32.0f / my_tex_h);    // UV coordinates for (32,32) in our texture
        ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);             // Black background
        ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);           // No tint
        if(ImGui::ImageButton("Gallery", my_tex_id, bsize, uv0, uv1, bg_col, tint_col))
        {
            manager->currentLayout = GALLERY;
        }
#else
        if(ImGui::Button("Gallery", bsize))
        {
            manager->currentLayout = GALLERY;
        }
#endif
    }
    ImGui::EndChild();


    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
    ImGui::End();
}