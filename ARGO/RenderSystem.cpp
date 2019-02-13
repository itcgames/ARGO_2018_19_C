#include "RenderSystem.h"

RenderSystem::RenderSystem() {

}

void RenderSystem::addEntity(Entity e) {
	entities.push_back(e);
}

void RenderSystem::update(SDL_Renderer *m_renderer, float dt) {

	time = time + dt;

	for (Entity & entity : entities) {

		


		if (entity.getName() == "Flag")
		{
			SpriteComponent *sc = (SpriteComponent*)entity.getCompByType("Sprite");
			PositionComponent * pc = (PositionComponent*)entity.getCompByType("Position");

			sc->setPosition(pc->getPositionX(), pc->getPositionY());

			int fps = 15;
			int ticksPerFrame = 1000 / fps;

			SDL_Rect rect = { 0,0,0,0 };

			sc->animate(index * 158,314,158,314,m_renderer);
			//sc->render(m_renderer, rect);

			if (ticksPerFrame < time)
			{
				index += 1;

				if (index > 7)
				{
					index = 0;
				}

				time = 0;
			}
		}
		else
		{
			SpriteComponent *sc = (SpriteComponent*)entity.getCompByType("Sprite");
			PositionComponent * pc = (PositionComponent*)entity.getCompByType("Position");
			AnimationComponent * ac = (AnimationComponent*)entity.getCompByType("Animation");

			sc->setPosition(pc->getPositionX(), pc->getPositionY());

			sc->render(m_renderer, ac->sRect);
		}

	}

}