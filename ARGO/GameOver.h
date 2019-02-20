#pragma once
#include <iostream>
#include <SDL_image.h>
#include <vector>
#include <string>
#include <SDL_ttf.h>
#include "LTexture.h"

class GameOverScreen
{
public:
	GameOverScreen();
	~GameOverScreen();
	void init();
	void update();
	void render(SDL_Renderer * ren);

private:
	std::vector<int> m_scores;
	std::vector<int> m_scoresIncreasing;
	TTF_Font *m_font;
	LTexture m_textTexture;
	void drawText(SDL_Renderer * ren, std::string s, int x, int y);
};