#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"


class optionsScreen
{
public:
	optionsScreen(SDL_Renderer * ren);
	~optionsScreen();
	void init();
	void update();
	void render(SDL_Renderer * renderer);
private:
	//background Texture
	LTexture m_bg;
	
	//keyboard Texture
	LTexture m_keyImg;
	
	//Controller Texture
	LTexture m_ControllerImg;

};