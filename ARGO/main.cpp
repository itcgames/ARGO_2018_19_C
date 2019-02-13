#define SDL_MAIN_HANDLED
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")

#if _DEBUG
#pragma comment(lib, "libtmxlite-s-d.lib")
#else 
#pragma comment (lib, "tmxlite.lib")
#endif 

#include "Game.h"

using namespace std;

int main(int argc, char* argv[]) {

	Game game;
	game.run();

	return 0;

}