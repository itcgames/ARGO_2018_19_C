#pragma once
#include <iostream>
#include <vector>
#include "EntityComponent.h"
#include "SDL.h"
#include "LTexture.h"
#include "Animation.h"
#include "Client.h"
#include "Command.h"
#include "menu.h"

#define MAX_CONTROLLERS 4

class ControlSystem
{
	

public:
	ControlSystem();
	void init();
	void addEntity(Entity e);
	int getEntityIndex(std::string entity);
	void removeEntityByIndex(int i);
	std::vector<std::string> getEntityIds();
	void idle();
	void input(SDL_Event &e, Client & client, GameState & gs, bool & changeReady, int & changeAi);
	void keyUp(SDL_Event & e);
private:
	std::vector<Entity> entities;
	
	ControlComponent * controlComp;
	AnimationComponent *amComp;
	float x = 0;
	float y = 0;
	float speed = 2;
	int windowWidth = 1280;
	int windowHeight = 720;
	bool pressed = false;

	std::string msg; // Message to be sent to the network

	// Controller
	SDL_GameController *ControllerHandles[MAX_CONTROLLERS];

	int bitePoint;

	bool AButton;
	bool BButton;
	bool XButton;
	bool YButton; 
	bool Up;
	bool Down;
	int StickLeftX;

	bool AButtonPrevious;
	bool BButtonPrevious;


	/*
	bool Left;
	bool Right;
	bool Start;
	bool Back;
	bool LeftShoulder;
	bool RightShoulder;
	int StickLeftY;
	int StickRightX;
	int StickRightY;
	int StickLT;
	int StickRT;*/

	Command * stickLeft;
	Command * stickRight;
	Command * buttonA;
	Command * buttonB;
	Command * buttonX;
	Command * buttonY;

};