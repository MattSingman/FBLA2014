#include "window.h"

window::window() {
	SDL_Init(SDL_INIT_EVERYTHING);//initialize SDL
	mainWindow = SDL_CreateWindow("GAMENAMEHERE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 32); //create Window TODO: Change window name
	screen = SDL_GetWindowSurface(mainWindow); //screen is on window
	activeScreens.push_back(getSurface());
	createMenu(getSurface(),getWindow()); //Load the startup menu
	while (!quit) { //main game loop
		while (SDL_PollEvent(&e) != 0) {
			//If user quits
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
	}
	close(activeScreens, mainWindow); //If quit, close window
}

void createMenu(SDL_Surface* screen, SDL_Window* mainWindow) {
	SDL_Surface* menuArt = SDL_LoadBMP("../art/menu.bmp"); //Load menu background
	SDL_BlitSurface(menuArt, NULL, screen, NULL); //Put menu background on screen
	SDL_UpdateWindowSurface(mainWindow); //Update screen
}
void close(std::vector<SDL_Surface*> activeScreens, SDL_Window* mainWindow) {
	//Deallocate surface(s)
	for (auto v : activeScreens) {
		SDL_FreeSurface(v);
		v = NULL;
	}


	//Destroy window
	SDL_DestroyWindow(mainWindow);
	mainWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}