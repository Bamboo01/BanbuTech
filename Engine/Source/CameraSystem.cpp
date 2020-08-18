#include "CameraSystem.h"

#include "Application.h"

void CameraSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<Camera>());
	coordinator.SetSystemSignature<CameraSystem>(signature);
}

void CameraSystem::Init()
{
	for (auto const& entity : m_Entities)
	{
		auto& camera = coordinator.GetComponent<Camera>(entity);
		camera.Init();
	}
}

void CameraSystem::Update(float dt)
{
	for (auto const& entity : m_Entities)
	{
		auto& camera = coordinator.GetComponent<Camera>(entity);

		if (Application::IsKeyPressed('A'))
		{
			camera.position.x -= dt * 50.f;
		}
		if (Application::IsKeyPressed('D'))
		{
			camera.position.x += dt * 50.f;
		}

		glm::mat4 rot(1.f);
		glm::vec3 rotation = glm::radians(camera.rotation);

		rot = glm::rotate(rot, rotation.x, glm::vec3(1, 0, 0));
		rot = glm::rotate(rot, rotation.y, glm::vec3(0, 1, 0));
		rot = glm::rotate(rot, rotation.z, glm::vec3(0, 0, 1));

		camera.target = camera.position + glm::vec3((rot * glm::vec4(0, 0, 1, 0)));
		camera.up = rot * glm::vec4(0, 1, 0, 0);
		camera.right = glm::cross((camera.target - camera.position), camera.up);
		camera.ViewMatrix = glm::lookAt(camera.position, camera.target, camera.up);

		if (camera.mode == CAMERA_MODE::MODE_ORTHOGRAPHIC)
		{
			camera.ProjectionMatrix = glm::ortho(0, camera.viewWidth, 0, camera.viewHeight);
		}
		else
		{
			camera.ProjectionMatrix = glm::perspective(camera.FOV, (float)(camera.viewWidth / camera.viewHeight), 0.1f, 1000.f);
		}
	}
}

void CameraSystem::Render()
{
	for (auto const& entity : m_Entities)
	{
		auto& camera = coordinator.GetComponent<Camera>(entity);
		bool useShader = camera.getPostProcessingShader();
		renderer.Render(camera, useShader);
	}
	renderer.RenderScreenQuad();
}
