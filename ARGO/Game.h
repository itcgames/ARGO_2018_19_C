#pragma once
#ifndef GAME
#define GAME

#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <iostream>
#include <WS2tcpip.h>
#include <string.h>
#include "EntityComponent.h"
#include "HealthSystem.h"
#include "RenderSystem.h"
#include "ControlSystem.h"
#include "AiSystem.h"
#include "PhysicsSystem.h"

using namespace std;
enum class
	GameState
{
	None,
	License,
	Splash,
	MainMenu,
	GameScreen,
	CoopScreen,
	Options,
	Credits,
	Help

};
class Game {

public:
	Game();
	~Game();

	void run();

private:

	void processEvents();
	void update();
	void render();
	void initialise();
	void setGameState(GameState gameState);

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Event event;
	bool exit;

	Entity* m_player;
	Entity* m_cat;
	Entity* m_alien;
	Entity* m_dog;

	HealthComponent* m_healthComponentOne;
	HealthComponent* m_healthComponentTwo;
	HealthComponent* m_healthComponentThree;
	HealthComponent* m_healthComponentFour;
	ControlComponent* m_ctrlComponent;
	PositionComponent* m_posComponent;


	HealthSystem hs;
	RenderSystem rs;
	AiSystem ais;
	ControlSystem cs;
	PhysicsSystem ps;
	LTexture m_texture;
	GameState m_currentGameState;
	GameState m_previousGameState;

};



#endif // !GAME