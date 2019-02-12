#pragma once
#pragma once
#include <vector>
#include "Component.h"
#include "LTexture.h"
class SpriteComponent : public Component
{

public:
	SpriteComponent(std::string path, float scale , SDL_Renderer *m_renderer, float xStep, float yStep): m_scale(scale),m_xStep(xStep), m_yStep(yStep)
	{

		
		Init(path, scale, m_renderer);
	
		m_width = getWidth();
		m_height = getHeight();

		rect = { 0,0,0,0 };

	};
	
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

	void animate(float x, float y, float width, float height, SDL_Renderer *m_renderer) {

		rect.h = height;
		rect.w = width;
		rect.y = y;
		rect.x = x;

		render(m_renderer, rect);

	}

	void render(SDL_Renderer *m_renderer, SDL_Rect s_rect) {



		m_texture.render(mPosX, mPosY, m_renderer,  &s_rect, m_xStep, m_yStep);

	}

	std::string getID()
	{
		return id;
	}

	float getWidth()
	{
		return m_texture.getWidth() / m_xStep;
	}

	float getHeight() { 

		return m_texture.getHeight() / m_yStep;
	 }

	LTexture getTexture()
	{
		return m_texture;
	}

	float getScale() {
		return m_scale;
	}
	
private:
	float m_scale;
	float m_xStep;
	float m_yStep;
	std::string id = "Sprite";
	int mPosX;
	int mPosY; 
	float m_width, m_height;
	LTexture m_texture;
	LTexture m_textureLeft;
	SDL_Rect rect;
	
};