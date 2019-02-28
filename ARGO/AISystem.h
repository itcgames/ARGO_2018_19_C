#pragma once
#include <iostream>
#include <vector>
#include "EntityComponent.h"
#include "Fuzzy.h"
#include "Level.h"

class AISystem
{
	std::vector<Entity> entities;
	Fuzzy* m_fuzzy = new Fuzzy();
	PositionComponent * pc;
	PositionComponent * pc2;
	PositionComponent * pcFlag;
	PickUpComponent * pickup;
	float posX = 0;
	float posY = 0;
	float velX = 0;
	float distance = 1000;
	int vecX, vecY;
	int maxX = 10, maxY = 10;
	int collision = false;

	float flagX = 0;
	float flagY = 0;
	float threat_Y = 0;

	AnimationComponent * ac;
	SpriteComponent * sc;
	SpriteComponent * sc2;
	CollisionComponent * Coll;
	VelocityComponent *vel;
	ControlComponent * cc2;
	ControlComponent * cc;
	VelocityComponent *vel2;
	AiComponent *ai;
	NodeObjects closestNode;

	std::string currentEntity;

public:
	AISystem();
	void addEntity(Entity e);
	void update(level &level);
	bool checkFlagInRange();
	//void update(float dis, Entity * entity);
	void moveLeft(float fuzz);
	void moveRight(float fuzz);
	void moveUp();
	void moveDown();
	void speedUp(Entity * entity);
	NodeObjects nearestNode(level &level, std::string type);
	float dist(float x1, float x2, float y1, float y2);
	std::string getEntity();
	Entity * getEntityById(std::string s);
	std::vector<std::string> getEntityIds();
	float setDistance(float dis);
	void leftOrRight(float fx, float fy, float px, float py);
	void nodeCollision(NodeObjects closestNode, float x, float y, float width, float height);
	bool AABB(float x1, float y1, float x2, float y2, float width1, float height1, float width2, float height2);

};
