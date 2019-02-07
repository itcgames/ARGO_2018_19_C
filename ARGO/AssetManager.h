#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H
#include <map>
#include <SDL_mixer.h>
#include "Game.h"
class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	Mix_Music * GetMusic(std::string filename);
	Mix_Chunk* GetSFX(std::string filename);

	static AssetManager * Instance();
	static void Release();

private:
	
	static AssetManager* sInstance;
	std::map<std::string, Mix_Music*> soundtrack;
	std::map<std::string, Mix_Chunk*> m_SFX;
};
#endif
