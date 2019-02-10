#pragma once
#include "SDL.h"
#include <stdio.h>
#include "SDL_image.h"

class gameObject {

public:
	gameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y);
	~gameObject();

	void update();
	void Render();
	void movement(const char* coord, bool positive);
private:

	int x;
	int y;

	SDL_Texture* objectTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};