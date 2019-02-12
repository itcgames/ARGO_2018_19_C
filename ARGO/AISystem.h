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
	float distance = 1000;

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
	float setDistance(float dis) {
		return distance;
	}

	void update(float dis, Entity * entity) {

		

		//for (Entity & entity : entities) {

			//Loop through all entities 
			for (Component* component : entity->getComponents()) {

				//call fuzzy update 
				m_fuzzy->update(dis);

				//now only do this if the ai has the flag

				//update the ai position
				pc = (PositionComponent*)entity->getCompByType("Position");

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
	


};