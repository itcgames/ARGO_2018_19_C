#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>

class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path, SDL_Renderer *gRenderer, float scale);

#ifdef _SDL_TTF_H
	//Creates image from font string
	LTexture(string fontpath);
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer *gRenderer);
	TTF_Font *gFont;
#endif

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Renderer *gRenderer = NULL, int stepX = NULL, int stepY = NULL, SDL_Rect* sRect = NULL);

	//Gets image dimensions
	int getWidth();
	int getHeight();
	int getSRect();

private:
	//The actual hardware texture
	SDL_Texture * mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
	float m_scale;

};