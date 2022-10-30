// dear imgui: standalone example application for Android + OpenGL ES 3
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
#include "main.h"
#include "imgui_internal.h"

using namespace std;

extern bool show_demo_window;

int32_t getDensityDpi(android_app* app) {
    AConfiguration* config = AConfiguration_new();
    AConfiguration_fromAssetManager(config, app->activity->assetManager);
    int32_t density = AConfiguration_getDensity(config);
    AConfiguration_delete(config);
    return density;
}
void init(struct android_app* app)
{
    if (g_Initialized)
        return;

    g_App = app;
    ANativeWindow_acquire(g_App->window);
    EGLint egl_format;
    // Initialize EGL
    // This is mostly boilerplate code for EGL...
    {
        g_EglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (g_EglDisplay == EGL_NO_DISPLAY)
            __android_log_print(ANDROID_LOG_ERROR, g_LogTag, "%s", "eglGetDisplay(EGL_DEFAULT_DISPLAY) returned EGL_NO_DISPLAY");

        if (eglInitialize(g_EglDisplay, 0, 0) != EGL_TRUE)
            __android_log_print(ANDROID_LOG_ERROR, g_LogTag, "%s", "eglInitialize() returned with an error");

        const EGLint egl_attributes[] = { EGL_BLUE_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_RED_SIZE, 8, EGL_DEPTH_SIZE, 24, EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_NONE };
        EGLint num_configs = 0;
        if (eglChooseConfig(g_EglDisplay, egl_attributes, nullptr, 0, &num_configs) != EGL_TRUE)
            __android_log_print(ANDROID_LOG_ERROR, g_LogTag, "%s", "eglChooseConfig() returned with an error");
        if (num_configs == 0)
            __android_log_print(ANDROID_LOG_ERROR, g_LogTag, "%s", "eglChooseConfig() returned 0 matching config");

        // Get the first matching config
        EGLConfig egl_config;
        eglChooseConfig(g_EglDisplay, egl_attributes, &egl_config, 1, &num_configs);

        eglGetConfigAttrib(g_EglDisplay, egl_config, EGL_NATIVE_VISUAL_ID, &egl_format);
        ANativeWindow_setBuffersGeometry(g_App->window, 0, 0, egl_format);

        const EGLint egl_context_attributes[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };
        g_EglContext = eglCreateContext(g_EglDisplay, egl_config, EGL_NO_CONTEXT, egl_context_attributes);

        if (g_EglContext == EGL_NO_CONTEXT)
            __android_log_print(ANDROID_LOG_ERROR, g_LogTag, "%s", "eglCreateContext() returned EGL_NO_CONTEXT");

        g_EglSurface = eglCreateWindowSurface(g_EglDisplay, egl_config, g_App->window, NULL);
        eglMakeCurrent(g_EglDisplay, g_EglSurface, g_EglSurface, g_EglContext);
    }


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Disable loading/saving of .ini file from disk.
    // FIXME: Consider using LoadIniSettingsFromMemory() / SaveIniSettingsToMemory() to save in appropriate location for Android.
    io.IniFilename = "/data/data/com.particlesdevs.PhotonCamera/window.ini";

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplAndroid_Init(g_App->window);
    const GLchar* fragment;
    GetAssetData("shaders/ui/imgui.glsl", (void **) &fragment);
    LOGD("Fragment code: %s",fragment);
    ImGui_ImplOpenGL3_Init("#version 300 es",fragment);

    JavaVM* java_vm = g_App->activity->vm;

    jint jni_return = java_vm->AttachCurrentThread(&g_App->activity->env, NULL);
    if (jni_return != JNI_OK)
        return;

    jclass native_activity_clazz = g_App->activity->env->GetObjectClass(g_App->activity->clazz);
    if (native_activity_clazz == NULL)
        return;

    jmethodID method_id = g_App->activity->env->GetMethodID(native_activity_clazz, "getUnicodeByteBuffer", "()Ljava/nio/ByteBuffer;");
    if (method_id == NULL)
        return;
    jobject buf = g_App->activity->env->CallObjectMethod(g_App->activity->clazz, method_id);
    unicodeBuffer = (int*)g_App->activity->env->GetDirectBufferAddress(buf);
    glGenTextures(1,&camera.texID);
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, camera.texID);
    uiManager.previewTexture = camera.texID;
    method_id = g_App->activity->env->GetMethodID(native_activity_clazz, "requestPermissions", "()V");
    if (method_id == NULL)
        return;
    g_App->activity->env->CallVoidMethod(g_App->activity->clazz, method_id);
    camera.OpenCamera(TEMPLATE_PREVIEW);
    auto mainSize = camera.MainSize(AIMAGE_FORMAT_YUV_420_888,16.f/9.f);
    LOGD("Main size: %d %d",mainSize.first,mainSize.second);
    auto size = camera.PreviewSize(mainSize);
    LOGD("PreviewSize size: %d %d",size.first,size.second);
    uiManager.previewAspect = float(mainSize.first)/float(mainSize.second);
    method_id = g_App->activity->env->GetMethodID(native_activity_clazz, "getSurfaceTexture", "(III)Landroid/view/Surface;");
    if (method_id == NULL)
        return;
    LOGD("Created Surface");
    auto surface = g_App->activity->env->CallObjectMethod(g_App->activity->clazz,method_id,camera.texID,size.first,size.second);
    auto window = ANativeWindow_fromSurface(g_App->activity->env, surface);


    ANativeWindow_acquire(window);
    //ANativeWindow_setBuffersGeometry(window,1920,1080,egl_format);
    //LOGD("Width: %d",ANativeWindow_getWidth(window));
    camera.theNativeWindow = window;

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    // - Android: The TTF files have to be placed into the assets/ directory (android/app/src/main/assets), we use our GetAssetData() helper to retrieve them.

    // We load the default font with increased size to improve readability on many devices with "high" DPI.
    auto DPI = float(getDensityDpi(app));
    // Important: when calling AddFontFromMemoryTTF(), ownership of font_data is transfered by Dear ImGui by default (deleted is handled by Dear ImGui), unless we set FontDataOwnedByAtlas=false in ImFontConfig
    ImFontConfig font_cfg;
    font_cfg.SizePixels = DPI/10;
    io.Fonts->AddFontDefault(&font_cfg);
    uiManager.DPI = DPI;
    void* font_data;
    int font_data_size;
    ImFont* font;
    ImFormatString(font_cfg.Name, IM_ARRAYSIZE(font_cfg.Name), "NotoSansMono-Regular-Nerd.ttf, %dpx", (int)font_cfg.SizePixels);
    font_data_size = GetAssetData("fonts/NotoSansMono-Regular-Nerd-Font-Complete.ttf", &font_data);
    font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, uiManager.DPI/10,&font_cfg);
    fonts.push_back(font);
    io.FontDefault = font;
    //font_data_size = GetAssetData("DroidSans.ttf", &font_data);
    //font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 16.0f);
    //IM_ASSERT(font != NULL);
    //font_data_size = GetAssetData("Roboto-Medium.ttf", &font_data);
    //font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 16.0f);
    //IM_ASSERT(font != NULL);
    //font_data_size = GetAssetData("Cousine-Regular.ttf", &font_data);
    //font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 15.0f);
    //IM_ASSERT(font != NULL);
    //font_data_size = GetAssetData("ArialUni.ttf", &font_data);
    //font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Arbitrary scale-up
    ImGui::GetStyle().ScaleAllSizes(uiManager.DPI/100);

    camera.StartPreview();
    ImGuiStyle& style = ImGui::GetStyle();
    style.ChildRounding = DPI/15.f;
    style.FrameRounding = DPI/2.f;
    style.GrabRounding = DPI/15.f;
    style.WindowRounding = DPI/15.f;
    style.PopupRounding = DPI/15.f;
    style.TabRounding = DPI/15.f;
    style.FramePadding = ImVec2{DPI/20.f,DPI/20.f};
    style.WindowTitleAlign = ImVec2{0.5f,0.5f};
    //style.WindowMenuButtonPosition = ImGuiDir_None;
    g_Initialized = true;
}

void tick()
{
    ImGuiIO& io = ImGui::GetIO();
    if (g_EglDisplay == EGL_NO_DISPLAY)
        return;
    static ImVec4 clear_color = ImVec4(106.f/255.f, 72.f/255.f, 201.f/255.f, 1.00f);

    // Poll Unicode characters via native way
    // Fixed removed JNI overhead
    PollUnicodeChars();

    // Open on-screen (soft) input if requested by Dear ImGui
    static bool WantTextInputLast = false;
    if (io.WantTextInput && !WantTextInputLast)
        ShowSoftKeyboardInput();
    WantTextInputLast = io.WantTextInput;

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame();
    ImGui::NewFrame();
    uiManager.tick();

#ifdef ENABLE_DEMO_WINDOWS

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);
    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    ShowSimpleWindow();
    // 3. Show another simple window.
    ShowAnotherWindow();
    //4 Show Style editor on button press
    ShowStyleEditor();


#endif
    // Rendering
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    eglSwapBuffers(g_EglDisplay, g_EglSurface);
    if(uiManager.handler.updatePreview){
        jclass native_activity_clazz = g_App->activity->env->GetObjectClass(g_App->activity->clazz);
        jmethodID method_id = g_App->activity->env->GetMethodID(native_activity_clazz, "updateTexImage", "()V");
        g_App->activity->env->CallVoidMethod(g_App->activity->clazz, method_id);
        uiManager.handler.updatePreview = false;
    }
}

void shutdown()
{
    if (!g_Initialized)
        return;

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext();

    if (g_EglDisplay != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(g_EglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

        if (g_EglContext != EGL_NO_CONTEXT)
            eglDestroyContext(g_EglDisplay, g_EglContext);

        if (g_EglSurface != EGL_NO_SURFACE)
            eglDestroySurface(g_EglDisplay, g_EglSurface);

        eglTerminate(g_EglDisplay);
    }

    g_EglDisplay = EGL_NO_DISPLAY;
    g_EglContext = EGL_NO_CONTEXT;
    g_EglSurface = EGL_NO_SURFACE;
    ANativeWindow_release(g_App->window);

    g_Initialized = false;
}

static void handleAppCmd(struct android_app* app, int32_t appCmd)
{
    switch (appCmd)
    {
    case APP_CMD_SAVE_STATE:
        break;
    case APP_CMD_INIT_WINDOW:
        init(app);
        break;
    case APP_CMD_TERM_WINDOW:
        shutdown();
        break;
    case APP_CMD_GAINED_FOCUS:
        break;
    case APP_CMD_LOST_FOCUS:
        break;
    }
}

static int32_t handleInputEvent(struct android_app* app, AInputEvent* inputEvent)
{
    return ImGui_ImplAndroid_HandleInputEvent(inputEvent);
}

void android_main(struct android_app* app)
{

    app->onAppCmd = handleAppCmd;
    app->onInputEvent = handleInputEvent;
    int cnt = 0;
    while (true)
    {
        int out_events;
        struct android_poll_source* out_data;

        // Poll all events. If the app is not visible, this loop blocks until g_Initialized == true.
        while (ALooper_pollAll(g_Initialized ? 0 : -1, NULL, &out_events, (void**)&out_data) >= 0)
        {
            // Process one event
            if (out_data != NULL)
                out_data->process(app, out_data);

            // Exit the app by returning from within the infinite loop
            if (app->destroyRequested != 0)
            {
                // shutdown() should have been called already while processing the
                // app command APP_CMD_TERM_WINDOW. But we play save here
                if (!g_Initialized)
                    shutdown();

                return;
            }
        }

        // Initiate a new frame
        if(g_Initialized) {
            tick();
        }
        cnt++;
    }
}

// Unfortunately, there is no way to show the on-screen input from native code.
// Therefore, we call ShowSoftKeyboardInput() of the main activity implemented in MainActivity.kt via JNI.
static int ShowSoftKeyboardInput()
{
    JavaVM* java_vm = g_App->activity->vm;
    JNIEnv* java_env = NULL;

    jint jni_return = java_vm->GetEnv((void**)&java_env, JNI_VERSION_1_6);
    if (jni_return == JNI_ERR)
        return -1;

    jni_return = java_vm->AttachCurrentThread(&java_env, NULL);
    if (jni_return != JNI_OK)
        return -2;

    jclass native_activity_clazz = java_env->GetObjectClass(g_App->activity->clazz);
    if (native_activity_clazz == NULL)
        return -3;

    jmethodID method_id = java_env->GetMethodID(native_activity_clazz, "showSoftInput", "()V");
    if (method_id == NULL)
        return -4;

    java_env->CallVoidMethod(g_App->activity->clazz, method_id);

    jni_return = java_vm->DetachCurrentThread();
    if (jni_return != JNI_OK)
        return -5;

    return 0;
}

// Unfortunately, the native KeyEvent implementation has no getUnicodeChar() function.
// Therefore, we implement the processing of KeyEvents in MainActivity.kt and poll
// the resulting Unicode characters here via native buffer and send them to Dear ImGui.
static int PollUnicodeChars()
{
    ImGuiIO& io = ImGui::GetIO();
    if(unicodeBuffer[1] != 0){
        for(int i =0; i<unicodeBuffer[0];i++){
            io.AddInputCharacter(unicodeBuffer[i+1]);
        }
        unicodeBuffer[0] = 0;
    }
    return 0;}

// Helper to retrieve data placed into the assets/ directory (android/app/src/main/assets)
static int GetAssetData(const char* filename, void** outData)
{
    long num_bytes = 0;
    AAsset* asset_descriptor = AAssetManager_open(g_App->activity->assetManager, filename, AASSET_MODE_BUFFER);
    if (asset_descriptor)
    {
        num_bytes = AAsset_getLength(asset_descriptor)+1;
        *outData = IM_ALLOC(num_bytes);
        LOGD("Asset size: %d",num_bytes);
        LOGD("Asset read: %d",AAsset_read(asset_descriptor, *outData, num_bytes));
        AAsset_close(asset_descriptor);
        ((char*)*outData)[num_bytes] = 0;
        ((char*)*outData)[num_bytes-1] = 0;
        //IM_ASSERT(num_bytes_read == num_bytes);
    }
    return num_bytes;
}

extern "C" __attribute__((unused)) JNIEXPORT void JNICALL
Java_com_particlesdevs_PhotonCamera_MainActivity_onImageAvailable(JNIEnv *env, jobject thiz) {
    uiManager.handler.updatePreview = true;
}