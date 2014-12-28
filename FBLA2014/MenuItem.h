#include <SDL.h>
#include <string>

#ifndef MENU_ITEM_H  //avoid multiple inclusion
#define MENU_ITEM_H

class MenuItem {
	bool selected = false;
	std::string path; //Path to menu item's art

	void *pf(); //Function to execute upon selection

public :
	MenuItem(const char*, void pf()); //constructor
};

#endif