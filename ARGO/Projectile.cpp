#include "Projectile.h"
#include <algorithm>
#include <string>
Projectile::Projectile(int x, int y, SDL_Renderer* m_renderer)
{

	//Initialize the offsets
	m_posX = x;
	m_posY = y;

	//width = 20;
	//height = 20;

	if (!m_texture.loadFromFile("dot1.bmp", m_renderer, 1))
	{
		printf("Failed to load dot texture!\n");

	}
}

Projectile::~Projectile()
{
	m_texture.free();
}

void Projectile::setPosition(float x, float y)
{
	m_posX = x; 
	m_posY = y;

}


void Projectile::render(SDL_Renderer *m_renderer)
{
	//Show the dot
	m_texture.render(m_posX, m_posY, m_renderer,  1, 1);
}


bool Projectile::checkCollision(int centerX, int centerY)
{
	//insert square collision
		return false;
	
}

float Projectile::getWidth() {
	return width;
}

float Projectile::getHeight() {
	return height;
}

float Projectile::getPositionX() {
	return m_posX;
}

float Projectile::getPositionY() {
	return m_posY;
}