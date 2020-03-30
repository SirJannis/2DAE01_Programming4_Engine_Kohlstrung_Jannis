#include "MiniginPCH.h"
#include "TransformComponent.h"
MyEngine::TransformComponent::TransformComponent(Vector2 pos)
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

const Vector2& MyEngine::TransformComponent::GetPosition() const
{
	return m_Position;
}

void MyEngine::TransformComponent::SetPosition(const float x, const float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

