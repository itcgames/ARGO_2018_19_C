#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
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
	void speedUp(Entity * entity);
	std::string getEntity();
	Entity * getEntityById(std::string s);

private:
	int vecX, vecY;
	int posX, posY;
	int maxX = 10, maxY = 10;
	int collision = false;
	ControlComponent * cc;
	PositionComponent * pc;

	AnimationComponent * ac;
	SpriteComponent * sc;

	CollisionComponent * Coll;

};