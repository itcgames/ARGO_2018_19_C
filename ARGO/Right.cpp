#include "Left.h"
#include "Right.h"
#include "JumpRight.h"
#include "JumpLeft.h"
#include "Idle.h"

void Right::idle(AnimationComponent* a)
{
	std::cout << "Going from Right to Idling" << std::endl;
	a->setCurrent(new Idle());
	//destRect.y = 531.3;
	delete this;
}
void Right::left(AnimationComponent* a)
{
	std::cout << "Going from Right to Left" << std::endl;
	a->setCurrent(new Left());
	//destRect.y = 531.3;
	delete this;
}
void Right::jumpLeft(AnimationComponent* a)
{
	std::cout << "Going from Right to jumpLeft" << std::endl;
	a->setCurrent(new JumpLeft());
	//destRect.y = 531.3;
	delete this;
}
void Right::jumpRight(AnimationComponent* a)
{
	std::cout << "Going from Right to jumpRight" << std::endl;
	a->setCurrent(new JumpRight());
	//destRect.y = 531.3;
	delete this;
}