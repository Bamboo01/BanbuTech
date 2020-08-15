#pragma once
#include "ComponentArray.h"
#include <assert.h>
#include <memory>

class ComponentManager
{
private:
	std::unordered_map<const char*, ComponentType> m_ComponentTypes{};
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_ComponentArrays{};
	ComponentType m_NextComponentType{};

	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		const char* typeName = typeid(T).name();
		assert(m_ComponentTypes.find(typeName) != m_ComponentTypes.end() && "Component not registered before use!!!");

		return std::static_pointer_cast<ComponentArray<T>>(m_ComponentArrays[typeName]);
	}

public:

	template<typename T>
	void RegisterComponent()
	{
		const char* typeName = typeid(T).name();

		if (m_ComponentTypes.find(typeName) != m_ComponentTypes.end())
		{
			std::cout << "WARNING: Component already registered!" << std::endl;
			return;
		}

		// Add this component type to the component type map
		m_ComponentTypes.insert({ typeName, m_NextComponentType });

		// Create a ComponentArray pointer and add it to the component arrays map
		m_ComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

		// Increment the value so that the next component registered will be different
		++m_NextComponentType;
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		const char* typeName = typeid(T).name();
		return m_ComponentTypes[typeName];
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		GetComponentArray<T>()->insertEntity(entity, component);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		GetComponentArray<T>()->removeEntity(entity);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		return GetComponentArray<T>()->getComponentData(entity);
	}

	void DestroyEntity(Entity entity)
	{
		for (auto const& componentArray : m_ComponentArrays)
		{
			auto const& component = componentArray.second;
			component->destroyEntity(entity);
		}
	}

	void CloneEntity(Entity original, Entity clone)
	{
		for (auto const& componentArray : m_ComponentArrays)
		{
			auto const& component = componentArray.second;
			component->cloneEntity(original, clone);
		}
	}
};

