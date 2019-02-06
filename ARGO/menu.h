#pragma once
#include <SDL.h>
#include <SDL_image.h>

class MenuScreen
{
public:
	MenuScreen();
	~MenuScreen();

	void update(double dt);
	void render(SDL_Renderer * renderer);
};
