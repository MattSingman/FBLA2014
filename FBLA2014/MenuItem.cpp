#include "MenuItem.h"
#include "window.h"

//Constructor
MenuItem::MenuItem(const char* artPath, std::function<void()> function, window* parentWindow) {
	path = artPath;
	onSelection = function;
	containerWindow = parentWindow;

}

PositionedTexture MenuItem::placeOnScreen(int x, int y) {
	SDL_Rect dstrect;//SDL_Rect telling location to place button, x and y correspond to coords to place surface, from top left
	dstrect.h = getItemHeight(); dstrect.w = getItemWidth(); //Height and width are the same for each item
	dstrect.x = x - (getItemWidth()/2); //compensates for SDL_Rect taking values at left corner, so the value passed in is the center of the item

	dstrect.y = y;
	SDL_Surface* surface = IMG_Load(path); //Load menu background
	texture = SDL_CreateTextureFromSurface(containerWindow->getRenderer(), surface); //Create texture
	SDL_FreeSurface(surface);
	posTexture = PositionedTexture(texture, dstrect, 0);
	return posTexture;

}
MenuItem::MenuItem() {} //Default constructor

