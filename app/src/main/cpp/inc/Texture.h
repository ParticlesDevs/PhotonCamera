//
// Created by eszdman on 29.10.2022.
//

#ifndef PHOTONCAMERA_TEXTURE_H
#define PHOTONCAMERA_TEXTURE_H
#include <gl.h>
#include <imgui.h>
namespace UiTexture {

    enum UITexType {
        DEFAULT = 0,
        OES = 1
    };
    struct UiTexture {
        UITexType type;
        GLuint ID;
    };
    struct types{
        UITexType texTypes[256];
    };
    void Image(GLuint user_texture_id,UITexType texType, const ImVec2& size,
               const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1),
               const ImVec4& tint_col = ImVec4(1, 1, 1, 1), const ImVec4& border_col = ImVec4(0, 0, 0, 0));
}

#endif //PHOTONCAMERA_TEXTURE_H
