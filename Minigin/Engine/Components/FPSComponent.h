#pragma once
#include "BaseComponent.h"
namespace MyEngine
{
	class FPSComponent final : public BaseComponent
	{
	public:
		void FixedUpdate(const float fixedDeltaTime) override;
		void Update(const float deltaTime) override;
		void Render() const override;

	private:
		float m_DeltaTime;
		int m_FPS;
	};
}

