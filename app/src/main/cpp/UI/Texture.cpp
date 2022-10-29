//
// Created by eszdman on 29.10.2022.
//
#include <Texture.h>
void UiTexture::Image(GLuint user_texture_id,UITexType texType, const ImVec2& size,
           const ImVec2& uv0, const ImVec2& uv1,
           const ImVec4& tint_col, const ImVec4& border_col){
    ImGui::Image(reinterpret_cast<ImTextureID>(user_texture_id), size, uv0, uv1, tint_col, border_col);
    types* type = (types*)ImGui::GetIO().BackendRendererUserData;
    type->texTypes[(int)(uintptr_t)user_texture_id] = texType;
}