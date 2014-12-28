#include "window.h"

window::window() { //TODO: Music
	SDL_Init(SDL_INIT_EVERYTHING);//initialize SDL
	mainWindow = SDL_CreateWindow("GAMENAMEHERE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 32); //create Window TODO: Change window name
	screen = SDL_GetWindowSurface(mainWindow); //screen is on window
	activeScreens.push_back(screen);
	loadBackgroundSurface("../art/menu.bmp"); //Load the startup menu
	createMenu();
	while (!quit) { //main menu loop TODO: seperate function when running game?
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
SDL_Surface* window::loadBackgroundSurface(std::string path){ //TODO Animation! TODO Make it more reusable
	SDL_Surface* art = IMG_Load(path.c_str()); //Load menu background
	art = SDL_ConvertSurface(art, getSurface()->format, NULL); //optimize image 
	SDL_BlitSurface(art, NULL, getSurface(), NULL); //Put menu background on screen
	SDL_UpdateWindowSurface(getWindow()); //Update screen
	getSurfaces().push_back(art); //Add to array of surfaces
	return art;
} 

void window::close(std::vector<SDL_Surface*> activeScreens, SDL_Window* mainWindow) { //TODO MenuItems close themselves
	//Deallocate surface(s)
	for (auto& v : activeScreens) {
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
void quitWindow() {

}
//Creates menu with options
void window::createMenu() {
	std::vector<MenuItem> menuItems = getMenuItems();

	MenuItem newGameOption = MenuItem("../art/newGame.bmp", newGame, this);  //New game option
	menuItems.push_back(newGameOption); //Adds to array of MenuItems

	MenuItem optionsOption = MenuItem("../art/options.bmp", showOptions, this);  //Show options menu
	menuItems.push_back(optionsOption);

	MenuItem helpOption = MenuItem("../art/help.bmp", showHelp, this); //Show help 
	menuItems.push_back(helpOption);

	MenuItem quitOption = MenuItem("../art/quit.bmp", quitWindow, this); //Quit
	menuItems.push_back(quitOption);

	int distanceAllotted = (getScreenHeight() - (2 * getMenuItemY())) / menuItems.size(); //distance between each item is the space allowed to the items divided by the number of items
	//TODO distance allotted
	for (size_t i = 0; i < menuItems.size(); ++i) {
		menuItems[i].placeOnScreen(getMenuItemX(), getMenuItemY(), i, distanceAllotted);//Place each MenuItem on screen
	}
	SDL_UpdateWindowSurface(getWindow()); //Update screen


}
