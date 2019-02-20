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
#include "Level.h"
#include "Particle.h"
#include "Factory.h"
#include <iterator>
#include "AmmoSystem.h"

// Network
#include "Client.h"
#include <sstream>
#include "Animation.h"


using namespace std;


enum class
	GameState
{
	None,
	License,
	Splash,
	MainMenu,
	Lobby,
	GameScreen,
	GameOverScreen,
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
	void setGameState(GameState gameState);

private:

	void processEvents();
	void update(float dt);
	void render(float dt);
	void initialise();
	void getDistance();


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
	/*HealthComponent* m_healthComponentOne;
	HealthComponent* m_healthComponentTwo;
	HealthComponent* m_healthComponentThree;
	HealthComponent* m_healthComponentFour;*/
	ControlComponent* m_ctrlComponent;
	PositionComponent* m_posComponent;
	CollisionComponent* CollisionComp;
	ParticleComponent* m_partComponent;

	Lobby * m_lobbyScreen;

	CombatSystem comsystem;
    //LifeSystem ls;
	RenderSystem rs;
	AISystem ais;
	ParticleSystem ps;
	ControlSystem cs;
	GameState m_currentGameState;
	GameState m_previousGameState;
	AmmoSystem ammos;

	CollisionSystem Colls;
	LTexture m_texture, wallTxt;


	PhysicsSystem phs;
	LifeSystem ls;

	Factory* m_factory;
	std::vector<PowerUp*> m_powerUps;
	double disBetweenAiPlayer = 10000;

	int m_timerSpawn;
	const int m_spawnTimeLimit = 1000;
	const int m_numOfPowerUps = 5;


	void rumble();
	void resetCamera();
	int rTimer = 0;
	int SCREEN_WIDTH = 1500;
	int SCREEN_HEIGHT = 1000;
	int mouseX, mouseY;
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

	int m_stateTimer;
	const int m_stateTimerLimit = 300;

};

#endif // !GAME
