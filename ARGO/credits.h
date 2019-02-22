#pragma once
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
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
	int timeLimit = 500;

	std::string line;

private:

	LTexture m_texture;

	std::vector<std::string> allLines;
	TTF_Font *m_font;
	LTexture m_textTexture;
	void drawText(SDL_Renderer * ren, std::string s, int x, int y);
};
