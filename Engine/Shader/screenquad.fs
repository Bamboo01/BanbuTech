#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D screenTexture;

void main()
{
     FragColor = texture(screenTexture, TexCoord);
     FragColor = vec4(TexCoobrd, 0.f, 1.f);
}