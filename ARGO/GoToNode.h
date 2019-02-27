#pragma once
#include "AIState.h"

class GoToNode: public AIState
{
public:
	GoToNode() {};
	~GoToNode() {};
	void goToFlag(NoFlag* nf);
	void goToPowerUp(NoFlag* nf);
};