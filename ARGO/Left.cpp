#include "Left.h"
#include "Right.h"
#include "JumpRight.h"
#include "JumpLeft.h"
#include "Idle.h"

void Left::idle(AnimationComponent* a)
{
	std::cout << "Going from Left to Idling" << std::endl;
	a->setCurrent(new Idle());
	//	destRect.y = 531.3;
	delete this;
}

void Left::jumpRight(AnimationComponent* a)
{
	std::cout << "Going from Left to jumpright" << std::endl;
	a->setCurrent(new JumpRight());
	//destRect.y = 531.3;
	delete this;
}
void Left::jumpLeft(AnimationComponent* a)
{
	std::cout << "Going from Left to jumpLeft" << std::endl;
	a->setCurrent(new JumpLeft());
	//	destRect.y = 531.3;
	delete this;
}
void Left::right(AnimationComponent* a)
{
	std::cout << "Going from Left to right" << std::endl;
	a->setCurrent(new Right());
	//destRect.y = 531.3;
	delete this;
}