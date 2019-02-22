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

			
		}
		else {
			pcFlag = (PositionComponent*)entity.getCompByType("Position");
		}

		if (pcFlag != NULL)
		{
			leftOrRight(pcFlag->getPositionX(), pcFlag->getPositionY(), pc->getPositionX(), pc->getPositionY());

		}
		
		if (cc->moveLeft == 1)
		{
			moveLeft();
		}
		if (cc->moveRight == 1)
		{
			moveRight();
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




		//Jamie
		////call fuzzy update
		//m_fuzzy->update(dis);

		////now only do this if the ai has the flag

		////update the ai position


		//posX = pc->getPositionX();
		//posY = pc->getPositionY();
		//// get vec from fuzy logic
		//velX = m_fuzzy->runAway();
		////std::cout << velX << std::endl;

		////determine which side the player is on
		//if (dis < 0) {
		//	posX -= velX;
		//}
		//if (dis > 0) {
		//	posX += velX;
		//}

		////set position
		//pc->setPosition(posX, posY);

		//collide
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

	//std::cout << "Vel :" << vel->getVelX() << std::endl;

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


//
//void PhysicsSystem::speedUp(Entity * entity) {
//
//	maxX++;
//}
//
void AISystem::moveLeft() {

	if (vel->getVelX() > -maxX)
	{
		ac->left();
		vel->setVelX(-4);
	}
}
void AISystem::moveRight() {

	if (vecX < maxX)
	{
		ac->right();
		vel->setVelX(4);
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
