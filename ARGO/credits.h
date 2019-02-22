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
	void read();
	bool endCredits();

	int timer = 0;
	int timeLimit = 300;
private:

	LTexture m_texture;
};
