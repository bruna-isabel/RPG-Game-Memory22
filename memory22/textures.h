#pragma once


#include "SDL_image.h"
class textureCreator 
{
public:
	static SDL_Texture* loadTexture(const char* fileName, SDL_Renderer* renderer);

};