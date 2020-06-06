#include "MiniginPCH.h"
#include "TransformComponent.h"
MyEngine::TransformComponent::TransformComponent(glm::fvec2 pos)
	:m_Position{pos}
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
	m_Position.x = x;
	m_Position.y = y;
}

