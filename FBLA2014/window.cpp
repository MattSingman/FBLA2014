#include "window.h"

window::window() {
	SDL_Init(SDL_INIT_EVERYTHING);//initialize SDL
	mainWindow = SDL_CreateWindow("GAMENAMEHERE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 32); //create Window TODO: Change window name
	screen = SDL_GetWindowSurface(mainWindow); //screen is on window
	activeScreens.push_back(getSurface());
	loadSurface(this, "../art/menu.bmp"); //Load the startup menu
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
SDL_Surface* loadSurface(const window* window, std::string path){ //TODO Animation! 
	SDL_Surface* art = IMG_Load(path.c_str()); //Load menu background
	SDL_BlitSurface(art, NULL, window -> getSurface(), NULL); //Put menu background on screen
	SDL_UpdateWindowSurface(window ->getWindow()); //Update screen
	window ->getSurfaces().push_back(art); //Add to array of surfaces
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