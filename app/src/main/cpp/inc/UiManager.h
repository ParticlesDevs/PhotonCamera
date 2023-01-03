//
// Created by eszdman on 23.10.2022.
//

#ifndef PHOTONCAMERA_UIMANAGER_H
#define PHOTONCAMERA_UIMANAGER_H
#include "UiHandler.h"
#include "CameraParameters.h"

enum Layout: int {
    MAIN,
    SETTINGS,
    GALLERY
};
enum Difficulty: int {
    EASY = 0,
    NORMAL,
    EXPERT
};
class UiManager {

public:
    UiHandler handler;

    //External variables passed to UI
    ImGuiStyle* style;
    CameraParameters *parameters;
    float DPI;                                  // <unset>          // Dots per inch (DPI, or dpi) is a measure of spatial printing, video or image scanner dot density, in particular the number of individual dots that can be placed in a line within the span of 1 inch (2.54 cm)
    Layout currentLayout = MAIN;
    Difficulty currentDiff = EASY;
    float sliderTest = 0.f;
    void tick();
};


#endif //PHOTONCAMERA_UIMANAGER_H
