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
			posComp = (PositionComponent *)entity.getCompByType("Position");
			//spriteComp = (SpriteComponent *)entity.getCompByType("Sprite");
			x1 = posComp->getPositionX();
			y1 = posComp->getPositionY();
			width1 = 20; //spriteComp->getTexture().getWidth();
			height1 = 20; //spriteComp->getTexture().getHeight();
		}
		if (entity.getName() == "Wall")
		{
			std::cout << "Wall propeties received" << std::endl;
			posComp = (PositionComponent *)entity.getCompByType("Position");
			x2 = posComp->getPositionX();
			y2 = posComp->getPositionY();
			width2 = 30;//spriteComp->getTexture().getWidth();
			height2 = 30; //spriteComp->getTexture().getHeight();
		}
	}
	collide->squareCollision(x1, y1, x2, y2, width1, height1, width2, height2);
}

void CollisionSystem::update()
{
	CheckCollision();
}