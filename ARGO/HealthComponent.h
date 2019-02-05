#pragma once
#include <vector>
#include "Component.h"
class HealthComponent: public Component
{
	
public:
	HealthComponent(int startHealth) : health(startHealth) {};

	/*Data only*/
	int getHealth() {
		return health;
	}

	void setHealth(int health) {
		this->health = health;
	}
	std::string getID()
	{
		return id;
	}
private:
	int health;
	std::string id = "Health";
};