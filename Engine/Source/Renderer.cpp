#include "Renderer.h"
#include <assert.h>
#include "Application.h"
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

void Renderer::addMaterial(Material* mat, Shader* shader)
{
	assert(mat != nullptr, "ERROR: TRYING TO REGISTER A NULLPTR AS A MATERIAL!");

	materialManager.push_back(mat);

	if (shader != nullptr)
	{
		shaderManager.push_back(shader);
		shader->InitShader();
	}

	MaterialtoShader.insert({ mat, shader });
}

void Renderer::assignMaterialtoMesh(Mesh* mesh, Material* material)
{
	assert(mesh != nullptr, "ERROR: TRYING TO ASSIGN A MATERIAL TO A NULLPTR!");

	MeshtoMaterial[mesh] = material;
}

void Renderer::Init()
{
	addMaterial(new Material, new Shader("Shader///basic.vs", "Shader//basic.fs"));
	meshManager = new MeshManager;
	defaultMaterial = materialManager[0];
	defaultShader = shaderManager[0];

	for (auto mesh : meshManager->meshList)
	{
		MeshtoMaterial.insert({ mesh, nullptr });
	}

	lightingManager.InitLights(shaderManager);

	/*Initialise all your shaders here*/

	/*Add your materials*/

	/*Assign your material their shaders here*/

	/*Assign your meshes their materials here*/

	/*Assignment of uniform blocks*/
	for (auto shader : shaderManager)
	{
		unsigned uniformblockMatrice = glGetUniformBlockIndex(*shader, "MatricesBlock");
		glUniformBlockBinding(*shader, uniformblockMatrice, 0);
		std::cout << glGetError() << std::endl;
	}

	glGenBuffers(1, &MatriceUBO);
	std::cout << glGetError() << std::endl;
	glBindBuffer(GL_UNIFORM_BUFFER, MatriceUBO);
	std::cout << glGetError() << std::endl;
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	std::cout << glGetError() << std::endl;
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, MatriceUBO, 0, 2 * sizeof(glm::mat4));
	std::cout << glGetError() << std::endl;
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	std::cout << glGetError() << std::endl;
}

/*
layout (std140) uniform Matrices
{
	mat4 projection;
	mat4 view;
};
*/

void Renderer::Update(float dt)
{
	for (auto mesh : meshManager->meshList)
	{
		//Clears all dynamic transform matrices
		mesh->DynamicTransformMatrices.clear();
		mesh->DynamicTransformMatrices.shrink_to_fit();
	}
	meshManager->Update(dt);
}

void Renderer::Render(Camera camera)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_BUFFER);

	glBindBuffer(GL_UNIFORM_BUFFER, MatriceUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(camera.ProjectionMatrix));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(camera.ViewMatrix));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	lightingManager.BufferLights();

	for (auto mesh : meshManager->meshList)
	{
		Shader* shader;
		Material* material;

		material = MeshtoMaterial[mesh];
		if (material == nullptr)
		{
			material = defaultMaterial;
			shader = defaultShader;
		}
		else
		{
			shader = MaterialtoShader[material];
			if (shader == nullptr)
			{
				shader = defaultShader;
			}
		}
		glUseProgram(*shader);
		shader->UpdateShader(*material);
		mesh->Render();
	}
}
