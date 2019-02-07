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

//Jamie
#include "Particle.h"

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

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Event event;
	bool exit;
	Dot* m_playerDot;


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



};



#endif // !GAME