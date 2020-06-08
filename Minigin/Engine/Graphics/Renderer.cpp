#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "../Managers/SceneManager.h"
#include "../Managers/PhysicsManager.h"
#include "Texture2D.h"

void MyEngine::Renderer::Init(SDL_Window * window,const SDL_Color& backColor)
{
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
	m_BackGroundColor = backColor;
}

void MyEngine::Renderer::Render() const
{
	SDL_SetRenderDrawColor(m_Renderer, m_BackGroundColor.r, m_BackGroundColor.g, m_BackGroundColor.b, m_BackGroundColor.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance()->Render();

	SDL_RenderPresent(m_Renderer);
}

void MyEngine::Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void MyEngine::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	int w;
	int h;
	SDL_GetRendererOutputSize(m_Renderer, &w, &h);
	//Move this rect to Rendercomponent maybe
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = h - static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	//Use SDL_RenderCopyEx
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void MyEngine::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	int w;
	int h;
	SDL_GetRendererOutputSize(m_Renderer, &w, &h);
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = h - static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void MyEngine::Renderer::RenderLine(const SDL_Point& p1, const SDL_Point& p2, const SDL_Point& pivot, const SDL_Color& color)
{
	int w;
	int h;
	SDL_GetRendererOutputSize(m_Renderer, &w, &h);
	SDL_SetRenderDrawColor(Renderer::GetInstance()->GetSDLRenderer(), color.r , color.g, color.b , color.a);
	SDL_RenderDrawLine(Renderer::GetInstance()->GetSDLRenderer(), p1.x,h- (2* pivot.y - p1.y), p2.x,h- (2 * pivot.y - p2.y));
}
