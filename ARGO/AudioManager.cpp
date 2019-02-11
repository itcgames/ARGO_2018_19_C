#include "AudioManager.h"

AudioManager* AudioManager::sInstance;

AudioManager* AudioManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new AudioManager();
	}
	return sInstance;
}

void AudioManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

AudioManager::AudioManager()
{
	
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
	{
		printf("Mixer Initializattion Error: %s\n", Mix_GetError());
	}
}

AudioManager::~AudioManager()
{
	
	Mix_CloseAudio();
}

bool AudioManager::load(std::string filename, std::string id, sound_type type)
{
	filename = "Sounds/" + filename;
	if (type == SOUND_MUSIC)
	{
		Mix_Music* musFile = Mix_LoadMUS(filename.c_str());
		if (musFile == 0)
		{
			std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}

		m_Music[id] = musFile;
		return true;
	}
}

bool AudioManager::loadSFX(std::string filename, std::string id, sound_type type)
{
	filename = "Sounds/" + filename;
	if (type == SOUND_SFX)
	{
		Mix_Chunk* sfxFile = Mix_LoadWAV(filename.c_str());
		if (sfxFile == 0)
		{
			std::cout << "Could not load SFX file: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}
		m_SFX[id] = sfxFile;
		return true;
	}
}

void AudioManager::PlayMusic(std::string filename, int loops)
{
	Mix_PlayMusic(m_Music[filename], loops);
}

void AudioManager::PlaySFX(std::string filename, int loops)
{
	Mix_PlayChannel(-1, m_SFX[filename], loops);
}

void AudioManager::PauseMusic()
{
	if (Mix_PlayingMusic != 0)
	{
		Mix_PauseMusic();
	}
}

void AudioManager::ResumeMusic()
{
	if (Mix_PausedMusic() != 0)
	{
		Mix_ResumeMusic();
	}
}

//void AudioManager::clearSoundMap()
//{
//	for (auto i = m_Music.begin(); i!=m_Music.end(); i++)
//	{
//		if (i->second != nullptr)
//		{
//			Mix_FreeMusic(i->second);
//			i->second = nullptr;
//		}
//	}
//	m_Music.clear();
//
//	for (auto j = m_SFX.begin(); j != m_SFX.end(); j++)
//	{
//		if (j->second != nullptr)
//		{
//			Mix_FreeChunk(j->second);
//			j->second = nullptr;
//		}
//	}
//	m_SFX.clear();
//}