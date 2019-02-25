#include "Game.h"
#include "Game.h"


struct not_digit {
	bool operator()(const char c)
	{
		return c != ' ' && !isdigit(c);
	}
};

std::vector<float> msgToPos(std::string s)
{
	not_digit notADigit;

	string::iterator end = std::remove_if(s.begin(), s.end(), notADigit);

	string all_numbers(s.begin(), end);

	stringstream ss(all_numbers);
	std::vector<float> vec;
	int i;
	for (; ss >> i;)
	{
		vec.push_back(i);
	}
	return vec;
}

Game::Game(): player("Player"), player2("Player2"), player3("Player3"), player4("Player4"), flag("Flag")
{

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);

		m_window = SDL_CreateWindow("ARGO Team C", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		m_currentGameState = (GameState::Lobby);

		int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		if (IMG_Init(imgFlags) != imgFlags)
		{
			cout << "Error: " << IMG_GetError() << endl;
		}

		//Initialize SDL_ttf

		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		}
		m_factory = new PowerUpFactory;

		m_client = new Client();

		initialise();

		const auto MAP_PATH = "assets/maps/map2.tmx";

		m_level = new level("Main Level");
		m_level->load(MAP_PATH, m_renderer);

		//m_fuzzy = new Fuzzy();

		cs.init();
	}
}


void Game::initialise()
{

	SDL_INIT_AUDIO;


	m_client->run();

	m_timerSpawn = 0;
	m_stateTimer = 0;
	if (!m_texture.loadFromFile("dot.bmp", m_renderer, 1))

	{
		printf("Failed to load dot texture!\n");

	}
	if (!wallTxt.loadFromFile("wall.bmp", m_renderer, 1))
	{
		printf("Failed to load wall texture!\n");
	}



	flag.addComponent(new PositionComponent(1000, 600));
	flag.addComponent(new SpriteComponent("img/flag.png", 0.3, m_renderer, 8 , 2));
	flag.addComponent(new PickUpComponent());

	//Initialise player with all the Components and systems they need (AI or Player)

	player.addComponent(new PositionComponent(300, 100));
	player.addComponent(new SpriteComponent("img/playerSheet.png", 0.5, m_renderer, 3, 5));
	player.addComponent(new AnimationComponent());
	player.addComponent(new CollisionComponent());
	player.addComponent(new ControlComponent());
	player.addComponent(new AmmoComponent(m_renderer));
	player.addComponent(new LifeComponent(4, 1, m_renderer, 1));
	player.addComponent(new VelocityComponent());

	player2.addComponent(new PositionComponent(500, 100));
	player2.addComponent(new SpriteComponent("img/playerSheet.png", 0.5, m_renderer, 3, 5));
	player2.addComponent(new AnimationComponent());
	player2.addComponent(new CollisionComponent());
	player2.addComponent(new ControlComponent());
	player2.addComponent(new AmmoComponent(m_renderer));
	player2.addComponent(new LifeComponent(5, 2, m_renderer, 1));
	player2.addComponent(new VelocityComponent());
	   
	player3.addComponent(new PositionComponent(300, 600));
	player3.addComponent(new SpriteComponent("img/playerSheet.png", 0.5, m_renderer, 3, 5));
	player3.addComponent(new AnimationComponent());
	player3.addComponent(new CollisionComponent());
	player3.addComponent(new ControlComponent());
	player3.addComponent(new AmmoComponent(m_renderer));
	player3.addComponent(new LifeComponent(6, 3, m_renderer, 1));
	player3.addComponent(new VelocityComponent());

	player4.addComponent(new PositionComponent(500, 500));
	player4.addComponent(new SpriteComponent("img/playerSheet.png", 0.5, m_renderer, 3, 5));
	player4.addComponent(new AnimationComponent());
	player4.addComponent(new CollisionComponent());
	player4.addComponent(new ControlComponent());
	player4.addComponent(new AmmoComponent(m_renderer));
	player4.addComponent(new LifeComponent(3, 4, m_renderer, 1));
	player4.addComponent(new VelocityComponent());

	Entity wall("Wall");
	//wall.addComponent(new PositionComponent(400, 500));
	//wall.addComponent(new CollisionComponent());
	//wall.addComponent(new SpriteComponent(wallTxt, m_renderer));

	ammos.addEntity(player);
	ammos.addEntity(player2);
	ammos.addEntity(player3);
	ammos.addEntity(player4);

	//hs.addEntity(player);
	//hs.addEntity(player2);
	//hs.addEntity(player3);

	player4.addComponent(new LifeComponent(0, 4, m_renderer, 1));



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

	ps.addEntity(player);
	ps.addEntity(player2);
	ps.addEntity(player3);
	ps.addEntity(player4);


	AudioManager::Instance()->load("africa-toto.wav", "song1", SOUND_MUSIC);
	AudioManager::Instance()->loadSFX("Jumping.wav", "Jump", SOUND_SFX);
	//AudioManager::Instance()->PlayMusic("song1", -1);

	// Screen Initialise
	m_lobbyScreen = new Lobby(m_renderer);
	m_creditsScreen = new Credits(m_renderer);

	m_gameoverScreen = new GameOverScreen();
	m_menuScreen = new MenuScreen(m_renderer);

}

Game::~Game()
{
	AudioManager::Release();
}

void Game::run()
{
	const Uint32 fps = 60;
	const Uint32 minimumFrameTime = 1000 / fps;

	Uint32 frameTime;
	Uint32 lastFrameTime = 0;
	Uint32 deltaTime = 0;

	while (!exit) {

		processEvents();
		frameTime = SDL_GetTicks();

		deltaTime = frameTime - lastFrameTime;
		lastFrameTime = frameTime;

		update(deltaTime);
		render(deltaTime);

		if ((SDL_GetTicks() - frameTime) < minimumFrameTime)
			SDL_Delay(minimumFrameTime - (SDL_GetTicks() - frameTime));
	}

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Game::processEvents()
{

	while (SDL_PollEvent(&event)) {


		cs.input(event);

		switch (event.type) {


		case SDL_QUIT:
			exit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&mouseX, &mouseY);
			break;
		case SDL_KEYUP:
			cs.idle();
			cs.keyUp(event);
			//resetCamera();
			break;
		case SDL_KEYDOWN:
			//rumble();
			if (event.key.keysym.sym == SDLK_ESCAPE)
				exit = true;
			break;
		}


	}
}
void Game::setGameState(GameState gameState)
{
	m_currentGameState = gameState;
}

void Game::update(float dt)
{

	switch (m_currentGameState)
	{
	case GameState::None:
		break;
	case GameState::Splash:
		break;
	case GameState::Lobby:
		m_lobbyScreen->update(m_playerIndex, mouseX, mouseY, m_currentGameState);
		mouseX = -1;
		mouseY = -1;
		updateNetwork();
		break;
	case GameState::MainMenu:
		m_menuScreen->update(mouseX, mouseY, m_currentGameState);
		mouseX = -1;
		mouseY = -1;
		break;
	case GameState::Options:
		break;
	case GameState::GameScreen:

		//ps.update(m_renderer);
		phs.update();
		comsystem.update(dt, m_playerIndex, *m_client);
		ls.update(dt);
		//phs.update();
		Colls.update(*m_level, dt);
		//hs.update();
		ammos.update();
		
		// Network
		updateNetwork();
		if (m_playerIndex == 0)
		{
			powerUpSpawn();
		}
		sendPUToNetwork();
		
		//If Host update ai
		if (m_playerIndex == 0)
		{
			//Update all ai
			ais.update(1000, ais.getEntityById("Player2"));
		}

			getDistance();
			break;
		case GameState::GameOverScreen:
			m_gameoverScreen->update();

			break;
		case GameState::Credits:

			if (m_creditsScreen->endCredits() == true)
			{
				setGameState(GameState::MainMenu);
			}
			m_creditsScreen->update();
		  break;
		default:
			break;
	}


	m_client->sendFinalMsg();
	m_previousGameState = m_currentGameState;
}


void Game::render(float dt)
{
	if (m_renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_renderer);

	switch (m_currentGameState)
	{
	case GameState::None:
		break;
	case GameState::Splash:
		break;
	case GameState::MainMenu:
		m_menuScreen->render(m_renderer);
		break;
	case GameState::Options:
		break;
	case GameState::Lobby:
		m_lobbyScreen->render(m_renderer);
		break;
	case GameState::GameScreen:
		//Jamie
		SDL_RenderSetLogicalSize(m_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
		rs.update(m_renderer, dt);
		//wallTxt.render(400, 500, m_renderer);
		//ps.update(m_renderer);
		m_level->draw(m_renderer);
		//m_playerDot->render(m_renderer);
		//m_texture.render(100, 100, m_renderer);
		ammos.render(m_renderer);
		for (int i = m_powerUps.size() - 1; i >= 0; i--)
		{
			m_powerUps[i]->draw(m_renderer);
		}
		break;
	case GameState::GameOverScreen:
		m_gameoverScreen->render(m_renderer);
		break;
	case GameState::Credits:
		m_creditsScreen->render(m_renderer);
		break;
	default:
		break;
	}
	SDL_RenderPresent(m_renderer);

}

void Game::rumble()
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

void Game::resetCamera()
{
	//set camera pos
	SCREEN_WIDTH = 1500;
	SCREEN_HEIGHT = 1020;
}

void Game::getDistance() {
	//how to tell if an entity is Ai

	//get distance of oncoming object
	PositionComponent * p = (PositionComponent *)player.getCompByType("Position");
	PositionComponent * p2 = (PositionComponent *)player2.getCompByType("Position");
	PositionComponent * p3 = (PositionComponent *)player3.getCompByType("Position");



}

void Game::updateNetwork()
{
	PositionComponent * p = (PositionComponent *)player.getCompByType("Position");
	LifeComponent * l = (LifeComponent *)player.getCompByType("Life");
	AnimationComponent * ac = (AnimationComponent *)player.getCompByType("Animation");

	if (m_playerIndex != 5)
	{
		std::string pos;
		if (m_currentGameState == GameState::MainMenu && m_previousGameState == GameState::Lobby)
		{
			std::string msg;
			msg = "Lobby i: " + std::to_string(m_playerIndex) + " " + m_lobbyScreen->sendMsg(m_playerIndex);
			m_client->sendMsg(msg);
		}

		switch (m_currentGameState)
		{
		case GameState::GameScreen:
			// Send position
			switch (m_playerIndex)
			{
			case 0:
				p = (PositionComponent *)player.getCompByType("Position");
				l = (LifeComponent *)player.getCompByType("Life");
				ac = (AnimationComponent *)player.getCompByType("Animation");

				sendAiToNetwork();
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
			pos = pos +", " + "I: " + std::to_string(m_playerIndex);	// Player Index
			pos = pos + ", " + "L: " + std::to_string(l->getLife()); // Player Life
			pos = pos + ", " + "A: " + std::to_string(ac->m_currentState); // Player state
			m_client->sendMsg(pos);
			break;

		case GameState::Lobby:
			if (m_lobbyScreen->everyoneReady(m_stateTimer))
			{
				if (m_stateTimer > m_stateTimerLimit)
				{
					if (!m_lobbyScreen->getInLobby(0))
					{
						// Player 1 is an Ai
						std::cout << "Player 1 is an AI" << std::endl;
						ais.addEntity(player);
						//player.addComponent(new AIComponent());
					}

					if (!m_lobbyScreen->getInLobby(1))
					{
						// Player 2 is an Ai
						std::cout << "Player 2 is an AI" << std::endl;
						ais.addEntity(player2);
						//player2.addComponent(new AIComponent());
					}

					if (!m_lobbyScreen->getInLobby(2))
					{
						// Player 3 is an Ai
						std::cout << "Player 3 is an AI" << std::endl;
						ais.addEntity(player3);
						//player3.addComponent(new AIComponent());
					}

					if (!m_lobbyScreen->getInLobby(3))
					{
						// Player 4 is an Ai
						std::cout << "Player 4 is an AI" << std::endl;
						ais.addEntity(player4);
						//player4.addComponent(new AIComponent());
					}

					m_stateTimer = 0;
					setGameState(GameState::GameScreen);
				}
				else
				{
					m_stateTimer++;
				}
			}
			else
			{
				m_stateTimer = 0;
			}

			std::string msg;
			msg = "Lobby i: " + std::to_string(m_playerIndex) + " " + m_lobbyScreen->sendMsg(m_playerIndex);
			m_client->sendMsg(msg);

			break;

		}
	}

	// Turn message to position.
	string msg = m_client->receive();

	if (msg.length() > 0)
	{
		int indexPlayer = msg.find("Player");

		// Setting other player positions
		char firstChar = msg.at(0);
		//if (firstChar == 'S' && msg.substr(13, 3) != "IP:")
		if(indexPlayer >= 0)
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
		

		int index = msg.find("Host");
		if (index >= 0)
		{
			//player.addComponent(new HealthComponent(200));
			player.addComponent(new ControlComponent());
			player.addComponent(new ScoreComponent(0));
			player.addComponent(new LifeComponent(6, 1, m_renderer, 1));


			m_playerIndex = 0;
			m_lobbyScreen->changeState(m_playerIndex, false);
			comsystem.addEntity(player);
			comsystem.addEntity(player2);
			comsystem.addEntity(player3);
			comsystem.addEntity(player4);
			cs.addEntity(player);
			Colls.addEntity(player);
			Colls.addEntity(player2);
			Colls.addEntity(player3);
			Colls.addEntity(player4);
			phs.addEntity(player);
			p = (PositionComponent *)player.getCompByType("Position");
			p->setPosition(100, 100);

		}


		index = msg.find("Joining");
		if (index >= 0)
		{
			std::string indexString = msg.substr(index + 14, 1);
			m_playerIndex = std::stoi(indexString);
			m_lobbyScreen->changeState(m_playerIndex, false);
			switch (m_playerIndex)
			{
			case 1:
				player2.addComponent(new ControlComponent());
				player2.addComponent(new ScoreComponent(0));
				player2.addComponent(new LifeComponent(6, 2, m_renderer, 1));
				comsystem.addEntity(player2);
				cs.addEntity(player2);
				Colls.addEntity(player2);
				phs.addEntity(player2);
				p = (PositionComponent *)player2.getCompByType("Position");
				p->setPosition(500, 100);

				break;
			case 2:
				player3.addComponent(new ControlComponent());
				player3.addComponent(new ScoreComponent(0));
				player3.addComponent(new LifeComponent(6, 3, m_renderer, 1));
				comsystem.addEntity(player3);
				cs.addEntity(player3);
				Colls.addEntity(player3);
				phs.addEntity(player3);
				p = (PositionComponent *)player3.getCompByType("Position");
				p->setPosition(100, 500);

				break;
			case 3:
				player4.addComponent(new ControlComponent());
				player4.addComponent(new ScoreComponent(0));
				player4.addComponent(new LifeComponent(6, 4, m_renderer, 1));
				comsystem.addEntity(player4);
				cs.addEntity(player4);
				Colls.addEntity(player4);
				phs.addEntity(player4);
				p = (PositionComponent *)player4.getCompByType("Position");
				p->setPosition(500, 500);

			}
		}

		index = msg.find("Lobby");
		if (index >= 0)
		{
			// If you don't have a player index
			if (m_playerIndex == 5)
			{
				// Ask for your index
				std::string msg;
				msg = "What is my Index";
				m_client->sendMsg(msg);
			}


			bool readyState;
			
			if ((int)msgToPos(msg.substr(index))[1] == 1)
			{
				readyState = true;
			}
			else
			{
				readyState = false;
			}

			bool lobby;
			if ((int)msgToPos(msg.substr(index))[2] == 1)
			{
				lobby = true;
			}
			else
			{
				lobby = false;
			}

			// Set other player lobby states
			switch ((int)msgToPos(msg.substr(index))[0])
			{
			case 0:
				m_lobbyScreen->changeState(0, readyState);
				m_lobbyScreen->inLobby(0, lobby);
				if (readyState && lobby)
				{
					player.removeComponent(player.getCompByType("AI"));
				}
				break;
			case 1:
				m_lobbyScreen->changeState(1, readyState);
				m_lobbyScreen->inLobby(1, lobby);
				if (readyState && lobby)
				{
					player2.removeComponent(player2.getCompByType("AI"));
				}
				break;
			case 2:
				m_lobbyScreen->changeState(2, readyState);
				m_lobbyScreen->inLobby(2, lobby);
				if (readyState && lobby)
				{
					player3.removeComponent(player3.getCompByType("AI"));
				}
				break;
			case 3:
				m_lobbyScreen->changeState(3, readyState);
				m_lobbyScreen->inLobby(3, lobby);
				if (readyState && lobby)
				{
					player4.removeComponent(player4.getCompByType("AI"));
				}
				break;
			}

		}

		index = msg.find("Collected");
		if (index >= 0)
		{
			std::cout << "Collected: " << (int)msgToPos(msg.substr(index))[0] << std::endl;
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
				case 0:
					m_powerUps[i] = m_factory->CreateSpeed(m_renderer);
					break;

				case 1:
					m_powerUps[i] = m_factory->CreateHealth(m_renderer);
					break;

				case 2:
					m_powerUps[i] = m_factory->CreateAmmo(m_renderer);
					break;

				case 3:
					m_powerUps[i] = m_factory->CreateSeekerAmmo(m_renderer);
					break;

				case 4:
					m_powerUps[i] = m_factory->CreateReset(m_renderer);
					break;

				}
			}
		}

		index = msg.find("Score");
		if (index >= 0)
		{
			m_gameoverScreen->addPlayerScore((int)msgToPos(msg.substr(index))[1], (int)msgToPos(msg.substr(index))[0]);
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
			switch ((int)msgToPos(msg.substr(index))[0])
			{
			case 0:
				// Player 1
				v = (VelocityComponent*)player.getCompByType("Vel");
				p = (PositionComponent*)player.getCompByType("Position");
				break;

			case 1:
				// Player 2
				v = (VelocityComponent*)player2.getCompByType("Vel");
				p = (PositionComponent*)player2.getCompByType("Position");
				break;

			case 2:
				// Player 3
				v = (VelocityComponent*)player3.getCompByType("Vel");
				p = (PositionComponent*)player3.getCompByType("Position");
				break;

			case 3:
				// Player 4
				v = (VelocityComponent*)player4.getCompByType("Vel");
				p = (PositionComponent*)player4.getCompByType("Position");
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
		}

	}
}

void Game::sendAiToNetwork()
{
	if (m_playerIndex == 0)
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
				m_client->sendMsg(pos);
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
				m_client->sendMsg(pos);

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
				m_client->sendMsg(pos);

			}
			else if (aiIDs[i] == "Flag")
			{
				p = (PositionComponent *)flag.getCompByType("Position");

				pos = "Flag X: " + std::to_string((int)p->getPositionX());	// Pos X
				pos = pos + ", " + "Y: " + std::to_string((int)p->getPositionY());	// Pos Y
				pos = pos + ", " + "H: " + std::to_string(whoHasFlag());	// If someone has it
				m_client->sendMsg(pos);
			}

		}

	}
}

int Game::whoHasFlag()
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

void Game::sendPUToNetwork()
{
	if (m_playerIndex == 0)
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
			m_client->sendMsg(pu);
		}
	}
}

void Game::powerUpSpawn()
{
	m_timerSpawn++;
	if (m_timerSpawn >= m_spawnTimeLimit)
	{
		switch (rand() % m_numOfPowerUps)
		{
		case 0:
			m_powerUps.push_back(m_factory->CreateSpeed(m_renderer));
			break;

		case 1:
			m_powerUps.push_back(m_factory->CreateHealth(m_renderer));
			break;

		case 2:
			m_powerUps.push_back(m_factory->CreateAmmo(m_renderer));
			break;

		case 3:
			m_powerUps.push_back(m_factory->CreateSeekerAmmo(m_renderer));
			break;

		case 4:
			m_powerUps.push_back(m_factory->CreateReset(m_renderer));
			break;

		}
		m_timerSpawn = 0;
	}


	for (int i = m_powerUps.size() - 1; i >= 0; i--)
	{
		if (m_powerUps[i]->getAlive())
		{
			m_powerUps[i]->update();
			//check collision

			// Getting player position and the sprite dimensions
			// Set up the pointer
			PositionComponent * p = (PositionComponent *)player.getCompByType("Position");
			SpriteComponent * s = (SpriteComponent *)player.getCompByType("Sprite");
			// Set the pointer to your player
			switch (m_playerIndex)
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

void Game::updatePlayerNet(std::string s)
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