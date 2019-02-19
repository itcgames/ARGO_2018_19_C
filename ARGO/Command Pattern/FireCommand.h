#pragma once

#include "Command.h"
#include <iostream>

class FireCommand : public Command
{
public:
	virtual void execute() { std::cout << "Fire" << std::endl; };
	virtual void undo() { std::cout << "Undo Fire" << std::endl; };
	virtual void redo() { std::cout << "Redo Fire" << std::endl; };
};