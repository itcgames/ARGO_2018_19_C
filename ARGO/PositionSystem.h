#pragma once
#pragma once
#include <iostream>
#include <vector>
#include "EntityComponent.h"
class PositionSystem
{
	std::vector<Entity> entities;

public:
	void addEntity(Entity e) {
		/*TBI*/
		entities.push_back(e);
	}
	void update() {

		/* Position Components and Update */
		/* Loop through Entities with */
		int index = 0;

		for (Entity & entity : entities) {

			//Loop through all entities 
			for (Component* component : entity.getComponents()) {
				//only update postition components
				//if (component->getID() == 2)
				//{

				//	//Get current health
				//	int posX = dynamic_cast<PositionComponent*>(component)->getPositionX();
				//	int posY = dynamic_cast<PositionComponent*>(component)->getPositionY();

				//	std::cout << "Checking position componenet of entity" << std::endl;

				//}
			}
		}
	}
};