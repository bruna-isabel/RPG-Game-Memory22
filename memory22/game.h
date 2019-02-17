//#include "SDL.h"
#pragma once
#include <stdio.h>
//#include "SDL_image.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2/SDL.h"

class Game {

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();

	void update();

	void render();

	void clean();

	bool running() 
	{ return isRunning; };

	static SDL_Event event;
    
private:
	int counter;
	bool isRunning;
	SDL_Window *window;
	SDL_Renderer *renderer;
};
