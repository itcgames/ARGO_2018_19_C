#pragma once
#include "AIState.h"

class GoToFlag : public AIState
{
public:
	GoToFlag() {};
	~GoToFlag() {};
	void goToNode(AIState* nf);
	void goToPowerUp(AIState* nf);
};