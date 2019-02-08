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
		ac = (AnimationComponent*)entity.getCompByType("Animation");
		
		//collide

		//std::cout << vecY <<std::endl;

		if (pc->getPositionY() < 200 - ac->sRect.h) {

			posY = pc->getPositionY();
			posX = pc->getPositionX();
			vecY++;
			posY += vecY;
			pc->setPosition(posX, posY);
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
			vecY = 0;
			collision = 1;

			if (ac->m_currentState == ac->jumpLeftS || ac->m_currentState == ac->jumpRightS)
			{
				ac->idle();
			}

		}

		int posX = pc->getPositionX();
		int posY = pc->getPositionY();
		posX += vecX;
		pc->setPosition(posX, posY);


		if (cc->getDirection() == cc->Left)
		{
			//if(!collide)
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
			cc->setDirection(cc->Idle);
			vecX = 0;
			ac->idle();

		}
		


	}


}
void PhysicsSystem::moveLeft() {

	if (vecX > -maxX && cc->moveLeft == 1)
	{
		ac->left();
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
		ac->right();
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


