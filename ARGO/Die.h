#pragma once
#include "State.h"
#include "Idle.h"

class Die : public State
{
public:
	Die() {};
	~Die() {};
	void idle(AnimationComponent* a);
};