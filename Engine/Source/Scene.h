#include "shader.h"

#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
	Scene() { }
	virtual ~Scene() {}

	virtual void Init() 
	{
		//By right I should be initialising all core systems here, but I am kind of lazy right now
	}

	virtual void EarlyUpdate(double dt) {}
	virtual void Update(double dt) {}
	virtual void LateUpdate(double dt) {}

	virtual void PreRender() {}
	virtual void Render() {}
	virtual void PostRender() {}

	virtual void Exit() {}

	virtual Scene* Clone() = 0;
};

#endif