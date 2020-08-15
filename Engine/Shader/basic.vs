#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in mat4 aModel;

out vec2 TexCoord;

layout (std140) uniform MatriceBlock
{
	mat4 projection;
	mat4 view;
};

void main()
{
    TexCoord = aTexCoord;
    gl_Position = projection * view * aModel * vec4(aPos, 1.0f);
}
