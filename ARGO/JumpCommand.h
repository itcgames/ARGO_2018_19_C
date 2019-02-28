#pragma once
#include "Command.h"
class JumpCommand : public Command
{
public:
	JumpCommand() {};
	~JumpCommand() {}
	void execute(Entity * e, Client & client)
	{
		ControlComponent * controlComp = (ControlComponent*)e->getCompByType("Control");
		controlComp->setDirection(controlComp->Up);
		AudioManager::Instance()->PlaySFX("Jump", 0);
	};

	void stop(Entity * e)
	{
		
	};

protected:
};

