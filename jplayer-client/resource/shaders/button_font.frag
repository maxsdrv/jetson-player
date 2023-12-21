#version 440

layout(location=0) in vec2 qt_TexCoord0;
layout(location=0) out vec4 fragColor;

layout(std140, binding=0) uniform buf {
    mat4 qt_Matrix;
    float qt_Opacity;
    vec4 customColor;
    float rotation; // image rotation
    float customWidth; // image width
    float customHeight; // image height
} ubuf;


layout(binding=1) uniform sampler2D source;

void main()
{
    vec4 src = texture(source, qt_TexCoord0);
    vec4 newColor = vec4(ubuf.customColor.rgb, src.a); 
    fragColor = src * newColor * ubuf.qt_Opacity; // change only background
}
