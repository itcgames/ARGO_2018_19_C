#pragma once
#include <iostream>
#include <vector>
#include "EntityComponent.h"
#include "SDL.h"
#include "LTexture.h"

#include "Animation.h"
class ControlSystem
{
	

public:
	ControlSystem();
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
};