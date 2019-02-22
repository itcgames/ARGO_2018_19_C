#include "Credits.h"
#include <fstream>

Credits::Credits(SDL_Renderer *ren)
{

	if (!m_texture.loadFromFile("Background_1.png", ren, 1))
	{
		printf("Failed to load ready texture!\n");
	}

	read();

}


Credits::~Credits() {};


void Credits::update()
{
	endCredits();
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
void Credits::read() {

	std::string line;
	std::ifstream IPFile;

	IPFile.open("credits.txt");
	if (IPFile.is_open())
	{
		while (!IPFile.eof())
		{
			getline(IPFile, line);

		}
		IPFile.close();
	}
}


bool Credits::endCredits()
{
	timer++;
	if (timer > timeLimit) {
		timer = 0;
		return true;
	}

	return false;
}