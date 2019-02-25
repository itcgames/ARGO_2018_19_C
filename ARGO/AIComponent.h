#pragma once
#include "Component.h"
class AiComponent: public Component 
{
	class AIState* m_current;
public:
	AiComponent() {};
	void setCurrent(AIState* s);
	AIState* getCurrent();

	void goToNode();

	void goToFlag();

	void goToPowerUp();

	std::string getID()
	{
		return id;
	}

private:
	std::string  id = "Ai";
};