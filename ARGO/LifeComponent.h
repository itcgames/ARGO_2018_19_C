#pragma once
#include <vector>
#include "Component.h"
#include "LTexture.h"
class LifeComponent: public Component
{
	
public:
	LifeComponent(int startLife, int playerID, SDL_Renderer *m_renderer, float scale) : m_lifeval(startLife), m_playerID(playerID) {
	
		initTextures(scale, m_renderer, playerID);

		switch (playerID)
		{
		case 1:
			mPosX = 84;
			break;
		case 2:
			mPosX = 438;
			break;
		case 3:
			mPosX = 792;
			break;
		case 4:
			mPosX = 1146;
			break;
		default:
			break;
		}

		setLifes(startLife);

		mPosY = 912;
		
	};

	/*Data only*/
	int getLife() {
		return m_lifeval;
	}

	void setLifes(int life) {
		m_lifeval= life;

		switch (life)
		{
		case 6:
			m_texture = life3_0txt;
			break;
		case 5:
			m_texture = life2_5txt;
			break;
		case 4:
			m_texture = life2_0txt;
			break;
		case 3:
			m_texture = life1_5txt;
			break;
		case 2:
			m_texture = life1_0txt;
			break;
		case 1:
			m_texture = life0_5txt;
			break;
		case 0:
			m_texture = life0_0txt;
			break;
		default:
			break;
		}

		if (life <= 0)
		{
			m_texture = life0_0txt;
		}
		
	}

	std::string getID()
	{
		return id;
	}

	void initTextures(float scale, SDL_Renderer *m_renderer, int playerID) {


		if (!m_texture.loadFromFile("assets/argot/assets/character/health3_0p" + std::to_string(playerID)+ ".png", m_renderer, scale))
		{
			printf("Failed to load dot texture!\n");

		}
		if (!life3_0txt.loadFromFile("assets/argot/assets/character/health3_0p" + std::to_string(playerID) + ".png", m_renderer, scale))
		{
			printf("Failed to load dot texture!\n");

		}
		if (!life2_5txt.loadFromFile("assets/argot/assets/character/health2_5p" + std::to_string(playerID) + ".png", m_renderer, scale))
		{
			printf("Failed to load dot texture!\n");

		}
		if (!life2_0txt.loadFromFile("assets/argot/assets/character/health2_0p" + std::to_string(playerID) + ".png", m_renderer, scale))
		{
			printf("Failed to load dot texture!\n");

		}
		if (!life1_5txt.loadFromFile("assets/argot/assets/character/health1_5p" + std::to_string(playerID) + ".png", m_renderer, scale))
		{
			printf("Failed to load dot texture!\n");

		}
		if (!life1_0txt.loadFromFile("assets/argot/assets/character/health1_0p" + std::to_string(playerID) + ".png", m_renderer, scale))
		{
			printf("Failed to load dot texture!\n");

		}
		if (!life0_5txt.loadFromFile("assets/argot/assets/character/health0_5p" + std::to_string(playerID) + ".png", m_renderer, scale))
		{
			printf("Failed to load dot texture!\n");

		}
		if (!life0_0txt.loadFromFile("assets/argot/assets/character/health0_0.png", m_renderer, scale))
		{
			printf("Failed to load dot texture!\n");

		}
		
		
	}

	void render(SDL_Renderer *m_renderer) {



		m_texture.render(mPosX, mPosY, m_renderer, 1, 1);

	}

	bool dead = false;
private:
	int m_lifeval;
	int m_playerID;
	float mPosX;
	float mPosY;

	LTexture m_texture;
	LTexture life3_0txt;
	LTexture life2_5txt;
	LTexture life2_0txt;
	LTexture life1_5txt;
	LTexture life1_0txt;
	LTexture life0_5txt;
	LTexture life0_0txt;
	SDL_Rect rect = { 100,100,100,100 };
	std::string id = "Life";
};