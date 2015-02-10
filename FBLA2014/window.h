#include <SDL.h> 
#include <SDL_Image.h>
#include <vector>
#include <string>
#include <functional>
#include <array>
#include "MenuItem.h"
#include "PositionedTexture.h"
#include "timer.h"
#include "turretButton.h"
#include "Block.h"
#include "PathBlock.h"
#include "WallBlock.h"
#include "game.h"
#include "TextTexture.h"
#include "File.h"
#include "MessageBox.h"


#ifndef WINDOW_H  //avoid multiple inclusion
#define WINDOW_H

class window{
	//Screen dimension constants 
	//TODO: Make it user inputted?
	const int SCREEN_WIDTH = 1366;
	const int SCREEN_HEIGHT = 768;
	const int SCREEN_FPS = 60;
	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

	const int MAX_LEVEL = 1;

	//Constants for MenuItem positioning, see MenuItem.h for further details
	const int MenuItemX = SCREEN_WIDTH/2; //Gives where CENTER of MenuItem should be
	const int MenuItemY = SCREEN_HEIGHT / 6; //Gives how much seperates top from first item and bottom from last //TODO, keep working on y positioning

	SDL_Window* mainWindow; //The window
	SDL_Surface* screen; //surface in window
	SDL_Texture* background; //background texture
	SDL_Renderer* renderer; //Renderer

	std::vector<PositionedTexture> textures;
	std::vector<MenuItem> menuItems; //Array of MenuItems
	std::vector<turretButton> turretButtons; //Vector of turret buttons (in game)
	std::vector<WallBlock> wallBlocks;//Vector of blocks
	std::vector<PathBlock> pathBlocks; //vector of path blocks (what enemy can walk on)
	Button playButton;

	TTF_Font* textFont;

	game currentGame;
	
	bool quit = false; //user has not quit
	bool inGame = false; //Is user playing or in menu?
	bool dialogBox = false; //If dialog box is open
	SDL_Event e; //Event handler

	//The frames per second timer
	timer fpsTimer;
	//The frames per second cap timer
	timer capTimer;
	int countedFrames = 0;
	int frameUntilNextKeyPressRegistered = 0;

	std::vector<std::vector<std::string>> gamePath; //Values assigned inside the newGame member function




public:
	window(); //constructor

	bool isInGame() const { return inGame; };
	void setInGame(bool change) { inGame = change; };

	const int getScreenWidth() const { return SCREEN_WIDTH; }; 
	const int getScreenHeight() const { return SCREEN_HEIGHT; };
	const int getMaxLevel() const { return MAX_LEVEL; };
	SDL_Window* getWindow() const { return mainWindow; }; 
	SDL_Surface* getSurface() const { return screen; }; 
	SDL_Renderer* getRenderer() const{ return renderer; }; 
	SDL_Texture* getBackgroundTexture() const { return background; };

	//Get MenuItem constants
	const int getMenuItemX() const { return MenuItemX; };
	const int getMenuItemY() const { return MenuItemY; };


	std::vector<MenuItem> getMenuItems() const{ return menuItems; }; 
	std::vector<PositionedTexture> getTextures() const { return textures; };
	std::vector<turretButton> getTurretButtons() const { return turretButtons; };
	std::vector<WallBlock> getWallBlocks() const { return wallBlocks; };
	std::vector<PathBlock> getPathBlocks() const { return pathBlocks; };

	void createMenu(); //creates startup menu
	void loadBackgroundSurface(std::string path); //Loads surface onto window

	void window::newGame();
	void window::showHelp();
	void window::quitWindow();

	void close(); //Closes SDL

};

#endif