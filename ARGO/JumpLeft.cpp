#include "JumpLeft.h"
#include "Idle.h"

void JumpLeft::idle(AnimationComponent* a)
{
	std::cout << "Going from Jumping to Idling" << std::endl;
	a->setCurrent(new Idle());
	//destRect.y = 531.3;
	delete this;
}

void JumpLeft::jumpRight(AnimationComponent* a)
{
	std::cout << "Going from Left to jumpright" << std::endl;
	//JumpRight* sdf = new JumpRight();
	a->setCurrent(new JumpRight());
	//destRect.y = 531.3;
	delete this;
}