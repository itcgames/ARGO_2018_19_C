#pragma once
#ifndef GAME
#define GAME

#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <WS2tcpip.h>
#include <string.h>
#include "EntityComponent.h"
#include "LifeSystem.h"
#include "RenderSystem.h"
#include "ControlSystem.h"
#include "CollisionSystem.h"
#include "CombatSystem.h"
#include "AudioManager.h"
#include "AiSystem.h"
#include "ParticleSystem.h"
#include "PhysicsSystem.h"
#include "LifeSystem.h"
#include "Lobby.h"
#include "Credits.h"
#include "Level.h"
#include "Particle.h"
#include "Factory.h"
#include <iterator>
#include "AmmoSystem.h"

// Network
#include "Client.h"
#include <sstream>
#include "Animation.h"

//Screens
#include "Lobby.h"
#include "GameOver.h"
#include "menu.h"
#include "GameScreen.h"

using namespace std;

class Lobby;

class Game {

public:
	Game();
	~Game();

	void run();
	void setGameState(GameState gameState);
	void playerAI(int pIndex, bool ai);
	void setPlayer(int pIndex);

private:

	void processEvents();
	void update(float dt);
	void render(float dt);
	void initialise();

	std::vector<float> msgToPos(std::string s);


	SDL_Window *m_window;
	int SCREEN_WIDTH = 1500;
	int SCREEN_HEIGHT = 1000;
	SDL_Renderer *m_renderer;
	SDL_Event event;
	bool exit;

	
	// Screens
	Lobby * m_lobbyScreen;
	Credits * m_creditsScreen;
	GameOverScreen * m_gameoverScreen;
	MenuScreen * m_menuScreen;
	GameScreen * m_gameScreen;

	GameState m_currentGameState;
	GameState m_previousGameState;

	
	int mouseX, mouseY;

	
	
	Client * m_client;

	int m_playerIndex = 5;

	void updateNetwork();

};

#endif // !GAME
