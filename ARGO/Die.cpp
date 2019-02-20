#include "Die.h"

void Die::idle(AnimationComponent* a)
{
	std::cout << "Going from Left to Idling" << std::endl;
	a->setCurrent(new Idle());
	a->setCurrentState(a->idleS);
	//	destRect.y = 531.3;
	a->sRect.y = 0;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.w = 80 * a->m_scale;
	a->sRect.x = 80 * a->m_scale;
	delete this;
}

