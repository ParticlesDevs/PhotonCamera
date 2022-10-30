//
// Created by Vibhor on 10/28/2022.
//
#include "Demos.h"

bool show_demo_window = false;
bool show_another_window = false;
bool show_simple_window = false;
bool show_app_style_editor = false;

void ShowSimpleWindow()
{
#ifdef ENABLE_DEMO_WINDOWS

    if(show_simple_window)
    {
        static float f = 0.0f;
        static int counter = 0;
        static ImVec4 clear_color = ImVec4(106.f/255.f, 72.f/255.f, 201.f/255.f, 1.00f);

        ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

#endif
}

void ShowAnotherWindow()
{
#ifdef ENABLE_DEMO_WINDOWS

    if (show_another_window)
    {
        ImGui::Begin("Another Window",&show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }

#endif
}

void ShowStyleEditor()
{
#ifdef ENABLE_DEMO_WINDOWS
    //style editor extracted from imgui_demo.cpp
    if (show_app_style_editor)
    {
        ImGui::Begin("Dear ImGui Style Editor", &show_app_style_editor);
        ImGui::ShowStyleEditor();
        ImGui::End();
    }

#endif
}

