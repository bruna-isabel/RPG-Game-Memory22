#include "game.h"
#include <iostream>
#include "textures.h"
#include "database.h"
#include "startMenu.h"
#include <map>
#include "gameObject.h"
#include "map.h"
#include "inventory.h"
#include "items.h"

GameObject* player;
GameObject* enemy;
Database *database;
startMenu *menu;
SDL_Event Game::event;
map* map1; //creates map1 object pointer
//Inventory* invt;
int nri = 0,ok=0;
int k = 0;
Inventory* inv;
Item* item1;
Item* item;


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

		inv = new Inventory();
		item1 = new Item(5*32,7*32, 1, renderer); //creating the first weapon

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
	//invt = new Inventory();
	//invt->init();
    
	for (std::vector<GameObject *>::iterator it = GameObject::allEntities.begin(); it != GameObject::allEntities.end(); it++) {
		int hp = (*it)->getCurrentHp();
		
		std::cout << hp << std::endl;
	}
	std::cout << typeid(GameObject::allEntities[0]).name() << std::endl;
    map1 = new map(renderer); //creates first map object
}

void Game::handleEvents()
{
	int ItemX = item1->getX();
	int ItemY = item1->getY();
	int PlayerX = player->getX();
	int PlayerY = player->getY();

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
		case SDLK_i:
			nri++;
			if (nri == 1)
			{
				inv->openInventory();
				SDL_RenderPresent(renderer);
			}
			else
			{
				inv->closeInventory();
				nri = 0;
			}
			break;
		case SDLK_k:
			player->attack();
			if (enemy->getCurrentHp() > 0) {
				std::cout << enemy->getCurrentHp() << std::endl;
			}
			else if (enemy->getKilled() == 1 && k==0)
			{
				std::cout << "Enemy Killed!" << std::endl;
				std::cout << "It looks like he dropped something in the grass" << std::endl;
				std::cout << "I think it's an armour" << std::endl;
				k = 1;
				item = new Item(player->getX(), player->getY(), 0, renderer);
				item->spawnItem(renderer);
				render();
				
			}
			break;
		case SDLK_q:
			if ((ItemX <= PlayerX + 36 && ItemX >= PlayerX - 48 - 36) && (ItemY <= PlayerY + 36 && ItemY >= PlayerY - 48 - 36))
			{
				if (item1->getPicked() == 0)
				{
					std::cout << "You found an item!!" << std::endl;
					inv->getItem(ItemX, ItemY, item1->getType());
					std::cout << "You picked it up!" << std::endl;
					std::cout << "The item is now in your inventory" << std::endl;
					item1->HideItem(renderer);
					SDL_RenderPresent(renderer);
				}
			}
			else
			{
				if (item)
				{
					ItemX = item->getX();
					ItemY = item->getY();
					if ((ItemX <= PlayerX + 36 && ItemX >= PlayerX - 48 - 36) && (ItemY <= PlayerY + 36 && ItemY >= PlayerY - 48 - 36))
						if (item->getPicked() == 0)
					{
						std::cout << "You found an item!!" << std::endl;
						inv->getItem(item->getX(), item->getY(), item->getType());
						std::cout << "You picked it up!" << std::endl;
						std::cout << "The item is now in your inventory" << std::endl;
						item->HideItem(renderer);
						SDL_RenderPresent(renderer);
					}
				}
			}
			break;
		case SDLK_ESCAPE:
			menu->menuLoop(window);
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
}

void Game::render()
{
	SDL_RenderClear(renderer);
    map1->drawMap(renderer); //draws map1 object
	if(item1->getPicked() == 0)
		item1->spawnItem(renderer); // spawns first item
	if (item)
		if (item->getPicked() == 0)
			item->spawnItem(renderer);
    if ((player->getCurrentHp()) > 0) {
		player->Render();
	}
	if ((enemy->getCurrentHp()) > 0) {
		enemy->Render();
	}

    SDL_RenderPresent(renderer);
    

}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game cleaned";
}
