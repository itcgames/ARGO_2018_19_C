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
	int vecX, vecY;
	int maxX = 10, maxY = 10;
	int collision = false;
	ControlComponent * cc;

	AnimationComponent * ac;
	SpriteComponent * sc;

	CollisionComponent * Coll;

public:
	AISystem();
	void addEntity(Entity e);
	void update();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void speedUp(Entity * entity);
	std::string getEntity();
	Entity * getEntityById(std::string s);
};