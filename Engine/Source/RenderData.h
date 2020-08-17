#include "Mesh.h"
#pragma once

struct RenderData
{
	Mesh* mesh = nullptr;
	bool enableLight;

	RenderData()
	{
		this->mesh = nullptr;
		enableLight = false;
	}

	RenderData(Mesh* mesh, bool light)
	{
		this->mesh = mesh;
		enableLight = light;
	}
};