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
	float flagX = 0;
	float flagY = 0;

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

		
		for (Entity & entity : entities) {
			for (Component* component : entity.getComponents()) {

				//get the flag pos and get the player to move left or right
				pc = (PositionComponent*)entity.getCompByType("Position");
				if (entity.getName() == "Flag") {
					flagX = pc->getPositionX();
					flagY = pc->getPositionY();
				}
				else {
					posX = pc->getPositionX();
					posY = pc->getPositionY();
				}
				//std::cout << "AI" << std::endl;
			}
			if (entity.getName() != "Flag") {
				leftOrRight(flagX, flagY, posX, posY);
			}
			
		}

	}

	void leftOrRight(float fx, float fy, float px, float py) {
		//if flag x greater the player x add on to player === go right
		if (fx > px) {
			px++;
			pc->setPosition(px, py);
		}
		//=== go left
		if (fx < px) {
			px--;
			pc->setPosition(px, py);
		}

	}
	


};