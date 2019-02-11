#include "Particle.h"
#include <algorithm>
#include <string>
Particle::Particle(int x, int y)
{

	//Initialize the offsets
	mPosX = x - 5 + (rand() % 25);
	mPosY = y - 5 + (rand() % 25);

	//Initialize animation
	mLife = rand() % 10;

	//Decide colour of particle
	color = (rand() % 3) + 1;
	
	width = 10;
	height = 10;
}

Particle::~Particle()
{
	gDotTexture.free();
}

void Particle::SetPosition(int x, int y)
{
	mPosX = x;
	mPosY = y;

	mCenterX = mPosX + (width / 2);
	mCenterY = mPosY + (height / 2);
}

void Particle::Init(SDL_Renderer *gRenderer)
{
	//Load red texture
	if (!gRedTexture.loadFromFile("red.bmp", gRenderer))
	{
		printf("Failed to load red texture!\n");
	}

	//Load green texture
	if (!gGreenTexture.loadFromFile("green.bmp", gRenderer))
	{
		printf("Failed to load green texture!\n");
	}

	//Load blue texture
	if (!gBlueTexture.loadFromFile("blue.bmp", gRenderer))
	{
		printf("Failed to load blue texture!\n");
	}

	//Load shimmer texture
	//if (!gShimmerTexture.loadFromFile("shimmer.bmp", gRenderer))
	//{
	//	printf("Failed to load shimmer texture!\n");
	//}

	//Set texture transparency
	gRedTexture.setAlpha(192);
	gGreenTexture.setAlpha(192);
	gBlueTexture.setAlpha(192);
	gShimmerTexture.setAlpha(192);

	width = gDotTexture.getWidth();
	height = gDotTexture.getHeight();

	//std::cout << "part init called" << std::endl;
}


void Particle::render(SDL_Renderer *gRenderer)
{
	//Show the dot
	if (color == 1) {
		gBlueTexture.render(mPosX, mPosY, gRenderer);
	}
	if (color == 2) {
		gRedTexture.render(mPosX, mPosY, gRenderer);
	}
	if (color == 3) {
		gGreenTexture.render(mPosX, mPosY, gRenderer);
	}


	mLife++;
}


int Particle::GetCenterX()
{
	return mCenterX;
}

int Particle::GetCenterY()
{
	return mCenterY;
}

bool Particle::isDead()
{

	return mLife > 30;
}

