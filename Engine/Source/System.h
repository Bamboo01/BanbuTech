#include <set>
#include "Entity.h"
#pragma once


class System
{
public:
	std::set<Entity> m_Entities;
	System() {}
	virtual ~System() {}
	virtual void Setup() {}
	virtual void Init() {}
	virtual void EarlyUpdate(float dt) {}
	virtual void Update(float dt) {}
	virtual void LateUpdate(float dt) {}
	virtual void Render() {}
	virtual void OnCollision() {}
};

