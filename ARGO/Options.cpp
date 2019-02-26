#include "Options.h"

optionsScreen::optionsScreen(SDL_Renderer * renderer):m_renderer(renderer)
{
	if (!m_bg.loadFromFile("assets/img/optionsBG.png",renderer,1))
	{
		printf("Error loading options BG Image!\n");
	}
	m_bgX = 0;
	m_bgY = 0;

	if (!m_backButton.loadFromFile("assets/img/backButton.png",renderer,1))
	{
		printf("Error loading back button!\n");
	}
	m_backX = 0;
	m_backY = 0;
	m_backW = m_backButton.getWidth();
	m_backH = m_backButton.getHeight();

	if (!m_SFXSpeaker.loadFromFile("assets/img/SFXOn.png",renderer,1))
	{
		printf("Error loading SFX speaker image!\n");
	}
	m_sfxX = 200;
	m_sfxY = 100;
	m_sfxW = m_SFXSpeaker.getWidth();
	m_sfxH = m_SFXSpeaker.getHeight();

	if (m_SoundSpeaker.loadFromFile("assets/img/musicOn.png", renderer, 1))
	{
		printf("Error loading SFX speaker image!\n");
	}
	m_soundX = 800;
	m_soundY = 100;
	m_soundW = m_SoundSpeaker.getWidth();
	m_soundH = m_SoundSpeaker.getHeight();

	if (!m_ControllerImg.loadFromFile("assets/img/controller.png", renderer, 1))
	{
		printf("Error loading controller Image!\n");
	}
	m_controllerX = 50;
	m_controllerY = 500;
}

optionsScreen::~optionsScreen() {};

void optionsScreen::update(int mouseX, int mouseY, GameState & gs)
{
	if (m_backX <= mouseX && m_backY <= mouseY && m_backX + m_backW >= mouseX && m_backY + m_backH >= mouseY)
	{
		gs = GameState::MainMenu;
	}

	if (m_sfxX <= mouseX && m_sfxY <= mouseY && m_sfxX + m_sfxW >= mouseX && m_sfxY + m_sfxH >= mouseY)
	{
		if (!m_muteSFX)
		{
			AudioManager::Instance()->muteSFX(-10);
			m_SFXSpeaker.loadFromFile("assets/img/SFXOff.png",m_renderer,1);
			m_muteSFX = true;
		}
		else if (m_muteSFX)
		{
			AudioManager::Instance()->unmuteSFX(0);
			m_SFXSpeaker.loadFromFile("assets/img/SFXOn.png", m_renderer, 1);
			m_muteSFX = false;
		}
	}

	if (m_soundX <= mouseX && m_soundY <= mouseY && m_soundX + m_soundW > mouseX && m_soundY + m_soundH >= mouseY)
	{
		if (!m_muteSound)
		{
			AudioManager::Instance()->PauseMusic();
			m_SoundSpeaker.loadFromFile("assets/img/musicOFF.png", m_renderer, 1);
			m_muteSound = true;
		}
		else if (m_muteSound)
		{
			AudioManager::Instance()->ResumeMusic();
			m_SoundSpeaker.loadFromFile("assets/img/musicOn.png", m_renderer, 1);
			m_muteSound = false;
		}
	}
}

void optionsScreen::render(SDL_Renderer * renderer)
{
	m_bg.render(m_bgX, m_bgY, renderer, 1, 1);
	m_backButton.render(m_backX, m_backY, renderer, 1, 1);
	m_SFXSpeaker.render(m_sfxX, m_sfxY, renderer, 1, 1);
	m_SoundSpeaker.render(m_soundX, m_soundY, renderer, 1, 1);
	m_ControllerImg.render(m_controllerX, m_controllerY, renderer, 1, 1);
}