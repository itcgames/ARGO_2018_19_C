#pragma once
#include <iostream>
#include <SDL_image.h>
#include "LTexture.h"
#include <vector>

class Lobby
{
public:
	Lobby(SDL_Renderer * ren);
	~Lobby();
	void init();
	void changeState(int index, bool state);
	bool everyoneReady();
	void update(int index, int x, int y);
	void render(SDL_Renderer * ren);
	std::string sendMsg(int index);

private:
	LTexture m_readyTexture;
	std::vector<LTexture> m_playerTextures;
	std::vector<bool> m_playerReady;
	LTexture m_playerTexture;
	LTexture m_player2Texture;
	LTexture m_player3Texture;
	LTexture m_player4Texture;
	int m_readyX, m_readyY, m_readyW, m_readyH;
};