#pragma once
#include "AIState.h"

class GoToNode: public AIState
{
public:
	GoToNode() {};
	~GoToNode() {};
	void goToFlag(AiComponent* ai);
	void goToPowerUp(AiComponent* ai);
};