#version 440

layout(location=0) in vec4 qt_Vertex;
layout(location=1) in vec2 qt_MultiTexCoord0;

layout(location=0) out vec2 qt_TexCoord0;

layout(std140, binding=0) uniform buf {
    mat4 qt_Matrix;
    float qt_Opacity;
    vec4 customColor;
    float rotation; // image rotation
    float customWidth; // image width
    float customHeight; // image height
} ubuf;


out gl_PerVertex {
    vec4 gl_Position;
};

void main(void)
{
    qt_TexCoord0 = qt_MultiTexCoord0;

    vec4 pos = qt_Vertex;
    vec2 center = vec2(ubuf.customWidth * 0.5, ubuf.customHeight * 0.5);
    float angle = radians(ubuf.rotation);
    float s = sin(angle);
    float c = cos(angle);
    pos.x -= center.x;
    pos.y -= center.y;
    float rotatedX = pos.x * c - pos.y * s;
    float rotatedY = pos.x * s + pos.y * c;
    pos.x = rotatedX + center.x;
    pos.y = rotatedY + center.y;

    gl_Position = ubuf.qt_Matrix * pos;
}
