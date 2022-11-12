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
        vec2 px = vec2(1.0)/vec2(textureSize(OESTexture,0));
        vec2 xy = vec2(Frag_UV.t,1.0-Frag_UV.s);
        col = texture(OESTexture, xy);
        /*col -= texture(OESTexture, xy+px*vec2(2.0,0.0))/4.0;
        col -= texture(OESTexture, xy+px*vec2(0.0,2.0))/4.0;
        col -= texture(OESTexture, xy+px*vec2(-2.0,0.0))/4.0;
        col -= texture(OESTexture, xy+px*vec2(0.0,-2.0))/4.0;
        //col/=4;
        col*=10.0;
        col.a = 1.0;
        col*=vec4(1.0,0.0,0.0,0.0);
        col = abs(col);
        col+=texture(OESTexture, xy);*/
    }
    Out_Color = Frag_Color * col;
}