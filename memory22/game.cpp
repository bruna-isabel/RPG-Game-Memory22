#include "game.h"
#include <iostream>
#include "textures.h"
#include "gameObject.h"

gameObject* player;
SDL_Event Game::event;
Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL systems initialized" << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window Created" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) 
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Created" << std::endl;
			
		}
		isRunning = true; // If everything initializes correctly makes the game loop condition true
	}
	else 
	{
		isRunning = false;
	}

	player = new gameObject("player.png", renderer, 0 , 0);
}

void Game::handleEvents()
{

	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) 
		{ 
		case SDLK_w:
			player->movement("x", true); 
			break;
		case SDLK_s:
			player->movement("x", false);
			break;
		case SDLK_d:
			player->movement("y", true);
			break;
		case SDLK_a:
			player->movement("y", false);
			break;
		}
	default:
		break;
	}
}

void Game::update()
{
	player->update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	player->Render();
	SDL_RenderPresent(renderer);

}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game cleaned";
}