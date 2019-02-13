#include "CombatSystem.h"

void CombatSystem::addEntity(Entity e)
{
	entities.push_back(e);
}

void CombatSystem::CheckCollision(float dt)
{

	time = time + dt;
	for (Entity& entity : entities)
	{
		if (entity.getName() == "Player")
		{

			posComp = (PositionComponent *)entity.getCompByType("Position");
			cc = (ControlComponent *)entity.getCompByType("Control");
			spriteComp = (SpriteComponent *)entity.getCompByType("Sprite");
		
		}
		else if(entity.getName() == "Flag")
		{
			posComp1 = (PositionComponent *)entity.getCompByType("Position");
			spriteComp1 = (SpriteComponent *)entity.getCompByType("Sprite");
			cc1 = (ControlComponent *)entity.getCompByType("Control");
			pickup = (PickUpComponent *)entity.getCompByType("PickUp");
		}
		else 
		{

			posComp2 = (PositionComponent *)entity.getCompByType("Position");
			cc2 = (ControlComponent *)entity.getCompByType("Control");
			spriteComp2 = (SpriteComponent *)entity.getCompByType("Sprite");

		}

		if (posComp1 != NULL && posComp2 != NULL) {

			if (cc->attack) {
				cc->attack = false;
				if (AABB(posComp->getPositionX(), posComp->getPositionY(), posComp2->getPositionX(), posComp2->getPositionY(),
					spriteComp->getWidth(), spriteComp->getHeight(), spriteComp2->getWidth(), spriteComp2->getHeight())) {

					if (cc2->hasFlag)
					{
						cc2->hasFlag = false;
						pickup->setState(pickup->Collectable);
					}

					if (posComp->getPositionX() < posComp2->getPositionX())
					{
						posComp2->setPosition(posComp2->getPositionX() + 100, posComp2->getPositionY() - 100);
					}
					else
					{
						posComp2->setPosition(posComp2->getPositionX() - 100, posComp2->getPositionY() - 100);
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


void CombatSystem::update(float dt)
{
	CheckCollision(dt);
}


