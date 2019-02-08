#include "AssetManager.h"


AssetManager::AssetManager()
{
}


AssetManager::~AssetManager()
{
}

AssetManager * AssetManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new AssetManager();
	}
	return nullptr;
}

void AssetManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

Mix_Music * AssetManager::GetMusic(std::string filename)
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Sounds/" + filename);


	if (soundtrack[fullPath] == nullptr)
	{
		soundtrack[fullPath] = Mix_LoadMUS(fullPath.c_str());
		if (soundtrack[fullPath] == NULL)
		{
			printf("Soundtrack loading error: File-%s Error-%s", filename.c_str(), Mix_GetError());
		}
	}
	return soundtrack[fullPath];
}

Mix_Chunk * AssetManager::GetSFX(std::string filename)
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Sounds/" + filename);

	if (m_SFX[fullPath] == nullptr)
	{
		m_SFX[fullPath] = Mix_LoadWAV(fullPath.c_str());
		if (m_SFX[fullPath] == NULL)
		{
			printf("SFX loading error: File-%s Error-%s", filename.c_str(), Mix_GetError());
		}
	}
	return m_SFX[fullPath];
}