#pragma once
#pragma once
#include <iostream>
#include <vector>
#include "EntityComponent.h"
#include "Fuzzy.h"
#include "AISystem.h"

AISystem::AISystem() {

}

void AISystem::addEntity(Entity e) {
	entities.push_back(e);
}
std::string AISystem::getEntity() {
	//only reurns first name
	for (Entity & entity : entities) {
		return entity.getName();
	}
}

Entity * AISystem::getEntityById(std::string s)
{
	for (Entity & entity : entities) {
		if (s == entity.getName())
			return &entity;
	}
	return &entities[0];
}



std::vector<std::string> AISystem::getEntityIds() {
		//only reurns first name
		std::vector<std::string> v;
		for (Entity & entity : entities) {
			v.push_back(entity.getName());
		}
		return v;
}

float AISystem::setDistance(float dis) {
	return distance;
}

int AISystem::getEntityIndex(std::string e)
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i].getName() == e)
		{
			return i;
		}
	}
	return -1;
}

void AISystem::removeEntityByIndex(int i)
{
	entities.erase(entities.begin() + i);
}

void AISystem::update(level &m_level) {

	for (Entity & entity : entities) {

		//for (Component* component : entity.getComponents()) {
		if (entity.getName() != "Flag") {
			cc = (ControlComponent*)entity.getCompByType("Control");
			pc = (PositionComponent*)entity.getCompByType("Position");
			ac = (AnimationComponent*)entity.getCompByType("Animation");
			sc = (SpriteComponent*)entity.getCompByType("Sprite");
			vel = (VelocityComponent*)entity.getCompByType("Vel");

			posX = pc->getPositionX();
			posY = pc->getPositionY();
			
			nodeCollision(m_level, pc->getPositionX(), pc->getPositionY(), sc->getWidth(), sc->getHeight(), threat_Y);

			if (!cc->stopFall && !cc->OnPlatform) {

				posY = pc->getPositionY();
				posX = pc->getPositionX();
				if (vel->getVelY() <= 10)
				{
					vel->setVelY(vel->getVelY() + 1);
					
				}

				cc->collision = 0;

				if (cc->moveLeft == 1) {
					ac->leftJump();
				}
				else if (cc->moveRight == 1)
				{
					ac->rightJump();
				}
			}
			else {
				vel->setVelY(0);
				cc->collision = 1;
				cc->jump = 0;

				if (ac->m_currentState == ac->jumpLeftS || ac->m_currentState == ac->jumpRightS)
				{
					ac->idle();
				}

			}
			//animation
			if (cc->moveLeft == 1)
			{
				moveLeft(velX);
			}
			if (cc->moveRight == 1)
			{
				moveRight(velX);
			}

			if (cc->getDirection() == cc->Up) {
				moveUp();
			}

			if (cc->moveLeft == 0 && cc->moveRight == 0)
			{
				cc->setDirection(cc->Idle);
				vecX = 0;
				ac->idle();
			}
			if (ac->m_currentState == ac->idleS && cc->moveLeft == 1)
			{
				ac->left();
			}
			else if (ac->m_currentState == ac->idleS && cc->moveRight == 1)
			{
				ac->right();
			}
			if (cc->ceilingHit)
			{
				vel->setVelY(5);
				cc->ceilingHit = false;
			}
			if (!cc->alive)
			{
				ac->die();
			}


			//Updates position of the ai
			pc->setPosition(pc->getPositionX() + vel->getVelX(), pc->getPositionY() + vel->getVelY());

			//if the Ai doesnt have the flag 
			if (cc->hasFlag != true) {
				//if not flag check position of the flag and decide whether or not to move left or right
				if (pcFlag != NULL)
				{
					leftOrRight(pcFlag->getPositionX(), pcFlag->getPositionY(), pc->getPositionX(), pc->getPositionY());

				}
			}
			else {

			}
			
		}
		else {
			pcFlag = (PositionComponent*)entity.getCompByType("Position");
		}

		//Gravity

		//Coll = (CollisionComponent *)entity.getCompByType("Collision");

		//if (cc->moveLeft == 1)
		//{
		//	//if(!collide)
		//	moveLeft();
		//}
		//if (cc->moveRight == 1)
		//{
		//	moveRight();
		//}

		//if (cc->moveLeft == 0 && cc->moveRight == 0)
		//{
		//	cc->setDirection(cc->Idle);
		//	vecX = 0;
		//	ac->idle();
		//}
		//if (ac->m_currentState == ac->idleS && cc->moveLeft == 1)
		//{
		//	ac->left();
		//}
		//else if (ac->m_currentState == ac->idleS && cc->moveRight == 1)
		//{
		//	ac->right();
		//}
		//std::cout << vecY << std::endl;
		//if (cc->ceilingHit)
		//{
		//	vecY = 5;
		//	cc->ceilingHit = false;

		//}

	}
	
}

void AISystem::leftOrRight(float fx, float fy, float px, float py) {
	//if flag x greater the player x add on to player === go right


	if (cc->collision == 1)
	{
		if (fx > px) {

			cc->moveRight = 1;
		}
		else {
			cc->moveRight = 0;
		}
		//=== go left
		if (fx < px) {

			cc->moveLeft = 1;
		}
		else {
			cc->moveLeft = 0;
		}
	}


}

void AISystem::moveLeft(float fuzz) {
	if (cc->hasFlag != true) {
		if (vel->getVelX() > -maxX)
		{
			ac->left();
			vel->setVelX(-4);
		}
	}
	else {
		//add code to move player using fuzzy velocity
		ac->left();
		vel->setVelX(-fuzz);
	}
	
}
void AISystem::moveRight(float fuzz) {
	if (cc->hasFlag != true) {
		if (vecX < maxX)
		{
			ac->right();
			vel->setVelX(4);
		}
	}
	else {
		//add code to move player using fuzzy velocity
		ac->left();
		vel->setVelX(fuzz);
	}
}
void AISystem::moveUp() {

	if (cc->jump == 0 && cc->collision == 1)
	{
		vel->setVelY(vel->getVelY() - 15);
		cc->stopFall = false;
		cc->OnPlatform = false;
		cc->jump = 1;
	}

}

void AISystem::checkNearest(float dis, Entity * entity, float c_y) {

	//Loop through all entities 
	for (Component* component : entity->getComponents()) {

		cc = (ControlComponent*)entity->getCompByType("Control");
		if (cc->hasFlag == true) {
			//call fuzzy update 
			m_fuzzy->update(dis);

			//update the ai position
			pc = (PositionComponent*)entity->getCompByType("Position");

			posX = pc->getPositionX();
			posY = pc->getPositionY();
			// get vec from fuzy logic
			velX = m_fuzzy->runAway();
			//std::cout << velX << std::endl;
			threat_Y = c_y;
			//instead of moving th pos here use the phys class

			//determine which side the player is on
			if (dis < 0) {
				moveLeft(-velX);
			}
			if (dis > 0) {
				moveRight(velX);
			}


			//set position 
			pc->setPosition(posX, posY);

		}
		
	}
}

bool AISystem::AABB(float x1, float y1, float x2, float y2, float width1, float height1, float width2, float height2)
{
	return(abs(x1 - x2) * 2 < (width1 + width2)) &&
		(abs(y1 - y2) * 2 < (height1 + height2));
}

void AISystem::nodeCollision(level &level, float x, float y, float width, float height, float c_y)
{
	for (int i = 0; i < level.m_nodes.size(); i++) {

		if (AABB(x, y, level.m_nodes[i].x, level.m_nodes[i].y, width, height, level.m_nodes[i].width, level.m_nodes[i].height)) {
		
			if (c_y < 0 && cc->hasFlag == true) {
				//
			}
			else {
				if (level.m_nodes[i].type == "JumpRight") {

					cc->setDirection(cc->Up);
					cc->jump = 0;
					cc->moveRight = 1;
					//std::cout << "Right" << std::endl;

				}
				else if (level.m_nodes[i].type == "JumpLeft") {

					cc->setDirection(cc->Up);
					cc->jump = 0;
					cc->moveLeft = 1;
					//std::cout << "JUMP" << std::endl;
				}
			}

		}
		else
		{
			cc->jump = 1;
		}

	}

}
