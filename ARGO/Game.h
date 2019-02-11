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
#include "AiSystem.h"
#include "ParticleSystem.h"
#include "Dot.h"
#include "PhysicsSystem.h"
#include "Level.h"
#include "Particle.h"
#include "Fuzzy.h"
#include "Factory.h"
#include <iterator>


using namespace std;

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
	double getDistance();

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Event event;
	bool exit;
	Dot* m_playerDot;
	level* m_level;


	//Entity* m_player;
	Entity* m_cat;
	Entity* m_alien;
	Entity* m_dog;
	//Entity* ai;

	HealthComponent* m_healthComponentOne;
	HealthComponent* m_healthComponentTwo;
	HealthComponent* m_healthComponentThree;
	HealthComponent* m_healthComponentFour;
	ControlComponent* m_ctrlComponent;
	PositionComponent* m_posComponent;
	CollisionComponent* CollisionComp;
	ParticleComponent* m_partComponent;

	HealthSystem hs;
	RenderSystem rs;
	AiSystem ais;
	ParticleSystem ps;
	ControlSystem cs;
	CollisionSystem Colls;
	LTexture m_texture, wallTxt;

	PhysicsSystem phs;

	Factory* m_factory;
	std::vector<PowerUp*> m_powerUps;
	//jamie
	double disBetweenAiPlayer = 10000;
	Fuzzy* m_fuzzy;

	int m_timerSpawn;
	const int m_spawnTimeLimit = 2000;
	const int m_numOfPowerUps = 2;

	void rumble();
	void resetCamera();
	int rTimer = 0;
	int SCREEN_WIDTH = 1500;
	int SCREEN_HEIGHT = 900;
	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };


	Entity player;
	Entity ai;

};



#endif // !GAME