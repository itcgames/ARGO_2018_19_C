#include "RenderSystem.h"

RenderSystem::RenderSystem() {

}

void RenderSystem::addEntity(Entity e) {
	entities.push_back(e);
}
void RenderSystem::removeEntity(std::string ID) {

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




void RenderSystem::update(SDL_Renderer *m_renderer, float dt) {

	time = time + dt;

	for (Entity & entity : entities) {

		if (entity.getName() == "Flag")
		{
			SpriteComponent *sc = (SpriteComponent*)entity.getCompByType("Sprite");
			PositionComponent * pc = (PositionComponent*)entity.getCompByType("Position");

			sc->setPosition(pc->getPositionX(), pc->getPositionY());
			int fps = 15;
			int ticksPerFrame = 2000 / fps;
			time = time + dt;

			if (ticksPerFrame < time)
			{
				index += 1;

				if (index > 7)
				{
					index = 0;
				}
				time = 0;
			}
			sc->animate(index * 158,314,158,314,m_renderer);
			//sc->render(m_renderer, rect);
		}
		else
		{
			SpriteComponent *sc = (SpriteComponent*)entity.getCompByType("Sprite");
			PositionComponent * pc = (PositionComponent*)entity.getCompByType("Position");
			AnimationComponent * ac = (AnimationComponent*)entity.getCompByType("Animation");
			ControlComponent * cc = (ControlComponent*)entity.getCompByType("Control");
			LifeComponent * lc = (LifeComponent*)entity.getCompByType("Life");
	if (lc->getLife() != 0)
	{
			int fps = 15;
			int ticksPerFrame = 2000 / fps;
			time = time + dt;
			//SDL_Rect rect = { 0,0,0,0 };
			if (ticksPerFrame < time)
			{
				i += 1;

				if (i > 2)
				{
					i = 0;
					if (ac->m_currentState == ac->DieS)
					{
						pc->setPosition(680, 100);
						ac->idle();
						cc->alive = true;
						//newLife;
						break;
					}
				}
				time = 0;
			}

			sc->setPosition(pc->getPositionX(), pc->getPositionY());
			sc->animate(i * ac->sRect.x, ac->sRect.y, ac->sRect.w, ac->sRect.h, m_renderer);
			//sc->render(m_renderer, ac->sRect);


		}

			lc->render(m_renderer);
		}

	}

}
