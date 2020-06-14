#include "MiniginPCH.h"
#include "SoundManager.h"
#include "SDL_mixer.h"
#include "../Helpers/SoundEffect.h"
#include "../Helpers/SoundStream.h"
#include "../Helpers/Logger.h"


MyEngine::SoundManager::~SoundManager()
{
	for (const std::pair <const Event, std::vector<SoundEffect*>>& pair : m_SoundEffects)
	{
		for (SoundEffect* pEffect : pair.second)
			SafeDelete(pEffect);
	}
	for (const std::pair <const Event, std::vector<SoundStream*>>& pair : m_SoundStreams)
	{
		for (SoundStream* pStream : pair.second)
			SafeDelete(pStream);
	}
}

void MyEngine::SoundManager::Init(const std::string& dataPath)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		Logger::LogError("Core::Initialize( ), error when calling Mix_OpenAudio: " + std::string(Mix_GetError()));
		return;
	}
	m_DataPath = dataPath;
}


MyEngine::SoundEffect* MyEngine::SoundManager::LoadSoundEffect(const std::string& file, const Event event)
{
	m_SoundEffects[event].push_back(new MyEngine::SoundEffect(m_DataPath + file));
	return m_SoundEffects[event].back();
}

MyEngine::SoundStream* MyEngine::SoundManager::LoadSoundStream(const std::string& file, const Event event)
{
	m_SoundStreams[event].push_back(new MyEngine::SoundStream(m_DataPath + file));
	return m_SoundStreams[event].back();
}

void MyEngine::SoundManager::Notify(const Event event, const int value, const GameObject*)
{
	for (SoundEffect* pEffect : m_SoundEffects[event])
	{
		pEffect->Play(value);
	}

	for (SoundStream* pStream : m_SoundStreams[event])
	{
		pStream->Play(bool(value));
	}
}
