#pragma once
#include <iostream>
#include <string>
#include <SDL.h>

class PowerUp
{
public:
	PowerUp() { 
		m_alive = true;
		m_x = 200;
		m_y = 200;
		m_xSpeed = 1.0f;
		m_ySpeed = 1.0f;
	};
	~PowerUp() {};
	virtual void draw(SDL_Renderer *m_renderer) = 0;
	void update() {
		//std::cout << "Timer: " << std::to_string(m_timer) << std::endl;
		if (m_headLeft)
		{
			moveLeft();
		}
		else
		{
			moveRight();
		}
		
		if (m_headUp)
		{
			moveUp();
		}
		else
		{
			moveDown();
		}
		
		m_timer++;
		if (m_timer >= m_timerLimit)
		{
			m_alive = false;
		}
	};
	void moveUp() 
	{ 
		m_y -= m_ySpeed; 
		if (m_y <= 0)
		{
			m_ySpeed = 0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.0f));
			m_headUp = false;
		}
	};
	void moveDown() 
	{ 
		m_y += m_ySpeed; 
		if (m_y + getHeight() >= 700)
		{
			m_ySpeed = 0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.0f));
			m_headUp = true;
		}
	};
	void moveLeft() 
	{ 
		m_x -= m_xSpeed; 
		if (m_x <= 0)
		{
			m_xSpeed = 0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.0f));
			m_headLeft = false;
		}
	};
	void moveRight()
	{
		m_x += m_xSpeed; 
		if (m_x + m_texture.getWidth() >= 1200)
		{
			m_xSpeed = 0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.0f));
			m_headLeft = true;
		}
	};
	int getID() { return m_id; };
	bool getAlive() { return m_alive; };
	float getX() { return m_x; };
	float getY() { return m_y; };
	int getWidth() { return m_texture.getWidth(); };
	int getHeight() { return m_texture.getHeight(); };

protected:
	bool m_headLeft;
	bool m_headUp;
	int m_id;
	bool m_alive;
	LTexture m_texture;
	float m_xSpeed, m_ySpeed;
	float m_x, m_y;
	int m_timer;
	const int m_timerLimit = 1200;

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

