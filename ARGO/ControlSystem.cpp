#include "ControlSystem.h"

ControlSystem::ControlSystem() {

}

void ControlSystem::addEntity(Entity e) {
	entities.push_back(e);
}

void ControlSystem::input(SDL_Event &e) {

	for (Entity& entity : entities) {
		
		controlComp = (ControlComponent*)entity.getCompByType("Control");
		switch (e.type)
		{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				controlComp->setDirection(controlComp->Up);
				break;
			case SDLK_DOWN:
				controlComp->setDirection(controlComp->Down);
				break;
			case SDLK_LEFT:
				controlComp->setDirection(controlComp->Left);
				break;
			case SDLK_RIGHT:
				controlComp->setDirection(controlComp->Right);
				break;
			default:
				controlComp->setDirection(controlComp->Idle);
				break;

			}
		

		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				controlComp->jump = 0;
				break;
			case SDLK_LEFT:
				controlComp->moveLeft = 0;
				break;
			case SDLK_RIGHT:
				controlComp->moveRight = 0;
				break;
		
			}
			

		}
	}


	

}


void ControlSystem::idle() {

	controlComp->setDirection(controlComp->Idle);
}