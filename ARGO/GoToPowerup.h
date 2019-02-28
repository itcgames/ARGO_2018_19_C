#pragma once
#pragma once
#include "AIState.h"

class GoToPowerup : public AIState
{
public:
	GoToPowerup() {};
	~GoToPowerup() {};
	void goToFlag(AIState* nf);
	void goToNode(AIState* nf);
};