#pragma once
//#include "SDL.h"
#include <stdio.h>
//#include "SDL_image.h"
#include <vector>
#include "SDL2_image/SDL_image.h"
#include "SDL2/SDL.h"
#include "game.h"

class GameObject {

public:
	GameObject(const char* texturesheet, SDL_Renderer* renderer, int x, int y, int _maxHp, int _currentHp, int _strength);
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
	void setDirectionFacing(char direction) { directionFacing = direction; };
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
