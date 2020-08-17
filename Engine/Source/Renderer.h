#include "MeshManager.h"
#include "Shader.h"
#include "Material.h"
#include <map>
#include "Camera.h"
#include "Light.h"
#include <glm.hpp>
#include "LightingManager.h"
#include "ScreenQuad.h"

#pragma once

class Renderer
{
private:
	//Mesh, material, shaders
	std::map<Material*, Shader*> MaterialtoShader;
	std::map<Mesh*, Material*> MeshtoMaterial;
	MeshManager* meshManager;
	std::vector<Shader*> shaderManager;
	std::vector<Material*> materialManager;

	//Matrice UBO
	unsigned MatriceUBO;

	//Default Stuff
	Material* defaultMaterial;
	Shader* defaultShader;
	Shader* postProcessingShader;
	ScreenQuad* screenQuad;
	
	//Add-ons to the rendering pipeline
	LightingManager lightingManager;

	void addMaterial(Material* mat, Shader* shader = nullptr);
	void assignMaterialtoMesh(Mesh* mesh, Material* material);

public:
	Mesh* getMesh(GEO_TYPE type);

	void Init();
	void Update(float dt);
	void Render(Camera& camera, bool useCameraShader);
	void RenderScreenQuad();
	void BufferStaticModels();
};

