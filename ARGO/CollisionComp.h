#pragma once
#include "Component.h"
#include <vector>
#include <math.h>
#include <map>


class CollisionComponent :public Component
{
public:
	bool squareCollided = false;
	bool crclCollided = false;
	bool m_Invincible = false;

	CollisionComponent() {};

	bool CircularCollision(float x1, float y1, float x2, float y2, float radius1, float radius2)
	{
		float distX = x1 - x2;
		float distY = y1 - y2;
		float distance = sqrt(distX * distX + distY * distY);

		if (distance < radius1 + radius2)
		{
			std::cout << "Circular collision" << std::endl;
			crclCollided = true;
		}
		else crclCollided = false;

		return crclCollided;
	}



	std::string getID() { return id; }
	
private:
	std::string id = "Collision";
	
	
};