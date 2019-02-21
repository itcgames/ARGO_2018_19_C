#pragma once
#include "PowerUp.h"

class Factory
{
public: 
	virtual PowerUp* CreateHealth(SDL_Renderer *m_renderer) = 0;
	virtual PowerUp* CreateSpeed(SDL_Renderer *m_renderer) = 0;
	virtual PowerUp* CreateAmmo(SDL_Renderer *m_renderer) = 0;
	virtual PowerUp* CreateSeekerAmmo(SDL_Renderer *m_renderer) = 0;
	virtual PowerUp* CreateReset(SDL_Renderer *m_renderer) = 0;
	virtual PowerUp* CreateInvincible(SDL_Renderer *m_renderer) = 0;
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

	PowerUp* CreateAmmo(SDL_Renderer *m_renderer)
	{
		return new AmmoUp(m_renderer);
	}

	PowerUp* CreateSeekerAmmo(SDL_Renderer *m_renderer)
	{
		return new SeekerAmmoUp(m_renderer);
	}

	PowerUp* CreateReset(SDL_Renderer *m_renderer)
	{
		return new ResetUp(m_renderer);
	}

	PowerUp* CreateInvincible(SDL_Renderer *m_renderer)
	{
		return new NoDamage(m_renderer);
	}
};