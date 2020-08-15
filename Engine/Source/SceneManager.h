#include "Scene.h"


#pragma once

enum SCENE_TYPE
{
	SCENE_TEST,
	SCENE_BASIC,
	SCENE_SHADOW,
	TOTAL_SCENES
};

class SceneManager
{
private:
	SceneManager();
	static SceneManager* instance;
	bool swap;

public:
	Scene* sceneList[TOTAL_SCENES];
	Scene** scene;
	SCENE_TYPE currentScene;
	
	void Init(Scene** s);
	void ChangeScene(SCENE_TYPE scenetype);
	void Update(float dt);
	static SceneManager* getInstance();

	~SceneManager();
};