#pragma once
#include "LTexture.h"
#include <SDL.h>
#include <string>
#include <algorithm>
#include <iostream>

class Particle
{
public:
	//The dimensions of the dot
	static const int PART_WIDTH = 20;
	static const int PART_HEIGHT = 20;

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 1;

	Particle() {};
	//Initializes the variables
	Particle(int x, int y);
	~Particle();

	void Init(SDL_Renderer *gRenderer);

	//Shows the dot on the screen
	void render(SDL_Renderer *gRenderer);

	int GetCenterX();
	int GetCenterY();

	void SetPosition(int x, int y);

	bool isDead();

private:

	//The X and Y offsets of the dot
	int mPosX, mPosY;

	int width, height;

	int mLife = 0;

	int mCenterX, mCenterY;

	int color = 0;

	//The velocity of the dot
	int mVelX, mVelY;
	LTexture *mTexture;

	LTexture gDotTexture;
	LTexture gGreenTexture;
	LTexture gRedTexture;
	LTexture gShimmerTexture;
	LTexture gBlueTexture;

};