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
#include "CollisionSystem.h"
#include "CombatSystem.h"
#include "AudioManager.h"
#include "AiSystem.h"
#include "ParticleSystem.h"
#include "PhysicsSystem.h"


//Jamie
#include "Level.h"
#include "Particle.h"
#include "Factory.h"
#include <iterator>

// Network
#include "Client.h"
#include <sstream>

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
	void update(float dt);
	void render(float dt);
	void initialise();
	void getDistance();


	void setGameState(GameState gameState);

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Event event;
	bool exit;

	level* m_level;

	//Entity* m_player;
	Entity* m_cat;
	Entity* m_alien;
	Entity* m_dog;
	Entity* m_flag;
	HealthComponent* m_healthComponentOne;
	HealthComponent* m_healthComponentTwo;
	HealthComponent* m_healthComponentThree;
	HealthComponent* m_healthComponentFour;
	ControlComponent* m_ctrlComponent;
	PositionComponent* m_posComponent;
	CollisionComponent* CollisionComp;
	ParticleComponent* m_partComponent;

	CombatSystem comsystem;
	HealthSystem hs;
	RenderSystem rs;
	AISystem ais;
	ParticleSystem ps;
	ControlSystem cs;
	GameState m_currentGameState;
	GameState m_previousGameState;

	CollisionSystem Colls;
	LTexture m_texture, wallTxt;


	PhysicsSystem phs;

	Factory* m_factory;
	std::vector<PowerUp*> m_powerUps;
	//jamie
	double disBetweenAiPlayer = 10000;
	//Fuzzy* m_fuzzy;

	int m_timerSpawn;
	const int m_spawnTimeLimit = 2000;
	const int m_numOfPowerUps = 2;

	void rumble();
	void resetCamera();
	int rTimer = 0;
	int SCREEN_WIDTH = 1500;
	int SCREEN_HEIGHT = 900;
	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// Player
	int m_playerIndex = 5;
	Entity player;
	Entity player2;
	Entity player3;
	Entity player4;

	// Network
	Client * m_client;
	void updateNetwork();
};

#endif // !GAME
