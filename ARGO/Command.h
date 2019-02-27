#pragma once
#include "EntityComponent.h"
#include "Client.h"

class Command
{
public:
	virtual ~Command() {}
	virtual void execute(Entity * e, Client & client) = 0;
	virtual void stop(Entity * e) = 0;

protected:
	Command() {}
};
