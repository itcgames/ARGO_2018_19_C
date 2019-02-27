#pragma once
#include "Command.h"
class KickCommand : public Command
{
public:
	KickCommand() {};
	~KickCommand() {}
	void execute(Entity * e, Client & client)
	{
		ControlComponent * controlComp = (ControlComponent*)e->getCompByType("Control");
		controlComp->kick();
	};

	void stop(Entity * e)
	{
		
	};

protected:
};

