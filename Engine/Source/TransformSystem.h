#include "System.h"
#include "Transform.h"
#include "Coordinator.h"

extern Coordinator coordinator;

#pragma once
class TransformSystem  : public System
{
public:
	virtual void Setup();
	virtual void Update(float dt);
};

