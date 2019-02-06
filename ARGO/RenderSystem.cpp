#include "RenderSystem.h"

RenderSystem::RenderSystem() {

}

void RenderSystem::addEntity(Entity e) {
	entities.push_back(e);
}

void RenderSystem::update(SDL_Renderer *m_renderer) {


	for (Entity & entity : entities) {

		/*for (Component * component : entity.getComponents()) {
			if (component->getID() == "Position") {
				
				pc = dynamic_cast<PositionComponent*>(component);
			}
			if (component->getID() == "Sprite") {

				sc = dynamic_cast<SpriteComponent*>(component);
			}
			
		}*/

		SpriteComponent *sc = (SpriteComponent*)entity.getCompByType("Sprite");
		PositionComponent * pc = (PositionComponent*)entity.getCompByType("Position");

		sc->setPosition(pc->getPositionX(), pc->getPositionY());

		sc->render(m_renderer);

		//sc->getTexture().render(pc->getPositionX(), pc->getPositionY());

		//sc.

		//sc.render(pc->getPositionX(), pc->getPositionY(), m_renderer);
		
	}

}