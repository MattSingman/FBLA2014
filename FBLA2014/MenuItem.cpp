#include "MenuItem.h"
#include "window.h"

//Constructor
MenuItem::MenuItem(const char* artPath, std::function<void()> function, window* parentWindow) {
	path = artPath;
	onSelection = function;
	containerWindow = parentWindow;

}
MenuItem::MenuItem() {} //Default constructor

