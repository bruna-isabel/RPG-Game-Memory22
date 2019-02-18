#pragma once
#include "SDL2/SDL.h"
// #include "SDL.h"
// #include "SDL_image.h"
#include <stdio.h>
#include "SDL2_image/SDL_image.h"

#include <vector>

#include "game.h"

class GameObject {

public:
	GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y, int _maxHp, int _currentHp, int _strength);
	~GameObject();


	static std::vector<GameObject *> allEntities;

	void update();
	void Render();
	void movement(const char* coord, bool positive);
	int getMaxHp();
	void addMaxHp(int change);
	int getCurrentHp();
	void setCurrentHp(int change);
	int getStrength();
	void changeStrength(int change);
	void attack();
	int getX() { return x; };
	int getY() { return y; };
	void setDirectionFacing(char direction) 
	{ 
		directionFacing = direction;
		if (directionFacing == 'w') {
			srcRect.x = 0;
		}
		else if (directionFacing == 's') {
			srcRect.x = 32;
		}
		else if (directionFacing == 'd') {
			srcRect.x = 64;
		}
		else if (directionFacing == 'a') {
			srcRect.x = 96;
		}
	
	};
	char getDirectionFacing() { return directionFacing; };
    
private:

	int x;
	int y;
	int strength;
	int maxHp;
	int currentHp;
	char directionFacing;


	SDL_Texture* objectTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};
