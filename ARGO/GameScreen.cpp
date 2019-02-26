#include "GameScreen.h"

struct not_digit {
	bool operator()(const char c)
	{
		return c != ' ' && !isdigit(c);
	}
};

std::vector<float> GameScreen::msgToPos(std::string s)
{
	not_digit notADigit;

	std::string::iterator end = std::remove_if(s.begin(), s.end(), notADigit);

	std::string all_numbers(s.begin(), end);

	std::stringstream ss(all_numbers);
	std::vector<float> vec;
	int i;
	for (; ss >> i;)
	{
		vec.push_back(i);
	}
	return vec;
}

GameScreen::GameScreen(SDL_Renderer * ren) : player("Player"), player2("Player2"), player3("Player3"), player4("Player4"), flag("Flag")
{
	m_factory = new PowerUpFactory;

	const auto MAP_PATH = "assets/maps/map2.tmx";
	m_level = new level("Main Level");
	m_level->load(MAP_PATH, ren);
	
	if (!wallTxt.loadFromFile("wall.bmp", ren, 1))
	{
		printf("Failed to load wall texture!\n");
	}


	flag.addComponent(new SpriteComponent("img/flag.png", 0.3, ren, 8, 2));
	flag.addComponent(new PickUpComponent());
	flag.addComponent(new PositionComponent(1000, 600));

	player.addComponent(new SpriteComponent("img/playerSheet.png", 0.5, ren, 3, 5));
	player.addComponent(new AmmoComponent(ren));
	player.addComponent(new AnimationComponent());
	player.addComponent(new CollisionComponent());
	player.addComponent(new ControlComponent());
	player.addComponent(new PositionComponent(300, 100));
	player.addComponent(new LifeComponent(4, 1, ren, 1));
	player.addComponent(new VelocityComponent());

	player2.addComponent(new SpriteComponent("img/playerSheet.png", 0.5, ren, 3, 5));
	player2.addComponent(new AnimationComponent());
	player2.addComponent(new CollisionComponent());
	player2.addComponent(new ControlComponent());
	player2.addComponent(new AmmoComponent(ren));
	player2.addComponent(new PositionComponent(500, 100));
	player2.addComponent(new LifeComponent(5, 2, ren, 1));
	player2.addComponent(new VelocityComponent());

	player3.addComponent(new SpriteComponent("img/playerSheet.png", 0.5, ren, 3, 5));
	player3.addComponent(new AnimationComponent());
	player3.addComponent(new CollisionComponent());
	player3.addComponent(new ControlComponent());
	player3.addComponent(new AmmoComponent(ren));
	player3.addComponent(new PositionComponent(300, 600));
	player3.addComponent(new LifeComponent(6, 3, ren, 1));
	player3.addComponent(new VelocityComponent());


	player4.addComponent(new SpriteComponent("img/playerSheet.png", 0.5, ren, 3, 5));
	player4.addComponent(new AnimationComponent());
	player4.addComponent(new CollisionComponent());
	player4.addComponent(new ControlComponent());
	player4.addComponent(new AmmoComponent(ren));
	player4.addComponent(new PositionComponent(500, 500));
	player4.addComponent(new LifeComponent(3, 4, ren, 1));
	player4.addComponent(new VelocityComponent());

	ammos.addEntity(player);
	ammos.addEntity(player2);
	ammos.addEntity(player3);
	ammos.addEntity(player4);

	rs.addEntity(flag);
	rs.addEntity(player);
	rs.addEntity(player2);
	rs.addEntity(player3);
	rs.addEntity(player4);

	ls.addEntity(player);
	ls.addEntity(player2);
	ls.addEntity(player3);
	ls.addEntity(player4);

	ais.addEntity(flag);

	Colls.addEntity(flag);

	comsystem.addEntity(flag);
	comsystem.addEntity(player);
	comsystem.addEntity(player2);
	comsystem.addEntity(player3);
	comsystem.addEntity(player4);

	ps.addEntity(player);
	ps.addEntity(player2);
	ps.addEntity(player3);
	ps.addEntity(player4);

	cs.init();

}

void GameScreen::init(SDL_Renderer * ren, int * pIndex)
{
	m_playerIndex = pIndex;
	m_timerSpawn = 0;

	flag.addComponent(new PositionComponent(1000, 600));

	//Initialise player with all the Components and systems they need (AI or Player)

	/*player.addComponent(new PositionComponent(300, 100));
	player.addComponent(new LifeComponent(4, 1, ren, 1));
	player.addComponent(new VelocityComponent());
	

	player2.addComponent(new PositionComponent(500, 100));
	player2.addComponent(new LifeComponent(5, 2, ren, 1));
	player2.addComponent(new VelocityComponent());
	

	player3.addComponent(new PositionComponent(300, 600));
	player3.addComponent(new LifeComponent(6, 3, ren, 1));
	player3.addComponent(new VelocityComponent());

	player4.addComponent(new PositionComponent(500, 500));
	player4.addComponent(new LifeComponent(3, 4, ren, 1));
	player4.addComponent(new VelocityComponent());
*/
}

void GameScreen::input(SDL_Event * e, Client * client)
{
	cs.input(*e, *client);

	if (e->type == SDL_KEYUP)
	{
		cs.idle();
		cs.keyUp(*e);
	}
}

void GameScreen::update(Client * client, float dt, SDL_Renderer * ren)
{
	//ps.update(m_renderer);
	phs.update();
	comsystem.update(*m_playerIndex, *client);
	ls.update();
	//phs.update();
	Colls.update(*m_level, dt);
	ammos.update();

	// Network
	powerUpSpawn(ren, client);
	sendPUToNetwork(client);
	sendAiToNetwork(client);
	//If Host update ai
	if (*m_playerIndex == 0)
	{
		//Update all ai
		ais.update(1000, ais.getEntityById("Player2"));
	}

	// ?? getDistance();
}

void GameScreen::render(SDL_Renderer * ren, float dt)
{
	//Jamie
	SDL_RenderSetLogicalSize(ren, SCREEN_WIDTH, SCREEN_HEIGHT);
	rs.update(ren, dt);
	//ps.update(m_renderer);
	m_level->draw(ren);
	ammos.render(ren);
	for (int i = m_powerUps.size() - 1; i >= 0; i--)
	{
		m_powerUps[i]->draw(ren);
	}
}

void GameScreen::getDistance() {
	//how to tell if an entity is Ai

	//get distance of oncoming object
	PositionComponent * p = (PositionComponent *)player.getCompByType("Position");
	PositionComponent * p2 = (PositionComponent *)player2.getCompByType("Position");
	PositionComponent * p3 = (PositionComponent *)player3.getCompByType("Position");



}


void GameScreen::rumble()
{
	//random number between 1-3
	int rWidth = rand() % 3 + 1;

	//pos 1
	if (rWidth == 1) {
		SCREEN_WIDTH = 1501;
		SCREEN_HEIGHT = 1010;
	}
	//pos 2
	if (rWidth == 2) {
		SCREEN_WIDTH = 1499;
		SCREEN_HEIGHT = 1020;
	}
	//pos 3
	if (rWidth == 3) {
		SCREEN_WIDTH = 1489;
		SCREEN_HEIGHT = 1020;
	}

}

void GameScreen::resetCamera()
{
	//set camera pos
	SCREEN_WIDTH = 1500;
	SCREEN_HEIGHT = 1020;
}


void GameScreen::sendAiToNetwork(Client * client)
{
	if (*m_playerIndex == 0)
	{
		std::vector<std::string> aiIDs = ais.getEntityIds();

		PositionComponent * p = (PositionComponent *)player2.getCompByType("Position");
		LifeComponent * l = (LifeComponent *)player2.getCompByType("Life");
		AnimationComponent * ac = (AnimationComponent *)player2.getCompByType("Animation");
		std::string pos;
		for (int i = 0; i < aiIDs.size(); i++)
		{
			if (aiIDs[i] == "Player2")
			{
				p = (PositionComponent *)player2.getCompByType("Position");
				l = (LifeComponent *)player2.getCompByType("Life");
				ac = (AnimationComponent *)player2.getCompByType("Animation");

				pos = "Player X: " + std::to_string((int)p->getPositionX());	// Pos X
				pos = pos + ", " + "Y: " + std::to_string((int)p->getPositionY());	// Pos Y
				pos = pos + ", " + "I: " + std::to_string(1);	// Player Index
				pos = pos + ", " + "L: " + std::to_string(l->getLife()); // Player Life
				pos = pos + ", " + "A: " + std::to_string(ac->m_currentState); // Player state
				client->sendMsg(pos);
			}
			else if (aiIDs[i] == "Player3")
			{
				p = (PositionComponent *)player3.getCompByType("Position");
				l = (LifeComponent *)player3.getCompByType("Life");
				ac = (AnimationComponent *)player3.getCompByType("Animation");

				pos = "Player X: " + std::to_string((int)p->getPositionX());	// Pos X
				pos = pos + ", " + "Y: " + std::to_string((int)p->getPositionY());	// Pos Y
				pos = pos + ", " + "I: " + std::to_string(2);	// Player Index
				pos = pos + ", " + "L: " + std::to_string(l->getLife()); // Player Life
				pos = pos + ", " + "A: " + std::to_string(ac->m_currentState); // Player state
				client->sendMsg(pos);

			}
			else if (aiIDs[i] == "Player4")
			{
				p = (PositionComponent *)player4.getCompByType("Position");
				l = (LifeComponent *)player4.getCompByType("Life");
				ac = (AnimationComponent *)player4.getCompByType("Animation");

				pos = "Player X: " + std::to_string((int)p->getPositionX());	// Pos X
				pos = pos + ", " + "Y: " + std::to_string((int)p->getPositionY());	// Pos Y
				pos = pos + ", " + "I: " + std::to_string(3);	// Player Index
				pos = pos + ", " + "L: " + std::to_string(l->getLife()); // Player Life
				pos = pos + ", " + "A: " + std::to_string(ac->m_currentState); // Player state
				client->sendMsg(pos);

			}
			else if (aiIDs[i] == "Flag")
			{
				p = (PositionComponent *)flag.getCompByType("Position");

				pos = "Flag X: " + std::to_string((int)p->getPositionX());	// Pos X
				pos = pos + ", " + "Y: " + std::to_string((int)p->getPositionY());	// Pos Y
				pos = pos + ", " + "H: " + std::to_string(whoHasFlag());	// If someone has it
				client->sendMsg(pos);
			}

		}

	}
}

int GameScreen::whoHasFlag()
{
	ControlComponent * cc = (ControlComponent *)player.getCompByType("Control");
	if (cc->hasFlag)
	{
		return 0;
	}

	cc = (ControlComponent *)player2.getCompByType("Control");
	if (cc->hasFlag)
	{
		return 1;
	}

	cc = (ControlComponent *)player3.getCompByType("Control");
	if (cc->hasFlag)
	{
		return 2;
	}

	cc = (ControlComponent *)player4.getCompByType("Control");
	if (cc->hasFlag)
	{
		return 3;
	}

	return -1;

}

void GameScreen::sendPUToNetwork(Client * client)
{
	if (*m_playerIndex == 0)
	{
		// Position
		// id
		// index

		for (int i = 0; i < m_powerUps.size(); i++)
		{
			std::string pu = "Power Ups ";
			pu = pu + "X: " + std::to_string((int)m_powerUps[i]->getX());
			pu = pu + " Y: " + std::to_string((int)m_powerUps[i]->getY());
			pu = pu + " ID: " + std::to_string(m_powerUps[i]->getID());
			pu = pu + " I: " + std::to_string(i);
			client->sendMsg(pu);
		}
	}
}

void GameScreen::powerUpSpawn(SDL_Renderer * ren, Client * client)
{
	if (*m_playerIndex == 0)
	{
		m_timerSpawn++;
		if (m_timerSpawn >= m_spawnTimeLimit)
		{
			//switch (rand() % m_numOfPowerUps)
			switch (2)
			{
			case 0:
				m_powerUps.push_back(m_factory->CreateSpeed(ren));
				break;

			case 1:
				m_powerUps.push_back(m_factory->CreateHealth(ren));
				break;

			case 2:
				m_powerUps.push_back(m_factory->CreateAmmo(ren));
				break;

			case 3:
				m_powerUps.push_back(m_factory->CreateSeekerAmmo(ren));
				break;

			case 4:
				m_powerUps.push_back(m_factory->CreateReset(ren));
				break;

			}
			m_timerSpawn = 0;
		}
	}


	for (int i = m_powerUps.size() - 1; i >= 0; i--)
	{
		if (m_powerUps[i]->getAlive())
		{
			if (*m_playerIndex == 0)
			{
				m_powerUps[i]->update();
			}

			//check collision

			// Getting player position and the sprite dimensions
			// Set up the pointer
			PositionComponent * p = (PositionComponent *)player.getCompByType("Position");
			SpriteComponent * s = (SpriteComponent *)player.getCompByType("Sprite");
			// Set the pointer to your player
			switch (*m_playerIndex)
			{
			case 0:	// Player 1
				p = (PositionComponent *)player.getCompByType("Position");
				s = (SpriteComponent *)player.getCompByType("Sprite");
				break;

			case 1:	// Player 2
				p = (PositionComponent *)player2.getCompByType("Position");
				s = (SpriteComponent *)player2.getCompByType("Sprite");
				break;

			case 2:	// Player 3
				p = (PositionComponent *)player3.getCompByType("Position");
				s = (SpriteComponent *)player3.getCompByType("Sprite");
				break;

			case 3:	// Player 4
				p = (PositionComponent *)player4.getCompByType("Position");
				s = (SpriteComponent *)player4.getCompByType("Sprite");
				break;
			}
			// Check if the power up and the player collided
			if (m_powerUps[i]->pickedUp(p->getPositionX(), p->getPositionY(), s->getWidth(), s->getWidth()))
			{
				std::string msg = "Collected: i: " + std::to_string(i) + " pi: " + std::to_string(*m_playerIndex);
				client->sendMsg(msg);
				// Which power up if it
				switch (m_powerUps[i]->getID())
				{
				case 1: // Health
					for (int j = 0; j < Colls.getEntityID().size(); j++)
					{
						if (Colls.getEntityID()[j] == "Player")
							Colls.ActivateInvincible();
						if (Colls.getEntityID()[j] == "Player2")
							Colls.ActivateInvincible();
						if (Colls.getEntityID()[j] == "Player3")
							Colls.ActivateInvincible();
						if (Colls.getEntityID()[j] == "Player4")
							Colls.ActivateInvincible();
					}
					break;

				case 2:	// Speed
					for (int j = 0; j < phs.getEntityIds().size(); j++)
					{
						if (phs.getEntityIds()[j] == "Player") {
							phs.speedUp(phs.getEntityById("Player"));
						}
						if (phs.getEntityIds()[j] == "Player2") {
							phs.speedUp(phs.getEntityById("Player2"));
						}
						if (phs.getEntityIds()[j] == "Player3") {
							phs.speedUp(phs.getEntityById("Player3"));
						}
						if (phs.getEntityIds()[j] == "Player4") {
							phs.speedUp(phs.getEntityById("Player4"));
						}
					}
					break;

				case 3: // Ammo
					for (int j = 0; j < ammos.getEntityIds().size(); j++)
					{
						if (ammos.getEntityIds()[j] == "Player") {
							ammos.addAmmo(ammos.getEntityById("Player"));
						}
						if (ammos.getEntityIds()[j] == "Player2") {
							ammos.addAmmo(ammos.getEntityById("Player2"));
						}
						if (ammos.getEntityIds()[j] == "Player3") {
							ammos.addAmmo(ammos.getEntityById("Player3"));
						}
						if (ammos.getEntityIds()[j] == "Player4") {
							ammos.addAmmo(ammos.getEntityById("Player4"));
						}
					}
					break;

				case 4: // SeekerAmmo
					for (int j = 0; j < ammos.getEntityIds().size(); j++)
					{
						if (ammos.getEntityIds()[j] == "Player") {
							ammos.addSeekerAmmo(ammos.getEntityById("Player"));
						}
						if (ammos.getEntityIds()[j] == "Player2") {
							ammos.addSeekerAmmo(ammos.getEntityById("Player2"));
						}
						if (ammos.getEntityIds()[j] == "Player3") {
							ammos.addSeekerAmmo(ammos.getEntityById("Player3"));
						}
						if (ammos.getEntityIds()[j] == "Player4") {
							ammos.addSeekerAmmo(ammos.getEntityById("Player4"));
						}
					}
					break;

				case 5: // Reset
					for (int j = 0; j < Colls.getEntityID().size(); j++)
					{
						if (Colls.getEntityID()[j + 1] == "Player")
							Colls.resetScore(Colls.getEntityID()[j + 1]);
						if (Colls.getEntityID()[j + 1] == "Player2")
							Colls.resetScore(Colls.getEntityID()[j + 1]);
						if (Colls.getEntityID()[j + 1] == "Player3")
							Colls.resetScore(Colls.getEntityID()[j + 1]);
						if (Colls.getEntityID()[j + 1] == "Player4")
							Colls.resetScore(Colls.getEntityID()[j + 1]);
					}
					break;

				}
			}
		}
		else
		{
			m_powerUps.erase(m_powerUps.begin() + i);
		}

	}
}

void GameScreen::updatePlayerNet(std::string s)
{

	PositionComponent * p = (PositionComponent *)player.getCompByType("Position");
	LifeComponent * l = (LifeComponent *)player.getCompByType("Life");
	AnimationComponent * ac = (AnimationComponent *)player.getCompByType("Animation");

	switch ((int)msgToPos(s)[2])
	{
	case 0:
		p = (PositionComponent *)player.getCompByType("Position");
		l = (LifeComponent *)player.getCompByType("Life");
		ac = (AnimationComponent *)player.getCompByType("Animation");
		break;
	case 1:
		p = (PositionComponent *)player2.getCompByType("Position");
		l = (LifeComponent *)player2.getCompByType("Life");
		ac = (AnimationComponent *)player2.getCompByType("Animation");
		break;
	case 2:
		p = (PositionComponent *)player3.getCompByType("Position");
		l = (LifeComponent *)player3.getCompByType("Life");
		ac = (AnimationComponent *)player3.getCompByType("Animation");
		break;
	case 3:
		p = (PositionComponent *)player4.getCompByType("Position");
		l = (LifeComponent *)player4.getCompByType("Life");
		ac = (AnimationComponent *)player4.getCompByType("Animation");
		break;
	}

	p->setPosition(msgToPos(s)[0], msgToPos(s)[1]);
	l->setLifes(msgToPos(s)[3]);

	switch ((int)msgToPos(s)[4])
	{
	case 0:
		ac->m_currentState = ac->AniState::idleS;
		ac->idle();
		break;

	case 1:
		ac->m_currentState = ac->AniState::leftS;
		ac->left();
		break;

	case 2:
		ac->m_currentState = ac->AniState::rightS;
		ac->right();
		break;

	case 3:
		ac->m_currentState = ac->AniState::jumpLeftS;
		ac->leftJump();
		break;

	case 4:
		ac->m_currentState = ac->AniState::jumpRightS;
		ac->rightJump();
		break;

	default:
		std::cout << "Oops! Missing animation" << std::endl;
		break;
	}
}


void GameScreen::updateNetwork(Client * client, std::string msg, SDL_Renderer * ren)
{
	PositionComponent * p = (PositionComponent *)player.getCompByType("Position");
	LifeComponent * l = (LifeComponent *)player.getCompByType("Life");
	AnimationComponent * ac = (AnimationComponent *)player.getCompByType("Animation");

	if (*m_playerIndex != 5)
	{
		std::string pos;
		// Send position
		switch (*m_playerIndex)
		{
		case 0:
			p = (PositionComponent *)player.getCompByType("Position");
			l = (LifeComponent *)player.getCompByType("Life");
			ac = (AnimationComponent *)player.getCompByType("Animation");

			sendAiToNetwork(client);
			break;
		case 1:
			p = (PositionComponent *)player2.getCompByType("Position");
			l = (LifeComponent *)player2.getCompByType("Life");
			ac = (AnimationComponent *)player2.getCompByType("Animation");
			break;
		case 2:
			p = (PositionComponent *)player3.getCompByType("Position");
			l = (LifeComponent *)player3.getCompByType("Life");
			ac = (AnimationComponent *)player3.getCompByType("Animation");
			break;
		case 3:
			p = (PositionComponent *)player4.getCompByType("Position");
			l = (LifeComponent *)player4.getCompByType("Life");
			ac = (AnimationComponent *)player4.getCompByType("Animation");
			break;
		}

		pos = "Player X: " + std::to_string((int)p->getPositionX());	// Pos X
		pos = pos + ", " + "Y: " + std::to_string((int)p->getPositionY());	// Pos Y
		pos = pos + ", " + "I: " + std::to_string(*m_playerIndex);	// Player Index
		pos = pos + ", " + "L: " + std::to_string(l->getLife()); // Player Life
		pos = pos + ", " + "A: " + std::to_string(ac->m_currentState); // Player state
		client->sendMsg(pos);			

		

	}


	if (msg.length() > 0)
	{

		updatePlayerNet(msg);

		int indexPlayer = msg.find("Player");

		// Setting other player positions
		char firstChar = msg.at(0);
		//if (firstChar == 'S' && msg.substr(13, 3) != "IP:")
		if (indexPlayer >= 0)
		{
			// Update first player
			updatePlayerNet(msg.substr(indexPlayer));
			// Check if there is ai being sent with the player
			indexPlayer = msg.find("Player", indexPlayer + 1);
			if (indexPlayer >= 0)
			{
				// Update AI
				updatePlayerNet(msg.substr(indexPlayer));
				// Check if there is another AI
				indexPlayer = msg.find("Player", indexPlayer + 1);
				if (indexPlayer >= 0)
				{
					// Update second AI
					updatePlayerNet(msg.substr(indexPlayer));
				}
			}

		}

		int index = msg.find("Collected");
		if (index >= 0)
		{
			int temp = (int)msgToPos(msg.substr(index))[0];
			std::cout << "Collected: " << temp << std::endl;
			m_powerUps.erase(m_powerUps.begin() + temp);
		}

		index = msg.find("Power Ups");
		if (index >= 0)
		{

			int i = (int)msgToPos(msg.substr(index))[3];

			// If the vector isn't the right size
			if (m_powerUps.size() < i + 1)
			{
				m_powerUps.resize(i + 1);

			}

			// If there is already a powerup in this space
			if (m_powerUps[i] != nullptr)
			{
				// Update pos
				m_powerUps[i]->setX(msgToPos(msg.substr(index))[0]);
				m_powerUps[i]->setY(msgToPos(msg.substr(index))[1]);
			}
			else
			{
				// If the vector position doesnt point to anything
				switch ((int)msgToPos(msg.substr(index))[2])
				{
				case 1:
					m_powerUps[i] = m_factory->CreateHealth(ren);
					break;

				case 2:
					m_powerUps[i] = m_factory->CreateSpeed(ren);
					break;

				case 3:
					m_powerUps[i] = m_factory->CreateAmmo(ren);
					break;

				case 4:
					m_powerUps[i] = m_factory->CreateSeekerAmmo(ren);
					break;

				case 5:
					m_powerUps[i] = m_factory->CreateReset(ren);
					break;

				}
			}
		}

		

		index = msg.find("Flag");
		if (index >= 0)
		{
			// Set flag position and if it can be taken
			PositionComponent * fp = (PositionComponent *)flag.getCompByType("Position");
			fp->setPosition((int)msgToPos(msg.substr(index))[0], (int)msgToPos(msg.substr(index))[1]);
			switch ((int)msgToPos(msg.substr(index))[2])
			{
			case 0:
				break;

			case 1:
				break;

			case 2:
				break;

			case 3:
				break;
			}
		}

		index = msg.find("Planted");
		if (index >= 0)
		{
			// Put Bomb on pos given
			int pIndex = (int)msgToPos(msg.substr(index))[0];
			int x = (int)msgToPos(msg.substr(index))[1];
			int y = (int)msgToPos(msg.substr(index))[2];

			AmmoComponent* ammoComp = (AmmoComponent*)player.getCompByType("Ammo");

			switch (pIndex)
			{
			case 0:
				ammoComp = (AmmoComponent*)player.getCompByType("Ammo");
				break;

			case 1:
				ammoComp = (AmmoComponent*)player2.getCompByType("Ammo");
				break;

			case 2:
				ammoComp = (AmmoComponent*)player3.getCompByType("Ammo");
				break;

			case 3:
				ammoComp = (AmmoComponent*)player4.getCompByType("Ammo");
				break;
			}
			ammoComp->dropProjectile(x, y);
		}

		index = msg.find("Fire");
		if (index >= 0)
		{
			// Fire rocket
		}


		index = msg.find("Kicked");
		if (index >= 0)
		{
			VelocityComponent * v = (VelocityComponent*)player.getCompByType("Vel");
			ControlComponent * cc = (ControlComponent*)player.getCompByType("Control");

			PickUpComponent * pickup = (PickUpComponent *)flag.getCompByType("PickUp");

			switch ((int)msgToPos(msg.substr(index))[0])
			{
			case 0:
				// Player 1
				v = (VelocityComponent*)player.getCompByType("Vel");
				p = (PositionComponent*)player.getCompByType("Position");
				cc = (ControlComponent*)player.getCompByType("Control");
				break;

			case 1:
				// Player 2
				v = (VelocityComponent*)player2.getCompByType("Vel");
				p = (PositionComponent*)player2.getCompByType("Position");
				cc = (ControlComponent*)player2.getCompByType("Control");
				break;

			case 2:
				// Player 3
				v = (VelocityComponent*)player3.getCompByType("Vel");
				p = (PositionComponent*)player3.getCompByType("Position");
				cc = (ControlComponent*)player3.getCompByType("Control");
				break;

			case 3:
				// Player 4
				v = (VelocityComponent*)player4.getCompByType("Vel");
				p = (PositionComponent*)player4.getCompByType("Position");
				cc = (ControlComponent*)player4.getCompByType("Control");
				break;
			}



			if ((int)msgToPos(msg.substr(index))[1] == 0)
			{
				// Left
				std::cout << "Kicked left" << std::endl;
				p->setPosition(p->getPositionX() + v->getVelX() - 100, p->getPositionY() + v->getVelY() - 90);
			}
			else
			{
				// Right
				std::cout << "Kicked right" << std::endl;
				p->setPosition(p->getPositionX() + v->getVelX() + 100, p->getPositionY() + v->getVelY() - 90);
			}

			if ((int)msgToPos(msg.substr(index))[2] == 1)
			{
				cc->hasFlag = false;
				pickup->setState(pickup->Collectable);
			}
		}

	}
}


void GameScreen::playerAI(int pIndex, bool ai)
{
	if (ai)
	{
		switch (pIndex)
		{
		case 0:
			ais.addEntity(player);
			break;
		case 1:
			ais.addEntity(player2);
			break;
		case 2:
			ais.addEntity(player3);
			break;
		case 3:
			ais.addEntity(player4);
			break;
		}
	}
	else
	{
		switch (pIndex)
		{
		case 0:
			player.removeComponent(player.getCompByType("AI"));
			break;
		case 1:
			player2.removeComponent(player.getCompByType("AI"));
			break;
		case 2:
			player3.removeComponent(player.getCompByType("AI"));
			break;
		case 3:
			player4.removeComponent(player.getCompByType("AI"));
			break;
		}
	}
}


void GameScreen::setPlayer(int pIndex)
{
	PositionComponent * p = (PositionComponent *)player.getCompByType("Position");
	*m_playerIndex = pIndex;
	switch (pIndex)
	{
	case 0:
		//player.addComponent(new ControlComponent());
		player.addComponent(new ScoreComponent(0));
		//player.addComponent(new LifeComponent(6, 1, m_renderer, 1));

		cs.addEntity(player);
		Colls.addEntity(player);
		Colls.addEntity(player2);
		Colls.addEntity(player3);
		Colls.addEntity(player4);
		phs.addEntity(player);
		p = (PositionComponent *)player.getCompByType("Position");
		p->setPosition(100, 100);
		break;

	case 1:
		//player2.addComponent(new ControlComponent());
		//player2.addComponent(new LifeComponent(6, 2, ren, 1));
		player2.addComponent(new ScoreComponent(0));
		cs.addEntity(player2);
		Colls.addEntity(player2);
		phs.addEntity(player2);
		p = (PositionComponent *)player2.getCompByType("Position");
		p->setPosition(500, 100);
		break;

	case 2:
		//player3.addComponent(new ControlComponent());
		//player3.addComponent(new LifeComponent(6, 3, ren, 1));
		player3.addComponent(new ScoreComponent(0));
		cs.addEntity(player3);
		Colls.addEntity(player3);
		phs.addEntity(player3);
		p = (PositionComponent *)player3.getCompByType("Position");
		p->setPosition(100, 500);
		break;

	case 3:
		//player4.addComponent(new ControlComponent());
		//player4.addComponent(new LifeComponent(6, 4, ren, 1));
		player4.addComponent(new ScoreComponent(0));
		cs.addEntity(player4);
		Colls.addEntity(player4);
		phs.addEntity(player4);
		p = (PositionComponent *)player4.getCompByType("Position");
		p->setPosition(500, 500);
		break;
	}
}