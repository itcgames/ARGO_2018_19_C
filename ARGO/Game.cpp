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

Game::Game(): player("Player"), player2("Player2"), player3("Player3"), player4("Player4")
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

		m_currentGameState = (GameState::GameScreen);

		int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		if (IMG_Init(imgFlags) != imgFlags)
		{
			cout << "Error: " << IMG_GetError() << endl;
		}
		m_factory = new PowerUpFactory;

		m_client = new Client();

		initialise();

		//phs.initialise();


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



	Entity flag("Flag");
	flag.addComponent(new PositionComponent(1000, 600));
	flag.addComponent(new SpriteComponent("img/flag.png", 0.3, m_renderer, 8 , 2));
	flag.addComponent(new PickUpComponent());


	player.addComponent(new PositionComponent(300, 100));
	player.addComponent(new SpriteComponent("img/playerSheet.png", 0.5, m_renderer, 3, 5));
	player.addComponent(new AnimationComponent());
	player.addComponent(new CollisionComponent());
	player.addComponent(new AmmoComponent(m_renderer));
	player.addComponent(new LifeComponent(4, 1, m_renderer, 1));


	player2.addComponent(new PositionComponent(500, 100));
	player2.addComponent(new SpriteComponent("img/playerSheet.png", 0.5, m_renderer, 3, 5));
	player2.addComponent(new AnimationComponent());
	player2.addComponent(new CollisionComponent());
	player2.addComponent(new AmmoComponent(m_renderer));
	player2.addComponent(new LifeComponent(5, 2, m_renderer, 1));
	player2.addComponent(new VelocityComponent());
	player2.addComponent(new AIComponent());



	player3.addComponent(new PositionComponent(75, 800));
	player3.addComponent(new SpriteComponent("img/playerSheet.png", 0.5, m_renderer, 3, 5));
	player3.addComponent(new AnimationComponent());
	player3.addComponent(new CollisionComponent());
	player3.addComponent(new AmmoComponent(m_renderer));
	player3.addComponent(new LifeComponent(6, 3, m_renderer, 1));
	player3.addComponent(new VelocityComponent());
	player3.addComponent(new AIComponent());

	player4.addComponent(new PositionComponent(500, 500));
	player4.addComponent(new SpriteComponent("img/playerSheet.png", 0.5, m_renderer, 3, 5));
	player4.addComponent(new AnimationComponent());
	player4.addComponent(new CollisionComponent());
	player4.addComponent(new AmmoComponent(m_renderer));
	player4.addComponent(new LifeComponent(3, 4, m_renderer, 1));
	player4.addComponent(new AIComponent());

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

	//rs.addEntity(cat);

	//ais.addEntity(alien);
	//ais.addEntity(dog);
	//ais.addEntity(cat);

	player2.addComponent(new ControlComponent());
	player3.addComponent(new ControlComponent());
	player4.addComponent(new ControlComponent());
	player2.addComponent(new ScoreComponent(0));
	player3.addComponent(new ScoreComponent(0));
	player4.addComponent(new ScoreComponent(0));

	ais.addEntity(player3);
	//ais.addEntity(player3);
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
	updateNetwork();


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
	updateNetwork();
	
	//hs.update();
	ammos.update();

	if (m_playerIndex> 0)
	{
		playerID = "Player" + std::to_string(m_playerIndex + 1);
	}
	else {
		playerID = "Player";
	}




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
		comsystem.update(dt, playerID);
		ls.update(dt);
		ais.update(*m_level);
		Colls.CheckCollision(*m_level, dt, playerID);

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

			case 5:
				m_powerUps.push_back(m_factory->CreateReset(m_renderer));
				break;

			}
			m_timerSpawn = 0;
		}


		for (int i = m_powerUps.size() - 1; i >= 0; i--)
		{
			if (m_powerUps[i]->getAlive())

				// Power ups
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
		}
		updateNetwork();

		ls.update(dt);
		for (int j = m_powerUps.size() - 1; j >= 0; j--)
		{
			if (m_powerUps[j]->getAlive())
			{
				m_powerUps[j]->update();
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

				if (m_powerUps[j]->pickedUp(p->getPositionX(), p->getPositionY(), s->getWidth(), s->getWidth()))
				{
					// switch case
					switch (m_powerUps[j]->getID())
					{
					case 1: // Health
						break;
					case 2:	// Speed
						break;
					case 3: // Ammo
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

						break;
					case 4: // SeekerAmmo
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
						break;
					case 5: // Reset
						break;

					}
				}


			}
			else
			{
				m_powerUps.erase(m_powerUps.begin() + j);
			}
		}
		//ais.update(1000, ais.getEntityById("Player2"));
		//ais.update(1000, ais.getEntityById("Player3"));
		break;

	case GameState::Credits:
		break;
	default:
		break;
		
	}
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
    ammos.render(m_renderer);
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


	//for (int i = 0; i < ais.getEntityIds().size(); i++) {


	//	if (ais.getEntityIds()[i] == "Player") {
	//		float pVp2 = sqrt((p->getPositionX() - p2->getPositionX())*(p->getPositionX() - p2->getPositionX())
	//			+ (p->getPositionY() - p2->getPositionY())*(p->getPositionY() - p2->getPositionY()));

	//		float pVp3 = sqrt((p->getPositionX() - p2->getPositionX())*(p->getPositionX() - p2->getPositionX())
	//			+ (p->getPositionY() - p2->getPositionY())*(p->getPositionY() - p2->getPositionY()));

	//		if (pVp2 > pVp3) {
	//			int playerX = p->getPositionX();
	//			int player3X = p3->getPositionX();
	//			if (player3X > playerX) {
	//				pVp3 = pVp3 * -1;
	//			}
	//			disBetweenAiPlayer = pVp3;

	//			ais.update(disBetweenAiPlayer, ais.getEntityById("Player"));
	//		}
	//		else {
	//			int playerX = p->getPositionX();
	//			int player2X = p2->getPositionX();
	//			if (player2X > playerX) {
	//				pVp2 = pVp2 * -1;
	//			}

	//			disBetweenAiPlayer = pVp2;
	//			ais.update(disBetweenAiPlayer, ais.getEntityById("Player"));
	//		}

	//	}

	//	if (ais.getEntityIds()[i] == "Player2") {
	//		float p2Vp = sqrt((p->getPositionX() - p2->getPositionX())*(p->getPositionX() - p2->getPositionX())
	//			+ (p->getPositionY() - p2->getPositionY())*(p->getPositionY() - p2->getPositionY()));

	//		float p2Vp3 = sqrt((p3->getPositionX() - p2->getPositionX())*(p3->getPositionX() - p2->getPositionX())
	//			+ (p3->getPositionY() - p2->getPositionY())*(p3->getPositionY() - p2->getPositionY()));

	//		if (p2Vp > p2Vp3) {
	//			//get what side thet ai is on
	//			int player2X = p2->getPositionX();
	//			int player3X = p3->getPositionX();
	//			if (player3X > player2X) {
	//				p2Vp3 = p2Vp3 * -1;
	//			}
	//			disBetweenAiPlayer = p2Vp3;
	//			ais.update(disBetweenAiPlayer, ais.getEntityById("Player2"));
	//		}
	//		else {
	//			//get what side thet ai is on
	//			int playerX = p->getPositionX();
	//			int player2X = p2->getPositionX();
	//			if (playerX > player2X) {
	//				p2Vp = p2Vp * -1;
	//			}
	//			disBetweenAiPlayer = p2Vp;
	//			ais.update(disBetweenAiPlayer, ais.getEntityById("Player2"));
	//		}
	//	}

	//	if (ais.getEntityIds()[i] == "Player3") {
	//		float p3Vp2 = sqrt((p3->getPositionX() - p2->getPositionX())*(p3->getPositionX() - p2->getPositionX())
	//			+ (p3->getPositionY() - p2->getPositionY())*(p3->getPositionY() - p2->getPositionY()));

	//		float p3Vp = sqrt((p->getPositionX() - p3->getPositionX())*(p->getPositionX() - p3->getPositionX())
	//			+ (p->getPositionY() - p3->getPositionY())*(p->getPositionY() - p3->getPositionY()));


	//		if (p3Vp2 > p3Vp) {
	//			disBetweenAiPlayer = p3Vp;
	//			//get what side thet ai is on
	//			int playerX = p->getPositionX();
	//			int player3X = p3->getPositionX();
	//			if (playerX > player3X) {
	//				p3Vp = p3Vp * -1;
	//			}
	//			disBetweenAiPlayer = p3Vp;
	//			//return disBetweenAiPlayer;
	//			ais.update(disBetweenAiPlayer, ais.getEntityById("Player3"));
	//		}
	//		else {
	//			int player2X = p2->getPositionX();
	//			int player3X = p3->getPositionX();
	//			if (player2X > player3X) {
	//				p3Vp2 = p3Vp2 * -1;
	//			}
	//			disBetweenAiPlayer = p3Vp2;
	//			//call update
	//			ais.update(disBetweenAiPlayer, ais.getEntityById("Player3"));
	//		}
	//	}

	//}




}

void Game::updateNetwork()
{
	PositionComponent * p = (PositionComponent *)player.getCompByType("Position");
	LifeComponent * l = (LifeComponent *)player.getCompByType("Life");
	AnimationComponent * ac = (AnimationComponent *)player.getCompByType("Animation");

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

			pos = "X: " + std::to_string((int)p->getPositionX());	// Pos X
			pos = pos + ", " + "Y: " + std::to_string((int)p->getPositionY());	// Pos Y
			pos = pos +", " + "I: " + std::to_string(m_playerIndex);	// Player Index
			pos = pos + ", " + "L: " + std::to_string(l->getLife()); // Player Life
			pos = pos + ", " + "A: " + std::to_string(ac->m_currentState); // Player state
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
		char firstChar = msg.at(0);
		if (firstChar == 'S' && msg.substr(13, 3) != "IP:")
		{
			switch ((int)msgToPos(msg)[3])
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

			p->setPosition(msgToPos(msg)[1], msgToPos(msg)[2]);
			l->setLifes(msgToPos(msg)[4]);

			switch ((int)msgToPos(msg)[5])
			{
			case 0:
				ac->m_currentState = ac->AniState::idleS;
				break;

			case 1:
				ac->m_currentState = ac->AniState::leftS;
				break;

			case 2:
				ac->m_currentState = ac->AniState::rightS;
				break;

			case 3:
				ac->m_currentState = ac->AniState::jumpLeftS;
				break;

			case 4:
				ac->m_currentState = ac->AniState::jumpRightS;
				break;

			default:
				std::cout << "Oops! Missing animation" << std::endl;
				break;
			}

		}
		else if (msg == "Host")
		{
			//player.addComponent(new HealthComponent(200));
			player.addComponent(new ControlComponent());
			player.addComponent(new ScoreComponent(0));
			player.addComponent(new LifeComponent(6, 1, m_renderer, 1));


			m_playerIndex = 0;
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
			//hs.addEntity(player);
			p = (PositionComponent *)player.getCompByType("Position");
			p->setPosition(100, 100);

			player2.addComponent(new VelocityComponent());
			player3.addComponent(new VelocityComponent());
			player4.addComponent(new VelocityComponent());

			player2.addComponent(new ControlComponent());
			player3.addComponent(new ControlComponent());
			player4.addComponent(new ControlComponent());



		}
		else if (msg.substr(0, 8) == "Joining ")
		{
			std::string indexString = msg.substr(14, 1);
			int index = std::stoi(indexString);
			m_playerIndex = index;
			switch (index)
			{
			case 1:
				//player2.addComponent(new HealthComponent(200));
				player2.addComponent(new ControlComponent());
				player2.addComponent(new ScoreComponent(0));
				player2.addComponent(new LifeComponent(6, 2, m_renderer, 1));
				comsystem.addEntity(player2);
				cs.addEntity(player2);
				Colls.addEntity(player2);
				phs.addEntity(player2);
				//hs.addEntity(player2);
				p = (PositionComponent *)player2.getCompByType("Position");
				p->setPosition(500, 100);

				player.addComponent(new  VelocityComponent());
				player3.addComponent(new VelocityComponent());
				player4.addComponent(new VelocityComponent());
				break;
			case 2:
			//	player3.addComponent(new HealthComponent(200));
				player3.addComponent(new ControlComponent());
				player3.addComponent(new ScoreComponent(0));
				player3.addComponent(new LifeComponent(6, 3, m_renderer, 1));
				comsystem.addEntity(player3);
				cs.addEntity(player3);
				Colls.addEntity(player3);
				phs.addEntity(player3);
			//	hs.addEntity(player3);
				p = (PositionComponent *)player3.getCompByType("Position");
				p->setPosition(100, 500);

				player.addComponent(new  VelocityComponent());
				player2.addComponent(new VelocityComponent());
				player4.addComponent(new  VelocityComponent());
				break;
			case 3:
			//	player4.addComponent(new HealthComponent(200));
				player4.addComponent(new ControlComponent());
				player4.addComponent(new ScoreComponent(0));
				player4.addComponent(new LifeComponent(6, 4, m_renderer, 1));
				comsystem.addEntity(player4);
				cs.addEntity(player4);
				Colls.addEntity(player4);
				phs.addEntity(player4);
			//	hs.addEntity(player4);
				p = (PositionComponent *)player4.getCompByType("Position");
				p->setPosition(500, 500);

				player.addComponent(new  VelocityComponent());
				player2.addComponent(new VelocityComponent());
				player3.addComponent(new VelocityComponent());
			}
		}
		else if (msg.length() > 5 && msg.substr(5, 5) == "Ready")
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
				if (readyState)
				{
					player.removeComponent(player.getCompByType("AI"));
				}
				break;
			case '1':
				m_lobbyScreen->changeState(1, readyState);
				if (readyState)
				{
					player2.removeComponent(player2.getCompByType("AI"));
				}
				break;
			case '2':
				m_lobbyScreen->changeState(2, readyState);
				if (readyState)
				{
					player3.removeComponent(player3.getCompByType("AI"));
				}
				break;
			case '3':
				m_lobbyScreen->changeState(3, readyState);
				if (readyState)
				{
					player4.removeComponent(player4.getCompByType("AI"));
				}
				break;
			}

		}
		else
		{
			std::cout << "Error! Unknown message:" << msg << std::endl;
		}

	}
}
