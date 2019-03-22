#include "startMenu.h"
#include <iostream>


startMenu::startMenu(SDL_Window *window)
{
	gScreenSurface = SDL_GetWindowSurface( window );
}


startMenu::~startMenu()
{
	//SDL_DestroyWindow( window );
	//SDL_Quit();
}



SDL_Surface* startMenu::loadSurface( std::string path )
{
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	return loadedSurface;
}



void startMenu::render()
{
	gKeyPressSurfaces[ newGame ] = loadSurface( "kewlStuffs/newgame.bmp" );
	gKeyPressSurfaces[ continueGame ] = loadSurface( "kewlStuffs/continue.bmp" );
	gKeyPressSurfaces[ saveGame ] = loadSurface( "kewlStuffs/save.bmp" );
	gKeyPressSurfaces[ exitGame ] = loadSurface( "kewlStuffs/exit.bmp" );
}




bool startMenu::menuLoop(SDL_Window *window)
{
	render();
	quit = false;
	SDL_Event e;
	gCurrentSurface = gKeyPressSurfaces[continueGame];
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_w:
					if (index == 0)
					{
						index = 3;
					}
					else
					{
						index = index - 1;
					}
					//std::cout<<index<<std::endl;
					gCurrentSurface = gKeyPressSurfaces[index];
					break;

				case SDLK_s:
					if (index == 3)
					{
						index = 0;
					}
					else
					{
						index = index + 1;
					}
					//std::cout<<index<<std::endl;
					gCurrentSurface = gKeyPressSurfaces[index];
					break;

				case SDLK_RETURN:
					if (index == 0)
					{
						std::cout << "Continue" << std::endl;
						quit = true;
						break;
					}
					else if (index == 1)
					{
						std::cout << "New Game" << std::endl;
						//db->deleteData();
						//db->presetGameData();
						quit = true;
						break;
					}
					else if (index == 2)
					{
						std::cout << "Save Game" << std::endl;
						//insert items and quests into respective tables
						quit = true;
						break;
					}
					else if (index == 3)
					{
						std::cout << "Exit" << std::endl;
						quit = true;
						break;
					}
				}
			}
		}
		SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

		//Update the surface
		SDL_UpdateWindowSurface(window);
		
	}
	return quit;
}
