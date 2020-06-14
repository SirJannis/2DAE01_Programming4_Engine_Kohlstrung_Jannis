#pragma once
#include "BaseComponent.h"
#include <SDL_pixels.h>
#include "glm/common.hpp"
namespace MyEngine
{
	class Font;
	class Texture2D;
	struct ColorRGBA;
	class TextComponent final : public BaseComponent
	{
	public:

		void FixedUpdate(const float fixedDeltaTime) override;
		void Update(const float deltaTime) override;
		void Render() const override;

		TextComponent(const std::string& text, Font* pFont, SDL_Color color, const float angle = 0, const glm::fvec2 pivot = { .5f, .5f }, const glm::fvec2 offset = { .5f, .5f });
		~TextComponent();

		void SetText(const std::string& text);
		Texture2D* GetTexture() const;

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		Font* m_pFont;
		Texture2D* m_pTexture;
		SDL_Color m_Color;
		float m_Angle;
		glm::fvec2 m_Pivot;
		glm::fvec2 m_Offset;
	};
}

