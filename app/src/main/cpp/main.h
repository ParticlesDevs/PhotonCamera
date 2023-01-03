//
// Created by eszdman on 23.10.2022.
//
#ifndef PHOTONCAMERA_MAIN_H
#define PHOTONCAMERA_MAIN_H
#include "imguiConf.h"
#include "imgui.h"
#include <string>
#include "imgui_impl_android.h"
#include "imgui_impl_opengl3_android.h"
#include "FileManager.h"
#include "UiManager.h"
#include "CameraNDK.h"
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
#include "EglPlate.h"

#endif

using namespace std;
// Data
static struct android_app*  g_App = nullptr;
static JNIEnv* env2 = nullptr;
static bool                 g_Initialized = false;
static char                 g_LogTag[] = "ImGuiExample";
static EglPlate *previewEgl;
static vector<ImFont*> fonts;
static int* unicodeBuffer;
// Forward declarations of helper functions
static int ShowSoftKeyboardInput();
static int PollUnicodeChars();
int GetAssetData(const char* filename, void** out_data);
static UiManager uiManager;
static class CameraNDK camera;

#endif //PHOTONCAMERA_MAIN_H
