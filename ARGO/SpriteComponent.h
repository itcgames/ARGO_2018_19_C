#pragma once
#pragma once
#include <vector>
#include "Component.h"
#include "LTexture.h"
class SpriteComponent : public Component
{

public:
	SpriteComponent(std::string path, float scale , SDL_Renderer *m_renderer): m_scale(scale)
	{

		
		Init(path, scale, m_renderer);
	
		m_width = m_texture.getWidth();
		m_height = m_texture.getHeight();

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

	void animate(float x, float y, float width, float height, float xStep, float yStep, SDL_Renderer *m_renderer) {

		rect.h = height;
		rect.w = width;
		rect.y = y;
		rect.x = x;

		render(m_renderer, rect, xStep, yStep);

	}

	void render(SDL_Renderer *m_renderer, SDL_Rect s_rect, float xStep, float yStep) {



		m_texture.render(mPosX, mPosY, m_renderer,  &s_rect, xStep, yStep);

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

	float getScale() {
		return m_scale;
	}
	
private:
	float m_scale;
	std::string id = "Sprite";
	int mPosX;
	int mPosY; 
	float m_width, m_height;
	LTexture m_texture;
	LTexture m_textureLeft;
	SDL_Rect rect;
	
};