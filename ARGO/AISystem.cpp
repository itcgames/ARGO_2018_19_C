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
		if(entity.getName() != "Flag")
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
			ai = (AiComponent*)entity.getCompByType("Ai");

			posX = pc->getPositionX();
			posY = pc->getPositionY();
			
			//nodeCollision(m_level, pc->getPositionX(), pc->getPositionY(), sc->getWidth(), sc->getHeight(), threat_Y);

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
			

			//Updates position of the ai
			pc->setPosition(pc->getPositionX() + vel->getVelX(), pc->getPositionY() + vel->getVelY());

		}
		else {
			pcFlag = (PositionComponent*)entity.getCompByType("Position");
		}
		if (cc != nullptr)
		{
			if (cc->hasFlag == false && pcFlag != NULL)
			{

				if (checkFlagInRange())
				{
					//left and right
					//ai->goToFlag();
					leftOrRight(pcFlag->getPositionX(), pcFlag->getPositionY(), pc->getPositionX(), pc->getPositionY());

				}
				else if (checkFlagInRange() == false && pc->getPositionY() < pcFlag->getPositionY()) {



					if (nearestNode(m_level, "Edge").x >= pc->getPositionX() && cc->collision == 1)
					{
						cc->moveRight = 1;
						cc->moveLeft = 0;
					}
					else if (nearestNode(m_level, "Edge").x <= pc->getPositionX() && cc->collision == 1)
					{
						cc->moveRight = 0;
						cc->moveLeft = 1;
					}
					if (cc->collision == 1) {
						nodeCollision(ai->closestNode, pc->getPositionX(), pc->getPositionY(), sc->getWidth(), sc->getHeight(), 2);
					}

				}
				else if (checkFlagInRange() == false && pc->getPositionY() - sc->getHeight() > pcFlag->getPositionY())
				{

					//ai->goToNode();



					if (nearestNode(m_level, "Jump").x >= pc->getPositionX() && cc->collision == 1)
					{
						cc->moveRight = 1;
						cc->moveLeft = 0;
					}
					else if (nearestNode(m_level, "Jump").x <= pc->getPositionX() && cc->collision == 1)
					{
						cc->moveRight = 0;
						cc->moveLeft = 1;
					}

					if (cc->collision == 1) {
						nodeCollision(ai->closestNode, pc->getPositionX(), pc->getPositionY(), sc->getWidth(), sc->getHeight(), 1);
					}


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

NodeObjects AISystem::nearestNode(level &level, std::string type) {

	ai->closestN = 10000;

	for (int i = 0; i < level.m_nodes.size(); i++) {

		//Check if node is on the same y level as the player 
		if (level.m_nodes[i].y < pc->getPositionY() + sc->getHeight() &&
			level.m_nodes[i].y > pc->getPositionY() - sc->getHeight()) {

			if (type == "Jump")
			{
				if (level.m_nodes[i].type == "JumpRight" && pc->getPositionX() < pcFlag->getPositionX())
				{
					ai->temp = dist(pc->getPositionX(), level.m_nodes[i].x, pc->getPositionY(), level.m_nodes[i].y);
					//std::cout << temp << std::endl;
					if (ai->temp < ai->closestN) {
						ai->closestN = ai->temp;
						ai->closestNode = level.m_nodes[i];

					}
				}
				else if (level.m_nodes[i].type == "JumpLeft" && pc->getPositionX() > pcFlag->getPositionX())
				{
					ai->temp = dist(pc->getPositionX(), level.m_nodes[i].x, pc->getPositionY(), level.m_nodes[i].y);
					//std::cout << temp << std::endl;
					if (ai->temp < ai->closestN) {
						ai->closestN = ai->temp;
						ai->closestNode = level.m_nodes[i];

					}
				}


			}
			else
			{
				if (level.m_nodes[i].type == type)
				{
					ai->temp = dist(pcFlag->getPositionX(), level.m_nodes[i].x, pcFlag->getPositionY(), level.m_nodes[i].y);
					//std::cout << temp << std::endl;
					if (ai->temp < ai->closestN) {
						ai->closestN = ai->temp;
						ai->closestNode = level.m_nodes[i];

					}
				}
			}

		}
	}

	return ai->closestNode;

}

float AISystem::dist(float x1, float x2, float y1, float y2) {

	float distanceX = x1 - x2;
	float distanceY = y1 - y2;

	return std::sqrt(distanceX * distanceX + distanceY * distanceY);

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

bool AISystem::checkFlagInRange() {

	if (pcFlag->getPositionY() < pc->getPositionY() &&
		pcFlag->getPositionY() > pc->getPositionY() - sc->getHeight() * 1)
	{
		if (pc->getPositionX() >= pcFlag->getPositionX() &&
			pc->getPositionX() < pcFlag->getPositionX() + sc->getWidth()
			&& pickup->getState() == pickup->Collectable) {

			cc->setDirection(cc->Up);
			moveUp();


			pc->setPosition(pc->getPositionX() + vel->getVelX(), pc->getPositionY() + vel->getVelY());

		}
		return true;
	}
	else
	{
		return false;
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
				moveLeft(velX);
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

void AISystem::nodeCollision(NodeObjects closestNode, float x, float y, float width, float height, float c_y)
{
	if (AABB(x, y, closestNode.x, closestNode.y, width, height, closestNode.width, closestNode.height)) {

		if (closestNode.type == "JumpRight" && pc->getPositionX() < pcFlag->getPositionX()) {

			cc->setDirection(cc->Up);
			moveUp();
			cc->moveRight = 1;
			cc->moveLeft = 0;

			std::cout << "Right" << std::endl;
			pc->setPosition(pc->getPositionX() + vel->getVelX(), pc->getPositionY() + vel->getVelY());


		}
		else if (closestNode.type == "JumpLeft" && pc->getPositionX() > pcFlag->getPositionX()) {

			cc->setDirection(cc->Up);
			moveUp();
			cc->moveLeft = 1;
			cc->moveRight = 0;
			pc->setPosition(pc->getPositionX() + vel->getVelX(), pc->getPositionY() + vel->getVelY());

		}

	}

}
