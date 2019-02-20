#pragma once
#include "State.h"
#include "JumpRight.h"
#include "Idle.h"

class JumpLeft : public State
{
public:
	JumpLeft() {};
	~JumpLeft() {};
	void idle(AnimationComponent* a);
	void jumpRight(AnimationComponent* a);
	void die(AnimationComponent* a);
};