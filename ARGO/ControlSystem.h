#pragma once
#include <iostream>
#include <vector>
#include "EntityComponent.h"
#include "SDL.h"
#include "LTexture.h"
#include "Animation.h"

#define MAX_CONTROLLERS 4

class ControlSystem
{
	

public:
	ControlSystem();
	void init();
	void addEntity(Entity e);
	void idle();
	void input(SDL_Event & e);
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

	// Controller
	SDL_GameController *ControllerHandles[MAX_CONTROLLERS];

	int bitePoint;

	bool AButton;
	bool BButton;
	bool XButton;
	bool YButton;
	bool Up;
	bool Down;
	bool Left;
	bool Right;
	bool Start;
	bool Back;
	bool LeftShoulder;
	bool RightShoulder;
	int StickLeftX;
	int StickLeftY;
	int StickRightX;
	int StickRightY;
	int StickLT;
	int StickRT;

	void(*buttonUp_)();
	void(*buttonDown_)();
	void(*buttonRight_)();
	void(*buttonLeft_)();
	void(*buttonLB_)();
	void(*buttonRB_)();
	void(*buttonLT_)();
	void(*buttonRT_)();
	void(*buttonStart_)();
	void(*buttonBack_)();
	void(*buttonRSX_)(int);
	void(*buttonRSY_)(int);
	void(*buttonLSX_)(int);
	void(*buttonLSY_)(int);

};