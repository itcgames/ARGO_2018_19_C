#pragma once
#include "State.h"

class Left : public State
{
public:
	Left() {};
	~Left() {};
	void idle(AnimationComponent* a);

	void right(AnimationComponent* a);

	void jumpLeft(AnimationComponent* a);

	void jumpRight(AnimationComponent* a);
	void die(AnimationComponent* a);
};