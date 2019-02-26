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


void CombatSystem::CheckCollision(int index, Client & client)
{

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

					int hadFlag = 0;
					if (cc2->hasFlag && pickup->getState() == pickup->NotCollectable)
					{
						cc2->hasFlag = false;
						pickup->setState(pickup->Collectable);

						hadFlag = 1;
					}

					if (posComp->getPositionX() > posComp2->getPositionX())
					{
						/*	vel->setVelX(- 10);
						vel->setVelY(- 50);*/
						posComp2->setPosition(posComp2->getPositionX() + vel->getVelX() - 100, posComp2->getPositionY() + vel->getVelY() - 90);

						if (entity.getName() == "Player")
						{
							std::cout << "Left: " << 0 << std::endl;
							client.sendMsg("Kicked I: 0 D: 0 F:" + std::to_string(hadFlag));
						}
						else if (entity.getName() == "Player2")
						{
							std::cout << "Left: " << 1 << std::endl;
							client.sendMsg("Kicked I: 1 D: 0 F:" + std::to_string(hadFlag));
						}
						else if (entity.getName() == "Player3")
						{
							std::cout << "Left: " << 2 << std::endl;
							client.sendMsg("Kicked I: 2 D: 0 F:" + std::to_string(hadFlag));
						}
						else if (entity.getName() == "Player4")
						{
							std::cout << "Left: " << 3 << std::endl;
							client.sendMsg("Kicked I: 3 D: 0 F:" + std::to_string(hadFlag));
						}

					}
					else {
						/*	vel->setVelX(+10);
						vel->setVelY(-50);*/
						posComp2->setPosition(posComp2->getPositionX() + vel->getVelX() + 100, posComp2->getPositionY() + vel->getVelY() - 90);

						if (entity.getName() == "Player")
						{
							std::cout << "Right: " << 0 << std::endl;
							client.sendMsg("Kicked I: 0 D: 1 F:" + std::to_string(hadFlag));
						}
						else if (entity.getName() == "Player2")
						{
							std::cout << "Right: " << 1 << std::endl;
							client.sendMsg("Kicked I: 1 D: 1 F:" + std::to_string(hadFlag));
						}
						else if (entity.getName() == "Player3 F:" + std::to_string(hadFlag))
						{
							std::cout << "Right: " << 2 << std::endl;
							client.sendMsg("Kicked I: 2 D: 1 F:" + std::to_string(hadFlag));
						}
						else if (entity.getName() == "Player4")
						{
							std::cout << "Right: " << 3 << std::endl;
							client.sendMsg("Kicked I: 3 D: 1 F:" + std::to_string(hadFlag));
						}
					}

					cc->attack = false;
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


void CombatSystem::update(int playerindex, Client & client)
{
	CheckCollision(playerindex, client);
}


