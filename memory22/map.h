#ifndef map_hpp
#define map_hpp
#include <stdio.h>
#include "game.h"
#include <string>

//Class that refers to all of the environment and textures of the game
class map{
    
public:
    map(SDL_Renderer* ren);
    ~map();
    
    std::vector<std::string> createArray(std::string textFile);
    void drawMap(SDL_Renderer* ren, std::string textFile);
    
private:
    
    SDL_Rect src_rect, dest_rect; //rectangle that will render on screen
    
    //textures in the environment
    SDL_Texture* tree;
    SDL_Texture* grass;
    SDL_Texture* water;
    
};
#endif /* map_hpp */
