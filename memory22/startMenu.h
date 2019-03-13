#include <SDL.h>
#include <SDL_image.h>
#include <string>
//Learned SDL2 from http://lazyfoo.net/tutorials/SDL/index.php
class startMenu 
{
    private:
    public:
    enum KeyPressSurfaces
    {
        continueGame,
        newGame,
        saveGame,
        exitGame,
        total
    };


    SDL_Window* gWindow = NULL;
    SDL_Surface* gScreenSurface = NULL;
    SDL_Surface* gKeyPressSurfaces[total];
    SDL_Surface* gCurrentSurface = NULL;
    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 720;
    int index = 0;
    

    startMenu(SDL_Window *window);
    ~startMenu();
    SDL_Surface* loadSurface( std::string path );
    void render();
    void menuLoop(SDL_Window *window);



};