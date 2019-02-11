#pragma once
#include <iostream>
class Command
{
public:
	virtual ~Command() {}
	virtual void execute() = 0;

protected:
	Command() {}
};
