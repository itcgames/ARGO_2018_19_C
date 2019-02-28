#pragma once
#include "Command.h"
class AiTakeOverCommand : public Command
{
public:
	AiTakeOverCommand() {};
	~AiTakeOverCommand() {}
	void execute(Entity * e, Client & client)
	{

		for (int i = 0; i < ais.getEntityIds().size(); i++)
		{
			if (ais.getEntityIds()[i] == "Player")
			{
				change = false;
			}
		}
		if (change)
		{
			ais.addEntity(player);
			if (cs.getEntityIndex("Player") != -1)
			{
				cs.removeEntityByIndex(cs.getEntityIndex("Player"));
			}
		}
	};

	void stop(Entity * e)
	{

	};

protected:
};