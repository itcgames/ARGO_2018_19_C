#pragma once
#include "AIState.h"

class GoToFlag : public AIState
{
public:
	GoToFlag() {};
	~GoToFlag() {};
	void goToNode(NoFlag* nf);
	void goToPowerUp(NoFlag* nf);
};