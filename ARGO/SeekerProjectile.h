#pragma once
#include "LTexture.h"
#include <SDL.h>
#include <string>
#include <algorithm>
#include <iostream>

class Seeker
{
public:

	Seeker() {};
	//Initializes the variables
	Seeker(int x, int y, SDL_Renderer *m_renderer);
	~Seeker();

	//Shows the projectile on the screen
	void render(SDL_Renderer *m_renderer);
	//set position
	void setPosition(float x, float y);
	//check player collision
	bool checkCollision(int centerX, int centerY);

	int maxProjectiles = 0;

	float getWidth();

	float getHeight();

	float getPositionX();

	float getPositionY();

private:

	//The X and Y offsets of the dot
	int m_posX, m_posY;

	//int mCenterX, mCenterY;

	//The velocity of the dot
	//int mVelX, mVelY;

	float width = 20;
	float height = 20;

	LTexture m_texture;

};