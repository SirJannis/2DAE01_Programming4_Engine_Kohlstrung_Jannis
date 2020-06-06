#pragma once
#include "BaseComponent.h"
#include <vector>
namespace MyEngine
{
	class Texture2D;
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent(const size_t maxTextures);
		~RenderComponent();

		virtual void FixedUpdate(const float fixedDeltaTime) override;
		virtual void Update(const float deltaTime) override;
		virtual void Render() const override;

		void AddTexture(Texture2D* text);
	private:
		std::vector<Texture2D*> m_Textures;
		size_t m_NrTextures;
	};
}