cmake_minimum_required(VERSION 3.6)

project(NPhotonCamera)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

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
        ${SRC_DIR}/Util/exiv_wrapper.cpp
        ${SRC_DIR}/Util/export_avif.cpp
        ${SRC_DIR}/Util/export_jxl.cpp
        ${SRC_DIR}/Util/import_avif.cpp
        ${SRC_DIR}/Util/import_jxl.cpp
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
        ${SRC_DIR}/Processing/Processor.cpp
        ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
        ${ANDROID_NDK}/sources/android/cpufeatures/cpu-features.c
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
        ${CMAKE_BINARY_DIR} # needed to find exv_conf.h
        )
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
        IMGUI_USER_CONFIG=<imguiConf.h>
        VERSION_BUILD="${VERSION_BUILD}"
        VERSION_NAME="${VERSION_NAME}"
        )
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
        IMGUI_IMPL_OPENGL_ES3
        )

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
        -Wno-deprecated-declarations #disable warnings from exiv2/exiv2.hpp
        -Wno-extra-semi
        )

set(CONFIG_PIC 1 CACHE INTERNAL "Build with PIC enabled." INTERNAL)
set(ENABLE_DOCS false CACHE INTERNAL "Enable documentation generation (doxygen required).")
set(ENABLE_EXAMPLES false CACHE INTERNAL "Enables build of example code.")
set(ENABLE_TOOLS false CACHE INTERNAL "Enable applications in tools sub directory.")
set(ENABLE_TESTS false CACHE INTERNAL "Enables unit tests.")
set(ENABLE_TESTDATA false CACHE INTERNAL "Enables unit test data download targets.")
add_subdirectory(deps/aom EXCLUDE_FROM_ALL)

set(AVIF_CODEC_AOM true CACHE INTERNAL "Use the AOM codec for encoding/decoding (see AVIF_CODEC_AOM_DECODE/AVIF_CODEC_AOM_ENCODE)")
set(AVIF_BUILD_TESTS false CACHE INTERNAL "Build avif tests.")
set(AVIF_ENABLE_GTEST false CACHE INTERNAL "Build avif C++ tests, which depend on GoogleTest. Requires GoogleTest. Has no effect unless AVIF_BUILD_TESTS is ON.")
set(AVIF_ENABLE_WERROR false CACHE INTERNAL "Treat all compiler warnings as errors")
add_subdirectory(deps/libavif EXCLUDE_FROM_ALL)
target_include_directories(avif PRIVATE ${SRC_DIR}/deps/aom/ )

set(JPEGXL_ENABLE_SKCMS true CACHE INTERNAL "Build with skcms instead of lcms2.")
set(JPEGXL_BUNDLE_SKCMS true CACHE INTERNAL "When building with skcms, bundle it into libjxl.a.")
set(JPEGXL_ENABLE_FUZZERS false CACHE INTERNAL "Build JPEGXL fuzzer targets.")
set(JPEGXL_ENABLE_TOOLS false CACHE INTERNAL "Build JPEGXL user tools: cjxl and djxl.")
set(JPEGXL_ENABLE_JPEGLI_LIBJPEG false CACHE INTERNAL "Build libjpeg.so shared library based on jpegli.")
set(JPEGXL_ENABLE_DOXYGEN false CACHE INTERNAL "Generate C API documentation using Doxygen.")
set(JPEGXL_ENABLE_MANPAGES false CACHE INTERNAL "Build and install man pages for the command-line tools.")
set(JPEGXL_ENABLE_BENCHMARK false CACHE INTERNAL "Build JPEGXL benchmark tools.")
set(JPEGXL_ENABLE_EXAMPLES false CACHE INTERNAL "Build JPEGXL library usage examples.")
set(JPEGXL_ENABLE_JNI false CACHE INTERNAL "Build JPEGXL JNI Java wrapper, if Java dependencies are installed.")
set(JPEGXL_ENABLE_SJPEG false CACHE INTERNAL "Build JPEGXL with support for encoding with sjpeg.")
set(JPEGXL_ENABLE_OPENEXR false CACHE INTERNAL "Build JPEGXL with support for OpenEXR if available.")
set(JPEGXL_ENABLE_TCMALLOC false CACHE INTERNAL "Build JPEGXL using gperftools (tcmalloc) allocator.")
set(JPEGXL_WARNINGS_AS_ERRORS false CACHE INTERNAL "Treat warnings as errors during compilation.")
set(HWY_FORCE_STATIC_LIBS true CACHE INTERNAL "Ignore BUILD_SHARED_LIBS")
set(HWY_ENABLE_EXAMPLES false CACHE INTERNAL "Build examples")
set(HWY_ENABLE_INSTALL false CACHE INTERNAL "Install library")
set(HWY_ENABLE_TESTS false CACHE INTERNAL "Enable HWY tests")
add_subdirectory(deps/libjxl EXCLUDE_FROM_ALL)
target_compile_options(jxl_dec-obj PRIVATE -Wno-shorten-64-to-32 -Wno-float-conversion -Wno-extra-semi-stmt)
target_compile_options(jxl_enc-obj PRIVATE -Wno-shorten-64-to-32 -Wno-float-conversion -Wno-extra-semi-stmt)
target_compile_options(jxl-static PRIVATE -Wno-shorten-64-to-32 -Wno-float-conversion -Wno-extra-semi-stmt)
target_compile_options(jxl_threads-static PRIVATE -Wno-shorten-64-to-32 -Wno-float-conversion -Wno-extra-semi-stmt)
target_compile_options(brotlicommon-static PRIVATE -Wno-extra-semi-stmt)
target_compile_options(brotlidec-static PRIVATE -Wno-extra-semi-stmt)
target_compile_options(brotlienc-static PRIVATE -Wno-extra-semi-stmt)

set(EXIV2_ENABLE_XMP false CACHE INTERNAL "Build with XMP metadata support")
set(EXIV2_ENABLE_PNG false CACHE INTERNAL "Build with png support (requires libz)")
set(EXIV2_ENABLE_BMFF true CACHE INTERNAL "Build with BMFF support")
set(EXIV2_BUILD_SAMPLES false CACHE INTERNAL "Build sample applications")
set(EXIV2_BUILD_EXIV2_COMMAND false CACHE INTERNAL "Build exiv2 command-line executable")
add_subdirectory(deps/exiv2 EXCLUDE_FROM_ALL)
target_compile_options(exiv2lib PRIVATE -Wno-deprecated-declarations -Wno-extra-semi -Wno-deprecated-copy)
target_compile_options(exiv2lib_int PRIVATE -Wno-deprecated-declarations -Wno-extra-semi -Wno-deprecated-copy)

add_subdirectory(deps/dng_writer EXCLUDE_FROM_ALL)
include_directories(deps/dng_writer/dngwriter)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        android
        EGL
        GLESv3
        camera2ndk
        mediandk
        log
        glm
        avif
        aom
        jxl-static
        jxl_threads-static
        exiv2lib
        dngwriter
        )
add_compile_definitions(ENABLE_DEMO_WINDOWS #comment this define to disable demo windows
        )
