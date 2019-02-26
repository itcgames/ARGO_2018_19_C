#include "Lobby.h"

struct not_digit {
	bool operator()(const char c)
	{
		return c != ' ' && !isdigit(c);
	}
};

std::vector<float> Lobby::msgToPos(std::string s)
{
	not_digit notADigit;

	std::string::iterator end = std::remove_if(s.begin(), s.end(), notADigit);

	std::string all_numbers(s.begin(), end);

	std::stringstream ss(all_numbers);
	std::vector<float> vec;
	int i;
	for (; ss >> i;)
	{
		vec.push_back(i);
	}
	return vec;
}

Lobby::Lobby(SDL_Renderer *ren, Game * game):m_game(game)
{
	//Open the font
	m_font = TTF_OpenFont("assets/Fonts/Amatic-Bold.ttf", 28);


	if (!m_readyTexture.loadFromFile("img/ReadyButton.png", ren, 1))
	{
		printf("Failed to load ready texture!\n");
	}

	m_readyX = 400;
	m_readyY = 800;
	m_readyW = m_readyTexture.getWidth();
	m_readyH = m_readyTexture.getHeight();

	if (!m_backTexture.loadFromFile("img/ReadyButton.png", ren, 1))
	{
		printf("Failed to load ready texture!\n");
	}

	m_backX = 800;
	m_backY = 800;
	m_backW = m_backTexture.getWidth();
	m_backH = m_backTexture.getHeight();

	if (!m_playerTexture.loadFromFile("img/ReadyButton.png", ren, 1))
	{
		printf("Failed to load ready texture!\n");
	}

	if (!m_player2Texture.loadFromFile("img/ReadyButton.png", ren, 1))
	{
		printf("Failed to load ready texture!\n");
	}

	if (!m_player3Texture.loadFromFile("img/ReadyButton.png", ren, 1))
	{
		printf("Failed to load ready texture!\n");
	}

	if (!m_player4Texture.loadFromFile("img/ReadyButton.png", ren, 1))
	{
		printf("Failed to load ready texture!\n");
	}

	for (int i = 0; i < 4; i++)
	{
		m_playerReady.push_back(true);
		m_playerInLobby.push_back(false);
	}

	m_stateTimer = 0;
}


Lobby::~Lobby() {};

void Lobby::init()
{

};



std::string Lobby::sendMsg(int index)
{
	return "Ready: " + std::to_string(m_playerReady[index]) + " L: " + std::to_string(m_playerInLobby[index]);
}

void Lobby::update(int index, int mouseX, int mouseY, GameState & gs)
{
	// On Button click
	// Ready, UnReady

	if (index != 5)
	{
		m_playerInLobby[index] = true;

		for (int i = 0; i < m_playerInLobby.size(); i++)
		{
			if (i != index && !m_playerInLobby[i])
			{
				m_playerReady[i] = true;
			}
		}

		if (m_readyX <= mouseX && m_readyY <= mouseY && m_readyX + m_readyW >= mouseX && m_readyY + m_readyH >= mouseY)
		{
			m_playerReady[index] = !m_playerReady[index];
		}


		if (m_backX <= mouseX && m_backY <= mouseY && m_backX + m_backW >= mouseX && m_backY + m_backH >= mouseY)
		{
			for (int i = 0; i < m_playerReady.size(); i++)
			{
				m_playerReady[i] = false;
			}
			gs = GameState::MainMenu;
			m_playerInLobby[index] = false;
		}
	}

}

void Lobby::changeState(int index, bool state)
{
	m_playerReady[index] = state;
}

void Lobby::inLobby(int index, bool state)
{
	m_playerInLobby[index] = state;
}

bool Lobby::getInLobby(int index)
{
	return m_playerInLobby[index];
}

bool Lobby::everyoneReady(int countdown)
{
	m_countdown = countdown;
	if (!m_playerReady[0])
	{
		return false;
	}
	if (!m_playerReady[1])
	{
		return false;
	}
	if (!m_playerReady[2])
	{
		return false;
	}
	if (!m_playerReady[3])
	{
		return false;
	}

	return true;
}

void Lobby::render(SDL_Renderer * ren)
{
	// Ready button
	m_readyTexture.render(m_readyX, m_readyY, ren, 1, 1);

	//Back button
	m_backTexture.render(m_backX, m_backY, ren, 1, 1);

	// Player one
	if (m_playerReady[0])
	{
		m_playerTexture.render(100, 400, ren, 1, 1);
	}
	// Player two
	if (m_playerReady[1])
	{
		m_player2Texture.render(350, 400, ren, 1, 1);
	}
	// Player three
	if (m_playerReady[2])
	{
		m_player3Texture.render(700, 400, ren, 1, 1);
	}
	// Player four
	if (m_playerReady[3])
	{
		m_player4Texture.render(950, 400, ren, 1, 1);
	}

	if (m_font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		if (m_countdown > 0)
		{
			drawText(ren, std::to_string((200 - m_countdown) / 50), 50, 50);
		}

	}

}

void Lobby::drawText(SDL_Renderer * ren, std::string s, int x, int y)
{
	//Render text
	SDL_Color textColor = { 255, 0, 0 };
	if (!m_textTexture.loadFromRenderedText(s, textColor, ren, m_font))
	{
		printf("Failed to render text texture!\n");

	}

	m_textTexture.render(x, y, ren, 1, 1);
}

void Lobby::updateNetwork(Client * client, int pIndex, std::string s)
{
	if (everyoneReady(m_stateTimer))
	{
		if (m_stateTimer > m_stateTimerLimit)
		{
			m_game->setGameState(GameState::GameScreen);
			if (!getInLobby(0))
			{
				// Player 1 is an Ai
				std::cout << "Player 1 is an AI" << std::endl;
				m_game->playerAI(0, true);
			}

			if (!getInLobby(1))
			{
				// Player 2 is an Ai
				std::cout << "Player 2 is an AI" << std::endl;
				m_game->playerAI(1, true);
			}

			if (!getInLobby(2))
			{
				// Player 3 is an Ai
				std::cout << "Player 3 is an AI" << std::endl;
				m_game->playerAI(2, true);
			}

			if (!getInLobby(3))
			{
				// Player 4 is an Ai
				std::cout << "Player 4 is an AI" << std::endl;
				m_game->playerAI(3, true);
			}

			// Start game
			m_stateTimer = 0;
			//setGameState(GameState::GameScreen);
		}
		else
		{
			m_stateTimer++;
		}
	}
	else
	{
		m_stateTimer = 0;
	}
	
	
	int index = s.find("Lobby");
	if (index >= 0)
	{
		// If you don't have a player index
		if (pIndex == 5)
		{
			// Ask for your index
			std::string msg;
			msg = "What is my Index";
			client->sendMsg(msg);
		}


		bool readyState;

		if ((int)msgToPos(s.substr(index))[1] == 1)
		{
			readyState = true;
		}
		else
		{
			readyState = false;
		}

		bool lobby;
		if ((int)msgToPos(s.substr(index))[2] == 1)
		{
			lobby = true;
		}
		else
		{
			lobby = false;
		}

		// Set other player lobby states
		switch ((int)msgToPos(s.substr(index))[0])
		{
		case 0:
			changeState(0, readyState);
			inLobby(0, lobby);
			if (readyState && lobby)
			{
				m_game->playerAI(0, true);
			}
			break;
		case 1:
			changeState(1, readyState);
			inLobby(1, lobby);
			if (readyState && lobby)
			{
				m_game->playerAI(1, true);
			}
			break;
		case 2:
			changeState(2, readyState);
			inLobby(2, lobby);
			if (readyState && lobby)
			{
				m_game->playerAI(2, true);
			}
			break;
		case 3:
			changeState(3, readyState);
			inLobby(3, lobby);
			if (readyState && lobby)
			{
				m_game->playerAI(3, true);
			}
			break;
		}

	}

	index = s.find("Joining");
	if (index >= 0 || s == "Host")
	{
		int pI = 0;
		if (s != "Host")
		{
			std::string indexString = s.substr(index + 14, 1);
			pI = std::stoi(indexString);
		}
		changeState(pI, false);
		m_game->setPlayer(pI);
	}

	if (pIndex != 5)
	{
		std::string msg;
		msg = "Lobby i: " + std::to_string(pIndex) + " " + sendMsg(pIndex);
		client->sendMsg(msg);
	}


}