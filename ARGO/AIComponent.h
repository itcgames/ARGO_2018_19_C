#pragma once
#include "Component.h"
#include "Level.h"
class AiComponent : public Component
{
	class AIState* m_current;
public:
	AiComponent();
	void setCurrent(AIState* s);
	AIState* getCurrent();

	void goToNode();

	void goToFlag();

	void goToPowerUp();

	std::string getID()
	{
		return id;
	}

	enum AiStateS {
		goToNodeS,
		goToFlagS,
		goToPowerupS
	};
	AiStateS m_currentState;

	float closestN = 10000;
	float temp;

	NodeObjects closestNode;

	void setCurrentState(AiStateS a);
private:
	std::string  id = "Ai";
};