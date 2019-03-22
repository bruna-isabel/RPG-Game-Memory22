// items.h

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "textures.h"

class Item
{
public:
	Item(int x, int y, int type, SDL_Renderer* ren);
	~Item();

	void spawnItem(SDL_Renderer* ren);

	void useItem(int type);

	void HideItem(SDL_Renderer* ren);

	int getX() { return x; };
	int getY() { return y; };
	int getType() { return Type; };
	void Render();
	int getPicked();
private:
	int Type; // 0 = armour; 1 = weapon;
	int defence;
	int damage;
	int Picked; // 0 if the item wasn't picked up yet ; 1 otherwise.

	int x,y; // where the item has been dropped
	SDL_Renderer* ren;
	SDL_Rect src_rect, dest_rect;
	SDL_Texture* item1;
	SDL_Texture* item2;
	SDL_Texture* objectTexture;
	SDL_Texture* grass;
};