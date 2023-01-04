//
// Created by eszdman on 23.10.2022.
//

#include "Preview.h"
#include "IconsMaterialDesign.h"
#include "Widgets.h"
#include "logs.h"

void Preview(UiManager* manager){
    auto io = ImGui::GetIO();
    auto disp = io.DisplaySize;
    ImGui::SetNextWindowSize(disp);
    ImGui::SetNextWindowPos(ImVec2{});
    auto pad = ImGui::GetStyle().WindowPadding;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,ImVec2{});

    if(!ImGui::Begin("Preview", nullptr,ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoBringToFrontOnFocus|
    ImGuiWindowFlags_NoBackground|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoDecoration)){
        ImGui::PopStyleVar();
        //ImGui::PopStyleColor();
        ImGui::End();
        return;
    }
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{0,0,0,0.35f});
    auto cursor = ImGui::GetCursorPos();
    auto edisp = disp-ImGui::GetCursorScreenPos();
    //ImGui::SetCursorPos(cursor+ImVec2{0,manager->DPI*0.25f});

    auto bsize = ImVec2{0.45f*manager->DPI,0.45f*manager->DPI};
    auto bsize2 = bsize/1.7;

    auto previewSize = ImVec2{disp.x,disp.x*manager->parameters->aspect};//Example MainSize
    //CameraNDK preview
    ImGui::SetCursorPos(cursor+ImVec2{0,(edisp.y-previewSize.y)/2});
    if(manager->parameters->cameraPreviewID != 0)
        UiTexture::Image(manager->parameters->cameraPreviewID,UiTexture::OES,previewSize);
    ImGui::SetCursorPos(cursor);
    ImGui::PushFont(io.Fonts->Fonts[3]);
    if (ImGui::BeginChild("##0",ImVec2{0,bsize2.y + pad.y * 2},false,ImGuiWindowFlags_NoDecoration)) {
        ImGui::SetCursorPos(ImGui::GetCursorPos() + pad);
        if (ImGui::Button(ICON_MD_SETTINGS, bsize2)) {
            manager->currentLayout = SETTINGS;
        }
    }
    ImGui::EndChild();
    ImGui::SetCursorPos(cursor+ImVec2{0,bsize2.y}+pad);
    ImGui::PopFont();
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{0,0,0,0.0f});
    if (ImGui::BeginChild("##1")){
        auto col = ImVec4{0,1,0,1};
        ImGui::TextColored(col,"%.2f FPS", ImGui::GetIO().Framerate);
        ImGui::TextColored(col,"Resolutions");
        ImGui::TextColored(col,"%d x %d Preview",manager->parameters->previewSize.first,manager->parameters->previewSize.second);
        ImGui::TextColored(col,"%d x %d Target",manager->parameters->rawSize.first,manager->parameters->rawSize.second);
    }
    ImGui::EndChild();
    ImGui::PopStyleColor();

    ImGui::SetCursorPos(cursor+ImVec2{0,(edisp.y-previewSize.y)/2 + previewSize.y/2});
    if(manager->parameters->requestedBuffers != 0)
        ImGui::ProgressBar(float(manager->parameters->buffCnt)/float(manager->parameters->requestedBuffers),ImVec2{edisp.x,manager->DPI*0.5f});

    ImGui::SetCursorPos(cursor+ImVec2{0,edisp.y - bsize.y*2});
    if (ImGui::BeginChild("##2")){
        auto shiftY = bsize.y;
        ImGui::SetCursorPos(ImVec2{edisp.x*0.2f-bsize.x/2,shiftY - bsize.y/2});
        ImGui::PushFont(io.Fonts->Fonts[2]);
        bool flip = CircleButton(ICON_MD_AUTORENEW,bsize,bsize.x/2,ImVec2{bsize.x/2,bsize.y/2});
        manager->parameters->flipCamera = std::max(manager->parameters->flipCamera,flip);
        ImGui::SetCursorPos(ImVec2{edisp.x*0.5f-bsize.x/2.0f,shiftY - bsize.y/2.f});
        bool shot = CircleButton(ICON_MD_LENS,bsize,bsize.x/2,ImVec2{bsize.x/2,bsize.y/2});
        manager->parameters->takePicture = std::max(manager->parameters->takePicture,shot);
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