#pragma once
#include "Component.h"
#include "Level.h"
class AiComponent: public Component 
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

	float closestN;
	float tempClosest;

	NodeObjects closestNode;

	void setCurrentState(AiStateS a);
private:
	std::string  id = "Ai";
};