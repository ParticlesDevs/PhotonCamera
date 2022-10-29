//
// Created by eszdman on 23.10.2022.
//

#ifndef PHOTONCAMERA_UIMANAGER_H
#define PHOTONCAMERA_UIMANAGER_H
#include <gl.h>
#include "UiHandler.h"
#include "imgui.h"
enum Layout: int {
    MAIN,
    SETTINGS
};
class UiManager {

public:
    UiHandler handler;
    GLuint previewTexture;
    float previewAspect = 4.f/3.f;
    float DPI;                                  // <unset>          // Dots per inch (DPI, or dpi) is a measure of spatial printing, video or image scanner dot density, in particular the number of individual dots that can be placed in a line within the span of 1 inch (2.54 cm)
    Layout currentLayout = MAIN;
    bool takeShot = false;
    float sliderTest = 0.f;
    void tick();
};


#endif //PHOTONCAMERA_UIMANAGER_H
