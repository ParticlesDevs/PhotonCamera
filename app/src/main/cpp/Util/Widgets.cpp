//
// Created by eszdman on 12.11.2022.
//
#include <Widgets.h>
#include <imgui_internal.h>
void ScrollWhenDraggingOnVoid(const ImVec2& delta, float animationK,float acceleration)
{
    ImGuiContext& g = *ImGui::GetCurrentContext();
    ImGuiWindow* window = g.CurrentWindow;
    bool hovered = false;
    bool held = false;
    static ImVec2 AvgDelta;
    static ImVec2 deltaFlow;
    static ImGuiWindow* lastWindow;
    if (g.HoveredId == 0) // If nothing hovered so far in the frame (not same as IsAnyItemHovered()!)
        ImGui::ButtonBehavior(window->Rect(), window->GetID("##scrolldraggingoverlay"), &hovered, &held, ImGuiButtonFlags_MouseButtonLeft);
    bool drag = ImGui::IsMouseDragging(ImGuiMouseButton_Left);
    bool release = ImGui::IsMouseReleased(ImGuiMouseButton_Left);
    if (hovered && drag) {
        deltaFlow = delta;
        AvgDelta.x = (AvgDelta.x + delta.x)/2.f;
        AvgDelta.y = (AvgDelta.y + delta.y)/2.f;
        lastWindow = window;//Last dragged and hovered window for animation
    }

    if(lastWindow == window) {
        if(release){
            deltaFlow = ImVec2{AvgDelta.x*acceleration,AvgDelta.y*acceleration};
        }
        window->Scroll.x += deltaFlow.x;
        window->Scroll.y += deltaFlow.y;
    } else {
        deltaFlow = ImVec2{};
    }
    deltaFlow.x = deltaFlow.x * animationK;
    deltaFlow.y = deltaFlow.y * animationK;
    lastWindow = window;
}