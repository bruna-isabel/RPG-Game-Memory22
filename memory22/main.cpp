//#include "SDL.h"
// #include "SDL_image.h"
#include "SDL2/SDL.h"
#include <stdio.h>
#include "game.h"


Game *game = nullptr;

int main(int argc, char* argv[]) {

	const int framerate = 60;
	const int frameDelay = 1000 / framerate;
	
	Uint32 frameBegin;
	int frameTime;

	game = new Game();
	game->init("Memory 22", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (game->running()) 
	{
		frameBegin = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();
		frameTime =  SDL_GetTicks() - frameBegin;

		if (frameTime < frameDelay)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}
