#include "Ai.h"
#include <algorithm>
#include <string>
Ai::Ai(int x, int y)
{

	//Initialize the offsets
	mPosX = x;
	mPosY = y;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;


	width = 20;
	height = 20;
}

Ai::~Ai()
{
	gDotTexture.free();
}

void Ai::setPosition(float x, float y)
{
	mPosX = x;
	mPosY = y;

	mCenterX = mPosX + (width / 2);
	mCenterY = mPosY + (height / 2);
}

void Ai::Init(SDL_Renderer *gRenderer)
{
	
	if (!gDotTexture.loadFromFile("dot.bmp", gRenderer))
	{
		printf("Failed to load dot texture!\n");
	}
	
	width = gDotTexture.getWidth();
	height = gDotTexture.getHeight();
}


void Ai::render(SDL_Renderer *gRenderer)
{
	//Show the dot
	gDotTexture.render(mPosX, mPosY, gRenderer);
}


int Ai::GetCenterX()
{
	return mCenterX;
}

int Ai::GetCenterY()
{
	return mCenterY;
}

