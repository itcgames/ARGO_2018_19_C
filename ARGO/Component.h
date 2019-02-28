#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
class Component
{
public:

	virtual ~Component() {}
	virtual std::string getID() = 0;
};