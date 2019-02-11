#include "Game.h"

Game::Game(): player("Player"), ai("Ai")
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

	m_fuzzy = new Fuzzy();

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
	player.addComponent(new PositionComponent(100, 100));
	player.addComponent(new ControlComponent());

	//pass in player pos 
	//player.addComponent(new ParticleComponent(100, 100, m_renderer));
	player.addComponent(new SpriteComponent(m_texture, m_renderer));
	player.addComponent(new CollisionComponent());

	Entity wall("Wall");
	wall.addComponent(new PositionComponent(400, 500));
	wall.addComponent(new CollisionComponent());
	//wall.addComponent(new SpriteComponent(wallTxt, m_renderer));

	//Entity ai("Ai");
	ai.addComponent(new HealthComponent(60));
	ai.addComponent(new PositionComponent(500, 500));
	ai.addComponent(new SpriteComponent(m_texture, m_renderer));



	hs.addEntity(player);
	hs.addEntity(ai);

	rs.addEntity(player);
	rs.addEntity(ai);
	//rs.addEntity(alien);
	//rs.addEntity(dog);
	//rs.addEntity(cat);

	//ais.addEntity(alien);

	cs.addEntity(player);


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
	m_fuzzy->update(disBetweenAiPlayer);
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
	wallTxt.render(400, 500, m_renderer);
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


double Game::getDistance() {
	//how does one get the players x,y and the ai x, y
	
	//get distance of oncoming object
	PositionComponent * p = (PositionComponent *)player.getCompByType("Position");
	PositionComponent * a = (PositionComponent *)ai.getCompByType("Position");

	
	disBetweenAiPlayer = sqrt((p->getPositionX() - a->getPositionX())*(p->getPositionX() - a->getPositionX())
		+ (p->getPositionY() - a->getPositionY())*(p->getPositionY()  - a->getPositionY()));

	//std::cout << disBetweenAiPlayer << std::endl;
	return disBetweenAiPlayer;

}





