//
// Created by eszdman on 23.10.2022.
//

#include "Preview.h"
extern bool show_simple_window;
extern bool show_app_style_editor;

void Preview(UiManager* manager){
    auto io = ImGui::GetIO();
    auto disp = io.DisplaySize;
    ImGui::SetNextWindowSize(disp);
    ImGui::SetNextWindowPos(ImVec2{});
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,ImVec2{});
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{0,0,0,0.35f});
    if(!ImGui::Begin("Preview", nullptr,ImGuiWindowFlags_NoCollapse |ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus)){
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
#ifdef ENABLE_DEMO_WINDOWS

    if(ImGui::Button("Simple Window"))
    {
        show_simple_window = !show_simple_window;
    }

    if(ImGui::Button("Style Editor"))
    {
        show_app_style_editor = !show_app_style_editor;
    }

#endif

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