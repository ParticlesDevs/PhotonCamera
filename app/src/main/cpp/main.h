//
// Created by eszdman on 23.10.2022.
//

#ifndef PHOTONCAMERA_MAIN_H
#define PHOTONCAMERA_MAIN_H
#include "imgui.h"
#include <string>
#include "imgui_impl_android.h"
#include "imgui_impl_opengl3_android.h"
#include "FileManager.h"
#include "UiManager.h"
#include "Camera.h"
#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/asset_manager.h>
#include <android/surface_texture.h>
#include <EGL/egl.h>
#include <gl.h>
#include "jni.h"
#include <vector>

#ifdef ENABLE_DEMO_WINDOWS
#include "Demos.h"
#endif

using namespace std;
// Data
static EGLDisplay           g_EglDisplay = EGL_NO_DISPLAY;
static EGLSurface           g_EglSurface = EGL_NO_SURFACE;
static EGLContext           g_EglContext = EGL_NO_CONTEXT;
static struct android_app*  g_App = nullptr;
static JNIEnv* env2 = nullptr;
static bool                 g_Initialized = false;
static char                 g_LogTag[] = "ImGuiExample";
static vector<ImFont*> fonts;
static int* unicodeBuffer;
// Forward declarations of helper functions
static int ShowSoftKeyboardInput();
static int PollUnicodeChars();
int GetAssetData(const char* filename, void** out_data);
static UiManager uiManager;
static Camera camera;

#endif //PHOTONCAMERA_MAIN_H
