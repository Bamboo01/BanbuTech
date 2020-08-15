#pragma once

#include "ComponentManager.h"
#include "SystemManager.h"
#include "EntityManager.h"

class Coordinator
{
private:

	ComponentManager* m_ComponentManager;
	SystemManager* m_SystemManager;
	EntityManager* m_EntityManager;

public:

	void Init()
	{
		m_ComponentManager = new ComponentManager;
		m_SystemManager = new SystemManager;
		m_EntityManager = new EntityManager;
	}

	void Exit()
	{
		if (m_ComponentManager)
		{
			delete m_ComponentManager;
			m_ComponentManager = nullptr;
		}
		if (m_SystemManager)
		{
			delete m_SystemManager;
			m_SystemManager = nullptr;
		}
		if (m_EntityManager)
		{
			delete m_EntityManager;
			m_EntityManager = nullptr;
		}
	}

	Entity CreateEntity()
	{
		return m_EntityManager->createEntity();
	}

	void DestroyEntity(Entity entity)
	{
		m_EntityManager->destroyEntity(entity);
		m_SystemManager->EntityDestroyed(entity);
		m_ComponentManager->DestroyEntity(entity);
	}

	Entity CloneEntity(Entity original)
	{
		Entity clone = m_EntityManager->createEntity();
		m_ComponentManager->CloneEntity(original, clone);
		Signature signature = m_EntityManager->getSignature(original);
		m_EntityManager->setSignature(clone, signature);
		m_SystemManager->EntitySignatureChanged(clone, signature);
		return clone;
	}

	template<typename T>
	void RegisterComponent()
	{
		m_ComponentManager->RegisterComponent<T>();
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		m_ComponentManager->AddComponent<T>(entity, component);
		Signature signature = m_EntityManager->getSignature(entity);
		signature.set(m_ComponentManager->GetComponentType<T>(), true);
		m_EntityManager->setSignature(entity, signature);
		m_SystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		m_ComponentManager->RemoveComponent<T>(entity);
		Signature signature;
		signature.set(m_ComponentManager->GetComponentType<T>(), false);
		m_EntityManager->setSignature(entity, signature);
		m_SystemManager->EntitySignatureChanged(entity, signature);
	}

	Signature GetEntitySignature(Entity entity)
	{
		return m_EntityManager->getSignature(entity);
	}

	void SetEntitySignature(Entity entity, Signature signature)
	{
		m_EntityManager->setSignature(entity, signature);
		m_SystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		return m_ComponentManager->GetComponent<T>(entity);
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		return m_ComponentManager->GetComponentType<T>();
	}

	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		return m_SystemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature signature)
	{
		m_SystemManager->setSignature<T>(signature);
	}
};