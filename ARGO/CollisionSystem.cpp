#include "CollisionSystem.h"

void CollisionSystem::addEntity(Entity e)
{
	entities.push_back(e);
}

void CollisionSystem::removeEntity(std::string ID) {

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

bool CollisionSystem::getInvincible()
{
	return collide->m_Invincible;
}

void CollisionSystem::ActivateInvincible(std::string ID)
{
	for (Entity & entity : entities)
	{
		if (entity.getName() == ID)
		{
			collide = (CollisionComponent*)entity.getCompByType("Collision");
			collide->m_Invincible = true;
		}

	}
}

void CollisionSystem::setInvincible(float dt, CollisionComponent* m_collide)
{
	timer += dt;
	int fps = 1;
	int ticksPerFrame = 1000 / fps;
	if (m_collide->m_Invincible)
	{
		if (ticksPerFrame<timer)
		{
			count += 1;
			timer = 0;
			std::cout << "INVINCIBLE" << std::endl;
		}
		if (count >= 10)
		{
			m_collide->m_Invincible = false;
			std::cout << "INVINCIBLE OVER" << std::endl;
			count = 0;
		}
	}

}

std::vector<std::string> CollisionSystem::getEntityID()
{
	//only returns first name
	std::vector<std::string> v;
	for (Entity & entity : entities) {
		if(entity.getName()!="Flag")
		v.push_back(entity.getName());
	}
	return v;
}

void CollisionSystem::FloatFlag(PositionComponent* pos)
{
	if (pos->getPositionX() < 1400 && moveRight)
	{
		pos->setPosition(pos->getPositionX() + 0.3, pos->getPositionY());
	}
	else
		moveRight = false;
	
	if (pos->getPositionX() > 50 && !moveRight)
	{
		pos->setPosition(pos->getPositionX() - 0.3, pos->getPositionY());
	}
	else
		moveRight = true;

	if (pos->getPositionY() < 750 && moveDown)
	{
		pos->setPosition(pos->getPositionX(), pos->getPositionY() + 0.3);
	}
	else
		moveDown = false;

	if (pos->getPositionY() > 50 && !moveDown)
	{
		pos->setPosition(pos->getPositionX(), pos->getPositionY() - 0.3);
	}
	else
		moveDown = true;
}

void CollisionSystem::resetScore(std::string id)
{
	for (Entity& entity : entities)
	{
		if (id != entity.getName() && entity.getName() !="Flag")
		{
			score = (ScoreComponent*)entity.getCompByType("Score");
			score->setScore(0);
		}
	}
}

void CollisionSystem::CheckCollision(level &level, float dt, std::string playerID)

{

	time = time + dt;
	for (Entity& entity : entities)
	{

		if (entity.getName() == "Player" || entity.getName() == "Player2" || entity.getName() == "Player3" || entity.getName() == "Player4")
		{

			LifeComponent * lc = (LifeComponent*)entity.getCompByType("Life");

			if (lc->getLife() != 0) {

				posComp1 = (PositionComponent *)entity.getCompByType("Position");
				cc = (ControlComponent *)entity.getCompByType("Control");
				spriteComp = (SpriteComponent *)entity.getCompByType("Sprite");
				score = (ScoreComponent*)entity.getCompByType("Score");
				ac = (AnimationComponent*)entity.getCompByType("Animation");
				collide = (CollisionComponent*)entity.getCompByType("Collision");
				x1 = posComp1->getPositionX();
				y1 = posComp1->getPositionY();
				width1 = spriteComp->getWidth();
				height1 = spriteComp->getHeight();
				tileCollision(x1, y1, width1, height1, level, lc);
				Teleport(x1, y1, width1, height1, level);

				if (entity.getName() != playerID) {
					//nodeCollision(level, posComp1->getPositionX(), posComp1->getPositionY(), spriteComp->getWidth(), spriteComp->getHeight());
				}
				
				setInvincible(dt, collide);

			}


		}
		else if (entity.getName() == "Flag")
		{
			//std::cout << "Wall propeties received" << std::endl;
			posComp2 = (PositionComponent *)entity.getCompByType("Position");
			spriteComp2 = (SpriteComponent *)entity.getCompByType("Sprite");
			pickup = (PickUpComponent *)entity.getCompByType("PickUp");

		}

		

		if (posComp1 != NULL && posComp2 != NULL) {
			if (AABB(posComp1->getPositionX(), posComp1->getPositionY(), posComp2->getPositionX(), posComp2->getPositionY(),
				spriteComp->getWidth(), spriteComp->getHeight(), spriteComp2->getWidth(), spriteComp2->getHeight())) {

				if (pickup->getState() == pickup->Collectable)
				{
					cc->hasFlag = true;
					pickup->setState(pickup->NotCollectable);
				}

				if (cc->hasFlag == true && pickup->getState() == pickup->NotCollectable)
				{
					posComp2->setPosition(posComp1->getPositionX() + spriteComp2->getHeight() / 6, posComp1->getPositionY() - spriteComp2->getHeight() / 2);
					int fps = 1;
					int ticksPerFrame = 1000 / fps;

					if (ticksPerFrame < time)
					{
						if (score != NULL)
						{
							score->setScore(score->getScore() + 1);
						}

						time = 0;
					}
				}

			}
			else
				FloatFlag(posComp2);
		}
	}
}


bool CollisionSystem::AABB(float x1, float y1, float x2, float y2, float width1, float height1, float width2, float height2)
{
	return(abs(x1 - x2) * 2 < (width1 + width2)) &&
		(abs(y1 - y2) * 2 < (height1 + height2));
}

void CollisionSystem::nodeCollision(level &level, float x, float y, float width, float height)
{
	for (int i = 0; i < level.m_nodes.size(); i++) {

		if (AABB(x, y, level.m_nodes[i].x, level.m_nodes[i].y, width, height, level.m_nodes[i].width, level.m_nodes[i].height)) {

			if (level.m_nodes[i].type == "JumpRight") {

				cc->setDirection(cc->Up);
				cc->jump = 0;
				cc->moveRight = 1;
				std::cout << "Right" << std::endl;
				
			}
			else if (level.m_nodes[i].type == "JumpLeft") {

				cc->setDirection(cc->Up);
				cc->jump = 0;
				cc->moveLeft = 1;
				std::cout << "JUMP" << std::endl;
			}
			
		}
		else
		{
			cc->jump = 1;
		}

	}

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
		else if (wy < hx)
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

void CollisionSystem::tileCollision(float x, float y, float width, float height, level &m_tiles, LifeComponent * lc)
{
	for (int i = 0; i < m_tiles.tiles.size(); i++)
	{
		//top of object
		if (y + height >= m_tiles.tiles[i].y &&
			y + height <= m_tiles.tiles[i].y + m_tiles.tiles[i].height&&
			x > m_tiles.tiles[i].x - width &&
			x <= m_tiles.tiles[i].x + m_tiles.tiles[i].width)
		{
			if (!cc->stopFall)
			{

				cc->jump = 0;
				posComp1->setPosition(x, m_tiles.tiles[i].y - height1);
				cc->stopFall = true;
				cc->OnPlatform = true;
				break;
			}
		}
		else
		{
			cc->OnPlatform = false;
			cc->stopFall = false;
		}

	}

	for (int i = 0; i < m_tiles.m_wall.size(); i++)
	{
		//right of tile
		if (x <= m_tiles.m_wall[i].x + m_tiles.m_wall[i].width&&
			x >= m_tiles.m_wall[i].x &&
			y + height >= m_tiles.m_wall[i].y &&
			y <= m_tiles.m_wall[i].y + m_tiles.m_wall[i].height)
		{

			cc->moveLeft = 0;
			posComp1->setPosition(m_tiles.m_wall[i].x + width, y);
		}

		//left of tile
		else if (x + width >= m_tiles.m_wall[i].x &&
			x + width < m_tiles.m_wall[i].x + m_tiles.m_wall[i].width &&
			y + height >= m_tiles.m_wall[i].y &&
			y <= m_tiles.m_wall[i].y + m_tiles.m_wall[i].height)
		{
			cc->moveRight = 0;
			posComp1->setPosition(m_tiles.m_wall[i].x - width, y);
		}
	}

	for (int i = 0; i < m_tiles.m_ceiling.size(); i++)
	{

		if (y >= m_tiles.m_ceiling[i].y &&
			y <= m_tiles.m_ceiling[i].y + m_tiles.m_ceiling[i].height &&
			x >= m_tiles.m_ceiling[i].x - width &&
			x <= m_tiles.m_ceiling[i].x + m_tiles.m_ceiling[i].width)
		{
			if (cc->getDirection() == cc->Idle)
			{
				cc->stopFall = false;
				cc->OnPlatform = false;
				cc->ceilingHit = true;
				break;
			}

		}
	}

	for (int i = 0; i < m_tiles.m_killTiles.size(); i++)
	{
		if ((abs(x1 - m_tiles.m_killTiles[i].x) * 2 < (width1 + m_tiles.m_killTiles[i].width)) &&
			(abs(y1 - m_tiles.m_killTiles[i].y) * 2 < (height1 + m_tiles.m_killTiles[i].height)) && !collide->m_Invincible)
		{
			std::cout << "KILL TILES COLLIDE" << std::endl;
			ac->die();
			cc->alive = false;
			posComp1->setPosition(1000, 300);
			lc->setLifes(lc->getLife() - 1);
		}
	}

}

void CollisionSystem::Teleport(float x, float y, float width, float height, level &m_tiles)
{
	for (int i = 0; i < m_tiles.m_teleport.size(); i++)
	{
		//right of tile
		if (x <= m_tiles.m_teleport[i].x + m_tiles.m_teleport[i].width&&
			x >= m_tiles.m_teleport[i].x &&
			y + height >= m_tiles.m_teleport[i].y &&
			y <= m_tiles.m_teleport[i].y + m_tiles.m_teleport[i].height)
		{
			posComp1->setPosition(m_tiles.m_teleport[1].x - width, m_tiles.m_teleport[1].y);
		}

		//left of tile
		else if (x + width >= m_tiles.m_teleport[i].x &&
			x + width < m_tiles.m_teleport[i].x + m_tiles.m_teleport[i].width &&
			y + height >= m_tiles.m_teleport[i].y &&
			y <= m_tiles.m_teleport[i].y + m_tiles.m_teleport[i].height)
		{
			posComp1->setPosition(m_tiles.m_teleport[0].x + width, m_tiles.m_teleport[0].y);
		}
	}
}

