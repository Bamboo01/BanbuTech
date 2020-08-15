#include "Mesh.h"
#include "MeshBuilder.h"
#include <assert.h>

#pragma once

enum MESH_TYPE
{
	MESH_AXES,
	NUM_MESH
};

class MeshManager
{
public:

	MeshManager();
	~MeshManager();
	Mesh* meshList[NUM_MESH];
	
	std::unordered_map<Mesh*, SpriteAnimation> animList;
	std::unordered_map <Mesh*, std::vector<unsigned char>> m_terrainList;

	void Update(float dt);
};

