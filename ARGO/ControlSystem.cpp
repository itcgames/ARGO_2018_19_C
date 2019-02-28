#include "ControlSystem.h"
#include "LeftCommand.h"
#include "RightCommand.h"
#include "JumpCommand.h"
#include "BombCommand.h"
#include "SeekerCommand.h"
#include "KickCommand.h"

ControlSystem::ControlSystem() {
	stickLeft = new LeftCommand();
	stickRight = new RightCommand();
	buttonA = new JumpCommand();
	buttonB = new BombCommand();
	buttonX = new KickCommand();
	buttonY = new SeekerCommand();

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

void ControlSystem::input(SDL_Event &e, Client & client, GameState & gs, bool & changeReady, int & changeAi) {




	for (int ControllerIndex = 0;
		ControllerIndex < MAX_CONTROLLERS;
		++ControllerIndex)
	{
		if (ControllerHandles[ControllerIndex] != 0 && SDL_GameControllerGetAttached(ControllerHandles[ControllerIndex]))
		{
			// NOTE: We have a controller with index ControllerIndex.
			AButtonPrevious = AButton;
			BButtonPrevious = BButton;
			AButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_A);
			BButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_B);
			XButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_X);
			YButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_Y);
			Up = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_UP);
			Down = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_DOWN);
			StickLeftX = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex], SDL_CONTROLLER_AXIS_LEFTX);

			// Don't use these (yet)
			/*
			Left = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_LEFT);
			Right = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
			Start = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_START);
			Back = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_BACK);
			LeftShoulder = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
			RightShoulder = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
			StickLeftY = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex], SDL_CONTROLLER_AXIS_LEFTY);
			StickRightX = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex], SDL_CONTROLLER_AXIS_RIGHTX);
			StickRightY = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex], SDL_CONTROLLER_AXIS_RIGHTY);
			StickLT = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex], SDL_CONTROLLER_AXIS_TRIGGERLEFT);
			StickRT = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex], SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
			*/
		}
		else
		{
			// TODO: This controller is not plugged in.
		}
	}

	switch (gs)
	{
	case GameState::MainMenu:
		if (AButton)
		{
			gs = GameState::Lobby;
		}

		if (XButton)
		{
			gs = GameState::Options;
		}

		if (BButton && !BButtonPrevious)
		{
			gs = GameState::Credits;
		}
		break;

	case GameState::Options:
	{
		if (BButton)
		{
			gs = GameState::MainMenu;
		}
	}

	case GameState::Lobby:
		if (AButton && !AButtonPrevious)
		{
			changeReady = true;
		}

		if (BButton)
		{
			gs = GameState::MainMenu;
		}
		break;

	case GameState::GameScreen:

		if (Up || e.key.keysym.sym == SDLK_z)
		{
			changeAi = 0;
		}
		if (Down || e.key.keysym.sym == SDLK_x)
		{
			changeAi = 1;
		}

		for (Entity& entity : entities)
		{

			controlComp = (ControlComponent*)entity.getCompByType("Control");
			amComp = (AnimationComponent*)entity.getCompByType("Animation");
			AmmoComponent* ammoComp = (AmmoComponent*)entity.getCompByType("Ammo");
			PositionComponent* posComp = (PositionComponent*)entity.getCompByType("Position");




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
			

			case SDL_JOYBUTTONDOWN:
				if (AButton)
				{
					buttonA->execute(&entity, client);
				}
				if (BButton)
				{

					buttonB->execute(&entity, client);
				}
				if (XButton)
				{
					if (!pressed)
					{
						buttonX->execute(&entity, client);
						pressed = true;
					}
				}
				if (YButton)
				{

					buttonY->execute(&entity, client);
				}

				

				
				break;

			case SDL_JOYAXISMOTION:

				if (StickLeftX < -bitePoint)
				{
					stickLeft->execute(&entity, client);
				}
				else
				{
					stickLeft->stop(&entity);
				}

				if (StickLeftX > bitePoint)
				{
					stickRight->execute(&entity, client);
				}
				else
				{
					stickRight->stop(&entity);
				}

				break;

			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					buttonA->execute(&entity, client);
					break;
				case SDLK_LEFT:
					stickLeft->execute(&entity, client);
					break;
				case SDLK_RIGHT:
					stickRight->execute(&entity, client);
					break;
				case SDLK_s:
					if (!pressed)
					{
						buttonX->execute(&entity, client);
						pressed = true;
					}
					break;
				case SDLK_a:
					buttonY->execute(&entity, client);
					break;
				case SDLK_SPACE:
					buttonB->execute(&entity, client);
					break;
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
		}
		break;
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


int ControlSystem::getEntityIndex(std::string entity)
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i].getName() == entity)
		{
			return i;
		}
	}
	return -1;
}

void ControlSystem::removeEntityByIndex(int i)
{
	entities.erase(entities.begin() + i);
}

std::vector<std::string> ControlSystem::getEntityIds() {
	//only reurns first name
	std::vector<std::string> v;
	for (Entity & entity : entities) {
		v.push_back(entity.getName());
	}
	return v;
}