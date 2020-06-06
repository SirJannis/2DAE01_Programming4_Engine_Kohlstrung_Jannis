#pragma once
#include <string>
struct Mix_Chunk;

namespace MyEngine
{

	class SoundEffect
	{
	public:
		explicit SoundEffect(const std::string& path);
		~SoundEffect();
		SoundEffect(const SoundEffect& other) = delete;
		SoundEffect& operator=(const SoundEffect& rhs) = delete;
		SoundEffect(SoundEffect&& other) = delete;
		SoundEffect& operator=(SoundEffect&& rhs) = delete;

		bool IsLoaded() const;
		bool Play(int loops);
		void SetVolume(int value);
		int GetVolume() const;
		void Stop();
		void Pause();
		void Resume();

	private:
		Mix_Chunk* m_pMixChunk;
		const std::string m_Path;
		int m_Channel;
	};

}