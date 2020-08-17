#include "System.h"
#include "Camera.h"
#include "Coordinator.h"
#include "Renderer.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

extern Coordinator coordinator;
extern Renderer renderer;

#pragma once
class CameraSystem : public System
{
public:
	virtual void Setup();
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render();
};

