#include "Credits.h"

Credits::Credits(SDL_Renderer *ren)
{

	if (!m_texture.loadFromFile("img/ReadyButton.png", ren, 1))
	{
		printf("Failed to load ready texture!\n");
	}

}


Credits::~Credits() {};


void Credits::update()
{
	//check if player has pressed any button

	//change screen to main menu
	

}
//
//void Credits::changeState(int index, bool state)
//{
//	m_playerReady[index] = state;
//}


void Credits::render(SDL_Renderer * renderer)
{
	m_texture.render(0, 0, renderer, 1, 1);
	

}
