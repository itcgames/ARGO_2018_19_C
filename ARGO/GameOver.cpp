#include "GameOver.h"

GameOverScreen::GameOverScreen()
{
	for (int i = 0; i < 4; i++)
	{
		m_scores.push_back(-1);
		m_scoresIncreasing.push_back(0);
	}
	//Open the font
	m_font = TTF_OpenFont("assets/Fonts/Amatic-Bold.ttf", 28);

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

	if (m_font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		drawText(ren, std::to_string(m_scoresIncreasing[0]), 50, 50);
		drawText(ren, std::to_string(m_scoresIncreasing[1]), 250, 50);
		drawText(ren, std::to_string(m_scoresIncreasing[2]), 550, 50);
		drawText(ren, std::to_string(m_scoresIncreasing[3]), 850, 50);
	}
};

void GameOverScreen::drawText(SDL_Renderer * ren, std::string s, int x, int y)
{
	//Render text
	SDL_Color textColor = { 255, 0, 0 };
	if (!m_textTexture.loadFromRenderedText(s, textColor, ren, m_font))
	{
		printf("Failed to render text texture!\n");

	}

	m_textTexture.render(x, y, ren, 1, 1);
}