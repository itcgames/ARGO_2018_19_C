#include "NoFlag.h"
#include "GoToFlag.h"
#include "GoToNode.h"
#include "GoToPowerup.h"
NoFlag::NoFlag()
{
	//m_current = new GoToNode();
	/*sRect.y = 0;
	sRect.h = 100 * m_scale;
	sRect.w = 80 * m_scale;
	sRect.x = 80 * m_scale;*/
}

void NoFlag::goToNode()
{
	m_current->goToNode(this);
}
void NoFlag::goToFlag()
{
	m_current->goToFlag(this);
}
void NoFlag::goToPowerUp()
{
	m_current->goToPowerUp(this);
}

void NoFlag::setCurrent(AIState* s)
{
	m_current = s;
}

AIState* NoFlag::getCurrent()
{
	return m_current;
}

//void AnimationComponent::setCurrentState(AniState a) {
//
//	m_currentState = a;
//}
