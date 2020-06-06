#include "MiniginPCH.h"
#include "SoundManager.h"
#include "SDL_mixer.h"
#include "../Helpers/SoundEffect.h"
#include "../Helpers/SoundStream.h"
#include "../Helpers/Logger.h"

MyEngine::SoundManager::~SoundManager()
{
	for (const SoundEffect* pEffect : m_SoundEffects)
		delete pEffect;
	for (const SoundStream* pStream : m_SoundStreams)
		delete pStream;
}

void MyEngine::SoundManager::Init(const std::string& dataPath)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		Logger::GetInstance()->LogError("Core::Initialize( ), error when calling Mix_OpenAudio: " + std::string(Mix_GetError()));
		return;
	}
	m_DataPath = dataPath;
}

MyEngine::SoundEffect* MyEngine::SoundManager::LoadSoundEffect(const std::string& file)
{
	m_SoundEffects.push_back(new MyEngine::SoundEffect(m_DataPath + file));
	return m_SoundEffects.back();
}

MyEngine::SoundStream* MyEngine::SoundManager::LoadSoundStream(const std::string& file)
{
	m_SoundStreams.push_back(new MyEngine::SoundStream(m_DataPath + file));
	return m_SoundStreams.back();
}
