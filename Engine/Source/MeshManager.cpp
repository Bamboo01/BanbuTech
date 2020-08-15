#include "MeshManager.h"
#include "LoadTexture.h"
#include "LoadTGA.h"
#include "LoadHmap.h"
#include "Vertex.h"

MeshManager::MeshManager()
{
	bool isfilled = true;

	for (int i = 0; i < NUM_MESH; i++)
	{
		meshList[i] = NULL;
	}

	//Initialise your meshes here
	meshList[MESH_AXES] = meshList[MESH_AXES] = MeshBuilder::GenerateAxes("reference");

	for (int i = 0; i < NUM_MESH; i++)
	{
		if (meshList[i] == NULL)
		{
			std::cout << "Mesh ID: " << i << " not initialised!" << std::endl;
			isfilled = false;
		}
	}

	assert(isfilled == true && "Some meshes have not been initialised! Review the command window for more information.");

	for (int i = 0; i < NUM_MESH; i++)
	{
		meshList[i]->Init();
	}
}

void MeshManager::Update(float dt)
{
	for (auto anim : animList)
	{
		anim.second.Update(dt);
	}
}

MeshManager::~MeshManager()
{
	for (int i = 0; i < NUM_MESH; ++i)
	{
		if (meshList[i])
			delete meshList[i];
	}
}