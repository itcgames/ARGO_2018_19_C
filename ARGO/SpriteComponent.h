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
	
	};

	float m_Width = m_texture.getWidth();
	float m_Height = m_texture.getHeight();

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
		return m_Width;
	}

	float getHeight() { return m_Height; }

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