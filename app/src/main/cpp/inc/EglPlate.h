//
// Created by eszdman on 12.11.2022.
//

#ifndef PHOTONCAMERA_EGLPLATE_H
#define PHOTONCAMERA_EGLPLATE_H

#include <EGL/egl.h>
#include <logs.h>
class EglPlate{
private:
public:
    EGLDisplay           g_EglDisplay = EGL_NO_DISPLAY;
    EGLSurface           g_EglSurface = EGL_NO_SURFACE;
    EGLContext           g_EglContext = EGL_NO_CONTEXT;

    EglPlate(ANativeWindow* window);
    ~EglPlate();
};
#endif //PHOTONCAMERA_EGLPLATE_H
