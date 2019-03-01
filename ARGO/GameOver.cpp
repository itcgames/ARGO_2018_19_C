#include "GameOver.h"

GameOverScreen::GameOverScreen(SDL_Renderer* ren):renderer(ren)
{
	if (!m_bg.loadFromFile("assets/argot/assets/art/LobbyBG.png", ren, 1))
	{
		printf("Failed to load gameover background!\n");
	}
	m_bgX = 0;
	m_bgY = 0;

	if (!m_mainMenubtn.loadFromFile("assets/argot/assets/art/MainMenu.png",ren,1))
	{
		printf("Failed to load main menu button");
	}
	m_mainMenuX = 625;
	m_mainMenuY = 875;
	m_mainMenuW = m_mainMenubtn.getWidth();
	m_mainMenuH = m_mainMenubtn.getHeight();



	for (int i = 0; i < 4; i++)
	{
		m_scores.push_back(-1);
		m_scoresIncreasing.push_back(0);
	}

	if (!m_first.loadFromFile("assets/argot/assets/art/first.png", ren, 1))
	{
		printf("error loading first png!\n");
	}
	if (!m_second.loadFromFile("assets/argot/assets/art/second.png", ren, 1))
	{
		printf("error loading third png!\n");
	}
	if (!m_third.loadFromFile("assets/argot/assets/art/third.png", ren, 1))
	{
		printf("error loading third png!\n");
	}
	if (!m_fourth.loadFromFile("assets/argot/assets/art/fourth.png", ren, 1))
	{
		printf("error loading fourth png!\n");
	}

	//Open the font
	m_font = TTF_OpenFont("assets/argot/assets/Fonts/Velekom.ttf", 14);
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
	winnerScore();
};

void GameOverScreen::winnerScore()
{
	m_winnerOrder = m_scores;
	std::sort(m_winnerOrder.rbegin(), m_winnerOrder.rend());

	for (int i = 0; i < m_winnerOrder.size();i++)
	{
		
		if (m_winnerOrder[0] == m_scores[i] && m_scores[i] != 0)
		{
			switch (i) {
			case 0:
				m_firstX = 120;
				m_firstY = 700;
				player1Win = true;
				break;
			case 1:
				player2Win = true;
				m_firstX = 520;
				m_firstY = 700;
				break;
			case 2:
				player3Win = true;
				m_firstX = 870;
				m_firstY = 700;
				break;
			case 3:
				player4Win = true;
				m_firstX = 1250;
				m_firstY = 700;
			}

		}
		if (m_winnerOrder[1] == m_scores[i] && m_scores[i] != 0)
		{
			switch (i) {
			case 0:
				m_secondX = 120;
				m_secondY = 700;
				break;
			case 1:
				m_secondX = 520;
				m_secondY = 700;
				break;
			case 2:
				m_secondX = 870;
				m_secondY = 700;
				break;
			case 3:
				m_secondX = 1250;
				m_secondY = 700;
			}

		}
		if (m_winnerOrder[2] == m_scores[i] && m_scores[i] != 0)
		{
			switch (i) {
			case 0:
				m_thirdX = 120;
				m_thirdY = 700;
				break;
			case 1:
				m_thirdX = 520;
				m_thirdY = 700;
				break;
			case 2:
				m_thirdX = 870;
				m_thirdY = 700;
				break;
			case 3:
				m_thirdX = 1250;
				m_thirdY = 700;
			}

		}
		if (m_winnerOrder[3] == m_scores[i] && m_scores[i] != 0)
		{
			switch (i) {
			case 0:
				m_fourthX = 120;
				m_fourthY = 750;
				break;
			case 1:
				m_fourthX = 520;
				m_fourthY = 750;
				break;
			case 2:
				m_fourthX = 870;
				m_fourthY = 750;
				break;
			case 3:
				m_fourthX = 1250;
				m_fourthY = 750;
			}

		}

		if (player1Win)
		{
			m_player1.loadFromFile("assets/argot/assets/character/lobbyPlayer1.png", renderer,1);
			m_player2.loadFromFile("assets/argot/assets/character/player2Sad.png", renderer, 1);
			m_player3.loadFromFile("assets/argot/assets/character/player3Sad.png", renderer, 1);
			m_player4.loadFromFile("assets/argot/assets/character/player4Sad.png", renderer, 1);
		}
		else if (player2Win)
		{
			m_player1.loadFromFile("assets/argot/assets/character/player1Sad.png", renderer, 1);
			m_player2.loadFromFile("assets/argot/assets/character/lobbyPlayer2.png", renderer, 1);
			m_player3.loadFromFile("assets/argot/assets/character/player3Sad.png", renderer, 1);
			m_player4.loadFromFile("assets/argot/assets/character/player4Sad.png", renderer, 1);
		}
		else if (player3Win)
		{
			m_player1.loadFromFile("assets/argot/assets/character/player1Sad.png", renderer, 1);
			m_player2.loadFromFile("assets/argot/assets/character/player2Sad.png", renderer, 1);
			m_player3.loadFromFile("assets/argot/assets/character/lobbyPlayer3.png", renderer, 1);
			m_player4.loadFromFile("assets/argot/assets/character/player4Sad.png", renderer, 1);
		}
		else if (player4Win)
		{
			m_player1.loadFromFile("assets/argot/assets/character/player1Sad.png", renderer, 1);
			m_player2.loadFromFile("assets/argot/assets/character/player2Sad.png", renderer, 1);
			m_player3.loadFromFile("assets/argot/assets/character/player3Sad.png", renderer, 1);
			m_player4.loadFromFile("assets/argot/assets/character/lobbyPlayer4.png", renderer, 1);
		}
	}
}

void GameOverScreen::render(SDL_Renderer * ren)
{
	m_bg.render(m_bgX, m_bgY, ren, 1, 1);
	m_first.render(m_firstX, m_firstY, ren, 1, 1);
	m_second.render(m_secondX, m_secondY, ren, 1, 1);
	m_third.render(m_thirdX, m_thirdY, ren, 1, 1);
	m_fourth.render(m_fourthX, m_fourthY, ren, 1, 1);
	m_mainMenubtn.render(m_mainMenuX, m_mainMenuY, ren, 1, 1);

	m_player1.render(100, 400, ren, 1, 1);
	m_player2.render(500, 400, ren, 1, 1);
	m_player3.render(850, 400, ren, 1, 1);
	m_player4.render(1250, 400, ren, 1, 1);

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
		drawText(ren,std::string("[A]"), 900, 900);
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