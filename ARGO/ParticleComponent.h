#pragma once
#include <vector>
#include "Component.h"
#include "Particle.h"
class ParticleComponent : public Component
{

public:
	ParticleComponent(float posX, float posY, SDL_Renderer *m_renderer) : positionX(posX), positionY(posY) {};


	Particle* particles[10];

	/*Data only*/
	float getPositionX() {
		return positionX;
	}

	float getPositionY() {
		return positionY;
	}



	void setPosition(float x, float y) {
		this->positionX = x;
		this->positionY = y;
	}

	float getParticles() {
		return totalParticles;
	}

	std::string getID()
	{
		return id;
	}

	void render(SDL_Renderer *m_renderer) {
	
		for (int i = 0; i < totalParticles; ++i)
		{
			//place new particle
			particles[i]->render(m_renderer);
		}
	}

	

private:
	float positionX;
	float positionY;
	std::string  id = "Particle";
	const int totalParticles = 10;
	LTexture m_texture;

	
};