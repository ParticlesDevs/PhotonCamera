//
// Created by eszdman on 23.10.2022.
//

#ifndef PHOTONCAMERA_UIMANAGER_H
#define PHOTONCAMERA_UIMANAGER_H

enum Layout: int {
    MAIN,
    SETTINGS
};
class UiManager {

public:
    Layout currentLayout = MAIN;
    bool takeShot = false;
    float sliderTest = 0.f;
    void tick();
};


#endif //PHOTONCAMERA_UIMANAGER_H
