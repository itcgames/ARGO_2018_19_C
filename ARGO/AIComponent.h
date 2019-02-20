#pragma once
#include <vector>
#include "Component.h"

class AIComponent : public Component
{

public:
	AIComponent() {};

	float getDistance() {
		return distance;
	}
	float getVelX() {
		return velX;
	}
	float getVelY() {
		return velY;
	}

	void setVelX(float vel) {
		velX = vel;
	}
	void setVelY(float vel) {
		velY = vel;
	}
	
	// might need to change the ai pos
	//check how the phy class gets reference the the position
	std::string getID() { return id; }
private:
	float positionX;
	float positionY;
	float velX = 0;
	float velY = 0;
	float distance;
	std::string  id = "AI";


};