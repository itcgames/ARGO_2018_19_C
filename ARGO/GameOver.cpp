#include "GameOver.h"

GameOverScreen::GameOverScreen(SDL_Renderer* ren)
{
	if (!m_bg.loadFromFile("assets/img/LobbyBG.png", ren, 1))
	{
		printf("Failed to load gameover background!\n");
	}
	m_bgX = 0;
	m_bgY = 0;

	if (!m_mainMenubtn.loadFromFile("assets/img/MainMenu.png",ren,1))
	{
		printf("Failed to load main menu button");
	}
	m_mainMenuX = 625;
	m_mainMenuY = 850;
	m_mainMenuW = m_mainMenubtn.getWidth();
	m_mainMenuH = m_mainMenubtn.getHeight();

	for (int i = 0; i < 4; i++)
	{
		m_scores.push_back(-1);
		m_scoresIncreasing.push_back(0);
	}
	//Open the font
	m_font = TTF_OpenFont("assets/Fonts/Velekom.ttf", 22);
};

GameOverScreen::~GameOverScreen()
{

};

void GameOverScreen::init()
{
	for (int i = 0; i < 4; i++)
	{
		m_scores[i] = -1;
	}
};

void GameOverScreen::addPlayerScore(int index, int score)
{
	m_scores[index] = score;
}

void GameOverScreen::update()
{
	for (int i = 0; i < m_scores.size(); i++)
	{
		if (m_scores[i] > m_scoresIncreasing[i])
		{
			m_scoresIncreasing[i]++;
		}
	}
};

void GameOverScreen::render(SDL_Renderer * ren)
{
	m_bg.render(m_bgX, m_bgY, ren, 1, 1);

	m_mainMenubtn.render(m_mainMenuX, m_mainMenuY, ren, 1, 1);
	if (m_font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		drawText(ren, std::to_string(m_scoresIncreasing[0]), 20, 50);
		drawText(ren, std::to_string(m_scoresIncreasing[1]), 375, 50);
		drawText(ren, std::to_string(m_scoresIncreasing[2]), 745, 50);
		drawText(ren, std::to_string(m_scoresIncreasing[3]), 1120, 50);
	}
};

void GameOverScreen::drawText(SDL_Renderer * ren, std::string s, int x, int y)
{
	//Render text
	
	SDL_Color textColor = { 255, 255, 255 };
	if (!m_textTexture.loadFromRenderedText(s, textColor, ren, m_font))
	{
		printf("Failed to render text texture!\n");
	}
	m_textTexture.render(x, y, ren, 1, 1);
}