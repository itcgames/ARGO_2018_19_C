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

Game::Game(): player("Player"), player2("Player2"), player3("Player3"), player4("Player4")
{
	m_window = SDL_CreateWindow("Entity Component Systems", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1500, 900, SDL_WINDOW_OPENGL);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	m_currentGameState = (GameState::Lobby);

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (IMG_Init(imgFlags) != imgFlags)
	{
		cout << "Error: " << IMG_GetError() << endl;
	}
	m_factory = new PowerUpFactory;

	m_client = new Client();
	

	initialise();

	//phs.initialise();
	

	const auto MAP_PATH = "assets/maps/example.tmx";

	m_level = new level("Main Level");
	m_level->load(MAP_PATH, m_renderer);

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

	Entity flag("Flag");
	flag.addComponent(new PositionComponent(500, 500));
	flag.addComponent(new SpriteComponent("img/flag.png", 0.3, m_renderer, 8 , 2));


	player.addComponent(new PositionComponent(100, 100));
	player.addComponent(new SpriteComponent("img/playerSheet.png", 1, m_renderer, 3, 4));
	player.addComponent(new AnimationComponent());
	player.addComponent(new CollisionComponent());

	player2.addComponent(new PositionComponent(500, 100));
	player2.addComponent(new SpriteComponent("img/playerSheet.png", 1, m_renderer, 3, 4));
	player2.addComponent(new AnimationComponent());
	player2.addComponent(new CollisionComponent());
	
	player3.addComponent(new PositionComponent(100, 500));
	player3.addComponent(new SpriteComponent("img/playerSheet.png", 1, m_renderer, 3, 4));
	player3.addComponent(new AnimationComponent());
	player3.addComponent(new CollisionComponent());

	player4.addComponent(new PositionComponent(500, 500));
	player4.addComponent(new SpriteComponent("img/playerSheet.png", 1, m_renderer, 3, 4));
	player4.addComponent(new AnimationComponent());
	player4.addComponent(new CollisionComponent());

	Entity wall("Wall");
	//wall.addComponent(new PositionComponent(400, 500));
	//wall.addComponent(new CollisionComponent());
	//wall.addComponent(new SpriteComponent(wallTxt, m_renderer));

	Entity alien("Alien");
	alien.addComponent(new HealthComponent(60));
	alien.addComponent(new PositionComponent(200, 500));

	Entity dog("Dog");
	dog.addComponent(new HealthComponent(150));
	dog.addComponent(new PositionComponent(400, 500));

	Entity cat("Cat");
	cat.addComponent(new HealthComponent(90));
	cat.addComponent(new PositionComponent(1000, 500));
	//HealthComponent *hc;
	//PositionComponent *pc;



	
	rs.addEntity(flag);
	rs.addEntity(player);
	rs.addEntity(player2);
	rs.addEntity(player3);
	rs.addEntity(player4);
	//rs.addEntity(cat);

	ais.addEntity(alien);
	ais.addEntity(dog);
	ais.addEntity(cat);

	


	Colls.addEntity(wall);
	Colls.addEntity(flag);

	ps.addEntity(player);
	ps.addEntity(player2);
	ps.addEntity(player3);
	ps.addEntity(player4);

	AudioManager::Instance()->load("africa-toto.wav", "song1", SOUND_MUSIC);
	AudioManager::Instance()->loadSFX("Jumping.wav", "Jump", SOUND_SFX);
	//AudioManager::Instance()->PlayMusic("song1", -1);

	// Screen Initialise
	m_lobbyScreen = new Lobby(m_renderer);
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
			cs.input(event);
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


	Colls.update(*m_level, dt);
	//hs.update();
	

	switch (m_currentGameState)
	{
	case GameState::None:
		break;
	case GameState::Splash:
		break;
	case GameState::Lobby:
		m_lobbyScreen->update(m_playerIndex, mouseX, mouseY);
		mouseX = -1;
		mouseY = -1;
		break;
	case GameState::MainMenu:
		break;
	case GameState::Options:
		break;
	case GameState::GameScreen:
		//ps.update(m_renderer);
		phs.update();

		//phs.update();

	//// Power ups
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
			}
			m_timerSpawn = 0;
		}
		for (int i = m_powerUps.size() - 1; i >= 0; i--)
		{
			if (m_powerUps[i]->getAlive())
			{
				m_powerUps[i]->update();
				//check collision

				PositionComponent * p = (PositionComponent *)player.getCompByType("Position");
				SpriteComponent * s = (SpriteComponent *)player.getCompByType("Sprite");

				switch (m_playerIndex)
				{
				case 0:
					p = (PositionComponent *)player.getCompByType("Position");
					s = (SpriteComponent *)player.getCompByType("Sprite");
					break;

				case 1:
					p = (PositionComponent *)player2.getCompByType("Position");
					s = (SpriteComponent *)player2.getCompByType("Sprite");
					break;

				case 2:
					p = (PositionComponent *)player3.getCompByType("Position");
					s = (SpriteComponent *)player3.getCompByType("Sprite");
					break;

				case 3:
					p = (PositionComponent *)player4.getCompByType("Position");
					s = (SpriteComponent *)player4.getCompByType("Sprite");
					break;
				}
				if (m_powerUps[i]->pickedUp(p->getPositionX(), p->getPositionY(), s->getWidth(), s->getWidth()))
				{
					// switch case
					switch (m_powerUps[i]->getID())
					{
					case 1: // Health
						break;
					case 2:	// Speed
						break;
					}
				}
			}
			else
			{
				m_powerUps.erase(m_powerUps.begin() + i);
			}
		}

		break;
	case GameState::Credits:
		break;
	default:
		break;
	}

	updateNetwork();

	
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

		for (int i = m_powerUps.size() - 1; i >= 0; i--)
		{
			m_powerUps[i]->draw(m_renderer);
		}
		break;
	case GameState::Credits:
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
		SCREEN_HEIGHT = 901;
	}
	//pos 2
	if (rWidth == 2) {
		SCREEN_WIDTH = 1499;
		SCREEN_HEIGHT = 899;
	}
	//pos 3
	if (rWidth == 3) {
		SCREEN_WIDTH = 1489;
		SCREEN_HEIGHT = 911;
	}
	
}

void Game::resetCamera()
{
	//set camera pos
	SCREEN_WIDTH = 1500;
	SCREEN_HEIGHT = 900;
}

void Game::updateNetwork()
{
	PositionComponent * p = (PositionComponent *)player.getCompByType("Position");

	if (m_playerIndex != 5)
	{
		std::string pos;
		switch (m_currentGameState)
		{
		case GameState::GameScreen:
			// Send position
			switch (m_playerIndex)
			{
			case 0:
				p = (PositionComponent *)player.getCompByType("Position");
				break;
			case 1:
				p = (PositionComponent *)player2.getCompByType("Position");
				break;
			case 2:
				p = (PositionComponent *)player3.getCompByType("Position");
				break;
			case 3:
				p = (PositionComponent *)player4.getCompByType("Position");
				break;
			}
			pos = "X: " + std::to_string((int)p->getPositionX()) + ", " + "Y: " + std::to_string((int)p->getPositionY()) + ", " + "I: " + std::to_string(m_playerIndex);
			m_client->sendMsg(pos);
			break;
			
		case GameState::Lobby:
			std::string msg;
			msg = "i: " + std::to_string(m_playerIndex) + " " + m_lobbyScreen->sendMsg(m_playerIndex);
			m_client->sendMsg(msg);

			if (m_lobbyScreen->everyoneReady())
			{
				if (m_stateTimer > m_stateTimerLimit)
				{
					m_stateTimer = 0;
					setGameState(GameState::GameScreen);
				}
				else
				{
					m_stateTimer++;
					std::cout << std::to_string(m_stateTimer) << std::endl;
				}
			}
			else
			{
				m_stateTimer = 0;
			}
			break;

		}
	}

	// Turn message to position.
	string msg = m_client->receive();
	if (msg.length() > 0)
	{
		std::cout << "Recieved: " << msg << std::endl;
		char firstChar = msg.at(0);
		if (firstChar == 'S' && msg.substr(13, 3) != "IP:")
		{
			switch ((int)msgToPos(msg)[3])
			{
			case 0:
				p = (PositionComponent *)player.getCompByType("Position");
				break;
			case 1:
				p = (PositionComponent *)player2.getCompByType("Position");
				break;
			case 2:
				p = (PositionComponent *)player3.getCompByType("Position");
				break;
			case 3:
				p = (PositionComponent *)player4.getCompByType("Position");
				break;
			}
			
			p->setPosition(msgToPos(msg)[1], msgToPos(msg)[2]);
			
		}
		else if (msg == "Host")
		{
			m_playerIndex = 0;
			cs.addEntity(player);
			Colls.addEntity(player);
			phs.addEntity(player);
			hs.addEntity(player);
			player.addComponent(new HealthComponent(200));
			player.addComponent(new ControlComponent());
			player.addComponent(new ScoreComponent(0));
			p = (PositionComponent *)player.getCompByType("Position");
			p->setPosition(100, 100);
		}
		else if (msg.substr(0, 8) == "Joining ")
		{
			std::string indexString = msg.substr(14, 1);
			int index = std::stoi(indexString);
			m_playerIndex = index;
			switch (index)
			{
			case 1:
				cs.addEntity(player2);
				Colls.addEntity(player2);
				phs.addEntity(player2);
				hs.addEntity(player2);
				player2.addComponent(new HealthComponent(200));
				player2.addComponent(new ControlComponent());
				player2.addComponent(new ScoreComponent(0));
				p = (PositionComponent *)player2.getCompByType("Position");
				p->setPosition(500, 100);
				break;
			case 2:
				cs.addEntity(player3);
				Colls.addEntity(player3);
				phs.addEntity(player3);
				hs.addEntity(player3);
				player3.addComponent(new HealthComponent(200));
				player3.addComponent(new ControlComponent());
				player3.addComponent(new ScoreComponent(0));
				p = (PositionComponent *)player3.getCompByType("Position");
				p->setPosition(100, 500);
				break;
			case 3:
				cs.addEntity(player4);
				Colls.addEntity(player4);
				phs.addEntity(player4);
				hs.addEntity(player4);
				player4.addComponent(new HealthComponent(200));
				player4.addComponent(new ControlComponent());
				player4.addComponent(new ScoreComponent(0));
				p = (PositionComponent *)player4.getCompByType("Position");
				p->setPosition(500, 500);
				break;
			}
		}
		else if (msg.substr(5, 5) == "Ready")
		{
			if (m_playerIndex == 5)
			{
				std::string msg;
				msg = "What is my Index";
				m_client->sendMsg(msg);
			}


			bool readyState;
			if (msg[12] == '1')
			{
				readyState = true;
			}
			else
			{
				readyState = false;
			}
			switch (msg[3])
			{
			case '0':
				m_lobbyScreen->changeState(0, readyState);
				break;
			case '1':
				m_lobbyScreen->changeState(1, readyState);
				break;
			case '2':
				m_lobbyScreen->changeState(2, readyState);
				break;
			case '3':
				m_lobbyScreen->changeState(3, readyState);
				break;
			}
			
		}
		else
		{
			std::cout << msg << std::endl;
		}
		
	}
}



