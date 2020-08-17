#include "Mesh.h"
#include "MeshBuilder.h"
#include <assert.h>

#pragma once

enum GEO_TYPE
{
	GEO_AXES,
	GEO_CUBE,
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

