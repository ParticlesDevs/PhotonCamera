cmake_minimum_required(VERSION 3.6)

project(NPhotonCamera)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(READ ${CMAKE_CURRENT_SOURCE_DIR}/../../../version.properties ver)
string(REGEX MATCH "VERSION_BUILD=([0-9]*)" _ ${ver})
set(VERSION_BUILD ${CMAKE_MATCH_1})
string(REGEX MATCH "VERSION_NAME=([0-9,.]*)" _ ${ver})
set(VERSION_NAME ${CMAKE_MATCH_1})
message(NPhotonCamera-${VERSION_NAME}${VERSION_BUILD})

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_library(${CMAKE_PROJECT_NAME} SHARED
        ${SRC_DIR}/Util/EglPlate.cpp
        ${SRC_DIR}/Util/FileManager.cpp
        ${SRC_DIR}/Util/Widgets.cpp
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/CameraNDK.cpp
        ${SRC_DIR}/deps/imgui/imgui.cpp
        ${SRC_DIR}/deps/imgui/imgui_demo.cpp
        ${SRC_DIR}/deps/imgui/imgui_draw.cpp
        ${SRC_DIR}/deps/imgui/imgui_tables.cpp
        ${SRC_DIR}/deps/imgui/imgui_widgets.cpp
        ${SRC_DIR}/impl/imgui_impl_android.cpp
        ${SRC_DIR}/impl/imgui_impl_opengl3_android.cpp
        ${SRC_DIR}/UI/Preview.cpp
        ${SRC_DIR}/UI/Settings.cpp
        ${SRC_DIR}/UI/UiManager.cpp
        ${SRC_DIR}/UI/Texture.cpp
        ${SRC_DIR}/UI/Gallery.cpp
        ${SRC_DIR}/UI/Demos.cpp
        ${SRC_DIR}/UI/image_loader.cpp
        ${SRC_DIR}/Processing/ProcessorQueue.cpp
        ${SRC_DIR}/Processing/Processor.cpp
        ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
        )

set(CMAKE_SHARED_LINKER_FLAGS
        "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate"
        )


add_subdirectory(${SRC_DIR}/deps/glm/ EXCLUDE_FROM_ALL)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${SRC_DIR}/deps/imgui
        ${SRC_DIR}/impl
        ${SRC_DIR}/inc
        ${SRC_DIR}/deps/tinydng
        ${SRC_DIR}
        ${ANDROID_NDK}/sources/android/native_app_glue
        )
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
        IMGUI_USER_CONFIG=<imguiConf.h>
        VERSION_BUILD="${VERSION_BUILD}"
        VERSION_NAME="${VERSION_NAME}"
        )
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
        IMGUI_IMPL_OPENGL_ES3
        )

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        android
        EGL
        GLESv3
        camera2ndk
        mediandk
        log
        PRIVATE glm
        )
add_compile_definitions(ENABLE_DEMO_WINDOWS #comment this define to disable demo windows
        )