#pragma once
#include "State.h"

class Right : public State
{
public:
	Right() {};
	~Right() {};
	void idle(AnimationComponent* a);

	void left(AnimationComponent* a);

	void jumpLeft(AnimationComponent* a);

	void jumpRight(AnimationComponent* a);

};