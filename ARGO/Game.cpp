#include "Game.h"

Game::Game()
{
	m_window = SDL_CreateWindow("Entity Component Systems", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 700, SDL_WINDOW_OPENGL);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	m_currentGameState = (GameState::GameScreen);

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

	if (IMG_Init(imgFlags) != imgFlags)
	{
		cout << "Error: " << IMG_GetError() << endl;
	}

	initialise();
	//m_playerDot = new Dot(false, 100, 100);
	//m_playerDot->Init(m_renderer);
}


void Game::initialise()
{
	

	Entity player("Player");
	player.addComponent(new HealthComponent(200));
	player.addComponent(new PositionComponent(100, 100));
	player.addComponent(new ControlComponent());
	player.addComponent(new SpriteComponent("img/playerSheet.png", 0.3, m_renderer));
	player.addComponent(new AnimationComponent());


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

	ps.addEntity(player);

	
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
			break;
		case SDL_KEYDOWN:
			cs.input(event);
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

void Game::update()
{
	//hs.update();
	

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
	case GameState::GameScreen:
		ps.update();
		break;
	case GameState::Credits:
		break;
	default:
		break;
	}

}

void Game::render()
{
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
	case GameState::GameScreen:
		break;
	case GameState::Credits:
		break;
	default:
		break;
	}

	if (m_renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}

	
	
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	SDL_RenderClear(m_renderer);
	rs.update(m_renderer);
	//m_playerDot->render(m_renderer);
	//m_texture.render(100, 100, m_renderer);
	SDL_RenderPresent(m_renderer);

}
