#include "gameObject.h"
#include "textures.h"
#include "game.h"
#include <math.h>
#include <iostream>
#include <vector>

std::vector<GameObject *> GameObject::allEntities;

GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren, int xx, int yy, int _maxHp, int _currentHp, int _strength)
{
	allEntities.push_back(this);
	renderer = ren;
	objectTexture = textureCreator::loadTexture(texturesheet, ren); //used to be ren
	maxHp = _maxHp;
	currentHp = _currentHp;
	changeStrength(_strength);
	x = xx;
	y = yy;
}

GameObject::~GameObject()
{
	
}

void GameObject::update()
{

	srcRect.h = 48;
	srcRect.w = 48;
	srcRect.x = 0;
	srcRect.y = 0;
	

	destRect.x = x;
	destRect.y = y;
	destRect.w = srcRect.w * 1.5; //72 ignore
	destRect.h = srcRect.h * 1.5; 
}

void GameObject::movement(const char* coord, bool positive)
{
	
	if (coord == "x" && positive == true) 
	{ 
		y -= 4;
		setDirectionFacing('w');

	};
    
	if (coord == "x" && positive == false) 
	{ 
		y += 4; 
		setDirectionFacing('s');

	};
    
	if (coord == "y" && positive == true) 
	{ 
		x += 4;
		setDirectionFacing('d');

	};
    
	if (coord == "y" && positive == false) 
	{ 
		x -= 4; 
		setDirectionFacing('a');
	};
	

}

void GameObject::Render()
{
	SDL_RenderCopy(renderer, objectTexture, &srcRect, &destRect);
}

int GameObject::getCurrentHp() { return currentHp; };

int GameObject::getMaxHp() { return maxHp; };

void GameObject::setCurrentHp(int change) { currentHp += change; };

void GameObject::addMaxHp(int change) { maxHp += change; };

int GameObject::getStrength() { return strength; }

void GameObject::changeStrength(int change) { strength += change; }

void GameObject::attack() 
{
	for (std::vector<GameObject *>::iterator it = allEntities.begin(); it != allEntities.end(); it++)
	{
		int xOther = (*it)->getX();
		int yOther = (*it)->getY();
		if ( (xOther <= x+36 &&  xOther >= x-48-36) && (yOther <= y+36 && yOther >= y-48-36 ) && *it != this )
		{
			(*it)->setCurrentHp(-getStrength());
		}
	}
	
}
