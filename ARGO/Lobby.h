#pragma once
#include <iostream>
#include <SDL_image.h>
#include "LTexture.h"
#include <vector>
#include "menu.h"
#include "Client.h"
#include "Game.h"

class Game;

class Lobby
{
public:
	Lobby(SDL_Renderer * ren, Game * game);
	~Lobby();
	void init();
	void changeState(int index, bool state);
	void inLobby(int index, bool state);
	bool getInLobby(int index);
	bool everyoneReady(int countdown);
	void update(int index, int x, int y, GameState & gs);
	void render(SDL_Renderer * ren);
	void updateNetwork(Client * client, int pIndex, std::string s);
	std::string sendMsg(int index);
	void setReadyButton(bool ru);
	bool getReadyButton();


private:
	Game * m_game;

	// Buttons
	LTexture m_readyTexture;
	int m_readyX, m_readyY, m_readyW, m_readyH;
	LTexture m_backTexture;
	int m_backX, m_backY, m_backW, m_backH;
	// Indicators
	std::vector<LTexture> m_playerTextures;
	std::vector<bool> m_playerReady;
	std::vector<bool> m_playerInLobby;
	bool m_inLobby;
	std::vector<float> msgToPos(std::string s);

	// Player Characters
	LTexture m_playerTexture;
	LTexture m_player2Texture;
	LTexture m_player3Texture;
	LTexture m_player4Texture;
	int m_playerIndex;

	// Count down
	int m_countdown;
	TTF_Font *m_font;
	LTexture m_textTexture;
	void drawText(SDL_Renderer * ren, std::string s, int x, int y);

	// Network 
	int m_stateTimer;
	const int m_stateTimerLimit = 200;
};
