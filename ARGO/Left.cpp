#include "Left.h"
#include "Right.h"
#include "JumpRight.h"
#include "JumpLeft.h"
#include "Idle.h"
#include "Die.h"

void Left::idle(AnimationComponent* a)
{
	//std::cout << "Going from Left to Idling" << std::endl;
	a->setCurrent(new Idle());
	a->setCurrentState(a->idleS);
	//	destRect.y = 531.3;
	a->sRect.y = 0;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.w = 80 * a->m_scale;
	a->sRect.x = 80 * a->m_scale;
	delete this;
}

void Left::jumpRight(AnimationComponent* a)
{
	//std::cout << "Going from Left to jumpright" << std::endl;
	a->setCurrent(new JumpRight());
	a->setCurrentState(a->jumpRightS);
	//destRect.y = 531.3;
	a->sRect.y = 0;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.w = 80 * a->m_scale;
	a->sRect.x = 160 * a->m_scale;
	delete this;
}
void Left::jumpLeft(AnimationComponent* a)
{
	//std::cout << "Going from Left to jumpLeft" << std::endl;
	a->setCurrent(new JumpLeft());
	a->setCurrentState(a->jumpLeftS);
	//	destRect.y = 531.3;
	a->sRect.y = 0;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.w = 80 * a->m_scale;
	a->sRect.x = 0;
	delete this;
}
void Left::right(AnimationComponent* a)
{
	//std::cout << "Going from Left to right" << std::endl;
	a->setCurrent(new Right()); 
	a->setCurrentState(a->rightS);
	a->sRect.y = 200 * a->m_scale;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.w = 80 * a->m_scale;
	a->sRect.x = 0;
	delete this;
}

void Left::die(AnimationComponent* a)
{
	std::cout << "Going from left to Die" << std::endl;
	a->setCurrent(new Die());
	a->setCurrentState(a->DieS);
	a->sRect.y = 400;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.x = 80;
	a->sRect.w = 80 * a->m_scale;
	delete this;
}