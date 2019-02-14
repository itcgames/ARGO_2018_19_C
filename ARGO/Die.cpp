#include "Die.h"

void Die::idle(AnimationComponent* a)
{
	std::cout << "Going from idle to Die" << std::endl;
	a->setCurrent(new Idle());
	a->setCurrentState(a->DieS);
	a->sRect.y = 400;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.x = 80;
	a->sRect.w = 80 * a->m_scale;
	delete this;
}

