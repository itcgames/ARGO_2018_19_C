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
			pc = (PositionComponent*)entity.getCompByType("Position");
			vel = (VelocityComponent*)entity.getCompByType("Vel");

			posX = pc->getPositionX();
			posY = pc->getPositionY();
			leftOrRight(flagX, flagY, posX, posY);

			if (!cc->stopFall && !cc->OnPlatform) {

				posY = pc->getPositionY();
				posX = pc->getPositionX();
				if (vel->getVelY() <= 10)
				{
					vel->setVelY(vel->getVelY() + 1);
				}

				//posY += vecY;

				pc->setPosition(pc->getPositionX() + vel->getVelX(), pc->getPositionY() + vel->getVelY());
				collision = 0;

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
				collision = 1;

				if (ac->m_currentState == ac->jumpLeftS || ac->m_currentState == ac->jumpRightS)
				{
					ac->idle();
				}

			}

			/*int posX = pc->getPositionX();
			int posY = pc->getPositionY();
			posX += vecX;*/
			pc->setPosition(pc->getPositionX() + vel->getVelX(), pc->getPositionY() + vel->getVelY());
		}
		else {
			pc = (PositionComponent*)entity.getCompByType("Position");
			flagX = pc->getPositionX();
			flagY = pc->getPositionY();
		}

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


		if (cc->getDirection() == cc->Up) {
			moveUp();
		}


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


//
//void PhysicsSystem::speedUp(Entity * entity) {
//
//	maxX++;
//}
//
//void PhysicsSystem::moveLeft() {
//
//	if (vecX > -maxX)
//	{
//		ac->left();
//		int posX = pc->getPositionX();
//		int posY = pc->getPositionY();
//		vecX = -7;
//		posX += vecX;
//
//		pc->setPosition(posX, posY);
//	}
//}
//void PhysicsSystem::moveRight() {
//
//	if (vecX < maxX)
//	{
//		ac->right();
//		int posX = pc->getPositionX();
//		int posY = pc->getPositionY();
//		vecX = 7;
//		posX += vecX;
//		pc->setPosition(posX, posY);
//	}
//
//
//}
void AISystem::moveUp() {

	if (cc->jump == 0 && collision == true)
	{
		int posX = pc->getPositionX();
		int posY = pc->getPositionY();
		vecY = -20;
	
		posY += vecY;
		posX += vecX;
		pc->setPosition(pc->getPositionX() + vel->getVelX(), pc->getPositionY() + vel->getVelY() - 20);
		cc->stopFall = false;
		cc->OnPlatform = false;
		cc->jump = 1;
	}

}
