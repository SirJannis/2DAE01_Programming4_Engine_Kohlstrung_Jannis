#include "MiniginPCH.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_pixels.h>

#include "TextComponent.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Font.h"
#include "../Graphics/Texture2D.h"
#include "../Scene/GameObject.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

void MyEngine::TextComponent::FixedUpdate(const float fixedDeltaTime)
{
	UNREFERENCED_PARAMETER(fixedDeltaTime);
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance()->GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture->SetTexture(texture);
		m_NeedsUpdate = false;
	}
}

void MyEngine::TextComponent::Update(const float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void MyEngine::TextComponent::Render() const
{
	glm::vec2 pos{ m_pGameObject->GetComponent<TransformComponent>()->GetPosition() };
	SDL_Rect dstRect{ static_cast<int>(pos.x), static_cast<int>(pos.y) };
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &dstRect.w, &dstRect.h);
	SDL_Point pivot = { int(m_Pivot.x * dstRect.w), int(m_Pivot.y * dstRect.h) };
	dstRect.x += -pivot.x + int(m_Offset.x);
	dstRect.y += pivot.y + int(m_Offset.y);
	Renderer::GetInstance()->RenderTexture(*m_pTexture, &dstRect, nullptr, m_pGameObject->GetComponent<TransformComponent>()->GetRotation() +m_Angle, pivot, false);
}

MyEngine::TextComponent::TextComponent(const std::string& text, Font* pFont, SDL_Color color, const float angle, const glm::fvec2 pivot, const glm::fvec2 offset)
	: m_NeedsUpdate(true), m_Text(text), m_pFont(pFont), m_pTexture(nullptr), m_Color(color), m_Angle{angle}, m_Pivot{pivot}, m_Offset{offset}
{
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance()->GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_pTexture = new Texture2D(texture);
	m_NeedsUpdate = false;
}

MyEngine::TextComponent::~TextComponent()
{
	SafeDelete(m_pTexture);
}


void MyEngine::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

MyEngine::Texture2D* MyEngine::TextComponent::GetTexture() const
{
	return m_pTexture;
}
