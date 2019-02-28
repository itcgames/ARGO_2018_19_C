#pragma once
#include "Command.h"
class BombCommand : public Command
{
public:
	BombCommand() {};
	~BombCommand() {}
	void execute(Entity * e, Client & client)
	{
		PositionComponent * posComp = (PositionComponent*)e->getCompByType("Position");
		AmmoComponent * ammoComp = (AmmoComponent*)e->getCompByType("Ammo");
		int posX = posComp->getPositionX();
		int posY = posComp->getPositionY();
		//get current ammo amount and if not 0 place bomb
		std::string msg = "";
		if (ammoComp->getAmmo() > 0) {
			if (e->getName() == "Player")
			{
				msg = "Planted I: 0";
			}
			else if (e->getName() == "Player2")
			{
				msg = "Planted I: 1";
			}
			else if (e->getName() == "Player3")
			{
				msg = "Planted I: 2";
			}
			else if (e->getName() == "Player4")
			{
				msg = "Planted I: 3";
			}
			msg = msg + " X: " + std::to_string(posX) + " Y: " + std::to_string(posY);
			client.sendMsg(msg);
			ammoComp->dropProjectile(posX, posY);
			//take one ammo away
			int current = ammoComp->getAmmo();
			current = 0;
			ammoComp->setAmmo(current);
		}
	};

	void stop(Entity * e)
	{
		
	};

protected:
};