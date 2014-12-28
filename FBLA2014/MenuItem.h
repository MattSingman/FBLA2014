#include <SDL.h>
#include <SDL_image.h>
#include <string>

#ifndef MENU_ITEM_H  //avoid multiple inclusion
#define MENU_ITEM_H
class window;

class MenuItem {	
	bool selected = false;
	const window* containerWindow; //Window menuItem is located in
	const char* path; //Path to menu item's art
	const int WIDTH = 300; //Width of menu item
	const int HEIGHT = 100; //Height of menu item

	void (*onSelection)(); //Function to execute upon selection

public :
	MenuItem(const char*, void function(), const window*); //constructor TODO: Param for animation? 
	const window* getContainerWindow() const { return containerWindow; };
	SDL_Surface* placeOnScreen(int x, int y, int, int); //Places MenuItem on screen at given location (IMPORTANT: X-Y location is at CENTER)
	//given number of previous MenuItems, and distance between each item 
	const int getItemWidth() const { return WIDTH; };
	const int getItemHeight() const { return HEIGHT; };
};

#endif