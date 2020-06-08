#pragma once
#include <vector>
#include "../Helpers/Singleton.h"
namespace MyEngine
{
	class SoundEffect;
	class SoundStream;
	class SoundManager final : public Singleton<SoundManager>
	{
	public:
		SoundManager() = default;
		~SoundManager();
		void Init(const std::string& dataPath);
		SoundEffect* LoadSoundEffect(const std::string& file);
		SoundStream* LoadSoundStream(const std::string& file);
	private:
		std::vector<SoundStream*> m_SoundStreams;
		std::vector<SoundEffect*> m_SoundEffects;
		std::string m_DataPath;
	};
}