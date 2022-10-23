//
// Created by eszdman on 23.10.2022.
//

#ifndef PHOTONCAMERA_MAIN_H
#define PHOTONCAMERA_MAIN_H
#include "imgui.h"
#include "imgui_impl_android.h"
#include "imgui_impl_opengl3.h"
#include "UiManager.h"
#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/asset_manager.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <vector>
using namespace std;

// Data
static EGLDisplay           g_EglDisplay = EGL_NO_DISPLAY;
static EGLSurface           g_EglSurface = EGL_NO_SURFACE;
static EGLContext           g_EglContext = EGL_NO_CONTEXT;
static struct android_app*  g_App = NULL;
static bool                 g_Initialized = false;
static char                 g_LogTag[] = "ImGuiExample";
static vector<ImFont*> fonts;
// Forward declarations of helper functions
static int ShowSoftKeyboardInput();
static int PollUnicodeChars();
static int GetAssetData(const char* filename, void** out_data);
static UiManager uiManager;

#endif //PHOTONCAMERA_MAIN_H
