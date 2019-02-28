#include "AiComponent.h"
#include "GoToFlag.h"
#include "GoToNode.h"
#include "GoToPowerup.h"
AiComponent::AiComponent()
{
	m_current = new GoToNode();
	m_currentState = goToNodeS;
	//	/*sRect.y = 0;
	//	sRect.h = 100 * m_scale;
	//	sRect.w = 80 * m_scale;
	//	sRect.x = 80 * m_scale;*/
}

void AiComponent::goToNode()
{
	m_current->goToNode(this);
}
void AiComponent::goToFlag()
{
	m_current->goToFlag(this);
}
void AiComponent::goToPowerUp()
{
	m_current->goToPowerUp(this);
}

void AiComponent::setCurrent(AIState* s)
{
	m_current = s;
}

AIState* AiComponent::getCurrent()
{
	return m_current;
}

void AiComponent::setCurrentState(AiStateS a) {

	m_currentState = a;
}