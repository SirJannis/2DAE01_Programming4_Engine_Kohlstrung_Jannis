#pragma once
#include <vector>
#include "../Helpers/Singleton.h"

namespace MyEngine
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		ResourceManager() = default;
		~ResourceManager();
		void Init(const std::string& data);
		Texture2D* LoadTexture(const std::string& file);
		Font* LoadFont(const std::string& file, unsigned int size);
	private:
		friend class Singleton<ResourceManager>;
		std::string m_DataPath;
		std::vector<Texture2D*> m_Textures;
		std::vector<Font*> m_Fonts;
	};
}
