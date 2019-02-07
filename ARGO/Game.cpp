#include "Game.h"

Game::Game()
{
	m_window = SDL_CreateWindow("Entity Component Systems", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 700, SDL_WINDOW_OPENGL);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

	if (IMG_Init(imgFlags) != imgFlags)
	{
		cout << "Error: " << IMG_GetError() << endl;
	}
	m_factory = new PowerUpFactory;


	initialise();
	m_playerDot = new Dot(false, 100, 100);
	m_playerDot->Init(m_renderer);

}


void Game::initialise()
{
	if (!m_texture.loadFromFile("dot.bmp", m_renderer))
	{
		printf("Failed to load dot texture!\n");

	}

	m_powerUps.push_back(m_factory->CreateSpeed(m_renderer));
	m_powerUps.push_back(m_factory->CreateHealth(m_renderer));

	Entity player("Player");
	player.addComponent(new HealthComponent(200));
	player.addComponent(new PositionComponent(100, 100));
	player.addComponent(new ControlComponent());
	player.addComponent(new SpriteComponent(m_texture, m_renderer));


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

	hs.addEntity(player);
	hs.addEntity(alien);
	hs.addEntity(dog);
	hs.addEntity(cat);


	rs.addEntity(player);
	//rs.addEntity(alien);
	//rs.addEntity(dog);
	//rs.addEntity(cat);

	ais.addEntity(alien);
	ais.addEntity(dog);
	ais.addEntity(cat);

	cs.addEntity(player);

	
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
		case SDL_KEYDOWN:
			cs.input(event);
			if (event.key.keysym.sym == SDLK_ESCAPE)
				exit = true;
			break;
		}
	}
}

void Game::update()
{
	for (int i = m_powerUps.size() - 1; i >= 0; i--)
	{
		if (m_powerUps[i]->getAlive())
		{
			m_powerUps[i]->update();
		}
		else
		{
			m_powerUps.erase(m_powerUps.begin() + i);
		}
	}
}

void Game::render()
{
	if (m_renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}
	
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_renderer);
	rs.update(m_renderer);

	for (int i = m_powerUps.size() - 1; i >= 0; i--)
	{
			m_powerUps[i]->draw(m_renderer);
	}
	//m_playerDot->render(m_renderer);
	//m_texture.render(100, 100, m_renderer);
	SDL_RenderPresent(m_renderer);

}
