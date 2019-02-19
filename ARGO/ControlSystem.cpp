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

		switch (e.type)
		{
		case SDL_JOYHATMOTION:
			if (Up)
			{
				std::cout << "Up" << std::endl;
				//buttonUp_();
			}
			if (Down)
			{
				std::cout << "Down" << std::endl;
				//buttonDown_();
			}
			if (Left)
			{
				std::cout << "Left" << std::endl;
				//buttonLeft_();
			}
			if (Right)
			{
				std::cout << "Right" << std::endl;
				//buttonRight_();
			}
			break;

		case SDL_JOYBUTTONDOWN:
			if (AButton)
			{
				std::cout << "A" << std::endl;
				//buttonA_->execute();
				//macro->add(buttonA_);
			}
			if (BButton)
			{
				std::cout << "B" << std::endl;
				//buttonB_->execute();
				//macro->add(buttonB_);
			}
			if (XButton)
			{
				std::cout << "X" << std::endl;
				//buttonX_->execute();
				//macro->add(buttonX_);
			}
			if (YButton)
			{
				std::cout << "Y" << std::endl;
				//buttonY_->execute();
				//macro->add(buttonY_);
			}

			if (Start)
			{
				std::cout << "Start" << std::endl;
				//buttonStart_();
			}
			if (Back)
			{
				std::cout << "Back" << std::endl;
				//buttonBack_();
			}
			if (LeftShoulder)
			{
				std::cout << "LB" << std::endl;
				//buttonLB_();
			}
			if (RightShoulder)
			{
				std::cout << "RB" << std::endl;
				//buttonRB_();
			}
			break;

		case SDL_JOYAXISMOTION:

			if (StickLT >= bitePoint || StickLT <= -bitePoint)
			{
				std::cout << "Left Trigger: " << std::to_string(StickLT) << std::endl;
				//buttonLT_();
			}
			if (StickRT >= bitePoint || StickRT <= -bitePoint)
			{
				std::cout << "Right Trigger: " << std::to_string(StickRT) << std::endl;
				//buttonRT_();
			}

			if (StickLeftX >= bitePoint || StickLeftX <= -bitePoint)
			{
				std::cout << "Left X: " << std::to_string(StickLeftX) << std::endl;
				//buttonLSX_(StickLeftX);
			}
			if (StickLeftY >= bitePoint || StickLeftY <= -bitePoint)
			{
				std::cout << "Left Y: " << std::to_string(StickLeftY) << std::endl;
				//buttonLSY_(StickLeftY);
			}

			if (StickRightX >= bitePoint || StickRightX <= -bitePoint)
			{
				std::cout << "Right X: " << std::to_string(StickRightX) << std::endl;
				//buttonRSX_(StickRightX);
			}
			if (StickRightY >= bitePoint || StickRightY <= -bitePoint)
			{
				std::cout << "Right Y: " << std::to_string(StickRightY) << std::endl;
				//buttonRSY_(StickRightY);
			}
			break;

		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_LCTRL:
				//buttonLB_();
				break;
			case SDLK_RCTRL:
				//buttonRB_();
				break;
			case SDLK_TAB:
				//buttonBack_();
				break;
			case SDLK_ESCAPE:
				//buttonStart_();
				break;
			case SDLK_SPACE:
				//buttonStart_();
				break;
			}

		}

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
			if (e.key.keysym.sym == SDLK_SPACE && pressed == false)
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

	controlComp->setDirection(controlComp->Idle);
}