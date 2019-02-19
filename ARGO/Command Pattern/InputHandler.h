#pragma once
#include "Command.h"
#include "FireCommand.h"
#include "JumpCommand.h"
#include "CrouchCommand.h"
#include "MeleeCommand.h"
#include "MacroCommand.h"
#include "ShieldCommand.h"
#include <SDL.h>
#include <string>
#define MAX_CONTROLLERS 4

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	void handleInput(SDL_Event & event);

private:
	Command * buttonX_;
	Command * buttonY_;
	Command * buttonC_;
	Command * buttonA_;
	Command * buttonB_;
	void(*buttonUp_)();
	void(*buttonDown_)();
	void(*buttonRight_)();
	void(*buttonLeft_)();
	void(*buttonLB_)();
	void(*buttonRB_)();
	void(*buttonLT_)();
	void(*buttonRT_)();
	void(*buttonStart_)();
	void(*buttonBack_)();
	void(*buttonRSX_)(int);
	void(*buttonRSY_)(int);
	void(*buttonLSX_)(int);
	void(*buttonLSY_)(int);
	MacroCommand * macro;
	
	int bitePoint;

	bool AButton;
	bool BButton;
	bool XButton;
	bool YButton;
	bool Up;
	bool Down;
	bool Left;
	bool Right;
	bool Start;
	bool Back;
	bool LeftShoulder;
	bool RightShoulder;
	int StickLeftX;
	int StickLeftY;
	int StickRightX;
	int StickRightY;
	int StickLT;
	int StickRT;

	SDL_GameController *ControllerHandles[MAX_CONTROLLERS];
};