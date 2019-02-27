#pragma once
#include "Command.h"

class RightCommand : public Command
{
public:
	RightCommand() {};
	~RightCommand() {}
	void execute(Entity * e, Client & client)
	{
		ControlComponent * controlComp = (ControlComponent*)e->getCompByType("Control");
		controlComp->setDirection(controlComp->Right);
		controlComp->moveRight = 1;
		if (!controlComp->alive)
			controlComp->alive = true;
	};

	void stop(Entity * e)
	{
		ControlComponent * controlComp = (ControlComponent*)e->getCompByType("Control");
		controlComp->moveRight = 0;
	};

protected:
};

