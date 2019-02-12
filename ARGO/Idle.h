#pragma once
#include "State.h"

class Idle : public State
{
public:
	Idle() {};
	~Idle() {};


	void jumpRight(AnimationComponent* a);
	void jumpLeft(AnimationComponent* a);
	void right(AnimationComponent* a);
	void left(AnimationComponent* a);

};