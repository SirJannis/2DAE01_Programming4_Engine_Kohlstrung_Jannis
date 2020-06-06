#include "MiniginPCH.h"
#include "SoundStream.h"
#include "SDL_mixer.h"
#include <iostream>
#include "../Helpers/Logger.h"

MyEngine::SoundStream::SoundStream( const std::string& path )
	:m_pMixMusic{ Mix_LoadMUS( path.c_str( )) }
	, m_Path{ path }
{
	if ( m_pMixMusic == nullptr )
	{
		std::string errorMsg = "SoundStream: Failed to load " + path + ",\nSDL_mixer Error: " + Mix_GetError( );
		Logger::GetInstance()->LogError(errorMsg);
	}
}

MyEngine::SoundStream::~SoundStream( )
{
	Mix_FreeMusic( m_pMixMusic );
	m_pMixMusic = nullptr;
}

bool MyEngine::SoundStream::IsLoaded( ) const
{
	return m_pMixMusic != nullptr;
}

bool MyEngine::SoundStream::Play(bool repeat ) const
{
	if ( m_pMixMusic != nullptr )
	{
		int result{ Mix_PlayMusic( m_pMixMusic, repeat ? -1 : 1 ) };
		return result == 0 ? true : false;
	}
	else
	{
		return false;
	}
}

void MyEngine::SoundStream::Stop( )
{
	Mix_HaltMusic( );
}
void MyEngine::SoundStream::Pause( )
{
	Mix_PauseMusic( );
}

void MyEngine::SoundStream::Resume( )
{
	Mix_ResumeMusic( );
}

int MyEngine::SoundStream::GetVolume( )
{
	return Mix_VolumeMusic( -1 );
}

bool MyEngine::SoundStream::IsPlaying( )
{
	return Mix_PlayingMusic( ) == 0 ? false : true;
}

void MyEngine::SoundStream::SetVolume( int value )
{
	Mix_VolumeMusic( value );
}

