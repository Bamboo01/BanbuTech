#pragma once
#include "Entity.h"
#include "Component.h"
#include "Signature.h"
#include <map>
#include <unordered_map>

class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void destroyEntity(Entity entity) = 0;
	virtual void cloneEntity(Entity original, Entity clone) = 0;
};


template<typename T>
class ComponentArray : public IComponentArray
{
private:
	//Total size of the component array
	size_t m_size{};

	//Array to store the components
	std::array<T, MAX_ENTITIES> m_ComponentArray;

	
	//Syntax for maps is KEY, VALUE
	//Map of Index to Entity
	std::unordered_map<size_t, Entity> m_IndexToEntity;

	//Map of Entity to Index
	std::unordered_map<Entity, size_t> m_EntityToIndex;


public:
	void insertEntity(Entity entity, T component)
	{
		size_t newIndex = m_size;
		m_EntityToIndex[entity] = m_size;
		m_IndexToEntity[m_size] = entity;
		m_ComponentArray[m_size] = component;
		m_size++;
	}

	void cloneEntity(Entity original, Entity clone) override
	{
		size_t cloneIndex = m_size;
		size_t originalIndex = m_EntityToIndex[original];

		m_EntityToIndex[clone] = cloneIndex;
		m_IndexToEntity[m_size] = clone;

		m_ComponentArray[m_size] = m_ComponentArray[originalIndex];

		m_size++;
	}

	void removeEntity(Entity entity)
	{
		size_t IndexOfRemovedEntity = m_EntityToIndex[entity];
		size_t IndexOfLastElement = m_size - 1;
		Entity EntityOfLastElement = m_EntityToIndex[IndexOfLastElement];

		m_ComponentArray[IndexOfRemovedEntity] = m_ComponentArray[IndexOfLastElement];
		m_EntityToIndex[EntityOfLastElement] = IndexOfRemovedEntity;
		m_IndexToEntity[IndexOfRemovedEntity] = EntityOfLastElement;

		m_EntityToIndex.erase(entity);
		m_IndexToEntity.erase(IndexOfLastElement);

		m_size--;
	}

	T& getComponentData(Entity entity)
	{
		return m_ComponentArray[m_EntityToIndex[entity]];
	}

	void destroyEntity(Entity entity) override
	{
		if (m_EntityToIndex.find(entity) != m_EntityToIndex.end())
		{
			removeEntity(entity);
		}
	}
};


