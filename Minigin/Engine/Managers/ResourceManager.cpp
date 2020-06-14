#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "../Graphics/Renderer.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/Font.h"

MyEngine::ResourceManager::~ResourceManager()
{
	for (Texture2D* pTexture : m_Textures)
	{
		SafeDelete(pTexture);
	}
	for (Font* pFont : m_Fonts)
	{
		SafeDelete(pFont);
	}
}

void MyEngine::ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

MyEngine::Texture2D* MyEngine::ResourceManager::LoadTexture(const std::string& file)
{
	const auto fullPath = m_DataPath + file;
	for (Texture2D* pTexture : m_Textures)
	{
		if (pTexture->GetPath() == fullPath)
			return pTexture;
	}
	auto texture = IMG_LoadTexture(Renderer::GetInstance()->GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	Texture2D* retText = new Texture2D(texture);
	retText->SetPath(fullPath);
	m_Textures.push_back(retText);
	return retText;
}

MyEngine::Font* MyEngine::ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	const auto fullPath = m_DataPath + file;
	for (Font* pFont : m_Fonts)
	{
		if (pFont->GetPath() == fullPath)
			return pFont;
	}
	Font* pRetFont = new Font(fullPath, size);
	m_Fonts.push_back(pRetFont);
	return pRetFont;
}
