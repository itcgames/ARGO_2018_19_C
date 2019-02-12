#include "CollisionSystem.h"

void CollisionSystem::addEntity(Entity e)
{
	entities.push_back(e);
}

void CollisionSystem::CheckCollision(level &level)
{
	for (Entity& entity : entities)
	{
		if (entity.getName() == "Player")
		{
		
			posComp1 = (PositionComponent *)entity.getCompByType("Position");
			cc = (ControlComponent *)entity.getCompByType("Control");
			spriteComp = (SpriteComponent *)entity.getCompByType("Sprite");
			x1 = posComp1->getPositionX();
			y1 = posComp1->getPositionY();
			width1 =  spriteComp->getWidth();
			height1 =  spriteComp->getHeight();
		}
		if (entity.getName() == "Wall")
		{
			
			posComp = (PositionComponent *)entity.getCompByType("Position");
			x2 = posComp->getPositionX();
			y2 = posComp->getPositionY();
			width2 = 30;
			height2 = 30;
		}
	}
	
	//squareCollision(x1, y1, x2, y2, width1, height1, width2, height2);
	tileCollision(x1, y1, width1, height1, level);
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
				posComp1->setPosition(x1, m_tiles.tiles[i].y - height1);
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
			cc->OnPlatform = false;
			cc->stopFall = false;
			posComp1->setPosition(m_tiles.m_wall[i].x + m_tiles.m_wall[i].width, y1);
		}

		//left of tile
		else if (x + width >= m_tiles.m_wall[i].x &&
			x + width < m_tiles.m_wall[i].x + m_tiles.m_wall[i].width &&
			y + height >= m_tiles.m_wall[i].y &&
			y <= m_tiles.m_wall[i].y + m_tiles.m_wall[i].height)
		{
			
			cc->moveRight = 0;
			cc->OnPlatform = false;
			cc->stopFall = false;
			posComp1->setPosition(m_tiles.m_wall[i].x - width1, y1);
		}
	}

	for (int i = 0; i < m_tiles.m_ceiling.size(); i++)
	{
		
		if (y - height >= m_tiles.m_ceiling[i].y &&
			y - height <= m_tiles.m_ceiling[i].y + m_tiles.m_ceiling[i].height &&
			x >= m_tiles.m_ceiling[i].x - width &&
			x <= m_tiles.m_ceiling[i].x + m_tiles.m_ceiling[i].width)
		{
			if(cc->getDirection() == cc->Up)
				std::cout << "Ceiling HIT" << std::endl;
				cc->stopFall = false;
				cc->OnPlatform = false;
				cc->ceilingHit = true;
				//posComp->setPosition(x, m_tiles.m_ceiling[i].y+height*2);
				break;
			
		}
	}
		

}

void CollisionSystem::update(level &level)
{
	CheckCollision(level);
}


