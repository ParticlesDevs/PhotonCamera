cmake_minimum_required(VERSION 3.6)

project(PhotonCamera)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_library(${CMAKE_PROJECT_NAME} SHARED
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/deps/imgui/imgui.cpp
        ${SRC_DIR}/deps/imgui/imgui_demo.cpp
        ${SRC_DIR}/deps/imgui/imgui_draw.cpp
        ${SRC_DIR}/deps/imgui/imgui_tables.cpp
        ${SRC_DIR}/deps/imgui/imgui_widgets.cpp
        ${SRC_DIR}/impl/imgui_impl_android.cpp
        ${SRC_DIR}/impl/imgui_impl_opengl3.cpp
        ${SRC_DIR}/UI/Preview.cpp
        ${SRC_DIR}/UI/Settings.cpp
        ${SRC_DIR}/UI/UiManager.cpp
        ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
        )

set(CMAKE_SHARED_LINKER_FLAGS
        "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate"
        )

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
        IMGUI_IMPL_OPENGL_ES3
        )

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${SRC_DIR}/deps/imgui
        ${SRC_DIR}/impl
        ${SRC_DIR}/inc
        ${SRC_DIR}
        ${ANDROID_NDK}/sources/android/native_app_glue
        )

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        android
        EGL
        GLESv3
        log
        )
