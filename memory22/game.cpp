#include "game.h"
#include <iostream>
#include "textures.h"
#include "database.h"
#include "startMenu.h"
#include <map>
#include "gameObject.h"
#include "map.h"

GameObject* player;
GameObject* enemy;
GameObject* bmario;
GameObject* pikachu;
Database *database;
startMenu *menu;
SDL_Event Game::event;
map* map1; //creates map1 object pointer



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
			//L_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Created" << std::endl;
			
		}
		menu = new startMenu(window);
		menu->menuLoop(window);
		isRunning = true; // If everything initializes correctly makes the game loop condition true
	}
	else 
	{
		isRunning = false;
	}

	database = new Database("Database");
	database->presetGameData();

	//Obtaining Player Data from Database
	std::map < std::string, std::string> playerData;
	playerData = database->selectQuery("player");
	int pCurrentHealth = std::stoi(playerData["CurrentHealth"]);
	int pMaxHealth = std::stoi(playerData["MaxHealth"]);
	int pStrength = std::stoi(playerData["Strength"]);
	int pXCor = std::stoi(playerData["XCoordinate"]);
	int pYCor = std::stoi(playerData["XCoordinate"]);
	std::string name = playerData["Name"];
	
	

	player = new GameObject("player.png", renderer, pXCor, pYCor, pMaxHealth, pCurrentHealth, pStrength);
	enemy = new GameObject("enemy.png", renderer, 500, 500, 10, 10, 2);
    	// Adding two NPCs
	bmario = new GameObject("kewlStuffs/bmario.png", renderer, 400, 400, 999, 999, 999);
	pikachu = new GameObject("kewlStuffs/pikachu.png", renderer, 100, 200, 999, 999, 999);
	
	for (std::vector<GameObject *>::iterator it = GameObject::allEntities.begin(); it != GameObject::allEntities.end(); it++) {
		int hp = (*it)->getCurrentHp();
		
		std::cout << hp << std::endl;
	}
	std::cout << typeid(GameObject::allEntities[0]).name() << std::endl;
    map1 = new map(renderer); //creates first map object
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
		case SDLK_k:
			player->attack();
			if (enemy->getCurrentHp() >0) {
				std::cout << enemy->getCurrentHp() << std::endl;
			}
			break;
		case SDLK_ESCAPE:
			if(!menu->menuLoop(window))
			{
				isRunning = false;
			}
			break;

		}
	default:
		break;
	}
}

void Game::update()
{
	
	player->update();
	
	enemy->update();
	
	bmario->update();

	pikachu->update();
}


void Game::render()
{
	SDL_RenderClear(renderer);
        map1->drawMap(renderer, "field.txt"); //draws map1 object

    if ((player->getCurrentHp()) > 0) {
		player->Render();
	}
	if ((enemy->getCurrentHp()) > 0) {
		enemy->Render();
	}
        if ((bmario->getCurrentHp()) > 0) {
		bmario->Render();
	}

	pikachu->Render();	

    
    SDL_RenderPresent(renderer);
    

}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game cleaned";
}
