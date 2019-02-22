#include "Lobby.h"

Lobby::Lobby(SDL_Renderer *ren)
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