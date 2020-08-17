#include "RenderSystem.h"

void RenderSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<RenderData>());
	signature.set(coordinator.GetComponentType<Transform>());
	coordinator.SetSystemSignature<RenderSystem>(signature);
}

void RenderSystem::Init()
{
	for (auto const& entity : m_Entities)
	{
		auto& transform = coordinator.GetComponent<Transform>(entity);
		auto& render = coordinator.GetComponent<RenderData>(entity);

		if (render.type == MESH_TYPE::STATIC_MESH)
		{
			glm::mat4 model(1.f);
			glm::vec3 rot = glm::radians(transform.rotation);
			model = glm::translate(model, transform.position);
			model = glm::rotate(model, rot.x, glm::vec3(1, 0, 0));
			model = glm::rotate(model, rot.y, glm::vec3(0, 1, 0));
			model = glm::rotate(model, rot.z, glm::vec3(0, 0, 1));
			model = glm::scale(model, transform.scale);

			render.mesh->StaticTransformMatrices.push_back(model);
		}
	}
}

void RenderSystem::Update(float dt)
{
	renderer.Update(dt);
}

void RenderSystem::Render()
{
	for (auto const& entity : m_Entities)
	{
		auto& transform = coordinator.GetComponent<Transform>(entity);
		auto& render = coordinator.GetComponent<RenderData>(entity);

		if (render.type == MESH_TYPE::DYNAMIC_MESH)
		{
			glm::mat4 model(1.f);
			glm::vec3 rot = glm::radians(transform.rotation);
			model = glm::translate(model, transform.position);
			model = glm::rotate(model, rot.x, glm::vec3(1, 0, 0));
			model = glm::rotate(model, rot.y, glm::vec3(0, 1, 0));
			model = glm::rotate(model, rot.z, glm::vec3(0, 0, 1));
			model = glm::scale(model, transform.scale);

			render.mesh->DynamicTransformMatrices.push_back(model);
		}
	}
	renderer.RenderScreenQuad();
}
