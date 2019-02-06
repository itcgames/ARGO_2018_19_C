#pragma once
#include <iostream>
#include <string>
#include <SDL.h>

class PowerUp
{
public:
	PowerUp() { m_alive = true; };
	~PowerUp() {};
	virtual void draw(SDL_Renderer *m_renderer) = 0;
	void update() {

		m_x = 200;
		m_y = 200;
		std::cout << "Power Up update: " << std::to_string(m_timer) << std::endl;
		m_timer++;
		if (m_timer >= m_timerLimit)
		{
			m_alive = false;
		}
	};
	int getID() { return m_id; };
	bool getAlive() { return m_alive; };
protected:
	int m_id;
	bool m_alive;
	LTexture m_texture;
	int m_x, m_y;
	int m_timer;
	const int m_timerLimit = 600;

};

class HealthUp : public PowerUp
{
public:
	HealthUp(SDL_Renderer *m_renderer) {
		
		if (!m_texture.loadFromFile("dot.bmp", m_renderer))
		{
			printf("Failed to load dot texture!\n");

		}
		m_timer = 0;
	};
	~HealthUp()
	{
	};
	void draw(SDL_Renderer *m_renderer)
	{
		m_texture.render(m_x, m_y, m_renderer);
	}
};

class SpeedUp : public PowerUp
{
public:
	SpeedUp(SDL_Renderer *m_renderer)
	{
		if (!m_texture.loadFromFile("dot.bmp", m_renderer))
		{
			printf("Failed to load dot texture!\n");

		}
		m_timer = 0;
	};
	~SpeedUp()
	{
	};
	void draw(SDL_Renderer *m_renderer)
	{
		m_texture.render(m_x, m_y, m_renderer);
	}
};

