#pragma once
#include "PowerUp.h"

class Factory
{
public: 
	virtual PowerUp* CreateHealth(SDL_Renderer *m_renderer) = 0;
	virtual PowerUp* CreateSpeed(SDL_Renderer *m_renderer) = 0;
};

class PowerUpFactory : public Factory
{
public:
	PowerUp * CreateHealth(SDL_Renderer *m_renderer)
	{
		return new HealthUp(m_renderer);
	}

	PowerUp* CreateSpeed(SDL_Renderer *m_renderer)
	{
		return new SpeedUp(m_renderer);
	}
};