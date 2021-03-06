#include "PhysicsSystem.h"


PhysicsSystem::PhysicsSystem() {

}

void PhysicsSystem::addEntity(Entity e) {
	entities.push_back(e);
}
std::string PhysicsSystem::getEntity() {
	//only reurns first name
	for (Entity & entity : entities) {
		return entity.getName();
	}
}

Entity * PhysicsSystem::getEntityById(std::string s)
{
	for (Entity & entity : entities) {
		if (s == entity.getName())
			return &entity;
	}
	return &entities[0];
}

std::vector<std::string> PhysicsSystem::getEntityIds() {
	//only reurns first name
	std::vector<std::string> v;
	for (Entity & entity : entities) {
		v.push_back(entity.getName());
	}
	return v;
}

void PhysicsSystem::update() {


	for (Entity & entity : entities) {

		cc = (ControlComponent*)entity.getCompByType("Control");
		pc = (PositionComponent*)entity.getCompByType("Position");
		ac = (AnimationComponent*)entity.getCompByType("Animation");
		sc = (SpriteComponent*)entity.getCompByType("Sprite");

		//collide
		//Gravity
			if (!cc->stopFall && !cc->OnPlatform) {
				
				posY = pc->getPositionY();
				posX = pc->getPositionX();
				if (vecY <= 15) {
					vecY++;
				}
					
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


			Coll = (CollisionComponent *)entity.getCompByType("Collision");


			if (cc->moveLeft == 1)
			{
				//if(!collide)
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
			vecY = 5;
			posY += 10;
			cc->ceilingHit = false;
		}
		if (!cc->alive)
		{
			ac->die();
		}

		if (pc != nullptr)
		{
			if (pc->getPositionX() < 0)
			{
				pc->setPosition(70, pc->getPositionY());
			}
			else if (pc->getPositionX() > 1470)
			{
				pc->setPosition(1400, pc->getPositionY());
			}

			if (pc->getPositionY() < 0)
			{
				pc->setPosition(pc->getPositionX(), 70);
			}
			else if (pc->getPositionX() > 1470)
			{
				pc->setPosition(pc->getPositionY(), 1400);
			}
		}
	}



	//std::cout << "Vel :" << vecX<< std::endl;

}
void PhysicsSystem::speedUp(Entity * entity) {

	maxX++;
}

void PhysicsSystem::moveLeft() {

	if (vecX > -maxX )
	{
		ac->left();
		int posX = pc->getPositionX();
		int posY = pc->getPositionY();
		vecX = -7;
		posX += vecX;

		pc->setPosition(posX, posY);
		//Jamie
		cc->jump = 0;
	}
}
void PhysicsSystem::moveRight() {

	if (vecX < maxX)
	{
		ac->right();
		int posX = pc->getPositionX();
		int posY = pc->getPositionY();
		vecX = 7;
		posX += vecX;
		pc->setPosition(posX, posY);

		//jamie
		cc->jump = 0;
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
		cc->stopFall = false;
		cc->OnPlatform = false;
		cc->jump = 1;
	}


}
