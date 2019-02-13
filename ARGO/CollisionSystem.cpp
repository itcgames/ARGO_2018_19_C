#include "CollisionSystem.h"

void CollisionSystem::addEntity(Entity e)
{
	entities.push_back(e);
}

void CollisionSystem::CheckCollision(level &level, float dt)
{

	time = time + dt;
	for (Entity& entity : entities)
	{
		if (entity.getName() == "Player" || entity.getName() == "Player2" || entity.getName() == "Player3" || entity.getName() == "Player4")
		{
			posComp1 = (PositionComponent *)entity.getCompByType("Position");
			cc = (ControlComponent *)entity.getCompByType("Control");
			spriteComp = (SpriteComponent *)entity.getCompByType("Sprite");
			score = (ScoreComponent*)entity.getCompByType("Score");
			x1 = posComp1->getPositionX();
			y1 = posComp1->getPositionY();
			width1 =  spriteComp->getWidth();
			height1 =  spriteComp->getHeight();
			tileCollision(x1, y1, width1, height1, level);
			Teleport(x1, y1, width1, height1, level);

			if (entity.getName() == "Flag")
			{
				posComp2 = (PositionComponent *)entity.getCompByType("Position");
				spriteComp2 = (SpriteComponent *)entity.getCompByType("Sprite");


				if (AABB(posComp1->getPositionX(), posComp1->getPositionY(), posComp2->getPositionX(), posComp2->getPositionY(),
					spriteComp->getWidth(), spriteComp->getHeight(), spriteComp2->getWidth(), spriteComp2->getHeight())) {

					posComp2->setPosition(posComp1->getPositionX() + spriteComp2->getWidth() / 6, posComp1->getPositionY() - spriteComp2->getHeight() / 2);
					int fps = 1;
					int ticksPerFrame = 1000 / fps;

					if (ticksPerFrame < time)
					{
						score->setScore(score->getScore() + 1);

						time = 0;
					}

					std::cout << "Score: " << score->getScore() << std::endl;


				}
			}
		}
	}		
}


bool CollisionSystem::AABB(float x1, float y1, float x2, float y2, float width1, float height1, float width2, float height2)
{
	return(abs(x1 - x2) * 2 < (width1 + width2)) &&
		(abs(y1 - y2) * 2 < (height1 + height2));
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

void CollisionSystem::tileCollision(float x, float y, float width, float height, level &m_tiles)
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
				std::cout << "Ceiling HIT" << std::endl;
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
			(abs(y1 - m_tiles.m_killTiles[i].y) * 2 < (height1 + m_tiles.m_killTiles[i].height)))
		{
			std::cout << "KILL TILES COLLIDE" << std::endl;
			posComp1->setPosition(680, 100);
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

void CollisionSystem::update(level &level,float dt)
{
	CheckCollision(level, dt);
}
