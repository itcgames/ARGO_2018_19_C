#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem() {

}

void PhysicsSystem::addEntity(Entity e) {
	entities.push_back(e);
}

void PhysicsSystem::update() {


	//std::cout << "PHYSICS SYSTEM:" << std::endl;
	for (Entity & entity : entities) {

		cc = (ControlComponent*)entity.getCompByType("Control");
		pc = (PositionComponent*)entity.getCompByType("Position");
		Coll = (CollisionComponent *)entity.getCompByType("Collision");

		if (cc->getDirection() == cc->Left)
		{
			moveLeft();
		}
		if (cc->getDirection() == cc->Right)
		{
			moveRight();
			
		}

		if (cc->getDirection() == cc->Up) {
			moveUp();
		}
		if (cc->moveLeft == 0 && cc->moveRight == 0)
		{
			vecX = 0;

		}
		
		//std::cout << vecY <<std::endl;
		if( pc->getPositionY() >= 500)
		{
			cc->stopFall = true;
		}
		if (!cc->stopFall) {
			
			posY = pc->getPositionY();
			posX = pc->getPositionX();
			vecY++;
			posY += vecY;
			pc->setPosition(posX, posY);
			collision = 0;
		}
		/*else if (pc->getPositionY() < 440 && !cc->stopFall) 
		{

			posY = pc->getPositionY();
			posX = pc->getPositionX();
			vecY++;
			posY += vecY;
			pc->setPosition(posX, posY);
			collision = 0;
		}*/
		else {
			vecY = 0;
			collision = 1;
		}
		/*if (cc->stopFall)
		{
			vecY = 0;
		}
		*/
		int posX = pc->getPositionX();
		int posY = pc->getPositionY();
		posX += vecX;
		pc->setPosition(posX, posY);


	}

	

	//std::cout << std::endl;
	//std::cout << std::endl;

}
void PhysicsSystem::moveLeft() {

	if (vecX > -maxX && cc->moveLeft == 1)
	{
		int posX = pc->getPositionX();
		int posY = pc->getPositionY();
		vecX = -7;
		posX += vecX;

		pc->setPosition(posX, posY);
	}
}
void PhysicsSystem::moveRight() {
	
	if (vecX < maxX && cc->moveRight == 1)
	{
		int posX = pc->getPositionX();
		int posY = pc->getPositionY();
		vecX = 7;
		posX += vecX;
		pc->setPosition(posX, posY);
	}
	

}
void PhysicsSystem::moveUp() {

	if (cc->jump == 0 && collision == true)
	{
		int posX = pc->getPositionX();
		int posY = pc->getPositionY();
		vecY = -20;
		posY += vecY;
		posX += vecX;
		pc->setPosition(posX, posY);
		

		cc->jump = 1;
	}
	

}
void PhysicsSystem::moveDown() {
	int posX = pc->getPositionX();
	int posY = pc->getPositionY();
	vecY = +7;
	posY += vecY;
	pc->setPosition(posX, posY);

}

