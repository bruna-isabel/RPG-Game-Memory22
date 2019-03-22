// inventory.h

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "textures.h"
#include <SDL_ttf.h>

class Inventory
{
public:
	Inventory();
	~Inventory();

	void init();

	void openInventory();

	void closeInventory();

	void drawInventory();

	void getItem(int x, int y, int type);

private:
	SDL_Renderer *ren;
	SDL_Window *window;
	SDL_Texture* invSlot;
	SDL_Texture* invItem1;
	SDL_Texture* invItem2;
	SDL_Rect src_rect, dest_rect;
	SDL_Texture* Background_Tx;
	SDL_Surface* Current_Surface;
	int Inv[32][32];
};