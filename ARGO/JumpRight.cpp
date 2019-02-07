#include "JumpRight.h"
#include "Idle.h"
#include "JumpLeft.h"

void JumpRight::idle(AnimationComponent* a)
{
	std::cout << "Going from Jumping to Idling" << std::endl;
	a->setCurrent(new Idle());
	//destRect.y = 531.3;
	delete this;
}

void JumpRight::jumpLeft(AnimationComponent* a)
{
	std::cout << "Going from Left to jumpLeft" << std::endl;
	a->setCurrent(new JumpLeft());
	//destRect.y = 531.3;
	delete this;
}