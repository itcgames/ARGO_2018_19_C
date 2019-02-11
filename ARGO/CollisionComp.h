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

	
		//if (level2 == false)
		//{
		//	for (int i = 0; i < m_tileMap.m_object_position.size(); i++)
		//	{
		//		//Top of the onject 
		//		if (m_position.y + animation.uvRect.height >= m_tileMap.m_object_position.at(i).y && m_position.y + animation.uvRect.height <= m_tileMap.m_object_position.at(i).y + m_tileMap.m_object_WH.at(i).y
		//			&& m_position.x >= m_tileMap.m_object_position.at(i).x - animation.uvRect.width && m_position.x <= m_tileMap.m_object_position.at(i).x + m_tileMap.m_object_WH.at(i).x)
		//		{
		//			if (m_velocity.y > 0)
		//			{
		//				gravity = false;
		//				m_velocity.y = 0;
		//				m_position.y = m_tileMap.m_object_position.at(i).y - animation.uvRect.height;
		//				jumped = false;
		//				jumpCount = 0;
		//			}

		//		}

		//		else
		//		{
		//			gravity = true;
		//			jumped = true;
		//		}


		//		/*if (m_position.y - m_radius <= m_tileMap.m_object_position.at(i).y + m_tileMap.m_object_WH.at(i).y && m_position.y - m_radius >= m_tileMap.m_object_position.at(i).y + m_tileMap.m_object_WH.at(i).y - 40
		//		&& m_position.x >= m_tileMap.m_object_position.at(i).x && m_position.x <= m_tileMap.m_object_position.at(i).x + m_tileMap.m_object_WH.at(i).x)
		//		{
		//		m_velocity.y = 0;
		//		}
		//		std::cout << gravity << std::endl;*/

		//	}
		/*for(int i =0; i<)*/
	
	
	std::string getID() { return id; }
	
private:
	std::string id = "Collision";

	
};