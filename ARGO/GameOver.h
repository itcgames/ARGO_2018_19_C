#pragma once
#include <iostream>
#include <SDL_image.h>
#include <vector>
#include <string>
#include <SDL_ttf.h>
#include "LTexture.h"
#include "menu.h"

class GameOverScreen
{
public:
	GameOverScreen(SDL_Renderer* ren);
	~GameOverScreen();
	void init();
	void update();
	void render(SDL_Renderer * ren);
	void addPlayerScore(int index, int score);

private:
	std::vector<int> m_scores;
	std::vector<int> m_scoresIncreasing;
	TTF_Font *m_font;
	LTexture m_textTexture;
	LTexture m_bg;
	LTexture m_mainMenubtn;

	int m_mainMenuX, m_mainMenuY, m_mainMenuW, m_mainMenuH;
	int m_bgX, m_bgY;
	void drawText(SDL_Renderer * ren, std::string s, int x, int y);
};