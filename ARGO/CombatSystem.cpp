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


void CombatSystem::update(float dt, std::string playerID)
{

	time = time + dt;

	
	
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
	if (playerID == "Player") {

		updateAI();

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

void CombatSystem::updateAI() {


	for (Entity& entity1 : entities)
	{
		AiComponent* ai = (AiComponent*)entity1.getCompByType("Ai");

		m_currentAIName = entity1.getName();

		if (ai != nullptr)
		{
			LifeComponent * lc = (LifeComponent*)entity1.getCompByType("Life");

			if (lc->getLife() != 0) {

				posComp = (PositionComponent *)entity1.getCompByType("Position");
				cc = (ControlComponent *)entity1.getCompByType("Control");
				spriteComp = (SpriteComponent *)entity1.getCompByType("Sprite");
				score = (ScoreComponent*)entity1.getCompByType("Score");
			}

			for (Entity& entity2 : entities)
			{

				if (entity2.getName() != "Flag" && entity2.getName() != m_currentAIName)
				{

					LifeComponent * lc = (LifeComponent*)entity2.getCompByType("Life");

					if (lc->getLife() != 0) {

						posComp2 = (PositionComponent *)entity2.getCompByType("Position");
						spriteComp2 = (SpriteComponent *)entity2.getCompByType("Sprite");
						cc2 = (ControlComponent *)entity2.getCompByType("Control");
						vel = (VelocityComponent*)entity2.getCompByType("Vel");
						ai2 = (AiComponent*)entity2.getCompByType("Ai");
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
							if (ai2 != NULL)
							{
								posComp2->setPosition(posComp2->getPositionX() + vel->getVelX() - 100, posComp2->getPositionY() + vel->getVelY() - 90);
							}
							else
							{
								posComp2->setPosition(posComp2->getPositionX() - 100, posComp2->getPositionY() - 90);
							}
							

						}
						else {
							/*	vel->setVelX(+10);
							vel->setVelY(-50);*/
							if (ai2 != NULL)
							{
								posComp2->setPosition(posComp2->getPositionX() + vel->getVelX() + 100, posComp2->getPositionY() + vel->getVelY() - 90);
							}
							else
							{
								posComp2->setPosition(posComp2->getPositionX() + 100, posComp2->getPositionY() - 90);
							}
							
						}

						cc->attack = false;
					}

				}

			}
		}

		
	}

	


}
bool CombatSystem::AABB(float x1, float y1, float x2, float y2, float width1, float height1, float width2, float height2)
{
	return(abs(x1 - x2) * 2 < (width1 + width2)) &&
		(abs(y1 - y2) * 2 < (height1 + height2));
}


