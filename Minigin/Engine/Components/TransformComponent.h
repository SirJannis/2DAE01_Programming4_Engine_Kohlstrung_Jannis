#pragma once
#include "BaseComponent.h"
#include "glm/glm.hpp"

namespace MyEngine
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent(glm::fvec2 pos = {0.f, 0.f});
		void FixedUpdate(const float fixedDeltaTime) override;
		void Update(const float deltaTime) override;
		void Render() const override;

		const glm::fvec2& GetPosition() const;
		void SetPosition(float x, float y);

		const float& GetRotation() const { return m_Angle; }
		void SetAngle(float angle);

	private:
		friend class PhysicsComponent;
		glm::fvec2 m_Position;
		float m_Angle;
	};
}
