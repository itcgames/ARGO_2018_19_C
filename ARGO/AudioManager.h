#pragma once

#include <iostream>
#include <map>
#include <string>
#include <SDL_mixer.h>

enum sound_type {
	SOUND_MUSIC = 1,
	SOUND_SFX = 1
};

class AudioManager
{
public:
	static AudioManager* Instance();

	static void Release();
	bool load(std::string fileName, std::string id, sound_type type);
	bool loadSFX(std::string filename, std::string id, sound_type type);

	void PlayMusic(std::string filename, int loops);
	void PlaySFX(std::string filename, int loops);
	void muteSFX(int vol);
	void unmuteSFX(int vol);
	void clearSoundMap();
	void PauseMusic();
	void VolumeUp();
	void VolumeDown();
	void ResumeMusic();

	

private:
	static AudioManager* sInstance;

	std::map<std::string, Mix_Chunk*> m_SFX;
	std::map<std::string, Mix_Music*> m_Music;
	int vol = -1;
	AudioManager();
	~AudioManager();

	AudioManager(const AudioManager&);
	AudioManager& operator=(const AudioManager&);
};

typedef AudioManager theAudioManager;


