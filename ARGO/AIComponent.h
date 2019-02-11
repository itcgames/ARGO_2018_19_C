#pragma once
#include <vector>
#include "Component.h"

class AIComponent : public Component
{

public:
	AIComponent() {};

	// might need to change the ai pos
	//check how the phy class gets reference the the position
	std::string getID() { return id; }
private:
	float positionX;
	float positionY;
	float velX;
	float velY;
	float distance;
	std::string  id = "AI";
};