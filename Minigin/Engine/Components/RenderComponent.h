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

		void FixedUpdate(const float fixedDeltaTime) override;
		void Update(const float deltaTime) override;
		//Render calculatest dest & source Rect, pivot then passes it down to render texture
		void Render() const override;

		void AddTexture(Texture2D* text);
	private:
		//add a pivot here to be the center of the texture
		std::vector<Texture2D*> m_Textures;
		size_t m_NrTextures;
	};
}