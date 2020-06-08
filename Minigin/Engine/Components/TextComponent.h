#pragma once
#include "BaseComponent.h"
#include <SDL_pixels.h>
//Todo: Make the TextComponent draw itself
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

		TextComponent(const std::string& text, Font* pFont, SDL_Color color);
		~TextComponent();

		void SetText(const std::string& text);
		Texture2D* GetTexture() const;

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		Font* m_pFont;
		Texture2D* m_pTexture;
		SDL_Color m_Color;
	};
}

