#pragma once
#include <vector>
#include "Component.h"

class VelocityComponent : public Component
{

public:
	VelocityComponent() {};

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
	float distance;
	// might need to change the ai pos
	//check how the phy class gets reference the the position
	std::string getID() { return id; }
private:
	float positionX;
	float positionY;
	float velX = 0;
	float velY = 0;
	
	std::string  id = "Vel";


};