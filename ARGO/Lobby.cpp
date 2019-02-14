#include "Lobby.h"

Lobby::Lobby(SDL_Renderer *ren)
{
	// need Render

	if (!m_readyTexture.loadFromFile("img/ReadyButton.png", ren, 1))
	{
		printf("Failed to load ready texture!\n");
	}

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
		m_playerReady.push_back(false);
	}

	m_readyX = 600;
	m_readyY = 800;
	m_readyW = m_readyTexture.getWidth();
	m_readyH = m_readyTexture.getHeight();
}


Lobby::~Lobby() {};

void Lobby::init()
{

};

std::string Lobby::sendMsg(int index)
{
	return "Ready: " + std::to_string(m_playerReady[index]);
}

void Lobby::update(int index, int mouseX, int mouseY)
{
	// On Button click
	// Ready, UnReady

	if (index != 5)
	{
		if (m_readyX <= mouseX && m_readyY <= mouseY && m_readyX + m_readyW >= mouseX && m_readyY + m_readyH >= mouseY)
		{
			m_playerReady[index] = !m_playerReady[index];
		}
	}

}

void Lobby::changeState(int index, bool state)
{
	m_playerReady[index] = state;
}

bool Lobby::everyoneReady()
{
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
	m_readyTexture.render(m_readyX, m_readyY, ren, NULL, 1, 1);
	// Player one
	if (m_playerReady[0])
	{
		m_playerTexture.render(100, 400, ren, NULL, 1, 1);
	}
	// Player two
	if (m_playerReady[1])
	{
		m_player2Texture.render(350, 400, ren, NULL, 1, 1);
	}
	// Player three
	if (m_playerReady[2])
	{
		m_player3Texture.render(700, 400, ren, NULL, 1, 1);
	}
	// Player four
	if (m_playerReady[3])
	{
		m_player4Texture.render(950, 400, ren, NULL, 1, 1);
	}

}
