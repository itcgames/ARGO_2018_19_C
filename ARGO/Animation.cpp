#include "Animation.h"
#include "Idle.h"
AnimationComponent::AnimationComponent()
{
	m_current = new Idle();
}

void AnimationComponent::idle()
{
	m_current->idle(this);
}
void AnimationComponent::leftJump()
{
	m_current->jumpLeft(this);
}
void AnimationComponent::rightJump()
{
	m_current->jumpRight(this);
}
void AnimationComponent::right()
{
	m_current->right(this);
}
void AnimationComponent::left()
{
	m_current->left(this);
}

void AnimationComponent::setCurrent(State* s)
{
	m_current = s;
}

State* AnimationComponent::getCurrent()
{
	return m_current;
}

void AnimationComponent::setCurrentState(AniState a) {

	m_currentState = a;
}
