#pragma once
#include "State.h"
#include "JumpRight.h"

class JumpLeft : public State
{
public:
	JumpLeft() {};
	~JumpLeft() {};
	void idle(AnimationComponent* a);
	

	void jumpRight(AnimationComponent* a);
	
};