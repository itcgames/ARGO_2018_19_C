#pragma once
#include <iostream>
#include <vector>
#include "EntityComponent.h"


class PhysicsSystem
{
	std::vector<Entity> entities;

public:
	PhysicsSystem();
	void addEntity(Entity e);
	void update();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

private:
	int vecX, vecY;
	int posX, posY;
	int maxX = 10, maxY = 10;
	int collision = false;
	ControlComponent * cc;
	PositionComponent * pc;
	AnimationComponent * ac;
};