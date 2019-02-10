#include "textures.h"

SDL_Texture* textureCreator::loadTexture(const char* texture, SDL_Renderer* ren)
{
	SDL_Surface* tempS = IMG_Load(texture);
	SDL_Texture* textu = SDL_CreateTextureFromSurface(ren, tempS);
	SDL_FreeSurface(tempS);
	return textu;
}