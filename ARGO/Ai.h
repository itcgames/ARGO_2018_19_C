#pragma once
#include "LTexture.h"
#include <SDL.h>
#include <string>
#include <algorithm>
#include <iostream>

class Ai
{
public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 1;

	Ai() {};
	//Initializes the variables
	Ai(int x, int y);
	~Ai();

	void Init(SDL_Renderer *gRenderer);
	//Takes key presses and adjusts the dot's velocity


	//Shows the dot on the screen
	void render(SDL_Renderer *gRenderer);


	//bool Checkcollision(int centerX, int centerY);


	int GetCenterX();
	int GetCenterY();

	void setPosition(float x, float y);

private:

	//The X and Y offsets of the dot
	int mPosX, mPosY;

	int width, height;

	int mCenterX, mCenterY;
	//The velocity of the dot
	int mVelX, mVelY;

	LTexture gDotTexture;


};