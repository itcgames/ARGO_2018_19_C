#pragma once
#include "Component.h"
class NoFlag 
{
	class AIState* m_current;
public:
	NoFlag() {};
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
	std::string  id = "NoFlag";
};