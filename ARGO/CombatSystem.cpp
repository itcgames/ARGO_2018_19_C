#include "CombatSystem.h"

void CombatSystem::addEntity(Entity e)
{
	entities.push_back(e);
}

void CombatSystem::removeEntity(std::string ID) {

	
	std::vector<Entity>::iterator iter;

	for (iter = entities.begin(); iter != entities.end(); ) {
		if (iter->getName() == ID) {
			iter = entities.erase(iter);
		}
		else {
			++iter;
		}
	}
}


void CombatSystem::CheckCollision(float dt, int index)
{

	time = time + dt;
	
	if (index > 0)
	{
		playerID = "Player" + std::to_string(index + 1);
	}
	else {
		playerID = "Player";
	}
	
	for (Entity& entity : entities)
	{

		
		if (entity.getName() == playerID)
		{

			LifeComponent * lc = (LifeComponent*)entity.getCompByType("Life");

			if (lc->getLife() != 0) {

				posComp = (PositionComponent *)entity.getCompByType("Position");
				cc = (ControlComponent *)entity.getCompByType("Control");
				spriteComp = (SpriteComponent *)entity.getCompByType("Sprite");
				score = (ScoreComponent*)entity.getCompByType("Score");
			}
		
		}
		else if (entity.getName() == "Flag")
		{
			pickup = (PickUpComponent *)entity.getCompByType("PickUp");
		}
	
	}

	if (cc->attack) {
		
		for (Entity& entity : entities)
		{

			if (entity.getName() != playerID && entity.getName() != "Flag")
			{

				LifeComponent * lc = (LifeComponent*)entity.getCompByType("Life");

				if (lc->getLife() != 0) {

					posComp2 = (PositionComponent *)entity.getCompByType("Position");
					spriteComp2 = (SpriteComponent *)entity.getCompByType("Sprite");
					cc2 = (ControlComponent *)entity.getCompByType("Control");
					vel = (VelocityComponent*)entity.getCompByType("Vel");
				}

				if (AABB(posComp->getPositionX(), posComp->getPositionY(), posComp2->getPositionX(), posComp2->getPositionY(),
					spriteComp->getWidth(), spriteComp->getHeight(), spriteComp2->getWidth(), spriteComp2->getHeight())) {


					if (cc2->hasFlag && pickup->getState() == pickup->NotCollectable)
					{
						cc2->hasFlag = false;
						pickup->setState(pickup->Collectable);
					}

					if (posComp->getPositionX() > posComp2->getPositionX())
					{
						/*	vel->setVelX(- 10);
						vel->setVelY(- 50);*/
						posComp2->setPosition(posComp2->getPositionX() + vel->getVelX() - 100, posComp2->getPositionY() + vel->getVelY() - 90);

					}
					else {
						/*	vel->setVelX(+10);
						vel->setVelY(-50);*/
						posComp2->setPosition(posComp2->getPositionX() + vel->getVelX() + 100, posComp2->getPositionY() + vel->getVelY() - 90);
					}

					cc->attack = false;
				}

			}

		}

	}
			
		/*posComp2->setPosition(posComp1->getPositionX() + spriteComp2->getHeight() / 3, posComp1->getPositionY() - spriteComp2->getHeight() / 2);
		int fps = 1;
		int ticksPerFrame = 1000 / fps;

		if (ticksPerFrame < time)
		{
			score->setScore(score->getScore() + 1);

			time = 0;
		}

		std::cout << "Score: " << score->getScore() << std::endl;*/


	
}


bool CombatSystem::AABB(float x1, float y1, float x2, float y2, float width1, float height1, float width2, float height2)
{
	return(abs(x1 - x2) * 2 < (width1 + width2)) &&
		(abs(y1 - y2) * 2 < (height1 + height2));
}


void CombatSystem::update(float dt, int playerindex)
{
	CheckCollision(dt, playerindex);
}


