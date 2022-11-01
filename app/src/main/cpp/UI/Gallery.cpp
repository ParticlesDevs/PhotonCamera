//
// Created by Vibhor on 10/28/2022.
//
#include "Gallery.h"

extern bool LoadTextureFromFile(const unsigned char *file_buff, int len, GLuint *out_texture, int *out_width, int *out_height);

extern int GetAssetData(const char *filename, void **outData);

void Gallery(UiManager *manager) {
    auto io = ImGui::GetIO();
    auto disp = io.DisplaySize;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(disp);
    if (!ImGui::Begin("Gallery", nullptr,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus))
    {
        ImGui::End();
        return;
    }
    if (ImGui::Button("Back"))
    {
        manager->currentLayout = MAIN;
    }
    static int row_cnt = 50;
    static int col_cnt = 3;

    ImGui::SliderInt("row_cnt", &row_cnt, 1, 500, "%d", ImGuiSliderFlags_AlwaysClamp);
    ImGui::SliderInt("col_cnt", &col_cnt, 1, 6, "%d", ImGuiSliderFlags_AlwaysClamp);

    //Populate for dummy file names
    int cur_item = 0;
    int dummydata[row_cnt][col_cnt];
    for (int i = 0; i < row_cnt; ++i)
    {
        for (int j = 0; j < col_cnt; ++j)
        {
            dummydata[i][j] = cur_item;
            cur_item++;
        }
    }
    //

    //loading a test Image from file
    static void *file_buff;
    static int file_len;
    static GLuint my_image_texture = 0;
    static int my_image_width = 0;
    static int my_image_height = 0;

    if (my_image_texture == 0) //Load this texture only once
    {
        file_len = GetAssetData("placeholder.jpg", &file_buff);
        bool ret = LoadTextureFromFile(reinterpret_cast<unsigned char *>(file_buff),
                                       file_len, &my_image_texture, &my_image_width,
                                       &my_image_height);
        IM_ASSERT(ret);
    }


    char name[50];

    //For opening an image popup
    static int which_image_clicked = -1;
    static bool was_image_clicked=false;

    //Populating Image Grid
    static ImGuiTableFlags table_flags = ImGuiTableFlags_ScrollY | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersH | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;

    if (ImGui::BeginTable("img_table", col_cnt, table_flags, ImVec2(0.0f, 0.0f))) {

        float cur_col_width;
        // Demonstrate using clipper for large vertical lists
        ImGuiListClipper clipper;
        clipper.Begin(row_cnt);
        while (clipper.Step()) {
            for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++) {
                ImGui::TableNextRow();
                for (int col = 0; col < col_cnt; col++) {
                    ImGui::TableSetColumnIndex(col);
                    cur_col_width = ImGui::GetColumnWidth();

                    sprintf(name,"img_%d",dummydata[row][col]); //image caption as well as button id

                    ImVec2 bsize = ImVec2(cur_col_width*.7f,cur_col_width*.7f);

                    //center the button/imageButton horizontally
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetColumnOffset() + (cur_col_width - bsize.x) * .5f);
                    //FIXME This can center the Button but does not center ImageButton properly
#if 1
//Image Button Start
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f)); //remove image button blue background in normal state

                    ImVec2 uv0 = ImVec2(0.0f,0.0f);
                    ImVec2 uv1 = ImVec2(1.0f,1.0f);
                    ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);             // Black background
                    ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);           // No tint

                   if(ImGui::ImageButton(name,(void *) (intptr_t) my_image_texture, bsize,uv0, uv1, bg_col, tint_col))
                   {
                       was_image_clicked ^= true;
                       which_image_clicked = dummydata[row][col];
                   }

                   ImGui::PopStyleColor(1);
//Image Button End
#else
                    if(ImGui::Button(name,bsize))
                    {
                        was_image_clicked ^= true;
                        which_image_clicked = dummydata[row][col];
                    }
#endif
                    //Image Caption
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetColumnOffset() + (cur_col_width - ImGui::CalcTextSize(name).x) * .5f); //centered text
                    ImGui::Text("%s", name);
                }
            }
        }
        ImGui::EndTable();
    }

    //Image Preview Window
     if (was_image_clicked && which_image_clicked != -1)
    {
        sprintf(name, "OpenGL ImagePreview");
        //ImGui::Begin(name, &images_opened[i]);
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(disp);
        ImGui::Begin(name, &was_image_clicked,ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::Text("Image = %d", which_image_clicked);
        ImGui::Text("pointer = %p", &my_image_texture);
        ImGui::Text("size = %d x %d", my_image_width, my_image_height);
        ImVec2 tex_size = ImVec2(ImGui::GetWindowWidth(), ImGui::GetWindowWidth() * my_image_height/my_image_width); //Fit width

        ImVec2 pos = ImGui::GetCursorScreenPos(); //used for zoom tooltip

        ImGui::Image((void *) (intptr_t) my_image_texture, tex_size);

#ifndef DISABLE_ZOOM_TOOLTIP

        ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
        ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
        if (ImGui::IsItemHovered())
        {
            auto my_tex_w = tex_size.x;
            auto my_tex_h = tex_size.y;
            ImGui::BeginTooltip();
            float region_sz = 100.0f;
            float region_x = io.MousePos.x - pos.x - region_sz * 0.5f;
            float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
            float zoom = 4.0f;
            if (region_x < 0.0f) { region_x = 0.0f; }
            else if (region_x > my_tex_w - region_sz) { region_x = my_tex_w - region_sz; }
            if (region_y < 0.0f) { region_y = 0.0f; }
            else if (region_y > my_tex_h - region_sz) { region_y = my_tex_h - region_sz; }
//            ImGui::Text("Min: (%.2f, %.2f)", region_x, region_y);
//            ImGui::Text("Max: (%.2f, %.2f)", region_x + region_sz, region_y + region_sz);
            ImVec2 uv0 = ImVec2((region_x) / my_tex_w, (region_y) / my_tex_h);
            ImVec2 uv1 = ImVec2((region_x + region_sz) / my_tex_w, (region_y + region_sz) / my_tex_h);
            ImGui::Image((void *) (intptr_t) my_image_texture, ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, tint_col, border_col);
            ImGui::EndTooltip();
        }

#endif
        ImGui::End(); //Image Preview Window
    }
    if (!was_image_clicked) { which_image_clicked = -1; }

    ImGui::End(); //Gallery Window
}