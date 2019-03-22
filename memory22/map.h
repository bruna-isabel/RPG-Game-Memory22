#ifndef map_hpp
#define map_hpp
#include <stdio.h>
#include "game.h"

class map{
    
public:
    map(SDL_Renderer* ren);
    ~map();
    
    void loadMap(int array[32][32]);
    void drawMap(SDL_Renderer* ren);
    
private:
    
    SDL_Rect src_rect, dest_rect;
    
    SDL_Texture* dirt;
    SDL_Texture* grass;
    SDL_Texture* water;
    
	int Map[32][32];
    
};
#endif /* map_hpp */
