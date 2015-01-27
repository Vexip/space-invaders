#include "stdafx.h"
#include "SoundManager.h"
#include "SoundClip.h"

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{
	Shutdown();
}

bool SoundManager::Initialize()
{
	bool ret = true;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		const char* error = Mix_GetError();
		return false;
	}
	return ret;
}

void SoundManager::Shutdown()
{

	for (unsigned int i = 0; i < m_axSoundClips.size(); i++)
	{
		delete m_axSoundClips[i];
		m_axSoundClips[i] = nullptr;
	}
	m_axSoundClips.clear();

	{
		std::map<std::string, Mix_Chunk*>::iterator it = m_axSounds.begin();
		while (it != m_axSounds.end())
		{
			Mix_FreeChunk(it->second);
			it->second = nullptr;
			it++;
		}
		m_axSounds.clear();
	}

	Mix_CloseAudio();
}

SoundClip* SoundManager::CreateSoundClip(std::string p_sFilename)
{
	SoundClip* ret = nullptr;

	std::map<std::string, Mix_Chunk*>::iterator it = m_axSounds.find(p_sFilename);

	if (it == m_axSounds.end())
	{
		Mix_Chunk* chunk = Mix_LoadWAV(p_sFilename.c_str());
		std::pair<std::string, Mix_Chunk*> pair;
		pair = std::make_pair(p_sFilename, chunk);
		m_axSounds.insert(pair);

		ret = new SoundClip(chunk);
		m_axSoundClips.push_back(ret);
	}
	else
	{
		ret = new SoundClip(it->second);
		m_axSoundClips.push_back(ret);
	}

	return ret;
}
