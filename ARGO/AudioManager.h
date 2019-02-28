#pragma once

#include <iostream>
#include <map>
#include <string>
#include <SDL_mixer.h>
#include <vector>

enum sound_type {
	SOUND_MUSIC = 1,
	SOUND_SFX = 1
};

enum observer_State {
	MUSIC_MUTED,
	MUSIC_UNMUTED
};

class Observer {



public:
	Observer() {};
	virtual ~Observer() {};
	virtual void onNotify(observer_State s) = 0;
};

class AudioManager : public Observer
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
	void PauseMusic();
	void ResumeMusic();
	
	virtual void onNotify(observer_State s)
	{
		if (s == MUSIC_MUTED)
		{
			std::cout << "MUSIC MUTED" << std::endl;
		}
		else if (s == MUSIC_UNMUTED)
		{
			std::cout << "MUSIC UNMUTED" << std::endl;
		}
	}

protected:
	void notify(observer_State s) {
		for(int i=0; i< observers.size(); i++)
		onNotify(s);
	}

private:
	static AudioManager* sInstance;
	Observer* observer_;
	std::vector<Observer*> observers;
	std::map<std::string, Mix_Chunk*> m_SFX;
	std::map<std::string, Mix_Music*> m_Music;
	observer_State current_ObserverState;
	int vol = -1;
	AudioManager();
	~AudioManager();
	bool musicPaused;
	AudioManager(const AudioManager&);
	AudioManager& operator=(const AudioManager&);
};

typedef AudioManager theAudioManager;


