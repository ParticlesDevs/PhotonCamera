cmake_minimum_required(VERSION 3.6)

project(PhotonCamera)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
add_executable(${CMAKE_PROJECT_NAME}
        ${SRC_DIR}/deps/imgui/imgui.cpp
        ${SRC_DIR}/deps/imgui/imgui_demo.cpp
        ${SRC_DIR}/deps/imgui/imgui_draw.cpp
        ${SRC_DIR}/deps/imgui/imgui_tables.cpp
        ${SRC_DIR}/deps/imgui/imgui_widgets.cpp
        #${SRC_DIR}/impl/imgui_impl_android.cpp
        ${SRC_DIR}/impl/imgui_impl_opengl3.cpp
        ${SRC_DIR}/UI/Preview.cpp
        ${SRC_DIR}/UI/Settings.cpp
        ${SRC_DIR}/UI/UiManager.cpp
        imgui_impl_glfw.cpp
        main.cpp main.h)

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
        ${ANDROID_NDK}/sources/android/native_app_glue
        )

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        ${OPENGL_LIBRARIES}
        GLEW::GLEW
        glfw
        )
