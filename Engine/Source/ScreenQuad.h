#include "Mesh.h"
#include "MeshBuilder.h"
#include "Shader.h"
#pragma once
class ScreenQuad : public Mesh
{
public:
	Shader* defaultScreenShader;
	unsigned screenTexture;
	virtual void Init();
	virtual void Render();
	ScreenQuad();
	~ScreenQuad();
};

