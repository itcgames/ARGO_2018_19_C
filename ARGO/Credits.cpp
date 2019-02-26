#include "Credits.h"
#include <fstream>

Credits::Credits(SDL_Renderer *ren)
{

	if (!m_texture.loadFromFile("assets/img/optionsBG.png", ren, 1))
	{
		printf("Failed to load ready texture!\n");
	}

	m_font = TTF_OpenFont("assets/Fonts/Velekom.ttf", 10);

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
	
	if (m_font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//drawText(renderer, "Jamie", 50, 50);
		for (std::vector<int>::size_type i = 0; i != allLines.size(); i++) {
			drawText(renderer, allLines[i], 100, 100 * i);
			
		}
		//drawText(renderer, line, 50, 50);

	}
}
void Credits::read() {

	//write text
	
	std::ifstream IPFile;

	IPFile.open("credits.txt");
	if (IPFile.is_open())
	{
		while (!IPFile.eof())
		{
			getline(IPFile, line);
			allLines.push_back(line);
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

void Credits::drawText(SDL_Renderer * ren, std::string s, int x, int y)
{
	//Render text
	SDL_Color textColor = { 255, 255, 255 };
	if (!m_textTexture.loadFromRenderedText(s, textColor, ren, m_font))
	{
		printf("Failed to render text texture!\n");
	}

	m_textTexture.render(x, y, ren, 1, 1);
}