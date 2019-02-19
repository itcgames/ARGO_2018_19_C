#pragma once

#include "Command.h"
#include <iostream>

class CrouchCommand : public Command
{
public:
	virtual void execute() { std::cout << "Crouch" << std::endl; };
	virtual void undo() { std::cout << "Undo Crouch" << std::endl; };
	virtual void redo() { std::cout << "Redo Crouch" << std::endl; };
};