#include "gameObject.h"
#include "textures.h"

gameObject::gameObject(const char* texturesheet, SDL_Renderer* ren, int xx, int yy)
{
	renderer = ren;
	objectTexture = textureCreator::loadTexture(texturesheet, ren);

	x = xx;
	y = yy;
}

void gameObject::update()
{



	srcRect.h = 48;
	srcRect.w = 48;
	srcRect.x = 0;
	srcRect.y = 0;
	

	destRect.x = x;
	destRect.y = y;
	destRect.w = srcRect.w * 1.5;
	destRect.h = srcRect.h * 1.5;
}

void gameObject::movement(const char* coord, bool positive)
{
	
	if (coord == "x" && positive == true) { y -= 4; };
	if (coord == "x" && positive == false) { y += 4; };
	if (coord == "y" && positive == true) { x += 4; };
	if (coord == "y" && positive == false) { x-=4; };
	

}

void gameObject::Render()
{
	SDL_RenderCopy(renderer, objectTexture, &srcRect, &destRect);
}