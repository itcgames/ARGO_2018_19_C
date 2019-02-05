#pragma once
#pragma once
#include <vector>
#include "Component.h"
#include "LTexture.h"
class SpriteComponent : public Component
{

public:
	SpriteComponent(LTexture texture, SDL_Renderer *m_renderer) : m_texture(texture)
	{
		
		////SDL_Texture* texture = IMG_LoadTexture(m_renderer, file.c_str());

		//if (!m_texture.loadFromFile("dot.bmp", m_renderer))
		//{
		//	printf("Failed to load dot texture!\n");

		//}
	
	
	};

	void setPosition(int posX, int posY) {

		mPosX = posX;
		mPosY = posY;

	}
	void render(SDL_Renderer *m_renderer) {

		m_texture.render(mPosX, mPosY, m_renderer);
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
};