#pragma once
#include "AiComponent.h"
#include "SDL.h"
#include <iostream>

class AIState
{
public:
	virtual void goToFlag(AiComponent* ai)
	{
		std::cout << "State::goToFlag" << std::endl;
	}
	virtual void goToNode(AiComponent* ai)
	{
		std::cout << "State::goToNode" << std::endl;
	}

	virtual void goToPowerUp(AiComponent* ai)
	{
		std::cout << "State::goToPowerUp" << std::endl;

	}
};