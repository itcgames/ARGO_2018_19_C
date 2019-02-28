#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"

enum class
	GameState
{
	None,
	License,
	Splash,
	MainMenu,
	Lobby,
	GameScreen,
	GameOverScreen,
	CoopScreen,
	Options,
	Credits,
	Help
};

class MenuScreen
{
public:
	MenuScreen(SDL_Renderer * ren);
	~MenuScreen();
	void init();
	void update(int mouseX, int mouseY, GameState & gs);
	void render(SDL_Renderer * renderer);

private:
	//Title button
	LTexture m_title;

	// Play button
	LTexture m_playTexture;
	
	// Exit button
	LTexture m_Credits;;

	//background Image
	LTexture m_bg;

	//Options image
	LTexture m_options;

	//Cursor Image
	LTexture m_cursor;

	int m_playX, m_playY, m_playW, m_playH;
	int m_CreditsX, m_CreditsY, m_CreditsW, m_CreditsH;
	int m_bgX, m_bgY, m_bgW, m_bgH;
	int m_cursorX, m_cursorY, m_cursorW, m_cursorH;
	int m_optionsX, m_optionsY, m_optionsW, m_optionsH;
	int m_titleX, m_titleY;
};
