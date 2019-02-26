#include "menu.h"

MenuScreen::MenuScreen(SDL_Renderer * ren)
{
	if (!m_bg.loadFromFile("assets/img/bg.png", ren, 1))
	{
		printf("Failed to load BG texture!\n");
	}
	m_bgX = 0;
	m_bgY = 0;
	m_bgW = m_bg.getWidth();
	m_bgH = m_bg.getHeight();

	if (m_title.loadFromFile("assets/img/title.png", ren, 1))
	{
		printf("Error loading title Image!\n");
	}
	m_titleX = 100;
	m_titleY = 0;

	if (!m_playTexture.loadFromFile("assets/img/play.png",ren,1))
	{
		printf("Failed to load play texture!\n");
	}
	m_playX = 50;
	m_playY = 200;
	m_playW = m_playTexture.getWidth();
	m_playH = m_playTexture.getHeight();

	if (!m_options.loadFromFile("assets/img/options.png", ren, 1))
	{
		printf("Failed to load options texture!\n");
	}
	m_optionsX = 550;
	m_optionsY = 200;
	m_optionsW = m_options.getWidth();
	m_optionsH = m_options.getHeight();

	if (!m_Credits.loadFromFile("assets/img/Credits.png", ren, 1))
	{
		printf("Failed to load Credits texture!\n");
	}
	m_CreditsX = 1000;
	m_CreditsY = 200;
	m_CreditsW = m_Credits.getWidth();
	m_CreditsH = m_Credits.getHeight();
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
	
	if (m_CreditsX <= mouseX && m_CreditsY <= mouseY && m_CreditsX + m_CreditsW >= mouseX && m_CreditsY + m_CreditsY >= mouseY)
	{
		gs = GameState::Credits;
	}

	if (m_optionsX <= mouseX && m_optionsY <= mouseY && m_optionsX + m_optionsW > mouseX && m_optionsY + m_optionsH >= mouseY)
	{
		gs = GameState::Options;
	}
}


void MenuScreen::render(SDL_Renderer * renderer)
{
	//Background Image
	m_bg.render(m_bgX, m_bgY, renderer, 1, 1);

	//Title Image
	m_title.render(m_titleX, m_titleY, renderer, 1, 1);

	// Play button
	m_playTexture.render(m_playX, m_playY, renderer, 1, 1);

	// Credits button
	m_Credits.render(m_CreditsX, m_CreditsY, renderer, 1, 1);

	//Options button
	m_options.render(m_optionsX, m_optionsY, renderer, 1, 1);

}