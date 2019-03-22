// items.cpp

#include "items.h"
using namespace std;
#include <iostream>

Item::Item(int k, int z, int type, SDL_Renderer* ren)
{
	x = k;
	y = z;
	Picked = 0;
	Type = type;
	//if (type == 0)
		//addDefence(); // function call to add armour stats to char
	//else
		//addDamage(); // function call to add weapon stats to char

	src_rect.x = src_rect.y = 0;
	src_rect.w = src_rect.h = dest_rect.w = dest_rect.h = 32;
}


void Item::HideItem(SDL_Renderer* ren)
{
	Picked = 1;
	dest_rect.x = x * 32;
	dest_rect.y = y * 32;
	std::cout << "The item is not there anymore" << std::endl;
	grass = textureCreator::loadTexture("kewlStuffs/mossover.png", ren);
	textureCreator::draw(ren, grass, src_rect, dest_rect);
	SDL_RenderPresent(ren);
}

void Item::Render()
{
	SDL_RenderCopy(ren, objectTexture, &src_rect, &dest_rect);
}


int Item::getPicked()
{
	return Picked;
}

void Item::useItem(int type)
{
	if (type == 0)
	{
		//add armour stats
	}
	else
	{
		//add weapon stats
	}
}

void Item::spawnItem(SDL_Renderer* ren)
{
	dest_rect.x = x;
	dest_rect.y = y;
	item1 = textureCreator::loadTexture("item1.png", ren);
	item2 = textureCreator::loadTexture("kewlStuffs/armour.png", ren);
	if (Type == 1)
		textureCreator::draw(ren, item1, src_rect, dest_rect);
	else
		textureCreator::draw(ren, item2, src_rect, dest_rect);
}
