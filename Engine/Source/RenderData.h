#include "Mesh.h"
#pragma once

enum MESH_TYPE
{
	STATIC_MESH,
	DYNAMIC_MESH
};


struct RenderData
{
	Mesh* mesh = nullptr;
	bool enableLight;
	MESH_TYPE type;

	RenderData()
	{
		this->mesh = nullptr;
		enableLight = false;
		this->type = MESH_TYPE::DYNAMIC_MESH;
	}

	RenderData(Mesh* mesh, bool light, MESH_TYPE type)
	{
		this->mesh = mesh;
		enableLight = light;
		this->type = type;
	}
};