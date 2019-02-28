#pragma once
#include "AIState.h"

class GoToNode: public AIState
{
public:
	GoToNode() {};
	~GoToNode() {};
	void goToFlag(AIState* nf);
	void goToPowerUp(AIState* nf);
};