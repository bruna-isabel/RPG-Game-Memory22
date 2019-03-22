// inventory.cpp

#include "inventory.h"
#include <iostream>


//Inventory* inv;

Inventory::Inventory()
{
	init();
}

void Inventory::init()
{
	window = SDL_CreateWindow("INVENTORY", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	ren = SDL_CreateRenderer(window, -1, 0);
	closeInventory();

	for (int row = 0; row < 32; row++)
	{
		for (int col = 0; col < 32; col++)
		{

			Inv[row][col] = 0;
		}
	}
	src_rect.x = src_rect.y = 0;
	src_rect.w = src_rect.h = dest_rect.w = dest_rect.h = 32;

	if(window)
		std::cout << "Inventory created" << std::endl;
}

void Inventory::openInventory()
{
	SDL_ShowWindow(window);
	drawInventory();
	SDL_RenderPresent(ren);
}

void Inventory::closeInventory()
{
	SDL_HideWindow(window);
}

void Inventory::drawInventory()
{
	int type = 0;
	invSlot = textureCreator::loadTexture("inventory.png", ren);
	invItem1 = textureCreator::loadTexture("inventory2.png", ren);
	invItem2 = textureCreator::loadTexture("kewlStuffs/armour.png", ren);
	for (int row = 0; row < 32; row++)
	{
		for (int col = 0; col < 32; col++)
		{
			type = Inv[row][col];
			dest_rect.x = col * 32;
			dest_rect.y = row * 32;


			if (type == 0)
				textureCreator::draw(ren, invSlot, src_rect, dest_rect);
			else if (type == 1)
				textureCreator::draw(ren, invItem1, src_rect, dest_rect);
			else
				textureCreator::draw(ren, invItem2, src_rect, dest_rect);
			/*switch (type)
			{
			case 0:
				textureCreator::draw(ren, invSlot, src_rect, dest_rect);
			case 1:
				textureCreator::draw(ren, invItem1, src_rect, dest_rect);
			default:
				break;
			}*/
		}
	}
}


void Inventory::getItem(int x, int y,int type)
{
	int ok = 0;
	invItem1 = textureCreator::loadTexture("inventory2.png", ren);
	invItem2 = textureCreator::loadTexture("kewlStuffs/armour.png", ren);
	for (int i = 0; i < 32; i++) 
	{
		if(ok==0)
			for (int j = 0; j < 32; j++)
				if (Inv[i][j] == 0 && ok==0)
				{
					std::cout << "You have enough space in your inventory" << std::endl;
					Inv[i][j] = 1;
					dest_rect.x = i * 32;
					dest_rect.y = j * 32;
					if (type == 1)
						textureCreator::draw(ren, invItem1, src_rect, dest_rect);
					else if (type == 0)
					{
						textureCreator::draw(ren, invItem2, src_rect, dest_rect);
						Inv[i][j] = 2;
					}
					ok = 1;
				}
				else break;
		else break;
	}
	SDL_RenderPresent(ren);
}