#pragma once
#include "BaseComponent.h"
#include <vector>
#include "glm/common.hpp"
namespace MyEngine
{
	class Texture2D;
	struct RenderTexture
	{
		Texture2D* Texture;
		int DrawWidth;
		int DrawHeight;
		bool IsMirrored;
		glm::fvec2 Pivot;
		glm::fvec2 Offset;
		glm::fvec2 SrcPos;
		glm::fvec2 SrcDim;
		float Angle;
	};
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent() = default;

		void FixedUpdate(const float fixedDeltaTime) override;
		void Update(const float deltaTime) override;
		void Render() const override;

		void AddTexture(Texture2D* text, const int drawWidth = 0, const int drawHeight = 0, const bool isMirrored = false, const glm::fvec2& pivot = { .5f, .5f }, const glm::fvec2& offset = { 0.f, 0.f }, const glm::fvec2& srcPos = { 0.f, 0.f }, const glm::fvec2& srcDim = { 1.f, 1.f }, const float angle = 0.f);
	private:

		std::vector<RenderTexture> m_Textures;
	};
}