#include "MiniginPCH.h"
#include "SoundEffect.h"
#include <iostream>
#include "SDL_mixer.h"
#include "../Helpers/Logger.h"

MyEngine::SoundEffect::SoundEffect(const std::string& path )
	:m_pMixChunk{ Mix_LoadWAV( path.c_str( ) ) }
	,m_Path{path}
{
	if ( m_pMixChunk == nullptr )
	{
		std::string errorMsg = "SoundEffect: Failed to load " + path + ",\nSDL_mixer Error: " + Mix_GetError( );
		Logger::LogError(errorMsg);
	}
}
MyEngine::SoundEffect::~SoundEffect( )
{
	Mix_FreeChunk( m_pMixChunk );
	m_pMixChunk = nullptr;
}

bool MyEngine::SoundEffect::IsLoaded( ) const
{
	return m_pMixChunk != nullptr;
}

bool MyEngine::SoundEffect::Play( int loops )
{
	if ( m_pMixChunk != nullptr )
	{
		m_Channel = Mix_PlayChannel( -1, m_pMixChunk, loops );
		return m_Channel == -1 ? false : true;
	}
	else
	{
		return false;
	}
}

void MyEngine::SoundEffect::SetVolume( int value )
{
	if ( m_pMixChunk != nullptr )
	{
		Mix_VolumeChunk( m_pMixChunk, value );
	}
}

int MyEngine::SoundEffect::GetVolume( ) const
{
	if ( m_pMixChunk != nullptr )
	{
		return Mix_VolumeChunk( m_pMixChunk, -1 );
	}
	else
	{
		return -1;
	}
}

void MyEngine::SoundEffect::Stop( )
{
	Mix_HaltChannel(m_Channel);
}

void MyEngine::SoundEffect::Pause( )
{
	Mix_Pause( m_Channel );
}
void MyEngine::SoundEffect::Resume( )
{
	Mix_Resume( m_Channel );
}




