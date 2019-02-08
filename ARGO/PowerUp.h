#pragma once
#include <iostream>
#include <string>
#include <SDL.h>

class PowerUp
{
public:
	PowerUp() { 
		m_id = 0;
		m_alive = true;
		m_x = 50.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 1100.0f));
		m_y = 50.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 650.0f));
		m_xSpeed = 0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.0f));
		m_ySpeed = 0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.0f));
		
		switch (rand() % 2)
		{
		case 0:
			m_headLeft = true;
			break;

		case 1:
			m_headLeft = false;
			break;
		}

		switch (rand() % 2)
		{
		case 0:
			m_headUp = true;
			break;

		case 1:
			m_headUp = false;
			break;
		}
	};
	~PowerUp() {};
	virtual void draw(SDL_Renderer *m_renderer) = 0;
	bool pickedUp(float x, float y, float w1, float h1)
	{
		float w = 0.5*(w1 + getWidth());
		float h = 0.5*(h1 + getHeight());
		float dx = (x + (w1 / 2)) - (m_x + (getWidth() / 2));
		float dy = (y + (h1 / 2)) - (m_y + (getHeight() / 2));
		if (abs(dx) <= w && abs(dy) <= h)
		{
			m_alive = false;
			return true;
		}
		return false;
	};
	void obstacleCollision(float x, float y, float w1, float h1)
	{
		float w = 0.5*(w1 + getWidth());
		float h = 0.5*(h1 + getHeight());
		float dx = (x + (w1 / 2)) - (m_x + (getWidth() / 2));
		float dy = (y + (h1 / 2)) - (m_y + (getHeight() / 2));
		if (abs(dx) <= w && abs(dy) <= h)
		{
			float wy = w * dy;
			float hx = h * dx;

			if (wy > hx)
			{
				if (wy > -hx)
				{
					//top
					m_headUp = false;
				}
				else if (wy < -hx)
				{
					//left
					m_headLeft = false;
				}

			}
			if (wy < hx)
			{
				if (wy > -hx)
				{
					//Right 
					m_headLeft = true;
				}
				else if (wy < -hx)
				{
					//Bottom
					m_headUp = true;
				}
			}
		}
	};
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
	const int m_timerLimit = 1800;

};

class HealthUp : public PowerUp
{
public:
	HealthUp(SDL_Renderer *m_renderer) {
		m_id = 1;
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
		m_id = 2;
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

