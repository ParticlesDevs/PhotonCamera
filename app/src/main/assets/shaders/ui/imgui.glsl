#extension GL_OES_EGL_image_external_essl3 : require
precision mediump float;
uniform int texType;
uniform sampler2D Texture;
uniform samplerExternalOES OESTexture;
in vec2 Frag_UV;
in vec4 Frag_Color;
layout (location = 0) out vec4 Out_Color;
void main()
{
    vec4 col;
    if(texType == 0){
        col = texture(Texture, Frag_UV.st);
    } else {
        col = texture(OESTexture, vec2(Frag_UV.t,1.0-Frag_UV.s));
    }
    Out_Color = Frag_Color * col;
}