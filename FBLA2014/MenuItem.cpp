#include "MenuItem.h"
#include "window.h"

//Constructor
MenuItem::MenuItem(const char* artPath, void function(), const window* parentWindow) {
	path = artPath;
	onSelection = function;
	containerWindow = parentWindow;

}

SDL_Surface* MenuItem::placeOnScreen(int x, int y, int numPrev, int distanceAllotted) {
	SDL_Rect dstrect;//SDL_Rect telling location to place MenuItem, x and y correspond to coords to place surface, from top left
	dstrect.h = 0; dstrect.w = 0;//The height and width are ignored when used as the 4th parameter in the SDL_BlitSurface function
	dstrect.x = x - (WIDTH/2); //compensates for SDL_Rect taking values at left corner, so the value passed in is the center of the item
	//TODO dstrect.y
	dstrect.y = y +
		(numPrev*distanceAllotted) + //Base distance + distanceallotted for each other TODO LOOK AT THIS LATER
		(distanceAllotted - getItemHeight()) / 2;
	SDL_Surface* surface = IMG_Load(path); //Load menu background
	surface = SDL_ConvertSurface(surface, getContainerWindow() -> getSurface() -> format, NULL); //optimize image 
	SDL_BlitSurface(surface, NULL, getContainerWindow()->getSurface(), &dstrect); //Put menu background on screen. Change dstrect to a pointer TODO: Make it a pointer all the way through?
	return surface;

}