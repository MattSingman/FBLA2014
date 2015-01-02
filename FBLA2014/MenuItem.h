#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "PositionedTexture.h"


#ifndef MENU_ITEM_H  //avoid multiple inclusion
#define MENU_ITEM_H
class window;

class MenuItem {	
	window* containerWindow; //Window menuItem is located in
	const char* path; //Path to menu item's art
	const int WIDTH = 300; //Width of menu item
	const int HEIGHT = 100; //Height of menu item
	SDL_Texture* texture;
	PositionedTexture posTexture;

	void (*onSelection)(); //Function to execute upon selection

public :
	MenuItem();
	MenuItem(const char*, void function(), window*); //constructor TODO: Param for animation? 
	window* getContainerWindow() const { return containerWindow; };
	SDL_Texture* getSDLTexture() const { return texture; };
	PositionedTexture getTexture() const { return posTexture; };
	PositionedTexture placeOnScreen(int x, int y, int, int); //Places MenuItem on screen at given location (IMPORTANT: X-Y location is at CENTER)
	//given number of previous MenuItems, and distance between each item 
	const int getItemWidth() const { return WIDTH; };
	const int getItemHeight() const { return HEIGHT; };
	int getXPos() const { return posTexture.getXPos(); };
	int getYPos() const { return posTexture.getYPos(); };

	auto getFunction() -> void(*)();

	bool insidePos(int, int);

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