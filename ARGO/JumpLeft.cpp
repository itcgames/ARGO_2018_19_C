#include "JumpLeft.h"
#include "Idle.h"

void JumpLeft::idle(AnimationComponent* a)
{
	std::cout << "Going from JumpLeft to Idling" << std::endl;
	a->setCurrent(new Idle());
	a->setCurrentState(a->idleS);
	//destRect.y = 531.3;
	/*a->sRect.y = 0;
	a->sRect.h = 100;
	a->sRect.w = 80;
	a->sRect.x = 80;*/
	delete this;
}

void JumpLeft::jumpRight(AnimationComponent* a)
{
	std::cout << "Going from JumpLeft to jumpright" << std::endl;
	//JumpRight* sdf = new JumpRight();
	a->setCurrent(new JumpRight());
	a->setCurrentState(a->jumpRightS);
	a->sRect.y = 0;
	a->sRect.h = 100;
	a->sRect.w = 80;
	a->sRect.x = 160;
	delete this;
}