#include "TransformSystem.h"

void TransformSystem::Setup()
{
	Signature signature;
	signature.set(coordinator.GetComponentType<Transform>());
	coordinator.SetSystemSignature<TransformSystem>(signature);
}

void TransformSystem::Update(float dt)
{
    for (auto const& entity : m_Entities)
    {
        auto& transform = coordinator.GetComponent<Transform>(entity);
        glm::mat4 mrot(1.f);

        glm::vec3 rotation = glm::radians(transform.rotation);

        mrot = glm::mat4(1.f);
        mrot = glm::rotate(mrot, rotation.x, glm::vec3(1, 0, 0));
        mrot = glm::rotate(mrot, rotation.y, glm::vec3(0, 1, 0));
        mrot = glm::rotate(mrot, rotation.z, glm::vec3(0, 0, 1));

        transform.AxisX = glm::vec3(mrot * glm::vec4(1, 0, 0, 0.f));
        transform.AxisY = glm::vec3(mrot * glm::vec4(0, 1, 0, 0.f));
        transform.AxisZ = glm::vec3(mrot * glm::vec4(0, 0, 1, 0.f));
    }
}
