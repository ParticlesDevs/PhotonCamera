//
// Created by eszdman on 23.10.2022.
//

#ifndef PHOTONCAMERA_UIMANAGER_H
#define PHOTONCAMERA_UIMANAGER_H

enum Layout: int {
    Main,
    Settings
};
class UiManager {
    Layout currentLayout = Main;

public:
    bool preview = true;
    bool takeShot = false;
    float sliderTest = 0.f;
    void tick();
};


#endif //PHOTONCAMERA_UIMANAGER_H
