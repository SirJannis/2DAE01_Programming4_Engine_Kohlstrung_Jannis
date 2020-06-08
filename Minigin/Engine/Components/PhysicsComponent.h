#pragma once
#include "../Components/BaseComponent.h"

class b2Body;
namespace MyEngine
{
	enum class PhysicsType
	{
		Static,
		Kinematic,
		Dynamic
	};

	class PhysicsComponent final : public BaseComponent
	{
	public:
		PhysicsComponent(const PhysicsType physicsType, const float posX = 0.f, const float posY =0.f, const float angle=0.f, const float halfWidth = .5f, const float halfHeight = .5f, const float density = 1.f, const float friction = .3f, const float restitution = .7f, unsigned short categoryBits = 0x0001, unsigned short maskBits = 0x0000);
		void FixedUpdate(const float fixedDeltaTime) override;
		void Update(const float deltaTime) override;
		void Render() const override;

		const bool IsTrigger() { return m_IsTrigger; }
		void SetIsTrigger(bool value);


		bool IsOverlapping(const PhysicsComponent* other) const;
	private:
		friend class TransformComponent;
		b2Body* m_pBody;
		bool m_IsTrigger;
		unsigned short m_OldMaskBits;
	};
}

