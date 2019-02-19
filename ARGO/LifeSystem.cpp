#include "LifeSystem.h"

LifeSystem::LifeSystem() {

}

void LifeSystem::addEntity(Entity e) {
	entities.push_back(e);
}

void LifeSystem::removeEntity(std::vector<Entity>&entities, std::string ID) {

	std::vector<Entity>::iterator iter = entities.begin();
	std::vector<Entity>::iterator endIter = entities.end();
	for (; iter != endIter; ++iter)
	{
		if (iter->getName() == ID)
		{
			entities.erase(iter);
		}
	}
}


void LifeSystem::update( float dt) {

	time = time + dt;

	for (Entity & entity : entities) {

		
		LifeComponent *lc = (LifeComponent*)entity.getCompByType("Life");

		if (lc->getLife() == 0) {

			removeEntity(entities, entity.getName());
		}

	}

	if (entities.size() == 1) {

		//m_game->setGameState(GameState::GameOverScreen);
	}

}