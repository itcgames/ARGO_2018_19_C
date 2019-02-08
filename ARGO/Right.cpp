#include "Left.h"
#include "Right.h"
#include "JumpRight.h"
#include "JumpLeft.h"
#include "Idle.h"

void Right::idle(AnimationComponent* a)
{
	std::cout << "Going from Right to Idling" << std::endl;
	a->setCurrent(new Idle());
	a->setCurrentState(a->idleS);
	//destRect.y = 531.3;
	a->sRect.y = 0;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.w = 80 * a->m_scale;
	a->sRect.x = 80 * a->m_scale;
	delete this;
}
void Right::left(AnimationComponent* a)
{
	std::cout << "Going from Right to Left" << std::endl;
	a->setCurrent(new Left());
	a->setCurrentState(a->leftS);
	a->sRect.y = 100 * a->m_scale;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.w = 80 * a->m_scale;
	a->sRect.x = 0;
	delete this;
}
void Right::jumpLeft(AnimationComponent* a)
{
	std::cout << "Going from Right to jumpLeft" << std::endl;
	a->setCurrent(new JumpLeft());
	a->setCurrentState(a->jumpLeftS);
	//destRect.y = 531.3;
	a->sRect.y = 0;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.w = 80 * a->m_scale;
	a->sRect.x = 0;
	delete this;
}
void Right::jumpRight(AnimationComponent* a)
{
	std::cout << "Going from Right to jumpRight" << std::endl;
	a->setCurrent(new JumpRight());
	a->setCurrentState(a->jumpRightS);
	//destRect.y = 531.3;
	a->sRect.y = 0;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.w = 80 * a->m_scale;
	a->sRect.x = 160 * a->m_scale;
	delete this;
}