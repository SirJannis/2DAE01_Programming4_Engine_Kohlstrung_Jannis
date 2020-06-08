#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "../Scene/GameObject.h"
#include "PhysicsComponent.h"
#include "../Managers/PhysicsManager.h"
MyEngine::TransformComponent::TransformComponent(glm::fvec2 pos)
	:m_Position{ pos }
{
}
void MyEngine::TransformComponent::FixedUpdate(const float fixedDeltaTime)
{
	UNREFERENCED_PARAMETER(fixedDeltaTime);
}
void MyEngine::TransformComponent::Update(const float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void MyEngine::TransformComponent::Render() const
{
}

const glm::fvec2& MyEngine::TransformComponent::GetPosition() const
{
	return m_Position;
}

void MyEngine::TransformComponent::SetPosition(const float x, const float y)
{
	PhysicsComponent* pPhysComp = m_pGameObject->GetComponent<PhysicsComponent>();
	if (pPhysComp != nullptr)
	{
		pPhysComp->m_pBody->SetTransform(b2Vec2(x / PhysicsManager::GetInstance()->GetPPM(), y / PhysicsManager::GetInstance()->GetPPM()), pPhysComp->m_pBody->GetAngle());
	}
	else
	{
		m_Position.x = x;
		m_Position.y = y;
	}
}

void MyEngine::TransformComponent::SetAngle(float angle)
{
	PhysicsComponent* pPhysComp = m_pGameObject->GetComponent<PhysicsComponent>();
	if (pPhysComp != nullptr)
	{
		pPhysComp->m_pBody->SetTransform(pPhysComp->m_pBody->GetPosition(), angle);
	}
	else
	{
		m_Angle = angle;
	}
}

