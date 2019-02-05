#pragma once
#include <iostream>
#include <sdl.h>
#include <SDL_image.h>
class Component
{
public:

	virtual ~Component() {}
	virtual std::string getID() = 0;
};