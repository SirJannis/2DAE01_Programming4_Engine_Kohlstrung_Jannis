#pragma once
#include "BaseComponent.h"
#include "../Helpers/Structs.h"

namespace MyEngine
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent(Vector2 pos = {0.f, 0.f});
		virtual void Update(const float deltaTime) override;
		virtual void Render() const override;

		const Vector2& GetPosition() const;
		void SetPosition(float x, float y);

	private:
		Vector2 m_Position;
	};
}
