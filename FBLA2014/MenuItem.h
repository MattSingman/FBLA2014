#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <functional>
#include "PositionedTexture.h"
#include "Button.h"


#ifndef MENU_ITEM_H  //avoid multiple inclusion
#define MENU_ITEM_H


class MenuItem : public Button {	 //Inherits from class Button
	
	const int WIDTH = 300; //Width of menu item
	const int HEIGHT = 100; //Height of menu item


	std::function<void()> onSelection; //Function to execute upon selection
public:
	MenuItem();
	MenuItem(const char*, std::function<void()>, window*); //constructor TODO: Param for animation? 
	std::function<void()> getFunction() { return onSelection; };


	MenuItem& MenuItem::operator=(const MenuItem &rhs) { //Equality overload
		containerWindow = rhs.containerWindow;
		path = rhs.path;
		texture = rhs.texture;
		posTexture = rhs.posTexture;
		onSelection = rhs.onSelection;
		return *this;
	}
};

#endif