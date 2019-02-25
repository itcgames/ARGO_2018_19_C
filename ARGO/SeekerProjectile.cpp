#include "SeekerProjectile.h"
#include <algorithm>
#include <string>

Seeker::Seeker(int x, int y, SDL_Renderer* m_renderer)
{

	//Initialize the offsets
	m_posX = x;
	m_posY = y;
	//width = 20;
	//height = 20;

	if (!m_texture.loadFromFile("dotRed.bmp", m_renderer, 1))
	{
		printf("Failed to load dot texture!\n");

	}
}

Seeker::~Seeker()
{
	m_texture.free();
}

void Seeker::setPosition(float x, float y)
{
	m_posX = x; 
	m_posY = y;

}


void Seeker::render(SDL_Renderer *m_renderer)
{
	//Show the dot
	m_texture.render(m_posX, m_posY, m_renderer, 1, 1);
}


bool Seeker::checkCollision(int centerX, int centerY)
{
	//insert square collision
		return false;
	
}

float Seeker::getWidth() {
	return width;
}

float Seeker::getHeight() {
	return height;
}

float Seeker::getPositionX() {
	return m_posX;
}

float Seeker::getPositionY() {
	return m_posY;
}

