#include "Button.h"

#include "window.h"

//Constructor
Button::Button(const char* artPath,window* parentWindow) {
	path = artPath;
	containerWindow = parentWindow;

}
Button::Button() {} //Default constructor

PositionedTexture Button::placeOnScreen(int x, int y) {
	SDL_Rect dstrect;//SDL_Rect telling location to place button, x and y correspond to coords to place surface, from top left
	dstrect.h = getItemHeight(); dstrect.w = getItemWidth(); //Height and width are the same for each item
	dstrect.x = x; //compensates for SDL_Rect taking values at left corner, so the value passed in is the center of the item
	
	dstrect.y = y;
	SDL_Surface* surface = IMG_Load(path); //Load menu background
	texture = SDL_CreateTextureFromSurface(containerWindow->getRenderer(), surface); //Create texture
	SDL_FreeSurface(surface);
	posTexture = PositionedTexture(texture, dstrect,0);
	return posTexture;

}

//is given position inside button?
bool Button::insidePos(int mouseX, int mouseY) { 
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

