#include "ControlSystem.h"

ControlSystem::ControlSystem() {

}

void ControlSystem::addEntity(Entity e) {
	entities.push_back(e);
}

void ControlSystem::input(SDL_Event &e) {

	for (Entity& entity : entities) 
	{
		
		controlComp = (ControlComponent*)entity.getCompByType("Control");
		amComp = (AnimationComponent*)entity.getCompByType("Animation");
	
		switch (e.type)
		{
		case SDL_KEYDOWN:

			if (e.key.keysym.sym == SDLK_UP)
			{
				controlComp->setDirection(controlComp->Up);
				AudioManager::Instance()->PlaySFX("Jump", 0);
			}
			if (e.key.keysym.sym == SDLK_LEFT)
			{
				controlComp->setDirection(controlComp->Left);
				controlComp->moveLeft = 1;
			}
			if (e.key.keysym.sym == SDLK_RIGHT)
			{
				controlComp->setDirection(controlComp->Right);
				controlComp->moveRight = 1;
				//amComp->rightJump();
			}
			if (e.key.keysym.sym == SDLK_SPACE)
			{
				//amComp->idle();
			}

		}
	}


	

}
void ControlSystem::keyUp(SDL_Event &e) {

	switch (e.type)
	{

	case SDL_KEYUP:
		
		if (e.key.keysym.sym == SDLK_UP)
		{
			controlComp->jump = 0;
		}
		if (e.key.keysym.sym == SDLK_RIGHT)
		{
			controlComp->moveRight = 0;
		}
		if (e.key.keysym.sym == SDLK_LEFT)
		{
			controlComp->moveLeft = 0;
		}


	}
}

void ControlSystem::idle() {

	controlComp->setDirection(controlComp->Idle);
}