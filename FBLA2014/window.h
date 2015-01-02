#include <SDL.h> 
#include <SDL_Image.h>
#include <vector>
#include <string>
#include "MenuItem.h"
#include "PositionedTexture.h"

#ifndef WINDOW_H  //avoid multiple inclusion
#define WINDOW_H

class window{
	//Screen dimension constants 
	//TODO: Make it user inputted?
	const int SCREEN_WIDTH = 1366;
	const int SCREEN_HEIGHT = 768;

	//Constants for MenuItem positioning, see MenuItem.h for further details
	const int MenuItemX = SCREEN_WIDTH/2; //Gives where CENTER of MenuItem should be
	const int MenuItemY = SCREEN_HEIGHT / 20; //Gives how much seperates top from first item and bottom from last //TODO, keep working on y positioning

	SDL_Window* mainWindow; //The window
	SDL_Surface* screen; //surface in window
	SDL_Texture* background; //background texture
	SDL_Renderer* renderer; //Renderer

	std::vector<PositionedTexture> textures;
	std::vector<MenuItem> menuItems; //Array of MenuItems, used to scroll through the options
	
	bool quit = false; //user has not quit
	SDL_Event e; //Event handler

public:
	window(); //constructor
	const int getScreenWidth() const { return SCREEN_WIDTH; }; 
	const int getScreenHeight() const { return SCREEN_HEIGHT; };
	SDL_Window* getWindow() const { return mainWindow; }; 
	SDL_Surface* getSurface() const { return screen; }; 
	SDL_Renderer* getRenderer() const{ return renderer; }; 
	SDL_Texture* getBackgroundTexture() const { return background; };

	//Get MenuItem constants
	const int getMenuItemX() const { return MenuItemX; };
	const int getMenuItemY() const { return MenuItemY; };


	std::vector<MenuItem> getMenuItems() const{ return menuItems; }; //TODO Pointer?
	std::vector<PositionedTexture> getTextures() const { return textures; };

	void createMenu(); //creates startup menu
	void loadBackgroundSurface(std::string path); //Loads surface onto window
	void close(); //Closes SDL

};

#endif