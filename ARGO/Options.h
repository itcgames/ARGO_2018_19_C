#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "EntityComponent.h"
#include "LTexture.h"
#include "menu.h"

class optionsScreen
{
public:
	optionsScreen(SDL_Renderer * ren);
	~optionsScreen();
	void init();
	void update(int mouseX, int mouseY, GameState & gs);
	void render(SDL_Renderer * renderer);
private:
	//background Texture
	LTexture m_bg;

	//SFX Texture
	LTexture m_SFXSpeaker;

	//Sound Texture
	LTexture m_SoundSpeaker;
	
	//Back To menu
	LTexture m_backButton;

	//keyboard Texture
	LTexture m_keyImg;
	
	//Controller Texture
	LTexture m_ControllerImg;

	SDL_Renderer * m_renderer;

	bool m_muteSFX, m_muteSound;
	ControlComponent* cc;
	int m_bgX, m_bgY;
	int m_controllerX, m_controllerY;
	int m_keysX, m_keysY;
	int m_sfxX, m_sfxY, m_sfxW, m_sfxH;
	int m_soundX, m_soundY, m_soundW, m_soundH;
	int m_backX, m_backY, m_backW, m_backH;
};