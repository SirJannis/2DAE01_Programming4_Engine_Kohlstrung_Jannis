#pragma once
#include "../Helpers/Singleton.h"
#include "Box2D.h"
#include "SDL_pixels.h"
namespace MyEngine
{
	class PhysicsManager final : public Singleton<PhysicsManager>
	{
	public:
		PhysicsManager() = default;
		~PhysicsManager();
		void Init(const b2Vec2& gravity, const int32 velocityIter, const int32 positionIter, const float ppm);

		b2Body* CreateBody(const b2BodyDef& bodyDef);

		void FixedUpdate(const float fixedDeltaTime);

		void SetPPM(const float ppm) { m_PixelsPerMeter = ppm; }
		const float GetPPM()const { return m_PixelsPerMeter; }

		const bool ShouldDebugDraw() { return m_ShouldDebugDraw; }
		void SetShouldDebugDraw(bool value) { m_ShouldDebugDraw = value; }

		const SDL_Color GetDebugColor() { return m_DebugDrawColor; }
		void SetDebugDrawColor(SDL_Color value) { m_DebugDrawColor = value; }


	private:

		bool m_ShouldDebugDraw;
		SDL_Color m_DebugDrawColor;

		float m_PixelsPerMeter;
		b2World* m_pWorld;
		int32 m_VelocityIterations;
		int32 m_PositionIterations;
	};
}
