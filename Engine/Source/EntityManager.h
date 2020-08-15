#pragma once
#include <queue>
#include <list>
#include <array>
#include <cassert>
#include "Signature.h"
#include "Entity.h"

class EntityManager
{
private:
	std::queue<Entity> m_AvailableEntities{};

	std::array<Signature, MAX_ENTITIES> m_Signatures{};

	uint32_t m_EntityCount{};

public:
	EntityManager()
	{
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			m_AvailableEntities.push(entity);
		}
	}

	Entity createEntity()
	{
		if (m_EntityCount > MAX_ENTITIES)
		{
			//Error check
		}
		Entity id = m_AvailableEntities.front();
		m_AvailableEntities.pop();
		m_EntityCount++;
		return id;
	}

	void destroyEntity(Entity entity)
	{
		m_Signatures[entity].reset();
		m_AvailableEntities.push(entity);
		m_EntityCount--;
	}

	void setSignature(Entity entity, Signature signature)
	{
		m_Signatures[entity] = signature;
	}

	Signature getSignature(Entity entity)
	{
		return m_Signatures[entity];
	}
};

