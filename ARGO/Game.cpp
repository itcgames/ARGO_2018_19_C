#include "Game.h"

struct not_digit {
	bool operator()(const char c)
	{
		return c != ' ' && !isdigit(c);
	}
};

std::vector<float> Game::msgToPos(std::string s)
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

Game::Game()
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

		m_client = new Client();

		initialise();



		//m_fuzzy = new Fuzzy();

	}
}


void Game::initialise()
{

	SDL_INIT_AUDIO;


	m_client->run();


	AudioManager::Instance()->load("africa-toto.wav", "song1", SOUND_MUSIC);
	AudioManager::Instance()->loadSFX("Jumping.wav", "Jump", SOUND_SFX);
	//AudioManager::Instance()->PlayMusic("song1", -1);

	// Screen Initialise
	m_lobbyScreen = new Lobby(m_renderer, this);
	m_creditsScreen = new Credits(m_renderer);
	m_gameScreen = new GameScreen(m_renderer, this);
	m_gameScreen->init(m_renderer, &m_playerIndex);
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
		m_gameScreen->input(&event, m_client);
		switch (event.type) {

		case SDL_QUIT:
			exit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&mouseX, &mouseY);
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
		//m_lobbyScreen->updateNetwork();
		break;
	case GameState::MainMenu:
		m_menuScreen->update(mouseX, mouseY, m_currentGameState);
		mouseX = -1;
		mouseY = -1;
		break;
	case GameState::Options:
		break;
	case GameState::GameScreen:
		m_gameScreen->update(m_client, dt, m_renderer);
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
		m_gameScreen->render(m_renderer, dt);
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

void Game::updateNetwork()
{

	// Turn message to position.
	std::string s = m_client->receive();
	
	if (s == "Host")
	{
		std::cout << "Shouldn't happen" << std::endl;
	}

	if (m_playerIndex != 5)
	{
		std::string pos;
		if (m_currentGameState == GameState::MainMenu && m_previousGameState == GameState::Lobby)
		{
			std::string msg;
			msg = "Lobby i: " + std::to_string(m_playerIndex) + " " + m_lobbyScreen->sendMsg(m_playerIndex);
			m_client->sendMsg(msg);
		}
	}

	int index = s.find("Score");
	if (index >= 0)
	{
		m_gameoverScreen->addPlayerScore((int)msgToPos(s.substr(index))[1], (int)msgToPos(s.substr(index))[0]);
	}
	switch (m_currentGameState)
	{
	case GameState::GameScreen:
		m_gameScreen->updateNetwork(m_client, s, m_renderer);
		break;

	case GameState::Lobby:
		m_lobbyScreen->updateNetwork(m_client, m_playerIndex, s);
		break;

	}
	

}

void Game::addPlayerScore(int index, int score)
{
	m_gameoverScreen->addPlayerScore(index, score);
}

void Game::playerAI(int pIndex, bool ai)
{
	m_gameScreen->playerAI(pIndex, ai);
}

void Game::setPlayer(int pIndex)
{
	m_playerIndex = pIndex;
	m_gameScreen->setPlayer(pIndex);
}