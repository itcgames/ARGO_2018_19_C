#pragma once
#include "Command.h"

class LeftCommand : public Command
{
public:
	LeftCommand() {};
	~LeftCommand() {}
	void execute(Entity * e, Client & client)
	{
		ControlComponent * controlComp = (ControlComponent*)e->getCompByType("Control");
		controlComp->setDirection(controlComp->Left);
		controlComp->moveLeft = 1;
		if (!controlComp->alive)
			controlComp->alive = true;
	};

	void stop(Entity * e)
	{
		ControlComponent * controlComp = (ControlComponent*)e->getCompByType("Control");
		controlComp->moveLeft = 0;
	};

protected:
};
