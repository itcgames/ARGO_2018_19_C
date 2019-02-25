#include "menu.h"

MenuScreen::MenuScreen(SDL_Renderer * ren)
{
	if (!m_playTexture.loadFromFile("img/ReadyButton.png", ren, 1))
	{
		printf("Failed to load ready texture!\n");
	}
	m_playX = 600;
	m_playY = 300;
	m_playW = m_playTexture.getWidth();
	m_playH = m_playTexture.getHeight();

	if (!m_exitTexture.loadFromFile("img/ReadyButton.png", ren, 1))
	{
		printf("Failed to load ready texture!\n");
	}
	m_exitX = 600;
	m_exitY = 700;
	m_exitW = m_exitTexture.getWidth();
	m_exitH = m_exitTexture.getHeight();
}


MenuScreen::~MenuScreen()
{
}

void MenuScreen::init()
{

}

void MenuScreen::update(int mouseX, int mouseY, GameState & gs)
{
	if (m_playX <= mouseX && m_playY <= mouseY && m_playX + m_playW >= mouseX && m_playY + m_playH >= mouseY)
	{
		gs = GameState::Lobby;
	}
	
	if (m_exitX <= mouseX && m_exitY <= mouseY && m_exitX + m_exitW >= mouseX && m_exitY + m_exitH >= mouseY)
	{
		gs = GameState::Credits;
	}
}


void MenuScreen::render(SDL_Renderer * renderer)
{

	// Play button
	m_playTexture.render(m_playX, m_playY, renderer, 1, 1);

	// Exit button
	m_exitTexture.render(m_exitX, m_exitY, renderer, 1, 1);
}