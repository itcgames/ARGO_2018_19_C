#pragma once
#pragma once
#include <iostream>
#include <vector>
#include "EntityComponent.h"
#include "Projectile.h"

class AmmoSystem
{
	std::vector<Entity> entities;
	//std::vector<Projectile *> projectiles;
	//int ammoCount = 0;
	float posX = 0;
	float posY = 0;

public:
	void addEntity(Entity e) {
		/*TBI*/
		entities.push_back(e);
	}
	std::string getEntity() {
		//only reurns first name
		for (Entity & entity : entities) {
			return entity.getName();
		}
	}
	Entity * getEntityById(std::string s)
	{
		for (Entity & entity : entities) {
			if(s == entity.getName())
			return &entity;
		}
		return &entities[0];
	}

	std::vector<std::string> getEntityIds() {
		//only reurns first name
		std::vector<std::string> v;
		for (Entity & entity : entities) {
			v.push_back(entity.getName());
		}
		return v;
	}

	void update() {

		/* Loop through Entities with */
		for (Entity & entity : entities) {

			//Loop through all entities 
			for (Component * component : entity.getComponents()) {
				AmmoComponent* ammoComp = (AmmoComponent*)entity.getCompByType("Ammo");
				//PositionComponent* posComp = (PositionComponent*)entity.getCompByType("Position");


				for (Entity & entityTwo : entities) {
					//check collsion then pop that index

					for (Component * componentTwo : entityTwo.getComponents()) {
						//AmmoComponent* ammoComp = (AmmoComponent*)entityTwo.getCompByType("Ammo");
						PositionComponent* posComp = (PositionComponent*)entityTwo.getCompByType("Position");

						if (entity.getName() != entityTwo.getName()) {
							float posX = posComp->getPositionX();
							float posY = posComp->getPositionY();


							ammoComp->checkCollision(posX, posY);
						}
						
					}
				}
				
			}
		}
		
	}

	void render(SDL_Renderer * m_renderer) {

		/* Loop through Entities with */
		for (Entity & entity : entities) {

			//Loop through all entities 
			for (Component * component : entity.getComponents()) {

				AmmoComponent* ammoComp = (AmmoComponent*)entity.getCompByType("Ammo");

				ammoComp->render();
				//could make method in ammo to return element in the projectile vector
			}
		}

	}

	void addAmmo(Entity * entity) {
		//increase the amout of ammo for that entity
		//Loop through all entities 
		for (Component * component : entity->getComponents()) {

			AmmoComponent* ammoComp = (AmmoComponent*)entity->getCompByType("Ammo");
			
			float current = ammoComp->getAmmo();
			current++;
			ammoComp->setAmmo(current);

		}
	}
	

};












