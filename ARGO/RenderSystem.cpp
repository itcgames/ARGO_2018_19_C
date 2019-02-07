#include "RenderSystem.h"

RenderSystem::RenderSystem() {

}

void RenderSystem::addEntity(Entity e) {
	entities.push_back(e);
}

void RenderSystem::update(SDL_Renderer *m_renderer) {


	//std::cout << "RENDER SYSTEM:" << std::endl;
	for (Entity & entity : entities) {


		SpriteComponent *sc = (SpriteComponent*)entity.getCompByType("Sprite");
		PositionComponent * pc = (PositionComponent*)entity.getCompByType("Position");
		AnimationComponent * ac = (AnimationComponent*)entity.getCompByType("Animation");

		sc->setPosition(pc->getPositionX(), pc->getPositionY());

		sc->render(m_renderer);

		
		
	}

}