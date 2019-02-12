#pragma once
#include "State.h"

class JumpRight : public State
{
public:
	JumpRight() {};
	~JumpRight() {};
	void idle(AnimationComponent* a);
	

	void jumpLeft(AnimationComponent* a);
	
};