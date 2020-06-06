#pragma once
#include <string>
typedef struct _Mix_Music Mix_Music;
namespace MyEngine
{
	class SoundStream
	{
		friend class SoundManager;
	public:
		explicit SoundStream(const std::string& path);
		~SoundStream();
		SoundStream(const SoundStream& other) = delete;
		SoundStream& operator=(const SoundStream& rhs) = delete;
		SoundStream(SoundStream&& other) = delete;
		SoundStream& operator=(SoundStream&& other) = delete;

		bool IsLoaded() const;
		bool Play(bool repeat) const;
		static void Stop();
		static void Pause();
		static void Resume();
		static void SetVolume(int value);
		static int GetVolume();
		static bool IsPlaying();

	private:
		Mix_Music* m_pMixMusic;
		const std::string m_Path;
	};
}