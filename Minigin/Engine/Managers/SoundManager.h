#pragma once
#include <vector>
#include <map>
#include "../Helpers/Observer.h"
namespace MyEngine
{
	class SoundEffect;
	class SoundStream;
	class SoundManager final : public Observer<SoundManager>
	{
	public:
		SoundManager() = default;
		~SoundManager();
		void Init(const std::string& dataPath);
		SoundEffect* LoadSoundEffect(const std::string& file,const Event event);
		SoundStream* LoadSoundStream(const std::string& file,const Event event);
		void Notify(const Event event, const int value = 0, const GameObject* gameObject = nullptr) override;
	private:
		std::map<const Event, std::vector<SoundStream*>> m_SoundStreams;
		std::map<const Event, std::vector<SoundEffect*>>m_SoundEffects;
		std::string m_DataPath;
	};
}