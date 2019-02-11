#pragma once
#pragma once
#include <SDL.h>
#include <SDL_image.h>

class CreditScreen
{
public:
	CreditScreen();
	~CreditScreen();

	void update(double dt);
	void render(SDL_Renderer * renderer);
};
