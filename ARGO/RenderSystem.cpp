#include "RenderSystem.h"

RenderSystem::RenderSystem() {

}

void RenderSystem::addEntity(Entity e) {
	entities.push_back(e);
}

void RenderSystem::update(SDL_Renderer *m_renderer) {


	std::cout << "RENDER SYSTEM:" << std::endl;
	for (Entity & entity : entities) {


		SpriteComponent *sc = (SpriteComponent*)entity.getCompByType("Sprite");
		PositionComponent * pc = (PositionComponent*)entity.getCompByType("Position");

		sc->setPosition(pc->getPositionX(), pc->getPositionY());

		sc->render(m_renderer);

		
		
	}
	std::cout << std::endl;
	std::cout << std::endl;

}