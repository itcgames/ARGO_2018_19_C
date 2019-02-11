#include "CollisionSystem.h"

void CollisionSystem::addEntity(Entity e)
{
	entities.push_back(e);
}

void CollisionSystem::CheckCollision()
{
	for (Entity& entity : entities)
	{
		if (entity.getName() == "Player")
		{
			std::cout << "Player Properties received" << std::endl;
			posComp1 = (PositionComponent *)entity.getCompByType("Position");
			cc = (ControlComponent *)entity.getCompByType("Control");
			spriteComp = (SpriteComponent *)entity.getCompByType("Sprite");
			x1 = posComp1->getPositionX();
			y1 = posComp1->getPositionY();
			width1 = 30;// spriteComp->getWidth();
			height1 = 30;// spriteComp->getHeight();
		}
		if (entity.getName() == "Wall")
		{
			std::cout << "Wall propeties received" << std::endl;
			posComp = (PositionComponent *)entity.getCompByType("Position");
			x2 = posComp->getPositionX();
			y2 = posComp->getPositionY();
			width2 = 30;
			height2 = 30;
		}
		if (entity.getName() == "Flag")
		{
			std::cout << "Wall propeties received" << std::endl;
			posComp2 = (PositionComponent *)entity.getCompByType("Position");
			spriteComp2 = (SpriteComponent *)entity.getCompByType("Sprite");
	
		}
	}
	
	squareCollision(x1, y1, x2, y2, width1, height1, width2, height2);

	posComp2->setPosition(posComp1->getPositionX(), posComp1->getPositionY() - 50);

	/*if (squareCollision(x1, y1, posComp2->getPositionX(), posComp2->getPositionY(), width1, height1, spriteComp2->getTexture().getWidth() / 8, spriteComp2->getTexture().getWidth() / 2)) {

		std::cout << "COLLIDEEEEDDD" << std::endl;
	}*/
}

bool CollisionSystem::squareCollision(float x1, float y1, float x2, float y2, float width1, float height1, float width2, float height2)
{
	float w = 0.5*(width1 + width2);
	float h = 0.5*(height1 + height2);
	float dx = (x1 + ( width1 / 2 )) - (x2 + (width2 / 2));
	float dy = (y1 + (height1 / 2 )) - (y2 + (height2 / 2));
	cc->stopFall = false;
	if (abs(dx) <= w && abs(dy) <= h)
	{
		float wy = w * dy;
		float hx = h * dx;

		if (wy > hx)
		{
			if (wy > -hx)
			{
				//top
				cc->stopFall = false;
				posComp1->setPosition(x1, y1 - height1);
			}
			else if (wy < -hx)
			{
				//left
				posComp1->setPosition(x2-width1, y1);
			}
			
		}
		if (wy < hx)
		{
			if (wy > -hx)
			{
				//Right 
				posComp1->setPosition(x2 + width1, y1);
			}
			else if (wy < -hx)
			{
				//Bottom
			}
		}
		return true;
		
	}
		return false;
}

void CollisionSystem::update()
{
	CheckCollision();
}


