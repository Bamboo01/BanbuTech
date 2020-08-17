#include "System.h"
#include "Transform.h"
#include "Coordinator.h"

extern Coordinator coordinator;

#pragma once
class TransformSystem  : public System
{
private:
	std::vector<Entity> DynamicEntities;

public:
	virtual void Setup();
	virtual void Init();
	virtual void Update(float dt);
};

