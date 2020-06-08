#include "MiniginPCH.h"
#include "PhysicsComponent.h"
#include "../Managers/PhysicsManager.h"
#include "../Scene/GameObject.h"
#include "TransformComponent.h"
#include "../Graphics/Renderer.h"
#include "SDL_rect.h"

//Don't forget to update this with Rotation / angle when you have it
MyEngine::PhysicsComponent::PhysicsComponent(const PhysicsType physicsType, const float posX, const float posY, const float angle, const float halfWidth, const float halfHeight, const float density, const float friction, const float restitution, unsigned short categoryBits, unsigned short maskBits)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2BodyType(physicsType);
	bodyDef.position.Set(posX / PhysicsManager::GetInstance()->GetPPM(), posY / PhysicsManager::GetInstance()->GetPPM());
	bodyDef.angle = angle * float(M_PI) / 180.f;
	m_pBody = PhysicsManager::GetInstance()->CreateBody(bodyDef);

	b2PolygonShape polyShape;
	b2FixtureDef fixtureDef;
	polyShape.SetAsBox(halfWidth / PhysicsManager::GetInstance()->GetPPM(), halfHeight / PhysicsManager::GetInstance()->GetPPM());
	fixtureDef.shape = &polyShape;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = restitution;
	fixtureDef.filter.categoryBits = categoryBits;
	fixtureDef.filter.maskBits = unsigned short(~maskBits);

	m_pBody->CreateFixture(&fixtureDef);
	m_IsTrigger = false;
}

void MyEngine::PhysicsComponent::FixedUpdate(const float fixedDeltaTime)
{
	UNREFERENCED_PARAMETER(fixedDeltaTime);
	TransformComponent* pTransform = m_pGameObject->GetComponent<TransformComponent>();
	pTransform->m_Position = { m_pBody->GetPosition().x * PhysicsManager::GetInstance()->GetPPM(),  m_pBody->GetPosition().y * PhysicsManager::GetInstance()->GetPPM() };
	pTransform->m_Angle = m_pBody->GetAngle() * 180.f / float(M_PI);
}

void MyEngine::PhysicsComponent::Update(const float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void MyEngine::PhysicsComponent::Render() const
{
	if (!PhysicsManager::GetInstance()->ShouldDebugDraw())
		return;
	b2PolygonShape* shape = dynamic_cast<b2PolygonShape*>(m_pBody->GetFixtureList()[0].GetShape());
	if (shape == nullptr)
		return;
	for (int32 i{}; i < shape->m_count - 1; i++)
	{
		Renderer::GetInstance()->RenderLine({ int(m_pBody->GetWorldPoint(shape->m_vertices[i]).x * PhysicsManager::GetInstance()->GetPPM()), int(m_pBody->GetWorldPoint(shape->m_vertices[i]).y * PhysicsManager::GetInstance()->GetPPM()) }, { int(m_pBody->GetWorldPoint(shape->m_vertices[i + 1]).x * PhysicsManager::GetInstance()->GetPPM()),int(m_pBody->GetWorldPoint(shape->m_vertices[i + 1]).y * PhysicsManager::GetInstance()->GetPPM()) }, { int(m_pBody->GetPosition().x * PhysicsManager::GetInstance()->GetPPM()), int(m_pBody->GetPosition().y * PhysicsManager::GetInstance()->GetPPM()) }, PhysicsManager::GetInstance()->GetDebugColor());
	}

	Renderer::GetInstance()->RenderLine({ int(m_pBody->GetWorldPoint(shape->m_vertices[0]).x * PhysicsManager::GetInstance()->GetPPM()), int(m_pBody->GetWorldPoint(shape->m_vertices[0]).y * PhysicsManager::GetInstance()->GetPPM()) }, { int(m_pBody->GetWorldPoint(shape->m_vertices[shape->m_count - 1]).x * PhysicsManager::GetInstance()->GetPPM()),int(m_pBody->GetWorldPoint(shape->m_vertices[shape->m_count - 1]).y * PhysicsManager::GetInstance()->GetPPM()) }, { int(m_pBody->GetPosition().x * PhysicsManager::GetInstance()->GetPPM()), int(m_pBody->GetPosition().y * PhysicsManager::GetInstance()->GetPPM()) }, PhysicsManager::GetInstance()->GetDebugColor());
}

void MyEngine::PhysicsComponent::SetIsTrigger(bool value)
{
	if (m_IsTrigger == value)
		return;
	m_IsTrigger = value;
	if (m_IsTrigger)
	{
		m_OldMaskBits = m_pBody->GetFixtureList()[0].GetFilterData().maskBits;
		b2Filter filter;
		filter.categoryBits = m_pBody->GetFixtureList()[0].GetFilterData().categoryBits;
		filter.maskBits = 0x0000;
		filter.groupIndex = m_pBody->GetFixtureList()[0].GetFilterData().groupIndex;
		m_pBody->GetFixtureList()[0].SetFilterData(filter);
		return;
	}
	b2Filter filter;
	filter.categoryBits = m_pBody->GetFixtureList()[0].GetFilterData().categoryBits;
	filter.maskBits = m_OldMaskBits;
	filter.groupIndex = m_pBody->GetFixtureList()[0].GetFilterData().groupIndex;
	m_pBody->GetFixtureList()[0].SetFilterData(filter);
}

bool MyEngine::PhysicsComponent::IsOverlapping(const PhysicsComponent* other) const
{
	if (m_IsTrigger || other->m_IsTrigger)
		return b2TestOverlap(m_pBody->GetFixtureList()[0].GetShape(), 0, other->m_pBody->GetFixtureList()[0].GetShape(), 0, m_pBody->GetTransform(), other->m_pBody->GetTransform());
	return false;
}
