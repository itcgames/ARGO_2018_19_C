#include "goToFlag.h"
#include "GoToNode.h"
#include "GoToPowerup.h"

void GoToPowerup::goToFlag(NoFlag* nf)
{
	//std::cout << "JumpLeft" << std::endl;
	nf->setCurrent(new GoToFlag());
	/*a->setCurrentState(a->jumpLeftS);
	a->sRect.y = 0;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.w = 80 * a->m_scale;
	a->sRect.x = 0;*/
	delete this;
}

void GoToPowerup::goToNode(NoFlag* nf)
{
	//std::cout << "JumpRight" << std::endl;
	nf->setCurrent(new GoToNode());
	//a->setCurrentState(a->jumpRightS);
	//	destRect.y = 265.6;
	/*a->sRect.y = 0;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.w = 80 * a->m_scale;
	a->sRect.x = 160 * a->m_scale;*/
	delete this;
}