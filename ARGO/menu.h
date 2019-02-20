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
	// Play button
	LTexture m_playTexture;
	
	// Exit button
	LTexture m_exitTexture;
	int m_playX, m_playY, m_playW, m_playH;
	int m_exitX, m_exitY, m_exitW, m_exitH;


};
