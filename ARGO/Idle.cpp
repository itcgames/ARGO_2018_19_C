#include "Idle.h"
#include "JumpLeft.h"
#include "JumpRight.h"
#include "Right.h"
#include "Left.h"

void Idle::jumpLeft(AnimationComponent* a)
{
	std::cout << "JumpLeft" << std::endl;
	a->setCurrent(new JumpLeft());
	a->setCurrentState(a->jumpLeftS);
//	destRect.y = 0;
	a->sRect.y = 0;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.w = 80 * a->m_scale;
	a->sRect.x = 0;
	delete this;
}

void Idle::jumpRight(AnimationComponent* a)
{
	std::cout << "JumpRight" << std::endl;
	a->setCurrent(new JumpRight());
	a->setCurrentState(a->jumpRightS);
//	destRect.y = 265.6;
	a->sRect.y = 0;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.w = 80 * a->m_scale;
	a->sRect.x = 160 * a->m_scale;
	delete this;
}
void Idle::left(AnimationComponent* a)
{
	std::cout << "Left" << std::endl;
	a->setCurrent(new Left());
	a->setCurrentState(a->leftS);
	a->sRect.y = 100 * a->m_scale;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.w = 80 * a->m_scale;
	a->sRect.x = 0;
	delete this;
}

void Idle::right(AnimationComponent* a)
{
	std::cout << "Right" << std::endl;
	a->setCurrent(new Right());
	a->setCurrentState(a->rightS);
	a->sRect.y = 200 * a->m_scale;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.w = 80 * a->m_scale;
	a->sRect.x = 0;
	delete this;
}