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
	for (int i = 0; i < 3; i++)
	{ 
		observers.push_back(observer_);
	}
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
	Mix_PlayChannel(vol, m_SFX[filename], loops);
}

void AudioManager::muteSFX(int volume)
{
	vol = volume;
}

void AudioManager::unmuteSFX(int volume)
{
	vol = volume;
}

void AudioManager::PauseMusic()
{

	if (Mix_PlayingMusic != 0)
	{
		Mix_PauseMusic();
		current_ObserverState = MUSIC_MUTED;
		notify(current_ObserverState);
	}
}

void AudioManager::ResumeMusic()
{
	if (Mix_PausedMusic() != 0)
	{
		Mix_ResumeMusic();
		current_ObserverState = MUSIC_UNMUTED;
		notify(current_ObserverState);
	}
}