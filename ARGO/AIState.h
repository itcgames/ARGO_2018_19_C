#pragma once
#include "AiComponent.h"
#include "SDL.h"
#include <iostream>

class AIState
{
public:
	virtual void goToFlag(AiComponent* nf)
	{
		std::cout << "State::goToFlag" << std::endl;
	}
	virtual void goToNode(AiComponent* nf)
	{
		std::cout << "State::goToNode" << std::endl;
	}

	virtual void goToPowerUp(AiComponent* nf)
	{
		std::cout << "State::goToPowerUp" << std::endl;

	}
};