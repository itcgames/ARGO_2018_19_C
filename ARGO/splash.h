#pragma once
#pragma once
#include <SDL.h>
#include <SDL_image.h>

class SplashScreen
{
public:
	SplashScreen();
	~SplashScreen();

	void update(double dt);
	void render(SDL_Renderer * renderer);
};
