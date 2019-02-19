#include "InputHandler.h"


InputHandler::InputHandler()
{
	buttonX_ = new JumpCommand();
	buttonY_ = new FireCommand();
	buttonA_ = new CrouchCommand();
	buttonB_ = new MeleeCommand();
	buttonC_ = new ShieldCommand();
	buttonLB_ = &buttonA_->test;
	buttonRB_ = &buttonA_->test;
	buttonUp_ = &buttonA_->test;
	buttonDown_ = &buttonA_->test;
	buttonLeft_ = &buttonA_->test;
	buttonRight_ = &buttonA_->test;
	buttonLT_ = &buttonA_->test;
	buttonRT_ = &buttonA_->test;
	buttonStart_ = &buttonA_->test;
	buttonBack_ = &buttonA_->test;
	buttonRSX_ = &buttonA_->testI;
	buttonRSY_ = &buttonA_->testI;
	buttonLSX_ = &buttonA_->testI;
	buttonLSY_ = &buttonA_->testI;
	macro = new MacroCommand();

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

InputHandler::~InputHandler()
{
	for (int ControllerIndex = 0; ControllerIndex < MAX_CONTROLLERS; ++ControllerIndex)
	{
		if (ControllerHandles[ControllerIndex])
		{
			SDL_GameControllerClose(ControllerHandles[ControllerIndex]);
		}
	}
}

void InputHandler::handleInput(SDL_Event & event)
{
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

	

	

	switch (event.type)
	{
	case SDL_JOYHATMOTION:
		if (Up)
		{
			std::cout << "Up" << std::endl;
			buttonUp_();
		}
		if (Down)
		{
			std::cout << "Down" << std::endl;
			buttonDown_();
		}
		if (Left)
		{
			std::cout << "Left" << std::endl;
			buttonLeft_();
		}
		if (Right)
		{
			std::cout << "Right" << std::endl;
			buttonRight_();
		}
		break;

	case SDL_JOYBUTTONDOWN:
		if (AButton)
		{
			std::cout << "A" << std::endl;
			buttonA_->execute();
			macro->add(buttonA_);
		}
		if (BButton)
		{
			std::cout << "B" << std::endl;
			buttonB_->execute();
			macro->add(buttonB_);
		}
		if (XButton)
		{
			std::cout << "X" << std::endl;
			buttonX_->execute();
			macro->add(buttonX_);
		}
		if (YButton)
		{
			std::cout << "Y" << std::endl;
			buttonY_->execute();
			macro->add(buttonY_);
		}

		if (Start)
		{
			std::cout << "Start" << std::endl;
			buttonStart_();
		}
		if (Back)
		{
			std::cout << "Back" << std::endl;
			buttonBack_();
		}
		if (LeftShoulder)
		{
			std::cout << "LB" << std::endl;
			buttonLB_();
		}
		if (RightShoulder)
		{
			std::cout << "RB" << std::endl;
			buttonRB_();
		}
		break;
		
	case SDL_JOYAXISMOTION:
		
		if (StickLT >= bitePoint || StickLT <= -bitePoint)
		{
			std::cout << "Left Trigger: " << std::to_string(StickLT) << std::endl;
			buttonLT_();
		}
		if (StickRT >= bitePoint || StickRT <= -bitePoint)
		{
			std::cout << "Right Trigger: " << std::to_string(StickRT) << std::endl;
			buttonRT_();
		}

		if (StickLeftX >= bitePoint || StickLeftX <= -bitePoint)
		{
			std::cout << "Left X: " << std::to_string(StickLeftX) << std::endl;
			buttonLSX_(StickLeftX);
		}
		if (StickLeftY >= bitePoint || StickLeftY <= -bitePoint)
		{
			std::cout << "Left Y: " << std::to_string(StickLeftY) << std::endl;
			buttonLSY_(StickLeftY);
		}

		if (StickRightX >= bitePoint || StickRightX <= -bitePoint)
		{
			std::cout << "Right X: " << std::to_string(StickRightX) << std::endl;
			buttonRSX_(StickRightX);
		}
		if (StickRightY >= bitePoint || StickRightY <= -bitePoint)
		{
			std::cout << "Right Y: " << std::to_string(StickRightY) << std::endl;
			buttonRSY_(StickRightY);
		}
		break;
	
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_x:
			buttonX_->execute();
			macro->add(buttonX_);
			break;
		case SDLK_y:
			buttonY_->execute();
			macro->add(buttonY_);
			break;
		case SDLK_a:
			buttonA_->execute();
			macro->add(buttonA_);
			break;
		case SDLK_b:
			buttonB_->execute();
			macro->add(buttonB_);
			break;
		case SDLK_c:
			buttonC_->execute();
			macro->add(buttonC_);
			break;
		case SDLK_z:
			macro->undo();
			break;
		case SDLK_s:
			macro->redo();
			break;
		case SDLK_LCTRL:
			buttonLB_();
			break;
		case SDLK_RCTRL:
			buttonRB_();
			break;
		case SDLK_TAB:
			buttonBack_();
			break;
		case SDLK_ESCAPE:
			buttonStart_();
			break;
		case SDLK_SPACE:
			buttonStart_();
			break;
		}

	}

}