#include "ControlSystem.h"

ControlSystem::ControlSystem() {


}

void ControlSystem::init()
{
	int MaxJoysticks = SDL_NumJoysticks();
	int ControllerIndex = 0;
	for (int JoystickIndex = 0; JoystickIndex < MaxJoysticks; ++JoystickIndex)
	{
		if (!SDL_IsGameController(JoystickIndex))
		{
			continue;
		}
		if (ControllerIndex >= MAX_CONTROLLERS)
		{
			break;
		}
		ControllerHandles[ControllerIndex] = SDL_GameControllerOpen(JoystickIndex);
		ControllerIndex++;
	}

	bitePoint = 5000;
}

void ControlSystem::addEntity(Entity e) {
	entities.push_back(e);
}

void bb(std::string s)
{

}

void ControlSystem::input(SDL_Event &e) {

	for (Entity& entity : entities)
	{

		controlComp = (ControlComponent*)entity.getCompByType("Control");
		amComp = (AnimationComponent*)entity.getCompByType("Animation");
		AmmoComponent* ammoComp = (AmmoComponent*)entity.getCompByType("Ammo");
		PositionComponent* posComp = (PositionComponent*)entity.getCompByType("Position");


		for (int ControllerIndex = 0;
			ControllerIndex < MAX_CONTROLLERS;
			++ControllerIndex)
		{
			if (ControllerHandles[ControllerIndex] != 0 && SDL_GameControllerGetAttached(ControllerHandles[ControllerIndex]))
			{
				// NOTE: We have a controller with index ControllerIndex.
				Up = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_UP);
				Down = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_DOWN);
				Left = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_LEFT);
				Right = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
				Start = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_START);
				Back = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_BACK);
				LeftShoulder = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
				RightShoulder = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
				AButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_A);
				BButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_B);
				XButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_X);
				YButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_Y);

				StickLeftX = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex], SDL_CONTROLLER_AXIS_LEFTX);
				StickLeftY = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex], SDL_CONTROLLER_AXIS_LEFTY);

				StickRightX = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex], SDL_CONTROLLER_AXIS_RIGHTX);
				StickRightY = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex], SDL_CONTROLLER_AXIS_RIGHTY);

				StickLT = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex], SDL_CONTROLLER_AXIS_TRIGGERLEFT);
				StickRT = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex], SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
			}
			else
			{
				// TODO: This controller is not plugged in.
			}
		}

		if (StickLeftX >= -bitePoint)
		{
			//controlComp->moveLeft = 0;
		}
		if (StickLeftX <= bitePoint)
		{
			//controlComp->moveRight = 0;
		}

		switch (e.type)
		{

		case SDL_JOYHATMOTION:
			if (Up)
			{
				//buttonUp_();
			}
			if (Down)
			{
				//buttonDown_();
			}
			if (Left)
			{
				//buttonLeft_();
			}
			if (Right)
			{
				//buttonRight_();
			}
			break;

		case SDL_JOYBUTTONDOWN:
			if (AButton)
			{
				controlComp->setDirection(controlComp->Up);
				AudioManager::Instance()->PlaySFX("Jump", 0);
			}
			if (BButton)
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
			if (XButton)
			{
				if (!pressed)
				{
					controlComp->attack = true;
					pressed = true;
				}
			}
			if (YButton)
			{
				//amComp->idle();
				int posX = posComp->getPositionX();
				int posY = posComp->getPositionY();
				//get current ammo amount and if not 0 place bomb
				if (ammoComp->getSeekerAmmo() > 0) {
					//third value is int for life span
					ammoComp->dropSeeker(posX, posY, 200);
					//take one ammo away
					int current = ammoComp->getSeekerAmmo();
					current = 0;
					ammoComp->setSeekerAmmo(current);
				}
			}

			if (Start)
			{
				//buttonStart_();
			}
			if (Back)
			{
				//buttonBack_();
			}
			if (LeftShoulder)
			{
				//buttonLB_();
			}
			if (RightShoulder)
			{
				//buttonRB_();
			}
			break;

		case SDL_JOYAXISMOTION:

			if (StickLeftX >= -bitePoint)
			{
			//	controlComp->moveLeft = 0;
			}
			if (StickLeftX <= bitePoint)
			{
			//	controlComp->moveRight = 0;
			}

			if (StickLT >= bitePoint || StickLT <= -bitePoint)
			{
				//buttonLT_();
			}
			if (StickRT >= bitePoint || StickRT <= -bitePoint)
			{
				//buttonRT_();
			}

			if (StickLeftX >= bitePoint || StickLeftX <= -bitePoint)
			{
				if (StickLeftX < 0)
				{
					controlComp->setDirection(controlComp->Left);
					controlComp->moveLeft = 1;
				}
				else if (StickLeftX > 0)
				{
					controlComp->setDirection(controlComp->Right);
					controlComp->moveRight = 1;
				}
				//buttonLSX_(StickLeftX);
			}
			if (StickLeftY >= bitePoint || StickLeftY <= -bitePoint)
			{

				//buttonLSY_(StickLeftY);
			}
			if (StickRightX >= bitePoint || StickRightX <= -bitePoint)
			{
				//buttonRSX_(StickRightX);
			}
			if (StickRightY >= bitePoint || StickRightY <= -bitePoint)
			{
				//buttonRSY_(StickRightY);
			}
			break;

		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
				int posX;
				int posY;
			case SDLK_UP:
				controlComp->setDirection(controlComp->Up);
				AudioManager::Instance()->PlaySFX("Jump", 0);
				break;
			case SDLK_LEFT:
				controlComp->setDirection(controlComp->Left);
				controlComp->moveLeft = 1;
				if (!controlComp->alive)
					controlComp->alive = true;
				break;
			case SDLK_RIGHT:
				controlComp->setDirection(controlComp->Right);
				controlComp->moveRight = 1;
				if (!controlComp->alive)
					controlComp->alive = true;
				break;
			case SDLK_s:
				if (!pressed)
				{
					controlComp->attack = true;
					pressed = true;
				}
				break;
			case SDLK_a:
				//amComp->idle();
				posX = posComp->getPositionX();
				posY = posComp->getPositionY();
				//get current ammo amount and if not 0 place bomb
				if (ammoComp->getSeekerAmmo() > 0) {
					ammoComp->dropSeeker(posX, posY, 200);
					//take one ammo away
					int current = ammoComp->getSeekerAmmo();
					current = 0;
					ammoComp->setSeekerAmmo(current);
				}
				break;
			case SDLK_SPACE:
				//amComp->idle();
				posX = posComp->getPositionX();
				posY = posComp->getPositionY();
				//get current ammo amount and if not 0 place bomb
				if (ammoComp->getAmmo() > 0) {
					ammoComp->dropProjectile(posX, posY);
					//take one ammo away
					int current = ammoComp->getAmmo();
					current = 0;
					ammoComp->setAmmo(current);
				}
				break;
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
		if (e.key.keysym.sym == SDLK_s)
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
