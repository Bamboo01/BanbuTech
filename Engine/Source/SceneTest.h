#include "Scene.h"
#include "TransformSystem.h"
#include "CameraSystem.h"
#include "RenderSystem.h"

#pragma once
class SceneTest : public Scene
{
public:
	virtual void Init();
	virtual void EarlyUpdate(double dt);
	virtual void Update(double dt);
	virtual void LateUpdate(double dt);

	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

	virtual void Exit();
	virtual Scene* Clone() { return new SceneTest(*this); }

	/*Systems of the scene*/
	std::shared_ptr<TransformSystem> transformsystem;
	std::shared_ptr<CameraSystem> camerasystem;
	std::shared_ptr<RenderSystem> rendersystem;

};

