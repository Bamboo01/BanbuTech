#include "SceneManager.h"

SceneManager::SceneManager()
{
	sceneList[SCENE_TEST] = new SceneTest;
	scene = nullptr;
	swap = false;
}


void SceneManager::Init(Scene** s)
{
	scene = s;
}


void SceneManager::ChangeScene(SCENE_TYPE scenetype)
{
	swap = true;
	currentScene = scenetype;
}

void SceneManager::Update()
{
	if (swap == true)
	{
		if (*scene)
		{
			(*scene)->Exit();
			delete* scene;
			*scene = nullptr;
		}
		*scene = sceneList[currentScene]->Clone();
		(*scene)->Init();
		(*scene)->EarlyUpdate(0);
		(*scene)->Update(0);
		(*scene)->LateUpdate(0);
		swap = false;
	}
}

SceneManager* SceneManager::getInstance()
{
	if (!instance)
	{
		instance = new SceneManager;
	}
	return instance;
}

SceneManager::~SceneManager()
{
	for (auto s : sceneList)
	{
		delete s;
	}
}