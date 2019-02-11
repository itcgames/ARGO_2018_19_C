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
		m_width = m_texture.getWidth();
		m_height = m_texture.getHeight();
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

	float getWidth()
	{
		return m_width;
	}

	float getHeight() { return m_height; }

	LTexture getTexture()
	{
		return m_texture;
	}
	
private:
	
	std::string id = "Sprite";
	int mPosX;
	int mPosY; 
	float m_width, m_height;
	LTexture m_texture;
};