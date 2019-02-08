#pragma once
#pragma once
#include <vector>
#include "Component.h"
#include "LTexture.h"
class SpriteComponent : public Component
{

public:
	SpriteComponent(SDL_Renderer *m_renderer) 
	{
		
		Init(m_renderer);
	
	
	};

	void Init(SDL_Renderer *gRenderer)
	{
		
		
		
		if (!m_texture.loadFromFile("img/playerSheet.png", gRenderer))
		{
			printf("Failed to load dot texture!\n");

		}
	
		
	}

	void setPosition(int posX, int posY) {

		mPosX = posX;
		mPosY = posY;

	}
	void render(SDL_Renderer *m_renderer, SDL_Rect s_rect) {

		m_texture.render(mPosX, mPosY, m_renderer, &s_rect);
	}

	std::string getID()
	{
		return id;
	}
	LTexture getTexture()
	{
		return m_texture;
	}
	
private:
	
	std::string id = "Sprite";
	int mPosX;
	int mPosY;
	LTexture m_texture;
	LTexture m_textureLeft;
};