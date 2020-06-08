#pragma once
#include "../Helpers/Singleton.h"

namespace MyEngine
{
	//Todo: Rework this to hold the pointers and delete them when it gets destroyed
	// If loading something in that already exists then return that
	// 1 options is struct with font* and path and another struct with texture* and path
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		ResourceManager() = default;
		void Init(const std::string& data);
		Texture2D* LoadTexture(const std::string& file) const;
		Font* LoadFont(const std::string& file, unsigned int size) const;
	private:
		friend class Singleton<ResourceManager>;
		std::string m_DataPath;
	};
}
