#include "MenuItem.h"
#include "window.h"

//Constructor
MenuItem::MenuItem(const char* artPath, void function(), window* parentWindow) {
	path = artPath;
	onSelection = function;
	containerWindow = parentWindow;

}
MenuItem::MenuItem() {} //Default constructor

PositionedTexture MenuItem::placeOnScreen(int x, int y, int numPrev, int distanceAllotted) {
	SDL_Rect dstrect;//SDL_Rect telling location to place MenuItem, x and y correspond to coords to place surface, from top left
	dstrect.h = HEIGHT; dstrect.w = WIDTH; //Height and width are the same for each item
	dstrect.x = x - (WIDTH/2); //compensates for SDL_Rect taking values at left corner, so the value passed in is the center of the item
	//TODO dstrect.y
	dstrect.y = y +
		(numPrev*distanceAllotted) + //Base distance + distanceallotted for each other TODO LOOK AT THIS LATER
		(distanceAllotted - getItemHeight()) / 2;
	SDL_Surface* surface = IMG_Load(path); //Load menu background
	texture = SDL_CreateTextureFromSurface(containerWindow->getRenderer(), surface); //Create texture
	SDL_FreeSurface(surface);
	posTexture =PositionedTexture(texture, dstrect);
	return posTexture;

}

//is given position inside button?
bool MenuItem::insidePos(int mouseX, int mouseY) { //TODO Member function vs variable?
	//Check if mouse is in button
	bool inside = true;

	//Mouse is left of the button
	if (mouseX < getXPos()) {
		inside = false;
	}
	//Mouse is right of the button
	else if (mouseX > getXPos() + getItemWidth()) {
		inside = false;
	}
	//Mouse above the button
	else if (mouseY < getYPos()) {
		inside = false;
	}
	//Mouse below the button
	else if (mouseY > getYPos() + getItemHeight()) {
		inside = false;
	}
	return inside;
}

auto MenuItem::getFunction()-> void(*)() {
	return onSelection;
}