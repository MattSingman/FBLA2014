#include <SDL.h>   
#ifndef WINDOW_H  //avoid multiple inclusion
#define WINDOW_H

class window{
	//Screen dimension constants 
	//TODO: Make it user inputted?
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 400;

	SDL_Window* mainWindow; //The window
	SDL_Surface* screen; //surface in window



public:
	window(); //constructor
	const int getScreenWidth() const { return SCREEN_WIDTH; }; 
	const int getScreenHeight() const { return SCREEN_HEIGHT; };
	SDL_Window* getWindow() const { return mainWindow; }; 
	SDL_Surface* getSurface() const { return screen; };

};
void createMenu(SDL_Surface* screen, SDL_Window* mainWindow); //creates startup menu

#endif