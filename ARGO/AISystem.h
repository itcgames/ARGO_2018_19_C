#pragma once
#pragma once
#include <iostream>
#include <vector>
#include "EntityComponent.h"
#include "Fuzzy.h"

class AISystem
{
	std::vector<Entity> entities;
	Fuzzy* m_fuzzy = new Fuzzy(); 
	PositionComponent * pc;
	float posX = 0;
	float posY = 0;
	float velX = 0;

public:
	void addEntity(Entity e) {
		/*TBI*/
		entities.push_back(e);
	}
	void update(float dis) {

		//call fuzzy update 
		m_fuzzy->update(dis);

		for (Entity & entity : entities) {

			//Loop through all entities 
			for (Component* component : entity.getComponents()) {
				//update the ai position
				pc = (PositionComponent*)entity.getCompByType("Position");

				posX = pc->getPositionX();
				posY = pc->getPositionY();
				// get vec from fuzy logic
				velX = m_fuzzy->runAway();
				//std::cout << velX << std::endl;

				//determine which side the player is on
				if (dis < 0) {
					posX -= velX;
				}
				if (dis > 0) {
					posX += velX;
				}
				
				//set position 
				pc->setPosition(posX, posY);
			}
		}
	}
};