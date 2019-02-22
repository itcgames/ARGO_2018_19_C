#include "LifeSystem.h"

LifeSystem::LifeSystem() {

}

void LifeSystem::addEntity(Entity e) {
	entities.push_back(e);
}

void LifeSystem::removeEntity(std::vector<Entity>&entities, std::string ID) {

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


void LifeSystem::update( float dt) {

	time = time + dt;

	for (Entity & entity : entities) {

		
		LifeComponent *lc = (LifeComponent*)entity.getCompByType("Life");

		if (lc->getLife() <= 0 && lc->dead == false) {

			deadEntities.push_back(entity);
			lc->dead = true;
		}

	}

	if (deadEntities.size() == 3) {

		//m_game->setGameState(GameState::GameOverScreen);
	}

}