#include "Idle.h"
#include "JumpLeft.h"
#include "JumpRight.h"
#include "Right.h"
#include "Left.h"

void Idle::jumpLeft(AnimationComponent* a)
{
	std::cout << "JumpLeft" << std::endl;
	a->setCurrent(new JumpLeft());
//	destRect.y = 0;
	delete this;
}

void Idle::jumpRight(AnimationComponent* a)
{
	std::cout << "JumpRight" << std::endl;
	a->setCurrent(new JumpRight());
//	destRect.y = 265.6;
	delete this;
}
void Idle::left(AnimationComponent* a)
{
	std::cout << "Left" << std::endl;
	a->setCurrent(new Left());
//	destRect.y = 0;
	delete this;
}

void Idle::right(AnimationComponent* a)
{
	std::cout << "Right" << std::endl;
	a->setCurrent(new Right());
	//destRect.y = 265.6;
	delete this;
}