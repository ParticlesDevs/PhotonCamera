//
// Created by eszdman on 12.11.2022.
//

#ifndef PHOTONCAMERA_WIDGETS_H
#define PHOTONCAMERA_WIDGETS_H

#include <imgui.h>
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include "imgui_internal.h"
const char* TextFmt(const char* fmt, ...);
void ScrollWhenDraggingOnVoid(const ImVec2& delta, float animationK = 0.95f,float acceleration = 2.f);
bool CircleButton(const char* label, const ImVec2& size_arg,float size, const ImVec2& shift_arg);
void BeginGroupPanel(const char* name, const ImVec2& size = ImVec2(0.0f, 0.0f));
void EndGroupPanel();

#endif //PHOTONCAMERA_WIDGETS_H
