#include "main.h"
#include "imgui_internal.h"
#include "IconsMaterialDesign.h"

using namespace std;
int32_t getDensityDpi(android_app* app) {
    AConfiguration* config = AConfiguration_new();
    AConfiguration_fromAssetManager(config, app->activity->assetManager);
    int32_t density = AConfiguration_getDensity(config);
    AConfiguration_delete(config);
    return density;
}
void setNDKPreview(){
    jclass native_activity_clazz = env2->GetObjectClass(g_App->activity->clazz);
    if (native_activity_clazz == nullptr)
        return;
    auto method_id = env2->GetMethodID(native_activity_clazz, "getSurfaceTexture", "(III)Landroid/view/Surface;");
    if (method_id == nullptr)
        return;
    LOGD("Created Surface");
    auto surface = env2->CallObjectMethod(g_App->activity->clazz,method_id,camera.parameters->cameraPreviewID,camera.parameters->previewSize.first,camera.parameters->previewSize.second);
    if(camera.theNativeWindow != nullptr){
        ANativeWindow_release(camera.theNativeWindow);
    }
    auto window = ANativeWindow_fromSurface(env2, surface);
    ANativeWindow_acquire(window);
    camera.theNativeWindow = window;
}
void CameraNDKInit(){
    camera.OpenCamera(TEMPLATE_PREVIEW,AIMAGE_FORMAT_RAW16,4.f/3.f);
    glGenTextures(1,&camera.parameters->cameraPreviewID);
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, camera.parameters->cameraPreviewID);

    uiManager.parameters = camera.parameters;
    setNDKPreview();
}
void CameraNDKReInit(){
    camera.Reset();
    LOGD("Selected preview size %d %d",camera.parameters->rawSize.first,camera.parameters->rawSize.second);
    uiManager.parameters = camera.parameters;
    setNDKPreview();
    camera.StartPreview();
}
void initUICamera(struct android_app* app)
{
    LOGD("Init");
    if (g_Initialized)
        return;

    g_App = app;
    ANativeWindow_acquire(g_App->window);
    previewEgl = new EglPlate(g_App->window);
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
    //getAllImageFiles(); //Causing crush on some devices

    jint jni_return = java_vm->AttachCurrentThread(&env2, nullptr);
    if (jni_return != JNI_OK)
        return;

    jclass native_activity_clazz = env2->GetObjectClass(g_App->activity->clazz);
    if (native_activity_clazz == nullptr)
        return;

    jmethodID method_id = env2->GetMethodID(native_activity_clazz, "getUnicodeByteBuffer", "()Ljava/nio/ByteBuffer;");
    if (method_id == nullptr)
        return;
    jobject buf = env2->CallObjectMethod(g_App->activity->clazz, method_id);
    unicodeBuffer = (int*)env2->GetDirectBufferAddress(buf);
    CameraNDKInit();

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

    io.Fonts->AddFontDefault(&font_cfg);
    uiManager.DPI = DPI;
    void* font_data;
    int font_data_size;
    ImFont* font;

    font_cfg.SizePixels = DPI/10;
    ImFormatString(font_cfg.Name, IM_ARRAYSIZE(font_cfg.Name), "NotoSansMono-Regular-Nerd.ttf, %dpx", (int)font_cfg.SizePixels);
    font_data_size = GetAssetData("fonts/NotoSansMono-Regular-Nerd-Font-Complete.ttf", &font_data);
    font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, font_cfg.SizePixels,&font_cfg);
    fonts.push_back(font);
    io.FontDefault = font;
    font_cfg.SizePixels = DPI/10;
    ImFormatString(font_cfg.Name, IM_ARRAYSIZE(font_cfg.Name), FONT_ICON_FILE_NAME_MD ", %dpx", (int)font_cfg.SizePixels);
    font_data_size = GetAssetData("fonts/" FONT_ICON_FILE_NAME_MD, &font_data);
    font_cfg.SizePixels = uiManager.DPI/3;
    //font_cfg.MergeMode = true;
    ImWchar ranges[] =
    {
            0xe3fa, 0xe3fa,
            0xe863, 0xe863,
            0xef68,0xef68,
            0xe8b8,0xe8b8,
            0xe2ea,0xe2ea,
            0,
    };
    font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, font_cfg.SizePixels,&font_cfg,ranges);
    fonts.push_back(font);
    font_cfg.SizePixels = font_cfg.SizePixels/(2.0);
    font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, font_cfg.SizePixels,&font_cfg,ranges);
    fonts.push_back(font);

    io.Fonts->Build();

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
    //style.Colors[ImGuiCol_Button] = ImVec4{0,0,0,0.1};
    style.Colors[ImGuiCol_ButtonHovered] = style.Colors[ImGuiCol_Button];
    style.Colors[ImGuiCol_HeaderHovered] = style.Colors[ImGuiCol_Header];
    style.Colors[ImGuiCol_TabHovered] = style.Colors[ImGuiCol_Tab];
    style.Colors[ImGuiCol_FrameBgHovered] = style.Colors[ImGuiCol_FrameBg];
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = style.Colors[ImGuiCol_ScrollbarGrab];
    //style.WindowMenuButtonPosition = ImGuiDir_None;
    uiManager.style = &ImGui::GetStyle();
    g_Initialized = true;
}

void tick()
{
    ImGuiIO& io = ImGui::GetIO();
    if (previewEgl->g_EglDisplay == EGL_NO_DISPLAY)
        return;
    //static ImVec4 clear_color = ImVec4(106.f/255.f, 72.f/255.f, 201.f/255.f, 1.00f);
    static ImVec4 clear_color = ImVec4(0.35f, 0.35f, 0.35f, 1.f);
    //static ImVec4 clear_color = ImVec4(0.f, 0.f, 0.f, 1.f);

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
    //Draw all our forms
    uiManager.tick();

    // Rendering
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    eglSwapBuffers(previewEgl->g_EglDisplay, previewEgl->g_EglSurface);
    if(uiManager.handler.updatePreview){
        jclass native_activity_clazz = env2->GetObjectClass(g_App->activity->clazz);
        jmethodID method_id = env2->GetMethodID(native_activity_clazz, "updateTexImage", "()V");
        env2->CallVoidMethod(g_App->activity->clazz, method_id);
        uiManager.handler.updatePreview = false;
        //ASurfaceTexture_updateTexImage(camera.parameters->cameraPreviewID);
    }
    if(camera.parameters->resetResCamera){
        camera.parameters->resetResCamera = false;
        CameraNDKReInit();
    }
}

void shutdownUICamera()
{
    if (!g_Initialized)
        return;

    // Cleanup
    camera.CloseCamera();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::GetIO().Fonts->Locked = false;
    ImGui::GetIO().Fonts = nullptr;

    ImGui::DestroyContext();

    previewEgl->~EglPlate();
    delete previewEgl;
    ANativeWindow_release(g_App->window);
    LOGD("Shutdown UI and Camera");
    g_Initialized = false;
}

static void handleAppCmd(struct android_app* app, int32_t appCmd)
{
    LOGD("command %d",appCmd);
    switch (appCmd)
    {
    case APP_CMD_START:
        LOGD("APP_CMD_START");
        break;
    case APP_CMD_SAVE_STATE:
        LOGD("APP_CMD_SAVE_STATE");
        break;
    case APP_CMD_INIT_WINDOW:
        LOGD("APP_CMD_INIT_WINDOW");
            initUICamera(app);
        break;
    case APP_CMD_TERM_WINDOW:
        LOGD("APP_CMD_TERM_WINDOW");
            shutdownUICamera();
        break;
    case APP_CMD_GAINED_FOCUS:
        LOGD("GAIN FOCUS");
        break;
    case APP_CMD_LOST_FOCUS:
        LOGD("APP_CMD_LOST_FOCUS");
        break;
    case APP_CMD_RESUME:
        LOGD("APP_CMD_RESUME");
        //if(g_App != nullptr)
        //    initUICamera(app);
        break;
    default:
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
                    shutdownUICamera();

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
    /*JavaVM* java_vm = g_App->activity->vm;
    JNIEnv* java_env = NULL;

    jint jni_return = java_vm->GetEnv((void**)&java_env, JNI_VERSION_1_6);
    if (jni_return == JNI_ERR)
        return -1;

    jni_return = java_vm->AttachCurrentThread(&java_env, NULL);
    if (jni_return != JNI_OK)
        return -2;*/

    jclass native_activity_clazz = env2->GetObjectClass(g_App->activity->clazz);
    if (native_activity_clazz == NULL)
        return -3;

    jmethodID method_id = env2->GetMethodID(native_activity_clazz, "showSoftInput", "()V");
    if (method_id == NULL)
        return -4;

    env2->CallVoidMethod(g_App->activity->clazz, method_id);

    //jni_return = java_vm->DetachCurrentThread();
    //if (jni_return != JNI_OK)
    //    return -5;
    LOGD("ShowSoftKeyboardInput OK");
    return 0;
}

// Unfortunately, the native KeyEvent implementation has no getUnicodeChar() function.
// Therefore, we implement the processing of KeyEvents in MainActivity.kt and poll
// the resulting Unicode characters here via native buffer and send them to Dear ImGui.
static int PollUnicodeChars()
{
    ImGuiIO& io = ImGui::GetIO();
    if(unicodeBuffer[1] != 0){
        LOGD("PollUnicodeChars");
        for(int i =0; i<unicodeBuffer[0];i++){
            io.AddInputCharacter(unicodeBuffer[i+1]);
        }
        unicodeBuffer[0] = 0;
        unicodeBuffer[1] = 0;
    }
    return 0;}

// Helper to retrieve data placed into the assets/ directory (android/app/src/main/assets)
int GetAssetData(const char* filename, void** outData)
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