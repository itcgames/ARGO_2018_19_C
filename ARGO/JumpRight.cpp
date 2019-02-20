#include "JumpRight.h"
#include "Idle.h"
#include "JumpLeft.h"

void JumpRight::idle(AnimationComponent* a)
{
	//std::cout << "Going from JumpingRight to Idling" << std::endl;
	a->setCurrent(new Idle());
	a->setCurrentState(a->idleS);
	a->sRect.y = 0;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.w = 80 * a->m_scale;
	a->sRect.x = 80 * a->m_scale;
	delete this;
}

void JumpRight::jumpLeft(AnimationComponent* a)
{
	//std::cout << "Going from JumpRight to jumpleft" << std::endl;
	a->setCurrent(new JumpLeft());
	a->setCurrentState(a->jumpLeftS);
	a->sRect.y = 0;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.w = 80 * a->m_scale;
	a->sRect.x = 0;
	delete this;
}