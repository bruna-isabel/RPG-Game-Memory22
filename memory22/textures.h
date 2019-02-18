#pragma once
#include "SDL2_image/SDL_image.h"

// #include "SDL_image.h"

#include "game.h"

class textureCreator 
{
public:
	static SDL_Texture* loadTexture(const char* fileName, SDL_Renderer* ren);
    static void draw(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
    
private:
    SDL_Renderer* renderer;
};
