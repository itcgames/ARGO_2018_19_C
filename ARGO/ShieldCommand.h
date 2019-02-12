#pragma once
#include "Command.h"
class ShieldCommand : public Command
{
public:
	virtual void execute()
	{
		std::cout << "Shield" << std::endl;
	}
};