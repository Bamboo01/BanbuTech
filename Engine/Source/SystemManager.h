#include "EntityManager.h"
#include "System.h"
#include <unordered_map>


#pragma once

class SystemManager
{
private:
	std::unordered_map<const char*, Signature> m_Signatures{};
	std::unordered_map<const char*, std::shared_ptr<System>> m_Systems{};

public:
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		const char* typeName = typeid(T).name();

		//Error check if the system type has already been added or something non-system has been registered

		auto system = std::make_shared<T>();
		m_Systems.insert({ typeName, system });
		return system;
	}

	template<typename T>
	std::shared_ptr<T> GetSystem()
	{

	}

	template<typename T>
	void setSignature(Signature signature)
	{
		const char* typeName = typeid(T).name();
		//Error check if the system has NOT been registered
		//m_Systems.find(typeName);
		m_Signatures.insert({ typeName, signature });
	}

	void EntityDestroyed(Entity entity)
	{
		for (auto const& pair : m_Systems)
		{
			auto const& system = pair.second;
			system->m_Entities.erase(entity);
		}
	}

	void EntitySignatureChanged(Entity entity, Signature entitySignature)
	{
		for (auto const& pair : m_Systems)
		{
			auto const& typeName = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = m_Signatures[typeName];

			if ((entitySignature & systemSignature) == systemSignature)
			{
				system->m_Entities.insert(entity);
			}
			else
			{
				system->m_Entities.erase(entity);
			}
		}
	}
};

