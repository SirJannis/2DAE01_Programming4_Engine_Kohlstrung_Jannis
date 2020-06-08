#pragma once
#include "BaseComponent.h"
#include <vector>
namespace MyEngine
{
	//Think about if i need the animated rendercomponent or if it can be done otherwise
	class Texture2D;
	class AnimatedRenderComponent final : public BaseComponent
	{
	public:
		AnimatedRenderComponent(const size_t maxTextures);
		~AnimatedRenderComponent();

		void FixedUpdate(const float fixedDeltaTime) override;
		void Update(const float deltaTime) override;
		void Render() const override;

		void AddTexture(Texture2D* text);
	private:
		std::vector<Texture2D*> m_Textures;
		size_t m_NrTextures;
	};
}

