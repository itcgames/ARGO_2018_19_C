#pragma once
#include "Command.h"
class SeekerCommand : public Command
{
public:
	SeekerCommand() {};
	~SeekerCommand() {}
	void execute(Entity * e, Client & client)
	{
		PositionComponent * posComp = (PositionComponent*)e->getCompByType("Position");
		AmmoComponent * ammoComp = (AmmoComponent*)e->getCompByType("Ammo");
		int posX = posComp->getPositionX();
		int posY = posComp->getPositionY();
		//get current ammo amount and if not 0 place bomb
		std::string msg = "";
		if (ammoComp->getSeekerAmmo() > 0) {
			if (e->getName() == "Player")
			{
				msg = "Fire I: 0";
			}
			else if (e->getName() == "Player2")
			{
				msg = "Fire I: 1";
			}
			else if (e->getName() == "Player3")
			{
				msg = "Fire I: 2";
			}
			else if (e->getName() == "Player4")
			{
				msg = "Fire I: 3";
			}
			msg = msg + " X: " + std::to_string(posX) + " Y: " + std::to_string(posY);
			client.sendMsg(msg);
			ammoComp->dropSeeker(posX, posY, 200);
			//take one ammo away
			int current = ammoComp->getSeekerAmmo();
			current = 0;
			ammoComp->setSeekerAmmo(current);
		}
	};

	void stop(Entity * e)
	{

	};

protected:
};

