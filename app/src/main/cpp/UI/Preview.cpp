//
// Created by eszdman on 23.10.2022.
//

#include "Preview.h"
#include "IconsMaterialDesign.h"
#include "Widgets.h"

void Preview(UiManager* manager){
    auto io = ImGui::GetIO();
    auto disp = io.DisplaySize;
    ImGui::SetNextWindowSize(disp);
    ImGui::SetNextWindowPos(ImVec2{});
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,ImVec2{});

    if(!ImGui::Begin("Preview", nullptr,ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoBringToFrontOnFocus|
    ImGuiWindowFlags_NoBackground|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoDecoration)){
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
        ImGui::End();
        return;
    }
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{0,0,0,0.35f});
    auto cursor = ImGui::GetCursorPos();
    auto edisp = disp-ImGui::GetCursorScreenPos();
    //ImGui::SetCursorPos(cursor+ImVec2{0,manager->DPI*0.25f});

    auto bsize = ImVec2{0.45f*manager->DPI,0.45f*manager->DPI};
    auto bsize2 = bsize/1.7;
    ImGui::SetCursorPos(cursor);
    auto previewSize = ImVec2{disp.x,disp.x*manager->previewAspect};//Example MainSize
    //Camera preview

    if(manager->previewTexture != 0)
        UiTexture::Image(manager->previewTexture,UiTexture::OES,previewSize);
    ImGui::SetCursorPos(cursor);
    ImGui::PushFont(io.Fonts->Fonts[3]);
    if (ImGui::BeginChild("##0",ImVec2{0,bsize2.y},false,ImGuiWindowFlags_NoDecoration)) {
        ImGui::SetCursorPos(ImGui::GetCursorPos()+ImVec2{bsize2.x/4,0});
        if (ImGui::Button(ICON_MD_SETTINGS, bsize2)) {
            manager->currentLayout = SETTINGS;
        }
        ImGui::EndChild();
    }
    ImGui::SetCursorPos(cursor+ImVec2{0,bsize2.y});
    ImGui::PopFont();
    if (ImGui::BeginChild("##1")){
        auto col = ImVec4{0,1,0,1};
        ImGui::TextColored(col,"%.2f FPS", ImGui::GetIO().Framerate);
        ImGui::TextColored(col,"Resolutions");
        ImGui::TextColored(col,"%d x %d Preview",manager->previewResolution.first,manager->previewResolution.second);
        ImGui::TextColored(col,"%d x %d Camera",manager->cameraResolution.first,manager->cameraResolution.second);
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(cursor+ImVec2{0,edisp.y - bsize.y*2});
    if (ImGui::BeginChild("##2")){
        auto shiftY = bsize.y;
        ImGui::SetCursorPos(ImVec2{edisp.x*0.2f-bsize.x/2,shiftY - bsize.y/2});
        ImGui::PushFont(io.Fonts->Fonts[2]);
        CircleButton(ICON_MD_AUTORENEW,bsize,bsize.x/2,ImVec2{bsize.x/2,bsize.y/2});
        ImGui::SetCursorPos(ImVec2{edisp.x*0.5f-bsize.x/2.0f,shiftY - bsize.y/2.f});
        bool shot = CircleButton(ICON_MD_LENS,bsize,bsize.x/2,ImVec2{bsize.x/2,bsize.y/2});
        if(manager->takePicture != nullptr)
            *manager->takePicture = shot;
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
        if(CircleButton(ICON_MD_PHOTO_CAMERA_BACK,bsize,bsize.x/2,ImVec2{bsize.x/2,bsize.y/2}))
        {
            manager->currentLayout = GALLERY;
        }
#endif
        ImGui::PopFont();
    }
    ImGui::EndChild();


    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
    ImGui::End();
}