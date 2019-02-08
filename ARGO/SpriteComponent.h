#pragma once
#pragma once
#include <vector>
#include "Component.h"
#include "LTexture.h"
class SpriteComponent : public Component
{

public:
	SpriteComponent(std::string path, float scale , SDL_Renderer *m_renderer)
	{
		
		Init(path, scale, m_renderer);
	
	
	};
	float m_scale;
	void Init(std::string path,  float scale, SDL_Renderer *gRenderer )
	{
		
		m_scale = scale;
		
		if (!m_texture.loadFromFile(path, gRenderer, m_scale))
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

	float getScale() {
		return m_scale;
	}
	
private:
	
	std::string id = "Sprite";
	int mPosX;
	int mPosY;
	LTexture m_texture;
	LTexture m_textureLeft;
	
};