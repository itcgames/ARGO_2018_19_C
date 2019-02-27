#pragma once
#include <iostream>
#include <SDL_image.h>
#include "LTexture.h"
#include <vector>
#include "menu.h"
#include "Level.h"
#include "EntityComponent.h"
#include "CombatSystem.h"
#include "RenderSystem.h"
#include "AISystem.h"
#include "ParticleSystem.h"
#include "ControlSystem.h"
#include "AmmoSystem.h"
#include "CollisionSystem.h"
#include "PhysicsSystem.h"
#include "LifeSystem.h"
#include "Factory.h"
#include <sstream>
#include "Game.h"

class Game;

class GameScreen
{
public:
	GameScreen(SDL_Renderer * ren, Game * game);
	~GameScreen();
	void init(SDL_Renderer * ren, int * pIndex);
	void update(Client * client, float dt, SDL_Renderer * ren);
	void input(SDL_Event * e, Client * client, GameState & gs, bool & changeReady);
	void render(SDL_Renderer * ren, float dt);
	void playerAI(int pIndex, bool ai);
	void updateNetwork(Client * client, std::string msg, SDL_Renderer * ren);
	void setPlayer(int pIndex);

private:
	level* m_level;

	Entity* m_flag;
	ControlComponent* m_ctrlComponent;
	PositionComponent* m_posComponent;
	CollisionComponent* CollisionComp;
	ParticleComponent* m_partComponent;

	CombatSystem comsystem;
	RenderSystem rs;
	AISystem ais;
	ParticleSystem ps;
	ControlSystem cs;
	AmmoSystem ammos;
	CollisionSystem Colls;
	PhysicsSystem phs;
	LifeSystem ls;


	LTexture m_texture, wallTxt;

	double disBetweenAiPlayer = 10000;

	// Power ups
	Factory* m_factory;
	std::vector<PowerUp*> m_powerUps;
	int m_timerSpawn;
	const int m_spawnTimeLimit = 1000;
	const int m_numOfPowerUps = 5;
	void powerUpSpawn(SDL_Renderer * ren, Client * client);

	// Window
	void rumble();
	void resetCamera();
	int rTimer = 0;
	int SCREEN_WIDTH = 1500;
	int SCREEN_HEIGHT = 1000;
	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// Flag
	Entity flag;
	int whoHasFlag();

	// Player
	int * m_playerIndex;
	Entity player;
	Entity player2;
	Entity player3;
	Entity player4;

	// Network
	void sendPUToNetwork(Client * client);
	void sendAiToNetwork(Client * client);
	void updatePlayerNet(std::string s);
	std::vector<float> msgToPos(std::string s);
	
	void getDistance();

	Game * m_game;

	// Countdown
	int m_countdownSec;
	int m_countdownMinute;
	TTF_Font *m_font;
	LTexture m_textTexture;
	void drawText(SDL_Renderer * ren, std::string s, int x, int y);
};