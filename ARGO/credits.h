#pragma once
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"

class Credits
{
public:
	Credits(SDL_Renderer * renderer);
	~Credits();

	void update();
	void render(SDL_Renderer * renderer);
private:

	LTexture m_texture;
};
