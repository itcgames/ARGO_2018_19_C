#pragma once
#include <iostream>
#include <SDL_image.h>
#include <vector>
#include <string>
#include <SDL_ttf.h>
#include "LTexture.h"
#include <algorithm>
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
	void winnerScore();

private:

	bool draw = false;

	std::vector<int>m_winnerOrder;
	std::vector<int> m_scores;
	std::vector<int> m_scoresIncreasing;
	TTF_Font *m_font;
	LTexture m_textTexture;
	LTexture m_bg;
	LTexture m_mainMenubtn;
	LTexture m_first, m_second, m_third, m_fourth;
	bool player1Win = false, player2Win = false, player3Win = false, player4Win = false;

	LTexture m_player1, player1sad, player1Display;
	LTexture m_player2;
	LTexture m_player3;
	LTexture m_player4;
	int m_currentHighest;
	int m_mainMenuX, m_mainMenuY, m_mainMenuW, m_mainMenuH;
	int m_firstX = -500, m_firstY, m_secondX=-500, m_secondY, m_thirdX=-500, m_thirdY, m_fourthX=-500, m_fourthY;
	int m_bgX, m_bgY;
	void drawText(SDL_Renderer * ren, std::string s, int x, int y);
	SDL_Renderer * renderer;
};