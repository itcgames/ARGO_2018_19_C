#pragma once
#pragma once
#include "Command.h"
class JumpCommand : public Command
{
public:
	virtual void execute()
	{
		std::cout << "jump" << std::endl;
	}
};