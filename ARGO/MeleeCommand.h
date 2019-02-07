#pragma once
#include "Command.h"
class MeleeCommand : public Command
{
public:
	virtual void execute()
	{
		std::cout << "melee" << std::endl;
	}
};