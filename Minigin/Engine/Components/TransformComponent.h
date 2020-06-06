#pragma once
#include "BaseComponent.h"
#include "glm/glm.hpp"

namespace MyEngine
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent(glm::fvec2 pos = {0.f, 0.f});
		virtual void FixedUpdate(const float fixedDeltaTime) override;
		virtual void Update(const float deltaTime) override;
		virtual void Render() const override;

		const glm::fvec2& GetPosition() const;
		void SetPosition(float x, float y);

	private:
		glm::fvec2 m_Position;
	};
}
