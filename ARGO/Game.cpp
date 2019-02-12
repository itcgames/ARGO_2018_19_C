#include "Game.h"

Game::Game(): player("Player"), player2("Player2"), player3("Player3"), player4("Player4")
{
	m_window = SDL_CreateWindow("Entity Component Systems", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1500, 900, SDL_WINDOW_OPENGL);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

	if (IMG_Init(imgFlags) != imgFlags)
	{
		cout << "Error: " << IMG_GetError() << endl;
	}
	m_factory = new PowerUpFactory;


	initialise();
	ps.initialise();
	m_playerDot = new Dot(false, 100, 100);
	m_playerDot->Init(m_renderer);


	const auto MAP_PATH = "assets/maps/example.tmx";

	m_level = new level("Main Level");
	m_level->load(MAP_PATH, m_renderer);

	//m_fuzzy = new Fuzzy();

}


void Game::initialise()
{

	m_timerSpawn = 0;
	if (!m_texture.loadFromFile("dot.bmp", m_renderer))

	{
		printf("Failed to load dot texture!\n");

	}
	if (!wallTxt.loadFromFile("wall.bmp", m_renderer))
	{
		printf("Failed to load wall texture!\n");
	}

	
	player.addComponent(new HealthComponent(200));
	player.addComponent(new PositionComponent(300, 100));
	player.addComponent(new ControlComponent());
	player.addComponent(new SpriteComponent(m_texture, m_renderer));
	player.addComponent(new CollisionComponent());

	Entity wall("Wall");
	wall.addComponent(new PositionComponent(1000, 500));
	wall.addComponent(new CollisionComponent());
	//wall.addComponent(new SpriteComponent(wallTxt, m_renderer));

	//player2 is AI
	player2.addComponent(new HealthComponent(60));
	player2.addComponent(new PositionComponent(100, 500));
	player2.addComponent(new SpriteComponent(m_texture, m_renderer));
	player2.addComponent(new CollisionComponent());
	player2.addComponent(new AIComponent());


	player3.addComponent(new HealthComponent(60));
	player3.addComponent(new PositionComponent(500, 500));
	player3.addComponent(new SpriteComponent(m_texture, m_renderer));
	player3.addComponent(new CollisionComponent());
	player3.addComponent(new AIComponent());


	hs.addEntity(player);
	hs.addEntity(player2);
	hs.addEntity(player3);

	rs.addEntity(player);
	rs.addEntity(player2);
	rs.addEntity(player3);

	cs.addEntity(player);

	ais.addEntity(player2);
	ais.addEntity(player3);

	Colls.addEntity(player);
	Colls.addEntity(wall);

	ps.addEntity(player);
	phs.addEntity(player);
	//phs.addEntity(ai);


	
}

Game::~Game()
{
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

		update();
		render();

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

void Game::update()
{

	Colls.update();
	phs.update();

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
		}
		m_timerSpawn = 0;
	}
	for (int i = m_powerUps.size() - 1; i >= 0; i--)
	{
		if (m_powerUps[i]->getAlive())
		{
			m_powerUps[i]->update();
			//check collision
			PositionComponent * p = (PositionComponent * )player.getCompByType("Position");
			SpriteComponent * s = (SpriteComponent *)player.getCompByType("Sprite");
			if(m_powerUps[i]->pickedUp(p->getPositionX(), p->getPositionY(), s->getWidth(), s->getWidth()))
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
	getDistance();
}

void Game::render()
{
	if (m_renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_renderer);
	
	//Jamie
	SDL_RenderSetLogicalSize(m_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	rs.update(m_renderer);
	wallTxt.render(1000, 500, m_renderer);
	ps.update(m_renderer);
	m_level->draw(m_renderer);
	//m_playerDot->render(m_renderer);
	//m_texture.render(100, 100, m_renderer);

	for (int i = m_powerUps.size() - 1; i >= 0; i--)
	{
			m_powerUps[i]->draw(m_renderer);
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

void Game::getDistance() {
	//how to tell if an entity is Ai

	//get distance of oncoming object
	PositionComponent * p = (PositionComponent *)player.getCompByType("Position");
	PositionComponent * p2 = (PositionComponent *)player2.getCompByType("Position");
	PositionComponent * p3 = (PositionComponent *)player3.getCompByType("Position");


	for (int i = 0; i < ais.getEntityIds().size(); i++) {
	

		if (ais.getEntityIds()[i] == "Player") {
			float pVp2 = sqrt((p->getPositionX() - p2->getPositionX())*(p->getPositionX() - p2->getPositionX())
				+ (p->getPositionY() - p2->getPositionY())*(p->getPositionY() - p2->getPositionY()));

			float pVp3 = sqrt((p->getPositionX() - p2->getPositionX())*(p->getPositionX() - p2->getPositionX())
				+ (p->getPositionY() - p2->getPositionY())*(p->getPositionY() - p2->getPositionY()));

			if (pVp2 > pVp3) {
				int playerX = p->getPositionX();
				int player3X = p3->getPositionX();
				if (player3X > playerX) {
					pVp3 = pVp3 * -1;
				}
				disBetweenAiPlayer = pVp3;
				
				ais.update(disBetweenAiPlayer, ais.getEntityById("Player"));
			}
			else {
				int playerX = p->getPositionX();
				int player2X = p2->getPositionX();
				if (player2X > playerX) {
					pVp2 = pVp2 * -1;
				}

				disBetweenAiPlayer = pVp2;
				ais.update(disBetweenAiPlayer, ais.getEntityById("Player"));
			}

		}

		if (ais.getEntityIds()[i] == "Player2") {
			float p2Vp = sqrt((p->getPositionX() - p2->getPositionX())*(p->getPositionX() - p2->getPositionX())
				+ (p->getPositionY() - p2->getPositionY())*(p->getPositionY() - p2->getPositionY()));

			float p2Vp3 = sqrt((p3->getPositionX() - p2->getPositionX())*(p3->getPositionX() - p2->getPositionX())
				+ (p3->getPositionY() - p2->getPositionY())*(p3->getPositionY() - p2->getPositionY()));

			if (p2Vp > p2Vp3) {
				//get what side thet ai is on
				int player2X = p2->getPositionX();
				int player3X = p3->getPositionX();
				if (player3X > player2X) {
					p2Vp3 = p2Vp3 * -1;
				}
				disBetweenAiPlayer = p2Vp3;
				ais.update(disBetweenAiPlayer, ais.getEntityById("Player2"));
			}
			else {
				//get what side thet ai is on
				int playerX = p->getPositionX();
				int player2X = p2->getPositionX();
				if (playerX > player2X) {
					p2Vp = p2Vp * -1;
				}
				disBetweenAiPlayer = p2Vp;
				ais.update(disBetweenAiPlayer, ais.getEntityById("Player2"));
			}
		}

		if (ais.getEntityIds()[i] == "Player3") {
			float p3Vp2 = sqrt((p3->getPositionX() - p2->getPositionX())*(p3->getPositionX() - p2->getPositionX())
				+ (p3->getPositionY() - p2->getPositionY())*(p3->getPositionY() - p2->getPositionY()));

			float p3Vp = sqrt((p->getPositionX() - p3->getPositionX())*(p->getPositionX() - p3->getPositionX())
				+ (p->getPositionY() - p3->getPositionY())*(p->getPositionY() - p3->getPositionY()));

		
			if (p3Vp2 > p3Vp) {
				disBetweenAiPlayer = p3Vp;
				//get what side thet ai is on
				int playerX = p->getPositionX();
				int player3X = p3->getPositionX();
				if (playerX > player3X) {
					p3Vp = p3Vp * -1;
				}
				disBetweenAiPlayer = p3Vp;
				//return disBetweenAiPlayer;
				ais.update(disBetweenAiPlayer, ais.getEntityById("Player3"));
			}
			else {
				int player2X = p2->getPositionX();
				int player3X = p3->getPositionX();
				if (player2X > player3X) {
					p3Vp2 = p3Vp2 * -1;
				}
				disBetweenAiPlayer = p3Vp2;
				//call update
				ais.update(disBetweenAiPlayer, ais.getEntityById("Player3"));
			}
		}
		
	}

	

}


