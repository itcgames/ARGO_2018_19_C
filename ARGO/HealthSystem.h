#pragma once
#include <iostream>
#include <vector>
#include "EntityComponent.h"
class HealthSystem
{
	std::vector<Entity> entities;


public:
	void addEntity(Entity e) {
		/*TBI*/
		entities.push_back(e);

	}
	void update() {
		std::cout << "HEALTH SYSTEM: " << std::endl;

		int index = 0;

		/* HealthComponents and Update */
		/* Loop through Entities with */
		for (Entity & entity : entities) {

			//Loop through all entities 
			for (Component * component : entity.getComponents()) {
				//only update health components
				
					index++;
					//Get current health

					HealthComponent * healthComp = (HealthComponent*)entity.getCompByType("Health");
			
					int healthVal = healthComp->getHealth();
					if (healthVal > 0)
					{

						healthVal = healthVal - 1;
						////Update health value of health component
						healthComp->setHealth(healthVal);

						std::cout << "Updated health component of entity: " << entity.getName() << std::endl;
						std::cout << "Health: " << healthComp->getHealth() << std::endl;
					}
					else
					{
						std::cout << "Entity " << entity.getName() << " has 0 health" << std::endl;
					}
					
					

					
					

				
			}
		}
		
		std::cout << std::endl;
		std::cout << std::endl;
	}
};