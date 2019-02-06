#pragma once
#include "Component.h"
#include <vector>
#include <math.h>

class CollisionComponent :public Component
{
public:
	CollisionComponent() {};
	bool squareCollision(float x1, float y1, float x2, float y2,float width1, float height1, float width2, float height2)
	{
		if (x1 <x2 + width2 && x1 + width1 > x2
			&&y1<y2 + height2 && y1 + height1>y2)
		{
			std::cout << "Square Collision" << std::endl;
			return true;
		}
		else return false;
	}
	bool CircularCollision(float x1, float y1, float x2, float y2, float radius1, float radius2)
	{
		float distX = x1 - x2;
		float distY = y1 - y2;
		float distance = sqrt(distX * distX + distY * distY);

		if (distance < radius1 + radius2)
		{
			std::cout << "Circular collision" << std::endl;
			return true;
		}
		else return false;
	}
	
	std::string getID() { return id; }
private:
	std::string id = "Collision";
};