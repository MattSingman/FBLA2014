#include "window.h"

window::window() { //TODO: Music
	SDL_Init(SDL_INIT_EVERYTHING);//initialize SDL
	mainWindow = SDL_CreateWindow("GAMENAMEHERE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 32); //create Window TODO: Change window name
	screen = SDL_GetWindowSurface(mainWindow); //screen is on window
	activeScreens.push_back(screen);
	loadBackgroundSurface(this, "../art/menu.bmp"); //Load the startup menu
	createMenu(this);
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
//Loads surface and places it on the screen
SDL_Surface* loadBackgroundSurface(const window* window, std::string path){ //TODO Animation! TODO Make it more reusable
	SDL_Surface* art = IMG_Load(path.c_str()); //Load menu background
	art = SDL_ConvertSurface(art, window->getSurface()->format, NULL); //optimize image 
	SDL_BlitSurface(art, NULL, window->getSurface(), NULL); //Put menu background on screen
	SDL_UpdateWindowSurface(window->getWindow()); //Update screen
	window->getSurfaces().push_back(art); //Add to array of surfaces
	return art;
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
//start a new game
void newGame() {
	
}
//show options
void showOptions() {

}
//Shows instructions on how to play
void showHelp() {

}
//Quits program
void quit() {

}
//Creates menu with options
void createMenu(const window* window) {
	std::vector<MenuItem> menuItems = window->getMenuItems();
	MenuItem newGameOption = MenuItem("../art/newGame.bmp", newGame);
	menuItems.push_back(newGameOption);
	MenuItem optionsOption = MenuItem("../art/options.bmp", newGame);
	menuItems.push_back(newGameOption);
	MenuItem helpOption = MenuItem("../art/help.bmp", newGame);
	menuItems.push_back(newGameOption);
	MenuItem quitOption = MenuItem("../art/quit.bmp", newGame);
	menuItems.push_back(newGameOption);

}
