#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
    //TexCoord = aPos.xy * 0.5f + 0.5f;
    TexCoord = aTexCoord;
    gl_Position = vec4(aPos, 1.0);
}