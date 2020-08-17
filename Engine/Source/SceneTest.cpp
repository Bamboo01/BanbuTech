#include "SceneTest.h"


void SceneTest::Init()
{
	coordinator.Init();
	coordinator.RegisterComponent<Camera>();
	coordinator.RegisterComponent<Transform>();
	coordinator.RegisterComponent<RenderData>();
	
	transformsystem = coordinator.RegisterSystem<TransformSystem>();
	camerasystem = coordinator.RegisterSystem<CameraSystem>();
	rendersystem = coordinator.RegisterSystem<RenderSystem>();

	transformsystem->Setup();
	camerasystem->Setup();
	rendersystem->Setup();

	Entity maincamera = coordinator.CreateEntity();
	coordinator.AddComponent<Camera>(maincamera, Camera(
		glm::vec3(0, 0, -3.f),
		glm::vec3(0, 0, 0),
		800, 600,
		45.f, 
		CAMERA_TYPE::CAMERA_MAIN,
		CAMERA_MODE::MODE_PERSPECTIVE
	));

	Entity axes = coordinator.CreateEntity();
	coordinator.AddComponent<RenderData>(axes, RenderData(renderer.getMesh(GEO_AXES), false, MESH_TYPE::STATIC_MESH));
	coordinator.AddComponent<Transform>(axes, Transform());

	Entity cube = coordinator.CreateEntity();
	coordinator.AddComponent<RenderData>(cube, RenderData(renderer.getMesh(GEO_CUBE), false, MESH_TYPE::DYNAMIC_MESH));
	coordinator.AddComponent<Transform>(cube, Transform());
	coordinator.GetComponent<Transform>(cube).rotation = glm::vec3(30.f, 60.f, 0.f);

	/*Init all systes*/
	camerasystem->Init();
	rendersystem->Init();
}

void SceneTest::EarlyUpdate(double dt)
{

}

void SceneTest::Update(double dt)
{
	transformsystem->Update(dt);
	camerasystem->Update(dt);
	rendersystem->Update(dt);
}

void SceneTest::LateUpdate(double dt)
{
}

void SceneTest::PreRender()
{
}

void SceneTest::Render()
{
	rendersystem->Render();
	camerasystem->Render();
}

void SceneTest::PostRender()
{
}

void SceneTest::Exit()
{
	coordinator.Exit();
}
