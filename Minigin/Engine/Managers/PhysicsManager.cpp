#include "MiniginPCH.h"
#include "PhysicsManager.h"

MyEngine::PhysicsManager::~PhysicsManager()
{
	SafeDelete(m_pWorld);
}

void MyEngine::PhysicsManager::Init(const b2Vec2& gravity, const int32 velocityIter, const int32 positionIter, const float ppm)
{
	m_pWorld = new b2World(gravity);
	m_VelocityIterations = velocityIter;
	m_PositionIterations = positionIter;
	m_PixelsPerMeter = ppm;
	m_ShouldDebugDraw = false;
}

b2Body* MyEngine::PhysicsManager::CreateBody(const b2BodyDef& bodyDef)
{
	return m_pWorld->CreateBody(&bodyDef);
}

void MyEngine::PhysicsManager::FixedUpdate(const float fixedDeltaTime)
{
	m_pWorld->Step(fixedDeltaTime, m_VelocityIterations, m_PositionIterations);
}
