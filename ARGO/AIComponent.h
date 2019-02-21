#pragma once
#include "Component.h"
class AIComponent : public Component
{

public:
	AIComponent() {};

	std::string getID()
	{
		return id;
	}

private:
	std::string  id = "AI";
};