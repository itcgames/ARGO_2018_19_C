#pragma once
#include "NoFlag.h"
#include "SDL.h"
#include <iostream>

class AIState
{
public:
	virtual void goToFlag(NoFlag* nf)
	{
		std::cout << "State::goToFlag" << std::endl;
	}
	virtual void goToNode(NoFlag* nf)
	{
		std::cout << "State::goToNode" << std::endl;
	}

	virtual void goToPowerUp(NoFlag* nf)
	{
		std::cout << "State::goToPowerUp" << std::endl;

	}
};