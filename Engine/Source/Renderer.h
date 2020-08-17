#include "MeshManager.h"
#include "Shader.h"
#include "Material.h"
#include <map>
#include "Camera.h"
#include "Light.h"
#include <glm.hpp>
#include "LightingManager.h"
#include "ScreenQuad.h"

#define MAX_LIGHTS 64

#pragma once

class Renderer
{
private:
	std::map<Material*, Shader*> MaterialtoShader;
	std::map<Mesh*, Material*> MeshtoMaterial;
	MeshManager* meshManager;
	std::vector<Shader*> shaderManager;
	std::vector<Material*> materialManager;
	Material* defaultMaterial;
	Shader* defaultShader;
	unsigned MatriceUBO;
	LightingManager lightingManager;

	Shader* postProcessingShader;
	ScreenQuad* screenQuad;
	
	

	void addMaterial(Material* mat, Shader* shader = nullptr);
	void assignMaterialtoMesh(Mesh* mesh, Material* material);

public:
	Mesh* getMesh(GEO_TYPE type);

	void Init();
	void Update(float dt);
	void Render(Camera& camera, bool useCameraShader);
	void RenderScreenQuad();
};

