#pragma once
#include "Component.h"
class HasFlag : public Component
{
	class AIState* m_current;
public:
	HasFlag() {};
	void setCurrent(AIState* s);
	AIState* getCurrent();

	void nearestNode();

	void goToFlag();

	void powerUp();

	std::string getID()
	{
		return id;
	}



private:
	std::string  id = "AI";
};