#include <SDL.h>   
#include <vector>
#ifndef WINDOW_H  //avoid multiple inclusion
#define WINDOW_H

class window{
	//Screen dimension constants 
	//TODO: Make it user inputted?
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 400;

	SDL_Window* mainWindow; //The window
	SDL_Surface* screen; //surface in window
	std::vector<SDL_Surface*> activeScreens;

	bool quit = false; //user has not quit
	SDL_Event e; //Event handler

public:
	window(); //constructor
	const int getScreenWidth() const { return SCREEN_WIDTH; }; 
	const int getScreenHeight() const { return SCREEN_HEIGHT; };
	SDL_Window* getWindow() const { return mainWindow; }; 
	SDL_Surface* getSurface() const { return screen; };

};
void createMenu(SDL_Surface* screen, SDL_Window* mainWindow); //creates startup menu
void close(std::vector<SDL_Surface*> activeScreens, SDL_Window* mainWindow); //Closes SDL
#endif