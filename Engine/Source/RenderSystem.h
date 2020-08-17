#include "System.h"
#include "Coordinator.h"
#include "Renderer.h"
#include "RenderData.h"
#include "Transform.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

extern Coordinator coordinator;
extern Renderer renderer;

#pragma once
class RenderSystem : public System
{
private:
	std::vector<Entity> DynamicEntities;

public:
	virtual void Setup();
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render();
};

