#include "turretButton.h"
#include "window.h"

//Constructor
turretButton::turretButton(const char* artPath, const char* child, window* parentWindow) {
	path = artPath;
	childPath = child;
	containerWindow = parentWindow;

	//Create texture of turret to be displayed should the item be selected
	SDL_Rect dstrect;
	dstrect.h = 0; dstrect.w = 0; 
	dstrect.x = 0;
	dstrect.y = 0;
	SDL_Surface* surface = IMG_Load(path); 
	texture = SDL_CreateTextureFromSurface(containerWindow->getRenderer(), surface); 
	SDL_FreeSurface(surface);
	childPosTexture = PositionedTexture(texture, dstrect, 1);

}

PositionedTexture turretButton::placeOnScreen(int x, int y) {
	SDL_Rect dstrect;//SDL_Rect telling location to place button, x and y correspond to coords to place surface, from top left
	dstrect.h = getItemHeight(); dstrect.w = getItemWidth(); //Height and width are the same for each item
	dstrect.x = x-getItemWidth(); //compensates for SDL_Rect taking values at left corner, so the value passed in is the center of the item

	dstrect.y = y;
	SDL_Surface* surface = IMG_Load(path); //Load menu background
	texture = SDL_CreateTextureFromSurface(containerWindow->getRenderer(), surface); //Create texture
	SDL_FreeSurface(surface);
	posTexture = PositionedTexture(texture, dstrect, 0);
	return posTexture;

}

void turretButton::setSelected(bool update) { 
	selected = update; 
	const SDL_Rect* childRect = childPosTexture.getRect();
	if (!selected) { //Hide
		childPosTexture.setRect(childRect->x, childRect->y, 0, 0);
	}
	else {
		childPosTexture.setRect(childRect->x, childRect->y, TURRET_HEIGHT, TURRET_WIDTH);
	}
}

void turretButton::setChildPosition(int x, int y) {
	childPosTexture.setRect(x, y, TURRET_HEIGHT, TURRET_WIDTH);
}

turretButton::turretButton() {} //Default constructor

