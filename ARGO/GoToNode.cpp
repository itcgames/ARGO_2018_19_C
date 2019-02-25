#include "goToFlag.h"
#include "GoToNode.h"
#include "GoToPowerup.h"

void GoToNode::goToFlag(AiComponent* ai)
{
	//std::cout << "JumpLeft" << std::endl;
	//ai->setCurrent(new GoToFlag());
	ai->setCurrentState(ai->goToFlagS);
	/*a->sRect.y = 0;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.w = 80 * a->m_scale;
	a->sRect.x = 0;*/
	delete this;
}

void GoToNode::goToPowerUp(AiComponent* ai)
{
	ai->setCurrentState(ai->goToPowerupS);
	//std::cout << "JumpRight" << std::endl;
	//ai->setCurrent(new GoToPowerup());
	//a->setCurrentState(a->jumpRightS);
	//	destRect.y = 265.6;
	/*a->sRect.y = 0;
	a->sRect.h = 100 * a->m_scale;
	a->sRect.w = 80 * a->m_scale;
	a->sRect.x = 160 * a->m_scale;*/
	delete this;
}