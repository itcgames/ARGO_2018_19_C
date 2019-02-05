#pragma once
#include <vector>
#include "Component.h"
class PositionComponent : public Component
{
	
public:
	PositionComponent(float posX, float posY) : positionX(posX), positionY(posY) {};

	/*Data only*/
	float getPositionX() {
		return positionX;
	}

	float getPositionY() {
		return positionY;
	}

	void setPosition(float x, float y) {
		this->positionX = x;
		this->positionY = y;
	}
	std::string getID()
	{
		return id;
	}
private:
	float positionX;
	float positionY;
	std::string  id = "Position";
};