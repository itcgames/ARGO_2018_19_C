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
		AmmoComponent* ammoComp = (AmmoComponent*)entity.getCompByType("Ammo");
		PositionComponent* posComp = (PositionComponent*)entity.getCompByType("Position");
	
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
			}
			if (e.key.keysym.sym == SDLK_SPACE )
			{
				//amComp->idle();
				int posX = posComp->getPositionX();
				int posY = posComp->getPositionY();
				//get current ammo amount and if not 0 place bomb
				if (ammoComp->getAmmo() > 0) {
					ammoComp->dropProjectile(posX, posY);
					//take one ammo away
					int current = ammoComp->getAmmo();
					current--;
					ammoComp->setAmmo(current);
				}
				
			}
			if (e.key.keysym.sym == SDLK_a)
			{
				//amComp->idle();
				int posX = posComp->getPositionX();
				int posY = posComp->getPositionY();
				//get current ammo amount and if not 0 place bomb
				if (ammoComp->getSeekerAmmo() > 0) {
					ammoComp->dropSeeker(posX, posY);
					//take one ammo away
					int current = ammoComp->getSeekerAmmo();
					current = 0;
					ammoComp->setSeekerAmmo(current);
				}
			}

			if (e.key.keysym.sym == SDLK_s && pressed == false)
			{
				controlComp->attack = true;
				pressed = true;
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
		if (e.key.keysym.sym == SDLK_SPACE)
		{
			pressed = false;
		}


	}
}

void ControlSystem::idle() {
	if (controlComp->alive)
	{
		controlComp->setDirection(controlComp->Idle);

	}
}